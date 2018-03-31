#pragma once

#include "CommonUtil.h"
#include "steellib.h"
//  IPE 121-188
// 	HE  189-312
// 	HL  313-347
// 	HD  348-389
// 	HP  390-420
// 	UB  421-574
// 	UC  575-620
// 	W   621-872
// 	HP  873-885
// 	HG  886-923
class HEINFO
{
public:
	HEINFO();
	virtual ~HEINFO();
	static HEINFO &Get();
private:
	static HEINFO s_HEINFO;
public:
	int TYPECOUNT;
	CStringArray NAMES;
	enum
	{
		eNullSect = -1,
		eIPE = 0,// 121-188
		eHE,//  189-312
		eHL,//  313-347
		eHD,//  348-389
		eHP,//  390-420
		eUB,//  421-574
		eUC,//  575-620
		eW ,//  621-872
		eHP_matric,//  873-885
		eHG  //  886-923
	};



};

class CSectKeeper
{
public:
	

private:
	STEEL m_SteelC;
	static const int HE_START_LINE;
	static const int HE_END_LINE;
	static const int TOTAL_LINE;
private:
	int m_HECount;
	CArray<int> m_TypeBegin;
	CArray<int> m_TypeEnd;
public:
	STEEL& steelC();
	int HECount();
	int TypeBeginEnd(int nTp,int& nBegin,int &nEnd);
public:
	static CString g_fileName;
	static CSectKeeper& Get();
public:
	CSectKeeper(void);
	~CSectKeeper(void);
public:
	bool read();
	bool OnelineToHE_(CString str,HE_& he);
	 
};

