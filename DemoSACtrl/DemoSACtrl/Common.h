#ifndef __COMMON__ 
#define __COMMON__
#pragma pack(1)

const int DIV_LOG = 8;					 // ��������
const int DIV_LINE = 10;				 // ���Ը���
const int TRACE_POINT = 501;			 // ɨ�����
const int EVS_POINT = 401;
const int STAT_POINT = /*600*/480;		 // ͳ��ͼ����


const INT64 N64_Hz = 1L;
const INT64 N64_KHz = 1000L;
const INT64 N64_MHz = 1000L*1000L;
const INT64 N64_GHz = 1000L*1000L*1000L;

const INT64 N64_DAY = 24*60*60*1000L;
const INT64 N64_HOUR = 60*60*1000L;
const INT64 N64_MINUTE = 60*1000L;
const INT64 N64_SEC = 1000L;
const INT64 N64_MSEC = 1L;

// ��ɫ����
#define UD_RED					RGB(255,0,0)
#define UD_GREEN				RGB(0,255,0) 
#define UD_BLUE					RGB(0,0,225)
#define UD_YELLOW				RGB(255,255,0)
#define UD_ORANGE				RGB(255,153,51)
#define UD_HOT_PINK				RGB(255,51,153)
#define UD_PURPLE				RGB(153,0,204)
#define UD_CYAN					RGB(0,255,255)
#define UD_BLACK				RGB(0,0,0)
#define UD_WHITE				RGB(255,255,255)
#define UD_LAVENDER				RGB(199,177,255)
#define UD_PEACH				RGB(255,226,177)
#define UD_SKY_BLUE				RGB(142,255,255)
#define UD_FOREST_GREEN			RGB(0,192,0)
#define UD_BROWN				RGB(80,50,0)
#define UD_TURQUOISE			RGB(0,192,192)
#define UD_ROYAL_BLUE			RGB(0,0,192)
#define UD_GREY					RGB(192,192,192)
#define UD_DARK_GREY			RGB(128,128,128)
#define UD_TAN					RGB(255,198,107)
#define UD_DARK_BLUE			RGB(0,0,128)
#define UD_MAROON				RGB(128,0,0)
#define UD_DUSK					RGB(255,143,107)
#define UD_LIGHT_GREY			RGB(225,225,225)	//only for 3D graph lines	
#define UD_EQUALIZER			RGB(220, 220, 220)
#define UD_DRAKISH				RGB(50, 50, 50)		//2009-8-31 liuhuijun
#define UD_BOTTLE_GREEN			RGB(45, 170, 90)	//RGB(30, 95, 40)	//RGB(45, 185, 95)
#define UD_WINE_RED				RGB(80, 0, 0)
#define UD_LARK_GREY			RGB(235,235,225)

//#define PI 3.14

enum USER_MESSAGE
{
	UM_MRK_OFF = WM_USER+100,
	UM_MRK_ON,
	UM_MRK_ACTIVE
};

//	����ģʽ
const CString CS_SA_POWER = _T("CS_SA_POWER");			//ͨ�����ʲ���
const CString CS_SA_ADJ = _T("CS_SA_ADJ");				//�ڵ����ʲ���
const CString CS_SA_OCC = _T("CS_SA_OCC");				//ռ�ô������
const CString CS_SA_FM = _T("CS_SA_FM");				//FM�첨��ʽ
const CString CS_SA = _T("CS_SA");						//��ͨƵ��ģʽ
const CString CS_SA_WIN = _T("CS_SA_WIN");				//˫������

const CString CS_DVBC_CONSTELL = _T("CS_DVBC_CONSTELL");//DVBC�µ�����ͼ
const CString CS_DTMB_CONSTELL = _T("CS_DTMB_CONSTELL");//DTMB�µ�����ͼ
const CString CS_DVBC_STAT = _T("CS_DVBC_STAT");		//DVBC�µĴ�ͳͳ��ͼ
const CString CS_DVBC_EQU = _T("CS_DVBC_EQU");			//DVBC�µľ�����
const CString CS_DVBC_IMPULSE = _T("CS_DVBC_IMPULSE");	//DVBC�µ�ͻ�����
const CString CS_DVBC_NOISE = _T("CS_DVBC_NOISE");		//DVBC�µ�EVS

const CString CS_ATV_FCC = _T("CS_ATV_FCC");			//FCC
//const CString CS_ATV_SCAN = _T("CS_ATV_SCAN");			//ɨ��Ƶ��
const CString CS_ATV_SCAN = _T("CS_ATV_SCAN");						//��׼ɨ��Ƶ��
const CString CS_ATV_SCAN_ANALOG = _T("CS_ATV_SCAN_ANALOG");		//ģ��ɨ��Ƶ��
const CString CS_ATV_SCAN_DIGITAL = _T("CS_ATV_SCAN_DIGITAL");		//����ɨ��Ƶ��
const CString CS_ATV_SCAN_FAV = _T("CS_ATV_SCAN_FAV");				//�Ѻ�ɨ��Ƶ��

const CString CS_ATV_LISTEN = _T("CS_ATV_LISTEN");		//��������
const CString CS_ATV_FMDEV = _T("CS_ATV_FMDEV");		//����Ƶƫ
const CString CS_ATV_CARRLF = _T("CS_ATV_CARRLF");		//�ز���ƽ����
const CString CS_ATV_MOD = _T("CS_ATV_MOD");			//ͼ����ƶ�
const CString CS_ATV_CCN = _T("CS_ATV_CCN");			//�����
const CString CS_ATV_HUM = _T("CS_ATV_HUM");			//��������
const CString CS_ATV_CROSS = _T("CS_ATV_CROSS");		//���ŵ���
const CString CS_ATV_CTBCSO = _T("CS_ATV_CTBCSO");		//���ĸ���
const CString CS_ATV_LEAK = _T("CS_ATV_LEAK");			//й©
const CString CS_ATV_CLDI = _T("CS_ATV_CLDI");			//ɫ��ʱ�Ӳ�
const CString CS_ATV_DGDP = _T("CS_ATV_DGDP");			//΢������/��λ 
const CString CS_ATV_RESP = _T("CS_ATV_RESP");			//����Ƶ��
const CString CS_ATV = _T("CS_ATV");					//catvģʽ�£�δ�����κβ���
const CString CS_UNKNOWN = _T("CS_UNKNOWN");			//δ֪״̬, ����

//CString STR_DLS = _T("");

enum VConsoleMode 
{
	MODE_SPEC = 0,				// Ƶ�׷���
	MODE_DTV = 3,				// ���ֵ���
	MODE_CATV = 1,				// ���ߵ���
	MODE_EQU = 5,				// ������
	MODE_CHSCAN = 100,			// Ƶ��ɨ��ģʽ
	MODE_DTV_STAT = 101,		// ͳ��ͼģʽ
	MODE_EVS = 102,				// EVS

	MODE_CATV_FMDEV,
	MODE_CATV_HUM,
	MODE_CATV_DEPTHMOD,
	MODE_CATV_LEAKAGE,
	MODE_CATV_CROSS,
	MODE_CATV_CARRIER,
	MODE_CATV_CN,
	MODE_CATV_CSOCTB,
	MODE_CATV_CLDI,
	MODE_CATV_DGDP,
	MODE_CATV_RESP,


	MODE_FCC,					// ϵͳ����
	MODE_HISTORY				// ��ʷ��¼
};

enum MEA_MODE				// ������ʽ
{
	MEA_LOG = 1,
	MEA_LIN = 0
};

enum UNIT_MODE
{
	UNIT_UNTURN = 0,		// δ�仯
	UNIT_LOG,				// ��λΪ����
	UNIT_LIN				// ��λΪ����
};


enum Quad 
{						// ����
	Quad_1 = 0,
	Quad_2,
	Quad_3,
	Quad_4
};

enum ConsMode
{					// ����ͼģʽ
	MODE_CONS_CONTINUE,
	MODE_CONS_CYCLIC,
	MODE_CONS_TIMERFILITER
};


// �������ݴ洢�ṹ	
struct tagWaveData 
{			
	int		iLogLine;			// ����������
	int		iPowerUnit;			// ���������Ե�λ
	double	dRef;				// �ο���ƽ
	double	dAmpDiv;			// DB/��
	INT64	lCF;				// ��Ƶ
	INT64	lSpan;				// ����
	INT64	lFStart;			// ��ʼƵ��
	INT64	lFStop;				// ��ֹƵ��
	long	lRBW;				// RBW
	long	lVBW;				// VBW
	INT64	lSweep;				// ɨ��ʱ��
	long	lAtt;				// ˥����
	int		nDeteor;			// �첨��ʽ
	float	fData[TRACE_POINT];	// �������ݴ洢�ռ�
	int		bAmplifier;			// �Ŵ���
};	

struct tagAssist 
{
	bool	bMaxHoldOn;		// ��󱣳ֿ�
	bool	bMinHoldOn;		// ��С���ֿ�
	char	cReserve[48];
};     // ��������

struct tagKCHead 
{
	char cVer[10];		// �汾
	double dMaxHold[TRACE_POINT];
	double dMinHold[TRACE_POINT];
};

struct tagKCData
{
	CTime tKCDate;
	tagWaveData WaveData;
};

// ѡ����Ϣ
struct tagOpt
{
	bool IsCatv;
	bool IsQam;
	bool IsGate;
	bool IsRBW;
	bool IsNet;
	bool IsDTMB;
	bool IsVSB;
	bool IsDVBT;
	bool IsImpulse;
};

struct sa_frame {
	int nDataLen;
	float fData[501];
};

#endif