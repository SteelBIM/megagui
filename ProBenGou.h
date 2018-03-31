#pragma once


// ProBenGou 对话框

class ProBenGou : public CDialog
{
	DECLARE_DYNAMIC(ProBenGou)

public:
	ProBenGou(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ProBenGou();

// 对话框数据
	enum { IDD = IDD_PRO_MODEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
//	void initlist();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CStatic m_draw;
	float e1[26];
	float f1[26];
	float m_ec;
	float m_qc;
	int currentline;
	float E1,E2;
	float Fy,Fu;
	float ecu;
	int Ctrl_curve;
	virtual BOOL OnInitDialog();
//	CListCtrl m_pro_list;
	afx_msg void OnBnClickedOk();

public:
	void CalPoint();		//通过曲线的斜率，反算离散点
	void InitPara(int Ctrl_C);
	float m_e1;
	float m_e2;
	float m_fu;
	float m_fy;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeComboCurve();
	void DrawDc(CDC *dc1,CRect& rc);
	void SaveBitmap();
	CComboBox m_curve;
};
