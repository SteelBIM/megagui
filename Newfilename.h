#pragma once


// CNewfilename 对话框

class CNewfilename : public CDialog
{
	DECLARE_DYNAMIC(CNewfilename)

public:
	CNewfilename(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewfilename();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_filename;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
