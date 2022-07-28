//=============================================================================
//		�X�L���@�@�@�w�b�_�t�@�C��								Weapon.h
//=============================================================================
#pragma once

#include "GameMain.h"
#include "Effect.h"

#define  BALL_MAX           200
#define  HOLDITEM_MAX       15


#define  DIVBALL_MAX          200
#define  SHIELD_MAX           200
#define	 BIGBALL_MAX		  200
#define	 PENETBALL_MAX		  200
#define	 PENETBALL_BILL_MAX	  10
#define	 ROLLBALL_MAX		  200
#define  WALL_MAX				4
#define  BENDBALLL_MAX			10

//�X�L����ID
#define  WEAPON_NORMAL           0
#define  WEAPON_DIV				 1
#define	 WEAPON_BIGBALL			 2
#define	 WEAPON_PENETBALL		 3
#define	 WEAPON_ROLLBALL		 4
#define	 WEAPON_SKILLPCBOOL		 5
#define  WEAPON_SKILLBOUNCE		 6
#define  WEAPON_SKILLSPEEDUP	 7


#define	 WEAPON_WALL			 100
#define	 WEAPON_SWORD			 100

//�X�L���N�[���^�C��
#define  WEAPON_DIV_WAITTIME			10
#define	WEAPON_BIGBALL_WAITTIME			 5
#define	 WEAPON_PENETBALL_WAITTIME		 3
#define	WEAPON_ROLLBALL_WAITTIME		10
#define	WEAPON_SKILLPCBOOL_WAITTIME		10
#define	WEAPON_SKILLBOUNCE_WAITTIME		 3
#define	WEAPON_SKILLSPEEDUP_WAITTIME	3

//�X�L������
#define	WEAPON_SKILLPCBOOL_TIME		10
#define	WEAPON_SKILLSPEEDUP_TIME	2

struct TargetStatas
{
	int Id;

};

// --------------------------------------------------------------------
//�X�L���@���@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponSwordProc;
class CWeaponSwordObj : public CBaseObj
{
protected:
	DWORD           m_dwOwner;
	int				m_nWeapoWaitTime[100];
	int				m_nWeapoMaxWaitTime[100];
	int				nCount[100];				//60�t���[���ň�b�����邽�߂̕ϐ�
	int				nWaitCount[100];

	CBBox*			m_pBBoxSub;			// �o�E���f�B���O�{�b�N�X�N���X
	DWORD			dwUseNumWeapon;		//�X�L�����g�p������		

public:
	BOOL Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner) override;
	BOOL Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner, DWORD dwPlayerNo) override;

	void Update() override;
	void Render();

	void UpdateDamage();

	int GetWeaponWaitTime(int n) { return m_nWeapoWaitTime[n]; }
	int GetWeaponMaxWaitTime(int n) { return m_nWeapoMaxWaitTime[n]; }
	void	SetWeaponWaitTime(int n, int time) { m_nWeapoWaitTime[n] = time; }
	void	SetWeaponMaxWaitTime(int n, int time) { m_nWeapoMaxWaitTime[n] = time; }

	int GetCount(int n) { return nCount[n]; }
	int GetWaitCount(int n) { return nWaitCount[n]; }

	DWORD GetUseNumWeapon() { return dwUseNumWeapon; }			
	void  SetUseNumWeapon(DWORD dwNum) { dwUseNumWeapon = dwNum; }	

	void ResetWeaponWaitTime(int n){  m_nWeapoWaitTime[n]=0; }

	void WeaponStart(DWORD dwWaitTime, const int WeaponColuman);

	CWeaponSwordObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponSwordObj();
};
// --------------------------------------------------------------------
// �X�L���@���@�v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponSwordProc : public CBaseProc
{
public:

	BOOL Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner);	// ���̔���
	BOOL Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner, DWORD dwPlayerNo);

	CWeaponSwordObj*	GetWeaponSwordObjPtr() { return(CWeaponSwordObj*)GetObjArrayPtr()[0]; }
	CWeaponSwordObj*	GetWeaponSwordSecObjPtr() { return(CWeaponSwordObj*)GetObjArrayPtr()[1]; }

	CWeaponSwordProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponSwordProc() { ; }

};

// --------------------------------------------------------------------
//�X�L���@�{�[���@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
	DWORD                    m_dwOwner;

	float				m_fLocalRotY;		// ���[�J����(Y��)   


	ChkFace* p;

	float				m_fJumpSpeed;		// �W�����v���x       
	VECTOR4				m_vDiffuse;

public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner) override;
	void Update() override;

	void UpdateDamage();

	void Render();

	MATRIX4X4  GetLocalMatrix();			// ���[�J�����}�g���b�N�X�𓾂�


	// �A�N�Z�X�֐�
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponBallObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponBallObj();
};
// --------------------------------------------------------------------
//�X�L���@�{�[���v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
public:
	BOOL Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner);  //�X�L���@�{�[���̔���

	CWeaponBallProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponBallProc();

	CWeaponBallObj*	GetWeaponBallObjPtr() { return(CWeaponBallObj*)GetObjArrayPtr()[0]; }

};

// --------------------------------------------------------------------
//�X�L���@��Ɏ��A�C�e���@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponHoldObj : public CBaseObj
{
protected:
	int                      m_nKindNo;			// ��Ɏ��A�C�e���̎��(1:���@2:�e)
	CFbxMesh*                m_pMesh;			// Fbx���b�V��(�v���V�[�W���ł͂Ȃ��I�u�W�F�N�g�Ƀ��b�V������������)
	VECTOR3                  m_vOffset;			// �e���܂ł̃I�t�Z�b�g�i�e�̂݁j
public:
	void Init();
	BOOL Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem,DWORD dwPlayerNo);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax);
	CBBox* GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);

	void Update() override;
	void Render();

	int GetKind() { return m_nKindNo; }

	CWeaponHoldObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponHoldObj();
};
// --------------------------------------------------------------------
//�X�L���@��Ɏ��A�C�e���@�v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponHoldProc : public CBaseProc
{
protected:
	;
public:
	BOOL Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, DWORD dwPlayerNo); // �X�L���@�̕\��
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax);
	CBBox* GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);
	int GetKind(BASEHOLDITEM HoldItem) { return ((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetKind(); }
	CWeaponHoldProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponHoldProc();

	CWeaponHoldObj*	GetWeaponHoldObjPtr() { return(CWeaponHoldObj*)GetObjArrayPtr()[0]; }

};

// --------------------------------------------------------------------
//�X�L���@�V�[���h�@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponShieldObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
	DWORD                    m_dwOwner;
	float				m_fLocalRotY;		// ���[�J����(Y��)  
	ChkFace* p;
	float				m_fJumpSpeed;		// �W�����v���x      

	DWORD		   dTargetNo;			//��邽�߂̎��ƂȂ�I�u�W�F�N�g�̔z��̃i���o�[
	float			fShieldDist;		//���ƂȂ�I�u�W�F�N�g�Ƃ̋���	


public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner) override;
	BOOL Start(MATRIX4X4 mWorld, DWORD dwOwner, DWORD dwPlayerNo) override;

	void Update() override;

	void UpdateDamage();
	void Render();
	MATRIX4X4  GetLocalMatrix();			// ���[�J�����}�g���b�N�X�𓾂�


	// �A�N�Z�X�֐�
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponShieldObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponShieldObj();
};
// --------------------------------------------------------------------
//�X�L���@�V�[���h�v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponShieldProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��

	DWORD		   dTargetNo;		//��邽�߂̎��ƂȂ�I�u�W�F�N�g�̔z��̃i���o�[	
	float			fShieldDist;		//���ƂȂ�I�u�W�F�N�g�Ƃ̋���	

public:


	BOOL Start(MATRIX4X4 mWorld, DWORD dwOwner);  //�X�L���@�{�[���̔���
	BOOL Start(MATRIX4X4 mWorld, DWORD dwOwner,DWORD dwPlayerNo);  //�X�L���@�{�[���̔���

	void SetTargetNo(DWORD dNo) { dTargetNo = dNo; }
	DWORD GetTargetNo() { return dTargetNo; }
	void SetShieldDist(float dNum) { fShieldDist = dNum; }
	float GetShieldDist() { return fShieldDist; }
	CWeaponShieldProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponShieldProc();

	CWeaponShieldObj*	GetWeaponBallObjPtr() { return(CWeaponShieldObj*)GetObjArrayPtr()[0]; }

};


// --------------------------------------------------------------------
//�X�L���@����{�[���@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponDivBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
	DWORD                    m_dwOwner;

	float				m_fLocalRotY;		// ���[�J����(Y��)  
	float				m_fDivTime;
	DWORD               Direction;

	ChkFace* p;

	float				m_fJumpSpeed;		// �W�����v���x       
	BOOL				m_bFront;
	DWORD					RanNum;			//ID��ۑ�����p	

	CBaseProc*			TargetProc;			//�^�[�Q�b�g���Ă���v���b�N	
	float					fActivTime;

	std::vector<TargetStatas>		TargetProcArr;
	std::vector<TargetStatas>		TargetObjArr;

public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner, DWORD dwNo, DWORD  dwNum);
	void Update() override;

	void UpdateDamage();

	void Render();

	MATRIX4X4  GetLocalMatrix();			// ���[�J�����}�g���b�N�X�𓾂�


	// �A�N�Z�X�֐�
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }


	BOOL LookTarget(CBaseProc* pOtherProc,DWORD dwPlayerNo);		//	�^�[�Q�b�g�������鏈��		


	CWeaponDivBallObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponDivBallObj();
};
// --------------------------------------------------------------------
//�X�L���@����{�[���v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponDivBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
public:
	BOOL Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner);  //�X�L���@�{�[���̔���
	BOOL Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner,DWORD dwPlayerNo);  //�X�L���@�{�[���̔���

	CWeaponDivBallProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponDivBallProc();

	CWeaponDivBallObj*	GetWeaponBallDivObjPtr() { return(CWeaponDivBallObj*)GetObjArrayPtr()[0]; }


};

// --------------------------------------------------------------------
//�X�L���@�r�b�O�{�[���@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponBigBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
	DWORD                    m_dwOwner;

	float				m_fLocalRotY;		// ���[�J����(Y��)   


	ChkFace* p;

	float				m_fJumpSpeed;		// �W�����v���x       
	VECTOR4				m_vDiffuse;
	DWORD				m_dDamageCount;
public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner) override;
	void Update() override;

	void UpdateDamage();

	void Render();

	MATRIX4X4  GetLocalMatrix();			// ���[�J�����}�g���b�N�X�𓾂�


	// �A�N�Z�X�֐�
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponBigBallObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponBigBallObj();
};
// --------------------------------------------------------------------
//�X�L���@�r�b�O�{�[���v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponBigBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
public:
	BOOL Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner);  //�X�L���@�{�[���̔���
	BOOL Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner,DWORD dwPlayerNo);  //�X�L���@�{�[���̔���

	CWeaponBigBallProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponBigBallProc();


};

// --------------------------------------------------------------------
//�X�L���@�ђʃ{�[���@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponPenetBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
	DWORD                    m_dwOwner;

	float				m_fLocalRotY;		// ���[�J����(Y��)   


	ChkFace* p;

	float				m_fJumpSpeed;		// �W�����v���x      
	VECTOR4				m_vDiffuse;	

public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner) override;
	void Update() override;

	void UpdateDamage();

	void Render();

	MATRIX4X4  GetLocalMatrix();			// ���[�J�����}�g���b�N�X�𓾂�


	// �A�N�Z�X�֐�
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponPenetBallObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponPenetBallObj();
};
// --------------------------------------------------------------------
//�X�L���@�ђʃ{�[���v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponPenetBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
public:
	BOOL Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner);  //�X�L���@�{�[���̔���
	BOOL Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner, DWORD dwPlayerNo);  //�X�L���@�{�[���̔���

	CWeaponPenetBallProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponPenetBallProc();


};


// --------------------------------------------------------------------
//�X�L���@��]�{�[���@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponRollBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
	DWORD                    m_dwOwner;

	float				m_fLocalRotY;		// ���[�J����(Y��) 


	ChkFace* p;

	float				m_fJumpSpeed;		// �W�����v���x     
	VECTOR4				m_vDiffuse;	

public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner) override;
	void Update() override;

	void UpdateDamage();

	void Render();

	MATRIX4X4  GetLocalMatrix();			// ���[�J�����}�g���b�N�X�𓾂�


	// �A�N�Z�X�֐�
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponRollBallObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponRollBallObj();
};
// --------------------------------------------------------------------
//�X�L���@��]�{�[���v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponRollBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
public:
	BOOL Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner);  //�X�L���@�{�[���̔���
	BOOL Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner, DWORD dwPlayerNo);  //�X�L���@�{�[���̔���

	CWeaponRollBallProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponRollBallProc();


};

// --------------------------------------------------------------------
//�X�L���@�ǁ@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponWallProc;
class CWeaponWallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
	DWORD                    m_dwOwner;
	float				m_fLocalRotY;		// ���[�J����(Y��)   
	ChkFace* p;
	float				m_fJumpSpeed;		// �W�����v���x    

	DWORD		   dTargetNo;			//��邽�߂̎��ƂȂ�I�u�W�F�N�g�̔z��̃i���o�[
	float			fWallDist;		//���ƂȂ�I�u�W�F�N�g�Ƃ̋���	
	
	CCollision*				m_pColMesh;			// �ړ��R���W�������b�V���ւ̃|�C���^
	MATRIX4X4				mColWorld;
	DWORD					dUseNo;		//�g�p���Ă���I�u�W�F�N�g�̃i���o�[	
	DWORD					dDamageNum;
	BOOL					bInvTrigger;	//���G���ǂ���
	VECTOR4					vDiffuse;
	BOOL					bDamageTrigger;
	BOOL					bStartTrigget;
public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner, DWORD dNo) override;
	void Update() override;
	void UpdateDamage();
	void Render();
	MATRIX4X4  GetLocalMatrix();			// ���[�J�����}�g���b�N�X�𓾂�


	// �A�N�Z�X�֐�
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	void SetColMesh(CCollision* pColMesh) { m_pColMesh = pColMesh; }
	CCollision*	GetColMesh() { return m_pColMesh; }
	void SetColMesh(CWeaponWallProc* pProc);

	BOOL	 isBBoxMoveGravity(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld,VECTOR3 vHit, VECTOR3 vNrm,float fRadius);
	void	 StartLE();
	void	 InvincibleTime();
	void	 ObjDisappear();

	CWeaponWallObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponWallObj();
};
// --------------------------------------------------------------------
//�X�L���@�ǃv���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponWallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��

	DWORD		   dTargetNo;		//��邽�߂̎��ƂȂ�I�u�W�F�N�g�̔z��̃i���o�[	
	float			fWallDist;		//���ƂȂ�I�u�W�F�N�g�Ƃ̋���	
	CCollision*				m_pColMesh;			// �ړ��R���W�������b�V���ւ̃|�C���^

public:
	BOOL Start(MATRIX4X4 mWorld, DWORD dwOwner, DWORD dNo);  //�X�L���@�{�[���̔���
	BOOL Start(MATRIX4X4 mWorld, DWORD dwOwner, DWORD dNo, DWORD dwPlayerNo);
	void SetTargetNo(DWORD dNo) { dTargetNo = dNo; }
	DWORD GetTargetNo() { return dTargetNo; }
	void SetWallDist(float dNum) { fWallDist = dNum; }
	float GetWallDist() { return fWallDist; }
	CWeaponWallProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponWallProc();

	CWeaponWallObj*	GetWeaponBallObjPtr() { return(CWeaponWallObj*)GetObjArrayPtr()[0]; }

	int  isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld,DWORD dwPlayerNo);

	BOOL	 isBBoxMoveGravity(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld, float fRadius );
	CCollision*	GetColMesh() { return m_pColMesh; }

};

// --------------------------------------------------------------------
//�X�L���@�Ȃ���{�[���@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponBendBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
	DWORD                    m_dwOwner;
	float				m_fLocalRotY;		// ���[�J����(Y��) 
	ChkFace* p;
	float				m_fJumpSpeed;		// �W�����v���x     

	DWORD		   dTargetNo;			//��邽�߂̎��ƂȂ�I�u�W�F�N�g�̔z��̃i���o�[
	float			fBendBallDist;		//���ƂȂ�I�u�W�F�N�g�Ƃ̋���	

	VECTOR3			vRotUp;
	MATRIX4X4		mTargetWorld;
	DWORD			dwMoveStatus;
	DWORD			Count;
	DWORD			dwTurnPos;
	VECTOR3			m_vDiffuse;
	MATRIX4X4		mStartRot;
public:
	BOOL Start(MATRIX4X4 mStartWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner) override;
	BOOL Start(MATRIX4X4 mStartWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner, DWORD dwPlayerNo) override;
	void Update() override;
	void UpdateDamage();
	void Render();
	MATRIX4X4  GetLocalMatrix();			// ���[�J�����}�g���b�N�X�𓾂�

	void BallDirectionStart(DWORD dwTurnPos);
	void ObjBend();
	void DamageRearHitcheck();


	// �A�N�Z�X�֐�
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponBendBallObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponBendBallObj();
};
// --------------------------------------------------------------------
//�X�L���@�Ȃ���{�[���v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponBendBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��

	DWORD		   dTargetNo;		//��邽�߂̎��ƂȂ�I�u�W�F�N�g�̔z��̃i���o�[	
	float			fBendBallDist;		//���ƂȂ�I�u�W�F�N�g�Ƃ̋���	

public:
	BOOL Start(MATRIX4X4 mWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner);  //�X�L���@�{�[���̔���
	BOOL Start(MATRIX4X4 mWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner, DWORD dwPlayerNo);  //�X�L���@�{�[���̔���


	void SetTargetNo(DWORD dNo) { dTargetNo = dNo; }
	DWORD GetTargetNo() { return dTargetNo; }
	void SetBendBallDist(float dNum) { fBendBallDist = dNum; }
	float GetBendBallDist() { return fBendBallDist; }
	CWeaponBendBallProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponBendBallProc();

	CWeaponBendBallObj*	GetWeaponBallObjPtr() { return(CWeaponBendBallObj*)GetObjArrayPtr()[0]; }

};



// ======================================================================
// �X�L���S�̂̃��C���v���V�[�W���N���X
// ======================================================================
class CWeaponProc : public CBaseProc
{
public:
	CWeaponSwordProc*     m_pWeaponSwordProc;

	CWeaponBallProc*      m_pWeaponBallProc;
	CWeaponHoldProc*      m_pWeaponHoldProc;

	CWeaponDivBallProc*      m_pWeaponDivBallProc;		
	CWeaponShieldProc*	 m_pWeaponShieldProc;		
	CWeaponBigBallProc*      m_pWeaponBigBallProc;		
	CWeaponPenetBallProc*      m_pWeaponPenetBallProc;		
	CWeaponRollBallProc*      m_pWeaponRollBallProc;		

	CWeaponWallProc*	 m_pWeaponWallProc;	
	CWeaponBendBallProc*      m_pWeaponBendBallProc;	


public:
	CWeaponProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponProc() { ; }
};


