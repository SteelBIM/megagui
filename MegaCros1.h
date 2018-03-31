#pragma once


// MegaCros1 对话框

class MegaCros1 : public CDialog
{
	DECLARE_DYNAMIC(MegaCros1)

public:
	MegaCros1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MegaCros1();

// 对话框数据
	enum { IDD = IDD_MEGA_CROS1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
