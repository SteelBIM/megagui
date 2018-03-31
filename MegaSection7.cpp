// MegaSection7.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "MegaSection7.h"
#include "afxdialogex.h"
#include "UserDefCross.h"
#include "SectCommon.h"
#include "GlobalPara.h"
#include "CfgBas.h"

extern "C" __declspec( dllimport ) CCfgBas *m_pCfgBas;
// CMegaSection7 对话框

IMPLEMENT_DYNAMIC(CMegaSection7, CDialog)

CMegaSection7::CMegaSection7(CWnd* pParent /*=NULL*/)
	: CDialog(CMegaSection7::IDD, pParent)
{
	/*
	m_sect7_bc = 3072;
	m_sect7_hc = 3072;
	m_profile_c = 586;
	m_profile_d = 524;
	m_cnom = 50.0;
	m_no_x = 16;
	m_no_y = 16;
	m_csz= 50;
	m_csy= 50;
	int code = 1;
	m_bar_mp_new=400;
	m_stud_d = 0;
	m_stud_fu = 0.0f;
	m_stud_fy = 0.0f;
	m_stud_l = 0;
	m_tranbar_mp = 0;
	m_tranratio_yy = 0.0f;
	m_tranratio_zz = 0.0f;
	*/
}


CMegaSection7::~CMegaSection7()
{
}
BOOL CMegaSection7::PreTranslateMessage(MSG* pMsg)   
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

void CMegaSection7::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_S7_HC, m_sect7_hc);
	DDX_Text(pDX, IDC_S7_BC, m_sect7_bc);
	DDX_Control(pDX, IDC_STRU_CLASS, m_stru_class);
	DDX_Control(pDX, IDC_EXP_CLASS, m_exp_class);
	DDX_Text(pDX, IDC_CNOM, m_cnom);
	DDX_Text(pDX, IDC_EDIT_CSZ, m_csz);
	DDX_Text(pDX, IDC_EDIT_CSY, m_csy);
	DDX_Control(pDX, IDC_CON_CLASS, m_con_class);
	DDX_Control(pDX, IDC_STEEL_FY, m_steel_fy);
	DDX_Control(pDX, IDC_BAR_D, m_bar_d);

	DDX_Text(pDX, IDC_BAR_Y, m_no_y);
	DDX_Text(pDX, IDC_BAR_X, m_no_x);
	DDX_Text(pDX, IDC_P_C, m_profile_c);
	DDX_Text(pDX, IDC_P_D, m_profile_d);
	DDX_Text(pDX, IDC_BAR_MP_NEW7, m_bar_mp_new);
	DDX_Text(pDX, IDC_STUD_D, m_stud_d);
	DDX_Text(pDX, IDC_STUD_FU, m_stud_fu);
	DDX_Text(pDX, IDC_STUD_FY, m_stud_fy);
	DDX_Text(pDX, IDC_STUD_L, m_stud_l);
	DDX_Text(pDX, IDC_TRNBAR_MP_NEW7, m_tranbar_mp);
	DDX_Control(pDX, IDC_STEEL_FY2, m_steel_code);
	DDX_Text(pDX, IDC_tranratio_yy_7, m_tranratio_yy);
	DDX_Text(pDX, IDC_tranratio_zz_7, m_tranratio_zz);
}


BEGIN_MESSAGE_MAP(CMegaSection7, CDialog)
	ON_BN_CLICKED(IDC_USER_DEF7, &CMegaSection7::OnBnClickedUserDef7)
	ON_BN_CLICKED(IDC_CHOOSE_PROFILE, &CMegaSection7::OnBnClickedChooseProfile)
	ON_BN_CLICKED(IDOK, &CMegaSection7::OnBnClickedOk)


	ON_CBN_SELCHANGE(IDC_BAR_D, &CMegaSection7::OnCbnSelchangeBarD)

	ON_CBN_SELCHANGE(IDC_CON_CLASS, &CMegaSection7::OnCbnSelchangeConClass)
	
	ON_CBN_SELCHANGE(IDC_STRU_CLASS, &CMegaSection7::OnCbnSelchangeStruClass)
	ON_CBN_SELCHANGE(IDC_EXP_CLASS, &CMegaSection7::OnCbnSelchangeExpClass)
	ON_STN_CLICKED(IDC_ARRANGE_BMP, &CMegaSection7::OnStnClickedArrangeBmp)
	ON_CBN_SELCHANGE(IDC_STEEL_FY2, &CMegaSection7::OnCbnSelchangeSteelFy2)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_S7_HC, &CMegaSection7::OnEnKillfocusS7Hc)
	ON_EN_KILLFOCUS(IDC_S7_BC, &CMegaSection7::OnEnKillfocusS7Bc)
	ON_EN_KILLFOCUS(IDC_BAR_Y, &CMegaSection7::OnEnKillfocusBarY)
	ON_EN_KILLFOCUS(IDC_BAR_X, &CMegaSection7::OnEnKillfocusBarX)
	ON_EN_KILLFOCUS(IDC_P_C, &CMegaSection7::OnEnKillfocusPC)
	ON_EN_KILLFOCUS(IDC_P_D, &CMegaSection7::OnEnKillfocusPD)
	ON_EN_KILLFOCUS(IDC_EDIT_CSZ, &CMegaSection7::OnEnKillfocusEditCsz)
	ON_EN_KILLFOCUS(IDC_EDIT_CSY, &CMegaSection7::OnEnKillfocusEditCsy)
	
END_MESSAGE_MAP()


// CMegaSection7 消息处理程序


BOOL CMegaSection7::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(GlobalPara::ExpertMode==true){
		GetDlgItem(IDC_USER_DEF7)->ShowWindow(SW_SHOW);
		m_con_class.AddString("Custom");		//自定义本构
	}
	else
		GetDlgItem(IDC_USER_DEF7)->ShowWindow(SW_HIDE);
	
	// 异常: OCX 属性页应返回 FALSE
	Hsect.B1 =GlobalPara::m_Sect_in.HSect.B1 ;	
	Hsect.H1=GlobalPara::m_Sect_in.HSect.H1 ;
	Hsect.RI=GlobalPara::m_Sect_in.HSect.RI;
	Hsect.RJ=GlobalPara::m_Sect_in.HSect.RJ;
	strcpy(Hsect.NAME,GlobalPara::m_Sect_in.HSect.NAME);
	if(strlen(Hsect.NAME)>1) GetDlgItem(IDC_SECTNAME)->SetWindowText(_T(Hsect.NAME));
	else GetDlgItem(IDC_SECTNAME)->SetWindowText(_T("Please choose one profile!"));
	
	m_sect7_hc = GlobalPara::m_Sect_in.Sect_h;
	m_sect7_bc = GlobalPara::m_Sect_in.Sect_b;

	m_profile_c=0.5*GlobalPara::m_Sect_in.Sect_h-GlobalPara::m_Sect_in.HSect_y;
	m_profile_d=0.5*GlobalPara::m_Sect_in.Sect_b-GlobalPara::m_Sect_in.HSect_x;

	int sel_value=0;
	m_bar_d.SetCurSel(SetBarD(GlobalPara::m_Sect_in.Bar_d));
	

	m_steel_fy.SetCurSel(GlobalPara::m_Sect_in.HSect_mat);
	m_stru_class.SetCurSel(GlobalPara::m_DesnPara.Struc_Class);
	m_exp_class.SetCurSel(GlobalPara::m_DesnPara.Exp_Class);
	
	m_bar_mp_new = GlobalPara::m_Sect_in.Bar_mat;
	v_bar_d = GlobalPara::m_Sect_in.Bar_d;
	v_exp_class = GlobalPara::m_DesnPara.Exp_Class;
	v_stru_class = GlobalPara::m_DesnPara.Struc_Class;
	m_no_x = GlobalPara::m_Sect_in.Bar_num_bside;
	m_no_y = GlobalPara::m_Sect_in.Bar_num_hside;
	m_stud_d = GlobalPara::m_DesnPara.stud_d;
	m_stud_l = GlobalPara::m_DesnPara.stud_len;
	m_stud_fu = GlobalPara::m_DesnPara.stud_fu;
	m_stud_fy = GlobalPara::m_DesnPara.stud_fy;
	m_tranratio_yy = GlobalPara::m_Sect_in.Tran_ratio_x;
	m_tranratio_zz = GlobalPara::m_Sect_in.Tran_ratio_y;
	m_cnom=GlobalPara::m_Sect_in.Concrete_coverd;
	m_csy = GlobalPara::m_Sect_in.Con_coverd_x;
	m_csz = GlobalPara::m_Sect_in.Con_coverd_y;
	m_tranbar_mp = GlobalPara::m_Sect_in.TransversalBar_mat;
	Tools::AddConMatByCode(m_con_class);
	Tools::SetConMatCurSel(m_con_class,GlobalPara::m_Sect_in.Concrete_mat,GlobalPara::ExpertMode);

	initSteel();
	m_steel_code.SetCurSel(GlobalPara::m_DesnPara.ProType);
	int newlen = m_steel_code.SetDroppedWidth(100);
	update=false;
	OnCbnSelchangeSteelFy2();
	m_steel_fy.SetCurSel(GlobalPara::m_DesnPara.ProLevel);
	m_steel_fy.SetDroppedWidth(150);
	UpdateData();
	update=true;

	SetGlobalPara();
	DrawSectOnPic();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CMegaSection7::initSteel()
{
	m_steel_code.ResetContent();
	m_steel_code.AddString("EN10025");
	m_steel_code.AddString("ETA-10/0156");
	m_steel_code.AddString("ASTM");
	m_steel_code.AddString("Chinese");
	if(GlobalPara::ExpertMode==true)
		m_steel_code.AddString("Custom");
}

void CMegaSection7::OnBnClickedUserDef7()
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


void CMegaSection7::OnBnClickedChooseProfile()
{
	// TODO: 在此添加控件通知处理程序代码
// 	int iType=7,IDel=0;
// 	short gSect[1200];	// 型钢库定义用不到这个数据
// 	//	SECTION1 m_sect;
// 	SECTIONS m_sect1;
// 	//STEEL_SECT_DEFINE(IDel,m_sect);
// 	//STS_StdSteelSect_Define_Ex(iType,m_sect,gSect,IDel);
// 	Hsect.KIND = 36;
// 	//	m_sect1.KIND = 36;
// 	STS_SIN_SECT_DEFINE(IDel,Hsect,m_sect1);
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
void CMegaSection7::SetGlobalPara(void)
{
	UpdateData();
	GlobalPara::m_Sect_in.HSect_x = m_sect7_bc*0.5-m_profile_d;
	GlobalPara::m_Sect_in.HSect_y = m_sect7_hc*0.5-m_profile_c;
	strcpy(GlobalPara::m_Sect_in.HSect.NAME,Hsect.NAME);
	GlobalPara::m_Sect_in.HSect.B1 = Hsect.B1;
	GlobalPara::m_Sect_in.HSect.B2 = Hsect.B1;
	GlobalPara::m_Sect_in.HSect.H1 = Hsect.H1;
	GlobalPara::m_Sect_in.HSect.RI = Hsect.RI;
	GlobalPara::m_Sect_in.HSect.RJ = Hsect.RJ;
	GlobalPara::m_Sect_in.Sect_b = m_sect7_bc;
	GlobalPara::m_Sect_in.Sect_h=m_sect7_hc;
	GlobalPara::m_Sect_in.m_kind=7;
	GlobalPara::m_Sect_in.RotateType = 0;
	GlobalPara::m_Sect_in.Concrete_coverd=m_cnom;
	GlobalPara::m_Sect_in.Bar_num_bside=m_no_x;
	GlobalPara::m_Sect_in.Bar_num_hside=m_no_y;
	GlobalPara::m_Sect_in.Bar_d=v_bar_d;
	GlobalPara::m_Sect_in.Bar_circleR=16;
	GlobalPara::m_Sect_in.Bar_mat = m_bar_mp_new;
	GlobalPara::m_Sect_in.HSect_mat = 2;

	CString conmat;
	m_con_class.GetWindowText(conmat);		
	Tools::ConMatStringCatch(conmat);


	float interval1 = (m_sect7_hc-2*m_cnom)/(m_no_x-1);
	float interval2 = (m_sect7_bc-2*m_cnom)/(m_no_y-1);
	GlobalPara::m_Sect_in.Bar_interval = max(interval1,interval2);
	GlobalPara::m_Sect_in.Con_coverd_x = m_csy;
	GlobalPara::m_Sect_in.Con_coverd_y = m_csz;

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
	return;
}
void CMegaSection7::OnBnClickedOk()
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


//void CMegaSection7::OnCbnSelchangeNoY()
//{
//	UpdateData();
//	// TODO: 在此添加控件通知处理程序代码
//	int no[5] = {2,3,4,5,6};
//	v_bar_y = no[m_bar_y.GetCurSel()];
//}
//
//
//void CMegaSection7::OnCbnSelchangeNoX()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	UpdateData();
//	int no[5] = {2,3,4,5,6};
//	v_bar_x = no[m_bar_x.GetCurSel()];
//}


void CMegaSection7::OnCbnSelchangeBarD()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	//	int bard[10]={8,10,12,14,16,20,25,28,32,40};
	v_bar_d = GlobalPara::bard[m_bar_d.GetCurSel()];
}




void CMegaSection7::OnCbnSelchangeConClass()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString conmat;
	m_con_class.GetWindowText(conmat);		
	Tools::ConMatStringCatch(conmat);
}

void CMegaSection7::OnCbnSelchangeStruClass()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	v_stru_class = m_stru_class.GetCurSel();
}


void CMegaSection7::OnCbnSelchangeExpClass()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	v_exp_class = m_exp_class.GetCurSel();
}

int CMegaSection7::SetBarMp(int BarMp)
{
	for(int i=0;i<barmp_no;i++){
		if(BarMp==GlobalPara::barmp[i]){
			return i;
		}
	}
	return 0;
}

int CMegaSection7::SetBarD(int BarD)
{
	//	int bard[10]={8,10,12,14,16,20,25,28,32,40};
	for(int i=0;i<10;i++){
		if(BarD == GlobalPara::bard[i]){
			return i;
		}
	}
	return 0 ;
}

void CMegaSection7::OnStnClickedArrangeBmp()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMegaSection7::OnCbnSelchangeSteelFy2()
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


void CMegaSection7::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 __super::OnPaint()
	DrawSectOnPic();
}


void CMegaSection7::OnEnKillfocusS7Hc()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_no_y=int(m_sect7_hc/150.+1+0.99);
	UpdateData(FALSE);

	SetGlobalPara();
	DrawSectOnPic();

}


void CMegaSection7::OnEnKillfocusS7Bc()
{

	// TODO: 在此添加控件通知处理程序代码
	UpdateData();	
	m_no_x=int(m_sect7_bc/150.+1+0.99);
	UpdateData(FALSE);

	SetGlobalPara();
	DrawSectOnPic();

}


void CMegaSection7::OnEnKillfocusBarY()
{
	// TODO: 在此添加控件通知处理程序代码
	SetGlobalPara();
	DrawSectOnPic();

}


void CMegaSection7::OnEnKillfocusBarX()
{
	// TODO: 在此添加控件通知处理程序代码
	SetGlobalPara();
	DrawSectOnPic();

}


void CMegaSection7::OnEnKillfocusPC()
{
	// TODO: 在此添加控件通知处理程序代码
	SetGlobalPara();
	DrawSectOnPic();

}


void CMegaSection7::OnEnKillfocusPD()
{
	// TODO: 在此添加控件通知处理程序代码
	SetGlobalPara();
	DrawSectOnPic();

}
void CMegaSection7::DrawSectOnPic()
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

void CMegaSection7::OnEnKillfocusEditCsz()
{
	// TODO: 在此添加控件通知处理程序代码
	SetGlobalPara();
	DrawSectOnPic();

}


void CMegaSection7::OnEnKillfocusEditCsy()
{
	// TODO: 在此添加控件通知处理程序代码
	SetGlobalPara();
	DrawSectOnPic();

}


