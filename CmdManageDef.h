#include <wxlCmdMngrKnl.h> //插件管理器核心头文件

#ifndef _CMD_MANAGE_DEF_H_
#define _CMD_MANAGE_DEF_H_
	
////主调用模块标志
//#define MOD_MODEL_GEN		0	//建模模块
//#define MOD_ANALYSE			1	//建模分析模块
//#define MOD_JC_DESN			2	//基础设计模块
//#define MOD_SLAB_DESN		3	//楼板设计模块
//#define MOD_DRAWING_DESN	4	//施工图设计模块
//
////子模块标志
////当主模块为“MOD_MODEL_GEN”时
//#define MODSUB_PMCAD		0	//PMCAD建模
//#define MODSUB_SPAS			1	//空间层建模
//主调用模块标志
#ifndef  MOD_MODEL_MACRO
#define MOD_MODEL_MACRO

#define MOD_MODEL_GEN		0	//建模模块
#define MOD_PRJ_DSN			1	//方案设计模块
#define MOD_ANALYSE			2	//建模分析模块
#define MOD_JC_DESN			3	//基础设计模块
#define MOD_SLAB_DESN		4	//楼板设计模块
#define MOD_DRAWING_DESN	5	//施工图设计模块
#define MOD_EPDA			6	//EPDA模块
#define MOD_PUSH			7	//PUSH模块
#define MOD_STS_DRAW_DESN	8	//钢结构施工图设计模块
#define MOD_PMSAP_DESN	    9	//PMSAP分析设计（含前后处理）
#define MOD_SPAS_GEN	    10	//SpasCAD
#define MOD_SAUSAGE_DESN	11	//SAUSAGE
#define MOD_STSPK_DESN	    12	//钢结构厂房
#define MOD_TOOLS_DESN	    13	//工具集
#define MOD_STWJ_DESN	    14	//网架设计软件
#define MOD_STWJZT_DESN	    15	//整体分析与网架设计
#define MOD_QITI_DESN	    16	//砌体设计
#define MOD_QITI_DK_DESN	17	//底框设计
#define MOD_QITI_PJ_DESN	18	//配筋砌体设计
#define MOD_STAT_DESN	    19	//混凝土算量
#define MOD_CONPK_DESN	    20	//混凝土PK
#define MOD_STSJDJG_DESN	21	//钢结构鉴定加固
#define MOD_STSMJ3D_DESN	22	//门架厂房三维
#define MOD_STSPJ3D_DESN	23	//排架厂房三维

#define MOD_LTCAD_DESN		24	//楼梯CAD

#define MOD_ANALYSE_POST	25	//建模分析模块-后处理
#define MOD_PMSAP_POST	    26	//PMSAP后处理

#define MOD_PMCADTOPK_DESN	27	//PMCAD模型转PK文件
#define MOD_SAUSAGE_CHK_DESN	28	//SAUSAGE_CHK
#define MOD_JDJG_CONDRAW_DESN 29	//混凝土鉴定加固施工图
#define MOD_STJG            30   //钢结构加固
#define MOD_QITI_JDJG_DESN	31	//砌体鉴定加固

#define MOD_PREC2D_DESN		32	//PREC2D
#define MOD_PREC3D_ANAPRE	39	//PREC3D-ANAPRE
#define MOD_PREC3D_DESN		33	//PREC3D
#define MOD_PREC3D_ANAPOST	34	//PREC3D-ANAPOST
#define MOD_PREC3D_PRECPOST	35	//PREC3D-PRECPOST

#define MOD_QITI_DK_POST	36	//底框设计后处理
#define MOD_QITI_PJ_POST	37	//配筋砌体设计后处理
#define MOD_QITI_JDJG_POST	38	//砌体鉴定加固后处理
#define MOD_DRAWING_CHECK   40  //施工图审查

#define MOD_SPAS_CSHCAD		 51  //施工图审查
#endif  // MOD_MODEL_MACRO



// 可以从=0x00010 开始定义
static const DWORD CMT_PUMPFUNC			=0x0001B;  
//绘图模块输出自身函数的接口,例如：可以传出一个void*[2],其中0为函数名字符串,1为此函数指针,DY 070115
static const DWORD CMT_PRETRANMSG		=0x0001F;  //PreTranslateMessage 消息
static const DWORD CMT_LBUTTONDOWN		=0x00020;  //鼠标左键按下消息
static const DWORD CMT_LBUTTONUP		=0x00021;	//鼠标左键抬起
static const DWORD CMT_RBUTTONDOWN		=0x00022;  //鼠标右键按下消息
static const DWORD CMT_RBUTTONUP		=0x00023;  //鼠标右键抬起消息
static const DWORD CMT_LBUTTONDBLCLK	=0x00024;  //双击鼠标左键消息
static const DWORD CMT_MOUSEMOVE		=0x00025;  //鼠标移动消息

static const DWORD CMT_KEYDOWN			=0x00030;  //按键按下消息
static const DWORD CMT_KEYUP			=0x00031;  //按键抬起消息
static const DWORD CMT_CHAR				=0x00032;  //字符消息
static const DWORD CMT_RIBBONCHGMENU	=0x00033;  //Ribbon切换一级菜单消息
static const DWORD CMT_RIBBONCHGMENUBEFORE	=0x00034;  //Ribbon切换一级菜单消息之前，有动态库判断是否能够切换。
static const DWORD CMT_STATUSRBCLICK	=  0x00035;  //statusbar 右键消息处理事件。

static const DWORD CMT_CONFOCT			=0x00051;	//多文档标签点取消息
static const DWORD CMT_BEFORECOMMAND	=0x00052;	//COMMAND命令执行前消息
static const DWORD CMT_POPCOMMAND		=0x00053;	//右键弹出菜单命令执行前消息
static const DWORD CMT_TIPMESSAGE		=0x00054;	//tip消息
//static const DWORD CMT_MENUEXPAND		=0x00027;	//菜单展开（或折叠）消息
//static const DWORD CMT_INITJCPM			=0x00028;	//基础平面菜单加载消息 锚栓布置图/桩位平面图
static const DWORD CMT_AFTERMENUCHANGE	=0x00055;	//菜单变化后传递消息，
static const DWORD CMT_CONTEXTMENU		=0x00056;	//右键弹出菜单消息，
static const DWORD CMT_METHODCHANGED    =0x00057;	//MethodChanged  画法变化消息
static const DWORD CMT_CREATEMENUCOMBO  =0x00058;	//CreateMenuCombo  创建列表框菜单消息
static const DWORD CMT_CHKPINPMESSAGE   =0x00059;	//CHKPINP消息
static const DWORD CMT_WREDRAWMESSAGE   =0x00060;	//WREDRAW消息  重画对话框图形窗口的内容
static const DWORD CMT_COMBITMMESSAGE   =0x00061;	//COMBITM消息  设定组合框选择表的内容
static const DWORD CMT_USERDRWMESSAGE   =0x00062;	//USERDRW消息  重载USERDRW
static const DWORD CMT_REDRWMESSAGE	    =0x00063;	//REDRW消息
static const DWORD CMT_DLGHIDEMESSAGE	    =0x00064;	//DLGHIDE消息

static const DWORD CMT_USER				=0x00500;  //用户自定义消息，推荐以CMT_USER+1,CMT_USER+2...的形式定义处理，
static const DWORD CMT_INITJCPM			=0x00502;	//基础初始化消息

static const DWORD CMT_STS_JD_MAIN		=0x00601;	//节点施工图主对话框
static const DWORD CMT_STS_GJ_MAIN		=0x00602;	//构件施工图主对话框
static const DWORD CMT_STS_SJT_MAIN		=0x00603;	//设计图主对话框
static const DWORD CMT_STXT_MAIN		=0x00604;	//详图设计主对话框
static const DWORD CMT_STS_DESN_MAIN	=0x00605;	//节点设计主对话框
static const DWORD CMT_STXT_DLL_CMD		=0x00606;	//动态库中发出的消息
static const DWORD CMT_STXT_CHG_LAYER	=0x00607;	//更换楼层消息
static const DWORD CMT_STXT_OUT_CMD		=0x00608;	//消息来自系统外部
static const DWORD CMT_STXT_EXIT_CMD	=0x00609;	//退出交互界面命令
static const DWORD CMT_XTTOOL_MAIN		=0x00610;	//详图工具箱主对话框
static const DWORD CMT_XTKJ_DRWSEL		=0x00611;	//KJ3DDraw的DrawSelGj发出消息
static const DWORD CMT_STXT_REDW_CMD	=0x00612;	//详图重画命令
static const DWORD CMT_PKPM_MAIN		=0x00613;	//PKPMMain主框架
static const DWORD CMT_CHANG_PANAL_COMB	=0x00614;	//切换右上角PANAL的Comb控件


static const DWORD CMT_SPAS_RUN_CMD		=0x00701;	//STS_SPAS命令执行
static const DWORD CMT_SPAS_SAVE_CMD	=0x00702;	//STS_SPAS保存文件消息
static const DWORD CMT_SPAS_LOAD_CMD	=0x00703;	//STS_SPAS装载文件消息
static const DWORD CMT_SPAS_GENDB_CMD	=0x00704;	//STS_SPAS生成详图数据库消息

static const DWORD CMT_PMCAD_RUN_CMD	=0x00801;	//PMCAD主程序命令执行
static const DWORD CMT_PMCAD_LBUTTONDOWN_VIEW  =0x00802;	//PMCAD mouse left down view
static const DWORD CMT_PMCAD_LBUTTONUP_VIEW  =0x00803;	//PMCAD mouse left up view
static const DWORD CMT_PMCAD_COMBLST	=0x00806;	//PMCAD主程序COMBLST
static const DWORD CMT_COMMAND_PARA     =0x00807;	//带两个指针参数的CMT_COMMAND命令
static const DWORD CMT_PLATFORM_DLL_COMMAND     =0x00809;	//动态库中接管平台下快捷命令

static const DWORD CMT_ANA_INIT			=0x00903;	//初始化消息
static const DWORD CMT_ANA_MAIN_INIT	=0x00904;	//
static const DWORD CMT_ANA_MAIN_QUIT	=0x00905;	//
static const DWORD CMT_ANA_QUIT				=0x00906;	//初始化消息
static const DWORD CMT_ANA_DLL_BEFORECMD	=0x00909;	//命令执行前消息
static const DWORD CMT_ANA_CHANGEMODEL	    =0x00913;	//切换多模型
static const DWORD CMT_ANA_UPDATE_MODEL		=0x00914;	//切换多模型
static const DWORD CMT_ANA_REG_CMD_CB		=0x00915;	//注册命令的回调函数，比如字符大小，换层
static const DWORD CMT_ANA_SHOW_HELP		=0x00916;	//显示帮助文档条目

//防止与系统公共的消息冲突
//范围 0x00500 - 0x00FFF

#endif //_CMD_MANAGE_DEF_H_
