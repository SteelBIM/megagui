// MegaColumnGui.h : MegaColumnGui DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__

#endif

#include "resource.h"		// ������
#include "PredefSectDescrib.h"
#include "GlobalPara.h"
#include "DlgSectionList.h"
#include "SectionReader.h"

// CMegaColumnGuiApp
// �йش���ʵ�ֵ���Ϣ������� MegaColumnGui.cpp
//

class CMegaColumnGuiApp : public CWinApp
{
public:
	CMegaColumnGuiApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
