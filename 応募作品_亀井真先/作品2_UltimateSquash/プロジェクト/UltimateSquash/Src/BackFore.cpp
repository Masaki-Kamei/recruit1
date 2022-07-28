//=============================================================================
//		前景・背景							                   BackFore.cpp
//=============================================================================
#include  "BackFore.h"

//============================================================================
//
// 前景・背景プロシージャのコンストラクタ
//
// ---------------------------------------------------------------------------
CBackForeProc::CBackForeProc(CGameMain* pGMain)
{
	m_pGMain		= pGMain;

	m_pImageConstruction = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Construction_Pro.png"));						//スキル欄イメージのロード
	m_pImageWeapon = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/WeaponTest.png"));									//スキルの種類イメージのロード
	m_pImageForegrdRadar = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Foregrd_Radar_Ver4.png"));						//レーダーイメージのロード
	m_pImageForegrdRadarBase = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Foregrd_Radar2.png"));						//レーダーのベースイメージのロード
	m_pImageEventReport = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/EVENT.png"));									//デンジャーイメージのロード
	m_pImageForegrdMangaEfect = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/MangaEfect_1.png"));						//擬音イメージのロード

	//チュートリアルのイメージロード
	m_pImageExplanationFrame = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Explanation_Frame_Ver2.png"));		//爆発のチュートリアルイメージのロード
	m_pImageTutorialNormal = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_Normal.png"));		//ベースチュートリアルレーダーイメージのロード
	m_pImageTutorialUI = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_UI_Ver2.png"));			//UIのチュートリアルレーダーイメージのロード
	m_pImageTutorialMove = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_Move.png"));			//移動のチュートリアルレーダーイメージのロード
	m_pImageTutorialHit = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_Hit.png"));				//打ち返すチュートリアルレーダーイメージのロード
	m_pImageTutorialTarget = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_Target.png"));		//的のチュートリアルレーダーイメージのロード
	m_pImageTutorialBoom = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_Boom.png"));			//爆弾のチュートリアルレーダーイメージのロード
	m_pImageTutorialSkill = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_Skill.png"));			//スキルのチュートリアルイメージのロード
	m_pImageTutorialSetSkill = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Tutorial/Tutorial_Image_SetSkill.png"));	//スキルのチュートリアルイメージのロード
	m_pQuestTextBack = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Text_Back_2_Ver2.png"));							//チュートリアルクリア条件イメージのロード
	m_pBackImage = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/black.png"));											//背景を暗くするイメージのロード

	m_pSprite       = new CSprite(m_pGMain->m_pShader); // スプライトの生成

	//レーダーの変数
	m_nRaderDispArea = 50;  // レーダーの表示範囲(m)
	m_nRaderSize = 156;     // レーダーの画面上の大きさ(ピクセル)
	m_nRaderMpX = 0;
	m_nRaderMpY = 0;
	FileTextRead();

}
// ---------------------------------------------------------------------------
//
// 前景・背景プロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CBackForeProc::~CBackForeProc()
{


	SAFE_DELETE(m_pImageConstruction);
	SAFE_DELETE(m_pImageWeapon)
	SAFE_DELETE(m_pImageForegrdRadar);
	SAFE_DELETE(m_pImageEventReport);
	SAFE_DELETE(m_pImageForegrdRadarBase);
	SAFE_DELETE(m_pImageForegrdMangaEfect);

	SAFE_DELETE(m_pImageExplanationFrame);
	SAFE_DELETE(m_pImageTutorialNormal);
	SAFE_DELETE(m_pImageTutorialUI);
	SAFE_DELETE(m_pImageTutorialMove);
	SAFE_DELETE(m_pImageTutorialHit);
	SAFE_DELETE(m_pImageTutorialTarget);
	SAFE_DELETE(m_pImageTutorialBoom);
	SAFE_DELETE(m_pImageTutorialSkill);
	SAFE_DELETE(m_pImageTutorialSetSkill);


	SAFE_DELETE(m_pBackImage);
	SAFE_DELETE(m_pQuestTextBack);


	SAFE_DELETE(m_pSprite);

	// vectorの削除
	m_ReaderArray.clear();					// 配列削除
	m_ReaderArray.shrink_to_fit();			// 不要メモリ解放


}
//------------------------------------------------------------------------
//
//	前景・背景プロシージャの更新	
//
//------------------------------------------------------------------------
void CBackForeProc::Update()
{
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();

	if (m_pGMain->m_dModeType == MAINMODE|| m_pGMain->m_dModeType == TUTORIAL)
	{
		const int nScoreImagePosX = 0, nScoreImagePosY = 45;	//スコア画像表示位置
		const int nScoreTextPosX = 10, nScoreTextPosY = 8;		//スコア文字表示位置
		const int nScorePointPosX = 0, nScorePointPosY = 55;	//スコア数値表示位置
		//スコア描画
		UpdateScore(nScoreImagePosX, nScoreImagePosY, nScoreTextPosX, nScoreTextPosY, nScorePointPosX, nScorePointPosY, m_pGMain->m_nScore);
		//スキル欄の表示と処理
		UpdateConstruction();
		//レーダの表示
		UpdateRadar();


	}

	//チュートリアルのテキスト表示
	if (m_pGMain->m_dModeType == TUTORIAL)		TutorialText();	
	//メインモード表示
	if (m_pGMain->m_dModeType == MAINMODE)		MainModeBackFore();	
	//マルチモードの表示
	if (m_pGMain->m_dModeType == MULTI)
	{
		MultiUpdate();																		//マルチモードの更新
		MultiUpdateScore();																	//マルチモードのスコア処理
		UpdateRadar(FIRSTPLAYER);															//１Pレーダーの処理
		UpdateRadar(SECONDPLAYER);															//２Pレーダーの処理
		m_pSprite->DrawRect(0, (WINDOW_HEIGHT / 2)-3, WINDOW_WIDTH, 6, RGB(0, 0, 0));		//分割中央線表示
		MainModeBackFore();																	//ゲームの流れ更新

	}
};

//============================================================================
//
//   スキル欄の更新と表示
//
//--M.Kamei_Point
//--Point_SkillDisplay
//
//============================================================================
void CBackForeProc::UpdateConstruction()
{
	int   DestX, DestY;												//位置（保存用）
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();			//プレイヤーの取得

	const int nWidth = 258, nHeight = 258;							//元の大きさ
	const int nWidthScale = nWidth / 2;								//表示大きさ
	const int nHeightScale = nHeight / 2;							//表示大きさ
	const int WeaponSet = 3;										//スキルの数

	//スキル欄の枠
	const int nColumnStartX = 0, nColumnStartY = 0;					//パターン左上
	const int nColumnWidth = 250, nColumnHeight = 250;				//パターン大きさ
	const int nColumnWidthScale = nColumnWidth / 2;					//幅の大きさ
	const int nColumnHeightScale = nColumnHeight / 2;				//高さの大きさ

	//スキル欄の外枠
	const int nFreamWidth = 272, nFreamHeight = 272;				//パターン大きさ
	const int nFreamWidthScale = nFreamWidth / 2;					//幅の大きさ
	const int nFreamHeightScale = nFreamHeight / 2;					//高さの大きさ
	const int nFreamNormalStartX = 300, nFreamNormalStartY = 0;		//パターン左上(ノーマル)
	const int nFreamChoiceStartX = 0, nFreamChoiceStartY = 300;		//パターン左上(選択中)
	const int nFreamUseStartX = 300, nFreamUseStartY = 300;			//パターン左上(発動中)


	DestX = 10;														//位置の調整X
	DestY = WINDOW_HEIGHT - nHeight + 100;							//位置の調整Y

	float WaitTime[100];											//残りのクールタイム
	float WaitMaxTime[100];											//クールタイム最大値
	int		WeaponNo = pPcObj->GetWeaponNo();						//スキルナンバー
	int		WeaponColuman = pPcObj->GetWeaponColuman() - 1;			//現在のスキル選択欄
	float	RemWaitTime[100];										//クールタイムの割合

	int	LineNum = (m_pGMain->m_pTitleProc->GetWeaponNum()/5)+1;		//スキルの選択欄の行の数


	//スキルの枠表示--------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < WeaponSet; i++)
	{
		//それぞれのスキルのクールタイム最大値を取得
		WaitMaxTime[i] = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->GetWeaponMaxWaitTime(i);
		//それぞれのスキルのクールタイムを取得
		WaitTime[i] = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->GetWeaponWaitTime(i);
		//残りのクールタイム
		RemWaitTime[i] = WaitTime[i] / WaitMaxTime[i];
		//クールタイム中の表示 
		if (WaitTime[i] > 0) {
			//スキルのクールタイムの比率に合わせて表示するパターンの左上、大きさ、幅と高さの大きさの表示を変更していく
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY + ((nHeightScale*(RemWaitTime[i]))), 0, nHeight*(RemWaitTime[i]), nColumnWidth, nColumnHeight*(1 - RemWaitTime[i]), nWidthScale, nHeightScale*(1 - RemWaitTime[i]));	//欄の枠
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nColumnStartX, nColumnStartY, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale, 0.5);		//欄の枠(クールタイムの表示で薄くする)
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nFreamNormalStartX, nFreamNormalStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);	//欄の外枠

		}
		//スキル発動中
		else if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetSkillActive(i) == TRUE) {
			//表示
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nColumnStartX, nColumnStartY, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale);			//欄の枠
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nFreamUseStartX, nFreamUseStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);			//欄の外枠


		}
		//選択中のスキル欄を枠付きにする
		else if (WeaponColuman == i) {
			//表示
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nColumnStartX, nColumnStartY, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale);			//欄の枠
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nFreamChoiceStartX, nFreamChoiceStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);	//欄の外枠

		}
		else {
			//表示
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nColumnStartX, nColumnStartY, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale);			//欄の枠
			m_pSprite->Draw(m_pImageConstruction, DestX + (nWidthScale + DestX)*i, DestY, nFreamNormalStartX, nFreamNormalStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);	//欄の外枠

		}

		//スキルのアイコン表示--------------------------------------------------------------------------------------------------------------
		DWORD dwWeaponSelectNo = pPcObj->GetWeaponColumanNo(i);
		int y = (dwWeaponSelectNo - 1) / 5;
		int x = 0;
		//選択したスキルが選択欄のなん列目にあるか
		for (int j = 0; j < LineNum; j++)
		{
			if (((j + 1) * 5) > (dwWeaponSelectNo - 1))
			{
				x = (dwWeaponSelectNo - 1) - 5;
				if (x < 0) {
					x = (dwWeaponSelectNo - 1);
				}
				break;
			}
		}

		//スプライト内の座標をスキルに合わせる処理
		float	ReduceGage;
		ReduceGage= WaitTime[i] / WaitMaxTime[i];		//残りのクールタイムを取得
		ReduceGage= (nHeight * (1 + y)) * ReduceGage;
		ReduceGage = (nHeight * (1 + y))- ReduceGage;
		ReduceGage= ReduceGage / (1 + y);
		if (dwWeaponSelectNo != NULL) {		//スキルがセットされたときにスキルを表示
			if (WaitTime[i] > 0) {
				//スキルのクールタイムの比率に合わせて表示するパターンの左上、大きさ、幅と高さの大きさの表示を変更していく
				m_pSprite->Draw(m_pImageWeapon, DestX + (nWidthScale + DestX)*i, DestY + ((nHeightScale*(RemWaitTime[i]))), nWidth*x, ((nHeight*(y+1))-(ReduceGage)), nWidth, (nHeight*(1 - RemWaitTime[i])), nWidthScale, nHeightScale*(1 - RemWaitTime[i]));		
				m_pSprite->Draw(m_pImageWeapon, DestX + (nWidthScale + DestX)*i, DestY, nWidth*x, nHeight*y, nWidth, nHeight, nWidthScale, nHeightScale, 0.5);																											
			}
			else {
				m_pSprite->Draw(m_pImageWeapon, DestX + (nWidthScale + DestX)*i, DestY, nWidth*x, nHeight*y, nWidth, nHeight, nWidthScale, nHeightScale);
			}
		}

	}

}
//============================================================================
//
//   スコアの更新と表示
//
//	const int		nScoreImagePosX　スコア画像表示位置X
//	const int		nScoreImagePosY　スコア画像表示位置Y
//	const int		nScoreTextPosX	 スコア文字表示位置X
//	const int		nScoreTextPosY   スコア文字表示位置Y
//	const int		nScorePointPosX	 スコア数値表示位置X
//	const int		nScorePointPosY  スコア数値表示位置Y
//	int				nScore			 スコアの数値
//
//
//============================================================================
void CBackForeProc::UpdateScore(const int nScoreImagePosX, const int nScoreImagePosY, const int nScoreTextPosX, const int nScoreTextPosY, const int nScorePointPosX, const int nScorePointPosY,int nScore)
{
	//スコア画像表示---------------------------------------
	const int nScoreImageStartX = 0, nScoreImageStartY = 250;	//パターンの左上位置
	const int nScoreImageWidth = 221, nScoreImageHeight = 58;	//パターンの大きさ
	m_pSprite->Draw(m_pImageForegrdRadarBase, nScoreImagePosX, nScoreImagePosY, nScoreImageStartX, nScoreImageStartY, nScoreImageWidth, nScoreImageHeight, 1.0f);

	//スコアの文字表示-------------------------------------
	const int nScoreTextSize = 50;	//スコア文字のサイズ
	m_pGMain->m_pFont->FreamDraw(nScoreTextPosX, nScoreTextPosY, _T("SCORE"), nScoreTextSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));
	m_pGMain->m_pFont->Draw(nScoreTextPosX, nScoreTextPosY, _T("SCORE"), nScoreTextSize, RGB(255, 0, 0), 1.0f, _T("メイリオ ボールド"));

	//スコアの数値表示-------------------------------------
	TCHAR str[256] = { 0 };
	const int nScorePointSize = 50;	//スコア数値のサイズ
	_stprintf(str, _T("%8d"), nScore);
	m_pGMain->m_pFont->Draw(nScorePointPosX, nScorePointPosY, str, nScorePointSize, RGB(255, 255, 255), 1.0, _T("メイリオ ボールド"));

}
//============================================================================
//
//   レーダーマップの更新と表示
//
//	DWORD			dwPlayerNo	プレイヤー番号
//
//
//============================================================================
void CBackForeProc::UpdateRadar(DWORD dwPlayerNo)
{
	TCHAR str[256];
	const int nDist = 20;																 // レーダーマップの画面端からの余白

	// 表示位置左上座標
	m_nRaderMpX = WINDOW_WIDTH - (m_nRaderSize + nDist);
	m_nRaderMpY = nDist + 30;
	if(dwPlayerNo==SECONDPLAYER)	m_nRaderMpY =(WINDOW_HEIGHT/2)+ m_nRaderMpY;
	const int	m_nRaderStartPosX = 400, m_nRaderStartPosY = 28;					//パターン左上

	// 表示位置中心座標を設定する
	const float fOfX = (m_nRaderMpX + m_nRaderSize / 2)-8;							//表示位置X
	const float fOfY = (m_nRaderMpY + m_nRaderSize / 2)-8;							//表示位置Y
	const float fOfStartX = 0, fOfStartY = 272;										//パターン左上
	const float fOfWidthX = 16;														// 幅
	const float fOfHeightY = 16;													// 高さ

	//レーダーフレームの変数
	const int	m_nRaderTimerFreamMpX = m_nRaderMpX - 205;							//表示位置X
	const int	m_nRaderTimerFreamMpY = m_nRaderMpY - 28;							//表示位置Y
	const int	m_nRaderTimerFreamStartPosX = 0,m_nRaderTimerFreamStartPosY = 0;	//パターン左上
	const int	m_nRaderTimerFreamStartWidth = 373;									// 幅
	const int	m_nRaderTimerFreamStartHeight= 196;									// 高さ

	//レーダーの変数
	const int	m_nRaderTimerMpX = m_nRaderMpX - 130;								//表示位置X
	const int	m_nRaderTimerMpY = m_nRaderMpY - 20;								//表示位置Y
	const int	m_nRaderTimerSize = 80;												//大きさ

	// レーダーマップの表示
	m_pSprite->Draw(m_pImageForegrdRadarBase, m_nRaderMpX, m_nRaderMpY, m_nRaderStartPosX, m_nRaderStartPosY, m_nRaderSize, m_nRaderSize, 1.0f);
	m_pSprite->Draw(m_pImageForegrdRadar, fOfX, fOfY , fOfStartX, fOfStartY, fOfWidthX, fOfHeightY);
	m_pSprite->Draw(m_pImageForegrdRadarBase, m_nRaderTimerFreamMpX, m_nRaderTimerFreamMpY, m_nRaderTimerFreamStartPosX, m_nRaderTimerFreamStartPosY, m_nRaderTimerFreamStartWidth, m_nRaderTimerFreamStartHeight,1.0f);
	if (m_pGMain->m_nTimer >= 0) {
		_stprintf(str, _T("%3d"), m_pGMain->m_nTimer);
		m_pGMain->m_pFont->Draw(m_nRaderTimerMpX, m_nRaderTimerMpY, str, m_nRaderTimerSize, RGB(255, 255, 255), 1.0, _T("メイリオ ボールド"));
	}
	else {
		_stprintf(str, _T("%3d"),0);
		m_pGMain->m_pFont->Draw(m_nRaderTimerMpX, m_nRaderTimerMpY, str, m_nRaderTimerSize, RGB(255, 255, 255), 1.0, _T("メイリオ ボールド"));

	}

	// レーダー内に敵の表示 
	SetReaderOn(dwPlayerNo);          // レーダー配列に敵
	DispEnmInfoRader(dwPlayerNo);		// 表示
}

//============================================================================
//
// レーダーに敵の情報を表示する処理
//
//	DWORD			dwPlayerNo	プレイヤー番号
//
//
//============================================================================
void CBackForeProc::DispEnmInfoRader(DWORD dwPlayerNo)
{

	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	if (dwPlayerNo == SECONDPLAYER)pPcObj = m_pGMain->m_pPcProc->GetPcSecObjPtr();

	float fRatio = (float)m_nRaderDispArea / m_nRaderSize;  // 実座標とレーダー画面座標との表示比率
	// 表示位置中心座標を設定する
	float fOfX = m_nRaderMpX + m_nRaderSize / 2;
	float fOfY = m_nRaderMpY + m_nRaderSize / 2;

	for (int i = 0; i < m_ReaderArray.size(); i++)
	{
		// ＰＣを原点とした敵の位置を求める
		VECTOR3 vEnm = GetPositionVector(m_ReaderArray[i].pEnmMisObj->GetWorld() * XMMatrixInverse(NULL, pPcObj->GetWorld()));
		int dx = (int)(vEnm.x / fRatio) + fOfX - 8;
		int dy = (int)(-vEnm.z / fRatio) + fOfY - 8;

		//ボールの表示変数
		const int BallImageStartPosX = 48, BallImageStartPosY = 256;	//パターン左上
		const int BallImageStartWidth = 16, BallImageStartHeight = 16;	//パターン大きさ
		//ボールの表示変数(跳ね返したとき)
		const int BallImageDamageStartPosX = 16, BallImageDamageStartPosY = 256;	//パターン左上
		const int BallImageDamageStartWidth = 16, BallImageDamageStartHeight = 16;	//パターン大きさ
		//爆弾の表示変数
		const int BoomImageStartPosX = 144, BoomImageStartPosY = 272;	//パターン左上
		const int BoomImageStartWidth = 16, BoomImageStartHeight = 16;	//パターン大きさ
		//的の表示変数
		const int TargetImageStartPosX = 16, TargetImageStartPosY = 272;	//パターン左上
		const int TargetImageStartWidth = 16, TargetImageStartHeight = 16;	//パターン大きさ

		//敵の位置を表示-------------------------------------------------------
		if (m_ReaderArray[i].dwObjID == ENM_BALL_ID)
		{
			// ボールの表示
			if (m_ReaderArray[i].pEnmMisObj->GetDamage() == TRUE) {
				m_pSprite->Draw(m_pImageForegrdRadar, dx, dy, BallImageStartPosX, BallImageStartPosY, BallImageStartWidth, BallImageStartHeight, 1.0f);

			}
			else {
				//跳ね返したときの表示
				m_pSprite->Draw(m_pImageForegrdRadar, dx, dy, BallImageDamageStartPosX, BallImageDamageStartPosY, BallImageDamageStartWidth, BallImageDamageStartHeight, 1.0f);
			}
		}
		else if (m_ReaderArray[i].dwObjID == ENM_BALLBOOM_ID)
		{
			//爆弾の表示	
			m_pSprite->Draw(m_pImageForegrdRadar, dx, dy, BoomImageStartPosX, BoomImageStartPosY, BoomImageStartWidth, BoomImageStartHeight, 1.0f);
		}
		else
		{
			// 的の表示
			m_pSprite->Draw(m_pImageForegrdRadar, dx, dy, TargetImageStartPosX, TargetImageStartPosY, TargetImageStartWidth, TargetImageStartHeight, 1.0f);

		}
	}
}

//-----------------------------------------------------------------------------   
// レーダー配列の設定
//
//
//-----------------------------------------------------------------------------
void	CBackForeProc::SetReaderOn(DWORD dwPlayerNo)
{
	int MpX, MpY, OfX, OfY;
	int nArea, nSize;

	MpX = m_nRaderMpX;	// 表示位置左上座標
	MpY = m_nRaderMpY;
	OfX = m_nRaderMpX + m_nRaderSize / 2;	// 表示位置中心座標
	OfY = m_nRaderMpY + m_nRaderSize / 2;
	nArea = m_nRaderDispArea;
	nSize = m_nRaderSize;


	m_ReaderArray.clear();			// 配列削除
	m_ReaderArray.shrink_to_fit();	// 不要メモリ解放

	// 現在生きている敵情報をレーダー配列に格納する
	float fRatio = (float)nArea / nSize;  // 実座標とレーダー画面座標との表示比率
	Reader lo;
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	if(dwPlayerNo==SECONDPLAYER)pPcObj = m_pGMain->m_pPcProc->GetPcSecObjPtr();
	std::vector<CBaseObj*> EnmMisObjArray;
	if (m_pGMain->m_dModeType == MULTI)m_pGMain->m_pEnmProc->GetActiveEnmMulti(EnmMisObjArray, dwPlayerNo);
	else m_pGMain->m_pEnmProc->GetActiveEnm(EnmMisObjArray);   // 現在生きている敵の情報を設定する

	for (int i = 0; i < EnmMisObjArray.size(); i++)   // 敵の情報をレーダー配列に格納
	{
		// ＰＣを原点とした敵の位置を求め、レーダー表示範囲内かどうかを判定する
		VECTOR3 vEnm = GetPositionVector(EnmMisObjArray[i]->GetWorld() * XMMatrixInverse(NULL, pPcObj->GetWorld()));
		int dx = (int)(vEnm.x / fRatio) + OfX - 8;
		int dy = (int)(-vEnm.z / fRatio) + OfY - 8;
		BOOL bWithin = FALSE;
		if (dx >= MpX && dx <= MpX + nSize - 8 && dy >= MpY && dy <= MpY + nSize - 8)
		{
			bWithin = TRUE;   // 画面内
		}
		if (bWithin) // レーダー内の表示のみ処理する
		{
			lo.dwObjID = EnmMisObjArray[i]->GetObjID();
			lo.pEnmMisObj = EnmMisObjArray[i];
			lo.pWeaponObj = NULL;
			lo.dwOwner = ENM;

			lo.bWithin = bWithin;
			m_ReaderArray.push_back(lo);
		}

	}

	EnmMisObjArray.clear();
	EnmMisObjArray.shrink_to_fit();
}


//============================================================================
//
//   チュートリアル表示するときのステータス格納
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//============================================================================
void CBackForeProc::TutorialCapture()
{
	//配列初期化
	int ArrSize = TutorialPhaseArr.size();
	if (ArrSize > 0) {
		for (int i = 0; i < ArrSize; i++)
		{
			TutorialPhaseArr[i].PhaseTextArray.clear();
			TutorialPhaseArr[i].PhaseTextArray.shrink_to_fit();
		}
		TutorialPhaseArr.clear();
		TutorialPhaseArr.shrink_to_fit();
	}
	const int		  TutorialPhaseArrNum = 11;		//フェーズの数
	//フェーズのステータス（番号、種類）
	TutorialPhaseArr =
	{
		StrTutorialPhase(0,STPKIND_TEXT),	//ルール、UI、プレイヤーの移動(説明)
		StrTutorialPhase(1,STPKIND_MISION),	//プレイヤーの移動(ミッション)
		StrTutorialPhase(2,STPKIND_TEXT),	//ボール(説明)
		StrTutorialPhase(3,STPKIND_MISION),	//ボール(ミッション)
		StrTutorialPhase(4,STPKIND_TEXT),	//的(説明)
		StrTutorialPhase(5,STPKIND_MISION),	//的(ミッション)
		StrTutorialPhase(6,STPKIND_TEXT),	//爆弾ボール(説明)
		StrTutorialPhase(7,STPKIND_MISION),	//爆弾ボール(ミッション)
		StrTutorialPhase(8,STPKIND_TEXT),	//スキル(説明)
		StrTutorialPhase(9,STPKIND_MISION),	//スキル(ミッション)
		StrTutorialPhase(10,STPKIND_TEXT),	//最後に(説明)
	};	//フェーズ配列

	//フェーズテキストのステータス（画像、番号、種類）
	TutorialPhaseTextArr =
	{
		//ルール、UI、プレイヤーの移動
		{
		StrTutorialPhaseText(0,STPTKIND_TEXT),
		StrTutorialPhaseText(1,STPTKIND_TEXT),
		StrTutorialPhaseText(m_pImageTutorialNormal,2,STPTKIND_DRAW),
		StrTutorialPhaseText(m_pImageTutorialMove,3,STPTKIND_NOTSTART),
		},
		//ミッション(0,0)
		{StrTutorialPhaseText(0,0),},
		//ボール
		{StrTutorialPhaseText(m_pImageTutorialHit,0,STPTKIND_NOTSTART),},
		//ミッション(0,0)
		{StrTutorialPhaseText(0,0),},
		//的
		{StrTutorialPhaseText(m_pImageTutorialTarget,0,STPTKIND_NOTSTART),},
		//ミッション(0,0)
		{StrTutorialPhaseText(0,0),},
		//爆弾ボール
		{StrTutorialPhaseText(m_pImageTutorialBoom,0,STPTKIND_NOTSTART),},
		//ミッション(0,0)
		{StrTutorialPhaseText(0,0),},
		//スキル
		{StrTutorialPhaseText(m_pImageTutorialSkill,0,STPTKIND_NOTSTART),},
		//ミッション(0,0)
		{StrTutorialPhaseText(0,0),},
		//スキル編成
		{StrTutorialPhaseText(m_pImageTutorialSetSkill,0,STPTKIND_START),},
	};

	//フェーズテキストのステータスを格納
	for (int i = 0; i < TutorialPhaseArrNum; i++)
	{
		for (int j = 0; j < TutorialPhaseTextArr[i].size(); j++) {
			TutorialPhaseArr[i].PhaseTextArray.push_back(TutorialPhaseTextArr[i][j]);
		}
	}

}
//============================================================================
//
//   チュートリアルテキスト
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//
//============================================================================
void CBackForeProc::TutorialText()
{
	//説明文のタイトル
	TCHAR PName[][20] = {
_T("チュートリアル"),
_T("ルール"),
_T("UI"),
_T("プレイヤーの移動"),
_T("ボール"),
_T("的"),
_T("爆弾ボール"),
_T("スキル"),

	};

	DWORD	PhaseNum = m_pGMain->m_dPhase;				//チュートリアルフェーズの番号取得
	TutorialPhaseDisKinds(TutorialPhaseArr[PhaseNum]);	//チュートリアルの表示
	

}
//============================================================================
//
//	 チュートリアルフェーズの種類
//
//	StrTutorialPhase		TutorialPhase	チュートリアルフェーズの構造体
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//============================================================================

void CBackForeProc::TutorialPhaseDisKinds(StrTutorialPhase TutorialPhase)
{

	if (TutorialPhase.Kinds == STPKIND_TEXT)
	{
		m_pSprite->Draw(m_pBackImage, 0, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, 0.5f);		//説明以外の画面を暗くする
		TutorialPhaseTextDisKinds(TutorialPhase.PhaseTextArray[TutorialPhaseTextNo]);		//チュートリアルフェーズテキストの表示
	}
	if (TutorialPhase.Kinds == STPKIND_MISION)
	{
		TutorialMisionText();				//チュートリアルミッションテキストの表示
	}
}

//============================================================================
//
//	 チュートリアルフェーズテキストの種類
//
//	StrTutorialPhase		TutorialPhase	チュートリアルフェーズテキストの構造体
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//
//============================================================================

void CBackForeProc::TutorialPhaseTextDisKinds(StrTutorialPhaseText TutorialPhaseText)
{
	const int FreamWidth = 1366;					//説明枠の横幅最大値
	const int FreamHeight = 768;					//説明枠の縦幅最大値

	const int FreamWidthUP = FreamWidth / 10;			//説明枠の横に広がり
	const int FreamHeightUP = FreamHeight / 10;		//説明枠の縦に広がり

	int	CurrentWidthFreamSize = FreamWidthUP * m_nCntTime;		//現在の説明枠の横幅
	int	CurrentHeightFreamSize = FreamHeightUP * m_nCntTime;	//現在の説明枠の縦幅

	int	CurrentWidthFreamPos;						//現在の説明枠の横位置
	int	CurrentHeightFreamPos;						//現在の説明枠の縦位置

	//徐々に説明枠が大きくなるようにする処理（最大値までは大きくならない）
	if ((FreamWidthUP*m_nCntTime) >= FreamWidth && (FreamHeightUP*m_nCntTime) >= FreamHeight)
	{
		CurrentWidthFreamSize = FreamWidth;
		CurrentHeightFreamSize = FreamHeight;

	}
	//大きくしたときに位置の調整
	CurrentWidthFreamPos = (WINDOW_WIDTH / 2) - (CurrentWidthFreamSize / 2);
	CurrentHeightFreamPos = (WINDOW_HEIGHT / 2) - (CurrentHeightFreamSize / 2);

	//テキストのみ(STPTKIND_TEXT)
	if (TutorialPhaseText.Kinds== STPTKIND_TEXT)
	{
		TutolialTextOnlySentence(CurrentWidthFreamPos, CurrentHeightFreamPos, FreamWidth, FreamHeight, CurrentWidthFreamSize, CurrentHeightFreamSize);
		if ((FreamWidthUP*m_nCntTime) >= FreamWidth && (FreamHeightUP*m_nCntTime) >= FreamHeight)		//説明欄が最大値になった時
		{
			TutorialTextDisplay();
		}

	}
	//写真付き(STPTKIND_DRAW)
	if (TutorialPhaseText.Kinds== STPTKIND_DRAW)
	{
		TutolialTextOnlySentence(CurrentWidthFreamPos, CurrentHeightFreamPos, FreamWidth, FreamHeight, CurrentWidthFreamSize, CurrentHeightFreamSize);
		if ((FreamWidthUP*m_nCntTime) >= FreamWidth && (FreamHeightUP*m_nCntTime) >= FreamHeight)																//説明欄が最大値になった時
		{
			if (PhaseTextNum == nPhaseNumAll + 1)m_pSprite->Draw(m_pImageTutorialUI, 0, 0, 0, 0, FreamWidth, FreamHeight, FreamWidth, FreamHeight, 1.0f);		//イメージ写真の表示
			else if (PhaseTextNum != nPhaseNumAll)
			{
				m_pSprite->Draw(TutorialPhaseText.pImage, 0, 0, 0, 0, FreamWidth, FreamHeight, FreamWidth, FreamHeight, 1.0f);									//イメージ写真の表示
			}
			TutorialTextDisplay();

		}

	}
	//表示時以外の写真付き(STPTKIND_NOTSTART)
	if (TutorialPhaseText.Kinds == STPTKIND_NOTSTART)
	{
		TutolialTextMisionSentence(CurrentWidthFreamPos, CurrentHeightFreamPos, FreamWidth, FreamHeight, CurrentWidthFreamSize, CurrentHeightFreamSize);
		if ((FreamWidthUP*m_nCntTime) >= FreamWidth && (FreamHeightUP*m_nCntTime) >= FreamHeight)																//説明欄が最大値になった時
		{
			if (PhaseTextNum != nPhaseNumAll)m_pSprite->Draw(TutorialPhaseText.pImage, 0, 0, 0, 0, FreamWidth, FreamHeight, FreamWidth, FreamHeight, 1.0f);		//イメージ写真の表示
			TutorialTextDisplay();

		}

	}
	//表示時からの写真付き(STPTKIND_NOTSTART)
	if (TutorialPhaseText.Kinds == STPTKIND_START)
	{
		TutolialTextMisionSentence(CurrentWidthFreamPos, CurrentHeightFreamPos, FreamWidth, FreamHeight, CurrentWidthFreamSize, CurrentHeightFreamSize);
		if ((FreamWidthUP*m_nCntTime) >= FreamWidth && (FreamHeightUP*m_nCntTime) >= FreamHeight)																//説明欄が最大値になった時
		{
			m_pSprite->Draw(TutorialPhaseText.pImage, 0, 0, 0, 0, FreamWidth, FreamHeight, FreamWidth, FreamHeight, 1.0f);										//イメージ写真の表示
			TutorialTextDisplay();

		}

	}

}

//============================================================================
//
//   チュートリアルテキスト説明だけ
//
//		const int		WidthFreamPos		説明欄表示位置の左上　X座標
//		const int		HeightFreamPos		説明欄表示位置の左上　Y座標
//		const int		FreamWidth			説明欄パターンの幅
//		const int		FreamHeight			説明欄パターンの高さ
//		const int		WidthFreamSize		説明欄表示の幅
//		const int		HeightFreamSize		説明欄表示の高さ
//
//
//============================================================================
void CBackForeProc::TutolialTextOnlySentence(const int WidthFreamPos,const int HeightFreamPos,const int FreamWidth,const int FreamHeight,const int WidthFreamSize,const int HeightFreamSize)
{
	//テキストの枠表示
	m_pSprite->Draw(m_pImageExplanationFrame, WidthFreamPos, HeightFreamPos, 0, 0, FreamWidth, FreamHeight, WidthFreamSize, HeightFreamSize, 1.0f);

	if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))		//クリックするとテキスト文を次に進める
	{
		PhaseTextNum++;
	}

	if (PhaseTextNum > PhaseNum[pNameNum] + nPhaseNumAll) {		//次のフェーズに移行
		TutorialTextSentenceEnd();
	}
	m_nCntTime++;


};

//============================================================================
//
//   チュートリアルテキスト説明後ミッション開始
//
//		const int		WidthFreamPos		説明欄表示位置の左上　X座標
//		const int		HeightFreamPos		説明欄表示位置の左上　Y座標
//		const int		FreamWidth			説明欄パターンの幅
//		const int		FreamHeight			説明欄パターンの高さ
//		const int		WidthFreamSize		説明欄表示の幅
//		const int		HeightFreamSize		説明欄表示の高さ
//
//
//============================================================================
void CBackForeProc::TutolialTextMisionSentence(const int WidthFreamPos, const int HeightFreamPos, const int FreamWidth, const int FreamHeight, const int WidthFreamSize, const int HeightFreamSize)
{
	//テキストの枠表示
	m_pSprite->Draw(m_pImageExplanationFrame, WidthFreamPos, HeightFreamPos, 0, 0, FreamWidth, FreamHeight, WidthFreamSize, HeightFreamSize, 1.0f);

	if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
	{
		PhaseTextNum++;
	}
	if (PhaseTextNum > PhaseNum[pNameNum] + nPhaseNumAll) {		//次のフェーズに移行
		if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
		{
			TutorialTextExplanationEnd();
		}
	}

	m_nCntTime++;

};


//============================================================================
//
//   チュートリアルテキスト変数の初期化
//
//
//============================================================================
void CBackForeProc::TutorialTextInit()
{
	PhaseTextNum=0;
	pNameNo=0;
	nPhaseNumAll=0;
	TutorialPhaseTextNo=0;
	pNameNum=0;
	dwQueastTextNum = -1;

	//配列初期化
	int ArrSize = TutorialPhaseArr.size();
	if (ArrSize > 0) {
		for (int i = 0; i < ArrSize; i++)
		{
			TutorialPhaseArr[i].PhaseTextArray.clear();
			TutorialPhaseArr[i].PhaseTextArray.shrink_to_fit();
		}
		TutorialPhaseArr.clear();
		TutorialPhaseArr.shrink_to_fit();
	}

}

//============================================================================
//
//   テキストフェーズのテキスト文が終わった時次のフェーズにする
//
//
//============================================================================
void CBackForeProc::TutorialTextSentenceEnd()
{

	if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	
	{
		m_nCntTime = 0;
		pNameNo++;
		nPhaseNumAll = PhaseTextNum;
		TutorialPhaseTextNo++;
		pNameNum++;
	}


};

//============================================================================
//
//   テキストフェーズのテキスト文が終わった時次のフェーズにする（クリア条件付けるとき）
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//
//============================================================================
void CBackForeProc::TutorialTextExplanationEnd()
{

	if (m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	
	{
		m_pGMain->m_dPhase++;			//全体のフェーズを進める
		pNameNo++;						//説明文のタイトルの番号を進める
		nPhaseNumAll = PhaseTextNum;	//現在までのテキスト分を更新
		TutorialPhaseTextNo = 0;		//トータルフェイズの中のテキストのフェーズをリセット
		pNameNum++;						//説明文のタイトル数を増やす
		m_nCntTime = 0;					//カウントをリセット
		dwQueastTextNum++;				//クリア条件の表示ナンバー
	}


};

//============================================================================
//
//   チュートリアルミッションのテキスト表示
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//
//============================================================================
void CBackForeProc::TutorialMisionText()
{
	const int TitleBackPosX = 0;		//ミッションタイトルのパターン位置X
	const int TitleBackPosY = 0;		//ミッションタイトルのパターン位置Y
	const int TitleBackWidth = 190;		//ミッションタイトルのパターン幅
	const int TitleBackHeight = 30;		//ミッションタイトルのパターン高さ
	const int TextBackPosX = 0;			//ミッション背景のパターン位置X
	const int TextBackPosY = 53;		//ミッション背景のパターン位置Y
	const int TextBackWidth = 380;		//ミッション背景のパターン幅
	const int TextBackHeight = 190;		//ミッション背景のパターン高さ
	int TextBackHeightUp = 0;			//ミッションテキストの行数

	int	TextFontSize = 20;				//ミッションテキスト文字のサイズ

	const int	BackPosX = 30, BackPosY = 120;		//表示位置
	const int	TitlePosX = 43, TitlePosY = 122;		//タイトル表示位置
	const int	TitleBackSize = 30;					//タイトル表示サイズ

	for (int i = 0; PhaseQueastText[dwQueastTextNum][i][0] != '\0'; i++) {		//テキストの背景のサイズを文字に合わせる
		TextBackHeightUp = (i * TextFontSize) + 70;
	}
	m_pSprite->Draw(m_pQuestTextBack, BackPosX, BackPosY + (TitleBackHeight), TextBackPosX, TextBackPosY, TextBackWidth, TextBackHeight, TextBackWidth, TextBackHeightUp, 1.0f);		//ミッション背景の表示
	m_pSprite->Draw(m_pQuestTextBack, BackPosX, BackPosY, TitleBackPosX, TitleBackPosY, TitleBackWidth, TitleBackHeight, TitleBackWidth + 50, TitleBackHeight, 1.0f);					//ミッションタイトルの背景の表示
	m_pGMain->m_pFont->Draw(TitlePosX, TitlePosY, _T("TUTORIAL MISSION"), TitleBackSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));											//ミッションタイトルの表示

	for (int i = 0; PhaseQueastText[dwQueastTextNum][i][0] != '\0'; i++) {		//文字の表示	次の行の最初の文字がヌルになるまで検索する
		int	FontSize = 30;		//フォントサイズ
		int TextInterval = 20;	//行間
		const int TextPosX=50, TextPosY = 140;	//ミッションテキストの表示位置
		const int ClearPosX = TextBackWidth-8, ClearPosY = 120;	//ミッションテキストの表示位置
		const int ClearStartPosX = 0, ClearStartPosY = 435;	//ミッションテキストのパターン位置
		const int ClearStartWidth = 76, ClearStartHeight = 76;	//ミッションテキストのパターンサイズ
		const int ClearWidth = 76, ClearHeight = 76;	//ミッションテキストの表示サイズ

		m_pGMain->m_pFont->Draw(TextPosX, TextPosY + (TitleBackHeight) + (TextInterval * i), PhaseQueastText[dwQueastTextNum][i], FontSize, RGB(0, 0, 0), 1.0f, _T("メイリオ ボールド"));	//テキスト表示
		if (PhaseQueastText[dwQueastTextNum][i + 1][0] == '\0') {		//クリアの表示
			if (m_pGMain->m_pMapProc->GetPhaseClear() == TRUE)m_pSprite->Draw(m_pQuestTextBack, ClearPosX, ClearPosY, ClearStartPosX, ClearStartPosY, ClearStartWidth, ClearStartHeight, ClearWidth, ClearHeight, 1.0f);

		}
	}


};



//============================================================================
//
//   チュートリアルテキストの題表示
//
//--M.Kamei_Point
//--Point_TutolialDisplay
//
//============================================================================
void CBackForeProc::TutorialTextDisplay()
{
	//説明文のタイトル
	TCHAR PName[][20] = {
		_T("チュートリアル"),
		_T("ルール"),
		_T("UI"),
		_T("プレイヤーの移動"),
		_T("ボール"),
		_T("的"),
		_T("爆弾ボール"),
		_T("スキル"),
		_T("スキル"),

	};

		const int	PNamePosX = 130, PNamePosY = 80;	//タイトルの表示位置
		const int	PNameSize=50;						//タイトルの表示サイズ

		m_pGMain->m_pFont->Draw(PNamePosX, PNamePosY, PName[pNameNo], PNameSize, RGB(255, 128, 0), 1.0f, _T("メイリオ ボールド"));			//説明文のタイトル表示
		for (int i = 0; i < (sizeof(PhaseText) / sizeof(*PhaseText)); i++) {
			const int	FontSize = 30;						//文字サイズ
			const int	TextPosX = 330, TextPosY = 540;		//文字の表示位置
			m_pGMain->m_pFont->Draw(TextPosX, TextPosY + (FontSize * i), PhaseText[PhaseTextNum][i], FontSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));		//テキスト文の表示
		}





};

//------------------------------------------------------------------------
//
//	メインモードの背景
//
//------------------------------------------------------------------------
void CBackForeProc::MainModeBackFore()
{
	int Phase = m_pGMain->m_pMapProc->GetPhaseMap();
	int nCount = m_pGMain->m_pMapProc->GetCount();
	const int StartCount = 120;		//スタート時に待つ時間
	switch (Phase)
	{
	case 0:
		if (nCount >= StartCount) {
			MainModeStartCount();

		}
		break;
	case 1:
		break;
	case 2:
		MainModeEnd();
		break;

	default:
		break;
	}
};


//------------------------------------------------------------------------
//
//	メインモードのスタートカウント	
//
//
//------------------------------------------------------------------------
void CBackForeProc::MainModeStartCount()
{
	TCHAR str[256];
	DWORD	dwStartCountSize = 500;		//表示サイズ
	DWORD	dwStartCountPosX = (WINDOW_WIDTH / 2) - (dwStartCountSize / 2)-80, dwStartCountPosY = (WINDOW_HEIGHT / 2) - (dwStartCountSize / 2);	//表示位置
	int		nStartCountNum = 3 - ((m_pGMain->m_pMapProc->GetCount()-120)/60);	//表示する数字
	MATRIX4X4	mWorld = XMMatrixTranslation(dwStartCountPosX, dwStartCountPosY,0);
	if (nStartCountNum > 0) {	//カウントを表示
		_stprintf(str, _T("%3d"), nStartCountNum);
		m_pGMain->m_pFont->Draw(mWorld, str, dwStartCountSize, RGB(255, 255, 255), 1.0, _T("メイリオ ボールド"));
	}
	else if(nStartCountNum<=0) {	//スタートを表示
		dwStartCountPosX = dwStartCountPosX - 250;
		mWorld = XMMatrixTranslation(dwStartCountPosX, dwStartCountPosY, 0);
		m_pGMain->m_pFont->Draw(mWorld, _T("START"), dwStartCountSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));

	}
};
//------------------------------------------------------------------------
//
//	メインモードの終了	
//
//------------------------------------------------------------------------
void CBackForeProc::MainModeEnd()
{
	TCHAR str[256];		//表示サイズ
	DWORD	dwStartCountSize = 500;
	DWORD	dwStartCountPosX = (WINDOW_WIDTH / 2) - (dwStartCountSize / 2) - 80, dwStartCountPosY = (WINDOW_HEIGHT / 2) - (dwStartCountSize / 2);	//表示位置

	m_pGMain->m_pFont->Draw(dwStartCountPosX, dwStartCountPosY, _T("終了"), dwStartCountSize, RGB(255, 255, 255), 1.0f, _T("メイリオ ボールド"));

};
//------------------------------------------------------------------------
//
//	マルチモードの更新	
//
//
//------------------------------------------------------------------------
void CBackForeProc::MultiUpdate()
{
	//１プレイヤーの処理
	CPcObj* pPcObj = m_pGMain->m_pPcProc->GetPcObjPtr();
	CWeaponSwordObj* pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr();
	int DestX = 0;					//１画面の左上X
	int DestY = WINDOW_HEIGHT/2;	//１画面の左上Y
	MultiUpdateConstruction(pPcObj, pWeaponObj, DestX, DestY);

	//２プレイヤーの処理
	pPcObj = m_pGMain->m_pPcProc->GetPcSecObjPtr();
	pWeaponObj = m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordSecObjPtr();
	DestX = 0;						//２画面の左上X
	DestY = WINDOW_HEIGHT;			//２画面の左上X
	MultiUpdateConstruction(pPcObj, pWeaponObj, DestX, DestY);
	
};

//============================================================================
//
//
//   マルチのスキル欄の更新と表示
//
//	CPcObj*				pPcObj	プレイヤーオブジェクト
//	CWeaponSwordObj*	pWeaponObj	剣オブジェクト
//	int					DestX	画面の左上X
//	int					DestY	画面の左上Y
//
//============================================================================
void CBackForeProc::MultiUpdateConstruction(CPcObj* pPcObj, CWeaponSwordObj* pWeaponObj,int DestX, int DestY)
{
	const int nWidth = 258, nHeight = 258;			//元の大きさ
	const int nWidthScale = nWidth / 2;				//表示大きさ
	const int nHeightScale = nHeight / 2;			//表示大きさ
	const int WeaponSet = 1;						//スキルの数


	//スキル欄の枠
	const int nColumnWidth = 250, nColumnHeight = 250;	//パターンの大きさ
	const int nColumnWidthScale = nColumnWidth / 2, nColumnHeightScale = nColumnHeight / 2;		//表示大きさ

	//スキル欄の外枠
	const int nFreamWidth = 272, nFreamHeight = 272;	//パターンの大きさ
	const int nFreamWidthScale = nFreamWidth / 2, nFreamHeightScale = nFreamHeight / 2;		//表示大きさ
	const int nFreamDist = (nFreamHeight - nColumnHeight) / 2;	//スキル欄ごとの幅

	const int nFreamNormalStartX = 300, nFreamNormalStartY = 0;	//パターン左上(ノーマル)
	const int nFreamChoiceStartX = 0, nFreamChoiceStartY = 300;	//パターン左上(選択中)
	const int nFreamUseStartX = 300, nFreamUseStartY = 300;	//パターン左上(発動中)

	const int MultiDestX=10, MultiDestY=100;		//位置の調整

	float WaitTime[100];		//残りのクールタイム
	float WaitMaxTime[100];		//クールタイム最大値
	int		WeaponNo = pPcObj->GetWeaponNo();
	int		WeaponColuman = pPcObj->GetWeaponColuman() - 1;
	float	RemWaitTime[100];	//クールタイムの割合

	int	LineNum = (m_pGMain->m_pTitleProc->GetWeaponNum() / 5) + 1;		//スキルの選択欄の行の数

	for (int i = 0; i < WeaponSet; i++)
	{

		WaitMaxTime[i] = pWeaponObj->GetWeaponMaxWaitTime(i);
		WaitTime[i] = pWeaponObj->GetWeaponWaitTime(i);		//それぞれのスキルのクールタイムを取得
		RemWaitTime[i] = WaitTime[i] / WaitMaxTime[i];
		if (WaitTime[i] > 0) {
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY + ((nHeightScale*(RemWaitTime[i]))), 0, nHeight*(RemWaitTime[i]), nColumnWidth, nColumnHeight*(1 - RemWaitTime[i]), nWidthScale, nHeightScale*(1 - RemWaitTime[i]));		//クールタイム中の表示
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, 0, 0, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale, 0.5);		//クールタイム中の表示
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, nFreamNormalStartX, nFreamNormalStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);

		}
		else if (pPcObj->GetSkillActive(i) == TRUE) {			//スキル発動中
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, 0, 0, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale);
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, nFreamUseStartX, nFreamUseStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);


		}
		else if (WeaponColuman == i) {						//選択中のスキル欄を枠付きにする
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, 0, 0, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale);
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, nFreamChoiceStartX, nFreamChoiceStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);

		}
		else {
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, 0, 0, nColumnWidth, nColumnHeight, nWidthScale, nHeightScale);
			m_pSprite->Draw(m_pImageConstruction, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, nFreamNormalStartX, nFreamNormalStartY, nFreamWidth, nFreamHeight, nWidthScale, nHeightScale);

		}


		DWORD WeaponSelectNo= pPcObj->GetWeaponColumanNo(i);
		int y = (WeaponSelectNo - 1) / 5;
		int x = 0;
		//選択したスキルが選択欄のなん列目にあるか
		for (int j = 0; j < LineNum; j++)
		{
			if (((j + 1) * 5) > (WeaponSelectNo - 1))
			{

				x = (WeaponSelectNo - 1) - 5;
				if (x < 0) {
					x = (WeaponSelectNo - 1);
				}
				break;
			}
		}

		float	ReduceGage[100];
		ReduceGage[i] = WaitTime[i] / WaitMaxTime[i];
		ReduceGage[i] = (nHeight * (1 + y)) * ReduceGage[i];
		ReduceGage[i] = (nHeight * (1 + y)) - ReduceGage[i];
		ReduceGage[i] = ReduceGage[i] / (1 + y);
		if (WeaponSelectNo != NULL) {		//スキルがセットされたときにスキルを表示
			if (WaitTime[i] > 0) {
				m_pSprite->Draw(m_pImageWeapon, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY + ((nHeightScale*(RemWaitTime[i]))), nWidth*x, ((nHeight*(y + 1)) - (ReduceGage[i])), nWidth, (nHeight*(1 - RemWaitTime[i])), nWidthScale, nHeightScale*(1 - RemWaitTime[i]));		//クールタイム中の表示
				m_pSprite->Draw(m_pImageWeapon, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, nWidth*x, nHeight*y, nWidth, nHeight, nWidthScale, nHeightScale, 0.5);		//クールタイム中の表示	

			}
			else {
				m_pSprite->Draw(m_pImageWeapon, DestX + MultiDestX + (nWidthScale + MultiDestX)*i, DestY - nHeight + MultiDestY, nWidth*x, nHeight*y, nWidth, nHeight, nWidthScale, nHeightScale);
			}
		}

	}

}

//------------------------------------------------------------------------
//	マルチモードの更新	
//
//
//------------------------------------------------------------------------
void CBackForeProc::MultiUpdateScore()
{
	//１プレイヤーの処理
	int nScoreImagePosX = 0, nScoreImagePosY = 45;	//スコアのイメージ表示位置
	int nScoreTextPosX = 10, nScoreTextPosY = 8;	//スコアのテキスト表示位置
	int nScorePointPosX = 0, nScorePointPosY = 55;	//スコアのポイント位置
	UpdateScore(nScoreImagePosX, nScoreImagePosY, nScoreTextPosX, nScoreTextPosY, nScorePointPosX, nScorePointPosY, m_pGMain->m_nScore);	//スコアの表示処理

	//２プレイヤーの処理
	int nWinHeight = WINDOW_HEIGHT / 2;
	nScoreImagePosX = 0,nScoreImagePosY = 45+ nWinHeight;
	nScoreTextPosX = 10, nScoreTextPosY = 8+ nWinHeight;
	nScorePointPosX = 0, nScorePointPosY = 55+ nWinHeight;
	UpdateScore(nScoreImagePosX, nScoreImagePosY, nScoreTextPosX, nScoreTextPosY, nScorePointPosX, nScorePointPosY, m_pGMain->m_nScoreSec);

};


//------------------------------------------------------------------------------
//CSVファイルのエクセルを読み込み
//
//
//------------------------------------------------------------------------------

void CBackForeProc::FileTextRead()
{
	char fname[30] = "Data/Read/PhaseText.csv";
	fopen_s(&fp, fname, "r"); // ファイルを開く。失敗するとNULLを返す。
	int i = 0;
	int j = 0;
	bool check = false;
	int Text_count = 0;
	int Sentence_count = 0;
	int Column = 0;
	int	Line = 0;
	char chr[100][100] = { '\0' };
	char chr2;

	while ((chr2 = fgetc(fp)) != EOF) {
		if (chr2 == '"') {
			if (check != true) check = true;
			else if (check != false) check = false;
		}
		if (j == 0 && (chr2 == ','|| chr2 == '\n')&& check != true)
		{
			if (chr2 == '\n')	// エクセルの行を変えて読み込み（列の数が最大値に満たしてない行が改行した時）
			{
				PhaseNum[Column] = (Line-1);
				Column++;
				Line = 0;

			}
			i++;
			j = 0;
			Sentence_count = 0;

		}
		else if (chr2 == ',') {
			chr[i][j] = '\0';
			//printf("%s", chr[i]);
			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, PhaseText[Text_count][Sentence_count], (sizeof PhaseText) / 2);
			Text_count++;
			i++;
			j = 0;
			Sentence_count = 0;
			Line++;
		}
		else if (check != true && chr2 == '\n') {		//エクセルの行を変えて読み込み
			chr[i][j] = '\0';
			//printf("%s", chr[i]);
			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, PhaseText[Text_count][Sentence_count], (sizeof PhaseText[Text_count][Sentence_count]) / 2);
			PhaseNum[Column] = Line;
			Column++;
			Line = 0;
			Text_count++;
			i++;
			j = 0;
			Sentence_count = 0;
		}
		else if (check != false && chr2 == '\n') {		//セル内で改行

			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, PhaseText[Text_count][Sentence_count], (sizeof PhaseText[Text_count][Sentence_count]) / 2);
			Sentence_count++;
			memset(chr[i], '\0', sizeof(chr[i]));
			j = 0;
		}
		else {
			//printf("%c", chr2);
			if (chr2 == '"') {

			}
			else {
				chr[i][j] = chr2;
				j++;
			}
		}
	}

	fclose(fp); // ファイルを閉じる


	//--------------------------------------------------------------------------

	char fname2[30] = "Data/Read/PhaseQueastText.csv";
	fopen_s(&fp, fname2, "r"); // ファイルを開く。失敗するとNULLを返す。
	i = 0;
	j = 0;
	check = false;
	Text_count = 0;
	Sentence_count = 0;
	Column = 0;
	Line = 0;
	chr[100][100] = { '\0' };
	chr2='\0';

	while ((chr2 = fgetc(fp)) != EOF) {
		if (chr2 == '"') {
			if (check != true) check = true;
			else if (check != false) check = false;
		}
		if (j == 0 && (chr2 == ',' || chr2 == '\n') && check != true)
		{
			if (chr2 == '\n')	// エクセルの行を変えて読み込み（列の数が最大値に満たしてない行が改行した時）
			{
				PhaseQueastNum[Column] = (Line - 1);
				Column++;
				Line = 0;

			}
			i++;
			j = 0;
			Sentence_count = 0;

		}
		else if (chr2 == ',') {
			chr[i][j] = '\0';
			//printf("%s", chr[i]);
			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, PhaseText[Text_count][Sentence_count], (sizeof PhaseQueastText) / 2);
			Text_count++;
			i++;
			j = 0;
			Sentence_count = 0;
			Line++;
		}
		else if (check != true && chr2 == '\n') {		//エクセルの行を変えて読み込み
			chr[i][j] = '\0';
			//printf("%s", chr[i]);
			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, PhaseQueastText[Text_count][Sentence_count], (sizeof PhaseQueastText[Text_count][Sentence_count]) / 2);
			PhaseQueastNum[Column] = Line;
			Column++;
			Line = 0;
			Text_count++;
			i++;
			j = 0;
			Sentence_count = 0;
		}
		else if (check != false && chr2 == '\n') {		//セル内で改行

			MultiByteToWideChar(CP_ACP, 0, chr[i], -1, PhaseQueastText[Text_count][Sentence_count], (sizeof PhaseQueastText[Text_count][Sentence_count]) / 2);
			Sentence_count++;
			memset(chr[i], '\0', sizeof(chr[i]));
			j = 0;
		}
		else {
			//printf("%c", chr2);
			if (chr2 == '"') {

			}
			else {
				chr[i][j] = chr2;
				j++;
			}
		}
	}

	fclose(fp); // ファイルを閉じる


}
