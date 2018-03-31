#pragma once
class CDrawSectPic
{
public:
	CDrawSectPic(void);
	~CDrawSectPic(void);

public:
	static void DrawPreDefinedSect();
	static void DrawSect1();
	static void DrawSect2();
	static void DrawSect3();
	static void DrawSect4();
	static void DrawSect5();
	static void DrawSect6();
	static void DrawSect7();
	static void DrawSect8();
	static void DrawProfile(float x_bas,float y_bas,const int rotate=0);
	static void DrawBoxBar();	//绘制方形的纵向钢筋
	static void DrawCircleBar();	//绘制圆形钢筋
};

