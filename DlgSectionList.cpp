// DlgSectionList.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "DlgSectionList.h"
#include "afxdialogex.h"
#include "steellib.h"
#include "SectionReader.h"
#include "resource.h"

extern "C" __declspec( dllexport )  void __stdcall STS_SECT_FOR_EURO(SECTION1 &SECT,short gSect[1200])
{
	CDlgSectionList dlg;
	if(IDOK == dlg.DoModal())
	{
		int nKd,nSel;
		dlg.GetResult(nKd,nSel);
		int nBegin,nEnd;
		CSectKeeper::Get().TypeBeginEnd(nKd,nBegin,nEnd);
		nSel = nSel + nBegin;

		struct HE_  hh = CSectKeeper::Get().steelC().HE[nSel];
		SECT.K = 2;
		SECT.B = short(hh.tw);
		SECT.H = short(hh.H);
		SECT.U = short(hh.B);
		SECT.D = short(hh.B);
		SECT.F = short(hh.tf);
		SECT.T = short(hh.tf);
//		SECT.L = short(hh.tw);
		SECT.M = 5;
		memcpy(SECT.NAME,hh.NAME,sizeof(char)*16);
	}
}

extern "C" __declspec( dllexport )  void __stdcall SET_PRO_FY(float &Fy)
{
	GlobalPara::Pro_Fy = Fy;
}

extern "C" __declspec( dllexport )  void __stdcall SET_BAR_FY(int &Fy)
{
	GlobalPara::Bar_Fy = Fy;
}


///////////////////////////////////////////////////////////////////////////
CSectTableInfoColumn::CSectTableInfoColumn(CString name, int format, int width)
{
	m_Name=name;
	m_nFormat=format;
	m_nWidth=width;
}

CSectTableInfoColumn::CSectTableInfoColumn()
{

}

CSectTableInfoColumn::~CSectTableInfoColumn()
{

}
///////////////////////////////////////////////////////////////////////
void CSectTableInfo::Add( CString name, int nFormat, int nWidth )
{
	m_Column.Add(CSectTableInfoColumn(name,nFormat,nWidth));
}

void CSectTableInfo::InitListCtrl( CListCtrl& list,int sel )
{
	BOOL flag;
	int i;
	for (;;){
		flag=list.DeleteColumn(0);
		if (!flag) break;
	}
	list.DeleteAllItems();
	m_nCol=m_Column.GetSize();
	for (i=0;i<m_nCol;i++)
		list.InsertColumn(i,m_Column[i].m_Name,
		m_Column[i].m_nFormat,
		m_Column[i].m_nWidth);
}

CSectTableInfo::CSectTableInfo()
{

}

CSectTableInfo::~CSectTableInfo()
{

}

/////////////////////////////////////////////////////////////////
// CDlgSectionList 对话框
IMPLEMENT_DYNAMIC(CDlgSectionList, CDialogEx)

CDlgSectionList::CDlgSectionList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSectionList::IDD, pParent)
{
	 
}

CDlgSectionList::~CDlgSectionList()
{
}

void CDlgSectionList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_R, c_ListR);
	DDX_Control(pDX, IDC_TREE_L, c_treeL);
}


BEGIN_MESSAGE_MAP(CDlgSectionList, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_L, &CDlgSectionList::OnSelchangedTreeL)
	ON_BN_CLICKED(IDOK, &CDlgSectionList::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LIST_R, &CDlgSectionList::OnNMClickListR)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_R, &CDlgSectionList::OnNMDblclkListR)
END_MESSAGE_MAP()

void CDlgSectionList::InitLTreeListInfo()
{
	int nFormat = LVCFMT_CENTER;

	for (int i=0;i<HEINFO::Get().TYPECOUNT;i++)
	{
		m_TabInfo[i].m_TabName=HEINFO::Get().NAMES[i];
		m_TabInfo[i].Add("Type"      ,nFormat,80);
		m_TabInfo[i].Add("g(kg/m)"   ,nFormat,80);
		m_TabInfo[i].Add("h(mm)"     ,nFormat,80);
		m_TabInfo[i].Add("b(mm)"     ,nFormat,80);
		m_TabInfo[i].Add("tw(mm)"    ,nFormat,80);
		m_TabInfo[i].Add("tf(mm)"    ,nFormat,80);
		m_TabInfo[i].Add("r(mm)"     ,nFormat,80);

		m_TabInfo[i].Add("A(cm2)"    ,nFormat,80);
		m_TabInfo[i].Add("hi(mm)"    ,nFormat,80);
		m_TabInfo[i].Add("d(mm)"     ,nFormat,80);
		m_TabInfo[i].Add("φ"        ,nFormat,80);
		m_TabInfo[i].Add("Pmin(mm)"  ,nFormat,80);
		m_TabInfo[i].Add("Pmax(mm)"  ,nFormat,80);
		m_TabInfo[i].Add("AL(m2/m)"  ,nFormat,80);
		m_TabInfo[i].Add("AG(m2/t)"  ,nFormat,80);

		m_TabInfo[i].Add("Iy(cm4)"   ,nFormat,80);
		m_TabInfo[i].Add("Wy(cm3)"   ,nFormat,80);
		m_TabInfo[i].Add("Wpl,y(cm3)",nFormat,80);
		m_TabInfo[i].Add("ix(cm)"   ,nFormat,80);
		m_TabInfo[i].Add("Avz(cm3)"  ,nFormat,80);

		m_TabInfo[i].Add("Iz(cm4)"   ,nFormat,80);
		m_TabInfo[i].Add("Wz(cm3)"   ,nFormat,80);
		m_TabInfo[i].Add("Wpl,z(cm3)",nFormat,80);
		m_TabInfo[i].Add("iz(cm)"    ,nFormat,80);

		m_TabInfo[i].Add("Ss(mm)"    ,nFormat,80);
		m_TabInfo[i].Add("It(cm4)"   ,nFormat,80);
		m_TabInfo[i].Add("Iw*1E-3(cm6)",nFormat,100);

		m_TabInfo[i].Add("S235W"     ,nFormat,80);
		m_TabInfo[i].Add("S355W"     ,nFormat,80);
		m_TabInfo[i].Add("S460W"     ,nFormat,80);

		m_TabInfo[i].Add("S235Y"     ,nFormat,80);
		m_TabInfo[i].Add("S355Y"     ,nFormat,80);
		m_TabInfo[i].Add("S460Y"     ,nFormat,80);

		m_TabInfo[i].Add("HISTAR"    ,nFormat,80);
	}
	
}

void CDlgSectionList::FillListR(int nCurType,int nCurSel ,bool updateDateMember)
{
	c_ListR.DeleteAllItems();
	m_TabInfo[nCurType].InitListCtrl(c_ListR,m_CurType);//初始化标头

	SetItemListR(nCurType,true); // 设置每行数据
	c_ListR.SetSelectionMark(nCurSel); //设置选中
	c_ListR.SetItemState(nCurSel,LVIS_SELECTED,LVIS_SELECTED);
	if (updateDateMember)
	{
		m_CurType = nCurType;
	}
	
}

BOOL CDlgSectionList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CSectKeeper::Get().read();

	InitLTreeListInfo();//初始化TabInfo;

	c_ListR.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_FULLROWSELECT);
	OnInitImage();

	FillTreeL();
	FillListR(HEINFO::Get().eIPE,0,true);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgSectionList::SetItemListR(int sel,bool updateDateMember)
{
	STEEL *pSteelC = &CSectKeeper::Get().steelC();
	CString str[50];
	int nCol=34;
	int nBegin=0;
	int nEnd=0;
	CSectKeeper::Get().TypeBeginEnd(sel,nBegin,nEnd);
	int nCurLine=0;
	for (int J=nBegin;J<nEnd;J++,nCurLine++)
	{
		str[ 0].Format("%s"  ,pSteelC->HE[J].NAME );
		str[ 1].Format("%.1f",pSteelC->HE[J].W    );
		str[ 2].Format("%d"  ,pSteelC->HE[J].H    );
		str[ 3].Format("%d"  ,pSteelC->HE[J].B    );
		str[ 4].Format("%.1f",pSteelC->HE[J].tw   );
		str[ 5].Format("%.1f",pSteelC->HE[J].tf   );
		str[ 6].Format("%.0f",pSteelC->HE[J].r    );
		str[ 7].Format("%.2f",pSteelC->HE[J].A    );
		str[ 8].Format("%d"  ,pSteelC->HE[J].hi   );
		str[ 9].Format("%d"  ,pSteelC->HE[J].d    );
		str[10].Format("M%d" ,pSteelC->HE[J].BD   );
		str[11].Format("%d"  ,pSteelC->HE[J].Pmin1);
		str[12].Format("%d"  ,pSteelC->HE[J].Pmax );
		str[13].Format("%.3f",pSteelC->HE[J].AL   );
		str[14].Format("%.2f",pSteelC->HE[J].AG   );
		str[15].Format("%.1f",pSteelC->HE[J].Iy   );
		str[16].Format("%.2f",pSteelC->HE[J].Wy   );
		str[17].Format("%.2f",pSteelC->HE[J].Wply );
		str[18].Format("%.2f",pSteelC->HE[J].Iy1  );
		str[19].Format("%.2f",pSteelC->HE[J].Avz  );
		str[20].Format("%.2f",pSteelC->HE[J].Iz   );
		str[21].Format("%.2f",pSteelC->HE[J].Wz   );
		str[22].Format("%.2f",pSteelC->HE[J].Wplz );
		str[23].Format("%.2f",pSteelC->HE[J].Iz1  );
		str[24].Format("%.1f",pSteelC->HE[J].Ss   );
		str[25].Format("%.2f",pSteelC->HE[J].It   );
		str[26].Format("%.2f",pSteelC->HE[J].Iw   );
		str[27].Format("%d"  ,pSteelC->HE[J].S235w);
		str[28].Format("%d"  ,pSteelC->HE[J].S355w);
		str[29].Format("%d"  ,pSteelC->HE[J].S460w);
		str[30].Format("%d"  ,pSteelC->HE[J].S235y);
		str[31].Format("%d"  ,pSteelC->HE[J].S355y);
		str[32].Format("%d"  ,pSteelC->HE[J].S460y);
		str[33].Format("%d"  ,pSteelC->HE[J].HISTAR);
		
		for (int K=0;K<nCol;K++)
		{
			if (K==0)
			{	
				c_ListR.InsertItem(nCurLine,str[K]);
			}
			else
			{	
				c_ListR.SetItemText(nCurLine,K,str[K]);
			}
		}
	}
	 m_CurSel = sel;
}





bool CDlgSectionList::OnInitImage() 
{
	m_treeicons.Create(16,16,ILC_COLOR24|ILC_MASK,1,2);
	const int nNumImage = 1;
	HICON icos[nNumImage];
	icos[0] = AfxGetApp()->LoadIcon(IDI_ICO_HE);
	
	for(int i=0;i<nNumImage;i++)
	{
		m_treeicons.Add(icos[i]);
	}
	c_treeL.SetImageList(&m_treeicons,LVSIL_NORMAL);

	return true;

}

bool CDlgSectionList::FillTreeL()
{
	int i=-1;
	int nIco = -1;
	int lval = -1;
	int nStr = 0;
	HTREEITEM hPar=0;

	nIco = 0;
	HTREEITEM ht;
	for(int i=0;i<HEINFO::Get().TYPECOUNT;i++)
	{
		ht = c_treeL.InsertItem(m_TabInfo[i].m_TabName,nIco,nIco,TVI_ROOT);
		c_treeL.SetItemData(ht,i);
	}
	return true;
}


void CDlgSectionList::OnSelchangedTreeL(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	HTREEITEM nItem = pNMTreeView->itemNew.hItem;
	DWORD dw = c_treeL.GetItemData(nItem);
	int nType = dw;
	int nSel = 0;
	FillListR(nType,nSel,true);

	*pResult = 0;
}


void CDlgSectionList::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CDlgSectionList::GetResult( int &Kd,int& sel )
{
	Kd = m_CurType;
	sel= m_CurSel;
}


void CDlgSectionList::OnNMClickListR(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate!=NULL)
	{
		int nRow = c_ListR.GetNextItem(-1,LVIS_SELECTED);
		m_CurSel = nRow;
	}
	*pResult = 0;
}




void CDlgSectionList::OnNMDblclkListR(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate!=NULL)
	{
		int nRow = c_ListR.GetNextItem(-1,LVIS_SELECTED);
		m_CurSel = nRow;

		OnOK();
	}
	*pResult = 0;
}
