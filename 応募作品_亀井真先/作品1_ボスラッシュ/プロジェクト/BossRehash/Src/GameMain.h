//=============================================================================
//
//		ゲームメイン処理
//																GameMain.h
//=============================================================================

#pragma once

//警告非表示
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)


//ヘッダーファイルのインクルード
#include <stdio.h>
#include <windows.h>
#include <vector>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Shader.h"
#include "Dinput.h"
#include "Sprite.h"
#include "BaseProc.h"


// ステータスタイプ
#define  NONE				0x00000000
#define  TITLE				0x00000001
#define  STAGEDEMO  		0x00000002
#define  GAMEMAIN			0x00000004
#define  GAMEOVER			0x00000008
#define  GAMECLEAR			0x00000010
#define  GAMEEND			0x00000020

#define  NORMAL				0x00000001
#define  STANBY				0x00000002
#define  CATCH				0x00000004
#define  ATTACK				0x00000008
#define  DAMAGE				0x00000010
#define  DEAD				0x00000020
#define  FLASH				0x00000040
#define  WALK				0x00000080
#define  JUMP				0x00000100
#define  RAND				0x00000200
#define  STOP				0x00000400

// ステータスサブ
#define  ATTACKNONE			0x00000001
#define  ATTACKMOVE			0x00000002
#define  ATTACKLASER		0x00000004
#define  ATTACKCANNON		0x00000008
#define  ATTACKBOM			0x00000010
#define  ATTACKEARTH		0x00000020

// オブジェクト区分
#define  PC					0x00000001
#define  NPC				0x00000002
#define  ENM				0x00000004

// 方向（DirIdx）
#define  UP					0
#define  RIGHT				1
#define  DOWN				2
#define  LEFT				3

#define  GRAVITY  1.0

class CMain;
class CShader;
class CSpriteImage;
class CSprite;
class CFontTexture;
class CBaseObj;
class CBaseProc;
class CPcProc;
class CEnmProc;
class CWeaponProc;
class CEffectProc;
class CForeProc;
class CMapProc;
class CTitleProc;
class CBaseProc;
class CExplosionProc;

// --------------------------------------------------------------------------------------------------
//  ゲームメインクラス
// --------------------------------------------------------------------------------------------------
class CGameMain
{
public:
	// メンバ変数
	CMain*			m_pMain;		// メインクラス
	CDirect3D*		m_pD3D;			//	Direct3Dオブジェクト
	CXAudio*		m_pXAudio;		//	XAudioオブジェクト
	CDirectInput*	m_pDI;			//	DirectInputDオブジェクト
	CShader*		m_pShader;		//	シェーダー
	CFontTexture*	m_pFont;		//	フォントテクスチャー

	DWORD			m_dwGameStatus;
	VECTOR2			m_vScroll;

	// プロシージャ
	CPcProc*		m_pPcProc;
	CEnmProc*		m_pEnmProc;
	CWeaponProc*	m_pWeaponProc;
	CEffectProc*	m_pEffectProc;
	CForeProc*		m_pForeProc;
	CMapProc*		m_pMapProc;
	CTitleProc*		m_pTitleProc;



	// サウンド
	CXAudioSource*  m_pSeShot;
	CXAudioSource*  m_pSeHit;
	CXAudioSource*  m_pSePower;
	CXAudioSource*  m_pBgm1;

	// スプライト
	CSpriteImage*   m_pImageChar;
	CSpriteImage*   m_pImageChar2;
	CSpriteImage*   m_pImageSprite;
	CSpriteImage*   m_pImageSprite2;
	CSpriteImage*   m_pImageSprite3;
	CSpriteImage*   m_pImageSprite4;


	//座標保存
	int				m_nPcpositionx = 0;
	int				m_nPcpositiony = 0;
	//シールド時武器禁止
	int				m_nShieldStop = 0;
	//向き
	int				m_nDirection = 0;
	//近接攻撃速度
	int				m_nProAtkStop = 0;
	//二段ジャンプ確認
	int				m_nJumptwo = 0;
	//チャージ量
	int				m_nCharAmount = 0;
	//チャージ量保存
	int				m_nCharAmountSave = 0;
	//チャージ禁止
	int				m_nCharStop = 0;
	//チャージ敵当たったら
	int				m_nCharEnmhit = 0;
	//爆弾処理
	int				m_nBoomStop = 0;

	//マップ戻る
	int				m_nMapChange = 0;
	//マップ扉開ける
	int				m_nDoorOpen = 0;
	//マップ扉封印
	int				m_nDoorStop[6];

	//武器変更
	int				m_nChangeWeapon = 0;
	//武器開放
	int				m_nUnLookWeapon [5];

	//キツネチャージショット
	int				m_nSpCharMove = 0;

	//ガマスペシャルショット
	int				m_nSpTordPosx = 0;
	int				m_nSpTordPosy = 0;
	int				m_nSpTordStop = 0;

	//最後の敵スペシャルショット
	int				m_nSpLastTrigger = 0;
	int				m_nSpLastStop = 0;


	//回復アイテム
	int				m_nHeelNum = 0;
	int				m_nHeelMaxNum = 0;

	//敵Hp
	int				m_nEnmHpSave= 0;
	int				m_nEnmHpMaxSave = 0;

	//ビットタイム
	int             m_nBitTimeStop = 0;

	//レーザーパターン
	int				m_nLaserPatternNum = 0;


public:
	// メソッド
	CGameMain(CMain* pMain);
	~CGameMain();

	HRESULT Init();
	void    Loop();
	void    GameMain();
	void    Quit();

	HRESULT ChangeScreenMode(int nMode=-1);    // -- 2020.1.15

};

