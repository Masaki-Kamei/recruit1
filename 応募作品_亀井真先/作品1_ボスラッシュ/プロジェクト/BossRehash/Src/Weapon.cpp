//=============================================================================
//
//      武器の処理
//																Weapon.cpp
//=============================================================================

#include "Weapon.h"
#include "Playchar.h"
#include "Enemy.h"
#include "Map.h"
#include "Effect.h"


//=============================================================================================================================
//
// 武器メインプロシージャのコンストラクタ
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
// ----------------------------------------------------------------------------------------------------------------------------
CWeaponProc::CWeaponProc(CGameMain* pGMain) : CBaseProc(pGMain)
{

	m_pWeaponShotProc = new CWeaponShotProc(m_pGMain);	// 武器・ショットプロシージャ
	m_pProcArray.push_back(m_pWeaponShotProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponShieldProc = new CWeaponShieldProc(m_pGMain);	// 武器・シールドプロシージャ
	m_pProcArray.push_back(m_pWeaponShieldProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponBoomProc = new CWeaponBoomProc(m_pGMain);	// 武器・爆弾プロシージャ
	m_pProcArray.push_back(m_pWeaponBoomProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponProAtkProc = new CWeaponProAtkProc(m_pGMain);	// 武器・近接攻撃プロシージャ
	m_pProcArray.push_back(m_pWeaponProAtkProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponDifShotProc = new CWeaponDifShotProc(m_pGMain);	// 武器・拡散ショットプロシージャ
	m_pProcArray.push_back(m_pWeaponDifShotProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponCharShotProc = new CWeaponCharShotProc(m_pGMain);	// 武器・チャージショットプロシージャ
	m_pProcArray.push_back(m_pWeaponCharShotProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponBoundShotProc = new CWeaponBoundShotProc(m_pGMain);	// 武器・バウンドショットプロシージャ
	m_pProcArray.push_back(m_pWeaponBoundShotProc);     // プロシージャをプロシージャ配列に登録する



	m_pWeaponSpWolfShotProc = new CWeaponSpWolfShotProc(m_pGMain);	// 武器・オオカミスペシャルショットプロシージャ
	m_pProcArray.push_back(m_pWeaponSpWolfShotProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponWolfShotProc = new CWeaponWolfShotProc(m_pGMain);	// 武器・オオカミショットプロシージャ
	m_pProcArray.push_back(m_pWeaponWolfShotProc);     // プロシージャをプロシージャ配列に登録する



	m_pWeaponFoxShotProc = new CWeaponFoxShotProc(m_pGMain);	// 武器・キツネショットプロシージャ
	m_pProcArray.push_back(m_pWeaponFoxShotProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponFoxSubShotProc = new CWeaponFoxSubShotProc(m_pGMain);	// 武器・キツネサブショットプロシージャ
	m_pProcArray.push_back(m_pWeaponFoxSubShotProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponFoxSpShotProc = new CWeaponFoxSpShotProc(m_pGMain);	// 武器・キツネスペシャルショットプロシージャ
	m_pProcArray.push_back(m_pWeaponFoxSpShotProc);     // プロシージャをプロシージャ配列に登録する



	m_pWeaponTordBrownShotProc = new CWeaponTordBrownShotProc(m_pGMain);	// 武器・がま茶色ショットプロシージャ
	m_pProcArray.push_back(m_pWeaponTordBrownShotProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponTordBrownSpShotProc = new CWeaponTordBrownSpShotProc(m_pGMain);	// 武器・がま茶色スペシャルショットプロシージャ
	m_pProcArray.push_back(m_pWeaponTordBrownSpShotProc);     // プロシージャをプロシージャ配列に登録する


	m_pWeaponTordShotProc = new CWeaponTordShotProc(m_pGMain);	// 武器・がまショットプロシージャ
	m_pProcArray.push_back(m_pWeaponTordShotProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponTordSpShotProc = new CWeaponTordSpShotProc(m_pGMain);	// 武器・がまスペシャルショットプロシージャ
	m_pProcArray.push_back(m_pWeaponTordSpShotProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponTordSubShotProc = new CWeaponTordSubShotProc(m_pGMain);	// 武器・がまサブショットプロシージャ
	m_pProcArray.push_back(m_pWeaponTordSubShotProc);     // プロシージャをプロシージャ配列に登録する



	m_pEnmLastSubShotProc = new CEnmLastSubShotProc(m_pGMain);	// 武器・最後の敵サブショットプロシージャ
	m_pProcArray.push_back(m_pEnmLastSubShotProc);     // プロシージャをプロシージャ配列に登録する

	m_pWeaponLaserProc = new CWeaponLaserProc(m_pGMain);	// 武器・レーザープロシージャ
	m_pProcArray.push_back(m_pWeaponLaserProc);     // プロシージャをプロシージャ配列に登録する

	m_pEnmLastSpShotProc = new CEnmLastSpShotProc(m_pGMain);	// 武器・最後の敵スペシャルショットプロシージャ
	m_pProcArray.push_back(m_pEnmLastSpShotProc);     // プロシージャをプロシージャ配列に登録する

	m_pEnmLastSpSubShotProc = new CEnmLastSpSubShotProc(m_pGMain);	// 武器・最後の敵スペシャルサブショットプロシージャ
	m_pProcArray.push_back(m_pEnmLastSpSubShotProc);     // プロシージャをプロシージャ配列に登録する

} 


// ================================================================================================================================
// 
// 各敵プロシージャ毎の処理
// 
// ================================================================================================================================

//------------------------------------------------------------------------
//
//	武器・ショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponShotProc::CWeaponShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・ショット
	for (DWORD i = 0; i < WEAPON_SHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponShotObj(m_pGMain));	// m_pObjArrayに武器・ショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・ショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・ショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponShotObj::CWeaponShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite4, 0, 480, 24, 24);
	m_nAnimNum = 1;

	m_nAtc = 40;
}
// ---------------------------------------------------------------------------
//
// 武器・ショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponShotObj::~CWeaponShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・ショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// 弾の速さ
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_vSitPos = m_vPos.x;

	switch(pObj->GetDirIdx() )
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed,0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed,0);
		break;
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・ショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponShotObj::Update()
{
	
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
			case  NORMAL:
				if (m_dwOwner == PC) // PCが発射した弾
				{
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);


				}
				else { //  敵が発射した弾
					m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
					

				}
				if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
				{
					m_bActive = FALSE;
				}

				if (m_vPos.x-m_pGMain->m_vScroll.x < 0 || m_vPos.x-m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
					m_vPos.y-m_pGMain->m_vScroll.y < 0 || m_vPos.y-m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
					m_bActive = FALSE;
				}
				if (m_vPos.x >= m_vSitPos + 350 || m_vPos.x <= m_vSitPos - 350)		//射程
				{
					m_bActive = FALSE;
				}
				break;

			case  DAMAGE:
				m_bActive = FALSE;
				
				break;
		}
		
		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}

//------------------------------------------------------------------------
//
//	武器・シールドプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponShieldProc::CWeaponShieldProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・シールド
	for (DWORD i = 0; i < WEAPON_SHIELD_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponShieldObj(m_pGMain));	// m_pObjArrayに武器・シールドオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・シールドプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponShieldProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・シールドオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponShieldObj::CWeaponShieldObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain-> m_pImageSprite2, 48, 320, 16, 32,16,74);
	m_nAnimNum = 1;

	m_nAtc = 100;
}
// ---------------------------------------------------------------------------
//
// 武器・シールドオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponShieldObj::~CWeaponShieldObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・シールドオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponShieldObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 0;	// 弾の速さ


	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	if (m_pGMain->m_nDirection == 0)
	{
		m_vPos.x = m_pGMain->m_nPcpositionx + 50.0f;
		m_vPos.y = m_pGMain->m_nPcpositiony-10;

	}
	else if (m_pGMain->m_nDirection==1)
	{
		m_vPos.x = m_pGMain->m_nPcpositionx - 30.0f;
		m_vPos.y = m_pGMain->m_nPcpositiony - 10;

	}

	m_vPosUp = VECTOR2(0, 0);

	switch (pObj->GetDirIdx())
	{
	case UP:
		break;
	case DOWN:
		break;
	case RIGHT:
		//m_nDirection = 0;

		break;
	case LEFT:
		//m_vPosUp = VECTOR2(-fSpeed, 0);
		//m_nDirection = 1;

		break;


	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・シールドオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponShieldObj::Update()
{
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:

			if (m_pGMain->m_nShieldStop == 0) {	//離したら消去
				m_bActive = FALSE;
			}
			
			if (m_pGMain->m_nDirection == 0)
			{
				m_vPos.x = m_pGMain->m_nPcpositionx + 50.0f;
				m_vPos.y = m_pGMain->m_nPcpositiony - 13;

			}
			else if (m_pGMain->m_nDirection == 1)
			{
				m_vPos.x = m_pGMain->m_nPcpositionx - 30.0f;
				m_vPos.y = m_pGMain->m_nPcpositiony - 13;

			}
			break;
		case  DAMAGE:
			//m_bActive = FALSE;
			m_dwStatus = NORMAL;
			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}
//------------------------------------------------------------------------
//
//	武器・爆弾 プロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponBoomProc::CWeaponBoomProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・爆弾
	for (DWORD i = 0; i < WEAPON_BOOM_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponBoomObj(m_pGMain));	// m_pObjArrayに武器・爆弾オブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・爆弾プロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponBoomProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・爆弾オブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponBoomObj::CWeaponBoomObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite2, 768, 416, 32, 14);
	m_nAnimNum = 1;

	m_nAtc = 150;
}
// ---------------------------------------------------------------------------
//
// 武器・爆弾オブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponBoomObj::~CWeaponBoomObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・爆弾オブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponBoomObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	m_vOf = VECTOR2(0, 0);
	m_vTarget = VECTOR2(0, 0);
	m_vPosUp = VECTOR2(0, 0);

	m_pSprite->SetSrc(768, 416, 32, 14);
	m_fRotate = 0.0f;
	m_fScale = 1.0f;
	m_fAlpha = 1.0f;
	BoomRangeHit = 0;

	m_nHp = m_nMaxHp;

	m_nCnt1 = 0;
	m_nCnt2 = 0;



	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・爆弾オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponBoomObj::Update()
{
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			switch (m_dwStatusPhase)
			{
			case 0:
				if (m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this)||m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this)|| m_pGMain->m_pWeaponProc->m_pWeaponShotProc->Hitcheck((CBaseObj*)this)|| m_pGMain->m_pWeaponProc->m_pWeaponCharShotProc->Hitcheck((CBaseObj*)this)|| m_pGMain->m_pWeaponProc->m_pWeaponDifShotProc->Hitcheck((CBaseObj*)this)|| m_pGMain->m_pWeaponProc->m_pWeaponBoundShotProc->Hitcheck((CBaseObj*)this)|| m_pGMain->m_pWeaponProc->m_pWeaponProAtkProc->Hitcheck((CBaseObj*)this))
				{   
					BoomRangeHit=1;
					// 敵に当たったら
					m_vPos.x -= ((64 - 32) / 2);   // 爆発スプライトに変更
					m_vPos.y -= ((64 - 14) / 2);   // 爆発スプライトに変更
					ResetAnim();
					m_pSprite->SetSrc(512, 448, 64, 64);
					m_fAlpha = 0.7f;
					m_fScale = 1.0f;
					m_nAnimNum = 2;
					m_nHp = 0;
					m_pOtherObj = NULL;
					m_dwStatusPhase = 1;   // 爆発処理へ
				}
				break;

			case 1:
				m_fScale += 0.25;     // 爆発をすこしづつ拡大していく
				if (m_fScale > 5) {
					m_bActive = false;
				}
				m_vOf.x = -(m_fScale * m_pSprite->GetSrcWidth() / 2);     // 拡大に合わせて表示位置をづらしていく
				m_vOf.y = -(m_fScale * m_pSprite->GetSrcHeight() / 2);
				break;
			}

			// 増分の計算
			m_vPos += m_vPosUp;

			if (m_dwOwner == PC) // PCが発射した弾
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				if (BoomRangeHit == 1) {
					m_pGMain->m_pWeaponProc->m_pWeaponBoomProc->Hitcheck((CBaseObj*)this);
				}
			}
			else { //  敵が発射した弾
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				//m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}

			if (m_vPos.x < 0 || m_vPos.x > WINDOW_WIDTH ||
				m_vPos.y < 0 || m_vPos.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}
			

			if (m_pGMain->m_nBoomStop == 1) {
				m_bActive = FALSE;
			}

		case  DAMAGE:
			m_dwStatus = NORMAL;
			break;
		}
		AnimCountup();
		Draw();
	}
}

//------------------------------------------------------------------------
//
//	武器・近接攻撃プロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponProAtkProc::CWeaponProAtkProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・近接攻撃
	for (DWORD i = 0; i < WEAPON_PROATK_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponProAtkObj(m_pGMain));	// m_pObjArrayに武器・近接攻撃オブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・近接攻撃プロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponProAtkProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・近接攻撃オブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponProAtkObj::CWeaponProAtkObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 396, 24, 24);
	m_nAnimNum = 1;

	m_nAtc = 70;
}
// ---------------------------------------------------------------------------
//
// 武器・近接攻撃オブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponProAtkObj::~CWeaponProAtkObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・近接攻撃オブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponProAtkObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// 弾の速さ
	//int Time = 1000;


	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);

	if (m_pGMain->m_nDirection == 0)
	{
		m_vPos.x = m_pGMain->m_nPcpositionx + 50.0f;
		m_vPos.y = m_pGMain->m_nPcpositiony + 10;
	}
	else if (m_pGMain->m_nDirection == 1)
	{
		m_vPos.x = m_pGMain->m_nPcpositionx - 30.0f;
		m_vPos.y = m_pGMain->m_nPcpositiony + 10;

	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・近接攻撃オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponProAtkObj::Update()
{
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			/*if (m_pGMain->m_nProAtkStop == 0) 
			{
				m_bActive = FALSE;
			}*/
			if (m_pGMain->m_nProAtkStop==1) 
			{
				if (TimeSave <= 1) 
				{
					Time++;
					TimeSave = Time / 10;
					
				}
				else {
					m_bActive = FALSE;
					Time = 0;
					TimeSave = 0;
					m_pGMain->m_nProAtkStop = 0;
				}
				
			}
			if (m_pGMain->m_nDirection == 0)
			{
				m_vPos.x = m_pGMain->m_nPcpositionx + 50.0f;
				m_vPos.y = m_pGMain->m_nPcpositiony + 10;
			}
			else if (m_pGMain->m_nDirection == 1)
			{
				m_vPos.x = m_pGMain->m_nPcpositionx - 30.0f;
				m_vPos.y = m_pGMain->m_nPcpositiony + 10;

			}

			if (m_dwOwner == PC) // PCが発射した弾
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  敵が発射した弾
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}

			break;

		case  DAMAGE:
			m_bActive = FALSE;
			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}

//------------------------------------------------------------------------
//
//	武器・拡散ショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponDifShotProc::CWeaponDifShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・拡散ショット
	for (DWORD i = 0; i < WEAPON_DIFSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponDifShotObj(m_pGMain));	// m_pObjArrayに武器・ショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 32;

}

//-----------------------------------------------------------------------------
// 武器・拡散ショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponDifShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;
	DWORD  dwNum;

	

	dwNum = 4;
	for (DWORD n = 0; n < dwNum; n++)
	{

		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				((CWeaponDifShotObj*)(m_pObjArray[i]))->Start(vPos, pObj,n, dwOwner);	// 武器の発生

				m_pGMain->m_pSeHit->Play();
				bRet = TRUE;
				break;
			}
		}

	}

	
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・拡散ショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponDifShotObj::CWeaponDifShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 48, 320, 16, 32);
	m_nAnimNum = 1;

	m_nAtc = 20;
}
// ---------------------------------------------------------------------------
//
// 武器・拡散ショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponDifShotObj::~CWeaponDifShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・拡散ショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponDifShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwNo,  DWORD dwOwner)
{
	float fSpeed = 8;	// 弾の速さ

	

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置

	switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		
		m_vPosUp.x = -sin(XMConvertToRadians(dwNo * 12.0f - 102)) * fSpeed;
		m_vPosUp.y = cos(XMConvertToRadians(dwNo * 12.0f - 102)) * fSpeed;
		m_fRotate = dwNo * 12.0f - 102;

		break;
	case LEFT:
		m_vPosUp.x = -sin(XMConvertToRadians(dwNo * 12.0f - 102)) * -fSpeed;
		m_vPosUp.y = cos(XMConvertToRadians(dwNo * 12.0f - 102)) * -fSpeed;
		m_fRotate = dwNo * 12.0f - 102;

		break;
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・拡散ショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponDifShotObj::Update()
{



	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:

			if (m_dwOwner == PC) // PCが発射した弾
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  敵が発射した弾
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				m_nAtc = 100;

			}
			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}
			
			break;

		case  DAMAGE:
			m_bActive = FALSE;
			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}

//------------------------------------------------------------------------
//
//	武器・チャージショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponCharShotProc::CWeaponCharShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・チャージショット
	for (DWORD i = 0; i < WEAPON_CHARSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponCharShotObj(m_pGMain));	// m_pObjArrayに武器・ショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・チャージショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponCharShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・チャージショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponCharShotObj::CWeaponCharShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 40;
}
// ---------------------------------------------------------------------------
//
// 武器・チャージショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponCharShotObj::~CWeaponCharShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・チャージショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponCharShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// 弾の速さ

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	
	m_vSitPos = m_vPos.x;

	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:		
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・チャージショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponCharShotObj::Update()
{
	int CharShot = 0;
	float fSpeed = 8;	// 弾の速さ

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  NORMAL:
			if (m_pGMain->m_nCharEnmhit == 1) 
			{
			if (m_dwOwner == PC) // PCが発射した弾
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);


			}
			else { //  敵が発射した弾
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


			}
			}
			if (m_pGMain->m_nCharStop == 0)
			{
				if (m_pGMain->m_nDirection == 0)
				{
					m_vPos.x = m_pGMain->m_nPcpositionx + 50.0f;
					m_vPos.y = m_pGMain->m_nPcpositiony + 10;
					m_vPosUp = VECTOR2(fSpeed, 0);

				}
				else if (m_pGMain->m_nDirection == 1)
				{
					m_vPos.x = m_pGMain->m_nPcpositionx - 30.0f;
					m_vPos.y = m_pGMain->m_nPcpositiony + 10;
					m_vPosUp = VECTOR2(-fSpeed, 0);

				}

			}
				if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
				{
					m_pGMain->m_nCharStop = 0;
					m_bActive = FALSE;

				}
			
			if (m_pGMain->m_nCharAmount >= 0)
			{
				CharShot = 0;
				CharShot = m_pGMain->m_nCharAmountSave/15;
					if (CharShot <= 3)
					{
						m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);
						m_nAtc = 50;
					}
					else {
						m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34, 32, 32);
						m_nAtc = 100;
					
				}
			}
			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_pGMain->m_nCharStop = 0;
				m_pGMain->m_nCharAmountSave = 0;
				m_pGMain->m_nCharAmount = 0;


				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_pGMain->m_nCharStop = 0;


				m_bActive = FALSE;
			

			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}

//========================================================================
//	武器・バウンドショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponBoundShotProc::CWeaponBoundShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・バウンドショット
	for (DWORD i = 0; i < WEAPON_BOUNDSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponBoundShotObj(m_pGMain));	// m_pObjArrayに武器・バウンドショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・バウンドショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponBoundShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・バウンドショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponBoundShotObj::CWeaponBoundShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 194, 417, 30, 30);
	m_nAnimNum = 1;

	m_nAtc = 20;
}
// ---------------------------------------------------------------------------
//
// 武器・バウンドショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponBoundShotObj::~CWeaponBoundShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・バウンドショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponBoundShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// 弾の速さ
	fSpeedx = 0;
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_vSitPos = m_vPos.x;
	BoundNum = 1;
	y = 0;

	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・バウンドショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponBoundShotObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;


	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:



			if (m_dwOwner == PC) // PCが発射した弾
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  敵が発射した弾
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


			}

			if(m_pGMain->m_nDirection == 0)
			{
				fSpeedx=1.5;
			}
			else if (m_pGMain->m_nDirection == 1)
			{
				fSpeedx = -1.5;

			}


			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}


		switch (m_dwStatusSub) {

		case  WALK:


			// ジャンプ開始
			if (BoundNum == 1) {
				m_dwStatusSub = JUMP;
				m_vPosUp.x = fSpeedx;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -(fJumpSpeed + (fJumpPlus/3));
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}else if (BoundNum == 2) {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -y*0.75;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}
			else if (BoundNum == 3) {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -y*0.75;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y/2;
				//m_nDirIdx = UP;
			}

			else {
				m_bActive = FALSE;
			}


			break;

		case  JUMP:		// ジャンプ中の処理
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + (GRAVITY/6) * m_fJumpTime);
			y = m_vPosUp.y;
			break;

		}
	}
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// マップ線が垂直まではＯＫ
		{
			m_dwStatusSub = WALK;	// マップ線に接触しているときは、ジャンプを歩行に戻す
			BoundNum++;
		}
	}
	
	// 増分
	m_vPos += m_vPosUp;

	AnimCountup();
	Draw();


}



//------------------------------------------------------------------------
//
//	武器・オオカミスペシャルプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponSpWolfShotProc::CWeaponSpWolfShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・オオカミスペシャルショット
	for (DWORD i = 0; i < WEAPON_SPWOLFSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponSpWolfShotObj(m_pGMain));	// m_pObjArrayに武器・ショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 32;

}

//-----------------------------------------------------------------------------
// 武器・オオカミスペシャルショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponSpWolfShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;
	DWORD  dwNum;



	dwNum = 25;
	for (DWORD n = 0; n < dwNum; n++)
	{

		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				((CWeaponSpWolfShotObj*)(m_pObjArray[i]))->Start(vPos, pObj, n, dwOwner);	// 武器の発生

				m_pGMain->m_pSeHit->Play();
				bRet = TRUE;
				break;
			}
		}

	}


	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・オオカミスペシャルショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponSpWolfShotObj::CWeaponSpWolfShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 48, 320, 16, 32);
	m_nAnimNum = 1;

	m_nAtc = 80;
}
// ---------------------------------------------------------------------------
//
// 武器・オオカミスペシャルショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponSpWolfShotObj::~CWeaponSpWolfShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・オオカミショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponSpWolfShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwNo, DWORD dwOwner)
{
	float fSpeed =6;	// 弾の速さ



	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置

	switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:

		m_vPosUp.x = -sin(XMConvertToRadians(dwNo * 15.0f - 102)) * fSpeed;
		m_vPosUp.y = cos(XMConvertToRadians(dwNo * 15.0f - 102)) * fSpeed;
		m_fRotate = dwNo * 12.0f - 102;

		break;
	case LEFT:
		m_vPosUp.x = -sin(XMConvertToRadians(dwNo * 15.0f - 102)) * -fSpeed;
		m_vPosUp.y = cos(XMConvertToRadians(dwNo * 15.0f - 102)) * -fSpeed;
		m_fRotate = dwNo * 15.0f - 102;

		break;
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・オオカミスペシャルショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponSpWolfShotObj::Update()
{



	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			if (m_dwOwner == PC) // PCが発射した弾
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  敵が発射した弾
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


			}
			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}

			break;

		case  DAMAGE:
			m_bActive = FALSE;
			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}

//------------------------------------------------------------------------
//
//	武器・オオカミショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponWolfShotProc::CWeaponWolfShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・オオカミショット
	for (DWORD i = 0; i < WEAPON_DIFSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponWolfShotObj(m_pGMain));	// m_pObjArrayに武器・ショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 32;

}

//-----------------------------------------------------------------------------
// 武器・オオカミショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponWolfShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;
	DWORD  dwNum;



	dwNum = 4;
	for (DWORD n = 0; n < dwNum; n++)
	{

		for (DWORD i = 0; i < m_pObjArray.size(); i++)
		{
			if (!m_pObjArray[i]->GetActive())
			{
				((CWeaponWolfShotObj*)(m_pObjArray[i]))->Start(vPos, pObj, n, dwOwner);	// 武器の発生

				m_pGMain->m_pSeHit->Play();
				bRet = TRUE;
				break;
			}
		}

	}


	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・オオカミショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponWolfShotObj::CWeaponWolfShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 48, 320, 16, 32);
	m_nAnimNum = 1;


	m_nAtc = 80;
}
// ---------------------------------------------------------------------------
//
// 武器・オオカミショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponWolfShotObj::~CWeaponWolfShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・オオカミショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponWolfShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwNo, DWORD dwOwner)
{
	float fSpeed = 8;	// 弾の速さ



	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置

	switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:

		m_vPosUp.x = -sin(XMConvertToRadians(dwNo * 12.0f - 102)) * fSpeed;
		m_vPosUp.y = cos(XMConvertToRadians(dwNo * 12.0f - 102)) * fSpeed;
		m_fRotate = dwNo * 12.0f - 102;

		break;
	case LEFT:
		m_vPosUp.x = -sin(XMConvertToRadians(dwNo * 12.0f - 102)) * -fSpeed;
		m_vPosUp.y = cos(XMConvertToRadians(dwNo * 12.0f - 102)) * -fSpeed;
		m_fRotate = dwNo * 12.0f - 102;

		break;
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・オオカミショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponWolfShotObj::Update()
{



	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			if (m_dwOwner == PC) // PCが発射した弾
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  敵が発射した弾
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				m_nAtc = 100;

			}
			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}

			break;

		case  DAMAGE:
			m_bActive = FALSE;
			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}


//------------------------------------------------------------------------
//
//	武器・フォックスショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponFoxShotProc::CWeaponFoxShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・フォックスショット
	for (DWORD i = 0; i < WEAPON_FOXSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponFoxShotObj(m_pGMain));	// m_pObjArrayに武器・ショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・フォックスショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponFoxShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・フォックスショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponFoxShotObj::CWeaponFoxShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 100;
}
// ---------------------------------------------------------------------------
//
// 武器・フォックスショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponFoxShotObj::~CWeaponFoxShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・フォックスショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponFoxShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// 弾の速さ

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置

//	m_vPos.x = Random(100,800);
//	m_vPos.y = Random(300, 730);

	m_vPosUp = VECTOR2(0, 0);

	m_vSitPos = m_vPos.x;
	CharShot = 0;
	CharMove = 0;


	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・フォックスショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponFoxShotObj::Update()
{
	float fSpeed = 8;	// 弾の速さ

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  NORMAL:
			if (m_vPosUp.x != 0|| m_vPosUp.y != 0) {
				if (m_dwOwner == PC) // PCが発射した弾
				{
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

				}
				else { //  敵が発射した弾
					m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


				}

			}

			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;

			}

			if (CharShot / 15 <= 3)
			{
				CharShot++;
				m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);
				if (CharShot / 15 > 2) {
					m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34, 32, 32);

				}
			}
			else {
				if (CharMove == 0) {
					
					/* if (m_vPos.y <= 600) 
					{
						m_vPosUp.y = fSpeed;

					}

					else */
					if (m_vPos.x <= m_pGMain->m_nPcpositionx)
					{
						m_vPosUp.x = fSpeed;
					}
					else {
						m_vPosUp.x = -fSpeed;

					}
					CharMove = 1;
				}
			}


			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去

				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}

//------------------------------------------------------------------------
//
//	武器・フォックスサブショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponFoxSubShotProc::CWeaponFoxSubShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・フォックスサブショット
	for (DWORD i = 0; i < WEAPON_FOXSUBSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponFoxSubShotObj(m_pGMain));	// m_pObjArrayに武器・ショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・フォックスサブショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponFoxSubShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・フォックスサブショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponFoxSubShotObj::CWeaponFoxSubShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 40;
}
// ---------------------------------------------------------------------------
//
// 武器・フォックスサブショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponFoxSubShotObj::~CWeaponFoxSubShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・フォックスサブショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponFoxSubShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// 弾の速さ

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置

	m_vPos.x = Random(100,800);
	m_vPos.y = Random(300, 500);

	m_vPosUp = VECTOR2(0, 0);

	m_vSitPos = m_vPos.x;
	CharShot = 0;
	CharMove = 0;


	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・フォックスサブショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponFoxSubShotObj::Update()
{
	float fSpeed = 8;	// 弾の速さ

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  NORMAL:
			if (m_vPosUp.x != 0 || m_vPosUp.y != 0) {
				if (m_dwOwner == PC) // PCが発射した弾
				{
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

				}
				else { //  敵が発射した弾
					m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


				}

			}

			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;

			}

			if (CharShot / 15 <= 3)
			{
				CharShot++;
				m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);

			}
			else {
				if (CharMove == 0) {
					m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34, 32, 32);
						m_vPosUp.y = fSpeed;


					CharMove = 1;
				}
			}


			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去

				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}


//------------------------------------------------------------------------
//
//	武器・フォックススペシャルショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponFoxSpShotProc::CWeaponFoxSpShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・フォックススペシャルショット
	for (DWORD i = 0; i < WEAPON_FOXSPSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponFoxSpShotObj(m_pGMain));	// m_pObjArrayに武器・ショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・フォックススペシャルショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponFoxSpShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・フォックススペシャルショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponFoxSpShotObj::CWeaponFoxSpShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 100;
}
// ---------------------------------------------------------------------------
//
// 武器・フォックススペシャルショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponFoxSpShotObj::~CWeaponFoxSpShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・フォックススペシャルショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponFoxSpShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// 弾の速さ

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置

	


	m_vPosUp = VECTOR2(0, 0);

	//m_vSitPos = m_vPos.x;
	CharShot = 0;
	PosxSave = m_vPos.x;
	PosySave = m_vPos.y;
	WeponNumx= 0;
	WeponNumy = 0;
	PcPosxSave = 0;
	PcPosySave = 0;
	SpCharMove = m_pGMain->m_nSpCharMove;
	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・フォックススペシャルショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponFoxSpShotObj::Update()
{
	float fSpeed = 8;	// 弾の速さ

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  NORMAL:



			if (m_vPosUp.x != 0 || m_vPosUp.y != 0) {
				if (m_dwOwner == PC) // PCが発射した弾
				{
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

				}
				else { //  敵が発射した弾
					m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


				}

			}

			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;

			}

			if (CharShot <= SpCharMove)
			{
				CharShot++;
				m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);
				PcPosxSave = m_pGMain->m_nPcpositionx;
				PcPosySave = m_pGMain->m_nPcpositiony;
				if (CharShot > SpCharMove-15) {
					m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34, 32, 32);

				}

			}
			else {

					/*/m_vPosUp.y = fSpeed;
					/if (PcPosySave >= PosySave) {
						//WeponNumy = ((PosySave / (PcPosySave / 100)) / 100);
						m_vPosUp.y = fSpeed;
					}
					else if(PcPosySave < PosySave) {
						//WeponNumy = ((PcPosySave / (PosySave / 100)) / 100);
						m_vPosUp.y = -fSpeed;

					}
					if (PcPosxSave >= PosxSave) {
						WeponNumx = ((PosxSave / (PcPosxSave / 100)) / 100);

					}
					else if (PcPosxSave < PosxSave) {
						WeponNumx = ((PcPosxSave / (PosxSave / 100)) / 100);
					}
					//m_vPosUp.y = ((PcPosySave - PosySave) / 30)*(WeponNumy);
					m_vPosUp.x = ((PcPosxSave - PosxSave) / 30)*(WeponNumx);*/
					/*x = ((PcPosxSave - PosxSave) / 2);
					y = ((PcPosySave - PosySave) / 2);

					m_vPosUp.y = ((PcPosySave - PosySave) / y);
					m_vPosUp.x = ((PcPosxSave - PosxSave) / x);*/
					

					float tan = atan2(PcPosySave- PosySave, PcPosxSave - PosxSave);
				
					m_vPosUp.x= cos(tan)*fSpeed;
					m_vPosUp.y = sin(tan)*fSpeed;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < -300 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH +300||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT+300) {	// 画面外へ出たので消去

				m_bActive = FALSE;
			}



			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}

//------------------------------------------------------------------------
//
//	武器・がま茶色ショット プロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponTordBrownShotProc::CWeaponTordBrownShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・がま茶色ショット
	for (DWORD i = 0; i < WEAPON_TORDBROWNSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponTordBrownShotObj(m_pGMain));	// m_pObjArrayに武器・がま茶色ショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・がま茶色ショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordBrownShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・がま茶色ショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponTordBrownShotObj::CWeaponTordBrownShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite2, 768, 416, 32, 14);
	m_nAnimNum = 1;

	m_nAtc = 200;
}
// ---------------------------------------------------------------------------
//
// 武器・がま茶色ショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponTordBrownShotObj::~CWeaponTordBrownShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・がま茶色ショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordBrownShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	m_vOf = VECTOR2(0, 0);
	m_vTarget = VECTOR2(0, 0);
	m_vPosUp = VECTOR2(0, 0);

	m_pSprite->SetSrc(768, 416, 32, 14);
	m_fRotate = 0.0f;
	m_fScale = 1.0f;
	m_fAlpha = 1.0f;

	m_nHp = m_nMaxHp;
	BoomTime = 0;

	m_nCnt1 = 0;
	m_nCnt2 = 0;


	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・がま茶色ショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponTordBrownShotObj::Update()
{
	if (m_bActive)
	{
		int fSpeed = 8;
		switch (m_dwStatus)
		{
		case  NORMAL:

			switch (m_dwStatusPhase)
			{
			case 0:

				if (m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this) ||BoomTime/15>=10)
				{   // 敵に当たったら
					m_vPos.x -= ((64 - 32) / 2);   // 爆発スプライトに変更
					m_vPos.y -= ((64 - 14) / 2);   // 爆発スプライトに変更
					ResetAnim();
					m_pSprite->SetSrc(512, 448, 64, 64);
					m_fAlpha = 0.7f;
					m_fScale = 1.0f;
					m_nAnimNum = 2;
					m_nHp = 0;
					m_pOtherObj = NULL;
					m_dwStatusPhase = 1;   // 爆発処理へ
				}
				else if (m_pGMain->m_pWeaponProc->m_pWeaponShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponCharShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponDifShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponBoundShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponProAtkProc->Hitcheck((CBaseObj*)this))
				{
					EnmHit = 1;
					// 敵に当たったら
					m_vPos.x -= ((64 - 32) / 2);   // 爆発スプライトに変更
					m_vPos.y -= ((64 - 14) / 2);   // 爆発スプライトに変更
					ResetAnim();
					m_pSprite->SetSrc(512, 448, 64, 64);
					m_fAlpha = 0.7f;
					m_fScale = 1.0f;
					m_nAnimNum = 2;
					m_nHp = 0;
					m_pOtherObj = NULL;
					m_dwStatusPhase = 1;
				}
				BoomTime++;
				break;

			case 1:
				m_fScale += 0.15;     // 爆発をすこしづつ拡大していく
				if (m_fScale > 3.5) {
					m_bActive = false;
					EnmHit = 0;
				}
				m_vOf.x = -(m_fScale * m_pSprite->GetSrcWidth() / 2);     // 拡大に合わせて表示位置をづらしていく
				m_vOf.y = -(m_fScale * m_pSprite->GetSrcHeight() / 2);
				break;
			}

			// 増分の計算
			m_vPos += m_vPosUp;

			if (m_dwOwner == PC) // PCが発射した弾
			{
				//m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);
				//m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			}
			else { //  敵が発射した弾
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				if (EnmHit == 1) {
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);
					
				}
			}

			if (m_vPos.x < 0 || m_vPos.x > WINDOW_WIDTH ||
				m_vPos.y < 0 || m_vPos.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}
			if (m_pGMain->m_nDoorStop[3] == 1)
			{
				m_bActive = FALSE;
			}
		
			break;

		case  DAMAGE:
			m_dwStatus = NORMAL;
			break;
		}
		AnimCountup();
		Draw();
	}
}

//------------------------------------------------------------------------
//
//	武器・がま茶色スペシャルショット プロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponTordBrownSpShotProc::CWeaponTordBrownSpShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・がま茶色スペシャルショット
	for (DWORD i = 0; i < WEAPON_TORDBROWNSPSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponTordBrownSpShotObj(m_pGMain));	// m_pObjArrayに武器・がま茶色スペシャルショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・がま茶色スペシャルショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordBrownSpShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・がま茶色スペシャルショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponTordBrownSpShotObj::CWeaponTordBrownSpShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite2, 768, 416, 32, 14);
	m_nAnimNum = 1;

	m_nAtc = 200;
}
// ---------------------------------------------------------------------------
//
// 武器・がま茶色スペシャルショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponTordBrownSpShotObj::~CWeaponTordBrownSpShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・がま茶色スペシャルショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordBrownSpShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	m_vOf = VECTOR2(0, 0);
	m_vTarget = VECTOR2(0, 0);
	m_vPosUp = VECTOR2(0, 0);

	m_pSprite->SetSrc(768, 416, 32, 14);
	m_fRotate = 0.0f;
	m_fScale = 1.0f;
	m_fAlpha = 1.0f;

	m_nHp = m_nMaxHp;
	BoomTime = 0;

	m_nCnt1 = 0;
	m_nCnt2 = 0;
	 fSpeed = Random(2, 8);



	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・がま茶色スペシャルショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponTordBrownSpShotObj::Update()
{
	CMapLine*  pHitmapline = NULL;

	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:

			switch (m_dwStatusPhase)
			{
			case 0:

				if (m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this) )
				{   // 敵に当たったら

					m_vPosUp.x = 0;
					m_vPosUp.y = 0;
					m_vPos.x -= ((64 - 32) / 2);   // 爆発スプライトに変更
					m_vPos.y -= ((64 - 14) / 2);   // 爆発スプライトに変更
					ResetAnim();
					m_pSprite->SetSrc(512, 448, 64, 64);
					m_fAlpha = 0.7f;
					m_fScale = 1.0f;
					m_nAnimNum = 2;
					m_nHp = 0;
					m_pOtherObj = NULL;
					m_dwStatusPhase = 1;   // 爆発処理へ
				}
				else if (m_pGMain->m_pWeaponProc->m_pWeaponShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponCharShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponDifShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponBoundShotProc->Hitcheck((CBaseObj*)this) || m_pGMain->m_pWeaponProc->m_pWeaponProAtkProc->Hitcheck((CBaseObj*)this))
				{
					m_vPosUp.x = 0;
					m_vPosUp.y = 0;
					EnmHit = 1;
					// 敵に当たったら
					m_vPos.x -= ((64 - 32) / 2);   // 爆発スプライトに変更
					m_vPos.y -= ((64 - 14) / 2);   // 爆発スプライトに変更
					ResetAnim();
					m_pSprite->SetSrc(512, 448, 64, 64);
					m_fAlpha = 0.7f;
					m_fScale = 1.0f;
					m_nAnimNum = 2;
					m_nHp = 0;
					m_pOtherObj = NULL;
					m_dwStatusPhase = 1;
				}
				else if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
				{
					if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// マップ線が垂直まではＯＫ
					{
						m_vPosUp.x = 0;
						m_vPosUp.y = 0;
						// 敵に当たったら
						m_vPos.x -= ((64 - 32) / 2);   // 爆発スプライトに変更
						m_vPos.y -= ((64 - 14) / 2);   // 爆発スプライトに変更
						ResetAnim();
						m_pSprite->SetSrc(512, 448, 64, 64);
						m_fAlpha = 0.7f;
						m_fScale = 1.0f;
						m_nAnimNum = 2;
						m_nHp = 0;
						m_pOtherObj = NULL;
						m_dwStatusPhase = 1;

					}
				}


			
				break;

			case 1:
				m_fScale += 0.15;     // 爆発をすこしづつ拡大していく
				if (m_fScale > 3.5) {
					m_bActive = false;
					EnmHit = 0;
				}
				m_vOf.x = -(m_fScale * m_pSprite->GetSrcWidth() / 2);     // 拡大に合わせて表示位置をづらしていく
				m_vOf.y = -(m_fScale * m_pSprite->GetSrcHeight() / 2);
				break;
			}

			m_fRotate = 270;
			m_vPosUp.y = fSpeed;



			// 増分の計算
			m_vPos += m_vPosUp;

			if (m_dwOwner == PC) // PCが発射した弾
			{
				//m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);
				//m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			}
			else { //  敵が発射した弾
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				if (EnmHit == 1) {
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

				}
			}

			if (m_vPos.x < 0 || m_vPos.x > WINDOW_WIDTH ||
				m_vPos.y < 0 || m_vPos.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}
			if (m_pGMain->m_nDoorStop[3] == 1)
			{
				m_bActive = FALSE;
			}

			break;

		case  DAMAGE:
			m_dwStatus = NORMAL;
			break;
		}

		AnimCountup();
		Draw();
	}
}

//========================================================================
//	武器・ガマショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponTordShotProc::CWeaponTordShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・ガマショット
	for (DWORD i = 0; i < WEAPON_TORDSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponTordShotObj(m_pGMain));	// m_pObjArrayに武器・ガマショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・ガマショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・ガマショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponTordShotObj::CWeaponTordShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 194, 417, 30, 30);
	m_nAnimNum = 1;

	m_nAtc = 80;
}
// ---------------------------------------------------------------------------
//
// 武器・ガマショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponTordShotObj::~CWeaponTordShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・ガマショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	fSpeedx = 0;
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_vSitPos = m_vPos.x;
	BoundNum = 1;
	Boundy = 0;
	if (Random(0, 1) == 0) {
		fSpeedx = 1.5;
	}
	else {
		fSpeedx = -1.5;

	}
	switch (pObj->GetDirIdx())
	{
	/*case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;*/
	case RIGHT:
		fSpeedx = 1.5;
		break;
	case LEFT:
		fSpeedx = -1.5;
		break;
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・ガマショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponTordShotObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;


	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:



			if (m_dwOwner == PC) // PCが発射した弾
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  敵が発射した弾
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


			}



			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}


		switch (m_dwStatusSub) {

		case  WALK:


			// ジャンプ開始
			if (BoundNum == 1) {
				m_dwStatusSub = JUMP;
				m_vPosUp.x = fSpeedx;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -(fJumpSpeed + (fJumpPlus / 3));
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}
			else if (BoundNum == 2) {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -Boundy * 0.75;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}
			else if (BoundNum == 3) {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -Boundy * 0.75;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y / 2;
				//m_nDirIdx = UP;
			}

			else {
				m_bActive = FALSE;
			}


			break;

		case  JUMP:		// ジャンプ中の処理
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + (GRAVITY / 6) * m_fJumpTime);
			Boundy = m_vPosUp.y;
			break;

		}
	}
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// マップ線が垂直まではＯＫ
		{
			m_dwStatusSub = WALK;	// マップ線に接触しているときは、ジャンプを歩行に戻す
			BoundNum++;
		}
	}

	// 増分
	m_vPos += m_vPosUp;

	AnimCountup();
	Draw();


}

//========================================================================
//	武器・ガマスペシャルショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponTordSpShotProc::CWeaponTordSpShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・ガマスペシャルショット
	for (DWORD i = 0; i < WEAPON_TORDSPSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponTordSpShotObj(m_pGMain));	// m_pObjArrayに武器・ガマスペシャルショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・ガマスペシャルショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordSpShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・ガマスペシャルショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponTordSpShotObj::CWeaponTordSpShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 526, 0, 200, 200);
	m_nAnimNum = 1;

	m_nAtc = 80;
}
// ---------------------------------------------------------------------------
//
// 武器・ガマスペシャルショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponTordSpShotObj::~CWeaponTordSpShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・ガマスペシャルショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordSpShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	fSpeedx = 0;
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	m_vPos.y = m_vPos.y - 200;
	m_vPos.x = m_vPos.x - 100;
	m_vPosUp = VECTOR2(0, 0);
	m_vSitPos = m_vPos.x;
	BoundNum = 0;
	PcPosxSave = m_pGMain->m_nPcpositionx;
	PcPosySave = m_pGMain->m_nPcpositiony;
	BoundTimeStop = 0;
	tan = 0;
	fSpeed = 5;
	//BoundNumMax = Random(5, 8);
	BoundNumMax = 7;
	StageWidth = 768;
	StageHeight = 536;
	switch (pObj->GetDirIdx())
	{
		/*case UP:
			m_vPosUp = VECTOR2(0, -fSpeed);
			break;
		case DOWN:
			m_vPosUp = VECTOR2(0, fSpeed);
			break;*/
	/*case RIGHT:
		fSpeedx = 4;
		break;
	case LEFT:
		fSpeedx = -4;
		break;*/
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・ガマスペシャルショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponTordSpShotObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;


	if (m_bActive)
	{


			if (Random(0, 35) == 0)
			{
				if (m_nDifShotWait <= 0) {
						m_pGMain->m_pWeaponProc->m_pWeaponTordShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
						//m_pGMain->m_pWeaponProc->m_pWeaponTordSpShotProc->Start(m_vPos + VECTOR2(16, 16), this, ENM);
						m_nDifShotWait = 15;
					
				}
			}
			if (m_nDifShotWait > 0) m_nDifShotWait--;    // 武器発射のウェイトをカウントダウン
			



				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);

			



			/*if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}*/
			if (BoundNum == 0)
			{

					m_vPosUp.x = -fSpeed;
					m_vPosUp.y = fSpeed;
					BoundNum=1;

			}

			if (BoundNum == 1) {
				BoundTimeStop++;
			}

			if (BoundTimeStop/30 >10) {
				m_pGMain->m_nSpTordPosx = m_vPos.x;
				m_pGMain->m_nSpTordPosy = m_vPos.y;
				m_pGMain->m_nSpTordStop = 1;


			}
			if (m_pGMain->m_nSpTordStop == 1)
			{
				m_bActive = FALSE;

			}

		

		
		



	}






	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
			
				//m_vPosUp.x = 0;
				//m_vPosUp.y = 0;
		if (BoundTimeStop / 30 <= 10) {
			if(m_vPosUp.x >=0 && m_vPos.x >=840-200) {
				m_vPosUp.x = -fSpeed;
			}
			else if (m_vPosUp.x < 0 && m_vPos.x <= 110) {
				m_vPosUp.x = fSpeed;

			}			
			if (m_vPosUp.y >= 0 && m_vPos.y >= 750-200) {
				m_vPosUp.y = -fSpeed;
			}
			else if (m_vPosUp.y < 0 && m_vPos.y <= 250) {
				m_vPosUp.y = fSpeed;

			}



		}

		
	}


	// 増分
	m_vPos += m_vPosUp;

	AnimCountup();
	Draw();


}

//========================================================================
//	武器・ガマサブショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponTordSubShotProc::CWeaponTordSubShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・ガマサブショット
	for (DWORD i = 0; i < WEAPON_TORDSUBSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponTordSubShotObj(m_pGMain));	// m_pObjArrayに武器・ガマサブショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・ガマサブショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordSubShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・ガマサブショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponTordSubShotObj::CWeaponTordSubShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite3, 194, 417, 30, 30);
	m_nAnimNum = 1;

	m_nAtc = 80;
}
// ---------------------------------------------------------------------------
//
// 武器・ガマサブショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponTordSubShotObj::~CWeaponTordSubShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・ガマサブショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponTordSubShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	fSpeedx = 0;
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_vSitPos = m_vPos.x;
	BoundNum = 1;
	Boundy = 0;

	switch (pObj->GetDirIdx())
	{
		/*case UP:
			m_vPosUp = VECTOR2(0, -fSpeed);
			break;
		case DOWN:
			m_vPosUp = VECTOR2(0, fSpeed);
			break;*/
	case RIGHT:
		if (Random(0, 1) == 0) {
			fSpeedx = 1.5;
		}
		else {
			fSpeedx = -1.5;

		}
		break;
	case LEFT:
		if (Random(0, 1) == 0) {
			fSpeedx = 1.5;
		}
		else {
			fSpeedx = -1.5;

		}

		break;
	}

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・ガマサブショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponTordSubShotObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fJumpSpeed = 5;
	float fJumpPlus = 4;


	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:



			if (m_dwOwner == PC) // PCが発射した弾
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

			}
			else { //  敵が発射した弾
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


			}



			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}
			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}


		switch (m_dwStatusSub) {

		case  WALK:


			// ジャンプ開始
			if (BoundNum == 1) {
				m_dwStatusSub = JUMP;
				m_vPosUp.x = fSpeedx;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -(fJumpSpeed + (fJumpPlus / 3));
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}
			else if (BoundNum == 2) {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -Boundy * 0.75;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}
			else if (BoundNum == 3) {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -Boundy * 0.75;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y / 2;
				//m_nDirIdx = UP;
			}

			else {
				m_bActive = FALSE;
			}


			break;

		case  JUMP:		// ジャンプ中の処理
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + (GRAVITY / 6) * m_fJumpTime);
			Boundy = m_vPosUp.y;
			break;

		}
	}
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// マップ線が垂直まではＯＫ
		{
			m_dwStatusSub = WALK;	// マップ線に接触しているときは、ジャンプを歩行に戻す
			BoundNum++;
		}
	}

	// 増分
	m_vPos += m_vPosUp;

	AnimCountup();
	Draw();


}


//------------------------------------------------------------------------
//
//	武器・最後の敵サブショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEnmLastSubShotProc::CEnmLastSubShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・最後の敵サブショット
	for (DWORD i = 0; i < WEAPON_ENMLASTSUBSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmLastSubShotObj(m_pGMain));	// m_pObjArrayに武器・ショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・最後の敵サブショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSubShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・最後の敵サブショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEnmLastSubShotObj::CEnmLastSubShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 0, 480, 24, 24);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 40;
}
// ---------------------------------------------------------------------------
//
// 武器・最後の敵サブショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmLastSubShotObj::~CEnmLastSubShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・最後の敵サブショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSubShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 2;	// 弾の速さ

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置




	m_vPosUp = VECTOR2(0, 0);

	//m_vSitPos = m_vPos.x;
	CharShot = 0;
	PosxSave = m_vPos.x;
	PosySave = m_vPos.y;
	WeponNumx = 0;
	WeponNumy = 0;
	PcPosxSave = 0;
	PcPosySave = 0;
	SpCharMove = m_pGMain->m_nSpCharMove;
	ShotStart = 0;
	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・最後の敵サブショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmLastSubShotObj::Update()
{
	float fSpeed = 8;	// 弾の速さ

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  NORMAL:

			if (m_vPosUp.x != 0 || m_vPosUp.y != 0) {
				if (m_dwOwner == PC) // PCが発射した弾
				{
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

				}
				else { //  敵が発射した弾
					m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


				}

			}

			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;

			}


			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}



			if (ShotStart == 0)
			{

				PcPosxSave = m_pGMain->m_nPcpositionx;
				PcPosySave = m_pGMain->m_nPcpositiony;
				ShotStart = 1;

			}
			else {

				/*/m_vPosUp.y = fSpeed;
				/if (PcPosySave >= PosySave) {
					//WeponNumy = ((PosySave / (PcPosySave / 100)) / 100);
					m_vPosUp.y = fSpeed;
				}
				else if(PcPosySave < PosySave) {
					//WeponNumy = ((PcPosySave / (PosySave / 100)) / 100);
					m_vPosUp.y = -fSpeed;

				}
				if (PcPosxSave >= PosxSave) {
					WeponNumx = ((PosxSave / (PcPosxSave / 100)) / 100);

				}
				else if (PcPosxSave < PosxSave) {
					WeponNumx = ((PcPosxSave / (PosxSave / 100)) / 100);
				}
				//m_vPosUp.y = ((PcPosySave - PosySave) / 30)*(WeponNumy);
				m_vPosUp.x = ((PcPosxSave - PosxSave) / 30)*(WeponNumx);*/
				/*x = ((PcPosxSave - PosxSave) / 2);
				y = ((PcPosySave - PosySave) / 2);

				m_vPosUp.y = ((PcPosySave - PosySave) / y);
				m_vPosUp.x = ((PcPosxSave - PosxSave) / x);*/


				float tan = atan2(PcPosySave - PosySave, PcPosxSave - PosxSave);

				m_vPosUp.x = cos(tan)*fSpeed;
				m_vPosUp.y = sin(tan)*fSpeed;
			}


			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}


// =================================================================================

//------------------------------------------------------------------------
//
//	武器・レーザープロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CWeaponLaserProc::CWeaponLaserProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・レーザー
	for (DWORD i = 0; i < WEAPON_LASER_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponLaserObj(m_pGMain));	// m_pObjArrayに武器・ショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・レーザープロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CWeaponLaserProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・レーザーオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CWeaponLaserObj::CWeaponLaserObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite2, 148, 320, 8, 64);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 40;
}
// ---------------------------------------------------------------------------
//
// 武器・レーザーオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CWeaponLaserObj::~CWeaponLaserObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・レーザーオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CWeaponLaserObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 2;	// 弾の速さ

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置




	m_vPosUp = VECTOR2(0, 0);

	//m_vSitPos = m_vPos.x;
	CharShot = 0;
	PosxSave = m_vPos.x;
	PosySave = m_vPos.y;
	WeponNumx = 0;
	WeponNumy = 0;
	PcPosxSave = 0;
	PcPosySave = 0;
	SpCharMove = m_pGMain->m_nSpCharMove;
	ShotStart = 0;
	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・レーザーオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CWeaponLaserObj::Update()
{
	float fSpeed = 8;	// 弾の速さ

	if (m_bActive)
	{

		

			switch (LaserPatten) {
			case 0:
				//横レーザー
				m_fRotate = 90;
				break;


			}


				if (m_dwOwner == PC) // PCが発射した弾
				{
					m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);

				}
				else { //  敵が発射した弾
					m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


				}

			


			if (ShotStart == 0)
			{

				PcPosxSave = m_pGMain->m_nPcpositionx;
				PcPosySave = m_pGMain->m_nPcpositiony;
				ShotStart = 1;

			}
			else {

				/*/m_vPosUp.y = fSpeed;
				/if (PcPosySave >= PosySave) {
					//WeponNumy = ((PosySave / (PcPosySave / 100)) / 100);
					m_vPosUp.y = fSpeed;
				}
				else if(PcPosySave < PosySave) {
					//WeponNumy = ((PcPosySave / (PosySave / 100)) / 100);
					m_vPosUp.y = -fSpeed;

				}
				if (PcPosxSave >= PosxSave) {
					WeponNumx = ((PosxSave / (PcPosxSave / 100)) / 100);

				}
				else if (PcPosxSave < PosxSave) {
					WeponNumx = ((PcPosxSave / (PosxSave / 100)) / 100);
				}
				//m_vPosUp.y = ((PcPosySave - PosySave) / 30)*(WeponNumy);
				m_vPosUp.x = ((PcPosxSave - PosxSave) / 30)*(WeponNumx);*/
				/*x = ((PcPosxSave - PosxSave) / 2);
				y = ((PcPosySave - PosySave) / 2);

				m_vPosUp.y = ((PcPosySave - PosySave) / y);
				m_vPosUp.x = ((PcPosxSave - PosxSave) / x);*/


				float tan = atan2(PcPosySave - PosySave, PcPosxSave - PosxSave);

				/*m_vPosUp.x = cos(tan)*fSpeed;
				m_vPosUp.y = sin(tan)*fSpeed;
				*/
			}



		

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}

//------------------------------------------------------------------------
//
//	武器・最後の敵スペシャルショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEnmLastSpShotProc::CEnmLastSpShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・最後の敵スペシャルショット
	for (DWORD i = 0; i < WEAPON_ENMLASTSPSHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmLastSpShotObj(m_pGMain));	// m_pObjArrayに武器・ショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・最後の敵スペシャルショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSpShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・最後の敵スペシャルショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEnmLastSpShotObj::CEnmLastSpShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite4, 400, 85, 250, 250);

	//m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 101, 536, 38, 34,16,16);
	m_nAnimNum = 1;

	m_nAtc = 40;
}
// ---------------------------------------------------------------------------
//
// 武器・最後の敵スペシャルショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmLastSpShotObj::~CEnmLastSpShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・最後の敵スペシャルショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSpShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 2;	// 弾の速さ

	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置




	m_vPosUp = VECTOR2(0, 0);

	//m_vSitPos = m_vPos.x;
	CharShot = 0;
	PosxSave = m_vPos.x;
	PosySave = m_vPos.y;
	WeponNumx = 0;
	WeponNumy = 0;
	PcPosxSave = 0;
	PcPosySave = 0;
	SpCharMove = m_pGMain->m_nSpCharMove;
	ShotStart = 0;

	ShotTime = 0;
	SpTime = 0;
	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・最後の敵スペシャルショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmLastSpShotObj::Update()
{
	float fSpeed = 8;	// 弾の速さ

	if (m_bActive)
	{

		switch (m_dwStatus)
		{
		case  NORMAL:
			if(SpTime>=Random(300,500)){
				m_pGMain->m_nSpLastTrigger = 0;
				m_pGMain->m_nSpLastStop = 0;
				m_bActive = FALSE;

			}
			else {

				if (410 < m_pGMain->m_nPcpositionx) {
					m_pGMain->m_nSpLastTrigger = 1;
				}
				else if (410 >= m_pGMain->m_nPcpositionx) {
					m_pGMain->m_nSpLastTrigger = 2;

				}
				if (ShotTime <= 0) {
					m_pGMain->m_pWeaponProc->m_pEnmLastSpSubShotProc->Start(m_vPos + VECTOR2(Random(22, 172), Random(0, 80)), this, ENM);
					ShotTime = 5;
				}
				if (ShotTime > 0)ShotTime--;

				m_fRotate += 3;
				SpTime++;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}



			if (ShotStart == 0)
			{

				PcPosxSave = m_pGMain->m_nPcpositionx;
				PcPosySave = m_pGMain->m_nPcpositiony;
				ShotStart = 1;

			}
			else {

				/*/m_vPosUp.y = fSpeed;
				/if (PcPosySave >= PosySave) {
					//WeponNumy = ((PosySave / (PcPosySave / 100)) / 100);
					m_vPosUp.y = fSpeed;
				}
				else if(PcPosySave < PosySave) {
					//WeponNumy = ((PcPosySave / (PosySave / 100)) / 100);
					m_vPosUp.y = -fSpeed;

				}
				if (PcPosxSave >= PosxSave) {
					WeponNumx = ((PosxSave / (PcPosxSave / 100)) / 100);

				}
				else if (PcPosxSave < PosxSave) {
					WeponNumx = ((PcPosxSave / (PosxSave / 100)) / 100);
				}
				//m_vPosUp.y = ((PcPosySave - PosySave) / 30)*(WeponNumy);
				m_vPosUp.x = ((PcPosxSave - PosxSave) / 30)*(WeponNumx);*/
				/*x = ((PcPosxSave - PosxSave) / 2);
				y = ((PcPosySave - PosySave) / 2);

				m_vPosUp.y = ((PcPosySave - PosySave) / y);
				m_vPosUp.x = ((PcPosxSave - PosxSave) / x);*/


			}


			break;

		case  DAMAGE:
			m_bActive = FALSE;

			break;
		}

		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();
	}
}


//------------------------------------------------------------------------
//
//	武器・最後の敵スペシャルサブショットプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEnmLastSpSubShotProc::CEnmLastSpSubShotProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// 武器・最後の敵スペシャルサブショット
	for (DWORD i = 0; i < WEAPON_SHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmLastSpSubShotObj(m_pGMain));	// m_pObjArrayに武器・最後の敵スペシャルサブショットオブジェクトを生成する
	}

	m_nWaitTime = m_nMaxwaitTime = 8;

}

//-----------------------------------------------------------------------------
// 武器・最後の敵スペシャルサブショットプロシージャの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSpSubShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// 武器の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (注意)m_nWaitTimeのカウントダウンは、CBaseProcで行っている

	return bRet;
}


//------------------------------------------------------------------------
//
//	武器・最後の敵スペシャルサブショットオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEnmLastSpSubShotObj::CEnmLastSpSubShotObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite4, 0, 380, 24, 24);
	m_nAnimNum = 1;

	m_nAtc = 1000;
}
// ---------------------------------------------------------------------------
//
// 武器・最後の敵スペシャルサブショットオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CEnmLastSpSubShotObj::~CEnmLastSpSubShotObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 武器・最後の敵スペシャルサブショットオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   CBaseObj*   pObj    発射元のオブジェクト
//   DWORD       dwOwner 発射元のオブジェクト区分
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CEnmLastSpSubShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner)
{
	float fSpeed = 8;	// 弾の速さ
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;

	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);
	m_vSitPos = m_vPos.x;

	/*switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}*/

	return TRUE;

}
//-----------------------------------------------------------------------------
// 武器・最後の敵スペシャルサブショットオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEnmLastSpSubShotObj::Update()
{
	CMapLine*  pHitmapline = NULL;

	float fSpeed = 8;

	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			m_vPosUp.y = fSpeed;
			if (m_dwOwner == PC) // PCが発射した弾
			{
				m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);


			}
			else { //  敵が発射した弾
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);


			}
			if (m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Hitcheck((CBaseObj*)this))
			{
				m_bActive = FALSE;
			}

			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// 画面外へ出たので消去
				m_bActive = FALSE;
			}
			break;


			break;
		}
		if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
		{
			m_bActive = FALSE;
		}
		m_vPos += m_vPosUp;

		AnimCountup();
		Draw();

	}
}

