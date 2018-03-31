#pragma once
#include "afxwin.h"
#include "EditTableHeader.h"
#include "MsgMacroHeader.h "
#include "EditTableCell.h"

// CDlgLoadInput 对话框

class CDlgLoadInput : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLoadInput)

	enum
	{
		eTAB_CASE = 1,
		eTAB_CON = 2,
		eTAB_DIS = 3,
		eTAB_END = 4,
		eTAB_AXIS = 5
	};

	enum
	{
		eYY = 0,
		eZZ = 1
	};

	enum
	{
		eCode_Euro=1,
		eCode_US,
		eCode_CHINA
	};
public:
	CDlgLoadInput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLoadInput();

// 对话框数据
	enum { IDD = IDD_LOAD_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg LRESULT OnEditChange(WPARAM wp,LPARAM lp);
	afx_msg LRESULT OnEditSelected(WPARAM wp,LPARAM lp);
	DECLARE_MESSAGE_MAP()

	bool m_InitOnce;
	CArray<mega_loads> m_CaseData;
	int m_CurHigh;
	int m_CurCase;
	int m_CurCon;
	int m_CurDis;
	int m_CurAxis;
	int m_CurEnd;
	int m_CodeType;
	int m_RedrawSwitch;
	//int m_CurAxis;
public:
	virtual BOOL OnInitDialog();
	void OnInitShowDataUI();
	void OnInitTableIndex();
	void OnInitTableHeader();
	void OnInitLoad();
	void InitTableIds();
	bool InTabCase(int id,int& nRow,int& nColumn);
	bool InTabCon(int id,int& nRow,int& nColumn);
	bool InTabDis(int id,int& nRow,int& nColumn);
	bool InTabEnd(int id,int& nRow,int& nColumn);
	bool InTabAxial(int id,int& nRow,int& nColumn);
	void InitIndexCtrls();

	void ShowCtrlOneTableLine(int nType,int nLine,int nShow);

	void FakeData();

	void OnSelectOneCase(int nCur,int nAx);
	void SetCodeType(int nCode);
	void SetMegaLoad(const CArray<mega_loads>& ld);
	CArray<mega_loads>& MegaLoad();
public:
// 	int m_nLoadCaseZ;
// 	int m_nLoadCaseY;
// 	CArray<mega_loads,mega_loads> m_CaseZ[4];
// 	CArray<mega_loads,mega_loads> m_CaseY[4];

private:
	static const int LINELEN_CASE;
	static const int LINELEN_CON;
	static const int LINELEN_DIS;

	static const int MAX_CASE_COUNT;
	static const int MAX_CON_COUNT;
	static const int MAX_DIS_COUNT;

	CArray<int> IDLINE_CASE;
	CArray<int> IDLINE_CON;
	CArray<int> IDLINE_DIS;
	CArray<int> IDLINE_END;
	CArray<int> IDLINE_AXIAL;
	CArray<int> IDLINE_FAI;

	CArray<CEditTableIndex*> c_index_CaseList;
	CArray<CEditTableIndex*> c_index_DisList;
	CArray<CEditTableIndex*> c_index_ConList;

public:
	//CEditTableIndex c_editHint_case;
	CEditTableIndex c_index_case1;
	CEditTableIndex c_index_case2;
	CEditTableIndex c_index_case3;
	CEditTableIndex c_index_case4;
	CEditTableIndex c_index_conload1;
	CEditTableIndex c_index_conload2;
	CEditTableIndex c_index_conload3;
	CEditTableIndex c_index_conload4;
	CEditTableIndex c_index_conload5;
	CEditTableIndex c_index_conload6;
	CEditTableIndex c_index_dis1;
	CEditTableIndex c_index_dis2;
	CEditTableIndex c_index_dis3;
	CEditTableIndex c_index_dis4;

	CEdit c_header_case_case;
	CEdit c_header_case_notatio;
	CEdit c_header_case_description;
	CEdit c_header_case_fai0;
	CEdit c_header_case_fai1;
	CEdit c_header_case_fai2;
	CEdit c_header_con_i;
	CEdit c_header_con_x;
	CEdit c_header_con_f;
	CEdit c_header_dis_i;
	CEdit c_header_dis_x1;
	CEdit c_header_dis_q1;
	CEdit c_header_dis_x2;
	CEdit c_header_dis_q2;



	CEditTableCell c_cell_case_notatio1;
	CEditTableCell c_cell_case_notatio2;
	CEditTableCell c_cell_case_notatio3;
	CEditTableCell c_cell_case_notatio4;

	CEditTableCell c_cell_case_descript1;
	CEditTableCell c_cell_case_descript2;
	CEditTableCell c_cell_case_descript3;
	CEditTableCell c_cell_case_descript4;

	CEditTableCell c_cell_case_fai0_1;
	CEditTableCell c_cell_case_fai0_2;
	CEditTableCell c_cell_case_fai0_3;
	CEditTableCell c_cell_case_fai0_4;

	CEditTableCell c_cell_case_fai1_1;
	CEditTableCell c_cell_case_fai1_2;
	CEditTableCell c_cell_case_fai1_3;
	CEditTableCell c_cell_case_fai1_4;

	CEditTableCell c_cell_case_fai2_1;
	CEditTableCell c_cell_case_fai2_2;
	CEditTableCell c_cell_case_fai2_3;
	CEditTableCell c_cell_case_fai2_4;

	CEditTableCell c_cell_con_x1;
	CEditTableCell c_cell_con_x2;
	CEditTableCell c_cell_con_x3;
	CEditTableCell c_cell_con_x4;
	CEditTableCell c_cell_con_x5;
	CEditTableCell c_cell_con_x6;

	CEditTableCell c_cell_con_f1;
	CEditTableCell c_cell_con_f2;
	CEditTableCell c_cell_con_f3;
	CEditTableCell c_cell_con_f4;
	CEditTableCell c_cell_con_f5;
	CEditTableCell c_cell_con_f6;

	CEditTableCell c_cell_dis_x1_1;
	CEditTableCell c_cell_dis_x1_2;
	CEditTableCell c_cell_dis_x1_3;
	CEditTableCell c_cell_dis_x1_4;
	
	CEditTableCell c_cell_dis_q1_1;
	CEditTableCell c_cell_dis_q1_2;
	CEditTableCell c_cell_dis_q1_3;
	CEditTableCell c_cell_dis_q1_4;

	CEditTableCell c_cell_dis_x2_1;
	CEditTableCell c_cell_dis_x2_2;
	CEditTableCell c_cell_dis_x2_3;
	CEditTableCell c_cell_dis_x2_4;

	CEditTableCell c_cell_dis_q2_1;
	CEditTableCell c_cell_dis_q2_2;
	CEditTableCell c_cell_dis_q2_3;
	CEditTableCell c_cell_dis_q2_4;
	afx_msg void OnBnClickedBtnLoadcaseAdd();
	afx_msg void OnBnClickedBtnLoadcaseRemove();
	afx_msg void OnBnClickedConAdd();
	afx_msg void OnBnClickedConRemove();
	afx_msg void OnBnClickedDisAdd();
	afx_msg void OnBnClickedDisRemove();
	bool GetTableOneLineCtrl(int nType,int nLine,CArray<int>& ctrls);
	void ValuesOneLine(int nLine,ConLoad& ldcon ,bool bUpdateData);
	void ValuesOneLine(int nLine,DisLoad& ldDis ,bool bUpdateData);
	void ValuesOneLine(int nLine,mega_loads& ldCase ,bool bUpdateData);
	void ValuesOneEnd(EndLoad& endVal,bool bUpdateData);
	void ValuesOneAxial(float& Val,bool bUpdateData);

	bool ValueOneEdit(int ID,float& val,int nPre=2,bool bUpdateData=true);
	bool ValueOneEdit( int ID,CString& val,bool bUpdateData );
	void SetTableCtrlOrangeCur(int nType,int nLine);
	
	
	afx_msg void OnBnClickedRadioZz();
	afx_msg void OnBnClickedRadioYy();
	int FillCaseTableUi();
	int FillConTableUi();
	int FillDisTableUi();
	void freshAddRemoveBtnStatus();
	void freshAddReBtnCase();
	void freshAddReBtnCon();
	void freshAddReBtnDis();
	void ChangeMegaDataCase(int nRow,int nColumn,int ID);
	void ChangeMegaDataCon(int nRow,int nColumn,int ID);
	void ChangeMegaDataDis(int nRow,int nColumn,int ID);
	void ChangeMegaDataEnd(int nRow,int nColumn,int ID);
	void ChangeMegaDataAxial(int nRow,int nColumn,int ID);
	void OnReDrawPreview();
	void OnReDrawPreview2(CDC& dc,CRect& PreRect);

	CButton c_CaseAdd;
	CButton c_CaseRemove;
	CButton c_ConAdd;
	CButton c_ConRemove;
	CButton c_DisAdd;
	CButton c_DisRemove;

	CEditTableCell c_EndForce_Bottom;
	CEditTableCell c_EndForce_Top;
	CEditTableCell c_Axial_Force;



	afx_msg void OnPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//void DrawPicture( );
	BOOL m_bMbuttonDown;
	float m_Scale,m_XOriPre,m_YOriPre;
	CPoint m_ptPrev;


// 	float m_hM;//预览移动
// 	float m_hS;//预览比例
	void InvalidatePreview();
	ULONG_PTR gidplusToken;


	CStatic m_pic;
	afx_msg void OnBnClickedButtonTestDr();
	void InitPicDc(CDC *dc);
	void DcDrawColumn(CDC *dc);
	void DcDrawSupport1(CDC *dc,int nPos);
	void DcDrawSupport0(CDC *dc,int nPos);

	void DcLdArrow(CDC *dc,int LoadPos,int loadDimLen,float n1,bool bHighLight);
	void DcLdDis(CDC *dc,int LoadPos,int loadDimStart,int loadDimLen,float n1,float n2,bool bHighLight);
	void DcLdM(CDC *dc,int LoadPos,float n1,bool bHighLight);

	void DcDimLinear(CDC *dc,int LoadPos,int loadDimStart,int loadDimLen,int offsetSt ,int offset,float num);
	void DcDimLinear2(CDC *dc,int LoadPos,int loadDimStart,int loadDimLen,int offsetSt ,int offset,float num,float num2);

	void DcDim(CDC *dc,int LoadPos,int loadDimStart,int loadDimLen,float num);
	void SaveBitmap();
	void DrawDc(CDC *dc);
	int m_dcColumnHight;
	int m_dcColumnWidth;

	afx_msg void OnBnClickedOk();
};
