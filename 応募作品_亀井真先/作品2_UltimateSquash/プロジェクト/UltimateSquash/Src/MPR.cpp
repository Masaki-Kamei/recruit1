// ============================================================================================
//		�Q�p�X�`��̃g�D�[�������_�����O�̃v���O����
//		�b�R�c�s�������R                           ver 2.8        2020.5.3
//
//																	MPR.cpp
// ============================================================================================
#include "MPR.h"


//------------------------------------------------------------------------
//
//  �R���X�g���N�^�[
//
//------------------------------------------------------------------------
CMPR::CMPR(CShader* pShader)
{
	ZeroMemory(this, sizeof(this));
	m_pD3D = pShader->m_pD3D;
	m_pShader = pShader;

	//  �}���`�p�X�����_�����O�p�e�N�X�`���̐ݒ�
	D3D11_TEXTURE2D_DESC tdesc;
	ZeroMemory(&tdesc, sizeof(D3D11_TEXTURE2D_DESC));
	tdesc.Width = m_pD3D->m_dwWindowWidth;  // �e�N�X�`���̑傫��
	tdesc.Height = m_pD3D->m_dwWindowHeight;
	tdesc.MipLevels = 1;     // �~�b�v�}�b�v�E���x����
	tdesc.ArraySize = 1;
	tdesc.MiscFlags = 0;
	//tdesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT; // �e�N�X�`���E�t�H�[�}�b�g
	tdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // �e�N�X�`���E�t�H�[�}�b�g
	tdesc.SampleDesc.Count = 1;
	tdesc.SampleDesc.Quality = 0;
	tdesc.Usage = D3D11_USAGE_DEFAULT;
	tdesc.BindFlags = D3D11_BIND_RENDER_TARGET |      // �`��^�[�Q�b�g
		D3D11_BIND_SHADER_RESOURCE;       // �V�F�[�_�Ŏg��
	tdesc.CPUAccessFlags = 0;
	m_pD3D->m_pDevice->CreateTexture2D(&tdesc, NULL, &m_pMPR_Tex);

	// �e�N�X�`���[�p�@�����_�[�^�[�Q�b�g�r���[�쐬
	D3D11_RENDER_TARGET_VIEW_DESC DescRT;
	DescRT.Format = tdesc.Format;
	DescRT.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	DescRT.Texture2D.MipSlice = 0;
	m_pD3D->m_pDevice->CreateRenderTargetView(m_pMPR_Tex, &DescRT, &m_pMPR_TexRTV);

	// �e�N�X�`���p�@�V�F�[�_�[���\�[�X�r���[(SRV)�쐬	
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));
	SRVDesc.Format = tdesc.Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = tdesc.MipLevels;
	m_pD3D->m_pDevice->CreateShaderResourceView(m_pMPR_Tex, &SRVDesc, &m_pMPR_TexSRV);

	// �}�b�v�e�N�X�`���������_�[�^�[�Q�b�g�ɂ���ۂ̃f�v�X�X�e���V���r���[�p�̃e�N�X�`���[���쐬
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = m_pD3D->m_dwWindowWidth;
	descDepth.Height = m_pD3D->m_dwWindowWidth;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	m_pD3D->m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pMPR_DSTex);

	//���̃e�N�X�`���[�ɑ΂��f�v�X�X�e���V���r���[(DSV)���쐬
	m_pD3D->m_pDevice->CreateDepthStencilView(m_pMPR_DSTex, NULL, &m_pMPR_DSTexDSV);

	// -------------------------------------------------------------------------------------
	DWORD dwWidth = m_pD3D->m_dwWindowWidth;
	DWORD dwHeight = m_pD3D->m_dwWindowHeight;

	//�o�[�e�b�N�X�o�b�t�@�[�쐬
	//�C�����邱�ƁBz�l���P�ȏ�ɂ��Ȃ��B�N���b�v��Ԃ�z=1�͍ł������Ӗ�����B���������ĕ`�悳��Ȃ��B
	MPRVertex vertices[] =
	{
		VECTOR3(0,              (float)dwHeight, 0), VECTOR2(0,1),      //���_1  ����
		VECTOR3((float)dwWidth, (float)dwHeight, 0), VECTOR2(1,1),      //���_2�@�E��
		VECTOR3(0,                            0, 0), VECTOR2(0,0),      //���_3�@����
		VECTOR3((float)dwWidth,               0, 0), VECTOR2(1,0),      //���_4�@�E��
	};

	// �o�[�e�b�N�X�o�b�t�@�쐬����
	D3D11_BUFFER_DESC bd;
	//bd.Usage          = D3D11_USAGE_DEFAULT;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(MPRVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferMPR)))
	{
		MessageBox(0, _T("MPR �o�[�e�b�N�X�o�b�t�@�[�쐬���s"), NULL, MB_OK);
	}


}
//------------------------------------------------------------------------
//
//	�f�X�g���N�^	
//
//------------------------------------------------------------------------
CMPR::~CMPR()
{
	SAFE_RELEASE(m_pMPR_Tex);		//  �}���`�p�X�����_�����O�p�e�N�X�`��    // -- 2020.5.3
	SAFE_RELEASE(m_pMPR_TexRTV);
	SAFE_RELEASE(m_pMPR_TexSRV);
	SAFE_RELEASE(m_pMPR_DSTex);
	SAFE_RELEASE(m_pMPR_DSTexDSV);

	SAFE_RELEASE(m_pVertexBufferMPR);

}


//------------------------------------------------------------------------
//
//	Render MPR����	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CMPR::RenderMPR()
{

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pMPR_VS, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pMPR_PS, NULL, 0);

	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferMPR);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferMPR);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pMPR_VertexLayout);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �T���v���[���Z�b�g
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetSamplers(1, 1, &m_pD3D->m_pSampleBorder);

	//Z�o�b�t�@�𖳌���
	m_pD3D->m_pDeviceContext->OMSetRenderTargets(1, &m_pD3D->m_pBackBuffer_TexRTV, NULL);

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(MPRVertex);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferMPR, &stride, &offset);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_MPR     cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferMPR, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{

		//�r���[�|�[�g�T�C�Y��n���i�N���C�A���g�̈�̉��Əc�j
		cb.ViewPort.x = m_pD3D->m_dwWindowWidth;
		cb.ViewPort.y = m_pD3D->m_dwWindowHeight;
		cb.Info = m_vInfo;
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferMPR, 0);
	}

	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pMPR_TexSRV);   // MPR�}�b�v�e�N�X�`��

	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(4, 0);

	//Z�o�b�t�@��L����
	m_pD3D->SetZBuffer(TRUE);

}

