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

//画所有截面示意图的函数   zzy
void CDrawSectPic::Setlayers(int i)
{
	int lay=0,ltype = 1,lw = 1 ,lc=0,lr =0;
	lay=i;
	switch (i)
	{
		case 1:                 //   混凝土多边形			
			lc=6;			
			break;
		case 2:                   //  型钢  Profile
			lc=3;
			lw=2;
			break;
		case 3:                 //  钢筋  bar
			lc=4;
			lw=2;
			break;
		case 4:                //   型钢标注
			lc=3;
			break;
		case 5:			
			lc=0;
			break;
		case 101:
			lc=0;
			break;
		case 102:
			lc=0;
			lw=2;
			break;
		default:
			lc=0;
			lw=0;
			break;
	}	
	m_pCfgBas->Layers(lay,ltype,lw,lc,lr);
	

}
//                                        1                           2
//                                  d1  
//                                  d2   |
//                                        ------------------------
//                              tail      |
//
//  ud=1，-1
//
void CDrawSectPic::Dim2p(float x1, float y1, float x2, float y2, float d1, float d2, float tail, int ud, float bl)
{
	float PI=3.14159265359;
	float ang=atan2(y2-y1,x2-x1);
	float ang_90=ang-0.5*PI;
	float x[8],y[8];
	float dd=d1;
	x[0]=x1+dd*cos(ang_90);
	y[0]=y1+dd*sin(ang_90);
	x[1]=x2+dd*cos(ang_90);
	y[1]=y2+dd*sin(ang_90);
	dd+=d2;
	x[2]=x1+dd*cos(ang_90);
	y[2]=y1+dd*sin(ang_90);
	x[3]=x2+dd*cos(ang_90);
	y[3]=y2+dd*sin(ang_90);
	dd+=tail;
	x[4]=x1+dd*cos(ang_90);
	y[4]=y1+dd*sin(ang_90);
	x[5]=x2+dd*cos(ang_90);
	y[5]=y2+dd*sin(ang_90);

	x[6]=x[2]-bl*cos(ang);
	y[6]=y[2]-bl*sin(ang);
	x[7]=x[3]+bl*cos(ang);
	y[7]=y[3]+bl*sin(ang);
	Setlayers(101);	
	m_pCfgBas->Line(x[0],y[0],x[4],y[4]);
	m_pCfgBas->Line(x[1],y[1],x[5],y[5]);
	m_pCfgBas->Line(x[6],y[6],x[7],y[7]);
	float alen=sqrtf((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	int len=int(alen+0.9999);
	char ch[80];
	itoa(len,ch,10);
	len=strlen(ch);
	float zb=1.8*bl;
	float zh=2.1*bl;
	float xm=0.5*(x[2]+x[3])+0.505*zh*ud*cos(ang+0.5*PI);
	float ym=0.5*(y[2]+y[3])+0.505*zh*ud*sin(ang+0.5*PI);
	float deg=ang*180/PI;
	if(deg<-89.9) deg+=180.;
	if(deg>90.0) deg-=180.;
	int ix=2;
	int iy=2;
	m_pCfgBas->Drawzf(len,ch,size_t(ch),xm,ym,zb,zh,ix,iy,deg);
	Setlayers(102);	
	float xx=0.5*bl;
	x[4]=x[2]+xx*cos(ang+PI/4);
	y[4]=y[2]+xx*sin(ang+PI/4);
	x[5]=x[2]-xx*cos(ang+PI/4);
	y[5]=y[2]-xx*sin(ang+PI/4);
	x[6]=x[3]+xx*cos(ang+PI/4);
	y[6]=y[3]+xx*sin(ang+PI/4);
	x[7]=x[3]-xx*cos(ang+PI/4);
	y[7]=y[3]-xx*sin(ang+PI/4);
	m_pCfgBas->Line(x[4],y[4],x[5],y[5]);
	m_pCfgBas->Line(x[6],y[6],x[7],y[7]);
}

void CDrawSectPic::DrawPreDefinedSect()
{
	
	int iWay = 99;
	CString StrFile;
	StrFile.Format(_T("temptemp.t"));
	int n1=StrFile.GetLength();
	char FileName[256];
	strcpy(FileName,StrFile);
	FileName[n1]=char(0);
	m_pCfgBas->Closfl(iWay);
	m_pCfgBas->Setcfg();
	m_pCfgBas->Openfl(iWay,FileName,n1,n1);
	m_pCfgBas->Savnewtoary(iWay);
	m_pCfgBas->Nowfil(iWay);
	m_pCfgBas->Tobegin0(iWay);
	int isave=1;
	m_pCfgBas->Ifsave(isave);		
	int ibcolor=15;
	m_pCfgBas->Bcolor(ibcolor);
	m_pCfgBas->Nowbcl(ibcolor);
	int narcl=72;
	m_pCfgBas->Narcl(narcl);
	float xmin,ymin,xmax,ymax,scale;
	GetSectSize(xmin,ymin,xmax,ymax,scale);
	float xx=1.2*(xmax-xmin);
	float yy=1.2*(ymax-ymin);
	float zz=xx;
	int iunit=1;
	float x0=xmin-0.1*xx;
	float y0=ymin-0.1*yy;
	float z0=x0;
	m_pCfgBas->Grfild(xx,yy,zz,iunit,scale,x0,y0,z0); 
	DrawSectAll();		
	int ivpd=0;
	m_pCfgBas->Xoyvpd(ivpd);
	m_pCfgBas->Redrwa();
	m_pCfgBas->Regens();
	m_pCfgBas->Zoome();
	StrFile=_T("TypeCrossSection");
	n1=StrFile.GetLength();	
	strcpy(FileName,StrFile);
	int NRC[4];
	for(int i=0;i<4;i++) NRC[i]=1;
	int kw=0;
	m_pCfgBas->Mfpcx(FileName,sizeof(FileName),n1,NRC,kw);
}

void CDrawSectPic::DrawSect1()
{
	DrawBoxConcrete();	
	float B = GlobalPara::m_Sect_in.Sect_b;
	float H = GlobalPara::m_Sect_in.Sect_h;
	if(GlobalPara::m_Sect_in.HSect.H1>1) 
	{
		DrawProfile(B*0.5,H*0.5);	
		TextProfile(B*0.5,0.);
	}
	
	DrawBoxBar();
}

void CDrawSectPic::DrawSect2()
{
	//实际为圆形单工字钢
	DrawCircleConcrete();	
	float R = GlobalPara::m_Sect_in.Sect_b*0.5;
	if(GlobalPara::m_Sect_in.HSect.H1>1)  
	{
		DrawProfile(R,R);
		TextProfile(R,0.);
	}
	DrawCircleBar();
}

void CDrawSectPic::DrawSect3()
{
	DrawBoxConcrete();
	float B = GlobalPara::m_Sect_in.Sect_b;
	float H = GlobalPara::m_Sect_in.Sect_h;

	float pro_x[4],pro_y[4];
	pro_x[0] = pro_x[2] = B*0.5 - GlobalPara::m_Sect_in.HSect_x;
	pro_x[1] = pro_x[3] = B*0.5 + GlobalPara::m_Sect_in.HSect_x;
	pro_y[0] = pro_y[1] = H*0.5 + GlobalPara::m_Sect_in.HSect_y;
	pro_y[2] = pro_y[3] = H*0.5 - GlobalPara::m_Sect_in.HSect_y;
	if(GlobalPara::m_Sect_in.HSect.H1>1)
	{
		for(int j=0;j<4;j++) 	DrawProfile(pro_x[j],pro_y[j]);
		TextProfile(0.5*B,0.);	

		float scale=DrawScale(B, H);
		float B_in=GlobalPara::m_Sect_in.HSect.B1;
		float H_in=GlobalPara::m_Sect_in.HSect.H1;
		Dim2p( pro_x[3],pro_y[3],B,pro_y[3] ,scale, pro_y[3] +5*scale, 2*scale, 1, scale);
		float dd=max(0.5*B_in,0.);
		Dim2p( pro_x[1],pro_y[1],pro_x[1],H ,scale, B-pro_x[1]+5*scale, 2*scale, 1, scale);
		
	}
	
	DrawBoxBar();

}

void CDrawSectPic::DrawSect4()
{
	DrawBoxConcrete();
	
	if(GlobalPara::m_Sect_in.HSect.H1>1)
	{
		float B = GlobalPara::m_Sect_in.Sect_b;
		float H = GlobalPara::m_Sect_in.Sect_h;

		DrawProfile(B*0.5,H*0.5+GlobalPara::m_Sect_in.HSect_y);
		DrawProfile(B*0.5,H*0.5-GlobalPara::m_Sect_in.HSect_y);
		DrawProfile(B*0.5-GlobalPara::m_Sect_in.HSect_x,H*0.5,1);
		DrawProfile(B*0.5+GlobalPara::m_Sect_in.HSect_x,H*0.5,1);

		TextProfile(B*0.5,0.);	

		float scale=DrawScale(B, H);
		float x0=B*0.5;
		float y0=H*0.5+GlobalPara::m_Sect_in.HSect_y;
		float B_in=GlobalPara::m_Sect_in.HSect.B1;
		float H_in=GlobalPara::m_Sect_in.HSect.H1;
		Dim2p(x0,y0,x0,H ,scale, 0.5*B_in+5*scale, 2*scale, 1, scale);
		x0=B*0.5-GlobalPara::m_Sect_in.HSect_x;
		y0=H*0.5;
		Dim2p( 0.,y0,x0,y0,scale, 0.5*B_in+5*scale, 2*scale, 1, scale);		
	}
	
	DrawBoxBar();
}

void CDrawSectPic::DrawSect5()
{
	DrawCircleConcrete();
	if(GlobalPara::m_Sect_in.HSect.H1>1)
	{
		
		float R = GlobalPara::m_Sect_in.Sect_b*0.5;
		DrawProfile(R,R+GlobalPara::m_Sect_in.HSect_y);
		DrawProfile(R,R-GlobalPara::m_Sect_in.HSect_y);
		DrawProfile(R-GlobalPara::m_Sect_in.HSect_x,R,1);
		DrawProfile(R+GlobalPara::m_Sect_in.HSect_x,R,1);

		TextProfile(R,0.);	

		float scale=DrawScale(2*R, 0.);
		float H_in=GlobalPara::m_Sect_in.HSect.B1; //转90度
		float xt=R+GlobalPara::m_Sect_in.HSect_x;
		float yt=R;
		Dim2p( xt,yt,2*R,yt,scale, 0.5*H_in+5*scale, 2*scale, 1, scale);
	}
	DrawCircleBar();
}

void CDrawSectPic::DrawSect6()
{
	
	DrawBoxConcrete();
	if(GlobalPara::m_Sect_in.HSect.H1>1)
	{
		float B = GlobalPara::m_Sect_in.Sect_b;
		float H = GlobalPara::m_Sect_in.Sect_h;

		float pro_x[6],pro_y[6];
		pro_x[0] = pro_x[2] = pro_x[4] = B*0.5 - GlobalPara::m_Sect_in.HSect_x;
		pro_x[1] = pro_x[3] = pro_x[5] = B*0.5 + GlobalPara::m_Sect_in.HSect_x;
		pro_y[0] = pro_y[1] = H*0.5 + GlobalPara::m_Sect_in.HSect_y;
		pro_y[4] = pro_y[5] = H*0.5 - GlobalPara::m_Sect_in.HSect_y;
		pro_y[2] = pro_y[3] = H*0.5;
		
		for(int j=0;j<6;j++) 	DrawProfile(pro_x[j],pro_y[j]);

		TextProfile(0.5*B,0.);	

		float scale=DrawScale(B, H);

		float B_in=GlobalPara::m_Sect_in.HSect.B1;
		float H_in=GlobalPara::m_Sect_in.HSect.H1;
		float x0,y0;
		x0=B*0.5 - GlobalPara::m_Sect_in.HSect_x;
		y0=H*0.5 - GlobalPara::m_Sect_in.HSect_y;		
		float dd;
		dd=y0-0.;
		Dim2p( 0.,y0, x0,y0 ,scale, dd+5*scale, 2*scale, 1, scale);		
		x0=B*0.5 + GlobalPara::m_Sect_in.HSect_x;
		y0=H*0.5 + GlobalPara::m_Sect_in.HSect_y;		
		dd=B-x0;		
		Dim2p( x0,y0 ,x0,H,scale, dd+5*scale, 2*scale, 1, scale);		
	}
	DrawBoxBar();
}

void CDrawSectPic::DrawSect7()
{
	DrawBoxConcrete();
	if(GlobalPara::m_Sect_in.HSect.H1>1)
	{
		float B = GlobalPara::m_Sect_in.Sect_b;
		float H = GlobalPara::m_Sect_in.Sect_h;

		float pro_x[6],pro_y[6];
		pro_x[0] = pro_x[3] = B*0.5 - GlobalPara::m_Sect_in.HSect_x;
		pro_x[2] = pro_x[5] = B*0.5 + GlobalPara::m_Sect_in.HSect_x;
		pro_x[1] = pro_x[4] = B*0.5;
		pro_y[0] = pro_y[1] = pro_y[2] = H*0.5 + GlobalPara::m_Sect_in.HSect_y;
		pro_y[3] = pro_y[4] = pro_y[5] = H*0.5 - GlobalPara::m_Sect_in.HSect_y;
		
		for(int j=0;j<6;j++)DrawProfile(pro_x[j],pro_y[j]);
		TextProfile(0.5*B,0.);	
		

		float scale=DrawScale(B, H);

		float B_in=GlobalPara::m_Sect_in.HSect.B1;
		float H_in=GlobalPara::m_Sect_in.HSect.H1;
		float x0,y0;
		x0=B*0.5 - GlobalPara::m_Sect_in.HSect_x;
		y0=H*0.5 - GlobalPara::m_Sect_in.HSect_y;		
		float dd;
		dd=y0-0.;
		Dim2p( 0.,y0, x0,y0 ,scale, dd+5*scale, 2*scale, 1, scale);		
		x0=B*0.5 + GlobalPara::m_Sect_in.HSect_x;
		y0=H*0.5 + GlobalPara::m_Sect_in.HSect_y;		
		dd=B-x0;		
		Dim2p( x0,y0 ,x0,H,scale, dd+5*scale, 2*scale, 1, scale);		
	}
	
	DrawBoxBar();
}

void CDrawSectPic::DrawSect8()
{
	
	DrawBoxConcrete();
	if(GlobalPara::m_Sect_in.HSect.H1>1)
	{
		float B = GlobalPara::m_Sect_in.Sect_b;
		float H = GlobalPara::m_Sect_in.Sect_h;
		DrawProfile(B*0.5,H*0.5);		
		TextProfile(0.5*B,0.);	
	}
	DrawBoxBar();
	
}

void CDrawSectPic::DrawProfile(float x_bas,float y_bas,const int rotate)
{
	Setlayers(2);	
	float PI=3.14159265359;
	float ang=rotate*PI/2.;
	float px[20],py[20];
	int n=GlobalPara::GetProfilePoly(x_bas,y_bas,ang,px,py)+1;
	m_pCfgBas->Poly(n,px,py);
}

void CDrawSectPic::PasteTo(int w, int h, float xmin, float ymin, float xmax, float ymax, float scale)
{
		int ir,ig,ib;
		ir=ig=ib=50;		
		int bcolor;
		m_pCfgBas->Daccfg(ir,ig,ib,bcolor);
		
		float PRCS[9];
	    int kepsave = 9999;
		m_pCfgBas->Ifsave(kepsave);
		int nowsave = 0;
		m_pCfgBas->Ifsave(nowsave);

		float xx=1.4*(xmax-xmin);
		float yy=1.4*(ymax-ymin);
		m_pCfgBas->Wgrfsiz(w,h,xx,yy);
		int iep=0;
		float eps=0.;
		float bata=0;
		m_pCfgBas->Gettgt(iep,eps,bata);
		PRCS[0]=0.2*(xmax-xmin)-xmin;
		PRCS[1]=0.2*(ymax-ymin)-ymin;
		PRCS[2]=0.;
		PRCS[3]=1.;
		PRCS[4]=1.;
		PRCS[5]=1.;
		PRCS[6]=0.;
		PRCS[7]=0.;
		PRCS[8]=0.;
		m_pCfgBas->Usercs(PRCS);
		int ih1=0;
		int ih2=h-1;
		int iw1=0;
		int iw2=w-1;
		m_pCfgBas->Frct(ih1,ih2,iw1,iw2,bcolor);
		
}


void CDrawSectPic::PasteToEnd(int kepsave)
{
	m_pCfgBas->Outucs();
	m_pCfgBas->Ifsave(kepsave);
}


void CDrawSectPic::GetSectSize(float& xmin, float& ymin, float& xmax, float& ymax, float& scale)
{
	scale=30.;  // 按比例尺 1:30
	float B = GlobalPara::m_Sect_in.Sect_b;
	float H = GlobalPara::m_Sect_in.Sect_h;
	
	if(GlobalPara::m_Sect_in.m_kind==2|| GlobalPara::m_Sect_in.m_kind==5)
	{
			float D = B;
			scale=DrawScale(D, 0.);
			xmin=0.;
			ymin=0.;
			xmax=D;
			ymax=D+7*scale;
			
	}else
	{
		scale=DrawScale(B, H);
		xmin=-7*scale;
		ymin=0.;
		xmax=B;
		ymax=H+7*scale;
		
	}

}


void CDrawSectPic::DrawSectAll(void)
{
	
	
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
}

void CDrawSectPic::DrawBoxBar()
{
	Setlayers(3);	
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
	Setlayers(3);	
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
//绘制方形的混凝土界面
void CDrawSectPic::DrawBoxConcrete()
{
	Setlayers(1);	
	float B = GlobalPara::m_Sect_in.Sect_b;
	float H = GlobalPara::m_Sect_in.Sect_h;
	float pt_x[5],pt_y[5];
	pt_x[4]=pt_x[0] = pt_x[3] = 0.f;
	pt_x[1] = pt_x[2] = B;
	pt_y[4] =pt_y[0] = pt_y[1] = H;
	pt_y[2] = pt_y[3] = 0.f;
	int n=5;
	m_pCfgBas->Poly(n,pt_x,pt_y);

	Setlayers(101);	
	float scale=DrawScale(B, H);
	Dim2p( B,H,0.,H,scale, 5*scale, 2*scale, -1, scale);
	Dim2p( 0.,H,0.,0.,scale, 5*scale, 2*scale, -1, scale);

}	
//绘制方形的混凝土界面
void CDrawSectPic::DrawCircleConcrete()
{
	Setlayers(1);	
	float R = GlobalPara::m_Sect_in.Sect_b*0.5;
	m_pCfgBas->Circle(R,R,R);	
	float scale=DrawScale(2*R, 0.);
	Dim2p( 2*R,R,0.,R,scale, R+5*scale, 2*scale, -1, scale);

}


float CDrawSectPic::DrawScale(float b, float h)
{
	float scale=0;
	float dd=max(b,h);
	if(dd<500.) scale=15.;
	else if(dd<1000.) scale=20.;
	else scale=50.;

	return scale;
}


void CDrawSectPic::TextProfile(float tx, float ty)
{

	float B = GlobalPara::m_Sect_in.Sect_b;
	float H = GlobalPara::m_Sect_in.Sect_h;
	if(H<0.001) H=B;
	float bl=DrawScale(B, H);

	Setlayers(4);	
	char ch[80];
	strcpy(ch,GlobalPara::m_Sect_in.HSect.NAME);
	int len=strlen(ch);
	float zb=1.8*bl;
	float zh=2.1*bl;
	float xm=tx;
	float ym=ty-5*bl;
	float deg=0.;
	int ix=2;
	int iy=1;
	m_pCfgBas->Drawzf(len,ch,size_t(ch),xm,ym,zb,zh,ix,iy,deg);

}
