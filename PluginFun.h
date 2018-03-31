#pragma once
#include "json\json.h"
class PluginFun
{
private:
	static PluginFun s_PluginFun;

	CArray<CString> m_NeliTuNames;


private:
	bool m_bHasFiberNM;
	bool m_bHasPDM;

public:
	static PluginFun& Get(); 
public:

	PluginFun(void);
	~PluginFun(void);

	void SetHasFiberNM(bool bHas=true);
	void SetHasPDM(bool bHas=true);


	void NeiLiTuDlgDock();
	bool NeiLiTuDraw(CString str);
	void NeiLiTuDlg();
	void FillNeiLiTuDock(Json::Value& meu);
	CArray<CString>& NeiliTuNames();

};

