#pragma once


// NodeLoad2 �Ի���

class NodeLoad2 : public CDialog
{
	DECLARE_DYNAMIC(NodeLoad2)

public:
	NodeLoad2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~NodeLoad2();

// �Ի�������
	enum { IDD = IDD_MEGA_LOAD3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
