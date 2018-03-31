// ConBenGou.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "ConBenGou.h"
#include "afxdialogex.h"
#include "Tools.h"


// ConBenGou 对话框

IMPLEMENT_DYNAMIC(ConBenGou, CDialog)

ConBenGou::ConBenGou(CWnd* pParent /*=NULL*/)
	: CDialog(ConBenGou::IDD, pParent)
	, m_grade(0)
{

	m_ec = 0.0f;
	m_qc = 0.0f;
}

ConBenGou::~ConBenGou()
{
}

void ConBenGou::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CON_LIST, m_con_list);
	DDX_Control(pDX, IDC_CURVE, m_draw);
	DDX_Text(pDX, IDC_ec, m_ec);
	DDX_Text(pDX, IDC_qc, m_qc);
//	DDX_Text(pDX, IDC_CON_GRADE, m_grade);
	DDX_Control(pDX, IDC_COMBO_GRADE, m_comb_grade);
}


BEGIN_MESSAGE_MAP(ConBenGou, CDialog)
	ON_BN_CLICKED(IDOK, &ConBenGou::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ConBenGou::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CON_LIST, &ConBenGou::OnLvnItemchangedConList)
	ON_NOTIFY(NM_CLICK,IDC_CON_LIST,&ConBenGou::OnNMClickConlist)
	ON_BN_CLICKED(IDC_Change, &ConBenGou::OnBnClickedChange)
	ON_BN_CLICKED(IDC_Cal, &ConBenGou::OnBnClickedCal)
	ON_CBN_SELCHANGE(IDC_COMBO_GRADE, &ConBenGou::OnCbnSelchangeComboGrade)
END_MESSAGE_MAP()


// ConBenGou 消息处理程序


void ConBenGou::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveBitmap();
	memcpy(GlobalPara::m_DesnPara.con_e,e1,sizeof(e1));
	memcpy(GlobalPara::m_DesnPara.con_f,f1,sizeof(f1));
	CDialog::OnOK();
}


void ConBenGou::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

void ConBenGou::DrawDc(CDC *dc1,CRect& rc)
{
	CDC *pDc = dc1;
	float cx = rc.right;
	float cy = rc.bottom;
	float cx_table = cx*0.1;
	float cy_table = cy*0.2;
	float table_width = cx*0.8;
	float table_height = cy*0.7;
	float width_step = table_width/8;
	float height_step = table_height/8;
	float Max_f=0.f;
	//获得最大的应力
	for(int i=0;i<26;i++){
		if(GlobalPara::m_DesnPara.con_f[i]>Max_f)
			Max_f = GlobalPara::m_DesnPara.con_f[i];
	}
	//最大应力整数化
	for(int i=0;i<10;i++){
		if(Max_f>i*10 && Max_f<(i+1)*10){
			Max_f = (i+1)*10;
			break;
		}
	}

	
	//填充白色
	CBrush brush;					
	brush.CreateSolidBrush(RGB(255,255,255));	
	pDc->FillRect(&rc,&brush);

	CPen pen(PS_SOLID,1,RGB(200,200,200));	//网格
	CPen pen2(PS_SOLID,2,RGB(150,150,150));	//坐标
	CPen pen3(PS_SOLID,2,RGB(91,155,213));		//曲线
	CPen pen4(PS_SOLID,1,RGB(0,0,0));		//文字
	//	CPen* pOldPen = pDc->SelectObject(&pen);
	CPen* pOldPen = pDc->SelectObject(&pen2);
	pDc->MoveTo(cx_table,cy_table);
	pDc->LineTo(cx_table,cy_table+table_height);
	pDc->LineTo(cx_table+table_width,cy_table+table_height);
	pDc->SelectObject(&pen);
	for(int i=0;i<8;i++){
		pDc->MoveTo(cx_table,cy_table+i*height_step);
		pDc->LineTo(cx_table+table_width,cy_table+i*height_step);
		pDc->MoveTo(cx_table+(i+1)*width_step,cy_table);
		pDc->LineTo(cx_table+(i+1)*width_step,cy_table+table_height);
	}
	//画曲线
	float drawratio = Max_f/8;
	CBrush brush2;
	brush2.CreateSolidBrush(RGB(91,155,213));
	pDc->SelectObject(&pen3);
	CRect point(cx_table-3,cy_table+table_height+3,cx_table+3,cy_table+table_height-3);
	pDc->FillRect(&point,&brush2);
	for(int i=0;i<25;i++){
		float x0 = cx_table+e1[i]*10000*width_step/5;
		float y0 = cy_table+table_height-f1[i]*height_step/drawratio;
		pDc->MoveTo(x0,y0);
		float x1 = cx_table+e1[i+1]*10000*width_step/5;
		float y1 = cy_table+table_height-f1[i+1]*height_step/drawratio;
		point.SetRect(x1-3,y1+3,x1+3,y1-3);
		pDc->FillRect(&point,&brush2);
		pDc->LineTo(x1,y1);
	}

	pDc->SelectObject(&pen4);
	CFont font;
	font.CreatePointFont(80,"Arial");
	LOGFONT lf;
	(pDc->GetCurrentFont())->GetLogFont(&lf);
	int fonth = lf.lfHeight;
	int fontb = lf.lfWidth;
	CFont *pOldFont =pDc->SelectObject(&font);
	//	CString ycod[9]={"0","5","10","15","20","25","30","35","40"};
	CString ycod[9];
	for(int i=0;i<9;i++){
		ycod[i].Format(_T("%.2f"),i*drawratio);
	}
	CString xcod[9]={"0","0.0005","0.0010","0.0015","0.0020","0.0025","0.0030","0.0035","0.0040"};
	for(int i=0;i<9;i++){
		int str_len = xcod[i].GetLength();
		float x_cod = cx_table+i*width_step-str_len*fontb*0.5;
		float y_cod = cy_table+table_height+2;
		pDc->TextOut(x_cod,y_cod,xcod[i]);
	}
	//标注字符
	float tx_cod = cx_table+table_width+fontb*2;
	float ty_cod = cy_table+table_height-fonth*0.5;
	CString title_cod(_T("strain"));
	pDc->TextOut(tx_cod,ty_cod,title_cod);
	for(int j=0;j<9;j++){
		int str_len = ycod[j].GetLength();
		float x_cod = cx_table-fontb*(str_len+1);
		float y_cod = cy_table+table_height-j*height_step-fonth*0.5;
		pDc->TextOut(x_cod,y_cod,ycod[j]);
	}
	tx_cod = cx_table-fontb*2;
	ty_cod = cy_table-fonth*1.5;
	title_cod.Format(_T("stress(MPa)"));
	pDc->TextOut(tx_cod,ty_cod,title_cod);
	lf.lfHeight = 1720;
	//	lf.lfWidth  = fontb*50;
	lf.lfWeight = 700;
	//	lf.lfUnderline = TRUE;
	CFont fonttitle;
	fonttitle.CreateFontIndirect(&lf);
	pDc->SelectObject(&fonttitle);
	CString title("Stress-Strain");
	float titlelen = title.GetLength();
	float title_x = cx_table+table_width*0.5-titlelen*fontb*0.5;	//-titlelen*fontb*6*0.5
	float title_y = cy_table*0.5-fonth*0.5;	//-fonth*6*0.5
	pDc->MoveTo(title_x,title_y);
	pDc->TextOut(title_x,title_y,title);
	pDc->SelectObject(pOldFont);
	pDc->SelectObject(pOldPen);
	::DeleteObject((HGDIOBJ)pen);
	::DeleteObject((HGDIOBJ)pen2);
	::DeleteObject((HGDIOBJ)pen3);
	::DeleteObject((HGDIOBJ)pen4);
}
void ConBenGou::SaveBitmap()
{
	CDC *pDc = m_draw.GetDC();
	HBITMAP hBitmap = NULL;
	if (pDc)
	{

		BITMAPINFO bmi;
		LPBYTE pBits;
		ZeroMemory(&bmi,sizeof(bmi));
		CRect rc;
		m_draw.GetClientRect(&rc);

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


		DrawDc(&dcMem,rc);


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
		img.Save(strPath+"ConBenGou.jpg");
		DeleteObject(hBitmap);
	}

}

void ConBenGou::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CRect rc;
	m_draw.GetClientRect(&rc);
	CDC *pDc = m_draw.GetDC();
	DrawDc(pDc,rc);
	m_draw.ReleaseDC(pDc);
}


BOOL ConBenGou::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  在此添加额外的初始化
	memcpy(e1,GlobalPara::m_DesnPara.con_e,sizeof(e1));
	memcpy(f1,GlobalPara::m_DesnPara.con_f,sizeof(f1));
	initlist();
	m_ec = e1[0];
	m_qc = f1[0];
	currentline = 0;
	m_comb_grade.SetCurSel(3);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ConBenGou::initlist()
{
	LPCTSTR LSTR[3]={"No.","strain","stress"};
	int div_w[3] = {30,70,70};
	m_con_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_con_list.RemoveAllGroups();
	for(int i=0;i<3;i++)
		m_con_list.DeleteColumn(0);
	m_con_list.DeleteAllItems();
	for (int i = 0; i < 3; i++) {
		m_con_list.InsertColumn(i,LSTR[i],LVCFMT_LEFT,div_w[i],-1 );	
	}
	for(int i=0;i<26;i++){
		CString temp;
		temp.Format(_T("%d"),i+1);
		m_con_list.InsertItem(i,temp);
		temp.Format(_T("%g"),e1[i]);
		m_con_list.SetItemText(i,1,temp);
		temp.Format(_T("%g"),f1[i]);
		m_con_list.SetItemText(i,2,temp);
	}
}


void ConBenGou::OnLvnItemchangedConList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void ConBenGou::OnNMClickConlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData();
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem !=-1)
		currentline = pNMListView->iItem;
	m_ec = e1[currentline];
	m_qc = f1[currentline];
	UpdateData(FALSE);
}

void ConBenGou::OnBnClickedChange()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	e1[currentline] = m_ec;
	f1[currentline] = m_qc;
	initlist();
	UpdateData(FALSE);
	OnPaint();
}


void ConBenGou::OnBnClickedCal()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString m_prograde;
	m_comb_grade.GetWindowText(m_prograde);
	m_grade = atoi(m_prograde);
	Tools::GetEuroStress(m_grade);
	memcpy(e1,GlobalPara::m_DesnPara.con_e,sizeof(e1));
	memcpy(f1,GlobalPara::m_DesnPara.con_f,sizeof(f1));
	initlist();
	UpdateData(FALSE);
	OnPaint();
}


void ConBenGou::OnCbnSelchangeComboGrade()
{
	// TODO: 在此添加控件通知处理程序代码
}
