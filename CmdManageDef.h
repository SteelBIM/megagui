#include <wxlCmdMngrKnl.h> //�������������ͷ�ļ�

#ifndef _CMD_MANAGE_DEF_H_
#define _CMD_MANAGE_DEF_H_
	
////������ģ���־
//#define MOD_MODEL_GEN		0	//��ģģ��
//#define MOD_ANALYSE			1	//��ģ����ģ��
//#define MOD_JC_DESN			2	//�������ģ��
//#define MOD_SLAB_DESN		3	//¥�����ģ��
//#define MOD_DRAWING_DESN	4	//ʩ��ͼ���ģ��
//
////��ģ���־
////����ģ��Ϊ��MOD_MODEL_GEN��ʱ
//#define MODSUB_PMCAD		0	//PMCAD��ģ
//#define MODSUB_SPAS			1	//�ռ�㽨ģ
//������ģ���־
#ifndef  MOD_MODEL_MACRO
#define MOD_MODEL_MACRO

#define MOD_MODEL_GEN		0	//��ģģ��
#define MOD_PRJ_DSN			1	//�������ģ��
#define MOD_ANALYSE			2	//��ģ����ģ��
#define MOD_JC_DESN			3	//�������ģ��
#define MOD_SLAB_DESN		4	//¥�����ģ��
#define MOD_DRAWING_DESN	5	//ʩ��ͼ���ģ��
#define MOD_EPDA			6	//EPDAģ��
#define MOD_PUSH			7	//PUSHģ��
#define MOD_STS_DRAW_DESN	8	//�ֽṹʩ��ͼ���ģ��
#define MOD_PMSAP_DESN	    9	//PMSAP������ƣ���ǰ����
#define MOD_SPAS_GEN	    10	//SpasCAD
#define MOD_SAUSAGE_DESN	11	//SAUSAGE
#define MOD_STSPK_DESN	    12	//�ֽṹ����
#define MOD_TOOLS_DESN	    13	//���߼�
#define MOD_STWJ_DESN	    14	//����������
#define MOD_STWJZT_DESN	    15	//����������������
#define MOD_QITI_DESN	    16	//�������
#define MOD_QITI_DK_DESN	17	//�׿����
#define MOD_QITI_PJ_DESN	18	//����������
#define MOD_STAT_DESN	    19	//����������
#define MOD_CONPK_DESN	    20	//������PK
#define MOD_STSJDJG_DESN	21	//�ֽṹ�����ӹ�
#define MOD_STSMJ3D_DESN	22	//�żܳ�����ά
#define MOD_STSPJ3D_DESN	23	//�żܳ�����ά

#define MOD_LTCAD_DESN		24	//¥��CAD

#define MOD_ANALYSE_POST	25	//��ģ����ģ��-����
#define MOD_PMSAP_POST	    26	//PMSAP����

#define MOD_PMCADTOPK_DESN	27	//PMCADģ��תPK�ļ�
#define MOD_SAUSAGE_CHK_DESN	28	//SAUSAGE_CHK
#define MOD_JDJG_CONDRAW_DESN 29	//�����������ӹ�ʩ��ͼ
#define MOD_STJG            30   //�ֽṹ�ӹ�
#define MOD_QITI_JDJG_DESN	31	//��������ӹ�

#define MOD_PREC2D_DESN		32	//PREC2D
#define MOD_PREC3D_ANAPRE	39	//PREC3D-ANAPRE
#define MOD_PREC3D_DESN		33	//PREC3D
#define MOD_PREC3D_ANAPOST	34	//PREC3D-ANAPOST
#define MOD_PREC3D_PRECPOST	35	//PREC3D-PRECPOST

#define MOD_QITI_DK_POST	36	//�׿���ƺ���
#define MOD_QITI_PJ_POST	37	//���������ƺ���
#define MOD_QITI_JDJG_POST	38	//��������ӹ̺���
#define MOD_DRAWING_CHECK   40  //ʩ��ͼ���

#define MOD_SPAS_CSHCAD		 51  //ʩ��ͼ���
#endif  // MOD_MODEL_MACRO



// ���Դ�=0x00010 ��ʼ����
static const DWORD CMT_PUMPFUNC			=0x0001B;  
//��ͼģ������������Ľӿ�,���磺���Դ���һ��void*[2],����0Ϊ�������ַ���,1Ϊ�˺���ָ��,DY 070115
static const DWORD CMT_PRETRANMSG		=0x0001F;  //PreTranslateMessage ��Ϣ
static const DWORD CMT_LBUTTONDOWN		=0x00020;  //������������Ϣ
static const DWORD CMT_LBUTTONUP		=0x00021;	//������̧��
static const DWORD CMT_RBUTTONDOWN		=0x00022;  //����Ҽ�������Ϣ
static const DWORD CMT_RBUTTONUP		=0x00023;  //����Ҽ�̧����Ϣ
static const DWORD CMT_LBUTTONDBLCLK	=0x00024;  //˫����������Ϣ
static const DWORD CMT_MOUSEMOVE		=0x00025;  //����ƶ���Ϣ

static const DWORD CMT_KEYDOWN			=0x00030;  //����������Ϣ
static const DWORD CMT_KEYUP			=0x00031;  //����̧����Ϣ
static const DWORD CMT_CHAR				=0x00032;  //�ַ���Ϣ
static const DWORD CMT_RIBBONCHGMENU	=0x00033;  //Ribbon�л�һ���˵���Ϣ
static const DWORD CMT_RIBBONCHGMENUBEFORE	=0x00034;  //Ribbon�л�һ���˵���Ϣ֮ǰ���ж�̬���ж��Ƿ��ܹ��л���
static const DWORD CMT_STATUSRBCLICK	=  0x00035;  //statusbar �Ҽ���Ϣ�����¼���

static const DWORD CMT_CONFOCT			=0x00051;	//���ĵ���ǩ��ȡ��Ϣ
static const DWORD CMT_BEFORECOMMAND	=0x00052;	//COMMAND����ִ��ǰ��Ϣ
static const DWORD CMT_POPCOMMAND		=0x00053;	//�Ҽ������˵�����ִ��ǰ��Ϣ
static const DWORD CMT_TIPMESSAGE		=0x00054;	//tip��Ϣ
//static const DWORD CMT_MENUEXPAND		=0x00027;	//�˵�չ�������۵�����Ϣ
//static const DWORD CMT_INITJCPM			=0x00028;	//����ƽ��˵�������Ϣ ê˨����ͼ/׮λƽ��ͼ
static const DWORD CMT_AFTERMENUCHANGE	=0x00055;	//�˵��仯�󴫵���Ϣ��
static const DWORD CMT_CONTEXTMENU		=0x00056;	//�Ҽ������˵���Ϣ��
static const DWORD CMT_METHODCHANGED    =0x00057;	//MethodChanged  �����仯��Ϣ
static const DWORD CMT_CREATEMENUCOMBO  =0x00058;	//CreateMenuCombo  �����б��˵���Ϣ
static const DWORD CMT_CHKPINPMESSAGE   =0x00059;	//CHKPINP��Ϣ
static const DWORD CMT_WREDRAWMESSAGE   =0x00060;	//WREDRAW��Ϣ  �ػ��Ի���ͼ�δ��ڵ�����
static const DWORD CMT_COMBITMMESSAGE   =0x00061;	//COMBITM��Ϣ  �趨��Ͽ�ѡ��������
static const DWORD CMT_USERDRWMESSAGE   =0x00062;	//USERDRW��Ϣ  ����USERDRW
static const DWORD CMT_REDRWMESSAGE	    =0x00063;	//REDRW��Ϣ
static const DWORD CMT_DLGHIDEMESSAGE	    =0x00064;	//DLGHIDE��Ϣ

static const DWORD CMT_USER				=0x00500;  //�û��Զ�����Ϣ���Ƽ���CMT_USER+1,CMT_USER+2...����ʽ���崦��
static const DWORD CMT_INITJCPM			=0x00502;	//������ʼ����Ϣ

static const DWORD CMT_STS_JD_MAIN		=0x00601;	//�ڵ�ʩ��ͼ���Ի���
static const DWORD CMT_STS_GJ_MAIN		=0x00602;	//����ʩ��ͼ���Ի���
static const DWORD CMT_STS_SJT_MAIN		=0x00603;	//���ͼ���Ի���
static const DWORD CMT_STXT_MAIN		=0x00604;	//��ͼ������Ի���
static const DWORD CMT_STS_DESN_MAIN	=0x00605;	//�ڵ�������Ի���
static const DWORD CMT_STXT_DLL_CMD		=0x00606;	//��̬���з�������Ϣ
static const DWORD CMT_STXT_CHG_LAYER	=0x00607;	//����¥����Ϣ
static const DWORD CMT_STXT_OUT_CMD		=0x00608;	//��Ϣ����ϵͳ�ⲿ
static const DWORD CMT_STXT_EXIT_CMD	=0x00609;	//�˳�������������
static const DWORD CMT_XTTOOL_MAIN		=0x00610;	//��ͼ���������Ի���
static const DWORD CMT_XTKJ_DRWSEL		=0x00611;	//KJ3DDraw��DrawSelGj������Ϣ
static const DWORD CMT_STXT_REDW_CMD	=0x00612;	//��ͼ�ػ�����
static const DWORD CMT_PKPM_MAIN		=0x00613;	//PKPMMain�����
static const DWORD CMT_CHANG_PANAL_COMB	=0x00614;	//�л����Ͻ�PANAL��Comb�ؼ�


static const DWORD CMT_SPAS_RUN_CMD		=0x00701;	//STS_SPAS����ִ��
static const DWORD CMT_SPAS_SAVE_CMD	=0x00702;	//STS_SPAS�����ļ���Ϣ
static const DWORD CMT_SPAS_LOAD_CMD	=0x00703;	//STS_SPASװ���ļ���Ϣ
static const DWORD CMT_SPAS_GENDB_CMD	=0x00704;	//STS_SPAS������ͼ���ݿ���Ϣ

static const DWORD CMT_PMCAD_RUN_CMD	=0x00801;	//PMCAD����������ִ��
static const DWORD CMT_PMCAD_LBUTTONDOWN_VIEW  =0x00802;	//PMCAD mouse left down view
static const DWORD CMT_PMCAD_LBUTTONUP_VIEW  =0x00803;	//PMCAD mouse left up view
static const DWORD CMT_PMCAD_COMBLST	=0x00806;	//PMCAD������COMBLST
static const DWORD CMT_COMMAND_PARA     =0x00807;	//������ָ�������CMT_COMMAND����
static const DWORD CMT_PLATFORM_DLL_COMMAND     =0x00809;	//��̬���нӹ�ƽ̨�¿������

static const DWORD CMT_ANA_INIT			=0x00903;	//��ʼ����Ϣ
static const DWORD CMT_ANA_MAIN_INIT	=0x00904;	//
static const DWORD CMT_ANA_MAIN_QUIT	=0x00905;	//
static const DWORD CMT_ANA_QUIT				=0x00906;	//��ʼ����Ϣ
static const DWORD CMT_ANA_DLL_BEFORECMD	=0x00909;	//����ִ��ǰ��Ϣ
static const DWORD CMT_ANA_CHANGEMODEL	    =0x00913;	//�л���ģ��
static const DWORD CMT_ANA_UPDATE_MODEL		=0x00914;	//�л���ģ��
static const DWORD CMT_ANA_REG_CMD_CB		=0x00915;	//ע������Ļص������������ַ���С������
static const DWORD CMT_ANA_SHOW_HELP		=0x00916;	//��ʾ�����ĵ���Ŀ

//��ֹ��ϵͳ��������Ϣ��ͻ
//��Χ 0x00500 - 0x00FFF

#endif //_CMD_MANAGE_DEF_H_
