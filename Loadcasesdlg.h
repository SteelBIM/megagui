#pragma once

//#include "Loaddef.h"
// CLoadcasesdlg 对话框
#include "GlobalPara.h"

class CLoadcasesdlg : public CDialog
{
	DECLARE_DYNAMIC(CLoadcasesdlg)

public:
	CLoadcasesdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoadcasesdlg();

// 对话框数据
	enum { IDD = IDD_DLG_LOADS };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	//load define
public:
// 	CArray<mega_loads*,mega_loads*> m_loads1_z;		//dead load
// 	CArray<mega_loads*,mega_loads*> m_loads1_y;		//dead load
// 	CArray<mega_loads*,mega_loads*> m_loads2_z;		//live1-3
// 	CArray<mega_loads*,mega_loads*> m_loads2_y;		//live1-3
// 	CArray<mega_loads*,mega_loads*> m_loads3_z;
// 	CArray<mega_loads*,mega_loads*> m_loads3_y;
// 	CArray<mega_loads*,mega_loads*> m_loads4_z;
// 	CArray<mega_loads*,mega_loads*> m_loads4_y;
	CString Notation_z[4];
	CString Descripe_z[4];
	CString Notation_y[4];
	CString Descripe_y[4];
	float f1_z[3];
	float f2_z[3];
	float f3_z[3];
	float f4_z[3];
	float f1_y[3];
	float f2_y[3];
	float f3_y[3];
	float f4_y[3];

	void DrawCol(); 
	void DrawCol_col(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,float x0,float y0,float x1,float y1);
	void DrawCol_yueshu(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,int ihing,float r,float x0,float y0,float x1,float y1);
	void DrawCol_zhizuo(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,int ihing,float x0,float y0,float x1,float y1);
	void DrawCol_hezai(int cenghao,int xianxing,int xiankuan,int yanse,int fanhui,float x0,float y0,float x1,float y1,
	float bili,int nload,int iloadtype[100],float P1loadcol[100],float y1loadcol[100],float P2loadcol[100],float y2loadcol[100]);
private:
	bool LoadLoads(int direct,int loadtype);

public:
	virtual BOOL OnInitDialog();
	CListCtrl m_disloads_list;
//	CListCtrl m_loads_list;
	CListCtrl m_nodeloads_list;
	afx_msg void OnBnClickedCheckcase1();
	afx_msg void OnBnClickedCheckcase2();
	afx_msg void OnBnClickedCheckcase3();
	afx_msg void OnBnClickedCheckcase4();
	BOOL m_check1;
	BOOL m_check2;
	BOOL m_check3;
	BOOL m_check4;
	afx_msg void OnBnClickedConAdd();
	afx_msg void OnBnClickedOk();
};
