#pragma once


// CDesignPara 对话框

class CDesignPara : public CDialog
{
	DECLARE_DYNAMIC(CDesignPara)

public:
	CDesignPara(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDesignPara();

// 对话框数据
	enum { IDD = IDD_Design_Parameter };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	float m_rQ;
	float m_rM1;
	float m_rM0;
	float m_rGSup;
	float m_rGinf;
	int m_2effect;
	int m_crackcheck;
	int m_nmmethod;

	int m_shear_method;
	afx_msg void OnCbnSelchangeShear();
	float m_rQ2;
	CComboBox m_con_model;
	float m_rc;
	float m_rs;
	CComboBox m_sectlist;
	int SecSel;	
	
	float m_conc_mesh;
	float m_profile_mesh;
	afx_msg void OnCbnSelchangeSectList();
	void GetParaLimit(int type,int& FiberMax,int& FiberMin,int& ShearMax,int& ShearMin);
	
	void SetParaStatus(int type);
	afx_msg void OnCbnSelchangeNmMethod();
};
