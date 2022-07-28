//=============================================================================
//
//		基本プロシージャ・基本オブジェクトクラス処理
//																BaseProc.h
//=============================================================================
#pragma once
#include "GameMain.h"

#define		PLAYER	1
#define		TARGET	2
#define		BALL	3


// -------------------------------------------------------------------------------------------------
// 
// 手に持つアイテムやスキルを指定する構造体
// 
// -------------------------------------------------------------------------------------------------
struct BASEHOLDITEM
{
	int				m_nHoldObjNo;	// 手に持つアイテムのオブジェクト番号
	int				m_nPosMesh;		// アイテムを持たせるスキンメッシュの位置　メッシュ番号
	int				m_nPosBone;		// アイテムを持たせるスキンメッシュの位置　ボーン番号
	VECTOR3			m_nOffsetPos;	// 手に持つアイテムの位置オフセット
	VECTOR3			m_nOffsetRot;	// 手に持つアイテムの角度オフセット
	BASEHOLDITEM()
	{
		m_nHoldObjNo = 0;				// 手に持つアイテムのオブジェクト番号
		m_nPosMesh = 0;					// アイテムを持たせるスキンメッシュの位置　メッシュ番号
		m_nPosBone = 0;					// アイテムを持たせるスキンメッシュの位置　ボーン番号
		m_nOffsetPos = VECTOR3(0, 0, 0);	// 手に持つアイテムの位置オフセット
		m_nOffsetRot = VECTOR3(0, 0, 0);	// 手に持つアイテムの角度オフセット
	}
};

class CBBox;
class CShader;
class CGameMain;
class CBaseProc;
// --------------------------------------------------------------------------------------------------
// 基本オブジェクトクラス
// 
// ＊　オブジェクトとは、ゲーム中に登場する一つ一つの物体、例えばＰＣや、スキルの１つなどを指す。
// 　　なお、オブジェクトは、各プロシージャのメンバー配列として宣言する
// 
// --------------------------------------------------------------------------------------------------
class CBaseObj
{
protected:
	CGameMain*		m_pGMain;			// ゲームメインクラス
	DWORD			m_dwStatus;			// ステータス
	DWORD			m_dwStatusSub;		// ステータスサブ
	DWORD			m_dwStatusPhase;	// ステータスフェーズ
	BOOL			m_bActive;			// TRUE:表示  FALSE:非表示
	DWORD			m_dwObjID;			// オブジェクトＩＤ
	DWORD			m_dwObjNo;			// オブジェクトＮＯ
	ANIMATION_STATUS m_AnimStatus;		// アニメーションステータス
	CBBox*			m_pBBox;			// バウンディングボックスクラス
	MATRIX4X4		m_mWorldOld;		// ワールドマトリクス（一つ前）
	MATRIX4X4		m_mWorld;			// ワールドマトリクス
	VECTOR3			m_vPosUp;			// 移動増分
	VECTOR3			m_vRotUp;			// 回転増分
	float			m_fJumpY;			// ジャンプ高さ
	float			m_fJumpTime;		// ジャンプ時間
	CBaseObj*		m_pOyaObj;			// 親オブジェクト（スキルオブジェ等）
	CBaseObj*		m_pHitObj;			// 当たった相手のオブジェクト
	VECTOR3			m_vHitPos;			// 当たった場所の座標
	VECTOR3			m_vHitNormal;		// 当たった場所の法線座標
	int             m_nCnt1;			// カウンター１
	int             m_nCnt2;			// カウンター２
	int				m_nMaxHp;			// 最大体力
	int				m_nHp;				// 体力
	int				m_nAtc;				// 攻撃力

	VECTOR3			m_vGravity;			// 重力


	float			m_fDist;
	BOOL			m_bDamage;			
	BOOL			bTarget;			//ターゲットされているか 
	
	CBaseObj*		m_pShaftObj;		//軸になるオブジェクト	
	BOOL			bShaftObjTrigger;	//範囲内にあるのかの判定
	float			m_fShaftDist;		//軸との距離

	DWORD			m_dWeaponUseNum;	//使用できるスキルの数
	DWORD			m_dwScorePoint;		//オブジェクトごとのポイント

	BOOL			m_bStop;			//オブジェクトの処理を止める

	DWORD			m_dwPlayerNo;
public:
	// オブジェクトの発生処理
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


	// あたり判定処理
	virtual BOOL    Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld);
	virtual BOOL    Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack);

	virtual BOOL    HitcheckOtherLay(CBaseObj* pOtherObj);				

	virtual BOOL    ObjGravity(CBaseObj* pOtherObj, float fDist, float fRotateSpeed);			
	virtual BOOL    ObjTarget(CBaseObj* pOtherObj,  float fRotateSpeed);				
	virtual BOOL    ObjTerritory(CBaseObj* pOtherObj, float fDist);			//範囲内かどうかを調べる	

	virtual void	ObjBasicConstructor(const int nMaxHP, const int nAtc, VECTOR3 vMin, VECTOR3 vMax);
	virtual void	ObjReflection();
	virtual void	ObjAppearanceDirection(DWORD dPosStatus, MATRIX4X4 *m_mWorld);
	virtual void	ObjBasicDelete();
	virtual void	ObjRoundTrip(VECTOR3 vMin, VECTOR3 vMax);
	virtual void	ObjNavOccurrence(VECTOR3 vMin, VECTOR3 vMax);


	// 更新処理
	virtual	void    Update() { ; }

	// 目的地（vTargetX,Z）への移動処理
	// (なお、回転スピードの省略値は3.0fとする)
	virtual	BOOL    TargetMove(VECTOR3 vTarget, float fSpeedIn, float fRotSpeed = 3.0f);

	// オブジェクト同士が重ならないようにするメンバ関数
	virtual	CBaseObj*	SetKeepOffset(CBaseProc* pProj);
	// オブジェクトのmWorldと引数位置との距離を求める
	virtual	float   GetDistance(VECTOR3 vPos);  
	// ステータスをリセットする
	virtual	void    ResetStatus();     

	virtual void	HitStatus(CBaseObj* pOtherObj, VECTOR3 vHit, VECTOR3 vNrm);
	virtual void	RotRig(float* fRotUp);

	// アクセス関数
	BOOL	GetActive() { return m_bActive; }
	void	SetActive(BOOL bActive) { m_bActive = bActive; }
	DWORD	GetObjID() { return m_dwObjID; }		// オブジェクトＩＤ
	void	SetObjID(DWORD dwObjID) { m_dwObjID = dwObjID; }		// オブジェクトＩＤ
	DWORD	GetObjNo() { return m_dwObjNo; }		// オブジェクトＮＯ
	void	SetObjNo(DWORD dwObjNo) { m_dwObjNo = dwObjNo; }		// オブジェクトＮＯ
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
	// コンストラクタ（基本オブジェクトの初期化）
	CBaseObj(CGameMain* pGMain);
	// デストラクタ
	virtual		~CBaseObj();
};

// --------------------------------------------------------------------------------------------------
// 基本プロシージャクラス
//
//   ＊　プロシージャとは、「複数の処理を一つにまとめたもの」という意味
//       複数のオブジェクトや下位プロシージャをコントロールするクラスのこと
//
// --------------------------------------------------------------------------------------------------
class  CBaseProc
{
protected:
	CGameMain*		m_pGMain;				// ゲームメインクラス

	// 
	// 下位のプロシージャポインタ配列は、プロシージャを階層構造にして管理するときに使用する
	// オブジェクトポインタ配列は、プロシージャの中にオブジェクトを配置して管理するときに使用する
	// 一般的には、どちらか片方のみを使用すること
	// 
	std::vector<CBaseProc*>  m_pProcArray;  // 下位のプロシージャポインタ配列
	std::vector<CBaseObj*>   m_pObjArray;	// オブジェクトポインタ配列

	DWORD			m_dwProcID;				// プロシージャＩＤ
	int				m_nMaxNum;				// 最大発生数
	int				m_nNum;					// 発生数
	int				m_nMaxwaitTime;			// 最大待ち時間
	int				m_nWaitTime;			// 現在の待ち時間
	int				m_nWaitTimeSec;			// 現在の待ち時間

	DWORD			m_dwKinds;			//種類
	DWORD			m_dwBreakNum;		//破壊数

public:
	// 全体更新処理（全てのプロシージャやオブジェクトを読み下して更新処理をする）
	virtual void	UpdateAll() final;
	virtual void	UpdateAllMulti(DWORD m_dwPlayerNo) final;

	// 更新処理（UpdateAll()の中で起動。プロシージャの更新処理）
	virtual void    Update() { ; }
	virtual void    UpdateMulti(DWORD m_dwPlayerNo) { ; }

	// あたり判定（全てのプロシージャやオブジェクトを読み下して処理をする）
	virtual BOOL    Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld) final;
	virtual BOOL    Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack) final;

	virtual BOOL    HitcheckOtherLay(CBaseObj* pOtherObj) final;

	virtual BOOL    ObjGravity(CBaseObj* pOtherObj, float fDist,float fRotateSpeed);	
	virtual BOOL    ObjTarget(CBaseObj* pOtherObj,float fRotateSpeed,DWORD RunNum);		

	virtual BOOL    Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack,DWORD NotID) final;		
	virtual BOOL    ObjTerritory(CBaseObj* pOtherObj, float fDist);		//範囲内かどうかを調べる	

	virtual BOOL    HitcheckMulti(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld, DWORD dwPlayerNo) final;	
	virtual BOOL    HitcheckMulti(CBaseObj* pOtherObj, CBBox* pBBoxAtack, DWORD dwPlayerNo) final;

	virtual BOOL    HitcheckMultiOtherLay(CBaseObj* pOtherObj, DWORD dwPlayerNo) final;		

	virtual BOOL    ObjGravityMulti(CBaseObj* pOtherObj, float fDist, float fRotateSpeed, DWORD dwPlayerNo);
	virtual BOOL    ObjTargetMulti(CBaseObj* pOtherObj, float fRotateSpeed, DWORD RunNum, DWORD dwPlayerNo);

	virtual BOOL    HitcheckMulti(CBaseObj* pOtherObj, CBBox* pBBoxAtack, DWORD NotID, DWORD dwPlayerNo) final;	
	virtual BOOL    ObjTerritoryMulti(CBaseObj* pOtherObj, float fDist, DWORD dwPlayerNo);		//範囲内かどうかを調べる	

	//	プロシージャとオブジェクトを探索し全てのオブジェクトをノンアクティブにする
	virtual void	SetNonActive();

	//	発生数の設定
	virtual void	SetMaxNum() { m_nNum = m_nMaxNum; }
	//	ウェイトタイムの設定
	virtual void	SetMaxWaitTime() { m_nWaitTime = m_nMaxwaitTime; }
	virtual void	SetWaitTime(int	n) { m_nWaitTime = n; }	
	virtual void	SetMaxWaitTimeSec() { m_nWaitTimeSec = m_nMaxwaitTime; }
	virtual void	SetWaitTimeSec(int	n) { m_nWaitTimeSec = n; }

	virtual MATRIX4X4	ObjReflectionStart(CBaseObj* mMyObj, CBaseObj* mHitObj);


	DWORD	GetWaitTime() { return m_nWaitTime; }
	DWORD	GetWaitTimeSec () { return m_nWaitTimeSec; }
	DWORD	GetKinds() { return m_dwKinds; }

	// アクセス関数
	std::vector<CBaseProc*> GetProcArrayPtr() { return m_pProcArray; } // 下位のプロシージャポインタ配列のアドレスを返す
	std::vector<CBaseObj*>  GetObjArrayPtr() { return m_pObjArray; }  // オブジェクトポインタ配列のアドレスを返す
	int  GetNum() { return m_nNum; }
	void AddNum(int n) { m_nNum += n; }

	DWORD GetBreakNum() { return m_dwBreakNum; }
	void AddBreakNum(DWORD n) { m_dwBreakNum += n; }

	DWORD GetProcID() { return m_dwProcID; }

	// コンストラクタ（基本プロシージャの初期化）
	CBaseProc(CGameMain* pGMain)
	{
		m_pGMain = pGMain;   // ゲームメインクラス
		m_dwProcID = 0;         // プロシージャＩＤ
		m_nMaxwaitTime = 0;		// 最大待ち時間
		m_nWaitTime = 0;		// 現在の待ち時間
		m_dwBreakNum = 0;
	}
	// デストラクタ（プロシージャとオブジェクトの解放）
	virtual		~CBaseProc();
};


