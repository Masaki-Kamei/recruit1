//=============================================================================
//
//		プレイキャラクターの制御
//																Playchar.cpp
//=============================================================================
#include  "Playchar.h"
#include  "Camera.h"
#include  "BackFore.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"
#include  "Enemy.h"
#include  "Title.h"


//============================================================================
//
// ＰＣプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CPcProc::CPcProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nNum = 3;    // PCの最大出現数
	const int test = 1;

	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Char/PC9/Pc9.mesh"));    // キャラクター
	m_pMesh->LoadAnimation(_T("Data/Char/PC9/PC9_Idle.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/PC9/PC9_Run.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/PC9/PC9_Run.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/PC9/PC9_Hit.anmx"));		
	m_pMesh->LoadAnimation(_T("Data/Char/PC9/PC9_Death.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/PC9/PC9_Hit_Rev.anmx"));		

	m_pMesh->m_fHeightMax = 0.01f;
	m_pMesh->m_iMaxDevide = 16;
	m_nHoldItem.m_nHoldObjNo = 3;	// 手に持つスキルのオブジェ番号(透明なラケット)
	m_nHoldItem.m_nPosMesh = 0;		// ラケットの根元位置のメッシュ番号
	m_nHoldItem.m_nPosBone = 13;	// ラケットの根元位置のボーン番号
	m_nHoldItem.m_nOffsetPos = VECTOR3(0.02f, 0.04f, -0.03f);  // 手に持つスキルの位置オフセット
	m_nHoldItem.m_nOffsetRot = VECTOR3(0.0f, 0.0f, 90.0f);  // 手に持つスキルの角度オフセット


		// -------------------------------------------------------------------------
	m_pObjArray.push_back(new CPcObj(m_pGMain));	// m_pObjArrayにオブジェクトを登録する
	((CPcObj*)m_pObjArray[0])->SetMesh(this);		// メッシュポインタを設定する
	((CPcObj*)m_pObjArray[0])->SetPlayerNo(FIRSTPLAYER);


	if (test == 1)
	{
		m_pMeshSecond = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Char/PC10/Pc10.mesh"));    // キャラクター
		m_pMeshSecond->LoadAnimation(_T("Data/Char/PC10/PC10_Idle.anmx"));
		m_pMeshSecond->LoadAnimation(_T("Data/Char/PC10/PC10_Run.anmx"));
		m_pMeshSecond->LoadAnimation(_T("Data/Char/PC10/PC10_Run.anmx"));
		m_pMeshSecond->LoadAnimation(_T("Data/Char/PC10/PC10_Hit.anmx"));		
		m_pMeshSecond->LoadAnimation(_T("Data/Char/PC10/PC10_Death.anmx"));
		m_pMeshSecond->LoadAnimation(_T("Data/Char/PC10/PC10_Hit_Rev.anmx"));		

		m_pMeshSecond->m_fHeightMax = 0.01f;
		m_pMeshSecond->m_iMaxDevide = 16;
		
		m_pObjArray.push_back(new CPcObj(m_pGMain));	// m_pObjArrayにオブジェクトを登録する
		((CPcObj*)m_pObjArray[1])->SetMeshSecond(this);		// メッシュポインタを設定する
		((CPcObj*)m_pObjArray[1])->SetPlayerNo(SECONDPLAYER);
	}
	m_nPcNum = nNum;
	
}

// ---------------------------------------------------------------------------
//
// ＰＣプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CPcProc::~CPcProc()
{
	SAFE_DELETE(m_pMesh);
	SAFE_DELETE(m_pMeshSecond);

}


//============================================================================
//
// ＰＣオブジェクトのコンストラクタ
//
//  引数
//  CGameMain* pGMain;		// ゲームメインクラスへのポインタ
//
// ---------------------------------------------------------------------------
CPcObj::CPcObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nHP = 1000;    // 体力
	const int nAtc = 50;      // 体の攻撃力

	m_bActive = TRUE;
	m_dwStatus = NORMAL;

	m_fLocalRotY = 0.0f;                 
	m_bSide = TRUE;                      

	m_fSpeed = 0.16f;      // 移動速度     
	m_fRotSpeed = 8.0f;   // 回転速度     
	m_fJumpSpeed = 0.2f;  // ジャンプ速度  
	m_fNormalSpeed = m_fSpeed;

	// バウンディングボックスの設定
	m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.25f, -0.05f, -0.25f), VECTOR3(0.25f, 2.0f, 0.25f));
	m_pBBox->m_mWorld = m_mWorld;                           
	m_nHp = m_nMaxHp = nHP;
	m_nAtc = nAtc;
	bSwordHitTrigger = FALSE;
	dwUseNumSkill = 0;
}
// ---------------------------------------------------------------------------
//
// ＰＣオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CPcObj::~CPcObj()
{
	;
}

// ---------------------------------------------------------------------------
//
// ＰＣオブジェクトのメッシュポインタ設定
//
//  CPcProc* pProc
//
// ---------------------------------------------------------------------------
void CPcObj::SetMesh(CPcProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ
	m_nHoldItem = pProc->GetHoldItem();			// 手に持つスキルの情報を得る 

	//アニメーション初期値
	m_AnimStatus.SetNum(0);
	m_AnimStatus.animFrame = 0;

}
// ---------------------------------------------------------------------------
//
// ＰＣ2オブジェクトのメッシュポインタ設定
//
//  CPcProc* pProc
//
// ---------------------------------------------------------------------------
void CPcObj::SetMeshSecond(CPcProc* pProc)
{
	m_pMesh = pProc->GetMeshSecond();					// スキンメッシュのポインタ
	m_nHoldItem = pProc->GetHoldItem();			// 手に持つスキルの情報を得る  

	//アニメーション初期値
	m_AnimStatus.SetNum(0);
	m_AnimStatus.animFrame = 0;

}

// ---------------------------------------------------------------------------
//
// ＰＣオブジェクトのローカル軸マトリックスを得る関数
//
//  m_mWorldの位置情報とm_fLocalRotYの角度情報を元に
//  ローカル軸マトリックスを返す
//
// ---------------------------------------------------------------------------
MATRIX4X4 CPcObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}


//-----------------------------------------------------------------------------
// ＰＣオブジェクトの更新
//
//　キーボードでＰＣを動かす
//　ＰＣのアニメーション、ジャンプ、自然落下
//　ワールド座標返還、マップとの接触判定
//　ＰＣの攻撃処理を行う
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CPcObj::Update()
{

	// 一つ前の位置を保存
	m_mWorldOld = m_mWorld;
	if (m_bStop != TRUE) {	

		// 各状態に応じた処理
		switch (m_dwStatus) {
		case  FLASH:  // ＰＣがダメージから復帰したときの処理
		case  NORMAL: // ＰＣが通常状態のときの処理
			UpdateNormal();  // ＰＣオブジェクトの更新 通常状態（NORMAL）
			break;

		case  DAMAGE: // ＰＣがダメージ状態のときの処理
			UpdateDamage();  // ＰＣオブジェクトの更新 ダメージ状態（DAMAGE）
			break;

		}
	}
	else if (m_bStop == TRUE) {
		if(m_AnimStatus.animFrame>=m_AnimStatus.endFrame)
		m_AnimStatus.SetNum(0);		//プレイヤーが止まっているときにアニメーション番号をゼロに戻す
	}


	// マップコリジョンと自然落下
	m_fJumpY += (0.5f*GRAVITY*0.00005f)*m_fJumpTime;	// 自然落下
	m_fJumpTime += 1.0f;
	if (m_pGMain->m_pMapSubProc->isCollisionMoveGravity(&m_mWorld, m_mWorldOld) != 3)  // マップコリジョン
	{
		m_fJumpY = 0.0f;  // 自然落下の停止
		m_fJumpTime = 0.0f;
	}
	m_pGMain->m_pWeaponProc->m_pWeaponWallProc->isCollisionMoveGravity(&m_mWorld, m_mWorldOld,m_dwPlayerNo);	

	SpeedUpAft();		// スピードアップ時残像を残す

	if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
	// バウンディングボックス
	m_pBBox->m_mWorld = m_mWorld;


	// 手に持つスキルやアイテムの表示をする     
	if (m_nHoldItem.m_nHoldObjNo != 0) // 手に持つスキルやアイテムがあるとき
	{
		MATRIX4X4 mHold;
		mHold = m_pMesh->GetFrameMatrices(m_AnimStatus, m_mWorld, m_nHoldItem.m_nPosBone, m_nHoldItem.m_nPosMesh);  // 手の位置のボーンマトリックス
		m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->Disp(mHold, m_nHoldItem,m_dwPlayerNo); // アイテム表示
	}

	SkillUpdate();		


}

//-----------------------------------------------------------------------------  
// ＰＣオブジェクトの更新 通常状態（NORMAL）
//
//　キーボードでＰＣを動かす
//　ＰＣのアニメーション、ジャンプ、自然落下
//　ワールド座標返還、マップとの接触判定
//　ＰＣの攻撃処理を行う
//
//
//   引数　なし
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormal()
{
	if (m_dwStatus == FLASH) // ＰＣがダメージから復帰したときの処理
	{
		m_nCnt1--;
		if (m_nCnt1 <= 0) m_dwStatus = NORMAL;
	}
	UpdateNormalMove();      // ＰＣオブジェクトの移動処理
	if(m_pGMain->m_dwGameStatus != GAMEMULTI)UpdateNormalAttack();    // ＰＣオブジェクトの攻撃処理
}
//-----------------------------------------------------------------------------  
// ＰＣオブジェクトの移動処理
//
//　キーボード／マウスでＰＣを動かす
//　ＰＣのアニメーション、ジャンプ、自然落下
//　ワールド座標返還、マップとの接触判定
//
//
//   引数　なし
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormalMove()
{
	CDirectInput* pDI = m_pGMain->m_pDI;

	MATRIX4X4 mYaw;  // ＰＣＹ軸回転マトリックス
	MATRIX4X4 mPos;  // ＰＣ移動マトリックス
	BOOL	  bKeyPush = FALSE;// キーを押したかどうかのチェック
	const float fRotLowSpeed = m_fRotSpeed / 6;   // ローカル軸（Ｙ軸）の回転速度

	// キーボード、マウス、ジョイスティック操作

	// 自然落下の初期値
	mPos = XMMatrixTranslation(0.0f, m_fJumpY, 0.0f);

	// ローカル軸（Ｙ軸）の回転処理  --------------------------------
	if (m_pGMain->m_dwGameStatus != GAMEMULTI) {
		if (pDI->CheckKey(KD_DAT, DIK_RIGHT) || pDI->CheckMouse(KD_DAT, DIM_RIGHT) || pDI->CheckJoy(KD_DAT, DIJ_R)) //	→キー
		{
			m_fLocalRotY += fRotLowSpeed;
			if (m_fLocalRotY >= 360.0f) m_fLocalRotY -= 360.0f;
		}

		if (pDI->CheckKey(KD_DAT, DIK_LEFT) || pDI->CheckMouse(KD_DAT, DIM_LEFT) || pDI->CheckJoy(KD_DAT, DIJ_L)) //	←キー
		{
			m_fLocalRotY -= fRotLowSpeed;
			if (m_fLocalRotY < 0.0f) m_fLocalRotY += 360.0f;
		}
	}

	if(m_dwPlayerNo==FIRSTPLAYER)mPos = UpdateNormalFirstPCMove(mPos);
	if (m_dwPlayerNo == SECONDPLAYER)mPos = UpdateNormalSecondPCMove(mPos);

	if (m_pGMain->m_dwGameStatus == GAMEMULTI) {

		if (m_dwPlayerNo == FIRSTPLAYER)SwingMoveFirst();
		if (m_dwPlayerNo == SECONDPLAYER)SwingMoveSecond();
	}

	// ローカル軸を基準として、ＰＣを移動させるワールドマトリックスを設定
	mYaw = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));
	m_mWorld = mPos * mYaw * GetLocalMatrix();

}

//-----------------------------------------------------------------------------   
// ＰＣオブジェクトの移動処理　キー操作毎の各種移動処理
//
//   引数　DWORD Key キー種別　DirectInputのキーコード
//
//   戻り値  移動マトリックス
//-----------------------------------------------------------------------------
MATRIX4X4 CPcObj::UpdateNormalMoveKeystate(DWORD DIKey)
{
	MATRIX4X4 mPos;
	int WalkOnoCount = 8;	//歩く時の擬音出現時間の間隔
	int WalkOnoPosMin = -1;	//擬音の出現位置の最小値（整数）
	int WalkOnoPosFewMin = 1;	//擬音の出現位置の最小値（少数）
	int WalkOnoPosMax = 1;	//擬音の出現位置の最大値（整数）
	int WalkOnoPosFewMax = 5;	//擬音の出現位置の最大値（少数）
	//擬音のステータス
	VECTOR2 vWalkOnoSize = VECTOR2(0.5, 0.5);	//表示サイズ	
	VECTOR2 vWalkOnoSrcPos = VECTOR2(64, 0);	//パターン位置
	VECTOR2 vWalkOnoSrcSize = VECTOR2(64, 64);	//パターンサイズ
	DWORD dwWalkOnoFreamEnd = 30;				//表示時間

	if (m_AnimStatus.animNum == 0) m_AnimStatus.SetNum(1);
	if (m_AnimStatus.isEnd(1))     m_AnimStatus.SetNum(2);

	//擬音の出現設定
	float fRPosX= Random(WalkOnoPosMin, WalkOnoPosMax);
	fRPosX =(fRPosX* Random(WalkOnoPosFewMin, WalkOnoPosFewMax))/10;
	MATRIX4X4 mDisWorld = XMMatrixTranslation(fRPosX, 0.5, 0)*m_mWorld;
	VECTOR3 vNowPos = GetPositionVector(mDisWorld);
	//擬音の表示
	if(m_AnimStatus.animFrame%WalkOnoCount==0)		m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), vNowPos, vWalkOnoSize, vWalkOnoSrcPos, vWalkOnoSrcSize, dwWalkOnoFreamEnd, m_dwPlayerNo, LENO_EXPANISIONTYPE,1.0);	

	if (m_bSide && DIKey != DIK_W)   // サイドモードで前進以外のとき
	{
		switch (DIKey)
		{
		case DIK_S:    // 後退
			// 方向を変えずに後退
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, -m_fSpeed);
			break;
		case DIK_D:
			// 方向を変えずに右移動
			mPos = XMMatrixTranslation(m_fSpeed, m_fJumpY, 0.0f);
			break;
		case DIK_A:    // 左
			// 方向を変えずに左移動
			mPos = XMMatrixTranslation(-m_fSpeed, m_fJumpY, 0.0f);
			break;
		}
	}
	else {
		// 進行方向に回転してから前進

		// ルートボーンアニメーションを行うかどうかルートアニメーションタイプを確認する
		if (m_pMesh->GetRootAnimType(m_AnimStatus.animNum) == eRootAnimNone)
		{
			// ルートボーンアニメーションを行わず固定の前進移動値
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, m_fSpeed);
		}
		else {
			// ルートボーンアニメーションでの前進移動値
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, 0.0f) * m_pMesh->GetRootAnimUpMatrices(m_AnimStatus);
		}

		// 進行方向に回転する処理
		// ・回転角度はm_vRotUp.yにある。-180～180度
		// ・１回の回転速度はm_fRotSpeed
		if (m_vRotUp.y > 180.0f)  m_vRotUp.y -= 360.0f;
		if (m_vRotUp.y < -180.0f) m_vRotUp.y += 360.0f;

		float fAngle;  // 目標回転角度

			switch (DIKey)
			{
			case DIK_W:    // 前進
				fAngle = 0.0f;
				break;
			case DIK_S:    // 後退
				if (m_vRotUp.y >= 0)  // 最小回転になるように方向を合わせる
				{
					fAngle = 180.0f;
				}
				else {
					fAngle = -180.0f;
				}
				break;
			case DIK_D:    // 右
				fAngle = 90.0f;
				if (m_vRotUp.y == -180.0f) m_vRotUp.y = 180.0f;  // 最小回転になるように方向を合わせる
				break;
			case DIK_A:    // 左
				fAngle = -90.0f;
				if (m_vRotUp.y == 180.0f) m_vRotUp.y = -180.0f;  // 最小回転になるように方向を合わせる
				break;
			}
		if (m_vRotUp.y > fAngle)  // 左回転
		{
			m_vRotUp.y -= m_fRotSpeed;
			if (m_vRotUp.y < fAngle) m_vRotUp.y = fAngle;
		}
		if (m_vRotUp.y < fAngle)  // 右回転
		{
			m_vRotUp.y += m_fRotSpeed;
			if (m_vRotUp.y > fAngle) m_vRotUp.y = fAngle;
		}

	}




	return mPos;
}

//-----------------------------------------------------------------------------  
// ファーストＰＣオブジェクトの移動処理　キー操作
//
//
//   戻り値  移動マトリックス
//-----------------------------------------------------------------------------
MATRIX4X4 CPcObj::UpdateNormalFirstPCMove(MATRIX4X4 mPos)
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	BOOL	  bKeyPush = FALSE;// キーを押したかどうかのチェック
	const float fRotLowSpeed = m_fRotSpeed / 6;   // ローカル軸（Ｙ軸）の回転速度

	if (pDI->CheckKey(KD_DAT, DIK_J)) //	Jキー
	{
		m_fLocalRotY += fRotLowSpeed;
		if (m_fLocalRotY >= 360.0f) m_fLocalRotY -= 360.0f;
	}

	if (pDI->CheckKey(KD_DAT, DIK_G)) //	Gキー
	{
		m_fLocalRotY -= fRotLowSpeed;
		if (m_fLocalRotY < 0.0f) m_fLocalRotY += 360.0f;
	}

	if (m_AnimStatus.animNum != 3 && m_AnimStatus.animNum != 5) {

		if (pDI->CheckKey(KD_DAT, DIK_W)) //	Wキー
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_W);
		}
		// 後退処理
		if (pDI->CheckKey(KD_DAT, DIK_S)) //Sキー
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_S);
		}
			// 右移動処理
		if (pDI->CheckKey(KD_DAT, DIK_D))//Dキー
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_D);
		}
			// 左移動処理
		if (pDI->CheckKey(KD_DAT, DIK_A))//Aキー
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_A);
		}
		
	}

	if (!bKeyPush && m_AnimStatus.animNum != 3 && m_AnimStatus.animNum != 5)  // キーを押していないとき
	{
		m_AnimStatus.SetNum(0);
	}

	return mPos;
}

//-----------------------------------------------------------------------------  
// セカンドＰＣオブジェクトの移動処理　キー操作
//
//
//   戻り値  移動マトリックス
//-----------------------------------------------------------------------------
MATRIX4X4 CPcObj::UpdateNormalSecondPCMove(MATRIX4X4 mPos)
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	BOOL	  bKeyPush = FALSE;// キーを押したかどうかのチェック

	const float fRotLowSpeed = m_fRotSpeed / 6;   // ローカル軸（Ｙ軸）の回転速度


	if (pDI->CheckMouse(KD_DAT, DIM_RIGHT)) //	マウス右移動
	{
		m_fLocalRotY += fRotLowSpeed;
		if (m_fLocalRotY >= 360.0f) m_fLocalRotY -= 360.0f;
	}

	if (pDI->CheckMouse(KD_DAT, DIM_LEFT)) //	マウス左移動
	{
		m_fLocalRotY -= fRotLowSpeed;
		if (m_fLocalRotY < 0.0f) m_fLocalRotY += 360.0f;
	}


	if (m_AnimStatus.animNum != 3 && m_AnimStatus.animNum != 5) {

		if (pDI->CheckKey(KD_DAT, DIK_UP)) //	↑キー
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_W);
		}
		// 後退処理
		if (pDI->CheckKey(KD_DAT, DIK_DOWN)) //↓キー
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_S);
		}
			// 右移動処理
		if (pDI->CheckKey(KD_DAT, DIK_RIGHT))//→キー
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_D);
		}
			// 左移動処理
		if (pDI->CheckKey(KD_DAT, DIK_LEFT))//←キー
		{
			bKeyPush = TRUE;
			mPos = UpdateNormalMoveKeystate(DIK_A);
		}
		
	}

	if (!bKeyPush && m_AnimStatus.animNum != 3 && m_AnimStatus.animNum != 5)  // キーを押していないとき		
	{
		m_AnimStatus.SetNum(0);
	}

	return mPos;
}


//-----------------------------------------------------------------------------  
// ＰＣオブジェクトの攻撃処理
//
//　キーボード／マウスでＰＣの攻撃処理を行う
//
//
//   引数　なし
//
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormalAttack()
{
	CDirectInput* pDI = m_pGMain->m_pDI;

	//-----------------------------------------------
	//スキルのナンバーの設定		
	if (m_pGMain->m_dModeType != SIMPLEMODE)		//メインモードなら	
	{
		if (pDI->CheckKey(KD_TRG, DIK_1)) // 1キー
		{
			SetSkillNo(1);
		}
		if (pDI->CheckKey(KD_TRG, DIK_2)) // 2キー
		{
			SetSkillNo(2);
		}
		if (pDI->CheckKey(KD_TRG, DIK_3)) // 3キー
		{
			SetSkillNo(3);
		}




		//背後を向く
		if (pDI->CheckKey(KD_TRG, DIK_C)) // Cキー
		{
			dwRotTrigger = TRUE;
		}
		if (dwRotTrigger) {
			int MaxRotCount = 5;
			if (dwRotCount < MaxRotCount) {
				m_fLocalRotY += 36;
				dwRotTrigger = TRUE;
				dwRotCount++;
				if (dwRotCount >= MaxRotCount)
				{
					dwRotTrigger = FALSE;
					dwRotCount = 0;
				}
			}
		}

	}

	// ------------------------------------------------------------- 
	// 
	// ・手に持つスキル・ラケットを持っていないとラケット攻撃はできない
		if ( pDI->CheckMouse(KD_TRG, DIM_RBUTTON)) // Zキー
		{
			if (m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetKind(m_nHoldItem) == 1 && m_AnimStatus.animNum != 5) m_AnimStatus.SetNum(3);   // 手に持つアイテム・ラケットを持っているときは、ラケット攻撃の開始
		}
		if (m_AnimStatus.animNum == 3)
		{
			SwingAnimProcess(3);
		}

		if (pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) // 逆打ち	

		{
			if (m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetKind(m_nHoldItem) == 1 && m_AnimStatus.animNum != 3) m_AnimStatus.SetNum(5);   // 手に持つアイテム・ラケットを持っているときは、ラケット攻撃の開始
		}
		if (m_AnimStatus.animNum == 5)
		{
			SwingAnimProcess(5);
		}
	
}
//-----------------------------------------------------------------------------  
//
//	スキル欄を選択
//
//	int		nSkillColumanNo	選択したスキル欄の番号	
//
//
//-----------------------------------------------------------------------------

void	CPcObj::SetSkillNo(const int nSkillColumanNo)
{
	CWeaponSwordObj*	pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr();
	if(m_dwPlayerNo==SECONDPLAYER)pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr();		
	int SkillColumanNo = nSkillColumanNo;		//選択したスキル欄の番号
	int SkillNo = SkillColumanNo - 1;			//選択したスキルの番号


	if (m_nWeaponColuman == SkillColumanNo) {		//スキル欄キャンセル
		m_nWeaponColuman = 0;
		m_nWeaponNo = 0;
	}
	else  if (pWeaponObj->GetWeaponWaitTime(SkillNo)<= 0) {
		m_nWeaponColuman = SkillColumanNo;		//スキル欄を枠付きにする	
		m_nWeaponNo = m_nWeaponColumanNo[SkillNo];		//スキルのナンバーを取得	
		SkillStart(SkillNo);		

	}
	
}

//----------------------------------------------------------------------------- 
//	ファーストプレイヤーがスイングしてる時の処理
//
//
//-----------------------------------------------------------------------------

void	CPcObj::SwingMoveFirst()
{
	CDirectInput* pDI = m_pGMain->m_pDI;

	if (pDI->CheckKey(KD_TRG, DIK_1) && m_dwPlayerNo == FIRSTPLAYER) // 1キー
	{
		SetSkillNo(1);
	}


	if (pDI->CheckKey(KD_TRG, DIK_SPACE)) // Zキー
	{
		if (m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetKind(m_nHoldItem) == 1 && m_AnimStatus.animNum != 5) m_AnimStatus.SetNum(3);   // 手に持つアイテム・ラケットを持っているときは、ラケット攻撃の開始
	}
	if (m_AnimStatus.animNum == 3)
	{
		SwingAnimProcess(3);
	}

	if (pDI->CheckKey(KD_TRG, DIK_LSHIFT)) // 逆打ち		

	{
		if (m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetKind(m_nHoldItem) == 1 && m_AnimStatus.animNum != 3) m_AnimStatus.SetNum(5);   // 手に持つアイテム・ラケットを持っているときは、ラケット攻撃の開始
	}
	if (m_AnimStatus.animNum == 5)
	{
		SwingAnimProcess(5);
	}


}
//----------------------------------------------------------------------------- 
//
//	セカンドプレイヤーがスイングしてる時の処理
//
//
//-----------------------------------------------------------------------------

void	CPcObj::SwingMoveSecond()
{
	CDirectInput* pDI = m_pGMain->m_pDI;

	if (pDI->CheckKey(KD_TRG, DIK_RSHIFT) && m_dwPlayerNo == SECONDPLAYER) // 1キー
	{
		SetSkillNo(1);
	}


	if (pDI->CheckMouse(KD_TRG, DIM_RBUTTON)) // Zキー
	{
		if (m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetKind(m_nHoldItem) == 1 && m_AnimStatus.animNum != 5) m_AnimStatus.SetNum(3);   // 手に持つアイテム・ラケットを持っているときは、ラケット攻撃の開始
	}
	if (m_AnimStatus.animNum == 3)
	{
		SwingAnimProcess(3);
	}

	if (pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) // 逆打ち		

	{
		if (m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetKind(m_nHoldItem) == 1 && m_AnimStatus.animNum != 3) m_AnimStatus.SetNum(5);   // 手に持つアイテム・ラケットを持っているときは、ラケット攻撃の開始
	}
	if (m_AnimStatus.animNum == 5)
	{
		SwingAnimProcess(5);
	}

}


//----------------------------------------------------------------------------- 
//
//	プレイヤーがスイングしてる時の処理
//
//	int		nSwingAnimNo	スイングした時のアニメーション番号	
//
//
//-----------------------------------------------------------------------------

void	CPcObj::SwingAnimProcess(const int nSwingAnimNo)
{

	MATRIX4X4 mSword, mHold;
	VECTOR3 vMin, vMax;
	int SwingAnimNo = nSwingAnimNo;
	VECTOR2 vSwingOnoSize = VECTOR2(2.5, 1.0);		//表示サイズ	
	VECTOR2 vSwingOnoSrcPos = VECTOR2(588, 338);	//パターン位置
	VECTOR2 vSwingOnoSrcSize = VECTOR2(147, 46);	//パターンサイズ
	DWORD dwSwingOnoFreamEnd = 100;					//表示時間


	mHold = m_pMesh->GetFrameMatrices(m_AnimStatus, m_mWorld, m_nHoldItem.m_nPosBone, m_nHoldItem.m_nPosMesh);  // 手の位置のボーンマトリックス
	m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->GetInfo(mHold, m_nHoldItem, mSword, vMin, vMax); // ボーンマトリックスを指定して手に持つアイテム情報を得る
	m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->Start(mSword, vMin, vMax, PC,m_dwPlayerNo);  // ラケット攻撃の開始	
	if (m_AnimStatus.animNum == SwingAnimNo && m_AnimStatus.animFrame >= m_AnimStatus.endFrame - 2)
	{
		m_AnimStatus.SetNum(0);
		MATRIX4X4 mDisWorld = XMMatrixTranslation(-0.5, 2, 0)*m_mWorld;
		VECTOR3 vNowPos = GetPositionVector(mDisWorld);
		if (bSwordHitTrigger == FALSE)m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), vNowPos, vSwingOnoSize, vSwingOnoSrcPos, vSwingOnoSrcSize, dwSwingOnoFreamEnd, m_dwPlayerNo, LENO_RIZETYPE,1.0);
		bSwordHitTrigger = FALSE;

	}

}

//-----------------------------------------------------------------------------   
// ＰＣオブジェクトの更新 ダメージ状態（DAMAGE）
//
//　ダメージを受けたときの処理
//
//
//   引数　なし
//
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateDamage()
{

	MATRIX4X4 mTemp;
	const int nFlashTime = 5;      // 無敵状態の時間
	const float fBlowDis = -0.15f;

	//吹き飛ばされたときの方向
	if (m_AnimStatus.animNum != 4) {
		m_AnimStatus.SetNum(4);
		m_mWorld=TurnTarget(m_mWorld, m_pHitObj->GetWorld());
	}
	if (m_AnimStatus.animFrame < m_AnimStatus.endFrame - 60)
	{
		
		mTemp = XMMatrixTranslation(0, 0, fBlowDis);	// バックする
		m_mWorld = mTemp * m_mWorld;
	}
	m_nHp -= m_pHitObj->GetAtc();	// 攻撃を受けたダメージ
	//吹き飛ばされるアニメーション		
	if (!m_AnimStatus.isEnd(4))
	{
		m_dwStatus = DAMAGE;     // ダメージからの復帰処理を行う

	}
	else {
		m_dwStatus = FLASH;     // ダメージからの復帰処理を行う
		m_AnimStatus.SetNum(0);

	}
}


//-----------------------------------------------------------------------------
//
// スキル発動時
//
// int		nWeaponColumanNo　スキル欄のナンバー
//
//
//-----------------------------------------------------------------------------
BOOL   CPcObj::SkillStart(const int nWeaponColumanNo)
{
	BOOL bRet = FALSE;

	CWeaponSwordObj*	pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr();
	if (m_dwPlayerNo == SECONDPLAYER)pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr();	


	if (m_nWeaponNo == WEAPON_SKILLPCBOOL)
	{
		if (bBoolSkillTrigger == TRUE) {
			m_nWeaponColuman = 0;		//スキル使用時選解除する	
			m_nWeaponNo = 0;

		}

		if (pWeaponObj->GetWeaponWaitTime(nWeaponColumanNo) <= 0)
		{
			if (bBoolSkillTrigger != TRUE&& bSkillActive[nWeaponColumanNo]!=TRUE)	
			{
				bBoolSkillTrigger = TRUE;
				bSkillActive[nWeaponColumanNo] = TRUE;
				nSkillTime[nWeaponColumanNo] = WEAPON_SKILLPCBOOL_TIME;
				m_nWeaponColuman = 0;		//スキル使用時選解除する
				m_nWeaponNo = 0;
				bRet = TRUE;
				dwUseNumSkill++;	

			}
		}

	}

	//周囲の弾を吹き飛ばすスキル	
	if (m_nWeaponNo == WEAPON_SKILLBOUNCE)
	{
		CBaseProc*	BallProc = m_pGMain->m_pEnmProc->m_pEnmBallProc;
		for (DWORD i = 0; i < BallProc->GetObjArrayPtr().size(); i++)
		{
			CBaseObj*	BallObj = BallProc->GetObjArrayPtr()[i];
			if (BallObj->GetPlayerNo() == m_dwPlayerNo) {
				VECTOR3		vPos = GetPositionVector(m_mWorld);
				VECTOR3		vBallPos = GetPositionVector(BallObj->GetWorld());
				float	fDist = magnitude(vBallPos - vPos);
				float   fRange = 10;		//判定距離
				if (fDist < fRange) {		//周囲の弾が判定距離より小さかったら
					if (BallObj->GetDamage() != TRUE)
					{
						MATRIX4X4	BallWorld = BallObj->GetWorld();
						MATRIX4X4	BallRotY = XMMatrixRotationY(XMConvertToRadians(180));
						BallWorld = BallRotY * TurnTarget(BallWorld, m_mWorld);

						BallObj->SetWorld(BallWorld);
						BallObj->SetDamage(TRUE);
						BallObj->SetStatus(DAMAGE);
					}
				}
			}
		}
		pWeaponObj->SetWeaponWaitTime(nWeaponColumanNo, WEAPON_SKILLPCBOOL_WAITTIME);
		pWeaponObj->SetWeaponMaxWaitTime(nWeaponColumanNo, WEAPON_SKILLPCBOOL_WAITTIME);
		m_nWeaponColuman = 0;		//スキル使用時選解除する	
		m_nWeaponNo = 0;
		dwUseNumSkill++;	
		if (m_pGMain->m_dwGameStatus == GAMEMULTI)
		{
			WeaponUseMulti();
		}

	}

	//スピードアップスキル	
	if (m_nWeaponNo == WEAPON_SKILLSPEEDUP)
	{

		if (bSpeedSkillTrigger == TRUE) {
			m_nWeaponColuman = 0;		//スキル使用時選択解除する		
			m_nWeaponNo = 0;

		}

		if (pWeaponObj->GetWeaponWaitTime(nWeaponColumanNo) <= 0)
		{

			if (bSpeedSkillTrigger != TRUE && bSkillActive[nWeaponColumanNo] != TRUE)
			{
				for (int i = 0; i < 4; i++)		//残像初期値の設定
				{
					AfterSta.mWorldOld[i] = m_mWorld;
					AfterSta.SaveFrame[i] = m_AnimStatus.animFrame;
					AfterSta.SaveFrameNo[i] = m_AnimStatus.animNum;
				}
				bSpeedSkillTrigger = TRUE;
				bSkillActive[nWeaponColumanNo] = TRUE;
				nSkillTime[nWeaponColumanNo] = WEAPON_SKILLSPEEDUP_TIME;
				m_nWeaponColuman = 0;		//スキル使用時選解除する	
				m_nWeaponNo = 0;
				m_fSpeed = m_fSpeed * 1.5;
				bRet = TRUE;
				dwUseNumSkill++;	

			}
		}
	}

	return bRet;
}

//-----------------------------------------------------------------------------
//
// スキル情報処理
//
//
//
//
//-----------------------------------------------------------------------------
void  CPcObj::SkillUpdate()
{
	BOOL	bActiveSkill[10] = {FALSE};

	for (int i = 0; i < 3; i++) {
		if (nSkillTime[i] > 0) {

			if (nCount[i] > 60) {
				nSkillTime[i]--;
				nCount[i] = 0;
			}
			else {
				nCount[i]++;
			}
			bActiveSkill[i] = TRUE;
		}
		else if (nSkillTime[i] <= 0) {
			nSkillTime[i] = 0;
			bActiveSkill[i] = FALSE;
		}

		if (bActiveSkill[i] != TRUE)
		{
			SkillTime(i);

		}


	}


}


//-----------------------------------------------------------------------------
//
// スキルクール時間終了時
//
// int		nWeaponColumanNo　スキル欄のナンバー
//
//
//-----------------------------------------------------------------------------
void  CPcObj::SkillTime(const int nWeaponColumanNo)
{
	CWeaponSwordObj*	pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr();
	if (m_dwPlayerNo == SECONDPLAYER)pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr();	



	if (m_nWeaponColumanNo[nWeaponColumanNo] == WEAPON_SKILLPCBOOL)
	{
		if (bBoolSkillTrigger != FALSE && bSkillActive[nWeaponColumanNo] != FALSE)		//発動中
		{
			bBoolSkillTrigger =FALSE;
			bSkillActive[nWeaponColumanNo] = FALSE;
			pWeaponObj->SetWeaponWaitTime(nWeaponColumanNo, WEAPON_SKILLPCBOOL_WAITTIME);
			pWeaponObj->SetWeaponMaxWaitTime(nWeaponColumanNo, WEAPON_SKILLPCBOOL_WAITTIME);
			if(m_pGMain->m_dwGameStatus== GAMEMULTI)WeaponUseMulti();
		}
	}


	if (m_nWeaponColumanNo[nWeaponColumanNo] == WEAPON_SKILLSPEEDUP)
	{
		if ( bSkillActive[nWeaponColumanNo] != FALSE&& bSpeedSkillTrigger != FALSE)		//発動中
		{
			bSkillActive[nWeaponColumanNo] = FALSE;
			bSpeedSkillTrigger = FALSE;
			pWeaponObj->SetWeaponWaitTime(nWeaponColumanNo, WEAPON_SKILLSPEEDUP_WAITTIME);
			pWeaponObj->SetWeaponMaxWaitTime(nWeaponColumanNo, WEAPON_SKILLSPEEDUP_WAITTIME);
			m_fSpeed = m_fNormalSpeed;
			if (m_pGMain->m_dwGameStatus == GAMEMULTI)WeaponUseMulti();

		}
	}

}


//-----------------------------------------------------------------------------
//
// スピードアップ時残像を残す
//
////-----------------------------------------------------------------------------

void	CPcObj::SpeedUpAft()
{
	//スピードアップ時に残像を出す
	if (bSpeedSkillTrigger == TRUE)
	{
		if (nAftTime % 6 == 0 && nAftTime != 0) {
			AfterSta.mWorldOld[nAfterCount] = m_mWorld;
			AfterSta.SaveFrame[nAfterCount] = m_AnimStatus.animFrame;
			AfterSta.SaveFrameNo[nAfterCount] = m_AnimStatus.animNum;
			nAfterCount++;
			if (nAfterCount >= 4)	nAfterCount = 0;
		}
		nAftTime++;
		if(m_dwPlayerNo==FIRSTPLAYER)m_pMesh->RenderAfter(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, AfterSta);
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderAfter(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePt, AfterSta);

	}
	else {
		nAftTime = 0;
		nAfterCount = 0;

	}

}

//-----------------------------------------------------------------------------
//
// 変数初期化
//
//
////-----------------------------------------------------------------------------
void  CPcObj::Init()
{

	m_nWeaponNo=0;	
	m_nWeaponColuman=0;		
	m_nWeaponColumanNo[10] = { 0 };
	SaveEndFrame=0;	
	m_nFrameTrigger=0;	
	bSwordHitTrigger=FALSE;
	m_dwStatus = NORMAL;
	m_AnimStatus.SetNum(0);
	nSkillTime[3] = { 0 };
	nCount[3] = { 0 };
	bSkillActive[3] = { FALSE };
	m_pGMain->m_pEnmProc->m_pEnmBallProc->SetPcBoolSkill(FALSE);

	for (int i = 0; i < 3; i++) {
		bSkillActive[i] = FALSE;

	}
	dwUseNumSkill = 0;		
	m_fSpeed= m_fNormalSpeed;	
	int ArrSize = sizeof(int) / sizeof(m_nWeaponColumanNo[0]);
	for (int i = 0; i < ArrSize; i++)
	{
		m_nWeaponColumanNo[i]=0;
	}

	dwRotCount = 0;
	dwRotTrigger = 0;
}

//-----------------------------------------------------------------------------
//
// マルチモードでスキルを使った時の更新処理
//
////-----------------------------------------------------------------------------
void  CPcObj::WeaponUseMulti()
{
	m_nWeaponColumanNo[0] = 0;
	if (m_dwPlayerNo == FIRSTPLAYER) {
		m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->SetWeaponWaitTime(0, 0);
		m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->SetWeaponMaxWaitTime(0, 0);
	}
	if (m_dwPlayerNo == SECONDPLAYER)
	{
		m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr()->SetWeaponWaitTime(0, 0);
		m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr()->SetWeaponMaxWaitTime(0, 0);
	}

}


