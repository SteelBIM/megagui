#pragma once
#include "afxcmn.h"


// CDlgNMVSel 对话框

class CDlgNMVSel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNMVSel)

public:
	CDlgNMVSel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgNMVSel();

// 对话框数据
	enum { IDD = IDD_DLG_NEILI_SEL };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
private:
	CString m_selStr;
public:
	CListCtrl c_ListNeiLi;

public:
	void onInitCtrlList();
	virtual BOOL OnInitDialog();
	void FillList();
	CString GetSelStr();
	afx_msg void OnDblclkListNeiliTu(NMHDR *pNMHDR, LRESULT *pResult);
};
