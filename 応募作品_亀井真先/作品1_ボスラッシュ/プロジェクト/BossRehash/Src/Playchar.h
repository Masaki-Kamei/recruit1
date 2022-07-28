//=============================================================================
//
//		プレイキャラクターの処理
//																Playchar.h
//=============================================================================

#pragma once

//警告非表示
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)


//ヘッダーファイルのインクルード
#include <stdio.h>
#include <windows.h>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite.h"


//======================================================================
// プレイキャラクター　オブジェクトクラス
class CPcObj : public CBaseObj
{
protected:
	int  m_nShotWait;
	int  m_nDifShotWait;
	int  m_nProAtkWait;
	int  m_nCharShotWait;
	int  m_nBoundShotWait;

	int  m_nProAtkTime;

	int  m_nDoorTime;


public:
	void Update() override;

	// コンストラクタ（オブジェクトの初期化）
	CPcObj(CGameMain* pGMain);
	~CPcObj();

};
//======================================================================
// プレイキャラクター　プロシージャクラス
class CPcProc : public CBaseProc
{
protected:
	CPcObj*			m_pPcObj;
	int             m_nPcNum;

public:
	// アクセス関数
	CPcObj*			    GetPcObjPtr() { return m_pPcObj; }
	int				    GetPcNum() { return m_nPcNum; }
	void				AddPcNum(int Num) { m_nPcNum += Num; }

	CPcProc(CGameMain* pGMain);	// コンストラクタ
	~CPcProc() { ; }

};