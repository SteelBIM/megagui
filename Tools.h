#if !defined(TOOLS_H_)
#define  TOOLS_H_
#pragma once
#include "GlobalPara.h"
#include "Loaddef.h"
class Tools
{
public:
	Tools(void);
	~Tools(void);

public:
	static void initmatbycode(const int codetype);
	static void DrawCurrentLoad(CArray<mega_loads,mega_loads> CurLoads);
	static void CalEndM(double Mtop,double Mend,int loadcase,const int side);		//从端部弯矩计算13个断面的弯矩
	static void CalEndN(double N,int loadcase);
	static double CalSelfG();
	static void SetConMatCurSel(CComboBox &conlist,int mat,BOOL ExpertMode);
	static void AddConMatByCode(CComboBox &conlist);
	static void AddProMatByType(CComboBox &code,CComboBox &mat);
	static void ConMatStringCatch(CString ConName);
	static void ProMat(int CodeNo,int ProNo);
	static float CalSectProRatio();
	static float GetECecu();		//欧洲规范获得最大的ecu
	static void GetDesnInfo(int &j,CString Strings[]);	//获得所有的设计信息，写出在屏幕上
	static void GetEuroCodeConcPara(int fck,float &Ecm,float &fcm,float &ec1,float &ecu1);		//获得欧洲规范的相应数据
	static void GetUSCodeConcPara(int fck,float &f0,float &e0,float &ecu);
	static void GetCHCodeConcPara(int fck,float &E,float &fcr,float &ecr,float &ecu,float &acr);
	static void GetEuroStress(int Fck);		//从混凝土等级计算对应的应力应变关系
	static float GetCNConF(int Grade);

	static void GetEUPara(double& Ecm,double& Es,double& Esr);
	static void GetAISCPara(double& Ecm,double& Es,double& Esr);
	static void GetCNPara(double& Ecm,double& Es,double& Esr);
	static float GetBenGouMaxFcm();	//从本构曲线中找到最大的fcm
	static float GetEUCreepEc(double Ac,double Ecm);
		
	static void CalProPoint(float E1,float E2,float m_fy,float m_fu);		//离散化型钢本构
	static void AutoComb();		//如果没有走对话框，自动组合

	//截面检查
	static int  GetCmindur_EURO(int &stru_class,int &exposure_class);	//欧洲规范中获得耐久性要求最小保护层厚度
	static void CompareVal(membercheck_rst &m_check,const int item_index,const bool checkval2=false);
	static bool MemberCheck_EU(membercheck_rst &Rst);
	static void GetSectA(double &As,double &Asr,double &Ac,double &Ag);
};

#endif