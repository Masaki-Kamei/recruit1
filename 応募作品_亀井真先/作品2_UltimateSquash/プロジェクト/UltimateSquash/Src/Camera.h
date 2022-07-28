//=============================================================================
//
//		カメラ制御
//
//		(視点変更処理・障害物回避処理が入っている)
//
//																Camera.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include"Playchar.h"

#define	CAMERA_STATUS			m_pGMain->m_pPcProc->GetPcObjPtr(),&m_pGMain->m_vEyePt,&m_pGMain->m_vLookatPt,&m_pGMain->m_mView
#define	CAMERASECOND_STATUS		m_pGMain->m_pPcProc->GetPcSecObjPtr(),&m_pGMain->m_vEyePtSecond,&m_pGMain->m_vLookatPtSecond,&m_pGMain->m_mViewSecond

//======================================================================
// カメラ　オブジェクトクラス
//======================================================================
class CCameraObj : public CBaseObj
{
protected:
	int     m_nCtrl;                       // カメラ制御
	MATRIX4X4 m_mBaseWorld;                // 注視点・視点の基点となる基点ワールドマトリックス
	VECTOR3 m_vLocalLookat;                // ローカル注視点ベクトル
	VECTOR3 m_vLocalEye;                   // ローカル視点ベクトル
	VECTOR3 m_vLocalEyeRotDist;            // ローカル視点ベクトルを生成するための角度と変位(TPSのみ)
	VECTOR3 m_vBaseLocalLookatTPS;         // ローカル注視点ベクトル初期値 TPS
	VECTOR3 m_vBaseLocalEyeRotDistTPS;     // ローカル視点ベクトル初期値(角度と変位) TPS
	VECTOR3 m_vBaseLocalLookatFPS;         // ローカル注視点ベクトル初期値 FPS
	VECTOR3 m_vBaseLocalEyeFPS;            // ローカル視点ベクトル初期値 FPS
	CPcObj*	pPcObj;

	VECTOR3*		pvEyePt;		//カメラ（視点）位置
	VECTOR3*        pvLookatPt;		//注視位置
	MATRIX4X4*      pmView;

public:
	virtual void Update() override;
	virtual void EvasiveObstacle();
	virtual void SetLocalEyeTPS(float fRotY, float fRotX, float fDist);
	virtual void SetCamBase();
	virtual int  GetCtrl() { return m_nCtrl; }
	void CameraSetStatus(CPcObj* pPcObjSet,VECTOR3* pvEyePtSet, VECTOR3* pvLookatPtSet, MATRIX4X4* pmViewSet);

	CCameraObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CCameraObj();
};


//======================================================================
// カメラ　プロシージャクラス
//======================================================================
class CCameraProc : public CBaseProc
{
protected:
	;

public:
	CCameraObj*	 GetCameraObjPtr() { return (CCameraObj*)GetObjArrayPtr()[0]; }
	CCameraObj*	 GetCameraSecondObjPtr() { return (CCameraObj*)GetObjArrayPtr()[1]; }

	CCameraProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CCameraProc() { ; }
};


