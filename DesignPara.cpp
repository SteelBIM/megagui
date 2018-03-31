// DesignPara.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "DesignPara.h"
#include "afxdialogex.h"
#include "GlobalPara.h"


// CDesignPara 对话框

IMPLEMENT_DYNAMIC(CDesignPara, CDialog)

CDesignPara::CDesignPara(CWnd* pParent /*=NULL*/)
	: CDialog(CDesignPara::IDD, pParent)
{

	m_rQ = 0.0f;
	m_rM1 = 0.0f;
	m_rM0 = 0.0f;
	m_rGSup = 0.0f;
	m_rGinf = 0.0f;
	m_2effect = 0;
	m_crackcheck = 0;
	m_nmmethod = 0;
	m_shear_method = 0;
	m_rQ2 = 0.0f;
	m_rc = 1.0f;
	m_rs = 1.0f;
	SecSel=0;
	
	m_conc_mesh = 0.0f;
	m_profile_mesh = 0.0f;
}

CDesignPara::~CDesignPara()
{
}

void CDesignPara::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//	DDX_Text(pDX, IDC_rQ, m_rQ);
	DDX_Text(pDX, IDC_rM1, m_rM1);
	DDX_Text(pDX, IDC_rM0, m_rM0);
	//	DDX_Text(pDX, IDC_rGSup, m_rGSup);
	//	DDX_Text(pDX, IDC_rGinf, m_rGinf);
	DDX_CBIndex(pDX, IDC_2EFFECT, m_2effect);
	DDX_CBIndex(pDX, IDC_CRACKCHECK, m_crackcheck);
	DDX_CBIndex(pDX, IDC_NM_METHOD, m_nmmethod);
	DDX_CBIndex(pDX, IDC_Shear_method, m_shear_method);
	//	DDX_Text(pDX, IDC_rQ22, m_rQ2);
	DDX_Control(pDX, IDC_Con_Model, m_con_model);
	DDX_Text(pDX, IDC_rcc, m_rc);
	DDX_Text(pDX, IDC_rss, m_rs);
	DDX_Control(pDX, IDC_SECT_LIST, m_sectlist);	
	
//	DDX_Text(pDX, IDC_MESH_CONC, m_conc_mesh);
//	DDX_Text(pDX, IDC_MESH_PROFILE, m_profile_mesh);
}


BEGIN_MESSAGE_MAP(CDesignPara, CDialog)
	ON_BN_CLICKED(IDOK, &CDesignPara::OnBnClickedOk)	
	
	ON_CBN_SELCHANGE(IDC_Shear_method, &CDesignPara::OnCbnSelchangeShear)
	
	ON_CBN_SELCHANGE(IDC_SECT_LIST, &CDesignPara::OnCbnSelchangeSectList)
	ON_CBN_SELCHANGE(IDC_NM_METHOD, &CDesignPara::OnCbnSelchangeNmMethod)
END_MESSAGE_MAP()


// CDesignPara 消息处理程序


void CDesignPara::OnBnClickedOk()
{
	UpdateData();
	GlobalPara::m_DesnPara.rGinf = m_rGinf;
	GlobalPara::m_DesnPara.rGsup = m_rGSup;
	GlobalPara::m_DesnPara.rQ1 = m_rQ;
	GlobalPara::m_DesnPara.rQ2 = m_rQ2;
	GlobalPara::m_DesnPara.gama0 = m_rM0;
	GlobalPara::m_DesnPara.gama1 = m_rM1;
	GlobalPara::m_DesnPara.ifCrackCheck = m_crackcheck;
	GlobalPara::m_DesnPara.ifFiber = m_nmmethod;
	GlobalPara::m_DesnPara.shearmethod = m_shear_method;
	GlobalPara::m_DesnPara.conc_mesh = m_conc_mesh;
	GlobalPara::m_DesnPara.profile_mesh = m_profile_mesh;
	GlobalPara::m_DesnPara.ifSecondEffect = m_2effect;
	GlobalPara::m_DesnPara.rs = m_rs;
	GlobalPara::m_DesnPara.rc = m_rc;
//	GlobalPara::m_DesnPara.con_model = m_con_model.GetCurSel();
	if(GlobalPara::m_Sect_in.HSect.H1 ==0)
		GlobalPara::currentsect = 1;
	else
		GlobalPara::currentsect = m_sectlist.GetCurSel();
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}

void CDesignPara::SetParaStatus(int type)
{
	int FiberMax,FiberMin,ShearMax,ShearMin;
	GetParaLimit(type,FiberMax,FiberMin,ShearMax,ShearMin);
	//初始化fiber截面选择    fiber:  0:
	if(FiberMax==FiberMin)   //  一定==1
	{	
		m_nmmethod = 1;		
		GetDlgItem(IDC_NM_METHOD)->EnableWindow(FALSE);		
	}else GetDlgItem(IDC_NM_METHOD)->EnableWindow(TRUE);		

	//初始化Shear 方法选择    fiber:  0:
	if(ShearMin==-1)
	{
		GetDlgItem(IDC_STATIC_shear_model)->ShowWindow(FALSE);   
		GetDlgItem(IDC_Shear_method)->ShowWindow(FALSE);
	}else
	{
		GetDlgItem(IDC_STATIC_shear_model)->ShowWindow(TRUE);   
		GetDlgItem(IDC_Shear_method)->ShowWindow(TRUE);
		if(ShearMax==0)
		{
			m_shear_method=0;				
			GetDlgItem(IDC_shear_model)->EnableWindow(FALSE);
		}else GetDlgItem(IDC_shear_model)->EnableWindow(TRUE);
	}

	if(m_nmmethod==1) 
	{
		m_crackcheck=1;		
	}else
	{
		m_crackcheck=0;		
	}
	UpdateData(FALSE);
}
BOOL CDesignPara::OnInitDialog()
{
	CDialog::OnInitDialog();
	int type;
	SecSel = GlobalPara::currentsect;
	if(SecSel==0)
	{
		if(GlobalPara::m_Sect_in.Sect_b==0)	type=0;
		else 	type=GlobalPara::m_Sect_in.m_kind;		
	}else
	{
		type=0;
	}	
	



	m_rGinf = GlobalPara::m_DesnPara.rGinf;
	m_rGSup = GlobalPara::m_DesnPara.rGsup;
	m_rQ    = GlobalPara::m_DesnPara.rQ1;
	m_rQ2   = GlobalPara::m_DesnPara.rQ2;
	m_rM0   = GlobalPara::m_DesnPara.gama0;
	m_rM1   = GlobalPara::m_DesnPara.gama1;
	
	m_rs = GlobalPara::m_DesnPara.rs;
	m_rc = GlobalPara::m_DesnPara.rc;
	m_conc_mesh = GlobalPara::m_DesnPara.conc_mesh;
	m_profile_mesh = GlobalPara::m_DesnPara.profile_mesh;
	m_crackcheck = GlobalPara::m_DesnPara.ifCrackCheck;
	m_nmmethod = GlobalPara::m_DesnPara.ifFiber;
	m_shear_method = GlobalPara::m_DesnPara.shearmethod;
	m_con_model.SetCurSel(GlobalPara::m_DesnPara.con_model);
//	m_2effect = GlobalPara::m_DesnPara.ifSecondEffect;
	// TODO:  在此添加额外的初始化
	m_con_model.ResetContent();
	if(GlobalPara::ExpertMode){
		m_con_model.AddString("Euro");
		m_con_model.AddString("US");
		m_con_model.AddString("China");
	if(GlobalPara::ExpertMode)	m_con_model.AddString("Self Define");
	}
	else{
		m_con_model.AddString("Euro");
		m_con_model.AddString("US");
		m_con_model.AddString("China");
	}
	m_con_model.SetCurSel(GlobalPara::m_DesnPara.con_model);
	//初始化截面选择
	SecSel = GlobalPara::currentsect;
	CString Userdef;
	if(GlobalPara::m_Sect_in.Sect_b!=0)   // 可选type和custom  
	{
		Userdef.Format("Section Type %d,With Profile %s",GlobalPara::m_Sect_in.m_kind,GlobalPara::m_Sect_in.HSect.NAME);
	}else
	{
		Userdef=_T("------");
		SecSel=1;
	}
		m_sectlist.AddString(Userdef);
	m_sectlist.AddString("Custom cross section");
	m_sectlist.SetCurSel(SecSel);
	if(GlobalPara::m_Sect_in.Sect_b==0)   
	{
		GetDlgItem(IDC_SECT_LIST)->EnableWindow(FALSE);
	}
	SetParaStatus(type);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}




void CDesignPara::OnCbnSelchangeShear()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(GlobalPara::m_Sect_in.m_kind==2 || GlobalPara::m_Sect_in.m_kind==5 || GlobalPara::m_Sect_in.m_kind==8){			//这三个截面无法计算桁架模型
		AfxMessageBox("this section incompatible with truss-model!");
		m_shear_method = 0;
		UpdateData(FALSE);
	}
}



void CDesignPara::OnCbnSelchangeSectList()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	int cur = m_sectlist.GetCurSel();
	CString tx;
	m_sectlist.GetLBText(cur,tx);
	int type;
	if(tx.Compare("Custom cross section")==0){
		type=0;
		m_crackcheck=0;
		GetDlgItem(IDC_CRACKCHECK)->EnableWindow(FALSE);
		m_nmmethod = 1;
	}
	else{
		type=GlobalPara::m_Sect_in.m_kind;
		if(m_nmmethod==1) 
		{
			m_crackcheck=1;
		GetDlgItem(IDC_CRACKCHECK)->EnableWindow(TRUE);
		}else
		{
			m_crackcheck=0;
			GetDlgItem(IDC_CRACKCHECK)->EnableWindow(FALSE);
	}

	}
	SetParaStatus(type);
	UpdateData(FALSE);	
}
void CDesignPara::GetParaLimit(int type,int& FiberMax,int& FiberMin,int& ShearMax,int& ShearMin)
{
	switch(type)
	{
		case 0:
			FiberMin=1;
			FiberMax=1;			
			ShearMin=-1;
			ShearMax=-1;			
			break;
		case 1:
			FiberMin=0;
			FiberMax=1;			
			ShearMin=0;
			ShearMax=0;			
			break;
		case 2:
			FiberMin=1;
			FiberMax=1;			
			ShearMin=-1;
			ShearMax=-1;
			break;
		case 3:
			FiberMin=0;
			FiberMax=1;			
			ShearMin=0;
			ShearMax=1;
			break;		
		case 4:
			FiberMin=0;
			FiberMax=1;			
			ShearMin=0;
			ShearMax=1;
			break;
		case 5:
			FiberMin=1;
			FiberMax=1;			
			ShearMin=-1;
			ShearMax=-1;
			break;
		case 6:
			FiberMin=0;
			FiberMax=1;			
			ShearMin=0;
			ShearMax=1;
			break;

		case 7:
			FiberMin=0;
			FiberMax=1;			
			ShearMin=0;
			ShearMax=1;
			break;
		case 8:
			FiberMin=0;
			FiberMax=1;			
			ShearMin=0;
			ShearMax=0;
			break;
		default:
			FiberMin=1;
			FiberMax=1;			
			ShearMin=-1;
			ShearMax=-1;
			break;

	}
	return ;
}
void CDesignPara::OnCbnSelchangeNmMethod()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	int type;
	if(SecSel==0)
	{
		if(GlobalPara::m_Sect_in.Sect_b==0)	type=0;
		else 	type=GlobalPara::m_Sect_in.m_kind;		
	}else
	{
		type=0;
	}
	SetParaStatus(type);
	if(m_nmmethod==0) GetDlgItem(IDC_CRACKCHECK)->EnableWindow(FALSE);
	else GetDlgItem(IDC_CRACKCHECK)->EnableWindow(TRUE);

}
