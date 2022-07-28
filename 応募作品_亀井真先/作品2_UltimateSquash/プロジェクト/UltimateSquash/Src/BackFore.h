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
// レーダー構造体
// ---------------------------------------------------------------------
struct Reader
{
	DWORD				dwObjID;
	CBaseObj*			pEnmMisObj;
	CBaseObj*			pWeaponObj;
	DWORD				dwOwner;
	BOOL				bWithin;

	Reader()      // コンストラクタ
	{
		dwObjID = 0;
		pEnmMisObj = NULL;
		pWeaponObj = NULL;
		dwOwner = 0;
		bWithin = FALSE;
	}
};


// ---------------------------------------------------------------------
// チュートリアル構造体
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
// チュートリアル構造体
// ---------------------------------------------------------------------
struct StrTutorialPhase
{

	std::vector<StrTutorialPhaseText>	PhaseTextArray;
	DWORD				No;
	DWORD				Kinds;


	StrTutorialPhase() = default;     // コンストラクタ
	StrTutorialPhase(DWORD No, DWORD Kinds)
	{
		this->No = No; this->Kinds = Kinds;
	}
};


// --------------------------------------------------------------------
// 前景・背景　プロシージャクラス
// 
// (注意)基本プロシージャクラスは継承していない
// --------------------------------------------------------------------
class CBackForeProc 
{
protected:
	CGameMain*		m_pGMain;
	CSprite*        m_pSprite;

	CSpriteImage*   m_pImageConstruction;		//スキル欄		
	CSpriteImage*   m_pImageWeapon;		//スキルの種類	

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


	//レーダーに使う変数
	std::vector<Reader> m_ReaderArray;			// レーダー配列
	int					m_nRaderDispArea;		//レーダーの表示範囲
	float				m_nRaderSize;			//レーダーの画面の大きさ
	int					m_nRaderMpX;			
	int					m_nRaderMpY;
	int					m_nCntTime;						//
	int					m_nRaderImageSize;				//レーダーの画像サイズ

	FILE	*fp;										// FILE型構造体
	TCHAR	PhaseText[100][100][100];					//チュートリアルのテキスト
	DWORD	PhaseNum[100];								//説明文の種類ごとのテキスト文の数
	TCHAR	PhaseQueastText[100][100][100];				//クエストのテキスト
	DWORD	PhaseQueastNum[100];						//クエストのの種類ごとのテキスト文の数
	DWORD	PhaseTextNum;								//現在のテキスト文の番号
	DWORD	pNameNo;									//説明文タイトルの番号
	int		nPhaseNumAll;								//現在までのテキスト分の数
	DWORD	TutorialPhaseTextNo;						//トータルフェイズの中のテキストのフェーズ
	DWORD	pNameNum;									//説明文タイトルの数
	DWORD	dwCrearCount;								//クリアの回数
	DWORD	dwQueastTextNum;							//クエストのテキストの数


	std::vector<StrTutorialPhase>  TutorialPhaseArr;							//チュートリアルの配列
	std::vector<std::vector<StrTutorialPhaseText>>  TutorialPhaseTextArr;		//チュートリアルのテキスト配列
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

	CBackForeProc(CGameMain* pGMain);	// コンストラクタ
	~CBackForeProc();

};

