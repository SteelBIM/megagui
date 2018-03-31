
#ifndef _STEELLIB_H
#define _STEELLIB_H

#define NSECTION_ 500
#pragma pack(2)
struct SECTIONS {			// STS-2 SECTION colum and beam
         short   KIND;
         char  NAME[16];
		 char  NAME1[16];   // 对型钢截面的名字 如I25a等
         short   B1,B2;
         short   H1,H2;
         short   B3,H3;
         short   T1,T2,T3,T4;
         short   T5,T6;
         short   M;    //  材料类型, 5 为混凝土, 6 为钢材料
         float  RI;         // 左(下)刚域长度(米)  或 YH 只在IK=4
         float  RJ;         // 右(上)刚域长度(米)  或 YL
         float  UA;         // 剪切不均匀系数
};

struct PK11_SECT {			// STS-2 pk11计算中的梁柱截面结构
         short   KIND;
         char  NAME[16];
		 char  NAME1[16];   // 对型钢截面的名字 如I25a等
         short   B1,B2;
         short   H1,H2;
         short   B3,H3;
         short   T1,T2,T3,T4;
         short   T5,T6;
         short   M;    //  材料类型, 5 为混凝土, 6 为钢材料
         float  RI;         // 左(下)刚域长度(米)  或 YH 只在IK=4
         float  RJ;         // 右(上)刚域长度(米)  或 YL
         float  UA;         // 剪切不均匀系数

         float  Xc,Yc;      // 截面形心坐标   单位 m
         float  Rx, Ry;     // 对钢结构截面的截面塑性发展系数
         // 对钢结构截面的强度设计值, 抗拉,压,弯和抗剪 KN/m*m
         float  Fy, Fv;  //  Fv = Fy/ SQRT(3)
         float  W1x,W2x;    // 截面的抵抗矩 x 方向, 和 y 方向
         float  W1y,W2y;    //
         short	TypeX;  // 对钢结构轴心受压构件的截面分类1=a,2=b,3=c
         short	TypeY;  // 对钢结构轴心受压构件的截面分类1=a,2=b,3=c
         float  Rc;         // 对标准型钢截面为翼缘与腹板连接的弧形交角半径
                          // 对焊接截面为焊脚尺寸
};
struct SteelType_{
	int No;       //  此类型钢的数目,最多只能是100个
	int Type;     //  型钢的类别 = 1  热扎等边角钢
                    //           = 2  热扎不等边角钢
                    //           = 3  热扎普通工字钢
                    //           = 4  热扎轻型工字钢
                    //           = 5  热扎普通槽钢
                    //           = 6  热扎轻型槽钢
					//           = 7  欧洲标准宽翼缘H型钢 European wide flange beams
					//           = 8  日本标准宽翼缘H型钢 JIS wide falnge beams
					//           = 9  美国标准宽翼缘H型钢 American wide flange beams
	char NAME[40];  //  型钢的名字
	int MaxLen;    //  型钢字符串的最大长度
};
          
struct  JiaoGang_{    // 热扎普通和轻型角钢等边截面
	char NAME[16];  //型号
	int B;      // 尺寸 b     单位 mm
	int T;      // 尺寸 t     单位 mm
	float R;      // 尺寸 r     单位 mm
	float A;      // 截面面积 A 单位 cm
	float W;      // 每米重量   单位 kg/m
	float X0;     // 形心坐标   单位 mm
           //  Ix             x-x轴 截面惯性矩  单位 cm
           //  Wxmax,Wxmin    x-x轴 截面抵抗矩  单位 cm
           //  Ix1            x-x轴 截面回转半径 单位 cm
	float Ix,Wxmax,Wxmin,Ix1;
           //  Iu             u-u轴 截面惯性矩  单位 cm
           //  Wu             u-u轴 截面抵抗矩  单位 cm
           //  Iu1            u-u轴 截面回转半径 单位 cm
	float Iu,Wu,Iu1;
           //  Iv             v-v轴 截面惯性矩  单位 cm
           //  Wvmax,Wvmin    v-v轴 截面抵抗矩  单位 cm
           //  Iv1            v-v轴 截面回转半径 单位 cm
	float Iv,Wvmax,Wvmin,Iv1;
           //  IIx1  x1-x1轴 截面惯性矩  单位 cm
	float IIx1;
};

struct BJiaoGang_{    // 热扎普通和轻型不等边角钢截面
	char NAME[16]; // 型号
	int B1;		   // 尺寸 B     单位 mm
	int B;      // 尺寸 b     单位 mm
	int T;      // 尺寸 t     单位 mm
	float R;      // 尺寸 r     单位 mm
	float A;      // 截面面积 A 单位 cm
	float W;      // 每米重量   单位 kg/m
	float X0;     // 形心坐标   单位 mm
	float Y0;     // 形心坐标   单位 mm
           //  Ix             x-x轴 截面惯性矩  单位 cm
           //  Wxmax,Wxmin    x-x轴 截面抵抗矩  单位 cm
           //  Ix1            x-x轴 截面回转半径 单位 cm
	float Ix,Wxmax,Wxmin,Ix1;
           //  Iy             y-y轴 截面惯性矩  单位 cm
           //  Wymay,Wymin    y-y轴 截面抵抗矩  单位 cm
           //  Iy1            y-y轴 截面回转半径 单位 cm
	float Iy,Wymax,Wymin,Iy1;
           //  IIx1  x1-x1轴 截面惯性矩  单位 cm
	float IIx1;
           //  IIy1  y1-y1轴 截面惯性矩  单位 cm
	float IIy1;
           //  Iv             v-v轴 截面惯性矩  单位 cm
           //  Wv             v-v轴 截面抵抗矩  单位 cm
           //  Iv1            v-v轴 截面回转半径 单位 cm
	float Iv,Wv,Iv1;
	float TAN;
};

struct GongGang_{    // 热扎普通和轻型工字钢截面
	char NAME[16];	// 型号
	int H;			// 尺寸 h     单位 mm
	int B;      // 尺寸 b     单位 mm
	float Tw;     // 尺寸 tw    单位 mm
	float T;      // 尺寸 t     单位 mm
	float R;      // 尺寸 r     单位 mm
	float R1;     // 尺寸 r1    单位 mm
	float A;      // 截面面积 A 单位 cm
    float W;      // 每米重量   单位 kg/m
           //  Ix,Iy           截面惯性矩  单位 cm
           //  Wx,Wy           截面抵抗矩  单位 cm
           //  Sx              半截面面积矩 单位 cm
           //  Ix1,Iy1         截面回转半径 单位 cm
           // x,y 轴 为形心轴
	float          Ix;
	float          Wx;
	float          Sx;
	float          Ix1;
	float          Iy;
	float          Wy;
	float          Iy1;
};

struct CaoGang_{    // 热扎普通和轻型槽钢截面
	char NAME[16];   // 型号
	int       H;      // 尺寸 h     单位 mm
	int       B;      // 尺寸 b     单位 mm
	float          Tw;     // 尺寸 tw    单位 mm
	float          T;      // 尺寸 t     单位 mm
	float          R;      // 尺寸 r     单位 mm
	float          R1;     // 尺寸 r1    单位 mm
	float          A;      // 截面面积 A 单位 cm
	float          W;      // 每米重量   单位 kg/m
	float          X0;     // 形心坐标   单位 mm
	//  Ix,Iy,IIy1      截面惯性矩  单位 cm
	//  Wx,Wymax,Wymin  截面抵抗矩  单位 cm
	//  Sx              半截面面积矩 单位 cm
	//  Ix1,Iy1         截面回转半径 单位 cm
	// x,y 轴 为形心轴, IIy1 对截面边
	float          Ix;
	float          Wx;
	float          Sx;
	float          Ix1;
	float          Iy;
	float          Wymax;
	float          Wymin;
	float          Iy1;
	float          IIy1;
};


struct JIS_ {    //  日本标准宽翼缘H型钢
	char Code[16];    //  截面的标准尺寸 (高度X宽度)
	char NAME[16];    //  截面的选择名字 ( H x B )
	int   H;          //  截面的高度  mm
	int   B;          //  截面的宽度  mm
	float      t1;         //  腹板厚度    mm
	float      t2;         //  翼缘厚度    mm
	float      r;          //  翼缘与腹板相连转角半径  mm
	float      A;          //  截面的面积 cm*cm
	float      W;          //  截面的净重 kg/m
	//  Ix,Iy           截面惯性矩  单位 cm**4
	//  Wx,Wy           截面抵抗矩  单位 cm**3
	//  Ix1,Iy1         截面回转半径 单位 cm
	// x,y 轴 为形心轴
	float          Ix;
	float          Wx;
	float          Ix1;
	float          Iy;
	float          Wy;
	float          Iy1;
};


struct HE_ {    //  欧洲标准宽翼缘H型钢
	char NAME[16];    //  截面的类型名字
	char NAME1[16];
	int   H;          //  截面的高度  mm
	int   B;          //  截面的宽度  mm
	float      tw;         //  腹板厚度    mm
	float      tf;         //  翼缘厚度    mm
	float      r;          //  翼缘与腹板相连转角半径  mm
	float      A;          //  截面的面积 cm*cm
	float      W;          //  截面的净重 kg/m
	//  Iy,Iz           截面惯性矩  单位 cm**4
	//  Wy,Wz           截面抵抗矩  单位 cm**3
	//  Iy1,Iz1         截面回转半径 单位 cm
	// y,z 轴 为形心轴  (相当于标准的x,y轴)
	float          Iy;
	float          Wy;
	float          Wply;    //   翼缘与腹板连接处的截面抵抗矩  ??
	float          Iy1;
	float          Avz;     //   面积矩 cm*cm
	float          Iz;
	float          Wz;
	float          Wplz;    //  ******
	float          Iz1;
	//   细部尺寸
	int       hi;      //  腹板净高度           mm
	int       d;       //  腹板去转角后的净高度 mm
	int      BD;      //  螺栓的直径 (类型)
	int      Pmin1;    //  翼缘上孔距的最小值1 mm
	int      Pmin2;    //  翼缘上孔距的最小值2 mm
	int      Pmax;     //  翼缘上孔距的最大值  mm
	float         AL;       //  表面积 m*m /m
	float         AG;       //  表面积 m*m /t
	float         Ss;
	float         It;
	float         Iw;       //  扭转惯性矩 ??
	//  分类 ENV1993-1-1
	int      S235w;    //  净弯 Y-Y
	int      S355w;    //  净弯 Y-Y
	int      S460w;    //  净弯 Y-Y
	int      S235y;    //  净压
	int      S355y;    //  净压
	int      S460y;    //  净压
	int      HISTAR;   //  HISTAR 的标志  带HI =1, 否则= 0
};

struct AmericanW_ {    //  美国标准宽翼缘H型钢
	char NAME[16];    //  截面的类型名字 单位 mm
	char NAME1[16];   //  截面的类型名字 单位 inch
	int   H;          //  截面的高度  mm
	int   B;          //  截面的宽度  mm
	float      tw;         //  腹板厚度    mm
	float      tf;         //  翼缘厚度    mm
	float      r;          //  翼缘与腹板相连转角半径  mm
	float      A;          //  截面的面积 cm*cm
	float      W;          //  截面的净重 kg/m
	//  Iy,Iz           截面惯性矩  单位 cm**4
	//  Wy,Wz           截面抵抗矩  单位 cm**3
	//  Iy1,Iz1         截面回转半径 单位 cm
	// y,z 轴 为形心轴  (相当于标准的x,y轴)
	float          Iy;
	float          Wy;
	float          Wply;    //   翼缘与腹板连接处的截面抵抗矩  ??
	float          Iy1;
	float          Avz;     //   面积矩 cm*cm
	float          Iz;
	float          Wz;
	float          Wplz;    //  ******
	float          Iz1;
	//   细部尺寸
	int       hi;      //  腹板净高度           mm
	int       d;       //  腹板去转角后的净高度 mm
	int       BD;      //  螺栓的直径 (类型)
	int      Pmin1;    //  翼缘上孔距的最小值1 mm
	int      Pmin2;    //  翼缘上孔距的最小值2 mm
	int      Pmax;     //  翼缘上孔距的最大值  mm
	float         AL;       //  表面积 m*m /m
	float         AG;       //  表面积 m*m /t
	float         Ss;
	float         It;
	float         Iw;       //  扭转惯性矩 ??
	//  分类 ENV1993-1-1
	int      S235w;    //  净弯 Y-Y
	int      S355w;    //  净弯 Y-Y
	int      S460w;    //  净弯 Y-Y
	int      S235y;    //  净压
	int      S355y;    //  净压
	int      S460y;    //  净压
	int      HISTAR;   //  HISTAR 的标志  带HI=1, 否则=0
};

struct HXG_ {
	char   Code[16];    //  截面的标准尺寸 (高度X宽度)
	char   NAME[16];   // 型号
	int       H;      // 尺寸 h     单位 mm
	int       B;      // 尺寸 b     单位 mm
	float          Tw;     // 尺寸 tw    单位 mm
	float          Tf;     // 尺寸 t     单位 mm
	float          R;      // 尺寸 r     单位 mm
	float          A;      // 截面面积 A 单位 cm
	float          W;      // 每米重量   单位 kg/m
	//  Ix,Iy           截面惯性矩  单位 cm
	//  Wx,Wy           截面抵抗矩  单位 cm
	//  Sx              半截面面积矩 单位 cm
	//  Ix1,Iy1         截面回转半径 单位 cm
	// x,y 轴 为形心轴
	float          Ix;
	float          Wx;
	float          Ix1;
	float          Iy;
	float          Wy;
	float          Iy1;
};

struct CIRCLE_{
	char  NAME[16];   // 型号 直径
	int       D;
	float          A;
	float          I;
	float          I1;
	float          W;
	float          G;
};

struct Tube_ {
	char  NAME[16];   // 型号 d X t
	int       d;
	float          t;
	float          A;
	float          I;
	float          I1;
	float          W;
	float          G;
};

struct RectTube_ {
	char  NAME[16];   // 型号 d X t
	int       h;
	int       b;
	float          t;
	float          A;
	float          Ix;
	float          Ix1;
	float          Wx;
	float          Iy;
	float          Iy1;
	float          Wy;
	float          G;
};


struct ThinC_ {
	char   NAME[16];   // 型号 h*b*t
	int       h;
	int       b;
	int       a;
	float          t;
	float          AA;
	float          G;
	float          X0;
	float          Ix;
	float          Ix1;
	float          Wx;
	float          Iy;
	float          Iy1;
	float          Wymax;
	float          Wymin;
	float          IIy1;
	float          e0;
	float          It;
	float          Iw;
	float          k;
	float          Ww1;
	float          Ww2;
	float          Uy;
};

struct ThinZ_ {
	char   NAME[16];   // 型号 h*b*t
	int       h;
	int       b;
	int       a;
	float          t;
	float          AA;
	float          G;
	float          CT;
	float          IIx;
	float          IIx1;
	float          WWx1;
	float          IIy;
	float          IIy1;
	float          WWy1;
	float          Ix;
	float          Ix1;
	float          Wx1;
	float          Wx2;
	float          Iy;
	float          Iy1;
	float          Wy1;
	float          Wy2;
	float          Ix1y1;
	float          It;
	float          Iw;
	float          k;
	float          Ww1;
	float          Ww2;
};

struct  ThinL_ {
	char  NAME[16];   // 型号
	int       B;
	int       A;
	float          T;
	float          AA;
	float          G;
	float          y0;
	float          Ix0;
	float          Wx0max;
	float          Wx0min;
	float          Ix10;
	float          Ix;
	float          Ix1;
	float          Iy;
	float          Iy1;
	float          IIx1;
	float          e0;
	float          It;
	float          Iw;
	float          Uy;
};

struct HFWHXG_{ // 高频焊接轻型H型钢     2000.6.26
	char NAME[16];	//型号
	int No;
	int H;			//尺寸 h     单位 mm
	int B1;			//尺寸 b1    单位 mm  下翼缘宽度
	int B2;			//尺寸 b2    单位 mm  上翼缘宽度
	float Tw;		//尺寸 tw    单位 mm
	float Tf;		//尺寸 t     单位 mm
	float A;		//截面面积 A 单位 cm
};

struct BFT_ {		// 国标部分T型钢
	char   Code[16];    //  截面的标准尺寸 (高度X宽度)
	char   NAME[16];   // 型号
	float          H;      // 尺寸 h     单位 mm
	float          B;      // 尺寸 b     单位 mm
	float          Tw;     // 尺寸 tw    单位 mm
	float          Tf;     // 尺寸 t     单位 mm
	float          R;      // 尺寸 r     单位 mm
	float          A;      // 截面面积 A 单位 cm
	float          W;      // 每米重量   单位 kg/m
	//  Ix,Iy           截面惯性矩  单位 cm
	//  Wx,Wy           截面抵抗矩  单位 cm
	//  Sx              半截面面积矩 单位 cm
	//  Ix1,Iy1         截面回转半径 单位 cm
	// x,y 轴 为形心轴
	float          Ix;
	float          Wx;
	float          Ix1;
	float          Iy;
	float          Wy;
	float          Iy1;
	float          Cx;
};

struct ThinBJG_{    // 冷弯薄壁不等边角钢
	char NAME[16]; // 型号
	int B1;		   // 尺寸 B     单位 mm
	int B;      // 尺寸 b     单位 mm
	float T;      // 尺寸 t     单位 mm
	float R;      // 尺寸 r     单位 mm
	float A;      // 截面面积 A 单位 cm
	float W;      // 每米重量   单位 kg/m
	float X0;     // 形心坐标   单位 mm
	float Y0;     // 形心坐标   单位 mm
           //  Ix             x-x轴 截面惯性矩  单位 cm
           //  Wxmax,Wxmin    x-x轴 截面抵抗矩  单位 cm
           //  Ix1            x-x轴 截面回转半径 单位 cm
	float Ix,Wxmax,Wxmin,Ix1;
           //  Iy             y-y轴 截面惯性矩  单位 cm
           //  Wymay,Wymin    y-y轴 截面抵抗矩  单位 cm
           //  Iy1            y-y轴 截面回转半径 单位 cm
	float Iy,Wymax,Wymin,Iy1;
           //  IIx1  x1-x1轴 截面惯性矩  单位 cm
	float IIx1;
           //  IIy1  y1-y1轴 截面惯性矩  单位 cm
	float IIy1;
           //  Iv             v-v轴 截面惯性矩  单位 cm
           //  Wv             v-v轴 截面抵抗矩  单位 cm
           //  Iv1            v-v轴 截面回转半径 单位 cm
	float Iv,Wv,Iv1;
	float TAN;
};

struct CWHXG_ {		//波纹腹板H型钢表
	char   NAME[16];  // 型号
	int       H;      // 尺寸 h     单位 mm
	int       B;      // 尺寸 b     单位 mm
	float     Tw;     // 尺寸 tw    单位 mm
	float     Tf;     // 尺寸 t     单位 mm
	float		  A;      // 截面面积 A 单位 cm
	float     Af;     // 2个翼缘面积 2Af 单位 cm
	float     Aw;     // 腹板面积 Aq 单位 cm
	float     W;      // 每米重量   单位 kg/m
	float       Ix;
	float       Wx;
	float       Ix1;
	float       Iy;
	float       Wy;
	float       Iy1;
	float       It;
	float       Iw;
	int         B2;     //不对称截面上翼缘截面参数     
	float      Tf2;
	float        M;    //截面承载力
	int       BX_b;    // 波形参数
	int       BX_d;
	int       BX_q;
	float     BX_s;
};

struct BWHXG_ {		//波浪腹板H型钢表
	char   NAME[16];  // 型号
	int       H;      // 尺寸 h     单位 mm
	int       B;      // 尺寸 b     单位 mm
	float     Tw;     // 尺寸 tw    单位 mm
	float     Tf;     // 尺寸 t     单位 mm
	float		  A;      // 截面面积 A 单位 cm
	float     Af;     // 2个翼缘面积 2Af 单位 cm
	float     Aw;     // 腹板面积 Aq 单位 cm
	float     W;      // 每米重量   单位 kg/m
	float       Ix;
	float       Wx;
	float       Ix1;
	float       Iy;
	float       Wy;
	float       Iy1;
	float       It;
	float       Iw;
	int         H2;     //不对称截面上翼缘截面参数     
	int         B2;
	float      Tf2;
	int       BX_a;    // 波形参数
	int       BX_q;
	float     BX_s;
};

struct CHAR16_{
	char str[16];
};

struct STEEL{
	int TotalSteelType;
	struct SteelType_* SteelType;
	int* INDEX_;
	struct CHAR16_ *NAME;
	struct GongGang_ *GongGang;
	struct JiaoGang_ *JiaoGang;
	struct BJiaoGang_ *BJiaoGang;
	struct CaoGang_ *CaoGang;
	struct HE_ *HE;
	struct JIS_ *JIS;
	struct AmericanW_ *USAW;
	struct HXG_ *HXG;
	struct CIRCLE_ *CIRCLE;
	struct Tube_ *BoxTube;
	struct Tube_ *CircleTube1;
	struct Tube_ *CircleTube2;
	struct ThinC_ *ThinC1;
	struct ThinC_ *ThinC2;
	struct ThinZ_ *ThinZ;
	struct ThinZ_ *ThinXZ;
	struct RectTube_ *RectTube;
	struct ThinL_ *ThinL1;
	struct ThinL_ *ThinL2;
	struct HFWHXG_ *HFWHXG;
	struct BFT_ *BFT;
	struct ThinBJG_ *ThinBJG;
	struct CWHXG_ *CWHXG;
	struct BWHXG_ *BWHXG;
	struct BWHXG_ *BWHXG2;
};

struct SINGLESTEEL{
	int Kind;
	int Type;
	char NAME[16];	// 型号
	struct GongGang_ GongGang;
	struct JiaoGang_ JiaoGang;
	struct BJiaoGang_ BJiaoGang;
	struct CaoGang_ CaoGang;
	struct HE_ HE;
	struct JIS_ JIS;
	struct AmericanW_ USAW;
	struct HXG_ HXG;
	struct CIRCLE_ CIRCLE;
	struct Tube_ BoxTube;
	struct Tube_ CircleTube1;
	struct Tube_ CircleTube2;
	struct ThinC_ ThinC1;
	struct ThinC_ ThinC2;
	struct ThinZ_ ThinZ;
	struct ThinZ_ ThinXZ;
	struct RectTube_ RectTube;
	struct ThinL_ ThinL1;
	struct ThinL_ ThinL2;
	struct HFWHXG_ HFWHXG;
	struct BFT_ BFT;
	struct ThinBJG_ ThinBJG;
	struct CWHXG_ CWHXG;
	struct BWHXG_ BWHXG;
	struct BWHXG_ BWHXG2;
};
#pragma pack()


struct SECTION1{     //colum and beam
            short K;          // kind
            short B;          // width/diameter
            short H;          // height/number of poly
            short U;          // width of up flap for H-shape
            short T;          // thickness of up flap for H-shape
            short D;          // width of up flap for H-shape
            short F;          // thickness of down flap for H-shape
            short L;          // length   USE FOR COLUM
            short M;          // material
            short P;          // colour/reflection/paste
            char  NAME[16];   //   标准型钢截面名字  97.5
			//short IGZZ;       // 构造柱标记
            short B1;         //   标准型钢截面类型  USE FOR COLUM
			int   ID;
};

struct SECTION2{     //colum and beam
            short K;          // kind
            short B;          // width/diameter
            short H;          // height/number of poly
            short U;          // width of up flap for H-shape
            short T;          // thickness of up flap for H-shape
            short D;          // width of up flap for H-shape
            short F;          // thickness of down flap for H-shape
            short L;          // length   USE FOR COLUM
            short M;          // material
            short P;          // colour/reflection/paste
            char  NAME[16];   //   标准型钢截面名字  97.5
            short B1;         //   标准型钢截面类型  USE FOR COLUM
			int   ID;
};

//
//struct SteelType_{
//	int No;       //  此类型钢的数目,最多只能是100个
//	int Type;     //  型钢的类别 = 1  热扎等边角钢
//                    //            //             = 2  热扎不等边角钢
//                    //            //             = 3  热扎普通工字钢
//                    //            //             = 4  热扎轻型工字钢
//                    //            //             = 5  热扎普通槽钢
//                    //            //             = 6  热扎轻型槽钢
//					//           = 7  欧洲标准宽翼缘H型钢 European wide flange beams
//					//           = 8  日本标准宽翼缘H型钢 JIS wide falnge beams
//					//           = 9  美国标准宽翼缘H型钢 American wide flange beams
//	char NAME[40];  //  型钢的名字
//	int MaxLen;    //  型钢字符串的最大长度
//};
//          
//struct  JiaoGang_{    // 热扎普通和轻型角钢等边截面
//	char NAME[16];  //型号
//	int B;      // 尺寸 b     单位 mm
//	int T;      // 尺寸 t     单位 mm
//	float R;      // 尺寸 r     单位 mm
//	float A;      // 截面面积 A 单位 cm
//	float W;      // 每米重量   单位 kg/m
//	float X0;     // 形心坐标   单位 mm
//           //  Ix             x-x轴 截面惯性矩  单位 cm
//           //  Wxmax,Wxmin    x-x轴 截面抵抗矩  单位 cm
//           //  Ix1            x-x轴 截面回转半径 单位 cm
//	float Ix,Wxmax,Wxmin,Ix1;
//           //  Iu             u-u轴 截面惯性矩  单位 cm
//           //  Wu             u-u轴 截面抵抗矩  单位 cm
//           //  Iu1            u-u轴 截面回转半径 单位 cm
//	float Iu,Wu,Iu1;
//           //  Iv             v-v轴 截面惯性矩  单位 cm
//           //  Wvmax,Wvmin    v-v轴 截面抵抗矩  单位 cm
//           //  Iv1            v-v轴 截面回转半径 单位 cm
//	float Iv,Wvmax,Wvmin,Iv1;
//           //  IIx1  x1-x1轴 截面惯性矩  单位 cm
//	float IIx1;
//};
//
//struct BJiaoGang_{    // 热扎普通和轻型不等边角钢截面
//	char NAME[16]; // 型号
//	int B1;		   // 尺寸 B     单位 mm
//	int B;      // 尺寸 b     单位 mm
//	int T;      // 尺寸 t     单位 mm
//	float R;      // 尺寸 r     单位 mm
//	float A;      // 截面面积 A 单位 cm
//	float W;      // 每米重量   单位 kg/m
//	float X0;     // 形心坐标   单位 mm
//	float Y0;     // 形心坐标   单位 mm
//           //  Ix             x-x轴 截面惯性矩  单位 cm
//           //  Wxmax,Wxmin    x-x轴 截面抵抗矩  单位 cm
//           //  Ix1            x-x轴 截面回转半径 单位 cm
//	float Ix,Wxmax,Wxmin,Ix1;
//           //  Iy             y-y轴 截面惯性矩  单位 cm
//           //  Wymay,Wymin    y-y轴 截面抵抗矩  单位 cm
//           //  Iy1            y-y轴 截面回转半径 单位 cm
//	float Iy,Wymax,Wymin,Iy1;
//           //  IIx1  x1-x1轴 截面惯性矩  单位 cm
//	float IIx1;
//           //  IIy1  y1-y1轴 截面惯性矩  单位 cm
//	float IIy1;
//           //  Iv             v-v轴 截面惯性矩  单位 cm
//           //  Wv             v-v轴 截面抵抗矩  单位 cm
//           //  Iv1            v-v轴 截面回转半径 单位 cm
//	float Iv,Wv,Iv1;
//	float TAN;
//};
//
//struct GongGang_{    // 热扎普通和轻型工字钢截面
//	char NAME[16];	// 型号
//	int H;			// 尺寸 h     单位 mm
//	int B;      // 尺寸 b     单位 mm
//	float Tw;     // 尺寸 tw    单位 mm
//	float T;      // 尺寸 t     单位 mm
//	float R;      // 尺寸 r     单位 mm
//	float R1;     // 尺寸 r1    单位 mm
//	float A;      // 截面面积 A 单位 cm
//    float W;      // 每米重量   单位 kg/m
//           //  Ix,Iy           截面惯性矩  单位 cm
//           //  Wx,Wy           截面抵抗矩  单位 cm
//           //  Sx              半截面面积矩 单位 cm
//           //  Ix1,Iy1         截面回转半径 单位 cm
//           // x,y 轴 为形心轴
//	float          Ix;
//	float          Wx;
//	float          Sx;
//	float          Ix1;
//	float          Iy;
//	float          Wy;
//	float          Iy1;
//};
//
//struct CaoGang_{    // 热扎普通和轻型槽钢截面
//	char NAME[16];   // 型号
//	int       H;      // 尺寸 h     单位 mm
//	int       B;      // 尺寸 b     单位 mm
//	float          Tw;     // 尺寸 tw    单位 mm
//	float          T;      // 尺寸 t     单位 mm
//	float          R;      // 尺寸 r     单位 mm
//	float          R1;     // 尺寸 r1    单位 mm
//	float          A;      // 截面面积 A 单位 cm
//	float          W;      // 每米重量   单位 kg/m
//	float          X0;     // 形心坐标   单位 mm
//	//  Ix,Iy,IIy1      截面惯性矩  单位 cm
//	//  Wx,Wymax,Wymin  截面抵抗矩  单位 cm
//	//  Sx              半截面面积矩 单位 cm
//	//  Ix1,Iy1         截面回转半径 单位 cm
//	// x,y 轴 为形心轴, IIy1 对截面边
//	float          Ix;
//	float          Wx;
//	float          Sx;
//	float          Ix1;
//	float          Iy;
//	float          Wymax;
//	float          Wymin;
//	float          Iy1;
//	float          IIy1;
//};
//
//
//struct JIS_ {    //  日本标准宽翼缘H型钢
//	char Code[16];    //  截面的标准尺寸 (高度X宽度)
//	char NAME[16];    //  截面的选择名字 ( H x B )
//	int   H;          //  截面的高度  mm
//	int   B;          //  截面的宽度  mm
//	float      t1;         //  腹板厚度    mm
//	float      t2;         //  翼缘厚度    mm
//	float      r;          //  翼缘与腹板相连转角半径  mm
//	float      A;          //  截面的面积 cm*cm
//	float      W;          //  截面的净重 kg/m
//	//  Ix,Iy           截面惯性矩  单位 cm**4
//	//  Wx,Wy           截面抵抗矩  单位 cm**3
//	//  Ix1,Iy1         截面回转半径 单位 cm
//	// x,y 轴 为形心轴
//	float          Ix;
//	float          Wx;
//	float          Ix1;
//	float          Iy;
//	float          Wy;
//	float          Iy1;
//};
//
//
//struct HE_ {    //  欧洲标准宽翼缘H型钢
//	char NAME[16];    //  截面的类型名字
//	char NAME1[16];
//	int   H;          //  截面的高度  mm
//	int   B;          //  截面的宽度  mm
//	float      tw;         //  腹板厚度    mm
//	float      tf;         //  翼缘厚度    mm
//	float      r;          //  翼缘与腹板相连转角半径  mm
//	float      A;          //  截面的面积 cm*cm
//	float      W;          //  截面的净重 kg/m
//	//  Iy,Iz           截面惯性矩  单位 cm**4
//	//  Wy,Wz           截面抵抗矩  单位 cm**3
//	//  Iy1,Iz1         截面回转半径 单位 cm
//	// y,z 轴 为形心轴  (相当于标准的x,y轴)
//	float          Iy;
//	float          Wy;
//	float          Wply;    //   翼缘与腹板连接处的截面抵抗矩  ??
//	float          Iy1;
//	float          Avz;     //   面积矩 cm*cm
//	float          Iz;
//	float          Wz;
//	float          Wplz;    //  ******
//	float          Iz1;
//	//   细部尺寸
//	int       hi;      //  腹板净高度           mm
//	int       d;       //  腹板去转角后的净高度 mm
//	int      BD;      //  螺栓的直径 (类型)
//	int      Pmin1;    //  翼缘上孔距的最小值1 mm
//	int      Pmin2;    //  翼缘上孔距的最小值2 mm
//	int      Pmax;     //  翼缘上孔距的最大值  mm
//	float         AL;       //  表面积 m*m /m
//	float         AG;       //  表面积 m*m /t
//	float         Ss;
//	float         It;
//	float         Iw;       //  扭转惯性矩 ??
//	//  分类 ENV1993-1-1
//	int      S235w;    //  净弯 Y-Y
//	int      S355w;    //  净弯 Y-Y
//	int      S460w;    //  净弯 Y-Y
//	int      S235y;    //  净压
//	int      S355y;    //  净压
//	int      S460y;    //  净压
//	int      HISTAR;   //  HISTAR 的标志  带HI =1, 否则= 0
//};
//
//struct AmericanW {    //  美国标准宽翼缘H型钢
//	char NAME[16];    //  截面的类型名字 单位 mm
//	char NAME1[16];   //  截面的类型名字 单位 inch
//	int   H;          //  截面的高度  mm
//	int   B;          //  截面的宽度  mm
//	float      tw;         //  腹板厚度    mm
//	float      tf;         //  翼缘厚度    mm
//	float      r;          //  翼缘与腹板相连转角半径  mm
//	float      A;          //  截面的面积 cm*cm
//	float      W;          //  截面的净重 kg/m
//	//  Iy,Iz           截面惯性矩  单位 cm**4
//	//  Wy,Wz           截面抵抗矩  单位 cm**3
//	//  Iy1,Iz1         截面回转半径 单位 cm
//	// y,z 轴 为形心轴  (相当于标准的x,y轴)
//	float          Iy;
//	float          Wy;
//	float          Wply;    //   翼缘与腹板连接处的截面抵抗矩  ??
//	float          Iy1;
//	float          Avz;     //   面积矩 cm*cm
//	float          Iz;
//	float          Wz;
//	float          Wplz;    //  ******
//	float          Iz1;
//	//   细部尺寸
//	int       hi;      //  腹板净高度           mm
//	int       d;       //  腹板去转角后的净高度 mm
//	int       BD;      //  螺栓的直径 (类型)
//	int      Pmin1;    //  翼缘上孔距的最小值1 mm
//	int      Pmin2;    //  翼缘上孔距的最小值2 mm
//	int      Pmax;     //  翼缘上孔距的最大值  mm
//	float         AL;       //  表面积 m*m /m
//	float         AG;       //  表面积 m*m /t
//	float         Ss;
//	float         It;
//	float         Iw;       //  扭转惯性矩 ??
//	//  分类 ENV1993-1-1
//	int      S235w;    //  净弯 Y-Y
//	int      S355w;    //  净弯 Y-Y
//	int      S460w;    //  净弯 Y-Y
//	int      S235y;    //  净压
//	int      S355y;    //  净压
//	int      S460y;    //  净压
//	int      HISTAR;   //  HISTAR 的标志  带HI=1, 否则=0
//};
//
//struct HXG_ {
//	char Code[16];    //  截面的标准尺寸 (高度X宽度)
//	char   NAME[16];   // 型号
//	int       H;      // 尺寸 h     单位 mm
//	int       B;      // 尺寸 b     单位 mm
//	float          Tw;     // 尺寸 tw    单位 mm
//	float          Tf;     // 尺寸 t     单位 mm
//	float          R;      // 尺寸 r     单位 mm
//	float          A;      // 截面面积 A 单位 cm
//	float          W;      // 每米重量   单位 kg/m
//	//  Ix,Iy           截面惯性矩  单位 cm
//	//  Wx,Wy           截面抵抗矩  单位 cm
//	//  Sx              半截面面积矩 单位 cm
//	//  Ix1,Iy1         截面回转半径 单位 cm
//	// x,y 轴 为形心轴
//	float          Ix;
//	float          Wx;
//	float          Ix1;
//	float          Iy;
//	float          Wy;
//	float          Iy1;
//};
//
//struct CIRCLE_{
//	char  NAME[16];   // 型号 直径
//	int       D;
//	float          A;
//	float          I;
//	float          I1;
//	float          W;
//	float          G;
//};
//
//struct Tube {
//	char  NAME[16];   // 型号 d X t
//	int       d;
//	float          t;
//	float          A;
//	float          I;
//	float          I1;
//	float          W;
//	float          G;
//};
//
//struct RectTube_ {
//	char  NAME[16];   // 型号 d X t
//	int       h;
//	int       b;
//	float          t;
//	float          A;
//	float          Ix;
//	float          Ix1;
//	float          Wx;
//	float          Iy;
//	float          Iy1;
//	float          Wy;
//	float          G;
//};
//
//
//struct ThinC {
//	char   NAME[16];   // 型号 h*b*t
//	int       h;
//	int       b;
//	int       a;
//	float          t;
//	float          AA;
//	float          G;
//	float          X0;
//	float          Ix;
//	float          Ix1;
//	float          Wx;
//	float          Iy;
//	float          Iy1;
//	float          Wymax;
//	float          Wymin;
//	float          IIy1;
//	float          e0;
//	float          It;
//	float          Iw;
//	float          k;
//	float          Ww1;
//	float          Ww2;
//	float          Uy;
//};
//
//struct ThinZ_ {
//	char   NAME[16];   // 型号 h*b*t
//	int       h;
//	int       b;
//	int       a;
//	float          t;
//	float          AA;
//	float          G;
//	float          CT;
//	float          IIx;
//	float          IIx1;
//	float          WWx1;
//	float          IIy;
//	float          IIy1;
//	float          WWy1;
//	float          Ix;
//	float          Ix1;
//	float          Wx1;
//	float          Wx2;
//	float          Iy;
//	float          Iy1;
//	float          Wy1;
//	float          Wy2;
//	float          Ix1y1;
//	float          It;
//	float          Iw;
//	float          k;
//	float          Ww1;
//	float          Ww2;
//};
//
//struct  ThinL {
//	char  NAME[16];   // 型号
//	int       B;
//	int       A;
//	float          T;
//	float          AA;
//	float          G;
//	float          y0;
//	float          Ix0;
//	float          Wx0max;
//	float          Wx0min;
//	float          Ix10;
//	float          Ix;
//	float          Ix1;
//	float          Iy;
//	float          Iy1;
//	float          IIx1;
//	float          e0;
//	float          It;
//	float          Iw;
//	float          Uy;
//};
//
//struct HFWHXG_{ // 高频焊接轻型H型钢     2000.6.26
//	char NAME[16];	//型号
//	int No;
//	int H;			//尺寸 h     单位 mm
//	int B1;			//尺寸 b1    单位 mm  下翼缘宽度
//	int B2;			//尺寸 b2    单位 mm  上翼缘宽度
//	float Tw;		//尺寸 tw    单位 mm
//	float Tf;		//尺寸 t     单位 mm
//	float A;		//截面面积 A 单位 cm
//};
//
//#pragma pack(2)
//struct STEEL{
//	int TotalSteelType;
//	struct SteelType_ SteelType[21];
//	int INDEX_[22];
//	char NAME[1500][16];
//	struct GongGang_ GongGang[200] ;
//	struct JiaoGang_ JiaoGang[100];
//	struct BJiaoGang_ BJiaoGang[100];
//	struct CaoGang_ CaoGang[200];
//	struct HE_ HE[200];
//	struct JIS_ JIS[100];
//	struct AmericanW USAW[200];
//	struct HXG_ HXG[150];
//	struct CIRCLE_ CIRCLE[60];
//	struct Tube BoxTube[30];
//	struct Tube CircleTube1[400];
//	struct Tube CircleTube2[200];
//	struct ThinC ThinC1[20];
//	struct ThinC ThinC2[20];
//	struct ThinZ_ ThinZ[20];
//	struct RectTube_ RectTube[100];
//	struct ThinL ThinL1[20];
//	struct ThinL ThinL2[20];
//	struct HFWHXG_ HFWHXG[80];
//};
//#pragma pack()
//
//struct SINGLESTEEL{
//	int Kind;
//	int Type;
//	char NAME[16];	// 型号
//	struct GongGang_ GongGang;
//	struct JiaoGang_ JiaoGang;
//	struct BJiaoGang_ BJiaoGang;
//	struct CaoGang_ CaoGang;
//	struct HE_ HE;
//	struct JIS_ JIS;
//	struct AmericanW USAW;
//	struct HXG_ HXG;
//	struct CIRCLE_ CIRCLE;
//	struct Tube BoxTube;
//	struct Tube CircleTube1;
//	struct Tube CircleTube2;
//	struct ThinC ThinC1;
//	struct ThinC ThinC2;
//	struct ThinZ_ ThinZ;
//	struct RectTube_ RectTube;
//	struct ThinL ThinL1;
//	struct ThinL ThinL2;
//	struct HFWHXG_ HFWHXG;
//};

#endif
