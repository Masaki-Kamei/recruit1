//=============================================================================
//		プレイキャラクター　ヘッダファイル							Playchar.h
//=============================================================================
#pragma once
#include "GameMain.h"


//======================================================================
// プレイキャラクター　オブジェクトクラス
//======================================================================
class CPcObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;			// Fbxスキンメッシュ
	BASEHOLDITEM        m_nHoldItem;		// 手に持つスキル
	float				m_fLocalRotY;		// ローカル軸(Y軸)   
	BOOL				m_bSide;			// 横移動モード 

	float				m_fSpeed;			// 移動速度         
	float				m_fRotSpeed;		// 回転速度        
	float				m_fJumpSpeed;		// ジャンプ速度   
	float				m_fNormalSpeed;			// 最初に設定した速度       

	int					m_nWeaponNo;		//スキルのナンバー	
	int					m_nWeaponColuman;		//スキル欄	 
	int					m_nWeaponColumanNo[10];		//スキル欄に入っているスキルのナンバー		

	int					SaveEndFrame;	//アニメーションフレームの数
	int					m_nFrameTrigger;	//アニメーションフレームのトリガー	
	
	BOOL				bSwordHitTrigger;

	int					nSkillTime[3];			//スキルのスキル時間		
	int					nCount[3];				//60フレームで一秒数えるための変数	
	BOOL				bSkillActive[3];		//スキル発動中			
	BOOL				bSpeedSkillTrigger;		//スピードアップ使用中
	DWORD				dwUseNumSkill;			//使用したスキルの回数	

	BOOL				bBoolSkillTrigger;		//ボールスキル使用中

	DWORD				dwRotCount;
	DWORD				dwRotTrigger;

	int	test;
	
	AFTERSTATUS			AfterSta;				//残像のステータス
	int					nAfterCount;			//残像一つの間隔
	int				    nAftTime;					//残像のためのカウント

public:
	void Update() override;
	void UpdateNormal();       
	void UpdateNormalMove();  
	MATRIX4X4 UpdateNormalMoveKeystate(DWORD DIKey); 
	MATRIX4X4 UpdateNormalFirstPCMove(MATRIX4X4 mPos);  
	MATRIX4X4 UpdateNormalSecondPCMove(MATRIX4X4 mPos); 
	void SwingMoveFirst();
	void SwingMoveSecond();

	void UpdateNormalAttack(); 
	void UpdateDamage();       
	void SetMesh(CPcProc* pProc);
	void SetMeshSecond(CPcProc* pProc);
	MATRIX4X4  GetLocalMatrix();			// ローカル軸マトリックスを得る
	void SetLocalRotY(float fRotY) { m_fLocalRotY = fRotY; }   // ローカル軸(Y軸)をセットする

	void	 SetWeaponNo(int No) { m_nWeaponNo = No; }		//スキルのナンバーを入れ替え		
	int		 GetWeaponNo() { return m_nWeaponNo; }			//スキルのナンバーを取得		

	void	 SetWeaponColuman(int n) { m_nWeaponColuman=n; }
	int		 GetWeaponColuman() { return m_nWeaponColuman; }			//スキル欄を取得			

	void	 SetSaveEndFrame(int n) { SaveEndFrame = n; }	
	int		 GetSaveEndFrame() { return SaveEndFrame; }		

	void	 SetFrameTrigger(int n) { m_nFrameTrigger = n; }	
	int		 GetFrameTrigger() { return m_nFrameTrigger; }	

	void	SetSwordHitTrigger(BOOL Trigger) { bSwordHitTrigger = Trigger; }
	BOOL	GetSwordHitTrigger() { return bSwordHitTrigger; }

	int		GetSkillActive(int nWeaponColumanNo) { return bSkillActive[nWeaponColumanNo]; }

	void	SpeedUpAft();
	void	SetSkillNo(const int nSkillColumanNo);
	void	SwingAnimProcess(const int nSwingAnimNo);

	BOOL	SkillStart(const int nWeaponColumanNo) ;	
	void	SkillUpdate();				
	void	SkillTime(const int nWeaponColumanNo);
	DWORD	GetUseNumSkill() { return dwUseNumSkill; }
	void	SetUseNumSkill(DWORD dwNum) { dwUseNumSkill = dwNum; }

	BOOL	GetBoolSkillTrigger() { return bBoolSkillTrigger; }
	DWORD	GetWeaponColumanNo(DWORD No) { return m_nWeaponColumanNo[No]; }
	void	SetWeaponColumanNo(DWORD No, DWORD nWeaponColumanNo) { m_nWeaponColumanNo[No] = nWeaponColumanNo; }
	void	WeaponUseMulti();
	void	Init();		

	CPcObj(CGameMain* pGMain);	// コンストラクタ
	virtual	~CPcObj();
};

//======================================================================
// プレイキャラクター　プロシージャクラス
//======================================================================
class CPcProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;				// Fbxスキンメッシュ
	CFbxMesh*           m_pMeshSecond;				// Fbxスキンメッシュ
	BASEHOLDITEM        m_nHoldItem;			// 手に持つスキル
	int				    m_nPcNum;



public:
	// アクセス関数
	CFbxMesh*           GetMesh() { return m_pMesh; }		// Fbxスキンメッシュ
	CFbxMesh*           GetMeshSecond() { return m_pMeshSecond; }		// Fbxスキンメッシュ
	BASEHOLDITEM        GetHoldItem() { return m_nHoldItem; }	// 手に持つアイテムの値
	CPcObj*			    GetPcObjPtr() { return (CPcObj*)GetObjArrayPtr()[0]; }
	int				    GetPcNum() { return m_nPcNum; }
	void				AddPcNum(int Num) { m_nPcNum += Num; }

	CPcObj*			    GetPcSecObjPtr() { return (CPcObj*)GetObjArrayPtr()[1]; }


	// コンストラクタ
	CPcProc(CGameMain* pGMain);
	virtual	~CPcProc();
};
