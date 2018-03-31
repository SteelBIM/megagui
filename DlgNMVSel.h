#pragma once
#include "afxcmn.h"


// CDlgNMVSel �Ի���

class CDlgNMVSel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNMVSel)

public:
	CDlgNMVSel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgNMVSel();

// �Ի�������
	enum { IDD = IDD_DLG_NEILI_SEL };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
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
