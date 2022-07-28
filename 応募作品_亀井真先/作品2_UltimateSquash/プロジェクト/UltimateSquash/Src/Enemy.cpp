//=============================================================================
//
//		�G�L�����N�^�[�̏���
//																Enemy.cpp
//=============================================================================
#include  "Enemy.h"
#include  "Playchar.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"
#include  "BackFore.h"


//============================================================================
//
// �G���C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmProc::CEnmProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pGMain = pGMain;

	m_pEnmBallProc = new CEnmBallProc(m_pGMain);					// �G�{�[���̐���
	m_pProcArray.push_back(m_pEnmBallProc);							// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmTargetProc = new CEnmTargetProc(m_pGMain);				// �G�I�̐���
	m_pProcArray.push_back(m_pEnmTargetProc);						// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmMoveTargetProc = new CEnmMoveTargetProc(m_pGMain);        // �G�����I�̐���
	m_pProcArray.push_back(m_pEnmMoveTargetProc);					// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmShieldProc = new CEnmShieldProc(m_pGMain);				// �G�V�[���h�̐���
	m_pProcArray.push_back(m_pEnmShieldProc);						// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmWallProc = new CEnmWallProc(m_pGMain);					// �G�ǂ̐���
	m_pProcArray.push_back(m_pEnmWallProc);							// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmBallBoomProc = new CEnmBallBoomProc(m_pGMain);			// ���e�{�[���̐���
	m_pProcArray.push_back(m_pEnmBallBoomProc);						// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmBendProc = new CEnmBendProc(m_pGMain);					// �G�Ȃ���̐���
	m_pProcArray.push_back(m_pEnmBendProc);							// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmTargetSkillProc = new CEnmTargetSkillProc(m_pGMain);      // �G�I�̐���
	m_pProcArray.push_back(m_pEnmTargetSkillProc);					// �v���V�[�W�����v���V�[�W���z��ɓo�^����

}
//============================================================================
// �G�v���V�[�W���̍X�V
//
//�@�G�̐��𐔂��A�O�ɂȂ�����Q�[���N�����[�ɂ���
//
//   �����@�@�@�Ȃ�
//============================================================================
void	CEnmProc::Update()
{


}
//============================================================================
//
// �S�Ă̓G�v���V�[�W���̔������������l�Ƀ��Z�b�g����
// �i�ő唭����(m_nMaxNum)�𔭐���m_nNum�ɐݒ肷��
//
// ����    CBaseProc* pProc  �ΏۂƂ���v���V�[�W���B�ȗ��l��NULL
//                           NULL�̎��͎��v���V�[�W��
// �߂�l  �Ȃ�
// ---------------------------------------------------------------------------
void CEnmProc::ResetEnmNum(CBaseProc* pProc)
{
	if (pProc)   // �ΏۂƂ���v���V�[�W��
	{
		pProc->SetMaxNum();  // �ő唭����(m_nMaxNum)�𔭐���m_nNum�ɐݒ肷��

		// ���ʂ̃v���V�[�W����T�����Ă���
		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
		{
			ResetEnmNum(pProc->GetProcArrayPtr()[i]);  // �ċA�Ăяo��
		}
	}
	else {   // ���v���V�[�W��
		SetMaxNum();  // �ő唭����(m_nMaxNum)�𔭐���m_nNum�ɐݒ肷��

		// ���ʂ̃v���V�[�W����T�����Ă���
		for (DWORD i = 0; i < m_pProcArray.size(); i++)
		{
			ResetEnmNum(m_pProcArray[i]);  // �ċA�Ăяo��
		}
	}
}

//============================================================================
//
// �S�Ă̓G�I�u�W�F�N�g�̎c���Ă���G�̐��𐔂��鏈��
// �i�c���Ă���G�̐��Ƃ́A�܂��������Ă��Ȃ���(m_nNum�̒l)�{���ݐ����Ă��鐔�̂��Ƃł���j
//
// ����    CBaseProc* pProc  �ΏۂƂ���v���V�[�W���BNULL�̎��͎��v���V�[�W���B�ȗ��l��NULL
//         int        nNum   ��ʂ̃v���V�[�W������^����ꂽ�G�̐��B�ȗ��l��0
//
// �߂�l  int �c���Ă���G�̐�
// ---------------------------------------------------------------------------
int CEnmProc::CountActiveEnm(CBaseProc* pProc, int nNum)
{

	if (pProc)   // �ΏۂƂ���v���V�[�W��
	{
		nNum += pProc->GetNum();									// �v���V�[�W�����Ɏc���Ă���G�̐��i�܂��������Ă��Ȃ����j
		for (DWORD j = 0; j < pProc->GetObjArrayPtr().size(); j++)
		{
			if (pProc->GetObjArrayPtr()[j]->GetActive()) nNum++;	// �I�u�W�F�N�g���ɂ��łɔ������Ă���G�̐��i���ݐ����Ă��鐔�j
		}

		// ���ʂ̃v���V�[�W����T�����Ă���
		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
		{
			nNum = CountActiveEnm(pProc->GetProcArrayPtr()[i], nNum);  // �ċA�Ăяo��
		}
	}
	else {   // ���v���V�[�W��
		nNum += GetNum();											// �v���V�[�W�����Ɏc���Ă���G�̐��i�܂��������Ă��Ȃ����j
		for (DWORD j = 0; j < m_pObjArray.size(); j++)
		{
			if (m_pObjArray[j]->GetActive()) nNum++;				// �I�u�W�F�N�g���ɂ��łɔ������Ă���G�̐��i���ݐ����Ă��鐔�j
		}

		// ���ʂ̃v���V�[�W����T�����Ă���
		for (DWORD i = 0; i < m_pProcArray.size(); i++)
		{
			nNum = CountActiveEnm(m_pProcArray[i], nNum);  // �ċA�Ăяo��
		}
	}

	return nNum;
}

//============================================================================    
//   
//	�v���V�[�W���ƃI�u�W�F�N�g��T�����A���ݐ����Ă���S�ẴI�u�W�F�N�g�̏��𓾂�
//   
//	�����@	std::vector<CBaseObj*> &ActiveObjArray  :  �ΏۃI�u�W�F�N�g�A�h���X��ݒ肷��z��
//
//	�߂�l  �Ȃ�
//============================================================================
void  CEnmProc::GetActiveEnm(std::vector<CBaseObj*> &ActiveObjArray)
{

	// �I�u�W�F�N�g�|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (m_pObjArray[i]->GetActive())  // ���ݐ����Ă���I�u�W�F�N�g��
		{
			ActiveObjArray.push_back(m_pObjArray[i]);    // �I�u�W�F�N�g�̃A�h���X��z��ɒǉ�����
		}
	}

	// ���ʂ̃v���V�[�W���|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		((CEnmProc*)m_pProcArray[i])->GetActiveEnm(ActiveObjArray);      // ���ʂ̃v���V�[�W���̏����i�ċA�����j
	}
}

//============================================================================   
//   
//	�v���V�[�W���ƃI�u�W�F�N�g��T�����A���ݐ����Ă���S�ẴI�u�W�F�N�g�̏��𓾂�
//   
//	�����@	std::vector<CBaseObj*> &ActiveObjArray  :  �ΏۃI�u�W�F�N�g�A�h���X��ݒ肷��z��
//
//	�߂�l  �Ȃ�
//============================================================================
void  CEnmProc::GetActiveEnmMulti(std::vector<CBaseObj*> &ActiveObjArray, DWORD dwPlayerNo)
{

	// �I�u�W�F�N�g�|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {
			if (m_pObjArray[i]->GetActive())  // ���ݐ����Ă���I�u�W�F�N�g��
			{
				ActiveObjArray.push_back(m_pObjArray[i]);    // �I�u�W�F�N�g�̃A�h���X��z��ɒǉ�����
			}
		}
	}

	// ���ʂ̃v���V�[�W���|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		((CEnmProc*)m_pProcArray[i])->GetActiveEnmMulti(ActiveObjArray, dwPlayerNo);      // ���ʂ̃v���V�[�W���̏����i�ċA�����j
	}
}


// =====================================================================================================
// 
// �e�G�v���V�[�W�����̏���
// 
// =====================================================================================================


//============================================================================   
//
// �GBall�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmBallProc::CEnmBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_BALL_WAITMAX;      // �G����������܂ł̑҂�����
	m_dwProcID = ENM_BALL_ID;                // �GBall��ID
	m_nNum = m_nMaxNum = ENM_BALL_ALLMAX;    // �GBall�̍ő�o����
	m_fSpeed = ENM_BALL_SPEED;
	m_dwKinds = BALL;
	bPcBoolSkill = FALSE;					 //�v���C���[�PP�X�L�̃g���K�[������
	bPcSecBoolSkill = FALSE;				 //�v���C���[�QP�X�L�̃g���K�[������

	// Fbx�X�L�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark_Pro.mesh"));   // �e�̃X�^�e�B�b�N���b�V��
	for (int i = 0; i < (ENM_BALL_MAX * 2); i++)
	{
			m_pObjArray.push_back(new CEnmBallObj(m_pGMain));				// m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
			m_pObjArray[i]->SetObjID(m_dwProcID);							//ID�̎擾
			m_pObjArray[i]->SetObjNo(i);									//No�擾
			((CEnmBallObj*)m_pObjArray[i])->SetMesh(this);					// ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��  
			if (i < ENM_BALL_MAX)((CEnmBallObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
			else if (i >= ENM_BALL_MAX)((CEnmBallObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);	
	}
	//�o���^�C���̐ݒ�
	m_nWaitTime = m_nMaxwaitTime = nWait;
	m_nWaitTimeSec = nWait;	
	//�ł��Ԃ��ꂽ�Ƃ����̏����l
	dwHitNum = 0;
}


//============================================================================   
//
// �GBall�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmBallProc::~CEnmBallProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================  
//
// �GBall�I�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CGameMain* pGMain;		// �Q�[�����C���N���X�ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CEnmBallObj::CEnmBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	VECTOR3 vMin(ENM_BALL_BBOX_MIN);
	VECTOR3 vMax(ENM_BALL_BBOX_MAX);

	ObjBasicConstructor(0, 0, vMin, vMax);

	m_vDiffuse = VECTOR4(ENM_BALL_COLOR);
	m_vTarget = GetPositionVector(m_mWorld);

	bPcBoolSkill = FALSE;

}
// ---------------------------------------------------------------------------    
//
// �GBall�I�u�W�F�N�g�̃f�X�g���N�^
//
//   �Ȃ��ACBBox��delete��CBaseObj�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmBallObj::~CEnmBallObj()
{
	;
}
// ---------------------------------------------------------------------------   
//
// �GBall�I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CEnmBallProc* pProc
//
// ---------------------------------------------------------------------------  
void CEnmBallObj::SetMesh(CEnmBallProc* pProc)
{
	//m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark_Pro.mesh"));				
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^
	m_fSpeed = pProc->GetSpeed();

}

// ---------------------------------------------------------------------------
// �GBall�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmBallProc::Update()
{
	UpdateNav();
}
// ---------------------------------------------------------------------------  
// �GBall�v���V�[�W���̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmBallProc::UpdateNav()
{

	std::vector<DWORD> Nav;   // �I���i�r�}�b�v

	BOOL	SkillActivity = FALSE;

	//�{�[���̃X�L����������		
	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			if (m_nWaitTime <= 0)
			{
				// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
				int k = Random(0, Nav.size() - 1);
				int no = Nav[k];
				for (DWORD i = 0; i < ENM_BALL_MAX; i++)
				{
					if (!m_pObjArray[i]->GetActive())
					{
						((CEnmBallObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
						((CEnmBallObj*)m_pObjArray[i])->SetPcBoolSkill(FALSE);
						if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetBoolSkillTrigger() == TRUE)((CEnmBallObj*)m_pObjArray[i])->SetPcBoolSkill(TRUE);	// �X�L��������	
						m_pObjArray[i]->Start();	// �G�𔭐�������
						m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
						SetMaxWaitTime();
						break;
					}
				}
			}
		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}



}

// ---------------------------------------------------------------------------   
// �GBall�v���V�[�W���}���`�̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmBallProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);
}

// ---------------------------------------------------------------------------    
// �GBall�v���V�[�W���}���`�̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmBallProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{


	BOOL	SkillActivity = FALSE;
	BOOL	SecSkillActivity = FALSE;

	
	//�{�[���̃X�L����������	

	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			//�v���C���[�P�̂Ƃ�
			if (m_dwPlayerNo == FIRSTPLAYER) {

				if (m_nWaitTime <= 0)
				{
					// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_BALL_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmBallObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
							((CEnmBallObj*)m_pObjArray[i])->SetPcBoolSkill(FALSE);							//�X�L��������
							if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetBoolSkillTrigger() == TRUE)((CEnmBallObj*)m_pObjArray[i])->SetPcBoolSkill(TRUE);	// �X�L��������		
							m_pObjArray[i]->Start();	// �G�𔭐�������
							m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
							SetMaxWaitTime();
							break;
						}

					}
				}
			}
			//�v���C���[�Q�̂Ƃ�
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_nWaitTimeSec <= 0)
				{
					// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = ENM_BALL_MAX; i < (ENM_BALL_MAX * 2); i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmBallObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
							((CEnmBallObj*)m_pObjArray[i])->SetPcBoolSkill(FALSE);							//�X�L��������
							if (m_pGMain->m_pPcProc->GetPcSecObjPtr()->GetBoolSkillTrigger() == TRUE)((CEnmBallObj*)m_pObjArray[i])->SetPcBoolSkill(TRUE);	// �X�L��������		
							m_pObjArray[i]->Start();	// �G�𔭐�������
							m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
							SetMaxWaitTimeSec();
							break;

						}

					}
				}
			}
			

		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}



}

// ---------------------------------------------------------------------------
// �GBall�v���V�[�W���̃i�r�Q�[�V�����}�b�v�o�^
//
//
// ---------------------------------------------------------------------------
void CEnmBallProc::NavSet()
{

	Nav.clear();
	Nav.shrink_to_fit();
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}


// --------------------------------------------------------------------------- 
//
// �GBall�I�u�W�F�N�g�̔���
//
//
// ---------------------------------------------------------------------------
BOOL CEnmBallObj::Start()
{

	m_bActive = TRUE;	// �GBall�I�u�W�F�N�g
	m_bDamage = FALSE;
	MATRIX4X4 mYaw;
	VECTOR3 m_vTarget;
	const float SkillRanMinPosx = -2;						//�X�L�������������Ƃ��̃����_���ŏ��ʒuX���W
	const float SkillRanMaxPosx = 2;						//�X�L�������������Ƃ��̃����_���ő�ʒuY���W
	const float SkillRanMinPosz = 11;						//�X�L�������������Ƃ��̃����_���ŏ��ʒuZ���W
	const float SkillRanMaxPosz = 13;						//�X�L�������������Ƃ��̃����_���ő�ʒuZ���W
	VECTOR2 vSkillImageSize = VECTOR2(1.5,1.5);				//�X�L���������̃G�i�W�[�f�B�X�N�̃T�C�Y
	VECTOR2 vSkillImageSrcPos = VECTOR2(0,0);				//�X�L���������̃G�i�W�[�f�B�X�N�p�^�[���ʒu
	VECTOR2 vSkillImageSrcSize = VECTOR2(400, 400);			//�X�L���������̃G�i�W�[�f�B�X�N�p�^�[���̃T�C�Y
	const float SkillImageFreamEnd = 180;					//�X�L���������̃G�i�W�[�f�B�X�N�̕\������

	VECTOR2 vSkillLESize = VECTOR2(2.5,1.0);				//�X�L���������̋[���G�t�F�N�g�̃T�C�Y
	VECTOR2 vSkillLESrcPos = VECTOR2(294, 384);				//�X�L���������̋[���G�t�F�N�g�̃p�^�[���ʒu
	VECTOR2 vSkillLESrcSize = VECTOR2(147, 46);				//�X�L���������̋[���G�t�F�N�g�̃p�^�[���T�C�Y
	const float vSkillLEFreamEnd = 60;						//�X�L���������̋[���G�t�F�N�g�̕\������

// �i�r�Q�[�V�����}�b�v�ɏ]���Ĕ���������	
	if (bPcBoolSkill != TRUE) {
		ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
		m_vTarget = VECTOR3((float)Random(m_Nav.vMin.x, m_Nav.vMax.x), m_Nav.vMax.y,
			(float)Random(m_Nav.vMin.z, m_Nav.vMax.z));
		m_pBBox->m_mWorld = m_mWorld;                
	}
	else {
		//�{�[���X�L�����������Ȃ�
		//�J�����̕�������o��������
		VECTOR3	 vPcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
		MATRIX4X4	mStartRot = GetRotateMatrixY(m_pGMain->m_pCameraProc->GetCameraObjPtr()->GetWorld());
		if (m_dwPlayerNo == SECONDPLAYER) {
			vPcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcSecObjPtr()->GetWorld());
			mStartRot = GetRotateMatrixY(m_pGMain->m_pCameraProc->GetCameraSecondObjPtr()->GetWorld());
		}
		MATRIX4X4	mStartPos = XMMatrixTranslation((float)Random(SkillRanMinPosx, SkillRanMaxPosx), m_Nav.vMax.y, (float)Random(SkillRanMinPosz, SkillRanMaxPosz));
		m_mWorld = mStartPos * mStartRot*XMMatrixTranslation(vPcPos.x,0, vPcPos.z);
		m_mWorldOld = m_mWorld;
		m_pBBox->m_mWorld = m_mWorld;                     
		VECTOR3	vPosStart = GetPositionVector(m_mWorld);
		m_pGMain->m_pEffectProc->m_pEnergyDiskProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), this, vPosStart, vSkillImageSize, vSkillImageSrcPos, vSkillImageSrcSize, SkillImageFreamEnd, m_dwPlayerNo, 0);
		vPosStart.y += 1;
		m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), vPosStart, vSkillLESize, vSkillLESrcPos, vSkillLESrcSize, vSkillLEFreamEnd, m_dwPlayerNo,LENO_EXPANISIONTYPE,1.0);	

	}
	m_dwStatus = NORMAL;
	m_dwStatusSub = ATTACKNONE;
	m_dwStatusPhase = 0;



	//�v���C���[�̕���������
	VECTOR3 vBall = GetPositionVector(m_mWorld);
	VECTOR3 m_vPcTarget;
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	if (m_dwPlayerNo == FIRSTPLAYER)	{
		m_vPcTarget = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetLocalMatrix());
		pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();

	}
	if (m_dwPlayerNo == SECONDPLAYER) { 
		m_vPcTarget = GetPositionVector(m_pGMain->m_pPcProc->GetPcSecObjPtr()->GetLocalMatrix()); 
		pPcObj = m_pGMain->m_pPcProc->GetPcSecObjPtr();

	}
	m_vDiffuse = VECTOR4(1, 1, 1, 1);				
	m_fDist = 0;
	bShaftObjTrigger = FALSE;
	m_vPcTarget = GetPositionVector(pPcObj->GetWorld());
	m_vPcTarget.y = vBall.y;
	m_vRotUp.y = GetTargetRotateVector(m_mWorld, m_vPcTarget).y;
	RotRig(&m_vRotUp.y);
	mYaw = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));
	m_mWorld =  mYaw * m_mWorld ;
	m_pBBox->m_mWorld = m_mWorld;


	return TRUE;

}

//-----------------------------------------------------------------------------   
//
//�@�L�[�{�[�h�œG�𓮂���
//�@�G�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ϊ��A�}�b�v�Ƃ̐ڐG����
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmBallObj::Update()
{
	if (!m_bActive) return;  // ��\���̂Ƃ��͏��������Ȃ�

	// �ϐ��̏�����   ---------------------------------------
	m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // ��O�̈ʒu

	// �X�e�[�^�X���Ƃ̏���  --------------------------------
	switch (m_dwStatus)
	{
	case  FLASH: // �G���_���[�W���畜�A�����Ƃ��̏����Bbreak�������Ɏ���NORMAL���s���B
	case  NORMAL: // �G���ʏ��Ԃ̂Ƃ��̏���
		UpdateNormal();
		break;

	case  DAMAGE: // �G���_���[�W��Ԃ̂Ƃ��̏���
		UpdateDamage();
		break;

	case  DEAD:	// �G�����S��Ԃ̂Ƃ��̏���
		UpdateDead();
		break;
	}


	if (m_pGMain->m_pMapProc->isCollisionMove(&m_mWorld, m_mWorldOld, m_pBBox->m_vMax.x))  // �}�b�v�R���W����
	{
		// �ǂɂԂ������Ƃ��폜����
		ObjBasicDelete();
	}

	// �{�[���̍폜����
	// ���_����P�O�O�����z������폜
	VECTOR3 vNowPos = GetPositionVector(m_mWorld);
	if (vNowPos.x < -100 || vNowPos.x > 100 || vNowPos.y < -100 || vNowPos.y > 100 || vNowPos.z < -100 || vNowPos.z > 100)
	{
		ObjBasicDelete();
	}

	// �`�揈��  --------------------------------------------
	m_pMesh->m_vDiffuse = m_vDiffuse;		
	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if(m_dwPlayerNo==FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}
	// �o�E���f�B���O�{�b�N�X
	m_pBBox->m_mWorld = m_mWorld;

}

//----------------------------------------------------------------------------- 
// �GBall�I�u�W�F�N�g�̐���
//
// �G���ʏ��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmBallObj::UpdateNormal()
{

	const float fNormalSpeed = 0.07f;                                    // �ړ��X�s�[�h
	MATRIX4X4 mPos;
	DWORD	EnmProcSize = m_pGMain->m_pEnmProc->GetProcArrayPtr().size();
	const float GravityDist = 3.0f;				//���苗��
	const float GravityRotateSpeed = 0.5f;		//�����]���̃X�s�[�h

	if (m_dwStatus == FLASH)m_dwStatus = NORMAL;

	ConditionsDelete();

	// �X�e�[�^�X���Ƃ̏���  -----------------------------------------

	if (bShaftObjTrigger == TRUE) {			//��]�{�[���͈͓̔��Ȃ�
		m_bDamage = TRUE;
		m_vDiffuse = VECTOR4(0, 255, 255, 1);			
		MATRIX4X4	mWorld = RotTarget(m_mWorld, m_pShaftObj->GetWorld(), fNormalSpeed*1.5, m_fShaftDist);
		m_mWorld = mWorld;
	}
	else {
		mPos = XMMatrixTranslation(0, 0, fNormalSpeed);    // ���i�����̂�
		m_mWorld = mPos * m_mWorld;
	}

	if (m_bDamage == TRUE) {		//�q�b�g��Ԃ̎��̏���
		for (int i = 0; i < EnmProcSize; i++) {
			//�I�ɓ���������
			if (m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->GetKinds() == TARGET) {
				if (m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {
					ObjBasicDelete();
				}
				//�{�[���̊p�x�̕␳
				if (bShaftObjTrigger != TRUE) {
					if (m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->GetProcID() == ENM_TARGETSKILL_ID)
					{
						m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->ObjGravityMulti(this, GravityDist + 2, GravityRotateSpeed, m_dwPlayerNo);
					}
					else
						m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->ObjGravityMulti(this, GravityDist, GravityRotateSpeed, m_dwPlayerNo);
				}
			}
		}

	}


}

//-----------------------------------------------------------------------------    
// �GBall�I�u�W�F�N�g�̐���
//
// �G���_���[�W��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmBallObj::UpdateDamage()
{
	if (m_bDamage != TRUE) {
		if (m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetProcID() == m_pHitObj->GetObjID()) {

			ObjReflection();
			m_bDamage = TRUE;
			m_pGMain->m_pEffectProc->m_pShockWaveProc->Start(m_vHitPos,m_dwPlayerNo);	// �p�[�e�B�N���̔���

			m_pGMain->m_pEnmProc->m_pEnmBallProc->AddHitNum(1);	
		}
	}
	m_vDiffuse = VECTOR4(1, 0, 0, 1);		

	//�A�j���[�V�����g���K�[�ɉ����Ċp�x��ς���	
	m_dwStatus = NORMAL;


}
//----------------------------------------------------------------------------- 
// �GBall�I�u�W�F�N�g�̐���
//
// �G�����S��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmBallObj::UpdateDead()
{
	ObjBasicDelete();
}
//----------------------------------------------------------------------------- 
// �GBall�I�u�W�F�N�g�̐���
//
// �폜�̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmBallObj::ConditionsDelete()
{
	//�ǂƂ̓����蔻��
	if (m_pGMain->m_pWeaponProc->m_pWeaponWallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {

		m_pHitObj->SetStatus(NORMAL);
		ObjBasicDelete();
		m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���
	}

	//�����ɓ�����ƃ{�[��������
	if (m_pGMain->m_pEffectProc->m_pBillProc->Hitcheck(this, m_pBBox)) {
		if (m_pHitObj->GetDamage() != TRUE) {
			ObjBasicDelete();
		}
		else {
			m_dwStatus = NORMAL;
		}
	}

}


//============================================================================    
//
// �G�I�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmTargetProc::CEnmTargetProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_TARGET_WAITMAX;                   // �G����������܂ł̑҂�����
	m_dwProcID = ENM_TARGET_ID;                // �G�I��ID
	m_nNum = m_nMaxNum = ENM_TARGET_ALLMAX;    // �G�I�̍ő�o����
	m_dwKinds = TARGET;

	// Fbx�X�L�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy_Target.mesh"));   // �e�̃X�^�e�B�b�N���b�V��
	
	for (int i = 0; i < (ENM_TARGET_MAX*2); i++)
	{
			m_pObjArray.push_back(new CEnmTargetObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
			m_pObjArray[i]->SetObjID(m_dwProcID);
			m_pObjArray[i]->SetObjNo(i);
			((CEnmTargetObj*)m_pObjArray[i])->SetMesh(this);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷�� 
			if (i < ENM_TARGET_MAX)((CEnmTargetObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
			else if (i >= ENM_TARGET_MAX)((CEnmTargetObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);

	}


	m_dwBreakNum = 0;
	m_nWaitTime = m_nMaxwaitTime = nWait;
	m_nWaitTimeSec = nWait;	
	
}



//============================================================================   
//
// �G�I�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmTargetProc::~CEnmTargetProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================  
//
// �G�I�I�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CGameMain* pGMain;		// �Q�[�����C���N���X�ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CEnmTargetObj::CEnmTargetObj(CGameMain* pGMain) : CBaseObj(pGMain)
{

	m_dwScorePoint = ENM_TARGET_POINT;

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	VECTOR3 vMin(ENM_TARGET_BBOX_MIN);
	VECTOR3 vMax(ENM_TARGET_BBOX_MAX);
	ObjBasicConstructor(0, 0, vMin, vMax);

	m_vTarget = GetPositionVector(m_mWorld);

}
// ---------------------------------------------------------------------------  
//
// �G�I�I�u�W�F�N�g�̃f�X�g���N�^
//
//   �Ȃ��ACBBox��delete��CBaseObj�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmTargetObj::~CEnmTargetObj()
{
	;
}
// ---------------------------------------------------------------------------   
//
// �G�I�I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CEnmTargetProc* pProc
//
// ---------------------------------------------------------------------------  
void CEnmTargetObj::SetMesh(CEnmTargetProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^
}

// ---------------------------------------------------------------------------  
//
// �G�I�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmTargetProc::Update()
{
	UpdateNav();
}

// ---------------------------------------------------------------------------   
// �G�I�v���V�[�W���̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmTargetProc::UpdateNav()
{
	std::vector<DWORD> Nav;   // �I���i�r�}�b�v



	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			if (m_nWaitTime <= 0)
			{
				// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
				int k = Random(0, Nav.size() - 1);
				int no = Nav[k];
				for (DWORD i = 0; i < ENM_TARGET_MAX; i++)
				{
					if (!m_pObjArray[i]->GetActive())
					{
						((CEnmTargetObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
						m_pObjArray[i]->Start();	// �G�𔭐�������
						m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
						SetMaxWaitTime();
						break;
					}
				}
			}
		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}

}

// ---------------------------------------------------------------------------  
//
// �G�I�v���V�[�W���}���`�̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmTargetProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);
}


// ---------------------------------------------------------------------------   
// �G�I�v���V�[�W���}���`�̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmTargetProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{

	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			if (m_dwPlayerNo == FIRSTPLAYER) {

				if (m_nWaitTime <= 0)
				{
					// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_TARGET_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmTargetObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
							m_pObjArray[i]->Start();	// �G�𔭐�������
							m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
							SetMaxWaitTime();
							break;

						}

					}
				}
			}
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_nWaitTimeSec <= 0)
				{
					// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = ENM_TARGET_MAX; i < (ENM_TARGET_MAX * 2); i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmTargetObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
							m_pObjArray[i]->Start();	// �G�𔭐�������
							m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
							SetMaxWaitTimeSec();
							break;

						}

					}
				}
			}

		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}



}

// ---------------------------------------------------------------------------    
// �G�I�v���V�[�W���̃i�r�Q�[�V�����}�b�v�o�^
//
//
// ---------------------------------------------------------------------------
void CEnmTargetProc::NavSet()
{

	Nav.clear();
	Nav.shrink_to_fit();

	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}


// ---------------------------------------------------------------------------   
//
// �G�I�I�u�W�F�N�g�̔���
//
//
// ---------------------------------------------------------------------------
BOOL CEnmTargetObj::Start()
{
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	bTarget = FALSE;	

	// �i�r�Q�[�V�����}�b�v�ɏo��	
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
	m_pBBox->m_mWorld = m_mWorld;                       

	// �I�̈ʒu�����Ȃ��悤�ɂ���		

	for (DWORD i = 0; i < m_pGMain->m_pEnmProc->m_pEnmTargetProc->GetObjArrayPtr().size(); i++) {

		if (m_pGMain->m_pEnmProc->m_pEnmTargetProc->GetObjArrayPtr()[i]->GetActive() == TRUE) {		//�\������Ă���I��T��
			if (m_pGMain->m_pEnmProc->m_pEnmTargetProc->GetObjArrayPtr()[i]->GetPlayerNo() == m_dwPlayerNo) {

				if (m_pBBox->OBBCollisionDetection(m_pGMain->m_pEnmProc->m_pEnmTargetProc->GetObjArrayPtr()[i]->GetBBox(), &vHit, &vNrm)) {

						ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
						m_pBBox->m_mWorld = m_mWorld;                        
						i = 0;

				}
			}
		}	

	}

	//--�I�Œ�p
	MATRIX4X4 mTran;
	ObjAppearanceDirection(m_Nav.dPosStatus, &m_mWorld);
	m_mWorldOld = m_mWorld;
	m_pBBox->m_mWorld = m_mWorld;   

	m_bActive = TRUE;	// �G�I�I�u�W�F�N�g
	m_nHp = m_nMaxHp;



	return TRUE;

}

//-----------------------------------------------------------------------------   
// �G�I�I�u�W�F�N�g�̐���
//
//�@�L�[�{�[�h�œG�𓮂���
//�@�G�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ϊ��A�}�b�v�Ƃ̐ڐG����
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmTargetObj::Update()
{
	if (!m_bActive) return;  // ��\���̂Ƃ��͏��������Ȃ�

	// �ϐ��̏�����   ---------------------------------------
	m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // ��O�̈ʒu

	// �X�e�[�^�X���Ƃ̏���  --------------------------------
	switch (m_dwStatus)
	{
	case  FLASH: // �G���_���[�W���畜�A�����Ƃ��̏����Bbreak�������Ɏ���NORMAL���s���B
	case  NORMAL: // �G���ʏ��Ԃ̂Ƃ��̏���
		UpdateNormal();
		break;

	case  DAMAGE: // �G���_���[�W��Ԃ̂Ƃ��̏���
		UpdateDamage();
		if(m_dwPlayerNo==FIRSTPLAYER)m_pGMain->m_nScore= m_pGMain->m_nScore + m_dwScorePoint;
		if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_nScoreSec = m_pGMain->m_nScoreSec + m_dwScorePoint;

		break;

	case  DEAD:	// �G�����S��Ԃ̂Ƃ��̏���
		UpdateDead();
		break;
	}


	// �`�揈��  ---------------------------------------------
	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
	}


	// �o�E���f�B���O�{�b�N�X
	m_pBBox->m_mWorld = m_mWorld;

}

//-----------------------------------------------------------------------------    
// �G�I�I�u�W�F�N�g�̐���
//
// �G���ʏ��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmTargetObj::UpdateNormal()
{


}

//-----------------------------------------------------------------------------    
// �G�I�I�u�W�F�N�g�̐���
//
// �G���_���[�W��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmTargetObj::UpdateDamage()
{
	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���
	m_dwStatus = DEAD;		// HP���O�Ȃ̂Ŏ��S��


}
//-----------------------------------------------------------------------------   
// �G�I�I�u�W�F�N�g�̐���
//
// �G�����S��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CEnmTargetObj::UpdateDead()
{
	ObjBasicDelete();
	if(m_dwPlayerNo==FIRSTPLAYER)m_pGMain->m_pEnmProc->m_pEnmTargetProc->SetMaxWaitTime();
	if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_pEnmProc->m_pEnmTargetProc->SetMaxWaitTimeSec();
	m_pGMain->m_pEnmProc->m_pEnmTargetProc->AddBreakNum(1);		

}

//============================================================================   
//
//  �G�����I�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmMoveTargetProc::CEnmMoveTargetProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_MOVETARGET_WAITMAX;                   // �G����������܂ł̑҂�����
	m_dwProcID = ENM_MOVETARGET_ID;                //  �G�����I��ID
	m_nNum = m_nMaxNum =  ENM_MOVETARGET_ALLMAX;    //  �G�����I�̍ő�o����
	m_dwKinds = TARGET;

	// Fbx�X�L�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy_Target_Ver2.mesh"));   // �e�̃X�^�e�B�b�N���b�V��

	for (int i = 0; i < (ENM_MOVETARGET_MAX*2); i++)
	{
			m_pObjArray.push_back(new CEnmMoveTargetObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
			m_pObjArray[i]->SetObjID(m_dwProcID);
			m_pObjArray[i]->SetObjNo(i);
			((CEnmMoveTargetObj*)m_pObjArray[i])->SetMesh(this);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷�� 
			if (i < ENM_MOVETARGET_MAX)((CEnmMoveTargetObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
			else if (i >= ENM_MOVETARGET_MAX)((CEnmMoveTargetObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);

	}

	m_nWaitTime = m_nMaxwaitTime = nWait;
	m_nWaitTimeSec = nWait;		

	m_dwBreakNum = 0;

}



//============================================================================  
//
//  �G�����I�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmMoveTargetProc::~CEnmMoveTargetProc()
{
	SAFE_DELETE(m_pMesh);
}

//============================================================================  
//
// �G�����I�I�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CGameMain* pGMain;		// �Q�[�����C���N���X�ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CEnmMoveTargetObj::CEnmMoveTargetObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_dwScorePoint = ENM_MOVETARGET_POINT;

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	VECTOR3 vMin(ENM_MOVETARGET_BBOX_MIN);
	VECTOR3 vMax(ENM_MOVETARGET_BBOX_MAX);
	ObjBasicConstructor(0, 0, vMin, vMax);
	m_vTarget = GetPositionVector(m_mWorld);

}

// ---------------------------------------------------------------------------   
//
// �G�����I�I�u�W�F�N�g�̃f�X�g���N�^
//
//   �Ȃ��ACBBox��delete��CBaseObj�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmMoveTargetObj::~CEnmMoveTargetObj()
{
	;
}
// ---------------------------------------------------------------------------   
//
// �G�����I�I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CEnmMoveTargetProc* pProc
//
// --------------------------------------------------------------------------- 
void CEnmMoveTargetObj::SetMesh(CEnmMoveTargetProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^
}

// ---------------------------------------------------------------------------  
// �G�����I�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmMoveTargetProc::Update()
{
	UpdateNav();

}


// ---------------------------------------------------------------------------   
//
//  �G�����I�v���V�[�W���̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmMoveTargetProc::UpdateNav()
{
	std::vector<DWORD> Nav;   // �I���i�r�}�b�v

	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if ( m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			if (m_nWaitTime <= 0)
			{
				// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
				int k = Random(0, Nav.size() - 1);
				int no = Nav[k];
				for (DWORD i = 0; i < ENM_MOVETARGET_MAX; i++)
				{
					if (!m_pObjArray[i]->GetActive())
					{
						((CEnmMoveTargetObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
						m_pObjArray[i]->Start();	// �G�𔭐�������
						m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
						SetMaxWaitTime();
						break;
					}
				}
			}
		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}

}

// ---------------------------------------------------------------------------   
// �G�����I�v���V�[�W���}���`�̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmMoveTargetProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);

}

// ---------------------------------------------------------------------------  
// �G�����I�v���V�[�W���}���`�̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmMoveTargetProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{

	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			if (m_dwPlayerNo == FIRSTPLAYER) {
				if (m_nWaitTime <= 0)
				{
					// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_MOVETARGET_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmMoveTargetObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
							m_pObjArray[i]->Start();	// �G�𔭐�������
							m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
							SetMaxWaitTime();
							break;

						}

					}
				}
			}
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_nWaitTimeSec <= 0)
				{
					// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = ENM_MOVETARGET_MAX; i < (ENM_MOVETARGET_MAX * 2); i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmMoveTargetObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
							m_pObjArray[i]->Start();	// �G�𔭐�������
							m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
							SetMaxWaitTimeSec();
							break;

						}

					}
				}
			}

		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}



}

// ---------------------------------------------------------------------------  
// �G�����I�v���V�[�W���̃i�r�Q�[�V�����}�b�v�o�^
//
//
// ---------------------------------------------------------------------------
void CEnmMoveTargetProc::NavSet()
{

	Nav.clear();
	Nav.shrink_to_fit();

	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}



// ---------------------------------------------------------------------------  
//
// �G�����I�I�u�W�F�N�g�̔���
//
//
// ---------------------------------------------------------------------------
BOOL CEnmMoveTargetObj::Start()
{
	int	Ran = Random(0, 3);
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	m_fLocalRotY = 0.0;

	int RanNum = Random(0, 1);
	if(RanNum==0)
	fMoveSpeed = ENM_MOVETARGET_SPEED;
	else
	fMoveSpeed = -ENM_MOVETARGET_SPEED;

	// �i�r�Q�[�V�����}�b�v�ɏo��	
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
	m_pBBox->m_mWorld = m_mWorld;                         

	VECTOR3 vTarget =VECTOR3(0,0,0);
	VECTOR3 vMyobj = GetPositionVector(m_mWorld);

	fDist = magnitude(vTarget - vMyobj);

	m_bActive = TRUE;	// �G�����I�I�u�W�F�N�g

	m_nHp = m_nMaxHp;

	return TRUE;

}

//-----------------------------------------------------------------------------   
// �G�����I�I�u�W�F�N�g�̐���
//
//�@�L�[�{�[�h�œG�𓮂���
//�@�G�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ϊ��A�}�b�v�Ƃ̐ڐG����
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmMoveTargetObj::Update()
{
	if (!m_bActive) return;  // ��\���̂Ƃ��͏��������Ȃ�

	// �ϐ��̏�����   ---------------------------------------
	m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // ��O�̈ʒu

	// �X�e�[�^�X���Ƃ̏���  --------------------------------
	switch (m_dwStatus)
	{
	case  FLASH: // �G���_���[�W���畜�A�����Ƃ��̏����Bbreak�������Ɏ���NORMAL���s���B
	case  NORMAL: // �G���ʏ��Ԃ̂Ƃ��̏���
		UpdateNormal();
		break;

	case  DAMAGE: // �G���_���[�W��Ԃ̂Ƃ��̏���
		UpdateDamage();
		if (m_dwPlayerNo == FIRSTPLAYER)m_pGMain->m_nScore = m_pGMain->m_nScore + m_dwScorePoint;
		if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_nScoreSec = m_pGMain->m_nScoreSec + m_dwScorePoint;
		break;

	case  DEAD:	// �G�����S��Ԃ̂Ƃ��̏���
		UpdateDead();
		break;
	}



	// �`�揈��  ---------------------------------------------
	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

	// �o�E���f�B���O�{�b�N�X
	m_pBBox->m_mWorld = m_mWorld;

}

//-----------------------------------------------------------------------------   
// �G�����I�I�u�W�F�N�g�̐���
//
// �G���ʏ��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmMoveTargetObj::UpdateNormal()
{

	MATRIX4X4 mPos;
	MATRIX4X4 mTemp;
	if (m_dwStatus == FLASH)m_dwStatus = NORMAL;

	// �}�b�v�̎�������悤�ɐݒ�----------------------------------------------------------------	
	VECTOR3 m_vBasePosWorld = GetPositionVector(m_mWorld);	//���[���h�}�g���b�N�X�̈ʒu���擾
	MATRIX4X4 m_mRotWorld = GetRotateMatrix(m_mWorld);		//���[���h�}�g���b�N�X�̊p�x�擾

		m_mWorld = XMMatrixTranslation(m_vBasePosWorld.x, m_vBasePosWorld.y, m_vBasePosWorld.z);
		MATRIX4X4 mBaseWorld = XMMatrixTranslation(0, 0, 0);
		m_mWorld = TurnTarget(m_mWorld, mBaseWorld);
		mPos = XMMatrixTranslation(fMoveSpeed, 0, 0);
		m_mWorld = mPos * m_mWorld;
		m_mWorld = TurnTarget(m_mWorld, mBaseWorld);	
		MATRIX4X4 m_mShaftRot = GetRotateMatrix(m_mWorld);		//���[���h�}�g���b�N�X�̊p�x�擾
		mPos = XMMatrixTranslation(0, m_vBasePosWorld.y, -fDist);
		m_mWorld = mPos * m_mShaftRot*mBaseWorld;



}

//-----------------------------------------------------------------------------   
// �G�����I�I�u�W�F�N�g�̐���
//
// �G���_���[�W��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmMoveTargetObj::UpdateDamage()
{
	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���
	m_dwStatus = DEAD;
}
//-----------------------------------------------------------------------------    
// �G�����I�I�u�W�F�N�g�̐���
//
// �G�����S��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmMoveTargetObj::UpdateDead()
{
	ObjBasicDelete();
	if(m_dwPlayerNo==FIRSTPLAYER)m_pGMain->m_pEnmProc->m_pEnmMoveTargetProc->SetMaxWaitTime();
	if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_pEnmProc->m_pEnmMoveTargetProc->SetMaxWaitTimeSec();

	m_pGMain->m_pEnmProc->m_pEnmMoveTargetProc->AddBreakNum(1);	



}


//============================================================================    
// �G�V�[���h�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmShieldProc::CEnmShieldProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_SHIELDT_WAITMAX;                   // �G����������܂ł̑҂�����
	m_dwProcID = ENM_SHIELD_ID;                // �G�I��ID
	m_nNum = m_nMaxNum = ENM_SHIELD_ALLMAX;    // �G�I�̍ő�o����
	m_dwKinds = TARGET;



	// Fbx�X�L�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy1.mesh"));   // �e�̃X�^�e�B�b�N���b�V��

	for (int i = 0; i < ENM_SHIELD_MAX*2; i++)
	{
		m_pObjArray.push_back(new CEnmShieldObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		m_pObjArray[i]->SetObjID(m_dwProcID);
		m_pObjArray[i]->SetObjNo(i);
		((CEnmShieldObj*)m_pObjArray[i])->SetMesh(this);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷�� 
		((CEnmShieldObj*)m_pObjArray[i])->SetArryNo(i);
		if (i < ENM_SHIELD_MAX)((CEnmShieldObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
		else if (i >= ENM_SHIELD_MAX)((CEnmShieldObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);


	}

	m_nWaitTime = m_nMaxwaitTime = nWait;


}



//============================================================================    
// �G�V�[���h�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmShieldProc::~CEnmShieldProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================    
//
// �G�V�[���h�I�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CGameMain* pGMain;		// �Q�[�����C���N���X�ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CEnmShieldObj::CEnmShieldObj(CGameMain* pGMain) : CBaseObj(pGMain)
{

	m_dwScorePoint = ENM_SHIELD_POINT;

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	VECTOR3 vMin(ENM_SHIELD_BBOX_MIN);
	VECTOR3 vMax(ENM_SHIELD_BBOX_MAX);
	ObjBasicConstructor(0, 0, vMin, vMax);
	m_vTarget = GetPositionVector(m_mWorld);

}
// ---------------------------------------------------------------------------   
// �G�V�[���h�I�u�W�F�N�g�̃f�X�g���N�^
//
//   �Ȃ��ACBBox��delete��CBaseObj�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmShieldObj::~CEnmShieldObj()
{
	;
}
// ---------------------------------------------------------------------------  
// �G�V�[���h�I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CEnmShieldProc* pProc
//
// ---------------------------------------------------------------------------  
void CEnmShieldObj::SetMesh(CEnmShieldProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^
}

// ---------------------------------------------------------------------------    
//
// �G�V�[���h�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmShieldProc::Update()
{
	UpdateNav();
}

// ---------------------------------------------------------------------------   
//
//  �G�V�[���h�v���V�[�W���̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmShieldProc::UpdateNav()
{
	std::vector<DWORD> Nav;   // �I���i�r�}�b�v

	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			if (m_pGMain->m_nScore > ENM_SHIELD_STARTPOINT) {		//�o�����邽�߂̃X�R�A

				if (m_nWaitTime <= 0)
				{
					// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_SHIELD_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmShieldObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
							m_pObjArray[i]->Start();	// �G�𔭐�������
							m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
							SetMaxWaitTime();
							break;
						}
					}
				}
			}
		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}

}

// ---------------------------------------------------------------------------  
// �G�V�[���h�v���V�[�W���}���`�̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmShieldProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);

}

// ---------------------------------------------------------------------------    
// �G�V�[���h�v���V�[�W���}���`�̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmShieldProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{
	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			if (m_dwPlayerNo == FIRSTPLAYER) {

				if (m_pGMain->m_nScore > ENM_SHIELD_STARTPOINT) {		//�o�����邽�߂̃X�R�A

					if (m_nWaitTime <= 0)
					{
						// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = 0; i < ENM_SHIELD_MAX; i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmShieldObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
								m_pObjArray[i]->Start();	// �G�𔭐�������
								m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
								SetMaxWaitTime();
								break;

							}

						}
					}
				}
			}
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_pGMain->m_nScoreSec > ENM_SHIELD_STARTPOINT) {		//�o�����邽�߂̃X�R�A

					if (m_nWaitTimeSec <= 0)
					{
						// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = ENM_SHIELD_MAX; i < (ENM_SHIELD_MAX * 2); i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmShieldObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
								m_pObjArray[i]->Start();	// �G�𔭐�������
								m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
								SetMaxWaitTimeSec();
								break;

							}

						}
					}
				}
			}

		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}



}

// ---------------------------------------------------------------------------  
// �G�V�[���h�v���V�[�W���̃i�r�Q�[�V�����}�b�v�o�^
//
//
// ---------------------------------------------------------------------------
void CEnmShieldProc::NavSet()
{

	Nav.clear();
	Nav.shrink_to_fit();

	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}



// ---------------------------------------------------------------------------    
// �G�V�[���h�I�u�W�F�N�g�̔���
//
//
// ---------------------------------------------------------------------------
BOOL CEnmShieldObj::Start()
{
	int	Ran = Random(0, 3);

	bTarget = FALSE;	

	// �i�r�Q�[�V�����}�b�v�ɏo��	
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);


	//�o���ʒu�ɉ����Ċp�x��ς���	
	ObjAppearanceDirection(m_Nav.dPosStatus, &m_mWorld);

	m_pBBox->m_mWorld = m_mWorld;                        

	ShieldAppearance(m_mWorld);



	m_bActive = TRUE;	// �G�V�[���h�I�u�W�F�N�g
	fNormalSpeed = 0.05f;
	m_vPosUp.x = fNormalSpeed;
	m_nHp = m_nMaxHp;
	return TRUE;

}

// ---------------------------------------------------------------------------  
// �G�V�[���h�I�u�W�F�N�g�̔���
//
//	MATRIX4X4	mWorld		���[���h�}�g���b�N�X
//
//
// ---------------------------------------------------------------------------
void CEnmShieldObj::ShieldAppearance(MATRIX4X4 mWorld)
{

	DWORD ShieldNum = 0;
	const float ShieldDist = 1.5f;		//�V�[���h�Ƃ̋���
	const float ShieldPos = -1.5f;
	for (DWORD i = 0; i < 4; i++)
	{
		MATRIX4X4 ShieldWorld;
		//�V�[���h���o��������
		switch (ShieldNum)
		{
		case 0:
			ShieldWorld = XMMatrixTranslation(0, 0, ShieldPos)*m_mWorld;
			ShieldNum++;
			break;
		case 1:
			ShieldWorld = XMMatrixRotationY(XMConvertToRadians(270.0f))* XMMatrixTranslation(ShieldDist, 0, 0)*m_mWorld;
			ShieldNum++;
			break;
		case 2:
			ShieldWorld = XMMatrixRotationY(XMConvertToRadians(180.0f))*XMMatrixTranslation(0, 0, ShieldDist)*m_mWorld;
			ShieldNum++;
			break;
		case 3:
			ShieldWorld = XMMatrixRotationY(XMConvertToRadians(90.0f))* XMMatrixTranslation(-ShieldDist, 0, 0)*m_mWorld;
			ShieldNum++;
			break;
		}
		m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->SetTargetNo(m_dwObjNo);
		m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->SetShieldDist(ShieldDist);
		m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Start(ShieldWorld, ENM,m_dwPlayerNo);		
	}

}


//-----------------------------------------------------------------------------   
// �G�V�[���h�I�u�W�F�N�g�̐���
//�@�L�[�{�[�h�œG�𓮂���
//�@�G�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ϊ��A�}�b�v�Ƃ̐ڐG����
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmShieldObj::Update()
{
	if (!m_bActive) return;  // ��\���̂Ƃ��͏��������Ȃ�
		// �ϐ��̏�����   ---------------------------------------
		m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
		m_mWorldOld = m_mWorld;  // ��O�̈ʒu

		// �X�e�[�^�X���Ƃ̏���  --------------------------------
		switch (m_dwStatus)
		{
		case  FLASH: // �G���_���[�W���畜�A�����Ƃ��̏����Bbreak�������Ɏ���NORMAL���s���B
		case  NORMAL: // �G���ʏ��Ԃ̂Ƃ��̏���
			UpdateNormal();
			break;

		case  DAMAGE: // �G���_���[�W��Ԃ̂Ƃ��̏���
			UpdateDamage();
			if (m_dwPlayerNo == FIRSTPLAYER)m_pGMain->m_nScore = m_pGMain->m_nScore + m_dwScorePoint;
			if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_nScoreSec = m_pGMain->m_nScoreSec + m_dwScorePoint;
			break;

		case  DEAD:	// �G�����S��Ԃ̂Ƃ��̏���
			UpdateDead();
			break;
		}

		// �}�b�v�R���W�����@�󒆈ړ��p
		// ���_����P�O�O�����z������폜
		VECTOR3 vNowPos = GetPositionVector(m_mWorld);
		if (vNowPos.x < -100 || vNowPos.x > 100 || vNowPos.y < -100 || vNowPos.y > 100 || vNowPos.z < -100 || vNowPos.z > 100)
		{
			m_dwStatus = DEAD;		// HP���O�Ȃ̂Ŏ��S��

		}

		// �`�揈��  ---------------------------------------------
		//��ʊO�Ȃ�`�悵�Ȃ�
		VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
		if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
			if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
		}
		vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
		if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
			if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
		}

		// �o�E���f�B���O�{�b�N�X
		m_pBBox->m_mWorld = m_mWorld;
}

//-----------------------------------------------------------------------------  
// �G�V�[���h�I�u�W�F�N�g�̐���
// �G���ʏ��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmShieldObj::UpdateNormal()
{

	MATRIX4X4 mPos;

	if (m_dwStatus == FLASH)m_dwStatus = NORMAL;

	mPos = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);    // ���i�����̂�
	m_mWorld = mPos * m_mWorld;

	//�i�r�Q�[�V�����}�b�v�����ړ����Ă���
	ObjRoundTrip(m_Nav.vMin, m_Nav.vMax);


}

//-----------------------------------------------------------------------------   
// �G�V�[���h�I�u�W�F�N�g�̐���
// �G���_���[�W��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmShieldObj::UpdateDamage()
{
	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���
	m_dwStatus = DEAD;		


}
//-----------------------------------------------------------------------------    
// �G�V�[���h�I�u�W�F�N�g�̐���
//
// �G�����S��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmShieldObj::UpdateDead()
{

	ObjBasicDelete();
	if (m_dwPlayerNo == FIRSTPLAYER)m_pGMain->m_pEnmProc->m_pEnmShieldProc->SetMaxWaitTime();
	if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_pEnmProc->m_pEnmShieldProc->SetMaxWaitTimeSec();
}


//============================================================================ 

// �G�ǃv���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmWallProc::CEnmWallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_WALL_WAITMAX;                   // �G����������܂ł̑҂�����
	m_dwProcID = ENM_WALL_ID;                // �G�I��ID
	m_nNum = m_nMaxNum = ENM_WALL_ALLMAX;    // �G�I�̍ő�o����
	m_dwKinds = TARGET;



	// Fbx�X�L�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy2.mesh"));   // �e�̃X�^�e�B�b�N���b�V��

	for (int i = 0; i < ENM_WALL_MAX*2; i++)
	{
		m_pObjArray.push_back(new CEnmWallObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		m_pObjArray[i]->SetObjID(m_dwProcID);
		m_pObjArray[i]->SetObjNo(i);
		((CEnmWallObj*)m_pObjArray[i])->SetMesh(this);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
		((CEnmWallObj*)m_pObjArray[i])->SetArryNo(i);
		if (i < ENM_WALL_MAX)((CEnmWallObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
		else if (i >= ENM_WALL_MAX)((CEnmWallObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);


	}

	m_nWaitTime = m_nMaxwaitTime = nWait;


}



//============================================================================    
// �G�ǃv���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmWallProc::~CEnmWallProc()
{
	SAFE_DELETE(m_pMesh);
}
//===========================================================================
//
// �G�ǃI�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CGameMain* pGMain;		// �Q�[�����C���N���X�ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CEnmWallObj::CEnmWallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{

	m_dwScorePoint = ENM_WALL_POINT;

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	VECTOR3 vMin(ENM_WALL_BBOX_MIN);
	VECTOR3 vMax(ENM_WALL_BBOX_MAX);
	ObjBasicConstructor(0, 0, vMin, vMax);
	m_vTarget = GetPositionVector(m_mWorld);

}
// ---------------------------------------------------------------------------   
// �G�ǃI�u�W�F�N�g�̃f�X�g���N�^
//
//   �Ȃ��ACBBox��delete��CBaseObj�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmWallObj::~CEnmWallObj()
{
	;
}
// ---------------------------------------------------------------------------  
// �G�ǃI�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CEnmWallProc* pProc
//
// ---------------------------------------------------------------------------  
void CEnmWallObj::SetMesh(CEnmWallProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^
}

// ---------------------------------------------------------------------------   
//
// �G�ǃv���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmWallProc::Update()
{
	UpdateNav();
}
// --------------------------------------------------------------------------- 
//
// �G�ǃv���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmWallProc::UpdateNav()
{
	std::vector<DWORD> Nav;   // �I���i�r�}�b�v
	if (m_pGMain->m_nScore > ENM_WALL_STARTPOINT) {		//�o�����邽�߂̃X�R�A	
		// �܂������ł��鐔�̏ꍇ�̂ݔ���������
		if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
		{
			// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
			for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
			{
				for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
				{
					if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
					{
						Nav.push_back(i);
					}
				}
			}
			if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
			{
				if (m_nWaitTime <= 0)
				{
					// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_WALL_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmWallObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
							m_pObjArray[i]->Start();	// �G�𔭐�������
							m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
							SetMaxWaitTime();
							break;
						}
					}
				}
			}
			else {
				m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
			}
		}
	}
}

// ---------------------------------------------------------------------------    
//
// �G�ǃv���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmWallProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);
}
// ---------------------------------------------------------------------------  

// �G�ǃv���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmWallProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{

	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			if (m_dwPlayerNo == FIRSTPLAYER) {

				if (m_pGMain->m_nScore > ENM_WALL_STARTPOINT) {		//�o�����邽�߂̃X�R�A	

					if (m_nWaitTime <= 0)
					{
						// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = 0; i < ENM_WALL_MAX; i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmWallObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
								m_pObjArray[i]->Start();	// �G�𔭐�������
								m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
								SetMaxWaitTime();
								break;

							}

						}
					}
				}
			}
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_pGMain->m_nScoreSec > ENM_WALL_STARTPOINT) {		//�o�����邽�߂̃X�R�A	

					if (m_nWaitTimeSec <= 0)
					{
						// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = ENM_WALL_MAX; i < (ENM_WALL_MAX * 2); i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmWallObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
								m_pObjArray[i]->Start();	// �G�𔭐�������
								m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
								SetMaxWaitTimeSec();
								break;

							}

						}
					}
				}
			}

		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}

}


// ---------------------------------------------------------------------------  
// �G�ǃv���V�[�W���̃i�r�Q�[�V�����}�b�v�o�^
//
//
// ---------------------------------------------------------------------------
void CEnmWallProc::NavSet()
{

	Nav.clear();
	Nav.shrink_to_fit();

	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}


// ---------------------------------------------------------------------------  
// �G�ǃI�u�W�F�N�g�̔���
//
//
// ---------------------------------------------------------------------------
BOOL CEnmWallObj::Start()
{
	dWallStartTime = ENM_WALL_STARTTIME;

	m_dWeaponUseNum = ENM_WALL_USENUM;
	bTarget = FALSE;	

	// �i�r�Q�[�V�����}�b�v�ɏo��		
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);

	//�o���ʒu�ɉ����Ċp�x��ς���	
	ObjAppearanceDirection(m_Nav.dPosStatus, &m_mWorld);

	m_pBBox->m_mWorld = m_mWorld;                           

	m_bActive = TRUE;	// �G�ǃI�u�W�F�N�g
	fNormalSpeed = ENM_WALL_SPEED;
	m_vPosUp.x = fNormalSpeed;
	m_nHp = m_nMaxHp;
	return TRUE;

}

//-----------------------------------------------------------------------------   
// �G�ǃI�u�W�F�N�g�̐���
//�@�L�[�{�[�h�œG�𓮂���
//�@�G�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ϊ��A�}�b�v�Ƃ̐ڐG����
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmWallObj::Update()
{
	if (!m_bActive) return;  // ��\���̂Ƃ��͏��������Ȃ�

	// �ϐ��̏�����   ---------------------------------------
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // ��O�̈ʒu

	// �X�e�[�^�X���Ƃ̏���  --------------------------------
	switch (m_dwStatus)
	{
	case  FLASH: // �G���_���[�W���畜�A�����Ƃ��̏����Bbreak�������Ɏ���NORMAL���s���B
	case  NORMAL: // �G���ʏ��Ԃ̂Ƃ��̏���
		UpdateNormal();
		break;

	case  DAMAGE: // �G���_���[�W��Ԃ̂Ƃ��̏���
		UpdateDamage();
		if (m_dwPlayerNo == FIRSTPLAYER)m_pGMain->m_nScore = m_pGMain->m_nScore + m_dwScorePoint;
		if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_nScoreSec = m_pGMain->m_nScoreSec + m_dwScorePoint;		
		break;

	case  DEAD:	// �G�����S��Ԃ̂Ƃ��̏���
		UpdateDead();
		break;
	}



	// �`�揈��  ---------------------------------------------

	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}
	// �o�E���f�B���O�{�b�N�X
	m_pBBox->m_mWorld = m_mWorld;

}

//-----------------------------------------------------------------------------   
// �G�ǃI�u�W�F�N�g�̐���
// �G���ʏ��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmWallObj::UpdateNormal()
{

	MATRIX4X4 mPos;
	const int dWallWaitTime = ENM_WALL_WAITTIME;		//�ǂ��o������܂ł̎���

	mPos = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);    // ���i�����̂�
	m_mWorld = mPos * m_mWorld;

	//�i�r�Q�[�V�����}�b�v�����ړ����Ă���	
	ObjRoundTrip(m_Nav.vMin, m_Nav.vMax);


	//�o�������邱�Ƃ̂ł��镐��̐�������Ȃ�
	if (m_dWeaponUseNum > 0) {	//�o�������邱�Ƃ̂ł���X�L���̐�������Ȃ�
		if ((dWallStartTime / 60) > dWallWaitTime) {
			m_pGMain->m_pWeaponProc->m_pWeaponWallProc->Start(m_mWorld, ENM, m_dwObjNo,m_dwPlayerNo); // �{�[������		

			m_dWeaponUseNum--;
			dWallStartTime = 0;
		}
		else {
			dWallStartTime++;
		}
	}

}

//-----------------------------------------------------------------------------    
// �G�ǃI�u�W�F�N�g�̐���
// �G���_���[�W��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmWallObj::UpdateDamage()
{
	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���

	const int nFlashTime = 5;  // ���G��Ԃ̎���


	m_nHp -= m_pHitObj->GetAtc();	// �U�����󂯂��_���[�W
	if (m_nHp <= 0)
	{
		m_nHp = 0;
		m_dwStatus = DEAD;		// HP���O�Ȃ̂Ŏ��S��
	}
	else {
		m_nCnt1 = nFlashTime;   // ���G��Ԃ̎���
		m_dwStatus = FLASH;     // �_���[�W����̕��A�������s��
	}


}
//-----------------------------------------------------------------------------   
// �G�ǃI�u�W�F�N�g�̐���
// �G�����S��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmWallObj::UpdateDead()
{
	ObjBasicDelete();
	if (m_pGMain->m_pEnmProc->m_pEnmWallProc->GetWaitTime() <= 0&& m_dwPlayerNo == FIRSTPLAYER) {	
		m_pGMain->m_pEnmProc->m_pEnmWallProc->SetMaxWaitTime();
	}

	if (m_pGMain->m_pEnmProc->m_pEnmWallProc->GetWaitTimeSec() <= 0 && m_dwPlayerNo == SECONDPLAYER) {	
		m_pGMain->m_pEnmProc->m_pEnmWallProc->SetMaxWaitTimeSec();
	}

}

//============================================================================  
//
// �G���eBall�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmBallBoomProc::CEnmBallBoomProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_BALLBOOM_WAITMAX;                   // �G����������܂ł̑҂�����
	m_dwProcID = ENM_BALLBOOM_ID;                // �G���eBall��ID
	m_nNum = m_nMaxNum = ENM_BALLBOOM_ALLMAX;    // �G���eBall�̍ő�o����
	m_dwKinds = BALL;

	// Fbx�X�L�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Weapon_BallBoom.mesh"));   // �e�̃X�^�e�B�b�N���b�V��
	for (int i = 0; i < ENM_BALLBOOM_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmBallBoomObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		m_pObjArray[i]->SetObjID(m_dwProcID);
		m_pObjArray[i]->SetObjNo(i);
		((CEnmBallBoomObj*)m_pObjArray[i])->SetMesh(this);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��  
		if (i < ENM_TARGET_MAX)((CEnmTargetObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);

	}

	m_nWaitTime = m_nMaxwaitTime = nWait;
	m_dwBreakNum = 0;
}
//============================================================================    
//
// �G���eBall�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmBallBoomProc::~CEnmBallBoomProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================  
//
// �G���eBall�I�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CGameMain* pGMain;		// �Q�[�����C���N���X�ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CEnmBallBoomObj::CEnmBallBoomObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	VECTOR3 vMin(ENM_BALLBOOM_BBOX_MIN);
	VECTOR3 vMax(ENM_BALLBOOM_BBOX_MAX);

	ObjBasicConstructor(0, 0, vMin, vMax);
	m_vDiffuse = VECTOR4(1, 1, 1, 1);
	m_vTarget = GetPositionVector(m_mWorld);


}
// ---------------------------------------------------------------------------  
//
// �G���eBall�I�u�W�F�N�g�̃f�X�g���N�^
//
//   �Ȃ��ACBBox��delete��CBaseObj�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmBallBoomObj::~CEnmBallBoomObj()
{
	;
}
// ---------------------------------------------------------------------------   
// �G���eBall�I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CEnmBallBoomProc* pProc
//
// --------------------------------------------------------------------------- 
void CEnmBallBoomObj::SetMesh(CEnmBallBoomProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^

}

// ---------------------------------------------------------------------------  
// �G���eBall�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmBallBoomProc::Update()
{

	std::vector<DWORD> Nav;   // �I���i�r�}�b�v
	if ( m_pGMain->m_nTimeNum!=0&&m_pGMain->m_nTimeNum % 10 == 0|| m_pGMain->m_dwGameStatus == GAMETUTORIAL) {		
		if (m_pGMain->m_dwGameStatus != GAMEMULTI) {
			// �܂������ł��鐔�̏ꍇ�̂ݔ���������
			if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
			{
				// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
				for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
				{
					for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
					{
						if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
						{
							Nav.push_back(i);
						}
					}
				}
				if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
				{
					if (m_nWaitTime <= 0)
					{
						// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = 0; i < m_pObjArray.size(); i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmBallBoomObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
								m_pObjArray[i]->Start();	// �G�𔭐�������
								m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
								break;
							}
						}
					}
				}
				else {
					m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
				}
			}
		}
	}


}
// ---------------------------------------------------------------------------    
//
// �G���eBall�I�u�W�F�N�g�̔���
//
//
// ---------------------------------------------------------------------------
BOOL CEnmBallBoomObj::Start()
{

	m_bActive = TRUE;	// �G���eBall�I�u�W�F�N�g
	MATRIX4X4 mYaw;
	VECTOR3 m_vTarget;

	// �i�r�Q�[�V�����}�b�v�ɏ]���Ĕ���������		
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
	m_vTarget = VECTOR3((float)Random(m_Nav.vMin.x, m_Nav.vMax.x), m_Nav.vMax.y,
		(float)Random(m_Nav.vMin.z, m_Nav.vMax.z));
	m_pBBox->m_mWorld = m_mWorld;                           

	VECTOR3 vBall = GetPositionVector(m_mWorld);
	VECTOR3 m_vPcTarget = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetLocalMatrix());
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	m_vDiffuse = VECTOR4(1, 1, 1, 1);						

	m_nHp = m_nMaxHp;
	m_dwStatus = NORMAL;
	m_dwStatusSub = ATTACKNONE;
	m_dwStatusPhase = 0;
	m_bDamage = FALSE;

	m_fDist = 0;
	bShaftObjTrigger = FALSE;


	m_vPcTarget = GetPositionVector(pPcObj->GetWorld());

	m_vPcTarget.y = vBall.y;
	m_vRotUp.y = GetTargetRotateVector(m_mWorld, m_vPcTarget).y;
	RotRig(&m_vRotUp.y);
	//m_pGMain->m_nScore = m_vTarget.y;
	mYaw = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));
	m_mWorld = mYaw * m_mWorld;
	
	
	m_pBBox->m_mWorld = m_mWorld;
	m_StartWorld = m_mWorld;		//�X�^�[�g���̃��[���h�}�g���b�N�X	

	m_nScrX = 0;	



	// �Œ�ʒu���甭��������(0,2,20)�����O�Ɍ�������
	return TRUE;

}

//-----------------------------------------------------------------------------  
// �G���eBall�I�u�W�F�N�g�̐���
//
//�@�L�[�{�[�h�œG�𓮂���
//�@�G�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ϊ��A�}�b�v�Ƃ̐ڐG����
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmBallBoomObj::Update()
{
	if (!m_bActive) return;  // ��\���̂Ƃ��͏��������Ȃ�

	// �ϐ��̏�����   ---------------------------------------
	m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // ��O�̈ʒu

	// �X�e�[�^�X���Ƃ̏���  --------------------------------
	switch (m_dwStatus)
	{
	case  FLASH: // �G���_���[�W���畜�A�����Ƃ��̏����Bbreak�������Ɏ���NORMAL���s���B
	case  NORMAL: // �G���ʏ��Ԃ̂Ƃ��̏���
		UpdateNormal();
		break;

	case  DAMAGE: // �G���_���[�W��Ԃ̂Ƃ��̏���
		UpdateDamage();
		break;

	case  DEAD:	// �G�����S��Ԃ̂Ƃ��̏���
		UpdateDead();
		break;
	}
	if (m_pGMain->m_pMapProc->isCollisionMove(&m_mWorld, m_mWorldOld, m_pBBox->m_vMax.x))  // �}�b�v�R���W����
	{

		m_dwStatus = DEAD;

	}

	// �{�[���̍폜����
	// �X�^�[�g����P�O�����z������폜	
	VECTOR3 vNowPos;
	VECTOR3	vStartPos;
	vNowPos = GetPositionVector(m_mWorld);
	vStartPos = GetPositionVector(m_StartWorld);
	if((magnitude(vNowPos - vStartPos)>10|| magnitude(vNowPos - vStartPos)<-10)&&m_bDamage!=TRUE)
	{
		m_dwStatus = DEAD;
	}

	// �`�揈��  ---------------------------------------------

	m_pMesh->m_vDiffuse = m_vDiffuse;			
	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	// �o�E���f�B���O�{�b�N�X
	m_pBBox->m_mWorld = m_mWorld;

	// �G�̓���̌x���\��  -----------------------------
	if (m_bDamage != TRUE) {
		VECTOR3 vEnmPos = GetPositionVector(m_mWorld);
		VECTOR2 vCaveatOverSize = VECTOR2(0.5, 0.5);			//����̌x���T�C�Y
		VECTOR2 vCaveatOverSrcPos = VECTOR2(554, 275);			//����̌x���p�^�[���ʒu
		VECTOR2 vCaveatOverSrcSize = VECTOR2(68, 64);			//����̌x���p�^�[���T�C�Y
		const float vCaveatOverPosTweak = 0.5f;					//����̌x���̈ʒu�������
		vEnmPos.y += 1.0f;

		m_pGMain->m_pRenderBufProc->SetDraw3DSprite(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageRadar(), vEnmPos, vCaveatOverSize, vCaveatOverSrcPos, vCaveatOverSrcSize);
		VECTOR3 vEyePt = m_pGMain->m_vEyePt;
		MATRIX4X4 mImageWorld = TurnTarget(m_mWorld, XMMatrixTranslation(vEyePt.x, vEyePt.y, vEyePt.z));
		mImageWorld = XMMatrixTranslation(vCaveatOverPosTweak,0,0)* mImageWorld;
		vEnmPos = GetPositionVector(mImageWorld);

	}

	//�x���̕\��	
	const int SpritePosX = (WINDOW_WIDTH / 2) - 129;		//�x���̕\���ʒuX���W
	const int SpritePosY = 20;								//�x���̕\���ʒuY���W
	const int SpriteSrcX = 0;								//�x���̃p�^�[���ʒuX���W
	const int SpriteSrcY = 0;								//�x���̃p�^�[���ʒuY���W
	const int SpriteSrcWidth = 258;							//�x���̃p�^�[���T�C�Y��
	const int SpriteSrcHeight =109;							//�x���̃p�^�[���T�C�Y����

	const int SpriteSubPosX = SpritePosX + 8;				//��ڂ̌x���̕\���ʒuX���W
	const int SpriteSubPosY = SpritePosY + 16;				//��ڂ̌x���̕\���ʒuY���W
	const int SpriteSubSrcX = 323;							//��ڂ̌x���̃p�^�[���ʒuX���W
	const int SpriteSubSrcY = 0;							//��ڂ̌x���̃p�^�[���T�C�Y��
	const int SpriteSubSizeWidth = 242;						//��ڂ̌x���̃p�^�[���T�C�Y����
	const int SpriteSubSizeHeight = 84;

	// ���X�N���[��		
	if (m_bDamage != TRUE) {
		m_nScrX += 1;
		if (m_nScrX > SpriteSubSizeWidth)m_nScrX = 0;
		m_pGMain->m_pRenderBufProc->SetDrawSprite(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageEventReport(), SpritePosX, SpritePosY, SpriteSrcX, SpriteSrcY, SpriteSrcWidth, SpriteSrcHeight, 1.0f);
		m_pGMain->m_pRenderBufProc->SetDrawSprite(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageEventReport(), SpriteSubPosX, SpriteSubPosY, SpriteSubSrcX + (m_nScrX), SpriteSubSrcY, SpriteSubSizeWidth - (m_nScrX), SpriteSubSizeHeight, 1.0f);
		m_pGMain->m_pRenderBufProc->SetDrawSprite(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageEventReport(), SpriteSubPosX + (SpriteSubSizeWidth - m_nScrX), SpriteSubPosY, SpriteSubSrcX, SpriteSubSrcY, m_nScrX, SpriteSubSizeHeight, 1.0f);

	}
	

}

//-----------------------------------------------------------------------------   
// �G���eBall�I�u�W�F�N�g�̐���
//
// �G���ʏ��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmBallBoomObj::UpdateNormal()
{

	float fNormalSpeed = ENM_BALLBOOM_SPEED;                                    // �ړ��X�s�[�h
	MATRIX4X4 mPos;
	DWORD	EnmProcSize = m_pGMain->m_pEnmProc->GetProcArrayPtr().size();
	if (m_bDamage == TRUE)	fNormalSpeed = (ENM_BALLBOOM_SPEED*2);		//���������瑬�x���オ��	
	if (m_dwStatus == FLASH)m_dwStatus = NORMAL;
	const float GravityDist = 3.0f;				//���苗��
	const float GravityRotateSpeed = 0.5f;		//�����]���̃X�s�[�h


	mPos = XMMatrixTranslation(0, 0, fNormalSpeed);    // ���i�����̂�
	m_mWorld = mPos * m_mWorld;

	if (m_bDamage == TRUE) {		//�q�b�g��Ԃ̎��̏���
		for (int i = 0; i < EnmProcSize; i++) {
			//�I�ɓ���������
			if (m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->GetKinds() == TARGET) {
				if (m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {
					m_dwStatus = DEAD;
					m_pGMain->m_pEffectProc->m_pLetterEffectProc->AddBreakNum(1);

				}
				//�{�[���̊p�x�̕␳
				if (bShaftObjTrigger != TRUE) {
					if (m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->GetProcID() == ENM_TARGETSKILL_ID)
					{
						m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->ObjGravityMulti(this, GravityDist + 2, GravityRotateSpeed, m_dwPlayerNo);
					}
					else
						m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->ObjGravityMulti(this, GravityDist, GravityRotateSpeed, m_dwPlayerNo);
				}
			}
		}

	}




}

//-----------------------------------------------------------------------------   
// �G���eBall�I�u�W�F�N�g�̐���
//
// �G���_���[�W��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmBallBoomObj::UpdateDamage()
{
		if (m_bDamage != TRUE) {
			if (m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetProcID() == m_pHitObj->GetObjID()) {
				ObjReflection();
				m_bDamage = TRUE;

				m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���
			}
		}
		m_dwStatus = NORMAL;

}
//-----------------------------------------------------------------------------  
// �G���eBall�I�u�W�F�N�g�̐���
//
// �G�����S��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmBallBoomObj::UpdateDead()
{
	VECTOR3 vImagePos = VECTOR3(2.5, 1.5, 7);
	VECTOR2 vLESize = VECTOR2(8, 2);
	VECTOR2 vLESrcPos = VECTOR2(441, 384);
	VECTOR2 vLESrcSize = VECTOR2(147, 46);
	const  float fLEFreamEnd = 100;

	ObjBasicDelete();
	VECTOR3 vNowPos = GetPositionVector(m_mWorld);
	m_pGMain->m_pEffectProc->m_pBillProc->Start(vNowPos,m_bDamage);	// �p�[�e�B�N���̔���
	VECTOR3 vEyePt = m_pGMain->m_vEyePt;
	MATRIX4X4 mImageWorld = TurnTarget(m_mWorld, XMMatrixTranslation(vEyePt.x, vEyePt.y, vEyePt.z));
	mImageWorld = XMMatrixTranslation(vImagePos.x, vImagePos.y, vImagePos.z)* mImageWorld;
	vNowPos = GetPositionVector(mImageWorld);

	//�[���\��
	m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), vNowPos, vLESize, vLESrcPos, vLESrcSize, fLEFreamEnd, m_dwPlayerNo, LENO_EXPANISIONTYPE,1.0);
	m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->SetWaitTime(600);		//���̏o�����邽�߂̎��Ԃ��Z�b�g
	m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->AddNum(1);			//�o�����鐔�𑝂₷
	if(m_pGMain->m_dwGameStatus==GAMETUTORIAL)		m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->SetWaitTime(120);		//���̏o�����邽�߂̎��Ԃ��Z�b�g�i�`���[�g���A���j
	if (m_bDamage != TRUE&&m_pGMain->m_dwGameStatus != GAMETUTORIAL)	m_pGMain->m_nTimer -= ENM_BALLBOOM_TIMERDOWN;		//�������Ԃ����炷

}

//============================================================================    
// �G�Ȃ���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//
// ---------------------------------------------------------------------------
CEnmBendProc::CEnmBendProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_BEND_WAITMAX;                   // �G����������܂ł̑҂�����
	m_dwProcID = ENM_BEND_ID;                // �G�I��ID
	m_nNum = m_nMaxNum = ENM_BEND_ALLMAX;    // �G�I�̍ő�o����
	m_dwKinds = TARGET;



	// Fbx�X�L�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy_BallBend.mesh"));   // �e�̃X�^�e�B�b�N���b�V��

	for (int i = 0; i < (ENM_BEND_MAX*2); i++)
	{
		m_pObjArray.push_back(new CEnmBendObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		m_pObjArray[i]->SetObjID(m_dwProcID);
		m_pObjArray[i]->SetObjNo(i);
		((CEnmBendObj*)m_pObjArray[i])->SetMesh(this);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��  
		((CEnmBendObj*)m_pObjArray[i])->SetArryNo(i);
		if (i < ENM_BEND_MAX)((CEnmBendObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
		else if (i >= ENM_BEND_MAX)((CEnmBendObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);


	}

	m_nWaitTime = m_nMaxwaitTime = nWait;


}



//============================================================================   
// �G�Ȃ���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmBendProc::~CEnmBendProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================  
//
// �G�Ȃ���I�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CGameMain* pGMain;		// �Q�[�����C���N���X�ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CEnmBendObj::CEnmBendObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_dwScorePoint = ENM_BEND_POINT;

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	VECTOR3 vMin(ENM_BEND_BBOX_MIN);
	VECTOR3 vMax(ENM_BEND_BBOX_MAX);
	fBaseDist = 0;
	ObjBasicConstructor(0, 0, vMin, vMax);
	m_vTarget = GetPositionVector(m_mWorld);

}
// ---------------------------------------------------------------------------    
// �G�Ȃ���I�u�W�F�N�g�̃f�X�g���N�^
//
//   �Ȃ��ACBBox��delete��CBaseObj�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmBendObj::~CEnmBendObj()
{
	;
}
// ---------------------------------------------------------------------------   
// �G�Ȃ���I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CEnmBendProc* pProc
//
// ---------------------------------------------------------------------------
void CEnmBendObj::SetMesh(CEnmBendProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^
}


// ---------------------------------------------------------------------------   
// �G�Ȃ���v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmBendProc::Update()
{
	UpdateNav();

}


// ---------------------------------------------------------------------------  
//
//  �G�Ȃ���v���V�[�W���̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmBendProc::UpdateNav()
{
	std::vector<DWORD> Nav;   // �I���i�r�}�b�v

	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			if (m_pGMain->m_nScore > ENM_BEND_STARTPOINT) {		//�o�����邽�߂̃X�R�A

				if (m_nWaitTime <= 0)
				{
					// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_BEND_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmBendObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
							m_pObjArray[i]->Start();	// �G�𔭐�������
							m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
							SetMaxWaitTime();
							break;
						}
					}
				}
			}
		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}

}


// --------------------------------------------------------------------------- 
// �G�Ȃ���v���V�[�W���}���`�̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmBendProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);

}

// ---------------------------------------------------------------------------   
// �G�Ȃ���v���V�[�W���}���`�̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmBendProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{
	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			if (m_dwPlayerNo == FIRSTPLAYER) {

				if (m_pGMain->m_nScore > ENM_BEND_STARTPOINT) {		//�o�����邽�߂̃X�R�A		

					if (m_nWaitTime <= 0)
					{
						// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = 0; i < ENM_BEND_MAX; i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmBendObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
								m_pObjArray[i]->Start();	// �G�𔭐�������
								m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
								SetMaxWaitTime();
								break;

							}

						}
					}
				}
			}
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_pGMain->m_nScoreSec > ENM_BEND_STARTPOINT) {		//�o�����邽�߂̃X�R�A	

					if (m_nWaitTimeSec <= 0)
					{
						// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = ENM_BEND_MAX; i < (ENM_BEND_MAX * 2); i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmBendObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
								m_pObjArray[i]->Start();	// �G�𔭐�������
								m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
								SetMaxWaitTimeSec();
								break;

							}

						}
					}
				}
			}

		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}



}

// ---------------------------------------------------------------------------    
// �G�Ȃ���v���V�[�W���̃i�r�Q�[�V�����}�b�v�o�^
//
//
// ---------------------------------------------------------------------------
void CEnmBendProc::NavSet()
{

	Nav.clear();
	Nav.shrink_to_fit();

	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}


// ---------------------------------------------------------------------------   
// �G�Ȃ���I�u�W�F�N�g�̔���
//
//
// ---------------------------------------------------------------------------
BOOL CEnmBendObj::Start()
{
	dBallStartTime = ENM_BEND_STARTTIME;
	m_dWeaponUseNum = ENM_BEND_USENUM;

	bTarget = FALSE;		
	int RanNum = Random(0, 1);
	if (RanNum == 0)
		fMoveSpeed = ENM_BEND_SPEED;
	else
		fMoveSpeed = -ENM_BEND_SPEED;


	// �i�r�Q�[�V�����}�b�v�ɏo��	
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);


	m_mWorld = TurnTarget(m_mWorld, XMMatrixTranslation(0,0,0));


	m_pBBox->m_mWorld = m_mWorld;                          

	VECTOR3 vTarget = VECTOR3(0, 0, 0);
	VECTOR3 vMyobj = GetPositionVector(m_mWorld);
	fBaseDist = magnitude(vTarget - vMyobj);


	m_bActive = TRUE;	// �G�Ȃ���I�u�W�F�N�g
	fNormalSpeed = 0.05f;
	m_vPosUp.x = fNormalSpeed;
	m_nHp = m_nMaxHp;


	return TRUE;

}

//-----------------------------------------------------------------------------    
// �G�Ȃ���I�u�W�F�N�g�̐���
//�@�L�[�{�[�h�œG�𓮂���
//�@�G�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ϊ��A�}�b�v�Ƃ̐ڐG����
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmBendObj::Update()
{
	if (!m_bActive) return;  // ��\���̂Ƃ��͏��������Ȃ�

	// �ϐ��̏�����   ---------------------------------------
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // ��O�̈ʒu

	// �X�e�[�^�X���Ƃ̏���  --------------------------------
	switch (m_dwStatus)
	{
	case  NORMAL: // �G���ʏ��Ԃ̂Ƃ��̏���
		UpdateNormal();
		break;

	case  DAMAGE: // �G���_���[�W��Ԃ̂Ƃ��̏���
		UpdateDamage();
		m_pGMain->m_nScore = m_pGMain->m_nScore + m_dwScorePoint;
		break;

	case  DEAD:	// �G�����S��Ԃ̂Ƃ��̏���
		UpdateDead();
		break;
	}



	// �`�揈��  ---------------------------------------------
	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

	// �o�E���f�B���O�{�b�N�X
	m_pBBox->m_mWorld = m_mWorld;

}

//-----------------------------------------------------------------------------   
// �G�Ȃ���I�u�W�F�N�g�̐���
// �G���ʏ��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CEnmBendObj::UpdateNormal()
{

	DWORD dBallWaitTime = ENM_WALL_WAITTIME;
	const float BallSpeedRanMin = ENM_WALL_SPEEDRUN_MIN;
	const float BallSpeedRanMax = ENM_WALL_SPEEDRUN_MAX;

	if (m_dwStatus == FLASH)m_dwStatus = NORMAL;

	MATRIX4X4	mBaseWorld = XMMatrixTranslation(0, GetPositionVector(m_mWorld).y, 0);
	m_mWorld = RotTarget(m_mWorld, mBaseWorld, fMoveSpeed,fBaseDist);
	m_mWorld = TurnTarget(m_mWorld, mBaseWorld);

		if ((dBallStartTime / 60) > dBallWaitTime) {
			m_dWeaponUseNum--;
			MATRIX4X4 mStartWord = TurnTarget(m_mWorld,m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
			if (m_dwPlayerNo == SECONDPLAYER)mStartWord = TurnTarget(m_mWorld, m_pGMain->m_pPcProc->GetPcSecObjPtr()->GetWorld());
			VECTOR3 vBallSpeed=VECTOR3(0,0,0);
			vBallSpeed.z = Random(BallSpeedRanMin, BallSpeedRanMax);
			vBallSpeed.z = vBallSpeed.z/ 100+ (Random(0, 9)/1000);
			vBallSpeed.x = vBallSpeed.z;
			m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->Start(mStartWord, vBallSpeed, RIGHT,ENM,m_dwPlayerNo);
			m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->Start(mStartWord, vBallSpeed, LEFT, ENM, m_dwPlayerNo);

			dBallStartTime = 0;
		}
		else {
			dBallStartTime++;
		}
	

}

//-----------------------------------------------------------------------------  
// �G�Ȃ���I�u�W�F�N�g�̐���
// �G���_���[�W��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmBendObj::UpdateDamage()
{
	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���
	m_dwStatus = DEAD;		// HP���O�Ȃ̂Ŏ��S��


}
//-----------------------------------------------------------------------------   
// �G�Ȃ���I�u�W�F�N�g�̐���
// �G�����S��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmBendObj::UpdateDead()
{
	ObjBasicDelete();
	if (m_pGMain->m_pEnmProc->m_pEnmBendProc->GetWaitTime() <= 0&&m_dwPlayerNo==FIRSTPLAYER) {		
		m_pGMain->m_pEnmProc->m_pEnmBendProc->SetMaxWaitTime();
	}
	if (m_pGMain->m_pEnmProc->m_pEnmBendProc->GetWaitTime() <= 0 && m_dwPlayerNo == SECONDPLAYER) {		
		m_pGMain->m_pEnmProc->m_pEnmBendProc->SetMaxWaitTimeSec();
	}

	
}

//============================================================================  
//
// �G�I�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmTargetSkillProc::CEnmTargetSkillProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_TARGETSKILL_WAITMAX;                   // �G����������܂ł̑҂�����
	m_dwProcID = ENM_TARGETSKILL_ID;                // �G�I��ID
	m_nNum = m_nMaxNum = ENM_TARGETSKILL_ALLMAX;    // �G�I�̍ő�o����
	m_dwKinds = TARGET;



	// Fbx�X�L�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy_TargetSkill.mesh"));   // �e�̃X�^�e�B�b�N���b�V��

	for (int i = 0; i < (ENM_TARGETSKILL_MAX * 2); i++)
	{
		m_pObjArray.push_back(new CEnmTargetSkillObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		m_pObjArray[i]->SetObjID(m_dwProcID);
		m_pObjArray[i]->SetObjNo(i);
		((CEnmTargetSkillObj*)m_pObjArray[i])->SetMesh(this);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��  
		if (i < ENM_TARGETSKILL_MAX)((CEnmTargetSkillObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
		else if (i >= ENM_TARGETSKILL_MAX)((CEnmTargetSkillObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);



	}


	m_dwBreakNum = 0;
	m_nWaitTime = m_nMaxwaitTime = nWait;
	m_nWaitTimeSec = nWait;		

}



//============================================================================   
//
// �G�I�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmTargetSkillProc::~CEnmTargetSkillProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================  
//
// �G�I�I�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CGameMain* pGMain;		// �Q�[�����C���N���X�ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CEnmTargetSkillObj::CEnmTargetSkillObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_dwScorePoint = ENM_TARGETSKILL_POINT;

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	VECTOR3 vMin(-0.75f, -0.75f, -0.75f);
	VECTOR3 vMax(ENM_TARGETSKILL_BBOX_MAX);
	ObjBasicConstructor(0, 0, vMin, vMax);

	m_vTarget = GetPositionVector(m_mWorld);

}
// ---------------------------------------------------------------------------    
//
// �G�I�I�u�W�F�N�g�̃f�X�g���N�^
//
//   �Ȃ��ACBBox��delete��CBaseObj�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmTargetSkillObj::~CEnmTargetSkillObj()
{
	;
}
// ---------------------------------------------------------------------------  
//
// �G�I�I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CEnmTargetSkillProc* pProc
//
// ---------------------------------------------------------------------------  
void CEnmTargetSkillObj::SetMesh(CEnmTargetSkillProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^
}

// ---------------------------------------------------------------------------   
//
// �G�I�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmTargetSkillProc::Update()
{
	UpdateNav();
}

// ---------------------------------------------------------------------------   
// �G�I�v���V�[�W���̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmTargetSkillProc::UpdateNav()
{
	std::vector<DWORD> Nav;   // �I���i�r�}�b�v



	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			if (m_nWaitTime <= 0)
			{
				// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
				int k = Random(0, Nav.size() - 1);
				int no = Nav[k];
				for (DWORD i = 0; i < ENM_TARGETSKILL_MAX; i++)
				{
					if (!m_pObjArray[i]->GetActive())
					{
						((CEnmTargetSkillObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
						m_pObjArray[i]->Start();	// �G�𔭐�������
						m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
						SetMaxWaitTime();
						break;
					}
				}
			}
		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}

}

// ---------------------------------------------------------------------------   
//
// �G�I�v���V�[�W���}���`�̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmTargetSkillProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);
}


// --------------------------------------------------------------------------- 
// �G�I�v���V�[�W���}���`�̎������������֐�
//
//
// ---------------------------------------------------------------------------
void CEnmTargetSkillProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{



	// �܂������ł��鐔�̏ꍇ�̂ݔ���������
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		if (Nav.size() > 0)  // �I���i�r�}�b�vNav�ɓo�^����Ă���Ƃ�
		{
			if (m_dwPlayerNo == FIRSTPLAYER) {

				if (m_nWaitTime <= 0)
				{
					// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_TARGETSKILL_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmTargetSkillObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
							m_pObjArray[i]->Start();	// �G�𔭐�������
							m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
							SetMaxWaitTime();
							break;

						}

					}
				}
			}
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_nWaitTimeSec <= 0)
				{
					// �I���i�r�}�b�vNav�̒����甭������i�r�}�b�v�������_���ɑI��
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = ENM_TARGETSKILL_MAX; i < (ENM_TARGETSKILL_MAX * 2); i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmTargetSkillObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // �I�΂ꂽ�i�r�}�b�v���I�u�W�F�N�g�ɓo�^����
							m_pObjArray[i]->Start();	// �G�𔭐�������
							m_nNum--;			// �G�����������甭���ł���G�̐����P���炷
							SetMaxWaitTimeSec();
							break;

						}

					}
				}
			}

		}
		else {
			m_nNum = 0;			// �i�r�}�b�vNav���I������Ă��Ȃ��ꍇ�A�������͂O�ƂȂ�
		}
	}



}

// ---------------------------------------------------------------------------   
// �G�I�v���V�[�W���̃i�r�Q�[�V�����}�b�v�o�^
//
//
// ---------------------------------------------------------------------------
void CEnmTargetSkillProc::NavSet()
{

	//Nav.erase(Nav.begin(), Nav.end());
	Nav.clear();
	Nav.shrink_to_fit();

	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// �i�r�}�b�v�̓G�h�c����v������̂�I���i�r�}�b�vNav�ɓo�^����
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}


// ---------------------------------------------------------------------------   
//
// �G�I�I�u�W�F�N�g�̔���
//
//
// ---------------------------------------------------------------------------
BOOL CEnmTargetSkillObj::Start()
{

	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);


	bTarget = FALSE;		

	// �i�r�Q�[�V�����}�b�v�ɏo��		
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
	m_pBBox->m_mWorld = m_mWorld;                          

	// �I�̈ʒu�����Ȃ��悤�ɂ���		

	for (DWORD i = 0; i < m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->GetObjArrayPtr().size(); i++) {

		if (m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->GetObjArrayPtr()[i]->GetActive() == TRUE) {		//�\������Ă���I��T��
			if (m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->GetObjArrayPtr()[i]->GetPlayerNo() == m_dwPlayerNo) {
				if (m_pBBox->OBBCollisionDetection(m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->GetObjArrayPtr()[i]->GetBBox(), &vHit, &vNrm)) {

					ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
					m_pBBox->m_mWorld = m_mWorld;                          
					i = 0;

				}

			}
		}

	}

	//--�I�Œ�p
	MATRIX4X4 mTran;
	ObjAppearanceDirection(m_Nav.dPosStatus, &m_mWorld);
	m_mWorldOld = m_mWorld;
	m_pBBox->m_mWorld = m_mWorld;                           

	m_bActive = TRUE;	// �G�I�I�u�W�F�N�g

	m_nHp = m_nMaxHp;



	return TRUE;

}

//-----------------------------------------------------------------------------  
// �G�I�I�u�W�F�N�g�̐���
//
//�@�L�[�{�[�h�œG�𓮂���
//�@�G�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ϊ��A�}�b�v�Ƃ̐ڐG����
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmTargetSkillObj::Update()
{
	if (!m_bActive) return;  // ��\���̂Ƃ��͏��������Ȃ�

	// �ϐ��̏�����   ---------------------------------------
	m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // ��O�̈ʒu

	// �X�e�[�^�X���Ƃ̏���  --------------------------------
	switch (m_dwStatus)
	{
	case  FLASH: // �G���_���[�W���畜�A�����Ƃ��̏����Bbreak�������Ɏ���NORMAL���s���B
	case  NORMAL: // �G���ʏ��Ԃ̂Ƃ��̏���
		UpdateNormal();
		break;

	case  DAMAGE: // �G���_���[�W��Ԃ̂Ƃ��̏���
		UpdateDamage();
		if (m_dwPlayerNo == FIRSTPLAYER)m_pGMain->m_nScore = m_pGMain->m_nScore + m_dwScorePoint;
		if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_nScoreSec = m_pGMain->m_nScoreSec + m_dwScorePoint;

		break;

	case  DEAD:	// �G�����S��Ԃ̂Ƃ��̏���
		UpdateDead();
		break;
	}


	// �`�揈��  ---------------------------------------------
	//��ʊO�Ȃ�`�悵�Ȃ�
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}


	// �o�E���f�B���O�{�b�N�X
	m_pBBox->m_mWorld = m_mWorld;


}

//-----------------------------------------------------------------------------   
// �G�I�I�u�W�F�N�g�̐���
//
// �G���ʏ��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmTargetSkillObj::UpdateNormal()
{

	MATRIX4X4 mPos;
	MATRIX4X4 mTemp;

	if (m_dwStatus == FLASH)m_dwStatus = NORMAL;
	mPos = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);    // ���i�����̂�

	m_mWorld = mPos * m_mWorld;

}

//-----------------------------------------------------------------------------   
// �G�I�I�u�W�F�N�g�̐���
//
// �G���_���[�W��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//
//-----------------------------------------------------------------------------
void	CEnmTargetSkillObj::UpdateDamage()
{
	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// �p�[�e�B�N���̔���
	m_dwStatus = DEAD;		// HP���O�Ȃ̂Ŏ��S��


}
//-----------------------------------------------------------------------------  
// �G�I�I�u�W�F�N�g�̐���
//
// �G�����S��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CEnmTargetSkillObj::UpdateDead()
{
	ObjBasicDelete();
	if (m_dwPlayerNo == FIRSTPLAYER)m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->SetMaxWaitTime();
	if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->SetMaxWaitTimeSec();
	SkillGetPc();
}

//-----------------------------------------------------------------------------  
// �G�I�I�u�W�F�N�g�̐���
//
// �v���C���[�ɃX�L������������
//
//   �����@�@�@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CEnmTargetSkillObj::SkillGetPc()
{
	int SkillNoRan = Random(WEAPON_DIV, WEAPON_SKILLSPEEDUP);
	//�o�����Ԃ�ݒ肷��
	if (m_dwPlayerNo == FIRSTPLAYER)
	{
		if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetWeaponColumanNo(0) == 0)m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColumanNo(0, SkillNoRan);

	}
	if (m_dwPlayerNo == SECONDPLAYER)
	{
		if (m_pGMain->m_pPcProc->GetPcSecObjPtr()->GetWeaponColumanNo(0) == 0)m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetWeaponColumanNo(0, SkillNoRan);

	}

}

