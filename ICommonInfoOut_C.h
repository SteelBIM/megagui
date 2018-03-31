#pragma once

#ifdef __cplusplus
    extern "C"
    {
#endif
          __declspec(dllexport) void __stdcall SHOW_RUNINFO_DLG();
          __declspec(dllexport) void __stdcall EXIT_RUNINFO_DLG();
          __declspec(dllexport) void __stdcall CLOSE_RUNINFO_DLG();
          __declspec(dllexport) void __stdcall REG_KILL_CALLBACK(void (__stdcall *pFun)());
          __declspec(dllexport) void __stdcall SET_ANALYZEITEM(char *sTemp, int len);
          __declspec(dllexport) void __stdcall ADDTXT_TORUNINFODLG(char *sTemp, int len);
          __declspec(dllexport) void __stdcall SET_RUNINFO_PROGRESS(int& process);
		  __declspec(dllexport) void __stdcall DLG_TOTOP();

#ifdef __cplusplus 
    }
#endif