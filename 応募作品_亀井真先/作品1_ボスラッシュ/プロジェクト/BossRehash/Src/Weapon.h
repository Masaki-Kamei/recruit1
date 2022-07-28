//=============================================================================
//
//      武器の処理
//																Weapon.h
//=============================================================================

#pragma once

//警告非表示
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)


//ヘッダーファイルのインクルード
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
// 武器・ショット　オブジェクトクラス
class CWeaponShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// コンストラクタ
	CWeaponShotObj(CGameMain* pGMain);
	~CWeaponShotObj();

};

//======================================================================
// 武器・ショット　プロシージャクラス
class CWeaponShotProc : public CBaseProc
{
public:
	BOOL Start( VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponShotProc() { ; }

};

//======================================================================
// 武器・シールド　オブジェクトクラス
class CWeaponShieldObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);
	void Update() override;

	// コンストラクタ
	CWeaponShieldObj(CGameMain* pGMain);
	~CWeaponShieldObj();

};

//======================================================================
// 武器・シールド　プロシージャクラス
class CWeaponShieldProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponShieldProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponShieldProc() { ; }

};

//======================================================================
// 武器・爆弾　オブジェクトクラス
class CWeaponBoomObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int BoomRangeHit;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// コンストラクタ
	CWeaponBoomObj(CGameMain* pGMain);
	~CWeaponBoomObj();

};

//======================================================================
// 武器・爆弾　プロシージャクラス
class CWeaponBoomProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponBoomProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponBoomProc() { ; }

};

//======================================================================
// 武器・近接攻撃　オブジェクトクラス
class CWeaponProAtkObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int Time=0;
	int TimeSave=0;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// コンストラクタ
	CWeaponProAtkObj(CGameMain* pGMain);
	~CWeaponProAtkObj();

};

//======================================================================
// 武器・近接攻撃　プロシージャクラス
class CWeaponProAtkProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponProAtkProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponProAtkProc() { ; }

};

//======================================================================
// 武器・拡散ショット　オブジェクトクラス
class CWeaponDifShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;
	

public:
	
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwNo, DWORD dwOwner);
	void Update() override;

	// コンストラクタ
	CWeaponDifShotObj(CGameMain* pGMain);
	~CWeaponDifShotObj();

};

//======================================================================
// 武器・拡散ショット　プロシージャクラス
class CWeaponDifShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj,  DWORD dwOwner);

	CWeaponDifShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponDifShotProc() { ; }

};

//======================================================================
// 武器・チャージショット　オブジェクトクラス
class CWeaponCharShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// コンストラクタ
	CWeaponCharShotObj(CGameMain* pGMain);
	~CWeaponCharShotObj();

};

//======================================================================
// 武器・チャージショット　プロシージャクラス
class CWeaponCharShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponCharShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponCharShotProc() { ; }

};

//======================================================================
// 武器・バウンドショット　オブジェクトクラス
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

	// コンストラクタ
	CWeaponBoundShotObj(CGameMain* pGMain);
	~CWeaponBoundShotObj();

};

//======================================================================
// 武器・バウンドショット　プロシージャクラス
class CWeaponBoundShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponBoundShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponBoundShotProc() { ; }

};

//======================================================================
// 武器・オオカミスペシャルショット　オブジェクトクラス
class CWeaponSpWolfShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;


public:

	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwNo, DWORD dwOwner);
	void Update() override;

	// コンストラクタ
	CWeaponSpWolfShotObj(CGameMain* pGMain);
	~CWeaponSpWolfShotObj();

};

//======================================================================
// 武器・オオカミスペシャルショット　プロシージャクラス
class CWeaponSpWolfShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponSpWolfShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponSpWolfShotProc() { ; }

};

//======================================================================
// 武器・オオカミショット　オブジェクトクラス
class CWeaponWolfShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;


public:

	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwNo, DWORD dwOwner);
	void Update() override;

	// コンストラクタ
	CWeaponWolfShotObj(CGameMain* pGMain);
	~CWeaponWolfShotObj();

};

//======================================================================
// 武器・オオカミショット　プロシージャクラス
class CWeaponWolfShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponWolfShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponWolfShotProc() { ; }

};

//======================================================================
// 武器・キツネショット　オブジェクトクラス
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

	// コンストラクタ
	CWeaponFoxShotObj(CGameMain* pGMain);
	~CWeaponFoxShotObj();

};

//======================================================================
// 武器・キツネショット　プロシージャクラス
class CWeaponFoxShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponFoxShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponFoxShotProc() { ; }

};

//======================================================================
// 武器・キツネサブショット　オブジェクトクラス
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

	// コンストラクタ
	CWeaponFoxSubShotObj(CGameMain* pGMain);
	~CWeaponFoxSubShotObj();

};

//======================================================================
// 武器・キツネサブショット　プロシージャクラス
class CWeaponFoxSubShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponFoxSubShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponFoxSubShotProc() { ; }

};

//======================================================================
// 武器・キツネスペシャルショット　オブジェクトクラス
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

	// コンストラクタ
	CWeaponFoxSpShotObj(CGameMain* pGMain);
	~CWeaponFoxSpShotObj();

};

//======================================================================
// 武器・キツネスペシャルショット　プロシージャクラス
class CWeaponFoxSpShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponFoxSpShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponFoxSpShotProc() { ; }

};

//======================================================================
// 武器・がま茶色ショット　オブジェクトクラス
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

	// コンストラクタ
	CWeaponTordBrownShotObj(CGameMain* pGMain);
	~CWeaponTordBrownShotObj();

};

//======================================================================
// 武器・がま茶色ショット　プロシージャクラス
class CWeaponTordBrownShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponTordBrownShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponTordBrownShotProc() { ; }

};

//======================================================================
// 武器・がま茶色スペシャルショット　オブジェクトクラス
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

	// コンストラクタ
	CWeaponTordBrownSpShotObj(CGameMain* pGMain);
	~CWeaponTordBrownSpShotObj();

};

//======================================================================
// 武器・がま茶色スペシャルショット　プロシージャクラス
class CWeaponTordBrownSpShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponTordBrownSpShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponTordBrownSpShotProc() { ; }

};

//======================================================================
// 武器・ガマショット　オブジェクトクラス
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

	// コンストラクタ
	CWeaponTordShotObj(CGameMain* pGMain);
	~CWeaponTordShotObj();

};

//======================================================================
// 武器・ガマショット　プロシージャクラス
class CWeaponTordShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponTordShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponTordShotProc() { ; }

};


//======================================================================
// 武器・ガマスペシャルショット　オブジェクトクラス
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
	int WeaponStop;		//攻撃停止

	int StageWidth;
	int StageHeight;

	float tan;




public:
	BOOL Start(VECTOR2 , CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// コンストラクタ
	CWeaponTordSpShotObj(CGameMain* pGMain);
	~CWeaponTordSpShotObj();

};

//======================================================================
// 武器・ガマスペシャルショット　プロシージャクラス
class CWeaponTordSpShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponTordSpShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponTordSpShotProc() { ; }

};

//======================================================================
// 武器・ガマサブショット　オブジェクトクラス
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

	// コンストラクタ
	CWeaponTordSubShotObj(CGameMain* pGMain);
	~CWeaponTordSubShotObj();

};

//======================================================================
// 武器・ガマサブショット　プロシージャクラス
class CWeaponTordSubShotProc : public CBaseProc
{
protected:

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponTordSubShotProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponTordSubShotProc() { ; }

};


//======================================================================
// 武器・最後の敵サブショット　オブジェクトクラス
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

	// コンストラクタ
	CEnmLastSubShotObj(CGameMain* pGMain);
	~CEnmLastSubShotObj();

};

//======================================================================
// 武器・最後の敵サブショット　プロシージャクラス
class CEnmLastSubShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CEnmLastSubShotProc(CGameMain* pGMain);	// コンストラクタ
	~CEnmLastSubShotProc() { ; }

};

//======================================================================
// 武器・最後の敵スペシャルショット　オブジェクトクラス
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

	// コンストラクタ
	CEnmLastSpShotObj(CGameMain* pGMain);
	~CEnmLastSpShotObj();

};

//======================================================================
// 武器・最後の敵スペシャルショット　プロシージャクラス
class CEnmLastSpShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CEnmLastSpShotProc(CGameMain* pGMain);	// コンストラクタ
	~CEnmLastSpShotProc() { ; }

};


//======================================================================
// 武器・最後の敵スペシャルサブショット　オブジェクトクラス
class CEnmLastSpSubShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	int m_vSitPos = 0;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// コンストラクタ
	CEnmLastSpSubShotObj(CGameMain* pGMain);
	~CEnmLastSpSubShotObj();

};

//======================================================================
// 武器・最後の敵スペシャルサブショット　プロシージャクラス
class CEnmLastSpSubShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CEnmLastSpSubShotProc(CGameMain* pGMain);	// コンストラクタ
	~CEnmLastSpSubShotProc() { ; }

};



//======================================================================
// 武器・レーザー　オブジェクトクラス
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

	// コンストラクタ
	CWeaponLaserObj(CGameMain* pGMain);
	~CWeaponLaserObj();

};

//======================================================================
// 武器・レーザー　プロシージャクラス
class CWeaponLaserProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponLaserProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponLaserProc() { ; }

};



//======================================================================
// 武器全体のメインプロシージャクラス
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

	CWeaponProc(CGameMain* pGMain);	// コンストラクタ
	~CWeaponProc() { ; }
};

