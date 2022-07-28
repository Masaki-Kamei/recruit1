//=============================================================================
//
//		エフェクトの処理
//																	Effect.h
//=============================================================================

#pragma once
#include "GameMain.h"

#define  PARTICLE_MAX   50
#define  BILLBOARD_MAX  20
#define  BILLFIRE_MAX   500

#define  BILLPENETBALL_MAX   500
#define  BILLSHOCKWAVE_MAX  20
#define  BILLENERGYDISK_MAX  30

#define  BILLBOARD_ID  1

#define  LETTEREFFECT_MAX   500

#define  LENO_SHAKEBESIDETYPE				1
#define  LENO_SHAKEVERTICALTYPE				2
#define  LENO_EXPANISIONTYPE				3
#define  LENO_RIZETYPE						4
#define  LENO_SHAKERANDOMTYPE				5


// 
class CDirect3D;
// ========================================================================================
//
//	パーティクル
//（ポイントスプライトでパーティクルを実現）
//
// ========================================================================================
//
// パーティクル構造体
//
struct PART
{
	VECTOR3 Pos;
	VECTOR3 Dir;
	float       Speed;
	int         BirthFrame;
	PART()
	{
		ZeroMemory(this, sizeof(PART));
	}
};
//
// 頂点の構造体
//
struct PARTICLE_VERTEX
{
	VECTOR3 Pos; //位置
};
struct BILLBOARD_VERTEX
{
	VECTOR3 Pos; //位置
	VECTOR2 UV; //テクスチャー座標
};

// -----------------------------------------------------------------------------
//	パーティクルのオブジェクトクラス
//（ポイントスプライトでパーティクルを実現）
//
// ----------------------------------------------------------------------------
class CParticleObj : public CBaseObj
{
protected:
	// 
	CDirect3D*	   m_pD3D;
	CShader*       m_pShader;
	FLOAT          m_fAlpha;
	float          m_fSize;  // パーティクルのサイズ
	int            m_MaxParticle;
	VECTOR3        m_vEmitPos;
	PART*          m_pPartArray;
	int            m_Frame;
	int            m_FrameEnd;
	float          m_fSpeed;  // パーティクルの移動スピード
	int            m_iBarthFrame;     // パーティクルの移動開始までの最大待ち時間（ランダム）


	ID3D11Buffer*  m_pVertexBuffer;
	ID3D11ShaderResourceView* m_pTexture;//テクスチャー（パーティクルプロシージャのテクスチャアドレスをセットするだけ）

public:	
	// 
	CParticleObj(CGameMain*  pGMain, int MaxParticle );
	virtual	~CParticleObj();

	void Init(int MaxParticle);
	HRESULT SetSrc();

	BOOL Start(VECTOR3 vEmitPos, VECTOR3 vNormal = VECTOR3(0.0f,0.0f,0.0f)) override;
	BOOL Start(VECTOR3 vEmitPos, DWORD dwPlayerNo, VECTOR3 vNormal = VECTOR3(0.0f, 0.0f, 0.0f)) override;	
	void Update() override;
	void Render();
	void RenderParticle(MATRIX4X4 W, MATRIX4X4 V, MATRIX4X4 P); 

	void SetTexture(ID3D11ShaderResourceView* pTexture) { m_pTexture = pTexture; }

};
// ========================================================================================
//
//	パーティクルのプロシージャクラス
//
// ========================================================================================
class CParticleProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //テクスチャー（用意するのはリソースビューだけでいい）
public:
	BOOL Start(VECTOR3 vEmitPos, VECTOR3 vNormal = VECTOR3(0.0f, 0.0f, 0.0f));
	BOOL Start(VECTOR3 vEmitPos, DWORD dwPlayerNo, VECTOR3 vNormal = VECTOR3(0.0f, 0.0f, 0.0f));
	CParticleProc(CGameMain* pGMain);	// コンストラクタ
	~CParticleProc();	// デストラクタ
};


// ========================================================================================
//
//	ビルボード
//
// ========================================================================================
// ------------------------------------------------------------------------
//	ビルボードのオブジェクトクラス
//
// ------------------------------------------------------------------------
class CBillboardObj : public CBaseObj
{
protected:
	float			m_fDestWidth;
	float			m_fDestHeight;
	DWORD			m_dwSrcX;
	DWORD			m_dwSrcY;
	DWORD			m_dwSrcWidth;
	DWORD			m_dwSrcHeight;
public:

	// 
	CDirect3D*	   m_pD3D;
	CShader*       m_pShader;
	VECTOR3        m_vPos;
	VECTOR2        m_vUVOffset;
	VECTOR2        m_vUVScale; 
	DWORD          m_dwNumX;
	DWORD          m_dwNumY;
	DWORD          m_dwFrame;
	FLOAT          m_fAlpha;
	DWORD          m_dwImageWidth;
	DWORD          m_dwImageHeight;

	BOOL		   m_bHitTrigger;	//爆風に当たったかどうか	


	ID3D11Buffer*  m_pVertexBuffer;
	ID3D11ShaderResourceView* m_pTexture;//テクスチャー（ビルボードプロシージャのテクスチャアドレスをセットするだけ）
	CFbxMesh*      m_pMesh;    //メッシュ（ビルボードプロシージャのメッシュアドレスをセットするだけ）

public:
	// 
	CBillboardObj(CGameMain* pGMain);
	virtual	~CBillboardObj();

	virtual void Init();
	virtual HRESULT SetSrc( float fDestWidth, float fDestHeight, DWORD dwSrcX, DWORD dwSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwNumX, DWORD dwNumY);
	virtual DWORD   GetSrcWidth()  {return m_dwSrcWidth;}
	virtual DWORD   GetSrcHeight() {return m_dwSrcHeight;}
	virtual float   GetDestWidth()  {return m_fDestWidth;}
	virtual float   GetDestHeight() {return m_fDestHeight;}

	virtual BOOL Start(VECTOR3 vPos) override;
	virtual void Update() override;
	virtual BOOL Render();
	virtual void RenderMesh();

	virtual BOOL Start(VECTOR3 vPos, BOOL bTrigger) override;

};
// ========================================================================================
//
//	ビルボードのプロシージャクラス
//
// ========================================================================================
class CBillboardProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //テクスチャー（用意するのはリソースビューだけでいい）
	DWORD m_dwImageWidth;
	DWORD m_dwImageHeight;
	CFbxMesh* m_pMesh;  // 半球ビルボードスタティックメッシュ 
public:
	virtual BOOL Start(VECTOR3 vPos);
	virtual HRESULT Load(TCHAR* szFName);

	virtual BOOL Start(VECTOR3 vPos,BOOL bTrigger);

	CBillboardProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CBillboardProc();	// デストラクタ
};

// ========================================================================================
//
//	衝撃波ビルボード
//
// ========================================================================================
// ------------------------------------------------------------------------
//	ビルボードのオブジェクトクラス
//
// ------------------------------------------------------------------------
class CBillShockWaveObj : public CBaseObj
{
protected:
	float			m_fDestWidth;
	float			m_fDestHeight;
	DWORD			m_dwSrcX;
	DWORD			m_dwSrcY;
	DWORD			m_dwSrcWidth;
	DWORD			m_dwSrcHeight;
public:

	// 
	CDirect3D*	   m_pD3D;
	CShader*       m_pShader;
	VECTOR3        m_vPos;
	VECTOR2        m_vUVOffset;
	VECTOR2        m_vUVScale; 
	DWORD          m_dwNumX;
	DWORD          m_dwNumY;
	DWORD          m_dwFrame;
	FLOAT          m_fAlpha;
	DWORD          m_dwImageWidth;
	DWORD          m_dwImageHeight;

	ID3D11Buffer*  m_pVertexBuffer;
	ID3D11ShaderResourceView* m_pTexture;//テクスチャー（ビルボードプロシージャのテクスチャアドレスをセットするだけ）
	CFbxMesh*      m_pMesh;    //メッシュ（ビルボードプロシージャのメッシュアドレスをセットするだけ） 

public:
	// 
	CBillShockWaveObj(CGameMain* pGMain);
	virtual	~CBillShockWaveObj();

	void Init();
	HRESULT SetSrc(float fDestWidth, float fDestHeight, DWORD dwSrcX, DWORD dwSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwNumX, DWORD dwNumY);
	DWORD   GetSrcWidth() { return m_dwSrcWidth; }
	DWORD   GetSrcHeight() { return m_dwSrcHeight; }
	float   GetDestWidth() { return m_fDestWidth; }
	float   GetDestHeight() { return m_fDestHeight; }

	BOOL Start(VECTOR3 vPos) override;
	BOOL Start(VECTOR3 vPos, DWORD dwPlayerNo) override;
	void Update() override;
	BOOL Render();
	void RenderMesh();

};
// ========================================================================================
//
//	衝撃波ビルボードのプロシージャクラス
//
// ========================================================================================
class CBillShockWaveProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //テクスチャー（用意するのはリソースビューだけでいい）
	DWORD m_dwImageWidth;
	DWORD m_dwImageHeight;
	CFbxMesh* m_pMesh;  // 半球ビルボードスタティックメッシュ
public:
	BOOL Start(VECTOR3 vPos);
	BOOL Start(VECTOR3 vPos, DWORD dwPlayerNo);
	HRESULT Load(TCHAR* szFName);
	CBillShockWaveProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CBillShockWaveProc();	// デストラクタ
};
// -----------------------------------------------------------------------------
//	パーティクルのオブジェクトクラス
//（ポイントスプライトでエネルギーディスクを実現）
//
// ----------------------------------------------------------------------------
class CLetterEffectObj : public CBaseObj
{
protected:
	// 
	FLOAT          m_fAlpha;
	float          m_fSize;  // エネルギーディスクのサイズ 
	VECTOR3        m_vEmitPos;
	int            m_Frame;
	int            m_FrameEnd;



	CSprite*		 m_pSprite;
	CSpriteImage*	 m_pImageForegrd;
	CBaseObj*		 vEffObj;
	VECTOR2			 vEffSize;
	VECTOR2			 vEffSrcPos;
	VECTOR2			 vEffSrcSize;
	float			 fEffAlpha;
	BOOL			 bTracTrigger;
	BOOL			 bNonFream;
	VECTOR3			 vEffPos;
	VECTOR3			 vPosGain;


	float			 fNum1;
	BOOL			 bTrigger;
	VECTOR2			 vVarNum1;
	DWORD			 dwPhase;


	DWORD			 dLetterEffectNo;

public:
	// 
	CLetterEffectObj(CGameMain*  pGMain);
	virtual	~CLetterEffectObj();

	void Init();

	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha);
	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha = 1.0f);
	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha, DWORD dwPlayerNo);
	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, DWORD dwPlayerNo, float fAlpha = 1.0f);

	void Update() override;
	void Render();

	void LetterShakeBesideType();
	void LetterShakeVerticalType();
	void LetterExpansionType();
	void LetterRizeType();
	void LetterShakeRandomType();

};
// ========================================================================================
//
//	効果字幕のプロシージャクラス
//
// ========================================================================================
class CLetterEffectProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //テクスチャー（用意するのはリソースビューだけでいい）
public:
	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo=0, float fAlpha=1.0f);
	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo = 0, float fAlpha = 1.0f);
	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, DWORD dNo = 0, float fAlpha = 1.0f);
	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, DWORD dNo = 0, float fAlpha = 1.0f);

	CLetterEffectProc(CGameMain* pGMain);	// コンストラクタ
	~CLetterEffectProc();	// デストラクタ
};


// -----------------------------------------------------------------------------
//	エネルギーディスクのオブジェクトクラス
//（ポイントスプライトで効果字幕を実現）
//
// ----------------------------------------------------------------------------
class CEnergyDiskObj : public CBaseObj
{
protected:
	// 
	FLOAT          m_fAlpha;
	float          m_fSize;  // 効果字幕のサイズ 
	VECTOR3        m_vEmitPos;
	int            m_Frame;
	int            m_FrameEnd;



	CSprite*		 m_pSprite;
	CSpriteImage*	 m_pImageForegrd;
	CBaseObj*		 vEffObj;
	VECTOR2			 vEffSize;
	VECTOR2			 vEffSrcPos;
	VECTOR2			 vEffSrcSize;
	float			 fEffAlpha;
	BOOL			 bTracTrigger;
	BOOL			 bNonFream;
	VECTOR3			 vEffPos;
	VECTOR3			 vPosGain;


	float			 fNum1;
	BOOL			 bTrigger;
	VECTOR2			 vVarNum1;
	BOOL			 bMaxSizeX;
	BOOL			 bMaxSizeY;
	int				 nWrapFrame;



public:
	// 
	CEnergyDiskObj(CGameMain*  pGMain);
	virtual	~CEnergyDiskObj();

	void Init();

	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, float fAlpha);
	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, float fAlpha);

	void Update() override;
	void Render();

};
// ========================================================================================
//
//	エネルギーディスクのプロシージャクラス
//
// ========================================================================================
class CEnergyDiskProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //テクスチャー（用意するのはリソースビューだけでいい）
	CSpriteImage*	 m_pImageForegrd;

public:
	BOOL Start(CSprite* pSprite, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, float fAlpha = 1.0f);
	BOOL Start(CSprite* pSprite, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, float fAlpha = 1.0f);

	CEnergyDiskProc(CGameMain* pGMain);	// コンストラクタ
	~CEnergyDiskProc();	// デストラクタ
};



// ========================================================================================
//
//	エフェクト全体のメインプロシージャクラス
//
// ========================================================================================
class CEffectProc : public CBaseProc
{
public:
	CParticleProc*		m_pParticleProc;
	CBillboardProc*		m_pBillProc;
	CBillShockWaveProc*	m_pShockWaveProc;
	CEnergyDiskProc*	m_pEnergyDiskProc;
	CLetterEffectProc*	m_pLetterEffectProc;


public:
	CEffectProc(CGameMain* pGMain);	// コンストラクタ
	virtual	~CEffectProc() { ; }
};

