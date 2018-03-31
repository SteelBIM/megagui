// MeshGrid.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "MeshGrid.h"
#include "afxdialogex.h"


// CMeshGrid 对话框

IMPLEMENT_DYNAMIC(CMeshGrid, CDialog)

CMeshGrid::CMeshGrid(CWnd* pParent /*=NULL*/)
	: CDialog(CMeshGrid::IDD, pParent)
{

	m_con_mesh = 0.0f;
	m_steel_mesh = 0.0f;
}

CMeshGrid::~CMeshGrid()
{
}

void CMeshGrid::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CON_MESH, m_con_mesh);
	DDX_Text(pDX, IDC_STEEL_MESH, m_steel_mesh);
}


BEGIN_MESSAGE_MAP(CMeshGrid, CDialog)
	ON_BN_CLICKED(IDOK, &CMeshGrid::OnBnClickedOk)
END_MESSAGE_MAP()


// CMeshGrid 消息处理程序


void CMeshGrid::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	GlobalPara::m_DesnPara.conc_mesh = m_con_mesh;
	GlobalPara::m_DesnPara.profile_mesh = m_steel_mesh;
	CDialog::OnOK();
}


BOOL CMeshGrid::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_con_mesh =	GlobalPara::m_DesnPara.conc_mesh;
	m_steel_mesh = GlobalPara::m_DesnPara.profile_mesh;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
