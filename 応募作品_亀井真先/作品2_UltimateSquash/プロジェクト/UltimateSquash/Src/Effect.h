//=============================================================================
//
//		�G�t�F�N�g�̏���
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
//	�p�[�e�B�N��
//�i�|�C���g�X�v���C�g�Ńp�[�e�B�N���������j
//
// ========================================================================================
//
// �p�[�e�B�N���\����
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
// ���_�̍\����
//
struct PARTICLE_VERTEX
{
	VECTOR3 Pos; //�ʒu
};
struct BILLBOARD_VERTEX
{
	VECTOR3 Pos; //�ʒu
	VECTOR2 UV; //�e�N�X�`���[���W
};

// -----------------------------------------------------------------------------
//	�p�[�e�B�N���̃I�u�W�F�N�g�N���X
//�i�|�C���g�X�v���C�g�Ńp�[�e�B�N���������j
//
// ----------------------------------------------------------------------------
class CParticleObj : public CBaseObj
{
protected:
	// 
	CDirect3D*	   m_pD3D;
	CShader*       m_pShader;
	FLOAT          m_fAlpha;
	float          m_fSize;  // �p�[�e�B�N���̃T�C�Y
	int            m_MaxParticle;
	VECTOR3        m_vEmitPos;
	PART*          m_pPartArray;
	int            m_Frame;
	int            m_FrameEnd;
	float          m_fSpeed;  // �p�[�e�B�N���̈ړ��X�s�[�h
	int            m_iBarthFrame;     // �p�[�e�B�N���̈ړ��J�n�܂ł̍ő�҂����ԁi�����_���j


	ID3D11Buffer*  m_pVertexBuffer;
	ID3D11ShaderResourceView* m_pTexture;//�e�N�X�`���[�i�p�[�e�B�N���v���V�[�W���̃e�N�X�`���A�h���X���Z�b�g���邾���j

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
//	�p�[�e�B�N���̃v���V�[�W���N���X
//
// ========================================================================================
class CParticleProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
public:
	BOOL Start(VECTOR3 vEmitPos, VECTOR3 vNormal = VECTOR3(0.0f, 0.0f, 0.0f));
	BOOL Start(VECTOR3 vEmitPos, DWORD dwPlayerNo, VECTOR3 vNormal = VECTOR3(0.0f, 0.0f, 0.0f));
	CParticleProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CParticleProc();	// �f�X�g���N�^
};


// ========================================================================================
//
//	�r���{�[�h
//
// ========================================================================================
// ------------------------------------------------------------------------
//	�r���{�[�h�̃I�u�W�F�N�g�N���X
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

	BOOL		   m_bHitTrigger;	//�����ɓ����������ǂ���	


	ID3D11Buffer*  m_pVertexBuffer;
	ID3D11ShaderResourceView* m_pTexture;//�e�N�X�`���[�i�r���{�[�h�v���V�[�W���̃e�N�X�`���A�h���X���Z�b�g���邾���j
	CFbxMesh*      m_pMesh;    //���b�V���i�r���{�[�h�v���V�[�W���̃��b�V���A�h���X���Z�b�g���邾���j

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
//	�r���{�[�h�̃v���V�[�W���N���X
//
// ========================================================================================
class CBillboardProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	DWORD m_dwImageWidth;
	DWORD m_dwImageHeight;
	CFbxMesh* m_pMesh;  // �����r���{�[�h�X�^�e�B�b�N���b�V�� 
public:
	virtual BOOL Start(VECTOR3 vPos);
	virtual HRESULT Load(TCHAR* szFName);

	virtual BOOL Start(VECTOR3 vPos,BOOL bTrigger);

	CBillboardProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CBillboardProc();	// �f�X�g���N�^
};

// ========================================================================================
//
//	�Ռ��g�r���{�[�h
//
// ========================================================================================
// ------------------------------------------------------------------------
//	�r���{�[�h�̃I�u�W�F�N�g�N���X
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
	ID3D11ShaderResourceView* m_pTexture;//�e�N�X�`���[�i�r���{�[�h�v���V�[�W���̃e�N�X�`���A�h���X���Z�b�g���邾���j
	CFbxMesh*      m_pMesh;    //���b�V���i�r���{�[�h�v���V�[�W���̃��b�V���A�h���X���Z�b�g���邾���j 

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
//	�Ռ��g�r���{�[�h�̃v���V�[�W���N���X
//
// ========================================================================================
class CBillShockWaveProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	DWORD m_dwImageWidth;
	DWORD m_dwImageHeight;
	CFbxMesh* m_pMesh;  // �����r���{�[�h�X�^�e�B�b�N���b�V��
public:
	BOOL Start(VECTOR3 vPos);
	BOOL Start(VECTOR3 vPos, DWORD dwPlayerNo);
	HRESULT Load(TCHAR* szFName);
	CBillShockWaveProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CBillShockWaveProc();	// �f�X�g���N�^
};
// -----------------------------------------------------------------------------
//	�p�[�e�B�N���̃I�u�W�F�N�g�N���X
//�i�|�C���g�X�v���C�g�ŃG�l���M�[�f�B�X�N�������j
//
// ----------------------------------------------------------------------------
class CLetterEffectObj : public CBaseObj
{
protected:
	// 
	FLOAT          m_fAlpha;
	float          m_fSize;  // �G�l���M�[�f�B�X�N�̃T�C�Y 
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
//	���ʎ����̃v���V�[�W���N���X
//
// ========================================================================================
class CLetterEffectProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
public:
	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo=0, float fAlpha=1.0f);
	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dNo = 0, float fAlpha = 1.0f);
	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, DWORD dNo = 0, float fAlpha = 1.0f);
	BOOL Start(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, DWORD dNo = 0, float fAlpha = 1.0f);

	CLetterEffectProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CLetterEffectProc();	// �f�X�g���N�^
};


// -----------------------------------------------------------------------------
//	�G�l���M�[�f�B�X�N�̃I�u�W�F�N�g�N���X
//�i�|�C���g�X�v���C�g�Ō��ʎ����������j
//
// ----------------------------------------------------------------------------
class CEnergyDiskObj : public CBaseObj
{
protected:
	// 
	FLOAT          m_fAlpha;
	float          m_fSize;  // ���ʎ����̃T�C�Y 
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
//	�G�l���M�[�f�B�X�N�̃v���V�[�W���N���X
//
// ========================================================================================
class CEnergyDiskProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	CSpriteImage*	 m_pImageForegrd;

public:
	BOOL Start(CSprite* pSprite, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, float fAlpha = 1.0f);
	BOOL Start(CSprite* pSprite, CBaseObj* pOtherObj, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD fFreamEnd, DWORD dwPlayerNo, float fAlpha = 1.0f);

	CEnergyDiskProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEnergyDiskProc();	// �f�X�g���N�^
};



// ========================================================================================
//
//	�G�t�F�N�g�S�̂̃��C���v���V�[�W���N���X
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
	CEffectProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEffectProc() { ; }
};

