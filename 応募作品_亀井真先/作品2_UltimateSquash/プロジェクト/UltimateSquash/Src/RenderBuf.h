//=============================================================================
//
//		�`��o�b�t�@�̏���
//
//		(�ۉe�E�g�c�q�Ή�)
//																RenderBuf.h
//=============================================================================
#pragma once
#include "GameMain.h"

class CGameMain;
class CSprite;
class CSpriteImage;
class CBaseProc;
// --------------------------------------------------------------------------------------------------
// 3D(�r���{�[�h)�t�H���g�`��o�b�t�@�\����
// 
//   �\���w��
//   3D�I�u�W�F�N�g�̒��ŗD�揇�ʂŃ\�[�g����ĕ\�������B
// 
// --------------------------------------------------------------------------------------------------
struct BILL_FONT_DATA
{
	VECTOR3  vPos;              // �\���ʒu
	VECTOR2  vSize;             // �\���T�C�Y
	TCHAR    szText[512];       // �\������e�L�X�g
	int      fontsize;          // �t�H���g�T�C�Y
	DWORD    colorABGR;         // �����F�@colorABGR�́AABGR�̎w��B��F���F��(0x00ffffff)
	float    fAlpha;            // �����x
	TCHAR    szFontName[256];   // �t�H���g��
};

// --------------------------------------------------------------------------------------------------
// 3D(�r���{�[�h)�X�v���C�g�`��o�b�t�@�\����
// 
//   �\���w��
//   3D�I�u�W�F�N�g�̒��ŗD�揇�ʂŃ\�[�g����ĕ\�������B
// 
// --------------------------------------------------------------------------------------------------
struct BILL_SPRITE_DATA
{
	CSprite*      pSprite;    // �X�v���C�g�I�u�W�F�N�g
	CSpriteImage* pImage;     // �X�v���C�g�C���[�W�I�u�W�F�N�g
	VECTOR3       vPos;       // �\���ʒu
	VECTOR2       vSize;      // �\���T�C�Y
	VECTOR2       vSrcPos;    // �p�^�[���ʒu
	VECTOR2       vSrcSize;   // �p�^�[���T�C�Y
	float         fAlpha;     // �����x
};


// --------------------------------------------------------------------------------------------------
// �`��o�b�t�@�\����
// 
// 
// --------------------------------------------------------------------------------------------------
struct RENDER_DATA
{
	DWORD			dwMeshKind;			// ���b�V�����
										//   (1:FbxStatic 2:FbxStaticDisplace 3:FbxSkin 4:FbxSkinDisplace 5:Wave 7:BBox 21:�p�[�e�B�N�� 22:�r���{�[�h 23:���r���{�[�h 24:�r���{�[�h���b�V�� 31:�Ή����� 51:�r���{�[�h�e�L�X�g 52:�r���{�[�h�X�v���C�g)
	DWORD			dwFlag;				// �t���O(1:�A���t�@�u�����h 2:���Z����  9:�y�o�b�t�@����)
	DWORD			dwPri;				// �`��̗D��x(�傫���قǐ�ɕ`��B�W���l��100)
										//   (9999:�� 1000:�}�b�v 100:�X�L���E�X�^�e�B�b�N���b�V�� 40:�g 30:���[�U�[�E�΂̋ʁE�p�[�e�B�N���� 25:���ؓ� 20:BBox )
	float			fEyeLen;			// �J��������̋���
	void*			pMesh;				// ���b�V���A�h���X
	void*			pObj;				// �I�u�W�F�N�g
	MATRIX4X4		mWorld;				// ���[���h�}�g���b�N�X

	std::vector<BILL_FONT_DATA> m_BillFontArray;		// �r���{�[�h�t�H���g�`��o�b�t�@�z��
	VECTOR3			vLight;				// �����x�N�g��
	DWORD			dwSC;				// �ۉe���i0:�ۉe����  1:�ۉe�j
	std::vector<BILL_SPRITE_DATA> m_BillSpriteArray;	// �r���{�[�h�X�v���C�g�`��o�b�t�@�z��

	// ���Z�q�I�[�o�[���[�h�Ŕ�r�֐����`
	// (�~���ɕ��ׂ�  �L�[1�FdwPri�@�L�[2�FfEyeLen )
	bool operator<(const RENDER_DATA& another) const {
		bool bRet = false;
		// �~���ɕ��ׂ�
		//   �L�[1�FdwPri�@�@�L�[2�FfEyeLen
		if (dwPri > another.dwPri ||
			(dwPri == another.dwPri  && fEyeLen > another.fEyeLen))
		{
			bRet = true;
		}
		return bRet;
	}
};

// --------------------------------------------------------------------------------------------------
// �X�v���C�g�Ɓ��t�H���g�̕`��o�b�t�@�\����
// 
//   �\���w��
//   (3D�I�u�W�F�N�g�E�r���{�[�h����O�ɕ\�������B�\�����́A�Z�b�g���ꂽ��)
// 
// --------------------------------------------------------------------------------------------------
struct DRAW_SPRITE_FONT_DATA
{
	DWORD dwKind;            // ���(1:�X�v���C�g 2:�t�H���g 3:���� 4:4�p�`)
	CSprite* pSprite;        // �X�v���C�g�I�u�W�F�N�g
	CSpriteImage* pImage;    // �X�v���C�g�C���[�W�I�u�W�F�N�g
	float posX;              // �\���ʒu�@����@�w���W
	float posY;              // �\���ʒu�@����@�x���W
	DWORD srcX;              // �p�^�[���ʒu�@�w���W
	DWORD srcY;              // �p�^�[���ʒu�@�x���W
	DWORD srcwidth;          // �p�^�[���T�C�Y�@��
	DWORD srcheight;         // �p�^�[���T�C�Y�@����
	DWORD destwidth;         // �\���T�C�Y�@��
	DWORD destheight;        // �\���T�C�Y�@����
	TCHAR  szText[512];      // �\������e�L�X�g
	int   fontsize;          // �t�H���g�T�C�Y
	DWORD colorABGR;         // �����F�@colorABGR�́AABGR�̎w��B��F���F��(0x00ffffff)
	float fAlpha;            // �����x
	TCHAR  szFontName[256];  // �t�H���g��

};

// --------------------------------------------------------------------------------------------------
//
// �`��o�b�t�@�N���X
//
// --------------------------------------------------------------------------------------------------
class  CRenderBufProc
{
protected:
	CGameMain*		m_pGMain;						// �Q�[�����C���N���X

	std::vector<RENDER_DATA>    m_RenderArray;		// �`��o�b�t�@�z��
	std::vector<DRAW_SPRITE_FONT_DATA> m_DrawSpriteFontArray;	// �X�v���C�g���t�H���g�`��o�b�t�@�z��

	std::vector<RENDER_DATA>    m_RenderArraySecond;		// �`��o�b�t�@�z��
	std::vector<DRAW_SPRITE_FONT_DATA> m_DrawSpriteFontArraySecond;	// �X�v���C�g���t�H���g�`��o�b�t�@�z��

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

