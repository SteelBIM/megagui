#pragma once


// WelcomeDlg �Ի���

class WelcomeDlg : public CDialog
{
	DECLARE_DYNAMIC(WelcomeDlg)

public:
	WelcomeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WelcomeDlg();

// �Ի�������
	enum { IDD = IDD_MEGA_WELCOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
