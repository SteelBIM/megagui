#pragma once


// CDlgLang �Ի���

class CDlgLang : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLang)

public:
	CDlgLang(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLang();

// �Ի�������
//enum { IDD = IDD_DLG_LANGUAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_lang;
	afx_msg void OnBnClickedOk();
};
