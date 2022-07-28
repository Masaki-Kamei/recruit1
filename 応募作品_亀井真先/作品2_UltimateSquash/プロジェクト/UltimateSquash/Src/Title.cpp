//=============================================================================
//		�^�C�g���E�Q�[���N�����[�E�Q�[���I�[�o�[�̏���
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
// �^�C�g���v���V�[�W���̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CTitleProc::CTitleProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;

	m_pImageTitle = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/TITLE_4_Ver2.png")); // �C���[�W�̃��[�h
	m_pImageClearScore = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Result.png")); // �C���[�W�̃��[�h
	m_pImageSelect = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Button_Ver4_3.png")); // �C���[�W�̃��[�h
	m_pSprite = new CSprite(m_pGMain->m_pShader); // �X�v���C�g�̐���

	m_pImageTitlePro = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/back_Ver2.png")); // �C���[�W�̃��[�h
	m_pImageConstruction = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Construction_Pro3.png"));
	m_pImageConstructionFrame = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Construction_Pro.png"));
	m_pImageWeapon = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/WeaponTest.png"));

	m_pImageTextBackPro = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Text_Back_Ver2.png"));	

	//�G�N�Z���̃e�L�X�g�������Ă���
	FileTextRead();

	nNo=nNoOld=0;

	m_dwCntTime = 0;

}
// ---------------------------------------------------------------------------
//
// �^�C�g���^�C�g���v���V�[�W���̃f�X�g���N�^
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
//	�^�C�g���̕\��  �S��	
//
//------------------------------------------------------------------------
void CTitleProc::Title()
{
	WeaponNum = 7;

	switch (m_dwStatusPhase)
	{
	case 0:

		// �t���X�N���[���ɂ���(�Ȃ���1�x�������Ɩ߂��Ă��܂��̂ŁA�ēx�t���X�N���[���ɂ���)
		//m_pGMain->ChangeScreenMode(1);
		TitleStart();
		break;
	case TITLE_MAIN:  //�^�C�g���\��
		//	�^�C�g����ʂ̕\��	
		TitleMain();
		break;

	case TITLE_MODESELECT:    // �t�F�[�Y�P  �L�����N�^�[�Z���N�g

		//	���[�h�Z���N�g	
		TitleModeSelect();
		break;
	case TITLE_MODESELECT_MAINMODE:

//	���C�����[�h�Z���N�g	
		TitleModeSelectMainMode();
		break;
	case TITLE_CONSTRUCTION:

//	�f�b�L�Z���N�g	
		TitleConstruction();
		break;
	case TITLE_MODESELECT_TUTORIAL:
		//	�`���[�g���A���Z���N�g	
		TitleModeSelectTutorialMode();
		break;

	case TITLE_MODESELECT_MULTI:

		//	�}���`�Z���N�g
		TitleModeSelectMultiMode();
		break;
	case TITLE_MODESELECT_MULTIBATTLE:

		//	�}���`�Z���N�g
		TitleModeSelectMultiBattleMode();
		break;

	}
	m_dwCntTime = 0;

}

//------------------------------------------------------------------------
//
//	�X�^�[�g�^�C�g���̕\��	
//
//------------------------------------------------------------------------
BOOL CTitleProc::TitleStart()
{
	BOOL bRet = FALSE;
	m_pGMain->m_dModeType = TITLEMODE;

	TCHAR PName[][50] = {
	_T("PLESS MOUSE CLICK TO START"),
	};

	// �\��
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	const int StartTextPosX = WINDOW_WIDTH / 2 - 250;
	const int StartTextPosY = WINDOW_HEIGHT - 240;
	const int StartTextSize = 50;

	m_pGMain->m_pFont->FreamDraw(StartTextPosX, StartTextPosY, PName[0], StartTextSize, RGB(0, 0, 0), StartTextAlpha, _T("���C���I �{�[���h"));
	m_pGMain->m_pFont->Draw(StartTextPosX, StartTextPosY, PName[0], StartTextSize, RGB(255, 255, 255), StartTextAlpha, _T("���C���I �{�[���h"));

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
//	���C���^�C�g���̕\��	
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

	const int nNum = sizeof(PName) / sizeof(PName[0]);   // �z��v�f��
	const float fScale = 3.0f;
	const int nStartX = 266, nStartY = 98;
	const int nWidth = 266, nHeight =98;

	const int nWidthScale = nWidth + 60;
	const int nHeightScale = nHeight;

	const int Posx = (WINDOW_WIDTH/2)- (nWidthScale/2);
	const int Posy = (WINDOW_HEIGHT / 2)+40;


	// �\��
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);


	// �L�[�ƃp�b�g�ɂ��L�����N�^�[�Z���N�g
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_DOWN) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_RIGHT))
	{
		if (nNo < nNum - 1) nNo++;
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_UP) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_LEFT))
	{
		if (nNo > 0) nNo--;
	}

	const int PosyRatio = (nWidth / 3) + 20;		//�{�^���̐��ɂ���Ă��炷����
	const int ButtonFontPosx = Posx + 33;			//�{�^���̕����̉��ʒu
	const int ButtonFontPosy = Posy + 21;			//�{�^���̕����̏c�ʒu
	const int ButtonFontPointPosx = Posx + 40;		//�I���������̕����̉��ʒu
	const int ButtonFontPointPosy = Posy + 21;		//�I���������̕����̏c�ʒu
	const int FontSize = 60;						//�����̑傫��

	// �}�E�X�ɂ��L�����N�^�[�Z���N�g
	for (int i = 0; i < nNum; i++)
	{

		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // �}�E�X�J�[�\�����L�����N�^�[�X�v���C�g���ɂ���

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);

			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy+(PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + ((nWidth / 3) + 20)*i, PName[i], FontSize, RGB(255, 255,255), 1.0f, _T("���C���I �{�[���h"));

			if ( m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (nNo)
				{
				case 0:
					// �ŏ��̓}�b�v�P�̃��[�h
					m_dwStatusPhase = TITLE_MODESELECT;
					m_dwCntTime = 0;

					break;
				case 1:
					// �ŏ��̓}�b�v�P�̃��[�h
					m_dwStatusPhase = TITLE_MODESELECT_MULTI;
					m_dwCntTime = 0;

					break;


				case 2:
					m_pGMain->m_dwGameStatus = GAMEEND;
					m_dwCntTime = 0;

					break;
				}
				bRet = TRUE;  // �I��
				m_dwCntTime = 0;

			}

		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale,0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("���C���I �{�[���h"));

		}

	}
	return bRet;

}

//------------------------------------------------------------------------
//	���[�h�Z���N�g�̕\��	
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

	const int nNum = sizeof(PName) / sizeof(PName[0]);   // �z��v�f��
	const float fScale = 3.0f;
	const int nStartX = 266, nStartY = 98;
	const int nWidth = 266, nHeight = 98;

	const int nWidthScale = nWidth+60;
	const int nHeightScale = nHeight;
	const int Posx = (WINDOW_WIDTH / 2) - (nWidthScale / 2);
	const int Posy = (WINDOW_HEIGHT / 2) + 40;

	// �\��
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	const int ModeFontPosx = Posx + 20;					//���݂̃��[�h�����̉��ʒu
	const int ModeFontPosy = Posy - 30;					//���݂̃��[�h�����̏c�ʒu
	const int ModeFontSize = 30;						//�����̑傫��

	m_pGMain->m_pFont->FreamDraw(ModeFontPosx, ModeFontPosy, _T("SOLO"), ModeFontSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	m_pGMain->m_pFont->Draw(ModeFontPosx, ModeFontPosy, _T("SOLO"), ModeFontSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));

	// �L�[�ƃp�b�g�ɂ��L�����N�^�[�Z���N�g
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_DOWN) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_RIGHT))
	{
		if (nNo < nNum - 1) nNo++;
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_UP) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_LEFT))
	{
		if (nNo > 0) nNo--;
	}

	const int PosyRatio = (nWidth / 3) + 20;		//�{�^���̐��ɂ���Ă��炷����
	const int ButtonFontPosx = Posx + 33;			//�{�^���̕����̉��ʒu
	const int ButtonFontPosy = Posy + 21;			//�{�^���̕����̏c�ʒu
	const int ButtonFontPointPosx = Posx + 40;		//�I���������̕����̉��ʒu
	const int ButtonFontPointPosy = Posy + 21;		//�I���������̕����̏c�ʒu
	const int FontSize = 60;						//�����̑傫��


	// �}�E�X�ɂ��L�����N�^�[�Z���N�g
	for (int i = 0; i < nNum; i++)
	{
		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // �}�E�X�J�[�\�����L�����N�^�[�X�v���C�g���ɂ���

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));

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
				bRet = TRUE;  // �I��
				m_dwCntTime = 0;

			}
		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale, 0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("���C���I �{�[���h"));

		}

	}
	
	return bRet;

}

//------------------------------------------------------------------------
//	���C�����[�h�̃��[�h�Z���N�g�̕\��	
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

	const int nNum = sizeof(PName) / sizeof(PName[0]);   // �z��v�f��
	const float fScale = 3.0f;
	const int nStartX = 266, nStartY = 98;
	const int nWidth = 266, nHeight = 98;

	const int nWidthScale = nWidth + 60;
	const int nHeightScale = nHeight;
	 
	const int Posx = (WINDOW_WIDTH / 2) - (nWidthScale / 2);
	const int Posy = (WINDOW_HEIGHT / 2) +40;

	// �\��
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	const int ModeFontPosx = Posx + 20;					//���݂̃��[�h�����̉��ʒu
	const int ModeFontPosy = Posy - 30;					//���݂̃��[�h�����̏c�ʒu
	const int ModeFontSize = 30;						//�����̑傫��

	m_pGMain->m_pFont->FreamDraw(ModeFontPosx, ModeFontPosy, _T("MAIN MODE"), ModeFontSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	m_pGMain->m_pFont->Draw(ModeFontPosx, ModeFontPosy, _T("MAIN MODE"), ModeFontSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));


	// �L�[�ƃp�b�g�ɂ��L�����N�^�[�Z���N�g
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_DOWN) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_RIGHT))
	{
		if (nNo < nNum - 1) nNo++;
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_UP) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_LEFT))
	{
		if (nNo > 0) nNo--;
	}


	const int PosyRatio = (nWidth / 3) + 20;		//�{�^���̐��ɂ���Ă��炷����
	const int ButtonFontPosx = Posx + 33;			//�{�^���̕����̉��ʒu
	const int ButtonFontPosy = Posy + 21;			//�{�^���̕����̏c�ʒu
	const int ButtonFontPointPosx = Posx + 40;		//�I���������̕����̉��ʒu
	const int ButtonFontPointPosy = Posy + 21;		//�I���������̕����̏c�ʒu
	const int FontSize = 60;						//�����̑傫��


	// �}�E�X�ɂ��L�����N�^�[�Z���N�g
	for (int i = 0; i < nNum; i++)
	{
		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // �}�E�X�J�[�\�����L�����N�^�[�X�v���C�g���ɂ���

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));

			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (nNo)
				{
				case 0:
					// �ŏ��̓}�b�v�P�̃��[�h
					m_pGMain->m_pMapProc->LoadMap1();
					m_pGMain->m_pMapSubProc->LoadMap1();	
					m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponNo(0);		//�X�L���i���o�[�̏�����	
					m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColuman(0);		//�X�L�����̏�����	
					m_pGMain->m_pPcProc->GetPcObjPtr()->Init();
					m_pGMain->m_pEnmProc->m_pEnmBallProc->SetHitNum(0);
					MapAllInit();								
					m_pGMain->m_dModeType = MAINMODE;
					m_pGMain->m_dwGameStatus = GAMEMAIN;
					for (int i = 0; i < 3; i++)
					{
						WeaponSelectNo[i] = WeaponSelectNoSave[i];		//�Ґ������X�L�����Z�b�g	
						m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColumanNo(i, WeaponSelectNo[i]);

					}

					for (int i = 0; i < 3; i++) {
						m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->ResetWeaponWaitTime(i);
					}
						m_dwCntTime = 0;
					break;

				case 1:
					nNo2 = -1;
					ClickWeaponNo = -1;		//�N���b�N�����X�L���i���o�[�̏�����
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
				bRet = TRUE;  // �I��
				m_dwCntTime = 0;

			}

		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale, 0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("���C���I �{�[���h"));

		}

	}
	//--�n�C�X�R�A�\��	
	int   DestX, DestY;

	DestX = 0;
	DestY = WINDOW_HEIGHT-200;
	TCHAR str[256] = { 0 };

	return bRet;

}

//------------------------------------------------------------------------
//	�`���[�g���A���̃��[�h�Z���N�g�̕\��	
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

	const int nNum = sizeof(PName) / sizeof(PName[0]);   // �z��v�f��
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

	// �\��
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	m_pGMain->m_pFont->FreamDraw(ModeNameTextPosx, ModeNameTextPosy, _T("TUTORIAL"), ModeNameTextSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));

	m_pGMain->m_pFont->Draw(ModeNameTextPosx, ModeNameTextPosy, _T("TUTORIAL"), ModeNameTextSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));


	// �L�[�ƃp�b�g�ɂ��L�����N�^�[�Z���N�g
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_DOWN) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_RIGHT))
	{
		if (nNo < nNum - 1) nNo++;
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_UP) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_LEFT))
	{
		if (nNo > 0) nNo--;
	}


	const int PosyRatio = (nWidth / 3) + 20;		//�{�^���̐��ɂ���Ă��炷����
	const int ButtonFontPosx = Posx + 33;			//�{�^���̕����̉��ʒu
	const int ButtonFontPosy = Posy + 21;			//�{�^���̕����̏c�ʒu
	const int ButtonFontPointPosx = Posx + 40;		//�I���������̕����̉��ʒu
	const int ButtonFontPointPosy = Posy + 21;		//�I���������̕����̏c�ʒu
	const int FontSize = 60;						//�����̑傫��


	// �}�E�X�ɂ��L�����N�^�[�Z���N�g
	for (int i = 0; i < nNum; i++)
	{

		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // �}�E�X�J�[�\�����L�����N�^�[�X�v���C�g���ɂ���

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));

			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (nNo)
				{
				case 0:

					// �ŏ��̓}�b�v3�̃��[�h
					m_pGMain->m_pMapProc->LoadMapTutorial();
					m_pGMain->m_pMapSubProc->LoadMap1();
					m_pGMain->m_pBackForeProc->TutorialTextInit();
					m_pGMain->m_pPcProc->GetPcObjPtr()->Init();
					m_pGMain->m_pEnmProc->m_pEnmBallProc->SetHitNum(0);
					m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponNo(0);		//�X�L���i���o�[�̏�����
					m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColuman(0);		//�X�L�����̏�����	

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
				bRet = TRUE;  // �I��
				m_dwCntTime = 0;

			}

		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale, 0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("���C���I �{�[���h"));

		}

	}



	return bRet;


}

//------------------------------------------------------------------------
//	�}���`���[�h�Z���N�g�̕\��	
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

	const int nNum = sizeof(PName) / sizeof(PName[0]);   // �z��v�f��
	const float fScale = 3.0f;
	const int nStartX = 266, nStartY = 98;
	const int nWidth = 266, nHeight = 98;

	const int nWidthScale = nWidth + 60;
	const int nHeightScale = nHeight;
	const int Posx = (WINDOW_WIDTH / 2) - (nWidthScale / 2);
	const int Posy = (WINDOW_HEIGHT / 2) + 40;

	// �\��
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	const int ModeFontPosx = Posx + 20;					//���݂̃��[�h�����̉��ʒu
	const int ModeFontPosy = Posy - 30;					//���݂̃��[�h�����̏c�ʒu
	const int ModeFontSize = 30;						//�����̑傫��

	m_pGMain->m_pFont->FreamDraw(ModeFontPosx, ModeFontPosy, _T("MULTI"), ModeFontSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	m_pGMain->m_pFont->Draw(ModeFontPosx, ModeFontPosy, _T("MULTI"), ModeFontSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));

	// �L�[�ƃp�b�g�ɂ��L�����N�^�[�Z���N�g
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_DOWN) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_RIGHT))
	{
		if (nNo < nNum - 1) nNo++;
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_UP) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_LEFT))
	{
		if (nNo > 0) nNo--;
	}

	const int PosyRatio = (nWidth / 3) + 20;		//�{�^���̐��ɂ���Ă��炷����
	const int ButtonFontPosx = Posx + 33;			//�{�^���̕����̉��ʒu
	const int ButtonFontPosy = Posy + 21;			//�{�^���̕����̏c�ʒu
	const int ButtonFontPointPosx = Posx + 40;		//�I���������̕����̉��ʒu
	const int ButtonFontPointPosy = Posy + 21;		//�I���������̕����̏c�ʒu
	const int FontSize = 60;						//�����̑傫��


	// �}�E�X�ɂ��L�����N�^�[�Z���N�g
	for (int i = 0; i < nNum; i++)
	{
		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // �}�E�X�J�[�\�����L�����N�^�[�X�v���C�g���ɂ���

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));

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
				bRet = TRUE;  // �I��
				m_dwCntTime = 0;

			}
		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale, 0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("���C���I �{�[���h"));

		}

	}

	return bRet;

}


//------------------------------------------------------------------------
//	�}���`�̃��[�h�Z���N�g�̕\��	
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

	const int nNum = sizeof(PName) / sizeof(PName[0]);   // �z��v�f��
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

	// �\��
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	const int ModeFontPosx = Posx + 20;					//���݂̃��[�h�����̉��ʒu
	const int ModeFontPosy = Posy - 30;					//���݂̃��[�h�����̏c�ʒu
	const int ModeFontSize = 30;						//�����̑傫��

	m_pGMain->m_pFont->FreamDraw(ModeFontPosx, ModeFontPosy, _T("BATTLE"), ModeFontSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	m_pGMain->m_pFont->Draw(ModeFontPosx, ModeFontPosy, _T("BATTLE"), ModeFontSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));


	// �L�[�ƃp�b�g�ɂ��L�����N�^�[�Z���N�g
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_DOWN) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_RIGHT))
	{
		if (nNo < nNum - 1) nNo++;
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_UP) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_LEFT))
	{
		if (nNo > 0) nNo--;
	}


	const int PosyRatio = (nWidth / 3) + 20;		//�{�^���̐��ɂ���Ă��炷����
	const int ButtonFontPosx = Posx + 33;			//�{�^���̕����̉��ʒu
	const int ButtonFontPosy = Posy + 21;			//�{�^���̕����̏c�ʒu
	const int ButtonFontPointPosx = Posx + 40;		//�I���������̕����̉��ʒu
	const int ButtonFontPointPosy = Posy + 21;		//�I���������̕����̏c�ʒu
	const int FontSize = 60;						//�����̑傫��


	// �}�E�X�ɂ��L�����N�^�[�Z���N�g
	for (int i = 0; i < nNum; i++)
	{

		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // �}�E�X�J�[�\�����L�����N�^�[�X�v���C�g���ɂ���

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));

			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (nNo)
				{
				case 0:

					// �ŏ��̓}�b�v3�̃��[�h
					m_pGMain->m_pMapProc->LoadMapMulti();
					m_pGMain->m_pMapSubProc->LoadMap1();	
					m_pGMain->m_pPcProc->GetPcObjPtr()->Init();
					m_pGMain->m_pPcProc->GetPcSecObjPtr()->Init();
					m_pGMain->m_pEnmProc->m_pEnmBallProc->SetHitNum(0);
					m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponNo(0);		//�X�L���i���o�[�̏�����	
					m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColuman(0);		//�X�L�����̏�����
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
				bRet = TRUE;  // �I��
				m_dwCntTime = 0;

			}

		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale, 0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPointPosx, ButtonFontPointPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("���C���I �{�[���h"));

		}

	}



	return bRet;

}


//------------------------------------------------------------------------
//	�f�b�L�Z���N�g�̕\��	
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

	//�X�L���̏ڍׂ̖��O		
	const int WeaponNameTextNum = 20;
	TCHAR WeaponName[][WeaponNameTextNum] = {
	_T("�g�U�{�[��"),
	_T("����{�[��"),
	_T("�ђʃ{�[��"),
	_T("��]�{�[��"),
	_T("�Œ萶��"),
	_T("������΂�"),
	_T("�X�s�[�h�A�b�v"),

	};
	BOOL bSwitchTrigger = FALSE;


	const int nNum = sizeof(PName) / sizeof(PName[0]);   // �z��v�f��
	const int nWeaponNameNum = sizeof(WeaponName) / sizeof(WeaponName[0]);
	const float fScale = 3.0f;
	int nStartX = 266, nStartY = 98;
	int nWidth = 258, nHeight = 258;

	int nWidthScale = nWidth;
	int nHeightScale = nHeight;

	const int Posx = WINDOW_WIDTH-300;
	const int Posy = WINDOW_HEIGHT -100;

	const int WeaponSet = 3;

	int	LineNum = (WeaponNum / 5) + 1;	//�X�L���̑I�𗓂̍s�̐�
	int Line = 0;						//�X�L���̑I�𗓂̍s
	int Column = 0;						//�X�L���̑I�𗓂̗�
	TCHAR *pWeaponName[nWeaponNameNum];
	for (int i = 0; i < nWeaponNameNum; i++) pWeaponName[i] = WeaponName[i];

	// �w�i�\��
	m_pSprite->Draw(m_pImageTitlePro, 0, 0, 0, 0, m_pImageTitlePro->m_dwImageWidth, m_pImageTitlePro->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pSprite->Draw(m_pImageConstruction,60, 30, 10, 10, 814, 414);

	SkillExplanation(nWidth, nHeight, pWeaponName);

	const int PosyRatio = (nWidth / 3) + 20;		//�{�^���̐��ɂ���Ă��炷����
	const int ButtonFontPosx = Posx + 40;			//�{�^���̕����̉��ʒu
	const int ButtonFontPosy = Posy + 21;			//�{�^���̕����̏c�ʒu
	const int ButtonFontPointPosx = Posx + 40;		//�I���������̕����̉��ʒu
	const int ButtonFontPointPosy = Posy + 21;		//�I���������̕����̏c�ʒu
	const int FontSize = 60;						//�����̑傫��

	// �߂�}�E�X�ɂ��{�^���Z���N�g
	for (int i = 0; i < nNum; i++)
	{
		nWidth = 266, nHeight = 98;
		nWidthScale = nWidth;
		nHeightScale = nHeight;

		if (CheckMousePos(Posx, Posy + (PosyRatio)*i, nWidthScale, nHeightScale))
		{
			nNo = i;     // �}�E�X�J�[�\�����L�����N�^�[�X�v���C�g���ɂ���

			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));

			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 1.0, _T("���C���I �{�[���h"));

			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				if (nNo == 0) {
					m_dwStatusPhase = TITLE_MODESELECT_MAINMODE;
					for (int i = 0; i < 3; i++)				//�Ґ������X�L�����Z�b�g
					{
						WeaponSelectNoSave[i] = WeaponSelectNo[i];
					}
					break;
				}

				bRet = TRUE;  // �I��
				m_dwCntTime = 0;
				bSwitchTrigger = TRUE;
			}
		}
		else {
			m_pSprite->Draw(m_pImageSelect, Posx, Posy + (PosyRatio)*i, 0, 0, nWidth, nHeight, nWidthScale, nHeightScale,0.8);
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(0, 0, 0), 0.5f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(ButtonFontPosx, ButtonFontPosy + (PosyRatio)*i, PName[i], FontSize, RGB(255, 255, 255), 0.8, _T("���C���I �{�[���h"));

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
//	�X�L���̐�������
//
//
//------------------------------------------------------------------------
void CTitleProc::SkillExplanation(const int nWidth,const int nHeight,TCHAR **WeaponName)
{
	const int TextBackPosx = 944;									//�������̈ʒuX���W
	const int TextBackPosy = 16;									//�������̈ʒuY���W
	const int TextBackWidthScale = 403;								//�������̉���
	const int TextBackHeightScale = 628;							//�������̏c��
	const int TextBackNamePosx = TextBackPosx + 40;					//�X�L���̖��O�ʒuX���W
	const int TextBackNamePosy = TextBackPosy + 50;					//�X�L���̖��O�ʒuY���W
	const int TextBackNameSize = 70;									//�X�L���̖��O�̃T�C�Y
	const int TextBackImagePosx = TextBackPosx + 70;				//�X�L���̖��O�ʒuX���W
	const int TextBackImagePosy = TextBackPosy + 100;				//�X�L���̖��O�ʒuX���W
	const int TextBackExpPosx = TextBackPosx + 40;					//�X�L���̐����ʒuX���W
	const int TextBackExpPosy = TextBackPosy + nWidth + 100;			//�X�L���̐����ʒuY���W
	const int TextBackExpWhile = 30;									//�s�̐��ɂ���Ă��炷����
	const int TextBackExpSize = 40;									//�X�L���̐����̕����T�C�Y
	int	LineNum = (WeaponNum / 5) + 1;	//�X�L���̑I�𗓂̍s�̐�
	int Line = 0;						//�X�L���̑I�𗓂̍s
	int Column = 0;						//�X�L���̑I�𗓂̗�

	//�X�L���̐���		
	m_pSprite->Draw(m_pImageTextBackPro, TextBackPosx, TextBackPosy, 0, 0, TextBackWidthScale, TextBackHeightScale, TextBackWidthScale, TextBackHeightScale);
	if (ClickWeaponNo >= 0)
	{
		int y = ClickWeaponNo / 5;
		int x = 0;
		for (int i = 0; i < LineNum; i++)
		{
			//�I�������X�L�����I�𗓂̂Ȃ��ڂɂ��邩	
			if (((i + 1) * 5) > ClickWeaponNo)
			{
				x = ClickWeaponNo - 5;
				if (x < 0) {
					x = ClickWeaponNo;
				}
				break;
			}
		}
		m_pGMain->m_pFont->Draw(TextBackNamePosx, TextBackNamePosy, WeaponName[ClickWeaponNo], 70, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));
		m_pSprite->Draw(m_pImageWeapon, TextBackImagePosx, TextBackImagePosy, nWidth*x, nHeight*y, nWidth, nHeight, nWidth, nHeight);		
		for (int i = 0; i < (sizeof(Sentence) / sizeof(*Sentence)); i++) {
			m_pGMain->m_pFont->Draw(TextBackExpPosx, TextBackExpPosy + (TextBackExpWhile*i), Sentence[ClickWeaponNo][i], TextBackExpSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));
		}
	}

}
//------------------------------------------------------------------------
//
//	�X�L���̃Z�b�g
//
//
//------------------------------------------------------------------------
BOOL CTitleProc::SetSkill(const int nWidth, const int nHeight, const int Posx, const int Posy, const int WeaponSet,const int LineNum, BOOL bSwitchTrigger)
{

	const int FreamPos = 272;
	const int nStartX = 250, nStartY = 250;
	const int nWidthScale = nWidth;
	const int nHeightScale = nHeight;
	const int SetSetWeaponPosyRatio = (nWidth + 30);			//�X�L���Z�b�g���̊Ԋu
	const int SetWeaponPosx = nWidth - 200;						//�X�L���Z�b�g����X���W
	const int SetWeaponPosy = Posy - nHeight + 70;				//�X�L���Z�b�g����Y���W
	const int SetWeaponConStartPosx = 0;						//�X�L���Z�b�g���̃p�^�[������X���W
	const int SetWeaponConStartPosy = 0;						//�X�L���Z�b�g���̃p�^�[������X���W
	const int SetWeaponNormalFreamStartPosx = 0;				//�X�L���Z�b�g���g�̃p�^�[������X���W
	const int SetWeaponNormalFreamStartPosy = 300;				//�X�L���Z�b�g���g�̃p�^�[������X���W
	const int SetWeaponPointFreamStartPosx = 300;				//�X�L���Z�b�g���g�i�I�𒆁j�̃p�^�[������X���W
	const int SetWeaponPointFreamStartPosy = 0;					//�X�L���Z�b�g���g�i�I�𒆁j�̃p�^�[������X���W
	BOOL bRet = bSwitchTrigger;

	//--�Z�b�g����Ă���X�L�����̕\��
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
		//�I�������X�L�����I�𗓂̂Ȃ��ڂɂ��邩
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

		if (WeaponSelectNo[i] != NULL)		//�X�L�����Z�b�g���ꂽ�Ƃ��ɃX�L����\��
			m_pSprite->Draw(m_pImageWeapon, SetWeaponPosx + (SetSetWeaponPosyRatio)*i, SetWeaponPosy, nWidth*x, nHeight*y, nWidth, nHeight, nWidthScale, nHeightScale);

		m_dwCntTime = 0;

	}
	//--�Z�b�g����Ă���X�L�����̃Z���N�g
	for (int i = 0; i < WeaponSet; i++)
	{
		if (CheckMousePos(SetWeaponPosx + (SetSetWeaponPosyRatio)*i, SetWeaponPosy, nWidthScale, nHeightScale))
		{
			if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
			{
				switch (i)
				{
				case 0:
					nNo2 = i;     // �}�E�X�J�[�\�����L�����N�^�[�X�v���C�g���ɂ���
					break;

				case 1:
					nNo2 = i;     // �}�E�X�J�[�\�����L�����N�^�[�X�v���C�g���ɂ���
					break;

				case 2:
					nNo2 = i;     // �}�E�X�J�[�\�����L�����N�^�[�X�v���C�g���ɂ���

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
//	�X�L���ꗗ�̕\���Ə���	
//
//
//------------------------------------------------------------------------
BOOL CTitleProc::SkillList(const int nWidth, const int nHeight, BOOL bSwitchTrigger)
{
	int Line = 0;
	int Column = 0;
	const int nWidthScale = nWidth / 2;
	const int nHeightScale = nHeight / 2;
	const int WeaponPosx = nWidth - 170;				//�X�L���̈ʒuX���W
	const int WeaponPosy = nHeightScale - 10;			//�X�L���̈ʒuY���W
	const int WeaponInterPosx = nWidthScale + 30;		//�X�L�����Ƃ̊ԊuX���W
	const int WeaponInterPosy = nHeightScale + 40;		//�X�L�����Ƃ̊ԊuY���W
	const int WeaponConSrcx = 10;						//�X�L���̌��摜�p�^�[������X���W
	const int WeaponConSrcy = 480;						//�X�L���̌��摜�p�^�[������Y���W
	const int WeaponConSrcWidth = 290;					//�X�L���̌��摜����
	const int WeaponConSrcHeight = 290;					//�X�L���̌��摜�c��
	BOOL bRet= bSwitchTrigger;
	//--�X�L���̎�ޕ\��
	for (int i = 0; i < WeaponNum; i++)
	{
		//�Ȃ�s�̂Ȃ��ڂɂ��邩�̐ݒ�		
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
	//--�X�L���̎�ނ��X�L�����ɃZ�b�g
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
				case 0:						//--�X�L���P���Z�b�g
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;
					break;

				case 1:						//--�X�L���Q���Z�b�g
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;


					break;

				case 2:						//--�X�L���R���Z�b�g
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;

					break;

				case 3:						//--�X�L���S���Z�b�g
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;

					break;

				case 4:						//--�X�L���T���Z�b�g
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;

					break;
				case 5:						//--�X�L���U���Z�b�g
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;

					break;
				case 6:						//--�X�L��7���Z�b�g
					WeaponSetColuman(i, nNo2);
					m_dwCntTime = 0;

					break;

				default:
					WeaponSelectNo[nNo2] = 0;
					break;
				}
				ClickWeaponNo = i;		//�N���b�N�����X�L���̃i���o�[
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
//	�Q�[���N�����[�̕\��	
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

	// �\��
	m_pSprite->Draw(m_pImageTitlePro, 0, 0, 0, 0, m_pImageTitlePro->m_dwImageWidth, m_pImageTitlePro->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pGMain->m_pFont->Draw((WINDOW_WIDTH/2)-(90*2), 83, _T("RESULT"), 110, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	m_pGMain->m_pFont->Draw((WINDOW_WIDTH / 2) - (90 * 2), 80, _T("RESULT"), 110, RGB(0, 0, 255), 1.0f, _T("���C���I �{�[���h"));

	// �X�R�A�̕\��
	m_pSprite->Draw(m_pImageClearScore, WINDOW_WIDTH / 2 - 407, 173+20, 10, 10, 814, 380);

	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 120, WINDOW_HEIGHT / 2 - 138 , _T("SCORE"), 70, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	TCHAR str[256];
	_stprintf(str, _T("%09d"), m_pGMain->m_nScore);
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 180, WINDOW_HEIGHT / 2 - 108 + 50, str, 110, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));


	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 120, WINDOW_HEIGHT / 2 - 138+200, _T("HIGHT SCORE"), 45, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	TCHAR str2[256];
	_stprintf(str2, _T("%09d"), m_pGMain->m_nHighScore);
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 180+100, WINDOW_HEIGHT / 2 - 108 +220, str2, 40, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));



	if (ButtonCreate(_T("PLAY AGAIN"), fScale, nWidth, nHeight, Posx+200, Posy+20,TextPosx+170, TextPosy+20, TextSize))	// --2021,12,15,11:30

	{
		if (m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON))
		{
			m_pGMain->m_pMapProc->LoadMap1();
			m_pGMain->m_pMapSubProc->LoadMap1();	
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponNo(0);		//�X�L���i���o�[�̏�����	
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColuman(0);		//�X�L�����̏�����	
			m_pGMain->m_pPcProc->GetPcObjPtr()->Init();
			m_pGMain->m_pEnmProc->m_pEnmBallProc->SetHitNum(0);
			MapAllInit();							
			m_pGMain->m_dModeType = MAINMODE;
			m_pGMain->m_dwGameStatus = GAMEMAIN;
			for (int i = 0; i < 3; i++)
			{
				WeaponSelectNo[i] = WeaponSelectNoSave[i];		//�Ґ������X�L�����Z�b�g	
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
//	�Q�[���N�����[�̕\��	
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

	// �\��
	m_pSprite->Draw(m_pImageTitlePro, 0, 0, 0, 0, m_pImageTitlePro->m_dwImageWidth, m_pImageTitlePro->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pGMain->m_pFont->Draw((WINDOW_WIDTH / 2) - (90 * 2), 83, _T("RESULT"), 110, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	m_pGMain->m_pFont->Draw((WINDOW_WIDTH / 2) - (90 * 2), 80, _T("RESULT"), 110, RGB(0, 0, 255), 1.0f, _T("���C���I �{�[���h"));

	// �X�R�A�̕\��
	m_pSprite->Draw(m_pImageClearScore, WINDOW_WIDTH / 2 - 407, 173 + 20, 10, 10, 814, 380);

	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 120, WINDOW_HEIGHT / 2 - 138, _T("WINNER"), 70, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));

	if(m_pGMain->m_nScore > m_pGMain->m_nScoreSec)m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 193, WINDOW_HEIGHT / 2 - 58, _T("PLAYER1"), 110, RGB(0, 0, 255), 1.0f, _T("���C���I �{�[���h"));
	if (m_pGMain->m_nScore < m_pGMain->m_nScoreSec)m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 193, WINDOW_HEIGHT / 2 - 58, _T("PLAYER2"), 110, RGB(255, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	if (m_pGMain->m_nScore == m_pGMain->m_nScoreSec)m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 110, WINDOW_HEIGHT / 2 - 58, _T("DRAW"), 110, RGB(0, 255, 0), 1.0f, _T("���C���I �{�[���h"));


	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 120, WINDOW_HEIGHT / 2 - 138 + 200, _T("SCORE"), 45, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	TCHAR str2[256];
	_stprintf(str2, _T("%08d"), m_pGMain->m_nScore);
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 180 + 100, WINDOW_HEIGHT / 2 - 108 + 220, str2, 40, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 180 -60, WINDOW_HEIGHT / 2 - 108 + 220, _T("PLAYER1 :"), 40, RGB(0, 0, 255), 1.0f, _T("���C���I �{�[���h"));
	_stprintf(str2, _T("%08d"), m_pGMain->m_nScoreSec);
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 180 + 430, WINDOW_HEIGHT / 2 - 108 + 220, str2, 40, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH / 2 - 407 + 180 +270, WINDOW_HEIGHT / 2 - 108 + 220, _T("PLAYER2 :"), 40, RGB(255, 0, 0), 1.0f, _T("���C���I �{�[���h"));



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
				WeaponSelectNo[i] = WeaponSelectNoSave[i];		//�Ґ������X�L�����Z�b�g
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
// �}�E�X�J�[�\�����w�肵����`���ɂ��邩�ǂ����𔻒肷��
//
// ����  int nPosX,  int nPosY     ��`������W
//       int nWidth, int nHeight   ��`�̕��ƍ���
//
// �߂�l  BOOL  TRUE:��`���ɂ���    FALSE:��`���ɖ���
//
//------------------------------------------------------------------------
BOOL CTitleProc::CheckMousePos(int nPosX, int nPosY, int nWidth, int nHeight)
{
	POINT MPos = m_pGMain->m_pDI->GetMousePos();
	if (MPos.x >= nPosX && MPos.x <= nPosX + nWidth &&
		MPos.y >= nPosY && MPos.y <= nPosY + nHeight)
	{
		return TRUE;  // ��`���ɂ���
	}
	else {
		return FALSE;  // ��`���ɖ���
	}
}

//---------------------------------------------------------------------------
//�{�^���̐ݒu
//
//
//����		TCHAR* PName�@����
//			const float fScale�@�C���[�W�傫���{��
//			const int nWidth, const int nHeight�@���̑傫��
//			const int Posx, const int Posy�@�z�u����ꏊ
//			const int TextPosx, const int TextPosy�@�����̏ꏊ
//			const int TextSize	�����̑傫��
//
//---------------------------------------------------------------------------
BOOL CTitleProc::ButtonCreate(TCHAR* PName, const float fScale,  const int nWidth, const int nHeight, const int Posx, const int Posy, const int TextPosx, const int TextPosy,const int TextSize)
{



	const int nWidthScale = 60+nWidth * fScale;
	const int nHeightScale = nHeight * fScale;


	if (CheckMousePos(Posx, Posy , nWidthScale, nHeightScale))
	{
			// �I�𒆂̃L����
			m_pSprite->Draw(m_pImageSelect, Posx, Posy , 0, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			m_pGMain->m_pFont->FreamDraw(TextPosx, TextPosy, PName, TextSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(TextPosx, TextPosy, PName, TextSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));
			return TRUE;
	}
	else 
	{
			m_pSprite->Draw(m_pImageSelect, Posx, Posy , 0, 0, nWidth, nHeight, nWidthScale, nHeightScale,0.8);
			m_pGMain->m_pFont->Draw(TextPosx , TextPosy, PName, TextSize, RGB(0, 0, 0), 0.5f, _T("���C���I �{�[���h"));
			m_pGMain->m_pFont->Draw(TextPosx, TextPosy, PName, TextSize, RGB(255, 255, 255), 0.8, _T("���C���I �{�[���h"));
			return FALSE;
	}
	



}
//--------------------------------------------------------------------------------
//�X�L�����ɐݒ�
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
	bRet = TRUE;  // �I��

	return bRet;

}
//------------------------------------------------------------------------------
//CSV�t�@�C���̃G�N�Z����ǂݍ���
//
//
//
//------------------------------------------------------------------------------

void CTitleProc::FileTextRead()
{
	fopen_s(&fp, fname, "r"); // �t�@�C�����J���B���s�����NULL��Ԃ��B
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
	fclose(fp); // �t�@�C�������




}


//------------------------------------------------------------------------------
//�Q�[���J�n�����[�J���ϐ��̏�����
//
//
//
//------------------------------------------------------------------------------

void CTitleProc::MapAllInit()
{
	//�w�i
	m_pGMain->m_pBackForeProc->TutorialTextInit();
	//�G
	m_pGMain->m_pEnmProc->m_pEnmBallProc->SetHitNum(0);
	//�X�L��
	m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->SetUseNumWeapon(0);
	m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr()->SetUseNumWeapon(0);
	for (int i = 0; i < 3; i++) {
		m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->SetWeaponWaitTime(i,0);
		m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr()->SetWeaponWaitTime(i, 0);
	}
	//�v���C���[
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetUseNumSkill(0);
	m_pGMain->m_pPcProc->GetPcObjPtr()->Init();
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponNo(0);		//�X�L���i���o�[�̏�����	
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColuman(0);		//�X�L�����̏�����	
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetStop(TRUE);
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetUseNumSkill(0);
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->Init();
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetWeaponNo(0);		//�X�L���i���o�[�̏�����	
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetWeaponColuman(0);		//�X�L�����̏�����	
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetStop(TRUE);

}

//------------------------------------------------------------------------------
//�G�̃i�r�Q�[�V�������Z�b�g
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
