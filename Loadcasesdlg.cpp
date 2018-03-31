// Loadcasesdlg.cpp : ʵ���ļ�
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

// CLoadcasesdlg �Ի���

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


// CLoadcasesdlg ��Ϣ�������


BOOL CLoadcasesdlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	OnBnClickedCheckcase1();
	OnBnClickedCheckcase2();
	OnBnClickedCheckcase3();
	OnBnClickedCheckcase4();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
// 	Titles.Format("%s","��0");
// 	Titles_Len = Titles.GetLength();
// 	nColmnWidth = 60;
// 	m_loads_list.InsertColumn(4,Titles,LVCFMT_CENTER,nColmnWidth,-1);
// 	Titles.Format("%s","��1");
// 	Titles_Len = Titles.GetLength();
// 	nColmnWidth = 60;
// 	m_loads_list.InsertColumn(5,Titles,LVCFMT_CENTER,nColmnWidth,-1);
// 	Titles.Format("%s","��2");
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CLoadcasesdlg::OnBnClickedCheckcase1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void CLoadcasesdlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
	DrawCol();

	
}

//�칤����ĳ����ĳ������ظ��������������ͣ�����or���У���������ֵ(P1\P2\X1\X2)
void CLoadcasesdlg::DrawCol()
{
	float x0,y0,x1,y1;
	int cenghao,xianxing,xiankuan,yanse,fanhui;
	int ihing,iloadtype[100],nload,nstep;
	float hcol,bili,r;
	float y1loadcol[100],y2loadcol[100],P1loadcol[100],P2loadcol[100];
	//��ͼ
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
	
	//1��������
	x0=0.f;
	y0=0.f;
	x1=0.f;
	y1=220;
	hcol=18000;//�칤�����ң�����mmGPara::m_DesnPara->Lens
	bili=hcol/y1;
	cenghao=1;
	xianxing=1;
	xiankuan=4;
	yanse=10;
	fanhui=0;
	DrawCol_col(cenghao,xianxing,xiankuan,yanse,fanhui,x0,y0,x1,y1);

	//2�����½���Ϣ
	ihing=4;//�칤�����ң��½���Ϣ0,1,2,3,4�����˹̽ӣ��½£��Ͻ£����˽£����ۣ�GPara::m_DesnPara->Restrict
	r=4;
	xiankuan=2;
	yanse=14;
	DrawCol_yueshu(cenghao,xianxing,xiankuan,yanse,fanhui,ihing,r,x0,y0,x1,y1);

	//3��������֧��
	xiankuan=3;
	yanse=7;
	DrawCol_zhizuo(cenghao,xianxing,xiankuan,yanse,fanhui,ihing,x0,y0,x1,y1);

	//������
	xiankuan=2;
	yanse=5;
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	nload=2;           //�칤�����ң����Ϻ��ظ���
	iloadtype[0]=1;    //�칤�����ң����Ϻ������ͣ�1-���ϼ�������2-�������κ���
	iloadtype[1]=2;    //�칤�����ң����Ϻ��ظ�����1-���ϼ�������2-�������κ���

	y1loadcol[0]=9000; //�칤�����ң����к��ؾ��·��߶�
	P1loadcol[0]=-10.25;  //�칤�����ң����к��ش�С

	y1loadcol[1]=6000;    //�칤�����ң����κ��ؾ��·��߶�
	y2loadcol[1]=6000; //�칤�����ң����κ��ظ߶�
	P2loadcol[1]=-50;   //�칤�����ң����κ����Ϸ�����
	P1loadcol[1]=-100;    //�칤�����ң����κ����·�����
	DrawCol_hezai(cenghao,xianxing,xiankuan,yanse,fanhui,x0,y0,x1,y1,bili,nload,iloadtype,P1loadcol,y1loadcol,P2loadcol,y2loadcol);

	m_pCfgBas->Closfl(iWay);
}


//������
void CLoadcasesdlg::DrawCol_col(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,float x0,float y0,float x1,float y1)
{
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	m_pCfgBas->Line(x0,y0,x1,y1);
}
//��Լ��
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

//��֧��
void CLoadcasesdlg::DrawCol_zhizuo(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,int ihing,float x0,float y0,float x1,float y1)
{
	float x2,x3,x4,x5,x6,x7,x8,x9,x10;
	float y2,y3,y4,y5,y6,y7,y8,y9,y10;
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	if (ihing==0)
	{
		//��֧��
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
		//��֧��
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
		//��֧��
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
		//��֧��
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
		//��֧��
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
		//��֧��
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
		//��֧��
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
		//��֧��
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
		//��֧��
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

//��֧��
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
		if (iloadtype[i]==1)//���ϼ�����
		{
			if (P1loadcol[i]>=0)//P>0 
			{
				//��ͷ����
				y1col=y1loadcol[i]/bili;
				x2=x0-3;
				x3=x2-40; 
				m_pCfgBas->Line(x2,y1col,x3,y1col);
				//��ͷ����
				x4=x2-4;
				y2=y1col+3;
				m_pCfgBas->Line(x2,y1col,x4,y2);
				y3=y1col-3;
				m_pCfgBas->Line(x2,y1col,x4,y3);
				//��ע
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
				//��ͷ����
				y1col=y1loadcol[i]/bili;
				x2=x0+3;
				x3=x2+40; 
				m_pCfgBas->Line(x2,y1col,x3,y1col);
				//��ͷ����
				x4=x2+4;
				y2=y1col+3;
				m_pCfgBas->Line(x2,y1col,x4,y2);
				y3=y1col-3;
				m_pCfgBas->Line(x2,y1col,x4,y3);
				//��ע
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
		else//�������κ���
		{
			y1col=y1loadcol[i]/bili;
			y2col=y2loadcol[i]/bili;
			y3col=y1col+y2loadcol[i]/bili;
			if (P1loadcol[i]>=0&&P2loadcol[i]>=0)//P1>0 P2>0
			{
				x2=x0-6;
				m_pCfgBas->Line(x2,y1col,x2,y3col);

				//�������߼�����
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
				m_pCfgBas->Line(x2,y1col,x3,y1col);//�º���
				m_pCfgBas->Line(x2,y3col,x4,y3col);//�Ϻ���
				m_pCfgBas->Line(x3,y1col,x4,y3col);//��������

				//��ע
				//��
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
				//��
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

				//���м����
				if (y2col/y1<=(1.0/4.0))
				{
					nstep=5;//�ֳ�6��
				} 
				else if (y2col/y1<=(2.0/4.0))
				{
					nstep=10;//�ֳ�11��
				}
				else if (y2col/y1<=(3.0/4.0))
				{
					nstep=15;//�ֳ�16��
				}
				else
				{
					nstep=20;//�ֳ�21��
				}
				istep=y2col/(nstep+1);//ÿ�γ�
				for(int j=0;j<nstep;j++)
				{
					if (P1loadcol[i]>=P2loadcol[i])//��>��
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

				//�������߼�����
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
				m_pCfgBas->Line(x2,y1col,x3,y1col);//�º���
				m_pCfgBas->Line(x2,y3col,x4,y3col);//�Ϻ���
				m_pCfgBas->Line(x3,y1col,x4,y3col);//��������

				//��ע
				//��
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
				//��
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

				//���м����
				if (y2col/y1<=(1.0/4.0))
				{
					nstep=5;//�ֳ�6��
				} 
				else if (y2col/y1<=(2.0/4.0))
				{
					nstep=10;//�ֳ�11��
				}
				else if (y2col/y1<=(3.0/4.0))
				{
					nstep=15;//�ֳ�16��
				}
				else
				{
					nstep=20;//�ֳ�21��
				}
				istep=y2col/(nstep+1);//ÿ�γ�
				for(int j=0;j<nstep;j++)
				{
					if (fabs(P1loadcol[i])>=fabs(P2loadcol[i]))//��>��
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


