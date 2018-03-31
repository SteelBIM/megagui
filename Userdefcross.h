#pragma once
#include "SectCommon.h"

// CUserdefcross 对话框

class CUserdefcross : public CDialog
{
	DECLARE_DYNAMIC(CUserdefcross)

public:
	CUserdefcross(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserdefcross();

// 对话框数据
	enum { IDD = IDD_DLG_USERDEF_CROSS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	SECTIONS UserDefSect;
	int m_sect_b;
	int m_sect_h;
	float m_sect_tf;
	float m_sect_tw;
};
