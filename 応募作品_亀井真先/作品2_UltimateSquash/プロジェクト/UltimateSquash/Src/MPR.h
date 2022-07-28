// ============================================================================================
//		�Q�p�X�`��̃g�D�[�������_�����O�̃v���O����
//		�b�R�c�s�������R                           ver 2.8        2020.5.3
//
//																	MPR.h
// ============================================================================================
#pragma once
#include "Direct3D.h"
#include "Shader.h"


//�x����\��
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)

//
// MPR�p���_�̍\����
//
struct MPRVertex
{
	VECTOR3 Pos;   //�ʒu
	VECTOR2 UV;	   //�e�N�X�`���[���W
};


//
// MPR�N���X
//
class CShader;
class CMPR
{
public:
	CDirect3D*            m_pD3D;  // Direct3D11
	CShader*              m_pShader;

	// �}���`�p�X�����_�����O�p
	ID3D11Texture2D*          m_pMPR_Tex;
	ID3D11RenderTargetView*   m_pMPR_TexRTV;
	ID3D11ShaderResourceView* m_pMPR_TexSRV;
	ID3D11Texture2D*          m_pMPR_DSTex;
	ID3D11DepthStencilView*   m_pMPR_DSTexDSV;

	ID3D11Buffer*             m_pVertexBufferMPR;

	VECTOR2                   m_vInfo;   // �G�t�F�N�g���

public:
	// ���\�b�h
	CMPR(CShader* pShader);
	~CMPR();

	void RenderMPR();
};