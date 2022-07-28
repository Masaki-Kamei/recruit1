//=============================================================================
//
//		�v���C�L�����N�^�[�̐���
//																Playchar.cpp
//=============================================================================
#include  "Playchar.h"
#include  "Camera.h"
#include  "BackFore.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"
#include  "Enemy.h"
#include  "Title.h"


//============================================================================
//
// �o�b�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CPcProc::CPcProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nNum = 3;    // PC�̍ő�o����
	const int test = 1;

	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Char/PC9/Pc9.mesh"));    // �L�����N�^�[
	m_pMesh->LoadAnimation(_T("Data/Char/PC9/PC9_Idle.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/PC9/PC9_Run.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/PC9/PC9_Run.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/PC9/PC9_Hit.anmx"));		
	m_pMesh->LoadAnimation(_T("Data/Char/PC9/PC9_Death.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/PC9/PC9_Hit_Rev.anmx"));		

	m_pMesh->m_fHeightMax = 0.01f;
	m_pMesh->m_iMaxDevide = 16;
	m_nHoldItem.m_nHoldObjNo = 3;	// ��Ɏ��X�L���̃I�u�W�F�ԍ�(�����ȃ��P�b�g)
	m_nHoldItem.m_nPosMesh = 0;		// ���P�b�g�̍����ʒu�̃��b�V���ԍ�
	m_nHoldItem.m_nPosBone = 13;	// ���P�b�g�̍����ʒu�̃{�[���ԍ�
	m_nHoldItem.m_nOffsetPos = VECTOR3(0.02f, 0.04f, -0.03f);  // ��Ɏ��X�L���̈ʒu�I�t�Z�b�g
	m_nHoldItem.m_nOffsetRot = VECTOR3(0.0f, 0.0f, 90.0f);  // ��Ɏ��X�L���̊p�x�I�t�Z�b�g


		// -------------------------------------------------------------------------
	m_pObjArray.push_back(new CPcObj(m_pGMain));	// m_pObjArray�ɃI�u�W�F�N�g��o�^����
	((CPcObj*)m_pObjArray[0])->SetMesh(this);		// ���b�V���|�C���^��ݒ肷��
	((CPcObj*)m_pObjArray[0])->SetPlayerNo(FIRSTPLAYER);


	if (test == 1)
	{
		m_pMeshSecond = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Char/PC10/Pc10.mesh"));    // �L�����N�^�[
		m_pMeshSecond->LoadAnimation(_T("Data/Char/PC10/PC10_Idle.anmx"));
		m_pMeshSecond->LoadAnimation(_T("Data/Char/PC10/PC10_Run.anmx"));
		m_pMeshSecond->LoadAnimation(_T("Data/Char/PC10/PC10_Run.anmx"));
		m_pMeshSecond->LoadAnimation(_T("Data/Char/PC10/PC10_Hit.anmx"));		
		m_pMeshSecond->LoadAnimation(_T("Data/Char/PC10/PC10_Death.anmx"));
		m_pMeshSecond->LoadAnimation(_T("Data/Char/PC10/PC10_Hit_Rev.anmx"));		

		m_pMeshSecond->m_fHeightMax = 0.01f;
		m_pMeshSecond->m_iMaxDevide = 16;
		
		m_pObjArray.push_back(new CPcObj(m_pGMain));	// m_pObjArray�ɃI�u�W�F�N�g��o�^����
		((CPcObj*)m_pObjArray[1])->SetMeshSecond(this);		// ���b�V���|�C���^��ݒ肷��
		((CPcObj*)m_pObjArray[1])->SetPlayerNo(SECONDPLAYER);
	}
	m_nPcNum = nNum;
	
}

// ---------------------------------------------------------------------------
//
// �o�b�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CPcProc::~CPcProc()
{
	SAFE_DELETE(m_pMesh);
	SAFE_DELETE(m_pMeshSecond);

}


//============================================================================
//
// �o�b�I�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CGameMain* pGMain;		// �Q�[�����C���N���X�ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CPcObj::CPcObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nHP = 1000;    // �̗�
	const int nAtc = 50;      // �̂̍U����

	m_bActive = TRUE;
	m_dwStatus = NORMAL;

	m_fLocalRotY = 0.0f;                 
	m_bSide = TRUE;                      

	m_fSpeed = 0.16f;      // �ړ����x     
	m_fRotSpeed = 8.0f;   // ��]���x     
	m_fJumpSpeed = 0.2f;  // �W�����v���x  
	m_fNormalSpeed = m_fSpeed;

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.25f, -0.05f, -0.25f), VECTOR3(0.25f, 2.0f, 0.25f));
	m_pBBox->m_mWorld = m_mWorld;                           
	m_nHp = m_nMaxHp = nHP;
	m_nAtc = nAtc;
	bSwordHitTrigger = FALSE;
	dwUseNumSkill = 0;
}
// ---------------------------------------------------------------------------
//
// �o�b�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CPcObj::~CPcObj()
{
	;
}

// ---------------------------------------------------------------------------
//
// �o�b�I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CPcProc* pProc
//
// ---------------------------------------------------------------------------
void CPcObj::SetMesh(CPcProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^
	m_nHoldItem = pProc->GetHoldItem();			// ��Ɏ��X�L���̏��𓾂� 

	//�A�j���[�V���������l
	m_AnimStatus.SetNum(0);
	m_AnimStatus.animFrame = 0;

}
// ---------------------------------------------------------------------------
//
// �o�b2�I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CPcProc* pProc
//
// ---------------------------------------------------------------------------
void CPcObj::SetMeshSecond(CPcProc* pProc)
{
	m_pMesh = pProc->GetMeshSecond();					// �X�L�����b�V���̃|�C���^
	m_nHoldItem = pProc->GetHoldItem();			// ��Ɏ��X�L���̏��𓾂�  

	//�A�j���[�V���������l
	m_AnimStatus.SetNum(0);
	m_AnimStatus.animFrame = 0;

}

// ---------------------------------------------------------------------------
//
// �o�b�I�u�W�F�N�g�̃��[�J�����}�g���b�N�X�𓾂�֐�
//
//  m_mWorld�̈ʒu����m_fLocalRotY�̊p�x��������
//  ���[�J�����}�g���b�N�X��Ԃ�
//
// ---------------------------------------------------------------------------
MATRIX4X4 CPcObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


//-----------------------------------------------------------------------------
// �o�b�I�u�W�F�N�g�̍X�V
//
//�@�L�[�{�[�h�ło�b�𓮂���
//�@�o�b�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ԊҁA�}�b�v�Ƃ̐ڐG����
//�@�o�b�̍U���������s��
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CPcObj::Update()
{

	// ��O�̈ʒu��ۑ�
	m_mWorldOld = m_mWorld;
	if (m_bStop != TRUE) {	

		// �e��Ԃɉ���������
		switch (m_dwStatus) {
		case  FLASH:  // �o�b���_���[�W���畜�A�����Ƃ��̏���
		case  NORMAL: // �o�b���ʏ��Ԃ̂Ƃ��̏���
			UpdateNormal();  // �o�b�I�u�W�F�N�g�̍X�V �ʏ��ԁiNORMAL�j
			break;

		case  DAMAGE: // �o�b���_���[�W��Ԃ̂Ƃ��̏���
			UpdateDamage();  // �o�b�I�u�W�F�N�g�̍X�V �_���[�W��ԁiDAMAGE�j
			break;

		}
	}
	else if (m_bStop == TRUE) {
		if(m_AnimStatus.animFrame>=m_AnimStatus.endFrame)
		m_AnimStatus.SetNum(0);		//�v���C���[���~�܂��Ă���Ƃ��ɃA�j���[�V�����ԍ����[���ɖ߂�
	}


	// �}�b�v�R���W�����Ǝ��R����
	m_fJumpY += (0.5f*GRAVITY*0.00005f)*m_fJumpTime;	// ���R����
	m_fJumpTime += 1.0f;
	if (m_pGMain->m_pMapSubProc->isCollisionMoveGravity(&m_mWorld, m_mWorldOld) != 3)  // �}�b�v�R���W����
	{
		m_fJumpY = 0.0f;  // ���R�����̒�~
		m_fJumpTime = 0.0f;
	}
	m_pGMain->m_pWeaponProc->m_pWeaponWallProc->isCollisionMoveGravity(&m_mWorld, m_mWorldOld,m_dwPlayerNo);	

	SpeedUpAft();		// �X�s�[�h�A�b�v���c�����c��

	if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
	// �o�E���f�B���O�{�b�N�X
	m_pBBox->m_mWorld = m_mWorld;


	// ��Ɏ��X�L����A�C�e���̕\��������     
	if (m_nHoldItem.m_nHoldObjNo != 0) // ��Ɏ��X�L����A�C�e��������Ƃ�
	{
		MATRIX4X4 mHold;
		mHold = m_pMesh->GetFrameMatrices(m_AnimStatus, m_mWorld, m_nHoldItem.m_nPosBone, m_nHoldItem.m_nPosMesh);  // ��̈ʒu�̃{�[���}�g���b�N�X
		m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->Disp(mHold, m_nHoldItem,m_dwPlayerNo); // �A�C�e���\��
	}

	SkillUpdate();		


}

//-----------------------------------------------------------------------------  
// �o�b�I�u�W�F�N�g�̍X�V �ʏ��ԁiNORMAL�j
//
//�@�L�[�{�[�h�ło�b�𓮂���
//�@�o�b�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ԊҁA�}�b�v�Ƃ̐ڐG����
//�@�o�b�̍U���������s��
//
//
//   �����@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormal()
{
	if (m_dwStatus == FLASH) // �o�b���_���[�W���畜�A�����Ƃ��̏���
	{
		m_nCnt1--;
		if (m_nCnt1 <= 0) m_dwStatus = NORMAL;
	}
	UpdateNormalMove();      // �o�b�I�u�W�F�N�g�̈ړ�����
	if(m_pGMain->m_dwGameStatus != GAMEMULTI)UpdateNormalAttack();    // �o�b�I�u�W�F�N�g�̍U������
}
//-----------------------------------------------------------------------------  
// �o�b�I�u�W�F�N�g�̈ړ�����
//
//�@�L�[�{�[�h�^�}�E�X�ło�b�𓮂���
//�@�o�b�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ԊҁA�}�b�v�Ƃ̐ڐG����
//
//
//   �����@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormalMove()
{
	CDirectInput* pDI = m_pGMain->m_pDI;

	MATRIX4X4 mYaw;  // �o�b�x����]�}�g���b�N�X
	MATRIX4X4 mPos;  // �o�b�ړ��}�g���b�N�X
	BOOL	  bKeyPush = FALSE;// �L�[�����������ǂ����̃`�F�b�N
	const float fRotLowSpeed = m_fRotSpeed / 6;   // ���[�J�����i�x���j�̉�]���x

	// �L�[�{�[�h�A�}�E�X�A�W���C�X�e�B�b�N����

	// ���R�����̏����l
	mPos = XMMatrixTranslation(0.0f, m_fJumpY, 0.0f);

	// ���[�J�����i�x���j�̉�]����  --------------------------------
	if (m_pGMain->m_dwGameStatus != GAMEMULTI) {
		if (pDI->CheckKey(KD_DAT, DIK_RIGHT) || pDI->CheckMouse(KD_DAT, DIM_RIGHT) || pDI->CheckJoy(KD_DAT, DIJ_R)) //	���L�[
		{
			m_fLocalRotY += fRotLowSpeed;
			if (m_fLocalRotY >= 360.0f) m_fLocalRotY -= 360.0f;
		}

		if (pDI->CheckKey(KD_DAT, DIK_LEFT) || pDI->CheckMouse(KD_DAT, DIM_LEFT) || pDI->CheckJoy(KD_DAT, DIJ_L)) //	���L�[
		{
			m_fLocalRotY -= fRotLowSpeed;
			if (m_fLocalRotY < 0.0f) m_fLocalRotY += 360.0f;
		}
	}

	if(m_dwPlayerNo==FIRSTPLAYER)mPos = UpdateNormalFirstPCMove(mPos);
	if (m_dwPlayerNo == SECONDPLAYER)mPos = UpdateNormalSecondPCMove(mPos);

	if (m_pGMain->m_dwGameStatus == GAMEMULTI) {

		if (m_dwPlayerNo == FIRSTPLAYER)SwingMoveFirst();
		if (m_dwPlayerNo == SECONDPLAYER)SwingMoveSecond();
	}

	// ���[�J��������Ƃ��āA�o�b���ړ������郏�[���h�}�g���b�N�X��ݒ�
	mYaw = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));
	m_mWorld = mPos * mYaw * GetLocalMatrix();

}

//-----------------------------------------------------------------------------   
// �o�b�I�u�W�F�N�g�̈ړ������@�L�[���얈�̊e��ړ�����
//
//   �����@DWORD Key �L�[��ʁ@DirectInput�̃L�[�R�[�h
//
//   �߂�l  �ړ��}�g���b�N�X
//-----------------------------------------------------------------------------
MATRIX4X4 CPcObj::UpdateNormalMoveKeystate(DWORD DIKey)
{
	MATRIX4X4 mPos;
	int WalkOnoCount = 8;	//�������̋[���o�����Ԃ̊Ԋu
	int WalkOnoPosMin = -1;	//�[���̏o���ʒu�̍ŏ��l�i�����j
	int WalkOnoPosFewMin = 1;	//�[���̏o���ʒu�̍ŏ��l�i�����j
	int WalkOnoPosMax = 1;	//�[���̏o���ʒu�̍ő�l�i�����j
	int WalkOnoPosFewMax = 5;	//�[���̏o���ʒu�̍ő�l�i�����j
	//�[���̃X�e�[�^�X
	VECTOR2 vWalkOnoSize = VECTOR2(0.5, 0.5);	//�\���T�C�Y	
	VECTOR2 vWalkOnoSrcPos = VECTOR2(64, 0);	//�p�^�[���ʒu
	VECTOR2 vWalkOnoSrcSize = VECTOR2(64, 64);	//�p�^�[���T�C�Y
	DWORD dwWalkOnoFreamEnd = 30;				//�\������

	if (m_AnimStatus.animNum == 0) m_AnimStatus.SetNum(1);
	if (m_AnimStatus.isEnd(1))     m_AnimStatus.SetNum(2);

	//�[���̏o���ݒ�
	float fRPosX= Random(WalkOnoPosMin, WalkOnoPosMax);
	fRPosX =(fRPosX* Random(WalkOnoPosFewMin, WalkOnoPosFewMax))/10;
	MATRIX4X4 mDisWorld = XMMatrixTranslation(fRPosX, 0.5, 0)*m_mWorld;
	VECTOR3 vNowPos = GetPositionVector(mDisWorld);
	//�[���̕\��
	if(m_AnimStatus.animFrame%WalkOnoCount==0)		m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), vNowPos, vWalkOnoSize, vWalkOnoSrcPos, vWalkOnoSrcSize, dwWalkOnoFreamEnd, m_dwPlayerNo, LENO_EXPANISIONTYPE,1.0);	

	if (m_bSide && DIKey != DIK_W)   // �T�C�h���[�h�őO�i�ȊO�̂Ƃ�
	{
		switch (DIKey)
		{
		case DIK_S:    // ���
			// ������ς����Ɍ��
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, -m_fSpeed);
			break;
		case DIK_D:
			// ������ς����ɉE�ړ�
			mPos = XMMatrixTranslation(m_fSpeed, m_fJumpY, 0.0f);
			break;
		case DIK_A:    // ��
			// ������ς����ɍ��ړ�
			mPos = XMMatrixTranslation(-m_fSpeed, m_fJumpY, 0.0f);
			break;
		}
	}
	else {
		// �i�s�����ɉ�]���Ă���O�i

		// ���[�g�{�[���A�j���[�V�������s�����ǂ������[�g�A�j���[�V�����^�C�v���m�F����
		if (m_pMesh->GetRootAnimType(m_AnimStatus.animNum) == eRootAnimNone)
		{
			// ���[�g�{�[���A�j���[�V�������s�킸�Œ�̑O�i�ړ��l
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, m_fSpeed);
		}
		else {
			// ���[�g�{�[���A�j���[�V�����ł̑O�i�ړ��l
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, 0.0f) * m_pMesh->GetRootAnimUpMatrices(m_AnimStatus);
		}

		// �i�s�����ɉ�]���鏈��
		// �E��]�p�x��m_vRotUp.y�ɂ���B-180�`180�x
		// �E�P��̉�]���x��m_fRotSpeed
		if (m_vRotUp.y > 180.0f)  m_vRotUp.y -= 360.0f;
		if (m_vRotUp.y < -180.0f) m_vRotUp.y += 360.0f;

		float fAngle;  // �ڕW��]�p�x

			switch (DIKey)
			{
			case DIK_W:    // �O�i
				fAngle = 0.0f;
				break;
			case DIK_S:    // ���
				if (m_vRotUp.y >= 0)  // �ŏ���]�ɂȂ�悤�ɕ��������킹��
				{
					fAngle = 180.0f;
				}
				else {
					fAngle = -180.0f;
				}
				break;
			case DIK_D:    // �E
				fAngle = 90.0f;
				if (m_vRotUp.y == -180.0f) m_vRotUp.y = 180.0f;  // �ŏ���]�ɂȂ�悤�ɕ��������킹��
				break;
			case DIK_A:    // ��
				fAngle = -90.0f;
				if (m_vRotUp.y == 180.0f) m_vRotUp.y = -180.0f;  // �ŏ���]�ɂȂ�悤�ɕ��������킹��
				break;
			}
		if (m_vRotUp.y > fAngle)  // ����]
		{
			m_vRotUp.y -= m_fRotSpeed;
			if (m_vRotUp.y < fAngle) m_vRotUp.y = fAngle;
		}
		if (m_vRotUp.y < fAngle)  // �E��]
		{
			m_vRotUp.y += m_fRotSpeed;
			if (m_vRotUp.y > fAngle) m_vRotUp.y = fAngle;
		}

	}




	return mPos;
}

//-----------------------------------------------------------------------------  
// �t�@�[�X�g�o�b�I�u�W�F�N�g�̈ړ������@�L�[����
//
//
//   �߂�l  �ړ��}�g���b�N�X
//-----------------------------------------------------------------------------
MATRIX4X4 CPcObj::UpdateNormalFirstPCMove(MATRIX4X4 mPos)
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	BOOL	  bKeyPush = FALSE;// �L�[�����������ǂ����̃`�F�b�N
	const float fRotLowSpeed = m_fRotSpeed / 6;   // ���[�J�����i�x���j�̉�]���x

	if (pDI->CheckKey(KD_DAT, DIK_J)) //	J�L�[
	{
		m_fLocalRotY += fRotLowSpeed;
		if (m_fLocalRotY >= 360.0f) m_fLocalRotY -= 360.0f;
	}

	if (pDI->CheckKey(KD_DAT, DIK_G)) //	G�L�[
	{
		m_fLocalRotY -= fRotLowSpeed;
		if (m_fLocalRotY < 0.0f) m_fLocalRotY += 360.0f;
	}

	if (m_AnimStatus.animNum != 3 && m_AnimStatus.animNum != 5) {

		if (pDI->CheckKey(KD_DAT, DIK_W)) //	W�L�[
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_W);
		}
		// ��ޏ���
		if (pDI->CheckKey(KD_DAT, DIK_S)) //S�L�[
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_S);
		}
			// �E�ړ�����
		if (pDI->CheckKey(KD_DAT, DIK_D))//D�L�[
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_D);
		}
			// ���ړ�����
		if (pDI->CheckKey(KD_DAT, DIK_A))//A�L�[
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_A);
		}
		
	}

	if (!bKeyPush && m_AnimStatus.animNum != 3 && m_AnimStatus.animNum != 5)  // �L�[�������Ă��Ȃ��Ƃ�
	{
		m_AnimStatus.SetNum(0);
	}

	return mPos;
}

//-----------------------------------------------------------------------------  
// �Z�J���h�o�b�I�u�W�F�N�g�̈ړ������@�L�[����
//
//
//   �߂�l  �ړ��}�g���b�N�X
//-----------------------------------------------------------------------------
MATRIX4X4 CPcObj::UpdateNormalSecondPCMove(MATRIX4X4 mPos)
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	BOOL	  bKeyPush = FALSE;// �L�[�����������ǂ����̃`�F�b�N

	const float fRotLowSpeed = m_fRotSpeed / 6;   // ���[�J�����i�x���j�̉�]���x


	if (pDI->CheckMouse(KD_DAT, DIM_RIGHT)) //	�}�E�X�E�ړ�
	{
		m_fLocalRotY += fRotLowSpeed;
		if (m_fLocalRotY >= 360.0f) m_fLocalRotY -= 360.0f;
	}

	if (pDI->CheckMouse(KD_DAT, DIM_LEFT)) //	�}�E�X���ړ�
	{
		m_fLocalRotY -= fRotLowSpeed;
		if (m_fLocalRotY < 0.0f) m_fLocalRotY += 360.0f;
	}


	if (m_AnimStatus.animNum != 3 && m_AnimStatus.animNum != 5) {

		if (pDI->CheckKey(KD_DAT, DIK_UP)) //	���L�[
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_W);
		}
		// ��ޏ���
		if (pDI->CheckKey(KD_DAT, DIK_DOWN)) //���L�[
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_S);
		}
			// �E�ړ�����
		if (pDI->CheckKey(KD_DAT, DIK_RIGHT))//���L�[
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_D);
		}
			// ���ړ�����
		if (pDI->CheckKey(KD_DAT, DIK_LEFT))//���L�[
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_A);
		}
		
	}

	if (!bKeyPush && m_AnimStatus.animNum != 3 && m_AnimStatus.animNum != 5)  // �L�[�������Ă��Ȃ��Ƃ�		
	{
		m_AnimStatus.SetNum(0);
	}

	return mPos;
}


//-----------------------------------------------------------------------------  
// �o�b�I�u�W�F�N�g�̍U������
//
//�@�L�[�{�[�h�^�}�E�X�ło�b�̍U���������s��
//
//
//   �����@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormalAttack()
{
	CDirectInput* pDI = m_pGMain->m_pDI;

	//-----------------------------------------------
	//�X�L���̃i���o�[�̐ݒ�		
	if (m_pGMain->m_dModeType != SIMPLEMODE)		//���C�����[�h�Ȃ�	
	{
		if (pDI->CheckKey(KD_TRG, DIK_1)) // 1�L�[
		{
			SetSkillNo(1);
		}
		if (pDI->CheckKey(KD_TRG, DIK_2)) // 2�L�[
		{
			SetSkillNo(2);
		}
		if (pDI->CheckKey(KD_TRG, DIK_3)) // 3�L�[
		{
			SetSkillNo(3);
		}




		//�w�������
		if (pDI->CheckKey(KD_TRG, DIK_C)) // C�L�[
		{
			dwRotTrigger = TRUE;
		}
		if (dwRotTrigger) {
			int MaxRotCount = 5;
			if (dwRotCount < MaxRotCount) {
				m_fLocalRotY += 36;
				dwRotTrigger = TRUE;
				dwRotCount++;
				if (dwRotCount >= MaxRotCount)
				{
					dwRotTrigger = FALSE;
					dwRotCount = 0;
				}
			}
		}

	}

	// ------------------------------------------------------------- 
	// 
	// �E��Ɏ��X�L���E���P�b�g�������Ă��Ȃ��ƃ��P�b�g�U���͂ł��Ȃ�
		if ( pDI->CheckMouse(KD_TRG, DIM_RBUTTON)) // Z�L�[
		{
			if (m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetKind(m_nHoldItem) == 1 && m_AnimStatus.animNum != 5) m_AnimStatus.SetNum(3);   // ��Ɏ��A�C�e���E���P�b�g�������Ă���Ƃ��́A���P�b�g�U���̊J�n
		}
		if (m_AnimStatus.animNum == 3)
		{
			SwingAnimProcess(3);
		}

		if (pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) // �t�ł�	

		{
			if (m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetKind(m_nHoldItem) == 1 && m_AnimStatus.animNum != 3) m_AnimStatus.SetNum(5);   // ��Ɏ��A�C�e���E���P�b�g�������Ă���Ƃ��́A���P�b�g�U���̊J�n
		}
		if (m_AnimStatus.animNum == 5)
		{
			SwingAnimProcess(5);
		}
	
}
//-----------------------------------------------------------------------------  
//
//	�X�L������I��
//
//	int		nSkillColumanNo	�I�������X�L�����̔ԍ�	
//
//
//-----------------------------------------------------------------------------

void	CPcObj::SetSkillNo(const int nSkillColumanNo)
{
	CWeaponSwordObj*	pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr();
	if(m_dwPlayerNo==SECONDPLAYER)pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr();		
	int SkillColumanNo = nSkillColumanNo;		//�I�������X�L�����̔ԍ�
	int SkillNo = SkillColumanNo - 1;			//�I�������X�L���̔ԍ�


	if (m_nWeaponColuman == SkillColumanNo) {		//�X�L�����L�����Z��
		m_nWeaponColuman = 0;
		m_nWeaponNo = 0;
	}
	else  if (pWeaponObj->GetWeaponWaitTime(SkillNo)<= 0) {
		m_nWeaponColuman = SkillColumanNo;		//�X�L������g�t���ɂ���	
		m_nWeaponNo = m_nWeaponColumanNo[SkillNo];		//�X�L���̃i���o�[���擾	
		SkillStart(SkillNo);		

	}
	
}

//----------------------------------------------------------------------------- 
//	�t�@�[�X�g�v���C���[���X�C���O���Ă鎞�̏���
//
//
//-----------------------------------------------------------------------------

void	CPcObj::SwingMoveFirst()
{
	CDirectInput* pDI = m_pGMain->m_pDI;

	if (pDI->CheckKey(KD_TRG, DIK_1) && m_dwPlayerNo == FIRSTPLAYER) // 1�L�[
	{
		SetSkillNo(1);
	}


	if (pDI->CheckKey(KD_TRG, DIK_SPACE)) // Z�L�[
	{
		if (m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetKind(m_nHoldItem) == 1 && m_AnimStatus.animNum != 5) m_AnimStatus.SetNum(3);   // ��Ɏ��A�C�e���E���P�b�g�������Ă���Ƃ��́A���P�b�g�U���̊J�n
	}
	if (m_AnimStatus.animNum == 3)
	{
		SwingAnimProcess(3);
	}

	if (pDI->CheckKey(KD_TRG, DIK_LSHIFT)) // �t�ł�		

	{
		if (m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetKind(m_nHoldItem) == 1 && m_AnimStatus.animNum != 3) m_AnimStatus.SetNum(5);   // ��Ɏ��A�C�e���E���P�b�g�������Ă���Ƃ��́A���P�b�g�U���̊J�n
	}
	if (m_AnimStatus.animNum == 5)
	{
		SwingAnimProcess(5);
	}


}
//----------------------------------------------------------------------------- 
//
//	�Z�J���h�v���C���[���X�C���O���Ă鎞�̏���
//
//
//-----------------------------------------------------------------------------

void	CPcObj::SwingMoveSecond()
{
	CDirectInput* pDI = m_pGMain->m_pDI;

	if (pDI->CheckKey(KD_TRG, DIK_RSHIFT) && m_dwPlayerNo == SECONDPLAYER) // 1�L�[
	{
		SetSkillNo(1);
	}


	if (pDI->CheckMouse(KD_TRG, DIM_RBUTTON)) // Z�L�[
	{
		if (m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetKind(m_nHoldItem) == 1 && m_AnimStatus.animNum != 5) m_AnimStatus.SetNum(3);   // ��Ɏ��A�C�e���E���P�b�g�������Ă���Ƃ��́A���P�b�g�U���̊J�n
	}
	if (m_AnimStatus.animNum == 3)
	{
		SwingAnimProcess(3);
	}

	if (pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) // �t�ł�		

	{
		if (m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetKind(m_nHoldItem) == 1 && m_AnimStatus.animNum != 3) m_AnimStatus.SetNum(5);   // ��Ɏ��A�C�e���E���P�b�g�������Ă���Ƃ��́A���P�b�g�U���̊J�n
	}
	if (m_AnimStatus.animNum == 5)
	{
		SwingAnimProcess(5);
	}

}


//----------------------------------------------------------------------------- 
//
//	�v���C���[���X�C���O���Ă鎞�̏���
//
//	int		nSwingAnimNo	�X�C���O�������̃A�j���[�V�����ԍ�	
//
//
//-----------------------------------------------------------------------------

void	CPcObj::SwingAnimProcess(const int nSwingAnimNo)
{

	MATRIX4X4 mSword, mHold;
	VECTOR3 vMin, vMax;
	int SwingAnimNo = nSwingAnimNo;
	VECTOR2 vSwingOnoSize = VECTOR2(2.5, 1.0);		//�\���T�C�Y	
	VECTOR2 vSwingOnoSrcPos = VECTOR2(588, 338);	//�p�^�[���ʒu
	VECTOR2 vSwingOnoSrcSize = VECTOR2(147, 46);	//�p�^�[���T�C�Y
	DWORD dwSwingOnoFreamEnd = 100;					//�\������


	mHold = m_pMesh->GetFrameMatrices(m_AnimStatus, m_mWorld, m_nHoldItem.m_nPosBone, m_nHoldItem.m_nPosMesh);  // ��̈ʒu�̃{�[���}�g���b�N�X
	m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetInfo(mHold, m_nHoldItem, mSword, vMin, vMax); // �{�[���}�g���b�N�X���w�肵�Ď�Ɏ��A�C�e�����𓾂�
	m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->Start(mSword, vMin, vMax, PC,m_dwPlayerNo);  // ���P�b�g�U���̊J�n	
	if (m_AnimStatus.animNum == SwingAnimNo && m_AnimStatus.animFrame >= m_AnimStatus.endFrame - 2)
	{
		m_AnimStatus.SetNum(0);
		MATRIX4X4 mDisWorld = XMMatrixTranslation(-0.5, 2, 0)*m_mWorld;
		VECTOR3 vNowPos = GetPositionVector(mDisWorld);
		if (bSwordHitTrigger == FALSE)m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), vNowPos, vSwingOnoSize, vSwingOnoSrcPos, vSwingOnoSrcSize, dwSwingOnoFreamEnd, m_dwPlayerNo, LENO_RIZETYPE,1.0);
		bSwordHitTrigger = FALSE;

	}

}

//-----------------------------------------------------------------------------   
// �o�b�I�u�W�F�N�g�̍X�V �_���[�W��ԁiDAMAGE�j
//
//�@�_���[�W���󂯂��Ƃ��̏���
//
//
//   �����@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateDamage()
{

	MATRIX4X4 mTemp;
	const int nFlashTime = 5;      // ���G��Ԃ̎���
	const float fBlowDis = -0.15f;

	//������΂��ꂽ�Ƃ��̕���
	if (m_AnimStatus.animNum != 4) {
		m_AnimStatus.SetNum(4);
		m_mWorld=TurnTarget(m_mWorld, m_pHitObj->GetWorld());
	}
	if (m_AnimStatus.animFrame < m_AnimStatus.endFrame - 60)
	{
		
		mTemp = XMMatrixTranslation(0, 0, fBlowDis);	// �o�b�N����
		m_mWorld = mTemp * m_mWorld;
	}
	m_nHp -= m_pHitObj->GetAtc();	// �U�����󂯂��_���[�W
	//������΂����A�j���[�V����		
	if (!m_AnimStatus.isEnd(4))
	{
		m_dwStatus = DAMAGE;     // �_���[�W����̕��A�������s��

	}
	else {
		m_dwStatus = FLASH;     // �_���[�W����̕��A�������s��
		m_AnimStatus.SetNum(0);

	}
}


//-----------------------------------------------------------------------------
//
// �X�L��������
//
// int		nWeaponColumanNo�@�X�L�����̃i���o�[
//
//
//-----------------------------------------------------------------------------
BOOL   CPcObj::SkillStart(const int nWeaponColumanNo)
{
	BOOL bRet = FALSE;

	CWeaponSwordObj*	pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr();
	if (m_dwPlayerNo == SECONDPLAYER)pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr();	


	if (m_nWeaponNo == WEAPON_SKILLPCBOOL)
	{
		if (bBoolSkillTrigger == TRUE) {
			m_nWeaponColuman = 0;		//�X�L���g�p���I��������	
			m_nWeaponNo = 0;

		}

		if (pWeaponObj->GetWeaponWaitTime(nWeaponColumanNo) <= 0)
		{
			if (bBoolSkillTrigger != TRUE&& bSkillActive[nWeaponColumanNo]!=TRUE)	
			{
				bBoolSkillTrigger = TRUE;
				bSkillActive[nWeaponColumanNo] = TRUE;
				nSkillTime[nWeaponColumanNo] = WEAPON_SKILLPCBOOL_TIME;
				m_nWeaponColuman = 0;		//�X�L���g�p���I��������
				m_nWeaponNo = 0;
				bRet = TRUE;
				dwUseNumSkill++;	

			}
		}

	}

	//���͂̒e�𐁂���΂��X�L��	
	if (m_nWeaponNo == WEAPON_SKILLBOUNCE)
	{
		CBaseProc*	BallProc = m_pGMain->m_pEnmProc->m_pEnmBallProc;
		for (DWORD i = 0; i < BallProc->GetObjArrayPtr().size(); i++)
		{
			CBaseObj*	BallObj = BallProc->GetObjArrayPtr()[i];
			if (BallObj->GetPlayerNo() == m_dwPlayerNo) {
				VECTOR3		vPos = GetPositionVector(m_mWorld);
				VECTOR3		vBallPos = GetPositionVector(BallObj->GetWorld());
				float	fDist = magnitude(vBallPos - vPos);
				float   fRange = 10;		//���苗��
				if (fDist < fRange) {		//���͂̒e�����苗����菬����������
					if (BallObj->GetDamage() != TRUE)
					{
						MATRIX4X4	BallWorld = BallObj->GetWorld();
						MATRIX4X4	BallRotY = XMMatrixRotationY(XMConvertToRadians(180));
						BallWorld = BallRotY * TurnTarget(BallWorld, m_mWorld);

						BallObj->SetWorld(BallWorld);
						BallObj->SetDamage(TRUE);
						BallObj->SetStatus(DAMAGE);
					}
				}
			}
		}
		pWeaponObj->SetWeaponWaitTime(nWeaponColumanNo, WEAPON_SKILLPCBOOL_WAITTIME);
		pWeaponObj->SetWeaponMaxWaitTime(nWeaponColumanNo, WEAPON_SKILLPCBOOL_WAITTIME);
		m_nWeaponColuman = 0;		//�X�L���g�p���I��������	
		m_nWeaponNo = 0;
		dwUseNumSkill++;	
		if (m_pGMain->m_dwGameStatus == GAMEMULTI)
		{
			WeaponUseMulti();
		}

	}

	//�X�s�[�h�A�b�v�X�L��	
	if (m_nWeaponNo == WEAPON_SKILLSPEEDUP)
	{

		if (bSpeedSkillTrigger == TRUE) {
			m_nWeaponColuman = 0;		//�X�L���g�p���I����������		
			m_nWeaponNo = 0;

		}

		if (pWeaponObj->GetWeaponWaitTime(nWeaponColumanNo) <= 0)
		{

			if (bSpeedSkillTrigger != TRUE && bSkillActive[nWeaponColumanNo] != TRUE)
			{
				for (int i = 0; i < 4; i++)		//�c�������l�̐ݒ�
				{
					AfterSta.mWorldOld[i] = m_mWorld;
					AfterSta.SaveFrame[i] = m_AnimStatus.animFrame;
					AfterSta.SaveFrameNo[i] = m_AnimStatus.animNum;
				}
				bSpeedSkillTrigger = TRUE;
				bSkillActive[nWeaponColumanNo] = TRUE;
				nSkillTime[nWeaponColumanNo] = WEAPON_SKILLSPEEDUP_TIME;
				m_nWeaponColuman = 0;		//�X�L���g�p���I��������	
				m_nWeaponNo = 0;
				m_fSpeed = m_fSpeed * 1.5;
				bRet = TRUE;
				dwUseNumSkill++;	

			}
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------
//
// �X�L����񏈗�
//
//
//
//
//-----------------------------------------------------------------------------
void  CPcObj::SkillUpdate()
{
	BOOL	bActiveSkill[10] = {FALSE};

	for (int i = 0; i < 3; i++) {
		if (nSkillTime[i] > 0) {

			if (nCount[i] > 60) {
				nSkillTime[i]--;
				nCount[i] = 0;
			}
			else {
				nCount[i]++;
			}
			bActiveSkill[i] = TRUE;
		}
		else if (nSkillTime[i] <= 0) {
			nSkillTime[i] = 0;
			bActiveSkill[i] = FALSE;
		}

		if (bActiveSkill[i] != TRUE)
		{
			SkillTime(i);

		}


	}


}


//-----------------------------------------------------------------------------
//
// �X�L���N�[�����ԏI����
//
// int		nWeaponColumanNo�@�X�L�����̃i���o�[
//
//
//-----------------------------------------------------------------------------
void  CPcObj::SkillTime(const int nWeaponColumanNo)
{
	CWeaponSwordObj*	pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr();
	if (m_dwPlayerNo == SECONDPLAYER)pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr();	



	if (m_nWeaponColumanNo[nWeaponColumanNo] == WEAPON_SKILLPCBOOL)
	{
		if (bBoolSkillTrigger != FALSE && bSkillActive[nWeaponColumanNo] != FALSE)		//������
		{
			bBoolSkillTrigger =FALSE;
			bSkillActive[nWeaponColumanNo] = FALSE;
			pWeaponObj->SetWeaponWaitTime(nWeaponColumanNo, WEAPON_SKILLPCBOOL_WAITTIME);
			pWeaponObj->SetWeaponMaxWaitTime(nWeaponColumanNo, WEAPON_SKILLPCBOOL_WAITTIME);
			if(m_pGMain->m_dwGameStatus== GAMEMULTI)WeaponUseMulti();
		}
	}


	if (m_nWeaponColumanNo[nWeaponColumanNo] == WEAPON_SKILLSPEEDUP)
	{
		if ( bSkillActive[nWeaponColumanNo] != FALSE&& bSpeedSkillTrigger != FALSE)		//������
		{
			bSkillActive[nWeaponColumanNo] = FALSE;
			bSpeedSkillTrigger = FALSE;
			pWeaponObj->SetWeaponWaitTime(nWeaponColumanNo, WEAPON_SKILLSPEEDUP_WAITTIME);
			pWeaponObj->SetWeaponMaxWaitTime(nWeaponColumanNo, WEAPON_SKILLSPEEDUP_WAITTIME);
			m_fSpeed = m_fNormalSpeed;
			if (m_pGMain->m_dwGameStatus == GAMEMULTI)WeaponUseMulti();

		}
	}

}


//-----------------------------------------------------------------------------
//
// �X�s�[�h�A�b�v���c�����c��
//
////-----------------------------------------------------------------------------

void	CPcObj::SpeedUpAft()
{
	//�X�s�[�h�A�b�v���Ɏc�����o��
	if (bSpeedSkillTrigger == TRUE)
	{
		if (nAftTime % 6 == 0 && nAftTime != 0) {
			AfterSta.mWorldOld[nAfterCount] = m_mWorld;
			AfterSta.SaveFrame[nAfterCount] = m_AnimStatus.animFrame;
			AfterSta.SaveFrameNo[nAfterCount] = m_AnimStatus.animNum;
			nAfterCount++;
			if (nAfterCount >= 4)	nAfterCount = 0;
		}
		nAftTime++;
		if(m_dwPlayerNo==FIRSTPLAYER)m_pMesh->RenderAfter(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, AfterSta);
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderAfter(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePt, AfterSta);

	}
	else {
		nAftTime = 0;
		nAfterCount = 0;

	}

}

//-----------------------------------------------------------------------------
//
// �ϐ�������
//
//
////-----------------------------------------------------------------------------
void  CPcObj::Init()
{

	m_nWeaponNo=0;	
	m_nWeaponColuman=0;		
	m_nWeaponColumanNo[10] = { 0 };
	SaveEndFrame=0;	
	m_nFrameTrigger=0;	
	bSwordHitTrigger=FALSE;
	m_dwStatus = NORMAL;
	m_AnimStatus.SetNum(0);
	nSkillTime[3] = { 0 };
	nCount[3] = { 0 };
	bSkillActive[3] = { FALSE };
	m_pGMain->m_pEnmProc->m_pEnmBallProc->SetPcBoolSkill(FALSE);

	for (int i = 0; i < 3; i++) {
		bSkillActive[i] = FALSE;

	}
	dwUseNumSkill = 0;		
	m_fSpeed= m_fNormalSpeed;	
	int ArrSize = sizeof(int) / sizeof(m_nWeaponColumanNo[0]);
	for (int i = 0; i < ArrSize; i++)
	{
		m_nWeaponColumanNo[i]=0;
	}

	dwRotCount = 0;
	dwRotTrigger = 0;
}

//-----------------------------------------------------------------------------
//
// �}���`���[�h�ŃX�L�����g�������̍X�V����
//
////-----------------------------------------------------------------------------
void  CPcObj::WeaponUseMulti()
{
	m_nWeaponColumanNo[0] = 0;
	if (m_dwPlayerNo == FIRSTPLAYER) {
		m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->SetWeaponWaitTime(0, 0);
		m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->SetWeaponMaxWaitTime(0, 0);
	}
	if (m_dwPlayerNo == SECONDPLAYER)
	{
		m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr()->SetWeaponWaitTime(0, 0);
		m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr()->SetWeaponMaxWaitTime(0, 0);
	}

}


