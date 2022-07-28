//=============================================================================
//		  �}�b�v�̏���
//																	Map.cpp
//=============================================================================
#include  "BaseProc.h"
#include  "Map.h"
#include  "Playchar.h"
#include  "Enemy.h"
#include  "Weapon.h"
#include  "Title.h"
#include  "BackFore.h"


//=============================================================================
//
// �}�b�v�v���V�[�W���̃R���X�g���N�^
//
//-----------------------------------------------------------------------------
CMapProc::CMapProc(CGameMain*	pGMain)
{
	// �N���X�S�̂̃N�����[
	// (vector�N���X�͏������s�v)
	m_pGMain = pGMain;
	m_dwMapNo = 0;
	m_bActive = FALSE;
	m_pColMesh = NULL;					// �R���W�������b�V���ւ̃|�C���^
	m_nEvtIdx = 0;					
	nCount = 0;

}

//-----------------------------------------------------------------------------
//
// �}�b�v�v���V�[�W���̃f�X�g���N�^
//
//-----------------------------------------------------------------------------
CMapProc::~CMapProc()
{
	DestroyAll();
}

//-----------------------------------------------------------------------------
//
// �}�b�v�̍폜
//
//-----------------------------------------------------------------------------
void CMapProc::DestroyAll()
{
	m_dwMapNo = 0;
	m_bActive = FALSE;
	m_nEvtIdx = 0;				

	// ���b�V���̃f���[�g
	for (DWORD i = 0; i < m_SkyMap.size(); i++)
	{
		SAFE_DELETE(m_SkyMap[i].m_pMesh);
		SAFE_DELETE(m_SkyMap[i].m_pWave);    // �g�p���Ă��Ȃ����O�̂��ߍ폜
	}
	for (DWORD i = 0; i < m_StageMap.size(); i++)
	{
		SAFE_DELETE(m_StageMap[i].m_pMesh);
		SAFE_DELETE(m_StageMap[i].m_pWave);
	}
	for (DWORD i = 0; i < m_MoveMap.size(); i++)
	{
		SAFE_DELETE(m_MoveMap[i].m_pMesh);
		SAFE_DELETE(m_MoveMap[i].m_pColMesh);
	}
	for (DWORD i = 0; i < m_EventMap.size(); i++)  
	{
		SAFE_DELETE(m_EventMap[i].m_pBBox);
	}
	SAFE_DELETE(m_pColMesh);

	// vector�̍폜
	m_SkyMap.clear();					// ��̃}�b�v  �z��폜
	m_SkyMap.shrink_to_fit();			// ��̃}�b�v  �s�v���������
	m_StageMap.clear();					// �X�e�[�W�̃}�b�v  �z��폜
	m_StageMap.shrink_to_fit();			// �X�e�[�W�̃}�b�v �s�v���������
	m_MoveMap.clear();					// �ړ��}�b�v  �z��폜
	m_MoveMap.shrink_to_fit();			// �ړ��}�b�v �s�v���������
	m_NavMap.clear();					// �i�r�Q�[�V�����}�b�v�z��폜
	m_NavMap.shrink_to_fit();			// �i�r�Q�[�V�����}�b�v�s�v���������
	m_EventMap.clear();					// �C�x���g�}�b�v�z��폜
	m_EventMap.shrink_to_fit();			// �C�x���g�}�b�v�s�v���������
	m_pGMain->m_nScore = 0;
	m_pGMain->m_nScoreSec = 0;			

}

//-----------------------------------------------------------------------------
//
// �}�b�v�P�̍쐬�ƈړ��̏���
//
//-----------------------------------------------------------------------------
void CMapProc::LoadMap1()
{
	// vector�������p�̍\����
	const STAGEMAP      sm;
	const MOVEMAP       mm;
	const NAVIGATIONMAP nv;

	m_pGMain->m_nTimer = 100;		//�^�C�}�[�̎���		


	// �S�}�b�v�̍폜 -----------------------------------------------
	DestroyAll();

	// �S�Ă̓G�E�X�L���E���ʂ̔�\���� 
	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEffectProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // �G�̔������̃��Z�b�g

	// �o�b��(0,0,-20)�̈ʒu�ɒu�� -------------------------------------
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorld(XMMatrixTranslation(0.0f, 0.05f, 0.0f));
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorldOld(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetLocalRotY(0.0f);  // ���[�J����(Y��)��0�x�ɂ���
	// �X�e�[�W�}�b�v�̐ݒ�E�R���W�����}�b�v�̐ݒ� -----------------------------------------
	m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // �R���W�����}�b�v�̐���
	int i = 0;

	// �}�b�v���b�V���̐ݒ�[0]
	m_StageMap.push_back(sm);
	m_StageMap[i].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/MapClsc/map40.mesh"));

	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	m_pColMesh->AddFbxLoad(_T("Data/Map/MapTkr/map50Field1_Mini.mesh"), VECTOR3(0.0f, 0.0f, 0.0f)); // �}�b�v���b�V���R���W�����̐ݒ�


	i++;

	// ��p  -----------------------------------------------------------
	// ��}�b�v�̐ݒ�[0]
	m_SkyMap.push_back(sm);
	m_SkyMap[0].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/MapTkr/map50Field1_Mini_Moon.mesh"));
	m_SkyMap[0].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	// �i�r�Q�[�V�����}�b�v�̐ݒ� --------------------------------------	

	int ni = 0;
	// �i�r�}�b�v�̐ݒ�[0]
		
	m_NavMap.push_back(nv);
	m_NavMap[ni].vMin = VECTOR3(-7.0f, 1.3f, 13.0f);
	m_NavMap[ni].vMax = VECTOR3(7.0f, 1.3f, 15.0f);
	m_NavMap[ni].dPosStatus = FRONT;		
	//�o���I�u�W�F�N�g��ID
	m_NavMap[ni].m_dwEnmID.push_back(ENM_MOVETARGET_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_SHIELD_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_WALL_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_TARGET_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALL_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALLBOOM_ID);   
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BEND_ID); 


	ni++;
	// �i�r�}�b�v�̐ݒ�[1]

	m_NavMap.push_back(nv);
	m_NavMap[ni].vMin = VECTOR3(13.0f, 1.3f, -7.0f);
	m_NavMap[ni].vMax = VECTOR3(15.0f, 1.3f, 7.0f);
	m_NavMap[ni].dPosStatus = RIGHT;	
	m_NavMap[ni].m_dwEnmID.push_back(ENM_MOVETARGET_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_SHIELD_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_WALL_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_TARGET_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALL_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALLBOOM_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BEND_ID);
	

	ni++;
	// �i�r�}�b�v�̐ݒ�[2]

	m_NavMap.push_back(nv);
	m_NavMap[ni].vMin = VECTOR3(-7.0f, 1.3f, -15.0f);
	m_NavMap[ni].vMax = VECTOR3(7.0f, 1.3f, -13.0f);
	m_NavMap[ni].dPosStatus = BACK;	
	m_NavMap[ni].m_dwEnmID.push_back(ENM_MOVETARGET_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_SHIELD_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_WALL_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_TARGET_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALL_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALLBOOM_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BEND_ID);


	ni++;
	// �i�r�}�b�v�̐ݒ�[3]

	m_NavMap.push_back(nv);
	m_NavMap[ni].vMin = VECTOR3(-15.0f, 1.3f, -7.0f);
	m_NavMap[ni].vMax = VECTOR3(-13.0f, 1.3f, 7.0f);
	m_NavMap[ni].dPosStatus = LEFT;	
	m_NavMap[ni].m_dwEnmID.push_back(ENM_MOVETARGET_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_SHIELD_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_WALL_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_TARGET_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALL_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALLBOOM_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BEND_ID); 


	ni++;
	
	
	// �}�b�v�m�n�P
	m_dwMapNo = 1;
	m_bActive = TRUE;

}


//-----------------------------------------------------------------------------
//
// �}�b�v�`���[�g���A���̍쐬�ƈړ��̏���
//
//-----------------------------------------------------------------------------
void CMapProc::LoadMapTutorial()
{
	// vector�������p�̍\����
	const STAGEMAP      sm;
	const MOVEMAP       mm;
	const NAVIGATIONMAP nv;

	m_pGMain->m_nTimer = 100;		//�^�C�}�[�̎���	


	// �S�}�b�v�̍폜 -----------------------------------------------
	DestroyAll();

	// �S�Ă̓G�E�X�L���E���ʂ̔�\���� 
	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEffectProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // �G�̔������̃��Z�b�g

	// �o�b��(0,0,-20)�̈ʒu�ɒu�� -------------------------------------
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorld(XMMatrixTranslation(0.0f, 0.05f, 0.0f));
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorldOld(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetLocalRotY(0.0f);  // ���[�J����(Y��)��0�x�ɂ���

	// �X�e�[�W�}�b�v�̐ݒ�E�R���W�����}�b�v�̐ݒ� -----------------------------------------
	m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // �R���W�����}�b�v�̐���
	int i = 0;

	// �}�b�v���b�V���̐ݒ�[0]
	m_StageMap.push_back(sm);
	m_StageMap[i].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/MapClsc/map40.mesh"));

	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	m_pColMesh->AddFbxLoad(_T("Data/Map/MapTkr/map50Field1_Mini.mesh"), VECTOR3(0.0f, 0.0f, 0.0f)); // �}�b�v���b�V���R���W�����̐ݒ�


	// ��p  -----------------------------------------------------------
	// ��}�b�v�̐ݒ�[0]
	m_SkyMap.push_back(sm);
	m_SkyMap[0].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/MapTkr/map50Field1_Mini_Moon.mesh"));
	m_SkyMap[0].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	// �i�r�Q�[�V�����}�b�v�̐ݒ� --------------------------------------		

	int ni = 0;
	// �i�r�}�b�v�̐ݒ�[0]


	// �}�b�v�m�n�P
	m_dwMapNo = 1;
	m_bActive = TRUE;

}

//-----------------------------------------------------------------------------
//
// �}�b�v�}���`�̍쐬�ƈړ��̏���
//
//-----------------------------------------------------------------------------
void CMapProc::LoadMapMulti()
{
	// vector�������p�̍\����
	const STAGEMAP      sm;
	const MOVEMAP       mm;
	const NAVIGATIONMAP nv;

	m_pGMain->m_nTimer = 100;		//�^�C�}�[�̎���	


	// �S�}�b�v�̍폜 -----------------------------------------------
	DestroyAll();

	// �S�Ă̓G�E�X�L���E���ʂ̔�\���� 
	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEffectProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // �G�̔������̃��Z�b�g

	// �o�b��(0,0,-20)�̈ʒu�ɒu�� -------------------------------------
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorld(XMMatrixTranslation(0.0f, 0.05f, 0.0f));
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorldOld(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetLocalRotY(0.0f);  // ���[�J����(Y��)��0�x�ɂ���
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetWorld(XMMatrixTranslation(0.0f, 0.05f, 0.0f));
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetWorldOld(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetLocalRotY(0.0f);  // ���[�J����(Y��)��0�x�ɂ���

	// �X�e�[�W�}�b�v�̐ݒ�E�R���W�����}�b�v�̐ݒ� -----------------------------------------
	m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // �R���W�����}�b�v�̐���
	int i = 0;

	// �}�b�v���b�V���̐ݒ�[0]
	m_StageMap.push_back(sm);
	m_StageMap[i].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/MapClsc/map40.mesh"));

	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	m_pColMesh->AddFbxLoad(_T("Data/Map/MapTkr/map50Field1_Mini.mesh"), VECTOR3(0.0f, 0.0f, 0.0f)); // �}�b�v���b�V���R���W�����̐ݒ�


	i++;

	// ��p  -----------------------------------------------------------
	// ��}�b�v�̐ݒ�[0]
	m_SkyMap.push_back(sm);
	m_SkyMap[0].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/MapTkr/map50Field1_Mini_Moon.mesh"));
	m_SkyMap[0].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	// �i�r�Q�[�V�����}�b�v�̐ݒ� --------------------------------------		

	int ni = 0;
	// �i�r�}�b�v�̐ݒ�[0]

	m_NavMap.push_back(nv);
	m_NavMap[ni].vMin = VECTOR3(-7.0f, 1.3f, 13.0f);
	m_NavMap[ni].vMax = VECTOR3(7.0f, 1.3f, 15.0f);
	m_NavMap[ni].dPosStatus = FRONT;		
	//�o���I�u�W�F�N�g��ID
	m_NavMap[ni].m_dwEnmID.push_back(ENM_MOVETARGET_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_SHIELD_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_WALL_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_TARGET_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALL_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALLBOOM_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BEND_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_TARGETSKILL_ID); 


	ni++;
	// �i�r�}�b�v�̐ݒ�[1]

	m_NavMap.push_back(nv);
	m_NavMap[ni].vMin = VECTOR3(13.0f, 1.3f, -7.0f);
	m_NavMap[ni].vMax = VECTOR3(15.0f, 1.3f, 7.0f);
	m_NavMap[ni].dPosStatus = RIGHT;		
	m_NavMap[ni].m_dwEnmID.push_back(ENM_MOVETARGET_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_SHIELD_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_WALL_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_TARGET_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALL_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALLBOOM_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BEND_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_TARGETSKILL_ID); 


	ni++;
	// �i�r�}�b�v�̐ݒ�[2]

	m_NavMap.push_back(nv);
	m_NavMap[ni].vMin = VECTOR3(-7.0f, 1.3f, -15.0f);
	m_NavMap[ni].vMax = VECTOR3(7.0f, 1.3f, -13.0f);
	m_NavMap[ni].dPosStatus = BACK;		
	m_NavMap[ni].m_dwEnmID.push_back(ENM_MOVETARGET_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_SHIELD_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_WALL_ID);  
	m_NavMap[ni].m_dwEnmID.push_back(ENM_TARGET_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALL_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALLBOOM_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BEND_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_TARGETSKILL_ID);


	ni++;
	// �i�r�}�b�v�̐ݒ�[3]

	m_NavMap.push_back(nv);
	m_NavMap[ni].vMin = VECTOR3(-15.0f, 1.3f, -7.0f);
	m_NavMap[ni].vMax = VECTOR3(-13.0f, 1.3f, 7.0f);
	m_NavMap[ni].dPosStatus = LEFT;		
	m_NavMap[ni].m_dwEnmID.push_back(ENM_MOVETARGET_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_SHIELD_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_WALL_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_TARGET_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALL_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BALLBOOM_ID);
	m_NavMap[ni].m_dwEnmID.push_back(ENM_BEND_ID); 
	m_NavMap[ni].m_dwEnmID.push_back(ENM_TARGETSKILL_ID);


	ni++;


	// �}�b�v�m�n�P
	m_dwMapNo = 1;
	m_bActive = TRUE;

}



//-----------------------------------------------------------------------------
// �}�b�v�v���V�[�W���̂����蔻��
//
// �E����i��ɂo�b�̃X�L���j�ƃR���W�����}�b�v�Ƃ̂����蔻��
//
//   CBaseObj*    pObj      ����̃I�u�W�F�N�g
//   VECTOR3* pHit		�ڐG�_�̍��W�i�o�́j
//   VECTOR3* pNormal	�ڐG�_�̖@���x�N�g���i�o�́jwwwwwwwwwwwwwwwwwwwww

//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//-----------------------------------------------------------------------------
BOOL   CMapProc::Hitcheck(CBaseObj* pObj, VECTOR3* pHit, VECTOR3* pNormal)
{
	return  Hitcheck(GetPositionVector(pObj->GetWorld()), GetPositionVector(pObj->GetWorldOld()), pHit, pNormal);
}
//-----------------------------------------------------------------------------
// �}�b�v�v���V�[�W���̂����蔻��
//
// �E����i��ɂo�b�̃X�L���j�ƃR���W�����}�b�v�Ƃ̂����蔻��
//
//   VECTOR3 vNow       ����̌��݈ʒu
//   VECTOR3 vOld       ����̈�O�̈ʒu
//   VECTOR3* vHit		�ڐG�_�̍��W�i�o�́j
//   VECTOR3* vNormal	�ڐG�_�̖@���x�N�g���i�o�́j
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//-----------------------------------------------------------------------------
BOOL   CMapProc::Hitcheck(VECTOR3 vNow, VECTOR3 vOld, VECTOR3* pHit, VECTOR3* pNormal)
{
	BOOL  bRet;
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			bRet = m_MoveMap[i].m_pColMesh->isCollisionLay(vNow, vOld, *pHit, *pNormal);
			if (bRet) return bRet;
		}
	}

	if (m_pColMesh && m_pColMesh->isCollisionLay(vNow, vOld, *pHit, *pNormal))
	{
		return TRUE;
	}
	else {
		return FALSE;
	}

}
//-----------------------------------------------------------------------------
// �}�b�v�v���V�[�W���̂����蔻��
//
// �E����i��ɂo�b�̃X�L���j�̋��ƃR���W�����}�b�v�Ƃ̂����蔻��
//
//   VECTOR3 vNow       ����̌��݂̃I�u�W�F�N�g���S�ʒu
//   VECTOR3 vOld       ����̈�O�̃I�u�W�F�N�g���S�ʒu
//   float& fRadius     ���̔��a
//   VECTOR3 &vHit      �ڐG���̃I�u�W�F�N�g���S�ʒu�̍��W�i�o�́j
//   VECTOR3 &vNormal   �ڐG�_�̖@���x�N�g���i�o�́j
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//-----------------------------------------------------------------------------
BOOL   CMapProc::Hitcheck(VECTOR3 vNow, VECTOR3 vOld, float fRadius, VECTOR3* pHit, VECTOR3* pNormal)
{
	BOOL  bRet;
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			bRet = m_MoveMap[i].m_pColMesh->isCollisionSphere(vNow, vOld, fRadius, *pHit, *pNormal);
			if (bRet) return bRet;
		}
	}

	if (m_pColMesh && m_pColMesh->isCollisionSphere(vNow, vOld, fRadius, *pHit, *pNormal))
	{
		return TRUE;
	}
	else {
		return FALSE;
	}

}


//-----------------------------------------------------------------------------
// �I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	���፷�Əd�͂��l�������A�ڐG������s��									
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�G���[		= -1
//		�ʏ���ړ�	= 1
//		���n		= 2
//		������		= 3
//-----------------------------------------------------------------------------
int  CMapProc::isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	int  nRet = 0, nRetMove = 0;

	// �ړ��}�b�v�Ƃ̐ڐG����ƈړ�
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->isCollisionMoveGravity(*pWorld, mWorldOld, fRadius);  
			if (nRetMove == 1 || nRetMove == 2) break;   // �ړ��}�b�v�ƐڐG�����Ƃ�
		}
	}

	// �ʏ�̃}�b�v�Ƃ̐ڐG����ƈړ�
	if (m_pColMesh)
	{
		nRet = m_pColMesh->isCollisionMoveGravity(*pWorld, mWorldOld, fRadius); 
	}

	if (nRetMove == 1 || nRetMove == 2)  // �ړ��}�b�v�ƐڐG���Ă����Ƃ� 
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}


//-----------------------------------------------------------------------------
// �I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	���፷�Əd�͂��l�������A�ڐG������s��								
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�G���[		= -1
//		�ʏ���ړ�	= 1
//		���n		= 2
//		������		= 3
//-----------------------------------------------------------------------------
int  CMapProc::isCollisionObjMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	int  nRet = 0, nRetMove = 0; 

	// �ړ��}�b�v�Ƃ̐ڐG����ƈړ�
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->CheckFloorMove(*pWorld, mWorldOld);  
			if (nRetMove == 1 || nRetMove == 2) break;   // �ړ��}�b�v�ƐڐG�����Ƃ�
		}
	}

	// �ʏ�̃}�b�v�Ƃ̐ڐG����ƈړ�
	if (m_pColMesh)
	{
		nRet = m_pColMesh->CheckFloorMove(*pWorld, mWorldOld);
	}

	if (nRetMove == 1 || nRetMove == 2)  // �ړ��}�b�v�ƐڐG���Ă����Ƃ�   
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}


//-----------------------------------------------------------------------------
// �I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	�d�͂��l�����A�ڐG������s��										
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�ڐG�����Ƃ��@		�P
//		�ڐG���Ă��Ȃ��Ƃ�	�O
//-----------------------------------------------------------------------------
int CMapProc::isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	int  nRet = 0, nRetMove = 0; 

	// �ړ��}�b�v�Ƃ̐ڐG����ƈړ�
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->isCollisionMove(*pWorld, mWorldOld, fRadius);  
			if (nRetMove == 1) break;
		}
	}

	// �ʏ�̃}�b�v�Ƃ̐ڐG����ƈړ�
	if (m_pColMesh)
	{
		nRet = m_pColMesh->isCollisionMove(*pWorld, mWorldOld, fRadius);  
	}

	if (nRetMove == 1)  // �ړ��}�b�v�ƐڐG���Ă����Ƃ�    
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}

//-----------------------------------------------------------------------------
//
// �}�b�v�v���V�[�W���̍X�V
//
//-----------------------------------------------------------------------------
void CMapProc::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;

	// �蓮�ɂ��}�b�v�̐؂�ւ�
	// �C�x���g�̍X�V����                      
	UpdateEvent();

	// ��̍X�V�@�@�J�����𒆐S�Ƃ����ʒu�ɒu���A�x����]������
	if (m_SkyMap.size() > 0)
	{
		MATRIX4X4 mRot;
		mRot = XMMatrixRotationY(XMConvertToRadians(0.005f));
		mRot = mRot * GetRotateMatrix(m_SkyMap[0].m_mWorld);
		m_SkyMap[0].m_mWorld = XMMatrixTranslation(m_pGMain->m_vEyePt.x, m_pGMain->m_vEyePt.y, m_pGMain->m_vEyePt.z);
		m_SkyMap[0].m_mWorld = mRot * m_SkyMap[0].m_mWorld;
	}

	// �ړ��}�b�v�X�V����
	UpdateMoveMap();

	//�����_�����O
	Render();




	if (m_pGMain->m_dModeType == TUTORIAL)		UpdateTutorial();		

	if (m_pGMain->m_dModeType == MAINMODE)		UpdateMainMode();

	if (m_pGMain->m_dModeType == MULTI)		UpdateMainMode();

}
//-----------------------------------------------------------------------------  
//
// �C�x���g�̃Z�b�g
//
// ����
//   VECTOR3 vMin         : �o�E���f�B���O�{�b�N�X�ŏ��l
//   VECTOR3 vMax         : �o�E���f�B���O�{�b�N�X�ő�l
//   MATRIX4X4 mWorld     : �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X
//   EVENTKIND nEvtKind   : �C�x���g�̎�� eEvtChangeMap:�}�b�v�ړ�, eEvtMoveMap:�ړ��}�b�v�̐���
//   int nEvtNo           : �C�x���g�ԍ� eEvtChangeMap�̂Ƃ��͈ړ���̃}�b�v�ԍ��AeEvtMoveMap�̂Ƃ��͈ړ��}�b�v�̗v�f�ԍ�
//   int nEvtOpe1         : eEvtMoveMap�̂݁B1:�ړ��}�b�v�̈ړ�Active�̎w��B2:�ړ��}�b�v�̈ړ��t���O�̎w��(�ȗ��l0)
//   int nEvtOpe2         : eEvtMoveMap�̂݁B�ړ�Active�̂Ƃ���0:��\�� 1:�\��  �ړ��t���O�̂Ƃ��́@0:�ړ������@1:���s�ړ��@2:��]�@3:�g��k��(�ȗ��l0)
//   int nEvtKeyPush      : 0:�o�E���f�B���O�{�b�N�X�ɐڐG����ƃC�x���g�����A 1:�o�E���f�B���O�{�b�N�X�ɐڐG���āAENTER�L�[�������ƃC�x���g����(�ȗ��l0)
//
// �߂�l
//   int �Z�b�g�����C�x���g�z��̗v�f�ԍ�
//
//-----------------------------------------------------------------------------
int  CMapProc::SetEvent(VECTOR3 vMin, VECTOR3 vMax, MATRIX4X4 mWorld, EVENTKIND nEvtKind, int nEvtNo, int nEvtOpe1, int nEvtOpe2, int nEvtKeyPush)
{
	const EVENTMAP      em;

	m_EventMap.push_back(em);

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	m_EventMap[m_nEvtIdx].m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_EventMap[m_nEvtIdx].m_pBBox->m_mWorld = mWorld;

	// �e���ڂ̐ݒ�
	m_EventMap[m_nEvtIdx].m_nEvtCycle = 0;
	m_EventMap[m_nEvtIdx].m_nEvtKind = nEvtKind;
	m_EventMap[m_nEvtIdx].m_nEvtNo = nEvtNo;
	m_EventMap[m_nEvtIdx].m_nEvtOpe1 = nEvtOpe1;
	m_EventMap[m_nEvtIdx].m_nEvtOpe2 = nEvtOpe2;
	m_EventMap[m_nEvtIdx].m_nEvtKeyPush = nEvtKeyPush;

	m_nEvtIdx++;
	return  m_nEvtIdx - 1;
}

//-----------------------------------------------------------------------------  
//
// �C�x���g�̍X�V�E���s
//
//-----------------------------------------------------------------------------
void  CMapProc::UpdateEvent()
{
	VECTOR3 vHit, vNrm;

	for (int i = 0; i < m_EventMap.size(); i++)
	{
		// PC�̃o�E���f�B���O�{�b�N�X�ɐڐG���Ă��邩�̔���
		if (m_EventMap[i].m_pBBox && m_EventMap[i].m_pBBox->OBBCollisionDetection(m_pGMain->m_pPcProc->GetPcObjPtr()->GetBBox(), &vHit, &vNrm))
		{
			// PC�̃o�E���f�B���O�{�b�N�X�ɐڐG���Ă���Ƃ�
			if (m_EventMap[i].m_nEvtCycle == 0)  // �C�x���g�T�C�N�����O�̂Ƃ�(�܂��ڐG���Ă��Ȃ������Ƃ�)
			{
				if (m_EventMap[i].m_nEvtKeyPush == 1 && !(m_pGMain->m_pDI->CheckKey(KD_DAT, DIK_RETURN) || m_pGMain->m_pDI->CheckJoy(KD_DAT, DIJ_A)))  // Enter�L�[�v�b�V�����K�v�ȂƂ�
				{
					VECTOR3 vPc = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
					vPc.y += 2.0f;
					// PC�̓���ɁAEnter�L�[�v�b�V�����s���Ă��Ȃ����̕\��������
					m_pGMain->m_pFont->Draw3D(vPc, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vEyePt, _T("Push Enter Key!"), VECTOR2(0.8f, 0.2f), RGB(255, 0, 0), 1.0f, _T("HGP�n�p�p�޼��UB"));
				}
				else {
					// �C�x���g���s
					RunEvent(m_EventMap[i]);
				}
			}
		}
		else {
			// PC�̃o�E���f�B���O�{�b�N�X�ɐڐG���Ă��Ȃ��Ƃ�
			if (m_EventMap[i].m_nEvtCycle == 2)  // �C�x���g�T�C�N�����Q�̂Ƃ�(���ɐڐG���Ă��ďI���҂��̂Ƃ�)
			{
				m_EventMap[i].m_nEvtCycle = 0;  // �C�x���g�T�C�N�����O�ɖ߂�
			}
		}
	}
}

//-----------------------------------------------------------------------------  
//
// �C�x���g�̎��s
//
// ����  EVENTMAP& EventMap:�C�x���g�}�b�v
//
//-----------------------------------------------------------------------------
void  CMapProc::RunEvent(EVENTMAP& EventMap)
{
	int i;

	if (EventMap.m_nEvtKind == eEvtChangeMap)   // �}�b�v�ړ��̂Ƃ�
	{
		switch (EventMap.m_nEvtNo)
		{
		case 1:
			LoadMap1();
			break;
		case 3:
			LoadMapTutorial();
			break;
		}
	}
	else if (EventMap.m_nEvtKind == eEvtMoveMap)  // �ړ��}�b�v�̐���̂Ƃ�
	{
		i = EventMap.m_nEvtNo;
		if (EventMap.m_nEvtOpe1 == 1)   // �\���L���Ɋւ��鏈��
		{
			m_MoveMap[i].m_bActive = EventMap.m_nEvtOpe2;
		}
		else if (EventMap.m_nEvtOpe1 == 2)   // �ړ��Ɋւ��鏈��
		{
			m_MoveMap[i].m_nMoveFlag = EventMap.m_nEvtOpe2;
		}
		EventMap.m_nEvtCycle = 2;  // �C�x���g�T�C�N�����Q�ɂ���  
	}
}

//-----------------------------------------------------------------------------
//
// �ړ��}�b�v�̍X�V
//
// �ړ��}�b�v�̕��s�ړ����]�̍X�V���s��
// ���E�l�i��[���[���j�ɒB�����Ƃ��́A���]�ichange�j���s��
// ���]�ichange�j�������Ƃ��́Am_nChangeFlag�ɂP���Ԃ�
// ���[�v�����Ȃ��Ƃ��͔��]�̃^�C�~���O�Œ�~����        
//
//-----------------------------------------------------------------------------
void CMapProc::UpdateMoveMap()
{
	for (DWORD i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)   // �ړ��}�b�v�̍X�V����
		{
			m_MoveMap[i].m_pColMesh->m_mWorldOld = m_MoveMap[i].m_pColMesh->m_mWorld;   // ���[���h�}�g���b�N�X��O
			m_MoveMap[i].m_nChangeFlag = 0;      // �`�F���W�t���O�̃��Z�b�g
			if (m_MoveMap[i].m_nMoveFlag == 1)   // ���s�ړ��̏���
			{
				MATRIX4X4 mPosUp;
				mPosUp = XMMatrixTranslation(m_MoveMap[i].m_vUp.x, m_MoveMap[i].m_vUp.y, m_MoveMap[i].m_vUp.z);
				m_MoveMap[i].m_pColMesh->SetWorldMatrix(mPosUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // �ړ������̏���
				if (m_MoveMap[i].m_vUp.x != 0)  // ���E�ɓ�����
				{
					if (GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).x < m_MoveMap[i].m_vMin.x ||  // ���E�ɓ��������߉E�[���[�Ŕ��]
						GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).x > m_MoveMap[i].m_vMax.x)
					{
						m_MoveMap[i].m_vUp.x *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				if (m_MoveMap[i].m_vUp.y != 0)  // �㉺�ɓ�����
				{
					if (GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).y < m_MoveMap[i].m_vMin.y ||  // �㉺�ɓ��������ߏ�[���[�Ŕ��]
						GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).y > m_MoveMap[i].m_vMax.y)
					{
						m_MoveMap[i].m_vUp.y *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				if (m_MoveMap[i].m_vUp.z != 0)  // �O��ɓ�����
				{
					if (GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).z < m_MoveMap[i].m_vMin.z ||  // �O��ɓ��������ߑO�[��[�Ŕ��]
						GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).z > m_MoveMap[i].m_vMax.z)
					{
						m_MoveMap[i].m_vUp.z *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
			}
			else if (m_MoveMap[i].m_nMoveFlag == 2) {   // ��]�̏���
				MATRIX4X4 mRotUp;
				if (m_MoveMap[i].m_vUp.x != 0)  // �w��]
				{
					mRotUp = XMMatrixRotationX(XMConvertToRadians(m_MoveMap[i].m_vUp.x));
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(mRotUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // �w��]�����̏���
					if (GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).x < m_MoveMap[i].m_vMin.x ||  // �w��]���邽�ߒ[�Ŕ��]
						GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).x > m_MoveMap[i].m_vMax.x)
					{
						m_MoveMap[i].m_vUp.x *= -1;  // �w��]���邽�ߒ[�Ŕ��]
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				else if (m_MoveMap[i].m_vUp.y != 0)  // �x��]
				{
					mRotUp = XMMatrixRotationY(XMConvertToRadians(m_MoveMap[i].m_vUp.y));
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(mRotUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // �w��]�����̏���
					if (GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).y < m_MoveMap[i].m_vMin.y ||  // �x��]���邽�ߒ[�Ŕ��]
						GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).y > m_MoveMap[i].m_vMax.y)
					{
						m_MoveMap[i].m_vUp.y *= -1;  // �x��]���邽�ߒ[�Ŕ��]
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				else if (m_MoveMap[i].m_vUp.z != 0)  // �y��]
				{
					mRotUp = XMMatrixRotationZ(XMConvertToRadians(m_MoveMap[i].m_vUp.z));
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(mRotUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // �w��]�����̏���
					if (GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).z < m_MoveMap[i].m_vMin.z ||  // �y��]���邽�ߒ[�Ŕ��]
						GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).z > m_MoveMap[i].m_vMax.z)
					{
						m_MoveMap[i].m_vUp.z *= -1;  // �y��]���邽�ߒ[�Ŕ��]
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
			}
			else if (m_MoveMap[i].m_nMoveFlag == 3) {   // �g��k���̏���  
				MATRIX4X4 mScaleUp;
				mScaleUp = XMMatrixScaling(m_MoveMap[i].m_vUp.x, m_MoveMap[i].m_vUp.y, m_MoveMap[i].m_vUp.z);
				m_MoveMap[i].m_pColMesh->SetWorldMatrix(mScaleUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // �g��k�������̏���
				VECTOR3 vScaleNow = GetScaleVector(m_MoveMap[i].m_pColMesh->m_mWorld);     // ���݂̊g�嗦�𓾂�
				if (vScaleNow.x < m_MoveMap[i].m_vMin.x ||      // �K��̊g��k���ɒB������
					vScaleNow.x > m_MoveMap[i].m_vMax.x ||
					vScaleNow.y < m_MoveMap[i].m_vMin.y ||
					vScaleNow.y > m_MoveMap[i].m_vMax.y ||
					vScaleNow.z < m_MoveMap[i].m_vMin.z ||
					vScaleNow.z > m_MoveMap[i].m_vMax.z)
				{
					m_MoveMap[i].m_vUp.x = 1 / avoidZero(m_MoveMap[i].m_vUp.x);  // �g��k���̔��]
					m_MoveMap[i].m_vUp.y = 1 / avoidZero(m_MoveMap[i].m_vUp.y);  // �g��k���̔��]
					m_MoveMap[i].m_vUp.z = 1 / avoidZero(m_MoveMap[i].m_vUp.z);  // �g��k���̔��]
					m_MoveMap[i].m_nChangeFlag = 1;
				}
			}
			// ���[�v�����Ȃ��Ƃ��̒�~���f�B���]�̃^�C�~���O�Œ�~����          
			if (m_MoveMap[i].m_nLoop == 0 && m_MoveMap[i].m_nChangeFlag == 1)
			{
				m_MoveMap[i].m_nMoveFlag = 0;    // �ړ����Ȃ�
			}
		}
	}
}

//-----------------------------------------------------------------------------  
// ���C�����[�h�̍X�V�E���s
//
//
//-----------------------------------------------------------------------------
void  CMapProc::UpdateMainMode()
{
	switch (PhaseMap)
	{
	case 0:
		nCount++;
		if (nCount >= 360)
		{
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetStop(FALSE);
			m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetStop(FALSE);
			nCount = 0;
			PhaseMap++;
		}
		break;

	case 1:
		//�^�C�}�[�@�\	
			if (0 > m_pGMain->m_nTimer) {
				//m_pGMain->m_dwGameStatus = GAMECLEAR;
				if (m_pGMain->m_nHighScore < m_pGMain->m_nScore) {		//--�n�C�X�R�A�̍X�V�ƃZ�[�u	
					FILE *fp;
					errno_t error;
					m_pGMain->m_nHighScore = m_pGMain->m_nScore;
					error = fopen_s(&fp, "Data/Read/Save.dat", "wb"); // �t�@�C�����J��
					if (fp == NULL) { // NULL���Ԃ��Ă�����G���[����
					}
					else {
						fwrite(&m_pGMain->m_nHighScore, sizeof(int), 1, fp);
						fclose(fp); //�t�@�C�������
					}
				}
				PhaseMap++;
				nCount = 0;
			}
			if (nCount > 60) {
				m_pGMain->m_nTimer--;
				m_pGMain->m_nTimeNum++;
				nCount = 0;
			}
			else {
				nCount++;
			}

		break;

	case 2:
		nCount++;
		m_pGMain->m_pPcProc->GetPcObjPtr()->SetStop(TRUE);
		m_pGMain->m_pPcProc->GetPcSecObjPtr()->SetStop(TRUE);
		if (nCount >= 120) {
			if(m_pGMain->m_dModeType == MAINMODE)m_pGMain->m_dwGameStatus = GAMECLEAR;
			if (m_pGMain->m_dModeType == MULTI)m_pGMain->m_dwGameStatus = GAMEMULTIBATTLERESULT;
			nCount = 0;
			PhaseMap = 0;

		}

		break;

	}

}

//-----------------------------------------------------------------------------  
// �C�x���g�̍X�V�E���s
//
//
//-----------------------------------------------------------------------------
void  CMapProc::UpdateTutorial()
{
	DWORD	TutorialPhase = m_pGMain->m_dPhase;		//�`���[�g���A���t�F�[�Y�̔ԍ�
	bPhaseClear = FALSE;

	int MoveCountClear = 20;		//�ړ��`���[�g���A���̃N���A�����i�ړ������j
	int HitNumClear = 5;			//�{�[���`���[�g���A���̃N���A�����i�ł��Ԃ����񐔁j
	int BreakNumClear = 3;			//�I�`���[�g���A���̃N���A�����i�󂵂��񐔁j
	int BoomBreakNumClear = 1;			//���e�`���[�g���A���̃N���A�����i�󂵂��񐔁j
	int UseNumSkillClear = 3;		//�X�L���`���[�g���A���̃N���A�����i�g�p�����񐔁j

	switch (TutorialPhase)
	{
	case 1:		//�ړ��̃`���[�g���A��-----------------------------------------------------------------------------------------------------------
		switch (PhaseMap)
		{
		case 0:
			m_TutorialVariable.mWorld = m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld();
			m_TutorialVariable.mWorldOld = m_TutorialVariable.mWorld;
			TutolialPhaseMapStart();
			break;

		case 1:

			m_TutorialVariable.mWorld = m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld();
			if (0 < magnitude(GetPositionVector(m_TutorialVariable.mWorld) - GetPositionVector(m_TutorialVariable.mWorldOld))) {
				m_TutorialVariable.fMoveCount += magnitude(GetPositionVector(m_TutorialVariable.mWorld) - GetPositionVector(m_TutorialVariable.mWorldOld));
			}
			if (m_TutorialVariable.fMoveCount > MoveCountClear)		//�v���C���[���i�񂾋����ɉ����ďI��������
			{
				PhaseMap++;
				m_pGMain->m_pPcProc->GetPcObjPtr()->SetStop(TRUE);

			}

			m_TutorialVariable.mWorldOld = m_TutorialVariable.mWorld;


			break;

		case 2:
			TutolialPhaseMapEnd();
			break;

		}

		break;

	case 3:		//�{�[���̃`���[�g���A��--------------------------------------------------------------------------------

		switch (PhaseMap)
		{
		case  0: 
		{
			DWORD dwID[] = {
				ENM_BALL_ID,
			};
			const int IDNum = sizeof(dwID) / sizeof(DWORD);
			TutolialPhaseSetNavMap(dwID, IDNum);
		}

			TutolialPhaseMapStart();
			break;

		case 1:
			if (m_pGMain->m_pEnmProc->m_pEnmBallProc->GetHitNum() >= HitNumClear) {		//�{�[���𓖂Ă����ɉ����ďI��
				PhaseMap++;
				m_pGMain->m_pPcProc->GetPcObjPtr()->SetStop(TRUE);

			}
			m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->SetActive(FALSE);
			break;

		case 2:
			TutolialPhaseMapEnd();
			break;

		}


		break;
	case 5:		//�I�̃`���[�g���A��------------------------------------------------------------------------------------------
		switch (PhaseMap)
		{
		case  0: 
			{
				DWORD dwID[] = {
					ENM_BALL_ID,
					ENM_TARGET_ID,
					ENM_MOVETARGET_ID,
				};
				const int IDNum = sizeof(dwID) / sizeof(DWORD);
				TutolialPhaseSetNavMap(dwID, IDNum);
			}
			TutolialPhaseMapStart();

			break;

		case 1:

			if ((m_pGMain->m_pEnmProc->m_pEnmTargetProc->GetBreakNum()+ m_pGMain->m_pEnmProc->m_pEnmMoveTargetProc->GetBreakNum())>= BreakNumClear) {		//�I�ɓ��Ă����ɉ����ďI��
				PhaseMap++;
				m_pGMain->m_pPcProc->GetPcObjPtr()->SetStop(TRUE);

			}
			break;

		case 2:
			TutolialPhaseMapEnd();
			break;

		}

		break;


	case 7:		//���e�{�[���̃`���[�g���A��--------------------------------------------------------------------------------

		switch (PhaseMap)
		{
		case  0:
			{
				DWORD dwID[] = {
					ENM_TARGET_ID,
					ENM_MOVETARGET_ID,
					ENM_BALLBOOM_ID,
				};
				const int IDNum = sizeof(dwID) / sizeof(DWORD);
				TutolialPhaseSetNavMap(dwID, IDNum);
			}

			TutolialPhaseMapStart();

			break;

		case 1:

			if ((m_pGMain->m_pEffectProc->m_pLetterEffectProc->GetBreakNum()) >= BoomBreakNumClear) {			//�����œI���󂵂����ɉ����ďI��
				PhaseMap++;
				m_pGMain->m_pPcProc->GetPcObjPtr()->SetStop(TRUE);

			}
			break;

		case 2:
			TutolialPhaseMapEnd();
			break;

		}

		break;

	case 9:		//�X�L���̃`���[�g���A��--------------------------------------------------------------------------

		switch (PhaseMap)
		{
		case  0:
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColumanNo(0, WEAPON_DIV);
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColumanNo(1, WEAPON_SKILLSPEEDUP);
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetWeaponColumanNo(2, WEAPON_BIGBALL);

			{
				DWORD dwID[] = {
					ENM_TARGET_ID,
					ENM_MOVETARGET_ID,
					ENM_BALL_ID,
				};
				const int IDNum = sizeof(dwID) / sizeof(DWORD);
				TutolialPhaseSetNavMap(dwID, IDNum);
			}

			TutolialPhaseMapStart();

			break;

		case 1:

			if ((m_pGMain->m_pWeaponProc->m_pWeaponSwordProc->GetWeaponSwordObjPtr()->GetUseNumWeapon()+m_pGMain->m_pPcProc->GetPcObjPtr()->GetUseNumSkill()) >= UseNumSkillClear) {		//�X�L���̎g�p�����񐔂ɉ����ďI��
				PhaseMap++;
				m_pGMain->m_pPcProc->GetPcObjPtr()->SetStop(TRUE);

			}
			break;

		case 2:
			TutolialPhaseMapEnd();
			break;

		}

		break;


	default:

		PhaseMap = 0;


		break;
	}

}


//============================================================================
//
//  �`���[�g���A�����[�h�̃t�F�[�Y�����̃t�F�[�Y�ɂ���
//
//
//============================================================================
void  CMapProc::TutolialNextPhase()
{

	m_pGMain->m_dPhase++;		//���̃t�F�[�Y�Ɉړ�
	PhaseMap = 0;
	m_TutorialVariable.fMoveCount = 0;
	m_TutorialVariable.dwNumCount = 0;
	m_NavMap.clear();					// �i�r�Q�[�V�����}�b�v�z��폜
	m_NavMap.shrink_to_fit();			// �i�r�Q�[�V�����}�b�v�s�v���������
	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // �G�̔������̃��Z�b�g
	dwCount = 0;


}

//============================================================================
//
//  �`���[�g���A�����[�h�̃t�F�[�Y���Ƃ̎n�߂�Ƃ��̏���
//
//
//============================================================================
void  CMapProc::TutolialPhaseMapStart()
{
	m_TutorialVariable.dwNumCount = 0;
	PhaseMap++;
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetStop(FALSE);		//�v���C���[�𓮂�����悤�ɂ���



}

//============================================================================
//
//  �`���[�g���A�����[�h�̃t�F�[�Y���Ƃ̏I������Ƃ��̏���
//
//
//============================================================================
void  CMapProc::TutolialPhaseMapEnd()
{
	dwCount++;
	bPhaseClear = TRUE;
	if (dwCount >= 120)		//120�J�E���g�҂�
	{
		TutolialNextPhase();
	}
}


//============================================================================
//
//  �`���[�g���A�����[�h�̃i�r�Q�[�V�����}�b�v��o�^
//
//	DWORD		*dwID	�i�r�Q�[�V�����}�b�v�ɓo�^����ID
//
//
//============================================================================
void  CMapProc::TutolialPhaseSetNavMap(const DWORD dwID[], const DWORD IDNum)
{

	int ni = 0;
	const NAVIGATIONMAP nv;

	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // �G�̔������̃��Z�b�g

	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorld(XMMatrixTranslation(0.0f, 0.05f, 0.0f));
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorldOld(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetLocalRotY(0.0f);  // ���[�J����(Y��)��0�x�ɂ���
	// �i�r�}�b�v�̐ݒ�[0]

	m_NavMap.push_back(nv);
	m_NavMap[ni].vMin = VECTOR3(-7.0f, 1.3f, 13.0f);
	m_NavMap[ni].vMax = VECTOR3(7.0f, 1.3f, 15.0f);
	m_NavMap[ni].dPosStatus = FRONT;		
	for(int i=0;i< IDNum;i++)	m_NavMap[ni].m_dwEnmID.push_back(dwID[i]);
	ni++;
	// �i�r�}�b�v�̐ݒ�[1]

	m_NavMap.push_back(nv);
	m_NavMap[ni].vMin = VECTOR3(13.0f, 1.3f, -7.0f);
	m_NavMap[ni].vMax = VECTOR3(15.0f, 1.3f, 7.0f);
	m_NavMap[ni].dPosStatus = RIGHT;	
	for (int i = 0; i < IDNum; i++)	m_NavMap[ni].m_dwEnmID.push_back(dwID[i]);
	ni++;
	// �i�r�}�b�v�̐ݒ�[2]

	m_NavMap.push_back(nv);
	m_NavMap[ni].vMin = VECTOR3(-7.0f, 1.3f, -15.0f);
	m_NavMap[ni].vMax = VECTOR3(7.0f, 1.3f, -13.0f);
	m_NavMap[ni].dPosStatus = BACK;	
	for (int i = 0; i < IDNum; i++)	m_NavMap[ni].m_dwEnmID.push_back(dwID[i]);
	ni++;
	// �i�r�}�b�v�̐ݒ�[3]

	m_NavMap.push_back(nv);
	m_NavMap[ni].vMin = VECTOR3(-15.0f, 1.3f, -7.0f);
	m_NavMap[ni].vMax = VECTOR3(-13.0f, 1.3f, 7.0f);
	m_NavMap[ni].dPosStatus = LEFT;	
	for (int i = 0; i < IDNum; i++)	m_NavMap[ni].m_dwEnmID.push_back(dwID[i]);
	ni++;



}


//============================================================================
//  �}�b�v�v���V�[�W���̃����_�����O
// 
//    �����@�@�Ȃ�
// 
//    �߂�l�@�Ȃ�
//============================================================================
void  CMapProc::Render(void)
{
	if (m_bActive) {

		// ��̃����_�����O
		if (m_SkyMap.size() > 0)
		{
			// ��̃����_�����O   �A�e�����Ȃ������_�����O 
			// Z�o�b�t�@�𖳌���
			m_pGMain->m_pD3D->SetZBuffer(FALSE);
			m_SkyMap[0].m_pMesh->Render(m_SkyMap[0].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt);  // �A�e�����Ȃ������_�����O 
			// Z�o�b�t�@��L����
			m_pGMain->m_pD3D->SetZBuffer(TRUE);
		}

		// �}�b�v�����_�����O
		for (DWORD i = 0; i < m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 0)  // �ʏ�̃u�����h�X�e�[�g
			{
				if (m_StageMap[i].m_pMesh) m_StageMap[i].m_pMesh->RenderToon(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);

			}
			else if (m_StageMap[i].m_nMaterialFlag == 2)  // �f�B�X�v���C�X�����g�}�b�s���O
			{
				// �f�B�X�v���C�X�����g�}�b�v�����_�����O
				if (m_StageMap[i].m_pMesh) 	m_StageMap[i].m_pMesh->RenderDisplace(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
		}

		// �ړ��}�b�v�����_�����O     * ���̃v���O�����ł͎g�p���Ă��Ȃ�
		for (DWORD i = 0; i < m_MoveMap.size(); i++)
		{
			if (m_MoveMap[i].m_nMaterialFlag == 0)  // �ʏ�̃u�����h�X�e�[�g
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->Render(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
			else if (m_MoveMap[i].m_nMaterialFlag == 2)  // �f�B�X�v���C�X�����g�}�b�s���O
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->RenderDisplace(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
		}

	}
}

//============================================================================
//  �}�b�v�v���V�[�W���̃����_�����O ���̂Q
// 
//  �������̃}�b�v�I�u�W�F�N�g��`�悷�邽�߁A�僋�[�v�̍Ō�Ɏ��s�����
// 
//    �����@�@�Ȃ�
// 
//    �߂�l�@�Ȃ�
//============================================================================
void  CMapProc::Render2(void)
{
	if (m_bActive) {

		// �}�b�v�����_�����O
		for (DWORD i = 0; i < m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 1)  // �����F�̃u�����h�X�e�[�g
			{
				// �����F�̃����_�����O
				if (m_StageMap[i].m_pMesh) m_StageMap[i].m_pMesh->RenderToon(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt);

			}
		}

		// �ړ��}�b�v�����_�����O     * ���̃v���O�����ł͎g�p���Ă��Ȃ�
		for (DWORD i = 0; i < m_MoveMap.size(); i++)
		{
			if (m_MoveMap[i].m_nMaterialFlag == 1)  // �����F�̃u�����h�X�e�[�g
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->Render(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
		}

		// �g�̃����_�����O
		for (DWORD i = 0; i < m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 3)
			{
				// �g�����_�����O
				if (m_StageMap[i].m_pWave)
					m_StageMap[i].m_pWave->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
		}

	}
}


//============================================================================
//  �}�b�v�v���V�[�W���̃����_�����O
// 
//    �����@�@�Ȃ�
// 
//    �߂�l�@�Ȃ�
//============================================================================
void  CMapProc::RenderSecond(void)
{
	if (m_bActive) {

		// ��̃����_�����O
		if (m_SkyMap.size() > 0)
		{
			// ��̃����_�����O   �A�e�����Ȃ������_�����O 
			// Z�o�b�t�@�𖳌���
			m_pGMain->m_pD3D->SetZBuffer(FALSE);
			m_SkyMap[0].m_pMesh->Render(m_SkyMap[0].m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, VECTOR3(0, 0, 0), m_pGMain->m_vEyePtSecond);  // �A�e�����Ȃ������_�����O 
			// Z�o�b�t�@��L����
			m_pGMain->m_pD3D->SetZBuffer(TRUE);
		}

		// �}�b�v�����_�����O
		for (DWORD i = 0; i < m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 0)  // �ʏ�̃u�����h�X�e�[�g
			{
				if (m_StageMap[i].m_pMesh) m_StageMap[i].m_pMesh->RenderToon(m_StageMap[i].m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);

			}
			else if (m_StageMap[i].m_nMaterialFlag == 2)  // �f�B�X�v���C�X�����g�}�b�s���O
			{
				// �f�B�X�v���C�X�����g�}�b�v�����_�����O
				if (m_StageMap[i].m_pMesh) 	m_StageMap[i].m_pMesh->RenderDisplace(m_StageMap[i].m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
			}
		}

		// �ړ��}�b�v�����_�����O     * ���̃v���O�����ł͎g�p���Ă��Ȃ�
		for (DWORD i = 0; i < m_MoveMap.size(); i++)
		{
			if (m_MoveMap[i].m_nMaterialFlag == 0)  // �ʏ�̃u�����h�X�e�[�g
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->Render(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
			}
			else if (m_MoveMap[i].m_nMaterialFlag == 2)  // �f�B�X�v���C�X�����g�}�b�s���O
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->RenderDisplace(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
			}
		}

	}
}

//============================================================================
//  �}�b�v�v���V�[�W���̃����_�����O ���̂Q
// 
//  �������̃}�b�v�I�u�W�F�N�g��`�悷�邽�߁A�僋�[�v�̍Ō�Ɏ��s�����
// 
//    �����@�@�Ȃ�
// 
//    �߂�l�@�Ȃ�
//============================================================================
void  CMapProc::Render2Second(void)
{
	if (m_bActive) {

		// �}�b�v�����_�����O
		for (DWORD i = 0; i < m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 1)  // �����F�̃u�����h�X�e�[�g
			{
				// �����F�̃����_�����O
				if (m_StageMap[i].m_pMesh) m_StageMap[i].m_pMesh->RenderToon(m_StageMap[i].m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, VECTOR3(0, 0, 0), m_pGMain->m_vEyePtSecond);

			}
		}

		// �ړ��}�b�v�����_�����O     * ���̃v���O�����ł͎g�p���Ă��Ȃ�
		for (DWORD i = 0; i < m_MoveMap.size(); i++)
		{
			if (m_MoveMap[i].m_nMaterialFlag == 1)  // �����F�̃u�����h�X�e�[�g
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->Render(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
			}
		}

		// �g�̃����_�����O
		for (DWORD i = 0; i < m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 3)
			{
				// �g�����_�����O
				if (m_StageMap[i].m_pWave)
					m_StageMap[i].m_pWave->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mViewSecond, m_pGMain->m_mProjSecond, m_pGMain->m_vLightDirSecond, m_pGMain->m_vEyePtSecond);
			}
		}

	}
}







//=============================================================================
// �T�u�@�}�b�v�v���V�[�W���̃R���X�g���N�^
//
//-----------------------------------------------------------------------------
CMapSubProc::CMapSubProc(CGameMain*	pGMain)
{
	// �N���X�S�̂̃N�����[
	// (vector�N���X�͏������s�v)
	m_pGMain = pGMain;
	m_dwMapNo = 0;
	m_bActive = FALSE;
	m_pColMesh = NULL;					// �R���W�������b�V���ւ̃|�C���^
	m_nEvtIdx = 0;							

}

//-----------------------------------------------------------------------------
// �T�u�@�}�b�v�v���V�[�W���̃f�X�g���N�^
//
//-----------------------------------------------------------------------------
CMapSubProc::~CMapSubProc()
{
	DestroyAll();
}

//-----------------------------------------------------------------------------
// �T�u�@�}�b�v�̍폜
//
//-----------------------------------------------------------------------------
void CMapSubProc::DestroyAll()
{
	m_dwMapNo = 0;
	m_bActive = FALSE;
	m_nEvtIdx = 0;							
	// ���b�V���̃f���[�g
	for (DWORD i = 0; i < m_StageMap.size(); i++)
	{
		SAFE_DELETE(m_StageMap[i].m_pMesh);
		SAFE_DELETE(m_StageMap[i].m_pWave);
	}
	for (DWORD i = 0; i < m_MoveMap.size(); i++)
	{
		SAFE_DELETE(m_MoveMap[i].m_pMesh);
		SAFE_DELETE(m_MoveMap[i].m_pColMesh);
	}
	for (DWORD i = 0; i < m_EventMap.size(); i++)
	{
		SAFE_DELETE(m_EventMap[i].m_pBBox);
	}
	SAFE_DELETE(m_pColMesh);

	m_StageMap.clear();					// �X�e�[�W�̃}�b�v  �z��폜
	m_StageMap.shrink_to_fit();			// �X�e�[�W�̃}�b�v �s�v���������
	m_MoveMap.clear();					// �ړ��}�b�v  �z��폜
	m_MoveMap.shrink_to_fit();			// �ړ��}�b�v �s�v���������
	m_NavMap.clear();					// �i�r�Q�[�V�����}�b�v�z��폜
	m_NavMap.shrink_to_fit();			// �i�r�Q�[�V�����}�b�v�s�v���������
	m_EventMap.clear();					// �C�x���g�}�b�v�z��폜
	m_EventMap.shrink_to_fit();			// �C�x���g�}�b�v�s�v���������

}

//-----------------------------------------------------------------------------
// �T�u�@�}�b�v�P�̍쐬�ƈړ��̏���
//
//-----------------------------------------------------------------------------
void CMapSubProc::LoadMap1()
{
	// vector�������p�̍\����
	const STAGEMAPSUB      sm;
	const MOVEMAPSUB       mm;
	const NAVIGATIONMAPSUB nv;

	// �S�}�b�v�̍폜 -----------------------------------------------
	DestroyAll();

	// �S�Ă̓G�E�X�L���E���ʂ̔�\���� 
	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEffectProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // �G�̔������̃��Z�b�g

	// �o�b��(0,0,-20)�̈ʒu�ɒu�� -------------------------------------
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorld(XMMatrixTranslation(0.0f, 0.05f, 0.0f));
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorldOld(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetLocalRotY(0.0f);  // ���[�J����(Y��)��0�x�ɂ���

	// �X�e�[�W�}�b�v�̐ݒ�E�R���W�����}�b�v�̐ݒ� -----------------------------------------
	m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // �R���W�����}�b�v�̐���
	int i = 0;

	// �}�b�v���b�V���̐ݒ�[0]
	m_StageMap.push_back(sm);
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	m_pColMesh->AddFbxLoad(_T("Data/Map/MapTkr/map50Field1_Mini_Mini.ver3.mesh"), VECTOR3(0.0f, 0.0f, 0.0f)); // �}�b�v���b�V���R���W�����̐ݒ�		


	i++;


	int ni = 0;
	// �i�r�}�b�v�̐ݒ�[0]
	// �}�b�v�m�n�P
	m_dwMapNo = 1;
	m_bActive = TRUE;

}

//-----------------------------------------------------------------------------
// �T�u�@�}�b�v2�̍쐬�ƈړ��̏���
//
//-----------------------------------------------------------------------------
void CMapSubProc::LoadMap2()
{
	// vector�������p�̍\����
	const STAGEMAPSUB      sm;
	const MOVEMAPSUB       mm;
	const NAVIGATIONMAPSUB nv;

	// �S�}�b�v�̍폜 -----------------------------------------------
	DestroyAll();

	// �S�Ă̓G�E�X�L���E���ʂ̔�\���� 
	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEffectProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // �G�̔������̃��Z�b�g

	// �o�b��(0,0,-20)�̈ʒu�ɒu�� -------------------------------------
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorld(XMMatrixTranslation(0.0f, 0.05f, 0.0f));
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorldOld(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetLocalRotY(0.0f);  // ���[�J����(Y��)��0�x�ɂ���

	// �X�e�[�W�}�b�v�̐ݒ�E�R���W�����}�b�v�̐ݒ� -----------------------------------------
	m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // �R���W�����}�b�v�̐���
	int i = 0;

	// �}�b�v���b�V���̐ݒ�[0]
	m_StageMap.push_back(sm);
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	m_pColMesh->AddFbxLoad(_T("Data/Map/MapTkr/map50Field1_Simple.mesh"), VECTOR3(0.0f, 0.0f, 0.0f)); // �}�b�v���b�V���R���W�����̐ݒ�	





	i++;


	// ��p  -----------------------------------------------------------
	// ��}�b�v�̐ݒ�[0]
	// �i�r�Q�[�V�����}�b�v�̐ݒ� --------------------------------------
	int ni = 0;
	// �i�r�}�b�v�̐ݒ�[0]
	// �}�b�v�m�n�P
	m_dwMapNo = 1;
	m_bActive = TRUE;

}


//-----------------------------------------------------------------------------
//�T�u�@�}�b�v�v���V�[�W���̂����蔻��
//
// �E����i��ɂo�b�̃X�L���j�ƃR���W�����}�b�v�Ƃ̂����蔻��
//
//   CBaseObj*    pObj      ����̃I�u�W�F�N�g
//   VECTOR3* pHit		�ڐG�_�̍��W�i�o�́j
//   VECTOR3* pNormal	�ڐG�_�̖@���x�N�g���i�o�́jwwwwwwwwwwwwwwwwwwwww

//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//-----------------------------------------------------------------------------
BOOL   CMapSubProc::Hitcheck(CBaseObj* pObj, VECTOR3* pHit, VECTOR3* pNormal)
{
	return  Hitcheck(GetPositionVector(pObj->GetWorld()), GetPositionVector(pObj->GetWorldOld()), pHit, pNormal);
}
//-----------------------------------------------------------------------------
//�T�u�@�}�b�v�v���V�[�W���̂����蔻��
//
// �E����i��ɂo�b�̃X�L���j�ƃR���W�����}�b�v�Ƃ̂����蔻��
//
//   VECTOR3 vNow       ����̌��݈ʒu
//   VECTOR3 vOld       ����̈�O�̈ʒu
//   VECTOR3* vHit		�ڐG�_�̍��W�i�o�́j
//   VECTOR3* vNormal	�ڐG�_�̖@���x�N�g���i�o�́j
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//-----------------------------------------------------------------------------
BOOL   CMapSubProc::Hitcheck(VECTOR3 vNow, VECTOR3 vOld, VECTOR3* pHit, VECTOR3* pNormal)
{
	BOOL  bRet;
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			bRet = m_MoveMap[i].m_pColMesh->isCollisionLay(vNow, vOld, *pHit, *pNormal);
			if (bRet) return bRet;
		}
	}

	if (m_pColMesh && m_pColMesh->isCollisionLay(vNow, vOld, *pHit, *pNormal))
	{
		return TRUE;
	}
	else {
		return FALSE;
	}

}
//----------------------------------------------------------------------------- 
//�T�u�@�}�b�v�v���V�[�W���̂����蔻��
//
// �E����i��ɂo�b�̃X�L���j�̋��ƃR���W�����}�b�v�Ƃ̂����蔻��
//
//   VECTOR3 vNow       ����̌��݂̃I�u�W�F�N�g���S�ʒu
//   VECTOR3 vOld       ����̈�O�̃I�u�W�F�N�g���S�ʒu
//   float& fRadius     ���̔��a
//   VECTOR3 &vHit      �ڐG���̃I�u�W�F�N�g���S�ʒu�̍��W�i�o�́j
//   VECTOR3 &vNormal   �ڐG�_�̖@���x�N�g���i�o�́j
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//-----------------------------------------------------------------------------
BOOL   CMapSubProc::Hitcheck(VECTOR3 vNow, VECTOR3 vOld, float fRadius, VECTOR3* pHit, VECTOR3* pNormal)
{
	BOOL  bRet;
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			bRet = m_MoveMap[i].m_pColMesh->isCollisionSphere(vNow, vOld, fRadius, *pHit, *pNormal);
			if (bRet) return bRet;
		}
	}

	if (m_pColMesh && m_pColMesh->isCollisionSphere(vNow, vOld, fRadius, *pHit, *pNormal))
	{
		return TRUE;
	}
	else {
		return FALSE;
	}

}


//-----------------------------------------------------------------------------
//
//�I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	���፷�Əd�͂��l�������A�ڐG������s��								
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�G���[		= -1
//		�ʏ���ړ�	= 1
//		���n		= 2
//		������		= 3
//-----------------------------------------------------------------------------
int  CMapSubProc::isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	int  nRet = 0, nRetMove = 0; 

	// �ړ��}�b�v�Ƃ̐ڐG����ƈړ�
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->isCollisionMoveGravity(*pWorld, mWorldOld, fRadius); 
			if (nRetMove == 1 || nRetMove == 2) break;   // �ړ��}�b�v�ƐڐG�����Ƃ�
		}
	}

	// �ʏ�̃}�b�v�Ƃ̐ڐG����ƈړ�
	if (m_pColMesh)
	{
		nRet = m_pColMesh->isCollisionMoveGravity(*pWorld, mWorldOld, fRadius); 
	}

	if (nRetMove == 1 || nRetMove == 2)  // �ړ��}�b�v�ƐڐG���Ă����Ƃ�  
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}


//-----------------------------------------------------------------------------
//�I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	���፷�Əd�͂��l�������A�ڐG������s��								
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�G���[		= -1
//		�ʏ���ړ�	= 1
//		���n		= 2
//		������		= 3
//-----------------------------------------------------------------------------
int  CMapSubProc::isCollisionObjMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	int  nRet = 0, nRetMove = 0; 

	// �ړ��}�b�v�Ƃ̐ڐG����ƈړ�
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->CheckFloorMove(*pWorld, mWorldOld);  
			if (nRetMove == 1 || nRetMove == 2) break;   // �ړ��}�b�v�ƐڐG�����Ƃ�
		}
	}

	// �ʏ�̃}�b�v�Ƃ̐ڐG����ƈړ�
	if (m_pColMesh)
	{
		nRet = m_pColMesh->CheckFloorMove(*pWorld, mWorldOld);  
	}

	if (nRetMove == 1 || nRetMove == 2)  // �ړ��}�b�v�ƐڐG���Ă����Ƃ�  
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}


//-----------------------------------------------------------------------------
//�I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	�d�͂��l�����A�ڐG������s��											
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�ڐG�����Ƃ��@		�P
//		�ڐG���Ă��Ȃ��Ƃ�	�O
//-----------------------------------------------------------------------------
int CMapSubProc::isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	int  nRet = 0, nRetMove = 0; 

	// �ړ��}�b�v�Ƃ̐ڐG����ƈړ�
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->isCollisionMove(*pWorld, mWorldOld, fRadius); 
			if (nRetMove == 1) break;
		}
	}

	// �ʏ�̃}�b�v�Ƃ̐ڐG����ƈړ�
	if (m_pColMesh)
	{
		nRet = m_pColMesh->isCollisionMove(*pWorld, mWorldOld, fRadius);  
	}

	if (nRetMove == 1)  // �ړ��}�b�v�ƐڐG���Ă����Ƃ�    
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}

//-----------------------------------------------------------------------------
// �T�u�@�}�b�v�v���V�[�W���̍X�V
//
//-----------------------------------------------------------------------------
void CMapSubProc::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;

	// �蓮�ɂ��}�b�v�̐؂�ւ�
	// �C�x���g�̍X�V����                      
	UpdateEvent();


	// �ړ��}�b�v�X�V����
	UpdateMoveMap();

	//�����_�����O
	Render();

}
//-----------------------------------------------------------------------------   
// �T�u�@�C�x���g�̃Z�b�g
//
// ����
//   VECTOR3 vMin         : �o�E���f�B���O�{�b�N�X�ŏ��l
//   VECTOR3 vMax         : �o�E���f�B���O�{�b�N�X�ő�l
//   MATRIX4X4 mWorld     : �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X
//   EVENTKIND nEvtKind   : �C�x���g�̎�� eEvtChangeMap:�}�b�v�ړ�, eEvtMoveMap:�ړ��}�b�v�̐���
//   int nEvtNo           : �C�x���g�ԍ� eEvtChangeMap�̂Ƃ��͈ړ���̃}�b�v�ԍ��AeEvtMoveMap�̂Ƃ��͈ړ��}�b�v�̗v�f�ԍ�
//   int nEvtOpe1         : eEvtMoveMap�̂݁B1:�ړ��}�b�v�̈ړ�Active�̎w��B2:�ړ��}�b�v�̈ړ��t���O�̎w��(�ȗ��l0)
//   int nEvtOpe2         : eEvtMoveMap�̂݁B�ړ�Active�̂Ƃ���0:��\�� 1:�\��  �ړ��t���O�̂Ƃ��́@0:�ړ������@1:���s�ړ��@2:��]�@3:�g��k��(�ȗ��l0)
//   int nEvtKeyPush      : 0:�o�E���f�B���O�{�b�N�X�ɐڐG����ƃC�x���g�����A 1:�o�E���f�B���O�{�b�N�X�ɐڐG���āAENTER�L�[�������ƃC�x���g����(�ȗ��l0)
//
// �߂�l
//   int �Z�b�g�����C�x���g�z��̗v�f�ԍ�
//
//-----------------------------------------------------------------------------
int  CMapSubProc::SetEvent(VECTOR3 vMin, VECTOR3 vMax, MATRIX4X4 mWorld, EVENTKIND nEvtKind, int nEvtNo, int nEvtOpe1, int nEvtOpe2, int nEvtKeyPush)
{
	const EVENTMAP      em;

	m_EventMap.push_back(em);

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	m_EventMap[m_nEvtIdx].m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_EventMap[m_nEvtIdx].m_pBBox->m_mWorld = mWorld;

	// �e���ڂ̐ݒ�
	m_EventMap[m_nEvtIdx].m_nEvtCycle = 0;
	m_EventMap[m_nEvtIdx].m_nEvtKind = nEvtKind;
	m_EventMap[m_nEvtIdx].m_nEvtNo = nEvtNo;
	m_EventMap[m_nEvtIdx].m_nEvtOpe1 = nEvtOpe1;
	m_EventMap[m_nEvtIdx].m_nEvtOpe2 = nEvtOpe2;
	m_EventMap[m_nEvtIdx].m_nEvtKeyPush = nEvtKeyPush;

	m_nEvtIdx++;
	return  m_nEvtIdx - 1;
}

//-----------------------------------------------------------------------------   
// �T�u�@�x���g�̍X�V�E���s
//
//-----------------------------------------------------------------------------
void  CMapSubProc::UpdateEvent()
{
	VECTOR3 vHit, vNrm;

	for (int i = 0; i < m_EventMap.size(); i++)
	{
		// PC�̃o�E���f�B���O�{�b�N�X�ɐڐG���Ă��邩�̔���
		if (m_EventMap[i].m_pBBox && m_EventMap[i].m_pBBox->OBBCollisionDetection(m_pGMain->m_pPcProc->GetPcObjPtr()->GetBBox(), &vHit, &vNrm))
		{
			// PC�̃o�E���f�B���O�{�b�N�X�ɐڐG���Ă���Ƃ�
			if (m_EventMap[i].m_nEvtCycle == 0)  // �C�x���g�T�C�N�����O�̂Ƃ�(�܂��ڐG���Ă��Ȃ������Ƃ�)
			{
				if (m_EventMap[i].m_nEvtKeyPush == 1 && !(m_pGMain->m_pDI->CheckKey(KD_DAT, DIK_RETURN) || m_pGMain->m_pDI->CheckJoy(KD_DAT, DIJ_A)))  // Enter�L�[�v�b�V�����K�v�ȂƂ�
				{
					VECTOR3 vPc = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
					vPc.y += 2.0f;
					// PC�̓���ɁAEnter�L�[�v�b�V�����s���Ă��Ȃ����̕\��������
					m_pGMain->m_pFont->Draw3D(vPc, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vEyePt, _T("Push Enter Key!"), VECTOR2(0.8f, 0.2f), RGB(255, 0, 0), 1.0f, _T("HGP�n�p�p�޼��UB"));
				}
				else {
					// �C�x���g���s
					RunEvent(m_EventMap[i]);
				}
			}
		}
		else {
			// PC�̃o�E���f�B���O�{�b�N�X�ɐڐG���Ă��Ȃ��Ƃ�
			if (m_EventMap[i].m_nEvtCycle == 2)  // �C�x���g�T�C�N�����Q�̂Ƃ�(���ɐڐG���Ă��ďI���҂��̂Ƃ�)
			{
				m_EventMap[i].m_nEvtCycle = 0;  // �C�x���g�T�C�N�����O�ɖ߂�
			}
		}
	}
}

//----------------------------------------------------------------------------- 
// �T�u�@�C�x���g�̎��s
//
// ����  EVENTMAP& EventMap:�C�x���g�}�b�v
//
//-----------------------------------------------------------------------------
void  CMapSubProc::RunEvent(EVENTMAP& EventMap)
{
	
}

//-----------------------------------------------------------------------------
// �T�u�@�ړ��}�b�v�̍X�V
//
// �ړ��}�b�v�̕��s�ړ����]�̍X�V���s��
// ���E�l�i��[���[���j�ɒB�����Ƃ��́A���]�ichange�j���s��
// ���]�ichange�j�������Ƃ��́Am_nChangeFlag�ɂP���Ԃ�
// ���[�v�����Ȃ��Ƃ��͔��]�̃^�C�~���O�Œ�~����       
//
//-----------------------------------------------------------------------------
void CMapSubProc::UpdateMoveMap()
{
}
//============================================================================
//�T�u�@�}�b�v�v���V�[�W���̃����_�����O
// 
//    �����@�@�Ȃ�
// 
//    �߂�l�@�Ȃ�
//============================================================================
void  CMapSubProc::Render(void)
{
	if (m_bActive) {


		// �}�b�v�����_�����O
		for (DWORD i = 0; i < m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 0)  // �ʏ�̃u�����h�X�e�[�g
			{
				if (m_StageMap[i].m_pMesh) m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
			else if (m_StageMap[i].m_nMaterialFlag == 2)  // �f�B�X�v���C�X�����g�}�b�s���O
			{
				// �f�B�X�v���C�X�����g�}�b�v�����_�����O
				if (m_StageMap[i].m_pMesh) 	m_StageMap[i].m_pMesh->RenderDisplace(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
		}

		// �ړ��}�b�v�����_�����O     * ���̃v���O�����ł͎g�p���Ă��Ȃ�
		for (DWORD i = 0; i < m_MoveMap.size(); i++)
		{
			if (m_MoveMap[i].m_nMaterialFlag == 0)  // �ʏ�̃u�����h�X�e�[�g
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->Render(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
			else if (m_MoveMap[i].m_nMaterialFlag == 2)  // �f�B�X�v���C�X�����g�}�b�s���O
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->RenderDisplace(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
		}

	}
}

//============================================================================
//�T�u�@�}�b�v�v���V�[�W���̃����_�����O ���̂Q
// 
//  �������̃}�b�v�I�u�W�F�N�g��`�悷�邽�߁A�僋�[�v�̍Ō�Ɏ��s�����
// 
//    �����@�@�Ȃ�
// 
//    �߂�l�@�Ȃ�
//============================================================================
void  CMapSubProc::Render2(void)
{
	if (m_bActive) {

		// �}�b�v�����_�����O
		for (DWORD i = 0; i < m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 1)  // �����F�̃u�����h�X�e�[�g
			{
				// �����F�̃����_�����O
				if (m_StageMap[i].m_pMesh) m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt);
			}
		}

		// �ړ��}�b�v�����_�����O     * ���̃v���O�����ł͎g�p���Ă��Ȃ�
		for (DWORD i = 0; i < m_MoveMap.size(); i++)
		{
			if (m_MoveMap[i].m_nMaterialFlag == 1)  // �����F�̃u�����h�X�e�[�g
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->Render(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
		}

		// �g�̃����_�����O
		for (DWORD i = 0; i < m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 3)
			{
				// �g�����_�����O
				if (m_StageMap[i].m_pWave)
					m_StageMap[i].m_pWave->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
		}

	}
}


