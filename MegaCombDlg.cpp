// MegaCombDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "MegaCombDlg.h"
#include "afxdialogex.h"
#include "GlobalPara.h"

const int COLUMN_NO_ = 0; //INDEX
const int COLUMN_G1 = 1;
const int COLUMN_Q1 = 2;
const int COLUMN_G2 = 3;
const int COLUMN_Q2 = 4;
const int COLUMN_Beta=5; 


// MegaCombDlg 对话框

IMPLEMENT_DYNAMIC(MegaCombDlg, CDialog)

MegaCombDlg::MegaCombDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MegaCombDlg::IDD, pParent)
	, m_checkautobeta(FALSE)
{
	//{{AFX_DATA_INIT(MegaCombDlg)
	//}}AFX_DATA_INIT
	m_iClickColum = -1;
	//  m_gsup = 0.0f;
	m_rginf = 0.0f;
	m_rgsup = 0.0f;
	m_rq = 0.0f;
	m_rq22 = 0.0f;
	m_rginf2 = 0.0f;
}

MegaCombDlg::~MegaCombDlg()
{
}

void MegaCombDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMB_LIST, m_ObjectList);
	DDX_Control(pDX, IDC_EDIT_LOADCOMB_DATA, m_editWnd);
	DDX_Text(pDX, IDC_rGinf, m_rginf);
	DDX_Text(pDX, IDC_rGSup, m_rgsup);
	DDX_Text(pDX, IDC_rQ, m_rq);
	DDX_Text(pDX, IDC_rQ22, m_rq22);
	DDX_Text(pDX, IDC_rGinf2, m_rginf2);
	DDX_Check(pDX, IDC_CHECK_beta, m_checkautobeta);
}


BEGIN_MESSAGE_MAP(MegaCombDlg, CDialog)
	ON_BN_CLICKED(IDC_AUTOGEN, &MegaCombDlg::OnBnClickedAutogen)
	ON_BN_CLICKED(IDC_ADD, &MegaCombDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_REMOVE, &MegaCombDlg::OnBnClickedRemove)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_COMB_LIST, OnItemchangedLISTDeadLoad)
	ON_EN_KILLFOCUS(IDC_EDIT_LOADCOMB_DATA, &MegaCombDlg::OnEnKillfocusEditListwnd)
	ON_NOTIFY(NM_CLICK, IDC_COMB_LIST, &MegaCombDlg::OnClickList)
	ON_BN_CLICKED(IDOK, &MegaCombDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MegaCombDlg::OnBnClickedCancel)
	ON_EN_KILLFOCUS(IDC_rGSup, &MegaCombDlg::OnEnKillfocusrgsup)
	ON_EN_KILLFOCUS(IDC_rQ, &MegaCombDlg::OnEnKillfocusrq)
	ON_EN_KILLFOCUS(IDC_rGinf, &MegaCombDlg::OnEnKillfocusrginf)
	ON_EN_KILLFOCUS(IDC_rQ22, &MegaCombDlg::OnEnKillfocusrq22)
	ON_EN_KILLFOCUS(IDC_rGinf2, &MegaCombDlg::OnEnKillfocusrginf2)
END_MESSAGE_MAP()

BOOL MegaCombDlg::OnInitDialog() 
{
	// TODO: Add extra initialization here
	CDialog::OnInitDialog();

	if(GlobalPara::m_DesnPara.CodeType==3){	//中国规范
		GetDlgItem(IDC_PARA_Ginf2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_EQ)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_rGinf2)->ShowWindow(SW_SHOW);
	}
	SetList1();
	if(GlobalPara::m_DesnPara.f[0][0]>0){
		m_ObjectList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
		SetList1Item(m_ObjectList);
	}
	else{
		AutoGenCombi();
		m_ObjectList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
		SetList1Item(m_ObjectList);
	}
	m_rginf = GlobalPara::m_DesnPara.rGinf;
	m_rginf2= GlobalPara::m_DesnPara.rGinf2;
	m_rgsup = GlobalPara::m_DesnPara.rGsup;
	m_rq    = GlobalPara::m_DesnPara.rQ1;
	m_rq22   = GlobalPara::m_DesnPara.rQ2;
	UpdateData(FALSE);

	EditEnds();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void MegaCombDlg::AutoGenCombi()
{
	CombForce_ Comb1;
	float f[4][Max_Combines]={0.f};
	int ncombi = 0;
	int n_Loads = GlobalPara::LoadCaseData.GetSize();
	float G1 = GlobalPara::m_DesnPara.rGsup;
	float G2 = GlobalPara::m_DesnPara.rGinf;
	float G3 = GlobalPara::m_DesnPara.rGinf2;
	float Q1 = GlobalPara::m_DesnPara.rQ1;
	float Q2 = GlobalPara::m_DesnPara.rQ2;
	float ffq[4] = {0.f};
	float ctrlf[4] = {0.f};
	int ctrls = 0;
	memset(&GlobalPara::m_DesnPara.f,0,sizeof(GlobalPara::m_DesnPara.f));
	for(int i=1;i<GlobalPara::LoadCaseData.GetSize();i++)
	{
		ffq[i] = GlobalPara::LoadCaseData[i].f0;
		ctrlf[i] = 1.f;
		ctrls++;
	}
	if(GlobalPara::m_DesnPara.CodeType==1)//欧洲
	{		
		//活1控制
			//1
		int ncombs = 0;
		f[0][ncombs]=G1;
		f[1][ncombs]=Q1*ctrlf[1];
		f[2][ncombs]=0.f;
		f[3][ncombs]=0.f;
		ncombs++;

		f[0][ncombs]=G2;
		f[1][ncombs]=Q1*ctrlf[1];
		f[2][ncombs]=0.f;
		f[3][ncombs]=0.f;
		ncombs++;
			//1+2
		if(ctrls>1){
		f[0][ncombs]=G1;
		f[1][ncombs]=Q1*ctrlf[1];
		f[2][ncombs]=Q1*ffq[2]*ctrlf[2];
		f[3][ncombs]=0.f;
		ncombs++;
		f[0][ncombs]=G2;
		f[1][ncombs]=Q1*ctrlf[1];
		f[2][ncombs]=Q1*ffq[2]*ctrlf[2];
		f[3][ncombs]=0.f;
		ncombs++;
		}
			//1+3
		if(ctrls>2){
		f[0][ncombs]=G1;
		f[1][ncombs]=Q1*ctrlf[1];
		f[2][ncombs]=0.f;
		f[3][ncombs]=Q1*ffq[3]*ctrlf[3];
		ncombs++;
		f[0][ncombs]=G2;
		f[1][ncombs]=Q1*ctrlf[1];
		f[2][ncombs]=0.f;
		f[3][ncombs]=Q1*ffq[3]*ctrlf[3];
		ncombs++;
		}
		//活2控制
			//2
		if(ctrls>1){
		f[0][ncombs]=G1;
		f[1][ncombs]=0;
		f[2][ncombs]=Q1*ctrlf[2];
		f[3][ncombs]=0.f;
		ncombs++;

		f[0][ncombs]=G2;
		f[1][ncombs]=0;
		f[2][ncombs]=Q1*ctrlf[2];
		f[3][ncombs]=0.f;
		ncombs++;
			//2+1
		f[0][ncombs]=G1;
		f[1][ncombs]=Q1*ffq[1]*ctrlf[1];
		f[2][ncombs]=Q1*ctrlf[2];
		f[3][ncombs]=0.f;
		ncombs++;

		f[0][ncombs]=G2;
		f[1][ncombs]=Q1*ffq[1]*ctrlf[1];
		f[2][ncombs]=Q1*ctrlf[2]*ctrlf[2];
		f[3][ncombs]=0;
		ncombs++;
			//2+3
		if(ctrls>2){
		f[0][ncombs]=G1;
		f[1][ncombs]=0;
		f[2][ncombs]=Q1*ctrlf[2];
		f[3][ncombs]=Q1*ffq[3]*ctrlf[3];
		ncombs++;

		f[0][ncombs]=G2;
		f[1][ncombs]=0;
		f[2][ncombs]=Q1*ctrlf[2];
		f[3][ncombs]=Q1*ffq[3]*ctrlf[3];
		ncombs++;
		}
		}
		//活3控制
			//3
		if(ctrls>2){
		f[0][ncombs]=G1;
		f[1][ncombs]=0;
		f[2][ncombs]=0;
		f[3][ncombs]=Q1*ctrlf[3];
		ncombs++;

		f[0][ncombs]=G2;
		f[1][ncombs]=0;
		f[2][ncombs]=0;
		f[3][ncombs]=Q1*ctrlf[3];	
		ncombs++;
			//3+1
		f[0][ncombs]=G1;
		f[1][ncombs]=Q1*ffq[1]*ctrlf[1];
		f[2][ncombs]=0;
		f[3][ncombs]=Q1*ctrlf[3];
		ncombs++;

		f[0][ncombs]=G2;
		f[1][ncombs]=Q1*ffq[1]*ctrlf[1];
		f[2][ncombs]=0;
		f[3][ncombs]=Q1*ctrlf[3];
		ncombs++;
			//3+2
		f[0][ncombs]=G1;
		f[1][ncombs]=0;
		f[2][ncombs]=Q1*ffq[2]*ctrlf[2];
		f[3][ncombs]=Q1*ctrlf[3];
		ncombs++;

		f[0][ncombs]=G2;
		f[1][ncombs]=0;
		f[2][ncombs]=Q1*ffq[2]*ctrlf[2];
		f[3][ncombs]=Q1*ctrlf[3];
		ncombs++;
		}
		GlobalPara::m_DesnPara.n_Combines =ncombs;

		//G1恒+Q1活1+Q1*ffq[2]*活2+Q1*ffq[3]*活3
// 		f[0][0]=G1;
// 		f[1][0]=Q1;
// 		f[2][0]=Q1*ffq[2];
// 		f[3][0]=Q1*ffq[3];
// 		//1.35恒+1.5*ffq[1]活1+1.5活2+1.5*ffq[3]*活3
// 		f[0][1]=1.35;
// 		f[1][1]=1.5*ffq[1];
// 		f[2][1]=1.5;
// 		f[3][1]=1.5*ffq[3];
// 		//1.35恒+1.5*ffq[1]活1+1.5*ffq[2]*活2+1.5活3
// 		f[0][2]=1.35;
// 		f[1][2]=1.5*ffq[1];
// 		f[2][2]=1.5*ffq[2];
// 		f[3][2]=1.5;
// 		//G2恒+Q2活1+Q2*ffq[2]*活2+Q2*ffq[3]*活3
// 		f[0][3]=G2;
// 		f[1][3]=Q2;
// 		f[2][3]=Q2*ffq[2];
// 		f[3][3]=Q2*ffq[3];
// 		//1.0恒+1.3*ffq[1]活1+1.3活2+1.3*ffq[3]*活3
// 		f[0][4]=1.0;
// 		f[1][4]=1.3*ffq[1];
// 		f[2][4]=1.3;
// 		f[3][4]=1.3*ffq[3];
// 		//1.0恒+1.3*ffq[1]活1+1.3*ffq[2]*活2+1.3活3
// 		f[0][5]=1.0;
// 		f[1][5]=1.3*ffq[1];
// 		f[2][5]=1.3*ffq[2];
// 		f[3][5]=1.3;
	}
	else if(GlobalPara::m_DesnPara.CodeType==2)//美国
	{	
		GlobalPara::m_DesnPara.n_Combines =2;
		//G1恒
		f[0][0]=G1;
		f[1][0]=0;
		f[2][0]=0;
		f[3][0]=0;
		//G2恒+1.6*ffq[1]活1+1.6*ffq[2]活2+1.6*ffq[3]活3
		f[0][1]=G2;
		f[1][1]=1.6*ffq[1];
		f[2][1]=1.6*ffq[2];
		f[3][1]=1.6*ffq[3];
	}
	else if(GlobalPara::m_DesnPara.CodeType==3)//中国
	{
		GlobalPara::m_DesnPara.n_Combines =7;
		//G1(1.35)恒+1.4*ffq[1]*活1+1.4*ffq[2]*活2+1.4*ffq[3]*活3
		f[0][0]=G1*1.35;
		f[1][0]=1.4*ffq[1];
		f[2][0]=1.4*ffq[2];
		f[3][0]=1.4*ffq[3];
		//G2(1.2)恒+1.4活1+1.4*ffq[2]*活2+1.4*ffq[3]*活3
		f[0][1]=G2*1.2;
		f[1][1]=1.4*ffq[1];
		f[2][1]=1.4*ffq[2];
		f[3][1]=1.4*ffq[3];
		//1.2恒+1.4*ffq[1]*活1+1.4活2+1.4*ffq[3]*活3
		f[0][2]=1.2;
		f[1][2]=1.4*ffq[1];
		f[2][2]=1.4;
		f[3][2]=1.4*ffq[3];
		//1.2恒+1.4*ffq[1]*活1+1.4*ffq[2]*活2+1.4活3
		f[0][3]=1.2;
		f[1][3]=1.4*ffq[1];
		f[2][3]=1.4*ffq[2];
		f[3][3]=1.4;
		//G3(1.0)恒+1.4活1+1.4*ffq[2]*活2+1.4*ffq[3]*活3
		f[0][4]=G3;
		f[1][4]=1.4;
		f[2][4]=1.4*ffq[2];
		f[3][4]=1.4*ffq[3];
		//1.0恒+1.4*ffq[1]*活1+1.4活2+1.4*ffq[3]*活3
		f[0][5]=1.0;
		f[1][5]=1.4*ffq[1];
		f[2][5]=1.4;
		f[3][5]=1.4*ffq[3];
		//1.0恒+1.4*ffq[1]*活1+1.4*ffq[2]*活2+1.4活3
		f[0][6]=1.0;
		f[1][6]=1.4*ffq[1];
		f[2][6]=1.4*ffq[2];
		f[3][6]=1.4;
	}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<GlobalPara::m_DesnPara.n_Combines;j++)
		{
			GlobalPara::m_DesnPara.f[i][j]=f[i][j];
		}
	}
	int nRow = GlobalPara::m_DesnPara.n_Combines;
	aryDesnComb.RemoveAll();
	for (int i=0;i<nRow;i++)
	{
		Comb1.DeadPara =GlobalPara::m_DesnPara.f[0][i];
		Comb1.LivePara1=GlobalPara::m_DesnPara.f[1][i];
		Comb1.LivePara2=GlobalPara::m_DesnPara.f[2][i];
		Comb1.LivePara3=GlobalPara::m_DesnPara.f[3][i];
		aryDesnComb.Add(Comb1);
	}
}


void MegaCombDlg::OnBnClickedAutogen()
{
	// TODO: 在此添加控件通知处理程序代码
	AutoGenCombi();
	m_ObjectList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	//SetList1();
	SetList1Item(m_ObjectList);
	UpdateData(FALSE);
}

void MegaCombDlg::OnItemchangedLISTDeadLoad(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	UpdateData(true);
	i_DeadP_CurSel = pNMListView->iItem;

	*pResult = 0;
}

void MegaCombDlg::SetList1()
{
	//int nFormat = LVCFMT_CENTER;

	////////////////////////////////////////////////////////
	int i;
	LPCTSTR LSTR[6]={"No.","G1","Q1","Q2","Q3","Beta"};
	int div_w[6] = {50,70,70,70,70,70};
	m_ObjectList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	for (i = 0; i < 6; i++) {
		m_ObjectList.InsertColumn(i,LSTR[i],LVCFMT_LEFT,div_w[i],-1 );	
	}
}

void MegaCombDlg::SetList1Item(CListCtrl &list)
{
	int J,i,nCol,Cur=0;
	CString str[50];
	list.DeleteAllItems();
	int nRow = GlobalPara::m_DesnPara.n_Combines;
	for (J=0;J<nRow;J++)
	{
		str[ 0].Format("%d"  ,J+1);
		str[ 1].Format("%.2f",GlobalPara::m_DesnPara.f[0][J]);
		str[ 2].Format("%.2f",GlobalPara::m_DesnPara.f[1][J]);
		str[ 3].Format("%.2f",GlobalPara::m_DesnPara.f[2][J]);
		str[ 4].Format("%.2f",GlobalPara::m_DesnPara.f[3][J]);
		str[ 5].Format("%.2f",GlobalPara::m_DesnPara.combbeta[J]);
		nCol=6;
		for (i=0;i<nCol;i++)
			if (i==0)
				list.InsertItem(J,str[i]);
			else
				list.SetItemText(J,i,str[i]);
	}
	list.SetSelectionMark(Cur);
	list.SetItemState(Cur,LVIS_SELECTED,LVIS_SELECTED);

	UpdateData(FALSE);
	return;
}

void MegaCombDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码 aryDesnComb
	CombForce_ Comb1;
	Comb1.DeadPara=1.0;//临时 等待张工的表格修改数值
	Comb1.LivePara1=1.0;
	Comb1.LivePara2=1.0;
	Comb1.LivePara3=1.0;
	aryDesnComb.Add(Comb1);
	memset(&GlobalPara::m_DesnPara.f,0,sizeof(GlobalPara::m_DesnPara.f));
	for (int i=0;i<aryDesnComb.GetSize();i++)
	{
		GlobalPara::m_DesnPara.f[0][i]=aryDesnComb[i].DeadPara;
		GlobalPara::m_DesnPara.f[1][i]=aryDesnComb[i].LivePara1;
		GlobalPara::m_DesnPara.f[2][i]=aryDesnComb[i].LivePara2;
		GlobalPara::m_DesnPara.f[3][i]=aryDesnComb[i].LivePara3;
	}
	GlobalPara::m_DesnPara.n_Combines=aryDesnComb.GetSize();
	//SetList1();
	SetList1Item(m_ObjectList);
	UpdateData(FALSE);
}


void MegaCombDlg::OnBnClickedRemove()
{
	// TODO: 在此添加控件通知处理程序代码
	if (i_DeadP_CurSel<0||i_DeadP_CurSel==0&&aryDesnComb.GetSize()<=0) return;
	aryDesnComb.RemoveAt(i_DeadP_CurSel);
	memset(&GlobalPara::m_DesnPara.f,0,sizeof(GlobalPara::m_DesnPara.f));
	for (int i=0;i<aryDesnComb.GetSize();i++)
	{
		GlobalPara::m_DesnPara.f[0][i]=aryDesnComb[i].DeadPara;
		GlobalPara::m_DesnPara.f[1][i]=aryDesnComb[i].LivePara1;
		GlobalPara::m_DesnPara.f[2][i]=aryDesnComb[i].LivePara2;
		GlobalPara::m_DesnPara.f[3][i]=aryDesnComb[i].LivePara3;
	}
	GlobalPara::m_DesnPara.n_Combines=aryDesnComb.GetSize();
	//SetList1();
	SetList1Item(m_ObjectList);
	UpdateData(FALSE);
}

bool MegaCombDlg::EditStarts()
{
	EditEnds();

	m_loseFocusFrom = KILLFOCUS_NULL;

	int nRow = m_ObjectList.GetNextItem(-1,LVIS_SELECTED);


	CString strHot = m_ObjectList.GetItemText(nRow,m_iClickColum);

	CRect rc;
	m_ObjectList.GetSubItemRect(nRow,m_iClickColum,LVIR_LABEL,rc);
	m_ObjectList.ClientToScreen(&rc);
	this->ScreenToClient(&rc);
// 	m_editWnd.Create(WS_VISIBLE|WS_CHILD|WS_BORDER|ES_CENTER|ES_AUTOHSCROLL,
// 		rc,this,IDC_EDIT_LOADCOMB_DATA);
	m_editWnd.SetWindowPos(NULL,rc.left,rc.top,rc.Width(),rc.Height(),SWP_SHOWWINDOW);
	m_editWnd.ShowWindow(SW_SHOW);
	m_editWnd.SetFont(this->GetFont());
	strHot.MakeUpper();
	m_editWnd.SetWindowText(strHot);

	m_editWnd.SetFocus();
	m_editWnd.SetSel(0,-1,TRUE);

	m_iBeingEdit = nRow; 

	return true;
}

bool MegaCombDlg::EditEnds( )
{
	m_editWnd.ShowWindow(SW_HIDE);
	//m_iLastEdit = m_iBeingEdit;
	m_iBeingEdit = -1;

	return true;
}
void MegaCombDlg::OnClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMItemActivate!=NULL)
	{
		if (pNMItemActivate->iItem>=0&&pNMItemActivate->iItem<m_ObjectList.GetItemCount())
		{
			int &nColumClick  =  pNMItemActivate->iSubItem;
			if(COLUMN_G1 == nColumClick
				||COLUMN_Q1 == nColumClick
				||COLUMN_G2 == nColumClick
				||COLUMN_Q2 == nColumClick
				||COLUMN_Beta==nColumClick) //快捷键
			{
				int nRow = m_ObjectList.GetNextItem(-1,LVIS_SELECTED);
				CString str = m_ObjectList.GetItemText(nRow,nColumClick);
				m_iClickColum = nColumClick;
				EditStarts();
			}
		}
		
	}
	*pResult = 0;
}

void MegaCombDlg::OnEnKillfocusEditListwnd()
{
	// TODO: 在此添加控件通知处理程序代码
	if ((KILLFOCUS_ESC!=m_loseFocusFrom&&KILLFOCUS_OK!=m_loseFocusFrom))
		//KILL_NULL 和  KILLFOCUS_OTHER 进入
	{
		if (KILLFOCUS_NULL == m_loseFocusFrom) //通过单击别处直接进来的  
		{
			m_loseFocusFrom = KILLFOCUS_OTHER;//咱没有用途
			//框还没有被删除
			CString str;
			CString strVal;
	 
			m_editWnd.GetWindowText(str);
			str.MakeUpper();
			strVal =m_ObjectList.GetItemText(m_iBeingEdit,m_iClickColum);
			if (0==str.CompareNoCase(strVal))
			{
				EditSaveText();
				EditEnds();
			}
			else
			{
				EditSaveText();
				EditEnds();
			}
		}
		return;
	}
	else //KILLFOCUS_ESC or KILLFOCUS_OK 
	{
		//已经决定过了 所以不再保存
		EditEnds();
		return;
	}
	return;
}

bool MegaCombDlg::EditSaveText()
{
	CString strEdit;
	CString strCmd;
	if (m_editWnd.GetSafeHwnd())
	{
		m_editWnd.GetWindowText(strEdit);
		strEdit.Trim();
		m_ObjectList.SetItemText(m_iBeingEdit,m_iClickColum,strEdit); 
	}
	return true;
	
}


void MegaCombDlg::OnBnClickedOk()
{
	int nID = GetFocus()->GetDlgCtrlID();

	if (m_iBeingEdit!=-1)
	{
		//判断是否占用
		if (m_editWnd.GetSafeHwnd())
		{
			m_loseFocusFrom = KILLFOCUS_OK;

			CString strTxt;
			m_editWnd.GetWindowText(strTxt);
			strTxt.MakeUpper();
			CString strlist;
			strlist = m_ObjectList.GetItemText(m_iBeingEdit,m_iClickColum);
			if (0==strlist.CompareNoCase(strTxt))//如果没有任何改动直接 killforus
			{
				EditEnds();
				return;
			}
			else
			{
				EditSaveText();
				EditEnds();
				return;
			}

		}
	}
	else
	{
		EditEnds();
		//写回结构
		UpdateData();
		if(m_checkautobeta)
			GlobalPara::m_DesnPara.EC_beta = -1;
		else
			GlobalPara::m_DesnPara.EC_beta = 1;
		GetlistItem();
		__super::OnOK();
	}
}


void MegaCombDlg::OnBnClickedCancel()
{
	if (m_iBeingEdit!=-1)
	{
		m_loseFocusFrom = KILLFOCUS_ESC;
		EditEnds();
		return;
	}
	else
	{
		EditEnds();
		__super::OnCancel();
	}
}


void MegaCombDlg::OnEnKillfocusrgsup()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	GlobalPara::m_DesnPara.rGsup = m_rgsup;
}


void MegaCombDlg::OnEnKillfocusrq()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	GlobalPara::m_DesnPara.rQ1 = m_rq;
}


void MegaCombDlg::OnEnKillfocusrginf()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	GlobalPara::m_DesnPara.rGinf = m_rginf;
}


void MegaCombDlg::OnEnKillfocusrq22()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	GlobalPara::m_DesnPara.rQ2 = m_rq22;
}


void MegaCombDlg::OnEnKillfocusrginf2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	GlobalPara::m_DesnPara.rGinf2 = m_rginf2;
}

void MegaCombDlg::GetlistItem()
{
	int nRow = GlobalPara::m_DesnPara.n_Combines;
	for (int i=0;i<nRow;i++)
	{
		for(int j=1;j<6;j++){
			CString tempchar = m_ObjectList.GetItemText(i,j);
			float val = atof(tempchar);
			if(j<5)
				GlobalPara::m_DesnPara.f[j-1][i] = val;
			else
				GlobalPara::m_DesnPara.combbeta[i] = val;
		}
	}

}