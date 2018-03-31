#pragma once

class CDrawSectPic
{
public:
	CDrawSectPic(void);
	~CDrawSectPic(void);

public:
	
	
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
	static void PasteTo(int w, int h, float xmin, float ymin, float xmax, float ymax,float scale);
	static void PasteToEnd(int kepsave);
	static void GetSectSize(float& xmin, float& ymin, float& xmax, float& ymax, float& scale);	
	static void DrawSectAll(void);
	static void Setlayers(int i);
	static void Dim2p(float x1, float y1, float x2, float y2, float d1, float d2, float tail, int ud, float bl);
	static float DrawScale(float b, float h);

	static void DrawBoxBar();	//绘制方形的纵向钢筋
	static void DrawCircleBar();	//绘制圆形钢筋
		
	static void DrawBoxConcrete();	//绘制方形的混凝土界面
	static void DrawCircleConcrete();	//绘制方形的混凝土界面

	static void TextProfile(float tx, float ty);
};

