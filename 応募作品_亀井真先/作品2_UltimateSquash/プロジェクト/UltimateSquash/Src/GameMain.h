//=============================================================================
//
//		ゲームのメイン処理
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
#include "Shader.h"
#include "FbxMesh.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite3D.h"
#include "Collision.h"
#include "Displace.h"
#include "BBox.h"
#include "BaseProc.h"
#include "MyImgui.h"

#include "MPR.h"		
#include "RenderBuf.h"


// ステータスタイプ
#define  NONE				0x00000000
#define  TITLE				0x00000001
#define  STAGEDEMO  		0x00000002
#define  GAMEMAIN			0x00000004
#define  GAMEOVER			0x00000008
#define  GAMECLEAR			0x00000010
#define  GAMEEND			0x00000020
#define  SIMPLEMODERESULT	0x00000040
#define  GAMETUTORIAL		0x00000080
#define  GAMEMULTI			0x00000160

#define  GAMEMULTIBATTLERESULT			0x00000320


#define  GAMEMAINSUB		0x00000040


#define  NORMAL				0x00000001
#define  WAIT				0x00000002
#define  DAMAGE				0x00000004
#define  FLASH				0x00000008
#define  DEAD				0x00000010

// ステータスサブ
#define  ATTACKNONE			0x00000001
#define  ATTACKMOVE			0x00000002
#define  ATTACKLASER		0x00000004
#define  ATTACKCANNON		0x00000008
#define  ATTACKBOM			0x00000010
#define  ATTACKEARTH		0x00000020
#define  ATTACKSWORD		0x00000040
#define  ATTACKFLAME		0x00000080
#define  ATTACKWAIT			0x00000100

#define  START				0x00001000
#define  INTER				0x00001001
#define  FINAL				0x00001002


// オブジェクト区分
#define  PC					0x00000001
#define  NPC				0x00000002
#define  ENM				0x00000004

//マップに対しての四方向
#define  FRONT				0x00000001
#define  RIGHT				0x00000002
#define  LEFT				0x00000004
#define  BACK				0x00000008

#define	TITLEMODE		0
#define	MAINMODE		1
#define	SIMPLEMODE		2
#define	TUTORIAL		3
#define	MULTI			4

//
#define	FIRSTPLAYER			1
#define	SECONDPLAYER		2

class CMain;
class CShader;
class CSpriteImage;
class CSprite;
class CFontTexture;
class CCollision;
class CWave;
class CBBox;
class CFbxMeshCtrl;

class CBaseObj;
class CBaseProc;
class CPcProc;
class CCameraProc;
class CEnmProc;
class CMapProc;
class CWeaponProc;
class CEffectProc;
class CBackForeProc;
class CTitleProc;

class CMapSubProc;		

class CMPR;	
class CRenderBufProc;


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
	CFontTexture*	m_pFont;		//	フォントテクスチャー
	CShader*		m_pShader;		//	シェーダー
	CFbxMeshCtrl*	m_pFbxMeshCtrl;	// メッシュコントロールクラス   

	DWORD           m_dwGameStatus;
	
	// カメラ・ライト・ビュー
	VECTOR3         m_vEyePt;		//カメラ（視点）位置
	VECTOR3         m_vLookatPt;	//注視位置
	MATRIX4X4       m_mView;
	MATRIX4X4       m_mProj;
	VECTOR3         m_vLightDir;	//ディレクショナルライトの方向

		// カメラ・ライト・ビュー
	VECTOR3         m_vEyePtSecond;		//カメラ（視点）位置
	VECTOR3         m_vLookatPtSecond;	//注視位置
	MATRIX4X4       m_mViewSecond;
	MATRIX4X4       m_mProjSecond;
	VECTOR3         m_vLightDirSecond;	//ディレクショナルライトの方向


	// MPR
	CMPR*			m_pMPR;		
	CRenderBufProc*	m_pRenderBufProc;  



	// プロシージャ
	CPcProc*		m_pPcProc;
	CCameraProc*	m_pCameraProc;
	CEnmProc*		m_pEnmProc;
	CMapProc*		m_pMapProc;
	CWeaponProc*	m_pWeaponProc;
	CEffectProc*	m_pEffectProc;
	CBackForeProc*	m_pBackForeProc;
	CTitleProc*		m_pTitleProc;

	CMapSubProc*	m_pMapSubProc;		



	// サウンド
	CXAudioSource*   m_pSeLazer;
	CXAudioSource*   m_pSeNitro;
	CXAudioSource*   m_pSeDead;
	CXAudioSource*   m_pSeFire;

	// スコア
	int             m_nScore;
	int				m_nHighScore;	
	int             m_nScoreSec;

	//タイム
	int				m_nTimer;		
	int				m_nTimeNum;

	//モード
	DWORD			m_dModeType;		

	DWORD			m_dPhase;		


public:
	// メソッド
	CGameMain(CMain* pMain);
	~CGameMain();

	HRESULT Init();
	void    Loop();
	void    Quit();

	void    GameMain();

	void    GameTutorial();		
	void	GameTutorialPhase();	

	void    GameMulti();

	HRESULT ChangeScreenMode(int nMode=-1);   

};


