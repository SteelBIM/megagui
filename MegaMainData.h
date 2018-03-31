#pragma once

#include "GlobalPara.h"
// MegaMainData 对话框

class MegaMainData : public CDialog
{
	DECLARE_DYNAMIC(MegaMainData)

public:
	MegaMainData(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MegaMainData();

// 对话框数据
	enum { IDD = IDD_MEGA_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	float m_bklen;
	float m_lens;
	int m_support;

	CBitmap bitmap1;
	CBitmap bitmap2;
	afx_msg void OnBnClickedSimplesupport();
	afx_msg void OnBnClickedCantilever();
	int m_stud_d;
	int m_stud_l;
	float m_stud_fu;
	float m_stud_fy;
	int m_aixal;
	afx_msg void OnEnChangeLen();
	bool ifcantilever;
};
