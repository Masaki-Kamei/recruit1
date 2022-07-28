//=============================================================================
//
//		��{�v���V�[�W���E��{�I�u�W�F�N�g�N���X����
//																BaseProc.cpp
//=============================================================================
#include  "BaseProc.h"

//------------------------------------------------------------------------
//
//	��{�v���V�[�W���N���X�̃f�X�g���N�^	
//  �i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����č폜����j
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CBaseProc::~CBaseProc()
{
	// �v���V�[�W���|�C���^�z��̍폜
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		SAFE_DELETE(m_pProcArray[i]);
	}
	// �I�u�W�F�N�g�|�C���^�z��̍폜
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		SAFE_DELETE(m_pObjArray[i]);
	}
}
//------------------------------------------------------------------------
//
//	��{�v���V�[�W���N���X�̑S�̍X�V����	
//  �i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����čX�V����������j
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
void CBaseProc::UpdateAll()
{

	Update();                              // �v���V�[�W���̍X�V����
	if (m_nWaitTime > 0) m_nWaitTime--;    // �E�F�C�g�^�C�}�[�̃J�E���g�_�E��

	// �I�u�W�F�N�g�|�C���^�z��̍X�V
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if(m_pObjArray[i]->GetPlayerNo()!=SECONDPLAYER)m_pObjArray[i]->Update();          // �I�u�W�F�N�g�̍X�V����
	}

	// ���ʂ̃v���V�[�W���|�C���^�z��̍X�V
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->UpdateAll();      // ���ʂ̃v���V�[�W���̑S�̍X�V�����i�ċA�����j
	}

}

//------------------------------------------------------------------------
//	��{�v���V�[�W���N���X�̑S�̍X�V����	
//  �i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����čX�V����������j
//
//  DWORD	m_dwPlayerNo		�v���C���[�ԍ�
//
//------------------------------------------------------------------------
void CBaseProc::UpdateAllMulti(DWORD m_dwPlayerNo)
{

	UpdateMulti(m_dwPlayerNo);                              // �v���V�[�W���̍X�V����

	// �I�u�W�F�N�g�|�C���^�z��̍X�V
	if (m_dwPlayerNo == FIRSTPLAYER) {	//�P�v���C���[�̃I�u�W�F�N�g�X�V����
		if (m_nWaitTime > 0) m_nWaitTime--;    // �E�F�C�g�^�C�}�[�̃J�E���g�_�E��
		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (m_pObjArray[i]->GetPlayerNo() == m_dwPlayerNo)m_pObjArray[i]->Update();          // �I�u�W�F�N�g�̍X�V����
		}
	}
	else if (m_dwPlayerNo == SECONDPLAYER) {	//�Q�v���C���[�̃I�u�W�F�N�g�X�V����
		if (m_nWaitTimeSec > 0) m_nWaitTimeSec--;    // �E�F�C�g�^�C�}�[�̃J�E���g�_�E��
		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (m_pObjArray[i]->GetPlayerNo() == m_dwPlayerNo)m_pObjArray[i]->Update();          // �I�u�W�F�N�g�̍X�V����

		}

	}
	// ���ʂ̃v���V�[�W���|�C���^�z��̍X�V
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->UpdateAllMulti(m_dwPlayerNo);      // ���ʂ̃v���V�[�W���̑S�̍X�V�����i�ċA�����j
	}

}


//-----------------------------------------------------------------------------
// ��{�v���V�[�W���N���X�̂����蔻��(�ړ�����)
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// �E���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�Ƒ���̈ړ������Ƃ̂����蔻�菈��������
//
//   CBaseObj* pOtherObj    ����̃I�u�W�F�N�g
//   VECTOR3 vNow       ����̌��݈ʒu
//   VECTOR3 vOld       ����̈�O�̈ʒu
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   ����Ǝ����I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj, vNow, vOld);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->Hitcheck(pOtherObj, vNow, vOld);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
// ��{�v���V�[�W���N���X�̂����蔻��i�o�E���f�B���O�{�b�N�X�j
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// �E���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�Ƒ���̍U���o�E���f�B���O�{�b�N�X�Ƃ̂����蔻��
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//   CBBox*    pAttackBBox    �ΏۂƂȂ�o�E���f�B���O�{�b�N�X
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   ����Ǝ����̃I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}
//-----------------------------------------------------------------------------
// ��{�v���V�[�W���N���X�̂����蔻��i�����̈ړ������j
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// �E���I�u�W�F�N�g�̈ړ������Ƒ���̃o�E���f�B���O�{�b�N�X�Ƃ̂����蔻��
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   ����Ǝ����̃I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::HitcheckOtherLay(CBaseObj* pOtherObj)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
			bRet = m_pObjArray[i]->HitcheckOtherLay(pOtherObj);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
			if (bRet) return bRet;
		
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->HitcheckOtherLay(pOtherObj);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
//��{�v���V�[�W���N���X�̈�����
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// 
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//	 float	�@�@fDist		  ����Ƃ̔��苗��
//	 float		fRotateSpeed�@�����]���̃X�s�[�h
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F���苗���ɓ����Ă��Ȃ�
//
//   ���茋�ʁ@�@
//           ���苗���ȓ��@�@�@�@����I�u�W�F�N�g�����I�u�W�F�N�g�Ɍ�����ς���
//           ���苗���ȊO�@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::ObjGravity(CBaseObj* pOtherObj, float fDist, float fRotateSpeed)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		if(m_pObjArray[i]->GetActive()==TRUE)
			bRet = m_pObjArray[i]->ObjGravity(pOtherObj, fDist, fRotateSpeed);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
			if (bRet) return bRet;
		
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->ObjGravity(pOtherObj, fDist, fRotateSpeed);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}


//-----------------------------------------------------------------------------
//��{�v���V�[�W���N���X�̕��������X�Ɍ���
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// 
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//	 float		fRotateSpeed�@�����]���̃X�s�[�h
//	 DWORD		RanNum		�@�ΏۃI�u�W�F�N�g��ID
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F���苗���ɓ����Ă��Ȃ�
//
//   ���茋�ʁ@�@
//           ���苗���ȓ��@�@�@�@����I�u�W�F�N�g�����I�u�W�F�N�g�Ɍ�����ς���
//           ���苗���ȊO�@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::ObjTarget(CBaseObj* pOtherObj, float fRotateSpeed,DWORD RanNum)
{
	BOOL  bRet = FALSE;
	DWORD j=RanNum;

	bRet = m_pObjArray[j]->ObjTarget(pOtherObj, fRotateSpeed);  // ����I�u�W�F�N�g�Ƃ̂����蔻��

	if (bRet) return bRet;
	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->ObjTarget(pOtherObj,  fRotateSpeed,RanNum);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
// ��{�v���V�[�W���N���X�̂����蔻��i�o�E���f�B���O�{�b�N�X�j
//
//�w�肵��ID�����O�ł���
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// �E���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�Ƒ���̍U���o�E���f�B���O�{�b�N�X�Ƃ̂����蔻��
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//   CBBox*    pAttackBBox    �ΏۂƂȂ�o�E���f�B���O�{�b�N�X
//	DWORD	  NotID			���O����ID
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   ����Ǝ����̃I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack,DWORD NotID)
{
	BOOL  bRet = FALSE;
	if (m_dwProcID != NotID) {
		// �S�Ă̑���Ƃ̂����蔻��
		for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
		{
			bRet = m_pObjArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
			if (bRet) return bRet;
		}
	}
		for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
		{
			bRet = m_pProcArray[i]->Hitcheck(pOtherObj, pBBoxAtack,NotID);  // ����v���V�[�W���Ƃ̂����蔻��
			if (bRet) return bRet;
		}
	
	return bRet;
}

//-----------------------------------------------------------------------------
//��{�v���V�[�W���N���X�͈̔̓`�F�b�N
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// 
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//	 float	�@�@fDist		  ����Ƃ̔��苗��
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F���苗���ɓ����Ă��Ȃ�
//
//   ���茋�ʁ@�@
//           ���苗���ȓ��@�@�@�@����I�u�W�F�N�g�����I�u�W�F�N�g�Ɍ�����ς���
//           ���苗���ȊO�@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::ObjTerritory(CBaseObj* pOtherObj, float fDist)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		if (m_pObjArray[i]->GetbShaftObjTrigger() != TRUE) {
			bRet = m_pObjArray[i]->ObjTerritory(pOtherObj, fDist);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
			if (bRet) return bRet;
		}
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->ObjTerritory(pOtherObj, fDist);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------		
// ��{�v���V�[�W���N���X�̂����蔻��(�ړ�����)
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// �E���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�Ƒ���̈ړ������Ƃ̂����蔻�菈��������
//
//   CBaseObj* pOtherObj    ����̃I�u�W�F�N�g
//   VECTOR3 vNow       ����̌��݈ʒu
//   VECTOR3 vOld       ����̈�O�̈ʒu
//	 DWORD	m_dwPlayerNo		�v���C���[�ԍ�

//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   ����Ǝ����I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::HitcheckMulti(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {	//�����v���C���[�i���o�[�̃I�u�W�F�N�g���m�̂ݏ���
			bRet = m_pObjArray[i]->Hitcheck(pOtherObj, vNow, vOld);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
			if (bRet) return bRet;
		}
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->HitcheckMulti(pOtherObj, vNow, vOld, dwPlayerNo);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
// ��{�v���V�[�W���N���X�̂����蔻��i�o�E���f�B���O�{�b�N�X�j
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// �E���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�Ƒ���̍U���o�E���f�B���O�{�b�N�X�Ƃ̂����蔻��
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//   CBBox*    pAttackBBox    �ΏۂƂȂ�o�E���f�B���O�{�b�N�X
//   DWORD	m_dwPlayerNo		�v���C���[�ԍ�
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   ����Ǝ����̃I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::HitcheckMulti(CBaseObj* pOtherObj, CBBox* pBBoxAtack, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {	//�����v���C���[�i���o�[�̃I�u�W�F�N�g���m�̂ݏ���
			bRet = m_pObjArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
			if (bRet) return bRet;
		}
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->HitcheckMulti(pOtherObj, pBBoxAtack, dwPlayerNo);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}
//-----------------------------------------------------------------------------
// ��{�v���V�[�W���N���X�̂����蔻��i�����̈ړ������j
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// �E���I�u�W�F�N�g�̈ړ������Ƒ���̃o�E���f�B���O�{�b�N�X�Ƃ̂����蔻��
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//   DWORD	m_dwPlayerNo		�v���C���[�ԍ�
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   ����Ǝ����̃I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::HitcheckMultiOtherLay(CBaseObj* pOtherObj, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {	//�����v���C���[�i���o�[�̃I�u�W�F�N�g���m�̂ݏ���
			bRet = m_pObjArray[i]->HitcheckOtherLay(pOtherObj);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
			if (bRet) return bRet;
		}

	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->HitcheckMultiOtherLay(pOtherObj, dwPlayerNo);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
//��{�v���V�[�W���N���X�̈�����
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// 
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//	 float	�@�@fDist		  ����Ƃ̔��苗��
//	 float		fRotateSpeed�@�����]���̃X�s�[�h
//   DWORD	m_dwPlayerNo		�v���C���[�ԍ�

//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F���苗���ɓ����Ă��Ȃ�
//
//   ���茋�ʁ@�@
//           ���苗���ȓ��@�@�@�@����I�u�W�F�N�g�����I�u�W�F�N�g�Ɍ�����ς���
//           ���苗���ȊO�@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::ObjGravityMulti(CBaseObj* pOtherObj, float fDist, float fRotateSpeed, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {	//�����v���C���[�i���o�[�̃I�u�W�F�N�g���m�̂ݏ���
			if (m_pObjArray[i]->GetActive() == TRUE)
				bRet = m_pObjArray[i]->ObjGravity(pOtherObj, fDist, fRotateSpeed);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
			if (bRet) return bRet;
		}

	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->ObjGravityMulti(pOtherObj, fDist, fRotateSpeed, dwPlayerNo);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}


//-----------------------------------------------------------------------------
//��{�v���V�[�W���N���X�̕��������X�Ɍ���
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// 
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//	 float		fRotateSpeed�@�����]���̃X�s�[�h
//	 DWORD		RanNum		�@�ΏۃI�u�W�F�N�g��ID
//   DWORD	m_dwPlayerNo		�v���C���[�ԍ�
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F���苗���ɓ����Ă��Ȃ�
//
//   ���茋�ʁ@�@
//           ���苗���ȓ��@�@�@�@����I�u�W�F�N�g�����I�u�W�F�N�g�Ɍ�����ς���
//           ���苗���ȊO�@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::ObjTargetMulti(CBaseObj* pOtherObj, float fRotateSpeed, DWORD RanNum, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;
	DWORD j = RanNum;

	if (m_pObjArray[j]->GetPlayerNo() == dwPlayerNo) {	//�����v���C���[�i���o�[�̃I�u�W�F�N�g���m�̂ݏ���
		bRet = m_pObjArray[j]->ObjTarget(pOtherObj, fRotateSpeed);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
	}
	if (bRet) return bRet;
	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->ObjTargetMulti(pOtherObj, fRotateSpeed, RanNum, dwPlayerNo);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
// ��{�v���V�[�W���N���X�̂����蔻��i�o�E���f�B���O�{�b�N�X�j
//
//�w�肵��ID�����O�ł���
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// �E���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�Ƒ���̍U���o�E���f�B���O�{�b�N�X�Ƃ̂����蔻��
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//   CBBox*    pAttackBBox    �ΏۂƂȂ�o�E���f�B���O�{�b�N�X
//	 DWORD	  NotID			���O����ID
//   DWORD	m_dwPlayerNo		�v���C���[�ԍ�
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   ����Ǝ����̃I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::HitcheckMulti(CBaseObj* pOtherObj, CBBox* pBBoxAtack, DWORD NotID, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;
	if (m_dwProcID != NotID) {
		// �S�Ă̑���Ƃ̂����蔻��
		for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
		{
			if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {	//�����v���C���[�i���o�[�̃I�u�W�F�N�g���m�̂ݏ���
				bRet = m_pObjArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
				if (bRet) return bRet;
			}
		}
	}
	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->HitcheckMulti(pOtherObj, pBBoxAtack, NotID, dwPlayerNo);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
//��{�v���V�[�W���N���X�͈̔̓`�F�b�N
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉���
// 
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//	 float	�@�@fDist		  ����Ƃ̔��苗��
//   DWORD	m_dwPlayerNo		�v���C���[�ԍ�
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F���苗���ɓ����Ă��Ȃ�
//
//   ���茋�ʁ@�@
//           ���苗���ȓ��@�@�@�@����I�u�W�F�N�g�����I�u�W�F�N�g�Ɍ�����ς���
//           ���苗���ȊO�@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::ObjTerritoryMulti(CBaseObj* pOtherObj, float fDist, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {	//�����v���C���[�i���o�[�̃I�u�W�F�N�g���m�̂ݏ���
			if (m_pObjArray[i]->GetbShaftObjTrigger() != TRUE) {
				bRet = m_pObjArray[i]->ObjTerritory(pOtherObj, fDist);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
				if (bRet) return bRet;
			}
		}
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->ObjTerritoryMulti(pOtherObj, fDist, dwPlayerNo);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}


//============================================================================
//   
//	�v���V�[�W���ƃI�u�W�F�N�g��T�����S�ẴI�u�W�F�N�g���m���A�N�e�B�u�ɂ���
//   
//	�����@	�Ȃ�
//
//	�߂�l  �Ȃ�
//============================================================================
void  CBaseProc::SetNonActive()
{

	// �G�̃I�u�W�F�N�g�|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive(FALSE);   // �A�N�e�B�u�t���O��FALSE��
		m_pObjArray[i]->ResetStatus();      // �e��X�e�[�^�X�����Z�b�g
	}

	// ���ʂ̃v���V�[�W���|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetMaxWaitTime();    // �E�F�C�g�^�C�����Z�b�g����
		m_pProcArray[i]->SetNonActive();      // ���ʂ̃v���V�[�W���̏����i�ċA�����j
	}

	m_dwBreakNum = 0;		//�j�󐔏�����

}


//------------------------------------------------------------------------
//
//	��{�I�u�W�F�N�g�N���X�̃R���X�g���N�^	
//
//  �����@CGameMain* pGMain  // �Q�[�����C���N���X
//
//------------------------------------------------------------------------
CBaseObj::CBaseObj(CGameMain* pGMain)
{
	// �S�̂̃[���N�����[
	// ���ӓ_�F�N���X���ɂr�s�k��錾���Ă���Ƃ��͎g�p���Ă͂Ȃ�Ȃ�
	ZeroMemory(this, sizeof(CBaseObj));

	m_pGMain = pGMain;					// �Q�[�����C���N���X
	ResetStatus();						// �e��X�e�[�^�X�����Z�b�g
	m_mWorld = XMMatrixIdentity();		// ���[���h�}�g���N�X
	m_mWorldOld = XMMatrixIdentity();	// ���[���h�}�g���N�X�i��O�j

	m_AnimStatus.playAnim = true;		// �A�j���[�V�����𓮍삳����
}
//------------------------------------------------------------------------
//
//	��{�I�u�W�F�N�g�N���X�̃f�X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CBaseObj::~CBaseObj()
{
	SAFE_DELETE(m_pBBox);
}

//-----------------------------------------------------------------------------
//
// ��{�I�u�W�F�N�g�N���X�̂����蔻��(�ړ�����)
//
// �E���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�Ƒ���̈ړ������Ƃ̂����蔻��
//
//   CBaseObj* pOtherObj  ����̃I�u�W�F�N�g
//   VECTOR3 vNow     ����̌��݈ʒu
//   VECTOR3 vOld     ����̈�O�̈ʒu
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����ƓG�̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   �G�I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����ƓG�̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld)
{
	BOOL bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	// �o�E���f�B���O�{�b�N�X�ƈړ������iLay�j�ɂ�锻��
	if ((m_bActive && m_dwStatus != DAMAGE && m_dwStatus != DEAD && m_dwStatus != FLASH) &&
		m_pBBox->OBBCollisionLay(vNow, vOld, &vHit, &vNrm))
	{
		HitStatus(pOtherObj, vHit, vNrm);
		bRet = TRUE;
	}
	return bRet;
}
//-----------------------------------------------------------------------------
//
// ��{�I�u�W�F�N�g�N���X�̂����蔻��i�o�E���f�B���O�{�b�N�X�j
//
// �E���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�Ƒ���̃o�E���f�B���O�{�b�N�X�Ƃ̂����蔻��
//
//   CBaseObj* pOtherObj  ����̃I�u�W�F�N�g
//   CBBox*      pBBoxAtack   �o�E���f�B���O�{�b�N�X�̔��������Ƃ�
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����ƓG�̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   �G�I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����ƓG�̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack)
{
	BOOL bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	// �o�E���f�B���O�{�b�N�X���m�ɂ�锻��
	if ((m_bActive && m_dwStatus != DAMAGE && m_dwStatus != DEAD && m_dwStatus != FLASH) &&
		m_pBBox->OBBCollisionDetection(pBBoxAtack, &vHit, &vNrm))
	{
		HitStatus(pOtherObj, vHit, vNrm);
		bRet = TRUE;
	}
	return bRet;
}

//-----------------------------------------------------------------------------
// ��{�I�u�W�F�N�g�N���X�̂����蔻��(�����̈ړ�����)
//
// �E���I�u�W�F�N�g�̈ړ������Ƒ���̃o�E���f�B���O�{�b�N�X�Ƃ̂����蔻��
//
//   CBaseObj* pOtherObj  ����̃I�u�W�F�N�g
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����ƓG�̃I�u�W�F�N�g��m_pHitObj��m_vHitPos��m_vHitNormal�ɒl���Z�b�g
//                                   �G�I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����ƓG�̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::HitcheckOtherLay(CBaseObj* pOtherObj)
{
	BOOL bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);
	VECTOR3 vNow = GetPositionVector(m_mWorld);
	VECTOR3 vOld = GetPositionVector(m_mWorldOld);

	// �o�E���f�B���O�{�b�N�X�ƈړ������iLay�j�ɂ�锻��
	if ((m_bActive && m_dwStatus != DAMAGE && m_dwStatus != DEAD && m_dwStatus != FLASH) &&
		pOtherObj->m_pBBox->OBBCollisionLay(vNow, vOld, &vHit, &vNrm))
	{
		HitStatus(pOtherObj, vHit, vNrm);
		bRet = TRUE;
	}
	return bRet;
}

//----------------------------------------------------------------------------- 
//
// �q�b�g�������̃X�e�[�^�X�ύX
//
//
//   CBaseObj* pOtherObj  ����̃I�u�W�F�N�g
//	 VECTOR3   vHit		�@���������ꏊ�̍��W
//	 VECTOR3   vNrm		�@���������ꏊ�̖@�����W
//
//-----------------------------------------------------------------------------
void   CBaseObj::HitStatus(CBaseObj* pOtherObj, VECTOR3 vHit, VECTOR3 vNrm)
{

	m_pHitObj = pOtherObj;	//�q�b�g�I�u�W�F�N�g�̍X�V
	pOtherObj->m_pHitObj = this;	//����̃I�u�W�F�N�g�̃q�b�g�I�u�W�F�N�g�̍X�V
	m_vHitPos = vHit;			//���������ꏊ�̍X�V
	m_vHitNormal = vNrm;		//���������ꏊ�̖@���̍X�V
	pOtherObj->m_vHitPos = vHit;	//����̃I�u�W�F�N�g�̓��������ꏊ�̍X�V
	pOtherObj->m_vHitNormal = vNrm;	//����̃I�u�W�F�N�g�̓��������ꏊ�̖@���̍X�V
	m_dwStatus = DAMAGE;			//�X�e�[�^�X��DAMAGE�ɂ���
	pOtherObj->m_dwStatus = DAMAGE;	//����̃I�u�W�F�N�g�̃X�e�[�^�X��DAMAGE�ɂ���

}




//-----------------------------------------------------------------------------
//��{�v���V�[�W���N���X�̈�����
//
// 
//
//   CBaseObj* pOtherObj  ����̃I�u�W�F�N�g
//	 float	�@�@fDist		  ����Ƃ̔��苗��
//	 float		fRotateSpeed�@�����]���̃X�s�[�h
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F���苗���ɓ����Ă��Ȃ�
//
//   ���茋�ʁ@�@
//           ���苗���ȓ��@�@�@�@����I�u�W�F�N�g�����I�u�W�F�N�g�Ɍ�����ς���
//           ���苗���ȊO�@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::ObjGravity(CBaseObj* pOtherObj, float fDist, float fRotateSpeed)
{
	BOOL bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);
	MATRIX4X4 mTemp;


	VECTOR3 vTarget = GetPositionVector(m_mWorld);
	VECTOR3 vMyobj = GetPositionVector(pOtherObj->m_mWorld);
	m_fDist = magnitude(vTarget - vMyobj);	//�����̃I�u�W�F�N�g�Ƒ���̃I�u�W�F�N�g�Ƃ̋���
	if (m_fDist < fDist) {	//����Ƃ̔��苗�����߂��Ȃ�

		vTarget.y = vMyobj.y;	//�����𓯂��ɂ���
		m_vRotUp.y = GetTargetRotateVector(pOtherObj->m_mWorld, vTarget).y;	//�I�u�W�F�N�g�̌������^�[�Q�b�g���������߂̊p�x
		RotRig(&m_vRotUp.y);	//�p�x�𒲐�
		if (m_vRotUp.y > fRotateSpeed)  m_vRotUp.y = fRotateSpeed;	// fRotateSpeed�x�ȏ�̕����ϊ��͍s��Ȃ�
		if (m_vRotUp.y < -fRotateSpeed) m_vRotUp.y = -fRotateSpeed;	// fRotateSpeed�x�ȏ�̕����ϊ��͍s��Ȃ�
		mTemp = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));	//�p�x�����߂�
		pOtherObj->m_mWorld = mTemp * pOtherObj->m_mWorld;			//�p�x��������

		bRet = TRUE;

	}

	return bRet;
}


//-----------------------------------------------------------------------------
//��{�v���V�[�W���N���X�̕��������X�Ɍ���
//
// 
//
//   CBaseObj* pOtherObj  ����̃I�u�W�F�N�g
//	 float		fRotateSpeed�@�����]���̃X�s�[�h
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F���苗���ɓ����Ă��Ȃ�
//
//   ���茋�ʁ@�@
//           ���苗���ȓ��@�@�@�@����I�u�W�F�N�g�����I�u�W�F�N�g�Ɍ�����ς���
//           ���苗���ȊO�@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::ObjTarget(CBaseObj* pOtherObj,  float fRotateSpeed)
{
	BOOL bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);
	MATRIX4X4 mTemp;

	m_pHitObj = pOtherObj;
	VECTOR3 vTarget = GetPositionVector(m_mWorld);
	pOtherObj->m_pHitObj = this;
	VECTOR3 vMyobj = GetPositionVector(pOtherObj->m_mWorld);
	m_fDist = magnitude(vTarget - vMyobj);	//�����̃I�u�W�F�N�g�Ƒ���̃I�u�W�F�N�g�Ƃ̋����i���̃I�u�W�F�N�g�j
	pOtherObj->m_fDist = magnitude(vTarget - vMyobj);	//�����̃I�u�W�F�N�g�Ƒ���̃I�u�W�F�N�g�Ƃ̋����i����̃I�u�W�F�N�g�j
		vTarget.y = vMyobj.y;	//�����𓯂��ɂ���
		m_vRotUp.y = GetTargetRotateVector(pOtherObj->m_mWorld, vTarget).y;	//�I�u�W�F�N�g�̌������^�[�Q�b�g���������߂̊p�x
		RotRig(&m_vRotUp.y);	//�p�x�𒲐�
		if (m_vRotUp.y > fRotateSpeed)  m_vRotUp.y = fRotateSpeed;	// fRotateSpeed�x�ȏ�̕����ϊ��͍s��Ȃ�
		if (m_vRotUp.y < -fRotateSpeed) m_vRotUp.y = -fRotateSpeed;	// fRotateSpeed�x�ȏ�̕����ϊ��͍s��Ȃ�
		mTemp = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));	//�p�x�����߂�
		pOtherObj->m_mWorld = mTemp * pOtherObj->m_mWorld;			//�p�x��������
	


		bRet = TRUE;

	

	return bRet;
}



//-----------------------------------------------------------------------------
//�ړI�n�ivTargetX,Z�j�ւ̈ړ�����  �ėp�֐�
//
//   ����
//               VECTOR3       :vTarget :�s����
//               float fSpeedIn    :���̈ړ���
//               float fRotSpeed   :��]���x(�ȗ��l��3.0f)
//
//   �߂�l�@�F�@TRUE�F�ړI�n�ɒB�����@�@FALSE:�܂��ړI�n�ɒB���Ă��Ȃ�
//               ������Am_vPosUp, m_vRotUp�Ɉړ��ʂ��ݒ肳���
//-----------------------------------------------------------------------------
BOOL CBaseObj::TargetMove(VECTOR3 vTarget, float fSpeedIn, float fRotSpeed)
{
	BOOL ret = FALSE;
	VECTOR3 vMove, vObjPos, vObjPosOld;
	float fLen, fSpeed;
	const float fNearLimit = 0.1f;    // �ړI�n�Ƃ̋ߐڃ��~�b�g(10cm�ȓ��ɋߐڂ����Ƃ�)

	vObjPos = GetPositionVector(m_mWorld);
	vObjPosOld = GetPositionVector(m_mWorldOld);

	vTarget.y = m_mWorld._42;		// �^�[�Q�b�g�̓I�u�W�F�N�g�Ɠ��ꍂ���Ƃ���

	if ((vObjPos.x <= vTarget.x + fNearLimit && vObjPos.x >= vTarget.x - fNearLimit) &&		// �ړI�n�ɋߐڂ����Ƃ�
		(vObjPos.z <= vTarget.z + fNearLimit && vObjPos.z >= vTarget.z - fNearLimit))
	{  // �ړI�n�ɒB�����Ƃ�
		m_vPosUp.x = 0;
		m_vPosUp.y = 0;
		m_vPosUp.z = 0;
		m_vRotUp = VECTOR3(0, 0, 0);
		ret = TRUE; // �ړI�n�ɒB����

	}
	else {    // �ړI�n�ւ̈ړ�����

		vMove = vTarget - vObjPos;
		fLen = magnitude(vMove);
		if (fLen < fSpeedIn)
		{
			fSpeed = fSpeedIn - fLen;
		}
		else {
			fSpeed = fSpeedIn;
		}

		m_vRotUp.y = GetTargetRotateVector(m_mWorld, vTarget).y;	// �^�[�Q�b�g�̕�������������Y���p�x�����߂�
		RotRig(&m_vRotUp.y);
		if (m_vRotUp.y > fRotSpeed) m_vRotUp.y = fRotSpeed;		// fRotSpeed�x�ȏ�̕����ϊ��͍s��Ȃ�
		if (m_vRotUp.y < -fRotSpeed) m_vRotUp.y = -fRotSpeed;		// fRotSpeed�x�ȏ�̕����ϊ��͍s��Ȃ�

		m_vPosUp.x = 0;
		m_vPosUp.y = 0;
		m_vPosUp.z = fSpeed;

		ret = FALSE;    // �܂��ړI�n�ɒB���Ă��Ȃ�
	}

	return ret;
}

//-----------------------------------------------------------------------------
//��{�v���V�[�W���N���X�͈̔̓`�F�b�N
//
// 
//
//   CBaseObj* pOtherObj  ����̃I�u�W�F�N�g
//	 float	�@�@fDist		  ����Ƃ̔��苗��
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F���苗���ɓ����Ă��Ȃ�
//
//   ���茋�ʁ@�@
//           ���苗���ȓ��@�@�@�@����I�u�W�F�N�g�����I�u�W�F�N�g�Ɍ�����ς���
//           ���苗���ȊO�@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pHitObj��NULL���Z�b�g
//
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::ObjTerritory(CBaseObj* pOtherObj, float fDist)
{
	BOOL bRet = FALSE;

	VECTOR3 vTarget = GetPositionVector(pOtherObj->m_mWorld);
	VECTOR3 vMyobj = GetPositionVector(m_mWorld);
	m_fDist = magnitude( vMyobj- vTarget);	//�����̃I�u�W�F�N�g�Ƒ���̃I�u�W�F�N�g�Ƃ̋���
	if (m_fDist < fDist&&m_bDamage != true) {	//����Ƃ̔��苗�����߂����_���[�W���󂯂Ă��Ȃ����
		if (bShaftObjTrigger != TRUE) {		//��]��Ԃł͂Ȃ��Ȃ�
			m_pShaftObj = pOtherObj;		//�I�u�W�F�N�g�����ɂ���
			m_fShaftDist = m_fDist;			//���ƃI�u�W�F�N�g�̋���
			bShaftObjTrigger = TRUE;		//��]��Ԃɂ���
		}

		bRet = TRUE;

	}

	return bRet;
}



//----------------------------------------------------------------------------- 
// �I�u�W�F�N�g��mWorld�ƈ����ʒu�Ƃ̋��������߂�
//
//   �����@�@�F�@vPos :�ʒu
//   �߂�l�@�F�@����
//-----------------------------------------------------------------------------
float CBaseObj::GetDistance(VECTOR3 vPos)
{
	VECTOR3 vVec;
	vVec = vPos - GetPositionVector(m_mWorld);

	return  magnitude(vVec);
}
//----------------------------------------------------------------------------- 
// �X�e�[�^�X�����Z�b�g����
//
//   �����@�@�F�@�Ȃ�
//   �߂�l�@�F�@�Ȃ�
//-----------------------------------------------------------------------------
void CBaseObj::ResetStatus()
{
	m_dwStatus = NORMAL;			// �X�e�[�^�X
	m_dwStatusSub = ATTACKNONE;		// �X�e�[�^�X�T�u
	m_dwStatusPhase = 0;			// �X�e�[�^�X�t�F�[�Y
	
}

//============================================================================
//  �I�u�W�F�N�g���m���d�Ȃ�Ȃ��悤�ɂ��郁���o�֐�
//
//	�����@	CBaseProc* pProj�@�ΏۂƂ����{�v���V�[�W��
//
//	�߂�lCBaseObj* 	�I�u�W�F�N�g�A�h���X:�����ړ��̑���I�u�W�F�N�g�@NULL:�ڋ��������Ă��Ȃ�
//============================================================================
CBaseObj*  CBaseObj::SetKeepOffset(CBaseProc* pProc)
{
	float	fMyRadius, fOtherRadius, fAddRadius, fLen, fMvMax = 0.0f;
	VECTOR3  vMy, vOther;
	VECTOR2  vMy2, vOther2;
	MATRIX4X4	 matWk1, matWk2;
	CBaseObj     *pOtherObj, *pTargetObj = NULL;
	CBBox		 *pOtherBBox;

	if (m_pBBox == NULL) return NULL;
	vMy = GetPositionVector(m_mWorld);
	vMy2.x = vMy.x;
	vMy2.y = vMy.z;

	// �����̔��a���o�E���f�B���O�{�b�N�X����Z�o����i�O�ƉE���̑傫�������̗p�j
	fMyRadius = (m_pBBox->m_vMax.x > m_pBBox->m_vMax.z) ? m_pBBox->m_vMax.x : m_pBBox->m_vMax.z;


	// �I�u�W�F�N�g�z��̒T��
	for (DWORD i = 0; i < pProc->GetObjArrayPtr().size(); i++)
	{
		pOtherObj = pProc->GetObjArrayPtr()[i];

		if (!pOtherObj->m_bActive) continue;	// ���ݐ����Ă��Ȃ���ΑΏۊO
		if (pOtherObj == this) continue;	// �������g�͑ΏۊO
		pOtherBBox = pOtherObj->m_pBBox;
		if (pOtherBBox == NULL) continue;	// �o�E���f�B���O�{�b�N�X���Ȃ���ΑΏۊO
		vOther = GetPositionVector(pOtherObj->m_mWorld);
		vOther2.x = vOther.x;
		vOther2.y = vOther.z;

		// �o�E���f�B���O�{�b�N�X���m�̍�������v���Ă��邩�B�͈͓��ɓ����Ă��Ȃ���ΑΏۊO
		if ((vMy.y + m_pBBox->m_vMin.y) > (vOther.y + pOtherObj->m_pBBox->m_vMax.y) ||
			(vMy.y + m_pBBox->m_vMax.y) < (vOther.y + pOtherObj->m_pBBox->m_vMin.y)) {
			continue;
		}

		// ����̔��a���o�E���f�B���O�{�b�N�X����Z�o����i�O�ƉE���̑傫�������̗p�j
		fOtherRadius = (pOtherBBox->m_vMax.x > pOtherBBox->m_vMax.z) ? pOtherBBox->m_vMax.x : pOtherBBox->m_vMax.z;

		fAddRadius = fMyRadius + fOtherRadius;
		if (fabs(vMy2.x - vOther2.x) < fAddRadius && fabs(vMy2.y - vOther2.y) < fAddRadius) {		// �܂��A���t�ɐ��������i�w�y�����j�Ŕ��a�͈͓̔��ɓ����Ă��邩
			fLen = magnitude(vMy2 - vOther2);		// ���������i�w�y�����j�Ŕ��a�̋������ɓ����Ă��邩
			if (fLen < fAddRadius) {
				fLen = fAddRadius - fLen;	// �������݋����ɂ���
				if (fLen > fMvMax) {		// ���܂ł̒��ŁA��Ԑڋ߂��Ă��邩
					fMvMax = fLen;
					pTargetObj = pOtherObj;
				}
			}
		}
	}

	if (pTargetObj) {	// ���a���ɓ��������肪�����ꍇ
		vOther = GetPositionVector(pTargetObj->m_mWorld);
		vOther.y = vMy.y;
		matWk1 = GetLookatMatrix(vMy, vOther);					// ����̕�������������}�g���b�N�X���쐬����
		matWk2 = XMMatrixTranslation(0.0f, 0.0f, -fMvMax);		// �������ݒl�����A�y�����̔��Ε����Ɉړ�����}�g���b�N�X���쐬����
		matWk1 = matWk2 * matWk1;								// �������ݒl�̔��Ε����Ɉړ�����
		vMy.x = 0.0f - vMy.x;
		vMy.y = 0.0f - vMy.y;
		vMy.z = 0.0f - vMy.z;
		matWk2 = XMMatrixTranslation(vMy.x, vMy.y, vMy.z);		// �����̈ʒu�̋t���̈ʒu
		matWk2 = m_mWorld * matWk2;								// �����̌��_�ʒu�ł̊p�x�݂̂ɂ���
		vMy = GetPositionVector(matWk1);						// �������ݒl�̔��Ε����Ɉړ������ʒu
		matWk1 = XMMatrixTranslation(vMy.x, vMy.y, vMy.z);		// �������ݒl�̔��Ε����Ɉړ������ʒu�݂̂̃}�g���b�N�X
		m_mWorld = matWk2 * matWk1;								// �����̐V�����ʒu�Ɗp�x�̃��[���h�}�g���b�N�X
	}


	// ���ʂ̃v���V�[�W���z��̒T��
	if (pTargetObj == NULL)
	{
		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
		{
			pTargetObj = SetKeepOffset(pProc->GetProcArrayPtr()[i]);      // ���ʂ̃v���V�[�W���̏����i�ċA�����j
			if (pTargetObj) break;
		}
	}

	return pTargetObj;
}


//----------------------------------------------------------------------
//����̂����������
//
//	MATRIX4X4	MyWorld		�����̃��[���h�}�g���b�N�X
//	 MATRIX4X4 TargetWorld		����̃��[���h�}�g���b�N�X
//
//
//---------------------------------------------------------------------
MATRIX4X4 CBaseObj::TurnTarget(MATRIX4X4 MyWorld, MATRIX4X4 TargetWorld)
{
	VECTOR3	vRotUp;			
	VECTOR3 vTarget = GetPositionVector(TargetWorld);
	VECTOR3 vMyobj = GetPositionVector(MyWorld);
	MATRIX4X4 mTran;
	MATRIX4X4 mWorld = MyWorld;

	vTarget.y = vMyobj.y;
	vRotUp.y = GetTargetRotateVector(mWorld, vTarget).y;	//�I�u�W�F�N�g�̌������^�[�Q�b�g���������߂̊p�x
	RotRig(&m_vRotUp.y);	//�p�x�̒���

	mTran = XMMatrixRotationY(XMConvertToRadians(vRotUp.y));	//�p�x�����߂�
	mWorld = mTran * mWorld;		//�p�x��������

	return mWorld;

}

//----------------------------------------------------------------------
//	���ɍ��킹�ĉ�]����
//
//	MATRIX4X4	MyWorld		�����̃��[���h�}�g���b�N�X
//	 MATRIX4X4 TargetWorld		���ƂȂ郏�[���h�}�g���b�N�X
//	float		fSpeed		��]����X�s�[�h
//	float		fDist		���Ƃ̋���
//
//
//---------------------------------------------------------------------
MATRIX4X4 CBaseObj::RotTarget(MATRIX4X4 MyWorld, MATRIX4X4 TargetWorld, float fSpeed, float fDist)
{
	MATRIX4X4 mWorld = MyWorld;
	MATRIX4X4 mPos;
	MATRIX4X4 mRotWorld=GetRotateMatrix(mWorld);
	VECTOR3 vTarget = GetPositionVector(TargetWorld);
	MATRIX4X4 mTargetPos = XMMatrixTranslation(vTarget.x, vTarget.y, vTarget.z);
	//�I�u�W�F�N�g�����Ƃ̋������������ʒu�ɂ���
	mPos = XMMatrixTranslation(0, 0, -fDist);
	mWorld = mPos * mRotWorld*mTargetPos;
	//�I�u�W�F�N�g���ړ�������
	mPos = XMMatrixTranslation(fSpeed, 0, 0);
	mWorld = mPos * mWorld;
	//�I�u�W�F�N�g�����̕����Ɍ�����
	mWorld =TurnTarget(mWorld, TargetWorld);

	mRotWorld = GetRotateMatrix(mWorld);		//���[���h�}�g���b�N�X�̊p�x�擾
	//���Ɠ����ʒu�ɂ���
	vTarget = GetPositionVector(TargetWorld);
	mTargetPos = XMMatrixTranslation(vTarget.x, vTarget.y, vTarget.z);
	//�I�u�W�F�N�g�����Ƃ̋������������ʒu�ɂ���
	mPos = XMMatrixTranslation(0, 0, -fDist);
	mWorld = mPos * mRotWorld*mTargetPos;


	return mWorld;

}

//-----------------------------------------------------------------------------
//
//	�p�x��0�`360�ɂ���
//
//   float* fRotUp  �p�x
//
//-----------------------------------------------------------------------------
void   CBaseObj::RotRig(float* fRotUp)
{

	if (*fRotUp >= 180) *fRotUp -= 360;
	if (*fRotUp <= -180) *fRotUp += 360;

}

//-----------------------------------------------------------------------------  
//
//	��{�R���X�g���N�^�̊֐�
//
//	const int		nMaxHP		�ő�HP
//	const int		nAtc		�U����
//	VECTOR3			vMin		�o�E���f�B���O�{�b�N�X�̍ŏ��l
//	VECTOR3			vMax		�o�E���f�B���O�{�b�N�X�̍ő�l
//
//-----------------------------------------------------------------------------
void   CBaseObj::ObjBasicConstructor(const int nMaxHP, const int nAtc, VECTOR3 vMin, VECTOR3 vMax)
{
	m_bDamage = FALSE;

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                     

	m_nHp = m_nMaxHp = nMaxHP;
	m_nAtc = nAtc;


}

//-----------------------------------------------------------------------------
//
//	�I�u�W�F�N�g�𔽎˂���
//
//--M.Kamei_Point
//--Point_Reflection
//
//-----------------------------------------------------------------------------
void   CBaseObj::ObjReflection()
{

	VECTOR3 vHear = GetPositionVector(m_mWorld); // �����̍�����ʒu
	VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // �����̑O�̈ʒu

	VECTOR3 vN;
	vN = m_vHitNormal;	//���������ꏊ�̖@�����W���擾
	vN = normalize(vN);	//���K������
	vN.y = 0;	//�����͕ς��Ȃ�

	VECTOR3 vR;
	if (vHear != vHearOld) {

		VECTOR3 vL = normalize(vHear - vHearOld);	//�ړ��x�N�g���i���K���j
		vR = (2 * dot(-vL, vN)*vN) + vL;			//���˃x�N�g��

	}
	vR = vN;
	m_mWorld = GetLookatMatrix(vHear, vHear + vR);	//���[���h�}�g���b�N�X���X�V

}

//-----------------------------------------------------------------------------
//
//	�I�u�W�F�N�g�𔽎˕�����������
//
//
//-----------------------------------------------------------------------------
MATRIX4X4   CBaseProc::ObjReflectionStart(CBaseObj* mMyObj, CBaseObj* mHitObj)
{
	MATRIX4X4 mLay;
	VECTOR3 vHear = GetPositionVector(mMyObj->GetWorld()); // �����̍�����ʒu
	VECTOR3 vHearOld = GetPositionVector(mMyObj->GetWorldOld()); // �����̑O�̈ʒu

	VECTOR3 vN ;

	vN = mMyObj->GetHitNormal();
	vN = normalize(vN);	//���K������
	vN.y = 0;	//�����͕ς��Ȃ�

	VECTOR3 vR;
	if (vHear != vHearOld) {

		VECTOR3 vL = normalize(vHear - vHearOld);	//�ړ��x�N�g���i���K���j
		vR = (2 * dot(-vL, vN)*vN) + vL;			//���˃x�N�g���i�����j

	}
	else {
		vR = vN;		//���˃x�N�g��
	}

	mLay = GetLookatMatrix(vHear, vHear + vR);	//���[���h�}�g���b�N�X���X�V

	return mLay;
}


//-----------------------------------------------------------------------------
//
//	�o�����Ɏl�����̑I�����������
//
//	DWORD		dPosStatus		�ʒu�̎l�����̂ǂꂩ
//	MATRIX4X4	*m_mWorld		���[���h�}�g���b�N�X
//
//
//-----------------------------------------------------------------------------
void   CBaseObj::ObjAppearanceDirection(DWORD dPosStatus, MATRIX4X4 *m_mWorld)
{
	MATRIX4X4 mTran;
	MATRIX4X4 mWorld = *m_mWorld;

	switch (dPosStatus)
	{
	case FRONT:
		mTran = XMMatrixRotationY(XMConvertToRadians(180));
		mWorld = mTran * mWorld;

		break;

	case RIGHT:
		mTran = XMMatrixRotationY(XMConvertToRadians(-90));
		mWorld = mTran * mWorld;

		break;
	case BACK:
		mTran = XMMatrixRotationY(XMConvertToRadians(0));
		mWorld = mTran * mWorld;

		break;
	case LEFT:
		mTran = XMMatrixRotationY(XMConvertToRadians(90));
		mWorld = mTran * mWorld;

		break;
	}

	*m_mWorld = mWorld;
}

//-----------------------------------------------------------------------------
//
//	�I�u�W�F�N�g�̍폜�̊�{����
//
//-----------------------------------------------------------------------------
void   CBaseObj::ObjBasicDelete()
{
	m_bActive = FALSE;
	m_nHp = m_nMaxHp;
	m_dwStatus = NORMAL;
	m_dwStatusSub = ATTACKNONE;
	m_dwStatusPhase = 0;
}

//-----------------------------------------------------------------------------
//
//	�I�u�W�F�N�g�̉���
//
//	VECTOR3		vMin		�ʒu�̍ŏ��l
//	VECTOR3		vMax		�ʒu�̍ő�l
//
//
//-----------------------------------------------------------------------------
void   CBaseObj::ObjRoundTrip(VECTOR3 vMin,VECTOR3 vMax)
{
	VECTOR3 vObjPos;
	vObjPos = GetPositionVector(m_mWorld);
	if (vObjPos.x < vMin.x) {
		m_vPosUp.x = m_vPosUp.x*(-1);
	}
	else if (vObjPos.x >vMax.x) {
		m_vPosUp.x = m_vPosUp.x*(-1);

	}
	else if (vObjPos.z < vMin.z) {
		m_vPosUp.x = m_vPosUp.x*(-1);

	}
	else if (vObjPos.z > vMax.z) {
		m_vPosUp.x = m_vPosUp.x*(-1);

	}
}

//-----------------------------------------------------------------------------
//
// �i�r�Q�[�V�����}�b�v�ɏ]���Ĕ���������
//
//	VECTOR3		vMin		�i�r�Q�[�V�����}�b�v�̍ŏ��l
//	VECTOR3		vMax		�i�r�Q�[�V�����}�b�v�̍ő�l
//
//-----------------------------------------------------------------------------
void   CBaseObj::ObjNavOccurrence(VECTOR3 vMin, VECTOR3 vMax)
{
	m_mWorld = XMMatrixTranslation((float)Random(vMin.x, vMax.x),
		vMax.y, (float)Random(vMin.z, vMax.z));
	m_mWorldOld = m_mWorld;

}
