// WelcomeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "WelcomeDlg.h"
#include "afxdialogex.h"


// WelcomeDlg 对话框

IMPLEMENT_DYNAMIC(WelcomeDlg, CDialog)

WelcomeDlg::WelcomeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(WelcomeDlg::IDD, pParent)
{

}

WelcomeDlg::~WelcomeDlg()
{
}

void WelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WelcomeDlg, CDialog)
END_MESSAGE_MAP()


// WelcomeDlg 消息处理程序
