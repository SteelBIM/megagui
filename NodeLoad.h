#pragma once


// NodeLoad �Ի���

class NodeLoad : public CDialog
{
	DECLARE_DYNAMIC(NodeLoad)

public:
	NodeLoad(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~NodeLoad();

// �Ի�������
	enum { IDD = IDD_MEGA_LOAD2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
