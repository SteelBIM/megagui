#pragma once


// CSectionSel �Ի���

class CSectionSel : public CDialog
{
	DECLARE_DYNAMIC(CSectionSel)

public:
	CSectionSel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSectionSel();

// �Ի�������
	enum { IDD = IDD_DLG_SECTSEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSect1();
	afx_msg void OnBnClickedSect2();
	afx_msg void OnBnClickedSect3();
	afx_msg void OnBnClickedSect4();
	afx_msg void OnBnClickedSect5();
	afx_msg void OnBnClickedSect6();
	afx_msg void OnBnClickedSect7();
	afx_msg void OnBnClickedSect8();
	virtual BOOL OnInitDialog();
	void ReadGloblePara(int Sectkind);
	void WriteGloblePara(int Sectkind);
	CString GetInitFileName(void);
};
