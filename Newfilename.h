#pragma once


// CNewfilename �Ի���

class CNewfilename : public CDialog
{
	DECLARE_DYNAMIC(CNewfilename)

public:
	CNewfilename(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewfilename();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_filename;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
