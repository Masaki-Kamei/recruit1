//=============================================================================
//
//		�O�i�E��i����
//																BackFore.h
//=============================================================================

#pragma once

//�x����\��
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)


//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite.h"


//======================================================================
// �o�b�N�N���E���h�@�v���V�[�W���N���X
//
// (����)��{�v���V�[�W���N���X�͌p�����Ă��Ȃ�
//
//======================================================================
class CBackProc
{
protected:
	CGameMain*		m_pGMain;
	CSpriteImage*	m_pImageBk;
	CSprite*		m_pBackgrd;
	VECTOR2			m_vScroll;

public:
	//void Update();

	//CBackProc(CGameMain* pGMain);	// �R���X�g���N�^
	//~CBackProc();

};
//======================================================================
// �t�H�A�N���E���h�@�v���V�[�W���N���X
//
// (����)��{�v���V�[�W���N���X�͌p�����Ă��Ȃ�
//
//======================================================================
class CForeProc
{
protected:
	CGameMain*		m_pGMain;
	CSprite*		m_pForegrd;

public:
	void Update();

	CForeProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CForeProc();

};
