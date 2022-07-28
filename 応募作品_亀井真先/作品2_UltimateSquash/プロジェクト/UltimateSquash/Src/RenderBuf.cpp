//=============================================================================
//
//		描画バッファの処理
//
//		(丸影・ＨＤＲ対応)
//																RenderBuf.cpp
//=============================================================================
#include  "RenderBuf.h"
#include  "Playchar.h"
#include  "Enemy.h"
#include  "Weapon.h"
#include <algorithm>
#include <functional>

//------------------------------------------------------------------------
//
//	描画バッファクラスのコンストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CRenderBufProc::CRenderBufProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;

}

//------------------------------------------------------------------------
//
//	描画バッファクラスのデストラクタ	
//
//  引数　なし
//
//------------------------------------------------------------------------
CRenderBufProc::~CRenderBufProc()
{
	;
}
//------------------------------------------------------------------------
//
//	描画バッファ配列のクリヤー	
//
//  引数　なし
//
//
//------------------------------------------------------------------------
void CRenderBufProc::Clear()
{
	for (DWORD i = 0; i < m_RenderArray.size(); i++)
	{
		if (m_RenderArray[i].m_BillFontArray.size() > 0)
		{
			m_RenderArray[i].m_BillFontArray.clear();			// 配列削除
			m_RenderArray[i].m_BillFontArray.shrink_to_fit();	// 不要メモリ解放
		}
		if (m_RenderArray[i].m_BillSpriteArray.size() > 0)
		{
			m_RenderArray[i].m_BillSpriteArray.clear();			// 配列削除
			m_RenderArray[i].m_BillSpriteArray.shrink_to_fit();	// 不要メモリ解放
		}
	}
	m_RenderArray.clear();					// 配列削除
	m_RenderArray.shrink_to_fit();			// 不要メモリ解放
	m_DrawSpriteFontArray.clear();			// 配列削除
	m_DrawSpriteFontArray.shrink_to_fit();	// 不要メモリ解放

	for (DWORD i = 0; i < m_RenderArraySecond.size(); i++)
	{
		if (m_RenderArraySecond[i].m_BillFontArray.size() > 0)
		{
			m_RenderArraySecond[i].m_BillFontArray.clear();			// 配列削除
			m_RenderArraySecond[i].m_BillFontArray.shrink_to_fit();	// 不要メモリ解放
		}
		if (m_RenderArraySecond[i].m_BillSpriteArray.size() > 0)
		{
			m_RenderArraySecond[i].m_BillSpriteArray.clear();			// 配列削除
			m_RenderArraySecond[i].m_BillSpriteArray.shrink_to_fit();	// 不要メモリ解放
		}
	}
	m_RenderArraySecond.clear();					// 配列削除
	m_RenderArraySecond.shrink_to_fit();			// 不要メモリ解放
	m_DrawSpriteFontArraySecond.clear();			// 配列削除
	m_DrawSpriteFontArraySecond.shrink_to_fit();	// 不要メモリ解放
	
}


//------------------------------------------------------------------------
//
//	描画バッファクラスのセット	
//
//  引数　
//  DWORD			dwMeshKind;			// メッシュ種別
//										 (1:FbxStatic 2:FbxStaticDisplace 3:FbxSkin 5:Wave 7:BBox 21:パーティクル 22:ビルボード 23:炎ビルボード)
//  DWORD			dwFlag;				// フラグ(1:アルファブレンド 2:加算合成 9:Ｚバッファ無効)
//  DWORD			dwPri;				// 描画の優先度(大きいほど先に描画。標準値は100)
										//   (9999:空 1000:マップ 100:スキン・スタティックメッシュ 40:波 30:レーザー・火の玉・パーティクル等  25:立木等 20:BBox )
//  void*			pMesh;				// メッシュアドレス
//  void*			pObj;				// ベースオブジェクト
//  MATRIX4X4		mWorld;				// ワールドマトリックス
//  VECTOR3			vLight;				// 光源ベクトル
//
//------------------------------------------------------------------------
void CRenderBufProc::SetRender(DWORD dwMeshKind, DWORD dwFlag, DWORD dwPri, void* pMesh, void*	pObj, MATRIX4X4 mWorld, VECTOR3 vLight)
{
	RENDER_DATA rd;
	rd.dwMeshKind = dwMeshKind;
	rd.dwFlag = dwFlag;
	rd.dwPri = dwPri;
	rd.fEyeLen = 0.0f;
	rd.pMesh = pMesh;
	rd.pObj = pObj;
	rd.mWorld = mWorld;
	rd.vLight = vLight;

	m_RenderArray.push_back(rd);	// m_pRenderjArrayにオブジェクトを登録する

}

//------------------------------------------------------------------------
//
//	描画バッファクラスのビルボードフォントのセット	
// 
//   画面に表示するビルボードテキストの表示指定
// 
//  引数　
//		VECTOR3   vPos              表示位置
//		TCHAR*    szText            表示するテキスト
//		VECTOR2   vSize             表示サイズ
//		DWORD     colorABGR;         // 文字色　colorABGRは、ABGRの指定。例：白色は(0x00ffffff)
//		float     fAlpha;            // 透明度(省略可)
//		TCHAR     szFontName[256];   // フォント名(省略可)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDraw3DFont(VECTOR3 vPos, TCHAR* szText, VECTOR2 vSize, DWORD colorABGR, float fAlpha, TCHAR szFontName[])
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);

	RENDER_DATA rd;
	rd.dwMeshKind = 51;    // メッシュ種別   51:ビルボードテキスト
	rd.dwFlag = 1;         // フラグ(1:アルファブレンド)
	rd.dwPri = 25;         // 描画の優先度(25)
	rd.fEyeLen = magnitude(vPos - m_pGMain->m_vEyePt);
	rd.pMesh = NULL;
	rd.pObj = NULL;
	rd.mWorld = mWorld;
	rd.vLight = VECTOR3(0, 0, 0);

	BILL_FONT_DATA bf;
	_tcscpy_s(bf.szText, szText);
	bf.vPos = vPos;
	bf.vSize = vSize;
	bf.fontsize = vSize.y * 100;
	bf.colorABGR = colorABGR;
	bf.fAlpha = fAlpha;
	_tcscpy_s(bf.szFontName, szFontName);

	rd.m_BillFontArray.push_back(bf);	// rdのm_pBillFontArrayにデータを登録する

	m_RenderArray.push_back(rd);	// m_pRenderjArrayにオブジェクトを登録する

}


//------------------------------------------------------------------------
//
//	描画バッファクラスの3D(ビルボード)スプライトのセット	
// 
//   画面に表示するビルボードスプライトの表示指定
// 
//  引数　
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		VECTOR3 vPos             表示位置
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		float fAlpha;            透明度(省略可)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDraw3DSprite(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, float fAlpha)
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation( vPos.x, vPos.y, vPos.z);

	RENDER_DATA rd;
	rd.dwMeshKind = 52;    // メッシュ種別   52:ビルボードスプライト
	rd.dwFlag = 1;         // フラグ(1:アルファブレンド)
	rd.dwPri = 25;         // 描画の優先度(25)
	rd.fEyeLen = magnitude(vPos - m_pGMain->m_vEyePt);
	rd.pMesh = NULL;
	rd.pObj = NULL;
	rd.mWorld = mWorld;
	rd.vLight = VECTOR3(0, 0, 0);

	BILL_SPRITE_DATA bs;
	bs.pSprite = pSprite;
	bs.pImage = pImage;
	bs.vPos = vPos;
	bs.vSize = vSize;
	bs.vSrcPos = vSrcPos;
	bs.vSrcSize = vSrcSize;
	bs.fAlpha = fAlpha;

	rd.m_BillSpriteArray.push_back(bs);	// rdのm_pBillFontArrayにデータを登録する

	m_RenderArray.push_back(rd);	// m_pRenderjArrayにオブジェクトを登録する

}

//------------------------------------------------------------------------
//
//	描画バッファクラスの3D(ビルボード)スプライトのセット	
// 
//   画面に表示するビルボードスプライトの表示指定
// 
//  引数　
//		CSprite* pSprite         スプライト
//		VECTOR3 vPos             表示位置
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDraw3DSprite(CSprite* pSprite, VECTOR3 vPos)
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation( vPos.x, vPos.y, vPos.z);

	RENDER_DATA rd;
	rd.dwMeshKind = 52;    // メッシュ種別   52:ビルボードスプライト
	rd.dwFlag = 1;         // フラグ(1:アルファブレンド)
	rd.dwPri = 25;         // 描画の優先度(25)
	rd.fEyeLen = magnitude(vPos - m_pGMain->m_vEyePt);
	rd.pMesh = NULL;
	rd.pObj = NULL;
	rd.mWorld = mWorld;
	rd.vLight = VECTOR3(0, 0, 0);

	BILL_SPRITE_DATA bs;
	bs.pSprite = pSprite;
	bs.pImage = NULL;
	bs.vPos = vPos;
	bs.vSize = VECTOR2(0, 0);
	bs.vSrcPos = VECTOR2(0, 0);
	bs.vSrcSize = VECTOR2(0, 0);
	bs.fAlpha = 1.0f;

	rd.m_BillSpriteArray.push_back(bs);	// rdのm_pBillFontArrayにデータを登録する

	m_RenderArray.push_back(rd);	// m_pRenderjArrayにオブジェクトを登録する

}

//------------------------------------------------------------------------
//
//	描画スプライトバッファクラスのセット	
// 
//   画面に表示するスプライトの表示指定
//   (3Dオブジェクトより手前に表示される。表示順は、セットされた順)
// 
//  引数　
//		CSprite* pSprite         スプライト
//  	CSpriteImage* pImage;    // スプライトイメージ
//  	float posX;              // 表示位置　左上　Ｘ座標
//  	float posY;              // 表示位置　左上　Ｙ座標
//  	DWORD srcX;              // パターン位置　Ｘ座標
//  	DWORD srcY;              // パターン位置　Ｙ座標
//  	DWORD srcwidth;          // パターンサイズ　幅
//  	DWORD srcheight;         // パターンサイズ　高さ
//  	DWORD destwidth;         // 表示サイズ　幅
//  	DWORD destheight;        // 表示サイズ　高さ
//		float fAlpha;            // 透明度(省略値1.0f)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDrawSprite(CSprite* pSprite, CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight, float fAlpha)
{
	DRAW_SPRITE_FONT_DATA dsf;

	dsf.dwKind = 1;         // 1:スプライト描画
	dsf.pSprite = pSprite;
	dsf.pImage = pImage;    // スプライトイメージ
	dsf.posX = posX;
	dsf.posY = posY;
	dsf.srcX = srcX;
	dsf.srcY = srcY;
	dsf.srcwidth = srcwidth;
	dsf.srcheight = srcheight;
	dsf.destwidth = destwidth;
	dsf.destheight = destheight;
	dsf.fAlpha = fAlpha;

	m_DrawSpriteFontArray.push_back(dsf);	// m_pDrawSpriteFontArrayにデータを登録する
}

//------------------------------------------------------------------------
//
//	描画スプライトバッファクラスのセット	
// 
//   画面に表示するスプライトの表示指定
//   (3Dオブジェクトより手前に表示される。表示順は、セットされた順)
// 
//  引数　
//		CSprite* pSprite         スプライト
//  	CSpriteImage* pImage;    // スプライトイメージ
//  	float posX;              // 表示位置　左上　Ｘ座標
//  	float posY;              // 表示位置　左上　Ｙ座標
//  	DWORD srcX;              // パターン位置　Ｘ座標
//  	DWORD srcY;              // パターン位置　Ｙ座標
//  	DWORD srcwidth;          // パターンサイズ　幅
//  	DWORD srcheight;         // パターンサイズ　高さ
//		float fAlpha;            // 透明度(省略値1.0f)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDrawSprite(CSprite* pSprite, CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, float fAlpha)
{
	DRAW_SPRITE_FONT_DATA dsf;

	dsf.dwKind = 1;         // 1:スプライト描画
	dsf.pSprite = pSprite;
	dsf.pImage = pImage;    // スプライトイメージ
	dsf.posX = posX;
	dsf.posY = posY;
	dsf.srcX = srcX;
	dsf.srcY = srcY;
	dsf.srcwidth = srcwidth;
	dsf.srcheight = srcheight;
	dsf.destwidth = srcwidth;
	dsf.destheight = srcheight;
	dsf.fAlpha = fAlpha;

	m_DrawSpriteFontArray.push_back(dsf);	// m_pDrawSpriteFontArrayにデータを登録する
}

//------------------------------------------------------------------------
//	描画バッファクラスのセット	
//
//  引数　
//  DWORD			dwMeshKind;			// メッシュ種別
//										 (1:FbxStatic 2:FbxStaticDisplace 3:FbxSkin 5:Wave 7:BBox 21:パーティクル 22:ビルボード 23:炎ビルボード)
//  DWORD			dwFlag;				// フラグ(1:アルファブレンド 2:加算合成 9:Ｚバッファ無効)
//  DWORD			dwPri;				// 描画の優先度(大きいほど先に描画。標準値は100)
										//   (9999:空 1000:マップ 100:スキン・スタティックメッシュ 40:波 30:レーザー・火の玉・パーティクル等  25:立木等 20:BBox )
//  void*			pMesh;				// メッシュアドレス
//  void*			pObj;				// ベースオブジェクト
//  MATRIX4X4		mWorld;				// ワールドマトリックス
//  VECTOR3			vLight;				// 光源ベクトル
//
//------------------------------------------------------------------------
void CRenderBufProc::SetRender(DWORD dwMeshKind, DWORD dwFlag, DWORD dwPri, void* pMesh, void*	pObj, MATRIX4X4 mWorld, VECTOR3 vLight, DWORD dwPlayerNo)
{
	RENDER_DATA rd;
	rd.dwMeshKind = dwMeshKind;
	rd.dwFlag = dwFlag;
	rd.dwPri = dwPri;
	rd.fEyeLen = 0.0f;
	rd.pMesh = pMesh;
	rd.pObj = pObj;
	rd.mWorld = mWorld;
	rd.vLight = vLight;

	if(dwPlayerNo==SECONDPLAYER)m_RenderArraySecond.push_back(rd);	// m_pRenderjArrayにオブジェクトを登録する
	else m_RenderArray.push_back(rd);
}

//------------------------------------------------------------------------
//	描画バッファクラスのビルボードフォントのセット	
// 
//   画面に表示するビルボードテキストの表示指定
// 
//  引数　
//		VECTOR3   vPos              表示位置
//		TCHAR*    szText            表示するテキスト
//		VECTOR2   vSize             表示サイズ
//		DWORD     colorABGR;         // 文字色　colorABGRは、ABGRの指定。例：白色は(0x00ffffff)
//		float     fAlpha;            // 透明度(省略可)
//		TCHAR     szFontName[256];   // フォント名(省略可)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDraw3DFont(VECTOR3 vPos, TCHAR* szText, VECTOR2 vSize, DWORD colorABGR, DWORD dwPlayerNo, float fAlpha, TCHAR szFontName[])
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);

	RENDER_DATA rd;
	rd.dwMeshKind = 51;    // メッシュ種別   51:ビルボードテキスト
	rd.dwFlag = 1;         // フラグ(1:アルファブレンド)
	rd.dwPri = 25;         // 描画の優先度(25)
	rd.fEyeLen = magnitude(vPos - m_pGMain->m_vEyePt);
	rd.pMesh = NULL;
	rd.pObj = NULL;
	rd.mWorld = mWorld;
	rd.vLight = VECTOR3(0, 0, 0);

	BILL_FONT_DATA bf;
	_tcscpy_s(bf.szText, szText);
	bf.vPos = vPos;
	bf.vSize = vSize;
	bf.fontsize = vSize.y * 100;
	bf.colorABGR = colorABGR;
	bf.fAlpha = fAlpha;
	_tcscpy_s(bf.szFontName, szFontName);

	rd.m_BillFontArray.push_back(bf);	// rdのm_pBillFontArrayにデータを登録する

	if (dwPlayerNo == SECONDPLAYER)m_RenderArraySecond.push_back(rd);	// m_pRenderjArrayにオブジェクトを登録する
	else m_RenderArray.push_back(rd);

}


//------------------------------------------------------------------------
//	描画バッファクラスの3D(ビルボード)スプライトのセット	
// 
//   画面に表示するビルボードスプライトの表示指定
// 
//  引数　
//		CSprite* pSprite         スプライト
//		CSpriteImage* pImage     スプライトイメージ
//		VECTOR3 vPos             表示位置
//		VECTOR2 vSize            表示サイズ
//		VECTOR2 vSrcPos          パターン位置
//		VECTOR2 vSrcSize         パターンサイズ
//		float fAlpha;            透明度(省略可)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDraw3DSprite(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD dwPlayerNo, float fAlpha)
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);

	RENDER_DATA rd;
	rd.dwMeshKind = 52;    // メッシュ種別   52:ビルボードスプライト
	rd.dwFlag = 1;         // フラグ(1:アルファブレンド)
	rd.dwPri = 25;         // 描画の優先度(25)
	rd.fEyeLen = magnitude(vPos - m_pGMain->m_vEyePt);
	rd.pMesh = NULL;
	rd.pObj = NULL;
	rd.mWorld = mWorld;
	rd.vLight = VECTOR3(0, 0, 0);

	BILL_SPRITE_DATA bs;
	bs.pSprite = pSprite;
	bs.pImage = pImage;
	bs.vPos = vPos;
	bs.vSize = vSize;
	bs.vSrcPos = vSrcPos;
	bs.vSrcSize = vSrcSize;
	bs.fAlpha = fAlpha;

	rd.m_BillSpriteArray.push_back(bs);	// rdのm_pBillFontArrayにデータを登録する

	if (dwPlayerNo == SECONDPLAYER)m_RenderArraySecond.push_back(rd);	// m_pRenderjArrayにオブジェクトを登録する
	else m_RenderArray.push_back(rd);

}

//------------------------------------------------------------------------
//	描画バッファクラスの3D(ビルボード)スプライトのセット	
// 
//   画面に表示するビルボードスプライトの表示指定
// 
//  引数　
//		CSprite* pSprite         スプライト
//		VECTOR3 vPos             表示位置
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDraw3DSprite(CSprite* pSprite, VECTOR3 vPos, DWORD dwPlayerNo)
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);

	RENDER_DATA rd;
	rd.dwMeshKind = 52;    // メッシュ種別   52:ビルボードスプライト
	rd.dwFlag = 1;         // フラグ(1:アルファブレンド)
	rd.dwPri = 25;         // 描画の優先度(25)
	rd.fEyeLen = magnitude(vPos - m_pGMain->m_vEyePt);
	rd.pMesh = NULL;
	rd.pObj = NULL;
	rd.mWorld = mWorld;
	rd.vLight = VECTOR3(0, 0, 0);

	BILL_SPRITE_DATA bs;
	bs.pSprite = pSprite;
	bs.pImage = NULL;
	bs.vPos = vPos;
	bs.vSize = VECTOR2(0, 0);
	bs.vSrcPos = VECTOR2(0, 0);
	bs.vSrcSize = VECTOR2(0, 0);
	bs.fAlpha = 1.0f;

	rd.m_BillSpriteArray.push_back(bs);	// rdのm_pBillFontArrayにデータを登録する

	if (dwPlayerNo == SECONDPLAYER)m_RenderArraySecond.push_back(rd);	// m_pRenderjArrayにオブジェクトを登録する
	else m_RenderArray.push_back(rd);

}

//------------------------------------------------------------------------
//	描画スプライトバッファクラスのセット	
// 
//   画面に表示するスプライトの表示指定
//   (3Dオブジェクトより手前に表示される。表示順は、セットされた順)
// 
//  引数　
//		CSprite* pSprite         スプライト
//  	CSpriteImage* pImage;    // スプライトイメージ
//  	float posX;              // 表示位置　左上　Ｘ座標
//  	float posY;              // 表示位置　左上　Ｙ座標
//  	DWORD srcX;              // パターン位置　Ｘ座標
//  	DWORD srcY;              // パターン位置　Ｙ座標
//  	DWORD srcwidth;          // パターンサイズ　幅
//  	DWORD srcheight;         // パターンサイズ　高さ
//  	DWORD destwidth;         // 表示サイズ　幅
//  	DWORD destheight;        // 表示サイズ　高さ
//		float fAlpha;            // 透明度(省略値1.0f)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDrawSprite(CSprite* pSprite, CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight, DWORD dwPlayerNo, float fAlpha)
{
	DRAW_SPRITE_FONT_DATA dsf;

	dsf.dwKind = 1;         // 1:スプライト描画
	dsf.pSprite = pSprite;
	dsf.pImage = pImage;    // スプライトイメージ
	dsf.posX = posX;
	dsf.posY = posY;
	dsf.srcX = srcX;
	dsf.srcY = srcY;
	dsf.srcwidth = srcwidth;
	dsf.srcheight = srcheight;
	dsf.destwidth = destwidth;
	dsf.destheight = destheight;
	dsf.fAlpha = fAlpha;

	if (dwPlayerNo == SECONDPLAYER)m_DrawSpriteFontArraySecond.push_back(dsf);	// m_pDrawSpriteFontArrayにデータを登録する
	else m_DrawSpriteFontArray.push_back(dsf);
}

//------------------------------------------------------------------------
//	描画スプライトバッファクラスのセット	
// 
//   画面に表示するスプライトの表示指定
//   (3Dオブジェクトより手前に表示される。表示順は、セットされた順)
// 
//  引数　
//		CSprite* pSprite         スプライト
//  	CSpriteImage* pImage;    // スプライトイメージ
//  	float posX;              // 表示位置　左上　Ｘ座標
//  	float posY;              // 表示位置　左上　Ｙ座標
//  	DWORD srcX;              // パターン位置　Ｘ座標
//  	DWORD srcY;              // パターン位置　Ｙ座標
//  	DWORD srcwidth;          // パターンサイズ　幅
//  	DWORD srcheight;         // パターンサイズ　高さ
//		float fAlpha;            // 透明度(省略値1.0f)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDrawSprite(CSprite* pSprite, CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD dwPlayerNo, float fAlpha)
{
	DRAW_SPRITE_FONT_DATA dsf;

	dsf.dwKind = 1;         // 1:スプライト描画
	dsf.pSprite = pSprite;
	dsf.pImage = pImage;    // スプライトイメージ
	dsf.posX = posX;
	dsf.posY = posY;
	dsf.srcX = srcX;
	dsf.srcY = srcY;
	dsf.srcwidth = srcwidth;
	dsf.srcheight = srcheight;
	dsf.destwidth = srcwidth;
	dsf.destheight = srcheight;
	dsf.fAlpha = fAlpha;

	if (dwPlayerNo == SECONDPLAYER)m_DrawSpriteFontArraySecond.push_back(dsf);	// m_pDrawSpriteFontArrayにデータを登録する
	else m_DrawSpriteFontArray.push_back(dsf);
}


//------------------------------------------------------------------------
//
//	描画バッファクラスの描画	
//
//  引数　なし
//
//
//------------------------------------------------------------------------
void CRenderBufProc::Render()
{
	float ClearColor[4] = { 0,0,0,1 };// クリア色作成　RGBAの順

	//m_pGMain->m_pD3D->ClearRenderTarget(ClearColor);    // 通常の画面クリヤー


	// 視点からの距離の設定
	for (DWORD i = 0; i < m_RenderArray.size(); i++)
	{
		m_RenderArray[i].fEyeLen = magnitude(m_pGMain->m_vEyePt - GetPositionVector(m_RenderArray[i].mWorld));
	}

	// -----------------------------------------------------------------------------------------------------------
	// vectorのsortを使って、描画順に並べ替え
	std::sort(m_RenderArray.begin(), m_RenderArray.end());    // 比較関数（演算子オーバーロード）を使用してソート

	

	// ------------------------------------------------------------------------------------------------------------
	//	レンダリング
	for (DWORD i = 0; i < m_RenderArray.size(); i++)
	{
		// ブレンドステート・Ｚバッファの設定  ------------------------------------------------------
		if (m_RenderArray[i].dwFlag == 1)
		{
			// 透明色のブレンディングを設定
			UINT mask = 0xffffffff;
			m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateTrapen, NULL, mask);
		}
		else if (m_RenderArray[i].dwFlag == 2)
		{
			// 加算合成のブレンディングを設定
			UINT mask = 0xffffffff;
			m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateAdd, NULL, mask);
		}
		else if (m_RenderArray[i].dwFlag == 9)
		{
			// Zバッファを無効化
			m_pGMain->m_pD3D->SetZBuffer(FALSE); // Zバッファを無効化
		}

		if (m_RenderArray[i].dwMeshKind == 24)			//	 ビルボードメッシュ 
		{
			((CBillShockWaveObj*)m_RenderArray[i].pObj)->RenderMesh();
		}
		else if (m_RenderArray[i].dwMeshKind == 51)			//	 ビルボードフォント
		{
			m_pGMain->m_pFont->Draw3D(m_RenderArray[i].m_BillFontArray[0].vPos, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vEyePt,
								m_RenderArray[i].m_BillFontArray[0].szText,
								m_RenderArray[i].m_BillFontArray[0].vSize, m_RenderArray[i].m_BillFontArray[0].colorABGR,
								m_RenderArray[i].m_BillFontArray[0].fAlpha, m_RenderArray[i].m_BillFontArray[0].szFontName);
		}
		else if (m_RenderArray[i].dwMeshKind == 52)			//	 ビルボードスプライト
		{
			if (m_RenderArray[i].m_BillSpriteArray[0].pImage)
			{
				m_RenderArray[i].m_BillSpriteArray[0].pSprite->Draw3D(m_RenderArray[i].m_BillSpriteArray[0].pImage, m_RenderArray[i].m_BillSpriteArray[0].vPos,
					m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vEyePt,
					m_RenderArray[i].m_BillSpriteArray[0].vSize, m_RenderArray[i].m_BillSpriteArray[0].vSrcPos,
					m_RenderArray[i].m_BillSpriteArray[0].vSrcSize, m_RenderArray[i].m_BillSpriteArray[0].fAlpha);
			}
			else {
				m_RenderArray[i].m_BillSpriteArray[0].pSprite->Draw3D(m_RenderArray[i].m_BillSpriteArray[0].vPos,
					m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vEyePt);
			}
		}
		// ブレンドステート・Ｚバッファのリセット-----------------------------------------------------
		if (m_RenderArray[i].dwFlag == 1 || m_RenderArray[i].dwFlag == 2)
		{
			// 通常のブレンディングに戻す
			UINT mask = 0xffffffff;
			m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateTrapen, NULL, mask);
		}
		else if (m_RenderArray[i].dwFlag == 9)
		{
			// Zバッファを有効化
			m_pGMain->m_pD3D->SetZBuffer(TRUE); // Zバッファを有効化

		}


	}

	// ---------------------------------------------------------------------------------------------------------------------
//	描画スプライト＆フォントバッファからスプライトとテキストの描画
//   (3Dオブジェクトより手前に表示される。)
	for (DWORD i = 0; i < m_DrawSpriteFontArray.size(); i++)
	{
		if (m_DrawSpriteFontArray[i].dwKind == 1)  // スプライト描画
		{
			if (m_DrawSpriteFontArray[i].pImage)
			{
				m_DrawSpriteFontArray[i].pSprite->Draw(m_DrawSpriteFontArray[i].pImage, m_DrawSpriteFontArray[i].posX, m_DrawSpriteFontArray[i].posY,
					m_DrawSpriteFontArray[i].srcX, m_DrawSpriteFontArray[i].srcY,
					m_DrawSpriteFontArray[i].srcwidth, m_DrawSpriteFontArray[i].srcheight,
					m_DrawSpriteFontArray[i].destwidth, m_DrawSpriteFontArray[i].destheight,
					m_DrawSpriteFontArray[i].fAlpha);
			}
			else {
				m_DrawSpriteFontArray[i].pSprite->Draw(m_DrawSpriteFontArray[i].posX, m_DrawSpriteFontArray[i].posY);
			}
		}
	}


}

//------------------------------------------------------------------------
//	描画バッファクラスの描画	
//
//  引数　なし
//
//
//------------------------------------------------------------------------
void CRenderBufProc::RenderSecond()
{
	float ClearColor[4] = { 0,0,0,1 };// クリア色作成　RGBAの順

	//m_pGMain->m_pD3D->ClearRenderTarget(ClearColor);    // 通常の画面クリヤー


	// 視点からの距離の設定
	for (DWORD i = 0; i < m_RenderArraySecond.size(); i++)
	{
		m_RenderArraySecond[i].fEyeLen = magnitude(m_pGMain->m_vEyePtSecond - GetPositionVector(m_RenderArraySecond[i].mWorld));
	}

	// -----------------------------------------------------------------------------------------------------------
	// vectorのsortを使って、描画順に並べ替え
	std::sort(m_RenderArraySecond.begin(), m_RenderArraySecond.end());    // 比較関数（演算子オーバーロード）を使用してソート



	// ------------------------------------------------------------------------------------------------------------
	//	レンダリング
	for (DWORD i = 0; i < m_RenderArraySecond.size(); i++)
	{
		// ブレンドステート・Ｚバッファの設定  ------------------------------------------------------
		if (m_RenderArraySecond[i].dwFlag == 1)
		{
			// 透明色のブレンディングを設定
			UINT mask = 0xffffffff;
			m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateTrapen, NULL, mask);
		}
		else if (m_RenderArraySecond[i].dwFlag == 2)
		{
			// 加算合成のブレンディングを設定
			UINT mask = 0xffffffff;
			m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateAdd, NULL, mask);
		}
		else if (m_RenderArraySecond[i].dwFlag == 9)
		{
			// Zバッファを無効化
			m_pGMain->m_pD3D->SetZBuffer(FALSE); // Zバッファを無効化
		}

		if (m_RenderArraySecond[i].dwMeshKind == 24)			//	 ビルボードメッシュ 
		{
			((CBillShockWaveObj*)m_RenderArraySecond[i].pObj)->RenderMesh();
		}
		else if (m_RenderArraySecond[i].dwMeshKind == 51)			//	 ビルボードフォント
		{
			m_pGMain->m_pFont->Draw3D(m_RenderArraySecond[i].m_BillFontArray[0].vPos, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vEyePtSecond,
				m_RenderArraySecond[i].m_BillFontArray[0].szText,
				m_RenderArraySecond[i].m_BillFontArray[0].vSize, m_RenderArraySecond[i].m_BillFontArray[0].colorABGR,
				m_RenderArraySecond[i].m_BillFontArray[0].fAlpha, m_RenderArraySecond[i].m_BillFontArray[0].szFontName);
		}
		else if (m_RenderArraySecond[i].dwMeshKind == 52)			//	 ビルボードスプライト
		{
			if (m_RenderArraySecond[i].m_BillSpriteArray[0].pImage)
			{
				m_RenderArraySecond[i].m_BillSpriteArray[0].pSprite->Draw3D(m_RenderArraySecond[i].m_BillSpriteArray[0].pImage, m_RenderArraySecond[i].m_BillSpriteArray[0].vPos,
					m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vEyePtSecond,
					m_RenderArraySecond[i].m_BillSpriteArray[0].vSize, m_RenderArraySecond[i].m_BillSpriteArray[0].vSrcPos,
					m_RenderArraySecond[i].m_BillSpriteArray[0].vSrcSize, m_RenderArraySecond[i].m_BillSpriteArray[0].fAlpha);
			}
			else {
				m_RenderArraySecond[i].m_BillSpriteArray[0].pSprite->Draw3D(m_RenderArraySecond[i].m_BillSpriteArray[0].vPos,
					m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vEyePtSecond);
			}
		}
		// ブレンドステート・Ｚバッファのリセット------------------------------------------------------
		if (m_RenderArraySecond[i].dwFlag == 1 || m_RenderArraySecond[i].dwFlag == 2)
		{
			// 通常のブレンディングに戻す
			UINT mask = 0xffffffff;
			m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateTrapen, NULL, mask);
		}
		else if (m_RenderArraySecond[i].dwFlag == 9)
		{
			// Zバッファを有効化
			m_pGMain->m_pD3D->SetZBuffer(TRUE); // Zバッファを有効化

		}


	}

	// ---------------------------------------------------------------------------------------------------------------------
//	描画スプライト＆フォントバッファからスプライトとテキストの描画
//   (3Dオブジェクトより手前に表示される。)
	for (DWORD i = 0; i < m_DrawSpriteFontArraySecond.size(); i++)
	{
		if (m_DrawSpriteFontArraySecond[i].dwKind == 1)  // スプライト描画
		{
			if (m_DrawSpriteFontArraySecond[i].pImage)
			{
				m_DrawSpriteFontArraySecond[i].pSprite->Draw(m_DrawSpriteFontArraySecond[i].pImage, m_DrawSpriteFontArraySecond[i].posX, m_DrawSpriteFontArraySecond[i].posY,
					m_DrawSpriteFontArraySecond[i].srcX, m_DrawSpriteFontArraySecond[i].srcY,
					m_DrawSpriteFontArraySecond[i].srcwidth, m_DrawSpriteFontArraySecond[i].srcheight,
					m_DrawSpriteFontArraySecond[i].destwidth, m_DrawSpriteFontArraySecond[i].destheight,
					m_DrawSpriteFontArraySecond[i].fAlpha);
			}
			else {
				m_DrawSpriteFontArraySecond[i].pSprite->Draw(m_DrawSpriteFontArraySecond[i].posX, m_DrawSpriteFontArraySecond[i].posY);
			}
		}
	}


}

