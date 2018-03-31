#pragma once


// WelcomeDlg 对话框

class WelcomeDlg : public CDialog
{
	DECLARE_DYNAMIC(WelcomeDlg)

public:
	WelcomeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~WelcomeDlg();

// 对话框数据
	enum { IDD = IDD_MEGA_WELCOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
