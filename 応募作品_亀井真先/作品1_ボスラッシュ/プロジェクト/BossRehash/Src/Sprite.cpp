// ========================================================================================
//
// スプライトの処理                                        ver ver 2.8        2020.2.15
//
//   前バージョンの処理に加え、DrawLine 線の描画処理と DrawRect 四角の描画処理が加わった
//   Sprite.h Sprite.cpp Sprite2D.hlsli Direct3D.h が変更となっている
//
// ========================================================================================

#include "Sprite.h"

//------------------------------------------------------------------------
//
//	スプライトイメージのコンストラクタ	
//
//  引数　CShader* pShader
//
//------------------------------------------------------------------------
CSpriteImage::CSpriteImage(CShader* pShader)
{
	ZeroMemory(this, sizeof(CSpriteImage));
	m_pShader = pShader;
	m_pD3D = pShader->m_pD3D;
}
//------------------------------------------------------------------------
//
//	スプライトイメージのコンストラクタ	
//
//	CShader* pShader
//  TCHAR*   TName  スプライトファイル名
//
//------------------------------------------------------------------------
CSpriteImage::CSpriteImage(CShader* pShader, TCHAR* TName)
{
	ZeroMemory(this, sizeof(CSpriteImage));
	m_pShader = pShader;
	m_pD3D = pShader->m_pD3D;
	Load(TName);
}
//------------------------------------------------------------------------
//
//	スプライトイメージのデストラクタ	
//
//------------------------------------------------------------------------
CSpriteImage::~CSpriteImage()
{
	SAFE_RELEASE(m_pTexture);
}


//------------------------------------------------------------------------
//	スプライトイメージの読み込み	
//
//	指定したスプライトファイル名のイメージを読み込む
//
//  TCHAR*   TName  スプライトファイル名
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= ファイル名が見つからない
//------------------------------------------------------------------------
HRESULT CSpriteImage::Load(TCHAR* TName)
{
	if (FAILED(m_pD3D->CreateShaderResourceViewFromFile(TName, &m_pTexture, m_dwImageWidth, m_dwImageHeight)))
	{
		MessageBox(0, _T("スプライト　テクスチャーを読み込めません"), TName, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

//------------------------------------------------------------------------
//
//	スプライトのコンストラクタ	
//
//  引数　CShader* pShader
//
//------------------------------------------------------------------------
CSprite::CSprite(CShader* pShader)
{
	ZeroMemory(this, sizeof(CSprite));
	m_pShader = pShader;
	m_pD3D = pShader->m_pD3D;
	m_vDiffuse = VECTOR4(1, 1, 1, 1);    // -- 2020.1.24
	m_nBlend = 1;
}
//------------------------------------------------------------------------
//                                                         // -- 2017.10.9
//	スプライトのコンストラクタ	
//
//  引数
//  CSpriteImage* pImage      スプライトイメージポインタ
//
//------------------------------------------------------------------------
CSprite::CSprite(CSpriteImage* pImage)
{
	ZeroMemory(this, sizeof(CSprite));
	m_pShader = pImage->m_pShader;
	m_pD3D = pImage->m_pD3D;
	m_vDiffuse = VECTOR4(1, 1, 1, 1);    // -- 2020.1.24
	m_nBlend = 1;
	m_pImage = pImage;

}
//------------------------------------------------------------------------
//
//	スプライトのコンストラクタ	
//
//  CSpriteImage* pImage      スプライトイメージポインタ
//  DWORD         srcX        パターンの左上　Ｘ座標
//  DWORD         srcY        パターンの左上　Ｙ座標
//  DWORD         srcwidth    パターンの幅
//  DWORD         srcheight   パターンの高さ
//
//------------------------------------------------------------------------
CSprite::CSprite(CSpriteImage* pImage, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight)
{
	ZeroMemory(this, sizeof(CSprite));
	m_pShader = pImage->m_pShader;
	m_pD3D = pImage->m_pD3D;
	m_vDiffuse = VECTOR4(1, 1, 1, 1);    // -- 2020.1.24
	m_nBlend = 1;
	SetSrc(pImage, srcX, srcY, srcwidth, srcheight, srcwidth, srcheight);
}
//------------------------------------------------------------------------
//
//	スプライトのコンストラクタ	
//
//  CSpriteImage* pImage      スプライトイメージポインタ
//  DWORD         srcX        パターンの左上　Ｘ座標
//  DWORD         srcY        パターンの左上　Ｙ座標
//  DWORD         srcwidth    パターンの幅
//  DWORD         srcheight   パターンの高さ
//  DWORD         destwidth   表示の幅
//  DWORD         destheight  表示の高さ
//
//------------------------------------------------------------------------
CSprite::CSprite(CSpriteImage* pImage, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight)
{
	ZeroMemory(this, sizeof(CSprite));
	m_pShader = pImage->m_pShader;
	m_pD3D = pImage->m_pD3D;
	m_vDiffuse = VECTOR4(1, 1, 1, 1);    // -- 2020.1.24
	m_nBlend = 1;
	SetSrc(pImage, srcX, srcY, srcwidth, srcheight, destwidth, destheight);
}
//------------------------------------------------------------------------
//
//	スプライトのデストラクタ	
//
//------------------------------------------------------------------------
CSprite::~CSprite()
{
	SAFE_RELEASE(m_pVertexBufferSprite);
	SAFE_RELEASE(m_pVertexBufferLine);
	SAFE_RELEASE(m_pVertexBufferRect);
}

//------------------------------------------------------------------------
//                                                         // -- 2017.10.9
//	スプライトのイメージを設定する	
//
//  CSpriteImage* pImage      スプライトイメージポインタ
//
//------------------------------------------------------------------------
void   CSprite::SetImage(CSpriteImage* pImage)
{
	m_pImage = pImage;
}
//------------------------------------------------------------------------
//
//	スプライトのイメージや位置、大きさの情報を設定する	
//
//  CSpriteImage* pImage      スプライトイメージポインタ
//  DWORD         srcX        パターンの左上　Ｘ座標
//  DWORD         srcY        パターンの左上　Ｙ座標
//  DWORD         srcwidth    パターンの幅
//  DWORD         srcheight   パターンの高さ
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CSprite::SetSrc(CSpriteImage* pImage, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight)
{
	m_pImage = pImage;
	return  SetSrc(srcX, srcY, srcwidth, srcheight, srcwidth, srcheight);
}
//------------------------------------------------------------------------
//
//	スプライトのイメージや位置、大きさの情報を設定する	
//
//  CSpriteImage* pImage      スプライトイメージポインタ
//  DWORD         srcX        パターンの左上　Ｘ座標
//  DWORD         srcY        パターンの左上　Ｙ座標
//  DWORD         srcwidth    パターンの幅
//  DWORD         srcheight   パターンの高さ
//  DWORD         destwidth   表示の幅
//  DWORD         destheight  表示の高さ
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CSprite::SetSrc(CSpriteImage* pImage, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight)
{
	m_pImage = pImage;
	return  SetSrc(srcX, srcY, srcwidth, srcheight, destwidth, destheight);
}
//------------------------------------------------------------------------
//
//	スプライトのイメージや位置、大きさの情報を設定する	
//
//  DWORD         srcX        パターンの左上　Ｘ座標
//  DWORD         srcY        パターンの左上　Ｙ座標
//  DWORD         srcwidth    パターンの幅
//  DWORD         srcheight   パターンの高さ
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CSprite::SetSrc(DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight)
{
	return  SetSrc(srcX, srcY, srcwidth, srcheight, srcwidth, srcheight);
}
//------------------------------------------------------------------------
//
//	スプライトのイメージや位置、大きさの情報を設定する	
//
//  DWORD         srcX        パターンの左上　Ｘ座標
//  DWORD         srcY        パターンの左上　Ｙ座標
//  DWORD         srcwidth    パターンの幅
//  DWORD         srcheight   パターンの高さ
//  DWORD         destwidth   表示の幅
//  DWORD         destheight  表示の高さ
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CSprite::SetSrc(DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight)
{
	// スプライト用の板ポリゴンを作成し、バーテックスバッファを作成する
	m_dwSrcX = srcX;
	m_dwSrcY = srcY;
	m_dwSrcWidth = srcwidth;
	m_dwSrcHeight = srcheight;
	m_dwDestWidth = destwidth;
	m_dwDestHeight = destheight;

	//バーテックスバッファー作成
	//気をつけること。z値を１以上にしない。クリップ空間でz=1は最も奥を意味する。したがって描画されない。
	SpriteVertex vertices[] =
	{
		VECTOR3(0,     (float)m_dwDestHeight, 0), VECTOR2((float)m_dwSrcX / m_pImage->m_dwImageWidth,                (float)(m_dwSrcY + m_dwSrcHeight) / m_pImage->m_dwImageHeight),    //頂点1  左下
		VECTOR3(0,                         0, 0), VECTOR2((float)m_dwSrcX / m_pImage->m_dwImageWidth,                (float)m_dwSrcY / m_pImage->m_dwImageHeight),                      //頂点2　左上
		VECTOR3((float)m_dwDestWidth, (float)m_dwDestHeight, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_pImage->m_dwImageWidth, (float)(m_dwSrcY + m_dwSrcHeight) / m_pImage->m_dwImageHeight),      //頂点3　右下
		VECTOR3((float)m_dwDestWidth,                     0, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_pImage->m_dwImageWidth, (float)m_dwSrcY / m_pImage->m_dwImageHeight),                      //頂点4　右上
	};

	// バーテックスバッファがすでに作成済みかどうかチェックする
	if (m_pVertexBufferSprite == NULL)
	{
		// 新規作成する
		D3D11_BUFFER_DESC bd = { 0 };
		//bd.Usage          = D3D11_USAGE_DEFAULT;
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(SpriteVertex) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//bd.CPUAccessFlags = 0;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = { 0 };
		InitData.pSysMem = vertices;
		if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferSprite)))
		{
			MessageBox(0, _T("Sprite.cpp バーテックスバッファー作成失敗"), NULL, MB_OK);
			return E_FAIL;
		}
	}
	else {

		// すでに作成済みのため、バーテックスバッファの書き換えをする
		D3D11_MAPPED_SUBRESOURCE msr = { 0 };
		if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pVertexBufferSprite, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr)))
		{
			memcpy(msr.pData, vertices, sizeof(SpriteVertex) * 4); // 4頂点分コピー
			m_pD3D->m_pDeviceContext->Unmap(m_pVertexBufferSprite, 0);
		}
	}

	return S_OK;
}

//------------------------------------------------------------------------
//
//	スプライトを画面にレンダリング
//
//  CSpriteImage* pImage      スプライトイメージポインタ
//  float         posX        表示位置の左上　Ｘ座標
//  float         posY        表示位置の左上　Ｙ座標
//  DWORD         srcX        パターンの左上　Ｘ座標
//  DWORD         srcY        パターンの左上　Ｙ座標
//  DWORD         srcwidth    パターンの幅
//  DWORD         srcheight   パターンの高さ
//  float         fAlpha      透明度
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void  CSprite::Draw(CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, float fAlpha)
{
	SetSrc(pImage, srcX, srcY, srcwidth, srcheight);
	m_ofX = 0;
	m_ofY = 0;
	m_vDiffuse.w = fAlpha;    // -- 2020.1.24
	Draw(posX, posY);
}
//------------------------------------------------------------------------
//
//	スプライトを画面にレンダリング
//
//  CSpriteImage* pImage      スプライトイメージポインタ
//  float         posX        表示位置の左上　Ｘ座標
//  float         posY        表示位置の左上　Ｙ座標
//  DWORD         srcX        パターンの左上　Ｘ座標
//  DWORD         srcY        パターンの左上　Ｙ座標
//  DWORD         srcwidth    パターンの幅
//  DWORD         srcheight   パターンの高さ
//  DWORD         destwidth   表示の幅
//  DWORD         destheight  表示の高さ
//  float         fAlpha      透明度
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void  CSprite::Draw(CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight, float fAlpha)
{
	SetSrc(pImage, srcX, srcY, srcwidth, srcheight, destwidth, destheight);
	m_ofX = 0;
	m_ofY = 0;
	m_vDiffuse.w = fAlpha;    // -- 2020.1.24
	Draw(posX, posY);
}
//------------------------------------------------------------------------
//
//	スプライトを画面にレンダリング
//
//  CSpriteImage* pImage      スプライトイメージポインタ
//  MATRIX4X4    mWorld      表示位置のワールドマトリックス
//  DWORD         srcX        パターンの左上　Ｘ座標
//  DWORD         srcY        パターンの左上　Ｙ座標
//  DWORD         srcwidth    パターンの幅
//  DWORD         srcheight   パターンの高さ
//  float         fAlpha      透明度
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void  CSprite::Draw(CSpriteImage* pImage, MATRIX4X4 mWorld, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, float fAlpha)
{
	SetSrc(pImage, srcX, srcY, srcwidth, srcheight);
	m_ofX = 0;
	m_ofY = 0;
	m_vDiffuse.w = fAlpha;    // -- 2020.1.24
	Draw(mWorld);
}
//------------------------------------------------------------------------
//
//	スプライトを画面にレンダリング
//
//  CSpriteImage* pImage      スプライトイメージポインタ
//  MATRIX4X4    mWorld      表示位置のワールドマトリックス
//  DWORD         srcX        パターンの左上　Ｘ座標
//  DWORD         srcY        パターンの左上　Ｙ座標
//  DWORD         srcwidth    パターンの幅
//  DWORD         srcheight   パターンの高さ
//  DWORD         destwidth   表示の幅
//  DWORD         destheight  表示の高さ
//  float         fAlpha      透明度
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void  CSprite::Draw(CSpriteImage* pImage, MATRIX4X4 mWorld, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight, float fAlpha)
{
	SetSrc(pImage, srcX, srcY, srcwidth, srcheight, destwidth, destheight);
	m_ofX = 0;
	m_ofY = 0;
	m_vDiffuse.w = fAlpha;    // -- 2020.1.24
	Draw(mWorld);
}
//------------------------------------------------------------------------
//
//	スプライトを画面にレンダリング
//
//  float         posX     表示位置の左上　Ｘ座標
//  float         posY     表示位置の左上　Ｙ座標
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void CSprite::Draw(float posX, float posY)
{
	MATRIX4X4 mWorld;

	mWorld = XMMatrixTranslation(posX, posY, 0.0f);
	Draw(mWorld);
}
//------------------------------------------------------------------------
//
//	スプライトを画面にレンダリング　サブ関数
//
//  MATRIX4X4    mWorld   表示位置のワールドマトリックス
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void CSprite::Draw(MATRIX4X4 mWorld)
{

	//バーテックスバッファーをセット
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferSprite, &stride, &offset);

	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData = { 0 };
	CONSTANT_BUFFER_SPRITE   cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferSprite2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{

		//ワールド行列を渡す
		cb.mW = XMMatrixTranspose(mWorld);

		//ビューポートサイズを渡す（クライアント領域の横と縦）
		cb.ViewPortWidth = m_pD3D->m_dwWindowWidth;
		cb.ViewPortHeight = m_pD3D->m_dwWindowHeight;
		cb.vUVOffset.x = (float)m_ofX / m_pImage->m_dwImageWidth;
		cb.vUVOffset.y = (float)m_ofY / m_pImage->m_dwImageHeight;
		cb.vColor = m_vDiffuse;                                         // -- 2020.1.24
		cb.vMatInfo = VECTOR4(1, 0, 0, 0);  // テクスチャ有り
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferSprite2D, 0);
	}

	//テクスチャーをシェーダーに渡す
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pImage->m_pTexture);

	// ブレンディングを設定    // -- 2020.2.15
	UINT mask = 0xffffffff;
	if (m_nBlend == 2)
	{
		// 2:加算合成のブレンディングを設定
		m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);
	}

	//プリミティブをレンダリング
	m_pD3D->m_pDeviceContext->Draw(4, 0);

	// ブレンディング設定を戻す    // -- 2020.2.15
	if (m_nBlend == 2)
	{
		// 透過色のブレンディングに戻す
		m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);
	}


}
//------------------------------------------------------------------------
//
//	ラインを画面にレンダリング　サブ関数
//
//  （なお、色や透明度はm_vDiffuseを使用していない。引数による直接指定である）
//
//  float StartX     ライン描画　開始Ｘ座標
//  float StartY     ライン描画　開始Ｙ座標
//  float EndX       ライン描画　終了Ｘ座標
//  float EndY       ライン描画　終了Ｙ座標
//  DWORD Width      ラインの太さ（１以上）
//  DWORD colorABGR  文字色　colorABGRは、ABGRの指定。例：白色は(0x00ffffff)   引数はRGB(1,1,1)
//  const float& fAlpha     透明度（省略値は1.0f）
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void CSprite::DrawLine(float StartX, float StartY, float EndX, float EndY, DWORD Width, DWORD colorABGR, float fAlpha)
{

	// 線が画面の範囲内に入っていなかったら描画しない
	if ((StartX < 0 && EndX < 0) || (StartY < 0 && EndY < 0) ||
		(StartX > WINDOW_WIDTH  && EndX > WINDOW_WIDTH) || (StartY > WINDOW_HEIGHT && EndY > WINDOW_HEIGHT))
	{
		return;
	}

	// 線ポリゴンバーテックスバッファー作成
	SpriteVertex vertices[] =
	{
		{ VECTOR3(StartX, StartY, 0), VECTOR2(0,0) },    //頂点1
		{ VECTOR3(EndX,     EndY, 0), VECTOR2(0,0) }     //頂点2
	};

	// バーテックスバッファがすでに作成済みかどうかチェックする
	if (m_pVertexBufferLine == NULL)
	{
		// 新規作成する
		D3D11_BUFFER_DESC bd = { 0 };
		//bd.Usage          = D3D11_USAGE_DEFAULT;
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(SpriteVertex) * 2;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//bd.CPUAccessFlags = 0;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = { 0 };
		InitData.pSysMem = vertices;
		if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferLine)))
		{
			MessageBox(0, _T("Sprite.cpp バーテックスバッファーLINE 作成失敗"), NULL, MB_OK);
			return;
		}
	}
	else {

		// すでに作成済みのため、バーテックスバッファの書き換えをする
		D3D11_MAPPED_SUBRESOURCE msr = { 0 };
		if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pVertexBufferLine, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr)))
		{
			memcpy(msr.pData, vertices, sizeof(SpriteVertex) * 2); // 2頂点分コピー
			m_pD3D->m_pDeviceContext->Unmap(m_pVertexBufferLine, 0);
		}
	}

	VECTOR4 color;
	color.x = ((colorABGR & 0x000000ff) >> 0) / (float)255;  // R
	color.y = ((colorABGR & 0x0000ff00) >> 8) / (float)255;  // G
	color.z = ((colorABGR & 0x00ff0000) >> 16) / (float)255;  // B
	color.w = fAlpha;                                         // A

	//バーテックスバッファーをセット
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferLine, &stride, &offset);

	//プリミティブ・トポロジーをセット
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//テクスチャーなしをシェーダーに渡す
	ID3D11ShaderResourceView* Nothing[1] = { 0 };
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, Nothing);

	//ワールド行列
	MATRIX4X4 mWorld;

	// 直線の法線を求める
	// (線の太さ分だけづらして描画するためにその描画方向を求めるため)
	VECTOR2 vNrm, vDif = VECTOR2(EndX - StartX, EndY - StartY), vLen;
	vNrm.x = vDif.y;
	vNrm.y = vDif.x * -1;

	vLen = XMVector2Length(vNrm);
	vNrm.x = vNrm.x / vLen.x;
	vNrm.y = vNrm.y / vLen.x;

	if (Width < 1) Width = 1;

	// 線の幅だけ描画を繰り返す
	for (DWORD i = 0; i < Width; i++)
	{
		// ワールド行列の初期化
		mWorld = XMMatrixIdentity();

		// 線の太さ分づらして表示するための処理
		if (i % 2 == 0)
		{
			mWorld._41 = vNrm.x*0.8*i*0.5;
			mWorld._42 = vNrm.y*0.8*i*0.5;
		}
		else {
			mWorld._41 = -vNrm.x*0.8*i*0.5;
			mWorld._42 = -vNrm.y*0.8*i*0.5;
		}

		//シェーダーのコンスタントバッファーに各種データを渡す
		D3D11_MAPPED_SUBRESOURCE pData = { 0 };
		CONSTANT_BUFFER_SPRITE     cb;
		if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferSprite2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			//ワールド行列を渡す
			cb.mW = XMMatrixTranspose(mWorld);

			//ビューポートサイズを渡す（クライアント領域の横と縦）
			cb.ViewPortWidth = m_pD3D->m_dwWindowWidth;
			cb.ViewPortHeight = m_pD3D->m_dwWindowHeight;
			cb.vUVOffset.x = 0;
			cb.vUVOffset.y = 0;
			cb.vColor = color;
			cb.vMatInfo = VECTOR4(0, 0, 0, 0);  // テクスチャなし
			memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
			m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferSprite2D, 0);
		}
		//プリミティブをレンダリング
		m_pD3D->m_pDeviceContext->Draw(2, 0);

	}

	//プリミティブ・トポロジーをセット
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


}

//------------------------------------------------------------------------
//                                                         // -- 2018.3.20
//	四角形を画面にレンダリング　サブ関数
//
//  （なお、色や透明度はm_vDiffuseを使用していない。引数による直接指定である）
//
//  float posX       四角形描画　開始Ｘ座標
//  float posY       四角形描画　開始Ｙ座標
//  DWORD width      四角形の幅
//  DWORD height     四角形の高さ
//  DWORD colorABGR  描画色　colorABGRは、ABGRの指定。例：白色は(0x00ffffff)   引数はRGB(1,1,1)
//  float fAlpha     透明度（省略値は1.0f）
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void  CSprite::DrawRect(float posX, float posY, DWORD width, DWORD height, DWORD colorABGR, float fAlpha)
{

	// バーテックスバッファー作成
	SpriteVertex vertices[] =
	{
		{VECTOR3(0, (float)height, 0),             VECTOR2(0,0)},      //頂点1  左下
		{VECTOR3(0, 0, 0),                         VECTOR2(0,0)},      //頂点2　左上
		{VECTOR3((float)width,  (float)height, 0), VECTOR2(0,0)},      //頂点3　右下
		{VECTOR3((float)width, 0, 0),              VECTOR2(0,0)},      //頂点4　右上
	};

	// バーテックスバッファがすでに作成済みかどうかチェックする
	if (m_pVertexBufferRect == NULL)
	{
		// 新規作成する
		D3D11_BUFFER_DESC bd = { 0 };
		//bd.Usage          = D3D11_USAGE_DEFAULT;
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(SpriteVertex) * 4; // 4頂点分
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//bd.CPUAccessFlags = 0;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = { 0 };
		InitData.pSysMem = vertices;
		if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferRect)))
		{
			MessageBox(0, _T("Sprite.cpp バーテックスバッファーRECT 作成失敗"), NULL, MB_OK);
			return;
		}
	}
	else {

		// すでに作成済みのため、バーテックスバッファの書き換えをする
		D3D11_MAPPED_SUBRESOURCE msr = { 0 };
		if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pVertexBufferRect, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr)))
		{
			memcpy(msr.pData, vertices, sizeof(SpriteVertex) * 4); // 4頂点分コピー
			m_pD3D->m_pDeviceContext->Unmap(m_pVertexBufferRect, 0);
		}
	}

	VECTOR4 color;
	color.x = ((colorABGR & 0x000000ff) >> 0) / (float)255;  // R
	color.y = ((colorABGR & 0x0000ff00) >> 8) / (float)255;  // G
	color.z = ((colorABGR & 0x00ff0000) >> 16) / (float)255;  // B
	color.w = fAlpha;                                         // A

	//バーテックスバッファーをセット
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferRect, &stride, &offset);

	//プリミティブ・トポロジーをセット
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//テクスチャーなしをシェーダーに渡す
	ID3D11ShaderResourceView* Nothing[1] = { 0 };
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, Nothing);

	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData = { 0 };
	CONSTANT_BUFFER_SPRITE     cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferSprite2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド行列を渡す
		cb.mW = XMMatrixTranspose(XMMatrixTranslation(posX, posY, 0.0f));

		//ビューポートサイズを渡す（クライアント領域の横と縦）
		cb.ViewPortWidth = m_pD3D->m_dwWindowWidth;
		cb.ViewPortHeight = m_pD3D->m_dwWindowHeight;
		cb.vUVOffset.x = 0;
		cb.vUVOffset.y = 0;
		cb.vColor = color;
		cb.vMatInfo = VECTOR4(0, 0, 0, 0);  // テクスチャなし
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferSprite2D, 0);
	}
	//プリミティブをレンダリング
	m_pD3D->m_pDeviceContext->Draw(4, 0);

}

//------------------------------------------------------------------------
//
//	描画前にシェーダー情報をセット
//
//  引数　　なし
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void CSprite::SetShader()
{

	//使用するシェーダーのセット
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pSprite2D_VS, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pSprite2D_PS, NULL, 0);


	//このコンスタントバッファーをどのシェーダーで使うか
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferSprite2D);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferSprite2D);
	//頂点インプットレイアウトをセット
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pSprite2D_VertexLayout);

	//プリミティブ・トポロジーをセット
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// サンプラーをセット
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);

	// ブレンディングを設定            // -- 2020.2.15
	UINT mask = 0xffffffff;
	// 透過色のブレンディングを設定
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	// Zバッファを無効化
	m_pD3D->SetZBuffer(FALSE);              // -- 2019.4.19

}
//------------------------------------------------------------------------
//
//	描画後にシェーダー情報をリセット
//
//  引数　　なし
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void CSprite::ResetShader()
{

	// Zバッファを有効化
	m_pD3D->SetZBuffer(TRUE);              // -- 2019.4.19


	// 透過色のブレンディングに戻す        // -- 2020.2.15
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);


}


// ========================================================================================
//
// フォントテクスチャーの処理
//
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	フォントテクスチャーのコンストラクタ	
//
//  引数　CShader* pShader
//
//------------------------------------------------------------------------
CFontTexture::CFontTexture(CShader* pShader)
{
	ZeroMemory(this, sizeof(CFontTexture));
	m_pShader = pShader;
	m_pD3D = pShader->m_pD3D;
	m_Idx = 0;
	for (DWORD i = 0; i < TEXT_DATA_MAX; i++)
	{
		m_TextData[i].m_fAlpha = 1.0f;
	}

	/*
	// 自分で追加したフォントを一時的に使えるようにする
	// プログラムが終了するとフォントは削除される
	DESIGNVECTOR design;
	if (AddFontResourceEx(
	TEXT("Fonts/追加フォント名.ttf"),
	FR_PRIVATE,
	&design) == NULL)
	{
	MessageBox(0, _T("Sprite.cpp フォントの追加に失敗しました"), _T(""), MB_OK);
	}
	*/

}
//------------------------------------------------------------------------
//
//	フォントテクスチャーのデストラクタ	
//
//------------------------------------------------------------------------
CFontTexture::~CFontTexture()
{

	/*
	// 追加したフォントを解放する
	DESIGNVECTOR design;
	if (RemoveFontResourceEx(
	TEXT("Fonts/追加フォント名.ttf"),
	FR_PRIVATE,
	&design) == NULL)
	{
	MessageBox(0, _T("Sprite.cpp フォントの解放に失敗しました"), _T(""), MB_OK);
	}
	*/

	for (DWORD i = 0; i < TEXT_DATA_MAX; i++)
	{
		SAFE_DELETE_ARRAY(m_TextData[i].m_szText);
		SAFE_RELEASE(m_TextData[i].m_pResourceView);
		SAFE_RELEASE(m_TextData[i].m_pVertexBufferFont);
	}
}
//------------------------------------------------------------------------
// テキスト情報のリフレッシュ
// 
// 　　表示するテキストの情報は、一行づつTextDataへ保存される
// 　　そのリフレッシュは、メインループの先頭で行う必要がある
//
//  引数　　なし
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void CFontTexture::Refresh()
{
	m_Idx = 0;
}
//------------------------------------------------------------------------
//
//	テキスト表示用のバーテックスバッファー作成。
//	１行分の大きさを確保する
//
//  DWORD dwWidth    表示幅（１行分の大きさ）
//  DWORD dwHeight   表示高さ（１文字の高さ）
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void CFontTexture::CreateVB(DWORD dwWidth, DWORD dwHeight)
{

	// バーテックスバッファー作成時に気をつけること。
	// z値を１以上にしないこと。クリップ空間でz=1は最も奥を意味する。したがって描画されない。
	SpriteVertex vertices[] =
	{
		VECTOR3(0, (float)dwHeight, 0), VECTOR2(0,  1),      //頂点1  左下
		VECTOR3(0,               0, 0), VECTOR2(0,  0),      //頂点2　左上
		VECTOR3((float)dwWidth, (float)dwHeight, 0), VECTOR2(1,  1),      //頂点3　右下
		VECTOR3((float)dwWidth,               0, 0), VECTOR2(1,  0)       //頂点4　右上
	};

	// バーテックスバッファがすでに作成済みかどうかチェックする
	if (m_TextData[m_Idx].m_pVertexBufferFont == NULL)
	{
		// 新規作成する
		D3D11_BUFFER_DESC bd = { 0 };
		//bd.Usage          = D3D11_USAGE_DEFAULT;
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(SpriteVertex) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//bd.CPUAccessFlags = 0;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = { 0 };
		InitData.pSysMem = vertices;
		if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_TextData[m_Idx].m_pVertexBufferFont)))
		{
			MessageBox(0, _T("Sprite.cpp バーテックスバッファー作成失敗"), NULL, MB_OK);
			return;
		}
	}
	else {

		// すでに作成済みのため、バーテックスバッファの書き換えをする
		D3D11_MAPPED_SUBRESOURCE msr = { 0 };
		if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_TextData[m_Idx].m_pVertexBufferFont, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr)))
		{
			memcpy(msr.pData, vertices, sizeof(SpriteVertex) * 4); // 4頂点分コピー
			m_pD3D->m_pDeviceContext->Unmap(m_TextData[m_Idx].m_pVertexBufferFont, 0);
		}
	}

}

//------------------------------------------------------------------------
//
//	テキストの描画
//
//	・座標指定の書き方の場合
//
//  float posX         表示位置　左上　Ｘ座標
//  float posY         表示位置　左上　Ｙ座標
//  TCHAR* szText       表示するテキスト
//  int fontsize       フォントサイズ
//  DWORD colorABGR    文字色　colorABGRは、ABGRの指定。例：白色は(0x00ffffff)
//  float fAlpha       透明度（省略可）
//  TCHAR* szFontName   フォント名（省略可）
//
//	戻り値  なし
//
//------------------------------------------------------------------------ 
void CFontTexture::Draw(float posX, float posY, TCHAR* szText, int fontsize, DWORD colorABGR, float fAlpha, TCHAR* szFontName)
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation(posX, posY, 0.0f);

	Draw(mWorld, szText, fontsize, colorABGR, fAlpha, szFontName);
}

//------------------------------------------------------------------------
//
//	テキストの描画
//
//	・ワールドマトリックスの書き方の場合
//
//  MATRIX4X4 mWorld  表示位置　左上　ワールドマトリックス
//  TCHAR* szText       表示するテキスト
//  int fontsize       フォントサイズ
//  DWORD colorABGR    文字色　colorABGRは、ABGRの指定。例：白色は(0x00ffffff)
//  float fAlpha       透明度（省略可）
//  TCHAR* szFontName   フォント名（省略可）
//
//	戻り値  なし
//
//------------------------------------------------------------------------ 
void CFontTexture::Draw(MATRIX4X4 mWorld, TCHAR* szText, int fontsize, DWORD colorABGR, float fAlpha, TCHAR* szFontName)
{
	// 文字列がないときは描画しない
	if (szText[0] == _T('\0')) return;         // -- 2017.11.22

	//
	// 前回までの「文字列や色、サイズ」が１画面分・発生順にm_TextData配列に入っているので
	// 作成データがそれと同じかどうかチェックする
	//
	// �@　同一の場合は、すでに作成済みのフォントテクスチャーを使用する
	// �A　文字列が異なる場合のみ、フォントテクスチャーの生成を行う
	// 　　（フォントテクスチャーの生成処理は非常に重い処理なので）

	if (m_TextData[m_Idx].m_szText == NULL || _tcscmp(m_TextData[m_Idx].m_szText, szText) != 0 ||
		m_TextData[m_Idx].m_iFontsize != fontsize || m_TextData[m_Idx].m_dwColor != colorABGR || m_TextData[m_Idx].m_fAlpha != fAlpha)  // 作成済みの文字列と同一か？
	{
		// 文字列等に変更のあったとき
		SAFE_DELETE_ARRAY(m_TextData[m_Idx].m_szText);
		m_TextData[m_Idx].m_szText = new TCHAR[_tcslen(szText) + 1];  // TCHARは、１文字が２バイト  // -- 2018.12.28
		_tcscpy_s(m_TextData[m_Idx].m_szText, _tcslen(szText) + 1, szText);    // 文字列の保存                           // -- 2018.12.28
		m_TextData[m_Idx].m_iFontsize = fontsize;		// フォントサイズを保存
		m_TextData[m_Idx].m_dwColor = colorABGR;		// 色を保存
		m_TextData[m_Idx].m_fAlpha = fAlpha;		    // 透明度を保存

		// フォントテクスチャーの作成
		CreateTex(szText, fontsize, colorABGR, szFontName);
	}

	// 出来上がったテクスチャを使って描画を行う

	//バーテックスバッファーをセット
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_TextData[m_Idx].m_pVertexBufferFont, &stride, &offset);

	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData = { 0 };
	CONSTANT_BUFFER_SPRITE     cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferSprite2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{

		//ワールド行列を渡す
		cb.mW = XMMatrixTranspose(mWorld);

		//ビューポートサイズを渡す（クライアント領域の横と縦）
		cb.ViewPortWidth = m_pD3D->m_dwWindowWidth;
		cb.ViewPortHeight = m_pD3D->m_dwWindowHeight;
		cb.vUVOffset.x = 0;
		cb.vUVOffset.y = 0;
		cb.vColor = VECTOR4(1, 1, 1, 1);                    // -- 2020.1.24
		cb.vColor.w = m_TextData[m_Idx].m_fAlpha;
		cb.vMatInfo = VECTOR4(1, 0, 0, 0);  // テクスチャ有り
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferSprite2D, 0);
	}

	//テクスチャーをシェーダーに渡す
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_TextData[m_Idx].m_pResourceView);

	//プリミティブをレンダリング
	m_pD3D->m_pDeviceContext->Draw(4, 0);


	// 保存するTextData配列の添字を１増やす。
	m_Idx++;
	if (m_Idx >= TEXT_DATA_MAX)
	{
		MessageBox(0, _T("Sprite.cpp 作成するフォントテクスチャの最大数を超えました。\nReflesh()が入っていますか。\nまたはTEXT_DATA_MAXを増やしてください。"), _T(""), MB_OK);
		m_Idx--;
	}
}

//------------------------------------------------------------------------
//
//	描画前にシェーダー情報をセット
//
//  引数　　なし
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void CFontTexture::SetShader()
{

	//使用するシェーダーのセット
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pSprite2D_VS, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pSprite2D_PS, NULL, 0);


	//このコンスタントバッファーをどのシェーダーで使うか
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferSprite2D);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferSprite2D);
	//頂点インプットレイアウトをセット
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pSprite2D_VertexLayout);

	//プリミティブ・トポロジーをセット
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// サンプラーをセット
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);

	// 透過色のブレンディングを設定
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	// Zバッファを無効化
	m_pD3D->SetZBuffer(FALSE);              // -- 2019.4.19

}
//------------------------------------------------------------------------
//
//	描画後にシェーダー情報をリセット
//
//  引数　　なし
//
//	戻り値  なし
//
//------------------------------------------------------------------------
void CFontTexture::ResetShader()
{

	// Zバッファを有効化
	m_pD3D->SetZBuffer(TRUE);              // -- 2019.4.19


	// 透過色のブレンディングに戻す
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);


}


//------------------------------------------------------------------------
//
//	フォントテクスチャーの作成
//
//	・GDIからフォントのグラフィックスを得て、テクスチャーを作成する
//	　作成したテクスチャーは、m_TextData[m_Idx]配列に格納する
//
//  TCHAR* text        表示するテキスト
//  int fontsize       フォントサイズ
//  DWORD colorABGR    文字色　colorABGRは、ABGRの指定。例：白色は(0x00ffffff)
//  TCHAR* fontname    フォント名（NULLでも可）
//
//	戻り値  なし
//
//------------------------------------------------------------------------ 
void CFontTexture::CreateTex(TCHAR* text, int fontsize, DWORD colorABGR, TCHAR* fontname)
{

	// フォントの生成
	LOGFONT lf = {
		fontsize,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		//TEXT("ＤＦ勘亭流")
		TEXT("ＭＳ Ｐゴシック")
		//TEXT("ＭＳ ゴシック")
		//TEXT("HGP創英角ﾎﾟｯﾌﾟ体")
		//TEXT("HGP創英角ｺﾞｼｯｸUB")
	};
	if (fontname != NULL) _tcscpy_s(lf.lfFaceName, sizeof(lf.lfFaceName) / sizeof(TCHAR), fontname); // フォント名を設定

	HFONT hFont = CreateFontIndirect(&lf);
	if (!(hFont))
	{
		MessageBox(0, _T("Sprite.cpp テクスチャ用のフォントが作成できません"), _T(""), MB_OK);
	}

	// 文字列グラフィックの生成

	DWORD     dwTextlen = _tcslen(text);    // 文字数（バイト数ではない）  // -- 2018.12.28
	DWORD     dwTextHeight = 0;
	DWORD     dwTextWidth = 0;
	DWORD     dwAllWidth = 0;
	FontData* pFontData = new FontData[dwTextlen];

	// デバイスコンテキスト取得
	// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
	HDC   hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);


	for (DWORD i = 0; i < dwTextlen; i++)
	{
		// 文字コード取得
		UINT code = 0;

#if _UNICODE
		// unicodeの場合、文字コードは単純にワイド文字のUINT変換
		code = (UINT)*(text + i);
#else
		// マルチバイト文字の場合、
		// 1バイト文字のコードの場合は1バイト目のUINT変換、
		// 2バイト文字のコードの場合は[先導コード]*256 + [文字コード]
		BYTE *c = (BYTE*)(text + i);
		if (IsDBCSLeadByte(*c))    // 2バイト文字の先導コードかどうか
		{
			code = (BYTE)c[0] << 8 | (BYTE)c[1];
			i++;
		}
		else {
			code = c[0];
		}
#endif

		// フォントビットマップ取得
		GetTextMetrics(hdc, &(pFontData + i)->TM);
		CONST MAT2 Mat = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };
		DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &(pFontData + i)->GM, 0, NULL, &Mat);  // バッファサイズだけ返してもらう
		if (size == 0) // フォントデータあるか  2017.4.15
		{
			(pFontData + i)->ptr = NULL; // フォントデータが無いとき  2017.4.15
		}
		else {
			(pFontData + i)->ptr = new BYTE[size];
			GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &(pFontData + i)->GM, size, (pFontData + i)->ptr, &Mat);
		}
		if (dwTextWidth < (pFontData + i)->GM.gmCellIncX) dwTextWidth = (pFontData + i)->GM.gmCellIncX;  // １文字の幅
		if (dwTextHeight < (pFontData + i)->TM.tmHeight) dwTextHeight = (pFontData + i)->TM.tmHeight;    // １文字の高さ
		dwAllWidth += (pFontData + i)->GM.gmCellIncX;				// 文字列全体の長さ（ドット長）
	}

	// デバイスコンテキストとフォントハンドルの開放
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	ReleaseDC(NULL, hdc);

	// ----------------------------------------------------
	// 文字列フォントビットマップの大きさでバーテックスバッファー作成
	CreateVB(dwAllWidth, dwTextHeight);

	// ----------------------------------------------------
	// 書き込み可能テクスチャ作成
	// CPUで書き込みができるテクスチャを作成

	ID3D11Texture2D* pTexture2D;    // 2Ｄテクスチャ

	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = dwAllWidth;		// 文字列１行分の大きさ
	desc.Height = dwTextHeight;		// 文字の高さ最大値
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;   // RGBA(255,255,255,255)タイプ
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;          // 動的（書き込みするための必須条件）
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;   // シェーダリソースとして使う
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;   // CPUからアクセスして書き込みOK

	if (FAILED(m_pD3D->m_pDevice->CreateTexture2D(&desc, 0, &pTexture2D)))
	{
		MessageBox(0, _T("Sprite.cpp テクスチャ用のフォントが作成できません"), _T(""), MB_OK);
	}


	D3D11_MAPPED_SUBRESOURCE hMappedResource = { 0 };

	if (FAILED(m_pD3D->m_pDeviceContext->Map(
		pTexture2D,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&hMappedResource)))
	{
		MessageBox(0, _T("Sprite.cpp テクスチャマップ  フォント  失敗"), _T(""), MB_OK);
	}


	// 作成したテクスチャ（ビュー）にフォント情報を書き込む
	BYTE* pBits = (BYTE*)hMappedResource.pData;
	ZeroMemory(pBits, hMappedResource.RowPitch * dwTextHeight);

	DWORD dwAllWidthWk = 0;
	for (DWORD i = 0; i < dwTextlen; i++)
	{

		// フォント情報の書き込み
		// iOfs_x, iOfs_y : 書き出し位置(左上)
		// iBmp_w, iBmp_h : フォントビットマップの幅高
		// Level : α値の段階 (GGO_GRAY4_BITMAPなので17段階)
		int iOfs_x = (pFontData + i)->GM.gmptGlyphOrigin.x;
		int iOfs_y = (pFontData + i)->TM.tmAscent - (pFontData + i)->GM.gmptGlyphOrigin.y;
		int iBmp_w = (pFontData + i)->GM.gmBlackBoxX + (4 - ((pFontData + i)->GM.gmBlackBoxX % 4)) % 4;
		int iBmp_h = (pFontData + i)->GM.gmBlackBoxY;
		int Level = 17;
		int x, y;
		DWORD Alpha, Color;

		for (y = iOfs_y; y < iOfs_y + iBmp_h; y++)
		{
			for (x = iOfs_x; x < iOfs_x + iBmp_w; x++)
			{
				if ((pFontData + i)->ptr == NULL) // フォントデータが無いとき  2017.4.15
				{
					Alpha = 0; // 透明色とする
				}
				else {
					Alpha = (255 * (pFontData + i)->ptr[x - iOfs_x + iBmp_w * (y - iOfs_y)]) / (Level - 1);
				}
				Color = colorABGR | (Alpha << 24);

				memcpy((BYTE*)pBits + hMappedResource.RowPitch * y + 4 * (x + dwAllWidthWk), &Color, sizeof(DWORD));
			}
		}
		dwAllWidthWk += (pFontData + i)->GM.gmCellIncX;	// １文字分進める
	}

	m_pD3D->m_pDeviceContext->Unmap(pTexture2D, 0);


	// テクスチャ情報を取得する
	D3D11_TEXTURE2D_DESC texDesc;
	pTexture2D->GetDesc(&texDesc);

	// ShaderResourceViewの情報を作成する
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

	SAFE_RELEASE(m_TextData[m_Idx].m_pResourceView);	// ２回目以降の作成に対応

	// シェーダーリソースビューの作成
	if (FAILED(m_pD3D->m_pDevice->CreateShaderResourceView(pTexture2D, &srvDesc, &m_TextData[m_Idx].m_pResourceView)))
	{
		MessageBox(0, _T("Sprite.cpp フォント用　ShaderResourceView作成に失敗しました"), NULL, MB_OK);
	}

	// 作成した一時リソースの解放
	SAFE_RELEASE(pTexture2D);

	for (DWORD i = 0; i < dwTextlen; i++)
	{
		SAFE_DELETE_ARRAY((pFontData + i)->ptr);
	}
	SAFE_DELETE_ARRAY(pFontData);

}