#pragma once
#include "SectCtrl.h"
#include "afxwin.h"
// CMegaSection1 对话框

class CMegaSection1 : public CDialog , public SectCtrl
{
	DECLARE_DYNAMIC(CMegaSection1)

public:
	CMegaSection1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMegaSection1();

// 对话框数据
	enum { IDD = IDD_DLG_SECTION1 };

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
	//CStatic m_arr_bmp;
	//afx_msg void OnCbnSelchangeArrBmp();
	CBitmap bitmap1;
	CBitmap bitmap2;
	
	int m_sect1_Dext;
	CComboBox m_stru_class;
	CComboBox m_exp_class;
	CComboBox m_con_class;
	CComboBox m_steel_fy;
	CComboBox m_bar_d;
	
	int m_no_x;
	int m_cs;
	int m_cnom;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedUserDef();
	afx_msg void OnBnClickedChooseProfile();
	//afx_msg void OnCbnSelchangeCombo9();
	afx_msg void OnBnClickedUserDef3();
	afx_msg void OnBnClickedOk();
	//afx_msg void OnCbnSelchangeNoY();
	//afx_msg void OnCbnSelchangeNoX();
	afx_msg void OnCbnSelchangeBarD();
	
	//afx_msg void OnCbnSelchangeConClass();
	afx_msg void OnCbnSelchangeSteelFy();
	afx_msg void OnCbnSelchangeStruClass();
	afx_msg void OnCbnSelchangeExpClass();
private:
	int SetBarMp(int BarMp);
	int SetBarD(int BarD);
	
	void initSteel();
	BOOL PreTranslateMessage(MSG* pMsg);   
public:
	int m_bar_mp_new;
	CComboBox m_steel_code;
	afx_msg void OnCbnSelchangeSteelFy2();
	int m_stud_d;
	int m_stud_l;
	float m_stud_fu;
	float m_stud_fy;
	int m_tranbar_mp;
	float m_tranratio_yy;
	
	afx_msg void OnPaint();
	void DrawSectOnPic(void);
	void SetGlobalPara(void);
//	afx_msg void OnEnChangeBarX();
	afx_msg void OnEnKillfocusBarX();
	afx_msg void OnEnKillfocusS1D();
	afx_msg void OnCbnSelchangeConClass();
};
