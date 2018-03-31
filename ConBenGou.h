#pragma once
#include "afxwin.h"


// ConBenGou 对话框

class ConBenGou : public CDialog
{
	DECLARE_DYNAMIC(ConBenGou)

public:
	ConBenGou(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ConBenGou();

// 对话框数据
	enum { IDD = IDD_CON_MODEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	void initlist();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CListCtrl m_con_list;
	afx_msg void OnPaint();
	CStatic m_draw;
	float e1[26];
	float f1[26];
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedConList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickConlist(NMHDR *pNMHDR, LRESULT *pResult);
	float m_ec;
	float m_qc;
	afx_msg void OnBnClickedChange();
	int currentline;

	afx_msg void OnBnClickedCal();
	int m_grade;
	afx_msg void OnCbnSelchangeComboGrade();
	void DrawDc(CDC *dc1,CRect& rc);
	void SaveBitmap();
	CComboBox m_comb_grade;
};
