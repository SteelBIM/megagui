// stdafx.cpp : 只包括标准包含文件的源文件
// MegaColumnGui.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#ifdef _DEBUG
#pragma comment(lib, "Sts_SectD.lib")
#pragma comment(lib, "StsKeyDllD.lib")
#pragma comment(lib, "megasectcalD.lib")
#pragma comment(lib, "thinbeamExportD.lib")
#pragma comment(lib, "CommonInfoOutD.lib")
#else
#pragma comment(lib, "Sts_Sect.lib")
#pragma comment(lib, "StsKeyDll.lib")
#pragma comment(lib, "megasectcal.lib")
#pragma comment(lib, "thinbeamExport.lib")
 #pragma comment(lib, "CommonInfoOut.lib")
#endif