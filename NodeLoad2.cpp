// NodeLoad2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "NodeLoad2.h"
#include "afxdialogex.h"


// NodeLoad2 �Ի���

IMPLEMENT_DYNAMIC(NodeLoad2, CDialog)

NodeLoad2::NodeLoad2(CWnd* pParent /*=NULL*/)
	: CDialog(NodeLoad2::IDD, pParent)
{

}

NodeLoad2::~NodeLoad2()
{
}

void NodeLoad2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NodeLoad2, CDialog)
	ON_BN_CLICKED(IDOK, &NodeLoad2::OnBnClickedOk)
END_MESSAGE_MAP()


// NodeLoad2 ��Ϣ�������


void NodeLoad2::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}
