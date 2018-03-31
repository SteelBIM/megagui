// Userdefcross.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "Userdefcross.h"
#include "afxdialogex.h"
extern "C" __declspec( dllexport )  void __stdcall CustomSect(SECTION1 &SECT)
{
	CUserdefcross pdlg;
	if(IDOK == pdlg.DoModal())
	{
		int tf = int(pdlg.m_sect_tf);
		int tw = int(pdlg.m_sect_tw);
		SECT.K = 2;
		SECT.B = short(tw);
		SECT.H = short(pdlg.m_sect_h);
		SECT.U = short(pdlg.m_sect_b);
		SECT.D = short(pdlg.m_sect_b);
		SECT.F = short(tf);
		SECT.T = short(tf);
		//		SECT.L = short(hh.tw);
		SECT.M = 5;
		CString name;
		name.Format(_T("%dx%dx%dx%d"),pdlg.m_sect_h,pdlg.m_sect_b,tf,tw);
		memcpy(SECT.NAME,name,sizeof(char)*16);
	}
}

// CUserdefcross 对话框

IMPLEMENT_DYNAMIC(CUserdefcross, CDialog)

CUserdefcross::CUserdefcross(CWnd* pParent /*=NULL*/)
	: CDialog(CUserdefcross::IDD, pParent)
{

	m_sect_b = 476;
	m_sect_h = 600;
	m_sect_tf = 140.0f;
	m_sect_tw = 100.0f;
}

CUserdefcross::~CUserdefcross()
{
}

void CUserdefcross::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DEF_B, m_sect_b);
	DDX_Text(pDX, IDC_DEF_H, m_sect_h);
	DDX_Text(pDX, IDC_DEF_TF, m_sect_tf);
	DDX_Text(pDX, IDC_DEF_TW, m_sect_tw);
}


BEGIN_MESSAGE_MAP(CUserdefcross, CDialog)
	ON_BN_CLICKED(IDOK, &CUserdefcross::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUserdefcross::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUserdefcross 消息处理程序


void CUserdefcross::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UserDefSect.B1 = m_sect_b;
	UserDefSect.H1 = m_sect_h;
	UserDefSect.RI = m_sect_tw;
	UserDefSect.RJ = m_sect_tf;
	CDialog::OnOK();
}


void CUserdefcross::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
