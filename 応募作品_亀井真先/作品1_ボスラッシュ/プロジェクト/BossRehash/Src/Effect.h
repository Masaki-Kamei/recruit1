//=============================================================================
//
//		映像効果の処理
//																Effect.h
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

#define  ITEMRESQUE   1           // 救急箱
#define  ITEMDOOR     2           // ドア


#define  ITEM_MAX  50

#define  EFFECT_BOM_MAX  50

//======================================================================
// 映像効果・爆発　オブジェクトクラス
class CEffectBomObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2) override;

	void Update() override;

	// コンストラクタ
	CEffectBomObj(CGameMain* pGMain);
	~CEffectBomObj();

};
//======================================================================
// 映像効果・爆発　プロシージャクラス
class CEffectBomProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2);

	CEffectBomProc(CGameMain* pGMain);	// コンストラクタ
	~CEffectBomProc() { ; }	// デストラクタ

};
//=================================================================================================================
//======================================================================
// アイテム　オブジェクトクラス
class CItemObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2, DWORD) override;

	void Update() override;

	// コンストラクタ
	CItemObj(CGameMain* pGMain);
	~CItemObj();

};
//======================================================================
// アイテム　プロシージャクラス
class CItemProc : public CBaseProc
{
public:
	void Update() override;
	CItemProc(CGameMain* pGMain);	// コンストラクタ
	~CItemProc() { ; }	// デストラクタ

};

//=================================================================================================================


//======================================================================
// 映像効果　プロシージャクラス
class CEffectProc : public CBaseProc
{
public:
	CEffectBomProc*		m_pEffectBomProc;

	CItemProc*			m_pItemProc;

public:
	void  SetNonActive();

	CEffectProc(CGameMain* pGMain);	// コンストラクタ
	~CEffectProc() { ; }	// デストラクタ
};
