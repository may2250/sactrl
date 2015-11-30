// deskland ��������������ʾ��, GDI��ʽ, �汾: 1.58.44
// designed by deskland@msn.com
// Final edit time at: 2010-06-07
// history: 2008-02-25 1.20		����mkr�������ԣ����;�����������
//			2008-02-28 1.20.26	����������ֵ������С�ɳ���ͼ����
//			2008-03-21 1.21		�������ѡ�����Ƶ��Ĺ���
//			2008-03-26 1.22		���ӻƵ����ɫ�������ƹ���
//			2008-04-18 1.23		���ӻ�ͼ���Ϸ��Զ�����ʾ���ֹ�5��,��������,�ָ���,����.
//			2008-04-21 1.24		���ӻ����������м��޼������ͼ���ԣ�N_HORBAR_NO_SEP
//			2008-04-24 1.25.27	�����Զ�����ʾY���������ֹ���
//			2008-04-24 1.26		�����Զ���mkrֵ����ʾ����
//			2008-04-28 1.26.28	����������ʾ���Զ�ʧ���ݵ�����
//			2008-04-29 1.26.29	������������Сֵʱ�޷���ʾ����
//			2008-04-30 1.27		���ӽ���ǰ���α���Ϊͼ���ļ��Ĺ���
//			2008-05-06 1.27.30	������ͼN_HORBAR_NO_SEP���Ե����������
//			2008-05-07 1.27.31	������ͼN_HORBAR_NO_SEP���Ե����������(��2��3����)
//			2008-05-07 1.28		����N_HORBAR_NO_SEP_ENABLE_MIN��ͼ���ԣ���ʾ��ͼ������Сֵ��N_HORBAR_NO_SEP��Ϊ����ʾ��ͼ������Сֵ
//			2008-06-10 1.29.32	���ӻ�ͼ����������14��
//			2008-06-11 1.30		���ӻ�ͼ�ӿ�2άָ������
//			2008-06-12 1.31		���ӻ�ͼ����������20��
//			2008-06-23 1.32.33	���Ӵ�ӡ������������20��������֧�����ô�ӡ����ʹ�С
//			2008-07-31 1.33		����Mkr�ڲ�ͬ���������ϵ���ɫ����
//			2008-08-05 1.34		����Mkr���ֵ���ɫ����
//			2008-08-11 1.35		���ӶԱ������Ͳ����������ֵ�֧�֣�����������������ִ�С
//			2008-08-20 1.36		�Ľ�����ͼ�ӿں�������Ӧ�����ݽṹ��ʹ��������ͼ��ÿһ��������Զ�����ɫ���������¼���
//			2008-09-18 1.37		���Ӳο���������ʾ���Զ������ֻ���ʾ����ֵ��֧����ʾλ���������ã���֧�ֲο����ƶ������̲���������ʽ����귽ʽ��
//			2008-10-13 1.38.34	����ʵʱ������ʾ���壬�Ľ�������ʾλ�ò�׼ȷ������
//			2008-10-31 1.38.35	����������ʾ�޷��ﵽ�ұ߽��bug
//			2008-11-03 1.38.36	������������ʾ�����bug
//			2008-11-25 1.39		��������ƶ����Ʋ��εĹ��ܣ�Ϳѻ�ķ�ʽ
//			2009-01-06 1.40		Ƶ����ģʽʱ����Ƶ�����ǻ�����
//			2009-03-04 1.41		����Ƶ���ߵĺ��ݷ����ߵĶ�������
//			2009-03-17 1.42		��������ͼ����������ʾ������DrawQamFill�Ĺ���
//			2009-03-26 1.42.37	��������ͼ����ʱ�����ܵ�ɾ���������bug
//			2009-05-20 1.42.38	�������Ϳѻʽ��ͼ���һ�����޷����ϵ�bug(GDI_SetMouseWavePixel)
//			2009-06-30 1.42.39	����Limit������ʾλ�ò���ȷ��bug
//			2009-07-09 1.43		��չLimit������ʾ���ܣ�ÿ��Limit�ߵ���������λ�����Ժ���������
//			2009-07-09 1.43.40	����I_HORIZONTAL_BAR���ηɵ��߿����bug��������ǰģʽ��MKRλ�ò���ȷ��bug
//			2009-08-18 1.44		��ɰ��պϸ������ֲ�����ɫ���ܣ������պϸ������ߵ���ɫ��Χ��������ʾ���Σ������һ���ϸ��ߵ�ֵ��ߣ���10����ͣ����ε�ǰֵ���ںϸ���
//								���պϸ��ߵ���ɫ��ʾ�����û�����κ�һ���ϸ��߰��ղ���ԭ����ɫ��ʾ
//			2009-08-19 1.44.41	�������պϸ�����ɫ��ʾ������ɫż�����ִ�λ��bug
//			2009-09-03 1.45		��Mkr Line�����������ѡ��һ��Ƶ�갴��Mkr line�Ļ�ͼ��Χ
//			2009-09-04 1.46		�����ƶ�������ʱMkr������ֵ���ֲ����Ĺ��ܣ��������޸ĺ�����ֵʱMkr������ֵ�������
//			2009-09-10 1.47		�������ò���������ʼλ�ù��ܣ�����MKR��ʼλ����ȷ��Bug
//			2009-09-17 1.48		����˫������ϵ����Ϊ�������������꣬�������ο�������ѡ������һ��������Ϊ�ο������νӿڲ���
//			2009-09-30 1.49		���ӹ���ͼ����
//			2009-10-10 1.50		���ӹ���ͼmkr���ܣ�֧�����ͼ��̲�������������������λ�ò�������bug
//			2009-10-12 1.51		���ӹ���ͼ�����еĿ�ֵ��ʾ����
//			2009-11-11 1.52		���ӹ���ͼ���α���ͼƬ����
//			2010-01-07 1.53		����GDI_SetLimitLineVal������ֵ��������
//			2010-01-15 1.53.42	������դ��λ��һ��������������
//			2010-04-08 1.54		������ʾ����������Ϣ
//			2010-05-05 1.55		���ӹ���ͼ�з��ȶ�����ɫ˵��
//			2010-05-14 1.56		����Mkr����������ͣ�����Ϸ����ܣ���ʹ������Mkr Lineʱ��Ч�������Զ������ֹ��ܣ�ʹλ�ðڷŸ�����
//			2010-05-25 1.56.43	����Limit Line������ʾ������Ч��Bug
//			2010-05-26 1.57		��������Limit line�߿���������
//			2010-05-27 1.58		����Limit Line Style�ӿں���
//			2010-06-07 1.58.44	����SavePicture���޷���ʾ���в���˵�����ֵ�bug

#pragma once

#include "deskland.h"
#include <deque>

#pragma warning (disable:4819)

using namespace std;

enum MKR_MOVE				// MKR�ƶ�����
{
	MKR_MOVE_LEFT = 0,		// �����ƶ�
	MKR_MOVE_RIGHT = 1,		// �����ƶ�
	MKR_MOVE_UP = 2,		// �����ƶ�
	MKR_MOVE_DOWN = 3		// �����ƶ�
};

enum DEFAULT_BORDER_GRID_POS			// ȱʡդ��߿��봰�ڵľ���
{
	DEFAULT_BORDER_GRID_LEFT = 60,		// ��߾�
	DEFAULT_BORDER_GRID_RIGHT = 25,		// �ұ߾�
	DEFAULT_BORDER_GRID_TOP = 15,		// �ϱ߾�
	DEFAULT_BORDER_GRID_BOTTOM = 30		// �±߾�
};

enum SPECTROGRAM_MKR	// ����ͼmkr����
{
	SPECTROGRAM_MKR_NONE = 0,	// δѡ���δ����
	SPECTROGRAM_MKR_X = 1,		// ʹ�ú���mkr
	SPECTROGRAM_MKR_Y = 2		// ʹ������mkr
};

enum Y_COORDINATE_DEF		// ����ϵ����
{
	Y_LEFT_COORDINATE_DOCK = 0,		// �������ϵ
	Y_RIGHT_COORDINATE_DOCK = 1		// �Ҳ�����ϵ
};

enum LIMI_MOVE_TYPE		// �ϸ������ƽ�Ʒ���
{
	LIMIT_MOVE_UPDOWN = 0,		// �����ƶ�
	LIMIT_MOVE_LEFTRIGHT = 1,	// �����ƶ�
	LIMIT_MOVE_ALL				// ȫ��λ�ƶ�
};

enum LIMIT_TYPE_DEF	// �ϸ������Ͷ���
{
	LIMIT_NORMAL = 20,		// ����
	LIMIT_OVERFLOW = 21,	// Խ�罻��
	LIMIT_UNDERBELOW =22	// �ؽ罻��
};

enum DEV_KEEP					// ��ʾԪ��ͣ��λ��
{
	DEV_KEEP_LEFT = 0,			// ���ͣ��
	DEV_KEEP_TOP_LEFT = 1,		// ����ͣ��
	DEV_KEEP_TOP = 2,			// �Ϸ�ͣ��
	DEV_KEEP_CENTER = 3,		// �м�ͣ��
	DEV_KEEP_TOP_RIGHT = 4,		// ���Ϸ�ͣ��
	DEV_KEEP_RIGHT = 5,			// �Ҳ�ͣ��
	DEV_KEEP_BOTTOM_RIGHT = 6,	// ���·�ͣ��
	DEV_KEEP_BOTTOM = 7,		// �·�ͣ��
	DEV_KEEP_BOTTOM_LEFT = 8,	// ���·�ͣ��
	DEV_KEEP_DEFINE_END = 255	// �������
};

enum DEV_MOVE				// ��ͼȥ�ƶ�����Ԫ������
{
	DEV_LIMIT_UP = 0,		// �ο�������
	DEV_LIMIT_DOWN = 1,		// �ο�������
	DEV_MKR_LEFT = 2,		// �α�����
	DEV_MKR_RIGHT = 3,		// �α�����
	DEV_LIMIT_LEFT = 4,		// �ο�������
	DEV_LIMIT_RIGHT = 5		// �ο�������
};

enum DEV_MKR_VALUE			// Ƶ����������ֵ��ʾ����
{
	DEV_MKR_VALUE_AUTO = 0,	// �Զ���ʾ
	DEV_MKR_VALUE_MANUAL_DIGIT = 1,	// �ֶ�������ʾ
	DEV_MKR_VALEE_MANUAL_CHAR = 2	// �ֶ��ַ���ʾ
};

enum DEV_MKR_STYLE
{
	DEV_MKR_TRIANGLE = 0,	// ������Ƶ��
	DEV_MKR_DIAMOND = 1,	// ����Ƶ��
	DEV_MKR_KEEP_LEFT = 2,	// MKR���ֺ��������
	DEV_MKR_KEEP_CENTER = 3,// mkr�����ں��������
	DEV_MKR_KEEP_RIGHT = 4	// MKR���ֺ������Ҳ�
};

enum DEV_GRIDENUM
{
	DEV_GRID_CLASSICAL = 0,
	DEV_GRID_SPECTRUM = 1
};

enum DEVGDI_SCROLLBAR	// scrollbar �ĸ����״̬
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

enum DEVGDI_WAVETYPE					// ���ε��������
{
	DEVGDI_WAVE_AUTOADJUST = 0,			//�Զ�����
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
	N_DRAW_SMALL_POINT = 0,	// ϸ��
	I_DRAW_LINE = 1,		// ϸ��
	I_DRAW_BIG_POINT = 2,	// �ֵ�
	I_MULTICOLOR_HORIZONTAL_LINE = 4,	// ˫��ɫ����
	I_HORIZONTAL_LINE = 5,	// ����
	N_HORBAR_LINE = 6,		// ������(������ϸ��)
	N_HORBAR_NO_SEP = 7,	// ����(�޼��)
	N_HORBAR_NO_SEP_ENABLE_MIN = 8,		// ����(�޼��), ����ʹ��Сֵ������������Ͷ�
	I_HORIZONTAL_BAR = 0xFFFFE,			// ����(���������м��)
	I_SPECAL_RFANDVA = 0xFFFFF			// ����(������ʾ�ز���ƽ��������VA�ź�4�ֲ�ͬ��ɫ�Ĳ���)
};

enum DEVGDI_MANUALTEXT_POS	// �ֹ�����λ��	wangzheng 2008-06-19
{
	DEVGDI_TEXT_LEFTTOP = 0,
	DEVGDI_TEXT_LEFT = 1,
	DEVGDI_TEXT_LEFTBOTTOM = 2,
	DEVGDI_TEXT_RIGHTTOP = 3,
	DEVGDI_TEXT_RIGHT = 4,
	DEVGDI_TEXT_RIGHTBOTTOM = 5,
	DEVGDI_TEXT_CENTER = 6
};

const static double D_SPECTROGRAM_NONE_VALUE = -999999.0;	// ����ͼ�����еĿ�ֵ
const static int N_TEXT_LEN = 30;
const static int I_DEPARTMENT_LEN = 10;
const static int I_LIMITLINE_NUMBER = 3000;
const static int I_MKR_NUMBER = 10;
const static int I_WAVE_NUM = 20;
const static int N_MAX_MANUAL_TEXT_NUMBER = 5;
const static int N_SPECTROGRAM_COLOR_NUM = 20;	// ����ͼ�����ɫ����֧��

struct tagMultiText				// ��������
{
	CString szMultiLineText;	// ��������
	COLORREF TextColor;			// ������ɫ
	bool bEnableView;			// �Ƿ���ʾ����
};

struct tagMouseLine		// �����Ϣ�ṹ
{
	int nLeft;
	int nRight;
	int nTop;
	int nBottom;
	int nLButtonDown;
};

struct tagGridNum		// ��ͼ�����Ϣ�ṹ
{
	int nXNum;
	int nYNum;
};

struct tagCoordinate	// ������Ϣ�ṹ
{
	short nXCoord;
	short nYCoord;
	COLORREF PointColor;
};

struct tagManualText	// �Զ���������ʾ
{
	TCHAR czTitle[256];	// ����
	TCHAR czDetail[256];	// ����
	TCHAR czSeperate[I_DEPARTMENT_LEN];	// �ָ���
	UINT  nTextPos;						// ����λ��		wangzheng 2008-06-19
	bool bView;
};

struct tagCoorText		// ��8831���� wangzheng 2008-09-11
{
	double dData;
	TCHAR czDepartment[I_DEPARTMENT_LEN];
};

typedef struct tagReport			// ���δ�ӡ�������ݽṹ
{
	CFont TitleFont;		// ����ͷ����
	CFont HeaderTextFont;	// �����Ϸ���������
	CFont EndTextFont;		// �����·���������
	CString szTitle;		// ����ͷ����
	CString szHeader;		// �����Ϸ�����
	CString szEnd;			// �����·�����
	double dTitleX;			// ����ͷ��ʼ������
	double dTitleY;			// ����ͷ��ʼ������
	double dHeaderX;		// �����Ϸ�������ʼ������
	double dHeaderY;		// �����Ϸ�������ʼ������
	double dEndX;			// �����·�������ʼ������
	double dEndY;			// �����·�������ʼ������
	double dWaveX;			// ������ʼ������
	double dWaveY;			// ������ʼ������
	double dWaveWidth;		// ���ο��
	double dWaveHeight;		// ���θ߶�
	bool bEnableTitle;		// ����ͷ����
	bool bEnableHeader;		// �����Ϸ����ֿ���
	bool bEnableEnd;		// �����·����ֿ���
} tagREPORT;

typedef struct tagLimitLine
{
	int m_nLineWidth;				// ��ǰLimit Line���߿�
	COLORREF m_LimitLineColor;		// ��ǰLimit Line����ɫ
	double m_dzLimitLineMinVal;		// LimitLine ����Сֵ
	double m_dzLimitLineMaxVal;		// LimitLine �����ֵ
	double m_dzLimitLineStartVal;	// LimitLine ������ʼֵ
	double m_dzLimitLineEndVal;		// LimitLine ����ֹʼֵ
	TCHAR m_czText[I_DEPARTMENT_LEN];	// Limit���ϵ���ʾ���֣�����ֵ
	bool m_bzEnableLimitLine;		// �Ƿ���ʾ������Limit line
	bool m_bManualText;				// �Զ���������ʾ
	bool m_bzFullScreen;			// limitline ȫ����ʾ
	bool m_bEnableText;				// ��ʾLimit���ϵ����ֿ���
} TAG_LimitLine;

class CDevGDI
{
public:
	// Grid ///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// ��ȡ����ͼ���޿������
	// QamZoomColor -- ���޿����ɫ
	// nLineWidth -- ���޿�Ŀ��
	void GDI_GetQamZoomStyle(COLORREF &QamZoomColor, int &nLineWidth);
	// ��������ͼ���޿������
	// QamZoomColor -- ���޿����ɫ
	// nLineWidth -- ���޿�Ŀ��
	void GDI_SetQamZoomStyle(const COLORREF &QamZoomColor, const int &nLineWidth);
	void GDI_EnableQamZoom(const bool &bEnable);	// ��������ͼ�����޿����ʾ�����ؿ���
	bool GDI_IsQamZoomEnable(void);					// ��ȡ����ͼ�����޿����ʾ�����ؿ���
	// ��������ͼ������λ��
	// nZoom = 1��2��3��4 ������λ�ã�
	// ����ֵ��true���óɹ���false����ʧ��
	bool GDI_SetQamZoom(const int &nZoom);
	int GDI_GetQamZoom(void);							// ��ȡ����ͼ������λ�ã�nZoom = 1��2��3��4
	void GDI_SetGridPointRate(const double &dRate);		// ����ɾ�����ĵ���ʾ����
	void GDI_SetGridRoundRate(const double &dRate);		// ����ɾ������Ȧ��ʾ����
	double GDI_GetGridPointRate(void);					// ��ȡɾ�����ĵ���ʾ����
	double GDI_GetGridRoundRate(void);					// ��ȡɾ������Ȧ��ʾ����
	void GDI_SetGridRoundColor(const COLORREF &color);	// ����ɾ������Ȧ����ɫ
	COLORREF GDI_GetGridRoundColor(void);				// ���ɾ������Ȧ����ɫ
	void GDI_EnableGridPoint(const bool &bEnable);		// ����ɾ�����ĵ����ʾ����
	void GDI_EnableGridRound(const bool &bEnable);		// ����ɾ������Ȧ����ʾ����
	bool GDI_IsGridPointEnable(void);					// ��ȡɾ�����ĵ����ʾ����
	bool GDI_IsGridRoundEnable(void);					// ��ȡɾ������Ȧ����ʾ����
	bool GDI_SetGridLineNum(const int &nXNum, const int &nYNum);	// ���û�ͼ�������
	void GDI_GetGridLineNum(int &nXNum, int &nYNum);	// ��ȡ��ͼ�������
	void GDI_GetBorderGridPos(RECT &rect);				// �ĵ���ͼ�߿�Χ
	void GDI_SetBorderGridPos(const RECT &rect);		// ���û�ͼ�߿�Χ
	// ���û�ͼ�߿�Χ
	void GDI_SetBorderGridPos(const int &nLeft, const int &nTop, const int &nRight, const int &nBottom);
	// ���ñ������		GridColor -- �����ɫ, iGridBorderWidth -- �߿���,
	// iLineWidth -- ����߿�
	void GDI_SetGridStyle(const COLORREF &GridColor,
		const int &iGridBorderWidth, const int &iGridLineWidth, const BYTE &nGridType = DEV_GRID_CLASSICAL);
	void GDI_EnableGrid(const bool &bGrid);	// ���û���ɾ�񿪹���

	// Text ///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// ���ù���ͼ����˵������
	// bEnable -- ����˵�����أ�true����false��
	void GDI_EnableSpecgView(const bool &bEnable);
	// ��ȡ����ͼ����˵������
	// ����ֵ: true��, false��
	bool GDI_IsSpecgViewEnable(void);
	// ���ò�������˵��
	// nID -- ����ID
	// pczText -- ˵������
	// color -- ������ɫ
	// bShow -- �Ƿ���ʾ���֣�true��ʾ��false����
	// ����ֵ��true���óɹ���false����ʧ��
	bool GDI_SetMultiText(const int &nID, const TCHAR *pczText, const COLORREF &color, const bool &bShow);
	// ����ڶ���������ϵ
	// bEnable -- ����أ�true���false�ر�
	void GDI_Enable2ndY(const bool &bEnable);
	// �ڶ���������ϵ�Ƿ��Ѽ���
	// ����ֵ������أ�true���false�ر�
	bool GDI_Is2ndYEnable(void);
	// �����Զ�����������
	// nID -- �Զ������ֵ�λ��id
	// pczTitle -- �Զ������ֱ���ͷ
	// pczDetail -- �Զ�����������
	// pczSeperate -- �Զ������ֱ���ͷ���Զ�����������֮��ķָ���
	// bEnableView -- �Ƿ���ʾ��ǰ�Զ�������
	// ����ֵ -- true�ɹ���false -- ʧ��
	bool GDI_SetManualText(const int &nID, const TCHAR *pczTitle, const TCHAR *pczDetail, const TCHAR *pczSeperate, const bool &bEnableView = true,
		const UINT &nTextPos = DEVGDI_TEXT_LEFTTOP);
	bool GDI_SetManualTextNum(const int nManualTextNum);	// �����Զ���������ʾ����
	int GDI_GetManualTextNum(void);						// ����Զ���������ʾ����
	void GDI_EnableManualText(const bool &bEnable);		// ��ʾ�Զ���������Ϣ����
	bool GDI_IsManualTextEnable(void);					// ��ȡ�Զ���������Ϣ����
	void GDI_EnableManualXText(const bool &bEnable);	// �Զ���X����������
	bool GDI_IsManualXTextEnable(void);					// ��ȡ�Զ���X���������ݿ���
	void GDI_EnableManualYText(const bool &bEnable);	// �Զ���Y����������
	bool GDI_IsManualYTextEnable(void);					// ��ȡ�Զ���X���������ݿ���
	void GDI_SETViewPrecision(const int &nPrecision);	// ����������ʾ����(С��������λ >=0 <=99)
	void GDI_SetXTextYOffset(const int &nOffset = 0);	// ���ú��������ֵ�����ƫ����
	void GDI_SetYTextXOffset(const int &nOffset = 0);	// �������������ֵĺ���ƫ����
	void GDI_SetTextEnable(const bool &bXEnable, const bool &bYEnable);		// ����������ʾ����
	void GDI_SetTextColor(const COLORREF &TextColor);	// ����������ɫ
	// �������ɨ��Χ, iStart -- ��ʼֵ, iEnd -- ��ֵֹ
	void GDI_SetXFullSizeSpan(const double &dStart, const double &dEnd, const int &nDataLen = 0);
	// ��ȡ���ɨ��Χ, iStart -- ��ʼֵ, iEnd -- ��ֵֹ
	void GDI_GetXFullSizeSpan(double &dStart, double &dEnd);
	// ����ɨ��Χ, iStart -- ��ʼֵ, iEnd -- ��ֵֹ
	void GDI_SetSpan(const double &dStart, const double &dEnd, const int &nDataLen = 0);
	// ��ȡɨ��Χ, iStart -- ��ʼֵ, iEnd -- ��ֵֹ
	void GDI_GetSpan(double &dStart, double &dEnd);
	void GDI_SetXDepartment(const TCHAR* szDepart);		// ����X�����굥λ
	void GDI_GetXDepartment(TCHAR* szDepart);			// ��ȡX�����굥λ
	void GDI_SetYDepartment(const TCHAR* szDepart);		// ����Y�����굥λ
	void GDI_GetYDepartment(TCHAR* szDepart);			// ��ȡY�����굥λ
	void GDI_SetYDep2ndY(const TCHAR* szDepart);		// ����Y��ڶ����굥λ
	void GDI_GetYDep2ndY(TCHAR* szDepart);				// ��ȡY��ڶ����굥λ
	// ���ݲ��������id��ø�λ�õĺ�����(��λ)ֵ
	// nDataLen -- �������ݵ��ܳ���
	// nArrayID -- �������ݵ�id
	// ����ֵ����ǰ���ε�ĺ�����(��λ)ֵ
	double GDI_GetCurrentXValue(const int &nDataLen, const int &nArrayID);
	// ���ú�����ֵ ���ַ�����
	void GDI_SetXValue(const TCHAR *pszStart, const	TCHAR *pszCenter,
		const TCHAR *pszEnd);
	// �Զ�����������ʾֵ
	// pszVal -- ������ĳһ���ֵ
	// nLocation -- ���ڸ��λ�ã������ǰλ��
	// ����ֵ��true���óɹ���false����ʧ��
	bool GDI_SetYValue(const TCHAR *pszVal, const int &nLocation);
	// ����Y����ʼ����ֵֹ
	void GDI_SetSpanY(const double &dStart, const double &dEnd);
	// ��ȡY����ʼ����ֵֹ
	void GDI_GetSpanY(double &dStart, double &dEnd);
	// ����������2�����귶Χ
	// dStart -- ��������ʼֵ
	// dEnd -- ��������ֵֹ
	void GDI_SetSpanYSpecial(const double &dStart, const double &dEnd);
	// ��ȡ������2�����귶Χ
	// dStart -- ��������ʼֵ
	// dEnd -- ��������ֵֹ
	void GDI_GetSpanYSpecial(double &dStart, double &dEnd);
	void GDI_EnableCoor( const bool &bEnableCoor );		// �Ƿ���ʾ����8831������ wangzheng 2008-09-11
	bool GDI_SetCoorData( tagCoorText Data[], int nDataLen );	// wangzheng �������������
	// ����ʵʱ��ͼ���ֵ�����
	// pszFont -- ����
	// nFontSize -- �����С
	// ����ֵ��true���óɹ���false����ʧ��
	bool GDI_SetFont(TCHAR *pszFont, int &nFontSize);

	// MKR ////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// �ƶ�����ͼ���
	// ucDirection -- �ƶ��������MKR_MOVE����
	// nWaveLen -- ��������
	// nDataLen -- ����ͼ�У�ÿ�����ε����ݳ���
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_MoveSpectrogramMkr(const BYTE &ucDirection, const int &nWaveNum, const int &nDataLen);
	// ѡ��ʹ�ù���ͼ���α�
	// ucType -- ��ʹ�õ��α꣬���SPECTROGRAM_MKR����
	void GDI_UseSpectrogramMkr(const BYTE &ucType);
	// ��ù���ͼ�α��ʹ��״��
	// ����ֵ������ͼ�α��ʹ��״�������SPECTROGRAM_MKR����
	BYTE GDI_GetSpectrogramMkrUse(void);
	// ���ù���ͼMkrλ��
	// nXPos -- ������λ��
	// nYPos -- ������λ��
	// nWaveLen -- ��������
	// nDataLen -- ����ͼ�У�ÿ�����ε����ݳ���
	void GDI_SetSpectrogramMkrPos(const int &nXPos, const int &nYPos, const int &nWaveLen, const int &nDataLen);
	// ��ȡ����ͼMkrλ��
	// uType -- �����������ͣ����SPECTROGRAM_MKR����
	// nXPos -- ������λ��
	// nYPos -- ������λ��
	// dzOutWave -- ����Ƶ�׻�ͳ������
	// dzInputWave -- �������ͼ����
	// nWaveNum -- ����ͼ��������
	// nDataLen -- ÿ�첨�ε����ݳ���
	void GDI_GetSpectrogramMkrPos(const BYTE &uType, int &nXID, int &nYID, double *dzOutWave, const double *dzInputWave, const int &nWaveNum, const int &nDataLen);
	// ���ù���ͼmkr��ɫ
	// color -- mkr��ɫ
	void GDI_SetSpectrogramMkrColor(const COLORREF &color);
	// ��ȡ����ͼmkr��ɫ
	// ����ֵ��mkr��ɫ
	COLORREF GDI_GetSpectrogramMkrColor(void);
	// ���ù���ͼMkr����״̬
	// bXEnable -- ����mkr����
	// bYEnable -- ����Mkr����
	void GDI_EnableSpectrogramMkr(const bool &bXEnable, const bool &bYEnable);
	// ��ȡ����ͼMkr����״̬
	// bXEnable -- ����mkr����
	// bYEnable -- ����Mkr����
	void GDI_IsSpectrogramMkrEnable(bool &bXEnable, bool &bYEnable);
	// �����α��ߵ���ɫ
	// color -- �α��ߵ���ɫ
	void GDI_SetMkrLineColor(const COLORREF &color);
	// ��ȡ�α��ߵ���ɫ
	// ����ֵ���α��ߵ���ɫ
	COLORREF GDI_GetMkrLineColor(void);
	// Ƶ���������ٱ��ֿ���
	// bEnable -- ���ٺ����꿪�أ�true������ֵ��false������λ��
	void GDI_EnableMkrKeepX(const bool &bEnable);
	inline bool GDI_IsMkrKeepX(void);		// ���Ƶ����ٺ����꿪��
	COLORREF GDI_GetActiveMkrColor(void);	// ��õ�ǰ�Ƶ�����ɫ
	void GDI_SetActiveMkrColor(const COLORREF &ActiveMkrColor);	// ���õ�ǰ�Ƶ�����ɫ
	// ����mkr�����ڲ����ϵĺ���λ��λ�ã���Ϊ���;�������״̬
	// nType -- mkr�ĺ���λ�����������ö��DEV_MKR_STYLE
	bool GDI_SetMkrXKeep(const int &nType);	
	bool GDI_SetMkrUnit(const int &nID, const TCHAR *pszUnit);	// ����Ƶ��ĵ�λ
	bool GDI_SetMkrXPos(const int &nID, const int &nArrayID);	// ����ָ��Ƶ�����ڲ��������е�λ��
	int GDI_GetMkrXPos(const int &nID);	// ���ָ��Ƶ�����ڲ��������е�λ�ã�����ֵ������id
	bool GDI_SetMkrVal(const double &dValY, const int &nID);	// ����ָ��mkr������ֵ
	bool GDI_SetMkrVal(const TCHAR* pszValY, const int &nID);	// ����ָ��mkr������ֵ
	void GDI_ManualMkrVal(const BYTE &ucManual);	// �ֶ�����mkr��ֵ,�����DEV_MKR_VALUE��˵��
	void GDI_SetXMrkEnable( const bool &bEnable );		// �����Ƿ���ʾ���Ͻǵĺ�����Ƶ��	wangzheng 2008-08-04
	void GDI_SetYMkrEnable(const bool &bEnable);	// ����Ƶ�����������ֿ���
	// ��õ�ǰƵ���ֵ
	// dYValue -- Ƶ��ĺ�����ֵ
	// dXValue -- Ƶ���������ֵ
	// nMkrID -- ��õ�ǰƵ���id
	// pdWaveData -- ��������
	// nWaveLen -- �������ݳ���
	// return value: -1��ȡʧ�ܣ�����ֵΪƵ�����ڲ������ݵ�λ��
	int GDI_GetMkrValue(double &dYValue, double &dXValue, const int &nMkrID, const double *pdWaveData,
		const int &nWaveLen);
	// ����Ƶ��״̬��֧�ֲ�������
	bool GDI_SetMkrKeepWave(const int &nMkrID, const int &nWaveID, const bool &bKeep);
	// ��ȡƵ��״̬��֧�ֲ�������
	bool GDI_GetMkrKeepWave(const int &nMkrID, const int &nWaveID);
	bool GDI_IsMkrLineEnable();		// �ж�Ƶ�����Ƿ���ʾ
	// ������ʾ, ����Ƶ����
	// bMkr -- Ƶ������ʾ����
	// bXLine -- ����Ƶ���߶�����ʾ����
	// bYLine -- ����Ƶ���߶�����ʾ����
	void GDI_EnableMkrLine(const bool &bMkr, const bool &bXLine = true, const bool &bYLine = true);
	bool GDI_IsMkrEnable(const int &iMkrID);	// �жϵ�ǰƵ���Ƿ�
	int GDI_GetActiveMkr(void);		//��õ�ǰ���Ƶ��
	// ʹ�����������ûƵ��
	bool GDI_SetActiveMkrByMouse(const int &nXPos, const int &nYPos, const double *pdData, const int &nDataLen, const double *pdData2 = NULL,
		const int &nDataLen2 = 0, const double *pdData3 = NULL, const int &nDataLen3 = 0, const double *pdData4 = NULL, const int &nDataLen4 = 0,
		const double *pdData5 = NULL, const int &nDataLen5 = 0, const double *pdData6 = NULL, const int &nDataLen6 = 0, const double *pdData7 = NULL,
		const int &nDataLen7 = 0, const double *pdData8 = NULL, const int &nDataLen8 = 0, const double *pdData9 = NULL, const int &nDataLen9 = 0,
		const double *pdData10 = NULL, const int &nDataLen10 = 0);
	void GDI_SetActiveMkr(const int &iMkrID);	//���õ�ǰ���Ƶ��
	// ����Ƶ��Ŀ������ԣ�iid--Ƶ��id, bEnable-- true���ӣ�false������
	void GDI_EnableMkr(const int &iID, const bool &bEnable);
	// ������ʾƵ��������, true��ʾ false����ʾ
	void GDI_EnableMkrYDepartment(const bool &bDepartment);
	void GDI_SetActiveXMkrVal(const CString &szMkrXValue);	// ���ù�굱ǰ��ʾ�ĺ�����ֵ
	void GDI_SetXMkrValue(const CString *pszMkrXValue);	// ���ù�굱ǰ������ֵ
	//����mkr���ض�Xֵ
	bool GDI_SetMkrX(const int &iLocation, const int &nYPos, const double *pdData, const int &iDataLen);
	// ����Mkr��ֵ���ӻ��
	void GDI_SetMkrX(const bool &AddOrAbate, const int &iDataLen);
	// ���������ʵ��ֵ����Mkr�ĺ�����λ��
	// nID -- Mkr�����
	// dXVal -- ���ú������ֵ
	// nDataLen -- ��ǰ���ε����ݳ���
	// ����ֵ��true�ɹ���falseʧ�ܣ���������ֵ�����˵�ǰ���귶Χ����
	bool GDI_SetMkrX(const int &nID, const double &dXVal, const int &nDataLen);
	void GDI_ResetMkr();	// ��mkrֵ��Ϊ0
	// ����Ƶ������
	// mkrColor -- Ƶ����ɫ, imkrType -- Ƶ������
	bool GDI_SetMkrStyle(const COLORREF &mkrColor, const int &imkrType, const int &nMkrID = 0);
	// ���Ƶ������
	// mkrColor -- Ƶ����ɫ, imkrType -- Ƶ������
	bool GDI_GetMkrStyle(COLORREF &mkrColor, int &nMkrType, const int &nMkrID);
	// ����Ƶ�����ԣ���չ����
	// mkrColor -- Ƶ����ɫ
	// imkrType -- Ƶ������
	// nMkrID -- Ƶ��ID
	// nWaveID -- Ƶ����ٲ��ε�ID
	// ����ֵ��true���óɹ���false����ʧ��
	bool GDI_SetMkrStyleEx(const COLORREF &mkrColor, const int &nMkrType, const int &nMkrID, const int &nWaveID);
	// ���Ƶ�����ԣ���չ����
	// mkrColor -- Ƶ����ɫ
	// imkrType -- Ƶ������
	// nMkrID -- Ƶ��ID
	// nWaveID -- Ƶ����ٲ��ε�ID
	// ����ֵ��true��ȡ�ɹ���false��ȡʧ��
	bool GDI_GetMkrStyleEx(COLORREF &mkrColor, int &nMkrType, const int &nMkrID, const int &nWaveID);
	// ����Ƶ�����ֵ���ɫ
	// TextColor -- Ƶ���������ɫ
	// nMkrID -- Ƶ��ID
	// nWaveID -- Ƶ����ٲ��ε�ID
	// ����ֵ��true���óɹ���false����ʧ��
	bool GDI_SetMkrTextColor(const COLORREF &TextColor, const int &nMkrID, const int &nWaveID);
	// ���Ƶ�����ֵ���ɫ
	// TextColor -- Ƶ���������ɫ
	// nMkrID -- Ƶ��ID
	// nWaveID -- Ƶ����ٲ��ε�ID
	// ����ֵ��true��ȡ�ɹ���false��ȡʧ��
	bool GDI_GetMkrTextColor(COLORREF &TextColor, const int &nMkrID, const int &nWaveID);

	// Zoom in/out ///////////////////////////////////////////////////////////////////////////////////////////////
	//
	int GDI_GetMouseLineStatus(void);					// �õ������״̬
	void GDI_SetMouseLineStatus(const int &nStatus);	// ���������״̬
	void GDI_SetMouseLineLButtonDown(const int &nXPos, const int &nYPos);	// ��껭��������������
	void GDI_SetMouseLineMove(const int &nXPos, const int &nYPos);			// ��껭��������ƶ�
	bool GDI_SetMouseLineLButtonUp(const int &nXPos, const int &nYPos, const int &nDataLen);// ��껭�����������ſ�
	// ����������¼�������pageup��pagedown�¼�
	bool GDI_MouseUpPageUp_Down(const int &nXPos, const int &nYPos, const int &nDataLen);
	void GDI_SetMouseStartX(const int& nXPos);	// ����������ʱ���������ĳ�ʼֵ�����ڹ�����
	// ʹ��������ò��ε�ǰλ�ú͹�����λ��
	bool GDI_ScrollWaveByMouse(const int &nXPos, const int &nYPos, const double* pdData, const int &nDataLen);
	void GDI_MoveWave(const int &nScrollType, const int &nDataLen);	// �ƶ�����
	int GDI_GetWaveRate(void);		// ��ò�����ʾ����
	int GDI_GetWaveAdjustRate(const int &nDataLen);	// ��ò����Զ��������
	// ���ò�����ʾ����
	void GDI_SetWaveRate(const int &iRatePercent, const int &nDataLen);
	// �ж�����λ�ã�������scrollbar�ĸ���״̬
	// return value: true -- ��button�ϣ� false -- ����button��
	int GDI_CheckMouseXY(const int &nXPos, const int &nYPos,
		const double* pdData, const int &iDataLen);
	bool GDI_IsScrollBarEnable();	// ���ScrollBar����ʾ��������
	void GDI_EnableScrollBar(const bool &bScrollBar);	// �Ƿ���ʾScrollBar
	

	// Limit line /////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// ����Limit line ����ʾ����
	// bLimitLine -- ��ʾ���ԣ�true��ʾ, false����
	// nID -- Limit Line �� ID
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_EnableLimitLine(const bool &bLimitLine, const int &nID);
	// ��ȡLimit line ����ʾ����
	// nID -- Limit Line �� ID
	// ����ֵ����ʾ���ԣ�true��ʾ, false���ػ��ȡʧ��
	bool GDI_IsLimitLineEnable(const int &nID);
	// ����Limit Line��ֵ
	// dStartX -- ��������ʼֵ
	// dEndX -- ��������ֵֹ
	// dMinY -- ��������Сֵ
	// dMaxY -- ���������ֵ
	// nID -- Limit Line �� ID
	// bProtect -- ������ֵ���б�����true������false������
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_SetLimitLineVal(double &dStartX, double &dEndX, double &dMinY, double &dMaxY,
		const int &nID, const bool &bProtect = true);
	// ��ȡLimit Line��ֵ
	// dStartX -- ��������ʼֵ
	// dEndX -- ��������ֵֹ
	// dMinY -- ��������Сֵ
	// dMaxY -- ���������ֵ
	// nID -- Limit Line �� ID
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_GetLimitLineVal(double &dStartX, double &dEndX, double &dMinY, double &dMaxY,
		const int &nID);
	// ����Limit Line������
	// LimitLineColor -- ��ǰLimit Line����ɫ
	// nLineWidth -- ��ǰLImit Line���߿�
	// nID -- Limit Line �� ID
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_SetLimitLineStyle(const COLORREF &LimitLineColor, const int &nLineWidth, const int &nID);
	// ��ȡLimit Line������
	// LimitLineColor -- ��ǰLimit Line����ɫ
	// nLineWidth -- ��ǰLImit Line���߿�
	// nID -- Limit Line �� ID
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_GetLimitLineStyle(COLORREF &LimitLineColor, int &nLineWidth, const int &nID);
	// ����Limit Line����ɫ
	// LimitLineColor -- ��ǰLimit Line����ɫ
	// nID -- Limit Line �� ID
	// nLineWidth -- ����LImit Line���߿�
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_SetLimitLineColor(const COLORREF &LimitLineColor, const int &nID, const int &nLineWidth = 1);
	// ��ȡLimit Line����ɫ
	// LimitLineColor -- ��ǰLimit Line����ɫ
	// nID -- Limit Line �� ID
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_GetLimitLineColor(COLORREF &LimitLineColor, const int &nID);
	// ����Limit Lineȫ��Ļ��ʾ
	// bFullScreen -- �Ƿ�ȫ����ʾ��true�ǣ�false��
	// nID -- Limit Line �� ID
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_SetLimitLineFullScreen(const bool &bFullScreen, const int &nID);
	// ����Limit Lineȫ��Ļ��ʾ
	// bFullScreen -- �Ƿ�ȫ����ʾ��true�ǣ�false��
	// nID -- Limit Line �� ID
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_GetLimitLineFullScreen(bool &bFullScreen, const int &nID);
	// ���³���Ϊ����DS7618���򣬺���ȫ��Ļlimit line ////////////////
	// ��ȡLimit Line��ֵ, ����ֵΪlimit line������
	int GDI_GetLimitLineVal(int* pnLimitLineVal, bool* pbEnable);
	// ����Limit Line��ֵ
	void GDI_SetLimitLineVal(const int* pnLimitLineVal, const bool* pbEnable, const int &nLimitLineNumber);
	// ����Limit Line��ֵ
	void GDI_SetLimitLineVal(const double* pnLimitLineVal, const bool* pbEnable, const int &nLimitLineNumber);
	// ����Limit Line����ɫ
	void GDI_SetLimitLineColor(const COLORREF &LimitLineColor);
	// ����Limit Line Text�Ŀ���
	// bEnable -- ��ʾ����
	// nID -- limit�ߵ�ID
	// ����ֵ���ɹ�true��ʧ��false
	bool GDI_EnableLimitLineText(const bool &bEnable, const int &nID);
	// ��ȡLimit Line Text�Ŀ���
	// bEnable -- ��ʾ����
	// nID -- limit�ߵ�ID
	// ����ֵ���ɹ�true��ʧ��false
	bool GDI_IsLimitLineTextEnable(bool &bEnable, const int &nID);
	// ����Limit�ߵ��Զ�������
	// pszStr -- �Զ�����������
	// nID -- Limit�ߵ�ID
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_SetManualLimitText(const TCHAR *pszStr, const int &nID);
	// ��ȡLimit�ߵ��Զ�������
	// pszStr -- �Զ�����������
	// nID -- Limit�ߵ�ID
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_GetManualLimitText(TCHAR *pszStr, const int &nID);
	// ����Limit�ߵ��Զ������ֿ���
	// bEnable -- �Զ������ֵĿ��أ�true����false��
	// nID -- Limit�ߵ�ID
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_EnableLimitManualText(const bool &bEnable, const int &nID);
	// ��ȡLimit�ߵ��Զ������ֿ���
	// bEnable -- �Զ������ֵĿ��أ�true����false��
	// nID -- Limit�ߵ�ID
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_IsLimitManualTextEnable(bool &bEnable, const int &nID);
	// ����Limit�ߵĲ���ֵ
	// dStep -- ����ֵ
	void GDI_SetLimitStep(const double &dStep);
	// ���Limit�ߵĲ���ֵ
	// ����ֵ������ֵ
	double GDI_GetLimitStep(void);
	// �ƶ��ο���,����ο�DEV_MOVE�Ķ���
	// nDirection -- �ο����ƶ�����
	void GDI_MoveLimitLine(const int &nDirection);
	// ������ƶ��ο��ߣ��ο��߸������λ���ƶ�
	// nXPos -- ���������
	// nYPos -- ����������
	void GDI_MoveLimitLine(const int &nXPos, const int &nYPos, const int &nType);
	// ���õ�ǰ���Limit��
	// nID -- Limit�ߵ�ID
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_SetActiveLimitLine(const int &nID);
	// ��õ�ǰ���Limit��
	// ����ֵ����ǰ�Limit�ߵ�ID
	int GDI_GetActiveLimitLine(void);
	// ����Limit Line���ֵ�λ��
	// nLocation -- ���ֵ�λ�ã��ο�DEV_KEEP�Ķ���
	// ����ֵ��true���óɹ���false����ʧ��
	bool GDI_SetLimitTextDock(const int &nLocation, const int &nID =0);

	// Wave ////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// ���ƹ���ͼ��������
	// pdData -- ��������
	// nWaveNum -- �����ܹ��ж�����
	// nDataLen -- ÿ���������ݳ���
	// pColor -- ����ͼ��ɫ��
	// pdLevel -- ����ͼ��������ֵ, ���е�0��ֵ�����ֵ���˺���ʾ���β���ֵ��������ֵ������������ɫ
	// nColorNum -- ����ͼ��ɫֵ
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_DrawSpectrogram(const double *pdData, const int &nWaveNum, const int &nDataLen, const COLORREF *pColor, const double *pdLevel, const int &nColorNum);
	// ���ò���ʹ������ϵ
	// nWaveID -- ����ID
	// ucDock -- ʹ������ϵ�����Y_COORDINATE_DEF�Ķ���
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_SetWaveDock(const int &nWaveID, const BYTE &ucDock);
	// ��ȡ����ʹ������ϵ
	// nWaveID -- ����ID
	// ucDock -- ����ʹ������ϵ�����Y_COORDINATE_DEF�Ķ���
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_GetWaveDock(const int &nWaveID, BYTE &ucDock);
	//���ò�����ʼλ�õĵ��� ���鴺/9/9
	void GDI_SetWaveStartPos(const int &iWaveStartPos);
	// ���Ʋ��Σ���ɫ���պϸ������������֣����ȸ���UpLimit�ģ�����UpLimit����ɫ��ʾ���������������ִ����ʾ���ȼ�
	// ����С�ģ�UpLimit����ʾ���ȼ�����DownLimit�����ȼ�
	// pdCurrent -- ������������
	// nCurrent --�����������ݳ���
	// pdMax -- ��󱣳ֲ�������
	// nMax -- ��󱣳ֲ������ݳ���
	// pdMin -- ��С���ֲ�������
	// nMin -- ��С���ֲ������ݳ���
	// pdAverage -- ƽ��ֵ��������
	// nAverage -- ƽ��ֵ�������ݳ���
	// pdUpLimit1 -- �Ϻϸ���1����
	// nUpLimit1 -- �Ϻϸ���1���ݳ���
	// pdDownLimit1 -- �ºϸ���1����
	// nDownLimit1 -- �ºϸ���1���ݳ���
	// pdUpLimit2 -- �Ϻϸ���2����
	// nUpLimit2 -- �Ϻϸ���2���ݳ���
	// pdDownLimit2 -- �ºϸ���2����
	// nDownLimit2 -- �ºϸ���2���ݳ���
	// pdUpLimit3 -- �Ϻϸ���3����
	// nUpLimit3 -- �Ϻϸ���3���ݳ���
	// pdDownLimit3 -- �ºϸ���3����
	// nDownLimit3 -- �ºϸ���3���ݳ���
	// pdUpLimit4 -- �Ϻϸ���4����
	// nUpLimit4 -- �Ϻϸ���4���ݳ���
	// pdDownLimit4 -- �ºϸ���4����
	// nDownLimit4 -- �ºϸ���4���ݳ���
	// pdUpLimit5 -- �Ϻϸ���5����
	// nUpLimit5 -- �Ϻϸ���5���ݳ���
	// pdDownLimit5 -- �ºϸ���5����
	// nDownLimit5 -- �ºϸ���5���ݳ���
	// bzEnable -- �ϸ���ʹ�ܣ�false��ʾ��Ч��true��ʾ��Ч
	// ����ֵ��trueִ�гɹ���falseִ��ʧ��
	bool GDI_DrawByLimit(const double *pdCurrent, const int &nCurrent, const double *pdMax, const int &nMax,
		const double *pdMin, const int &nMin, const double *pdAverage, const int &nAverage,
		const double *pdUpLimit1, const int &nUpLimit1, const double *pdDownLimit1, const int &nDownLimit1,
		const double *pdUpLimit2, const int &nUpLimit2, const double *pdDownLimit2, const int &nDownLimit2,
		const double *pdUpLimit3, const int &nUpLimit3, const double *pdDownLimit3, const int &nDownLimit3,
		const double *pdUpLimit4, const int &nUpLimit4, const double *pdDownLimit4, const int &nDownLimit4,
		const double *pdUpLimit5, const int &nUpLimit5, const double *pdDownLimit5, const int &nDownLimit5, bool *bzEnable);
	// ���������Ʋ��ε���ʼ�㣬��LButtonDown�¼��������
	// nXStartPos -- ��������λ��
	// nYStartPos -- ���������λ��
	// pdData -- ��������
	// nDataLen --��ǰ���ε����ݳ���
	// nWaveID -- ��������ID
	// ����ֵ��true���óɹ���false����ʧ��
	bool GDI_SetMouseWaveLineStart(const int &nXStartPos, const int &nYStartPos, double *pdData, const int &nDataLen, const int &nWaveID);
	// �����Ʋ��ε�Ϳѻ���������ƵĲ�����������껬���Ĺ켣������
	// nXEndPos -- ��������λ��
	// nYEndPos -- ���������λ��
	// pdData -- ��������
	// nDataLen -- �������ݳ���
	// nWaveID -- ���ε�ID
	// ����ֵ��true���óɹ���false����ʧ��
	bool GDI_SetMouseWavePixel(const int &nXEndPos, const int &nYEndPos, double *pdData, const int &nDataLen, const int &nWaveID);
	int GDI_GetWavePixNum(void);	// ��ò��ο�ȣ�������
	int GDI_GetXPixelNumber();//���������X��������
	// ����������������
	// LineColor -- ���ߵ���ɫ, iLineWidth -- �ߵĿ��
	// LineColor2 -- �ڶ������ߵ���ɫ, iLineWidth2 -- �ڶ������ߵĿ��
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
	// ��ȡ������������
	// LineColor -- ������ɫ
	// iLineWidth -- ���߿��
	void GDI_GetLine(COLORREF &LineColor, int &iLineWidth, COLORREF &LineColor2, int &iLineWidth2, COLORREF &LineColor3, int &nLineWidth3, COLORREF &LineColor4,
		int &nLineWidth4, COLORREF &LineColor5, int &nLineWidth5, COLORREF &LineColor6, int &nLineWidth6, COLORREF &LineColor7, int &nLineWidth7, COLORREF &LineColor8,
		int &nLineWidth8, COLORREF &LineColor9, int &nLineWidth9, COLORREF &LineColor10, int &nLineWidth10, COLORREF &LineColor11, int &nLineWidth11,
		COLORREF &LineColor12, int &nLineWidth12, COLORREF &LineColor13, int &nLineWidth13, COLORREF &LineColor14, int &nLineWidth14, COLORREF &LineColor15,
		int &nLineWidth15, COLORREF &LineColor16, int &nLineWidth16, COLORREF &LineColor17, int &nLineWidth17, COLORREF &LineColor18, int &nLineWidth18,
		COLORREF &LineColor19, int &nLineWidth19, COLORREF &LineColor20, int &nLineWidth20);
	// ��ʾQAM����
	// pnData -- ��������
	// nDataLen -- �������ݳ���
	// bManualColor -- �Զ��岨����ɫ���أ�falseʹ�����ڲ��Ĳ�����ɫ���ԣ�trueʹ���Զ�����ɫ��ÿ�������ɫ���Բ�ͬ
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_DrawQAM(const struct tagCoordinate *pnData, const int &nDataLen, const bool &bManualColor = false);
	// ��ʾQAM����
	bool GDI_DrawQAM(deque<int> &nstQamData);
	// ��ʾQAM���ݣ����ģʽ
	// pnData -- ����ͼ����
	// nDataLen --���������ͼ���ݳ���
	// bManualColor -- �������Զ�����ɫ����
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_DrawQamFill(const struct tagCoordinate *pnData, const int &nDataLen,
		const bool &bManualColor = false);
	// ��ʾQAM���ݣ����ģʽ
	bool GDI_DrawQamFill(deque<int> &nstQamData);
	void GDI_DrawQamClean(void);	// ���Qam���ݣ��������ģʽ
	// ��ʾһ֡����, iData -- ��������, iDataLen -- ɨ�����
	bool GDI_Draw(const double *pdData, const int &iDataLen, const double *pdData2 = NULL, const int nDataLen2 = 0, const double *pdData3 = NULL,
		const int &nDataLen3 = 0, const double *pdData4 = NULL, const int &nDataLen4 = 0, const double *pdData5 = NULL, const int &nDataLen5 = 0,
		const double *pdData6 = NULL, const int &nDataLen6 = 0, const double *pdData7 = NULL, const int &nDataLen7 = 0, const double *pdData8 = NULL,
		const int &nDataLen8 = 0, const double *pdData9 = NULL, const int &nDataLen9 = 0, const double *pdData10 = NULL, const int &nDataLen10 = 0,
		const double *pdData11 = NULL, const int &nDataLen11 = 0, const double *pdData12 = NULL, const int &nDataLen12 = 0, const double *pdData13 = NULL,
		const int &nDataLen13 = 0, const double *pdData14 = NULL, const int &nDataLen14 = 0, const double *pdData15 = NULL, const int &nDataLen15 = 0,
		const double *pdData16 = NULL, const int &nDataLen16 = 0, const double *pdData17 = NULL, const int &nDataLen17 = 0, const double *pdData18 = NULL,
		const int &nDataLen18 = 0, const double *pdData19 = NULL, const int &nDataLen19 = 0, const double *pdData20 = NULL, const int &nDataLen20 = 0);
	// ��ʾһ�����λ���
	// ppdData -- �������ݶ�άָ������
	// pnDataLen -- �������ݳ���һάָ������
	// nWaveNum -- ������������
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_DrawD(double **ppdData, const int *pnDataLen, const int &nWaveNum);
	// �����������ͼ, public
	bool GDI_DrawLgX(const double *pdData, const int &nDataLen, const double *pdData2 = NULL,
		const int nDataLen2 = 0);
	// ��ʾ�������δ���
	bool GDI_DrawDoubleRect(const double *pdData1, const int &nDataLen1, const double *pdData2, const int &nDataLen2);
	// ��ʾ�������δ���
	bool GDI_Draw3Horizontal(const double *pdData1, const int &nDataLen1, const double *pdData2 = NULL,
		const int &nDataLen2 = 0, const double *pdData3 = NULL, const int &nDataLen3 = 0);
	// ����������
	bool GDI_DrawLineOnly(const double *pdData, const int &nDataLen, const double *pdData2 = NULL,
		const int &nDataLen2 = 0);
	// ���Ʋ������ݣ�֧�ֲ�������������
	// pdData -- ��������
	// nDataLen -- ��ǰ�������ݵĳ���
	// nMaxPointNum -- ��ͼ֧�ֵĲ������ݵ���󳤶�
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_DrawLineEnableMaxPointNum(const double *pdData, const int &nDataLen, const int &nMaxPointNum);

	// Picture //////////////////////////////////////////////////////////////////////////////
	//
	// �������ͼͼƬ
	// pszFileName -- ��������ļ�·��
	// pdData -- ��������
	// nWaveNum -- �����ܹ��ж�����
	// nDataLen -- ÿ���������ݳ���
	// pColor -- ����ͼ��ɫ��
	// pdLevel -- ����ͼ��������ֵ, ���е�0��ֵ�����ֵ���˺���ʾ���β���ֵ��������ֵ������������ɫ
	// nColorNum -- ����ͼ��ɫֵ
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_SaveSpectrogramPic(const TCHAR *pszFileName, const double *pdData, const int &nWaveNum, const int &nDataLen, const COLORREF *pColor,
		const double *pdLevel, const int &nColorNum);
	// ����ǰ����ͼ�񱣴��ΪͼƬ, ͼ���ļ�����bmp,jpg�ȸ�ʽ����
	// pszFileName -- ��������ļ�·��
	// pdData-pdData10 -- ��������
	// iDataLen-nDataLen10 -- �������ݳ���
	// ����ֵ��true����ɹ���false����ʧ��
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
	// ��ʾһ֡�������ڱ���, ������ֵ, iData -- ��������, iDataLen -- ɨ�����
	bool GDI_DrawReport(CDC *pDC, CPrintInfo* pInfo, const double *pdData, const int &nDataLen, const double *pdData2 = NULL, const int &nDataLen2 = 0,
		const double *pdData3 = NULL, const int &nDataLen3 = 0, const double *pdData4 = NULL, const int &nDataLen4 = 0, const double *pdData5 = NULL,
		const int &nDataLen5 = 0, const double *pdData6 = NULL, const int &nDataLen6 = 0, const double *pdData7 = NULL, const int &nDataLen7 = 0,
		const double *pdData8 = NULL, const int &nDataLen8 = 0, const double *pdData9 = NULL, const int &nDataLen9 = 0, const double *pdData10 = NULL,
		const int &nDataLen10 = 0, const double *pdData11 = NULL, const int &nDataLen11 = 0, const double *pdData12 = NULL, const int &nDataLen12 = 0,
		const double *pdData13 = NULL, const int &nDataLen13 = 0, const double *pdData14 = NULL, const int &nDataLen14 = 0, const double *pdData15 = NULL,
		const int &nDataLen15 = 0, const double *pdData16 = NULL, const int &nDataLen16 = 0, const double *pdData17 = NULL, const int &nDataLen17 = 0,
		const double *pdData18 = NULL, const int &nDataLen18 = 0, const double *pdData19 = NULL, const int &nDataLen19 = 0, const double *pdData20 = NULL,
		const int &nDataLen20 = 0);
	// ���ñ������ִ�С������
	// pszFont -- ��������
	// nFontSize -- ���ִ�С
	void GDI_SetReportFont(const TCHAR *pszFont, const int &nFontSize);
	// ��ʼ������
	// ReportData -- ��������ݽṹ
	// bDefault -- �Ƿ�����Ϊȱʡ���ã�true����λȱʡ���ã���ReportData��������Ч�����ĸ���������ϵͳ����ȱʡ���á�false�Զ������ã�ReportData��������Ч
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_InitReport(const tagREPORT &ReportData, const bool &bDefault = true);
	void GDI_ExitReport(void);	// �˳���ӡ����
	// ���ñ������ͷ����
	// pszFont -- ����
	// nFontSize -- �ִ�С
	// nFontWeight -- �����ϸ�̶ȣ�FW_NORMAL��ͨ��FW_BLACK���ּӴ�
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_SetReportTitleFont(const TCHAR *pszFont, const int &nFontSize, const int &nFontWeight);
	// ���ò����Ϸ���������
	// pszFont -- ����
	// nFontSize -- �ִ�С
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_SetReportHeaderFont(const TCHAR *pszFont, const int &nFontSize);
	// ���ò����·���������
	// pszFont -- ����
	// nFontSize -- �ִ�С
	// ����ֵ��true�ɹ���falseʧ��
	bool GDI_SetReportEndFont(const TCHAR *pszFont, const int &nFontSize);
	// ���ñ������ͷ����
	void GDI_SetReportTitleText(const TCHAR *pszText);
	// ���ò���ǰ����
	void GDI_SetReportHeaderText(const TCHAR *pszText);
	// ���ò��κ�����
	void GDI_SetReportEndText(const TCHAR *pszText);
	// ���ñ������ͷλ��
	void GDI_SetReportTitlePos(const double &dXPos, const double &dYPos);
	// ���ò���ǰ����λ��
	void GDI_SetReportHeaderPos(const double &dXPos, const double &dYPos);
	// ���ò��κ�����λ��
	void GDI_SetReportEndPos(const double &dXPos, const double &dYPos);
	// ���ò���λ��
	// dXStartPos -- ��ʼ������λ��
	// dYStartPos -- ��ʼ������λ��
	// dXEndPos -- ��ֹ������λ��
	// dYEndPos -- ��ֹ������λ��
	void GDI_SetReportWavePos(CDC *pDC, CPrintInfo* pInfo, const double &dXStartPos, const double &dYStartPos, const double &dXEndPos,
		const double &dYEndPos);
	//���ñ����ͼ����
	// ��ʾһ֡�������ڱ��������ֵ, iData -- ��������, iDataLen -- ɨ�����
	bool GDI_SetRectReport(const RECT &ReportRect, const POINT &StartPoint);

	// Init ///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// ��ʼ����ͼ��
	// Rect -- ����λ��, hWnd -- ������, bkColor -- ��ͼ����ɫ, 
	// GridColor -- ��ͼ���ɫ, iGridBorderWidth -- ���߿���,
	// iGridLineWidth -- ����߿��, LineColor -- ����������ɫ,
	// iLineWidth -- �������߿��, TextColor -- ������ɫ, mkrColor -- Ƶ��ɫ
	// imkrType -- Ƶ������
	bool GDI_Init(const RECT &rect, const HWND &hWnd = NULL, const COLORREF &bkColor = RGB(50, 50, 50),
		const COLORREF &GridColor = RGB(0, 255, 0), const int &iGridBorderWidth = 2, const int &iGridLineWidth = 1,
		const COLORREF &LineColor = RGB(255, 255, 0), const int &iLineWidth = 1,
		const COLORREF &TextColor = RGB(255, 255, 0), const COLORREF &mkrColor = RGB(0, 255, 0),
		const int &imkrType = 0);
	void GDI_Exit();	// �˳�GDI��ͼϵͳ
	bool GDI_SetBKColor(const COLORREF &bkColor);	//���û�ͼ����ɫ
	bool GDI_SetRect(const RECT &rect);	// ���û�ͼ����
	void GDI_GetRect(RECT &rect);		// ��û�ͼ����

	CDevGDI(void);
	virtual ~CDevGDI(void);

	// Variables /////////////////////////////////////////////////////////////////////////////////////////////////
	//
	HWND m_hwnd;			// ��ͼ������
	HDC m_hdc;				// ��ǰ��ͼ�豸DC

protected:
	// MKR ///////////////////////////////////////////////////////////////////////////
	//
	// ��ʾȫ��Mkr�ĺ���
	void MkrFunc(const HDC &memDC, const double *pdData, const int &iDataLen, const double *pdData2, const int &nDataLen2, const double *pdData3,
		const int &nDataLen3, const double *pdData4, const int &nDataLen4, const double *pdData5, const int &nDataLen5, const double *pdData6,
		const int &nDataLen6, const double *pdData7, const int &nDataLen7, const double *pdData8, const int &nDataLen8, const double *pdData9,
		const int &nDataLen9, const double *pdData10, const int &nDataLen10, const double *pdData11, const int &nDataLen11, const double *pdData12,
		const int &nDataLen12, const double *pdData13, const int &nDataLen13, const double *pdData14, const int &nDataLen14, const double *pdData15,
		const int &nDataLen15, const double *pdData16, const int &nDataLen16, const double *pdData17, const int &nDataLen17, const double *pdData18,
		const int &nDataLen18, const double *pdData19, const int &nDataLen19, const double *pdData20, const int &nDataLen20);
	// ����Mkr
	void DrawMkr(const HDC &memDC, const double *pdData, const int &iDataLen, const int &iMkrID, const int &nWaveID);

	// Grid //////////////////////////////////////////////////////////////////////////
	//
	void DrawQamZoom(const HDC &memDC);	// ��������ͼ�����޿�
	void DrawHorizontal3Grid(const HDC &memDC);	//���ƺ���3�����α��
	void DrawLgGrid(const HDC &memDC);		// ���Ƶ���������������
	void DrawDoubleGrid(const HDC &memDC);	// �����������������
	bool DrawGrid(const HDC &memDC);	// ���Ʊ����
	bool DrawGridSpectrum(const HDC &memDC);	// ����Ƶ���ǵı��������DS8821
	bool DrawGridCenterRound(const HDC &memDC);	// ���Ʊ�����ĵ�ԲȦ
	bool DrawGridCenterPoint(const HDC &memDC);	// ���Ʊ�����ĵ�

	// Text //////////////////////////////////////////////////////////////////////////
	//
	void DrawMultiText(const HDC &memDC);	// �����Զ����������
	void DrawYDoubleText(const HDC &memDC);	// ����˫���δ���Yֵ
	void DrawCoor( const HDC &memDC );			// ���������8831 wangzheng 2008-09-11
	// ��ֵ��ʾ
	// memDC -- �ڴ��豸DC
	// iVal -- ����ʾ����ֵ
	// szDepartment -- ��ʾ��λ�ַ���
	// iXLocation -- ��ʾλ�ú�����
	// iYLocation -- ��ʾλ��������
	// iDir -- ��ʾ����λ, 0�����, 1�Ҷ���, 2�м����
	void ShowText(const HDC &memDC, const double &dVal, const TCHAR *szDepartment, const int &iXLocation,
		const int &iYLocation, const char &iDir);
	void DrawXText(const HDC &memDC);	// ������ʼ����ֹƵ��/ʱ��ֵ���ı����
	void DrawXTextHorizontal3Grid(const HDC &memDC);	// ������ʼ����ֹƵ��/ʱ��ֵ���ı����--����3������
	void DrawYText(const HDC &memDC);	// ��ͼ��ʼ����ֹV/dbֵ
	void ShowManualText(const HDC &memDC);	// ��ʾ�Զ�������

	// Limit line ////////////////////////////////////////////////////////////////////
	//
	void DrawLimitLine(const HDC &memDC);	// ����Limit Line

	// Calucate //////////////////////////////////////////////////////////////////////
	//
	// ���ݵ�ǰ��������ID�������ǰ��ͼ������ֵ
	// dWavePixNum -- ���λ�ͼ���Ŀ��
	// nDataLen -- ������������
	// nDataID -- ��ǰ���ߵ�����id
	// return value -- ��ͼ���ߵĺ�����ֵ
	inline int GetWaveLineX(const double &dWavePixNum, const int &nDataLen, const int &nDataID);
	// ���ݲ��ε�ǰ������ֵ�������Ļ������ֵ
	inline int GetWaveLineX(const double &dData);
	// ���ݵ�ǰ��������ID�������ǰ��ͼ������ֵ
	// dWavePixNum -- ���λ�ͼ���Ŀ��
	// nDataLen -- ������������
	// dDataID -- ��ǰ���ߵ�����id, ��ֵ������ʽ
	// return value -- ��ͼ���ߵĺ�����ֵ
	inline int GetWaveLineX(const double &dWavePixNum, const int &nDataLen, const double &dDataID);
	// ���ݲ���������2ֵ�������Ļ������ֵ
	inline int GetWaveLineYSpecial(const double &dData);
	// ���ݲ��ε�ǰֵ�������Ļ������ֵ
	inline int GetWaveLineY(const double &dData);
	// ���ݲ��ε�ǰֵ�������Ļ������ֵ��˫������
	inline int GetWaveLineYUp(const double &dData);
	// ���ݲ��ε�ǰֵ�������Ļ������ֵ��˫������
	inline int GetWaveLineYDown(const double &dData);

	// Scroll bar /////////////////////////////////////////////////////////////////////
	//
	void DrawScrollBar(const HDC &memDC, const int &nDataLen);	// ����ScrollBar

	// Mouse //////////////////////////////////////////////////////////////////////////
	//
	void DrawMouseRect(const HDC &memDC);	//�������ѡ�񷽿�

	// Report /////////////////////////////////////////////////////////////////////////
	//
	void DrawReportText(CDC *pDC, CPrintInfo* pInfo);	// ���Ʊ�������

	// Varible /////////////////////////////////////////////////////////////////////////
	//
	const static int N_MAX_X_SCREEN = 1920;		// ��Ļ���ֱ���֧�֣�����
	const static int N_MAX_Y_SCREEN = 1080;		// ��Ļ���ֱ���֧�֣�����
	const static int I_WAVE_PIX_MOVE = 10;
	const static int N_LIMIT_COLOR_ID_OFFSET = 4;	// �ϸ���IDƫ����
	struct tagMouseLine m_MouseLine;
	tagREPORT m_ReportData;		// �����������ݽṹ

private:
	// ����ͼ Spectrogram //////////////////////////////////////////////////////////////
	//
	// ���ƹ���ͼ����
	// memDC -- ��ͼ�ڴ�DC
	// pColor -- ��ɫ��
	// pdLevel -- ���ȱ�
	// nColorNum -- ������ɫ�������
	void DrawSpecgView(HDC &memDC, const COLORREF *pColor, const double *pdLevel, const int &nColorNum);
	// ���ƹ���ͼ��Mkr
	// memDC -- ��ͼ�ڴ�DC
	// nDataLen -- ÿ���������ݳ���
	// nWaveNum -- ����ͼ��������
	void DrawSpectrogramMkr(HDC &memDC, const int &nDataLen, const int &nWaveNum);
	// ���ƹ���ͼ����ͼ
	// memDC -- ��ͼ�ڴ�DC
	// pdData -- ��������
	// nWaveNum -- ��������
	// nDataLen -- ÿ�����εĵ���
	// pColor -- ��ɫ��
	// pdLevel -- ���ȱ�
	// nColorNum -- ������ɫ�������
	// ����ֵ��true�ɹ���falseʧ�ܣ������������ڴ�����ʧ�����
	bool DrawSpectrogram(HDC &memDC, const double *pdData, const int &nWaveNum, const int &nDataLen, const COLORREF *pColor, const double *pdLevel,
		const int &nColorNum);
	//

	// Draw line by limit //////////////////////////////////////////////////////////////
	//
	// ���ݺϸ����ҵ���ǰ��Ӧ�����õ���ɫ���ؽ罻��
	// Color -- ��ǰ�����ɫ
	// dYPos -- ��ǰ���������ֵ
	// ..... -- ���кϸ��ߵ�ֵ
	// pbzPriority -- �ϸ��ߵ�ʹ��
	// ����ֵ��Խ���ϸ��ߵ�ID
	char FindPointColorOver(COLORREF &Color, const double &dYPos, const double &dUpLimit1Y, const double &dDownLimit1Y, const double &dUpLimit2Y,
		const double &dDownLimit2Y, const double &dUpLimit3Y, const double &dDownLimit3Y, const double &dUpLimit4Y, const double &dDownLimit4Y,
		const double &dUpLimit5Y, const double &dDownLimit5Y, const bool *pbzPriority);
	// ���ݺϸ����ҵ���ǰ��Ӧ�����õ���ɫ
	// Color -- ��ǰ�����ɫ
	// dYPos -- ��ǰ���������ֵ
	// ..... -- ���кϸ��ߵ�ֵ
	// pbzPriority -- �ϸ��ߵ�ʹ��
	// ����ֵ��Խ���ϸ��ߵ�ID
	char FindPointColor(COLORREF &Color, const double &dYPos, const double &dUpLimit1Y, const double &dDownLimit1Y, const double &dUpLimit2Y,
		const double &dDownLimit2Y, const double &dUpLimit3Y, const double &dDownLimit3Y, const double &dUpLimit4Y, const double &dDownLimit4Y,
		const double &dUpLimit5Y, const double &dDownLimit5Y, const bool *pbzPriority);
	// �ҵ������ںϸ��ߵĽ��������
	// nXPos, nYPos -- �����ĺ�������ֵ
	// dStartX, dStartY, dEndX, dEndY -- ���ε���ʼ�ᡢ���������ֹ�ᡢ������
	// dEndLimitX, dEndLimitY -- �ϸ��ߵ���ʼ�ᡢ���������ֹ�ᡢ������ֵ
	// nDataLen -- �������ݳ���
	// nID -- ����ID
	// ����ֵ��true���ڽ���㣬false�����ڽ����
	bool FindCrossPoint(int &nXPos, int &nYPos, const double &dStartX, const double &dStartY, const double &dEndX, const double &dEndY, const double &dStartLimitY,
		const double &dEndLimitY, const int &nDataLen, const int &nID);
	// ���ݲ��ε������������Լ��ϸ�����ȷ����������������ɫ�仯����
	// memDC -- ��ͼ�ڴ�DC
	// dXStart -- X��ԭ��ʼ����, dXEnd -- X��ԭ��ֹ����, dYStart -- Y��ԭ��ʼ����, dYEnd -- Y��ԭ��ֹ����
	// dUpLimit1Start, dUpLimit1End, dUpLimit2Start, dUpLimit2End, dUpLimit3Start, dUpLimit3End, dUpLimit4Start, dUpLimit4End, dUpLimit5Start, dUpLimit5End,
	// dDownLimit1Start, dDownLimit1End, dDownLimit2Start, dDownLimit2End, dDownLimit3Start, dDownLimit3End, dDownLimit4Start, dDownLimit4End,
	// dDownLimit5Start, dDownLimit5End, -- �ֱ���5���ϡ������޵�����ԭ�ؼ�������
	// pbzPriority -- �ϸ���ʹ��
	// nDataLen -- ��ǰ�������ݳ���
	// nID -- ��ǰ���ID
	// LineColor -- ��ǰ������ɫ
	// ����ֵ��true�����任��ɫ��false���ޱ任��ɫ
	bool GetLineColorByLimit(HDC &memDC, const double &dXStart, const double &dXEnd, const double &dYStart, const double &dYEnd,
		const double &dUpLimit1Start, const double &dUpLimit1End, const double &dUpLimit2Start, const double &dUpLimit2End,
		const double &dUpLimit3Start, const double &dUpLimit3End, const double &dUpLimit4Start, const double &dUpLimit4End,
		const double &dUpLimit5Start, const double &dUpLimit5End,
		const double &dDownLimit1Start, const double &dDownLimit1End, const double &dDownLimit2Start, const double &dDownLimit2End,
		const double &dDownLimit3Start, const double &dDownLimit3End, const double &dDownLimit4Start, const double &dDownLimit4End,
		const double &dDownLimit5Start, const double &dDownLimit5End, const bool *pbzPriority, const int &nDataLen, const int &nID, const COLORREF &LineColor);
	// ���Ʋ��Σ���ɫ���պϸ������������֣����ȸ���UpLimit�ģ�����UpLimit����ɫ��ʾ���������������ִ����ʾ���ȼ�
	// ����С�ģ�UpLimit����ʾ���ȼ�����DownLimit�����ȼ�
	// pdCurrent -- ������������
	// nCurrent --�����������ݳ���
	// pdMax -- ��󱣳ֲ�������
	// nMax -- ��󱣳ֲ������ݳ���
	// pdMin -- ��С���ֲ�������
	// nMin -- ��С���ֲ������ݳ���
	// pdAverage -- ƽ��ֵ��������
	// nAverage -- ƽ��ֵ�������ݳ���
	// pdUpLimit1 -- �Ϻϸ���1����
	// nUpLimit1 -- �Ϻϸ���1���ݳ���
	// pdDownLimit1 -- �ºϸ���1����
	// nDownLimit1 -- �ºϸ���1���ݳ���
	// pdUpLimit2 -- �Ϻϸ���2����
	// nUpLimit2 -- �Ϻϸ���2���ݳ���
	// pdDownLimit2 -- �ºϸ���2����
	// nDownLimit2 -- �ºϸ���2���ݳ���
	// pdUpLimit3 -- �Ϻϸ���3����
	// nUpLimit3 -- �Ϻϸ���3���ݳ���
	// pdDownLimit3 -- �ºϸ���3����
	// nDownLimit3 -- �ºϸ���3���ݳ���
	// pdUpLimit4 -- �Ϻϸ���4����
	// nUpLimit4 -- �Ϻϸ���4���ݳ���
	// pdDownLimit4 -- �ºϸ���4����
	// nDownLimit4 -- �ºϸ���4���ݳ���
	// pdUpLimit5 -- �Ϻϸ���5����
	// nUpLimit5 -- �Ϻϸ���5���ݳ���
	// pdDownLimit5 -- �ºϸ���5����
	// nDownLimit5 -- �ºϸ���5���ݳ���
	// bzPriority -- �ϸ���ʹ�ܣ�false��ʾ�رգ�true��ʾ��
	// ����ֵ��trueִ�гɹ���falseִ��ʧ��
	bool DrawLineByLimit(HDC &memDC, const double *pdCurrent, const int &nCurrent, const double *pdMax, const int &nMax,
		const double *pdMin, const int &nMin, const double *pdAverage, const int &nAverage,
		const double *pdUpLimit1, const int &nUpLimit1, const double *pdDownLimit1, const int &nDownLimit1,
		const double *pdUpLimit2, const int &nUpLimit2, const double *pdDownLimit2, const int &nDownLimit2,
		const double *pdUpLimit3, const int &nUpLimit3, const double *pdDownLimit3, const int &nDownLimit3,
		const double *pdUpLimit4, const int &nUpLimit4, const double *pdDownLimit4, const int &nDownLimit4,
		const double *pdUpLimit5, const int &nUpLimit5, const double *pdDownLimit5, const int &nDownLimit5, const bool *bzPriority);

	// QAM /////////////////////////////////////////////////////////////////////////////////////
	//
	// ��������ͼ�Ĳ�������
	// memDC -- �ڴ�DC
	// pnData -- ����ͼ���ݽṹ��
	// nDataLen -- ����ͼ����
	// bManualColor -- ����ͼ�����Զ�����ɫ����
	// ����ֵ��trueִ�гɹ���falseִ��ʧ��
	bool DrawQamData(const HDC &memDC, const struct tagCoordinate *pnData, const int &nDataLen,
		const bool &bManualColor);

	// Calucate /////////////////////////////////////////////////////////////////////////////////
	//
	// ���Ҳ�������ķ�ֵ
	void FindMaxWaveVal(const double* pdData, const int &nDataLen, const int &nMkrID);

	// Draw line ////////////////////////////////////////////////////////////////////////////////
	//
	// ���ƺ���3����������
	void DrawHorizontal3Line(const HDC &memDC, const double *pdData, const int &nDataLen, const double *pdData2,
		const int &nDataLen2, const double *pdData3, const int nDataLen3);
	// ���������������ߣ�����˫����
	void DrawDoubleWndLine(const HDC &memDC, const double* pdData1,
		const int &nDataLen1, const double* pdData2, const int &nDataLen2);
	// ���Ʋ�������, �Զ����С
	bool DrawLineSpecialLen(const HDC &memDC, const double* pdData, const int &nDataLen, const double* pdData2,
		const int &nDataLen2, const double *pdData3, const int &nDataLen3);
	// ���Ʋ�������
	bool DrawLineAdjust(const HDC &memDC, const double *pdData, const int &iDataLen, const double *pdData2, const int &nDataLen2, const double *pdData3,
		const int &nDataLen3, const double *pdData4, const int &nDataLen4, const double *pdData5, const int &nDataLen5, const double *pdData6,
		const int &nDataLen6, const double *pdData7, const int &nDataLen7, const double *pdData8, const int &nDataLen8, const double *pdData9,
		const int &nDataLen9, const double *pdData10, const int &nDataLen10, const double *pdData11, const int &nDataLen11, const double *pdData12,
		const int &nDataLen12, const double *pdData13, const int &nDataLen13, const double *pdData14, const int &nDataLen14, const double *pdData15,
		const int &nDataLen15, const double *pdData16, const int &nDataLen16, const double *pdData17, const int &nDataLen17, const double *pdData18,
		const int &nDataLen18, const double *pdData19, const int &nDataLen19, const double *pdData20, const int &nDataLen20);
	// ���Ʋ������ߣ�֧�ֲ�������������
	bool DrawLineEnableMaxPointNum(const HDC &memDC, const double *pdData, const int &nDataLen,
		const int &nMaxDataLen);

	// Variable /////////////////////////////////////////////////////////////////////////////////
	//
	struct tagGridNum m_GridNum;	// �������
	struct tagManualText m_ManualText[N_MAX_MANUAL_TEXT_NUMBER];	// �Զ�������
	struct tagMultiText m_MultiText[I_WAVE_NUM];	// ��������
	TAG_LimitLine m_LimitLineTag[I_LIMITLINE_NUMBER];	// LimitLine���ݽṹ
	tagCoorText m_CoorData[20];			// ��8831���������� wangzheng 2008-09-11
	RECT m_rect;					// ��ͼ��λ��
	POINT m_StartPoint;				// ��ͼ��ʼλ��
	HDC m_hMemDC;					// ��ͼ�ڴ�DC
	HBITMAP m_hBitmap;				// ��ͼ�ڴ�λͼ
	COLORREF m_MouseLineColor;		// ����϶��������ɫ
	COLORREF m_bkColor;				// ����ɫ
	COLORREF m_GridColor;			// ɾ��ɫ
	COLORREF m_LineColor[I_WAVE_NUM];	// ����ɫ
	COLORREF m_TextColor;			// �ı�ɫ
	COLORREF m_ActiveMkrColor;		// ��ǰ��Ƶ�����ɫ
	COLORREF m_mkrColor[I_MKR_NUMBER][I_WAVE_NUM];	// Ƶ��ɫ
	COLORREF m_MkrLineColor;		// Ƶ���ߵ���ɫ
	COLORREF m_ScrollBarHightLight;	// ��������������ʾ��ɫ
	COLORREF m_GridRoundColor;		// ɾ������Ȧ����ɫ
	COLORREF m_QamZoomColor;		// ���޿����ɫ
	COLORREF m_MkrTextColor[I_MKR_NUMBER][I_WAVE_NUM];
	COLORREF m_SpectrogramMkrColor;	// ����ͼMkr��ɫ

	int m_nQamZoomLineWidth;		// ���޿���߿�
	int m_iGridBorderWidth;			// ɾ��߿���
	int m_iXGridDepart;				// X����λ����
	int m_iYGridDepart;				// Y����λ����
	int m_iGridLineWidth;			// ɾ���߿��
	int m_iLineWidth[I_WAVE_NUM];	// ���߿��
	int m_imkrType;					// Ƶ������
	int m_iBorderGridTop;			// ɾ���߿�ľ��� -- ����
	int m_iBorderGridBottom;		// ɾ���߿�ľ��� -- �ײ�
	int m_iBorderGridRight;			// ɾ���߿�ľ��� -- �ҷ�
	int m_iBorderGridLeft;			// ɾ���߿�ľ��� -- ���
	int m_iMkrValue[I_MKR_NUMBER];	// Ƶ�������ֵ
	int m_iActiveMkr;				// ��ǰ��������Ƶ���ID
	int m_nActiveLimit;				// ��ǰ��������Limit Line
	int m_nRateSizeX;				// ����������ֵ,�ٷֱ�ֵ
	int m_nWaveStartPos;			// ������ʼλ��
	int m_nLimitLineNum;			// ��ǰLimit line ������
	int m_nStartMouseX;				// ����������ʱ���������ĳ�ʼֵ�����ڹ�����
	int m_nXTextOffsetY;			// ���������ֵ�������ƫ����
	int m_nYTextOffsetX;			// ���������ֵĺ�����ƫ����
	int m_nQamZoomNum;				// ����ͼ���޵���ֵ
	int m_nMkrXKeepType;			// mkr����ƫ�����ԣ����DEV_MKR_STYLE
	int m_nManualTextNum;			// �Զ�����������
	int m_nLimitTextDock[I_LIMITLINE_NUMBER];	// Limit����ͣ������
	int m_nMouseLineStartX;			// �����Ʋ��ε���ʼX����
	int m_nSpectrogramMkrX;			// ����ͼ������Mkrͣ��λ�ã�������ID
	int m_nSpectrogramMkrY;			// ����ͼ������Mkrͣ��λ�ã���������ID

	double m_dMouseLineStartY;		// �����Ʋ��ε���ʼY����
	double m_dzMkrVal[I_MKR_NUMBER];	// �ֶ�mkr��ֵ
	double m_dGridPointRate;		// ɾ�����ĵ��С������0.0 -- 1.0
	double m_dGridRoundRate;		// ɾ������Ȧ��С������0.0 -- 1.0
	double m_dStartX;				// ��������ʼֵ
	double m_dEndX;					// ��������ֵֹ
	double m_dFullStartX;			// ȫ����������ʼֵ
	double m_dFullEndX;				// ȫ����������ֵֹ
	double m_dStartY;				// ��������ʼֵ
	double m_dEndY;					// ��������ֵֹ
	double m_dSpecialStartY;		// ����2��ʼֵ
	double m_dSpecialEndY;			// ����2��ֵָ
	double m_dWavePixNum;			// ���ο��
	double m_dScrollBarStartPos;	// ��������ʼλ�ã�������
	double m_dScrollBarScrollWidth;	// �������Ŀ�ȣ������϶��Ļ�����
	double m_dLimitStep;			// Limit�Ĳ���ֵ

	TCHAR m_czMkrVal[I_MKR_NUMBER][N_TEXT_LEN];	// �ֶ�mkr��ֵ
	TCHAR m_czViewPrecision[8];
	TCHAR m_szXDepartment[I_DEPARTMENT_LEN];	// �����굥λ
	TCHAR m_szYDepartment[I_DEPARTMENT_LEN];	// �����굥λ
	TCHAR m_szYDep2nd[I_DEPARTMENT_LEN];		// �ڶ������굥λ
	TCHAR m_szMkrDepart[I_MKR_NUMBER][I_DEPARTMENT_LEN];	// Ƶ�굥λ
	TCHAR m_szMkrDep2nd[I_MKR_NUMBER][I_DEPARTMENT_LEN];	// Ƶ��ڶ������굥λ
	TCHAR m_szXStart[N_TEXT_LEN];		// ��������ʼֵ
	TCHAR m_szXCenter[N_TEXT_LEN];		// ����������ֵ
	TCHAR m_szXEnd[N_TEXT_LEN];			// �������ֵֹ
	CString m_szXCurrent;		// ��ǰƵ�������ֵ
	CStringArray m_szzYCurrent;	// �Զ���Y����ʾ����ֵ

	TCHAR m_czPrintFont[10];	// ��ӡ����
	TCHAR m_czTextFont[10];		// ʵʱ��ͼ��������
	int m_nPrintFontSize;		// ��ӡ���ִ�С
	int m_nTextFontSize;		// ʵʱ��ͼ���������С

	HBRUSH m_brBackground;	// ������ˢ
	HBRUSH m_brCross;		// ���滭ˢ
	HBITMAP m_OldBitmap;	// ���ݵ�ǰλͼ�豸

	Cdeskland m_GuangCom;

	BYTE m_ucScrollBarActiveButton;	// ��ǰscrollbar�ĸ����״̬
	BYTE m_ucGridType;				// ��ͼ�������
	BYTE m_bManualMkrVal;			// �ֶ�����Ƶ��ֵ
	BYTE m_uczWaveDockY[I_WAVE_NUM];// ����ʹ���ĸ�����ϵ��0��1��0Ϊ�������ϵ��1Ϊ�Ҳ�����ϵ
	BYTE m_ucUseSpectrogramMkr;		// �����Mkr���أ�ֵ������� SPECTROGRAM_MKR

	bool m_bGrid;					// �Ƿ���ʾɾ����, true��ʾ, false����ʾ
	bool m_bGridCenterRound;		// ɾ�񷽿�����Ȧ
	bool m_bGridCenterPoint;		// ɾ�񷽿����ĵ�
	bool m_bMkr[I_MKR_NUMBER];		// �Ƿ���ʾƵ��
	bool m_bMkrStatus[I_MKR_NUMBER][I_WAVE_NUM];	// ����֧������
	bool m_bEnalbeScrollBar;		// ScrollBar �Ƿ���ʾ��־, true��ʾ false����ʾ
	bool m_bEnableMkrDepartment;	// �Ƿ���ʾƵ�������굥λ, true��ʾ false����ʾ
	bool m_bEnableMkrLine;			// �Ƿ���ʾ������Ƶ����
	bool m_bEnableMkrXLine;			// ����Ƶ���߿���
	bool m_bEnableMkrYLine;			// ����Ƶ���߿���
	bool m_bEnable2ndY;				// �Ƿ��Ƿ���ʾ�ڶ���������ֵ
	bool m_bMkrKeepMaxVal;			// Ƶ���Ƿ���ٲ��εķ�ֵ��true���٣�false������
	bool m_bEnableXText;			// ��ʾ������ֵ
	bool m_bEnableYText;			// ��ʾ������ֵ
	bool m_bQamZoom;				// ����ͼ���޵Ŀ���
	bool m_bEnableManualXText;		// �Զ���X����������
	bool m_bEnableManualYText;		// �Զ���Y����������
	bool m_bEnableMText;			// �Զ���������Ϣ����
	bool m_bEnableMrkXText;			// ���Ͻ�Ƶ�������ֵ����  wangzheng 2008-08-04
	bool m_bEnableMrkYText;			// Ƶ�����������ֿ���
	bool m_bEnableCoorText;			// ��ʾ����8831�ϵ��������� wangzheng 2008-09-11
	bool m_bRectChange;				// ��ͼ�����ڳߴ�仯��־��true���ڳߴ緢���仯��falseδ�����仯
	bool m_bMkrAutoKeepX;			// Mkr�Զ����ٺ�����
	bool m_bSpectrogramMkrX;		// ���׺������α꿪��
	bool m_bSpectrogramMkrY;		// �����������α꿪��
	bool m_bEnableSpecgView;		// ����ͼ������˵������
};
