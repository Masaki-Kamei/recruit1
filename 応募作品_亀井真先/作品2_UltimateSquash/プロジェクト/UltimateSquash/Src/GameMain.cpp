//=============================================================================
//
//		�Q�[���̃��C������
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
// CGameMain �Q�[�����C���N���X�̏���
//
// ============================================================================================
//------------------------------------------------------------------------
//
//	�Q�[�����C���N���X�̃R���X�g���N�^	
//
//  �����@�Ȃ�
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
	MyImgui::ImguiQuit();            // MyImgui�̏I������

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

	// �g�D�[���e�N�X�`���ǂݍ���
	if (FAILED(m_pD3D->CreateShaderResourceViewFromFile(_T("Data/Image/ToonPaint.png"), &m_pD3D->m_pToonTexture, 3)))
	{
		MessageBox(NULL, _T("Data/Image/ToonPaint.png"), _T("�g�D�[���e�N�X�`���t�@�C��������܂���"), MB_OK);
		return E_FAIL;
	}

	// �t�H���g�e�N�X�`���[�̏�����
	m_pFont = new CFontTexture(m_pShader);

	// MyImgui�̏�����
	MyImgui::ImguiInit(m_pMain->m_hWnd, m_pD3D, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Fbx���b�V���R���g���[���N���X
	m_pFbxMeshCtrl = new CFbxMeshCtrl(m_pShader); 

	// MPR�̏�����
	m_pMPR = new CMPR(m_pShader);


	// ----------------------------------------------------------------------------------------
	// �ϐ��̏�����
	m_dwGameStatus = TITLE;
	m_vLightDir = normalize( VECTOR3(0.8f, 1, -1) );  // �������W�̏����l�B���K������
	m_vLightDirSecond = normalize(VECTOR3(0.8f, 1, -1));  // �������W�̏����l�B���K������

	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j�̏����l
	//m_mProj = XMMatrixPerspectiveFovLH((FLOAT)(XM_PI / 4), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);
	m_mProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);
	m_mProjSecond = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);


	// �r���[�g�����X�t�H�[���i���_���W�ϊ��j�̏����l
	VECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//����ʒu
	m_vEyePt = VECTOR3(0.0f, 1.0f, 0.0f);
	m_vLookatPt = VECTOR3(0.0f, 1.0f, 1.0f);
	m_mView = XMMatrixLookAtLH(m_vEyePt, m_vLookatPt, vUpVec);

	m_vEyePtSecond = VECTOR3(0.0f, 1.0f, 0.0f);
	m_vLookatPtSecond = VECTOR3(0.0f, 1.0f, 1.0f);
	m_mViewSecond = XMMatrixLookAtLH(m_vEyePtSecond, m_vLookatPtSecond, vUpVec);


	// �e�v���V�[�W���̏�����
	m_pPcProc = new CPcProc(this);		// �o�b�v���V�[�W��

	m_pCameraProc = new CCameraProc(this);	// �J�����v���V�[�W��


	m_pEnmProc = new CEnmProc(this);	// �G�v���V�[�W��


	m_pEffectProc = new CEffectProc(this);  // �R�c����

	m_pWeaponProc = new CWeaponProc(this);	// Weapon�v���V�[�W��

	m_pMapProc = new CMapProc(this);	// Map�v���V�[�W��


	m_pMapSubProc = new CMapSubProc(this);	// Map�v���V�[�W��


	m_pBackForeProc = new CBackForeProc(this);  // �O�i�E�w�i

	m_pTitleProc = new CTitleProc(this);  // �^�C�g���B�Q�[���N�����[�B�Q�[���I�[�o�[

	m_pRenderBufProc = new CRenderBufProc(this);  // �`��o�b�t�@ 



	//--�Z�[�u�f�[�^���[�h
	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, "Data/Read/Save.dat", "rb"); // �t�@�C�����J��
	if (fp == NULL) { // NULL���Ԃ��Ă�����G���[����
	}
	else {
		fread(&m_nHighScore, sizeof(int), 1, fp);
		fclose(fp); //�t�@�C�������

	}



	return S_OK;
}

//------------------------------------------------------------------------
//
//	�Q�[���̃��[�v����	
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
	MyImgui::ImguiNewFrame();   // MyImgui�`��O����

	//if (m_pDI->CheckKey(KD_TRG, DIK_F4))  ChangeScreenMode();   // �t���X�N���[���̐؂�ւ�

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

	case GAMEEND:			// �Q�[���I��
		PostQuitMessage(0);
		break;

	case GAMETUTORIAL:			// �Q�[���又��
		GameTutorial();
		break;

	case GAMEMULTI:			// �Q�[���又��
		GameMulti();
		break;

	case GAMEMULTIBATTLERESULT:			// �Q�[���又��
		m_pTitleProc->MultiBattleGameClear();
		break;


	}

	MyImgui::ImguiRender();      // MyImgui���`�揈�� 



	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	m_pD3D->m_pSwapChain->Present(0, 0);                   // Vsync�Ȃ�



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
	m_pRenderBufProc->Clear();	// �`��o�b�t�@�̃N�����[

	// �p�X�P�@�@�l�o�q�e�N�X�`���Ƀ����_�����O
// �����_�[�^�[�Q�b�g��MPR�e�N�X�`���[�ɂ���
	m_pD3D->SetRenderTarget(m_pMPR->m_pMPR_TexRTV, m_pMPR->m_pMPR_DSTexDSV);


	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	float ClearColor[4] = { 0,0,0,1 };// �N���A�F�쐬�@RGBA�̏�
	m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A

	m_mProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);

	// Map�̍X�V
	m_pMapProc->Update();

	m_pMapSubProc->Update();
	// �o�b�̍X�V
	m_pPcProc->UpdateAll();

	// �G�̍X�V
	if (m_pMapProc->GetPhaseMap() == 1)m_pEnmProc->UpdateAll();

	// �X�L���̍X�V
	if (m_pMapProc->GetPhaseMap() == 1)m_pWeaponProc->UpdateAll();

	// �R�c���ʂ̍X�V
	m_pEffectProc->UpdateAll();

	// �`��o�b�t�@����̕`�揈�� 
	m_pRenderBufProc->Render();

	// Map�̕`��2
	// �������̃}�b�v�I�u�W�F�N�g��`�悷�邽�߁A�僋�[�v�̍Ō�Ɏ��s
	m_pMapProc->Render2();

	m_pMapSubProc->Render2();

// ------------------------------------------------------------------------------------
// �p�X�Q	
// �����_�[�^�[�Q�b�g��ʏ�i�o�b�N�o�b�t�@�[�j�ɖ߂�
m_pD3D->SetRenderTarget(NULL, NULL);

	// ��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A


	//Z�o�b�t�@�𖳌���
	m_pD3D->SetZBuffer(FALSE);


	// �����_�[
	m_pMPR->RenderMPR();

	//Z�o�b�t�@��L����
	m_pD3D->SetZBuffer(TRUE);


	
	// ---------------------------------------------------------------------------------------
	

	// �O�i�E�w�i�̍X�V
	m_pBackForeProc->Update();


	// �J�����̍X�V
	m_pCameraProc->GetCameraObjPtr()->Update();


}



//------------------------------------------------------------------------
//
//	�Q�[���̃`���[�g���A������	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//
//
//------------------------------------------------------------------------
void CGameMain::GameTutorial()
{

	m_pRenderBufProc->Clear();	// �`��o�b�t�@�̃N�����[

	// �p�X�P�@�@�l�o�q�e�N�X�`���Ƀ����_�����O
// �����_�[�^�[�Q�b�g��MPR�e�N�X�`���[�ɂ���
	m_pD3D->SetRenderTarget(m_pMPR->m_pMPR_TexRTV, m_pMPR->m_pMPR_DSTexDSV);

	GameTutorialPhase();


	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	float ClearColor[4] = { 0,0,0,1 };// �N���A�F�쐬�@RGBA�̏�
	m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A

	m_mProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);


	// Map�̍X�V
	m_pMapProc->Update();

	m_pMapSubProc->Update();
	// �o�b�̍X�V
	m_pPcProc->UpdateAll();
		
	// �G�̍X�V
	m_pEnmProc->UpdateAll();

	
	// �X�L���̍X�V
	m_pWeaponProc->UpdateAll();

	// �R�c���ʂ̍X�V
	m_pEffectProc->UpdateAll();

	// �`��o�b�t�@����̕`�揈��
	m_pRenderBufProc->Render();

	// Map�̕`��2
	// �������̃}�b�v�I�u�W�F�N�g��`�悷�邽�߁A�僋�[�v�̍Ō�Ɏ��s
	m_pMapProc->Render2();

	m_pMapSubProc->Render2();

// ------------------------------------------------------------------------------------
// �p�X�Q
// �����_�[�^�[�Q�b�g��ʏ�i�o�b�N�o�b�t�@�[�j�ɖ߂�
	m_pD3D->SetRenderTarget(NULL, NULL);

	// ��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A


	//Z�o�b�t�@�𖳌���
	m_pD3D->SetZBuffer(FALSE);


	// �����_�[
	m_pMPR->RenderMPR();

	//Z�o�b�t�@��L����
	m_pD3D->SetZBuffer(TRUE);


	// �f�t�H���g�̃u�����h�X�e�[�g���A���t�@�u�����h�p�u�����h�X�e�[�g�ɂ���
	// (�����F�̃u�����f�B���O��ݒ�)
	//m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	// ---------------------------------------------------------------------------------------


	// �O�i�E�w�i�̍X�V
	m_pBackForeProc->Update();


	// �J�����̍X�V
	m_pCameraProc->GetCameraObjPtr()->Update();



}


//------------------------------------------------------------------------
//	�Q�[���̃`���[�g���A���t�F�[�Y����	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
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
//	�Q�[���̃��C������	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CGameMain::GameMulti()
{
	m_pRenderBufProc->Clear();	// �`��o�b�t�@�̃N�����[

	m_mProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), ((FLOAT)WINDOW_WIDTH) / ((FLOAT)(WINDOW_HEIGHT / 3) * 2), 0.1f, 1000.0);


// �����_�[�^�[�Q�b�g��MPR�e�N�X�`���[�ɂ���
	m_pD3D->SetRenderTarget(m_pMPR->m_pMPR_TexRTV, m_pMPR->m_pMPR_DSTexDSV);

	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	float ClearColor[4] = { 0,0,0,1 };// �N���A�F�쐬�@RGBA�̏�
	m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A

	// Map�̍X�V
	m_pMapProc->Update();

	m_pMapSubProc->Update();
	// �o�b�̍X�V
	m_pPcProc->UpdateAllMulti(FIRSTPLAYER);

	// �G�̍X�V
	if (m_pMapProc->GetPhaseMap() == 1)m_pEnmProc->UpdateAllMulti(FIRSTPLAYER);

	// �X�L���̍X�V
	if (m_pMapProc->GetPhaseMap() == 1)m_pWeaponProc->UpdateAllMulti(FIRSTPLAYER);

	// �R�c���ʂ̍X�V
	m_pEffectProc->UpdateAllMulti(FIRSTPLAYER);

	// �`��o�b�t�@����̕`�揈��
	m_pRenderBufProc->Render();

	// Map�̕`��2
	// �������̃}�b�v�I�u�W�F�N�g��`�悷�邽�߁A�僋�[�v�̍Ō�Ɏ��s
	m_pMapProc->Render2();

	m_pMapSubProc->Render2();

// ------------------------------------------------------------------------------------
// �p�X�Q

	D3D11_VIEWPORT vp;
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT/2;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pD3D->m_pDeviceContext->RSSetViewports(1, &vp);

// �����_�[�^�[�Q�b�g��ʏ�i�o�b�N�o�b�t�@�[�j�ɖ߂�
	m_pD3D->SetRenderTarget(NULL, NULL);

	// ��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A


	//Z�o�b�t�@�𖳌���
	m_pD3D->SetZBuffer(FALSE);


	// �����_�[
	m_pMPR->RenderMPR();

	//Z�o�b�t�@��L����
	m_pD3D->SetZBuffer(TRUE);

	// ---------------------------------------------------------------------------------------


	// �O�i�E�w�i�̍X�V
	//m_pBackForeProc->Update();


	// �J�����̍X�V
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

// �����_�[�^�[�Q�b�g��MPR�e�N�X�`���[�ɂ���
	m_pD3D->SetRenderTarget(m_pMPR->m_pMPR_TexRTV, m_pMPR->m_pMPR_DSTexDSV);


	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A

	// Map�̍X�V
	m_pMapProc->RenderSecond();


	// �o�b�̍X�V
	m_pPcProc->UpdateAllMulti(SECONDPLAYER);

	if (m_pMapProc->GetPhaseMap() == 1)m_pEnmProc->UpdateAllMulti(SECONDPLAYER);

	if (m_pMapProc->GetPhaseMap() == 1)m_pWeaponProc->UpdateAllMulti(SECONDPLAYER);

	// �R�c���ʂ̍X�V
	m_pEffectProc->UpdateAllMulti(SECONDPLAYER);


	// �`��o�b�t�@����̕`�揈��
	m_pRenderBufProc->RenderSecond();

	m_pMapProc->Render2Second();

	vp.TopLeftX = 0;
	vp.TopLeftY = WINDOW_HEIGHT / 2;

	m_pD3D->m_pDeviceContext->RSSetViewports(1, &vp);

	// �����_�[�^�[�Q�b�g��ʏ�i�o�b�N�o�b�t�@�[�j�ɖ߂�
	m_pD3D->SetRenderTarget(NULL, NULL);

	//Z�o�b�t�@�𖳌���
	m_pD3D->SetZBuffer(FALSE);


	// �����_�[
	m_pMPR->RenderMPR();

	//Z�o�b�t�@��L����
	m_pD3D->SetZBuffer(TRUE);


	// ---------------------------------------------------------------------------------------

	// �J�����̍X�V
	m_pCameraProc->UpdateAllMulti(SECONDPLAYER);

	vp2.TopLeftX = 0;
	vp2.TopLeftY = 0;

	m_pD3D->m_pDeviceContext->RSSetViewports(1, &vp2);

	// �O�i�E�w�i�̍X�V
	m_pBackForeProc->Update();


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
	;
}

//------------------------------------------------------------------------
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

