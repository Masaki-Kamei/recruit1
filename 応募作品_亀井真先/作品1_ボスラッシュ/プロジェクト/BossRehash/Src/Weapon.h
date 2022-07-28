//=============================================================================
//
//      ����̏���
//																Weapon.h
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
#include "Map.h"


#define  WEAPON_SHOT_MAX  200
#define  WEAPON_DIFSHOT_MAX  200
#define  WEAPON_SHIELD_MAX 1
#define  WEAPON_BOOM_MAX 3
#define  WEAPON_PROATK_MAX 1
#define  WEAPON_CHARSHOT_MAX 1
#define  WEAPON_BOUNDSHOT_MAX  200


#define  WEAPON_SPWOLFSHOT_MAX 200


#define  WEAPON_FOXSHOT_MAX 200
#define  WEAPON_FOXSUBSHOT_MAX 200
#define  WEAPON_FOXSPSHOT_MAX 200


#define  WEAPON_TORDBROWNSHOT_MAX 200
#define  WEAPON_TORDBROWNSPSHOT_MAX 200


#define  WEAPON_TORDSHOT_MAX 200
#define  WEAPON_TORDSPSHOT_MAX 1
#define  WEAPON_TORDSUBSHOT_MAX 200



#define WEAPON_ENMLASTSUBSHOT_MAX 200
#define WEAPON_ENMLASTSUBBIT_MAX 2
#define WEAPON_LASER_MAX   200
#define WEAPON_ENMLASTSPSHOT_MAX 1


//======================================================================
// ����E�V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// �R���X�g���N�^
	CWeaponShotObj(CGameMain* pGMain);
	~CWeaponShotObj();

};

//======================================================================
// ����E�V���b�g�@�v���V�[�W���N���X
class CWeaponShotProc : public CBaseProc
{
public:
	BOOL Start( VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponShotProc() { ; }

};

//======================================================================
// ����E�V�[���h�@�I�u�W�F�N�g�N���X
class CWeaponShieldObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);
	void Update() override;

	// �R���X�g���N�^
	CWeaponShieldObj(CGameMain* pGMain);
	~CWeaponShieldObj();

};

//======================================================================
// ����E�V�[���h�@�v���V�[�W���N���X
class CWeaponShieldProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponShieldProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponShieldProc() { ; }

};

//======================================================================
// ����E���e�@�I�u�W�F�N�g�N���X
class CWeaponBoomObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int BoomRangeHit;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// �R���X�g���N�^
	CWeaponBoomObj(CGameMain* pGMain);
	~CWeaponBoomObj();

};

//======================================================================
// ����E���e�@�v���V�[�W���N���X
class CWeaponBoomProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponBoomProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponBoomProc() { ; }

};

//======================================================================
// ����E�ߐڍU���@�I�u�W�F�N�g�N���X
class CWeaponProAtkObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int Time=0;
	int TimeSave=0;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// �R���X�g���N�^
	CWeaponProAtkObj(CGameMain* pGMain);
	~CWeaponProAtkObj();

};

//======================================================================
// ����E�ߐڍU���@�v���V�[�W���N���X
class CWeaponProAtkProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponProAtkProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponProAtkProc() { ; }

};

//======================================================================
// ����E�g�U�V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponDifShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;
	

public:
	
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwNo, DWORD dwOwner);
	void Update() override;

	// �R���X�g���N�^
	CWeaponDifShotObj(CGameMain* pGMain);
	~CWeaponDifShotObj();

};

//======================================================================
// ����E�g�U�V���b�g�@�v���V�[�W���N���X
class CWeaponDifShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj,  DWORD dwOwner);

	CWeaponDifShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponDifShotProc() { ; }

};

//======================================================================
// ����E�`���[�W�V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponCharShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// �R���X�g���N�^
	CWeaponCharShotObj(CGameMain* pGMain);
	~CWeaponCharShotObj();

};

//======================================================================
// ����E�`���[�W�V���b�g�@�v���V�[�W���N���X
class CWeaponCharShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponCharShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponCharShotProc() { ; }

};

//======================================================================
// ����E�o�E���h�V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponBoundShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;
	int BoundNum = 0;
	float fSpeedx = 0;
	int y;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// �R���X�g���N�^
	CWeaponBoundShotObj(CGameMain* pGMain);
	~CWeaponBoundShotObj();

};

//======================================================================
// ����E�o�E���h�V���b�g�@�v���V�[�W���N���X
class CWeaponBoundShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponBoundShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponBoundShotProc() { ; }

};

//======================================================================
// ����E�I�I�J�~�X�y�V�����V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponSpWolfShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;


public:

	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwNo, DWORD dwOwner);
	void Update() override;

	// �R���X�g���N�^
	CWeaponSpWolfShotObj(CGameMain* pGMain);
	~CWeaponSpWolfShotObj();

};

//======================================================================
// ����E�I�I�J�~�X�y�V�����V���b�g�@�v���V�[�W���N���X
class CWeaponSpWolfShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponSpWolfShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponSpWolfShotProc() { ; }

};

//======================================================================
// ����E�I�I�J�~�V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponWolfShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;


public:

	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwNo, DWORD dwOwner);
	void Update() override;

	// �R���X�g���N�^
	CWeaponWolfShotObj(CGameMain* pGMain);
	~CWeaponWolfShotObj();

};

//======================================================================
// ����E�I�I�J�~�V���b�g�@�v���V�[�W���N���X
class CWeaponWolfShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponWolfShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponWolfShotProc() { ; }

};

//======================================================================
// ����E�L�c�l�V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponFoxShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;


	int CharShot = 0;
	int CharMove = 0;

public:

	BOOL Start(VECTOR2, CBaseObj* pObj,  DWORD dwOwner);
	void Update() override;

	// �R���X�g���N�^
	CWeaponFoxShotObj(CGameMain* pGMain);
	~CWeaponFoxShotObj();

};

//======================================================================
// ����E�L�c�l�V���b�g�@�v���V�[�W���N���X
class CWeaponFoxShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponFoxShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponFoxShotProc() { ; }

};

//======================================================================
// ����E�L�c�l�T�u�V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponFoxSubShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;


	int CharShot = 0;
	int CharMove = 0;

public:

	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);
	void Update() override;

	// �R���X�g���N�^
	CWeaponFoxSubShotObj(CGameMain* pGMain);
	~CWeaponFoxSubShotObj();

};

//======================================================================
// ����E�L�c�l�T�u�V���b�g�@�v���V�[�W���N���X
class CWeaponFoxSubShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponFoxSubShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponFoxSubShotProc() { ; }

};

//======================================================================
// ����E�L�c�l�X�y�V�����V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponFoxSpShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;


	int CharShot = 0;
	int SpCharMove = 0;

	float PosxSave = 0;
	float PosySave = 0;
	float PcPosxSave = 0;
	float PcPosySave = 0;
	float WeponNumx = 0;
	float WeponNumy = 0;

public:

	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);
	void Update() override;

	// �R���X�g���N�^
	CWeaponFoxSpShotObj(CGameMain* pGMain);
	~CWeaponFoxSpShotObj();

};

//======================================================================
// ����E�L�c�l�X�y�V�����V���b�g�@�v���V�[�W���N���X
class CWeaponFoxSpShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponFoxSpShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponFoxSpShotProc() { ; }

};

//======================================================================
// ����E���ܒ��F�V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponTordBrownShotObj : public CBaseObj
{
protected:
	int EnmHit;
	int BoomTime=0;
	int Explosion = 0;

	DWORD  m_dwOwner;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// �R���X�g���N�^
	CWeaponTordBrownShotObj(CGameMain* pGMain);
	~CWeaponTordBrownShotObj();

};

//======================================================================
// ����E���ܒ��F�V���b�g�@�v���V�[�W���N���X
class CWeaponTordBrownShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponTordBrownShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponTordBrownShotProc() { ; }

};

//======================================================================
// ����E���ܒ��F�X�y�V�����V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponTordBrownSpShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int EnmHit;
	int BoomTime = 0;
	int fSpeed = 0;
	int Explosion = 0;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) ;
	void Update() override;

	// �R���X�g���N�^
	CWeaponTordBrownSpShotObj(CGameMain* pGMain);
	~CWeaponTordBrownSpShotObj();

};

//======================================================================
// ����E���ܒ��F�X�y�V�����V���b�g�@�v���V�[�W���N���X
class CWeaponTordBrownSpShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponTordBrownSpShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponTordBrownSpShotProc() { ; }

};

//======================================================================
// ����E�K�}�V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponTordShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;
	int BoundNum = 0;
	float fSpeedx = 0;
	int Boundy=0;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// �R���X�g���N�^
	CWeaponTordShotObj(CGameMain* pGMain);
	~CWeaponTordShotObj();

};

//======================================================================
// ����E�K�}�V���b�g�@�v���V�[�W���N���X
class CWeaponTordShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponTordShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponTordShotProc() { ; }

};


//======================================================================
// ����E�K�}�X�y�V�����V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponTordSpShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;
	int BoundNum = 0;
	float fSpeedx = 0;


	float PcPosxSave = 0;
	float PcPosySave = 0;
	float BoundTimeStop=0;
	float fSpeed = 0;
	int BoundNumMax=0;

	int  m_nDifShotWait;
	int WeaponStop;		//�U����~

	int StageWidth;
	int StageHeight;

	float tan;




public:
	BOOL Start(VECTOR2 , CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// �R���X�g���N�^
	CWeaponTordSpShotObj(CGameMain* pGMain);
	~CWeaponTordSpShotObj();

};

//======================================================================
// ����E�K�}�X�y�V�����V���b�g�@�v���V�[�W���N���X
class CWeaponTordSpShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponTordSpShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponTordSpShotProc() { ; }

};

//======================================================================
// ����E�K�}�T�u�V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponTordSubShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;
	int BoundNum = 0;
	float fSpeedx = 0;
	int Boundy = 0;
public:

	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);
	void Update() override;

	// �R���X�g���N�^
	CWeaponTordSubShotObj(CGameMain* pGMain);
	~CWeaponTordSubShotObj();

};

//======================================================================
// ����E�K�}�T�u�V���b�g�@�v���V�[�W���N���X
class CWeaponTordSubShotProc : public CBaseProc
{
protected:

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponTordSubShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponTordSubShotProc() { ; }

};


//======================================================================
// ����E�Ō�̓G�T�u�V���b�g�@�I�u�W�F�N�g�N���X
class CEnmLastSubShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;


	int CharShot = 0;
	int SpCharMove = 0;
	int ShotStart=0;

	float PosxSave = 0;
	float PosySave = 0;
	float PcPosxSave = 0;
	float PcPosySave = 0;
	float WeponNumx = 0;
	float WeponNumy = 0;

public:

	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);
	void Update() override;

	// �R���X�g���N�^
	CEnmLastSubShotObj(CGameMain* pGMain);
	~CEnmLastSubShotObj();

};

//======================================================================
// ����E�Ō�̓G�T�u�V���b�g�@�v���V�[�W���N���X
class CEnmLastSubShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CEnmLastSubShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEnmLastSubShotProc() { ; }

};

//======================================================================
// ����E�Ō�̓G�X�y�V�����V���b�g�@�I�u�W�F�N�g�N���X
class CEnmLastSpShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;
	int ShotTime = 0;
	int SpTime = 0;

	int CharShot = 0;
	int SpCharMove = 0;
	int ShotStart = 0;

	float PosxSave = 0;
	float PosySave = 0;
	float PcPosxSave = 0;
	float PcPosySave = 0;
	float WeponNumx = 0;
	float WeponNumy = 0;

public:

	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);
	void Update() override;

	// �R���X�g���N�^
	CEnmLastSpShotObj(CGameMain* pGMain);
	~CEnmLastSpShotObj();

};

//======================================================================
// ����E�Ō�̓G�X�y�V�����V���b�g�@�v���V�[�W���N���X
class CEnmLastSpShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CEnmLastSpShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEnmLastSpShotProc() { ; }

};


//======================================================================
// ����E�Ō�̓G�X�y�V�����T�u�V���b�g�@�I�u�W�F�N�g�N���X
class CEnmLastSpSubShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmLastSpSubShotObj(CGameMain* pGMain);
	~CEnmLastSpSubShotObj();

};

//======================================================================
// ����E�Ō�̓G�X�y�V�����T�u�V���b�g�@�v���V�[�W���N���X
class CEnmLastSpSubShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CEnmLastSpSubShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEnmLastSpSubShotProc() { ; }

};



//======================================================================
// ����E���[�U�[�@�I�u�W�F�N�g�N���X
class CWeaponLaserObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;


	int CharShot = 0;
	int SpCharMove = 0;
	int ShotStart = 0;

	float PosxSave = 0;
	float PosySave = 0;
	float PcPosxSave = 0;
	float PcPosySave = 0;
	float WeponNumx = 0;
	float WeponNumy = 0;

	int LaserPatten = 0;

public:

	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);
	void Update() override;

	// �R���X�g���N�^
	CWeaponLaserObj(CGameMain* pGMain);
	~CWeaponLaserObj();

};

//======================================================================
// ����E���[�U�[�@�v���V�[�W���N���X
class CWeaponLaserProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponLaserProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponLaserProc() { ; }

};



//======================================================================
// ����S�̂̃��C���v���V�[�W���N���X
//======================================================================
class CWeaponProc : public CBaseProc
{
public:
	CWeaponShotProc*	m_pWeaponShotProc;
	CWeaponShieldProc*	m_pWeaponShieldProc;
	CWeaponBoomProc*	m_pWeaponBoomProc;
	CWeaponProAtkProc*	m_pWeaponProAtkProc;
	CWeaponDifShotProc*	m_pWeaponDifShotProc;
	CWeaponCharShotProc*	m_pWeaponCharShotProc;
	CWeaponBoundShotProc*	m_pWeaponBoundShotProc;


	CWeaponWolfShotProc* m_pWeaponWolfShotProc;
	CWeaponSpWolfShotProc* m_pWeaponSpWolfShotProc;


	CWeaponFoxShotProc* m_pWeaponFoxShotProc;
	CWeaponFoxSubShotProc* m_pWeaponFoxSubShotProc;
	CWeaponFoxSpShotProc* m_pWeaponFoxSpShotProc;


	CWeaponTordBrownShotProc*  m_pWeaponTordBrownShotProc;
	CWeaponTordBrownSpShotProc*  m_pWeaponTordBrownSpShotProc;


	CWeaponTordShotProc*  m_pWeaponTordShotProc;
	CWeaponTordSpShotProc*  m_pWeaponTordSpShotProc;
	CWeaponTordSubShotProc*  m_pWeaponTordSubShotProc;

	CEnmLastSubShotProc* m_pEnmLastSubShotProc;
	CEnmLastSpShotProc* m_pEnmLastSpShotProc;
	CWeaponLaserProc*	m_pWeaponLaserProc;
	CEnmLastSpSubShotProc* m_pEnmLastSpSubShotProc;






public:

	CWeaponProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponProc() { ; }
};

