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
	static void CalEndM(double Mtop,double Mend,int loadcase,const int side);		//�Ӷ˲���ؼ���13����������
	static void CalEndN(double N,int loadcase);
	static double CalSelfG();
	static void SetConMatCurSel(CComboBox &conlist,int mat,BOOL ExpertMode);
	static void AddConMatByCode(CComboBox &conlist);
	static void AddProMatByType(CComboBox &code,CComboBox &mat);
	static void ConMatStringCatch(CString ConName);
	static void ProMat(int CodeNo,int ProNo);
	static float CalSectProRatio();
	static float GetECecu();		//ŷ�޹淶�������ecu
	static void GetDesnInfo(int &j,CString Strings[]);	//������е������Ϣ��д������Ļ��
	static void GetEuroCodeConcPara(int fck,float &Ecm,float &fcm,float &ec1,float &ecu1);		//���ŷ�޹淶����Ӧ����
	static void GetUSCodeConcPara(int fck,float &f0,float &e0,float &ecu);
	static void GetCHCodeConcPara(int fck,float &E,float &fcr,float &ecr,float &ecu,float &acr);
	static void GetEuroStress(int Fck);		//�ӻ������ȼ������Ӧ��Ӧ��Ӧ���ϵ
	static float GetCNConF(int Grade);

	static void GetEUPara(double& Ecm,double& Es,double& Esr);
	static void GetAISCPara(double& Ecm,double& Es,double& Esr);
	static void GetCNPara(double& Ecm,double& Es,double& Esr);
	static float GetBenGouMaxFcm();	//�ӱ����������ҵ�����fcm
	static float GetEUCreepEc(double Ac,double Ecm);
		
	static void CalProPoint(float E1,float E2,float m_fy,float m_fu);		//��ɢ���͸ֱ���
	static void AutoComb();		//���û���߶Ի����Զ����

	//������
	static int  GetCmindur_EURO(int &stru_class,int &exposure_class);	//ŷ�޹淶�л���;���Ҫ����С��������
	static void CompareVal(membercheck_rst &m_check,const int item_index,const bool checkval2=false);
	static bool MemberCheck_EU(membercheck_rst &Rst);
	static void GetSectA(double &As,double &Asr,double &Ac,double &Ag);
};

#endif