// ============================================================================================
//		２パス描画のトゥーンレンダリングのプログラム
//		Ｃ３ＤＴｏｏｎ３                           ver 2.8        2020.5.3
//
//																	MPR.cpp
// ============================================================================================
#include "MPR.h"


//------------------------------------------------------------------------
//
//  コンストラクター
//
//------------------------------------------------------------------------
CMPR::CMPR(CShader* pShader)
{
	ZeroMemory(this, sizeof(this));
	m_pD3D = pShader->m_pD3D;
	m_pShader = pShader;

	//  マルチパスレンダリング用テクスチャの設定
	D3D11_TEXTURE2D_DESC tdesc;
	ZeroMemory(&tdesc, sizeof(D3D11_TEXTURE2D_DESC));
	tdesc.Width = m_pD3D->m_dwWindowWidth;  // テクスチャの大きさ
	tdesc.Height = m_pD3D->m_dwWindowHeight;
	tdesc.MipLevels = 1;     // ミップマップ・レベル数
	tdesc.ArraySize = 1;
	tdesc.MiscFlags = 0;
	//tdesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT; // テクスチャ・フォーマット
	tdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // テクスチャ・フォーマット
	tdesc.SampleDesc.Count = 1;
	tdesc.SampleDesc.Quality = 0;
	tdesc.Usage = D3D11_USAGE_DEFAULT;
	tdesc.BindFlags = D3D11_BIND_RENDER_TARGET |      // 描画ターゲット
		D3D11_BIND_SHADER_RESOURCE;       // シェーダで使う
	tdesc.CPUAccessFlags = 0;
	m_pD3D->m_pDevice->CreateTexture2D(&tdesc, NULL, &m_pMPR_Tex);

	// テクスチャー用　レンダーターゲットビュー作成
	D3D11_RENDER_TARGET_VIEW_DESC DescRT;
	DescRT.Format = tdesc.Format;
	DescRT.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	DescRT.Texture2D.MipSlice = 0;
	m_pD3D->m_pDevice->CreateRenderTargetView(m_pMPR_Tex, &DescRT, &m_pMPR_TexRTV);

	// テクスチャ用　シェーダーリソースビュー(SRV)作成	
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));
	SRVDesc.Format = tdesc.Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = tdesc.MipLevels;
	m_pD3D->m_pDevice->CreateShaderResourceView(m_pMPR_Tex, &SRVDesc, &m_pMPR_TexSRV);

	// マップテクスチャをレンダーターゲットにする際のデプスステンシルビュー用のテクスチャーを作成
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = m_pD3D->m_dwWindowWidth;
	descDepth.Height = m_pD3D->m_dwWindowWidth;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	m_pD3D->m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pMPR_DSTex);

	//そのテクスチャーに対しデプスステンシルビュー(DSV)を作成
	m_pD3D->m_pDevice->CreateDepthStencilView(m_pMPR_DSTex, NULL, &m_pMPR_DSTexDSV);

	// -------------------------------------------------------------------------------------
	DWORD dwWidth = m_pD3D->m_dwWindowWidth;
	DWORD dwHeight = m_pD3D->m_dwWindowHeight;

	//バーテックスバッファー作成
	//気をつけること。z値を１以上にしない。クリップ空間でz=1は最も奥を意味する。したがって描画されない。
	MPRVertex vertices[] =
	{
		VECTOR3(0,              (float)dwHeight, 0), VECTOR2(0,1),      //頂点1  左下
		VECTOR3((float)dwWidth, (float)dwHeight, 0), VECTOR2(1,1),      //頂点2　右下
		VECTOR3(0,                            0, 0), VECTOR2(0,0),      //頂点3　左上
		VECTOR3((float)dwWidth,               0, 0), VECTOR2(1,0),      //頂点4　右上
	};

	// バーテックスバッファ作成する
	D3D11_BUFFER_DESC bd;
	//bd.Usage          = D3D11_USAGE_DEFAULT;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(MPRVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferMPR)))
	{
		MessageBox(0, _T("MPR バーテックスバッファー作成失敗"), NULL, MB_OK);
	}


}
//------------------------------------------------------------------------
//
//	デストラクタ	
//
//------------------------------------------------------------------------
CMPR::~CMPR()
{
	SAFE_RELEASE(m_pMPR_Tex);		//  マルチパスレンダリング用テクスチャ    // -- 2020.5.3
	SAFE_RELEASE(m_pMPR_TexRTV);
	SAFE_RELEASE(m_pMPR_TexSRV);
	SAFE_RELEASE(m_pMPR_DSTex);
	SAFE_RELEASE(m_pMPR_DSTexDSV);

	SAFE_RELEASE(m_pVertexBufferMPR);

}


//------------------------------------------------------------------------
//
//	Render MPR処理	
//
//  引数　なし
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CMPR::RenderMPR()
{

	//使用するシェーダーのセット
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pMPR_VS, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pMPR_PS, NULL, 0);

	//このコンスタントバッファーをどのシェーダーで使うか
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferMPR);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferMPR);
	//頂点インプットレイアウトをセット
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pMPR_VertexLayout);

	//プリミティブ・トポロジーをセット
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// サンプラーをセット
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetSamplers(1, 1, &m_pD3D->m_pSampleBorder);

	//Zバッファを無効化
	m_pD3D->m_pDeviceContext->OMSetRenderTargets(1, &m_pD3D->m_pBackBuffer_TexRTV, NULL);

	//バーテックスバッファーをセット
	UINT stride = sizeof(MPRVertex);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferMPR, &stride, &offset);

	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_MPR     cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferMPR, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{

		//ビューポートサイズを渡す（クライアント領域の横と縦）
		cb.ViewPort.x = m_pD3D->m_dwWindowWidth;
		cb.ViewPort.y = m_pD3D->m_dwWindowHeight;
		cb.Info = m_vInfo;
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferMPR, 0);
	}

	//テクスチャーをシェーダーに渡す
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pMPR_TexSRV);   // MPRマップテクスチャ

	//プリミティブをレンダリング
	m_pD3D->m_pDeviceContext->Draw(4, 0);

	//Zバッファを有効化
	m_pD3D->SetZBuffer(TRUE);

}

