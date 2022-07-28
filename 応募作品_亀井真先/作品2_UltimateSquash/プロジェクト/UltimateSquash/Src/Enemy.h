//=============================================================================
//		�G�L�����N�^�[�@�w�b�_�t�@�C��							Enemy.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Map.h"
#include"Camera.h"

// �G�̂h�c�Ɣ�����
// 
//   ID    :�G�̂h�c�B�P���珇�ԂɐU��
//   MAX   :�G�I�u�W�F�N�g�̐��B�i�����������j
//   ALLMAX:�G�̍ő�o�����B�i�������܂߂�j
// 

//�{�[���̃X�e�[�^�X
#define  ENM_BALL_ID			1
#define  ENM_BALL_MAX			10
#define  ENM_BALL_ALLMAX		1000
#define	 ENM_BALL_SPEED			0.1f
#define	 ENM_BALL_WAITMAX		50
#define	 ENM_BALL_BBOX_MAX		0.35f, 0.35f, 0.35f
#define	 ENM_BALL_BBOX_MIN		-0.35f, -0.35f, -0.35f
#define	 ENM_BALL_COLOR			1, 1, 1, 1

//�I�̃X�e�[�^�X
#define  ENM_TARGET_ID				2
#define  ENM_TARGET_MAX				10
#define  ENM_TARGET_ALLMAX			100
#define	 ENM_TARGET_SPEED			0.05f
#define	 ENM_TARGET_WAITMAX			50
#define	 ENM_TARGET_BBOX_MAX		0.35f, 0.35f, 0.35f
#define	 ENM_TARGET_BBOX_MIN		-0.35f, -0.35f, -0.35f
#define  ENM_TARGET_POINT			100

//�����I�̃X�e�[�^�X
#define  ENM_MOVETARGET_ID				3
#define  ENM_MOVETARGET_MAX				5
#define  ENM_MOVETARGET_ALLMAX			100
#define	 ENM_MOVETARGET_SPEED			0.03f
#define	 ENM_MOVETARGET_WAITMAX			50
#define	 ENM_MOVETARGET_BBOX_MAX		0.5f, 0.5f, 0.5f
#define	 ENM_MOVETARGET_BBOX_MIN		-0.5f, -0.5f, -0.5f
#define  ENM_MOVETARGET_POINT			300

#define  ENM_SHIELD_ID				4
#define  ENM_SHIELD_MAX				2
#define  ENM_SHIELD_ALLMAX			100
#define	 ENM_SHIELD_SPEED			0.03f
#define	 ENM_SHIELDT_WAITMAX		300
#define	 ENM_SHIELD_BBOX_MAX		0.35f, 0.35f, 0.35f
#define	 ENM_SHIELD_BBOX_MIN		-0.35f, -0.35f, -0.35f
#define  ENM_SHIELD_POINT			1000
#define  ENM_SHIELD_STARTPOINT		1500

#define  ENM_WALL_ID				5
#define  ENM_WALL_MAX				1
#define  ENM_WALL_ALLMAX			2
#define	 ENM_WALL_SPEED				0.05f
#define	 ENM_WALL_WAITMAX			300
#define	 ENM_WALL_BBOX_MAX			0.35f, 0.35f, 0.35f
#define	 ENM_WALL_BBOX_MIN			-0.35f, -0.35f, -0.35f
#define  ENM_WALL_POINT				500
#define  ENM_WALL_STARTPOINT		5000
#define	 ENM_WALL_USENUM			2
#define	 ENM_WALL_STARTTIME			400
#define	 ENM_WALL_WAITTIME			3

#define  ENM_BALLBOOM_ID			6
#define  ENM_BALLBOOM_MAX			1
#define  ENM_BALLBOOM_ALLMAX		1000
#define	 ENM_BALLBOOM_SPEED			0.03f
#define	 ENM_BALLBOOM_WAITMAX		0
#define	 ENM_BALLBOOM_BBOX_MAX		0.35f, 0.35f, 0.35f
#define	 ENM_BALLBOOM_BBOX_MIN		-0.35f, -0.35f, -0.35f
#define	 ENM_BALLBOOM_TIMERDOWN		5

	
#define  ENM_BEND_ID				7
#define  ENM_BEND_MAX				2
#define  ENM_BEND_ALLMAX			10
#define	 ENM_BEND_SPEED				0.01f
#define	 ENM_BEND_WAITMAX			300
#define	 ENM_BEND_BBOX_MAX			0.35f, 0.35f, 0.35f
#define	 ENM_BEND_BBOX_MIN			-0.35f, -0.35f, -0.35f
#define  ENM_BEND_POINT				500
#define  ENM_BEND_STARTPOINT		7000
#define	 ENM_BEND_USENUM			2
#define	 ENM_BEND_STARTTIME			400
#define	 ENM_WALL_WAITTIME			5
#define	 ENM_WALL_SPEEDRUN_MIN		4.0f
#define	 ENM_WALL_SPEEDRUN_MAX		6.0f

#define  ENM_TARGETSKILL_ID				8
#define  ENM_TARGETSKILL_MAX			2
#define  ENM_TARGETSKILL_ALLMAX			10
#define	 ENM_TARGETSKILL_SPEED			0.05f
#define	 ENM_TARGETSKILL_WAITMAX		300
#define	 ENM_TARGETSKILL_BBOX_MAX		0.75f, 0.75f, 0.75f
#define	 ENM_TARGETSKILL_BBOX_MIN		-0.75f, -0.75f, -0.75f
#define  ENM_TARGETSKILL_POINT			100


//======================================================================   
// �G�{�[���@�I�u�W�F�N�g�N���X
//======================================================================
class CEnmBallProc;
class CEnmBallObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;	// Fbx�X�L�����b�V��
	VECTOR3				m_vTarget;	// �^�[�Q�b�g
	NAVIGATIONMAP		m_Nav;		// �i�r�Q�[�V�����}�b�v


	VECTOR4				m_vDiffuse;	
	int				m_nWeapoWaitTime[100];
	int				m_nWeapoMaxWaitTime[100];

	BOOL				bPcBoolSkill;
	BOOL				bPcSecBoolSkill;


public:

	float				m_fSpeed;

	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmBallProc* pProc);
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }
	
	void SetPcBoolSkill(BOOL bSkill) { bPcBoolSkill = bSkill; }
	void ConditionsDelete();

	CEnmBallObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmBallObj();	// �f�X�g���N�^
};
// ------------------------------------ 
// �G�{�[���@�v���V�[�W���N���X
// ------------------------------------
class CEnmBallProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;		// Fbx�X�L�����b�V��
	float				m_fSpeed;

	BOOL				bPcBoolSkill;
	BOOL				bPcSecBoolSkill;

	DWORD				dwHitNum;		//�ł��ς���ꂽ��	

	std::vector<DWORD> Nav;   // �I���i�r�}�b�v


public:
	void Update() override;
	void UpdateMulti(DWORD m_dwPlayerNo) override;
	void NavSet();

	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��

	float				GetSpeed() { return m_fSpeed; }

	BOOL GetPcBoolSkill() { return bPcBoolSkill; }
	void SetPcBoolSkill(BOOL bSkill) { bPcBoolSkill = bSkill; }
	BOOL GetPcSecBoolSkill() { return bPcSecBoolSkill; }
	void SetPcSecBoolSkill(BOOL bSkill) { bPcSecBoolSkill = bSkill; }

	DWORD GetHitNum() { return dwHitNum; }		
	void SetHitNum(DWORD dwNum) { dwHitNum = dwNum; }		
	void AddHitNum(DWORD dwNum) { dwHitNum += dwNum; }	

	void UpdateNav();
	void UpdateNavMulti(DWORD m_dwPlayerNo);


	CEnmBallProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmBallProc();	// �f�X�g���N�^
};

//======================================================================  
// �G�I�@�I�u�W�F�N�g�N���X
//======================================================================
class CEnmTargetProc;
class CEnmTargetObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;	// Fbx�X�L�����b�V��
	VECTOR3				m_vTarget;	// �^�[�Q�b�g
	NAVIGATIONMAP		m_Nav;		// �i�r�Q�[�V�����}�b�v

public:


	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmTargetProc* pProc);
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }




	CEnmTargetObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmTargetObj();	// �f�X�g���N�^
};

// ------------------------------------
// �G�I�@�v���V�[�W���N���X
// ------------------------------------
class CEnmTargetProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;		// Fbx�X�L�����b�V��

	std::vector<DWORD> Nav;   // �I���i�r�}�b�v


public:
	void Update() override;
	void UpdateMulti(DWORD m_dwPlayerNo) override;
	void NavSet();

	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��
	
	void UpdateNav();
	void UpdateNavMulti(DWORD m_dwPlayerNo);


	CEnmTargetProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmTargetProc();	// �f�X�g���N�^
};


//======================================================================    
// �G�����I�@�I�u�W�F�N�g�N���X
//======================================================================
class CEnmMoveTargetProc;
class CEnmMoveTargetObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;	// Fbx�X�L�����b�V��
	VECTOR3				m_vTarget;	// �^�[�Q�b�g
	NAVIGATIONMAP		m_Nav;		// �i�r�Q�[�V�����}�b�v

	float				m_fLocalRotY;		// ���[�J����(Y��)   
	float				fMoveSpeed;
	float				fDist;
public:


	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmMoveTargetProc* pProc);
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }




	CEnmMoveTargetObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmMoveTargetObj();	// �f�X�g���N�^
};



// ------------------------------------   
// �G�����I�@�v���V�[�W���N���X
// ------------------------------------
class CEnmMoveTargetProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;		// Fbx�X�L�����b�V��

	std::vector<DWORD> Nav;   // �I���i�r�}�b�v


public:
	void Update() override;
	void UpdateMulti(DWORD m_dwPlayerNo) override;
	void NavSet();

	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��


	void UpdateNav();
	void UpdateNavMulti(DWORD m_dwPlayerNo);


	CEnmMoveTargetProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmMoveTargetProc();	// �f�X�g���N�^
};


//======================================================================  
// �G�V�[���h�@�I�u�W�F�N�g�N���X
//======================================================================
class CEnmShieldProc;
class CEnmShieldObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;	// Fbx�X�L�����b�V��
	VECTOR3				m_vTarget;	// �^�[�Q�b�g
	NAVIGATIONMAP		m_Nav;		// �i�r�Q�[�V�����}�b�v

	int					n_ArryNo;
	float				fNormalSpeed ;                                    // �ړ��X�s�[�h
	DWORD				dPosStatus;				//�}�b�v�ɑ΂��Ďl�����̃X�e�[�^�X	
	DWORD				dwRespawnTime;
public:


	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmShieldProc* pProc);
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }
	NAVIGATIONMAP	GetNav() { return	m_Nav; }
	void SetArryNo(int n) { n_ArryNo = n; }
	int  GetArryNo() { return n_ArryNo; }
	void ShieldAppearance(MATRIX4X4 mWorld);

	void SetPosStatus(DWORD Sta) { dPosStatus = Sta; }
	CEnmShieldObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmShieldObj();	// �f�X�g���N�^
};






// ------------------------------------ 
// �G�V�[���h�v���V�[�W���N���X
// ------------------------------------
class CEnmShieldProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;		// Fbx�X�L�����b�V��

	std::vector<DWORD> Nav;   // �I���i�r�}�b�v


public:
	void Update() override;
	void UpdateMulti(DWORD m_dwPlayerNo) override;
	void NavSet();

	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��

	void UpdateNav();
	void UpdateNavMulti(DWORD m_dwPlayerNo);



	CEnmShieldProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmShieldProc();	// �f�X�g���N�^
};



//======================================================================   
// �G���e�{�[���@�I�u�W�F�N�g�N���X
//======================================================================
class CEnmBallBoomProc;
class CEnmBallBoomObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;	// Fbx�X�L�����b�V��
	VECTOR3				m_vTarget;	// �^�[�Q�b�g
	NAVIGATIONMAP		m_Nav;		// �i�r�Q�[�V�����}�b�v
	MATRIX4X4			m_StartWorld;

	VECTOR4				m_vDiffuse;
	int				m_nWeapoWaitTime[100];
	int				m_nWeapoMaxWaitTime[100];

public:

	float				m_fSpeed;
	
	int					m_nScrX;	//�X�N���[���ő��₵�Â���ϐ�	


	//bool				m_bDamage;


	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmBallBoomProc* pProc);
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }



	CEnmBallBoomObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmBallBoomObj();	// �f�X�g���N�^
};
// ------------------------------------   
// �G���e�{�[���@�v���V�[�W���N���X
// ------------------------------------
class CEnmBallBoomProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;		// Fbx�X�L�����b�V��
	float				m_fSpeed;

public:
	void Update() override;
	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��

	float				GetSpeed() { return m_fSpeed; }

	CEnmBallBoomProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmBallBoomProc();	// �f�X�g���N�^
};


//====================================================================== 
// �G�ǁ@�I�u�W�F�N�g�N���X
//======================================================================
class CEnmWallProc;
class CEnmWallObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;	// Fbx�X�L�����b�V��
	VECTOR3				m_vTarget;	// �^�[�Q�b�g
	NAVIGATIONMAP		m_Nav;		// �i�r�Q�[�V�����}�b�v

	int					n_ArryNo;
	float				fNormalSpeed ;                                    // �ړ��X�s�[�h
	DWORD				dPosStatus;				//�}�b�v�ɑ΂��Ďl�����̃X�e�[�^�X	
	int					dWallStartTime;

	DWORD				dWeaeponNum;
public:


	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmWallProc* pProc);
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }
	NAVIGATIONMAP	GetNav() { return	m_Nav; }
	void SetArryNo(int n) { n_ArryNo = n; }
	int  GetArryNo() { return n_ArryNo; }

	void SetPosStatus(DWORD Sta) { dPosStatus = Sta; }
	CEnmWallObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmWallObj();	// �f�X�g���N�^
};






// ------------------------------------   
// �G�ǃv���V�[�W���N���X
// ------------------------------------
class CEnmWallProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;		// Fbx�X�L�����b�V��

	std::vector<DWORD> Nav;   // �I���i�r�}�b�v


public:
	void Update() override;
	void UpdateMulti(DWORD m_dwPlayerNo) override;
	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��
	void NavSet();

	void UpdateNav();
	void UpdateNavMulti(DWORD m_dwPlayerNo);


	CEnmWallProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmWallProc();	// �f�X�g���N�^
};

//======================================================================
// �G�Ȃ���@�I�u�W�F�N�g�N���X
//======================================================================
class CEnmBendProc;
class CEnmBendObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;	// Fbx�X�L�����b�V��
	VECTOR3				m_vTarget;	// �^�[�Q�b�g
	NAVIGATIONMAP		m_Nav;		// �i�r�Q�[�V�����}�b�v

	int					n_ArryNo;
	float				fNormalSpeed;                                    // �ړ��X�s�[�h
	DWORD				dPosStatus;				//�}�b�v�ɑ΂��Ďl�����̃X�e�[�^�X		
	int					dBallStartTime;

	DWORD				dWeaeponNum;
	float				fBaseDist;
	float				fMoveSpeed;
public:


	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmBendProc* pProc);
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }
	NAVIGATIONMAP	GetNav() { return	m_Nav; }
	void SetArryNo(int n) { n_ArryNo = n; }
	int  GetArryNo() { return n_ArryNo; }

	void SetPosStatus(DWORD Sta) { dPosStatus = Sta; }
	CEnmBendObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmBendObj();	// �f�X�g���N�^
};






// ------------------------------------   
// �G�Ȃ���v���V�[�W���N���X
// ------------------------------------
class CEnmBendProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;		// Fbx�X�L�����b�V��

	std::vector<DWORD> Nav;   // �I���i�r�}�b�v


public:
	void Update() override;
	void UpdateMulti(DWORD m_dwPlayerNo) override;
	void NavSet();

	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��

	void UpdateNav();
	void UpdateNavMulti(DWORD m_dwPlayerNo);


	CEnmBendProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmBendProc();	// �f�X�g���N�^
};

//======================================================================   
// �G�I�@�I�u�W�F�N�g�N���X
//======================================================================
class CEnmTargetSkillProc;
class CEnmTargetSkillObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;	// Fbx�X�L�����b�V��
	VECTOR3				m_vTarget;	// �^�[�Q�b�g
	NAVIGATIONMAP		m_Nav;		// �i�r�Q�[�V�����}�b�v

public:


	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmTargetSkillProc* pProc);
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }
	void SkillGetPc();



	CEnmTargetSkillObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmTargetSkillObj();	// �f�X�g���N�^
};

// ------------------------------------  
// �G�I�@�v���V�[�W���N���X
// ------------------------------------
class CEnmTargetSkillProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;		// Fbx�X�L�����b�V��

	std::vector<DWORD> Nav;   // �I���i�r�}�b�v


public:
	void Update() override;
	void UpdateMulti(DWORD m_dwPlayerNo) override;
	void NavSet();

	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��

	void UpdateNav();
	void UpdateNavMulti(DWORD m_dwPlayerNo);


	CEnmTargetSkillProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmTargetSkillProc();	// �f�X�g���N�^
};


//======================================================================
// �G�L�����N�^�[�S�̂̃��C���v���V�[�W���N���X
//======================================================================
class CEnmProc : public CBaseProc
{
public:
	CEnmBallProc*		m_pEnmBallProc;   
	CEnmTargetProc*		m_pEnmTargetProc;     
	CEnmMoveTargetProc*		m_pEnmMoveTargetProc;    
	CEnmShieldProc*		m_pEnmShieldProc;   
	CEnmWallProc*		m_pEnmWallProc;   
	CEnmBallBoomProc*		m_pEnmBallBoomProc;   
	CEnmBendProc*		m_pEnmBendProc; 
	CEnmTargetSkillProc*		m_pEnmTargetSkillProc;  


public:
	void Update();
	void ResetEnmNum(CBaseProc* pProc = NULL);
	int  CountActiveEnm(CBaseProc* pProc = NULL, int nNum = 0);
	void GetActiveEnm(std::vector<CBaseObj*> &ActiveObjArray);
	void GetActiveEnmMulti(std::vector<CBaseObj*> &ActiveObjArray,DWORD dwPlayerNo);
	CEnmProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmProc() { ; }	// �f�X�g���N�^

};

