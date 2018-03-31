// SectionSel.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "SectionSel.h"
#include "afxdialogex.h"
#include "MegaSection1.h"
#include "MegaSection2.h"
#include "MegaSection3.h"
#include "MegaSection4.h"
#include "MegaSection5.h"
#include "MegaSection6.h"
#include "MegaSection7.h"
#include "MegaSection8.h"
#include "GlobalPara.h"
#include <stdio.h>


// CSectionSel 对话框

IMPLEMENT_DYNAMIC(CSectionSel, CDialog)

CSectionSel::CSectionSel(CWnd* pParent /*=NULL*/)
	: CDialog(CSectionSel::IDD, pParent)
{

}

CSectionSel::~CSectionSel()
{
}

void CSectionSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSectionSel, CDialog)
	ON_BN_CLICKED(IDC_SECT1, &CSectionSel::OnBnClickedSect1)
	ON_BN_CLICKED(IDC_SECT2, &CSectionSel::OnBnClickedSect2)
	ON_BN_CLICKED(IDC_SECT3, &CSectionSel::OnBnClickedSect3)
	ON_BN_CLICKED(IDC_SECT4, &CSectionSel::OnBnClickedSect4)
	ON_BN_CLICKED(IDC_SECT5, &CSectionSel::OnBnClickedSect5)
	ON_BN_CLICKED(IDC_SECT6, &CSectionSel::OnBnClickedSect6)
	ON_BN_CLICKED(IDC_SECT7, &CSectionSel::OnBnClickedSect7)
	ON_BN_CLICKED(IDC_SECT8, &CSectionSel::OnBnClickedSect8)
END_MESSAGE_MAP()


// CSectionSel 消息处理程序


void CSectionSel::OnBnClickedSect1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	
	GlobalPara::m_Sect_in.m_kind=1;
	ReadGloblePara(GlobalPara::m_Sect_in.m_kind);
	CMegaSection2 pdlg;	
	if(pdlg.DoModal()==IDOK)  WriteGloblePara(GlobalPara::m_Sect_in.m_kind);	
}


void CSectionSel::OnBnClickedSect2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	GlobalPara::m_Sect_in.m_kind=2;
	ReadGloblePara(GlobalPara::m_Sect_in.m_kind);
	CMegaSection1 pdlg;		
	if(pdlg.DoModal()==IDOK)  WriteGloblePara(GlobalPara::m_Sect_in.m_kind);
}


void CSectionSel::OnBnClickedSect3()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	GlobalPara::m_Sect_in.m_kind=3;
	ReadGloblePara(GlobalPara::m_Sect_in.m_kind);
	CMegaSection3 pdlg;		
	if(pdlg.DoModal()==IDOK)  WriteGloblePara(GlobalPara::m_Sect_in.m_kind);
}


void CSectionSel::OnBnClickedSect4()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	GlobalPara::m_Sect_in.m_kind=4;
	ReadGloblePara(GlobalPara::m_Sect_in.m_kind);
	CMegaSection5 pdlg;	
	if(pdlg.DoModal()==IDOK)  WriteGloblePara(GlobalPara::m_Sect_in.m_kind);
}


void CSectionSel::OnBnClickedSect5()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	GlobalPara::m_Sect_in.m_kind=5;
	ReadGloblePara(GlobalPara::m_Sect_in.m_kind);
	CMegaSection4 pdlg;	
	if(pdlg.DoModal()==IDOK)  WriteGloblePara(GlobalPara::m_Sect_in.m_kind);

}


void CSectionSel::OnBnClickedSect6()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	GlobalPara::m_Sect_in.m_kind=6;
	ReadGloblePara(GlobalPara::m_Sect_in.m_kind);
	CMegaSection6 pdlg;
	
	if(pdlg.DoModal()==IDOK)  WriteGloblePara(GlobalPara::m_Sect_in.m_kind);

}


void CSectionSel::OnBnClickedSect7()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	GlobalPara::m_Sect_in.m_kind=7;
	ReadGloblePara(GlobalPara::m_Sect_in.m_kind);
	CMegaSection7 pdlg;	
	if(pdlg.DoModal()==IDOK)  WriteGloblePara(GlobalPara::m_Sect_in.m_kind);

}

void CSectionSel::OnBnClickedSect8()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	GlobalPara::m_Sect_in.m_kind=8;
	ReadGloblePara(GlobalPara::m_Sect_in.m_kind);
	CMegaSection8 pdlg;	
	if(pdlg.DoModal()==IDOK)  WriteGloblePara(GlobalPara::m_Sect_in.m_kind);

}

BOOL CSectionSel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	HBITMAP hBitmap1,hBitmap2,hBitmap3,hBitmap4,hBitmap5,hBitmap6,hBitmap7,hBitmap8;
	hBitmap1 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_SECT1));
	hBitmap2 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_SECT2));
	hBitmap3 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_SECT3));
	hBitmap4 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_SECT4));
	hBitmap5 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_SECT5));
	hBitmap6 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_SECT6));
	hBitmap7 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_SECT8));
	hBitmap8 = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_SECT7));
	((CButton*)GetDlgItem(IDC_SECT1))->SetBitmap(hBitmap1);
	((CButton*)GetDlgItem(IDC_SECT2))->SetBitmap(hBitmap2);
	((CButton*)GetDlgItem(IDC_SECT3))->SetBitmap(hBitmap3);
	((CButton*)GetDlgItem(IDC_SECT4))->SetBitmap(hBitmap4);
	((CButton*)GetDlgItem(IDC_SECT5))->SetBitmap(hBitmap5);
	((CButton*)GetDlgItem(IDC_SECT6))->SetBitmap(hBitmap6);
	((CButton*)GetDlgItem(IDC_SECT7))->SetBitmap(hBitmap7);
	((CButton*)GetDlgItem(IDC_SECT8))->SetBitmap(hBitmap8);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSectionSel::WriteGloblePara(int Sectkind)
{
	CString FileName=GetInitFileName();
	CString SectName;
	SectName.Format("SectionKind %d",Sectkind);	
	CString ch;
	SectDescribe *ps=&GlobalPara::m_Sect_in;
	ch.Format("%d",ps->m_kind );  
	WritePrivateProfileString(SectName,_T("Kind"),ch,FileName);

	ch.Format("%d,%d",ps->Sect_b,ps->Sect_h );  
	WritePrivateProfileString(SectName,_T("SectionSize"),ch,FileName);

	ch.Format("%d,%d,%d",ps->RotateType,ps->HSect_x,ps->HSect_y);  
	WritePrivateProfileString(SectName,_T("ProfileCoord"),ch,FileName);

	ch.Format("%d,%d,%d",ps->HSect_mat,ps->Concrete_mat,ps->Bar_mat);  
	WritePrivateProfileString(SectName,_T("Materials"),ch,FileName);

	ch.Format("%d,%d,%d,%d,%d,%d",ps->Bar_d,ps->Bar_layers,ps->Bar_interval,ps->Bar_circleR,ps->Bar_num_hside,ps->Bar_num_bside);  
	WritePrivateProfileString(SectName,_T("Rebar"),ch,FileName);

	ch.Format("%d,%d,%d",ps->Concrete_coverd,ps->Con_coverd_x,ps->Con_coverd_y);  
	WritePrivateProfileString(SectName,_T("Cover"),ch,FileName);

	ch.Format("%f,%f,%f,%d",ps->Transversal_ratio,ps->Tran_ratio_x,ps->Tran_ratio_y,ps->TransversalBar_mat);  
	WritePrivateProfileString(SectName,_T("Stirrup"),ch,FileName);

	ch.Format("%f,%f",ps->MV_ratio_x,ps->MV_ratio_y);  
	WritePrivateProfileString(SectName,_T("MV"),ch,FileName);


	// 型钢信息
	ch.Format("%d",GlobalPara::m_Sect_in.HSect.KIND );  
	WritePrivateProfileString(SectName,_T("HSect.KIND"),ch,FileName);
	ch=_T(GlobalPara::m_Sect_in.HSect.NAME);
	WritePrivateProfileString(SectName,_T("HSect.NAME"),ch,FileName);
	ch=_T(GlobalPara::m_Sect_in.HSect.NAME1);
	WritePrivateProfileString(SectName,_T("HSect.NAME1"),ch,FileName);

	SECTION *p=&GlobalPara::m_Sect_in.HSect;

	ch.Format("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		p->B1,p->B2,p->B3,p->H1,p->H2, p->H3,p->T1,p->T2,p->T3,p->T4,p->T5,p->T6,p->M);  
	WritePrivateProfileString(SectName,_T("HSect.Data1"),ch,FileName);

	ch.Format("%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		p->RI,p->RJ,p->UA,p->Xc,p->Yc, p->Rx,p->Ry,p->Fy,p->Fv,p->W1x,p->W1y,p->W2x,p->W2y);  
	WritePrivateProfileString(SectName,_T("HSect.Data2"),ch,FileName);

	ch.Format("%d,%d,%f,%f,%f,%f,%f,%f,%f,%f",
		p->TypeX,p->TypeY,p->Rc,p->A,p->Ix, p->Iy,p->Ix1,p->Iy1,p->Sw,p->Sf);  
	WritePrivateProfileString(SectName,_T("HSect.Data3"),ch,FileName);

	DesnPara* pd=&GlobalPara::m_DesnPara;

	ch.Format("%d,%d,%d,%d,%f,%f,%f,%f",
		pd->ProType,pd->ProLevel,pd->Struc_Class,pd->Exp_Class,pd->stud_d,pd->stud_len,pd->stud_fu,pd->stud_fy);  

	WritePrivateProfileString(SectName,_T("DesnPara"),ch,FileName);

/*
	//钢材信息
	m_DesnPara.ProType
		m_DesnPara.ProLevel

		//环境等级
		m_DesnPara.Struc_Class
		m_DesnPara.Exp_Class

		//栓钉信息
		m_DesnPara.stud_d
		m_DesnPara.stud_len
		m_DesnPara.stud_fu
		m_DesnPara.stud_fy	
*/
}


void CSectionSel::ReadGloblePara(int Sectkind)
{
	char buff[1000];
	CString FileName=GetInitFileName();
	CString SectName;
	SectName.Format("SectionKind %d",Sectkind);	
	CString ch;
	SectDescribe *ps=&GlobalPara::m_Sect_in;
	ps->m_kind = GetPrivateProfileInt(SectName,_T("Kind"),1,FileName);	

	GetPrivateProfileString(SectName,_T("SectionSize"),"",buff,sizeof(buff),FileName);
	sscanf(buff,"%d,%d",&ps->Sect_b,&ps->Sect_h);

	GetPrivateProfileString(SectName,_T("ProfileCoord"),"",buff,sizeof(buff),FileName);
	sscanf(buff,"%d,%d,%d",&ps->RotateType,&ps->HSect_x,&ps->HSect_y);

	GetPrivateProfileString(SectName,_T("Materials"),"",buff,sizeof(buff),FileName);
	sscanf(buff,"%d,%d,%d",&ps->HSect_mat,&ps->Concrete_mat,&ps->Bar_mat);

	GetPrivateProfileString(SectName,_T("Rebar"),"",buff,sizeof(buff),FileName);
	sscanf(buff,"%d,%d,%d,%d,%d,%d",&ps->Bar_d,&ps->Bar_layers,&ps->Bar_interval,&ps->Bar_circleR,&ps->Bar_num_hside,&ps->Bar_num_bside);

	GetPrivateProfileString(SectName,_T("Cover"),"",buff,sizeof(buff),FileName);
	sscanf(buff,"%d,%d,%d",&ps->Concrete_coverd,&ps->Con_coverd_x,&ps->Con_coverd_y);

	GetPrivateProfileString(SectName,_T("Stirrup"),"",buff,sizeof(buff),FileName);
	sscanf(buff,"%f,%f,%f,%d",&ps->Transversal_ratio,&ps->Tran_ratio_x,&ps->Tran_ratio_y,&ps->TransversalBar_mat);

	GetPrivateProfileString(SectName,_T("MV"),"",buff,sizeof(buff),FileName);
	sscanf(buff,"%f,%f",&ps->MV_ratio_x,&ps->MV_ratio_y);

	SECTION *p=&GlobalPara::m_Sect_in.HSect;

	GetPrivateProfileString(SectName,_T("HSect.KIND"),"",buff,sizeof(buff),FileName);
	sscanf(buff,"%d",&p->KIND);

	GetPrivateProfileString(SectName,_T("HSect.NAME"),"",p->NAME,sizeof(p->NAME),FileName);
	GetPrivateProfileString(SectName,_T("HSect.NAME1"),"",p->NAME1,sizeof(p->NAME1),FileName);
	

	GetPrivateProfileString(SectName,_T("HSect.Data1"),"",buff,sizeof(buff),FileName);
	sscanf(buff,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&p->B1,&p->B2,&p->B3,&p->H1,&p->H2, &p->H3,&p->T1,&p->T2,&p->T3,&p->T4,&p->T5,&p->T6,&p->M);

	GetPrivateProfileString(SectName,_T("HSect.Data2"),"",buff,sizeof(buff),FileName);
	sscanf(buff,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		&p->RI,&p->RJ,&p->UA,&p->Xc,&p->Yc, &p->Rx,&p->Ry,&p->Fy,&p->Fv,&p->W1x,&p->W1y,&p->W2x,&p->W2y);

	GetPrivateProfileString(SectName,_T("HSect.Data3"),"",buff,sizeof(buff),FileName);
	sscanf(buff,"%d,%d,%f,%f,%f,%f,%f,%f,%f,%f",
		&p->TypeX,&p->TypeY,&p->Rc,&p->A,&p->Ix, &p->Iy,&p->Ix1,&p->Iy1,&p->Sw,&p->Sf);

	DesnPara* pd=&GlobalPara::m_DesnPara;

	GetPrivateProfileString(SectName,_T("DesnPara"),"",buff,sizeof(buff),FileName);
	sscanf(buff,"%d,%d,%d,%d,%f,%f,%f,%f",
		&pd->ProType,&pd->ProLevel,&pd->Struc_Class,&pd->Exp_Class,&pd->stud_d,&pd->stud_len,&pd->stud_fu,&pd->stud_fy);
}


CString CSectionSel::GetInitFileName(void)
{
	CString FileName=_T("");
	TCHAR tcExePath[MAX_PATH] = {0};  
	::GetModuleFileName(NULL, tcExePath, MAX_PATH);  
	TCHAR *pFind = _tcsrchr(tcExePath, '\\');  
	if (pFind == NULL)  
	{  
		return FileName;  
	}  
	*pFind = '\0';  

	FileName = tcExePath;  
	FileName += _T("\\");  
	FileName += _T("MageColumn.ini");  

	return FileName ;
}
