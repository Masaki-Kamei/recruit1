//=============================================================================
//		タイトル・ゲームクリヤー・ゲームオーバーの処理
//																Title.cpp
//=============================================================================
#include  "Title.h"
#include  "Map.h"
#include  "Playchar.h"
#include  "Weapon.h"
#include  "BackFore.h"
#include  "Enemy.h"
//============================================================================
//
// タイトルプロシージャのコンストラクタ
//
// ---------------------------------------------------------------------------
CTitleProc::CTitleProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;

	m_pImageTitle = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/TITLE_4_Ver2.png")); // イメージのロード
	m_pImageClearScore = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Result.png")); // イメージのロード
	m_pImageSelect = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Button_Ver4_3.png")); // イメージのロード
	m_pSprite = new CSprite(m_pGMain->m_pShader); // スプライトの生成

	m_pImageTitlePro = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/back_Ver2.png")); // イメージのロード
	m_pImageConstruction = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Construction_Pro3.png"));
	m_pImageConstructionFrame = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Construction_Pro.png"));
	m_pImageWeapon = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/WeaponTest.png"));

	m_pImageTextBackPro = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Text_Back_Ver2.png"));	

	//エクセルのテキストを持ってくる
	FileTextRead();

	nNo=nNoOld=0;

	m_dwCntTime = 0;

}
// ---------------------------------------------------------------------------
//
// タイトルタイトルプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CTitleProc::~CTitleProc()
{
	SAFE_DELETE(m_pImageTitle);
	SAFE_DELETE(m_pImageClearScore);

	SAFE_DELETE   (m_pImageTitlePro);
	SAFE_DELETE  (m_pImageConstruction);
	SAFE_DELETE   (m_pImageConstructionFrame);
	SAFE_DELETE   (m_pImageWeapon);

	SAFE_DELETE(m_pSprite);

}

//------------------------------------------------------------------------
//	タイトルの表示  全体	
//
//------------------------------------------------------------------------
void CTitleProc::Title()
{
	WeaponNum = 7;

	switch (m_dwStatusPhase)
	{
	case 0:

		// フルスクリーンにする(なぜか1度だけだと戻ってしまうので、再度フルスクリーンにする)
		//m_pGMain->ChangeScreenMode(1);
		TitleStart();
		break;
	case TITLE_MAIN:  //タイトル表示
		//	タイトル画面の表示	
		TitleMain();
		break;

	case TITLE_MODESELECT:    // フェーズ１  キャラクターセレクト

		//	モードセレクト	
		TitleModeSelect();
		break;
	case TITLE_MODESELECT_MAINMODE:

//	メインモードセレクト	
		TitleModeSelectMainMode();
		break;
	case TITLE_CONSTRUCTION:

//	デッキセレクト	
		TitleConstruction();
		break;
	case TITLE_MODESELECT_TUTORIAL:
		//	チュートリアルセレクト	
		TitleModeSelectTutorialMode();
		break;

	case TITLE_MODESELECT_MULTI:

		//	マルチセレクト
		TitleModeSelectMultiMode();
		break;
	case TITLE_MODESELECT_MULTIBATTLE:

		//	マルチセレクト
		TitleModeSelectMultiBattleMode();
		break;

	}
	m_dwCntTime = 0;

}

//------------------------------------------------------------------------
//
//	スタートタイトルの表示	
//
//------------------------------------------------------------------------
BOOL CTitleProc::TitleStart()
{
	BOOL bRet = FALSE;
	m_pGMain->m_dModeType = TITLEMODE;

	TCHAR PName[][50] = {
	_T("PLESS MOUSE CLICK TO START"),
	};

	// 表示
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	const int StartTextPosX = WINDOW_WIDTH / 2 - 250;
	const int StartTextPosY = WINDOW_HEIGHT - 240;
	const int StartTextSize = 50;

	m_pGMain->m_pFont->FreamDraw(StartTextPosX, StartTextPosY, PName[0], StartTextSize, RGB(0, 0, 0), StartTextAlpha, _T("メイリオ ボールド"));
	m_pGMain->m_pFont->Draw(StartTextPosX, StartTextPosY, PName[0], StartTextSize, RGB(255, 255, 255), StartTextAlpha, _T("メイリオ ボールド"));

	if (!StartTextAlphaTrigger) {
		StartTextAlpha -= 0.01;
		if (StartTextAlpha <= 0.0f)
		{
			StartTextAlpha = 0;
			StartTextAlphaTrigger = TRUE;
		}
	}
	else {
		StartTextAlpha += 0.01;
		if (StartTextAlpha >= 1.0f)
		{
			StartTextAlpha = 1.0;
			StartTextAlphaTrigger = FALSE;
		}

	}


	if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
	{
			m_dwStatusPhase = TITLE_MAIN;
			m_dwCntTime = 0;

	}

	return bRet;

}



//------------------------------------------------------------------------
//
//	メインタイトルの表示	
//
//
//------------------------------------------------------------------------
BOOL CTitleProc::TitleMain()
{
	BOOL bRet = FALSE;
	m_pGMain->m_dModeType = TITLEMODE;
	
	TCHAR PName[][20] = {
	_T("SOLO"),
	_T("MULTI"),
	_T("END"),
	};

	const int nNum = sizeof(PName) / sizeof(PName[0]);   // 配列要素数
	const float fScale = 3.0f;
	const int nStartX = 266, nStartY = 98;
	const int nWidth = 266, nHeight =98;

	const int nWidthScale = nWidth + 60;
	const int nHeightScale = nHeight;

	const int Posx = (WINDOW_WIDTH/2)- (nWidthScale/2);
	const int Posy = (WINDOW_HEIGHT / 2)+40;


	// 表示
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);


	// キーとパットによるキャラクターセレクト
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_DOWN) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_RIGHT))
	{
		if (nNo < nNum - 1) nNo++;
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_UP) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_LEFT))
	{
		if (nNo > 0) nNo--;
	}

	const int PosyRatio = (nWidth / 3) + 20;		//ボタンの数によってずらす距離
	const int ButtonFontPosx = Posx + 33;			//ボタンの文字の横位置
	const int ButtonFontPosy = Posy + 21;			//ボタンの文字の縦位置
	const int ButtonFontPointPosx = Posx + 40;		//選択した時の文字の横位置
	const int ButtonFontPointPosy = Posy + 21;		//選択した時の文字の縦位置
	const int FontSize = 60;						//文字の大きさ

	// マウスによるキャラクターセレクト
	for (int i = 0; i < nNum; i++)
	{

		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // マウスカーソルがキャラクタースプライト内にある

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);

			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy+(PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + ((nWidth / 3) + 20)*i, PName[i], FontSize, RGB(255, 255,255), 1.0f, _T("メイリオ ボールド"));

			if ( m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (nNo)
				{
				case 0:
					// 最初はマップ１のロード
					m_dwStatusPhase = TITLE_MODESELECT;
					m_dwCntTime = 0;

					break;
				case 1:
					// 最初はマップ１のロード
					m_dwStatusPhase = TITLE_MODESELECT_MULTI;
					m_dwCntTime = 0;

					break;


				case 2:
					m_pGMain->m_dwGameStatus = GAMEEND;
					m_dwCntTime = 0;

					break;
				}
				bRet = TRUE;  // 終了
				m_dwCntTime = 0;

			}

		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale,0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("メイリオ ボールド"));

		}

	}
	return bRet;

}

//------------------------------------------------------------------------
//	モードセレクトの表示	
//
//
//------------------------------------------------------------------------
BOOL CTitleProc::TitleModeSelect()
{
	BOOL bRet = FALSE;
	m_pGMain->m_dModeType = TITLEMODE;


	TCHAR PName[][20] = {
	_T("MAIN MODE"),
	_T("TUTORIAL"),
	_T("BACK"),
	};

	const int nNum = sizeof(PName) / sizeof(PName[0]);   // 配列要素数
	const float fScale = 3.0f;
	const int nStartX = 266, nStartY = 98;
	const int nWidth = 266, nHeight = 98;

	const int nWidthScale = nWidth+60;
	const int nHeightScale = nHeight;
	const int Posx = (WINDOW_WIDTH / 2) - (nWidthScale / 2);
	const int Posy = (WINDOW_HEIGHT / 2) + 40;

	// 表示
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	const int ModeFontPosx = Posx + 20;					//現在のモード文字の横位置
	const int ModeFontPosy = Posy - 30;					//現在のモード文字の縦位置
	const int ModeFontSize = 30;						//文字の大きさ

	m_pGMain->m_pFont->FreamDraw(ModeFontPosx, ModeFontPosy, _T("SOLO"), ModeFontSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
	m_pGMain->m_pFont->Draw(ModeFontPosx, ModeFontPosy, _T("SOLO"), ModeFontSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));

	// キーとパットによるキャラクターセレクト
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_DOWN) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_RIGHT))
	{
		if (nNo < nNum - 1) nNo++;
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_UP) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_LEFT))
	{
		if (nNo > 0) nNo--;
	}

	const int PosyRatio = (nWidth / 3) + 20;		//ボタンの数によってずらす距離
	const int ButtonFontPosx = Posx + 33;			//ボタンの文字の横位置
	const int ButtonFontPosy = Posy + 21;			//ボタンの文字の縦位置
	const int ButtonFontPointPosx = Posx + 40;		//選択した時の文字の横位置
	const int ButtonFontPointPosy = Posy + 21;		//選択した時の文字の縦位置
	const int FontSize = 60;						//文字の大きさ


	// マウスによるキャラクターセレクト
	for (int i = 0; i < nNum; i++)
	{
		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // マウスカーソルがキャラクタースプライト内にある

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));

			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (nNo)
				{
				case 0:
					m_dwStatusPhase = TITLE_MODESELECT_MAINMODE;
					m_dwCntTime = 0;
					break;
				case 1:
					m_dwStatusPhase = TITLE_MODESELECT_TUTORIAL;		
					m_dwCntTime = 0;

					break;
				case 2:
					m_dwStatusPhase = TITLE_MAIN;
					break;
				}
				bRet = TRUE;  // 終了
				m_dwCntTime = 0;

			}
		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale, 0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("メイリオ ボールド"));

		}

	}
	
	return bRet;

}

//------------------------------------------------------------------------
//	メインモードのモードセレクトの表示	
//
//------------------------------------------------------------------------
BOOL CTitleProc::TitleModeSelectMainMode()
{
	BOOL bRet = FALSE;
	m_pGMain->m_dModeType = TITLEMODE;
	TCHAR PName[][20] = {
	_T("START"),
	_T("SET SKILL"),
	_T("BACK"),
	};
	//MultiByteToWideChar(CP_ACP, 0, str0, -1, PName[0], 20);

	const int nNum = sizeof(PName) / sizeof(PName[0]);   // 配列要素数
	const float fScale = 3.0f;
	const int nStartX = 266, nStartY = 98;
	const int nWidth = 266, nHeight = 98;

	const int nWidthScale = nWidth + 60;
	const int nHeightScale = nHeight;
	 
	const int Posx = (WINDOW_WIDTH / 2) - (nWidthScale / 2);
	const int Posy = (WINDOW_HEIGHT / 2) +40;

	// 表示
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	const int ModeFontPosx = Posx + 20;					//現在のモード文字の横位置
	const int ModeFontPosy = Posy - 30;					//現在のモード文字の縦位置
	const int ModeFontSize = 30;						//文字の大きさ

	m_pGMain->m_pFont->FreamDraw(ModeFontPosx, ModeFontPosy, _T("MAIN MODE"), ModeFontSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
	m_pGMain->m_pFont->Draw(ModeFontPosx, ModeFontPosy, _T("MAIN MODE"), ModeFontSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));


	// キーとパットによるキャラクターセレクト
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_DOWN) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_RIGHT))
	{
		if (nNo < nNum - 1) nNo++;
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_UP) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_LEFT))
	{
		if (nNo > 0) nNo--;
	}


	const int PosyRatio = (nWidth / 3) + 20;		//ボタンの数によってずらす距離
	const int ButtonFontPosx = Posx + 33;			//ボタンの文字の横位置
	const int ButtonFontPosy = Posy + 21;			//ボタンの文字の縦位置
	const int ButtonFontPointPosx = Posx + 40;		//選択した時の文字の横位置
	const int ButtonFontPointPosy = Posy + 21;		//選択した時の文字の縦位置
	const int FontSize = 60;						//文字の大きさ


	// マウスによるキャラクターセレクト
	for (int i = 0; i < nNum; i++)
	{
		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // マウスカーソルがキャラクタースプライト内にある

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));

			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (nNo)
				{
				case 0:
					// 最初はマップ１のロード
					m_pGMain->m_pMapProc->LoadMap1();
					m_pGMain->m_pMapSubProc->LoadMap1();	
					m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponNo(0);		//スキルナンバーの初期化	
					m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColuman(0);		//スキル欄の初期化	
					m_pGMain->m_pPcProc->GetPcObjPtr()->Init();
					m_pGMain->m_pEnmProc->m_pEnmBallProc->SetHitNum(0);
					MapAllInit();								
					m_pGMain->m_dModeType = MAINMODE;
					m_pGMain->m_dwGameStatus = GAMEMAIN;
					for (int i = 0; i < 3; i++)
					{
						WeaponSelectNo[i] = WeaponSelectNoSave[i];		//編成したスキルをセット	
						m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColumanNo(i, WeaponSelectNo[i]);

					}

					for (int i = 0; i < 3; i++) {
						m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->ResetWeaponWaitTime(i);
					}
						m_dwCntTime = 0;
					break;

				case 1:
					nNo2 = -1;
					ClickWeaponNo = -1;		//クリックしたスキルナンバーの初期化
					for (int i = 0; i < 3; i++)
					{
						WeaponSelectNo[i] = WeaponSelectNoSave[i];
					}
					m_dwStatusPhase = TITLE_CONSTRUCTION;
					break;


				case 2:
					m_dwStatusPhase = TITLE_MODESELECT;
					break;
				}
				bRet = TRUE;  // 終了
				m_dwCntTime = 0;

			}

		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale, 0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("メイリオ ボールド"));

		}

	}
	//--ハイスコア表示	
	int   DestX, DestY;

	DestX = 0;
	DestY = WINDOW_HEIGHT-200;
	TCHAR str[256] = { 0 };

	return bRet;

}

//------------------------------------------------------------------------
//	チュートリアルのモードセレクトの表示	
//
//------------------------------------------------------------------------
BOOL CTitleProc::TitleModeSelectTutorialMode()
{
	BOOL bRet = FALSE;
	m_pGMain->m_dModeType = TITLEMODE;


	TCHAR PName[][20] = {
	_T("START"),
	_T("BACK"),
	};

	const int nNum = sizeof(PName) / sizeof(PName[0]);   // 配列要素数
	const float fScale = 3.0f;
	const int nStartX = 266, nStartY = 98;
	const int nWidth = 266, nHeight = 98;

	const int nWidthScale = nWidth + 60;
	const int nHeightScale = nHeight;

	const int Posx = (WINDOW_WIDTH / 2) - (nWidthScale / 2);
	const int Posy = (WINDOW_HEIGHT / 2) + 40;

	const int ModeNameTextPosx = Posx + 20;
	const int ModeNameTextPosy = Posy - 30;
	const int ModeNameTextSize = 30;

	// 表示
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	m_pGMain->m_pFont->FreamDraw(ModeNameTextPosx, ModeNameTextPosy, _T("TUTORIAL"), ModeNameTextSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));

	m_pGMain->m_pFont->Draw(ModeNameTextPosx, ModeNameTextPosy, _T("TUTORIAL"), ModeNameTextSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));


	// キーとパットによるキャラクターセレクト
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_DOWN) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_RIGHT))
	{
		if (nNo < nNum - 1) nNo++;
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_UP) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_LEFT))
	{
		if (nNo > 0) nNo--;
	}


	const int PosyRatio = (nWidth / 3) + 20;		//ボタンの数によってずらす距離
	const int ButtonFontPosx = Posx + 33;			//ボタンの文字の横位置
	const int ButtonFontPosy = Posy + 21;			//ボタンの文字の縦位置
	const int ButtonFontPointPosx = Posx + 40;		//選択した時の文字の横位置
	const int ButtonFontPointPosy = Posy + 21;		//選択した時の文字の縦位置
	const int FontSize = 60;						//文字の大きさ


	// マウスによるキャラクターセレクト
	for (int i = 0; i < nNum; i++)
	{

		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // マウスカーソルがキャラクタースプライト内にある

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));

			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (nNo)
				{
				case 0:

					// 最初はマップ3のロード
					m_pGMain->m_pMapProc->LoadMapTutorial();
					m_pGMain->m_pMapSubProc->LoadMap1();
					m_pGMain->m_pBackForeProc->TutorialTextInit();
					m_pGMain->m_pPcProc->GetPcObjPtr()->Init();
					m_pGMain->m_pEnmProc->m_pEnmBallProc->SetHitNum(0);
					m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponNo(0);		//スキルナンバーの初期化
					m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColuman(0);		//スキル欄の初期化	

					MapAllInit();
					for (int i = 0; i < 3; i++)
					{
						WeaponSelectNo[i] = 0;
						m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColumanNo(i, WeaponSelectNo[i]);

					}
					m_pGMain->m_dModeType = TUTORIAL;
					m_pGMain->m_dwGameStatus = GAMETUTORIAL;
					m_pGMain->m_pBackForeProc->TutorialCapture();
					m_dwCntTime = 0;
					break;



				case 1:
					m_dwStatusPhase = TITLE_MODESELECT;
					break;
				}
				bRet = TRUE;  // 終了
				m_dwCntTime = 0;

			}

		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale, 0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("メイリオ ボールド"));

		}

	}



	return bRet;


}

//------------------------------------------------------------------------
//	マルチモードセレクトの表示	
//
//
//------------------------------------------------------------------------
BOOL CTitleProc::TitleModeSelectMultiMode()
{
	BOOL bRet = FALSE;
	m_pGMain->m_dModeType = TITLEMODE;


	TCHAR PName[][20] = {
	_T("BATTLE"),
	_T("BACK"),
	};

	const int nNum = sizeof(PName) / sizeof(PName[0]);   // 配列要素数
	const float fScale = 3.0f;
	const int nStartX = 266, nStartY = 98;
	const int nWidth = 266, nHeight = 98;

	const int nWidthScale = nWidth + 60;
	const int nHeightScale = nHeight;
	const int Posx = (WINDOW_WIDTH / 2) - (nWidthScale / 2);
	const int Posy = (WINDOW_HEIGHT / 2) + 40;

	// 表示
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	const int ModeFontPosx = Posx + 20;					//現在のモード文字の横位置
	const int ModeFontPosy = Posy - 30;					//現在のモード文字の縦位置
	const int ModeFontSize = 30;						//文字の大きさ

	m_pGMain->m_pFont->FreamDraw(ModeFontPosx, ModeFontPosy, _T("MULTI"), ModeFontSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
	m_pGMain->m_pFont->Draw(ModeFontPosx, ModeFontPosy, _T("MULTI"), ModeFontSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));

	// キーとパットによるキャラクターセレクト
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_DOWN) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_RIGHT))
	{
		if (nNo < nNum - 1) nNo++;
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_UP) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_LEFT))
	{
		if (nNo > 0) nNo--;
	}

	const int PosyRatio = (nWidth / 3) + 20;		//ボタンの数によってずらす距離
	const int ButtonFontPosx = Posx + 33;			//ボタンの文字の横位置
	const int ButtonFontPosy = Posy + 21;			//ボタンの文字の縦位置
	const int ButtonFontPointPosx = Posx + 40;		//選択した時の文字の横位置
	const int ButtonFontPointPosy = Posy + 21;		//選択した時の文字の縦位置
	const int FontSize = 60;						//文字の大きさ


	// マウスによるキャラクターセレクト
	for (int i = 0; i < nNum; i++)
	{
		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // マウスカーソルがキャラクタースプライト内にある

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));

			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (nNo)
				{
				case 0:
					m_dwStatusPhase = TITLE_MODESELECT_MULTIBATTLE;
					m_dwCntTime = 0;
					break;
				case 1:
					m_dwStatusPhase = TITLE_MAIN;
					break;
				}
				bRet = TRUE;  // 終了
				m_dwCntTime = 0;

			}
		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale, 0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("メイリオ ボールド"));

		}

	}

	return bRet;

}


//------------------------------------------------------------------------
//	マルチのモードセレクトの表示	
//
//------------------------------------------------------------------------
BOOL CTitleProc::TitleModeSelectMultiBattleMode()
{
	BOOL bRet = FALSE;
	m_pGMain->m_dModeType = TITLEMODE;


	TCHAR PName[][20] = {
	_T("START"),
	_T("BACK"),
	};

	const int nNum = sizeof(PName) / sizeof(PName[0]);   // 配列要素数
	const float fScale = 3.0f;
	const int nStartX = 266, nStartY = 98;
	const int nWidth = 266, nHeight = 98;

	const int nWidthScale = nWidth + 60;
	const int nHeightScale = nHeight;

	const int Posx = (WINDOW_WIDTH / 2) - (nWidthScale / 2);
	const int Posy = (WINDOW_HEIGHT / 2) + 40;

	const int ModeNameTextPosx = Posx + 20;
	const int ModeNameTextPosy = Posy - 30;
	const int ModeNameTextSize = 30;

	// 表示
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	const int ModeFontPosx = Posx + 20;					//現在のモード文字の横位置
	const int ModeFontPosy = Posy - 30;					//現在のモード文字の縦位置
	const int ModeFontSize = 30;						//文字の大きさ

	m_pGMain->m_pFont->FreamDraw(ModeFontPosx, ModeFontPosy, _T("BATTLE"), ModeFontSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
	m_pGMain->m_pFont->Draw(ModeFontPosx, ModeFontPosy, _T("BATTLE"), ModeFontSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));


	// キーとパットによるキャラクターセレクト
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_DOWN) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_RIGHT))
	{
		if (nNo < nNum - 1) nNo++;
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_UP) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_LEFT))
	{
		if (nNo > 0) nNo--;
	}


	const int PosyRatio = (nWidth / 3) + 20;		//ボタンの数によってずらす距離
	const int ButtonFontPosx = Posx + 33;			//ボタンの文字の横位置
	const int ButtonFontPosy = Posy + 21;			//ボタンの文字の縦位置
	const int ButtonFontPointPosx = Posx + 40;		//選択した時の文字の横位置
	const int ButtonFontPointPosy = Posy + 21;		//選択した時の文字の縦位置
	const int FontSize = 60;						//文字の大きさ


	// マウスによるキャラクターセレクト
	for (int i = 0; i < nNum; i++)
	{

		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // マウスカーソルがキャラクタースプライト内にある

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));

			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (nNo)
				{
				case 0:

					// 最初はマップ3のロード
					m_pGMain->m_pMapProc->LoadMapMulti();
					m_pGMain->m_pMapSubProc->LoadMap1();	
					m_pGMain->m_pPcProc->GetPcObjPtr()->Init();
					m_pGMain->m_pPcProc->GetPcSecObjPtr()->Init();
					m_pGMain->m_pEnmProc->m_pEnmBallProc->SetHitNum(0);
					m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponNo(0);		//スキルナンバーの初期化	
					m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColuman(0);		//スキル欄の初期化
					MapAllInit();
					SetEnmNav();
					for (int i = 0; i < 3; i++)
					{
						WeaponSelectNo[i] = 0;
					}
					m_pGMain->m_dModeType = MULTI;
					m_pGMain->m_dwGameStatus = GAMEMULTI;
					m_dwCntTime = 0;

					break;

				case 1:
					m_dwStatusPhase = TITLE_MODESELECT_MULTI;
					break;
				}
				bRet = TRUE;  // 終了
				m_dwCntTime = 0;

			}

		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale, 0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("メイリオ ボールド"));

		}

	}



	return bRet;

}


//------------------------------------------------------------------------
//	デッキセレクトの表示	
//
//
//------------------------------------------------------------------------
BOOL CTitleProc::TitleConstruction()
{
	BOOL bRet = FALSE;
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	m_pGMain->m_dModeType = TITLEMODE;

	TCHAR PName[][20] = {
	_T("BACK"),
	};

	//スキルの詳細の名前		
	const int WeaponNameTextNum = 20;
	TCHAR WeaponName[][WeaponNameTextNum] = {
	_T("拡散ボール"),
	_T("巨大ボール"),
	_T("貫通ボール"),
	_T("回転ボール"),
	_T("固定生成"),
	_T("吹き飛ばす"),
	_T("スピードアップ"),

	};
	BOOL bSwitchTrigger = FALSE;


	const int nNum = sizeof(PName) / sizeof(PName[0]);   // 配列要素数
	const int nWeaponNameNum = sizeof(WeaponName) / sizeof(WeaponName[0]);
	const float fScale = 3.0f;
	int nStartX = 266, nStartY = 98;
	int nWidth = 258, nHeight = 258;

	int nWidthScale = nWidth;
	int nHeightScale = nHeight;

	const int Posx = WINDOW_WIDTH-300;
	const int Posy = WINDOW_HEIGHT -100;

	const int WeaponSet = 3;

	int	LineNum = (WeaponNum / 5) + 1;	//スキルの選択欄の行の数
	int Line = 0;						//スキルの選択欄の行
	int Column = 0;						//スキルの選択欄の列
	TCHAR *pWeaponName[nWeaponNameNum];
	for (int i = 0; i < nWeaponNameNum; i++) pWeaponName[i] = WeaponName[i];

	// 背景表示
	m_pSprite->Draw(m_pImageTitlePro, 0, 0, 0, 0, m_pImageTitlePro->m_dwImageWidth, m_pImageTitlePro->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pSprite->Draw(m_pImageConstruction,60, 30, 10, 10, 814, 414);

	SkillExplanation(nWidth, nHeight, pWeaponName);

	const int PosyRatio = (nWidth / 3) + 20;		//ボタンの数によってずらす距離
	const int ButtonFontPosx = Posx + 40;			//ボタンの文字の横位置
	const int ButtonFontPosy = Posy + 21;			//ボタンの文字の縦位置
	const int ButtonFontPointPosx = Posx + 40;		//選択した時の文字の横位置
	const int ButtonFontPointPosy = Posy + 21;		//選択した時の文字の縦位置
	const int FontSize = 60;						//文字の大きさ

	// 戻るマウスによるボタンセレクト
	for (int i = 0; i < nNum; i++)
	{
		nWidth = 266, nHeight = 98;
		nWidthScale = nWidth;
		nHeightScale = nHeight;

		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // マウスカーソルがキャラクタースプライト内にある

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));

			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 1.0, _T("メイリオ ボールド"));

			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				if (nNo == 0) {
					m_dwStatusPhase = TITLE_MODESELECT_MAINMODE;
					for (int i = 0; i < 3; i++)				//編成したスキルをセット
					{
						WeaponSelectNoSave[i] = WeaponSelectNo[i];
					}
					break;
				}

				bRet = TRUE;  // 終了
				m_dwCntTime = 0;
				bSwitchTrigger = TRUE;
			}
		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale,0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("メイリオ ボールド"));

		}
	}

	Line = 0;
	Column = 0;
	const int FreamPos = 272;
	nWidth = 258, nHeight = 258;

	bSwitchTrigger = SetSkill(nWidth, nHeight,Posx,Posy,WeaponSet,LineNum, bSwitchTrigger);

	bSwitchTrigger=SkillList(nWidth, nHeight, bSwitchTrigger);

	if (bSwitchTrigger != TRUE && m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	nNo2 = -1;

	return bRet;

}
//------------------------------------------------------------------------
//
//	スキルの説明処理
//
//
//------------------------------------------------------------------------
void CTitleProc::SkillExplanation(const int nWidth,const int nHeight,TCHAR **WeaponName)
{
	const int TextBackPosx = 944;									//説明欄の位置X座標
	const int TextBackPosy = 16;									//説明欄の位置Y座標
	const int TextBackWidthScale = 403;								//説明欄の横幅
	const int TextBackHeightScale = 628;							//説明欄の縦幅
	const int TextBackNamePosx = TextBackPosx + 40;					//スキルの名前位置X座標
	const int TextBackNamePosy = TextBackPosy + 50;					//スキルの名前位置Y座標
	const int TextBackNameSize = 70;									//スキルの名前のサイズ
	const int TextBackImagePosx = TextBackPosx + 70;				//スキルの名前位置X座標
	const int TextBackImagePosy = TextBackPosy + 100;				//スキルの名前位置X座標
	const int TextBackExpPosx = TextBackPosx + 40;					//スキルの説明位置X座標
	const int TextBackExpPosy = TextBackPosy + nWidth + 100;			//スキルの説明位置Y座標
	const int TextBackExpWhile = 30;									//行の数によってずらす距離
	const int TextBackExpSize = 40;									//スキルの説明の文字サイズ
	int	LineNum = (WeaponNum / 5) + 1;	//スキルの選択欄の行の数
	int Line = 0;						//スキルの選択欄の行
	int Column = 0;						//スキルの選択欄の列

	//スキルの説明		
	m_pSprite->Draw(m_pImageTextBackPro, TextBackPosx, TextBackPosy, 0, 0, TextBackWidthScale, TextBackHeightScale, TextBackWidthScale, TextBackHeightScale);
	if (ClickWeaponNo >= 0)
	{
		int y = ClickWeaponNo / 5;
		int x = 0;
		for (int i = 0; i < LineNum; i++)
		{
			//選択したスキルが選択欄のなん列目にあるか	
			if (((i + 1) * 5) > ClickWeaponNo)
			{
				x = ClickWeaponNo - 5;
				if (x < 0) {
					x = ClickWeaponNo;
				}
				break;
			}
		}
		m_pGMain->m_pFont->Draw(TextBackNamePosx, TextBackNamePosy, WeaponName[ClickWeaponNo], 70, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));
		m_pSprite->Draw(m_pImageWeapon, TextBackImagePosx, TextBackImagePosy, nWidth*x, nHeight*y, nWidth, nHeight, nWidth, nHeight);		
		for (int i = 0; i < (sizeof(Sentence) / sizeof(*Sentence)); i++) {
			m_pGMain->m_pFont->Draw(TextBackExpPosx, TextBackExpPosy + (TextBackExpWhile*i), Sentence[ClickWeaponNo][i], TextBackExpSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));
		}
	}

}
//------------------------------------------------------------------------
//
//	スキルのセット
//
//
//------------------------------------------------------------------------
BOOL CTitleProc::SetSkill(const int nWidth, const int nHeight, const int Posx, const int Posy, const int WeaponSet,const int LineNum, BOOL bSwitchTrigger)
{

	const int FreamPos = 272;
	const int nStartX = 250, nStartY = 250;
	const int nWidthScale = nWidth;
	const int nHeightScale = nHeight;
	const int SetSetWeaponPosyRatio = (nWidth + 30);			//スキルセット欄の間隔
	const int SetWeaponPosx = nWidth - 200;						//スキルセット欄のX座標
	const int SetWeaponPosy = Posy - nHeight + 70;				//スキルセット欄のY座標
	const int SetWeaponConStartPosx = 0;						//スキルセット欄のパターン左上X座標
	const int SetWeaponConStartPosy = 0;						//スキルセット欄のパターン左上X座標
	const int SetWeaponNormalFreamStartPosx = 0;				//スキルセット欄枠のパターン左上X座標
	const int SetWeaponNormalFreamStartPosy = 300;				//スキルセット欄枠のパターン左上X座標
	const int SetWeaponPointFreamStartPosx = 300;				//スキルセット欄枠（選択中）のパターン左上X座標
	const int SetWeaponPointFreamStartPosy = 0;					//スキルセット欄枠（選択中）のパターン左上X座標
	BOOL bRet = bSwitchTrigger;

	//--セットされているスキル欄の表示
	for (int i = 0; i < WeaponSet; i++)
	{
		if (nNo2 == i) {
			m_pSprite->Draw(m_pImageConstructionFrame, SetWeaponPosx + (SetSetWeaponPosyRatio)*i, SetWeaponPosy, SetWeaponNormalFreamStartPosx, SetWeaponConStartPosy, nStartX, nStartY, nWidthScale, nHeightScale);
			m_pSprite->Draw(m_pImageConstructionFrame, SetWeaponPosx + (SetSetWeaponPosyRatio)*i, SetWeaponPosy, SetWeaponNormalFreamStartPosx, SetWeaponNormalFreamStartPosy, FreamPos, FreamPos, nWidthScale, nHeightScale);
		}
		else {
			m_pSprite->Draw(m_pImageConstructionFrame, SetWeaponPosx + (SetSetWeaponPosyRatio)*i, SetWeaponPosy, SetWeaponConStartPosx, SetWeaponConStartPosy, nStartX, nStartY, nWidthScale, nHeightScale);
			m_pSprite->Draw(m_pImageConstructionFrame, SetWeaponPosx + (SetSetWeaponPosyRatio)*i, SetWeaponPosy, SetWeaponPointFreamStartPosx, SetWeaponPointFreamStartPosy, FreamPos, FreamPos, nWidthScale, nHeightScale);
		}

		int y = (WeaponSelectNo[i] - 1) / 5;
		int x = 0;
		//選択したスキルが選択欄のなん列目にあるか
		for (int j = 0; j < LineNum; j++)
		{
			if (((j + 1) * 5) > (WeaponSelectNo[i] - 1))
			{

				x = (WeaponSelectNo[i] - 1) - 5;
				if (x < 0) {
					x = (WeaponSelectNo[i] - 1);
				}
				break;
			}
		}

		if (WeaponSelectNo[i] != NULL)		//スキルがセットされたときにスキルを表示
			m_pSprite->Draw(m_pImageWeapon, SetWeaponPosx + (SetSetWeaponPosyRatio)*i, SetWeaponPosy, nWidth*x, nHeight*y, nWidth, nHeight, nWidthScale, nHeightScale);

		m_dwCntTime = 0;

	}
	//--セットされているスキル欄のセレクト
	for (int i = 0; i < WeaponSet; i++)
	{
		if (CheckMousePos(SetWeaponPosx + (SetSetWeaponPosyRatio)*i, SetWeaponPosy, nWidthScale, nHeightScale))
		{
			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (i)
				{
				case 0:
					nNo2 = i;     // マウスカーソルがキャラクタースプライト内にある
					break;

				case 1:
					nNo2 = i;     // マウスカーソルがキャラクタースプライト内にある
					break;

				case 2:
					nNo2 = i;     // マウスカーソルがキャラクタースプライト内にある

					break;

				}
				m_dwCntTime = 0;
				bRet = TRUE;

			}
		}

	}


	return bRet;

}

//------------------------------------------------------------------------
//
//	スキル一覧の表示と処理	
//
//
//------------------------------------------------------------------------
BOOL CTitleProc::SkillList(const int nWidth, const int nHeight, BOOL bSwitchTrigger)
{
	int Line = 0;
	int Column = 0;
	const int nWidthScale = nWidth / 2;
	const int nHeightScale = nHeight / 2;
	const int WeaponPosx = nWidth - 170;				//スキルの位置X座標
	const int WeaponPosy = nHeightScale - 10;			//スキルの位置Y座標
	const int WeaponInterPosx = nWidthScale + 30;		//スキルごとの間隔X座標
	const int WeaponInterPosy = nHeightScale + 40;		//スキルごとの間隔Y座標
	const int WeaponConSrcx = 10;						//スキルの後ろ画像パターン左上X座標
	const int WeaponConSrcy = 480;						//スキルの後ろ画像パターン左上Y座標
	const int WeaponConSrcWidth = 290;					//スキルの後ろ画像横幅
	const int WeaponConSrcHeight = 290;					//スキルの後ろ画像縦幅
	BOOL bRet= bSwitchTrigger;
	//--スキルの種類表示
	for (int i = 0; i < WeaponNum; i++)
	{
		//なん行のなん列目にあるかの設定		
		int x = i;
		int y = 0;
		if (i % 5 == 0 && i != 0)
		{
			Line++;
			Column = 0;
		}
		x = Column;
		y = Line;

		m_pSprite->Draw(m_pImageConstruction, WeaponPosx + (WeaponInterPosx)*x, WeaponPosy + (WeaponInterPosy)*y, WeaponConSrcx, WeaponConSrcy, WeaponConSrcWidth, WeaponConSrcHeight, nWidthScale, nHeightScale);
		m_pSprite->Draw(m_pImageWeapon, WeaponPosx + (WeaponInterPosx)*x, WeaponPosy + (WeaponInterPosy)*y, nWidth*x, nHeight*y, nWidth, nHeight, nWidthScale, nHeightScale);

		m_dwCntTime = 0;
		Column++;
	}

	Line = 0;
	Column = 0;
	//--スキルの種類をスキル欄にセット
	for (int i = 0; i < WeaponNum; i++)
	{
		int x = i;
		int y = 0;
		if (i % 5 == 0 && i != 0)
		{
			Line++;
			Column = 0;
		}

		x = Column;
		y = Line;

		if (CheckMousePos(WeaponPosx + (WeaponInterPosx)*x, WeaponPosy + (WeaponInterPosy)*y, nWidthScale, nHeightScale))
		{


			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (i)
				{
				case 0:						//--スキル１をセット
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;
					break;

				case 1:						//--スキル２をセット
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;


					break;

				case 2:						//--スキル３をセット
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;

					break;

				case 3:						//--スキル４をセット
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;

					break;

				case 4:						//--スキル５をセット
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;

					break;
				case 5:						//--スキル６をセット
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;

					break;
				case 6:						//--スキル7をセット
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;

					break;

				default:
					WeaponSelectNo[nNo2] = 0;
					break;
				}
				ClickWeaponNo = i;		//クリックしたスキルのナンバー
				m_dwCntTime = 0;
				bRet = TRUE;

			}


		}
		m_dwCntTime = 0;
		Column++;

	}

	return bRet;
	
}
//------------------------------------------------------------------------
//
//	ゲームクリヤーの表示	
//
//
//------------------------------------------------------------------------
void CTitleProc::GameClear()
{
	m_pGMain->m_dModeType = TITLEMODE;

	const float fScale = 1.0f;
	const int nWidth = 266, nHeight = 98;

	const int nWidthScale = nWidth+60;
	const int nHeightScale = nHeight;


	const int Posx = (WINDOW_WIDTH / 2) - 140;
	const int Posy = (WINDOW_HEIGHT / 2) + 180;

	const int TextPosx= Posx+63, TextPosy= Posy+21;
	const int TextSize = 60;

	// 表示
	m_pSprite->Draw(m_pImageTitlePro, 0, 0, 0, 0, m_pImageTitlePro->m_dwImageWidth, m_pImageTitlePro->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pGMain->m_pFont->Draw((WINDOW_WIDTH/2)-(90*2), 83, _T("RESULT"), 110, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
	m_pGMain->m_pFont->Draw((WINDOW_WIDTH / 2) - (90 * 2), 80, _T("RESULT"), 110, RGB(0, 0, 255), 1.0f, _T("メイリオ ボールド"));

	// スコアの表示
	m_pSprite->Draw(m_pImageClearScore, WINDOW_WIDTH / 2 - 407, 173+20, 10, 10, 814, 380);

	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 120, WINDOW_HEIGHT / 2 - 138 , _T("SCORE"), 70, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
	TCHAR str[256];
	_stprintf(str, _T("%09d"), m_pGMain->m_nScore);
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 180, WINDOW_HEIGHT / 2 - 108 + 50, str, 110, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));


	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 120, WINDOW_HEIGHT / 2 - 138+200, _T("HIGHT SCORE"), 45, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
	TCHAR str2[256];
	_stprintf(str2, _T("%09d"), m_pGMain->m_nHighScore);
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 180+100, WINDOW_HEIGHT / 2 - 108 +220, str2, 40, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));



	if (ButtonCreate(_T("PLAY AGAIN"), fScale, nWidth, nHeight, Posx+200, Posy+20,TextPosx+170, TextPosy+20, TextSize))	// --2021,12,15,11:30

	{
		if (m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON))
		{
			m_pGMain->m_pMapProc->LoadMap1();
			m_pGMain->m_pMapSubProc->LoadMap1();	
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponNo(0);		//スキルナンバーの初期化	
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColuman(0);		//スキル欄の初期化	
			m_pGMain->m_pPcProc->GetPcObjPtr()->Init();
			m_pGMain->m_pEnmProc->m_pEnmBallProc->SetHitNum(0);
			MapAllInit();							
			m_pGMain->m_dModeType = MAINMODE;
			m_pGMain->m_dwGameStatus = GAMEMAIN;
			for (int i = 0; i < 3; i++)
			{
				WeaponSelectNo[i] = WeaponSelectNoSave[i];		//編成したスキルをセット	
			}

			for (int i = 0; i < 3; i++) {
				m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->ResetWeaponWaitTime(i);
			}
			m_dwCntTime = 0;
		}
	}

	if (ButtonCreate(_T("END"), fScale, nWidth, nHeight, Posx-240, Posy+20, TextPosx-270, TextPosy+20,TextSize))

	{
		if (m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON))
		{
			//m_pGMain->m_pBgm1->Stop();
			m_dwStatusPhase = TITLE_MODESELECT_MAINMODE;
			m_pGMain->m_dwGameStatus = TITLE;
		}
	}


}

//------------------------------------------------------------------------
//
//	ゲームクリヤーの表示	
//
//
//------------------------------------------------------------------------
void CTitleProc::MultiBattleGameClear()
{
	m_pGMain->m_dModeType = TITLEMODE;

	const float fScale = 1.0f;
	const int nWidth = 266, nHeight = 98;

	const int nWidthScale = nWidth + 60;
	const int nHeightScale = nHeight;


	const int Posx = (WINDOW_WIDTH / 2) - 140;
	const int Posy = (WINDOW_HEIGHT / 2) + 180;

	const int TextPosx = Posx + 63, TextPosy = Posy + 21;
	const int TextSize = 60;

	// 表示
	m_pSprite->Draw(m_pImageTitlePro, 0, 0, 0, 0, m_pImageTitlePro->m_dwImageWidth, m_pImageTitlePro->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pGMain->m_pFont->Draw((WINDOW_WIDTH / 2) - (90 * 2), 83, _T("RESULT"), 110, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
	m_pGMain->m_pFont->Draw((WINDOW_WIDTH / 2) - (90 * 2), 80, _T("RESULT"), 110, RGB(0, 0, 255), 1.0f, _T("メイリオ ボールド"));

	// スコアの表示
	m_pSprite->Draw(m_pImageClearScore, WINDOW_WIDTH / 2 - 407, 173 + 20, 10, 10, 814, 380);

	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 120, WINDOW_HEIGHT / 2 - 138, _T("WINNER"), 70, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));

	if(m_pGMain->m_nScore > m_pGMain->m_nScoreSec)m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 193, WINDOW_HEIGHT / 2 - 58, _T("PLAYER1"), 110, RGB(0, 0, 255), 1.0f, _T("メイリオ ボールド"));
	if (m_pGMain->m_nScore < m_pGMain->m_nScoreSec)m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 193, WINDOW_HEIGHT / 2 - 58, _T("PLAYER2"), 110, RGB(255, 0, 0), 1.0f, _T("メイリオ ボールド"));
	if (m_pGMain->m_nScore == m_pGMain->m_nScoreSec)m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 110, WINDOW_HEIGHT / 2 - 58, _T("DRAW"), 110, RGB(0, 255, 0), 1.0f, _T("メイリオ ボールド"));


	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 120, WINDOW_HEIGHT / 2 - 138 + 200, _T("SCORE"), 45, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
	TCHAR str2[256];
	_stprintf(str2, _T("%08d"), m_pGMain->m_nScore);
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 180 + 100, WINDOW_HEIGHT / 2 - 108 + 220, str2, 40, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 180 -60, WINDOW_HEIGHT / 2 - 108 + 220, _T("PLAYER1 :"), 40, RGB(0, 0, 255), 1.0f, _T("メイリオ ボールド"));
	_stprintf(str2, _T("%08d"), m_pGMain->m_nScoreSec);
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 180 + 430, WINDOW_HEIGHT / 2 - 108 + 220, str2, 40, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 180 +270, WINDOW_HEIGHT / 2 - 108 + 220, _T("PLAYER2 :"), 40, RGB(255, 0, 0), 1.0f, _T("メイリオ ボールド"));



	if (ButtonCreate(_T("PLAY AGAIN"), fScale, nWidth, nHeight, Posx + 200, Posy + 20, TextPosx + 170, TextPosy + 20, TextSize))	// --2021,12,15,11:30

	{
		if (m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON))
		{
			m_pGMain->m_pMapProc->LoadMapMulti();
			m_pGMain->m_pMapSubProc->LoadMap1();	
			MapAllInit();							
			m_pGMain->m_dModeType = MULTI;
			m_pGMain->m_dwGameStatus = GAMEMULTI;
			for (int i = 0; i < 3; i++)
			{
				WeaponSelectNo[i] = WeaponSelectNoSave[i];		//編成したスキルをセット
			}

			for (int i = 0; i < 3; i++) {
				m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->ResetWeaponWaitTime(i);
			}
			m_dwCntTime = 0;
		}
	}

	if (ButtonCreate(_T("END"), fScale, nWidth, nHeight, Posx - 240, Posy + 20, TextPosx - 270, TextPosy + 20, TextSize))

	{
		if (m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON))
		{
			//m_pGMain->m_pBgm1->Stop();
			m_dwStatusPhase = TITLE_MODESELECT_MULTI;
			m_pGMain->m_dwGameStatus = TITLE;
		}
	}


}


//------------------------------------------------------------------------
//
// マウスカーソルが指定した矩形内にあるかどうかを判定する
//
// 引数  int nPosX,  int nPosY     矩形左上座標
//       int nWidth, int nHeight   矩形の幅と高さ
//
// 戻り値  BOOL  TRUE:矩形内にある    FALSE:矩形内に無い
//
//------------------------------------------------------------------------
BOOL CTitleProc::CheckMousePos(int nPosX, int nPosY, int nWidth, int nHeight)
{
	POINT MPos = m_pGMain->m_pDI->GetMousePos();
	if (MPos.x >= nPosX && MPos.x <= nPosX + nWidth &&
		MPos.y >= nPosY && MPos.y <= nPosY + nHeight)
	{
		return TRUE;  // 矩形内にある
	}
	else {
		return FALSE;  // 矩形内に無い
	}
}

//---------------------------------------------------------------------------
//ボタンの設置
//
//
//引数		TCHAR* PName　文字
//			const float fScale　イメージ大きさ倍率
//			const int nWidth, const int nHeight　元の大きさ
//			const int Posx, const int Posy　配置する場所
//			const int TextPosx, const int TextPosy　文字の場所
//			const int TextSize	文字の大きさ
//
//---------------------------------------------------------------------------
BOOL CTitleProc::ButtonCreate(TCHAR* PName, const float fScale,  const int nWidth, const int nHeight, const int Posx, const int Posy, const int TextPosx, const int TextPosy,const int TextSize)
{



	const int nWidthScale = 60+nWidth * fScale;
	const int nHeightScale = nHeight * fScale;


	if (CheckMousePos(Posx, Posy , nWidthScale, nHeightScale))
	{
			// 選択中のキャラ
			m_pSprite->Draw(m_pImageSelect, Posx, Posy , 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(TextPosx, TextPosy, PName, TextSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(TextPosx, TextPosy, PName, TextSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));
			return TRUE;
	}
	else 
	{
			m_pSprite->Draw(m_pImageSelect, Posx, Posy , 0, 0, nWidth, nHeight, nWidthScale, nHeightScale,0.8);
			m_pGMain->m_pFont->Draw(TextPosx , TextPosy, PName, TextSize, RGB(0, 0, 0), 0.5f, _T("メイリオ ボールド"));
			m_pGMain->m_pFont->Draw(TextPosx, TextPosy, PName, TextSize, RGB(255, 255, 255), 0.8, _T("メイリオ ボールド"));
			return FALSE;
	}
	



}
//--------------------------------------------------------------------------------
//スキル欄に設定
//
//
//--------------------------------------------------------------------------------
BOOL CTitleProc::WeaponSetColuman(int nWeapon, int nColuman)
{
	BOOL bRet = FALSE;

	switch (nColuman)
	{
	case 0:
		WeaponSelectNo[nColuman] = nWeapon + 1;


		break;
	case 1:
		WeaponSelectNo[nColuman] = nWeapon + 1;

		break;
	case 2:
		WeaponSelectNo[nColuman] = nWeapon + 1;

		break;


	}
	bRet = TRUE;  // 終了

	return bRet;

}
//------------------------------------------------------------------------------
//CSVファイルのエクセルを読み込み
//
//
//
//------------------------------------------------------------------------------

void CTitleProc::FileTextRead()
{
	fopen_s(&fp, fname, "r"); // ファイルを開く。失敗するとNULLを返す。
	int i = 0;
	int j = 0;
	bool check = false;
	int Text_count = 0;
	int Sentence_count = 0;

	while ((chr2 = fgetc(fp)) != EOF) {
		if (chr2 == '"') {
			if (check != true) check = true;
			else if (check != false) check = false;
		}

		if (chr2 == ',') {
			chr[i][j] = '\0';
			//printf("%s", chr[i]);
			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, Sentence[Text_count][Sentence_count], (sizeof Sentence) / 2);
			Text_count++;
			i++;
			j = 0;
			Sentence_count = 0;
		}
		else if (check != true && chr2 == '\n') {
			chr[i][j] = '\0';
			//printf("%s", chr[i]);
			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, Sentence[Text_count][Sentence_count], (sizeof Sentence[Text_count][Sentence_count]) / 2);
			Text_count++;
			i++;
			j = 0;
			Sentence_count = 0;
		}
		else if (check != false && chr2 == '\n') {

			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, Sentence[Text_count][Sentence_count], (sizeof Sentence[Text_count][Sentence_count]) / 2);
			Sentence_count++;
			memset(chr[i], '\0', sizeof(chr[i]));
			j = 0;
		}
		else {
			//printf("%c", chr2);
			if (chr2 == '"') {

			}
			else {
				chr[i][j] = chr2;
				j++;
			}
		}
	}
	fclose(fp); // ファイルを閉じる




}


//------------------------------------------------------------------------------
//ゲーム開始時ローカル変数の初期化
//
//
//
//------------------------------------------------------------------------------

void CTitleProc::MapAllInit()
{
	//背景
	m_pGMain->m_pBackForeProc->TutorialTextInit();
	//敵
	m_pGMain->m_pEnmProc->m_pEnmBallProc->SetHitNum(0);
	//スキル
	m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->SetUseNumWeapon(0);
	m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr()->SetUseNumWeapon(0);
	for (int i = 0; i < 3; i++) {
		m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->SetWeaponWaitTime(i,0);
		m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr()->SetWeaponWaitTime(i, 0);
	}
	//プレイヤー
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetUseNumSkill(0);
	m_pGMain->m_pPcProc->GetPcObjPtr()->Init();
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponNo(0);		//スキルナンバーの初期化	
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColuman(0);		//スキル欄の初期化	
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetStop(TRUE);
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetUseNumSkill(0);
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->Init();
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetWeaponNo(0);		//スキルナンバーの初期化	
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetWeaponColuman(0);		//スキル欄の初期化	
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetStop(TRUE);

}

//------------------------------------------------------------------------------
//敵のナビゲーションをセット
//
//
//
//------------------------------------------------------------------------------

void CTitleProc::SetEnmNav()
{
	m_pGMain->m_pEnmProc->m_pEnmBallProc->NavSet();
	m_pGMain->m_pEnmProc->m_pEnmTargetProc->NavSet();
	m_pGMain->m_pEnmProc->m_pEnmMoveTargetProc->NavSet();
	m_pGMain->m_pEnmProc->m_pEnmShieldProc->NavSet();
	m_pGMain->m_pEnmProc->m_pEnmWallProc->NavSet();
	m_pGMain->m_pEnmProc->m_pEnmBendProc->NavSet();
	m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->NavSet();

}
