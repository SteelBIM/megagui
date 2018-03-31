// ProBenGou.cpp : 实现文件
//

#include "stdafx.h"
#include "MegaColumnGui.h"
#include "ProBenGou.h"
#include "afxdialogex.h"


// ProBenGou 对话框

IMPLEMENT_DYNAMIC(ProBenGou, CDialog)

ProBenGou::ProBenGou(CWnd* pParent /*=NULL*/)
	: CDialog(ProBenGou::IDD, pParent)
{

	m_e1 = 206000.0f;
	m_e2 = 0.01f;
	m_fu = 470.0f;
	m_fy = 345.0f;
}

ProBenGou::~ProBenGou()
{
}

void ProBenGou::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CURVE, m_draw);
	//	DDX_Control(pDX, IDC_PRO_LIST, m_pro_list);
	DDX_Text(pDX, IDC_EDIT_E1, m_e1);
	DDX_Text(pDX, IDC_EDIT_E2, m_e2);
	DDX_Text(pDX, IDC_EDIT_FU, m_fu);
	DDX_Text(pDX, IDC_EDIT_FY, m_fy);
	DDX_Control(pDX, IDC_COMBO_CURVE, m_curve);
}


BEGIN_MESSAGE_MAP(ProBenGou, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &ProBenGou::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &ProBenGou::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO_CURVE, &ProBenGou::OnCbnSelchangeComboCurve)
END_MESSAGE_MAP()

void ProBenGou::SaveBitmap()
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
		img.Save(strPath+"ProBenGou.jpg");
		DeleteObject(hBitmap);
	}

}
// ProBenGou 消息处理程序
void ProBenGou::DrawDc(CDC *dc1,CRect& rc)
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
	CBrush brush2;
	brush2.CreateSolidBrush(RGB(91,155,213));
	CBrush brush3;
	brush3.CreateSolidBrush(RGB(233,75,68));
	pDc->SelectObject(&pen3);
	CRect point(cx_table-3,cy_table+table_height+3,cx_table+3,cy_table+table_height-3);
	pDc->FillRect(&point,&brush2);
	// 	for(int i=0;i<25;i++){
	// 		float x0 = cx_table+e1[i]*100000*width_step/125;
	// 		float y0 = cy_table+table_height-f1[i]*height_step/100;
	// 		pDc->MoveTo(x0,y0);
	// 		float x1 = cx_table+e1[i+1]*100000*width_step/125;
	// 		float y1 = cy_table+table_height-f1[i+1]*height_step/100;
	// 		if(i==9 || i==24 || i==25){		//关键点高亮
	// 			point.SetRect(x1-5,y1+5,x1+5,y1-5);
	// 			pDc->FillRect(&point,&brush3);
	// 		}
	// 		else{
	// 			point.SetRect(x1-3,y1+3,x1+3,y1-3);
	// 			pDc->FillRect(&point,&brush2);
	// 		}
	// 		pDc->LineTo(x1,y1);
	// 	}
	float tempe1[4] = {e1[0],e1[9],e1[24],e1[25]};
	float tempf1[4] = {f1[0],f1[9],f1[24],f1[25]};
	for(int i=0;i<3;i++){
		float x0 = cx_table+tempe1[i]*table_width/0.1;
		float y0 = cy_table+table_height-tempf1[i]*table_height/800;
		pDc->MoveTo(x0,y0);
		float x1 = cx_table+tempe1[i+1]*table_width/0.1;
		float y1 = cy_table+table_height-tempf1[i+1]*height_step/100;	
		point.SetRect(x1-5,y1+5,x1+5,y1-5);
		pDc->FillRect(&point,&brush3);
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
	CString ycod[9]={"0","100","200","300","400","500","600","700","800"};
	CString xcod[9]={"0","0.025","0.05","0.075","0.1","0.125","0.150","0.175","0.2"};
	for(int i=0;i<9;i++){
		int str_len = xcod[i].GetLength();
		float x_cod = cx_table+i*width_step-str_len*fontb*0.5;
		float y_cod = cy_table+table_height+2;
		pDc->TextOut(x_cod,y_cod,xcod[i]);
	}
	float tx_cod = cx_table+table_width+fontb*2;
	float ty_cod = cy_table+table_height-fonth*0.5;
	CString title_cod(_T("strain"));
	pDc->TextOut(tx_cod,ty_cod,title_cod);
	for(int j=0;j<9;j++){
		int str_len = ycod[j].GetLength();
		float x_cod = cx_table-fontb*(str_len+2);
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

void ProBenGou::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CDC *pDc = m_draw.GetDC();
	CRect rc;
	m_draw.GetClientRect(&rc);
	DrawDc(pDc,rc);
	m_draw.ReleaseDC(pDc);
}


BOOL ProBenGou::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
//	initlist();
	int ctrl = 1;
	InitPara(ctrl);
	CalPoint();
	m_curve.SetCurSel(Ctrl_curve-1);
// 	m_ec = e1[0];
// 	m_qc = f1[0];
// 	currentline = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	UpdateData(FALSE);
	// 异常: OCX 属性页应返回 FALSE
}

// void ProBenGou::initlist()
// {
// 	LPCTSTR LSTR[3]={"No.","εc","σc"};
// 	int div_w[3] = {30,70,70};
// 	m_pro_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
// 	m_pro_list.RemoveAllGroups();
// 	for (int i = 0; i < 3; i++) {
// 		m_pro_list.InsertColumn(i,LSTR[i],LVCFMT_LEFT,div_w[i],-1 );	
// 	}
// 	for(int i=0;i<26;i++){
// 		CString temp;
// 		temp.Format(_T("%d"),i+1);
// 		m_pro_list.InsertItem(i,temp);
// 		temp.Format(_T("%g"),e1[i]);
// 		m_pro_list.SetItemText(i,1,temp);
// 		temp.Format(_T("%g"),f1[i]);
// 		m_pro_list.SetItemText(i,2,temp);
// 	}
// }


void ProBenGou::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveBitmap();

	UpdateData();
	memcpy(GlobalPara::m_DesnPara.prop_e[Ctrl_curve],e1,sizeof(e1));
	memcpy(GlobalPara::m_DesnPara.prop_f[Ctrl_curve],f1,sizeof(f1));
	GlobalPara::m_DesnPara.E1[Ctrl_curve] = m_e1;
	GlobalPara::m_DesnPara.E2[Ctrl_curve] = m_e2;
	GlobalPara::m_DesnPara.Fy[Ctrl_curve] = m_fy;
	GlobalPara::m_DesnPara.Fu[Ctrl_curve] = m_fu;
	CDialog::OnOK();
}

//离散化
void ProBenGou::CalPoint()
{
	float E1 = m_e1;
	float E2 = m_e2*E1;
	if(m_e2==0){
		m_fu = m_fy;
		E2 = E1;
	}
	//前10个点
	for(int i=0;i<10;i++){
		e1[i] = m_fy*i/(10*E1);
		f1[i] = m_fy*i/10;
	}
	//中间15个点
	for(int i=10;i<25;i++){
		e1[i] = m_fy/E1+(m_fu-m_fy)*(i-10)/(14*E2);
		f1[i] = m_fy+(m_fu-m_fy)*(i-10)/14;
	}
	//最后一个点
	e1[25] = e1[24]+0.01;
	f1[25] = m_fu;
}



void ProBenGou::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CalPoint();
	OnPaint();
	UpdateData(FALSE);
}

//根据选择来初始化曲线
void ProBenGou::InitPara(int Ctrl_C)
{
	Ctrl_curve = Ctrl_C;
	memcpy(e1,GlobalPara::m_DesnPara.prop_e[Ctrl_curve],sizeof(e1));
	memcpy(f1,GlobalPara::m_DesnPara.prop_f[Ctrl_curve],sizeof(f1));
	m_e1 = GlobalPara::m_DesnPara.E1[Ctrl_curve];
	m_e2 = GlobalPara::m_DesnPara.E2[Ctrl_curve];
	m_fy = GlobalPara::m_DesnPara.Fy[Ctrl_curve];
	m_fu = GlobalPara::m_DesnPara.Fu[Ctrl_curve];
}

void ProBenGou::OnCbnSelchangeComboCurve()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	memcpy(GlobalPara::m_DesnPara.prop_e[Ctrl_curve],e1,sizeof(e1));
	memcpy(GlobalPara::m_DesnPara.prop_f[Ctrl_curve],f1,sizeof(f1));
	GlobalPara::m_DesnPara.E1[Ctrl_curve] = m_e1;
	GlobalPara::m_DesnPara.E2[Ctrl_curve] = m_e2;
	GlobalPara::m_DesnPara.Fy[Ctrl_curve] = m_fy;
	GlobalPara::m_DesnPara.Fu[Ctrl_curve] = m_fu;
	Ctrl_curve = m_curve.GetCurSel()+1;
	memcpy(e1,GlobalPara::m_DesnPara.prop_e[Ctrl_curve],sizeof(e1));
	memcpy(f1,GlobalPara::m_DesnPara.prop_f[Ctrl_curve],sizeof(f1));
	m_e1 = GlobalPara::m_DesnPara.E1[Ctrl_curve];
	m_e2 = GlobalPara::m_DesnPara.E2[Ctrl_curve];
	m_fy = GlobalPara::m_DesnPara.Fy[Ctrl_curve];
	m_fu = GlobalPara::m_DesnPara.Fu[Ctrl_curve];
	CalPoint();
	OnPaint();
	UpdateData(FALSE);
}
