#pragma once


// MegaLoad1 �Ի���

class MegaLoad1 : public CDialog
{
	DECLARE_DYNAMIC(MegaLoad1)

public:
	MegaLoad1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MegaLoad1();

// �Ի�������
	enum { IDD = IDD_MEGA_LOAD1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
