//=============================================================================
//
//		�v���C�L�����N�^�[�̏���
//																Playchar.h
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
// �v���C�L�����N�^�[�@�I�u�W�F�N�g�N���X
class CPcObj : public CBaseObj
{
protected:
	int  m_nShotWait;
	int  m_nDifShotWait;
	int  m_nProAtkWait;
	int  m_nCharShotWait;
	int  m_nBoundShotWait;

	int  m_nProAtkTime;

	int  m_nDoorTime;


public:
	void Update() override;

	// �R���X�g���N�^�i�I�u�W�F�N�g�̏������j
	CPcObj(CGameMain* pGMain);
	~CPcObj();

};
//======================================================================
// �v���C�L�����N�^�[�@�v���V�[�W���N���X
class CPcProc : public CBaseProc
{
protected:
	CPcObj*			m_pPcObj;
	int             m_nPcNum;

public:
	// �A�N�Z�X�֐�
	CPcObj*			    GetPcObjPtr() { return m_pPcObj; }
	int				    GetPcNum() { return m_nPcNum; }
	void				AddPcNum(int Num) { m_nPcNum += Num; }

	CPcProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CPcProc() { ; }

};