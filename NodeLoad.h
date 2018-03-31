#pragma once


// NodeLoad 对话框

class NodeLoad : public CDialog
{
	DECLARE_DYNAMIC(NodeLoad)

public:
	NodeLoad(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~NodeLoad();

// 对话框数据
	enum { IDD = IDD_MEGA_LOAD2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
