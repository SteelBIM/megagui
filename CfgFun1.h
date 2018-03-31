#pragma once

class CCfgFun1
{
public:
	CCfgFun1(void);
	~CCfgFun1(void);
	//static void DrawBar3D(int &N, float X[], float Y[], CPoint3D pt1, CPoint3D pt2, float &DR, int &IFILL);
	//static void GetPMUCI(float *fX0_x,float *fX0_y,float *fX0_z, /*坐标原点的三个 至?*/ float *fX_x,float *fX_y,float *fX_z, /*X 较虻娜?至?*/ float *fY_x,float *fY_y,float *fY_z, /*Y 较虻娜?至?*/ float *fZ_x,float *fZ_y,float *fZ_z, /*Z 较虻娜?至?*/ float PMUCI[9]);


	static void MyUserCs3dXOY(float X0,float Y0,float ang=0.f,float Sc=1.f);
	static void MyUserCs3dExit();
};

