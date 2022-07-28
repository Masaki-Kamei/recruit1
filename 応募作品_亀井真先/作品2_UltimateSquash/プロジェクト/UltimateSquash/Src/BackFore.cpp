//=============================================================================
//		�O�i�E�w�i							                   BackFore.cpp
//=============================================================================
#include  "BackFore.h"

//============================================================================
//
// �O�i�E�w�i�v���V�[�W���̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CBackForeProc::CBackForeProc(CGameMain* pGMain)
{
	m_pGMain		= pGMain;

	m_pImageConstruction = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Construction_Pro.png"));						//�X�L�����C���[�W�̃��[�h
	m_pImageWeapon = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/WeaponTest.png"));									//�X�L���̎�ރC���[�W�̃��[�h
	m_pImageForegrdRadar = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Foregrd_Radar_Ver4.png"));						//���[�_�[�C���[�W�̃��[�h
	m_pImageForegrdRadarBase = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Foregrd_Radar2.png"));						//���[�_�[�̃x�[�X�C���[�W�̃��[�h
	m_pImageEventReport = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/EVENT.png"));									//�f���W���[�C���[�W�̃��[�h
	m_pImageForegrdMangaEfect = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/MangaEfect_1.png"));						//�[���C���[�W�̃��[�h

	//�`���[�g���A���̃C���[�W���[�h
	m_pImageExplanationFrame = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Explanation_Frame_Ver2.png"));		//�����̃`���[�g���A���C���[�W�̃��[�h
	m_pImageTutorialNormal = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_Normal.png"));		//�x�[�X�`���[�g���A�����[�_�[�C���[�W�̃��[�h
	m_pImageTutorialUI = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_UI_Ver2.png"));			//UI�̃`���[�g���A�����[�_�[�C���[�W�̃��[�h
	m_pImageTutorialMove = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_Move.png"));			//�ړ��̃`���[�g���A�����[�_�[�C���[�W�̃��[�h
	m_pImageTutorialHit = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_Hit.png"));				//�ł��Ԃ��`���[�g���A�����[�_�[�C���[�W�̃��[�h
	m_pImageTutorialTarget = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_Target.png"));		//�I�̃`���[�g���A�����[�_�[�C���[�W�̃��[�h
	m_pImageTutorialBoom = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_Boom.png"));			//���e�̃`���[�g���A�����[�_�[�C���[�W�̃��[�h
	m_pImageTutorialSkill = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_Skill.png"));			//�X�L���̃`���[�g���A���C���[�W�̃��[�h
	m_pImageTutorialSetSkill = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_SetSkill.png"));	//�X�L���̃`���[�g���A���C���[�W�̃��[�h
	m_pQuestTextBack = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Text_Back_2_Ver2.png"));							//�`���[�g���A���N���A�����C���[�W�̃��[�h
	m_pBackImage = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/black.png"));											//�w�i���Â�����C���[�W�̃��[�h

	m_pSprite       = new CSprite(m_pGMain->m_pShader); // �X�v���C�g�̐���

	//���[�_�[�̕ϐ�
	m_nRaderDispArea = 50;  // ���[�_�[�̕\���͈�(m)
	m_nRaderSize = 156;     // ���[�_�[�̉�ʏ�̑傫��(�s�N�Z��)
	m_nRaderMpX = 0;
	m_nRaderMpY = 0;
	FileTextRead();

}
// ---------------------------------------------------------------------------
//
// �O�i�E�w�i�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CBackForeProc::~CBackForeProc()
{


	SAFE_DELETE(m_pImageConstruction);
	SAFE_DELETE(m_pImageWeapon)
	SAFE_DELETE(m_pImageForegrdRadar);
	SAFE_DELETE(m_pImageEventReport);
	SAFE_DELETE(m_pImageForegrdRadarBase);
	SAFE_DELETE(m_pImageForegrdMangaEfect);

	SAFE_DELETE(m_pImageExplanationFrame);
	SAFE_DELETE(m_pImageTutorialNormal);
	SAFE_DELETE(m_pImageTutorialUI);
	SAFE_DELETE(m_pImageTutorialMove);
	SAFE_DELETE(m_pImageTutorialHit);
	SAFE_DELETE(m_pImageTutorialTarget);
	SAFE_DELETE(m_pImageTutorialBoom);
	SAFE_DELETE(m_pImageTutorialSkill);
	SAFE_DELETE(m_pImageTutorialSetSkill);


	SAFE_DELETE(m_pBackImage);
	SAFE_DELETE(m_pQuestTextBack);


	SAFE_DELETE(m_pSprite);

	// vector�̍폜
	m_ReaderArray.clear();					// �z��폜
	m_ReaderArray.shrink_to_fit();			// �s�v���������


}
//------------------------------------------------------------------------
//
//	�O�i�E�w�i�v���V�[�W���̍X�V	
//
//------------------------------------------------------------------------
void CBackForeProc::Update()
{
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();

	if (m_pGMain->m_dModeType == MAINMODE|| m_pGMain->m_dModeType == TUTORIAL)
	{
		const int nScoreImagePosX = 0, nScoreImagePosY = 45;	//�X�R�A�摜�\���ʒu
		const int nScoreTextPosX = 10, nScoreTextPosY = 8;		//�X�R�A�����\���ʒu
		const int nScorePointPosX = 0, nScorePointPosY = 55;	//�X�R�A���l�\���ʒu
		//�X�R�A�`��
		UpdateScore(nScoreImagePosX, nScoreImagePosY, nScoreTextPosX, nScoreTextPosY, nScorePointPosX, nScorePointPosY, m_pGMain->m_nScore);
		//�X�L�����̕\���Ə���
		UpdateConstruction();
		//���[�_�̕\��
		UpdateRadar();


	}

	//�`���[�g���A���̃e�L�X�g�\��
	if (m_pGMain->m_dModeType == TUTORIAL)		TutorialText();	
	//���C�����[�h�\��
	if (m_pGMain->m_dModeType == MAINMODE)		MainModeBackFore();	
	//�}���`���[�h�̕\��
	if (m_pGMain->m_dModeType == MULTI)
	{
		MultiUpdate();																		//�}���`���[�h�̍X�V
		MultiUpdateScore();																	//�}���`���[�h�̃X�R�A����
		UpdateRadar(FIRSTPLAYER);															//�PP���[�_�[�̏���
		UpdateRadar(SECONDPLAYER);															//�QP���[�_�[�̏���
		m_pSprite->DrawRect(0, (WINDOW_HEIGHT / 2)-3, WINDOW_WIDTH, 6, RGB(0, 0, 0));		//�����������\��
		MainModeBackFore();																	//�Q�[���̗���X�V

	}
};

//============================================================================
//
//   �X�L�����̍X�V�ƕ\��
//
//--M.Kamei_Point
//--Point_SkillDisplay
//
//============================================================================
void CBackForeProc::UpdateConstruction()
{
	int   DestX, DestY;												//�ʒu�i�ۑ��p�j
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();			//�v���C���[�̎擾

	const int nWidth = 258, nHeight = 258;							//���̑傫��
	const int nWidthScale = nWidth / 2;								//�\���傫��
	const int nHeightScale = nHeight / 2;							//�\���傫��
	const int WeaponSet = 3;										//�X�L���̐�

	//�X�L�����̘g
	const int nColumnStartX = 0, nColumnStartY = 0;					//�p�^�[������
	const int nColumnWidth = 250, nColumnHeight = 250;				//�p�^�[���傫��
	const int nColumnWidthScale = nColumnWidth / 2;					//���̑傫��
	const int nColumnHeightScale = nColumnHeight / 2;				//�����̑傫��

	//�X�L�����̊O�g
	const int nFreamWidth = 272, nFreamHeight = 272;				//�p�^�[���傫��
	const int nFreamWidthScale = nFreamWidth / 2;					//���̑傫��
	const int nFreamHeightScale = nFreamHeight / 2;					//�����̑傫��
	const int nFreamNormalStartX = 300, nFreamNormalStartY = 0;		//�p�^�[������(�m�[�}��)
	const int nFreamChoiceStartX = 0, nFreamChoiceStartY = 300;		//�p�^�[������(�I��)
	const int nFreamUseStartX = 300, nFreamUseStartY = 300;			//�p�^�[������(������)


	DestX = 10;														//�ʒu�̒���X
	DestY = WINDOW_HEIGHT - nHeight + 100;							//�ʒu�̒���Y

	float WaitTime[100];											//�c��̃N�[���^�C��
	float WaitMaxTime[100];											//�N�[���^�C���ő�l
	int		WeaponNo = pPcObj->GetWeaponNo();						//�X�L���i���o�[
	int		WeaponColuman = pPcObj->GetWeaponColuman() - 1;			//���݂̃X�L���I��
	float	RemWaitTime[100];										//�N�[���^�C���̊���

	int	LineNum = (m_pGMain->m_pTitleProc->GetWeaponNum()/5)+1;		//�X�L���̑I�𗓂̍s�̐�


	//�X�L���̘g�\��--------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < WeaponSet; i++)
	{
		//���ꂼ��̃X�L���̃N�[���^�C���ő�l���擾
		WaitMaxTime[i] = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->GetWeaponMaxWaitTime(i);
		//���ꂼ��̃X�L���̃N�[���^�C�����擾
		WaitTime[i] = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->GetWeaponWaitTime(i);
		//�c��̃N�[���^�C��
		RemWaitTime[i] = WaitTime[i] / WaitMaxTime[i];
		//�N�[���^�C�����̕\�� 
		if (WaitTime[i] > 0) {
			//�X�L���̃N�[���^�C���̔䗦�ɍ��킹�ĕ\������p�^�[���̍���A�傫���A���ƍ����̑傫���̕\����ύX���Ă���
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY + ((nHeightScale*(RemWaitTime[i]))), 0, nHeight*(RemWaitTime[i]), nColumnWidth, nColumnHeight*(1 - RemWaitTime[i]), nWidthScale, nHeightScale*(1 - RemWaitTime[i]));	//���̘g
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nColumnStartX, nColumnStartY, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale, 0.5);		//���̘g(�N�[���^�C���̕\���Ŕ�������)
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nFreamNormalStartX, nFreamNormalStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);	//���̊O�g

		}
		//�X�L��������
		else if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetSkillActive(i) == TRUE) {
			//�\��
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nColumnStartX, nColumnStartY, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale);			//���̘g
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nFreamUseStartX, nFreamUseStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);			//���̊O�g


		}
		//�I�𒆂̃X�L������g�t���ɂ���
		else if (WeaponColuman == i) {
			//�\��
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nColumnStartX, nColumnStartY, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale);			//���̘g
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nFreamChoiceStartX, nFreamChoiceStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);	//���̊O�g

		}
		else {
			//�\��
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nColumnStartX, nColumnStartY, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale);			//���̘g
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nFreamNormalStartX, nFreamNormalStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);	//���̊O�g

		}

		//�X�L���̃A�C�R���\��--------------------------------------------------------------------------------------------------------------
		DWORD dwWeaponSelectNo = pPcObj->GetWeaponColumanNo(i);
		int y = (dwWeaponSelectNo - 1) / 5;
		int x = 0;
		//�I�������X�L�����I�𗓂̂Ȃ��ڂɂ��邩
		for (int j = 0; j < LineNum; j++)
		{
			if (((j + 1) * 5) > (dwWeaponSelectNo - 1))
			{
				x = (dwWeaponSelectNo - 1) - 5;
				if (x < 0) {
					x = (dwWeaponSelectNo - 1);
				}
				break;
			}
		}

		//�X�v���C�g���̍��W���X�L���ɍ��킹�鏈��
		float	ReduceGage;
		ReduceGage= WaitTime[i] / WaitMaxTime[i];		//�c��̃N�[���^�C�����擾
		ReduceGage= (nHeight * (1 + y)) * ReduceGage;
		ReduceGage = (nHeight * (1 + y))- ReduceGage;
		ReduceGage= ReduceGage / (1 + y);
		if (dwWeaponSelectNo != NULL) {		//�X�L�����Z�b�g���ꂽ�Ƃ��ɃX�L����\��
			if (WaitTime[i] > 0) {
				//�X�L���̃N�[���^�C���̔䗦�ɍ��킹�ĕ\������p�^�[���̍���A�傫���A���ƍ����̑傫���̕\����ύX���Ă���
				m_pSprite->Draw(m_pImageWeapon, DestX + (nWidthScale + DestX)*i, DestY + ((nHeightScale*(RemWaitTime[i]))), nWidth*x, ((nHeight*(y+1))-(ReduceGage)), nWidth, (nHeight*(1 - RemWaitTime[i])), nWidthScale, nHeightScale*(1 - RemWaitTime[i]));		
				m_pSprite->Draw(m_pImageWeapon, DestX + (nWidthScale + DestX)*i, DestY, nWidth*x, nHeight*y, nWidth, nHeight, nWidthScale, nHeightScale, 0.5);																											
			}
			else {
				m_pSprite->Draw(m_pImageWeapon, DestX + (nWidthScale + DestX)*i, DestY, nWidth*x, nHeight*y, nWidth, nHeight, nWidthScale, nHeightScale);
			}
		}

	}

}
//============================================================================
//
//   �X�R�A�̍X�V�ƕ\��
//
//	const int		nScoreImagePosX�@�X�R�A�摜�\���ʒuX
//	const int		nScoreImagePosY�@�X�R�A�摜�\���ʒuY
//	const int		nScoreTextPosX	 �X�R�A�����\���ʒuX
//	const int		nScoreTextPosY   �X�R�A�����\���ʒuY
//	const int		nScorePointPosX	 �X�R�A���l�\���ʒuX
//	const int		nScorePointPosY  �X�R�A���l�\���ʒuY
//	int				nScore			 �X�R�A�̐��l
//
//
//============================================================================
void CBackForeProc::UpdateScore(const int nScoreImagePosX, const int nScoreImagePosY, const int nScoreTextPosX, const int nScoreTextPosY, const int nScorePointPosX, const int nScorePointPosY,int nScore)
{
	//�X�R�A�摜�\��---------------------------------------
	const int nScoreImageStartX = 0, nScoreImageStartY = 250;	//�p�^�[���̍���ʒu
	const int nScoreImageWidth = 221, nScoreImageHeight = 58;	//�p�^�[���̑傫��
	m_pSprite->Draw(m_pImageForegrdRadarBase, nScoreImagePosX, nScoreImagePosY, nScoreImageStartX, nScoreImageStartY, nScoreImageWidth, nScoreImageHeight, 1.0f);

	//�X�R�A�̕����\��-------------------------------------
	const int nScoreTextSize = 50;	//�X�R�A�����̃T�C�Y
	m_pGMain->m_pFont->FreamDraw(nScoreTextPosX, nScoreTextPosY, _T("SCORE"), nScoreTextSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));
	m_pGMain->m_pFont->Draw(nScoreTextPosX, nScoreTextPosY, _T("SCORE"), nScoreTextSize, RGB(255, 0, 0), 1.0f, _T("���C���I �{�[���h"));

	//�X�R�A�̐��l�\��-------------------------------------
	TCHAR str[256] = { 0 };
	const int nScorePointSize = 50;	//�X�R�A���l�̃T�C�Y
	_stprintf(str, _T("%8d"), nScore);
	m_pGMain->m_pFont->Draw(nScorePointPosX, nScorePointPosY, str, nScorePointSize, RGB(255, 255, 255), 1.0, _T("���C���I �{�[���h"));

}
//============================================================================
//
//   ���[�_�[�}�b�v�̍X�V�ƕ\��
//
//	DWORD			dwPlayerNo	�v���C���[�ԍ�
//
//
//============================================================================
void CBackForeProc::UpdateRadar(DWORD dwPlayerNo)
{
	TCHAR str[256];
	const int nDist = 20;																 // ���[�_�[�}�b�v�̉�ʒ[����̗]��

	// �\���ʒu������W
	m_nRaderMpX = WINDOW_WIDTH - (m_nRaderSize + nDist);
	m_nRaderMpY = nDist + 30;
	if(dwPlayerNo==SECONDPLAYER)	m_nRaderMpY =(WINDOW_HEIGHT/2)+ m_nRaderMpY;
	const int	m_nRaderStartPosX = 400, m_nRaderStartPosY = 28;					//�p�^�[������

	// �\���ʒu���S���W��ݒ肷��
	const float fOfX = (m_nRaderMpX + m_nRaderSize / 2)-8;							//�\���ʒuX
	const float fOfY = (m_nRaderMpY + m_nRaderSize / 2)-8;							//�\���ʒuY
	const float fOfStartX = 0, fOfStartY = 272;										//�p�^�[������
	const float fOfWidthX = 16;														// ��
	const float fOfHeightY = 16;													// ����

	//���[�_�[�t���[���̕ϐ�
	const int	m_nRaderTimerFreamMpX = m_nRaderMpX - 205;							//�\���ʒuX
	const int	m_nRaderTimerFreamMpY = m_nRaderMpY - 28;							//�\���ʒuY
	const int	m_nRaderTimerFreamStartPosX = 0,m_nRaderTimerFreamStartPosY = 0;	//�p�^�[������
	const int	m_nRaderTimerFreamStartWidth = 373;									// ��
	const int	m_nRaderTimerFreamStartHeight= 196;									// ����

	//���[�_�[�̕ϐ�
	const int	m_nRaderTimerMpX = m_nRaderMpX - 130;								//�\���ʒuX
	const int	m_nRaderTimerMpY = m_nRaderMpY - 20;								//�\���ʒuY
	const int	m_nRaderTimerSize = 80;												//�傫��

	// ���[�_�[�}�b�v�̕\��
	m_pSprite->Draw(m_pImageForegrdRadarBase, m_nRaderMpX, m_nRaderMpY, m_nRaderStartPosX, m_nRaderStartPosY, m_nRaderSize, m_nRaderSize, 1.0f);
	m_pSprite->Draw(m_pImageForegrdRadar, fOfX, fOfY , fOfStartX, fOfStartY, fOfWidthX, fOfHeightY);
	m_pSprite->Draw(m_pImageForegrdRadarBase, m_nRaderTimerFreamMpX, m_nRaderTimerFreamMpY, m_nRaderTimerFreamStartPosX, m_nRaderTimerFreamStartPosY, m_nRaderTimerFreamStartWidth, m_nRaderTimerFreamStartHeight,1.0f);
	if (m_pGMain->m_nTimer >= 0) {
		_stprintf(str, _T("%3d"), m_pGMain->m_nTimer);
		m_pGMain->m_pFont->Draw(m_nRaderTimerMpX, m_nRaderTimerMpY, str, m_nRaderTimerSize, RGB(255, 255, 255), 1.0, _T("���C���I �{�[���h"));
	}
	else {
		_stprintf(str, _T("%3d"),0);
		m_pGMain->m_pFont->Draw(m_nRaderTimerMpX, m_nRaderTimerMpY, str, m_nRaderTimerSize, RGB(255, 255, 255), 1.0, _T("���C���I �{�[���h"));

	}

	// ���[�_�[���ɓG�̕\�� 
	SetReaderOn(dwPlayerNo);          // ���[�_�[�z��ɓG
	DispEnmInfoRader(dwPlayerNo);		// �\��
}

//============================================================================
//
// ���[�_�[�ɓG�̏���\�����鏈��
//
//	DWORD			dwPlayerNo	�v���C���[�ԍ�
//
//
//============================================================================
void CBackForeProc::DispEnmInfoRader(DWORD dwPlayerNo)
{

	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	if (dwPlayerNo == SECONDPLAYER)pPcObj = m_pGMain->m_pPcProc->GetPcSecObjPtr();

	float fRatio = (float)m_nRaderDispArea / m_nRaderSize;  // �����W�ƃ��[�_�[��ʍ��W�Ƃ̕\���䗦
	// �\���ʒu���S���W��ݒ肷��
	float fOfX = m_nRaderMpX + m_nRaderSize / 2;
	float fOfY = m_nRaderMpY + m_nRaderSize / 2;

	for (int i = 0; i < m_ReaderArray.size(); i++)
	{
		// �o�b�����_�Ƃ����G�̈ʒu�����߂�
		VECTOR3 vEnm = GetPositionVector(m_ReaderArray[i].pEnmMisObj->GetWorld() * XMMatrixInverse(NULL, pPcObj->GetWorld()));
		int dx = (int)(vEnm.x / fRatio) + fOfX - 8;
		int dy = (int)(-vEnm.z / fRatio) + fOfY - 8;

		//�{�[���̕\���ϐ�
		const int BallImageStartPosX = 48, BallImageStartPosY = 256;	//�p�^�[������
		const int BallImageStartWidth = 16, BallImageStartHeight = 16;	//�p�^�[���傫��
		//�{�[���̕\���ϐ�(���˕Ԃ����Ƃ�)
		const int BallImageDamageStartPosX = 16, BallImageDamageStartPosY = 256;	//�p�^�[������
		const int BallImageDamageStartWidth = 16, BallImageDamageStartHeight = 16;	//�p�^�[���傫��
		//���e�̕\���ϐ�
		const int BoomImageStartPosX = 144, BoomImageStartPosY = 272;	//�p�^�[������
		const int BoomImageStartWidth = 16, BoomImageStartHeight = 16;	//�p�^�[���傫��
		//�I�̕\���ϐ�
		const int TargetImageStartPosX = 16, TargetImageStartPosY = 272;	//�p�^�[������
		const int TargetImageStartWidth = 16, TargetImageStartHeight = 16;	//�p�^�[���傫��

		//�G�̈ʒu��\��-------------------------------------------------------
		if (m_ReaderArray[i].dwObjID == ENM_BALL_ID)
		{
			// �{�[���̕\��
			if (m_ReaderArray[i].pEnmMisObj->GetDamage() == TRUE) {
				m_pSprite->Draw(m_pImageForegrdRadar, dx, dy, BallImageStartPosX, BallImageStartPosY, BallImageStartWidth, BallImageStartHeight, 1.0f);

			}
			else {
				//���˕Ԃ����Ƃ��̕\��
				m_pSprite->Draw(m_pImageForegrdRadar, dx, dy, BallImageDamageStartPosX, BallImageDamageStartPosY, BallImageDamageStartWidth, BallImageDamageStartHeight, 1.0f);
			}
		}
		else if (m_ReaderArray[i].dwObjID == ENM_BALLBOOM_ID)
		{
			//���e�̕\��	
			m_pSprite->Draw(m_pImageForegrdRadar, dx, dy, BoomImageStartPosX, BoomImageStartPosY, BoomImageStartWidth, BoomImageStartHeight, 1.0f);
		}
		else
		{
			// �I�̕\��
			m_pSprite->Draw(m_pImageForegrdRadar, dx, dy, TargetImageStartPosX, TargetImageStartPosY, TargetImageStartWidth, TargetImageStartHeight, 1.0f);

		}
	}
}

//-----------------------------------------------------------------------------   
// ���[�_�[�z��̐ݒ�
//
//
//-----------------------------------------------------------------------------
void	CBackForeProc::SetReaderOn(DWORD dwPlayerNo)
{
	int MpX, MpY, OfX, OfY;
	int nArea, nSize;

	MpX = m_nRaderMpX;	// �\���ʒu������W
	MpY = m_nRaderMpY;
	OfX = m_nRaderMpX + m_nRaderSize / 2;	// �\���ʒu���S���W
	OfY = m_nRaderMpY + m_nRaderSize / 2;
	nArea = m_nRaderDispArea;
	nSize = m_nRaderSize;


	m_ReaderArray.clear();			// �z��폜
	m_ReaderArray.shrink_to_fit();	// �s�v���������

	// ���ݐ����Ă���G�������[�_�[�z��Ɋi�[����
	float fRatio = (float)nArea / nSize;  // �����W�ƃ��[�_�[��ʍ��W�Ƃ̕\���䗦
	Reader lo;
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	if(dwPlayerNo==SECONDPLAYER)pPcObj = m_pGMain->m_pPcProc->GetPcSecObjPtr();
	std::vector<CBaseObj*> EnmMisObjArray;
	if (m_pGMain->m_dModeType == MULTI)m_pGMain->m_pEnmProc->GetActiveEnmMulti(EnmMisObjArray, dwPlayerNo);
	else m_pGMain->m_pEnmProc->GetActiveEnm(EnmMisObjArray);   // ���ݐ����Ă���G�̏���ݒ肷��

	for (int i = 0; i < EnmMisObjArray.size(); i++)   // �G�̏������[�_�[�z��Ɋi�[
	{
		// �o�b�����_�Ƃ����G�̈ʒu�����߁A���[�_�[�\���͈͓����ǂ����𔻒肷��
		VECTOR3 vEnm = GetPositionVector(EnmMisObjArray[i]->GetWorld() * XMMatrixInverse(NULL, pPcObj->GetWorld()));
		int dx = (int)(vEnm.x / fRatio) + OfX - 8;
		int dy = (int)(-vEnm.z / fRatio) + OfY - 8;
		BOOL bWithin = FALSE;
		if (dx >= MpX && dx <= MpX + nSize - 8 && dy >= MpY && dy <= MpY + nSize - 8)
		{
			bWithin = TRUE;   // ��ʓ�
		}
		if (bWithin) // ���[�_�[���̕\���̂ݏ�������
		{
			lo.dwObjID = EnmMisObjArray[i]->GetObjID();
			lo.pEnmMisObj = EnmMisObjArray[i];
			lo.pWeaponObj = NULL;
			lo.dwOwner = ENM;

			lo.bWithin = bWithin;
			m_ReaderArray.push_back(lo);
		}

	}

	EnmMisObjArray.clear();
	EnmMisObjArray.shrink_to_fit();
}


//============================================================================
//
//   �`���[�g���A���\������Ƃ��̃X�e�[�^�X�i�[
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//============================================================================
void CBackForeProc::TutorialCapture()
{
	//�z�񏉊���
	int ArrSize = TutorialPhaseArr.size();
	if (ArrSize > 0) {
		for (int i = 0; i < ArrSize; i++)
		{
			TutorialPhaseArr[i].PhaseTextArray.clear();
			TutorialPhaseArr[i].PhaseTextArray.shrink_to_fit();
		}
		TutorialPhaseArr.clear();
		TutorialPhaseArr.shrink_to_fit();
	}
	const int		  TutorialPhaseArrNum = 11;		//�t�F�[�Y�̐�
	//�t�F�[�Y�̃X�e�[�^�X�i�ԍ��A��ށj
	TutorialPhaseArr =
	{
		StrTutorialPhase(0,STPKIND_TEXT),	//���[���AUI�A�v���C���[�̈ړ�(����)
		StrTutorialPhase(1,STPKIND_MISION),	//�v���C���[�̈ړ�(�~�b�V����)
		StrTutorialPhase(2,STPKIND_TEXT),	//�{�[��(����)
		StrTutorialPhase(3,STPKIND_MISION),	//�{�[��(�~�b�V����)
		StrTutorialPhase(4,STPKIND_TEXT),	//�I(����)
		StrTutorialPhase(5,STPKIND_MISION),	//�I(�~�b�V����)
		StrTutorialPhase(6,STPKIND_TEXT),	//���e�{�[��(����)
		StrTutorialPhase(7,STPKIND_MISION),	//���e�{�[��(�~�b�V����)
		StrTutorialPhase(8,STPKIND_TEXT),	//�X�L��(����)
		StrTutorialPhase(9,STPKIND_MISION),	//�X�L��(�~�b�V����)
		StrTutorialPhase(10,STPKIND_TEXT),	//�Ō��(����)
	};	//�t�F�[�Y�z��

	//�t�F�[�Y�e�L�X�g�̃X�e�[�^�X�i�摜�A�ԍ��A��ށj
	TutorialPhaseTextArr =
	{
		//���[���AUI�A�v���C���[�̈ړ�
		{
		StrTutorialPhaseText(0,STPTKIND_TEXT),
		StrTutorialPhaseText(1,STPTKIND_TEXT),
		StrTutorialPhaseText(m_pImageTutorialNormal,2,STPTKIND_DRAW),
		StrTutorialPhaseText(m_pImageTutorialMove,3,STPTKIND_NOTSTART),
		},
		//�~�b�V����(0,0)
		{StrTutorialPhaseText(0,0),},
		//�{�[��
		{StrTutorialPhaseText(m_pImageTutorialHit,0,STPTKIND_NOTSTART),},
		//�~�b�V����(0,0)
		{StrTutorialPhaseText(0,0),},
		//�I
		{StrTutorialPhaseText(m_pImageTutorialTarget,0,STPTKIND_NOTSTART),},
		//�~�b�V����(0,0)
		{StrTutorialPhaseText(0,0),},
		//���e�{�[��
		{StrTutorialPhaseText(m_pImageTutorialBoom,0,STPTKIND_NOTSTART),},
		//�~�b�V����(0,0)
		{StrTutorialPhaseText(0,0),},
		//�X�L��
		{StrTutorialPhaseText(m_pImageTutorialSkill,0,STPTKIND_NOTSTART),},
		//�~�b�V����(0,0)
		{StrTutorialPhaseText(0,0),},
		//�X�L���Ґ�
		{StrTutorialPhaseText(m_pImageTutorialSetSkill,0,STPTKIND_START),},
	};

	//�t�F�[�Y�e�L�X�g�̃X�e�[�^�X���i�[
	for (int i = 0; i < TutorialPhaseArrNum; i++)
	{
		for (int j = 0; j < TutorialPhaseTextArr[i].size(); j++) {
			TutorialPhaseArr[i].PhaseTextArray.push_back(TutorialPhaseTextArr[i][j]);
		}
	}

}
//============================================================================
//
//   �`���[�g���A���e�L�X�g
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//
//============================================================================
void CBackForeProc::TutorialText()
{
	//�������̃^�C�g��
	TCHAR PName[][20] = {
_T("�`���[�g���A��"),
_T("���[��"),
_T("UI"),
_T("�v���C���[�̈ړ�"),
_T("�{�[��"),
_T("�I"),
_T("���e�{�[��"),
_T("�X�L��"),

	};

	DWORD	PhaseNum = m_pGMain->m_dPhase;				//�`���[�g���A���t�F�[�Y�̔ԍ��擾
	TutorialPhaseDisKinds(TutorialPhaseArr[PhaseNum]);	//�`���[�g���A���̕\��
	

}
//============================================================================
//
//	 �`���[�g���A���t�F�[�Y�̎��
//
//	StrTutorialPhase		TutorialPhase	�`���[�g���A���t�F�[�Y�̍\����
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//============================================================================

void CBackForeProc::TutorialPhaseDisKinds(StrTutorialPhase TutorialPhase)
{

	if (TutorialPhase.Kinds == STPKIND_TEXT)
	{
		m_pSprite->Draw(m_pBackImage, 0, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, 0.5f);		//�����ȊO�̉�ʂ��Â�����
		TutorialPhaseTextDisKinds(TutorialPhase.PhaseTextArray[TutorialPhaseTextNo]);		//�`���[�g���A���t�F�[�Y�e�L�X�g�̕\��
	}
	if (TutorialPhase.Kinds == STPKIND_MISION)
	{
		TutorialMisionText();				//�`���[�g���A���~�b�V�����e�L�X�g�̕\��
	}
}

//============================================================================
//
//	 �`���[�g���A���t�F�[�Y�e�L�X�g�̎��
//
//	StrTutorialPhase		TutorialPhase	�`���[�g���A���t�F�[�Y�e�L�X�g�̍\����
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//
//============================================================================

void CBackForeProc::TutorialPhaseTextDisKinds(StrTutorialPhaseText TutorialPhaseText)
{
	const int FreamWidth = 1366;					//�����g�̉����ő�l
	const int FreamHeight = 768;					//�����g�̏c���ő�l

	const int FreamWidthUP = FreamWidth / 10;			//�����g�̉��ɍL����
	const int FreamHeightUP = FreamHeight / 10;		//�����g�̏c�ɍL����

	int	CurrentWidthFreamSize = FreamWidthUP * m_nCntTime;		//���݂̐����g�̉���
	int	CurrentHeightFreamSize = FreamHeightUP * m_nCntTime;	//���݂̐����g�̏c��

	int	CurrentWidthFreamPos;						//���݂̐����g�̉��ʒu
	int	CurrentHeightFreamPos;						//���݂̐����g�̏c�ʒu

	//���X�ɐ����g���傫���Ȃ�悤�ɂ��鏈���i�ő�l�܂ł͑傫���Ȃ�Ȃ��j
	if ((FreamWidthUP*m_nCntTime) >= FreamWidth && (FreamHeightUP*m_nCntTime) >= FreamHeight)
	{
		CurrentWidthFreamSize = FreamWidth;
		CurrentHeightFreamSize = FreamHeight;

	}
	//�傫�������Ƃ��Ɉʒu�̒���
	CurrentWidthFreamPos = (WINDOW_WIDTH / 2) - (CurrentWidthFreamSize / 2);
	CurrentHeightFreamPos = (WINDOW_HEIGHT / 2) - (CurrentHeightFreamSize / 2);

	//�e�L�X�g�̂�(STPTKIND_TEXT)
	if (TutorialPhaseText.Kinds== STPTKIND_TEXT)
	{
		TutolialTextOnlySentence(CurrentWidthFreamPos, CurrentHeightFreamPos, FreamWidth, FreamHeight, CurrentWidthFreamSize, CurrentHeightFreamSize);
		if ((FreamWidthUP*m_nCntTime) >= FreamWidth && (FreamHeightUP*m_nCntTime) >= FreamHeight)		//���������ő�l�ɂȂ�����
		{
			TutorialTextDisplay();
		}

	}
	//�ʐ^�t��(STPTKIND_DRAW)
	if (TutorialPhaseText.Kinds== STPTKIND_DRAW)
	{
		TutolialTextOnlySentence(CurrentWidthFreamPos, CurrentHeightFreamPos, FreamWidth, FreamHeight, CurrentWidthFreamSize, CurrentHeightFreamSize);
		if ((FreamWidthUP*m_nCntTime) >= FreamWidth && (FreamHeightUP*m_nCntTime) >= FreamHeight)																//���������ő�l�ɂȂ�����
		{
			if (PhaseTextNum == nPhaseNumAll + 1)m_pSprite->Draw(m_pImageTutorialUI, 0, 0, 0, 0, FreamWidth, FreamHeight, FreamWidth, FreamHeight, 1.0f);		//�C���[�W�ʐ^�̕\��
			else if (PhaseTextNum != nPhaseNumAll)
			{
				m_pSprite->Draw(TutorialPhaseText.pImage, 0, 0, 0, 0, FreamWidth, FreamHeight, FreamWidth, FreamHeight, 1.0f);									//�C���[�W�ʐ^�̕\��
			}
			TutorialTextDisplay();

		}

	}
	//�\�����ȊO�̎ʐ^�t��(STPTKIND_NOTSTART)
	if (TutorialPhaseText.Kinds == STPTKIND_NOTSTART)
	{
		TutolialTextMisionSentence(CurrentWidthFreamPos, CurrentHeightFreamPos, FreamWidth, FreamHeight, CurrentWidthFreamSize, CurrentHeightFreamSize);
		if ((FreamWidthUP*m_nCntTime) >= FreamWidth && (FreamHeightUP*m_nCntTime) >= FreamHeight)																//���������ő�l�ɂȂ�����
		{
			if (PhaseTextNum != nPhaseNumAll)m_pSprite->Draw(TutorialPhaseText.pImage, 0, 0, 0, 0, FreamWidth, FreamHeight, FreamWidth, FreamHeight, 1.0f);		//�C���[�W�ʐ^�̕\��
			TutorialTextDisplay();

		}

	}
	//�\��������̎ʐ^�t��(STPTKIND_NOTSTART)
	if (TutorialPhaseText.Kinds == STPTKIND_START)
	{
		TutolialTextMisionSentence(CurrentWidthFreamPos, CurrentHeightFreamPos, FreamWidth, FreamHeight, CurrentWidthFreamSize, CurrentHeightFreamSize);
		if ((FreamWidthUP*m_nCntTime) >= FreamWidth && (FreamHeightUP*m_nCntTime) >= FreamHeight)																//���������ő�l�ɂȂ�����
		{
			m_pSprite->Draw(TutorialPhaseText.pImage, 0, 0, 0, 0, FreamWidth, FreamHeight, FreamWidth, FreamHeight, 1.0f);										//�C���[�W�ʐ^�̕\��
			TutorialTextDisplay();

		}

	}

}

//============================================================================
//
//   �`���[�g���A���e�L�X�g��������
//
//		const int		WidthFreamPos		�������\���ʒu�̍���@X���W
//		const int		HeightFreamPos		�������\���ʒu�̍���@Y���W
//		const int		FreamWidth			�������p�^�[���̕�
//		const int		FreamHeight			�������p�^�[���̍���
//		const int		WidthFreamSize		�������\���̕�
//		const int		HeightFreamSize		�������\���̍���
//
//
//============================================================================
void CBackForeProc::TutolialTextOnlySentence(const int WidthFreamPos,const int HeightFreamPos,const int FreamWidth,const int FreamHeight,const int WidthFreamSize,const int HeightFreamSize)
{
	//�e�L�X�g�̘g�\��
	m_pSprite->Draw(m_pImageExplanationFrame, WidthFreamPos, HeightFreamPos, 0, 0, FreamWidth, FreamHeight, WidthFreamSize, HeightFreamSize, 1.0f);

	if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))		//�N���b�N����ƃe�L�X�g�������ɐi�߂�
	{
		PhaseTextNum++;
	}

	if (PhaseTextNum > PhaseNum[pNameNum] + nPhaseNumAll) {		//���̃t�F�[�Y�Ɉڍs
		TutorialTextSentenceEnd();
	}
	m_nCntTime++;


};

//============================================================================
//
//   �`���[�g���A���e�L�X�g������~�b�V�����J�n
//
//		const int		WidthFreamPos		�������\���ʒu�̍���@X���W
//		const int		HeightFreamPos		�������\���ʒu�̍���@Y���W
//		const int		FreamWidth			�������p�^�[���̕�
//		const int		FreamHeight			�������p�^�[���̍���
//		const int		WidthFreamSize		�������\���̕�
//		const int		HeightFreamSize		�������\���̍���
//
//
//============================================================================
void CBackForeProc::TutolialTextMisionSentence(const int WidthFreamPos, const int HeightFreamPos, const int FreamWidth, const int FreamHeight, const int WidthFreamSize, const int HeightFreamSize)
{
	//�e�L�X�g�̘g�\��
	m_pSprite->Draw(m_pImageExplanationFrame, WidthFreamPos, HeightFreamPos, 0, 0, FreamWidth, FreamHeight, WidthFreamSize, HeightFreamSize, 1.0f);

	if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
	{
		PhaseTextNum++;
	}
	if (PhaseTextNum > PhaseNum[pNameNum] + nPhaseNumAll) {		//���̃t�F�[�Y�Ɉڍs
		if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
		{
			TutorialTextExplanationEnd();
		}
	}

	m_nCntTime++;

};


//============================================================================
//
//   �`���[�g���A���e�L�X�g�ϐ��̏�����
//
//
//============================================================================
void CBackForeProc::TutorialTextInit()
{
	PhaseTextNum=0;
	pNameNo=0;
	nPhaseNumAll=0;
	TutorialPhaseTextNo=0;
	pNameNum=0;
	dwQueastTextNum = -1;

	//�z�񏉊���
	int ArrSize = TutorialPhaseArr.size();
	if (ArrSize > 0) {
		for (int i = 0; i < ArrSize; i++)
		{
			TutorialPhaseArr[i].PhaseTextArray.clear();
			TutorialPhaseArr[i].PhaseTextArray.shrink_to_fit();
		}
		TutorialPhaseArr.clear();
		TutorialPhaseArr.shrink_to_fit();
	}

}

//============================================================================
//
//   �e�L�X�g�t�F�[�Y�̃e�L�X�g�����I����������̃t�F�[�Y�ɂ���
//
//
//============================================================================
void CBackForeProc::TutorialTextSentenceEnd()
{

	if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	
	{
		m_nCntTime = 0;
		pNameNo++;
		nPhaseNumAll = PhaseTextNum;
		TutorialPhaseTextNo++;
		pNameNum++;
	}


};

//============================================================================
//
//   �e�L�X�g�t�F�[�Y�̃e�L�X�g�����I����������̃t�F�[�Y�ɂ���i�N���A�����t����Ƃ��j
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//
//============================================================================
void CBackForeProc::TutorialTextExplanationEnd()
{

	if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	
	{
		m_pGMain->m_dPhase++;			//�S�̂̃t�F�[�Y��i�߂�
		pNameNo++;						//�������̃^�C�g���̔ԍ���i�߂�
		nPhaseNumAll = PhaseTextNum;	//���݂܂ł̃e�L�X�g�����X�V
		TutorialPhaseTextNo = 0;		//�g�[�^���t�F�C�Y�̒��̃e�L�X�g�̃t�F�[�Y�����Z�b�g
		pNameNum++;						//�������̃^�C�g�����𑝂₷
		m_nCntTime = 0;					//�J�E���g�����Z�b�g
		dwQueastTextNum++;				//�N���A�����̕\���i���o�[
	}


};

//============================================================================
//
//   �`���[�g���A���~�b�V�����̃e�L�X�g�\��
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//
//============================================================================
void CBackForeProc::TutorialMisionText()
{
	const int TitleBackPosX = 0;		//�~�b�V�����^�C�g���̃p�^�[���ʒuX
	const int TitleBackPosY = 0;		//�~�b�V�����^�C�g���̃p�^�[���ʒuY
	const int TitleBackWidth = 190;		//�~�b�V�����^�C�g���̃p�^�[����
	const int TitleBackHeight = 30;		//�~�b�V�����^�C�g���̃p�^�[������
	const int TextBackPosX = 0;			//�~�b�V�����w�i�̃p�^�[���ʒuX
	const int TextBackPosY = 53;		//�~�b�V�����w�i�̃p�^�[���ʒuY
	const int TextBackWidth = 380;		//�~�b�V�����w�i�̃p�^�[����
	const int TextBackHeight = 190;		//�~�b�V�����w�i�̃p�^�[������
	int TextBackHeightUp = 0;			//�~�b�V�����e�L�X�g�̍s��

	int	TextFontSize = 20;				//�~�b�V�����e�L�X�g�����̃T�C�Y

	const int	BackPosX = 30, BackPosY = 120;		//�\���ʒu
	const int	TitlePosX = 43, TitlePosY = 122;		//�^�C�g���\���ʒu
	const int	TitleBackSize = 30;					//�^�C�g���\���T�C�Y

	for (int i = 0; PhaseQueastText[dwQueastTextNum][i][0] != '\0'; i++) {		//�e�L�X�g�̔w�i�̃T�C�Y�𕶎��ɍ��킹��
		TextBackHeightUp = (i * TextFontSize) + 70;
	}
	m_pSprite->Draw(m_pQuestTextBack, BackPosX, BackPosY + (TitleBackHeight), TextBackPosX, TextBackPosY, TextBackWidth, TextBackHeight, TextBackWidth, TextBackHeightUp, 1.0f);		//�~�b�V�����w�i�̕\��
	m_pSprite->Draw(m_pQuestTextBack, BackPosX, BackPosY, TitleBackPosX, TitleBackPosY, TitleBackWidth, TitleBackHeight, TitleBackWidth + 50, TitleBackHeight, 1.0f);					//�~�b�V�����^�C�g���̔w�i�̕\��
	m_pGMain->m_pFont->Draw(TitlePosX, TitlePosY, _T("TUTORIAL MISSION"), TitleBackSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));											//�~�b�V�����^�C�g���̕\��

	for (int i = 0; PhaseQueastText[dwQueastTextNum][i][0] != '\0'; i++) {		//�����̕\��	���̍s�̍ŏ��̕������k���ɂȂ�܂Ō�������
		int	FontSize = 30;		//�t�H���g�T�C�Y
		int TextInterval = 20;	//�s��
		const int TextPosX=50, TextPosY = 140;	//�~�b�V�����e�L�X�g�̕\���ʒu
		const int ClearPosX = TextBackWidth-8, ClearPosY = 120;	//�~�b�V�����e�L�X�g�̕\���ʒu
		const int ClearStartPosX = 0, ClearStartPosY = 435;	//�~�b�V�����e�L�X�g�̃p�^�[���ʒu
		const int ClearStartWidth = 76, ClearStartHeight = 76;	//�~�b�V�����e�L�X�g�̃p�^�[���T�C�Y
		const int ClearWidth = 76, ClearHeight = 76;	//�~�b�V�����e�L�X�g�̕\���T�C�Y

		m_pGMain->m_pFont->Draw(TextPosX, TextPosY + (TitleBackHeight) + (TextInterval * i), PhaseQueastText[dwQueastTextNum][i], FontSize, RGB(0, 0, 0), 1.0f, _T("���C���I �{�[���h"));	//�e�L�X�g�\��
		if (PhaseQueastText[dwQueastTextNum][i + 1][0] == '\0') {		//�N���A�̕\��
			if (m_pGMain->m_pMapProc->GetPhaseClear() == TRUE)m_pSprite->Draw(m_pQuestTextBack, ClearPosX, ClearPosY, ClearStartPosX, ClearStartPosY, ClearStartWidth, ClearStartHeight, ClearWidth, ClearHeight, 1.0f);

		}
	}


};



//============================================================================
//
//   �`���[�g���A���e�L�X�g�̑�\��
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//
//============================================================================
void CBackForeProc::TutorialTextDisplay()
{
	//�������̃^�C�g��
	TCHAR PName[][20] = {
		_T("�`���[�g���A��"),
		_T("���[��"),
		_T("UI"),
		_T("�v���C���[�̈ړ�"),
		_T("�{�[��"),
		_T("�I"),
		_T("���e�{�[��"),
		_T("�X�L��"),
		_T("�X�L��"),

	};

		const int	PNamePosX = 130, PNamePosY = 80;	//�^�C�g���̕\���ʒu
		const int	PNameSize=50;						//�^�C�g���̕\���T�C�Y

		m_pGMain->m_pFont->Draw(PNamePosX, PNamePosY, PName[pNameNo], PNameSize, RGB(255, 128, 0), 1.0f, _T("���C���I �{�[���h"));			//�������̃^�C�g���\��
		for (int i = 0; i < (sizeof(PhaseText) / sizeof(*PhaseText)); i++) {
			const int	FontSize = 30;						//�����T�C�Y
			const int	TextPosX = 330, TextPosY = 540;		//�����̕\���ʒu
			m_pGMain->m_pFont->Draw(TextPosX, TextPosY + (FontSize * i), PhaseText[PhaseTextNum][i], FontSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));		//�e�L�X�g���̕\��
		}





};

//------------------------------------------------------------------------
//
//	���C�����[�h�̔w�i
//
//------------------------------------------------------------------------
void CBackForeProc::MainModeBackFore()
{
	int Phase = m_pGMain->m_pMapProc->GetPhaseMap();
	int nCount = m_pGMain->m_pMapProc->GetCount();
	const int StartCount = 120;		//�X�^�[�g���ɑ҂���
	switch (Phase)
	{
	case 0:
		if (nCount >= StartCount) {
			MainModeStartCount();

		}
		break;
	case 1:
		break;
	case 2:
		MainModeEnd();
		break;

	default:
		break;
	}
};


//------------------------------------------------------------------------
//
//	���C�����[�h�̃X�^�[�g�J�E���g	
//
//
//------------------------------------------------------------------------
void CBackForeProc::MainModeStartCount()
{
	TCHAR str[256];
	DWORD	dwStartCountSize = 500;		//�\���T�C�Y
	DWORD	dwStartCountPosX = (WINDOW_WIDTH / 2) - (dwStartCountSize / 2)-80, dwStartCountPosY = (WINDOW_HEIGHT / 2) - (dwStartCountSize / 2);	//�\���ʒu
	int		nStartCountNum = 3 - ((m_pGMain->m_pMapProc->GetCount()-120)/60);	//�\�����鐔��
	MATRIX4X4	mWorld = XMMatrixTranslation(dwStartCountPosX, dwStartCountPosY,0);
	if (nStartCountNum > 0) {	//�J�E���g��\��
		_stprintf(str, _T("%3d"), nStartCountNum);
		m_pGMain->m_pFont->Draw(mWorld, str, dwStartCountSize, RGB(255, 255, 255), 1.0, _T("���C���I �{�[���h"));
	}
	else if(nStartCountNum<=0) {	//�X�^�[�g��\��
		dwStartCountPosX = dwStartCountPosX - 250;
		mWorld = XMMatrixTranslation(dwStartCountPosX, dwStartCountPosY, 0);
		m_pGMain->m_pFont->Draw(mWorld, _T("START"), dwStartCountSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));

	}
};
//------------------------------------------------------------------------
//
//	���C�����[�h�̏I��	
//
//------------------------------------------------------------------------
void CBackForeProc::MainModeEnd()
{
	TCHAR str[256];		//�\���T�C�Y
	DWORD	dwStartCountSize = 500;
	DWORD	dwStartCountPosX = (WINDOW_WIDTH / 2) - (dwStartCountSize / 2) - 80, dwStartCountPosY = (WINDOW_HEIGHT / 2) - (dwStartCountSize / 2);	//�\���ʒu

	m_pGMain->m_pFont->Draw(dwStartCountPosX, dwStartCountPosY, _T("�I��"), dwStartCountSize, RGB(255, 255, 255), 1.0f, _T("���C���I �{�[���h"));

};
//------------------------------------------------------------------------
//
//	�}���`���[�h�̍X�V	
//
//
//------------------------------------------------------------------------
void CBackForeProc::MultiUpdate()
{
	//�P�v���C���[�̏���
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	CWeaponSwordObj* pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr();
	int DestX = 0;					//�P��ʂ̍���X
	int DestY = WINDOW_HEIGHT/2;	//�P��ʂ̍���Y
	MultiUpdateConstruction(pPcObj, pWeaponObj, DestX, DestY);

	//�Q�v���C���[�̏���
	pPcObj = m_pGMain->m_pPcProc->GetPcSecObjPtr();
	pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr();
	DestX = 0;						//�Q��ʂ̍���X
	DestY = WINDOW_HEIGHT;			//�Q��ʂ̍���X
	MultiUpdateConstruction(pPcObj, pWeaponObj, DestX, DestY);
	
};

//============================================================================
//
//
//   �}���`�̃X�L�����̍X�V�ƕ\��
//
//	CPcObj*				pPcObj	�v���C���[�I�u�W�F�N�g
//	CWeaponSwordObj*	pWeaponObj	���I�u�W�F�N�g
//	int					DestX	��ʂ̍���X
//	int					DestY	��ʂ̍���Y
//
//============================================================================
void CBackForeProc::MultiUpdateConstruction(CPcObj* pPcObj, CWeaponSwordObj* pWeaponObj,int DestX, int DestY)
{
	const int nWidth = 258, nHeight = 258;			//���̑傫��
	const int nWidthScale = nWidth / 2;				//�\���傫��
	const int nHeightScale = nHeight / 2;			//�\���傫��
	const int WeaponSet = 1;						//�X�L���̐�


	//�X�L�����̘g
	const int nColumnWidth = 250, nColumnHeight = 250;	//�p�^�[���̑傫��
	const int nColumnWidthScale = nColumnWidth / 2, nColumnHeightScale = nColumnHeight / 2;		//�\���傫��

	//�X�L�����̊O�g
	const int nFreamWidth = 272, nFreamHeight = 272;	//�p�^�[���̑傫��
	const int nFreamWidthScale = nFreamWidth / 2, nFreamHeightScale = nFreamHeight / 2;		//�\���傫��
	const int nFreamDist = (nFreamHeight - nColumnHeight) / 2;	//�X�L�������Ƃ̕�

	const int nFreamNormalStartX = 300, nFreamNormalStartY = 0;	//�p�^�[������(�m�[�}��)
	const int nFreamChoiceStartX = 0, nFreamChoiceStartY = 300;	//�p�^�[������(�I��)
	const int nFreamUseStartX = 300, nFreamUseStartY = 300;	//�p�^�[������(������)

	const int MultiDestX=10, MultiDestY=100;		//�ʒu�̒���

	float WaitTime[100];		//�c��̃N�[���^�C��
	float WaitMaxTime[100];		//�N�[���^�C���ő�l
	int		WeaponNo = pPcObj->GetWeaponNo();
	int		WeaponColuman = pPcObj->GetWeaponColuman() - 1;
	float	RemWaitTime[100];	//�N�[���^�C���̊���

	int	LineNum = (m_pGMain->m_pTitleProc->GetWeaponNum() / 5) + 1;		//�X�L���̑I�𗓂̍s�̐�

	for (int i = 0; i < WeaponSet; i++)
	{

		WaitMaxTime[i] = pWeaponObj->GetWeaponMaxWaitTime(i);
		WaitTime[i] = pWeaponObj->GetWeaponWaitTime(i);		//���ꂼ��̃X�L���̃N�[���^�C�����擾
		RemWaitTime[i] = WaitTime[i] / WaitMaxTime[i];
		if (WaitTime[i] > 0) {
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY + ((nHeightScale*(RemWaitTime[i]))), 0, nHeight*(RemWaitTime[i]), nColumnWidth, nColumnHeight*(1 - RemWaitTime[i]), nWidthScale, nHeightScale*(1 - RemWaitTime[i]));		//�N�[���^�C�����̕\��
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, 0, 0, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale, 0.5);		//�N�[���^�C�����̕\��
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, nFreamNormalStartX, nFreamNormalStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);

		}
		else if (pPcObj->GetSkillActive(i) == TRUE) {			//�X�L��������
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, 0, 0, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale);
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, nFreamUseStartX, nFreamUseStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);


		}
		else if (WeaponColuman == i) {						//�I�𒆂̃X�L������g�t���ɂ���
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, 0, 0, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale);
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, nFreamChoiceStartX, nFreamChoiceStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);

		}
		else {
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, 0, 0, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale);
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, nFreamNormalStartX, nFreamNormalStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);

		}


		DWORD WeaponSelectNo= pPcObj->GetWeaponColumanNo(i);
		int y = (WeaponSelectNo - 1) / 5;
		int x = 0;
		//�I�������X�L�����I�𗓂̂Ȃ��ڂɂ��邩
		for (int j = 0; j < LineNum; j++)
		{
			if (((j + 1) * 5) > (WeaponSelectNo - 1))
			{

				x = (WeaponSelectNo - 1) - 5;
				if (x < 0) {
					x = (WeaponSelectNo - 1);
				}
				break;
			}
		}

		float	ReduceGage[100];
		ReduceGage[i] = WaitTime[i] / WaitMaxTime[i];
		ReduceGage[i] = (nHeight * (1 + y)) * ReduceGage[i];
		ReduceGage[i] = (nHeight * (1 + y)) - ReduceGage[i];
		ReduceGage[i] = ReduceGage[i] / (1 + y);
		if (WeaponSelectNo != NULL) {		//�X�L�����Z�b�g���ꂽ�Ƃ��ɃX�L����\��
			if (WaitTime[i] > 0) {
				m_pSprite->Draw(m_pImageWeapon, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY + ((nHeightScale*(RemWaitTime[i]))), nWidth*x, ((nHeight*(y + 1)) - (ReduceGage[i])), nWidth, (nHeight*(1 - RemWaitTime[i])), nWidthScale, nHeightScale*(1 - RemWaitTime[i]));		//�N�[���^�C�����̕\��
				m_pSprite->Draw(m_pImageWeapon, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, nWidth*x, nHeight*y, nWidth, nHeight, nWidthScale, nHeightScale, 0.5);		//�N�[���^�C�����̕\��	

			}
			else {
				m_pSprite->Draw(m_pImageWeapon, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, nWidth*x, nHeight*y, nWidth, nHeight, nWidthScale, nHeightScale);
			}
		}

	}

}

//------------------------------------------------------------------------
//	�}���`���[�h�̍X�V	
//
//
//------------------------------------------------------------------------
void CBackForeProc::MultiUpdateScore()
{
	//�P�v���C���[�̏���
	int nScoreImagePosX = 0, nScoreImagePosY = 45;	//�X�R�A�̃C���[�W�\���ʒu
	int nScoreTextPosX = 10, nScoreTextPosY = 8;	//�X�R�A�̃e�L�X�g�\���ʒu
	int nScorePointPosX = 0, nScorePointPosY = 55;	//�X�R�A�̃|�C���g�ʒu
	UpdateScore(nScoreImagePosX, nScoreImagePosY, nScoreTextPosX, nScoreTextPosY, nScorePointPosX, nScorePointPosY, m_pGMain->m_nScore);	//�X�R�A�̕\������

	//�Q�v���C���[�̏���
	int nWinHeight = WINDOW_HEIGHT / 2;
	nScoreImagePosX = 0,nScoreImagePosY = 45+ nWinHeight;
	nScoreTextPosX = 10, nScoreTextPosY = 8+ nWinHeight;
	nScorePointPosX = 0, nScorePointPosY = 55+ nWinHeight;
	UpdateScore(nScoreImagePosX, nScoreImagePosY, nScoreTextPosX, nScoreTextPosY, nScorePointPosX, nScorePointPosY, m_pGMain->m_nScoreSec);

};


//------------------------------------------------------------------------------
//CSV�t�@�C���̃G�N�Z����ǂݍ���
//
//
//------------------------------------------------------------------------------

void CBackForeProc::FileTextRead()
{
	char fname[30] = "Data/Read/PhaseText.csv";
	fopen_s(&fp, fname, "r"); // �t�@�C�����J���B���s�����NULL��Ԃ��B
	int i = 0;
	int j = 0;
	bool check = false;
	int Text_count = 0;
	int Sentence_count = 0;
	int Column = 0;
	int	Line = 0;
	char chr[100][100] = { '\0' };
	char chr2;

	while ((chr2 = fgetc(fp)) != EOF) {
		if (chr2 == '"') {
			if (check != true) check = true;
			else if (check != false) check = false;
		}
		if (j == 0 && (chr2 == ','|| chr2 == '\n')&& check != true)
		{
			if (chr2 == '\n')	// �G�N�Z���̍s��ς��ēǂݍ��݁i��̐����ő�l�ɖ������ĂȂ��s�����s�������j
			{
				PhaseNum[Column] = (Line-1);
				Column++;
				Line = 0;

			}
			i++;
			j = 0;
			Sentence_count = 0;

		}
		else if (chr2 == ',') {
			chr[i][j] = '\0';
			//printf("%s", chr[i]);
			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, PhaseText[Text_count][Sentence_count], (sizeof PhaseText) / 2);
			Text_count++;
			i++;
			j = 0;
			Sentence_count = 0;
			Line++;
		}
		else if (check != true && chr2 == '\n') {		//�G�N�Z���̍s��ς��ēǂݍ���
			chr[i][j] = '\0';
			//printf("%s", chr[i]);
			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, PhaseText[Text_count][Sentence_count], (sizeof PhaseText[Text_count][Sentence_count]) / 2);
			PhaseNum[Column] = Line;
			Column++;
			Line = 0;
			Text_count++;
			i++;
			j = 0;
			Sentence_count = 0;
		}
		else if (check != false && chr2 == '\n') {		//�Z�����ŉ��s

			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, PhaseText[Text_count][Sentence_count], (sizeof PhaseText[Text_count][Sentence_count]) / 2);
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


	//--------------------------------------------------------------------------

	char fname2[30] = "Data/Read/PhaseQueastText.csv";
	fopen_s(&fp, fname2, "r"); // �t�@�C�����J���B���s�����NULL��Ԃ��B
	i = 0;
	j = 0;
	check = false;
	Text_count = 0;
	Sentence_count = 0;
	Column = 0;
	Line = 0;
	chr[100][100] = { '\0' };
	chr2='\0';

	while ((chr2 = fgetc(fp)) != EOF) {
		if (chr2 == '"') {
			if (check != true) check = true;
			else if (check != false) check = false;
		}
		if (j == 0 && (chr2 == ',' || chr2 == '\n') && check != true)
		{
			if (chr2 == '\n')	// �G�N�Z���̍s��ς��ēǂݍ��݁i��̐����ő�l�ɖ������ĂȂ��s�����s�������j
			{
				PhaseQueastNum[Column] = (Line - 1);
				Column++;
				Line = 0;

			}
			i++;
			j = 0;
			Sentence_count = 0;

		}
		else if (chr2 == ',') {
			chr[i][j] = '\0';
			//printf("%s", chr[i]);
			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, PhaseText[Text_count][Sentence_count], (sizeof PhaseQueastText) / 2);
			Text_count++;
			i++;
			j = 0;
			Sentence_count = 0;
			Line++;
		}
		else if (check != true && chr2 == '\n') {		//�G�N�Z���̍s��ς��ēǂݍ���
			chr[i][j] = '\0';
			//printf("%s", chr[i]);
			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, PhaseQueastText[Text_count][Sentence_count], (sizeof PhaseQueastText[Text_count][Sentence_count]) / 2);
			PhaseQueastNum[Column] = Line;
			Column++;
			Line = 0;
			Text_count++;
			i++;
			j = 0;
			Sentence_count = 0;
		}
		else if (check != false && chr2 == '\n') {		//�Z�����ŉ��s

			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, PhaseQueastText[Text_count][Sentence_count], (sizeof PhaseQueastText[Text_count][Sentence_count]) / 2);
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
