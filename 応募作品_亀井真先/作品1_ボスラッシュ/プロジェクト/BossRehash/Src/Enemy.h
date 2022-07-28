//=============================================================================
//
//		敵の処理
//																Enamy.h
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


#define  ENM_WATER_MAX  30
#define  ENM_TORD_MAX  20
#define  ENM_WOLF_MAX  20
#define  ENM_FOX_MAX  20 

#define WEAPON_ENMLASTSUBBIT_MAX 2


//======================================================================
// 泉の水の敵　オブジェクトクラス
class CEnmWaterObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// コンストラクタ
	CEnmWaterObj(CGameMain* pGMain);
	~CEnmWaterObj();

};
//======================================================================
// 泉の水の敵　プロシージャクラス
class CEnmWaterProc : public CBaseProc
{
protected:
	;

public:
	void   Update() override;

	// コンストラクタ
	CEnmWaterProc(CGameMain* pGMain);
	~CEnmWaterProc() { ; }

};
//======================================================================
// がまの敵　オブジェクトクラス
class CEnmTordObj : public CBaseObj
{
protected:
	int	m_nEnmpositionx;	//座標保存X
	int	m_nEnmpositiony;	//座標保存Y


	int WeaponStop;		//攻撃停止
	int Jump;
	int Direction;			//向き
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

	// コンストラクタ
	CEnmTordObj(CGameMain* pGMain);
	~CEnmTordObj();

};
//======================================================================
// がまの敵　プロシージャクラス
class CEnmTordProc : public CBaseProc
{
protected:
	;

public:
	void   Update() override;

	// コンストラクタ
	CEnmTordProc(CGameMain* pGMain);
	~CEnmTordProc() { ; }

};

//======================================================================
// オオカミの敵　オブジェクトクラス
class CEnmWolfObj : public CBaseObj
{
protected:
	int	m_nEnmpositionx ;	//座標保存X
	int	m_nEnmpositiony;	//座標保存Y


	int WeaponStop ;		//攻撃停止
	int Jump;
	int Direction;			//向き
	int  m_nDifShotWait;


	int SpNum;
	int SpPosx;
	int SpDis;
	int SpCol;
	

	int Damage = 0;



public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// コンストラクタ
	CEnmWolfObj(CGameMain* pGMain);
	~CEnmWolfObj();

};
//======================================================================
// オオカミの敵　プロシージャクラス
class CEnmWolfProc : public CBaseProc
{
protected:

	;

public:
	void   Update() override;

	// コンストラクタ
	CEnmWolfProc(CGameMain* pGMain);
	~CEnmWolfProc() { ; }

};
//======================================================================
// きつねの敵　オブジェクトクラス
class CEnmFoxObj : public CBaseObj
{
protected:
	int	m_nEnmpositionx;	//座標保存X
	int	m_nEnmpositiony;	//座標保存Y

	int WeaponStop;		//攻撃停止
	int Jump;
	int Direction;			//向き

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

	// コンストラクタ
	CEnmFoxObj(CGameMain* pGMain);
	~CEnmFoxObj();

};
//======================================================================
// きつねの敵　プロシージャクラス
class CEnmFoxProc : public CBaseProc
{
protected:

	;

public:
	void   Update() override;

	// コンストラクタ
	CEnmFoxProc(CGameMain* pGMain);
	~CEnmFoxProc() { ; }
};

	//======================================================================
// がま茶色の敵　オブジェクトクラス
	class CEnmTordBrownObj : public CBaseObj
	{
	protected:
		int	m_nEnmpositionx;	//座標保存X
		int	m_nEnmpositiony;	//座標保存Y


		int WeaponStop;		//攻撃停止
		int Jump;
		int Direction;			//向き
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

		// コンストラクタ
		CEnmTordBrownObj(CGameMain* pGMain);
		~CEnmTordBrownObj();

	};
	//======================================================================
	// がま茶色の敵　プロシージャクラス
	class CEnmTordBrownProc : public CBaseProc
	{
	protected:
		;

	public:
		void   Update() override;

		// コンストラクタ
		CEnmTordBrownProc(CGameMain* pGMain);
		~CEnmTordBrownProc() { ; }

	};

	//======================================================================
// 最後の敵　オブジェクトクラス
	class CEnmLastObj : public CBaseObj
	{
	protected:
		int	m_nEnmpositionx;	//座標保存X
		int	m_nEnmpositiony;	//座標保存Y


		int WeaponStop;		//攻撃停止
		int Jump;
		int Direction;			//向き
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

		// コンストラクタ
		CEnmLastObj(CGameMain* pGMain);
		~CEnmLastObj();

	};
	//======================================================================
	// 最後の敵　プロシージャクラス
	class CEnmLastProc : public CBaseProc
	{
	protected:
		;

	public:
		void   Update() override;

		// コンストラクタ
		CEnmLastProc(CGameMain* pGMain);
		~CEnmLastProc() { ; }

	};


	//======================================================================
// 最後のサブ敵　オブジェクトクラス
	class CEnmLastSubObj : public CBaseObj
	{
	protected:
		int	m_nEnmpositionx;	//座標保存X
		int	m_nEnmpositiony;	//座標保存Y


		int WeaponStop;		//攻撃停止
		int Jump;
		int Direction;			//向き
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

		// コンストラクタ
		CEnmLastSubObj(CGameMain* pGMain);
		~CEnmLastSubObj();

	};
	//======================================================================
	// 最後のサブ敵　プロシージャクラス
	class CEnmLastSubProc : public CBaseProc
	{
	protected:

		;

	public:
		BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);


		// コンストラクタ
		CEnmLastSubProc(CGameMain* pGMain);
		~CEnmLastSubProc() { ; }

	};

	//======================================================================

//======================================================================
// 敵キャラクター全体のメインプロシージャクラス
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

	CEnmProc(CGameMain* pGMain);	// コンストラクタ
	~CEnmProc() { ; }

};

