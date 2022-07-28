//=============================================================================
//		�v���C�L�����N�^�[�@�w�b�_�t�@�C��							Playchar.h
//=============================================================================
#pragma once
#include "GameMain.h"


//======================================================================
// �v���C�L�����N�^�[�@�I�u�W�F�N�g�N���X
//======================================================================
class CPcObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;			// Fbx�X�L�����b�V��
	BASEHOLDITEM        m_nHoldItem;		// ��Ɏ��X�L��
	float				m_fLocalRotY;		// ���[�J����(Y��)   
	BOOL				m_bSide;			// ���ړ����[�h 

	float				m_fSpeed;			// �ړ����x         
	float				m_fRotSpeed;		// ��]���x        
	float				m_fJumpSpeed;		// �W�����v���x   
	float				m_fNormalSpeed;			// �ŏ��ɐݒ肵�����x       

	int					m_nWeaponNo;		//�X�L���̃i���o�[	
	int					m_nWeaponColuman;		//�X�L����	 
	int					m_nWeaponColumanNo[10];		//�X�L�����ɓ����Ă���X�L���̃i���o�[		

	int					SaveEndFrame;	//�A�j���[�V�����t���[���̐�
	int					m_nFrameTrigger;	//�A�j���[�V�����t���[���̃g���K�[	
	
	BOOL				bSwordHitTrigger;

	int					nSkillTime[3];			//�X�L���̃X�L������		
	int					nCount[3];				//60�t���[���ň�b�����邽�߂̕ϐ�	
	BOOL				bSkillActive[3];		//�X�L��������			
	BOOL				bSpeedSkillTrigger;		//�X�s�[�h�A�b�v�g�p��
	DWORD				dwUseNumSkill;			//�g�p�����X�L���̉�	

	BOOL				bBoolSkillTrigger;		//�{�[���X�L���g�p��

	DWORD				dwRotCount;
	DWORD				dwRotTrigger;

	int	test;
	
	AFTERSTATUS			AfterSta;				//�c���̃X�e�[�^�X
	int					nAfterCount;			//�c����̊Ԋu
	int				    nAftTime;					//�c���̂��߂̃J�E���g

public:
	void Update() override;
	void UpdateNormal();       
	void UpdateNormalMove();  
	MATRIX4X4 UpdateNormalMoveKeystate(DWORD DIKey); 
	MATRIX4X4 UpdateNormalFirstPCMove(MATRIX4X4 mPos);  
	MATRIX4X4 UpdateNormalSecondPCMove(MATRIX4X4 mPos); 
	void SwingMoveFirst();
	void SwingMoveSecond();

	void UpdateNormalAttack(); 
	void UpdateDamage();       
	void SetMesh(CPcProc* pProc);
	void SetMeshSecond(CPcProc* pProc);
	MATRIX4X4  GetLocalMatrix();			// ���[�J�����}�g���b�N�X�𓾂�
	void SetLocalRotY(float fRotY) { m_fLocalRotY = fRotY; }   // ���[�J����(Y��)���Z�b�g����

	void	 SetWeaponNo(int No) { m_nWeaponNo = No; }		//�X�L���̃i���o�[�����ւ�		
	int		 GetWeaponNo() { return m_nWeaponNo; }			//�X�L���̃i���o�[���擾		

	void	 SetWeaponColuman(int n) { m_nWeaponColuman=n; }
	int		 GetWeaponColuman() { return m_nWeaponColuman; }			//�X�L�������擾			

	void	 SetSaveEndFrame(int n) { SaveEndFrame = n; }	
	int		 GetSaveEndFrame() { return SaveEndFrame; }		

	void	 SetFrameTrigger(int n) { m_nFrameTrigger = n; }	
	int		 GetFrameTrigger() { return m_nFrameTrigger; }	

	void	SetSwordHitTrigger(BOOL Trigger) { bSwordHitTrigger = Trigger; }
	BOOL	GetSwordHitTrigger() { return bSwordHitTrigger; }

	int		GetSkillActive(int nWeaponColumanNo) { return bSkillActive[nWeaponColumanNo]; }

	void	SpeedUpAft();
	void	SetSkillNo(const int nSkillColumanNo);
	void	SwingAnimProcess(const int nSwingAnimNo);

	BOOL	SkillStart(const int nWeaponColumanNo) ;	
	void	SkillUpdate();				
	void	SkillTime(const int nWeaponColumanNo);
	DWORD	GetUseNumSkill() { return dwUseNumSkill; }
	void	SetUseNumSkill(DWORD dwNum) { dwUseNumSkill = dwNum; }

	BOOL	GetBoolSkillTrigger() { return bBoolSkillTrigger; }
	DWORD	GetWeaponColumanNo(DWORD No) { return m_nWeaponColumanNo[No]; }
	void	SetWeaponColumanNo(DWORD No, DWORD nWeaponColumanNo) { m_nWeaponColumanNo[No] = nWeaponColumanNo; }
	void	WeaponUseMulti();
	void	Init();		

	CPcObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CPcObj();
};

//======================================================================
// �v���C�L�����N�^�[�@�v���V�[�W���N���X
//======================================================================
class CPcProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;				// Fbx�X�L�����b�V��
	CFbxMesh*           m_pMeshSecond;				// Fbx�X�L�����b�V��
	BASEHOLDITEM        m_nHoldItem;			// ��Ɏ��X�L��
	int				    m_nPcNum;



public:
	// �A�N�Z�X�֐�
	CFbxMesh*           GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��
	CFbxMesh*           GetMeshSecond() { return m_pMeshSecond; }		// Fbx�X�L�����b�V��
	BASEHOLDITEM        GetHoldItem() { return m_nHoldItem; }	// ��Ɏ��A�C�e���̒l
	CPcObj*			    GetPcObjPtr() { return (CPcObj*)GetObjArrayPtr()[0]; }
	int				    GetPcNum() { return m_nPcNum; }
	void				AddPcNum(int Num) { m_nPcNum += Num; }

	CPcObj*			    GetPcSecObjPtr() { return (CPcObj*)GetObjArrayPtr()[1]; }


	// �R���X�g���N�^
	CPcProc(CGameMain* pGMain);
	virtual	~CPcProc();
};
