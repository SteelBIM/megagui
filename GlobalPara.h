#if !defined(GLOBALPARA_H_)
#define  GLOBALPARA_H_

#define bard_no 10
#define barmp_no 2
#define confck_no 9
#define profy_no 8
#define PII 3.1415926
#define FirbePoints 300
#define PII 3.1415926
#pragma once
#include "DesignParameter.h"
#include "PredefSectDescrib.h"
#include "Loaddef.h"

struct membercheck_rst{
	float PermitVal_lower[20];
	float PermitVal_upper[20];
	float CalVal[20];
	float CalVal2[20];
	int   ifOk[20];
	int   ifOk2[20];
};

class GlobalPara
{
public:
	GlobalPara(void);
	~GlobalPara(void);

	static bool ExpertMode;		//专家模式开关
	static bool InExpertMode();		//判断是否处于专家模式

public:
	static DesnPara m_DesnPara;
	static SectDescribe m_Sect_in;
	static membercheck_rst m_Rst;
	static void initPara(int CodeType);
	static void initbengou();
	static bool SavePara();
	static bool LoadPara();

public:
	static int bard[bard_no];
	static int barmp[barmp_no];
	static int confck[confck_no];
	static int profy[profy_no];

public:
	//
	static int bard_euro[bard_no];
	static int barmp_euro[barmp_no];
	static int confck_euro[confck_no];
	static int profy_euro[profy_no];

	static int bard_aisc[bard_no];
	static int barmp_aisc[barmp_no];
	static int confck_aisc[confck_no];
	static int profy_aisc[profy_no];

	static int bard_chi[bard_no];
	static int barmp_chi[barmp_no];
	static int confck_chi[confck_no];
	static int profy_chi[profy_no];

public:
	static int currentload;
	static int currentside;
	static int currentsect;
	static float Pro_Fy;
	static float Bar_Fy;

public:
	static float ks_y,ks_z;
	static float fiber_draw_ratio_y;
	static float fiber_draw_ratio_z;
	static double Iin[6];

public:		//将荷载定义放在这里
// 	static CArray<mega_loads,mega_loads> m_loads1_z;		//dead load
// 	static CArray<mega_loads,mega_loads> m_loads1_y;		//dead load
// 	static CArray<mega_loads,mega_loads> m_loads2_z;		//live1-3
// 	static CArray<mega_loads,mega_loads> m_loads2_y;		//live1-3
// 	static CArray<mega_loads,mega_loads> m_loads3_z;
// 	static CArray<mega_loads,mega_loads> m_loads3_y;
// 	static CArray<mega_loads,mega_loads> m_loads4_z;
// 	static CArray<mega_loads,mega_loads> m_loads4_y;
// 
// 	static int nLoadCase;

	static CArray<mega_loads> LoadCaseData;
	//小李的NM曲线数据
	static double M_Cu[4][FirbePoints];
	static double N_Cu[4][FirbePoints];

//绘图
	static void DrawCol(const int currentload,const int side); 
	static void DrawColImp(const int currentload,const int side,
		CArray<mega_loads>* pTmpload,bool bShowInTFile,float xadd=0,float yadd=0,float scl=1,
		int nHighType=-1,int nHighidx=-1); 
	static void DrawCol_col(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,float x0,float y0,float x1,float y1);
	static void DrawCol_col3D(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,float x0,float y0,float x1,float y1);

	static void DrawCol_yueshu(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,int ihing,float r,float x0,float y0,float x1,float y1);
	static void DrawCol_zhizuo(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,int ihing,float x0,float y0,float x1,float y1);
	static void DrawCol_hezai(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,float x0,float y0,float x1,float y1,
		float bili,int nload,int iloadtype[100],float P1loadcol[100],float y1loadcol[100],float P2loadcol[100],float y2loadcol[100],float htop,float Ntop,float Mtop,float Mdown,
		int nHightType=-1,int nHighIdx=-1);
	static int GetMegaColPoly(float xp[], float yp[]);
	static int GetProfilePoly(float x0,float y0,float ang,float xp[],float yp[]);


};

#endif
