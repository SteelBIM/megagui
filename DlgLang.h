#pragma once


// CDlgLang 对话框

class CDlgLang : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLang)

public:
	CDlgLang(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLang();

// 对话框数据
//enum { IDD = IDD_DLG_LANGUAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_lang;
	afx_msg void OnBnClickedOk();
};
