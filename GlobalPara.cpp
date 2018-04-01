#include "StdAfx.h"
#include "GlobalPara.h"
#include "CfgBas.h"
#include <math.h>
#include "CfgFun1.h"
#include "Tools.h"


bool GlobalPara::ExpertMode = false;
DesnPara GlobalPara::m_DesnPara;
SectDescribe GlobalPara::m_Sect_in;
membercheck_rst GlobalPara::m_Rst;

int GlobalPara::bard[bard_no];
int GlobalPara::barmp[barmp_no];
int GlobalPara::confck[confck_no];
int GlobalPara::profy[profy_no];

int GlobalPara::bard_euro[bard_no]={8,10,12,14,16,20,25,28,32,40};
int GlobalPara::barmp_euro[barmp_no]={420,500};
int GlobalPara::confck_euro[confck_no]={20,25,30,35,40,45,50,55,60};
int GlobalPara::profy_euro[profy_no]={355,420,460,500};

// CArray<mega_loads,mega_loads> GlobalPara::m_loads1_z;		//dead load
// CArray<mega_loads,mega_loads> GlobalPara::m_loads1_y;		//dead load
// CArray<mega_loads,mega_loads> GlobalPara::m_loads2_z;		//live1-3
// CArray<mega_loads,mega_loads> GlobalPara::m_loads2_y;		//live1-3
// CArray<mega_loads,mega_loads> GlobalPara::m_loads3_z;
// CArray<mega_loads,mega_loads> GlobalPara::m_loads3_y;
// CArray<mega_loads,mega_loads> GlobalPara::m_loads4_z;
// CArray<mega_loads,mega_loads> GlobalPara::m_loads4_y;
int GlobalPara::currentload = 0;
int GlobalPara::currentside = 1;
int GlobalPara::currentsect = 0;

float GlobalPara::Pro_Fy;
float GlobalPara::Bar_Fy;
float GlobalPara::ks_y;
float GlobalPara::ks_z;
float GlobalPara::fiber_draw_ratio_y;
float GlobalPara::fiber_draw_ratio_z;
double GlobalPara::Iin[6];

CArray<mega_loads> GlobalPara::LoadCaseData;

CArray<mega_loads,mega_loads> m_loadCase;

double GlobalPara::M_Cu[4][FirbePoints];
double GlobalPara::N_Cu[4][FirbePoints];

/*int GlobalPara::nLoadCase = 0;*/

extern "C" __declspec(dllimport) CCfgBas* m_pCfgBas;

GlobalPara::GlobalPara(void)
{
}


GlobalPara::~GlobalPara(void)
{
}

//初始化参数
void GlobalPara::initPara(int CodeType)
{
	//通用信息
	GlobalPara::m_DesnPara.m_Gravity = 10;
	GlobalPara::m_DesnPara.m_Density = 7850;	//钢材密度
	GlobalPara::m_DesnPara.m_Possion = 0.3;
	GlobalPara::m_DesnPara.m_Conp = 2500;
	GlobalPara::m_DesnPara.ifSecondEffect = true;
	GlobalPara::m_DesnPara.shearmethod = 1;
	//材料初始化
	GlobalPara::m_DesnPara.ProType = 2;
	GlobalPara::m_DesnPara.ProLevel = 1;
	GlobalPara::Bar_Fy = 400;
	//构件信息初始化
	GlobalPara::m_DesnPara.Lens = 9;		//m
	GlobalPara::m_DesnPara.Restrict = 3;		//铰接信息0,1,2,3,4（两端固接，左下铰，右上铰，两端铰,悬臂）
	GlobalPara::m_DesnPara.uL = 1.f;
	GlobalPara::m_DesnPara.Struc_Class = 3;
	GlobalPara::m_DesnPara.Exp_Class = 1;
	//荷载参数初始化
	GlobalPara::m_DesnPara.f1_y = 1.f;
	GlobalPara::m_DesnPara.f2_y = 1.f;
	GlobalPara::m_DesnPara.f3_y = 1.f;
	GlobalPara::m_DesnPara.f1_z = 1.f;
	GlobalPara::m_DesnPara.f2_z = 1.f;
	GlobalPara::m_DesnPara.f3_z = 1.f;
	//栓钉初始化
	GlobalPara::m_DesnPara.stud_d = 25;
	GlobalPara::m_DesnPara.stud_len = 100;
	GlobalPara::m_DesnPara.stud_fu = 450;
	GlobalPara::m_DesnPara.stud_fy = 350;
	//欧洲规范混凝土用的
	GlobalPara::m_DesnPara.RH = 74.5;
	GlobalPara::m_DesnPara.day_t0 = 28;
	//荷载组合
	GlobalPara::m_DesnPara.rGinf2= 1.0;
	for(int i=0;i<Max_Combines;i++)
		GlobalPara::m_DesnPara.combbeta[i] = 0.75;
	if(CodeType==1){
		GlobalPara::m_DesnPara.CodeType = 1;
		GlobalPara::m_DesnPara.gama0 = 1.0;
		GlobalPara::m_DesnPara.gama1 = 1.0;
		GlobalPara::m_DesnPara.rs = 1.15;
		GlobalPara::m_DesnPara.rc = 1.5;
		GlobalPara::m_DesnPara.faib = 1.f;
		GlobalPara::m_DesnPara.faic = 1.f;
		//规范材料初始化
		memcpy(GlobalPara::bard,GlobalPara::bard_euro,sizeof(int)*bard_no);
		memcpy(GlobalPara::barmp,GlobalPara::barmp_euro,sizeof(int)*barmp_no);
		memcpy(GlobalPara::confck,GlobalPara::confck_euro,sizeof(int)*confck_no);
		memcpy(GlobalPara::profy,GlobalPara::profy_euro,sizeof(int)*profy_no);
		GlobalPara::m_DesnPara.rGsup = 1.35;
		GlobalPara::m_DesnPara.rGinf = 1.00;
		GlobalPara::m_DesnPara.rQ1   = 1.5;
		GlobalPara::m_DesnPara.rQ2	 = 1.3;
		GlobalPara::m_DesnPara.con_model = 0;
		GlobalPara::m_DesnPara.EC_beta = 0.75f;
	}
	else if(CodeType==2){
		GlobalPara::m_DesnPara.CodeType = 2;
		GlobalPara::m_DesnPara.faib = 0.9;
		GlobalPara::m_DesnPara.faic = 0.75;
		GlobalPara::m_DesnPara.rGsup = 1.4;
		GlobalPara::m_DesnPara.rGinf = 1.2;
		GlobalPara::m_DesnPara.rQ1   = 1.6;
		GlobalPara::m_DesnPara.con_model = 1;
	}
	else if(CodeType==3){
		GlobalPara::m_DesnPara.faib = 1.f;
		GlobalPara::m_DesnPara.faic = 1.f;
		GlobalPara::m_DesnPara.rGsup = 1.35;
		GlobalPara::m_DesnPara.rGinf = 1.2;
		GlobalPara::m_DesnPara.rQ1   = 1.4;
		GlobalPara::m_DesnPara.con_model = 2;
	}
	GlobalPara::m_Sect_in.Bar_d = 40;
	GlobalPara::m_Sect_in.Sect_b = 3072;
	GlobalPara::m_Sect_in.Sect_h = 3072;
	GlobalPara::m_Sect_in.Bar_num_bside = 56;
	GlobalPara::m_Sect_in.Bar_num_hside = 56;
	GlobalPara::m_Sect_in.m_kind = 3;
	GlobalPara::m_Sect_in.Concrete_coverd = 50;
	GlobalPara::m_Sect_in.Con_coverd_x = 86;
	GlobalPara::m_Sect_in.Con_coverd_y = 86;
	GlobalPara::m_Sect_in.Bar_mat = 500;		//mp
	GlobalPara::m_Sect_in.HSect_mat = 2;
	GlobalPara::m_Sect_in.Concrete_mat = 50;
	GlobalPara::m_Sect_in.HSect_x = 1012;
	GlobalPara::m_Sect_in.HSect_y = 950;
	GlobalPara::m_Sect_in.Transversal_ratio = 1.f;
	GlobalPara::m_Sect_in.Tran_ratio_x = 1.f;
	GlobalPara::m_Sect_in.Tran_ratio_y = 1.f;
	GlobalPara::m_Sect_in.TransversalBar_mat = 400;
	GlobalPara::m_DesnPara.ifCrackCheck = false;
	//无侧移
	//本构曲线初始化
	initbengou();
	//钢材本构
	for(int i=0;i<6;i++){
		GlobalPara::m_DesnPara.E1[i] = 206000.f;
		GlobalPara::m_DesnPara.E2[i] = 0.01f;
		GlobalPara::m_DesnPara.Fy[i] = 345;
		GlobalPara::m_DesnPara.Fu[i] = 470;
		memset(GlobalPara::m_DesnPara.prop_e[i],0,sizeof(float)*26);
		memset(GlobalPara::m_DesnPara.prop_f[i],0,sizeof(float)*26); 
	}
	Tools::CalProPoint(GlobalPara::m_DesnPara.E1[0],0.01*GlobalPara::m_DesnPara.E1[0],GlobalPara::m_DesnPara.Fy[0],GlobalPara::m_DesnPara.Fu[0]);

	GlobalPara::m_DesnPara.con_model = 0;

	GlobalPara::m_DesnPara.My_hasmidforce = false;
	GlobalPara::m_DesnPara.Mz_hasmidforce = false;
	GlobalPara::m_DesnPara.conc_mesh = 100;
	GlobalPara::m_DesnPara.profile_mesh = 20;
}

void GlobalPara::initbengou()
{
	float e1[26]={0,0.00011,0.00022,0.00033,0.00044,0.00055,0.00066,0.00077,0.00088,0.00099,0.0011,0.00121,0.00132,0.00143,0.00154,0.00165,0.00176,0.00187,0.00198,0.00209,0.0022,0.00246,0.00272,0.00298,0.00324,0.0035};
	float f1[26]={0,3.715376,7.238679,10.5699,13.7094,16.65729,19.41375,21.97894,24.35304,26.53622,28.52866,30.33053,31.942,33.36324,34.59443,35.63573,36.48732,37.14938,37.62206,37.90554,38.0,37.47282,35.89279,33.26215,29.58313,24.85795};
	memcpy(GlobalPara::m_DesnPara.con_e,e1,sizeof(e1));
	memcpy(GlobalPara::m_DesnPara.con_f,f1,sizeof(f1));
}

//保存
bool GlobalPara::SavePara()
{
	return 0;
}

//读取
bool GlobalPara::LoadPara()
{
	return 0;
}

void MyUserCs2d(float X0,float Y0,float ang,float BL)
{
	float PRCS[9];
	PRCS[0] = X0;
	PRCS[1] = Y0;
	PRCS[2] = 0;

	if (fabs(BL)<1E-9)
	{
		BL=1;
	}
	PRCS[3] = 1./BL;
	PRCS[4] = 1./BL;
	PRCS[5] = 1./BL;


	PRCS[6] = 0;
	PRCS[7] = 0;
	PRCS[8] = ang;

	m_pCfgBas->Usercs(PRCS);

}

void MyUserCs2DEnlarge(float X0,float Y0,float ang,float Sc)	 
{
	float PRCS[9];
	PRCS[0] = X0;
	PRCS[1] = Y0;
	PRCS[2] = 0;

	PRCS[3] = Sc;
	PRCS[4] = Sc;
	PRCS[5] = Sc;


	PRCS[6] = 0;
	PRCS[7] = 0;
	PRCS[8] = ang;

	m_pCfgBas->Usercs(PRCS);

}
void MyUserCs2DExit()
{
	m_pCfgBas->Outucs();
}


void GlobalPara::DrawColImp(const int currentload,const int side,
	CArray<mega_loads>* pTmpload,bool bShowInTFile,float xOri,float yOri,float scl,int nHighType,int nHighidx)
{

	//nHighType 2=集中 3=分布


	float x0,y0,x1,y1;
	int cenghao,xianxing,xiankuan,yanse,fanhui;
	int ihing,iloadtype[100],nload,nstep;
	float hcol,bili,r;
	float y1loadcol[100],y2loadcol[100],P1loadcol[100],P2loadcol[100];
	float htop;
	//画图
	

	if (true/*bShowInTFile*/)
	{
		int iWay = 99;
		m_pCfgBas->Closfl(iWay);
		CString StrFile("DRAWCOL.t");
		int n1=StrFile.GetLength();
		char FileName[256];
		strcpy(FileName,StrFile);
		FileName[n1]=char(0);
		m_pCfgBas->Closfl(iWay);
		m_pCfgBas->Setcfg();
		m_pCfgBas->Openfl(iWay,FileName,n1,n1);
		//m_pCfgBas->Redrw();
		m_pCfgBas->Nowfil(iWay);
		m_pCfgBas->Tobegin0(iWay);
		int isave=1;
		m_pCfgBas->Ifsave(isave);
		int ibc=15;
		m_pCfgBas->Bcolor(ibc);
		m_pCfgBas->Nowbcl(ibc);
	}


	//1、画柱子
	x0=xOri;
	y0=yOri;

	x1=x0;
	y1=y0+220;
	htop=y1;
	hcol = 1000*GlobalPara::m_DesnPara.Lens;

	MyUserCs2d(x0,y0,0,scl);
	//	hcol=18000;//朱工传给我：柱高mmGPara::m_DesnPara->Lens
	bili=hcol/220;
	cenghao=1;
	xianxing=1;
	xiankuan=4;
	yanse=10;
	fanhui=0;
	DrawCol_col(cenghao,xianxing,xiankuan,yanse,fanhui,x0,y0,x1,y1);

	//2、画铰接信息
	ihing=GlobalPara::m_DesnPara.Restrict;//朱工传给我：铰接信息0,1,2,3,4（两端固接，下铰，上铰，两端铰，悬臂）GPara::m_DesnPara->Restrict
	r=4;
	xiankuan=2;
	yanse=14;
	DrawCol_yueshu(cenghao,xianxing,xiankuan,yanse,fanhui,ihing,r,x0,y0,x1,y1);

	//3、画上下支座
	xiankuan=3;
	yanse=7;
	DrawCol_zhizuo(cenghao,xianxing,xiankuan,yanse,fanhui,ihing,x0,y0,x1,y1);

	CArray<mega_loads> LoadCaseDataTemp;
	if (pTmpload!=NULL)
	{
		LoadCaseDataTemp.Append(*pTmpload);
	}
	else
	{
		LoadCaseDataTemp.Append(GlobalPara::LoadCaseData);
	}
	//Mega_Cases::Get().Cases();
	if(LoadCaseDataTemp.GetSize()>0)
	{
		//画荷载
		xiankuan=2;
		yanse=5;
		m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
		int conloads,disloads;
		if(0==side){	//yy向
			conloads = LoadCaseDataTemp[currentload].ConYY.GetSize();
			disloads = LoadCaseDataTemp[currentload].DisYY.GetSize();
			nload=conloads+disloads;           //朱工传给我：柱上荷载个数
			for(int i=0;i<conloads;i++)
			{
				iloadtype[i]=1;
				y1loadcol[i] = LoadCaseDataTemp[currentload].ConYY[i].x;
				P1loadcol[i] = LoadCaseDataTemp[currentload].ConYY[i].F;
			}
			for(int j=conloads;j<nload;j++)
			{
				iloadtype[j]=2;
				y1loadcol[j] = LoadCaseDataTemp[currentload].DisYY[j-conloads].x1;
				y2loadcol[j] = LoadCaseDataTemp[currentload].DisYY[j-conloads].x2-y1loadcol[j];
				P1loadcol[j] = LoadCaseDataTemp[currentload].DisYY[j-conloads].q1;
				P2loadcol[j] = LoadCaseDataTemp[currentload].DisYY[j-conloads].q2;
			}
		}
		else if(1==side){
			conloads = LoadCaseDataTemp[currentload].ConZZ.GetSize();
			disloads = LoadCaseDataTemp[currentload].DisZZ.GetSize();
			nload=conloads+disloads;           //朱工传给我：柱上荷载个数
			for(int i=0;i<conloads;i++){
				iloadtype[i]=1;
				y1loadcol[i] = LoadCaseDataTemp[currentload].ConZZ[i].x;
				P1loadcol[i] = LoadCaseDataTemp[currentload].ConZZ[i].F;
			}
			for(int j=conloads;j<nload;j++){
				iloadtype[j]=2;
				y1loadcol[j] = LoadCaseDataTemp[currentload].DisZZ[j-conloads].x1;
				y2loadcol[j] = LoadCaseDataTemp[currentload].DisZZ[j-conloads].x2-y1loadcol[j];
				P1loadcol[j] = LoadCaseDataTemp[currentload].DisZZ[j-conloads].q1;
				P1loadcol[j] = LoadCaseDataTemp[currentload].DisZZ[j-conloads].q2;
			}
		}
		if (1==nHighType)
		{
			nHighidx = nHighidx;
		}
		else if (2 == nHighType)
		{
			nHighidx += conloads;
		}
		//	iloadtype[0]=1;    //朱工传给我：柱上荷载类型，1-柱上集中力、2-柱上梯形荷载
		//	iloadtype[1]=2;    //朱工传给我：柱上荷载个数，1-柱上集中力、2-柱上梯形荷载

		// 	y1loadcol[0]=9000; //朱工传给我：集中荷载距下方高度
		// 	P1loadcol[0]=-10.25;  //朱工传给我：集中荷载大小
		// 
		// 	y1loadcol[1]=6000;    //朱工传给我：梯形荷载距下方高度
		// 	y2loadcol[1]=6000; //朱工传给我：梯形荷载高度
		// 	P2loadcol[1]=-50;   //朱工传给我：梯形荷载上方荷载
		// 	P1loadcol[1]=-100;    //朱工传给我：梯形荷载下方荷载
		
		float Ntop,Mtop,Mdown;
		if(side==0){
			Ntop=LoadCaseDataTemp[currentload].AnxialForceYY;
			Mtop=LoadCaseDataTemp[currentload].EndmYY.Top;
			Mdown = LoadCaseDataTemp[currentload].EndmYY.Bottom;
		}
		else{
			Ntop = LoadCaseDataTemp[currentload].AnxialForceZZ;
			Mtop = LoadCaseDataTemp[currentload].EndmZZ.Top;
			Mdown = LoadCaseDataTemp[currentload].EndmZZ.Bottom;
		}
		DrawCol_hezai(cenghao,xianxing,xiankuan,yanse,fanhui,x0,y0,x1,y1,bili,nload,iloadtype,P1loadcol,y1loadcol,P2loadcol,y2loadcol,htop,Ntop,Mtop,Mdown,nHighType, nHighidx);
	}

	//	m_pCfgBas->Closfl(iWay);
	MyUserCs2DExit();

}
//朱工传入某工况某方向荷载个数、各荷载类型（柱间or集中）、各荷载值(P1\P2\X1\X2)
void GlobalPara::DrawCol(const int currentload,const int side)
{
//	DrawColImp(currentload,side,&LoadCaseData,true);
}


//画柱子
void GlobalPara::DrawCol_col(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,float x0,float y0,float x1,float y1)
{
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	m_pCfgBas->Line(x0,y0,x1,y1);
}

//画柱子
void GlobalPara::DrawCol_col3D(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,float x0,float y0,float x1,float y1)
{
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
// 	m_pCfgBas->Line(x0,y0,x1,y1);

	int nWidCol;
	CCfgFun1::MyUserCs3dXOY(x0,y0);






}

//画约束
void GlobalPara::DrawCol_yueshu(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,int ihing,float r,float x0,float y0,float x1,float y1)
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
void GlobalPara::DrawCol_zhizuo(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,int ihing,float x0,float y0,float x1,float y1)
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

//画荷载
void GlobalPara::DrawCol_hezai(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,float x0,float y0,float x1,float y1,
	float bili,int nload,int iloadtype[100],float P1loadcol[100],float y1loadcol[100],float P2loadcol[100],float y2loadcol[100],
	float htop,float Ntop,float Mtop,float Mdown,int nHightType,int nHighIdx)
{
 
	const int eTyConLoad = 1;
	const int eTyDisLoad = 2;

	int  cenghaoHi=cenghao+1;
	int  yanseHi=6;

	float x2,x3,x4,x5,x6,x7,x8,x9,x10;
	float y2,y3,y4,y5,y6,y7,y8,y9,y10;
	float y1col,y2col,y3col,istep,xstep,ystep,lstep;
	int nstep;
	int N,n1,IX,IY;
	float Xzf,Yzf,XM,YM,ANGLE,r,a0,a1;
	CString str;
	char* ZFSTR;

	for(int i=0;i<nload;i++)
	{
		if (iloadtype[i]==eTyConLoad)//柱上集中力
		{
			if (P1loadcol[i]>=0)//P>0 
			{
				xiankuan=2;
				yanse=5;
				if (eTyConLoad==nHightType&&nHighIdx == i)
				{
					m_pCfgBas->Layers(cenghaoHi,xianxing,xiankuan,yanseHi,fanhui);
				}
				else
				{
					m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
				}
				
				//箭头横线
				y1col=y1loadcol[i]/bili + y0;
				x2=x0-3;
				x3=x2-40; 
				m_pCfgBas->Line(x2,y1col,x3,y1col);
				//箭头部分
				x4=x2-4;
				y2=y1col+3;
				m_pCfgBas->Line(x2,y1col,x4,y2);
				y3=y1col-3;
				m_pCfgBas->Line(x2,y1col,x4,y3);
				//标注文字
				str.Format("P=%.2fkN",P1loadcol[i]);
				n1=str.GetLength();
				ZFSTR=str.GetBuffer(str.GetLength());
				N=n1;
				Xzf=x2-3; 
				Yzf=y1col+2;
				XM=5;
				YM=5;
				IX=1;
				IY=1;
				ANGLE=0;
				m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);
			} 
			else//P<0 
			{
				xiankuan=2;
				yanse=5;
				if (eTyConLoad==nHightType&&nHighIdx == i)
				{
					m_pCfgBas->Layers(cenghaoHi,xianxing,xiankuan,yanseHi,fanhui);
				}
				else
				{
					m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
				}
				//箭头横线
				y1col=y1loadcol[i]/bili + y0;
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
				str.Format("P=%.2fkN",P1loadcol[i]);
				n1=str.GetLength();
				ZFSTR=str.GetBuffer(str.GetLength());
				N=n1;
				Xzf=x2; 
				Yzf=y1col+2;
				XM=5;
				YM=5;
				IX=3;
				IY=1;
				ANGLE=0;
				m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);
			}
			//标注尺寸
			xiankuan=1;
			yanse=7;
			m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);

			x5=x2+60+i*20;
			m_pCfgBas->Line(x5,y0,x5,y1col);//竖线
			x6=x2+35;
			x7=x5+5;
			m_pCfgBas->Line(x6,y1col,x7,y1col);//上横线
			m_pCfgBas->Line(x6,y0,x7,y0);//下横线
			x6=x5-3;
			x7=x5+3;
			y6=y1col-3;
			y7=y1col+3;
			m_pCfgBas->Line(x6,y6,x7,y7);//上斜线
			y6=y0-3;
			y7=y0+3;
			m_pCfgBas->Line(x6,y6,x7,y7);//下斜线

			str.Format("%dmm",int(y1loadcol[i]));
			n1=str.GetLength();
			ZFSTR=str.GetBuffer(str.GetLength());
			N=n1;
			Xzf=x2+60+i*20;
			Yzf=(y1col-y0)/2+y0;
			XM=5;
			YM=5;
			IX=3;
			IY=2;
			ANGLE=0;
			m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);
		}
		else//柱上梯形荷载
		{
			float v3,v4;
			y1col=y1loadcol[i]/bili + y0;
			y2col=y2loadcol[i]/bili + y0;
			y3col=y1col+y2loadcol[i]/bili;
			if (P1loadcol[i]>=0&&P2loadcol[i]>=0)//P1>0 P2>0
			{
				xiankuan=2;
				yanse=5;
				if (eTyDisLoad==nHightType&&nHighIdx == i)
				{
					m_pCfgBas->Layers(cenghaoHi,xianxing,xiankuan,yanseHi,fanhui);
				}
				else
				{
					m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
				}
				x2=x0-6; //x2 =  均布荷载靠近杆件的一侧内边
				m_pCfgBas->Line(x2,y1col,x2,y3col); //靠近杆件的内线  y1=最下 y3=最上

				//画上下线及连线
				if (P1loadcol[i]<=0.0001 && P2loadcol[i]<=0.0001)
				{
					x3=x2;
					x4=x2;
					v3 = -6;
					v4 = -6;
				} 
				else if (P1loadcol[i]<=0.0001 && P2loadcol[i]>0.0001)
				{
					x3=x2;
					x4=x2-10;

					v3 = -6;
					v4 = -16;

				} 
				else if (P2loadcol[i]<=0.0001 && P1loadcol[i]>0.0001)
				{
					x3=x2-10;
					x4=x2;

					v3 = -16;
					v4 = -6;
				}
				else
				{
					x3=x2-10;
					x4=x2-10*(P2loadcol[i]/P1loadcol[i]);

					v3 = -16;
					v4 = -16*(P2loadcol[i]/P1loadcol[i]);
				}
				m_pCfgBas->Line(x2,y1col,x3,y1col);//下横线
				m_pCfgBas->Line(x2,y3col,x4,y3col);//上横线
				m_pCfgBas->Line(x3,y1col,x4,y3col);//两端连线

				//标注
				//下
				str.Format("q1=%.2fkN/m",P1loadcol[i]);
				n1=str.GetLength();
				ZFSTR=str.GetBuffer(str.GetLength());
				N=n1;
				Xzf=x2; 
				Yzf=y1col-9;
				XM=5;
				YM=5;
				IX=1;
				IY=1;
				ANGLE=0;
				m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);
				//上
				str.Format("q2=%.2fkN/m",P2loadcol[i]);
				n1=str.GetLength();
				ZFSTR=str.GetBuffer(str.GetLength());
				N=n1;
				Xzf=x2; 
				Yzf=y3col+2;
				XM=5;
				YM=5;
				IX=1;
				IY=1;
				ANGLE=0;
				m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);

				//画中间的线
				if ((y2col-y0)/(y1-y0)<=(1.0/4.0))
				{
					nstep=5;//分成6段
				} 
				else if ((y2col-y0)/(y1-y0)<=(2.0/4.0))
				{
					nstep=10;//分成11段
				}
				else if ((y2col-y0)/(y1-y0)<=(3.0/4.0))
				{
					nstep=15;//分成16段
				}
				else
				{
					nstep=20;//分成21段
				}
				istep=(y2col-y0)/(nstep+1);//每段长
				for(int j=0;j<nstep;j++)
				{
					if (P1loadcol[i]>=P2loadcol[i])//下>上
					{
						lstep=fabs(v4)+(nstep-j)/(1.0*(nstep+1))*(fabs(v3)-fabs(v4));
					} 
					else
					{
						lstep=fabs(v3)+(j+1)/(1.0*(nstep+1))*(fabs(v4)-fabs(v3));
					}		
					xstep=x2-lstep+6;
					ystep=y1col+(j+1)*istep;
					m_pCfgBas->Line(x2,ystep,xstep,ystep);
				}
			} 
			else//P1>0 P2>0
			{
				xiankuan=2;
				yanse=5;
				if (eTyDisLoad==nHightType&&nHighIdx == i)
				{
					m_pCfgBas->Layers(cenghaoHi,xianxing,xiankuan,yanseHi,fanhui);
				}
				else
				{
					m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
				}
				x2=x0+6;
				m_pCfgBas->Line(x2,y1col,x2,y3col);

				//画上下线及连线
				if (fabs(P1loadcol[i])<=0.0001 && fabs(P2loadcol[i])<=0.0001)
				{
					x3=x2;
					x4=x2;
					v3 = 6;
					v4 = 6;
				} 
				else if (fabs(P1loadcol[i])<=0.0001 && fabs(P2loadcol[i])>0.0001)
				{
					x3=x2;
					x4=x2+10;
					v3 = 6;
					v4 = 16;
				} 
				else if (fabs(P2loadcol[i])<=0.0001 && fabs(P1loadcol[i])>0.0001)
				{
					x3=x2+10;
					x4=x2;

					v3 = 16;
					v4 = 6;
				}
				else
				{
					x3=x2+10;
					x4=x2+10*(P2loadcol[i]/P1loadcol[i]);

					v3 = 6+10;
					v4 = 6+10*(P2loadcol[i]/P1loadcol[i]);
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
				if ((y2col-y0)/(y1-y0)<=(1.0/4.0))
				{
					nstep=5;//分成6段
				} 
				else if ((y2col-y0)/(y1-y0)<=(2.0/4.0))
				{
					nstep=10;//分成11段
				}
				else if ((y2col-y0)/(y1-y0)<=(3.0/4.0))
				{
					nstep=15;//分成16段
				}
				else
				{
					nstep=20;//分成21段
				}
				istep=(y2col-y0)/(nstep+1);//每段长
				for(int j=0;j<nstep;j++)
				{
					if (fabs(P1loadcol[i])>=fabs(P2loadcol[i]))//下>上
					{
						lstep=fabs(v4)+(nstep-j)/(1.0*(nstep+1))*(fabs(v3)-fabs(v4));
					} 
					else
					{
						lstep=fabs(v3)+(j+1)/(1.0*(nstep+1))*(fabs(v4)-fabs(v3));
					}		
					xstep=x2+lstep-6;
					ystep=y1col+(j+1)*istep;
					m_pCfgBas->Line(x2,ystep,xstep,ystep);
				}
			}
			//标注尺寸
			xiankuan=1;
			yanse=7;
			m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);

			x5=x2+3+60+i*20;
			m_pCfgBas->Line(x5,y0,x5,y3col);//竖线
			x6=x2+3+35;
			x7=x5+5;
			m_pCfgBas->Line(x6,y3col,x7,y3col);//上横线
			m_pCfgBas->Line(x6,y0,x7,y0);//下横线
			m_pCfgBas->Line(x6,y1col,x7,y1col);//中横线
			x6=x5-3;
			x7=x5+3;
			y6=y3col-3;
			y7=y3col+3;
			m_pCfgBas->Line(x6,y6,x7,y7);//上斜线
			y6=y0-3;
			y7=y0+3;
			m_pCfgBas->Line(x6,y6,x7,y7);//下斜线
			y6=y1col-3;
			y7=y1col+3;
			m_pCfgBas->Line(x6,y6,x7,y7);//中斜线

			str.Format("%dmm",int(y1loadcol[i]));
			n1=str.GetLength();
			ZFSTR=str.GetBuffer(str.GetLength());
			N=n1;
			Xzf=x2+3+60+i*20; 
			Yzf=(y1col-y0)/2+y0;
			XM=5;
			YM=5;
			IX=3;
			IY=2;
			ANGLE=0;
			m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE); //长度

			str.Format("%dmm",int(y2loadcol[i]));
			n1=str.GetLength();
			ZFSTR=str.GetBuffer(str.GetLength());
			N=n1;
			Xzf=x2+3+60+i*20; 
			Yzf=y1col+(y2col-y0)/2;
			XM=5;
			YM=5;
			IX=3;
			IY=2;
			ANGLE=0;
			m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE); //起始点
		}
	}

	//柱端附加荷载
	xiankuan=2;
	yanse=11;
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	//Ntop
	if (Ntop>0.0001)
	{
		y2=htop+12;
		y3=htop+50;
		m_pCfgBas->Line(x0,y2,x0,y3);//竖线
		x2=x0-3;
		x3=x0+3;
		y3=y2+4;
		m_pCfgBas->Line(x0,y2,x2,y3);//箭头
		m_pCfgBas->Line(x0,y2,x3,y3);//箭头

		str.Format("N=%.2fkN",Ntop);
		n1=str.GetLength();
		ZFSTR=str.GetBuffer(str.GetLength());
		N=n1;
		Xzf=x0-25; 
		Yzf=htop+52;
		XM=5;
		YM=5;
		IX=3;
		IY=1;
		ANGLE=0;
		m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);
	}
	//Mtop
	if (fabs(Mtop)>0.0001)
	{
		r=12;
		a0=0;
		a1=180;
		y2=htop+15;
		m_pCfgBas->Arc(x0,y2,r,a0,a1);
		str.Format("M=%.2fkN·m",Mtop);
		n1=str.GetLength();
		ZFSTR=str.GetBuffer(str.GetLength());
		N=n1;
		Xzf=x0+20; 
		Yzf=htop+15;
		XM=5;
		YM=5;
		IX=3;
		IY=1;
		ANGLE=0;
		m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);
		if (Mtop>0)
		{
			x2=x0+r;
			x3=x2-3;
			x4=x2+3;
			y3=y2+4;
		} 
		else
		{
			x2=x0-r;
			x3=x2-3;
			x4=x2+3;
			y3=y2+4;
		}
		m_pCfgBas->Line(x2,y2,x3,y3);//箭头
		m_pCfgBas->Line(x2,y2,x4,y3);//箭头
	}
	//Mdown
	if (fabs(Mdown)>0.0001)
	{
		r=12;
		a0=180;
		a1=0;
		y2=y0-15;
		m_pCfgBas->Arc(x0,y2,r,a0,a1);
		str.Format("M=%.2fkN·m",Mdown);
		n1=str.GetLength();
		ZFSTR=str.GetBuffer(str.GetLength());
		N=n1;
		Xzf=x0+20; 
		Yzf=y0-20;
		XM=5;
		YM=5;
		IX=3;
		IY=1;
		ANGLE=0;
		m_pCfgBas->Drawzf(N,ZFSTR,n1,Xzf,Yzf,XM,YM,IX,IY,ANGLE);
		if (Mdown>0)
		{
			x2=x0+r;
			x3=x2-3;
			x4=x2+3;
			y3=y2-4;
		} 
		else
		{
			x2=x0-r;
			x3=x2-3;
			x4=x2+3;
			y3=y2-4;
		}
		m_pCfgBas->Line(x2,y2,x3,y3);//箭头
		m_pCfgBas->Line(x2,y2,x4,y3);//箭头
	}
}

//          3,   2
//       0(4),   1
//  return  多边形顶点数。圆为1
int GlobalPara::GetMegaColPoly(float xp[], float yp[])
{
	int n=0;
	if(m_Sect_in.m_kind==2||m_Sect_in.m_kind==5) 
	{
		n=1;
		xp[0]=0.5*m_Sect_in.Sect_b;
		yp[0]=0.5*m_Sect_in.Sect_b;
		xp[2]=0.5*m_Sect_in.Sect_b;
	}
	else 
	{
		n=4;
		xp[0]=xp[3]=xp[4]=-0.5*m_Sect_in.Sect_b;
		xp[1]=xp[2]=0.5*m_Sect_in.Sect_b;
		yp[0]=yp[1]=yp[4]=-0.5*m_Sect_in.Sect_h;
		yp[2]=yp[3]=0.5*m_Sect_in.Sect_h;

	}
	return n;
}
//
//                             7                                                6 
//                              8                       9    4                5
//                                                        |     |
//                                                        |     | 
//                               11                    10   3                2
//                                0    								          1
int GlobalPara::GetProfilePoly(float x0,float y0,float ang,float xp[],float yp[])
{
	float PI=3.14159265359;
	float ang1=ang+0.5*PI;
	int n=12;	
	float HSect_b = m_Sect_in.HSect.B1;
	float HSect_h = m_Sect_in.HSect.H1;
	float HSect_tw = m_Sect_in.HSect.RI;
	float HSect_tf = m_Sect_in.HSect.RJ;	

	xp[0] = xp[11] = xp[8] = xp[7] = -HSect_b*0.5;
	xp[1] = xp[2] = xp[5] = xp[6] = HSect_b*0.5;
	xp[10] = xp[9] = -HSect_tw*0.5;
	xp[3] = xp[4] = HSect_tw*0.5;

	yp[0] = yp[1] = -HSect_h*0.5;
	yp[2] = yp[3] = yp[10] = yp[11] =-HSect_h*0.5+HSect_tf;
	yp[4] = yp[5] = yp[8] = yp[9] = HSect_h*0.5-HSect_tf;	
	yp[6] = yp[7] = HSect_h*0.5;

	if(fabs(ang)>0.000001)
	{
		for(int i=0;i<n;i++ )
		{
			float xtmp=xp[i];
			float ytmp=yp[i];
			xp[i]=xtmp*cos(ang)+ytmp*sin(ang);
			yp[i]=xtmp*cos(ang1)+ytmp*sin(ang1);
		}
	}

	for(int i=0;i<n;i++)
	{
		xp[i]+=x0;
		yp[i]+=y0;
	}
	xp[n]=xp[0];
	yp[n]=yp[0];
	return n;
}

