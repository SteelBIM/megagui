// DlgLoadInput.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "DlgLoadInput.h"
#include "afxdialogex.h"
#include <math.h>
#include "CfgBas.h"
#include <gdiplus.h>
#include <GdiplusTypes.h>
#pragma comment (lib,"gdiplus.lib")
using namespace Gdiplus;

extern "C" __declspec( dllimport ) CCfgBas *m_pCfgBas;

// CDlgLoadInput 对话框
const int CDlgLoadInput::MAX_DIS_COUNT = 4;
const int CDlgLoadInput::MAX_CON_COUNT = 6;
const int CDlgLoadInput::MAX_CASE_COUNT = 4;
const int CDlgLoadInput::LINELEN_DIS = 5;
const int CDlgLoadInput::LINELEN_CON = 3;
const int CDlgLoadInput::LINELEN_CASE = 6;

//extern "C" void __stdcall TONWNEX2(int& I);

IMPLEMENT_DYNAMIC(CDlgLoadInput, CDialogEx)

CDlgLoadInput::CDlgLoadInput(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLoadInput::IDD, pParent)
	, m_CurAxis(0)
{
	
	m_CurAxis = 0;
	m_CurCase = -1;
	m_CurCon = -1;
	m_CurDis = -1;
	m_CodeType = eCode_Euro;
	m_bMbuttonDown = FALSE;
	m_Scale = 1;
	m_ptPrev.x = 0;
	m_ptPrev.y = 0;
	//m_XOriPre=82,m_YOriPre=26;
	m_XOriPre=0,m_YOriPre=0;
	m_RedrawSwitch = TRUE;

	GdiplusStartupInput gidplusstartupinput;

	GdiplusStartup(&gidplusToken,&gidplusstartupinput,NULL);

	m_dcColumnHight = GlobalPara::m_DesnPara.Lens*1000;
	m_dcColumnWidth = GlobalPara::m_DesnPara.Lens*1000/12.0;

// 	m_hM = 0.0;
// 	m_hS = 1.0;
}

CDlgLoadInput::~CDlgLoadInput()
{
	GdiplusShutdown(gidplusToken);
}

bool CDlgLoadInput::InTabCase(int id,int& nRow,int& nColumn)
{
	nRow = -1;
	nColumn =-1;

	for(int i=0;i<IDLINE_CASE.GetCount();i++)
	{
		if(IDLINE_CASE[i] == id)
		{
			nColumn=i%LINELEN_CASE;
			nRow = i*1.0/LINELEN_CASE;
			return true;
		}
	}
	return false;

}
bool CDlgLoadInput::InTabCon(int id,int& nRow,int& nColumn)
{
	nRow = -1;
	nColumn =-1;

	for(int i=0;i<IDLINE_CON.GetCount();i++)
	{
		if(IDLINE_CON[i] == id)
		{
			nColumn=i%LINELEN_CON;
			nRow = i*1.0/LINELEN_CON;
			return true;
		}
	}
	return false;
}

bool CDlgLoadInput::InTabDis(int id,int& nRow,int& nColumn)
{
	nRow = -1;
	nColumn =-1;

	for(int i=0;i<IDLINE_DIS.GetCount();i++)
	{
		if(IDLINE_DIS[i] == id)
		{
			nColumn=i%LINELEN_DIS;
			nRow = i*1.0/LINELEN_DIS;
			return true;
		}
	}
	return false;
}
bool CDlgLoadInput::InTabEnd(int id,int& nRow,int& nColumn)
{
	nRow = -1;
	nColumn =-1;

	for(int i=0;i<IDLINE_END.GetCount();i++)
	{
		if(IDLINE_END[i] == id)
		{
			nRow = i;
			nColumn = 1;
			return true;
		}
	}
	return false;
}
bool CDlgLoadInput::InTabAxial(int id,int& nRow,int& nColumn)
{
	nRow = -1;
	nColumn =-1;

	for(int i=0;i<IDLINE_AXIAL.GetCount();i++)
	{
		if(IDLINE_AXIAL[i] == id)
		{
			nRow = 0;
			nColumn = 1;
			return true;
		}
	}
	return false;
}
void CDlgLoadInput::InitIndexCtrls()
{
	c_index_CaseList.Add(&c_index_case1);
	c_index_CaseList.Add(&c_index_case2);
	c_index_CaseList.Add(&c_index_case3);
	c_index_CaseList.Add(&c_index_case4);


	c_index_DisList.Add(&c_index_dis1);
	c_index_DisList.Add(&c_index_dis2);
	c_index_DisList.Add(&c_index_dis3);
	c_index_DisList.Add(&c_index_dis4);

	c_index_ConList.Add(&c_index_conload1);
	c_index_ConList.Add(&c_index_conload2);
	c_index_ConList.Add(&c_index_conload3);
	c_index_ConList.Add(&c_index_conload4);
	c_index_ConList.Add(&c_index_conload5);
	c_index_ConList.Add(&c_index_conload6);
	
}
void CDlgLoadInput::InitTableIds()
{
/*	LINELEN_CASE = 6;*/
	
	IDLINE_CASE.Add(IDC_EDTHINT_CASE1);
	IDLINE_CASE.Add(IDC_EDT_NOTATIO1);
	IDLINE_CASE.Add(IDC_EDT_DESCRIPTION1);
	IDLINE_CASE.Add(IDC_EDT_FAI0_1);
	IDLINE_CASE.Add(IDC_EDT_FAI1_1);
	IDLINE_CASE.Add(IDC_EDT_FAI2_1);

	IDLINE_CASE.Add(IDC_EDTHINT_CASE2);
	IDLINE_CASE.Add(IDC_EDT_NOTATIO2);
	IDLINE_CASE.Add(IDC_EDT_DESCRIPTION2);
	IDLINE_CASE.Add(IDC_EDT_FAI0_2);
	IDLINE_CASE.Add(IDC_EDT_FAI1_2);
	IDLINE_CASE.Add(IDC_EDT_FAI2_2);

	IDLINE_CASE.Add(IDC_EDTHINT_CASE3);
	IDLINE_CASE.Add(IDC_EDT_NOTATIO3);
	IDLINE_CASE.Add(IDC_EDT_DESCRIPTION3);
	IDLINE_CASE.Add(IDC_EDT_FAI0_3);
	IDLINE_CASE.Add(IDC_EDT_FAI1_3);
	IDLINE_CASE.Add(IDC_EDT_FAI2_3);

	IDLINE_CASE.Add(IDC_EDTHINT_CASE4);
	IDLINE_CASE.Add(IDC_EDT_NOTATIO4);
	IDLINE_CASE.Add(IDC_EDT_DESCRIPTION4);
	IDLINE_CASE.Add(IDC_EDT_FAI0_4);
	IDLINE_CASE.Add(IDC_EDT_FAI1_4);
	IDLINE_CASE.Add(IDC_EDT_FAI2_4);

	///////////////////////////////////////////////////////
//	LINELEN_CON=3;
	
	IDLINE_CON.Add(IDC_EDTHINT_CONLOAD_I1);
	IDLINE_CON.Add(IDC_EDT_CONLOAD_X1);
	IDLINE_CON.Add(IDC_EDT_CONLOAD_F1);

	IDLINE_CON.Add(IDC_EDTHINT_CONLOAD_I2);
	IDLINE_CON.Add(IDC_EDT_CONLOAD_X2);
	IDLINE_CON.Add(IDC_EDT_CONLOAD_F2);

	IDLINE_CON.Add(IDC_EDTHINT_CONLOAD_I3);
	IDLINE_CON.Add(IDC_EDT_CONLOAD_X3);
	IDLINE_CON.Add(IDC_EDT_CONLOAD_F3);

	IDLINE_CON.Add(IDC_EDTHINT_CONLOAD_I4);
	IDLINE_CON.Add(IDC_EDT_CONLOAD_X4);
	IDLINE_CON.Add(IDC_EDT_CONLOAD_F4);

	IDLINE_CON.Add(IDC_EDTHINT_CONLOAD_I5);
	IDLINE_CON.Add(IDC_EDT_CONLOAD_X5);
	IDLINE_CON.Add(IDC_EDT_CONLOAD_F5);

	IDLINE_CON.Add(IDC_EDTHINT_CONLOAD_I6);
	IDLINE_CON.Add(IDC_EDT_CONLOAD_X6);
	IDLINE_CON.Add(IDC_EDT_CONLOAD_F6);

//	LINELEN_DIS=5;
	IDLINE_DIS.Add(IDC_EDTHINT_DISLOAD_I1);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_X1_1);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_Q1_1);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_X2_1);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_Q2_1);

	IDLINE_DIS.Add(IDC_EDTHINT_DISLOAD_I2);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_X1_2);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_Q1_2);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_X2_2);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_Q2_2);

	IDLINE_DIS.Add(IDC_EDTHINT_DISLOAD_I3);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_X1_3);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_Q1_3);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_X2_3);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_Q2_3);

	IDLINE_DIS.Add(IDC_EDTHINT_DISLOAD_I4);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_X1_4);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_Q1_4);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_X2_4);
	IDLINE_DIS.Add(IDC_EDT_DISLOAD_Q2_4);

	IDLINE_END.Add(IDC_EDIT_END_BOTTOM);
	IDLINE_END.Add(IDC_EDIT_END_TOP);

	IDLINE_AXIAL.Add(IDC_EDT_AXIAL_FORCE);


	//ZHLEI 2017/11 :
	IDLINE_FAI.Add(IDC_EDT_FAI0_1);
	IDLINE_FAI.Add(IDC_EDT_FAI1_1);
	IDLINE_FAI.Add(IDC_EDT_FAI2_1);
	IDLINE_FAI.Add(IDC_EDT_FAI0_2);
	IDLINE_FAI.Add(IDC_EDT_FAI1_2);
	IDLINE_FAI.Add(IDC_EDT_FAI2_2);
	IDLINE_FAI.Add(IDC_EDT_FAI0_3);
	IDLINE_FAI.Add(IDC_EDT_FAI1_3);
	IDLINE_FAI.Add(IDC_EDT_FAI2_3);
	IDLINE_FAI.Add(IDC_EDT_FAI0_4);
	IDLINE_FAI.Add(IDC_EDT_FAI1_4);
	IDLINE_FAI.Add(IDC_EDT_FAI2_4);
	 

}
void CDlgLoadInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDTHINT_CASE, c_editHint_case);
	DDX_Control(pDX, IDC_EDTHINT_CASE1, c_index_case1);
	DDX_Control(pDX, IDC_EDTHINT_CASE2, c_index_case2);
	DDX_Control(pDX, IDC_EDTHINT_CASE3, c_index_case3);
	DDX_Control(pDX, IDC_EDTHINT_CASE4, c_index_case4);

	DDX_Control(pDX, IDC_EDTHINT_CONLOAD_I1, c_index_conload1);
	DDX_Control(pDX, IDC_EDTHINT_CONLOAD_I2, c_index_conload2);
	DDX_Control(pDX, IDC_EDTHINT_CONLOAD_I3, c_index_conload3);
	DDX_Control(pDX, IDC_EDTHINT_CONLOAD_I4, c_index_conload4);
	DDX_Control(pDX, IDC_EDTHINT_CONLOAD_I5, c_index_conload5);
	DDX_Control(pDX, IDC_EDTHINT_CONLOAD_I6, c_index_conload6);

	DDX_Control(pDX, IDC_EDTHINT_DISLOAD_I1, c_index_dis1);
	DDX_Control(pDX, IDC_EDTHINT_DISLOAD_I2, c_index_dis2);
	DDX_Control(pDX, IDC_EDTHINT_DISLOAD_I3, c_index_dis3);
	DDX_Control(pDX, IDC_EDTHINT_DISLOAD_I4, c_index_dis4);


	DDX_Control(pDX, IDC_EDTHINT_CASE, c_header_case_case);
	DDX_Control(pDX, IDC_EDTHINT_NOTATIO, c_header_case_notatio);
	DDX_Control(pDX, IDC_EDTHINT_DESCRIPTION, c_header_case_description);
	DDX_Control(pDX, IDC_EDTHINT_FAI0, c_header_case_fai0);
	DDX_Control(pDX, IDC_EDTHINT_FAI1, c_header_case_fai1);
	DDX_Control(pDX, IDC_EDTHINT_FAI2, c_header_case_fai2);
	DDX_Control(pDX, IDC_EDTHINT_CONLOAD_I, c_header_con_i);
	DDX_Control(pDX, IDC_EDTHINT_CONLOAD_X, c_header_con_x);
	DDX_Control(pDX, IDC_EDTHINT_CONLOAD_F, c_header_con_f);
	DDX_Control(pDX, IDC_EDTHINT_DISLOAD_I, c_header_dis_i);
	DDX_Control(pDX, IDC_EDTHINT_DISLOAD_X1, c_header_dis_x1);
	DDX_Control(pDX, IDC_EDTHINT_DISLOAD_Q1, c_header_dis_q1);
	DDX_Control(pDX, IDC_EDTHINT_DISLOAD_X2, c_header_dis_x2);
	DDX_Control(pDX, IDC_EDTHINT_DISLOAD_Q2, c_header_dis_q2);

	DDX_Control(pDX, IDC_EDT_NOTATIO1, c_cell_case_notatio1);
	DDX_Control(pDX, IDC_EDT_NOTATIO2, c_cell_case_notatio2);
	DDX_Control(pDX, IDC_EDT_NOTATIO3, c_cell_case_notatio3);
	DDX_Control(pDX, IDC_EDT_NOTATIO4, c_cell_case_notatio4);

	DDX_Control(pDX, IDC_EDT_DESCRIPTION1, c_cell_case_descript1);
	DDX_Control(pDX, IDC_EDT_DESCRIPTION2, c_cell_case_descript2);
	DDX_Control(pDX, IDC_EDT_DESCRIPTION3, c_cell_case_descript3);
	DDX_Control(pDX, IDC_EDT_DESCRIPTION4, c_cell_case_descript4);

	DDX_Control(pDX, IDC_EDT_FAI0_1, c_cell_case_fai0_1);
	DDX_Control(pDX, IDC_EDT_FAI0_2, c_cell_case_fai0_2);
	DDX_Control(pDX, IDC_EDT_FAI0_3, c_cell_case_fai0_3);
	DDX_Control(pDX, IDC_EDT_FAI0_4, c_cell_case_fai0_4);

	DDX_Control(pDX, IDC_EDT_FAI1_1, c_cell_case_fai1_1);
	DDX_Control(pDX, IDC_EDT_FAI1_2, c_cell_case_fai1_2);
	DDX_Control(pDX, IDC_EDT_FAI1_3, c_cell_case_fai1_3);
	DDX_Control(pDX, IDC_EDT_FAI1_4, c_cell_case_fai1_4);

	DDX_Control(pDX, IDC_EDT_FAI2_1, c_cell_case_fai2_1);
	DDX_Control(pDX, IDC_EDT_FAI2_2, c_cell_case_fai2_2);
	DDX_Control(pDX, IDC_EDT_FAI2_3, c_cell_case_fai2_3);
	DDX_Control(pDX, IDC_EDT_FAI2_4, c_cell_case_fai2_4);


	DDX_Control(pDX, IDC_EDT_CONLOAD_X1, c_cell_con_x1);
	DDX_Control(pDX, IDC_EDT_CONLOAD_X2, c_cell_con_x2);
	DDX_Control(pDX, IDC_EDT_CONLOAD_X3, c_cell_con_x3);
	DDX_Control(pDX, IDC_EDT_CONLOAD_X4, c_cell_con_x4);
	DDX_Control(pDX, IDC_EDT_CONLOAD_X5, c_cell_con_x5);
	DDX_Control(pDX, IDC_EDT_CONLOAD_X6, c_cell_con_x6);

	DDX_Control(pDX, IDC_EDT_CONLOAD_F1, c_cell_con_f1);
	DDX_Control(pDX, IDC_EDT_CONLOAD_F2, c_cell_con_f2);
	DDX_Control(pDX, IDC_EDT_CONLOAD_F3, c_cell_con_f3);
	DDX_Control(pDX, IDC_EDT_CONLOAD_F4, c_cell_con_f4);
	DDX_Control(pDX, IDC_EDT_CONLOAD_F5, c_cell_con_f5);
	DDX_Control(pDX, IDC_EDT_CONLOAD_F6, c_cell_con_f6);

	DDX_Control(pDX, IDC_EDT_DISLOAD_X1_1, c_cell_dis_x1_1);
	DDX_Control(pDX, IDC_EDT_DISLOAD_X1_2, c_cell_dis_x1_2);
	DDX_Control(pDX, IDC_EDT_DISLOAD_X1_3, c_cell_dis_x1_3);
	DDX_Control(pDX, IDC_EDT_DISLOAD_X1_4, c_cell_dis_x1_4);

	DDX_Control(pDX, IDC_EDT_DISLOAD_Q1_1, c_cell_dis_q1_1);
	DDX_Control(pDX, IDC_EDT_DISLOAD_Q1_2, c_cell_dis_q1_2);
	DDX_Control(pDX, IDC_EDT_DISLOAD_Q1_3, c_cell_dis_q1_3);
	DDX_Control(pDX, IDC_EDT_DISLOAD_Q1_4, c_cell_dis_q1_4);

	DDX_Control(pDX, IDC_EDT_DISLOAD_X2_1, c_cell_dis_x2_1);
	DDX_Control(pDX, IDC_EDT_DISLOAD_X2_2, c_cell_dis_x2_2);
	DDX_Control(pDX, IDC_EDT_DISLOAD_X2_3, c_cell_dis_x2_3);
	DDX_Control(pDX, IDC_EDT_DISLOAD_X2_4, c_cell_dis_x2_4);

	DDX_Control(pDX, IDC_EDT_DISLOAD_Q2_1, c_cell_dis_q2_1);
	DDX_Control(pDX, IDC_EDT_DISLOAD_Q2_2, c_cell_dis_q2_2);
	DDX_Control(pDX, IDC_EDT_DISLOAD_Q2_3, c_cell_dis_q2_3);
	DDX_Control(pDX, IDC_EDT_DISLOAD_Q2_4, c_cell_dis_q2_4);
	DDX_Control(pDX, IDC_BTN_LOADCASE_ADD, c_CaseAdd);
	DDX_Control(pDX, IDC_BTN_LOADCASE_REMOVE, c_CaseRemove);
	DDX_Control(pDX, IDC_CON_ADD, c_ConAdd);
	DDX_Control(pDX, IDC_CON_REMOVE, c_ConRemove);
	DDX_Control(pDX, IDC_DIS_ADD, c_DisAdd);
	DDX_Control(pDX, IDC_DIS_REMOVE, c_DisRemove);
	DDX_Control(pDX, IDC_EDIT_END_BOTTOM, c_EndForce_Bottom);
	DDX_Control(pDX, IDC_EDIT_END_TOP, c_EndForce_Top);
	DDX_Control(pDX, IDC_EDT_AXIAL_FORCE, c_Axial_Force);
	DDX_Control(pDX, IDC_AREA_DRAW, m_pic);
}


BEGIN_MESSAGE_MAP(CDlgLoadInput, CDialogEx)
	//ON_MESSAGE(EDITMSG_CHANGED,OnEditChange)
	ON_MESSAGE(EDITINDEXMSG_SELECTED,OnEditSelected)
	ON_MESSAGE(EDITMSG_SELECTED,OnEditSelected)
	ON_MESSAGE(EDITMSG_CHANGED,OnEditChange)
	ON_BN_CLICKED(IDC_BTN_LOADCASE_ADD, &CDlgLoadInput::OnBnClickedBtnLoadcaseAdd)
	ON_BN_CLICKED(IDC_BTN_LOADCASE_REMOVE, &CDlgLoadInput::OnBnClickedBtnLoadcaseRemove)
	ON_BN_CLICKED(IDC_CON_ADD, &CDlgLoadInput::OnBnClickedConAdd)
	ON_BN_CLICKED(IDC_CON_REMOVE, &CDlgLoadInput::OnBnClickedConRemove)
	ON_BN_CLICKED(IDC_DIS_ADD, &CDlgLoadInput::OnBnClickedDisAdd)
	ON_BN_CLICKED(IDC_DIS_REMOVE, &CDlgLoadInput::OnBnClickedDisRemove)
 	ON_BN_CLICKED(IDC_RADIO_ZZ, &CDlgLoadInput::OnBnClickedRadioZz)
 	ON_BN_CLICKED(IDC_RADIO_YY, &CDlgLoadInput::OnBnClickedRadioYy)
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	//ON_BN_CLICKED(IDC_BUTTON_TEST_DR, &CDlgLoadInput::OnBnClickedButtonTestDr)
	ON_BN_CLICKED(IDOK, &CDlgLoadInput::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLoadInput 消息处理程序

void CDlgLoadInput::FakeData()
{
	mega_loads mg;
	mg.Notatio = "G";
	mg.Description = "Permanet loads";
	mg.f0 = LOADDLG_NUMBER_NULL;
	mg.f1 = LOADDLG_NUMBER_NULL;
	mg.f2 = LOADDLG_NUMBER_NULL;

	ConLoad con;
	con.F = 10.f;
	con.x = int(m_dcColumnHight/2.0);

	DisLoad dis;
	dis.q1 = 2;
	dis.q2 = 2;
	dis.x1 = 1000;
	if (m_dcColumnHight-2000>0)
	{
		dis.x2 = m_dcColumnHight - 2000;
	}
	else
	{
		dis.x2 = 1500;
	}
	

	mg.ConYY.Add(con);
	mg.DisYY.Add(dis);

	EndLoad end;
	end.Bottom = 0;
	end.Top = 0;
	mg.EndmYY = end;

	end.Bottom = 0;
	end.Top = 0;
	mg.EndmZZ = end;

	mg.AnxialForceYY = 0;
	mg.AnxialForceZZ = 0;


	m_CaseData.Add(mg);



	

}
BOOL CDlgLoadInput::OnInitDialog()
{

	m_InitOnce = false;
	CDialogEx::OnInitDialog();
	m_InitOnce = true;

	OnInitTableHeader();
	OnInitTableIndex();
	InitIndexCtrls();
	InitTableIds();

	if (m_CaseData.GetSize()<=0)
	{
		FakeData();
	}
	

	OnInitShowDataUI();
	//c_editHint_case.SetWindowText("A");
	// TODO:  在此添加额外的初始化

	InvalidatePreview();

	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

int  CDlgLoadInput::FillCaseTableUi()
{
	
	int i;
	int nCase = m_CaseData.GetSize();
	for (i=0;i<nCase;i++)
	{
		ShowCtrlOneTableLine(eTAB_CASE,i,true);
		ValuesOneLine(i,m_CaseData[i],false);
	}
	for (;i<MAX_CASE_COUNT;i++)
	{
		ShowCtrlOneTableLine(eTAB_CASE,i,false);
	}
	return nCase;
}
void CDlgLoadInput::OnInitShowDataUI()
{
	//G Permeanent 必须有
	int nCase = FillCaseTableUi();
	if (nCase<=0)
	{
		m_CurCase = -1;
		return;
	}

	{
		m_CurCase = 0;
		SetTableCtrlOrangeCur(eTAB_CASE,m_CurCase);
		m_CurAxis = eYY; //
		CButton *pBt = (CButton *)GetDlgItem(IDC_RADIO_YY);
		pBt->SetCheck(TRUE);

		c_cell_case_fai0_1.EnableWindow(FALSE);
		c_cell_case_fai1_1.EnableWindow(FALSE);
		c_cell_case_fai2_1.EnableWindow(FALSE);
	}

	if(eCode_US == m_CodeType)
	{
		for(int i=0;i<IDLINE_FAI.GetCount();i++)
		{
			GetDlgItem(IDLINE_FAI[i])->EnableWindow(FALSE);
		}
	}


	if (m_CurCase>=0)
	{
		OnSelectOneCase(m_CurCase,m_CurAxis);
	}
	
}
void CDlgLoadInput::OnInitTableIndex()
{
	c_index_case1.SetWindowText("1");
	c_index_case2.SetWindowText("2");
	c_index_case3.SetWindowText("3");
	c_index_case4.SetWindowText("4");
	c_index_conload1.SetWindowText("1");
	c_index_conload2.SetWindowText("2");
	c_index_conload3.SetWindowText("3");
	c_index_conload4.SetWindowText("4");
	c_index_conload5.SetWindowText("5");
	c_index_conload6.SetWindowText("6");
	c_index_dis1.SetWindowText("1");
	c_index_dis2.SetWindowText("2");
	c_index_dis3.SetWindowText("3");
	c_index_dis4.SetWindowText("4");
}
void CDlgLoadInput::OnInitTableHeader()
{
	c_header_case_case.SetWindowText("Case");
	c_header_case_notatio.SetWindowText("Notatio");
	c_header_case_description.SetWindowText("Description");
	c_header_case_fai0.SetWindowText("Ψ0");
	c_header_case_fai1.SetWindowText("Ψ1");
	c_header_case_fai2.SetWindowText("Ψ2");
	c_header_con_i.SetWindowText("i");
	c_header_con_x.SetWindowText("x(mm)");
	c_header_con_f.SetWindowText("F(kN)");
	c_header_dis_i.SetWindowText("i");
	c_header_dis_x1.SetWindowText("x1(mm)");
	c_header_dis_q1.SetWindowText("q1(kN/m)");
	c_header_dis_x2.SetWindowText("x2(mm)");
	c_header_dis_q2.SetWindowText("q2(kN/m)");
}

void CDlgLoadInput::OnInitLoad()
{
 

}


bool CDlgLoadInput::GetTableOneLineCtrl(int nType,int nLine,CArray<int>& ctrls)
{
	if (eTAB_CASE == nType)
	{
		int nStart = nLine * LINELEN_CASE;
		int nEnd = nStart + LINELEN_CASE;
		for(int i=nStart;i<nEnd;i++)
		{
			ctrls.Add(IDLINE_CASE[i]);
		}	
		return true;
	}
	else if (eTAB_CON == nType)
	{
		int nStart = nLine * LINELEN_CON;
		int nEnd = nStart + LINELEN_CON;
		for(int i=nStart;i<nEnd;i++)
		{
			ctrls.Add(IDLINE_CON[i]);
		}	
		return true;
	}
	else if (eTAB_DIS == nType)
	{
		int nStart = nLine * LINELEN_DIS;
		int nEnd = nStart + LINELEN_DIS;
		for(int i=nStart;i<nEnd;i++)
		{
			ctrls.Add(IDLINE_DIS[i]);
		}	
		return true;
	}

	return false;
}

void CDlgLoadInput::SetTableCtrlOrangeCur(int nType,int nLine)
{
	if (nLine<0)
	{
		return;
	}
	if(eTAB_CASE==nType)
	{
		for (int i=0;i<c_index_CaseList.GetSize();i++)
		{
			c_index_CaseList[i]->SetSelected(false,true);
		}
		c_index_CaseList[nLine]->SetSelected(true,true);
	}
	else if(eTAB_CON == nType)
	{
		for (int i=0;i<c_index_ConList.GetSize();i++)
		{
			c_index_ConList[i]->SetSelected(false,true);
		}
		c_index_ConList[nLine]->SetSelected(true,true);

	}
	else if (eTAB_DIS == nType)
	{
		for (int i=0;i<c_index_DisList.GetSize();i++)
		{
			c_index_DisList[i]->SetSelected(false,true);
		}
		c_index_DisList[nLine]->SetSelected(true,true);
	 
	}
}
LRESULT CDlgLoadInput::OnEditSelected( WPARAM wp,LPARAM lp )
{
	int nRow,nColumn;
	if(InTabCase(wp,nRow,nColumn))
	{
		SetTableCtrlOrangeCur(eTAB_CASE,nRow);

		m_CurCase = nRow;
		OnSelectOneCase(m_CurCase,m_CurAxis);
		m_CurHigh = eTAB_CASE;
		//OnReDrawPreview();
		InvalidatePreview();
	}
	else if(InTabCon(wp,nRow,nColumn))
	{
		SetTableCtrlOrangeCur(eTAB_CON,nRow);
		m_CurCon = nRow;

		m_CurHigh = eTAB_CON;
		//OnReDrawPreview();
		InvalidatePreview();

	}
	else if (InTabDis(wp,nRow,nColumn))
	{
		SetTableCtrlOrangeCur(eTAB_DIS,nRow);
		m_CurDis = nRow;

		m_CurHigh = eTAB_DIS;
		//OnReDrawPreview();
		InvalidatePreview();
	}
	else if (InTabAxial(wp,nRow,nColumn))
	{
		m_CurHigh = eTAB_AXIS;
		InvalidatePreview();

	} 
	else if(InTabEnd(wp,nRow,nColumn))
	{
		m_CurHigh = eTAB_END;
		m_CurEnd = nColumn;
		InvalidatePreview();
	}
	return 0;
} 
void CDlgLoadInput::ChangeMegaDataCase(int nRow,int nColumn,int ID)
{
	mega_loads &ca =  m_CaseData[nRow];
	if (1==nColumn) //
	{
		CString str;
		ValueOneEdit(ID,str,true);
		str.Trim();
		ca.Notatio = str;
	}
	else if (2==nColumn)
	{
		CString str;
		ValueOneEdit(ID,str,true);
		str.Trim();
		ca.Description = str;
	}
	else if (3==nColumn)
	{
		float val;
		ValueOneEdit(ID,val,true);
		ca.f0 = val;
	}
	else if (4==nColumn)
	{
		float val;
		ValueOneEdit(ID,val,true);
		ca.f1 = val;
	}
	else if (5==nColumn)
	{
		float val;
		ValueOneEdit(ID,val,true);
		ca.f2 = val;
	}

}
void CDlgLoadInput::ChangeMegaDataCon(int nRow,int nColumn,int ID)
{
	mega_loads &ca =  m_CaseData[m_CurCase];
	ConLoad *pCon;
	if (eYY == m_CurAxis)
	{
		pCon = &ca.ConYY[nRow];
	}
	else if (eZZ == m_CurAxis)
	{
		pCon = &ca.ConZZ[nRow];
	}
	
	if (1==nColumn) //
	{
		float val;
		ValueOneEdit(ID,val,true);
		pCon->x = val;
	}
	else if (2==nColumn)
	{
		float val;
		ValueOneEdit(ID,val,true);
		pCon->F = val;
	}
	
}
void CDlgLoadInput::ChangeMegaDataDis(int nRow,int nColumn,int ID)
{
	mega_loads &ca =  m_CaseData[m_CurCase];
	DisLoad *pDis;
	if (eYY == m_CurAxis)
	{
		pDis = &ca.DisYY[nRow];
	}
	else if (eZZ == m_CurAxis)
	{
		pDis = &ca.DisZZ[nRow];
	}

	if (1==nColumn) //
	{
		float val;
		ValueOneEdit(ID,val,true);
		pDis->x1 = val;
	}
	else if (2==nColumn)
	{
		float val;
		ValueOneEdit(ID,val,true);
		pDis->q1 = val;
	}
	else if (3==nColumn) //
	{
		float val;
		ValueOneEdit(ID,val,true);
		pDis->x2 = val;
	}
	else if (4==nColumn)
	{
		float val;
		ValueOneEdit(ID,val,true);
		pDis->q2 = val;
	}
	
}
void CDlgLoadInput::ChangeMegaDataEnd(int nRow,int nColumn,int ID)
{
	mega_loads &ca =  m_CaseData[m_CurCase];
	EndLoad *pLoad;
	if (eYY == m_CurAxis)
	{
		pLoad = &ca.EndmYY;
	}
	else if (eZZ == m_CurAxis)
	{
		pLoad = &ca.EndmZZ;
	}

	if (0==nRow) //
	{
		float val;
		ValueOneEdit(ID,val,true);
		pLoad->Bottom = val;
	}
	else if (1==nRow)
	{
		float val;
		ValueOneEdit(ID,val,true);
		pLoad->Top = val;
	}
	 
}
void CDlgLoadInput::ChangeMegaDataAxial(int nRow,int nColumn,int ID)
{
	mega_loads &ca =  m_CaseData[m_CurCase];
	float *pLoadYY;
	float *pLoadZZ;

	pLoadYY = &ca.AnxialForceYY;
	pLoadZZ = &ca.AnxialForceZZ;
	

	float val;
	ValueOneEdit(ID,val,true);
	*pLoadYY = val ;
	*pLoadZZ = val ;
}
LRESULT CDlgLoadInput::OnEditChange(WPARAM wp,LPARAM lp)
{
	int nRow,nColumn;
	if(InTabCase(wp,nRow,nColumn))
	{
		ChangeMegaDataCase(nRow,nColumn,wp);
		//OnReDrawPreview();
		InvalidatePreview();
	}
	else if(InTabCon(wp,nRow,nColumn))
	{
		ChangeMegaDataCon(nRow,nColumn,wp);
		//OnReDrawPreview();
		InvalidatePreview();
	}
	else if (InTabDis(wp,nRow,nColumn))
	{
		ChangeMegaDataDis(nRow,nColumn,wp);
		//OnReDrawPreview();
		InvalidatePreview();
	}
	else if (InTabEnd(wp,nRow,nColumn))
	{
		ChangeMegaDataEnd(nRow,nColumn,wp);
		//OnReDrawPreview();
		InvalidatePreview();
	}
	else if (InTabAxial(wp,nRow,nColumn))
	{
		ChangeMegaDataAxial(nRow,nColumn,wp);
		//OnReDrawPreview();
		InvalidatePreview();
	}


	return 0;
}

void CDlgLoadInput::OnBnClickedBtnLoadcaseAdd()
{
	//增加一个数据
	m_RedrawSwitch = FALSE;

	mega_loads ldcase;
	ldcase.Description="Live loads";
	int iqcases = m_CaseData.GetSize();
	ldcase.Notatio.Format(_T("Q%d"),iqcases);
	ldcase.f0 = 1.f;
	ldcase.f1 = 1.f;
	ldcase.f2 = 1.f;
	m_CaseData.Add(ldcase);

	FillCaseTableUi();

	m_CurCase = m_CaseData.GetSize()-1;
	OnSelectOneCase(m_CurCase,m_CurAxis);

	SetTableCtrlOrangeCur(eTAB_CASE,m_CurCase);

	m_RedrawSwitch = TRUE;
	//OnReDrawPreview();
	InvalidatePreview();
}


void CDlgLoadInput::OnBnClickedBtnLoadcaseRemove()
{
	 m_RedrawSwitch = FALSE;

	 int nRemove = m_CurCase;
	 m_CaseData.RemoveAt(nRemove);

	 FillCaseTableUi();
	 m_CurCase--;
	 OnSelectOneCase(m_CurCase,m_CurAxis);

	 SetTableCtrlOrangeCur(eTAB_CASE,m_CurCase);

	 m_RedrawSwitch = TRUE;
	 //OnReDrawPreview();
	 InvalidatePreview();
}


void CDlgLoadInput::OnBnClickedConAdd()
{
	m_RedrawSwitch = FALSE;


	ConLoad ld;
	int nNewLine=-1;

	CArray<ConLoad,ConLoad> *pLoad;
	if (eYY == m_CurAxis)
	{
		pLoad =& m_CaseData[m_CurCase].ConYY;
	}
	else
	{
		pLoad =& m_CaseData[m_CurCase].ConZZ; 
	}
	nNewLine = pLoad->Add(ld);
	FillConTableUi();

	m_CurCon = nNewLine;
	SetTableCtrlOrangeCur(eTAB_CON,nNewLine);

	freshAddReBtnCon();


	m_RedrawSwitch = TRUE;
	//OnReDrawPreview();
	InvalidatePreview();
 
	
}


void CDlgLoadInput::OnBnClickedConRemove()
{
	m_RedrawSwitch = FALSE;


	CArray<ConLoad,ConLoad> *pLoad;
	if (eYY == m_CurAxis)
	{
		pLoad =& m_CaseData[m_CurCase].ConYY;
	}
	else
	{
		pLoad =& m_CaseData[m_CurCase].ConZZ; 
	}
	pLoad->RemoveAt(m_CurCon);
	FillConTableUi();

	m_CurCon--;
	if (m_CurCon<0&&pLoad->GetSize()>0)
	{
		m_CurCon = 0;
	}
	SetTableCtrlOrangeCur(eTAB_CON,m_CurCon);
	freshAddReBtnCon();


	m_RedrawSwitch = TRUE;
	//OnReDrawPreview();
	InvalidatePreview();
}


void CDlgLoadInput::OnBnClickedDisAdd()
{
	m_RedrawSwitch = FALSE;


	DisLoad ld;
	int nNewLine=-1;

	CArray<DisLoad ,DisLoad> *pLoad;
	if (eYY == m_CurAxis)
	{
		pLoad =& m_CaseData[m_CurCase].DisYY;
	}
	else
	{
		pLoad =& m_CaseData[m_CurCase].DisZZ; 
	}
	nNewLine = pLoad->Add(ld);
	FillDisTableUi();


	m_CurDis = nNewLine;
	SetTableCtrlOrangeCur(eTAB_DIS,nNewLine);
	freshAddReBtnDis();


	m_RedrawSwitch = TRUE;
	//OnReDrawPreview();
	InvalidatePreview();
}


void CDlgLoadInput::OnBnClickedDisRemove()
{

	m_RedrawSwitch = FALSE;

	CArray<DisLoad,DisLoad> *pLoad;
	if (eYY == m_CurAxis)
	{
		pLoad =& m_CaseData[m_CurCase].DisYY;
	}
	else
	{
		pLoad =& m_CaseData[m_CurCase].DisZZ; 
	}
	pLoad->RemoveAt(m_CurDis);
	FillDisTableUi();

	m_CurDis--;
	if (m_CurDis<0&&pLoad->GetSize()>0)
	{
		m_CurDis = 0;
	}
	SetTableCtrlOrangeCur(eTAB_DIS,m_CurDis);
	freshAddReBtnDis();


	m_RedrawSwitch = TRUE;
	//OnReDrawPreview();
	InvalidatePreview();

}

void CDlgLoadInput::ShowCtrlOneTableLine( int nType,int nLine,int nShow )
{
	CArray<int> ctrls;
	GetTableOneLineCtrl(nType,nLine,ctrls);
	for(int i=0;i<ctrls.GetSize();i++)
	{
		if (TRUE == nShow)
		{
			GetDlgItem(ctrls[i])->ShowWindow(SW_SHOW);
		}
		else
		{
			GetDlgItem(ctrls[i])->ShowWindow(SW_HIDE);
		}
		
	}
}

void CDlgLoadInput::ValuesOneLine(int nLine,ConLoad& ldcon ,bool bUpdateData)
{
	CArray<int> ctrls;
	GetTableOneLineCtrl(eTAB_CON,nLine,ctrls);
	int i=0;
	float x;
	float F;
	if (true == bUpdateData)
	{
		ValueOneEdit(ctrls[++i],x,0,bUpdateData);
		ldcon.x = x;
		ValueOneEdit(ctrls[++i],F,0,bUpdateData);
		ldcon.F = F;

	}
	else
	{
		x = ldcon.x ;
		ValueOneEdit(ctrls[++i],x,0,bUpdateData);
		F=ldcon.F;
		ValueOneEdit(ctrls[++i],F,0,bUpdateData);
	}
	return ;
}

void CDlgLoadInput::ValuesOneLine(int nLine,DisLoad& ldDis ,bool bUpdateData)
{
	CArray<int> ctrls;
	GetTableOneLineCtrl(eTAB_DIS,nLine,ctrls);

	float x1,x2;
	float q1,q2;
	int i=0;
	if (true == bUpdateData)
	{
	
		ValueOneEdit(ctrls[++i],x1,0,bUpdateData);
		ldDis.x1 = x1;
		ValueOneEdit(ctrls[++i],q1,0,bUpdateData);
		ldDis.q1 = q1;
		ValueOneEdit(ctrls[++i],x2,0,bUpdateData);
		ldDis.x2 = x2;
		ValueOneEdit(ctrls[++i],q2,0,bUpdateData);
		ldDis.q2 = q2;

	}
	else
	{
		x1=ldDis.x1;
		ValueOneEdit(ctrls[++i],x1,0,bUpdateData);
		q1=ldDis.q1;
		ValueOneEdit(ctrls[++i],q1,0,bUpdateData);
		x2=ldDis.x2;
		ValueOneEdit(ctrls[++i],x2,0,bUpdateData);
		q2=ldDis.q2;
		ValueOneEdit(ctrls[++i],q2,0,bUpdateData);
		
	}
	return ;
}

void CDlgLoadInput::ValuesOneLine(int nLine,mega_loads& ldCase ,bool bUpdateData)
{
	CArray<int> ctrls;
	GetTableOneLineCtrl(eTAB_CASE,nLine,ctrls);
	int i=0;
	CString strNo;
	CString strDes;
	float f1;
	float f2;
	float f3;
	if (true == bUpdateData)
	{
		ValueOneEdit(ctrls[++i],strNo,bUpdateData);
		ldCase.Notatio=strNo;
		ValueOneEdit(ctrls[++i],strDes,bUpdateData);
		ldCase.Description=strDes;
		ValueOneEdit(ctrls[++i],f1,0,bUpdateData);
		ldCase.f0 = f1;
		ValueOneEdit(ctrls[++i],f2,0,bUpdateData);
		ldCase.f1 = f2;
		ValueOneEdit(ctrls[++i],f3,0,bUpdateData);
		ldCase.f2 = f3;

	}
	else
	{
		strNo = ldCase.Notatio;
		ValueOneEdit(ctrls[++i],strNo,bUpdateData);
		strDes = ldCase.Description;
		ValueOneEdit(ctrls[++i],strDes,bUpdateData);
		f1 = ldCase.f0 ;
		ValueOneEdit(ctrls[++i],f1,0,bUpdateData);
		f2 = ldCase.f1 ;
		ValueOneEdit(ctrls[++i],f2,0,bUpdateData);
		f3 = ldCase.f2 ;
		ValueOneEdit(ctrls[++i],f3,0,bUpdateData);
	}
	return ;
}
void CDlgLoadInput::ValuesOneEnd(EndLoad& endVal,bool bUpdateData)
{
	float B;
	float T;
	if (bUpdateData)
	{
		ValueOneEdit(IDC_EDIT_END_BOTTOM,B,0,bUpdateData);
		endVal.Bottom = B;
		ValueOneEdit(IDC_EDIT_END_TOP,T,0,bUpdateData);
		endVal.Top = T;
		 
	}
	else
	{
		B = endVal.Bottom;
		ValueOneEdit(IDC_EDIT_END_BOTTOM,B,0,bUpdateData);
		T = endVal.Top;
		ValueOneEdit(IDC_EDIT_END_TOP,T,0,bUpdateData);
	}
	
}

void CDlgLoadInput::ValuesOneAxial(float& Val,bool bUpdateData)
{
	float Ax;
	if (bUpdateData)
	{
		ValueOneEdit(IDC_EDT_AXIAL_FORCE,Ax,0,bUpdateData);
		Val= Ax;
	}
	else
	{
		Ax = Val;
		ValueOneEdit(IDC_EDT_AXIAL_FORCE,Val,0,bUpdateData);
	}
}
bool CDlgLoadInput::ValueOneEdit( int ID,CString& val,bool bUpdateData )
{
	if(NULL==GetDlgItem(ID))
	{
		return false;
	}

	if (bUpdateData)
	{
		GetDlgItem(ID)->GetWindowText(val);
	}
	else
	{
		GetDlgItem(ID)->SetWindowText(val);
	}
}
bool CDlgLoadInput::ValueOneEdit( int ID,float& val,int nPre,bool bUpdateData )
{
	if(NULL==GetDlgItem(ID))
	{
		return false;
	}
	if (bUpdateData)
	{
		CString strText  ;
		GetDlgItem(ID)->GetWindowText(strText);
		strText.Trim();
		if (strText.IsEmpty())
		{
			val = LOADDLG_NUMBER_NULL;
		}
		else
		{
			val = atof(strText);
		}
		
		return true;
	}
	else
	{
		CString strTextFormat;
		CString strText;

		if (fabs(val-LOADDLG_NUMBER_NULL)<1e-3)
		{
			strText = " ";
		}
		else
		{
			if (nPre>0)
			{
				strTextFormat.Format("%%0.%df",nPre)  ;
				strText.Format(strTextFormat,val);
			}
			else if(0==nPre)
			{
				strTextFormat.Format("%%d",nPre)  ;
				strText.Format(strTextFormat,int(val+0.01));
			}
		}
		
		
		GetDlgItem(ID)->SetWindowText(strText);
		return true;
	}
	return false;
}

int CDlgLoadInput::FillConTableUi()
{
	CArray<ConLoad,ConLoad>  *pCon = nullptr;
	if (eYY == m_CurAxis)
	{
		pCon = &m_CaseData[m_CurCase].ConYY;
	}
	else if (eZZ == m_CurAxis)
	{
		pCon = &m_CaseData[m_CurCase].ConZZ;
	}
		
	int i;
	for (i=0;i<pCon->GetSize();i++)
	{
		ShowCtrlOneTableLine(eTAB_CON,i,true);
		ValuesOneLine(i,pCon->GetAt(i),false);
	}
	for (;i<MAX_CON_COUNT;i++)
	{
		ShowCtrlOneTableLine(eTAB_CON,i,false);
	}
	return pCon->GetSize();
}
int CDlgLoadInput::FillDisTableUi()
{
	CArray<DisLoad,DisLoad > *pDis = nullptr;

	if (eYY == m_CurAxis)
	{
		pDis = &m_CaseData[m_CurCase].DisYY;
	}
	else if (eZZ == m_CurAxis)
	{
		pDis = &m_CaseData[m_CurCase].DisZZ;
	}

	int i;
	for (i=0;i<pDis->GetSize();i++)
	{
		ShowCtrlOneTableLine(eTAB_DIS,i,true);
		ValuesOneLine(i,pDis->GetAt(i),false);
	}
	for (;i<MAX_DIS_COUNT;i++)
	{
		ShowCtrlOneTableLine(eTAB_DIS,i,false);
	}
	return pDis->GetSize();
}

void CDlgLoadInput::freshAddReBtnCase()
{
	if (m_CaseData.GetSize()>0&&m_CurCase!=0)
	{
		c_CaseRemove.EnableWindow(TRUE);
	}
	else
	{
		c_CaseRemove.EnableWindow(FALSE);
	}

	if (m_CaseData.GetSize()<MAX_CASE_COUNT)
	{
		c_CaseAdd.EnableWindow(TRUE);
	}
	else
	{
		c_CaseAdd.EnableWindow(FALSE);
	}
}
void CDlgLoadInput::freshAddReBtnCon()
{
	CArray<ConLoad,ConLoad> *pCon;
	if (eYY == m_CurAxis)
	{
		pCon = &m_CaseData[m_CurCase].ConYY;
	}
	else
	{
		pCon = &m_CaseData[m_CurCase].ConZZ;
	}
	if (pCon->GetSize()>0)
	{
		c_ConRemove.EnableWindow(TRUE);
	}
	else
	{
		c_ConRemove.EnableWindow(FALSE);
	}
	if (pCon->GetSize()<MAX_CON_COUNT)
	{
		c_ConAdd.EnableWindow(TRUE);
	}
	else
	{
		c_ConAdd.EnableWindow(FALSE);
	}
}
void CDlgLoadInput::freshAddReBtnDis()
{
	CArray<DisLoad,DisLoad> *pDis;
	if (eYY == m_CurAxis)
	{
		pDis = &m_CaseData[m_CurCase].DisYY;
	}
	else
	{
		pDis = &m_CaseData[m_CurCase].DisZZ;
	}

	if (pDis->GetSize()>0)
	{
		c_DisRemove.EnableWindow(TRUE);
	}
	else
	{
		c_DisRemove.EnableWindow(FALSE);
	}
	if (pDis->GetSize()<MAX_DIS_COUNT)
	{
		c_DisAdd.EnableWindow(TRUE);
	}
	else
	{
		c_DisAdd.EnableWindow(FALSE);
	}
}
void CDlgLoadInput::freshAddRemoveBtnStatus()
{
	freshAddReBtnCase();
	freshAddReBtnCon();
	freshAddReBtnDis();
}
void CDlgLoadInput::OnSelectOneCase( int nCur,int nAx)
{
	m_RedrawSwitch = FALSE;


	mega_loads& oneCase = m_CaseData[nCur];

	int i=0;
	CArray<ConLoad,ConLoad> * pCon;
	if (eYY == nAx)
	{
		 pCon=&oneCase.ConYY;
	}
	else
	{
		pCon=&oneCase.ConZZ;
	}
	
	for(i=0;i<pCon->GetSize();i++)
	{
		ShowCtrlOneTableLine(eTAB_CON,i,true);
		ValuesOneLine(i,pCon->GetAt(i),false);
	}
	for (;i<MAX_CON_COUNT;i++)
	{
		ShowCtrlOneTableLine(eTAB_CON,i,false);
	}
	if (pCon->GetSize()>0)
	{
		m_CurCon = 0;
		SetTableCtrlOrangeCur(eTAB_CON,0);
	}
	else
	{
		m_CurCon = -1;
	}



	CArray<DisLoad,DisLoad> * pDis;
	if (eYY == nAx)
	{
		pDis=&oneCase.DisYY;
	}
	else
	{
		pDis=&oneCase.DisZZ;
	}


	for(i=0;i<pDis->GetSize();i++)
	{
		ShowCtrlOneTableLine(eTAB_DIS,i,true);
		ValuesOneLine(i,pDis->GetAt(i),false);
	}
	for (;i<MAX_DIS_COUNT;i++)
	{
		ShowCtrlOneTableLine(eTAB_DIS,i,false);
	}
	if (pDis->GetSize()>0)
	{
		m_CurDis = 0;
		SetTableCtrlOrangeCur(eTAB_DIS,0);
	}
	else
	{
		m_CurDis = -1;
	}




	if (eYY == nAx)
	{
		ValuesOneEnd(oneCase.EndmYY,false);
	}
	else
	{
		ValuesOneEnd(oneCase.EndmZZ,false);
	}

	if (eYY == nAx)
	{
		ValuesOneAxial(oneCase.AnxialForceYY,false);
	}
	else
	{
		ValuesOneAxial(oneCase.AnxialForceZZ,false);
	}


	
	freshAddRemoveBtnStatus();

	m_RedrawSwitch = TRUE;
//	OnReDrawPreview();
/*	m_CurCase = nCur;*/
}

void CDlgLoadInput::OnBnClickedRadioZz()
{
	m_CurAxis = eZZ;
	OnSelectOneCase(m_CurCase,m_CurAxis);

}
void CDlgLoadInput::OnBnClickedRadioYy()
{
	m_CurAxis = eYY;
	OnSelectOneCase(m_CurCase,m_CurAxis);
}

void CDlgLoadInput::SetMegaLoad( const CArray<mega_loads>& ld )
{
	m_CaseData.RemoveAll();
	m_CaseData.Append(ld);
}

CArray<mega_loads>& CDlgLoadInput::MegaLoad()
{
	return m_CaseData;
}

void CDlgLoadInput::SetCodeType( int nCode )
{
	m_CodeType = nCode;
}

void CDlgLoadInput::InitPicDc(CDC *dc)
{
	CRect rcPic;
	
	int WinHight = m_dcColumnHight*1.5;
	int WinWid = m_dcColumnWidth*1.5;

	dc->SetMapMode(MM_ISOTROPIC);
	m_pic.GetWindowRect(&rcPic);
	dc->SetViewportExt(rcPic.Width()*m_Scale,-rcPic.Height()*m_Scale);
	dc->SetViewportOrg(rcPic.Width()/2.0,rcPic.Height());
	dc->OffsetViewportOrg(m_XOriPre,m_YOriPre);
	dc->SetWindowExt(WinWid,WinHight);
	dc->SetWindowOrg(0,-WinHight*0.15);

	
}
void CDlgLoadInput::DcDrawColumn(CDC *dc)
{
	InitPicDc(dc);

	Graphics grColumn(dc->m_hDC);
	Gdiplus::Rect rcCol(0,0,m_dcColumnWidth,m_dcColumnHight);

	LinearGradientBrush brColumn(rcCol,
		Color::Blue,Color::Green,LinearGradientModeVertical);
	if (m_bMbuttonDown==FALSE)
	{
		grColumn.FillRectangle(&brColumn,-rcCol.Width/2.0,0,rcCol.Width,rcCol.Height);
	}
	
	Gdiplus::Pen penColumn(Color::Black,2);
	grColumn.DrawRectangle(&penColumn,-rcCol.Width/2.0,0,rcCol.Width,rcCol.Height);
	if (m_bMbuttonDown==FALSE)
	{

		float nArrowLen = m_dcColumnHight*0.18;
		float offsetDim = m_dcColumnHight*0.06;

		DcDimLinear(dc,3,0,rcCol.Height,      offsetDim   ,nArrowLen*1.3,  rcCol.Height);
		//              起点  终点          空白     , 空白 + 实线          标注数字
	}
// 	Graphics gr1(dc->m_hDC);
// 	gr1.DrawLine(&Pen(Color::Red,1),Point(0,0),Point(100,100));
}
void CDlgLoadInput::DcDrawSupport0(CDC *dc,int nPos)
{
	Matrix maDr;
	if (nPos == 1) //0 = 下  1 = 上
	{
		maDr.RotateAt(90,PointF(0,0));
		maDr.Translate(m_dcColumnWidth/2.0,m_dcColumnHight,MatrixOrderAppend);
		
	}
	else
	{
		maDr.RotateAt(90,PointF(0,0));
		maDr.Translate(m_dcColumnWidth/2.0,0.f,MatrixOrderAppend);
	}


	float SupWid = m_dcColumnWidth * 0.6;
	float SupCircle = m_dcColumnWidth *0.08;

	InitPicDc(dc);
	Graphics grSp(dc->m_hDC);

	GraphicsPath pa0;
	RectF rcF(-SupCircle,-SupCircle,2*SupCircle,2*SupCircle);
	pa0.AddEllipse(rcF);
	pa0.Transform(&maDr);
	Region reg0(&pa0);
	grSp.DrawPath(&Pen(Color::Black,2),&pa0);


	if (m_bMbuttonDown==FALSE)
	{
		LinearGradientBrush lgb(Point(-SupWid,-SupWid)
			,Point(SupWid,SupWid),Color::White,Color::White);
		grSp.FillRegion(&lgb,&reg0);
	}

	GraphicsPath pa3;
	pa3.AddLine(0.f,0.f,-SupWid,-SupWid);
	pa3.AddLine(-SupWid,-SupWid,SupWid,-SupWid);
	pa3.AddLine(SupWid,-SupWid,0.f,0.f);
	pa3.Transform(&maDr);

	Region regi(&pa3);
	LinearGradientBrush lgb(Point(-SupWid,-SupWid)
		,Point(SupWid,SupWid),Color::Violet,Color::Gold);

	grSp.DrawPath(&Pen(Color::Black,2),&pa3);
	if (m_bMbuttonDown==FALSE)
	{
		grSp.FillRegion(&lgb,&regi);
	}
	

	GraphicsPath pa4;
	pa4.AddLine(-1.3*SupWid,-SupWid,1.3*SupWid,-SupWid);
	pa4.Transform(&maDr);
	grSp.DrawPath(&Pen(Color::Black,4),&pa4);


}
void CDlgLoadInput::DcDrawSupport1(CDC *dc,int nPos)
{
	Matrix maDr;
	if (nPos == 1)
	{
		maDr.Translate(0,m_dcColumnHight);
		maDr.RotateAt(180,PointF(0,m_dcColumnHight),MatrixOrderAppend);
	}

	InitPicDc(dc);
	Graphics grSp(dc->m_hDC);


	GraphicsPath pa0;
	GraphicsPath pa1;
	GraphicsPath pa2;
	pa0.AddLine(-m_dcColumnWidth*2,0,m_dcColumnWidth*2,0);
	pa0.Transform(&maDr);
	Pen pe(Color::Black,2);
	grSp.DrawPath(&pe,&pa0);

	pa1.AddLine(0,0,-m_dcColumnWidth*0.3,-m_dcColumnWidth*0.3);
	pa2.AddLine(0,0,-m_dcColumnWidth*0.3,-m_dcColumnWidth*0.3);

	Matrix ma1;
	pa1.Transform(&maDr);
	for(int i=0;i<3;i++)
	{
		ma1.Translate(-m_dcColumnWidth*0.3,0);
		pa1.Transform(&ma1);
		grSp.DrawPath(&pe,&pa1);
	}

	Matrix ma2;
	pa2.Transform(&maDr);
	for(int i=0;i<3;i++)
	{
		ma2.Translate(m_dcColumnWidth*0.3,0);
		pa2.Transform(&ma2);
		grSp.DrawPath(&pe,&pa2);
	}
	 

}
 
void CDlgLoadInput::DcLdArrow(CDC *dc,int LoadPos,int loadDimLen,float n1,bool bHighLight)
{
	//  箭头外观
	//    /---------|
	//    \---------|
	float nArrowLen = m_dcColumnHight*0.18;
	float nArrowWid = nArrowLen*0.18;
	float offsetDim = m_dcColumnHight*0.04;
	float fUpDnInter = nArrowWid*1.8;
	Matrix maDr;
	switch(LoadPos)
	{
	case 1: ///左侧
		maDr.RotateAt(180,PointF(0,0));
		maDr.Translate(-m_dcColumnWidth*0.5,loadDimLen,MatrixOrderAppend);
		break;
	case 2: //上侧
		if (n1>0) //向下
		{
			maDr.RotateAt(90,PointF(0,0));
			maDr.Translate(0,m_dcColumnHight+fUpDnInter,MatrixOrderAppend);
		}
		else if (n1<=0) //向上
		{
			maDr.RotateAt(-90,PointF(0,0));
			maDr.Translate(0,m_dcColumnHight+nArrowLen+ fUpDnInter,MatrixOrderAppend);
		}
		break;
	case 3: ///右侧
		maDr.Translate(m_dcColumnWidth*0.5,loadDimLen);
		break;
	case 4: ///下侧
		if (n1>0) //向上
		{
			maDr.RotateAt(-90,PointF(0,0));
			maDr.Translate(0,-fUpDnInter,MatrixOrderAppend);
		}
		else
		{
			maDr.RotateAt(90,PointF(0,0));
			maDr.Translate(0,-nArrowLen-fUpDnInter,MatrixOrderAppend);
		}
		
		break;
	}
	InitPicDc(dc);
	Graphics gr(dc->GetSafeHdc());
	
	GraphicsPath pa;
	pa.AddLine(0.f,0.f,nArrowWid*1.0,nArrowWid*1.0); //      
	pa.AddLine(nArrowWid,nArrowWid,nArrowWid,nArrowWid*0.5); //   
	pa.AddLine(nArrowWid*1.0,nArrowWid*0.5,nArrowLen,nArrowWid*0.5); 
	pa.AddLine(nArrowLen,nArrowWid*0.5,nArrowLen,-nArrowWid*0.5); 

	pa.AddLine(nArrowLen,-nArrowWid*0.5,nArrowWid,-nArrowWid*0.5); 
	pa.AddLine(nArrowWid,-nArrowWid*0.5,nArrowWid,-nArrowWid*1.0); 
	pa.AddLine(nArrowWid,-nArrowWid*1.0,0.f,0.f); 
	pa.Transform(&maDr);

	 
	Region regi(&pa);

	if (m_bMbuttonDown==FALSE)
	{
		switch(LoadPos)
		{
		case 1:
			{
				LinearGradientBrush lgb(Point(nArrowLen,0),Point(0,0),Color::HotPink,Color::HotPink);
				LinearGradientBrush lgb2(Point(nArrowLen,0),Point(0,0),Color::LightGoldenrodYellow,Color::LightGoldenrodYellow);
				if (bHighLight)
				{
					gr.FillRegion(&lgb2,&regi);
				}
				else
				{
					gr.FillRegion(&lgb,&regi);
				}

			}
			break;
		case 2:
			{
				LinearGradientBrush lgb(Point(0,nArrowLen),Point(0,0),Color::HotPink,Color::HotPink);
				LinearGradientBrush lgb2(Point(nArrowLen,0),Point(0,0),Color::LightGoldenrodYellow,Color::LightGoldenrodYellow);
				if (bHighLight)
				{
					gr.FillRegion(&lgb2,&regi);
				}
				else
				{
					gr.FillRegion(&lgb,&regi);
				}
			}
			break;
		case 3:
			{
				LinearGradientBrush lgb(Point(nArrowLen,0),Point(0,0),Color::HotPink,Color::HotPink);
				LinearGradientBrush lgb2(Point(nArrowLen,0),Point(0,0),Color::LightGoldenrodYellow,Color::LightGoldenrodYellow);
				if (bHighLight)
				{
					gr.FillRegion(&lgb2,&regi);
				}
				else
				{
					gr.FillRegion(&lgb,&regi);
				}
			}
			break;
		case 4:
			{
				LinearGradientBrush lgb(Point(0,nArrowLen),Point(0,0),Color::HotPink,Color::HotPink);
				LinearGradientBrush lgb2(Point(nArrowLen,0),Point(0,0),Color::LightGoldenrodYellow,Color::LightGoldenrodYellow);
				if (bHighLight)
				{
					gr.FillRegion(&lgb2,&regi);
				}
				else
				{
					gr.FillRegion(&lgb,&regi);
				}
			}
			break;
		}
	}
	if (bHighLight)
	{
		gr.DrawPath(&Pen(Color::Black,4),&pa);
	}
	else
	{
		gr.DrawPath(&Pen(Color::Black,2),&pa);
	}
	

	if ((LoadPos==1||LoadPos==3)&&m_bMbuttonDown==FALSE)
	{
		DcDimLinear(dc,LoadPos,0,loadDimLen,offsetDim,nArrowLen+offsetDim,loadDimLen);
	}

}
void CDlgLoadInput::DcDimLinear2(CDC *dc,int LoadPos,int loadDimStart,int loadDimLen,int offsetSt ,int offset,float num,float num2) 
{
	DcDimLinear(dc,LoadPos,0,loadDimStart,offsetSt,offset,loadDimStart);
	DcDimLinear(dc,LoadPos,loadDimStart,loadDimLen,offsetSt,offset,loadDimLen);
}


//ZHLEI 2018/03 :
//loadPos = 1 2 3 4 == 左 上 右 下
//             |  |
//             |  |
//offsetSt     |  |
//   *-- offset|  |
//   |         |  |
//   |         |  |
//   |         |  |
//loadDimLen   |  |   num = 标注数字
//   |         |  |
//   |         |  |
//   |         |  |
//   *--       |  |
//loadDimStart |  |
//			   |  |
void CDlgLoadInput::DcDimLinear(CDC *dc,int LoadPos,int loadDimStart,int loadDimLen,int offsetSt ,int offset,float num)
{
	float fBeyond = m_dcColumnHight * 0.02;
	float fthink = m_dcColumnHight * 0.01;
	float FtHight = m_dcColumnHight * 0.05;
	InitPicDc(dc);
	Graphics gr(dc->GetSafeHdc());

	Matrix maDr;
	Matrix maText;
	
	switch(LoadPos)
	{
	case 1: ///左侧
		maDr.RotateAt(90,PointF(0,0));
		maDr.Translate(-m_dcColumnWidth*0.5-offset-offsetSt,loadDimStart,MatrixOrderAppend);


		maText.Scale(1,-1);
		maText.RotateAt(90,PointF(0,0),MatrixOrderAppend);
		maText.Translate(-m_dcColumnWidth*0.5-offset-offsetSt,loadDimStart,MatrixOrderAppend);
		break;
	case 3: ///右侧
		maDr.RotateAt(90,PointF(0,0));
		maDr.Translate(m_dcColumnWidth*0.5+offset+offsetSt,loadDimStart,MatrixOrderAppend);

		maText.Scale(1,-1);
		maText.RotateAt(90,PointF(0,0),MatrixOrderAppend);
		maText.Translate(m_dcColumnWidth*0.5+offset+offsetSt,loadDimStart,MatrixOrderAppend);
		break;
	};
	

	gr.SetTransform(&maDr);
	Pen pe(Color::Black,1);
	Pen pe2(Color::Black,int(fthink));
	GraphicsPath pa0;
	pa0.AddLine(0.0,0.0,loadDimLen,0.0); //水平线
	//pa0.Transform(&maDr);
	gr.DrawPath(&pe,&pa0);
	GraphicsPath pa1;
	if (1 == LoadPos)
	{
		pa1.AddLine(0.0,fBeyond,0.0,(-offsetSt)*1.0);  //尺寸界线1
	}
	else if(3==LoadPos)
	{
		pa1.AddLine(0.0,-fBeyond,0.0,(offsetSt)*1.0);  //尺寸界线1
	}
	gr.DrawPath(&pe,&pa1);
	GraphicsPath pa2;
	if (1==LoadPos)
	{
		pa2.AddLine(loadDimLen*1.0,fBeyond,loadDimLen*1.0,(-offsetSt)*1.0); //尺寸界线2
	}
	else
	{
		pa2.AddLine(loadDimLen*1.0,-fBeyond,loadDimLen*1.0,(offsetSt)*1.0); //尺寸界线2
	}
	gr.DrawPath(&pe,&pa2);
	GraphicsPath pa3; //斜杠
	pa3.AddLine(fBeyond,fBeyond,-fBeyond,-fBeyond);  
	//pa3.Transform(&maDr);
	gr.DrawPath(&pe2,&pa3);
	GraphicsPath pa4; //斜杠
	pa4.AddLine(loadDimLen+fBeyond,fBeyond,loadDimLen-fBeyond,-fBeyond);  
	//pa4.Transform(&maDr);
	gr.DrawPath(&pe2,&pa4);

	FontFamily fontFa(L"Arial");
	Gdiplus::Font fot(&fontFa,FtHight,FontStyleRegular,UnitPixel);
	WCHAR infoString[100]=L"";
	
	InitPicDc(dc);
	Graphics gr2(dc->GetSafeHdc());
	swprintf_s(infoString,100,L"%d",int(num+0.01));
	SolidBrush soldBr(Color::Black);
	gr2.SetTransform(&maText);
 	gr2.DrawString(infoString,wcslen(infoString),&fot,
 		PointF(loadDimLen/2.0-fot.GetHeight(0.f)*(wcslen(infoString)/2),-fot.GetHeight(0.f)),&soldBr);

}
void CDlgLoadInput::DcDim(CDC *dc,int LoadPos,int loadDimStart,int loadDimLen,float num)
{
	InitPicDc(dc);
	Graphics gr(dc->GetSafeHdc());


}
 
void CDlgLoadInput::DcLdM(CDC *dc,int LoadPos,float n1,bool bHighLight)
{
	bool bClock=true;
	if (n1>0)
	{
		bClock = true;
	}
	else
	{
		bClock = false;
	}

	InitPicDc(dc);
	Graphics gr(dc->GetSafeHdc());

	float fRad =  m_dcColumnWidth * 1.8;
	float fthick$2 = m_dcColumnHight * 0.18 *0.18 *0.4;
	float swapAng90 = 90;

	GraphicsPath pa;
	GraphicsPath pa1;
	Region regi1;
	
	{
		RectF rc1(PointF(-fRad+fthick$2,-fRad+fthick$2),
			SizeF(2*fRad-2*fthick$2,2*fRad-2*fthick$2));
		pa.AddArc(rc1,0,swapAng90);

		//pa.AddLine(0.f,fRad+fthick$2,0.f,fRad-fthick$2);

		RectF rc2(PointF(-fRad-fthick$2,-fRad-fthick$2),
			SizeF(2*fRad+2*fthick$2,2*fRad+2*fthick$2));
		pa.AddArc(rc2,swapAng90,-swapAng90);

		Matrix ma;
		if (bClock)
		{
			ma.Translate(-fRad,0);
		}
		else
		{
			ma.Translate(-fRad,0);
			ma.Scale(-1,1,MatrixOrderAppend);
		}
		pa.Transform(&ma);
	}

	{
		pa1.AddLine(fthick$2*2,0.f,-fthick$2*2,0.f);
		pa1.AddLine(-2*fthick$2,0.f,0.f,-2*fthick$2);
		pa1.AddLine(0.f,-2*fthick$2,2*fthick$2,0.f);
		pa1.AddLine(2*fthick$2,0.f,2*fthick$2,0.f);
	}

	//移动对其中点
	Matrix ma2;
	if (bClock)
	{
		ma2.Translate(fRad,0);
		pa.Transform(&ma2);
		pa1.Transform(&ma2);
	}
	else
	{
		ma2.Translate(-fRad,0);
		pa.Transform(&ma2);
		pa1.Transform(&ma2);
	}

	Matrix ma3;
	switch(LoadPos)
	{
	case 2: // 上
		{
			if (bClock)
			{
				ma3.Rotate(45.f);
			}
			else
			{
				ma3.Rotate(-45.f);
			}
			ma3.Translate(0,m_dcColumnHight,MatrixOrderAppend);
		}
		break;
	case 4:
		{
			if (bClock)
			{
				ma3.Rotate(45.f+90.f);
			}
			else
			{
				ma3.Rotate(-45.f-90.f);
			}
			//ma3.Translate(0,m_dcColumnHight,MatrixOrderAppend);
		}
		break;
	}
	pa.Transform(&ma3);
	pa1.Transform(&ma3);

	gr.DrawPath(&Pen(Color::Black,2),&pa);
	if (FALSE == m_bMbuttonDown)
	{
		Region regi(&pa);
		LinearGradientBrush lgb(Point(-1000,-1000)
			,Point(1000,10000),Color::Violet,Color::Violet);
		gr.FillRegion(&lgb,&regi);
	}
	 

	
	gr.DrawPath(&Pen(Color::Black,2),&pa1);
	if (FALSE == m_bMbuttonDown)
	{
		Region regi1(&pa1);
		LinearGradientBrush lgb(Point(-1000,-1000)
			,Point(1000,10000),Color::Violet,Color::Violet);
		gr.FillRegion(&lgb,&regi1);
	}
	
 
}
void CDlgLoadInput::DcLdDis(CDC *dc,int LoadPos,int loadDimStart,int loadDimLen,float n1,float n2,bool bHighLight)
{
	InitPicDc(dc);
	Graphics gr(dc->GetSafeHdc());

	Matrix maDr;
	switch(LoadPos)
	{
	case 1: ///左侧
		maDr.RotateAt(90,PointF(0,0));
		maDr.Translate(-m_dcColumnWidth*0.5,loadDimStart,MatrixOrderAppend);
		break;
	case 3: ///右侧
		maDr.RotateAt(90,PointF(0,0));
		maDr.Translate(-m_dcColumnWidth*0.5,loadDimStart,MatrixOrderAppend);
		maDr.Scale(-1,1,MatrixOrderAppend);
		break;
	}
	float offsetDim = m_dcColumnHight * 0.02;
	float fH1= m_dcColumnHight*0.04;
	float fH2= m_dcColumnHight*0.08;
	float nTstInter = m_dcColumnHight*0.04;
	float nStep = loadDimLen / nTstInter;
	float fHx;
	float fStp;
	if (fabs(n1)>fabs(n2))
	{
		float temp = fH1;
		fH1 = fH2;
		fH2 = temp;
	}
	else if (fabs(n1)<fabs(n2))
	{

	}
	else
	{
		fH2 = fH1;
	}

	if (fabs(n1)<1e-5)
	{
		fH1 = 0;
	}
	if (fabs(n2)<1e-5)
	{
		fH2 = 0;
	}

	if (fabs(n1-n2)<1e-5)
	{
		fH2 = fH1;
		fHx = 0;
		
	}
	else if(fabs(n1)>fabs(n2))
	{
		fHx = -(fH1 - fH2)/nStep*1.0; //高差
	}
	else
	{
		fHx = (fH2 -fH1)/nStep*1.0; //高差
	}
	
	 
	fStp = loadDimLen / nStep ;// 水平单步长
// 	if (1==LoadPos)
// 	{
// 		fStp = fStp;
// 	}
// 	else 
// 	{
// 		fStp = fStp * (-1);
// 	}
	
	
	int i;

	for(i=0;i<=nStep;i++)
	{
		GraphicsPath pa;
		pa.AddLine(0+fStp*i,0.f,0+fStp*i,fH1+fHx*i);
		pa.Transform(&maDr);
		if (false == bHighLight)
		{
			gr.DrawPath(&Pen(Color::BurlyWood,3),&pa);
		}
		else
		{
			gr.DrawPath(&Pen(Color::Blue,3),&pa);
		}
	}

	 
	
	GraphicsPath pa;
	pa.AddLine(0.f,fH1,fStp*(i-1),fH1+fHx*(i-1));
	pa.Transform(&maDr);
	if (false == bHighLight)
	{
		gr.DrawPath(&Pen(Color::BurlyWood,3),&pa);
	}
	else
	{
		gr.DrawPath(&Pen(Color::Blue,3),&pa);
	}


	if ((LoadPos==1||LoadPos==3)&&m_bMbuttonDown==FALSE)
	{
		DcDimLinear2(dc,LoadPos,loadDimStart,loadDimLen,offsetDim,fH2+offsetDim,loadDimStart,loadDimLen);
	}

}


void CDlgLoadInput::SaveBitmap()
{
	CDC* pDc = GetDC();
	HBITMAP hBitmap = NULL;
	if (pDc)
	{

		BITMAPINFO bmi;
		LPBYTE pBits;
		ZeroMemory(&bmi,sizeof(bmi));
		CRect rc;
		m_pic.GetWindowRect(&rc);

		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = rc.Width();
		bmi.bmiHeader.biHeight = rc.Height();
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biCompression = BI_RGB;
		hBitmap = CreateDIBSection(pDc->m_hDC,&bmi,DIB_RGB_COLORS,(void**)&pBits,0,0);

		CDC dcMem;
		dcMem.CreateCompatibleDC(pDc);
		dcMem.SelectObject(hBitmap);


		DrawDc(&dcMem);


		ReleaseDC(pDc);

	}

	if(hBitmap)
	{
		CImage img;
		img.Attach(hBitmap);
		CString strPath;
		GetCurrentDirectory(MAX_PATH,strPath.GetBuffer(MAX_PATH));
		strPath.ReleaseBuffer();
		strPath+= "\\";
		img.Save(strPath+"Load.jpg");
		DeleteObject(hBitmap);
	}

}

void CDlgLoadInput::DrawDc(CDC *dc1)
{
	CDC *dc;

	/*
	int m_dcColumnHight;
	int m_dcColumnWidth;
	*/

	CRect rc;
	m_pic.GetWindowRect(&rc);

	dc = dc1;

	dc->FillSolidRect(0,0,rc.Width(),rc.Height(),RGB(255,255,255));
	DcDrawColumn(dc);

	if (3==GlobalPara::m_DesnPara.Restrict)
	{
		DcDrawSupport0(dc,0);
		DcDrawSupport0(dc,1);
		
	}
	else if (4 ==GlobalPara::m_DesnPara.Restrict)
	{
		DcDrawSupport1(dc,0);
	}
	
	
	

	if (m_CurCase<0||m_CurCase>=m_CaseData.GetSize())
	{
		return ;
	}
	mega_loads &ld = m_CaseData[m_CurCase];

	//集中
	CArray<ConLoad,ConLoad>* conlds;
	if (m_CurAxis==eYY)
	{
		conlds = &ld.ConYY;
	}
	else if(m_CurAxis==eZZ)
	{
		conlds = &ld.ConZZ;
	}
	bool bHighlight=false;//高亮
	for(int i=0;i<conlds->GetSize();i++)
	{
		if (i==m_CurCon&&eTAB_CON==m_CurHigh)
		{
			bHighlight = true;
		}
		else
		{
			bHighlight = false;
		}
		ConLoad oneload = conlds->GetAt(i);
		if (oneload.F>0)
		{
			DcLdArrow(dc,1,oneload.x,oneload.F,bHighlight);
		}
		else if (oneload.F<0)
		{
			DcLdArrow(dc,2,oneload.x,fabs(oneload.F),bHighlight);
		}

	}

	//线性
	CArray<DisLoad,DisLoad>* dislds;
	if (m_CurAxis==eYY)
	{
		dislds = &ld.DisYY;
	}
	else if(m_CurAxis==eZZ)
	{
		dislds = &ld.DisZZ;
	}
	bHighlight=false;
	for(int i=0;i<dislds->GetSize();i++)
	{
		if (i==m_CurDis&&eTAB_DIS==m_CurHigh)
		{
			bHighlight = true;
		}
		else
		{
			bHighlight = false;
		}

		DisLoad oneload = dislds->GetAt(i);
		if (oneload.q1>-1e-5)
		{
			DcLdDis(dc,1,oneload.x1,oneload.x2,oneload.q1,oneload.q2,bHighlight);
		}
		else if (oneload.q1<-1e-5)
		{
			DcLdDis(dc,3,oneload.x1,oneload.x2,oneload.q1,oneload.q2,bHighlight);
		}
	}

	//轴力
	{
		float axLoad;
		if (eYY == m_CurAxis)
		{
			axLoad = ld.AnxialForceYY;
		}
		else if(eZZ == m_CurAxis)
		{
			axLoad = ld.AnxialForceZZ;
		}
		
		if(eTAB_DIS==m_CurHigh)
		{
			bHighlight = true;
		}
		else
		{
			bHighlight = false;
		}
		
		if (false==(fabs(axLoad)<1e-3))
		{
			DcLdArrow(dc,4,0,axLoad,bHighlight);//下部
			DcLdArrow(dc,2,0,axLoad,bHighlight);//上部
		}
			
	}


	
	{
		EndLoad* endm;
		if (m_CurAxis==eYY)
		{
			endm = &ld.EndmYY;
		}
		else if(m_CurAxis==eZZ)
		{
			endm = &ld.EndmZZ;
		}

		if (false == (fabs(endm->Bottom)<1e-3))// == 0
		{
			DcLdM(dc,4,endm->Bottom,true);
		}

		if (false == (fabs(endm->Top)<1e-3))// == 0
		{
			DcLdM(dc,2,endm->Top,true);
		}
	}
	

}

void CDlgLoadInput::InvalidatePreview()
{
	if (FALSE ==  m_RedrawSwitch)
	{
		return;
	}

	CDC *ctrlDc;
	ctrlDc = CDC::FromHandle(::GetDC(m_pic.m_hWnd));
	
	DrawDc(ctrlDc);
	
	ReleaseDC(ctrlDc);
	return;
}
void CDlgLoadInput::OnReDrawPreview2(CDC& dc,CRect& PreRect)
{
	
// 	CBrush br2(RGB(0,0,0));
// 	CRect rc22(0,0,50,50);
// 	dc.FillRect(&rc22,&br2);

	dc.SetMapMode(MM_ISOTROPIC);
// 	dc.SetWindowExt(100,100);
// 	dc.OffsetWindowOrg(m_XOriPre,m_YOriPre);
// 	dc.SetViewportExt(PreRect.Height()*m_Scale,PreRect.Height()*m_Scale);
// 	dc.SetViewportOrg(PreRect.right/2.0,PreRect.bottom/2.0);


// 	CRect rc(-50,-50,50,50);
// 	CPen penRed(PS_DASH,2,RGB(255,0,0));
// 	dc.SelectObject(penRed);
	
// 	Graphics graphics(dc.GetSafeHdc());
// 
// 	
// 	LinearGradientBrush br(Point(-50,50),Point(50,50),Color::Blue,Color::Red);
// 	graphics.FillRectangle(&br,rc.left,rc.top,rc.Width(),rc.Height());



}
void CDlgLoadInput::OnReDrawPreview()
{
	//return ;

	if (FALSE == m_RedrawSwitch)
	{
		return ;
	}
	if (m_CurCase<0||m_CurAxis<0)
	{
		return;
	}

// 	CRect PreRect;
// 	GetDlgItem(IDC_AREA_DRAW)->GetWindowRect(&PreRect);
// 	ScreenToClient(&PreRect);
// 	CDC *pDiaDc=GetDC();
// 	pDiaDc->FillSolidRect(&PreRect,RGB(0,0,0));
// 
// 	//int k1= m_iRadio_Ping+1;
// 	int k1 = 1;
// 	TONWNEX2(k1);
// 
//  	int k2=3;
//  	m_pCfgBas->Chgwnd(k2);
//  	HDC OldDc= m_pCfgBas->Customiz_CFGDC(pDiaDc->GetSafeHdc(),PreRect,TRUE);
// 	//m_pCfgBas->Redrw();
// 
// 	m_pCfgBas->Ersdsp();
// 
// 	int IW=PreRect.Width();
// 	int IH=PreRect.Height();
// 	float RH=(1000*GlobalPara::m_DesnPara.Lens * 1.3)*m_Scale;
// 	float RW = ((IW*1.0 / IH)*RH);
// 	float XO= RH/2.0+ m_XOriPre;
// 	float YO= 200+ m_YOriPre;
// 	m_pCfgBas->Wgrfsizo(IW,IH,RW,RH,XO,YO);
// 	int nHgType=-1,nHgidx=-1;
// 	if (m_CurHigh == eTAB_CASE)
// 	{
// 		nHgType=-1;nHgidx=-1;
// 	}
// 	else if (m_CurHigh == eTAB_CON)
// 	{
// 		nHgType=1;nHgidx=m_CurCon;
// 	}
// 	else if (m_CurHigh == eTAB_DIS)
// 	{
// 		nHgType=2;nHgidx=m_CurDis;
// 	}
// //	GlobalPara::DrawColImp(m_CurCase,m_CurAxis,&m_CaseData,false,0/*m_XOriPre*/,0/*m_YOriPre*/,1/*m_Scale*/,nHgType,nHgidx);
// 	m_pCfgBas->Customiz_CFGDC(OldDc,PreRect,FALSE);
// 	ReleaseDC(pDiaDc);

}

void CDlgLoadInput::OnPaint()
{

	CPaintDC dc(this); // device context for painting
 
	
	
	InvalidatePreview( );
	 
	 
}




BOOL CDlgLoadInput::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bMbuttonDown)
	{
		CRect rc;
		GetDlgItem(IDC_AREA_DRAW)->GetWindowRect(&rc);
		if (rc.PtInRect(pt))
		{
			m_Scale *= float(1.0+0.2*zDelta/abs(zDelta));
			InvalidatePreview();
		}
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}
void CDlgLoadInput::OnMButtonDown(UINT nFlags, CPoint point)
{
	m_bMbuttonDown = TRUE;
	ClientToScreen(&point);
	m_ptPrev = point;
	CDialog::OnMButtonDown(nFlags, point);
}

void CDlgLoadInput::OnMButtonUp( UINT nFlags, CPoint point )
{
	m_bMbuttonDown = FALSE;
	InvalidatePreview();
	CDialog::OnMButtonUp(nFlags, point);
}

void CDlgLoadInput::OnMouseMove(UINT nFlags, CPoint point) 
{

	// TODO: Add your message handler code here and/or call default
	CRect rc;
	GetDlgItem(IDC_AREA_DRAW)->GetWindowRect(&rc);
	ClientToScreen(&point);
	if (rc.PtInRect(point) ) //&& nFlags == MK_LBUTTON)
	{
		if (m_bMbuttonDown)
		{
			m_XOriPre += (point.x-m_ptPrev.x);
			m_YOriPre += (point.y-m_ptPrev.y);
			InvalidatePreview(); 
			CDC *ctrlDc;
			ctrlDc = CDC::FromHandle(::GetDC(m_pic.m_hWnd));
			ctrlDc->OffsetViewportOrg(m_XOriPre,m_YOriPre);
			m_ptPrev = point;
		}
	}
	else
	{
		m_bMbuttonDown=FALSE;
	}
	

	CDialog::OnMouseMove(nFlags, point);
}
// void CDlgLoadInput::DrawPicture( )
// {
// 	InvalidatePreview();
// }

void CDlgLoadInput::OnBnClickedButtonTestDr()
{
	// TODO: 在此添加控件通知处理程序代码
	InvalidatePreview();
}


void CDlgLoadInput::OnBnClickedOk()
{
	SaveBitmap();
	CDialogEx::OnOK();
}
