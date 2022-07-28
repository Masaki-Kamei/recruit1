//=============================================================================
//
//		プレイキャラクターの処理
//																Playchar.cpp
//=============================================================================

#include "Playchar.h"
#include "Weapon.h"
#include "Effect.h"
#include "Map.h"
#include "GameMain.h"


//------------------------------------------------------------------------
//
//	ＰＣプロシージャのコンストラクタ	
//
//   なお、オブジェクトのdeleteはCBaseProcのデストラクタで行うため不要
//
//------------------------------------------------------------------------
CPcProc::CPcProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pPcObj = new CPcObj(m_pGMain);
	m_pObjArray.push_back(m_pPcObj);  // m_pObjArrayにオブジェクトを登録する

	m_nPcNum = 2;
}

// ===========================================================================
//------------------------------------------------------------------------
//
//	ＰＣオブジェクトのコンストラクタ	
//
//  引数　CGameMain* pGMain
//
//------------------------------------------------------------------------
CPcObj::CPcObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 96, 0, 48, 48);
	m_vPos = VECTOR2(48, 721);

	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_nDirIdx = DOWN;
	m_nHp = m_nMaxHp = 3000;
	m_nMaxMp = 3000;
	m_nMp = 0;
	m_nAtc = 300;

	m_nShotWait = 0;
	m_nDifShotWait = 0;
	m_nProAtkWait=0;
	m_nCharShotWait = 0;
	m_nProAtkTime = 0;


	m_pGMain->m_nHeelNum = m_pGMain->m_nHeelMaxNum+1;
}
// ---------------------------------------------------------------------------
//
// ＰＣオブジェクトのデストラクタ
//
// ---------------------------------------------------------------------------
CPcObj::~CPcObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ＰＣオブジェクトの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CPcObj::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	CMapLine*  pHitmapline = NULL;
	float fSpeed     = 5;
	float fJumpPlus  = 4;

	if (!m_bActive) return;

	m_vPosUp = VECTOR2(0, 0);

	if (m_pGMain->m_nMapChange == 1) {

	}
	
	
	switch (m_dwStatus)
	{
		case  FLASH:
				m_nCnt1--;
				if (m_nCnt1 <= 0) {
					ResetStatus();
					ResetAnim();
				}
				else {
					FlashCountup();
				}		// break;を入れずそのまま　NORMAL　の処理を行う
		case  NORMAL:

			m_pGMain->m_nPcpositionx = m_vPos.x;
			m_pGMain->m_nPcpositiony = m_vPos.y;

			if (m_pGMain->m_nSpLastTrigger == 1) {
				m_vPosUp.x = -3;
			}
			else if (m_pGMain->m_nSpLastTrigger == 2) {
				m_vPosUp.x = 3;

			}

				break;

		case DAMAGE:
				if (m_pOtherObj->GetAtc() > 0)
				{
					m_nHp -= m_pOtherObj->GetAtc();	// 攻撃を受けたダメージ
					if (m_nHp <= 0)
					{
						m_nHp = 0;
						m_dwStatus = DEAD;		// HPが０なので死亡へ
						m_nCnt1 = 180;			// 死亡フラッシュ中の時間設定
					}
					else {
						m_dwStatus = FLASH;
						m_nCnt1 = 60;
					}
				}
				else {
					m_dwStatus = NORMAL;  // 攻撃力なしのときはすぐにNORMALに戻る
				}
				break;

		case DEAD:
				m_nCnt1--;
				if (m_nCnt1 <= 0)
				{
						m_pGMain->m_dwGameStatus = GAMEOVER;
					
				}
				else {
					FlashCountup();
				}
				break;

	}

	switch (m_dwStatusSub)
	{
		case  WALK:		// 歩行中の処理


			if (pDI->CheckKey(KD_DAT, DIK_RIGHT) || pDI->CheckJoy(KD_DAT, DIJ_RIGHT))//→キー
			{
				if (m_pGMain->m_nShieldStop == 0)
				{
					if (m_pGMain->m_nSpLastTrigger == 1) {
						m_vPosUp.x = 1;
						m_nDirIdx = RIGHT;

					}
					else if (m_pGMain->m_nSpLastTrigger == 2) {
						m_vPosUp.x = 8;
						m_nDirIdx = RIGHT;

					}
					else {
						m_vPosUp.x = fSpeed;
						m_nDirIdx = RIGHT;
						m_pGMain->m_nDirection = 0;
					}
				}
			}
			if (pDI->CheckKey(KD_DAT, DIK_LEFT) || pDI->CheckJoy(KD_DAT, DIJ_LEFT))//←キー
			{
				if (m_pGMain->m_nShieldStop == 0)
				{
					if (m_pGMain->m_nSpLastTrigger == 1) {
						m_vPosUp.x = -8;
						m_nDirIdx = LEFT;

					}
					else if (m_pGMain->m_nSpLastTrigger == 2) {
						m_vPosUp.x = -1;
						m_nDirIdx = LEFT;

					}
					else {


						m_vPosUp.x = -fSpeed;
						m_nDirIdx = LEFT;
						m_pGMain->m_nDirection = 1;
					}
					
				}
				
			}
			if (pDI->CheckKey(KD_TRG, DIK_UP) || pDI->CheckJoy(KD_DAT, DIJ_UP)) //	↑キー
			{	// ジャンプ開始
				if (m_pGMain->m_nShieldStop == 0)
				{
					m_dwStatusSub = JUMP;
					m_vJumpSpeed.x = m_vPosUp.x;
					m_vJumpSpeed.y = -(fSpeed*2.5 + fJumpPlus);
					m_fJumpTime = 0;
					m_vPosUp.y = m_vJumpSpeed.y;
					//m_nDirIdx = UP;
				}
			}
			else {// 自然落下
				if (pDI->CheckKey(KD_DAT, DIK_DOWN) || pDI->CheckJoy(KD_DAT, DIJ_DOWN))//↓キー
				{
					//m_vPosUp.y = fSpeed;
					//m_nDirIdx = DOWN;



				}
				else {
					m_dwStatusSub = JUMP;
					m_vJumpSpeed.x = m_vPosUp.x;
					m_vJumpSpeed.y = fSpeed / 2;
					m_fJumpTime = 0;
					m_vPosUp.y = m_vJumpSpeed.y;
			
				}
			}
			break;

		case  JUMP:		// ジャンプ中の処理
			if (pDI->CheckKey(KD_DAT, DIK_RIGHT) || pDI->CheckJoy(KD_DAT, DIJ_RIGHT))//→キー
			{
				if (m_pGMain->m_nSpLastTrigger == 1) {
					m_vPosUp.x = -8;
				}
				else if (m_pGMain->m_nSpLastTrigger == 2) {
					m_vPosUp.x = 1;

				}
				else {

					m_vJumpSpeed.x = fSpeed;
					m_nDirIdx = RIGHT;
					m_pGMain->m_nDirection = 0;
				}
			}
			if (pDI->CheckKey(KD_DAT, DIK_LEFT) || pDI->CheckJoy(KD_DAT, DIJ_LEFT))//←キー
			{
				if (m_pGMain->m_nSpLastTrigger == 1) {
					m_vPosUp.x = -1;
				}
				else if (m_pGMain->m_nSpLastTrigger == 2) {
					m_vPosUp.x = 8;

				}
				else {

					m_vJumpSpeed.x = -fSpeed;
					m_nDirIdx = LEFT;
					m_pGMain->m_nDirection = 1;
				}
			}
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + GRAVITY*m_fJumpTime);
			break;

			
	}
	// 2段ジャンプ
	if (pDI->CheckKey(KD_TRG, DIK_UP) || pDI->CheckJoy(KD_DAT, DIJ_UP)) //	↑キー
	{	// 2段ジャンプ開始
		if (m_pGMain->m_nShieldStop == 0)
		{
			if (m_pGMain->m_nJumptwo <= 1) {
				m_pGMain->m_nJumptwo++;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -(fSpeed*2.5 + fJumpPlus);
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}
		}
	}

	//武器変更
	if (pDI->CheckKey(KD_TRG, DIK_1) || pDI->CheckJoy(KD_DAT, DIJ_A))
		m_pGMain->m_nChangeWeapon=0;
	if (pDI->CheckKey(KD_TRG, DIK_2) || pDI->CheckJoy(KD_DAT, DIJ_A))
		m_pGMain->m_nChangeWeapon = 1;
	if (pDI->CheckKey(KD_TRG, DIK_3) || pDI->CheckJoy(KD_DAT, DIJ_A))
		m_pGMain->m_nChangeWeapon = 2;
	if (pDI->CheckKey(KD_TRG, DIK_4) || pDI->CheckJoy(KD_DAT, DIJ_A)) {
		m_pGMain->m_nChangeWeapon = 3;
		m_pGMain->m_nCharAmountSave = 0;
		m_pGMain->m_nCharAmount = 0;
		m_pGMain->m_nCharStop = 0;
	}
	if (pDI->CheckKey(KD_TRG, DIK_5) || pDI->CheckJoy(KD_DAT, DIJ_A))
		m_pGMain->m_nChangeWeapon = 4;



	//ショット
	if (m_pGMain->m_nChangeWeapon == 0) {
		if (pDI->CheckKey(KD_DAT, DIK_X) || pDI->CheckJoy(KD_DAT, DIJ_A))
		{

			if (m_nShotWait <= 0)
			{

				if (m_pGMain->m_nShieldStop == 0)
				{
					// ショットの発射
					m_pGMain->m_pWeaponProc->m_pWeaponShotProc->Start(m_vPos + VECTOR2(16, 16), this, PC);
					m_nShotWait = 30;    // 武器発射のウェイトを掛ける
				}
			}
		}
	}
	if (m_nShotWait > 0) m_nShotWait--;    // 武器発射のウェイトをカウントダウン

	//拡散ショット
	if (m_pGMain->m_nUnLookWeapon[0] == 1) {
		if (m_pGMain->m_nChangeWeapon == 1) {

			if (pDI->CheckKey(KD_DAT, DIK_X) || pDI->CheckJoy(KD_DAT, DIJ_A))
			{
				if (m_nDifShotWait <= 0)
				{
					if (m_pGMain->m_nShieldStop == 0)
					{
						// 拡散ショットの発射
						m_pGMain->m_pWeaponProc->m_pWeaponDifShotProc->Start(m_vPos + VECTOR2(16, 16), this, PC);


						m_nDifShotWait = 60;    // 武器発射のウェイトを掛ける
					}
				}
			}
		}
		if (m_nDifShotWait > 0) m_nDifShotWait--;    // 武器発射のウェイトをカウントダウン
	}

	//シールド

	if (pDI->CheckKey(KD_DAT, DIK_DOWN) || pDI->CheckJoy(KD_DAT, DIJ_A))
	{
		m_pGMain->m_nShieldStop = 1;
			// シールドの発射
			m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Start(m_vPos + VECTOR2(16, 16), this, PC);
	}
	else if (pDI->CheckKey(KD_UTRG, DIK_DOWN) || pDI->CheckJoy(KD_DAT, DIJ_A)) {
		m_pGMain->m_nShieldStop = 0;
	}

	//爆弾
	if (m_pGMain->m_nUnLookWeapon[1] == 1) {
		if (m_pGMain->m_nChangeWeapon == 2) {
			if (pDI->CheckKey(KD_TRG, DIK_X) || pDI->CheckJoy(KD_TRG, DIJ_A))
			{

				if (m_nShotWait <= 0)
				{
					if (m_pGMain->m_nShieldStop == 0)
					{
						if (m_pGMain->m_nDirection == 0) {
							// 爆弾の発射
							m_pGMain->m_pWeaponProc->m_pWeaponBoomProc->Start(m_vPos + VECTOR2(66, 16), this, PC);
						}
						else if (m_pGMain->m_nDirection == 1) {
							// 爆弾の発射
							m_pGMain->m_pWeaponProc->m_pWeaponBoomProc->Start(m_vPos + VECTOR2(-34, 16), this, PC);
						}
					}
				}
			}
		}
	}
	//近距離攻撃
	if(pDI->CheckKey(KD_DAT, DIK_X) || pDI->CheckJoy(KD_DAT, DIJ_A)){

	}
	else {
		if (pDI->CheckKey(KD_DAT, DIK_Y) || pDI->CheckJoy(KD_DAT, DIJ_A))
		{


			if (m_nProAtkWait <= 0)
			{
				//m_pGMain->m_nProAtkStop = 1;
				m_pGMain->m_pWeaponProc->m_pWeaponProAtkProc->Start(m_vPos + VECTOR2(16, 16), this, PC);
				m_pGMain->m_nProAtkStop = 1;

				m_nProAtkWait = 10;

			}



		}
	}
    if (m_nProAtkWait > 0)
		{
		//m_pGMain->m_nProAtkStop = 0;
		m_nProAtkWait--;
		}
	if (m_pGMain->m_nUnLookWeapon[2] == 1) {
		//チャージショット
		if (m_pGMain->m_nChangeWeapon == 3) {
			if (pDI->CheckKey(KD_DAT, DIK_X) || pDI->CheckJoy(KD_DAT, DIJ_A))
			{

				if (m_pGMain->m_nShieldStop == 0) {
					if (m_nCharShotWait <= 0) {
						m_pGMain->m_nCharEnmhit = 0;
						if (m_pGMain->m_nCharStop == 0)
						{
							m_pGMain->m_nCharAmountSave = 0;


							m_pGMain->m_nCharAmount++;
							m_pGMain->m_nCharAmountSave = m_pGMain->m_nCharAmount;

							m_pGMain->m_pWeaponProc->m_pWeaponCharShotProc->Start(m_vPos + VECTOR2(16, 16), this, PC);
						}
					}

				}
				else {
					m_pGMain->m_nCharAmountSave = 0;
					m_pGMain->m_nCharAmount = 0;

				}

			}




			if (pDI->CheckKey(KD_UTRG, DIK_X) || pDI->CheckJoy(KD_UTRG, DIJ_A))
			{

				if (m_pGMain->m_nShieldStop == 0) {

					m_pGMain->m_nCharStop = 1;
					m_pGMain->m_nCharEnmhit = 1;
					if (m_nCharShotWait <= 0)
					{
						// チャージショットの発射

						m_pGMain->m_nCharAmount = 0;
						m_nCharShotWait = 10;
					}

				}
				else {
					m_pGMain->m_nCharAmountSave = 0;
					m_pGMain->m_nCharAmount = 0;

				}

			}
		}
		else if (m_pGMain->m_nCharAmountSave > 1)
		{
			if (m_pGMain->m_nShieldStop == 0) {

				m_pGMain->m_nCharStop = 1;
				m_pGMain->m_nCharEnmhit = 1;
				if (m_nCharShotWait <= 0)
				{
					// チャージショットの発射

					m_pGMain->m_nCharAmount = 0;
					m_nCharShotWait = 10;
				}

			}
			else {
				m_pGMain->m_nCharAmountSave = 0;
				m_pGMain->m_nCharAmount = 0;

			}

		}

		if (m_nCharShotWait > 0) m_nCharShotWait--;    // 武器発射のウェイトをカウントダウン

	}


	if (m_pGMain->m_nUnLookWeapon[3] == 1) {

	//バウンドショット
	if (m_pGMain->m_nChangeWeapon == 4) {
		if (pDI->CheckKey(KD_DAT, DIK_X) || pDI->CheckJoy(KD_DAT, DIJ_A))
		{

			if (m_nBoundShotWait <= 0)
			{

				if (m_pGMain->m_nShieldStop == 0)
				{
					// ショットの発射
					m_pGMain->m_pWeaponProc->m_pWeaponBoundShotProc->Start(m_vPos + VECTOR2(16, 16), this, PC);
					m_nBoundShotWait = 30;    // 武器発射のウェイトを掛ける
				}
			}
		}
	}
	if (m_nBoundShotWait > 0) m_nBoundShotWait--;    // 武器発射のウェイトをカウントダウン
	}

	if (pDI->CheckKey(KD_TRG, DIK_H) || pDI->CheckJoy(KD_DAT, DIJ_UP)) //	Hキー
	{
		// 回復
		if (m_pGMain->m_nHeelNum>0) {
			if (m_nHp < m_nMaxHp - 1700) {
				m_nHp += 1700;

			}
			else if (m_nHp >= m_nMaxHp - 1700) {
				m_nHp = m_nMaxHp;
			}
		}
		m_pGMain->m_nHeelNum--;

	}

	// マップ線との接触判定と適切な位置への移動
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// マップ線が垂直まではＯＫ
		{
			m_dwStatusSub = WALK;	// マップ線に接触しているときは、ジャンプを歩行に戻す
			m_pGMain->m_nJumptwo = 0;
			m_fJumpTime = 0;
		}
	}

	// 増分計算
	m_vPos += m_vPosUp;

	AnimCountup();
	Draw();

}
