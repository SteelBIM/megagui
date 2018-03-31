#pragma once
class DrawNMCurve
{
public:
	DrawNMCurve(void);
	~DrawNMCurve(void);

public:
	static void CalColmNMCurve_Fiber();
	static void GSect_FiberCal();
	static void GSect_Mesh();
	static void LengthEffect(double* Ncurve,int npoints,int yz);
	static void DrawFiberCurve(double N[][FirbePoints],double M[][FirbePoints],const int yz);
	static void ReduceNM();
	static void InitUCS(float scale_x,float sclae_y);
};

