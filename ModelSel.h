#pragma once


// CModelSel �Ի���

class CModelSel : public CDialog
{
	DECLARE_DYNAMIC(CModelSel)

public:
	CModelSel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModelSel();

// �Ի�������
	enum { IDD = IDD_Model };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConModel();
	afx_msg void OnBnClickedProModel();
	virtual BOOL OnInitDialog();
};
