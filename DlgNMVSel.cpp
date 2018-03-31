// DlgNMVSel.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "DlgNMVSel.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "PluginFun.h"

// CDlgNMVSel 对话框

IMPLEMENT_DYNAMIC(CDlgNMVSel, CDialogEx)

CDlgNMVSel::CDlgNMVSel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgNMVSel::IDD, pParent)
{

}

CDlgNMVSel::~CDlgNMVSel()
{
}

void CDlgNMVSel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_NEILI_TU, c_ListNeiLi);
}


BEGIN_MESSAGE_MAP(CDlgNMVSel, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NEILI_TU, &CDlgNMVSel::OnDblclkListNeiliTu)
END_MESSAGE_MAP()


void CDlgNMVSel::onInitCtrlList()
{
	c_ListNeiLi.DeleteAllItems();
	c_ListNeiLi.InsertColumn(0,"Index",LVCFMT_CENTER,80);
	c_ListNeiLi.InsertColumn(1,"Name",LVCFMT_CENTER,260);
}


// CDlgNMVSel 消息处理程序


BOOL CDlgNMVSel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	onInitCtrlList();
	FillList();
	c_ListNeiLi.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgNMVSel::FillList()
{
	PluginFun::Get().NeiliTuNames().RemoveAll();
	c_ListNeiLi.DeleteAllItems();

	int nCase = Mega_Cases::Get().Cases().GetCount();
	int nCol=2;
	CString strIndex;
	CString strNa;
	CString strdes;
	int nLine=0;
	for (int nCurCase =0;nCurCase<nCase;nCurCase++)
	{
		//ZHLEI 2017/11 :
		strIndex.Format("%0d",nLine+1);
		strdes = Mega_Cases::Get().Cases().GetAt(nCurCase).Description;
		strNa.Format("%s_M(Y-Y)",strdes);
		PluginFun::Get().NeiliTuNames().Add(strNa);

		c_ListNeiLi.InsertItem(nLine,strIndex);
		c_ListNeiLi.SetItemText(nLine,1,strNa);
		nLine++;


		//ZHLEI 2017/11 :
		strIndex.Format("%0d",nLine+1);
		strdes = Mega_Cases::Get().Cases().GetAt(nCurCase).Description;
		strNa.Format("%s_M(Z-Z)",strdes);
		PluginFun::Get().NeiliTuNames().Add(strNa);

		c_ListNeiLi.InsertItem(nLine,strIndex);
		c_ListNeiLi.SetItemText(nLine,1,strNa);
		nLine++;

		//ZHLEI 2017/11 :
		strIndex.Format("%0d",nLine+1);
		strdes = Mega_Cases::Get().Cases().GetAt(nCurCase).Description;
		strNa.Format("%s_V(Y-Y)",strdes);
		PluginFun::Get().NeiliTuNames().Add(strNa);

		c_ListNeiLi.InsertItem(nLine,strIndex);
		c_ListNeiLi.SetItemText(nLine,1,strNa);
		nLine++;

		//ZHLEI 2017/11 :
		strIndex.Format("%0d",nLine+1);
		strdes = Mega_Cases::Get().Cases().GetAt(nCurCase).Description;
		strNa.Format("%s_V(Z-Z)",strdes);
		PluginFun::Get().NeiliTuNames().Add(strNa);

		c_ListNeiLi.InsertItem(nLine,strIndex);
		c_ListNeiLi.SetItemText(nLine,1,strNa);
		nLine++;

		//ZHLEI 2017/11 :
		strIndex.Format("%0d",nLine+1);
		strdes = Mega_Cases::Get().Cases().GetAt(nCurCase).Description;
		strNa.Format("%s_N",strdes);
		PluginFun::Get().NeiliTuNames().Add(strNa);

		c_ListNeiLi.InsertItem(nLine,strIndex);
		c_ListNeiLi.SetItemText(nLine,1,strNa);
		nLine++;
	}
	//附加两个N_M曲线
// 	strIndex.Format("%0d",nLine+1);
// 	strNa.Format("Fiber Model N-M Curve")
// 	c_ListNeiLi.InsertItem(nLine,strIndex);
// 	c_ListNeiLi.SetItemText(nLine,1,strNa);

}

CString CDlgNMVSel::GetSelStr()
{
	return m_selStr;
}


void CDlgNMVSel::OnDblclkListNeiliTu(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nSel = pNMItemActivate->iItem;
	m_selStr = PluginFun::Get().NeiliTuNames()[nSel];
	EndDialog(IDOK);

	*pResult = 0;
}
