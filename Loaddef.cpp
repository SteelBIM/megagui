#include "stdafx.h"
#include "Loaddef.h"
#include "GlobalPara.h"

mega_loads::mega_loads()
{
	Notatio="";
	Description="";
	f0=0.f;
	f1=0.f;
	f2=0.f;
 	ConYY.RemoveAll();
 	ConZZ.RemoveAll();
 	DisYY.RemoveAll();
 	DisZZ.RemoveAll();
	
	AnxialForceYY=0;
	AnxialForceZZ=0;
}

mega_loads::mega_loads( const mega_loads &ld )
{
	//*this = ld;
}

mega_loads& mega_loads::operator=( const mega_loads& ld )
{
	Notatio = ld.Notatio;
	Description = ld.Description;
	f0 = ld.f0;
	f1 = ld.f1;
	f2 = ld.f2;

	for (int i=0;i<ld.ConYY.GetSize();i++)
	{
		ConYY.Add(ld.ConYY[i]);
	}
	for (int i=0;i<ld.ConZZ.GetSize();i++)
	{
		ConZZ.Add(ld.ConZZ[i]);
	}

	for (int i=0;i<ld.DisYY.GetSize();i++)
	{
		DisYY.Add(ld.DisYY[i]);
	}
	for (int i=0;i<ld.DisZZ.GetSize();i++)
	{
		DisZZ.Add(ld.DisZZ[i]);
	}

	EndmYY = ld.EndmYY;
	EndmZZ = ld.EndmZZ;


	AnxialForceYY = ld.AnxialForceYY;
	AnxialForceZZ = ld.AnxialForceZZ;

	return *this;
}

// 
// ConLoad::ConLoad()
// {
// 	x = 0.f;
// 	F =0.f;
// }
// 
// ConLoad::ConLoad( const ConLoad& ll )
// {
// 	x = ll.x;
// 	F = ll.F;
// }
// 
// DisLoad::DisLoad()
// {
// 	x1=0.f;
// 	q1=0.f;
// 	x2=0.f;
// 	q2=0.f;
// }
// 
// DisLoad::DisLoad( const DisLoad& ll )
// {
// 	x1 = ll.x1;
// 	q1 = ll.q1;
// 	x2 = ll.x2;
// 	q2 = ll.q2;
// }
// 
// EndLoad::EndLoad()
// {
// 	Bottom=0.f;
// 	Top=0.f;
// }
// 
// EndLoad::EndLoad( const EndLoad& ll )
// {
// 	Bottom = ll.Bottom;
// 	Top = ll.Top;
// }


///////////////////////////////////////////////////////


Mega_Cases Mega_Cases::s_Mega_Cases;

Mega_Cases& Mega_Cases::Get()
{
	return s_Mega_Cases;
}

CArray<mega_loads>& Mega_Cases::Cases()
{
	//return m_Cases;
	return GlobalPara::LoadCaseData;
}

mega_loads& Mega_Cases::CaseAt( int idx )
{
	return Cases()[idx];
}

extern "C" __declspec( dllexport ) void  MegaCal_LoadCaseInit();
extern "C" __declspec( dllexport ) void MegaCal_LoadCaseSet(CString Notatio, CString Description,float f0,float f1,float f2,
	const ConLoad* ConYY,int nConYY, const ConLoad* ConZZ,int nConZZ,
	const DisLoad* DisYY,int nDisYY,const DisLoad* DisZZ,int nDisZZ,
	const EndLoad* EndmYY,const EndLoad* EndmZZ,
	float AnxialForceYY,float AnxialForceZZ);
void Mega_Cases::SetCases( const CArray<mega_loads>& cs )
{
	Cases().RemoveAll();
	Cases().Append(cs);
	MegaCal_LoadCaseInit();

	for (int i=0;i<cs.GetSize();i++)
	{
		const mega_loads& one = cs.GetAt(i);
		MegaCal_LoadCaseSet(
			one.Notatio,one.Description,one.f0,one.f1,one.f2,
			one.ConYY.GetData(),one.ConYY.GetSize(),one.ConZZ.GetData(),one.ConZZ.GetSize(),
			one.DisYY.GetData(),one.DisYY.GetSize(),one.DisZZ.GetData(),one.DisZZ.GetSize(),
			&one.EndmYY,&one.EndmZZ,
			one.AnxialForceYY,one.AnxialForceZZ
			);

	}
	 
}
