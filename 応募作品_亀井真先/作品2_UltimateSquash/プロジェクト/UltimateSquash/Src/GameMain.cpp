//=============================================================================
//
//		ゲームのメイン処理
//																GameMain.cpp
//=============================================================================
#include "GameMain.h"
#include "Playchar.h"
#include "Camera.h"
#include "Enemy.h"
#include "Map.h"
#include "Weapon.h"
#include "Effect.h"
#include "BackFore.h"
#include "Title.h"

// ============================================================================================
//
// CGameMain ゲームメインクラスの処理
//
// ============================================================================================
//------------------------------------------------------------------------
//
//	ゲームメインクラスのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CGameMain::CGameMain(CMain*	pMain)
{
	ZeroMemory(this, sizeof(CGameMain));
	m_pMain = pMain;
}
//------------------------------------------------------------------------
//
//	ゲームメインクラスのデストラクタ	
//
//------------------------------------------------------------------------
CGameMain::~CGameMain()
{
	MyImgui::ImguiQuit();            // MyImguiの終了処理

	SAFE_DELETE(m_pSeLazer);
	SAFE_DELETE(m_pSeFire);
	SAFE_DELETE(m_pSeDead);
	SAFE_DELETE(m_pSeNitro);

	SAFE_DELETE(m_pEnmProc);
	SAFE_DELETE(m_pPcProc);
	SAFE_DELETE(m_pCameraProc);
	SAFE_DELETE(m_pMapProc);
	SAFE_DELETE(m_pWeaponProc);
	SAFE_DELETE(m_pEffectProc);
	SAFE_DELETE(m_pBackForeProc);
	SAFE_DELETE(m_pTitleProc);

	SAFE_DELETE(m_pMapSubProc);	
	SAFE_DELETE(m_pRenderBufProc);

	SAFE_DELETE(m_pMPR);


	SAFE_DELETE(m_pFbxMeshCtrl);
	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDI);
	SAFE_DELETE(m_pXAudio);
	SAFE_DELETE(m_pD3D);

	CoUninitialize();   // COMの解放
}

//------------------------------------------------------------------------
//
//	アプリケーションの初期化処理	
//
//  引数　なし
//
//	戻り値 HRESULT
//		S_OK	= 正常
//		E_FAIL	= 異常
//
//------------------------------------------------------------------------
HRESULT CGameMain::Init()
{
	// ＣＯＭの初期化
	CoInitialize( NULL );

	// Direct3Dの初期化
	m_pD3D = new CDirect3D;
	if (FAILED(m_pD3D->InitD3D(m_pMain->m_hWnd, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("Direct3Dを初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// シェーダーの初期化
	m_pShader = new CShader(m_pD3D);
	if (FAILED(m_pShader->InitShader())) {
		MessageBox(0, _T("Shaderを生成・初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// XAudio2の初期化
	m_pXAudio = new CXAudio;
	if (FAILED(m_pXAudio->InitAudio(m_pMain->m_hWnd))) {
		MessageBox(0, _T("XAudio2を初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// DirectInputの初期化
	m_pDI = new CDirectInput;
	if (FAILED(m_pDI->StartDirectInput(m_pMain->m_hInstance, m_pMain->m_hWnd, 
                    INIT_KEYBOARD | INIT_MOUSE | INIT_JOYSTICK, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("DirectInputを初期化出来ません"), NULL, MB_OK);
		return E_FAIL;
	}

	// トゥーンテクスチャ読み込み
	if (FAILED(m_pD3D->CreateShaderResourceViewFromFile(_T("Data/Image/ToonPaint.png"), &m_pD3D->m_pToonTexture, 3)))
	{
		MessageBox(NULL, _T("Data/Image/ToonPaint.png"), _T("トゥーンテクスチャファイルがありません"), MB_OK);
		return E_FAIL;
	}

	// フォントテクスチャーの初期化
	m_pFont = new CFontTexture(m_pShader);

	// MyImguiの初期化
	MyImgui::ImguiInit(m_pMain->m_hWnd, m_pD3D, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Fbxメッシュコントロールクラス
	m_pFbxMeshCtrl = new CFbxMeshCtrl(m_pShader); 

	// MPRの初期化
	m_pMPR = new CMPR(m_pShader);


	// ----------------------------------------------------------------------------------------
	// 変数の初期化
	m_dwGameStatus = TITLE;
	m_vLightDir = normalize( VECTOR3(0.8f, 1, -1) );  // 光源座標の初期値。正規化する
	m_vLightDirSecond = normalize(VECTOR3(0.8f, 1, -1));  // 光源座標の初期値。正規化する

	// プロジェクショントランスフォーム（射影変換）の初期値
	//m_mProj = XMMatrixPerspectiveFovLH((FLOAT)(XM_PI / 4), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);
	m_mProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);
	m_mProjSecond = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);


	// ビュートランスフォーム（視点座標変換）の初期値
	VECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//上方位置
	m_vEyePt = VECTOR3(0.0f, 1.0f, 0.0f);
	m_vLookatPt = VECTOR3(0.0f, 1.0f, 1.0f);
	m_mView = XMMatrixLookAtLH(m_vEyePt, m_vLookatPt, vUpVec);

	m_vEyePtSecond = VECTOR3(0.0f, 1.0f, 0.0f);
	m_vLookatPtSecond = VECTOR3(0.0f, 1.0f, 1.0f);
	m_mViewSecond = XMMatrixLookAtLH(m_vEyePtSecond, m_vLookatPtSecond, vUpVec);


	// 各プロシージャの初期化
	m_pPcProc = new CPcProc(this);		// ＰＣプロシージャ

	m_pCameraProc = new CCameraProc(this);	// カメラプロシージャ


	m_pEnmProc = new CEnmProc(this);	// 敵プロシージャ


	m_pEffectProc = new CEffectProc(this);  // ３Ｄ効果

	m_pWeaponProc = new CWeaponProc(this);	// Weaponプロシージャ

	m_pMapProc = new CMapProc(this);	// Mapプロシージャ


	m_pMapSubProc = new CMapSubProc(this);	// Mapプロシージャ


	m_pBackForeProc = new CBackForeProc(this);  // 前景・背景

	m_pTitleProc = new CTitleProc(this);  // タイトル。ゲームクリヤー。ゲームオーバー

	m_pRenderBufProc = new CRenderBufProc(this);  // 描画バッファ 



	//--セーブデータロード
	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, "Data/Read/Save.dat", "rb"); // ファイルを開く
	if (fp == NULL) { // NULLが返ってきたらエラー発生
	}
	else {
		fread(&m_nHighScore, sizeof(int), 1, fp);
		fclose(fp); //ファイルを閉じる

	}



	return S_OK;
}

//------------------------------------------------------------------------
//
//	ゲームのループ処理	
//
//  引数　なし
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CGameMain::Loop()
{

	m_pDI->GetInput();			// 入力情報の取得
	m_pFont->Refresh();         // フォント情報のリフレッシュ
	MyImgui::ImguiNewFrame();   // MyImgui描画前処理

	//if (m_pDI->CheckKey(KD_TRG, DIK_F4))  ChangeScreenMode();   // フルスクリーンの切り替え

	switch (m_dwGameStatus)
	{
	case TITLE:				// ゲーム開始タイトル
		m_pTitleProc->Title();
		break;

	case GAMEMAIN:			// ゲーム主処理
		GameMain();
		break;

	case GAMECLEAR:			// ゲームクリヤー処理
		m_pTitleProc->GameClear();
		break;

	case GAMEEND:			// ゲーム終了
		PostQuitMessage(0);
		break;

	case GAMETUTORIAL:			// ゲーム主処理
		GameTutorial();
		break;

	case GAMEMULTI:			// ゲーム主処理
		GameMulti();
		break;

	case GAMEMULTIBATTLERESULT:			// ゲーム主処理
		m_pTitleProc->MultiBattleGameClear();
		break;


	}

	MyImgui::ImguiRender();      // MyImgui実描画処理 



	//画面更新（バックバッファをフロントバッファに）
	m_pD3D->m_pSwapChain->Present(0, 0);                   // Vsyncなし



}

//------------------------------------------------------------------------
//
//	ゲームのメイン処理	
//
//  引数　なし
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CGameMain::GameMain()
{
	m_pRenderBufProc->Clear();	// 描画バッファのクリヤー

	// パス１　　ＭＰＲテクスチャにレンダリング
// レンダーターゲットをMPRテクスチャーにする
	m_pD3D->SetRenderTarget(m_pMPR->m_pMPR_TexRTV, m_pMPR->m_pMPR_DSTexDSV);


	//画面クリア（実際は単色で画面を塗りつぶす処理）
	float ClearColor[4] = { 0,0,0,1 };// クリア色作成　RGBAの順
	m_pD3D->ClearRenderTarget(ClearColor); // 画面クリア

	m_mProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);

	// Mapの更新
	m_pMapProc->Update();

	m_pMapSubProc->Update();
	// ＰＣの更新
	m_pPcProc->UpdateAll();

	// 敵の更新
	if (m_pMapProc->GetPhaseMap() == 1)m_pEnmProc->UpdateAll();

	// スキルの更新
	if (m_pMapProc->GetPhaseMap() == 1)m_pWeaponProc->UpdateAll();

	// ３Ｄ効果の更新
	m_pEffectProc->UpdateAll();

	// 描画バッファからの描画処理 
	m_pRenderBufProc->Render();

	// Mapの描画2
	// 半透明のマップオブジェクトを描画するため、主ループの最後に実行
	m_pMapProc->Render2();

	m_pMapSubProc->Render2();

// ------------------------------------------------------------------------------------
// パス２	
// レンダーターゲットを通常（バックバッファー）に戻す
m_pD3D->SetRenderTarget(NULL, NULL);

	// 画面クリア（実際は単色で画面を塗りつぶす処理）
	m_pD3D->ClearRenderTarget(ClearColor); // 画面クリア


	//Zバッファを無効化
	m_pD3D->SetZBuffer(FALSE);


	// レンダー
	m_pMPR->RenderMPR();

	//Zバッファを有効化
	m_pD3D->SetZBuffer(TRUE);


	
	// ---------------------------------------------------------------------------------------
	

	// 前景・背景の更新
	m_pBackForeProc->Update();


	// カメラの更新
	m_pCameraProc->GetCameraObjPtr()->Update();


}



//------------------------------------------------------------------------
//
//	ゲームのチュートリアル処理	
//
//  引数　なし
//
//	戻り値 なし
//
//
//------------------------------------------------------------------------
void CGameMain::GameTutorial()
{

	m_pRenderBufProc->Clear();	// 描画バッファのクリヤー

	// パス１　　ＭＰＲテクスチャにレンダリング
// レンダーターゲットをMPRテクスチャーにする
	m_pD3D->SetRenderTarget(m_pMPR->m_pMPR_TexRTV, m_pMPR->m_pMPR_DSTexDSV);

	GameTutorialPhase();


	//画面クリア（実際は単色で画面を塗りつぶす処理）
	float ClearColor[4] = { 0,0,0,1 };// クリア色作成　RGBAの順
	m_pD3D->ClearRenderTarget(ClearColor); // 画面クリア

	m_mProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);


	// Mapの更新
	m_pMapProc->Update();

	m_pMapSubProc->Update();
	// ＰＣの更新
	m_pPcProc->UpdateAll();
		
	// 敵の更新
	m_pEnmProc->UpdateAll();

	
	// スキルの更新
	m_pWeaponProc->UpdateAll();

	// ３Ｄ効果の更新
	m_pEffectProc->UpdateAll();

	// 描画バッファからの描画処理
	m_pRenderBufProc->Render();

	// Mapの描画2
	// 半透明のマップオブジェクトを描画するため、主ループの最後に実行
	m_pMapProc->Render2();

	m_pMapSubProc->Render2();

// ------------------------------------------------------------------------------------
// パス２
// レンダーターゲットを通常（バックバッファー）に戻す
	m_pD3D->SetRenderTarget(NULL, NULL);

	// 画面クリア（実際は単色で画面を塗りつぶす処理）
	m_pD3D->ClearRenderTarget(ClearColor); // 画面クリア


	//Zバッファを無効化
	m_pD3D->SetZBuffer(FALSE);


	// レンダー
	m_pMPR->RenderMPR();

	//Zバッファを有効化
	m_pD3D->SetZBuffer(TRUE);


	// デフォルトのブレンドステートをアルファブレンド用ブレンドステートにする
	// (透明色のブレンディングを設定)
	//m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	// ---------------------------------------------------------------------------------------


	// 前景・背景の更新
	m_pBackForeProc->Update();


	// カメラの更新
	m_pCameraProc->GetCameraObjPtr()->Update();



}


//------------------------------------------------------------------------
//	ゲームのチュートリアルフェーズ処理	
//
//  引数　なし
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CGameMain::GameTutorialPhase()
{
	DWORD dwMaxPhase = 11;
	if(m_dPhase%2==0)			m_pPcProc->GetPcObjPtr()->SetStop(TRUE);
	else if (m_dPhase == dwMaxPhase)
	{
		m_pPcProc->GetPcObjPtr()->SetStop(FALSE);
		m_pTitleProc->m_dwStatusPhase = TITLE_MODESELECT_TUTORIAL;
		m_dwGameStatus = TITLE;
		m_dPhase = 0;

	}
}


//------------------------------------------------------------------------
//
//	ゲームのメイン処理	
//
//  引数　なし
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CGameMain::GameMulti()
{
	m_pRenderBufProc->Clear();	// 描画バッファのクリヤー

	m_mProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), ((FLOAT)WINDOW_WIDTH) / ((FLOAT)(WINDOW_HEIGHT / 3) * 2), 0.1f, 1000.0);


// レンダーターゲットをMPRテクスチャーにする
	m_pD3D->SetRenderTarget(m_pMPR->m_pMPR_TexRTV, m_pMPR->m_pMPR_DSTexDSV);

	//画面クリア（実際は単色で画面を塗りつぶす処理）
	float ClearColor[4] = { 0,0,0,1 };// クリア色作成　RGBAの順
	m_pD3D->ClearRenderTarget(ClearColor); // 画面クリア

	// Mapの更新
	m_pMapProc->Update();

	m_pMapSubProc->Update();
	// ＰＣの更新
	m_pPcProc->UpdateAllMulti(FIRSTPLAYER);

	// 敵の更新
	if (m_pMapProc->GetPhaseMap() == 1)m_pEnmProc->UpdateAllMulti(FIRSTPLAYER);

	// スキルの更新
	if (m_pMapProc->GetPhaseMap() == 1)m_pWeaponProc->UpdateAllMulti(FIRSTPLAYER);

	// ３Ｄ効果の更新
	m_pEffectProc->UpdateAllMulti(FIRSTPLAYER);

	// 描画バッファからの描画処理
	m_pRenderBufProc->Render();

	// Mapの描画2
	// 半透明のマップオブジェクトを描画するため、主ループの最後に実行
	m_pMapProc->Render2();

	m_pMapSubProc->Render2();

// ------------------------------------------------------------------------------------
// パス２

	D3D11_VIEWPORT vp;
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT/2;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pD3D->m_pDeviceContext->RSSetViewports(1, &vp);

// レンダーターゲットを通常（バックバッファー）に戻す
	m_pD3D->SetRenderTarget(NULL, NULL);

	// 画面クリア（実際は単色で画面を塗りつぶす処理）
	m_pD3D->ClearRenderTarget(ClearColor); // 画面クリア


	//Zバッファを無効化
	m_pD3D->SetZBuffer(FALSE);


	// レンダー
	m_pMPR->RenderMPR();

	//Zバッファを有効化
	m_pD3D->SetZBuffer(TRUE);

	// ---------------------------------------------------------------------------------------


	// 前景・背景の更新
	//m_pBackForeProc->Update();


	// カメラの更新
	m_pCameraProc->GetCameraObjPtr()->Update();



	D3D11_VIEWPORT vp2;
	vp2.Width = WINDOW_WIDTH;
	vp2.Height = WINDOW_HEIGHT;
	vp2.MinDepth = 0.0f;
	vp2.MaxDepth = 1.0f;
	vp2.TopLeftX = 0;
	vp2.TopLeftY = 0;

	m_pD3D->m_pDeviceContext->RSSetViewports(1, &vp2);


//----------------------------------------------------------------------------------------------------------------------------------
	m_mProjSecond = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), ((FLOAT)WINDOW_WIDTH) / ((FLOAT)(WINDOW_HEIGHT / 3) * 2), 0.1f, 1000.0);

// レンダーターゲットをMPRテクスチャーにする
	m_pD3D->SetRenderTarget(m_pMPR->m_pMPR_TexRTV, m_pMPR->m_pMPR_DSTexDSV);


	//画面クリア（実際は単色で画面を塗りつぶす処理）
	m_pD3D->ClearRenderTarget(ClearColor); // 画面クリア

	// Mapの更新
	m_pMapProc->RenderSecond();


	// ＰＣの更新
	m_pPcProc->UpdateAllMulti(SECONDPLAYER);

	if (m_pMapProc->GetPhaseMap() == 1)m_pEnmProc->UpdateAllMulti(SECONDPLAYER);

	if (m_pMapProc->GetPhaseMap() == 1)m_pWeaponProc->UpdateAllMulti(SECONDPLAYER);

	// ３Ｄ効果の更新
	m_pEffectProc->UpdateAllMulti(SECONDPLAYER);


	// 描画バッファからの描画処理
	m_pRenderBufProc->RenderSecond();

	m_pMapProc->Render2Second();

	vp.TopLeftX = 0;
	vp.TopLeftY = WINDOW_HEIGHT / 2;

	m_pD3D->m_pDeviceContext->RSSetViewports(1, &vp);

	// レンダーターゲットを通常（バックバッファー）に戻す
	m_pD3D->SetRenderTarget(NULL, NULL);

	//Zバッファを無効化
	m_pD3D->SetZBuffer(FALSE);


	// レンダー
	m_pMPR->RenderMPR();

	//Zバッファを有効化
	m_pD3D->SetZBuffer(TRUE);


	// ---------------------------------------------------------------------------------------

	// カメラの更新
	m_pCameraProc->UpdateAllMulti(SECONDPLAYER);

	vp2.TopLeftX = 0;
	vp2.TopLeftY = 0;

	m_pD3D->m_pDeviceContext->RSSetViewports(1, &vp2);

	// 前景・背景の更新
	m_pBackForeProc->Update();


}

//------------------------------------------------------------------------
//
//	アプリケーションの終了処理	
//
//  引数　なし
//
//	戻り値 なし
//
//------------------------------------------------------------------------
void CGameMain::Quit()
{
	;
}

//------------------------------------------------------------------------
//
//	ウィンドウモードとフルスクリーンモードを切り替える処理	
//
//  引数　モード  0:ウインドウモード　1:フルスクリーン　-1:モード切り替え（省略値）
//
//	戻り値 なし
//
//------------------------------------------------------------------------
HRESULT CGameMain::ChangeScreenMode(int nMode)
{
	HRESULT Ret = S_OK;
	BOOL bFullScreen;  // フルスクリーンモードか？

	//	現在のスクリーンモードを得る
	m_pD3D->m_pSwapChain->GetFullscreenState(&bFullScreen, NULL);

	switch (nMode)
	{
	case 0:    // ウインドウモードにする
		if( bFullScreen ) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, NULL);
		break;
	case 1:    // フルスクリーンモードにする
		if( !bFullScreen ) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, NULL);
		break;
	default:   // 現在のモードを切り替える
		if (bFullScreen)
		{
			Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, NULL);
		}
		else {
			Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, NULL);
		}
	}

	return Ret;
}

