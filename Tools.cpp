#include "StdAfx.h"
#include "Tools.h"
#include <math.h>

Tools::Tools(void)
{
}


Tools::~Tools(void)
{
}

void Tools::initmatbycode(const int codetype)
{
	if(codetype==1){

	}
	else if(codetype==2){

	}
	else if(codetype==3){

	}
}

void Tools::DrawCurrentLoad(CArray<mega_loads,mega_loads> CurLoads)
{

}

void Tools::CalEndM(double Mtop,double Mend,int loadcase,const int side)
{
	//0~13,从上到下
	//support:3 铰接，4 悬臂
	double sepMtop[13]={0.f};
	double sepMend[13]={0.f};
	if(GlobalPara::m_DesnPara.Restrict==3){
		for(int i=0;i<13;i++){
			sepMtop[i] = Mtop - Mtop*i/12;
			sepMend[i] = 0+Mend*i/12;
		}
	}
	else{
		for(int i=0;i<13;i++){
			sepMtop[i] = Mtop;
			sepMend[i] = 0;
		}
	}
	if(side==1){		//yy向
		for(int i=0;i<13;i++)
			GlobalPara::m_DesnPara.My_ed[loadcase][i] = sepMtop[i]+sepMend[i];
	}
	else{			//zz向
		for(int i=0;i<13;i++)
			GlobalPara::m_DesnPara.Mz_ed[loadcase][i] = sepMtop[i]+sepMend[i];		
	}

}

void Tools::CalEndN(double N,int loadcase)
{
	//轴力不做区分，选择yy和zz最大的
// 	for(int i=0;i<13;i++){
// 	
// 	}
	GlobalPara::m_DesnPara.N_ed[loadcase] = N;
}

//计算构件自重
double Tools::CalSelfG()
{
	int type = GlobalPara::m_Sect_in.m_kind;
	int nsects=1;
	if(type>2 && type<6)
		nsects = 4;
	else if(type==6)
		nsects = 6;
	int con_h = GlobalPara::m_Sect_in.Sect_h;
	int con_b = GlobalPara::m_Sect_in.Sect_b;
	int h = GlobalPara::m_Sect_in.HSect.H1;
	int b = GlobalPara::m_Sect_in.HSect.B1;
	float tf = GlobalPara::m_Sect_in.HSect.RI;
	float tw = GlobalPara::m_Sect_in.HSect.RJ;
	int bard = GlobalPara::m_Sect_in.Bar_d;
	int cover = GlobalPara::m_Sect_in.Concrete_coverd;
	int bar_x = GlobalPara::m_Sect_in.Bar_num_bside;
	int bar_y = GlobalPara::m_Sect_in.Bar_num_hside;
	double Ag,As,Asr,Ac;
	if(type==2 || type==5)
	{
		Ag = con_b*con_b*PII*0.25;
		As = nsects*(h*b-(h-2*tf)*(b-tw));
		Asr = bar_x*bard*bard*PII*0.25;
	}else
	{
		Ag = con_b*con_h;
		As = nsects*(h*b-(h-2*tf)*(b-tw));
		Asr = (2*(bar_x+bar_y)-4)*bard*bard*PII*0.25;
	}
	Ac = Ag-As-Asr;
	float conp = GlobalPara::m_DesnPara.m_Conp;
	float m_desn = GlobalPara::m_DesnPara.m_Density;
	float m_gravity = GlobalPara::m_DesnPara.m_Gravity;
	double SelfG = (Ac*conp+(As+Asr)*m_desn)*m_gravity*1e-6;
	SelfG = SelfG*GlobalPara::m_DesnPara.Lens*1e-3;
	return SelfG;
}

void Tools::SetConMatCurSel(CComboBox &conlist,int mat,BOOL ExpertMode)
{
	
	int n=conlist.GetCount();
	if(ExpertMode) 
	{
		conlist.SetCurSel(n-1);
		return;
	}
	int cursel=-1;
	for(int isel=0;isel<n;isel++)
	{
		CString str;
		int c1,c2;
		conlist.GetLBText(isel,str);
		if(str==_T("Custom")){	cursel=isel;	break;}
		
		char* ZFSTR=str.GetBuffer(str.GetLength());	
		if(str.Find("//")>0) sscanf(ZFSTR,"C%d//%d",&c1,&c2);
		else sscanf(ZFSTR,"C%d",&c1);	
		if(c1==mat) 	{	cursel=isel;		break;	}
	}
	if(cursel!=-1) conlist.SetCurSel(cursel);

}
void Tools::AddConMatByCode(CComboBox &conlist)
{
	if(GlobalPara::m_DesnPara.CodeType==1){
		conlist.ResetContent();
		conlist.AddString("C12/15");
		conlist.AddString("C16/20");
		conlist.AddString("C20/25");
		conlist.AddString("C25/30");
		conlist.AddString("C30/37");
		conlist.AddString("C35/45");
		conlist.AddString("C40/50");
		conlist.AddString("C45/55");
		conlist.AddString("C50/60");
		conlist.AddString("C55/67");
		conlist.AddString("C60/75");
		conlist.AddString("C70/85");
		conlist.AddString("C80/95");
		conlist.AddString("C90/105");
//		conlist.AddString("Custom");
	}
	else{
		conlist.ResetContent();
		conlist.AddString("C15");
		conlist.AddString("C20");
		conlist.AddString("C25");
		conlist.AddString("C30");
		conlist.AddString("C35");
		conlist.AddString("C40");
		conlist.AddString("C45");
		conlist.AddString("C50");
		conlist.AddString("C55");
		conlist.AddString("C60");
		conlist.AddString("C65");
		conlist.AddString("C70");
		conlist.AddString("C75");
		conlist.AddString("C80");

	}
	if(GlobalPara::ExpertMode==true)
		conlist.AddString("Custom");

	CSize sz;
	TEXTMETRIC tm;
	CDC* pDC = conlist.GetDC();
	CFont* pFont = conlist.GetFont();
	CFont* pOldFont = pDC->SelectObject(pFont);
	pDC->GetTextMetrics(&tm);
	int nWidth =0;
	for(int i=0;i<conlist.GetCount();i++){
		CString strtable = _T("");
		conlist.GetLBText(i,strtable);
		sz = pDC->GetTextExtent(strtable);
		sz.cx +=tm.tmAveCharWidth;
		nWidth = max(sz.cx,nWidth);
	}
	pDC->SelectObject(pOldFont);
	conlist.ReleaseDC(pDC);
	nWidth += ::GetSystemMetrics(SM_CXVSCROLL)+2*::GetSystemMetrics(SM_CXEDGE);

	conlist.SetDroppedWidth(nWidth);
}

void Tools::ConMatStringCatch(CString ConName)
{
	int lens = ConName.GetLength();
	if(ConName==_T("Custom"))
	{
		GlobalPara::m_DesnPara.con_model=3;
		float fcm = GetBenGouMaxFcm();
		GlobalPara::m_Sect_in.Concrete_mat = int(fcm)-8;	//对本构时，默认处理一下
	}
	else{	//拆字符
		int c1,c2;
		char* ZFSTR=ConName.GetBuffer(ConName.GetLength());	
		if(ConName.Find("/")>0) sscanf(ZFSTR,"C%d/%d",&c1,&c2);
		else sscanf(ZFSTR,"C%d",&c1);	
		GlobalPara::m_Sect_in.Concrete_mat=c1;
	}
}

void Tools::AddProMatByType(CComboBox &code,CComboBox &mat)
{

}

float Tools::CalSectProRatio()	//计算截面的含钢率
{
	float HRatio=0.f;
	int sect_type = GlobalPara::m_Sect_in.m_kind;
	int b = GlobalPara::m_Sect_in.Sect_b;
	int h = GlobalPara::m_Sect_in.Sect_h;
	int Hsect = GlobalPara::m_Sect_in.HSect.H1;
	int Bsect = GlobalPara::m_Sect_in.HSect.B1;
	float Tfsect = GlobalPara::m_Sect_in.HSect.RI;
	float Twsect = GlobalPara::m_Sect_in.HSect.RJ;
	float As = Hsect*1.f*Bsect - (Bsect-Twsect)*(Hsect-2*Tfsect);
	if(sect_type==1 || sect_type==8){
		HRatio = As/(b*1.f*h);
	}
	else if(sect_type==2){
		HRatio = As/(PII*b*b*0.25);
	}
	else if(sect_type==3 || sect_type==4 || sect_type==5){
		HRatio = 4*As/(b*1.f*h);
	}
	else if(sect_type==6 || sect_type==7){
		HRatio = 6*As/(b*1.f*h);
	}

	return HRatio;
}

//获得欧洲规范的ecu1
float Tools::GetECecu()
{
	float ecu;
	if(GlobalPara::m_Sect_in.Concrete_mat<50)
		ecu = 3.5;
	else{
		int fcm = GlobalPara::m_Sect_in.Concrete_mat+8;
		float d1 = (98-fcm)*1.f/100;
		ecu = 2.8+27*d1*d1*d1*d1;
	}
	return ecu;
}

void Tools::GetEuroCodeConcPara(int fck,float &Ecm,float &fcm,float &ec1,float &ecu1)
{
	fcm = fck+8;
	Ecm = 22*exp(0.3*log(fcm/10));
	Ecm = Ecm*1000;
	ec1 = 0.7*exp(0.31*log(fcm));
	float d1 = (98-fcm)*1.f/100;
	if(fck<50)
		ecu1 = 3.5;
	else
		ecu1 = 2.8+27*d1*d1*d1*d1; 
	ec1 = ec1/1000;
	ecu1 = ecu1/1000;
}

void Tools::GetUSCodeConcPara(int fck,float &f0,float &e0,float &ecu)
{
	f0 = 0.85*fck;
	e0 = 4700*sqrt(fck*1.f);
	ecu = 0.003;
}

void Tools::GetCHCodeConcPara(int fck,float &E,float &fcr,float &ecr,float &ecu,float &acr)
{
	if(fck==20){
		E = 2.55e4;
		ecr = 0.00147;
		ecu = 3*ecr;
		acr = 0.74;
	}
	else if(fck==25){
		E = 2.8e4;
		ecr = 0.00156;
		ecu = 2.6*ecr;
		acr = 1.06;
	}
	else if(fck==30){
		E = 3.0e4;
		ecr = 0.00164;
		ecu = 2.3*ecr;
		acr = 1.36;
	}
	else if(fck==35){
		E = 3.15e4;
		ecr = 0.00172;
		ecu = 2.1*ecr;
		acr = 1.65;
	}
	else if(fck==40){
		E = 3.25e4;
		ecr = 0.00179;
		ecu = 2*ecr;
		acr = 1.94;
	}
	else if(fck==45){
		E = 3.35e4;
		ecr = 0.00185;
		ecu = 1.9*ecr;
		acr = 2.21;
	}
	else if(fck==50){
		E = 3.45e4;
		ecr = 0.00192;
		ecu = 1.9*ecr;
		acr = 2.48;
	}
	else if(fck==55){
		E = 3.55e4;
		ecr = 0.00198;
		ecu = 1.8*ecr;
		acr = 2.74;
	}
	else if(fck==60){
		E = 3.6e4;
		ecr = 0.00203;
		ecu = 1.8*ecr;
		acr = 3.0;
	}
	else if(fck==65){
		E = 3.65e4;
		ecr = 0.00208;
		ecu = 1.7*ecr;
		acr = 3.25;
	}
	else if(fck==70){
		E = 3.7e4;
		ecr = 0.00213;
		ecu = 1.7*ecr;
		acr = 3.5;
	}
	else if(fck==75){
		E = 3.75e4;
		ecr = 0.00219;
		ecu = 1.7*ecr;
		acr = 3.75;
	}
	else if(fck==80){
		E = 3.8e4;
		ecr = 0.00224;
		ecu = 1.6*ecr;
		acr = 3.99;
	}
}
void Tools::ProMat(int CodeNo,int ProNo)
{

}

void Tools::GetEuroStress(int Fck)
{
	GlobalPara::initbengou();
	float Fcm = Fck+8;		//MPa
	float Ecm = 22*exp(0.3*log(Fcm/10));		//GPa
	float ec1 = 0.7*exp(0.31*log(Fcm));
	if(ec1>2.8)
		ec1 = 2.8;
	float ecu1;
	float d1 = (98-Fcm)*1.f/100;
	if(Fck<50)
		ecu1 = 3.5;
	else
		ecu1 = 2.8+27*d1*d1*d1*d1;
	//对应变量放大缩小
	Ecm = Ecm*1000;
	ec1 = ec1/1000;
	ecu1 = ecu1/1000;
	float k = 1.05*Ecm*ec1/Fcm;
	double nn;
	//先对ec进行上限处理
	for(int i=0;i<26;i++){
		if(GlobalPara::m_DesnPara.con_e[i]>ecu1)
			GlobalPara::m_DesnPara.con_e[i] = ecu1;
	}

	for(int i=0;i<26;i++){
		nn = GlobalPara::m_DesnPara.con_e[i]/ec1;
		GlobalPara::m_DesnPara.con_f[i] = (k*nn-nn*nn)*Fcm/(1+(k-2)*nn);
	}
}

float Tools::GetCNConF(int Grade)
{
	float fck;
	return fck;
}

void Tools::GetEUPara(double& Ecm,double& Es,double& Esr)
{
	float fcm = GetBenGouMaxFcm();		//从本构曲线里面取得
	Ecm = 1000*22*0.3*exp(log(fcm/10));
	Es = 210000;
	Esr = 200000;
}

void Tools::GetAISCPara(double& Ecm,double& Es,double& Esr)
{

}

void Tools::GetCNPara(double& Ecm,double& Es,double& Esr)
{

}

float Tools::GetBenGouMaxFcm()
{
	float maxfcm = 0;
	for(int i=1;i<26;i++){
		if(GlobalPara::m_DesnPara.con_f[i]>maxfcm)
			maxfcm = GlobalPara::m_DesnPara.con_f[i];
	}
	return maxfcm;
}

float Tools::GetEUCreepEc(double Ac,double Ecm)	//获得欧洲规范的徐变模量
{
	int h = GlobalPara::m_Sect_in.Sect_h;
	int b = GlobalPara::m_Sect_in.Sect_b;
	float RH = GlobalPara::m_DesnPara.RH;
	int day_t0 = GlobalPara::m_DesnPara.day_t0;
	int u = 2*(b+h);
	float h0 = 2*Ac/u;
	float fcm;
	float fRH;
	fcm = GetBenGouMaxFcm();
	float alpha1 = exp(0.7*log(35/fcm));
	float alpha2 = exp(0.2*log(35/fcm));
	float temp1 = 0.1*exp(3*log(h0));
	if(fcm>35)
		fRH = (1+(1-(RH/100))*alpha1/temp1)*alpha2;
	else
		fRH = 1+(1-RH/100)/temp1;
	float betafcm = 16.8/sqrt(fcm);
	float betat0 = 1/(0.1+exp(0.2*log(day_t0*1.f)));
	float fait0 = fRH*betafcm*betat0;
	float Ecp = Ecm/(1+fait0);
	return Ecp;
}

void Tools::CalProPoint(float E1,float E2,float m_fy,float m_fu)
{
	//前10个点
	float e1[26],f1[26];
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
	memcpy(GlobalPara::m_DesnPara.prop_e[0],e1,26*sizeof(float));
	memcpy(GlobalPara::m_DesnPara.prop_f[0],f1,26*sizeof(float));
	memcpy(GlobalPara::m_DesnPara.prop_e[1],e1,26*sizeof(float));
	memcpy(GlobalPara::m_DesnPara.prop_f[1],f1,26*sizeof(float));
}

void Tools::AutoComb()
{
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
}

//strings上限设置为80
//获得信息
void Tools::GetDesnInfo(int &j,CString Strings[])
{
	//截面几何信息
	Strings[j++].Format(_T("◆Section Infomation:"));
	Strings[j++].Format(_T(""));

	//约束信息
	Strings[j++].Format(_T("◆Restric Infomation:"));

	//荷载信息
	Strings[j++].Format(_T("◆Load Infomations:"));

}

bool Tools::MemberCheck_EU(membercheck_rst &Rst)
{
	int m_kind = GlobalPara::m_Sect_in.m_kind;
	int stru_class = GlobalPara::m_DesnPara.Struc_Class;
	int exposure_class = GlobalPara::m_DesnPara.Exp_Class;
	float Cmindur = Tools::GetCmindur_EURO(stru_class,exposure_class);
	float Cnom,Cdev;
	Cdev = 10;
	float Cmin = max(GlobalPara::m_Sect_in.Bar_d,max(Cmindur,10));
	Cnom = Cmin+Cdev;
	//保护层厚度检查
	//y
	Rst.PermitVal_lower[0] = Cnom;
	Rst.PermitVal_upper[0] = 0.4*GlobalPara::m_Sect_in.Sect_b;
	Rst.CalVal[0] = GlobalPara::m_Sect_in.Con_coverd_x;
	Tools::CompareVal(Rst,0);

	//z
	Rst.PermitVal_lower[1] = min(40,min(Cnom,GlobalPara::m_Sect_in.HSect.B1/6));
	Rst.PermitVal_upper[1] = 0.3*GlobalPara::m_Sect_in.Sect_h;
	Rst.CalVal[1] = GlobalPara::m_Sect_in.Con_coverd_y;
	Tools::CompareVal(Rst,1);

	float hb_ratio = GlobalPara::m_Sect_in.Sect_h/GlobalPara::m_Sect_in.Sect_b;
	if(hb_ratio>1)
		hb_ratio = 1/hb_ratio;
	Rst.PermitVal_lower[2] = 0.2;
	Rst.PermitVal_upper[2] = 5.0;
	Rst.CalVal[2] = hb_ratio;
	Tools::CompareVal(Rst,2);

// 	//型钢,无法考虑
// 	float Pro_fy = m_Sectinfo.fy;
// 	float delta = m_Sectinfo.As*Pro_fy/GPara::NplRd;
// 	GlobalResult::Pro_RatioCheck.PermitVal_lower = 0.2;
// 	GlobalResult::Pro_RatioCheck.PermitVal_upper = 0.9;
// 	GlobalResult::Pro_RatioCheck.CalVal = delta;
// 	Tools::CompareVal(GlobalResult::Pro_RatioCheck);

	//纵筋
	double As,Asr,Ac,Ag;
	GetSectA(As,Asr,Ac,Ag);
	Rst.PermitVal_lower[3] = 0.3;
	Rst.PermitVal_upper[3] = 6;
	Rst.CalVal[3] = Asr*100/Ac;
	Tools::CompareVal(Rst,3);
	//最小纵筋数量无法校核
	Rst.PermitVal_lower[4] = max(GlobalPara::m_Sect_in.Bar_d,max(GlobalPara::m_DesnPara.Dagg+5,20));
	Rst.PermitVal_upper[4] = 10000;
	Rst.CalVal[4] = GlobalPara::m_Sect_in.Bar_interval;
	Tools::CompareVal(Rst,4);

	Rst.PermitVal_lower[5] = 8;
	Rst.PermitVal_upper[5] = 10000;
	Rst.CalVal[5] = GlobalPara::m_Sect_in.Bar_d;
	Tools::CompareVal(Rst,5);

	return true;
}

void Tools::CompareVal(membercheck_rst &m_check,const int item_index,const bool checkval2/* =false */)
{
	if(fabs(m_check.PermitVal_upper[item_index]-10000)<0.01){		//没有上限的情况
		if(m_check.CalVal[item_index]-m_check.PermitVal_lower[item_index]>0.01){
			m_check.ifOk[item_index] = true;
		}
		else{
			m_check.ifOk[item_index] = false;
		}
	}
	else if(fabs(m_check.PermitVal_lower[item_index]-10000.f)<0.01){		//没有下限的情况
		if(m_check.PermitVal_upper[item_index]-m_check.CalVal[item_index]>0.01){
			m_check.ifOk[item_index] = true;
		}
		else{
			m_check.ifOk[item_index] = false;
		}
	}
	else{	//有上限情况
		if(m_check.CalVal[item_index]-m_check.PermitVal_lower[item_index]>0.01 && m_check.PermitVal_upper[item_index]-m_check.CalVal[item_index]>0.01){
			m_check.ifOk[item_index] = true;
		}
		else{
			m_check.ifOk[item_index] = false;
		}
	}

	//存在第二个数据
	if(checkval2){
		if(fabs(m_check.PermitVal_upper[item_index]-10000)<0.01){		//没有上限的情况
			if(m_check.CalVal2[item_index]-m_check.PermitVal_lower[item_index]>0.01){
				m_check.ifOk2[item_index] = true;
			}
			else{
				m_check.ifOk2[item_index] = false;
			}
		}
		else if(fabs(m_check.PermitVal_lower[item_index]-10000)<0.01){		//没有下限的情况
			if(m_check.PermitVal_upper[item_index]-m_check.CalVal2[item_index]>0.01){
				m_check.ifOk2[item_index] = true;
			}
			else{
				m_check.ifOk2[item_index] = false;
			}
		}
		else{	//有上限情况
			if(m_check.CalVal2[item_index]-m_check.PermitVal_lower[item_index]>0.01 && m_check.PermitVal_upper[item_index]-m_check.CalVal2[item_index]>0.01){
				m_check.ifOk2[item_index] = true;
			}
			else{
				m_check.ifOk2[item_index] = false;
			}
		}
	}
}

int Tools::GetCmindur_EURO(int &stru_class,int &exposure_class)
{
	int Cmindur[6][11]={
		{10,10,10,15,20,25,30},
		{10,10,15,20,25,30,35},
		{10,10,20,25,30,35,40},
		{10,15,25,30,35,40,45},
		{15,20,30,35,40,45,50},
		{20,25,35,40,45,50,55}
	};
	int ex_class = exposure_class;
	if(exposure_class==3)
		ex_class = 2;
	else if(exposure_class==4)
		ex_class = 3;
	else if(exposure_class==5 || exposure_class==8)
		ex_class = 4;
	else if(exposure_class==6 || exposure_class==9)
		ex_class = 5;
	else if(exposure_class==7 || exposure_class==10)
		ex_class = 6;
	int Cmin = Cmindur[stru_class][ex_class];
	return Cmin;
}

void Tools::GetSectA(double &As,double &Asr,double &Ac,double &Ag)
{
	int type = GlobalPara::m_Sect_in.m_kind;
	int con_h = GlobalPara::m_Sect_in.Sect_h;
	int con_b = GlobalPara::m_Sect_in.Sect_b;
	int h = GlobalPara::m_Sect_in.HSect.H1;
	int b = GlobalPara::m_Sect_in.HSect.B1;
	float tf = GlobalPara::m_Sect_in.HSect.RI;
	float tw = GlobalPara::m_Sect_in.HSect.RJ;
	int bard = GlobalPara::m_Sect_in.Bar_d;
	int bar_x = GlobalPara::m_Sect_in.Bar_num_bside;
	int bar_y = GlobalPara::m_Sect_in.Bar_num_hside;
	int nsects=1;
	if(type>2 && type<6)
		nsects = 4;
	else if(type==6)
		nsects = 6;
	if(type==2 || type==5)
	{
		Ag = con_b*con_b*PII*0.25;
		As = nsects*(h*b-(h-2*tf)*(b-tw));
		Asr = bar_x*bard*bard*PII*0.25;
	}
	else
	{
		Ag = con_b*con_h;
		As = nsects*(h*b-(h-2*tf)*(b-tw));
		Asr = (2*(bar_x+bar_y)-4)*bard*bard*PII*0.25;
	}
	Ac = Ag-As-Asr;

}