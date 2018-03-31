#pragma once


// MegaLoad1 对话框

class MegaLoad1 : public CDialog
{
	DECLARE_DYNAMIC(MegaLoad1)

public:
	MegaLoad1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MegaLoad1();

// 对话框数据
	enum { IDD = IDD_MEGA_LOAD1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
