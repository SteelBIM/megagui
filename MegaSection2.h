#pragma once
#include "SectCtrl.h"
// CMegaSection2 对话框

class CMegaSection2 : public CDialog, public SectCtrl
{
	DECLARE_DYNAMIC(CMegaSection2)

public:
	CMegaSection2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMegaSection2();

// 对话框数据
	enum { IDD = IDD_DLG_SECTION2 };

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
	afx_msg void OnBnClickedUserDef2();
	afx_msg void OnBnClickedChooseProfile();
	afx_msg void OnBnClickedOk();
	//afx_msg void OnCbnSelchangeNoY();
	//afx_msg void OnCbnSelchangeNoX();
	afx_msg void OnCbnSelchangeBarD();
	
	afx_msg void OnCbnSelchangeConClass();
	afx_msg void OnCbnSelchangeSteelFy();
	afx_msg void OnCbnSelchangeStruClass();
	afx_msg void OnCbnSelchangeExpClass();
	int m_sect2_hc;
	int m_sect2_bc;
	CComboBox m_stru_class;
	CComboBox m_exp_class;
	int m_cnom;
	int m_csz;
	int m_csy;
	CComboBox m_con_class;
	CComboBox m_steel_fy;
	CComboBox m_bar_d;
	
	int m_no_y;
	int m_no_x;
private:
	int SetBarMp(int BarMp);
	int SetBarD(int BarD);
	
	void initSteel();
public:
	int m_bar_mp_new;
	int m_stud_d;
	int m_stud_l;
	float m_stud_fu;
	float m_stud_fy;
	int m_tranbar_mp;
	CComboBox m_steel_code;
	float m_tranratio_yy;
	float m_tranratio_zz;
	afx_msg void OnCbnSelchangeSteelFy2();
	afx_msg void OnPaint();
	void SetGlobalPara(void);
	void DrawSectOnPic(void);
	afx_msg void OnEnKillfocusS2Hc();
	afx_msg void OnEnKillfocusS2Bc();
	afx_msg void OnEnKillfocusBarY();
	afx_msg void OnEnKillfocusBarX();
};
