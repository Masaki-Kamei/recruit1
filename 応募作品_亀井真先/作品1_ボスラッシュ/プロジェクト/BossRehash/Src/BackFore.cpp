//=============================================================================
//
//		前景・後景処理
//																BackFore.cpp
//=============================================================================

#include "GameMain.h"
#include "Playchar.h"
#include "BackFore.h"


// ========================================================================================
//
// 前景の処理
//
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	前景プロシージャのコンストラクタ	
//
//  引数　CGameMain* pGMain
//
//------------------------------------------------------------------------
CForeProc::CForeProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;

	m_pForegrd = new CSprite(m_pGMain->m_pShader);
}
// ---------------------------------------------------------------------------
//
// 前景プロシージャのデストラクタ
//
// ---------------------------------------------------------------------------
CForeProc::~CForeProc()
{
	SAFE_DELETE(m_pForegrd);
}
//-----------------------------------------------------------------------------
// 前景プロシージャの更新
//
//   引数　　　なし
//-----------------------------------------------------------------------------
void	CForeProc::Update()
{
	CSpriteImage* pImageFore = m_pGMain->m_pImageSprite; // すでに読み込んであるスプライトイメージを使用する
	CSpriteImage* pImageFore2 = m_pGMain->m_pImageSprite2; // すでに読み込んであるスプライトイメージを使用する
	CSpriteImage* pImageFore3 = m_pGMain->m_pImageSprite4; // すでに読み込んであるスプライトイメージを使用する



	// ステータスバーの表示
	float h = (float)m_pGMain->m_pPcProc->GetPcObjPtr()->GetHp() / m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaxHp();
	if (h < 0) h = 0;
	float m = (float)m_pGMain->m_nEnmHpSave/ m_pGMain->m_nEnmHpMaxSave;
	if (m < 0) m = 0;



	m_pForegrd->Draw(pImageFore, 40, 10,  0, 432, 240, 18);
	m_pForegrd->Draw(pImageFore, 108, 14, 68, 470, (int)(166 * h), 10);

	m_pForegrd->Draw(pImageFore, WINDOW_WIDTH - 300, 10, 0, 432, 240, 18);
	m_pForegrd->Draw(pImageFore, WINDOW_WIDTH - 300 + 68, 14, 68, 470, (int)(166 * m), 10);


	m_pForegrd->Draw(pImageFore3, 110, 30, 68, 380, 22, 22);
	if (m_pGMain->m_nChangeWeapon == 0) 
		m_pForegrd->Draw(pImageFore, 109, 29, 198, 379, 24, 24);
	

	m_pForegrd->Draw(pImageFore, 136, 30, 94, 380, 22, 22);
	if (m_pGMain->m_nChangeWeapon == 1)
	m_pForegrd->Draw(pImageFore, 135, 29, 198, 379, 24, 24);
	if(m_pGMain->m_nUnLookWeapon[0] !=1)
	m_pForegrd->Draw(pImageFore, 136, 30, 43, 381, 20, 20);


	m_pForegrd->Draw(pImageFore, 160, 30, 120, 380, 22, 22);
	if (m_pGMain->m_nChangeWeapon == 2)
	m_pForegrd->Draw(pImageFore, 159, 29, 198, 379, 24, 24);
	if (m_pGMain->m_nUnLookWeapon[1] != 1)
	m_pForegrd->Draw(pImageFore, 160, 30, 43, 381, 20, 20);


	m_pForegrd->Draw(pImageFore, 186, 30, 146, 380, 22, 22);
	if (m_pGMain->m_nChangeWeapon == 3)
	m_pForegrd->Draw(pImageFore, 185, 29, 198, 379, 24, 24);
	if (m_pGMain->m_nUnLookWeapon[2] != 1)
	m_pForegrd->Draw(pImageFore, 186, 30, 43, 381, 20, 20);


	m_pForegrd->Draw(pImageFore, 212, 30, 172, 380, 22, 22);
	if (m_pGMain->m_nChangeWeapon == 4)
	m_pForegrd->Draw(pImageFore, 211, 29, 198, 379, 24, 24);
	if (m_pGMain->m_nUnLookWeapon[3] != 1)
	m_pForegrd->Draw(pImageFore, 212, 30, 43, 381, 20, 20);

	if(m_pGMain->m_nHeelNum>0)
	m_pForegrd->Draw(pImageFore2, 105, 60, 227, 388, 27, 24);
	if (m_pGMain->m_nHeelNum > 1)
		m_pForegrd->Draw(pImageFore2, 134, 60, 227, 388, 27, 24);
	if (m_pGMain->m_nHeelNum > 2)
		m_pForegrd->Draw(pImageFore2, 163, 60, 227, 388, 27, 24);
	if (m_pGMain->m_nHeelNum > 3)
		m_pForegrd->Draw(pImageFore2, 192, 60, 227, 388, 27, 24);
	if (m_pGMain->m_nHeelNum > 4)
		m_pForegrd->Draw(pImageFore2, 221, 60, 227, 388, 27, 24);




	

	// ＨＰとＭＰの表示
	TCHAR str[256];
	_stprintf(str, _T("%06d"), m_pGMain->m_pPcProc->GetPcObjPtr()->GetHp());
	m_pGMain->m_pFont->Draw(64, 14, str, 12, RGB(0, 0, 0));


	_stprintf(str, _T("%06d"), m_pGMain->m_nEnmHpSave);
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH - 300 + 24, 14, str, 12, RGB(0, 0, 0));

}


