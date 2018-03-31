// PluginCmd.h: interface for the PluginCmd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLUGINCMD_H__B2CC16CF_B9A5_4F0B_AB8D_0912E8408D10__INCLUDED_)
#define AFX_PLUGINCMD_H__B2CC16CF_B9A5_4F0B_AB8D_0912E8408D10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CmdManageDef.h"

class PluginCmd  
{
	DECLARE_CMDMNGR_MSGMAP()
public:
	static CString filename;

protected:
	static char PLUG_SIG[10];

public:
	static int m_ICmdFrom;			//0:-命令来源于平台;1:-命令来源于动态库;
	static bool ifautocomb;
	static HINSTANCE m_HInstanceExternalRes;
	static void PluginCmd::RunCmd(const CString& cmd);
	static int OnCalForce(CArray<mega_loads> & cases);
	static void ClsAllGraphic();
protected:
	static void RegisterMyCmds();
	static void RegisterLinkParas();
	static int OnTipMessage(LPVOID cmdPkt);

	static int OnRibbonMenuExpanded(LPVOID cmdPkt);

	static int OnLoad(LPVOID cmdPara);
	static int OnUnload(LPVOID cmdPara);
	static int OnBeforeQuit(LPVOID cmdPara);
	static int OnInit(LPVOID cmdPara);
	static int OnSetCmdFromDll(LPVOID cmdPara);
	static int OnSetCmdFromSys(LPVOID cmdPara);
public:
	static void ChangeToSubModule(const int &iSubModule,const int &ifChangeMenu);
	static void SendPluginCmd(CString  cmd,LPVOID cmdPara);
	static int OnCommandPara(LPVOID cmdPara);
	static void LoadFile(CString &StrFileDll);
	static void UnLoadFile(CString &StrFileDll);
	static void CloseMiniPane();
	static void DestoryAllDlg();
	static void Language(CString & str);
	static void OnEnalbeIcon_Ribbon(const CString &strID,const bool &bEnable);
	static void SetIcon(int iflag);
	static bool SaveMegaPara();
	static bool SaveasMegaPara();
	static bool OpenMegaPara();
	static bool NewMegaPara();
	static void SepSectforFiber();	//处理一下截面，有些不能走PDM
};
#endif // !defined(AFX_PLUGINCMD_H__B2CC16CF_B9A5_4F0B_AB8D_0912E8408D10__INCLUDED_)
