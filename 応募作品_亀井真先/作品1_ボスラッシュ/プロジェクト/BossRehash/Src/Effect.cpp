//=============================================================================
//
//		映像効果の処理
//																Effect.cpp
//=============================================================================

#include "Effect.h"
#include "Playchar.h"
#include "Map.h"

//------------------------------------------------------------------------
//
//	映像効果メインプロシージャのコンストラクタ
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEffectProc::CEffectProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pEffectBomProc = new CEffectBomProc(m_pGMain);	// 映像効果・爆発プロシージャ
	m_pProcArray.push_back(m_pEffectBomProc);     // プロシージャをプロシージャ配列に登録する

	m_pItemProc = new CItemProc(m_pGMain);				// アイテムプロシージャ
	m_pProcArray.push_back(m_pItemProc);		// プロシージャをプロシージャ配列に登録する

}
//============================================================================
//   プロシージャとオブジェクトを探索し全てのオブジェクトをノンアクティブにする
//   プロシージャの開始フラグをリセットする
//============================================================================
void  CEffectProc::SetNonActive()
{

	//オブジェクトポインタ配列の探索
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive( FALSE);
	}

	// 下位のプロシージャポインタ配列の探索
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetStartFlag(0);				// 開始フラグのリセット
		((CEffectProc*)m_pProcArray[i])->SetNonActive();      // 下位のプロシージャの処理（再帰処理）
	}
}


// ================================================================================================================================
// 
// 各映像効果プロシージャ毎の処理
// 
// ================================================================================================================================


//------------------------------------------------------------------------
//
//	映像効果・爆発プロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CEffectBomProc::CEffectBomProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < EFFECT_BOM_MAX; i++)
	{
		m_pObjArray.push_back(new CEffectBomObj(m_pGMain));	// m_pObjArrayに映像効果・爆発オブジェクトを生成する
	}

}

//-----------------------------------------------------------------------------
// 映像効果・爆発プロシージャの開始
//
//   VECTOR2 vPos    発生位置
//
//   戻り値　　正常に発生 : TRUE    発生しなかった : FALSE
//-----------------------------------------------------------------------------
BOOL	CEffectBomProc::Start(VECTOR2 vPos)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive() )
		{
			m_pObjArray[i]->Start(vPos);	// 映像効果・爆発の発生
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}

	return TRUE;
}

//------------------------------------------------------------------------
//
//	映像効果・爆発オブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CEffectBomObj::CEffectBomObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 144, 480, 64, 64);
	m_nAnimNum = 7;

}
// ---------------------------------------------------------------------------
//
// 映像効果・爆発オブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CEffectBomObj::~CEffectBomObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// 映像効果・爆発オブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CEffectBomObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	m_dwStatus = NORMAL;
	m_dwStatusSub = STOP;
	m_dwStatusPhase = 0;

	m_vPos = vPos;	// 発生位置

	m_nAnimIdx = 0;

	return TRUE;
}
//-----------------------------------------------------------------------------
// 映像効果・爆発オブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CEffectBomObj::Update()
{
	if (m_bActive)
	{
		if (AnimCountup() == 1)
		{
			m_bActive = FALSE;
		}
		Draw();

	}
}
// ==============================================================================================================

// =================================================================================
//------------------------------------------------------------------------
//
//	アイテムプロシージャのコンストラクタ	
//
//   なお、プロシージャのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CItemProc::CItemProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ITEM_MAX; i++)
	{
		m_pObjArray.push_back(new CItemObj(m_pGMain));	// m_pObjArrayにアイテムを生成する
	}
	m_nStartFlag = 0;
}

//-----------------------------------------------------------------------------
// アイテムプロシージャの開始
//
//   戻り値　　なし
//-----------------------------------------------------------------------------
void	CItemProc::Update()
{
	VECTOR2 vPos;
	int  nNext;

	if (m_nStartFlag == 0)
	{
		// イベントマップを探索し、救急箱を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップの探索　 ( EvtID:2　アイテムの出現位置,  EvtNo:0x10 救急箱	)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x10, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos, ITEMRESQUE);
						break;
					}
				}
			}
		}

		// イベントマップを探索し、ドア（出口）を設定する
		nNext = 0;
		while (nNext != -1)
		{
			// イベントマップの探索　 ( EvtID:2　アイテムの出現位置,  EvtNo:0x20 ドア	)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x20, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos, ITEMDOOR);
						break;
					}
				}
			}
		}

		m_nStartFlag = 1;  // 一回発させたら、もう発生しない
	}

}

//------------------------------------------------------------------------
//
//	アイテムオブジェクトのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CItemObj::CItemObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar);
	m_nAnimNum = 2;

}
// ---------------------------------------------------------------------------
//
// アイテムオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CItemObj::~CItemObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// アイテムオブジェクトの開始
//
//   VECTOR2 vPos    発生位置
//   DWORD       dwNo    アイテム種別
//
//   戻り値　　TRUE
//-----------------------------------------------------------------------------
BOOL	CItemObj::Start(VECTOR2 vPos, DWORD dwNo)
{
	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_dwStatusSub = dwNo;

	m_vPos = vPos;	// 発生位置
	m_vPosUp = VECTOR2(0, 0);

	switch (m_dwStatusSub)
	{
	case  ITEMRESQUE:     // 救急箱
		m_pSprite->SetSrc(384, 336, 48, 48);
		break;

	case  ITEMDOOR:      // ドア
		m_pSprite->SetSrc(384, 288, 48, 48);   // 透明色
		break;
	}

	return TRUE;
}
//-----------------------------------------------------------------------------
// アイテムオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CItemObj::Update()
{
	if (!m_bActive) return;

	if (isCollision(m_pGMain->m_pPcProc->GetPcObjPtr())) // PCとの接触判定
	{
		switch (m_dwStatusSub)
		{
		case  ITEMRESQUE:     // 救急箱
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetHp( m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaxHp());
			m_pGMain->m_pSePower->Play();
			break;

		case  ITEMDOOR:      // ドア
			m_pGMain->m_pSePower->Play();
			m_pGMain->m_pMapProc->MoveMap();
			break;
		}
		m_bActive = FALSE;
	}

	AnimCountup();
	Draw();

}


