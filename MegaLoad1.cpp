// MegaLoad1.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "MegaLoad1.h"
#include "afxdialogex.h"
extern "C" void MegaLoad1Dlg(){
	MegaLoad1 pDlg;
	pDlg.DoModal();
}

// MegaLoad1 对话框

IMPLEMENT_DYNAMIC(MegaLoad1, CDialog)

MegaLoad1::MegaLoad1(CWnd* pParent /*=NULL*/)
	: CDialog(MegaLoad1::IDD, pParent)
{

}

MegaLoad1::~MegaLoad1()
{
}

void MegaLoad1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MegaLoad1, CDialog)
	ON_BN_CLICKED(IDOK, &MegaLoad1::OnBnClickedOk)
END_MESSAGE_MAP()


// MegaLoad1 消息处理程序


void MegaLoad1::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
