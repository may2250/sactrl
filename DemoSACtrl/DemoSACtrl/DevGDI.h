// deskland 仪器波形数据显示类, GDI方式, 版本: 1.58.44
// designed by deskland@msn.com
// Final edit time at: 2010-06-07
// history: 2008-02-25 1.20		增加mkr横向属性，左侧和居中两个属性
//			2008-02-28 1.20.26	修正纵坐标值过大或过小飞出绘图区外
//			2008-03-21 1.21		增加鼠标选择操纵频标的功能
//			2008-03-26 1.22		增加活动频标颜色单独控制功能
//			2008-04-18 1.23		增加绘图区上方自定义显示文字共5组,包含标题,分隔符,内容.
//			2008-04-21 1.24		增加绘制竖条，中间无间隔，绘图属性：N_HORBAR_NO_SEP
//			2008-04-24 1.25.27	增加自定义显示Y轴坐标文字功能
//			2008-04-24 1.26		增加自定义mkr值的显示功能
//			2008-04-28 1.26.28	修正竖条显示属性丢失数据的问题
//			2008-04-29 1.26.29	修正数据在最小值时无法显示问题
//			2008-04-30 1.27		增加将当前波形保存为图像文件的功能
//			2008-05-06 1.27.30	修正绘图N_HORBAR_NO_SEP属性的纵坐标误差
//			2008-05-07 1.27.31	修正绘图N_HORBAR_NO_SEP属性的纵坐标误差(第2，3条线)
//			2008-05-07 1.28		增加N_HORBAR_NO_SEP_ENABLE_MIN绘图属性，显示绘图坐标最小值，N_HORBAR_NO_SEP改为不显示绘图坐标最小值
//			2008-06-10 1.29.32	增加绘图波形数量到14条
//			2008-06-11 1.30		增加绘图接口2维指针描述
//			2008-06-12 1.31		增加绘图波形数量到20条
//			2008-06-23 1.32.33	增加打印报表波形数量到20条，并且支持设置打印字体和大小
//			2008-07-31 1.33		增加Mkr在不同波形曲线上的颜色设置
//			2008-08-05 1.34		增加Mkr文字的颜色设置
//			2008-08-11 1.35		增加对报表标题和部分正文文字的支持，可以设置字体和文字大小
//			2008-08-20 1.36		改进星座图接口函数和相应的数据结构，使绘制星座图的每一个点可以自定义颜色，并且相下兼容
//			2008-09-18 1.37		增加参考线文字显示（自定义文字或显示坐标值，支持显示位置属性设置），支持参考线移动（键盘操作步进方式；鼠标方式）
//			2008-10-13 1.38.34	设置实时文字显示字体，改进文字显示位置不准确的问题
//			2008-10-31 1.38.35	修正波形显示无法达到右边界的bug
//			2008-11-03 1.38.36	修正纵坐标显示反向的bug
//			2008-11-25 1.39		增加鼠标移动绘制波形的功能，涂鸦的方式
//			2009-01-06 1.40		频标线模式时隐藏频标三角或菱形
//			2009-03-04 1.41		增加频标线的横纵方向线的独立开关
//			2009-03-17 1.42		增加星座图数据属性显示，完善DrawQamFill的功能
//			2009-03-26 1.42.37	修正星座图缩放时波形跑到删格区域外的bug
//			2009-05-20 1.42.38	修正鼠标涂鸦式绘图最后一个点无法画上的bug(GDI_SetMouseWavePixel)
//			2009-06-30 1.42.39	修正Limit文字显示位置不正确的bug
//			2009-07-09 1.43		扩展Limit文字显示功能，每条Limit线单独的文字位置属性和内容属性
//			2009-07-09 1.43.40	修正I_HORIZONTAL_BAR波形飞到边框外的bug，修正当前模式下MKR位置不正确的bug
//			2009-08-18 1.44		完成按照合格线区分波形颜色功能，即按照合格线曲线的颜色范围设置来显示波形，定义第一条合格线的值最高，第10条最低，波形当前值高于合格线
//								按照合格线的颜色显示，如果没超过任何一条合格线按照波形原有颜色显示
//			2009-08-19 1.44.41	修正按照合格线颜色显示波形颜色偶尔出现错位的bug
//			2009-09-03 1.45		在Mkr Line开启的情况下选择一个频标按照Mkr line的绘图范围
//			2009-09-04 1.46		增加移动横坐标时Mkr横坐标值保持不动的功能，但连续修改横坐标值时Mkr横坐标值会有误差
//			2009-09-10 1.47		增加设置波形数据起始位置功能，修正MKR开始位置正确的Bug
//			2009-09-17 1.48		增加双纵坐标系，分为左、右两个纵坐标，采样波形可以任意选择其中一组坐标作为参考，波形接口不变
//			2009-09-30 1.49		增加光谱图功能
//			2009-10-10 1.50		增加光谱图mkr功能，支持鼠标和键盘操作，修正纵坐标文字位置不正常的bug
//			2009-10-12 1.51		增加光谱图波形中的空值显示功能
//			2009-11-11 1.52		增加光谱图波形保存图片功能
//			2010-01-07 1.53		增加GDI_SetLimitLineVal的输入值保护开关
//			2010-01-15 1.53.42	修正了栅格位置一个像素误差的问题
//			2010-04-08 1.54		增加显示波形文字信息
//			2010-05-05 1.55		增加光谱图中幅度对照颜色说明
//			2010-05-14 1.56		增加Mkr纵坐标文字停靠最上方功能，在使用纵向Mkr Line时有效。完善自定义文字功能，使位置摆放更合理
//			2010-05-25 1.56.43	修正Limit Line文字显示开关无效的Bug
//			2010-05-26 1.57		增加设置Limit line线宽属性设置
//			2010-05-27 1.58		增加Limit Line Style接口函数
//			2010-06-07 1.58.44	修正SavePicture中无法显示多行波形说明文字的bug

#pragma once

#include "deskland.h"
#include <deque>

#pragma warning (disable:4819)

using namespace std;

enum MKR_MOVE				// MKR移动方向
{
	MKR_MOVE_LEFT = 0,		// 向左移动
	MKR_MOVE_RIGHT = 1,		// 向右移动
	MKR_MOVE_UP = 2,		// 向上移动
	MKR_MOVE_DOWN = 3		// 向下移动
};

enum DEFAULT_BORDER_GRID_POS			// 缺省栅格边框与窗口的距离
{
	DEFAULT_BORDER_GRID_LEFT = 60,		// 左边距
	DEFAULT_BORDER_GRID_RIGHT = 25,		// 右边距
	DEFAULT_BORDER_GRID_TOP = 15,		// 上边距
	DEFAULT_BORDER_GRID_BOTTOM = 30		// 下边距
};

enum SPECTROGRAM_MKR	// 光谱图mkr定义
{
	SPECTROGRAM_MKR_NONE = 0,	// 未选择或未定义
	SPECTROGRAM_MKR_X = 1,		// 使用横向mkr
	SPECTROGRAM_MKR_Y = 2		// 使用纵向mkr
};

enum Y_COORDINATE_DEF		// 坐标系定义
{
	Y_LEFT_COORDINATE_DOCK = 0,		// 左侧坐标系
	Y_RIGHT_COORDINATE_DOCK = 1		// 右侧坐标系
};

enum LIMI_MOVE_TYPE		// 合格线鼠标平移方向
{
	LIMIT_MOVE_UPDOWN = 0,		// 上下移动
	LIMIT_MOVE_LEFTRIGHT = 1,	// 左右移动
	LIMIT_MOVE_ALL				// 全方位移动
};

enum LIMIT_TYPE_DEF	// 合格线类型定义
{
	LIMIT_NORMAL = 20,		// 正常
	LIMIT_OVERFLOW = 21,	// 越界交叉
	LIMIT_UNDERBELOW =22	// 回界交叉
};

enum DEV_KEEP					// 显示元件停靠位置
{
	DEV_KEEP_LEFT = 0,			// 左侧停靠
	DEV_KEEP_TOP_LEFT = 1,		// 左上停靠
	DEV_KEEP_TOP = 2,			// 上方停靠
	DEV_KEEP_CENTER = 3,		// 中间停靠
	DEV_KEEP_TOP_RIGHT = 4,		// 右上方停靠
	DEV_KEEP_RIGHT = 5,			// 右侧停靠
	DEV_KEEP_BOTTOM_RIGHT = 6,	// 右下方停靠
	DEV_KEEP_BOTTOM = 7,		// 下方停靠
	DEV_KEEP_BOTTOM_LEFT = 8,	// 左下方停靠
	DEV_KEEP_DEFINE_END = 255	// 定义完毕
};

enum DEV_MOVE				// 绘图去移动个类元件定义
{
	DEV_LIMIT_UP = 0,		// 参考线上移
	DEV_LIMIT_DOWN = 1,		// 参考线下移
	DEV_MKR_LEFT = 2,		// 游标左移
	DEV_MKR_RIGHT = 3,		// 游标右移
	DEV_LIMIT_LEFT = 4,		// 参考线左移
	DEV_LIMIT_RIGHT = 5		// 参考线右移
};

enum DEV_MKR_VALUE			// 频标纵坐标数值显示参数
{
	DEV_MKR_VALUE_AUTO = 0,	// 自动显示
	DEV_MKR_VALUE_MANUAL_DIGIT = 1,	// 手动数字显示
	DEV_MKR_VALEE_MANUAL_CHAR = 2	// 手动字符显示
};

enum DEV_MKR_STYLE
{
	DEV_MKR_TRIANGLE = 0,	// 三角形频标
	DEV_MKR_DIAMOND = 1,	// 菱形频标
	DEV_MKR_KEEP_LEFT = 2,	// MKR保持横坐标左侧
	DEV_MKR_KEEP_CENTER = 3,// mkr保持在横坐标居中
	DEV_MKR_KEEP_RIGHT = 4	// MKR保持横坐标右侧
};

enum DEV_GRIDENUM
{
	DEV_GRID_CLASSICAL = 0,
	DEV_GRID_SPECTRUM = 1
};

enum DEVGDI_SCROLLBAR	// scrollbar 的高亮活动状态
{
	DEVGDI_SCROLLBAR_NOACTIVE = 0,
	DEVGDI_SCROLLBAR_UP = 1,
	DEVGDI_SCROLLBAR_DOWN = 2,
	DEVGDI_SCROLLBAR_PAGEUP = 3,
	DEVGDI_SCROLLBAR_PAGEDOWN = 4,
	DEVGDI_SCROLLBAR_SCROLL = 5,
	DEVGDI_SCROLLBAR_HOME = 6,
	DEVGDI_SCROLLBAR_END = 7
};

enum DEVGDI_WAVETYPE					// 波形的拉伸比例
{
	DEVGDI_WAVE_AUTOADJUST = 0,			//自动拉伸
	DEVGDI_WAVE_10_PERCENT = 10,		//10%
	DEVGDI_WAVE_25_PERCENT = 25,		//25%
	DEVGDI_WAVE_50_PERCENT = 50,		//50%
	DEVGDI_WAVE_100_PERCENT = 100,		//100%
	DEVGDI_WAVE_200_PERCENT = 200,		//200%
	DEVGDI_WAVE_500_PERCENT = 500,		//500%
	DEVGDI_WAVE_1000_PERCENT = 1000,	//1000%
	DEVGDI_WAVE_2000_PERCENT = 2000,	//2000%
	DEVGDI_WAVE_5000_PERCENT = 5000,	//5000%
	DEVGDI_WAVE_10000_PERCENT = 10000,	//10000%
	DEVGDI_WAVE_MAX_PERCENT = 0x7fffffff
};

enum DEVGDI_MOUSELINESTATUS
{
	DEVGDI_MOUSELINE_NOCURROR = 0,
	DEVGDI_MOUSELINE_READY = 1,
	DEVGDI_MOUSELINE_DRAW = 2
};

enum DEVGDI_DRAWLINE
{
	N_DRAW_SMALL_POINT = 0,	// 细点
	I_DRAW_LINE = 1,		// 细线
	I_DRAW_BIG_POINT = 2,	// 粗点
	I_MULTICOLOR_HORIZONTAL_LINE = 4,	// 双颜色竖条
	I_HORIZONTAL_LINE = 5,	// 竖线
	N_HORBAR_LINE = 6,		// 均衡器(竖条加细线)
	N_HORBAR_NO_SEP = 7,	// 竖条(无间隔)
	N_HORBAR_NO_SEP_ENABLE_MIN = 8,		// 竖条(无间隔), 并且使最小值保持在网格最低端
	I_HORIZONTAL_BAR = 0xFFFFE,			// 竖条(点数少则有间隔)
	I_SPECAL_RFANDVA = 0xFFFFF			// 竖线(用于显示载波电平、伴音和VA信号4种不同颜色的波形)
};

enum DEVGDI_MANUALTEXT_POS	// 手工文字位置	wangzheng 2008-06-19
{
	DEVGDI_TEXT_LEFTTOP = 0,
	DEVGDI_TEXT_LEFT = 1,
	DEVGDI_TEXT_LEFTBOTTOM = 2,
	DEVGDI_TEXT_RIGHTTOP = 3,
	DEVGDI_TEXT_RIGHT = 4,
	DEVGDI_TEXT_RIGHTBOTTOM = 5,
	DEVGDI_TEXT_CENTER = 6
};

const static double D_SPECTROGRAM_NONE_VALUE = -999999.0;	// 光谱图波形中的空值
const static int N_TEXT_LEN = 30;
const static int I_DEPARTMENT_LEN = 10;
const static int I_LIMITLINE_NUMBER = 3000;
const static int I_MKR_NUMBER = 10;
const static int I_WAVE_NUM = 20;
const static int N_MAX_MANUAL_TEXT_NUMBER = 5;
const static int N_SPECTROGRAM_COLOR_NUM = 20;	// 光谱图最大颜色数量支持

struct tagMultiText				// 多行文字
{
	CString szMultiLineText;	// 文字内容
	COLORREF TextColor;			// 文字颜色
	bool bEnableView;			// 是否显示文字
};

struct tagMouseLine		// 鼠标信息结构
{
	int nLeft;
	int nRight;
	int nTop;
	int nBottom;
	int nLButtonDown;
};

struct tagGridNum		// 绘图表格信息结构
{
	int nXNum;
	int nYNum;
};

struct tagCoordinate	// 坐标信息结构
{
	short nXCoord;
	short nYCoord;
	COLORREF PointColor;
};

struct tagManualText	// 自定义文字显示
{
	TCHAR czTitle[256];	// 标题
	TCHAR czDetail[256];	// 内容
	TCHAR czSeperate[I_DEPARTMENT_LEN];	// 分隔符
	UINT  nTextPos;						// 文字位置		wangzheng 2008-06-19
	bool bView;
};

struct tagCoorText		// 仿8831坐标 wangzheng 2008-09-11
{
	double dData;
	TCHAR czDepartment[I_DEPARTMENT_LEN];
};

typedef struct tagReport			// 波形打印报表数据结构
{
	CFont TitleFont;		// 标题头字体
	CFont HeaderTextFont;	// 波形上方文字字体
	CFont EndTextFont;		// 波形下方文字字体
	CString szTitle;		// 标题头文字
	CString szHeader;		// 波形上方文字
	CString szEnd;			// 波形下方文字
	double dTitleX;			// 标题头起始横坐标
	double dTitleY;			// 标题头起始纵坐标
	double dHeaderX;		// 波形上方文字起始横坐标
	double dHeaderY;		// 波形上方文字起始纵坐标
	double dEndX;			// 波形下方文字起始横坐标
	double dEndY;			// 波形下方文字起始纵坐标
	double dWaveX;			// 波形起始横坐标
	double dWaveY;			// 波形起始纵坐标
	double dWaveWidth;		// 波形宽度
	double dWaveHeight;		// 波形高度
	bool bEnableTitle;		// 标题头开关
	bool bEnableHeader;		// 波形上方文字开关
	bool bEnableEnd;		// 波形下方文字开关
} tagREPORT;

typedef struct tagLimitLine
{
	int m_nLineWidth;				// 当前Limit Line的线宽
	COLORREF m_LimitLineColor;		// 当前Limit Line的颜色
	double m_dzLimitLineMinVal;		// LimitLine 的最小值
	double m_dzLimitLineMaxVal;		// LimitLine 的最大值
	double m_dzLimitLineStartVal;	// LimitLine 的最起始值
	double m_dzLimitLineEndVal;		// LimitLine 的终止始值
	TCHAR m_czText[I_DEPARTMENT_LEN];	// Limit线上的显示文字，幅度值
	bool m_bzEnableLimitLine;		// 是否显示、隐藏Limit line
	bool m_bManualText;				// 自定义文字显示
	bool m_bzFullScreen;			// limitline 全屏显示
	bool m_bEnableText;				// 显示Limit线上的文字开关
} TAG_LimitLine;

class CDevGDI
{
public:
	// Grid ///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// 读取星座图象限框的属性
	// QamZoomColor -- 象限框的颜色
	// nLineWidth -- 象限框的宽度
	void GDI_GetQamZoomStyle(COLORREF &QamZoomColor, int &nLineWidth);
	// 设置星座图象限框的属性
	// QamZoomColor -- 象限框的颜色
	// nLineWidth -- 象限框的宽度
	void GDI_SetQamZoomStyle(const COLORREF &QamZoomColor, const int &nLineWidth);
	void GDI_EnableQamZoom(const bool &bEnable);	// 设置星座图的象限框的显示与隐藏开关
	bool GDI_IsQamZoomEnable(void);					// 读取星座图的象限框的显示与隐藏开关
	// 设置星座图的象限位置
	// nZoom = 1，2，3，4 （象限位置）
	// 返回值：true设置成功，false设置失败
	bool GDI_SetQamZoom(const int &nZoom);
	int GDI_GetQamZoom(void);							// 读取星座图的象限位置，nZoom = 1，2，3，4
	void GDI_SetGridPointRate(const double &dRate);		// 设置删格中心点显示比例
	void GDI_SetGridRoundRate(const double &dRate);		// 设置删格中心圈显示比例
	double GDI_GetGridPointRate(void);					// 读取删格中心点显示比例
	double GDI_GetGridRoundRate(void);					// 读取删格中心圈显示比例
	void GDI_SetGridRoundColor(const COLORREF &color);	// 设置删格中心圈的颜色
	COLORREF GDI_GetGridRoundColor(void);				// 获得删格中心圈的颜色
	void GDI_EnableGridPoint(const bool &bEnable);		// 设置删格中心点的显示开关
	void GDI_EnableGridRound(const bool &bEnable);		// 设置删格中心圈的显示开关
	bool GDI_IsGridPointEnable(void);					// 读取删格中心点的显示开关
	bool GDI_IsGridRoundEnable(void);					// 读取删格中心圈的显示开关
	bool GDI_SetGridLineNum(const int &nXNum, const int &nYNum);	// 设置绘图表格数量
	void GDI_GetGridLineNum(int &nXNum, int &nYNum);	// 获取绘图表格数量
	void GDI_GetBorderGridPos(RECT &rect);				// 的到绘图边框范围
	void GDI_SetBorderGridPos(const RECT &rect);		// 设置绘图边框范围
	// 设置绘图边框范围
	void GDI_SetBorderGridPos(const int &nLeft, const int &nTop, const int &nRight, const int &nBottom);
	// 设置表格属性		GridColor -- 表格颜色, iGridBorderWidth -- 边框宽度,
	// iLineWidth -- 表格线宽
	void GDI_SetGridStyle(const COLORREF &GridColor,
		const int &iGridBorderWidth, const int &iGridLineWidth, const BYTE &nGridType = DEV_GRID_CLASSICAL);
	void GDI_EnableGrid(const bool &bGrid);	// 设置绘制删格开关项

	// Text ///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// 设置光谱图文字说明开关
	// bEnable -- 文字说明开关，true开，false关
	void GDI_EnableSpecgView(const bool &bEnable);
	// 读取光谱图文字说明开关
	// 返回值: true开, false关
	bool GDI_IsSpecgViewEnable(void);
	// 设置波形文字说明
	// nID -- 波形ID
	// pczText -- 说明文字
	// color -- 文字颜色
	// bShow -- 是否显示文字，true显示，false隐藏
	// 返回值：true设置成功，false设置失败
	bool GDI_SetMultiText(const int &nID, const TCHAR *pczText, const COLORREF &color, const bool &bShow);
	// 激活第二个纵坐标系
	// bEnable -- 激活开关，true激活，false关闭
	void GDI_Enable2ndY(const bool &bEnable);
	// 第二个纵坐标系是否已激活
	// 返回值：激活开关，true激活，false关闭
	bool GDI_Is2ndYEnable(void);
	// 设置自定义文字内容
	// nID -- 自定义文字的位置id
	// pczTitle -- 自定义文字标题头
	// pczDetail -- 自定义文字内容
	// pczSeperate -- 自定义文字标题头与自定义文字内容之间的分隔符
	// bEnableView -- 是否显示当前自定义文字
	// 返回值 -- true成功，false -- 失败
	bool GDI_SetManualText(const int &nID, const TCHAR *pczTitle, const TCHAR *pczDetail, const TCHAR *pczSeperate, const bool &bEnableView = true,
		const UINT &nTextPos = DEVGDI_TEXT_LEFTTOP);
	bool GDI_SetManualTextNum(const int nManualTextNum);	// 设置自定义文字显示数量
	int GDI_GetManualTextNum(void);						// 获得自定义文字显示数量
	void GDI_EnableManualText(const bool &bEnable);		// 显示自定义文字信息开关
	bool GDI_IsManualTextEnable(void);					// 读取自定义文字信息开关
	void GDI_EnableManualXText(const bool &bEnable);	// 自定义X轴坐标内容
	bool GDI_IsManualXTextEnable(void);					// 读取自定义X轴坐标内容开关
	void GDI_EnableManualYText(const bool &bEnable);	// 自定义Y轴坐标内容
	bool GDI_IsManualYTextEnable(void);					// 读取自定义X轴坐标内容开关
	void GDI_SETViewPrecision(const int &nPrecision);	// 设置数据显示精度(小数点后多少位 >=0 <=99)
	void GDI_SetXTextYOffset(const int &nOffset = 0);	// 设置横坐标文字的纵向偏移量
	void GDI_SetYTextXOffset(const int &nOffset = 0);	// 设置纵坐标文字的横向偏移量
	void GDI_SetTextEnable(const bool &bXEnable, const bool &bYEnable);		// 设置坐标显示开关
	void GDI_SetTextColor(const COLORREF &TextColor);	// 设置文字颜色
	// 设置最大扫宽范围, iStart -- 起始值, iEnd -- 中止值
	void GDI_SetXFullSizeSpan(const double &dStart, const double &dEnd, const int &nDataLen = 0);
	// 读取最大扫宽范围, iStart -- 起始值, iEnd -- 中止值
	void GDI_GetXFullSizeSpan(double &dStart, double &dEnd);
	// 设置扫宽范围, iStart -- 起始值, iEnd -- 中止值
	void GDI_SetSpan(const double &dStart, const double &dEnd, const int &nDataLen = 0);
	// 读取扫宽范围, iStart -- 起始值, iEnd -- 中止值
	void GDI_GetSpan(double &dStart, double &dEnd);
	void GDI_SetXDepartment(const TCHAR* szDepart);		// 设置X轴坐标单位
	void GDI_GetXDepartment(TCHAR* szDepart);			// 读取X轴坐标单位
	void GDI_SetYDepartment(const TCHAR* szDepart);		// 设置Y轴坐标单位
	void GDI_GetYDepartment(TCHAR* szDepart);			// 读取Y轴坐标单位
	void GDI_SetYDep2ndY(const TCHAR* szDepart);		// 设置Y轴第二坐标单位
	void GDI_GetYDep2ndY(TCHAR* szDepart);				// 读取Y轴第二坐标单位
	// 根据波形数组的id获得改位置的横坐标(单位)值
	// nDataLen -- 波形数据的总长度
	// nArrayID -- 波形数据的id
	// 返回值：当前波形点的横坐标(单位)值
	double GDI_GetCurrentXValue(const int &nDataLen, const int &nArrayID);
	// 设置横坐标值 纯字符串用
	void GDI_SetXValue(const TCHAR *pszStart, const	TCHAR *pszCenter,
		const TCHAR *pszEnd);
	// 自定义纵坐标显示值
	// pszVal -- 纵坐标某一格的值
	// nLocation -- 所在格的位置，如果当前位置
	// 返回值：true设置成功，false设置失败
	bool GDI_SetYValue(const TCHAR *pszVal, const int &nLocation);
	// 设置Y轴起始，终止值
	void GDI_SetSpanY(const double &dStart, const double &dEnd);
	// 读取Y轴起始，终止值
	void GDI_GetSpanY(double &dStart, double &dEnd);
	// 设置纵坐标2的坐标范围
	// dStart -- 纵坐标起始值
	// dEnd -- 纵坐标终止值
	void GDI_SetSpanYSpecial(const double &dStart, const double &dEnd);
	// 获取纵坐标2的坐标范围
	// dStart -- 纵坐标起始值
	// dEnd -- 纵坐标终止值
	void GDI_GetSpanYSpecial(double &dStart, double &dEnd);
	void GDI_EnableCoor( const bool &bEnableCoor );		// 是否显示类似8831的坐标 wangzheng 2008-09-11
	bool GDI_SetCoorData( tagCoorText Data[], int nDataLen );	// wangzheng 设置坐标的数据
	// 设置实时绘图文字的字体
	// pszFont -- 字体
	// nFontSize -- 字体大小
	// 返回值：true设置成功，false设置失败
	bool GDI_SetFont(TCHAR *pszFont, int &nFontSize);

	// MKR ////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// 移动光谱图光标
	// ucDirection -- 移动方向，详见MKR_MOVE定义
	// nWaveLen -- 波形数量
	// nDataLen -- 光谱图中，每场波形的数据长度
	// 返回值：true成功，false失败
	bool GDI_MoveSpectrogramMkr(const BYTE &ucDirection, const int &nWaveNum, const int &nDataLen);
	// 选择使用光谱图的游标
	// ucType -- 被使用的游标，详见SPECTROGRAM_MKR定义
	void GDI_UseSpectrogramMkr(const BYTE &ucType);
	// 获得光谱图游标的使用状况
	// 返回值：光谱图游标的使用状况，详见SPECTROGRAM_MKR定义
	BYTE GDI_GetSpectrogramMkrUse(void);
	// 设置光谱图Mkr位置
	// nXPos -- 横坐标位置
	// nYPos -- 纵坐标位置
	// nWaveLen -- 波形数量
	// nDataLen -- 光谱图中，每场波形的数据长度
	void GDI_SetSpectrogramMkrPos(const int &nXPos, const int &nYPos, const int &nWaveLen, const int &nDataLen);
	// 读取光谱图Mkr位置
	// uType -- 返回数据类型，详见SPECTROGRAM_MKR定义
	// nXPos -- 横坐标位置
	// nYPos -- 纵坐标位置
	// dzOutWave -- 返回频谱或统计数据
	// dzInputWave -- 输入光谱图数据
	// nWaveNum -- 光谱图波形数量
	// nDataLen -- 每天波形的数据长度
	void GDI_GetSpectrogramMkrPos(const BYTE &uType, int &nXID, int &nYID, double *dzOutWave, const double *dzInputWave, const int &nWaveNum, const int &nDataLen);
	// 设置光谱图mkr颜色
	// color -- mkr颜色
	void GDI_SetSpectrogramMkrColor(const COLORREF &color);
	// 读取光谱图mkr颜色
	// 返回值：mkr颜色
	COLORREF GDI_GetSpectrogramMkrColor(void);
	// 设置光谱图Mkr开关状态
	// bXEnable -- 横向mkr开关
	// bYEnable -- 纵向Mkr开关
	void GDI_EnableSpectrogramMkr(const bool &bXEnable, const bool &bYEnable);
	// 读取光谱图Mkr开关状态
	// bXEnable -- 横向mkr开关
	// bYEnable -- 纵向Mkr开关
	void GDI_IsSpectrogramMkrEnable(bool &bXEnable, bool &bYEnable);
	// 设置游标线的颜色
	// color -- 游标线的颜色
	void GDI_SetMkrLineColor(const COLORREF &color);
	// 读取游标线的颜色
	// 返回值：游标线的颜色
	COLORREF GDI_GetMkrLineColor(void);
	// 频标横坐标跟踪保持开关
	// bEnable -- 跟踪横坐标开关，true：跟踪值，false：跟踪位置
	void GDI_EnableMkrKeepX(const bool &bEnable);
	inline bool GDI_IsMkrKeepX(void);		// 获得频标跟踪横坐标开关
	COLORREF GDI_GetActiveMkrColor(void);	// 获得当前活动频标的颜色
	void GDI_SetActiveMkrColor(const COLORREF &ActiveMkrColor);	// 设置当前活动频标的颜色
	// 设置mkr保持在波形上的横向位置位置，分为左侧和居中两种状态
	// nType -- mkr的横向位置特征，相见枚举DEV_MKR_STYLE
	bool GDI_SetMkrXKeep(const int &nType);	
	bool GDI_SetMkrUnit(const int &nID, const TCHAR *pszUnit);	// 设置频标的单位
	bool GDI_SetMkrXPos(const int &nID, const int &nArrayID);	// 设置指定频标所在波形数据中的位置
	int GDI_GetMkrXPos(const int &nID);	// 获得指定频标所在波形数据中的位置，返回值：数组id
	bool GDI_SetMkrVal(const double &dValY, const int &nID);	// 设置指定mkr纵坐标值
	bool GDI_SetMkrVal(const TCHAR* pszValY, const int &nID);	// 设置指定mkr纵坐标值
	void GDI_ManualMkrVal(const BYTE &ucManual);	// 手动设置mkr的值,具体见DEV_MKR_VALUE的说明
	void GDI_SetXMrkEnable( const bool &bEnable );		// 设置是否显示左上角的横坐标频标	wangzheng 2008-08-04
	void GDI_SetYMkrEnable(const bool &bEnable);	// 设置频标纵坐标文字开关
	// 获得当前频标的值
	// dYValue -- 频标的横坐标值
	// dXValue -- 频标的纵坐标值
	// nMkrID -- 获得当前频标的id
	// pdWaveData -- 波形数据
	// nWaveLen -- 波形数据长度
	// return value: -1读取失败，其余值为频标所在波形数据的位置
	int GDI_GetMkrValue(double &dYValue, double &dXValue, const int &nMkrID, const double *pdWaveData,
		const int &nWaveLen);
	// 设置频标状态，支持波形数量
	bool GDI_SetMkrKeepWave(const int &nMkrID, const int &nWaveID, const bool &bKeep);
	// 读取频标状态，支持波形数量
	bool GDI_GetMkrKeepWave(const int &nMkrID, const int &nWaveID);
	bool GDI_IsMkrLineEnable();		// 判断频标线是否显示
	// 设置显示, 隐藏频标线
	// bMkr -- 频标线显示开关
	// bXLine -- 横向频标线独立显示开关
	// bYLine -- 纵向频标线独立显示开关
	void GDI_EnableMkrLine(const bool &bMkr, const bool &bXLine = true, const bool &bYLine = true);
	bool GDI_IsMkrEnable(const int &iMkrID);	// 判断当前频标是否活动
	int GDI_GetActiveMkr(void);		//获得当前活动的频标
	// 使用鼠标操作设置活动频标
	bool GDI_SetActiveMkrByMouse(const int &nXPos, const int &nYPos, const double *pdData, const int &nDataLen, const double *pdData2 = NULL,
		const int &nDataLen2 = 0, const double *pdData3 = NULL, const int &nDataLen3 = 0, const double *pdData4 = NULL, const int &nDataLen4 = 0,
		const double *pdData5 = NULL, const int &nDataLen5 = 0, const double *pdData6 = NULL, const int &nDataLen6 = 0, const double *pdData7 = NULL,
		const int &nDataLen7 = 0, const double *pdData8 = NULL, const int &nDataLen8 = 0, const double *pdData9 = NULL, const int &nDataLen9 = 0,
		const double *pdData10 = NULL, const int &nDataLen10 = 0);
	void GDI_SetActiveMkr(const int &iMkrID);	//设置当前活动的频标
	// 设置频标的可视属性，iid--频标id, bEnable-- true可视，false不可视
	void GDI_EnableMkr(const int &iID, const bool &bEnable);
	// 设置显示频标纵坐标, true显示 false不显示
	void GDI_EnableMkrYDepartment(const bool &bDepartment);
	void GDI_SetActiveXMkrVal(const CString &szMkrXValue);	// 设置光标当前显示的横坐标值
	void GDI_SetXMkrValue(const CString *pszMkrXValue);	// 设置光标当前横坐标值
	//设置mkr的特定X值
	bool GDI_SetMkrX(const int &iLocation, const int &nYPos, const double *pdData, const int &iDataLen);
	// 设置Mkr的值，加或减
	void GDI_SetMkrX(const bool &AddOrAbate, const int &iDataLen);
	// 按照坐标的实际值设置Mkr的横坐标位置
	// nID -- Mkr的序号
	// dXVal -- 设置横坐标的值
	// nDataLen -- 当前波形的数据长度
	// 返回值：true成功，false失败，由于输入值超出了当前坐标范围引起
	bool GDI_SetMkrX(const int &nID, const double &dXVal, const int &nDataLen);
	void GDI_ResetMkr();	// 将mkr值设为0
	// 设置频标属性
	// mkrColor -- 频标颜色, imkrType -- 频标类型
	bool GDI_SetMkrStyle(const COLORREF &mkrColor, const int &imkrType, const int &nMkrID = 0);
	// 获得频标属性
	// mkrColor -- 频标颜色, imkrType -- 频标类型
	bool GDI_GetMkrStyle(COLORREF &mkrColor, int &nMkrType, const int &nMkrID);
	// 设置频标属性，扩展功能
	// mkrColor -- 频标颜色
	// imkrType -- 频标类型
	// nMkrID -- 频标ID
	// nWaveID -- 频标跟踪波形的ID
	// 返回值：true设置成功，false设置失败
	bool GDI_SetMkrStyleEx(const COLORREF &mkrColor, const int &nMkrType, const int &nMkrID, const int &nWaveID);
	// 获得频标属性，扩展功能
	// mkrColor -- 频标颜色
	// imkrType -- 频标类型
	// nMkrID -- 频标ID
	// nWaveID -- 频标跟踪波形的ID
	// 返回值：true读取成功，false读取失败
	bool GDI_GetMkrStyleEx(COLORREF &mkrColor, int &nMkrType, const int &nMkrID, const int &nWaveID);
	// 设置频标文字的颜色
	// TextColor -- 频标的文字颜色
	// nMkrID -- 频标ID
	// nWaveID -- 频标跟踪波形的ID
	// 返回值：true设置成功，false设置失败
	bool GDI_SetMkrTextColor(const COLORREF &TextColor, const int &nMkrID, const int &nWaveID);
	// 获得频标文字的颜色
	// TextColor -- 频标的文字颜色
	// nMkrID -- 频标ID
	// nWaveID -- 频标跟踪波形的ID
	// 返回值：true读取成功，false读取失败
	bool GDI_GetMkrTextColor(COLORREF &TextColor, const int &nMkrID, const int &nWaveID);

	// Zoom in/out ///////////////////////////////////////////////////////////////////////////////////////////////
	//
	int GDI_GetMouseLineStatus(void);					// 得到鼠标线状态
	void GDI_SetMouseLineStatus(const int &nStatus);	// 设置鼠标线状态
	void GDI_SetMouseLineLButtonDown(const int &nXPos, const int &nYPos);	// 鼠标画方框控制左键按下
	void GDI_SetMouseLineMove(const int &nXPos, const int &nYPos);			// 鼠标画方框控制移动
	bool GDI_SetMouseLineLButtonUp(const int &nXPos, const int &nYPos, const int &nDataLen);// 鼠标画方框控制左键放开
	// 鼠标左键点击事件滑动条pageup和pagedown事件
	bool GDI_MouseUpPageUp_Down(const int &nXPos, const int &nYPos, const int &nDataLen);
	void GDI_SetMouseStartX(const int& nXPos);	// 鼠标左键按下时，鼠标坐标的初始值，用于滚动条
	// 使用鼠标设置波形当前位置和滚动条位置
	bool GDI_ScrollWaveByMouse(const int &nXPos, const int &nYPos, const double* pdData, const int &nDataLen);
	void GDI_MoveWave(const int &nScrollType, const int &nDataLen);	// 移动波形
	int GDI_GetWaveRate(void);		// 获得波形显示比例
	int GDI_GetWaveAdjustRate(const int &nDataLen);	// 获得波形自动拉伸比例
	// 设置波形显示比例
	void GDI_SetWaveRate(const int &iRatePercent, const int &nDataLen);
	// 判断鼠标的位置，并设置scrollbar的高亮状态
	// return value: true -- 在button上， false -- 不在button上
	int GDI_CheckMouseXY(const int &nXPos, const int &nYPos,
		const double* pdData, const int &iDataLen);
	bool GDI_IsScrollBarEnable();	// 获得ScrollBar的显示隐藏属性
	void GDI_EnableScrollBar(const bool &bScrollBar);	// 是否显示ScrollBar
	

	// Limit line /////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// 设置Limit line 的显示属性
	// bLimitLine -- 显示属性，true显示, false隐藏
	// nID -- Limit Line 的 ID
	// 返回值：true成功，false失败
	bool GDI_EnableLimitLine(const bool &bLimitLine, const int &nID);
	// 读取Limit line 的显示属性
	// nID -- Limit Line 的 ID
	// 返回值：显示属性，true显示, false隐藏或读取失败
	bool GDI_IsLimitLineEnable(const int &nID);
	// 设置Limit Line的值
	// dStartX -- 横坐标起始值
	// dEndX -- 横坐标终止值
	// dMinY -- 纵坐标最小值
	// dMaxY -- 纵坐标最大值
	// nID -- Limit Line 的 ID
	// bProtect -- 对输入值进行保护，true保护，false不保护
	// 返回值：true成功，false失败
	bool GDI_SetLimitLineVal(double &dStartX, double &dEndX, double &dMinY, double &dMaxY,
		const int &nID, const bool &bProtect = true);
	// 读取Limit Line的值
	// dStartX -- 横坐标起始值
	// dEndX -- 横坐标终止值
	// dMinY -- 纵坐标最小值
	// dMaxY -- 纵坐标最大值
	// nID -- Limit Line 的 ID
	// 返回值：true成功，false失败
	bool GDI_GetLimitLineVal(double &dStartX, double &dEndX, double &dMinY, double &dMaxY,
		const int &nID);
	// 设置Limit Line的属性
	// LimitLineColor -- 当前Limit Line的颜色
	// nLineWidth -- 当前LImit Line的线宽
	// nID -- Limit Line 的 ID
	// 返回值：true成功，false失败
	bool GDI_SetLimitLineStyle(const COLORREF &LimitLineColor, const int &nLineWidth, const int &nID);
	// 读取Limit Line的属性
	// LimitLineColor -- 当前Limit Line的颜色
	// nLineWidth -- 当前LImit Line的线宽
	// nID -- Limit Line 的 ID
	// 返回值：true成功，false失败
	bool GDI_GetLimitLineStyle(COLORREF &LimitLineColor, int &nLineWidth, const int &nID);
	// 设置Limit Line的颜色
	// LimitLineColor -- 当前Limit Line的颜色
	// nID -- Limit Line 的 ID
	// nLineWidth -- 设置LImit Line的线宽
	// 返回值：true成功，false失败
	bool GDI_SetLimitLineColor(const COLORREF &LimitLineColor, const int &nID, const int &nLineWidth = 1);
	// 读取Limit Line的颜色
	// LimitLineColor -- 当前Limit Line的颜色
	// nID -- Limit Line 的 ID
	// 返回值：true成功，false失败
	bool GDI_GetLimitLineColor(COLORREF &LimitLineColor, const int &nID);
	// 设置Limit Line全屏幕显示
	// bFullScreen -- 是否全屏显示，true是，false否
	// nID -- Limit Line 的 ID
	// 返回值：true成功，false失败
	bool GDI_SetLimitLineFullScreen(const bool &bFullScreen, const int &nID);
	// 设置Limit Line全屏幕显示
	// bFullScreen -- 是否全屏显示，true是，false否
	// nID -- Limit Line 的 ID
	// 返回值：true成功，false失败
	bool GDI_GetLimitLineFullScreen(bool &bFullScreen, const int &nID);
	// 以下程序为兼容DS7618程序，横向全屏幕limit line ////////////////
	// 读取Limit Line的值, 返回值为limit line的数量
	int GDI_GetLimitLineVal(int* pnLimitLineVal, bool* pbEnable);
	// 设置Limit Line的值
	void GDI_SetLimitLineVal(const int* pnLimitLineVal, const bool* pbEnable, const int &nLimitLineNumber);
	// 设置Limit Line的值
	void GDI_SetLimitLineVal(const double* pnLimitLineVal, const bool* pbEnable, const int &nLimitLineNumber);
	// 设置Limit Line的颜色
	void GDI_SetLimitLineColor(const COLORREF &LimitLineColor);
	// 设置Limit Line Text的开关
	// bEnable -- 显示开关
	// nID -- limit线的ID
	// 返回值：成功true，失败false
	bool GDI_EnableLimitLineText(const bool &bEnable, const int &nID);
	// 读取Limit Line Text的开关
	// bEnable -- 显示开关
	// nID -- limit线的ID
	// 返回值：成功true，失败false
	bool GDI_IsLimitLineTextEnable(bool &bEnable, const int &nID);
	// 设置Limit线的自定义文字
	// pszStr -- 自定义文字内容
	// nID -- Limit线的ID
	// 返回值：true成功，false失败
	bool GDI_SetManualLimitText(const TCHAR *pszStr, const int &nID);
	// 读取Limit线的自定义文字
	// pszStr -- 自定义文字内容
	// nID -- Limit线的ID
	// 返回值：true成功，false失败
	bool GDI_GetManualLimitText(TCHAR *pszStr, const int &nID);
	// 设置Limit线的自定义文字开关
	// bEnable -- 自定义文字的开关，true开，false关
	// nID -- Limit线的ID
	// 返回值：true成功，false失败
	bool GDI_EnableLimitManualText(const bool &bEnable, const int &nID);
	// 读取Limit线的自定义文字开关
	// bEnable -- 自定义文字的开关，true开，false关
	// nID -- Limit线的ID
	// 返回值：true成功，false失败
	bool GDI_IsLimitManualTextEnable(bool &bEnable, const int &nID);
	// 设置Limit线的步进值
	// dStep -- 步进值
	void GDI_SetLimitStep(const double &dStep);
	// 获得Limit线的步进值
	// 返回值：步进值
	double GDI_GetLimitStep(void);
	// 移动参考线,方向参考DEV_MOVE的定义
	// nDirection -- 参考线移动方向
	void GDI_MoveLimitLine(const int &nDirection);
	// 用鼠标移动参考线，参考线跟踪鼠标位置移动
	// nXPos -- 输入横坐标
	// nYPos -- 输入纵坐标
	void GDI_MoveLimitLine(const int &nXPos, const int &nYPos, const int &nType);
	// 设置当前活动的Limit线
	// nID -- Limit线的ID
	// 返回值：true成功，false失败
	bool GDI_SetActiveLimitLine(const int &nID);
	// 获得当前活动的Limit线
	// 返回值：当前活动Limit线的ID
	int GDI_GetActiveLimitLine(void);
	// 设置Limit Line文字的位置
	// nLocation -- 文字的位置，参考DEV_KEEP的定义
	// 返回值：true设置成功，false设置失败
	bool GDI_SetLimitTextDock(const int &nLocation, const int &nID =0);

	// Wave ////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// 绘制光谱图波形数据
	// pdData -- 波形数据
	// nWaveNum -- 波形总共有多少条
	// nDataLen -- 每条波形数据长度
	// pColor -- 光谱图颜色表
	// pdLevel -- 光谱图幅度门限值, 其中第0个值是最低值，此后显示波形采样值大于门限值中最大的门限颜色
	// nColorNum -- 光谱图颜色值
	// 返回值：true成功，false失败
	bool GDI_DrawSpectrogram(const double *pdData, const int &nWaveNum, const int &nDataLen, const COLORREF *pColor, const double *pdLevel, const int &nColorNum);
	// 设置波形使用坐标系
	// nWaveID -- 波形ID
	// ucDock -- 使用坐标系，详见Y_COORDINATE_DEF的定义
	// 返回值：true成功，false失败
	bool GDI_SetWaveDock(const int &nWaveID, const BYTE &ucDock);
	// 读取波形使用坐标系
	// nWaveID -- 波形ID
	// ucDock -- 返回使用坐标系，详见Y_COORDINATE_DEF的定义
	// 返回值：true成功，false失败
	bool GDI_GetWaveDock(const int &nWaveID, BYTE &ucDock);
	//设置波形起始位置的点数 尔洪春/9/9
	void GDI_SetWaveStartPos(const int &iWaveStartPos);
	// 绘制波形，颜色按照合格线设置来区分，幅度高于UpLimit的，按照UpLimit的颜色显示，变量定义中数字大的显示优先级
	// 高于小的，UpLimit的显示优先级高于DownLimit的优先级
	// pdCurrent -- 采样波形数据
	// nCurrent --采样波形数据长度
	// pdMax -- 最大保持波形数据
	// nMax -- 最大保持波形数据长度
	// pdMin -- 最小保持波形数据
	// nMin -- 最小保持波形数据长度
	// pdAverage -- 平均值波形数据
	// nAverage -- 平均值波形数据长度
	// pdUpLimit1 -- 上合格线1数据
	// nUpLimit1 -- 上合格线1数据长度
	// pdDownLimit1 -- 下合格线1数据
	// nDownLimit1 -- 下合格线1数据长度
	// pdUpLimit2 -- 上合格线2数据
	// nUpLimit2 -- 上合格线2数据长度
	// pdDownLimit2 -- 下合格线2数据
	// nDownLimit2 -- 下合格线2数据长度
	// pdUpLimit3 -- 上合格线3数据
	// nUpLimit3 -- 上合格线3数据长度
	// pdDownLimit3 -- 下合格线3数据
	// nDownLimit3 -- 下合格线3数据长度
	// pdUpLimit4 -- 上合格线4数据
	// nUpLimit4 -- 上合格线4数据长度
	// pdDownLimit4 -- 下合格线4数据
	// nDownLimit4 -- 下合格线4数据长度
	// pdUpLimit5 -- 上合格先5数据
	// nUpLimit5 -- 上合格线5数据长度
	// pdDownLimit5 -- 下合格线5数据
	// nDownLimit5 -- 下合格线5数据长度
	// bzEnable -- 合格线使能，false表示无效，true表示有效
	// 返回值：true执行成功，false执行失败
	bool GDI_DrawByLimit(const double *pdCurrent, const int &nCurrent, const double *pdMax, const int &nMax,
		const double *pdMin, const int &nMin, const double *pdAverage, const int &nAverage,
		const double *pdUpLimit1, const int &nUpLimit1, const double *pdDownLimit1, const int &nDownLimit1,
		const double *pdUpLimit2, const int &nUpLimit2, const double *pdDownLimit2, const int &nDownLimit2,
		const double *pdUpLimit3, const int &nUpLimit3, const double *pdDownLimit3, const int &nDownLimit3,
		const double *pdUpLimit4, const int &nUpLimit4, const double *pdDownLimit4, const int &nDownLimit4,
		const double *pdUpLimit5, const int &nUpLimit5, const double *pdDownLimit5, const int &nDownLimit5, bool *bzEnable);
	// 设置鼠标绘制波形的起始点，由LButtonDown事件程序调用
	// nXStartPos -- 鼠标横坐标位置
	// nYStartPos -- 鼠标纵坐标位置
	// pdData -- 波形数据
	// nDataLen --当前波形的数据长度
	// nWaveID -- 波形数据ID
	// 返回值：true设置成功，false设置失败
	bool GDI_SetMouseWaveLineStart(const int &nXStartPos, const int &nYStartPos, double *pdData, const int &nDataLen, const int &nWaveID);
	// 鼠标绘制波形的涂鸦函数，绘制的波形曲线由鼠标滑过的轨迹来决定
	// nXEndPos -- 鼠标横坐标位置
	// nYEndPos -- 鼠标纵坐标位置
	// pdData -- 波形数据
	// nDataLen -- 波形数据长度
	// nWaveID -- 波形的ID
	// 返回值：true设置成功，false设置失败
	bool GDI_SetMouseWavePixel(const int &nXEndPos, const int &nYEndPos, double *pdData, const int &nDataLen, const int &nWaveID);
	int GDI_GetWavePixNum(void);	// 获得波形宽度，像素数
	int GDI_GetXPixelNumber();//获得数据区X轴像素数
	// 设置数据曲线属性
	// LineColor -- 曲线的颜色, iLineWidth -- 线的宽度
	// LineColor2 -- 第二条曲线的颜色, iLineWidth2 -- 第二条曲线的宽度
	void GDI_SetLine(const COLORREF &LineColor, const int &iLineWidth, const COLORREF &LineColor2 = RGB(0, 255, 255), const int &iLineWidth2 = 1,
		const COLORREF &LineColor3 = RGB(255, 0, 255), const int &nLineWidth3 = 1, const COLORREF &LineColor4 = RGB(255, 0, 0),
		const int &nLineWidth4 = 1, const COLORREF &LineColor5 = RGB(0, 255, 0), const int &nLineWidth5 = 1, const COLORREF &LineColor6 = RGB(0, 0, 255),
		const int &nLineWidth6 = 1, const COLORREF &LineColor7 = RGB(255, 255, 255), const int &nLineWidth7 = 1,
		const COLORREF &LineColor8 = RGB(255, 255, 255), const int &nLineWidth8 = 1, const COLORREF &LineColor9 = RGB(255, 255, 255),
		const int &nLineWidth9 = 1, const COLORREF &LineColor10 = RGB(255, 255, 255), const int &nLineWidth10 = 1,
		const COLORREF &LineColor11 = RGB(255, 255, 255), const int &nLineWidth11 = 1, const COLORREF &LineColor12 = RGB(255, 255, 255),
		const int &nLineWidth12 = 1, const COLORREF &LineColor13 = RGB(255, 255, 255), const int &nLineWidth13 = 1,
		const COLORREF &LineColor14 = RGB(255, 255, 255), const int &nLineWidth14 = 1, const COLORREF &LineColor15 = RGB(255, 255, 255),
		const int &nLineWidth15 = 1, const COLORREF &LineColor16 = RGB(255, 255, 255), const int &nLineWidth16 = 1,
		const COLORREF &LineColor17 = RGB(255, 255, 255), const int &nLineWidth17 = 1, const COLORREF &LineColor18 = RGB(255, 255, 255),
		const int &nLineWidth18 = 1, const COLORREF &LineColor19 = RGB(255, 255, 255), const int &nLineWidth19 = 1,
		const COLORREF &LineColor20 = RGB(255, 255, 255), const int &nLineWidth20 = 1);
	// 读取数据曲线属性
	// LineColor -- 曲线颜色
	// iLineWidth -- 曲线宽度
	void GDI_GetLine(COLORREF &LineColor, int &iLineWidth, COLORREF &LineColor2, int &iLineWidth2, COLORREF &LineColor3, int &nLineWidth3, COLORREF &LineColor4,
		int &nLineWidth4, COLORREF &LineColor5, int &nLineWidth5, COLORREF &LineColor6, int &nLineWidth6, COLORREF &LineColor7, int &nLineWidth7, COLORREF &LineColor8,
		int &nLineWidth8, COLORREF &LineColor9, int &nLineWidth9, COLORREF &LineColor10, int &nLineWidth10, COLORREF &LineColor11, int &nLineWidth11,
		COLORREF &LineColor12, int &nLineWidth12, COLORREF &LineColor13, int &nLineWidth13, COLORREF &LineColor14, int &nLineWidth14, COLORREF &LineColor15,
		int &nLineWidth15, COLORREF &LineColor16, int &nLineWidth16, COLORREF &LineColor17, int &nLineWidth17, COLORREF &LineColor18, int &nLineWidth18,
		COLORREF &LineColor19, int &nLineWidth19, COLORREF &LineColor20, int &nLineWidth20);
	// 显示QAM数据
	// pnData -- 波形数据
	// nDataLen -- 波形数据长度
	// bManualColor -- 自定义波形颜色开关，false使用类内部的波形颜色属性，true使用自定义颜色，每个点的颜色可以不同
	// 返回值：true成功，false失败
	bool GDI_DrawQAM(const struct tagCoordinate *pnData, const int &nDataLen, const bool &bManualColor = false);
	// 显示QAM数据
	bool GDI_DrawQAM(deque<int> &nstQamData);
	// 显示QAM数据，填充模式
	// pnData -- 星座图数据
	// nDataLen --输入的星座图数据长度
	// bManualColor -- 单个点自定义颜色开关
	// 返回值：true成功，false失败
	bool GDI_DrawQamFill(const struct tagCoordinate *pnData, const int &nDataLen,
		const bool &bManualColor = false);
	// 显示QAM数据，填充模式
	bool GDI_DrawQamFill(deque<int> &nstQamData);
	void GDI_DrawQamClean(void);	// 清除Qam数据，用于填充模式
	// 显示一帧画面, iData -- 数据曲线, iDataLen -- 扫描点数
	bool GDI_Draw(const double *pdData, const int &iDataLen, const double *pdData2 = NULL, const int nDataLen2 = 0, const double *pdData3 = NULL,
		const int &nDataLen3 = 0, const double *pdData4 = NULL, const int &nDataLen4 = 0, const double *pdData5 = NULL, const int &nDataLen5 = 0,
		const double *pdData6 = NULL, const int &nDataLen6 = 0, const double *pdData7 = NULL, const int &nDataLen7 = 0, const double *pdData8 = NULL,
		const int &nDataLen8 = 0, const double *pdData9 = NULL, const int &nDataLen9 = 0, const double *pdData10 = NULL, const int &nDataLen10 = 0,
		const double *pdData11 = NULL, const int &nDataLen11 = 0, const double *pdData12 = NULL, const int &nDataLen12 = 0, const double *pdData13 = NULL,
		const int &nDataLen13 = 0, const double *pdData14 = NULL, const int &nDataLen14 = 0, const double *pdData15 = NULL, const int &nDataLen15 = 0,
		const double *pdData16 = NULL, const int &nDataLen16 = 0, const double *pdData17 = NULL, const int &nDataLen17 = 0, const double *pdData18 = NULL,
		const int &nDataLen18 = 0, const double *pdData19 = NULL, const int &nDataLen19 = 0, const double *pdData20 = NULL, const int &nDataLen20 = 0);
	// 显示一幅波形画面
	// ppdData -- 波形数据二维指针数组
	// pnDataLen -- 波形数据长度一维指针数组
	// nWaveNum -- 波形数据数量
	// 返回值：true成功，false失败
	bool GDI_DrawD(double **ppdData, const int *pnDataLen, const int &nWaveNum);
	// 对数横坐标绘图, public
	bool GDI_DrawLgX(const double *pdData, const int &nDataLen, const double *pdData2 = NULL,
		const int nDataLen2 = 0);
	// 显示两个波形窗口
	bool GDI_DrawDoubleRect(const double *pdData1, const int &nDataLen1, const double *pdData2, const int &nDataLen2);
	// 显示对数波形窗口
	bool GDI_Draw3Horizontal(const double *pdData1, const int &nDataLen1, const double *pdData2 = NULL,
		const int &nDataLen2 = 0, const double *pdData3 = NULL, const int &nDataLen3 = 0);
	// 仅绘制数据
	bool GDI_DrawLineOnly(const double *pdData, const int &nDataLen, const double *pdData2 = NULL,
		const int &nDataLen2 = 0);
	// 绘制波形数据，支持波形数据最大点数
	// pdData -- 波形数据
	// nDataLen -- 当前波形数据的长度
	// nMaxPointNum -- 绘图支持的波形数据的最大长度
	// 返回值：true成功，false失败
	bool GDI_DrawLineEnableMaxPointNum(const double *pdData, const int &nDataLen, const int &nMaxPointNum);

	// Picture //////////////////////////////////////////////////////////////////////////////
	//
	// 保存光谱图图片
	// pszFileName -- 被保存的文件路径
	// pdData -- 波形数据
	// nWaveNum -- 波形总共有多少条
	// nDataLen -- 每条波形数据长度
	// pColor -- 光谱图颜色表
	// pdLevel -- 光谱图幅度门限值, 其中第0个值是最低值，此后显示波形采样值大于门限值中最大的门限颜色
	// nColorNum -- 光谱图颜色值
	// 返回值：true成功，false失败
	bool GDI_SaveSpectrogramPic(const TCHAR *pszFileName, const double *pdData, const int &nWaveNum, const int &nDataLen, const COLORREF *pColor,
		const double *pdLevel, const int &nColorNum);
	// 将当前波形图像保存成为图片, 图像文件可以bmp,jpg等各式均可
	// pszFileName -- 被保存的文件路径
	// pdData-pdData10 -- 波形数据
	// iDataLen-nDataLen10 -- 波形数据长度
	// 返回值：true保存成功，false保存失败
	bool GDI_SavePicture(const TCHAR *pszFileName, const double *pdData, const int &iDataLen, const double *pdData2 = NULL, const int nDataLen2 = 0,
		const double *pdData3 = NULL, const int &nDataLen3 = 0, const double *pdData4 = NULL, const int &nDataLen4 = 0, const double *pdData5 = NULL,
		const int &nDataLen5 = 0, const double *pdData6 = NULL, const int &nDataLen6 = 0, const double *pdData7 = NULL, const int &nDataLen7 = 0,
		const double *pdData8 = NULL, const int &nDataLen8 = 0, const double *pdData9 = NULL, const int &nDataLen9 = 0, const double *pdData10 = NULL,
		const int &nDataLen10 = 0, const double *pdData11 = NULL, const int &nDataLen11 = 0, const double *pdData12 = NULL, const int &nDataLen12 = 0,
		const double *pdData13 = NULL, const int &nDataLen13 = 0, const double *pdData14 = NULL, const int &nDataLen14 = 0, const double *pdData15 = NULL,
		const int &nDataLen15 = 0, const double *pdData16 = NULL, const int &nDataLen16 = 0, const double *pdData17 = NULL, const int &nDataLen17 = 0,
		const double *pdData18 = NULL, const int &nDataLen18 = 0, const double *pdData19 = NULL, const int &nDataLen19 = 0, const double *pdData20 = NULL,
		const int &nDataLen20 = 0);

	// Report //////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// 显示一帧画面用于报表, 的坐标值, iData -- 数据曲线, iDataLen -- 扫描点数
	bool GDI_DrawReport(CDC *pDC, CPrintInfo* pInfo, const double *pdData, const int &nDataLen, const double *pdData2 = NULL, const int &nDataLen2 = 0,
		const double *pdData3 = NULL, const int &nDataLen3 = 0, const double *pdData4 = NULL, const int &nDataLen4 = 0, const double *pdData5 = NULL,
		const int &nDataLen5 = 0, const double *pdData6 = NULL, const int &nDataLen6 = 0, const double *pdData7 = NULL, const int &nDataLen7 = 0,
		const double *pdData8 = NULL, const int &nDataLen8 = 0, const double *pdData9 = NULL, const int &nDataLen9 = 0, const double *pdData10 = NULL,
		const int &nDataLen10 = 0, const double *pdData11 = NULL, const int &nDataLen11 = 0, const double *pdData12 = NULL, const int &nDataLen12 = 0,
		const double *pdData13 = NULL, const int &nDataLen13 = 0, const double *pdData14 = NULL, const int &nDataLen14 = 0, const double *pdData15 = NULL,
		const int &nDataLen15 = 0, const double *pdData16 = NULL, const int &nDataLen16 = 0, const double *pdData17 = NULL, const int &nDataLen17 = 0,
		const double *pdData18 = NULL, const int &nDataLen18 = 0, const double *pdData19 = NULL, const int &nDataLen19 = 0, const double *pdData20 = NULL,
		const int &nDataLen20 = 0);
	// 设置报表文字大小和字体
	// pszFont -- 文字字体
	// nFontSize -- 文字大小
	void GDI_SetReportFont(const TCHAR *pszFont, const int &nFontSize);
	// 初始化报表
	// ReportData -- 报表的数据结构
	// bDefault -- 是否引导为缺省设置，true引导位缺省设置，则ReportData的数据无效，表报的各种属性由系统进行缺省设置。false自定义设置，ReportData的数据有效
	// 返回值：true成功，false失败
	bool GDI_InitReport(const tagREPORT &ReportData, const bool &bDefault = true);
	void GDI_ExitReport(void);	// 退出打印报表
	// 设置报表标题头字体
	// pszFont -- 字体
	// nFontSize -- 字大小
	// nFontWeight -- 字体粗细程度，FW_NORMAL普通，FW_BLACK文字加粗
	// 返回值：true成功，false失败
	bool GDI_SetReportTitleFont(const TCHAR *pszFont, const int &nFontSize, const int &nFontWeight);
	// 设置波形上方文字字体
	// pszFont -- 字体
	// nFontSize -- 字大小
	// 返回值：true成功，false失败
	bool GDI_SetReportHeaderFont(const TCHAR *pszFont, const int &nFontSize);
	// 设置波形下方文字字体
	// pszFont -- 字体
	// nFontSize -- 字大小
	// 返回值：true成功，false失败
	bool GDI_SetReportEndFont(const TCHAR *pszFont, const int &nFontSize);
	// 设置报表标题头文字
	void GDI_SetReportTitleText(const TCHAR *pszText);
	// 设置波形前文字
	void GDI_SetReportHeaderText(const TCHAR *pszText);
	// 设置波形后文字
	void GDI_SetReportEndText(const TCHAR *pszText);
	// 设置报表标题头位置
	void GDI_SetReportTitlePos(const double &dXPos, const double &dYPos);
	// 设置波形前文字位置
	void GDI_SetReportHeaderPos(const double &dXPos, const double &dYPos);
	// 设置波形后文字位置
	void GDI_SetReportEndPos(const double &dXPos, const double &dYPos);
	// 设置波形位置
	// dXStartPos -- 起始横坐标位置
	// dYStartPos -- 起始纵坐标位置
	// dXEndPos -- 终止横坐标位置
	// dYEndPos -- 终止纵坐标位置
	void GDI_SetReportWavePos(CDC *pDC, CPrintInfo* pInfo, const double &dXStartPos, const double &dYStartPos, const double &dXEndPos,
		const double &dYEndPos);
	//设置报表绘图区域
	// 显示一帧画面用于报表的坐标值, iData -- 数据曲线, iDataLen -- 扫描点数
	bool GDI_SetRectReport(const RECT &ReportRect, const POINT &StartPoint);

	// Init ///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// 初始化绘图类
	// Rect -- 窗体位置, hWnd -- 窗体句柄, bkColor -- 绘图背景色, 
	// GridColor -- 绘图表格色, iGridBorderWidth -- 表格边框宽度,
	// iGridLineWidth -- 表格线宽度, LineColor -- 数据曲线颜色,
	// iLineWidth -- 数据曲线宽度, TextColor -- 文字颜色, mkrColor -- 频标色
	// imkrType -- 频标特征
	bool GDI_Init(const RECT &rect, const HWND &hWnd = NULL, const COLORREF &bkColor = RGB(50, 50, 50),
		const COLORREF &GridColor = RGB(0, 255, 0), const int &iGridBorderWidth = 2, const int &iGridLineWidth = 1,
		const COLORREF &LineColor = RGB(255, 255, 0), const int &iLineWidth = 1,
		const COLORREF &TextColor = RGB(255, 255, 0), const COLORREF &mkrColor = RGB(0, 255, 0),
		const int &imkrType = 0);
	void GDI_Exit();	// 退出GDI绘图系统
	bool GDI_SetBKColor(const COLORREF &bkColor);	//设置绘图背景色
	bool GDI_SetRect(const RECT &rect);	// 设置绘图区域
	void GDI_GetRect(RECT &rect);		// 获得绘图区域

	CDevGDI(void);
	virtual ~CDevGDI(void);

	// Variables /////////////////////////////////////////////////////////////////////////////////////////////////
	//
	HWND m_hwnd;			// 绘图窗体句柄
	HDC m_hdc;				// 当前绘图设备DC

protected:
	// MKR ///////////////////////////////////////////////////////////////////////////
	//
	// 显示全部Mkr的函数
	void MkrFunc(const HDC &memDC, const double *pdData, const int &iDataLen, const double *pdData2, const int &nDataLen2, const double *pdData3,
		const int &nDataLen3, const double *pdData4, const int &nDataLen4, const double *pdData5, const int &nDataLen5, const double *pdData6,
		const int &nDataLen6, const double *pdData7, const int &nDataLen7, const double *pdData8, const int &nDataLen8, const double *pdData9,
		const int &nDataLen9, const double *pdData10, const int &nDataLen10, const double *pdData11, const int &nDataLen11, const double *pdData12,
		const int &nDataLen12, const double *pdData13, const int &nDataLen13, const double *pdData14, const int &nDataLen14, const double *pdData15,
		const int &nDataLen15, const double *pdData16, const int &nDataLen16, const double *pdData17, const int &nDataLen17, const double *pdData18,
		const int &nDataLen18, const double *pdData19, const int &nDataLen19, const double *pdData20, const int &nDataLen20);
	// 绘制Mkr
	void DrawMkr(const HDC &memDC, const double *pdData, const int &iDataLen, const int &iMkrID, const int &nWaveID);

	// Grid //////////////////////////////////////////////////////////////////////////
	//
	void DrawQamZoom(const HDC &memDC);	// 绘制星座图的象限框
	void DrawHorizontal3Grid(const HDC &memDC);	//绘制横向3个波形表格
	void DrawLgGrid(const HDC &memDC);		// 绘制单波对数横坐标表格
	void DrawDoubleGrid(const HDC &memDC);	// 绘制上下两个表格函数
	bool DrawGrid(const HDC &memDC);	// 绘制表格函数
	bool DrawGridSpectrum(const HDC &memDC);	// 绘制频谱仪的表格函数，仿DS8821
	bool DrawGridCenterRound(const HDC &memDC);	// 绘制表格中心的圆圈
	bool DrawGridCenterPoint(const HDC &memDC);	// 绘制表格中心点

	// Text //////////////////////////////////////////////////////////////////////////
	//
	void DrawMultiText(const HDC &memDC);	// 绘制自定义多行文字
	void DrawYDoubleText(const HDC &memDC);	// 绘制双波形窗口Y值
	void DrawCoor( const HDC &memDC );			// 绘制坐标仿8831 wangzheng 2008-09-11
	// 数值显示
	// memDC -- 内存设备DC
	// iVal -- 被显示的数值
	// szDepartment -- 显示单位字符串
	// iXLocation -- 显示位置横坐标
	// iYLocation -- 显示位置纵坐标
	// iDir -- 显示对齐位, 0左对齐, 1右对齐, 2中间对齐
	void ShowText(const HDC &memDC, const double &dVal, const TCHAR *szDepartment, const int &iXLocation,
		const int &iYLocation, const char &iDir);
	void DrawXText(const HDC &memDC);	// 绘制起始、中止频率/时间值，文本输出
	void DrawXTextHorizontal3Grid(const HDC &memDC);	// 绘制起始、中止频率/时间值，文本输出--横向3个波形
	void DrawYText(const HDC &memDC);	// 绘图起始、中止V/db值
	void ShowManualText(const HDC &memDC);	// 显示自定义文字

	// Limit line ////////////////////////////////////////////////////////////////////
	//
	void DrawLimitLine(const HDC &memDC);	// 绘制Limit Line

	// Calucate //////////////////////////////////////////////////////////////////////
	//
	// 根据当前波形数据ID计算出当前绘图横坐标值
	// dWavePixNum -- 波形绘图区的宽度
	// nDataLen -- 曲线总数据量
	// nDataID -- 当前曲线的数据id
	// return value -- 绘图曲线的横坐标值
	inline int GetWaveLineX(const double &dWavePixNum, const int &nDataLen, const int &nDataID);
	// 根据波形当前横坐标值计算出屏幕横坐标值
	inline int GetWaveLineX(const double &dData);
	// 根据当前波形数据ID计算出当前绘图横坐标值
	// dWavePixNum -- 波形绘图区的宽度
	// nDataLen -- 曲线总数据量
	// dDataID -- 当前曲线的数据id, 插值描述方式
	// return value -- 绘图曲线的横坐标值
	inline int GetWaveLineX(const double &dWavePixNum, const int &nDataLen, const double &dDataID);
	// 根据波形纵坐标2值计算出屏幕纵坐标值
	inline int GetWaveLineYSpecial(const double &dData);
	// 根据波形当前值计算出屏幕纵坐标值
	inline int GetWaveLineY(const double &dData);
	// 根据波形当前值计算出屏幕纵坐标值，双窗口上
	inline int GetWaveLineYUp(const double &dData);
	// 根据波形当前值计算出屏幕纵坐标值，双窗口下
	inline int GetWaveLineYDown(const double &dData);

	// Scroll bar /////////////////////////////////////////////////////////////////////
	//
	void DrawScrollBar(const HDC &memDC, const int &nDataLen);	// 绘制ScrollBar

	// Mouse //////////////////////////////////////////////////////////////////////////
	//
	void DrawMouseRect(const HDC &memDC);	//绘制鼠标选择方框

	// Report /////////////////////////////////////////////////////////////////////////
	//
	void DrawReportText(CDC *pDC, CPrintInfo* pInfo);	// 绘制报表文字

	// Varible /////////////////////////////////////////////////////////////////////////
	//
	const static int N_MAX_X_SCREEN = 1920;		// 屏幕最大分辨率支持（横向）
	const static int N_MAX_Y_SCREEN = 1080;		// 屏幕最大分辨率支持（纵向）
	const static int I_WAVE_PIX_MOVE = 10;
	const static int N_LIMIT_COLOR_ID_OFFSET = 4;	// 合格线ID偏移量
	struct tagMouseLine m_MouseLine;
	tagREPORT m_ReportData;		// 波形属性数据结构

private:
	// 光谱图 Spectrogram //////////////////////////////////////////////////////////////
	//
	// 绘制光谱图文字
	// memDC -- 绘图内存DC
	// pColor -- 颜色表
	// pdLevel -- 幅度表
	// nColorNum -- 幅度颜色表的数量
	void DrawSpecgView(HDC &memDC, const COLORREF *pColor, const double *pdLevel, const int &nColorNum);
	// 绘制光谱图的Mkr
	// memDC -- 绘图内存DC
	// nDataLen -- 每场波形数据长度
	// nWaveNum -- 光谱图波形数量
	void DrawSpectrogramMkr(HDC &memDC, const int &nDataLen, const int &nWaveNum);
	// 绘制光谱图波形图
	// memDC -- 绘图内存DC
	// pdData -- 波形数据
	// nWaveNum -- 波形条数
	// nDataLen -- 每条波形的点数
	// pColor -- 颜色表
	// pdLevel -- 幅度表
	// nColorNum -- 幅度颜色表的数量
	// 返回值：true成功，false失败，可能是由于内存申请失败造成
	bool DrawSpectrogram(HDC &memDC, const double *pdData, const int &nWaveNum, const int &nDataLen, const COLORREF *pColor, const double *pdLevel,
		const int &nColorNum);
	//

	// Draw line by limit //////////////////////////////////////////////////////////////
	//
	// 根据合格线找到当前点应该设置的颜色，回界交叉
	// Color -- 当前点的颜色
	// dYPos -- 当前点的纵坐标值
	// ..... -- 所有合格线的值
	// pbzPriority -- 合格线的使能
	// 返回值：越过合格线的ID
	char FindPointColorOver(COLORREF &Color, const double &dYPos, const double &dUpLimit1Y, const double &dDownLimit1Y, const double &dUpLimit2Y,
		const double &dDownLimit2Y, const double &dUpLimit3Y, const double &dDownLimit3Y, const double &dUpLimit4Y, const double &dDownLimit4Y,
		const double &dUpLimit5Y, const double &dDownLimit5Y, const bool *pbzPriority);
	// 根据合格线找到当前点应该设置的颜色
	// Color -- 当前点的颜色
	// dYPos -- 当前点的纵坐标值
	// ..... -- 所有合格线的值
	// pbzPriority -- 合格线的使能
	// 返回值：越过合格线的ID
	char FindPointColor(COLORREF &Color, const double &dYPos, const double &dUpLimit1Y, const double &dDownLimit1Y, const double &dUpLimit2Y,
		const double &dDownLimit2Y, const double &dUpLimit3Y, const double &dDownLimit3Y, const double &dUpLimit4Y, const double &dDownLimit4Y,
		const double &dUpLimit5Y, const double &dDownLimit5Y, const bool *pbzPriority);
	// 找到波形于合格线的交叉点坐标
	// nXPos, nYPos -- 交叉点的横纵坐标值
	// dStartX, dStartY, dEndX, dEndY -- 波形的起始横、纵坐标和终止横、纵坐标
	// dEndLimitX, dEndLimitY -- 合格线的起始横、纵坐标和终止横、纵坐标值
	// nDataLen -- 波形数据长度
	// nID -- 波形ID
	// 返回值：true存在交叉点，false不存在交叉点
	bool FindCrossPoint(int &nXPos, int &nYPos, const double &dStartX, const double &dStartY, const double &dEndX, const double &dEndY, const double &dStartLimitY,
		const double &dEndLimitY, const int &nDataLen, const int &nID);
	// 根据波形的两个采样点以及合格线来确定两个采样点间的颜色变化过程
	// memDC -- 绘图内存DC
	// dXStart -- X轴原起始坐标, dXEnd -- X轴原终止坐标, dYStart -- Y轴原起始坐标, dYEnd -- Y轴原终止坐标
	// dUpLimit1Start, dUpLimit1End, dUpLimit2Start, dUpLimit2End, dUpLimit3Start, dUpLimit3End, dUpLimit4Start, dUpLimit4End, dUpLimit5Start, dUpLimit5End,
	// dDownLimit1Start, dDownLimit1End, dDownLimit2Start, dDownLimit2End, dDownLimit3Start, dDownLimit3End, dDownLimit4Start, dDownLimit4End,
	// dDownLimit5Start, dDownLimit5End, -- 分别是5条上、下门限的两个原关键点坐标
	// pbzPriority -- 合格线使能
	// nDataLen -- 当前波形数据长度
	// nID -- 当前点的ID
	// LineColor -- 当前波形颜色
	// 返回值：true包含变换颜色，false：无变换颜色
	bool GetLineColorByLimit(HDC &memDC, const double &dXStart, const double &dXEnd, const double &dYStart, const double &dYEnd,
		const double &dUpLimit1Start, const double &dUpLimit1End, const double &dUpLimit2Start, const double &dUpLimit2End,
		const double &dUpLimit3Start, const double &dUpLimit3End, const double &dUpLimit4Start, const double &dUpLimit4End,
		const double &dUpLimit5Start, const double &dUpLimit5End,
		const double &dDownLimit1Start, const double &dDownLimit1End, const double &dDownLimit2Start, const double &dDownLimit2End,
		const double &dDownLimit3Start, const double &dDownLimit3End, const double &dDownLimit4Start, const double &dDownLimit4End,
		const double &dDownLimit5Start, const double &dDownLimit5End, const bool *pbzPriority, const int &nDataLen, const int &nID, const COLORREF &LineColor);
	// 绘制波形，颜色按照合格线设置来区分，幅度高于UpLimit的，按照UpLimit的颜色显示，变量定义中数字大的显示优先级
	// 高于小的，UpLimit的显示优先级高于DownLimit的优先级
	// pdCurrent -- 采样波形数据
	// nCurrent --采样波形数据长度
	// pdMax -- 最大保持波形数据
	// nMax -- 最大保持波形数据长度
	// pdMin -- 最小保持波形数据
	// nMin -- 最小保持波形数据长度
	// pdAverage -- 平均值波形数据
	// nAverage -- 平均值波形数据长度
	// pdUpLimit1 -- 上合格线1数据
	// nUpLimit1 -- 上合格线1数据长度
	// pdDownLimit1 -- 下合格线1数据
	// nDownLimit1 -- 下合格线1数据长度
	// pdUpLimit2 -- 上合格线2数据
	// nUpLimit2 -- 上合格线2数据长度
	// pdDownLimit2 -- 下合格线2数据
	// nDownLimit2 -- 下合格线2数据长度
	// pdUpLimit3 -- 上合格线3数据
	// nUpLimit3 -- 上合格线3数据长度
	// pdDownLimit3 -- 下合格线3数据
	// nDownLimit3 -- 下合格线3数据长度
	// pdUpLimit4 -- 上合格线4数据
	// nUpLimit4 -- 上合格线4数据长度
	// pdDownLimit4 -- 下合格线4数据
	// nDownLimit4 -- 下合格线4数据长度
	// pdUpLimit5 -- 上合格先5数据
	// nUpLimit5 -- 上合格线5数据长度
	// pdDownLimit5 -- 下合格线5数据
	// nDownLimit5 -- 下合格线5数据长度
	// bzPriority -- 合格线使能，false表示关闭，true表示打开
	// 返回值：true执行成功，false执行失败
	bool DrawLineByLimit(HDC &memDC, const double *pdCurrent, const int &nCurrent, const double *pdMax, const int &nMax,
		const double *pdMin, const int &nMin, const double *pdAverage, const int &nAverage,
		const double *pdUpLimit1, const int &nUpLimit1, const double *pdDownLimit1, const int &nDownLimit1,
		const double *pdUpLimit2, const int &nUpLimit2, const double *pdDownLimit2, const int &nDownLimit2,
		const double *pdUpLimit3, const int &nUpLimit3, const double *pdDownLimit3, const int &nDownLimit3,
		const double *pdUpLimit4, const int &nUpLimit4, const double *pdDownLimit4, const int &nDownLimit4,
		const double *pdUpLimit5, const int &nUpLimit5, const double *pdDownLimit5, const int &nDownLimit5, const bool *bzPriority);

	// QAM /////////////////////////////////////////////////////////////////////////////////////
	//
	// 绘制星座图的波形数据
	// memDC -- 内存DC
	// pnData -- 星座图数据结构体
	// nDataLen -- 星座图点数
	// bManualColor -- 星座图数据自定义颜色开关
	// 返回值：true执行成功，false执行失败
	bool DrawQamData(const HDC &memDC, const struct tagCoordinate *pnData, const int &nDataLen,
		const bool &bManualColor);

	// Calucate /////////////////////////////////////////////////////////////////////////////////
	//
	// 查找波形最近的峰值
	void FindMaxWaveVal(const double* pdData, const int &nDataLen, const int &nMkrID);

	// Draw line ////////////////////////////////////////////////////////////////////////////////
	//
	// 绘制横向3个波形曲线
	void DrawHorizontal3Line(const HDC &memDC, const double *pdData, const int &nDataLen, const double *pdData2,
		const int &nDataLen2, const double *pdData3, const int nDataLen3);
	// 绘制两条波形曲线，用于双窗口
	void DrawDoubleWndLine(const HDC &memDC, const double* pdData1,
		const int &nDataLen1, const double* pdData2, const int &nDataLen2);
	// 绘制波形曲线, 自定义大小
	bool DrawLineSpecialLen(const HDC &memDC, const double* pdData, const int &nDataLen, const double* pdData2,
		const int &nDataLen2, const double *pdData3, const int &nDataLen3);
	// 绘制波形曲线
	bool DrawLineAdjust(const HDC &memDC, const double *pdData, const int &iDataLen, const double *pdData2, const int &nDataLen2, const double *pdData3,
		const int &nDataLen3, const double *pdData4, const int &nDataLen4, const double *pdData5, const int &nDataLen5, const double *pdData6,
		const int &nDataLen6, const double *pdData7, const int &nDataLen7, const double *pdData8, const int &nDataLen8, const double *pdData9,
		const int &nDataLen9, const double *pdData10, const int &nDataLen10, const double *pdData11, const int &nDataLen11, const double *pdData12,
		const int &nDataLen12, const double *pdData13, const int &nDataLen13, const double *pdData14, const int &nDataLen14, const double *pdData15,
		const int &nDataLen15, const double *pdData16, const int &nDataLen16, const double *pdData17, const int &nDataLen17, const double *pdData18,
		const int &nDataLen18, const double *pdData19, const int &nDataLen19, const double *pdData20, const int &nDataLen20);
	// 绘制波形曲线，支持波形数据最大点数
	bool DrawLineEnableMaxPointNum(const HDC &memDC, const double *pdData, const int &nDataLen,
		const int &nMaxDataLen);

	// Variable /////////////////////////////////////////////////////////////////////////////////
	//
	struct tagGridNum m_GridNum;	// 表格数量
	struct tagManualText m_ManualText[N_MAX_MANUAL_TEXT_NUMBER];	// 自定义文字
	struct tagMultiText m_MultiText[I_WAVE_NUM];	// 多行文字
	TAG_LimitLine m_LimitLineTag[I_LIMITLINE_NUMBER];	// LimitLine数据结构
	tagCoorText m_CoorData[20];			// 仿8831的坐标数据 wangzheng 2008-09-11
	RECT m_rect;					// 绘图区位置
	POINT m_StartPoint;				// 绘图起始位置
	HDC m_hMemDC;					// 绘图内存DC
	HBITMAP m_hBitmap;				// 绘图内存位图
	COLORREF m_MouseLineColor;		// 鼠标拖动方块的颜色
	COLORREF m_bkColor;				// 背景色
	COLORREF m_GridColor;			// 删格色
	COLORREF m_LineColor[I_WAVE_NUM];	// 曲线色
	COLORREF m_TextColor;			// 文本色
	COLORREF m_ActiveMkrColor;		// 当前或动频标的颜色
	COLORREF m_mkrColor[I_MKR_NUMBER][I_WAVE_NUM];	// 频标色
	COLORREF m_MkrLineColor;		// 频标线的颜色
	COLORREF m_ScrollBarHightLight;	// 滑动条高亮度显示颜色
	COLORREF m_GridRoundColor;		// 删格中心圈的颜色
	COLORREF m_QamZoomColor;		// 象限框的颜色
	COLORREF m_MkrTextColor[I_MKR_NUMBER][I_WAVE_NUM];
	COLORREF m_SpectrogramMkrColor;	// 光谱图Mkr颜色

	int m_nQamZoomLineWidth;		// 象限框的线宽
	int m_iGridBorderWidth;			// 删格边框宽度
	int m_iXGridDepart;				// X轴表格单位距离
	int m_iYGridDepart;				// Y轴表格单位距离
	int m_iGridLineWidth;			// 删格线宽度
	int m_iLineWidth[I_WAVE_NUM];	// 曲线宽度
	int m_imkrType;					// 频标特征
	int m_iBorderGridTop;			// 删格距边框的距离 -- 顶部
	int m_iBorderGridBottom;		// 删格距边框的距离 -- 底部
	int m_iBorderGridRight;			// 删格距边框的距离 -- 右方
	int m_iBorderGridLeft;			// 删格距边框的距离 -- 左侧
	int m_iMkrValue[I_MKR_NUMBER];	// 频标横坐标值
	int m_iActiveMkr;				// 当前被操作的频标的ID
	int m_nActiveLimit;				// 当前被操作的Limit Line
	int m_nRateSizeX;				// 横坐标拉伸值,百分比值
	int m_nWaveStartPos;			// 波形起始位置
	int m_nLimitLineNum;			// 当前Limit line 的数量
	int m_nStartMouseX;				// 鼠标左键按下时，鼠标坐标的初始值，用于滚动条
	int m_nXTextOffsetY;			// 横坐标文字的纵坐标偏移量
	int m_nYTextOffsetX;			// 纵坐标文字的横坐标偏移量
	int m_nQamZoomNum;				// 星座图象限的数值
	int m_nMkrXKeepType;			// mkr横向偏移属性，详见DEV_MKR_STYLE
	int m_nManualTextNum;			// 自定义文字数量
	int m_nLimitTextDock[I_LIMITLINE_NUMBER];	// Limit文字停靠属性
	int m_nMouseLineStartX;			// 鼠标绘制波形的起始X坐标
	int m_nSpectrogramMkrX;			// 光谱图横坐标Mkr停靠位置，采样点ID
	int m_nSpectrogramMkrY;			// 光谱图纵坐标Mkr停靠位置，采样波形ID

	double m_dMouseLineStartY;		// 鼠标绘制波形的起始Y坐标
	double m_dzMkrVal[I_MKR_NUMBER];	// 手动mkr的值
	double m_dGridPointRate;		// 删格中心点大小比例，0.0 -- 1.0
	double m_dGridRoundRate;		// 删格中心圈大小比例，0.0 -- 1.0
	double m_dStartX;				// 横坐标起始值
	double m_dEndX;					// 横坐标中止值
	double m_dFullStartX;			// 全景横坐标起始值
	double m_dFullEndX;				// 全景横坐标中止值
	double m_dStartY;				// 纵坐标起始值
	double m_dEndY;					// 纵坐标中止值
	double m_dSpecialStartY;		// 坐标2起始值
	double m_dSpecialEndY;			// 坐标2中指值
	double m_dWavePixNum;			// 波形宽度
	double m_dScrollBarStartPos;	// 滑动条开始位置，横坐标
	double m_dScrollBarScrollWidth;	// 滑动条的宽度，鼠标可拖动的滑块宽度
	double m_dLimitStep;			// Limit的步进值

	TCHAR m_czMkrVal[I_MKR_NUMBER][N_TEXT_LEN];	// 手动mkr的值
	TCHAR m_czViewPrecision[8];
	TCHAR m_szXDepartment[I_DEPARTMENT_LEN];	// 横坐标单位
	TCHAR m_szYDepartment[I_DEPARTMENT_LEN];	// 纵坐标单位
	TCHAR m_szYDep2nd[I_DEPARTMENT_LEN];		// 第二纵坐标单位
	TCHAR m_szMkrDepart[I_MKR_NUMBER][I_DEPARTMENT_LEN];	// 频标单位
	TCHAR m_szMkrDep2nd[I_MKR_NUMBER][I_DEPARTMENT_LEN];	// 频标第二纵坐标单位
	TCHAR m_szXStart[N_TEXT_LEN];		// 横坐标起始值
	TCHAR m_szXCenter[N_TEXT_LEN];		// 横坐标中心值
	TCHAR m_szXEnd[N_TEXT_LEN];			// 横坐标截止值
	CString m_szXCurrent;		// 当前频标横坐标值
	CStringArray m_szzYCurrent;	// 自定义Y轴显示坐标值

	TCHAR m_czPrintFont[10];	// 打印字体
	TCHAR m_czTextFont[10];		// 实时绘图波形字体
	int m_nPrintFontSize;		// 打印文字大小
	int m_nTextFontSize;		// 实时绘图波形字体大小

	HBRUSH m_brBackground;	// 背景画刷
	HBRUSH m_brCross;		// 交叉画刷
	HBITMAP m_OldBitmap;	// 备份当前位图设备

	Cdeskland m_GuangCom;

	BYTE m_ucScrollBarActiveButton;	// 当前scrollbar的高亮活动状态
	BYTE m_ucGridType;				// 绘图表格类型
	BYTE m_bManualMkrVal;			// 手动设置频标值
	BYTE m_uczWaveDockY[I_WAVE_NUM];// 波形使用哪个坐标系，0或1，0为左侧坐标系，1为右侧坐标系
	BYTE m_ucUseSpectrogramMkr;		// 活动光谱Mkr开关，值定义详见 SPECTROGRAM_MKR

	bool m_bGrid;					// 是否显示删格线, true显示, false不显示
	bool m_bGridCenterRound;		// 删格方块中心圈
	bool m_bGridCenterPoint;		// 删格方块中心点
	bool m_bMkr[I_MKR_NUMBER];		// 是否显示频标
	bool m_bMkrStatus[I_MKR_NUMBER][I_WAVE_NUM];	// 波形支持数量
	bool m_bEnalbeScrollBar;		// ScrollBar 是否显示标志, true显示 false不显示
	bool m_bEnableMkrDepartment;	// 是否显示频标纵坐标单位, true显示 false不显示
	bool m_bEnableMkrLine;			// 是否显示、隐藏频标线
	bool m_bEnableMkrXLine;			// 横向频标线开关
	bool m_bEnableMkrYLine;			// 纵向频标线开关
	bool m_bEnable2ndY;				// 是否是否显示第二个纵坐标值
	bool m_bMkrKeepMaxVal;			// 频标是否跟踪波形的峰值，true跟踪，false不跟踪
	bool m_bEnableXText;			// 显示横坐标值
	bool m_bEnableYText;			// 显示纵坐标值
	bool m_bQamZoom;				// 星座图象限的开关
	bool m_bEnableManualXText;		// 自定义X轴坐标内容
	bool m_bEnableManualYText;		// 自定义Y轴坐标内容
	bool m_bEnableMText;			// 自定义文字信息开关
	bool m_bEnableMrkXText;			// 左上角频标横坐标值开关  wangzheng 2008-08-04
	bool m_bEnableMrkYText;			// 频标纵坐标文字开关
	bool m_bEnableCoorText;			// 显示类似8831上的坐标数据 wangzheng 2008-09-11
	bool m_bRectChange;				// 绘图区窗口尺寸变化标志，true窗口尺寸发生变化，false未发生变化
	bool m_bMkrAutoKeepX;			// Mkr自动跟踪横坐标
	bool m_bSpectrogramMkrX;		// 光谱横坐标游标开关
	bool m_bSpectrogramMkrY;		// 光谱纵坐标游标开关
	bool m_bEnableSpecgView;		// 光谱图纵坐标说明开关
};
