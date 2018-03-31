// MegaCros1.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "MegaCros1.h"
#include "afxdialogex.h"

extern "C" void MegaCros1Dlg(){
	MegaCros1 pDlg;
	pDlg.DoModal();
}
// MegaCros1 对话框

IMPLEMENT_DYNAMIC(MegaCros1, CDialog)

MegaCros1::MegaCros1(CWnd* pParent /*=NULL*/)
	: CDialog(MegaCros1::IDD, pParent)
{

}

MegaCros1::~MegaCros1()
{
}

void MegaCros1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MegaCros1, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MegaCros1::OnBnClickedButton1)
END_MESSAGE_MAP()


// MegaCros1 消息处理程序


void MegaCros1::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
