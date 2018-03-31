#include "StdAfx.h"
//#include <point3d.h>
#include "CfgFun1.h"
#include "CfgBas.h"

extern "C" __declspec(dllimport) CCfgBas* m_pCfgBas;

CCfgFun1::CCfgFun1(void)
{
}


CCfgFun1::~CCfgFun1(void)
{
}
// void CCfgFun1::DrawBar3D(int &N, float X[], float Y[], CPoint3D pt1, CPoint3D pt2, float &DR, int &IFILL)
// {
// 	float X1,Y1,Z1,X2,Y2,Z2;
// 	X1 = pt1.x;
// 	Y1 = pt1.y;
// 	Z1 = pt1.z;
// 
// 	X2 = pt2.x;
// 	Y2 = pt2.y;
// 	Z2 = pt2.z;
// 	 
// 	m_pCfgBas->Bar3d(N, X, Y, X1, Y1, Z1, X2, Y2, Z2, DR, IFILL);
// 	 
// }

void CCfgFun1::MyUserCs3dXOY(float X0,float Y0,float ang,float Sc)
{
	float PRCS[9];
	PRCS[0] = X0;
	PRCS[1] = Y0;
	PRCS[2] = 0;

	PRCS[3] = Sc;
	PRCS[4] = Sc;
	PRCS[5] = Sc;


	PRCS[6] = -90;
	PRCS[7] = 0;
	PRCS[8] = ang;

	m_pCfgBas->Usercs(PRCS);
}

void CCfgFun1::MyUserCs3dExit()
{
	m_pCfgBas->Outucs();
}
