//=============================================================================
//
//		�f�����ʂ̏���
//																Effect.h
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

#define  ITEMRESQUE   1           // �~�}��
#define  ITEMDOOR     2           // �h�A


#define  ITEM_MAX  50

#define  EFFECT_BOM_MAX  50

//======================================================================
// �f�����ʁE�����@�I�u�W�F�N�g�N���X
class CEffectBomObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2) override;

	void Update() override;

	// �R���X�g���N�^
	CEffectBomObj(CGameMain* pGMain);
	~CEffectBomObj();

};
//======================================================================
// �f�����ʁE�����@�v���V�[�W���N���X
class CEffectBomProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2);

	CEffectBomProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEffectBomProc() { ; }	// �f�X�g���N�^

};
//=================================================================================================================
//======================================================================
// �A�C�e���@�I�u�W�F�N�g�N���X
class CItemObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2, DWORD) override;

	void Update() override;

	// �R���X�g���N�^
	CItemObj(CGameMain* pGMain);
	~CItemObj();

};
//======================================================================
// �A�C�e���@�v���V�[�W���N���X
class CItemProc : public CBaseProc
{
public:
	void Update() override;
	CItemProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CItemProc() { ; }	// �f�X�g���N�^

};

//=================================================================================================================


//======================================================================
// �f�����ʁ@�v���V�[�W���N���X
class CEffectProc : public CBaseProc
{
public:
	CEffectBomProc*		m_pEffectBomProc;

	CItemProc*			m_pItemProc;

public:
	void  SetNonActive();

	CEffectProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEffectProc() { ; }	// �f�X�g���N�^
};
