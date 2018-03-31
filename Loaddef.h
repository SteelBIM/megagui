#include "stdafx.h"
 
#ifndef MEGA_LOADS_HEADER
#define MEGA_LOADS_HEADER
class ConLoad
{
public:
	float x;
	float F;

	ConLoad();
	ConLoad(const ConLoad& ll);
};
class DisLoad
{
public:
	float x1;
	float q1;
	float x2;
	float q2;

	DisLoad();
	DisLoad(const DisLoad& ll);
};
class EndLoad
{
public:
	float Bottom;
	float Top;
	EndLoad();
	EndLoad(const EndLoad& ll);
};
///////////////////////////////////////////////////////
struct mega_loads
{
public:
//	{   工况信息
	CString Notatio;
	CString Description;
	float f0,f1,f2;
//	}
	


//{ 集中力
	CArray<ConLoad,ConLoad> ConYY;
	CArray<ConLoad,ConLoad> ConZZ;
//} 

// { 分布荷载
	CArray<DisLoad,DisLoad> DisYY;
	CArray<DisLoad,DisLoad> DisZZ;

//

// { 端部荷载
	EndLoad EndmYY;
	EndLoad EndmZZ;
// }
	
   float AnxialForceYY;
   float AnxialForceZZ;
//ZHLEI 2017/11 :拷贝构造和赋值

	mega_loads();
	mega_loads(const mega_loads &ld);
	mega_loads& operator = (const mega_loads &ld);
	 
};


class Mega_Cases
{
private:
	static Mega_Cases s_Mega_Cases;
private:
	//CArray<mega_loads> m_Cases;
public:
	static Mega_Cases& Get();
public:
	CArray<mega_loads>& Cases();
	mega_loads& CaseAt(int idx);
	void SetCases(const CArray<mega_loads>& cs);
};

#endif