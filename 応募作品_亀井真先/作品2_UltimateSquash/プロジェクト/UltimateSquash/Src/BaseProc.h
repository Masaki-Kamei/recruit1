//=============================================================================
//
//		��{�v���V�[�W���E��{�I�u�W�F�N�g�N���X����
//																BaseProc.h
//=============================================================================
#pragma once
#include "GameMain.h"

#define		PLAYER	1
#define		TARGET	2
#define		BALL	3


// -------------------------------------------------------------------------------------------------
// 
// ��Ɏ��A�C�e����X�L�����w�肷��\����
// 
// -------------------------------------------------------------------------------------------------
struct BASEHOLDITEM
{
	int				m_nHoldObjNo;	// ��Ɏ��A�C�e���̃I�u�W�F�N�g�ԍ�
	int				m_nPosMesh;		// �A�C�e������������X�L�����b�V���̈ʒu�@���b�V���ԍ�
	int				m_nPosBone;		// �A�C�e������������X�L�����b�V���̈ʒu�@�{�[���ԍ�
	VECTOR3			m_nOffsetPos;	// ��Ɏ��A�C�e���̈ʒu�I�t�Z�b�g
	VECTOR3			m_nOffsetRot;	// ��Ɏ��A�C�e���̊p�x�I�t�Z�b�g
	BASEHOLDITEM()
	{
		m_nHoldObjNo = 0;				// ��Ɏ��A�C�e���̃I�u�W�F�N�g�ԍ�
		m_nPosMesh = 0;					// �A�C�e������������X�L�����b�V���̈ʒu�@���b�V���ԍ�
		m_nPosBone = 0;					// �A�C�e������������X�L�����b�V���̈ʒu�@�{�[���ԍ�
		m_nOffsetPos = VECTOR3(0, 0, 0);	// ��Ɏ��A�C�e���̈ʒu�I�t�Z�b�g
		m_nOffsetRot = VECTOR3(0, 0, 0);	// ��Ɏ��A�C�e���̊p�x�I�t�Z�b�g
	}
};

class CBBox;
class CShader;
class CGameMain;
class CBaseProc;
// --------------------------------------------------------------------------------------------------
// ��{�I�u�W�F�N�g�N���X
// 
// ���@�I�u�W�F�N�g�Ƃ́A�Q�[�����ɓo�ꂷ����̕��́A�Ⴆ�΂o�b��A�X�L���̂P�Ȃǂ��w���B
// �@�@�Ȃ��A�I�u�W�F�N�g�́A�e�v���V�[�W���̃����o�[�z��Ƃ��Đ錾����
// 
// --------------------------------------------------------------------------------------------------
class CBaseObj
{
protected:
	CGameMain*		m_pGMain;			// �Q�[�����C���N���X
	DWORD			m_dwStatus;			// �X�e�[�^�X
	DWORD			m_dwStatusSub;		// �X�e�[�^�X�T�u
	DWORD			m_dwStatusPhase;	// �X�e�[�^�X�t�F�[�Y
	BOOL			m_bActive;			// TRUE:�\��  FALSE:��\��
	DWORD			m_dwObjID;			// �I�u�W�F�N�g�h�c
	DWORD			m_dwObjNo;			// �I�u�W�F�N�g�m�n
	ANIMATION_STATUS m_AnimStatus;		// �A�j���[�V�����X�e�[�^�X
	CBBox*			m_pBBox;			// �o�E���f�B���O�{�b�N�X�N���X
	MATRIX4X4		m_mWorldOld;		// ���[���h�}�g���N�X�i��O�j
	MATRIX4X4		m_mWorld;			// ���[���h�}�g���N�X
	VECTOR3			m_vPosUp;			// �ړ�����
	VECTOR3			m_vRotUp;			// ��]����
	float			m_fJumpY;			// �W�����v����
	float			m_fJumpTime;		// �W�����v����
	CBaseObj*		m_pOyaObj;			// �e�I�u�W�F�N�g�i�X�L���I�u�W�F���j
	CBaseObj*		m_pHitObj;			// ������������̃I�u�W�F�N�g
	VECTOR3			m_vHitPos;			// ���������ꏊ�̍��W
	VECTOR3			m_vHitNormal;		// ���������ꏊ�̖@�����W
	int             m_nCnt1;			// �J�E���^�[�P
	int             m_nCnt2;			// �J�E���^�[�Q
	int				m_nMaxHp;			// �ő�̗�
	int				m_nHp;				// �̗�
	int				m_nAtc;				// �U����

	VECTOR3			m_vGravity;			// �d��


	float			m_fDist;
	BOOL			m_bDamage;			
	BOOL			bTarget;			//�^�[�Q�b�g����Ă��邩 
	
	CBaseObj*		m_pShaftObj;		//���ɂȂ�I�u�W�F�N�g	
	BOOL			bShaftObjTrigger;	//�͈͓��ɂ���̂��̔���
	float			m_fShaftDist;		//���Ƃ̋���

	DWORD			m_dWeaponUseNum;	//�g�p�ł���X�L���̐�
	DWORD			m_dwScorePoint;		//�I�u�W�F�N�g���Ƃ̃|�C���g

	BOOL			m_bStop;			//�I�u�W�F�N�g�̏������~�߂�

	DWORD			m_dwPlayerNo;
public:
	// �I�u�W�F�N�g�̔�������
	virtual BOOL	Start() { return TRUE; }
	virtual BOOL	Start(VECTOR3 vPos) { return TRUE; }
	virtual BOOL	Start(VECTOR3 vPos, DWORD dwPlayerNo) { return TRUE; }
	virtual BOOL	Start(VECTOR3 vPos, VECTOR3 vNormal) { return TRUE; }
	virtual BOOL	Start(VECTOR3 vPos, DWORD dwPlayerNo, VECTOR3 vNormal) { return TRUE; }
	virtual BOOL	Start(MATRIX4X4 mGun, DWORD dwOwner) { return TRUE; }
	virtual BOOL	Start(VECTOR3 vStart, VECTOR3 vTarget, DWORD dwOwner) { return TRUE; }
	virtual BOOL	Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner) { return TRUE; }
	virtual BOOL	Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner, DWORD dwPlayerNo) { return TRUE; }

	virtual BOOL	Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner) { return TRUE; }

	virtual	BOOL	Start(MATRIX4X4 mStartWorld, DWORD dwOwner, DWORD dNo) { return TRUE; }

	virtual BOOL	Start(VECTOR3 vPos,BOOL bTrigger) { return TRUE; }
	virtual BOOL	Start(MATRIX4X4 mStartWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner) { return TRUE; }
	virtual BOOL	Start(MATRIX4X4 mStartWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner, DWORD dwPlayerNo) { return TRUE; }


	// �����蔻�菈��
	virtual BOOL    Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld);
	virtual BOOL    Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack);

	virtual BOOL    HitcheckOtherLay(CBaseObj* pOtherObj);				

	virtual BOOL    ObjGravity(CBaseObj* pOtherObj, float fDist, float fRotateSpeed);			
	virtual BOOL    ObjTarget(CBaseObj* pOtherObj,  float fRotateSpeed);				
	virtual BOOL    ObjTerritory(CBaseObj* pOtherObj, float fDist);			//�͈͓����ǂ����𒲂ׂ�	

	virtual void	ObjBasicConstructor(const int nMaxHP, const int nAtc, VECTOR3 vMin, VECTOR3 vMax);
	virtual void	ObjReflection();
	virtual void	ObjAppearanceDirection(DWORD dPosStatus, MATRIX4X4 *m_mWorld);
	virtual void	ObjBasicDelete();
	virtual void	ObjRoundTrip(VECTOR3 vMin, VECTOR3 vMax);
	virtual void	ObjNavOccurrence(VECTOR3 vMin, VECTOR3 vMax);


	// �X�V����
	virtual	void    Update() { ; }

	// �ړI�n�ivTargetX,Z�j�ւ̈ړ�����
	// (�Ȃ��A��]�X�s�[�h�̏ȗ��l��3.0f�Ƃ���)
	virtual	BOOL    TargetMove(VECTOR3 vTarget, float fSpeedIn, float fRotSpeed = 3.0f);

	// �I�u�W�F�N�g���m���d�Ȃ�Ȃ��悤�ɂ��郁���o�֐�
	virtual	CBaseObj*	SetKeepOffset(CBaseProc* pProj);
	// �I�u�W�F�N�g��mWorld�ƈ����ʒu�Ƃ̋��������߂�
	virtual	float   GetDistance(VECTOR3 vPos);  
	// �X�e�[�^�X�����Z�b�g����
	virtual	void    ResetStatus();     

	virtual void	HitStatus(CBaseObj* pOtherObj, VECTOR3 vHit, VECTOR3 vNrm);
	virtual void	RotRig(float* fRotUp);

	// �A�N�Z�X�֐�
	BOOL	GetActive() { return m_bActive; }
	void	SetActive(BOOL bActive) { m_bActive = bActive; }
	DWORD	GetObjID() { return m_dwObjID; }		// �I�u�W�F�N�g�h�c
	void	SetObjID(DWORD dwObjID) { m_dwObjID = dwObjID; }		// �I�u�W�F�N�g�h�c
	DWORD	GetObjNo() { return m_dwObjNo; }		// �I�u�W�F�N�g�m�n
	void	SetObjNo(DWORD dwObjNo) { m_dwObjNo = dwObjNo; }		// �I�u�W�F�N�g�m�n
	DWORD	GetStatus() { return m_dwStatus; }
	void	SetStatus(DWORD dwStatus) { m_dwStatus = dwStatus; }
	CBBox*	GetBBox() { return m_pBBox; }
	MATRIX4X4  GetWorld() { return m_mWorld; }
	MATRIX4X4  GetWorldOld() { return m_mWorldOld; }
	void    SetWorld(MATRIX4X4 mWorld) { m_mWorld = mWorld; }
	void    SetWorldOld(MATRIX4X4 mWorldOld) { m_mWorldOld = mWorldOld; }
	VECTOR3 GetPosUp() { return m_vPosUp; }
	void    SetPosUp(VECTOR3 vPosUp) { m_vPosUp = vPosUp; }
	int		GetMaxHp() { return m_nMaxHp; }
	int		GetHp() { return m_nHp; }
	int		GetAtc() { return m_nAtc; }
	VECTOR3 GetHitNormal() { return m_vHitNormal; }

	float	GetDist() { return m_fDist; }
	BOOL	GetTarget() { return bTarget; }
	void	SetTarget(BOOL Target) { bTarget = Target; }

	BOOL	GetbShaftObjTrigger() { return bShaftObjTrigger; }		

	void	SetWeaponUseNum(DWORD dNum) { m_dWeaponUseNum = dNum; }	
	DWORD	GetWeaponUseNum() { return	m_dWeaponUseNum; }

	ANIMATION_STATUS GetAnimStatus() { return m_AnimStatus; } 
	void    SetAnimStatus(ANIMATION_STATUS as) { m_AnimStatus = as; } 

	BOOL	GetDamage() { return m_bDamage; }
	void	SetDamage(BOOL bDamage) { m_bDamage = bDamage; }

	void	SetHitPos(VECTOR3 HitPos) { m_vHitPos = HitPos; }
	void	SetHitNormal(VECTOR3 HitNormal) { m_vHitNormal = HitNormal; }

	BOOL	GetStop() { return m_bStop; }	
	void	SetStop(BOOL bStop) { m_bStop = bStop; }

	DWORD	GetPlayerNo() { return m_dwPlayerNo; }
	void	SetPlayerNo(DWORD dwPlayerNo) { m_dwPlayerNo= dwPlayerNo; }


	MATRIX4X4 TurnTarget(MATRIX4X4 MyWorld, MATRIX4X4 TargetWorld);	
	MATRIX4X4 RotTarget(MATRIX4X4 MyWorld, MATRIX4X4 TargetWorld, float fSpeed, float fDist);
	// �R���X�g���N�^�i��{�I�u�W�F�N�g�̏������j
	CBaseObj(CGameMain* pGMain);
	// �f�X�g���N�^
	virtual		~CBaseObj();
};

// --------------------------------------------------------------------------------------------------
// ��{�v���V�[�W���N���X
//
//   ���@�v���V�[�W���Ƃ́A�u�����̏�������ɂ܂Ƃ߂����́v�Ƃ����Ӗ�
//       �����̃I�u�W�F�N�g�≺�ʃv���V�[�W�����R���g���[������N���X�̂���
//
// --------------------------------------------------------------------------------------------------
class  CBaseProc
{
protected:
	CGameMain*		m_pGMain;				// �Q�[�����C���N���X

	// 
	// ���ʂ̃v���V�[�W���|�C���^�z��́A�v���V�[�W�����K�w�\���ɂ��ĊǗ�����Ƃ��Ɏg�p����
	// �I�u�W�F�N�g�|�C���^�z��́A�v���V�[�W���̒��ɃI�u�W�F�N�g��z�u���ĊǗ�����Ƃ��Ɏg�p����
	// ��ʓI�ɂ́A�ǂ��炩�Е��݂̂��g�p���邱��
	// 
	std::vector<CBaseProc*>  m_pProcArray;  // ���ʂ̃v���V�[�W���|�C���^�z��
	std::vector<CBaseObj*>   m_pObjArray;	// �I�u�W�F�N�g�|�C���^�z��

	DWORD			m_dwProcID;				// �v���V�[�W���h�c
	int				m_nMaxNum;				// �ő唭����
	int				m_nNum;					// ������
	int				m_nMaxwaitTime;			// �ő�҂�����
	int				m_nWaitTime;			// ���݂̑҂�����
	int				m_nWaitTimeSec;			// ���݂̑҂�����

	DWORD			m_dwKinds;			//���
	DWORD			m_dwBreakNum;		//�j��

public:
	// �S�̍X�V�����i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����čX�V����������j
	virtual void	UpdateAll() final;
	virtual void	UpdateAllMulti(DWORD m_dwPlayerNo) final;

	// �X�V�����iUpdateAll()�̒��ŋN���B�v���V�[�W���̍X�V�����j
	virtual void    Update() { ; }
	virtual void    UpdateMulti(DWORD m_dwPlayerNo) { ; }

	// �����蔻��i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����ď���������j
	virtual BOOL    Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld) final;
	virtual BOOL    Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack) final;

	virtual BOOL    HitcheckOtherLay(CBaseObj* pOtherObj) final;

	virtual BOOL    ObjGravity(CBaseObj* pOtherObj, float fDist,float fRotateSpeed);	
	virtual BOOL    ObjTarget(CBaseObj* pOtherObj,float fRotateSpeed,DWORD RunNum);		

	virtual BOOL    Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack,DWORD NotID) final;		
	virtual BOOL    ObjTerritory(CBaseObj* pOtherObj, float fDist);		//�͈͓����ǂ����𒲂ׂ�	

	virtual BOOL    HitcheckMulti(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld, DWORD dwPlayerNo) final;	
	virtual BOOL    HitcheckMulti(CBaseObj* pOtherObj, CBBox* pBBoxAtack, DWORD dwPlayerNo) final;

	virtual BOOL    HitcheckMultiOtherLay(CBaseObj* pOtherObj, DWORD dwPlayerNo) final;		

	virtual BOOL    ObjGravityMulti(CBaseObj* pOtherObj, float fDist, float fRotateSpeed, DWORD dwPlayerNo);
	virtual BOOL    ObjTargetMulti(CBaseObj* pOtherObj, float fRotateSpeed, DWORD RunNum, DWORD dwPlayerNo);

	virtual BOOL    HitcheckMulti(CBaseObj* pOtherObj, CBBox* pBBoxAtack, DWORD NotID, DWORD dwPlayerNo) final;	
	virtual BOOL    ObjTerritoryMulti(CBaseObj* pOtherObj, float fDist, DWORD dwPlayerNo);		//�͈͓����ǂ����𒲂ׂ�	

	//	�v���V�[�W���ƃI�u�W�F�N�g��T�����S�ẴI�u�W�F�N�g���m���A�N�e�B�u�ɂ���
	virtual void	SetNonActive();

	//	�������̐ݒ�
	virtual void	SetMaxNum() { m_nNum = m_nMaxNum; }
	//	�E�F�C�g�^�C���̐ݒ�
	virtual void	SetMaxWaitTime() { m_nWaitTime = m_nMaxwaitTime; }
	virtual void	SetWaitTime(int	n) { m_nWaitTime = n; }	
	virtual void	SetMaxWaitTimeSec() { m_nWaitTimeSec = m_nMaxwaitTime; }
	virtual void	SetWaitTimeSec(int	n) { m_nWaitTimeSec = n; }

	virtual MATRIX4X4	ObjReflectionStart(CBaseObj* mMyObj, CBaseObj* mHitObj);


	DWORD	GetWaitTime() { return m_nWaitTime; }
	DWORD	GetWaitTimeSec () { return m_nWaitTimeSec; }
	DWORD	GetKinds() { return m_dwKinds; }

	// �A�N�Z�X�֐�
	std::vector<CBaseProc*> GetProcArrayPtr() { return m_pProcArray; } // ���ʂ̃v���V�[�W���|�C���^�z��̃A�h���X��Ԃ�
	std::vector<CBaseObj*>  GetObjArrayPtr() { return m_pObjArray; }  // �I�u�W�F�N�g�|�C���^�z��̃A�h���X��Ԃ�
	int  GetNum() { return m_nNum; }
	void AddNum(int n) { m_nNum += n; }

	DWORD GetBreakNum() { return m_dwBreakNum; }
	void AddBreakNum(DWORD n) { m_dwBreakNum += n; }

	DWORD GetProcID() { return m_dwProcID; }

	// �R���X�g���N�^�i��{�v���V�[�W���̏������j
	CBaseProc(CGameMain* pGMain)
	{
		m_pGMain = pGMain;   // �Q�[�����C���N���X
		m_dwProcID = 0;         // �v���V�[�W���h�c
		m_nMaxwaitTime = 0;		// �ő�҂�����
		m_nWaitTime = 0;		// ���݂̑҂�����
		m_dwBreakNum = 0;
	}
	// �f�X�g���N�^�i�v���V�[�W���ƃI�u�W�F�N�g�̉���j
	virtual		~CBaseProc();
};


