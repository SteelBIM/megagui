// MegaSection4.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "MegaSection4.h"
#include "afxdialogex.h"
#include "UserDefCross.h"
#include "SectCommon.h"
#include "GlobalPara.h"
#include "CfgBas.h"
#include <string.h>

// CMegaSection4 对话框
extern "C" __declspec( dllimport ) CCfgBas *m_pCfgBas;
IMPLEMENT_DYNAMIC(CMegaSection4, CDialog)

CMegaSection4::CMegaSection4(CWnd* pParent /*=NULL*/)
	: CDialog(CMegaSection4::IDD, pParent)
{
	/*
	m_sect4_Dext = 3072;
	m_profile_c = 586;
	m_cnom = 50.0;
	m_no_x = 16;
	m_cs= 50;
	int code = 1;
//	m_bar_mp_new=400;
	m_stud_d = 0;
	m_stud_fu = 0.0f;
	m_stud_fy = 0.0f;
	m_stud_l = 0.0f;
	m_tranbar_mp = 0;
	m_tranratio_yy = 0.0f;
	m_tranratio_zz = 0.0f;
	*/
}

CMegaSection4::~CMegaSection4()
{
}
BOOL CMegaSection4::PreTranslateMessage(MSG* pMsg)   
{  
	// TODO: Add your specialized code here and/or call the base class  
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)  
	{  
		GetNextDlgTabItem(GetFocus())->SetFocus();  
		//		UpdateData(FALSE);
		SetGlobalPara();
		DrawSectOnPic();
		return TRUE;  
	}  

	return CDialog::PreTranslateMessage(pMsg);  
}  

void CMegaSection4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_S4_D, m_sect4_Dext);
	DDX_Control(pDX, IDC_STRU_CLASS, m_stru_class);
	DDX_Control(pDX, IDC_EXP_CLASS, m_exp_class);
	DDX_Text(pDX, IDC_CNOM, m_cnom);
	DDX_Text(pDX, IDC_EDIT_CS, m_cs);
	DDX_Control(pDX, IDC_CON_CLASS, m_con_class);
	DDX_Control(pDX, IDC_STEEL_FY, m_steel_fy);
	DDX_Control(pDX, IDC_BAR_D, m_bar_d);
	DDX_Text(pDX, IDC_BAR_X, m_no_x);
	DDX_Text(pDX, IDC_P_C, m_profile_c);
	DDX_Text(pDX, IDC_BAR_MP_NEW4, m_bar_mp_new);
	DDX_Text(pDX, IDC_STUD_D, m_stud_d);
	DDX_Text(pDX, IDC_STUD_FU, m_stud_fu);
	DDX_Text(pDX, IDC_STUD_FY, m_stud_fy);
	DDX_Text(pDX, IDC_STUD_L, m_stud_l);
	DDX_Text(pDX, IDC_TRNBAR_MP_NEW4, m_tranbar_mp);
	DDX_Control(pDX, IDC_STEEL_FY3, m_steel_code);
	DDX_Text(pDX, IDC_tranratio_yy_4, m_tranratio_yy);
//	DDX_Text(pDX, IDC_tranratio_zz_4, m_tranratio_zz);
}


BEGIN_MESSAGE_MAP(CMegaSection4, CDialog)
	ON_BN_CLICKED(IDC_USER_DEF4, &CMegaSection4::OnBnClickedUserDef4)
	ON_BN_CLICKED(IDC_CHOOSE_PROFILE, &CMegaSection4::OnBnClickedChooseProfile)
	ON_BN_CLICKED(IDOK, &CMegaSection4::OnBnClickedOk)
	//ON_CBN_SELCHANGE(IDC_NO_Y, &CMegaSection4::OnCbnSelchangeNoY)
	//ON_CBN_SELCHANGE(IDC_NO_X, &CMegaSection4::OnCbnSelchangeNoX)
	ON_CBN_SELCHANGE(IDC_BAR_D, &CMegaSection4::OnCbnSelchangeBarD)
//	
//	ON_CBN_SELCHANGE(IDC_CON_CLASS, &CMegaSection4::OnCbnSelchangeConClass)
	ON_CBN_SELCHANGE(IDC_STEEL_FY, &CMegaSection4::OnCbnSelchangeSteelFy)
	ON_CBN_SELCHANGE(IDC_STRU_CLASS, &CMegaSection4::OnCbnSelchangeStruClass)
	ON_CBN_SELCHANGE(IDC_EXP_CLASS, &CMegaSection4::OnCbnSelchangeExpClass)
	ON_CBN_SELCHANGE(IDC_STEEL_FY3, &CMegaSection4::OnCbnSelchangeSteelFy3)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_S4_D, &CMegaSection4::OnEnKillfocusS4D)
	ON_EN_KILLFOCUS(IDC_BAR_X, &CMegaSection4::OnEnKillfocusBarX)
	ON_EN_KILLFOCUS(IDC_P_C, &CMegaSection4::OnEnKillfocusPC)
//	ON_STN_CLICKED(IDS_CAL_METHOD, &CMegaSection4::OnStnClickedCalMethod)
//ON_CBN_KILLFOCUS(IDC_CON_CLASS, &CMegaSection4::OnCbnKillfocusConClass)
ON_CBN_SELCHANGE(IDC_CON_CLASS, &CMegaSection4::OnCbnSelchangeConClass)
ON_EN_KILLFOCUS(IDC_EDIT_CS, &CMegaSection4::OnEnKillfocusEditCs)
END_MESSAGE_MAP()


// CMegaSection4 消息处理程序


BOOL CMegaSection4::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(GlobalPara::ExpertMode==true){
		GetDlgItem(IDC_USER_DEF4)->ShowWindow(SW_SHOW);
		m_con_class.AddString("Custom");		//自定义本构
	}
	else
		GetDlgItem(IDC_USER_DEF4)->ShowWindow(SW_HIDE);
	
	// 异常: OCX 属性页应返回 FALSE

	Hsect.B1 =GlobalPara::m_Sect_in.HSect.B1 ;	
	Hsect.H1=GlobalPara::m_Sect_in.HSect.H1 ;
	Hsect.RI=GlobalPara::m_Sect_in.HSect.RI;
	Hsect.RJ=GlobalPara::m_Sect_in.HSect.RJ;
	strcpy(Hsect.NAME,GlobalPara::m_Sect_in.HSect.NAME);
	if(strlen(Hsect.NAME)>1) GetDlgItem(IDC_SECTNAME)->SetWindowText(_T(Hsect.NAME));
	else GetDlgItem(IDC_SECTNAME)->SetWindowText(_T("Please choose one profile!"));	
	m_sect4_Dext=GlobalPara::m_Sect_in.Sect_b ;

	m_profile_c=0.5*m_sect4_Dext-GlobalPara::m_Sect_in.HSect_x;
	int sel_value=0;
	m_bar_d.SetCurSel(SetBarD(GlobalPara::m_Sect_in.Bar_d));
	
	m_steel_fy.SetCurSel(GlobalPara::m_Sect_in.HSect_mat);
	m_stru_class.SetCurSel(GlobalPara::m_DesnPara.Struc_Class);
	m_exp_class.SetCurSel(GlobalPara::m_DesnPara.Exp_Class);
	
	m_bar_mp_new = GlobalPara::m_Sect_in.Bar_mat;
	v_bar_d = GlobalPara::m_Sect_in.Bar_d;
	m_cnom=GlobalPara::m_Sect_in.Concrete_coverd;
	v_exp_class = GlobalPara::m_DesnPara.Exp_Class;
	v_stru_class = GlobalPara::m_DesnPara.Struc_Class;
	m_no_x = GlobalPara::m_Sect_in.Bar_num_bside;
	m_stud_d = GlobalPara::m_DesnPara.stud_d;
	m_stud_l = GlobalPara::m_DesnPara.stud_len;
	m_stud_fu = GlobalPara::m_DesnPara.stud_fu;
	m_stud_fy = GlobalPara::m_DesnPara.stud_fy;
	m_tranratio_yy = GlobalPara::m_Sect_in.Tran_ratio_x;
	m_cs = GlobalPara::m_Sect_in.Con_coverd_x;
	m_tranbar_mp = GlobalPara::m_Sect_in.TransversalBar_mat;
	Tools::AddConMatByCode(m_con_class);
	Tools::SetConMatCurSel(m_con_class,GlobalPara::m_Sect_in.Concrete_mat,GlobalPara::ExpertMode);
	
	initSteel();
	m_steel_code.SetCurSel(GlobalPara::m_DesnPara.ProType);
	int newlen = m_steel_code.SetDroppedWidth(100);
	update=false;
	OnCbnSelchangeSteelFy3();
	m_steel_fy.SetCurSel(GlobalPara::m_DesnPara.ProLevel);
	m_steel_fy.SetDroppedWidth(150);
	update=true;
//	m_no_y = GlobalPara::m_Sect_in.Bar_num_hside;
	UpdateData();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CMegaSection4::initSteel()
{
	m_steel_code.ResetContent();
	m_steel_code.AddString("EN10025");
	m_steel_code.AddString("ETA-10/0156");
	m_steel_code.AddString("ASTM");
	m_steel_code.AddString("Chinese");
	if(GlobalPara::ExpertMode==true)
		m_steel_code.AddString("Custom");
}

void CMegaSection4::OnBnClickedUserDef4()
{
	// TODO: 在此添加控件通知处理程序代码
	CUserdefcross pdlg;
	int ik = pdlg.DoModal();
	if(ik){
		Hsect.B1 = pdlg.UserDefSect.B1;
		Hsect.H1 = pdlg.UserDefSect.H1;
		Hsect.RI = pdlg.UserDefSect.RI;
		Hsect.RJ = pdlg.UserDefSect.RJ;
		ProName.Format("User defined %dx%dx%gx%g",Hsect.H1,Hsect.B1,Hsect.RJ,Hsect.RI);
		memcpy(Hsect.NAME,ProName,sizeof(ProName));
		GetDlgItem(IDC_SECTNAME)->SetWindowText(ProName);
		UpdateData(FALSE);
	}
}


void CMegaSection4::OnBnClickedChooseProfile()
{
	// TODO: 在此添加控件通知处理程序代码
// 	int iType=7,IDel=0;
// 	short gSect[1200];	// 型钢库定义用不到这个数据
// 	SECTION1 m_sect;
// 	SECTIONS m_sect1,m_sect2;
// 	//STEEL_SECT_DEFINE(IDel,m_sect);
// 	//STS_StdSteelSect_Define_Ex(iType,m_sect,gSect,IDel);
// 	Hsect.KIND = 36;
// 	STS_SIN_SECT_DEFINE(IDel,m_sect1,m_sect2);
	CDlgSectionList dlg;
	if(IDOK == dlg.DoModal())
	{
		int nKd,nSel;
		dlg.GetResult(nKd,nSel);
		int nBegin,nEnd;
		CSectKeeper::Get().TypeBeginEnd(nKd,nBegin,nEnd);
		nSel = nSel + nBegin;

		struct HE_  hh = CSectKeeper::Get().steelC().HE[nSel];
		Hsect.B1 = hh.B;
		Hsect.H1 = hh.H;
		Hsect.RI = hh.tf;
		Hsect.RJ = hh.tw;
		memcpy(Hsect.NAME,hh.NAME,sizeof(hh.NAME));
		ProName.Format("%s",hh.NAME);
		GetDlgItem(IDC_SECTNAME)->SetWindowText(ProName);
		UpdateData(FALSE);
		SetGlobalPara();
		DrawSectOnPic();

	}

}

void CMegaSection4::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//d~bc~x,c~hc~y
	UpdateData();
	if(Hsect.B1<0){
		AfxMessageBox(_T("Please choose one profile!"),MB_OK+MB_ICONINFORMATION);
		return;
	}
	SetGlobalPara();

	float Hratio = Tools::CalSectProRatio();
	if(Hratio<0.002)
		AfxMessageBox(_T("Profile ratio is lower than 0.2!"),MB_OK+MB_ICONINFORMATION);
	else{
		CDialog::OnOK();
		CDrawSectPic::DrawPreDefinedSect();
	}
}


//void CMegaSection4::OnCbnSelchangeNoY()
//{
//	UpdateData();
//	// TODO: 在此添加控件通知处理程序代码
//	int no[5] = {2,3,4,5,6};
//	v_bar_y = no[m_bar_y.GetCurSel()];
//}
//
//
//void CMegaSection4::OnCbnSelchangeNoX()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	UpdateData();
//	int no[5] = {2,3,4,5,6};
//	v_bar_x = no[m_bar_x.GetCurSel()];
//}


void CMegaSection4::OnCbnSelchangeBarD()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	//	int bard[10]={8,10,12,14,16,20,25,28,32,40};
	v_bar_d = GlobalPara::bard[m_bar_d.GetCurSel()];
}




//void CMegaSection4::OnCbnSelchangeConClass()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	UpdateData();
//	CString conmat;
//	m_con_class.GetWindowText(conmat);		
//	Tools::ConMatStringCatch(conmat);
//}


void CMegaSection4::OnCbnSelchangeSteelFy()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	//	int profy[4]={355,420,460,500};
	v_steel_fy = GlobalPara::profy[m_steel_fy.GetCurSel()];
}


void CMegaSection4::OnCbnSelchangeStruClass()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	v_stru_class = m_stru_class.GetCurSel();
}


void CMegaSection4::OnCbnSelchangeExpClass()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	v_exp_class = m_exp_class.GetCurSel();
}

int CMegaSection4::SetBarMp(int BarMp)
{
	for(int i=0;i<barmp_no;i++){
		if(BarMp==GlobalPara::barmp[i]){
			return i;
		}
	}
	return 0;
}

int CMegaSection4::SetBarD(int BarD)
{
	//	int bard[10]={8,10,12,14,16,20,25,28,32,40};
	for(int i=0;i<10;i++){
		if(BarD == GlobalPara::bard[i]){
			return i;
		}
	}
	return 0 ;
}

void CMegaSection4::OnCbnSelchangeSteelFy3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(update)
		UpdateData();
	v_steel_code = m_steel_code.GetCurSel();
	if(v_steel_code==0)		//EN 10025& EN 10225
	{
		m_steel_fy.ResetContent();
		m_steel_fy.AddString("S355JR/JO/J2/K2");
		m_steel_fy.AddString("S460JR/JO/J2/K2");
		m_steel_fy.AddString("S500JO");
		m_steel_fy.AddString("S355M/ML");
		m_steel_fy.AddString("S420M/ML");
		m_steel_fy.AddString("S460M/ML");
		m_steel_fy.AddString("S500M/ML");
	}
	else if(v_steel_code==1)		//ETA-10/0156
	{
		m_steel_fy.ResetContent();
		m_steel_fy.AddString("Histar355");
		m_steel_fy.AddString("Histar460");
	}
	else if(v_steel_code==2)		//ASTM
	{
		m_steel_fy.ResetContent();
		m_steel_fy.AddString("A913Gr50");
		m_steel_fy.AddString("A913Gr65");
		m_steel_fy.AddString("A913Gr70");
		m_steel_fy.AddString("A913Gr80");
	}
	else if(v_steel_code==3)		//chinese
	{
		m_steel_fy.ResetContent();
		m_steel_fy.AddString("Q235");
		m_steel_fy.AddString("Q345");
		m_steel_fy.AddString("Q345GJ");
		m_steel_fy.AddString("Q390");
		m_steel_fy.AddString("Q420"); 
	}
	else if(v_steel_code==4){
		m_steel_fy.ResetContent();
		m_steel_fy.AddString("Curve 1");
		m_steel_fy.AddString("Curve 2");
	}	m_steel_fy.SetCurSel(0);

	UpdateData(FALSE);
}


void CMegaSection4::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 __super::OnPaint()
	DrawSectOnPic();
}



void CMegaSection4::SetGlobalPara(void)
{
	UpdateData();
	GlobalPara::m_Sect_in.HSect_x = m_sect4_Dext*0.5-m_profile_c;
	GlobalPara::m_Sect_in.HSect_y = m_sect4_Dext*0.5-m_profile_c;
	strcpy(GlobalPara::m_Sect_in.HSect.NAME,Hsect.NAME);
	GlobalPara::m_Sect_in.HSect.B1 = Hsect.B1;
	GlobalPara::m_Sect_in.HSect.B2 = Hsect.B1;
	GlobalPara::m_Sect_in.HSect.H1 = Hsect.H1;
	GlobalPara::m_Sect_in.HSect.RI = Hsect.RI;
	GlobalPara::m_Sect_in.HSect.RJ = Hsect.RJ;

	GlobalPara::m_Sect_in.Sect_b = m_sect4_Dext;
	GlobalPara::m_Sect_in.Sect_h=m_sect4_Dext;
	GlobalPara::m_Sect_in.m_kind=5;
	GlobalPara::m_Sect_in.RotateType = 0;
	GlobalPara::m_Sect_in.Concrete_coverd=m_cnom;
	GlobalPara::m_Sect_in.Bar_num_bside=m_no_x;
	GlobalPara::m_Sect_in.Bar_num_hside=0;
	GlobalPara::m_Sect_in.Bar_d=v_bar_d;
	GlobalPara::m_Sect_in.Bar_circleR=16;
	GlobalPara::m_Sect_in.Bar_mat = m_bar_mp_new;
	GlobalPara::m_Sect_in.HSect_mat = 2;

	CString conmat;
	m_con_class.GetWindowText(conmat);		
	Tools::ConMatStringCatch(conmat);

	GlobalPara::m_Sect_in.Con_coverd_x = m_cs;
	float interval1 = (m_sect4_Dext-2*m_cnom)/(m_no_x-1);
	float interval2 = 0;
	GlobalPara::m_Sect_in.Bar_interval = max(interval1,interval2);

	GlobalPara::m_DesnPara.Struc_Class = v_stru_class;
	GlobalPara::m_DesnPara.Exp_Class = v_exp_class;

	GlobalPara::m_DesnPara.ProType = m_steel_code.GetCurSel();
	GlobalPara::m_DesnPara.ProLevel = m_steel_fy.GetCurSel();
	GlobalPara::m_Sect_in.Tran_ratio_x = m_tranratio_yy;
	GlobalPara::m_Sect_in.Tran_ratio_y = m_tranratio_zz;
	GlobalPara::m_Sect_in.TransversalBar_mat = m_tranbar_mp;

	GlobalPara::m_DesnPara.stud_d = m_stud_d;
	GlobalPara::m_DesnPara.stud_len = m_stud_l;
	GlobalPara::m_DesnPara.stud_fu = m_stud_fu;
	GlobalPara::m_DesnPara.stud_fy = m_stud_fy;

}


void CMegaSection4::DrawSectOnPic(void)
{
	CPaintDC dc(this);
	UpdateData();
	//	CPaintDC dc(this); // device context for painting
	RECT *lpRect=new RECT;
	long w,h;
	CWnd *pWnd=GetDlgItem(IDC_ARRANGE_BMP);
	pWnd->GetClientRect(lpRect);
	w=(lpRect->right-lpRect->left);
	h=(lpRect->bottom-lpRect->top);
	CDC *pDiaDc=pWnd->GetDC();	
	HDC OldDc= m_pCfgBas->Customiz_CFGDC(pDiaDc->GetSafeHdc(),*lpRect,TRUE);	
	float xmin,ymin,xmax,ymax,scale;
	
	CDrawSectPic::GetSectSize(xmin,ymin,xmax,ymax,scale);
	CDrawSectPic::PasteTo(w,h,xmin,ymin,xmax,ymax,scale);
	CDrawSectPic::DrawSectAll();
	m_pCfgBas->Customiz_CFGDC(OldDc,*lpRect,FALSE);	
	delete lpRect;
}


void CMegaSection4::OnEnKillfocusS4D()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_no_x=int(3.142*m_sect4_Dext/150);
	UpdateData(FALSE);

	SetGlobalPara();
	DrawSectOnPic();
}


void CMegaSection4::OnEnKillfocusBarX()
{
	// TODO: 在此添加控件通知处理程序代码
	SetGlobalPara();
	DrawSectOnPic();
}


void CMegaSection4::OnEnKillfocusPC()
{
	// TODO: 在此添加控件通知处理程序代码
	SetGlobalPara();
	DrawSectOnPic();
}



//void CMegaSection4::OnCbnKillfocusConClass()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void CMegaSection4::OnCbnSelchangeConClass()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMegaSection4::OnEnKillfocusEditCs()
{
	// TODO: 在此添加控件通知处理程序代码
}
