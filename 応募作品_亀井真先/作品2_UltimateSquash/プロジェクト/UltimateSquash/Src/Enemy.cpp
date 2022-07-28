//=============================================================================
//
//		敵キャラクターの処理
//																Enemy.cpp
//=============================================================================
#include  "Enemy.h"
#include  "Playchar.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"
#include  "BackFore.h"


//============================================================================
//
// 敵メインプロシージャのコンストラクタ
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmProc::CEnmProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pGMain = pGMain;

	m_pEnmBallProc = new CEnmBallProc(m_pGMain);					// 敵ボールの生成
	m_pProcArray.push_back(m_pEnmBallProc);							// プロシージャをプロシージャ配列に登録する

	m_pEnmTargetProc = new CEnmTargetProc(m_pGMain);				// 敵的の生成
	m_pProcArray.push_back(m_pEnmTargetProc);						// プロシージャをプロシージャ配列に登録する

	m_pEnmMoveTargetProc = new CEnmMoveTargetProc(m_pGMain);        // 敵動く的の生成
	m_pProcArray.push_back(m_pEnmMoveTargetProc);					// プロシージャをプロシージャ配列に登録する

	m_pEnmShieldProc = new CEnmShieldProc(m_pGMain);				// 敵シールドの生成
	m_pProcArray.push_back(m_pEnmShieldProc);						// プロシージャをプロシージャ配列に登録する

	m_pEnmWallProc = new CEnmWallProc(m_pGMain);					// 敵壁の生成
	m_pProcArray.push_back(m_pEnmWallProc);							// プロシージャをプロシージャ配列に登録する

	m_pEnmBallBoomProc = new CEnmBallBoomProc(m_pGMain);			// 爆弾ボールの生成
	m_pProcArray.push_back(m_pEnmBallBoomProc);						// プロシージャをプロシージャ配列に登録する

	m_pEnmBendProc = new CEnmBendProc(m_pGMain);					// 敵曲がるの生成
	m_pProcArray.push_back(m_pEnmBendProc);							// プロシージャをプロシージャ配列に登録する

	m_pEnmTargetSkillProc = new CEnmTargetSkillProc(m_pGMain);      // 敵的の生成
	m_pProcArray.push_back(m_pEnmTargetSkillProc);					// プロシージャをプロシージャ配列に登録する

}
//============================================================================
// 敵プロシージャの更新
//
//　敵の数を数え、０になったらゲームクリヤーにする
//
//   引数　　　なし
//============================================================================
void	CEnmProc::Update()
{


}
//============================================================================
//
// 全ての敵プロシージャの発生数を初期値にリセットする
// （最大発生数(m_nMaxNum)を発生数m_nNumに設定する
//
// 引数    CBaseProc* pProc  対象とするプロシージャ。省略値はNULL
//                           NULLの時は自プロシージャ
// 戻り値  なし
// ---------------------------------------------------------------------------
void CEnmProc::ResetEnmNum(CBaseProc* pProc)
{
	if (pProc)   // 対象とするプロシージャ
	{
		pProc->SetMaxNum();  // 最大発生数(m_nMaxNum)を発生数m_nNumに設定する

		// 下位のプロシージャを探索していく
		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
		{
			ResetEnmNum(pProc->GetProcArrayPtr()[i]);  // 再帰呼び出し
		}
	}
	else {   // 自プロシージャ
		SetMaxNum();  // 最大発生数(m_nMaxNum)を発生数m_nNumに設定する

		// 下位のプロシージャを探索していく
		for (DWORD i = 0; i < m_pProcArray.size(); i++)
		{
			ResetEnmNum(m_pProcArray[i]);  // 再帰呼び出し
		}
	}
}

//============================================================================
//
// 全ての敵オブジェクトの残っている敵の数を数える処理
// （残っている敵の数とは、まだ発生していない数(m_nNumの値)＋現在生きている数のことである）
//
// 引数    CBaseProc* pProc  対象とするプロシージャ。NULLの時は自プロシージャ。省略値はNULL
//         int        nNum   上位のプロシージャから与えられた敵の数。省略値は0
//
// 戻り値  int 残っている敵の数
// ---------------------------------------------------------------------------
int CEnmProc::CountActiveEnm(CBaseProc* pProc, int nNum)
{

	if (pProc)   // 対象とするプロシージャ
	{
		nNum += pProc->GetNum();									// プロシージャ中に残っている敵の数（まだ発生していない数）
		for (DWORD j = 0; j < pProc->GetObjArrayPtr().size(); j++)
		{
			if (pProc->GetObjArrayPtr()[j]->GetActive()) nNum++;	// オブジェクト中にすでに発生している敵の数（現在生きている数）
		}

		// 下位のプロシージャを探索していく
		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
		{
			nNum = CountActiveEnm(pProc->GetProcArrayPtr()[i], nNum);  // 再帰呼び出し
		}
	}
	else {   // 自プロシージャ
		nNum += GetNum();											// プロシージャ中に残っている敵の数（まだ発生していない数）
		for (DWORD j = 0; j < m_pObjArray.size(); j++)
		{
			if (m_pObjArray[j]->GetActive()) nNum++;				// オブジェクト中にすでに発生している敵の数（現在生きている数）
		}

		// 下位のプロシージャを探索していく
		for (DWORD i = 0; i < m_pProcArray.size(); i++)
		{
			nNum = CountActiveEnm(m_pProcArray[i], nNum);  // 再帰呼び出し
		}
	}

	return nNum;
}

//============================================================================    
//   
//	プロシージャとオブジェクトを探索し、現在生きている全てのオブジェクトの情報を得る
//   
//	引数　	std::vector<CBaseObj*> &ActiveObjArray  :  対象オブジェクトアドレスを設定する配列
//
//	戻り値  なし
//============================================================================
void  CEnmProc::GetActiveEnm(std::vector<CBaseObj*> &ActiveObjArray)
{

	// オブジェクトポインタ配列の探索
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (m_pObjArray[i]->GetActive())  // 現在生きているオブジェクトか
		{
			ActiveObjArray.push_back(m_pObjArray[i]);    // オブジェクトのアドレスを配列に追加する
		}
	}

	// 下位のプロシージャポインタ配列の探索
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		((CEnmProc*)m_pProcArray[i])->GetActiveEnm(ActiveObjArray);      // 下位のプロシージャの処理（再帰処理）
	}
}

//============================================================================   
//   
//	プロシージャとオブジェクトを探索し、現在生きている全てのオブジェクトの情報を得る
//   
//	引数　	std::vector<CBaseObj*> &ActiveObjArray  :  対象オブジェクトアドレスを設定する配列
//
//	戻り値  なし
//============================================================================
void  CEnmProc::GetActiveEnmMulti(std::vector<CBaseObj*> &ActiveObjArray, DWORD dwPlayerNo)
{

	// オブジェクトポインタ配列の探索
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (m_pObjArray[i]->GetPlayerNo() == dwPlayerNo) {
			if (m_pObjArray[i]->GetActive())  // 現在生きているオブジェクトか
			{
				ActiveObjArray.push_back(m_pObjArray[i]);    // オブジェクトのアドレスを配列に追加する
			}
		}
	}

	// 下位のプロシージャポインタ配列の探索
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		((CEnmProc*)m_pProcArray[i])->GetActiveEnmMulti(ActiveObjArray, dwPlayerNo);      // 下位のプロシージャの処理（再帰処理）
	}
}


// =====================================================================================================
// 
// 各敵プロシージャ毎の処理
// 
// =====================================================================================================


//============================================================================   
//
// 敵Ballプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmBallProc::CEnmBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_BALL_WAITMAX;      // 敵が発生するまでの待ち時間
	m_dwProcID = ENM_BALL_ID;                // 敵BallのID
	m_nNum = m_nMaxNum = ENM_BALL_ALLMAX;    // 敵Ballの最大出現数
	m_fSpeed = ENM_BALL_SPEED;
	m_dwKinds = BALL;
	bPcBoolSkill = FALSE;					 //プレイヤー１Pスキのトリガーを解除
	bPcSecBoolSkill = FALSE;				 //プレイヤー２Pスキのトリガーを解除

	// Fbxスキンメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark_Pro.mesh"));   // 弾のスタティックメッシュ
	for (int i = 0; i < (ENM_BALL_MAX * 2); i++)
	{
			m_pObjArray.push_back(new CEnmBallObj(m_pGMain));				// m_pObjArrayにオブジェクトを生成する
			m_pObjArray[i]->SetObjID(m_dwProcID);							//IDの取得
			m_pObjArray[i]->SetObjNo(i);									//No取得
			((CEnmBallObj*)m_pObjArray[i])->SetMesh(this);					// メッシュのアドレスをオブジェクトに設定する  
			if (i < ENM_BALL_MAX)((CEnmBallObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
			else if (i >= ENM_BALL_MAX)((CEnmBallObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);	
	}
	//出現タイムの設定
	m_nWaitTime = m_nMaxwaitTime = nWait;
	m_nWaitTimeSec = nWait;	
	//打ち返されたとき数の初期値
	dwHitNum = 0;
}


//============================================================================   
//
// 敵Ballプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmBallProc::~CEnmBallProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================  
//
// 敵Ballオブジェクトのコンストラクタ
//
//  引数
//  CGameMain* pGMain;		// ゲームメインクラスへのポインタ
//
// ---------------------------------------------------------------------------
CEnmBallObj::CEnmBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{

	// バウンディングボックスの設定
	VECTOR3 vMin(ENM_BALL_BBOX_MIN);
	VECTOR3 vMax(ENM_BALL_BBOX_MAX);

	ObjBasicConstructor(0, 0, vMin, vMax);

	m_vDiffuse = VECTOR4(ENM_BALL_COLOR);
	m_vTarget = GetPositionVector(m_mWorld);

	bPcBoolSkill = FALSE;

}
// ---------------------------------------------------------------------------    
//
// 敵Ballオブジェクトのデストラクタ
//
//   なお、CBBoxのdeleteはCBaseObjのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmBallObj::~CEnmBallObj()
{
	;
}
// ---------------------------------------------------------------------------   
//
// 敵Ballオブジェクトのメッシュポインタ設定
//
//  CEnmBallProc* pProc
//
// ---------------------------------------------------------------------------  
void CEnmBallObj::SetMesh(CEnmBallProc* pProc)
{
	//m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark_Pro.mesh"));				
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ
	m_fSpeed = pProc->GetSpeed();

}

// ---------------------------------------------------------------------------
// 敵Ballプロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmBallProc::Update()
{
	UpdateNav();
}
// ---------------------------------------------------------------------------  
// 敵Ballプロシージャの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmBallProc::UpdateNav()
{

	std::vector<DWORD> Nav;   // 選択ナビマップ

	BOOL	SkillActivity = FALSE;

	//ボールのスキルが発動中		
	// まだ発生できる数の場合のみ発生させる
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			if (m_nWaitTime <= 0)
			{
				// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
				int k = Random(0, Nav.size() - 1);
				int no = Nav[k];
				for (DWORD i = 0; i < ENM_BALL_MAX; i++)
				{
					if (!m_pObjArray[i]->GetActive())
					{
						((CEnmBallObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
						((CEnmBallObj*)m_pObjArray[i])->SetPcBoolSkill(FALSE);
						if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetBoolSkillTrigger() == TRUE)((CEnmBallObj*)m_pObjArray[i])->SetPcBoolSkill(TRUE);	// スキル発動中	
						m_pObjArray[i]->Start();	// 敵を発生させる
						m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
						SetMaxWaitTime();
						break;
					}
				}
			}
		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}



}

// ---------------------------------------------------------------------------   
// 敵Ballプロシージャマルチの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmBallProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);
}

// ---------------------------------------------------------------------------    
// 敵Ballプロシージャマルチの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmBallProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{


	BOOL	SkillActivity = FALSE;
	BOOL	SecSkillActivity = FALSE;

	
	//ボールのスキルが発動中	

	// まだ発生できる数の場合のみ発生させる
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			//プレイヤー１のとき
			if (m_dwPlayerNo == FIRSTPLAYER) {

				if (m_nWaitTime <= 0)
				{
					// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_BALL_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmBallObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
							((CEnmBallObj*)m_pObjArray[i])->SetPcBoolSkill(FALSE);							//スキルを解除
							if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetBoolSkillTrigger() == TRUE)((CEnmBallObj*)m_pObjArray[i])->SetPcBoolSkill(TRUE);	// スキル発動中		
							m_pObjArray[i]->Start();	// 敵を発生させる
							m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
							SetMaxWaitTime();
							break;
						}

					}
				}
			}
			//プレイヤー２のとき
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_nWaitTimeSec <= 0)
				{
					// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = ENM_BALL_MAX; i < (ENM_BALL_MAX * 2); i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmBallObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
							((CEnmBallObj*)m_pObjArray[i])->SetPcBoolSkill(FALSE);							//スキルを解除
							if (m_pGMain->m_pPcProc->GetPcSecObjPtr()->GetBoolSkillTrigger() == TRUE)((CEnmBallObj*)m_pObjArray[i])->SetPcBoolSkill(TRUE);	// スキル発動中		
							m_pObjArray[i]->Start();	// 敵を発生させる
							m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
							SetMaxWaitTimeSec();
							break;

						}

					}
				}
			}
			

		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}



}

// ---------------------------------------------------------------------------
// 敵Ballプロシージャのナビゲーションマップ登録
//
//
// ---------------------------------------------------------------------------
void CEnmBallProc::NavSet()
{

	Nav.clear();
	Nav.shrink_to_fit();
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}


// --------------------------------------------------------------------------- 
//
// 敵Ballオブジェクトの発生
//
//
// ---------------------------------------------------------------------------
BOOL CEnmBallObj::Start()
{

	m_bActive = TRUE;	// 敵Ballオブジェクト
	m_bDamage = FALSE;
	MATRIX4X4 mYaw;
	VECTOR3 m_vTarget;
	const float SkillRanMinPosx = -2;						//スキルが発動したときのランダム最小位置X座標
	const float SkillRanMaxPosx = 2;						//スキルが発動したときのランダム最大位置Y座標
	const float SkillRanMinPosz = 11;						//スキルが発動したときのランダム最小位置Z座標
	const float SkillRanMaxPosz = 13;						//スキルが発動したときのランダム最大位置Z座標
	VECTOR2 vSkillImageSize = VECTOR2(1.5,1.5);				//スキル発動時のエナジーディスクのサイズ
	VECTOR2 vSkillImageSrcPos = VECTOR2(0,0);				//スキル発動時のエナジーディスクパターン位置
	VECTOR2 vSkillImageSrcSize = VECTOR2(400, 400);			//スキル発動時のエナジーディスクパターンのサイズ
	const float SkillImageFreamEnd = 180;					//スキル発動時のエナジーディスクの表示時間

	VECTOR2 vSkillLESize = VECTOR2(2.5,1.0);				//スキル発動時の擬音エフェクトのサイズ
	VECTOR2 vSkillLESrcPos = VECTOR2(294, 384);				//スキル発動時の擬音エフェクトのパターン位置
	VECTOR2 vSkillLESrcSize = VECTOR2(147, 46);				//スキル発動時の擬音エフェクトのパターンサイズ
	const float vSkillLEFreamEnd = 60;						//スキル発動時の擬音エフェクトの表示時間

// ナビゲーションマップに従って発生させる	
	if (bPcBoolSkill != TRUE) {
		ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
		m_vTarget = VECTOR3((float)Random(m_Nav.vMin.x, m_Nav.vMax.x), m_Nav.vMax.y,
			(float)Random(m_Nav.vMin.z, m_Nav.vMax.z));
		m_pBBox->m_mWorld = m_mWorld;                
	}
	else {
		//ボールスキルが発動中なら
		//カメラの方向から出現させる
		VECTOR3	 vPcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
		MATRIX4X4	mStartRot = GetRotateMatrixY(m_pGMain->m_pCameraProc->GetCameraObjPtr()->GetWorld());
		if (m_dwPlayerNo == SECONDPLAYER) {
			vPcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcSecObjPtr()->GetWorld());
			mStartRot = GetRotateMatrixY(m_pGMain->m_pCameraProc->GetCameraSecondObjPtr()->GetWorld());
		}
		MATRIX4X4	mStartPos = XMMatrixTranslation((float)Random(SkillRanMinPosx, SkillRanMaxPosx), m_Nav.vMax.y, (float)Random(SkillRanMinPosz, SkillRanMaxPosz));
		m_mWorld = mStartPos * mStartRot*XMMatrixTranslation(vPcPos.x,0, vPcPos.z);
		m_mWorldOld = m_mWorld;
		m_pBBox->m_mWorld = m_mWorld;                     
		VECTOR3	vPosStart = GetPositionVector(m_mWorld);
		m_pGMain->m_pEffectProc->m_pEnergyDiskProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), this, vPosStart, vSkillImageSize, vSkillImageSrcPos, vSkillImageSrcSize, SkillImageFreamEnd, m_dwPlayerNo, 0);
		vPosStart.y += 1;
		m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), vPosStart, vSkillLESize, vSkillLESrcPos, vSkillLESrcSize, vSkillLEFreamEnd, m_dwPlayerNo,LENO_EXPANISIONTYPE,1.0);	

	}
	m_dwStatus = NORMAL;
	m_dwStatusSub = ATTACKNONE;
	m_dwStatusPhase = 0;



	//プレイヤーの方向を向く
	VECTOR3 vBall = GetPositionVector(m_mWorld);
	VECTOR3 m_vPcTarget;
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	if (m_dwPlayerNo == FIRSTPLAYER)	{
		m_vPcTarget = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetLocalMatrix());
		pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();

	}
	if (m_dwPlayerNo == SECONDPLAYER) { 
		m_vPcTarget = GetPositionVector(m_pGMain->m_pPcProc->GetPcSecObjPtr()->GetLocalMatrix()); 
		pPcObj = m_pGMain->m_pPcProc->GetPcSecObjPtr();

	}
	m_vDiffuse = VECTOR4(1, 1, 1, 1);				
	m_fDist = 0;
	bShaftObjTrigger = FALSE;
	m_vPcTarget = GetPositionVector(pPcObj->GetWorld());
	m_vPcTarget.y = vBall.y;
	m_vRotUp.y = GetTargetRotateVector(m_mWorld, m_vPcTarget).y;
	RotRig(&m_vRotUp.y);
	mYaw = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));
	m_mWorld =  mYaw * m_mWorld ;
	m_pBBox->m_mWorld = m_mWorld;


	return TRUE;

}

//-----------------------------------------------------------------------------   
//
//　キーボードで敵を動かす
//　敵のアニメーション、ジャンプ、自然落下
//　ワールド座標変換、マップとの接触判定
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmBallObj::Update()
{
	if (!m_bActive) return;  // 非表示のときは処理をしない

	// 変数の初期化   ---------------------------------------
	m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // 一つ前の位置

	// ステータスごとの処理  --------------------------------
	switch (m_dwStatus)
	{
	case  FLASH: // 敵がダメージから復帰したときの処理。breakをつけずに次のNORMALを行う。
	case  NORMAL: // 敵が通常状態のときの処理
		UpdateNormal();
		break;

	case  DAMAGE: // 敵がダメージ状態のときの処理
		UpdateDamage();
		break;

	case  DEAD:	// 敵が死亡状態のときの処理
		UpdateDead();
		break;
	}


	if (m_pGMain->m_pMapProc->isCollisionMove(&m_mWorld, m_mWorldOld, m_pBBox->m_vMax.x))  // マップコリジョン
	{
		// 壁にぶつかったとき削除する
		ObjBasicDelete();
	}

	// ボールの削除処理
	// 原点から１００ｍを越えたら削除
	VECTOR3 vNowPos = GetPositionVector(m_mWorld);
	if (vNowPos.x < -100 || vNowPos.x > 100 || vNowPos.y < -100 || vNowPos.y > 100 || vNowPos.z < -100 || vNowPos.z > 100)
	{
		ObjBasicDelete();
	}

	// 描画処理  --------------------------------------------
	m_pMesh->m_vDiffuse = m_vDiffuse;		
	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if(m_dwPlayerNo==FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}
	// バウンディングボックス
	m_pBBox->m_mWorld = m_mWorld;

}

//----------------------------------------------------------------------------- 
// 敵Ballオブジェクトの制御
//
// 敵が通常状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmBallObj::UpdateNormal()
{

	const float fNormalSpeed = 0.07f;                                    // 移動スピード
	MATRIX4X4 mPos;
	DWORD	EnmProcSize = m_pGMain->m_pEnmProc->GetProcArrayPtr().size();
	const float GravityDist = 3.0f;				//判定距離
	const float GravityRotateSpeed = 0.5f;		//方向転換のスピード

	if (m_dwStatus == FLASH)m_dwStatus = NORMAL;

	ConditionsDelete();

	// ステータスごとの処理  -----------------------------------------

	if (bShaftObjTrigger == TRUE) {			//回転ボールの範囲内なら
		m_bDamage = TRUE;
		m_vDiffuse = VECTOR4(0, 255, 255, 1);			
		MATRIX4X4	mWorld = RotTarget(m_mWorld, m_pShaftObj->GetWorld(), fNormalSpeed*1.5, m_fShaftDist);
		m_mWorld = mWorld;
	}
	else {
		mPos = XMMatrixTranslation(0, 0, fNormalSpeed);    // 直進処理のみ
		m_mWorld = mPos * m_mWorld;
	}

	if (m_bDamage == TRUE) {		//ヒット状態の時の処理
		for (int i = 0; i < EnmProcSize; i++) {
			//的に当たった時
			if (m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->GetKinds() == TARGET) {
				if (m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {
					ObjBasicDelete();
				}
				//ボールの角度の補正
				if (bShaftObjTrigger != TRUE) {
					if (m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->GetProcID() == ENM_TARGETSKILL_ID)
					{
						m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->ObjGravityMulti(this, GravityDist + 2, GravityRotateSpeed, m_dwPlayerNo);
					}
					else
						m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->ObjGravityMulti(this, GravityDist, GravityRotateSpeed, m_dwPlayerNo);
				}
			}
		}

	}


}

//-----------------------------------------------------------------------------    
// 敵Ballオブジェクトの制御
//
// 敵がダメージ状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmBallObj::UpdateDamage()
{
	if (m_bDamage != TRUE) {
		if (m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetProcID() == m_pHitObj->GetObjID()) {

			ObjReflection();
			m_bDamage = TRUE;
			m_pGMain->m_pEffectProc->m_pShockWaveProc->Start(m_vHitPos,m_dwPlayerNo);	// パーティクルの発生

			m_pGMain->m_pEnmProc->m_pEnmBallProc->AddHitNum(1);	
		}
	}
	m_vDiffuse = VECTOR4(1, 0, 0, 1);		

	//アニメーショントリガーに応じて角度を変える	
	m_dwStatus = NORMAL;


}
//----------------------------------------------------------------------------- 
// 敵Ballオブジェクトの制御
//
// 敵が死亡状態のときの処理
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmBallObj::UpdateDead()
{
	ObjBasicDelete();
}
//----------------------------------------------------------------------------- 
// 敵Ballオブジェクトの制御
//
// 削除の条件
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmBallObj::ConditionsDelete()
{
	//壁との当たり判定
	if (m_pGMain->m_pWeaponProc->m_pWeaponWallProc->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {

		m_pHitObj->SetStatus(NORMAL);
		ObjBasicDelete();
		m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生
	}

	//爆風に当たるとボールを消す
	if (m_pGMain->m_pEffectProc->m_pBillProc->Hitcheck(this, m_pBBox)) {
		if (m_pHitObj->GetDamage() != TRUE) {
			ObjBasicDelete();
		}
		else {
			m_dwStatus = NORMAL;
		}
	}

}


//============================================================================    
//
// 敵的プロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmTargetProc::CEnmTargetProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_TARGET_WAITMAX;                   // 敵が発生するまでの待ち時間
	m_dwProcID = ENM_TARGET_ID;                // 敵的のID
	m_nNum = m_nMaxNum = ENM_TARGET_ALLMAX;    // 敵的の最大出現数
	m_dwKinds = TARGET;

	// Fbxスキンメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy_Target.mesh"));   // 弾のスタティックメッシュ
	
	for (int i = 0; i < (ENM_TARGET_MAX*2); i++)
	{
			m_pObjArray.push_back(new CEnmTargetObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
			m_pObjArray[i]->SetObjID(m_dwProcID);
			m_pObjArray[i]->SetObjNo(i);
			((CEnmTargetObj*)m_pObjArray[i])->SetMesh(this);  // メッシュのアドレスをオブジェクトに設定する 
			if (i < ENM_TARGET_MAX)((CEnmTargetObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
			else if (i >= ENM_TARGET_MAX)((CEnmTargetObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);

	}


	m_dwBreakNum = 0;
	m_nWaitTime = m_nMaxwaitTime = nWait;
	m_nWaitTimeSec = nWait;	
	
}



//============================================================================   
//
// 敵的プロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmTargetProc::~CEnmTargetProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================  
//
// 敵的オブジェクトのコンストラクタ
//
//  引数
//  CGameMain* pGMain;		// ゲームメインクラスへのポインタ
//
// ---------------------------------------------------------------------------
CEnmTargetObj::CEnmTargetObj(CGameMain* pGMain) : CBaseObj(pGMain)
{

	m_dwScorePoint = ENM_TARGET_POINT;

	// バウンディングボックスの設定
	VECTOR3 vMin(ENM_TARGET_BBOX_MIN);
	VECTOR3 vMax(ENM_TARGET_BBOX_MAX);
	ObjBasicConstructor(0, 0, vMin, vMax);

	m_vTarget = GetPositionVector(m_mWorld);

}
// ---------------------------------------------------------------------------  
//
// 敵的オブジェクトのデストラクタ
//
//   なお、CBBoxのdeleteはCBaseObjのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmTargetObj::~CEnmTargetObj()
{
	;
}
// ---------------------------------------------------------------------------   
//
// 敵的オブジェクトのメッシュポインタ設定
//
//  CEnmTargetProc* pProc
//
// ---------------------------------------------------------------------------  
void CEnmTargetObj::SetMesh(CEnmTargetProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ
}

// ---------------------------------------------------------------------------  
//
// 敵的プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmTargetProc::Update()
{
	UpdateNav();
}

// ---------------------------------------------------------------------------   
// 敵的プロシージャの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmTargetProc::UpdateNav()
{
	std::vector<DWORD> Nav;   // 選択ナビマップ



	// まだ発生できる数の場合のみ発生させる
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			if (m_nWaitTime <= 0)
			{
				// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
				int k = Random(0, Nav.size() - 1);
				int no = Nav[k];
				for (DWORD i = 0; i < ENM_TARGET_MAX; i++)
				{
					if (!m_pObjArray[i]->GetActive())
					{
						((CEnmTargetObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
						m_pObjArray[i]->Start();	// 敵を発生させる
						m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
						SetMaxWaitTime();
						break;
					}
				}
			}
		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}

}

// ---------------------------------------------------------------------------  
//
// 敵的プロシージャマルチの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmTargetProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);
}


// ---------------------------------------------------------------------------   
// 敵的プロシージャマルチの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmTargetProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{

	// まだ発生できる数の場合のみ発生させる
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			if (m_dwPlayerNo == FIRSTPLAYER) {

				if (m_nWaitTime <= 0)
				{
					// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_TARGET_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmTargetObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
							m_pObjArray[i]->Start();	// 敵を発生させる
							m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
							SetMaxWaitTime();
							break;

						}

					}
				}
			}
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_nWaitTimeSec <= 0)
				{
					// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = ENM_TARGET_MAX; i < (ENM_TARGET_MAX * 2); i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmTargetObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
							m_pObjArray[i]->Start();	// 敵を発生させる
							m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
							SetMaxWaitTimeSec();
							break;

						}

					}
				}
			}

		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}



}

// ---------------------------------------------------------------------------    
// 敵的プロシージャのナビゲーションマップ登録
//
//
// ---------------------------------------------------------------------------
void CEnmTargetProc::NavSet()
{

	Nav.clear();
	Nav.shrink_to_fit();

	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}


// ---------------------------------------------------------------------------   
//
// 敵的オブジェクトの発生
//
//
// ---------------------------------------------------------------------------
BOOL CEnmTargetObj::Start()
{
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	bTarget = FALSE;	

	// ナビゲーションマップに出現	
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
	m_pBBox->m_mWorld = m_mWorld;                       

	// 的の位置が被らないようにする		

	for (DWORD i = 0; i < m_pGMain->m_pEnmProc->m_pEnmTargetProc->GetObjArrayPtr().size(); i++) {

		if (m_pGMain->m_pEnmProc->m_pEnmTargetProc->GetObjArrayPtr()[i]->GetActive() == TRUE) {		//表示されている的を探す
			if (m_pGMain->m_pEnmProc->m_pEnmTargetProc->GetObjArrayPtr()[i]->GetPlayerNo() == m_dwPlayerNo) {

				if (m_pBBox->OBBCollisionDetection(m_pGMain->m_pEnmProc->m_pEnmTargetProc->GetObjArrayPtr()[i]->GetBBox(), &vHit, &vNrm)) {

						ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
						m_pBBox->m_mWorld = m_mWorld;                        
						i = 0;

				}
			}
		}	

	}

	//--的固定用
	MATRIX4X4 mTran;
	ObjAppearanceDirection(m_Nav.dPosStatus, &m_mWorld);
	m_mWorldOld = m_mWorld;
	m_pBBox->m_mWorld = m_mWorld;   

	m_bActive = TRUE;	// 敵的オブジェクト
	m_nHp = m_nMaxHp;



	return TRUE;

}

//-----------------------------------------------------------------------------   
// 敵的オブジェクトの制御
//
//　キーボードで敵を動かす
//　敵のアニメーション、ジャンプ、自然落下
//　ワールド座標変換、マップとの接触判定
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmTargetObj::Update()
{
	if (!m_bActive) return;  // 非表示のときは処理をしない

	// 変数の初期化   ---------------------------------------
	m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // 一つ前の位置

	// ステータスごとの処理  --------------------------------
	switch (m_dwStatus)
	{
	case  FLASH: // 敵がダメージから復帰したときの処理。breakをつけずに次のNORMALを行う。
	case  NORMAL: // 敵が通常状態のときの処理
		UpdateNormal();
		break;

	case  DAMAGE: // 敵がダメージ状態のときの処理
		UpdateDamage();
		if(m_dwPlayerNo==FIRSTPLAYER)m_pGMain->m_nScore= m_pGMain->m_nScore + m_dwScorePoint;
		if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_nScoreSec = m_pGMain->m_nScoreSec + m_dwScorePoint;

		break;

	case  DEAD:	// 敵が死亡状態のときの処理
		UpdateDead();
		break;
	}


	// 描画処理  ---------------------------------------------
	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
	}


	// バウンディングボックス
	m_pBBox->m_mWorld = m_mWorld;

}

//-----------------------------------------------------------------------------    
// 敵的オブジェクトの制御
//
// 敵が通常状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmTargetObj::UpdateNormal()
{


}

//-----------------------------------------------------------------------------    
// 敵的オブジェクトの制御
//
// 敵がダメージ状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmTargetObj::UpdateDamage()
{
	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生
	m_dwStatus = DEAD;		// HPが０なので死亡へ


}
//-----------------------------------------------------------------------------   
// 敵的オブジェクトの制御
//
// 敵が死亡状態のときの処理
//
//   引数　　　なし
//
//-----------------------------------------------------------------------------
void	CEnmTargetObj::UpdateDead()
{
	ObjBasicDelete();
	if(m_dwPlayerNo==FIRSTPLAYER)m_pGMain->m_pEnmProc->m_pEnmTargetProc->SetMaxWaitTime();
	if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_pEnmProc->m_pEnmTargetProc->SetMaxWaitTimeSec();
	m_pGMain->m_pEnmProc->m_pEnmTargetProc->AddBreakNum(1);		

}

//============================================================================   
//
//  敵動く的プロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmMoveTargetProc::CEnmMoveTargetProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_MOVETARGET_WAITMAX;                   // 敵が発生するまでの待ち時間
	m_dwProcID = ENM_MOVETARGET_ID;                //  敵動く的のID
	m_nNum = m_nMaxNum =  ENM_MOVETARGET_ALLMAX;    //  敵動く的の最大出現数
	m_dwKinds = TARGET;

	// Fbxスキンメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy_Target_Ver2.mesh"));   // 弾のスタティックメッシュ

	for (int i = 0; i < (ENM_MOVETARGET_MAX*2); i++)
	{
			m_pObjArray.push_back(new CEnmMoveTargetObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
			m_pObjArray[i]->SetObjID(m_dwProcID);
			m_pObjArray[i]->SetObjNo(i);
			((CEnmMoveTargetObj*)m_pObjArray[i])->SetMesh(this);  // メッシュのアドレスをオブジェクトに設定する 
			if (i < ENM_MOVETARGET_MAX)((CEnmMoveTargetObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
			else if (i >= ENM_MOVETARGET_MAX)((CEnmMoveTargetObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);

	}

	m_nWaitTime = m_nMaxwaitTime = nWait;
	m_nWaitTimeSec = nWait;		

	m_dwBreakNum = 0;

}



//============================================================================  
//
//  敵動く的プロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmMoveTargetProc::~CEnmMoveTargetProc()
{
	SAFE_DELETE(m_pMesh);
}

//============================================================================  
//
// 敵動く的オブジェクトのコンストラクタ
//
//  引数
//  CGameMain* pGMain;		// ゲームメインクラスへのポインタ
//
// ---------------------------------------------------------------------------
CEnmMoveTargetObj::CEnmMoveTargetObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_dwScorePoint = ENM_MOVETARGET_POINT;

	// バウンディングボックスの設定
	VECTOR3 vMin(ENM_MOVETARGET_BBOX_MIN);
	VECTOR3 vMax(ENM_MOVETARGET_BBOX_MAX);
	ObjBasicConstructor(0, 0, vMin, vMax);
	m_vTarget = GetPositionVector(m_mWorld);

}

// ---------------------------------------------------------------------------   
//
// 敵動く的オブジェクトのデストラクタ
//
//   なお、CBBoxのdeleteはCBaseObjのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmMoveTargetObj::~CEnmMoveTargetObj()
{
	;
}
// ---------------------------------------------------------------------------   
//
// 敵動く的オブジェクトのメッシュポインタ設定
//
//  CEnmMoveTargetProc* pProc
//
// --------------------------------------------------------------------------- 
void CEnmMoveTargetObj::SetMesh(CEnmMoveTargetProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ
}

// ---------------------------------------------------------------------------  
// 敵動く的プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmMoveTargetProc::Update()
{
	UpdateNav();

}


// ---------------------------------------------------------------------------   
//
//  敵動く的プロシージャの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmMoveTargetProc::UpdateNav()
{
	std::vector<DWORD> Nav;   // 選択ナビマップ

	// まだ発生できる数の場合のみ発生させる
	if ( m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			if (m_nWaitTime <= 0)
			{
				// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
				int k = Random(0, Nav.size() - 1);
				int no = Nav[k];
				for (DWORD i = 0; i < ENM_MOVETARGET_MAX; i++)
				{
					if (!m_pObjArray[i]->GetActive())
					{
						((CEnmMoveTargetObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
						m_pObjArray[i]->Start();	// 敵を発生させる
						m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
						SetMaxWaitTime();
						break;
					}
				}
			}
		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}

}

// ---------------------------------------------------------------------------   
// 敵動く的プロシージャマルチの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmMoveTargetProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);

}

// ---------------------------------------------------------------------------  
// 敵動く的プロシージャマルチの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmMoveTargetProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{

	// まだ発生できる数の場合のみ発生させる
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			if (m_dwPlayerNo == FIRSTPLAYER) {
				if (m_nWaitTime <= 0)
				{
					// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_MOVETARGET_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmMoveTargetObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
							m_pObjArray[i]->Start();	// 敵を発生させる
							m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
							SetMaxWaitTime();
							break;

						}

					}
				}
			}
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_nWaitTimeSec <= 0)
				{
					// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = ENM_MOVETARGET_MAX; i < (ENM_MOVETARGET_MAX * 2); i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmMoveTargetObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
							m_pObjArray[i]->Start();	// 敵を発生させる
							m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
							SetMaxWaitTimeSec();
							break;

						}

					}
				}
			}

		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}



}

// ---------------------------------------------------------------------------  
// 敵動く的プロシージャのナビゲーションマップ登録
//
//
// ---------------------------------------------------------------------------
void CEnmMoveTargetProc::NavSet()
{

	Nav.clear();
	Nav.shrink_to_fit();

	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}



// ---------------------------------------------------------------------------  
//
// 敵動く的オブジェクトの発生
//
//
// ---------------------------------------------------------------------------
BOOL CEnmMoveTargetObj::Start()
{
	int	Ran = Random(0, 3);
	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);

	m_fLocalRotY = 0.0;

	int RanNum = Random(0, 1);
	if(RanNum==0)
	fMoveSpeed = ENM_MOVETARGET_SPEED;
	else
	fMoveSpeed = -ENM_MOVETARGET_SPEED;

	// ナビゲーションマップに出現	
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
	m_pBBox->m_mWorld = m_mWorld;                         

	VECTOR3 vTarget =VECTOR3(0,0,0);
	VECTOR3 vMyobj = GetPositionVector(m_mWorld);

	fDist = magnitude(vTarget - vMyobj);

	m_bActive = TRUE;	// 敵動く的オブジェクト

	m_nHp = m_nMaxHp;

	return TRUE;

}

//-----------------------------------------------------------------------------   
// 敵動く的オブジェクトの制御
//
//　キーボードで敵を動かす
//　敵のアニメーション、ジャンプ、自然落下
//　ワールド座標変換、マップとの接触判定
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmMoveTargetObj::Update()
{
	if (!m_bActive) return;  // 非表示のときは処理をしない

	// 変数の初期化   ---------------------------------------
	m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // 一つ前の位置

	// ステータスごとの処理  --------------------------------
	switch (m_dwStatus)
	{
	case  FLASH: // 敵がダメージから復帰したときの処理。breakをつけずに次のNORMALを行う。
	case  NORMAL: // 敵が通常状態のときの処理
		UpdateNormal();
		break;

	case  DAMAGE: // 敵がダメージ状態のときの処理
		UpdateDamage();
		if (m_dwPlayerNo == FIRSTPLAYER)m_pGMain->m_nScore = m_pGMain->m_nScore + m_dwScorePoint;
		if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_nScoreSec = m_pGMain->m_nScoreSec + m_dwScorePoint;
		break;

	case  DEAD:	// 敵が死亡状態のときの処理
		UpdateDead();
		break;
	}



	// 描画処理  ---------------------------------------------
	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

	// バウンディングボックス
	m_pBBox->m_mWorld = m_mWorld;

}

//-----------------------------------------------------------------------------   
// 敵動く的オブジェクトの制御
//
// 敵が通常状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmMoveTargetObj::UpdateNormal()
{

	MATRIX4X4 mPos;
	MATRIX4X4 mTemp;
	if (m_dwStatus == FLASH)m_dwStatus = NORMAL;

	// マップの周りを回るように設定----------------------------------------------------------------	
	VECTOR3 m_vBasePosWorld = GetPositionVector(m_mWorld);	//ワールドマトリックスの位置を取得
	MATRIX4X4 m_mRotWorld = GetRotateMatrix(m_mWorld);		//ワールドマトリックスの角度取得

		m_mWorld = XMMatrixTranslation(m_vBasePosWorld.x, m_vBasePosWorld.y, m_vBasePosWorld.z);
		MATRIX4X4 mBaseWorld = XMMatrixTranslation(0, 0, 0);
		m_mWorld = TurnTarget(m_mWorld, mBaseWorld);
		mPos = XMMatrixTranslation(fMoveSpeed, 0, 0);
		m_mWorld = mPos * m_mWorld;
		m_mWorld = TurnTarget(m_mWorld, mBaseWorld);	
		MATRIX4X4 m_mShaftRot = GetRotateMatrix(m_mWorld);		//ワールドマトリックスの角度取得
		mPos = XMMatrixTranslation(0, m_vBasePosWorld.y, -fDist);
		m_mWorld = mPos * m_mShaftRot*mBaseWorld;



}

//-----------------------------------------------------------------------------   
// 敵動く的オブジェクトの制御
//
// 敵がダメージ状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmMoveTargetObj::UpdateDamage()
{
	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生
	m_dwStatus = DEAD;
}
//-----------------------------------------------------------------------------    
// 敵動く的オブジェクトの制御
//
// 敵が死亡状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmMoveTargetObj::UpdateDead()
{
	ObjBasicDelete();
	if(m_dwPlayerNo==FIRSTPLAYER)m_pGMain->m_pEnmProc->m_pEnmMoveTargetProc->SetMaxWaitTime();
	if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_pEnmProc->m_pEnmMoveTargetProc->SetMaxWaitTimeSec();

	m_pGMain->m_pEnmProc->m_pEnmMoveTargetProc->AddBreakNum(1);	



}


//============================================================================    
// 敵シールドプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmShieldProc::CEnmShieldProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_SHIELDT_WAITMAX;                   // 敵が発生するまでの待ち時間
	m_dwProcID = ENM_SHIELD_ID;                // 敵的のID
	m_nNum = m_nMaxNum = ENM_SHIELD_ALLMAX;    // 敵的の最大出現数
	m_dwKinds = TARGET;



	// Fbxスキンメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy1.mesh"));   // 弾のスタティックメッシュ

	for (int i = 0; i < ENM_SHIELD_MAX*2; i++)
	{
		m_pObjArray.push_back(new CEnmShieldObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
		m_pObjArray[i]->SetObjID(m_dwProcID);
		m_pObjArray[i]->SetObjNo(i);
		((CEnmShieldObj*)m_pObjArray[i])->SetMesh(this);  // メッシュのアドレスをオブジェクトに設定する 
		((CEnmShieldObj*)m_pObjArray[i])->SetArryNo(i);
		if (i < ENM_SHIELD_MAX)((CEnmShieldObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
		else if (i >= ENM_SHIELD_MAX)((CEnmShieldObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);


	}

	m_nWaitTime = m_nMaxwaitTime = nWait;


}



//============================================================================    
// 敵シールドプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmShieldProc::~CEnmShieldProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================    
//
// 敵シールドオブジェクトのコンストラクタ
//
//  引数
//  CGameMain* pGMain;		// ゲームメインクラスへのポインタ
//
// ---------------------------------------------------------------------------
CEnmShieldObj::CEnmShieldObj(CGameMain* pGMain) : CBaseObj(pGMain)
{

	m_dwScorePoint = ENM_SHIELD_POINT;

	// バウンディングボックスの設定
	VECTOR3 vMin(ENM_SHIELD_BBOX_MIN);
	VECTOR3 vMax(ENM_SHIELD_BBOX_MAX);
	ObjBasicConstructor(0, 0, vMin, vMax);
	m_vTarget = GetPositionVector(m_mWorld);

}
// ---------------------------------------------------------------------------   
// 敵シールドオブジェクトのデストラクタ
//
//   なお、CBBoxのdeleteはCBaseObjのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmShieldObj::~CEnmShieldObj()
{
	;
}
// ---------------------------------------------------------------------------  
// 敵シールドオブジェクトのメッシュポインタ設定
//
//  CEnmShieldProc* pProc
//
// ---------------------------------------------------------------------------  
void CEnmShieldObj::SetMesh(CEnmShieldProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ
}

// ---------------------------------------------------------------------------    
//
// 敵シールドプロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmShieldProc::Update()
{
	UpdateNav();
}

// ---------------------------------------------------------------------------   
//
//  敵シールドプロシージャの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmShieldProc::UpdateNav()
{
	std::vector<DWORD> Nav;   // 選択ナビマップ

	// まだ発生できる数の場合のみ発生させる
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			if (m_pGMain->m_nScore > ENM_SHIELD_STARTPOINT) {		//出現するためのスコア

				if (m_nWaitTime <= 0)
				{
					// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_SHIELD_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmShieldObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
							m_pObjArray[i]->Start();	// 敵を発生させる
							m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
							SetMaxWaitTime();
							break;
						}
					}
				}
			}
		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}

}

// ---------------------------------------------------------------------------  
// 敵シールドプロシージャマルチの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmShieldProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);

}

// ---------------------------------------------------------------------------    
// 敵シールドプロシージャマルチの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmShieldProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{
	// まだ発生できる数の場合のみ発生させる
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			if (m_dwPlayerNo == FIRSTPLAYER) {

				if (m_pGMain->m_nScore > ENM_SHIELD_STARTPOINT) {		//出現するためのスコア

					if (m_nWaitTime <= 0)
					{
						// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = 0; i < ENM_SHIELD_MAX; i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmShieldObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
								m_pObjArray[i]->Start();	// 敵を発生させる
								m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
								SetMaxWaitTime();
								break;

							}

						}
					}
				}
			}
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_pGMain->m_nScoreSec > ENM_SHIELD_STARTPOINT) {		//出現するためのスコア

					if (m_nWaitTimeSec <= 0)
					{
						// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = ENM_SHIELD_MAX; i < (ENM_SHIELD_MAX * 2); i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmShieldObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
								m_pObjArray[i]->Start();	// 敵を発生させる
								m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
								SetMaxWaitTimeSec();
								break;

							}

						}
					}
				}
			}

		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}



}

// ---------------------------------------------------------------------------  
// 敵シールドプロシージャのナビゲーションマップ登録
//
//
// ---------------------------------------------------------------------------
void CEnmShieldProc::NavSet()
{

	Nav.clear();
	Nav.shrink_to_fit();

	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}



// ---------------------------------------------------------------------------    
// 敵シールドオブジェクトの発生
//
//
// ---------------------------------------------------------------------------
BOOL CEnmShieldObj::Start()
{
	int	Ran = Random(0, 3);

	bTarget = FALSE;	

	// ナビゲーションマップに出現	
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);


	//出現位置に応じて角度を変える	
	ObjAppearanceDirection(m_Nav.dPosStatus, &m_mWorld);

	m_pBBox->m_mWorld = m_mWorld;                        

	ShieldAppearance(m_mWorld);



	m_bActive = TRUE;	// 敵シールドオブジェクト
	fNormalSpeed = 0.05f;
	m_vPosUp.x = fNormalSpeed;
	m_nHp = m_nMaxHp;
	return TRUE;

}

// ---------------------------------------------------------------------------  
// 敵シールドオブジェクトの発生
//
//	MATRIX4X4	mWorld		ワールドマトリックス
//
//
// ---------------------------------------------------------------------------
void CEnmShieldObj::ShieldAppearance(MATRIX4X4 mWorld)
{

	DWORD ShieldNum = 0;
	const float ShieldDist = 1.5f;		//シールドとの距離
	const float ShieldPos = -1.5f;
	for (DWORD i = 0; i < 4; i++)
	{
		MATRIX4X4 ShieldWorld;
		//シールドを出現させる
		switch (ShieldNum)
		{
		case 0:
			ShieldWorld = XMMatrixTranslation(0, 0, ShieldPos)*m_mWorld;
			ShieldNum++;
			break;
		case 1:
			ShieldWorld = XMMatrixRotationY(XMConvertToRadians(270.0f))* XMMatrixTranslation(ShieldDist, 0, 0)*m_mWorld;
			ShieldNum++;
			break;
		case 2:
			ShieldWorld = XMMatrixRotationY(XMConvertToRadians(180.0f))*XMMatrixTranslation(0, 0, ShieldDist)*m_mWorld;
			ShieldNum++;
			break;
		case 3:
			ShieldWorld = XMMatrixRotationY(XMConvertToRadians(90.0f))* XMMatrixTranslation(-ShieldDist, 0, 0)*m_mWorld;
			ShieldNum++;
			break;
		}
		m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->SetTargetNo(m_dwObjNo);
		m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->SetShieldDist(ShieldDist);
		m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Start(ShieldWorld, ENM,m_dwPlayerNo);		
	}

}


//-----------------------------------------------------------------------------   
// 敵シールドオブジェクトの制御
//　キーボードで敵を動かす
//　敵のアニメーション、ジャンプ、自然落下
//　ワールド座標変換、マップとの接触判定
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmShieldObj::Update()
{
	if (!m_bActive) return;  // 非表示のときは処理をしない
		// 変数の初期化   ---------------------------------------
		m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
		m_mWorldOld = m_mWorld;  // 一つ前の位置

		// ステータスごとの処理  --------------------------------
		switch (m_dwStatus)
		{
		case  FLASH: // 敵がダメージから復帰したときの処理。breakをつけずに次のNORMALを行う。
		case  NORMAL: // 敵が通常状態のときの処理
			UpdateNormal();
			break;

		case  DAMAGE: // 敵がダメージ状態のときの処理
			UpdateDamage();
			if (m_dwPlayerNo == FIRSTPLAYER)m_pGMain->m_nScore = m_pGMain->m_nScore + m_dwScorePoint;
			if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_nScoreSec = m_pGMain->m_nScoreSec + m_dwScorePoint;
			break;

		case  DEAD:	// 敵が死亡状態のときの処理
			UpdateDead();
			break;
		}

		// マップコリジョン　空中移動用
		// 原点から１００ｍを越えたら削除
		VECTOR3 vNowPos = GetPositionVector(m_mWorld);
		if (vNowPos.x < -100 || vNowPos.x > 100 || vNowPos.y < -100 || vNowPos.y > 100 || vNowPos.z < -100 || vNowPos.z > 100)
		{
			m_dwStatus = DEAD;		// HPが０なので死亡へ

		}

		// 描画処理  ---------------------------------------------
		//画面外なら描画しない
		VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
		if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
			if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
		}
		vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
		if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
			if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
		}

		// バウンディングボックス
		m_pBBox->m_mWorld = m_mWorld;
}

//-----------------------------------------------------------------------------  
// 敵シールドオブジェクトの制御
// 敵が通常状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmShieldObj::UpdateNormal()
{

	MATRIX4X4 mPos;

	if (m_dwStatus == FLASH)m_dwStatus = NORMAL;

	mPos = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);    // 直進処理のみ
	m_mWorld = mPos * m_mWorld;

	//ナビゲーションマップを横移動していく
	ObjRoundTrip(m_Nav.vMin, m_Nav.vMax);


}

//-----------------------------------------------------------------------------   
// 敵シールドオブジェクトの制御
// 敵がダメージ状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmShieldObj::UpdateDamage()
{
	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生
	m_dwStatus = DEAD;		


}
//-----------------------------------------------------------------------------    
// 敵シールドオブジェクトの制御
//
// 敵が死亡状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmShieldObj::UpdateDead()
{

	ObjBasicDelete();
	if (m_dwPlayerNo == FIRSTPLAYER)m_pGMain->m_pEnmProc->m_pEnmShieldProc->SetMaxWaitTime();
	if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_pEnmProc->m_pEnmShieldProc->SetMaxWaitTimeSec();
}


//============================================================================ 

// 敵壁プロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmWallProc::CEnmWallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_WALL_WAITMAX;                   // 敵が発生するまでの待ち時間
	m_dwProcID = ENM_WALL_ID;                // 敵的のID
	m_nNum = m_nMaxNum = ENM_WALL_ALLMAX;    // 敵的の最大出現数
	m_dwKinds = TARGET;



	// Fbxスキンメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy2.mesh"));   // 弾のスタティックメッシュ

	for (int i = 0; i < ENM_WALL_MAX*2; i++)
	{
		m_pObjArray.push_back(new CEnmWallObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
		m_pObjArray[i]->SetObjID(m_dwProcID);
		m_pObjArray[i]->SetObjNo(i);
		((CEnmWallObj*)m_pObjArray[i])->SetMesh(this);  // メッシュのアドレスをオブジェクトに設定する
		((CEnmWallObj*)m_pObjArray[i])->SetArryNo(i);
		if (i < ENM_WALL_MAX)((CEnmWallObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
		else if (i >= ENM_WALL_MAX)((CEnmWallObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);


	}

	m_nWaitTime = m_nMaxwaitTime = nWait;


}



//============================================================================    
// 敵壁プロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmWallProc::~CEnmWallProc()
{
	SAFE_DELETE(m_pMesh);
}
//===========================================================================
//
// 敵壁オブジェクトのコンストラクタ
//
//  引数
//  CGameMain* pGMain;		// ゲームメインクラスへのポインタ
//
// ---------------------------------------------------------------------------
CEnmWallObj::CEnmWallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{

	m_dwScorePoint = ENM_WALL_POINT;

	// バウンディングボックスの設定
	VECTOR3 vMin(ENM_WALL_BBOX_MIN);
	VECTOR3 vMax(ENM_WALL_BBOX_MAX);
	ObjBasicConstructor(0, 0, vMin, vMax);
	m_vTarget = GetPositionVector(m_mWorld);

}
// ---------------------------------------------------------------------------   
// 敵壁オブジェクトのデストラクタ
//
//   なお、CBBoxのdeleteはCBaseObjのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmWallObj::~CEnmWallObj()
{
	;
}
// ---------------------------------------------------------------------------  
// 敵壁オブジェクトのメッシュポインタ設定
//
//  CEnmWallProc* pProc
//
// ---------------------------------------------------------------------------  
void CEnmWallObj::SetMesh(CEnmWallProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ
}

// ---------------------------------------------------------------------------   
//
// 敵壁プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmWallProc::Update()
{
	UpdateNav();
}
// --------------------------------------------------------------------------- 
//
// 敵壁プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmWallProc::UpdateNav()
{
	std::vector<DWORD> Nav;   // 選択ナビマップ
	if (m_pGMain->m_nScore > ENM_WALL_STARTPOINT) {		//出現するためのスコア	
		// まだ発生できる数の場合のみ発生させる
		if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
		{
			// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
			for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
			{
				for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
				{
					if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
					{
						Nav.push_back(i);
					}
				}
			}
			if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
			{
				if (m_nWaitTime <= 0)
				{
					// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_WALL_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmWallObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
							m_pObjArray[i]->Start();	// 敵を発生させる
							m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
							SetMaxWaitTime();
							break;
						}
					}
				}
			}
			else {
				m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
			}
		}
	}
}

// ---------------------------------------------------------------------------    
//
// 敵壁プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmWallProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);
}
// ---------------------------------------------------------------------------  

// 敵壁プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmWallProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{

	// まだ発生できる数の場合のみ発生させる
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			if (m_dwPlayerNo == FIRSTPLAYER) {

				if (m_pGMain->m_nScore > ENM_WALL_STARTPOINT) {		//出現するためのスコア	

					if (m_nWaitTime <= 0)
					{
						// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = 0; i < ENM_WALL_MAX; i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmWallObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
								m_pObjArray[i]->Start();	// 敵を発生させる
								m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
								SetMaxWaitTime();
								break;

							}

						}
					}
				}
			}
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_pGMain->m_nScoreSec > ENM_WALL_STARTPOINT) {		//出現するためのスコア	

					if (m_nWaitTimeSec <= 0)
					{
						// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = ENM_WALL_MAX; i < (ENM_WALL_MAX * 2); i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmWallObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
								m_pObjArray[i]->Start();	// 敵を発生させる
								m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
								SetMaxWaitTimeSec();
								break;

							}

						}
					}
				}
			}

		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}

}


// ---------------------------------------------------------------------------  
// 敵壁プロシージャのナビゲーションマップ登録
//
//
// ---------------------------------------------------------------------------
void CEnmWallProc::NavSet()
{

	Nav.clear();
	Nav.shrink_to_fit();

	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}


// ---------------------------------------------------------------------------  
// 敵壁オブジェクトの発生
//
//
// ---------------------------------------------------------------------------
BOOL CEnmWallObj::Start()
{
	dWallStartTime = ENM_WALL_STARTTIME;

	m_dWeaponUseNum = ENM_WALL_USENUM;
	bTarget = FALSE;	

	// ナビゲーションマップに出現		
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);

	//出現位置に応じて角度を変える	
	ObjAppearanceDirection(m_Nav.dPosStatus, &m_mWorld);

	m_pBBox->m_mWorld = m_mWorld;                           

	m_bActive = TRUE;	// 敵壁オブジェクト
	fNormalSpeed = ENM_WALL_SPEED;
	m_vPosUp.x = fNormalSpeed;
	m_nHp = m_nMaxHp;
	return TRUE;

}

//-----------------------------------------------------------------------------   
// 敵壁オブジェクトの制御
//　キーボードで敵を動かす
//　敵のアニメーション、ジャンプ、自然落下
//　ワールド座標変換、マップとの接触判定
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmWallObj::Update()
{
	if (!m_bActive) return;  // 非表示のときは処理をしない

	// 変数の初期化   ---------------------------------------
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // 一つ前の位置

	// ステータスごとの処理  --------------------------------
	switch (m_dwStatus)
	{
	case  FLASH: // 敵がダメージから復帰したときの処理。breakをつけずに次のNORMALを行う。
	case  NORMAL: // 敵が通常状態のときの処理
		UpdateNormal();
		break;

	case  DAMAGE: // 敵がダメージ状態のときの処理
		UpdateDamage();
		if (m_dwPlayerNo == FIRSTPLAYER)m_pGMain->m_nScore = m_pGMain->m_nScore + m_dwScorePoint;
		if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_nScoreSec = m_pGMain->m_nScoreSec + m_dwScorePoint;		
		break;

	case  DEAD:	// 敵が死亡状態のときの処理
		UpdateDead();
		break;
	}



	// 描画処理  ---------------------------------------------

	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}
	// バウンディングボックス
	m_pBBox->m_mWorld = m_mWorld;

}

//-----------------------------------------------------------------------------   
// 敵壁オブジェクトの制御
// 敵が通常状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmWallObj::UpdateNormal()
{

	MATRIX4X4 mPos;
	const int dWallWaitTime = ENM_WALL_WAITTIME;		//壁が出現するまでの時間

	mPos = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);    // 直進処理のみ
	m_mWorld = mPos * m_mWorld;

	//ナビゲーションマップを横移動していく	
	ObjRoundTrip(m_Nav.vMin, m_Nav.vMax);


	//出現させることのできる武器の数があるなら
	if (m_dWeaponUseNum > 0) {	//出現させることのできるスキルの数があるなら
		if ((dWallStartTime / 60) > dWallWaitTime) {
			m_pGMain->m_pWeaponProc->m_pWeaponWallProc->Start(m_mWorld, ENM, m_dwObjNo,m_dwPlayerNo); // ボール発射		

			m_dWeaponUseNum--;
			dWallStartTime = 0;
		}
		else {
			dWallStartTime++;
		}
	}

}

//-----------------------------------------------------------------------------    
// 敵壁オブジェクトの制御
// 敵がダメージ状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmWallObj::UpdateDamage()
{
	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生

	const int nFlashTime = 5;  // 無敵状態の時間


	m_nHp -= m_pHitObj->GetAtc();	// 攻撃を受けたダメージ
	if (m_nHp <= 0)
	{
		m_nHp = 0;
		m_dwStatus = DEAD;		// HPが０なので死亡へ
	}
	else {
		m_nCnt1 = nFlashTime;   // 無敵状態の時間
		m_dwStatus = FLASH;     // ダメージからの復帰処理を行う
	}


}
//-----------------------------------------------------------------------------   
// 敵壁オブジェクトの制御
// 敵が死亡状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmWallObj::UpdateDead()
{
	ObjBasicDelete();
	if (m_pGMain->m_pEnmProc->m_pEnmWallProc->GetWaitTime() <= 0&& m_dwPlayerNo == FIRSTPLAYER) {	
		m_pGMain->m_pEnmProc->m_pEnmWallProc->SetMaxWaitTime();
	}

	if (m_pGMain->m_pEnmProc->m_pEnmWallProc->GetWaitTimeSec() <= 0 && m_dwPlayerNo == SECONDPLAYER) {	
		m_pGMain->m_pEnmProc->m_pEnmWallProc->SetMaxWaitTimeSec();
	}

}

//============================================================================  
//
// 敵爆弾Ballプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmBallBoomProc::CEnmBallBoomProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_BALLBOOM_WAITMAX;                   // 敵が発生するまでの待ち時間
	m_dwProcID = ENM_BALLBOOM_ID;                // 敵爆弾BallのID
	m_nNum = m_nMaxNum = ENM_BALLBOOM_ALLMAX;    // 敵爆弾Ballの最大出現数
	m_dwKinds = BALL;

	// Fbxスキンメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Weapon_BallBoom.mesh"));   // 弾のスタティックメッシュ
	for (int i = 0; i < ENM_BALLBOOM_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmBallBoomObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
		m_pObjArray[i]->SetObjID(m_dwProcID);
		m_pObjArray[i]->SetObjNo(i);
		((CEnmBallBoomObj*)m_pObjArray[i])->SetMesh(this);  // メッシュのアドレスをオブジェクトに設定する  
		if (i < ENM_TARGET_MAX)((CEnmTargetObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);

	}

	m_nWaitTime = m_nMaxwaitTime = nWait;
	m_dwBreakNum = 0;
}
//============================================================================    
//
// 敵爆弾Ballプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmBallBoomProc::~CEnmBallBoomProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================  
//
// 敵爆弾Ballオブジェクトのコンストラクタ
//
//  引数
//  CGameMain* pGMain;		// ゲームメインクラスへのポインタ
//
// ---------------------------------------------------------------------------
CEnmBallBoomObj::CEnmBallBoomObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// バウンディングボックスの設定
	VECTOR3 vMin(ENM_BALLBOOM_BBOX_MIN);
	VECTOR3 vMax(ENM_BALLBOOM_BBOX_MAX);

	ObjBasicConstructor(0, 0, vMin, vMax);
	m_vDiffuse = VECTOR4(1, 1, 1, 1);
	m_vTarget = GetPositionVector(m_mWorld);


}
// ---------------------------------------------------------------------------  
//
// 敵爆弾Ballオブジェクトのデストラクタ
//
//   なお、CBBoxのdeleteはCBaseObjのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmBallBoomObj::~CEnmBallBoomObj()
{
	;
}
// ---------------------------------------------------------------------------   
// 敵爆弾Ballオブジェクトのメッシュポインタ設定
//
//  CEnmBallBoomProc* pProc
//
// --------------------------------------------------------------------------- 
void CEnmBallBoomObj::SetMesh(CEnmBallBoomProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ

}

// ---------------------------------------------------------------------------  
// 敵爆弾Ballプロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmBallBoomProc::Update()
{

	std::vector<DWORD> Nav;   // 選択ナビマップ
	if ( m_pGMain->m_nTimeNum!=0&&m_pGMain->m_nTimeNum % 10 == 0|| m_pGMain->m_dwGameStatus == GAMETUTORIAL) {		
		if (m_pGMain->m_dwGameStatus != GAMEMULTI) {
			// まだ発生できる数の場合のみ発生させる
			if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
			{
				// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
				for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
				{
					for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
					{
						if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
						{
							Nav.push_back(i);
						}
					}
				}
				if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
				{
					if (m_nWaitTime <= 0)
					{
						// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = 0; i < m_pObjArray.size(); i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmBallBoomObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
								m_pObjArray[i]->Start();	// 敵を発生させる
								m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
								break;
							}
						}
					}
				}
				else {
					m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
				}
			}
		}
	}


}
// ---------------------------------------------------------------------------    
//
// 敵爆弾Ballオブジェクトの発生
//
//
// ---------------------------------------------------------------------------
BOOL CEnmBallBoomObj::Start()
{

	m_bActive = TRUE;	// 敵爆弾Ballオブジェクト
	MATRIX4X4 mYaw;
	VECTOR3 m_vTarget;

	// ナビゲーションマップに従って発生させる		
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
	m_vTarget = VECTOR3((float)Random(m_Nav.vMin.x, m_Nav.vMax.x), m_Nav.vMax.y,
		(float)Random(m_Nav.vMin.z, m_Nav.vMax.z));
	m_pBBox->m_mWorld = m_mWorld;                           

	VECTOR3 vBall = GetPositionVector(m_mWorld);
	VECTOR3 m_vPcTarget = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetLocalMatrix());
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	m_vDiffuse = VECTOR4(1, 1, 1, 1);						

	m_nHp = m_nMaxHp;
	m_dwStatus = NORMAL;
	m_dwStatusSub = ATTACKNONE;
	m_dwStatusPhase = 0;
	m_bDamage = FALSE;

	m_fDist = 0;
	bShaftObjTrigger = FALSE;


	m_vPcTarget = GetPositionVector(pPcObj->GetWorld());

	m_vPcTarget.y = vBall.y;
	m_vRotUp.y = GetTargetRotateVector(m_mWorld, m_vPcTarget).y;
	RotRig(&m_vRotUp.y);
	//m_pGMain->m_nScore = m_vTarget.y;
	mYaw = XMMatrixRotationY(XMConvertToRadians(m_vRotUp.y));
	m_mWorld = mYaw * m_mWorld;
	
	
	m_pBBox->m_mWorld = m_mWorld;
	m_StartWorld = m_mWorld;		//スタート時のワールドマトリックス	

	m_nScrX = 0;	



	// 固定位置から発生させる(0,2,20)から手前に向かって
	return TRUE;

}

//-----------------------------------------------------------------------------  
// 敵爆弾Ballオブジェクトの制御
//
//　キーボードで敵を動かす
//　敵のアニメーション、ジャンプ、自然落下
//　ワールド座標変換、マップとの接触判定
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmBallBoomObj::Update()
{
	if (!m_bActive) return;  // 非表示のときは処理をしない

	// 変数の初期化   ---------------------------------------
	m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // 一つ前の位置

	// ステータスごとの処理  --------------------------------
	switch (m_dwStatus)
	{
	case  FLASH: // 敵がダメージから復帰したときの処理。breakをつけずに次のNORMALを行う。
	case  NORMAL: // 敵が通常状態のときの処理
		UpdateNormal();
		break;

	case  DAMAGE: // 敵がダメージ状態のときの処理
		UpdateDamage();
		break;

	case  DEAD:	// 敵が死亡状態のときの処理
		UpdateDead();
		break;
	}
	if (m_pGMain->m_pMapProc->isCollisionMove(&m_mWorld, m_mWorldOld, m_pBBox->m_vMax.x))  // マップコリジョン
	{

		m_dwStatus = DEAD;

	}

	// ボールの削除処理
	// スタートから１０ｍを越えたら削除	
	VECTOR3 vNowPos;
	VECTOR3	vStartPos;
	vNowPos = GetPositionVector(m_mWorld);
	vStartPos = GetPositionVector(m_StartWorld);
	if((magnitude(vNowPos - vStartPos)>10|| magnitude(vNowPos - vStartPos)<-10)&&m_bDamage!=TRUE)
	{
		m_dwStatus = DEAD;
	}

	// 描画処理  ---------------------------------------------

	m_pMesh->m_vDiffuse = m_vDiffuse;			
	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	// バウンディングボックス
	m_pBBox->m_mWorld = m_mWorld;

	// 敵の頭上の警告表示  -----------------------------
	if (m_bDamage != TRUE) {
		VECTOR3 vEnmPos = GetPositionVector(m_mWorld);
		VECTOR2 vCaveatOverSize = VECTOR2(0.5, 0.5);			//頭上の警告サイズ
		VECTOR2 vCaveatOverSrcPos = VECTOR2(554, 275);			//頭上の警告パターン位置
		VECTOR2 vCaveatOverSrcSize = VECTOR2(68, 64);			//頭上の警告パターンサイズ
		const float vCaveatOverPosTweak = 0.5f;					//頭上の警告の位置を微調整
		vEnmPos.y += 1.0f;

		m_pGMain->m_pRenderBufProc->SetDraw3DSprite(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageRadar(), vEnmPos, vCaveatOverSize, vCaveatOverSrcPos, vCaveatOverSrcSize);
		VECTOR3 vEyePt = m_pGMain->m_vEyePt;
		MATRIX4X4 mImageWorld = TurnTarget(m_mWorld, XMMatrixTranslation(vEyePt.x, vEyePt.y, vEyePt.z));
		mImageWorld = XMMatrixTranslation(vCaveatOverPosTweak,0,0)* mImageWorld;
		vEnmPos = GetPositionVector(mImageWorld);

	}

	//警告の表示	
	const int SpritePosX = (WINDOW_WIDTH / 2) - 129;		//警告の表示位置X座標
	const int SpritePosY = 20;								//警告の表示位置Y座標
	const int SpriteSrcX = 0;								//警告のパターン位置X座標
	const int SpriteSrcY = 0;								//警告のパターン位置Y座標
	const int SpriteSrcWidth = 258;							//警告のパターンサイズ幅
	const int SpriteSrcHeight =109;							//警告のパターンサイズ高さ

	const int SpriteSubPosX = SpritePosX + 8;				//二つ目の警告の表示位置X座標
	const int SpriteSubPosY = SpritePosY + 16;				//二つ目の警告の表示位置Y座標
	const int SpriteSubSrcX = 323;							//二つ目の警告のパターン位置X座標
	const int SpriteSubSrcY = 0;							//二つ目の警告のパターンサイズ幅
	const int SpriteSubSizeWidth = 242;						//二つ目の警告のパターンサイズ高さ
	const int SpriteSubSizeHeight = 84;

	// 横スクロール		
	if (m_bDamage != TRUE) {
		m_nScrX += 1;
		if (m_nScrX > SpriteSubSizeWidth)m_nScrX = 0;
		m_pGMain->m_pRenderBufProc->SetDrawSprite(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageEventReport(), SpritePosX, SpritePosY, SpriteSrcX, SpriteSrcY, SpriteSrcWidth, SpriteSrcHeight, 1.0f);
		m_pGMain->m_pRenderBufProc->SetDrawSprite(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageEventReport(), SpriteSubPosX, SpriteSubPosY, SpriteSubSrcX + (m_nScrX), SpriteSubSrcY, SpriteSubSizeWidth - (m_nScrX), SpriteSubSizeHeight, 1.0f);
		m_pGMain->m_pRenderBufProc->SetDrawSprite(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageEventReport(), SpriteSubPosX + (SpriteSubSizeWidth - m_nScrX), SpriteSubPosY, SpriteSubSrcX, SpriteSubSrcY, m_nScrX, SpriteSubSizeHeight, 1.0f);

	}
	

}

//-----------------------------------------------------------------------------   
// 敵爆弾Ballオブジェクトの制御
//
// 敵が通常状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmBallBoomObj::UpdateNormal()
{

	float fNormalSpeed = ENM_BALLBOOM_SPEED;                                    // 移動スピード
	MATRIX4X4 mPos;
	DWORD	EnmProcSize = m_pGMain->m_pEnmProc->GetProcArrayPtr().size();
	if (m_bDamage == TRUE)	fNormalSpeed = (ENM_BALLBOOM_SPEED*2);		//当たったら速度が上がる	
	if (m_dwStatus == FLASH)m_dwStatus = NORMAL;
	const float GravityDist = 3.0f;				//判定距離
	const float GravityRotateSpeed = 0.5f;		//方向転換のスピード


	mPos = XMMatrixTranslation(0, 0, fNormalSpeed);    // 直進処理のみ
	m_mWorld = mPos * m_mWorld;

	if (m_bDamage == TRUE) {		//ヒット状態の時の処理
		for (int i = 0; i < EnmProcSize; i++) {
			//的に当たった時
			if (m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->GetKinds() == TARGET) {
				if (m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->HitcheckMulti(this, m_pBBox, m_dwPlayerNo)) {
					m_dwStatus = DEAD;
					m_pGMain->m_pEffectProc->m_pLetterEffectProc->AddBreakNum(1);

				}
				//ボールの角度の補正
				if (bShaftObjTrigger != TRUE) {
					if (m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->GetProcID() == ENM_TARGETSKILL_ID)
					{
						m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->ObjGravityMulti(this, GravityDist + 2, GravityRotateSpeed, m_dwPlayerNo);
					}
					else
						m_pGMain->m_pEnmProc->GetProcArrayPtr()[i]->ObjGravityMulti(this, GravityDist, GravityRotateSpeed, m_dwPlayerNo);
				}
			}
		}

	}




}

//-----------------------------------------------------------------------------   
// 敵爆弾Ballオブジェクトの制御
//
// 敵がダメージ状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmBallBoomObj::UpdateDamage()
{
		if (m_bDamage != TRUE) {
			if (m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetProcID() == m_pHitObj->GetObjID()) {
				ObjReflection();
				m_bDamage = TRUE;

				m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生
			}
		}
		m_dwStatus = NORMAL;

}
//-----------------------------------------------------------------------------  
// 敵爆弾Ballオブジェクトの制御
//
// 敵が死亡状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmBallBoomObj::UpdateDead()
{
	VECTOR3 vImagePos = VECTOR3(2.5, 1.5, 7);
	VECTOR2 vLESize = VECTOR2(8, 2);
	VECTOR2 vLESrcPos = VECTOR2(441, 384);
	VECTOR2 vLESrcSize = VECTOR2(147, 46);
	const  float fLEFreamEnd = 100;

	ObjBasicDelete();
	VECTOR3 vNowPos = GetPositionVector(m_mWorld);
	m_pGMain->m_pEffectProc->m_pBillProc->Start(vNowPos,m_bDamage);	// パーティクルの発生
	VECTOR3 vEyePt = m_pGMain->m_vEyePt;
	MATRIX4X4 mImageWorld = TurnTarget(m_mWorld, XMMatrixTranslation(vEyePt.x, vEyePt.y, vEyePt.z));
	mImageWorld = XMMatrixTranslation(vImagePos.x, vImagePos.y, vImagePos.z)* mImageWorld;
	vNowPos = GetPositionVector(mImageWorld);

	//擬音表示
	m_pGMain->m_pEffectProc->m_pLetterEffectProc->Start(m_pGMain->m_pBackForeProc->GetSprite(), m_pGMain->m_pBackForeProc->GetImageMangaEfect(), vNowPos, vLESize, vLESrcPos, vLESrcSize, fLEFreamEnd, m_dwPlayerNo, LENO_EXPANISIONTYPE,1.0);
	m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->SetWaitTime(600);		//次の出現するための時間をセット
	m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->AddNum(1);			//出現する数を増やす
	if(m_pGMain->m_dwGameStatus==GAMETUTORIAL)		m_pGMain->m_pEnmProc->m_pEnmBallBoomProc->SetWaitTime(120);		//次の出現するための時間をセット（チュートリアル）
	if (m_bDamage != TRUE&&m_pGMain->m_dwGameStatus != GAMETUTORIAL)	m_pGMain->m_nTimer -= ENM_BALLBOOM_TIMERDOWN;		//制限時間を減らす

}

//============================================================================    
// 敵曲がるプロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
//
// ---------------------------------------------------------------------------
CEnmBendProc::CEnmBendProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_BEND_WAITMAX;                   // 敵が発生するまでの待ち時間
	m_dwProcID = ENM_BEND_ID;                // 敵的のID
	m_nNum = m_nMaxNum = ENM_BEND_ALLMAX;    // 敵的の最大出現数
	m_dwKinds = TARGET;



	// Fbxスキンメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy_BallBend.mesh"));   // 弾のスタティックメッシュ

	for (int i = 0; i < (ENM_BEND_MAX*2); i++)
	{
		m_pObjArray.push_back(new CEnmBendObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
		m_pObjArray[i]->SetObjID(m_dwProcID);
		m_pObjArray[i]->SetObjNo(i);
		((CEnmBendObj*)m_pObjArray[i])->SetMesh(this);  // メッシュのアドレスをオブジェクトに設定する  
		((CEnmBendObj*)m_pObjArray[i])->SetArryNo(i);
		if (i < ENM_BEND_MAX)((CEnmBendObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
		else if (i >= ENM_BEND_MAX)((CEnmBendObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);


	}

	m_nWaitTime = m_nMaxwaitTime = nWait;


}



//============================================================================   
// 敵曲がるプロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmBendProc::~CEnmBendProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================  
//
// 敵曲がるオブジェクトのコンストラクタ
//
//  引数
//  CGameMain* pGMain;		// ゲームメインクラスへのポインタ
//
// ---------------------------------------------------------------------------
CEnmBendObj::CEnmBendObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_dwScorePoint = ENM_BEND_POINT;

	// バウンディングボックスの設定
	VECTOR3 vMin(ENM_BEND_BBOX_MIN);
	VECTOR3 vMax(ENM_BEND_BBOX_MAX);
	fBaseDist = 0;
	ObjBasicConstructor(0, 0, vMin, vMax);
	m_vTarget = GetPositionVector(m_mWorld);

}
// ---------------------------------------------------------------------------    
// 敵曲がるオブジェクトのデストラクタ
//
//   なお、CBBoxのdeleteはCBaseObjのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmBendObj::~CEnmBendObj()
{
	;
}
// ---------------------------------------------------------------------------   
// 敵曲がるオブジェクトのメッシュポインタ設定
//
//  CEnmBendProc* pProc
//
// ---------------------------------------------------------------------------
void CEnmBendObj::SetMesh(CEnmBendProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ
}


// ---------------------------------------------------------------------------   
// 敵曲がるプロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmBendProc::Update()
{
	UpdateNav();

}


// ---------------------------------------------------------------------------  
//
//  敵曲がるプロシージャの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmBendProc::UpdateNav()
{
	std::vector<DWORD> Nav;   // 選択ナビマップ

	// まだ発生できる数の場合のみ発生させる
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			if (m_pGMain->m_nScore > ENM_BEND_STARTPOINT) {		//出現するためのスコア

				if (m_nWaitTime <= 0)
				{
					// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_BEND_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmBendObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
							m_pObjArray[i]->Start();	// 敵を発生させる
							m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
							SetMaxWaitTime();
							break;
						}
					}
				}
			}
		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}

}


// --------------------------------------------------------------------------- 
// 敵曲がるプロシージャマルチの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmBendProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);

}

// ---------------------------------------------------------------------------   
// 敵曲がるプロシージャマルチの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmBendProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{
	// まだ発生できる数の場合のみ発生させる
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			if (m_dwPlayerNo == FIRSTPLAYER) {

				if (m_pGMain->m_nScore > ENM_BEND_STARTPOINT) {		//出現するためのスコア		

					if (m_nWaitTime <= 0)
					{
						// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = 0; i < ENM_BEND_MAX; i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmBendObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
								m_pObjArray[i]->Start();	// 敵を発生させる
								m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
								SetMaxWaitTime();
								break;

							}

						}
					}
				}
			}
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_pGMain->m_nScoreSec > ENM_BEND_STARTPOINT) {		//出現するためのスコア	

					if (m_nWaitTimeSec <= 0)
					{
						// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
						int k = Random(0, Nav.size() - 1);
						int no = Nav[k];
						for (DWORD i = ENM_BEND_MAX; i < (ENM_BEND_MAX * 2); i++)
						{
							if (!m_pObjArray[i]->GetActive())
							{
								((CEnmBendObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
								m_pObjArray[i]->Start();	// 敵を発生させる
								m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
								SetMaxWaitTimeSec();
								break;

							}

						}
					}
				}
			}

		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}



}

// ---------------------------------------------------------------------------    
// 敵曲がるプロシージャのナビゲーションマップ登録
//
//
// ---------------------------------------------------------------------------
void CEnmBendProc::NavSet()
{

	Nav.clear();
	Nav.shrink_to_fit();

	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}


// ---------------------------------------------------------------------------   
// 敵曲がるオブジェクトの発生
//
//
// ---------------------------------------------------------------------------
BOOL CEnmBendObj::Start()
{
	dBallStartTime = ENM_BEND_STARTTIME;
	m_dWeaponUseNum = ENM_BEND_USENUM;

	bTarget = FALSE;		
	int RanNum = Random(0, 1);
	if (RanNum == 0)
		fMoveSpeed = ENM_BEND_SPEED;
	else
		fMoveSpeed = -ENM_BEND_SPEED;


	// ナビゲーションマップに出現	
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);


	m_mWorld = TurnTarget(m_mWorld, XMMatrixTranslation(0,0,0));


	m_pBBox->m_mWorld = m_mWorld;                          

	VECTOR3 vTarget = VECTOR3(0, 0, 0);
	VECTOR3 vMyobj = GetPositionVector(m_mWorld);
	fBaseDist = magnitude(vTarget - vMyobj);


	m_bActive = TRUE;	// 敵曲がるオブジェクト
	fNormalSpeed = 0.05f;
	m_vPosUp.x = fNormalSpeed;
	m_nHp = m_nMaxHp;


	return TRUE;

}

//-----------------------------------------------------------------------------    
// 敵曲がるオブジェクトの制御
//　キーボードで敵を動かす
//　敵のアニメーション、ジャンプ、自然落下
//　ワールド座標変換、マップとの接触判定
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmBendObj::Update()
{
	if (!m_bActive) return;  // 非表示のときは処理をしない

	// 変数の初期化   ---------------------------------------
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // 一つ前の位置

	// ステータスごとの処理  --------------------------------
	switch (m_dwStatus)
	{
	case  NORMAL: // 敵が通常状態のときの処理
		UpdateNormal();
		break;

	case  DAMAGE: // 敵がダメージ状態のときの処理
		UpdateDamage();
		m_pGMain->m_nScore = m_pGMain->m_nScore + m_dwScorePoint;
		break;

	case  DEAD:	// 敵が死亡状態のときの処理
		UpdateDead();
		break;
	}



	// 描画処理  ---------------------------------------------
	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);	
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}

	// バウンディングボックス
	m_pBBox->m_mWorld = m_mWorld;

}

//-----------------------------------------------------------------------------   
// 敵曲がるオブジェクトの制御
// 敵が通常状態のときの処理
//
//   引数　　　なし
//
//-----------------------------------------------------------------------------
void	CEnmBendObj::UpdateNormal()
{

	DWORD dBallWaitTime = ENM_WALL_WAITTIME;
	const float BallSpeedRanMin = ENM_WALL_SPEEDRUN_MIN;
	const float BallSpeedRanMax = ENM_WALL_SPEEDRUN_MAX;

	if (m_dwStatus == FLASH)m_dwStatus = NORMAL;

	MATRIX4X4	mBaseWorld = XMMatrixTranslation(0, GetPositionVector(m_mWorld).y, 0);
	m_mWorld = RotTarget(m_mWorld, mBaseWorld, fMoveSpeed,fBaseDist);
	m_mWorld = TurnTarget(m_mWorld, mBaseWorld);

		if ((dBallStartTime / 60) > dBallWaitTime) {
			m_dWeaponUseNum--;
			MATRIX4X4 mStartWord = TurnTarget(m_mWorld,m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
			if (m_dwPlayerNo == SECONDPLAYER)mStartWord = TurnTarget(m_mWorld, m_pGMain->m_pPcProc->GetPcSecObjPtr()->GetWorld());
			VECTOR3 vBallSpeed=VECTOR3(0,0,0);
			vBallSpeed.z = Random(BallSpeedRanMin, BallSpeedRanMax);
			vBallSpeed.z = vBallSpeed.z/ 100+ (Random(0, 9)/1000);
			vBallSpeed.x = vBallSpeed.z;
			m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->Start(mStartWord, vBallSpeed, RIGHT,ENM,m_dwPlayerNo);
			m_pGMain->m_pWeaponProc->m_pWeaponBendBallProc->Start(mStartWord, vBallSpeed, LEFT, ENM, m_dwPlayerNo);

			dBallStartTime = 0;
		}
		else {
			dBallStartTime++;
		}
	

}

//-----------------------------------------------------------------------------  
// 敵曲がるオブジェクトの制御
// 敵がダメージ状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmBendObj::UpdateDamage()
{
	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生
	m_dwStatus = DEAD;		// HPが０なので死亡へ


}
//-----------------------------------------------------------------------------   
// 敵曲がるオブジェクトの制御
// 敵が死亡状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmBendObj::UpdateDead()
{
	ObjBasicDelete();
	if (m_pGMain->m_pEnmProc->m_pEnmBendProc->GetWaitTime() <= 0&&m_dwPlayerNo==FIRSTPLAYER) {		
		m_pGMain->m_pEnmProc->m_pEnmBendProc->SetMaxWaitTime();
	}
	if (m_pGMain->m_pEnmProc->m_pEnmBendProc->GetWaitTime() <= 0 && m_dwPlayerNo == SECONDPLAYER) {		
		m_pGMain->m_pEnmProc->m_pEnmBendProc->SetMaxWaitTimeSec();
	}

	
}

//============================================================================  
//
// 敵的プロシージャのコンストラクタ
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmTargetSkillProc::CEnmTargetSkillProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait = ENM_TARGETSKILL_WAITMAX;                   // 敵が発生するまでの待ち時間
	m_dwProcID = ENM_TARGETSKILL_ID;                // 敵的のID
	m_nNum = m_nMaxNum = ENM_TARGETSKILL_ALLMAX;    // 敵的の最大出現数
	m_dwKinds = TARGET;



	// Fbxスキンメッシュの設定
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Enemy_TargetSkill.mesh"));   // 弾のスタティックメッシュ

	for (int i = 0; i < (ENM_TARGETSKILL_MAX * 2); i++)
	{
		m_pObjArray.push_back(new CEnmTargetSkillObj(m_pGMain));  // m_pObjArrayにオブジェクトを生成する
		m_pObjArray[i]->SetObjID(m_dwProcID);
		m_pObjArray[i]->SetObjNo(i);
		((CEnmTargetSkillObj*)m_pObjArray[i])->SetMesh(this);  // メッシュのアドレスをオブジェクトに設定する  
		if (i < ENM_TARGETSKILL_MAX)((CEnmTargetSkillObj*)m_pObjArray[i])->SetPlayerNo(FIRSTPLAYER);
		else if (i >= ENM_TARGETSKILL_MAX)((CEnmTargetSkillObj*)m_pObjArray[i])->SetPlayerNo(SECONDPLAYER);



	}


	m_dwBreakNum = 0;
	m_nWaitTime = m_nMaxwaitTime = nWait;
	m_nWaitTimeSec = nWait;		

}



//============================================================================   
//
// 敵的プロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmTargetSkillProc::~CEnmTargetSkillProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================  
//
// 敵的オブジェクトのコンストラクタ
//
//  引数
//  CGameMain* pGMain;		// ゲームメインクラスへのポインタ
//
// ---------------------------------------------------------------------------
CEnmTargetSkillObj::CEnmTargetSkillObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_dwScorePoint = ENM_TARGETSKILL_POINT;

	// バウンディングボックスの設定
	VECTOR3 vMin(-0.75f, -0.75f, -0.75f);
	VECTOR3 vMax(ENM_TARGETSKILL_BBOX_MAX);
	ObjBasicConstructor(0, 0, vMin, vMax);

	m_vTarget = GetPositionVector(m_mWorld);

}
// ---------------------------------------------------------------------------    
//
// 敵的オブジェクトのデストラクタ
//
//   なお、CBBoxのdeleteはCBaseObjのデストラクタで行うため不要
//
// ---------------------------------------------------------------------------
CEnmTargetSkillObj::~CEnmTargetSkillObj()
{
	;
}
// ---------------------------------------------------------------------------  
//
// 敵的オブジェクトのメッシュポインタ設定
//
//  CEnmTargetSkillProc* pProc
//
// ---------------------------------------------------------------------------  
void CEnmTargetSkillObj::SetMesh(CEnmTargetSkillProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// スキンメッシュのポインタ
}

// ---------------------------------------------------------------------------   
//
// 敵的プロシージャの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmTargetSkillProc::Update()
{
	UpdateNav();
}

// ---------------------------------------------------------------------------   
// 敵的プロシージャの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmTargetSkillProc::UpdateNav()
{
	std::vector<DWORD> Nav;   // 選択ナビマップ



	// まだ発生できる数の場合のみ発生させる
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			if (m_nWaitTime <= 0)
			{
				// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
				int k = Random(0, Nav.size() - 1);
				int no = Nav[k];
				for (DWORD i = 0; i < ENM_TARGETSKILL_MAX; i++)
				{
					if (!m_pObjArray[i]->GetActive())
					{
						((CEnmTargetSkillObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
						m_pObjArray[i]->Start();	// 敵を発生させる
						m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
						SetMaxWaitTime();
						break;
					}
				}
			}
		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}

}

// ---------------------------------------------------------------------------   
//
// 敵的プロシージャマルチの自動発生処理
//
//
// ---------------------------------------------------------------------------
void CEnmTargetSkillProc::UpdateMulti(DWORD m_dwPlayerNo)
{
	UpdateNavMulti(m_dwPlayerNo);
}


// --------------------------------------------------------------------------- 
// 敵的プロシージャマルチの自動発生処理関数
//
//
// ---------------------------------------------------------------------------
void CEnmTargetSkillProc::UpdateNavMulti(DWORD m_dwPlayerNo)
{



	// まだ発生できる数の場合のみ発生させる
	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		if (Nav.size() > 0)  // 選択ナビマップNavに登録されているとき
		{
			if (m_dwPlayerNo == FIRSTPLAYER) {

				if (m_nWaitTime <= 0)
				{
					// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = 0; i < ENM_TARGETSKILL_MAX; i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmTargetSkillObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
							m_pObjArray[i]->Start();	// 敵を発生させる
							m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
							SetMaxWaitTime();
							break;

						}

					}
				}
			}
			else if (m_dwPlayerNo == SECONDPLAYER) {
				if (m_nWaitTimeSec <= 0)
				{
					// 選択ナビマップNavの中から発生するナビマップをランダムに選ぶ
					int k = Random(0, Nav.size() - 1);
					int no = Nav[k];
					for (DWORD i = ENM_TARGETSKILL_MAX; i < (ENM_TARGETSKILL_MAX * 2); i++)
					{
						if (!m_pObjArray[i]->GetActive())
						{
							((CEnmTargetSkillObj*)m_pObjArray[i])->SetNav(m_pGMain->m_pMapProc->GetNavMap()[no]);  // 選ばれたナビマップをオブジェクトに登録する
							m_pObjArray[i]->Start();	// 敵を発生させる
							m_nNum--;			// 敵が発生したら発生できる敵の数を１減らす
							SetMaxWaitTimeSec();
							break;

						}

					}
				}
			}

		}
		else {
			m_nNum = 0;			// ナビマップNavが選択されていない場合、発生数は０となる
		}
	}



}

// ---------------------------------------------------------------------------   
// 敵的プロシージャのナビゲーションマップ登録
//
//
// ---------------------------------------------------------------------------
void CEnmTargetSkillProc::NavSet()
{

	//Nav.erase(Nav.begin(), Nav.end());
	Nav.clear();
	Nav.shrink_to_fit();

	if (m_pGMain->m_pMapProc->GetNavMap().size() > 0)
	{
		// ナビマップの敵ＩＤが一致するものを選択ナビマップNavに登録する
		for (int i = 0; i < m_pGMain->m_pMapProc->GetNavMap().size(); i++)
		{
			for (int j = 0; j < m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID.size(); j++)
			{
				if (m_pGMain->m_pMapProc->GetNavMap()[i].m_dwEnmID[j] == m_dwProcID)
				{
					Nav.push_back(i);
				}
			}
		}
	}


}


// ---------------------------------------------------------------------------   
//
// 敵的オブジェクトの発生
//
//
// ---------------------------------------------------------------------------
BOOL CEnmTargetSkillObj::Start()
{

	VECTOR3 vHit = VECTOR3(0.0f, 0.0f, 0.0f), vNrm = VECTOR3(0.0f, 1.0f, 0.0f);


	bTarget = FALSE;		

	// ナビゲーションマップに出現		
	ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
	m_pBBox->m_mWorld = m_mWorld;                          

	// 的の位置が被らないようにする		

	for (DWORD i = 0; i < m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->GetObjArrayPtr().size(); i++) {

		if (m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->GetObjArrayPtr()[i]->GetActive() == TRUE) {		//表示されている的を探す
			if (m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->GetObjArrayPtr()[i]->GetPlayerNo() == m_dwPlayerNo) {
				if (m_pBBox->OBBCollisionDetection(m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->GetObjArrayPtr()[i]->GetBBox(), &vHit, &vNrm)) {

					ObjNavOccurrence(m_Nav.vMin, m_Nav.vMax);
					m_pBBox->m_mWorld = m_mWorld;                          
					i = 0;

				}

			}
		}

	}

	//--的固定用
	MATRIX4X4 mTran;
	ObjAppearanceDirection(m_Nav.dPosStatus, &m_mWorld);
	m_mWorldOld = m_mWorld;
	m_pBBox->m_mWorld = m_mWorld;                           

	m_bActive = TRUE;	// 敵的オブジェクト

	m_nHp = m_nMaxHp;



	return TRUE;

}

//-----------------------------------------------------------------------------  
// 敵的オブジェクトの制御
//
//　キーボードで敵を動かす
//　敵のアニメーション、ジャンプ、自然落下
//　ワールド座標変換、マップとの接触判定
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmTargetSkillObj::Update()
{
	if (!m_bActive) return;  // 非表示のときは処理をしない

	// 変数の初期化   ---------------------------------------
	m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
	m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
	m_mWorldOld = m_mWorld;  // 一つ前の位置

	// ステータスごとの処理  --------------------------------
	switch (m_dwStatus)
	{
	case  FLASH: // 敵がダメージから復帰したときの処理。breakをつけずに次のNORMALを行う。
	case  NORMAL: // 敵が通常状態のときの処理
		UpdateNormal();
		break;

	case  DAMAGE: // 敵がダメージ状態のときの処理
		UpdateDamage();
		if (m_dwPlayerNo == FIRSTPLAYER)m_pGMain->m_nScore = m_pGMain->m_nScore + m_dwScorePoint;
		if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_nScoreSec = m_pGMain->m_nScoreSec + m_dwScorePoint;

		break;

	case  DEAD:	// 敵が死亡状態のときの処理
		UpdateDead();
		break;
	}


	// 描画処理  ---------------------------------------------
	//画面外なら描画しない
	VECTOR3 vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProj, m_pGMain->m_mView, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == FIRSTPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
	}
	vSPos = XMVector3Project(VECTOR3(0, 0, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1, m_pGMain->m_mProjSecond, m_pGMain->m_mViewSecond, m_mWorld);
	if ((vSPos.x >= (-10) && vSPos.x <= WINDOW_WIDTH + 10) && (vSPos.y >= (-10) && vSPos.y <= WINDOW_HEIGHT + 10)) {
		if (m_dwPlayerNo == SECONDPLAYER)m_pMesh->RenderToon(m_AnimStatus, m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);	
	}


	// バウンディングボックス
	m_pBBox->m_mWorld = m_mWorld;


}

//-----------------------------------------------------------------------------   
// 敵的オブジェクトの制御
//
// 敵が通常状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmTargetSkillObj::UpdateNormal()
{

	MATRIX4X4 mPos;
	MATRIX4X4 mTemp;

	if (m_dwStatus == FLASH)m_dwStatus = NORMAL;
	mPos = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);    // 直進処理のみ

	m_mWorld = mPos * m_mWorld;

}

//-----------------------------------------------------------------------------   
// 敵的オブジェクトの制御
//
// 敵がダメージ状態のときの処理
//
//   引数　　　なし
//
//
//-----------------------------------------------------------------------------
void	CEnmTargetSkillObj::UpdateDamage()
{
	m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_dwPlayerNo, m_vHitNormal);	// パーティクルの発生
	m_dwStatus = DEAD;		// HPが０なので死亡へ


}
//-----------------------------------------------------------------------------  
// 敵的オブジェクトの制御
//
// 敵が死亡状態のときの処理
//
//   引数　　　なし
//
//-----------------------------------------------------------------------------
void	CEnmTargetSkillObj::UpdateDead()
{
	ObjBasicDelete();
	if (m_dwPlayerNo == FIRSTPLAYER)m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->SetMaxWaitTime();
	if (m_dwPlayerNo == SECONDPLAYER)m_pGMain->m_pEnmProc->m_pEnmTargetSkillProc->SetMaxWaitTimeSec();
	SkillGetPc();
}

//-----------------------------------------------------------------------------  
// 敵的オブジェクトの制御
//
// プレイヤーにスキルを持たせる
//
//   引数　　　なし
//
//-----------------------------------------------------------------------------
void	CEnmTargetSkillObj::SkillGetPc()
{
	int SkillNoRan = Random(WEAPON_DIV, WEAPON_SKILLSPEEDUP);
	//出現時間を設定する
	if (m_dwPlayerNo == FIRSTPLAYER)
	{
		if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetWeaponColumanNo(0) == 0)m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColumanNo(0, SkillNoRan);

	}
	if (m_dwPlayerNo == SECONDPLAYER)
	{
		if (m_pGMain->m_pPcProc->GetPcSecObjPtr()->GetWeaponColumanNo(0) == 0)m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetWeaponColumanNo(0, SkillNoRan);

	}

}

