#include <string>
#include "steellib.h"
#include "DrawSectPic.h"

extern "C" __declspec( dllimport )  void STEEL_SECT_DEFINE(
	int &idel,						// 1 Cancel,0 OK
struct SECTIONS& CRS);			// ��׼��������

extern "C" __declspec( dllimport )  void STS_StdSteelSect_Define_Ex(const int &iType, struct SECTION1 &SECT, short gSect[], int &IDel);

extern "C" __declspec( dllimport )  void STS_SIN_SECT_DEFINE(
	int &idel,						// 1 OK,0 Cancel 
struct SECTIONS& CRS,
struct SECTIONS& BRC);