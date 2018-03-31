#include "StdAfx.h"
#include "SectionReader.h"


///////////////////////////////////////////////////////
HEINFO HEINFO::s_HEINFO;

HEINFO::HEINFO()
{
	TYPECOUNT = 10;
	NAMES.Add("IPE");
	NAMES.Add("HE");
	NAMES.Add("HL");
	NAMES.Add("HD");
	NAMES.Add("HP");
	NAMES.Add("UB");
	NAMES.Add("UC");
	NAMES.Add("W");
	NAMES.Add("HP[matric]");
	NAMES.Add("HG");
}

HEINFO::~HEINFO()
{

}

HEINFO & HEINFO::Get()
{
	return s_HEINFO;
}

///////////////////////////////////////////////////////

CString CSectKeeper::g_fileName = "Europe_juzhu.txt";
CSectKeeper g_SectionReader;

const int CSectKeeper::TOTAL_LINE=921;
const int CSectKeeper::HE_START_LINE = 119;
const int CSectKeeper::HE_END_LINE=921;
CSectKeeper::CSectKeeper(void)
{
	

	m_TypeBegin.Add(119);m_TypeEnd.Add(187);
	m_TypeBegin.Add(187 );m_TypeEnd.Add(311);
	m_TypeBegin.Add(311);m_TypeEnd.Add(346);
	m_TypeBegin.Add(346);m_TypeEnd.Add(388);
	m_TypeBegin.Add(388);m_TypeEnd.Add(419);
	m_TypeBegin.Add(419);m_TypeEnd.Add(573);
	m_TypeBegin.Add(573);m_TypeEnd.Add(619);
	m_TypeBegin.Add(619);m_TypeEnd.Add(871);
	m_TypeBegin.Add(871);m_TypeEnd.Add(884);
	m_TypeBegin.Add(884);m_TypeEnd.Add(922);

	m_HECount = HE_END_LINE+1;
	m_SteelC.HE = new HE_[m_HECount]; 
}


CSectKeeper::~CSectKeeper(void)
{
	if (NULL!=m_SteelC.HE)
	{
		delete[] m_SteelC.HE;
	}
}

CSectKeeper& CSectKeeper::Get()
{
	return g_SectionReader;
}

bool CSectKeeper::OnelineToHE_(CString str,HE_& he)
{
	CStringArray strArrGet;
	sjx::SplitCString(str,"\t",strArrGet);
	for(int i=strArrGet.GetSize()-1;i>=0;i--)
	{
		CString strOne  = strArrGet[i].Trim("\"");
		if(strOne.IsEmpty()==true)
		{
			strArrGet.RemoveAt(i);
		}
	}
	//Excel;
	//名	g	h	b	tw	tf	r	A	hi	d	fai	Pmin	Pmax	AL	AG	Iy	Wy	Wply	ix	Avz	Iz	Wz	Wplz	iz	Ss	It	Iw	S235W	S355W	S460W	S235Y	S355Y	S460Y	HISTAR
	int j=-1;
	_tcscpy_s(he.NAME,16,strArrGet[++j]);
	he.W=atof(strArrGet[++j]);
	he.H = atoi(strArrGet[++j]);
	he.B = atoi(strArrGet[++j]);
	he.tw = atof(strArrGet[++j]);
	he.tf = atof(strArrGet[++j]);
	he.r = atof(strArrGet[++j]);
	he.A = atof(strArrGet[++j]);
	he.hi = atoi(strArrGet[++j]);
	he.d = atoi(strArrGet[++j]);
	++j;
	he.Pmin1 = atoi(strArrGet[++j]);
	he.Pmin2 = atoi(strArrGet[++j]);
	he.AL= atof(strArrGet[++j]);
	he.AG= atof(strArrGet[++j]);
	he.Iy= atof(strArrGet[++j]);
	he.Wy= atof(strArrGet[++j]);
	he.Wply= atof(strArrGet[++j]);
	++j;
	he.Avz= atof(strArrGet[++j]);
	he.Iz= atof(strArrGet[++j]);
	he.Wz= atof(strArrGet[++j]);
	he.Wplz= atof(strArrGet[++j]);
	he.Iz1= atof(strArrGet[++j]);
	he.Ss= atof(strArrGet[++j]);
	he.It= atof(strArrGet[++j]);
	he.Iw= atof(strArrGet[++j]);
	he.S235w=atoi(strArrGet[++j]);
	he.S355w=atoi(strArrGet[++j]);
	he.S460w=atoi(strArrGet[++j]);
	he.S235y=atoi(strArrGet[++j]);
	he.S355y=atoi(strArrGet[++j]);
	he.S460y=atoi(strArrGet[++j]);
	he.HISTAR=atoi(strArrGet[++j]);
	//  Iy,Iz           截面惯性矩  单位 cm**4
	//  Wy,Wz           截面抵抗矩  单位 cm**3
	//  Iy1,Iz1         截面回转半径 单位 cm
	// y,z 轴 为形心轴  (相当于标准的x,y轴)
// 	float          Iy;
// 	float          Wy;
// 	float          Wply;    //   翼缘与腹板连接处的截面抵抗矩  ??
// 	float          Iy1;
// 	float          Avz;     //   面积矩 cm*cm
// 	float          Iz;
// 	float          Wz;
// 	float          Wplz;    //  ******
// 	float          Iz1;
// 	//   细部尺寸
// 	int       hi;      //  腹板净高度           mm
// 	int       d;       //  腹板去转角后的净高度 mm
// 	int      BD;      //  螺栓的直径 (类型)
// 	int      Pmin1;    //  翼缘上孔距的最小值1 mm
// 	int      Pmin2;    //  翼缘上孔距的最小值2 mm
// 	int      Pmax;     //  翼缘上孔距的最大值  mm
// 	float         AL;       //  表面积 m*m /m
// 	float         AG;       //  表面积 m*m /t
// 	float         Ss;
// 	float         It;
// 	float         Iw;       //  扭转惯性矩 ??
// 	//  分类 ENV1993-1-1
// 	int      S235w;    //  净弯 Y-Y
// 	int      S355w;    //  净弯 Y-Y
// 	int      S460w;    //  净弯 Y-Y
// 	int      S235y;    //  净压
// 	int      S355y;    //  净压
// 	int      S460y;    //  净压
// 	int      HISTAR;   //  HISTAR 的标志  带HI =1, 否则= 0
	return true;

}
bool CSectKeeper::read()
{
	CStdioFile file;
// 	TRY 
 	{
		CString strExeFileName;
		GetModuleFileName(NULL,strExeFileName.GetBuffer(MAX_PATH),MAX_PATH);//本程序就是exe
		strExeFileName.ReleaseBuffer(-1);
		int nsp = strExeFileName.ReverseFind('\\');
		CString path = strExeFileName.Left(nsp);
	    path += '\\';

		 
		if(false == file.Open(path + g_fileName,CFile::typeText|CFile::modeRead,NULL,NULL))
		{
			file.Close();
			return false;
		}
 
		CString str="";
		int nCurLine=0;
		int i=0;
		for (nCurLine=0;nCurLine<=HE_END_LINE;nCurLine++)
		{
			if (FALSE == file.ReadString(str))
			{
				break;
			}
 
			HE_& rHE = m_SteelC.HE[nCurLine];
			OnelineToHE_(str,rHE);

		}
		file.Close();
	}
// 	CATCH (CException, e)
// 	{
// 		return false;
// 	}
// 	END_CATCH
	return true;
}

int CSectKeeper::HECount()
{
	return m_HECount;
}

 
int CSectKeeper::TypeBeginEnd( int nTp,int& nBegin,int &nEnd )
{
	nBegin = m_TypeBegin[nTp];
	nEnd = m_TypeEnd[nTp];
	return true;
}

STEEL& CSectKeeper::steelC()
{
	return m_SteelC;
}

