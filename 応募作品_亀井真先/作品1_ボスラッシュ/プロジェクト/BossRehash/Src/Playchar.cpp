//=============================================================================
//
//		�v���C�L�����N�^�[�̏���
//																Playchar.cpp
//=============================================================================

#include "Playchar.h"
#include "Weapon.h"
#include "Effect.h"
#include "Map.h"
#include "GameMain.h"


//------------------------------------------------------------------------
//
//	�o�b�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CPcProc::CPcProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pPcObj = new CPcObj(m_pGMain);
	m_pObjArray.push_back(m_pPcObj);  // m_pObjArray�ɃI�u�W�F�N�g��o�^����

	m_nPcNum = 2;
}

// ===========================================================================
//------------------------------------------------------------------------
//
//	�o�b�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@CGameMain* pGMain
//
//------------------------------------------------------------------------
CPcObj::CPcObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 96, 0, 48, 48);
	m_vPos = VECTOR2(48, 721);

	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_nDirIdx = DOWN;
	m_nHp = m_nMaxHp = 3000;
	m_nMaxMp = 3000;
	m_nMp = 0;
	m_nAtc = 300;

	m_nShotWait = 0;
	m_nDifShotWait = 0;
	m_nProAtkWait=0;
	m_nCharShotWait = 0;
	m_nProAtkTime = 0;


	m_pGMain->m_nHeelNum = m_pGMain->m_nHeelMaxNum+1;
}
// ---------------------------------------------------------------------------
//
// �o�b�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CPcObj::~CPcObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// �o�b�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CPcObj::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	CMapLine*  pHitmapline = NULL;
	float fSpeed     = 5;
	float fJumpPlus  = 4;

	if (!m_bActive) return;

	m_vPosUp = VECTOR2(0, 0);

	if (m_pGMain->m_nMapChange == 1) {

	}
	
	
	switch (m_dwStatus)
	{
		case  FLASH:
				m_nCnt1--;
				if (m_nCnt1 <= 0) {
					ResetStatus();
					ResetAnim();
				}
				else {
					FlashCountup();
				}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
		case  NORMAL:

			m_pGMain->m_nPcpositionx = m_vPos.x;
			m_pGMain->m_nPcpositiony = m_vPos.y;

			if (m_pGMain->m_nSpLastTrigger == 1) {
				m_vPosUp.x = -3;
			}
			else if (m_pGMain->m_nSpLastTrigger == 2) {
				m_vPosUp.x = 3;

			}

				break;

		case DAMAGE:
				if (m_pOtherObj->GetAtc() > 0)
				{
					m_nHp -= m_pOtherObj->GetAtc();	// �U�����󂯂��_���[�W
					if (m_nHp <= 0)
					{
						m_nHp = 0;
						m_dwStatus = DEAD;		// HP���O�Ȃ̂Ŏ��S��
						m_nCnt1 = 180;			// ���S�t���b�V�����̎��Ԑݒ�
					}
					else {
						m_dwStatus = FLASH;
						m_nCnt1 = 60;
					}
				}
				else {
					m_dwStatus = NORMAL;  // �U���͂Ȃ��̂Ƃ��͂�����NORMAL�ɖ߂�
				}
				break;

		case DEAD:
				m_nCnt1--;
				if (m_nCnt1 <= 0)
				{
						m_pGMain->m_dwGameStatus = GAMEOVER;
					
				}
				else {
					FlashCountup();
				}
				break;

	}

	switch (m_dwStatusSub)
	{
		case  WALK:		// ���s���̏���


			if (pDI->CheckKey(KD_DAT, DIK_RIGHT) || pDI->CheckJoy(KD_DAT, DIJ_RIGHT))//���L�[
			{
				if (m_pGMain->m_nShieldStop == 0)
				{
					if (m_pGMain->m_nSpLastTrigger == 1) {
						m_vPosUp.x = 1;
						m_nDirIdx = RIGHT;

					}
					else if (m_pGMain->m_nSpLastTrigger == 2) {
						m_vPosUp.x = 8;
						m_nDirIdx = RIGHT;

					}
					else {
						m_vPosUp.x = fSpeed;
						m_nDirIdx = RIGHT;
						m_pGMain->m_nDirection = 0;
					}
				}
			}
			if (pDI->CheckKey(KD_DAT, DIK_LEFT) || pDI->CheckJoy(KD_DAT, DIJ_LEFT))//���L�[
			{
				if (m_pGMain->m_nShieldStop == 0)
				{
					if (m_pGMain->m_nSpLastTrigger == 1) {
						m_vPosUp.x = -8;
						m_nDirIdx = LEFT;

					}
					else if (m_pGMain->m_nSpLastTrigger == 2) {
						m_vPosUp.x = -1;
						m_nDirIdx = LEFT;

					}
					else {


						m_vPosUp.x = -fSpeed;
						m_nDirIdx = LEFT;
						m_pGMain->m_nDirection = 1;
					}
					
				}
				
			}
			if (pDI->CheckKey(KD_TRG, DIK_UP) || pDI->CheckJoy(KD_DAT, DIJ_UP)) //	���L�[
			{	// �W�����v�J�n
				if (m_pGMain->m_nShieldStop == 0)
				{
					m_dwStatusSub = JUMP;
					m_vJumpSpeed.x = m_vPosUp.x;
					m_vJumpSpeed.y = -(fSpeed*2.5 + fJumpPlus);
					m_fJumpTime = 0;
					m_vPosUp.y = m_vJumpSpeed.y;
					//m_nDirIdx = UP;
				}
			}
			else {// ���R����
				if (pDI->CheckKey(KD_DAT, DIK_DOWN) || pDI->CheckJoy(KD_DAT, DIJ_DOWN))//���L�[
				{
					//m_vPosUp.y = fSpeed;
					//m_nDirIdx = DOWN;



				}
				else {
					m_dwStatusSub = JUMP;
					m_vJumpSpeed.x = m_vPosUp.x;
					m_vJumpSpeed.y = fSpeed / 2;
					m_fJumpTime = 0;
					m_vPosUp.y = m_vJumpSpeed.y;
			
				}
			}
			break;

		case  JUMP:		// �W�����v���̏���
			if (pDI->CheckKey(KD_DAT, DIK_RIGHT) || pDI->CheckJoy(KD_DAT, DIJ_RIGHT))//���L�[
			{
				if (m_pGMain->m_nSpLastTrigger == 1) {
					m_vPosUp.x = -8;
				}
				else if (m_pGMain->m_nSpLastTrigger == 2) {
					m_vPosUp.x = 1;

				}
				else {

					m_vJumpSpeed.x = fSpeed;
					m_nDirIdx = RIGHT;
					m_pGMain->m_nDirection = 0;
				}
			}
			if (pDI->CheckKey(KD_DAT, DIK_LEFT) || pDI->CheckJoy(KD_DAT, DIJ_LEFT))//���L�[
			{
				if (m_pGMain->m_nSpLastTrigger == 1) {
					m_vPosUp.x = -1;
				}
				else if (m_pGMain->m_nSpLastTrigger == 2) {
					m_vPosUp.x = 8;

				}
				else {

					m_vJumpSpeed.x = -fSpeed;
					m_nDirIdx = LEFT;
					m_pGMain->m_nDirection = 1;
				}
			}
			m_fJumpTime++;
			m_vPosUp.x = m_vJumpSpeed.x;
			m_vPosUp.y = round(m_vJumpSpeed.y + GRAVITY*m_fJumpTime);
			break;

			
	}
	// 2�i�W�����v
	if (pDI->CheckKey(KD_TRG, DIK_UP) || pDI->CheckJoy(KD_DAT, DIJ_UP)) //	���L�[
	{	// 2�i�W�����v�J�n
		if (m_pGMain->m_nShieldStop == 0)
		{
			if (m_pGMain->m_nJumptwo <= 1) {
				m_pGMain->m_nJumptwo++;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = -(fSpeed*2.5 + fJumpPlus);
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
				//m_nDirIdx = UP;
			}
		}
	}

	//����ύX
	if (pDI->CheckKey(KD_TRG, DIK_1) || pDI->CheckJoy(KD_DAT, DIJ_A))
		m_pGMain->m_nChangeWeapon=0;
	if (pDI->CheckKey(KD_TRG, DIK_2) || pDI->CheckJoy(KD_DAT, DIJ_A))
		m_pGMain->m_nChangeWeapon = 1;
	if (pDI->CheckKey(KD_TRG, DIK_3) || pDI->CheckJoy(KD_DAT, DIJ_A))
		m_pGMain->m_nChangeWeapon = 2;
	if (pDI->CheckKey(KD_TRG, DIK_4) || pDI->CheckJoy(KD_DAT, DIJ_A)) {
		m_pGMain->m_nChangeWeapon = 3;
		m_pGMain->m_nCharAmountSave = 0;
		m_pGMain->m_nCharAmount = 0;
		m_pGMain->m_nCharStop = 0;
	}
	if (pDI->CheckKey(KD_TRG, DIK_5) || pDI->CheckJoy(KD_DAT, DIJ_A))
		m_pGMain->m_nChangeWeapon = 4;



	//�V���b�g
	if (m_pGMain->m_nChangeWeapon == 0) {
		if (pDI->CheckKey(KD_DAT, DIK_X) || pDI->CheckJoy(KD_DAT, DIJ_A))
		{

			if (m_nShotWait <= 0)
			{

				if (m_pGMain->m_nShieldStop == 0)
				{
					// �V���b�g�̔���
					m_pGMain->m_pWeaponProc->m_pWeaponShotProc->Start(m_vPos + VECTOR2(16, 16), this, PC);
					m_nShotWait = 30;    // ���픭�˂̃E�F�C�g���|����
				}
			}
		}
	}
	if (m_nShotWait > 0) m_nShotWait--;    // ���픭�˂̃E�F�C�g���J�E���g�_�E��

	//�g�U�V���b�g
	if (m_pGMain->m_nUnLookWeapon[0] == 1) {
		if (m_pGMain->m_nChangeWeapon == 1) {

			if (pDI->CheckKey(KD_DAT, DIK_X) || pDI->CheckJoy(KD_DAT, DIJ_A))
			{
				if (m_nDifShotWait <= 0)
				{
					if (m_pGMain->m_nShieldStop == 0)
					{
						// �g�U�V���b�g�̔���
						m_pGMain->m_pWeaponProc->m_pWeaponDifShotProc->Start(m_vPos + VECTOR2(16, 16), this, PC);


						m_nDifShotWait = 60;    // ���픭�˂̃E�F�C�g���|����
					}
				}
			}
		}
		if (m_nDifShotWait > 0) m_nDifShotWait--;    // ���픭�˂̃E�F�C�g���J�E���g�_�E��
	}

	//�V�[���h

	if (pDI->CheckKey(KD_DAT, DIK_DOWN) || pDI->CheckJoy(KD_DAT, DIJ_A))
	{
		m_pGMain->m_nShieldStop = 1;
			// �V�[���h�̔���
			m_pGMain->m_pWeaponProc->m_pWeaponShieldProc->Start(m_vPos + VECTOR2(16, 16), this, PC);
	}
	else if (pDI->CheckKey(KD_UTRG, DIK_DOWN) || pDI->CheckJoy(KD_DAT, DIJ_A)) {
		m_pGMain->m_nShieldStop = 0;
	}

	//���e
	if (m_pGMain->m_nUnLookWeapon[1] == 1) {
		if (m_pGMain->m_nChangeWeapon == 2) {
			if (pDI->CheckKey(KD_TRG, DIK_X) || pDI->CheckJoy(KD_TRG, DIJ_A))
			{

				if (m_nShotWait <= 0)
				{
					if (m_pGMain->m_nShieldStop == 0)
					{
						if (m_pGMain->m_nDirection == 0) {
							// ���e�̔���
							m_pGMain->m_pWeaponProc->m_pWeaponBoomProc->Start(m_vPos + VECTOR2(66, 16), this, PC);
						}
						else if (m_pGMain->m_nDirection == 1) {
							// ���e�̔���
							m_pGMain->m_pWeaponProc->m_pWeaponBoomProc->Start(m_vPos + VECTOR2(-34, 16), this, PC);
						}
					}
				}
			}
		}
	}
	//�ߋ����U��
	if(pDI->CheckKey(KD_DAT, DIK_X) || pDI->CheckJoy(KD_DAT, DIJ_A)){

	}
	else {
		if (pDI->CheckKey(KD_DAT, DIK_Y) || pDI->CheckJoy(KD_DAT, DIJ_A))
		{


			if (m_nProAtkWait <= 0)
			{
				//m_pGMain->m_nProAtkStop = 1;
				m_pGMain->m_pWeaponProc->m_pWeaponProAtkProc->Start(m_vPos + VECTOR2(16, 16), this, PC);
				m_pGMain->m_nProAtkStop = 1;

				m_nProAtkWait = 10;

			}



		}
	}
    if (m_nProAtkWait > 0)
		{
		//m_pGMain->m_nProAtkStop = 0;
		m_nProAtkWait--;
		}
	if (m_pGMain->m_nUnLookWeapon[2] == 1) {
		//�`���[�W�V���b�g
		if (m_pGMain->m_nChangeWeapon == 3) {
			if (pDI->CheckKey(KD_DAT, DIK_X) || pDI->CheckJoy(KD_DAT, DIJ_A))
			{

				if (m_pGMain->m_nShieldStop == 0) {
					if (m_nCharShotWait <= 0) {
						m_pGMain->m_nCharEnmhit = 0;
						if (m_pGMain->m_nCharStop == 0)
						{
							m_pGMain->m_nCharAmountSave = 0;


							m_pGMain->m_nCharAmount++;
							m_pGMain->m_nCharAmountSave = m_pGMain->m_nCharAmount;

							m_pGMain->m_pWeaponProc->m_pWeaponCharShotProc->Start(m_vPos + VECTOR2(16, 16), this, PC);
						}
					}

				}
				else {
					m_pGMain->m_nCharAmountSave = 0;
					m_pGMain->m_nCharAmount = 0;

				}

			}




			if (pDI->CheckKey(KD_UTRG, DIK_X) || pDI->CheckJoy(KD_UTRG, DIJ_A))
			{

				if (m_pGMain->m_nShieldStop == 0) {

					m_pGMain->m_nCharStop = 1;
					m_pGMain->m_nCharEnmhit = 1;
					if (m_nCharShotWait <= 0)
					{
						// �`���[�W�V���b�g�̔���

						m_pGMain->m_nCharAmount = 0;
						m_nCharShotWait = 10;
					}

				}
				else {
					m_pGMain->m_nCharAmountSave = 0;
					m_pGMain->m_nCharAmount = 0;

				}

			}
		}
		else if (m_pGMain->m_nCharAmountSave > 1)
		{
			if (m_pGMain->m_nShieldStop == 0) {

				m_pGMain->m_nCharStop = 1;
				m_pGMain->m_nCharEnmhit = 1;
				if (m_nCharShotWait <= 0)
				{
					// �`���[�W�V���b�g�̔���

					m_pGMain->m_nCharAmount = 0;
					m_nCharShotWait = 10;
				}

			}
			else {
				m_pGMain->m_nCharAmountSave = 0;
				m_pGMain->m_nCharAmount = 0;

			}

		}

		if (m_nCharShotWait > 0) m_nCharShotWait--;    // ���픭�˂̃E�F�C�g���J�E���g�_�E��

	}


	if (m_pGMain->m_nUnLookWeapon[3] == 1) {

	//�o�E���h�V���b�g
	if (m_pGMain->m_nChangeWeapon == 4) {
		if (pDI->CheckKey(KD_DAT, DIK_X) || pDI->CheckJoy(KD_DAT, DIJ_A))
		{

			if (m_nBoundShotWait <= 0)
			{

				if (m_pGMain->m_nShieldStop == 0)
				{
					// �V���b�g�̔���
					m_pGMain->m_pWeaponProc->m_pWeaponBoundShotProc->Start(m_vPos + VECTOR2(16, 16), this, PC);
					m_nBoundShotWait = 30;    // ���픭�˂̃E�F�C�g���|����
				}
			}
		}
	}
	if (m_nBoundShotWait > 0) m_nBoundShotWait--;    // ���픭�˂̃E�F�C�g���J�E���g�_�E��
	}

	if (pDI->CheckKey(KD_TRG, DIK_H) || pDI->CheckJoy(KD_DAT, DIJ_UP)) //	H�L�[
	{
		// ��
		if (m_pGMain->m_nHeelNum>0) {
			if (m_nHp < m_nMaxHp - 1700) {
				m_nHp += 1700;

			}
			else if (m_nHp >= m_nMaxHp - 1700) {
				m_nHp = m_nMaxHp;
			}
		}
		m_pGMain->m_nHeelNum--;

	}

	// �}�b�v���Ƃ̐ڐG����ƓK�؂Ȉʒu�ւ̈ړ�
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
		{
			m_dwStatusSub = WALK;	// �}�b�v���ɐڐG���Ă���Ƃ��́A�W�����v����s�ɖ߂�
			m_pGMain->m_nJumptwo = 0;
			m_fJumpTime = 0;
		}
	}

	// �����v�Z
	m_vPos += m_vPosUp;

	AnimCountup();
	Draw();

}
