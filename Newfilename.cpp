// Newfilename.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "Newfilename.h"
#include "afxdialogex.h"


// CNewfilename 对话框

IMPLEMENT_DYNAMIC(CNewfilename, CDialog)

CNewfilename::CNewfilename(CWnd* pParent /*=NULL*/)
	: CDialog(CNewfilename::IDD, pParent)
	, m_filename(_T(""))
{

}

CNewfilename::~CNewfilename()
{
}

void CNewfilename::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FileName, m_filename);
}


BEGIN_MESSAGE_MAP(CNewfilename, CDialog)
	ON_BN_CLICKED(IDOK, &CNewfilename::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNewfilename::OnBnClickedCancel)
END_MESSAGE_MAP()


// CNewfilename 消息处理程序


void CNewfilename::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void CNewfilename::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
