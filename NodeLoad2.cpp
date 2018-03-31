// NodeLoad2.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "NodeLoad2.h"
#include "afxdialogex.h"


// NodeLoad2 对话框

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


// NodeLoad2 消息处理程序


void NodeLoad2::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
