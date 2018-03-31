// NodeLoad.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "NodeLoad.h"
#include "afxdialogex.h"


// NodeLoad 对话框

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


// NodeLoad 消息处理程序


void NodeLoad::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
