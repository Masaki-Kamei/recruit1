//=============================================================================
//		スキルの処理
//															Weapon.cpp
//=============================================================================
#include  "Enemy.h"
#include  "Playchar.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"
#include  "BackFore.h"




//=============================================================================================================================
//
// スキルメインプロシージャのコンストラクタ
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
// ----------------------------------------------------------------------------------------------------------------------------
CWeaponProc::CWeaponProc(CGameMain* pGMain) : CBaseProc(pGMain)
{


	m_pWeaponSwordProc = new CWeaponSwordProc(pGMain);		// スキル・剣プロシージャ
	m_pProcArray.push_back(m_pWeaponSwordProc);				// プロシージャをプロシージャ配列に登録する


	m_pWeaponBallProc = new CWeaponBallProc(pGMain);		// スキル・ボールプロシージャ
	m_pProcArray.push_back(m_pWeaponBallProc);				// プロシージャをプロシージャ配列に登録する


	m_pWeaponHoldProc = new CWeaponHoldProc(pGMain);		// スキル・手に持つアイテムのプロシージャ
	m_pProcArray.push_back(m_pWeaponHoldProc);				// プロシージャをプロシージャ配列に登録する



	m_pWeaponDivBallProc = new CWeaponDivBallProc(pGMain);		// スキル・拡散ボールプロシージャ
	m_pProcArray.push_back(m_pWeaponDivBallProc);				// プロシージャをプロシージャ配列に登録する


	m_pWeaponShieldProc = new CWeaponShieldProc(pGMain);		// スキル・シールドプロシージャ
	m_pProcArray.push_back(m_pWeaponShieldProc);				// プロシージャをプロシージャ配列に登録する

	m_pWeaponBigBallProc = new CWeaponBigBallProc(pGMain);		// スキル・ビッグボールプロシージャ
	m_pProcArray.push_back(m_pWeaponBigBallProc);				// プロシージャをプロシージャ配列に登録する

	m_pWeaponPenetBallProc = new CWeaponPenetBallProc(pGMain);		// スキル・貫通ボールプロシージャ
	m_pProcArray.push_back(m_pWeaponPenetBallProc);				// プロシージャをプロシージャ配列に登録する
		
	m_pWeaponRollBallProc = new CWeaponRollBallProc(pGMain);		// スキル・回転ボールプロシージャ
	m_pProcArray.push_back(m_pWeaponRollBallProc);				// プロシージャをプロシージャ配列に登録する


	m_pWeaponWallProc = new CWeaponWallProc(pGMain);		// スキル・壁プロシージャ
	m_pProcArray.push_back(m_pWeaponWallProc);				// プロシージャをプロシージャ配列に登録する

	m_pWeaponBendBallProc = new CWeaponBendBallProc(pGMain);		// スキル・曲がるボールプロシージャ
	m_pProcArray.push_back(m_pWeaponBendBallProc);				// プロシージャをプロシージャ配列に登録する

}


// ================================================================================================================================
// 
// 各スキルプロシージャ毎の処理
// 
// ================================================================================================================================


// ================================================================================================================================
//============================================================================
//
// スキル・剣プロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CWeaponSwordProc::CWeaponSwordProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_dwProcID = WEAPON_SWORD;	
		m_pObjArray.push_back(new CWeaponSwordObj(m_pGMain));	// スキル・剣オブジェクト
		m_pObjArray[0]->SetObjID(m_dwProcID);
		m_pObjArray[0]->SetObjNo(0);
		m_pObjArray[0]->SetPlayerNo(FIRSTPLAYER);
		m_pObjArray.push_back(new CWeaponSwordObj(m_pGMain));	// スキル・剣オブジェクト
		m_pObjArray[1]->SetObjID(m_dwProcID);
		m_pObjArray[1]->SetObjNo(1);
		m_pObjArray[1]->SetPlayerNo(SECONDPLAYER);

}

// ---------------------------------------------------------------------------
//
// スキル剣・プロシージャの発生
//
// ---------------------------------------------------------------------------

BOOL CWeaponSwordProc::Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner)
{

	m_pObjArray[0]->Start(mMat, vMin, vMax, dwOwner);	// スキル・剣オブジェクト

	return TRUE;
}

// ---------------------------------------------------------------------------
// スキル剣・プロシージャの発生
//
// ---------------------------------------------------------------------------

BOOL CWeaponSwordProc::Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner, DWORD dwPlayerNo)
{
	if(dwPlayerNo==FIRSTPLAYER)m_pObjArray[0]->Start(mMat, vMin, vMax, dwOwner, dwPlayerNo);	// スキル・剣オブジェクト
	if (dwPlayerNo == SECONDPLAYER)m_pObjArray[1]->Start(mMat, vMin, vMax, dwOwner, dwPlayerNo);	// スキル・剣オブジェクト

	return TRUE;
}

//============================================================================
//
// スキル・剣オブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CWeaponSwordObj::CWeaponSwordObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;    // 剣の攻撃力

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

	// BBoxの設定(大きさは、仮に設定)
	m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.1f, -0.1f, -0.1f), VECTOR3(0.1f, 0.1f, 0.1f));
	m_pBBoxSub= new CBBox(m_pGMain->m_pShader, VECTOR3(-0.1f, -0.1f, -0.1f), VECTOR3(0.1f, 0.1f, 0.1f));


	m_nAtc = nAtc;
	m_dwOwner = 0;
	dwUseNumWeapon = 0;
}
// ---------------------------------------------------------------------------
//
// スキル・剣オブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponSwordObj::~CWeaponSwordObj()
{
	;
}
// ---------------------------------------------------------------------------
//
// スキル・剣オブジェクトの発生と処理、描画
//
//     MATRIX4X4  mMat        ：剣の位置
//     VECTOR3 vMin        ：バウンディングボックスの最小値
//     VECTOR3 vMax        ：バウンディングボックスの最大値
//     DWORD       dwOwner     ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponSwordObj::Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner)
{
	m_bActive = TRUE;  // スタート時に表示開始
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();

	VECTOR3 vOffset(0.0f, 0.0f, 0.0f);

	int		WeaponNo = pPcObj->GetWeaponNo();		//スキルのナンバー		
	int		WeaponColuman = pPcObj->GetWeaponColuman()-1;	//選択中のスキル欄	

	// バウンディングボックスのサイズが変わっていたら作り替える
	if (m_pBBox->m_vMin.x != vMin.x || m_pBBox->m_vMin.y != vMin.y || m_pBBox->m_vMin.z != vMin.z
		||
		m_pBBox->m_vMax.x != vMax.x || m_pBBox->m_vMax.y != vMax.y || m_pBBox->m_vMax.z != vMax.z)
	{
		m_pBBox->InitBBox(vMin, vMax);   // バウンディングボックスの大きさ変更
	}
	m_pBBox->m_mWorld = mMat;   // バウンディングボックスのワールドマトリックスをセット
	
	//剣攻撃の当たり判定を横だけにする--------------------------------	
	MATRIX4X4 mPatternWorld = mMat;
	VECTOR3	vPatternPosition = GetPositionVector(mMat);
	MATRIX4X4 mWorldUpY = XMMatrixTranslation(0, 0.01,0);
	mPatternWorld = mWorldUpY * mPatternWorld;
	//m_pBBox->m_mWorld = mPatternWorld;
	
	VECTOR3	vMinBBox, vMaxBBox;
	vMinBBox = VECTOR3(-0.3,-1.0,-0.3);
	vMaxBBox = VECTOR3(0.0,1.0,1.0);

	m_pBBox->InitBBox(vMinBBox, vMaxBBox);
	m_pBBoxSub->InitBBox(vMinBBox, vMaxBBox);		
	VECTOR3 vBBoxPos;
	MATRIX4X4 mBBoxWorld;

	vBBoxPos = GetPositionVector(mPatternWorld);

	mBBoxWorld = XMMatrixTranslation(vBBoxPos.x, vBBoxPos.y / 2, vBBoxPos.z);
	
	MATRIX4X4 mBBoxRot = TurnTarget(mBBoxWorld, mMat);
	mBBoxRot = XMMatrixRotationY(XMConvertToRadians(180)) *mBBoxRot;
	if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetAnimStatus().animNum == 3) {		//逆手打ちの時にバウンディングボックスの正面に向く
		mBBoxRot = XMMatrixRotationZ(XMConvertToRadians(180)) *mBBoxRot;
	}
	m_pBBox->m_mWorld = mBBoxRot;
	m_pBBoxSub->m_mWorld = mBBoxRot;


	m_dwOwner = dwOwner;

	//------------------------------------------------

		// 敵やＰＣとのあたり判定
	BOOL	bHit = FALSE;
	//バウンディングボックス同士で当たり判定を確認
		if (m_pGMain->m_pEnmProc->m_pEnmBallProc->Hitcheck(this, m_pBBoxSub)
			|| m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->Hitcheck(this, m_pBBoxSub) || m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->Hitcheck(this, m_pBBoxSub)) {

			VECTOR3 vHitObjPos = GetPositionVector(m_pHitObj->GetWorld());
			MATRIX4X4 mHitObjWorld = XMMatrixTranslation(vHitObjPos.x, vHitObjPos.y, vHitObjPos.z);		//ヒットオブジェクトの位置を取得	

			m_pBBox->m_mWorld = GetRotateMatrix(mBBoxRot)*mHitObjWorld;		//ヒットオブジェクトの位置と同じ位置にする
			bHit = TRUE;
			m_pHitObj->SetStatus(NORMAL);

		}
	

		if ((dwOwner != ENM && m_pGMain->m_pEnmProc->m_pEnmBallProc->HitcheckOtherLay(this)) ||
			(dwOwner != PC && m_pGMain->m_pPcProc->HitcheckOtherLay(this)))
		{

			if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//スキルのクールタイム		
				if (WeaponNo == WEAPON_DIV) {			//分裂する弾の開始	
					m_pGMain->m_pWeaponProc->m_pWeaponDivBallProc->Start(m_pHitObj->GetWorld(), vOffset, pPcObj->GetWorld(), PC); // ボール発射
					WeaponStart(WEAPON_DIV_WAITTIME, WeaponColuman);

				}
			}
			if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//スキルのクールタイム	
				if (WeaponNo == WEAPON_BIGBALL) {			//大きくなる弾の開始
					m_pGMain->m_pWeaponProc->m_pWeaponBigBallProc->Start(this, m_pHitObj, PC); // ボール発射
					WeaponStart(WEAPON_BIGBALL_WAITTIME, WeaponColuman);

				}
			}
			if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//スキルのクールタイム		
				if (WeaponNo == WEAPON_PENETBALL) {			//貫通する弾の開始
					m_pGMain->m_pWeaponProc->m_pWeaponPenetBallProc->Start(this, m_pHitObj, PC); // ボール発射
					WeaponStart(WEAPON_PENETBALL_WAITTIME, WeaponColuman);

				}
			}
			if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//スキルのクールタイム		
				if (WeaponNo == WEAPON_ROLLBALL) {			//回転する弾の開始	
					m_pGMain->m_pWeaponProc->m_pWeaponRollBallProc->Start(this, m_pHitObj, PC); // ボール発射
					WeaponStart(WEAPON_ROLLBALL_WAITTIME, WeaponColuman);
				}
			}

			if(m_pHitObj->GetDamage()!=TRUE)
			m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), m_vHitPos, VECTOR2(2.5, 1.0), VECTOR2(164, 391), VECTOR2(111, 30),100, m_dwPlayerNo,LENO_SHAKEBESIDETYPE,1.0);	
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetSwordHitTrigger(TRUE);

		}
	
	if(m_pGMain->m_pWeaponProc->m_pWeaponBallProc->HitcheckOtherLay(this))		m_pGMain->m_pPcProc->GetPcObjPtr()->SetSwordHitTrigger(TRUE);
	if(m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->HitcheckOtherLay(this))		m_pGMain->m_pPcProc->GetPcObjPtr()->SetSwordHitTrigger(TRUE);		
	if (m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->HitcheckOtherLay(this))
	{
		m_pGMain->m_pPcProc->GetPcObjPtr()->SetSwordHitTrigger(TRUE);
	}


	if(m_pGMain->m_pWeaponProc->m_pWeaponWallProc->Hitcheck(this, m_pBBoxSub))		m_pGMain->m_pPcProc->GetPcObjPtr()->SetSwordHitTrigger(TRUE);	


	if (m_dwStatus== DAMAGE) {
		UpdateDamage();  // ＰＣオブジェクトの更新 ダメージ状態（DAMAGE）
	}

	m_bActive = FALSE;  // １回処理したら、消す

	return TRUE;
}


// ---------------------------------------------------------------------------
// スキル・剣オブジェクトの発生と処理、描画
//
//     MATRIX4X4  mMat        ：剣の位置
//     VECTOR3 vMin        ：バウンディングボックスの最小値
//     VECTOR3 vMax        ：バウンディングボックスの最大値
//     DWORD       dwOwner     ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponSwordObj::Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner, DWORD dwPlayerNo)
{

	m_bActive = TRUE;  // スタート時に表示開始
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	if(dwPlayerNo==SECONDPLAYER)pPcObj = m_pGMain->m_pPcProc->GetPcSecObjPtr();		
	m_dwPlayerNo = dwPlayerNo;

	VECTOR3 vOffset(0.0f, 0.0f, 0.0f);

	int		WeaponNo = pPcObj->GetWeaponNo();		//スキルのナンバー		
	int		WeaponColuman = pPcObj->GetWeaponColuman() - 1;	//選択中のスキル欄		
	// バウンディングボックスのサイズが変わっていたら作り替える
	if (m_pBBox->m_vMin.x != vMin.x || m_pBBox->m_vMin.y != vMin.y || m_pBBox->m_vMin.z != vMin.z
		||
		m_pBBox->m_vMax.x != vMax.x || m_pBBox->m_vMax.y != vMax.y || m_pBBox->m_vMax.z != vMax.z)
	{
		m_pBBox->InitBBox(vMin, vMax);   // バウンディングボックスの大きさ変更
	}
	m_pBBox->m_mWorld = mMat;   // バウンディングボックスのワールドマトリックスをセット

	//剣攻撃の当たり判定を横だけにする--------------------------------	
	MATRIX4X4 mPatternWorld = mMat;
	VECTOR3	vPatternPosition = GetPositionVector(mMat);
	MATRIX4X4 mWorldUpY = XMMatrixTranslation(0, 0.01, 0);
	mPatternWorld = mWorldUpY * mPatternWorld;
	//m_pBBox->m_mWorld = mPatternWorld;

	VECTOR3	vMinBBox, vMaxBBox;
	vMinBBox = VECTOR3(-0.3, -1.0, -0.3);
	vMaxBBox = VECTOR3(0.0, 1.0, 1.0);

	m_pBBox->InitBBox(vMinBBox, vMaxBBox);
	m_pBBoxSub->InitBBox(vMinBBox, vMaxBBox);		

	VECTOR3 vBBoxPos;
	MATRIX4X4 mBBoxWorld;

	vBBoxPos = GetPositionVector(mPatternWorld);

	mBBoxWorld = XMMatrixTranslation(vBBoxPos.x, vBBoxPos.y / 2, vBBoxPos.z);

	MATRIX4X4 mBBoxRot = TurnTarget(mBBoxWorld, mMat);
	mBBoxRot = XMMatrixRotationY(XMConvertToRadians(180)) *mBBoxRot;
	if (pPcObj->GetAnimStatus().animNum == 3) {		//逆手打ちの時にバウンディングボックスの正面に向く
		mBBoxRot = XMMatrixRotationZ(XMConvertToRadians(180)) *mBBoxRot;
	}
	m_pBBox->m_mWorld = mBBoxRot;
	m_pBBoxSub->m_mWorld = mBBoxRot;


	m_dwOwner = dwOwner;

	//------------------------------------------------

		// 敵やＰＣとのあたり判定
	BOOL	bHit = FALSE;
	//バウンディングボックス同士で当たり判定を確認	
		if (m_pGMain->m_pEnmProc->m_pEnmBallProc->HitcheckMulti(this, m_pBBoxSub, dwPlayerNo) 
			|| m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->HitcheckMulti(this, m_pBBoxSub, dwPlayerNo) || m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->HitcheckMulti(this, m_pBBoxSub, dwPlayerNo)) {

			VECTOR3 vHitObjPos = GetPositionVector(m_pHitObj->GetWorld());
			MATRIX4X4 mHitObjWorld = XMMatrixTranslation(vHitObjPos.x, vHitObjPos.y, vHitObjPos.z);		//ヒットオブジェクトの位置を取得	

			m_pBBox->m_mWorld = GetRotateMatrix(mBBoxRot)*mHitObjWorld;		//ヒットオブジェクトの位置と同じ位置にする
			bHit = TRUE;
			m_pHitObj->SetStatus(NORMAL);

		}

		if (bHit == TRUE) {
			if (m_pHitObj->GetDamage() != TRUE) {
				if ((dwOwner != ENM && m_pGMain->m_pEnmProc->m_pEnmBallProc->HitcheckMultiOtherLay(this, dwPlayerNo)) ||
					(dwOwner != PC && m_pGMain->m_pPcProc->HitcheckMultiOtherLay(this, dwPlayerNo)))
				{

					if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//スキルのクールタイム	
						if (WeaponNo == WEAPON_DIV) {			//分裂する弾の開始
							m_pGMain->m_pWeaponProc->m_pWeaponDivBallProc->Start(m_pHitObj->GetWorld(), vOffset, pPcObj->GetWorld(), PC, dwPlayerNo); // ボール発射
							WeaponStart(WEAPON_DIV_WAITTIME, WeaponColuman);
							if (m_pGMain->m_dwGameStatus == GAMEMULTI)pPcObj->WeaponUseMulti();

						}
					}
					if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//スキルのクールタイム	
						if (WeaponNo == WEAPON_BIGBALL) {			//大きくなる弾の開始	
							m_pGMain->m_pWeaponProc->m_pWeaponBigBallProc->Start(this, m_pHitObj, PC, dwPlayerNo); // ボール発射	
							WeaponStart(WEAPON_BIGBALL_WAITTIME, WeaponColuman);
							if (m_pGMain->m_dwGameStatus == GAMEMULTI)pPcObj->WeaponUseMulti();


						}
					}
					if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//スキルのクールタイム	
						if (WeaponNo == WEAPON_PENETBALL) {			//貫通する弾の開始	
							m_pGMain->m_pWeaponProc->m_pWeaponPenetBallProc->Start(this, m_pHitObj, PC, dwPlayerNo); // ボール発射
							WeaponStart(WEAPON_PENETBALL_WAITTIME, WeaponColuman);
							if (m_pGMain->m_dwGameStatus == GAMEMULTI)pPcObj->WeaponUseMulti();

						}
					}
					if (m_nWeapoWaitTime[WeaponColuman] <= 0) {		//スキルのクールタイム		
						if (WeaponNo == WEAPON_ROLLBALL) {			//回転する弾の開始
							m_pGMain->m_pWeaponProc->m_pWeaponRollBallProc->Start(this, m_pHitObj, PC, dwPlayerNo); // ボール発射	
							WeaponStart(WEAPON_ROLLBALL_WAITTIME, WeaponColuman);
							if (m_pGMain->m_dwGameStatus == GAMEMULTI)pPcObj->WeaponUseMulti();

						}
					}

					if (m_pHitObj->GetDamage() != TRUE)
						m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), m_vHitPos, VECTOR2(2.5, 1.0), VECTOR2(164, 391), VECTOR2(111, 30), 100, m_dwPlayerNo, LENO_SHAKEBESIDETYPE, 1.0);	//--2022.03.28.8:30
					pPcObj->SetSwordHitTrigger(TRUE);

				}
			}
		}
	if (m_pGMain->m_pWeaponProc->m_pWeaponBallProc->HitcheckMultiOtherLay(this, dwPlayerNo))		pPcObj->SetSwordHitTrigger(TRUE);
	if (m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->HitcheckMultiOtherLay(this, dwPlayerNo))		pPcObj->SetSwordHitTrigger(TRUE);	
	if (m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->HitcheckMultiOtherLay(this, dwPlayerNo))
	{
		pPcObj->SetSwordHitTrigger(TRUE);
	}


	if (m_pGMain->m_pWeaponProc->m_pWeaponWallProc->HitcheckMulti(this, m_pBBoxSub, dwPlayerNo))		pPcObj->SetSwordHitTrigger(TRUE);	


	if (m_dwStatus == DAMAGE) {
		UpdateDamage();  // ＰＣオブジェクトの更新 ダメージ状態（DAMAGE）
	}




	m_bActive = FALSE;  // １回処理したら、消す

	return TRUE;
}




// ---------------------------------------------------------------------------
//
// スキル・剣オブジェクトの更新
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponSwordObj::Update()
{

	//クールタイム処理		
	for (int i = 0; i < 3; i++) {
		if (m_nWeapoWaitTime[i] > 0) {

			if (nCount[i] > 60) {
				m_nWeapoWaitTime[i]--;
				nCount[i] = 0;
			}
			else {
				nCount[i]++;
			}

		}
		else if (m_nWeapoWaitTime[i] <= 0) {
			m_nWeapoWaitTime[i] = 0;
		}

	}
	;
}

// ---------------------------------------------------------------------------
//
// スキル・剣オブジェクトのダメージ更新
//
//
//
// ---------------------------------------------------------------------------

void CWeaponSwordObj::UpdateDamage() {
	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
//
//スキル使用時の固定処理
//
//    DWORD			dwWaitTime		スキルごとのクールタイム
//    const int		WeaponColuman	スキルの欄
//
//
// ---------------------------------------------------------------------------
void CWeaponSwordObj::WeaponStart(DWORD dwWaitTime,const int WeaponColuman)
{
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	if (m_dwPlayerNo == SECONDPLAYER)pPcObj = m_pGMain->m_pPcProc->GetPcSecObjPtr();

	m_nWeapoWaitTime[WeaponColuman] = dwWaitTime;
	m_nWeapoMaxWaitTime[WeaponColuman] = dwWaitTime;
	m_pHitObj->SetActive(FALSE);
	pPcObj->SetWeaponColuman(0);		//スキル使用時選解除する	
	pPcObj->SetWeaponNo(0);
	dwUseNumWeapon++;					


}


// ---------------------------------------------------------------------------
//
// スキル・剣オブジェクトのレンダリング
// (バウンディングボックスのレンダリング)
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponSwordObj::Render()
{

	//   バウンディングボックスレンダリング
	m_pBBox->Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	m_pBBoxSub->Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);

}

// ================================================================================================================================
//============================================================================
//
// スキル・ボールプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CWeaponBallProc::CWeaponBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ボールメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark_Big.mesh"));

	for (int i = 0; i < BALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponBallObj(m_pGMain));	// m_pObjArrayにスキル・ボールオブジェクトを生成する
		((CWeaponBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // メッシュのアドレスをオブジェクトに設定する
	}
}
//============================================================================
//
// スキル・ボールプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponBallProc::~CWeaponBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
//
// スキル・ボールプロシージャの発射
//
//  MATRIX4X4  mGun         ：銃の位置マトリックス
//  VECTOR3    vOffset      ：位置の微調整
//  MATRIX4X4  mOwnerWorld  ：発射するキャラのマトリックス
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
// ---------------------------------------------------------------------------
BOOL CWeaponBallProc::Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner)
{
	MATRIX4X4 mLay, mOwnerRot, mOffset;

	mLay = GetPositionMatrix(mGun);               // 銃の位置(回転を取り除く)
	mOwnerRot = GetRotateMatrix(mOwnerWorld);     // 発射するキャラの回転マトリックスのみ(位置を取り除く)にする
	mLay = mOwnerRot * mLay;                      // 銃の位置から、キャラの方向で発射するマトリックスを作る
	mOffset = XMMatrixTranslation(vOffset.x, vOffset.y + 0.5, vOffset.z);	// 位置の微調整
	mLay = mOffset * mLay;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner);	       // スキル・ボールオブジェクトの発射
			return TRUE;
		}
	}
	return FALSE;
}

//============================================================================
//
// スキル・ボールオブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CWeaponBallObj::CWeaponBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // 攻撃力

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-0.15f, -0.15f, -0.15f);
	VECTOR3 vMax(0.15f, 0.15f, 0.15f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                           

}
// ---------------------------------------------------------------------------
//
// スキル・ボールオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponBallObj::~CWeaponBallObj()
{
	;
}

// ---------------------------------------------------------------------------
//
// スキル・ボールオブジェクトの発射
//
//     MATRIX4X4 mStartWorld     ボールの発射位置のマトリックス
//     DWORD      dwOwner        スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponBallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	const float fSpeed = 0.05f;		// ボールの速さ
	const int nLifeTime = 300;		// ボールの持続時間
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;

	m_vPosUp = VECTOR3(0, 0, fSpeed);
	m_vGravity = VECTOR3(0, fSpeed, 0);

	m_nCnt1 = nLifeTime;
	m_dwOwner = dwOwner;
	return TRUE;
}

// ---------------------------------------------------------------------------
//
// ボールオブジェクトのローカル軸マトリックスを得る関数
//
//  m_mWorldの位置情報とm_fLocalRotYの角度情報を元に
//  ローカル軸マトリックスを返す
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponBallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
//
// スキル・ボールオブジェクトの更新
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponBallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		MATRIX4X4 mTran;
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// 自分ボールの位置判定と移動
		VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // 自分の前の位置


	// 敵やＰＣとのあたり判定
		if ((m_dwOwner != ENM && m_pGMain->m_pEnmProc->Hitcheck(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld))) ||
			(m_dwOwner != PC && m_pGMain->m_pPcProc->Hitcheck(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld))))
		{
			VECTOR3 vN = GetPositionVector(m_pHitObj->GetWorld()) - GetPositionVector(m_pHitObj->GetWorldOld());
			if (vN.x == 0 && vN.z == 0) {

				vN = m_vHitNormal;

			}
			vN = normalize(vN);
			VECTOR3 vR;
			if (vHear != vHearOld) {

				VECTOR3 vL = normalize(vHear - vHearOld);
				vR = (2 * dot(-vL, vN)*vN) + vL;

			}
			else {

				vR = vN;

			}

			m_mWorld = GetLookatMatrix(vHear, vHear + vR);


			m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生	

		}
		else {
			// マップとのあたり判定
			VECTOR3 vHit, vNormal;

			if (m_pGMain->m_pMapProc->Hitcheck(GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), &vHit, &vNormal))
			{
				VECTOR3 vL = normalize(GetPositionVector(m_mWorld) - GetPositionVector(m_mWorldOld));  // 移動ベクトル（正規化）
				VECTOR3 vN = normalize(vNormal);            // 接触ポリゴンの法線（正規化）
				VECTOR3 vR = (2 * dot(-vL, vN) * vN) + vL;  // 反射ベクトルの公式
				m_mWorldOld = m_mWorld = GetLookatMatrix(vHit, vHit + vR);  // 接触点から反射先を見るマトリックスを作成し、ワールドマトリックスに代入
				m_vGravity.y *= -1;
				m_pGMain->m_pEffectProc->m_pParticleProc->Start(vHit, m_dwPlayerNo, vNormal);	// パーティクルの発生	

			}


		}

		if (m_pGMain->m_pEnmProc->m_pEnmTargetProc->HitcheckOtherLay(this)) {



		}

		switch (m_dwStatus)
		{

		case DAMAGE:
			m_pGMain->m_nScore++;
			UpdateDamage();

			break;
		}
		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_bActive = FALSE;
		}
		m_pBBox->m_mWorld = m_mWorld;

		// レンダリング
		Render();

	}
}
//----------------------------------------------------------------------------
//ボールが当たった時
//----------------------------------------------------------------------------
void CWeaponBallObj::UpdateDamage()
{


	ObjReflection();

	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生



	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
//
// スキル・ボールオブジェクトのレンダリング
//
//   陰影をつけないレンダリング　光の方向が(0,0,0)
//
//     引数　　　なし
//     戻り値　　なし
// ---------------------------------------------------------------------------
void CWeaponBallObj::Render()
{

	// ボールのレンダリング
	//m_pMesh->Render(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	m_pMesh->RenderToon(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	m_pBBox->Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);

}


// ============================================================================================================================
//============================================================================
//
// スキル・手に持つアイテムプロシージャのコンストラクタ
//
// ・直接攻撃するスキルではなく、スキルを表示したり、位置情報を返したりする
//
//   メッシュはプロシージャではなく、オブジェクトで読み込む
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CWeaponHoldProc::CWeaponHoldProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (int i = 0; i < HOLDITEM_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponHoldObj(m_pGMain));	// m_pObjArrayにオブジェクトを生成する
		m_pObjArray[i]->SetObjNo(i);    // オブジェクトＮＯをオブジェクトに設定する
		((CWeaponHoldObj*)m_pObjArray[i])->Init();   // オブジェクトの初期化
	}
}
// ---------------------------------------------------------------------------
//
// スキル・手に持つアイテムプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponHoldProc::~CWeaponHoldProc()
{
	;
}

// ---------------------------------------------------------------------------
//
// スキル・手に持つアイテムプロシージャの情報を得る
//
//     MATRIX4X4  mHold       ：剣の位置
//     BASEHOLDITEM HoldItem  :手に持つスキルの情報
//     MATRIX4X4& mMat        :手に持つスキルのマトリックス(Out)
//     VECTOR3& vMin          :バウンディングボックスのMin(Out)
//     VECTOR3& vMax          :バウンディングボックスのMax(Out)
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
void  CWeaponHoldProc::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax)
{
	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetInfo(mHold, HoldItem, mMat, vMin, vMax);	// スキル・剣オブジェクト

	return;
}
// ---------------------------------------------------------------------------
//
// スキル・手に持つアイテムプロシージャの情報を得る
//
//     MATRIX4X4  mHold       ：剣の位置
//     BASEHOLDITEM HoldItem  :手に持つスキルの情報
//     MATRIX4X4& mMat        :手に持つスキルのマトリックス(Out)
//     VECTOR3& vOffset       :銃口までのオフセット(Out)
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
void  CWeaponHoldProc::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset)
{
	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetInfo(mHold, HoldItem, mMat, vOffset);	// スキル・銃オブジェクト

	return;
}

// ---------------------------------------------------------------------------
//
// スキル・手に持つアイテムプロシージャのバウンディングボックスを得る
//
//     MATRIX4X4  mHold       ：剣の位置
//     BASEHOLDITEM HoldItem  :手に持つスキルの情報
//
//     戻り値　　CBBox* バウンディングボックス
// ---------------------------------------------------------------------------
CBBox*  CWeaponHoldProc::GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{
	return ((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetBBox(mHold, HoldItem);	// スキル・剣オブジェクト
}

// ---------------------------------------------------------------------------
//
// スキル・手に持つアイテムプロシージャの表示
//
//     MATRIX4X4  mHold       ：剣の位置
//     BASEHOLDITEM HoldItem  :手に持つスキルの情報
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
BOOL CWeaponHoldProc::Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem,DWORD dwPlayerNo)
{

	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->Disp(mHold, HoldItem, dwPlayerNo);	// スキル・剣オブジェクト

	return TRUE;
}
//============================================================================
//
// スキル・手に持つアイテムオブジェクトのコンストラクタ
//
// ・直接攻撃するスキルではなく、スキルを表示したり、位置情報を返したりする
//
// ---------------------------------------------------------------------------
CWeaponHoldObj::CWeaponHoldObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_nKindNo = 0;
	m_pMesh = NULL;
	m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // オフセットの設定
}
//============================================================================
//
// スキル・手に持つアイテムオブジェクトの初期化
//
// ・メッシュは、プロシージャではなくオブジェクトの中に設定する
//
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Init()
{

	switch (m_dwObjNo)
	{
	case 0:     // 未設定
		m_nKindNo = 0;
		m_pMesh = NULL; // オブジェクトは無し
		m_pBBox = NULL; // BBoxの設定
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // オフセットなし


	case 3:     // 剣（ソード）メッシュの設定
		m_nKindNo = 1;  // 1:種別　剣
		m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Weapon_Bad.mesh"));
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-1.15f, 0.1f, -0.15f), VECTOR3(1.15f, 1.8f, 1.15f));// BBoxの設定
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // 銃口までのオフセットの設定
		break;

	default:
		m_nKindNo = 0;
		m_pMesh = NULL; // オブジェクトは無し
		m_pBBox = NULL; // BBoxの設定
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // オフセットなし
		break;
	}

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

}
// ---------------------------------------------------------------------------
//
// スキル・手に持つアイテムオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponHoldObj::~CWeaponHoldObj()
{
	SAFE_DELETE(m_pMesh);
}

// ---------------------------------------------------------------------------
//
// スキル・手に持つアイテムオブジェクトの情報を得る
//
//     MATRIX4X4  mHold       ：剣の位置
//     BASEHOLDITEM HoldItem  :手に持つスキルの情報
//     MATRIX4X4& mMat        :手に持つスキルのマトリックス(Out)
//     VECTOR3& vMin          :バウンディングボックスのMin(Out)
//     VECTOR3& vMax          :バウンディングボックスのMax(Out)
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
void  CWeaponHoldObj::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax)
{
	// オフセットマトリックスの計算
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// 
	// ワールドマトリックスの計算
	// 
	// 但し、このときm_mWorldやm_pBBox->m_mWorldの設定は行っていない!!
	// 
	mMat = mOffset * mHold;     // 剣の位置のワールドマトリックス

	vMin = m_pBBox->m_vMin;
	vMax = m_pBBox->m_vMax;

	return;
}

// ---------------------------------------------------------------------------
//
// スキル・手に持つアイテムオブジェクトの情報を得る
//
//     MATRIX4X4  mHold       ：銃の位置
//     BASEHOLDITEM HoldItem  :手に持つスキルの情報
//     MATRIX4X4& mMat        :手に持つスキルのマトリックス(Out)
//     VECTOR3& vOffset       :銃口までのオフセット(Out)
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
void  CWeaponHoldObj::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset)
{
	// オフセットマトリックスの計算
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ワールドマトリックスの計算
	// 
	// 但し、このときm_mWorldの設定は行っていない!!
	// 
	mMat = mOffset * mHold;     // 銃の位置のワールドマトリックス

	vOffset = m_vOffset;

	return;
}

// ---------------------------------------------------------------------------
//
// スキル・手に持つアイテムオブジェクトのバウンディングボックスを得る
//
//     MATRIX4X4  mHold       ：剣の位置
//     BASEHOLDITEM HoldItem  :手に持つスキルの情報
//
//     戻り値　　CBBox* バウンディングボックス
// ---------------------------------------------------------------------------
CBBox* CWeaponHoldObj::GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{

	// オフセットマトリックスの計算
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ワールドマトリックスの計算
	// 
	// 但し、このときm_mWorldとm_pBBox->m_mWorldの設定を行っている!!
	// 
	m_mWorld = mOffset * mHold;     // 剣の位置のワールドマトリックス
	m_pBBox->m_mWorld = m_mWorld;   // バウンディングボックスのワールドマトリックスをセット

	return m_pBBox;

}


// ---------------------------------------------------------------------------
//
// スキル・手に持つアイテムオブジェクトの描画
//
//     MATRIX4X4  mHold        ：アイテムの位置
//     VECTOR3    vPos         :位置のオフセット
//     VECTOR3    vRot         :角度のオフセット
//
//     戻り値　　なし
// ---------------------------------------------------------------------------
BOOL CWeaponHoldObj::Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem,DWORD dwPlayerNo)
{
	m_bActive = TRUE;  // スタート時に表示開始
	m_dwPlayerNo = dwPlayerNo;
	// オフセットマトリックスの計算
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ワールドマトリックスの計算
	m_mWorld = mOffset * mHold;     // 剣の位置のワールドマトリックス
	if (m_pBBox) m_pBBox->m_mWorld = m_mWorld;   // バウンディングボックスのワールドマトリックスをセット

	// レンダリング
	Render();

	m_bActive = FALSE;  // １回処理したら、消す

	return TRUE;
}

// ---------------------------------------------------------------------------
//
// スキル・手に持つアイテムオブジェクトの更新
//
//     引数　　　なし
//     戻り値　　なし
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Update()
{

	//Render()
		;
}
// ---------------------------------------------------------------------------
//
// スキル・手に持つアイテムオブジェクトの描画
//
//     引数　　　なし
//     戻り値　　なし
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Render()
{

	if(m_pMesh&&m_dwPlayerNo== FIRSTPLAYER)	m_pMesh->RenderToon(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	if (m_pMesh&&m_dwPlayerNo == SECONDPLAYER)	m_pMesh->RenderToon(m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);

}




// ================================================================================================================================
//============================================================================
//
// スキル・拡散ボールプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CWeaponDivBallProc::CWeaponDivBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 拡散ボールメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark.mesh"));
	m_dwProcID = WEAPON_DIV;	

	for (int i = 0; i < DIVBALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponDivBallObj(m_pGMain));	// m_pObjArrayにスキル・拡散ボールオブジェクトを生成する
		((CWeaponDivBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // メッシュのアドレスをオブジェクトに設定する
		m_pObjArray[i]->SetObjID(m_dwProcID);		

	}
}
//============================================================================
//
// スキル・拡散ボールプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponDivBallProc::~CWeaponDivBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
//
// スキル・拡散ボールプロシージャの発射
//
//  MATRIX4X4  mGun         ：銃の位置マトリックス
//  VECTOR3    vOffset      ：位置の微調整
//  MATRIX4X4  mOwnerWorld  ：発射するキャラのマトリックス
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
// ---------------------------------------------------------------------------
BOOL CWeaponDivBallProc::Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner)
{
	MATRIX4X4 mLay, mOwnerRot, mOffset;
	BOOL bRet = FALSE;

	DWORD  dwNum;
	dwNum =5;			//出てくる弾の数


	mLay = GetPositionMatrix(mGun);               // 銃の位置(回転を取り除く)
	mOwnerRot = GetRotateMatrix(mOwnerWorld);     // 発射するキャラの回転マトリックスのみ(位置を取り除く)にする
	mLay = mOwnerRot * mLay;                      // 銃の位置から、キャラの方向で発射するマトリックスを作る
	mOffset = XMMatrixTranslation(vOffset.x, vOffset.y + 0.5, vOffset.z);	// 位置の微調整
	mLay = mOffset * mLay;
	for (DWORD n = 0; n < dwNum; n++)
	{
		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				((CWeaponDivBallObj*)(m_pObjArray[i]))->Start(mLay, dwOwner,n,dwNum);	       // スキル・拡散ボールオブジェクトの発射
				bRet = TRUE;
				break;
			}
		}
	}
	return bRet;
}

// ---------------------------------------------------------------------------
//
// スキル・拡散ボールプロシージャの発射
//
//  MATRIX4X4  mGun         ：銃の位置マトリックス
//  VECTOR3    vOffset      ：位置の微調整
//  MATRIX4X4  mOwnerWorld  ：発射するキャラのマトリックス
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
// ---------------------------------------------------------------------------
BOOL CWeaponDivBallProc::Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner, DWORD dwPlayerNo)
{
	MATRIX4X4 mLay, mOwnerRot, mOffset;
	BOOL bRet = FALSE;

	DWORD  dwNum;
	dwNum = 5;			//出てくる弾の数


	mLay = GetPositionMatrix(mGun);               // 銃の位置(回転を取り除く)
	mOwnerRot = GetRotateMatrix(mOwnerWorld);     // 発射するキャラの回転マトリックスのみ(位置を取り除く)にする
	mLay = mOwnerRot * mLay;                      // 銃の位置から、キャラの方向で発射するマトリックスを作る
	mOffset = XMMatrixTranslation(vOffset.x, vOffset.y + 0.5, vOffset.z);	// 位置の微調整
	mLay = mOffset * mLay;
	for (DWORD n = 0; n < dwNum; n++)
	{
		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				((CWeaponDivBallObj*)(m_pObjArray[i]))->SetPlayerNo(dwPlayerNo);
				((CWeaponDivBallObj*)(m_pObjArray[i]))->Start(mLay, dwOwner, n, dwNum);	       // スキル・拡散ボールオブジェクトの発射
				bRet = TRUE;
				break;
			}
		}
	}
	return bRet;
}


//============================================================================
//
// スキル・拡散ボールオブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CWeaponDivBallObj::CWeaponDivBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // 攻撃力

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-0.15f, -0.15f, -0.15f);
	VECTOR3 vMax(0.15f, 0.15f, 0.15f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                       


	TargetProc = m_pGMain->m_pEnmProc->GetProcArrayPtr()[0];

}
// ---------------------------------------------------------------------------
//
// スキル・拡散ボールオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponDivBallObj::~CWeaponDivBallObj()
{
	;
}

// ---------------------------------------------------------------------------
//
// スキル・拡散ボールオブジェクトの発射
//
//     MATRIX4X4 mStartWorld     拡散ボールの発射位置のマトリックス
//     DWORD      dwOwner        スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponDivBallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner,DWORD dwNo,DWORD  dwNum)
{
	const float fSpeed = 0.02f;		// 拡散ボールの速さ
	const int nLifeTime = 300;		// 拡散ボールの持続時間
	if (m_bActive) return FALSE;

	float angle = 0;
	MATRIX4X4 mYaw;  // Ｙ軸回転マトリックス
	float test = 10;
	float Breadth=120.0f; //広さ
	DWORD SaveNum = 0;	//的のIDの保存	
	int	  NumRim = 0;	//残りの的の数	
	m_bFront = FALSE;
	fActivTime = 300;

	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	m_fDivTime = 0;

	m_fDist = 10000000;
	
	TargetProcArr.clear();
	TargetProcArr.shrink_to_fit();

	TargetStatas TS;
	for (DWORD i = 0; i < m_pGMain->m_pEnmProc->GetProcArrayPtr().size(); i++)  // 全ての相手オブジェクト
	{
		if (i != (ENM_BALL_ID - 1) && i != (ENM_BALLBOOM_ID - 1)) {
			TS.Id = m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->GetProcID()-1;
			TargetProcArr.push_back(TS);
		}
	}

	//ターゲットするオブジェクトを検索 
	DWORD RanSarch = Random(0, TargetProcArr.size() - 1);

	for (DWORD i = 0; i < TargetProcArr.size(); i++)  // 全ての相手オブジェクト
	{
		if (LookTarget(m_pGMain->m_pEnmProc->GetProcArrayPtr()[TargetProcArr[RanSarch].Id], m_dwPlayerNo))break;

			RanSarch++;
			if(RanSarch> TargetProcArr.size() - 1)RanSarch = 0;

	}


	m_vPosUp = VECTOR3(0, 0, fSpeed);
	m_nCnt1 = nLifeTime;
	m_dwOwner = dwOwner;
	
	dwNo = dwNo;
	//扇形に弾を出現させる
	angle = Breadth / (dwNum-1);
	if (dwNum == 0) {
		angle = 0;
	}
	else {
		angle = angle * dwNo;
		angle = angle - (Breadth/2);

	}
	mYaw = XMMatrixRotationY(XMConvertToRadians(angle));
	m_mWorld = mYaw * m_mWorld;
	
	
	return TRUE;
}

// ---------------------------------------------------------------------------
//
// 拡散ボールオブジェクトのローカル軸マトリックスを得る関数
//
//  m_mWorldの位置情報とm_fLocalRotYの角度情報を元に
//  ローカル軸マトリックスを返す
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponDivBallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
//
// スキル・拡散ボールオブジェクトの更新
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponDivBallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;
		TargetProc->GetObjArrayPtr()[RanNum]->SetTarget(FALSE);		//的のターゲットトリガーを外す		

		MATRIX4X4 mTran;
		m_vPosUp.z = 0.3;

		if (m_bFront != TRUE) {		
			TargetProc->ObjTarget(this, 10.0f, RanNum);		//ターゲットに向けて弾が向かう
			if (TargetProc->GetObjArrayPtr()[RanNum]->GetActive() != TRUE) m_bFront = TRUE;		//的が壊れたら追従を止める
		}
			
		
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// 自分拡散ボールの位置判定と移動
		VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // 自分の前の位置
		
		m_pGMain->m_pEnmProc->Hitcheck(this, m_pBBox, m_pGMain->m_pEnmProc->m_pEnmBallProc->GetProcID());
		m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->HitcheckMulti(this, m_pBBox,m_dwPlayerNo);
		if (m_pGMain->m_pWeaponProc->m_pWeaponWallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {	
			m_pHitObj->SetStatus(NORMAL);
		}
		if (m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {	
			m_pHitObj->SetStatus(NORMAL);
		}



	// 敵やＰＣとのあたり判定
		if ((m_dwOwner != ENM && m_pGMain->m_pEnmProc->m_pEnmTargetProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo) )||
			(m_dwOwner != PC && m_pGMain->m_pPcProc->HitcheckMulti(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), m_dwPlayerNo)))
		{
			m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生	
			//m_pGMain->m_pSeDead->Play();// 爆発効果音
			//m_bActive = FALSE;

		}
		if (fActivTime < 0) {
			m_bActive = FALSE;

		}


		switch (m_dwStatus)
		{

		case DAMAGE:
			UpdateDamage();
			m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生
			m_bActive = FALSE;

			break;
		}
		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_bActive = FALSE;
		}
		m_pBBox->m_mWorld = m_mWorld;

		// レンダリング
		Render();
		m_fDivTime++;
		fActivTime--;
	}
}
//----------------------------------------------------------------------------
//拡散ボールが当たった時
//----------------------------------------------------------------------------
void CWeaponDivBallObj::UpdateDamage()
{
	m_dwStatus = NORMAL;

}




// ---------------------------------------------------------------------------
// スキル・拡散ボールオブジェクトのレンダリング
//
//   陰影をつけないレンダリング　光の方向が(0,0,0)
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponDivBallObj::Render()
{

	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

}
//-----------------------------------------------------------------------------
//
//ターゲットを見つける処理
//
//
//-----------------------------------------------------------------------------
BOOL CWeaponDivBallObj::LookTarget(CBaseProc* pOtherProc, DWORD dwPlayerNo)
{
	BOOL  bRet = FALSE;

	int	  NumRim = 0;	//残りの的の数	
	DWORD SaveNum = 0;	//的のIDの保存	/

	TargetStatas TS;
	//---------------------------------------------------------- 
	TargetObjArr.clear();
	TargetObjArr.shrink_to_fit();


//残っている的の数
	for (DWORD i = 0; i < pOtherProc->GetObjArrayPtr().size(); i++) {
		if (pOtherProc->GetObjArrayPtr()[i]->GetActive() == TRUE&& dwPlayerNo== pOtherProc->GetObjArrayPtr()[i]->GetPlayerNo())
		{
			NumRim++;
			TS.Id = pOtherProc->GetObjArrayPtr()[i]->GetObjNo();
			TargetObjArr.push_back(TS);

		}
	}

	if (NumRim <= 0) {		//的がないとき
		bRet = FALSE;

	}
	else {
		DWORD RanSetNum = Random(0, TargetObjArr.size() - 1);
		for (DWORD i = 0; i < TargetObjArr.size(); i++) {

			if (pOtherProc->GetObjArrayPtr()[TargetObjArr[RanSetNum].Id]->GetActive() == TRUE) {

					TargetProc = pOtherProc;
					SaveNum = TargetObjArr[RanSetNum].Id;
					bRet = TRUE;

					break;

			}
			RanSetNum++;
			if (RanSetNum > TargetObjArr.size() - 1)RanSetNum = 0;
		}

		for (DWORD i = 0; i < TargetObjArr.size(); i++) {

				if (pOtherProc->GetObjArrayPtr()[TargetObjArr[RanSetNum].Id]->GetActive() == TRUE) {

					if (pOtherProc->GetObjArrayPtr()[TargetObjArr[RanSetNum].Id]->GetTarget() != TRUE) {		//的に向かっていない弾がないとき（的に向かう弾を分ける）
						pOtherProc->GetObjArrayPtr()[TargetObjArr[RanSetNum].Id]->SetTarget(TRUE);
						TargetProc = pOtherProc;
						SaveNum = TargetObjArr[RanSetNum].Id;
						bRet = TRUE;

						break;

					}
				}
				RanSetNum++;
				if(RanSetNum > TargetObjArr.size() - 1)RanSetNum = 0;
			bRet = FALSE;
		}

		RanNum = SaveNum;		//弾のIDを取得（余った弾は的が被る）

	}


	return bRet;

}


// ================================================================================================================================
//============================================================================
// スキル・シールドプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CWeaponShieldProc::CWeaponShieldProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// シールドメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy_Shield.mesh"));

	for (int i = 0; i < SHIELD_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponShieldObj(m_pGMain));	// m_pObjArrayにスキル・シールドオブジェクトを生成する
		((CWeaponShieldObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // メッシュのアドレスをオブジェクトに設定する
		m_pObjArray[i]->SetObjID(m_dwProcID);	

	}
}
//============================================================================
// スキル・シールドプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponShieldProc::~CWeaponShieldProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
// スキル・シールドプロシージャの発射
//
//  MATRIX4X4  mGun         ：銃の位置マトリックス
//  VECTOR3    vOffset      ：位置の微調整
//  MATRIX4X4  mOwnerWorld  ：発射するキャラのマトリックス
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）

// ---------------------------------------------------------------------------
BOOL CWeaponShieldProc::Start(MATRIX4X4 mWorld, DWORD dwOwner)
{
	MATRIX4X4 mLay;

	mLay = mWorld;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner);	       // スキル・シールドオブジェクトの発射
			return TRUE;
		}
	}
	return FALSE;
}

// ---------------------------------------------------------------------------
// スキル・シールドプロシージャの発射
//
//  MATRIX4X4  mGun         ：銃の位置マトリックス
//  VECTOR3    vOffset      ：位置の微調整
//  MATRIX4X4  mOwnerWorld  ：発射するキャラのマトリックス
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）

// ---------------------------------------------------------------------------
BOOL CWeaponShieldProc::Start(MATRIX4X4 mWorld, DWORD dwOwner, DWORD dwPlayerNo)
{
	MATRIX4X4 mLay;

	mLay = mWorld;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner, dwPlayerNo);	       // スキル・シールドオブジェクトの発射
			return TRUE;
		}
	}
	return FALSE;
}


//============================================================================
// スキル・シールドオブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CWeaponShieldObj::CWeaponShieldObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // 攻撃力

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-0.35f, -0.35f, -0.35f);
	VECTOR3 vMax(0.35f, 0.35f, 0.35f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                           


}
// ---------------------------------------------------------------------------
// スキル・シールドオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponShieldObj::~CWeaponShieldObj()
{
	;
}

// ---------------------------------------------------------------------------
// スキル・シールドオブジェクトの発射
//
//     MATRIX4X4 mStartWorld     シールドの発射位置のマトリックス
//     DWORD      dwOwner        スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
//
// ---------------------------------------------------------------------------
BOOL CWeaponShieldObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;

	dTargetNo=m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->GetTargetNo();
	fShieldDist = m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->GetShieldDist();
	return TRUE;
}

// ---------------------------------------------------------------------------
// スキル・シールドオブジェクトの発射
//
//     MATRIX4X4 mStartWorld     シールドの発射位置のマトリックス
//     DWORD      dwOwner        スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
//
// ---------------------------------------------------------------------------
BOOL CWeaponShieldObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner, DWORD dwPlayerNo)
{
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	m_dwPlayerNo = dwPlayerNo;
	dTargetNo = m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->GetTargetNo();
	fShieldDist = m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->GetShieldDist();
	return TRUE;
}


// ---------------------------------------------------------------------------
// シールドオブジェクトのローカル軸マトリックスを得る関数
//
//  m_mWorldの位置情報とm_fLocalRotYの角度情報を元に
//  ローカル軸マトリックスを返す
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponShieldObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
// スキル・シールドオブジェクトの更新
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponShieldObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;
		// 自分シールドの位置判定と移動
		VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // 自分の前の位置

		//シールドを回転させる
		MATRIX4X4 mBaseWorld = m_pGMain->m_pEnmProc->m_pEnmShieldProc->GetObjArrayPtr()[dTargetNo]->GetWorld();
		const float fMoveSpeed = 0.05f;

		m_mWorld = RotTarget(m_mWorld, mBaseWorld, fMoveSpeed, fShieldDist);	
		if (m_pGMain->m_pEnmProc->m_pEnmShieldProc->GetObjArrayPtr()[dTargetNo]->GetActive() == FALSE) {
			m_bActive = FALSE;
		}


		switch (m_dwStatus)
		{

		case DAMAGE:
			UpdateDamage();

			break;
		}
		m_pBBox->m_mWorld = m_mWorld;

		// レンダリング
		Render();

	}
}
//----------------------------------------------------------------------------
//シールドが当たった時
//
//
//----------------------------------------------------------------------------
void CWeaponShieldObj::UpdateDamage()
{

	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生
	//m_pGMain->m_pSeDead->Play();// 爆発効果音
	m_bActive = FALSE;



	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
// スキル・シールドオブジェクトのレンダリング
//
//   陰影をつけないレンダリング　光の方向が(0,0,0)
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponShieldObj::Render()
{

	// シールドのレンダリング
	//m_pMesh->Render(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

	//m_pBBox->Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);

}


// ================================================================================================================================
//============================================================================
// スキル・ビッグボールプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CWeaponBigBallProc::CWeaponBigBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ビッグボールメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark_Pro_Big.mesh"));
	m_dwProcID = WEAPON_BIGBALL;		

	for (int i = 0; i < BIGBALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponBigBallObj(m_pGMain));	// m_pObjArrayにスキル・ビッグボールオブジェクトを生成する
		((CWeaponBigBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // メッシュのアドレスをオブジェクトに設定する
		m_pObjArray[i]->SetObjID(m_dwProcID);	

	}
}
//============================================================================
// スキル・ビッグボールプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponBigBallProc::~CWeaponBigBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
// スキル・ビッグボールプロシージャの発射
//
//  CBaseObj* mMyObj         ：反射させたオブジェクト
//	CBaseObj* mHitObj		:反射するオブジェクト
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
// ---------------------------------------------------------------------------
BOOL CWeaponBigBallProc::Start(CBaseObj* mMyObj,  CBaseObj* mHitObj, DWORD dwOwner)
{
	{

		MATRIX4X4 mLay;
		mLay = ObjReflectionStart(mMyObj, mHitObj);
		VECTOR3 vPos = GetPositionVector(mHitObj->GetWorld());
		MATRIX4X4	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
		mLay = mLay * mWorld;
		for (int i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				m_pObjArray[i]->Start(mLay, dwOwner);	       // スキル・ビッグボールオブジェクトの発射
				return TRUE;
			}
		}
		return FALSE;
	}
}

// ---------------------------------------------------------------------------
// スキル・ビッグボールプロシージャの発射
//
//  CBaseObj* mMyObj         ：反射させたオブジェクト
//	CBaseObj* mHitObj		:反射するオブジェクト
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
// ---------------------------------------------------------------------------
BOOL CWeaponBigBallProc::Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner, DWORD dwPlayerNo)
{
	{

		MATRIX4X4 mLay;
		mLay = ObjReflectionStart(mMyObj, mHitObj);
		VECTOR3 vPos = GetPositionVector(mHitObj->GetWorld());
		MATRIX4X4	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
		mLay = mLay * mWorld;
		for (int i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				m_pObjArray[i]->SetPlayerNo(dwPlayerNo);
				m_pObjArray[i]->Start(mLay, dwOwner);	       // スキル・ビッグボールオブジェクトの発射
				return TRUE;
			}
		}
		return FALSE;
	}
}


//============================================================================
// スキル・ビッグボールオブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CWeaponBigBallObj::CWeaponBigBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // 攻撃力

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-1.0f, -1.0f, -1.0f);
	VECTOR3 vMax(1.0f, 1.0f, 1.0f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                  
	m_vDiffuse = VECTOR4(1, 0, 0, 1);		


}
// ---------------------------------------------------------------------------
// スキル・ビッグボールオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponBigBallObj::~CWeaponBigBallObj()
{
	;
}

// ---------------------------------------------------------------------------
// スキル・ビッグボールオブジェクトの発射
//
//     MATRIX4X4 mStartWorld     ビッグボールの発射位置のマトリックス
//     DWORD      dwOwner        スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponBigBallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	const float fSpeed = 0.1f;		// ビッグボールの速さ
	const int nLifeTime = 300;		// ビッグボールの持続時間
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	m_dDamageCount = 0;
	m_vPosUp = VECTOR3(0, 0, fSpeed);
	m_vGravity = VECTOR3(0, fSpeed, 0);

	m_bDamage = true;

	m_nCnt1 = nLifeTime;
	m_dwOwner = dwOwner;
	return TRUE;
}

// ---------------------------------------------------------------------------
// ビッグボールオブジェクトのローカル軸マトリックスを得る関数
//
//  m_mWorldの位置情報とm_fLocalRotYの角度情報を元に
//  ローカル軸マトリックスを返す
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponBigBallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
// スキル・ビッグボールオブジェクトの更新
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponBigBallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		MATRIX4X4 mTran;
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// 自分ビッグボールの位置判定と移動
		VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // 自分の前の位置

	// 敵やＰＣとのあたり判定
			// マップとのあたり判定
			VECTOR3 vHit, vNormal;

			if (m_pGMain->m_pMapProc->Hitcheck(GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), &vHit, &vNormal))
			{
				m_bActive = FALSE;

			}

			m_pGMain->m_pEnmProc->HitcheckMulti(this, m_pBBox, m_pGMain->m_pEnmProc->m_pEnmBallProc->GetProcID(), m_dwPlayerNo);	
			m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo);	
			if (m_pGMain->m_pWeaponProc->m_pWeaponWallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {	
				m_pHitObj->SetStatus(NORMAL);
			}
			if (m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {		
				m_pHitObj->SetStatus(NORMAL);
			}



		switch (m_dwStatus)
		{

		case DAMAGE:
			m_dDamageCount++;
			UpdateDamage();

			break;
		}
		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_bActive = FALSE;
		}
		m_pBBox->m_mWorld = m_mWorld;

		// レンダリング
		Render();

	}
	m_pMesh->m_vDiffuse = m_vDiffuse;	

}
//----------------------------------------------------------------------------
//ビッグボールが当たった時
//
//
//----------------------------------------------------------------------------
void CWeaponBigBallObj::UpdateDamage()
{


	VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置
	VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // 自分の前の位置

	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生	
	if(m_dDamageCount>1)
	m_bActive = FALSE;


	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
// スキル・ビッグボールオブジェクトのレンダリング
//
//   陰影をつけないレンダリング　光の方向が(0,0,0)
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponBigBallObj::Render()
{

	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

}

// ================================================================================================================================
//============================================================================
// スキル・貫通ボールプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CWeaponPenetBallProc::CWeaponPenetBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 貫通ボールメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Weapon_PenetBall.mesh"));
	m_dwProcID = WEAPON_PENETBALL;	

	for (int i = 0; i < BALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponPenetBallObj(m_pGMain));	// m_pObjArrayにスキル・貫通ボールオブジェクトを生成する
		((CWeaponPenetBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // メッシュのアドレスをオブジェクトに設定する
		m_pObjArray[i]->SetObjID(m_dwProcID);	

	}
}
//============================================================================
// スキル・貫通ボールプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponPenetBallProc::~CWeaponPenetBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
// スキル・貫通ボールプロシージャの発射
//
//  CBaseObj* mMyObj         ：反射させたオブジェクト
//	CBaseObj* mHitObj		:反射するオブジェクト
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
// ---------------------------------------------------------------------------
BOOL CWeaponPenetBallProc::Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner)
{
	{

		MATRIX4X4 mLay;
		mLay = ObjReflectionStart(mMyObj, mHitObj);
		VECTOR3 vPos = GetPositionVector(mHitObj->GetWorld());
		MATRIX4X4	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
		mLay = mLay * mWorld;
		for (int i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				m_pObjArray[i]->Start(mLay, dwOwner);	       // スキル・貫通ボールオブジェクトの発射
				return TRUE;
			}
		}
		return FALSE;
	}
}

// ---------------------------------------------------------------------------
// スキル・貫通ボールプロシージャの発射
//
//  CBaseObj* mMyObj         ：反射させたオブジェクト
//	CBaseObj* mHitObj		:反射するオブジェクト
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
// ---------------------------------------------------------------------------
BOOL CWeaponPenetBallProc::Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner,DWORD dwPlayerNo)
{
	{

		MATRIX4X4 mLay;
		mLay = ObjReflectionStart(mMyObj, mHitObj);
		VECTOR3 vPos = GetPositionVector(mHitObj->GetWorld());
		MATRIX4X4	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
		mLay = mLay * mWorld;
		for (int i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				m_pObjArray[i]->SetPlayerNo(dwPlayerNo);
				m_pObjArray[i]->Start(mLay, dwOwner);	       // スキル・貫通ボールオブジェクトの発射
				return TRUE;
			}
		}
		return FALSE;
	}
}

//============================================================================
// スキル・貫通ボールオブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CWeaponPenetBallObj::CWeaponPenetBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // 攻撃力

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-0.15f, -0.15f, -0.15f);
	VECTOR3 vMax(0.15f, 0.15f, 0.15f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;            
	m_vDiffuse = VECTOR4(1, 1, 1, 1);	


}
// ---------------------------------------------------------------------------
// スキル・貫通ボールオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponPenetBallObj::~CWeaponPenetBallObj()
{
	;
}

// ---------------------------------------------------------------------------
// スキル・貫通ボールオブジェクトの発射
//
//     MATRIX4X4 mStartWorld     貫通ボールの発射位置のマトリックス
//     DWORD      dwOwner        スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponPenetBallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	const float fSpeed = 0.3f;		// 貫通ボールの速さ
	const int nLifeTime = 300;		// 貫通ボールの持続時間
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	MATRIX4X4 mPos = XMMatrixTranslation(0,0,2);
	m_mWorld = mPos * m_mWorld;
	m_mWorldOld = m_mWorld;

	m_vPosUp = VECTOR3(0, 0, fSpeed);
	m_vGravity = VECTOR3(0, fSpeed, 0);

	//m_vPosUp  = VECTOR3(0, fSpeed, fSpeed);
	m_nCnt1 = nLifeTime;
	m_dwOwner = dwOwner;

	return TRUE;
}

// ---------------------------------------------------------------------------
// 貫通ボールオブジェクトのローカル軸マトリックスを得る関数
//
//  m_mWorldの位置情報とm_fLocalRotYの角度情報を元に
//  ローカル軸マトリックスを返す
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponPenetBallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
// スキル・貫通ボールオブジェクトの更新
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponPenetBallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		MATRIX4X4 mTran;
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// 自分貫通ボールの位置判定と移動
		VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // 自分の前の位置

	// 敵やＰＣとのあたり判定
			// マップとのあたり判定
		VECTOR3 vHit, vNormal;

		if (m_pGMain->m_pMapProc->Hitcheck(GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), &vHit, &vNormal))
		{
			m_bActive = FALSE;

		}
		m_pGMain->m_pEnmProc->HitcheckMulti(this, m_pBBox, m_pGMain->m_pEnmProc->m_pEnmBallProc->GetProcID(),m_dwPlayerNo);		
		m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo);	

		switch (m_dwStatus)
		{

		case DAMAGE:
			m_pGMain->m_nScore++;
			UpdateDamage();

			break;
		}
		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_bActive = FALSE;

		}
		m_pBBox->m_mWorld = m_mWorld;

		// レンダリング
		Render();

	}


	m_pMesh->m_vDiffuse = m_vDiffuse;

}
//----------------------------------------------------------------------------
//貫通ボールが当たった時
//
//----------------------------------------------------------------------------
void CWeaponPenetBallObj::UpdateDamage()
{


	VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置
	VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // 自分の前の位置

	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生	

	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
// スキル・貫通ボールオブジェクトのレンダリング
//
//   陰影をつけないレンダリング　光の方向が(0,0,0)
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponPenetBallObj::Render()
{

	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

}

// ================================================================================================================================
//============================================================================
// スキル・回転ボールプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CWeaponRollBallProc::CWeaponRollBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 回転ボールメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark_Pro.mesh"));
	m_dwProcID = WEAPON_ROLLBALL;	

	for (int i = 0; i < BALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponRollBallObj(m_pGMain));	// m_pObjArrayにスキル・回転ボールオブジェクトを生成する
		((CWeaponRollBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // メッシュのアドレスをオブジェクトに設定する
		m_pObjArray[i]->SetObjID(m_dwProcID);

	}
}
//============================================================================
// スキル・回転ボールプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponRollBallProc::~CWeaponRollBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
// スキル・回転ボールプロシージャの発射
//
//  CBaseObj* mMyObj         ：反射させたオブジェクト
//	CBaseObj* mHitObj		:反射するオブジェクト
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
// ---------------------------------------------------------------------------
BOOL CWeaponRollBallProc::Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner)
{
	{

		MATRIX4X4 mLay;
		mLay= ObjReflectionStart(mMyObj, mHitObj);
		VECTOR3 vPos = GetPositionVector(mHitObj->GetWorld());
		MATRIX4X4	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
		mLay = mLay * mWorld;
		for (int i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				m_pObjArray[i]->Start(mLay, dwOwner);	       // スキル・回転ボールオブジェクトの発射
				return TRUE;
			}
		}
		return FALSE;
	}
}

// ---------------------------------------------------------------------------
// スキル・回転ボールプロシージャの発射
//
//  CBaseObj* mMyObj         ：反射させたオブジェクト
//	CBaseObj* mHitObj		:反射するオブジェクト
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
// ---------------------------------------------------------------------------
BOOL CWeaponRollBallProc::Start(CBaseObj* mMyObj, CBaseObj* mHitObj, DWORD dwOwner, DWORD dwPlayerNo)
{
	{

		MATRIX4X4 mLay;
		mLay = ObjReflectionStart(mMyObj, mHitObj);
		VECTOR3 vPos = GetPositionVector(mHitObj->GetWorld());
		MATRIX4X4	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
		mLay = mLay * mWorld;
		for (int i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				m_pObjArray[i]->SetPlayerNo(dwPlayerNo);
				m_pObjArray[i]->Start(mLay, dwOwner);	       // スキル・回転ボールオブジェクトの発射
				return TRUE;
			}
		}
		return FALSE;
	}
}


//============================================================================
// スキル・回転ボールオブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CWeaponRollBallObj::CWeaponRollBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // 攻撃力

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-0.45f, -0.45f, -0.45f);
	VECTOR3 vMax(0.45f, 0.45f, 0.45f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                 
	m_vDiffuse = VECTOR4(0, 0, 1, 1);	


}
// ---------------------------------------------------------------------------
// スキル・回転ボールオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponRollBallObj::~CWeaponRollBallObj()
{
	;
}

// ---------------------------------------------------------------------------
// スキル・回転ボールオブジェクトの発射
//
//     MATRIX4X4 mStartWorld     回転ボールの発射位置のマトリックス
//     DWORD      dwOwner        スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponRollBallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	const float fSpeed = 0.05f;		// 回転ボールの速さ
	const int nLifeTime = 300;		// 回転ボールの持続時間
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	m_vPosUp = VECTOR3(0, 0, fSpeed);
	m_vGravity = VECTOR3(0, fSpeed, 0);

	//m_vPosUp  = VECTOR3(0, fSpeed, fSpeed);
	m_nCnt1 = nLifeTime;
	m_dwOwner = dwOwner;
	return TRUE;
}

// ---------------------------------------------------------------------------
// 回転ボールオブジェクトのローカル軸マトリックスを得る関数
//
//  m_mWorldの位置情報とm_fLocalRotYの角度情報を元に
//  ローカル軸マトリックスを返す
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponRollBallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
// スキル・回転ボールオブジェクトの更新
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponRollBallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		MATRIX4X4 mTran;
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// 自分回転ボールの位置判定と移動
		VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // 自分の前の位置

	// 敵やＰＣとのあたり判定
			// マップとのあたり判定
		VECTOR3 vHit, vNormal;

		if (m_pGMain->m_pMapProc->Hitcheck(GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), &vHit, &vNormal))
		{
			m_bActive = FALSE;

		}
		m_pGMain->m_pEnmProc->m_pEnmBallProc->ObjTerritoryMulti(this, Random(1.0f,5.0f),m_dwPlayerNo);	


		switch (m_dwStatus)
		{

		case DAMAGE:
			UpdateDamage();

			break;
		}
		m_pBBox->m_mWorld = m_mWorld;

		// レンダリング
		Render();

	}
	m_pMesh->m_vDiffuse = m_vDiffuse;		

}
//----------------------------------------------------------------------------
//回転ボールが当たった時
//
//
//----------------------------------------------------------------------------
void CWeaponRollBallObj::UpdateDamage()
{
	VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置
	VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // 自分の前の位置

	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生


	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
// スキル・回転ボールオブジェクトのレンダリング
//
//   陰影をつけないレンダリング　光の方向が(0,0,0)
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponRollBallObj::Render()
{

	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
	}

}


// ================================================================================================================================
//============================================================================
// スキル・壁プロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CWeaponWallProc::CWeaponWallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{

	// 壁メッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Wall.mesh"));
	//m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // コリジョンマップの生成
	m_dwProcID = WEAPON_WALL;		

	for (int i = 0; i < WALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponWallObj(m_pGMain));	// m_pObjArrayにスキル・壁オブジェクトを生成する
		m_pObjArray[i]->SetObjNo(i);
		((CWeaponWallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // メッシュのアドレスをオブジェクトに設定する
		((CWeaponWallObj*)m_pObjArray[i])->SetColMesh(this);  // メッシュのアドレスをオブジェクトに設定する
		m_pObjArray[i]->SetObjID(m_dwProcID);	

	}
}
//============================================================================
// スキル・壁プロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponWallProc::~CWeaponWallProc()
{
	SAFE_DELETE(m_pMesh);
	SAFE_DELETE(m_pColMesh);

}
// ---------------------------------------------------------------------------
// スキル・壁プロシージャの発射
//
//  MATRIX4X4  mGun         ：銃の位置マトリックス
//  VECTOR3    vOffset      ：位置の微調整
//  MATRIX4X4  mOwnerWorld  ：発射するキャラのマトリックス
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）

// ---------------------------------------------------------------------------
BOOL CWeaponWallProc::Start(MATRIX4X4 mWorld, DWORD dwOwner, DWORD dNo)
{

	MATRIX4X4 mLay = mWorld;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner,dNo);	       // スキル・壁オブジェクトの発射

			return TRUE;
		}
	}
	return FALSE;
}

// ---------------------------------------------------------------------------
// スキル・壁プロシージャの発射
//
//  MATRIX4X4  mGun         ：銃の位置マトリックス
//  VECTOR3    vOffset      ：位置の微調整
//  MATRIX4X4  mOwnerWorld  ：発射するキャラのマトリックス
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）

// ---------------------------------------------------------------------------
BOOL CWeaponWallProc::Start(MATRIX4X4 mWorld, DWORD dwOwner, DWORD dNo,DWORD dwPlayerNo)
{

	MATRIX4X4 mLay = mWorld;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->SetPlayerNo(dwPlayerNo);
			m_pObjArray[i]->Start(mLay, dwOwner, dNo);	       // スキル・壁オブジェクトの発射

			return TRUE;
		}
	}
	return FALSE;
}


//============================================================================
// スキル・壁オブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CWeaponWallObj::CWeaponWallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // 攻撃力


	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-2.35f, -7.35f, -0.15f);
	VECTOR3 vMax(2.35f, 3.35f, 0.15f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                        


}


// ---------------------------------------------------------------------------
// スキル・壁オブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponWallObj::~CWeaponWallObj()
{
	SAFE_DELETE(m_pColMesh);
	;
}


// ---------------------------------------------------------------------------  
// 敵Ballオブジェクトのメッシュポインタ設定
//
//  CEnmBallProc* pProc
//
// --------------------------------------------------------------------------
void CWeaponWallObj::SetColMesh(CWeaponWallProc* pProc)
{
	//m_pColMesh = pProc->GetColMesh();					// スキンメッシュのポインタ
	 m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // コリジョンマップの生成
	m_pColMesh->AddFbxLoad(_T("Data/Item/Wall.mesh"), VECTOR3(0.0f, 0.0f, 0.0f));

}

// ---------------------------------------------------------------------------
// スキル・壁オブジェクトの発射
//
//     MATRIX4X4 mStartWorld     壁の発射位置のマトリックス
//     DWORD      dwOwner        スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponWallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner, DWORD dNo)
{
	//const float fSpeed = 0.05f;		// 壁の速さ
	//const int nLifeTime = 300;		// 壁の持続時間

	dDamageNum = 3;
	m_nCnt1 = 120;
	bInvTrigger = FALSE;	
	if (m_bActive) return FALSE;
	MATRIX4X4 mRot;
	m_bActive = TRUE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	bStartTrigget = FALSE;

	VECTOR3 vMin, vMax;
	vMin = VECTOR3(-5.0f, -10.0f, -5.0f);
	vMax = VECTOR3(5.0f, -10.0f, 5.0f);

	dTargetNo = m_pGMain->m_pWeaponProc->m_pWeaponWallProc->GetTargetNo();
	fWallDist = m_pGMain->m_pWeaponProc->m_pWeaponWallProc->GetWallDist();

	//壁を生成する

	m_mWorld = XMMatrixTranslation((float)Random(vMin.x, vMax.x),
		vMax.y, (float)Random(vMin.z,vMax.z));
	mRot = GetRotateMatrix(mStartWorld);
	m_mWorld = mRot * m_mWorld;
	m_pBBox->m_mWorld = m_mWorld;                    

	for (DWORD i = 0; i < m_pGMain->m_pWeaponProc->m_pWeaponWallProc->GetObjArrayPtr().size(); i++) {

		if (i != m_dwObjNo) {
			if (m_pGMain->m_pWeaponProc->m_pWeaponWallProc->GetObjArrayPtr()[i]->GetActive() == TRUE) {		//表示されている壁を探す

				if (m_pBBox->OBBCollisionDetection(m_pGMain->m_pWeaponProc->m_pWeaponWallProc->GetObjArrayPtr()[i]->GetBBox(), &vHit, &vNrm)) {

					m_mWorld = XMMatrixTranslation((float)Random(vMin.x, vMax.x),
						vMax.y, (float)Random(vMin.z, vMax.z));
					mRot = GetRotateMatrix(mStartWorld);
					m_mWorld = mRot * m_mWorld;
					m_pBBox->m_mWorld = m_mWorld;        
					i = 0;

				}

			}

		}

	}
	vDiffuse = VECTOR4(1, 1, 1, 1);

	dUseNo = dNo;

	return TRUE;
}

// ---------------------------------------------------------------------------
// 壁オブジェクトのローカル軸マトリックスを得る関数
//
//  m_mWorldの位置情報とm_fLocalRotYの角度情報を元に
//  ローカル軸マトリックスを返す
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponWallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
// スキル・壁オブジェクトの更新
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponWallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		//vy += 0.01;
		MATRIX4X4 mPos;

		// 自分壁の位置判定と移動
		VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // 自分の前の位置

		//壁を移動
		const float fMoveSpeed = 0.05f;
		if(vHear.y<0){
		mPos = XMMatrixTranslation(0, fMoveSpeed, 0);
		m_mWorld = mPos * m_mWorld;
		StartLE();
		}

		m_pColMesh->SetWorldMatrix(m_mWorld);
		m_pColMesh->m_mWorldOld = m_pColMesh->m_mWorld;

		ObjDisappear();
		InvincibleTime();
		switch (m_dwStatus)
		{

		case DAMAGE:
			UpdateDamage();

			break;
		}
		m_pBBox->m_mWorld = m_mWorld;

		m_pMesh->m_vDiffuse = vDiffuse;		

		// レンダリング
		Render();


	}
}
//----------------------------------------------------------------------------
//当たった時
//
//----------------------------------------------------------------------------
void CWeaponWallObj::UpdateDamage()
{

	if (bInvTrigger != TRUE) {
		bInvTrigger = TRUE;
		dDamageNum--;
		//壊れた時の処理
		if (dDamageNum <= 0) {
			DWORD	dUseNum = m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->GetWeaponUseNum();	//使用オブジェクトの存在できるスキルの数取得

			m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->SetWeaponUseNum(dUseNum + 1);	//使用オブジェクトのスキルの数を増やす	
			m_bActive = FALSE;

		}
		if (m_pGMain->m_pEffectProc->m_pBillProc->GetProcID() == m_pHitObj->GetObjID()) {	
			DWORD	dUseNum = m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->GetWeaponUseNum();	//使用オブジェクトの存在できるスキルの数取得	

			m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->SetWeaponUseNum(dUseNum + 1);	//使用オブジェクトのスキルの数を増やす	
			m_bActive = FALSE;

		}

		bDamageTrigger = FALSE;
		m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生
		//m_pGMain->m_pSeDead->Play();// 爆発効果音


	}
	m_dwStatus = NORMAL;

}

// ---------------------------------------------------------------------------
//
//	擬音の発生
//
// ---------------------------------------------------------------------------
void CWeaponWallObj::StartLE()
{
	VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置

	if (vHear.y > -2.7&&bStartTrigget == FALSE)			//擬音発生処理
	{
		bStartTrigget = TRUE;
		int Dire = Random(0, 1);		//最初に出現する時の位置　左は０　右が１
		for (int i = 0; i < 4; i++) {
			MATRIX4X4	mEffectWorld = m_mWorld;
			float fEffectAddPosX = (Random(0, 9)*0.1);
			float fEffectAddPosY = 1 + (0.5*i);
			if (Dire == 0)  mEffectWorld = XMMatrixTranslation(-2.0 - fEffectAddPosX, 0, 0)*mEffectWorld;
			if (Dire == 1)	mEffectWorld = XMMatrixTranslation(3.0 - fEffectAddPosX, 0, 0)*mEffectWorld;
			VECTOR3	vEffectPos = GetPositionVector(mEffectWorld);
			vEffectPos.y = fEffectAddPosY;
			float fEffectSize = Random(6, 9)*0.1;
			m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), vEffectPos, VECTOR2(fEffectSize, fEffectSize), VECTOR2(320, 0), VECTOR2(64, 64), 120, m_dwPlayerNo, LENO_SHAKERANDOMTYPE,1.0);	

			if (Dire == 0) {
				Dire = 1;
			}
			else if (Dire == 1) {
				Dire = 0;
			}


		}


	}


}

// ---------------------------------------------------------------------------
//
//	無敵時間の処理
//
//
//
// ---------------------------------------------------------------------------
void CWeaponWallObj::InvincibleTime()
{
	//無敵時間の処理
	if (bInvTrigger == TRUE) {
		if (m_nCnt1 < 0) {
			bInvTrigger = FALSE;
			m_nCnt1 = 120;

		}
		else {
			m_nCnt1--;
			if (m_nCnt1 % 2 == 0) {
				vDiffuse = VECTOR4(0, 0, 0, 1);
			}
			else {
				vDiffuse = VECTOR4(1, 1, 1, 1);

			}
		}
	}

}

// ---------------------------------------------------------------------------
//
//	消える条件
//
//
// ---------------------------------------------------------------------------
void CWeaponWallObj::ObjDisappear()
{
	if (m_pGMain->m_pWeaponProc->m_pWeaponPenetBallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {	
		DWORD	dUseNum = m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->GetWeaponUseNum();	//使用オブジェクトの存在できる壁の数取得	
		m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->SetWeaponUseNum(dUseNum + 1);	//使用オブジェクトの壁の数を増やす
		m_bActive = FALSE;
		bDamageTrigger = FALSE;
	}


	if (!m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->GetActive()) {			//使用しているオブジェクトが消えるとこのオブジェクトも消える
		DWORD	dUseNum = m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->GetWeaponUseNum();	//使用オブジェクトの存在できる壁の数取得	
		m_pGMain->m_pEnmProc->m_pEnmWallProc->GetObjArrayPtr()[dUseNo]->SetWeaponUseNum(dUseNum + 1);	//使用オブジェクトの壁の数を増やす
		m_bActive = FALSE;
		bDamageTrigger = FALSE;
	}

}


// ---------------------------------------------------------------------------
// スキル・壁オブジェクトのレンダリング
//
//   陰影をつけないレンダリング　光の方向が(0,0,0)
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponWallObj::Render()
{

	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-200) && vSPos.x <= WINDOW_WIDTH + 200) && (vSPos.y >= (-200) && vSPos.y <= WINDOW_HEIGHT + 200)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-200) && vSPos.x <= WINDOW_WIDTH + 200) && (vSPos.y >= (-200) && vSPos.y <= WINDOW_HEIGHT + 200)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
	}
}


//-----------------------------------------------------------------------------
//
//オブジェクトのレイとメッシュ接触判定用配列との接触判定とスリスリ動かす制御
//	高低差と重力を考慮した、接触判定を行う								
//  
//  MATRIX4X4* pWorld     オブジェクトの現在のマトリックス(in,out)
//  MATRIX4X4  mWorldOld  オブジェクトの一つ前のマトリックス		
//  float fRadius          オブジェクトの半径（省略値は0.2）
//  
//  戻り値　int
//		エラー		= -1
//		面上を移動	= 1
//		着地		= 2
//		落下中		= 3
//-----------------------------------------------------------------------------
int  CWeaponWallProc::isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld,DWORD dwPlayerNo)
{
	int  nRet = 0, nRetMove = 0;

	// 移動マップとの接触判定と移動
	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (((CWeaponWallObj*)m_pObjArray[i])->GetPlayerNo() == dwPlayerNo) {
			if (((CWeaponWallObj*)m_pObjArray[i])->GetColMesh() && ((CWeaponWallObj*)m_pObjArray[i])->GetActive())
			{
				nRetMove = ((CWeaponWallObj*)m_pObjArray[i])->GetColMesh()->isCollisionMoveGravity(*pWorld, mWorldOld);  
				if (nRetMove == 1 || nRetMove == 2) break;   // 移動マップと接触したとき
			}
		}
	}

	if (nRetMove == 1 || nRetMove == 2)  // 移動マップと接触していたとき
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}

//-----------------------------------------------------------------------------
//
//オブジェクトのレイとメッシュ接触判定用配列との接触判定とスリスリ動かす制御
//	高低差と重力を考慮した、接触判定を行う								
//  
//  MATRIX4X4* pWorld     オブジェクトの現在のマトリックス(in,out)
//  MATRIX4X4  mWorldOld  オブジェクトの一つ前のマトリックス		
//  float fRadius          オブジェクトの半径（省略値は0.2）
//  
//  戻り値　int
//		エラー		= -1
//		面上を移動	= 1
//		着地		= 2
//		落下中		= 3
//-----------------------------------------------------------------------------
BOOL  CWeaponWallProc::isBBoxMoveGravity(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld, float fRadius)
{

	BOOL  bRet = FALSE;
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // 全ての相手オブジェクト
	{

		bRet=m_pObjArray[i]->GetBBox()->OBBCollisionLay(vNow, vOld, &vHit, &vNrm);

		if (bRet == TRUE) {
				
			((CWeaponWallObj*)m_pObjArray[i])->isBBoxMoveGravity(pOtherObj, vNow, vOld, vHit, vNrm, fRadius);

			if (bRet) return bRet;

			
		}

	}


	return	bRet;
}

//-----------------------------------------------------------------------------
//
//オブジェクトのレイとメッシュ接触判定用配列との接触判定とスリスリ動かす制御
//	高低差と重力を考慮した、接触判定を行う					
//  
//  MATRIX4X4* pWorld     オブジェクトの現在のマトリックス(in,out)
//  MATRIX4X4  mWorldOld  オブジェクトの一つ前のマトリックス		
//  float fRadius          オブジェクトの半径（省略値は0.2）
//  
//-----------------------------------------------------------------------------
BOOL  CWeaponWallObj::isBBoxMoveGravity(CBaseObj* pOtherObj, VECTOR3 vNow, VECTOR3 vOld, VECTOR3 vHit, VECTOR3 vNrm, float fRadius)
{


	bool HitTrigger;
	float fNowDist=0;
	VECTOR3 vTargetPos;
	VECTOR3 vMove,vDist;
	MATRIX4X4	mHitWorld;

	mHitWorld = pOtherObj->GetWorld();


		vMove = normalize(vNow - vOld);		//移動ベクトル
		vDist = vNrm * dot(-vMove, vNrm);
		fNowDist = magnitude(vDist - vTargetPos);



		vTargetPos = GetPositionVector(pOtherObj->GetWorld());
		fNowDist = magnitude(vHit- vTargetPos);	//接触位置と接触したオブジェクトの位置の距離
		vMove = vNow + vNrm * (-fNowDist + fRadius);	//食い込んでいる距離
		mHitWorld._41 = vMove.x;
		mHitWorld._42 = vMove.y;
		mHitWorld._43 = vMove.z;

		pOtherObj->SetWorld(mHitWorld);




		//-------------------------------------------------------------------
		HitTrigger = m_pBBox->OBBCollisionLay(vNow, vOld, &vHit, &vNrm);

		vTargetPos = GetPositionVector(pOtherObj->GetWorld());
		fNowDist = magnitude(vHit - vTargetPos);	//接触位置と接触したオブジェクトの位置の距離
		vMove = vNow + vNrm * (-fNowDist + fRadius);	//食い込んでいる距離
		mHitWorld._41 = vMove.x;
		mHitWorld._42 = vMove.y;
		mHitWorld._43 = vMove.z;

		pOtherObj->SetWorld(mHitWorld);
	
	


	int nRet = 0;

	m_dwStatus = NORMAL;
	pOtherObj->SetStatus(NORMAL);


	return TRUE;
}

// ================================================================================================================================


//============================================================================
// スキル・曲がるボールプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CWeaponBendBallProc::CWeaponBendBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 曲がるボールメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Weapon_BallBend.mesh"));

	for (int i = 0; i < BENDBALLL_MAX; i++)		
	{
		m_pObjArray.push_back(new CWeaponBendBallObj(m_pGMain));	// m_pObjArrayにスキル・曲がるボールオブジェクトを生成する
		((CWeaponBendBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // メッシュのアドレスをオブジェクトに設定する
		m_pObjArray[i]->SetObjID(m_dwProcID);	

	}
}
//============================================================================
// スキル・曲がるボールプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponBendBallProc::~CWeaponBendBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
// スキル・曲がるボールプロシージャの発射
//
//  MATRIX4X4  mGun         ：銃の位置マトリックス
//  VECTOR3    vOffset      ：位置の微調整
//  MATRIX4X4  mOwnerWorld  ：発射するキャラのマトリックス
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）

// ---------------------------------------------------------------------------
BOOL CWeaponBendBallProc::Start(MATRIX4X4 mWorld, VECTOR3 vSpeed, DWORD	dwTurn,DWORD dwOwner)
{
	MATRIX4X4 mLay;

	mLay = mWorld;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, vSpeed,dwTurn, dwOwner);	       // スキル・曲がるボールオブジェクトの発射
			return TRUE;
		}
	}
	return FALSE;
}

// ---------------------------------------------------------------------------
// スキル・曲がるボールプロシージャの発射
//
//  MATRIX4X4  mGun         ：銃の位置マトリックス
//  VECTOR3    vOffset      ：位置の微調整
//  MATRIX4X4  mOwnerWorld  ：発射するキャラのマトリックス
//  DWORD      dwOwner      ：スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）

// ---------------------------------------------------------------------------
BOOL CWeaponBendBallProc::Start(MATRIX4X4 mWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner,DWORD dwPlayerNo)
{
	MATRIX4X4 mLay;

	mLay = mWorld;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, vSpeed, dwTurn, dwOwner, dwPlayerNo);	       // スキル・曲がるボールオブジェクトの発射
			return TRUE;
		}
	}
	return FALSE;
}


//============================================================================
// スキル・曲がるボールオブジェクトのコンストラクタ
//
// ---------------------------------------------------------------------------
CWeaponBendBallObj::CWeaponBendBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // 攻撃力

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

	VECTOR3 vMin(-0.85f, -0.35f, -0.85f);
	VECTOR3 vMax(0.85f, 0.35f, 0.85f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                         


}
// ---------------------------------------------------------------------------
// スキル・曲がるボールオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponBendBallObj::~CWeaponBendBallObj()
{
	;
}
// ---------------------------------------------------------------------------
// スキル・曲がるボールオブジェクトの発射
//
//     MATRIX4X4 mStartWorld     曲がるボールの発射位置のマトリックス
//     DWORD      dwOwner        スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponBendBallObj::Start(MATRIX4X4 mStartWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner)
{
	//const float fSpeed = 0.05f;		// 曲がるボールの速さ
	//const int nLifeTime = 300;		// 曲がるボールの持続時間
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	dwTurnPos = dwTurn;

	dTargetNo = m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->GetTargetNo();
	fBendBallDist = m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->GetBendBallDist();
	m_dwOwner = dwOwner;
	vRotUp.y = 0;
	dwMoveStatus = START;
	m_vPosUp = vSpeed;
	m_bDamage = FALSE;
	Count = 0;
	m_vDiffuse = VECTOR4(1, 1, 1, 1);
	mStartRot = GetRotateMatrix(m_mWorld);
	if(dwTurnPos==LEFT)
	m_mWorld = XMMatrixRotationZ(XMConvertToRadians(180.0f))*m_mWorld;
	return TRUE;
}

// ---------------------------------------------------------------------------
// スキル・曲がるボールオブジェクトの発射
//
//     MATRIX4X4 mStartWorld     曲がるボールの発射位置のマトリックス
//     DWORD      dwOwner        スキルを発射したキャラ区分（PC:PC(省略値)　ENM:敵）
//
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
BOOL CWeaponBendBallObj::Start(MATRIX4X4 mStartWorld, VECTOR3 vSpeed, DWORD	dwTurn, DWORD dwOwner, DWORD dwPlayerNo)
{
	//const float fSpeed = 0.05f;		// 曲がるボールの速さ
	//const int nLifeTime = 300;		// 曲がるボールの持続時間
	m_dwPlayerNo = dwPlayerNo;
	if (m_bActive) return FALSE;
	m_bActive = TRUE;
	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;
	dwTurnPos = dwTurn;

	dTargetNo = m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->GetTargetNo();
	fBendBallDist = m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->GetBendBallDist();
	m_dwOwner = dwOwner;
	vRotUp.y = 0;
	dwMoveStatus = START;
	m_vPosUp = vSpeed;
	m_bDamage = FALSE;
	Count = 0;
	m_vDiffuse = VECTOR4(1, 1, 1, 1);
	mStartRot = GetRotateMatrix(m_mWorld);
	if (dwTurnPos == LEFT)
		m_mWorld = XMMatrixRotationZ(XMConvertToRadians(180.0f))*m_mWorld;
	return TRUE;
}


// ---------------------------------------------------------------------------
// 曲がるボールオブジェクトのローカル軸マトリックスを得る関数
//
//  m_mWorldの位置情報とm_fLocalRotYの角度情報を元に
//  ローカル軸マトリックスを返す
//
// ---------------------------------------------------------------------------
MATRIX4X4 CWeaponBendBallObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


// ---------------------------------------------------------------------------
// スキル・曲がるボールオブジェクトの更新
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponBendBallObj::Update()
{
	float vy = 0;
	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;
		// 自分曲がるボールの位置判定と移動
		VECTOR3 vHear = GetPositionVector(m_mWorld); // 自分の今いる位置
		VECTOR3 vHearOld = GetPositionVector(m_mWorldOld); // 自分の前の位置

		MATRIX4X4 mTemp;

		BallDirectionStart(dwTurnPos);
		VECTOR3 vHit, vNormal;
		if (m_pGMain->m_pMapProc->Hitcheck(this, &vHit, &vNormal))  // マップコリジョン
		{
			// 壁にぶつかったとき削除する
			ObjBasicDelete();
		}
		

		//壁との当たり判定		
		if (m_pGMain->m_pWeaponProc->m_pWeaponWallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {
			m_pHitObj->SetStatus(NORMAL);
			ObjBasicDelete();
		}


		if (m_bDamage != TRUE) {
			ObjBend();
			if (m_pGMain->m_pEnmProc->m_pEnmBallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo))
			{
					m_pHitObj->SetActive(FALSE);
					m_dwStatus = NORMAL;
					m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生

			}
			if (m_pGMain->m_pWeaponProc->m_pWeaponDivBallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)||m_pGMain->m_pWeaponProc->m_pWeaponBigBallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo))
			{
				m_pHitObj->SetActive(FALSE);
				m_dwStatus = NORMAL;
				m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生

			}

		}
		else {
			m_vPosUp.x = 0;

			DamageRearHitcheck();
		}

		switch (m_dwStatus)
		{

		case DAMAGE:
			UpdateDamage();

			break;
		}
		m_pBBox->m_mWorld = m_mWorld;

		// レンダリング
		Render();
		Count++;
	}
}
//----------------------------------------------------------------------------
//曲がるボールが当たった時
//----------------------------------------------------------------------------
void CWeaponBendBallObj::UpdateDamage()
{

	if (m_bDamage != TRUE) {
		ObjReflection();
		mStartRot = GetRotateMatrix(m_mWorld);
		m_pGMain->m_pEffectProc->m_pShockWaveProc->Start(m_vHitPos, m_dwPlayerNo);	// パーティクルの発生
		m_bDamage = TRUE;
	}

	m_dwStatus = NORMAL;

}

//----------------------------------------------------------------------------
//曲がるボールが回転し続ける
//
//----------------------------------------------------------------------------
void CWeaponBendBallObj::BallDirectionStart(DWORD dwTurnPos)
{
	MATRIX4X4 mTemp;
	VECTOR3 vWorldPos;
	mTemp = XMMatrixRotationY(XMConvertToRadians(-10.0f));	//回転し続ける 
	m_mWorld = mTemp * m_mWorld;
	VECTOR3 m_vBasePosWorld = GetPositionVector(m_mWorld);	//ワールドマトリックスの位置を取得
	MATRIX4X4 m_mRotWorld = GetRotateMatrix(m_mWorld);		//ワールドマトリックスの角度取得
	m_mWorld = XMMatrixTranslation(m_vBasePosWorld.x, m_vBasePosWorld.y, m_vBasePosWorld.z);
	if (dwTurnPos == RIGHT) vWorldPos = GetPositionVector(XMMatrixTranslation(m_vPosUp.x, 0, m_vPosUp.z)*mStartRot*m_mWorld);
	if (dwTurnPos == LEFT) vWorldPos = GetPositionVector(XMMatrixTranslation(-m_vPosUp.x, 0, m_vPosUp.z)*mStartRot*m_mWorld);
	m_mWorld = XMMatrixTranslation(vWorldPos.x, vWorldPos.y, vWorldPos.z);
	m_mWorld = m_mRotWorld * m_mWorld;



}

//----------------------------------------------------------------------------
//曲がるボールの曲がる処理
//
//
//----------------------------------------------------------------------------
void CWeaponBendBallObj::ObjBend()
{
	switch (dwMoveStatus)
	{
	case START:
		m_vPosUp.x -= 0.0003;
		if (m_vPosUp.x < 0)
		{
			dwMoveStatus = INTER;

		}

		break;
	case INTER:
		m_vPosUp.x -= 0.0005;
		m_vPosUp.z += 0.0003;
		if ((m_vPosUp.x*-1) > m_vPosUp.z)
		{
			dwMoveStatus = FINAL;

		}

		break;

	case FINAL:
		//m_vPosUp.x -= 0.0005;
		m_vPosUp.z += 0.0008;

		break;

	default:
		break;

	}


}

//----------------------------------------------------------------------------
//曲がるボールが打ち返したときの処理
//
//
//----------------------------------------------------------------------------
void CWeaponBendBallObj::DamageRearHitcheck()
{
	if (m_bDamage == TRUE) {
		if (m_pGMain->m_pEnmProc->m_pEnmTargetProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {

		}

		if (m_pGMain->m_pEnmProc->m_pEnmMoveTargetProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {
		}

		if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {
		}

		if (m_pGMain->m_pEnmProc->m_pEnmShieldProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {
		}

		if (m_pGMain->m_pEnmProc->m_pEnmWallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {

		}
		if (m_pGMain->m_pEnmProc->m_pEnmBendProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {

		}

	}



}


// ---------------------------------------------------------------------------
// スキル・曲がるボールオブジェクトのレンダリング
//
//   陰影をつけないレンダリング　光の方向が(0,0,0)
//
//     引数　　　なし
//     戻り値　　なし
//
//
// ---------------------------------------------------------------------------
void CWeaponBendBallObj::Render()
{

	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

}
