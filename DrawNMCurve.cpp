#include "StdAfx.h"
#include "DrawNMCurve.h"
#include "GlobalPara.h"
#include "CfgBas.h"
//#include "SatweCombWallInfo.h"
//#include "SecBeearCapacity.h"
#include "SecToMesh_Inc.h"
#include "MeshGrid.h"
#include "Tools.h"
#include <fstream>
#include "Inteface_Mega.h"
#include "ICommonInfoOut_C.h"
using namespace std;

extern "C" __declspec(dllimport) CCfgBas* m_pCfgBas;

extern "C" __declspec( dllimport ) 
	void GetProPara(int ProType,float TT,int ProNo,int code,float &fy,int &ProE);
extern "C" __declspec( dllimport ) 
	void GetBarE(int code,int &BarE);
extern "C" __declspec( dllimport ) 
	void GetSLSCombine(double &My,double &Mz,double &MMix,double &N);

extern "C" __declspec( dllimport ) void DrawNMPoints(float ratio,double Iin[],int yz);

DrawNMCurve::DrawNMCurve(void)
{
}


DrawNMCurve::~DrawNMCurve(void)
{
}

void DrawNMCurve::GSect_Mesh()
{
	CMeshGrid pdlg;
	pdlg.DoModal();
	SectDescribe Sec1;
	Sec1.m_kind=GlobalPara::m_Sect_in.m_kind;
	if(Sec1.m_kind==2 || Sec1.m_kind==5){
		Sec1.Sect_h=0.5*GlobalPara::m_Sect_in.Sect_h;
		Sec1.Sect_b=0.5*GlobalPara::m_Sect_in.Sect_b;
	}
	else{
		Sec1.Sect_h=GlobalPara::m_Sect_in.Sect_h;
		Sec1.Sect_b=GlobalPara::m_Sect_in.Sect_b;
	}
	Sec1.HSect.B1=GlobalPara::m_Sect_in.HSect.B1;
	Sec1.HSect.B2=GlobalPara::m_Sect_in.HSect.B1;
	Sec1.HSect.H1=GlobalPara::m_Sect_in.HSect.H1;
	Sec1.HSect.RI=GlobalPara::m_Sect_in.HSect.RI;
	Sec1.HSect.RJ=GlobalPara::m_Sect_in.HSect.RJ;
	Sec1.HSect.KIND = 16;
	Sec1.RotateType=0;
	Sec1.HSect_x=GlobalPara::m_Sect_in.HSect_x;	//+Sec1.HSect.B1/2;
	Sec1.HSect_y=GlobalPara::m_Sect_in.HSect_y; //450+Sec1.HSect.H1/2;
	Sec1.Concrete_coverd=GlobalPara::m_Sect_in.Concrete_coverd;
	Sec1.Bar_num_bside=GlobalPara::m_Sect_in.Bar_num_bside;
	Sec1.Bar_num_hside=GlobalPara::m_Sect_in.Bar_num_hside;
	Sec1.Bar_d=GlobalPara::m_Sect_in.Bar_d;
	Sec1.Bar_circleR=GlobalPara::m_Sect_in.Bar_d;

	if(GlobalPara::currentsect==0)
		GetReguSec(Sec1);
	MakeSec();
	Mesh(GlobalPara::m_DesnPara.conc_mesh,GlobalPara::m_DesnPara.profile_mesh);
}

void DrawNMCurve::CalColmNMCurve_Fiber()
{
	int nPro = 1;
	SHOW_RUNINFO_DLG();
	{
		SET_ANALYZEITEM("1.Start",8);
		ADDTXT_TORUNINFODLG("Start",6);
		SET_RUNINFO_PROGRESS(nPro);
	}
	
// 	SectDescribe Sec1;
// 	memcpy(&Sec1,GlobalPara::m_Sect_in,sizeof(SectDescribe));
// 	Sec1.m_kind=1;
// 	Sec1.Sect_h=2000;
// 	Sec1.Sect_b=2000;
// 	Sec1.HSect.B1=500;
// 	Sec1.HSect.B2=500;
// 	Sec1.HSect.H1=500;
// 	Sec1.HSect.RI=100;
// 	Sec1.HSect.RJ=100;
// 	Sec1.RotateType=0;
// 	Sec1.HSect_x=450+Sec1.HSect.B1/2;
// 	Sec1.HSect_y=450+Sec1.HSect.H1/2;
// 	Sec1.Concrete_coverd=50;
// 	Sec1.Bar_num_bside=8;
// 	Sec1.Bar_num_hside=2;
// 	Sec1.Bar_d=16;
// 	Sec1.Bar_circleR=16;
/*	CSecToMesh Meshprepare1(GlobalPara::m_Sect_in);
	Meshprepare1.mesh();
 	CSecBeearCapacity SecBeear(Meshprepare1);
	CConcretMat_Chinese conc_cn(3e4,30,1.64e-3,3.3*1.64e-3,1.36);
	CShapeSteelMat ShapeSteel;
	ShapeSteel.Add_Stress_Strain(-0.0018,-360);
	ShapeSteel.Add_Stress_Strain(-0.003,-360);
	ShapeSteel.Add_Stress_Strain(0.0018,360);
	ShapeSteel.Add_Stress_Strain(0.003,360);


	CBarMat BarMat;
	BarMat.Add_Stress_Strain(-0.0018,-360);
	BarMat.Add_Stress_Strain(-0.003,-360);
	BarMat.Add_Stress_Strain(0.0018,360);
	BarMat.Add_Stress_Strain(0.003,360);
	//SecBeear.AddConc(conc);
	SecBeear.AddConc_cn(conc_cn);
	SecBeear.AddSteel(ShapeSteel);
	SecBeear.AddBarMat(BarMat);
	vector<double>NM;
	int AA=22;
	NM.resize(22);
	SecBeear.CalNM(NM);
	
	*/
	int cenghao,xianxing,xiankuan,yanse,fanhui;
	int N,n2,IX,IY;
	float Xzf,Yzf,XM,YM,ANGLE;
	CString str;
	char* ZFSTR;
	SectDescribe Sec1;
	Sec1.m_kind=GlobalPara::m_Sect_in.m_kind;
	if(Sec1.m_kind==2 || Sec1.m_kind==5){
		Sec1.Sect_h=0.5*GlobalPara::m_Sect_in.Sect_h;
		Sec1.Sect_b=0.5*GlobalPara::m_Sect_in.Sect_b;
	}
	else{
		Sec1.Sect_h=GlobalPara::m_Sect_in.Sect_h;
		Sec1.Sect_b=GlobalPara::m_Sect_in.Sect_b;
	}
	Sec1.HSect.B1=GlobalPara::m_Sect_in.HSect.B1;
	Sec1.HSect.B2=GlobalPara::m_Sect_in.HSect.B1;
	Sec1.HSect.H1=GlobalPara::m_Sect_in.HSect.H1;
	Sec1.HSect.RI=GlobalPara::m_Sect_in.HSect.RI;
	Sec1.HSect.RJ=GlobalPara::m_Sect_in.HSect.RJ;
	Sec1.HSect.KIND = 16;
	Sec1.RotateType=0;
	Sec1.HSect_x=GlobalPara::m_Sect_in.HSect_x;	//+Sec1.HSect.B1/2;
	Sec1.HSect_y=GlobalPara::m_Sect_in.HSect_y; //450+Sec1.HSect.H1/2;
	Sec1.Concrete_coverd=GlobalPara::m_Sect_in.Concrete_coverd;
	Sec1.Bar_num_bside=GlobalPara::m_Sect_in.Bar_num_bside;
	Sec1.Bar_num_hside=GlobalPara::m_Sect_in.Bar_num_hside;
	Sec1.Bar_d=GlobalPara::m_Sect_in.Bar_d;
	Sec1.Bar_circleR=GlobalPara::m_Sect_in.Bar_d;

	{
		nPro = 5;
		SET_ANALYZEITEM("1.Mesh",7);
		ADDTXT_TORUNINFODLG("Mesh",5);
		SET_RUNINFO_PROGRESS(nPro);
	}

	GetReguSec(Sec1);
	MakeSec();
	Mesh(GlobalPara::m_DesnPara.conc_mesh,GlobalPara::m_DesnPara.profile_mesh);


	{
		nPro = 10;
		SET_ANALYZEITEM("2.SetConc",10);
		ADDTXT_TORUNINFODLG("SetConc",8);
		SET_RUNINFO_PROGRESS(nPro);
	}

	//WrtieGrid();
	//ReadGrid();
//	CConcretMat conc;
	double e1;
	double f1;
	if(GlobalPara::m_DesnPara.con_model==0){
		float Ecm,fcm,ec1,ecu1;
		int fck = GlobalPara::m_Sect_in.Concrete_mat;
		Tools::GetEuroCodeConcPara(fck,Ecm,fcm,ec1,ecu1);
		SetConc_UR(Ecm,fcm,ec1,ecu1);
	}
	else if(GlobalPara::m_DesnPara.con_model==1){
		float f0,e0,ecu;
		int fck = GlobalPara::m_Sect_in.Concrete_mat;
		Tools::GetUSCodeConcPara(fck,f0,e0,ecu);
		SetConc_US(f0,e0,ecu);
	}
	else if(GlobalPara::m_DesnPara.con_model==2){
		float E,fcr,ecr,ecu,acr;
		int fck = GlobalPara::m_Sect_in.Concrete_mat;
		Tools::GetCHCodeConcPara(fck,E,fcr,ecr,ecu,acr);
		fcr = fck;	//标准值的时候
		SetConc_CN(E,fcr,ecr,ecu,acr);
	}
	else if(GlobalPara::m_DesnPara.con_model==3){
		vector<vector<double>> ss;
		ss.reserve(50);
		vector<double>container1 (2);
		for(int i=1;i<26;i++){
			e1 = -1.f*GlobalPara::m_DesnPara.con_e[i];
			f1 = -1.f*GlobalPara::m_DesnPara.con_f[i];
			container1[0]=e1;
			container1[1]=f1;
			ss.push_back(container1);
		}
		SetConc_Custom(ss);
	}

	{
		nPro = 15;
		SET_ANALYZEITEM("3.GetBarE",10);
		ADDTXT_TORUNINFODLG("GetBarE",8);
		SET_RUNINFO_PROGRESS(nPro);
	}

	float Profy;
	int ProE,BarE;
	GetProPara(GlobalPara::m_DesnPara.ProType,GlobalPara::m_Sect_in.HSect.RI,GlobalPara::m_DesnPara.ProLevel,GlobalPara::m_DesnPara.CodeType,Profy,ProE);
	GetBarE(GlobalPara::m_DesnPara.CodeType,BarE);
//	SetShapeMat(360,2e5);
	double ProE_d = ProE*1.f;
//	SetShapeMat(GlobalPara::m_DesnPara.ProType,GlobalPara::m_DesnPara.ProLevel,ProE_d);
//	SetBarMat(360,2e5);

	{
		nPro = 15;
		SET_ANALYZEITEM("4.SetShapeMat",14);
		ADDTXT_TORUNINFODLG("SetShapeMat",12);
		SET_RUNINFO_PROGRESS(nPro);
	}
	if(GlobalPara::m_DesnPara.ProType<4){
		SetShapeMat_Regu(GlobalPara::m_DesnPara.ProType,GlobalPara::m_DesnPara.ProLevel,ProE_d);
	}
	else{
		vector<vector<double>> ss1;
		vector<vector<double>> ss2;
		ss1.reserve(50);
		ss2.reserve(50);
		vector<double>container1 (2);
		vector<double>container2 (2);
		for(int i=1;i<26;i++){
			e1 = -1.f*GlobalPara::m_DesnPara.prop_e[0][i];
			f1 = -1.f*GlobalPara::m_DesnPara.prop_f[0][i];
			container1[0]=e1;
			container1[1]=f1;
			e1 = -1.f*GlobalPara::m_DesnPara.prop_e[1][i];
			f1 = -1.f*GlobalPara::m_DesnPara.prop_f[1][i];
			container2[0]=e1;
			container2[1]=f1;
			ss1.push_back(container1);
			ss2.push_back(container2);
		}
		for(int i=1;i<26;i++){
			e1 = GlobalPara::m_DesnPara.prop_e[0][i];
			f1 = GlobalPara::m_DesnPara.prop_f[0][i];
			container1[0]=e1;
			container1[1]=f1;
			e1 = GlobalPara::m_DesnPara.prop_e[1][i];
			f1 = GlobalPara::m_DesnPara.prop_f[1][i];
			container2[0]=e1;
			container2[1]=f1;
			ss1.push_back(container1);
			ss2.push_back(container2);
		}
		SetShapeMat1_Custom_Regu(ss1);
		SetShapeMat2_Custom_Regu(ss2);
	}
	SetBarMat(GlobalPara::m_Sect_in.Bar_mat,BarE);
	double th=3.14/8;
	double l[2]={1,0};
	SetMomAxis(l);

	{
		nPro = 20;
		SET_ANALYZEITEM("5.Calculation",14);
		ADDTXT_TORUNINFODLG("Calculation",12);
		SET_RUNINFO_PROGRESS(nPro);
	}

	int cal_type=2;
	Calculation(cal_type);
	lwh::vector<double>result;
	//result.reserve(10);

/*	{
		nPro = 25;
		SET_ANALYZEITEM("6. write file NM.txt",19);
		ADDTXT_TORUNINFODLG("write file NM.txt",17);
		SET_RUNINFO_PROGRESS(nPro);
	}*/

	GetResult(result);
 	ofstream outfile("D:\\NM.txt");
 	for(size_t i=0;i<result.size()/2;i++)
 	{
 		outfile<<abs(result[2*i+1])<<"\n";
 	}
 	for(size_t i=0;i<result.size()/2;i++)
 	{
 		outfile<<-result[2*i]<<"\n";
 	}
	outfile.flush();


	//存入数据中
	int npoints = result.size()*0.5;
	GlobalPara::m_DesnPara.Fiberpoints_y_k = npoints;
	for(int i=0;i<npoints;i++)
	{
		GlobalPara::M_Cu[0][i] = abs(result[i*2+1]);
		GlobalPara::N_Cu[0][i] = -result[i*2];
	}
	if(GlobalPara::m_DesnPara.ifCrackCheck){
	//算钢筋应力
  	if(GlobalPara::m_DesnPara.CodeType!=2){	//美国规范不用验算钢筋应力
  		double My,Mz,Mmix,Nmax;
  		double stress;
  		GetSLSCombine(My,Mz,Mmix,Nmax);
  		SetLoad(Nmax*-1.f,Mmix);
  		GetBarStressMax(stress);
  		GlobalPara::m_DesnPara.BarQ = stress;
  	}
	}
	//换一个方向,z向
	l[0] = 0;
	l[1] = 1;
	SetMomAxis(l);


	{
		nPro = 30;
		SET_ANALYZEITEM("6.Calculation",14);
		ADDTXT_TORUNINFODLG("Calculation",12);
		SET_RUNINFO_PROGRESS(nPro);
	}

	Calculation(cal_type);
	GetResult(result);
	npoints = result.size()*0.5;
	GlobalPara::m_DesnPara.Fiberpoints_z_k = npoints;
	for(int i=0;i<npoints;i++)
	{
		GlobalPara::M_Cu[2][i] = abs(result[i*2+1]);
		GlobalPara::N_Cu[2][i] = -result[i*2];
	}
// 	if(GlobalPara::m_DesnPara.CodeType!=2){	//美国规范不用验算钢筋应力
// 		double My,Mz,Mmix,Nmax;
// 		double stress;
// 		GetSLSCombine(My,Mz,Mmix,Nmax);
// 		SetLoad(Nmax*-1.f,Mmix);
// 		GetBarStressMax(stress);
// 		GlobalPara::m_DesnPara.BarQ = stress;
// 	}

	//按照设计值再进行计算
	if(GlobalPara::m_DesnPara.con_model==0){
// 		float Ecm,fcm,ec1,ecu1;
// 		int fck = GlobalPara::m_Sect_in.Concrete_mat;
// 		Tools::GetEuroCodeConcPara(fck,Ecm,fcm,ec1,ecu1);
// 		fcm = fcm/1.5;
// 		SetConc_UR(Ecm,fcm,ec1,ecu1);
		//欧洲规范设计值直接按照自定义本构的方式来计算
		Tools::GetEuroStress(GlobalPara::m_Sect_in.Concrete_mat);
		vector<vector<double>> ss;
		ss.reserve(50);
		vector<double>container1 (2);
		for(int i=1;i<26;i++){
			e1 = -1.f*GlobalPara::m_DesnPara.con_e[i];
			f1 = -1.f*GlobalPara::m_DesnPara.con_f[i];
			f1 = f1/1.5;
			container1[0]=e1;
			container1[1]=f1;
			ss.push_back(container1);
		}
		SetConc_Custom(ss);

	}
	else if(GlobalPara::m_DesnPara.con_model==1){
		float f0,e0,ecu;
		int fck = GlobalPara::m_Sect_in.Concrete_mat;
		Tools::GetUSCodeConcPara(fck,f0,e0,ecu);
		SetConc_US(f0,e0,ecu);
	}
	else if(GlobalPara::m_DesnPara.con_model==2){
		float E,fcr,ecr,ecu,acr;
		int fck = GlobalPara::m_Sect_in.Concrete_mat;
		Tools::GetCHCodeConcPara(fck,E,fcr,ecr,ecu,acr);
		fcr = fck/1.4;	//标准值的时候
		SetConc_CN(E,fcr,ecr,ecu,acr);
	}
	else if(GlobalPara::m_DesnPara.con_model==3){
		// 		for(int i=1;i<26;i++){
		// 			e1 = -1.f*GlobalPara::m_DesnPara.con_e[i];
		// 			f1 = -1.f*GlobalPara::m_DesnPara.con_f[i];
		// 			conc.Add_Stress_Strain(e1,f1);
		// 		}
		// 		SetConc_Custom(conc);
		vector<vector<double>> ss;
		ss.reserve(50);
		vector<double>container1 (2);
		for(int i=1;i<26;i++){
			e1 = -1.f*GlobalPara::m_DesnPara.con_e[i];
			f1 = -1.f*GlobalPara::m_DesnPara.con_f[i];
			f1 = f1/1.5;
			container1[0]=e1;
			container1[1]=f1;
			ss.push_back(container1);
		}
		SetConc_Custom(ss);
	}

	GetProPara(GlobalPara::m_DesnPara.ProType,GlobalPara::m_Sect_in.HSect.RI,GlobalPara::m_DesnPara.ProLevel,GlobalPara::m_DesnPara.CodeType,Profy,ProE);
	GetBarE(GlobalPara::m_DesnPara.CodeType,BarE);
	//	SetShapeMat(360,2e5);
//	double ProE_d = ProE*1.f;
	//	SetShapeMat(GlobalPara::m_DesnPara.ProType,GlobalPara::m_DesnPara.ProLevel,ProE_d);
	//	SetBarMat(360,2e5);
	int tempProtype = 10+GlobalPara::m_DesnPara.ProType;
	int tempProlevel = GlobalPara::m_DesnPara.ProLevel;
	SetShapeMat_Regu(tempProtype,tempProlevel,ProE_d);
	if(GlobalPara::m_DesnPara.CodeType==1)
		SetBarMat(GlobalPara::m_Sect_in.Bar_mat/1.15,BarE);
	else if(GlobalPara::m_DesnPara.CodeType==2)
		SetBarMat(GlobalPara::m_Sect_in.Bar_mat,BarE);
	else if(GlobalPara::m_DesnPara.CodeType==3)
		SetBarMat(GlobalPara::m_Sect_in.Bar_mat*0.9,BarE);
	th=3.14/8;
	l[0] = 1;
	l[1] = 0;
	SetMomAxis(l);
	cal_type=2;
	Calculation(cal_type);
//	lwh::vector<double>result;
	//result.reserve(10);
	GetResult(result);

	//存入数据中
	npoints = result.size()*0.5;
	GlobalPara::m_DesnPara.Fiberpoints_y = npoints;
	for(int i=0;i<npoints;i++)
	{
		GlobalPara::M_Cu[1][i] = abs(result[i*2+1]);
		GlobalPara::N_Cu[1][i] = -result[i*2];
	}
	//换一个方向,z向
	l[0] = 0;
	l[1] = 1;
	SetMomAxis(l);
	Calculation(cal_type);
	GetResult(result);
	npoints = result.size()*0.5;
	GlobalPara::m_DesnPara.Fiberpoints_z = npoints;
	for(int i=0;i<npoints;i++)
	{
		GlobalPara::M_Cu[3][i] = abs(result[i*2+1]);
		GlobalPara::N_Cu[3][i] = -result[i*2];
	}

	CLOSE_RUNINFO_DLG();

}

//任意截面时候才调用，不用在预定义参数里面取截面信息
void DrawNMCurve::GSect_FiberCal()
{
// 	int cenghao,xianxing,xiankuan,yanse,fanhui;
// 	int N,n2,IX,IY;
// 	float Xzf,Yzf,XM,YM,ANGLE;
// 	CString str;
// 	char* ZFSTR;
	double e1;
	double f1;
	int BarE;
	GetBarE(GlobalPara::m_DesnPara.CodeType,BarE);
	int protype=1;
	double ProE = 206000;
	SetShapepara_ForArbi(protype,ProE); 
	vector<vector<vector<double>>> ss;
	vector<vector<double>> container;
	vector<double>container1 (2);
	for(int j=0;j<2;j++){
		container.clear();
		for(int i=1;i<26;i++){
			e1 = -1.f*GlobalPara::m_DesnPara.prop_e[j][26-i];
			f1 = -1.f*GlobalPara::m_DesnPara.prop_f[j][26-i];
			container1[0]=e1;
			container1[1]=f1;
			container.push_back(container1);
		}
		for(int i=1;i<26;i++){
			e1 = GlobalPara::m_DesnPara.prop_e[j][i];
			f1 = GlobalPara::m_DesnPara.prop_f[j][i];
			container1[0]=e1;
			container1[1]=f1;
			container.push_back(container1);
		}
		ss.push_back(container);
	}
	SetshapSS_custom_ForArbi(ss);
	SetBarMat(GlobalPara::Bar_Fy,BarE);

	MakeSec();
	Mesh(GlobalPara::m_DesnPara.conc_mesh,GlobalPara::m_DesnPara.profile_mesh);



	if(GlobalPara::m_DesnPara.con_model==0){
		float Ecm,fcm,ec1,ecu1;
		int fck = GlobalPara::m_Sect_in.Concrete_mat;
		Tools::GetEuroCodeConcPara(fck,Ecm,fcm,ec1,ecu1);
		SetConc_UR(Ecm,fcm,ec1,ecu1);
	}
	else if(GlobalPara::m_DesnPara.con_model==1){
		float f0,e0,ecu;
		int fck = GlobalPara::m_Sect_in.Concrete_mat;
		Tools::GetUSCodeConcPara(fck,f0,e0,ecu);
		SetConc_US(f0,e0,ecu);
	}
	else if(GlobalPara::m_DesnPara.con_model==2){
		float E,fcr,ecr,ecu,acr;
		int fck = GlobalPara::m_Sect_in.Concrete_mat;
		Tools::GetCHCodeConcPara(fck,E,fcr,ecr,ecu,acr);
		fcr = fck;	//标准值的时候
		SetConc_CN(E,fcr,ecr,ecu,acr);
	}
	else if(GlobalPara::m_DesnPara.con_model==3){
		vector<vector<double>> ss;
		ss.reserve(50);
		vector<double>container1 (2);
		for(int i=1;i<26;i++){
			e1 = -1.f*GlobalPara::m_DesnPara.con_e[i];
			f1 = -1.f*GlobalPara::m_DesnPara.con_f[i];
			container1[0]=e1;
			container1[1]=f1;
			ss.push_back(container1);
		}
		SetConc_Custom(ss);
	}

//	float Profy;
//	int ProE,BarE;
//	GetProPara(GlobalPara::m_DesnPara.ProType,GlobalPara::m_Sect_in.HSect.RI,GlobalPara::m_DesnPara.ProLevel,GlobalPara::m_DesnPara.CodeType,Profy,ProE);

	double l[2]={1,0};
	SetMomAxis(l);
	int cal_type=2;
	Calculation(cal_type);
	lwh::vector<double>result;
	GetResult(result);
	ofstream outfile("D:\\NM.txt");
	for(size_t i=0;i<result.size()/2;i++)
	{
		outfile<<abs(result[2*i+1])<<"\n";
	}
	for(size_t i=0;i<result.size()/2;i++)
	{
		outfile<<-result[2*i]<<"\n";
	}
	outfile.flush();
	//存入数据中
	int npoints = result.size()*0.5;
	GlobalPara::m_DesnPara.Fiberpoints_y_k = npoints;
	for(int i=0;i<npoints;i++)
	{
		GlobalPara::M_Cu[0][i] = abs(result[i*2+1]);
		GlobalPara::N_Cu[0][i] = -result[i*2];
	}

	//换一个方向,z向
	l[0] = 0;
	l[1] = 1;
	SetMomAxis(l);
	Calculation(cal_type);
	GetResult(result);
	npoints = result.size()*0.5;
	GlobalPara::m_DesnPara.Fiberpoints_z_k = npoints;
	for(int i=0;i<npoints;i++)
	{
		GlobalPara::M_Cu[2][i] = abs(result[i*2+1]);
		GlobalPara::N_Cu[2][i] = -result[i*2];
	}


	//按照设计值再进行计算
	if(GlobalPara::m_DesnPara.con_model==0){
		// 		float Ecm,fcm,ec1,ecu1;
		// 		int fck = GlobalPara::m_Sect_in.Concrete_mat;
		// 		Tools::GetEuroCodeConcPara(fck,Ecm,fcm,ec1,ecu1);
		// 		fcm = fcm/1.5;
		// 		SetConc_UR(Ecm,fcm,ec1,ecu1);
		//欧洲规范设计值直接按照自定义本构的方式来计算
		Tools::GetEuroStress(GlobalPara::m_Sect_in.Concrete_mat);
		vector<vector<double>> ss;
		ss.reserve(50);
		vector<double>container1 (2);
		for(int i=1;i<26;i++){
			e1 = -1.f*GlobalPara::m_DesnPara.con_e[i];
			f1 = -1.f*GlobalPara::m_DesnPara.con_f[i];
			f1 = f1/1.5;
			container1[0]=e1;
			container1[1]=f1;
			ss.push_back(container1);
		}
		SetConc_Custom(ss);

	}
	else if(GlobalPara::m_DesnPara.con_model==1){
		float f0,e0,ecu;
		int fck = GlobalPara::m_Sect_in.Concrete_mat;
		Tools::GetUSCodeConcPara(fck,f0,e0,ecu);
		SetConc_US(f0,e0,ecu);
	}
	else if(GlobalPara::m_DesnPara.con_model==2){
		float E,fcr,ecr,ecu,acr;
		int fck = GlobalPara::m_Sect_in.Concrete_mat;
		Tools::GetCHCodeConcPara(fck,E,fcr,ecr,ecu,acr);
		fcr = fck/1.4;	//标准值的时候
		SetConc_CN(E,fcr,ecr,ecu,acr);
	}
	else if(GlobalPara::m_DesnPara.con_model==3){
		vector<vector<double>> ss;
		ss.reserve(50);
		vector<double>container1 (2);
		for(int i=1;i<26;i++){
			e1 = -1.f*GlobalPara::m_DesnPara.con_e[i];
			f1 = -1.f*GlobalPara::m_DesnPara.con_f[i];
			f1 = f1/1.5;
			container1[0]=e1;
			container1[1]=f1;
			ss.push_back(container1);
		}
		SetConc_Custom(ss);
	}
	protype = 2;
	SetShapepara_ForArbi(protype,ProE);
	GetBarE(GlobalPara::m_DesnPara.CodeType,BarE);
	if(GlobalPara::m_DesnPara.CodeType==1)
		SetBarMat(GlobalPara::Bar_Fy/1.15,BarE);
	else if(GlobalPara::m_DesnPara.CodeType==2)
		SetBarMat(GlobalPara::Bar_Fy,BarE);
	else if(GlobalPara::m_DesnPara.CodeType==3)
		SetBarMat(GlobalPara::Bar_Fy*0.9,BarE);
	l[0] = 1;
	l[1] = 0;
	SetMomAxis(l);
	cal_type=2;
	Calculation(cal_type);
	GetResult(result);

	//存入数据中
	npoints = result.size()*0.5;
	GlobalPara::m_DesnPara.Fiberpoints_y = npoints;
	for(int i=0;i<npoints;i++)
	{
		GlobalPara::M_Cu[1][i] = abs(result[i*2+1]);
		GlobalPara::N_Cu[1][i] = -result[i*2];
	}
	//换一个方向,z向
	l[0] = 0;
	l[1] = 1;
	SetMomAxis(l);
	Calculation(cal_type);
	GetResult(result);
	npoints = result.size()*0.5;
	GlobalPara::m_DesnPara.Fiberpoints_z = npoints;
	for(int i=0;i<npoints;i++)
	{
		GlobalPara::M_Cu[3][i] = abs(result[i*2+1]);
		GlobalPara::N_Cu[3][i] = -result[i*2];
	}

	//绘制曲线
	ReduceNM();
}

void DrawNMCurve::ReduceNM()
{
	double N_draw[3][FirbePoints],M_draw[3][FirbePoints];
	//先画y轴
	memcpy(N_draw[0],GlobalPara::N_Cu[0],FirbePoints*sizeof(double));
	memcpy(M_draw[0],GlobalPara::M_Cu[0],FirbePoints*sizeof(double));
	memcpy(M_draw[1],GlobalPara::M_Cu[0],FirbePoints*sizeof(double));
	memcpy(M_draw[2],GlobalPara::M_Cu[1],FirbePoints*sizeof(double));
	int yz=1;
	double Ntemp[FirbePoints];
	memcpy(Ntemp,GlobalPara::N_Cu[0],FirbePoints*sizeof(double));
	LengthEffect(Ntemp,GlobalPara::m_DesnPara.Fiberpoints_y_k,yz);
	memcpy(N_draw[1],Ntemp,FirbePoints*sizeof(double));
	memcpy(Ntemp,GlobalPara::N_Cu[1],FirbePoints*sizeof(double));
	LengthEffect(Ntemp,GlobalPara::m_DesnPara.Fiberpoints_y,yz);
	memcpy(N_draw[2],Ntemp,FirbePoints*sizeof(double));
	DrawFiberCurve(N_draw,M_draw,yz);
	DrawNMPoints(GlobalPara::fiber_draw_ratio_y,GlobalPara::Iin,yz);
	//将第二条曲线写回去
	memcpy(GlobalPara::N_Cu[1],N_draw[2],FirbePoints*sizeof(double));
	memcpy(GlobalPara::M_Cu[1],M_draw[2],FirbePoints*sizeof(double));
	//再画z轴
	memcpy(N_draw[0],GlobalPara::N_Cu[2],FirbePoints*sizeof(double));
	memcpy(M_draw[0],GlobalPara::M_Cu[2],FirbePoints*sizeof(double));
	memcpy(M_draw[1],GlobalPara::M_Cu[2],FirbePoints*sizeof(double));
	memcpy(M_draw[2],GlobalPara::M_Cu[3],FirbePoints*sizeof(double));
	yz=2;
	memcpy(Ntemp,GlobalPara::N_Cu[2],FirbePoints*sizeof(double));
	LengthEffect(Ntemp,GlobalPara::m_DesnPara.Fiberpoints_y_k,yz);
	memcpy(N_draw[1],Ntemp,FirbePoints*sizeof(double));
	memcpy(Ntemp,GlobalPara::N_Cu[3],FirbePoints*sizeof(double));
	LengthEffect(Ntemp,GlobalPara::m_DesnPara.Fiberpoints_y,yz);
	memcpy(N_draw[2],Ntemp,FirbePoints*sizeof(double));
	DrawFiberCurve(N_draw,M_draw,yz);
	DrawNMPoints(GlobalPara::fiber_draw_ratio_z,GlobalPara::Iin,yz);
	//将第二条曲线写回去
	memcpy(GlobalPara::N_Cu[3],N_draw[2],FirbePoints*sizeof(double));
	memcpy(GlobalPara::M_Cu[3],M_draw[2],FirbePoints*sizeof(double));

}


void DrawNMCurve::LengthEffect(double* Ncurve,int npoints,int yz)
{
	double Ec,Es,Esr;
	float Ecp;
	if(GlobalPara::m_DesnPara.CodeType==1)
		Tools::GetEUPara(Ec,Es,Esr);
	else if(GlobalPara::m_DesnPara.CodeType==2)
		Tools::GetAISCPara(Ec,Es,Esr);
	else if(GlobalPara::m_DesnPara.CodeType==3)
		Tools::GetCNPara(Ec,Es,Esr);
	SetEcEsEsr(Ec,Es,Esr);
	double EcIx,EcIy,EsIx,EsIy,EsrIx,EsrIy,Ac,As,Asr;
	GetAEI(EcIx,EcIy,EsIx,EsIy,EsrIx,EsrIy,Ac,As,Asr);
	GlobalPara::Iin[0] = EsIx;
	GlobalPara::Iin[1] = EsrIx;
	GlobalPara::Iin[2] = EcIx;
	GlobalPara::Iin[3] = EsIy;
	GlobalPara::Iin[4] = EsrIy;
	GlobalPara::Iin[5] = EcIy;
	if(GlobalPara::m_DesnPara.CodeType==1){
		if(GlobalPara::currentsect==0)
			Ecp = Tools::GetEUCreepEc(Ac,Ec);
		else
			Ecp = Ec*0.5;		//陈涛拍脑袋决定的
		double L0 = GlobalPara::m_DesnPara.uL*GlobalPara::m_DesnPara.Lens*1000;
		double EIeff_x = EsIx+EsrIx+0.6*Ecp*EcIx/Ec;
		double Ncr_x = PII*PII*EIeff_x/(L0*L0);
		double Nplrk = Ncurve[0];
		float LL = sqrt(Nplrk/Ncr_x);
		//强轴的曲线b
		float ff = 0.5*(1+0.34*(LL-0.2)+LL*LL);
		float ks_y = 1/(ff+sqrt(ff*ff-LL*LL));
		if(ks_y>1)
			ks_y = 1;
		//弱轴的曲线c
		double EIeff_y = EsIy+EsrIy+0.6*Ecp*EcIy/Ec;
		double Ncr_y = PII*PII*EIeff_y/(L0*L0);
		LL = sqrt(Nplrk/Ncr_y);
		ff = 0.5*(1+0.49*(LL-0.2)+LL*LL);
		float ks_z = 1/(ff+sqrt(ff*ff-LL*LL));
		if(ks_z>1)
			ks_z = 1;
		float ks;
		if(yz==1)
			ks = ks_y;
		else
			ks = ks_z;
		for(int i=0;i<FirbePoints;i++){
			Ncurve[i] = Ncurve[i]*ks;
		}
	}
	else if(GlobalPara::m_DesnPara.CodeType==2){
		//稍后实现
	}
	else if(GlobalPara::m_DesnPara.CodeType==3){
		//稍后实现
	}
}
void DrawNMCurve::InitUCS(float scale_x,float sclae_y)
{
	float pmucs[9];

	pmucs[0]=0.0;
	pmucs[1]=0.0;
	//pmucs[2]=nUcs++;
	pmucs[2]=0.0; //cyl 2017-08-08

	pmucs[3]=1.0/scale_x;
	pmucs[4]=1.0/sclae_y;
	pmucs[5]=1.0;

	pmucs[6]=0;
	pmucs[7]=0;
	pmucs[8]=0;
	m_pCfgBas->Usercs(pmucs);
}
	//	m_pCfgBas->Outucs();
void DrawNMCurve::DrawFiberCurve(double N[][FirbePoints],double M[][FirbePoints],const int yz)
{
	int cenghao,xianxing,xiankuan,yanse,fanhui;
	int NN,n2,IX,IY;
	float Xzf,Yzf,ANGLE;
	CString str;
	char* ZFSTR;
	int iWay = 99;
	int npoints;
	CString StrFile;
	if(yz==1){
		StrFile.Format(_T("Fiber_NM_y.t"));
		npoints = GlobalPara::m_DesnPara.Fiberpoints_y_k;
	}
	else{
		StrFile.Format(_T("Fiber_NM_z.t"));
		npoints = GlobalPara::m_DesnPara.Fiberpoints_z_k;
	}
	int n1=StrFile.GetLength();
	char FileName[256];
	strcpy(FileName,StrFile);
	FileName[n1]=char(0);
	m_pCfgBas->Closfl(iWay);
	m_pCfgBas->Setcfg();
	m_pCfgBas->Openfl(iWay,FileName,n1,n1);
	m_pCfgBas->Nowfil(iWay);
	m_pCfgBas->Tobegin0(iWay);
	int isave=1;
	m_pCfgBas->Ifsave(isave);	
	int ibc=15;
	m_pCfgBas->Bcolor(ibc);
	m_pCfgBas->Nowbcl(ibc);
	float max_x=0;
	float max_y=0;
	float max_tmp;
	for(int j=0;j<3;j++)
	{
		if(j==2)
		{
			if(yz==1)  npoints = GlobalPara::m_DesnPara.Fiberpoints_y;
			else	npoints = GlobalPara::m_DesnPara.Fiberpoints_z;
		}
		for(int i=0;i<npoints;i++)
		{
			if(M[j][i]>max_x) max_x=M[j][i]*1.e-6;
			if(N[j][i]>max_y) max_y=N[j][i]*1.e-3;
		}
	}	
	int iunit=1;
	float bl=1;
	float xoo=0;
	float yoo=0;
	float zoo=0;
	float  size_x=4000;
	float  size_y=3000;
	float size_z=size_x;
	float scale_x=max_x/size_x;
	float scale_y=max_y/size_y;


	m_pCfgBas->Grfild(size_x,size_y,size_z,iunit,bl,xoo,yoo,zoo);
	InitUCS(scale_x,scale_y);
	float XM1=45*scale_x;
	float YM1=60*scale_y;
	float XM2=55*scale_x;
	float YM2=70*scale_y;


	//在这里画线
	cenghao=1;
	xianxing=1;
	xiankuan=3;
	yanse=10;
	fanhui=0;
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	//	int npoints = result.size()*0.5;
	//	 = FirbePoints;


	double ratio1;
	ratio1 = M[0][npoints-1]/N[0][0]; 
	if(yz==1)
		GlobalPara::fiber_draw_ratio_y = ratio1;
	else
		GlobalPara::fiber_draw_ratio_z = ratio1;
	for(int j=0;j<3;j++){
		if(j==2){
			if(yz==1)
				npoints = GlobalPara::m_DesnPara.Fiberpoints_y;
			else
				npoints = GlobalPara::m_DesnPara.Fiberpoints_z;
		}
		for(int i=0;i<npoints-1;i++)
		{
			float x1 = M[j][i]*1.e-6;			//原来是5000000000
			float x2 = M[j][i+1]*1.e-6;
			float y1 = N[j][i]*1.e-3;
			float y2 = N[j][i+1]*1.e-3;
			m_pCfgBas->Line(x1,y1,x2,y2);
		}
	}
	//画内力点
/*	xiankuan = 10;
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	float x,y;
	if(yz==1){
		x = GlobalResult::draw_point.My/5000000000;
		x = GPara::My_max/5000000000;
	}
	else{
		x = GlobalResult::draw_point.Mz/5000000000;
		x = GPara::Mz_max/5000000000;
	}
	y = GlobalResult::draw_point.N/10000000;
	y = GPara::N_max/10000000;
	float z;
	z = 0;
	m_pCfgBas->Pnt3d(x,y,z);*/

	//画x,y轴
	cenghao=1;
	xianxing=1;
	xiankuan=2;
	yanse=7;
	fanhui=0;
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	max_x = max_x*1.2;
	max_y = max_y*1.2;
	double x_step = max_x/10;
	double y_step = max_y/10;
	float x_base,y_base;
	x_base=y_base=0.f;
	//x轴
	float x_temp = 0.f;
	m_pCfgBas->Line(x_base,y_base,max_x,y_base);
	float x_jt=max_x-max_x/20;
	float y_jt=x_temp+max_x/50;
	//	m_pCfgBas->Line(max_x,x_temp,x_jt,y_jt);
	x_jt=max_x-max_x/20;
	y_jt=x_temp-max_x/50;
	//	m_pCfgBas->Line(max_x,x_temp,x_jt,y_jt);
	//横向轴网
	
	

	for(int i=0;i<10;i++){
		x_temp = (i+1)*y_step;
		m_pCfgBas->Line(x_base,x_temp,max_x,x_temp);
		//绘制网格坐标
		str.Format(_T("%g"),(i+1)*y_step);
		n2=str.GetLength();
		ZFSTR=str.GetBuffer(str.GetLength());
		NN=n2;
		Xzf=0.; 
		Yzf=(i+1)*y_step;
		IX=1;
		IY=2;
		ANGLE=0;
		m_pCfgBas->Drawzf(NN,ZFSTR,n2,Xzf,Yzf,XM1,YM1,IX,IY,ANGLE);
	}
	//标注
	str.Format("M(kN·m)");
	n2=str.GetLength();
	ZFSTR=str.GetBuffer(str.GetLength());
	NN=n2;
	Xzf=max_x; 
	Yzf=y_base;

	IX=3;
	IY=2;
	ANGLE=0;
	m_pCfgBas->Drawzf(NN,ZFSTR,n2,Xzf,Yzf,XM2,YM2,IX,IY,ANGLE);

	//y轴
	m_pCfgBas->Line(x_base,y_base,x_base,max_y);
	x_jt=x_temp+max_x/50;
	y_jt=max_y-max_x/20;
	//	m_pCfgBas->Line(x_temp,max_y,x_jt,y_jt);
	x_jt=x_temp-max_x/50;
	y_jt=max_y-max_x/20;
	//	m_pCfgBas->Line(x_temp,max_y,x_jt,y_jt);
	for(int i=0;i<10;i++){
		x_temp = (i+1)*x_step;
		m_pCfgBas->Line(x_temp,y_base,x_temp,max_y);
		//x坐标
		str.Format(_T("%g"),(i+1)*x_step);
		n2=str.GetLength();
		ZFSTR=str.GetBuffer(str.GetLength());
		NN=n2;
		Xzf=(i+1)*x_step; 
		Yzf=y_base - 1;
		IX=2;
		IY=3;
		ANGLE=0;
		m_pCfgBas->Drawzf(NN,ZFSTR,n2,Xzf,Yzf,XM1,YM1,IX,IY,ANGLE);
	}
	//标注
	str.Format("N(kN)");
	n2=str.GetLength();
	ZFSTR=str.GetBuffer(str.GetLength());
	NN=n2;
	Xzf=x_base; 
	Yzf=max_y+YM2;
	IX=2;
	IY=1;
	ANGLE=0;
	m_pCfgBas->Drawzf(NN,ZFSTR,n2,Xzf,Yzf,XM2,YM2,IX,IY,ANGLE);

	//文字
	str.Format("Axial force-bending moment interaction curve");
	n2=str.GetLength();
	ZFSTR=str.GetBuffer(str.GetLength());
	NN=n2;
	Xzf=max_x/2; 
	Yzf=y_base-y_step/3;
	IX=2;
	IY=1;
	ANGLE=0;
	m_pCfgBas->Drawzf(NN,ZFSTR,n2,Xzf,Yzf,XM1,YM1,IX,IY,ANGLE);
	m_pCfgBas->Outucs();
	int ivpd=0;
	m_pCfgBas->Xoyvpd(ivpd);
	m_pCfgBas->Redrwa();
	m_pCfgBas->Regens();
	m_pCfgBas->Zoome();

	CString pcxFileName=StrFile;
	pcxFileName=pcxFileName.Left(pcxFileName.Find(_T(".t")));
	n1=pcxFileName.GetLength();	
	strcpy(FileName,pcxFileName);
	int NRC[4];
	for(int i=0;i<4;i++) NRC[i]=1;
	int kw=0;
	m_pCfgBas->Mfpcx(FileName,sizeof(FileName),n1,NRC,kw);

//	m_pCfgBas->Closfl(iWay);

}
