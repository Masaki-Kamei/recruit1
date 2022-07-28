//=============================================================================
//
//		�G�t�F�N�g�̏���
//																	Effect.cpp
//=============================================================================

#include "Effect.h"
#include "Playchar.h"
#include "Enemy.h"
#include "Weapon.h"


// ========================================================================================
//
//	�G�t�F�N�g�@���C���v���V�[�W���N���X
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	�G�t�F�N�g�@���C���v���V�[�W���N���X�̃R���X�g���N�^	
//
//------------------------------------------------------------------------
CEffectProc::CEffectProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pParticleProc = new CParticleProc(pGMain);     // �p�[�e�B�N���v���V�[�W���̐���
	m_pProcArray.push_back(m_pParticleProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pBillProc     = new CBillboardProc(pGMain);     // �r���{�[�h�v���V�[�W���̐���
	m_pProcArray.push_back(m_pBillProc);        // �v���V�[�W�����v���V�[�W���z��ɓo�^����


	m_pShockWaveProc = new CBillShockWaveProc(pGMain);     // �r���{�[�h�v���V�[�W���̐���
	m_pProcArray.push_back(m_pShockWaveProc);        // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnergyDiskProc = new CEnergyDiskProc(pGMain);     // �G�l���M�[�f�B�X�N�v���V�[�W���̐���
	m_pProcArray.push_back(m_pEnergyDiskProc);        // �G�l���M�[�f�B�X�N���v���V�[�W���z��ɓo�^����


	m_pLetterEffectProc = new CLetterEffectProc(pGMain);     // ���ʎ����v���V�[�W���̐���
	m_pProcArray.push_back(m_pLetterEffectProc);        // ���ʎ������v���V�[�W���z��ɓo�^����


};


// =====================================================================================================
// 
// �e�v���V�[�W�����̏���
// 
// =====================================================================================================
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���v���V�[�W���N���X�̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CParticleProc::CParticleProc(CGameMain* pGMain) : CBaseProc( pGMain)
{
	const int ParticleNumMax = 30; // ��̃p�[�e�B�N���I�u�W�F�N�g���̃p�[�e�B�N���̐�

	// �p�[�e�B�N���e�N�X�`��
	TCHAR szFName[] = _T("Data/Image/particle3.png");

	//�e�N�X�`���[�ǂݍ���
	m_pTexture = NULL;
	if (FAILED(m_pGMain->m_pD3D->CreateShaderResourceViewFromFile(szFName, &m_pTexture, 3)))
	{
		MessageBox(0, _T("�p�[�e�B�N���@�e�N�X�`���[��ǂݍ��߂܂���"),_T(""), MB_OK);
		return;
	}
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		// ��̃p�[�e�B�N���I�u�W�F�N�g���̃p�[�e�B�N���̐���ݒ肷��
		m_pObjArray.push_back(new CParticleObj( m_pGMain, ParticleNumMax));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		((CParticleObj*)(m_pObjArray[i]))->SetTexture( m_pTexture ); // �p�[�e�B�N���e�N�X�`���̃Z�b�g
	}

};
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���v���V�[�W���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CParticleProc::~CParticleProc()
{
	SAFE_RELEASE(m_pTexture);
};

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���v���V�[�W���N���X�̊J�n	
//
//	�E�p�[�e�B�N���I�u�W�F�N�g�z��̒�����A�󂢂Ă���p�[�e�B�N����T���ĊJ�n����
//
//  VECTOR3 vEmitPos          �p�[�e�B�N���̔����ʒu
//  VECTOR3 vNormal           �p�[�e�B�N���̔����ʂ̖@���i�ȗ��j
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CParticleProc::Start(VECTOR3 vEmitPos, VECTOR3 vNormal)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vEmitPos, vNormal);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//	�p�[�e�B�N���v���V�[�W���N���X�̊J�n	
//
//	�E�p�[�e�B�N���I�u�W�F�N�g�z��̒�����A�󂢂Ă���p�[�e�B�N����T���ĊJ�n����
//
//  VECTOR3 vEmitPos          �p�[�e�B�N���̔����ʒu
//  VECTOR3 vNormal           �p�[�e�B�N���̔����ʂ̖@���i�ȗ��j
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CParticleProc::Start(VECTOR3 vEmitPos, DWORD dwPlayerNo, VECTOR3 vNormal)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vEmitPos, dwPlayerNo, vNormal);
			return TRUE;
		}
	}
	return FALSE;
};

// ========================================================================================
//
//	�p�[�e�B�N���I�u�W�F�N�g�N���X
//�i�|�C���g�X�v���C�g�Ńp�[�e�B�N���������j
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̃R���X�g���N�^	
//
//  int MaxParticle          �p�[�e�B�N���̐�
//
//------------------------------------------------------------------------
CParticleObj::CParticleObj(CGameMain* pGMain, int MaxParticle) : CBaseObj( pGMain)
{
	m_pD3D = m_pGMain->m_pD3D;
	m_pShader = m_pGMain->m_pShader;
	m_fAlpha = 0.0f;
	m_fSize = 0.0f;
	m_MaxParticle = 0;
	m_vEmitPos = VECTOR3(0,0,0);
	m_pPartArray = NULL;
	m_Frame = 0;
	m_FrameEnd = 0;
	m_fSpeed = 0.0f;  // �p�[�e�B�N���̈ړ��X�s�[�h
	m_iBarthFrame = 0;     // �p�[�e�B�N���̈ړ��J�n�܂ł̍ő�҂����ԁi�����_���j

	m_pVertexBuffer = NULL;
	m_pTexture = NULL; //�e�N�X�`���[

	//	������
	Init(MaxParticle);

	// �o�[�e�b�N�X�o�b�t�@���쐬
	SetSrc();
}
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CParticleObj::~CParticleObj()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_DELETE_ARRAY(m_pPartArray);
}

//------------------------------------------------------------------------
//	�p�[�e�B�N���I�u�W�F�N�g�̏������֐�
//
//  �e��ݒ�l�̏�����
//
//  int MaxParticle        �p�[�e�B�N���̐�
//
//  �߂�l�@�@�@�Ȃ�
//------------------------------------------------------------------------
void CParticleObj::Init( int MaxParticle )
{
	m_bActive = FALSE;
	m_fAlpha = 1.0f;
	m_fSize = 0.1f;    // �p�[�e�B�N���̃T�C�Y 
	m_MaxParticle = MaxParticle;   // ��L�p�[�e�B�N���v���V�[�W���Ŏw�肵���p�[�e�B�N����
	m_pPartArray = new PART[m_MaxParticle];    // �p�[�e�B�N���z��̐���
	m_FrameEnd = 60;	// �p�[�e�B�N����\�����Ă��鎞��
	m_fSpeed = 0.015f;  // �p�[�e�B�N���̈ړ��X�s�[�h
	m_iBarthFrame = 20;     // �p�[�e�B�N���̈ړ��J�n�܂ł̍ő�҂����ԁi�����_���j
}

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̃o�[�e�B�N�X�o�b�t�@�쐬�ƃe�N�X�`���̓ǂݍ���	
//	�i�W�I���g���֘A���������D�����ł́h�_�h�p�j	
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CParticleObj::SetSrc()
{
	//�o�[�e�b�N�X
	PARTICLE_VERTEX vertices[] =
	{
		VECTOR3(0.0f, 0.0f, 0.0f)
	};

	// �Q�x�ڈȍ~�ɏ���������邱�Ƃ̑΍�
	SAFE_RELEASE(m_pVertexBuffer);

	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(PARTICLE_VERTEX) * 1;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̊J�n	
//  �E�p�[�e�B�N�����w��ʒu���甭��������B
//  �E����������@�����W�Ŏw��ł���B�ȗ�����ƑS�����֔�������B
//
//  VECTOR3 vEmitPos          �p�[�e�B�N���̔����ʒu
//  VECTOR3 vNormal           �p�[�e�B�N���̔����ʂ̖@���i�ȗ��j
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CParticleObj::Start(VECTOR3 vEmitPos, VECTOR3 vNormal)
{
	if (m_bActive)
	{
		// ���łɕ\�����̂Ƃ�
		return FALSE;

	}else {
		// �J�n����
		m_bActive = TRUE;
		m_fAlpha  = 0.9f;
		m_vEmitPos = vEmitPos;
		m_Frame = 0;

		// �@�������𒆐S�Ƃ��ă����_�������ɔ���������
		VECTOR3 vDist, vMin, vMax;
		vDist.x = (1.0f - fabsf(vNormal.x))/2;
		vDist.y = (1.0f - fabsf(vNormal.y))/2;
		vDist.z = (1.0f - fabsf(vNormal.z))/2;

		if (vNormal.x < 0)
		{
			vMin.x = vNormal.x - vDist.x;
			vMax.x = 0.0f + vDist.x;
		}else {
			vMin.x = 0.0f - vDist.x;
			vMax.x = vNormal.x + vDist.x;
		}
		if (vNormal.y < 0)
		{
			vMin.y = vNormal.y - vDist.y;
			vMax.y = 0.0f + vDist.y;
		}else {
			vMin.y = 0.0f - vDist.y;
			vMax.y = vNormal.y + vDist.y;
		}
		if (vNormal.z < 0)
		{
			vMin.z = vNormal.z - vDist.z;
			vMax.z = 0.0f + vDist.z;
		}else {
			vMin.z = 0.0f - vDist.z;
			vMax.z = vNormal.z + vDist.z;
		}

		// �p�[�e�B�N���̊J�n
		for (int i = 0; i<m_MaxParticle; i++)
		{
			m_pPartArray[i].Pos = m_vEmitPos;
			m_pPartArray[i].Dir.x = ((float)rand() / (float)RAND_MAX) * (vMax.x - vMin.x) + vMin.x;
			m_pPartArray[i].Dir.y = ((float)rand() / (float)RAND_MAX) * (vMax.y - vMin.y) + vMin.y;
			m_pPartArray[i].Dir.z = ((float)rand() / (float)RAND_MAX) * (vMax.z - vMin.z) + vMin.z;
			m_pPartArray[i].Dir = normalize(m_pPartArray[i].Dir);
			m_pPartArray[i].Speed = (5 + ((float)rand() / (float)RAND_MAX)) * m_fSpeed;
			m_pPartArray[i].BirthFrame = (int)(((float)rand() / RAND_MAX) * m_iBarthFrame);
		}
		return TRUE;
	}
}
//------------------------------------------------------------------------
//	�p�[�e�B�N���I�u�W�F�N�g�̊J�n	
//  �E�p�[�e�B�N�����w��ʒu���甭��������B
//  �E����������@�����W�Ŏw��ł���B�ȗ�����ƑS�����֔�������B
//
//  VECTOR3 vEmitPos          �p�[�e�B�N���̔����ʒu
//  VECTOR3 vNormal           �p�[�e�B�N���̔����ʂ̖@���i�ȗ��j
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CParticleObj::Start(VECTOR3 vEmitPos, DWORD dwPlayerNo,VECTOR3 vNormal)
{
	if (m_bActive)
	{
		// ���łɕ\�����̂Ƃ�
		return FALSE;

	}
	else {
		// �J�n����
		m_bActive = TRUE;
		m_fAlpha = 0.9f;
		m_vEmitPos = vEmitPos;
		m_Frame = 0;
		m_dwPlayerNo = dwPlayerNo;
		// �@�������𒆐S�Ƃ��ă����_�������ɔ���������
		VECTOR3 vDist, vMin, vMax;
		vDist.x = (1.0f - fabsf(vNormal.x)) / 2;
		vDist.y = (1.0f - fabsf(vNormal.y)) / 2;
		vDist.z = (1.0f - fabsf(vNormal.z)) / 2;

		if (vNormal.x < 0)
		{
			vMin.x = vNormal.x - vDist.x;
			vMax.x = 0.0f + vDist.x;
		}
		else {
			vMin.x = 0.0f - vDist.x;
			vMax.x = vNormal.x + vDist.x;
		}
		if (vNormal.y < 0)
		{
			vMin.y = vNormal.y - vDist.y;
			vMax.y = 0.0f + vDist.y;
		}
		else {
			vMin.y = 0.0f - vDist.y;
			vMax.y = vNormal.y + vDist.y;
		}
		if (vNormal.z < 0)
		{
			vMin.z = vNormal.z - vDist.z;
			vMax.z = 0.0f + vDist.z;
		}
		else {
			vMin.z = 0.0f - vDist.z;
			vMax.z = vNormal.z + vDist.z;
		}

		// �p�[�e�B�N���̊J�n
		for (int i = 0; i < m_MaxParticle; i++)
		{
			m_pPartArray[i].Pos = m_vEmitPos;
			m_pPartArray[i].Dir.x = ((float)rand() / (float)RAND_MAX) * (vMax.x - vMin.x) + vMin.x;
			m_pPartArray[i].Dir.y = ((float)rand() / (float)RAND_MAX) * (vMax.y - vMin.y) + vMin.y;
			m_pPartArray[i].Dir.z = ((float)rand() / (float)RAND_MAX) * (vMax.z - vMin.z) + vMin.z;
			m_pPartArray[i].Dir = normalize(m_pPartArray[i].Dir);
			m_pPartArray[i].Speed = (5 + ((float)rand() / (float)RAND_MAX)) * m_fSpeed;
			m_pPartArray[i].BirthFrame = (int)(((float)rand() / RAND_MAX) * m_iBarthFrame);
		}
		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̈ړ��E�X�V����	
//  �E�p�[�e�B�N�����X�V����
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CParticleObj::Update()
{
	if (m_bActive)
	{
		m_Frame++;	// �t���[����i�߂�
		for (int i = 0; i < m_MaxParticle; i++)
		{
			if (m_Frame > m_pPartArray[i].BirthFrame) // ��̃p�[�e�B�N�����\���J�n���ԂɂȂ����Ƃ�
			{
				// �ړ�
				m_pPartArray[i].Pos = m_pPartArray[i].Pos + m_pPartArray[i].Dir * m_pPartArray[i].Speed;

				// �d��
				m_pPartArray[i].Dir = m_pPartArray[i].Dir + VECTOR3(0, -0.049f, 0);
			}
		}

		// �����_�����O
		Render();

		if (m_Frame >= m_FrameEnd) // �\�����ԏI����
		{
			m_bActive = FALSE;
		}

	}
}

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g����ʂɃ����_�����O	
//  �E�p�[�e�B�N����\������
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CParticleObj::Render()
{
	// �\����ԂłȂ��Ƃ�
	if (!m_bActive)  return;
	MATRIX4X4 mView = m_pGMain->m_mView;
	MATRIX4X4 mProj = m_pGMain->m_mProj;
	VECTOR3	  vEyePt = m_pGMain->m_vEyePt;
	if (m_dwPlayerNo == SECONDPLAYER)
	{
		 mView = m_pGMain->m_mViewSecond;
		 mProj = m_pGMain->m_mProjSecond;
		 vEyePt = m_pGMain->m_vEyePtSecond;

	}
	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_POINT, NULL, 0);
	m_pD3D->m_pDeviceContext->GSSetShader(m_pShader->m_pEffect3D_GS_POINT, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(PARTICLE_VERTEX);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//�p�[�e�B�N���P�����P���|�C���g�X�v���C�g�Ƃ���m_MaxParticle���`��
	for (int i = 0; i<m_MaxParticle; i++)
	{
		if (m_FrameEnd < m_Frame + (m_iBarthFrame - m_pPartArray[i].BirthFrame)) continue;

		//�X�̃p�[�e�B�N���́A���_���������[���h�g�����X�t�H�[�������߂�
		MATRIX4X4 mWorld = GetLookatMatrix( m_pPartArray[i].Pos, vEyePt);

		RenderParticle(mWorld, mView, mProj);
	}

	// �ʏ�̃u�����f�B���O�ɖ߂�
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	//�W�I���g���V�F�[�_�[�̃��Z�b�g
	m_pD3D->m_pDeviceContext->GSSetShader(NULL, NULL, 0);

	return;
}
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���������_�����O����	
//
//  MATRIX4X4    W    ���[���h�}�g���b�N�X
//  MATRIX4X4    V    �r���[�}�g���b�N�X
//  MATRIX4X4    P    �v���W�F�N�V�����}�g���b�N�X
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CParticleObj::RenderParticle(MATRIX4X4 W, MATRIX4X4 V, MATRIX4X4 P)
{

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s���n��
		cb.mW = XMMatrixTranspose(W);
		cb.mV = XMMatrixTranspose(V);
		cb.mP = XMMatrixTranspose(P);

		cb.fAlpha    = m_fAlpha;
		cb.fSize     = m_fSize;          // �p�[�e�B�N���̃T�C�Y 
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}

	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->GSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(1, 0);

}

// ========================================================================================
//
//	�r���{�[�h�̃N���X
//
// ========================================================================================

//------------------------------------------------------------------------
//
//	�r���{�[�h�v���V�[�W���N���X�̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CBillboardProc::CBillboardProc(CGameMain* pGMain) : CBaseProc( pGMain)
{
	// �r���{�[�h�e�N�X�`��
	TCHAR szFName[] = _T("Data/Image/Bom3.png");

	// �����r���{�[�h�X�^�e�B�b�N���b�V���̓ǂݍ��� 
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Item/BillSphere.mesh"));

	m_dwProcID = BILLBOARD_ID;	
	// �e�N�X�`���̓ǂݍ���
	m_pTexture = NULL;
	if (FAILED(Load(szFName)))
	{
		return;
	}

	for (DWORD i = 0; i < BILLBOARD_MAX; i++)
	{

		m_pObjArray.push_back(new CBillboardObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		((CBillboardObj*)m_pObjArray[i])->m_pTexture = m_pTexture;            // �v���V�[�W���̃e�N�X�`���A�h���X���Z�b�g����
		((CBillboardObj*)m_pObjArray[i])->m_pMesh = m_pMesh;                  // �v���V�[�W���̃��b�V���A�h���X���Z�b�g����
		((CBillboardObj*)m_pObjArray[i])->m_dwImageHeight = m_dwImageHeight;
		((CBillboardObj*)m_pObjArray[i])->m_dwImageWidth  = m_dwImageWidth;
		((CBillboardObj*)m_pObjArray[i])->SetSrc(12, 12, 0, 0, 64, 64, 4, 3);  //  �r���{�[�h�p�̃o�[�e�b�N�X�o�b�t�@�쐬	
																			 //  float fDestWidth         �\����
																			 //  float fDestHeight        �\������
																			 //  DWORD dwSrcX             �X�v���C�g�̈ʒu�@�w���W
																			 //  DWORD dwSrcY             �X�v���C�g�̈ʒu�@�x���W
																			 //  DWORD dwSrcWidth         �X�v���C�g�̕�
																			 //  DWORD dwSrcHeight        �X�v���C�g�̍���
																			 //  DWORD dwNumX             �A�j���[�V����������X�v���C�g�̐��@�w����
																			 //  DWORD dwNumY             �A�j���[�V����������X�v���C�g�̐��@�x����
		m_pObjArray[i]->SetObjID(m_dwProcID);	

	}
	m_dwBreakNum = 0;
};

//------------------------------------------------------------------------
//
//	�r���{�[�h�v���V�[�W���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CBillboardProc::~CBillboardProc()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_pMesh);
};

//------------------------------------------------------------------------
//
//	�X�v���C�g�C���[�W�̓ǂݍ���	
//
//  TCHAR* szFName            �r���{�[�h�̃e�N�X�`���t�@�C����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CBillboardProc::Load(TCHAR* szFName)
{

	//�e�N�X�`���[�ǂݍ���	�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	if (FAILED(m_pGMain->m_pD3D->CreateShaderResourceViewFromFile(szFName, &m_pTexture, m_dwImageWidth, m_dwImageHeight, 3)))
	{
		MessageBox(0, _T("�r���{�[�h�@�e�N�X�`���[��ǂݍ��߂܂���"), szFName, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�v���V�[�W���̊J�n	
//
//	�E�r���{�[�h�I�u�W�F�N�g�z��̒�����A�󂢂Ă���r���{�[�h��T���ĊJ�n����
//
//  VECTOR3 vPos          �r���{�[�h�̔����ʒu
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CBillboardProc::Start(VECTOR3 vPos)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//
//	�r���{�[�h�v���V�[�W���̊J�n	
//
//	�E�r���{�[�h�I�u�W�F�N�g�z��̒�����A�󂢂Ă���r���{�[�h��T���ĊJ�n����
//
//  VECTOR3 vPos          �r���{�[�h�̔����ʒu
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CBillboardProc::Start(VECTOR3 vPos,BOOL bTrigger)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, bTrigger);
			return TRUE;
		}
	}
	return FALSE;
};


//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CBillboardObj::CBillboardObj(CGameMain* pGMain) : CBaseObj( pGMain)
{
	m_pD3D = m_pGMain->m_pD3D;
	m_pShader = m_pGMain->m_pShader;

	m_fDestWidth  = 0.0f;
	m_fDestHeight = 0.0f;
	m_dwSrcX = 0;
	m_dwSrcY = 0;
	m_dwSrcWidth = 0;
	m_dwSrcHeight = 0;
	m_vPos = VECTOR3(0,0,0);
	m_vUVOffset = VECTOR2(0,0);
	m_vUVScale = VECTOR2(1,1);             
	m_dwNumX = 0;
	m_dwNumY = 0;
	m_dwFrame = 0;
	m_fAlpha = 0.0f;
	m_dwImageWidth = 0;
	m_dwImageHeight = 0;
	m_pVertexBuffer = NULL;
	m_pTexture = NULL;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j

	//�o�E���f�B���O�{�b�N�X�̐���
	float BBoxSize = 5.5;
	VECTOR3 vMin(-BBoxSize, -BBoxSize, -BBoxSize);
	VECTOR3 vMax(BBoxSize, BBoxSize, BBoxSize);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_bHitTrigger = FALSE;
	m_nAtc = 0;

	//	������
	Init();
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CBillboardObj::~CBillboardObj()
{
	SAFE_RELEASE(m_pVertexBuffer);
}
//------------------------------------------------------------------------
//	�r���{�[�h�I�u�W�F�N�g�̏������֐�
//
//  �e��ݒ�l�̏�����
//
//  �����@�@�Ȃ�
//
//  �߂�l�@�@�@�Ȃ�
//------------------------------------------------------------------------
void CBillboardObj::Init()
{
	m_bActive = FALSE;
	m_fAlpha = 0.9f;
}
//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̃o�[�e�B�N�X�o�b�t�@�쐬	
//	�i�W�I���g���֘A���������j	
//
//  float fDestWidth         �\����
//  float fDestHeight        �\������
//  DWORD dwSrcX             �X�v���C�g�̈ʒu�@�w���W
//  DWORD dwSrcY             �X�v���C�g�̈ʒu�@�x���W
//  DWORD dwSrcWidth         �X�v���C�g�̕�
//  DWORD dwSrcHeight        �X�v���C�g�̍���
//  DWORD dwNumX             �A�j���[�V����������X�v���C�g�̐��@�w����
//  DWORD dwNumY             �A�j���[�V����������X�v���C�g�̐��@�x����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CBillboardObj::SetSrc(float fDestWidth, float fDestHeight, DWORD dwSrcX, DWORD dwSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwNumX, DWORD dwNumY)
{
	// �r���{�[�h�p�̔|���S�����쐬���A�o�[�e�b�N�X�o�b�t�@���쐬����
	m_fDestWidth   = fDestWidth;
	m_fDestHeight  = fDestHeight;
	m_dwSrcX       = dwSrcX;
	m_dwSrcY       = dwSrcY;
	m_dwSrcWidth   = dwSrcWidth;
	m_dwSrcHeight  = dwSrcHeight;
	m_dwNumX       = dwNumX;
	m_dwNumY       = dwNumY;

	//�o�[�e�b�N�X�o�b�t�@�[�쐬(�������̍��W�ō쐬)
	BILLBOARD_VERTEX vertices[] =
	{
		VECTOR3(-m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)m_dwSrcY / m_dwImageHeight),                     //���_1  ����
		VECTOR3(m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)m_dwSrcY / m_dwImageHeight),                        //���_2�@�E��   
		VECTOR3(-m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),   //���_3�@����  
		VECTOR3(m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),      //���_4�@�E��
	};

	// �Q�x�ڈȍ~�ɏ���������邱�Ƃ̑΍�
	SAFE_RELEASE(m_pVertexBuffer);

	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(BILLBOARD_VERTEX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̊J�n	
//
//  VECTOR3   vPos     �\���ʒu�i�r���{�[�h�̒��S�_�ʒu���w��j
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CBillboardObj::Start(VECTOR3 vPos)
{
	if (m_bActive) return FALSE;  // ���łɊJ�n��

	m_bActive = TRUE;
	m_dwFrame = 0;
	m_vPos = vPos;
	m_bHitTrigger = FALSE;	

	return TRUE;
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̊J�n	
//
//  VECTOR3   vPos     �\���ʒu�i�r���{�[�h�̒��S�_�ʒu���w��j
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CBillboardObj::Start(VECTOR3 vPos,BOOL bTrigger)
{

	if (m_bActive) return FALSE;  // ���łɊJ�n��

	m_bActive = TRUE;
	m_dwFrame = 0;
	m_vPos = vPos;
	m_bHitTrigger = FALSE;
	m_bDamage = bTrigger;
	m_nAtc = 0;
	return TRUE;
}


//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̍X�V	
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CBillboardObj::Update()
{
	const DWORD dwSpeed = 3;   // �r���{�[�h�̃A�j���[�V�����X�s�[�h	
	DWORD dwIdx;
	m_dwStatus = NORMAL;
	if (!m_bActive) return;

	m_dwFrame++;
	dwIdx = m_dwFrame / dwSpeed;

	if (dwIdx >= m_dwNumX * m_dwNumY)	// �p�^�[���̍Ō�ɒB�����Ƃ�
	{
		m_bActive = FALSE;
		return;
	}

	// �A�j���[�V�����̂��߂̃e�N�X�`���I�t�Z�b�g��ݒ肷��
	m_vUVOffset.x = (float)(dwIdx % m_dwNumX * GetSrcWidth());   // �w�����̕ψ�
	m_vUVOffset.y = (float)(dwIdx / m_dwNumX * GetSrcHeight());  // �x�����̕ψ�
	//�o�E���f�B���O�{�b�N�X�̍X�V
	m_mWorld = XMMatrixTranslation(m_vPos.x, m_vPos.y, m_vPos.z);
	m_pBBox->m_mWorld = m_mWorld;

	//�����̓����������̏���	
	if (m_bHitTrigger != TRUE&&m_bDamage!=TRUE) {
		if (m_pGMain->m_pPcProc->GetPcObjPtr()->Hitcheck(this, m_pBBox)) {
			m_bHitTrigger = TRUE;

		}
	}
	if(m_bDamage==TRUE)
	{
		m_nAtc = 2000;
		if (m_pGMain->m_pEnmProc->Hitcheck(this, m_pBBox, m_pGMain->m_pEnmProc->m_pEnmBallProc->GetProcID()))	
		{
			m_pGMain->m_pEffectProc->m_pLetterEffectProc->AddBreakNum(1);	
		}
		m_pGMain->m_pWeaponProc->m_pWeaponWallProc->Hitcheck(this, m_pBBox);
	}
	//Render();// �����_�����O
	RenderMesh();// �����_�����O(�����r���{�[�h���b�V��)

}
//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g����ʂɃ����_�����O	
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CBillboardObj::Render()
{

	if (!m_bActive) return FALSE;

	//�r���{�[�h�́A���_���������[���h�g�����X�t�H�[�������߂�
	MATRIX4X4 mWorld =	GetLookatMatrix( m_vPos, m_pGMain->m_vEyePt);

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILL, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(BILLBOARD_VERTEX);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));

	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s��A�e�N�X�`���[�I�t�Z�b�g��n��
		cb.mWVP = XMMatrixTranspose(mWorld * m_pGMain->m_mView * m_pGMain->m_mProj);

		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;		// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;		// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVScale.x = 1;
		cb.vUVScale.y = 1;
		cb.fAlpha      = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout_BILL);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(4, 0);

	// �ʏ�̃u�����f�B���O�ɖ߂�
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	return TRUE;
}

//------------------------------------------------------------------------ 
//
//	�r���{�[�h���b�V������ʂɃ����_�����O���鏈��
//
// ����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
void CBillboardObj::RenderMesh()
{

	//�g�p����V�F�[�_�[�̓o�^	
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILLMESH, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//�r���{�[�h�́A���_���������[���h�g�����X�t�H�[�������߂�
	MATRIX4X4 mWorld = GetLookatMatrix(m_vPos, m_pGMain->m_vEyePt);
	// ���b�V���̑傫���Ɋg�傷��ݒ肷��i���X�̃��b�V���͂P���l���̔����j
	MATRIX4X4 mScale = XMMatrixScaling(GetDestWidth(), GetDestHeight(), (GetDestWidth() + GetDestHeight()) / 2);
	mWorld = mScale * mWorld;

	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s��A�e�N�X�`���[�I�t�Z�b�g��n��
		cb.mWVP = XMMatrixTranspose(mWorld * m_pGMain->m_mView * m_pGMain->m_mProj);

		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;			// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;			// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVScale.x = (float)GetSrcWidth() / m_dwImageWidth;		// �e�N�X�`���A�j���[�V������1/����
		cb.vUVScale.y = (float)GetSrcHeight() / m_dwImageHeight;	// �e�N�X�`���A�j���[�V������1/�c��

		cb.fAlpha = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}

	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pFbxStaticMesh_VertexLayout);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�e�N�X�`���[�T���v���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);

	// ���b�V���̕`�揇�����肷��m_dwRenderIdxArray�̐ݒ�
	m_pMesh->SetRenderIdxArray(mWorld, m_pGMain->m_vEyePt);

	// ���b�V���̐������e�N�X�`���[�A�o�[�e�b�N�X�o�b�t�@�A�C���f�b�N�X�o�b�t�@���Z�b�g���āA�����_�����O����
	for (DWORD mi = 0; mi < m_pMesh->m_dwMeshNum; mi++)
	{
		DWORD i = m_pMesh->m_dwRenderIdxArray[mi];

		//�e�N�X�`���[���V�F�[�_�[�ɓn��
		m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

		// �o�[�e�b�N�X�o�b�t�@�[���Z�b�g
		UINT stride = sizeof(StaticVertexNormal);
		UINT offset = 0;
		m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pMesh->m_pMeshArray[i].m_pVertexBuffer, &stride, &offset);

		//�C���f�b�N�X�o�b�t�@�[���Z�b�g
		m_pD3D->m_pDeviceContext->IASetIndexBuffer(m_pMesh->m_pMeshArray[i].m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//�v���~�e�B�u�������_�����O
		// �i�C���f�b�N�X�̐����w�肵�ă����_�����O�j
		m_pD3D->m_pDeviceContext->DrawIndexed(m_pMesh->m_pMeshArray[i].m_dwIndicesNum, 0, 0);
	}

	// �ʏ�̃u�����f�B���O�ɖ߂�
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

}



// ========================================================================================
//
//	�r���{�[�h�̃N���X
//
// ========================================================================================

//------------------------------------------------------------------------
//
//	�Ռ��g�r���{�[�h�v���V�[�W���N���X�̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//
//------------------------------------------------------------------------
CBillShockWaveProc::CBillShockWaveProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �r���{�[�h�e�N�X�`��
	TCHAR szFName[] = _T("Data/Image/Shock_Wave_3_ver1.png");

	// �����r���{�[�h�X�^�e�B�b�N���b�V���̓ǂݍ��� 
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Item/BillSphere.mesh"));

	// �e�N�X�`���̓ǂݍ���
	m_pTexture = NULL;
	if (FAILED(Load(szFName)))
	{
		return;
	}

	for (DWORD i = 0; i < BILLSHOCKWAVE_MAX; i++)
	{
		m_pObjArray.push_back(new CBillShockWaveObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		((CBillShockWaveObj*)m_pObjArray[i])->m_pTexture = m_pTexture;            // �v���V�[�W���̃e�N�X�`���A�h���X���Z�b�g����
		((CBillShockWaveObj*)m_pObjArray[i])->m_pMesh = m_pMesh;                  // �v���V�[�W���̃��b�V���A�h���X���Z�b�g����
		((CBillShockWaveObj*)m_pObjArray[i])->m_dwImageHeight = m_dwImageHeight;
		((CBillShockWaveObj*)m_pObjArray[i])->m_dwImageWidth = m_dwImageWidth;
		((CBillShockWaveObj*)m_pObjArray[i])->SetSrc(2, 2, 0, 0, 64, 64, 4, 2);  //  �r���{�[�h�p�̃o�[�e�b�N�X�o�b�t�@�쐬	
																			 //  float fDestWidth         �\����
																			 //  float fDestHeight        �\������
																			 //  DWORD dwSrcX             �X�v���C�g�̈ʒu�@�w���W
																			 //  DWORD dwSrcY             �X�v���C�g�̈ʒu�@�x���W
																			 //  DWORD dwSrcWidth         �X�v���C�g�̕�
																			 //  DWORD dwSrcHeight        �X�v���C�g�̍���
																			 //  DWORD dwNumX             �A�j���[�V����������X�v���C�g�̐��@�w����
																			 //  DWORD dwNumY             �A�j���[�V����������X�v���C�g�̐��@�x����
	}
};

//------------------------------------------------------------------------
//
//	�Ռ��g�r���{�[�h�v���V�[�W���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CBillShockWaveProc::~CBillShockWaveProc()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_pMesh);
};

//------------------------------------------------------------------------
//
//	�X�v���C�g�C���[�W�̓ǂݍ���	
//
//  TCHAR* szFName            �Ռ��g�r���{�[�h�̃e�N�X�`���t�@�C����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CBillShockWaveProc::Load(TCHAR* szFName)
{

	//�e�N�X�`���[�ǂݍ���	�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	if (FAILED(m_pGMain->m_pD3D->CreateShaderResourceViewFromFile(szFName, &m_pTexture, m_dwImageWidth, m_dwImageHeight, 3)))
	{
		MessageBox(0, _T("�r���{�[�h�@�e�N�X�`���[��ǂݍ��߂܂���"), szFName, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//------------------------------------------------------------------------
//
//	�Ռ��g�r���{�[�h�v���V�[�W���̊J�n	
//
//	�E�r���{�[�h�I�u�W�F�N�g�z��̒�����A�󂢂Ă���r���{�[�h��T���ĊJ�n����
//
//  VECTOR3 vPos          �r���{�[�h�̔����ʒu
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CBillShockWaveProc::Start(VECTOR3 vPos)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);
			return TRUE;
		}
	}
	return FALSE;
};


//------------------------------------------------------------------------
//	�Ռ��g�r���{�[�h�v���V�[�W���̊J�n	
//
//	�E�r���{�[�h�I�u�W�F�N�g�z��̒�����A�󂢂Ă���r���{�[�h��T���ĊJ�n����
//
//  VECTOR3 vPos          �r���{�[�h�̔����ʒu
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CBillShockWaveProc::Start(VECTOR3 vPos, DWORD dwPlayerNo)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, dwPlayerNo);
			return TRUE;
		}
	}
	return FALSE;
};


//------------------------------------------------------------------------
//
//	�Ռ��g�r���{�[�h�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CBillShockWaveObj::CBillShockWaveObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pD3D = m_pGMain->m_pD3D;
	m_pShader = m_pGMain->m_pShader;

	m_fDestWidth = 0.0f;
	m_fDestHeight = 0.0f;
	m_dwSrcX = 0;
	m_dwSrcY = 0;
	m_dwSrcWidth = 0;
	m_dwSrcHeight = 0;
	m_vPos = VECTOR3(0, 0, 0);
	m_vUVOffset = VECTOR2(0, 0);
	m_vUVScale = VECTOR2(1, 1);           
	m_dwNumX = 0;
	m_dwNumY = 0;
	m_dwFrame = 0;
	m_fAlpha = 0.0f;
	m_dwImageWidth = 0;
	m_dwImageHeight = 0;
	m_pVertexBuffer = NULL;
	m_pTexture = NULL;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j

	//	������
	Init();
}

//------------------------------------------------------------------------
//
//	�Ռ��g�r���{�[�h�I�u�W�F�N�g�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CBillShockWaveObj::~CBillShockWaveObj()
{
	SAFE_RELEASE(m_pVertexBuffer);
}
//------------------------------------------------------------------------
//	�r���{�[�h�I�u�W�F�N�g�̏������֐�
//
//  �e��ݒ�l�̏�����
//
//  �����@�@�Ȃ�
//
//  �߂�l�@�@�@�Ȃ�
//------------------------------------------------------------------------
void CBillShockWaveObj::Init()
{
	m_bActive = FALSE;
	m_fAlpha = 0.9f;
}
//------------------------------------------------------------------------
//
//	�Ռ��g�r���{�[�h�I�u�W�F�N�g�̃o�[�e�B�N�X�o�b�t�@�쐬	
//	�i�W�I���g���֘A���������j	
//
//  float fDestWidth         �\����
//  float fDestHeight        �\������
//  DWORD dwSrcX             �X�v���C�g�̈ʒu�@�w���W
//  DWORD dwSrcY             �X�v���C�g�̈ʒu�@�x���W
//  DWORD dwSrcWidth         �X�v���C�g�̕�
//  DWORD dwSrcHeight        �X�v���C�g�̍���
//  DWORD dwNumX             �A�j���[�V����������X�v���C�g�̐��@�w����
//  DWORD dwNumY             �A�j���[�V����������X�v���C�g�̐��@�x����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CBillShockWaveObj::SetSrc(float fDestWidth, float fDestHeight, DWORD dwSrcX, DWORD dwSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwNumX, DWORD dwNumY)
{
	// �r���{�[�h�p�̔|���S�����쐬���A�o�[�e�b�N�X�o�b�t�@���쐬����
	m_fDestWidth = fDestWidth;
	m_fDestHeight = fDestHeight;
	m_dwSrcX = dwSrcX;
	m_dwSrcY = dwSrcY;
	m_dwSrcWidth = dwSrcWidth;
	m_dwSrcHeight = dwSrcHeight;
	m_dwNumX = dwNumX;
	m_dwNumY = dwNumY;

	//�o�[�e�b�N�X�o�b�t�@�[�쐬(�������̍��W�ō쐬)
	BILLBOARD_VERTEX vertices[] =
	{
		VECTOR3(-m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)m_dwSrcY / m_dwImageHeight),                     //���_1  ����
		VECTOR3(m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)m_dwSrcY / m_dwImageHeight),                        //���_2�@�E��   
		VECTOR3(-m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),   //���_3�@����   
		VECTOR3(m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),      //���_4�@�E��
	};

	// �Q�x�ڈȍ~�ɏ���������邱�Ƃ̑΍�
	SAFE_RELEASE(m_pVertexBuffer);

	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(BILLBOARD_VERTEX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//------------------------------------------------------------------------
//
//	�Ռ��g�r���{�[�h�I�u�W�F�N�g�̊J�n	
//
//  VECTOR3   vPos     �\���ʒu�i�r���{�[�h�̒��S�_�ʒu���w��j
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CBillShockWaveObj::Start(VECTOR3 vPos)
{
	if (m_bActive) return FALSE;  // ���łɊJ�n��

	m_bActive = TRUE;
	m_dwFrame = 0;
	m_vPos = vPos;

	return TRUE;
}
//------------------------------------------------------------------------
//	�Ռ��g�r���{�[�h�I�u�W�F�N�g�̊J�n	
//
//  VECTOR3   vPos     �\���ʒu�i�r���{�[�h�̒��S�_�ʒu���w��j
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CBillShockWaveObj::Start(VECTOR3 vPos, DWORD dwPlayerNo)
{
	if (m_bActive) return FALSE;  // ���łɊJ�n��

	m_bActive = TRUE;
	m_dwFrame = 0;
	m_vPos = vPos;
	m_dwPlayerNo = dwPlayerNo;
	return TRUE;
}


//------------------------------------------------------------------------
//
//	�Ռ��g�r���{�[�h�I�u�W�F�N�g�̍X�V	
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CBillShockWaveObj::Update()
{
	const DWORD dwSpeed = 3;   // �r���{�[�h�̃A�j���[�V�����X�s�[�h
	DWORD dwIdx;

	if (!m_bActive) return;

	m_dwFrame++;
	dwIdx = m_dwFrame / dwSpeed;

	if (dwIdx >= m_dwNumX * m_dwNumY)	// �p�^�[���̍Ō�ɒB�����Ƃ�
	{
		m_bActive = FALSE;
		return;
	}

	// �A�j���[�V�����̂��߂̃e�N�X�`���I�t�Z�b�g��ݒ肷��
	m_vUVOffset.x = (float)(dwIdx % m_dwNumX * GetSrcWidth());   // �w�����̕ψ�
	m_vUVOffset.y = (float)(dwIdx / m_dwNumX * GetSrcHeight());  // �x�����̕ψ�

		// ���_�Ƃ̋����v�Z�̂���m_mWorld��ݒ�B�Ȃ��Am_mWorld�̓����_�����O�ɂ͎g���Ă��Ȃ�  
	m_mWorld = XMMatrixTranslation(m_vPos.x, m_vPos.y, m_vPos.z);

	// �r���{�[�h�̃����_�����O  ���b�V�����:24�r���{�[�h���b�V��   �D��x:20
	m_pGMain->m_pRenderBufProc->SetRender(24, 0, 20, NULL, this, m_mWorld, VECTOR3(0, 0, 0), m_dwPlayerNo);  //--2022.03.28.8:30

}
//------------------------------------------------------------------------
//
//	�Ռ��g�r���{�[�h�I�u�W�F�N�g����ʂɃ����_�����O	
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CBillShockWaveObj::Render()
{

	if (!m_bActive) return FALSE;

	//�r���{�[�h�́A���_���������[���h�g�����X�t�H�[�������߂�
	MATRIX4X4 mWorld = GetLookatMatrix(m_vPos, m_pGMain->m_vEyePt);

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILL, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(BILLBOARD_VERTEX);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));

	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s��A�e�N�X�`���[�I�t�Z�b�g��n��
		cb.mWVP = XMMatrixTranspose(mWorld * m_pGMain->m_mView * m_pGMain->m_mProj);

		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;		// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;		// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVScale.x = 1;
		cb.vUVScale.y = 1;
		cb.fAlpha = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout_BILL);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(4, 0);

	// �ʏ�̃u�����f�B���O�ɖ߂�
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	return TRUE;
}

//------------------------------------------------------------------------  
//
//	�Ռ��g�r���{�[�h���b�V������ʂɃ����_�����O���鏈��
//
// ����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
void CBillShockWaveObj::RenderMesh()
{
	MATRIX4X4 mView = m_pGMain->m_mView;
	MATRIX4X4 mProj = m_pGMain->m_mProj;
	VECTOR3	  vEyePt = m_pGMain->m_vEyePt;
	if (m_dwPlayerNo == SECONDPLAYER)
	{
		mView = m_pGMain->m_mViewSecond;
		mProj = m_pGMain->m_mProjSecond;
		vEyePt = m_pGMain->m_vEyePtSecond;

	}

	//�g�p����V�F�[�_�[�̓o�^	
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILLMESH, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//�r���{�[�h�́A���_���������[���h�g�����X�t�H�[�������߂�
	MATRIX4X4 mWorld = GetLookatMatrix(m_vPos, vEyePt);
	// ���b�V���̑傫���Ɋg�傷��ݒ肷��i���X�̃��b�V���͂P���l���̔����j
	MATRIX4X4 mScale = XMMatrixScaling(GetDestWidth(), GetDestHeight(), (GetDestWidth() + GetDestHeight()) / 2);
	mWorld = mScale * mWorld;

	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s��A�e�N�X�`���[�I�t�Z�b�g��n��
		cb.mWVP = XMMatrixTranspose(mWorld * mView * mProj);

		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;			// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;			// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVScale.x = (float)GetSrcWidth() / m_dwImageWidth;		// �e�N�X�`���A�j���[�V������1/����
		cb.vUVScale.y = (float)GetSrcHeight() / m_dwImageHeight;	// �e�N�X�`���A�j���[�V������1/�c��

		cb.fAlpha = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}

	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pFbxStaticMesh_VertexLayout);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�e�N�X�`���[�T���v���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);

	// ���b�V���̕`�揇�����肷��m_dwRenderIdxArray�̐ݒ�
	m_pMesh->SetRenderIdxArray(mWorld, vEyePt);

	// ���b�V���̐������e�N�X�`���[�A�o�[�e�b�N�X�o�b�t�@�A�C���f�b�N�X�o�b�t�@���Z�b�g���āA�����_�����O����
	for (DWORD mi = 0; mi < m_pMesh->m_dwMeshNum; mi++)
	{
		DWORD i = m_pMesh->m_dwRenderIdxArray[mi];

		//�e�N�X�`���[���V�F�[�_�[�ɓn��
		m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

		// �o�[�e�b�N�X�o�b�t�@�[���Z�b�g
		UINT stride = sizeof(StaticVertexNormal);
		UINT offset = 0;
		m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pMesh->m_pMeshArray[i].m_pVertexBuffer, &stride, &offset);

		//�C���f�b�N�X�o�b�t�@�[���Z�b�g
		m_pD3D->m_pDeviceContext->IASetIndexBuffer(m_pMesh->m_pMeshArray[i].m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//�v���~�e�B�u�������_�����O
		// �i�C���f�b�N�X�̐����w�肵�ă����_�����O�j
		m_pD3D->m_pDeviceContext->DrawIndexed(m_pMesh->m_pMeshArray[i].m_dwIndicesNum, 0, 0);
	}

	// �ʏ�̃u�����f�B���O�ɖ߂�
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

}

//------------------------------------------------------------------------
//
//	���ʎ����v���V�[�W���N���X�̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CLetterEffectProc::CLetterEffectProc(CGameMain* pGMain) : CBaseProc(pGMain)
{

	//�e�N�X�`���[�ǂݍ���
	m_pTexture = NULL;
	for (int i = 0; i < LETTEREFFECT_MAX; i++)
	{
		// ��̌��ʎ����I�u�W�F�N�g���̌��ʎ����̐���ݒ肷��
		m_pObjArray.push_back(new CLetterEffectObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}

};
//------------------------------------------------------------------------
//
//	���ʎ����v���V�[�W���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CLetterEffectProc::~CLetterEffectProc()
{
	SAFE_RELEASE(m_pTexture);
};

//------------------------------------------------------------------------
//
//	���ʎ����v���V�[�W���N���X�̊J�n	
//
//	�E���ʎ����I�u�W�F�N�g�z��̒�����A�󂢂Ă�����ʎ�����T���ĊJ�n����
//
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		CBaseObj* pOtherOb       �I�u�W�F�N�g
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		DWORD fFreamEnd			 �\������
//		DWORD dNo				 �������ʂ̎��
//		float fAlpha;            �����x(�ȗ���)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CLetterEffectProc::Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CLetterEffectObj*)m_pObjArray[i])->Start(pSprite, pImage, pOtherObj, vPos,vSize,vSrcPos,vSrcSize,fFreamEnd, dNo,fAlpha);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//
//	���ʎ����v���V�[�W���N���X�̊J�n	
//
//	�E���ʎ����I�u�W�F�N�g�z��̒�����A�󂢂Ă�����ʎ�����T���ĊJ�n����
//
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		VECTOR3 vPos             �\���ʒu
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		DWORD fFreamEnd			 �\������
//		DWORD dNo				 �������ʂ̎��
//		float fAlpha;            �����x(�ȗ���)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CLetterEffectProc::Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CLetterEffectObj*)m_pObjArray[i])->Start(pSprite, pImage, vPos, vSize, vSrcPos, vSrcSize,fFreamEnd, dNo, fAlpha);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//
//	���ʎ����v���V�[�W���N���X�̊J�n	
//
//	�E���ʎ����I�u�W�F�N�g�z��̒�����A�󂢂Ă�����ʎ�����T���ĊJ�n����
//
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		CBaseObj* pOtherOb       �I�u�W�F�N�g
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		DWORD fFreamEnd			 �\������
//		DWORD dNo				 �������ʂ̎��
//		float fAlpha;            �����x(�ȗ���)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CLetterEffectProc::Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, DWORD dNo, float fAlpha)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CLetterEffectObj*)m_pObjArray[i])->Start(pSprite, pImage, pOtherObj, vPos, vSize, vSrcPos, vSrcSize, fFreamEnd, dNo, fAlpha, dwPlayerNo);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//
//	���ʎ����v���V�[�W���N���X�̊J�n	
//
//	�E���ʎ����I�u�W�F�N�g�z��̒�����A�󂢂Ă�����ʎ�����T���ĊJ�n����
//
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		VECTOR3 vPos             �\���ʒu
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		DWORD fFreamEnd			 �\������
//		DWORD dNo				 �������ʂ̎��
//		float fAlpha;            �����x(�ȗ���)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CLetterEffectProc::Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, DWORD dNo, float fAlpha)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CLetterEffectObj*)m_pObjArray[i])->Start(pSprite, pImage, vPos, vSize, vSrcPos, vSrcSize, fFreamEnd, dNo, dwPlayerNo,fAlpha);
			return TRUE;
		}
	}
	return FALSE;
};

// ========================================================================================
//
//	���ʎ����I�u�W�F�N�g�N���X
//�i�|�C���g�X�v���C�g�Ō��ʎ����������j
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	���ʎ����I�u�W�F�N�g�̃R���X�g���N�^	
//
//  int MaxParticle          ���ʎ����̐�
//
//------------------------------------------------------------------------
CLetterEffectObj::CLetterEffectObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_fAlpha = 0.0f;
	m_fSize = 0.0f;
	m_vEmitPos = VECTOR3(0, 0, 0);
	m_Frame = 0;
	m_FrameEnd = 0;

	Init();

	

}
//------------------------------------------------------------------------
//
//	���ʎ����I�u�W�F�N�g�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CLetterEffectObj::~CLetterEffectObj()
{

}

//------------------------------------------------------------------------
//
//	���ʎ����I�u�W�F�N�g�̏������֐�
//
//  �e��ݒ�l�̏�����
//
//  int MaxParticle        ���ʎ����̐�
//
//  �߂�l�@�@�@�Ȃ�
//------------------------------------------------------------------------
void CLetterEffectObj::Init()
{
	m_bActive = FALSE;
	m_FrameEnd = 0;	// ���ʎ�����\�����Ă��鎞��
	m_fAlpha = 1.0f;
	fNum1 = 0;
	bTrigger = FALSE;
	dLetterEffectNo = 0;
	vVarNum1 = VECTOR2(0,0);
	bTracTrigger = FALSE;

}

//------------------------------------------------------------------------
//
//	���ʎ����I�u�W�F�N�g�̊J�n	
//  �E���ʎ������w��ʒu���甭��������B
//  �E����������@�����W�Ŏw��ł���B�ȗ�����ƑS�����֔�������B
//
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		CBaseObj* pOtherOb       �I�u�W�F�N�g
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		DWORD fFreamEnd			 �\������
//		DWORD dNo				 �������ʂ̎��
//		float fAlpha;            �����x(�ȗ���)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//
//------------------------------------------------------------------------
BOOL CLetterEffectObj::Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos,VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha)
{
	if (m_bActive)
	{
		// ���łɕ\�����̂Ƃ�
		return FALSE;

	}
	else {
		// �J�n����
		m_bActive = TRUE;

		//������ϐ��ɑ��
		m_FrameEnd = fFreamEnd;
		m_pSprite = pSprite;
		m_pImageForegrd = pImage;
		vPosGain = vPos;
		vEffObj = pOtherObj;
		vEffSize = vSize;
		vEffSrcPos = vSrcPos;
		vEffSrcSize = vSrcSize;
		fEffAlpha = fAlpha;
		m_Frame = 0;
		fNum1 = Random(-6,6);
		fNum1 = fNum1 / 10;
		dLetterEffectNo = dNo;
		bTrigger = FALSE;
		vVarNum1 = VECTOR2(0, 0);
		bTracTrigger = TRUE;
		dwPhase = 0;

		if(m_FrameEnd<0)	bNonFream = TRUE;
		else
		{
			bNonFream = FALSE;
		}
		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	���ʎ����I�u�W�F�N�g�̊J�n	
//  �E���ʎ������w��ʒu���甭��������B
//  �E����������@�����W�Ŏw��ł���B�ȗ�����ƑS�����֔�������B
//
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		VECTOR3 vPos             �\���ʒu
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		DWORD fFreamEnd			 �\������
//		DWORD dNo				 �������ʂ̎��
//		float fAlpha;            �����x(�ȗ���)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//
//------------------------------------------------------------------------
BOOL CLetterEffectObj::Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha)
{
	if (m_bActive)
	{
		// ���łɕ\�����̂Ƃ�
		return FALSE;

	}
	else {
		// �J�n����
		m_bActive = TRUE;

		//������ϐ��ɑ��
		m_FrameEnd = fFreamEnd;
		m_pSprite = pSprite;
		m_pImageForegrd = pImage;
		vEffPos = vPos;
		vEffSize = vSize;
		vEffSrcPos = vSrcPos;
		vEffSrcSize = vSrcSize;
		fEffAlpha = fAlpha;
		m_Frame = 0;
		fNum1 = 0;
		dLetterEffectNo = dNo;
		bTrigger = FALSE;
		vVarNum1 = VECTOR2(0, 0);
		bTracTrigger = FALSE;
		bNonFream = FALSE;
		dwPhase = 0;

		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	���ʎ����I�u�W�F�N�g�̊J�n	
//  �E���ʎ������w��ʒu���甭��������B
//  �E����������@�����W�Ŏw��ł���B�ȗ�����ƑS�����֔�������B
//
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		CBaseObj* pOtherOb       �I�u�W�F�N�g
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		DWORD fFreamEnd			 �\������
//		DWORD dNo				 �������ʂ̎��
//		float fAlpha;            �����x(�ȗ���)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//
//------------------------------------------------------------------------
BOOL CLetterEffectObj::Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, float fAlpha, DWORD dwPlayerNo)
{
	if (m_bActive)
	{
		// ���łɕ\�����̂Ƃ�
		return FALSE;

	}
	else {
		// �J�n����
		m_bActive = TRUE;
		//������ϐ��ɑ��
		m_dwPlayerNo = dwPlayerNo;
		m_FrameEnd = fFreamEnd;
		m_pSprite = pSprite;
		m_pImageForegrd = pImage;
		vPosGain = vPos;
		vEffObj = pOtherObj;
		vEffSize = vSize;
		vEffSrcPos = vSrcPos;
		vEffSrcSize = vSrcSize;
		fEffAlpha = fAlpha;
		m_Frame = 0;
		fNum1 = Random(-6, 6);
		fNum1 = fNum1 / 10;
		dLetterEffectNo = dNo;
		bTrigger = FALSE;
		vVarNum1 = VECTOR2(0, 0);
		bTracTrigger = TRUE;
		dwPhase = 0;

		if (m_FrameEnd < 0)	bNonFream = TRUE;
		else
		{
			bNonFream = FALSE;
		}
		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	���ʎ����I�u�W�F�N�g�̊J�n	
//  �E���ʎ������w��ʒu���甭��������B
//  �E����������@�����W�Ŏw��ł���B�ȗ�����ƑS�����֔�������B
//
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		VECTOR3 vPos             �\���ʒu
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		DWORD fFreamEnd			 �\������
//		DWORD dNo				 �������ʂ̎��
//		float fAlpha;            �����x(�ȗ���)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//
//------------------------------------------------------------------------
BOOL CLetterEffectObj::Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo, DWORD dwPlayerNo, float fAlpha)
{
	if (m_bActive)
	{
		// ���łɕ\�����̂Ƃ�
		return FALSE;

	}
	else {
		// �J�n����
		m_bActive = TRUE;
		//������ϐ��ɑ��
		m_dwPlayerNo = dwPlayerNo;
		m_FrameEnd = fFreamEnd;
		m_pSprite = pSprite;
		m_pImageForegrd = pImage;
		vEffPos = vPos;
		vEffSize = vSize;
		vEffSrcPos = vSrcPos;
		vEffSrcSize = vSrcSize;
		fEffAlpha = fAlpha;
		m_Frame = 0;
		fNum1 = 0;
		dLetterEffectNo = dNo;
		bTrigger = FALSE;
		vVarNum1 = VECTOR2(0, 0);
		bTracTrigger = FALSE;
		bNonFream = FALSE;
		dwPhase = 0;

		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	���ʎ����I�u�W�F�N�g�̈ړ��E�X�V����	
//  �E���ʎ������X�V����
//
//	�߂�l �Ȃ�
//
//
//------------------------------------------------------------------------
void CLetterEffectObj::Update()
{
	DWORD dwPosUp = 0.5;
	DWORD dwFreamInterval = 3;

	if (m_bActive)
	{
		if (bTracTrigger == TRUE)
		{
			VECTOR3 vPos = GetPositionVector(vEffObj->GetWorld());
			vPos.y += dwPosUp;
			MATRIX4X4 mPos = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
			VECTOR3 vEyePt = m_pGMain->m_vEyePt;
			if(m_dwPlayerNo==SECONDPLAYER)	vEyePt = m_pGMain->m_vEyePtSecond;	
			MATRIX4X4 mImageWorld = TurnTarget(mPos, XMMatrixTranslation(vEyePt.x, vEyePt.y, vEyePt.z));
			mImageWorld = XMMatrixTranslation(vPosGain.x, vPosGain.y, vPosGain.z)* mImageWorld;
			vPos = GetPositionVector(mImageWorld);
			vEffPos = vPos;
		}
		switch (dLetterEffectNo)
		{
		case LENO_SHAKEBESIDETYPE:		//���ʎ������G��
			LetterShakeBesideType();

			break;

		case LENO_SHAKEVERTICALTYPE:	//���ʎ����c�G��
			LetterShakeVerticalType();

			break;


		case LENO_EXPANISIONTYPE:		//���ʎ����g��
			LetterExpansionType();
			break;

		case LENO_RIZETYPE:				//���ʎ����㏸
			LetterRizeType();
			break;

		case LENO_SHAKERANDOMTYPE:		//���ʎ��������_���h��
			LetterShakeRandomType();
			break;

		default:
			break;
		}
		// �����_�����O
		Render();
		// �t���[����i�߂�
		m_Frame++;

		if (bNonFream != TRUE)
		{

			if (m_Frame >= (m_FrameEnd / dwFreamInterval)) {
				float RemFream = m_FrameEnd - (m_FrameEnd / dwFreamInterval);

				fEffAlpha = fEffAlpha - (fEffAlpha / RemFream);
			}
			if (m_Frame >= m_FrameEnd) // �\�����ԏI����
			{
				m_bActive = FALSE;
			}
		}
		else if (vEffObj->GetActive() == FALSE)  m_bActive = FALSE;

	}
}

//------------------------------------------------------------------------
//
//	���ʎ����I�u�W�F�N�g����ʂɃ����_�����O	
//  �E���ʎ�����\������
//
//	�߂�l �Ȃ�
//
//
//------------------------------------------------------------------------
void CLetterEffectObj::Render()
{
	// �\����ԂłȂ��Ƃ�
	if (!m_bActive)  return;

	m_pGMain->m_pRenderBufProc->SetDraw3DSprite(m_pSprite, m_pImageForegrd, vEffPos, vEffSize, vEffSrcPos, vEffSrcSize, m_dwPlayerNo, fEffAlpha);	

	return;
}

//---------------------------------------------------------------------------
//
//		���ʎ������h��
//
//
//---------------------------------------------------------------------------
void CLetterEffectObj::LetterShakeBesideType()
{
	if (!m_bActive)  return;
	int MovePos = 0.03;
	MATRIX4X4	mWorld;
	//�G�t�F�N�g�̍��W���擾
	mWorld = XMMatrixTranslation(vEffPos.x, vEffPos.y, vEffPos.z);
	//�J�����̍��W���擾
	VECTOR3 vEyePt = m_pGMain->m_vEyePt;
	if (m_dwPlayerNo == SECONDPLAYER)	vEyePt = m_pGMain->m_vEyePtSecond;

	VECTOR3 vPos= vEffPos;
	if (bTrigger!=TRUE) {	//�E�Ɉړ�
		fNum1+= MovePos;
		if (fNum1 >= (MovePos*2)) {
			fNum1 = (MovePos * 2);
			bTrigger = TRUE;
		}
	}
	else {					//���Ɉړ�
		fNum1 -= MovePos;
		if (fNum1 <= (-MovePos * 2)) {
			fNum1 = (-MovePos * 2);
			bTrigger = FALSE;
		}
	}
	
	//��ɃJ����������
	mWorld = XMMatrixTranslation (fNum1, 0,0)*TurnTarget(mWorld, XMMatrixTranslation(vEyePt.x, vEyePt.y, vEyePt.z));
	//�ʒu����
	vEffPos = GetPositionVector(mWorld);
}

//---------------------------------------------------------------------------
//
//		���ʎ����c�h��
//
//
//---------------------------------------------------------------------------
void CLetterEffectObj::LetterShakeVerticalType()
{
	if (!m_bActive)  return;

	int			MovePos = 0.03;
	MATRIX4X4	mWorld;

	//�G�t�F�N�g�̍��W���擾
	mWorld = XMMatrixTranslation(vEffPos.x, vEffPos.y, vEffPos.z);
	//�J�����̍��W���擾
	VECTOR3 vEyePt = m_pGMain->m_vEyePt;
	if (m_dwPlayerNo == SECONDPLAYER)	vEyePt = m_pGMain->m_vEyePtSecond;	

	VECTOR3 vPos = vEffPos;
	if (bTrigger != TRUE) {		//��Ɉړ�
		fNum1 += MovePos;
		if (fNum1 >= (MovePos * 2)) {
			fNum1 = (MovePos * 2);
			bTrigger = TRUE;
		}
	}
	else {								//���Ɉړ�
		fNum1 -= MovePos;
		if (fNum1 <= (-MovePos * 2)) {
			fNum1 = (-MovePos * 2);
			bTrigger = FALSE;
		}
	}
	//��ɃJ����������
	mWorld = XMMatrixTranslation(0, fNum1, 0)*TurnTarget(mWorld, XMMatrixTranslation(vEyePt.x, vEyePt.y, vEyePt.z));
	//�ʒu����
	vEffPos = GetPositionVector(mWorld);
}



//---------------------------------------------------------------------------
//
//		���ʎ����g��
//
//
//---------------------------------------------------------------------------
void CLetterEffectObj::LetterExpansionType()
{
	if (!m_bActive)  return;

	//�������G�t�F�N�g���ł͂Ȃ���΃T�C�Y���擾
	if(bTrigger!=TRUE)vVarNum1 = vEffSize;

	VECTOR2 vSize(0, 0);
	VECTOR2 vMaxSize = vVarNum1;

	//�t���[���ɍ��킹�Ċg��ʂ����킹��
	float ExpNumX = (vMaxSize.x/ (m_FrameEnd*0.1));
	float ExpNumY = (vMaxSize.y / (m_FrameEnd*0.1));

	//�T�C�Y�g��
	vSize.x = ExpNumX * m_Frame;
	if(vSize.x>= vMaxSize.x)	vSize.x = vMaxSize.x;
	vSize.y = ExpNumY * m_Frame;
	if (vSize.y >= vMaxSize.y)	vSize.y = vMaxSize.y;
	//�T�C�Y����
	vEffSize = vSize;
	//�������G�t�F�N�g���ɂ���
	bTrigger = TRUE;
}

//---------------------------------------------------------------------------
//
//		���ʎ����㏸
//
//
//---------------------------------------------------------------------------
void CLetterEffectObj::LetterRizeType()
{
	if (!m_bActive)  return;

	//�㏸
	fNum1 += 0.0001;
	vEffPos.y += fNum1;

}

//---------------------------------------------------------------------------
//
//		���ʎ��������_���h��
//
//
//---------------------------------------------------------------------------
void CLetterEffectObj::LetterShakeRandomType()
{
	if (!m_bActive)  return;

	MATRIX4X4	mWorld;
	//�G�t�F�N�g�̍��W���擾
	mWorld = XMMatrixTranslation(vEffPos.x, vEffPos.y, vEffPos.z);
	//�J�����̍��W���擾
	VECTOR3 vEyePt = m_pGMain->m_vEyePt;
	if (m_dwPlayerNo == SECONDPLAYER)	vEyePt = m_pGMain->m_vEyePtSecond;

	VECTOR3		vPos = vEffPos;
	MATRIX4X4	mWorldRot = GetRotateMatrix(mWorld);
	MATRIX4X4	mWorldPos = GetPositionMatrix(mWorld);
	FLOAT		fMoveDist = 0.03;

	switch (dwPhase)
	{
	case 0:	//�ړ��p�x���擾

		fNum1 = Random(0, 360);
		if (fNum1 >= 180) fNum1 -= 360;
		if (fNum1 <= -180) fNum1 += 360;
		dwPhase++;
		break;

	case 1:	//�ړ�

		mWorld = mWorldPos;
		mWorld = XMMatrixTranslation(fMoveDist, 0, 0)*XMMatrixRotationZ(XMConvertToRadians(fNum1))*mWorld;
		if (m_Frame % 2 == 0)
		{
			dwPhase++;
		}
		break;

	case 2:	//���������t�Ɉړ�

		mWorld = mWorldPos;
		mWorld = XMMatrixTranslation(-fMoveDist, 0, 0)*XMMatrixRotationZ(XMConvertToRadians(fNum1))*mWorld;
		if (m_Frame % 2 == 0)
		{
			dwPhase--;
			fNum1 = Random(0, 360);
			if (fNum1 >= 180) fNum1 -= 360;
			if (fNum1 <= -180) fNum1 += 360;

		}


		break;

	}

	mWorld = TurnTarget(mWorld, XMMatrixTranslation(vEyePt.x, vEyePt.y, vEyePt.z));


	vEffPos = GetPositionVector(mWorld);
}


//------------------------------------------------------------------------
//
//	�G�l���M�[�f�B�X�N�v���V�[�W���N���X�̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnergyDiskProc::CEnergyDiskProc(CGameMain* pGMain) : CBaseProc(pGMain)
{

	m_pImageForegrd= new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Energy_Disk_2.png")); // �X�L�����I�𒆃C���[�W�̃��[�h	

	for (int i = 0; i < BILLENERGYDISK_MAX; i++)
	{
		// ��̃G�l���M�[�f�B�X�N�I�u�W�F�N�g���̃G�l���M�[�f�B�X�N�̐���ݒ肷��
		m_pObjArray.push_back(new CEnergyDiskObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}

};
//------------------------------------------------------------------------
//
//	�G�l���M�[�f�B�X�N�v���V�[�W���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CEnergyDiskProc::~CEnergyDiskProc()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_pImageForegrd);
};

//------------------------------------------------------------------------
//
//	�G�l���M�[�f�B�X�N�v���V�[�W���N���X�̊J�n	
//
//	�E�G�l���M�[�f�B�X�N�I�u�W�F�N�g�z��̒�����A�󂢂Ă���G�l���M�[�f�B�X�N��T���ĊJ�n����
//
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		VECTOR3 vPos			 �\���ʒu
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		DWORD fFreamEnd			 �\������
//		DWORD dNo				 �������ʂ̎��
//		float fAlpha;            �����x(�ȗ���)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CEnergyDiskProc::Start(CSprite* pSprite, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, float fAlpha)
{


	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CEnergyDiskObj*)m_pObjArray[i])->Start(pSprite,m_pImageForegrd, pOtherObj, vPos, vSize, vSrcPos, vSrcSize, fFreamEnd, fAlpha);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//
//	�G�l���M�[�f�B�X�N�v���V�[�W���N���X�̊J�n	
//
//	�E�G�l���M�[�f�B�X�N�I�u�W�F�N�g�z��̒�����A�󂢂Ă���G�l���M�[�f�B�X�N��T���ĊJ�n����
//
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		VECTOR3 vPos			 �\���ʒu
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		DWORD fFreamEnd			 �\������
//		DWORD dNo				 �������ʂ̎��
//		float fAlpha;            �����x(�ȗ���)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CEnergyDiskProc::Start(CSprite* pSprite, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, float fAlpha)
{


	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			((CEnergyDiskObj*)m_pObjArray[i])->Start(pSprite, m_pImageForegrd, pOtherObj, vPos, vSize, vSrcPos, vSrcSize, fFreamEnd, dwPlayerNo, fAlpha);
			return TRUE;
		}
	}
	return FALSE;
};

// ========================================================================================
//
//	�G�l���M�[�f�B�X�N�I�u�W�F�N�g�N���X
//�i�|�C���g�X�v���C�g�ŃG�l���M�[�f�B�X�N�������j
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	�G�l���M�[�f�B�X�N�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  int MaxParticle          �G�l���M�[�f�B�X�N�̐�
//
//------------------------------------------------------------------------
CEnergyDiskObj::CEnergyDiskObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_fAlpha = 0.0f;
	m_fSize = 0.0f;
	m_vEmitPos = VECTOR3(0, 0, 0);
	m_Frame = 0;
	m_FrameEnd = 0;

	Init();



}
//------------------------------------------------------------------------
//
//	�G�l���M�[�f�B�X�N�I�u�W�F�N�g�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CEnergyDiskObj::~CEnergyDiskObj()
{
}

//------------------------------------------------------------------------
//
//	�G�l���M�[�f�B�X�N�I�u�W�F�N�g�̏������֐�
//
//  �e��ݒ�l�̏�����
//
//  int MaxParticle        �G�l���M�[�f�B�X�N�̐�
//
//  �߂�l�@�@�@�Ȃ�
//------------------------------------------------------------------------
void CEnergyDiskObj::Init()
{
	m_bActive = FALSE;
	m_FrameEnd = 0;	// �G�l���M�[�f�B�X�N��\�����Ă��鎞��
	m_fAlpha = 1.0f;
	fNum1 = 0;
	bTrigger = FALSE;
	vVarNum1 = VECTOR2(0, 0);
	bTracTrigger = FALSE;
	bMaxSizeX = FALSE;
	bMaxSizeY = FALSE;
	nWrapFrame = 0;
}

//------------------------------------------------------------------------
//
//	�G�l���M�[�f�B�X�N�I�u�W�F�N�g�̊J�n	
//  �E�G�l���M�[�f�B�X�N���w��ʒu���甭��������B
//  �E����������@�����W�Ŏw��ł���B�ȗ�����ƑS�����֔�������B
//
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		CBaseObj* pOtherOb       �I�u�W�F�N�g
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		DWORD fFreamEnd			 �\������
//		DWORD dNo				 �������ʂ̎��
//		float fAlpha;            �����x(�ȗ���)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//
//------------------------------------------------------------------------
BOOL CEnergyDiskObj::Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd,  float fAlpha)
{
	if (m_bActive)
	{
		// ���łɕ\�����̂Ƃ�
		return FALSE;

	}
	else {
		// �J�n����
		m_bActive = TRUE;
		m_FrameEnd = fFreamEnd;
		m_pSprite = pSprite;
		m_pImageForegrd = pImage;
		vPosGain = vPos;
		vEffObj = pOtherObj;
		vEffSize = vSize;
		vEffSrcPos = vSrcPos;
		vEffSrcSize = vSrcSize;
		fEffAlpha = fAlpha;
		m_Frame = 0;
		fNum1 = Random(-6, 6);
		fNum1 = fNum1 / 10;
		bTrigger = FALSE;
		vVarNum1 = VECTOR2(0, 0);
		bMaxSizeX = FALSE;
		bMaxSizeY = FALSE;
		nWrapFrame = 0;

		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	�G�l���M�[�f�B�X�N�I�u�W�F�N�g�̊J�n	
//  �E�G�l���M�[�f�B�X�N���w��ʒu���甭��������B
//  �E����������@�����W�Ŏw��ł���B�ȗ�����ƑS�����֔�������B
//
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		CBaseObj* pOtherOb       �I�u�W�F�N�g
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		DWORD fFreamEnd			 �\������
//		DWORD dNo				 �������ʂ̎��
//		float fAlpha;            �����x(�ȗ���)
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//
//------------------------------------------------------------------------
BOOL CEnergyDiskObj::Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, float fAlpha)
{
	if (m_bActive)
	{
		// ���łɕ\�����̂Ƃ�
		return FALSE;

	}
	else {
		// �J�n����
		m_bActive = TRUE;
		m_FrameEnd = fFreamEnd;
		m_dwPlayerNo = dwPlayerNo;
		m_pSprite = pSprite;
		m_pImageForegrd = pImage;
		vPosGain = vPos;
		vEffObj = pOtherObj;
		vEffSize = vSize;
		vEffSrcPos = vSrcPos;
		vEffSrcSize = vSrcSize;
		fEffAlpha = fAlpha;
		m_Frame = 0;
		fNum1 = Random(-6, 6);
		fNum1 = fNum1 / 10;
		bTrigger = FALSE;
		vVarNum1 = VECTOR2(0, 0);
		bMaxSizeX = FALSE;
		bMaxSizeY = FALSE;
		nWrapFrame = 0;

		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	�G�l���M�[�f�B�X�N�I�u�W�F�N�g�̈ړ��E�X�V����	
//  �E�G�l���M�[�f�B�X�N���X�V����
//
//	�߂�l �Ȃ�
//
//
//------------------------------------------------------------------------
void CEnergyDiskObj::Update()
{
	if (m_bActive)
	{

		VECTOR2 vSize(0, 0);

		if (bTrigger != TRUE)vVarNum1 = vEffSize;
		VECTOR2 vMaxSize = vVarNum1;
		DWORD WrapFrameAdd = 120;

		//�t���[���ɍ��킹�Ċg��ʂ����킹��
		float ExpNumX = (vMaxSize.x / (m_FrameEnd*0.1));
		float ExpNumY = (vMaxSize.y / (m_FrameEnd*0.1));

		//�ő�ɂȂ�����T�C�Y���Œ肳����
		if (bMaxSizeX == TRUE && bMaxSizeY == TRUE) {
			if (nWrapFrame + WrapFrameAdd < m_Frame) {
				vSize.x = vMaxSize.x-( ExpNumX * (m_Frame - (nWrapFrame+ WrapFrameAdd)));
				vSize.y = vMaxSize.y-(ExpNumX * (m_Frame - (nWrapFrame+ WrapFrameAdd)));
				if (vSize.x <= 0)	vSize.x=0;
				if (vSize.y <= 0)	vSize.y=0;
			}
			else {
				vSize.x = vMaxSize.x;
				vSize.y = vMaxSize.y;

			}
		}
		else {	//�T�C�Y�g��

			vSize.x = ExpNumX * m_Frame;
			if (vSize.x >= vMaxSize.x) {
				vSize.x = vMaxSize.x;
				bMaxSizeX = TRUE;
				nWrapFrame = m_Frame;
			}
			vSize.y = ExpNumY * m_Frame;
			if (vSize.y >= vMaxSize.y) {
				vSize.y = vMaxSize.y;
				bMaxSizeY = TRUE;
				nWrapFrame = m_Frame;
			}

		}
		vEffSize = vSize;
		bTrigger = TRUE;
		// �����_�����O
		Render();
		m_Frame++;	// �t���[����i�߂�

		if (m_FrameEnd <= m_Frame)		m_bActive = FALSE;



	}
}

//------------------------------------------------------------------------
//
//	�G�l���M�[�f�B�X�N�I�u�W�F�N�g����ʂɃ����_�����O	
//  �E�G�l���M�[�f�B�X�N��\������
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CEnergyDiskObj::Render()
{
	// �\����ԂłȂ��Ƃ�
	if (!m_bActive)  return;
	VECTOR2 vSize = VECTOR2(400,400);
	m_pGMain->m_pRenderBufProc->SetDraw3DSprite(m_pSprite, m_pImageForegrd, vPosGain, vEffSize, VECTOR2(0, 0), vSize, m_dwPlayerNo);

	return;
}
