#ifndef __COMMON__ 
#define __COMMON__
#pragma pack(1)

const int DIV_LOG = 8;					 // 对数格数
const int DIV_LINE = 10;				 // 线性格数
const int TRACE_POINT = 501;			 // 扫描点数
const int EVS_POINT = 401;
const int STAT_POINT = /*600*/480;		 // 统计图点数


const INT64 N64_Hz = 1L;
const INT64 N64_KHz = 1000L;
const INT64 N64_MHz = 1000L*1000L;
const INT64 N64_GHz = 1000L*1000L*1000L;

const INT64 N64_DAY = 24*60*60*1000L;
const INT64 N64_HOUR = 60*60*1000L;
const INT64 N64_MINUTE = 60*1000L;
const INT64 N64_SEC = 1000L;
const INT64 N64_MSEC = 1L;

// 颜色定义
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

//	工作模式
const CString CS_SA_POWER = _T("CS_SA_POWER");			//通道功率测量
const CString CS_SA_ADJ = _T("CS_SA_ADJ");				//邻道功率测量
const CString CS_SA_OCC = _T("CS_SA_OCC");				//占用带宽测量
const CString CS_SA_FM = _T("CS_SA_FM");				//FM检波方式
const CString CS_SA = _T("CS_SA");						//普通频谱模式
const CString CS_SA_WIN = _T("CS_SA_WIN");				//双窗测量

const CString CS_DVBC_CONSTELL = _T("CS_DVBC_CONSTELL");//DVBC下的星座图
const CString CS_DTMB_CONSTELL = _T("CS_DTMB_CONSTELL");//DTMB下的星座图
const CString CS_DVBC_STAT = _T("CS_DVBC_STAT");		//DVBC下的传统统计图
const CString CS_DVBC_EQU = _T("CS_DVBC_EQU");			//DVBC下的均衡器
const CString CS_DVBC_IMPULSE = _T("CS_DVBC_IMPULSE");	//DVBC下的突发监测
const CString CS_DVBC_NOISE = _T("CS_DVBC_NOISE");		//DVBC下的EVS

const CString CS_ATV_FCC = _T("CS_ATV_FCC");			//FCC
//const CString CS_ATV_SCAN = _T("CS_ATV_SCAN");			//扫描频道
const CString CS_ATV_SCAN = _T("CS_ATV_SCAN");						//标准扫描频道
const CString CS_ATV_SCAN_ANALOG = _T("CS_ATV_SCAN_ANALOG");		//模拟扫描频道
const CString CS_ATV_SCAN_DIGITAL = _T("CS_ATV_SCAN_DIGITAL");		//数字扫描频道
const CString CS_ATV_SCAN_FAV = _T("CS_ATV_SCAN_FAV");				//友好扫描频道

const CString CS_ATV_LISTEN = _T("CS_ATV_LISTEN");		//伴音监听
const CString CS_ATV_FMDEV = _T("CS_ATV_FMDEV");		//伴音频偏
const CString CS_ATV_CARRLF = _T("CS_ATV_CARRLF");		//载波电平幅度
const CString CS_ATV_MOD = _T("CS_ATV_MOD");			//图像调制度
const CString CS_ATV_CCN = _T("CS_ATV_CCN");			//载噪比
const CString CS_ATV_HUM = _T("CS_ATV_HUM");			//哼声调制
const CString CS_ATV_CROSS = _T("CS_ATV_CROSS");		//交扰调制
const CString CS_ATV_CTBCSO = _T("CS_ATV_CTBCSO");		//差拍干扰
const CString CS_ATV_LEAK = _T("CS_ATV_LEAK");			//泄漏
const CString CS_ATV_CLDI = _T("CS_ATV_CLDI");			//色亮时延差
const CString CS_ATV_DGDP = _T("CS_ATV_DGDP");			//微分增益/相位 
const CString CS_ATV_RESP = _T("CS_ATV_RESP");			//带内频响
const CString CS_ATV = _T("CS_ATV");					//catv模式下，未进行任何测量
const CString CS_UNKNOWN = _T("CS_UNKNOWN");			//未知状态, 错误

//CString STR_DLS = _T("");

enum VConsoleMode 
{
	MODE_SPEC = 0,				// 频谱分析
	MODE_DTV = 3,				// 数字电视
	MODE_CATV = 1,				// 有线电视
	MODE_EQU = 5,				// 均衡器
	MODE_CHSCAN = 100,			// 频道扫描模式
	MODE_DTV_STAT = 101,		// 统计图模式
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


	MODE_FCC,					// 系统测量
	MODE_HISTORY				// 历史记录
};

enum MEA_MODE				// 测量方式
{
	MEA_LOG = 1,
	MEA_LIN = 0
};

enum UNIT_MODE
{
	UNIT_UNTURN = 0,		// 未变化
	UNIT_LOG,				// 单位为对数
	UNIT_LIN				// 单位为线性
};


enum Quad 
{						// 象限
	Quad_1 = 0,
	Quad_2,
	Quad_3,
	Quad_4
};

enum ConsMode
{					// 星座图模式
	MODE_CONS_CONTINUE,
	MODE_CONS_CYCLIC,
	MODE_CONS_TIMERFILITER
};


// 波形数据存储结构	
struct tagWaveData 
{			
	int		iLogLine;			// 对数或线性
	int		iPowerUnit;			// 对数或线性单位
	double	dRef;				// 参考电平
	double	dAmpDiv;			// DB/格
	INT64	lCF;				// 中频
	INT64	lSpan;				// 带宽
	INT64	lFStart;			// 起始频率
	INT64	lFStop;				// 终止频率
	long	lRBW;				// RBW
	long	lVBW;				// VBW
	INT64	lSweep;				// 扫描时间
	long	lAtt;				// 衰减器
	int		nDeteor;			// 检波方式
	float	fData[TRACE_POINT];	// 波形数据存储空间
	int		bAmplifier;			// 放大器
};	

struct tagAssist 
{
	bool	bMaxHoldOn;		// 最大保持开
	bool	bMinHoldOn;		// 最小保持开
	char	cReserve[48];
};     // 辅助功能

struct tagKCHead 
{
	char cVer[10];		// 版本
	double dMaxHold[TRACE_POINT];
	double dMinHold[TRACE_POINT];
};

struct tagKCData
{
	CTime tKCDate;
	tagWaveData WaveData;
};

// 选件信息
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