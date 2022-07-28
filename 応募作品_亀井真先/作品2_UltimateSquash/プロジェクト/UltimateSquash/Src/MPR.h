// ============================================================================================
//		２パス描画のトゥーンレンダリングのプログラム
//		Ｃ３ＤＴｏｏｎ３                           ver 2.8        2020.5.3
//
//																	MPR.h
// ============================================================================================
#pragma once
#include "Direct3D.h"
#include "Shader.h"


//警告非表示
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)

//
// MPR用頂点の構造体
//
struct MPRVertex
{
	VECTOR3 Pos;   //位置
	VECTOR2 UV;	   //テクスチャー座標
};


//
// MPRクラス
//
class CShader;
class CMPR
{
public:
	CDirect3D*            m_pD3D;  // Direct3D11
	CShader*              m_pShader;

	// マルチパスレンダリング用
	ID3D11Texture2D*          m_pMPR_Tex;
	ID3D11RenderTargetView*   m_pMPR_TexRTV;
	ID3D11ShaderResourceView* m_pMPR_TexSRV;
	ID3D11Texture2D*          m_pMPR_DSTex;
	ID3D11DepthStencilView*   m_pMPR_DSTexDSV;

	ID3D11Buffer*             m_pVertexBufferMPR;

	VECTOR2                   m_vInfo;   // エフェクト種別

public:
	// メソッド
	CMPR(CShader* pShader);
	~CMPR();

	void RenderMPR();
};