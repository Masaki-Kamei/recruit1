//=============================================================================
//		タイトル　ヘッダファイル							Title.h
//=============================================================================
#pragma once

#include "GameMain.h"


#define  TITLE_MAIN								  1
#define  TITLE_MODESELECT						  2
#define  TITLE_MODESELECT_MAINMODE				  3
#define  TITLE_CONSTRUCTION						  4
#define  TITLE_MODESELECT_TUTORIAL				  5
#define  TITLE_MODESELECT_MULTI					  6
#define  TITLE_MODESELECT_MULTIBATTLE			  7


// --------------------------------------------------------------------
// タイトル　プロシージャクラス
// --------------------------------------------------------------------
class CTitleProc
{
public:
	CGameMain*		m_pGMain;

	CSpriteImage*   m_pImageTitle;
	CSpriteImage*   m_pImageSelect;
	CSpriteImage*   m_pImageClearScore;
	CSprite*        m_pSprite;

	CSpriteImage*   m_pImageTitlePro;
	CSpriteImage*   m_pImageConstruction;
	CSpriteImage*   m_pImageConstructionFrame;
	CSpriteImage*   m_pImageWeapon;

	CSpriteImage*   m_pImageSetConstruction1;
	CSpriteImage*   m_pImageSetConstruction2;
	CSpriteImage*   m_pImageSetConstruction3;

	CSpriteImage*   m_pImageTextBackPro;	


	DWORD           m_dwCntTime;

	DWORD           m_dwStatusPhase;



	int nNo, nNoOld;	
	int nNo2, nNoOld2;	//選択されているスキル欄のナンバー

	int WeaponSelectNo[100];	//スキルの種類	
	int	WeaponSelectNoSave[100];		//編成したスキルを保存	

	FILE *fp; // FILE型構造体
	char fname[30] = "Data/Read/data_1.csv";
	TCHAR Sentence[20][20][100];
	char chr[20][100];
	char chr2;

	int ClickWeaponNo;
	int WeaponNum;

	float StartTextAlpha =1.0f;
	BOOL StartTextAlphaTrigger=FALSE;
public:

	void Title();
	void GameClear();
	void MultiBattleGameClear();

	void FileTextRead();	

	BOOL TitleMain();
	BOOL TitleStart();
	BOOL TitleModeSelect();	
	BOOL TitleModeSelectMainMode();	
	BOOL TitleConstruction();	
	BOOL TitleModeSelectTutorialMode();
	BOOL TitleModeSelectMultiMode();
	BOOL TitleModeSelectMultiBattleMode();

	BOOL CheckMousePos(int nPosX, int nPosY, int nWidth, int nHeight);

	BOOL ButtonCreate(TCHAR* PName, const float fScale,  const int nWidth, const int nHeight, const int Posx, const int Posy, const int TextPosx, const int TextPosy, const int TextSize);	

	BOOL WeaponSetColuman(int nWeapon,int nColuman);		//スキル欄に設定

	int GetWeaponSelectNo(int n) { return WeaponSelectNo[n]; }		//スキルの種類を取得	
	int GetWeaponNum() { return WeaponNum; }		

	void MapAllInit();
	void SkillExplanation(const int nWidth, const int nHeight,TCHAR **WeaponName);
	BOOL SetSkill(const int nWidth, const int nHeight, const int Posx, const int Posy, const int WeaponSet, const int LineNum, BOOL bSwitchTrigger);
	BOOL SkillList(const int nWidth,const int nHeight,BOOL bSwitchTrigger);
	void SetEnmNav();
	CTitleProc(CGameMain* pGMain);	// コンストラクタ
	~CTitleProc();




};
