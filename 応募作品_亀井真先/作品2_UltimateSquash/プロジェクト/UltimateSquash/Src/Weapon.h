//=============================================================================
//		スキル　　　ヘッダファイル								Weapon.h
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

//スキルのID
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

//スキルクールタイム
#define  WEAPON_DIV_WAITTIME			10
#define	WEAPON_BIGBALL_WAITTIME			 5
#define	 WEAPON_PENETBALL_WAITTIME		 3
#define	WEAPON_ROLLBALL_WAITTIME		10
#define	WEAPON_SKILLPCBOOL_WAITTIME		10
#define	WEAPON_SKILLBOUNCE_WAITTIME		 3
#define	WEAPON_SKILLSPEEDUP_WAITTIME	3

//スキル時間
#define	WEAPON_SKILLPCBOOL_TIME		10
#define	WEAPON_SKILLSPEEDUP_TIME	2

struct TargetStatas
{
	int Id;

};

// --------------------------------------------------------------------
//スキル　剣　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponSwordProc;
class CWeaponSwordObj : public CBaseObj
{
protected:
	DWORD           m_dwOwner;
	int				m_nWeapoWaitTime[100];
	int				m_nWeapoMaxWaitTime[100];
	int				nCount[100];				//60フレームで一秒数えるための変数
	int				nWaitCount[100];

	CBBox*			m_pBBoxSub;			// バウンディングボックスクラス
	DWORD			dwUseNumWeapon;		//スキルを使用した回数		

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

	CWeaponSwordObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponSwordObj();
};
// --------------------------------------------------------------------
// スキル　剣　プロシージャクラス
// --------------------------------------------------------------------
class CWeaponSwordProc : public CBaseProc
{
public:

	BOOL Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner);	// 剣の発射
	BOOL Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner, DWORD dwPlayerNo);

	CWeaponSwordObj*	GetWeaponSwordObjPtr() { return(CWeaponSwordObj*)GetObjArrayPtr()[0]; }
	CWeaponSwordObj*	GetWeaponSwordSecObjPtr() { return(CWeaponSwordObj*)GetObjArrayPtr()[1]; }

	CWeaponSwordProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponSwordProc() { ; }

};

// --------------------------------------------------------------------
//スキル　ボール　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
	DWORD                    m_dwOwner;

	float				m_fLocalRotY;		// ローカル軸(Y軸)   


	ChkFace* p;

	float				m_fJumpSpeed;		// ジャンプ速度       
	VECTOR4				m_vDiffuse;

public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner) override;
	void Update() override;

	void UpdateDamage();

	void Render();

	MATRIX4X4  GetLocalMatrix();			// ローカル軸マトリックスを得る


	// アクセス関数
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponBallObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponBallObj();
};
// --------------------------------------------------------------------
//スキル　ボールプロシージャクラス
// --------------------------------------------------------------------
class CWeaponBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
public:
	BOOL Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner);  //スキル　ボールの発射

	CWeaponBallProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponBallProc();

	CWeaponBallObj*	GetWeaponBallObjPtr() { return(CWeaponBallObj*)GetObjArrayPtr()[0]; }

};

// --------------------------------------------------------------------
//スキル　手に持つアイテム　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponHoldObj : public CBaseObj
{
protected:
	int                      m_nKindNo;			// 手に持つアイテムの種類(1:剣　2:銃)
	CFbxMesh*                m_pMesh;			// Fbxメッシュ(プロシージャではなくオブジェクトにメッシュを持たせる)
	VECTOR3                  m_vOffset;			// 銃口までのオフセット（銃のみ）
public:
	void Init();
	BOOL Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem,DWORD dwPlayerNo);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax);
	CBBox* GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);

	void Update() override;
	void Render();

	int GetKind() { return m_nKindNo; }

	CWeaponHoldObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponHoldObj();
};
// --------------------------------------------------------------------
//スキル　手に持つアイテム　プロシージャクラス
// --------------------------------------------------------------------
class CWeaponHoldProc : public CBaseProc
{
protected:
	;
public:
	BOOL Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, DWORD dwPlayerNo); // スキル　の表示
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax);
	CBBox* GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);
	int GetKind(BASEHOLDITEM HoldItem) { return ((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetKind(); }
	CWeaponHoldProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponHoldProc();

	CWeaponHoldObj*	GetWeaponHoldObjPtr() { return(CWeaponHoldObj*)GetObjArrayPtr()[0]; }

};

// --------------------------------------------------------------------
//スキル　シールド　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponShieldObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
	DWORD                    m_dwOwner;
	float				m_fLocalRotY;		// ローカル軸(Y軸)  
	ChkFace* p;
	float				m_fJumpSpeed;		// ジャンプ速度      

	DWORD		   dTargetNo;			//回るための軸となるオブジェクトの配列のナンバー
	float			fShieldDist;		//軸となるオブジェクトとの距離	


public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner) override;
	BOOL Start(MATRIX4X4 mWorld, DWORD dwOwner, DWORD dwPlayerNo) override;

	void Update() override;

	void UpdateDamage();
	void Render();
	MATRIX4X4  GetLocalMatrix();			// ローカル軸マトリックスを得る


	// アクセス関数
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponShieldObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponShieldObj();
};
// --------------------------------------------------------------------
//スキル　シールドプロシージャクラス
// --------------------------------------------------------------------
class CWeaponShieldProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ

	DWORD		   dTargetNo;		//回るための軸となるオブジェクトの配列のナンバー	
	float			fShieldDist;		//軸となるオブジェクトとの距離	

public:


	BOOL Start(MATRIX4X4 mWorld, DWORD dwOwner);  //スキル　ボールの発射
	BOOL Start(MATRIX4X4 mWorld, DWORD dwOwner,DWORD dwPlayerNo);  //スキル　ボールの発射

	void SetTargetNo(DWORD dNo) { dTargetNo = dNo; }
	DWORD GetTargetNo() { return dTargetNo; }
	void SetShieldDist(float dNum) { fShieldDist = dNum; }
	float GetShieldDist() { return fShieldDist; }
	CWeaponShieldProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponShieldProc();

	CWeaponShieldObj*	GetWeaponBallObjPtr() { return(CWeaponShieldObj*)GetObjArrayPtr()[0]; }

};


// --------------------------------------------------------------------
//スキル　分裂ボール　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponDivBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
	DWORD                    m_dwOwner;

	float				m_fLocalRotY;		// ローカル軸(Y軸)  
	float				m_fDivTime;
	DWORD               Direction;

	ChkFace* p;

	float				m_fJumpSpeed;		// ジャンプ速度       
	BOOL				m_bFront;
	DWORD					RanNum;			//IDを保存する用	

	CBaseProc*			TargetProc;			//ターゲットしているプロック	
	float					fActivTime;

	std::vector<TargetStatas>		TargetProcArr;
	std::vector<TargetStatas>		TargetObjArr;

public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner, DWORD dwNo, DWORD  dwNum);
	void Update() override;

	void UpdateDamage();

	void Render();

	MATRIX4X4  GetLocalMatrix();			// ローカル軸マトリックスを得る


	// アクセス関数
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }


	BOOL LookTarget(CBaseProc* pOtherProc,DWORD dwPlayerNo);		//	ターゲットを見つける処理		


	CWeaponDivBallObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponDivBallObj();
};
// --------------------------------------------------------------------
//スキル　分裂ボールプロシージャクラス
// --------------------------------------------------------------------
class CWeaponDivBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
public:
	BOOL Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner);  //スキル　ボールの発射
	BOOL Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner,DWORD dwPlayerNo);  //スキル　ボールの発射

	CWeaponDivBallProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponDivBallProc();

	CWeaponDivBallObj*	GetWeaponBallDivObjPtr() { return(CWeaponDivBallObj*)GetObjArrayPtr()[0]; }


};

// --------------------------------------------------------------------
//スキル　ビッグボール　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponBigBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
	DWORD                    m_dwOwner;

	float				m_fLocalRotY;		// ローカル軸(Y軸)   


	ChkFace* p;

	float				m_fJumpSpeed;		// ジャンプ速度       
	VECTOR4				m_vDiffuse;
	DWORD				m_dDamageCount;
public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner) override;
	void Update() override;

	void UpdateDamage();

	void Render();

	MATRIX4X4  GetLocalMatrix();			// ローカル軸マトリックスを得る


	// アクセス関数
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponBigBallObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponBigBallObj();
};
// --------------------------------------------------------------------
//スキル　ビッグボールプロシージャクラス
// --------------------------------------------------------------------
class CWeaponBigBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
public:
	BOOL Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner);  //スキル　ボールの発射
	BOOL Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner,DWORD dwPlayerNo);  //スキル　ボールの発射

	CWeaponBigBallProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponBigBallProc();


};

// --------------------------------------------------------------------
//スキル　貫通ボール　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponPenetBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
	DWORD                    m_dwOwner;

	float				m_fLocalRotY;		// ローカル軸(Y軸)   


	ChkFace* p;

	float				m_fJumpSpeed;		// ジャンプ速度      
	VECTOR4				m_vDiffuse;	

public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner) override;
	void Update() override;

	void UpdateDamage();

	void Render();

	MATRIX4X4  GetLocalMatrix();			// ローカル軸マトリックスを得る


	// アクセス関数
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponPenetBallObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponPenetBallObj();
};
// --------------------------------------------------------------------
//スキル　貫通ボールプロシージャクラス
// --------------------------------------------------------------------
class CWeaponPenetBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
public:
	BOOL Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner);  //スキル　ボールの発射
	BOOL Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner, DWORD dwPlayerNo);  //スキル　ボールの発射

	CWeaponPenetBallProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponPenetBallProc();


};


// --------------------------------------------------------------------
//スキル　回転ボール　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponRollBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
	DWORD                    m_dwOwner;

	float				m_fLocalRotY;		// ローカル軸(Y軸) 


	ChkFace* p;

	float				m_fJumpSpeed;		// ジャンプ速度     
	VECTOR4				m_vDiffuse;	

public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner) override;
	void Update() override;

	void UpdateDamage();

	void Render();

	MATRIX4X4  GetLocalMatrix();			// ローカル軸マトリックスを得る


	// アクセス関数
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponRollBallObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponRollBallObj();
};
// --------------------------------------------------------------------
//スキル　回転ボールプロシージャクラス
// --------------------------------------------------------------------
class CWeaponRollBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
public:
	BOOL Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner);  //スキル　ボールの発射
	BOOL Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner, DWORD dwPlayerNo);  //スキル　ボールの発射

	CWeaponRollBallProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponRollBallProc();


};

// --------------------------------------------------------------------
//スキル　壁　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponWallProc;
class CWeaponWallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
	DWORD                    m_dwOwner;
	float				m_fLocalRotY;		// ローカル軸(Y軸)   
	ChkFace* p;
	float				m_fJumpSpeed;		// ジャンプ速度    

	DWORD		   dTargetNo;			//回るための軸となるオブジェクトの配列のナンバー
	float			fWallDist;		//軸となるオブジェクトとの距離	
	
	CCollision*				m_pColMesh;			// 移動コリジョンメッシュへのポインタ
	MATRIX4X4				mColWorld;
	DWORD					dUseNo;		//使用しているオブジェクトのナンバー	
	DWORD					dDamageNum;
	BOOL					bInvTrigger;	//無敵かどうか
	VECTOR4					vDiffuse;
	BOOL					bDamageTrigger;
	BOOL					bStartTrigget;
public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner, DWORD dNo) override;
	void Update() override;
	void UpdateDamage();
	void Render();
	MATRIX4X4  GetLocalMatrix();			// ローカル軸マトリックスを得る


	// アクセス関数
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	void SetColMesh(CCollision* pColMesh) { m_pColMesh = pColMesh; }
	CCollision*	GetColMesh() { return m_pColMesh; }
	void SetColMesh(CWeaponWallProc* pProc);

	BOOL	 isBBoxMoveGravity(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld,VECTOR3 vHit, VECTOR3 vNrm,float fRadius);
	void	 StartLE();
	void	 InvincibleTime();
	void	 ObjDisappear();

	CWeaponWallObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponWallObj();
};
// --------------------------------------------------------------------
//スキル　壁プロシージャクラス
// --------------------------------------------------------------------
class CWeaponWallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ

	DWORD		   dTargetNo;		//回るための軸となるオブジェクトの配列のナンバー	
	float			fWallDist;		//軸となるオブジェクトとの距離	
	CCollision*				m_pColMesh;			// 移動コリジョンメッシュへのポインタ

public:
	BOOL Start(MATRIX4X4 mWorld, DWORD dwOwner, DWORD dNo);  //スキル　ボールの発射
	BOOL Start(MATRIX4X4 mWorld, DWORD dwOwner, DWORD dNo, DWORD dwPlayerNo);
	void SetTargetNo(DWORD dNo) { dTargetNo = dNo; }
	DWORD GetTargetNo() { return dTargetNo; }
	void SetWallDist(float dNum) { fWallDist = dNum; }
	float GetWallDist() { return fWallDist; }
	CWeaponWallProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponWallProc();

	CWeaponWallObj*	GetWeaponBallObjPtr() { return(CWeaponWallObj*)GetObjArrayPtr()[0]; }

	int  isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld,DWORD dwPlayerNo);

	BOOL	 isBBoxMoveGravity(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld, float fRadius );
	CCollision*	GetColMesh() { return m_pColMesh; }

};

// --------------------------------------------------------------------
//スキル　曲がるボール　オブジェクトクラス
// --------------------------------------------------------------------
class CWeaponBendBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ
	DWORD                    m_dwOwner;
	float				m_fLocalRotY;		// ローカル軸(Y軸) 
	ChkFace* p;
	float				m_fJumpSpeed;		// ジャンプ速度     

	DWORD		   dTargetNo;			//回るための軸となるオブジェクトの配列のナンバー
	float			fBendBallDist;		//軸となるオブジェクトとの距離	

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
	MATRIX4X4  GetLocalMatrix();			// ローカル軸マトリックスを得る

	void BallDirectionStart(DWORD dwTurnPos);
	void ObjBend();
	void DamageRearHitcheck();


	// アクセス関数
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponBendBallObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponBendBallObj();
};
// --------------------------------------------------------------------
//スキル　曲がるボールプロシージャクラス
// --------------------------------------------------------------------
class CWeaponBendBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbxスタティックメッシュ

	DWORD		   dTargetNo;		//回るための軸となるオブジェクトの配列のナンバー	
	float			fBendBallDist;		//軸となるオブジェクトとの距離	

public:
	BOOL Start(MATRIX4X4 mWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner);  //スキル　ボールの発射
	BOOL Start(MATRIX4X4 mWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner, DWORD dwPlayerNo);  //スキル　ボールの発射


	void SetTargetNo(DWORD dNo) { dTargetNo = dNo; }
	DWORD GetTargetNo() { return dTargetNo; }
	void SetBendBallDist(float dNum) { fBendBallDist = dNum; }
	float GetBendBallDist() { return fBendBallDist; }
	CWeaponBendBallProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponBendBallProc();

	CWeaponBendBallObj*	GetWeaponBallObjPtr() { return(CWeaponBendBallObj*)GetObjArrayPtr()[0]; }

};



// ======================================================================
// スキル全体のメインプロシージャクラス
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
	CWeaponProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CWeaponProc() { ; }
};


