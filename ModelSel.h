#pragma once


// CModelSel 对话框

class CModelSel : public CDialog
{
	DECLARE_DYNAMIC(CModelSel)

public:
	CModelSel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModelSel();

// 对话框数据
	enum { IDD = IDD_Model };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConModel();
	afx_msg void OnBnClickedProModel();
	virtual BOOL OnInitDialog();
};
