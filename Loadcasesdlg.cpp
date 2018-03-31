// Loadcasesdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "Loadcasesdlg.h"
#include "afxdialogex.h"
#include "CfgBas.h"
#include <intrin.h>
#include <math.h>
//#include "GPara.h"

extern "C" __declspec(dllimport) CCfgBas* m_pCfgBas;

// CLoadcasesdlg 对话框

IMPLEMENT_DYNAMIC(CLoadcasesdlg, CDialog)

CLoadcasesdlg::CLoadcasesdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadcasesdlg::IDD, pParent)
{
	m_check1 = 0;
	m_check2 = 0;
	m_check3 = 0;
	m_check4 = 0;
}

CLoadcasesdlg::~CLoadcasesdlg()
{
}

void CLoadcasesdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISLOADS_LIST, m_disloads_list);
//	DDX_Control(pDX, IDC_LOADS_LIST, m_loads_list);
	DDX_Control(pDX, IDC_NODELOADS_LIST, m_nodeloads_list);
	DDX_Check(pDX, IDC_CHECKCASE1, m_check1);
	DDX_Check(pDX, IDC_CHECKCASE2, m_check2);
	DDX_Check(pDX, IDC_CHECKCASE3, m_check3);
	DDX_Check(pDX, IDC_CHECKCASE4, m_check4);
}


BEGIN_MESSAGE_MAP(CLoadcasesdlg, CDialog)
	ON_BN_CLICKED(IDC_CHECKCASE1, &CLoadcasesdlg::OnBnClickedCheckcase1)
	ON_BN_CLICKED(IDC_CHECKCASE2, &CLoadcasesdlg::OnBnClickedCheckcase2)
	ON_BN_CLICKED(IDC_CHECKCASE3, &CLoadcasesdlg::OnBnClickedCheckcase3)
	ON_BN_CLICKED(IDC_CHECKCASE4, &CLoadcasesdlg::OnBnClickedCheckcase4)
	ON_BN_CLICKED(IDC_CON_ADD, &CLoadcasesdlg::OnBnClickedConAdd)
	ON_BN_CLICKED(IDOK, &CLoadcasesdlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoadcasesdlg 消息处理程序


BOOL CLoadcasesdlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	OnBnClickedCheckcase1();
	OnBnClickedCheckcase2();
	OnBnClickedCheckcase3();
	OnBnClickedCheckcase4();

	// TODO:  在此添加额外的初始化
	//LOADlist
// 	m_loads_list.DeleteAllItems();
// 	m_loads_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);
// 	CString Titles;
// 	int Titles_Len;
// 	int nColmnWidth;
// 	Titles.Format("%s","Case");
// 	Titles_Len = Titles.GetLength();
// 	nColmnWidth = 60;
// 	m_loads_list.InsertColumn(1,Titles,LVCFMT_CENTER,nColmnWidth,-1);
// 	Titles.Format("%s","Notatio");
// 	Titles_Len = Titles.GetLength();
// 	nColmnWidth = 60;
// 	m_loads_list.InsertColumn(2,Titles,LVCFMT_CENTER,nColmnWidth,-1);
// 	Titles.Format("%s","Description");
// 	Titles_Len = Titles.GetLength();
// 	nColmnWidth = 200;
// 	m_loads_list.InsertColumn(3,Titles,LVCFMT_CENTER,nColmnWidth,-1);
// 	Titles.Format("%s","Ψ0");
// 	Titles_Len = Titles.GetLength();
// 	nColmnWidth = 60;
// 	m_loads_list.InsertColumn(4,Titles,LVCFMT_CENTER,nColmnWidth,-1);
// 	Titles.Format("%s","Ψ1");
// 	Titles_Len = Titles.GetLength();
// 	nColmnWidth = 60;
// 	m_loads_list.InsertColumn(5,Titles,LVCFMT_CENTER,nColmnWidth,-1);
// 	Titles.Format("%s","Ψ2");
// 	Titles_Len = Titles.GetLength();
// 	nColmnWidth = 60;
// 	m_loads_list.InsertColumn(6,Titles,LVCFMT_CENTER,nColmnWidth,-1);

	//distributed loads
	m_disloads_list.DeleteAllItems();
	m_disloads_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);
 	CString Titles;
 	int Titles_Len;
 	int nColmnWidth;
	Titles.Format("%s","i");
	Titles_Len = Titles.GetLength();
	nColmnWidth = 40;
	m_disloads_list.InsertColumn(1,Titles,LVCFMT_CENTER,nColmnWidth,-1);
	Titles.Format("%s","x1 (mm)");
	Titles_Len = Titles.GetLength();
	nColmnWidth = 60;
	m_disloads_list.InsertColumn(2,Titles,LVCFMT_CENTER,nColmnWidth,-1);
	Titles.Format("%s","q1 (daN/mm)");
	Titles_Len = Titles.GetLength();
	nColmnWidth = 60;
	m_disloads_list.InsertColumn(3,Titles,LVCFMT_CENTER,nColmnWidth,-1);
	Titles.Format("%s","x2 (mm)");
	Titles_Len = Titles.GetLength();
	nColmnWidth = 60;
	m_disloads_list.InsertColumn(4,Titles,LVCFMT_CENTER,nColmnWidth,-1);
	Titles.Format("%s","q2 (daN/mm");
	Titles_Len = Titles.GetLength();
	nColmnWidth = 60;
	m_disloads_list.InsertColumn(5,Titles,LVCFMT_CENTER,nColmnWidth,-1);

	//concentrated loads	
	m_nodeloads_list.DeleteAllItems();
	m_nodeloads_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	Titles.Format("%s","i");
	Titles_Len = Titles.GetLength();
	nColmnWidth = 40;
	m_nodeloads_list.InsertColumn(1,Titles,LVCFMT_CENTER,nColmnWidth,-1);
	Titles.Format("%s","x (mm)");
	Titles_Len = Titles.GetLength();
	nColmnWidth = 60;
	m_nodeloads_list.InsertColumn(2,Titles,LVCFMT_CENTER,nColmnWidth,-1);
	Titles.Format("%s","F (daN)");
	Titles_Len = Titles.GetLength();
	nColmnWidth = 60;
	m_nodeloads_list.InsertColumn(3,Titles,LVCFMT_CENTER,nColmnWidth,-1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CLoadcasesdlg::OnBnClickedCheckcase1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_check1){
		GetDlgItem(IDC_NOTATIO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DESCRIB1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FAI01)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FAI11)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FAI21)->ShowWindow(SW_SHOW);
	}
	else{
		GetDlgItem(IDC_NOTATIO1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DESCRIB1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FAI01)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FAI11)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FAI21)->ShowWindow(SW_HIDE);
	}
}


void CLoadcasesdlg::OnBnClickedCheckcase2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_check2){
		GetDlgItem(IDC_NOTATIO2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DESCRIB2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FAI02)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FAI12)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FAI22)->ShowWindow(SW_SHOW);
	}
	else{
		GetDlgItem(IDC_NOTATIO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DESCRIB2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FAI02)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FAI12)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FAI22)->ShowWindow(SW_HIDE);
	}
}


void CLoadcasesdlg::OnBnClickedCheckcase3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_check3){
		GetDlgItem(IDC_NOTATIO3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DESCRIB3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FAI03)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FAI13)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FAI23)->ShowWindow(SW_SHOW);
	}
	else{
		GetDlgItem(IDC_NOTATIO3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DESCRIB3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FAI03)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FAI13)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FAI23)->ShowWindow(SW_HIDE);
	}
}


void CLoadcasesdlg::OnBnClickedCheckcase4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_check4){
		GetDlgItem(IDC_NOTATIO4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DESCRIB4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FAI04)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FAI14)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FAI24)->ShowWindow(SW_SHOW);
	}
	else{
		GetDlgItem(IDC_NOTATIO4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DESCRIB4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FAI04)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FAI14)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FAI24)->ShowWindow(SW_HIDE);
	}
}


void CLoadcasesdlg::OnBnClickedConAdd()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CLoadcasesdlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
	DrawCol();

	
}

//朱工传入某工况某方向荷载个数、各荷载类型（柱间or集中）、各荷载值(P1\P2\X1\X2)
void CLoadcasesdlg::DrawCol()
{
	float x0,y0,x1,y1;
	int cenghao,xianxing,xiankuan,yanse,fanhui;
	int ihing,iloadtype[100],nload,nstep;
	float hcol,bili,r;
	float y1loadcol[100],y2loadcol[100],P1loadcol[100],P2loadcol[100];
	//画图
	int iWay = 44;
	CString StrFile("d:\\DRAWCOL.t");
	int n1=StrFile.GetLength();
	char FileName[256];
	strcpy(FileName,StrFile);
	FileName[n1]=char(0);
	m_pCfgBas->Openfl(iWay,FileName,n1,n1);
	m_pCfgBas->Nowfil(iWay);
	m_pCfgBas->Tobegin0(iWay);
	int isave=1;
	m_pCfgBas->Ifsave(isave);
	int ibc=15;
	m_pCfgBas->Bcolor(ibc);
	
	//1、画柱子
	x0=0.f;
	y0=0.f;
	x1=0.f;
	y1=220;
	hcol=18000;//朱工传给我：柱高mmGPara::m_DesnPara->Lens
	bili=hcol/y1;
	cenghao=1;
	xianxing=1;
	xiankuan=4;
	yanse=10;
	fanhui=0;
	DrawCol_col(cenghao,xianxing,xiankuan,yanse,fanhui,x0,y0,x1,y1);

	//2、画铰接信息
	ihing=4;//朱工传给我：铰接信息0,1,2,3,4（两端固接，下铰，上铰，两端铰，悬臂）GPara::m_DesnPara->Restrict
	r=4;
	xiankuan=2;
	yanse=14;
	DrawCol_yueshu(cenghao,xianxing,xiankuan,yanse,fanhui,ihing,r,x0,y0,x1,y1);

	//3、画上下支座
	xiankuan=3;
	yanse=7;
	DrawCol_zhizuo(cenghao,xianxing,xiankuan,yanse,fanhui,ihing,x0,y0,x1,y1);

	//画荷载
	xiankuan=2;
	yanse=5;
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	nload=2;           //朱工传给我：柱上荷载个数
	iloadtype[0]=1;    //朱工传给我：柱上荷载类型，1-柱上集中力、2-柱上梯形荷载
	iloadtype[1]=2;    //朱工传给我：柱上荷载个数，1-柱上集中力、2-柱上梯形荷载

	y1loadcol[0]=9000; //朱工传给我：集中荷载距下方高度
	P1loadcol[0]=-10.25;  //朱工传给我：集中荷载大小

	y1loadcol[1]=6000;    //朱工传给我：梯形荷载距下方高度
	y2loadcol[1]=6000; //朱工传给我：梯形荷载高度
	P2loadcol[1]=-50;   //朱工传给我：梯形荷载上方荷载
	P1loadcol[1]=-100;    //朱工传给我：梯形荷载下方荷载
	DrawCol_hezai(cenghao,xianxing,xiankuan,yanse,fanhui,x0,y0,x1,y1,bili,nload,iloadtype,P1loadcol,y1loadcol,P2loadcol,y2loadcol);

	m_pCfgBas->Closfl(iWay);
}


//画柱子
void CLoadcasesdlg::DrawCol_col(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,float x0,float y0,float x1,float y1)
{
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	m_pCfgBas->Line(x0,y0,x1,y1);
}
//画约束
void CLoadcasesdlg::DrawCol_yueshu(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,int ihing,float r,float x0,float y0,float x1,float y1)
{
	float y2;
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	if (ihing==1)
	{
		y2=y0;
		m_pCfgBas->Circle(x0,y2,r);
	} 
	else if (ihing==2)
	{
		y2=y1;
		m_pCfgBas->Circle(x1,y2,r);
	}
	else if (ihing==3)
	{
		y2=y0;
		m_pCfgBas->Circle(x0,y2,r);
		y2=y1;
		m_pCfgBas->Circle(x1,y2,r);
	}
}

//画支座
void CLoadcasesdlg::DrawCol_zhizuo(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,int ihing,float x0,float y0,float x1,float y1)
{
	float x2,x3,x4,x5,x6,x7,x8,x9,x10;
	float y2,y3,y4,y5,y6,y7,y8,y9,y10;
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	if (ihing==0)
	{
		//下支座
		x2=x0-20;
		x3=x0+20;
		y2=y0;
		m_pCfgBas->Line(x0,y2,x2,y2);
		m_pCfgBas->Line(x0,y2,x3,y2);
		x4=x0-4;
		x5=x0-8;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0-12;
		x5=x0-16;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0+4;
		x5=x0;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0+12;
		x5=x0+8;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		//上支座
		x2=x1-20;
		x3=x1+20;
		y2=y1;
		m_pCfgBas->Line(x1,y2,x2,y2);
		m_pCfgBas->Line(x1,y2,x3,y2);
		x4=x1-4;
		x5=x1;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x1-12;
		x5=x1-8;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x1+4;
		x5=x1+8;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x1+12;
		x5=x1+16;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
	} 
	else if (ihing==1)
	{
		//下支座
		x2=x0-20;
		x3=x0+20;
		y2=y0-4;
		m_pCfgBas->Line(x0,y2,x2,y2);
		m_pCfgBas->Line(x0,y2,x3,y2);
		x4=x0-4;
		x5=x0-8;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0-12;
		x5=x0-16;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0+4;
		x5=x0;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0+12;
		x5=x0+8;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		//上支座
		x2=x1-20;
		x3=x1+20;
		y2=y1;
		m_pCfgBas->Line(x1,y2,x2,y2);
		m_pCfgBas->Line(x1,y2,x3,y2);
		x4=x1-4;
		x5=x1;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x1-12;
		x5=x1-8;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x1+4;
		x5=x1+8;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x1+12;
		x5=x1+16;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
	}
	else if (ihing==2)
	{
		//下支座
		x2=x0-20;
		x3=x0+20;
		y2=y0;
		m_pCfgBas->Line(x0,y2,x2,y2);
		m_pCfgBas->Line(x0,y2,x3,y2);
		x4=x0-4;
		x5=x0-8;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0-12;
		x5=x0-16;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0+4;
		x5=x0;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0+12;
		x5=x0+8;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		//上支座
		x2=x1-20;
		x3=x1+20;
		y2=y1+4;
		m_pCfgBas->Line(x1,y2,x2,y2);
		m_pCfgBas->Line(x1,y2,x3,y2);
		x4=x1-4;
		x5=x1;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x1-12;
		x5=x1-8;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x1+4;
		x5=x1+8;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x1+12;
		x5=x1+16;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
	}
	else if (ihing==3)
	{
		//下支座
		x2=x0-20;
		x3=x0+20;
		y2=y0-4;
		m_pCfgBas->Line(x0,y2,x2,y2);
		m_pCfgBas->Line(x0,y2,x3,y2);
		x4=x0-4;
		x5=x0-8;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0-12;
		x5=x0-16;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0+4;
		x5=x0;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0+12;
		x5=x0+8;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		//上支座
		x2=x1-20;
		x3=x1+20;
		y2=y1+4;
		m_pCfgBas->Line(x1,y2,x2,y2);
		m_pCfgBas->Line(x1,y2,x3,y2);
		x4=x1-4;
		x5=x1;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x1-12;
		x5=x1-8;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x1+4;
		x5=x1+8;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x1+12;
		x5=x1+16;
		y3=y2+7;
		m_pCfgBas->Line(x4,y2,x5,y3);
	}
	else if (ihing==4)
	{
		//下支座
		x2=x0-20;
		x3=x0+20;
		y2=y0;
		m_pCfgBas->Line(x0,y2,x2,y2);
		m_pCfgBas->Line(x0,y2,x3,y2);
		x4=x0-4;
		x5=x0-8;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0-12;
		x5=x0-16;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0+4;
		x5=x0;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
		x4=x0+12;
		x5=x0+8;
		y3=y2-7;
		m_pCfgBas->Line(x4,y2,x5,y3);
	} 
}

//画支座
void CLoadcasesdlg::DrawCol_hezai(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,float x0,float y0,float x1,float y1,
	float bili,int nload,int iloadtype[100],float P1loadcol[100],float y1loadcol[100],float P2loadcol[100],float y2loadcol[100])
{
	float x2,x3,x4,x5,x6,x7,x8,x9,x10;
	float y2,y3,y4,y5,y6,y7,y8,y9,y10;
	float y1col,y2col,y3col,istep,xstep,ystep,lstep;
	int nstep;
	int N,n1,IX,IY;
	float Xzf,Yzf,XM,YM,ANGLE;
	CString str;
	char* ZFSTR;
	for(int i=0;i<nload;i++)
	{
		if (iloadtype[i]==1)//柱上集中力
		{
			if (P1loadcol[i]>=0)//P>0 
			{
				//箭头横线
				y1col=y1loadcol[i]/bili;
				x2=x0-3;
				x3=x2-40; 
				m_pCfgBas->Line(x2,y1col,x3,y1col);
				//箭头部分
				x4=x2-4;
				y2=y1col+3;
				m_pCfgBas->Line(x2,y1col,x4,y2);
				y3=y1col-3;
				m_pCfgBas->Line(x2,y1col,x4,y3);
				//标注
				str.Format("%.2f",P1loadcol[i]);
				n1=str.GetLength();
				ZFSTR=str.GetBuffer(str.GetLength());
				N=n1;
				Xzf=x2-3; 
				Yzf=y1col+2;
				XM=n1;
				YM=5;
				IX=1;
				IY=1;
				ANGLE=0;
				m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);
			} 
			else//P<0 
			{
				//箭头横线
				y1col=y1loadcol[i]/bili;
				x2=x0+3;
				x3=x2+40; 
				m_pCfgBas->Line(x2,y1col,x3,y1col);
				//箭头部分
				x4=x2+4;
				y2=y1col+3;
				m_pCfgBas->Line(x2,y1col,x4,y2);
				y3=y1col-3;
				m_pCfgBas->Line(x2,y1col,x4,y3);
				//标注
				str.Format("%.2f",P1loadcol[i]);
				n1=str.GetLength();
				ZFSTR=str.GetBuffer(str.GetLength());
				N=n1;
				Xzf=x2; 
				Yzf=y1col+2;
				XM=n1;
				YM=5;
				IX=3;
				IY=1;
				ANGLE=0;
				m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);
			}
		}
		else//柱上梯形荷载
		{
			y1col=y1loadcol[i]/bili;
			y2col=y2loadcol[i]/bili;
			y3col=y1col+y2loadcol[i]/bili;
			if (P1loadcol[i]>=0&&P2loadcol[i]>=0)//P1>0 P2>0
			{
				x2=x0-6;
				m_pCfgBas->Line(x2,y1col,x2,y3col);

				//画上下线及连线
				if (P1loadcol[i]<=0.0001 && P2loadcol[i]<=0.0001)
				{
					x3=x2;
					x4=x2;
				} 
				else if (P1loadcol[i]<=0.0001 && P2loadcol[i]>0.0001)
				{
					x3=x2;
					x4=x2-10;
				} 
				else if (P2loadcol[i]<=0.0001 && P1loadcol[i]>0.0001)
				{
					x3=x2-10;
					x4=x2;
				}
				else
				{
					x3=x2-10;
					x4=x2-10*(P2loadcol[i]/P1loadcol[i]);
				}
				m_pCfgBas->Line(x2,y1col,x3,y1col);//下横线
				m_pCfgBas->Line(x2,y3col,x4,y3col);//上横线
				m_pCfgBas->Line(x3,y1col,x4,y3col);//两端连线

				//标注
				//下
				str.Format("%.2f",P1loadcol[i]);
				n1=str.GetLength();
				ZFSTR=str.GetBuffer(str.GetLength());
				N=n1;
				Xzf=x2; 
				Yzf=y1col-9;
				XM=n1;
				YM=5;
				IX=1;
				IY=1;
				ANGLE=0;
				m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);
				//上
				str.Format("%.2f",P2loadcol[i]);
				n1=str.GetLength();
				ZFSTR=str.GetBuffer(str.GetLength());
				N=n1;
				Xzf=x2; 
				Yzf=y3col+2;
				XM=n1;
				YM=5;
				IX=1;
				IY=1;
				ANGLE=0;
				m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);

				//画中间的线
				if (y2col/y1<=(1.0/4.0))
				{
					nstep=5;//分成6段
				} 
				else if (y2col/y1<=(2.0/4.0))
				{
					nstep=10;//分成11段
				}
				else if (y2col/y1<=(3.0/4.0))
				{
					nstep=15;//分成16段
				}
				else
				{
					nstep=20;//分成21段
				}
				istep=y2col/(nstep+1);//每段长
				for(int j=0;j<nstep;j++)
				{
					if (P1loadcol[i]>=P2loadcol[i])//下>上
					{
						lstep=fabs(x4)+(nstep-j)/(1.0*(nstep+1))*(fabs(x3)-fabs(x4));
					} 
					else
					{
						lstep=fabs(x3)+(j+1)/(1.0*(nstep+1))*(fabs(x4)-fabs(x3));
					}		
					xstep=x2-lstep+6;
					ystep=y1col+(j+1)*istep;
					m_pCfgBas->Line(x2,ystep,xstep,ystep);
				}
			} 
			else//P1>0 P2>0
			{
				x2=x0+6;
				m_pCfgBas->Line(x2,y1col,x2,y3col);

				//画上下线及连线
				if (fabs(P1loadcol[i])<=0.0001 && fabs(P2loadcol[i])<=0.0001)
				{
					x3=x2;
					x4=x2;
				} 
				else if (fabs(P1loadcol[i])<=0.0001 && fabs(P2loadcol[i])>0.0001)
				{
					x3=x2;
					x4=x2+10;
				} 
				else if (fabs(P2loadcol[i])<=0.0001 && fabs(P1loadcol[i])>0.0001)
				{
					x3=x2+10;
					x4=x2;
				}
				else
				{
					x3=x2+10;
					x4=x2+10*(P2loadcol[i]/P1loadcol[i]);
				}
				m_pCfgBas->Line(x2,y1col,x3,y1col);//下横线
				m_pCfgBas->Line(x2,y3col,x4,y3col);//上横线
				m_pCfgBas->Line(x3,y1col,x4,y3col);//两端连线

				//标注
				//下
				str.Format("%.2f",P1loadcol[i]);
				n1=str.GetLength();
				ZFSTR=str.GetBuffer(str.GetLength());
				N=n1;
				Xzf=x2; 
				Yzf=y1col-9;
				XM=n1;
				YM=5;
				IX=3;
				IY=1;
				ANGLE=0;
				m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);
				//上
				str.Format("%.2f",P2loadcol[i]);
				n1=str.GetLength();
				ZFSTR=str.GetBuffer(str.GetLength());
				N=n1;
				Xzf=x2; 
				Yzf=y3col+2;
				XM=n1;
				YM=5;
				IX=3;
				IY=1;
				ANGLE=0;
				m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);

				//画中间的线
				if (y2col/y1<=(1.0/4.0))
				{
					nstep=5;//分成6段
				} 
				else if (y2col/y1<=(2.0/4.0))
				{
					nstep=10;//分成11段
				}
				else if (y2col/y1<=(3.0/4.0))
				{
					nstep=15;//分成16段
				}
				else
				{
					nstep=20;//分成21段
				}
				istep=y2col/(nstep+1);//每段长
				for(int j=0;j<nstep;j++)
				{
					if (fabs(P1loadcol[i])>=fabs(P2loadcol[i]))//下>上
					{
						lstep=fabs(x4)+(nstep-j)/(1.0*(nstep+1))*(fabs(x3)-fabs(x4));
					} 
					else
					{
						lstep=fabs(x3)+(j+1)/(1.0*(nstep+1))*(fabs(x4)-fabs(x3));
					}		
					xstep=x2+lstep-6;
					ystep=y1col+(j+1)*istep;
					m_pCfgBas->Line(x2,ystep,xstep,ystep);
				}
			}
		}
	}
}


