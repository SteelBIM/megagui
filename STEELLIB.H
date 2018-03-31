
#ifndef _STEELLIB_H
#define _STEELLIB_H

#define NSECTION_ 500
#pragma pack(2)
struct SECTIONS {			// STS-2 SECTION colum and beam
         short   KIND;
         char  NAME[16];
		 char  NAME1[16];   // ���͸ֽ�������� ��I25a��
         short   B1,B2;
         short   H1,H2;
         short   B3,H3;
         short   T1,T2,T3,T4;
         short   T5,T6;
         short   M;    //  ��������, 5 Ϊ������, 6 Ϊ�ֲ���
         float  RI;         // ��(��)���򳤶�(��)  �� YH ֻ��IK=4
         float  RJ;         // ��(��)���򳤶�(��)  �� YL
         float  UA;         // ���в�����ϵ��
};

struct PK11_SECT {			// STS-2 pk11�����е���������ṹ
         short   KIND;
         char  NAME[16];
		 char  NAME1[16];   // ���͸ֽ�������� ��I25a��
         short   B1,B2;
         short   H1,H2;
         short   B3,H3;
         short   T1,T2,T3,T4;
         short   T5,T6;
         short   M;    //  ��������, 5 Ϊ������, 6 Ϊ�ֲ���
         float  RI;         // ��(��)���򳤶�(��)  �� YH ֻ��IK=4
         float  RJ;         // ��(��)���򳤶�(��)  �� YL
         float  UA;         // ���в�����ϵ��

         float  Xc,Yc;      // ������������   ��λ m
         float  Rx, Ry;     // �Ըֽṹ����Ľ������Է�չϵ��
         // �Ըֽṹ�����ǿ�����ֵ, ����,ѹ,��Ϳ��� KN/m*m
         float  Fy, Fv;  //  Fv = Fy/ SQRT(3)
         float  W1x,W2x;    // ����ĵֿ��� x ����, �� y ����
         float  W1y,W2y;    //
         short	TypeX;  // �Ըֽṹ������ѹ�����Ľ������1=a,2=b,3=c
         short	TypeY;  // �Ըֽṹ������ѹ�����Ľ������1=a,2=b,3=c
         float  Rc;         // �Ա�׼�͸ֽ���Ϊ��Ե�븹�����ӵĻ��ν��ǰ뾶
                          // �Ժ��ӽ���Ϊ���ųߴ�
};
struct SteelType_{
	int No;       //  �����͸ֵ���Ŀ,���ֻ����100��
	int Type;     //  �͸ֵ���� = 1  �����ȱ߽Ǹ�
                    //           = 2  �������ȱ߽Ǹ�
                    //           = 3  ������ͨ���ָ�
                    //           = 4  �������͹��ָ�
                    //           = 5  ������ͨ�۸�
                    //           = 6  �������Ͳ۸�
					//           = 7  ŷ�ޱ�׼����ԵH�͸� European wide flange beams
					//           = 8  �ձ���׼����ԵH�͸� JIS wide falnge beams
					//           = 9  ������׼����ԵH�͸� American wide flange beams
	char NAME[40];  //  �͸ֵ�����
	int MaxLen;    //  �͸��ַ�������󳤶�
};
          
struct  JiaoGang_{    // ������ͨ�����ͽǸֵȱ߽���
	char NAME[16];  //�ͺ�
	int B;      // �ߴ� b     ��λ mm
	int T;      // �ߴ� t     ��λ mm
	float R;      // �ߴ� r     ��λ mm
	float A;      // ������� A ��λ cm��
	float W;      // ÿ������   ��λ kg/m
	float X0;     // ��������   ��λ mm
           //  Ix             x-x�� ������Ծ�  ��λ cm��
           //  Wxmax,Wxmin    x-x�� ����ֿ���  ��λ cm��
           //  Ix1            x-x�� �����ת�뾶 ��λ cm
	float Ix,Wxmax,Wxmin,Ix1;
           //  Iu             u-u�� ������Ծ�  ��λ cm��
           //  Wu             u-u�� ����ֿ���  ��λ cm��
           //  Iu1            u-u�� �����ת�뾶 ��λ cm
	float Iu,Wu,Iu1;
           //  Iv             v-v�� ������Ծ�  ��λ cm��
           //  Wvmax,Wvmin    v-v�� ����ֿ���  ��λ cm��
           //  Iv1            v-v�� �����ת�뾶 ��λ cm
	float Iv,Wvmax,Wvmin,Iv1;
           //  IIx1  x1-x1�� ������Ծ�  ��λ cm��
	float IIx1;
};

struct BJiaoGang_{    // ������ͨ�����Ͳ��ȱ߽Ǹֽ���
	char NAME[16]; // �ͺ�
	int B1;		   // �ߴ� B     ��λ mm
	int B;      // �ߴ� b     ��λ mm
	int T;      // �ߴ� t     ��λ mm
	float R;      // �ߴ� r     ��λ mm
	float A;      // ������� A ��λ cm��
	float W;      // ÿ������   ��λ kg/m
	float X0;     // ��������   ��λ mm
	float Y0;     // ��������   ��λ mm
           //  Ix             x-x�� ������Ծ�  ��λ cm��
           //  Wxmax,Wxmin    x-x�� ����ֿ���  ��λ cm��
           //  Ix1            x-x�� �����ת�뾶 ��λ cm
	float Ix,Wxmax,Wxmin,Ix1;
           //  Iy             y-y�� ������Ծ�  ��λ cm��
           //  Wymay,Wymin    y-y�� ����ֿ���  ��λ cm��
           //  Iy1            y-y�� �����ת�뾶 ��λ cm
	float Iy,Wymax,Wymin,Iy1;
           //  IIx1  x1-x1�� ������Ծ�  ��λ cm��
	float IIx1;
           //  IIy1  y1-y1�� ������Ծ�  ��λ cm��
	float IIy1;
           //  Iv             v-v�� ������Ծ�  ��λ cm��
           //  Wv             v-v�� ����ֿ���  ��λ cm��
           //  Iv1            v-v�� �����ת�뾶 ��λ cm
	float Iv,Wv,Iv1;
	float TAN;
};

struct GongGang_{    // ������ͨ�����͹��ָֽ���
	char NAME[16];	// �ͺ�
	int H;			// �ߴ� h     ��λ mm
	int B;      // �ߴ� b     ��λ mm
	float Tw;     // �ߴ� tw    ��λ mm
	float T;      // �ߴ� t     ��λ mm
	float R;      // �ߴ� r     ��λ mm
	float R1;     // �ߴ� r1    ��λ mm
	float A;      // ������� A ��λ cm��
    float W;      // ÿ������   ��λ kg/m
           //  Ix,Iy           ������Ծ�  ��λ cm��
           //  Wx,Wy           ����ֿ���  ��λ cm��
           //  Sx              ���������� ��λ cm��
           //  Ix1,Iy1         �����ת�뾶 ��λ cm
           // x,y �� Ϊ������
	float          Ix;
	float          Wx;
	float          Sx;
	float          Ix1;
	float          Iy;
	float          Wy;
	float          Iy1;
};

struct CaoGang_{    // ������ͨ�����Ͳ۸ֽ���
	char NAME[16];   // �ͺ�
	int       H;      // �ߴ� h     ��λ mm
	int       B;      // �ߴ� b     ��λ mm
	float          Tw;     // �ߴ� tw    ��λ mm
	float          T;      // �ߴ� t     ��λ mm
	float          R;      // �ߴ� r     ��λ mm
	float          R1;     // �ߴ� r1    ��λ mm
	float          A;      // ������� A ��λ cm��
	float          W;      // ÿ������   ��λ kg/m
	float          X0;     // ��������   ��λ mm
	//  Ix,Iy,IIy1      ������Ծ�  ��λ cm��
	//  Wx,Wymax,Wymin  ����ֿ���  ��λ cm��
	//  Sx              ���������� ��λ cm��
	//  Ix1,Iy1         �����ת�뾶 ��λ cm
	// x,y �� Ϊ������, IIy1 �Խ����
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


struct JIS_ {    //  �ձ���׼����ԵH�͸�
	char Code[16];    //  ����ı�׼�ߴ� (�߶�X����)
	char NAME[16];    //  �����ѡ������ ( H x B )
	int   H;          //  ����ĸ߶�  mm
	int   B;          //  ����Ŀ���  mm
	float      t1;         //  ������    mm
	float      t2;         //  ��Ե���    mm
	float      r;          //  ��Ե�븹������ת�ǰ뾶  mm
	float      A;          //  �������� cm*cm
	float      W;          //  ����ľ��� kg/m
	//  Ix,Iy           ������Ծ�  ��λ cm**4
	//  Wx,Wy           ����ֿ���  ��λ cm**3
	//  Ix1,Iy1         �����ת�뾶 ��λ cm
	// x,y �� Ϊ������
	float          Ix;
	float          Wx;
	float          Ix1;
	float          Iy;
	float          Wy;
	float          Iy1;
};


struct HE_ {    //  ŷ�ޱ�׼����ԵH�͸�
	char NAME[16];    //  �������������
	char NAME1[16];
	int   H;          //  ����ĸ߶�  mm
	int   B;          //  ����Ŀ���  mm
	float      tw;         //  ������    mm
	float      tf;         //  ��Ե���    mm
	float      r;          //  ��Ե�븹������ת�ǰ뾶  mm
	float      A;          //  �������� cm*cm
	float      W;          //  ����ľ��� kg/m
	//  Iy,Iz           ������Ծ�  ��λ cm**4
	//  Wy,Wz           ����ֿ���  ��λ cm**3
	//  Iy1,Iz1         �����ת�뾶 ��λ cm
	// y,z �� Ϊ������  (�൱�ڱ�׼��x,y��)
	float          Iy;
	float          Wy;
	float          Wply;    //   ��Ե�븹�����Ӵ��Ľ���ֿ���  ??
	float          Iy1;
	float          Avz;     //   ����� cm*cm
	float          Iz;
	float          Wz;
	float          Wplz;    //  ******
	float          Iz1;
	//   ϸ���ߴ�
	int       hi;      //  ���徻�߶�           mm
	int       d;       //  ����ȥת�Ǻ�ľ��߶� mm
	int      BD;      //  ��˨��ֱ�� (����)
	int      Pmin1;    //  ��Ե�Ͽ׾����Сֵ1 mm
	int      Pmin2;    //  ��Ե�Ͽ׾����Сֵ2 mm
	int      Pmax;     //  ��Ե�Ͽ׾�����ֵ  mm
	float         AL;       //  ����� m*m /m
	float         AG;       //  ����� m*m /t
	float         Ss;
	float         It;
	float         Iw;       //  Ťת���Ծ� ??
	//  ���� ENV1993-1-1
	int      S235w;    //  ���� Y-Y
	int      S355w;    //  ���� Y-Y
	int      S460w;    //  ���� Y-Y
	int      S235y;    //  ��ѹ
	int      S355y;    //  ��ѹ
	int      S460y;    //  ��ѹ
	int      HISTAR;   //  HISTAR �ı�־  ��HI =1, ����= 0
};

struct AmericanW_ {    //  ������׼����ԵH�͸�
	char NAME[16];    //  ������������� ��λ mm
	char NAME1[16];   //  ������������� ��λ inch
	int   H;          //  ����ĸ߶�  mm
	int   B;          //  ����Ŀ���  mm
	float      tw;         //  ������    mm
	float      tf;         //  ��Ե���    mm
	float      r;          //  ��Ե�븹������ת�ǰ뾶  mm
	float      A;          //  �������� cm*cm
	float      W;          //  ����ľ��� kg/m
	//  Iy,Iz           ������Ծ�  ��λ cm**4
	//  Wy,Wz           ����ֿ���  ��λ cm**3
	//  Iy1,Iz1         �����ת�뾶 ��λ cm
	// y,z �� Ϊ������  (�൱�ڱ�׼��x,y��)
	float          Iy;
	float          Wy;
	float          Wply;    //   ��Ե�븹�����Ӵ��Ľ���ֿ���  ??
	float          Iy1;
	float          Avz;     //   ����� cm*cm
	float          Iz;
	float          Wz;
	float          Wplz;    //  ******
	float          Iz1;
	//   ϸ���ߴ�
	int       hi;      //  ���徻�߶�           mm
	int       d;       //  ����ȥת�Ǻ�ľ��߶� mm
	int       BD;      //  ��˨��ֱ�� (����)
	int      Pmin1;    //  ��Ե�Ͽ׾����Сֵ1 mm
	int      Pmin2;    //  ��Ե�Ͽ׾����Сֵ2 mm
	int      Pmax;     //  ��Ե�Ͽ׾�����ֵ  mm
	float         AL;       //  ����� m*m /m
	float         AG;       //  ����� m*m /t
	float         Ss;
	float         It;
	float         Iw;       //  Ťת���Ծ� ??
	//  ���� ENV1993-1-1
	int      S235w;    //  ���� Y-Y
	int      S355w;    //  ���� Y-Y
	int      S460w;    //  ���� Y-Y
	int      S235y;    //  ��ѹ
	int      S355y;    //  ��ѹ
	int      S460y;    //  ��ѹ
	int      HISTAR;   //  HISTAR �ı�־  ��HI=1, ����=0
};

struct HXG_ {
	char   Code[16];    //  ����ı�׼�ߴ� (�߶�X����)
	char   NAME[16];   // �ͺ�
	int       H;      // �ߴ� h     ��λ mm
	int       B;      // �ߴ� b     ��λ mm
	float          Tw;     // �ߴ� tw    ��λ mm
	float          Tf;     // �ߴ� t     ��λ mm
	float          R;      // �ߴ� r     ��λ mm
	float          A;      // ������� A ��λ cm��
	float          W;      // ÿ������   ��λ kg/m
	//  Ix,Iy           ������Ծ�  ��λ cm��
	//  Wx,Wy           ����ֿ���  ��λ cm��
	//  Sx              ���������� ��λ cm��
	//  Ix1,Iy1         �����ת�뾶 ��λ cm
	// x,y �� Ϊ������
	float          Ix;
	float          Wx;
	float          Ix1;
	float          Iy;
	float          Wy;
	float          Iy1;
};

struct CIRCLE_{
	char  NAME[16];   // �ͺ� ֱ��
	int       D;
	float          A;
	float          I;
	float          I1;
	float          W;
	float          G;
};

struct Tube_ {
	char  NAME[16];   // �ͺ� d X t
	int       d;
	float          t;
	float          A;
	float          I;
	float          I1;
	float          W;
	float          G;
};

struct RectTube_ {
	char  NAME[16];   // �ͺ� d X t
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
	char   NAME[16];   // �ͺ� h*b*t
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
	char   NAME[16];   // �ͺ� h*b*t
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
	char  NAME[16];   // �ͺ�
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

struct HFWHXG_{ // ��Ƶ��������H�͸�     2000.6.26
	char NAME[16];	//�ͺ�
	int No;
	int H;			//�ߴ� h     ��λ mm
	int B1;			//�ߴ� b1    ��λ mm  ����Ե����
	int B2;			//�ߴ� b2    ��λ mm  ����Ե����
	float Tw;		//�ߴ� tw    ��λ mm
	float Tf;		//�ߴ� t     ��λ mm
	float A;		//������� A ��λ cm��
};

struct BFT_ {		// ���겿��T�͸�
	char   Code[16];    //  ����ı�׼�ߴ� (�߶�X����)
	char   NAME[16];   // �ͺ�
	float          H;      // �ߴ� h     ��λ mm
	float          B;      // �ߴ� b     ��λ mm
	float          Tw;     // �ߴ� tw    ��λ mm
	float          Tf;     // �ߴ� t     ��λ mm
	float          R;      // �ߴ� r     ��λ mm
	float          A;      // ������� A ��λ cm��
	float          W;      // ÿ������   ��λ kg/m
	//  Ix,Iy           ������Ծ�  ��λ cm��
	//  Wx,Wy           ����ֿ���  ��λ cm��
	//  Sx              ���������� ��λ cm��
	//  Ix1,Iy1         �����ת�뾶 ��λ cm
	// x,y �� Ϊ������
	float          Ix;
	float          Wx;
	float          Ix1;
	float          Iy;
	float          Wy;
	float          Iy1;
	float          Cx;
};

struct ThinBJG_{    // ���䱡�ڲ��ȱ߽Ǹ�
	char NAME[16]; // �ͺ�
	int B1;		   // �ߴ� B     ��λ mm
	int B;      // �ߴ� b     ��λ mm
	float T;      // �ߴ� t     ��λ mm
	float R;      // �ߴ� r     ��λ mm
	float A;      // ������� A ��λ cm��
	float W;      // ÿ������   ��λ kg/m
	float X0;     // ��������   ��λ mm
	float Y0;     // ��������   ��λ mm
           //  Ix             x-x�� ������Ծ�  ��λ cm��
           //  Wxmax,Wxmin    x-x�� ����ֿ���  ��λ cm��
           //  Ix1            x-x�� �����ת�뾶 ��λ cm
	float Ix,Wxmax,Wxmin,Ix1;
           //  Iy             y-y�� ������Ծ�  ��λ cm��
           //  Wymay,Wymin    y-y�� ����ֿ���  ��λ cm��
           //  Iy1            y-y�� �����ת�뾶 ��λ cm
	float Iy,Wymax,Wymin,Iy1;
           //  IIx1  x1-x1�� ������Ծ�  ��λ cm��
	float IIx1;
           //  IIy1  y1-y1�� ������Ծ�  ��λ cm��
	float IIy1;
           //  Iv             v-v�� ������Ծ�  ��λ cm��
           //  Wv             v-v�� ����ֿ���  ��λ cm��
           //  Iv1            v-v�� �����ת�뾶 ��λ cm
	float Iv,Wv,Iv1;
	float TAN;
};

struct CWHXG_ {		//���Ƹ���H�͸ֱ�
	char   NAME[16];  // �ͺ�
	int       H;      // �ߴ� h     ��λ mm
	int       B;      // �ߴ� b     ��λ mm
	float     Tw;     // �ߴ� tw    ��λ mm
	float     Tf;     // �ߴ� t     ��λ mm
	float		  A;      // ������� A ��λ cm��
	float     Af;     // 2����Ե��� 2Af ��λ cm��
	float     Aw;     // ������� Aq ��λ cm��
	float     W;      // ÿ������   ��λ kg/m
	float       Ix;
	float       Wx;
	float       Ix1;
	float       Iy;
	float       Wy;
	float       Iy1;
	float       It;
	float       Iw;
	int         B2;     //���Գƽ�������Ե�������     
	float      Tf2;
	float        M;    //���������
	int       BX_b;    // ���β���
	int       BX_d;
	int       BX_q;
	float     BX_s;
};

struct BWHXG_ {		//���˸���H�͸ֱ�
	char   NAME[16];  // �ͺ�
	int       H;      // �ߴ� h     ��λ mm
	int       B;      // �ߴ� b     ��λ mm
	float     Tw;     // �ߴ� tw    ��λ mm
	float     Tf;     // �ߴ� t     ��λ mm
	float		  A;      // ������� A ��λ cm��
	float     Af;     // 2����Ե��� 2Af ��λ cm��
	float     Aw;     // ������� Aq ��λ cm��
	float     W;      // ÿ������   ��λ kg/m
	float       Ix;
	float       Wx;
	float       Ix1;
	float       Iy;
	float       Wy;
	float       Iy1;
	float       It;
	float       Iw;
	int         H2;     //���Գƽ�������Ե�������     
	int         B2;
	float      Tf2;
	int       BX_a;    // ���β���
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
	char NAME[16];	// �ͺ�
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
            char  NAME[16];   //   ��׼�͸ֽ�������  97.5
			//short IGZZ;       // ���������
            short B1;         //   ��׼�͸ֽ�������  USE FOR COLUM
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
            char  NAME[16];   //   ��׼�͸ֽ�������  97.5
            short B1;         //   ��׼�͸ֽ�������  USE FOR COLUM
			int   ID;
};

//
//struct SteelType_{
//	int No;       //  �����͸ֵ���Ŀ,���ֻ����100��
//	int Type;     //  �͸ֵ���� = 1  �����ȱ߽Ǹ�
//                    //            //             = 2  �������ȱ߽Ǹ�
//                    //            //             = 3  ������ͨ���ָ�
//                    //            //             = 4  �������͹��ָ�
//                    //            //             = 5  ������ͨ�۸�
//                    //            //             = 6  �������Ͳ۸�
//					//           = 7  ŷ�ޱ�׼����ԵH�͸� European wide flange beams
//					//           = 8  �ձ���׼����ԵH�͸� JIS wide falnge beams
//					//           = 9  ������׼����ԵH�͸� American wide flange beams
//	char NAME[40];  //  �͸ֵ�����
//	int MaxLen;    //  �͸��ַ�������󳤶�
//};
//          
//struct  JiaoGang_{    // ������ͨ�����ͽǸֵȱ߽���
//	char NAME[16];  //�ͺ�
//	int B;      // �ߴ� b     ��λ mm
//	int T;      // �ߴ� t     ��λ mm
//	float R;      // �ߴ� r     ��λ mm
//	float A;      // ������� A ��λ cm��
//	float W;      // ÿ������   ��λ kg/m
//	float X0;     // ��������   ��λ mm
//           //  Ix             x-x�� ������Ծ�  ��λ cm��
//           //  Wxmax,Wxmin    x-x�� ����ֿ���  ��λ cm��
//           //  Ix1            x-x�� �����ת�뾶 ��λ cm
//	float Ix,Wxmax,Wxmin,Ix1;
//           //  Iu             u-u�� ������Ծ�  ��λ cm��
//           //  Wu             u-u�� ����ֿ���  ��λ cm��
//           //  Iu1            u-u�� �����ת�뾶 ��λ cm
//	float Iu,Wu,Iu1;
//           //  Iv             v-v�� ������Ծ�  ��λ cm��
//           //  Wvmax,Wvmin    v-v�� ����ֿ���  ��λ cm��
//           //  Iv1            v-v�� �����ת�뾶 ��λ cm
//	float Iv,Wvmax,Wvmin,Iv1;
//           //  IIx1  x1-x1�� ������Ծ�  ��λ cm��
//	float IIx1;
//};
//
//struct BJiaoGang_{    // ������ͨ�����Ͳ��ȱ߽Ǹֽ���
//	char NAME[16]; // �ͺ�
//	int B1;		   // �ߴ� B     ��λ mm
//	int B;      // �ߴ� b     ��λ mm
//	int T;      // �ߴ� t     ��λ mm
//	float R;      // �ߴ� r     ��λ mm
//	float A;      // ������� A ��λ cm��
//	float W;      // ÿ������   ��λ kg/m
//	float X0;     // ��������   ��λ mm
//	float Y0;     // ��������   ��λ mm
//           //  Ix             x-x�� ������Ծ�  ��λ cm��
//           //  Wxmax,Wxmin    x-x�� ����ֿ���  ��λ cm��
//           //  Ix1            x-x�� �����ת�뾶 ��λ cm
//	float Ix,Wxmax,Wxmin,Ix1;
//           //  Iy             y-y�� ������Ծ�  ��λ cm��
//           //  Wymay,Wymin    y-y�� ����ֿ���  ��λ cm��
//           //  Iy1            y-y�� �����ת�뾶 ��λ cm
//	float Iy,Wymax,Wymin,Iy1;
//           //  IIx1  x1-x1�� ������Ծ�  ��λ cm��
//	float IIx1;
//           //  IIy1  y1-y1�� ������Ծ�  ��λ cm��
//	float IIy1;
//           //  Iv             v-v�� ������Ծ�  ��λ cm��
//           //  Wv             v-v�� ����ֿ���  ��λ cm��
//           //  Iv1            v-v�� �����ת�뾶 ��λ cm
//	float Iv,Wv,Iv1;
//	float TAN;
//};
//
//struct GongGang_{    // ������ͨ�����͹��ָֽ���
//	char NAME[16];	// �ͺ�
//	int H;			// �ߴ� h     ��λ mm
//	int B;      // �ߴ� b     ��λ mm
//	float Tw;     // �ߴ� tw    ��λ mm
//	float T;      // �ߴ� t     ��λ mm
//	float R;      // �ߴ� r     ��λ mm
//	float R1;     // �ߴ� r1    ��λ mm
//	float A;      // ������� A ��λ cm��
//    float W;      // ÿ������   ��λ kg/m
//           //  Ix,Iy           ������Ծ�  ��λ cm��
//           //  Wx,Wy           ����ֿ���  ��λ cm��
//           //  Sx              ���������� ��λ cm��
//           //  Ix1,Iy1         �����ת�뾶 ��λ cm
//           // x,y �� Ϊ������
//	float          Ix;
//	float          Wx;
//	float          Sx;
//	float          Ix1;
//	float          Iy;
//	float          Wy;
//	float          Iy1;
//};
//
//struct CaoGang_{    // ������ͨ�����Ͳ۸ֽ���
//	char NAME[16];   // �ͺ�
//	int       H;      // �ߴ� h     ��λ mm
//	int       B;      // �ߴ� b     ��λ mm
//	float          Tw;     // �ߴ� tw    ��λ mm
//	float          T;      // �ߴ� t     ��λ mm
//	float          R;      // �ߴ� r     ��λ mm
//	float          R1;     // �ߴ� r1    ��λ mm
//	float          A;      // ������� A ��λ cm��
//	float          W;      // ÿ������   ��λ kg/m
//	float          X0;     // ��������   ��λ mm
//	//  Ix,Iy,IIy1      ������Ծ�  ��λ cm��
//	//  Wx,Wymax,Wymin  ����ֿ���  ��λ cm��
//	//  Sx              ���������� ��λ cm��
//	//  Ix1,Iy1         �����ת�뾶 ��λ cm
//	// x,y �� Ϊ������, IIy1 �Խ����
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
//struct JIS_ {    //  �ձ���׼����ԵH�͸�
//	char Code[16];    //  ����ı�׼�ߴ� (�߶�X����)
//	char NAME[16];    //  �����ѡ������ ( H x B )
//	int   H;          //  ����ĸ߶�  mm
//	int   B;          //  ����Ŀ���  mm
//	float      t1;         //  ������    mm
//	float      t2;         //  ��Ե���    mm
//	float      r;          //  ��Ե�븹������ת�ǰ뾶  mm
//	float      A;          //  �������� cm*cm
//	float      W;          //  ����ľ��� kg/m
//	//  Ix,Iy           ������Ծ�  ��λ cm**4
//	//  Wx,Wy           ����ֿ���  ��λ cm**3
//	//  Ix1,Iy1         �����ת�뾶 ��λ cm
//	// x,y �� Ϊ������
//	float          Ix;
//	float          Wx;
//	float          Ix1;
//	float          Iy;
//	float          Wy;
//	float          Iy1;
//};
//
//
//struct HE_ {    //  ŷ�ޱ�׼����ԵH�͸�
//	char NAME[16];    //  �������������
//	char NAME1[16];
//	int   H;          //  ����ĸ߶�  mm
//	int   B;          //  ����Ŀ���  mm
//	float      tw;         //  ������    mm
//	float      tf;         //  ��Ե���    mm
//	float      r;          //  ��Ե�븹������ת�ǰ뾶  mm
//	float      A;          //  �������� cm*cm
//	float      W;          //  ����ľ��� kg/m
//	//  Iy,Iz           ������Ծ�  ��λ cm**4
//	//  Wy,Wz           ����ֿ���  ��λ cm**3
//	//  Iy1,Iz1         �����ת�뾶 ��λ cm
//	// y,z �� Ϊ������  (�൱�ڱ�׼��x,y��)
//	float          Iy;
//	float          Wy;
//	float          Wply;    //   ��Ե�븹�����Ӵ��Ľ���ֿ���  ??
//	float          Iy1;
//	float          Avz;     //   ����� cm*cm
//	float          Iz;
//	float          Wz;
//	float          Wplz;    //  ******
//	float          Iz1;
//	//   ϸ���ߴ�
//	int       hi;      //  ���徻�߶�           mm
//	int       d;       //  ����ȥת�Ǻ�ľ��߶� mm
//	int      BD;      //  ��˨��ֱ�� (����)
//	int      Pmin1;    //  ��Ե�Ͽ׾����Сֵ1 mm
//	int      Pmin2;    //  ��Ե�Ͽ׾����Сֵ2 mm
//	int      Pmax;     //  ��Ե�Ͽ׾�����ֵ  mm
//	float         AL;       //  ����� m*m /m
//	float         AG;       //  ����� m*m /t
//	float         Ss;
//	float         It;
//	float         Iw;       //  Ťת���Ծ� ??
//	//  ���� ENV1993-1-1
//	int      S235w;    //  ���� Y-Y
//	int      S355w;    //  ���� Y-Y
//	int      S460w;    //  ���� Y-Y
//	int      S235y;    //  ��ѹ
//	int      S355y;    //  ��ѹ
//	int      S460y;    //  ��ѹ
//	int      HISTAR;   //  HISTAR �ı�־  ��HI =1, ����= 0
//};
//
//struct AmericanW {    //  ������׼����ԵH�͸�
//	char NAME[16];    //  ������������� ��λ mm
//	char NAME1[16];   //  ������������� ��λ inch
//	int   H;          //  ����ĸ߶�  mm
//	int   B;          //  ����Ŀ���  mm
//	float      tw;         //  ������    mm
//	float      tf;         //  ��Ե���    mm
//	float      r;          //  ��Ե�븹������ת�ǰ뾶  mm
//	float      A;          //  �������� cm*cm
//	float      W;          //  ����ľ��� kg/m
//	//  Iy,Iz           ������Ծ�  ��λ cm**4
//	//  Wy,Wz           ����ֿ���  ��λ cm**3
//	//  Iy1,Iz1         �����ת�뾶 ��λ cm
//	// y,z �� Ϊ������  (�൱�ڱ�׼��x,y��)
//	float          Iy;
//	float          Wy;
//	float          Wply;    //   ��Ե�븹�����Ӵ��Ľ���ֿ���  ??
//	float          Iy1;
//	float          Avz;     //   ����� cm*cm
//	float          Iz;
//	float          Wz;
//	float          Wplz;    //  ******
//	float          Iz1;
//	//   ϸ���ߴ�
//	int       hi;      //  ���徻�߶�           mm
//	int       d;       //  ����ȥת�Ǻ�ľ��߶� mm
//	int       BD;      //  ��˨��ֱ�� (����)
//	int      Pmin1;    //  ��Ե�Ͽ׾����Сֵ1 mm
//	int      Pmin2;    //  ��Ե�Ͽ׾����Сֵ2 mm
//	int      Pmax;     //  ��Ե�Ͽ׾�����ֵ  mm
//	float         AL;       //  ����� m*m /m
//	float         AG;       //  ����� m*m /t
//	float         Ss;
//	float         It;
//	float         Iw;       //  Ťת���Ծ� ??
//	//  ���� ENV1993-1-1
//	int      S235w;    //  ���� Y-Y
//	int      S355w;    //  ���� Y-Y
//	int      S460w;    //  ���� Y-Y
//	int      S235y;    //  ��ѹ
//	int      S355y;    //  ��ѹ
//	int      S460y;    //  ��ѹ
//	int      HISTAR;   //  HISTAR �ı�־  ��HI=1, ����=0
//};
//
//struct HXG_ {
//	char Code[16];    //  ����ı�׼�ߴ� (�߶�X����)
//	char   NAME[16];   // �ͺ�
//	int       H;      // �ߴ� h     ��λ mm
//	int       B;      // �ߴ� b     ��λ mm
//	float          Tw;     // �ߴ� tw    ��λ mm
//	float          Tf;     // �ߴ� t     ��λ mm
//	float          R;      // �ߴ� r     ��λ mm
//	float          A;      // ������� A ��λ cm��
//	float          W;      // ÿ������   ��λ kg/m
//	//  Ix,Iy           ������Ծ�  ��λ cm��
//	//  Wx,Wy           ����ֿ���  ��λ cm��
//	//  Sx              ���������� ��λ cm��
//	//  Ix1,Iy1         �����ת�뾶 ��λ cm
//	// x,y �� Ϊ������
//	float          Ix;
//	float          Wx;
//	float          Ix1;
//	float          Iy;
//	float          Wy;
//	float          Iy1;
//};
//
//struct CIRCLE_{
//	char  NAME[16];   // �ͺ� ֱ��
//	int       D;
//	float          A;
//	float          I;
//	float          I1;
//	float          W;
//	float          G;
//};
//
//struct Tube {
//	char  NAME[16];   // �ͺ� d X t
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
//	char  NAME[16];   // �ͺ� d X t
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
//	char   NAME[16];   // �ͺ� h*b*t
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
//	char   NAME[16];   // �ͺ� h*b*t
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
//	char  NAME[16];   // �ͺ�
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
//struct HFWHXG_{ // ��Ƶ��������H�͸�     2000.6.26
//	char NAME[16];	//�ͺ�
//	int No;
//	int H;			//�ߴ� h     ��λ mm
//	int B1;			//�ߴ� b1    ��λ mm  ����Ե����
//	int B2;			//�ߴ� b2    ��λ mm  ����Ե����
//	float Tw;		//�ߴ� tw    ��λ mm
//	float Tf;		//�ߴ� t     ��λ mm
//	float A;		//������� A ��λ cm��
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
//	char NAME[16];	// �ͺ�
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