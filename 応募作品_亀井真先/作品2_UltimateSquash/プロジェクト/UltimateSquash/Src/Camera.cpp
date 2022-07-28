//=============================================================================
//
//		�J��������
//
//		(���_�ύX�����E��Q����������������Ă���)
//
//																Camera.cpp
//=============================================================================
#include  "Camera.h"
#include  "Playchar.h"
#include  "Map.h"


//==========================================================================================================================
//
// �J�����v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// -------------------------------------------------------------------------------------------------------------------------
CCameraProc::CCameraProc(CGameMain* pGMain) : CBaseProc(pGMain)
{


	m_pObjArray.push_back(new CCameraObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g��o�^����
	((CCameraObj*)m_pObjArray[0])->CameraSetStatus(CAMERA_STATUS);
	m_pObjArray[0]->SetPlayerNo(FIRSTPLAYER);
	m_pObjArray.push_back(new CCameraObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g��o�^����
	((CCameraObj*)m_pObjArray[1])->CameraSetStatus(CAMERASECOND_STATUS);
	m_pObjArray[1]->SetPlayerNo(SECONDPLAYER);

}


// ---------------------------------------------------------------------------
//
// �J�����I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CCameraObj::CCameraObj(CGameMain* pGMain) : CBaseObj(pGMain)
{

}

//==========================================================================================================================
//
// �J�����v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// -------------------------------------------------------------------------------------------------------------------------
void CCameraObj::CameraSetStatus(CPcObj* pPcObjSet,VECTOR3* pvEyePtSet, VECTOR3* pvLookatPtSet, MATRIX4X4* pmViewSet)
{

	pPcObj = pPcObjSet;
	pvEyePt = pvEyePtSet;
	pvLookatPt = pvLookatPtSet;
	pmView = pmViewSet;

	// �J��������t���O
	m_nCtrl = 0;

	// ��_���[���h�}�g���b�N�X�̏����l
	m_mBaseWorld = XMMatrixTranslation(0, 0, 0);

	// ��_���[���h�}�g���b�N�X����̕ψʏ����l�̐ݒ�
	// �@ TPS���_�̂Ƃ��̊�_���[���h�}�g���b�N�X����̕ψʒl
	// �E�����_�́A�ψʋ�����m_vBaseLocalLookatTPS�ɐݒ肷��
	m_vBaseLocalLookatTPS = VECTOR3(0.0f, pPcObj->GetBBox()->m_vMax.y, 0.0f);

	// �E���_�́A�ψʊp�x�w�C�x��m_vBaseLocalEyeRotDistTPS.x m_vBaseLocalEyeRotDistTPS.y�ɁA�ψʒ���������m_vBaseLocalEyeRotDistTPS.z�ɐݒ肷��
	m_vBaseLocalEyeRotDistTPS.z = -7.0f;  // �ψʒ�������
	m_vBaseLocalEyeRotDistTPS.x = XMConvertToDegrees(atan2f(pPcObj->GetBBox()->m_vMax.y + 0.3f, -m_vBaseLocalEyeRotDistTPS.z)); // �ψʊp�x�w
	m_vBaseLocalEyeRotDistTPS.y = 0.0f;   // �ψʊp�x�x

	// �A FPS���_�̂Ƃ��̊�_���[���h�}�g���b�N�X����̕ψʒl
	// �E�����_�E���_���ɁA�ψʋ�����m_vBaseLocalEyeFPS�ɐݒ肷��
	m_vBaseLocalLookatFPS = VECTOR3(0.0f, 1.5f, 7.0f);
	m_vBaseLocalEyeFPS = VECTOR3(0.0f, 1.5f, 0.3f);

	// �J�����ψʏ����l��ݒ肷��
	SetCamBase();

}


// ---------------------------------------------------------------------------
//
// �J�����I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CCameraObj::~CCameraObj()
{
	;
}
//----------------------------------------------------------------------------- 
// �J�����I�u�W�F�N�g�̐���
//
//�@�o�b�̓����ɍ��킹�ăJ�����𐧌䂷��
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::Update()
{
	// �����_�E���_�̊�_�ƂȂ��_���[���h�}�g���b�N�X�̐ݒ�
	// (�����ł́A�o�b�̃��[�J�����}�g���b�N�X��ݒ肷��)
	m_mBaseWorld = pPcObj->GetLocalMatrix();

	// �J�����I�u�W�F�N�g�̈ʒu���蓮����
	// �܂��A�J���������ύX�i�s�o�r���_���e�o�r���_���j

	// �����_�̃x�N�g�����쐬���鏈��
	// (�����_�̃��[�J�����W�Ɗ�_���[���h�}�g���b�N�X���|�����킹�A�����_�}�g���b�N�X�𓾂�)
	MATRIX4X4 mLookat = XMMatrixTranslationFromVector(m_vLocalLookat) * m_mBaseWorld;
	*pvLookatPt = GetPositionVector(mLookat);    // �����_�}�g���b�N�X���璍���_�ʒu�𓾂�


	m_vLocalEye.z = -7;

	// �J�����i���_�j�x�N�g�����쐬���鏈��
	// (�J�����i���_�j�̃��[�J�����W�Ɗ�_���[���h�}�g���b�N�X���|�����킹�A���_�}�g���b�N�X�𓾂�)
	MATRIX4X4 mEye = XMMatrixTranslationFromVector(m_vLocalEye) * m_mBaseWorld;
	*pvEyePt = GetPositionVector( mEye );        // ���_�}�g���b�N�X���王�_�ʒu�𓾂�
	pvEyePt->y = 4.5f;
	// TPS���_�̎��A��Q����������鏈��
	if (m_nCtrl == 0) EvasiveObstacle();

	// ���_�x�N�g���ƒ����_�x�N�g������J�����̃��[���h�}�g���b�N�X�𓾂�i���͎g�p���Ă��Ȃ��j
	m_mWorld = GetLookatMatrix(*pvEyePt, *pvLookatPt);

	// �r���[�}�g���b�N�X�̍쐬
	VECTOR3 vUpVec(0.0f, 1.0f, 0.0f);    // ����ʒu���΍��W�̏�����Ƃ���
	// �J����(���_)�̈ʒu�A������A����ђ����_���g�p���āA������W�n�̃r���[�s����쐬
	*pmView = XMMatrixLookAtLH(*pvEyePt, *pvLookatPt, vUpVec);


}
//-----------------------------------------------------------------------------
// ��Q����������鏈��
//
// �E���_�ƒ����_�Ƃ̊Ԃɏ�Q�����������ꍇ�A���_����Q���̑O�Ɉړ����鏈��
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::EvasiveObstacle()
{
	VECTOR3 vHit;
	VECTOR3 vNorm;
	if (m_pGMain->m_pMapProc->Hitcheck(*pvEyePt, *pvLookatPt, &vHit, &vNorm))   // ��Q���Ƃ̐ڐG�`�F�b�N
	{
		MATRIX4X4 mTemp;
		mTemp = GetLookatMatrix(vHit, *pvLookatPt);        // ��Q���Ƃ̐ڐG�_���璍���ʒu������}�g���b�N�X
		mTemp = XMMatrixTranslation(0.0f, 0.0f, 0.01f) * mTemp;      // ��Q���Ƃ̐ڐG�_����1cm���������Ɉړ��������_�ʒu�𓾂�
		m_pGMain->m_vEyePt = GetPositionVector(mTemp);
	}
}

//-----------------------------------------------------------------------------
// �s�o�r�̂Ƃ��J�����ʒu�̐ݒ菈��
//
//   m_vLocalEyeRotDist.x��m_vLocalEyeRotDist.y�ɉ�]�p�x�Am_vLocalEyeRotDist.z��
//   �����_���王�_�܂ł̒��������������Ă���A
//   ���̒l�ɁA�����̉�]�Ƌ��������Z���A���̌��ʂ���ɁA�ψʒl���v�Z���A
//   ���̌��ʂ�m_vLocalEye�ɐݒ肷��
//
//   ����	float fRotY : �x��]
//			float fRotX : �w��]
//			float fDist : ����
//
//   �߂�l�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::SetLocalEyeTPS(float fRotY, float fRotX, float fDist)
{
	m_vLocalEyeRotDist.x += fRotX;
	m_vLocalEyeRotDist.y += fRotY;
	m_vLocalEyeRotDist.z += fDist;

	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(m_vLocalEyeRotDist.y));
	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(m_vLocalEyeRotDist.x));
	MATRIX4X4 mPos = XMMatrixTranslation(0, 0, m_vLocalEyeRotDist.z);
	mPos = mPos * mRotX * mRotY;
	m_vLocalEye = GetPositionVector(mPos);
}
//-----------------------------------------------------------------------------
// �J�����ψʏ����l��ݒ肷�鏈��
//
// �@ TPS���_�̂Ƃ�
//    ���_�́A�ψʊp�x�ƕψʒ����������A��Um_vLocalEyeRotDist�ɐݒ肵�A
//    ���̌�SetLocalEyeTPS�֐��ɂ���āAm_vLocalEye�ɐݒ肷��
//    �����_�́A�ψʋ�����m_vLocalLookatTPS�ɐݒ肷��
//
// �A FPS���_�̂Ƃ�
//    ���_�́A�ψʋ�����m_vLocalEye�ɐݒ肷��
//    �����_�́A�ψʋ�����m_vLocalLookat�ɐݒ肷��
//
//   ����	�Ȃ�
//
//   �߂�l�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::SetCamBase()
{
	// �J�����ψʂ̏����l��ݒ肷��
	if (m_nCtrl == 0)
	{
		m_vLocalEyeRotDist = m_vBaseLocalEyeRotDistTPS;
		m_vLocalLookat = m_vBaseLocalLookatTPS;
		SetLocalEyeTPS(0, 0, 0);
	}
	else {
		m_vLocalEye = m_vBaseLocalEyeFPS;
		m_vLocalLookat = m_vBaseLocalLookatFPS;
	}
}


