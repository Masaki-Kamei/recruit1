//=============================================================================
//
//		エフェクトの処理
//																	Effect.cpp
//=============================================================================

#include "Effect.h"
#include "Playchar.h"
#include "Enemy.h"
#include "Weapon.h"


// ========================================================================================
//
//	エフェクト　メインプロシージャクラス
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	エフェクト　メインプロシージャクラスのコンストラクタ	
//
//------------------------------------------------------------------------
CEffectProc::CEffectProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pParticleProc = new CParticleProc(pGMain);     // パーティクルプロシージャの生成
	m_pProcArray.push_back(m_pParticleProc);   // プロシージャをプロシージャ配列に登録する

	m_pBillProc     = new CBillboardProc(pGMain);     // ビルボードプロシージャの生成
	m_pProcArray.push_back(m_pBillProc);        // プロシージャをプロシージャ配列に登録する


	m_pShockWaveProc = new CBillShockWaveProc(pGMain);     // ビルボードプロシージャの生成
	m_pProcArray.push_back(m_pShockWaveProc);        // プロシージャをプロシージャ配列に登録する

	m_pEnergyDiskProc = new CEnergyDiskProc(pGMain);     // エネルギーディスクプロシージャの生成
	m_pProcArray.push_back(m_pEnergyDiskProc);        // エネルギーディスクをプロシージャ配列に登録する


	m_pLetterEffectProc = new CLetterEffectProc(pGMain);     // 効果字幕プロシージャの生成
	m_pProcArray.push_back(m_pLetterEffectProc);        // 効果字幕をプロシージャ配列に登録する


};


// =====================================================================================================
// 
// 各プロシージャ毎の処理
// 
// =====================================================================================================
//------------------------------------------------------------------------
//
//	パーティクルプロシージャクラスのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CParticleProc::CParticleProc(CGameMain* pGMain) : CBaseProc( pGMain)
{
	const int ParticleNumMax = 30; // 一つのパーティクルオブジェクト中のパーティクルの数

	// パーティクルテクスチャ
	TCHAR szFName[] = _T("Data/Image/particle3.png");

	//テクスチャー読み込み
	m_pTexture = NULL;
	if (FAILED(m_pGMain->m_pD3D->CreateShaderResourceViewFromFile(szFName, &m_pTexture, 3)))
	{
		MessageBox(0, _T("パーティクル　テクスチャーを読み込めません"),_T(""), MB_OK);
		return;
	}
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		// 一つのパーティクルオブジェクト中のパーティクルの数を設定する
		m_pObjArray.push_back(new CParticleObj( m_pGMain, ParticleNumMax));  // m_pObjArrayにオブジェクトを生成する
		((CParticleObj*)(m_pObjArray[i]))->SetTexture( m_pTexture ); // パーティクルテクスチャのセット
	}

};
//------------------------------------------------------------------------
//
//	パーティクルプロシージャクラスのデストラクタ	
//
//------------------------------------------------------------------------
CParticleProc::~CParticleProc()
{
	SAFE_RELEASE(m_pTexture);
};

//------------------------------------------------------------------------
//
//	パーティクルプロシージャクラスの開始	
//
//	・パーティクルオブジェクト配列の中から、空いているパーティクルを探して開始する
//
//  VECTOR3 vEmitPos          パーティクルの発生位置
//  VECTOR3 vNormal           パーティクルの発生面の法線（省略可）
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CParticleProc::Start(VECTOR3 vEmitPos, VECTOR3 vNormal)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vEmitPos, vNormal);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//	パーティクルプロシージャクラスの開始	
//
//	・パーティクルオブジェクト配列の中から、空いているパーティクルを探して開始する
//
//  VECTOR3 vEmitPos          パーティクルの発生位置
//  VECTOR3 vNormal           パーティクルの発生面の法線（省略可）
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CParticleProc::Start(VECTOR3 vEmitPos, DWORD dwPlayerNo, VECTOR3 vNormal)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vEmitPos, dwPlayerNo, vNormal);
			return TRUE;
		}
	}
	return FALSE;
};

// ========================================================================================
//
//	パーティクルオブジェクトクラス
//（ポイントスプライトでパーティクルを実現）
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	パーティクルオブジェクトのコンストラクタ	
//
//  int MaxParticle          パーティクルの数
//
//------------------------------------------------------------------------
CParticleObj::CParticleObj(CGameMain* pGMain, int MaxParticle) : CBaseObj( pGMain)
{
	m_pD3D = m_pGMain->m_pD3D;
	m_pShader = m_pGMain->m_pShader;
	m_fAlpha = 0.0f;
	m_fSize = 0.0f;
	m_MaxParticle = 0;
	m_vEmitPos = VECTOR3(0,0,0);
	m_pPartArray = NULL;
	m_Frame = 0;
	m_FrameEnd = 0;
	m_fSpeed = 0.0f;  // パーティクルの移動スピード
	m_iBarthFrame = 0;     // パーティクルの移動開始までの最大待ち時間（ランダム）

	m_pVertexBuffer = NULL;
	m_pTexture = NULL; //テクスチャー

	//	初期化
	Init(MaxParticle);

	// バーテックスバッファを作成
	SetSrc();
}
//------------------------------------------------------------------------
//
//	パーティクルオブジェクトのデストラクタ	
//
//------------------------------------------------------------------------
CParticleObj::~CParticleObj()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_DELETE_ARRAY(m_pPartArray);
}

//------------------------------------------------------------------------
//	パーティクルオブジェクトの初期化関数
//
//  各種設定値の初期化
//
//  int MaxParticle        パーティクルの数
//
//  戻り値　　　なし
//------------------------------------------------------------------------
void CParticleObj::Init( int MaxParticle )
{
	m_bActive = FALSE;
	m_fAlpha = 1.0f;
	m_fSize = 0.1f;    // パーティクルのサイズ 
	m_MaxParticle = MaxParticle;   // 上記パーティクルプロシージャで指定したパーティクル数
	m_pPartArray = new PART[m_MaxParticle];    // パーティクル配列の生成
	m_FrameEnd = 60;	// パーティクルを表示している時間
	m_fSpeed = 0.015f;  // パーティクルの移動スピード
	m_iBarthFrame = 20;     // パーティクルの移動開始までの最大待ち時間（ランダム）
}

//------------------------------------------------------------------------
//
//	パーティクルオブジェクトのバーティクスバッファ作成とテクスチャの読み込み	
//	（ジオメトリ関連を初期化．ここでは”点”用）	
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CParticleObj::SetSrc()
{
	//バーテックス
	PARTICLE_VERTEX vertices[] =
	{
		VECTOR3(0.0f, 0.0f, 0.0f)
	};

	// ２度目以降に初期化されることの対策
	SAFE_RELEASE(m_pVertexBuffer);

	// バーテックスバッファー作成
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(PARTICLE_VERTEX) * 1;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//------------------------------------------------------------------------
//
//	パーティクルオブジェクトの開始	
//  ・パーティクルを指定位置から発生させる。
//  ・発生方向を法線座標で指定できる。省略すると全方向へ発生する。
//
//  VECTOR3 vEmitPos          パーティクルの発生位置
//  VECTOR3 vNormal           パーティクルの発生面の法線（省略可）
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CParticleObj::Start(VECTOR3 vEmitPos, VECTOR3 vNormal)
{
	if (m_bActive)
	{
		// すでに表示中のとき
		return FALSE;

	}else {
		// 開始処理
		m_bActive = TRUE;
		m_fAlpha  = 0.9f;
		m_vEmitPos = vEmitPos;
		m_Frame = 0;

		// 法線方向を中心としてランダム方向に発生させる
		VECTOR3 vDist, vMin, vMax;
		vDist.x = (1.0f - fabsf(vNormal.x))/2;
		vDist.y = (1.0f - fabsf(vNormal.y))/2;
		vDist.z = (1.0f - fabsf(vNormal.z))/2;

		if (vNormal.x < 0)
		{
			vMin.x = vNormal.x - vDist.x;
			vMax.x = 0.0f + vDist.x;
		}else {
			vMin.x = 0.0f - vDist.x;
			vMax.x = vNormal.x + vDist.x;
		}
		if (vNormal.y < 0)
		{
			vMin.y = vNormal.y - vDist.y;
			vMax.y = 0.0f + vDist.y;
		}else {
			vMin.y = 0.0f - vDist.y;
			vMax.y = vNormal.y + vDist.y;
		}
		if (vNormal.z < 0)
		{
			vMin.z = vNormal.z - vDist.z;
			vMax.z = 0.0f + vDist.z;
		}else {
			vMin.z = 0.0f - vDist.z;
			vMax.z = vNormal.z + vDist.z;
		}

		// パーティクルの開始
		for (int i = 0; i<m_MaxParticle; i++)
		{
			m_pPartArray[i].Pos = m_vEmitPos;
			m_pPartArray[i].Dir.x = ((float)rand() / (float)RAND_MAX) * (vMax.x - vMin.x) + vMin.x;
			m_pPartArray[i].Dir.y = ((float)rand() / (float)RAND_MAX) * (vMax.y - vMin.y) + vMin.y;
			m_pPartArray[i].Dir.z = ((float)rand() / (float)RAND_MAX) * (vMax.z - vMin.z) + vMin.z;
			m_pPartArray[i].Dir = normalize(m_pPartArray[i].Dir);
			m_pPartArray[i].Speed = (5 + ((float)rand() / (float)RAND_MAX)) * m_fSpeed;
			m_pPartArray[i].BirthFrame = (int)(((float)rand() / RAND_MAX) * m_iBarthFrame);
		}
		return TRUE;
	}
}
//------------------------------------------------------------------------
//	パーティクルオブジェクトの開始	
//  ・パーティクルを指定位置から発生させる。
//  ・発生方向を法線座標で指定できる。省略すると全方向へ発生する。
//
//  VECTOR3 vEmitPos          パーティクルの発生位置
//  VECTOR3 vNormal           パーティクルの発生面の法線（省略可）
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CParticleObj::Start(VECTOR3 vEmitPos, DWORD dwPlayerNo,VECTOR3 vNormal)
{
	if (m_bActive)
	{
		// すでに表示中のとき
		return FALSE;

	}
	else {
		// 開始処理
		m_bActive = TRUE;
		m_fAlpha = 0.9f;
		m_vEmitPos = vEmitPos;
		m_Frame = 0;
		m_dwPlayerNo = dwPlayerNo;
		// 法線方向を中心としてランダム方向に発生させる
		VECTOR3 vDist, vMin, vMax;
		vDist.x = (1.0f - fabsf(vNormal.x)) / 2;
		vDist.y = (1.0f - fabsf(vNormal.y)) / 2;
		vDist.z = (1.0f - fabsf(vNormal.z)) / 2;

		if (vNormal.x < 0)
		{
			vMin.x = vNormal.x - vDist.x;
			vMax.x = 0.0f + vDist.x;
		}
		else {
			vMin.x = 0.0f - vDist.x;
			vMax.x = vNormal.x + vDist.x;
		}
		if (vNormal.y < 0)
		{
			vMin.y = vNormal.y - vDist.y;
			vMax.y = 0.0f + vDist.y;
		}
		else {
			vMin.y = 0.0f - vDist.y;
			vMax.y = vNormal.y + vDist.y;
		}
		if (vNormal.z < 0)
		{
			vMin.z = vNormal.z - vDist.z;
			vMax.z = 0.0f + vDist.z;
		}
		else {
			vMin.z = 0.0f - vDist.z;
			vMax.z = vNormal.z + vDist.z;
		}

		// パーティクルの開始
		for (int i = 0; i < m_MaxParticle; i++)
		{
			m_pPartArray[i].Pos = m_vEmitPos;
			m_pPartArray[i].Dir.x = ((float)rand() / (float)RAND_MAX) * (vMax.x - vMin.x) + vMin.x;
			m_pPartArray[i].Dir.y = ((float)rand() / (float)RAND_MAX) * (vMax.y - vMin.y) + vMin.y;
			m_pPartArray[i].Dir.z = ((float)rand() / (float)RAND_MAX) * (vMax.z - vMin.z) + vMin.z;
			m_pPartArray[i].Dir = normalize(m_pPartArray[i].Dir);
			m_pPartArray[i].Speed = (5 + ((float)rand() / (float)RAND_MAX)) * m_fSpeed;
			m_pPartArray[i].BirthFrame = (int)(((float)rand() / RAND_MAX) * m_iBarthFrame);
		}
		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	パーティクルオブジェクトの移動・更新処理	
//  ・パーティクルを更新する
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CParticleObj::Update()
{
	if (m_bActive)
	{
		m_Frame++;	// フレームを進める
		for (int i = 0; i < m_MaxParticle; i++)
		{
			if (m_Frame > m_pPartArray[i].BirthFrame) // 一個のパーティクルが表示開始時間になったとき
			{
				// 移動
				m_pPartArray[i].Pos = m_pPartArray[i].Pos + m_pPartArray[i].Dir * m_pPartArray[i].Speed;

				// 重力
				m_pPartArray[i].Dir = m_pPartArray[i].Dir + VECTOR3(0, -0.049f, 0);
			}
		}

		// レンダリング
		Render();

		if (m_Frame >= m_FrameEnd) // 表示時間終了か
		{
			m_bActive = FALSE;
		}

	}
}

//------------------------------------------------------------------------
//
//	パーティクルオブジェクトを画面にレンダリング	
//  ・パーティクルを表示する
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CParticleObj::Render()
{
	// 表示状態でないとき
	if (!m_bActive)  return;
	MATRIX4X4 mView = m_pGMain->m_mView;
	MATRIX4X4 mProj = m_pGMain->m_mProj;
	VECTOR3	  vEyePt = m_pGMain->m_vEyePt;
	if (m_dwPlayerNo == SECONDPLAYER)
	{
		 mView = m_pGMain->m_mViewSecond;
		 mProj = m_pGMain->m_mProjSecond;
		 vEyePt = m_pGMain->m_vEyePtSecond;

	}
	//使用するシェーダーのセット
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_POINT, NULL, 0);
	m_pD3D->m_pDeviceContext->GSSetShader(m_pShader->m_pEffect3D_GS_POINT, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//バーテックスバッファーをセット
	UINT stride = sizeof(PARTICLE_VERTEX);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// 加算合成色のブレンディングを設定
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//パーティクル１粒を１枚ポイントスプライトとしてm_MaxParticle枚描画
	for (int i = 0; i<m_MaxParticle; i++)
	{
		if (m_FrameEnd < m_Frame + (m_iBarthFrame - m_pPartArray[i].BirthFrame)) continue;

		//個々のパーティクルの、視点を向くワールドトランスフォームを求める
		MATRIX4X4 mWorld = GetLookatMatrix( m_pPartArray[i].Pos, vEyePt);

		RenderParticle(mWorld, mView, mProj);
	}

	// 通常のブレンディングに戻す
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	//ジオメトリシェーダーのリセット
	m_pD3D->m_pDeviceContext->GSSetShader(NULL, NULL, 0);

	return;
}
//------------------------------------------------------------------------
//
//	パーティクルをレンダリングする	
//
//  MATRIX4X4    W    ワールドマトリックス
//  MATRIX4X4    V    ビューマトリックス
//  MATRIX4X4    P    プロジェクションマトリックス
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CParticleObj::RenderParticle(MATRIX4X4 W, MATRIX4X4 V, MATRIX4X4 P)
{

	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド、カメラ、射影行列を渡す
		cb.mW = XMMatrixTranspose(W);
		cb.mV = XMMatrixTranspose(V);
		cb.mP = XMMatrixTranspose(P);

		cb.fAlpha    = m_fAlpha;
		cb.fSize     = m_fSize;          // パーティクルのサイズ 
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}

	//このコンスタントバッファーをどのシェーダーで使うか
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->GSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//頂点インプットレイアウトをセット
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout);
	//プリミティブ・トポロジーをセット
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	//テクスチャーをシェーダーに渡す
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	//プリミティブをレンダリング
	m_pD3D->m_pDeviceContext->Draw(1, 0);

}

// ========================================================================================
//
//	ビルボードのクラス
//
// ========================================================================================

//------------------------------------------------------------------------
//
//	ビルボードプロシージャクラスのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CBillboardProc::CBillboardProc(CGameMain* pGMain) : CBaseProc( pGMain)
{
	// ビルボードテクスチャ
	TCHAR szFName[] = _T("Data/Image/Bom3.png");

	// 半球ビルボードスタティックメッシュの読み込み 
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Item/BillSphere.mesh"));

	m_dwProcID = BILLBOARD_ID;	
	// テクスチャの読み込み
	m_pTexture = NULL;
	if (FAILED(Load(szFName)))
	{
		return;
	}

	for (DWORD i = 0; i < BILLBOARD_MAX; i++)
	{

		m_pObjArray.push_back(new CBillboardObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
		((CBillboardObj*)m_pObjArray[i])->m_pTexture = m_pTexture;            // プロシージャのテクスチャアドレスをセットする
		((CBillboardObj*)m_pObjArray[i])->m_pMesh = m_pMesh;                  // プロシージャのメッシュアドレスをセットする
		((CBillboardObj*)m_pObjArray[i])->m_dwImageHeight = m_dwImageHeight;
		((CBillboardObj*)m_pObjArray[i])->m_dwImageWidth  = m_dwImageWidth;
		((CBillboardObj*)m_pObjArray[i])->SetSrc(12, 12, 0, 0, 64, 64, 4, 3);  //  ビルボード用のバーテックスバッファ作成	
																			 //  float fDestWidth         表示幅
																			 //  float fDestHeight        表示高さ
																			 //  DWORD dwSrcX             スプライトの位置　Ｘ座標
																			 //  DWORD dwSrcY             スプライトの位置　Ｙ座標
																			 //  DWORD dwSrcWidth         スプライトの幅
																			 //  DWORD dwSrcHeight        スプライトの高さ
																			 //  DWORD dwNumX             アニメーションさせるスプライトの数　Ｘ方向
																			 //  DWORD dwNumY             アニメーションさせるスプライトの数　Ｙ方向
		m_pObjArray[i]->SetObjID(m_dwProcID);	

	}
	m_dwBreakNum = 0;
};

//------------------------------------------------------------------------
//
//	ビルボードプロシージャクラスのデストラクタ	
//
//------------------------------------------------------------------------
CBillboardProc::~CBillboardProc()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_pMesh);
};

//------------------------------------------------------------------------
//
//	スプライトイメージの読み込み	
//
//  TCHAR* szFName            ビルボードのテクスチャファイル名
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CBillboardProc::Load(TCHAR* szFName)
{

	//テクスチャー読み込み	（用意するのはリソースビューだけでいい）
	if (FAILED(m_pGMain->m_pD3D->CreateShaderResourceViewFromFile(szFName, &m_pTexture, m_dwImageWidth, m_dwImageHeight, 3)))
	{
		MessageBox(0, _T("ビルボード　テクスチャーを読み込めません"), szFName, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//------------------------------------------------------------------------
//
//	ビルボードプロシージャの開始	
//
//	・ビルボードオブジェクト配列の中から、空いているビルボードを探して開始する
//
//  VECTOR3 vPos          ビルボードの発生位置
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CBillboardProc::Start(VECTOR3 vPos)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//
//	ビルボードプロシージャの開始	
//
//	・ビルボードオブジェクト配列の中から、空いているビルボードを探して開始する
//
//  VECTOR3 vPos          ビルボードの発生位置
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CBillboardProc::Start(VECTOR3 vPos,BOOL bTrigger)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, bTrigger);
			return TRUE;
		}
	}
	return FALSE;
};


//------------------------------------------------------------------------
//
//	ビルボードオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CBillboardObj::CBillboardObj(CGameMain* pGMain) : CBaseObj( pGMain)
{
	m_pD3D = m_pGMain->m_pD3D;
	m_pShader = m_pGMain->m_pShader;

	m_fDestWidth  = 0.0f;
	m_fDestHeight = 0.0f;
	m_dwSrcX = 0;
	m_dwSrcY = 0;
	m_dwSrcWidth = 0;
	m_dwSrcHeight = 0;
	m_vPos = VECTOR3(0,0,0);
	m_vUVOffset = VECTOR2(0,0);
	m_vUVScale = VECTOR2(1,1);             
	m_dwNumX = 0;
	m_dwNumY = 0;
	m_dwFrame = 0;
	m_fAlpha = 0.0f;
	m_dwImageWidth = 0;
	m_dwImageHeight = 0;
	m_pVertexBuffer = NULL;
	m_pTexture = NULL;  //テクスチャー（用意するのはリソースビューだけでいい）

	//バウンディングボックスの生成
	float BBoxSize = 5.5;
	VECTOR3 vMin(-BBoxSize, -BBoxSize, -BBoxSize);
	VECTOR3 vMax(BBoxSize, BBoxSize, BBoxSize);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_bHitTrigger = FALSE;
	m_nAtc = 0;

	//	初期化
	Init();
}

//------------------------------------------------------------------------
//
//	ビルボードオブジェクトのデストラクタ	
//
//------------------------------------------------------------------------
CBillboardObj::~CBillboardObj()
{
	SAFE_RELEASE(m_pVertexBuffer);
}
//------------------------------------------------------------------------
//	ビルボードオブジェクトの初期化関数
//
//  各種設定値の初期化
//
//  引数　　なし
//
//  戻り値　　　なし
//------------------------------------------------------------------------
void CBillboardObj::Init()
{
	m_bActive = FALSE;
	m_fAlpha = 0.9f;
}
//------------------------------------------------------------------------
//
//	ビルボードオブジェクトのバーティクスバッファ作成	
//	（ジオメトリ関連を初期化）	
//
//  float fDestWidth         表示幅
//  float fDestHeight        表示高さ
//  DWORD dwSrcX             スプライトの位置　Ｘ座標
//  DWORD dwSrcY             スプライトの位置　Ｙ座標
//  DWORD dwSrcWidth         スプライトの幅
//  DWORD dwSrcHeight        スプライトの高さ
//  DWORD dwNumX             アニメーションさせるスプライトの数　Ｘ方向
//  DWORD dwNumY             アニメーションさせるスプライトの数　Ｙ方向
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CBillboardObj::SetSrc(float fDestWidth, float fDestHeight, DWORD dwSrcX, DWORD dwSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwNumX, DWORD dwNumY)
{
	// ビルボード用の板ポリゴンを作成し、バーテックスバッファを作成する
	m_fDestWidth   = fDestWidth;
	m_fDestHeight  = fDestHeight;
	m_dwSrcX       = dwSrcX;
	m_dwSrcY       = dwSrcY;
	m_dwSrcWidth   = dwSrcWidth;
	m_dwSrcHeight  = dwSrcHeight;
	m_dwNumX       = dwNumX;
	m_dwNumY       = dwNumY;

	//バーテックスバッファー作成(裏向きの座標で作成)
	BILLBOARD_VERTEX vertices[] =
	{
		VECTOR3(-m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)m_dwSrcY / m_dwImageHeight),                     //頂点1  左上
		VECTOR3(m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)m_dwSrcY / m_dwImageHeight),                        //頂点2　右上   
		VECTOR3(-m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),   //頂点3　左下  
		VECTOR3(m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),      //頂点4　右下
	};

	// ２度目以降に初期化されることの対策
	SAFE_RELEASE(m_pVertexBuffer);

	// バーテックスバッファー作成
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(BILLBOARD_VERTEX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//------------------------------------------------------------------------
//
//	ビルボードオブジェクトの開始	
//
//  VECTOR3   vPos     表示位置（ビルボードの中心点位置を指定）
//
//	戻り値 BOOL
//		TRUE      表示継続
//		FALSE     表示終了
//
//------------------------------------------------------------------------
BOOL CBillboardObj::Start(VECTOR3 vPos)
{
	if (m_bActive) return FALSE;  // すでに開始中

	m_bActive = TRUE;
	m_dwFrame = 0;
	m_vPos = vPos;
	m_bHitTrigger = FALSE;	

	return TRUE;
}

//------------------------------------------------------------------------
//
//	ビルボードオブジェクトの開始	
//
//  VECTOR3   vPos     表示位置（ビルボードの中心点位置を指定）
//
//	戻り値 BOOL
//		TRUE      表示継続
//		FALSE     表示終了
//
//------------------------------------------------------------------------
BOOL CBillboardObj::Start(VECTOR3 vPos,BOOL bTrigger)
{

	if (m_bActive) return FALSE;  // すでに開始中

	m_bActive = TRUE;
	m_dwFrame = 0;
	m_vPos = vPos;
	m_bHitTrigger = FALSE;
	m_bDamage = bTrigger;
	m_nAtc = 0;
	return TRUE;
}


//------------------------------------------------------------------------
//
//	ビルボードオブジェクトの更新	
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CBillboardObj::Update()
{
	const DWORD dwSpeed = 3;   // ビルボードのアニメーションスピード	
	DWORD dwIdx;
	m_dwStatus = NORMAL;
	if (!m_bActive) return;

	m_dwFrame++;
	dwIdx = m_dwFrame / dwSpeed;

	if (dwIdx >= m_dwNumX * m_dwNumY)	// パターンの最後に達したとき
	{
		m_bActive = FALSE;
		return;
	}

	// アニメーションのためのテクスチャオフセットを設定する
	m_vUVOffset.x = (float)(dwIdx % m_dwNumX * GetSrcWidth());   // Ｘ方向の変位
	m_vUVOffset.y = (float)(dwIdx / m_dwNumX * GetSrcHeight());  // Ｙ方向の変位
	//バウンディングボックスの更新
	m_mWorld = XMMatrixTranslation(m_vPos.x, m_vPos.y, m_vPos.z);
	m_pBBox->m_mWorld = m_mWorld;

	//爆風の当たった時の処理	
	if (m_bHitTrigger != TRUE&&m_bDamage!=TRUE) {
		if (m_pGMain->m_pPcProc->GetPcObjPtr()->Hitcheck(this, m_pBBox)) {
			m_bHitTrigger = TRUE;

		}
	}
	if(m_bDamage==TRUE)
	{
		m_nAtc = 2000;
		if (m_pGMain->m_pEnmProc->Hitcheck(this, m_pBBox, m_pGMain->m_pEnmProc->m_pEnmBallProc->GetProcID()))	
		{
			m_pGMain->m_pEffectProc->m_pLetterEffectProc->AddBreakNum(1);	
		}
		m_pGMain->m_pWeaponProc->m_pWeaponWallProc->Hitcheck(this, m_pBBox);
	}
	//Render();// レンダリング
	RenderMesh();// レンダリング(半球ビルボードメッシュ)

}
//------------------------------------------------------------------------
//
//	ビルボードオブジェクトを画面にレンダリング	
//
//	戻り値 BOOL
//		TRUE      表示継続
//		FALSE     表示終了
//
//------------------------------------------------------------------------
BOOL CBillboardObj::Render()
{

	if (!m_bActive) return FALSE;

	//ビルボードの、視点を向くワールドトランスフォームを求める
	MATRIX4X4 mWorld =	GetLookatMatrix( m_vPos, m_pGMain->m_vEyePt);

	//使用するシェーダーのセット
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILL, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//バーテックスバッファーをセット
	UINT stride = sizeof(BILLBOARD_VERTEX);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// 加算合成色のブレンディングを設定
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));

	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド、カメラ、射影行列、テクスチャーオフセットを渡す
		cb.mWVP = XMMatrixTranspose(mWorld * m_pGMain->m_mView * m_pGMain->m_mProj);

		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;		// テクスチャアニメーションのオフセット
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;		// テクスチャアニメーションのオフセット
		cb.vUVScale.x = 1;
		cb.vUVScale.y = 1;
		cb.fAlpha      = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}
	//このコンスタントバッファーをどのシェーダーで使うか
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//頂点インプットレイアウトをセット
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout_BILL);
	//プリミティブ・トポロジーをセット
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//テクスチャーをシェーダーに渡す
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	//プリミティブをレンダリング
	m_pD3D->m_pDeviceContext->Draw(4, 0);

	// 通常のブレンディングに戻す
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	return TRUE;
}

//------------------------------------------------------------------------ 
//
//	ビルボードメッシュを画面にレンダリングする処理
//
// 引数
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
void CBillboardObj::RenderMesh()
{

	//使用するシェーダーの登録	
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILLMESH, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//ビルボードの、視点を向くワールドトランスフォームを求める
	MATRIX4X4 mWorld = GetLookatMatrix(m_vPos, m_pGMain->m_vEyePt);
	// メッシュの大きさに拡大する設定する（元々のメッシュは１ｍ四方の半球）
	MATRIX4X4 mScale = XMMatrixScaling(GetDestWidth(), GetDestHeight(), (GetDestWidth() + GetDestHeight()) / 2);
	mWorld = mScale * mWorld;

	// 加算合成色のブレンディングを設定
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド、カメラ、射影行列、テクスチャーオフセットを渡す
		cb.mWVP = XMMatrixTranspose(mWorld * m_pGMain->m_mView * m_pGMain->m_mProj);

		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;			// テクスチャアニメーションのオフセット
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;			// テクスチャアニメーションのオフセット
		cb.vUVScale.x = (float)GetSrcWidth() / m_dwImageWidth;		// テクスチャアニメーションの1/横回数
		cb.vUVScale.y = (float)GetSrcHeight() / m_dwImageHeight;	// テクスチャアニメーションの1/縦回数

		cb.fAlpha = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}

	//このコンスタントバッファーをどのシェーダーで使うか
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);

	//頂点インプットレイアウトをセット
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pFbxStaticMesh_VertexLayout);

	//プリミティブ・トポロジーをセット
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//テクスチャーサンプラーをシェーダーに渡す
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);

	// メッシュの描画順を決定するm_dwRenderIdxArrayの設定
	m_pMesh->SetRenderIdxArray(mWorld, m_pGMain->m_vEyePt);

	// メッシュの数だけテクスチャー、バーテックスバッファ、インデックスバッファをセットして、レンダリングする
	for (DWORD mi = 0; mi < m_pMesh->m_dwMeshNum; mi++)
	{
		DWORD i = m_pMesh->m_dwRenderIdxArray[mi];

		//テクスチャーをシェーダーに渡す
		m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

		// バーテックスバッファーをセット
		UINT stride = sizeof(StaticVertexNormal);
		UINT offset = 0;
		m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pMesh->m_pMeshArray[i].m_pVertexBuffer, &stride, &offset);

		//インデックスバッファーをセット
		m_pD3D->m_pDeviceContext->IASetIndexBuffer(m_pMesh->m_pMeshArray[i].m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//プリミティブをレンダリング
		// （インデックスの数を指定してレンダリング）
		m_pD3D->m_pDeviceContext->DrawIndexed(m_pMesh->m_pMeshArray[i].m_dwIndicesNum, 0, 0);
	}

	// 通常のブレンディングに戻す
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

}



// ========================================================================================
//
//	ビルボードのクラス
//
// ========================================================================================

//------------------------------------------------------------------------
//
//	衝撃波ビルボードプロシージャクラスのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//
//------------------------------------------------------------------------
CBillShockWaveProc::CBillShockWaveProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ビルボードテクスチャ
	TCHAR szFName[] = _T("Data/Image/Shock_Wave_3_ver1.png");

	// 半球ビルボードスタティックメッシュの読み込み 
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Item/BillSphere.mesh"));

	// テクスチャの読み込み
	m_pTexture = NULL;
	if (FAILED(Load(szFName)))
	{
		return;
	}

	for (DWORD i = 0; i < BILLSHOCKWAVE_MAX; i++)
	{
		m_pObjArray.push_back(new CBillShockWaveObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
		((CBillShockWaveObj*)m_pObjArray[i])->m_pTexture = m_pTexture;            // プロシージャのテクスチャアドレスをセットする
		((CBillShockWaveObj*)m_pObjArray[i])->m_pMesh = m_pMesh;                  // プロシージャのメッシュアドレスをセットする
		((CBillShockWaveObj*)m_pObjArray[i])->m_dwImageHeight = m_dwImageHeight;
		((CBillShockWaveObj*)m_pObjArray[i])->m_dwImageWidth = m_dwImageWidth;
		((CBillShockWaveObj*)m_pObjArray[i])->SetSrc(2, 2, 0, 0, 64, 64, 4, 2);  //  ビルボード用のバーテックスバッファ作成	
																			 //  float fDestWidth         表示幅
																			 //  float fDestHeight        表示高さ
																			 //  DWORD dwSrcX             スプライトの位置　Ｘ座標
																			 //  DWORD dwSrcY             スプライトの位置　Ｙ座標
																			 //  DWORD dwSrcWidth         スプライトの幅
																			 //  DWORD dwSrcHeight        スプライトの高さ
																			 //  DWORD dwNumX             アニメーションさせるスプライトの数　Ｘ方向
																			 //  DWORD dwNumY             アニメーションさせるスプライトの数　Ｙ方向
	}
};

//------------------------------------------------------------------------
//
//	衝撃波ビルボードプロシージャクラスのデストラクタ	
//
//------------------------------------------------------------------------
CBillShockWaveProc::~CBillShockWaveProc()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_pMesh);
};

//------------------------------------------------------------------------
//
//	スプライトイメージの読み込み	
//
//  TCHAR* szFName            衝撃波ビルボードのテクスチャファイル名
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CBillShockWaveProc::Load(TCHAR* szFName)
{

	//テクスチャー読み込み	（用意するのはリソースビューだけでいい）
	if (FAILED(m_pGMain->m_pD3D->CreateShaderResourceViewFromFile(szFName, &m_pTexture, m_dwImageWidth, m_dwImageHeight, 3)))
	{
		MessageBox(0, _T("ビルボード　テクスチャーを読み込めません"), szFName, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//------------------------------------------------------------------------
//
//	衝撃波ビルボードプロシージャの開始	
//
//	・ビルボードオブジェクト配列の中から、空いているビルボードを探して開始する
//
//  VECTOR3 vPos          ビルボードの発生位置
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CBillShockWaveProc::Start(VECTOR3 vPos)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);
			return TRUE;
		}
	}
	return FALSE;
};


//------------------------------------------------------------------------
//	衝撃波ビルボードプロシージャの開始	
//
//	・ビルボードオブジェクト配列の中から、空いているビルボードを探して開始する
//
//  VECTOR3 vPos          ビルボードの発生位置
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CBillShockWaveProc::Start(VECTOR3 vPos, DWORD dwPlayerNo)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, dwPlayerNo);
			return TRUE;
		}
	}
	return FALSE;
};


//------------------------------------------------------------------------
//
//	衝撃波ビルボードオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CBillShockWaveObj::CBillShockWaveObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pD3D = m_pGMain->m_pD3D;
	m_pShader = m_pGMain->m_pShader;

	m_fDestWidth = 0.0f;
	m_fDestHeight = 0.0f;
	m_dwSrcX = 0;
	m_dwSrcY = 0;
	m_dwSrcWidth = 0;
	m_dwSrcHeight = 0;
	m_vPos = VECTOR3(0, 0, 0);
	m_vUVOffset = VECTOR2(0, 0);
	m_vUVScale = VECTOR2(1, 1);           
	m_dwNumX = 0;
	m_dwNumY = 0;
	m_dwFrame = 0;
	m_fAlpha = 0.0f;
	m_dwImageWidth = 0;
	m_dwImageHeight = 0;
	m_pVertexBuffer = NULL;
	m_pTexture = NULL;  //テクスチャー（用意するのはリソースビューだけでいい）

	//	初期化
	Init();
}

//------------------------------------------------------------------------
//
//	衝撃波ビルボードオブジェクトのデストラクタ	
//
//------------------------------------------------------------------------
CBillShockWaveObj::~CBillShockWaveObj()
{
	SAFE_RELEASE(m_pVertexBuffer);
}
//------------------------------------------------------------------------
//	ビルボードオブジェクトの初期化関数
//
//  各種設定値の初期化
//
//  引数　　なし
//
//  戻り値　　　なし
//------------------------------------------------------------------------
void CBillShockWaveObj::Init()
{
	m_bActive = FALSE;
	m_fAlpha = 0.9f;
}
//------------------------------------------------------------------------
//
//	衝撃波ビルボードオブジェクトのバーティクスバッファ作成	
//	（ジオメトリ関連を初期化）	
//
//  float fDestWidth         表示幅
//  float fDestHeight        表示高さ
//  DWORD dwSrcX             スプライトの位置　Ｘ座標
//  DWORD dwSrcY             スプライトの位置　Ｙ座標
//  DWORD dwSrcWidth         スプライトの幅
//  DWORD dwSrcHeight        スプライトの高さ
//  DWORD dwNumX             アニメーションさせるスプライトの数　Ｘ方向
//  DWORD dwNumY             アニメーションさせるスプライトの数　Ｙ方向
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CBillShockWaveObj::SetSrc(float fDestWidth, float fDestHeight, DWORD dwSrcX, DWORD dwSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwNumX, DWORD dwNumY)
{
	// ビルボード用の板ポリゴンを作成し、バーテックスバッファを作成する
	m_fDestWidth = fDestWidth;
	m_fDestHeight = fDestHeight;
	m_dwSrcX = dwSrcX;
	m_dwSrcY = dwSrcY;
	m_dwSrcWidth = dwSrcWidth;
	m_dwSrcHeight = dwSrcHeight;
	m_dwNumX = dwNumX;
	m_dwNumY = dwNumY;

	//バーテックスバッファー作成(裏向きの座標で作成)
	BILLBOARD_VERTEX vertices[] =
	{
		VECTOR3(-m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)m_dwSrcY / m_dwImageHeight),                     //頂点1  左上
		VECTOR3(m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)m_dwSrcY / m_dwImageHeight),                        //頂点2　右上   
		VECTOR3(-m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),   //頂点3　左下   
		VECTOR3(m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),      //頂点4　右下
	};

	// ２度目以降に初期化されることの対策
	SAFE_RELEASE(m_pVertexBuffer);

	// バーテックスバッファー作成
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(BILLBOARD_VERTEX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//------------------------------------------------------------------------
//
//	衝撃波ビルボードオブジェクトの開始	
//
//  VECTOR3   vPos     表示位置（ビルボードの中心点位置を指定）
//
//	戻り値 BOOL
//		TRUE      表示継続
//		FALSE     表示終了
//
//------------------------------------------------------------------------
BOOL CBillShockWaveObj::Start(VECTOR3 vPos)
{
	if (m_bActive) return FALSE;  // すでに開始中

	m_bActive = TRUE;
	m_dwFrame = 0;
	m_vPos = vPos;

	return TRUE;
}
//------------------------------------------------------------------------
//	衝撃波ビルボードオブジェクトの開始	
//
//  VECTOR3   vPos     表示位置（ビルボードの中心点位置を指定）
//
//	戻り値 BOOL
//		TRUE      表示継続
//		FALSE     表示終了
//
//------------------------------------------------------------------------
BOOL CBillShockWaveObj::Start(VECTOR3 vPos, DWORD dwPlayerNo)
{
	if (m_bActive) return FALSE;  // すでに開始中

	m_bActive = TRUE;
	m_dwFrame = 0;
	m_vPos = vPos;
	m_dwPlayerNo = dwPlayerNo;
	return TRUE;
}


//------------------------------------------------------------------------
//
//	衝撃波ビルボードオブジェクトの更新	
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CBillShockWaveObj::Update()
{
	const DWORD dwSpeed = 3;   // ビルボードのアニメーションスピード
	DWORD dwIdx;

	if (!m_bActive) return;

	m_dwFrame++;
	dwIdx = m_dwFrame / dwSpeed;

	if (dwIdx >= m_dwNumX * m_dwNumY)	// パターンの最後に達したとき
	{
		m_bActive = FALSE;
		return;
	}

	// アニメーションのためのテクスチャオフセットを設定する
	m_vUVOffset.x = (float)(dwIdx % m_dwNumX * GetSrcWidth());   // Ｘ方向の変位
	m_vUVOffset.y = (float)(dwIdx / m_dwNumX * GetSrcHeight());  // Ｙ方向の変位

		// 視点との距離計算のためm_mWorldを設定。なお、m_mWorldはレンダリングには使っていない  
	m_mWorld = XMMatrixTranslation(m_vPos.x, m_vPos.y, m_vPos.z);

	// ビルボードのレンダリング  メッシュ種別:24ビルボードメッシュ   優先度:20
	m_pGMain->m_pRenderBufProc->SetRender(24, 0, 20, NULL, this, m_mWorld, VECTOR3(0, 0, 0), m_dwPlayerNo);  //--2022.03.28.8:30

}
//------------------------------------------------------------------------
//
//	衝撃波ビルボードオブジェクトを画面にレンダリング	
//
//	戻り値 BOOL
//		TRUE      表示継続
//		FALSE     表示終了
//
//------------------------------------------------------------------------
BOOL CBillShockWaveObj::Render()
{

	if (!m_bActive) return FALSE;

	//ビルボードの、視点を向くワールドトランスフォームを求める
	MATRIX4X4 mWorld = GetLookatMatrix(m_vPos, m_pGMain->m_vEyePt);

	//使用するシェーダーのセット
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILL, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//バーテックスバッファーをセット
	UINT stride = sizeof(BILLBOARD_VERTEX);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// 加算合成色のブレンディングを設定
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));

	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド、カメラ、射影行列、テクスチャーオフセットを渡す
		cb.mWVP = XMMatrixTranspose(mWorld * m_pGMain->m_mView * m_pGMain->m_mProj);

		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;		// テクスチャアニメーションのオフセット
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;		// テクスチャアニメーションのオフセット
		cb.vUVScale.x = 1;
		cb.vUVScale.y = 1;
		cb.fAlpha = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}
	//このコンスタントバッファーをどのシェーダーで使うか
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//頂点インプットレイアウトをセット
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout_BILL);
	//プリミティブ・トポロジーをセット
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//テクスチャーをシェーダーに渡す
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	//プリミティブをレンダリング
	m_pD3D->m_pDeviceContext->Draw(4, 0);

	// 通常のブレンディングに戻す
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	return TRUE;
}

//------------------------------------------------------------------------  
//
//	衝撃波ビルボードメッシュを画面にレンダリングする処理
//
// 引数
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
void CBillShockWaveObj::RenderMesh()
{
	MATRIX4X4 mView = m_pGMain->m_mView;
	MATRIX4X4 mProj = m_pGMain->m_mProj;
	VECTOR3	  vEyePt = m_pGMain->m_vEyePt;
	if (m_dwPlayerNo == SECONDPLAYER)
	{
		mView = m_pGMain->m_mViewSecond;
		mProj = m_pGMain->m_mProjSecond;
		vEyePt = m_pGMain->m_vEyePtSecond;

	}

	//使用するシェーダーの登録	
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILLMESH, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//ビルボードの、視点を向くワールドトランスフォームを求める
	MATRIX4X4 mWorld = GetLookatMatrix(m_vPos, vEyePt);
	// メッシュの大きさに拡大する設定する（元々のメッシュは１ｍ四方の半球）
	MATRIX4X4 mScale = XMMatrixScaling(GetDestWidth(), GetDestHeight(), (GetDestWidth() + GetDestHeight()) / 2);
	mWorld = mScale * mWorld;

	// 加算合成色のブレンディングを設定
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド、カメラ、射影行列、テクスチャーオフセットを渡す
		cb.mWVP = XMMatrixTranspose(mWorld * mView * mProj);

		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;			// テクスチャアニメーションのオフセット
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;			// テクスチャアニメーションのオフセット
		cb.vUVScale.x = (float)GetSrcWidth() / m_dwImageWidth;		// テクスチャアニメーションの1/横回数
		cb.vUVScale.y = (float)GetSrcHeight() / m_dwImageHeight;	// テクスチャアニメーションの1/縦回数

		cb.fAlpha = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}

	//このコンスタントバッファーをどのシェーダーで使うか
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);

	//頂点インプットレイアウトをセット
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pFbxStaticMesh_VertexLayout);

	//プリミティブ・トポロジーをセット
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//テクスチャーサンプラーをシェーダーに渡す
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);

	// メッシュの描画順を決定するm_dwRenderIdxArrayの設定
	m_pMesh->SetRenderIdxArray(mWorld, vEyePt);

	// メッシュの数だけテクスチャー、バーテックスバッファ、インデックスバッファをセットして、レンダリングする
	for (DWORD mi = 0; mi < m_pMesh->m_dwMeshNum; mi++)
	{
		DWORD i = m_pMesh->m_dwRenderIdxArray[mi];

		//テクスチャーをシェーダーに渡す
		m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

		// バーテックスバッファーをセット
		UINT stride = sizeof(StaticVertexNormal);
		UINT offset = 0;
		m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pMesh->m_pMeshArray[i].m_pVertexBuffer, &stride, &offset);

		//インデックスバッファーをセット
		m_pD3D->m_pDeviceContext->IASetIndexBuffer(m_pMesh->m_pMeshArray[i].m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//プリミティブをレンダリング
		// （インデックスの数を指定してレンダリング）
		m_pD3D->m_pDeviceContext->DrawIndexed(m_pMesh->m_pMeshArray[i].m_dwIndicesNum, 0, 0);
	}

	// 通常のブレンディングに戻す
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

}

//------------------------------------------------------------------------
//
//	効果字幕プロシージャクラスのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CLetterEffectProc::CLetterEffectProc(CGameMain* pGMain) : CBaseProc(pGMain)
{

	//テクスチャー読み込み
	m_pTexture = NULL;
	for (int i = 0; i < LETTEREFFECT_MAX; i++)
	{
		// 一つの効果字幕オブジェクト中の効果字幕の数を設定する
		m_pObjArray.push_back(new CLetterEffectObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}

};
//------------------------------------------------------------------------
//
//	効果字幕プロシージャクラスのデストラクタ	
//
//------------------------------------------------------------------------
CLetterEffectProc::~CLetterEffectProc()
{
	SAFE_RELEASE(m_pTexture);
};

//------------------------------------------------------------------------
//
//	効果字幕プロシージャクラスの開始	
//
//	・効果字幕オブジェクト配列の中から、空いている効果字幕を探して開始する
//
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		CBaseObj* pOtherOb       オブジェクト
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		DWORD fFreamEnd			 表示時間
//		DWORD dNo				 字幕効果の種類
//		float fAlpha;            透明度(省略可)
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CLetterEffectProc::Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CLetterEffectObj*)m_pObjArray[i])->Start(pSprite, pImage, pOtherObj, vPos,vSize,vSrcPos,vSrcSize,fFreamEnd, dNo,fAlpha);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//
//	効果字幕プロシージャクラスの開始	
//
//	・効果字幕オブジェクト配列の中から、空いている効果字幕を探して開始する
//
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		VECTOR3 vPos             表示位置
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		DWORD fFreamEnd			 表示時間
//		DWORD dNo				 字幕効果の種類
//		float fAlpha;            透明度(省略可)
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CLetterEffectProc::Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CLetterEffectObj*)m_pObjArray[i])->Start(pSprite, pImage, vPos, vSize, vSrcPos, vSrcSize,fFreamEnd, dNo, fAlpha);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//
//	効果字幕プロシージャクラスの開始	
//
//	・効果字幕オブジェクト配列の中から、空いている効果字幕を探して開始する
//
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		CBaseObj* pOtherOb       オブジェクト
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		DWORD fFreamEnd			 表示時間
//		DWORD dNo				 字幕効果の種類
//		float fAlpha;            透明度(省略可)
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CLetterEffectProc::Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, DWORD dNo, float fAlpha)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CLetterEffectObj*)m_pObjArray[i])->Start(pSprite, pImage, pOtherObj, vPos, vSize, vSrcPos, vSrcSize, fFreamEnd, dNo, fAlpha, dwPlayerNo);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//
//	効果字幕プロシージャクラスの開始	
//
//	・効果字幕オブジェクト配列の中から、空いている効果字幕を探して開始する
//
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		VECTOR3 vPos             表示位置
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		DWORD fFreamEnd			 表示時間
//		DWORD dNo				 字幕効果の種類
//		float fAlpha;            透明度(省略可)
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CLetterEffectProc::Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, DWORD dNo, float fAlpha)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CLetterEffectObj*)m_pObjArray[i])->Start(pSprite, pImage, vPos, vSize, vSrcPos, vSrcSize, fFreamEnd, dNo, dwPlayerNo,fAlpha);
			return TRUE;
		}
	}
	return FALSE;
};

// ========================================================================================
//
//	効果字幕オブジェクトクラス
//（ポイントスプライトで効果字幕を実現）
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	効果字幕オブジェクトのコンストラクタ	
//
//  int MaxParticle          効果字幕の数
//
//------------------------------------------------------------------------
CLetterEffectObj::CLetterEffectObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_fAlpha = 0.0f;
	m_fSize = 0.0f;
	m_vEmitPos = VECTOR3(0, 0, 0);
	m_Frame = 0;
	m_FrameEnd = 0;

	Init();

	

}
//------------------------------------------------------------------------
//
//	効果字幕オブジェクトのデストラクタ	
//
//------------------------------------------------------------------------
CLetterEffectObj::~CLetterEffectObj()
{

}

//------------------------------------------------------------------------
//
//	効果字幕オブジェクトの初期化関数
//
//  各種設定値の初期化
//
//  int MaxParticle        効果字幕の数
//
//  戻り値　　　なし
//------------------------------------------------------------------------
void CLetterEffectObj::Init()
{
	m_bActive = FALSE;
	m_FrameEnd = 0;	// 効果字幕を表示している時間
	m_fAlpha = 1.0f;
	fNum1 = 0;
	bTrigger = FALSE;
	dLetterEffectNo = 0;
	vVarNum1 = VECTOR2(0,0);
	bTracTrigger = FALSE;

}

//------------------------------------------------------------------------
//
//	効果字幕オブジェクトの開始	
//  ・効果字幕を指定位置から発生させる。
//  ・発生方向を法線座標で指定できる。省略すると全方向へ発生する。
//
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		CBaseObj* pOtherOb       オブジェクト
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		DWORD fFreamEnd			 表示時間
//		DWORD dNo				 字幕効果の種類
//		float fAlpha;            透明度(省略可)
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//
//------------------------------------------------------------------------
BOOL CLetterEffectObj::Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos,VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha)
{
	if (m_bActive)
	{
		// すでに表示中のとき
		return FALSE;

	}
	else {
		// 開始処理
		m_bActive = TRUE;

		//引数を変数に代入
		m_FrameEnd = fFreamEnd;
		m_pSprite = pSprite;
		m_pImageForegrd = pImage;
		vPosGain = vPos;
		vEffObj = pOtherObj;
		vEffSize = vSize;
		vEffSrcPos = vSrcPos;
		vEffSrcSize = vSrcSize;
		fEffAlpha = fAlpha;
		m_Frame = 0;
		fNum1 = Random(-6,6);
		fNum1 = fNum1 / 10;
		dLetterEffectNo = dNo;
		bTrigger = FALSE;
		vVarNum1 = VECTOR2(0, 0);
		bTracTrigger = TRUE;
		dwPhase = 0;

		if(m_FrameEnd<0)	bNonFream = TRUE;
		else
		{
			bNonFream = FALSE;
		}
		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	効果字幕オブジェクトの開始	
//  ・効果字幕を指定位置から発生させる。
//  ・発生方向を法線座標で指定できる。省略すると全方向へ発生する。
//
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		VECTOR3 vPos             表示位置
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		DWORD fFreamEnd			 表示時間
//		DWORD dNo				 字幕効果の種類
//		float fAlpha;            透明度(省略可)
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//
//------------------------------------------------------------------------
BOOL CLetterEffectObj::Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha)
{
	if (m_bActive)
	{
		// すでに表示中のとき
		return FALSE;

	}
	else {
		// 開始処理
		m_bActive = TRUE;

		//引数を変数に代入
		m_FrameEnd = fFreamEnd;
		m_pSprite = pSprite;
		m_pImageForegrd = pImage;
		vEffPos = vPos;
		vEffSize = vSize;
		vEffSrcPos = vSrcPos;
		vEffSrcSize = vSrcSize;
		fEffAlpha = fAlpha;
		m_Frame = 0;
		fNum1 = 0;
		dLetterEffectNo = dNo;
		bTrigger = FALSE;
		vVarNum1 = VECTOR2(0, 0);
		bTracTrigger = FALSE;
		bNonFream = FALSE;
		dwPhase = 0;

		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	効果字幕オブジェクトの開始	
//  ・効果字幕を指定位置から発生させる。
//  ・発生方向を法線座標で指定できる。省略すると全方向へ発生する。
//
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		CBaseObj* pOtherOb       オブジェクト
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		DWORD fFreamEnd			 表示時間
//		DWORD dNo				 字幕効果の種類
//		float fAlpha;            透明度(省略可)
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//
//------------------------------------------------------------------------
BOOL CLetterEffectObj::Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha, DWORD dwPlayerNo)
{
	if (m_bActive)
	{
		// すでに表示中のとき
		return FALSE;

	}
	else {
		// 開始処理
		m_bActive = TRUE;
		//引数を変数に代入
		m_dwPlayerNo = dwPlayerNo;
		m_FrameEnd = fFreamEnd;
		m_pSprite = pSprite;
		m_pImageForegrd = pImage;
		vPosGain = vPos;
		vEffObj = pOtherObj;
		vEffSize = vSize;
		vEffSrcPos = vSrcPos;
		vEffSrcSize = vSrcSize;
		fEffAlpha = fAlpha;
		m_Frame = 0;
		fNum1 = Random(-6, 6);
		fNum1 = fNum1 / 10;
		dLetterEffectNo = dNo;
		bTrigger = FALSE;
		vVarNum1 = VECTOR2(0, 0);
		bTracTrigger = TRUE;
		dwPhase = 0;

		if (m_FrameEnd < 0)	bNonFream = TRUE;
		else
		{
			bNonFream = FALSE;
		}
		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	効果字幕オブジェクトの開始	
//  ・効果字幕を指定位置から発生させる。
//  ・発生方向を法線座標で指定できる。省略すると全方向へ発生する。
//
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		VECTOR3 vPos             表示位置
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		DWORD fFreamEnd			 表示時間
//		DWORD dNo				 字幕効果の種類
//		float fAlpha;            透明度(省略可)
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//
//------------------------------------------------------------------------
BOOL CLetterEffectObj::Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, DWORD dwPlayerNo, float fAlpha)
{
	if (m_bActive)
	{
		// すでに表示中のとき
		return FALSE;

	}
	else {
		// 開始処理
		m_bActive = TRUE;
		//引数を変数に代入
		m_dwPlayerNo = dwPlayerNo;
		m_FrameEnd = fFreamEnd;
		m_pSprite = pSprite;
		m_pImageForegrd = pImage;
		vEffPos = vPos;
		vEffSize = vSize;
		vEffSrcPos = vSrcPos;
		vEffSrcSize = vSrcSize;
		fEffAlpha = fAlpha;
		m_Frame = 0;
		fNum1 = 0;
		dLetterEffectNo = dNo;
		bTrigger = FALSE;
		vVarNum1 = VECTOR2(0, 0);
		bTracTrigger = FALSE;
		bNonFream = FALSE;
		dwPhase = 0;

		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	効果字幕オブジェクトの移動・更新処理	
//  ・効果字幕を更新する
//
//	戻り値 なし
//
//
//------------------------------------------------------------------------
void CLetterEffectObj::Update()
{
	DWORD dwPosUp = 0.5;
	DWORD dwFreamInterval = 3;

	if (m_bActive)
	{
		if (bTracTrigger == TRUE)
		{
			VECTOR3 vPos = GetPositionVector(vEffObj->GetWorld());
			vPos.y += dwPosUp;
			MATRIX4X4 mPos = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
			VECTOR3 vEyePt = m_pGMain->m_vEyePt;
			if(m_dwPlayerNo==SECONDPLAYER)	vEyePt = m_pGMain->m_vEyePtSecond;	
			MATRIX4X4 mImageWorld = TurnTarget(mPos, XMMatrixTranslation(vEyePt.x, vEyePt.y, vEyePt.z));
			mImageWorld = XMMatrixTranslation(vPosGain.x, vPosGain.y, vPosGain.z)* mImageWorld;
			vPos = GetPositionVector(mImageWorld);
			vEffPos = vPos;
		}
		switch (dLetterEffectNo)
		{
		case LENO_SHAKEBESIDETYPE:		//効果字幕横触れ
			LetterShakeBesideType();

			break;

		case LENO_SHAKEVERTICALTYPE:	//効果字幕縦触れ
			LetterShakeVerticalType();

			break;


		case LENO_EXPANISIONTYPE:		//効果字幕拡大
			LetterExpansionType();
			break;

		case LENO_RIZETYPE:				//効果字幕上昇
			LetterRizeType();
			break;

		case LENO_SHAKERANDOMTYPE:		//効果字幕ランダム揺れ
			LetterShakeRandomType();
			break;

		default:
			break;
		}
		// レンダリング
		Render();
		// フレームを進める
		m_Frame++;

		if (bNonFream != TRUE)
		{

			if (m_Frame >= (m_FrameEnd / dwFreamInterval)) {
				float RemFream = m_FrameEnd - (m_FrameEnd / dwFreamInterval);

				fEffAlpha = fEffAlpha - (fEffAlpha / RemFream);
			}
			if (m_Frame >= m_FrameEnd) // 表示時間終了か
			{
				m_bActive = FALSE;
			}
		}
		else if (vEffObj->GetActive() == FALSE)  m_bActive = FALSE;

	}
}

//------------------------------------------------------------------------
//
//	効果字幕オブジェクトを画面にレンダリング	
//  ・効果字幕を表示する
//
//	戻り値 なし
//
//
//------------------------------------------------------------------------
void CLetterEffectObj::Render()
{
	// 表示状態でないとき
	if (!m_bActive)  return;

	m_pGMain->m_pRenderBufProc->SetDraw3DSprite(m_pSprite, m_pImageForegrd, vEffPos, vEffSize, vEffSrcPos, vEffSrcSize, m_dwPlayerNo, fEffAlpha);	

	return;
}

//---------------------------------------------------------------------------
//
//		効果字幕横揺れ
//
//
//---------------------------------------------------------------------------
void CLetterEffectObj::LetterShakeBesideType()
{
	if (!m_bActive)  return;
	int MovePos = 0.03;
	MATRIX4X4	mWorld;
	//エフェクトの座標を取得
	mWorld = XMMatrixTranslation(vEffPos.x, vEffPos.y, vEffPos.z);
	//カメラの座標を取得
	VECTOR3 vEyePt = m_pGMain->m_vEyePt;
	if (m_dwPlayerNo == SECONDPLAYER)	vEyePt = m_pGMain->m_vEyePtSecond;

	VECTOR3 vPos= vEffPos;
	if (bTrigger!=TRUE) {	//右に移動
		fNum1+= MovePos;
		if (fNum1 >= (MovePos*2)) {
			fNum1 = (MovePos * 2);
			bTrigger = TRUE;
		}
	}
	else {					//左に移動
		fNum1 -= MovePos;
		if (fNum1 <= (-MovePos * 2)) {
			fNum1 = (-MovePos * 2);
			bTrigger = FALSE;
		}
	}
	
	//常にカメラを向く
	mWorld = XMMatrixTranslation (fNum1, 0,0)*TurnTarget(mWorld, XMMatrixTranslation(vEyePt.x, vEyePt.y, vEyePt.z));
	//位置を代入
	vEffPos = GetPositionVector(mWorld);
}

//---------------------------------------------------------------------------
//
//		効果字幕縦揺れ
//
//
//---------------------------------------------------------------------------
void CLetterEffectObj::LetterShakeVerticalType()
{
	if (!m_bActive)  return;

	int			MovePos = 0.03;
	MATRIX4X4	mWorld;

	//エフェクトの座標を取得
	mWorld = XMMatrixTranslation(vEffPos.x, vEffPos.y, vEffPos.z);
	//カメラの座標を取得
	VECTOR3 vEyePt = m_pGMain->m_vEyePt;
	if (m_dwPlayerNo == SECONDPLAYER)	vEyePt = m_pGMain->m_vEyePtSecond;	

	VECTOR3 vPos = vEffPos;
	if (bTrigger != TRUE) {		//上に移動
		fNum1 += MovePos;
		if (fNum1 >= (MovePos * 2)) {
			fNum1 = (MovePos * 2);
			bTrigger = TRUE;
		}
	}
	else {								//下に移動
		fNum1 -= MovePos;
		if (fNum1 <= (-MovePos * 2)) {
			fNum1 = (-MovePos * 2);
			bTrigger = FALSE;
		}
	}
	//常にカメラを向く
	mWorld = XMMatrixTranslation(0, fNum1, 0)*TurnTarget(mWorld, XMMatrixTranslation(vEyePt.x, vEyePt.y, vEyePt.z));
	//位置を代入
	vEffPos = GetPositionVector(mWorld);
}



//---------------------------------------------------------------------------
//
//		効果字幕拡大
//
//
//---------------------------------------------------------------------------
void CLetterEffectObj::LetterExpansionType()
{
	if (!m_bActive)  return;

	//字幕がエフェクト中ではなければサイズを取得
	if(bTrigger!=TRUE)vVarNum1 = vEffSize;

	VECTOR2 vSize(0, 0);
	VECTOR2 vMaxSize = vVarNum1;

	//フレームに合わせて拡大量を合わせる
	float ExpNumX = (vMaxSize.x/ (m_FrameEnd*0.1));
	float ExpNumY = (vMaxSize.y / (m_FrameEnd*0.1));

	//サイズ拡大
	vSize.x = ExpNumX * m_Frame;
	if(vSize.x>= vMaxSize.x)	vSize.x = vMaxSize.x;
	vSize.y = ExpNumY * m_Frame;
	if (vSize.y >= vMaxSize.y)	vSize.y = vMaxSize.y;
	//サイズを代入
	vEffSize = vSize;
	//字幕がエフェクト中にする
	bTrigger = TRUE;
}

//---------------------------------------------------------------------------
//
//		効果字幕上昇
//
//
//---------------------------------------------------------------------------
void CLetterEffectObj::LetterRizeType()
{
	if (!m_bActive)  return;

	//上昇
	fNum1 += 0.0001;
	vEffPos.y += fNum1;

}

//---------------------------------------------------------------------------
//
//		効果字幕ランダム揺れ
//
//
//---------------------------------------------------------------------------
void CLetterEffectObj::LetterShakeRandomType()
{
	if (!m_bActive)  return;

	MATRIX4X4	mWorld;
	//エフェクトの座標を取得
	mWorld = XMMatrixTranslation(vEffPos.x, vEffPos.y, vEffPos.z);
	//カメラの座標を取得
	VECTOR3 vEyePt = m_pGMain->m_vEyePt;
	if (m_dwPlayerNo == SECONDPLAYER)	vEyePt = m_pGMain->m_vEyePtSecond;

	VECTOR3		vPos = vEffPos;
	MATRIX4X4	mWorldRot = GetRotateMatrix(mWorld);
	MATRIX4X4	mWorldPos = GetPositionMatrix(mWorld);
	FLOAT		fMoveDist = 0.03;

	switch (dwPhase)
	{
	case 0:	//移動角度を取得

		fNum1 = Random(0, 360);
		if (fNum1 >= 180) fNum1 -= 360;
		if (fNum1 <= -180) fNum1 += 360;
		dwPhase++;
		break;

	case 1:	//移動

		mWorld = mWorldPos;
		mWorld = XMMatrixTranslation(fMoveDist, 0, 0)*XMMatrixRotationZ(XMConvertToRadians(fNum1))*mWorld;
		if (m_Frame % 2 == 0)
		{
			dwPhase++;
		}
		break;

	case 2:	//同じ距離逆に移動

		mWorld = mWorldPos;
		mWorld = XMMatrixTranslation(-fMoveDist, 0, 0)*XMMatrixRotationZ(XMConvertToRadians(fNum1))*mWorld;
		if (m_Frame % 2 == 0)
		{
			dwPhase--;
			fNum1 = Random(0, 360);
			if (fNum1 >= 180) fNum1 -= 360;
			if (fNum1 <= -180) fNum1 += 360;

		}


		break;

	}

	mWorld = TurnTarget(mWorld, XMMatrixTranslation(vEyePt.x, vEyePt.y, vEyePt.z));


	vEffPos = GetPositionVector(mWorld);
}


//------------------------------------------------------------------------
//
//	エネルギーディスクプロシージャクラスのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEnergyDiskProc::CEnergyDiskProc(CGameMain* pGMain) : CBaseProc(pGMain)
{

	m_pImageForegrd= new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Energy_Disk_2.png")); // スキル欄選択中イメージのロード	

	for (int i = 0; i < BILLENERGYDISK_MAX; i++)
	{
		// 一つのエネルギーディスクオブジェクト中のエネルギーディスクの数を設定する
		m_pObjArray.push_back(new CEnergyDiskObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
	}

};
//------------------------------------------------------------------------
//
//	エネルギーディスクプロシージャクラスのデストラクタ	
//
//------------------------------------------------------------------------
CEnergyDiskProc::~CEnergyDiskProc()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_pImageForegrd);
};

//------------------------------------------------------------------------
//
//	エネルギーディスクプロシージャクラスの開始	
//
//	・エネルギーディスクオブジェクト配列の中から、空いているエネルギーディスクを探して開始する
//
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		VECTOR3 vPos			 表示位置
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		DWORD fFreamEnd			 表示時間
//		DWORD dNo				 字幕効果の種類
//		float fAlpha;            透明度(省略可)
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CEnergyDiskProc::Start(CSprite* pSprite, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, float fAlpha)
{


	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CEnergyDiskObj*)m_pObjArray[i])->Start(pSprite,m_pImageForegrd, pOtherObj, vPos, vSize, vSrcPos, vSrcSize, fFreamEnd, fAlpha);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//
//	エネルギーディスクプロシージャクラスの開始	
//
//	・エネルギーディスクオブジェクト配列の中から、空いているエネルギーディスクを探して開始する
//
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		VECTOR3 vPos			 表示位置
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		DWORD fFreamEnd			 表示時間
//		DWORD dNo				 字幕効果の種類
//		float fAlpha;            透明度(省略可)
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//------------------------------------------------------------------------
BOOL CEnergyDiskProc::Start(CSprite* pSprite, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, float fAlpha)
{


	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CEnergyDiskObj*)m_pObjArray[i])->Start(pSprite, m_pImageForegrd, pOtherObj, vPos, vSize, vSrcPos, vSrcSize, fFreamEnd, dwPlayerNo, fAlpha);
			return TRUE;
		}
	}
	return FALSE;
};

// ========================================================================================
//
//	エネルギーディスクオブジェクトクラス
//（ポイントスプライトでエネルギーディスクを実現）
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	エネルギーディスクオブジェクトのコンストラクタ	
//
//  int MaxParticle          エネルギーディスクの数
//
//------------------------------------------------------------------------
CEnergyDiskObj::CEnergyDiskObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_fAlpha = 0.0f;
	m_fSize = 0.0f;
	m_vEmitPos = VECTOR3(0, 0, 0);
	m_Frame = 0;
	m_FrameEnd = 0;

	Init();



}
//------------------------------------------------------------------------
//
//	エネルギーディスクオブジェクトのデストラクタ	
//
//------------------------------------------------------------------------
CEnergyDiskObj::~CEnergyDiskObj()
{
}

//------------------------------------------------------------------------
//
//	エネルギーディスクオブジェクトの初期化関数
//
//  各種設定値の初期化
//
//  int MaxParticle        エネルギーディスクの数
//
//  戻り値　　　なし
//------------------------------------------------------------------------
void CEnergyDiskObj::Init()
{
	m_bActive = FALSE;
	m_FrameEnd = 0;	// エネルギーディスクを表示している時間
	m_fAlpha = 1.0f;
	fNum1 = 0;
	bTrigger = FALSE;
	vVarNum1 = VECTOR2(0, 0);
	bTracTrigger = FALSE;
	bMaxSizeX = FALSE;
	bMaxSizeY = FALSE;
	nWrapFrame = 0;
}

//------------------------------------------------------------------------
//
//	エネルギーディスクオブジェクトの開始	
//  ・エネルギーディスクを指定位置から発生させる。
//  ・発生方向を法線座標で指定できる。省略すると全方向へ発生する。
//
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		CBaseObj* pOtherOb       オブジェクト
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		DWORD fFreamEnd			 表示時間
//		DWORD dNo				 字幕効果の種類
//		float fAlpha;            透明度(省略可)
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//
//------------------------------------------------------------------------
BOOL CEnergyDiskObj::Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd,  float fAlpha)
{
	if (m_bActive)
	{
		// すでに表示中のとき
		return FALSE;

	}
	else {
		// 開始処理
		m_bActive = TRUE;
		m_FrameEnd = fFreamEnd;
		m_pSprite = pSprite;
		m_pImageForegrd = pImage;
		vPosGain = vPos;
		vEffObj = pOtherObj;
		vEffSize = vSize;
		vEffSrcPos = vSrcPos;
		vEffSrcSize = vSrcSize;
		fEffAlpha = fAlpha;
		m_Frame = 0;
		fNum1 = Random(-6, 6);
		fNum1 = fNum1 / 10;
		bTrigger = FALSE;
		vVarNum1 = VECTOR2(0, 0);
		bMaxSizeX = FALSE;
		bMaxSizeY = FALSE;
		nWrapFrame = 0;

		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	エネルギーディスクオブジェクトの開始	
//  ・エネルギーディスクを指定位置から発生させる。
//  ・発生方向を法線座標で指定できる。省略すると全方向へ発生する。
//
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		CBaseObj* pOtherOb       オブジェクト
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		DWORD fFreamEnd			 表示時間
//		DWORD dNo				 字幕効果の種類
//		float fAlpha;            透明度(省略可)
//
//	戻り値 BOOL
//		TRUE	= 正常
//		FALSE	= 異常
//
//
//------------------------------------------------------------------------
BOOL CEnergyDiskObj::Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, float fAlpha)
{
	if (m_bActive)
	{
		// すでに表示中のとき
		return FALSE;

	}
	else {
		// 開始処理
		m_bActive = TRUE;
		m_FrameEnd = fFreamEnd;
		m_dwPlayerNo = dwPlayerNo;
		m_pSprite = pSprite;
		m_pImageForegrd = pImage;
		vPosGain = vPos;
		vEffObj = pOtherObj;
		vEffSize = vSize;
		vEffSrcPos = vSrcPos;
		vEffSrcSize = vSrcSize;
		fEffAlpha = fAlpha;
		m_Frame = 0;
		fNum1 = Random(-6, 6);
		fNum1 = fNum1 / 10;
		bTrigger = FALSE;
		vVarNum1 = VECTOR2(0, 0);
		bMaxSizeX = FALSE;
		bMaxSizeY = FALSE;
		nWrapFrame = 0;

		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	エネルギーディスクオブジェクトの移動・更新処理	
//  ・エネルギーディスクを更新する
//
//	戻り値 なし
//
//
//------------------------------------------------------------------------
void CEnergyDiskObj::Update()
{
	if (m_bActive)
	{

		VECTOR2 vSize(0, 0);

		if (bTrigger != TRUE)vVarNum1 = vEffSize;
		VECTOR2 vMaxSize = vVarNum1;
		DWORD WrapFrameAdd = 120;

		//フレームに合わせて拡大量を合わせる
		float ExpNumX = (vMaxSize.x / (m_FrameEnd*0.1));
		float ExpNumY = (vMaxSize.y / (m_FrameEnd*0.1));

		//最大になったらサイズを固定させる
		if (bMaxSizeX == TRUE && bMaxSizeY == TRUE) {
			if (nWrapFrame + WrapFrameAdd < m_Frame) {
				vSize.x = vMaxSize.x-( ExpNumX * (m_Frame - (nWrapFrame+ WrapFrameAdd)));
				vSize.y = vMaxSize.y-(ExpNumX * (m_Frame - (nWrapFrame+ WrapFrameAdd)));
				if (vSize.x <= 0)	vSize.x=0;
				if (vSize.y <= 0)	vSize.y=0;
			}
			else {
				vSize.x = vMaxSize.x;
				vSize.y = vMaxSize.y;

			}
		}
		else {	//サイズ拡大

			vSize.x = ExpNumX * m_Frame;
			if (vSize.x >= vMaxSize.x) {
				vSize.x = vMaxSize.x;
				bMaxSizeX = TRUE;
				nWrapFrame = m_Frame;
			}
			vSize.y = ExpNumY * m_Frame;
			if (vSize.y >= vMaxSize.y) {
				vSize.y = vMaxSize.y;
				bMaxSizeY = TRUE;
				nWrapFrame = m_Frame;
			}

		}
		vEffSize = vSize;
		bTrigger = TRUE;
		// レンダリング
		Render();
		m_Frame++;	// フレームを進める

		if (m_FrameEnd <= m_Frame)		m_bActive = FALSE;



	}
}

//------------------------------------------------------------------------
//
//	エネルギーディスクオブジェクトを画面にレンダリング	
//  ・エネルギーディスクを表示する
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CEnergyDiskObj::Render()
{
	// 表示状態でないとき
	if (!m_bActive)  return;
	VECTOR2 vSize = VECTOR2(400,400);
	m_pGMain->m_pRenderBufProc->SetDraw3DSprite(m_pSprite, m_pImageForegrd, vPosGain, vEffSize, VECTOR2(0, 0), vSize, m_dwPlayerNo);

	return;
}
