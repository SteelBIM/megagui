#include "StdAfx.h"
#include "PluginFun.h"
#include "PluginCmd.h"
#include "Loaddef.h"
#include "json/json.h"
#include "MsgMacroHeader.h"
#include "DlgNMVSel.h"
#include "CfgBas.h"
 

extern "C" __declspec( dllimport ) CCfgBas *m_pCfgBas;

extern "C" __declspec( dllimport ) void MegaDraw(int nLoadCase , int nType);

PluginFun PluginFun::s_PluginFun;
PluginFun& PluginFun::Get()
{
	return s_PluginFun;
}


PluginFun::PluginFun(void)
{

}


PluginFun::~PluginFun(void)
{
}
void PluginFun::NeiLiTuDlg()
{
	CDlgNMVSel dlg;
	if(IDOK == dlg.DoModal())
	{
		CString str = dlg.GetSelStr();
		NeiLiTuDraw(str);
	}

}

void PluginFun::FillNeiLiTuDock(Json::Value& meu)
{
	PluginFun::Get().NeiliTuNames().RemoveAll();
	int iway = 1;
	m_pCfgBas->Closfl(iway);
	int nCaseCount = Mega_Cases::Get().Cases().GetCount();
	int nCol=2;
	CString strIndex;
	CString strNa;
	CString strdes;
	int nLine=0;
	CString indexFormat;
	indexFormat="@%04d";
	CString meuIdx;
	for (int iCase =0;iCase<nCaseCount;iCase++)
	{
		//ZHLEI 2017/11 :
		strIndex.Format("%0d",nLine+1);
		strdes = Mega_Cases::Get().Cases().GetAt(iCase).Description;
		strNa.Format("%s_M(Y-Y)",strdes);
		PluginFun::Get().NeiliTuNames().Add(strNa);

		meuIdx.Format(indexFormat,nLine);
		meu[meuIdx] = LPCTSTR(strNa);

		nLine++;


		//ZHLEI 2017/11 :
		strIndex.Format("%0d",nLine+1);
		strdes = Mega_Cases::Get().Cases().GetAt(iCase).Description;
		strNa.Format("%s_M(Z-Z)",strdes);
		PluginFun::Get().NeiliTuNames().Add(strNa);

		meuIdx.Format(indexFormat,nLine);
		meu[meuIdx] = LPCTSTR(strNa);
		nLine++;

		//ZHLEI 2017/11 :
		strIndex.Format("%0d",nLine+1);
		strdes = Mega_Cases::Get().Cases().GetAt(iCase).Description;
		strNa.Format("%s_V(Y-Y)",strdes);
		PluginFun::Get().NeiliTuNames().Add(strNa);

		meuIdx.Format(indexFormat,nLine);
		meu[meuIdx] = LPCTSTR(strNa);
		nLine++;

		//ZHLEI 2017/11 :
		strIndex.Format("%0d",nLine+1);
		strdes = Mega_Cases::Get().Cases().GetAt(iCase).Description;
		strNa.Format("%s_V(Z-Z)",strdes);
		PluginFun::Get().NeiliTuNames().Add(strNa);

		meuIdx.Format(indexFormat,nLine);
		meu[meuIdx] = LPCTSTR(strNa);
		nLine++;

		//ZHLEI 2017/11 :
		strIndex.Format("%0d",nLine+1);
		strdes = Mega_Cases::Get().Cases().GetAt(iCase).Description;
		strNa.Format("%s_N",strdes);
		PluginFun::Get().NeiliTuNames().Add(strNa);

		meuIdx.Format(indexFormat,nLine);
		meu[meuIdx] = LPCTSTR(strNa);
		nLine++;
	}
	if(GlobalPara::currentsect==0){
		if(GlobalPara::m_DesnPara.ifFiber){
			m_bHasFiberNM = GlobalPara::m_DesnPara.ifFiber;
			m_bHasPDM = false;
		}
		else{
			m_bHasFiberNM = false;
			m_bHasPDM = true;
		}
	}
	else{
		m_bHasFiberNM = true;
		m_bHasPDM = false;
	}

	if (m_bHasPDM)
	{
		strNa=_T("N-M Curve (PDM Method y-y axis)");
		PluginFun::Get().NeiliTuNames().Add(strNa);

		meuIdx.Format(indexFormat,nLine);
		meu[meuIdx] = LPCTSTR(strNa);
		nLine++;

		strNa=_T("N-M Curve (PDM Method z-z axis)");
		PluginFun::Get().NeiliTuNames().Add(strNa);

		meuIdx.Format(indexFormat,nLine);
		meu[meuIdx] = LPCTSTR(strNa);
		nLine++;
		
	}

	if(m_bHasFiberNM)
	{
		strNa=_T("N-M Curve (Fiber Model y-y axis)");
		PluginFun::Get().NeiliTuNames().Add(strNa);

		meuIdx.Format(indexFormat,nLine);
		meu[meuIdx] = LPCTSTR(strNa);
		nLine++;

		strNa=_T("N-M Curve (Fiber Model z-z axis)");
		PluginFun::Get().NeiliTuNames().Add(strNa);

		meuIdx.Format(indexFormat,nLine);
		meu[meuIdx] = LPCTSTR(strNa);
		nLine++;
	}
	

	 
}
void PluginFun::NeiLiTuDlgDock()
{
	//NeiLiTuDlg();
	//return ;
	//m_NeliTuNames.RemoveAll();

	//int iCaseCount = Mega_Cases::Get().Cases().GetCount();

	Json::Value meu;
 	meu["CONFIG_CAPTION"] = "NMV";
  	meu["CONFIG_CMDMARK"] = "MEGA_NEILI_TU";	// 随COMMONINFO_CMD_STS_TREE_MESSAGE 返回的一个标志
  	meu["CONFIG_SIMPLEMODE"] = true;		      //true仅显示选中对象的名字.  false 从树的顶级一直记录路径到选中对象 格式 ROOT|ITEM|SUBITEM
  	meu["CONFIG_ADD_SINGLE_TOP"] = false;
 
	FillNeiLiTuDock(meu);

	LPVOID cmdPara[2];
	cmdPara[0] = LPVOID(&meu);

// 	Json::FastWriter wr;
// 	wr.write(meu).c_str();

//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_NeliTuNames.GetSize()>0)
	{
		NeiLiTuDraw( m_NeliTuNames[0] );
	}
	
	PluginCmd::SendPluginCmd("COMMONINFO_CMD_SHOW_STS_TREE",cmdPara);
	 
}

bool PluginFun::NeiLiTuDraw( CString str )
{
	str.Trim();
	int nFind = -1;
	int ipara=1;
	for (int i=0;i<m_NeliTuNames.GetCount();i++)
	{
		CString s1 =m_NeliTuNames.GetAt(i);
		if (0 == s1.CompareNoCase(str))
		{
			nFind = i;
			break;
		}
	}

	if (nFind == -1)
	{
		return false;
	}
	if (0==str.CompareNoCase("N-M Curve (PDM Method y-y axis)"))
	{
		int iWay = 99;
//		char Dir[256];
//		GetCurrentDirectory( 256, Dir ); 
		CString StrFile;
//		StrFile.Format(_T("%s\\PDM_NM_y.t"),Dir);
		StrFile=_T("PDM_NM_y.t");
		int n1=StrFile.GetLength();
		char FileName[256];
		strcpy(FileName,StrFile);
		FileName[n1]=char(0);
		m_pCfgBas->Closfl(iWay);
		m_pCfgBas->Setcfg();
		m_pCfgBas->Openfl(iWay,FileName,n1,n1);
		m_pCfgBas->Ttips(ipara);
		m_pCfgBas->Zoome();
 		//m_pCfgBas->Nowfil(iWay);
 		//m_pCfgBas->Tobegin0(iWay);
		return true;
	}
	else if (0==str.CompareNoCase("N-M Curve (PDM Method z-z axis)"))
	{
		int iWay = 99;
//		char Dir[256];
//		GetCurrentDirectory( 256, Dir ); 
		CString StrFile;
//		StrFile.Format(_T("%s\\PDM_NM_z.t"),Dir);
		StrFile=_T("PDM_NM_z.t");
		int n1=StrFile.GetLength();
		char FileName[256];
		strcpy(FileName,StrFile);
		FileName[n1]=char(0);
		m_pCfgBas->Closfl(iWay);
		m_pCfgBas->Setcfg();
		m_pCfgBas->Openfl(iWay,FileName,n1,n1);
		m_pCfgBas->Zoome();
		m_pCfgBas->Ttips(ipara);

		//m_pCfgBas->Nowfil(iWay);
		//m_pCfgBas->Tobegin0(iWay);
		return true;
	}
	else if (0==str.CompareNoCase("N-M Curve (Fiber Model y-y axis)"))
	{
		int iWay = 99;
//		char Dir[256];
//		GetCurrentDirectory( 256, Dir ); 
		CString StrFile;
//		StrFile.Format(_T("%s\\Fiber_NM_y.t"),Dir);
		StrFile=_T("Fiber_NM_y.t");
		int n1=StrFile.GetLength();
		char FileName[256];
		strcpy(FileName,StrFile);
		FileName[n1]=char(0);
		m_pCfgBas->Closfl(iWay);
		m_pCfgBas->Setcfg();
		m_pCfgBas->Openfl(iWay,FileName,n1,n1);
		m_pCfgBas->Zoome();
		m_pCfgBas->Ttips(ipara);

		//m_pCfgBas->Nowfil(iWay);
		//m_pCfgBas->Tobegin0(iWay);
		return true;
	}
	else if (0==str.CompareNoCase("N-M Curve (Fiber Model z-z axis)"))
	{
		int iWay = 99;
//		char Dir[256];
//		GetCurrentDirectory( 256, Dir ); 
		CString StrFile;
//		StrFile.Format(_T("%s\\Fiber_NM_z.t"),Dir);
		StrFile=_T("Fiber_NM_z.t");
		int n1=StrFile.GetLength();
		char FileName[256];
		strcpy(FileName,StrFile);
		FileName[n1]=char(0);
		m_pCfgBas->Closfl(iWay);
		m_pCfgBas->Setcfg();
		m_pCfgBas->Openfl(iWay,FileName,n1,n1);
		m_pCfgBas->Zoome();
		m_pCfgBas->Ttips(ipara);

		//m_pCfgBas->Nowfil(iWay);
		//m_pCfgBas->Tobegin0(iWay);
		return true;
	}

	int nType = (nFind)%5;// 1 = MYY  1=MZZ  2=VYY 3=VZZ 4=N
	nType += 1;
	int nLoadCase = int(nFind / 5.0);
	MegaDraw(nLoadCase,nType);
	m_pCfgBas->Zoome();
	return true;
}

CArray<CString>& PluginFun::NeiliTuNames()
{
	return m_NeliTuNames;
}

void PluginFun::SetHasFiberNM( bool bHas/*=true*/ )
{
	m_bHasFiberNM = bHas;
}

void PluginFun::SetHasPDM( bool bHas/*=true*/ )
{
	m_bHasPDM = bHas;
}


