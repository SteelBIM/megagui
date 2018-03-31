#pragma once
#include "SectCtrl.h"
// CMegaSection7 �Ի���

class CMegaSection7 : public CDialog , public SectCtrl
{
	DECLARE_DYNAMIC(CMegaSection7)

public:
	CMegaSection7(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMegaSection7();

// �Ի�������
	enum { IDD = IDD_DLG_SECTION7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedUserDef7();
	afx_msg void OnBnClickedChooseProfile();
	afx_msg void OnBnClickedOk();
	//afx_msg void OnCbnSelchangeNoY();
	//afx_msg void OnCbnSelchangeNoX();
	afx_msg void OnCbnSelchangeBarD();
	
	afx_msg void OnCbnSelchangeConClass();
	
	afx_msg void OnCbnSelchangeStruClass();
	afx_msg void OnCbnSelchangeExpClass();
	int m_sect7_hc;
	int m_sect7_bc;
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
	int m_profile_c;
	int m_profile_d;
private:
	int SetBarMp(int BarMp);
	int SetBarD(int BarD);
	 
	void initSteel();
	BOOL PreTranslateMessage(MSG* pMsg);   
public:
	int m_bar_mp_new;
	int m_stud_d;
	float m_stud_fu;
	float m_stud_fy;
	int m_stud_l;
	int m_tranbar_mp;
	afx_msg void OnStnClickedArrangeBmp();
	CComboBox m_steel_code;
	float m_tranratio_yy;
	float m_tranratio_zz;
	afx_msg void OnCbnSelchangeSteelFy2();
	afx_msg void OnPaint();
	afx_msg void OnEnKillfocusS7Hc();
	afx_msg void OnEnKillfocusS7Bc();
	afx_msg void OnEnKillfocusBarY();
	afx_msg void OnEnKillfocusBarX();
	afx_msg void OnEnKillfocusPC();
	afx_msg void OnEnKillfocusPD();

	void DrawSectOnPic(void);
	void SetGlobalPara(void);

	afx_msg void OnEnKillfocusEditCsz();
	afx_msg void OnEnKillfocusEditCsy();
	
};
