//=============================================================================
//
//		�f�����ʂ̏���
//																Effect.cpp
//=============================================================================

#include "Effect.h"
#include "Playchar.h"
#include "Map.h"

//------------------------------------------------------------------------
//
//	�f�����ʃ��C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEffectProc::CEffectProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pEffectBomProc = new CEffectBomProc(m_pGMain);	// �f�����ʁE�����v���V�[�W��
	m_pProcArray.push_back(m_pEffectBomProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pItemProc = new CItemProc(m_pGMain);				// �A�C�e���v���V�[�W��
	m_pProcArray.push_back(m_pItemProc);		// �v���V�[�W�����v���V�[�W���z��ɓo�^����

}
//============================================================================
//   �v���V�[�W���ƃI�u�W�F�N�g��T�����S�ẴI�u�W�F�N�g���m���A�N�e�B�u�ɂ���
//   �v���V�[�W���̊J�n�t���O�����Z�b�g����
//============================================================================
void  CEffectProc::SetNonActive()
{

	//�I�u�W�F�N�g�|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive( FALSE);
	}

	// ���ʂ̃v���V�[�W���|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetStartFlag(0);				// �J�n�t���O�̃��Z�b�g
		((CEffectProc*)m_pProcArray[i])->SetNonActive();      // ���ʂ̃v���V�[�W���̏����i�ċA�����j
	}
}


// ================================================================================================================================
// 
// �e�f�����ʃv���V�[�W�����̏���
// 
// ================================================================================================================================


//------------------------------------------------------------------------
//
//	�f�����ʁE�����v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEffectBomProc::CEffectBomProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < EFFECT_BOM_MAX; i++)
	{
		m_pObjArray.push_back(new CEffectBomObj(m_pGMain));	// m_pObjArray�ɉf�����ʁE�����I�u�W�F�N�g�𐶐�����
	}

}

//-----------------------------------------------------------------------------
// �f�����ʁE�����v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CEffectBomProc::Start(VECTOR2 vPos)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive() )
		{
			m_pObjArray[i]->Start(vPos);	// �f�����ʁE�����̔���
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}

	return TRUE;
}

//------------------------------------------------------------------------
//
//	�f�����ʁE�����I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEffectBomObj::CEffectBomObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 144, 480, 64, 64);
	m_nAnimNum = 7;

}
// ---------------------------------------------------------------------------
//
// �f�����ʁE�����I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEffectBomObj::~CEffectBomObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// �f�����ʁE�����I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CEffectBomObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	m_dwStatus = NORMAL;
	m_dwStatusSub = STOP;
	m_dwStatusPhase = 0;

	m_vPos = vPos;	// �����ʒu

	m_nAnimIdx = 0;

	return TRUE;
}
//-----------------------------------------------------------------------------
// �f�����ʁE�����I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEffectBomObj::Update()
{
	if (m_bActive)
	{
		if (AnimCountup() == 1)
		{
			m_bActive = FALSE;
		}
		Draw();

	}
}
// ==============================================================================================================

// =================================================================================
//------------------------------------------------------------------------
//
//	�A�C�e���v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CItemProc::CItemProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ITEM_MAX; i++)
	{
		m_pObjArray.push_back(new CItemObj(m_pGMain));	// m_pObjArray�ɃA�C�e���𐶐�����
	}
	m_nStartFlag = 0;
}

//-----------------------------------------------------------------------------
// �A�C�e���v���V�[�W���̊J�n
//
//   �߂�l�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CItemProc::Update()
{
	VECTOR2 vPos;
	int  nNext;

	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�~�}����ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T���@ ( EvtID:2�@�A�C�e���̏o���ʒu,  EvtNo:0x10 �~�}��	)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x10, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos, ITEMRESQUE);
						break;
					}
				}
			}
		}

		// �C�x���g�}�b�v��T�����A�h�A�i�o���j��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T���@ ( EvtID:2�@�A�C�e���̏o���ʒu,  EvtNo:0x20 �h�A	)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x20, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos, ITEMDOOR);
						break;
					}
				}
			}
		}

		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}

}

//------------------------------------------------------------------------
//
//	�A�C�e���I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CItemObj::CItemObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar);
	m_nAnimNum = 2;

}
// ---------------------------------------------------------------------------
//
// �A�C�e���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CItemObj::~CItemObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// �A�C�e���I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   DWORD       dwNo    �A�C�e�����
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CItemObj::Start(VECTOR2 vPos, DWORD dwNo)
{
	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_dwStatusSub = dwNo;

	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);

	switch (m_dwStatusSub)
	{
	case  ITEMRESQUE:     // �~�}��
		m_pSprite->SetSrc(384, 336, 48, 48);
		break;

	case  ITEMDOOR:      // �h�A
		m_pSprite->SetSrc(384, 288, 48, 48);   // �����F
		break;
	}

	return TRUE;
}
//-----------------------------------------------------------------------------
// �A�C�e���I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CItemObj::Update()
{
	if (!m_bActive) return;

	if (isCollision(m_pGMain->m_pPcProc->GetPcObjPtr())) // PC�Ƃ̐ڐG����
	{
		switch (m_dwStatusSub)
		{
		case  ITEMRESQUE:     // �~�}��
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetHp( m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaxHp());
			m_pGMain->m_pSePower->Play();
			break;

		case  ITEMDOOR:      // �h�A
			m_pGMain->m_pSePower->Play();
			m_pGMain->m_pMapProc->MoveMap();
			break;
		}
		m_bActive = FALSE;
	}

	AnimCountup();
	Draw();

}


