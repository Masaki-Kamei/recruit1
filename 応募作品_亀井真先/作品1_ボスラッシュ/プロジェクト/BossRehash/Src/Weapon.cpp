//=============================================================================
//
//      ����̏���
//																Weapon.cpp
//=============================================================================

#include "Weapon.h"
#include "Playchar.h"
#include "Enemy.h"
#include "Map.h"
#include "Effect.h"


//=============================================================================================================================
//
// ���탁�C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ----------------------------------------------------------------------------------------------------------------------------
CWeaponProc::CWeaponProc(CGameMain* pGMain) : CBaseProc(pGMain)
{

	m_pWeaponShotProc = new CWeaponShotProc(m_pGMain);	// ����E�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponShieldProc = new CWeaponShieldProc(m_pGMain);	// ����E�V�[���h�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponShieldProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponBoomProc = new CWeaponBoomProc(m_pGMain);	// ����E���e�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponBoomProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponProAtkProc = new CWeaponProAtkProc(m_pGMain);	// ����E�ߐڍU���v���V�[�W��
	m_pProcArray.push_back(m_pWeaponProAtkProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponDifShotProc = new CWeaponDifShotProc(m_pGMain);	// ����E�g�U�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponDifShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponCharShotProc = new CWeaponCharShotProc(m_pGMain);	// ����E�`���[�W�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponCharShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponBoundShotProc = new CWeaponBoundShotProc(m_pGMain);	// ����E�o�E���h�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponBoundShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����



	m_pWeaponSpWolfShotProc = new CWeaponSpWolfShotProc(m_pGMain);	// ����E�I�I�J�~�X�y�V�����V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponSpWolfShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponWolfShotProc = new CWeaponWolfShotProc(m_pGMain);	// ����E�I�I�J�~�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponWolfShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����



	m_pWeaponFoxShotProc = new CWeaponFoxShotProc(m_pGMain);	// ����E�L�c�l�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponFoxShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponFoxSubShotProc = new CWeaponFoxSubShotProc(m_pGMain);	// ����E�L�c�l�T�u�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponFoxSubShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponFoxSpShotProc = new CWeaponFoxSpShotProc(m_pGMain);	// ����E�L�c�l�X�y�V�����V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponFoxSpShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����



	m_pWeaponTordBrownShotProc = new CWeaponTordBrownShotProc(m_pGMain);	// ����E���ܒ��F�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponTordBrownShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponTordBrownSpShotProc = new CWeaponTordBrownSpShotProc(m_pGMain);	// ����E���ܒ��F�X�y�V�����V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponTordBrownSpShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����


	m_pWeaponTordShotProc = new CWeaponTordShotProc(m_pGMain);	// ����E���܃V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponTordShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponTordSpShotProc = new CWeaponTordSpShotProc(m_pGMain);	// ����E���܃X�y�V�����V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponTordSpShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponTordSubShotProc = new CWeaponTordSubShotProc(m_pGMain);	// ����E���܃T�u�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponTordSubShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����



	m_pEnmLastSubShotProc = new CEnmLastSubShotProc(m_pGMain);	// ����E�Ō�̓G�T�u�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pEnmLastSubShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponLaserProc = new CWeaponLaserProc(m_pGMain);	// ����E���[�U�[�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponLaserProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmLastSpShotProc = new CEnmLastSpShotProc(m_pGMain);	// ����E�Ō�̓G�X�y�V�����V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pEnmLastSpShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmLastSpSubShotProc = new CEnmLastSpSubShotProc(m_pGMain);	// ����E�Ō�̓G�X�y�V�����T�u�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pEnmLastSpSubShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

} 


// ================================================================================================================================
// 
// �e�G�v���V�[�W�����̏���
// 
// ================================================================================================================================

//------------------------------------------------------------------------
//
//	����E�V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponShotProc::CWeaponShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�V���b�g
	for (DWORD i = 0; i < WEAPON_SHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponShotObj(m_pGMain));	// m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponShotObj::CWeaponShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite4, 0, 480, 24, 24);
	m_nAnimNum = 1;

	m_nAtc = 40;
}
// ---------------------------------------------------------------------------
//
// ����E�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponShotObj::~CWeaponShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// �e�̑���
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_vSitPos = m_vPos.x;

	switch(pObj->GetDirIdx() )
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed,0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed,0);
		break;
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponShotObj::Update()
{
	
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
			case  NORMAL:
				if (m_dwOwner == PC) // PC�����˂����e
				{
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);


				}
				else { //  �G�����˂����e
					m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
					

				}
				if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
				{
					m_bActive = FALSE;
				}

				if (m_vPos.x-m_pGMain->m_vScroll.x < 0 || m_vPos.x-m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
					m_vPos.y-m_pGMain->m_vScroll.y < 0 || m_vPos.y-m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
					m_bActive = FALSE;
				}
				if (m_vPos.x >= m_vSitPos + 350 || m_vPos.x <= m_vSitPos - 350)		//�˒�
				{
					m_bActive = FALSE;
				}
				break;

			case  DAMAGE:
				m_bActive = FALSE;
				
				break;
		}
		
		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}

//------------------------------------------------------------------------
//
//	����E�V�[���h�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponShieldProc::CWeaponShieldProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�V�[���h
	for (DWORD i = 0; i < WEAPON_SHIELD_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponShieldObj(m_pGMain));	// m_pObjArray�ɕ���E�V�[���h�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�V�[���h�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponShieldProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�V�[���h�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponShieldObj::CWeaponShieldObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain-> m_pImageSprite2, 48, 320, 16, 32,16,74);
	m_nAnimNum = 1;

	m_nAtc = 100;
}
// ---------------------------------------------------------------------------
//
// ����E�V�[���h�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponShieldObj::~CWeaponShieldObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�V�[���h�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponShieldObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 0;	// �e�̑���


	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu
	if (m_pGMain->m_nDirection == 0)
	{
		m_vPos.x = m_pGMain->m_nPcpositionx + 50.0f;
		m_vPos.y = m_pGMain->m_nPcpositiony-10;

	}
	else if (m_pGMain->m_nDirection==1)
	{
		m_vPos.x = m_pGMain->m_nPcpositionx - 30.0f;
		m_vPos.y = m_pGMain->m_nPcpositiony - 10;

	}

	m_vPosUp = VECTOR2(0, 0);

	switch (pObj->GetDirIdx())
	{
	case UP:
		break;
	case DOWN:
		break;
	case RIGHT:
		//m_nDirection = 0;

		break;
	case LEFT:
		//m_vPosUp = VECTOR2(-fSpeed, 0);
		//m_nDirection = 1;

		break;


	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�V�[���h�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponShieldObj::Update()
{
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:

			if (m_pGMain->m_nShieldStop == 0) {	//�����������
				m_bActive = FALSE;
			}
			
			if (m_pGMain->m_nDirection == 0)
			{
				m_vPos.x = m_pGMain->m_nPcpositionx + 50.0f;
				m_vPos.y = m_pGMain->m_nPcpositiony - 13;

			}
			else if (m_pGMain->m_nDirection == 1)
			{
				m_vPos.x = m_pGMain->m_nPcpositionx - 30.0f;
				m_vPos.y = m_pGMain->m_nPcpositiony - 13;

			}
			break;
		case  DAMAGE:
			//m_bActive = FALSE;
			m_dwStatus = NORMAL;
			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}
//------------------------------------------------------------------------
//
//	����E���e �v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponBoomProc::CWeaponBoomProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E���e
	for (DWORD i = 0; i < WEAPON_BOOM_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponBoomObj(m_pGMain));	// m_pObjArray�ɕ���E���e�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E���e�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponBoomProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E���e�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponBoomObj::CWeaponBoomObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite2, 768, 416, 32, 14);
	m_nAnimNum = 1;

	m_nAtc = 150;
}
// ---------------------------------------------------------------------------
//
// ����E���e�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBoomObj::~CWeaponBoomObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E���e�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponBoomObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu
	m_vOf = VECTOR2(0, 0);
	m_vTarget = VECTOR2(0, 0);
	m_vPosUp = VECTOR2(0, 0);

	m_pSprite->SetSrc(768, 416, 32, 14);
	m_fRotate = 0.0f;
	m_fScale = 1.0f;
	m_fAlpha = 1.0f;
	BoomRangeHit = 0;

	m_nHp = m_nMaxHp;

	m_nCnt1 = 0;
	m_nCnt2 = 0;



	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E���e�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponBoomObj::Update()
{
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			switch (m_dwStatusPhase)
			{
			case 0:
				if (m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this)||m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this)|| m_pGMain->m_pWeaponProc->m_pWeaponShotProc->Hitcheck((CBaseObj*)this)|| m_pGMain->m_pWeaponProc->m_pWeaponCharShotProc->Hitcheck((CBaseObj*)this)|| m_pGMain->m_pWeaponProc->m_pWeaponDifShotProc->Hitcheck((CBaseObj*)this)|| m_pGMain->m_pWeaponProc->m_pWeaponBoundShotProc->Hitcheck((CBaseObj*)this)|| m_pGMain->m_pWeaponProc->m_pWeaponProAtkProc->Hitcheck((CBaseObj*)this))
				{   
					BoomRangeHit=1;
					// �G�ɓ���������
					m_vPos.x -= ((64 - 32) / 2);   // �����X�v���C�g�ɕύX
					m_vPos.y -= ((64 - 14) / 2);   // �����X�v���C�g�ɕύX
					ResetAnim();
					m_pSprite->SetSrc(512, 448, 64, 64);
					m_fAlpha = 0.7f;
					m_fScale = 1.0f;
					m_nAnimNum = 2;
					m_nHp = 0;
					m_pOtherObj = NULL;
					m_dwStatusPhase = 1;   // ����������
				}
				break;

			case 1:
				m_fScale += 0.25;     // �������������Âg�債�Ă���
				if (m_fScale > 5) {
					m_bActive = false;
				}
				m_vOf.x = -(m_fScale * m_pSprite->GetSrcWidth() / 2);     // �g��ɍ��킹�ĕ\���ʒu���Â炵�Ă���
				m_vOf.y = -(m_fScale * m_pSprite->GetSrcHeight() / 2);
				break;
			}

			// �����̌v�Z
			m_vPos += m_vPosUp;

			if (m_dwOwner == PC) // PC�����˂����e
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				if (BoomRangeHit == 1) {
					m_pGMain->m_pWeaponProc->m_pWeaponBoomProc->Hitcheck((CBaseObj*)this);
				}
			}
			else { //  �G�����˂����e
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				//m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}

			if (m_vPos.x < 0 || m_vPos.x > WINDOW_WIDTH ||
				m_vPos.y < 0 || m_vPos.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}
			

			if (m_pGMain->m_nBoomStop == 1) {
				m_bActive = FALSE;
			}

		case  DAMAGE:
			m_dwStatus = NORMAL;
			break;
		}
		AnimCountup();
		Draw();
	}
}

//------------------------------------------------------------------------
//
//	����E�ߐڍU���v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponProAtkProc::CWeaponProAtkProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�ߐڍU��
	for (DWORD i = 0; i < WEAPON_PROATK_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponProAtkObj(m_pGMain));	// m_pObjArray�ɕ���E�ߐڍU���I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�ߐڍU���v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponProAtkProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�ߐڍU���I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponProAtkObj::CWeaponProAtkObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 396, 24, 24);
	m_nAnimNum = 1;

	m_nAtc = 70;
}
// ---------------------------------------------------------------------------
//
// ����E�ߐڍU���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponProAtkObj::~CWeaponProAtkObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�ߐڍU���I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponProAtkObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// �e�̑���
	//int Time = 1000;


	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);

	if (m_pGMain->m_nDirection == 0)
	{
		m_vPos.x = m_pGMain->m_nPcpositionx + 50.0f;
		m_vPos.y = m_pGMain->m_nPcpositiony + 10;
	}
	else if (m_pGMain->m_nDirection == 1)
	{
		m_vPos.x = m_pGMain->m_nPcpositionx - 30.0f;
		m_vPos.y = m_pGMain->m_nPcpositiony + 10;

	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�ߐڍU���I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponProAtkObj::Update()
{
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			/*if (m_pGMain->m_nProAtkStop == 0) 
			{
				m_bActive = FALSE;
			}*/
			if (m_pGMain->m_nProAtkStop==1) 
			{
				if (TimeSave <= 1) 
				{
					Time++;
					TimeSave = Time / 10;
					
				}
				else {
					m_bActive = FALSE;
					Time = 0;
					TimeSave = 0;
					m_pGMain->m_nProAtkStop = 0;
				}
				
			}
			if (m_pGMain->m_nDirection == 0)
			{
				m_vPos.x = m_pGMain->m_nPcpositionx + 50.0f;
				m_vPos.y = m_pGMain->m_nPcpositiony + 10;
			}
			else if (m_pGMain->m_nDirection == 1)
			{
				m_vPos.x = m_pGMain->m_nPcpositionx - 30.0f;
				m_vPos.y = m_pGMain->m_nPcpositiony + 10;

			}

			if (m_dwOwner == PC) // PC�����˂����e
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  �G�����˂����e
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}

			break;

		case  DAMAGE:
			m_bActive = FALSE;
			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}

//------------------------------------------------------------------------
//
//	����E�g�U�V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponDifShotProc::CWeaponDifShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�g�U�V���b�g
	for (DWORD i = 0; i < WEAPON_DIFSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponDifShotObj(m_pGMain));	// m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 32;

}

//-----------------------------------------------------------------------------
// ����E�g�U�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponDifShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;
	DWORD  dwNum;

	

	dwNum = 4;
	for (DWORD n = 0; n < dwNum; n++)
	{

		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				((CWeaponDifShotObj*)(m_pObjArray[i]))->Start(vPos, pObj,n, dwOwner);	// ����̔���

				m_pGMain->m_pSeHit->Play();
				bRet = TRUE;
				break;
			}
		}

	}

	
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���

	return bRet;
}


//------------------------------------------------------------------------
//
//	����E�g�U�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponDifShotObj::CWeaponDifShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 48, 320, 16, 32);
	m_nAnimNum = 1;

	m_nAtc = 20;
}
// ---------------------------------------------------------------------------
//
// ����E�g�U�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponDifShotObj::~CWeaponDifShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�g�U�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponDifShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwNo,  DWORD dwOwner)
{
	float fSpeed = 8;	// �e�̑���

	

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu

	switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		
		m_vPosUp.x = -sin(XMConvertToRadians(dwNo * 12.0f - 102)) * fSpeed;
		m_vPosUp.y = cos(XMConvertToRadians(dwNo * 12.0f - 102)) * fSpeed;
		m_fRotate = dwNo * 12.0f - 102;

		break;
	case LEFT:
		m_vPosUp.x = -sin(XMConvertToRadians(dwNo * 12.0f - 102)) * -fSpeed;
		m_vPosUp.y = cos(XMConvertToRadians(dwNo * 12.0f - 102)) * -fSpeed;
		m_fRotate = dwNo * 12.0f - 102;

		break;
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�g�U�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponDifShotObj::Update()
{



	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:

			if (m_dwOwner == PC) // PC�����˂����e
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  �G�����˂����e
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				m_nAtc = 100;

			}
			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}
			
			break;

		case  DAMAGE:
			m_bActive = FALSE;
			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}

//------------------------------------------------------------------------
//
//	����E�`���[�W�V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponCharShotProc::CWeaponCharShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�`���[�W�V���b�g
	for (DWORD i = 0; i < WEAPON_CHARSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponCharShotObj(m_pGMain));	// m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�`���[�W�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponCharShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�`���[�W�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponCharShotObj::CWeaponCharShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 40;
}
// ---------------------------------------------------------------------------
//
// ����E�`���[�W�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponCharShotObj::~CWeaponCharShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�`���[�W�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponCharShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// �e�̑���

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	
	m_vSitPos = m_vPos.x;

	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:		
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�`���[�W�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponCharShotObj::Update()
{
	int CharShot = 0;
	float fSpeed = 8;	// �e�̑���

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  NORMAL:
			if (m_pGMain->m_nCharEnmhit == 1) 
			{
			if (m_dwOwner == PC) // PC�����˂����e
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);


			}
			else { //  �G�����˂����e
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


			}
			}
			if (m_pGMain->m_nCharStop == 0)
			{
				if (m_pGMain->m_nDirection == 0)
				{
					m_vPos.x = m_pGMain->m_nPcpositionx + 50.0f;
					m_vPos.y = m_pGMain->m_nPcpositiony + 10;
					m_vPosUp = VECTOR2(fSpeed, 0);

				}
				else if (m_pGMain->m_nDirection == 1)
				{
					m_vPos.x = m_pGMain->m_nPcpositionx - 30.0f;
					m_vPos.y = m_pGMain->m_nPcpositiony + 10;
					m_vPosUp = VECTOR2(-fSpeed, 0);

				}

			}
				if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
				{
					m_pGMain->m_nCharStop = 0;
					m_bActive = FALSE;

				}
			
			if (m_pGMain->m_nCharAmount >= 0)
			{
				CharShot = 0;
				CharShot = m_pGMain->m_nCharAmountSave/15;
					if (CharShot <= 3)
					{
						m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);
						m_nAtc = 50;
					}
					else {
						m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34, 32, 32);
						m_nAtc = 100;
					
				}
			}
			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_pGMain->m_nCharStop = 0;
				m_pGMain->m_nCharAmountSave = 0;
				m_pGMain->m_nCharAmount = 0;


				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_pGMain->m_nCharStop = 0;


				m_bActive = FALSE;
			

			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}

//========================================================================
//	����E�o�E���h�V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponBoundShotProc::CWeaponBoundShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�o�E���h�V���b�g
	for (DWORD i = 0; i < WEAPON_BOUNDSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponBoundShotObj(m_pGMain));	// m_pObjArray�ɕ���E�o�E���h�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�o�E���h�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponBoundShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�o�E���h�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponBoundShotObj::CWeaponBoundShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 194, 417, 30, 30);
	m_nAnimNum = 1;

	m_nAtc = 20;
}
// ---------------------------------------------------------------------------
//
// ����E�o�E���h�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBoundShotObj::~CWeaponBoundShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�o�E���h�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponBoundShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// �e�̑���
	fSpeedx = 0;
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_vSitPos = m_vPos.x;
	BoundNum = 1;
	y = 0;

	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�o�E���h�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponBoundShotObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;


	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:



			if (m_dwOwner == PC) // PC�����˂����e
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  �G�����˂����e
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


			}

			if(m_pGMain->m_nDirection == 0)
			{
				fSpeedx=1.5;
			}
			else if (m_pGMain->m_nDirection == 1)
			{
				fSpeedx = -1.5;

			}


			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}


		switch (m_dwStatusSub) {

		case  WALK:


			// �W�����v�J�n
			if (BoundNum == 1) {
				m_dwStatusSub = JUMP;
				m_vPosUp.x = fSpeedx;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -(fJumpSpeed + (fJumpPlus/3));
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}else if (BoundNum == 2) {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -y*0.75;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}
			else if (BoundNum == 3) {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -y*0.75;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y/2;
				//m_nDirIdx = UP;
			}

			else {
				m_bActive = FALSE;
			}


			break;

		case  JUMP:		// �W�����v���̏���
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + (GRAVITY/6) * m_fJumpTime);
			y = m_vPosUp.y;
			break;

		}
	}
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
		{
			m_dwStatusSub = WALK;	// �}�b�v���ɐڐG���Ă���Ƃ��́A�W�����v����s�ɖ߂�
			BoundNum++;
		}
	}
	
	// ����
	m_vPos += m_vPosUp;

	AnimCountup();
	Draw();


}



//------------------------------------------------------------------------
//
//	����E�I�I�J�~�X�y�V�����v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponSpWolfShotProc::CWeaponSpWolfShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�I�I�J�~�X�y�V�����V���b�g
	for (DWORD i = 0; i < WEAPON_SPWOLFSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponSpWolfShotObj(m_pGMain));	// m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 32;

}

//-----------------------------------------------------------------------------
// ����E�I�I�J�~�X�y�V�����V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponSpWolfShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;
	DWORD  dwNum;



	dwNum = 25;
	for (DWORD n = 0; n < dwNum; n++)
	{

		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				((CWeaponSpWolfShotObj*)(m_pObjArray[i]))->Start(vPos, pObj, n, dwOwner);	// ����̔���

				m_pGMain->m_pSeHit->Play();
				bRet = TRUE;
				break;
			}
		}

	}


	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���

	return bRet;
}


//------------------------------------------------------------------------
//
//	����E�I�I�J�~�X�y�V�����V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponSpWolfShotObj::CWeaponSpWolfShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 48, 320, 16, 32);
	m_nAnimNum = 1;

	m_nAtc = 80;
}
// ---------------------------------------------------------------------------
//
// ����E�I�I�J�~�X�y�V�����V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponSpWolfShotObj::~CWeaponSpWolfShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�I�I�J�~�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponSpWolfShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwNo, DWORD dwOwner)
{
	float fSpeed =6;	// �e�̑���



	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu

	switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:

		m_vPosUp.x = -sin(XMConvertToRadians(dwNo * 15.0f - 102)) * fSpeed;
		m_vPosUp.y = cos(XMConvertToRadians(dwNo * 15.0f - 102)) * fSpeed;
		m_fRotate = dwNo * 12.0f - 102;

		break;
	case LEFT:
		m_vPosUp.x = -sin(XMConvertToRadians(dwNo * 15.0f - 102)) * -fSpeed;
		m_vPosUp.y = cos(XMConvertToRadians(dwNo * 15.0f - 102)) * -fSpeed;
		m_fRotate = dwNo * 15.0f - 102;

		break;
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�I�I�J�~�X�y�V�����V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponSpWolfShotObj::Update()
{



	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			if (m_dwOwner == PC) // PC�����˂����e
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  �G�����˂����e
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


			}
			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}

			break;

		case  DAMAGE:
			m_bActive = FALSE;
			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}

//------------------------------------------------------------------------
//
//	����E�I�I�J�~�V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponWolfShotProc::CWeaponWolfShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�I�I�J�~�V���b�g
	for (DWORD i = 0; i < WEAPON_DIFSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponWolfShotObj(m_pGMain));	// m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 32;

}

//-----------------------------------------------------------------------------
// ����E�I�I�J�~�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponWolfShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;
	DWORD  dwNum;



	dwNum = 4;
	for (DWORD n = 0; n < dwNum; n++)
	{

		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				((CWeaponWolfShotObj*)(m_pObjArray[i]))->Start(vPos, pObj, n, dwOwner);	// ����̔���

				m_pGMain->m_pSeHit->Play();
				bRet = TRUE;
				break;
			}
		}

	}


	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���

	return bRet;
}


//------------------------------------------------------------------------
//
//	����E�I�I�J�~�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponWolfShotObj::CWeaponWolfShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 48, 320, 16, 32);
	m_nAnimNum = 1;


	m_nAtc = 80;
}
// ---------------------------------------------------------------------------
//
// ����E�I�I�J�~�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponWolfShotObj::~CWeaponWolfShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�I�I�J�~�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponWolfShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwNo, DWORD dwOwner)
{
	float fSpeed = 8;	// �e�̑���



	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu

	switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:

		m_vPosUp.x = -sin(XMConvertToRadians(dwNo * 12.0f - 102)) * fSpeed;
		m_vPosUp.y = cos(XMConvertToRadians(dwNo * 12.0f - 102)) * fSpeed;
		m_fRotate = dwNo * 12.0f - 102;

		break;
	case LEFT:
		m_vPosUp.x = -sin(XMConvertToRadians(dwNo * 12.0f - 102)) * -fSpeed;
		m_vPosUp.y = cos(XMConvertToRadians(dwNo * 12.0f - 102)) * -fSpeed;
		m_fRotate = dwNo * 12.0f - 102;

		break;
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�I�I�J�~�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponWolfShotObj::Update()
{



	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			if (m_dwOwner == PC) // PC�����˂����e
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  �G�����˂����e
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				m_nAtc = 100;

			}
			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}

			break;

		case  DAMAGE:
			m_bActive = FALSE;
			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}


//------------------------------------------------------------------------
//
//	����E�t�H�b�N�X�V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponFoxShotProc::CWeaponFoxShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�t�H�b�N�X�V���b�g
	for (DWORD i = 0; i < WEAPON_FOXSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponFoxShotObj(m_pGMain));	// m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�t�H�b�N�X�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponFoxShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�t�H�b�N�X�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponFoxShotObj::CWeaponFoxShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 100;
}
// ---------------------------------------------------------------------------
//
// ����E�t�H�b�N�X�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponFoxShotObj::~CWeaponFoxShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�t�H�b�N�X�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponFoxShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// �e�̑���

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu

//	m_vPos.x = Random(100,800);
//	m_vPos.y = Random(300, 730);

	m_vPosUp = VECTOR2(0, 0);

	m_vSitPos = m_vPos.x;
	CharShot = 0;
	CharMove = 0;


	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�t�H�b�N�X�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponFoxShotObj::Update()
{
	float fSpeed = 8;	// �e�̑���

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  NORMAL:
			if (m_vPosUp.x != 0|| m_vPosUp.y != 0) {
				if (m_dwOwner == PC) // PC�����˂����e
				{
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

				}
				else { //  �G�����˂����e
					m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


				}

			}

			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;

			}

			if (CharShot / 15 <= 3)
			{
				CharShot++;
				m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);
				if (CharShot / 15 > 2) {
					m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34, 32, 32);

				}
			}
			else {
				if (CharMove == 0) {
					
					/* if (m_vPos.y <= 600) 
					{
						m_vPosUp.y = fSpeed;

					}

					else */
					if (m_vPos.x <= m_pGMain->m_nPcpositionx)
					{
						m_vPosUp.x = fSpeed;
					}
					else {
						m_vPosUp.x = -fSpeed;

					}
					CharMove = 1;
				}
			}


			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���

				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}

//------------------------------------------------------------------------
//
//	����E�t�H�b�N�X�T�u�V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponFoxSubShotProc::CWeaponFoxSubShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�t�H�b�N�X�T�u�V���b�g
	for (DWORD i = 0; i < WEAPON_FOXSUBSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponFoxSubShotObj(m_pGMain));	// m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�t�H�b�N�X�T�u�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponFoxSubShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�t�H�b�N�X�T�u�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponFoxSubShotObj::CWeaponFoxSubShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 40;
}
// ---------------------------------------------------------------------------
//
// ����E�t�H�b�N�X�T�u�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponFoxSubShotObj::~CWeaponFoxSubShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�t�H�b�N�X�T�u�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponFoxSubShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// �e�̑���

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu

	m_vPos.x = Random(100,800);
	m_vPos.y = Random(300, 500);

	m_vPosUp = VECTOR2(0, 0);

	m_vSitPos = m_vPos.x;
	CharShot = 0;
	CharMove = 0;


	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�t�H�b�N�X�T�u�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponFoxSubShotObj::Update()
{
	float fSpeed = 8;	// �e�̑���

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  NORMAL:
			if (m_vPosUp.x != 0 || m_vPosUp.y != 0) {
				if (m_dwOwner == PC) // PC�����˂����e
				{
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

				}
				else { //  �G�����˂����e
					m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


				}

			}

			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;

			}

			if (CharShot / 15 <= 3)
			{
				CharShot++;
				m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);

			}
			else {
				if (CharMove == 0) {
					m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34, 32, 32);
						m_vPosUp.y = fSpeed;


					CharMove = 1;
				}
			}


			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���

				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}


//------------------------------------------------------------------------
//
//	����E�t�H�b�N�X�X�y�V�����V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponFoxSpShotProc::CWeaponFoxSpShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�t�H�b�N�X�X�y�V�����V���b�g
	for (DWORD i = 0; i < WEAPON_FOXSPSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponFoxSpShotObj(m_pGMain));	// m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�t�H�b�N�X�X�y�V�����V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponFoxSpShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�t�H�b�N�X�X�y�V�����V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponFoxSpShotObj::CWeaponFoxSpShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 100;
}
// ---------------------------------------------------------------------------
//
// ����E�t�H�b�N�X�X�y�V�����V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponFoxSpShotObj::~CWeaponFoxSpShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�t�H�b�N�X�X�y�V�����V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponFoxSpShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// �e�̑���

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu

	


	m_vPosUp = VECTOR2(0, 0);

	//m_vSitPos = m_vPos.x;
	CharShot = 0;
	PosxSave = m_vPos.x;
	PosySave = m_vPos.y;
	WeponNumx= 0;
	WeponNumy = 0;
	PcPosxSave = 0;
	PcPosySave = 0;
	SpCharMove = m_pGMain->m_nSpCharMove;
	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�t�H�b�N�X�X�y�V�����V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponFoxSpShotObj::Update()
{
	float fSpeed = 8;	// �e�̑���

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  NORMAL:



			if (m_vPosUp.x != 0 || m_vPosUp.y != 0) {
				if (m_dwOwner == PC) // PC�����˂����e
				{
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

				}
				else { //  �G�����˂����e
					m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


				}

			}

			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;

			}

			if (CharShot <= SpCharMove)
			{
				CharShot++;
				m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);
				PcPosxSave = m_pGMain->m_nPcpositionx;
				PcPosySave = m_pGMain->m_nPcpositiony;
				if (CharShot > SpCharMove-15) {
					m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34, 32, 32);

				}

			}
			else {

					/*/m_vPosUp.y = fSpeed;
					/if (PcPosySave >= PosySave) {
						//WeponNumy = ((PosySave / (PcPosySave / 100)) / 100);
						m_vPosUp.y = fSpeed;
					}
					else if(PcPosySave < PosySave) {
						//WeponNumy = ((PcPosySave / (PosySave / 100)) / 100);
						m_vPosUp.y = -fSpeed;

					}
					if (PcPosxSave >= PosxSave) {
						WeponNumx = ((PosxSave / (PcPosxSave / 100)) / 100);

					}
					else if (PcPosxSave < PosxSave) {
						WeponNumx = ((PcPosxSave / (PosxSave / 100)) / 100);
					}
					//m_vPosUp.y = ((PcPosySave - PosySave) / 30)*(WeponNumy);
					m_vPosUp.x = ((PcPosxSave - PosxSave) / 30)*(WeponNumx);*/
					/*x = ((PcPosxSave - PosxSave) / 2);
					y = ((PcPosySave - PosySave) / 2);

					m_vPosUp.y = ((PcPosySave - PosySave) / y);
					m_vPosUp.x = ((PcPosxSave - PosxSave) / x);*/
					

					float tan = atan2(PcPosySave- PosySave, PcPosxSave - PosxSave);
				
					m_vPosUp.x= cos(tan)*fSpeed;
					m_vPosUp.y = sin(tan)*fSpeed;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < -300 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH +300||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT+300) {	// ��ʊO�֏o���̂ŏ���

				m_bActive = FALSE;
			}



			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}

//------------------------------------------------------------------------
//
//	����E���ܒ��F�V���b�g �v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponTordBrownShotProc::CWeaponTordBrownShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E���ܒ��F�V���b�g
	for (DWORD i = 0; i < WEAPON_TORDBROWNSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponTordBrownShotObj(m_pGMain));	// m_pObjArray�ɕ���E���ܒ��F�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E���ܒ��F�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordBrownShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E���ܒ��F�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponTordBrownShotObj::CWeaponTordBrownShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite2, 768, 416, 32, 14);
	m_nAnimNum = 1;

	m_nAtc = 200;
}
// ---------------------------------------------------------------------------
//
// ����E���ܒ��F�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponTordBrownShotObj::~CWeaponTordBrownShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E���ܒ��F�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordBrownShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu
	m_vOf = VECTOR2(0, 0);
	m_vTarget = VECTOR2(0, 0);
	m_vPosUp = VECTOR2(0, 0);

	m_pSprite->SetSrc(768, 416, 32, 14);
	m_fRotate = 0.0f;
	m_fScale = 1.0f;
	m_fAlpha = 1.0f;

	m_nHp = m_nMaxHp;
	BoomTime = 0;

	m_nCnt1 = 0;
	m_nCnt2 = 0;


	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E���ܒ��F�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponTordBrownShotObj::Update()
{
	if (m_bActive)
	{
		int fSpeed = 8;
		switch (m_dwStatus)
		{
		case  NORMAL:

			switch (m_dwStatusPhase)
			{
			case 0:

				if (m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this) ||BoomTime/15>=10)
				{   // �G�ɓ���������
					m_vPos.x -= ((64 - 32) / 2);   // �����X�v���C�g�ɕύX
					m_vPos.y -= ((64 - 14) / 2);   // �����X�v���C�g�ɕύX
					ResetAnim();
					m_pSprite->SetSrc(512, 448, 64, 64);
					m_fAlpha = 0.7f;
					m_fScale = 1.0f;
					m_nAnimNum = 2;
					m_nHp = 0;
					m_pOtherObj = NULL;
					m_dwStatusPhase = 1;   // ����������
				}
				else if (m_pGMain->m_pWeaponProc->m_pWeaponShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponCharShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponDifShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponBoundShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponProAtkProc->Hitcheck((CBaseObj*)this))
				{
					EnmHit = 1;
					// �G�ɓ���������
					m_vPos.x -= ((64 - 32) / 2);   // �����X�v���C�g�ɕύX
					m_vPos.y -= ((64 - 14) / 2);   // �����X�v���C�g�ɕύX
					ResetAnim();
					m_pSprite->SetSrc(512, 448, 64, 64);
					m_fAlpha = 0.7f;
					m_fScale = 1.0f;
					m_nAnimNum = 2;
					m_nHp = 0;
					m_pOtherObj = NULL;
					m_dwStatusPhase = 1;
				}
				BoomTime++;
				break;

			case 1:
				m_fScale += 0.15;     // �������������Âg�債�Ă���
				if (m_fScale > 3.5) {
					m_bActive = false;
					EnmHit = 0;
				}
				m_vOf.x = -(m_fScale * m_pSprite->GetSrcWidth() / 2);     // �g��ɍ��킹�ĕ\���ʒu���Â炵�Ă���
				m_vOf.y = -(m_fScale * m_pSprite->GetSrcHeight() / 2);
				break;
			}

			// �����̌v�Z
			m_vPos += m_vPosUp;

			if (m_dwOwner == PC) // PC�����˂����e
			{
				//m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);
				//m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			}
			else { //  �G�����˂����e
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				if (EnmHit == 1) {
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);
					
				}
			}

			if (m_vPos.x < 0 || m_vPos.x > WINDOW_WIDTH ||
				m_vPos.y < 0 || m_vPos.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}
			if (m_pGMain->m_nDoorStop[3] == 1)
			{
				m_bActive = FALSE;
			}
		
			break;

		case  DAMAGE:
			m_dwStatus = NORMAL;
			break;
		}
		AnimCountup();
		Draw();
	}
}

//------------------------------------------------------------------------
//
//	����E���ܒ��F�X�y�V�����V���b�g �v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponTordBrownSpShotProc::CWeaponTordBrownSpShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E���ܒ��F�X�y�V�����V���b�g
	for (DWORD i = 0; i < WEAPON_TORDBROWNSPSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponTordBrownSpShotObj(m_pGMain));	// m_pObjArray�ɕ���E���ܒ��F�X�y�V�����V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E���ܒ��F�X�y�V�����V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordBrownSpShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E���ܒ��F�X�y�V�����V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponTordBrownSpShotObj::CWeaponTordBrownSpShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite2, 768, 416, 32, 14);
	m_nAnimNum = 1;

	m_nAtc = 200;
}
// ---------------------------------------------------------------------------
//
// ����E���ܒ��F�X�y�V�����V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponTordBrownSpShotObj::~CWeaponTordBrownSpShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E���ܒ��F�X�y�V�����V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordBrownSpShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu
	m_vOf = VECTOR2(0, 0);
	m_vTarget = VECTOR2(0, 0);
	m_vPosUp = VECTOR2(0, 0);

	m_pSprite->SetSrc(768, 416, 32, 14);
	m_fRotate = 0.0f;
	m_fScale = 1.0f;
	m_fAlpha = 1.0f;

	m_nHp = m_nMaxHp;
	BoomTime = 0;

	m_nCnt1 = 0;
	m_nCnt2 = 0;
	 fSpeed = Random(2, 8);



	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E���ܒ��F�X�y�V�����V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponTordBrownSpShotObj::Update()
{
	CMapLine*  pHitmapline = NULL;

	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:

			switch (m_dwStatusPhase)
			{
			case 0:

				if (m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this) )
				{   // �G�ɓ���������

					m_vPosUp.x = 0;
					m_vPosUp.y = 0;
					m_vPos.x -= ((64 - 32) / 2);   // �����X�v���C�g�ɕύX
					m_vPos.y -= ((64 - 14) / 2);   // �����X�v���C�g�ɕύX
					ResetAnim();
					m_pSprite->SetSrc(512, 448, 64, 64);
					m_fAlpha = 0.7f;
					m_fScale = 1.0f;
					m_nAnimNum = 2;
					m_nHp = 0;
					m_pOtherObj = NULL;
					m_dwStatusPhase = 1;   // ����������
				}
				else if (m_pGMain->m_pWeaponProc->m_pWeaponShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponCharShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponDifShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponBoundShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponProAtkProc->Hitcheck((CBaseObj*)this))
				{
					m_vPosUp.x = 0;
					m_vPosUp.y = 0;
					EnmHit = 1;
					// �G�ɓ���������
					m_vPos.x -= ((64 - 32) / 2);   // �����X�v���C�g�ɕύX
					m_vPos.y -= ((64 - 14) / 2);   // �����X�v���C�g�ɕύX
					ResetAnim();
					m_pSprite->SetSrc(512, 448, 64, 64);
					m_fAlpha = 0.7f;
					m_fScale = 1.0f;
					m_nAnimNum = 2;
					m_nHp = 0;
					m_pOtherObj = NULL;
					m_dwStatusPhase = 1;
				}
				else if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
				{
					if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
					{
						m_vPosUp.x = 0;
						m_vPosUp.y = 0;
						// �G�ɓ���������
						m_vPos.x -= ((64 - 32) / 2);   // �����X�v���C�g�ɕύX
						m_vPos.y -= ((64 - 14) / 2);   // �����X�v���C�g�ɕύX
						ResetAnim();
						m_pSprite->SetSrc(512, 448, 64, 64);
						m_fAlpha = 0.7f;
						m_fScale = 1.0f;
						m_nAnimNum = 2;
						m_nHp = 0;
						m_pOtherObj = NULL;
						m_dwStatusPhase = 1;

					}
				}


			
				break;

			case 1:
				m_fScale += 0.15;     // �������������Âg�債�Ă���
				if (m_fScale > 3.5) {
					m_bActive = false;
					EnmHit = 0;
				}
				m_vOf.x = -(m_fScale * m_pSprite->GetSrcWidth() / 2);     // �g��ɍ��킹�ĕ\���ʒu���Â炵�Ă���
				m_vOf.y = -(m_fScale * m_pSprite->GetSrcHeight() / 2);
				break;
			}

			m_fRotate = 270;
			m_vPosUp.y = fSpeed;



			// �����̌v�Z
			m_vPos += m_vPosUp;

			if (m_dwOwner == PC) // PC�����˂����e
			{
				//m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);
				//m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			}
			else { //  �G�����˂����e
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				if (EnmHit == 1) {
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

				}
			}

			if (m_vPos.x < 0 || m_vPos.x > WINDOW_WIDTH ||
				m_vPos.y < 0 || m_vPos.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}
			if (m_pGMain->m_nDoorStop[3] == 1)
			{
				m_bActive = FALSE;
			}

			break;

		case  DAMAGE:
			m_dwStatus = NORMAL;
			break;
		}

		AnimCountup();
		Draw();
	}
}

//========================================================================
//	����E�K�}�V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponTordShotProc::CWeaponTordShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�K�}�V���b�g
	for (DWORD i = 0; i < WEAPON_TORDSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponTordShotObj(m_pGMain));	// m_pObjArray�ɕ���E�K�}�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�K�}�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�K�}�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponTordShotObj::CWeaponTordShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 194, 417, 30, 30);
	m_nAnimNum = 1;

	m_nAtc = 80;
}
// ---------------------------------------------------------------------------
//
// ����E�K�}�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponTordShotObj::~CWeaponTordShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�K�}�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	fSpeedx = 0;
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_vSitPos = m_vPos.x;
	BoundNum = 1;
	Boundy = 0;
	if (Random(0, 1) == 0) {
		fSpeedx = 1.5;
	}
	else {
		fSpeedx = -1.5;

	}
	switch (pObj->GetDirIdx())
	{
	/*case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;*/
	case RIGHT:
		fSpeedx = 1.5;
		break;
	case LEFT:
		fSpeedx = -1.5;
		break;
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�K�}�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponTordShotObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;


	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:



			if (m_dwOwner == PC) // PC�����˂����e
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  �G�����˂����e
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


			}



			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}


		switch (m_dwStatusSub) {

		case  WALK:


			// �W�����v�J�n
			if (BoundNum == 1) {
				m_dwStatusSub = JUMP;
				m_vPosUp.x = fSpeedx;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -(fJumpSpeed + (fJumpPlus / 3));
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}
			else if (BoundNum == 2) {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -Boundy * 0.75;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}
			else if (BoundNum == 3) {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -Boundy * 0.75;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y / 2;
				//m_nDirIdx = UP;
			}

			else {
				m_bActive = FALSE;
			}


			break;

		case  JUMP:		// �W�����v���̏���
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + (GRAVITY / 6) * m_fJumpTime);
			Boundy = m_vPosUp.y;
			break;

		}
	}
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
		{
			m_dwStatusSub = WALK;	// �}�b�v���ɐڐG���Ă���Ƃ��́A�W�����v����s�ɖ߂�
			BoundNum++;
		}
	}

	// ����
	m_vPos += m_vPosUp;

	AnimCountup();
	Draw();


}

//========================================================================
//	����E�K�}�X�y�V�����V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponTordSpShotProc::CWeaponTordSpShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�K�}�X�y�V�����V���b�g
	for (DWORD i = 0; i < WEAPON_TORDSPSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponTordSpShotObj(m_pGMain));	// m_pObjArray�ɕ���E�K�}�X�y�V�����V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�K�}�X�y�V�����V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordSpShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�K�}�X�y�V�����V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponTordSpShotObj::CWeaponTordSpShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 526, 0, 200, 200);
	m_nAnimNum = 1;

	m_nAtc = 80;
}
// ---------------------------------------------------------------------------
//
// ����E�K�}�X�y�V�����V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponTordSpShotObj::~CWeaponTordSpShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�K�}�X�y�V�����V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordSpShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	fSpeedx = 0;
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu
	m_vPos.y = m_vPos.y - 200;
	m_vPos.x = m_vPos.x - 100;
	m_vPosUp = VECTOR2(0, 0);
	m_vSitPos = m_vPos.x;
	BoundNum = 0;
	PcPosxSave = m_pGMain->m_nPcpositionx;
	PcPosySave = m_pGMain->m_nPcpositiony;
	BoundTimeStop = 0;
	tan = 0;
	fSpeed = 5;
	//BoundNumMax = Random(5, 8);
	BoundNumMax = 7;
	StageWidth = 768;
	StageHeight = 536;
	switch (pObj->GetDirIdx())
	{
		/*case UP:
			m_vPosUp = VECTOR2(0, -fSpeed);
			break;
		case DOWN:
			m_vPosUp = VECTOR2(0, fSpeed);
			break;*/
	/*case RIGHT:
		fSpeedx = 4;
		break;
	case LEFT:
		fSpeedx = -4;
		break;*/
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�K�}�X�y�V�����V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponTordSpShotObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;


	if (m_bActive)
	{


			if (Random(0, 35) == 0)
			{
				if (m_nDifShotWait <= 0) {
						m_pGMain->m_pWeaponProc->m_pWeaponTordShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
						//m_pGMain->m_pWeaponProc->m_pWeaponTordSpShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
						m_nDifShotWait = 15;
					
				}
			}
			if (m_nDifShotWait > 0) m_nDifShotWait--;    // ���픭�˂̃E�F�C�g���J�E���g�_�E��
			



				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);

			



			/*if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}*/
			if (BoundNum == 0)
			{

					m_vPosUp.x = -fSpeed;
					m_vPosUp.y = fSpeed;
					BoundNum=1;

			}

			if (BoundNum == 1) {
				BoundTimeStop++;
			}

			if (BoundTimeStop/30 >10) {
				m_pGMain->m_nSpTordPosx = m_vPos.x;
				m_pGMain->m_nSpTordPosy = m_vPos.y;
				m_pGMain->m_nSpTordStop = 1;


			}
			if (m_pGMain->m_nSpTordStop == 1)
			{
				m_bActive = FALSE;

			}

		

		
		



	}






	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
			
				//m_vPosUp.x = 0;
				//m_vPosUp.y = 0;
		if (BoundTimeStop / 30 <= 10) {
			if(m_vPosUp.x >=0 && m_vPos.x >=840-200) {
				m_vPosUp.x = -fSpeed;
			}
			else if (m_vPosUp.x < 0 && m_vPos.x <= 110) {
				m_vPosUp.x = fSpeed;

			}			
			if (m_vPosUp.y >= 0 && m_vPos.y >= 750-200) {
				m_vPosUp.y = -fSpeed;
			}
			else if (m_vPosUp.y < 0 && m_vPos.y <= 250) {
				m_vPosUp.y = fSpeed;

			}



		}

		
	}


	// ����
	m_vPos += m_vPosUp;

	AnimCountup();
	Draw();


}

//========================================================================
//	����E�K�}�T�u�V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponTordSubShotProc::CWeaponTordSubShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�K�}�T�u�V���b�g
	for (DWORD i = 0; i < WEAPON_TORDSUBSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponTordSubShotObj(m_pGMain));	// m_pObjArray�ɕ���E�K�}�T�u�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�K�}�T�u�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordSubShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�K�}�T�u�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponTordSubShotObj::CWeaponTordSubShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 194, 417, 30, 30);
	m_nAnimNum = 1;

	m_nAtc = 80;
}
// ---------------------------------------------------------------------------
//
// ����E�K�}�T�u�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponTordSubShotObj::~CWeaponTordSubShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�K�}�T�u�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordSubShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	fSpeedx = 0;
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_vSitPos = m_vPos.x;
	BoundNum = 1;
	Boundy = 0;

	switch (pObj->GetDirIdx())
	{
		/*case UP:
			m_vPosUp = VECTOR2(0, -fSpeed);
			break;
		case DOWN:
			m_vPosUp = VECTOR2(0, fSpeed);
			break;*/
	case RIGHT:
		if (Random(0, 1) == 0) {
			fSpeedx = 1.5;
		}
		else {
			fSpeedx = -1.5;

		}
		break;
	case LEFT:
		if (Random(0, 1) == 0) {
			fSpeedx = 1.5;
		}
		else {
			fSpeedx = -1.5;

		}

		break;
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�K�}�T�u�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponTordSubShotObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;


	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:



			if (m_dwOwner == PC) // PC�����˂����e
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  �G�����˂����e
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


			}



			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}


		switch (m_dwStatusSub) {

		case  WALK:


			// �W�����v�J�n
			if (BoundNum == 1) {
				m_dwStatusSub = JUMP;
				m_vPosUp.x = fSpeedx;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -(fJumpSpeed + (fJumpPlus / 3));
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}
			else if (BoundNum == 2) {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -Boundy * 0.75;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}
			else if (BoundNum == 3) {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -Boundy * 0.75;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y / 2;
				//m_nDirIdx = UP;
			}

			else {
				m_bActive = FALSE;
			}


			break;

		case  JUMP:		// �W�����v���̏���
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + (GRAVITY / 6) * m_fJumpTime);
			Boundy = m_vPosUp.y;
			break;

		}
	}
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
		{
			m_dwStatusSub = WALK;	// �}�b�v���ɐڐG���Ă���Ƃ��́A�W�����v����s�ɖ߂�
			BoundNum++;
		}
	}

	// ����
	m_vPos += m_vPosUp;

	AnimCountup();
	Draw();


}


//------------------------------------------------------------------------
//
//	����E�Ō�̓G�T�u�V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmLastSubShotProc::CEnmLastSubShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�Ō�̓G�T�u�V���b�g
	for (DWORD i = 0; i < WEAPON_ENMLASTSUBSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmLastSubShotObj(m_pGMain));	// m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�Ō�̓G�T�u�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSubShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�Ō�̓G�T�u�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmLastSubShotObj::CEnmLastSubShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 40;
}
// ---------------------------------------------------------------------------
//
// ����E�Ō�̓G�T�u�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmLastSubShotObj::~CEnmLastSubShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�Ō�̓G�T�u�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSubShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 2;	// �e�̑���

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu




	m_vPosUp = VECTOR2(0, 0);

	//m_vSitPos = m_vPos.x;
	CharShot = 0;
	PosxSave = m_vPos.x;
	PosySave = m_vPos.y;
	WeponNumx = 0;
	WeponNumy = 0;
	PcPosxSave = 0;
	PcPosySave = 0;
	SpCharMove = m_pGMain->m_nSpCharMove;
	ShotStart = 0;
	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�Ō�̓G�T�u�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmLastSubShotObj::Update()
{
	float fSpeed = 8;	// �e�̑���

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  NORMAL:

			if (m_vPosUp.x != 0 || m_vPosUp.y != 0) {
				if (m_dwOwner == PC) // PC�����˂����e
				{
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

				}
				else { //  �G�����˂����e
					m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


				}

			}

			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;

			}


			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}



			if (ShotStart == 0)
			{

				PcPosxSave = m_pGMain->m_nPcpositionx;
				PcPosySave = m_pGMain->m_nPcpositiony;
				ShotStart = 1;

			}
			else {

				/*/m_vPosUp.y = fSpeed;
				/if (PcPosySave >= PosySave) {
					//WeponNumy = ((PosySave / (PcPosySave / 100)) / 100);
					m_vPosUp.y = fSpeed;
				}
				else if(PcPosySave < PosySave) {
					//WeponNumy = ((PcPosySave / (PosySave / 100)) / 100);
					m_vPosUp.y = -fSpeed;

				}
				if (PcPosxSave >= PosxSave) {
					WeponNumx = ((PosxSave / (PcPosxSave / 100)) / 100);

				}
				else if (PcPosxSave < PosxSave) {
					WeponNumx = ((PcPosxSave / (PosxSave / 100)) / 100);
				}
				//m_vPosUp.y = ((PcPosySave - PosySave) / 30)*(WeponNumy);
				m_vPosUp.x = ((PcPosxSave - PosxSave) / 30)*(WeponNumx);*/
				/*x = ((PcPosxSave - PosxSave) / 2);
				y = ((PcPosySave - PosySave) / 2);

				m_vPosUp.y = ((PcPosySave - PosySave) / y);
				m_vPosUp.x = ((PcPosxSave - PosxSave) / x);*/


				float tan = atan2(PcPosySave - PosySave, PcPosxSave - PosxSave);

				m_vPosUp.x = cos(tan)*fSpeed;
				m_vPosUp.y = sin(tan)*fSpeed;
			}


			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}


// =================================================================================

//------------------------------------------------------------------------
//
//	����E���[�U�[�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CWeaponLaserProc::CWeaponLaserProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E���[�U�[
	for (DWORD i = 0; i < WEAPON_LASER_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponLaserObj(m_pGMain));	// m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E���[�U�[�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponLaserProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E���[�U�[�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CWeaponLaserObj::CWeaponLaserObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite2, 148, 320, 8, 64);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 40;
}
// ---------------------------------------------------------------------------
//
// ����E���[�U�[�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponLaserObj::~CWeaponLaserObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E���[�U�[�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponLaserObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 2;	// �e�̑���

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu




	m_vPosUp = VECTOR2(0, 0);

	//m_vSitPos = m_vPos.x;
	CharShot = 0;
	PosxSave = m_vPos.x;
	PosySave = m_vPos.y;
	WeponNumx = 0;
	WeponNumy = 0;
	PcPosxSave = 0;
	PcPosySave = 0;
	SpCharMove = m_pGMain->m_nSpCharMove;
	ShotStart = 0;
	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E���[�U�[�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CWeaponLaserObj::Update()
{
	float fSpeed = 8;	// �e�̑���

	if (m_bActive)
	{

		

			switch (LaserPatten) {
			case 0:
				//�����[�U�[
				m_fRotate = 90;
				break;


			}


				if (m_dwOwner == PC) // PC�����˂����e
				{
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

				}
				else { //  �G�����˂����e
					m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


				}

			


			if (ShotStart == 0)
			{

				PcPosxSave = m_pGMain->m_nPcpositionx;
				PcPosySave = m_pGMain->m_nPcpositiony;
				ShotStart = 1;

			}
			else {

				/*/m_vPosUp.y = fSpeed;
				/if (PcPosySave >= PosySave) {
					//WeponNumy = ((PosySave / (PcPosySave / 100)) / 100);
					m_vPosUp.y = fSpeed;
				}
				else if(PcPosySave < PosySave) {
					//WeponNumy = ((PcPosySave / (PosySave / 100)) / 100);
					m_vPosUp.y = -fSpeed;

				}
				if (PcPosxSave >= PosxSave) {
					WeponNumx = ((PosxSave / (PcPosxSave / 100)) / 100);

				}
				else if (PcPosxSave < PosxSave) {
					WeponNumx = ((PcPosxSave / (PosxSave / 100)) / 100);
				}
				//m_vPosUp.y = ((PcPosySave - PosySave) / 30)*(WeponNumy);
				m_vPosUp.x = ((PcPosxSave - PosxSave) / 30)*(WeponNumx);*/
				/*x = ((PcPosxSave - PosxSave) / 2);
				y = ((PcPosySave - PosySave) / 2);

				m_vPosUp.y = ((PcPosySave - PosySave) / y);
				m_vPosUp.x = ((PcPosxSave - PosxSave) / x);*/


				float tan = atan2(PcPosySave - PosySave, PcPosxSave - PosxSave);

				/*m_vPosUp.x = cos(tan)*fSpeed;
				m_vPosUp.y = sin(tan)*fSpeed;
				*/
			}



		

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}

//------------------------------------------------------------------------
//
//	����E�Ō�̓G�X�y�V�����V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmLastSpShotProc::CEnmLastSpShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�Ō�̓G�X�y�V�����V���b�g
	for (DWORD i = 0; i < WEAPON_ENMLASTSPSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmLastSpShotObj(m_pGMain));	// m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�Ō�̓G�X�y�V�����V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSpShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�Ō�̓G�X�y�V�����V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmLastSpShotObj::CEnmLastSpShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite4, 400, 85, 250, 250);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 40;
}
// ---------------------------------------------------------------------------
//
// ����E�Ō�̓G�X�y�V�����V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmLastSpShotObj::~CEnmLastSpShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�Ō�̓G�X�y�V�����V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSpShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 2;	// �e�̑���

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu




	m_vPosUp = VECTOR2(0, 0);

	//m_vSitPos = m_vPos.x;
	CharShot = 0;
	PosxSave = m_vPos.x;
	PosySave = m_vPos.y;
	WeponNumx = 0;
	WeponNumy = 0;
	PcPosxSave = 0;
	PcPosySave = 0;
	SpCharMove = m_pGMain->m_nSpCharMove;
	ShotStart = 0;

	ShotTime = 0;
	SpTime = 0;
	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�Ō�̓G�X�y�V�����V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmLastSpShotObj::Update()
{
	float fSpeed = 8;	// �e�̑���

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  NORMAL:
			if(SpTime>=Random(300,500)){
				m_pGMain->m_nSpLastTrigger = 0;
				m_pGMain->m_nSpLastStop = 0;
				m_bActive = FALSE;

			}
			else {

				if (410 < m_pGMain->m_nPcpositionx) {
					m_pGMain->m_nSpLastTrigger = 1;
				}
				else if (410 >= m_pGMain->m_nPcpositionx) {
					m_pGMain->m_nSpLastTrigger = 2;

				}
				if (ShotTime <= 0) {
					m_pGMain->m_pWeaponProc->m_pEnmLastSpSubShotProc->Start(m_vPos + VECTOR2(Random(22, 172), Random(0, 80)), this, ENM);
					ShotTime = 5;
				}
				if (ShotTime > 0)ShotTime--;

				m_fRotate += 3;
				SpTime++;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}



			if (ShotStart == 0)
			{

				PcPosxSave = m_pGMain->m_nPcpositionx;
				PcPosySave = m_pGMain->m_nPcpositiony;
				ShotStart = 1;

			}
			else {

				/*/m_vPosUp.y = fSpeed;
				/if (PcPosySave >= PosySave) {
					//WeponNumy = ((PosySave / (PcPosySave / 100)) / 100);
					m_vPosUp.y = fSpeed;
				}
				else if(PcPosySave < PosySave) {
					//WeponNumy = ((PcPosySave / (PosySave / 100)) / 100);
					m_vPosUp.y = -fSpeed;

				}
				if (PcPosxSave >= PosxSave) {
					WeponNumx = ((PosxSave / (PcPosxSave / 100)) / 100);

				}
				else if (PcPosxSave < PosxSave) {
					WeponNumx = ((PcPosxSave / (PosxSave / 100)) / 100);
				}
				//m_vPosUp.y = ((PcPosySave - PosySave) / 30)*(WeponNumy);
				m_vPosUp.x = ((PcPosxSave - PosxSave) / 30)*(WeponNumx);*/
				/*x = ((PcPosxSave - PosxSave) / 2);
				y = ((PcPosySave - PosySave) / 2);

				m_vPosUp.y = ((PcPosySave - PosySave) / y);
				m_vPosUp.x = ((PcPosxSave - PosxSave) / x);*/


			}


			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}


//------------------------------------------------------------------------
//
//	����E�Ō�̓G�X�y�V�����T�u�V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmLastSpSubShotProc::CEnmLastSpSubShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ����E�Ō�̓G�X�y�V�����T�u�V���b�g
	for (DWORD i = 0; i < WEAPON_SHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmLastSpSubShotObj(m_pGMain));	// m_pObjArray�ɕ���E�Ō�̓G�X�y�V�����T�u�V���b�g�I�u�W�F�N�g�𐶐�����
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// ����E�Ō�̓G�X�y�V�����T�u�V���b�g�v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSpSubShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
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
//	����E�Ō�̓G�X�y�V�����T�u�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmLastSpSubShotObj::CEnmLastSpSubShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite4, 0, 380, 24, 24);
	m_nAnimNum = 1;

	m_nAtc = 1000;
}
// ---------------------------------------------------------------------------
//
// ����E�Ō�̓G�X�y�V�����T�u�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmLastSpSubShotObj::~CEnmLastSpSubShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�Ō�̓G�X�y�V�����T�u�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSpSubShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// �e�̑���
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_vSitPos = m_vPos.x;

	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// ����E�Ō�̓G�X�y�V�����T�u�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmLastSpSubShotObj::Update()
{
	CMapLine*  pHitmapline = NULL;

	float fSpeed = 8;

	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			m_vPosUp.y = fSpeed;
			if (m_dwOwner == PC) // PC�����˂����e
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);


			}
			else { //  �G�����˂����e
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


			}
			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}
			break;


			break;
		}
		if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
		{
			m_bActive = FALSE;
		}
		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}

