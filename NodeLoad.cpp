// NodeLoad.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "NodeLoad.h"
#include "afxdialogex.h"


// NodeLoad �Ի���

IMPLEMENT_DYNAMIC(NodeLoad, CDialog)

NodeLoad::NodeLoad(CWnd* pParent /*=NULL*/)
	: CDialog(NodeLoad::IDD, pParent)
{

}

NodeLoad::~NodeLoad()
{
}

void NodeLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NodeLoad, CDialog)
	ON_BN_CLICKED(IDOK, &NodeLoad::OnBnClickedOk)
END_MESSAGE_MAP()


// NodeLoad ��Ϣ�������


void NodeLoad::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}
