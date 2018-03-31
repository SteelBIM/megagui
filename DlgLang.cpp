// DlgLang.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "DlgLang.h"
#include "afxdialogex.h"


// CDlgLang 对话框

IMPLEMENT_DYNAMIC(CDlgLang, CDialogEx)

CDlgLang::CDlgLang(CWnd* pParent /*=NULL*/)
	 
{

}

CDlgLang::~CDlgLang()
{
}

void CDlgLang::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_CBIndex(pDX, IDC_COMBO_LAN, m_lang);
}


BEGIN_MESSAGE_MAP(CDlgLang, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgLang::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLang 消息处理程序


void CDlgLang::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
