// ConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"
#include "GlobalPara.h"


// CConfigDlg 对话框

IMPLEMENT_DYNAMIC(CConfigDlg, CDialog)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{

	m_con_den = 0.0f;
	m_steel_den = 0.0f;
	m_pos = 0.0f;
	m_g = 0.0f;
}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CON_DEN, m_con_den);
	DDX_Text(pDX, IDC_STEEL_DEN, m_steel_den);
	DDX_Text(pDX, IDC_POS, m_pos);
	DDX_Text(pDX, IDC_G, m_g);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConfigDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConfigDlg 消息处理程序


void CConfigDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	GlobalPara::m_DesnPara.m_Gravity = m_g;
	GlobalPara::m_DesnPara.m_Conp = m_con_den;
	GlobalPara::m_DesnPara.m_Density = m_steel_den;
	GlobalPara::m_DesnPara.m_Possion = m_pos;
	CDialog::OnOK();
}


BOOL CConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_g = GlobalPara::m_DesnPara.m_Gravity;
	m_con_den = GlobalPara::m_DesnPara.m_Conp;
	m_steel_den = GlobalPara::m_DesnPara.m_Density;
	m_pos = GlobalPara::m_DesnPara.m_Possion;
	// TODO:  在此添加额外的初始化
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
