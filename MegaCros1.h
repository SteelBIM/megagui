#pragma once


// MegaCros1 �Ի���

class MegaCros1 : public CDialog
{
	DECLARE_DYNAMIC(MegaCros1)

public:
	MegaCros1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MegaCros1();

// �Ի�������
	enum { IDD = IDD_MEGA_CROS1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
