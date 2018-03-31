#pragma once
#include "SectCtrl.h"
// CMegaSection3 对话框

class CMegaSection3 : public CDialog , public SectCtrl
{
	DECLARE_DYNAMIC(CMegaSection3)

public:
	CMegaSection3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMegaSection3();

// 对话框数据
	enum { IDD = IDD_DLG_SECTION3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int v_bar_x;
	int v_bar_y;
	int v_bar_d;
	int v_bar_mp;	
	int v_steel_fy;
	int v_stru_class;
	int v_exp_class;
	int v_steel_code;
	CString ProName;

public:
	virtual BOOL OnInitDialog();
//	afx_msg void OnCbnSelchangeCombo9();
	afx_msg void OnBnClickedUserDef3();
	afx_msg void OnBnClickedChooseProfile();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeBarD();
	afx_msg void OnCbnSelchangeBarMp();
	afx_msg void OnCbnSelchangeConClass();
	afx_msg void OnCbnSelchangeSteelFy();
	afx_msg void OnCbnSelchangeStruClass();
	afx_msg void OnCbnSelchangeExpClass();

	int m_sect3_bc;
	int m_sect3_hc;
	int m_profile_c;
	int m_profile_d;
	int m_cnom;
	int m_no_x;
	int m_no_y;
	int m_csz;
	int m_csy;

//	CComboBox m_steel_arr;
	
	
	CComboBox m_steel_fy;
	CComboBox m_bar_d;
	
	CComboBox m_exp_class;
	CComboBox m_stru_class;
	CComboBox m_con_class;
	CComboBox m_steel_code;

// 	CBitmap bitmap1;
// 	CBitmap bitmap2;
private:
	BOOL PreTranslateMessage(MSG* pMsg);   
	int SetBarMp(int BarMp);
	int SetBarD(int BarD);
	
	void initSteel();
	
	bool update;
public:
	int m_bar_mp_new;
	afx_msg void OnCbnSelchangeSteelFy2();
	float m_trans_ratio;
	int m_stud_d;
	float m_stud_fu;
	float m_stud_fy;
	int m_stud_l;
	int m_tranbar_mp;
	float m_tranratio_yy;
	float m_tranratio_zz;
	afx_msg void OnEnKillfocusS3Hc();
	afx_msg void OnEnKillfocusS3Bc();
	afx_msg void OnEnKillfocusBarY();
	afx_msg void OnEnKillfocusBarX();
	afx_msg void OnEnKillfocusPC();
	afx_msg void OnEnKillfocusPD();
	afx_msg void OnPaint();
	void DrawSectOnPic(void);
	void SetGlobalPara(void);

	afx_msg void OnEnKillfocusEditCsz();
	afx_msg void OnEnKillfocusEditCsy();
};

