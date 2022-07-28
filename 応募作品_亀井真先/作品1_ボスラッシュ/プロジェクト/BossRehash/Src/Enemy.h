//=============================================================================
//
//		�G�̏���
//																Enamy.h
//=============================================================================

#pragma once

//�x����\��
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)


//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite.h"


#define  ENM_WATER_MAX  30
#define  ENM_TORD_MAX  20
#define  ENM_WOLF_MAX  20
#define  ENM_FOX_MAX  20 

#define WEAPON_ENMLASTSUBBIT_MAX 2


//======================================================================
// ��̐��̓G�@�I�u�W�F�N�g�N���X
class CEnmWaterObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmWaterObj(CGameMain* pGMain);
	~CEnmWaterObj();

};
//======================================================================
// ��̐��̓G�@�v���V�[�W���N���X
class CEnmWaterProc : public CBaseProc
{
protected:
	;

public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmWaterProc(CGameMain* pGMain);
	~CEnmWaterProc() { ; }

};
//======================================================================
// ���܂̓G�@�I�u�W�F�N�g�N���X
class CEnmTordObj : public CBaseObj
{
protected:
	int	m_nEnmpositionx;	//���W�ۑ�X
	int	m_nEnmpositiony;	//���W�ۑ�Y


	int WeaponStop;		//�U����~
	int Jump;
	int Direction;			//����
	int  m_nDifShotWait;


	int SpNum;
	int SpPosx;
	int SpPosy;
	int SpDis;
	int SpCol;
	int WeponPosy;
	int SpStop;


	int Damage = 0;


	

public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmTordObj(CGameMain* pGMain);
	~CEnmTordObj();

};
//======================================================================
// ���܂̓G�@�v���V�[�W���N���X
class CEnmTordProc : public CBaseProc
{
protected:
	;

public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmTordProc(CGameMain* pGMain);
	~CEnmTordProc() { ; }

};

//======================================================================
// �I�I�J�~�̓G�@�I�u�W�F�N�g�N���X
class CEnmWolfObj : public CBaseObj
{
protected:
	int	m_nEnmpositionx ;	//���W�ۑ�X
	int	m_nEnmpositiony;	//���W�ۑ�Y


	int WeaponStop ;		//�U����~
	int Jump;
	int Direction;			//����
	int  m_nDifShotWait;


	int SpNum;
	int SpPosx;
	int SpDis;
	int SpCol;
	

	int Damage = 0;



public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmWolfObj(CGameMain* pGMain);
	~CEnmWolfObj();

};
//======================================================================
// �I�I�J�~�̓G�@�v���V�[�W���N���X
class CEnmWolfProc : public CBaseProc
{
protected:

	;

public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmWolfProc(CGameMain* pGMain);
	~CEnmWolfProc() { ; }

};
//======================================================================
// ���˂̓G�@�I�u�W�F�N�g�N���X
class CEnmFoxObj : public CBaseObj
{
protected:
	int	m_nEnmpositionx;	//���W�ۑ�X
	int	m_nEnmpositiony;	//���W�ۑ�Y

	int WeaponStop;		//�U����~
	int Jump;
	int Direction;			//����

	int SpAtc=0;
	int SpTime;
	int SpNum;
	int SpDis;
	int SpCol;
	int EnmWalk;

	int Damage = 0;


public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmFoxObj(CGameMain* pGMain);
	~CEnmFoxObj();

};
//======================================================================
// ���˂̓G�@�v���V�[�W���N���X
class CEnmFoxProc : public CBaseProc
{
protected:

	;

public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmFoxProc(CGameMain* pGMain);
	~CEnmFoxProc() { ; }
};

	//======================================================================
// ���ܒ��F�̓G�@�I�u�W�F�N�g�N���X
	class CEnmTordBrownObj : public CBaseObj
	{
	protected:
		int	m_nEnmpositionx;	//���W�ۑ�X
		int	m_nEnmpositiony;	//���W�ۑ�Y


		int WeaponStop;		//�U����~
		int Jump;
		int Direction;			//����
		int  m_nDifShotWait;


		int SpNum;
		int SpPosx;
		int SpDis;
		int SpCol;
		int SpAtc;
		int SpTime;
		int SpStop;
		float HpSpeedUp;

		float PosxSave = 0;
		float PosySave = 0;

		int Damage = 0;
		

	public:
		BOOL Start(VECTOR2 vPos) override;
		void Update() override;

		// �R���X�g���N�^
		CEnmTordBrownObj(CGameMain* pGMain);
		~CEnmTordBrownObj();

	};
	//======================================================================
	// ���ܒ��F�̓G�@�v���V�[�W���N���X
	class CEnmTordBrownProc : public CBaseProc
	{
	protected:
		;

	public:
		void   Update() override;

		// �R���X�g���N�^
		CEnmTordBrownProc(CGameMain* pGMain);
		~CEnmTordBrownProc() { ; }

	};

	//======================================================================
// �Ō�̓G�@�I�u�W�F�N�g�N���X
	class CEnmLastObj : public CBaseObj
	{
	protected:
		int	m_nEnmpositionx;	//���W�ۑ�X
		int	m_nEnmpositiony;	//���W�ۑ�Y


		int WeaponStop;		//�U����~
		int Jump;
		int Direction;			//����
		int  m_nDifShotWait;

		int EnmSpShotWait;


		int SpNum;
		int SpDis;
		int SpCol;
		int WeponPosy;

		int  WeponChange;


		int SpCharAtc;
		int SpCharTime;
		int EnmCharWalk;


		int TordBrownWait;
		int SpBoomStop;
		int SpBoomAtc;
		int SpBoomTime;

		int SpBoundStop = 0;


		int EnmBoundWait;

		int WeaponBitTime = 0;

		int Damage = 0;

		int SpStartNum = 0;


	public:
		BOOL Start(VECTOR2 vPos) override;
		void Update() override;

		// �R���X�g���N�^
		CEnmLastObj(CGameMain* pGMain);
		~CEnmLastObj();

	};
	//======================================================================
	// �Ō�̓G�@�v���V�[�W���N���X
	class CEnmLastProc : public CBaseProc
	{
	protected:
		;

	public:
		void   Update() override;

		// �R���X�g���N�^
		CEnmLastProc(CGameMain* pGMain);
		~CEnmLastProc() { ; }

	};


	//======================================================================
// �Ō�̃T�u�G�@�I�u�W�F�N�g�N���X
	class CEnmLastSubObj : public CBaseObj
	{
	protected:
		int	m_nEnmpositionx;	//���W�ۑ�X
		int	m_nEnmpositiony;	//���W�ۑ�Y


		int WeaponStop;		//�U����~
		int Jump;
		int Direction;			//����
		int  m_nDifShotWait;


		int SpNum;
		int SpPosx;
		int SpDis;
		int SpCol;

		int PcPosySave;
		int PcPosxSave;
		int PosySave;
		int PosxSave;



	public:
		BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
		void Update() override;

		// �R���X�g���N�^
		CEnmLastSubObj(CGameMain* pGMain);
		~CEnmLastSubObj();

	};
	//======================================================================
	// �Ō�̃T�u�G�@�v���V�[�W���N���X
	class CEnmLastSubProc : public CBaseProc
	{
	protected:

		;

	public:
		BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);


		// �R���X�g���N�^
		CEnmLastSubProc(CGameMain* pGMain);
		~CEnmLastSubProc() { ; }

	};

	//======================================================================

//======================================================================
// �G�L�����N�^�[�S�̂̃��C���v���V�[�W���N���X
//======================================================================




class CEnmProc : public CBaseProc
{
public:
	CEnmWaterProc*	m_pEnmWaterProc;
	CEnmTordProc*	m_pEnmTordProc;
	CEnmWolfProc*	m_pEnmWolfProc;
	CEnmFoxProc*	m_pEnmFoxProc;
	CEnmTordBrownProc*   m_pEnmTordBrownProc;
	CEnmLastProc*	m_pEnmLastProc;

	CEnmLastSubProc*	m_pEnmLastSubProc;


public:
	void  SetNonActive();

	CEnmProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEnmProc() { ; }

};

