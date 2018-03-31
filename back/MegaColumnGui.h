// MegaColumnGui.h : MegaColumnGui DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__

#endif

#include "resource.h"		// 主符号
#include "PredefSectDescrib.h"
#include "GlobalPara.h"
#include "DlgSectionList.h"
#include "SectionReader.h"

// CMegaColumnGuiApp
// 有关此类实现的信息，请参阅 MegaColumnGui.cpp
//

class CMegaColumnGuiApp : public CWinApp
{
public:
	CMegaColumnGuiApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
