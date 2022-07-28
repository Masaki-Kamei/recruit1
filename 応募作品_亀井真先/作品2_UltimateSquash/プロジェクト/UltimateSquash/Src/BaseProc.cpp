//=============================================================================
//
//		基本プロシージャ・基本オブジェクトクラス処理
//																BaseProc.cpp
//=============================================================================
#include  "BaseProc.h"

//------------------------------------------------------------------------
//
//	基本プロシージャクラスのデストラクタ	
//  （全てのプロシージャやオブジェクトを読み下して削除する）
//
//  引数　なし
//
//------------------------------------------------------------------------
CBaseProc::~CBaseProc()
{
	// プロシージャポインタ配列の削除
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		SAFE_DELETE(m_pProcArray[i]);
	}
	// オブジェクトポインタ配列の削除
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		SAFE_DELETE(m_pObjArray[i]);
	}
}
//------------------------------------------------------------------------
//
//	基本プロシージャクラスの全体更新処理	
//  （全てのプロシージャやオブジェクトを読み下して更新処理をする）
//
//  引数　なし
//
//------------------------------------------------------------------------
void CBaseProc::UpdateAll()
{

	Update();                              // プロシージャの更新処理
	if (m_nWaitTime > 0) m_nWaitTime--;    // ウェイトタイマーのカウントダウン

	// オブジェクトポインタ配列の更新
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if(m_pObjArray[i]->GetPlayerNo()!=SECONDPLAYER)m_pObjArray[i]->Update();          // オブジェクトの更新処理
	}

	// 下位のプロシージャポインタ配列の更新
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->UpdateAll();      // 下位のプロシージャの全体更新処理（再帰処理）
	}

}

//------------------------------------------------------------------------
//	基本プロシージャクラスの全体更新処理	
//  （全てのプロシージャやオブジェクトを読み下して更新処理をする）
//
//  DWORD	m_dwPlayerNo		プレイヤー番号
//
//------------------------------------------------------------------------
void CBaseProc::UpdateAllMulti(DWORD m_dwPlayerNo)
{

	UpdateMulti(m_dwPlayerNo);                              // プロシージャの更新処理

	// オブジェクトポインタ配列の更新
	if (m_dwPlayerNo == FIRSTPLAYER) {	//１プレイヤーのオブジェクト更新処理
		if (m_nWaitTime > 0) m_nWaitTime--;    // ウェイトタイマーのカウントダウン
		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (m_pObjArray[i]->GetPlayerNo() == m_dwPlayerNo)m_pObjArray[i]->Update();          // オブジェクトの更新処理
		}
	}
	else if (m_dwPlayerNo == SECONDPLAYER) {	//２プレイヤーのオブジェクト更新処理
		if (m_nWaitTimeSec > 0) m_nWaitTimeSec--;    // ウェイトタイマーのカウントダウン
		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (m_pObjArray[i]->GetPlayerNo() == m_dwPlayerNo)m_pObjArray[i]->Update();          // オブジェクトの更新処理

		}

	}
	// 下位のプロシージャポインタ配列の更新
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->UpdateAllMulti(m_dwPlayerNo);      // 下位のプロシージャの全体更新処理（再帰処理）
	}

}


//-----------------------------------------------------------------------------
// 基本プロシージャクラスのあたり判定(移動直線)
//
// ・全ての相手プロシージャと相手オブジェクトを読み下し
// ・自オブジェクトのバウンディングボックスと相手の移動直線とのあたり判定処理をする
//
//   CBaseObj* pOtherObj    相手のオブジェクト
//   VECTOR3 vNow       相手の現在位置
//   VECTOR3 vOld       相手の一つ前の位置
//
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と自分のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   相手と自分オブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld)
{
	BOOL  bRet = FALSE;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj, vNow, vOld);  // 相手オブジェクトとのあたり判定
		if (bRet) return bRet;
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->Hitcheck(pOtherObj, vNow, vOld);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
// 基本プロシージャクラスのあたり判定（バウンディングボックス）
//
// ・全ての相手プロシージャと相手オブジェクトを読み下し
// ・自オブジェクトのバウンディングボックスと相手の攻撃バウンディングボックスとのあたり判定
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//   CBBox*    pAttackBBox    対象となるバウンディングボックス
//
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と自分のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   相手と自分のオブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack)
{
	BOOL  bRet = FALSE;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // 相手オブジェクトとのあたり判定
		if (bRet) return bRet;
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}
//-----------------------------------------------------------------------------
// 基本プロシージャクラスのあたり判定（自分の移動直線）
//
// ・全ての相手プロシージャと相手オブジェクトを読み下し
// ・自オブジェクトの移動直線と相手のバウンディングボックスとのあたり判定
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と自分のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   相手と自分のオブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::HitcheckOtherLay(CBaseObj* pOtherObj)
{
	BOOL  bRet = FALSE;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
			bRet = m_pObjArray[i]->HitcheckOtherLay(pOtherObj);  // 相手オブジェクトとのあたり判定
			if (bRet) return bRet;
		
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->HitcheckOtherLay(pOtherObj);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
//基本プロシージャクラスの引き寄せ
//
// ・全ての相手プロシージャと相手オブジェクトを読み下す
// 
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//	 float	　　fDist		  相手との判定距離
//	 float		fRotateSpeed　方向転換のスピード
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：判定距離に入っていない
//
//   判定結果　　
//           判定距離以内　　　　相手オブジェクトが自オブジェクトに向きを変える
//           判定距離以外　　　　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::ObjGravity(CBaseObj* pOtherObj, float fDist, float fRotateSpeed)
{
	BOOL  bRet = FALSE;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
		if(m_pObjArray[i]->GetActive()==TRUE)
			bRet = m_pObjArray[i]->ObjGravity(pOtherObj, fDist, fRotateSpeed);  // 相手オブジェクトとのあたり判定
			if (bRet) return bRet;
		
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->ObjGravity(pOtherObj, fDist, fRotateSpeed);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}


//-----------------------------------------------------------------------------
//基本プロシージャクラスの方向を徐々に向く
//
// ・全ての相手プロシージャと相手オブジェクトを読み下す
// 
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//	 float		fRotateSpeed　方向転換のスピード
//	 DWORD		RanNum		　対象オブジェクトのID
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：判定距離に入っていない
//
//   判定結果　　
//           判定距離以内　　　　相手オブジェクトが自オブジェクトに向きを変える
//           判定距離以外　　　　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::ObjTarget(CBaseObj* pOtherObj, float fRotateSpeed,DWORD RanNum)
{
	BOOL  bRet = FALSE;
	DWORD j=RanNum;

	bRet = m_pObjArray[j]->ObjTarget(pOtherObj, fRotateSpeed);  // 相手オブジェクトとのあたり判定

	if (bRet) return bRet;
	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->ObjTarget(pOtherObj,  fRotateSpeed,RanNum);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
// 基本プロシージャクラスのあたり判定（バウンディングボックス）
//
//指定したIDを除外できる
//
// ・全ての相手プロシージャと相手オブジェクトを読み下し
// ・自オブジェクトのバウンディングボックスと相手の攻撃バウンディングボックスとのあたり判定
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//   CBBox*    pAttackBBox    対象となるバウンディングボックス
//	DWORD	  NotID			除外するID
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と自分のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   相手と自分のオブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack,DWORD NotID)
{
	BOOL  bRet = FALSE;
	if (m_dwProcID != NotID) {
		// 全ての相手とのあたり判定
		for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
		{
			bRet = m_pObjArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // 相手オブジェクトとのあたり判定
			if (bRet) return bRet;
		}
	}
		for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
		{
			bRet = m_pProcArray[i]->Hitcheck(pOtherObj, pBBoxAtack,NotID);  // 相手プロシージャとのあたり判定
			if (bRet) return bRet;
		}
	
	return bRet;
}

//-----------------------------------------------------------------------------
//基本プロシージャクラスの範囲チェック
//
// ・全ての相手プロシージャと相手オブジェクトを読み下す
// 
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//	 float	　　fDist		  相手との判定距離
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：判定距離に入っていない
//
//   判定結果　　
//           判定距離以内　　　　相手オブジェクトが自オブジェクトに向きを変える
//           判定距離以外　　　　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::ObjTerritory(CBaseObj* pOtherObj, float fDist)
{
	BOOL  bRet = FALSE;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
		if (m_pObjArray[i]->GetbShaftObjTrigger() != TRUE) {
			bRet = m_pObjArray[i]->ObjTerritory(pOtherObj, fDist);  // 相手オブジェクトとのあたり判定
			if (bRet) return bRet;
		}
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->ObjTerritory(pOtherObj, fDist);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------		
// 基本プロシージャクラスのあたり判定(移動直線)
//
// ・全ての相手プロシージャと相手オブジェクトを読み下し
// ・自オブジェクトのバウンディングボックスと相手の移動直線とのあたり判定処理をする
//
//   CBaseObj* pOtherObj    相手のオブジェクト
//   VECTOR3 vNow       相手の現在位置
//   VECTOR3 vOld       相手の一つ前の位置
//	 DWORD	m_dwPlayerNo		プレイヤー番号

//
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と自分のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   相手と自分オブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::HitcheckMulti(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
		if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {	//同じプレイヤーナンバーのオブジェクト同士のみ処理
			bRet = m_pObjArray[i]->Hitcheck(pOtherObj, vNow, vOld);  // 相手オブジェクトとのあたり判定
			if (bRet) return bRet;
		}
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->HitcheckMulti(pOtherObj, vNow, vOld, dwPlayerNo);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
// 基本プロシージャクラスのあたり判定（バウンディングボックス）
//
// ・全ての相手プロシージャと相手オブジェクトを読み下し
// ・自オブジェクトのバウンディングボックスと相手の攻撃バウンディングボックスとのあたり判定
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//   CBBox*    pAttackBBox    対象となるバウンディングボックス
//   DWORD	m_dwPlayerNo		プレイヤー番号
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と自分のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   相手と自分のオブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::HitcheckMulti(CBaseObj* pOtherObj, CBBox* pBBoxAtack, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
		if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {	//同じプレイヤーナンバーのオブジェクト同士のみ処理
			bRet = m_pObjArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // 相手オブジェクトとのあたり判定
			if (bRet) return bRet;
		}
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->HitcheckMulti(pOtherObj, pBBoxAtack, dwPlayerNo);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}
//-----------------------------------------------------------------------------
// 基本プロシージャクラスのあたり判定（自分の移動直線）
//
// ・全ての相手プロシージャと相手オブジェクトを読み下し
// ・自オブジェクトの移動直線と相手のバウンディングボックスとのあたり判定
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//   DWORD	m_dwPlayerNo		プレイヤー番号
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と自分のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   相手と自分のオブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::HitcheckMultiOtherLay(CBaseObj* pOtherObj, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
		if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {	//同じプレイヤーナンバーのオブジェクト同士のみ処理
			bRet = m_pObjArray[i]->HitcheckOtherLay(pOtherObj);  // 相手オブジェクトとのあたり判定
			if (bRet) return bRet;
		}

	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->HitcheckMultiOtherLay(pOtherObj, dwPlayerNo);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
//基本プロシージャクラスの引き寄せ
//
// ・全ての相手プロシージャと相手オブジェクトを読み下す
// 
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//	 float	　　fDist		  相手との判定距離
//	 float		fRotateSpeed　方向転換のスピード
//   DWORD	m_dwPlayerNo		プレイヤー番号

//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：判定距離に入っていない
//
//   判定結果　　
//           判定距離以内　　　　相手オブジェクトが自オブジェクトに向きを変える
//           判定距離以外　　　　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::ObjGravityMulti(CBaseObj* pOtherObj, float fDist, float fRotateSpeed, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
		if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {	//同じプレイヤーナンバーのオブジェクト同士のみ処理
			if (m_pObjArray[i]->GetActive() == TRUE)
				bRet = m_pObjArray[i]->ObjGravity(pOtherObj, fDist, fRotateSpeed);  // 相手オブジェクトとのあたり判定
			if (bRet) return bRet;
		}

	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->ObjGravityMulti(pOtherObj, fDist, fRotateSpeed, dwPlayerNo);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}


//-----------------------------------------------------------------------------
//基本プロシージャクラスの方向を徐々に向く
//
// ・全ての相手プロシージャと相手オブジェクトを読み下す
// 
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//	 float		fRotateSpeed　方向転換のスピード
//	 DWORD		RanNum		　対象オブジェクトのID
//   DWORD	m_dwPlayerNo		プレイヤー番号
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：判定距離に入っていない
//
//   判定結果　　
//           判定距離以内　　　　相手オブジェクトが自オブジェクトに向きを変える
//           判定距離以外　　　　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::ObjTargetMulti(CBaseObj* pOtherObj, float fRotateSpeed, DWORD RanNum, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;
	DWORD j = RanNum;

	if (m_pObjArray[j]->GetPlayerNo() == dwPlayerNo) {	//同じプレイヤーナンバーのオブジェクト同士のみ処理
		bRet = m_pObjArray[j]->ObjTarget(pOtherObj, fRotateSpeed);  // 相手オブジェクトとのあたり判定
	}
	if (bRet) return bRet;
	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->ObjTargetMulti(pOtherObj, fRotateSpeed, RanNum, dwPlayerNo);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
// 基本プロシージャクラスのあたり判定（バウンディングボックス）
//
//指定したIDを除外できる
//
// ・全ての相手プロシージャと相手オブジェクトを読み下し
// ・自オブジェクトのバウンディングボックスと相手の攻撃バウンディングボックスとのあたり判定
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//   CBBox*    pAttackBBox    対象となるバウンディングボックス
//	 DWORD	  NotID			除外するID
//   DWORD	m_dwPlayerNo		プレイヤー番号
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と自分のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   相手と自分のオブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::HitcheckMulti(CBaseObj* pOtherObj, CBBox* pBBoxAtack, DWORD NotID, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;
	if (m_dwProcID != NotID) {
		// 全ての相手とのあたり判定
		for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
		{
			if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {	//同じプレイヤーナンバーのオブジェクト同士のみ処理
				bRet = m_pObjArray[i]->Hitcheck(pOtherObj, pBBoxAtack);  // 相手オブジェクトとのあたり判定
				if (bRet) return bRet;
			}
		}
	}
	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->HitcheckMulti(pOtherObj, pBBoxAtack, NotID, dwPlayerNo);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}

//-----------------------------------------------------------------------------
//基本プロシージャクラスの範囲チェック
//
// ・全ての相手プロシージャと相手オブジェクトを読み下す
// 
//
//   CBaseObj* pOtherObj      相手のオブジェクト
//	 float	　　fDist		  相手との判定距離
//   DWORD	m_dwPlayerNo		プレイヤー番号
//
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：判定距離に入っていない
//
//   判定結果　　
//           判定距離以内　　　　相手オブジェクトが自オブジェクトに向きを変える
//           判定距離以外　　　　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::ObjTerritoryMulti(CBaseObj* pOtherObj, float fDist, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;

	// 全ての相手とのあたり判定
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{
		if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {	//同じプレイヤーナンバーのオブジェクト同士のみ処理
			if (m_pObjArray[i]->GetbShaftObjTrigger() != TRUE) {
				bRet = m_pObjArray[i]->ObjTerritory(pOtherObj, fDist);  // 相手オブジェクトとのあたり判定
				if (bRet) return bRet;
			}
		}
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // 下位の相手プロシージャ
	{
		bRet = m_pProcArray[i]->ObjTerritoryMulti(pOtherObj, fDist, dwPlayerNo);  // 相手プロシージャとのあたり判定
		if (bRet) return bRet;
	}

	return bRet;
}


//============================================================================
//   
//	プロシージャとオブジェクトを探索し全てのオブジェクトをノンアクティブにする
//   
//	引数　	なし
//
//	戻り値  なし
//============================================================================
void  CBaseProc::SetNonActive()
{

	// 敵のオブジェクトポインタ配列の探索
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive(FALSE);   // アクティブフラグをFALSEに
		m_pObjArray[i]->ResetStatus();      // 各種ステータスをリセット
	}

	// 下位のプロシージャポインタ配列の探索
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetMaxWaitTime();    // ウェイトタイムをセットする
		m_pProcArray[i]->SetNonActive();      // 下位のプロシージャの処理（再帰処理）
	}

	m_dwBreakNum = 0;		//破壊数初期化

}


//------------------------------------------------------------------------
//
//	基本オブジェクトクラスのコンストラクタ	
//
//  引数　CGameMain* pGMain  // ゲームメインクラス
//
//------------------------------------------------------------------------
CBaseObj::CBaseObj(CGameMain* pGMain)
{
	// 全体のゼロクリヤー
	// 注意点：クラス中にＳＴＬを宣言しているときは使用してはならない
	ZeroMemory(this, sizeof(CBaseObj));

	m_pGMain = pGMain;					// ゲームメインクラス
	ResetStatus();						// 各種ステータスをリセット
	m_mWorld = XMMatrixIdentity();		// ワールドマトリクス
	m_mWorldOld = XMMatrixIdentity();	// ワールドマトリクス（一つ前）

	m_AnimStatus.playAnim = true;		// アニメーションを動作させる
}
//------------------------------------------------------------------------
//
//	基本オブジェクトクラスのデストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CBaseObj::~CBaseObj()
{
	SAFE_DELETE(m_pBBox);
}

//-----------------------------------------------------------------------------
//
// 基本オブジェクトクラスのあたり判定(移動直線)
//
// ・自オブジェクトのバウンディングボックスと相手の移動直線とのあたり判定
//
//   CBaseObj* pOtherObj  相手のオブジェクト
//   VECTOR3 vNow     相手の現在位置
//   VECTOR3 vOld     相手の一つ前の位置
//
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と敵のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   敵オブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と敵のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::Hitcheck(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld)
{
	BOOL bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	// バウンディングボックスと移動直線（Lay）による判定
	if ((m_bActive && m_dwStatus != DAMAGE && m_dwStatus != DEAD && m_dwStatus != FLASH) &&
		m_pBBox->OBBCollisionLay(vNow, vOld, &vHit, &vNrm))
	{
		HitStatus(pOtherObj, vHit, vNrm);
		bRet = TRUE;
	}
	return bRet;
}
//-----------------------------------------------------------------------------
//
// 基本オブジェクトクラスのあたり判定（バウンディングボックス）
//
// ・自オブジェクトのバウンディングボックスと相手のバウンディングボックスとのあたり判定
//
//   CBaseObj* pOtherObj  相手のオブジェクト
//   CBBox*      pBBoxAtack   バウンディングボックスの判定をするとき
//
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と敵のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   敵オブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と敵のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::Hitcheck(CBaseObj* pOtherObj, CBBox* pBBoxAtack)
{
	BOOL bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	// バウンディングボックス同士による判定
	if ((m_bActive && m_dwStatus != DAMAGE && m_dwStatus != DEAD && m_dwStatus != FLASH) &&
		m_pBBox->OBBCollisionDetection(pBBoxAtack, &vHit, &vNrm))
	{
		HitStatus(pOtherObj, vHit, vNrm);
		bRet = TRUE;
	}
	return bRet;
}

//-----------------------------------------------------------------------------
// 基本オブジェクトクラスのあたり判定(自分の移動直線)
//
// ・自オブジェクトの移動直線と相手のバウンディングボックスとのあたり判定
//
//   CBaseObj* pOtherObj  相手のオブジェクト
//
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：ヒットしていないとき
//
//   判定結果　　
//           ヒットしたときは　　　　相手と敵のオブジェクトのm_pHitObjとm_vHitPosとm_vHitNormalに値をセット
//                                   敵オブジェクトのm_dwStatusにDAMAGEを設定する
//           ヒットしていないときは　相手と敵のオブジェクトのm_pHitObjにNULLをセット
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::HitcheckOtherLay(CBaseObj* pOtherObj)
{
	BOOL bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);
	VECTOR3 vNow = GetPositionVector(m_mWorld);
	VECTOR3 vOld = GetPositionVector(m_mWorldOld);

	// バウンディングボックスと移動直線（Lay）による判定
	if ((m_bActive && m_dwStatus != DAMAGE && m_dwStatus != DEAD && m_dwStatus != FLASH) &&
		pOtherObj->m_pBBox->OBBCollisionLay(vNow, vOld, &vHit, &vNrm))
	{
		HitStatus(pOtherObj, vHit, vNrm);
		bRet = TRUE;
	}
	return bRet;
}

//----------------------------------------------------------------------------- 
//
// ヒットした時のステータス変更
//
//
//   CBaseObj* pOtherObj  相手のオブジェクト
//	 VECTOR3   vHit		　当たった場所の座標
//	 VECTOR3   vNrm		　当たった場所の法線座標
//
//-----------------------------------------------------------------------------
void   CBaseObj::HitStatus(CBaseObj* pOtherObj, VECTOR3 vHit, VECTOR3 vNrm)
{

	m_pHitObj = pOtherObj;	//ヒットオブジェクトの更新
	pOtherObj->m_pHitObj = this;	//相手のオブジェクトのヒットオブジェクトの更新
	m_vHitPos = vHit;			//当たった場所の更新
	m_vHitNormal = vNrm;		//当たった場所の法線の更新
	pOtherObj->m_vHitPos = vHit;	//相手のオブジェクトの当たった場所の更新
	pOtherObj->m_vHitNormal = vNrm;	//相手のオブジェクトの当たった場所の法線の更新
	m_dwStatus = DAMAGE;			//ステータスをDAMAGEにする
	pOtherObj->m_dwStatus = DAMAGE;	//相手のオブジェクトのステータスをDAMAGEにする

}




//-----------------------------------------------------------------------------
//基本プロシージャクラスの引き寄せ
//
// 
//
//   CBaseObj* pOtherObj  相手のオブジェクト
//	 float	　　fDist		  相手との判定距離
//	 float		fRotateSpeed　方向転換のスピード
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：判定距離に入っていない
//
//   判定結果　　
//           判定距離以内　　　　相手オブジェクトが自オブジェクトに向きを変える
//           判定距離以外　　　　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::ObjGravity(CBaseObj* pOtherObj, float fDist, float fRotateSpeed)
{
	BOOL bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);
	MATRIX4X4 mTemp;


	VECTOR3 vTarget = GetPositionVector(m_mWorld);
	VECTOR3 vMyobj = GetPositionVector(pOtherObj->m_mWorld);
	m_fDist = magnitude(vTarget - vMyobj);	//自分のオブジェクトと相手のオブジェクトとの距離
	if (m_fDist < fDist) {	//相手との判定距離より近いなら

		vTarget.y = vMyobj.y;	//高さを同じにする
		m_vRotUp.y = GetTargetRotateVector(pOtherObj->m_mWorld, vTarget).y;	//オブジェクトの向きがターゲットを向くための角度
		RotRig(&m_vRotUp.y);	//角度を調整
		if (m_vRotUp.y > fRotateSpeed)  m_vRotUp.y = fRotateSpeed;	// fRotateSpeed度以上の方向変換は行わない
		if (m_vRotUp.y < -fRotateSpeed) m_vRotUp.y = -fRotateSpeed;	// fRotateSpeed度以上の方向変換は行わない
		mTemp = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));	//角度を求める
		pOtherObj->m_mWorld = mTemp * pOtherObj->m_mWorld;			//角度を向ける

		bRet = TRUE;

	}

	return bRet;
}


//-----------------------------------------------------------------------------
//基本プロシージャクラスの方向を徐々に向く
//
// 
//
//   CBaseObj* pOtherObj  相手のオブジェクト
//	 float		fRotateSpeed　方向転換のスピード
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：判定距離に入っていない
//
//   判定結果　　
//           判定距離以内　　　　相手オブジェクトが自オブジェクトに向きを変える
//           判定距離以外　　　　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::ObjTarget(CBaseObj* pOtherObj,  float fRotateSpeed)
{
	BOOL bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);
	MATRIX4X4 mTemp;

	m_pHitObj = pOtherObj;
	VECTOR3 vTarget = GetPositionVector(m_mWorld);
	pOtherObj->m_pHitObj = this;
	VECTOR3 vMyobj = GetPositionVector(pOtherObj->m_mWorld);
	m_fDist = magnitude(vTarget - vMyobj);	//自分のオブジェクトと相手のオブジェクトとの距離（このオブジェクト）
	pOtherObj->m_fDist = magnitude(vTarget - vMyobj);	//自分のオブジェクトと相手のオブジェクトとの距離（相手のオブジェクト）
		vTarget.y = vMyobj.y;	//高さを同じにする
		m_vRotUp.y = GetTargetRotateVector(pOtherObj->m_mWorld, vTarget).y;	//オブジェクトの向きがターゲットを向くための角度
		RotRig(&m_vRotUp.y);	//角度を調整
		if (m_vRotUp.y > fRotateSpeed)  m_vRotUp.y = fRotateSpeed;	// fRotateSpeed度以上の方向変換は行わない
		if (m_vRotUp.y < -fRotateSpeed) m_vRotUp.y = -fRotateSpeed;	// fRotateSpeed度以上の方向変換は行わない
		mTemp = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));	//角度を求める
		pOtherObj->m_mWorld = mTemp * pOtherObj->m_mWorld;			//角度を向ける
	


		bRet = TRUE;

	

	return bRet;
}



//-----------------------------------------------------------------------------
//目的地（vTargetX,Z）への移動処理  汎用関数
//
//   引数
//               VECTOR3       :vTarget :行き先
//               float fSpeedIn    :一回の移動量
//               float fRotSpeed   :回転速度(省略値は3.0f)
//
//   戻り値　：　TRUE：目的地に達した　　FALSE:まだ目的地に達していない
//               処理後、m_vPosUp, m_vRotUpに移動量が設定される
//-----------------------------------------------------------------------------
BOOL CBaseObj::TargetMove(VECTOR3 vTarget, float fSpeedIn, float fRotSpeed)
{
	BOOL ret = FALSE;
	VECTOR3 vMove, vObjPos, vObjPosOld;
	float fLen, fSpeed;
	const float fNearLimit = 0.1f;    // 目的地との近接リミット(10cm以内に近接したとき)

	vObjPos = GetPositionVector(m_mWorld);
	vObjPosOld = GetPositionVector(m_mWorldOld);

	vTarget.y = m_mWorld._42;		// ターゲットはオブジェクトと同一高さとする

	if ((vObjPos.x <= vTarget.x + fNearLimit && vObjPos.x >= vTarget.x - fNearLimit) &&		// 目的地に近接したとき
		(vObjPos.z <= vTarget.z + fNearLimit && vObjPos.z >= vTarget.z - fNearLimit))
	{  // 目的地に達したとき
		m_vPosUp.x = 0;
		m_vPosUp.y = 0;
		m_vPosUp.z = 0;
		m_vRotUp = VECTOR3(0, 0, 0);
		ret = TRUE; // 目的地に達した

	}
	else {    // 目的地への移動処理

		vMove = vTarget - vObjPos;
		fLen = magnitude(vMove);
		if (fLen < fSpeedIn)
		{
			fSpeed = fSpeedIn - fLen;
		}
		else {
			fSpeed = fSpeedIn;
		}

		m_vRotUp.y = GetTargetRotateVector(m_mWorld, vTarget).y;	// ターゲットの方向を向かせるY軸角度を求める
		RotRig(&m_vRotUp.y);
		if (m_vRotUp.y > fRotSpeed) m_vRotUp.y = fRotSpeed;		// fRotSpeed度以上の方向変換は行わない
		if (m_vRotUp.y < -fRotSpeed) m_vRotUp.y = -fRotSpeed;		// fRotSpeed度以上の方向変換は行わない

		m_vPosUp.x = 0;
		m_vPosUp.y = 0;
		m_vPosUp.z = fSpeed;

		ret = FALSE;    // まだ目的地に達していない
	}

	return ret;
}

//-----------------------------------------------------------------------------
//基本プロシージャクラスの範囲チェック
//
// 
//
//   CBaseObj* pOtherObj  相手のオブジェクト
//	 float	　　fDist		  相手との判定距離
//   戻り値　BOOL
//           TRUE:ヒットしたとき       FALSE：判定距離に入っていない
//
//   判定結果　　
//           判定距離以内　　　　相手オブジェクトが自オブジェクトに向きを変える
//           判定距離以外　　　　相手と自分のオブジェクトのm_pHitObjにNULLをセット
//
//
//-----------------------------------------------------------------------------
BOOL   CBaseObj::ObjTerritory(CBaseObj* pOtherObj, float fDist)
{
	BOOL bRet = FALSE;

	VECTOR3 vTarget = GetPositionVector(pOtherObj->m_mWorld);
	VECTOR3 vMyobj = GetPositionVector(m_mWorld);
	m_fDist = magnitude( vMyobj- vTarget);	//自分のオブジェクトと相手のオブジェクトとの距離
	if (m_fDist < fDist&&m_bDamage != true) {	//相手との判定距離より近いかつダメージを受けていなければ
		if (bShaftObjTrigger != TRUE) {		//回転状態ではないなら
			m_pShaftObj = pOtherObj;		//オブジェクトを軸にする
			m_fShaftDist = m_fDist;			//軸とオブジェクトの距離
			bShaftObjTrigger = TRUE;		//回転状態にする
		}

		bRet = TRUE;

	}

	return bRet;
}



//----------------------------------------------------------------------------- 
// オブジェクトのmWorldと引数位置との距離を求める
//
//   引数　　：　vPos :位置
//   戻り値　：　距離
//-----------------------------------------------------------------------------
float CBaseObj::GetDistance(VECTOR3 vPos)
{
	VECTOR3 vVec;
	vVec = vPos - GetPositionVector(m_mWorld);

	return  magnitude(vVec);
}
//----------------------------------------------------------------------------- 
// ステータスをリセットする
//
//   引数　　：　なし
//   戻り値　：　なし
//-----------------------------------------------------------------------------
void CBaseObj::ResetStatus()
{
	m_dwStatus = NORMAL;			// ステータス
	m_dwStatusSub = ATTACKNONE;		// ステータスサブ
	m_dwStatusPhase = 0;			// ステータスフェーズ
	
}

//============================================================================
//  オブジェクト同士が重ならないようにするメンバ関数
//
//	引数　	CBaseProc* pProj　対象とする基本プロシージャ
//
//	戻り値CBaseObj* 	オブジェクトアドレス:強制移動の相手オブジェクト　NULL:移強制動していない
//============================================================================
CBaseObj*  CBaseObj::SetKeepOffset(CBaseProc* pProc)
{
	float	fMyRadius, fOtherRadius, fAddRadius, fLen, fMvMax = 0.0f;
	VECTOR3  vMy, vOther;
	VECTOR2  vMy2, vOther2;
	MATRIX4X4	 matWk1, matWk2;
	CBaseObj     *pOtherObj, *pTargetObj = NULL;
	CBBox		 *pOtherBBox;

	if (m_pBBox == NULL) return NULL;
	vMy = GetPositionVector(m_mWorld);
	vMy2.x = vMy.x;
	vMy2.y = vMy.z;

	// 自分の半径をバウンディングボックスから算出する（前と右幅の大きい方を採用）
	fMyRadius = (m_pBBox->m_vMax.x > m_pBBox->m_vMax.z) ? m_pBBox->m_vMax.x : m_pBBox->m_vMax.z;


	// オブジェクト配列の探索
	for (DWORD i = 0; i < pProc->GetObjArrayPtr().size(); i++)
	{
		pOtherObj = pProc->GetObjArrayPtr()[i];

		if (!pOtherObj->m_bActive) continue;	// 現在生きていなければ対象外
		if (pOtherObj == this) continue;	// 自分自身は対象外
		pOtherBBox = pOtherObj->m_pBBox;
		if (pOtherBBox == NULL) continue;	// バウンディングボックスがなければ対象外
		vOther = GetPositionVector(pOtherObj->m_mWorld);
		vOther2.x = vOther.x;
		vOther2.y = vOther.z;

		// バウンディングボックス同士の高さが一致しているか。範囲内に入っていなければ対象外
		if ((vMy.y + m_pBBox->m_vMin.y) > (vOther.y + pOtherObj->m_pBBox->m_vMax.y) ||
			(vMy.y + m_pBBox->m_vMax.y) < (vOther.y + pOtherObj->m_pBBox->m_vMin.y)) {
			continue;
		}

		// 相手の半径をバウンディングボックスから算出する（前と右幅の大きい方を採用）
		fOtherRadius = (pOtherBBox->m_vMax.x > pOtherBBox->m_vMax.z) ? pOtherBBox->m_vMax.x : pOtherBBox->m_vMax.z;

		fAddRadius = fMyRadius + fOtherRadius;
		if (fabs(vMy2.x - vOther2.x) < fAddRadius && fabs(vMy2.y - vOther2.y) < fAddRadius) {		// まず、ラフに水平方向（ＸＺ方向）で半径の範囲内に入っているか
			fLen = magnitude(vMy2 - vOther2);		// 水平方向（ＸＺ方向）で半径の距離内に入っているか
			if (fLen < fAddRadius) {
				fLen = fAddRadius - fLen;	// くい込み距離にする
				if (fLen > fMvMax) {		// 今までの中で、一番接近しているか
					fMvMax = fLen;
					pTargetObj = pOtherObj;
				}
			}
		}
	}

	if (pTargetObj) {	// 半径内に入った相手がいた場合
		vOther = GetPositionVector(pTargetObj->m_mWorld);
		vOther.y = vMy.y;
		matWk1 = GetLookatMatrix(vMy, vOther);					// 相手の方向を向かせるマトリックスを作成する
		matWk2 = XMMatrixTranslation(0.0f, 0.0f, -fMvMax);		// くい込み値だけ、Ｚ方向の反対方向に移動するマトリックスを作成する
		matWk1 = matWk2 * matWk1;								// くい込み値の反対方向に移動する
		vMy.x = 0.0f - vMy.x;
		vMy.y = 0.0f - vMy.y;
		vMy.z = 0.0f - vMy.z;
		matWk2 = XMMatrixTranslation(vMy.x, vMy.y, vMy.z);		// 自分の位置の逆数の位置
		matWk2 = m_mWorld * matWk2;								// 自分の原点位置での角度のみにする
		vMy = GetPositionVector(matWk1);						// くい込み値の反対方向に移動した位置
		matWk1 = XMMatrixTranslation(vMy.x, vMy.y, vMy.z);		// くい込み値の反対方向に移動した位置のみのマトリックス
		m_mWorld = matWk2 * matWk1;								// 自分の新しい位置と角度のワールドマトリックス
	}


	// 下位のプロシージャ配列の探索
	if (pTargetObj == NULL)
	{
		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
		{
			pTargetObj = SetKeepOffset(pProc->GetProcArrayPtr()[i]);      // 下位のプロシージャの処理（再帰処理）
			if (pTargetObj) break;
		}
	}

	return pTargetObj;
}


//----------------------------------------------------------------------
//相手のいる方を向く
//
//	MATRIX4X4	MyWorld		自分のワールドマトリックス
//	 MATRIX4X4 TargetWorld		相手のワールドマトリックス
//
//
//---------------------------------------------------------------------
MATRIX4X4 CBaseObj::TurnTarget(MATRIX4X4 MyWorld, MATRIX4X4 TargetWorld)
{
	VECTOR3	vRotUp;			
	VECTOR3 vTarget = GetPositionVector(TargetWorld);
	VECTOR3 vMyobj = GetPositionVector(MyWorld);
	MATRIX4X4 mTran;
	MATRIX4X4 mWorld = MyWorld;

	vTarget.y = vMyobj.y;
	vRotUp.y = GetTargetRotateVector(mWorld, vTarget).y;	//オブジェクトの向きがターゲットを向くための角度
	RotRig(&m_vRotUp.y);	//角度の調整

	mTran = XMMatrixRotationY(XMConvertToRadians(vRotUp.y));	//角度を求める
	mWorld = mTran * mWorld;		//角度を向ける

	return mWorld;

}

//----------------------------------------------------------------------
//	軸に合わせて回転する
//
//	MATRIX4X4	MyWorld		自分のワールドマトリックス
//	 MATRIX4X4 TargetWorld		軸となるワールドマトリックス
//	float		fSpeed		回転するスピード
//	float		fDist		軸との距離
//
//
//---------------------------------------------------------------------
MATRIX4X4 CBaseObj::RotTarget(MATRIX4X4 MyWorld, MATRIX4X4 TargetWorld, float fSpeed, float fDist)
{
	MATRIX4X4 mWorld = MyWorld;
	MATRIX4X4 mPos;
	MATRIX4X4 mRotWorld=GetRotateMatrix(mWorld);
	VECTOR3 vTarget = GetPositionVector(TargetWorld);
	MATRIX4X4 mTargetPos = XMMatrixTranslation(vTarget.x, vTarget.y, vTarget.z);
	//オブジェクトを軸との距離分離した位置にする
	mPos = XMMatrixTranslation(0, 0, -fDist);
	mWorld = mPos * mRotWorld*mTargetPos;
	//オブジェクトを移動させる
	mPos = XMMatrixTranslation(fSpeed, 0, 0);
	mWorld = mPos * mWorld;
	//オブジェクトを軸の方向に向ける
	mWorld =TurnTarget(mWorld, TargetWorld);

	mRotWorld = GetRotateMatrix(mWorld);		//ワールドマトリックスの角度取得
	//軸と同じ位置にする
	vTarget = GetPositionVector(TargetWorld);
	mTargetPos = XMMatrixTranslation(vTarget.x, vTarget.y, vTarget.z);
	//オブジェクトを軸との距離分離した位置にする
	mPos = XMMatrixTranslation(0, 0, -fDist);
	mWorld = mPos * mRotWorld*mTargetPos;


	return mWorld;

}

//-----------------------------------------------------------------------------
//
//	角度を0～360にする
//
//   float* fRotUp  角度
//
//-----------------------------------------------------------------------------
void   CBaseObj::RotRig(float* fRotUp)
{

	if (*fRotUp >= 180) *fRotUp -= 360;
	if (*fRotUp <= -180) *fRotUp += 360;

}

//-----------------------------------------------------------------------------  
//
//	基本コンストラクタの関数
//
//	const int		nMaxHP		最大HP
//	const int		nAtc		攻撃力
//	VECTOR3			vMin		バウンディングボックスの最小値
//	VECTOR3			vMax		バウンディングボックスの最大値
//
//-----------------------------------------------------------------------------
void   CBaseObj::ObjBasicConstructor(const int nMaxHP, const int nAtc, VECTOR3 vMin, VECTOR3 vMax)
{
	m_bDamage = FALSE;

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

	// バウンディングボックスの設定
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                     

	m_nHp = m_nMaxHp = nMaxHP;
	m_nAtc = nAtc;


}

//-----------------------------------------------------------------------------
//
//	オブジェクトを反射する
//
//--M.Kamei_Point
//--Point_Reflection
//
//-----------------------------------------------------------------------------
void   CBaseObj::ObjReflection()
{

	VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置
	VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // 自分の前の位置

	VECTOR3 vN;
	vN = m_vHitNormal;	//当たった場所の法線座標を取得
	vN = normalize(vN);	//正規化する
	vN.y = 0;	//高さは変えない

	VECTOR3 vR;
	if (vHear != vHearOld) {

		VECTOR3 vL = normalize(vHear - vHearOld);	//移動ベクトル（正規化）
		vR = (2 * dot(-vL, vN)*vN) + vL;			//反射ベクトル

	}
	vR = vN;
	m_mWorld = GetLookatMatrix(vHear, vHear + vR);	//ワールドマトリックスを更新

}

//-----------------------------------------------------------------------------
//
//	オブジェクトを反射方向を向ける
//
//
//-----------------------------------------------------------------------------
MATRIX4X4   CBaseProc::ObjReflectionStart(CBaseObj* mMyObj, CBaseObj* mHitObj)
{
	MATRIX4X4 mLay;
	VECTOR3 vHear = GetPositionVector(mMyObj->GetWorld()); // 自分の今いる位置
	VECTOR3 vHearOld = GetPositionVector(mMyObj->GetWorldOld()); // 自分の前の位置

	VECTOR3 vN ;

	vN = mMyObj->GetHitNormal();
	vN = normalize(vN);	//正規化する
	vN.y = 0;	//高さは変えない

	VECTOR3 vR;
	if (vHear != vHearOld) {

		VECTOR3 vL = normalize(vHear - vHearOld);	//移動ベクトル（正規化）
		vR = (2 * dot(-vL, vN)*vN) + vL;			//反射ベクトル（公式）

	}
	else {
		vR = vN;		//反射ベクトル
	}

	mLay = GetLookatMatrix(vHear, vHear + vR);	//ワールドマトリックスを更新

	return mLay;
}


//-----------------------------------------------------------------------------
//
//	出現時に四方向の選択方向を向く
//
//	DWORD		dPosStatus		位置の四方向のどれか
//	MATRIX4X4	*m_mWorld		ワールドマトリックス
//
//
//-----------------------------------------------------------------------------
void   CBaseObj::ObjAppearanceDirection(DWORD dPosStatus, MATRIX4X4 *m_mWorld)
{
	MATRIX4X4 mTran;
	MATRIX4X4 mWorld = *m_mWorld;

	switch (dPosStatus)
	{
	case FRONT:
		mTran = XMMatrixRotationY(XMConvertToRadians(180));
		mWorld = mTran * mWorld;

		break;

	case RIGHT:
		mTran = XMMatrixRotationY(XMConvertToRadians(-90));
		mWorld = mTran * mWorld;

		break;
	case BACK:
		mTran = XMMatrixRotationY(XMConvertToRadians(0));
		mWorld = mTran * mWorld;

		break;
	case LEFT:
		mTran = XMMatrixRotationY(XMConvertToRadians(90));
		mWorld = mTran * mWorld;

		break;
	}

	*m_mWorld = mWorld;
}

//-----------------------------------------------------------------------------
//
//	オブジェクトの削除の基本処理
//
//-----------------------------------------------------------------------------
void   CBaseObj::ObjBasicDelete()
{
	m_bActive = FALSE;
	m_nHp = m_nMaxHp;
	m_dwStatus = NORMAL;
	m_dwStatusSub = ATTACKNONE;
	m_dwStatusPhase = 0;
}

//-----------------------------------------------------------------------------
//
//	オブジェクトの往復
//
//	VECTOR3		vMin		位置の最小値
//	VECTOR3		vMax		位置の最大値
//
//
//-----------------------------------------------------------------------------
void   CBaseObj::ObjRoundTrip(VECTOR3 vMin,VECTOR3 vMax)
{
	VECTOR3 vObjPos;
	vObjPos = GetPositionVector(m_mWorld);
	if (vObjPos.x < vMin.x) {
		m_vPosUp.x = m_vPosUp.x*(-1);
	}
	else if (vObjPos.x >vMax.x) {
		m_vPosUp.x = m_vPosUp.x*(-1);

	}
	else if (vObjPos.z < vMin.z) {
		m_vPosUp.x = m_vPosUp.x*(-1);

	}
	else if (vObjPos.z > vMax.z) {
		m_vPosUp.x = m_vPosUp.x*(-1);

	}
}

//-----------------------------------------------------------------------------
//
// ナビゲーションマップに従って発生させる
//
//	VECTOR3		vMin		ナビゲーションマップの最小値
//	VECTOR3		vMax		ナビゲーションマップの最大値
//
//-----------------------------------------------------------------------------
void   CBaseObj::ObjNavOccurrence(VECTOR3 vMin, VECTOR3 vMax)
{
	m_mWorld = XMMatrixTranslation((float)Random(vMin.x, vMax.x),
		vMax.y, (float)Random(vMin.z, vMax.z));
	m_mWorldOld = m_mWorld;

}
