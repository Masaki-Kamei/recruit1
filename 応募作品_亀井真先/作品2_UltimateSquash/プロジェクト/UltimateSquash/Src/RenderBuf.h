//=============================================================================
//
//		描画バッファの処理
//
//		(丸影・ＨＤＲ対応)
//																RenderBuf.h
//=============================================================================
#pragma once
#include "GameMain.h"

class CGameMain;
class CSprite;
class CSpriteImage;
class CBaseProc;
// --------------------------------------------------------------------------------------------------
// 3D(ビルボード)フォント描画バッファ構造体
// 
//   表示指定
//   3Dオブジェクトの中で優先順位でソートされて表示される。
// 
// --------------------------------------------------------------------------------------------------
struct BILL_FONT_DATA
{
	VECTOR3  vPos;              // 表示位置
	VECTOR2  vSize;             // 表示サイズ
	TCHAR    szText[512];       // 表示するテキスト
	int      fontsize;          // フォントサイズ
	DWORD    colorABGR;         // 文字色　colorABGRは、ABGRの指定。例：白色は(0x00ffffff)
	float    fAlpha;            // 透明度
	TCHAR    szFontName[256];   // フォント名
};

// --------------------------------------------------------------------------------------------------
// 3D(ビルボード)スプライト描画バッファ構造体
// 
//   表示指定
//   3Dオブジェクトの中で優先順位でソートされて表示される。
// 
// --------------------------------------------------------------------------------------------------
struct BILL_SPRITE_DATA
{
	CSprite*      pSprite;    // スプライトオブジェクト
	CSpriteImage* pImage;     // スプライトイメージオブジェクト
	VECTOR3       vPos;       // 表示位置
	VECTOR2       vSize;      // 表示サイズ
	VECTOR2       vSrcPos;    // パターン位置
	VECTOR2       vSrcSize;   // パターンサイズ
	float         fAlpha;     // 透明度
};


// --------------------------------------------------------------------------------------------------
// 描画バッファ構造体
// 
// 
// --------------------------------------------------------------------------------------------------
struct RENDER_DATA
{
	DWORD			dwMeshKind;			// メッシュ種別
										//   (1:FbxStatic 2:FbxStaticDisplace 3:FbxSkin 4:FbxSkinDisplace 5:Wave 7:BBox 21:パーティクル 22:ビルボード 23:炎ビルボード 24:ビルボードメッシュ 31:火炎流体 51:ビルボードテキスト 52:ビルボードスプライト)
	DWORD			dwFlag;				// フラグ(1:アルファブレンド 2:加算合成  9:Ｚバッファ無効)
	DWORD			dwPri;				// 描画の優先度(大きいほど先に描画。標準値は100)
										//   (9999:空 1000:マップ 100:スキン・スタティックメッシュ 40:波 30:レーザー・火の玉・パーティクル等 25:立木等 20:BBox )
	float			fEyeLen;			// カメラからの距離
	void*			pMesh;				// メッシュアドレス
	void*			pObj;				// オブジェクト
	MATRIX4X4		mWorld;				// ワールドマトリックス

	std::vector<BILL_FONT_DATA> m_BillFontArray;		// ビルボードフォント描画バッファ配列
	VECTOR3			vLight;				// 光源ベクトル
	DWORD			dwSC;				// 丸影か（0:丸影無し  1:丸影）
	std::vector<BILL_SPRITE_DATA> m_BillSpriteArray;	// ビルボードスプライト描画バッファ配列

	// 演算子オーバーロードで比較関数を定義
	// (降順に並べる  キー1：dwPri　キー2：fEyeLen )
	bool operator<(const RENDER_DATA& another) const {
		bool bRet = false;
		// 降順に並べる
		//   キー1：dwPri　　キー2：fEyeLen
		if (dwPri > another.dwPri ||
			(dwPri == another.dwPri  && fEyeLen > another.fEyeLen))
		{
			bRet = true;
		}
		return bRet;
	}
};

// --------------------------------------------------------------------------------------------------
// スプライトと＆フォントの描画バッファ構造体
// 
//   表示指定
//   (3Dオブジェクト・ビルボードより手前に表示される。表示順は、セットされた順)
// 
// --------------------------------------------------------------------------------------------------
struct DRAW_SPRITE_FONT_DATA
{
	DWORD dwKind;            // 種別(1:スプライト 2:フォント 3:直線 4:4角形)
	CSprite* pSprite;        // スプライトオブジェクト
	CSpriteImage* pImage;    // スプライトイメージオブジェクト
	float posX;              // 表示位置　左上　Ｘ座標
	float posY;              // 表示位置　左上　Ｙ座標
	DWORD srcX;              // パターン位置　Ｘ座標
	DWORD srcY;              // パターン位置　Ｙ座標
	DWORD srcwidth;          // パターンサイズ　幅
	DWORD srcheight;         // パターンサイズ　高さ
	DWORD destwidth;         // 表示サイズ　幅
	DWORD destheight;        // 表示サイズ　高さ
	TCHAR  szText[512];      // 表示するテキスト
	int   fontsize;          // フォントサイズ
	DWORD colorABGR;         // 文字色　colorABGRは、ABGRの指定。例：白色は(0x00ffffff)
	float fAlpha;            // 透明度
	TCHAR  szFontName[256];  // フォント名

};

// --------------------------------------------------------------------------------------------------
//
// 描画バッファクラス
//
// --------------------------------------------------------------------------------------------------
class  CRenderBufProc
{
protected:
	CGameMain*		m_pGMain;						// ゲームメインクラス

	std::vector<RENDER_DATA>    m_RenderArray;		// 描画バッファ配列
	std::vector<DRAW_SPRITE_FONT_DATA> m_DrawSpriteFontArray;	// スプライト＆フォント描画バッファ配列

	std::vector<RENDER_DATA>    m_RenderArraySecond;		// 描画バッファ配列
	std::vector<DRAW_SPRITE_FONT_DATA> m_DrawSpriteFontArraySecond;	// スプライト＆フォント描画バッファ配列

public:
	void Clear();
	void SetDraw3DFont(VECTOR3 vPos, TCHAR* szText, VECTOR2 vSize, DWORD colorABGR, float fAlpha = 1.0f, TCHAR szFontName[] = _T(""));
	void SetDraw3DSprite(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, float fAlpha = 1.0f);
	void SetDraw3DSprite(CSprite* pSprite, VECTOR3 vPos);
	void SetDrawSprite(CSprite* pSprite, CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight, float fAlpha = 1.0f);
	void SetDrawSprite(CSprite* pSprite, CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, float fAlpha = 1.0f);
	void SetRender(DWORD dwMeshKind, DWORD dwFlag, DWORD dwPri, void* pMesh, void* pObj, MATRIX4X4 mWorld, VECTOR3 vLight);

	void SetDraw3DFont(VECTOR3 vPos, TCHAR* szText, VECTOR2 vSize, DWORD colorABGR, DWORD dwPlayerNo, float fAlpha = 1.0f, TCHAR szFontName[] = _T(""));
	void SetDraw3DSprite(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD dwPlayerNo, float fAlpha = 1.0f);
	void SetDraw3DSprite(CSprite* pSprite, VECTOR3 vPos, DWORD dwPlayerNo);
	void SetDrawSprite(CSprite* pSprite, CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight, DWORD dwPlayerNo,float fAlpha = 1.0f);
	void SetDrawSprite(CSprite* pSprite, CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD dwPlayerNo, float fAlpha = 1.0f);
	void SetRender(DWORD dwMeshKind, DWORD dwFlag, DWORD dwPri, void* pMesh, void* pObj, MATRIX4X4 mWorld, VECTOR3 vLight, DWORD dwPlayerNo);

	
	void Render();
	void RenderSecond();
	CRenderBufProc(CGameMain* pGMain);
	~CRenderBufProc();

};

