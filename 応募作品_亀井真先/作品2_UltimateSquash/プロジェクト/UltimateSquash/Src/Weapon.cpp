//=============================================================================
//		�X�L���̏���
//															Weapon.cpp
//=============================================================================
#include  "Enemy.h"
#include  "Playchar.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"
#include  "BackFore.h"




//=============================================================================================================================
//
// �X�L�����C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ----------------------------------------------------------------------------------------------------------------------------
CWeaponProc::CWeaponProc(CGameMain* pGMain) : CBaseProc(pGMain)
{


	m_pWeaponSwordProc = new CWeaponSwordProc(pGMain);		// �X�L���E���v���V�[�W��
	m_pProcArray.push_back(m_pWeaponSwordProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����


	m_pWeaponBallProc = new CWeaponBallProc(pGMain);		// �X�L���E�{�[���v���V�[�W��
	m_pProcArray.push_back(m_pWeaponBallProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����


	m_pWeaponHoldProc = new CWeaponHoldProc(pGMain);		// �X�L���E��Ɏ��A�C�e���̃v���V�[�W��
	m_pProcArray.push_back(m_pWeaponHoldProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����



	m_pWeaponDivBallProc = new CWeaponDivBallProc(pGMain);		// �X�L���E�g�U�{�[���v���V�[�W��
	m_pProcArray.push_back(m_pWeaponDivBallProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����


	m_pWeaponShieldProc = new CWeaponShieldProc(pGMain);		// �X�L���E�V�[���h�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponShieldProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponBigBallProc = new CWeaponBigBallProc(pGMain);		// �X�L���E�r�b�O�{�[���v���V�[�W��
	m_pProcArray.push_back(m_pWeaponBigBallProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponPenetBallProc = new CWeaponPenetBallProc(pGMain);		// �X�L���E�ђʃ{�[���v���V�[�W��
	m_pProcArray.push_back(m_pWeaponPenetBallProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����
		
	m_pWeaponRollBallProc = new CWeaponRollBallProc(pGMain);		// �X�L���E��]�{�[���v���V�[�W��
	m_pProcArray.push_back(m_pWeaponRollBallProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����


	m_pWeaponWallProc = new CWeaponWallProc(pGMain);		// �X�L���E�ǃv���V�[�W��
	m_pProcArray.push_back(m_pWeaponWallProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponBendBallProc = new CWeaponBendBallProc(pGMain);		// �X�L���E�Ȃ���{�[���v���V�[�W��
	m_pProcArray.push_back(m_pWeaponBendBallProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����

}


// ================================================================================================================================
// 
// �e�X�L���v���V�[�W�����̏���
// 
// ================================================================================================================================


// ================================================================================================================================
//============================================================================
//
// �X�L���E���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponSwordProc::CWeaponSwordProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_dwProcID = WEAPON_SWORD;	
		m_pObjArray.push_back(new CWeaponSwordObj(m_pGMain));	// �X�L���E���I�u�W�F�N�g
		m_pObjArray[0]->SetObjID(m_dwProcID);
		m_pObjArray[0]->SetObjNo(0);
		m_pObjArray[0]->SetPlayerNo(FIRSTPLAYER);
		m_pObjArray.push_back(new CWeaponSwordObj(m_pGMain));	// �X�L���E���I�u�W�F�N�g
		m_pObjArray[1]->SetObjID(m_dwProcID);
		m_pObjArray[1]->SetObjNo(1);
		m_pObjArray[1]->SetPlayerNo(SECONDPLAYER);

}

// ---------------------------------------------------------------------------
//
// �X�L�����E�v���V�[�W���̔���
//
// ---------------------------------------------------------------------------

BOOL CWeaponSwordProc::Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner)
{

	m_pObjArray[0]->Start(mMat, vMin, vMax, dwOwner);	// �X�L���E���I�u�W�F�N�g

	return TRUE;
}

// ---------------------------------------------------------------------------
// �X�L�����E�v���V�[�W���̔���
//
// ---------------------------------------------------------------------------

BOOL CWeaponSwordProc::Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner, DWORD dwPlayerNo)
{
	if(dwPlayerNo==FIRSTPLAYER)m_pObjArray[0]->Start(mMat, vMin, vMax, dwOwner, dwPlayerNo);	// �X�L���E���I�u�W�F�N�g
	if (dwPlayerNo == SECONDPLAYER)m_pObjArray[1]->Start(mMat, vMin, vMax, dwOwner, dwPlayerNo);	// �X�L���E���I�u�W�F�N�g

	return TRUE;
}

//============================================================================
//
// �X�L���E���I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponSwordObj::CWeaponSwordObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;    // ���̍U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

	// BBox�̐ݒ�(�傫���́A���ɐݒ�)
	m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.1f, -0.1f, -0.1f), VECTOR3(0.1f, 0.1f, 0.1f));
	m_pBBoxSub= new CBBox(m_pGMain->m_pShader, VECTOR3(-0.1f, -0.1f, -0.1f), VECTOR3(0.1f, 0.1f, 0.1f));


	m_nAtc = nAtc;
	m_dwOwner = 0;
	dwUseNumWeapon = 0;
}
// ---------------------------------------------------------------------------
//
// �X�L���E���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponSwordObj::~CWeaponSwordObj()
{
	;
}
// ---------------------------------------------------------------------------
//
// �X�L���E���I�u�W�F�N�g�̔����Ə����A�`��
//
//     MATRIX4X4  mMat        �F���̈ʒu
//     VECTOR3 vMin        �F�o�E���f�B���O�{�b�N�X�̍ŏ��l
//     VECTOR3 vMax        �F�o�E���f�B���O�{�b�N�X�̍ő�l
//     DWORD       dwOwner     �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponSwordObj::Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner)
{
	m_bActive = TRUE;  // �X�^�[�g���ɕ\���J�n
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();

	VECTOR3 vOffset(0.0f, 0.0f, 0.0f);

	int		WeaponNo = pPcObj->GetWeaponNo();		//�X�L���̃i���o�[		
	int		WeaponColuman = pPcObj->GetWeaponColuman()-1;	//�I�𒆂̃X�L����	

	// �o�E���f�B���O�{�b�N�X�̃T�C�Y���ς���Ă�������ւ���
	if (m_pBBox->m_vMin.x != vMin.x || m_pBBox->m_vMin.y != vMin.y || m_pBBox->m_vMin.z != vMin.z
		||
		m_pBBox->m_vMax.x != vMax.x || m_pBBox->m_vMax.y != vMax.y || m_pBBox->m_vMax.z != vMax.z)
	{
		m_pBBox->InitBBox(vMin, vMax);   // �o�E���f�B���O�{�b�N�X�̑傫���ύX
	}
	m_pBBox->m_mWorld = mMat;   // �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X���Z�b�g
	
	//���U���̓����蔻����������ɂ���--------------------------------	
	MATRIX4X4 mPatternWorld = mMat;
	VECTOR3	vPatternPosition = GetPositionVector(mMat);
	MATRIX4X4 mWorldUpY = XMMatrixTranslation(0, 0.01,0);
	mPatternWorld = mWorldUpY * mPatternWorld;
	//m_pBBox->m_mWorld = mPatternWorld;
	
	VECTOR3	vMinBBox, vMaxBBox;
	vMinBBox = VECTOR3(-0.3,-1.0,-0.3);
	vMaxBBox = VECTOR3(0.0,1.0,1.0);

	m_pBBox->InitBBox(vMinBBox, vMaxBBox);
	m_pBBoxSub->InitBBox(vMinBBox, vMaxBBox);		
	VECTOR3 vBBoxPos;
	MATRIX4X4 mBBoxWorld;

	vBBoxPos = GetPositionVector(mPatternWorld);

	mBBoxWorld = XMMatrixTranslation(vBBoxPos.x, vBBoxPos.y / 2, vBBoxPos.z);
	
	MATRIX4X4 mBBoxRot = TurnTarget(mBBoxWorld, mMat);
	mBBoxRot = XMMatrixRotationY(XMConvertToRadians(180)) *mBBoxRot;
	if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetAnimStatus().animNum == 3) {		//�t��ł��̎��Ƀo�E���f�B���O�{�b�N�X�̐��ʂɌ���
		mBBoxRot = XMMatrixRotationZ(XMConvertToRadians(180)) *mBBoxRot;
	}
	m_pBBox->m_mWorld = mBBoxRot;
	m_pBBoxSub->m_mWorld = mBBoxRot;


	m_dwOwner = dwOwner;

	//------------------------------------------------

		// �G��o�b�Ƃ̂����蔻��
	BOOL	bHit = FALSE;
	//�o�E���f�B���O�{�b�N�X���m�œ����蔻����m�F
		if (m_pGMain->m_pEnmProc->m_pEnmBallProc->Hitcheck(this, m_pBBoxSub)
			|| m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->Hitcheck(this, m_pBBoxSub) || m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->Hitcheck(this, m_pBBoxSub)) {

			VECTOR3 vHitObjPos = GetPositionVector(m_pHitObj->GetWorld());
			MATRIX4X4 mHitObjWorld = XMMatrixTranslation(vHitObjPos.x, vHitObjPos.y, vHitObjPos.z);		//�q�b�g�I�u�W�F�N�g�̈ʒu���擾	

			m_pBBox->m_mWorld = GetRotateMatrix(mBBoxRot)*mHitObjWorld;		//�q�b�g�I�u�W�F�N�g�̈ʒu�Ɠ����ʒu�ɂ���
			bHit = TRUE;
			m_pHitObj->SetStatus(NORMAL);

		}
	

		if ((dwOwner != ENM && m_pGMain->m_pEnmProc->m_pEnmBallProc->HitcheckOtherLay(this)) ||
			(dwOwner != PC && m_pGMain->m_pPcProc->HitcheckOtherLay(this)))
		{

			if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//�X�L���̃N�[���^�C��		
				if (WeaponNo == WEAPON_DIV) {			//���􂷂�e�̊J�n	
					m_pGMain->m_pWeaponProc->m_pWeaponDivBallProc->Start(m_pHitObj->GetWorld(), vOffset, pPcObj->GetWorld(), PC); // �{�[������
					WeaponStart(WEAPON_DIV_WAITTIME, WeaponColuman);

				}
			}
			if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//�X�L���̃N�[���^�C��	
				if (WeaponNo == WEAPON_BIGBALL) {			//�傫���Ȃ�e�̊J�n
					m_pGMain->m_pWeaponProc->m_pWeaponBigBallProc->Start(this, m_pHitObj, PC); // �{�[������
					WeaponStart(WEAPON_BIGBALL_WAITTIME, WeaponColuman);

				}
			}
			if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//�X�L���̃N�[���^�C��		
				if (WeaponNo == WEAPON_PENETBALL) {			//�ђʂ���e�̊J�n
					m_pGMain->m_pWeaponProc->m_pWeaponPenetBallProc->Start(this, m_pHitObj, PC); // �{�[������
					WeaponStart(WEAPON_PENETBALL_WAITTIME, WeaponColuman);

				}
			}
			if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//�X�L���̃N�[���^�C��		
				if (WeaponNo == WEAPON_ROLLBALL) {			//��]����e�̊J�n	
					m_pGMain->m_pWeaponProc->m_pWeaponRollBallProc->Start(this, m_pHitObj, PC); // �{�[������
					WeaponStart(WEAPON_ROLLBALL_WAITTIME, WeaponColuman);
				}
			}

			if(m_pHitObj->GetDamage()!=TRUE)
			m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), m_vHitPos, VECTOR2(2.5, 1.0), VECTOR2(164, 391), VECTOR2(111, 30),100, m_dwPlayerNo,LENO_SHAKEBESIDETYPE,1.0);	
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetSwordHitTrigger(TRUE);

		}
	
	if(m_pGMain->m_pWeaponProc->m_pWeaponBallProc->HitcheckOtherLay(this))		m_pGMain->m_pPcProc->GetPcObjPtr()->SetSwordHitTrigger(TRUE);
	if(m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->HitcheckOtherLay(this))		m_pGMain->m_pPcProc->GetPcObjPtr()->SetSwordHitTrigger(TRUE);		
	if (m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->HitcheckOtherLay(this))
	{
		m_pGMain->m_pPcProc->GetPcObjPtr()->SetSwordHitTrigger(TRUE);
	}


	if(m_pGMain->m_pWeaponProc->m_pWeaponWallProc->Hitcheck(this, m_pBBoxSub))		m_pGMain->m_pPcProc->GetPcObjPtr()->SetSwordHitTrigger(TRUE);	


	if (m_dwStatus== DAMAGE) {
		UpdateDamage();  // �o�b�I�u�W�F�N�g�̍X�V �_���[�W��ԁiDAMAGE�j
	}

	m_bActive = FALSE;  // �P�񏈗�������A����

	return TRUE;
}


// ---------------------------------------------------------------------------
// �X�L���E���I�u�W�F�N�g�̔����Ə����A�`��
//
//     MATRIX4X4  mMat        �F���̈ʒu
//     VECTOR3 vMin        �F�o�E���f�B���O�{�b�N�X�̍ŏ��l
//     VECTOR3 vMax        �F�o�E���f�B���O�{�b�N�X�̍ő�l
//     DWORD       dwOwner     �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponSwordObj::Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner, DWORD dwPlayerNo)
{

	m_bActive = TRUE;  // �X�^�[�g���ɕ\���J�n
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	if(dwPlayerNo==SECONDPLAYER)pPcObj = m_pGMain->m_pPcProc->GetPcSecObjPtr();		
	m_dwPlayerNo = dwPlayerNo;

	VECTOR3 vOffset(0.0f, 0.0f, 0.0f);

	int		WeaponNo = pPcObj->GetWeaponNo();		//�X�L���̃i���o�[		
	int		WeaponColuman = pPcObj->GetWeaponColuman() - 1;	//�I�𒆂̃X�L����		
	// �o�E���f�B���O�{�b�N�X�̃T�C�Y���ς���Ă�������ւ���
	if (m_pBBox->m_vMin.x != vMin.x || m_pBBox->m_vMin.y != vMin.y || m_pBBox->m_vMin.z != vMin.z
		||
		m_pBBox->m_vMax.x != vMax.x || m_pBBox->m_vMax.y != vMax.y || m_pBBox->m_vMax.z != vMax.z)
	{
		m_pBBox->InitBBox(vMin, vMax);   // �o�E���f�B���O�{�b�N�X�̑傫���ύX
	}
	m_pBBox->m_mWorld = mMat;   // �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X���Z�b�g

	//���U���̓����蔻����������ɂ���--------------------------------	
	MATRIX4X4 mPatternWorld = mMat;
	VECTOR3	vPatternPosition = GetPositionVector(mMat);
	MATRIX4X4 mWorldUpY = XMMatrixTranslation(0, 0.01, 0);
	mPatternWorld = mWorldUpY * mPatternWorld;
	//m_pBBox->m_mWorld = mPatternWorld;

	VECTOR3	vMinBBox, vMaxBBox;
	vMinBBox = VECTOR3(-0.3, -1.0, -0.3);
	vMaxBBox = VECTOR3(0.0, 1.0, 1.0);

	m_pBBox->InitBBox(vMinBBox, vMaxBBox);
	m_pBBoxSub->InitBBox(vMinBBox, vMaxBBox);		

	VECTOR3 vBBoxPos;
	MATRIX4X4 mBBoxWorld;

	vBBoxPos = GetPositionVector(mPatternWorld);

	mBBoxWorld = XMMatrixTranslation(vBBoxPos.x, vBBoxPos.y / 2, vBBoxPos.z);

	MATRIX4X4 mBBoxRot = TurnTarget(mBBoxWorld, mMat);
	mBBoxRot = XMMatrixRotationY(XMConvertToRadians(180)) *mBBoxRot;
	if (pPcObj->GetAnimStatus().animNum == 3) {		//�t��ł��̎��Ƀo�E���f�B���O�{�b�N�X�̐��ʂɌ���
		mBBoxRot = XMMatrixRotationZ(XMConvertToRadians(180)) *mBBoxRot;
	}
	m_pBBox->m_mWorld = mBBoxRot;
	m_pBBoxSub->m_mWorld = mBBoxRot;


	m_dwOwner = dwOwner;

	//------------------------------------------------

		// �G��o�b�Ƃ̂����蔻��
	BOOL	bHit = FALSE;
	//�o�E���f�B���O�{�b�N�X���m�œ����蔻����m�F	
		if (m_pGMain->m_pEnmProc->m_pEnmBallProc->HitcheckMulti(this, m_pBBoxSub, dwPlayerNo) 
			|| m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->HitcheckMulti(this, m_pBBoxSub, dwPlayerNo) || m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->HitcheckMulti(this, m_pBBoxSub, dwPlayerNo)) {

			VECTOR3 vHitObjPos = GetPositionVector(m_pHitObj->GetWorld());
			MATRIX4X4 mHitObjWorld = XMMatrixTranslation(vHitObjPos.x, vHitObjPos.y, vHitObjPos.z);		//�q�b�g�I�u�W�F�N�g�̈ʒu���擾	

			m_pBBox->m_mWorld = GetRotateMatrix(mBBoxRot)*mHitObjWorld;		//�q�b�g�I�u�W�F�N�g�̈ʒu�Ɠ����ʒu�ɂ���
			bHit = TRUE;
			m_pHitObj->SetStatus(NORMAL);

		}

		if (bHit == TRUE) {
			if (m_pHitObj->GetDamage() != TRUE) {
				if ((dwOwner != ENM && m_pGMain->m_pEnmProc->m_pEnmBallProc->HitcheckMultiOtherLay(this, dwPlayerNo)) ||
					(dwOwner != PC && m_pGMain->m_pPcProc->HitcheckMultiOtherLay(this, dwPlayerNo)))
				{

					if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//�X�L���̃N�[���^�C��	
						if (WeaponNo == WEAPON_DIV) {			//���􂷂�e�̊J�n
							m_pGMain->m_pWeaponProc->m_pWeaponDivBallProc->Start(m_pHitObj->GetWorld(), vOffset, pPcObj->GetWorld(), PC, dwPlayerNo); // �{�[������
							WeaponStart(WEAPON_DIV_WAITTIME, WeaponColuman);
							if (m_pGMain->m_dwGameStatus == GAMEMULTI)pPcObj->WeaponUseMulti();

						}
					}
					if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//�X�L���̃N�[���^�C��	
						if (WeaponNo == WEAPON_BIGBALL) {			//�傫���Ȃ�e�̊J�n	
							m_pGMain->m_pWeaponProc->m_pWeaponBigBallProc->Start(this, m_pHitObj, PC, dwPlayerNo); // �{�[������	
							WeaponStart(WEAPON_BIGBALL_WAITTIME, WeaponColuman);
							if (m_pGMain->m_dwGameStatus == GAMEMULTI)pPcObj->WeaponUseMulti();


						}
					}
					if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//�X�L���̃N�[���^�C��	
						if (WeaponNo == WEAPON_PENETBALL) {			//�ђʂ���e�̊J�n	
							m_pGMain->m_pWeaponProc->m_pWeaponPenetBallProc->Start(this, m_pHitObj, PC, dwPlayerNo); // �{�[������
							WeaponStart(WEAPON_PENETBALL_WAITTIME, WeaponColuman);
							if (m_pGMain->m_dwGameStatus == GAMEMULTI)pPcObj->WeaponUseMulti();

						}
					}
					if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//�X�L���̃N�[���^�C��		
						if (WeaponNo == WEAPON_ROLLBALL) {			//��]����e�̊J�n
							m_pGMain->m_pWeaponProc->m_pWeaponRollBallProc->Start(this, m_pHitObj, PC, dwPlayerNo); // �{�[������	
							WeaponStart(WEAPON_ROLLBALL_WAITTIME, WeaponColuman);
							if (m_pGMain->m_dwGameStatus == GAMEMULTI)pPcObj->WeaponUseMulti();

						}
					}

					if (m_pHitObj->GetDamage() != TRUE)
						m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), m_vHitPos, VECTOR2(2.5, 1.0), VECTOR2(164, 391), VECTOR2(111, 30), 100, m_dwPlayerNo, LENO_SHAKEBESIDETYPE, 1.0);	//--2022.03.28.8:30
					pPcObj->SetSwordHitTrigger(TRUE);

				}
			}
		}
	if (m_pGMain->m_pWeaponProc->m_pWeaponBallProc->HitcheckMultiOtherLay(this, dwPlayerNo))		pPcObj->SetSwordHitTrigger(TRUE);
	if (m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->HitcheckMultiOtherLay(this, dwPlayerNo))		pPcObj->SetSwordHitTrigger(TRUE);	
	if (m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->HitcheckMultiOtherLay(this, dwPlayerNo))
	{
		pPcObj->SetSwordHitTrigger(TRUE);
	}


	if (m_pGMain->m_pWeaponProc->m_pWeaponWallProc->HitcheckMulti(this, m_pBBoxSub, dwPlayerNo))		pPcObj->SetSwordHitTrigger(TRUE);	


	if (m_dwStatus == DAMAGE) {
		UpdateDamage();  // �o�b�I�u�W�F�N�g�̍X�V �_���[�W��ԁiDAMAGE�j
	}




	m_bActive = FALSE;  // �P�񏈗�������A����

	return TRUE;
}




// ---------------------------------------------------------------------------
//
// �X�L���E���I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponSwordObj::Update()
{

	//�N�[���^�C������		
	for (int i = 0; i < 3; i++) {
		if (m_nWeapoWaitTime[i] > 0) {

			if (nCount[i] > 60) {
				m_nWeapoWaitTime[i]--;
				nCount[i] = 0;
			}
			else {
				nCount[i]++;
			}

		}
		else if (m_nWeapoWaitTime[i] <= 0) {
			m_nWeapoWaitTime[i] = 0;
		}

	}
	;
}

// ---------------------------------------------------------------------------
//
// �X�L���E���I�u�W�F�N�g�̃_���[�W�X�V
//
//
//
// ---------------------------------------------------------------------------

void CWeaponSwordObj::UpdateDamage() {
	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
//
//�X�L���g�p���̌Œ菈��
//
//    DWORD			dwWaitTime		�X�L�����Ƃ̃N�[���^�C��
//    const int		WeaponColuman	�X�L���̗�
//
//
// ---------------------------------------------------------------------------
void CWeaponSwordObj::WeaponStart(DWORD dwWaitTime,const int WeaponColuman)
{
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	if (m_dwPlayerNo == SECONDPLAYER)pPcObj = m_pGMain->m_pPcProc->GetPcSecObjPtr();

	m_nWeapoWaitTime[WeaponColuman] = dwWaitTime;
	m_nWeapoMaxWaitTime[WeaponColuman] = dwWaitTime;
	m_pHitObj->SetActive(FALSE);
	pPcObj->SetWeaponColuman(0);		//�X�L���g�p���I��������	
	pPcObj->SetWeaponNo(0);
	dwUseNumWeapon++;					


}


// ---------------------------------------------------------------------------
//
// �X�L���E���I�u�W�F�N�g�̃����_�����O
// (�o�E���f�B���O�{�b�N�X�̃����_�����O)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponSwordObj::Render()
{

	//   �o�E���f�B���O�{�b�N�X�����_�����O
	m_pBBox->Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	m_pBBoxSub->Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);

}

// ================================================================================================================================
//============================================================================
//
// �X�L���E�{�[���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponBallProc::CWeaponBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �{�[�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark_Big.mesh"));

	for (int i = 0; i < BALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponBallObj(m_pGMain));	// m_pObjArray�ɃX�L���E�{�[���I�u�W�F�N�g�𐶐�����
		((CWeaponBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
	}
}
//============================================================================
//
// �X�L���E�{�[���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBallProc::~CWeaponBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
//
// �X�L���E�{�[���v���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X
//  VECTOR3    vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponBallProc::Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner)
{
	MATRIX4X4 mLay, mOwnerRot, mOffset;

	mLay = GetPositionMatrix(mGun);               // �e�̈ʒu(��]����菜��)
	mOwnerRot = GetRotateMatrix(mOwnerWorld);     // ���˂���L�����̉�]�}�g���b�N�X�̂�(�ʒu����菜��)�ɂ���
	mLay = mOwnerRot * mLay;                      // �e�̈ʒu����A�L�����̕����Ŕ��˂���}�g���b�N�X�����
	mOffset = XMMatrixTranslation(vOffset.x, vOffset.y + 0.5, vOffset.z);	// �ʒu�̔�����
	mLay = mOffset * mLay;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner);	       // �X�L���E�{�[���I�u�W�F�N�g�̔���
			return TRUE;
		}
	}
	return FALSE;
}

//============================================================================
//
// �X�L���E�{�[���I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBallObj::CWeaponBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // �U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-0.15f, -0.15f, -0.15f);
	VECTOR3 vMax(0.15f, 0.15f, 0.15f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                           

}
// ---------------------------------------------------------------------------
//
// �X�L���E�{�[���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBallObj::~CWeaponBallObj()
{
	;
}

// ---------------------------------------------------------------------------
//
// �X�L���E�{�[���I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     �{�[���̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner        �X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponBallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	const float fSpeed = 0.05f;		// �{�[���̑���
	const int nLifeTime = 300;		// �{�[���̎�������
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;

	m_vPosUp = VECTOR3(0, 0, fSpeed);
	m_vGravity = VECTOR3(0, fSpeed, 0);

	m_nCnt1 = nLifeTime;
	m_dwOwner = dwOwner;
	return TRUE;
}

// ---------------------------------------------------------------------------
//
// �{�[���I�u�W�F�N�g�̃��[�J�����}�g���b�N�X�𓾂�֐�
//
//  m_mWorld�̈ʒu����m_fLocalRotY�̊p�x��������
//  ���[�J�����}�g���b�N�X��Ԃ�
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponBallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
//
// �X�L���E�{�[���I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponBallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		MATRIX4X4 mTran;
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// �����{�[���̈ʒu����ƈړ�
		VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // �����̑O�̈ʒu


	// �G��o�b�Ƃ̂����蔻��
		if ((m_dwOwner != ENM && m_pGMain->m_pEnmProc->Hitcheck(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld))) ||
			(m_dwOwner != PC && m_pGMain->m_pPcProc->Hitcheck(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld))))
		{
			VECTOR3 vN = GetPositionVector(m_pHitObj->GetWorld()) - GetPositionVector(m_pHitObj->GetWorldOld());
			if (vN.x == 0 && vN.z == 0) {

				vN = m_vHitNormal;

			}
			vN = normalize(vN);
			VECTOR3 vR;
			if (vHear != vHearOld) {

				VECTOR3 vL = normalize(vHear - vHearOld);
				vR = (2 * dot(-vL, vN)*vN) + vL;

			}
			else {

				vR = vN;

			}

			m_mWorld = GetLookatMatrix(vHear, vHear + vR);


			m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���	

		}
		else {
			// �}�b�v�Ƃ̂����蔻��
			VECTOR3 vHit, vNormal;

			if (m_pGMain->m_pMapProc->Hitcheck(GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), &vHit, &vNormal))
			{
				VECTOR3 vL = normalize(GetPositionVector(m_mWorld) - GetPositionVector(m_mWorldOld));  // �ړ��x�N�g���i���K���j
				VECTOR3 vN = normalize(vNormal);            // �ڐG�|���S���̖@���i���K���j
				VECTOR3 vR = (2 * dot(-vL, vN) * vN) + vL;  // ���˃x�N�g���̌���
				m_mWorldOld = m_mWorld = GetLookatMatrix(vHit, vHit + vR);  // �ڐG�_���甽�ː������}�g���b�N�X���쐬���A���[���h�}�g���b�N�X�ɑ��
				m_vGravity.y *= -1;
				m_pGMain->m_pEffectProc->m_pParticleProc->Start(vHit, m_dwPlayerNo, vNormal);	// �p�[�e�B�N���̔���	

			}


		}

		if (m_pGMain->m_pEnmProc->m_pEnmTargetProc->HitcheckOtherLay(this)) {



		}

		switch (m_dwStatus)
		{

		case DAMAGE:
			m_pGMain->m_nScore++;
			UpdateDamage();

			break;
		}
		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_bActive = FALSE;
		}
		m_pBBox->m_mWorld = m_mWorld;

		// �����_�����O
		Render();

	}
}
//----------------------------------------------------------------------------
//�{�[��������������
//----------------------------------------------------------------------------
void CWeaponBallObj::UpdateDamage()
{


	ObjReflection();

	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���



	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
//
// �X�L���E�{�[���I�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponBallObj::Render()
{

	// �{�[���̃����_�����O
	//m_pMesh->Render(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	m_pMesh->RenderToon(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	m_pBBox->Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);

}


// ============================================================================================================================
//============================================================================
//
// �X�L���E��Ɏ��A�C�e���v���V�[�W���̃R���X�g���N�^
//
// �E���ڍU������X�L���ł͂Ȃ��A�X�L����\��������A�ʒu����Ԃ����肷��
//
//   ���b�V���̓v���V�[�W���ł͂Ȃ��A�I�u�W�F�N�g�œǂݍ���
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponHoldProc::CWeaponHoldProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (int i = 0; i < HOLDITEM_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponHoldObj(m_pGMain));	// m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		m_pObjArray[i]->SetObjNo(i);    // �I�u�W�F�N�g�m�n���I�u�W�F�N�g�ɐݒ肷��
		((CWeaponHoldObj*)m_pObjArray[i])->Init();   // �I�u�W�F�N�g�̏�����
	}
}
// ---------------------------------------------------------------------------
//
// �X�L���E��Ɏ��A�C�e���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponHoldProc::~CWeaponHoldProc()
{
	;
}

// ---------------------------------------------------------------------------
//
// �X�L���E��Ɏ��A�C�e���v���V�[�W���̏��𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ��X�L���̏��
//     MATRIX4X4& mMat        :��Ɏ��X�L���̃}�g���b�N�X(Out)
//     VECTOR3& vMin          :�o�E���f�B���O�{�b�N�X��Min(Out)
//     VECTOR3& vMax          :�o�E���f�B���O�{�b�N�X��Max(Out)
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void  CWeaponHoldProc::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax)
{
	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetInfo(mHold, HoldItem, mMat, vMin, vMax);	// �X�L���E���I�u�W�F�N�g

	return;
}
// ---------------------------------------------------------------------------
//
// �X�L���E��Ɏ��A�C�e���v���V�[�W���̏��𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ��X�L���̏��
//     MATRIX4X4& mMat        :��Ɏ��X�L���̃}�g���b�N�X(Out)
//     VECTOR3& vOffset       :�e���܂ł̃I�t�Z�b�g(Out)
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void  CWeaponHoldProc::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset)
{
	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetInfo(mHold, HoldItem, mMat, vOffset);	// �X�L���E�e�I�u�W�F�N�g

	return;
}

// ---------------------------------------------------------------------------
//
// �X�L���E��Ɏ��A�C�e���v���V�[�W���̃o�E���f�B���O�{�b�N�X�𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ��X�L���̏��
//
//     �߂�l�@�@CBBox* �o�E���f�B���O�{�b�N�X
// ---------------------------------------------------------------------------
CBBox*  CWeaponHoldProc::GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{
	return ((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetBBox(mHold, HoldItem);	// �X�L���E���I�u�W�F�N�g
}

// ---------------------------------------------------------------------------
//
// �X�L���E��Ɏ��A�C�e���v���V�[�W���̕\��
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ��X�L���̏��
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
BOOL CWeaponHoldProc::Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem,DWORD dwPlayerNo)
{

	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->Disp(mHold, HoldItem, dwPlayerNo);	// �X�L���E���I�u�W�F�N�g

	return TRUE;
}
//============================================================================
//
// �X�L���E��Ɏ��A�C�e���I�u�W�F�N�g�̃R���X�g���N�^
//
// �E���ڍU������X�L���ł͂Ȃ��A�X�L����\��������A�ʒu����Ԃ����肷��
//
// ---------------------------------------------------------------------------
CWeaponHoldObj::CWeaponHoldObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_nKindNo = 0;
	m_pMesh = NULL;
	m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �I�t�Z�b�g�̐ݒ�
}
//============================================================================
//
// �X�L���E��Ɏ��A�C�e���I�u�W�F�N�g�̏�����
//
// �E���b�V���́A�v���V�[�W���ł͂Ȃ��I�u�W�F�N�g�̒��ɐݒ肷��
//
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Init()
{

	switch (m_dwObjNo)
	{
	case 0:     // ���ݒ�
		m_nKindNo = 0;
		m_pMesh = NULL; // �I�u�W�F�N�g�͖���
		m_pBBox = NULL; // BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �I�t�Z�b�g�Ȃ�


	case 3:     // ���i�\�[�h�j���b�V���̐ݒ�
		m_nKindNo = 1;  // 1:��ʁ@��
		m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Weapon_Bad.mesh"));
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-1.15f, 0.1f, -0.15f), VECTOR3(1.15f, 1.8f, 1.15f));// BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	default:
		m_nKindNo = 0;
		m_pMesh = NULL; // �I�u�W�F�N�g�͖���
		m_pBBox = NULL; // BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �I�t�Z�b�g�Ȃ�
		break;
	}

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

}
// ---------------------------------------------------------------------------
//
// �X�L���E��Ɏ��A�C�e���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponHoldObj::~CWeaponHoldObj()
{
	SAFE_DELETE(m_pMesh);
}

// ---------------------------------------------------------------------------
//
// �X�L���E��Ɏ��A�C�e���I�u�W�F�N�g�̏��𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ��X�L���̏��
//     MATRIX4X4& mMat        :��Ɏ��X�L���̃}�g���b�N�X(Out)
//     VECTOR3& vMin          :�o�E���f�B���O�{�b�N�X��Min(Out)
//     VECTOR3& vMax          :�o�E���f�B���O�{�b�N�X��Max(Out)
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void  CWeaponHoldObj::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax)
{
	// �I�t�Z�b�g�}�g���b�N�X�̌v�Z
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// 
	// ���[���h�}�g���b�N�X�̌v�Z
	// 
	// �A���A���̂Ƃ�m_mWorld��m_pBBox->m_mWorld�̐ݒ�͍s���Ă��Ȃ�!!
	// 
	mMat = mOffset * mHold;     // ���̈ʒu�̃��[���h�}�g���b�N�X

	vMin = m_pBBox->m_vMin;
	vMax = m_pBBox->m_vMax;

	return;
}

// ---------------------------------------------------------------------------
//
// �X�L���E��Ɏ��A�C�e���I�u�W�F�N�g�̏��𓾂�
//
//     MATRIX4X4  mHold       �F�e�̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ��X�L���̏��
//     MATRIX4X4& mMat        :��Ɏ��X�L���̃}�g���b�N�X(Out)
//     VECTOR3& vOffset       :�e���܂ł̃I�t�Z�b�g(Out)
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void  CWeaponHoldObj::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset)
{
	// �I�t�Z�b�g�}�g���b�N�X�̌v�Z
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ���[���h�}�g���b�N�X�̌v�Z
	// 
	// �A���A���̂Ƃ�m_mWorld�̐ݒ�͍s���Ă��Ȃ�!!
	// 
	mMat = mOffset * mHold;     // �e�̈ʒu�̃��[���h�}�g���b�N�X

	vOffset = m_vOffset;

	return;
}

// ---------------------------------------------------------------------------
//
// �X�L���E��Ɏ��A�C�e���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ��X�L���̏��
//
//     �߂�l�@�@CBBox* �o�E���f�B���O�{�b�N�X
// ---------------------------------------------------------------------------
CBBox* CWeaponHoldObj::GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{

	// �I�t�Z�b�g�}�g���b�N�X�̌v�Z
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ���[���h�}�g���b�N�X�̌v�Z
	// 
	// �A���A���̂Ƃ�m_mWorld��m_pBBox->m_mWorld�̐ݒ���s���Ă���!!
	// 
	m_mWorld = mOffset * mHold;     // ���̈ʒu�̃��[���h�}�g���b�N�X
	m_pBBox->m_mWorld = m_mWorld;   // �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X���Z�b�g

	return m_pBBox;

}


// ---------------------------------------------------------------------------
//
// �X�L���E��Ɏ��A�C�e���I�u�W�F�N�g�̕`��
//
//     MATRIX4X4  mHold        �F�A�C�e���̈ʒu
//     VECTOR3    vPos         :�ʒu�̃I�t�Z�b�g
//     VECTOR3    vRot         :�p�x�̃I�t�Z�b�g
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
BOOL CWeaponHoldObj::Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem,DWORD dwPlayerNo)
{
	m_bActive = TRUE;  // �X�^�[�g���ɕ\���J�n
	m_dwPlayerNo = dwPlayerNo;
	// �I�t�Z�b�g�}�g���b�N�X�̌v�Z
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ���[���h�}�g���b�N�X�̌v�Z
	m_mWorld = mOffset * mHold;     // ���̈ʒu�̃��[���h�}�g���b�N�X
	if (m_pBBox) m_pBBox->m_mWorld = m_mWorld;   // �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X���Z�b�g

	// �����_�����O
	Render();

	m_bActive = FALSE;  // �P�񏈗�������A����

	return TRUE;
}

// ---------------------------------------------------------------------------
//
// �X�L���E��Ɏ��A�C�e���I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Update()
{

	//Render()
		;
}
// ---------------------------------------------------------------------------
//
// �X�L���E��Ɏ��A�C�e���I�u�W�F�N�g�̕`��
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Render()
{

	if(m_pMesh&&m_dwPlayerNo== FIRSTPLAYER)	m_pMesh->RenderToon(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	if (m_pMesh&&m_dwPlayerNo == SECONDPLAYER)	m_pMesh->RenderToon(m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);

}




// ================================================================================================================================
//============================================================================
//
// �X�L���E�g�U�{�[���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponDivBallProc::CWeaponDivBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �g�U�{�[�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark.mesh"));
	m_dwProcID = WEAPON_DIV;	

	for (int i = 0; i < DIVBALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponDivBallObj(m_pGMain));	// m_pObjArray�ɃX�L���E�g�U�{�[���I�u�W�F�N�g�𐶐�����
		((CWeaponDivBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
		m_pObjArray[i]->SetObjID(m_dwProcID);		

	}
}
//============================================================================
//
// �X�L���E�g�U�{�[���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponDivBallProc::~CWeaponDivBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
//
// �X�L���E�g�U�{�[���v���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X
//  VECTOR3    vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponDivBallProc::Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner)
{
	MATRIX4X4 mLay, mOwnerRot, mOffset;
	BOOL bRet = FALSE;

	DWORD  dwNum;
	dwNum =5;			//�o�Ă���e�̐�


	mLay = GetPositionMatrix(mGun);               // �e�̈ʒu(��]����菜��)
	mOwnerRot = GetRotateMatrix(mOwnerWorld);     // ���˂���L�����̉�]�}�g���b�N�X�̂�(�ʒu����菜��)�ɂ���
	mLay = mOwnerRot * mLay;                      // �e�̈ʒu����A�L�����̕����Ŕ��˂���}�g���b�N�X�����
	mOffset = XMMatrixTranslation(vOffset.x, vOffset.y + 0.5, vOffset.z);	// �ʒu�̔�����
	mLay = mOffset * mLay;
	for (DWORD n = 0; n < dwNum; n++)
	{
		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				((CWeaponDivBallObj*)(m_pObjArray[i]))->Start(mLay, dwOwner,n,dwNum);	       // �X�L���E�g�U�{�[���I�u�W�F�N�g�̔���
				bRet = TRUE;
				break;
			}
		}
	}
	return bRet;
}

// ---------------------------------------------------------------------------
//
// �X�L���E�g�U�{�[���v���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X
//  VECTOR3    vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponDivBallProc::Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner, DWORD dwPlayerNo)
{
	MATRIX4X4 mLay, mOwnerRot, mOffset;
	BOOL bRet = FALSE;

	DWORD  dwNum;
	dwNum = 5;			//�o�Ă���e�̐�


	mLay = GetPositionMatrix(mGun);               // �e�̈ʒu(��]����菜��)
	mOwnerRot = GetRotateMatrix(mOwnerWorld);     // ���˂���L�����̉�]�}�g���b�N�X�̂�(�ʒu����菜��)�ɂ���
	mLay = mOwnerRot * mLay;                      // �e�̈ʒu����A�L�����̕����Ŕ��˂���}�g���b�N�X�����
	mOffset = XMMatrixTranslation(vOffset.x, vOffset.y + 0.5, vOffset.z);	// �ʒu�̔�����
	mLay = mOffset * mLay;
	for (DWORD n = 0; n < dwNum; n++)
	{
		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				((CWeaponDivBallObj*)(m_pObjArray[i]))->SetPlayerNo(dwPlayerNo);
				((CWeaponDivBallObj*)(m_pObjArray[i]))->Start(mLay, dwOwner, n, dwNum);	       // �X�L���E�g�U�{�[���I�u�W�F�N�g�̔���
				bRet = TRUE;
				break;
			}
		}
	}
	return bRet;
}


//============================================================================
//
// �X�L���E�g�U�{�[���I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponDivBallObj::CWeaponDivBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // �U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-0.15f, -0.15f, -0.15f);
	VECTOR3 vMax(0.15f, 0.15f, 0.15f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                       


	TargetProc = m_pGMain->m_pEnmProc->GetProcArrayPtr()[0];

}
// ---------------------------------------------------------------------------
//
// �X�L���E�g�U�{�[���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponDivBallObj::~CWeaponDivBallObj()
{
	;
}

// ---------------------------------------------------------------------------
//
// �X�L���E�g�U�{�[���I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     �g�U�{�[���̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner        �X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponDivBallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner,DWORD dwNo,DWORD  dwNum)
{
	const float fSpeed = 0.02f;		// �g�U�{�[���̑���
	const int nLifeTime = 300;		// �g�U�{�[���̎�������
	if (m_bActive) return FALSE;

	float angle = 0;
	MATRIX4X4 mYaw;  // �x����]�}�g���b�N�X
	float test = 10;
	float Breadth=120.0f; //�L��
	DWORD SaveNum = 0;	//�I��ID�̕ۑ�	
	int	  NumRim = 0;	//�c��̓I�̐�	
	m_bFront = FALSE;
	fActivTime = 300;

	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	m_fDivTime = 0;

	m_fDist = 10000000;
	
	TargetProcArr.clear();
	TargetProcArr.shrink_to_fit();

	TargetStatas TS;
	for (DWORD i = 0; i < m_pGMain->m_pEnmProc->GetProcArrayPtr().size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		if (i != (ENM_BALL_ID - 1) && i != (ENM_BALLBOOM_ID - 1)) {
			TS.Id = m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->GetProcID()-1;
			TargetProcArr.push_back(TS);
		}
	}

	//�^�[�Q�b�g����I�u�W�F�N�g������ 
	DWORD RanSarch = Random(0, TargetProcArr.size() - 1);

	for (DWORD i = 0; i < TargetProcArr.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		if (LookTarget(m_pGMain->m_pEnmProc->GetProcArrayPtr()[TargetProcArr[RanSarch].Id], m_dwPlayerNo))break;

			RanSarch++;
			if(RanSarch> TargetProcArr.size() - 1)RanSarch = 0;

	}


	m_vPosUp = VECTOR3(0, 0, fSpeed);
	m_nCnt1 = nLifeTime;
	m_dwOwner = dwOwner;
	
	dwNo = dwNo;
	//��`�ɒe���o��������
	angle = Breadth / (dwNum-1);
	if (dwNum == 0) {
		angle = 0;
	}
	else {
		angle = angle * dwNo;
		angle = angle - (Breadth/2);

	}
	mYaw = XMMatrixRotationY(XMConvertToRadians(angle));
	m_mWorld = mYaw * m_mWorld;
	
	
	return TRUE;
}

// ---------------------------------------------------------------------------
//
// �g�U�{�[���I�u�W�F�N�g�̃��[�J�����}�g���b�N�X�𓾂�֐�
//
//  m_mWorld�̈ʒu����m_fLocalRotY�̊p�x��������
//  ���[�J�����}�g���b�N�X��Ԃ�
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponDivBallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
//
// �X�L���E�g�U�{�[���I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponDivBallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;
		TargetProc->GetObjArrayPtr()[RanNum]->SetTarget(FALSE);		//�I�̃^�[�Q�b�g�g���K�[���O��		

		MATRIX4X4 mTran;
		m_vPosUp.z = 0.3;

		if (m_bFront != TRUE) {		
			TargetProc->ObjTarget(this, 10.0f, RanNum);		//�^�[�Q�b�g�Ɍ����Ēe��������
			if (TargetProc->GetObjArrayPtr()[RanNum]->GetActive() != TRUE) m_bFront = TRUE;		//�I����ꂽ��Ǐ]���~�߂�
		}
			
		
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// �����g�U�{�[���̈ʒu����ƈړ�
		VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // �����̑O�̈ʒu
		
		m_pGMain->m_pEnmProc->Hitcheck(this, m_pBBox, m_pGMain->m_pEnmProc->m_pEnmBallProc->GetProcID());
		m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->HitcheckMulti(this, m_pBBox,m_dwPlayerNo);
		if (m_pGMain->m_pWeaponProc->m_pWeaponWallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {	
			m_pHitObj->SetStatus(NORMAL);
		}
		if (m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {	
			m_pHitObj->SetStatus(NORMAL);
		}



	// �G��o�b�Ƃ̂����蔻��
		if ((m_dwOwner != ENM && m_pGMain->m_pEnmProc->m_pEnmTargetProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo) )||
			(m_dwOwner != PC && m_pGMain->m_pPcProc->HitcheckMulti(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), m_dwPlayerNo)))
		{
			m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���	
			//m_pGMain->m_pSeDead->Play();// �������ʉ�
			//m_bActive = FALSE;

		}
		if (fActivTime < 0) {
			m_bActive = FALSE;

		}


		switch (m_dwStatus)
		{

		case DAMAGE:
			UpdateDamage();
			m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���
			m_bActive = FALSE;

			break;
		}
		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_bActive = FALSE;
		}
		m_pBBox->m_mWorld = m_mWorld;

		// �����_�����O
		Render();
		m_fDivTime++;
		fActivTime--;
	}
}
//----------------------------------------------------------------------------
//�g�U�{�[��������������
//----------------------------------------------------------------------------
void CWeaponDivBallObj::UpdateDamage()
{
	m_dwStatus = NORMAL;

}




// ---------------------------------------------------------------------------
// �X�L���E�g�U�{�[���I�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponDivBallObj::Render()
{

	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

}
//-----------------------------------------------------------------------------
//
//�^�[�Q�b�g�������鏈��
//
//
//-----------------------------------------------------------------------------
BOOL CWeaponDivBallObj::LookTarget(CBaseProc* pOtherProc, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;

	int	  NumRim = 0;	//�c��̓I�̐�	
	DWORD SaveNum = 0;	//�I��ID�̕ۑ�	/

	TargetStatas TS;
	//---------------------------------------------------------- 
	TargetObjArr.clear();
	TargetObjArr.shrink_to_fit();


//�c���Ă���I�̐�
	for (DWORD i = 0; i < pOtherProc->GetObjArrayPtr().size(); i++) {
		if (pOtherProc->GetObjArrayPtr()[i]->GetActive() == TRUE&& dwPlayerNo== pOtherProc->GetObjArrayPtr()[i]->GetPlayerNo())
		{
			NumRim++;
			TS.Id = pOtherProc->GetObjArrayPtr()[i]->GetObjNo();
			TargetObjArr.push_back(TS);

		}
	}

	if (NumRim <= 0) {		//�I���Ȃ��Ƃ�
		bRet = FALSE;

	}
	else {
		DWORD RanSetNum = Random(0, TargetObjArr.size() - 1);
		for (DWORD i = 0; i < TargetObjArr.size(); i++) {

			if (pOtherProc->GetObjArrayPtr()[TargetObjArr[RanSetNum].Id]->GetActive() == TRUE) {

					TargetProc = pOtherProc;
					SaveNum = TargetObjArr[RanSetNum].Id;
					bRet = TRUE;

					break;

			}
			RanSetNum++;
			if (RanSetNum > TargetObjArr.size() - 1)RanSetNum = 0;
		}

		for (DWORD i = 0; i < TargetObjArr.size(); i++) {

				if (pOtherProc->GetObjArrayPtr()[TargetObjArr[RanSetNum].Id]->GetActive() == TRUE) {

					if (pOtherProc->GetObjArrayPtr()[TargetObjArr[RanSetNum].Id]->GetTarget() != TRUE) {		//�I�Ɍ������Ă��Ȃ��e���Ȃ��Ƃ��i�I�Ɍ������e�𕪂���j
						pOtherProc->GetObjArrayPtr()[TargetObjArr[RanSetNum].Id]->SetTarget(TRUE);
						TargetProc = pOtherProc;
						SaveNum = TargetObjArr[RanSetNum].Id;
						bRet = TRUE;

						break;

					}
				}
				RanSetNum++;
				if(RanSetNum > TargetObjArr.size() - 1)RanSetNum = 0;
			bRet = FALSE;
		}

		RanNum = SaveNum;		//�e��ID���擾�i�]�����e�͓I�����j

	}


	return bRet;

}


// ================================================================================================================================
//============================================================================
// �X�L���E�V�[���h�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponShieldProc::CWeaponShieldProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �V�[���h���b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy_Shield.mesh"));

	for (int i = 0; i < SHIELD_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponShieldObj(m_pGMain));	// m_pObjArray�ɃX�L���E�V�[���h�I�u�W�F�N�g�𐶐�����
		((CWeaponShieldObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
		m_pObjArray[i]->SetObjID(m_dwProcID);	

	}
}
//============================================================================
// �X�L���E�V�[���h�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponShieldProc::~CWeaponShieldProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
// �X�L���E�V�[���h�v���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X
//  VECTOR3    vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j

// ---------------------------------------------------------------------------
BOOL CWeaponShieldProc::Start(MATRIX4X4 mWorld, DWORD dwOwner)
{
	MATRIX4X4 mLay;

	mLay = mWorld;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner);	       // �X�L���E�V�[���h�I�u�W�F�N�g�̔���
			return TRUE;
		}
	}
	return FALSE;
}

// ---------------------------------------------------------------------------
// �X�L���E�V�[���h�v���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X
//  VECTOR3    vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j

// ---------------------------------------------------------------------------
BOOL CWeaponShieldProc::Start(MATRIX4X4 mWorld, DWORD dwOwner, DWORD dwPlayerNo)
{
	MATRIX4X4 mLay;

	mLay = mWorld;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner, dwPlayerNo);	       // �X�L���E�V�[���h�I�u�W�F�N�g�̔���
			return TRUE;
		}
	}
	return FALSE;
}


//============================================================================
// �X�L���E�V�[���h�I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponShieldObj::CWeaponShieldObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // �U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-0.35f, -0.35f, -0.35f);
	VECTOR3 vMax(0.35f, 0.35f, 0.35f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                           


}
// ---------------------------------------------------------------------------
// �X�L���E�V�[���h�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponShieldObj::~CWeaponShieldObj()
{
	;
}

// ---------------------------------------------------------------------------
// �X�L���E�V�[���h�I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     �V�[���h�̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner        �X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
//
// ---------------------------------------------------------------------------
BOOL CWeaponShieldObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;

	dTargetNo=m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->GetTargetNo();
	fShieldDist = m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->GetShieldDist();
	return TRUE;
}

// ---------------------------------------------------------------------------
// �X�L���E�V�[���h�I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     �V�[���h�̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner        �X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
//
// ---------------------------------------------------------------------------
BOOL CWeaponShieldObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner, DWORD dwPlayerNo)
{
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	m_dwPlayerNo = dwPlayerNo;
	dTargetNo = m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->GetTargetNo();
	fShieldDist = m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->GetShieldDist();
	return TRUE;
}


// ---------------------------------------------------------------------------
// �V�[���h�I�u�W�F�N�g�̃��[�J�����}�g���b�N�X�𓾂�֐�
//
//  m_mWorld�̈ʒu����m_fLocalRotY�̊p�x��������
//  ���[�J�����}�g���b�N�X��Ԃ�
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponShieldObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
// �X�L���E�V�[���h�I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponShieldObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;
		// �����V�[���h�̈ʒu����ƈړ�
		VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // �����̑O�̈ʒu

		//�V�[���h����]������
		MATRIX4X4 mBaseWorld = m_pGMain->m_pEnmProc->m_pEnmShieldProc->GetObjArrayPtr()[dTargetNo]->GetWorld();
		const float fMoveSpeed = 0.05f;

		m_mWorld = RotTarget(m_mWorld, mBaseWorld, fMoveSpeed, fShieldDist);	
		if (m_pGMain->m_pEnmProc->m_pEnmShieldProc->GetObjArrayPtr()[dTargetNo]->GetActive() == FALSE) {
			m_bActive = FALSE;
		}


		switch (m_dwStatus)
		{

		case DAMAGE:
			UpdateDamage();

			break;
		}
		m_pBBox->m_mWorld = m_mWorld;

		// �����_�����O
		Render();

	}
}
//----------------------------------------------------------------------------
//�V�[���h������������
//
//
//----------------------------------------------------------------------------
void CWeaponShieldObj::UpdateDamage()
{

	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���
	//m_pGMain->m_pSeDead->Play();// �������ʉ�
	m_bActive = FALSE;



	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
// �X�L���E�V�[���h�I�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponShieldObj::Render()
{

	// �V�[���h�̃����_�����O
	//m_pMesh->Render(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

	//m_pBBox->Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);

}


// ================================================================================================================================
//============================================================================
// �X�L���E�r�b�O�{�[���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponBigBallProc::CWeaponBigBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �r�b�O�{�[�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark_Pro_Big.mesh"));
	m_dwProcID = WEAPON_BIGBALL;		

	for (int i = 0; i < BIGBALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponBigBallObj(m_pGMain));	// m_pObjArray�ɃX�L���E�r�b�O�{�[���I�u�W�F�N�g�𐶐�����
		((CWeaponBigBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
		m_pObjArray[i]->SetObjID(m_dwProcID);	

	}
}
//============================================================================
// �X�L���E�r�b�O�{�[���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBigBallProc::~CWeaponBigBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
// �X�L���E�r�b�O�{�[���v���V�[�W���̔���
//
//  CBaseObj* mMyObj         �F���˂������I�u�W�F�N�g
//	CBaseObj* mHitObj		:���˂���I�u�W�F�N�g
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponBigBallProc::Start(CBaseObj* mMyObj,  CBaseObj* mHitObj, DWORD dwOwner)
{
	{

		MATRIX4X4 mLay;
		mLay = ObjReflectionStart(mMyObj, mHitObj);
		VECTOR3 vPos = GetPositionVector(mHitObj->GetWorld());
		MATRIX4X4	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
		mLay = mLay * mWorld;
		for (int i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				m_pObjArray[i]->Start(mLay, dwOwner);	       // �X�L���E�r�b�O�{�[���I�u�W�F�N�g�̔���
				return TRUE;
			}
		}
		return FALSE;
	}
}

// ---------------------------------------------------------------------------
// �X�L���E�r�b�O�{�[���v���V�[�W���̔���
//
//  CBaseObj* mMyObj         �F���˂������I�u�W�F�N�g
//	CBaseObj* mHitObj		:���˂���I�u�W�F�N�g
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponBigBallProc::Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner, DWORD dwPlayerNo)
{
	{

		MATRIX4X4 mLay;
		mLay = ObjReflectionStart(mMyObj, mHitObj);
		VECTOR3 vPos = GetPositionVector(mHitObj->GetWorld());
		MATRIX4X4	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
		mLay = mLay * mWorld;
		for (int i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				m_pObjArray[i]->SetPlayerNo(dwPlayerNo);
				m_pObjArray[i]->Start(mLay, dwOwner);	       // �X�L���E�r�b�O�{�[���I�u�W�F�N�g�̔���
				return TRUE;
			}
		}
		return FALSE;
	}
}


//============================================================================
// �X�L���E�r�b�O�{�[���I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBigBallObj::CWeaponBigBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // �U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-1.0f, -1.0f, -1.0f);
	VECTOR3 vMax(1.0f, 1.0f, 1.0f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                  
	m_vDiffuse = VECTOR4(1, 0, 0, 1);		


}
// ---------------------------------------------------------------------------
// �X�L���E�r�b�O�{�[���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBigBallObj::~CWeaponBigBallObj()
{
	;
}

// ---------------------------------------------------------------------------
// �X�L���E�r�b�O�{�[���I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     �r�b�O�{�[���̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner        �X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponBigBallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	const float fSpeed = 0.1f;		// �r�b�O�{�[���̑���
	const int nLifeTime = 300;		// �r�b�O�{�[���̎�������
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	m_dDamageCount = 0;
	m_vPosUp = VECTOR3(0, 0, fSpeed);
	m_vGravity = VECTOR3(0, fSpeed, 0);

	m_bDamage = true;

	m_nCnt1 = nLifeTime;
	m_dwOwner = dwOwner;
	return TRUE;
}

// ---------------------------------------------------------------------------
// �r�b�O�{�[���I�u�W�F�N�g�̃��[�J�����}�g���b�N�X�𓾂�֐�
//
//  m_mWorld�̈ʒu����m_fLocalRotY�̊p�x��������
//  ���[�J�����}�g���b�N�X��Ԃ�
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponBigBallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
// �X�L���E�r�b�O�{�[���I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponBigBallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		MATRIX4X4 mTran;
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// �����r�b�O�{�[���̈ʒu����ƈړ�
		VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // �����̑O�̈ʒu

	// �G��o�b�Ƃ̂����蔻��
			// �}�b�v�Ƃ̂����蔻��
			VECTOR3 vHit, vNormal;

			if (m_pGMain->m_pMapProc->Hitcheck(GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), &vHit, &vNormal))
			{
				m_bActive = FALSE;

			}

			m_pGMain->m_pEnmProc->HitcheckMulti(this, m_pBBox, m_pGMain->m_pEnmProc->m_pEnmBallProc->GetProcID(), m_dwPlayerNo);	
			m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo);	
			if (m_pGMain->m_pWeaponProc->m_pWeaponWallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {	
				m_pHitObj->SetStatus(NORMAL);
			}
			if (m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {		
				m_pHitObj->SetStatus(NORMAL);
			}



		switch (m_dwStatus)
		{

		case DAMAGE:
			m_dDamageCount++;
			UpdateDamage();

			break;
		}
		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_bActive = FALSE;
		}
		m_pBBox->m_mWorld = m_mWorld;

		// �����_�����O
		Render();

	}
	m_pMesh->m_vDiffuse = m_vDiffuse;	

}
//----------------------------------------------------------------------------
//�r�b�O�{�[��������������
//
//
//----------------------------------------------------------------------------
void CWeaponBigBallObj::UpdateDamage()
{


	VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu
	VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // �����̑O�̈ʒu

	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���	
	if(m_dDamageCount>1)
	m_bActive = FALSE;


	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
// �X�L���E�r�b�O�{�[���I�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponBigBallObj::Render()
{

	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

}

// ================================================================================================================================
//============================================================================
// �X�L���E�ђʃ{�[���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponPenetBallProc::CWeaponPenetBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �ђʃ{�[�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Weapon_PenetBall.mesh"));
	m_dwProcID = WEAPON_PENETBALL;	

	for (int i = 0; i < BALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponPenetBallObj(m_pGMain));	// m_pObjArray�ɃX�L���E�ђʃ{�[���I�u�W�F�N�g�𐶐�����
		((CWeaponPenetBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
		m_pObjArray[i]->SetObjID(m_dwProcID);	

	}
}
//============================================================================
// �X�L���E�ђʃ{�[���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponPenetBallProc::~CWeaponPenetBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
// �X�L���E�ђʃ{�[���v���V�[�W���̔���
//
//  CBaseObj* mMyObj         �F���˂������I�u�W�F�N�g
//	CBaseObj* mHitObj		:���˂���I�u�W�F�N�g
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponPenetBallProc::Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner)
{
	{

		MATRIX4X4 mLay;
		mLay = ObjReflectionStart(mMyObj, mHitObj);
		VECTOR3 vPos = GetPositionVector(mHitObj->GetWorld());
		MATRIX4X4	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
		mLay = mLay * mWorld;
		for (int i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				m_pObjArray[i]->Start(mLay, dwOwner);	       // �X�L���E�ђʃ{�[���I�u�W�F�N�g�̔���
				return TRUE;
			}
		}
		return FALSE;
	}
}

// ---------------------------------------------------------------------------
// �X�L���E�ђʃ{�[���v���V�[�W���̔���
//
//  CBaseObj* mMyObj         �F���˂������I�u�W�F�N�g
//	CBaseObj* mHitObj		:���˂���I�u�W�F�N�g
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponPenetBallProc::Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner,DWORD dwPlayerNo)
{
	{

		MATRIX4X4 mLay;
		mLay = ObjReflectionStart(mMyObj, mHitObj);
		VECTOR3 vPos = GetPositionVector(mHitObj->GetWorld());
		MATRIX4X4	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
		mLay = mLay * mWorld;
		for (int i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				m_pObjArray[i]->SetPlayerNo(dwPlayerNo);
				m_pObjArray[i]->Start(mLay, dwOwner);	       // �X�L���E�ђʃ{�[���I�u�W�F�N�g�̔���
				return TRUE;
			}
		}
		return FALSE;
	}
}

//============================================================================
// �X�L���E�ђʃ{�[���I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponPenetBallObj::CWeaponPenetBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // �U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-0.15f, -0.15f, -0.15f);
	VECTOR3 vMax(0.15f, 0.15f, 0.15f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;            
	m_vDiffuse = VECTOR4(1, 1, 1, 1);	


}
// ---------------------------------------------------------------------------
// �X�L���E�ђʃ{�[���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponPenetBallObj::~CWeaponPenetBallObj()
{
	;
}

// ---------------------------------------------------------------------------
// �X�L���E�ђʃ{�[���I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     �ђʃ{�[���̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner        �X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponPenetBallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	const float fSpeed = 0.3f;		// �ђʃ{�[���̑���
	const int nLifeTime = 300;		// �ђʃ{�[���̎�������
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	MATRIX4X4 mPos = XMMatrixTranslation(0,0,2);
	m_mWorld = mPos * m_mWorld;
	m_mWorldOld = m_mWorld;

	m_vPosUp = VECTOR3(0, 0, fSpeed);
	m_vGravity = VECTOR3(0, fSpeed, 0);

	//m_vPosUp  = VECTOR3(0, fSpeed, fSpeed);
	m_nCnt1 = nLifeTime;
	m_dwOwner = dwOwner;

	return TRUE;
}

// ---------------------------------------------------------------------------
// �ђʃ{�[���I�u�W�F�N�g�̃��[�J�����}�g���b�N�X�𓾂�֐�
//
//  m_mWorld�̈ʒu����m_fLocalRotY�̊p�x��������
//  ���[�J�����}�g���b�N�X��Ԃ�
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponPenetBallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
// �X�L���E�ђʃ{�[���I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponPenetBallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		MATRIX4X4 mTran;
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// �����ђʃ{�[���̈ʒu����ƈړ�
		VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // �����̑O�̈ʒu

	// �G��o�b�Ƃ̂����蔻��
			// �}�b�v�Ƃ̂����蔻��
		VECTOR3 vHit, vNormal;

		if (m_pGMain->m_pMapProc->Hitcheck(GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), &vHit, &vNormal))
		{
			m_bActive = FALSE;

		}
		m_pGMain->m_pEnmProc->HitcheckMulti(this, m_pBBox, m_pGMain->m_pEnmProc->m_pEnmBallProc->GetProcID(),m_dwPlayerNo);		
		m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo);	

		switch (m_dwStatus)
		{

		case DAMAGE:
			m_pGMain->m_nScore++;
			UpdateDamage();

			break;
		}
		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_bActive = FALSE;

		}
		m_pBBox->m_mWorld = m_mWorld;

		// �����_�����O
		Render();

	}


	m_pMesh->m_vDiffuse = m_vDiffuse;

}
//----------------------------------------------------------------------------
//�ђʃ{�[��������������
//
//----------------------------------------------------------------------------
void CWeaponPenetBallObj::UpdateDamage()
{


	VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu
	VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // �����̑O�̈ʒu

	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���	

	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
// �X�L���E�ђʃ{�[���I�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponPenetBallObj::Render()
{

	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

}

// ================================================================================================================================
//============================================================================
// �X�L���E��]�{�[���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponRollBallProc::CWeaponRollBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ��]�{�[�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark_Pro.mesh"));
	m_dwProcID = WEAPON_ROLLBALL;	

	for (int i = 0; i < BALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponRollBallObj(m_pGMain));	// m_pObjArray�ɃX�L���E��]�{�[���I�u�W�F�N�g�𐶐�����
		((CWeaponRollBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
		m_pObjArray[i]->SetObjID(m_dwProcID);

	}
}
//============================================================================
// �X�L���E��]�{�[���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponRollBallProc::~CWeaponRollBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
// �X�L���E��]�{�[���v���V�[�W���̔���
//
//  CBaseObj* mMyObj         �F���˂������I�u�W�F�N�g
//	CBaseObj* mHitObj		:���˂���I�u�W�F�N�g
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponRollBallProc::Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner)
{
	{

		MATRIX4X4 mLay;
		mLay= ObjReflectionStart(mMyObj, mHitObj);
		VECTOR3 vPos = GetPositionVector(mHitObj->GetWorld());
		MATRIX4X4	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
		mLay = mLay * mWorld;
		for (int i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				m_pObjArray[i]->Start(mLay, dwOwner);	       // �X�L���E��]�{�[���I�u�W�F�N�g�̔���
				return TRUE;
			}
		}
		return FALSE;
	}
}

// ---------------------------------------------------------------------------
// �X�L���E��]�{�[���v���V�[�W���̔���
//
//  CBaseObj* mMyObj         �F���˂������I�u�W�F�N�g
//	CBaseObj* mHitObj		:���˂���I�u�W�F�N�g
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponRollBallProc::Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner, DWORD dwPlayerNo)
{
	{

		MATRIX4X4 mLay;
		mLay = ObjReflectionStart(mMyObj, mHitObj);
		VECTOR3 vPos = GetPositionVector(mHitObj->GetWorld());
		MATRIX4X4	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
		mLay = mLay * mWorld;
		for (int i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				m_pObjArray[i]->SetPlayerNo(dwPlayerNo);
				m_pObjArray[i]->Start(mLay, dwOwner);	       // �X�L���E��]�{�[���I�u�W�F�N�g�̔���
				return TRUE;
			}
		}
		return FALSE;
	}
}


//============================================================================
// �X�L���E��]�{�[���I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponRollBallObj::CWeaponRollBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // �U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-0.45f, -0.45f, -0.45f);
	VECTOR3 vMax(0.45f, 0.45f, 0.45f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                 
	m_vDiffuse = VECTOR4(0, 0, 1, 1);	


}
// ---------------------------------------------------------------------------
// �X�L���E��]�{�[���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponRollBallObj::~CWeaponRollBallObj()
{
	;
}

// ---------------------------------------------------------------------------
// �X�L���E��]�{�[���I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     ��]�{�[���̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner        �X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponRollBallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	const float fSpeed = 0.05f;		// ��]�{�[���̑���
	const int nLifeTime = 300;		// ��]�{�[���̎�������
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	m_vPosUp = VECTOR3(0, 0, fSpeed);
	m_vGravity = VECTOR3(0, fSpeed, 0);

	//m_vPosUp  = VECTOR3(0, fSpeed, fSpeed);
	m_nCnt1 = nLifeTime;
	m_dwOwner = dwOwner;
	return TRUE;
}

// ---------------------------------------------------------------------------
// ��]�{�[���I�u�W�F�N�g�̃��[�J�����}�g���b�N�X�𓾂�֐�
//
//  m_mWorld�̈ʒu����m_fLocalRotY�̊p�x��������
//  ���[�J�����}�g���b�N�X��Ԃ�
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponRollBallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
// �X�L���E��]�{�[���I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponRollBallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		MATRIX4X4 mTran;
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// ������]�{�[���̈ʒu����ƈړ�
		VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // �����̑O�̈ʒu

	// �G��o�b�Ƃ̂����蔻��
			// �}�b�v�Ƃ̂����蔻��
		VECTOR3 vHit, vNormal;

		if (m_pGMain->m_pMapProc->Hitcheck(GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), &vHit, &vNormal))
		{
			m_bActive = FALSE;

		}
		m_pGMain->m_pEnmProc->m_pEnmBallProc->ObjTerritoryMulti(this, Random(1.0f,5.0f),m_dwPlayerNo);	


		switch (m_dwStatus)
		{

		case DAMAGE:
			UpdateDamage();

			break;
		}
		m_pBBox->m_mWorld = m_mWorld;

		// �����_�����O
		Render();

	}
	m_pMesh->m_vDiffuse = m_vDiffuse;		

}
//----------------------------------------------------------------------------
//��]�{�[��������������
//
//
//----------------------------------------------------------------------------
void CWeaponRollBallObj::UpdateDamage()
{
	VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu
	VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // �����̑O�̈ʒu

	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���


	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
// �X�L���E��]�{�[���I�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponRollBallObj::Render()
{

	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
	}

}


// ================================================================================================================================
//============================================================================
// �X�L���E�ǃv���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponWallProc::CWeaponWallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{

	// �ǃ��b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Wall.mesh"));
	//m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // �R���W�����}�b�v�̐���
	m_dwProcID = WEAPON_WALL;		

	for (int i = 0; i < WALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponWallObj(m_pGMain));	// m_pObjArray�ɃX�L���E�ǃI�u�W�F�N�g�𐶐�����
		m_pObjArray[i]->SetObjNo(i);
		((CWeaponWallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
		((CWeaponWallObj*)m_pObjArray[i])->SetColMesh(this);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
		m_pObjArray[i]->SetObjID(m_dwProcID);	

	}
}
//============================================================================
// �X�L���E�ǃv���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponWallProc::~CWeaponWallProc()
{
	SAFE_DELETE(m_pMesh);
	SAFE_DELETE(m_pColMesh);

}
// ---------------------------------------------------------------------------
// �X�L���E�ǃv���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X
//  VECTOR3    vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j

// ---------------------------------------------------------------------------
BOOL CWeaponWallProc::Start(MATRIX4X4 mWorld, DWORD dwOwner, DWORD dNo)
{

	MATRIX4X4 mLay = mWorld;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner,dNo);	       // �X�L���E�ǃI�u�W�F�N�g�̔���

			return TRUE;
		}
	}
	return FALSE;
}

// ---------------------------------------------------------------------------
// �X�L���E�ǃv���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X
//  VECTOR3    vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j

// ---------------------------------------------------------------------------
BOOL CWeaponWallProc::Start(MATRIX4X4 mWorld, DWORD dwOwner, DWORD dNo,DWORD dwPlayerNo)
{

	MATRIX4X4 mLay = mWorld;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->SetPlayerNo(dwPlayerNo);
			m_pObjArray[i]->Start(mLay, dwOwner, dNo);	       // �X�L���E�ǃI�u�W�F�N�g�̔���

			return TRUE;
		}
	}
	return FALSE;
}


//============================================================================
// �X�L���E�ǃI�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponWallObj::CWeaponWallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // �U����


	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-2.35f, -7.35f, -0.15f);
	VECTOR3 vMax(2.35f, 3.35f, 0.15f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                        


}


// ---------------------------------------------------------------------------
// �X�L���E�ǃI�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponWallObj::~CWeaponWallObj()
{
	SAFE_DELETE(m_pColMesh);
	;
}


// ---------------------------------------------------------------------------  
// �GBall�I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CEnmBallProc* pProc
//
// --------------------------------------------------------------------------
void CWeaponWallObj::SetColMesh(CWeaponWallProc* pProc)
{
	//m_pColMesh = pProc->GetColMesh();					// �X�L�����b�V���̃|�C���^
	 m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // �R���W�����}�b�v�̐���
	m_pColMesh->AddFbxLoad(_T("Data/Item/Wall.mesh"), VECTOR3(0.0f, 0.0f, 0.0f));

}

// ---------------------------------------------------------------------------
// �X�L���E�ǃI�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     �ǂ̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner        �X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponWallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner, DWORD dNo)
{
	//const float fSpeed = 0.05f;		// �ǂ̑���
	//const int nLifeTime = 300;		// �ǂ̎�������

	dDamageNum = 3;
	m_nCnt1 = 120;
	bInvTrigger = FALSE;	
	if (m_bActive) return FALSE;
	MATRIX4X4 mRot;
	m_bActive = TRUE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	bStartTrigget = FALSE;

	VECTOR3 vMin, vMax;
	vMin = VECTOR3(-5.0f, -10.0f, -5.0f);
	vMax = VECTOR3(5.0f, -10.0f, 5.0f);

	dTargetNo = m_pGMain->m_pWeaponProc->m_pWeaponWallProc->GetTargetNo();
	fWallDist = m_pGMain->m_pWeaponProc->m_pWeaponWallProc->GetWallDist();

	//�ǂ𐶐�����

	m_mWorld = XMMatrixTranslation((float)Random(vMin.x, vMax.x),
		vMax.y, (float)Random(vMin.z,vMax.z));
	mRot = GetRotateMatrix(mStartWorld);
	m_mWorld = mRot * m_mWorld;
	m_pBBox->m_mWorld = m_mWorld;                    

	for (DWORD i = 0; i < m_pGMain->m_pWeaponProc->m_pWeaponWallProc->GetObjArrayPtr().size(); i++) {

		if (i != m_dwObjNo) {
			if (m_pGMain->m_pWeaponProc->m_pWeaponWallProc->GetObjArrayPtr()[i]->GetActive() == TRUE) {		//�\������Ă���ǂ�T��

				if (m_pBBox->OBBCollisionDetection(m_pGMain->m_pWeaponProc->m_pWeaponWallProc->GetObjArrayPtr()[i]->GetBBox(), &vHit, &vNrm)) {

					m_mWorld = XMMatrixTranslation((float)Random(vMin.x, vMax.x),
						vMax.y, (float)Random(vMin.z, vMax.z));
					mRot = GetRotateMatrix(mStartWorld);
					m_mWorld = mRot * m_mWorld;
					m_pBBox->m_mWorld = m_mWorld;        
					i = 0;

				}

			}

		}

	}
	vDiffuse = VECTOR4(1, 1, 1, 1);

	dUseNo = dNo;

	return TRUE;
}

// ---------------------------------------------------------------------------
// �ǃI�u�W�F�N�g�̃��[�J�����}�g���b�N�X�𓾂�֐�
//
//  m_mWorld�̈ʒu����m_fLocalRotY�̊p�x��������
//  ���[�J�����}�g���b�N�X��Ԃ�
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponWallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
// �X�L���E�ǃI�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponWallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		//vy += 0.01;
		MATRIX4X4 mPos;

		// �����ǂ̈ʒu����ƈړ�
		VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // �����̑O�̈ʒu

		//�ǂ��ړ�
		const float fMoveSpeed = 0.05f;
		if(vHear.y<0){
		mPos = XMMatrixTranslation(0, fMoveSpeed, 0);
		m_mWorld = mPos * m_mWorld;
		StartLE();
		}

		m_pColMesh->SetWorldMatrix(m_mWorld);
		m_pColMesh->m_mWorldOld = m_pColMesh->m_mWorld;

		ObjDisappear();
		InvincibleTime();
		switch (m_dwStatus)
		{

		case DAMAGE:
			UpdateDamage();

			break;
		}
		m_pBBox->m_mWorld = m_mWorld;

		m_pMesh->m_vDiffuse = vDiffuse;		

		// �����_�����O
		Render();


	}
}
//----------------------------------------------------------------------------
//����������
//
//----------------------------------------------------------------------------
void CWeaponWallObj::UpdateDamage()
{

	if (bInvTrigger != TRUE) {
		bInvTrigger = TRUE;
		dDamageNum--;
		//��ꂽ���̏���
		if (dDamageNum <= 0) {
			DWORD	dUseNum = m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->GetWeaponUseNum();	//�g�p�I�u�W�F�N�g�̑��݂ł���X�L���̐��擾

			m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->SetWeaponUseNum(dUseNum + 1);	//�g�p�I�u�W�F�N�g�̃X�L���̐��𑝂₷	
			m_bActive = FALSE;

		}
		if (m_pGMain->m_pEffectProc->m_pBillProc->GetProcID() == m_pHitObj->GetObjID()) {	
			DWORD	dUseNum = m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->GetWeaponUseNum();	//�g�p�I�u�W�F�N�g�̑��݂ł���X�L���̐��擾	

			m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->SetWeaponUseNum(dUseNum + 1);	//�g�p�I�u�W�F�N�g�̃X�L���̐��𑝂₷	
			m_bActive = FALSE;

		}

		bDamageTrigger = FALSE;
		m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���
		//m_pGMain->m_pSeDead->Play();// �������ʉ�


	}
	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
//
//	�[���̔���
//
// ---------------------------------------------------------------------------
void CWeaponWallObj::StartLE()
{
	VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu

	if (vHear.y > -2.7&&bStartTrigget == FALSE)			//�[����������
	{
		bStartTrigget = TRUE;
		int Dire = Random(0, 1);		//�ŏ��ɏo�����鎞�̈ʒu�@���͂O�@�E���P
		for (int i = 0; i < 4; i++) {
			MATRIX4X4	mEffectWorld = m_mWorld;
			float fEffectAddPosX = (Random(0, 9)*0.1);
			float fEffectAddPosY = 1 + (0.5*i);
			if (Dire == 0)  mEffectWorld = XMMatrixTranslation(-2.0 - fEffectAddPosX, 0, 0)*mEffectWorld;
			if (Dire == 1)	mEffectWorld = XMMatrixTranslation(3.0 - fEffectAddPosX, 0, 0)*mEffectWorld;
			VECTOR3	vEffectPos = GetPositionVector(mEffectWorld);
			vEffectPos.y = fEffectAddPosY;
			float fEffectSize = Random(6, 9)*0.1;
			m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), vEffectPos, VECTOR2(fEffectSize, fEffectSize), VECTOR2(320, 0), VECTOR2(64, 64), 120, m_dwPlayerNo, LENO_SHAKERANDOMTYPE,1.0);	

			if (Dire == 0) {
				Dire = 1;
			}
			else if (Dire == 1) {
				Dire = 0;
			}


		}


	}


}

// ---------------------------------------------------------------------------
//
//	���G���Ԃ̏���
//
//
//
// ---------------------------------------------------------------------------
void CWeaponWallObj::InvincibleTime()
{
	//���G���Ԃ̏���
	if (bInvTrigger == TRUE) {
		if (m_nCnt1 < 0) {
			bInvTrigger = FALSE;
			m_nCnt1 = 120;

		}
		else {
			m_nCnt1--;
			if (m_nCnt1 % 2 == 0) {
				vDiffuse = VECTOR4(0, 0, 0, 1);
			}
			else {
				vDiffuse = VECTOR4(1, 1, 1, 1);

			}
		}
	}

}

// ---------------------------------------------------------------------------
//
//	���������
//
//
// ---------------------------------------------------------------------------
void CWeaponWallObj::ObjDisappear()
{
	if (m_pGMain->m_pWeaponProc->m_pWeaponPenetBallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {	
		DWORD	dUseNum = m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->GetWeaponUseNum();	//�g�p�I�u�W�F�N�g�̑��݂ł���ǂ̐��擾	
		m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->SetWeaponUseNum(dUseNum + 1);	//�g�p�I�u�W�F�N�g�̕ǂ̐��𑝂₷
		m_bActive = FALSE;
		bDamageTrigger = FALSE;
	}


	if (!m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->GetActive()) {			//�g�p���Ă���I�u�W�F�N�g��������Ƃ��̃I�u�W�F�N�g��������
		DWORD	dUseNum = m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->GetWeaponUseNum();	//�g�p�I�u�W�F�N�g�̑��݂ł���ǂ̐��擾	
		m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->SetWeaponUseNum(dUseNum + 1);	//�g�p�I�u�W�F�N�g�̕ǂ̐��𑝂₷
		m_bActive = FALSE;
		bDamageTrigger = FALSE;
	}

}


// ---------------------------------------------------------------------------
// �X�L���E�ǃI�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponWallObj::Render()
{

	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-200) && vSPos.x <= WINDOW_WIDTH + 200) && (vSPos.y >= (-200) && vSPos.y <= WINDOW_HEIGHT + 200)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-200) && vSPos.x <= WINDOW_WIDTH + 200) && (vSPos.y >= (-200) && vSPos.y <= WINDOW_HEIGHT + 200)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
	}
}


//-----------------------------------------------------------------------------
//
//�I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	���፷�Əd�͂��l�������A�ڐG������s��								
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�G���[		= -1
//		�ʏ���ړ�	= 1
//		���n		= 2
//		������		= 3
//-----------------------------------------------------------------------------
int  CWeaponWallProc::isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld,DWORD dwPlayerNo)
{
	int  nRet = 0, nRetMove = 0;

	// �ړ��}�b�v�Ƃ̐ڐG����ƈړ�
	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (((CWeaponWallObj*)m_pObjArray[i])->GetPlayerNo() == dwPlayerNo) {
			if (((CWeaponWallObj*)m_pObjArray[i])->GetColMesh() && ((CWeaponWallObj*)m_pObjArray[i])->GetActive())
			{
				nRetMove = ((CWeaponWallObj*)m_pObjArray[i])->GetColMesh()->isCollisionMoveGravity(*pWorld, mWorldOld);  
				if (nRetMove == 1 || nRetMove == 2) break;   // �ړ��}�b�v�ƐڐG�����Ƃ�
			}
		}
	}

	if (nRetMove == 1 || nRetMove == 2)  // �ړ��}�b�v�ƐڐG���Ă����Ƃ�
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}

//-----------------------------------------------------------------------------
//
//�I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	���፷�Əd�͂��l�������A�ڐG������s��								
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�G���[		= -1
//		�ʏ���ړ�	= 1
//		���n		= 2
//		������		= 3
//-----------------------------------------------------------------------------
BOOL  CWeaponWallProc::isBBoxMoveGravity(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld, float fRadius)
{

	BOOL  bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{

		bRet=m_pObjArray[i]->GetBBox()->OBBCollisionLay(vNow, vOld, &vHit, &vNrm);

		if (bRet == TRUE) {
				
			((CWeaponWallObj*)m_pObjArray[i])->isBBoxMoveGravity(pOtherObj, vNow, vOld, vHit, vNrm, fRadius);

			if (bRet) return bRet;

			
		}

	}


	return	bRet;
}

//-----------------------------------------------------------------------------
//
//�I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	���፷�Əd�͂��l�������A�ڐG������s��					
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//-----------------------------------------------------------------------------
BOOL  CWeaponWallObj::isBBoxMoveGravity(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld, VECTOR3 vHit, VECTOR3 vNrm, float fRadius)
{


	bool HitTrigger;
	float fNowDist=0;
	VECTOR3 vTargetPos;
	VECTOR3 vMove,vDist;
	MATRIX4X4	mHitWorld;

	mHitWorld = pOtherObj->GetWorld();


		vMove = normalize(vNow - vOld);		//�ړ��x�N�g��
		vDist = vNrm * dot(-vMove, vNrm);
		fNowDist = magnitude(vDist - vTargetPos);



		vTargetPos = GetPositionVector(pOtherObj->GetWorld());
		fNowDist = magnitude(vHit- vTargetPos);	//�ڐG�ʒu�ƐڐG�����I�u�W�F�N�g�̈ʒu�̋���
		vMove = vNow + vNrm * (-fNowDist + fRadius);	//�H������ł��鋗��
		mHitWorld._41 = vMove.x;
		mHitWorld._42 = vMove.y;
		mHitWorld._43 = vMove.z;

		pOtherObj->SetWorld(mHitWorld);




		//-------------------------------------------------------------------
		HitTrigger = m_pBBox->OBBCollisionLay(vNow, vOld, &vHit, &vNrm);

		vTargetPos = GetPositionVector(pOtherObj->GetWorld());
		fNowDist = magnitude(vHit - vTargetPos);	//�ڐG�ʒu�ƐڐG�����I�u�W�F�N�g�̈ʒu�̋���
		vMove = vNow + vNrm * (-fNowDist + fRadius);	//�H������ł��鋗��
		mHitWorld._41 = vMove.x;
		mHitWorld._42 = vMove.y;
		mHitWorld._43 = vMove.z;

		pOtherObj->SetWorld(mHitWorld);
	
	


	int nRet = 0;

	m_dwStatus = NORMAL;
	pOtherObj->SetStatus(NORMAL);


	return TRUE;
}

// ================================================================================================================================


//============================================================================
// �X�L���E�Ȃ���{�[���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponBendBallProc::CWeaponBendBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �Ȃ���{�[�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Weapon_BallBend.mesh"));

	for (int i = 0; i < BENDBALLL_MAX; i++)		
	{
		m_pObjArray.push_back(new CWeaponBendBallObj(m_pGMain));	// m_pObjArray�ɃX�L���E�Ȃ���{�[���I�u�W�F�N�g�𐶐�����
		((CWeaponBendBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
		m_pObjArray[i]->SetObjID(m_dwProcID);	

	}
}
//============================================================================
// �X�L���E�Ȃ���{�[���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBendBallProc::~CWeaponBendBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
// �X�L���E�Ȃ���{�[���v���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X
//  VECTOR3    vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j

// ---------------------------------------------------------------------------
BOOL CWeaponBendBallProc::Start(MATRIX4X4 mWorld, VECTOR3 vSpeed, DWORD	dwTurn,DWORD dwOwner)
{
	MATRIX4X4 mLay;

	mLay = mWorld;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, vSpeed,dwTurn, dwOwner);	       // �X�L���E�Ȃ���{�[���I�u�W�F�N�g�̔���
			return TRUE;
		}
	}
	return FALSE;
}

// ---------------------------------------------------------------------------
// �X�L���E�Ȃ���{�[���v���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X
//  VECTOR3    vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X
//  DWORD      dwOwner      �F�X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j

// ---------------------------------------------------------------------------
BOOL CWeaponBendBallProc::Start(MATRIX4X4 mWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner,DWORD dwPlayerNo)
{
	MATRIX4X4 mLay;

	mLay = mWorld;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, vSpeed, dwTurn, dwOwner, dwPlayerNo);	       // �X�L���E�Ȃ���{�[���I�u�W�F�N�g�̔���
			return TRUE;
		}
	}
	return FALSE;
}


//============================================================================
// �X�L���E�Ȃ���{�[���I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBendBallObj::CWeaponBendBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // �U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-0.85f, -0.35f, -0.85f);
	VECTOR3 vMax(0.85f, 0.35f, 0.85f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                         


}
// ---------------------------------------------------------------------------
// �X�L���E�Ȃ���{�[���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBendBallObj::~CWeaponBendBallObj()
{
	;
}
// ---------------------------------------------------------------------------
// �X�L���E�Ȃ���{�[���I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     �Ȃ���{�[���̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner        �X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponBendBallObj::Start(MATRIX4X4 mStartWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner)
{
	//const float fSpeed = 0.05f;		// �Ȃ���{�[���̑���
	//const int nLifeTime = 300;		// �Ȃ���{�[���̎�������
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	dwTurnPos = dwTurn;

	dTargetNo = m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->GetTargetNo();
	fBendBallDist = m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->GetBendBallDist();
	m_dwOwner = dwOwner;
	vRotUp.y = 0;
	dwMoveStatus = START;
	m_vPosUp = vSpeed;
	m_bDamage = FALSE;
	Count = 0;
	m_vDiffuse = VECTOR4(1, 1, 1, 1);
	mStartRot = GetRotateMatrix(m_mWorld);
	if(dwTurnPos==LEFT)
	m_mWorld = XMMatrixRotationZ(XMConvertToRadians(180.0f))*m_mWorld;
	return TRUE;
}

// ---------------------------------------------------------------------------
// �X�L���E�Ȃ���{�[���I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     �Ȃ���{�[���̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner        �X�L���𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponBendBallObj::Start(MATRIX4X4 mStartWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner, DWORD dwPlayerNo)
{
	//const float fSpeed = 0.05f;		// �Ȃ���{�[���̑���
	//const int nLifeTime = 300;		// �Ȃ���{�[���̎�������
	m_dwPlayerNo = dwPlayerNo;
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	dwTurnPos = dwTurn;

	dTargetNo = m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->GetTargetNo();
	fBendBallDist = m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->GetBendBallDist();
	m_dwOwner = dwOwner;
	vRotUp.y = 0;
	dwMoveStatus = START;
	m_vPosUp = vSpeed;
	m_bDamage = FALSE;
	Count = 0;
	m_vDiffuse = VECTOR4(1, 1, 1, 1);
	mStartRot = GetRotateMatrix(m_mWorld);
	if (dwTurnPos == LEFT)
		m_mWorld = XMMatrixRotationZ(XMConvertToRadians(180.0f))*m_mWorld;
	return TRUE;
}


// ---------------------------------------------------------------------------
// �Ȃ���{�[���I�u�W�F�N�g�̃��[�J�����}�g���b�N�X�𓾂�֐�
//
//  m_mWorld�̈ʒu����m_fLocalRotY�̊p�x��������
//  ���[�J�����}�g���b�N�X��Ԃ�
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponBendBallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
// �X�L���E�Ȃ���{�[���I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponBendBallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;
		// �����Ȃ���{�[���̈ʒu����ƈړ�
		VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // �����̑O�̈ʒu

		MATRIX4X4 mTemp;

		BallDirectionStart(dwTurnPos);
		VECTOR3 vHit, vNormal;
		if (m_pGMain->m_pMapProc->Hitcheck(this, &vHit, &vNormal))  // �}�b�v�R���W����
		{
			// �ǂɂԂ������Ƃ��폜����
			ObjBasicDelete();
		}
		

		//�ǂƂ̓����蔻��		
		if (m_pGMain->m_pWeaponProc->m_pWeaponWallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {
			m_pHitObj->SetStatus(NORMAL);
			ObjBasicDelete();
		}


		if (m_bDamage != TRUE) {
			ObjBend();
			if (m_pGMain->m_pEnmProc->m_pEnmBallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo))
			{
					m_pHitObj->SetActive(FALSE);
					m_dwStatus = NORMAL;
					m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���

			}
			if (m_pGMain->m_pWeaponProc->m_pWeaponDivBallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)||m_pGMain->m_pWeaponProc->m_pWeaponBigBallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo))
			{
				m_pHitObj->SetActive(FALSE);
				m_dwStatus = NORMAL;
				m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���

			}

		}
		else {
			m_vPosUp.x = 0;

			DamageRearHitcheck();
		}

		switch (m_dwStatus)
		{

		case DAMAGE:
			UpdateDamage();

			break;
		}
		m_pBBox->m_mWorld = m_mWorld;

		// �����_�����O
		Render();
		Count++;
	}
}
//----------------------------------------------------------------------------
//�Ȃ���{�[��������������
//----------------------------------------------------------------------------
void CWeaponBendBallObj::UpdateDamage()
{

	if (m_bDamage != TRUE) {
		ObjReflection();
		mStartRot = GetRotateMatrix(m_mWorld);
		m_pGMain->m_pEffectProc->m_pShockWaveProc->Start(m_vHitPos, m_dwPlayerNo);	// �p�[�e�B�N���̔���
		m_bDamage = TRUE;
	}

	m_dwStatus = NORMAL;

}

//----------------------------------------------------------------------------
//�Ȃ���{�[������]��������
//
//----------------------------------------------------------------------------
void CWeaponBendBallObj::BallDirectionStart(DWORD dwTurnPos)
{
	MATRIX4X4 mTemp;
	VECTOR3 vWorldPos;
	mTemp = XMMatrixRotationY(XMConvertToRadians(-10.0f));	//��]�������� 
	m_mWorld = mTemp * m_mWorld;
	VECTOR3 m_vBasePosWorld = GetPositionVector(m_mWorld);	//���[���h�}�g���b�N�X�̈ʒu���擾
	MATRIX4X4 m_mRotWorld = GetRotateMatrix(m_mWorld);		//���[���h�}�g���b�N�X�̊p�x�擾
	m_mWorld = XMMatrixTranslation(m_vBasePosWorld.x, m_vBasePosWorld.y, m_vBasePosWorld.z);
	if (dwTurnPos == RIGHT) vWorldPos = GetPositionVector(XMMatrixTranslation(m_vPosUp.x, 0, m_vPosUp.z)*mStartRot*m_mWorld);
	if (dwTurnPos == LEFT) vWorldPos = GetPositionVector(XMMatrixTranslation(-m_vPosUp.x, 0, m_vPosUp.z)*mStartRot*m_mWorld);
	m_mWorld = XMMatrixTranslation(vWorldPos.x, vWorldPos.y, vWorldPos.z);
	m_mWorld = m_mRotWorld * m_mWorld;



}

//----------------------------------------------------------------------------
//�Ȃ���{�[���̋Ȃ��鏈��
//
//
//----------------------------------------------------------------------------
void CWeaponBendBallObj::ObjBend()
{
	switch (dwMoveStatus)
	{
	case START:
		m_vPosUp.x -= 0.0003;
		if (m_vPosUp.x < 0)
		{
			dwMoveStatus = INTER;

		}

		break;
	case INTER:
		m_vPosUp.x -= 0.0005;
		m_vPosUp.z += 0.0003;
		if ((m_vPosUp.x*-1) > m_vPosUp.z)
		{
			dwMoveStatus = FINAL;

		}

		break;

	case FINAL:
		//m_vPosUp.x -= 0.0005;
		m_vPosUp.z += 0.0008;

		break;

	default:
		break;

	}


}

//----------------------------------------------------------------------------
//�Ȃ���{�[�����ł��Ԃ����Ƃ��̏���
//
//
//----------------------------------------------------------------------------
void CWeaponBendBallObj::DamageRearHitcheck()
{
	if (m_bDamage == TRUE) {
		if (m_pGMain->m_pEnmProc->m_pEnmTargetProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {

		}

		if (m_pGMain->m_pEnmProc->m_pEnmMoveTargetProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {
		}

		if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {
		}

		if (m_pGMain->m_pEnmProc->m_pEnmShieldProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {
		}

		if (m_pGMain->m_pEnmProc->m_pEnmWallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {

		}
		if (m_pGMain->m_pEnmProc->m_pEnmBendProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {

		}

	}



}


// ---------------------------------------------------------------------------
// �X�L���E�Ȃ���{�[���I�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
//
//
// ---------------------------------------------------------------------------
void CWeaponBendBallObj::Render()
{

	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

}
