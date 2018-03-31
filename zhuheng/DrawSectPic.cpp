#include "StdAfx.h"
#include "DrawSectPic.h"
#include "CfgBas.h"
#include "GlobalPara.h"

extern "C" __declspec( dllimport ) CCfgBas *m_pCfgBas;

CDrawSectPic::CDrawSectPic(void)
{
}


CDrawSectPic::~CDrawSectPic(void)
{
}

void CDrawSectPic::DrawPreDefinedSect()
{
	int cenghao,xianxing,xiankuan,yanse,fanhui;
	int iWay = 8;
	CString StrFile;
	StrFile.Format(_T("temptemp.t"));
	int n1=StrFile.GetLength();
	char FileName[256];
	strcpy(FileName,StrFile);
	FileName[n1]=char(0);
	m_pCfgBas->Closfl(iWay);
	m_pCfgBas->Openfl(iWay,FileName,n1,n1);
	m_pCfgBas->Nowfil(iWay);
	m_pCfgBas->Tobegin0(iWay);
	cenghao=1;
	xianxing=1;
	xiankuan=3;
	yanse=10;
	fanhui=0;
	m_pCfgBas->Layers(cenghao,xianxing,xiankuan,yanse,fanhui);
	if(GlobalPara::m_Sect_in.m_kind==1)
		DrawSect1();
	else if(GlobalPara::m_Sect_in.m_kind==2)
		DrawSect2();
	else if(GlobalPara::m_Sect_in.m_kind==3)
		DrawSect3();
	else if(GlobalPara::m_Sect_in.m_kind==4)
		DrawSect4();
	else if(GlobalPara::m_Sect_in.m_kind==5)
		DrawSect5();
	else if(GlobalPara::m_Sect_in.m_kind==6)
		DrawSect6();
	else if(GlobalPara::m_Sect_in.m_kind==7)
		DrawSect7();
	else if(GlobalPara::m_Sect_in.m_kind==8)
		DrawSect8();

	m_pCfgBas->Zoome();

}

void CDrawSectPic::DrawSect1()
{
	float B = GlobalPara::m_Sect_in.Sect_b;
	float H = GlobalPara::m_Sect_in.Sect_h;
	float barR = GlobalPara::m_Sect_in.Bar_d*0.5;
	float pt_x[4],pt_y[4];
	pt_x[0] = pt_x[3] = 0.f;
	pt_x[1] = pt_x[2] = B;
	pt_y[0] = pt_y[1] = H;
	pt_y[2] = pt_y[3] = 0.f;
	for(int i=0;i<3;i++)
		m_pCfgBas->Line(pt_x[i],pt_y[i],pt_x[i+1],pt_y[i+1]);
	m_pCfgBas->Line(pt_x[3],pt_y[3],pt_x[0],pt_y[0]);

	DrawProfile(B*0.5,H*0.5);

	DrawBoxBar();
}

void CDrawSectPic::DrawSect2()
{
	//实际为圆形单工字钢
	float R = GlobalPara::m_Sect_in.Sect_b*0.5;
	m_pCfgBas->Circle(R,R,R);
	DrawProfile(R,R);
	DrawCircleBar();
}

void CDrawSectPic::DrawSect3()
{
	float B = GlobalPara::m_Sect_in.Sect_b;
	float H = GlobalPara::m_Sect_in.Sect_h;
	float pt_x[4],pt_y[4];
	pt_x[0] = pt_x[3] = 0.f;
	pt_x[1] = pt_x[2] = B;
	pt_y[0] = pt_y[1] = H;
	pt_y[2] = pt_y[3] = 0.f;
	for(int i=0;i<3;i++)
		m_pCfgBas->Line(pt_x[i],pt_y[i],pt_x[i+1],pt_y[i+1]);
	m_pCfgBas->Line(pt_x[3],pt_y[3],pt_x[0],pt_y[0]);

	float pro_x[4],pro_y[4];
	pro_x[0] = pro_x[2] = B*0.5 - GlobalPara::m_Sect_in.HSect_x;
	pro_x[1] = pro_x[3] = B*0.5 + GlobalPara::m_Sect_in.HSect_x;
	pro_y[0] = pro_y[1] = H*0.5 + GlobalPara::m_Sect_in.HSect_y;
	pro_y[2] = pro_y[3] = H*0.5 - GlobalPara::m_Sect_in.HSect_y;
	for(int j=0;j<4;j++)
		DrawProfile(pro_x[j],pro_y[j]);
	DrawBoxBar();
}

void CDrawSectPic::DrawSect4()
{
	float B = GlobalPara::m_Sect_in.Sect_b;
	float H = GlobalPara::m_Sect_in.Sect_h;
	float pt_x[4],pt_y[4];
	pt_x[0] = pt_x[3] = 0.f;
	pt_x[1] = pt_x[2] = B;
	pt_y[0] = pt_y[1] = H;
	pt_y[2] = pt_y[3] = 0.f;
	for(int i=0;i<3;i++)
		m_pCfgBas->Line(pt_x[i],pt_y[i],pt_x[i+1],pt_y[i+1]);
	m_pCfgBas->Line(pt_x[3],pt_y[3],pt_x[0],pt_y[0]);

	DrawProfile(B*0.5,H*0.5+GlobalPara::m_Sect_in.HSect_y);
	DrawProfile(B*0.5,H*0.5-GlobalPara::m_Sect_in.HSect_y);
	DrawProfile(B*0.5-GlobalPara::m_Sect_in.HSect_x,H*0.5,1);
	DrawProfile(B*0.5+GlobalPara::m_Sect_in.HSect_x,H*0.5,1);
	DrawBoxBar();
}

void CDrawSectPic::DrawSect5()
{
	float R = GlobalPara::m_Sect_in.Sect_b*0.5;
	m_pCfgBas->Circle(R,R,R);

	DrawProfile(R,R+GlobalPara::m_Sect_in.HSect_y);
	DrawProfile(R,R-GlobalPara::m_Sect_in.HSect_y);
	DrawProfile(R-GlobalPara::m_Sect_in.HSect_x,R,1);
	DrawProfile(R+GlobalPara::m_Sect_in.HSect_x,R,1);
	DrawCircleBar();
}

void CDrawSectPic::DrawSect6()
{
	float B = GlobalPara::m_Sect_in.Sect_b;
	float H = GlobalPara::m_Sect_in.Sect_h;
	float pt_x[4],pt_y[4];
	pt_x[0] = pt_x[3] = 0.f;
	pt_x[1] = pt_x[2] = B;
	pt_y[0] = pt_y[1] = H;
	pt_y[2] = pt_y[3] = 0.f;
	for(int i=0;i<3;i++)
		m_pCfgBas->Line(pt_x[i],pt_y[i],pt_x[i+1],pt_y[i+1]);
	m_pCfgBas->Line(pt_x[3],pt_y[3],pt_x[0],pt_y[0]);

	float pro_x[6],pro_y[6];
	pro_x[0] = pro_x[2] = pro_x[4] = B*0.5 - GlobalPara::m_Sect_in.HSect_x;
	pro_x[1] = pro_x[3] = pro_x[5] = B*0.5 + GlobalPara::m_Sect_in.HSect_x;
	pro_y[0] = pro_y[1] = H*0.5 + GlobalPara::m_Sect_in.HSect_y;
	pro_y[4] = pro_y[5] = H*0.5 - GlobalPara::m_Sect_in.HSect_y;
	pro_y[2] = pro_y[3] = H*0.5;

	for(int j=0;j<6;j++)
		DrawProfile(pro_x[j],pro_y[j]);
	DrawBoxBar();
}

void CDrawSectPic::DrawSect7()
{
	float B = GlobalPara::m_Sect_in.Sect_b;
	float H = GlobalPara::m_Sect_in.Sect_h;
	float pt_x[4],pt_y[4];
	pt_x[0] = pt_x[3] = 0.f;
	pt_x[1] = pt_x[2] = B;
	pt_y[0] = pt_y[1] = H;
	pt_y[2] = pt_y[3] = 0.f;
	for(int i=0;i<3;i++)
		m_pCfgBas->Line(pt_x[i],pt_y[i],pt_x[i+1],pt_y[i+1]);
	m_pCfgBas->Line(pt_x[3],pt_y[3],pt_x[0],pt_y[0]);

	float pro_x[6],pro_y[6];
	pro_x[0] = pro_x[3] = B*0.5 - GlobalPara::m_Sect_in.HSect_x;
	pro_x[2] = pro_x[5] = B*0.5 + GlobalPara::m_Sect_in.HSect_x;
	pro_x[1] = pro_x[4] = B*0.5;
	pro_y[0] = pro_y[1] = pro_y[2] = H*0.5 + GlobalPara::m_Sect_in.HSect_y;
	pro_y[3] = pro_y[4] = pro_y[5] = H*0.5 - GlobalPara::m_Sect_in.HSect_y;
	for(int j=0;j<6;j++)
		DrawProfile(pro_x[j],pro_y[j]);
	DrawBoxBar();
}

void CDrawSectPic::DrawSect8()
{
	float B = GlobalPara::m_Sect_in.Sect_b;
	float H = GlobalPara::m_Sect_in.Sect_h;
	float pt_x[4],pt_y[4];
	pt_x[0] = pt_x[3] = 0.f;
	pt_x[1] = pt_x[2] = B;
	pt_y[0] = pt_y[1] = H;
	pt_y[2] = pt_y[3] = 0.f;
	for(int i=0;i<3;i++)
		m_pCfgBas->Line(pt_x[i],pt_y[i],pt_x[i+1],pt_y[i+1]);
	m_pCfgBas->Line(pt_x[3],pt_y[3],pt_x[0],pt_y[0]);

	DrawProfile(B*0.5,H*0.5);
}

void CDrawSectPic::DrawProfile(float x_bas,float y_bas,const int rotate)
{
	float HSect_b = GlobalPara::m_Sect_in.HSect.B1;
	float HSect_h = GlobalPara::m_Sect_in.HSect.H1;
	float HSect_tw = GlobalPara::m_Sect_in.HSect.RI;
	float HSect_tf = GlobalPara::m_Sect_in.HSect.RJ;
	float px[12],py[12];
	if(rotate==0){
	px[0] = px[11] = px[8] = px[7] = x_bas-HSect_b*0.5;
	px[1] = px[2] = px[5] = px[6] = x_bas+HSect_b*0.5;
	px[10] = px[9] = x_bas-HSect_tw*0.5;
	px[3] = px[4] = x_bas+HSect_tw*0.5;

	py[0] = py[1] = y_bas+HSect_h*0.5;
	py[11] = py[10] = py[3] = py[2] = y_bas+HSect_h*0.5-HSect_tf;
	py[8] = py[9] = py[4] = py[5] = y_bas-HSect_h*0.5+HSect_tf;
	py[7] = py[6] = y_bas-HSect_h*0.5;
	}
	else{
		px[0] = px[1]=x_bas-HSect_h*0.5;
		px[2] = px[3] = px[10] = px[11] = x_bas-HSect_h*0.5+HSect_tf;
		px[5] = px[4] = px[9] = px[8] = x_bas+HSect_h*0.5-HSect_tf;
		px[6] = px[7] = x_bas+HSect_h*0.5;

		py[0] = py[11] = py[8] = py[7] = y_bas-HSect_b*0.5;
		py[10] = py[9] = y_bas-HSect_tw*0.5;
		py[3] = py[4] = y_bas+HSect_tw*0.5;
		py[1] = py[2] = py[5] = py[6] = y_bas+HSect_b*0.5;
	}
	for(int i=0;i<11;i++)
		m_pCfgBas->Line(px[i],py[i],px[i+1],py[i+1]);
	m_pCfgBas->Line(px[11],py[11],px[0],py[0]);
}

void CDrawSectPic::DrawBoxBar()
{
	float B = GlobalPara::m_Sect_in.Sect_b;
	float H = GlobalPara::m_Sect_in.Sect_h;
	float barR = GlobalPara::m_Sect_in.Bar_d*0.5;
	float m_csy = GlobalPara::m_Sect_in.Con_coverd_x;
	float m_csz = GlobalPara::m_Sect_in.Con_coverd_y;
	int m_no_x = GlobalPara::m_Sect_in.Bar_num_bside;
	int m_no_y = GlobalPara::m_Sect_in.Bar_num_hside;
	float intervaly = (B-2*m_csy-2*barR)/(m_no_x-1);
	float intervalz = (H-2*m_csz-2*barR)/(m_no_y-1);
	float* pt_bar_x=new float[m_no_x];
	float* pt_bar_y=new float[m_no_y];
	for(int i=0;i<m_no_x;i++){
		pt_bar_x[i] = m_csy+barR+i*intervaly;
	}
	for(int j=0;j<m_no_y;j++){
		pt_bar_y[j] = m_csz+barR+j*intervalz;
	}
	for(int i=0;i<m_no_x;i++){
		m_pCfgBas->Circle(pt_bar_x[i],pt_bar_y[0],barR);
		m_pCfgBas->Circle(pt_bar_x[i],pt_bar_y[m_no_y-1],barR);
	}
	for(int j=0;j<m_no_y;j++){
		m_pCfgBas->Circle(pt_bar_x[0],pt_bar_y[j],barR);
		m_pCfgBas->Circle(pt_bar_x[m_no_x-1],pt_bar_y[j],barR);
	}
	delete[] pt_bar_x;
	delete[] pt_bar_y;
}

void CDrawSectPic::DrawCircleBar()
{
	float RR = GlobalPara::m_Sect_in.Sect_b*0.5;
	float barR = GlobalPara::m_Sect_in.Bar_d*0.5;
	float m_cs = GlobalPara::m_Sect_in.Con_coverd_x;
	int m_no = GlobalPara::m_Sect_in.Bar_num_bside;
	float R = RR-m_cs-barR;
//	float* pt_bar_x=new float[m_no];
//	float* pt_bar_y=new float[m_no];
	float pt_bar_x,pt_bar_y;

	for(int i=0;i<m_no;i++){
		float pt_arc = 2*3.14125*i/m_no;
		pt_bar_x = RR+R*cos(pt_arc);
		pt_bar_y = RR+R*sin(pt_arc);
		m_pCfgBas->Circle(pt_bar_x,pt_bar_y,barR);
	}
}