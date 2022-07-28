//=============================================================================
//=============================================================================
#pragma once
#include "GameMain.h"
#include  "Playchar.h"
#include  "Title.h"
#include  "Weapon.h"
#include  "Enemy.h"

#define	STPKIND_TEXT	1
#define	STPKIND_MISION	2

#define	STPTKIND_TEXT		1
#define	STPTKIND_DRAW		2
#define	STPTKIND_NOTSTART	3
#define	STPTKIND_START		4


// ---------------------------------------------------------------------
// ���[�_�[�\����
// ---------------------------------------------------------------------
struct Reader
{
	DWORD				dwObjID;
	CBaseObj*			pEnmMisObj;
	CBaseObj*			pWeaponObj;
	DWORD				dwOwner;
	BOOL				bWithin;

	Reader()      // �R���X�g���N�^
	{
		dwObjID = 0;
		pEnmMisObj = NULL;
		pWeaponObj = NULL;
		dwOwner = 0;
		bWithin = FALSE;
	}
};


// ---------------------------------------------------------------------
// �`���[�g���A���\����
// ---------------------------------------------------------------------
struct StrTutorialPhaseText
{
	CSpriteImage*		pImage;
	DWORD				No;
	DWORD				Kinds;


	StrTutorialPhaseText() = default;
	StrTutorialPhaseText(CSpriteImage* pImage, DWORD No, DWORD Kinds)
	{
		this->pImage = pImage; this->No = No; this->Kinds = Kinds;
	}
	StrTutorialPhaseText( DWORD No, DWORD Kinds)
	{
		 this->No = No; this->Kinds = Kinds;
	}

};

// ---------------------------------------------------------------------
// �`���[�g���A���\����
// ---------------------------------------------------------------------
struct StrTutorialPhase
{

	std::vector<StrTutorialPhaseText>	PhaseTextArray;
	DWORD				No;
	DWORD				Kinds;


	StrTutorialPhase() = default;     // �R���X�g���N�^
	StrTutorialPhase(DWORD No, DWORD Kinds)
	{
		this->No = No; this->Kinds = Kinds;
	}
};


// --------------------------------------------------------------------
// �O�i�E�w�i�@�v���V�[�W���N���X
// 
// (����)��{�v���V�[�W���N���X�͌p�����Ă��Ȃ�
// --------------------------------------------------------------------
class CBackForeProc 
{
protected:
	CGameMain*		m_pGMain;
	CSprite*        m_pSprite;

	CSpriteImage*   m_pImageConstruction;		//�X�L����		
	CSpriteImage*   m_pImageWeapon;		//�X�L���̎��	

	CSpriteImage*   m_pImageForegrdRadar;
	CSpriteImage*   m_pImageForegrdRadarBase;
	CSpriteImage*   m_pImageEventReport;

	CSpriteImage*   m_pImageForegrdMangaEfect;

	CSpriteImage*	m_pImageExplanationFrame;
	CSpriteImage*	m_pImageTutorialNormal;
	CSpriteImage*	m_pImageTutorialUI;
	CSpriteImage*	m_pImageTutorialMove;
	CSpriteImage*	m_pImageTutorialHit;
	CSpriteImage*	m_pImageTutorialTarget;
	CSpriteImage*	m_pImageTutorialBoom;
	CSpriteImage*	m_pImageTutorialSkill;
	CSpriteImage*	m_pImageTutorialSetSkill;


	CSpriteImage*	m_pBackImage;

	CSpriteImage*	m_pQuestTextBack;


	//���[�_�[�Ɏg���ϐ�
	std::vector<Reader> m_ReaderArray;			// ���[�_�[�z��
	int					m_nRaderDispArea;		//���[�_�[�̕\���͈�
	float				m_nRaderSize;			//���[�_�[�̉�ʂ̑傫��
	int					m_nRaderMpX;			
	int					m_nRaderMpY;
	int					m_nCntTime;						//
	int					m_nRaderImageSize;				//���[�_�[�̉摜�T�C�Y

	FILE	*fp;										// FILE�^�\����
	TCHAR	PhaseText[100][100][100];					//�`���[�g���A���̃e�L�X�g
	DWORD	PhaseNum[100];								//�������̎�ނ��Ƃ̃e�L�X�g���̐�
	TCHAR	PhaseQueastText[100][100][100];				//�N�G�X�g�̃e�L�X�g
	DWORD	PhaseQueastNum[100];						//�N�G�X�g�̂̎�ނ��Ƃ̃e�L�X�g���̐�
	DWORD	PhaseTextNum;								//���݂̃e�L�X�g���̔ԍ�
	DWORD	pNameNo;									//�������^�C�g���̔ԍ�
	int		nPhaseNumAll;								//���݂܂ł̃e�L�X�g���̐�
	DWORD	TutorialPhaseTextNo;						//�g�[�^���t�F�C�Y�̒��̃e�L�X�g�̃t�F�[�Y
	DWORD	pNameNum;									//�������^�C�g���̐�
	DWORD	dwCrearCount;								//�N���A�̉�
	DWORD	dwQueastTextNum;							//�N�G�X�g�̃e�L�X�g�̐�


	std::vector<StrTutorialPhase>  TutorialPhaseArr;							//�`���[�g���A���̔z��
	std::vector<std::vector<StrTutorialPhaseText>>  TutorialPhaseTextArr;		//�`���[�g���A���̃e�L�X�g�z��
public:
	void			Update();
	CSprite*        GetSprite() { return m_pSprite; }
	CSpriteImage*   GetImageRadar() { return m_pImageForegrdRadar; }
	CSpriteImage*   GetImageEventReport() { return m_pImageEventReport; }
	CSpriteImage*   GetImageMangaEfect() { return m_pImageForegrdMangaEfect; }

	void			UpdateConstruction();
	void			UpdateScore(const int nScoreImagePosX, const int nScoreImagePosY, const int nScoreTextPosX, const int nScoreTextPosY, const int nScorePointPosX, const int nScorePointPosY, int nScore);
	void            UpdateRadar(DWORD dwPlayerNo=FIRSTPLAYER);
	void            DispEnmInfoRader(DWORD dwPlayerNo);
	void            TutorialText();
	void			TutorialTextInit();
	void			TutorialTextSentenceEnd();
	void			TutorialTextDisplay();
	void			TutorialTextExplanationEnd();
	void			TutorialMisionText();
	void			TutolialTextOnlySentence(const int WidthFreamPos, const int HeightFreamPos, const int FreamWidth, const int FreamHeight, const int WidthFreamSize, const int HeightFreamSize);
	void			TutolialTextMisionSentence(const int WidthFreamPos, const int HeightFreamPos, const int FreamWidth, const int FreamHeight, const int WidthFreamSize, const int HeightFreamSize);
	void			MultiUpdate();
	void			MultiUpdateConstruction(CPcObj* pPcObj, CWeaponSwordObj* pWeaponObj, int DestX, int DestY);
	void			MultiUpdateScore();
	void            SetReaderOn( DWORD dwPlayerNo);	
	void			FileTextRead();		
	void			MainModeBackFore();
	void			MainModeStartCount();
	void			MainModeEnd();
	void			TutorialPhaseDisKinds(StrTutorialPhase TutorialPhase);
	void			TutorialPhaseTextDisKinds(StrTutorialPhaseText TutorialPhaseText);
	void			TutorialCapture();

	CBackForeProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CBackForeProc();

};

