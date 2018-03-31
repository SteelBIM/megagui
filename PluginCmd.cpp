// PluginCmd.cpp: implementation of the PluginCmd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PluginCmd.h"
#include "MegaMainData.h"
#include "MegaLoad1.h"
#include "MegaCros1.h"
#include "NodeLoad.h"
#include "WelcomeDlg.h"
#include "NodeLoad2.h"
#include "GlobalPara.h"
#include "MegaSection1.h"
#include "MegaSection2.h"
#include "MegaSection3.h"
#include "MegaSection4.h"
#include "MegaSection5.h"
#include "MegaSection6.h"
#include "MegaSection7.h"
#include "DesignPara.h"
#include "SectionSel.h"
#include "ConfigDlg.h"
#include "DrawNMCurve.h"
//#include "MegaCalIO.h"
#include "DesignParameter.h"
#include "PredefSectDescrib.h"
#include "DlgLoadInput.h"
#include "DlgSectionList.h"
#include "SectionReader.h"
#include "Tools.h"
#include "MsgMacroHeader.h"
#include "PluginFun.h"
#include "MegaCombDlg.h"
#include "ModelSel.h"
#include "DlgLang.h"
#include "CfgBas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString PluginCmd::filename;
char PluginCmd::PLUG_SIG[10]=_T("$XTSpas");
int PluginCmd::m_ICmdFrom=0;
bool PluginCmd::ifautocomb=false;
HINSTANCE PluginCmd::m_HInstanceExternalRes = NULL;
extern "C" int RunUserCmd(LPVOID cmdParam);
extern "C" __declspec( dllimport ) CCfgBas *m_pCfgBas;

//获得本动态库中的资源图片
extern "C" __declspec( dllexport )  void GetResBitmap(const int& IDRes,CBitmap &Bitmap)
{
	Bitmap.LoadBitmap(IDRes);
}
extern "C" void __stdcall RELOAD_MAIN_SUB(int &Itype, int &NInt, int IPara[], int &NFloat, float RPara[], int &NStr, int &LStr, char *StrPara[], int n1);

extern "C" __declspec( dllimport ) void MegaCheckIO_(SectDescribe *pSect,DesnPara *pDesnPara);

extern "C" __declspec( dllimport) void MegaDesn_(DesnPara *pDesnPara,double M[][FirbePoints],double N[][FirbePoints]);

extern "C" __declspec( dllimport) void ExitMega_();

extern "C" __declspec( dllexport ) void MegaReport();

extern "C" __declspec( dllimport ) void SetCalEI(double EIin[]);
extern "C" __declspec( dllimport ) void GetTipsStr(float& XCRS,float& YCRS,char* STR);
extern "C" __declspec( dllimport )  void SetIfExpertMode(int expert);
//extern "C" void CalcOutWord();
//////////////////////////////////////////////////////////////////////
//消息映射表
BEGIN_CMDMNGR_MSGMAP(PluginCmd,CMT_USER_BASE)
	//{{AFX_CMDMNGR_MSGMAP(PzcdStatCmd)
	ON_CMDMNGR_CMD(CMT_LOAD, OnLoad)
	ON_CMDMNGR_CMD(CMT_UNLOAD, OnUnload)
	ON_CMDMNGR_CMD(CMT_QUIT, OnBeforeQuit)
	ON_CMDMNGR_CMD(CMT_INIT, OnInit)
	ON_CMDMNGR_CMD(CMT_STXT_DLL_CMD,OnSetCmdFromDll)
	ON_CMDMNGR_CMD(CMT_STXT_OUT_CMD,OnSetCmdFromSys)
	ON_CMDMNGR_CMD(CMT_COMMAND_PARA,OnCommandPara)
	ON_CMDMNGR_CMD(CMT_TIPMESSAGE,OnTipMessage)

	ON_CMDMNGR_CMD(CMT_RIBBONCHGMENU,OnRibbonMenuExpanded)

	//}}AFX_CMDMNGR_MSGMAP
END_CMDMNGR_MSGMAP()

//注册dll输出命令
void PluginCmd::RegisterMyCmds()
{
	//支撑连接动态库中实现的命令
	RegisterCmd(PLUG_SIG,"XTSPAS",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGAMAINDATA",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGANEW",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGASAVE",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGASAVEAS",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGAOPEN",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGASECT1",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGASECT2",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGASECT3",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGASECT4",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGASECT5",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGASECT6",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGASECT7",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGASECTSEL",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGALOAD",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGALOAD1",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGALOAD2",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGALOAD3",RunUserCmd);
	RegisterCmd(PLUG_SIG,"CONFIG",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGAEXIT",RunUserCmd);
	RegisterCmd(PLUG_SIG,"BENGOU",RunUserCmd);
	RegisterCmd(PLUG_SIG,"PROBENGOU",RunUserCmd);
	RegisterCmd(PLUG_SIG,"DESIGNPARA",RunUserCmd);
	RegisterCmd(PLUG_SIG,"EXPERTMODE",RunUserCmd);
	RegisterCmd(PLUG_SIG,"EXPERTMODEOFF",RunUserCmd);
	RegisterCmd(PLUG_SIG,"FIBERCAL",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGASECTCAL",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGA_DRAW",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGAGETFORCE",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGA_LOADCASE_DLG",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGA_SECT_LIST_DLG",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGA_REPORT",RunUserCmd);
	RegisterCmd(PLUG_SIG,"FIBERCAL2",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGALOADCOMB",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGA_LANGUAGE",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGA_MESH",RunUserCmd);
	RegisterCmd(PLUG_SIG,"MEGASETSECT",RunUserCmd);
	return;
}
int PluginCmd::OnRibbonMenuExpanded(LPVOID cmdPara)
{
	void **p = (void**)cmdPara;
	TCHAR* text;
	text=(TCHAR*)p[0];   // 一级菜单名text
	int nLen=strlen(text);

	bool bExpand=(bool)p[1];  //一级菜单的状态  false = 正在关闭菜单text    true=正在打开菜单text
	CString strText = text;

	if(strText.CompareNoCase(_T("截面优选"))==0||strText.CompareNoCase(_T("计算结果查询"))==0)
	{
		if(bExpand)
		{
			CString strCallMenu=_T("OpenMenu");
			//正在打开 截面优选 或者  计算结果查询       (此时已经打开菜单完成了)
		}
		else
		{
			CString strCallMenu=_T("CloseMenu");
			//正在关闭  截面优选 或者  计算结果查询      (此时已经关闭菜单完成了)
		}
	}

	return 0;
}



//消息响应函数
int PluginCmd::OnLoad(LPVOID cmdPara)
{
	TRACE("Plugin <%s> loaded.\n",PLUG_SIG);

	RegisterMyCmds();

	RegisterLinkParas();

	CString strDll;
#ifdef _DEBUG
	strDll = "CommonTreeInfoD.dll";
#else
	strDll = "CommonTreeInfo.dll";
#endif // _DEBUG
	LoadFile(strDll);
	return 0;
}

int PluginCmd::OnUnload(LPVOID cmdPara)
{
	TRACE("Plugin <%s> unloaded.\n",PLUG_SIG);

	//exSave_ColumData();
	//::AfxDaoTerm();
	UnRegisterCmdGroup(PLUG_SIG);

	if (m_HInstanceExternalRes)
	{
		FreeLibrary(m_HInstanceExternalRes);
		//之后不再还原资源,反正已经要卸载了
	}
	return 0;
}

int PluginCmd::OnBeforeQuit(LPVOID cmdPara)
{
	TRACE("XTSpas.dll has recieved the QUIT message.\n");
	ExitMega_();

	return 0;
}

int PluginCmd::OnInit(LPVOID cmdPara)
{
	//默认在D盘下创建一个MegaColm的目录，都存在那里面
	TRACE("XTSpas.dll has recieved the INIT message.\n");
	
	LCID lcidNew = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT);
	SetThreadLocale(lcidNew);

	//初始化本动态库中For程序中的型钢库
	//TRAN_STEEL_LIB_FROM_DLL_FOR();
	ZeroMemory(&(GlobalPara::m_Sect_in),sizeof(SectDescribe));
	ZeroMemory(&(GlobalPara::m_DesnPara),sizeof(DesnPara));
	int code=1;
	int interfacelanguage;
	int m_unit;
	char Dir[256];
	GetCurrentDirectory( 256, Dir ); 
	CString FileName;
	FileName.Format(_T("%s\\ctrl.mgc"),Dir);
	CFileStatus rStatus;
	if (CFile::GetStatus(FileName,rStatus)){
		CFile ReadFile;
		ReadFile.Open(FileName,CFile::modeRead|CFile::typeBinary);
		ReadFile.Read(&code,sizeof(int));
		ReadFile.Read(&interfacelanguage,sizeof(int));
		ReadFile.Read(&m_unit,sizeof(int));
		ReadFile.Close();

		GlobalPara::m_DesnPara.InterfaceLan = interfacelanguage;
	}
	GlobalPara::initPara(code);
	int iflag = 1;
	SetIcon(iflag);

// 	HINSTANCE langDll = LoadLibrary("MegaGuiCHND.dll");
// 	AfxSetResourceHandle(langDll);

	// 	CString StrDll=_T("megasectcal.dll");
// #ifdef _DEBUG
// 	StrDll=_T("megasectcald.dll");
// #endif
// 	HINSTANCE	hinstance_DLL = LoadLibrary(StrDll);

	CString strl;
	Language(strl);

	CString strLangDll;
	strLangDll.Format("MegaGui%sD.dll",strl);
	
	CString path;
	::GetModuleFileName(NULL,path.GetBuffer(MAX_PATH),MAX_PATH);
	path.ReleaseBuffer();
	path = path.Left(path.ReverseFind('\\'));
	strLangDll = path + "\\" + strLangDll;


	m_HInstanceExternalRes = LoadLibrary(strLangDll);
	if (m_HInstanceExternalRes)
	{
		AfxSetResourceHandle(m_HInstanceExternalRes);
	}
	 

	//删除本构图
	{
		::DeleteFile("ConBenGou.jpg");
		::DeleteFile("ProBenGou.jpg");
	}

	

	return 0;
}

//注册本动态库中包含的连接类型（资源在本动态库中）
void PluginCmd::RegisterLinkParas()
{
//	LPTSTR StrDllFile=_T("XTSpas.dll");	//本动态库名称
	#ifdef _DEBUG
//		StrDllFile=_T("XTSpasD.dll");
	#endif
	//注册本动态库加载信息（当本动态库中有连接实现时需要注册）
//	CKj3DEx::RegExDllFile(StrDllFile);


	return;
}

//设置命令调用来源与动态库
int PluginCmd::OnSetCmdFromDll(LPVOID cmdParam)
{
	m_ICmdFrom=1;
	return 0;
}

//设置命令调用来源于系统外部
int PluginCmd::OnSetCmdFromSys(LPVOID cmdParam)
{
	m_ICmdFrom=0;
	return 0;
}


//运行命令
extern "C" int RunUserCmd(LPVOID cmdParam)
{

	LPCTSTR CTSTR = (LPCTSTR)cmdParam;

	CString CommandStr = CTSTR;

	CString CSTR;
	
	CSTR = CommandStr;
	CSTR.MakeUpper();
	CSTR.TrimLeft();
	CSTR.TrimRight();

	PluginCmd::CloseMiniPane();
	PluginCmd::DestoryAllDlg();

	if(CSTR=="XTSPAS"){
		AfxMessageBox(_T("测试XTSpas中命令调用！"));
	}
	else if(CSTR=="MEGANEW"){
		//新建数据，默认在D:\mega目录下
		PluginCmd::NewMegaPara();
	}
	else if(CSTR=="MEGASAVE"){
		//保存
		PluginCmd::SaveMegaPara();
	}
	else if(CSTR=="MEGASAVEAS"){
		PluginCmd::SaveasMegaPara();
	}
	else if(CSTR=="MEGAOPEN"){
		//打开.mega文件
		PluginCmd::OpenMegaPara();
	}
	else if(CSTR=="MEGAMAINDATA"){
		MegaMainData pDlg;
		pDlg.DoModal();
	}	
 	else if(CSTR=="MEGALOAD1"){
		MegaLoad1 pDlg;
		pDlg.DoModal();
	}
	else if(CSTR=="MEGASECT1"){
		CMegaSection1 pDlg;
		pDlg.DoModal();
	}
	else if(CSTR=="MEGASECT2"){
		CMegaSection2 pDlg;
		pDlg.DoModal();
	}
	else if(CSTR=="MEGASECT3"){
		CMegaSection3 pDlg;
		pDlg.DoModal();
	}
	else if(CSTR=="MEGASECT4"){
		CMegaSection4 pDlg;
		pDlg.DoModal();
	}
	else if(CSTR=="MEGASECT5"){
		CMegaSection5 pDlg;
		pDlg.DoModal();
	}
	else if(CSTR=="MEGASECT6"){
		CMegaSection6 pDlg;
		pDlg.DoModal();
	}
	else if(CSTR=="MEGASECT7"){
		CMegaSection7 pDlg;
		pDlg.DoModal();
	}
	else if(CSTR=="MEGASECTSEL"){
		CSectionSel pDlg;
		pDlg.DoModal();
		GlobalPara::m_DesnPara.max_con_ec = Tools::GetECecu();	//欧洲规范算一下最大ecu1
		int iflag = 2;
		PluginCmd::SetIcon(iflag);
	}
	else if(CSTR=="MEGASETSECT"){
		int iflag = 2;
		PluginCmd::SetIcon(iflag);
	}
	else if(CSTR=="BENGOU"){
		CModelSel pdlg;
		pdlg.DoModal();
	}
	else if(CSTR=="PROBENGOU"){

	}
	else if(CSTR=="DESIGNPARA"){
		CDesignPara pdlg;
		pdlg.DoModal();
		int iflag =3;
		PluginCmd::SetIcon(iflag);
	}
	else if(CSTR=="CONFIG"){
		CConfigDlg pdlg;
		pdlg.DoModal();
	}
	else if(CSTR=="MEGALOAD3"){
		NodeLoad2 pDlg;
		pDlg.DoModal();
	}
	else if(CSTR=="EXPERTMODE"){
		GlobalPara::ExpertMode = true;
		PluginCmd::RunCmd(_T("EXPERTMODE1"));
		PluginCmd::ChangeToSubModule(1,1);
	}
	else if(CSTR=="EXPERTMODEOFF"){
		GlobalPara::ExpertMode = false;
	}
	else if(CSTR=="MEGAEXIT"){
		int Itype=0,NInt=2,IPara[2],NFloat=2,NStr=2,LStr=10,n1=0;
		float RPara[2];
		char *StrPara[2];
		int ireturn = AfxMessageBox("Do you want to exit?",4+32+256);
		if(ireturn==IDYES)
			RELOAD_MAIN_SUB(Itype,NInt,IPara,NFloat,RPara,NStr,LStr,StrPara,n1);
	}
	else if(CSTR=="FIBERCAL"){
		//DrawNMCurve::CalColmNMCurve_Fiber();
	}
	else if(CSTR=="MEGASECTCAL"){
		SetIfExpertMode(GlobalPara::ExpertMode);
		PluginCmd::SepSectforFiber();
		if(!PluginCmd::ifautocomb)
			Tools::AutoComb();
		PluginCmd::OnCalForce(Mega_Cases::Get().Cases());
		if(GlobalPara::currentsect==0){
			GlobalPara::m_DesnPara.ifCustomSection = false;
			MegaCheckIO_(&(GlobalPara::m_Sect_in),&(GlobalPara::m_DesnPara));
			if(GlobalPara::m_DesnPara.ifFiber)
				DrawNMCurve::CalColmNMCurve_Fiber();
			MegaDesn_(&(GlobalPara::m_DesnPara),GlobalPara::M_Cu,GlobalPara::N_Cu);
		}
		else{
			GlobalPara::m_DesnPara.ifCustomSection = true;
			MegaCheckIO_(&(GlobalPara::m_Sect_in),&(GlobalPara::m_DesnPara));
			DrawNMCurve::GSect_FiberCal();
			//这里需要增加构件验算内容,这里的第二条曲线是已经折减过的设计值曲线
			SetCalEI(GlobalPara::Iin);
			MegaDesn_(&(GlobalPara::m_DesnPara),GlobalPara::M_Cu,GlobalPara::N_Cu);		//构件验算
		}
		int iflag = 4;
		PluginCmd::SetIcon(iflag);
		int iWay = 99;
		m_pCfgBas->Closfl(iWay);
		m_pCfgBas->Tobegin0(iWay);
		iWay = 1;
		m_pCfgBas->Closfl(iWay);
		m_pCfgBas->Tobegin0(iWay);
//		if(!GlobalPara::m_DesnPara.ifFiber)
			
//		DrawNMCurve::CalColmNMCurve_Fiber();
//		PluginCmd::OnCalForce();
//		MegaCheckIO_(&(GlobalPara::m_Sect_in),&(GlobalPara::m_DesnPara));
	}
	else if (0 == CSTR.CompareNoCase("MEGA_DRAW"))
	{
		PluginFun::Get().NeiLiTuDlgDock();
	}
	else if(CSTR=="MEGAGETFORCE"){
		MegaCheckIO_(&(GlobalPara::m_Sect_in),&(GlobalPara::m_DesnPara));
	}
	else if(CSTR=="MEGA_MESH"){
		DrawNMCurve::GSect_Mesh();
	}
	else if(0==CSTR.CompareNoCase("MEGA_LANGUAGE"))
	{
		CDlgLang dlg;
		if(IDOK == dlg.DoModal())
		{
			if (0==dlg.m_lang)
			{
				LCID lcidNew = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT);
				SetThreadLocale(lcidNew);
			}
			else if (1==dlg.m_lang)
			{
				LCID lcidNew = MAKELCID(MAKELANGID(LANG_GERMAN,SUBLANG_GERMAN),SORT_DEFAULT);
				SetThreadLocale(lcidNew);
			}
			else if (2==dlg.m_lang)
			{
				LCID lcidNew = MAKELCID(MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_SIMPLIFIED),SORT_DEFAULT);
				SetThreadLocale(lcidNew);
			}
		}
	}
	else if (0 == CSTR.CompareNoCase("MEGA_LOADCASE_DLG"))
	{
		CDlgLoadInput dlg;
		dlg.SetMegaLoad(Mega_Cases::Get().Cases());


		if(IDOK == dlg.DoModal())
		{
			Mega_Cases::Get().SetCases(dlg.MegaLoad());
			
		}
		else
		{
			//Mega_Cases::Get().SetCases(dlg.MegaLoad());
		}
		int iflag = 3;
		PluginCmd::SetIcon(iflag);
	}
	else if (0 == CSTR.CompareNoCase("MEGA_SECT_LIST_DLG"))
	{
		CDlgSectionList dlg;
		if(IDOK == dlg.DoModal())
		{
			int nKd,nSel;
			dlg.GetResult(nKd,nSel);
			int nBegin,nEnd;
			CSectKeeper::Get().TypeBeginEnd(nKd,nBegin,nEnd);
			nSel = nSel + nBegin;

			struct HE_  hh = CSectKeeper::Get().steelC().HE[nSel];
		}

		
	}
	else if(CSTR=="FIBERCAL2"){
		//DrawNMCurve::GSect_FiberCal();
	}
	else if(CSTR=="MEGALOADCOMB"){
		MegaCombDlg dlg;
		if(IDOK == dlg.DoModal()){
			PluginCmd::ifautocomb = true;
		}
	}
	else if(0 == CSTR.Compare("MEGA_REPORT"))
	{
//		if(GlobalPara::currentsect==0)
		 MegaReport();	//对于任意截面先不输出结果文本
	}
	return 0;
}

void PluginCmd::RunCmd(const CString& cmd)
{
	int Itype=-1,NInt=2,IPara[2],NFloat=2,NStr=2,LStr=cmd.GetLength(),n1=0;
	float RPara[2];
	char *StrPara[2];
	char StrCmd[40];
	strncpy(StrCmd,cmd,LStr);
	StrCmd[LStr]=char(0);
	StrPara[0]=StrCmd;
	RELOAD_MAIN_SUB(Itype,NInt,IPara,NFloat,RPara,NStr,LStr,StrPara,n1);
}




extern "C"  void CALMG_FUNC(float RPARA[30],float LoadP[6]);
int PluginCmd::OnCalForce(CArray<mega_loads> & cases)
{
	int iWay = 99;
	m_pCfgBas->Closfl(iWay);
	GlobalPara::m_DesnPara.f1_y = cases[0].f0;
	GlobalPara::m_DesnPara.f2_y = cases[0].f1;
	GlobalPara::m_DesnPara.f3_y = cases[0].f2;
	GlobalPara::m_DesnPara.f1_z = cases[0].f0;
	GlobalPara::m_DesnPara.f2_z = cases[0].f1;
	GlobalPara::m_DesnPara.f3_z = cases[0].f2;
	GlobalPara::m_DesnPara.nLoads_y = cases.GetSize();
	GlobalPara::m_DesnPara.nLoads_z = cases.GetSize();
	float Rpara[30],LoadPj[6];
	Rpara[0] = GlobalPara::m_DesnPara.Lens;
	Rpara[1] = GlobalPara::m_DesnPara.Restrict;
	Rpara[2] = 2;//
	Rpara[3] = 1;
	Rpara[4] = 0.85;
	Rpara[5] = 200;
	Rpara[6] = 150;
	Rpara[7] = 0;
	Rpara[8] = 3;
	Rpara[9] = 0;
	Rpara[10] = 1;	
	LoadPj[0] = 1;	
	//位置按mm,力按kN
	//先算yy向
	for(int i=0;i<cases.GetSize();i++){
		CString temp = cases[i].Notatio;
		char* temp2 = temp.GetBuffer(temp.GetLength());
		memcpy(GlobalPara::m_DesnPara.notation[i],temp2,10*sizeof(char));
//		GlobalPara::m_DesnPara.notaion[i].Format(_T("%s"),cases[i].Notatio);
		for(int j1=0;j1<cases[i].ConYY.GetSize();j1++){
			LoadPj[1] = 8;
			LoadPj[2] = cases[i].ConYY[j1].F; //荷载值P
			LoadPj[3] = cases[i].ConYY[j1].x;  //x
			CALMG_FUNC(Rpara,LoadPj);
		}
		for(int j2=0;j2<cases[i].DisYY.GetSize();j2++){
			GlobalPara::m_DesnPara.My_hasmidforce = true;
			LoadPj[1] = 111;
			LoadPj[2] = cases[i].DisYY[j2].q1;
			LoadPj[3] = cases[i].DisYY[j2].q2;
			LoadPj[4] = cases[i].DisYY[j2].x1;
			LoadPj[5] = cases[i].DisYY[j2].x2;
			CALMG_FUNC(Rpara,LoadPj);			
		}
		//给一下荷载数量
		GlobalPara::m_DesnPara.nLoadCase_y[i] = cases[i].ConYY.GetSize()+cases[i].DisYY.GetSize();
		Tools::CalEndM(cases[i].EndmYY.Top*1e6,cases[i].EndmYY.Bottom*1e6,i,1);		
	}
	//再算zz向
	for(int i=0;i<cases.GetSize();i++){
		for(int j1=0;j1<cases[i].ConZZ.GetSize();j1++){
			LoadPj[1] = 8;
			LoadPj[2] = cases[i].ConZZ[j1].F; //荷载值P
			LoadPj[3] = cases[i].ConZZ[j1].x;  //x
			CALMG_FUNC(Rpara,LoadPj);
		}
		for(int j2=0;j2<cases[i].DisZZ.GetSize();j2++){
			GlobalPara::m_DesnPara.Mz_hasmidforce = true;
			LoadPj[1] = 111;
			LoadPj[2] = cases[i].DisZZ[j2].q1;
			LoadPj[3] = cases[i].DisZZ[j2].q2;
			LoadPj[4] = cases[i].DisZZ[j2].x1;
			LoadPj[5] = cases[i].DisZZ[j2].x2;
			CALMG_FUNC(Rpara,LoadPj);
		}
		GlobalPara::m_DesnPara.nLoadCase_z[i] = cases[i].ConZZ.GetSize()+cases[i].DisZZ.GetSize();		
		Tools::CalEndM(cases[i].EndmZZ.Top*1e6,cases[i].EndmZZ.Bottom*1e6,i,2);	
	}
	//最后统计叠加一下轴力
	for(int i=0;i<cases.GetSize();i++){
		float N_max = max(cases[i].AnxialForceYY,cases[i].AnxialForceZZ);
		N_max = N_max*1000;		//kN
		//i=0的时候叠加一下自重
		if(i==0){
			N_max = N_max+Tools::CalSelfG();
		}
		Tools::CalEndN(N_max,i);
	}	
	return 1;
}
	//再算zz向

	// // 				if(LoadPj[1]==8){
	// // 					LoadPj[2] = GlobalPara::m_loads1_z[i].p1;
	// // 					LoadPj[3] = GlobalPara::m_loads1_z[i].x1;
	// // 					LoadPj[4] = 0;
	// // 					LoadPj[5] = 0;
	// // 				}
	// // 				else if(LoadPj[1]==10){
	// // 					LoadPj[2] = GlobalPara::m_loads1_z[i].p1;
	// // 					LoadPj[3] = GlobalPara::m_loads1_z[i].p2;
	// // 					LoadPj[4] = GlobalPara::m_loads1_z[i].x1;
	// // 					LoadPj[5] = GlobalPara::m_loads1_z[i].x2;
	// // 				}
	// 				CALMG_FUNC(Rpara,LoadPj);

	/*char  MgName[10];
	CString name(_T("mgmodel"));
	strncpy(MgName,name,name.GetLength());*/

	//if(DLLINSTANCE!=NULL)
// 	for(int iCa=0;iCa<cases.GetCount();iCa++)
// 	{
// 		//FUNCALMG fCalMg = (FUNCALMG)GetProcAddress(DLLINSTANCE,"CALMG_FUNC");
// 
// 		//按工况循环
// //		mega_loads load1 = cases[iCa];
// // 		load1.loadtype = 8;
// // 		load1.p1 = 2;
// // 		load1.x1 = 8000;
// //		GlobalPara::m_loads1_z.Add(load1);
// 
// 		if(GlobalPara::m_loads1_z.GetSize()>0){	//有恒载
// 			for(int i=0;i<GlobalPara::m_loads1_z.GetSize();i++){
// 				Rpara[0] = GlobalPara::m_DesnPara.Lens;
// 				Rpara[1] = GlobalPara::m_DesnPara.Restrict;
// 				Rpara[2] = 2;//
// 				Rpara[3] = 1;
// 				Rpara[4] = 0.85;
// 				Rpara[5] = 200;
// 				Rpara[6] = 150;
// 				Rpara[7] = 0;
// 				Rpara[8] = 3;
// 				Rpara[9] = 0;
// 				Rpara[10] = 1;
// 
// 				LoadPj[0] = 1;
// 				LoadPj[1] = 8;
// 				LoadPj[3] =10; //荷载值P
// 				LoadPj[4] =3000;  //x
// 				LoadPj[5] =0;  //荷载值P1
// 				LoadPj[6] =0;  //x1
// //				LoadPj[2] = 
// 				//GlobalPara::m_loads1_z[i].loadtype;
// // 				if(LoadPj[1]==8){
// // 					LoadPj[2] = GlobalPara::m_loads1_z[i].p1;
// // 					LoadPj[3] = GlobalPara::m_loads1_z[i].x1;
// // 					LoadPj[4] = 0;
// // 					LoadPj[5] = 0;
// // 				}
// // 				else if(LoadPj[1]==10){
// // 					LoadPj[2] = GlobalPara::m_loads1_z[i].p1;
// // 					LoadPj[3] = GlobalPara::m_loads1_z[i].p2;
// // 					LoadPj[4] = GlobalPara::m_loads1_z[i].x1;
// // 					LoadPj[5] = GlobalPara::m_loads1_z[i].x2;
// // 				}
// 				CALMG_FUNC(Rpara,LoadPj);
// 				//如果是端部的内力，则需要另外计算
// //				double Mtop,Mend;
// //				Tools::CalEndM(Mtop,Mend,cases.GetCount());
// 			}
// 		}
// 	}	
	/*delete[] Rpara;
	delete[] LoadPj;*/



//发送带2个指针参数的命令
void PluginCmd::SendPluginCmd(CString  cmd,LPVOID cmdPara)
{
	int Itype=-15,NInt=2,IPara[2],NFloat=2,NStr=2,LStr=cmd.GetLength(),n1=0;
	float RPara[2];
	char *StrPara[2];
	char Strcmd[256];
	strncpy(Strcmd,cmd,LStr);
	Strcmd[LStr]=char(0);
	StrPara[0]=Strcmd;
	void **p = (void**)cmdPara;
	IPara[0]=(int)(p[0]);
	IPara[1]=(int)(p[1]);

	RELOAD_MAIN_SUB(Itype,NInt,IPara,NFloat,RPara,NStr,LStr,StrPara,n1);
}

int PluginCmd::OnCommandPara( LPVOID cmdPara )
{
 	float *RPARA;
 	void **p = (void**)cmdPara;
 	CString strCmd = LPCTSTR(p[0]);
	if (stricmp(LPCTSTR(p[0]), "COMMONINFO_CMD_STS_TREE_MESSAGE") == 0)
	{
		LPCTSTR menuName=LPCTSTR(p[1]);
		LPCTSTR menuMark=LPCTSTR(p[2]);
		CString CSTR=menuName;

		bool bFindCmd = false;
		if(stricmp(menuMark, "MEGA_NEILI_TU") == 0&&false == bFindCmd)
		{
			PluginFun::Get().NeiLiTuDraw( CSTR );
		}
 	}

	return 0; 
}
//加载带注册命令的动态库
void PluginCmd::LoadFile(CString &StrFileDll)
{
	int Itype=-13,NInt=2,IPara[2],NFloat=2,NStr=2,LStr=StrFileDll.GetLength(),n1=0;
	float RPara[2];
	char *StrPara[2];
	char StrFile[256];
	strncpy(StrFile,StrFileDll,LStr);
	StrFile[LStr]=char(0);
	StrPara[0]=StrFile;
	RELOAD_MAIN_SUB(Itype,NInt,IPara,NFloat,RPara,NStr,LStr,StrPara,n1);
}

//卸载带注册命令的动态库
void PluginCmd::UnLoadFile(CString &StrFileDll)
{
	int Itype=-14,NInt=2,IPara[2],NFloat=2,NStr=2,LStr=StrFileDll.GetLength(),n1=0;
	float RPara[2];
	char *StrPara[2];
	char StrFile[256];
	strncpy(StrFile,StrFileDll,LStr);
	StrFile[LStr]=char(0);
	StrPara[0]=StrFile;
	RELOAD_MAIN_SUB(Itype,NInt,IPara,NFloat,RPara,NStr,LStr,StrPara,n1);
}

//清空T图
void PluginCmd::ClsAllGraphic()
{

}

void PluginCmd::CloseMiniPane()
{
	int NFloat = 1;
	float RPara[1];
	int NStr = 1;
	int LStr = 0;
	char chCaption[256];
	char *StrPara[1];
	StrPara[0] = chCaption;
	int n1 = 1;
	// 有用的参数
	int Itype = -23;
	int NInt = 1;
	int IPara[1];
	IPara[0] = -1;	// 全部清除

	RELOAD_MAIN_SUB(Itype, NInt, IPara, NFloat, RPara, NStr, LStr, StrPara, n1);
}

void PluginCmd::DestoryAllDlg()
{
	int NFloat = 1;
	float RPara[1];
	int n1 = 1;
	// 有用的参数
	int Itype = -18;
	int NInt = 4;
	int IPara[1];
	IPara[0] = -1;	// 全部清除

	int NStr = 1;
	int LStr = 0;
	char chCaption[256];
	char *StrPara[1];
	StrPara[0] = chCaption;

	RELOAD_MAIN_SUB(Itype, NInt, IPara, NFloat, RPara, NStr, LStr, StrPara, n1);
}

void PluginCmd::Language( CString & strLanguage )
{
	// 有用的参数
	int Itype = -50;
	int NInt = 0;
	int IPara[1];

	int NFloat = 0;
	float RPara[1];

	int NStr = 1;
	int LStr = MAX_PATH;
	char chCaption[MAX_PATH];
	char *StrPara[1];
	StrPara[0] = chCaption;
	int n1 = 0;
 
	RELOAD_MAIN_SUB(Itype, NInt, IPara, NFloat, RPara, NStr, LStr, StrPara, n1);
	strLanguage = chCaption;
	strLanguage.Trim();
}

void PluginCmd::OnEnalbeIcon_Ribbon(const CString &strID,const bool &bEnable)
{
	int Itype=-22,NInt=2,IPara[2],NFloat=2,NStr=2,LStr=strID.GetLength(),n1=0;
	float RPara[2];
	char *StrPara[2];
	char StrFile[256];
	if (bEnable)
		IPara[0]=1;
	else
		IPara[0]=0;
	strncpy(StrFile,strID,LStr);
	StrFile[LStr]=char(0);
	StrPara[0]=StrFile;
	RELOAD_MAIN_SUB(Itype,NInt,IPara,NFloat,RPara,NStr,LStr,StrPara,n1);
}

//控制图标的显示
void PluginCmd::SetIcon(int iflag)
{
	bool binit=true;
	bool binputsect=true;
	bool binputload=false;
	bool bcal=false;
	bool bresult=false;
	bool bmesh=false;
	if(iflag==1){	//初始化
		binit=true;
		binputsect=true;
		binputload=false;
		bcal=false;
		bresult=false;
	}
	else if(iflag==2){	//输入荷载
		binit=true;
		binputsect=true;
		binputload=true;
		bcal=false;
		bresult=false;
	}
	else if(iflag==3){	//可以计算
		binit=true;
		binputsect=true;
		binputload=true;
		bcal=true;
		bresult=false;
	}
	else if(iflag==4){	//可以查看结果
		binit=true;
		binputsect=true;
		binputload=true;
		bcal=true;
		bresult=true;
	}

	if(iflag==3)
	{
		if(GlobalPara::m_DesnPara.ifFiber)
			bmesh=true;
	}

	//参数输入
	//OnEnalbeIcon_Ribbon();
	//荷载输入
	OnEnalbeIcon_Ribbon(_T("ID_MEGALOAD"),binputload);
	OnEnalbeIcon_Ribbon(_T("ID_MEGACOMB"),binputload);
	//计算功能
	OnEnalbeIcon_Ribbon(_T("ID_DESIGNPARA"),bcal);
	OnEnalbeIcon_Ribbon(_T("ID_MEGASECTCAL"),bcal);
	OnEnalbeIcon_Ribbon(_T("ID_GSD_MESH"),bmesh);

	//结果查看
	OnEnalbeIcon_Ribbon(_T("ID_MEGA_DRAW"),bresult);
	OnEnalbeIcon_Ribbon(_T("ID_MEGA_REPORT"),bresult);
// 	if(GlobalPara::currentsect==0)
// 		OnEnalbeIcon_Ribbon(_T("ID_MEGA_REPORT"),bresult);
// 	else{
// 		bool bfalse = false;
// 		OnEnalbeIcon_Ribbon(_T("ID_MEGA_REPORT"),bfalse);
// 	}

}

int PluginCmd::OnTipMessage(LPVOID cmdPkt)
{
	struct sTip{
		int *IX;
		int *IY;
		float *X;
		float *Y;
		float *Z;
		LPCTSTR STR;
	}*pTip;

	pTip = (struct sTip *)cmdPkt;

	int *IX = pTip->IX;
	int *IY = pTip->IY;
	float *X = pTip->X;
	float *Y = pTip->Y;
	float *Z = pTip->Z;
	char *STR = (char *)pTip->STR;
	int nStr = 200;

	GetTipsStr(*X,*Y,STR);
//	CGlobalTools::NowTTip(*X,*Y,*Z,STR);
	//如果是预定义截面

	//如果是自定义截面

	pTip->STR = STR;

	return 0;
}

bool PluginCmd::SaveMegaPara()
{
	if(filename.GetLength()>0){
		CFile File(filename,CFile::modeCreate|CFile::modeReadWrite);
		File.SeekToBegin();
		File.Write(&(GlobalPara::m_Sect_in),sizeof(SectDescribe));
		//保存设计结构
		File.Write(&(GlobalPara::m_DesnPara),sizeof(DesnPara));
		File.Close();
	}
	return true;
}

bool PluginCmd::SaveasMegaPara()
{
	char szFilters[] = "mega file(*.mega)\0*.mega\0";
	CFileDialog FileDlg(FALSE);
	FileDlg.m_ofn.lpstrTitle = "Save File";
	FileDlg.m_ofn.lpstrFilter = szFilters;

	if(IDOK == FileDlg.DoModal())
	{
		CFile File(FileDlg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);
		// 		CArchive ar(&File,CArchive::store);
		// 		ar<<GlobalPara::m_Sect_in
		//保存截面
		File.SeekToBegin();
		File.Write(&(GlobalPara::m_Sect_in),sizeof(SectDescribe));
		//保存设计结构
		File.Write(&(GlobalPara::m_DesnPara),sizeof(DesnPara));
		File.Close();
	}
	return true;
}

bool PluginCmd::NewMegaPara()
{
//	CNewfilename pdlg;
	char szFilters[] = "mega file(*.mega)\0*.mega\0";
	CFileDialog OpenDlg(true);
	OpenDlg.m_ofn.lpstrTitle = "New File";
	OpenDlg.m_ofn.lpstrFilter = szFilters;

	filename = OpenDlg.GetPathName();
	filename.Append(".mega");
//	filename = filename+".mega";
	if(IDOK==OpenDlg.DoModal()){
		CFile File(filename,CFile::modeCreate|CFile::modeReadWrite);
		//保存截面
		File.Write(&(GlobalPara::m_Sect_in),sizeof(SectDescribe));
		//保存设计结构
		File.Write(&(GlobalPara::m_DesnPara),sizeof(DesnPara));
		File.Close();
	}
	return true;
}

bool PluginCmd::OpenMegaPara()
{
	char szFilters[] = "mega file(*.mega)\0*.mega\0";
	CFileDialog OpenDlg(true);
	OpenDlg.m_ofn.lpstrTitle = "Open File";
	OpenDlg.m_ofn.lpstrFilter = szFilters;

	if(IDOK == OpenDlg.DoModal()){
		CFile File;
		CFileException e;
		if(!File.Open(OpenDlg.GetPathName(),CFile::modeRead,&e)){
			CString strErr;
			strErr.Format(_T("File could not be opened %d\n"),e.m_cause);
			AfxMessageBox(strErr);
		}
		DWORD dwFilelenth = (DWORD)File.GetLength();
		if(dwFilelenth>0){
			File.SeekToBegin();
			File.Read(&(GlobalPara::m_Sect_in),sizeof(SectDescribe));
			File.Read(&(GlobalPara::m_DesnPara),sizeof(DesnPara));
			File.Close();
		}
	}
	return true;
}

void PluginCmd::ChangeToSubModule(const int &iSubModule,const int &ifChangeMenu)
{
	int Itype=-17,NInt=2,IPara[2],NFloat=2,NStr=2,LStr=10,n1=0;
	float RPara[2];
	char *StrPara[2];
	IPara[0]=iSubModule;
	IPara[1]=ifChangeMenu;
	RELOAD_MAIN_SUB(Itype,NInt,IPara,NFloat,RPara,NStr,LStr,StrPara,n1);
}

void PluginCmd::SepSectforFiber()
{
	CString msg_char;
	int sect_type = GlobalPara::m_Sect_in.m_kind;
	if(sect_type==1){		//FP
		if(GlobalPara::m_DesnPara.shearmethod==1){
			GlobalPara::m_DesnPara.shearmethod==0;
			msg_char.Format(_T("Cross section type %d could not use Adapted method-truss model method,now change to Beam theory method!"),sect_type);
		}
	}
	else if(sect_type==2 || sect_type==5){	//F
		if(GlobalPara::m_DesnPara.ifFiber==0){
			GlobalPara::m_DesnPara.ifFiber==1;
			msg_char.Format(_T("Cross section type %d could not use PDM method,now change to fiber model!"),sect_type);
		}
		if(GlobalPara::m_DesnPara.shearmethod==1)
			GlobalPara::m_DesnPara.shearmethod=0;
	}
	else if(sect_type==8){	//FP
		if(GlobalPara::m_DesnPara.shearmethod==1){
			GlobalPara::m_DesnPara.shearmethod==0;
			msg_char.Format(_T("Cross section type %d could not use Adapted method-truss model method,now change to Beam theory method!"),sect_type);
		}
	}
	if(msg_char.GetLength()>0)
		AfxMessageBox(msg_char);
}