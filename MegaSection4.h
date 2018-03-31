#pragma once
#include "SectCtrl.h"
// CMegaSection4 对话框

class CMegaSection4 : public CDialog , public SectCtrl
{
	DECLARE_DYNAMIC(CMegaSection4)

public:
	CMegaSection4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMegaSection4();

// 对话框数据
	enum { IDD = IDD_DLG_SECTION4 };

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
	bool update;
public:
	BOOL PreTranslateMessage(MSG* pMsg);   
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedUserDef4();
	afx_msg void OnBnClickedChooseProfile();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeNoY();
	afx_msg void OnCbnSelchangeNoX();
	afx_msg void OnCbnSelchangeBarD();
//	afx_msg void OnCbnSelchangeBarMp();
//	afx_msg void OnCbnSelchangeConClass();
	afx_msg void OnCbnSelchangeSteelFy();
	afx_msg void OnCbnSelchangeStruClass();
	afx_msg void OnCbnSelchangeExpClass();
	int m_sect4_Dext;
	CComboBox m_stru_class;
	CComboBox m_exp_class;
	int m_cnom;
	int m_cs;
	CComboBox m_con_class;
	CComboBox m_steel_fy;
	CComboBox m_bar_d;

	int m_no_x;
	int m_profile_c;
private:
	int SetBarMp(int BarMp);
	int SetBarD(int BarD);
	 
	void initSteel();
public:
	int m_bar_mp_new;
	int m_stud_d;
	float m_stud_fu;
	float m_stud_fy;
	float m_stud_l;
	int m_tranbar_mp;
	CComboBox m_steel_code;
	float m_tranratio_yy;
	float m_tranratio_zz;
	void SetGlobalPara(void);
	void DrawSectOnPic(void);
	afx_msg void OnCbnSelchangeSteelFy3();
	afx_msg void OnPaint();
	afx_msg void OnEnKillfocusS4D();
	afx_msg void OnEnKillfocusBarX();
	afx_msg void OnEnKillfocusPC();
//	afx_msg void OnStnClickedCalMethod();
//	afx_msg void OnCbnKillfocusConClass();
	afx_msg void OnCbnSelchangeConClass();
	afx_msg void OnEnKillfocusEditCs();
};
