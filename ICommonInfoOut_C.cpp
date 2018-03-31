#include "stdafx.h"
#include "ICommonInfoOut_C.h"
#include "UiDialogManipulate.h"

extern "C" __declspec(dllexport) void __stdcall SHOW_RUNINFO_DLG()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    UiDialogManipulate::Get()->Show();
}

extern "C" __declspec(dllexport) void __stdcall EXIT_RUNINFO_DLG()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    UiDialogManipulate::Get()->Bye();
}

extern "C" __declspec(dllexport) void __stdcall CLOSE_RUNINFO_DLG()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    UiDialogManipulate::Get()->Close();
}


extern "C" __declspec(dllexport) void __stdcall REG_KILL_CALLBACK(Fun_OutUi_Callback fooCallBack)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (fooCallBack!=nullptr)
    {
        UiDialogManipulate::Get()->RegKillCallBack(true,fooCallBack);
    }
}

extern "C" __declspec(dllexport) void __stdcall SET_ANALYZEITEM(char *sTemp, int len)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CString str(sTemp, len);
    UiDialogManipulate::Get()->Step(str);
}

extern "C" __declspec(dllexport) void __stdcall ADDTXT_TORUNINFODLG(char *sTemp, int len)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if(len<=0) return;  // 保护

    CString str(sTemp, len-1); // fortran传过来，并不是C里用strlen得到的长度，而是strlen+1
    str += _T("\r\n");

    UiDialogManipulate::Get()->TextParagraph(str, false,
        /*int nProgress = */UIPROGRESS_HOLDON,
        /*int nLevel = */3,
        /*int indent = */UITEXT_INDENT_DEFAULT,
        /*COLORREF clr = */UITEXT_COLOR_DEFAULT,
        /*bool bBold = */false,
        /*bool bItalic = */false,
        /*bool bUnderLine = */false);
}

extern "C" __declspec(dllexport) void __stdcall SET_RUNINFO_PROGRESS(int& process)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    UiDialogManipulate::Get()->Progress(process);
}

extern "C" __declspec(dllexport) void __stdcall DLG_TOTOP()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	UiDialogManipulate::Get()->DlgToTop();
}