//=============================================================================
//
//		�Q�[���̃��C������
//																GameMain.h
//=============================================================================

#pragma once

//�x����\��
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)


//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>
#include <vector>

#include "Main.h"
#include "Direct3D.h"
#include "Shader.h"
#include "FbxMesh.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite3D.h"
#include "Collision.h"
#include "Displace.h"
#include "BBox.h"
#include "BaseProc.h"
#include "MyImgui.h"

#include "MPR.h"		
#include "RenderBuf.h"


// �X�e�[�^�X�^�C�v
#define  NONE				0x00000000
#define  TITLE				0x00000001
#define  STAGEDEMO  		0x00000002
#define  GAMEMAIN			0x00000004
#define  GAMEOVER			0x00000008
#define  GAMECLEAR			0x00000010
#define  GAMEEND			0x00000020
#define  SIMPLEMODERESULT	0x00000040
#define  GAMETUTORIAL		0x00000080
#define  GAMEMULTI			0x00000160

#define  GAMEMULTIBATTLERESULT			0x00000320


#define  GAMEMAINSUB		0x00000040


#define  NORMAL				0x00000001
#define  WAIT				0x00000002
#define  DAMAGE				0x00000004
#define  FLASH				0x00000008
#define  DEAD				0x00000010

// �X�e�[�^�X�T�u
#define  ATTACKNONE			0x00000001
#define  ATTACKMOVE			0x00000002
#define  ATTACKLASER		0x00000004
#define  ATTACKCANNON		0x00000008
#define  ATTACKBOM			0x00000010
#define  ATTACKEARTH		0x00000020
#define  ATTACKSWORD		0x00000040
#define  ATTACKFLAME		0x00000080
#define  ATTACKWAIT			0x00000100

#define  START				0x00001000
#define  INTER				0x00001001
#define  FINAL				0x00001002


// �I�u�W�F�N�g�敪
#define  PC					0x00000001
#define  NPC				0x00000002
#define  ENM				0x00000004

//�}�b�v�ɑ΂��Ă̎l����
#define  FRONT				0x00000001
#define  RIGHT				0x00000002
#define  LEFT				0x00000004
#define  BACK				0x00000008

#define	TITLEMODE		0
#define	MAINMODE		1
#define	SIMPLEMODE		2
#define	TUTORIAL		3
#define	MULTI			4

//
#define	FIRSTPLAYER			1
#define	SECONDPLAYER		2

class CMain;
class CShader;
class CSpriteImage;
class CSprite;
class CFontTexture;
class CCollision;
class CWave;
class CBBox;
class CFbxMeshCtrl;

class CBaseObj;
class CBaseProc;
class CPcProc;
class CCameraProc;
class CEnmProc;
class CMapProc;
class CWeaponProc;
class CEffectProc;
class CBackForeProc;
class CTitleProc;

class CMapSubProc;		

class CMPR;	
class CRenderBufProc;


// --------------------------------------------------------------------------------------------------
//  �Q�[�����C���N���X
// --------------------------------------------------------------------------------------------------
class CGameMain
{
public:
	// �����o�ϐ�
	CMain*			m_pMain;		// ���C���N���X
	CDirect3D*		m_pD3D;			//	Direct3D�I�u�W�F�N�g
	CXAudio*		m_pXAudio;		//	XAudio�I�u�W�F�N�g
	CDirectInput*	m_pDI;			//	DirectInputD�I�u�W�F�N�g
	CFontTexture*	m_pFont;		//	�t�H���g�e�N�X�`���[
	CShader*		m_pShader;		//	�V�F�[�_�[
	CFbxMeshCtrl*	m_pFbxMeshCtrl;	// ���b�V���R���g���[���N���X   

	DWORD           m_dwGameStatus;
	
	// �J�����E���C�g�E�r���[
	VECTOR3         m_vEyePt;		//�J�����i���_�j�ʒu
	VECTOR3         m_vLookatPt;	//�����ʒu
	MATRIX4X4       m_mView;
	MATRIX4X4       m_mProj;
	VECTOR3         m_vLightDir;	//�f�B���N�V���i�����C�g�̕���

		// �J�����E���C�g�E�r���[
	VECTOR3         m_vEyePtSecond;		//�J�����i���_�j�ʒu
	VECTOR3         m_vLookatPtSecond;	//�����ʒu
	MATRIX4X4       m_mViewSecond;
	MATRIX4X4       m_mProjSecond;
	VECTOR3         m_vLightDirSecond;	//�f�B���N�V���i�����C�g�̕���


	// MPR
	CMPR*			m_pMPR;		
	CRenderBufProc*	m_pRenderBufProc;  



	// �v���V�[�W��
	CPcProc*		m_pPcProc;
	CCameraProc*	m_pCameraProc;
	CEnmProc*		m_pEnmProc;
	CMapProc*		m_pMapProc;
	CWeaponProc*	m_pWeaponProc;
	CEffectProc*	m_pEffectProc;
	CBackForeProc*	m_pBackForeProc;
	CTitleProc*		m_pTitleProc;

	CMapSubProc*	m_pMapSubProc;		



	// �T�E���h
	CXAudioSource*   m_pSeLazer;
	CXAudioSource*   m_pSeNitro;
	CXAudioSource*   m_pSeDead;
	CXAudioSource*   m_pSeFire;

	// �X�R�A
	int             m_nScore;
	int				m_nHighScore;	
	int             m_nScoreSec;

	//�^�C��
	int				m_nTimer;		
	int				m_nTimeNum;

	//���[�h
	DWORD			m_dModeType;		

	DWORD			m_dPhase;		


public:
	// ���\�b�h
	CGameMain(CMain* pMain);
	~CGameMain();

	HRESULT Init();
	void    Loop();
	void    Quit();

	void    GameMain();

	void    GameTutorial();		
	void	GameTutorialPhase();	

	void    GameMulti();

	HRESULT ChangeScreenMode(int nMode=-1);   

};


