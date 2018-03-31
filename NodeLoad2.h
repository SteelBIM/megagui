#pragma once


// NodeLoad2 对话框

class NodeLoad2 : public CDialog
{
	DECLARE_DYNAMIC(NodeLoad2)

public:
	NodeLoad2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~NodeLoad2();

// 对话框数据
	enum { IDD = IDD_MEGA_LOAD3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
