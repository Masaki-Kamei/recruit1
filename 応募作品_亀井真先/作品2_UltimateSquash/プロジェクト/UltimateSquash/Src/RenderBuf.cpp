//=============================================================================
//
//		�`��o�b�t�@�̏���
//
//		(�ۉe�E�g�c�q�Ή�)
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
//	�`��o�b�t�@�N���X�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CRenderBufProc::CRenderBufProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;

}

//------------------------------------------------------------------------
//
//	�`��o�b�t�@�N���X�̃f�X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CRenderBufProc::~CRenderBufProc()
{
	;
}
//------------------------------------------------------------------------
//
//	�`��o�b�t�@�z��̃N�����[	
//
//  �����@�Ȃ�
//
//
//------------------------------------------------------------------------
void CRenderBufProc::Clear()
{
	for (DWORD i = 0; i < m_RenderArray.size(); i++)
	{
		if (m_RenderArray[i].m_BillFontArray.size() > 0)
		{
			m_RenderArray[i].m_BillFontArray.clear();			// �z��폜
			m_RenderArray[i].m_BillFontArray.shrink_to_fit();	// �s�v���������
		}
		if (m_RenderArray[i].m_BillSpriteArray.size() > 0)
		{
			m_RenderArray[i].m_BillSpriteArray.clear();			// �z��폜
			m_RenderArray[i].m_BillSpriteArray.shrink_to_fit();	// �s�v���������
		}
	}
	m_RenderArray.clear();					// �z��폜
	m_RenderArray.shrink_to_fit();			// �s�v���������
	m_DrawSpriteFontArray.clear();			// �z��폜
	m_DrawSpriteFontArray.shrink_to_fit();	// �s�v���������

	for (DWORD i = 0; i < m_RenderArraySecond.size(); i++)
	{
		if (m_RenderArraySecond[i].m_BillFontArray.size() > 0)
		{
			m_RenderArraySecond[i].m_BillFontArray.clear();			// �z��폜
			m_RenderArraySecond[i].m_BillFontArray.shrink_to_fit();	// �s�v���������
		}
		if (m_RenderArraySecond[i].m_BillSpriteArray.size() > 0)
		{
			m_RenderArraySecond[i].m_BillSpriteArray.clear();			// �z��폜
			m_RenderArraySecond[i].m_BillSpriteArray.shrink_to_fit();	// �s�v���������
		}
	}
	m_RenderArraySecond.clear();					// �z��폜
	m_RenderArraySecond.shrink_to_fit();			// �s�v���������
	m_DrawSpriteFontArraySecond.clear();			// �z��폜
	m_DrawSpriteFontArraySecond.shrink_to_fit();	// �s�v���������
	
}


//------------------------------------------------------------------------
//
//	�`��o�b�t�@�N���X�̃Z�b�g	
//
//  �����@
//  DWORD			dwMeshKind;			// ���b�V�����
//										 (1:FbxStatic 2:FbxStaticDisplace 3:FbxSkin 5:Wave 7:BBox 21:�p�[�e�B�N�� 22:�r���{�[�h 23:���r���{�[�h)
//  DWORD			dwFlag;				// �t���O(1:�A���t�@�u�����h 2:���Z���� 9:�y�o�b�t�@����)
//  DWORD			dwPri;				// �`��̗D��x(�傫���قǐ�ɕ`��B�W���l��100)
										//   (9999:�� 1000:�}�b�v 100:�X�L���E�X�^�e�B�b�N���b�V�� 40:�g 30:���[�U�[�E�΂̋ʁE�p�[�e�B�N����  25:���ؓ� 20:BBox )
//  void*			pMesh;				// ���b�V���A�h���X
//  void*			pObj;				// �x�[�X�I�u�W�F�N�g
//  MATRIX4X4		mWorld;				// ���[���h�}�g���b�N�X
//  VECTOR3			vLight;				// �����x�N�g��
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

	m_RenderArray.push_back(rd);	// m_pRenderjArray�ɃI�u�W�F�N�g��o�^����

}

//------------------------------------------------------------------------
//
//	�`��o�b�t�@�N���X�̃r���{�[�h�t�H���g�̃Z�b�g	
// 
//   ��ʂɕ\������r���{�[�h�e�L�X�g�̕\���w��
// 
//  �����@
//		VECTOR3   vPos              �\���ʒu
//		TCHAR*    szText            �\������e�L�X�g
//		VECTOR2   vSize             �\���T�C�Y
//		DWORD     colorABGR;         // �����F�@colorABGR�́AABGR�̎w��B��F���F��(0x00ffffff)
//		float     fAlpha;            // �����x(�ȗ���)
//		TCHAR     szFontName[256];   // �t�H���g��(�ȗ���)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDraw3DFont(VECTOR3 vPos, TCHAR* szText, VECTOR2 vSize, DWORD colorABGR, float fAlpha, TCHAR szFontName[])
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);

	RENDER_DATA rd;
	rd.dwMeshKind = 51;    // ���b�V�����   51:�r���{�[�h�e�L�X�g
	rd.dwFlag = 1;         // �t���O(1:�A���t�@�u�����h)
	rd.dwPri = 25;         // �`��̗D��x(25)
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

	rd.m_BillFontArray.push_back(bf);	// rd��m_pBillFontArray�Ƀf�[�^��o�^����

	m_RenderArray.push_back(rd);	// m_pRenderjArray�ɃI�u�W�F�N�g��o�^����

}


//------------------------------------------------------------------------
//
//	�`��o�b�t�@�N���X��3D(�r���{�[�h)�X�v���C�g�̃Z�b�g	
// 
//   ��ʂɕ\������r���{�[�h�X�v���C�g�̕\���w��
// 
//  �����@
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		VECTOR3 vPos             �\���ʒu
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		float fAlpha;            �����x(�ȗ���)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDraw3DSprite(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, float fAlpha)
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation( vPos.x, vPos.y, vPos.z);

	RENDER_DATA rd;
	rd.dwMeshKind = 52;    // ���b�V�����   52:�r���{�[�h�X�v���C�g
	rd.dwFlag = 1;         // �t���O(1:�A���t�@�u�����h)
	rd.dwPri = 25;         // �`��̗D��x(25)
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

	rd.m_BillSpriteArray.push_back(bs);	// rd��m_pBillFontArray�Ƀf�[�^��o�^����

	m_RenderArray.push_back(rd);	// m_pRenderjArray�ɃI�u�W�F�N�g��o�^����

}

//------------------------------------------------------------------------
//
//	�`��o�b�t�@�N���X��3D(�r���{�[�h)�X�v���C�g�̃Z�b�g	
// 
//   ��ʂɕ\������r���{�[�h�X�v���C�g�̕\���w��
// 
//  �����@
//		CSprite* pSprite         �X�v���C�g
//		VECTOR3 vPos             �\���ʒu
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDraw3DSprite(CSprite* pSprite, VECTOR3 vPos)
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation( vPos.x, vPos.y, vPos.z);

	RENDER_DATA rd;
	rd.dwMeshKind = 52;    // ���b�V�����   52:�r���{�[�h�X�v���C�g
	rd.dwFlag = 1;         // �t���O(1:�A���t�@�u�����h)
	rd.dwPri = 25;         // �`��̗D��x(25)
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

	rd.m_BillSpriteArray.push_back(bs);	// rd��m_pBillFontArray�Ƀf�[�^��o�^����

	m_RenderArray.push_back(rd);	// m_pRenderjArray�ɃI�u�W�F�N�g��o�^����

}

//------------------------------------------------------------------------
//
//	�`��X�v���C�g�o�b�t�@�N���X�̃Z�b�g	
// 
//   ��ʂɕ\������X�v���C�g�̕\���w��
//   (3D�I�u�W�F�N�g����O�ɕ\�������B�\�����́A�Z�b�g���ꂽ��)
// 
//  �����@
//		CSprite* pSprite         �X�v���C�g
//  	CSpriteImage* pImage;    // �X�v���C�g�C���[�W
//  	float posX;              // �\���ʒu�@����@�w���W
//  	float posY;              // �\���ʒu�@����@�x���W
//  	DWORD srcX;              // �p�^�[���ʒu�@�w���W
//  	DWORD srcY;              // �p�^�[���ʒu�@�x���W
//  	DWORD srcwidth;          // �p�^�[���T�C�Y�@��
//  	DWORD srcheight;         // �p�^�[���T�C�Y�@����
//  	DWORD destwidth;         // �\���T�C�Y�@��
//  	DWORD destheight;        // �\���T�C�Y�@����
//		float fAlpha;            // �����x(�ȗ��l1.0f)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDrawSprite(CSprite* pSprite, CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight, float fAlpha)
{
	DRAW_SPRITE_FONT_DATA dsf;

	dsf.dwKind = 1;         // 1:�X�v���C�g�`��
	dsf.pSprite = pSprite;
	dsf.pImage = pImage;    // �X�v���C�g�C���[�W
	dsf.posX = posX;
	dsf.posY = posY;
	dsf.srcX = srcX;
	dsf.srcY = srcY;
	dsf.srcwidth = srcwidth;
	dsf.srcheight = srcheight;
	dsf.destwidth = destwidth;
	dsf.destheight = destheight;
	dsf.fAlpha = fAlpha;

	m_DrawSpriteFontArray.push_back(dsf);	// m_pDrawSpriteFontArray�Ƀf�[�^��o�^����
}

//------------------------------------------------------------------------
//
//	�`��X�v���C�g�o�b�t�@�N���X�̃Z�b�g	
// 
//   ��ʂɕ\������X�v���C�g�̕\���w��
//   (3D�I�u�W�F�N�g����O�ɕ\�������B�\�����́A�Z�b�g���ꂽ��)
// 
//  �����@
//		CSprite* pSprite         �X�v���C�g
//  	CSpriteImage* pImage;    // �X�v���C�g�C���[�W
//  	float posX;              // �\���ʒu�@����@�w���W
//  	float posY;              // �\���ʒu�@����@�x���W
//  	DWORD srcX;              // �p�^�[���ʒu�@�w���W
//  	DWORD srcY;              // �p�^�[���ʒu�@�x���W
//  	DWORD srcwidth;          // �p�^�[���T�C�Y�@��
//  	DWORD srcheight;         // �p�^�[���T�C�Y�@����
//		float fAlpha;            // �����x(�ȗ��l1.0f)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDrawSprite(CSprite* pSprite, CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, float fAlpha)
{
	DRAW_SPRITE_FONT_DATA dsf;

	dsf.dwKind = 1;         // 1:�X�v���C�g�`��
	dsf.pSprite = pSprite;
	dsf.pImage = pImage;    // �X�v���C�g�C���[�W
	dsf.posX = posX;
	dsf.posY = posY;
	dsf.srcX = srcX;
	dsf.srcY = srcY;
	dsf.srcwidth = srcwidth;
	dsf.srcheight = srcheight;
	dsf.destwidth = srcwidth;
	dsf.destheight = srcheight;
	dsf.fAlpha = fAlpha;

	m_DrawSpriteFontArray.push_back(dsf);	// m_pDrawSpriteFontArray�Ƀf�[�^��o�^����
}

//------------------------------------------------------------------------
//	�`��o�b�t�@�N���X�̃Z�b�g	
//
//  �����@
//  DWORD			dwMeshKind;			// ���b�V�����
//										 (1:FbxStatic 2:FbxStaticDisplace 3:FbxSkin 5:Wave 7:BBox 21:�p�[�e�B�N�� 22:�r���{�[�h 23:���r���{�[�h)
//  DWORD			dwFlag;				// �t���O(1:�A���t�@�u�����h 2:���Z���� 9:�y�o�b�t�@����)
//  DWORD			dwPri;				// �`��̗D��x(�傫���قǐ�ɕ`��B�W���l��100)
										//   (9999:�� 1000:�}�b�v 100:�X�L���E�X�^�e�B�b�N���b�V�� 40:�g 30:���[�U�[�E�΂̋ʁE�p�[�e�B�N����  25:���ؓ� 20:BBox )
//  void*			pMesh;				// ���b�V���A�h���X
//  void*			pObj;				// �x�[�X�I�u�W�F�N�g
//  MATRIX4X4		mWorld;				// ���[���h�}�g���b�N�X
//  VECTOR3			vLight;				// �����x�N�g��
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

	if(dwPlayerNo==SECONDPLAYER)m_RenderArraySecond.push_back(rd);	// m_pRenderjArray�ɃI�u�W�F�N�g��o�^����
	else m_RenderArray.push_back(rd);
}

//------------------------------------------------------------------------
//	�`��o�b�t�@�N���X�̃r���{�[�h�t�H���g�̃Z�b�g	
// 
//   ��ʂɕ\������r���{�[�h�e�L�X�g�̕\���w��
// 
//  �����@
//		VECTOR3   vPos              �\���ʒu
//		TCHAR*    szText            �\������e�L�X�g
//		VECTOR2   vSize             �\���T�C�Y
//		DWORD     colorABGR;         // �����F�@colorABGR�́AABGR�̎w��B��F���F��(0x00ffffff)
//		float     fAlpha;            // �����x(�ȗ���)
//		TCHAR     szFontName[256];   // �t�H���g��(�ȗ���)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDraw3DFont(VECTOR3 vPos, TCHAR* szText, VECTOR2 vSize, DWORD colorABGR, DWORD dwPlayerNo, float fAlpha, TCHAR szFontName[])
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);

	RENDER_DATA rd;
	rd.dwMeshKind = 51;    // ���b�V�����   51:�r���{�[�h�e�L�X�g
	rd.dwFlag = 1;         // �t���O(1:�A���t�@�u�����h)
	rd.dwPri = 25;         // �`��̗D��x(25)
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

	rd.m_BillFontArray.push_back(bf);	// rd��m_pBillFontArray�Ƀf�[�^��o�^����

	if (dwPlayerNo == SECONDPLAYER)m_RenderArraySecond.push_back(rd);	// m_pRenderjArray�ɃI�u�W�F�N�g��o�^����
	else m_RenderArray.push_back(rd);

}


//------------------------------------------------------------------------
//	�`��o�b�t�@�N���X��3D(�r���{�[�h)�X�v���C�g�̃Z�b�g	
// 
//   ��ʂɕ\������r���{�[�h�X�v���C�g�̕\���w��
// 
//  �����@
//		CSprite* pSprite         �X�v���C�g
//		CSpriteImage* pImage     �X�v���C�g�C���[�W
//		VECTOR3 vPos             �\���ʒu
//		VECTOR2 vSize            �\���T�C�Y
//		VECTOR2 vSrcPos          �p�^�[���ʒu
//		VECTOR2 vSrcSize         �p�^�[���T�C�Y
//		float fAlpha;            �����x(�ȗ���)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDraw3DSprite(CSprite* pSprite, CSpriteImage* pImage, VECTOR3 vPos, VECTOR2 vSize, VECTOR2 vSrcPos, VECTOR2 vSrcSize, DWORD dwPlayerNo, float fAlpha)
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);

	RENDER_DATA rd;
	rd.dwMeshKind = 52;    // ���b�V�����   52:�r���{�[�h�X�v���C�g
	rd.dwFlag = 1;         // �t���O(1:�A���t�@�u�����h)
	rd.dwPri = 25;         // �`��̗D��x(25)
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

	rd.m_BillSpriteArray.push_back(bs);	// rd��m_pBillFontArray�Ƀf�[�^��o�^����

	if (dwPlayerNo == SECONDPLAYER)m_RenderArraySecond.push_back(rd);	// m_pRenderjArray�ɃI�u�W�F�N�g��o�^����
	else m_RenderArray.push_back(rd);

}

//------------------------------------------------------------------------
//	�`��o�b�t�@�N���X��3D(�r���{�[�h)�X�v���C�g�̃Z�b�g	
// 
//   ��ʂɕ\������r���{�[�h�X�v���C�g�̕\���w��
// 
//  �����@
//		CSprite* pSprite         �X�v���C�g
//		VECTOR3 vPos             �\���ʒu
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDraw3DSprite(CSprite* pSprite, VECTOR3 vPos, DWORD dwPlayerNo)
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);

	RENDER_DATA rd;
	rd.dwMeshKind = 52;    // ���b�V�����   52:�r���{�[�h�X�v���C�g
	rd.dwFlag = 1;         // �t���O(1:�A���t�@�u�����h)
	rd.dwPri = 25;         // �`��̗D��x(25)
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

	rd.m_BillSpriteArray.push_back(bs);	// rd��m_pBillFontArray�Ƀf�[�^��o�^����

	if (dwPlayerNo == SECONDPLAYER)m_RenderArraySecond.push_back(rd);	// m_pRenderjArray�ɃI�u�W�F�N�g��o�^����
	else m_RenderArray.push_back(rd);

}

//------------------------------------------------------------------------
//	�`��X�v���C�g�o�b�t�@�N���X�̃Z�b�g	
// 
//   ��ʂɕ\������X�v���C�g�̕\���w��
//   (3D�I�u�W�F�N�g����O�ɕ\�������B�\�����́A�Z�b�g���ꂽ��)
// 
//  �����@
//		CSprite* pSprite         �X�v���C�g
//  	CSpriteImage* pImage;    // �X�v���C�g�C���[�W
//  	float posX;              // �\���ʒu�@����@�w���W
//  	float posY;              // �\���ʒu�@����@�x���W
//  	DWORD srcX;              // �p�^�[���ʒu�@�w���W
//  	DWORD srcY;              // �p�^�[���ʒu�@�x���W
//  	DWORD srcwidth;          // �p�^�[���T�C�Y�@��
//  	DWORD srcheight;         // �p�^�[���T�C�Y�@����
//  	DWORD destwidth;         // �\���T�C�Y�@��
//  	DWORD destheight;        // �\���T�C�Y�@����
//		float fAlpha;            // �����x(�ȗ��l1.0f)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDrawSprite(CSprite* pSprite, CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight, DWORD dwPlayerNo, float fAlpha)
{
	DRAW_SPRITE_FONT_DATA dsf;

	dsf.dwKind = 1;         // 1:�X�v���C�g�`��
	dsf.pSprite = pSprite;
	dsf.pImage = pImage;    // �X�v���C�g�C���[�W
	dsf.posX = posX;
	dsf.posY = posY;
	dsf.srcX = srcX;
	dsf.srcY = srcY;
	dsf.srcwidth = srcwidth;
	dsf.srcheight = srcheight;
	dsf.destwidth = destwidth;
	dsf.destheight = destheight;
	dsf.fAlpha = fAlpha;

	if (dwPlayerNo == SECONDPLAYER)m_DrawSpriteFontArraySecond.push_back(dsf);	// m_pDrawSpriteFontArray�Ƀf�[�^��o�^����
	else m_DrawSpriteFontArray.push_back(dsf);
}

//------------------------------------------------------------------------
//	�`��X�v���C�g�o�b�t�@�N���X�̃Z�b�g	
// 
//   ��ʂɕ\������X�v���C�g�̕\���w��
//   (3D�I�u�W�F�N�g����O�ɕ\�������B�\�����́A�Z�b�g���ꂽ��)
// 
//  �����@
//		CSprite* pSprite         �X�v���C�g
//  	CSpriteImage* pImage;    // �X�v���C�g�C���[�W
//  	float posX;              // �\���ʒu�@����@�w���W
//  	float posY;              // �\���ʒu�@����@�x���W
//  	DWORD srcX;              // �p�^�[���ʒu�@�w���W
//  	DWORD srcY;              // �p�^�[���ʒu�@�x���W
//  	DWORD srcwidth;          // �p�^�[���T�C�Y�@��
//  	DWORD srcheight;         // �p�^�[���T�C�Y�@����
//		float fAlpha;            // �����x(�ȗ��l1.0f)
//
//------------------------------------------------------------------------
void CRenderBufProc::SetDrawSprite(CSprite* pSprite, CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD dwPlayerNo, float fAlpha)
{
	DRAW_SPRITE_FONT_DATA dsf;

	dsf.dwKind = 1;         // 1:�X�v���C�g�`��
	dsf.pSprite = pSprite;
	dsf.pImage = pImage;    // �X�v���C�g�C���[�W
	dsf.posX = posX;
	dsf.posY = posY;
	dsf.srcX = srcX;
	dsf.srcY = srcY;
	dsf.srcwidth = srcwidth;
	dsf.srcheight = srcheight;
	dsf.destwidth = srcwidth;
	dsf.destheight = srcheight;
	dsf.fAlpha = fAlpha;

	if (dwPlayerNo == SECONDPLAYER)m_DrawSpriteFontArraySecond.push_back(dsf);	// m_pDrawSpriteFontArray�Ƀf�[�^��o�^����
	else m_DrawSpriteFontArray.push_back(dsf);
}


//------------------------------------------------------------------------
//
//	�`��o�b�t�@�N���X�̕`��	
//
//  �����@�Ȃ�
//
//
//------------------------------------------------------------------------
void CRenderBufProc::Render()
{
	float ClearColor[4] = { 0,0,0,1 };// �N���A�F�쐬�@RGBA�̏�

	//m_pGMain->m_pD3D->ClearRenderTarget(ClearColor);    // �ʏ�̉�ʃN�����[


	// ���_����̋����̐ݒ�
	for (DWORD i = 0; i < m_RenderArray.size(); i++)
	{
		m_RenderArray[i].fEyeLen = magnitude(m_pGMain->m_vEyePt - GetPositionVector(m_RenderArray[i].mWorld));
	}

	// -----------------------------------------------------------------------------------------------------------
	// vector��sort���g���āA�`�揇�ɕ��בւ�
	std::sort(m_RenderArray.begin(), m_RenderArray.end());    // ��r�֐��i���Z�q�I�[�o�[���[�h�j���g�p���ă\�[�g

	

	// ------------------------------------------------------------------------------------------------------------
	//	�����_�����O
	for (DWORD i = 0; i < m_RenderArray.size(); i++)
	{
		// �u�����h�X�e�[�g�E�y�o�b�t�@�̐ݒ�  ------------------------------------------------------
		if (m_RenderArray[i].dwFlag == 1)
		{
			// �����F�̃u�����f�B���O��ݒ�
			UINT mask = 0xffffffff;
			m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateTrapen, NULL, mask);
		}
		else if (m_RenderArray[i].dwFlag == 2)
		{
			// ���Z�����̃u�����f�B���O��ݒ�
			UINT mask = 0xffffffff;
			m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateAdd, NULL, mask);
		}
		else if (m_RenderArray[i].dwFlag == 9)
		{
			// Z�o�b�t�@�𖳌���
			m_pGMain->m_pD3D->SetZBuffer(FALSE); // Z�o�b�t�@�𖳌���
		}

		if (m_RenderArray[i].dwMeshKind == 24)			//	 �r���{�[�h���b�V�� 
		{
			((CBillShockWaveObj*)m_RenderArray[i].pObj)->RenderMesh();
		}
		else if (m_RenderArray[i].dwMeshKind == 51)			//	 �r���{�[�h�t�H���g
		{
			m_pGMain->m_pFont->Draw3D(m_RenderArray[i].m_BillFontArray[0].vPos, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vEyePt,
								m_RenderArray[i].m_BillFontArray[0].szText,
								m_RenderArray[i].m_BillFontArray[0].vSize, m_RenderArray[i].m_BillFontArray[0].colorABGR,
								m_RenderArray[i].m_BillFontArray[0].fAlpha, m_RenderArray[i].m_BillFontArray[0].szFontName);
		}
		else if (m_RenderArray[i].dwMeshKind == 52)			//	 �r���{�[�h�X�v���C�g
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
		// �u�����h�X�e�[�g�E�y�o�b�t�@�̃��Z�b�g-----------------------------------------------------
		if (m_RenderArray[i].dwFlag == 1 || m_RenderArray[i].dwFlag == 2)
		{
			// �ʏ�̃u�����f�B���O�ɖ߂�
			UINT mask = 0xffffffff;
			m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateTrapen, NULL, mask);
		}
		else if (m_RenderArray[i].dwFlag == 9)
		{
			// Z�o�b�t�@��L����
			m_pGMain->m_pD3D->SetZBuffer(TRUE); // Z�o�b�t�@��L����

		}


	}

	// ---------------------------------------------------------------------------------------------------------------------
//	�`��X�v���C�g���t�H���g�o�b�t�@����X�v���C�g�ƃe�L�X�g�̕`��
//   (3D�I�u�W�F�N�g����O�ɕ\�������B)
	for (DWORD i = 0; i < m_DrawSpriteFontArray.size(); i++)
	{
		if (m_DrawSpriteFontArray[i].dwKind == 1)  // �X�v���C�g�`��
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
//	�`��o�b�t�@�N���X�̕`��	
//
//  �����@�Ȃ�
//
//
//------------------------------------------------------------------------
void CRenderBufProc::RenderSecond()
{
	float ClearColor[4] = { 0,0,0,1 };// �N���A�F�쐬�@RGBA�̏�

	//m_pGMain->m_pD3D->ClearRenderTarget(ClearColor);    // �ʏ�̉�ʃN�����[


	// ���_����̋����̐ݒ�
	for (DWORD i = 0; i < m_RenderArraySecond.size(); i++)
	{
		m_RenderArraySecond[i].fEyeLen = magnitude(m_pGMain->m_vEyePtSecond - GetPositionVector(m_RenderArraySecond[i].mWorld));
	}

	// -----------------------------------------------------------------------------------------------------------
	// vector��sort���g���āA�`�揇�ɕ��בւ�
	std::sort(m_RenderArraySecond.begin(), m_RenderArraySecond.end());    // ��r�֐��i���Z�q�I�[�o�[���[�h�j���g�p���ă\�[�g



	// ------------------------------------------------------------------------------------------------------------
	//	�����_�����O
	for (DWORD i = 0; i < m_RenderArraySecond.size(); i++)
	{
		// �u�����h�X�e�[�g�E�y�o�b�t�@�̐ݒ�  ------------------------------------------------------
		if (m_RenderArraySecond[i].dwFlag == 1)
		{
			// �����F�̃u�����f�B���O��ݒ�
			UINT mask = 0xffffffff;
			m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateTrapen, NULL, mask);
		}
		else if (m_RenderArraySecond[i].dwFlag == 2)
		{
			// ���Z�����̃u�����f�B���O��ݒ�
			UINT mask = 0xffffffff;
			m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateAdd, NULL, mask);
		}
		else if (m_RenderArraySecond[i].dwFlag == 9)
		{
			// Z�o�b�t�@�𖳌���
			m_pGMain->m_pD3D->SetZBuffer(FALSE); // Z�o�b�t�@�𖳌���
		}

		if (m_RenderArraySecond[i].dwMeshKind == 24)			//	 �r���{�[�h���b�V�� 
		{
			((CBillShockWaveObj*)m_RenderArraySecond[i].pObj)->RenderMesh();
		}
		else if (m_RenderArraySecond[i].dwMeshKind == 51)			//	 �r���{�[�h�t�H���g
		{
			m_pGMain->m_pFont->Draw3D(m_RenderArraySecond[i].m_BillFontArray[0].vPos, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vEyePtSecond,
				m_RenderArraySecond[i].m_BillFontArray[0].szText,
				m_RenderArraySecond[i].m_BillFontArray[0].vSize, m_RenderArraySecond[i].m_BillFontArray[0].colorABGR,
				m_RenderArraySecond[i].m_BillFontArray[0].fAlpha, m_RenderArraySecond[i].m_BillFontArray[0].szFontName);
		}
		else if (m_RenderArraySecond[i].dwMeshKind == 52)			//	 �r���{�[�h�X�v���C�g
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
		// �u�����h�X�e�[�g�E�y�o�b�t�@�̃��Z�b�g------------------------------------------------------
		if (m_RenderArraySecond[i].dwFlag == 1 || m_RenderArraySecond[i].dwFlag == 2)
		{
			// �ʏ�̃u�����f�B���O�ɖ߂�
			UINT mask = 0xffffffff;
			m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateTrapen, NULL, mask);
		}
		else if (m_RenderArraySecond[i].dwFlag == 9)
		{
			// Z�o�b�t�@��L����
			m_pGMain->m_pD3D->SetZBuffer(TRUE); // Z�o�b�t�@��L����

		}


	}

	// ---------------------------------------------------------------------------------------------------------------------
//	�`��X�v���C�g���t�H���g�o�b�t�@����X�v���C�g�ƃe�L�X�g�̕`��
//   (3D�I�u�W�F�N�g����O�ɕ\�������B)
	for (DWORD i = 0; i < m_DrawSpriteFontArraySecond.size(); i++)
	{
		if (m_DrawSpriteFontArraySecond[i].dwKind == 1)  // �X�v���C�g�`��
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

