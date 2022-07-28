//=============================================================================
//
//		�G�̏���
//																Enamy.cpp
//=============================================================================

#include "Enemy.h"
#include "Weapon.h"
#include "Effect.h"
#include "Playchar.h"
#include "Map.h"


//------------------------------------------------------------------------
//
// �G���C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmProc::CEnmProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pEnmWaterProc = new CEnmWaterProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmWaterProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmTordProc = new CEnmTordProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmTordProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmWolfProc = new CEnmWolfProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmWolfProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmFoxProc = new CEnmFoxProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmFoxProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmTordBrownProc = new CEnmTordBrownProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmTordBrownProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmLastProc = new CEnmLastProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmLastProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����


	m_pEnmLastSubProc = new CEnmLastSubProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmLastSubProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����


}

//============================================================================
//   �G�v���V�[�W���ƃI�u�W�F�N�g��T�����S�ẴI�u�W�F�N�g���m���A�N�e�B�u�ɂ���
//   �G�v���V�[�W���̊J�n�t���O�����Z�b�g����
//============================================================================
void  CEnmProc::SetNonActive()
{

	// �G�̃I�u�W�F�N�g�|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive( FALSE);
	}

	// ���ʂ̃v���V�[�W���|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetStartFlag( 0 );				// �J�n�t���O�̃��Z�b�g
		((CEnmProc*)m_pProcArray[i])->SetNonActive();   // ���ʂ̃v���V�[�W���̏����i�ċA�����j
	}
}

// =====================================================================================================
// 
// �e�G�v���V�[�W�����̏���
// 
// =====================================================================================================

//------------------------------------------------------------------------
//
//	��̐��̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmWaterProc::CEnmWaterProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_WATER_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmWaterObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}

// ---------------------------------------------------------------------------
//
// ��̐��̓G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmWaterProc::Update()
{
	VECTOR2 vPos;
	int nNext;

	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�@ ( EvtID:3�@�G�̏o���ʒu,     �@EvtNo:0x01	��̐��̓G  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x00, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}

		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���

}

//------------------------------------------------------------------------
//
//	��̐��̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmWaterObj::CEnmWaterObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 384, 192, 48, 48);
	m_fAlpha = 0.8f;
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 10000;
	m_nAtc = 200;

}
// ---------------------------------------------------------------------------
//
// ��̐��̓G�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmWaterObj::~CEnmWaterObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// ��̐��̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmWaterObj::Start(VECTOR2 vPos)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = RIGHT;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;

}
//-----------------------------------------------------------------------------
// ��̐��̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmWaterObj::Update()
{

	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			break;

		case  DAMAGE:
			m_dwStatus = NORMAL;
			break;

		case  DEAD:
			m_dwStatus = NORMAL;
			break;
		}

		AnimCountup();
		Draw();

	}
}


// ===================================================================================================

//------------------------------------------------------------------------
//
//	���܂̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmTordProc::CEnmTordProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_TORD_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmTordObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}

}

// ---------------------------------------------------------------------------
//
// ���܂̓G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmTordProc::Update()
{
	VECTOR2 vPos;
	int nNext;


	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while ( nNext != -1 )
		{
			// �C�x���g�}�b�v�@ ( EvtID:3�@�G�̏o���ʒu,     �@EvtNo:0x02�@���܂̓G  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x02, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}

		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���

}

//------------------------------------------------------------------------
//
//	���܂̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmTordObj::CEnmTordObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 480+Random(0,1)*96, 192, 48, 48);
	m_vPos = VECTOR2(0,0);
	m_nHp = m_nMaxHp = 500;
	m_nAtc = 300;

}
// ---------------------------------------------------------------------------
//
// ���܂̓G�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmTordObj::~CEnmTordObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// ���܂̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmTordObj::Start(VECTOR2 vPos)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = LEFT;
	m_vPos = vPos;	// �����ʒu

	m_vPosUp = VECTOR2(0, 0);

	m_nHp = m_nMaxHp;
	 m_pGMain->m_nEnmHpMaxSave = m_nMaxHp;

	m_nEnmpositionx = m_vPos.x;
	m_nEnmpositiony = m_vPos.y;
	SpNum = 0;
	SpCol = 0;
	WeponPosy = 16;
	SpStop = 0;
	m_pGMain->m_nEnmHpSave = m_nHp;

	Damage = 0;

	return TRUE;

}
//-----------------------------------------------------------------------------
// ���܂̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmTordObj::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 2;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;
	int SpPosx = 450;
	int SpPosy = 450;

	BOOL bRet;

	if (m_bActive)
	{


		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
		case  NORMAL:
			//�_���[�W
			Damage = 0;
			if (m_pGMain->m_pWeaponProc->m_pWeaponDifShotProc->Hitcheck((CBaseObj*)this)) {
				m_nHp -= m_pOtherObj->GetAtc()*2;
				Damage = 1;

			}
			else if (m_pGMain->m_pWeaponProc->m_pWeaponCharShotProc->Hitcheck((CBaseObj*)this)) {
				m_nHp -= m_pOtherObj->GetAtc()/2;
				Damage = 1;

			}


			if (Random(0, 50) == 0)
			{
				if (m_nDifShotWait <= 0) {
					if (m_dwStatusSub != STOP) {
						m_vPosUp.x = 0;
						WeaponStop++;
						m_pGMain->m_pWeaponProc->m_pWeaponTordShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
						//m_pGMain->m_pWeaponProc->m_pWeaponTordSpShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
						m_nDifShotWait = 15;
					}
				}
			}
			WeaponStop = 0;
			if (m_nDifShotWait > 0) m_nDifShotWait--;    // ���픭�˂̃E�F�C�g���J�E���g�_�E��

			//Hp������
			if (m_nHp < m_nMaxHp / 2)
			{
				if (m_vPos.x > 260 && m_vPos.x < 650) {
					SpStop = 1;
				}
				if (SpStop == 1) {
					if (SpNum == 0) {
						m_dwStatusSub = STOP;
						m_vPosUp.x = 0;
						m_pGMain->m_nSpTordStop = 0;


						if (m_vPos.y <= SpPosy + 4 && m_vPos.y >= SpPosy - 4)
						{

							m_vPosUp.x = 0;
							m_vPosUp.y = 0;

							m_pGMain->m_pWeaponProc->m_pWeaponTordSpShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
							m_vPos.y = 1000;
							SpNum = 1;

						}
						else {

							if (m_vPos.y > SpPosy)
							{
								m_vPosUp.y = -4;
							}
							else if (m_vPos.y < SpPosy)
							{
								m_vPosUp.y = 4;
							}
							else {
								m_vPosUp.y = 0;
							}

						}
					}
					if (SpNum == 1) {
						if (m_pGMain->m_nSpTordStop == 1)
						{
							m_vPos.x = m_pGMain->m_nSpTordPosx;
							m_vPos.y = m_pGMain->m_nSpTordPosy;
							m_pGMain->m_pWeaponProc->m_pWeaponTordSubShotProc->Start(m_vPos + VECTOR2(Random(-16, 64), Random(-16, 64)), this, ENM);
							m_pGMain->m_pWeaponProc->m_pWeaponTordSubShotProc->Start(m_vPos + VECTOR2(Random(-16, 64), Random(-16, 64)), this, ENM);

							SpNum = 2;
						}

					}
					else if (SpNum > 1 && SpNum <= 12) {
						m_pGMain->m_pWeaponProc->m_pWeaponTordSubShotProc->Start(m_vPos + VECTOR2(Random(-16, 64), Random(-16, 64)), this, ENM);
						m_pGMain->m_pWeaponProc->m_pWeaponTordSubShotProc->Start(m_vPos + VECTOR2(Random(-16, 64), Random(-16, 64)), this, ENM);
						SpNum++;
					}
					else if (SpNum > 12) {
						m_vPosUp.y = fSpeed * 3;
						SpNum = 13;
						SpStop = 0;

					}
				}
			}




					if (SpNum == 13 && Random(0, 1000) == 0 && SpCol / 10 >= 5) {
						SpNum = 0;
						SpCol = 0;
					}
					else if(SpNum == 13){
						SpCol++;
					
				}
			





			break;



		case  DAMAGE:
			if (m_dwStatusSub != STOP) {
				if (Damage == 0) {
					m_nHp -= m_pOtherObj->GetAtc();
				}

				if (m_nHp <= 0) {
					m_dwStatus = DEAD;
					m_nCnt1 = 180;
				}
				else {
					m_dwStatus = FLASH;
					m_nCnt1 = 60;
				}
				m_pGMain->m_nEnmHpSave = m_nHp;
				m_pGMain->m_pSeHit->Play();
			}
			else {
				m_dwStatus = NORMAL;

			}




			break;

		case  DEAD:
			m_nCnt1--;
			if (m_nCnt1 <= 0)
			{
				m_bActive = FALSE;
				//m_pGMain->m_dwGameStatus = GAMECLEAR;
				//m_pGMain->m_nMapChange = 1;
				m_pGMain->m_nUnLookWeapon[3] = 1;
				m_pGMain->m_nEnmHpSave = 0;
				m_pGMain->m_nHeelMaxNum++;
				m_pGMain->m_nBoomStop = 1;
				m_pGMain->m_nDoorStop[4] = 1;
				m_pGMain->m_pMapProc->SetMap(0);
				m_pGMain->m_nHeelNum = m_pGMain->m_nHeelMaxNum + 1;
				m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
				m_pGMain->m_pEffectProc->SetNonActive();	// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����

			}
			else {
				FlashCountup();
			}

			break;



		}

		switch (m_dwStatusSub)
		{
		case  WALK:
			Jump++;

			if (Random(0, 40) == 0)
			{
				if (WeaponStop == 0) {
					if (m_vPos.x <= m_nEnmpositionx + 100)
					{
						m_vPosUp.x = fSpeed;

					}


					if (m_vPos.x > m_nEnmpositionx - 100)
					{
						m_vPosUp.x = -fSpeed;


					}
				}


			}

			/*if (Jump/80>=3)
			{
				if (m_vPos.y >= m_nEnmpositiony - 250)
				{
					m_vPosUp.y = -(fSpeed*2.5 + fJumpPlus);


				}
				Jump = 0;
			}



				if(m_vPos.y < m_nEnmpositiony - 250){
					m_vPosUp.y = fSpeed*2.5 + fJumpPlus;

					Jump = 0;
				}*/


				// ���R�ړ��̏���
				/*if (m_nDirIdx == RIGHT)
				{
					m_vPosUp.x = fSpeed;
				}
				else {
					m_vPosUp.x = -fSpeed;
				}*/

			if (m_vPos.x <= m_pGMain->m_nPcpositionx)
			{
				m_nDirIdx = RIGHT;


			}
			else {
				m_nDirIdx = LEFT;


			}

			if (Jump / 40 >= 3)
			{	// �W�����v�J�n

				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -(fJumpSpeed*2.5 + fJumpPlus);
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				Jump = 0;
				//m_nDirIdx = UP;

			}
			else {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = fSpeed / 2;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;

			}
			break;

		case  JUMP:		// �W�����v���̏���
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + GRAVITY * m_fJumpTime);
			Jump = 0;
			break;

		}

		AnimCountup();
		Draw();

	}
	// �o�b�Ƃ̂����蔻��
//m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
		{
			m_dwStatusSub = WALK;	// �}�b�v���ɐڐG���Ă���Ƃ��́A�W�����v����s�ɖ߂�
			m_fJumpTime = 0;
		}
	}
	// ����
	m_vPos += m_vPosUp;

}

// ===================================================================================================

//------------------------------------------------------------------------
//
//	�I�I�J�~�̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmWolfProc::CEnmWolfProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_TORD_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmWolfObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}

// ---------------------------------------------------------------------------
//
// �I�I�J�~�̓G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmWolfProc::Update()
{
	VECTOR2 vPos;
	int  nNext;

	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T���@ ( EvtID:3�@�G�̏o���ʒu,  EvtNo:0x04	�I�I�J�~�̓G  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x04, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}

		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���

}

//------------------------------------------------------------------------
//
//	�I�I�J�~�̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmWolfObj::CEnmWolfObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 96, 192, 48, 48);
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 500;
	m_nAtc = 400;

}
// ---------------------------------------------------------------------------
//
// �I�I�J�~�̓G�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmWolfObj::~CEnmWolfObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// �I�I�J�~�̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmWolfObj::Start(VECTOR2 vPos)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = LEFT;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);

	m_nHp = m_nMaxHp;
	m_pGMain->m_nEnmHpMaxSave = m_nMaxHp;
	m_nEnmpositionx = m_vPos.x;
	m_nEnmpositiony = m_vPos.y;
	SpNum = 0;
	SpCol = 0;
	m_pGMain->m_nEnmHpSave = m_nHp;

	Damage = 0;

	return TRUE;

}
//-----------------------------------------------------------------------------
// �I�I�J�~�̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmWolfObj::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 2;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;
	int SpPosx = 450;
	int SpPosy = 450;

	BOOL bRet;

	if (m_bActive)
	{
		

		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
		case  NORMAL:
			
			//�_���[�W
			Damage = 0;
			if (m_pGMain->m_pWeaponProc->m_pWeaponCharShotProc->Hitcheck((CBaseObj*)this)) {
				m_nHp -= m_pOtherObj->GetAtc() * 2;
				Damage = 1;

			}
			else if (m_pGMain->m_pWeaponProc->m_pWeaponBoundShotProc->Hitcheck((CBaseObj*)this)) {
				m_nHp -= m_pOtherObj->GetAtc() / 2;
				Damage = 1;

			}

			if (Random(0, 50) == 0)
			{
				if (m_nDifShotWait <= 0) {
					if (m_dwStatusSub != STOP) {
						m_vPosUp.x = 0;
						WeaponStop++;
						m_pGMain->m_pWeaponProc->m_pWeaponWolfShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
						m_nDifShotWait = 15;
					}
				}
			}
			WeaponStop = 0;
			if (m_nDifShotWait > 0) m_nDifShotWait--;    // ���픭�˂̃E�F�C�g���J�E���g�_�E��

			//Hp������
			if(m_nHp< m_nMaxHp/2)
			{
				if (SpNum < 3) {
					m_dwStatusSub = STOP;
					if (SpNum == 0) {

						if (m_vPos.x <= SpPosx+1 && m_vPos.x >= SpPosx-1&& m_vPos.y <= SpPosy + 1 && m_vPos.y >= SpPosy - 1)
						{
							m_vPosUp.x = 0;
							m_vPosUp.y = 0;
							m_pGMain->m_pWeaponProc->m_pWeaponSpWolfShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
							SpNum = 1;

						}
						else {
							if (m_vPos.x > SpPosx)
							{
								m_vPosUp.x = -1;
							}
							else if (m_vPos.x < SpPosx)
							{
								m_vPosUp.x = 1;
							}
							else {
								m_vPosUp.x = 0;
							}
							if (m_vPos.y > SpPosy)
							{
								m_vPosUp.y = -1;
							}
							else if (m_vPos.y < SpPosy)
							{
								m_vPosUp.y = 1;
							}
							else {
								m_vPosUp.y = 0;
							}
						}
					}
					if (SpNum == 1) {
						if (SpDis / 10 <= 3)
						{
							m_vPosUp.x = -fSpeed * 2;
							m_vPosUp.y = -fSpeed;
							SpDis++;
						}
						else {
							m_vPosUp.x = 0;
							m_vPosUp.y = 0;
							m_pGMain->m_pWeaponProc->m_pWeaponSpWolfShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
							SpDis = 0;
							SpNum = 2;

						}
					}
					if (SpNum == 2) {
						if (SpDis / 10 <= 3)
						{
							m_vPosUp.x = fSpeed * 4;
							SpDis++;
						}
						else {
							m_vPosUp.x = 0;
							m_vPosUp.y = 0;
							m_pGMain->m_pWeaponProc->m_pWeaponSpWolfShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
							SpDis = 0;
							SpNum = 3;
							//m_fJumpTime++;
							//m_vPosUp.x = m_vJumpSpeed.x;
							m_vPosUp.y = fSpeed*3;
						}
					}
				}
				if (SpNum == 3 && Random(0, 1000) == 0 &&SpCol/10>=5) {
					SpNum = 0;
					SpCol = 0;
				}
				else {
					SpCol++;
				}
				
			}

			

			
			
			break;



		case  DAMAGE:
			
			if (m_dwStatusSub != STOP) {

				if (Damage == 0)
					m_nHp -= m_pOtherObj->GetAtc();
				if (m_nHp <= 0) {
					m_dwStatus = DEAD;
					m_nCnt1 = 180;
				}
				else {
					m_dwStatus = FLASH;
					m_nCnt1 = 60;
				}
				m_pGMain->m_nEnmHpSave = m_nHp;
				m_pGMain->m_pSeHit->Play();
			}
			else {
				m_dwStatus = NORMAL;

			}

			


			break;

		case  DEAD:
			m_nCnt1--;
			if (m_nCnt1 <= 0)
			{
				m_bActive = FALSE;
				//m_pGMain->m_dwGameStatus = GAMECLEAR;
				//m_pGMain->m_nMapChange = 1;
				m_pGMain->m_nUnLookWeapon[0] = 1;
				m_pGMain->m_nEnmHpSave = 0;
				m_pGMain->m_nHeelMaxNum++;
				m_pGMain->m_nBoomStop = 1;
				m_pGMain->m_nDoorStop[2] = 1;
				m_pGMain->m_pMapProc->SetMap(0);
				m_pGMain->m_nHeelNum = m_pGMain->m_nHeelMaxNum + 1;
				m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
				m_pGMain->m_pEffectProc->SetNonActive();	// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����

			}
			else {
				FlashCountup();
			}
			
			break;

		

		}

		switch (m_dwStatusSub)
		{
		case  WALK:
			Jump++;

			if (Random(0, 40) == 0)
			{
				if (WeaponStop == 0) {
					if (m_vPos.x <= m_nEnmpositionx + 100)
					{
						m_vPosUp.x = fSpeed;

					}


					if (m_vPos.x > m_nEnmpositionx - 100)
					{
						m_vPosUp.x = -fSpeed;


					}
				}


			}

			/*if (Jump/80>=3)
			{
				if (m_vPos.y >= m_nEnmpositiony - 250)
				{
					m_vPosUp.y = -(fSpeed*2.5 + fJumpPlus);


				}
				Jump = 0;
			}



				if(m_vPos.y < m_nEnmpositiony - 250){
					m_vPosUp.y = fSpeed*2.5 + fJumpPlus;

					Jump = 0;
				}*/


				// ���R�ړ��̏���
				/*if (m_nDirIdx == RIGHT)
				{
					m_vPosUp.x = fSpeed;
				}
				else {
					m_vPosUp.x = -fSpeed;
				}*/

			if (m_vPos.x <= m_pGMain->m_nPcpositionx)
			{
				m_nDirIdx = RIGHT;


			}
			else {
				m_nDirIdx = LEFT;


			}
			
			if (Jump / 40 >= 3)
			{	// �W�����v�J�n
				
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -(fJumpSpeed*2.5 + fJumpPlus);
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				Jump = 0;
				//m_nDirIdx = UP;

			}
			else {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = fSpeed / 2;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;

			}
			break;

		case  JUMP:		// �W�����v���̏���
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + GRAVITY * m_fJumpTime);
			Jump = 0;
			break;

		}

		AnimCountup();
		Draw();

	}
	// �o�b�Ƃ̂����蔻��
//m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
		{
			m_dwStatusSub = WALK;	// �}�b�v���ɐڐG���Ă���Ƃ��́A�W�����v����s�ɖ߂�
			m_fJumpTime = 0;
		}
	}
	// ����
	m_vPos += m_vPosUp;

}
//------------------------------------------------------------------------
//
//	Fox�̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmFoxProc::CEnmFoxProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_FOX_MAX; i++)				//��
	{
		m_pObjArray.push_back(new CEnmFoxObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}

// ---------------------------------------------------------------------------
//
// Fox�̓G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmFoxProc::Update()
{
	VECTOR2 vPos;
	int  nNext;

	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T���@ ( EvtID:3�@�G�̏o���ʒu,  EvtNo:0x04	�I�I�J�~�̓G�C EvtNo:0x08 Fox�̓G )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x08, vPos, nNext))		//��
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}

		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���

}

//------------------------------------------------------------------------
//
//	Fox�̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmFoxObj::CEnmFoxObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 192, 192, 48, 48);		//���G
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 500;							//��
	m_nAtc = 200;								//��

}
// ---------------------------------------------------------------------------
//
// Fox�̓G�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmFoxObj::~CEnmFoxObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// Fox�̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmFoxObj::Start(VECTOR2 vPos)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = RIGHT;				//�����܂Ɣ��Ό���
	m_vPos = vPos;	// �����ʒu

	m_vPosUp = VECTOR2(0, 0);

	m_nHp = m_nMaxHp;
	m_pGMain->m_nEnmHpSave = m_nHp;
	m_pGMain->m_nEnmHpMaxSave = m_nMaxHp;

	m_nEnmpositionx = m_vPos.x;
	m_nEnmpositiony = m_vPos.y;
	SpNum = 0;
	SpCol = 0;
	SpTime = 0;

	Damage = 0;

	return TRUE;

}
//-----------------------------------------------------------------------------
// Fox�̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmFoxObj::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 2;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;
	int SpPosx = 450;
	int SpPosy = 450;

	BOOL bRet;

	if (m_bActive)
	{


		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
		case  NORMAL:
			//�_���[�W
			Damage = 0;
			if (m_pGMain->m_pWeaponProc->m_pWeaponBoundShotProc->Hitcheck((CBaseObj*)this)) {
				m_nHp -= m_pOtherObj->GetAtc() * 2;
				Damage = 1;

			}
			else if (m_pGMain->m_pWeaponProc->m_pWeaponDifShotProc->Hitcheck((CBaseObj*)this)) {
				m_nHp -= m_pOtherObj->GetAtc() / 2;
				Damage = 1;

			}

			if (Random(0, 100) == 0)
			{

				if (m_dwStatusSub != STOP) {
					m_vPosUp.x = 0;
					WeaponStop++;
					m_pGMain->m_pWeaponProc->m_pWeaponFoxShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);

				}

			}

			WeaponStop = 0;


			//Hp������
			if (m_nHp < m_nMaxHp / 2)
			{
				if (SpAtc == 0) {
					if (Random(0, 1) == 0) {
						SpAtc = 1;
					}
					else {
						SpAtc = 2;
					}

				}
					switch (SpAtc)
					{
					case 1:
						if (SpNum <= 10) {
							m_vPosUp.x = 0;
							m_vPosUp.y = 0;
							SpTime = 0;
							EnmWalk = 0;
							m_nDirIdx = UP;
							m_dwStatusSub = STOP;


							if (SpNum == 0) {
								SpPosx = 140;
								m_pGMain->m_nSpCharMove = 35;
								m_pGMain->m_pWeaponProc->m_pWeaponFoxSpShotProc->Start(VECTOR2(SpPosx, 500), this, ENM);

							}
							else {
								SpPosx = 140 + (67 * SpNum);
								m_pGMain->m_nSpCharMove += 35;
								m_pGMain->m_pWeaponProc->m_pWeaponFoxSpShotProc->Start(VECTOR2(SpPosx, 500), this, ENM);

							}

							SpNum++;

						}
						else {
							if (SpNum > 10 && Random(0, 1000) == 0 && SpCol / 100 >= 6) {
								SpNum = 0;
								SpCol = 0;
								SpAtc = 0;
							}
							else {
								SpCol++;
							}
							if (SpNum > 10 && SpTime / 100 >= 5 && EnmWalk == 0) {
								m_dwStatusSub = WALK;
								EnmWalk = 1;
								
							}
							else if (EnmWalk == 0) {
								m_dwStatusSub = STOP;
								SpTime++;
							}

						}
						break;

					case 2:
						if (SpNum <= 5) {
							m_vPosUp.x = 0;
							m_vPosUp.y = 0;
							SpTime = 0;
							EnmWalk = 0;
							m_nDirIdx = UP;
							m_dwStatusSub = STOP;


							if (SpNum == 0) {
								SpPosy = 300;
								m_pGMain->m_nSpCharMove = 35;
								m_pGMain->m_pWeaponProc->m_pWeaponFoxSpShotProc->Start(VECTOR2(110, SpPosy), this, ENM);
								m_pGMain->m_pWeaponProc->m_pWeaponFoxSpShotProc->Start(VECTOR2(840, SpPosy), this, ENM);

							}
							else {
								SpPosy = 300 + (80 * SpNum);
								m_pGMain->m_nSpCharMove += 35;
								m_pGMain->m_pWeaponProc->m_pWeaponFoxSpShotProc->Start(VECTOR2(110, SpPosy), this, ENM);
								m_pGMain->m_pWeaponProc->m_pWeaponFoxSpShotProc->Start(VECTOR2(840, SpPosy), this, ENM);

							}

							SpNum++;

						}
						else {
							if (SpNum > 5 && Random(0, 1000) == 0 && SpCol / 100 >= 6) {
								SpNum = 0;
								SpCol = 0;
								SpAtc = 0;
							}
							else {
								SpCol++;
							}
							if (SpNum > 5 && SpTime / 60 >= 5 && EnmWalk == 0) {
								m_dwStatusSub = WALK;
								EnmWalk = 1;
								
							}
							else if (EnmWalk == 0) {
								m_dwStatusSub = STOP;
								SpTime++;
							}

						}
						break;
					}
				
			}





			break;



		case  DAMAGE:

			if (m_dwStatusSub != STOP) {

				if (Damage == 0)
					m_nHp -= m_pOtherObj->GetAtc();
				if (m_nHp <= 0) {
					m_dwStatus = DEAD;
					m_nCnt1 = 180;
				}
				else {
					m_dwStatus = FLASH;
					m_nCnt1 = 60;
				}
				m_pGMain->m_nEnmHpSave = m_nHp;
				m_pGMain->m_pSeHit->Play();
			}
			else {
				m_dwStatus = NORMAL;

			}




			break;

		case  DEAD:
			m_nCnt1--;
			if (m_nCnt1 <= 0)
			{
				m_bActive = FALSE;
				//m_pGMain->m_dwGameStatus = GAMECLEAR;
				//m_pGMain->m_nMapChange = 1;
				m_pGMain->m_nUnLookWeapon[2] = 1;
				m_pGMain->m_nEnmHpSave = 0;
				m_pGMain->m_nHeelMaxNum++;
				m_pGMain->m_nBoomStop = 1;
				m_pGMain->m_nDoorStop[1] = 1;
				m_pGMain->m_pMapProc->SetMap(0);
				m_pGMain->m_nHeelNum = m_pGMain->m_nHeelMaxNum + 1;
				m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
				m_pGMain->m_pEffectProc->SetNonActive();	// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����


			}
			else {
				FlashCountup();
			}

			break;



		}

		switch (m_dwStatusSub)
		{
		case  WALK:
			Jump++;

			if (Random(0, 40) == 0)
			{
				if (WeaponStop == 0) {
					if (m_vPos.x <= m_nEnmpositionx + 100)
					{
						m_vPosUp.x = fSpeed;

					}


					if (m_vPos.x > m_nEnmpositionx - 100)
					{
						m_vPosUp.x = -fSpeed;


					}
				}


			}

			/*if (Jump/80>=3)
			{
				if (m_vPos.y >= m_nEnmpositiony - 250)
				{
					m_vPosUp.y = -(fSpeed*2.5 + fJumpPlus);


				}
				Jump = 0;
			}



				if(m_vPos.y < m_nEnmpositiony - 250){
					m_vPosUp.y = fSpeed*2.5 + fJumpPlus;

					Jump = 0;
				}*/


				// ���R�ړ��̏���
				/*if (m_nDirIdx == RIGHT)
				{
					m_vPosUp.x = fSpeed;
				}
				else {
					m_vPosUp.x = -fSpeed;
				}*/

			if (m_vPos.x <= m_pGMain->m_nPcpositionx)
			{
				m_nDirIdx = RIGHT;


			}
			else {
				m_nDirIdx = LEFT;


			}
		
				if (Jump / 20 >= 3)
				{	// �W�����v�J�n

					m_dwStatusSub = JUMP;
					m_vJumpSpeed.x = m_vPosUp.x;
					m_vJumpSpeed.y = -(fJumpSpeed*2.5 + fJumpPlus);
					m_fJumpTime = 0;
					m_vPosUp.y = m_vJumpSpeed.y;
					Jump = 0;
					//m_nDirIdx = UP;

				}
				else {
					m_dwStatusSub = JUMP;
					m_vJumpSpeed.x = m_vPosUp.x;
					m_vJumpSpeed.y = fSpeed / 2;
					m_fJumpTime = 0;
					m_vPosUp.y = m_vJumpSpeed.y;

				
				break;

		case  JUMP:		// �W�����v���̏���
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + GRAVITY * m_fJumpTime);
			Jump = 0;
			break;

			}
		}

		AnimCountup();
		Draw();

	}
	// �o�b�Ƃ̂����蔻��
//m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
	
		if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
		{
			if (m_nDirIdx != UP) {
				if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
				{
					m_dwStatusSub = WALK;	// �}�b�v���ɐڐG���Ă���Ƃ��́A�W�����v����s�ɖ߂�
					m_fJumpTime = 0;
				}
			}
		
	}
	// ����
	m_vPos += m_vPosUp;

}

//------------------------------------------------------------------------
//
//	���ܒ��F�̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmTordBrownProc::CEnmTordBrownProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_TORD_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmTordBrownObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}

// ---------------------------------------------------------------------------
//
// ���ܒ��F�̓G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmTordBrownProc::Update()
{
	VECTOR2 vPos;
	int  nNext;

	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T���@ ( EvtID:3�@�G�̏o���ʒu,  EvtNo:0x04	���ܒ��F�̓G  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x10, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}

		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���

}

//------------------------------------------------------------------------
//
//	���ܒ��F�̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmTordBrownObj::CEnmTordBrownObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar2, 480 + Random(0, 1) * 96, 192, 48, 48);
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 700;
	m_nAtc = 400;

}
// ---------------------------------------------------------------------------
//
// ���ܒ��F�̓G�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmTordBrownObj::~CEnmTordBrownObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// ���ܒ��F�̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmTordBrownObj::Start(VECTOR2 vPos)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = LEFT;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);

	m_nHp = m_nMaxHp;
	m_nEnmpositionx = m_vPos.x;
	m_nEnmpositiony = m_vPos.y;
	SpNum = 0;
	SpCol = 0;
	HpSpeedUp=1;
	m_pGMain->m_nEnmHpMaxSave = m_nMaxHp;
	m_pGMain->m_nEnmHpSave = m_nHp;

	Damage = 0;

	return TRUE;

}
//-----------------------------------------------------------------------------
// ���ܒ��F�̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmTordBrownObj::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 2;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;
	int SpPosx = 460;
	int SpPosy = 270;

	BOOL bRet;

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
		case  NORMAL:
			//�_���[�W
			Damage = 0;
			if (m_pGMain->m_pWeaponProc->m_pWeaponBoomProc->Hitcheck((CBaseObj*)this)|| m_pGMain->m_pWeaponProc->m_pWeaponProAtkProc->Hitcheck((CBaseObj*)this)) {
				m_nHp -= m_pOtherObj->GetAtc() * 2;
				Damage = 1;

			}

			if (Random(0, 80) == 0)
			{
				if (m_nDifShotWait <= 0) {
					if (m_dwStatusSub != STOP) {
						WeaponStop++;
						m_pGMain->m_pWeaponProc->m_pWeaponTordBrownShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
						m_nDifShotWait = 15;
					}
				}
			}
			WeaponStop = 0;
			if (m_nDifShotWait > 0) m_nDifShotWait--;    // ���픭�˂̃E�F�C�g���J�E���g�_�E��

			//Hp������
			if (m_nHp < m_nMaxHp / 2)
			{
				if (SpStop == 0) {
					switch (SpAtc) {
					case 0:
						m_dwStatusSub = STOP;
						m_nDirIdx = DOWN;
						if (m_vPos.x <= SpPosx + 2 && m_vPos.x >= SpPosx - 2 && m_vPos.y <= SpPosy + 2 && m_vPos.y >= SpPosy - 2)
						{
							m_vPosUp.x = fSpeed;
							m_vPosUp.y = 0;
							SpAtc = 1;

						}
						else {
							if (m_vPos.x > SpPosx)
							{
								m_vPosUp.x = -2;
							}
							else if (m_vPos.x < SpPosx)
							{
								m_vPosUp.x = 2;
							}
							else {
								m_vPosUp.x = 0;
							}
							if (m_vPos.y > SpPosy)
							{
								m_vPosUp.y = -2;
							}
							else if (m_vPos.y < SpPosy)
							{
								m_vPosUp.y = 2;
							}
							else {
								m_vPosUp.y = 0;
							}
						}

						break;
					case 1:
						if (SpNum / 100 <= 6) {
							if (m_vPos.x <= 140) {
								m_vPosUp.x = 6;
							}
							else if (m_vPos.x > 790) {
								m_vPosUp.x = -6;

							}

							if (SpTime / 15 >= Random(1, 4)) {
								m_pGMain->m_pWeaponProc->m_pWeaponTordBrownSpShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
								//SpNum = 3;
								SpTime = 0;
							}
							SpTime++;
							SpNum++;
						}
						else {

							m_vPosUp.x = 0;
							m_vPosUp.y = 6;
							SpAtc = 2;

						}
					

						break;


					}
					if (SpAtc == 2 && Random(0, 1000) == 0 && SpCol / 10 >= 5) {
						SpNum = 0;
						SpCol = 0;
						SpAtc = 0;
					}
					else if (SpAtc == 2) {
						SpCol++;
					}

				}
			}

			if (m_nHp <= (m_nMaxHp*4) / 5&& m_nHp > (m_nMaxHp * 3) / 5)
				HpSpeedUp = 1.25;
			if (m_nHp <= (m_nMaxHp * 3) / 5 && m_nHp > (m_nMaxHp * 2) / 5)
				HpSpeedUp = 1.5;
			if (m_nHp <= (m_nMaxHp * 2) / 5 && m_nHp > (m_nMaxHp * 1) / 5)
				HpSpeedUp = 2;
			if (m_nHp <= (m_nMaxHp * 1) / 5 )
				HpSpeedUp = 3;



			break;



		case  DAMAGE:
			if (m_dwStatusSub != STOP) {

				if (Damage == 0)
					m_nHp -= m_pOtherObj->GetAtc() / 2;
				if (m_nHp <= 0) {
					m_dwStatus = DEAD;
					m_nCnt1 = 180;
				}
				else {
					m_dwStatus = FLASH;
					m_nCnt1 = 60;
				}
				m_pGMain->m_nEnmHpSave = m_nHp;
				m_pGMain->m_pSeHit->Play();
			}
			else {
				m_dwStatus = NORMAL;

			}




			break;

		case  DEAD:
			m_nCnt1--;
			if (m_nCnt1 <= 0)
			{
				m_bActive = FALSE;
				//m_pGMain->m_dwGameStatus = GAMECLEAR;
				//m_pGMain->m_nMapChange = 1;
				m_pGMain->m_nUnLookWeapon[1] = 1;
				m_pGMain->m_nEnmHpSave = 0;
				m_pGMain->m_nHeelMaxNum++;
				m_pGMain->m_nDoorStop[3] = 1;
				m_pGMain->m_nBoomStop = 1;
				m_pGMain->m_pMapProc->SetMap(0);
				m_pGMain->m_nHeelNum = m_pGMain->m_nHeelMaxNum + 1;
				m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
				m_pGMain->m_pEffectProc->SetNonActive();	// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����

			}
			else {
				FlashCountup();
			}

			break;



		}

		switch (m_dwStatusSub)
		{
		case  WALK:
			Jump++;

			if (m_vPos.x >= 820) {
				m_vPosUp.x = -fSpeed* HpSpeedUp;
			}
			if(m_vPos.x<=120){
				m_vPosUp.x = fSpeed* HpSpeedUp;

			}

			if (Random(0, 50) == 0)
			{
				if (WeaponStop == 0) {
					if (m_vPos.x <= m_nEnmpositionx + 100)
					{
						m_vPosUp.x = fSpeed* HpSpeedUp;

					}


					if (m_vPos.x > m_nEnmpositionx - 100)
					{
						m_vPosUp.x = -fSpeed* HpSpeedUp;


					}
				}


			}

			/*if (Jump/80>=3)
			{
				if (m_vPos.y >= m_nEnmpositiony - 250)
				{
					m_vPosUp.y = -(fSpeed*2.5 + fJumpPlus);


				}
				Jump = 0;
			}



				if(m_vPos.y < m_nEnmpositiony - 250){
					m_vPosUp.y = fSpeed*2.5 + fJumpPlus;

					Jump = 0;
				}*/


				// ���R�ړ��̏���
				/*if (m_nDirIdx == RIGHT)
				{
					m_vPosUp.x = fSpeed;
				}
				else {
					m_vPosUp.x = -fSpeed;
				}*/

			if (m_vPos.x <= m_pGMain->m_nPcpositionx)
			{
				m_nDirIdx = RIGHT;


			}
			else {
				m_nDirIdx = LEFT;


			}
				if (Jump / 40 >= 2)
				{	// �W�����v�J�n

					m_dwStatusSub = JUMP;
					m_vJumpSpeed.x = m_vPosUp.x;
					m_vJumpSpeed.y = -(fJumpSpeed*2.5 + fJumpPlus);
					m_fJumpTime = 0;
					m_vPosUp.y = m_vJumpSpeed.y;
					Jump = 0;
					//m_nDirIdx = UP;

				}
				else {
					m_dwStatusSub = JUMP;
					m_vJumpSpeed.x = m_vPosUp.x;
					m_vJumpSpeed.y = fSpeed / 2;
					m_fJumpTime = 0;
					m_vPosUp.y = m_vJumpSpeed.y;

				}
			
			break;

		case  JUMP:		// �W�����v���̏���
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + GRAVITY * m_fJumpTime);
			Jump = 0;
			break;

		}

		AnimCountup();
		Draw();

	}
	// �o�b�Ƃ̂����蔻��
//m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
	
		if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
		{
			if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
			{
				m_dwStatusSub = WALK;	// �}�b�v���ɐڐG���Ă���Ƃ��́A�W�����v����s�ɖ߂�
				m_fJumpTime = 0;
			}
		}
	
	// ����
	m_vPos += m_vPosUp;

}


// ===================================================================================================

//------------------------------------------------------------------------
//
//	�Ō�̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmLastProc::CEnmLastProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_TORD_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmLastObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}

}

// ---------------------------------------------------------------------------
//
// �Ō�̓G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmLastProc::Update()
{
	VECTOR2 vPos;
	int nNext;


	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�@ ( EvtID:3�@�G�̏o���ʒu,     �@EvtNo:0x12�@�Ō�̓G  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x01, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}

		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���

}

//------------------------------------------------------------------------
//
//	�Ō�̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmLastObj::CEnmLastObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar2, 96, 0, 48, 48);
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 700;
	m_nAtc = 300;

}
// ---------------------------------------------------------------------------
//
// �Ō�̓G�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmLastObj::~CEnmLastObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// �Ō�̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmLastObj::Start(VECTOR2 vPos)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = LEFT;
	m_vPos = vPos;	// �����ʒu

	m_vPosUp = VECTOR2(0, 0);

	m_nHp = m_nMaxHp;
	m_nEnmpositionx = m_vPos.x;
	m_nEnmpositiony = m_vPos.y;
	EnmSpShotWait =Random(500, 1000);
	SpNum = 0;
	SpCol = 0;
	WeponPosy = 16;
	SpStartNum = 0;
	WeponChange = Random(0, 2);
	WeaponBitTime = 0;
	m_pGMain->m_nEnmHpSave = m_nHp;
	m_pGMain->m_nEnmHpMaxSave = m_nMaxHp;

	Damage = 0;

	return TRUE;

}
//-----------------------------------------------------------------------------
// �Ō�̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmLastObj::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 4;
	int SpDifSpeed=2;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;
	int SpCharPosx = 450;
	int SpCharPosy = 450;
	int SpBoomPosx = 460;
	int SpBoomPosy = 270;
	int SpBoundPosx = 450;
	int SpBoundPosy = 450;



	BOOL bRet;

	if (m_bActive)
	{


		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
		case  NORMAL:





			//�_���[�W
			Damage = 0;
			if (WeponChange == 0) {
				Damage = 0;
				if (m_pGMain->m_pWeaponProc->m_pWeaponCharShotProc->Hitcheck((CBaseObj*)this)) {
					m_nHp -= m_pOtherObj->GetAtc() * 2;
					Damage = 1;

				}
				else if (m_pGMain->m_pWeaponProc->m_pWeaponBoundShotProc->Hitcheck((CBaseObj*)this)) {
					m_nHp -= m_pOtherObj->GetAtc() / 2;
					Damage = 1;

				}

			}
			else if (WeponChange == 1) {
				Damage = 0;
				if (m_pGMain->m_pWeaponProc->m_pWeaponBoundShotProc->Hitcheck((CBaseObj*)this)) {
					m_nHp -= m_pOtherObj->GetAtc() * 2;
					Damage = 1;

				}
				else if (m_pGMain->m_pWeaponProc->m_pWeaponDifShotProc->Hitcheck((CBaseObj*)this)) {
					m_nHp -= m_pOtherObj->GetAtc() / 2;
					Damage = 1;

				}

			}
			else if (WeponChange == 2) {
				Damage = 0;
				if (m_pGMain->m_pWeaponProc->m_pWeaponDifShotProc->Hitcheck((CBaseObj*)this)) {
					m_nHp -= m_pOtherObj->GetAtc() * 2;
					Damage = 1;

				}
				else if (m_pGMain->m_pWeaponProc->m_pWeaponCharShotProc->Hitcheck((CBaseObj*)this)) {
					m_nHp -= m_pOtherObj->GetAtc() / 2;
					Damage = 1;

				}

			}


			if (m_nHp < m_nMaxHp / 2) {
				if (m_pGMain->m_nBitTimeStop == 0) {

					if (WeaponBitTime <= 0) {
						if (SpNum <= 0) {
							m_pGMain->m_pEnmProc->m_pEnmLastSubProc->Start(m_vPos + VECTOR2(32, -16), this, ENM);
							m_pGMain->m_pEnmProc->m_pEnmLastSubProc->Start(m_vPos + VECTOR2(0, -16), this, ENM);
							WeaponBitTime = Random(700, 1000);
							m_pGMain->m_nBitTimeStop = 1;
						}



					}
					if(WeaponBitTime>0)WeaponBitTime--;
				}
			}
			if (SpStartNum <= 0) {
				if (m_nHp < m_nMaxHp / 3)
				{
					if (SpNum <= 0) {

						if (EnmSpShotWait <= 0) {
							SpStartNum = Random(1000, 1500);
							WeponChange = 4;
						}
					}
				}

			}
			if (SpStartNum > 0)SpStartNum--;

				if (m_vPos.x <= 120) {
					m_vPosUp.x = fSpeed;
				}
				else if (m_vPos.x > 810) {
					m_vPosUp.x = -fSpeed;

				}

			switch (WeponChange)
			{


			case 0:
				m_pSprite->m_vDiffuse = VECTOR4(0.0f,2.0f,0.0f,1.0f);
				if (Random(0, 50) == 0)
				{
					if (m_nDifShotWait <= 0) {
						if (m_dwStatusSub != STOP) {
							m_vPosUp.x = 0;
							WeaponStop++;
							m_pGMain->m_pWeaponProc->m_pWeaponWolfShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
							m_nDifShotWait = 15;
						}
					}
				}
				WeaponStop = 0;
				if (m_nDifShotWait > 0) m_nDifShotWait--;    // ���픭�˂̃E�F�C�g���J�E���g�_�E��

				if (EnmSpShotWait <= 0) {

					if (SpNum < 3) {
						m_dwStatusSub = STOP;
						if (SpNum == 0) {

							if (m_vPos.x <= SpCharPosx + 1 && m_vPos.x >= SpCharPosx - 1 && m_vPos.y <= SpCharPosy + 1 && m_vPos.y >= SpCharPosy - 1)
							{
								m_vPosUp.x = 0;
								m_vPosUp.y = 0;
								m_pGMain->m_pWeaponProc->m_pWeaponSpWolfShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
								SpNum = 1;

							}
							else {
								if (m_vPos.x > SpCharPosx)
								{
									m_vPosUp.x = -1;
								}
								else if (m_vPos.x < SpCharPosx)
								{
									m_vPosUp.x = 1;
								}
								else {
									m_vPosUp.x = 0;
								}
								if (m_vPos.y > SpCharPosy)
								{
									m_vPosUp.y = -1;
								}
								else if (m_vPos.y < SpCharPosy)
								{
									m_vPosUp.y = 1;
								}
								else {
									m_vPosUp.y = 0;
								}
							}
						}
						if (SpNum == 1) {
							if (SpDis / 10 <= 3)
							{
								m_vPosUp.x = -SpDifSpeed * 2;
								m_vPosUp.y = -SpDifSpeed;
								SpDis++;
							}
							else {
								m_vPosUp.x = 0;
								m_vPosUp.y = 0;
								m_pGMain->m_pWeaponProc->m_pWeaponSpWolfShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
								SpDis = 0;
								SpNum = 2;

							}
						}
						if (SpNum == 2) {
							if (SpDis / 10 <= 3)
							{
								m_vPosUp.x = SpDifSpeed * 4;
								SpDis++;
							}
							else {
								m_vPosUp.x = 0;
								m_vPosUp.y = 0;
								m_pGMain->m_pWeaponProc->m_pWeaponSpWolfShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
								SpDis = 0;
								SpNum = 0;
								EnmSpShotWait = Random(500, 1000);
								WeponChange = Random(0, 2);
								m_dwStatusSub = WALK;

								//m_fJumpTime++;
								//m_vPosUp.x = m_vJumpSpeed.x;
								m_vPosUp.y = fSpeed * 3;
							}
						}
					}
				}

				if (EnmSpShotWait > 0) EnmSpShotWait--;

				break;

			case 1:

				m_pSprite->m_vDiffuse = VECTOR4(2.0f, 0.0f, 0.0f, 1.0f);
				if (Random(0, 100) == 0)
				{

					if ( EnmSpShotWait>0) {
						m_vPosUp.x = 0;
						m_pGMain->m_pWeaponProc->m_pWeaponFoxShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);

					}

				}

				if (EnmSpShotWait <= 0) {

					if (SpCharAtc == 0) {
						if (Random(0, 1) == 0) {
							SpCharAtc = 1;
						}
						else {
							SpCharAtc = 2;
						}

					}

					switch (SpCharAtc)
					{
					case 1:
						if (SpNum <= 10) {
							m_vPosUp.x = 0;
							m_vPosUp.y = 0;
							SpCharTime = 0;
							EnmCharWalk = 0;
							m_nDirIdx = UP;
							m_dwStatusSub = STOP;


							if (SpNum == 0) {
								SpCharPosx = 140;
								m_pGMain->m_nSpCharMove = 35;
								m_pGMain->m_pWeaponProc->m_pWeaponFoxSpShotProc->Start(VECTOR2(SpCharPosx, 500), this, ENM);

							}
							else {
								SpCharPosx = 140 + (67 * SpNum);
								m_pGMain->m_nSpCharMove += 35;
								m_pGMain->m_pWeaponProc->m_pWeaponFoxSpShotProc->Start(VECTOR2(SpCharPosx, 500), this, ENM);

							}

							SpNum++;

						}
						else {
							if (SpNum > 10 && SpCharTime / 100 >= 5 && EnmCharWalk == 0) {
								//m_dwStatusSub = WALK;
								EnmCharWalk = 1;
								SpNum = 0;
								SpCharAtc = 0;
								EnmSpShotWait = Random(500, 1000);
								WeponChange = Random(0, 2);
								SpNum = 0;
								m_dwStatusSub = WALK;




							}
							else if (EnmCharWalk == 0) {
								m_dwStatusSub = STOP;
								SpCharTime++;
							}

						}
						break;

					case 2:


						if (SpNum <= 5) {
							m_vPosUp.x = 0;
							m_vPosUp.y = 0;
							SpCharTime = 0;
							EnmCharWalk = 0;
							m_nDirIdx = UP;
							m_dwStatusSub = STOP;


							if (SpNum == 0) {
								SpCharPosy = 300;
								m_pGMain->m_nSpCharMove = 35;
								m_pGMain->m_pWeaponProc->m_pWeaponFoxSpShotProc->Start(VECTOR2(110, SpCharPosy), this, ENM);
								m_pGMain->m_pWeaponProc->m_pWeaponFoxSpShotProc->Start(VECTOR2(840, SpCharPosy), this, ENM);

							}
							else {
								SpCharPosy = 300 + (80 * SpNum);
								m_pGMain->m_nSpCharMove += 35;
								m_pGMain->m_pWeaponProc->m_pWeaponFoxSpShotProc->Start(VECTOR2(110, SpCharPosy), this, ENM);
								m_pGMain->m_pWeaponProc->m_pWeaponFoxSpShotProc->Start(VECTOR2(840, SpCharPosy), this, ENM);

							}

							SpNum++;

						}
						else {
							if (SpNum > 5 && SpCharTime / 60 >= 5 && EnmCharWalk == 0) {
								m_dwStatusSub = WALK;
								EnmCharWalk = 1;
								SpCharAtc = 0;
								EnmSpShotWait = Random(500, 1000);
								WeponChange = Random(0, 2);
								SpNum = 0;
								m_dwStatusSub = WALK;


							}
							else if (EnmCharWalk == 0) {
								m_dwStatusSub = STOP;
								SpCharTime++;
							}

						}
						break;

					}
				}
				if (EnmSpShotWait > 0) EnmSpShotWait--;

				break;


			case 2:
				m_pSprite->m_vDiffuse = VECTOR4(0.0f, 0.0f, 2.0f, 1.0f);
				if (Random(0, 50) == 0)
				{
					if (EnmBoundWait <= 0) {
						if (m_dwStatusSub != STOP) {
							m_vPosUp.x = 0;
							WeaponStop++;
							m_pGMain->m_pWeaponProc->m_pWeaponTordShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
							//m_pGMain->m_pWeaponProc->m_pWeaponTordSpShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
							EnmBoundWait = 15;
						}
					}
				}
				WeaponStop = 0;
				if (EnmBoundWait > 0) EnmBoundWait--;    // ���픭�˂̃E�F�C�g���J�E���g�_�E��

				if (EnmSpShotWait <= 0) {

					if (m_vPos.x > 260 && m_vPos.x < 650) {
						SpBoundStop = 1;
					}

					if (SpBoundStop == 1) {
						if (SpNum == 0) {
							m_dwStatusSub = STOP;
							m_vPosUp.x = 0;
							m_pGMain->m_nSpTordStop = 0;


							if (m_vPos.y <= SpBoundPosy + 4 && m_vPos.y >= SpBoundPosy - 4)
							{

								m_vPosUp.x = 0;
								m_vPosUp.y = 0;

								m_pGMain->m_pWeaponProc->m_pWeaponTordSpShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
								m_vPos.x = 1000;
								m_vPos.y = 1000;
								SpNum = 1;

							}
							else {

								if (m_vPos.y > SpBoundPosy)
								{
									m_vPosUp.y = -4;
								}
								else if (m_vPos.y < SpBoundPosy)
								{
									m_vPosUp.y = 4;
								}
								else {
									m_vPosUp.y = 0;
								}

							}
						}
						if (SpNum == 1) {
							if (m_pGMain->m_nSpTordStop == 1)
							{
								m_vPos.x = m_pGMain->m_nSpTordPosx;
								m_vPos.y = m_pGMain->m_nSpTordPosy;
								m_pGMain->m_pWeaponProc->m_pWeaponTordSubShotProc->Start(m_vPos + VECTOR2(Random(-16, 64), Random(-16, 64)), this, ENM);
								m_pGMain->m_pWeaponProc->m_pWeaponTordSubShotProc->Start(m_vPos + VECTOR2(Random(-16, 64), Random(-16, 64)), this, ENM);

								SpNum = 2;
							}

						}
						else if (SpNum > 1 && SpNum <= 12) {
							m_pGMain->m_pWeaponProc->m_pWeaponTordSubShotProc->Start(m_vPos + VECTOR2(Random(-16, 64), Random(-16, 64)), this, ENM);
							m_pGMain->m_pWeaponProc->m_pWeaponTordSubShotProc->Start(m_vPos + VECTOR2(Random(-16, 64), Random(-16, 64)), this, ENM);
							SpNum++;
						}
						else if (SpNum > 12) {
							m_vPosUp.y = fSpeed * 3;
							EnmSpShotWait = Random(500, 1000);
							WeponChange = Random(0, 2);
							SpNum = 0;
							SpBoundStop = 0;
							m_dwStatusSub = WALK;

						}
					}

				}
				if (EnmSpShotWait > 0) EnmSpShotWait--;

				break;

		case 4:
				if (EnmSpShotWait <= 0) {
					if (SpNum < 3) {
						m_dwStatusSub = STOP;
						m_nDirIdx = UP;
						if (SpNum == 0) {
							m_pSprite->m_vDiffuse = VECTOR4(1.28f, 0.0f, 1.28f, 1.0f);

							if (m_vPos.x <= SpCharPosx + 1 && m_vPos.x >= SpCharPosx - 1 && m_vPos.y <= SpCharPosy + 1 && m_vPos.y >= SpCharPosy - 1)
							{
								m_vPosUp.x = 0;
								m_vPosUp.y = 0;
								m_pGMain->m_nSpLastStop = 1;
								m_pGMain->m_pWeaponProc->m_pEnmLastSpShotProc->Start(m_vPos + VECTOR2(-100, -128), this, ENM);
								SpNum = 1;

							}
							else {
								if (m_vPos.x > SpCharPosx)
								{
									m_vPosUp.x = -1;
								}
								else if (m_vPos.x < SpCharPosx)
								{
									m_vPosUp.x = 1;
								}
								else {
									m_vPosUp.x = 0;
								}
								if (m_vPos.y > SpCharPosy)
								{
									m_vPosUp.y = -1;
								}
								else if (m_vPos.y < SpCharPosy)
								{
									m_vPosUp.y = 1;
								}
								else {
									m_vPosUp.y = 0;
								}
							}
						}
						if (SpNum == 1) {
							if (m_pGMain->m_nSpLastStop == 0) {
								m_vPosUp.y = fSpeed * 3;
								SpNum = 2;
							}

						}
						if (SpNum == 2) {
								EnmSpShotWait = Random(500, 1000);
								WeponChange = Random(0, 2);
								SpDis = 0;
								SpNum = 0;

								
								//m_fJumpTime++;
								//m_vPosUp.x = m_vJumpSpeed.x;
								m_dwStatusSub = WALK;

						}
					}

				}
				if (EnmSpShotWait > 0) EnmSpShotWait--;

				break;

			}

			break;



		case  DAMAGE:
			if (m_dwStatusSub != STOP) {

				if (Damage == 0) {
					m_nHp -= m_pOtherObj->GetAtc() / 2;

				}

				if (Damage == 0)
					m_nHp -= m_pOtherObj->GetAtc();
				if (m_nHp <= 0) {
					m_dwStatus = DEAD;
					m_nCnt1 = 180;
				}
				else {
					m_dwStatus = FLASH;
					m_nCnt1 = 60;
				}
				m_pGMain->m_nEnmHpSave = m_nHp;
				m_pGMain->m_pSeHit->Play();

			}
			else {
				m_dwStatus = NORMAL;

			}


			break;

		case  DEAD:
			m_nCnt1--;
			if (m_nCnt1 <= 0)
			{
				m_bActive = FALSE;
				m_pGMain->m_dwGameStatus = GAMECLEAR;
				//m_pGMain->m_nMapChange = 1;
				m_pGMain->m_nEnmHpSave = 0;
				m_pGMain->m_nBoomStop = 1;
				m_pGMain->m_nDoorStop[4] = 1;
				m_pGMain->m_pMapProc->SetMap(0);
				m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
				m_pGMain->m_pEffectProc->SetNonActive();	// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����

			}
			else {
				FlashCountup();
			}

			break;



		}

		switch (m_dwStatusSub)
		{
		case  WALK:
			Jump++;

			if (Random(0, 40) == 0)
			{
				if (WeaponStop == 0) {
					if (m_vPos.x <= m_nEnmpositionx + 100)
					{
						m_vPosUp.x = fSpeed;

					}


					if (m_vPos.x > m_nEnmpositionx - 100)
					{
						m_vPosUp.x = -fSpeed;


					}
				}


			}

			/*if (Jump/80>=3)
			{
				if (m_vPos.y >= m_nEnmpositiony - 250)
				{
					m_vPosUp.y = -(fSpeed*2.5 + fJumpPlus);


				}
				Jump = 0;
			}



				if(m_vPos.y < m_nEnmpositiony - 250){
					m_vPosUp.y = fSpeed*2.5 + fJumpPlus;

					Jump = 0;
				}*/


				// ���R�ړ��̏���
				/*if (m_nDirIdx == RIGHT)
				{
					m_vPosUp.x = fSpeed;
				}
				else {
					m_vPosUp.x = -fSpeed;
				}*/

			if (m_vPos.x <= m_pGMain->m_nPcpositionx)
			{
				m_nDirIdx = RIGHT;


			}
			else {
				m_nDirIdx = LEFT;


			}

			if (Jump / 40 >= 3)
			{	// �W�����v�J�n

				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -(fJumpSpeed*2.5 + fJumpPlus);
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				Jump = 0;
				//m_nDirIdx = UP;

			}
			else {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = fSpeed / 2;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;

			}
			break;

		case  JUMP:		// �W�����v���̏���
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + GRAVITY * m_fJumpTime);
			Jump = 0;
			break;

		}

		AnimCountup();
		Draw();

	}
	// �o�b�Ƃ̂����蔻��
//m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
		{
			m_dwStatusSub = WALK;	// �}�b�v���ɐڐG���Ă���Ƃ��́A�W�����v����s�ɖ߂�
			m_fJumpTime = 0;
		}
	}
	// ����
	m_vPos += m_vPosUp;

}



// ===================================================================================================

//------------------------------------------------------------------------
//
//	�Ō�̃T�u�G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmLastSubProc::CEnmLastSubProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < WEAPON_ENMLASTSUBBIT_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmLastSubObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}


// ---------------------------------------------------------------------------
//
// �Ō�̃T�u�G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
/*void CEnmLastSubProc::Update()
{
	VECTOR2 vPos;
	int  nNext;

	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T���@ ( EvtID:3�@�G�̏o���ʒu,  EvtNo:0x04	�Ō�̃T�u�G  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x00, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}

		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���

}*/

//-----------------------------------------------------------------------------
// ����E�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSubProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// ����̔���
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���

	return bRet;
}




//------------------------------------------------------------------------
//
//	�Ō�̃T�u�G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmLastSubObj::CEnmLastSubObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar2, 480, 45, 48, 48);
	m_nAnimNum = 1;

	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 80;
	m_nAtc = 400;

}
// ---------------------------------------------------------------------------
//
// �Ō�̃T�u�G�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmLastSubObj::~CEnmLastSubObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// �Ō�̃T�u�G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmLastSubObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = LEFT;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);

	m_nHp = m_nMaxHp;
	m_nEnmpositionx = m_vPos.x;
	m_nEnmpositiony = m_vPos.y;
	SpNum = 0;
	SpCol = 0;

	PosxSave = m_vPos.x;
	PosySave = m_vPos.y;

	return TRUE;

}
//-----------------------------------------------------------------------------
// �Ō�̃T�u�G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmLastSubObj::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 1.5;
	int SpPosx = 450;
	int SpPosy = 450;

	BOOL bRet;

	if (m_bActive)
	{


		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
		case  NORMAL:

			if (m_vPos.y < 400) {
				m_vPosUp.y = fSpeed;
			}

			if (m_vPos.x < 250)
			{
				m_vPosUp.x = fSpeed;

			}


			if (m_vPos.x > 750)
			{
				m_vPosUp.x = -fSpeed;


			}
			if (m_vPos.y > 700) {
				m_vPosUp.y = -fSpeed;

			}

			if (Random(0, 40) == 0)
			{
				if (WeaponStop == 0) {
					if (m_vPos.x <= m_nEnmpositionx + 250)
					{
						m_vPosUp.x = fSpeed;

					}


					if (m_vPos.x > m_nEnmpositionx - 250)
					{
						m_vPosUp.x = -fSpeed;


					}
					if (Random(0, 50) == 0)
					{
						m_vPosUp.y = -fSpeed;

					}


					if (Random(0, 40) == 0)
					{
						m_vPosUp.y = fSpeed;


					}
				}


			}



			if (Random(0, 50) == 0)
			{
				if (m_nDifShotWait <= 0) {
					if (m_dwStatusSub != STOP) {
						m_pGMain->m_pWeaponProc->m_pEnmLastSubShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
						m_nDifShotWait = 100;
					}
				}
			}
			WeaponStop = 0;
			if (m_nDifShotWait > 0) m_nDifShotWait--;    // ���픭�˂̃E�F�C�g���J�E���g�_�E��


				PcPosxSave = m_pGMain->m_nPcpositionx;
				PcPosySave = m_pGMain->m_nPcpositiony;






			break;



		case  DAMAGE:


			m_nHp -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0) {
				m_dwStatus = DEAD;
				m_nCnt1 = 180;
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}

			m_pGMain->m_pSeHit->Play();




			break;

		case  DEAD:
			m_nCnt1--;
			if (m_nCnt1 <= 0)
			{
				m_pGMain->m_nBitTimeStop = 0;
				m_bActive = FALSE;
				//m_pGMain->m_dwGameStatus = GAMECLEAR;
				//m_pGMain->m_nMapChange = 1;


			}
			else {
				FlashCountup();
			}

			break;



		}


		AnimCountup();
		Draw();

	}
	// �o�b�Ƃ̂����蔻��
//m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
		{

		}
	}
	// ����
	m_vPos += m_vPosUp;

}
