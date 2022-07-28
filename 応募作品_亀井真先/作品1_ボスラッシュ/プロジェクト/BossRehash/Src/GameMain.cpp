//=============================================================================
//
//		�Q�[�����C������
//																GameMain.cpp
//=============================================================================

#include "GameMain.h"
#include "Playchar.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Effect.h"
#include "BackFore.h"
#include "Map.h"
#include "Title.h"

//------------------------------------------------------------------------
//
//	�Q�[�����C���N���X�̃R���X�g���N�^	
//
//  �����@CMain*	pMain
//
//------------------------------------------------------------------------
CGameMain::CGameMain(CMain*	pMain)
{
	ZeroMemory(this, sizeof(CGameMain));
	m_pMain = pMain;
}
//------------------------------------------------------------------------
//
//	�Q�[�����C���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CGameMain::~CGameMain()
{

	SAFE_DELETE(m_pTitleProc);
	SAFE_DELETE(m_pMapProc);
	SAFE_DELETE(m_pForeProc);
	SAFE_DELETE(m_pEffectProc);
	SAFE_DELETE(m_pWeaponProc);
	SAFE_DELETE(m_pEnmProc);
	SAFE_DELETE(m_pPcProc);

	SAFE_DELETE(m_pSePower);
	SAFE_DELETE(m_pSeShot);
	SAFE_DELETE(m_pSeHit);
	SAFE_DELETE(m_pBgm1);

	SAFE_DELETE(m_pImageChar);
	SAFE_DELETE(m_pImageSprite);

	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDI);
	SAFE_DELETE(m_pXAudio);
	SAFE_DELETE(m_pD3D);

	CoUninitialize();   // COM�̉��
}


//------------------------------------------------------------------------
//
//	�A�v���P�[�V�����̏���������	
//
//  �����@�Ȃ�
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CGameMain::Init()
{
	// �b�n�l�̏�����
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);
	CoInitialize( NULL );

	// Direct3D�̏�����
	m_pD3D = new CDirect3D;
	if (FAILED(m_pD3D->InitD3D(m_pMain->m_hWnd, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("Direct3D���������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// �V�F�[�_�[�̏�����
	m_pShader = new CShader(m_pD3D);
	if (FAILED(m_pShader->InitShader())) {
		MessageBox(0, _T("Shader�𐶐��E�������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// XAudio2�̏�����
	m_pXAudio = new CXAudio;
	if (FAILED(m_pXAudio->InitAudio(m_pMain->m_hWnd))) {
		MessageBox(0, _T("XAudio2���������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// DirectInput�̏�����
	m_pDI = new CDirectInput;
	if (FAILED(m_pDI->StartDirectInput(m_pMain->m_hInstance, m_pMain->m_hWnd,
		INIT_KEYBOARD | INIT_MOUSE | INIT_JOYSTICK, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("DirectInput���������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// �t�H���g�e�N�X�`���[�̏�����
	m_pFont = new CFontTexture(m_pShader);

	// �t�H���g���X�v���C�g�p�̃V�F�[�_�[�̃Z�b�g
	// �ŏ���1�񂾂��V�F�[�_�[�̃Z�b�g������B�r���ŃV�F�[�_�[�̕ύX�͂Ȃ����߁B
	m_pFont->SetShader();


	// ----------------------------------------------------------------------------------------
	// �X�v���C�g�C���[�W�̃��[�h
	m_pImageChar   = new CSpriteImage(m_pShader, _T("Data/Image/char1_P.png"));   // �L�����N�^�[�C���[�W�̃��[�h
	m_pImageChar2 = new CSpriteImage(m_pShader, _T("Data/Image/char1ver2_P.png"));   // �L�����N�^�[�C���[�W�̃��[�h
	m_pImageSprite = new CSpriteImage(m_pShader, _T("Data/Image/sprite1.png")); // �X�v���C�g�C���[�W�̃��[�h
	m_pImageSprite2 = new CSpriteImage(m_pShader, _T("Data/Image/sprite2.png")); // �X�v���C�g�C���[�W�̃��[�h
	m_pImageSprite3 = new CSpriteImage(m_pShader, _T("Data/Image/sprite2ver2.png")); // �X�v���C�g�C���[�W�̃��[�h
	m_pImageSprite4 = new CSpriteImage(m_pShader, _T("Data/Image/sprite1ver2.png")); // �X�v���C�g�C���[�W�̃��[�h

	// �v���V�[�W���̏�����
	m_pPcProc   = new CPcProc(this);
	m_pEnmProc  = new CEnmProc(this);
	m_pWeaponProc  = new CWeaponProc(this);
	m_pEffectProc  = new CEffectProc(this);
	m_pForeProc = new CForeProc(this);
	m_pMapProc  = new CMapProc(this);
	m_pTitleProc = new CTitleProc(this);

	// �T�E���h
	m_pSePower = new CXAudioSource(m_pXAudio, _T("Data/Sound/PowerUp2.wav"));
	m_pSeHit = new CXAudioSource(m_pXAudio, _T("Data/Sound/Damage.wav"), 5);
	m_pSeShot = new CXAudioSource(m_pXAudio, _T("Data/Sound/MainShot.wav"), 10);
	m_pBgm1 = new CXAudioSource(m_pXAudio, _T("Data/Sound/bgm.mp3"));

	// �Q�[���ϐ��̏�����
	m_dwGameStatus = TITLE;
	// �X�N���[�����W�̏�����
	m_vScroll = VECTOR2(0, 0);

	return S_OK;
}

//------------------------------------------------------------------------
//
//	�A�v���P�[�V�����̃��C�����[�v����	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CGameMain::Loop()
{

	m_pDI->GetInput();			// ���͏��̎擾
	m_pFont->Refresh();         // �t�H���g���̃��t���b�V��

	if (m_pDI->CheckKey(KD_TRG, DIK_F4))  ChangeScreenMode();   // �t���X�N���[���̐؂�ւ�       // -- 2018.12.14

	switch (m_dwGameStatus)
	{
		case TITLE:				// �Q�[���J�n�^�C�g��
			m_pTitleProc->Title();
			break;

		case GAMEMAIN:			// �Q�[���又��
			GameMain();
			break;

		case GAMECLEAR:			// �Q�[���N�����[����
			m_pTitleProc->GameClear();
			break;

		case GAMEOVER:			// �Q�[���I�[�o�[����
			m_pTitleProc->GameOver();
			break;

		case GAMEEND:			// �Q�[���I��
			PostQuitMessage(0);
			break;
	}

	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	m_pD3D->m_pSwapChain->Present(0, 0);

}

//------------------------------------------------------------------------
//
//	�Q�[���̃��C������	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CGameMain::GameMain()
{

	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	float ClearColor[4] = { 0,0,1,1 };// �N���A�F�쐬�@RGBA�̏�
	m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A

	// �v���V�[�W���̍X�V
	m_pMapProc->Update();		// �}�b�v�v���V�[�W���̍X�V
	m_pPcProc->UpdateAll();		// �o�b�v���V�[�W���̍X�V
	m_pEnmProc->UpdateAll();	// �G�v���V�[�W���̍X�V
	m_pWeaponProc->UpdateAll();	// ����v���V�[�W���̍X�V
	m_pEffectProc->UpdateAll();	// �f�����ʃv���V�[�W���̍X�V

	m_pMapProc->Update2();		// �}�b�v�v���V�[�W���̍X�V2
	m_pForeProc->Update();		// �O�i�v���V�[�W���̍X�V

	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	m_pD3D->m_pSwapChain->Present(0, 0);

}

//------------------------------------------------------------------------
//
//	�A�v���P�[�V�����̏I������	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CGameMain::Quit()
{

}


//------------------------------------------------------------------------    // -- 2018.12.14
//
//	�E�B���h�E���[�h�ƃt���X�N���[�����[�h��؂�ւ��鏈��	
//
//  �����@���[�h  0:�E�C���h�E���[�h�@1:�t���X�N���[���@-1:���[�h�؂�ւ��i�ȗ��l�j
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
HRESULT CGameMain::ChangeScreenMode(int nMode)
{
	HRESULT Ret = S_OK;
	BOOL bFullScreen;  // �t���X�N���[�����[�h���H

	//	���݂̃X�N���[�����[�h�𓾂�
	m_pD3D->m_pSwapChain->GetFullscreenState(&bFullScreen, NULL);

	switch (nMode)
	{
	case 0:    // �E�C���h�E���[�h�ɂ���
		if( bFullScreen ) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, NULL);
		break;
	case 1:    // �t���X�N���[�����[�h�ɂ���
		if( !bFullScreen ) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, NULL);
		break;
	default:   // ���݂̃��[�h��؂�ւ���
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

