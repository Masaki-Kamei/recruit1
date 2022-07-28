//=============================================================================
//
//		�J��������
//
//		(���_�ύX�����E��Q����������������Ă���)
//
//																Camera.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include"Playchar.h"

#define	CAMERA_STATUS			m_pGMain->m_pPcProc->GetPcObjPtr(),&m_pGMain->m_vEyePt,&m_pGMain->m_vLookatPt,&m_pGMain->m_mView
#define	CAMERASECOND_STATUS		m_pGMain->m_pPcProc->GetPcSecObjPtr(),&m_pGMain->m_vEyePtSecond,&m_pGMain->m_vLookatPtSecond,&m_pGMain->m_mViewSecond

//======================================================================
// �J�����@�I�u�W�F�N�g�N���X
//======================================================================
class CCameraObj : public CBaseObj
{
protected:
	int     m_nCtrl;                       // �J��������
	MATRIX4X4 m_mBaseWorld;                // �����_�E���_�̊�_�ƂȂ��_���[���h�}�g���b�N�X
	VECTOR3 m_vLocalLookat;                // ���[�J�������_�x�N�g��
	VECTOR3 m_vLocalEye;                   // ���[�J�����_�x�N�g��
	VECTOR3 m_vLocalEyeRotDist;            // ���[�J�����_�x�N�g���𐶐����邽�߂̊p�x�ƕψ�(TPS�̂�)
	VECTOR3 m_vBaseLocalLookatTPS;         // ���[�J�������_�x�N�g�������l TPS
	VECTOR3 m_vBaseLocalEyeRotDistTPS;     // ���[�J�����_�x�N�g�������l(�p�x�ƕψ�) TPS
	VECTOR3 m_vBaseLocalLookatFPS;         // ���[�J�������_�x�N�g�������l FPS
	VECTOR3 m_vBaseLocalEyeFPS;            // ���[�J�����_�x�N�g�������l FPS
	CPcObj*	pPcObj;

	VECTOR3*		pvEyePt;		//�J�����i���_�j�ʒu
	VECTOR3*        pvLookatPt;		//�����ʒu
	MATRIX4X4*      pmView;

public:
	virtual void Update() override;
	virtual void EvasiveObstacle();
	virtual void SetLocalEyeTPS(float fRotY, float fRotX, float fDist);
	virtual void SetCamBase();
	virtual int  GetCtrl() { return m_nCtrl; }
	void CameraSetStatus(CPcObj* pPcObjSet,VECTOR3* pvEyePtSet, VECTOR3* pvLookatPtSet, MATRIX4X4* pmViewSet);

	CCameraObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CCameraObj();
};


//======================================================================
// �J�����@�v���V�[�W���N���X
//======================================================================
class CCameraProc : public CBaseProc
{
protected:
	;

public:
	CCameraObj*	 GetCameraObjPtr() { return (CCameraObj*)GetObjArrayPtr()[0]; }
	CCameraObj*	 GetCameraSecondObjPtr() { return (CCameraObj*)GetObjArrayPtr()[1]; }

	CCameraProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CCameraProc() { ; }
};


