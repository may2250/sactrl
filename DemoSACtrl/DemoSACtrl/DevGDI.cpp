#include "StdAfx.h"
#include "DevGDI.h"
#include <comdef.h>
#include <assert.h>
#include <math.h>
#include <atlimage.h>

/////////////////////////////////////////////////////////////////

CDevGDI::CDevGDI(void)
{
	int i = 0;

	for (; i<I_WAVE_NUM; i++)
	{
		m_iLineWidth[i] = 1;
		m_LineColor[i] = RGB(255, 255, 255);
		m_uczWaveDockY[i] = Y_LEFT_COORDINATE_DOCK;	// 默认左侧坐标系
	}
	m_ActiveMkrColor = RGB(255, 255, 255);
	m_LineColor[0] = RGB(0, 255, 0);
	m_LineColor[1] = RGB(255, 255, 0);
	m_LineColor[2] = RGB(255, 0, 255);
	m_LineColor[3] = RGB(0, 255, 255);
	m_LineColor[4] = RGB(0, 0, 255);
	m_LineColor[5] = RGB(255, 0, 0);
	m_MkrLineColor = RGB(0, 220, 220);
	m_ScrollBarHightLight = RGB(255, 255, 255);	// 滑动条高亮度显示颜色
	m_MouseLineColor = RGB(255, 255, 255);		// 鼠标拖动方块的颜色
	m_GridRoundColor = RGB(255, 0, 255);		// 删格中心圈的颜色
	memset(m_iMkrValue, 0, sizeof(int)*10);
	memset(m_bMkr, false, sizeof(bool)*I_MKR_NUMBER);
	memset(m_bMkrStatus, true, sizeof(bool)*I_WAVE_NUM*I_MKR_NUMBER);
	memset(m_czMkrVal, 0, sizeof(TCHAR)*I_MKR_NUMBER*I_DEPARTMENT_LEN);
	m_iActiveMkr = 0;
	m_nActiveLimit = 0;
	m_szXDepartment[0] = _T('\0');
	m_szYDepartment[0] = _T('\0');
	m_nRateSizeX = DEVGDI_WAVE_AUTOADJUST;
	m_dWavePixNum = 1.0;
	m_ucScrollBarActiveButton = DEVGDI_SCROLLBAR_NOACTIVE;
	m_ucGridType = DEV_GRID_CLASSICAL;
	m_nWaveStartPos = 0;
	m_nLimitLineNum = I_LIMITLINE_NUMBER;
	m_nStartMouseX = 0;			// 鼠标左键按下时，鼠标坐标的初始值，用于滚动条
	m_GridNum.nXNum = 8;
	m_GridNum.nYNum = 6;		// DS8821默认对数8，线性10
	m_nXTextOffsetY = 0;		// 横坐标文字的纵坐标偏移量
	m_nYTextOffsetX = 0;		// 纵坐标文字的横坐标偏移量
	m_dGridPointRate = 0.05;	// 删格中心点大小比例，0.0 -- 1.0
	m_dGridRoundRate = 0.5;		// 删格中心圈大小比例，0.0 -- 1.0

	m_StartPoint.x = 0;
	m_StartPoint.y = 0;
	m_iBorderGridBottom = DEFAULT_BORDER_GRID_BOTTOM;
	m_iBorderGridLeft = DEFAULT_BORDER_GRID_LEFT;
	m_iBorderGridTop = DEFAULT_BORDER_GRID_TOP;
	m_iBorderGridRight = DEFAULT_BORDER_GRID_RIGHT;
	m_dStartX = 0.0;			// 横坐标起始值
	m_dEndX = 1000000.0;		// 横坐标中止值
	m_dFullStartX = 0.0;		// 全景横坐标起始值
	m_dFullEndX = 1000000.0;	// 全景横坐标中止值
	m_dStartY = 0.0;
	m_dEndY = 1000000.0;
	m_dSpecialStartY = 0.0;
	m_dSpecialEndY = 100.0;
	m_hwnd = NULL;
	m_bGrid = true;
	m_bGridCenterRound = false;	// 删格方块中心圈
	m_bGridCenterPoint = false;	// 删格方块中心点
	m_bEnalbeScrollBar = false;
	m_bEnableMkrDepartment = true;
	m_bEnableMkrLine = false;
	m_bEnableMkrXLine = true;
	m_bEnableMkrXLine = true;
	//	m_bAutoMkrXValue = true;	// 是否自动计算mkr横坐标值
	m_bMkrKeepMaxVal = true;	// 频标是否跟踪波形的峰值，true跟踪，false不跟踪
	m_bEnableXText = true;		// 显示横坐标值
	m_bEnableYText = true;		// 显示纵坐标值
	m_bManualMkrVal = 0;
	m_bMkrAutoKeepX = false;

	ZeroMemory(&m_MouseLine, sizeof(tagMouseLine));

	for (i=0; i<I_LIMITLINE_NUMBER; i++)
	{
		m_LimitLineTag[i].m_dzLimitLineStartVal = 0.0;
		m_LimitLineTag[i].m_dzLimitLineEndVal = 10.0;
		m_LimitLineTag[i].m_dzLimitLineMinVal = 0.0;
		m_LimitLineTag[i].m_dzLimitLineMaxVal = 0.0;
		m_LimitLineTag[i].m_LimitLineColor = RGB(255, 0, 0);
		m_LimitLineTag[i].m_nLineWidth = 1;
		m_LimitLineTag[i].m_bzEnableLimitLine = false;	// 是否显示、隐藏Limit line
		m_LimitLineTag[i].m_bzFullScreen = true;
		m_LimitLineTag[i].m_bManualText = false;
		m_LimitLineTag[i].m_bEnableText = false;
	}

	m_nQamZoomNum = 1;
	m_QamZoomColor = RGB(0, 0, 255);
	m_nQamZoomLineWidth = 1;
	m_bQamZoom = true;
	_tcscpy(m_czViewPrecision, _T("%.3f"));

	m_bEnableManualXText = false;
	m_bEnableManualYText = false;		// 自定义Y轴坐标内容
	m_nMkrXKeepType = DEV_MKR_KEEP_LEFT;
	m_bEnableMText = false;
	m_nManualTextNum = N_MAX_MANUAL_TEXT_NUMBER;
	memset(m_ManualText, 0, sizeof(struct tagManualText)*N_MAX_MANUAL_TEXT_NUMBER);
	for (i=0; i<N_MAX_MANUAL_TEXT_NUMBER; i++)
	{
		_tcscpy(m_ManualText[i].czSeperate, _T(" "));
	}

	m_nPrintFontSize = 100;
	m_nTextFontSize = 100;
	_tcscpy(m_czPrintFont, _T("System"));
	_tcscpy(m_czTextFont, _T("System"));
	m_bEnableMrkYText = true;			// 频标纵坐标文字开关
	m_bEnableMrkXText = true;	// wangzheng 2008-08-04
	m_bEnableCoorText = false;  // wangzheng 2008-09-11
	m_dLimitStep = 1.0;
	for (i=0; i<I_LIMITLINE_NUMBER; i++)
	{
		m_nLimitTextDock[i] = DEV_KEEP_TOP_RIGHT;
	}

	m_dMouseLineStartY = 0.0;
	m_nMouseLineStartX = 0;
	m_bRectChange = true;	// 窗口尺寸发生变化
	m_bEnable2ndY = false;

	for (i=0; i<I_MKR_NUMBER; i++)
	{
		_tcscpy(m_czMkrVal[i], _T(" "));
		_tcscpy(m_szMkrDepart[i], _T(" "));
		_tcscpy(m_szMkrDep2nd[i], _T(" "));
	}
	_tcscpy(m_szXDepartment, _T(" "));
	_tcscpy(m_szYDepartment, _T(" "));
	_tcscpy(m_szYDep2nd, _T(" "));
	_tcscpy(m_szXStart, _T(" "));
	_tcscpy(m_szXCenter, _T(" "));
	_tcscpy(m_szXEnd, _T(" "));

	m_bSpectrogramMkrX = false;
	m_bSpectrogramMkrY = false;
	m_SpectrogramMkrColor = RGB(255, 255, 255);
	m_nSpectrogramMkrX = 0;
	m_nSpectrogramMkrY = 0;
	m_ucUseSpectrogramMkr = SPECTROGRAM_MKR_NONE;
	m_bEnableSpecgView = true;	// 默认光谱图文字说明开
}

CDevGDI::~CDevGDI(void)
{
}

// wangzheng 2008-08-04
void CDevGDI::GDI_SetXMrkEnable( const bool &bEnable )
{
	m_bEnableMrkXText = bEnable;
}

// 设置频标纵坐标文字开关
void CDevGDI::GDI_SetYMkrEnable(const bool &bEnable)
{
	m_bEnableMrkYText = bEnable;
}

// 初始化绘图类
// Rect -- 窗体位置, hWnd -- 窗体句柄, bkColor -- 绘图背景色, 
// GridColor -- 绘图表格色, iGridBorderWidth -- 表格边框宽度,
// iGridLineWidth -- 表格线宽度, LineColor -- 数据曲线颜色,
// iLineWidth -- 数据曲线宽度, TextColor -- 文字颜色, mkrColor -- 频标色
// imkrType -- 频标特征
bool CDevGDI::GDI_Init(const RECT &rect, const HWND &hWnd /*= NULL*/,
					   const COLORREF &bkColor /*= RGB(50, 50, 50)*/,
					   const COLORREF &GridColor /*= RGB(0, 255, 0)*/,
					   const int &iGridBorderWidth /*= 2*/, const int &iGridLineWidth /*= 1*/,
					   const COLORREF &LineColor /*= RGB(255, 0, 0)*/, const int &iLineWidth
					   /*= 1*/, const COLORREF &TextColor /*= RGB(255, 255, 0)*/,
					   const COLORREF &mkrColor /*= RGB(0, 0, 255)*/, const int &imkrType
					   /*= 0*/)
{
	m_hwnd = hWnd;
	m_hdc = GetDC(hWnd);
	int i = 0;
	int j = 0;

	m_hMemDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	GDI_SetBKColor(bkColor);
	GDI_SetRect(rect);
	GDI_SetGridStyle(GridColor, iGridBorderWidth, iGridLineWidth);
	GDI_SetLine(LineColor, iLineWidth);
	GDI_SetTextColor(TextColor);
	for (i=0; i<I_MKR_NUMBER; i++)
	{
		GDI_SetMkrStyle(mkrColor, imkrType, i);
		for (j=0; j<I_WAVE_NUM; j++)
		{
			m_MkrTextColor[i][j] = TextColor;
		}
	}
	GDI_SetActiveMkr(0);

	return true;
}

//设置绘图背景色
bool CDevGDI::GDI_SetBKColor(const COLORREF &bkColor)
{
	m_bkColor = bkColor;

	DeleteObject(m_brBackground);
	DeleteObject(m_brCross);

	m_brBackground = CreateSolidBrush(bkColor);
	m_brCross = CreateHatchBrush(HS_DIAGCROSS, 0L);

	return true;
}

// 获得绘图区域
void CDevGDI::GDI_GetRect(RECT &rect)
{
	rect = m_rect;
}

//设置绘图区域
bool CDevGDI::GDI_SetRect(const RECT &rect)
{
	if ((m_rect.right==rect.right-rect.left)&&(m_rect.bottom==rect.bottom-rect.top))
	{
		return false;
	}

	m_rect = rect;
	m_rect.bottom -= m_rect.top;
	m_rect.right -= m_rect.left;
	m_rect.left = 0;
	m_rect.top = 0;

	//DeleteObject(m_OldBitmap);
	////将兼容位图选入内存DC
	//m_OldBitmap = CreateBitmap(m_rect.right-m_rect.left,
	//	m_rect.bottom-m_rect.top, 0xffffffff, 32, NULL);
	m_bRectChange = true;

	return true;
}

// 设置表格属性
// GridColor -- 表格颜色, iGridBorderWidth -- 边框宽度, iLineWidth -- 表格线宽
void CDevGDI::GDI_SetGridStyle(const COLORREF &GridColor,
							   const int &iGridBorderWidth, const int &iGridLineWidth, const BYTE &nGridType/* = DEV_GRID_CLASSICAL*/)
{
	m_GridColor = GridColor;
	m_iGridBorderWidth = iGridBorderWidth;
	m_iGridLineWidth = iGridLineWidth;
	m_ucGridType = nGridType;
}

// 设置数据曲线属性
// LineColor -- 曲线的颜色, iLineWidth -- 线的宽度
void CDevGDI::GDI_SetLine(const COLORREF &LineColor, const int &iLineWidth, const COLORREF &LineColor2 /*= RGB(0, 255, 255)*/, const int &iLineWidth2 /*= 1*/,
						  const COLORREF &LineColor3 /*= RGB(255, 0, 255)*/, const int &nLineWidth3 /*= 1*/, const COLORREF &LineColor4 /*= RGB(255, 0, 0)*/, const int &nLineWidth4 /*= 1*/,
						  const COLORREF &LineColor5 /*= RGB(0, 255, 0)*/, const int &nLineWidth5 /*= 1*/, const COLORREF &LineColor6 /*= RGB(0, 0, 255)*/, const int &nLineWidth6 /*= 1*/,
						  const COLORREF &LineColor7 /*= RGB(255, 255, 255)*/, const int &nLineWidth7 /*= 1*/, const COLORREF &LineColor8 /*= RGB(255, 255, 255)*/, const int &nLineWidth8 /*= 1*/,
						  const COLORREF &LineColor9 /*= RGB(255, 255, 255)*/, const int &nLineWidth9 /*= 1*/, const COLORREF &LineColor10 /*= RGB(255, 255, 255)*/, const int &nLineWidth10 /*= 1*/,
						  const COLORREF &LineColor11 /*= RGB(255, 255, 255)*/, const int &nLineWidth11 /*= 1*/, const COLORREF &LineColor12 /*= RGB(255, 255, 255)*/, const int &nLineWidth12 /*= 1*/,
						  const COLORREF &LineColor13 /*= RGB(255, 255, 255)*/, const int &nLineWidth13 /*= 1*/, const COLORREF &LineColor14 /*= RGB(255, 255, 255)*/, const int &nLineWidth14 /*= 1*/,
						  const COLORREF &LineColor15 /*= RGB(255, 255, 255)*/, const int &nLineWidth15 /*= 1*/, const COLORREF &LineColor16 /*= RGB(255, 255, 255)*/, const int &nLineWidth16 /*= 1*/,
						  const COLORREF &LineColor17 /*= RGB(255, 255, 255)*/, const int &nLineWidth17 /*= 1*/, const COLORREF &LineColor18 /*= RGB(255, 255, 255)*/, const int &nLineWidth18 /*= 1*/,
						  const COLORREF &LineColor19 /*= RGB(255, 255, 255)*/, const int &nLineWidth19 /*= 1*/, const COLORREF &LineColor20 /*= RGB(255, 255, 255)*/, const int &nLineWidth20 /*= 1*/)
{
	m_LineColor[0] = LineColor;
	m_LineColor[1] = LineColor2;
	m_LineColor[2] = LineColor3;
	m_LineColor[3] = LineColor4;
	m_LineColor[4] = LineColor5;
	m_LineColor[5] = LineColor6;
	m_LineColor[6] = LineColor7;
	m_LineColor[7] = LineColor8;
	m_LineColor[8] = LineColor9;
	m_LineColor[9] = LineColor10;
	m_LineColor[10] = LineColor11;
	m_LineColor[11] = LineColor12;
	m_LineColor[12] = LineColor13;
	m_LineColor[13] = LineColor14;
	m_LineColor[14] = LineColor15;
	m_LineColor[15] = LineColor16;
	m_LineColor[16] = LineColor17;
	m_LineColor[17] = LineColor18;
	m_LineColor[18] = LineColor19;
	m_LineColor[19] = LineColor20;

	m_iLineWidth[0] = iLineWidth;
	m_iLineWidth[1] = iLineWidth2;
	m_iLineWidth[2] = nLineWidth3;
	m_iLineWidth[3] = nLineWidth4;
	m_iLineWidth[4] = nLineWidth5;
	m_iLineWidth[5] = nLineWidth6;
	m_iLineWidth[6] = nLineWidth7;
	m_iLineWidth[7] = nLineWidth8;
	m_iLineWidth[8] = nLineWidth9;
	m_iLineWidth[9] = nLineWidth10;
	m_iLineWidth[10] = nLineWidth11;
	m_iLineWidth[11] = nLineWidth12;
	m_iLineWidth[12] = nLineWidth13;
	m_iLineWidth[13] = nLineWidth14;
	m_iLineWidth[14] = nLineWidth15;
	m_iLineWidth[15] = nLineWidth16;
	m_iLineWidth[16] = nLineWidth17;
	m_iLineWidth[17] = nLineWidth18;
	m_iLineWidth[18] = nLineWidth19;
	m_iLineWidth[19] = nLineWidth20;
}

// 读取数据曲线属性
// LineColor -- 曲线颜色
// iLineWidth -- 曲线宽度
void CDevGDI::GDI_GetLine(COLORREF &LineColor, int &iLineWidth, COLORREF &LineColor2, int &iLineWidth2, COLORREF &LineColor3, int &nLineWidth3, COLORREF &LineColor4,
	int &nLineWidth4, COLORREF &LineColor5, int &nLineWidth5, COLORREF &LineColor6, int &nLineWidth6, COLORREF &LineColor7, int &nLineWidth7, COLORREF &LineColor8,
	int &nLineWidth8, COLORREF &LineColor9, int &nLineWidth9, COLORREF &LineColor10, int &nLineWidth10, COLORREF &LineColor11, int &nLineWidth11,
	COLORREF &LineColor12, int &nLineWidth12, COLORREF &LineColor13, int &nLineWidth13, COLORREF &LineColor14, int &nLineWidth14, COLORREF &LineColor15,
	int &nLineWidth15, COLORREF &LineColor16, int &nLineWidth16, COLORREF &LineColor17, int &nLineWidth17, COLORREF &LineColor18, int &nLineWidth18,
	COLORREF &LineColor19, int &nLineWidth19, COLORREF &LineColor20, int &nLineWidth20)
{
	LineColor = m_LineColor[0];
	LineColor2 = m_LineColor[1];
	LineColor3 = m_LineColor[2];
	LineColor4 = m_LineColor[3];
	LineColor5 = m_LineColor[4];
	LineColor6 = m_LineColor[5];
	LineColor7 = m_LineColor[6];
	LineColor8 = m_LineColor[7];
	LineColor9 = m_LineColor[8];
	LineColor10 = m_LineColor[9];
	LineColor11 = m_LineColor[10];
	LineColor12 = m_LineColor[11];
	LineColor13 = m_LineColor[12];
	LineColor14 = m_LineColor[13];
	LineColor15 = m_LineColor[14];
	LineColor16 = m_LineColor[15];
	LineColor17 = m_LineColor[16];
	LineColor18 = m_LineColor[17];
	LineColor19 = m_LineColor[18];
	LineColor20 = m_LineColor[19];

	iLineWidth = m_iLineWidth[0];
	iLineWidth2 = m_iLineWidth[1];
	nLineWidth3 = m_iLineWidth[2];
	nLineWidth4 = m_iLineWidth[3];
	nLineWidth5 = m_iLineWidth[4];
	nLineWidth6 = m_iLineWidth[5];
	nLineWidth7 = m_iLineWidth[6];
	nLineWidth8 = m_iLineWidth[7];
	nLineWidth9 = m_iLineWidth[8];
	nLineWidth10 = m_iLineWidth[9];
	nLineWidth11 = m_iLineWidth[10];
	nLineWidth12 = m_iLineWidth[11];
	nLineWidth13 = m_iLineWidth[12];
	nLineWidth14 = m_iLineWidth[13];
	nLineWidth15 = m_iLineWidth[14];
	nLineWidth16 = m_iLineWidth[15];
	nLineWidth17 = m_iLineWidth[16];
	nLineWidth18 = m_iLineWidth[17];
	nLineWidth19 = m_iLineWidth[18];
	nLineWidth20 = m_iLineWidth[19];
}

//设置文字颜色
void CDevGDI::GDI_SetTextColor(const COLORREF &TextColor)
{
	m_TextColor = TextColor;
}

// 设置频标属性
// mkrColor -- 频标颜色, imkrType -- 频标类型
bool CDevGDI::GDI_SetMkrStyle(const COLORREF &mkrColor, const int &imkrType, const int &nMkrID /*= 0*/)
{
	int i = 0;
	assert((nMkrID>=0)&&(nMkrID<I_MKR_NUMBER));

	if ((nMkrID<0)||(nMkrID>=I_MKR_NUMBER))
	{
		return false;
	}

	for (; i<I_WAVE_NUM; i++)
	{
		m_mkrColor[nMkrID][i] = mkrColor;
	}
	m_imkrType = imkrType;

	return true;
}

// 获得频标属性
// mkrColor -- 频标颜色, imkrType -- 频标类型
bool CDevGDI::GDI_GetMkrStyle(COLORREF &mkrColor, int &nMkrType, const int &nMkrID)
{
	assert((nMkrID>=0)&&(nMkrID<I_MKR_NUMBER));

	if ((nMkrID>=0)&&(nMkrID<I_MKR_NUMBER))
	{
		return false;
	}

	mkrColor = m_mkrColor[nMkrID][0];
	nMkrType = m_imkrType;

	return true;
}

// 退出GDI绘图系统
void CDevGDI::GDI_Exit()
{
	DeleteObject(m_brBackground);
	DeleteObject(m_brCross);
	DeleteObject(m_OldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}

// 的到绘图边框范围
void CDevGDI::GDI_GetBorderGridPos(RECT &rect)
{
	rect.top = m_iBorderGridTop;
	rect.bottom = m_iBorderGridBottom;
	rect.right = m_iBorderGridRight;
	rect.left = m_iBorderGridLeft;
}

// 设置绘图边框范围
void CDevGDI::GDI_SetBorderGridPos(const RECT &rect)
{
	m_iBorderGridTop = rect.top;			// 删格距边框的距离 -- 顶部
	m_iBorderGridBottom = rect.bottom;		// 删格距边框的距离 -- 底部
	m_iBorderGridRight = rect.right;		// 删格距边框的距离 -- 右方
	m_iBorderGridLeft = rect.left;
}

// 设置绘图边框范围
void CDevGDI::GDI_SetBorderGridPos(const int &nLeft, const int &nTop, const int &nRight, const int &nBottom)
{
	m_iBorderGridTop = nTop;			// 删格距边框的距离 -- 顶部
	m_iBorderGridBottom = nBottom;		// 删格距边框的距离 -- 底部
	m_iBorderGridRight = nRight;		// 删格距边框的距离 -- 右方
	m_iBorderGridLeft = nLeft;
}

// 绘制星座图的象限框
void CDevGDI::DrawQamZoom(const HDC &memDC)
{
	if (m_bQamZoom)
	{
		HPEN hPen = CreatePen(PS_SOLID, m_nQamZoomLineWidth, m_QamZoomColor);
		HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
		int nLoStartX;
		int nLoEndX;
		int nLoStartY;
		int nLoEndY;

		switch (m_nQamZoomNum)
		{
		case 1:
			nLoStartX = m_rect.left+m_iBorderGridLeft;
			nLoEndX = m_rect.left+m_iBorderGridLeft
				+static_cast<int>(0.5*(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight));
			nLoStartY = m_rect.top+m_iBorderGridTop;
			nLoEndY = m_rect.top+m_iBorderGridTop
				+static_cast<int>(0.5*(m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop));
			break;
		case 2:
			nLoStartX = m_rect.left+m_iBorderGridLeft
				+static_cast<int>(0.5*(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight));
			nLoEndX = m_rect.right-m_iBorderGridRight-1;
			nLoStartY = m_rect.top+m_iBorderGridTop;
			nLoEndY = m_rect.top+m_iBorderGridTop
				+static_cast<int>(0.5*(m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop));
			break;
		case 3:
			nLoStartX = m_rect.left+m_iBorderGridLeft
				+static_cast<int>(0.5*(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight));
			nLoEndX = m_rect.right-m_iBorderGridRight-1;
			nLoStartY = m_rect.top+m_iBorderGridTop
				+static_cast<int>(0.5*(m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop));
			nLoEndY = m_rect.bottom-m_iBorderGridBottom-1;
			break;
		case 4:
			nLoStartX = m_rect.left+m_iBorderGridLeft;
			nLoEndX = m_rect.left+m_iBorderGridLeft
				+static_cast<int>(0.5*(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight));
			nLoStartY = m_rect.top+m_iBorderGridTop
				+static_cast<int>(0.5*(m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop));
			nLoEndY = m_rect.bottom-m_iBorderGridBottom-1;
			break;
		default:
			nLoStartX = 0;
			nLoEndX = 0;
			nLoStartY = 0;
			nLoEndY = 0;
			break;
		}

		MoveToEx(memDC, nLoStartX, nLoStartY, NULL);
		LineTo(memDC, nLoStartX, nLoEndY);
		LineTo(memDC, nLoEndX, nLoEndY);
		LineTo(memDC, nLoEndX, nLoStartY);
		LineTo(memDC, nLoStartX, nLoStartY);

		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);
	}
}

// 显示QAM数据
// pnData -- 波形数据
// nDataLen -- 波形数据长度
// bManualColor -- 自定义波形颜色开关，false使用类内部的波形颜色属性，true使用自定义颜色，每个点的颜色可以不同
// 返回值：true成功，false失败
bool CDevGDI::GDI_DrawQAM(const struct tagCoordinate *pnData, const int &nDataLen, const bool &bManualColor /*= false*/)
{
	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right, m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, m_brCross);	// 备份当前画刷
	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);

	if (m_ucGridType==DEV_GRID_CLASSICAL)
	{
		DrawGrid(memDC);
	}
	else
	{
		DrawGridSpectrum(memDC);
	}
	DrawGridCenterRound(memDC);
	DrawGridCenterPoint(memDC);
	DrawQamZoom(memDC);
	ShowManualText(memDC);

	DrawQamData(memDC, pnData, nDataLen, bManualColor);

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, memDC,
		m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(mybitmap);
	DeleteDC(memDC);

	return true;
}

// 显示QAM数据
bool CDevGDI::GDI_DrawQAM(deque<int> &nstQamData)
{
	deque<int>::iterator nstQamDataIter = nstQamData.begin();
	int i = 0;
	int nXPos = 0;
	int nYPos = 0;
	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right,
		m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, m_brCross);// 备份当前画刷
	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);

	if (m_ucGridType==DEV_GRID_CLASSICAL)
	{
		DrawGrid(memDC);
	}
	else
	{
		DrawGridSpectrum(memDC);
	}
	DrawGridCenterRound(memDC);
	DrawGridCenterPoint(memDC);
	DrawQamZoom(memDC);
	ShowManualText(memDC);

	m_dWavePixNum = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	while (nstQamDataIter<nstQamData.end())	// 画细点
	{
		nXPos = GetWaveLineX(*nstQamDataIter);
		nstQamDataIter ++;
		nYPos =  m_rect.bottom-m_iBorderGridBottom+m_iBorderGridTop-1-GetWaveLineY(*nstQamDataIter);
		nstQamDataIter ++;
		SetPixel(memDC, nXPos, nYPos, m_LineColor[0]);
	}

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, memDC,
		m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(mybitmap);
	DeleteDC(memDC);

	return true;
}

// 仅绘制数据
bool CDevGDI::GDI_DrawLineOnly(const double *pdData, const int &nDataLen, const double *pdData2/* = NULL*/,
							   const int &nDataLen2/* = 0*/)
{
	int i = 0;
	int nXPos = 0;//横坐标曲线点
	int nYPos = 0;//纵坐标曲线点
	// 当前画笔设备 -- Line
	HPEN hPen = CreatePen(PS_SOLID, 1, m_LineColor[0]);
	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right,
		m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

	// Draw back ground
	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);

	// Draw line
	m_dWavePixNum = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	if(m_dWavePixNum < 1.0)
	{
		m_dWavePixNum = 1.0;
	}
	nXPos = GetWaveLineX(m_dWavePixNum, nDataLen, i);
	nYPos = GetWaveLineY(pdData[i]);
	MoveToEx(memDC, nXPos, nYPos, NULL);

	switch (m_iLineWidth[0])
	{
	case 1:
		for (i=0; i<nDataLen; i++)
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen, i);
			nYPos = GetWaveLineY(pdData[i]);
			LineTo(memDC, nXPos, nYPos);
		}
		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);

		if (nDataLen2>0)
		{
			hPen = CreatePen(PS_SOLID, 1, m_LineColor[1]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, 0);
			nYPos = GetWaveLineY(pdData2[0]);
			MoveToEx(memDC, nXPos, nYPos, NULL);
			for (i=0; i<nDataLen2; i++)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
				nYPos = GetWaveLineY(pdData2[i]);
				LineTo(memDC, nXPos, nYPos);
			}
		}
		break;
	case I_HORIZONTAL_LINE:
		for (i=0; i<nDataLen; i++)
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen, i);
			nYPos = GetWaveLineY(pdData[i]);
			MoveToEx(memDC, nXPos, m_rect.bottom-m_rect.top-m_iBorderGridBottom, NULL);
			LineTo(memDC, nXPos, nYPos);
		}
		break;
	default:
		break;
	}
	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);

	// Draw limit line
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
	for (i=0; i<2; i++)
	{
		MoveToEx(memDC, static_cast<int>((m_rect.right-m_iBorderGridRight-m_rect.left-m_iBorderGridLeft)
			*(m_LimitLineTag[i].m_dzLimitLineMinVal-m_dStartX)/(m_dEndX-m_dStartX))+m_iBorderGridLeft,
			m_rect.top, NULL);
		LineTo(memDC, static_cast<int>((m_rect.right-m_iBorderGridRight-m_rect.left-m_iBorderGridLeft)
			*(m_LimitLineTag[i].m_dzLimitLineMinVal-m_dStartX)/(m_dEndX-m_dStartX))+m_iBorderGridLeft,
			m_rect.bottom);
	}
	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
	for (; i<4; i++)
	{
		MoveToEx(memDC, static_cast<int>((m_rect.right-m_iBorderGridRight-m_rect.left-m_iBorderGridLeft)
			*(m_LimitLineTag[i].m_dzLimitLineMinVal-m_dStartX)/(m_dEndX-m_dStartX))+m_iBorderGridLeft,
			m_rect.top, NULL);
		LineTo(memDC, static_cast<int>((m_rect.right-m_iBorderGridRight-m_rect.left-m_iBorderGridLeft)
			*(m_LimitLineTag[i].m_dzLimitLineMinVal-m_dStartX)/(m_dEndX-m_dStartX))+m_iBorderGridLeft,
			m_rect.bottom);
	}
	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
	for (; i<6; i++)
	{
		MoveToEx(memDC, static_cast<int>((m_rect.right-m_iBorderGridRight-m_rect.left-m_iBorderGridLeft)
			*(m_LimitLineTag[i].m_dzLimitLineMinVal-m_dStartX)/(m_dEndX-m_dStartX))+m_iBorderGridLeft,
			m_rect.top, NULL);
		LineTo(memDC, static_cast<int>((m_rect.right-m_iBorderGridRight-m_rect.left-m_iBorderGridLeft)
			*(m_LimitLineTag[i].m_dzLimitLineMinVal-m_dStartX)/(m_dEndX-m_dStartX))+m_iBorderGridLeft,
			m_rect.bottom);
	}
	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, memDC, m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(mybitmap);
	DeleteDC(memDC);

	return true;
}

// 设置报表文字大小和字体
// pszFont -- 文字字体
// nFontSize -- 文字大小
void CDevGDI::GDI_SetReportFont(const TCHAR *pszFont, const int &nFontSize)
{
	_tcscpy(m_czPrintFont, pszFont);
	m_nPrintFontSize = nFontSize;
}

// 显示一帧画面用于报表, 的坐标值, iData -- 数据曲线, iDataLen -- 扫描点数
bool CDevGDI::GDI_DrawReport(CDC *pDC, CPrintInfo* pInfo, const double *pdData, const int &nDataLen, const double *pdData2/* = NULL*/,
							 const int &nDataLen2/* = 0*/, const double *pdData3 /*=NULL*/, const int &nDataLen3 /*=0*/, const double *pdData4 /*= NULL*/,
							 const int &nDataLen4 /*= 0*/, const double *pdData5 /*= NULL*/, const int &nDataLen5 /*= 0*/, const double *pdData6 /*= NULL*/,
							 const int &nDataLen6 /*= 0*/, const double *pdData7 /*= NULL*/, const int &nDataLen7 /*= 0*/, const double *pdData8 /*= NULL*/,
							 const int &nDataLen8 /*= 0*/, const double *pdData9 /*= NULL*/, const int &nDataLen9 /*= 0*/, const double *pdData10 /*= NULL*/,
							 const int &nDataLen10 /*= 0*/, const double *pdData11 /*= NULL*/, const int &nDataLen11 /*= 0*/, const double *pdData12 /*= NULL*/,
							 const int &nDataLen12 /*= 0*/, const double *pdData13 /*= NULL*/, const int &nDataLen13 /*= 0*/, const double *pdData14 /*= NULL*/,
							 const int &nDataLen14 /*= 0*/, const double *pdData15 /*= NULL*/, const int &nDataLen15 /*= 0*/, const double *pdData16 /*= NULL*/,
							 const int &nDataLen16 /*= 0*/, const double *pdData17 /*= NULL*/, const int &nDataLen17 /*= 0*/, const double *pdData18 /*= NULL*/,
							 const int &nDataLen18 /*= 0*/, const double *pdData19 /*= NULL*/, const int &nDataLen19 /*= 0*/, const double *pdData20 /*= NULL*/,
							 const int &nDataLen20 /*= 0*/)
{
	int i = 0;
	int nXPos = 0;//横坐标曲线点
	int nYPos = 0;//纵坐标曲线点
	CBrush myBrush;
	CFont myFont;
	CFont *pBakFont;

	// 当前画笔设备 -- Line
	myBrush.CreateSolidBrush(m_bkColor);
	// Draw back ground
	pDC->SetBkColor(m_bkColor);
	pDC->FillRect(&m_rect, &myBrush);
	myBrush.DeleteObject();
	pDC->SetTextColor(m_TextColor);
	pDC->SetTextAlign(TA_LEFT);

	myFont.CreatePointFont(m_nPrintFontSize, m_czPrintFont, pDC);
	pBakFont = pDC->SelectObject(&myFont);

	//////////////////////////////////////////////////////////////////////////////////////////////////
	DrawLimitLine(pDC->m_hDC);
	if (DEVGDI_WAVE_AUTOADJUST==m_nRateSizeX)
	{
		DrawLineAdjust(pDC->m_hDC, pdData, nDataLen, pdData2, nDataLen2, pdData3, nDataLen3, pdData4, nDataLen4, pdData5, nDataLen5, pdData6, nDataLen6, pdData7, nDataLen7, pdData8,
			nDataLen8, pdData9, nDataLen9, pdData10, nDataLen10, pdData11, nDataLen11, pdData12, nDataLen12, pdData13, nDataLen13, pdData14, nDataLen14, pdData15, nDataLen15, pdData16,
			nDataLen16, pdData17, nDataLen17, pdData18, nDataLen18, pdData19, nDataLen19, pdData20, nDataLen20);
	}
	else
	{
		DrawLineSpecialLen(pDC->m_hDC, pdData, nDataLen, pdData2, nDataLen2, pdData3, nDataLen3);
	}

	if (m_ucGridType==DEV_GRID_CLASSICAL)
	{
		DrawGrid(pDC->m_hDC);
	}
	else
	{
		DrawGridSpectrum(pDC->m_hDC);
	}

	if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
	{
		FindMaxWaveVal(pdData, nDataLen, i);
	}

	for (i=0; i<I_MKR_NUMBER; i++)
	{
		if (m_bMkr[i])
		{
			if (nDataLen>0)
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData, nDataLen, i);
				}
				DrawMkr(pDC->m_hDC, pdData, nDataLen, i, 0);
			}
			if (nDataLen2>0)
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData2, nDataLen2, i);
				}
				DrawMkr(pDC->m_hDC, pdData2, nDataLen2, i, 1);
			}
		}
	}
	DrawXText(pDC->m_hDC);
	DrawYText(pDC->m_hDC);
	DrawMultiText(pDC->m_hDC);
	ShowManualText(pDC->m_hDC);

	if (m_bEnalbeScrollBar)
	{
		if (nDataLen==0)
		{
			//			DrawScrollBar(pDC->m_hDC, nDataLen2);
		}
		else
		{
			//			DrawScrollBar(pDC->m_hDC, nDataLen);
		}
	}
	if (m_MouseLine.nLButtonDown==DEVGDI_MOUSELINE_DRAW)
	{
		//		DrawMouseRect(pDC->m_hDC);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////

	pDC->SelectObject(pBakFont);
	myFont.DeleteObject();
	DrawReportText(pDC, pInfo);

	return true;
}

// 显示一帧画面, iData -- 数据曲线, iDataLen -- 扫描点数
bool CDevGDI::GDI_Draw(const double *pdData, const int &iDataLen, const double *pdData2/* = NULL*/, const int nDataLen2/* = 0*/,
	const double *pdData3 /*= NULL*/, const int &nDataLen3 /*= 0*/, const double *pdData4 /*= NULL*/, const int &nDataLen4 /*= 0*/,
	const double *pdData5 /*= NULL*/, const int &nDataLen5 /*= 0*/, const double *pdData6 /*= NULL*/, const int &nDataLen6 /*= 0*/,
	const double *pdData7 /*= NULL*/, const int &nDataLen7 /*= 0*/, const double *pdData8 /*= NULL*/, const int &nDataLen8 /*= 0*/,
	const double *pdData9 /*= NULL*/, const int &nDataLen9 /*= 0*/, const double *pdData10 /*= NULL*/, const int &nDataLen10 /*= 0*/,
	const double *pdData11 /*= NULL*/, const int &nDataLen11 /*= 0*/, const double *pdData12 /*= NULL*/, const int &nDataLen12 /*= 0*/,
	const double *pdData13 /*= NULL*/, const int &nDataLen13 /*= 0*/, const double *pdData14 /*= NULL*/, const int &nDataLen14 /*= 0*/,
	const double *pdData15 /*= NULL*/, const int &nDataLen15 /*= 0*/, const double *pdData16 /*= NULL*/, const int &nDataLen16 /*= 0*/,
	const double *pdData17 /*= NULL*/, const int &nDataLen17 /*= 0*/, const double *pdData18 /*= NULL*/, const int &nDataLen18 /*= 0*/,
	const double *pdData19 /*= NULL*/, const int &nDataLen19 /*= 0*/, const double *pdData20 /*= NULL*/, const int &nDataLen20 /*= 0*/)
{
	CFont myFont;
	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right,
		m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, m_brCross);// 备份当前画刷
	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);
	myFont.CreatePointFont(m_nTextFontSize, m_czTextFont);
	SelectObject(memDC, myFont);

	if (m_ucGridType==DEV_GRID_CLASSICAL)
	{
		DrawGrid(memDC);
	}
	else
	{
		DrawGridSpectrum(memDC);
	}
	DrawCoor( memDC );
	DrawGridCenterRound(memDC);
	DrawGridCenterPoint(memDC);
	DrawLimitLine(memDC);

	if (DEVGDI_WAVE_AUTOADJUST==m_nRateSizeX)
	{
		DrawLineAdjust(memDC, pdData, iDataLen, pdData2, nDataLen2, pdData3, nDataLen3, pdData4,
			nDataLen4, pdData5, nDataLen5, pdData6, nDataLen6, pdData7, nDataLen7, pdData8, nDataLen8,
			pdData9, nDataLen9, pdData10, nDataLen10, pdData11, nDataLen11, pdData12, nDataLen12, pdData13, nDataLen13, pdData14,
			nDataLen14, pdData15, nDataLen15, pdData16, nDataLen16, pdData17, nDataLen17, pdData18, nDataLen18, pdData19, nDataLen19,
			pdData20, nDataLen20);
	}
	else
	{
		DrawLineSpecialLen(memDC, pdData, iDataLen, pdData2, nDataLen2, pdData3, nDataLen3);
	}
	// 绘制mkr
	MkrFunc(memDC, pdData, iDataLen, pdData2, nDataLen2, pdData3, nDataLen3, pdData4, nDataLen4, pdData5, nDataLen5, pdData6, nDataLen6, pdData7,
		nDataLen7, pdData8, nDataLen8, pdData9, nDataLen9, pdData10, nDataLen10, pdData11, nDataLen11, pdData12, nDataLen12, pdData13, nDataLen13,
		pdData14, nDataLen14, pdData15, nDataLen15, pdData16, nDataLen16, pdData17, nDataLen17, pdData18, nDataLen18, pdData19, nDataLen19, pdData20,
		nDataLen20);
	DrawXText(memDC);	// 显示横坐标值
	DrawYText(memDC);	// 显示纵坐标值

	if (iDataLen==0)
	{
		DrawScrollBar(memDC, nDataLen2);
	}
	else
	{
		DrawScrollBar(memDC, iDataLen);
	}
	if (m_MouseLine.nLButtonDown==DEVGDI_MOUSELINE_DRAW)
	{
		DrawMouseRect(memDC);
	}
	ShowManualText(memDC);
	DrawMultiText(memDC);

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, memDC, m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(mybitmap);
	DeleteDC(memDC);
	myFont.DeleteObject();

	return true;
}

// 绘制表格函数
bool CDevGDI::DrawGrid(const HDC &memDC)
{
	int i = 0;
	double dPosX = 0.0;
	double dPosY = 0.0;

	// 当前画笔设备 -- Grid
	LOGBRUSH myLogBrush;
	HPEN hPen = CreatePen(PS_SOLID, m_iGridBorderWidth, m_GridColor);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
	myLogBrush.lbHatch = HS_CROSS;
	myLogBrush.lbStyle = BS_HOLLOW;
	myLogBrush.lbColor = m_GridColor;
	HBRUSH myBrush = CreateBrushIndirect(&myLogBrush);
	hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备

	// 绘制删格外边框
	Rectangle(memDC, m_rect.left+m_iBorderGridLeft, m_rect.top+m_iBorderGridTop,
		m_rect.right-m_iBorderGridRight, m_rect.bottom-m_iBorderGridBottom);

	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);
	DeleteObject(myBrush);

	if (m_bGrid)
	{
		// 当前画笔设备 -- Grid
		hPen = CreatePen(PS_DOT, m_iGridLineWidth, m_GridColor);
		hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

		dPosY = (double)(m_rect.bottom-m_rect.top-m_iBorderGridTop-m_iBorderGridBottom)/m_GridNum.nYNum;
		// draw grid here 纵向上半部分
		for (i=1; i<m_GridNum.nYNum*0.5; i++)
		{
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+1, m_rect.top+m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight-2, m_rect.top+m_iBorderGridTop+(int)(i*dPosY));
		}
		i++;	//纵向下半部分
		for (; i<m_GridNum.nYNum; i++)
		{
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+1, m_rect.top+m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight-2, m_rect.top+m_iBorderGridTop+(int)(i*dPosY));
		}

		dPosX = (double)(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight)/m_GridNum.nXNum;
		for (i=1; i<m_GridNum.nXNum*0.5; i++)	//横向左半部分删格
		{
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX), m_rect.top+m_iBorderGridTop+1, NULL);
			LineTo(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-2);
		}
		i++;	//横向右半部分删格
		for (; i<m_GridNum.nXNum; i++)
		{
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX), m_rect.top+m_iBorderGridTop+1, NULL);
			LineTo(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-2);
		}

		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);

		hPen = CreatePen(PS_SOLID, m_iGridLineWidth, m_GridColor);
		hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

		// 中央部分删格
		/*		MoveToEx(memDC, m_rect.left+m_iBorderGridLeft, m_iBorderGridTop+(int)(3*dPosY),
		NULL);
		LineTo(memDC, m_rect.right-m_iBorderGridRight,
		m_iBorderGridTop+(int)(3*dPosY));
		MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+(int)(4*dPosX), m_iBorderGridTop,
		NULL);
		LineTo(memDC, m_iBorderGridLeft+(int)(4*dPosX),
		m_rect.bottom-m_iBorderGridBottom);
		*/
		for (i=1; i<m_GridNum.nYNum*5; i++)	//纵向边框刻度上半部分
		{
			//左
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+1,
				m_rect.top+m_iBorderGridTop+(int)(i*dPosY*0.1), NULL);
			LineTo(memDC, m_rect.left+m_iBorderGridLeft+4,
				m_rect.top+m_iBorderGridTop+(int)(i*dPosY*0.1));
			//右
			MoveToEx(memDC, m_rect.right-m_iBorderGridRight-2,
				m_rect.top+m_iBorderGridTop+(int)(i*dPosY*0.1), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight-5,
				m_rect.top+m_iBorderGridTop+(int)(i*dPosY*0.1));
		}
		//		i++;
		for (; i<m_GridNum.nYNum*10; i++)	//纵向边框刻度下半部分
		{
			//左
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+1,
				m_rect.top+m_iBorderGridTop+(int)(i*dPosY*0.1), NULL);
			LineTo(memDC, m_rect.left+m_iBorderGridLeft+4,
				m_rect.top+m_iBorderGridTop+(int)(i*dPosY*0.1));
			//右
			MoveToEx(memDC, m_rect.right-m_iBorderGridRight-2,
				m_rect.top+m_iBorderGridTop+(int)(i*dPosY*0.1), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight-5,
				m_rect.top+m_iBorderGridTop+(int)(i*dPosY*0.1));
		}
		// 中央部分删格刻度----纵向
		for (i=1; i<m_GridNum.nYNum*10; i++)
		{
			MoveToEx(memDC,
				m_rect.left+m_iBorderGridLeft+static_cast<int>((m_rect.right-m_rect.left
				-m_iBorderGridRight-m_iBorderGridLeft)*0.5)-2,
				m_rect.top+m_iBorderGridTop+static_cast<int>(i*dPosY*0.1), NULL);
			LineTo(memDC,
				m_rect.left+m_iBorderGridLeft+static_cast<int>((m_rect.right-m_rect.left
				-m_iBorderGridRight-m_iBorderGridLeft)*0.5)+3,
				m_rect.top+m_iBorderGridTop+static_cast<int>(i*dPosY*0.1));
		}

		dPosX *= 0.1;
		for (i=1; i<m_GridNum.nXNum*5; i++)	//横向边框刻度左半部分
		{
			//上
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.top+m_iBorderGridTop+1, NULL);
			LineTo(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.top+m_iBorderGridTop+4);
			//下
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.bottom-m_iBorderGridBottom-2, NULL);
			LineTo(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.bottom-m_iBorderGridBottom-6);
		}
		//		i++;
		for (; i<m_GridNum.nXNum*10; i++)	//横向边框刻度右半部分
		{
			//上
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.top+m_iBorderGridTop+1, NULL);
			LineTo(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.top+m_iBorderGridTop+4);
			//下
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.bottom-m_iBorderGridBottom-2, NULL);
			LineTo(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.bottom-m_iBorderGridBottom-6);
		}
		// 中央部分删格刻度----横向
		for (i=1; i<m_GridNum.nXNum*10; i++)
		{
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+static_cast<int>(i*dPosX),
				m_rect.top+m_iBorderGridTop+static_cast<int>((m_rect.bottom-m_rect.top
				-m_iBorderGridTop-m_iBorderGridBottom)*0.5)-2, NULL);
			LineTo(memDC, m_rect.left+m_iBorderGridLeft+static_cast<int>(i*dPosX),
				m_rect.top+m_iBorderGridTop+static_cast<int>((m_rect.bottom-m_rect.top
				-m_iBorderGridTop-m_iBorderGridBottom)*0.5)+3);
		}

		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);
	}

	return true;
}

// 设置坐标的数据
bool CDevGDI::GDI_SetCoorData( tagCoorText Data[], int nDataLen )
{
	if ( nDataLen > 20 )
	{
		return false;
	}

	for( int i=0; i<nDataLen; i++ )
	{
		memcpy( &m_CoorData[i], &Data[i], sizeof(tagCoorText) );
	}
	
	return true;
}

// 绘制坐标系 仿8831 wangzheng 2008-09-11
void CDevGDI::DrawCoor( const HDC &memDC )
{
	double dPosY;
	TCHAR szStr[40];	// wangzheng 2008-09-11

	if ( m_bEnableCoorText )
	{
		dPosY = (double)(m_rect.bottom-m_rect.top-m_iBorderGridTop-m_iBorderGridBottom)/m_GridNum.nYNum;
		SetTextColor(memDC, m_GridColor);

		for (int i=1; i<m_GridNum.nYNum; i++)
		{	
			_stprintf( szStr, _T("%.1lf"), m_CoorData[i-1].dData );
			_tcscat(szStr, m_CoorData[i-1].czDepartment);
			TextOut(memDC,m_rect.left+m_iBorderGridLeft, m_rect.top+m_iBorderGridTop+(int)(i*dPosY),
				szStr, _tcslen(szStr) );
		}
	}
}

// 绘制频谱仪的表格函数，仿DS8821
bool CDevGDI::DrawGridSpectrum(const HDC &memDC)
{
	int i = 0;
	double dPosX = 0.0;
	double dPosY = 0.0;

	// 当前画笔设备 -- Grid
	LOGBRUSH myLogBrush;
	HPEN hPen = CreatePen(PS_SOLID, m_iGridBorderWidth, m_GridColor);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
	myLogBrush.lbHatch = HS_CROSS;
	myLogBrush.lbStyle = BS_HOLLOW;
	myLogBrush.lbColor = m_GridColor;
	HBRUSH myBrush = CreateBrushIndirect(&myLogBrush);
	hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备

	// 绘制删格外边框
	Rectangle(memDC, m_rect.left+m_iBorderGridLeft, m_rect.top+m_iBorderGridTop,
		m_rect.right-m_iBorderGridRight, m_rect.bottom-m_iBorderGridBottom);

	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);
	DeleteObject(myBrush);

	if (m_bGrid)
	{
		// 当前画笔设备 -- Grid
		hPen = CreatePen(PS_SOLID, m_iGridLineWidth, m_GridColor);
		hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

		dPosY = (double)(m_rect.bottom-m_rect.top-m_iBorderGridTop-m_iBorderGridBottom)/m_GridNum.nYNum;
		// draw grid here 纵向
		for (i=1; i<m_GridNum.nYNum; i++)
		{
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+1, m_rect.top+m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight-2, m_rect.top+m_iBorderGridTop+(int)(i*dPosY));
		}

		dPosX = (double)(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight)/m_GridNum.nXNum;
		for (i=1; i<m_GridNum.nXNum; i++)	//横向
		{
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX), m_rect.top+m_iBorderGridTop+1, NULL);
			LineTo(memDC, m_rect.left+m_iBorderGridLeft+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-2);
		}

		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);
	}

	return true;
}

// 设置绘制删格开关项
void CDevGDI::GDI_EnableGrid(const bool &bGrid)
{
	m_bGrid = bGrid;
}

// 根据当前波形数据ID计算出当前绘图横坐标值
// dWavePixNum -- 波形绘图区的宽度
// nDataLen -- 曲线总数据量
// nDataID -- 当前曲线的数据id
// return value -- 绘图曲线的横坐标值
int CDevGDI::GetWaveLineX(const double &dWavePixNum, const int &nDataLen,
						  const int &nDataID)
{
	return m_rect.left+m_iBorderGridLeft+static_cast<int>(0.5+nDataID*dWavePixNum/(nDataLen-1));
}

// 根据波形当前横坐标值计算出屏幕横坐标值
inline int CDevGDI::GetWaveLineX(const double &dData)
{
	return m_rect.left+m_iBorderGridLeft+static_cast<int>((dData-m_dStartX)
		*(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight)/(m_dEndX-m_dStartX));
}

// 根据波形当前值计算出屏幕总坐标值
int CDevGDI::GetWaveLineY(const double &dData)
{
	int nYVal = m_rect.bottom-m_iBorderGridBottom-static_cast<int>((dData-m_dStartY)*(m_rect.bottom-m_rect.top
		-m_iBorderGridTop-m_iBorderGridBottom)/(m_dEndY-m_dStartY))-1;

	if (nYVal<m_rect.top+1)
	{
		nYVal = m_rect.top+1;
	}
	else if (nYVal>m_rect.bottom-2)
	{
		nYVal = m_rect.bottom-2;
	}

	return nYVal;
}

// 根据波形纵坐标2值计算出屏幕纵坐标值
int CDevGDI::GetWaveLineYSpecial(const double &dData)
{
	int nYVal = m_rect.bottom-m_iBorderGridBottom-static_cast<int>((dData-m_dSpecialStartY)*(m_rect.bottom-m_rect.top
		-m_iBorderGridTop-m_iBorderGridBottom)/(m_dSpecialEndY-m_dSpecialStartY))-1;

	if (nYVal<m_rect.top+1)
	{
		nYVal = m_rect.top+1;
	}
	else if (nYVal>m_rect.bottom-2)
	{
		nYVal = m_rect.bottom-2;
	}

	return nYVal;
}

// 绘制波形曲线
bool CDevGDI::DrawLineAdjust(const HDC &memDC, const double *pdData, const int &iDataLen, const double *pdData2, const int &nDataLen2, const double *pdData3, const int &nDataLen3,
							 const double *pdData4, const int &nDataLen4, const double *pdData5, const int &nDataLen5, const double *pdData6, const int &nDataLen6, const double *pdData7, const int &nDataLen7,
							 const double *pdData8, const int &nDataLen8, const double *pdData9, const int &nDataLen9, const double *pdData10, const int &nDataLen10, const double *pdData11,
							 const int &nDataLen11, const double *pdData12, const int &nDataLen12, const double *pdData13, const int &nDataLen13, const double *pdData14, const int &nDataLen14,
							 const double *pdData15, const int &nDataLen15, const double *pdData16, const int &nDataLen16, const double *pdData17, const int &nDataLen17, const double *pdData18,
							 const int &nDataLen18, const double *pdData19, const int &nDataLen19, const double *pdData20, const int &nDataLen20)
{
	int i = 0;
	int j = 0;
	int iLineWidth = 1;
	int nXPos = 0;//横坐标曲线点
	int nYPos = 0;//纵坐标曲线点
	int nXPosNext = 0;
	int nSkipPos = 0;
	// 当前画笔设备 -- Line
	HPEN hPen;
	LOGBRUSH myLogBrush[4];
	for (i=0; i<4; i++)
	{
		myLogBrush[i].lbColor = m_LineColor[i];
		myLogBrush[i].lbHatch = HS_CROSS;
		myLogBrush[i].lbStyle = BS_SOLID;
	}
	HBRUSH myBrush = CreateBrushIndirect(&myLogBrush[0]);

	switch (m_iLineWidth[0])
	{
	case I_DRAW_BIG_POINT:
		iLineWidth = 3;
		break;
	case I_MULTICOLOR_HORIZONTAL_LINE:
	case I_HORIZONTAL_LINE:
	case I_HORIZONTAL_BAR:
	case I_SPECAL_RFANDVA:
	case N_HORBAR_LINE:
	case N_HORBAR_NO_SEP:
	case N_HORBAR_NO_SEP_ENABLE_MIN:
		iLineWidth = 1;
		break;
	default:
		iLineWidth = m_iLineWidth[0];
		break;
	}

	hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[0]);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

	m_dWavePixNum = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	if(m_dWavePixNum < 1.0)
	{
		m_dWavePixNum = 1.0;
	}

	/////////////////////////////////////////////////////////////////////////
	switch (m_iLineWidth[0])
	{
	case 0://////////////////////////////////////////////////////////////////
		for (i=0; i<iDataLen; i++)	// 画细点
		{
			nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, i);
			nYPos = GetWaveLineY(pdData[i]);
			SetPixel(memDC, nXPos, nYPos, m_LineColor[0]);
		}

		for (i=0; i<nDataLen2; i++)	// 画细点
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
			nYPos = GetWaveLineY(pdData2[i]);
			SetPixel(memDC, nXPos, nYPos, m_LineColor[1]);
		}

		for (i=0; i<nDataLen3; i++)	// 画细点
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3, i);
			nYPos = GetWaveLineY(pdData3[i]);
			SetPixel(memDC, nXPos, nYPos, m_LineColor[2]);
		}
		break;

	case 1:	//////////////////////////////////////////////////////////////////
	case 3:	// 画细线或粗线
		if (iDataLen>0)
		{
			if (m_uczWaveDockY[0]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, 0);
				nYPos = GetWaveLineY(pdData[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<iDataLen; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, i);
					nYPos = GetWaveLineY(pdData[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, 0);
				nYPos = GetWaveLineYSpecial(pdData[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<iDataLen; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, i);
					nYPos = GetWaveLineYSpecial(pdData[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen2>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[1], m_LineColor[1]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[1]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, 0);
				nYPos = GetWaveLineY(pdData2[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen2; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
					nYPos = GetWaveLineY(pdData2[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, 0);
				nYPos = GetWaveLineYSpecial(pdData2[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen2; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
					nYPos = GetWaveLineYSpecial(pdData2[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen3>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[2], m_LineColor[2]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[2]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3, 0);
				nYPos = GetWaveLineY(pdData3[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen3; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3, i);
					nYPos = GetWaveLineY(pdData3[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3, 0);
				nYPos = GetWaveLineYSpecial(pdData3[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen3; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3, i);
					nYPos = GetWaveLineYSpecial(pdData3[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen4>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[3], m_LineColor[3]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[3]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen4, 0);
				nYPos = GetWaveLineY(pdData4[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen4; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen4, i);
					nYPos = GetWaveLineY(pdData4[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen4, 0);
				nYPos = GetWaveLineYSpecial(pdData4[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen4; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen4, i);
					nYPos = GetWaveLineYSpecial(pdData4[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen5>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[4], m_LineColor[4]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[4]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen5, 0);
				nYPos = GetWaveLineY(pdData5[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen5; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen5, i);
					nYPos = GetWaveLineY(pdData5[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen5, 0);
				nYPos = GetWaveLineYSpecial(pdData5[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen5; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen5, i);
					nYPos = GetWaveLineYSpecial(pdData5[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen6>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[5], m_LineColor[5]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[5]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen6, 0);
				nYPos = GetWaveLineY(pdData6[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen6; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen6, i);
					nYPos = GetWaveLineY(pdData6[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen6, 0);
				nYPos = GetWaveLineYSpecial(pdData6[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen6; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen6, i);
					nYPos = GetWaveLineYSpecial(pdData6[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen7>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[6], m_LineColor[6]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[6]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen7, 0);
				nYPos = GetWaveLineY(pdData7[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen7; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen7, i);
					nYPos = GetWaveLineY(pdData7[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen7, 0);
				nYPos = GetWaveLineYSpecial(pdData7[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen7; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen7, i);
					nYPos = GetWaveLineYSpecial(pdData7[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen8>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[7], m_LineColor[7]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[7]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen8, 0);
				nYPos = GetWaveLineY(pdData8[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen8; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen8, i);
					nYPos = GetWaveLineY(pdData8[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen8, 0);
				nYPos = GetWaveLineYSpecial(pdData8[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen8; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen8, i);
					nYPos = GetWaveLineYSpecial(pdData8[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen9>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[8], m_LineColor[8]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[8]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen9, 0);
				nYPos = GetWaveLineY(pdData9[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen9; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen9, i);
					nYPos = GetWaveLineY(pdData9[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen9, 0);
				nYPos = GetWaveLineYSpecial(pdData9[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen9; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen9, i);
					nYPos = GetWaveLineYSpecial(pdData9[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen10>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[9], m_LineColor[9]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[9]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen10, 0);
				nYPos = GetWaveLineY(pdData10[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen10; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen10, i);
					nYPos = GetWaveLineY(pdData10[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen10, 0);
				nYPos = GetWaveLineYSpecial(pdData10[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen10; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen10, i);
					nYPos = GetWaveLineYSpecial(pdData10[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen11>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[10], m_LineColor[10]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[10]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen11, 0);
				nYPos = GetWaveLineY(pdData11[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen11; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen11, i);
					nYPos = GetWaveLineY(pdData11[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen11, 0);
				nYPos = GetWaveLineYSpecial(pdData11[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen11; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen11, i);
					nYPos = GetWaveLineYSpecial(pdData11[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen12>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[11], m_LineColor[11]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[11]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen12, 0);
				nYPos = GetWaveLineY(pdData12[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen12; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen12, i);
					nYPos = GetWaveLineY(pdData12[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen12, 0);
				nYPos = GetWaveLineYSpecial(pdData12[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen12; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen12, i);
					nYPos = GetWaveLineYSpecial(pdData12[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen13>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[12], m_LineColor[12]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[12]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen13, 0);
				nYPos = GetWaveLineY(pdData13[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen13; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen13, i);
					nYPos = GetWaveLineY(pdData13[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen13, 0);
				nYPos = GetWaveLineYSpecial(pdData13[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen13; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen13, i);
					nYPos = GetWaveLineYSpecial(pdData13[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen14>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[13], m_LineColor[13]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[13]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen14, 0);
				nYPos = GetWaveLineY(pdData14[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen14; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen14, i);
					nYPos = GetWaveLineY(pdData14[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen14, 0);
				nYPos = GetWaveLineYSpecial(pdData14[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen14; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen14, i);
					nYPos = GetWaveLineYSpecial(pdData14[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen15>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[14], m_LineColor[14]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[14]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen15, 0);
				nYPos = GetWaveLineY(pdData15[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen15; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen15, i);
					nYPos = GetWaveLineY(pdData15[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen15, 0);
				nYPos = GetWaveLineYSpecial(pdData15[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen15; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen15, i);
					nYPos = GetWaveLineYSpecial(pdData15[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen16>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[15], m_LineColor[15]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[15]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen16, 0);
				nYPos = GetWaveLineY(pdData16[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen16; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen16, i);
					nYPos = GetWaveLineY(pdData16[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen16, 0);
				nYPos = GetWaveLineYSpecial(pdData16[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen16; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen16, i);
					nYPos = GetWaveLineYSpecial(pdData16[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen17>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[16], m_LineColor[16]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[16]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen17, 0);
				nYPos = GetWaveLineY(pdData17[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen17; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen17, i);
					nYPos = GetWaveLineY(pdData17[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen17, 0);
				nYPos = GetWaveLineYSpecial(pdData17[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen17; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen17, i);
					nYPos = GetWaveLineYSpecial(pdData17[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen18>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[17], m_LineColor[17]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[17]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen18, 0);
				nYPos = GetWaveLineY(pdData18[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen18; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen18, i);
					nYPos = GetWaveLineY(pdData18[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen18, 0);
				nYPos = GetWaveLineYSpecial(pdData18[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen18; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen18, i);
					nYPos = GetWaveLineYSpecial(pdData18[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen19>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[18], m_LineColor[18]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[18]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen19, 0);
				nYPos = GetWaveLineY(pdData19[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen19; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen19, i);
					nYPos = GetWaveLineY(pdData19[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen19, 0);
				nYPos = GetWaveLineYSpecial(pdData19[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen19; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen19, i);
					nYPos = GetWaveLineYSpecial(pdData19[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		if (nDataLen20>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[19], m_LineColor[19]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			if (m_uczWaveDockY[19]==Y_LEFT_COORDINATE_DOCK)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen20, 0);
				nYPos = GetWaveLineY(pdData20[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen20; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen20, i);
					nYPos = GetWaveLineY(pdData20[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
			else
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen20, 0);
				nYPos = GetWaveLineYSpecial(pdData20[0]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				for (i=0; i<nDataLen20; i++)
				{
					nXPos = GetWaveLineX(m_dWavePixNum, nDataLen20, i);
					nYPos = GetWaveLineYSpecial(pdData20[i]);
					LineTo(memDC, nXPos, nYPos);
				}
			}
		}

		break;
	case I_DRAW_BIG_POINT:///////////////////////////////////////////////////
		for (i=0; i<iDataLen; i++)	// 画粗点
		{
			nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, i);
			nYPos = GetWaveLineY(pdData[i]);
			MoveToEx(memDC, nXPos, nYPos, NULL);
			LineTo(memDC, nXPos, nYPos);
		}

		if (nDataLen2>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[1]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen2; i++)	// 画粗点
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
				nYPos = GetWaveLineY(pdData2[i]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}

		if (nDataLen3>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[2]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen3; i++)	// 画粗点
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3, i);
				nYPos = GetWaveLineY(pdData3[i]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}

		if (nDataLen4>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[3]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen4; i++)	// 画粗点
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen4, i);
				nYPos = GetWaveLineY(pdData4[i]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}

		if (nDataLen5>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[4]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen5; i++)	// 画粗点
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen5, i);
				nYPos = GetWaveLineY(pdData5[i]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}

		if (nDataLen6>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[5]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen6; i++)	// 画粗点
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen6, i);
				nYPos = GetWaveLineY(pdData6[i]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}

		if (nDataLen7>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[6]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen7; i++)	// 画粗点
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen7, i);
				nYPos = GetWaveLineY(pdData7[i]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}

		if (nDataLen8>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[7]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen8; i++)	// 画粗点
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen8, i);
				nYPos = GetWaveLineY(pdData8[i]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}

		if (nDataLen9>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[8]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen9; i++)	// 画粗点
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen9, i);
				nYPos = GetWaveLineY(pdData9[i]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}

		if (nDataLen10>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[9]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen10; i++)	// 画粗点
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen10, i);
				nYPos = GetWaveLineY(pdData10[i]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}
		break;

	case I_MULTICOLOR_HORIZONTAL_LINE:
		for (i=0; i<iDataLen; i++)	// 画竖线
		{
			nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, i);
			nYPos = GetWaveLineY(pdData[i]);
			MoveToEx(memDC, nXPos, m_rect.bottom-m_iBorderGridBottom-1, NULL);
			LineTo(memDC, nXPos, nYPos);

			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			if (i%2==0)
			{
				hPen = CreatePen(PS_SOLID, m_iLineWidth[1], m_LineColor[1]);
			}
			else
			{
				hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[0]);
			}
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
		}
		break;

	case I_HORIZONTAL_LINE://////////////////////////////////////////////////
		if (iDataLen>0)
		{
			for (i=0; i<iDataLen; i++)	// 画竖线
			{
				nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, i);
				nYPos = GetWaveLineY(pdData[i]);
				MoveToEx(memDC, nXPos, m_rect.bottom-m_iBorderGridBottom-1, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}

		if (nDataLen2>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[1]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen2; i++)	// 画竖线
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
				nYPos = GetWaveLineY(pdData2[i]);
				MoveToEx(memDC, nXPos, m_rect.bottom-m_iBorderGridBottom-1, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}
		break;

	case N_HORBAR_LINE:
		hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
		i = 0;
		nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, i);
		nXPosNext = GetWaveLineX(m_dWavePixNum, iDataLen, i+1);
		nYPos = GetWaveLineY(pdData[i]);
		nSkipPos = static_cast<int>((nXPosNext-nXPos)*0.1);
		if (nSkipPos<1)
		{
			nSkipPos = 1;
		}
		Rectangle(memDC, nXPos+nSkipPos, m_rect.bottom-m_iBorderGridBottom-1,
			nXPosNext-nSkipPos, nYPos);
		for (i=1; i<iDataLen; i++)
		{
			nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, i);
			nXPosNext = GetWaveLineX(m_dWavePixNum, iDataLen, i+1);
			nYPos = GetWaveLineY(pdData[i]);
			Rectangle(memDC, nXPos+nSkipPos, m_rect.bottom-m_iBorderGridBottom-1,
				nXPosNext-nSkipPos, nYPos);
		}

		if (nDataLen2>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[1], m_LineColor[1]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			i = 0;
			nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, i);
			nYPos = GetWaveLineY(pdData2[i]);
			MoveToEx(memDC, nXPos, nYPos, NULL);
			for (i=1; i<nDataLen2; i++)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
				nYPos = GetWaveLineY(pdData2[i]);
				LineTo(memDC, nXPos, nYPos);
			}
		}
		break;

	case N_HORBAR_NO_SEP:
		hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
		if (iDataLen>0)
		{
			for (i=0; i<iDataLen; i++)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, i);
				nXPosNext = GetWaveLineX(m_dWavePixNum, iDataLen, i+1);
				if (nXPosNext<=nXPos)
				{
					nXPosNext = nXPos+1;
				}
				nYPos = GetWaveLineY(pdData[i]);
				if (nYPos==m_rect.bottom-m_iBorderGridBottom-2)
				{
					if (nXPosNext==nXPos+1)
					{
						SetPixel(memDC, nXPos, nYPos, m_LineColor[0]);	// 补偿竖线宽度为1是的绘图误差
					}
				}
				Rectangle(memDC, nXPos, nYPos, nXPosNext, m_rect.bottom-m_iBorderGridBottom-1);
			}
		}

		if (nDataLen2>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(myBrush);
			DeleteObject(hPen);
			myBrush = CreateBrushIndirect(&myLogBrush[1]);
			hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
			hPen = CreatePen(PS_SOLID, m_iLineWidth[1], m_LineColor[1]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen2; i++)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
				nXPosNext = GetWaveLineX(m_dWavePixNum, nDataLen2, i+1);
				if (nXPosNext<=nXPos)
				{
					nXPosNext = nXPos+1;
				}
				nYPos = GetWaveLineY(pdData2[i]);
				if (nYPos==m_rect.bottom-m_iBorderGridBottom-2)
				{
					if (nXPosNext==nXPos+1)
					{
						SetPixel(memDC, nXPos, nYPos, m_LineColor[1]);	// 补偿竖线宽度为1是的绘图误差
					}
				}
				Rectangle(memDC, nXPos, nYPos, nXPosNext, m_rect.bottom-m_iBorderGridBottom-1);
			}
		}

		if (nDataLen3>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(myBrush);
			DeleteObject(hPen);
			myBrush = CreateBrushIndirect(&myLogBrush[2]);
			hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
			hPen = CreatePen(PS_SOLID, m_iLineWidth[2], m_LineColor[2]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen3; i++)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3, i);
				nXPosNext = GetWaveLineX(m_dWavePixNum, nDataLen3, i+1);
				if (nXPosNext<=nXPos)
				{
					nXPosNext = nXPos+1;
				}
				nYPos = GetWaveLineY(pdData3[i]);
				if (nYPos==m_rect.bottom-m_iBorderGridBottom-2)
				{
					if (nXPosNext==nXPos+1)
					{
						SetPixel(memDC, nXPos, nYPos, m_LineColor[2]);	// 补偿竖线宽度为1是的绘图误差
					}
				}
				Rectangle(memDC, nXPos, nYPos, nXPosNext, m_rect.bottom-m_iBorderGridBottom-1);
			}
		}
		break;

	case N_HORBAR_NO_SEP_ENABLE_MIN:
		hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
		if (iDataLen>0)
		{
			for (i=0; i<iDataLen; i++)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, i);
				nXPosNext = GetWaveLineX(m_dWavePixNum, iDataLen, i+1);
				if (nXPosNext<=nXPos)
				{
					nXPosNext = nXPos+1;
				}
				nYPos = GetWaveLineY(pdData[i]);
				if (nYPos>=m_rect.bottom-m_iBorderGridBottom-1)
				{
					nYPos --;
				}
				if (nXPosNext==nXPos+1)
				{
					SetPixel(memDC, nXPos, nYPos, m_LineColor[0]);	// 补偿竖线宽度为1是的绘图误差
				}
				Rectangle(memDC, nXPos, nYPos, nXPosNext, m_rect.bottom-m_iBorderGridBottom-1);
			}
		}

		if (nDataLen2>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(myBrush);
			DeleteObject(hPen);
			myBrush = CreateBrushIndirect(&myLogBrush[1]);
			hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
			hPen = CreatePen(PS_SOLID, m_iLineWidth[1], m_LineColor[1]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen2; i++)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
				nXPosNext = GetWaveLineX(m_dWavePixNum, nDataLen2, i+1);
				if (nXPosNext<=nXPos)
				{
					nXPosNext = nXPos+1;
				}
				nYPos = GetWaveLineY(pdData2[i]);
				if (nYPos>=m_rect.bottom-m_iBorderGridBottom-1)
				{
					nYPos --;
				}
				if (nXPosNext==nXPos+1)
				{
					SetPixel(memDC, nXPos, nYPos, m_LineColor[1]);	// 补偿竖线宽度为1是的绘图误差
				}
				Rectangle(memDC, nXPos, nYPos, nXPosNext, m_rect.bottom-m_iBorderGridBottom-1);
			}
		}

		if (nDataLen3>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(myBrush);
			DeleteObject(hPen);
			myBrush = CreateBrushIndirect(&myLogBrush[2]);
			hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
			hPen = CreatePen(PS_SOLID, m_iLineWidth[2], m_LineColor[2]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen3; i++)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3, i);
				nXPosNext = GetWaveLineX(m_dWavePixNum, nDataLen3, i+1);
				if (nXPosNext<=nXPos)
				{
					nXPosNext = nXPos+1;
				}
				nYPos = GetWaveLineY(pdData3[i]);
				if (nYPos>=m_rect.bottom-m_iBorderGridBottom-1)
				{
					nYPos --;
				}
				if (nXPosNext==nXPos+1)
				{
					SetPixel(memDC, nXPos, nYPos, m_LineColor[2]);	// 补偿竖线宽度为1是的绘图误差
				}
				Rectangle(memDC, nXPos, nYPos, nXPosNext, m_rect.bottom-m_iBorderGridBottom-1);
			}
		}
		break;

	case I_SPECAL_RFANDVA:///////////////////////////////////////////////////
		for (j=0; j<4; j++)
		{
			hOldPen = (HPEN)SelectObject(memDC, hPen);// 备份当前画笔设备
			hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
			if (j==2)
			{
				continue;
			}
			for (i=j; i<iDataLen; i+=6)	// 画竖条
			{
				nXPos = GetWaveLineX(m_dWavePixNum, iDataLen, i);
				nYPos = GetWaveLineY(pdData[i]);
				Rectangle(memDC, nXPos, m_rect.bottom-m_iBorderGridBottom-1,
					GetWaveLineX(m_dWavePixNum, iDataLen, i+1), nYPos);
			}
			DeleteObject(myBrush);
			DeleteObject(hPen);
			myBrush = CreateBrushIndirect(&myLogBrush[j+1]);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[j+1]);
		}
		break;

	case I_HORIZONTAL_BAR:
		hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
		i = 0;
		nXPos = GetWaveLineX(m_dWavePixNum, iDataLen+1, i);
		nXPosNext = GetWaveLineX(m_dWavePixNum, iDataLen+1, i+1);
		nYPos = GetWaveLineY(pdData[i]);
		nSkipPos = static_cast<int>((nXPosNext-nXPos)*0.1);
		if (nSkipPos<1)
		{
			nSkipPos = 1;
		}
		Rectangle(memDC, nXPos+nSkipPos, m_rect.bottom-m_iBorderGridBottom-1,
			nXPosNext-nSkipPos, nYPos);
		for (i=1; i<iDataLen; i++)
		{
			nXPos = GetWaveLineX(m_dWavePixNum, iDataLen+1, i);
			nXPosNext = GetWaveLineX(m_dWavePixNum, iDataLen+1, i+1);
			nYPos = GetWaveLineY(pdData[i]);
			Rectangle(memDC, nXPos+nSkipPos, m_rect.bottom-m_iBorderGridBottom-1,
				nXPosNext-nSkipPos, nYPos);
		}

		if (nDataLen2>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(myBrush);
			DeleteObject(hPen);
			myBrush = CreateBrushIndirect(&myLogBrush[1]);
			hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
			hPen = CreatePen(PS_SOLID, m_iLineWidth[1], m_LineColor[1]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			i = 0;
			nXPos = GetWaveLineX(m_dWavePixNum, iDataLen+1, i);
			nXPosNext = GetWaveLineX(m_dWavePixNum, iDataLen+1, i+1);
			nYPos = GetWaveLineY(pdData2[i]);
			nSkipPos = static_cast<int>((nXPosNext-nXPos)*0.1);
			if (nSkipPos<1)
			{
				nSkipPos = 1;
			}
			Rectangle(memDC, nXPos+nSkipPos, m_rect.bottom-m_iBorderGridBottom-1,
				nXPosNext-nSkipPos, nYPos);
			for (i=1; i<nDataLen2; i++)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2+1, i);
				nXPosNext = GetWaveLineX(m_dWavePixNum, nDataLen2+1, i+1);
				nYPos = GetWaveLineY(pdData2[i]);
				Rectangle(memDC, nXPos+nSkipPos, nYPos,
					nXPosNext-nSkipPos, m_rect.bottom-m_iBorderGridBottom-1);
			}
		}

		if (nDataLen3>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(myBrush);
			DeleteObject(hPen);
			myBrush = CreateBrushIndirect(&myLogBrush[2]);
			hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
			hPen = CreatePen(PS_SOLID, m_iLineWidth[2], m_LineColor[2]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			i = 0;
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3+1, i);
			nXPosNext = GetWaveLineX(m_dWavePixNum, nDataLen3+1, i+1);
			nYPos = GetWaveLineY(pdData3[i]);
			nSkipPos = static_cast<int>((nXPosNext-nXPos)*0.1);
			if (nSkipPos<1)
			{
				nSkipPos = 1;
			}
			Rectangle(memDC, nXPos+nSkipPos, m_rect.bottom-m_iBorderGridBottom-1,
				nXPosNext-nSkipPos, nYPos);
			for (i=1; i<nDataLen3; i++)
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3+1, i);
				nXPosNext = GetWaveLineX(m_dWavePixNum, nDataLen3+1, i+1);
				nYPos = GetWaveLineY(pdData3[i]);
				Rectangle(memDC, nXPos+nSkipPos, nYPos,
					nXPosNext-nSkipPos, m_rect.bottom-m_iBorderGridBottom-1);
			}
		}
		break;

	default://///////////////////////////////////////////////////////////////
		break;
	}////////////////////////////////////////////////////////////////////////

	DeleteObject(myBrush);
	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);

	return true;
}

// 读取最大扫宽范围, iStart -- 起始值, iEnd -- 中止值
void CDevGDI::GDI_GetXFullSizeSpan(double &dStart, double &dEnd)
{
	dStart = m_dFullStartX;
	dEnd = m_dFullEndX;
}

// 设置最大扫宽范围, iStart -- 起始值, iEnd -- 中止值
void CDevGDI::GDI_SetXFullSizeSpan(const double &dStart, const double &dEnd, const int &nDataLen /*= 0*/)
{
	int i = 0;
	double dTemp[I_MKR_NUMBER];

	if ((m_bMkrAutoKeepX)&&(nDataLen>0))
	{
		for (i=0; i<I_MKR_NUMBER; i++)
		{
			//尔洪春 同前，减去开始点2009/9月
			dTemp[i] = static_cast<double>(m_iMkrValue[i]-m_nWaveStartPos)/nDataLen*(m_dFullEndX-m_dFullStartX)+m_dFullStartX;
		}
	}

	m_dFullStartX = dStart;
	m_dFullEndX = dEnd;

	if ((m_bMkrAutoKeepX)&&(nDataLen>0))
	{
		for (i=0; i<I_MKR_NUMBER; i++)
		{
			GDI_SetMkrX(i, dTemp[i], nDataLen);
		}
	}
}

// 读取扫宽范围, iStart -- 起始值, iEnd -- 中止值
void CDevGDI::GDI_GetSpan(double &dStart, double &dEnd)
{
	dStart = m_dStartX;
	dEnd = m_dEndX;
}

// 设置扫宽范围, iStart -- 起始值, iEnd -- 中止值
void CDevGDI::GDI_SetSpan(const double &dStart, const double &dEnd, const int &nDataLen /*= 0*/)
{
	int i = 0;
	double dTemp[I_MKR_NUMBER];

	if ((m_bMkrAutoKeepX)&&(nDataLen>0))
	{
		for (i=0; i<I_MKR_NUMBER; i++)
		{
			//尔洪春 同前，减去开始点2009/9月
			dTemp[i] = static_cast<double>(m_iMkrValue[i]-m_nWaveStartPos)/nDataLen*(m_dEndX-m_dStartX)+m_dStartX;
		}
	}

	m_dStartX = dStart;
	m_dEndX = dEnd;

	if ((m_bMkrAutoKeepX)&&(nDataLen>0))
	{
		for (i=0; i<I_MKR_NUMBER; i++)
		{
			GDI_SetMkrX(i, dTemp[i], nDataLen);
		}
	}
}

// 设置X轴坐标单位
void CDevGDI::GDI_SetXDepartment(const TCHAR* szDepart)
{
	_tcscpy(m_szXDepartment, _T(" "));
	_tcscat(m_szXDepartment, szDepart);
}

// 读取X轴坐标单位
void CDevGDI::GDI_GetXDepartment(TCHAR* szDepart)
{
	_tcscpy(szDepart, m_szXDepartment);
}

// 设置Y轴坐标单位
void CDevGDI::GDI_SetYDepartment(const TCHAR* szDepart)
{
	int i = 0;

	_tcscpy(m_szYDepartment, _T(" "));
	_tcscat(m_szYDepartment, szDepart);
	for (i=0; i<I_MKR_NUMBER; i++)
	{
		_tcscpy(m_szMkrDepart[i], m_szYDepartment);
	}
}

// 读取Y轴坐标单位
void CDevGDI::GDI_GetYDepartment(TCHAR* szDepart)
{
	_tcscpy(szDepart, m_szYDepartment);
}

// 设置Y轴第二坐标单位
void CDevGDI::GDI_SetYDep2ndY(const TCHAR* szDepart)
{
	int i = 0;

	_tcscpy(m_szYDep2nd, _T(" "));
	_tcscat(m_szYDep2nd, szDepart);
	for (; i<I_MKR_NUMBER; i++)
	{
		_tcscpy(m_szMkrDep2nd[i], m_szYDep2nd);
	}
}

// 读取Y轴第二坐标单位
void CDevGDI::GDI_GetYDep2ndY(TCHAR* szDepart)
{
	_tcscpy(szDepart, m_szYDep2nd);
}

// 数值显示
// memDC -- 内存设备DC
// iVal -- 被显示的数值
// szDepartment -- 显示单位字符串
// iXLocation -- 显示位置横坐标
// iYLocation -- 显示位置纵坐标
// iDir -- 显示对齐位, 0左对齐, 1右对齐, 2中间对齐
void CDevGDI::ShowText(const HDC &memDC, const double &dVal,
					   const TCHAR *szDepartment, const int &iXLocation, const int &iYLocation,
					   const char &iDir)
{
	TCHAR szStr[40];
	int iXLo = iXLocation;
	SIZE size;

	if (abs(static_cast<int>(dVal))<fabs(dVal))
	{
		_stprintf(szStr, m_czViewPrecision, dVal);
	}
	else
	{
		_itot(static_cast<int>(dVal), szStr, 10);
	}
	_tcscat(szStr, szDepartment);
	int iLen = static_cast<int>(_tcslen(szStr));

	GetTextExtentPoint32(memDC, szStr, iLen, &size);
	switch (iDir)
	{
	case 1:
		iXLo -= size.cx;
		break;
	case 2:
		iXLo -= static_cast<int>(size.cx*0.5);
		break;
	default:
		break;
	}

	TextOut(memDC, iXLo, iYLocation, szStr, iLen);
}

// 绘制起始、中止频率值，文本输出
void CDevGDI::DrawXText(const HDC &memDC)
{
	if (m_bEnableXText)
	{
		int nStartXLocation = m_rect.left+m_iBorderGridLeft;
		int nMidXLocation = m_rect.left+m_iBorderGridLeft+static_cast<int>((m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight)
			*0.5);
		int nYLocation = m_rect.bottom-m_iBorderGridBottom+m_nXTextOffsetY;
		SIZE size;

		if (m_bEnableManualXText)
		{
			TextOut(memDC, nStartXLocation, nYLocation, m_szXStart, _tcslen(m_szXStart));
			GetTextExtentPoint32(memDC, m_szXCenter, _tcslen(m_szXCenter), &size);
			TextOut(memDC, nMidXLocation-static_cast<int>(size.cx*0.5), nYLocation, m_szXCenter, _tcslen(m_szXCenter));
			GetTextExtentPoint32(memDC, m_szXEnd, _tcslen(m_szXEnd), &size);
			TextOut(memDC, m_rect.right-m_rect.left-m_iBorderGridRight-size.cx, nYLocation, m_szXEnd, _tcslen(m_szXEnd));
		}
		else
		{
			//Show start freq
			ShowText(memDC, m_dStartX, m_szXDepartment, nStartXLocation, nYLocation, 0);
			//Show time
			ShowText(memDC, (m_dStartX+m_dEndX)/2, m_szXDepartment, nMidXLocation,
				nYLocation, 2);
			//Show stop freq
			ShowText(memDC, m_dEndX, m_szXDepartment, m_rect.right-m_iBorderGridRight, nYLocation, 1);
		}
	}
}

// 绘图起始、中止V/db值
void CDevGDI::DrawYText(const HDC &memDC)
{
	int nXLocation = m_rect.left+m_iBorderGridLeft+m_nYTextOffsetX-1;
	int nYLocation = m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop;
	int i = 0;
	int nNum = m_GridNum.nYNum+1;
	SIZE size;

	if (m_bEnableYText)
	{
		if (m_bEnableManualYText)
		{
			if (nNum>m_szzYCurrent.GetSize())
			{
				nNum = static_cast<int>(m_szzYCurrent.GetSize());
			}
			for (; i<nNum; i++)
			{
				GetTextExtentPoint32(memDC, m_szzYCurrent.GetAt(i), m_szzYCurrent.GetAt(i).GetLength(), &size);
				TextOut(memDC, m_rect.left+nXLocation-size.cx,
					m_rect.top+m_iBorderGridTop-DEFAULT_BORDER_GRID_TOP+static_cast<int>(nYLocation*(nNum-1-i)/m_GridNum.nYNum+size.cy*0.5),
					m_szzYCurrent.GetAt(i), m_szzYCurrent.GetAt(i).GetLength());
			}
		}
		else
		{
			GetTextExtentPoint32(memDC, _T("A"), _tcslen(_T("A")), &size);
			ShowText(memDC, m_dStartY+(m_dEndY-m_dStartY)*i/m_GridNum.nYNum, m_szYDepartment,
				nXLocation, m_rect.top+m_iBorderGridTop-DEFAULT_BORDER_GRID_TOP+nYLocation*(nNum-1-i)/m_GridNum.nYNum, 1);
			for (i=1; i<nNum; i++)
			{
				ShowText(memDC, m_dStartY+(m_dEndY-m_dStartY)*i/m_GridNum.nYNum, m_szYDepartment,
					nXLocation, m_rect.top+m_iBorderGridTop-DEFAULT_BORDER_GRID_TOP+nYLocation*(nNum-1-i)/m_GridNum.nYNum+static_cast<int>(size.cy*0.5), 1);
			}
		}
	}

	if (m_bEnable2ndY)
	{
		i = 0;
		nXLocation = m_rect.right-m_iBorderGridRight+1;
		GetTextExtentPoint32(memDC, _T("A"), _tcslen(_T("A")), &size);
		ShowText(memDC, m_dSpecialStartY+(m_dSpecialEndY-m_dSpecialStartY)*i/m_GridNum.nYNum, m_szYDep2nd,
			nXLocation, m_rect.top+m_iBorderGridTop-DEFAULT_BORDER_GRID_TOP+nYLocation*(nNum-1-i)/m_GridNum.nYNum, 0);
		for (i=1; i<nNum; i++)
		{
			ShowText(memDC, m_dSpecialStartY+(m_dSpecialEndY-m_dSpecialStartY)*i/m_GridNum.nYNum, m_szYDep2nd,
				nXLocation, m_rect.top+m_iBorderGridTop-DEFAULT_BORDER_GRID_TOP+nYLocation*(nNum-1-i)/m_GridNum.nYNum+static_cast<int>(size.cy*0.5), 0);
		}
	}
}

// 设置Y轴起始，终止值
void CDevGDI::GDI_SetSpanY(const double &dStart, const double &dEnd)
{
	m_dStartY = dStart;
	m_dEndY = dEnd;
}

// 设置显示频标纵坐标, true显示 false不显示
void CDevGDI::GDI_EnableMkrYDepartment(const bool &bDepartment)
{
	m_bEnableMkrDepartment = bDepartment;
}

// 设置mkr保持在波形上的横向位置位置，分为左侧和居中两种状态
// nType -- mkr的横向位置特征，相见枚举DEV_MKR_STYLE
bool CDevGDI::GDI_SetMkrXKeep(const int &nType)
{
	if ((nType<DEV_MKR_KEEP_LEFT)&&(nType>DEV_MKR_KEEP_CENTER))
	{
		return false;
	}
	m_nMkrXKeepType = nType;

	return true;
}

// 绘制Mkr
void CDevGDI::DrawMkr(const HDC &memDC, const double *pdData, const int &iDataLen, const int &iMkrID, const int &nWaveID)
{
	assert((iMkrID>-1)&&(iMkrID<I_MKR_NUMBER));
	assert((nWaveID>-1)&&(nWaveID<I_WAVE_NUM));

	HPEN hPen = CreatePen(PS_SOLID, 2, m_mkrColor[iMkrID][nWaveID]);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
	double dLength = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	double dMkrVal = 0.0;
	double dMkrXVal = 0.0;
	int iYValue = 0;
	int iXVal = 0;
	TCHAR szMkrVal[100];
	TCHAR czMkrXVal[100];
	SIZE size;

	SetTextColor(memDC, m_MkrTextColor[iMkrID][nWaveID]);	// 设置mkr文字的颜色

	if (m_nRateSizeX==DEVGDI_WAVE_AUTOADJUST)	// 判断绘制mkr的横纵坐标
	{
		if (m_uczWaveDockY[nWaveID]==Y_LEFT_COORDINATE_DOCK)
		{
			iYValue = static_cast<int>(m_rect.bottom-m_iBorderGridBottom-(pdData[m_iMkrValue[iMkrID]]-m_dStartY)*(m_rect.bottom-m_rect.top
				-m_iBorderGridTop-m_iBorderGridBottom)/(m_dEndY-m_dStartY))-1;
		}
		else
		{
			iYValue = static_cast<int>(m_rect.bottom-m_iBorderGridBottom-(pdData[m_iMkrValue[iMkrID]]-m_dSpecialStartY)*(m_rect.bottom-m_rect.top
				-m_iBorderGridTop-m_iBorderGridBottom)/(m_dSpecialEndY-m_dSpecialStartY))-1;
		}
		switch (m_iLineWidth[0])
		{
		case I_HORIZONTAL_BAR:
			iXVal = m_rect.left+m_iBorderGridLeft+static_cast<int>((m_iMkrValue[iMkrID]-m_nWaveStartPos)*dLength/(iDataLen));
			break;
		default:
			//尔洪春 同前，减去开始点2009/9月
			iXVal = m_rect.left+m_iBorderGridLeft+static_cast<int>((m_iMkrValue[iMkrID]-m_nWaveStartPos)*dLength/(iDataLen-1));
			break;
		}
	}
	else
	{
		iYValue = GetWaveLineY(pdData[m_iMkrValue[iMkrID]+m_nWaveStartPos]);
		iXVal = m_rect.left+m_iBorderGridLeft+static_cast<int>(m_iMkrValue[iMkrID]*m_nRateSizeX*0.01);
		dMkrVal = pdData[m_iMkrValue[iMkrID]+m_nWaveStartPos];
	}
	if (m_nMkrXKeepType==DEV_MKR_KEEP_CENTER)	// mkr横向停靠波形中间
	{
		iXVal += static_cast<int>(dLength/iDataLen*0.5);
	}

	if (m_bEnableMkrLine)	// 绘制mkr line
	{
		HPEN hMkrLinePen = CreatePen(PS_SOLID, 1, m_MkrLineColor);
		// 备份当前画笔设备
		HPEN hMkrLineOldPen = (HPEN)SelectObject(memDC, hMkrLinePen);

		if (m_bEnableMkrXLine)
		{
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft+1, iYValue, NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight-1, iYValue);
		}
		if (m_bEnableMkrYLine)
		{
			MoveToEx(memDC, iXVal, m_rect.top+m_iBorderGridTop, NULL);
			LineTo(memDC, iXVal, m_rect.bottom-m_iBorderGridBottom);
		}

		SelectObject(memDC, hMkrLineOldPen);
		DeleteObject(hMkrLinePen);
	}
	else
	{
		switch (m_imkrType)		// 绘制mkr
		{
		case DEV_MKR_TRIANGLE:	// 三角形
			MoveToEx(memDC, iXVal, iYValue, NULL);
			LineTo(memDC, iXVal+5, iYValue-10);
			LineTo(memDC, iXVal-5, iYValue-10);
			LineTo(memDC, iXVal, iYValue);
			break;
		case DEV_MKR_DIAMOND:	// 菱形
			MoveToEx(memDC, iXVal, iYValue, NULL);
			LineTo(memDC, iXVal+4, iYValue-7);
			LineTo(memDC, iXVal, iYValue-14);
			LineTo(memDC, iXVal-4, iYValue-7);
			LineTo(memDC, iXVal, iYValue);
			break;
		default:	// 缺省：三角形
			MoveToEx(memDC, iXVal, iYValue, NULL);
			LineTo(memDC, iXVal+5, iYValue-10);
			LineTo(memDC, iXVal-5, iYValue-10);
			LineTo(memDC, iXVal, iYValue);
			break;
		}
	}

	// 显示mkr的id号
	_itot(iMkrID+1, szMkrVal, 10);
	TextOut(memDC, iXVal+6, iYValue-15, szMkrVal, _tcslen(szMkrVal));
	if (iYValue<30)		// 显示mkr的Y值
	{
		iYValue += 35;
	}
	if (iYValue<30)
	{
		iYValue = 30;
	}

	if (m_bManualMkrVal==DEV_MKR_VALUE_MANUAL_DIGIT)	// 自定义频标纵坐标值
	{
		_stprintf(szMkrVal, m_czViewPrecision, m_dzMkrVal[iMkrID]);
	}
	else if (m_bManualMkrVal==DEV_MKR_VALEE_MANUAL_CHAR)
	{
		_tcscpy(szMkrVal, m_czMkrVal[iMkrID]);
	}
	else if (m_nRateSizeX==DEVGDI_WAVE_AUTOADJUST)
	{
		if (abs(static_cast<int>(pdData[m_iMkrValue[iMkrID]]))<fabs(pdData[m_iMkrValue[iMkrID]]))
		{
			// 尔洪春 同前，减去开始点2009/9月
			_stprintf(szMkrVal, m_czViewPrecision, pdData[m_iMkrValue[iMkrID]-m_nWaveStartPos]);
		}
		else
		{
			_itot(static_cast<int>(pdData[m_iMkrValue[iMkrID]-m_nWaveStartPos]), szMkrVal, 10);
		}
	}
	else
	{
		if (abs(static_cast<int>(dMkrVal))<fabs(dMkrVal))
		{
			_stprintf(szMkrVal, m_czViewPrecision, dMkrVal);
		}
		else
		{
			_itot(static_cast<int>(dMkrVal), szMkrVal, 10);
		}
	}

	if (m_bEnableMkrDepartment)		// 显示mkr纵坐标单位
	{
		if (m_uczWaveDockY[nWaveID]==Y_LEFT_COORDINATE_DOCK)
		{
			_tcscat(szMkrVal, m_szMkrDepart[iMkrID]);
		}
		else
		{
			_tcscat(szMkrVal, m_szMkrDep2nd[iMkrID]);
		}
		GetTextExtentPoint32(memDC, szMkrVal, _tcslen(szMkrVal), &size);
	}
	else
	{
		GetTextExtentPoint32(memDC, szMkrVal, _tcslen(szMkrVal), &size);
	}
	if (m_bEnableMrkYText)		// 是否显示Mkr纵坐标文字
	{
		if ((m_bEnableMkrLine)&&(m_bEnableMkrYLine))
		{
			int nWaveTemp = nWaveID;

			if (nWaveID>0)
			{
				nWaveTemp ++;
			}
			SetTextColor(memDC, m_LineColor[nWaveID]);
			TextOut(memDC, iXVal-static_cast<int>(size.cx*0.5), m_rect.top+m_iBorderGridTop+size.cy*nWaveTemp, szMkrVal, _tcslen(szMkrVal));
			SetTextColor(memDC, m_TextColor);	// 还原缺省文字颜色
		}
		else
		{
			TextOut(memDC, iXVal-static_cast<int>(size.cx*0.5), iYValue-30, szMkrVal, _tcslen(szMkrVal));
		}
	}

	SetTextColor(memDC, m_TextColor);	// 还原缺省文字颜色

	if (m_iActiveMkr==iMkrID)	// 显示mkr横坐标值，在屏幕左上角
	{
		if (!m_bEnableManualXText/*m_bAutoMkrXValue*/)	// 非自定义mkr横坐标内容
		{
			//尔洪春 同前，减去开始点2009/9月
			dMkrXVal = (m_iMkrValue[iMkrID]-m_nWaveStartPos)*(m_dFullEndX-m_dFullStartX)
				/static_cast<double>(iDataLen-1)+m_dFullStartX;
			if (abs(static_cast<int>(dMkrXVal))<fabs(dMkrXVal))
			{
				_stprintf(czMkrXVal, m_czViewPrecision, dMkrXVal);
			}
			else
			{
				_itot(static_cast<int>(dMkrXVal), czMkrXVal, 10);
			}
			m_szXCurrent = czMkrXVal;
			m_szXCurrent += m_szXDepartment;
		}

		if ( m_bEnableMrkXText )		// wangzheng 2008-08-04
		{
			TextOut(memDC, m_rect.left+m_iBorderGridLeft+10, m_rect.top+m_iBorderGridTop+size.cy, m_szXCurrent,
				_tcslen(m_szXCurrent));
		}
	}

	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);
}

//设置mkr的特定X值
bool CDevGDI::GDI_SetMkrX(const int &iLocation, const int &nYPos,
						  const double *pdData, const int &iDataLen)
{
	int iLength = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	int nLo = iLocation;

	if ((nYPos>m_rect.bottom-m_rect.top-m_iBorderGridBottom)
		||(nYPos<m_rect.top+m_iBorderGridTop)
		||(iLocation>m_rect.right-m_rect.left-m_iBorderGridRight)
		||(iLocation<m_rect.left+m_iBorderGridLeft)||(iLength==0))
	{
		return false;
	}

	if (nLo<m_iBorderGridLeft)
	{
		nLo = m_iBorderGridLeft;
	}
	else if (nLo>m_rect.right-m_rect.left-m_iBorderGridRight)
	{
		nLo = m_rect.right-m_rect.left-m_iBorderGridRight;
	}
	else
	{
	}

	if (DEVGDI_WAVE_AUTOADJUST==m_nRateSizeX)
	{
		if (static_cast<double>(nLo-m_iBorderGridLeft)*iDataLen/iLength-
			(nLo-m_iBorderGridLeft)*iDataLen/iLength>0.5)
		{
			m_iMkrValue[m_iActiveMkr] = (nLo-m_iBorderGridLeft)*iDataLen/iLength+1;
		}
		else
		{
			m_iMkrValue[m_iActiveMkr] = (nLo-m_iBorderGridLeft)*iDataLen/iLength;
		}
		if (m_iMkrValue[m_iActiveMkr]>=iDataLen)
		{
			m_iMkrValue[m_iActiveMkr] = iDataLen-1;
		}
	}
	else
	{
		if ((nLo-m_iBorderGridLeft)*100/m_nRateSizeX<iDataLen)
		{
			if (static_cast<double>(nLo-m_iBorderGridLeft)*100/m_nRateSizeX
				-(nLo-m_iBorderGridLeft)*100/m_nRateSizeX>0.5)
			{
				m_iMkrValue[m_iActiveMkr] = static_cast<int>((nLo
					-m_iBorderGridLeft)*100/m_nRateSizeX)+1;
			}
			else
			{
				m_iMkrValue[m_iActiveMkr] = static_cast<int>((nLo
					-m_iBorderGridLeft)*100/m_nRateSizeX);
			}
		}
	}

	return true;
}

// 设置Mkr的值，加或减
void CDevGDI::GDI_SetMkrX(const bool &AddOrAbate, const int &iDataLen)
{
	double dLength = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	int iXVal = 0;

	assert(iDataLen>0);

	if (AddOrAbate)
	{
		iXVal = static_cast<int>((m_iMkrValue[m_iActiveMkr]+1)*dLength/iDataLen);
		if ((m_nRateSizeX*iDataLen*0.01<dLength)&&(iXVal<dLength))
		{
			m_iMkrValue[m_iActiveMkr] ++;
		}
		if ((m_nRateSizeX*iDataLen*0.01>dLength)
			&&(m_iMkrValue[m_iActiveMkr]<dLength*100/m_nRateSizeX-1))
		{
			m_iMkrValue[m_iActiveMkr] ++;
		}
	}
	else
	{
		if (m_iMkrValue[m_iActiveMkr]>0)
		{
			m_iMkrValue[m_iActiveMkr] --;
		}
	}
}

//获得当前活动的频标
int CDevGDI::GDI_GetActiveMkr(void)
{
	return m_iActiveMkr;
}

//设置当前活动的频标
void CDevGDI::GDI_SetActiveMkr(const int &iMkrID)
{
	int i = 0;
	assert((iMkrID>-1)&&(iMkrID<I_MKR_NUMBER));

	for (; i<I_WAVE_NUM; i++)
	{
		m_mkrColor[m_iActiveMkr][i] = m_mkrColor[iMkrID][i];
		m_mkrColor[iMkrID][i] = m_ActiveMkrColor;
	}
	m_iActiveMkr = iMkrID;
}

// 判断当前频标是否活动
bool CDevGDI::GDI_IsMkrEnable(const int &iMkrID)
{
	assert((iMkrID>-1)&&(iMkrID<I_MKR_NUMBER));

	return m_bMkr[iMkrID];
}

// 将mkr值设为0
void CDevGDI::GDI_ResetMkr()
{
	int i = 0;

	for (; i<I_MKR_NUMBER; i++)
	{
		m_iMkrValue[i] = 0;
	}
	m_nWaveStartPos = 0;
}

// 是否显示ScrollBar
void CDevGDI::GDI_EnableScrollBar(const bool &bScrollBar)
{
	if (bScrollBar!=m_bEnalbeScrollBar)
	{
		if (bScrollBar)
		{
			m_iBorderGridBottom += 20;
		}
		else
		{
			m_iBorderGridBottom -= 20;
		}
		m_bEnalbeScrollBar = bScrollBar;
	}
}

// 获得ScrollBar的显示隐藏属性
bool CDevGDI::GDI_IsScrollBarEnable()
{
	return m_bEnalbeScrollBar;
}

// 绘制ScrollBar
void CDevGDI::DrawScrollBar(const HDC &memDC, const int &nDataLen)
{
	if (m_bEnalbeScrollBar)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, m_GridColor);
		HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
		LOGBRUSH myLogBrush;
		LOGBRUSH HighLightLogBrush;

		myLogBrush.lbColor = m_GridColor;
		myLogBrush.lbHatch = HS_CROSS;
		myLogBrush.lbStyle = BS_SOLID;
		HighLightLogBrush.lbColor = m_ScrollBarHightLight;
		HighLightLogBrush.lbHatch = HS_CROSS;
		HighLightLogBrush.lbStyle = BS_SOLID;

		HBRUSH myBrush = CreateBrushIndirect(&myLogBrush);
		HBRUSH HighLightBrush = CreateBrushIndirect(&HighLightLogBrush);
		int iXPos = 10;
		int iYPos = m_rect.bottom-25;

		// Draw Left PageDown
		MoveToEx(memDC, iXPos, iYPos+14, NULL);
		LineTo(memDC, iXPos+14, iYPos+14);
		LineTo(memDC, iXPos+14, iYPos);
		LineTo(memDC, iXPos, iYPos);
		LineTo(memDC, iXPos, iYPos+14);
		MoveToEx(memDC, iXPos+2, iYPos+7, NULL);
		LineTo(memDC, iXPos+7, iYPos+12);
		LineTo(memDC, iXPos+7, iYPos+2);
		LineTo(memDC, iXPos+2, iYPos+7);
		MoveToEx(memDC, iXPos+7, iYPos+7, NULL);
		LineTo(memDC, iXPos+12, iYPos+12);
		LineTo(memDC, iXPos+12, iYPos+2);
		LineTo(memDC, iXPos+7, iYPos+7);

		// Draw Left ScrollDown
		MoveToEx(memDC, iXPos+16, iYPos+14, NULL);
		LineTo(memDC, iXPos+30, iYPos+14);
		LineTo(memDC, iXPos+30, iYPos);
		LineTo(memDC, iXPos+16, iYPos);
		LineTo(memDC, iXPos+16, iYPos+14);
		MoveToEx(memDC, iXPos+18, iYPos+7, NULL);
		LineTo(memDC, iXPos+27, iYPos+12);
		LineTo(memDC, iXPos+27, iYPos+2);
		LineTo(memDC, iXPos+18, iYPos+7);

		// Draw Right ScrollDown
		MoveToEx(memDC, m_rect.right-iXPos-36, iYPos+14, NULL);
		LineTo(memDC, m_rect.right-iXPos-22, iYPos+14);
		LineTo(memDC, m_rect.right-iXPos-22, iYPos);
		LineTo(memDC, m_rect.right-iXPos-36, iYPos);
		LineTo(memDC, m_rect.right-iXPos-36, iYPos+14);
		MoveToEx(memDC, m_rect.right-iXPos-24, iYPos+7, NULL);
		LineTo(memDC, m_rect.right-iXPos-33, iYPos+12);
		LineTo(memDC, m_rect.right-iXPos-33, iYPos+2);
		LineTo(memDC, m_rect.right-iXPos-24, iYPos+7);

		// Draw Right PageUp
		MoveToEx(memDC, m_rect.right-iXPos-20, iYPos+14, NULL);
		LineTo(memDC, m_rect.right-iXPos-6, iYPos+14);
		LineTo(memDC, m_rect.right-iXPos-6, iYPos);
		LineTo(memDC, m_rect.right-iXPos-20, iYPos);
		LineTo(memDC, m_rect.right-iXPos-20, iYPos+14);
		MoveToEx(memDC, m_rect.right-iXPos-8, iYPos+7, NULL);
		LineTo(memDC, m_rect.right-iXPos-13, iYPos+12);
		LineTo(memDC, m_rect.right-iXPos-13, iYPos+2);
		LineTo(memDC, m_rect.right-iXPos-8, iYPos+7);
		MoveToEx(memDC, m_rect.right-iXPos-13, iYPos+7, NULL);
		LineTo(memDC, m_rect.right-iXPos-18, iYPos+12);
		LineTo(memDC, m_rect.right-iXPos-18, iYPos+2);
		LineTo(memDC, m_rect.right-iXPos-13, iYPos+7);

		// Draw ScrollBar
		double dLength = m_rect.right-m_rect.left-m_iBorderGridRight-m_iBorderGridLeft;
		m_dScrollBarScrollWidth = (m_rect.right-2*iXPos-73)*dLength/(nDataLen*0.01*m_nRateSizeX)
			+iXPos+34;
		m_dScrollBarStartPos = iXPos+34+m_nWaveStartPos*(m_rect.right-2*iXPos-73-m_dScrollBarScrollWidth)
			/(nDataLen-dLength*100/m_nRateSizeX);

		//Rectangle(memDC, iXPos+32, iYPos+15, m_rect.right-iXPos-37, iYPos);
		MoveToEx(memDC, iXPos+32, iYPos+14, NULL);
		LineTo(memDC, iXPos+32, iYPos);
		LineTo(memDC, m_rect.right-iXPos-38, iYPos);
		LineTo(memDC, m_rect.right-iXPos-38, iYPos+14);
		LineTo(memDC, iXPos+32, iYPos+14);
		Rectangle(memDC, static_cast<int>(m_dScrollBarStartPos), iYPos+13,
			static_cast<int>(m_dScrollBarScrollWidth+m_dScrollBarStartPos), iYPos+2);

		switch (m_ucScrollBarActiveButton)
		{
		case DEVGDI_SCROLLBAR_DOWN:
			hOldPen = (HPEN)SelectObject(memDC, myBrush);
			// Fill left PageDown botton
			ExtFloodFill(memDC, iXPos+2, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill left Scroll down button
			ExtFloodFill(memDC, iXPos+18, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill Scroll bar
			if (m_dScrollBarScrollWidth>3.0)
			{
				ExtFloodFill(memDC, static_cast<int>(m_dScrollBarStartPos)+1, m_rect.bottom-14, m_GridColor,
					FLOODFILLBORDER);
			}
			// Fill right PageUP button
			ExtFloodFill(memDC, m_rect.right-iXPos-18, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);

			hOldPen = (HPEN)SelectObject(memDC, HighLightBrush);
			// Fill right Scroll up button
			ExtFloodFill(memDC, m_rect.right-iXPos-34, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			break;
		case DEVGDI_SCROLLBAR_UP:
			hOldPen = (HPEN)SelectObject(memDC, myBrush);
			// Fill left PageDown botton
			ExtFloodFill(memDC, iXPos+2, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill Scroll bar
			if (m_dScrollBarScrollWidth>3.0)
			{
				ExtFloodFill(memDC, static_cast<int>(m_dScrollBarStartPos)+1, m_rect.bottom-14, m_GridColor,
					FLOODFILLBORDER);
			}
			// Fill right Scroll up button
			ExtFloodFill(memDC, m_rect.right-iXPos-34, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill right PageUP button
			ExtFloodFill(memDC, m_rect.right-iXPos-18, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);

			hOldPen = (HPEN)SelectObject(memDC, HighLightBrush);
			// Fill left Scroll down button
			ExtFloodFill(memDC, iXPos+18, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			break;
		case DEVGDI_SCROLLBAR_PAGEDOWN:
			hOldPen = (HPEN)SelectObject(memDC, myBrush);
			// Fill left PageDown botton
			ExtFloodFill(memDC, iXPos+2, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill left Scroll down button
			ExtFloodFill(memDC, iXPos+18, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill Scroll bar
			if (m_dScrollBarScrollWidth>3.0)
			{
				ExtFloodFill(memDC, static_cast<int>(m_dScrollBarStartPos)+1, m_rect.bottom-14, m_GridColor,
					FLOODFILLBORDER);
			}
			// Fill right Scroll up button
			ExtFloodFill(memDC, m_rect.right-iXPos-34, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);

			hOldPen = (HPEN)SelectObject(memDC, HighLightBrush);
			// Fill right PageUP button
			ExtFloodFill(memDC, m_rect.right-iXPos-18, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			break;
		case DEVGDI_SCROLLBAR_PAGEUP:
			hOldPen = (HPEN)SelectObject(memDC, HighLightBrush);
			// Fill left PageDown botton
			ExtFloodFill(memDC, iXPos+2, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);

			hOldPen = (HPEN)SelectObject(memDC, myBrush);
			// Fill left Scroll down button
			ExtFloodFill(memDC, iXPos+18, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill Scroll bar
			if (m_dScrollBarScrollWidth>3.0)
			{
				ExtFloodFill(memDC, static_cast<int>(m_dScrollBarStartPos)+1, m_rect.bottom-14, m_GridColor,
					FLOODFILLBORDER);
			}
			// Fill right Scroll up button
			ExtFloodFill(memDC, m_rect.right-iXPos-34, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill right PageUP button
			ExtFloodFill(memDC, m_rect.right-iXPos-18, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			break;
		case DEVGDI_SCROLLBAR_SCROLL:
			hOldPen = (HPEN)SelectObject(memDC, myBrush);
			// Fill left PageDown botton
			ExtFloodFill(memDC, iXPos+2, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill left Scroll down button
			ExtFloodFill(memDC, iXPos+18, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill right Scroll up button
			ExtFloodFill(memDC, m_rect.right-iXPos-34, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill right PageUP button
			ExtFloodFill(memDC, m_rect.right-iXPos-18, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);

			hOldPen = (HPEN)SelectObject(memDC, HighLightBrush);
			// Fill Scroll bar
			if (m_dScrollBarScrollWidth>3.0)
			{
				ExtFloodFill(memDC, static_cast<int>(m_dScrollBarStartPos)+1, m_rect.bottom-14, m_GridColor,
					FLOODFILLBORDER);
			}
			break;
		default:
			hOldPen = (HPEN)SelectObject(memDC, myBrush);
			// Fill left PageDown botton
			ExtFloodFill(memDC, iXPos+2, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill left Scroll down button
			ExtFloodFill(memDC, iXPos+18, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill Scroll bar
			if (m_dScrollBarScrollWidth>3.0)
			{
				ExtFloodFill(memDC, static_cast<int>(m_dScrollBarStartPos)+1, m_rect.bottom-14, m_GridColor,
					FLOODFILLBORDER);
			}
			// Fill right Scroll up button
			ExtFloodFill(memDC, m_rect.right-iXPos-34, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			// Fill right PageUP button
			ExtFloodFill(memDC, m_rect.right-iXPos-18, m_rect.bottom-12, m_GridColor,
				FLOODFILLBORDER);
			break;
		}

		SelectObject(memDC, hOldPen);
		DeleteObject(myBrush);
		DeleteObject(HighLightBrush);
		DeleteObject(hPen);
	}
}

// 设置横坐标值 纯字符串用
void CDevGDI::GDI_SetXValue(const TCHAR *pszStart, const TCHAR *pszCenter,
							const TCHAR *pszEnd)
{
	assert(pszStart!=NULL);
	assert(pszCenter!=NULL);
	assert(pszEnd!=NULL);

	_tcscpy(m_szXStart, pszStart);
	_tcscpy(m_szXCenter, pszCenter);
	_tcscpy(m_szXEnd, pszEnd);
}

//获得数据区X轴像素数
int CDevGDI::GDI_GetXPixelNumber()
{
	return (m_rect.right-m_iBorderGridRight-m_iBorderGridLeft);
}

// 设置光标当前横坐标值
void CDevGDI::GDI_SetXMkrValue(const CString *pszMkrXValue)
{
	m_szXCurrent = pszMkrXValue[m_iActiveMkr];
}

// 设置光标当前显示的横坐标值
void CDevGDI::GDI_SetActiveXMkrVal(const CString &szMkrXValue)
{
	if (m_bEnableManualXText)
	{
		m_szXCurrent = szMkrXValue;
	}
}

// 设置频标的可视属性，iid--频标id, bEnable-- true可视，false不可视
void CDevGDI::GDI_EnableMkr(const int &iID, const bool &bEnable)
{
	assert((iID>-1)&&(iID<I_MKR_NUMBER));

	m_bMkr[iID] = bEnable;
}

//判断频标线是否显示
bool CDevGDI::GDI_IsMkrLineEnable()
{
	return m_bEnableMkrLine;
}

// 设置显示, 隐藏频标线
// bMkr -- 频标线显示开关
// bXLine -- 横向频标线独立显示开关
// bYLine -- 纵向频标线独立显示开关
void CDevGDI::GDI_EnableMkrLine(const bool &bMkr, const bool &bXLine /*= true*/, const bool &bYLine /*= true*/)
{
	m_bEnableMkrLine = bMkr;
	m_bEnableMkrXLine = bXLine;
	m_bEnableMkrYLine = bYLine;
}

// 获得波形宽度，像素数
int CDevGDI::GDI_GetWavePixNum(void)
{
	return static_cast<int>(m_dWavePixNum);
}

// 判断鼠标的位置，并设置scrollbar的高亮状态
// return value: true -- 在button上， false -- 不在button上
int CDevGDI::GDI_CheckMouseXY(const int &nXPos, const int &nYPos,
							  const double* pdData, const int &iDataLen)
{
	if ((nXPos>10)&&(nXPos<25)&&(nYPos>m_rect.bottom-25)
		&&(nYPos<m_rect.bottom-10))
	{
		if (m_ucScrollBarActiveButton!=DEVGDI_SCROLLBAR_PAGEUP)
		{
			m_ucScrollBarActiveButton = DEVGDI_SCROLLBAR_PAGEUP;
		}

		return DEVGDI_SCROLLBAR_PAGEUP;
	}
	else if ((nXPos>26)&&(nXPos<41)&&(nYPos>m_rect.bottom-25)
		&&(nYPos<m_rect.bottom-10))
	{
		if (m_ucScrollBarActiveButton!=DEVGDI_SCROLLBAR_UP)
		{
			m_ucScrollBarActiveButton = DEVGDI_SCROLLBAR_UP;
		}

		return DEVGDI_SCROLLBAR_UP;
	}
	else if ((nXPos<m_rect.right-15)&&(nXPos>m_rect.right-30)
		&&(nYPos>m_rect.bottom-25)&&(nYPos<m_rect.bottom-10))
	{
		if (m_ucScrollBarActiveButton!=DEVGDI_SCROLLBAR_PAGEDOWN)
		{
			m_ucScrollBarActiveButton = DEVGDI_SCROLLBAR_PAGEDOWN;
		}

		return DEVGDI_SCROLLBAR_PAGEDOWN;
	}
	else if ((nXPos<m_rect.right-31)&&(nXPos>m_rect.right-46)
		&&(nYPos>m_rect.bottom-25)&&(nYPos<m_rect.bottom-10))
	{
		if (m_ucScrollBarActiveButton!=DEVGDI_SCROLLBAR_DOWN)
		{
			m_ucScrollBarActiveButton = DEVGDI_SCROLLBAR_DOWN;
		}

		return DEVGDI_SCROLLBAR_DOWN;
	}
	else if ((nXPos<m_dScrollBarScrollWidth+m_dScrollBarStartPos)&&(nXPos>m_dScrollBarStartPos)
		&&(nYPos>m_rect.bottom-25)&&(nYPos<m_rect.bottom-10))
	{
		if (m_ucScrollBarActiveButton!=DEVGDI_SCROLLBAR_SCROLL)
		{
			m_ucScrollBarActiveButton=DEVGDI_SCROLLBAR_SCROLL;
		}

		return DEVGDI_SCROLLBAR_SCROLL;
	}
	else
	{
		if (m_ucScrollBarActiveButton!=DEVGDI_SCROLLBAR_NOACTIVE)
		{
			m_ucScrollBarActiveButton=DEVGDI_SCROLLBAR_NOACTIVE;
		}

		return DEVGDI_SCROLLBAR_NOACTIVE;
	}
}

// 绘制波形曲线, 自定义大小
bool CDevGDI::DrawLineSpecialLen(const HDC &memDC, const double* pdData, const int &nDataLen, const double* pdData2,
								 const int &nDataLen2, const double *pdData3, const int &nDataLen3)
{
	int i = 0;
	int j = 0;
	int iLineWidth = 1;
	int nXPos = 0;//横坐标曲线点
	int nYPos = 0;//纵坐标曲线点
	// 当前画笔设备 -- Line
	HPEN hPen;
	LOGBRUSH myLogBrush[4];
	myLogBrush[0].lbColor = m_LineColor[0];
	myLogBrush[0].lbHatch = HS_CROSS;
	myLogBrush[0].lbStyle = BS_SOLID;
	myLogBrush[1].lbColor = m_LineColor[1];
	myLogBrush[1].lbHatch = HS_CROSS;
	myLogBrush[1].lbStyle = BS_SOLID;
	myLogBrush[2].lbColor = m_LineColor[2];
	myLogBrush[2].lbHatch = HS_CROSS;
	myLogBrush[2].lbStyle = BS_SOLID;
	myLogBrush[3].lbColor = m_LineColor[3];
	myLogBrush[3].lbHatch = HS_CROSS;
	myLogBrush[3].lbStyle = BS_SOLID;
	HBRUSH myBrush = CreateBrushIndirect(&myLogBrush[0]);

	switch (m_iLineWidth[0])
	{
	case I_DRAW_BIG_POINT:
		iLineWidth = 3;
		break;
	case I_MULTICOLOR_HORIZONTAL_LINE:
	case I_HORIZONTAL_LINE:
	case I_SPECAL_RFANDVA:
		iLineWidth = 1;
		break;
	default:
		iLineWidth = m_iLineWidth[0];
		break;
	}

	hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[0]);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

	m_dWavePixNum = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	if(m_dWavePixNum < 1.0)
	{
		m_dWavePixNum = 1.0;
	}

	/////////////////////////////////////////////////////////////////////////
	switch (m_iLineWidth[0])
	{
	case 0://////////////////////////////////////////////////////////////////
		for (i=0; i<nDataLen; i++)	// 画细点
		{
			nXPos = m_rect.left+m_iBorderGridLeft+static_cast<int>(i*m_nRateSizeX*0.01);
			if (nXPos>m_rect.right-m_iBorderGridRight)
			{
				break;
			}
			nYPos = GetWaveLineY(pdData[i+m_nWaveStartPos]);
			SetPixel(memDC, nXPos, nYPos, m_LineColor[0]);
		}

		for (i=0; i<nDataLen2; i++)	// 画细点
		{
			nXPos = m_rect.left+m_iBorderGridLeft+static_cast<int>(i*m_nRateSizeX*0.01);
			if (nXPos>m_rect.right-m_iBorderGridRight)
			{
				break;
			}
			nYPos = GetWaveLineY(pdData2[i+m_nWaveStartPos]);
			SetPixel(memDC, nXPos, nYPos, m_LineColor[1]);
		}

		for (i=0; i<nDataLen3; i++)	// 画细点
		{
			nXPos = m_rect.left+m_iBorderGridLeft+static_cast<int>(i*m_nRateSizeX*0.01);
			if (nXPos>m_rect.right-m_iBorderGridRight)
			{
				break;
			}
			nYPos = GetWaveLineY(pdData3[i+m_nWaveStartPos]);
			SetPixel(memDC, nXPos, nYPos, m_LineColor[2]);
		}
		break;
	case 1:	//////////////////////////////////////////////////////////////////
	case 3:	// 画细线或粗线
		nXPos = m_rect.left+m_iBorderGridLeft+static_cast<int>(i*m_nRateSizeX*0.01);
		if (nXPos>m_rect.right-m_iBorderGridRight)
		{
			return false;
		}
		nYPos = GetWaveLineY(pdData[i+m_nWaveStartPos]);
		MoveToEx(memDC, nXPos, nYPos, NULL);
		for (i=0; i<nDataLen; i++)
		{
			nXPos = m_rect.left+m_iBorderGridLeft+static_cast<int>(i*m_nRateSizeX*0.01);
			if (nXPos>m_rect.right-m_iBorderGridRight)
			{
				break;
			}
			nYPos = GetWaveLineY(pdData[i+m_nWaveStartPos]);
			LineTo(memDC, nXPos, nYPos);
		}

		if (nDataLen2>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[1], m_LineColor[1]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			nXPos = m_rect.left+m_iBorderGridLeft;
			if (nXPos>m_rect.right-m_iBorderGridRight)
			{
				return false;
			}
			nYPos = GetWaveLineY(pdData2[m_nWaveStartPos]);
			MoveToEx(memDC, nXPos, nYPos, NULL);
			for (i=0; i<nDataLen2; i++)
			{
				nXPos = m_rect.left+m_iBorderGridLeft+static_cast<int>(i*m_nRateSizeX*0.01);
				if (nXPos>m_rect.right-m_iBorderGridRight)
				{
					break;
				}
				nYPos = GetWaveLineY(pdData2[i+m_nWaveStartPos]);
				LineTo(memDC, nXPos, nYPos);
			}
		}

		if (nDataLen3>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, m_iLineWidth[2], m_LineColor[2]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			nXPos = m_rect.left+m_iBorderGridLeft;
			if (nXPos>m_rect.right-m_iBorderGridRight)
			{
				return false;
			}
			nYPos = GetWaveLineY(pdData3[m_nWaveStartPos]);
			MoveToEx(memDC, nXPos, nYPos, NULL);
			for (i=0; i<nDataLen3; i++)
			{
				nXPos = m_rect.left+m_iBorderGridLeft+static_cast<int>(i*m_nRateSizeX*0.01);
				if (nXPos>m_rect.right-m_iBorderGridRight)
				{
					break;
				}
				nYPos = GetWaveLineY(pdData3[i+m_nWaveStartPos]);
				LineTo(memDC, nXPos, nYPos);
			}
		}
		break;
	case I_DRAW_BIG_POINT:///////////////////////////////////////////////////
		for (i=0; i<nDataLen; i++)	// 画粗点
		{
			nXPos = m_rect.left+m_iBorderGridLeft+static_cast<int>(i*m_nRateSizeX*0.01);
			if (nXPos>m_rect.right-m_iBorderGridRight)
			{
				break;
			}
			nYPos = GetWaveLineY(pdData[i+m_nWaveStartPos]);
			MoveToEx(memDC, nXPos, nYPos, NULL);
			LineTo(memDC, nXPos, nYPos);
		}

		if (nDataLen2>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[1]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen2; i++)
			{
				nXPos = m_rect.left+m_iBorderGridLeft+static_cast<int>(i*m_nRateSizeX*0.01);
				if (nXPos>m_rect.right-m_iBorderGridRight)
				{
					break;
				}
				nYPos = GetWaveLineY(pdData2[i+m_nWaveStartPos]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}

		if (nDataLen3>0)
		{
			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[2]);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

			for (i=0; i<nDataLen3; i++)
			{
				nXPos = m_rect.left+m_iBorderGridLeft+static_cast<int>(i*m_nRateSizeX*0.01);
				if (nXPos>m_rect.right-m_iBorderGridRight)
				{
					break;
				}
				nYPos = GetWaveLineY(pdData3[i+m_nWaveStartPos]);
				MoveToEx(memDC, nXPos, nYPos, NULL);
				LineTo(memDC, nXPos, nYPos);
			}
		}
		break;
	case I_MULTICOLOR_HORIZONTAL_LINE:
	case I_HORIZONTAL_LINE://////////////////////////////////////////////////
		for (i=0; i<nDataLen; i++)	// 画竖线
		{
			nXPos = m_rect.left+m_iBorderGridLeft+static_cast<int>(i*m_nRateSizeX*0.01);
			if (nXPos>m_rect.right-m_iBorderGridRight)
			{
				break;
			}
			nYPos = GetWaveLineY(pdData[i+m_nWaveStartPos]);
			MoveToEx(memDC, nXPos, m_rect.bottom-m_iBorderGridBottom-1, NULL);
			LineTo(memDC, nXPos, nYPos);

			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			if (i%2==0)
			{
				hPen = CreatePen(PS_SOLID, m_iLineWidth[1], m_LineColor[1]);
			}
			else
			{
				hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[0]);
			}
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
		}
		break;
	case I_SPECAL_RFANDVA:///////////////////////////////////////////////////
		for (j=0; j<4; j++)
		{
			hOldPen = (HPEN)SelectObject(memDC, hPen);// 备份当前画笔设备
			hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
			if (j==2)
			{
				continue;
			}
			for (i=j; i<nDataLen; i+=6)	// 画竖条
			{
				nXPos = m_rect.left+m_iBorderGridLeft+static_cast<int>(i*m_nRateSizeX*0.01);
				if (nXPos>m_rect.right-m_iBorderGridRight)
				{
					break;
				}
				nYPos = GetWaveLineY(pdData[i+m_nWaveStartPos]);
				Rectangle(memDC, nXPos, m_rect.bottom-m_iBorderGridBottom-1,
					GetWaveLineX(m_dWavePixNum, nDataLen, i+1), nYPos);
			}
			DeleteObject(myBrush);
			DeleteObject(hPen);
			myBrush = CreateBrushIndirect(&myLogBrush[j+1]);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[j+1]);
		}
		break;
	default://///////////////////////////////////////////////////////////////
		break;
	}////////////////////////////////////////////////////////////////////////

	DeleteObject(myBrush);
	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);

	return true;
}

// 获得波形显示比例
int CDevGDI::GDI_GetWaveRate(void)
{
	return m_nRateSizeX;
}

// 设置波形显示比例
void CDevGDI::GDI_SetWaveRate(const int &iRatePercent, const int &nDataLen)
{
	assert((DEVGDI_WAVE_AUTOADJUST==iRatePercent)		//Adjust
		||(DEVGDI_WAVE_10_PERCENT==iRatePercent)		//10%
		||(DEVGDI_WAVE_25_PERCENT==iRatePercent)		//25%
		||(DEVGDI_WAVE_50_PERCENT==iRatePercent)		//50%
		||(DEVGDI_WAVE_100_PERCENT==iRatePercent)		//100%
		||(DEVGDI_WAVE_200_PERCENT==iRatePercent)		//200%
		||(DEVGDI_WAVE_500_PERCENT==iRatePercent)		//500%
		||(DEVGDI_WAVE_1000_PERCENT==iRatePercent)		//1000%
		||(DEVGDI_WAVE_2000_PERCENT==iRatePercent)		//2000%
		||(DEVGDI_WAVE_5000_PERCENT==iRatePercent)		//5000%
		||(DEVGDI_WAVE_10000_PERCENT==iRatePercent));	//10000%

	int i = 0;
	int nScreenData = static_cast<int>(m_dWavePixNum*100/iRatePercent);

	if (iRatePercent>DEVGDI_WAVE_AUTOADJUST)
	{
		for (; i<I_MKR_NUMBER; i++)
		{
			if (m_iMkrValue[i]>m_nWaveStartPos+nScreenData)
			{
				m_iMkrValue[i] = m_nWaveStartPos+nScreenData;
			}
		}
	}

	m_nRateSizeX = iRatePercent;

	if (nScreenData>=nDataLen)	// 当放大波形向缩小波形改变时，判断右边界
	{
		m_nWaveStartPos = 0;
		m_dStartX = m_dFullStartX;
		if (nScreenData==0)		// 计算横坐标最大值
		{
			m_dEndX = m_dFullEndX;
		}
		else
		{
			m_dEndX = (m_dFullEndX-m_dFullStartX)*nScreenData/nDataLen
				+m_dFullStartX;
		}
		GDI_EnableScrollBar(false);
	}
	else if (m_nWaveStartPos+nScreenData>nDataLen)
	{
		m_nWaveStartPos = nDataLen-nScreenData;
		if (DEVGDI_WAVE_AUTOADJUST==m_nRateSizeX)
		{
			m_dStartX = m_dFullStartX;
			m_dEndX = m_dFullEndX;
			m_nWaveStartPos = 0;
			GDI_EnableScrollBar(false);
		}
		else
		{
			if (nDataLen==0)	// 设置横坐标起始、终止值
			{
				m_dStartX = m_dFullStartX;
			}
			else
			{
				m_dStartX = (m_dFullEndX-m_dFullStartX)/nDataLen*m_nWaveStartPos;
			}
			m_dEndX = m_dFullEndX;
			GDI_EnableScrollBar(true);
		}
	}
	else
	{
		if (DEVGDI_WAVE_AUTOADJUST==m_nRateSizeX)
		{
			m_dStartX = m_dFullStartX;
			m_dEndX = m_dFullEndX;
			m_nWaveStartPos = 0;
			GDI_EnableScrollBar(false);
		}
		else
		{
			if (nDataLen==0)
			{
				m_dStartX = m_dFullStartX;
				m_dEndX = m_dFullEndX;
			}
			else
			{
				m_dStartX = (m_dFullEndX-m_dFullStartX)/nDataLen*m_nWaveStartPos;
				m_dEndX = (m_dFullEndX-m_dFullStartX)/nDataLen*(m_nWaveStartPos+
					nScreenData);
			}
			GDI_EnableScrollBar(true);
		}
	}
}

// 移动波形
void CDevGDI::GDI_MoveWave(const int &nScrollType, const int &nDataLen)
{
	int nScreenData = static_cast<int>(m_dWavePixNum);

	if (m_nRateSizeX!=0)	// 除0保护
	{
		nScreenData = static_cast<int>(m_dWavePixNum*100/m_nRateSizeX);
	}

	switch (nScrollType)
	{
	case DEVGDI_SCROLLBAR_DOWN:
		if (m_nWaveStartPos<nDataLen-nScreenData-I_WAVE_PIX_MOVE)
		{
			m_nWaveStartPos += I_WAVE_PIX_MOVE;
		}
		else
		{
			m_nWaveStartPos = nDataLen-nScreenData;
		}
		break;
	case DEVGDI_SCROLLBAR_UP:
		if (m_nWaveStartPos>I_WAVE_PIX_MOVE)
		{
			m_nWaveStartPos -= I_WAVE_PIX_MOVE;
		}
		else
		{
			m_nWaveStartPos = 0;
		}
		break;
	case DEVGDI_SCROLLBAR_PAGEDOWN:
		if (m_nWaveStartPos<nDataLen-2*nScreenData)
		{
			m_nWaveStartPos += static_cast<int>(nScreenData);
		}
		else if (m_nWaveStartPos<nDataLen-nScreenData)
		{
			m_nWaveStartPos = nDataLen-nScreenData;
		}
		break;
	case DEVGDI_SCROLLBAR_PAGEUP:
		if (m_nWaveStartPos>nScreenData)
		{
			m_nWaveStartPos -= nScreenData;
		}
		else if (m_nWaveStartPos<=nScreenData)
		{
			m_nWaveStartPos = 0;
		}
		break;
	case DEVGDI_SCROLLBAR_HOME:
		m_nWaveStartPos = 0;
		break;
	case DEVGDI_SCROLLBAR_END:
		m_nWaveStartPos = nDataLen-nScreenData;
		break;
	default:
		break;
	}

	GDI_SetWaveRate(m_nRateSizeX, nDataLen);
}

//绘制Limit Line
void CDevGDI::DrawLimitLine(const HDC &memDC)
{
	int i = 0;
	int nStartX = 0;
	int nStartY = 0;
	int nEndX = 0;
	int nEndY = 0;
	double dPosX = 0.0;
	double dPosY = 0.0;
	HPEN hPen;
	HPEN hOldPen;
	SIZE TextSize;
	TCHAR czTemp[I_DEPARTMENT_LEN];

	for (; i<I_LIMITLINE_NUMBER; i++)
	{
		if (m_LimitLineTag[i].m_bzEnableLimitLine)
		{
			hPen = CreatePen(PS_SOLID, m_LimitLineTag[i].m_nLineWidth, m_LimitLineTag[i].m_LimitLineColor);
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
			if (m_LimitLineTag[i].m_bzFullScreen)	//全坐标系模式
			{
				if ((fabs(m_LimitLineTag[i].m_dzLimitLineEndVal-m_LimitLineTag[i].m_dzLimitLineStartVal)/(m_dEndX-m_dStartX))
					>(fabs(m_LimitLineTag[i].m_dzLimitLineMaxVal-m_LimitLineTag[i].m_dzLimitLineMinVal)/(m_dEndY-m_dStartY)))
				{
					nStartX = m_rect.left+m_iBorderGridLeft;
					nStartY = GetWaveLineY(m_LimitLineTag[i].m_dzLimitLineMinVal);
					nEndX = m_rect.right-m_iBorderGridRight;
					nEndY = GetWaveLineY(m_LimitLineTag[i].m_dzLimitLineMaxVal);
				}
				else
				{
					nStartX = m_rect.left+m_iBorderGridLeft+static_cast<int>((m_LimitLineTag[i].m_dzLimitLineStartVal-m_dStartX)
						*(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight)/(m_dEndX-m_dStartX));
					nStartY = m_rect.bottom-m_iBorderGridBottom;
					nEndX = m_rect.left+m_iBorderGridLeft+static_cast<int>((m_LimitLineTag[i].m_dzLimitLineEndVal-m_dStartX)
						*(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight)/(m_dEndX-m_dStartX));
					nEndY = m_rect.top+m_iBorderGridTop;
				}
			}
			else	// 非全坐标系模式
			{
				nStartX = m_rect.left+m_iBorderGridLeft+static_cast<int>((m_LimitLineTag[i].m_dzLimitLineStartVal-m_dStartX)
					*(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight)/(m_dEndX-m_dStartX));
				nStartY = GetWaveLineY(m_LimitLineTag[i].m_dzLimitLineMinVal);
				nEndX = m_rect.left+m_iBorderGridLeft+static_cast<int>((m_LimitLineTag[i].m_dzLimitLineEndVal-m_dStartX)
					*(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight)/(m_dEndX-m_dStartX));
				nEndY = GetWaveLineY(m_LimitLineTag[i].m_dzLimitLineMaxVal);
			}
			MoveToEx(memDC, nStartX, nStartY, NULL);
			LineTo(memDC, nEndX, nEndY);

			if (m_LimitLineTag[i].m_bEnableText)
			{
				if (m_LimitLineTag[i].m_bManualText)
				{
					_tcscpy(czTemp, m_LimitLineTag[i].m_czText);
				}
				else
				{
					_stprintf(czTemp, m_czViewPrecision, m_LimitLineTag[i].m_dzLimitLineMaxVal);
				}
				GetTextExtentPoint32(memDC, czTemp, _tcslen(czTemp), &TextSize);
				switch (m_nLimitTextDock[i])
				{
				case DEV_KEEP_LEFT:			// 左侧停靠
					if (nStartX-TextSize.cx<m_iBorderGridLeft+m_rect.left)
					{
						dPosX = m_iBorderGridLeft;
					}
					else
					{
						dPosX = nStartX-TextSize.cx;
					}
					dPosY = nStartY-TextSize.cy*0.5;
					break;
				case DEV_KEEP_TOP_LEFT:		// 左上停靠
					dPosX = nStartX;
					dPosY = nStartY-TextSize.cy;
					break;
				case DEV_KEEP_TOP:			// 上方停靠
					dPosX = (nEndX-nStartX)*0.5+nStartX-TextSize.cx*0.5;
					dPosY = (nStartY+nEndY)*0.5-TextSize.cy;
					break;
				case DEV_KEEP_CENTER:		// 中间停靠
					dPosX = (nEndX-nStartX)*0.5+nStartX-TextSize.cx*0.5;
					dPosY = (nStartY+nEndY)*0.5-TextSize.cy*0.5;
					break;
				case DEV_KEEP_TOP_RIGHT:	// 右上方停靠
					dPosX = nEndX-TextSize.cx;
					dPosY = nEndY-TextSize.cy;
					break;
				case DEV_KEEP_RIGHT:		// 右侧停靠
					if (nEndX+TextSize.cx>m_rect.right-m_iBorderGridRight-m_rect.left)
					{
						dPosX = m_rect.right-m_iBorderGridRight-m_rect.left-TextSize.cx;
					}
					else
					{
						dPosX = nEndX;
					}
					dPosY = nEndY-TextSize.cy*0.5;
					break;
				case DEV_KEEP_BOTTOM_RIGHT:	// 右下方停靠
					dPosX = nEndX-TextSize.cx;
					dPosY = nEndY;
					break;
				case DEV_KEEP_BOTTOM:		// 下方停靠
					dPosX = (nEndX-nStartX)*0.5+nStartX-TextSize.cx*0.5;
					dPosY = (nStartY+nEndY)*0.5;
					break;
				case DEV_KEEP_BOTTOM_LEFT:	// 左下方停靠
					dPosX = nStartX;
					dPosY = nStartY;
					break;
				default:	// Top Right
					if (nEndX+TextSize.cx>m_rect.right-m_iBorderGridRight-m_rect.left)
					{
						dPosX = m_rect.right-m_iBorderGridRight-m_rect.left-TextSize.cx;
					}
					else
					{
						dPosX = nEndX;
					}
					dPosY = nEndY-TextSize.cy*0.5;
				}
				TextOut(memDC, static_cast<int>(dPosX), static_cast<int>(dPosY), czTemp, _tcslen(czTemp));
			}

			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
		}
	}
}

// 设置Limit Line全屏幕显示
// bFullScreen -- 是否全屏显示，true是，false否
// nID -- Limit Line 的 ID
// 返回值：true成功，false失败
bool CDevGDI::GDI_SetLimitLineFullScreen(const bool &bFullScreen, const int &nID)
{
	assert((nID>-1)&&(nID<I_LIMITLINE_NUMBER));

	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	m_LimitLineTag[nID].m_bzFullScreen = bFullScreen;

	return true;
}

// 设置Limit Line全屏幕显示
// bFullScreen -- 是否全屏显示，true是，false否
// nID -- Limit Line 的 ID
// 返回值：true成功，false失败
bool CDevGDI::GDI_GetLimitLineFullScreen(bool &bFullScreen, const int &nID)
{
	assert((nID>-1)&&(nID<I_LIMITLINE_NUMBER));

	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	bFullScreen = m_LimitLineTag[nID].m_bzFullScreen;

	return true;
}

// 设置Limit Line的颜色
// LimitLineColor -- 当前Limit Line的颜色
// nID -- Limit Line 的 ID
// nLineWidth -- 设置LImit Line的线宽
// 返回值：true成功，false失败
bool CDevGDI::GDI_SetLimitLineColor(const COLORREF &LimitLineColor, const int &nID, const int &nLineWidth /*= 1*/)
{
	assert((nID>-1)&&(nID<I_LIMITLINE_NUMBER));

	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	m_LimitLineTag[nID].m_LimitLineColor = LimitLineColor;
	m_LimitLineTag[nID].m_nLineWidth = nLineWidth;

	return true;
}

// 读取Limit Line的颜色
// LimitLineColor -- 当前Limit Line的颜色
// nID -- Limit Line 的 ID
// 返回值：true成功，false失败
bool CDevGDI::GDI_GetLimitLineColor(COLORREF &LimitLineColor, const int &nID)
{
	assert((nID>-1)&&(nID<I_LIMITLINE_NUMBER));

	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	LimitLineColor = m_LimitLineTag[nID].m_LimitLineColor;

	return true;
}

// 读取Limit Line的值
// dStartX -- 横坐标起始值
// dEndX -- 横坐标终止值
// dMinY -- 纵坐标最小值
// dMaxY -- 纵坐标最大值
// nID -- Limit Line 的 ID
// 返回值：true成功，false失败
bool CDevGDI::GDI_GetLimitLineVal(double &dStartX, double &dEndX, double &dMinY, double &dMaxY,
								  const int &nID)
{
	assert((nID>-1)&&(nID<I_LIMITLINE_NUMBER));

	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	dStartX = m_LimitLineTag[nID].m_dzLimitLineStartVal;
	dEndX = m_LimitLineTag[nID].m_dzLimitLineEndVal;
	dMinY = m_LimitLineTag[nID].m_dzLimitLineMinVal;
	dMaxY = m_LimitLineTag[nID].m_dzLimitLineMaxVal;

	return true;
}

// 设置Limit Line的值
// dStartX -- 横坐标起始值
// dEndX -- 横坐标终止值
// dMinY -- 纵坐标最小值
// dMaxY -- 纵坐标最大值
// nID -- Limit Line 的 ID
// bProtect -- 对输入值进行保护，true保护，false不保护
// 返回值：true成功，false失败
bool CDevGDI::GDI_SetLimitLineVal(double &dStartX, double &dEndX, double &dMinY, double &dMaxY,
								  const int &nID, const bool &bProtect /*= true*/)
{
	assert((nID>-1)&&(nID<I_LIMITLINE_NUMBER));

	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	if (bProtect)
	{
		if (dStartX<m_dStartX)
		{
			dStartX = m_dStartX;
		}
		else if (dStartX>m_dEndX)
		{
			dStartX = m_dEndX;
		}
	}
	m_LimitLineTag[nID].m_dzLimitLineStartVal = dStartX;

	if (bProtect)
	{
		if (dEndX<m_dStartX)
		{
			dEndX = m_dStartX;
		}
		else if (dEndX>m_dEndX)
		{
			dEndX = m_dEndX;
		}
	}
	m_LimitLineTag[nID].m_dzLimitLineEndVal = dEndX;

	if (bProtect)
	{
		if (dMinY<m_dStartY)
		{
			dMinY = m_dStartY;
		}
		else if (dMinY>m_dEndY)
		{
			dMinY = m_dEndY;
		}
	}
	m_LimitLineTag[nID].m_dzLimitLineMinVal = dMinY;

	if (bProtect)
	{
		if (dMaxY<m_dStartY)
		{
			dMaxY = m_dStartY;
		}
		else if (dMaxY>m_dEndY)
		{
			dMaxY = m_dEndY;
		}
	}
	m_LimitLineTag[nID].m_dzLimitLineMaxVal = dMaxY;

	return true;
}

// 读取Limit line 的显示属性
// nID -- Limit Line 的 ID
// 返回值：显示属性，true显示, false隐藏或读取失败
bool CDevGDI::GDI_IsLimitLineEnable(const int &nID)
{
	assert((nID>-1)&&(nID<I_LIMITLINE_NUMBER));

	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	return m_LimitLineTag[nID].m_bzEnableLimitLine;
}

// 设置Limit line 的显示属性
// bLimitLine -- 显示属性，true显示, false隐藏
// nID -- Limit Line 的 ID
// 返回值：true成功，false失败
bool CDevGDI::GDI_EnableLimitLine(const bool &bLimitLine, const int &nID)
{
	assert((nID>-1)&&(nID<I_LIMITLINE_NUMBER));

	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	m_LimitLineTag[nID].m_bzEnableLimitLine = bLimitLine;

	return true;
}

//读取Limit Line的值, 返回值为limit line的数量
int CDevGDI::GDI_GetLimitLineVal(int* pnLimitLineVal, bool* pbEnable)
{
	int i = 0;

	for (; i<I_LIMITLINE_NUMBER; i++)
	{
		pnLimitLineVal[i] = static_cast<int>(m_LimitLineTag[i].m_dzLimitLineMinVal);
		pbEnable[i] = m_LimitLineTag[i].m_bzEnableLimitLine;
	}

	return I_LIMITLINE_NUMBER;
}

//设置Limit Line的值
void CDevGDI::GDI_SetLimitLineVal(const int* pnLimitLineVal, const bool* pbEnable,
								  const int &nLimitLineNumber)
{
	assert(nLimitLineNumber<=I_LIMITLINE_NUMBER);
	int i = 0;

	for (; i<nLimitLineNumber; i++)
	{
		m_LimitLineTag[i].m_dzLimitLineMinVal = pnLimitLineVal[i];
		m_LimitLineTag[i].m_dzLimitLineMaxVal = pnLimitLineVal[i];
		m_LimitLineTag[i].m_bzEnableLimitLine = pbEnable[i];
	}
}

// 设置Limit Line的值
void CDevGDI::GDI_SetLimitLineVal(const double* pdLimitLineVal, const bool* pbEnable,
								  const int &nLimitLineNumber)
{
	assert(nLimitLineNumber<=I_LIMITLINE_NUMBER);
	int i = 0;

	for (; i<nLimitLineNumber; i++)
	{
		m_LimitLineTag[i].m_dzLimitLineMinVal = pdLimitLineVal[i];
		m_LimitLineTag[i].m_dzLimitLineMaxVal = pdLimitLineVal[i];
		m_LimitLineTag[i].m_bzEnableLimitLine = pbEnable[i];
	}
}

//设置Limit Line的颜色
void CDevGDI::GDI_SetLimitLineColor(const COLORREF &LimitLineColor)
{
	int i = 0;

	for (; i<I_LIMITLINE_NUMBER; i++)
	{
		m_LimitLineTag[i].m_LimitLineColor = LimitLineColor;
	}
}

//读取Y轴起始，终止值
void CDevGDI::GDI_GetSpanY(double &dStart, double &dEnd)
{
	dStart = m_dStartY;
	dEnd = m_dEndY;
}

// 显示两个波形窗口
bool CDevGDI::GDI_DrawDoubleRect(const double *pdData1, const int &nDataLen1,
								 const double *pdData2, const int &nDataLen2)
{
	int i = 0;

	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right,
		m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, m_brCross);// 备份当前画刷
	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);

	//	DrawLimitLine(memDC);
	DrawDoubleWndLine(memDC, pdData1, nDataLen1, pdData2, nDataLen2);

	DrawDoubleGrid(memDC);
	/*	for (i=0; i<I_MKR_NUMBER; i++)
	{
	if (m_bMkr[i])
	{
	DrawMkr(memDC, pdData, iDataLen, i);
	}
	}*/
	DrawXText(memDC);
	DrawYDoubleText(memDC);
	ShowManualText(memDC);

	/*	if (m_bEnalbeScrollBar)
	{
	DrawScrollBar(memDC);
	}*/

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, memDC,
		m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(mybitmap);
	DeleteDC(memDC);

	return true;
}

// 绘制两条波形曲线，用于双窗口
void CDevGDI::DrawDoubleWndLine(const HDC &memDC, const double* pdData1,
								const int &nDataLen1, const double* pdData2, const int &nDataLen2)
{
	int i = 0;
	int j = 0;
	int iLineWidth = 1;
	int nXPos = 0;//横坐标曲线点
	int nYPos = 0;//纵坐标曲线点
	// 当前画笔设备 -- Line
	HPEN hPen;
	LOGBRUSH myLogBrush[4];
	myLogBrush[0].lbColor = m_LineColor[0];
	myLogBrush[0].lbHatch = HS_CROSS;
	myLogBrush[0].lbStyle = BS_SOLID;
	myLogBrush[1].lbColor = m_LineColor[1];
	myLogBrush[1].lbHatch = HS_CROSS;
	myLogBrush[1].lbStyle = BS_SOLID;
	myLogBrush[2].lbColor = m_LineColor[2];
	myLogBrush[2].lbHatch = HS_CROSS;
	myLogBrush[2].lbStyle = BS_SOLID;
	myLogBrush[3].lbColor = m_LineColor[3];
	myLogBrush[3].lbHatch = HS_CROSS;
	myLogBrush[3].lbStyle = BS_SOLID;
	HBRUSH myBrush = CreateBrushIndirect(&myLogBrush[0]);

	switch (m_iLineWidth[0])
	{
	case I_DRAW_BIG_POINT:
		iLineWidth = 3;
		break;
	case I_MULTICOLOR_HORIZONTAL_LINE:
	case I_HORIZONTAL_LINE:
	case I_SPECAL_RFANDVA:
		iLineWidth = 1;
		break;
	default:
		iLineWidth = m_iLineWidth[0];
		break;
	}

	hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[0]);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

	m_dWavePixNum = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	if (m_dWavePixNum < 1.0)
	{
		m_dWavePixNum = 1.0;
	}

	/////////////////////////////////////////////////////////////////////////
	switch (m_iLineWidth[0])
	{
	case 0://////////////////////////////////////////////////////////////////
		for (i=0; i<nDataLen1; i++)	// 画细点
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen1, i);
			nYPos = GetWaveLineYUp(pdData1[i]);
			SetPixel(memDC, nXPos, nYPos, m_LineColor[0]);
		}

		for (i=0; i<nDataLen2; i++)	// 画细点
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
			nYPos = GetWaveLineYDown(pdData2[i]);
			SetPixel(memDC, nXPos, nYPos, m_LineColor[0]);
		}
		break;
	case 1:	//////////////////////////////////////////////////////////////////
	case 3:	// 画细线或粗线
		nXPos = GetWaveLineX(m_dWavePixNum, nDataLen1, i);
		nYPos = GetWaveLineYUp(pdData1[i]);
		MoveToEx(memDC, nXPos, nYPos, NULL);
		for (i=0; i<nDataLen1; i++)
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen1, i);
			nYPos = GetWaveLineYUp(pdData1[i]);
			LineTo(memDC, nXPos, nYPos);
		}

		nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, 0);
		nYPos = GetWaveLineYDown(pdData2[0]);
		MoveToEx(memDC, nXPos, nYPos, NULL);
		for (i=0; i<nDataLen2; i++)
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
			nYPos = GetWaveLineYDown(pdData2[i]);
			LineTo(memDC, nXPos, nYPos);
		}
		break;
	case I_DRAW_BIG_POINT:	///////////////////////////////////////////////////
		for (i=0; i<nDataLen1; i++)	// 画粗点
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen1, i);
			nYPos = GetWaveLineYUp(pdData1[i]);
			MoveToEx(memDC, nXPos, nYPos, NULL);
			LineTo(memDC, nXPos, nYPos);
		}

		for (i=0; i<nDataLen2; i++)	// 画粗点
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
			nYPos = GetWaveLineYDown(pdData2[i]);
			MoveToEx(memDC, nXPos, nYPos, NULL);
			LineTo(memDC, nXPos, nYPos);
		}
		break;
	case I_MULTICOLOR_HORIZONTAL_LINE:
	case I_HORIZONTAL_LINE://////////////////////////////////////////////////
		for (i=0; i<nDataLen1; i++)	// 画竖线 未支持
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen1, i);
			nYPos = GetWaveLineY(pdData1[i]);
			MoveToEx(memDC, nXPos, m_rect.bottom-m_iBorderGridBottom-1, NULL);
			LineTo(memDC, nXPos, nYPos);

			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			if (i%2==0)
			{
				hPen = CreatePen(PS_SOLID, m_iLineWidth[1], m_LineColor[1]);
			}
			else
			{
				hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[0]);
			}
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
		}
		break;
	case I_SPECAL_RFANDVA:///////////////////////////////////////////////////
		for (j=0; j<4; j++)		// 未支持
		{
			hOldPen = (HPEN)SelectObject(memDC, hPen);// 备份当前画笔设备
			hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
			if (j==2)
			{
				continue;
			}
			for (i=j; i<nDataLen1; i+=6)	// 画竖条
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen1, i);
				nYPos = GetWaveLineY(pdData1[i]);
				Rectangle(memDC, nXPos, m_rect.bottom-m_iBorderGridBottom-1,
					GetWaveLineX(m_dWavePixNum, nDataLen1, i+1), nYPos);
			}
			DeleteObject(myBrush);
			DeleteObject(hPen);
			myBrush = CreateBrushIndirect(&myLogBrush[j+1]);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[j+1]);
		}
		break;
	default://///////////////////////////////////////////////////////////////
		break;
	}////////////////////////////////////////////////////////////////////////

	DeleteObject(myBrush);
	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);
}

// 根据波形当前值计算出屏幕纵坐标值，双窗口上
int CDevGDI::GetWaveLineYUp(const double &dData)
{
	int n1Bottom = static_cast<int>((m_rect.bottom-m_iBorderGridBottom
		-m_iBorderGridTop)*0.5)+m_iBorderGridTop-10;

	return n1Bottom-static_cast<int>((dData-m_dStartY)
		*(n1Bottom-m_iBorderGridTop)/(m_dEndY-m_dStartY))-1;
}

// 根据波形当前值计算出屏幕纵坐标值，双窗口下
int CDevGDI::GetWaveLineYDown(const double &dData)
{
	int n2Top = static_cast<int>((m_rect.bottom-m_iBorderGridBottom
		-m_iBorderGridTop)*0.5)+m_iBorderGridTop+10;

	return m_rect.bottom-m_iBorderGridBottom-static_cast<int>((dData-m_dStartY)
		*(m_rect.bottom-m_rect.top-n2Top-m_iBorderGridBottom)/(m_dEndY
		-m_dStartY))-1;
}

// 绘制双波形窗口Y值
void CDevGDI::DrawYDoubleText(const HDC &memDC)
{
	int nXLocation = m_rect.left+m_iBorderGridLeft;
	int nYLocation = static_cast<int>((m_rect.bottom-m_iBorderGridBottom
		-m_iBorderGridTop)*0.5)+m_iBorderGridTop-24;
	int i = 0;

	for (; i<5; i++)
	{
		ShowText(memDC, m_dStartY+(m_dEndY-m_dStartY)*(4-i)/4, m_szYDepartment,
			nXLocation, m_rect.top+nYLocation*i/4+6, 1);
	}

	for (i=0; i<5; i++)
	{
		ShowText(memDC, m_dStartY+(m_dEndY-m_dStartY)*(4-i)/4, m_szYDepartment,
			nXLocation, m_rect.top+nYLocation+m_iBorderGridTop+nYLocation*i/4+10,
			1);
	}
}

// 绘制上下两个表格函数
void CDevGDI::DrawDoubleGrid(const HDC &memDC)
{
	int i = 0;
	int n1Bottom = static_cast<int>((m_rect.bottom-m_iBorderGridBottom
		-m_iBorderGridTop)*0.5)+m_iBorderGridTop-10;
	int n2Top = n1Bottom+20;
	double dPosY = 0.0;
	double dPosX = 0.0;

	// 当前画笔设备 -- Grid
	LOGBRUSH myLogBrush;
	HPEN hPen = CreatePen(PS_SOLID, m_iGridBorderWidth, m_GridColor);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
	myLogBrush.lbHatch = HS_CROSS;
	myLogBrush.lbStyle = BS_HOLLOW;
	myLogBrush.lbColor = m_GridColor;
	HBRUSH myBrush = CreateBrushIndirect(&myLogBrush);
	hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备

	// 绘制删格外边框
	Rectangle(memDC, m_rect.left+m_iBorderGridLeft, m_rect.top+m_iBorderGridTop,
		m_rect.right-m_iBorderGridRight, n1Bottom+1);
	Rectangle(memDC, m_rect.left+m_iBorderGridLeft, n2Top,
		m_rect.right-m_iBorderGridRight, m_rect.bottom-m_iBorderGridBottom);

	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);
	DeleteObject(myBrush);

	if (m_bGrid)
	{
		// 当前画笔设备 -- Grid
		hPen = CreatePen(PS_DOT, m_iGridLineWidth, m_GridColor);
		hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

		dPosY = (double)(n1Bottom-m_iBorderGridTop)/4;
		// draw grid here 纵向上半部分 //////////////////////////////////////////
		for (i=1; i<2; i++)
		{
			MoveToEx(memDC, m_iBorderGridLeft, m_iBorderGridTop+(int)(i*dPosY),
				NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight,
				m_iBorderGridTop+(int)(i*dPosY));
		}
		i++;	//纵向下半部分
		for (; i<4; i++)
		{
			MoveToEx(memDC, m_iBorderGridLeft, m_iBorderGridTop+(int)(i*dPosY),
				NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight,
				m_iBorderGridTop+(int)(i*dPosY));
		}
		dPosY = (double)(m_rect.bottom-n2Top-m_iBorderGridBottom)/4;
		for (i=1; i<2; i++)
		{
			MoveToEx(memDC, m_iBorderGridLeft, n2Top+(int)(i*dPosY), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight,
				n2Top+(int)(i*dPosY));
		}
		i++;	//纵向下半部分
		for (; i<4; i++)
		{
			MoveToEx(memDC, m_iBorderGridLeft, n2Top+(int)(i*dPosY), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight,
				n2Top+(int)(i*dPosY));
		}

		//////////////////////////////////////////////////////////////////////////
		dPosX = (double)(m_rect.right-m_iBorderGridLeft-m_iBorderGridRight)/8;
		for (i=1; i<4; i++)	//横向左半部分删格
		{
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_iBorderGridTop,
				NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), n1Bottom);
		}
		i++;	//横向右半部分删格
		for (; i<8; i++)
		{
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_iBorderGridTop,
				NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), n1Bottom);
		}
		for (i=1; i<4; i++)	//横向左半部分删格
		{
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), n2Top, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.bottom-m_iBorderGridBottom);
		}
		i++;	//横向右半部分删格
		for (; i<8; i++)
		{
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), n2Top, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.bottom-m_iBorderGridBottom);
		}
		/////////////////////////////////////////////////////////////////////////

		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);

		hPen = CreatePen(PS_SOLID, m_iGridLineWidth, m_GridColor);
		hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

		// 中央部分删格
		/*		MoveToEx(memDC, m_iBorderGridLeft, m_iBorderGridTop+(int)(3*dPosY),
		NULL);
		LineTo(memDC, m_rect.right-m_iBorderGridRight,
		m_iBorderGridTop+(int)(3*dPosY));
		MoveToEx(memDC, m_iBorderGridLeft+(int)(4*dPosX), m_iBorderGridTop,
		NULL);
		LineTo(memDC, m_iBorderGridLeft+(int)(4*dPosX),
		m_rect.bottom-m_iBorderGridBottom);
		*/
		/////////////////////////////////////////////////////////////////////////
		for (i=1; i<20; i++)	//纵向边框刻度上半部分
		{
			//左
			MoveToEx(memDC, m_iBorderGridLeft,
				m_iBorderGridTop+(int)(i*dPosY*0.1), NULL);
			LineTo(memDC, m_iBorderGridLeft+4,
				m_iBorderGridTop+(int)(i*dPosY*0.1));
			//右
			MoveToEx(memDC, m_rect.right-m_iBorderGridRight-2,
				m_iBorderGridTop+(int)(i*dPosY*0.1), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight-6,
				m_iBorderGridTop+(int)(i*dPosY*0.1));
		}
		//		i++;
		for (; i<40; i++)	//纵向边框刻度下半部分
		{
			//左
			MoveToEx(memDC, m_iBorderGridLeft,
				m_iBorderGridTop+(int)(i*dPosY*0.1), NULL);
			LineTo(memDC, m_iBorderGridLeft+4,
				m_iBorderGridTop+(int)(i*dPosY*0.1));
			//右
			MoveToEx(memDC, m_rect.right-m_iBorderGridRight-2,
				m_iBorderGridTop+(int)(i*dPosY*0.1), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight-6,
				m_iBorderGridTop+(int)(i*dPosY*0.1));
		}
		for (i=1; i<20; i++)	//纵向边框刻度上半部分
		{
			//左
			MoveToEx(memDC, m_iBorderGridLeft, n2Top+(int)(i*dPosY*0.1), NULL);
			LineTo(memDC, m_iBorderGridLeft+4, n2Top+(int)(i*dPosY*0.1));
			//右
			MoveToEx(memDC, m_rect.right-m_iBorderGridRight-2,
				n2Top+(int)(i*dPosY*0.1), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight-6,
				n2Top+(int)(i*dPosY*0.1));
		}
		//		i++;
		for (; i<40; i++)	//纵向边框刻度下半部分
		{
			//左
			MoveToEx(memDC, m_iBorderGridLeft, n2Top+(int)(i*dPosY*0.1), NULL);
			LineTo(memDC, m_iBorderGridLeft+4, n2Top+(int)(i*dPosY*0.1));
			//右
			MoveToEx(memDC, m_rect.right-m_iBorderGridRight-2,
				n2Top+(int)(i*dPosY*0.1), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight-6,
				n2Top+(int)(i*dPosY*0.1));
		}
		// 中央部分删格刻度----纵向
		for (i=1; i<40; i++)
		{
			MoveToEx(memDC,
				m_iBorderGridLeft+static_cast<int>((m_rect.right-m_rect.left
				-m_iBorderGridRight-m_iBorderGridLeft)*0.5)-2,
				m_iBorderGridTop+static_cast<int>(i*dPosY*0.1), NULL);
			LineTo(memDC,
				m_iBorderGridLeft+static_cast<int>((m_rect.right-m_rect.left
				-m_iBorderGridRight-m_iBorderGridLeft)*0.5)+3,
				m_iBorderGridTop+static_cast<int>(i*dPosY*0.1));
		}
		for (i=1; i<40; i++)
		{
			MoveToEx(memDC,
				m_iBorderGridLeft+static_cast<int>((m_rect.right-m_rect.left
				-m_iBorderGridRight-m_iBorderGridLeft)*0.5)-2,
				n2Top+static_cast<int>(i*dPosY*0.1), NULL);
			LineTo(memDC,
				m_iBorderGridLeft+static_cast<int>((m_rect.right-m_rect.left
				-m_iBorderGridRight-m_iBorderGridLeft)*0.5)+3,
				n2Top+static_cast<int>(i*dPosY*0.1));
		}

		/////////////////////////////////////////////////////////////////////////
		dPosX *= 0.1;
		for (i=1; i<40; i++)	//横向边框刻度左半部分
		{
			//上上
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX),
				m_iBorderGridTop, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX),
				m_iBorderGridTop+4);
			//上下
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), n1Bottom, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), n1Bottom-5);
			//下上
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), n2Top, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), n2Top+4);
			//下下
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.bottom-m_iBorderGridBottom-2, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.bottom-m_iBorderGridBottom-6);
		}
		//		i++;
		for (; i<80; i++)	//横向边框刻度右半部分
		{
			//上上
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX),
				m_iBorderGridTop, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX),
				m_iBorderGridTop+4);
			//上下
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), n1Bottom, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), n1Bottom-5);
			//下上
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), n2Top, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), n2Top+4);
			//下下
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.bottom-m_iBorderGridBottom-2, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX),
				m_rect.bottom-m_iBorderGridBottom-6);
		}
		// 中央部分删格刻度----横向
		for (i=1; i<80; i++)
		{
			MoveToEx(memDC, m_iBorderGridLeft+static_cast<int>(i*dPosX),
				static_cast<int>((n1Bottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				-2, NULL);
			LineTo(memDC, m_iBorderGridLeft+static_cast<int>(i*dPosX),
				static_cast<int>((n1Bottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				+3);
			MoveToEx(memDC, m_iBorderGridLeft+static_cast<int>(i*dPosX),
				static_cast<int>((n1Bottom-m_iBorderGridTop)*0.5)+n2Top-2, NULL);
			LineTo(memDC, m_iBorderGridLeft+static_cast<int>(i*dPosX),
				static_cast<int>((n1Bottom-m_iBorderGridTop)*0.5)+n2Top+3);
		}
		/////////////////////////////////////////////////////////////////////////

		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);
	}
}

//绘制横向3个波形表格
void CDevGDI::DrawHorizontal3Grid(const HDC &memDC)
{
	int i = 0;
	int n1Right = (m_rect.right-m_iBorderGridLeft-m_iBorderGridRight)/3+m_iBorderGridLeft-5;
	int n2Left = n1Right+10;
	int n2Right = (m_rect.right-m_iBorderGridLeft-m_iBorderGridRight)*2/3+m_iBorderGridLeft-5;
	int n3Left = n2Right+10;
	double dPosY = 0.0;
	double dPosX = 0.0;

	// 当前画笔设备 -- Grid
	LOGBRUSH myLogBrush;
	HPEN hPen = CreatePen(PS_SOLID, m_iGridBorderWidth, m_GridColor);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
	myLogBrush.lbHatch = HS_CROSS;
	myLogBrush.lbStyle = BS_HOLLOW;
	myLogBrush.lbColor = m_GridColor;
	HBRUSH myBrush = CreateBrushIndirect(&myLogBrush);
	hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备

	// 绘制删格外边框
	Rectangle(memDC, m_rect.left+m_iBorderGridLeft, m_rect.top+m_iBorderGridTop,
		n1Right, m_rect.bottom-m_iBorderGridBottom);
	Rectangle(memDC, n2Left, m_rect.top+m_iBorderGridTop, n2Right, m_rect.bottom-m_iBorderGridBottom);
	Rectangle(memDC, n3Left, m_rect.top+m_iBorderGridTop, m_rect.right-m_iBorderGridRight,
		m_rect.bottom-m_iBorderGridBottom);

	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);
	DeleteObject(myBrush);

	if (m_bGrid)
	{
		// 当前画笔设备 -- Grid
		hPen = CreatePen(PS_DOT, m_iGridLineWidth, m_GridColor);
		hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

		dPosY = static_cast<double>(m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)/6;
		// draw grid here 纵向上半部分 //////////////////////////////////////////
		for (i=1; i<3; i++)
		{
			MoveToEx(memDC, m_iBorderGridLeft, m_iBorderGridTop+(int)(i*dPosY),
				NULL);
			LineTo(memDC, n1Right, m_iBorderGridTop+(int)(i*dPosY));
			MoveToEx(memDC, n2Left, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, n2Right, m_iBorderGridTop+(int)(i*dPosY));
			MoveToEx(memDC, n3Left, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight, m_iBorderGridTop+(int)(i*dPosY));
		}
		i++;	//纵向下半部分
		for (; i<6; i++)
		{
			MoveToEx(memDC, m_iBorderGridLeft, m_iBorderGridTop+(int)(i*dPosY),
				NULL);
			LineTo(memDC, n1Right, m_iBorderGridTop+(int)(i*dPosY));
			MoveToEx(memDC, n2Left, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, n2Right, m_iBorderGridTop+(int)(i*dPosY));
			MoveToEx(memDC, n3Left, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight, m_iBorderGridTop+(int)(i*dPosY));
		}

		//////////////////////////////////////////////////////////////////////////
		dPosX = static_cast<double>(n1Right-m_iBorderGridLeft)/8;
		// left
		for (i=1; i<4; i++)	//横向左半部分删格
		{
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_iBorderGridTop-m_rect.top, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_rect.bottom-m_rect.top-m_iBorderGridBottom);
			MoveToEx(memDC, n2Left+(int)(i*dPosX), m_iBorderGridTop-m_rect.top, NULL);
			LineTo(memDC, n2Left+(int)(i*dPosX), m_rect.bottom-m_rect.top-m_iBorderGridBottom);
			MoveToEx(memDC, n3Left+(int)(i*dPosX), m_iBorderGridTop-m_rect.top, NULL);
			LineTo(memDC, n3Left+(int)(i*dPosX), m_rect.bottom-m_rect.top-m_iBorderGridBottom);
		}
		i++;	//横向右半部分删格
		for (; i<8; i++)
		{
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_iBorderGridTop-m_rect.top, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_rect.bottom-m_rect.top-m_iBorderGridBottom);
			MoveToEx(memDC, n2Left+(int)(i*dPosX), m_iBorderGridTop-m_rect.top, NULL);
			LineTo(memDC, n2Left+(int)(i*dPosX), m_rect.bottom-m_rect.top-m_iBorderGridBottom);
			MoveToEx(memDC, n3Left+(int)(i*dPosX), m_iBorderGridTop-m_rect.top, NULL);
			LineTo(memDC, n3Left+(int)(i*dPosX), m_rect.bottom-m_rect.top-m_iBorderGridBottom);
		}

		/////////////////////////////////////////////////////////////////////////

		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);

		hPen = CreatePen(PS_SOLID, m_iGridLineWidth, m_GridColor);
		hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

		// 中央部分删格
		/*		MoveToEx(memDC, m_iBorderGridLeft, m_iBorderGridTop+(int)(3*dPosY),
		NULL);
		LineTo(memDC, m_rect.right-m_iBorderGridRight,
		m_iBorderGridTop+(int)(3*dPosY));
		MoveToEx(memDC, m_iBorderGridLeft+(int)(4*dPosX), m_iBorderGridTop,
		NULL);
		LineTo(memDC, m_iBorderGridLeft+(int)(4*dPosX),
		m_rect.bottom-m_iBorderGridBottom);
		*/
		// 修改dPosY精度 ////////////////////////////////////////////////////////
		dPosY *= 0.1;
		/////////////////////////////////////////////////////////////////////////

		for (i=1; i<30; i++)	//纵向边框刻度上半部分
		{
			//左左
			MoveToEx(memDC, m_iBorderGridLeft, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, m_iBorderGridLeft+4, m_iBorderGridTop+(int)(i*dPosY));
			//左中
			MoveToEx(memDC, static_cast<int>((n1Right-m_iBorderGridLeft-m_rect.left)*0.5)+m_iBorderGridLeft-2,
				m_iBorderGridTop+static_cast<int>(i*dPosY), NULL);
			LineTo(memDC, static_cast<int>((n1Right-m_iBorderGridLeft-m_rect.left)*0.5)+m_iBorderGridLeft+3,
				m_iBorderGridTop+static_cast<int>(i*dPosY));
			//左右
			MoveToEx(memDC, n1Right-2, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, n1Right-6, m_iBorderGridTop+(int)(i*dPosY));
			//中左
			MoveToEx(memDC, n2Left, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, n2Left+4, m_iBorderGridTop+(int)(i*dPosY));
			//中中
			MoveToEx(memDC, static_cast<int>((n2Right-n2Left-m_rect.left)*0.5)+n2Left,
				m_iBorderGridTop+static_cast<int>(i*dPosY), NULL);
			LineTo(memDC, static_cast<int>((n2Right-n2Left-m_rect.left)*0.5)+n2Left+5,
				m_iBorderGridTop+static_cast<int>(i*dPosY));
			//中右
			MoveToEx(memDC, n2Right-2, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, n2Right-6, m_iBorderGridTop+(int)(i*dPosY));
			//右左
			MoveToEx(memDC, n3Left, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, n3Left+4, m_iBorderGridTop+(int)(i*dPosY));
			//右中
			MoveToEx(memDC, static_cast<int>((m_rect.right-m_iBorderGridRight-n3Left-m_rect.left)*0.5)+n3Left-2,
				m_iBorderGridTop+static_cast<int>(i*dPosY), NULL);
			LineTo(memDC, static_cast<int>((m_rect.right-m_iBorderGridRight-n3Left-m_rect.left)*0.5)+n3Left+3,
				m_iBorderGridTop+static_cast<int>(i*dPosY));
			//右右
			MoveToEx(memDC, m_rect.right-m_iBorderGridRight-2, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight-6, m_iBorderGridTop+(int)(i*dPosY));
		}
		//		i++;
		for (; i<60; i++)	//纵向边框刻度下半部分
		{
			//左左
			MoveToEx(memDC, m_iBorderGridLeft, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, m_iBorderGridLeft+4, m_iBorderGridTop+(int)(i*dPosY));
			//左中
			MoveToEx(memDC, static_cast<int>((n1Right-m_iBorderGridLeft-m_rect.left)*0.5)+m_iBorderGridLeft-2,
				m_iBorderGridTop+static_cast<int>(i*dPosY), NULL);
			LineTo(memDC, static_cast<int>((n1Right-m_iBorderGridLeft-m_rect.left)*0.5)+m_iBorderGridLeft+3,
				m_iBorderGridTop+static_cast<int>(i*dPosY));
			//左右
			MoveToEx(memDC, n1Right-2, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, n1Right-6, m_iBorderGridTop+(int)(i*dPosY));
			//中左
			MoveToEx(memDC, n2Left, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, n2Left+4, m_iBorderGridTop+(int)(i*dPosY));
			//中中
			MoveToEx(memDC, static_cast<int>((n2Right-n2Left-m_rect.left)*0.5)+n2Left,
				m_iBorderGridTop+static_cast<int>(i*dPosY), NULL);
			LineTo(memDC, static_cast<int>((n2Right-n2Left-m_rect.left)*0.5)+n2Left+5,
				m_iBorderGridTop+static_cast<int>(i*dPosY));
			//中右
			MoveToEx(memDC, n2Right-2, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, n2Right-6, m_iBorderGridTop+(int)(i*dPosY));
			//右左
			MoveToEx(memDC, n3Left, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, n3Left+4, m_iBorderGridTop+(int)(i*dPosY));
			//右中
			MoveToEx(memDC, static_cast<int>((m_rect.right-m_iBorderGridRight-n3Left-m_rect.left)*0.5)+n3Left-2,
				m_iBorderGridTop+static_cast<int>(i*dPosY), NULL);
			LineTo(memDC, static_cast<int>((m_rect.right-m_iBorderGridRight-n3Left-m_rect.left)*0.5)+n3Left+3,
				m_iBorderGridTop+static_cast<int>(i*dPosY));
			//右右
			MoveToEx(memDC, m_rect.right-m_iBorderGridRight-2, m_iBorderGridTop+(int)(i*dPosY), NULL);
			LineTo(memDC, m_rect.right-m_iBorderGridRight-6, m_iBorderGridTop+(int)(i*dPosY));
		}

		// 修改dPosX的精度 ///////////////////////////////////////
		dPosX *= 0.1;
		//////////////////////////////////////////////////////////

		for (i=1; i<40; i++)	//横向边框刻度左半部分
		{
			//上左
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_iBorderGridTop, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_iBorderGridTop+4);
			//上中
			MoveToEx(memDC, n2Left+(int)(i*dPosX), m_iBorderGridTop, NULL);
			LineTo(memDC, n2Left+(int)(i*dPosX), m_iBorderGridTop+4);
			//上右
			MoveToEx(memDC, n3Left+(int)(i*dPosX), m_iBorderGridTop, NULL);
			LineTo(memDC, n3Left+(int)(i*dPosX), m_iBorderGridTop+4);

			//中左
			MoveToEx(memDC, m_iBorderGridLeft+static_cast<int>(i*dPosX),
				static_cast<int>((m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				-2, NULL);
			LineTo(memDC, m_iBorderGridLeft+static_cast<int>(i*dPosX),
				static_cast<int>((m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				+3);
			//中中
			MoveToEx(memDC, n2Left+static_cast<int>(i*dPosX),
				static_cast<int>((m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				-2, NULL);
			LineTo(memDC, n2Left+static_cast<int>(i*dPosX),
				static_cast<int>((m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				+3);
			//中右
			MoveToEx(memDC, n3Left+static_cast<int>(i*dPosX),
				static_cast<int>((m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				-2, NULL);
			LineTo(memDC, n3Left+static_cast<int>(i*dPosX),
				static_cast<int>((m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				+3);

			//下左
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-2, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-6);
			//下中
			MoveToEx(memDC, n2Left+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-2, NULL);
			LineTo(memDC, n2Left+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-6);
			//下右
			MoveToEx(memDC, n3Left+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-2, NULL);
			LineTo(memDC, n3Left+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-6);
		}
		//		i++;
		for (; i<79; i++)	//横向边框刻度右半部分
		{
			//上左
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_iBorderGridTop, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_iBorderGridTop+4);
			//上中
			MoveToEx(memDC, n2Left+(int)(i*dPosX), m_iBorderGridTop, NULL);
			LineTo(memDC, n2Left+(int)(i*dPosX), m_iBorderGridTop+4);
			//上右
			MoveToEx(memDC, n3Left+(int)(i*dPosX), m_iBorderGridTop, NULL);
			LineTo(memDC, n3Left+(int)(i*dPosX), m_iBorderGridTop+4);

			//中左
			MoveToEx(memDC, m_iBorderGridLeft+static_cast<int>(i*dPosX),
				static_cast<int>((m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				-2, NULL);
			LineTo(memDC, m_iBorderGridLeft+static_cast<int>(i*dPosX),
				static_cast<int>((m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				+3);
			//中中
			MoveToEx(memDC, n2Left+static_cast<int>(i*dPosX),
				static_cast<int>((m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				-2, NULL);
			LineTo(memDC, n2Left+static_cast<int>(i*dPosX),
				static_cast<int>((m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				+3);
			//中右
			MoveToEx(memDC, n3Left+static_cast<int>(i*dPosX),
				static_cast<int>((m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				-2, NULL);
			LineTo(memDC, n3Left+static_cast<int>(i*dPosX),
				static_cast<int>((m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)*0.5)+m_iBorderGridTop
				+3);

			//下左
			MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-2, NULL);
			LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-6);
			//下中
			MoveToEx(memDC, n2Left+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-2, NULL);
			LineTo(memDC, n2Left+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-6);
			//下右
			MoveToEx(memDC, n3Left+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-2, NULL);
			LineTo(memDC, n3Left+(int)(i*dPosX), m_rect.bottom-m_iBorderGridBottom-6);
		}
		/////////////////////////////////////////////////////////////////////////

		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);
	}
}

// 显示对数波形窗口
bool CDevGDI::GDI_Draw3Horizontal(const double *pdData1, const int &nDataLen1,
								  const double *pdData2/* = NULL*/, const int &nDataLen2/* = 0*/,
								  const double *pdData3 /*= NULL*/, const int &nDataLen3 /*= 0*/)
{
	int i = 0;

	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right,
		m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, m_brCross);	// 备份当前画刷
	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);

	DrawLimitLine(memDC);
	DrawHorizontal3Line(memDC, pdData1, nDataLen1, pdData2, nDataLen2, pdData3, nDataLen3);
	DrawHorizontal3Grid(memDC);

	/*	for (i=0; i<I_MKR_NUMBER; i++)
	{
	if (m_bMkr[i])
	{
	DrawMkr(memDC, pdData1, nDataLen1, i);
	}
	}*/
	DrawXTextHorizontal3Grid(memDC);
	DrawYText(memDC);
	ShowManualText(memDC);

	/*	if (m_bEnalbeScrollBar)
	{
	DrawScrollBar(memDC, nDataLen1);
	}*/

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, memDC,
		m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(mybitmap);
	DeleteDC(memDC);

	return true;
}

// 绘制横向3个波形曲线
void CDevGDI::DrawHorizontal3Line(const HDC &memDC, const double *pdData, const int &nDataLen, const double *pdData2,
								  const int &nDataLen2, const double *pdData3, const int nDataLen3)
{
	int i = 0;
	int j = 0;
	int iLineWidth = 1;
	int nXPos = 0;//横坐标曲线点
	int nYPos = 0;//纵坐标曲线点
	// 当前画笔设备 -- Line
	HPEN hPen;
	LOGBRUSH myLogBrush[4];
	myLogBrush[0].lbColor = m_LineColor[0];
	myLogBrush[0].lbHatch = HS_CROSS;
	myLogBrush[0].lbStyle = BS_SOLID;
	myLogBrush[1].lbColor = m_LineColor[1];
	myLogBrush[1].lbHatch = HS_CROSS;
	myLogBrush[1].lbStyle = BS_SOLID;
	myLogBrush[2].lbColor = m_LineColor[2];
	myLogBrush[2].lbHatch = HS_CROSS;
	myLogBrush[2].lbStyle = BS_SOLID;
	myLogBrush[3].lbColor = m_LineColor[3];
	myLogBrush[3].lbHatch = HS_CROSS;
	myLogBrush[3].lbStyle = BS_SOLID;
	HBRUSH myBrush = CreateBrushIndirect(&myLogBrush[0]);

	switch (m_iLineWidth[0])
	{
	case I_DRAW_BIG_POINT:
		iLineWidth = 3;
		break;
	case I_MULTICOLOR_HORIZONTAL_LINE:
	case I_HORIZONTAL_LINE:
	case I_SPECAL_RFANDVA:
		iLineWidth = 1;
		break;
	default:
		iLineWidth = m_iLineWidth[0];
		break;
	}

	hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[0]);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

	m_dWavePixNum = (m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight-20)/3;
	if(m_dWavePixNum < 1.0)
	{
		m_dWavePixNum = 1.0;
	}

	/////////////////////////////////////////////////////////////////////////
	switch (m_iLineWidth[0])
	{
	case 0://////////////////////////////////////////////////////////////////
		for (i=0; i<nDataLen; i++)	// 画细点
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen, i);
			nYPos = GetWaveLineY(pdData[i]);
			SetPixel(memDC, nXPos, nYPos, m_LineColor[0]);
		}
		for (i=0; i<nDataLen2-45; i++)	// 画细点
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
			nYPos = GetWaveLineY(pdData2[i]);
			SetPixel(memDC, nXPos+static_cast<int>(m_dWavePixNum)+12, nYPos, m_LineColor[0]);
		}
		for (i=0; i<nDataLen3; i++)
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3, i);
			nYPos = GetWaveLineY(pdData3[i]);
			SetPixel(memDC, nXPos+static_cast<int>((m_dWavePixNum+9)*2), nYPos, m_LineColor[0]);
		}
		break;
	case 1:	//////////////////////////////////////////////////////////////////
	case 3:	// 画细线或粗线
		nXPos = GetWaveLineX(m_dWavePixNum, nDataLen, 0);
		nYPos = GetWaveLineY(pdData[0]);
		MoveToEx(memDC, nXPos, nYPos, NULL);
		for (i=0; i<nDataLen; i++)
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen, i);
			nYPos = GetWaveLineY(pdData[i]);
			LineTo(memDC, nXPos, nYPos);
		}

		nXPos += 12;
		nYPos = GetWaveLineY(pdData2[0]);
		MoveToEx(memDC, nXPos, nYPos, NULL);
		for (i=0; i<nDataLen2-45; i++)
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
			nYPos = GetWaveLineY(pdData2[i]);
			LineTo(memDC, nXPos+static_cast<int>(m_dWavePixNum)+12, nYPos);
		}

		nXPos += 12;
		nYPos = GetWaveLineY(pdData3[0]);
		MoveToEx(memDC, nXPos+static_cast<int>(m_dWavePixNum)+12, nYPos, NULL);
		for (i=0; i<nDataLen3; i++)
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3, i);
			nYPos = GetWaveLineY(pdData3[i]);
			LineTo(memDC, nXPos+static_cast<int>((m_dWavePixNum+9)*2), nYPos);
		}
		break;
	case I_DRAW_BIG_POINT:///////////////////////////////////////////////////
		for (i=0; i<nDataLen; i++)	// 画粗点
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen, i);
			nYPos = GetWaveLineY(pdData[i]);
			MoveToEx(memDC, nXPos, nYPos, NULL);
			LineTo(memDC, nXPos, nYPos);
		}
		for (i=0; i<nDataLen2-45; i++)	// 画粗点
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen2, i);
			nYPos = GetWaveLineY(pdData2[i]);
			MoveToEx(memDC, nXPos+static_cast<int>(m_dWavePixNum)+12, nYPos, NULL);
			LineTo(memDC, nXPos+static_cast<int>(m_dWavePixNum)+12, nYPos);
		}
		for (i=0; i<nDataLen3; i++)
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen3, i);
			nYPos = GetWaveLineY(pdData3[i]);
			MoveToEx(memDC, nXPos+static_cast<int>((m_dWavePixNum+9)*2), nYPos, NULL);
			LineTo(memDC, nXPos+static_cast<int>((m_dWavePixNum+9)*2), nYPos);
		}
		break;
	case I_MULTICOLOR_HORIZONTAL_LINE:
	case I_HORIZONTAL_LINE://////////////////////////////////////////////////
		for (i=0; i<nDataLen; i++)	// 画竖线
		{
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen, i);
			nYPos = GetWaveLineY(pdData[i]);
			MoveToEx(memDC, nXPos, m_rect.bottom-m_iBorderGridBottom-1, NULL);
			LineTo(memDC, nXPos, nYPos);

			SelectObject(memDC, hOldPen);
			DeleteObject(hPen);
			if (i%2==0)
			{
				hPen = CreatePen(PS_SOLID, m_iLineWidth[1], m_LineColor[1]);
			}
			else
			{
				hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[0]);
			}
			hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
		}
		break;
	case I_SPECAL_RFANDVA:///////////////////////////////////////////////////
		for (j=0; j<4; j++)
		{
			hOldPen = (HPEN)SelectObject(memDC, hPen);// 备份当前画笔设备
			hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备
			if (j==2)
			{
				continue;
			}
			for (i=j; i<nDataLen; i+=6)	// 画竖条
			{
				nXPos = GetWaveLineX(m_dWavePixNum, nDataLen, i);
				nYPos = GetWaveLineY(pdData[i]);
				Rectangle(memDC, nXPos, m_rect.bottom-m_iBorderGridBottom-1,
					GetWaveLineX(m_dWavePixNum, nDataLen, i+1), nYPos);
			}
			DeleteObject(myBrush);
			DeleteObject(hPen);
			myBrush = CreateBrushIndirect(&myLogBrush[j+1]);
			hPen = CreatePen(PS_SOLID, iLineWidth, m_LineColor[j+1]);
		}
		break;
	default://///////////////////////////////////////////////////////////////
		break;
	}////////////////////////////////////////////////////////////////////////

	DeleteObject(myBrush);
	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);
}

// 绘制单波对数横坐标表格
void CDevGDI::DrawLgGrid(const HDC &memDC)
{
	int i = 0;
	double dPosY = 0.0;
	double dPosX = 0.0;

	// 当前画笔设备 -- Grid
	LOGBRUSH myLogBrush;
	HPEN hPen = CreatePen(PS_SOLID, m_iGridBorderWidth, m_GridColor);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
	myLogBrush.lbHatch = HS_CROSS;
	myLogBrush.lbStyle = BS_HOLLOW;
	myLogBrush.lbColor = m_GridColor;
	HBRUSH myBrush = CreateBrushIndirect(&myLogBrush);
	hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备

	// 绘制删格外边框
	Rectangle(memDC, m_rect.left+m_iBorderGridLeft, m_rect.top+m_iBorderGridTop,
		m_rect.right-m_rect.left-m_iBorderGridRight, m_rect.bottom-m_iBorderGridBottom);
	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);
	DeleteObject(myBrush);

	if (m_bGrid)
	{
		// 当前画笔设备 -- Grid
		hPen = CreatePen(PS_DOT, m_iGridLineWidth, m_GridColor);
		hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

		dPosY = static_cast<double>(m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)/6;
		// draw grid here 纵向上半部分 //////////////////////////////////////////
		for (i=1; i<3; i++)
		{
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft, m_iBorderGridTop+(int)(i*dPosY),
				NULL);
			LineTo(memDC, m_rect.right-m_rect.left-m_iBorderGridRight, m_iBorderGridTop+(int)(i*dPosY));
		}
		//		i++;	//纵向下半部分
		for (; i<6; i++)
		{
			MoveToEx(memDC, m_rect.left+m_iBorderGridLeft, m_iBorderGridTop+(int)(i*dPosY),
				NULL);
			LineTo(memDC, m_rect.right-m_rect.left-m_iBorderGridRight, m_iBorderGridTop+(int)(i*dPosY));
		}

		//////////////////////////////////////////////////////////////////////////
		i = 0;
		dPosX = m_iBorderGridLeft+500*log10(static_cast<double>(i));
		while (dPosX<m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight)
		{
			MoveToEx(memDC, m_iBorderGridLeft+static_cast<int>(dPosX), m_iBorderGridTop-m_rect.top, NULL);
			LineTo(memDC, m_iBorderGridLeft+static_cast<int>(dPosX), m_rect.bottom-m_rect.top-m_iBorderGridBottom);
			i+=2;
			dPosX = m_iBorderGridLeft+500*log10(static_cast<double>(i));
		}
		/*		dPosX = static_cast<double>(n1Right-m_iBorderGridLeft)/8;
		// left
		for (i=1; i<8; i++)	//横向删格
		{
		MoveToEx(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_iBorderGridTop-m_rect.top, NULL);
		LineTo(memDC, m_iBorderGridLeft+(int)(i*dPosX), m_rect.bottom-m_rect.top-m_iBorderGridBottom);
		MoveToEx(memDC, n2Left+(int)(i*dPosX), m_iBorderGridTop-m_rect.top, NULL);
		LineTo(memDC, n2Left+(int)(i*dPosX), m_rect.bottom-m_rect.top-m_iBorderGridBottom);
		MoveToEx(memDC, n3Left+(int)(i*dPosX), m_iBorderGridTop-m_rect.top, NULL);
		LineTo(memDC, n3Left+(int)(i*dPosX), m_rect.bottom-m_rect.top-m_iBorderGridBottom);
		}
		*/
		/////////////////////////////////////////////////////////////////////////
		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);
	}
}

// 对数横坐标绘图, public
bool CDevGDI::GDI_DrawLgX(const double *pdData, const int &nDataLen,
						  const double *pdData2/* = NULL*/, const int nDataLen2/* = 0*/)
{
	int i = 0;

	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right,
		m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, m_brCross);// 备份当前画刷
	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);

	DrawLimitLine(memDC);
	/*	if (DEVGDI_WAVE_AUTOADJUST==m_nRateSizeX)
	{
	DrawLineAdjust(memDC, pdData, nDataLen, pdData2, nDataLen2);
	}
	else
	{
	DrawLineSpecialLen(memDC, pdData, nDataLen);
	}
	*/	DrawLgGrid(memDC);

	for (i=0; i<I_MKR_NUMBER; i++)
	{
		if (m_bMkr[i])
		{
			DrawMkr(memDC, pdData, nDataLen, i, 0);
		}
	}
	DrawXText(memDC);
	DrawYText(memDC);

	if (m_bEnalbeScrollBar)
	{
		DrawScrollBar(memDC, nDataLen);
	}

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, memDC,
		m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(mybitmap);
	DeleteDC(memDC);

	return true;
}

// 绘制起始、中止频率/时间值，文本输出--横向3个波形
void CDevGDI::DrawXTextHorizontal3Grid(const HDC &memDC)
{
	int nStartXLocation = m_rect.left+m_iBorderGridLeft-10;
	int nMidXLocation = m_rect.left+m_iBorderGridLeft+(m_rect.right
		-m_iBorderGridLeft-m_iBorderGridRight)/2-15;
	int nYLocation = m_rect.bottom-m_iBorderGridBottom+5;

	int n1Right = (m_rect.right-m_iBorderGridLeft-m_iBorderGridRight)/3+m_iBorderGridLeft-5;
	int n2Left = n1Right+10;
	int n2Right = (m_rect.right-m_iBorderGridLeft-m_iBorderGridRight)*2/3+m_iBorderGridLeft-5;
	int n3Left = n2Right+10;

	//Show start value
	ShowText(memDC, m_dStartX, m_szXDepartment, nStartXLocation, nYLocation, 0);
	ShowText(memDC, m_dStartX, m_szXDepartment, n2Left, nYLocation, 0);
	ShowText(memDC, m_dStartX, m_szXDepartment, n3Left, nYLocation, 0);
	//Show middle value
	ShowText(memDC, (m_dStartX+m_dEndX)/2, m_szXDepartment, (n1Right-m_iBorderGridLeft)/2+m_iBorderGridLeft-15,
		nYLocation, 0);
	ShowText(memDC, (m_dStartX+m_dEndX)/2, m_szXDepartment, nMidXLocation,
		nYLocation, 0);
	ShowText(memDC, (m_dStartX+m_dEndX)/2, m_szXDepartment,
		(n1Right-m_iBorderGridLeft)/2+n3Left-15, nYLocation, 0);
	//Show stop value
	ShowText(memDC, m_dEndX, m_szXDepartment, n1Right+5, nYLocation, 1);
	ShowText(memDC, m_dEndX, m_szXDepartment, n2Right+5, nYLocation, 1);
	ShowText(memDC, m_dEndX, m_szXDepartment, m_rect.right-6, nYLocation, 1);
}

// 设置频标状态，支持波形数量
bool CDevGDI::GDI_SetMkrKeepWave(const int &nMkrID, const int &nWaveID, const bool &bKeep)
{
	assert((nMkrID<=I_MKR_NUMBER)&&(nMkrID>=0));
	assert((nWaveID<I_WAVE_NUM)&&(nWaveID>=0));

	if ((nMkrID<0)||(nMkrID>=I_MKR_NUMBER)||(nWaveID<0)||(nWaveID>=I_WAVE_NUM))
	{
		return false;
	}

	m_bMkrStatus[nMkrID][nWaveID] = bKeep;

	return true;
}

// 读取频标状态，支持波形数量
bool CDevGDI::GDI_GetMkrKeepWave(const int &nMkrID, const int &nWaveID)
{
	assert((nMkrID<=I_MKR_NUMBER)&&(nMkrID>=0));
	assert((nWaveID<I_WAVE_NUM)&&(nWaveID>=0));

	if ((nMkrID<0)||(nMkrID>=I_MKR_NUMBER)||(nWaveID<0)||(nWaveID>=I_WAVE_NUM))
	{
		return false;
	}

	return m_bMkrStatus[nMkrID][nWaveID];
}

// 使用鼠标设置波形当前位置和滚动条位置
bool CDevGDI::GDI_ScrollWaveByMouse(const int &nXPos, const int &nYPos, const double* pdData, const int &nDataLen)
{
	int iXPos = 10;

	if ((nXPos<m_rect.right-iXPos-39/*m_dScrollBarScrollWidth+m_dScrollBarStartPos*/)
		&&(nXPos>iXPos+34/*m_dScrollBarStartPos*/)&&(nYPos>m_rect.bottom-m_iBorderGridBottom/*25*/)
		&&(nYPos<m_rect.bottom/*-10*/))
	{
		double dScrollBarStartPos = nXPos-m_nStartMouseX;
		double dLength = m_rect.right-m_rect.left-m_iBorderGridRight-m_iBorderGridLeft;

		if ((dScrollBarStartPos>iXPos+34)&&(dScrollBarStartPos+m_dScrollBarScrollWidth<m_rect.right-iXPos-35))
		{
			m_nWaveStartPos = static_cast<int>((dScrollBarStartPos-iXPos-34)*(nDataLen-dLength*100/m_nRateSizeX)
				/(m_rect.right-2*iXPos-73-m_dScrollBarScrollWidth));
		}
		GDI_SetWaveRate(m_nRateSizeX, nDataLen);

		return true;
	}

	return false;
}

// 鼠标左键按下时，鼠标坐标的初始值，用于滚动条
void CDevGDI::GDI_SetMouseStartX(const int& nXPos)
{
	m_nStartMouseX = nXPos-static_cast<int>(m_dScrollBarStartPos);
}

// 鼠标左键点击事件滑动条pageup和pagedown事件
bool CDevGDI::GDI_MouseUpPageUp_Down(const int &nXPos, const int &nYPos, const int &nDataLen)
{
	int iXPos = 10;

	if ((nYPos>m_rect.bottom-25)&&(nYPos<m_rect.bottom-10))
	{
		if ((nXPos<m_rect.right-iXPos-39)&&(nXPos>m_dScrollBarScrollWidth+m_dScrollBarStartPos))
		{
			// page down
			GDI_MoveWave(DEVGDI_SCROLLBAR_PAGEDOWN, nDataLen);

			return true;
		}
		else if ((nXPos>iXPos+34)&&(nXPos<m_dScrollBarStartPos))
		{
			// page up
			GDI_MoveWave(DEVGDI_SCROLLBAR_PAGEUP, nDataLen);

			return true;
		}
	}

	return false;
}

// 鼠标画方框控制左键按下
void CDevGDI::GDI_SetMouseLineLButtonDown(const int &nXPos, const int &nYPos)
{
	if ((nXPos>m_iBorderGridLeft)&&(nXPos<m_rect.right-m_iBorderGridRight)&&(nYPos>m_iBorderGridTop)
		&&(nYPos<m_rect.bottom-m_iBorderGridBottom))
	{
		m_MouseLine.nLeft = nXPos;
		m_MouseLine.nTop = m_iBorderGridTop+1;
	}
}

// 鼠标画方框控制移动
void CDevGDI::GDI_SetMouseLineMove(const int &nXPos, const int &nYPos)
{
	if ((nXPos>m_iBorderGridLeft)&&(nXPos<m_rect.right-m_iBorderGridRight)&&(nYPos>m_iBorderGridTop)
		&&(nYPos<m_rect.bottom-m_iBorderGridBottom))
	{
		m_MouseLine.nRight = nXPos;
		m_MouseLine.nBottom = m_rect.bottom-m_iBorderGridBottom-2;
		if (m_MouseLine.nLButtonDown==DEVGDI_MOUSELINE_READY)
		{
			m_MouseLine.nLButtonDown = DEVGDI_MOUSELINE_DRAW;
		}
	}
}

// 鼠标画方框控制左键放开
bool CDevGDI::GDI_SetMouseLineLButtonUp(const int &nXPos, const int &nYPos, const int &nDataLen)
{
	m_MouseLine.nRight = nXPos;
	m_MouseLine.nBottom = m_rect.bottom-m_iBorderGridBottom-2;
	if (m_MouseLine.nLButtonDown>DEVGDI_MOUSELINE_NOCURROR)
	{
		int nZoomSize = 100;
		double dLength = m_rect.right-m_rect.left-m_iBorderGridRight-m_iBorderGridLeft;

		if (m_nRateSizeX==DEVGDI_WAVE_AUTOADJUST)
		{
			if (m_MouseLine.nRight==m_MouseLine.nLeft)	//除零保护
			{
				nZoomSize = DEVGDI_WAVE_MAX_PERCENT;
			}
			else
			{
				nZoomSize = static_cast<int>(dLength*100/nDataLen*dLength/(abs(m_MouseLine.nRight-m_MouseLine.nLeft)));
			}
		}
		else
		{
			if (m_MouseLine.nRight==m_MouseLine.nLeft)	//除零保护
			{
				nZoomSize = DEVGDI_WAVE_MAX_PERCENT;
			}
			else
			{
				nZoomSize = static_cast<int>(m_nRateSizeX*dLength/(abs(m_MouseLine.nRight-m_MouseLine.nLeft)));
			}
		}

		if (nZoomSize<=(DEVGDI_WAVE_25_PERCENT-DEVGDI_WAVE_10_PERCENT)/2)
		{
			nZoomSize = DEVGDI_WAVE_10_PERCENT;
		}
		else if ((nZoomSize>(DEVGDI_WAVE_25_PERCENT+DEVGDI_WAVE_10_PERCENT)/2)
			&&(nZoomSize<=(DEVGDI_WAVE_50_PERCENT+DEVGDI_WAVE_25_PERCENT)/2))
		{
			nZoomSize = DEVGDI_WAVE_25_PERCENT;
		}
		else if ((nZoomSize>(DEVGDI_WAVE_50_PERCENT+DEVGDI_WAVE_25_PERCENT)/2)
			&&(nZoomSize<=(DEVGDI_WAVE_100_PERCENT+DEVGDI_WAVE_50_PERCENT)/2))
		{
			nZoomSize = DEVGDI_WAVE_50_PERCENT;
		}
		else if ((nZoomSize>(DEVGDI_WAVE_100_PERCENT+DEVGDI_WAVE_50_PERCENT)/2)
			&&(nZoomSize<=(DEVGDI_WAVE_200_PERCENT+DEVGDI_WAVE_100_PERCENT)/2))
		{
			nZoomSize = DEVGDI_WAVE_100_PERCENT;
		}
		else if ((nZoomSize>(DEVGDI_WAVE_200_PERCENT+DEVGDI_WAVE_100_PERCENT)/2)
			&&(nZoomSize<=(DEVGDI_WAVE_500_PERCENT+DEVGDI_WAVE_200_PERCENT)/2))
		{
			nZoomSize = DEVGDI_WAVE_200_PERCENT;
		}
		else if ((nZoomSize>(DEVGDI_WAVE_500_PERCENT+DEVGDI_WAVE_200_PERCENT)/2)
			&&(nZoomSize<=(DEVGDI_WAVE_1000_PERCENT+DEVGDI_WAVE_500_PERCENT)/2))
		{
			nZoomSize = DEVGDI_WAVE_500_PERCENT;
		}
		else if ((nZoomSize>(DEVGDI_WAVE_1000_PERCENT+DEVGDI_WAVE_500_PERCENT)/2)
			&&(nZoomSize<=(DEVGDI_WAVE_2000_PERCENT+DEVGDI_WAVE_1000_PERCENT)/2))
		{
			nZoomSize = DEVGDI_WAVE_1000_PERCENT;
		}
		else
		{
			nZoomSize = DEVGDI_WAVE_2000_PERCENT;
		}

		int nMouseStartX = m_MouseLine.nLeft;
		if (m_MouseLine.nLeft>m_MouseLine.nRight)
		{
			nMouseStartX = m_MouseLine.nRight;
		}
		if (m_nRateSizeX==DEVGDI_WAVE_AUTOADJUST)
		{
			m_nWaveStartPos = static_cast<int>(nDataLen*(nMouseStartX-m_iBorderGridLeft)/dLength);
		}
		else
		{
			m_nWaveStartPos += static_cast<int>(100*(nMouseStartX-m_iBorderGridLeft)/nZoomSize);
			if (m_nWaveStartPos>nDataLen-dLength*100/nZoomSize)
			{
				m_nWaveStartPos = static_cast<int>(nDataLen-dLength*100/nZoomSize);
			}
		}

		m_nRateSizeX = nZoomSize;
		m_MouseLine.nLButtonDown = DEVGDI_MOUSELINE_NOCURROR;
	}
	//	GDI_SetWaveRate(m_nRateSizeX, nDataLen);

	return true;
}

// 设置鼠标线状态
void CDevGDI::GDI_SetMouseLineStatus(const int &nStatus)
{
	m_MouseLine.nLButtonDown = nStatus;
}

// 得到鼠标线状态
int CDevGDI::GDI_GetMouseLineStatus(void)
{
	return m_MouseLine.nLButtonDown;
}

//绘制鼠标选择方框
void CDevGDI::DrawMouseRect(const HDC &memDC)
{
	LOGBRUSH myLogBrush;
	HPEN hPen = CreatePen(PS_SOLID, m_iLineWidth[0], m_MouseLineColor);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
	myLogBrush.lbHatch = HS_CROSS;
	myLogBrush.lbStyle = BS_HOLLOW;
	myLogBrush.lbColor = m_GridColor;
	HBRUSH myBrush = CreateBrushIndirect(&myLogBrush);
	hOldPen = (HPEN)SelectObject(memDC, myBrush);// 备份当前画笔设备

	// 绘制删格外边框
	Rectangle(memDC, m_MouseLine.nLeft, m_MouseLine.nTop, m_MouseLine.nRight, m_MouseLine.nBottom);

	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);
	DeleteObject(myBrush);
}

// 获得波形自动拉伸比例
int CDevGDI::GDI_GetWaveAdjustRate(const int &nDataLen)
{
	if (nDataLen>0)
	{
		return (m_rect.right-m_rect.left-m_iBorderGridRight-m_iBorderGridLeft)*100/nDataLen;
	}
	else
	{
		return 0;
	}
}

// 查找波形最近的峰值
void CDevGDI::FindMaxWaveVal(const double* pdData, const int &nDataLen, const int &nMkrID)
{
	//	pdData[m_iMkrValue[nMkrID]];
}

//设置报表绘图区域
bool CDevGDI::GDI_SetRectReport(const RECT &ReportRect, const POINT &StartPoint)
{
	m_rect.right = ReportRect.right-StartPoint.x;
	m_rect.left = ReportRect.left+StartPoint.x;
	m_rect.bottom = ReportRect.bottom-StartPoint.y;
	m_rect.top = ReportRect.top+StartPoint.y;

	return true;
}

// 获取绘图表格数量
void CDevGDI::GDI_GetGridLineNum(int &nXNum, int &nYNum)
{
	nXNum = m_GridNum.nXNum;
	nYNum = m_GridNum.nYNum;
}

// 设置绘图表格数量
bool CDevGDI::GDI_SetGridLineNum(const int &nXNum, const int &nYNum)
{
	if ((nXNum==0)||(nYNum==0))
	{
		return false;
	}

	m_GridNum.nXNum = nXNum;
	m_GridNum.nYNum = nYNum;

	return true;
}

// 设置坐标显示开关
void CDevGDI::GDI_SetTextEnable(const bool &bXEnable, const bool &bYEnable)
{
	m_bEnableXText = bXEnable;
	m_bEnableYText = bYEnable;
}

// 获得当前频标的值
// dYValue -- 频标的横坐标值
// dXValue -- 频标的纵坐标值
// nMkrID -- 获得当前频标的id
// pdWaveData -- 波形数据
// nWaveLen -- 波形数据长度
// return value: -1读取失败，其余值为频标所在波形数据的位置
int CDevGDI::GDI_GetMkrValue(double &dYValue, double &dXValue, const int &nMkrID, const double *pdWaveData,
							 const int &nWaveLen)
{
	assert((nMkrID>-1)&&(nMkrID<I_MKR_NUMBER));
	if ((nMkrID<0)||(nMkrID>=I_MKR_NUMBER))
	{
		return -1;
	}

	dYValue = pdWaveData[m_iMkrValue[nMkrID]];
	dXValue = (m_nWaveStartPos+m_iMkrValue[nMkrID])*(m_dFullEndX-m_dFullStartX)/static_cast<double>(nWaveLen-1)
		+m_dFullStartX;

	return m_iMkrValue[nMkrID];
}

// 手动设置mkr的值,具体见DEV_MKR_VALUE的说明
void CDevGDI::GDI_ManualMkrVal(const BYTE &ucManual)
{
	m_bManualMkrVal = ucManual;
}

// 设置指定mkr纵坐标值
bool CDevGDI::GDI_SetMkrVal(const TCHAR* pszValY, const int &nID)
{
	assert((nID>-1)&&(nID<I_MKR_NUMBER));
	assert(pszValY!=NULL);
	if ((nID<0)||(nID>=I_MKR_NUMBER))
	{
		return false;
	}
	if (pszValY==NULL)
	{
		return false;
	}

	_tcscpy(m_czMkrVal[nID], pszValY);

	return true;
}

// 设置指定mkr纵坐标值
bool CDevGDI::GDI_SetMkrVal(const double &dValY, const int &nID)
{
	assert((nID>-1)&&(nID<I_MKR_NUMBER));
	if ((nID<0)||(nID>=I_MKR_NUMBER))
	{
		return false;
	}

	m_dzMkrVal[nID] = dValY;

	return true;
}

// 获得指定频标所在波形数据中的位置，返回值：数组id
int CDevGDI::GDI_GetMkrXPos(const int &nID)
{
	assert((nID>-1)&&(nID<I_MKR_NUMBER));
	if ((nID<0)||(nID>=I_MKR_NUMBER))
	{
		return -1;
	}

	return m_iMkrValue[nID]+m_nWaveStartPos;
}

// 设置指定频标所在波形数据中的位置
bool CDevGDI::GDI_SetMkrXPos(const int &nID, const int &nArrayID)
{
	assert((nID>-1)&&(nID<I_MKR_NUMBER));
	if ((nID<0)||(nID>=I_MKR_NUMBER))
	{
		return false;
	}

	m_iMkrValue[nID] = nArrayID;

	return true;
}

// 设置频标的单位
bool CDevGDI::GDI_SetMkrUnit(const int &nID, const TCHAR *pszUnit)
{
	assert((nID>-1)&&(nID<I_MKR_NUMBER));
	if ((nID<0)||(nID>=I_MKR_NUMBER))
	{
		return false;
	}
	assert((pszUnit!=NULL)&&(_tcslen(pszUnit)<I_DEPARTMENT_LEN));
	if ((pszUnit==NULL)&&(_tcslen(pszUnit)>=I_DEPARTMENT_LEN))
	{
		return false;
	}

	_tcscpy(m_szMkrDepart[nID], pszUnit);

	return true;
}

// 设置横坐标文字的纵向偏移量
void CDevGDI::GDI_SetXTextYOffset(const int &nOffset /*= 0*/)
{
	m_nXTextOffsetY = nOffset;
}

// 设置纵坐标文字的横向偏移量
void CDevGDI::GDI_SetYTextXOffset(const int &nOffset /*= 0*/)
{
	m_nYTextOffsetX = nOffset;
}

// 绘制表格中心的圆圈
bool CDevGDI::DrawGridCenterRound(const HDC &memDC)
{
	if (m_bGridCenterRound)
	{
		// 当前画笔设备 -- Center Point
		HPEN hPen = CreatePen(PS_SOLID, m_iGridLineWidth, m_GridRoundColor);
		HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
		HBRUSH hbrush = CreateSolidBrush(m_bkColor);
		HBRUSH hbrushOld = (HBRUSH)SelectObject(memDC, hbrush);;
		double dPosY = static_cast<double>(m_rect.bottom-m_rect.top-m_iBorderGridTop-m_iBorderGridBottom)
			/m_GridNum.nYNum;
		double dPosX = static_cast<double>(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight)
			/m_GridNum.nXNum;
		double dCenterPointWidth = m_dGridRoundRate*0.5*dPosX;
		double dCenterPointHeight = m_dGridRoundRate*0.5*dPosY;
		int i = 0;
		int j = 0;

		for (j=0; j<m_GridNum.nYNum; j++)		//纵向
		{
			for (i=0; i<m_GridNum.nXNum; i++)	//横向
			{
				Ellipse(memDC, static_cast<int>(m_rect.left+m_iBorderGridLeft+dPosX*(0.5+i)-dCenterPointWidth),
					static_cast<int>(m_rect.top+m_iBorderGridTop+(0.5+j)*dPosY-dCenterPointHeight),
					static_cast<int>(m_rect.left+m_iBorderGridLeft+dPosX*(0.5+i)+dCenterPointWidth+1),
					static_cast<int>(m_rect.top+m_iBorderGridTop+(0.5+j)*dPosY+dCenterPointHeight+1));
			}
		}

		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);
		SelectObject(memDC, hbrushOld);
		DeleteObject(hbrush);
	}

	return true;
}

// 绘制表格中心点
bool CDevGDI::DrawGridCenterPoint(const HDC &memDC)
{
	if (m_bGridCenterPoint)
	{
		// 当前画笔设备 -- Center Point
		HPEN hPen = CreatePen(PS_SOLID, m_iGridLineWidth, m_GridColor);
		HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
		double dPosY = static_cast<double>(m_rect.bottom-m_rect.top-m_iBorderGridTop-m_iBorderGridBottom)
			/m_GridNum.nYNum;
		double dPosX = static_cast<double>(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight)
			/m_GridNum.nXNum;
		double dCenterPointWidth = m_dGridPointRate*0.5*dPosX;
		double dCenterPointHeight = m_dGridPointRate*0.5*dPosY;
		int i = 0;
		int j = 0;

		for (j=0; j<m_GridNum.nYNum; j++)		//纵向
		{
			for (i=0; i<m_GridNum.nXNum; i++)	//横向
			{
				MoveToEx(memDC, static_cast<int>(m_rect.left+m_iBorderGridLeft+dPosX*(0.5+i)-dCenterPointWidth),
					static_cast<int>(m_rect.top+m_iBorderGridTop+(0.5+j)*dPosY-dCenterPointHeight), NULL);
				LineTo(memDC, static_cast<int>(m_rect.left+m_iBorderGridLeft+dPosX*(0.5+i)+dCenterPointWidth+1),
					static_cast<int>(m_rect.top+m_iBorderGridTop+(0.5+j)*dPosY+dCenterPointHeight+1));
				MoveToEx(memDC, static_cast<int>(m_rect.left+m_iBorderGridLeft+dPosX*(0.5+i)+dCenterPointWidth),
					static_cast<int>(m_rect.top+m_iBorderGridTop+(0.5+j)*dPosY-dCenterPointHeight), NULL);
				LineTo(memDC, static_cast<int>(m_rect.left+m_iBorderGridLeft+dPosX*(0.5+i)-dCenterPointWidth-1),
					static_cast<int>(m_rect.top+m_iBorderGridTop+(0.5+j)*dPosY+dCenterPointHeight+1));
			}
		}

		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);
	}

	return true;
}

// 设置删格中心点的显示开关
void CDevGDI::GDI_EnableGridPoint(const bool &bEnable)
{
	m_bGridCenterPoint = bEnable;
}

// 设置删格中心圈的显示开关
void CDevGDI::GDI_EnableGridRound(const bool &bEnable)
{
	m_bGridCenterRound = bEnable;
}

// 读取删格中心点的显示开关
bool CDevGDI::GDI_IsGridPointEnable(void)
{
	return m_bGridCenterPoint;
}

// 读取删格中心圈的显示开关
bool CDevGDI::GDI_IsGridRoundEnable(void)
{
	return m_bGridCenterRound;
}

// 设置删格中心圈的颜色
void CDevGDI::GDI_SetGridRoundColor(const COLORREF &color)
{
	m_GridRoundColor = color;
}

// 获得删格中心圈的颜色
COLORREF CDevGDI::GDI_GetGridRoundColor(void)
{
	return m_GridRoundColor;
}

// 设置删格中心点显示比例
void CDevGDI::GDI_SetGridPointRate(const double &dRate)
{
	m_dGridPointRate = dRate;
}

// 设置删格中心圈显示比例
void CDevGDI::GDI_SetGridRoundRate(const double &dRate)
{
	m_dGridRoundRate = dRate;
}

// 读取删格中心点显示比例
double CDevGDI::GDI_GetGridPointRate(void)
{
	return m_dGridPointRate;
}

// 读取删格中心圈显示比例
double CDevGDI::GDI_GetGridRoundRate(void)
{
	return m_dGridRoundRate;
}

// 根据波形数组的id获得改位置的横坐标(单位)值
// nDataLen -- 波形数据的总长度
// nArrayID -- 波形数据的id
// 返回值：当前波形点的横坐标(单位)值
double CDevGDI::GDI_GetCurrentXValue(const int &nDataLen, const int &nArrayID)
{
	return (m_nWaveStartPos+nArrayID)*(m_dFullEndX-m_dFullStartX)/static_cast<double>(nDataLen-1)
		+m_dFullStartX;
}

// 设置星座图的象限框的显示与隐藏开关
void CDevGDI::GDI_EnableQamZoom(const bool &bEnable)
{
	m_bQamZoom = bEnable;
}

// 读取星座图的象限框的显示与隐藏开关
bool CDevGDI::GDI_IsQamZoomEnable(void)
{
	return m_bQamZoom;
}

// 设置星座图的象限位置
// nZoom = 1，2，3，4 （象限位置）
// 返回值：true设置成功，false设置失败
bool CDevGDI::GDI_SetQamZoom(const int &nZoom)
{
	if ((nZoom<1)&&(nZoom>4))
	{
		return false;
	}

	m_nQamZoomNum = nZoom;

	return true;
}

// 读取星座图的象限位置，nZoom = 1，2，3，4
int CDevGDI::GDI_GetQamZoom(void)
{
	return m_nQamZoomNum;
}

// 读取星座图象限框的属性
// QamZoomColor -- 象限框的颜色
// nLineWidth -- 象限框的宽度
void CDevGDI::GDI_GetQamZoomStyle(COLORREF &QamZoomColor, int &nLineWidth)
{
	QamZoomColor = m_QamZoomColor;
	nLineWidth = m_nQamZoomLineWidth;
}

// 设置星座图象限框的属性
// QamZoomColor -- 象限框的颜色
// nLineWidth -- 象限框的宽度
void CDevGDI::GDI_SetQamZoomStyle(const COLORREF &QamZoomColor, const int &nLineWidth)
{
	m_QamZoomColor = QamZoomColor;
	m_nQamZoomLineWidth = nLineWidth;
}

// 绘制波形数据，支持波形数据最大点数
// pdData -- 波形数据
// nDataLen -- 当前波形数据的长度
// nMaxPointNum -- 绘图支持的波形数据的最大长度
// 返回值：true成功，false失败
bool CDevGDI::GDI_DrawLineEnableMaxPointNum(const double *pdData, const int &nDataLen,
											const int &nMaxPointNum)
{
	int i = 0;

	//	CFont myFont;
	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right,
		m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, m_brCross);	// 备份当前画刷
	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);
	//	myFont.CreatePointFont(100, _T("宋体"));
	//	SelectObject(memDC, myFont);

	if (m_ucGridType==DEV_GRID_CLASSICAL)
	{
		DrawGrid(memDC);
	}
	else
	{
		DrawGridSpectrum(memDC);
	}
	DrawGridCenterRound(memDC);
	DrawGridCenterPoint(memDC);

	DrawLimitLine(memDC);
	if (DEVGDI_WAVE_AUTOADJUST==m_nRateSizeX)
	{
		DrawLineEnableMaxPointNum(memDC, pdData, nDataLen, nMaxPointNum);
	}
	else
	{
		//		DrawLineSpecialLen(memDC, pdData, iDataLen, pdData2, nDataLen2, pdData3, nDataLen3);
	}

	if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
	{
		FindMaxWaveVal(pdData, nDataLen, i);
	}

	for (i=0; i<I_MKR_NUMBER; i++)
	{
		if (m_bMkr[i])
		{
			if ((nDataLen>0)&&(m_bMkrStatus[i][0]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData, nDataLen, i);
				}
				DrawMkr(memDC, pdData, nDataLen, i, 0);
			}
			/*			if ((nDataLen2>0)&&(m_bMkrStatus[i][1]))
			{
			if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
			{
			FindMaxWaveVal(pdData2, nDataLen2, i);
			}
			DrawMkr(memDC, pdData2, nDataLen2, i);
			}
			if ((nDataLen3>0)&&(m_bMkrStatus[i][2]))
			{
			if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
			{
			FindMaxWaveVal(pdData3, nDataLen3, i);
			}
			DrawMkr(memDC, pdData3, nDataLen3, i);
			}*/
		}
	}

	if (m_bEnableXText)		// 显示横坐标值
	{
		DrawXText(memDC);
	}
	if (m_bEnableYText)			// 显示纵坐标值
	{
		DrawYText(memDC);
	}

	if (m_bEnalbeScrollBar)
	{
		if (nDataLen==0)
		{
			//		DrawScrollBar(memDC, nDataLen2);
		}
		else
		{
			DrawScrollBar(memDC, nDataLen);
		}
	}
	if (m_MouseLine.nLButtonDown==DEVGDI_MOUSELINE_DRAW)
	{
		DrawMouseRect(memDC);
	}
	ShowManualText(memDC);

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, memDC,
		m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(mybitmap);
	DeleteDC(memDC);
	//	myFont.DeleteObject();

	return true;
}

// 绘制波形曲线，支持波形数据最大点数
bool CDevGDI::DrawLineEnableMaxPointNum(const HDC &memDC, const double *pdData, const int &nDataLen,
										const int &nMaxDataLen)
{
	int i = 0;
	int j = 0;
	int nXPos = 0;//横坐标曲线点
	int nYPos = 0;//纵坐标曲线点
	// 当前画笔设备 -- Line
	HPEN hPen = CreatePen(PS_SOLID, m_iLineWidth[0], m_LineColor[0]);
	HPEN hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备

	m_dWavePixNum = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	if(m_dWavePixNum < 1.0)
	{
		m_dWavePixNum = 1.0;
	}

	nXPos = GetWaveLineX(m_dWavePixNum, nMaxDataLen, i);
	nYPos = GetWaveLineY(pdData[i]);
	MoveToEx(memDC, nXPos, nYPos, NULL);
	for (i=0; i<nDataLen; i++)
	{
		nXPos = GetWaveLineX(m_dWavePixNum, nMaxDataLen, i);
		nYPos = GetWaveLineY(pdData[i]);
		LineTo(memDC, nXPos, nYPos);
	}

	SelectObject(memDC, hOldPen);
	DeleteObject(hPen);

	return true;
}

// 显示QAM数据，填充模式
// pnData -- 星座图数据
// nDataLen --输入的星座图数据长度
// bManualColor -- 单个点自定义颜色开关
// 返回值：true成功，false失败
bool CDevGDI::GDI_DrawQamFill(const struct tagCoordinate *pnData, const int &nDataLen,
	const bool &bManualColor /*= false*/)
{
	int i = 0;
	int nXPos = 0;
	int nYPos = 0;

	if (m_bRectChange)
	{
		GDI_DrawQamClean();
		m_bRectChange = false;
	}

	ShowManualText(m_hMemDC);
	DrawQamData(m_hMemDC, pnData, nDataLen, bManualColor);

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, m_hMemDC, m_rect.left, m_rect.top,
		SRCCOPY);

	return true;
}

// 显示QAM数据，填充模式
bool CDevGDI::GDI_DrawQamFill(deque<int> &nstQamData)
{
	deque<int>::iterator nstQamDataIter = nstQamData.begin();
	int i = 0;
	int nXPos = 0;
	int nYPos = 0;

	ShowManualText(m_hdc);
	m_dWavePixNum = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	while (nstQamDataIter<nstQamData.end())	// 画细点
	{
		nXPos = GetWaveLineX(*nstQamDataIter);
		nstQamDataIter ++;
		nYPos =  m_rect.bottom-m_iBorderGridBottom+m_iBorderGridTop-1-GetWaveLineY(*nstQamDataIter);
		nstQamDataIter ++;
		SetPixel(m_hdc, nXPos, nYPos, m_LineColor[0]);
	}

	return true;
}

// 清除Qam数据，用于填充模式
void CDevGDI::GDI_DrawQamClean(void)
{
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
	m_hMemDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP m_hBitmap = CreateCompatibleBitmap(m_hdc, m_rect.right-m_rect.left, m_rect.bottom-m_rect.top);
	m_OldBitmap = (HBITMAP)SelectObject(m_hMemDC, (HBITMAP)m_hBitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(m_hMemDC, m_brCross);	// 备份当前画刷

	FillRect(m_hMemDC, &m_rect, m_brBackground);
	SetBkMode(m_hMemDC, TRANSPARENT);
	SetTextColor(m_hMemDC, m_TextColor);

	if (m_ucGridType==DEV_GRID_CLASSICAL)
	{
		DrawGrid(m_hMemDC);
	}
	else
	{
		DrawGridSpectrum(m_hMemDC);
	}
	DrawGridCenterRound(m_hMemDC);
	DrawGridCenterPoint(m_hMemDC);
	DrawQamZoom(m_hMemDC);

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, m_hMemDC, m_rect.left, m_rect.top,
		SRCCOPY);
}

// 设置数据显示精度(小数点后多少位 >=0 <=99)
void CDevGDI::GDI_SETViewPrecision(const int &nPrecision)
{
	int nPre = nPrecision;
	TCHAR czTemp[10];
	TCHAR czData[10];

	if (nPre<0)
	{
		nPre = 0;
	}
	else if (nPre>99)
	{
		nPre = 99;
	}

	_tcscpy(czTemp, _T("%."));
	_itot(nPre, czData, 10);
	_tcscat(czTemp, czData);
	_tcscat(czTemp, _T("f"));
	_tcscpy(m_czViewPrecision, czTemp);
}

// 自定义X轴坐标内容
void CDevGDI::GDI_EnableManualXText(const bool &bEnable)
{
	m_bEnableManualXText = bEnable;
}

// 读取自定义X轴坐标内容开关
bool CDevGDI::GDI_IsManualXTextEnable(void)
{
	return m_bEnableManualXText;
}

// 自定义Y轴坐标内容
void CDevGDI::GDI_EnableManualYText(const bool &bEnable)
{
	m_bEnableManualYText = bEnable;
}

// 读取自定义X轴坐标内容开关
bool CDevGDI::GDI_IsManualYTextEnable(void)
{
	return m_bEnableManualYText;
}

// 使用鼠标操作设置活动频标
bool CDevGDI::GDI_SetActiveMkrByMouse(const int &nXPos, const int &nYPos, const double *pdData, const int &nDataLen,
	const double *pdData2 /*= NULL*/, const int &nDataLen2 /*= 0*/, const double *pdData3 /*= NULL*/,
	const int &nDataLen3 /*= 0*/, const double *pdData4 /*= NULL*/, const int &nDataLen4 /*= 0*/,
	const double *pdData5 /*= NULL*/, const int &nDataLen5 /*= 0*/, const double *pdData6 /*= NULL*/,
	const int &nDataLen6 /*= 0*/, const double *pdData7 /*= NULL*/, const int &nDataLen7 /*= 0*/,
	const double *pdData8 /*= NULL*/, const int &nDataLen8 /*= 0*/, const double *pdData9 /*= NULL*/,
	const int &nDataLen9 /*= 0*/, const double *pdData10 /*= NULL*/, const int &nDataLen10 /*= 0*/)
{
	int iLength = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	int nLo = nXPos;
	int nActiveMkr = GDI_GetActiveMkr();
	int i = 0;
	int j = 0;
	int nPixX = 0;
	int nPixY = 0;
	const int N_MKR_UP = 35;
	const int N_MKR_DOWN = 5;
	const int N_MKR_LEFT = 20;
	const int N_MKR_RIGHT = 20;

	if ((nYPos>m_rect.bottom-m_rect.top)||(nYPos<m_rect.top)||(nXPos>m_rect.right-m_rect.left)||(nXPos<m_rect.left)
		||(iLength==0))
	{
		return false;
	}

	if (nLo<m_rect.left)
	{
		nLo = m_rect.left;
	}
	else if (nLo>m_rect.right-m_rect.left)
	{
		nLo = m_rect.right-m_rect.left;
	}
	else
	{
	}

	if (DEVGDI_WAVE_AUTOADJUST==m_nRateSizeX)
	{
		for (i=0; i<I_MKR_NUMBER; i++)
		{
			if (m_bMkr[i])
			{
				// wave 1
				if (nDataLen>0)
				{
					nPixX = GetWaveLineX(iLength, nDataLen, m_iMkrValue[i]);
					nPixY = GetWaveLineY(pdData[m_iMkrValue[i]]);
					if ((nPixX-N_MKR_LEFT<nXPos)&&(nPixX+N_MKR_RIGHT>nXPos))
					{
						if (!m_bEnableMkrLine)
						{
							if ((nPixY-N_MKR_UP<nYPos)&&(nPixY+N_MKR_DOWN>nYPos))
							{
								GDI_SetActiveMkr(i);
							}
						}
						else
						{
							GDI_SetActiveMkr(i);
						}
						break;
					}
				}

				// wave 2
				if (nDataLen2>0)
				{
					nPixX = GetWaveLineX(iLength, nDataLen2, m_iMkrValue[i]);
					nPixY = GetWaveLineY(pdData2[m_iMkrValue[i]]);
					if ((nPixX-N_MKR_LEFT<nXPos)&&(nPixX+N_MKR_RIGHT>nXPos))
					{
						if (!m_bEnableMkrLine)
						{
							if ((nPixY-N_MKR_UP<nYPos)&&(nPixY+N_MKR_DOWN>nYPos))
							{
								GDI_SetActiveMkr(i);
							}
						}
						else
						{
							GDI_SetActiveMkr(i);
						}
						break;
					}
				}

				// wave 3
				if (nDataLen3>0)
				{
					nPixX = GetWaveLineX(iLength, nDataLen3, m_iMkrValue[i]);
					nPixY = GetWaveLineY(pdData3[m_iMkrValue[i]]);
					if ((nPixX-N_MKR_LEFT<nXPos)&&(nPixX+N_MKR_RIGHT>nXPos))
					{
						if (!m_bEnableMkrLine)
						{
							if ((nPixY-N_MKR_UP<nYPos)&&(nPixY+N_MKR_DOWN>nYPos))
							{
								GDI_SetActiveMkr(i);
							}
						}
						else
						{
							GDI_SetActiveMkr(i);
						}
						break;
					}
				}

				// wave 4
				if (nDataLen4>0)
				{
					nPixX = GetWaveLineX(iLength, nDataLen4, m_iMkrValue[i]);
					nPixY = GetWaveLineY(pdData4[m_iMkrValue[i]]);
					if ((nPixX-N_MKR_LEFT<nXPos)&&(nPixX+N_MKR_RIGHT>nXPos))
					{
						if (!m_bEnableMkrLine)
						{
							if ((nPixY-N_MKR_UP<nYPos)&&(nPixY+N_MKR_DOWN>nYPos))
							{
								GDI_SetActiveMkr(i);
							}
						}
						else
						{
							GDI_SetActiveMkr(i);
						}
						break;
					}
				}

				// wave 5
				if (nDataLen5>0)
				{
					nPixX = GetWaveLineX(iLength, nDataLen5, m_iMkrValue[i]);
					nPixY = GetWaveLineY(pdData5[m_iMkrValue[i]]);
					if ((nPixX-N_MKR_LEFT<nXPos)&&(nPixX+N_MKR_RIGHT>nXPos))
					{
						if (!m_bEnableMkrLine)
						{
							if ((nPixY-N_MKR_UP<nYPos)&&(nPixY+N_MKR_DOWN>nYPos))
							{
								GDI_SetActiveMkr(i);
							}
						}
						else
						{
							GDI_SetActiveMkr(i);
						}
						break;
					}
				}

				// wave 6
				if (nDataLen6>0)
				{
					nPixX = GetWaveLineX(iLength, nDataLen6, m_iMkrValue[i]);
					nPixY = GetWaveLineY(pdData6[m_iMkrValue[i]]);
					if ((nPixX-N_MKR_LEFT<nXPos)&&(nPixX+N_MKR_RIGHT>nXPos))
					{
						if (!m_bEnableMkrLine)
						{
							if ((nPixY-N_MKR_UP<nYPos)&&(nPixY+N_MKR_DOWN>nYPos))
							{
								GDI_SetActiveMkr(i);
							}
						}
						else
						{
							GDI_SetActiveMkr(i);
						}
						break;
					}
				}

				// wave 7
				if (nDataLen7>0)
				{
					nPixX = GetWaveLineX(iLength, nDataLen7, m_iMkrValue[i]);
					nPixY = GetWaveLineY(pdData7[m_iMkrValue[i]]);
					if ((nPixX-N_MKR_LEFT<nXPos)&&(nPixX+N_MKR_RIGHT>nXPos))
					{
						if (!m_bEnableMkrLine)
						{
							if ((nPixY-N_MKR_UP<nYPos)&&(nPixY+N_MKR_DOWN>nYPos))
							{
								GDI_SetActiveMkr(i);
							}
						}
						else
						{
							GDI_SetActiveMkr(i);
						}
						break;
					}
				}

				// wave 8
				if (nDataLen8>0)
				{
					nPixX = GetWaveLineX(iLength, nDataLen8, m_iMkrValue[i]);
					nPixY = GetWaveLineY(pdData8[m_iMkrValue[i]]);
					if ((nPixX-N_MKR_LEFT<nXPos)&&(nPixX+N_MKR_RIGHT>nXPos))
					{
						if (!m_bEnableMkrLine)
						{
							if ((nPixY-N_MKR_UP<nYPos)&&(nPixY+N_MKR_DOWN>nYPos))
							{
								GDI_SetActiveMkr(i);
							}
						}
						else
						{
							GDI_SetActiveMkr(i);
						}
						break;
					}
				}

				// wave 9
				if (nDataLen9>0)
				{
					nPixX = GetWaveLineX(iLength, nDataLen9, m_iMkrValue[i]);
					nPixY = GetWaveLineY(pdData9[m_iMkrValue[i]]);
					if ((nPixX-N_MKR_LEFT<nXPos)&&(nPixX+N_MKR_RIGHT>nXPos))
					{
						if (!m_bEnableMkrLine)
						{
							if ((nPixY-N_MKR_UP<nYPos)&&(nPixY+N_MKR_DOWN>nYPos))
							{
								GDI_SetActiveMkr(i);
							}
						}
						else
						{
							GDI_SetActiveMkr(i);
						}
						break;
					}
				}

				// wave 10
				if (nDataLen10>0)
				{
					nPixX = GetWaveLineX(iLength, nDataLen10, m_iMkrValue[i]);
					nPixY = GetWaveLineY(pdData10[m_iMkrValue[i]]);
					if ((nPixX-N_MKR_LEFT<nXPos)&&(nPixX+N_MKR_RIGHT>nXPos))
					{
						if (!m_bEnableMkrLine)
						{
							if ((nPixY-N_MKR_UP<nYPos)&&(nPixY+N_MKR_DOWN>nYPos))
							{
								GDI_SetActiveMkr(i);
							}
						}
						else
						{
							GDI_SetActiveMkr(i);
						}
						break;
					}
				}

				// wave 11
			}
		}
	}
	else
	{
		/*if ((nLo-m_iBorderGridLeft)*100/m_nRateSizeX<nDataLen)
		{
		if (static_cast<double>(nLo-m_iBorderGridLeft)*100/m_nRateSizeX-(nLo-m_iBorderGridLeft)*100/m_nRateSizeX>0.5)
		{
		m_iMkrValue[m_iActiveMkr] = static_cast<int>((nLo
		-m_iBorderGridLeft)*100/m_nRateSizeX)+1;
		}
		else
		{
		m_iMkrValue[m_iActiveMkr] = static_cast<int>((nLo
		-m_iBorderGridLeft)*100/m_nRateSizeX);
		}
		}*/
	}

	return true;
}

// 获得当前活动频标的颜色
COLORREF CDevGDI::GDI_GetActiveMkrColor(void)
{
	return m_ActiveMkrColor;
}

// 设置当前活动频标的颜色
void CDevGDI::GDI_SetActiveMkrColor(const COLORREF &ActiveMkrColor)
{
	m_ActiveMkrColor = ActiveMkrColor;
}

// 显示自定义文字信息开关
void CDevGDI::GDI_EnableManualText(const bool &bEnable)
{
	m_bEnableMText = bEnable;
}

// 读取自定义文字信息开关
bool CDevGDI::GDI_IsManualTextEnable(void)
{
	return m_bEnableMText;
}

// 设置自定义文字显示数量
bool CDevGDI::GDI_SetManualTextNum(const int nManualTextNum)
{
	assert((nManualTextNum>=0)&&(nManualTextNum<=N_MAX_MANUAL_TEXT_NUMBER));
	if ((nManualTextNum<0)||(nManualTextNum>N_MAX_MANUAL_TEXT_NUMBER))
	{
		return false;
	}

	m_nManualTextNum = nManualTextNum;

	return true;
}

// 获得自定义文字显示数量
int CDevGDI::GDI_GetManualTextNum(void)
{
	return m_nManualTextNum;
}

// 设置自定义文字内容
// nID -- 自定义文字的位置id
// pczTitle -- 自定义文字标题头
// pczDetail -- 自定义文字内容
// pczSeperate -- 自定义文字标题头与自定义文字内容之间的分隔符
// bEnableView -- 是否显示当前自定义文字
// 返回值 -- true成功，false -- 失败
bool CDevGDI::GDI_SetManualText(const int &nID, const TCHAR *pczTitle, const TCHAR *pczDetail, const TCHAR *pczSeperate,
								const bool &bEnableView /*= true*/, const UINT &nTextPos/* = DEVGDI_TEXT_LEFTTOP*/)
{
	assert((nID>=0)&&(nID<=N_MAX_MANUAL_TEXT_NUMBER));
	if ((nID<0)||(nID>N_MAX_MANUAL_TEXT_NUMBER))
	{
		return false;
	}

	m_ManualText[nID].bView = bEnableView;
	m_ManualText[nID].nTextPos = nTextPos;
	_tcscpy(m_ManualText[nID].czTitle, pczTitle);
	_tcscpy(m_ManualText[nID].czDetail, pczDetail);
	_tcscpy(m_ManualText[nID].czSeperate, pczSeperate);

	return true;
}

// 显示自定义文字
// 修改 wangzheng 2008-06-19
void CDevGDI::ShowManualText(const HDC &memDC)
{
	int i = 0;

	for (; i<N_MAX_MANUAL_TEXT_NUMBER; i++)
	{
		if (m_ManualText[i].bView)
		{
			CString szStr;
			SIZE SizeStr;
			szStr = m_ManualText[i].czTitle;
			szStr += m_ManualText[i].czSeperate;
			szStr += m_ManualText[i].czDetail;
			szStr += _T("   ");

			// 计算字符的像素长度
			GetTextExtentPoint32(memDC, szStr, szStr.GetLength(), &SizeStr);

			switch (m_ManualText[i].nTextPos)
			{
			case DEVGDI_TEXT_LEFTTOP:
				TextOut(memDC, m_rect.left+m_iBorderGridLeft, m_rect.top+m_iBorderGridTop-SizeStr.cy-2, szStr, szStr.GetLength());
				break;
			case DEVGDI_TEXT_LEFT:
				TextOut(memDC, m_rect.left+m_iBorderGridLeft, m_rect.top+m_iBorderGridTop+(m_rect.bottom - m_rect.top)/2, szStr, szStr.GetLength());
				break;
			case DEVGDI_TEXT_LEFTBOTTOM:
				TextOut(memDC, m_rect.left+m_iBorderGridLeft, m_rect.bottom-m_iBorderGridBottom+SizeStr.cy, szStr, szStr.GetLength());
				break;
			case DEVGDI_TEXT_RIGHTTOP:
				TextOut(memDC, m_rect.right-m_iBorderGridRight-SizeStr.cx, m_rect.top+m_iBorderGridTop-SizeStr.cy-2, szStr, szStr.GetLength());
				break;
			case DEVGDI_TEXT_RIGHT:
				TextOut(memDC, m_rect.right-m_iBorderGridRight-SizeStr.cx, m_rect.top+m_iBorderGridTop+(m_rect.bottom - m_rect.top)/2, szStr, szStr.GetLength());
				break;
			case DEVGDI_TEXT_RIGHTBOTTOM:
				TextOut(memDC, m_rect.right-m_iBorderGridRight-SizeStr.cx, m_rect.bottom-m_iBorderGridBottom+SizeStr.cy, szStr, szStr.GetLength());
				break;
			case DEVGDI_TEXT_CENTER:
				TextOut(memDC, m_rect.left+m_iBorderGridLeft+(m_rect.right-m_rect.left)/2-SizeStr.cx/2, m_rect.top+m_iBorderGridTop+(m_rect.bottom-m_rect.top)/2,
					szStr, szStr.GetLength());
				break;
			default:
				TextOut(memDC, m_rect.left+m_iBorderGridLeft, m_rect.top, szStr, szStr.GetLength());
				break;
			}
		}
	}
}

// 自定义纵坐标显示值
// pszVal -- 纵坐标某一格的值
// nLocation -- 所在格的位置，如果当前位置
// 返回值：true设置成功，false设置失败
bool CDevGDI::GDI_SetYValue(const TCHAR *pszVal, const int &nLocation)
{
	assert((pszVal!=NULL)&&(nLocation<100)&&(nLocation>-1));
	if ((pszVal==NULL)||(nLocation>99)||(nLocation<0))
	{
		return false;
	}

	int i = static_cast<int>(m_szzYCurrent.GetSize());

	if (nLocation>=i)
	{
		for (; i<=nLocation; i++)
		{
			m_szzYCurrent.Add(pszVal);
		}
	}
	else
	{
		m_szzYCurrent.SetAt(nLocation, pszVal);
	}

	return true;
}

// 将当前波形图像保存成为图片, 图像文件可以bmp,jpg等各式均可
// pszFileName -- 被保存的文件路径
// pdData-pdData10 -- 波形数据
// iDataLen-nDataLen10 -- 波形数据长度
// 返回值：true保存成功，false保存失败
bool CDevGDI::GDI_SavePicture(const TCHAR *pszFileName, const double *pdData, const int &iDataLen, const double *pdData2/* = NULL*/, const int nDataLen2/* = 0*/,
	const double *pdData3 /*= NULL*/, const int &nDataLen3 /*= 0*/, const double *pdData4 /*= NULL*/, const int &nDataLen4 /*= 0*/, const double *pdData5 /*= NULL*/,
	const int &nDataLen5 /*= 0*/, const double *pdData6 /*= NULL*/, const int &nDataLen6 /*= 0*/, const double *pdData7 /*= NULL*/, const int &nDataLen7 /*= 0*/,
	const double *pdData8 /*= NULL*/, const int &nDataLen8 /*= 0*/, const double *pdData9 /*= NULL*/, const int &nDataLen9 /*= 0*/, const double *pdData10 /*= NULL*/,
	const int &nDataLen10 /*= 0*/, const double *pdData11 /*= NULL*/, const int &nDataLen11 /*= 0*/, const double *pdData12 /*= NULL*/, const int &nDataLen12 /*= 0*/,
	const double *pdData13 /*= NULL*/, const int &nDataLen13 /*= 0*/, const double *pdData14 /*= NULL*/, const int &nDataLen14 /*= 0*/, const double *pdData15 /*= NULL*/,
	const int &nDataLen15 /*= 0*/, const double *pdData16 /*= NULL*/, const int &nDataLen16 /*= 0*/, const double *pdData17 /*= NULL*/, const int &nDataLen17 /*= 0*/,
	const double *pdData18 /*= NULL*/, const int &nDataLen18 /*= 0*/, const double *pdData19 /*= NULL*/, const int &nDataLen19 /*= 0*/, const double *pdData20 /*= NULL*/,
	const int &nDataLen20 /*= 0*/)
{
	int i = 0;

	//	CFont myFont;
	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right,
		m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, m_brCross);// 备份当前画刷
	CImage myImage;

	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);
	//	myFont.CreatePointFont(100, _T("宋体"));
	//	SelectObject(memDC, myFont);

	if (m_ucGridType==DEV_GRID_CLASSICAL)
	{
		DrawGrid(memDC);
	}
	else
	{
		DrawGridSpectrum(memDC);
	}
	DrawGridCenterRound(memDC);
	DrawGridCenterPoint(memDC);

	DrawLimitLine(memDC);
	if (DEVGDI_WAVE_AUTOADJUST==m_nRateSizeX)
	{
		DrawLineAdjust(memDC, pdData, iDataLen, pdData2, nDataLen2, pdData3, nDataLen3, pdData4,
			nDataLen4, pdData5, nDataLen5, pdData6, nDataLen6, pdData7, nDataLen7, pdData8, nDataLen8,
			pdData9, nDataLen9, pdData10, nDataLen10, pdData11, nDataLen11, pdData12, nDataLen12, pdData13,
			nDataLen13, pdData14, nDataLen14, pdData15, nDataLen15, pdData16, nDataLen16,
			pdData17, nDataLen17, pdData18, nDataLen18, pdData19, nDataLen19, pdData20, nDataLen20);
	}
	else
	{
		DrawLineSpecialLen(memDC, pdData, iDataLen, pdData2, nDataLen2, pdData3, nDataLen3);
	}

	if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
	{
		FindMaxWaveVal(pdData, iDataLen, i);
	}

	for (i=0; i<I_MKR_NUMBER; i++)
	{
		if (m_bMkr[i])
		{
			if ((iDataLen>0)&&(m_bMkrStatus[i][0]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData, iDataLen, i);
				}
				DrawMkr(memDC, pdData, iDataLen, i, 0);
			}
			if ((nDataLen2>0)&&(m_bMkrStatus[i][1]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData2, nDataLen2, i);
				}
				DrawMkr(memDC, pdData2, nDataLen2, i, 1);
			}
			if ((nDataLen3>0)&&(m_bMkrStatus[i][2]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData3, nDataLen3, i);
				}
				DrawMkr(memDC, pdData3, nDataLen3, i, 2);
			}
			if ((nDataLen4>0)&&(m_bMkrStatus[i][3]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData4, nDataLen4, i);
				}
				DrawMkr(memDC, pdData4, nDataLen4, i, 3);
			}

			if ((nDataLen5>0)&&(m_bMkrStatus[i][4]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData5, nDataLen5, i);
				}
				DrawMkr(memDC, pdData5, nDataLen5, i, 4);
			}

			if ((nDataLen6>0)&&(m_bMkrStatus[i][5]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData6, nDataLen6, i);
				}
				DrawMkr(memDC, pdData6, nDataLen6, i, 5);
			}

			if ((nDataLen7>0)&&(m_bMkrStatus[i][6]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData7, nDataLen7, i);
				}
				DrawMkr(memDC, pdData7, nDataLen7, i, 6);
			}

			if ((nDataLen8>0)&&(m_bMkrStatus[i][7]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData8, nDataLen8, i);
				}
				DrawMkr(memDC, pdData8, nDataLen8, i, 7);
			}

			if ((nDataLen9>0)&&(m_bMkrStatus[i][8]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData9, nDataLen9, i);
				}
				DrawMkr(memDC, pdData9, nDataLen9, i, 8);
			}

			if ((nDataLen10>0)&&(m_bMkrStatus[i][9]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData10, nDataLen10, i);
				}
				DrawMkr(memDC, pdData10, nDataLen10, i, 9);
			}
		}
	}

	if (m_bEnableXText)		// 显示横坐标值
	{
		DrawXText(memDC);
	}
	if (m_bEnableYText)			// 显示纵坐标值
	{
		DrawYText(memDC);
	}

	if (m_bEnalbeScrollBar)
	{
		if (iDataLen==0)
		{
			DrawScrollBar(memDC, nDataLen2);
		}
		else
		{
			DrawScrollBar(memDC, iDataLen);
		}
	}
	if (m_MouseLine.nLButtonDown==DEVGDI_MOUSELINE_DRAW)
	{
		DrawMouseRect(memDC);
	}
	ShowManualText(memDC);
	DrawMultiText(memDC);

	myImage.Attach(mybitmap);
	myImage.Save(pszFileName);	// save bitmap

	DeleteObject(mybitmap);
	DeleteDC(memDC);
	//	myFont.DeleteObject();

	return true;
}

// 显示一幅波形画面
// ppdData -- 波形数据二维指针数组
// pnDataLen -- 波形数据长度一维指针数组
// nWaveNum -- 波形数据数量
// 返回值：true成功，false失败
bool CDevGDI::GDI_DrawD(double **ppdData, const int *pnDataLen, const int &nWaveNum)
{
	int i = 0;
	int j = 0;

	//	CFont myFont;
	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right,
		m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, m_brCross);// 备份当前画刷

	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);
	//	myFont.CreatePointFont(100, _T("宋体"));
	//	SelectObject(memDC, myFont);

	if (m_ucGridType==DEV_GRID_CLASSICAL)
	{
		DrawGrid(memDC);
	}
	else
	{
		DrawGridSpectrum(memDC);
	}
	DrawGridCenterRound(memDC);
	DrawGridCenterPoint(memDC);

	DrawLimitLine(memDC);
	if (DEVGDI_WAVE_AUTOADJUST==m_nRateSizeX)
	{
		DrawLineAdjust(memDC, ppdData[0], pnDataLen[0], ppdData[1], pnDataLen[1], ppdData[2], pnDataLen[2], ppdData[3],
			pnDataLen[3], ppdData[4], pnDataLen[4], ppdData[5], pnDataLen[5], ppdData[6], pnDataLen[6], ppdData[7], pnDataLen[7],
			ppdData[8], pnDataLen[8], ppdData[9], pnDataLen[9], ppdData[10], pnDataLen[10], ppdData[11], pnDataLen[11], ppdData[12], pnDataLen[12], ppdData[13], pnDataLen[13],
			ppdData[14], pnDataLen[14], ppdData[15], pnDataLen[15], ppdData[16], pnDataLen[16], ppdData[17], pnDataLen[17], ppdData[18], pnDataLen[18], ppdData[19], pnDataLen[19]);
	}
	else
	{
		DrawLineSpecialLen(memDC, ppdData[0], pnDataLen[0], ppdData[1], pnDataLen[1], ppdData[2], pnDataLen[2]);
	}

	if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
	{
		FindMaxWaveVal(ppdData[0], pnDataLen[0], i);
	}

	for (i=0; i<I_MKR_NUMBER; i++)
	{
		if (m_bMkr[i])
		{
			for (j=0; j<I_WAVE_NUM; j++)
			{
				if ((pnDataLen[i]>0)&&(m_bMkrStatus[i][j]))
				{
					if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
					{
						FindMaxWaveVal(ppdData[i], pnDataLen[i], i);
					}
					DrawMkr(memDC, ppdData[i], pnDataLen[i], i, j);
				}
			}
		}
	}

	if (m_bEnableXText)		// 显示横坐标值
	{
		DrawXText(memDC);
	}
	if (m_bEnableYText)			// 显示纵坐标值
	{
		DrawYText(memDC);
	}

	if (m_bEnalbeScrollBar)
	{
		if (pnDataLen[0]==0)
		{
			DrawScrollBar(memDC, pnDataLen[1]);
		}
		else
		{
			DrawScrollBar(memDC, pnDataLen[0]);
		}
	}
	if (m_MouseLine.nLButtonDown==DEVGDI_MOUSELINE_DRAW)
	{
		DrawMouseRect(memDC);
	}
	ShowManualText(memDC);
	DrawMultiText(memDC);

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, memDC, m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(mybitmap);
	DeleteDC(memDC);
	//	myFont.DeleteObject();

	return true;
}

// 设置频标属性，扩展功能
// mkrColor -- 频标颜色
// imkrType -- 频标类型
// nMkrID -- 频标ID
// nWaveID -- 频标跟踪波形的ID
// 返回值：true设置成功，false设置失败
bool CDevGDI::GDI_SetMkrStyleEx(const COLORREF &mkrColor, const int &nMkrType, const int &nMkrID, const int &nWaveID)
{
	if ((nMkrID>-1)&&(nMkrID<I_MKR_NUMBER)&&(nWaveID>-1)&&(nWaveID<I_WAVE_NUM))
	{
		m_imkrType = nMkrType;
		m_mkrColor[nMkrID][nWaveID] = mkrColor;

		return true;
	}

	return false;
}

// 获得频标属性，扩展功能
// mkrColor -- 频标颜色
// imkrType -- 频标类型
// nMkrID -- 频标ID
// nWaveID -- 频标跟踪波形的ID
// 返回值：true设置成功，false设置失败
bool CDevGDI::GDI_GetMkrStyleEx(COLORREF &mkrColor, int &nMkrType, const int &nMkrID, const int &nWaveID)
{
	if ((nMkrID>-1)&&(nMkrID<I_MKR_NUMBER)&&(nWaveID>-1)&&(nWaveID<I_WAVE_NUM))
	{
		nMkrType = m_imkrType;
		mkrColor = m_mkrColor[nMkrID][nWaveID];

		return true;
	}

	return false;
}

// 设置频标文字的颜色
// TextColor -- 频标的文字颜色
// nMkrID -- 频标ID
// nWaveID -- 频标跟踪波形的ID
// 返回值：true设置成功，false设置失败
bool CDevGDI::GDI_SetMkrTextColor(const COLORREF &TextColor, const int &nMkrID, const int &nWaveID)
{
	if ((nMkrID>-1)&&(nMkrID<I_MKR_NUMBER)&&(nWaveID>-1)&&(nWaveID<I_WAVE_NUM))
	{
		m_MkrTextColor[nMkrID][nWaveID] = TextColor;
	}

	return false;
}

// 获得频标文字的颜色
// TextColor -- 频标的文字颜色
// nMkrID -- 频标ID
// nWaveID -- 频标跟踪波形的ID
// 返回值：true读取成功，false读取失败
bool CDevGDI::GDI_GetMkrTextColor(COLORREF &TextColor, const int &nMkrID, const int &nWaveID)
{
	if ((nMkrID>-1)&&(nMkrID<I_MKR_NUMBER)&&(nWaveID>-1)&&(nWaveID<I_WAVE_NUM))
	{
		TextColor = m_MkrTextColor[nMkrID][nWaveID];
	}

	return false;
}

// 初始化报表
// ReportData -- 报表的数据结构
// bDefault -- 是否引导为缺省设置，true引导位缺省设置，则ReportData的数据无效，表报的各种属性由系统进行缺省设置。false自定义设置，ReportData的数据有效
// 返回值：true成功，false失败
bool CDevGDI::GDI_InitReport(const tagREPORT &ReportData, const bool &bDefault /*= true*/)
{
	if (bDefault)
	{
		m_ReportData.bEnableEnd = true;
		m_ReportData.bEnableHeader = true;
		m_ReportData.bEnableTitle = true;
		m_ReportData.dEndX = 0.1;
		m_ReportData.dEndY = 0.9;
		m_ReportData.dHeaderX = 0.1;
		m_ReportData.dHeaderY = 0.2;
		m_ReportData.dTitleX = 0.3;
		m_ReportData.dTitleY = 0.1;
		m_ReportData.dWaveHeight = 0.5;
		m_ReportData.dWaveWidth = 0.8;
		m_ReportData.dWaveX = 0.1;
		m_ReportData.dWaveY = 0.3;
		if (!m_ReportData.EndTextFont.CreateFont(100, 0, 0, 0, FW_NORMAL, false, false, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")))
		{
			return false;
		}
		if (!m_ReportData.HeaderTextFont.CreateFont(100, 0, 0, 0, FW_NORMAL, false, false, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")))
		{
			return false;
		}
		m_ReportData.szEnd = _T("结束：输入报表后面的文字说明。");
		m_ReportData.szHeader = _T("开始位置：输入报表前面的文字说明。");
		m_ReportData.szTitle = _T("测试报表标题头");
		if (!m_ReportData.TitleFont.CreateFont(200, 0, 0, 0, FW_BLACK, false, false, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")))
		{
			return false;
		}
	}
	else
	{
		m_ReportData.bEnableEnd = ReportData.bEnableEnd;
		m_ReportData.bEnableHeader = ReportData.bEnableHeader;
		m_ReportData.bEnableTitle = ReportData.bEnableTitle;
		m_ReportData.dEndX = ReportData.dEndX;
		m_ReportData.dEndY = ReportData.dEndY;
		m_ReportData.dHeaderX = ReportData.dHeaderX;
		m_ReportData.dHeaderY = ReportData.dHeaderY;
		m_ReportData.dTitleX = ReportData.dTitleX;
		m_ReportData.dTitleY = ReportData.dTitleY;
		m_ReportData.dWaveHeight = ReportData.dWaveHeight;
		m_ReportData.dWaveWidth = ReportData.dWaveWidth;
		m_ReportData.dWaveX = ReportData.dWaveX;
		m_ReportData.dWaveY = ReportData.dWaveY;
		memcpy(&m_ReportData.EndTextFont, &ReportData.EndTextFont, sizeof(CFont));;
		memcpy(&m_ReportData.HeaderTextFont, &ReportData.HeaderTextFont, sizeof(CFont));
		m_ReportData.szEnd = ReportData.szEnd;
		m_ReportData.szHeader = ReportData.szHeader;
		m_ReportData.szTitle = ReportData.szTitle;
		memcpy(&m_ReportData.TitleFont, &ReportData.TitleFont, sizeof(CFont));
	}

	return true;
}

// 退出打印报表
void CDevGDI::GDI_ExitReport(void)
{
	m_ReportData.TitleFont.DeleteObject();
	m_ReportData.HeaderTextFont.DeleteObject();
	m_ReportData.EndTextFont.DeleteObject();
}

// 设置报表标题头字体
// pszFont -- 字体
// nFontSize -- 字大小
// nFontWeight -- 字体粗细程度，FW_NORMAL普通，FW_BLACK文字加粗
// 返回值：true成功，false失败
bool CDevGDI::GDI_SetReportTitleFont(const TCHAR *pszFont, const int &nFontSize, const int &nFontWeight)
{
	assert(pszFont!=NULL);
	if (pszFont==NULL)
	{
		return false;
	}

	m_ReportData.TitleFont.DeleteObject();
	if (m_ReportData.TitleFont.CreateFont(nFontSize, 0, 0, 0, nFontWeight, false, false, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, pszFont))
	{
		return true;
	}

	return false;
}

// 设置波形上方文字字体
// pszFont -- 字体
// nFontSize -- 字大小
// 返回值：true成功，false失败
bool CDevGDI::GDI_SetReportHeaderFont(const TCHAR *pszFont, const int &nFontSize)
{
	assert(pszFont!=NULL);
	if (pszFont==NULL)
	{
		return false;
	}

	m_ReportData.HeaderTextFont.DeleteObject();
	if (m_ReportData.HeaderTextFont.CreateFont(nFontSize, 0, 0, 0, FW_NORMAL, false, false, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, pszFont))
	{
		return true;
	}

	return false;
}

// 设置波形下方文字字体
// pszFont -- 字体
// nFontSize -- 字大小
// 返回值：true成功，false失败
bool CDevGDI::GDI_SetReportEndFont(const TCHAR *pszFont, const int &nFontSize)
{
	assert(pszFont!=NULL);
	if (pszFont==NULL)
	{
		return false;
	}

	m_ReportData.EndTextFont.DeleteObject();
	if (m_ReportData.EndTextFont.CreateFont(nFontSize, 0, 0, 0, FW_NORMAL, false, false, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, pszFont))
	{
		return true;
	}

	return false;
}

// 设置报表标题头文字
void CDevGDI::GDI_SetReportTitleText(const TCHAR *pszText)
{
	m_ReportData.szTitle = pszText;
}

// 设置波形前文字
void CDevGDI::GDI_SetReportHeaderText(const TCHAR *pszText)
{
	m_ReportData.szHeader = pszText;
}

// 设置波形后文字
void CDevGDI::GDI_SetReportEndText(const TCHAR *pszText)
{
	m_ReportData.szEnd = pszText;
}

// 设置报表标题头位置
void CDevGDI::GDI_SetReportTitlePos(const double &dXPos, const double &dYPos)
{
	m_ReportData.dTitleX = dXPos;
	m_ReportData.dTitleY = dYPos;
}

// 设置波形前文字位置
void CDevGDI::GDI_SetReportHeaderPos(const double &dXPos, const double &dYPos)
{
	m_ReportData.dHeaderX = dXPos;
	m_ReportData.dHeaderY = dYPos;
}

// 设置波形后文字位置
void CDevGDI::GDI_SetReportEndPos(const double &dXPos, const double &dYPos)
{
	m_ReportData.dEndX = dXPos;
	m_ReportData.dEndY = dYPos;
}

// 设置波形位置
// dXStartPos -- 起始横坐标位置
// dYStartPos -- 起始纵坐标位置
// dXEndPos -- 终止横坐标位置
// dYEndPos -- 终止纵坐标位置
void CDevGDI::GDI_SetReportWavePos(CDC *pDC, CPrintInfo* pInfo, const double &dXStartPos, const double &dYStartPos, const double &dXEndPos,
								   const double &dYEndPos)
{
	m_ReportData.dWaveX = dXStartPos;
	m_ReportData.dWaveY = dYStartPos;
	m_ReportData.dWaveWidth = dXEndPos-dXStartPos;
	m_ReportData.dWaveHeight = dYEndPos-dYStartPos;
	m_rect.left = static_cast<int>(dXStartPos*pInfo->m_rectDraw.Width());
	m_rect.top = static_cast<int>(dYStartPos*pInfo->m_rectDraw.Height());
	m_rect.right = static_cast<int>(dXEndPos*pInfo->m_rectDraw.Width());
	m_rect.bottom = static_cast<int>(dYEndPos*pInfo->m_rectDraw.Height());
}

// 绘制报表文字
void CDevGDI::DrawReportText(CDC *pDC, CPrintInfo* pInfo)
{
	CFont *pBakFont;
	int nXPos = 0;
	int nYPos = 0;

	// Draw Title
	pBakFont = pDC->SelectObject(&m_ReportData.TitleFont);
	nXPos = static_cast<int>(m_ReportData.dTitleX*pInfo->m_rectDraw.Width());
	nYPos = static_cast<int>(m_ReportData.dTitleY*pInfo->m_rectDraw.Height());
	pDC->TextOut(nXPos, nYPos, m_ReportData.szTitle, m_ReportData.szTitle.GetLength());

	// Draw Header
	pDC->SelectObject(&m_ReportData.HeaderTextFont);
	nXPos = static_cast<int>(m_ReportData.dHeaderX*pInfo->m_rectDraw.Width());
	nYPos = static_cast<int>(m_ReportData.dHeaderY*pInfo->m_rectDraw.Height());
	pDC->TextOut(nXPos, nYPos, m_ReportData.szHeader, m_ReportData.szHeader.GetLength());

	// Draw End
	pDC->SelectObject(&m_ReportData.EndTextFont);
	nXPos = static_cast<int>(m_ReportData.dEndX*pInfo->m_rectDraw.Width());
	nYPos = static_cast<int>(m_ReportData.dEndY*pInfo->m_rectDraw.Height());
	pDC->TextOut(nXPos, nYPos, m_ReportData.szEnd, m_ReportData.szEnd.GetLength());

	pDC->SelectObject(pBakFont);
}

// 显示类似8831的坐标
void CDevGDI::GDI_EnableCoor( const bool &bEnableCoor )
{
	m_bEnableCoorText = bEnableCoor;
}

// 显示全部Mkr的函数
void CDevGDI::MkrFunc(const HDC &memDC, const double *pdData, const int &iDataLen, const double *pdData2, const int &nDataLen2, const double *pdData3,
	const int &nDataLen3, const double *pdData4, const int &nDataLen4, const double *pdData5, const int &nDataLen5, const double *pdData6,
	const int &nDataLen6, const double *pdData7, const int &nDataLen7, const double *pdData8, const int &nDataLen8, const double *pdData9,
	const int &nDataLen9, const double *pdData10, const int &nDataLen10, const double *pdData11, const int &nDataLen11, const double *pdData12,
	const int &nDataLen12, const double *pdData13, const int &nDataLen13, const double *pdData14, const int &nDataLen14, const double *pdData15,
	const int &nDataLen15, const double *pdData16, const int &nDataLen16, const double *pdData17, const int &nDataLen17, const double *pdData18,
	const int &nDataLen18, const double *pdData19, const int &nDataLen19, const double *pdData20, const int &nDataLen20)
{
	int i = 0;

	for (i=0; i<I_MKR_NUMBER; i++)
	{
		if (m_bMkr[i])
		{
			if ((iDataLen>0)&&(m_bMkrStatus[i][0]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData, iDataLen, i);
				}
				DrawMkr(memDC, pdData, iDataLen, i, 0);
			}
			if ((nDataLen2>0)&&(m_bMkrStatus[i][1]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData2, nDataLen2, i);
				}
				DrawMkr(memDC, pdData2, nDataLen2, i, 1);
			}
			if ((nDataLen3>0)&&(m_bMkrStatus[i][2]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData3, nDataLen3, i);
				}
				DrawMkr(memDC, pdData3, nDataLen3, i, 2);
			}
			if ((nDataLen4>0)&&(m_bMkrStatus[i][3]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData4, nDataLen4, i);
				}
				DrawMkr(memDC, pdData4, nDataLen4, i, 3);
			}

			if ((nDataLen5>0)&&(m_bMkrStatus[i][4]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData5, nDataLen5, i);
				}
				DrawMkr(memDC, pdData5, nDataLen5, i, 4);
			}

			if ((nDataLen6>0)&&(m_bMkrStatus[i][5]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData6, nDataLen6, i);
				}
				DrawMkr(memDC, pdData6, nDataLen6, i, 5);
			}

			if ((nDataLen7>0)&&(m_bMkrStatus[i][6]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData7, nDataLen7, i);
				}
				DrawMkr(memDC, pdData7, nDataLen7, i, 6);
			}

			if ((nDataLen8>0)&&(m_bMkrStatus[i][7]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData8, nDataLen8, i);
				}
				DrawMkr(memDC, pdData8, nDataLen8, i, 7);
			}

			if ((nDataLen9>0)&&(m_bMkrStatus[i][8]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData9, nDataLen9, i);
				}
				DrawMkr(memDC, pdData9, nDataLen9, i, 8);
			}

			if ((nDataLen10>0)&&(m_bMkrStatus[i][9]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData10, nDataLen10, i);
				}
				DrawMkr(memDC, pdData10, nDataLen10, i, 9);
			}

			if ((nDataLen11>0)&&(m_bMkrStatus[i][10]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData11, nDataLen11, i);
				}
				DrawMkr(memDC, pdData11, nDataLen11, i, 10);
			}

			if ((nDataLen12>0)&&(m_bMkrStatus[i][11]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData12, nDataLen12, i);
				}
				DrawMkr(memDC, pdData12, nDataLen12, i, 11);
			}

			if ((nDataLen13>0)&&(m_bMkrStatus[i][12]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData13, nDataLen13, i);
				}
				DrawMkr(memDC, pdData13, nDataLen13, i, 12);
			}

			if ((nDataLen14>0)&&(m_bMkrStatus[i][13]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData14, nDataLen14, i);
				}
				DrawMkr(memDC, pdData14, nDataLen14, i, 13);
			}

			if ((nDataLen15>0)&&(m_bMkrStatus[i][14]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData15, nDataLen15, i);
				}
				DrawMkr(memDC, pdData15, nDataLen15, i, 14);
			}

			if ((nDataLen16>0)&&(m_bMkrStatus[i][15]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData16, nDataLen16, i);
				}
				DrawMkr(memDC, pdData16, nDataLen16, i, 15);
			}

			if ((nDataLen17>0)&&(m_bMkrStatus[i][16]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData17, nDataLen17, i);
				}
				DrawMkr(memDC, pdData17, nDataLen17, i, 16);
			}

			if ((nDataLen18>0)&&(m_bMkrStatus[i][17]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData18, nDataLen18, i);
				}
				DrawMkr(memDC, pdData18, nDataLen18, i, 17);
			}

			if ((nDataLen19>0)&&(m_bMkrStatus[i][18]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData19, nDataLen19, i);
				}
				DrawMkr(memDC, pdData19, nDataLen19, i, 18);
			}

			if ((nDataLen20>0)&&(m_bMkrStatus[i][19]))
			{
				if (m_bMkrKeepMaxVal)	// 频标跟踪峰值
				{
					FindMaxWaveVal(pdData20, nDataLen20, i);
				}
				DrawMkr(memDC, pdData20, nDataLen20, i, 19);
			}
		}
	}
}

// 设置Limit Line Text的开关
// bEnable -- 显示开关
// nID -- limit线的ID
// 返回值：成功true，失败false
bool CDevGDI::GDI_EnableLimitLineText(const bool &bEnable, const int &nID)
{
	assert((nID>=0)&&(nID<I_LIMITLINE_NUMBER));
	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	m_LimitLineTag[nID].m_bEnableText = bEnable;

	return true;
}

// 读取Limit Line Text的开关
// bEnable -- 显示开关
// nID -- limit线的ID
// 返回值：成功true，失败false
bool CDevGDI::GDI_IsLimitLineTextEnable(bool &bEnable, const int &nID)		// 读取Limit Line Text的开关
{
	assert((nID>=0)&&(nID<I_LIMITLINE_NUMBER));
	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	bEnable = m_LimitLineTag[nID].m_bEnableText;

	return true;
}

// 设置Limit线的自定义文字
// pszStr -- 自定义文字内容
// nID -- Limit线的ID
// 返回值：true成功，false失败
bool CDevGDI::GDI_SetManualLimitText(const TCHAR *pszStr, const int &nID)
{
	assert((nID>=0)&&(nID<I_LIMITLINE_NUMBER));
	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}
	if (pszStr==NULL)
	{
		return false;
	}

	_tcscpy(m_LimitLineTag[nID].m_czText, pszStr);

	return true;
}

// 读取Limit线的自定义文字
// pszStr -- 自定义文字内容
// nID -- Limit线的ID
// 返回值：true成功，false失败
bool CDevGDI::GDI_GetManualLimitText(TCHAR *pszStr, const int &nID)
{
	assert((nID>=0)&&(nID<I_LIMITLINE_NUMBER));
	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}
	if (pszStr==NULL)
	{
		return false;
	}

	_tcscpy(pszStr, m_LimitLineTag[nID].m_czText);

	return true;
}

// 设置Limit线的自定义文字开关
// bEnable -- 自定义文字的开关，true开，false关
// nID -- Limit线的ID
// 返回值：true成功，false失败
bool CDevGDI::GDI_EnableLimitManualText(const bool &bEnable, const int &nID)
{
	assert((nID>=0)&&(nID<I_LIMITLINE_NUMBER));
	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	m_LimitLineTag[nID].m_bManualText = bEnable;

	return true;
}

// 读取Limit线的自定义文字开关
// bEnable -- 自定义文字的开关，true开，false关
// nID -- Limit线的ID
// 返回值：true成功，false失败
bool CDevGDI::GDI_IsLimitManualTextEnable(bool &bEnable, const int &nID)
{
	assert((nID>=0)&&(nID<I_LIMITLINE_NUMBER));
	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	bEnable = m_LimitLineTag[nID].m_bManualText;

	return true;
}

// 设置Limit线的步进值
// dStep -- 步进值
void CDevGDI::GDI_SetLimitStep(const double &dStep)
{
	m_dLimitStep = dStep;
}

// 获得Limit线的步进值
// 返回值：步进值
double CDevGDI::GDI_GetLimitStep(void)
{
	return m_dLimitStep;
}

// 移动参考线,方向参考DEV_MOVE的定义
// nDirection -- 参考线移动方向
void CDevGDI::GDI_MoveLimitLine(const int &nDirection)
{
	switch (nDirection)
	{
	case DEV_LIMIT_UP:
		if ((m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMaxVal<m_dEndY)&&(m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMinVal<m_dEndY))
		{
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMaxVal += m_dLimitStep;
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMinVal += m_dLimitStep;
		}
		break;
	case DEV_LIMIT_DOWN:
		if ((m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMaxVal>m_dStartY)&&(m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMinVal>m_dStartY))
		{
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMaxVal -= m_dLimitStep;
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMinVal -= m_dLimitStep;
		}
		break;
	case DEV_LIMIT_LEFT:
		if ((m_LimitLineTag[m_nActiveLimit].m_dzLimitLineStartVal>m_dStartX)&&(m_LimitLineTag[m_nActiveLimit].m_dzLimitLineEndVal>m_dStartX))
		{
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineStartVal -= m_dLimitStep;
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineEndVal -= m_dLimitStep;
		}
		break;
	case DEV_LIMIT_RIGHT:
		if ((m_LimitLineTag[m_nActiveLimit].m_dzLimitLineStartVal<m_dEndX)&&(m_LimitLineTag[m_nActiveLimit].m_dzLimitLineEndVal<m_dEndX))
		{
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineStartVal += m_dLimitStep;
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineEndVal += m_dLimitStep;
		}
		break;
	default:
		break;
	}
}

// 用鼠标移动参考线，参考线跟踪鼠标位置移动
// nXPos -- 输入横坐标
// nYPos -- 输入纵坐标
void CDevGDI::GDI_MoveLimitLine(const int &nXPos, const int &nYPos, const int &nType)
{
	int nYSpan = m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop;
	int nXSpan = m_rect.right-m_rect.left-m_iBorderGridRight-m_iBorderGridLeft;
	double dYPos = (m_dEndY-m_dStartY)*(nYSpan-nYPos+m_iBorderGridTop)/nYSpan;
	double dXPos = (m_dEndX-m_dStartX)*(nXPos-m_iBorderGridLeft)/nXSpan;
	double dOffset = 0.0;

	switch (nType)
	{
	case LIMIT_MOVE_UPDOWN:
		dOffset = (m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMaxVal-m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMinVal)*0.5;
		if ((m_dEndY>dYPos+dOffset)&&(m_dStartY-0.00000001<dYPos-dOffset))
		{
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMaxVal = dYPos+dOffset;
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMinVal = dYPos-dOffset;
		}
		break;
	case LIMIT_MOVE_LEFTRIGHT:
		dOffset = (m_LimitLineTag[m_nActiveLimit].m_dzLimitLineEndVal-m_LimitLineTag[m_nActiveLimit].m_dzLimitLineStartVal)*0.5;
		if ((m_dEndX>dXPos+dOffset)&&(m_dStartX-0.00000001<dXPos-dOffset))
		{
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineStartVal = dXPos-dOffset;
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineEndVal = dXPos+dOffset;
		}
		break;
	case LIMIT_MOVE_ALL:
		dOffset = (m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMaxVal-m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMinVal)*0.5;
		if ((m_dEndY>dYPos+dOffset)&&(m_dStartY-0.00000001<dYPos-dOffset))
		{
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMaxVal = dYPos+dOffset;
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineMinVal = dYPos-dOffset;
		}
		dOffset = (m_LimitLineTag[m_nActiveLimit].m_dzLimitLineEndVal-m_LimitLineTag[m_nActiveLimit].m_dzLimitLineStartVal)*0.5;
		if ((m_dEndX>dXPos+dOffset)&&(m_dStartX-0.00000001<dXPos-dOffset))
		{
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineStartVal = dXPos-dOffset;
			m_LimitLineTag[m_nActiveLimit].m_dzLimitLineEndVal = dXPos+dOffset;
		}
		break;
	default:
		break;
	}
}

// 设置当前活动的Limit线
// nID -- Limit线的ID
// 返回值：true成功，false失败
bool CDevGDI::GDI_SetActiveLimitLine(const int &nID)
{
	assert((nID>=0)&&(nID<I_LIMITLINE_NUMBER));
	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	m_nActiveLimit = nID;

	return true;
}

// 获得当前活动的Limit线
// 返回值：当前活动Limit线的ID
int CDevGDI::GDI_GetActiveLimitLine(void)
{
	return m_nActiveLimit;
}

// 设置Limit Line文字的位置
// nLocation -- 文字的位置，参考DEV_KEEP的定义
// 返回值：true设置成功，false设置失败
bool CDevGDI::GDI_SetLimitTextDock(const int &nLocation, const int &nID /*=0*/)
{
	assert((nID>-1)&&(nID<I_LIMITLINE_NUMBER));
	assert((nLocation>=0)&&(nLocation<DEV_KEEP_DEFINE_END));
	if ((nLocation<0)||(nLocation>=DEV_KEEP_DEFINE_END))
	{
		return false;
	}
	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	m_nLimitTextDock[nID] = nLocation;

	return true;
}

// 设置实时绘图文字的字体
// pszFont -- 字体
// nFontSize -- 字体大小
bool CDevGDI::GDI_SetFont(TCHAR *pszFont, int &nFontSize)
{
	assert(pszFont!=NULL);
	if (pszFont==NULL)
	{
		return false;
	}

	_tcscpy(m_czTextFont, pszFont);
	m_nTextFontSize = nFontSize;

	return true;
}

// 设置鼠标绘制波形的起始点，由LButtonDown事件程序调用
// nXStartPos -- 鼠标横坐标位置
// nYStartPos -- 鼠标纵坐标位置
// pdData -- 波形数据
// nDataLen --当前波形的数据长度
// nWaveID -- 波形数据ID
// 返回值：true设置成功，false设置失败
bool CDevGDI::GDI_SetMouseWaveLineStart(const int &nXStartPos, const int &nYStartPos, double *pdData, const int &nDataLen, const int &nWaveID)
{
	assert(nDataLen>0);
	assert((nWaveID>-1)&&(nWaveID<I_WAVE_NUM));

	if (nDataLen<1)
	{
		return false;
	}
	if ((nWaveID<0)||(nWaveID>=I_WAVE_NUM))
	{
		return false;
	}

	if (nXStartPos<m_rect.left+m_iBorderGridLeft)
	{
		m_nMouseLineStartX = 0;
	}
	else if (nXStartPos>m_rect.right-m_iBorderGridRight)
	{
		m_nMouseLineStartX = nDataLen-1;
	}
	else
	{
		m_nMouseLineStartX = (nXStartPos-m_rect.left-m_iBorderGridLeft)*nDataLen/(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight);
	}

	if (nYStartPos<m_rect.top+m_iBorderGridTop)
	{
		m_dMouseLineStartY = m_dStartY;
	}
	else if (nYStartPos>m_rect.bottom-m_iBorderGridBottom)
	{
		m_dMouseLineStartY = m_dEndY;
	}
	else
	{
		m_dMouseLineStartY = (m_dEndY-m_dStartY)*(m_rect.bottom-m_rect.top-m_iBorderGridBottom-1-nYStartPos)
			/(m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)+m_dStartY;
		pdData[m_nMouseLineStartX] = m_dMouseLineStartY;
	}

	return true;
}

// 鼠标绘制波形的涂鸦函数，绘制的波形曲线由鼠标滑过的轨迹来决定
// nXEndPos -- 鼠标横坐标位置
// nYEndPos -- 鼠标纵坐标位置
// pdData -- 波形数据
// nDataLen -- 波形数据长度
// nWaveID -- 波形的ID
// 返回值：true设置成功，false设置失败
bool CDevGDI::GDI_SetMouseWavePixel(const int &nXEndPos, const int &nYEndPos, double *pdData, const int &nDataLen, const int &nWaveID)
{
	int i = 0;
	int nMax = 0;
	int nMouseLineEndX = 0;
	double dMouseLineEndY = 0.0;

	assert(nDataLen>0);
	assert((nWaveID>-1)&&(nWaveID<I_WAVE_NUM));

	if (nDataLen<1)
	{
		return false;
	}
	if ((nWaveID<0)||(nWaveID>=I_WAVE_NUM))
	{
		return false;
	}

	if (nXEndPos<m_rect.left+m_iBorderGridLeft)
	{
		nMouseLineEndX = 0;
	}
	else if (nXEndPos>m_rect.right-m_iBorderGridRight)
	{
		nMouseLineEndX = nDataLen;
	}
	else
	{
		nMouseLineEndX = (nXEndPos-m_rect.left-m_iBorderGridLeft)*nDataLen/(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight);
	}

	if (nYEndPos<m_rect.top+m_iBorderGridTop)
	{
		dMouseLineEndY = m_dStartY;
	}
	else if (nYEndPos>m_rect.bottom-m_iBorderGridBottom)
	{
		dMouseLineEndY = m_dEndY;
	}
	else
	{
		dMouseLineEndY = (m_dEndY-m_dStartY)*(m_rect.bottom-m_rect.top-m_iBorderGridBottom-1-nYEndPos)
			/(m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)+m_dStartY;
		if (nMouseLineEndX>m_nMouseLineStartX)
		{
			i = m_nMouseLineStartX;
			nMax = nMouseLineEndX;
		}
		else
		{
			i = nMouseLineEndX;
			nMax = m_nMouseLineStartX;
		}
		for (; i<nMax; i++)
		{
			pdData[i] = dMouseLineEndY;
		}
	}

	m_nMouseLineStartX = nMouseLineEndX;
	m_dMouseLineStartY = dMouseLineEndY;

	return true;
}

// 绘制星座图的波形数据
// memDC -- 内存DC
// pnData -- 星座图数据结构体
// nDataLen -- 星座图点数
// bManualColor -- 星座图数据自定义颜色开关
// 返回值：true执行成功，false执行失败
bool CDevGDI::DrawQamData(const HDC &memDC, const struct tagCoordinate *pnData, const int &nDataLen,
	const bool &bManualColor)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int nXPos = 0;
	int nYPos = 0;

	switch (m_iLineWidth[0])
	{
	case N_DRAW_SMALL_POINT:	// 星座图画细点
	case I_DRAW_LINE:
		if (bManualColor)	// 自定义星座图点的颜色
		{
			for (i=0; i<nDataLen; i++)	// 画细点
			{
				nXPos = GetWaveLineX(pnData[i].nXCoord);
				nYPos =  m_rect.bottom-m_iBorderGridBottom+m_iBorderGridTop-1-GetWaveLineY(pnData[i].nYCoord);
				if ((nXPos<m_rect.right-m_rect.left-m_iBorderGridRight)
					&&(nXPos>m_rect.left+m_iBorderGridLeft)
					&&(nYPos<m_rect.bottom-m_rect.top-m_iBorderGridBottom)
					&&(nYPos>m_rect.top+m_iBorderGridTop))
				{
					SetPixel(memDC, nXPos, nYPos, pnData[i].PointColor);
				}
			}
		}
		else		// 使用类属性波形曲线的颜色
		{
			for (i=0; i<nDataLen; i++)	// 画细点
			{
				nXPos = GetWaveLineX(pnData[i].nXCoord);
				nYPos =  m_rect.bottom-m_iBorderGridBottom+m_iBorderGridTop-1-GetWaveLineY(pnData[i].nYCoord);
				if ((nXPos<m_rect.right-m_rect.left-m_iBorderGridRight)
					&&(nXPos>m_rect.left+m_iBorderGridLeft)
					&&(nYPos<m_rect.bottom-m_rect.top-m_iBorderGridBottom)
					&&(nYPos>m_rect.top+m_iBorderGridTop))
				{
					SetPixel(memDC, nXPos, nYPos, m_LineColor[0]);
				}
			}
		}
		break;

	case I_DRAW_BIG_POINT:	// 星座图画粗点
		if (bManualColor)	// 自定义星座图点的颜色
		{
			for (i=0; i<nDataLen; i++)	// 画细点
			{
				nXPos = GetWaveLineX(pnData[i].nXCoord);
				nYPos =  m_rect.bottom-m_iBorderGridBottom+m_iBorderGridTop-1-GetWaveLineY(pnData[i].nYCoord);
				if ((nXPos<m_rect.right-m_rect.left-m_iBorderGridRight)
					&&(nXPos>m_rect.left+m_iBorderGridLeft)
					&&(nYPos<m_rect.bottom-m_rect.top-m_iBorderGridBottom)
					&&(nYPos>m_rect.top+m_iBorderGridTop))
				{
					for (j=nXPos-1; j<nXPos+2; j++)
					{
						for (k=nYPos-1; k<nYPos+2; k++)
						{
							SetPixel(memDC, j, k, pnData[i].PointColor);
						}
					}
				}
			}
		}
		else		// 使用类属性波形曲线的颜色
		{
			for (i=0; i<nDataLen; i++)	// 画细点
			{
				nXPos = GetWaveLineX(pnData[i].nXCoord);
				nYPos =  m_rect.bottom-m_iBorderGridBottom+m_iBorderGridTop-1-GetWaveLineY(pnData[i].nYCoord);
				if ((nXPos<m_rect.right-m_rect.left-m_iBorderGridRight)
					&&(nXPos>m_rect.left+m_iBorderGridLeft)
					&&(nYPos<m_rect.bottom-m_rect.top-m_iBorderGridBottom)
					&&(nYPos>m_rect.top+m_iBorderGridTop))
				{
					for (j=nXPos-1; j<nXPos+2; j++)
					{
						for (k=nYPos-1; k<nYPos+2; k++)
						{
							SetPixel(memDC, j, k, m_LineColor[0]);
						}
					}
				}
			}
		}
		break;

	default:
		break;
	}

	return true;
}

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
bool CDevGDI::GDI_DrawByLimit(const double *pdCurrent, const int &nCurrent, const double *pdMax, const int &nMax,
	const double *pdMin, const int &nMin, const double *pdAverage, const int &nAverage,
	const double *pdUpLimit1, const int &nUpLimit1, const double *pdDownLimit1, const int &nDownLimit1,
	const double *pdUpLimit2, const int &nUpLimit2, const double *pdDownLimit2, const int &nDownLimit2,
	const double *pdUpLimit3, const int &nUpLimit3, const double *pdDownLimit3, const int &nDownLimit3,
	const double *pdUpLimit4, const int &nUpLimit4, const double *pdDownLimit4, const int &nDownLimit4,
	const double *pdUpLimit5, const int &nUpLimit5, const double *pdDownLimit5, const int &nDownLimit5, bool *bzEnable)
{
	CFont myFont;
	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right,
		m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, m_brCross);// 备份当前画刷
	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);
	myFont.CreatePointFont(m_nTextFontSize, m_czTextFont);
	SelectObject(memDC, myFont);

	DrawLineByLimit(memDC, pdCurrent, nCurrent, pdMax, nMax, pdMin, nMin, pdAverage, nAverage, pdUpLimit1, nUpLimit1, pdDownLimit1, nDownLimit1, pdUpLimit2, nUpLimit2,
		pdDownLimit2, nDownLimit2, pdUpLimit3, nUpLimit3, pdDownLimit3, nDownLimit3, pdUpLimit4, nUpLimit4, pdDownLimit4, nDownLimit4, pdUpLimit5, nUpLimit5,
		pdDownLimit5, nDownLimit5, bzEnable);
	if (m_ucGridType==DEV_GRID_CLASSICAL)
	{
		DrawGrid(memDC);
	}
	else
	{
		DrawGridSpectrum(memDC);
	}
	DrawCoor( memDC );
	DrawGridCenterRound(memDC);
	DrawGridCenterPoint(memDC);
	DrawLimitLine(memDC);

	// 绘制mkr
	MkrFunc(memDC, pdCurrent, nCurrent, pdMax, 0/*nMax*/, pdMin, 0/*nMin*/, pdAverage, 0/*nAverage*/,
		pdUpLimit1, 0/*nUpLimit1*/,
		pdDownLimit1, 0/*nDownLimit1*/,
		pdUpLimit2, 0/*nUpLimit2*/,
		pdDownLimit2, 0/*nDownLimit2*/,
		pdUpLimit3, 0/*nUpLimit3*/,
		pdDownLimit3, 0/*nDownLimit3*/,
		pdUpLimit4, 0/*nUpLimit4*/,
		pdDownLimit4, 0/*nDownLimit4*/,
		pdUpLimit5, 0/*nUpLimit5*/,
		pdDownLimit5, 0/*nDownLimit5*/, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0);
	DrawXText(memDC);	// 显示横坐标值
	DrawYText(memDC);	// 显示纵坐标值
	ShowManualText(memDC);

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, memDC, m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(mybitmap);
	DeleteDC(memDC);
	myFont.DeleteObject();

	return true;
}

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
bool CDevGDI::DrawLineByLimit(HDC &memDC, const double *pdCurrent, const int &nCurrent, const double *pdMax, const int &nMax,
	const double *pdMin, const int &nMin, const double *pdAverage, const int &nAverage,
	const double *pdUpLimit1, const int &nUpLimit1, const double *pdDownLimit1, const int &nDownLimit1,
	const double *pdUpLimit2, const int &nUpLimit2, const double *pdDownLimit2, const int &nDownLimit2,
	const double *pdUpLimit3, const int &nUpLimit3, const double *pdDownLimit3, const int &nDownLimit3,
	const double *pdUpLimit4, const int &nUpLimit4, const double *pdDownLimit4, const int &nDownLimit4,
	const double *pdUpLimit5, const int &nUpLimit5, const double *pdDownLimit5, const int &nDownLimit5, const bool *bzPriority)
{
	int i = 0;

	m_dWavePixNum = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	if (nCurrent>0)
	{
		for (i=1; i<nCurrent; i++)
		{
			GetLineColorByLimit(memDC,
				static_cast<double>(i-1), static_cast<double>(i),	// X
				pdCurrent[i-1], pdCurrent[i],	// current
				pdUpLimit1[i-1], pdUpLimit1[i],	// up limit1
				pdUpLimit2[i-1], pdUpLimit2[i],	// up limit2
				pdUpLimit3[i-1], pdUpLimit3[i],	// up limit3
				pdUpLimit4[i-1], pdUpLimit4[i],	// up limit4
				pdUpLimit5[i-1], pdUpLimit5[i],	// up limit5
				pdDownLimit1[i-1], pdDownLimit1[i],	// down limit1
				pdDownLimit2[i-1], pdDownLimit2[i],	// down limit2
				pdDownLimit3[i-1], pdDownLimit3[i],	// down limit3
				pdDownLimit4[i-1], pdDownLimit4[i],	// down limit4
				pdDownLimit5[i-1], pdDownLimit5[i],	// down limit5
				bzPriority, nCurrent, i, m_LineColor[0]);
		}
	}

	if ((nMax>0)&&(nMax==nCurrent))
	{
		for (i=1; i<nMax; i++)
		{
			GetLineColorByLimit(memDC,
				static_cast<double>(i-1), static_cast<double>(i),	// X
				pdMax[i-1], pdMax[i],	// Max
				pdUpLimit1[i-1], pdUpLimit1[i],	// up limit1
				pdUpLimit2[i-1], pdUpLimit2[i],	// up limit2
				pdUpLimit3[i-1], pdUpLimit3[i],	// up limit3
				pdUpLimit4[i-1], pdUpLimit4[i],	// up limit4
				pdUpLimit5[i-1], pdUpLimit5[i],	// up limit5
				pdDownLimit1[i-1], pdDownLimit1[i],	// down limit1
				pdDownLimit2[i-1], pdDownLimit2[i],	// down limit2
				pdDownLimit3[i-1], pdDownLimit3[i],	// down limit3
				pdDownLimit4[i-1], pdDownLimit4[i],	// down limit4
				pdDownLimit5[i-1], pdDownLimit5[i],	// down limit5
				bzPriority, nMax, i, m_LineColor[0]);
		}
	}

	if ((nMin>0)&&(nMin==nCurrent))
	{
		for (i=1; i<nMin; i++)
		{
			GetLineColorByLimit(memDC,
				static_cast<double>(i-1), static_cast<double>(i),	// X
				pdMin[i-1], pdMin[i],	// Min
				pdUpLimit1[i-1], pdUpLimit1[i],	// up limit1
				pdUpLimit2[i-1], pdUpLimit2[i],	// up limit2
				pdUpLimit3[i-1], pdUpLimit3[i],	// up limit3
				pdUpLimit4[i-1], pdUpLimit4[i],	// up limit4
				pdUpLimit5[i-1], pdUpLimit5[i],	// up limit5
				pdDownLimit1[i-1], pdDownLimit1[i],	// down limit1
				pdDownLimit2[i-1], pdDownLimit2[i],	// down limit2
				pdDownLimit3[i-1], pdDownLimit3[i],	// down limit3
				pdDownLimit4[i-1], pdDownLimit4[i],	// down limit4
				pdDownLimit5[i-1], pdDownLimit5[i],	// down limit5
				bzPriority, nMin, i, m_LineColor[0]);
		}
	}

	if ((nAverage>0)&&(nAverage==nCurrent))
	{
		for (i=1; i<nAverage; i++)
		{
			GetLineColorByLimit(memDC,
				static_cast<double>(i-1), static_cast<double>(i),	// X
				pdAverage[i-1], pdAverage[i],	// Min
				pdUpLimit1[i-1], pdUpLimit1[i],	// up limit1
				pdUpLimit2[i-1], pdUpLimit2[i],	// up limit2
				pdUpLimit3[i-1], pdUpLimit3[i],	// up limit3
				pdUpLimit4[i-1], pdUpLimit4[i],	// up limit4
				pdUpLimit5[i-1], pdUpLimit5[i],	// up limit5
				pdDownLimit1[i-1], pdDownLimit1[i],	// down limit1
				pdDownLimit2[i-1], pdDownLimit2[i],	// down limit2
				pdDownLimit3[i-1], pdDownLimit3[i],	// down limit3
				pdDownLimit4[i-1], pdDownLimit4[i],	// down limit4
				pdDownLimit5[i-1], pdDownLimit5[i],	// down limit5
				bzPriority, nAverage, i, m_LineColor[0]);
		}
	}

	return true;
}

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
bool CDevGDI::GetLineColorByLimit(HDC &memDC, const double &dXStart, const double &dXEnd, const double &dYStart, const double &dYEnd,
	const double &dUpLimit1Start, const double &dUpLimit1End, const double &dUpLimit2Start, const double &dUpLimit2End,
	const double &dUpLimit3Start, const double &dUpLimit3End, const double &dUpLimit4Start, const double &dUpLimit4End,
	const double &dUpLimit5Start, const double &dUpLimit5End,
	const double &dDownLimit1Start, const double &dDownLimit1End, const double &dDownLimit2Start, const double &dDownLimit2End,
	const double &dDownLimit3Start, const double &dDownLimit3End, const double &dDownLimit4Start, const double &dDownLimit4End,
	const double &dDownLimit5Start, const double &dDownLimit5End, const bool *pbzPriority, const int &nDataLen, const int &nID, const COLORREF &LineColor)
{
	HPEN hPen;
	HPEN hOldPen;	// 备份当前画笔设备
	int i = 0;
	int nzXPos[12] = {0};//横坐标曲线点
	int nzYPos[12] = {0};//纵坐标曲线点
	int nPoint = 0;
	COLORREF Color[12] = {0};
	BYTE cPoint[12] = {0};
	bool bRet = false;
	BYTE uType = LIMIT_NORMAL;	// 交叉类型，具体详见LIMIT_TYPE_DEF定义
	BYTE uDegree = 0;	// 向上

	if (dYStart<dYEnd)
	{
		uDegree = 1;
	}
	// 确定越界或回界
	if (((dYStart<dUpLimit1Start)&&(dYEnd>dUpLimit1End))||((dYStart<dUpLimit2Start)&&(dYEnd>dUpLimit2End))||((dYStart<dUpLimit3Start)&&(dYEnd>dUpLimit3End))
		||((dYStart<dUpLimit4Start)&&(dYEnd>dUpLimit4End))||((dYStart<dUpLimit5Start)&&(dYEnd>dUpLimit5End))||((dYStart<dDownLimit1Start)&&(dYEnd>dDownLimit1End))
		||((dYStart<dDownLimit2Start)&&(dYEnd>dDownLimit2End))||((dYStart<dDownLimit3Start)&&(dYEnd>dDownLimit3End))
		||((dYStart<dDownLimit4Start)&&(dYEnd>dDownLimit4End))||((dYStart<dDownLimit5Start)&&(dYEnd>dDownLimit5End)))	// 越界交叉
	{
		uType = LIMIT_OVERFLOW;
	}
	else if (((dYStart>dUpLimit1Start)&&(dYEnd<dUpLimit1End))||((dYStart>dUpLimit2Start)&&(dYEnd<dUpLimit2End))||((dYStart>dUpLimit3Start)&&(dYEnd<dUpLimit3End))
		||((dYStart>dUpLimit4Start)&&(dYEnd<dUpLimit4End))||((dYStart>dUpLimit5Start)&&(dYEnd<dUpLimit5End))||((dYStart>dDownLimit1Start)&&(dYEnd<dDownLimit1End))
		||((dYStart>dDownLimit2Start)&&(dYEnd<dDownLimit2End))||((dYStart>dDownLimit3Start)&&(dYEnd<dDownLimit3End))
		||((dYStart>dDownLimit4Start)&&(dYEnd<dDownLimit4End))||((dYStart>dDownLimit5Start)&&(dYEnd<dDownLimit5End)))	// 回界交叉
	{
		uType = LIMIT_UNDERBELOW;
	}

	// 确定起始点的坐标和颜色
	nzXPos[nPoint] = GetWaveLineX(m_dWavePixNum, nDataLen, dXStart);
	nzYPos[nPoint] = GetWaveLineY(dYStart);
	Color[nPoint] = LineColor;
	if ((LIMIT_OVERFLOW==uType)||(1==uDegree))
	{
		cPoint[nPoint] = FindPointColorOver(Color[nPoint], dYStart, dUpLimit1Start, dDownLimit1Start, dUpLimit2Start, dDownLimit2Start, dUpLimit3Start,
			dDownLimit3Start, dUpLimit4Start, dDownLimit4Start, dUpLimit5Start, dDownLimit5Start, pbzPriority);
	}
	else
	{
		cPoint[nPoint] = FindPointColor(Color[nPoint], dYStart, dUpLimit1Start, dDownLimit1Start, dUpLimit2Start, dDownLimit2Start, dUpLimit3Start, dDownLimit3Start,
			dUpLimit4Start, dDownLimit4Start, dUpLimit5Start, dDownLimit5Start, pbzPriority);
	}
	nPoint ++;

	if (LIMIT_UNDERBELOW==uType)
	{
		i = 0;
		if (pbzPriority[i])		// Up 1
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dUpLimit1Start, dUpLimit1End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET+1];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i ++;

		if (pbzPriority[i])		// Down 1
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dDownLimit1Start, dDownLimit1End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET+1];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i ++;

		if (pbzPriority[i])		// Up 2
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dUpLimit2Start, dUpLimit2End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET+1];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i ++;

		if (pbzPriority[i])		// Down 2
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dDownLimit2Start, dDownLimit2End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET+1];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i ++;

		if (pbzPriority[i])		// Up 3
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dUpLimit3Start, dUpLimit3End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET+1];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i ++;

		if (pbzPriority[i])		// Down 3
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dDownLimit3Start, dDownLimit3End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET+1];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i ++;

		if (pbzPriority[i])		// Up 4
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dUpLimit4Start, dUpLimit4End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET+1];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i ++;

		if (pbzPriority[i])		// Down 4
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dDownLimit4Start, dDownLimit4End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET+1];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i ++;

		if (pbzPriority[i])		// Up 5
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dUpLimit5Start, dUpLimit5End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET+1];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i ++;

		if (pbzPriority[i])		// Down 5
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dDownLimit5Start, dDownLimit5End, nDataLen, nID))
			{
				Color[nPoint] = LineColor;
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i ++;
	}
	else if (LIMIT_OVERFLOW==uType)
	{
		i = 9;
		if (pbzPriority[i])		// Down 5
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dDownLimit5Start, dDownLimit5End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i --;

		if (pbzPriority[i])		// Up 5
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dUpLimit5Start, dUpLimit5End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i --;

		if (pbzPriority[i])		// Down 4
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dDownLimit4Start, dDownLimit4End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i --;

		if (pbzPriority[i])		// Up 4
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dUpLimit4Start, dUpLimit4End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i --;

		if (pbzPriority[i])		// Down 3
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dDownLimit3Start, dDownLimit3End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i --;

		if (pbzPriority[i])		// Up 3
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dUpLimit3Start, dUpLimit3End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i --;

		if (pbzPriority[i])		// Down 2
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dDownLimit2Start, dDownLimit2End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i --;

		if (pbzPriority[i])		// Up 2
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dUpLimit2Start, dUpLimit2End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i --;

		if (pbzPriority[i])		// Down 1
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dDownLimit1Start, dDownLimit1End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i --;

		if (pbzPriority[i])		// Up 1
		{
			if (FindCrossPoint(nzXPos[nPoint], nzYPos[nPoint], dXStart, dYStart, dXEnd, dYEnd, dUpLimit1Start, dUpLimit1End, nDataLen, nID))
			{
				Color[nPoint] = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
				cPoint[nPoint] = i;
				nPoint ++;
			}
		}
		i --;
	}

	nzXPos[nPoint] = GetWaveLineX(m_dWavePixNum, nDataLen, dXEnd);
	nzYPos[nPoint] = GetWaveLineY(dYEnd);
	if (LIMIT_OVERFLOW==uType)
	{
		cPoint[nPoint] = FindPointColorOver(Color[nPoint], dYStart, dUpLimit1Start, dDownLimit1Start, dUpLimit2Start, dDownLimit2Start, dUpLimit3Start,
			dDownLimit3Start, dUpLimit4Start, dDownLimit4Start, dUpLimit5Start, dDownLimit5Start, pbzPriority);
	}
	else
	{
		cPoint[nPoint] = FindPointColor(Color[nPoint], dYEnd, dUpLimit1End, dDownLimit1End, dUpLimit2End, dDownLimit2End, dUpLimit3End, dDownLimit3End, dUpLimit4End,
			dDownLimit4End, dUpLimit5End, dDownLimit5End, pbzPriority);
	}

	for (i=0; i<nPoint; i++)
	{
		hPen = CreatePen(PS_SOLID, m_iLineWidth[0], Color[i]);
		hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份当前画笔设备
		MoveToEx(memDC, nzXPos[i], nzYPos[i], NULL);
		LineTo(memDC, nzXPos[i+1], nzYPos[i+1]);
		SelectObject(memDC, hOldPen);
		DeleteObject(hPen);
	}

	return bRet;
}

// 根据当前波形数据ID计算出当前绘图横坐标值
// dWavePixNum -- 波形绘图区的宽度
// nDataLen -- 曲线总数据量
// dDataID -- 当前曲线的数据id, 插值描述方式
// return value -- 绘图曲线的横坐标值
int CDevGDI::GetWaveLineX(const double &dWavePixNum, const int &nDataLen, const double &dDataID)
{
	return m_rect.left+m_iBorderGridLeft+static_cast<int>(0.5+dDataID*dWavePixNum/(nDataLen-1));;
}

// 找到波形于合格线的交叉点坐标
// nXPos, nYPos -- 交叉点的横纵坐标值
// dStartX, dStartY, dEndX, dEndY -- 波形的起始横、纵坐标和终止横、纵坐标
// dEndLimitX, dEndLimitY -- 合格线的起始横、纵坐标和终止横、纵坐标值
// nDataLen -- 波形数据长度
// nID -- 波形ID
// 返回值：true存在交叉点，false不存在交叉点
bool CDevGDI::FindCrossPoint(int &nXPos, int &nYPos, const double &dStartX, const double &dStartY, const double &dEndX, const double &dEndY, const double &dStartLimitY,
	const double &dEndLimitY, const int &nDataLen, const int &nID)
{
	double dTemp = 0.0;
	bool bRet = false;

	if ((dStartY<dStartLimitY)&&(dEndY>dEndLimitY)||(dStartY>dStartLimitY)&&(dEndY<dEndLimitY))		// 判断是否存在交叉点
	{
		// 开始找交叉点
		if (fabs(dEndX-dStartX)>0.0000000001)	// 斜率不为0的处理方式
		{
			dTemp = (dStartLimitY-dStartY)/((dEndY-dStartY-dEndLimitY+dStartLimitY)*(dEndX-dStartX));
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen, dTemp+dStartX);
			nYPos = GetWaveLineY((dEndY-dStartY)/(dEndX-dStartX)*dTemp+dStartY);
		}
		else	// 斜率为0的处理方式
		{
			if (fabs(dEndLimitY-dEndY)<0.000000001)	// 值接近与终止点
			{
				dTemp = 1.0;
			}
			else	// 值接近于中间点或起始点
			{
				dTemp = fabs((dEndY-dEndLimitY)/(dStartLimitY-dStartY));
			}
			nXPos = GetWaveLineX(m_dWavePixNum, nDataLen, dTemp+nID);
			nYPos = GetWaveLineY(dEndLimitY);
		}

		bRet = true;
	}

	return bRet;
}

// 根据合格线找到当前点应该设置的颜色
// Color -- 当前点的颜色
// dYPos -- 当前点的纵坐标值
// ..... -- 所有合格线的值
// pbzPriority -- 合格线的使能
// 返回值：true存在合格线颜色，false不存在合格线颜色，颜色设置失败
char CDevGDI::FindPointColor(COLORREF &Color, const double &dYPos, const double &dUpLimit1Y, const double &dDownLimit1Y, const double &dUpLimit2Y,
	const double &dDownLimit2Y, const double &dUpLimit3Y, const double &dDownLimit3Y, const double &dUpLimit4Y, const double &dDownLimit4Y,
	const double &dUpLimit5Y, const double &dDownLimit5Y, const bool *pbzPriority)
{
	int i = 9;
	char cRet = 0;

	if (pbzPriority[i])
	{
		if (dDownLimit5Y<dYPos)		// 0, 下溢5
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dUpLimit5Y<dYPos)		// 1, 上溢5
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dDownLimit4Y<dYPos)		// 2, 下溢4
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dUpLimit4Y<dYPos)		// 3, 上溢4
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dDownLimit3Y<dYPos)		// 4, 下溢3
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dUpLimit3Y<dYPos)		// 5, 上溢3
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dDownLimit2Y<dYPos)		// 6, 下溢2
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dUpLimit2Y<dYPos)		// 7, 上溢2
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dDownLimit1Y<dYPos)		// 8, 下溢1
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dUpLimit1Y<dYPos)		// 9, 上溢1
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}

	return cRet;
}

// 根据合格线找到当前点应该设置的颜色，回界交叉
// Color -- 当前点的颜色
// dYPos -- 当前点的纵坐标值
// ..... -- 所有合格线的值
// pbzPriority -- 合格线的使能
// 返回值：越过合格线的ID
char CDevGDI::FindPointColorOver(COLORREF &Color, const double &dYPos, const double &dUpLimit1Y, const double &dDownLimit1Y, const double &dUpLimit2Y,
	const double &dDownLimit2Y, const double &dUpLimit3Y, const double &dDownLimit3Y, const double &dUpLimit4Y, const double &dDownLimit4Y,
	const double &dUpLimit5Y, const double &dDownLimit5Y, const bool *pbzPriority)
{
	int i = 9;
	char cRet = 0;

	if (pbzPriority[i])
	{
		if (dDownLimit5Y<dYPos+0.000000001)		// 0, 下溢5
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dUpLimit5Y<dYPos+0.000000001)		// 1, 上溢5
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dDownLimit4Y<dYPos+0.000000001)		// 2, 下溢4
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dUpLimit4Y<dYPos+0.000000001)		// 3, 上溢4
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dDownLimit3Y<dYPos+0.000000001)		// 4, 下溢3
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dUpLimit3Y<dYPos+0.000000001)		// 5, 上溢3
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dDownLimit2Y<dYPos+0.000000001)		// 6, 下溢2
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dUpLimit2Y<dYPos+0.000000001)		// 7, 上溢2
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dDownLimit1Y<dYPos+0.000000001)		// 8, 下溢1
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}
	i --;

	if (pbzPriority[i])
	{
		if (dUpLimit1Y<dYPos+0.000000001)		// 9, 上溢1
		{
			cRet = i;
			Color = m_LineColor[i+N_LIMIT_COLOR_ID_OFFSET];
		}
	}

	return cRet;
}

// 按照坐标的实际值设置Mkr的横坐标位置
// nID -- Mkr的序号
// dXVal -- 设置横坐标的值
// nDataLen -- 当前波形的数据长度
// 返回值：true成功，false失败，由于输入值超出了当前坐标范围引起
bool CDevGDI::GDI_SetMkrX(const int &nID, const double &dXVal, const int &nDataLen)
{
	int nTemp = 0;

	assert((nID>-1)&&(nID<I_MKR_NUMBER)&&(nDataLen>0));
	if ((nID<0)||(nID>=I_MKR_NUMBER)||(nDataLen<1))
	{
		return false;
	}

	//尔洪春 同前，减去开始点2009/9月
	nTemp = static_cast<int>((dXVal-m_dFullStartX)/(m_dFullEndX-m_dFullStartX)*nDataLen+m_nWaveStartPos+0.5);
	if (nTemp<m_nWaveStartPos)
	{
		m_iMkrValue[nID] = m_nWaveStartPos;
	}
	else if (nTemp>=nDataLen+m_nWaveStartPos)
	{
		m_iMkrValue[nID] = nDataLen+m_nWaveStartPos-1;
	}
	else
	{
		m_iMkrValue[nID] = nTemp;
	}

	return true;
}

// 频标横坐标跟踪保持开关
// bEnable -- 跟踪横坐标开关，true：跟踪值，false：跟踪位置
void CDevGDI::GDI_EnableMkrKeepX(const bool &bEnable)
{
	m_bMkrAutoKeepX = bEnable;
}

// 获得频标跟踪横坐标开关
bool CDevGDI::GDI_IsMkrKeepX(void)
{
	return m_bMkrAutoKeepX;
}

// 设置纵坐标2的坐标范围
// dStart -- 纵坐标起始值
// dEnd -- 纵坐标终止值
void CDevGDI::GDI_SetSpanYSpecial(const double &dStart, const double &dEnd)
{
	m_dSpecialStartY = dStart;
	m_dSpecialEndY = dEnd;
}

// 获取纵坐标2的坐标范围
// dStart -- 纵坐标起始值
// dEnd -- 纵坐标终止值
void CDevGDI::GDI_GetSpanYSpecial(double &dStart, double &dEnd)
{
	dStart = m_dSpecialStartY;
	dEnd = m_dSpecialEndY;
}

//设置波形起始位置的点数 尔洪春/9/9
void CDevGDI::GDI_SetWaveStartPos(const int &iWaveStartPos)
{
	m_nWaveStartPos = iWaveStartPos;
}

// 激活第二个纵坐标系
// bEnable -- 激活开关，true激活，false关闭
void CDevGDI::GDI_Enable2ndY(const bool &bEnable)
{
	int i = 0;

	if (bEnable)
	{
		if (!m_bEnable2ndY)
		{
			m_iBorderGridRight += 20;
		}
	}
	else
	{
		for (; i<I_WAVE_NUM; i++)
		{
			m_uczWaveDockY[i] = Y_LEFT_COORDINATE_DOCK;	// 使用左侧坐标系
		}
		if (m_bEnable2ndY)
		{
			m_iBorderGridRight -= 20;
		}
	}

	m_bEnable2ndY = bEnable;
}

// 第二个纵坐标系是否已激活
// 返回值：激活开关，true激活，false关闭
bool CDevGDI::GDI_Is2ndYEnable(void)
{
	return m_bEnable2ndY;
}

// 设置波形使用坐标系
// nWaveID -- 波形ID
// ucDock -- 使用坐标系，详见Y_COORDINATE_DEF的定义
// 返回值：true成功，false失败
bool CDevGDI::GDI_SetWaveDock(const int &nWaveID, const BYTE &ucDock)
{
	assert((nWaveID>-1)&&(nWaveID<I_WAVE_NUM));
	if ((nWaveID<0)||(nWaveID>=I_WAVE_NUM))
	{
		return false;
	}

	m_uczWaveDockY[nWaveID] = ucDock;

	return true;
}

// 读取波形使用坐标系
// nWaveID -- 波形ID
// ucDock -- 返回使用坐标系，详见Y_COORDINATE_DEF的定义
// 返回值：true成功，false失败
bool CDevGDI::GDI_GetWaveDock(const int &nWaveID, BYTE &ucDock)
{
	assert((nWaveID>-1)&&(nWaveID<I_WAVE_NUM));
	if ((nWaveID<0)||(nWaveID>=I_WAVE_NUM))
	{
		return false;
	}

	ucDock = m_uczWaveDockY[nWaveID];

	return true;
}

// 绘制光谱图波形数据
// pdData -- 波形数据
// nWaveNum -- 波形总共有多少条
// nDataLen -- 每条波形数据长度
// pColor -- 光谱图颜色表
// pdLevel -- 光谱图幅度门限值, 其中第0个值是最低值，此后显示波形采样值大于门限值中最大的门限颜色
// nColorNum -- 光谱图颜色值
// 返回值：true成功，false失败
bool CDevGDI::GDI_DrawSpectrogram(const double *pdData, const int &nWaveNum, const int &nDataLen, const COLORREF *pColor, const double *pdLevel, const int &nColorNum)
{
	CFont myFont;
	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right,
		m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, m_brCross);// 备份当前画刷

	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);
	myFont.CreatePointFont(m_nTextFontSize, m_czTextFont);
	SelectObject(memDC, myFont);

	m_dWavePixNum = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	if(m_dWavePixNum < 1.0)
	{
		m_dWavePixNum = 1.0;
	}
	// Draw Spectrogram
	DrawSpectrogram(memDC, pdData, nWaveNum, nDataLen, pColor, pdLevel, nColorNum);

	if (m_ucGridType==DEV_GRID_CLASSICAL)
	{
		DrawGrid(memDC);
	}
	else
	{
		DrawGridSpectrum(memDC);
	}
	DrawCoor( memDC );
	DrawGridCenterRound(memDC);
	DrawGridCenterPoint(memDC);
	DrawLimitLine(memDC);
	DrawXText(memDC);	// 显示横坐标值
	DrawYText(memDC);	// 显示纵坐标值

	if (m_MouseLine.nLButtonDown==DEVGDI_MOUSELINE_DRAW)
	{
		DrawMouseRect(memDC);
	}
	ShowManualText(memDC);
	DrawSpecgView(memDC, pColor, pdLevel, nColorNum);
	DrawSpectrogramMkr(memDC, nDataLen, nWaveNum);	// 绘制光谱图Mkr

	BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, memDC, m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(mybitmap);
	DeleteDC(memDC);
	myFont.DeleteObject();

	return true;
}

// 设置游标线的颜色
// color -- 游标线的颜色
void CDevGDI::GDI_SetMkrLineColor(const COLORREF &color)
{
	m_MkrLineColor = color;
}

// 读取游标线的颜色
// 返回值：游标线的颜色
COLORREF CDevGDI::GDI_GetMkrLineColor(void)
{
	return m_MkrLineColor;
}

// 绘制光谱图波形图
// memDC -- 绘图内存DC
// pdData -- 波形数据
// nWaveNum -- 波形条数
// nDataLen -- 每条波形的点数
// pColor -- 颜色表
// pdLevel -- 幅度表
// nColorNum -- 幅度颜色表的数量
// 返回值：true成功，false失败，可能是由于内存申请失败造成
bool CDevGDI::DrawSpectrogram(HDC &memDC, const double *pdData, const int &nWaveNum, const int &nDataLen, const COLORREF *pColor, const double *pdLevel,
	const int &nColorNum)
{
	HPEN hOldPen;	// 备份当前画笔设备
	HBRUSH hOldBrush;
	LOGBRUSH pLogBrush[N_SPECTROGRAM_COLOR_NUM];
	HBRUSH pBrush[N_SPECTROGRAM_COLOR_NUM];	// 画刷表
	HPEN phPen[N_SPECTROGRAM_COLOR_NUM];	// 画笔表
	int i = 0;
	int j = 0;
	int k = 0;
	int id = 0;
	int nStartY = 0;
	int nEndY = 0;
	int nStartX = 0;
	int nEndX = 0;
	// 每个光谱波形高度
	double dWaveHeight = (static_cast<double>(m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop))/nWaveNum;
	// 每个光谱点的宽度
	double dWaveWidth = (static_cast<double>(m_rect.right-m_rect.left-m_iBorderGridRight-m_iBorderGridLeft))/nDataLen;

	if ((pLogBrush==NULL)||(pBrush==NULL)||(phPen==NULL))	// 颜色表输入合法监测
	{
		return false;
	}
	if ((nColorNum<0)||(nColorNum>=N_SPECTROGRAM_COLOR_NUM))	// 颜色表数量最大值监测
	{
		return false;
	}

	for (i=0; i<nColorNum; i++)	// 初始化颜色表
	{
		pLogBrush[i].lbColor = pColor[i];
		pLogBrush[i].lbHatch = HS_CROSS;
		pLogBrush[i].lbStyle = BS_SOLID;
		pBrush[i] = CreateBrushIndirect(&pLogBrush[i]);
		phPen[i] = CreatePen(PS_SOLID, 1, pColor[i]);
	}

	// 备份画笔
	hOldPen = (HPEN)SelectObject(memDC, phPen[0]);
	hOldBrush = (HBRUSH)SelectObject(memDC, pBrush[0]);
	// 绘制光谱图
	nStartY = m_rect.bottom-m_iBorderGridBottom;
	for (i=0; i<nWaveNum; i++)
	{
		nStartX = m_rect.left+m_iBorderGridLeft;
		nEndY = m_rect.bottom-m_iBorderGridBottom-static_cast<int>(dWaveHeight*(i+1));
		for (j=0; j<nDataLen; j++)
		{
			nEndX = m_rect.left+m_iBorderGridLeft+static_cast<int>(dWaveWidth*(j+1));
			id = i*nDataLen+j;
			if (D_SPECTROGRAM_NONE_VALUE+1<pdData[id])	// 空值判断
			{
				for (k=nColorNum-1; k>-1; k--)
				{
					if (pdData[id]>pdLevel[k])
					{
						SelectObject(memDC, phPen[k]);	// 根据幅度值选择颜色
						SelectObject(memDC, pBrush[k]);
						break;
					}
				}
				Rectangle(memDC, nStartX, nStartY, nEndX, nEndY);
			}
			nStartX = nEndX;
		}
		nStartY = nEndY;
	}

	for (i=0; i<nColorNum; i++)		// 卸载颜色表
	{
		DeleteObject(phPen[i]);
		DeleteObject(pBrush[i]);
	}
	SelectObject(memDC, hOldBrush);	// 回复画笔
	SelectObject(memDC, hOldPen);

	return true;
}

// 设置光谱图Mkr开关状态
// bXEnable -- 横向mkr开关
// bYEnable -- 纵向Mkr开关
void CDevGDI::GDI_EnableSpectrogramMkr(const bool &bXEnable, const bool &bYEnable)
{
	m_bSpectrogramMkrX = bXEnable;
	m_bSpectrogramMkrY = bYEnable;
}

// 读取光谱图Mkr开关状态
// bXEnable -- 横向mkr开关
// bYEnable -- 纵向Mkr开关
void CDevGDI::GDI_IsSpectrogramMkrEnable(bool &bXEnable, bool &bYEnable)
{
	bXEnable = m_bSpectrogramMkrX;
	bYEnable = m_bSpectrogramMkrY;
}

// 设置光谱图mkr颜色
// color -- mkr颜色
void CDevGDI::GDI_SetSpectrogramMkrColor(const COLORREF &color)
{
	m_SpectrogramMkrColor = color;
}

// 读取光谱图mkr颜色
// 返回值：mkr颜色
COLORREF CDevGDI::GDI_GetSpectrogramMkrColor(void)
{
	return m_SpectrogramMkrColor;
}

// 绘制光谱图的Mkr
// memDC -- 绘图内存DC
// nDataLen -- 每场波形数据长度
// nWaveNum -- 光谱图波形数量
void CDevGDI::DrawSpectrogramMkr(HDC &memDC, const int &nDataLen, const int &nWaveNum)
{
	HPEN hOldPen;
	HPEN hPen;
	int nXPos = 0;
	int nYPos = 0;
	double dWavePerPix = 0.0;

	hPen = CreatePen(PS_SOLID, 3, m_SpectrogramMkrColor);
	hOldPen = (HPEN)SelectObject(memDC, hPen);	// 备份画笔

	if (m_bSpectrogramMkrX)	// 绘制横向mkr
	{
		// 两采样点间的宽度
		dWavePerPix = (static_cast<double>(m_rect.right-m_rect.left-m_iBorderGridRight-m_iBorderGridLeft))/nDataLen;
		// 获得mkr横坐标值
		nXPos = m_iBorderGridLeft+m_rect.left+static_cast<int>(dWavePerPix*m_nSpectrogramMkrX+dWavePerPix*0.5);
		// 绘制mkr
		MoveToEx(memDC, nXPos, m_rect.top+m_iBorderGridTop-20, NULL);
		LineTo(memDC, nXPos, m_rect.top+m_iBorderGridTop);
		LineTo(memDC, nXPos-5, m_rect.top+m_iBorderGridTop-10);
		MoveToEx(memDC, nXPos, m_rect.top+m_iBorderGridTop, NULL);
		LineTo(memDC, nXPos+5, m_rect.top+m_iBorderGridTop-10);
	}

	if (m_bSpectrogramMkrY)	// 绘制纵向mkr
	{
		// 两采场波形间的高度
		dWavePerPix = static_cast<double>(m_rect.bottom-m_rect.top-m_iBorderGridBottom-m_iBorderGridTop)/nWaveNum;
		// 获得mkr纵坐标值
		nYPos = m_rect.bottom-m_iBorderGridBottom-static_cast<int>(dWavePerPix*m_nSpectrogramMkrY+dWavePerPix*0.5);
		// 绘制mkr
		MoveToEx(memDC, m_rect.right-m_iBorderGridRight+20, nYPos, NULL);
		LineTo(memDC, m_rect.right-m_iBorderGridRight, nYPos);
		LineTo(memDC, m_rect.right-m_iBorderGridRight+10, nYPos-5);
		MoveToEx(memDC, m_rect.right-m_iBorderGridRight, nYPos, NULL);
		LineTo(memDC, m_rect.right-m_iBorderGridRight+10, nYPos+5);
	}

	DeleteObject(hPen);
	SelectObject(memDC, hOldPen);
}

// 设置光谱图Mkr位置
// nXPos -- 横坐标位置
// nYPos -- 纵坐标位置
// nWaveLen -- 波形数量
// nDataLen -- 光谱图中，每场波形的数据长度
void CDevGDI::GDI_SetSpectrogramMkrPos(const int &nXPos, const int &nYPos, const int &nWaveLen, const int &nDataLen)
{
	if (m_ucUseSpectrogramMkr==SPECTROGRAM_MKR_X)	// 移动横坐标mkr
	{
		if ((nYPos>m_rect.top)&&(nYPos<m_rect.top+m_iBorderGridTop+20))
		{
			// 设置横坐标mkr位置，单位是采样点的序号
			m_nSpectrogramMkrX = nDataLen*(nXPos-m_iBorderGridLeft)/(m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight);
			if (m_nSpectrogramMkrX<0)
			{
				m_nSpectrogramMkrX = 0;
			}
			else if (m_nSpectrogramMkrX>nDataLen-1)
			{
				m_nSpectrogramMkrX = nDataLen-1;
			}
		}
	}
	else if (m_ucUseSpectrogramMkr==SPECTROGRAM_MKR_Y)	// 移动纵坐标mkr
	{
		if ((nXPos>m_rect.right-m_iBorderGridRight-20)&&(nXPos<m_rect.right))
		{
			// 设置纵坐标mkr位置，单位是采样点的序号
			m_nSpectrogramMkrY = nWaveLen*(m_rect.bottom-nYPos-m_iBorderGridBottom)/(m_rect.bottom-m_rect.top-m_iBorderGridTop-m_iBorderGridBottom);
			if (m_nSpectrogramMkrY<0)
			{
				m_nSpectrogramMkrY = 0;
			}
			else if (m_nSpectrogramMkrY>nWaveLen-1)
			{
				m_nSpectrogramMkrY = nWaveLen-1;
			}
		}
	}
}

// 读取光谱图Mkr位置
// uType -- 返回数据类型，详见SPECTROGRAM_MKR定义
// nXPos -- 横坐标位置
// nYPos -- 纵坐标位置
// dzOutWave -- 返回频谱或统计数据
// dzInputWave -- 输入光谱图数据
// nWaveNum -- 光谱图波形数量
// nDataLen -- 每天波形的数据长度
void CDevGDI::GDI_GetSpectrogramMkrPos(const BYTE &uType, int &nXID, int &nYID, double *dzOutWave, const double *dzInputWave, const int &nWaveNum,
	const int &nDataLen)
{
	int i = 0;

	nXID = m_nSpectrogramMkrX;
	nYID = m_nSpectrogramMkrY;

	if ((nDataLen==0)||(dzInputWave==NULL)||(nWaveNum==0))
	{
		dzOutWave = NULL;
	}
	else
	{
		switch (uType)
		{
		case SPECTROGRAM_MKR_X:
			for (i=0; i<nWaveNum; i++)
			{
				dzOutWave[i] = dzInputWave[nDataLen*i+m_nSpectrogramMkrX];
			}
			break;
		case SPECTROGRAM_MKR_Y:
			for (i=0; i<nDataLen; i++)
			{
				dzOutWave[i] = dzInputWave[m_nSpectrogramMkrY*nDataLen+i];
			}
//			memcpy(dzOutWave, dzInputWave+sizeof(double)*m_nSpectrogramMkrY*nDataLen, nDataLen*sizeof(double));
			break;
		default:
			break;
		}
	}
}

// 选择使用光谱图的游标
// ucType -- 被使用的游标，详见SPECTROGRAM_MKR定义
void CDevGDI::GDI_UseSpectrogramMkr(const BYTE &ucType)
{
	m_ucUseSpectrogramMkr = ucType;
}

// 获得光谱图游标的使用状况
// 返回值：光谱图游标的使用状况，详见SPECTROGRAM_MKR定义
BYTE CDevGDI::GDI_GetSpectrogramMkrUse(void)
{
	return m_ucUseSpectrogramMkr;
}

// 移动光谱图光标
// ucDirection -- 移动方向，详见MKR_MOVE定义
// nWaveLen -- 波形数量
// nDataLen -- 光谱图中，每场波形的数据长度
// 返回值：true成功，false失败
bool CDevGDI::GDI_MoveSpectrogramMkr(const BYTE &ucDirection, const int &nWaveNum, const int &nDataLen)
{
	bool bRet = true;

	switch (ucDirection)
	{
	case MKR_MOVE_UP:
		if ((m_ucUseSpectrogramMkr==SPECTROGRAM_MKR_Y)&&(m_nSpectrogramMkrY<nWaveNum-1))
		{
			m_nSpectrogramMkrY ++;
		}
		break;
	case MKR_MOVE_DOWN:
		if ((m_ucUseSpectrogramMkr==SPECTROGRAM_MKR_Y)&&(m_nSpectrogramMkrY>0))
		{
			m_nSpectrogramMkrY --;
		}
		break;
	case MKR_MOVE_LEFT:
		if ((m_ucUseSpectrogramMkr==SPECTROGRAM_MKR_X)&&(m_nSpectrogramMkrX>0))
		{
			m_nSpectrogramMkrX --;
		}
		break;
	case MKR_MOVE_RIGHT:
		if ((m_ucUseSpectrogramMkr==SPECTROGRAM_MKR_X)&&(m_nSpectrogramMkrX<nDataLen-1))
		{
			m_nSpectrogramMkrX ++;
		}
		break;
	default:
		bRet = false;
		break;
	}

	return bRet;
}

// 保存光谱图图片
// pszFileName -- 被保存的文件路径
// pdData -- 波形数据
// nWaveNum -- 波形总共有多少条
// nDataLen -- 每条波形数据长度
// pColor -- 光谱图颜色表
// pdLevel -- 光谱图幅度门限值, 其中第0个值是最低值，此后显示波形采样值大于门限值中最大的门限颜色
// nColorNum -- 光谱图颜色值
// 返回值：true成功，false失败
bool CDevGDI::GDI_SaveSpectrogramPic(const TCHAR *pszFileName, const double *pdData, const int &nWaveNum, const int &nDataLen, const COLORREF *pColor,
	const double *pdLevel, const int &nColorNum)
{
	CImage myImage;
	CFont myFont;
	HDC memDC = CreateCompatibleDC(m_hdc);	// 绘图内存DC
	// 当前位图设备
	HBITMAP mybitmap = CreateCompatibleBitmap(m_hdc, m_rect.right,
		m_rect.bottom);
	// 备份当前位图设备
	m_OldBitmap = (HBITMAP)SelectObject(memDC, (HBITMAP)mybitmap);
	HBRUSH OldBrush = (HBRUSH)SelectObject(memDC, m_brCross);// 备份当前画刷

	FillRect(memDC, &m_rect, m_brBackground);
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, m_TextColor);
	myFont.CreatePointFont(m_nTextFontSize, m_czTextFont);
	SelectObject(memDC, myFont);

	m_dWavePixNum = m_rect.right-m_rect.left-m_iBorderGridLeft-m_iBorderGridRight;
	if(m_dWavePixNum < 1.0)
	{
		m_dWavePixNum = 1.0;
	}
	// Draw Spectrogram
	DrawSpectrogram(memDC, pdData, nWaveNum, nDataLen, pColor, pdLevel, nColorNum);

	if (m_ucGridType==DEV_GRID_CLASSICAL)
	{
		DrawGrid(memDC);
	}
	else
	{
		DrawGridSpectrum(memDC);
	}
	DrawCoor( memDC );
	DrawGridCenterRound(memDC);
	DrawGridCenterPoint(memDC);
	DrawLimitLine(memDC);
	DrawXText(memDC);	// 显示横坐标值
	DrawYText(memDC);	// 显示纵坐标值

	if (m_MouseLine.nLButtonDown==DEVGDI_MOUSELINE_DRAW)
	{
		DrawMouseRect(memDC);
	}
	ShowManualText(memDC);
	DrawSpectrogramMkr(memDC, nDataLen, nWaveNum);	// 绘制光谱图Mkr

	myImage.Attach(mybitmap);
	myImage.Save(pszFileName);	// save bitmap
	//BitBlt(m_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, memDC, m_rect.left, m_rect.top, SRCCOPY);

	DeleteObject(mybitmap);
	DeleteDC(memDC);
	myFont.DeleteObject();

	return true;
}

// 设置波形文字说明
// nID -- 波形ID
// pczText -- 说明文字
// color -- 文字颜色
// bShow -- 是否显示文字，true显示，false隐藏
// 返回值：true设置成功，false设置失败
bool CDevGDI::GDI_SetMultiText(const int &nID, const TCHAR *pczText, const COLORREF &color, const bool &bShow)
{
	assert((nID>=0)&&(nID<I_WAVE_NUM));
	if ((nID<0)||(nID>=I_WAVE_NUM))
	{
		return false;
	}

	m_MultiText[nID].szMultiLineText = pczText;
	m_MultiText[nID].TextColor = color;
	m_MultiText[nID].bEnableView = bShow;

	return true;
}

// 绘制自定义多行文字
void CDevGDI::DrawMultiText(const HDC &memDC)
{
	int i = 0;
	int nCount = 0;
	SIZE size;
	COLORREF DefaultTextColor = GetTextColor(memDC);

	for (; i<I_WAVE_NUM; i++)
	{
		if (m_MultiText[i].bEnableView)
		{
			GetTextExtentPoint32(memDC, m_MultiText[i].szMultiLineText, m_MultiText[i].szMultiLineText.GetLength(),
				&size);
			break;
		}
	}

	for (; i<I_WAVE_NUM; i++)
	{
		if (m_MultiText[i].bEnableView)
		{
			SetTextColor(memDC, m_MultiText[i].TextColor);
			TextOut(memDC, m_rect.right-m_iBorderGridRight-(m_rect.right-m_rect.left-m_iBorderGridRight-m_iBorderGridLeft)*3/16,
				m_rect.top+m_iBorderGridTop+size.cy*nCount+2,
				m_MultiText[i].szMultiLineText, m_MultiText[i].szMultiLineText.GetLength());
			nCount ++;
		}
	}

	SetTextColor(memDC, DefaultTextColor);
}

// 设置光谱图文字说明开关
// bEnable -- 文字说明开关，true开，false关
void CDevGDI::GDI_EnableSpecgView(const bool &bEnable)
{
	m_bEnableSpecgView = bEnable;
}

// 读取光谱图文字说明开关
// 返回值: true开, false关
bool CDevGDI::GDI_IsSpecgViewEnable(void)
{
	return m_bEnableSpecgView;
}

// 绘制光谱图文字
// memDC -- 绘图内存DC
// pColor -- 颜色表
// pdLevel -- 幅度表
// nColorNum -- 幅度颜色表的数量
void CDevGDI::DrawSpecgView(HDC &memDC, const COLORREF *pColor, const double *pdLevel, const int &nColorNum)
{
	if (nColorNum<1)
	{
		return;
	}

	int i = 0;
	int nXPos = 0;
	int nYPos = 0;
	SIZE size;
	COLORREF DefaultTextColor = GetTextColor(memDC);
	TCHAR czShow[20] = {_T("   <")};
	TCHAR czTemp[10];
	TCHAR czLast[10];
	LOGBRUSH myLogBrush;

	myLogBrush.lbColor = pColor[0];
	myLogBrush.lbHatch = HS_CROSS;
	myLogBrush.lbStyle = BS_SOLID;

	HBRUSH myBrush = CreateBrushIndirect(&myLogBrush);
	HPEN hOldPen = (HPEN)SelectObject(memDC, myBrush);	// 备份当前画笔设备
	HPEN hPen = CreatePen(PS_SOLID, 1, pColor[0]);

	hOldPen = (HPEN)SelectObject(memDC, hPen);// 备份当前画笔设备
	
	_itot(static_cast<int>(pdLevel[1]), czTemp, 10);
	_tcscat(czShow, czTemp);
	GetTextExtentPoint32(memDC, czShow, _tcslen(czShow), &size);
	
	for (i=0; i<nColorNum-2; i++)
	{
		nXPos = m_rect.right-m_rect.left-m_iBorderGridRight+24;
		nYPos = m_rect.bottom-m_rect.top-m_iBorderGridBottom-size.cy*(i+1);
		Rectangle(memDC, nXPos, nYPos, nXPos+size.cy, nYPos+size.cy);	// 绘制光谱颜色表

		_tcscpy(czLast, czTemp);
		_itot(static_cast<int>(pdLevel[i+2]), czTemp, 10);
		SetTextColor(memDC, pColor[i]);
		TextOut(memDC, nXPos+size.cy, nYPos, czShow, _tcslen(czShow));	// 绘制光谱颜色表说明
		_tcscpy(czShow, czLast);
		_tcscat(czShow, _T("-"));
		_tcscat(czShow, czTemp);

		DeleteObject(myBrush);
		DeleteObject(hPen);
		myLogBrush.lbColor = pColor[i+1];
		hPen = CreatePen(PS_SOLID, 1, pColor[i+1]);
		myBrush = CreateBrushIndirect(&myLogBrush);
		SelectObject(memDC, myBrush);
		SelectObject(memDC, hPen);
	}
	// 倒数第二个数
	nXPos = m_rect.right-m_rect.left-m_iBorderGridRight+24;
	nYPos = m_rect.bottom-m_rect.top-m_iBorderGridBottom-size.cy*(i+1);
	Rectangle(memDC, nXPos, nYPos, nXPos+size.cy, nYPos+size.cy);
	SetTextColor(memDC, pColor[i]);
	TextOut(memDC, nXPos+size.cy, nYPos, czShow, _tcslen(czShow));

	// 最后一个数
	i ++;
	DeleteObject(myBrush);
	DeleteObject(hPen);
	myLogBrush.lbColor = pColor[i];
	hPen = CreatePen(PS_SOLID, 1, pColor[i]);
	myBrush = CreateBrushIndirect(&myLogBrush);
	SelectObject(memDC, myBrush);
	SelectObject(memDC, hPen);
	nXPos = m_rect.right-m_rect.left-m_iBorderGridRight+24;
	nYPos = m_rect.bottom-m_rect.top-m_iBorderGridBottom-size.cy*(i+1);
	Rectangle(memDC, nXPos, nYPos, nXPos+size.cy, nYPos+size.cy);

	_tcscpy(czShow, _T("   >"));
	_tcscat(czShow, czTemp);
	SetTextColor(memDC, pColor[i]);
	nXPos = m_rect.right-m_rect.left-m_iBorderGridRight+24;
	nYPos = m_rect.bottom-m_rect.top-m_iBorderGridBottom-size.cy*(i+1);
	TextOut(memDC, nXPos+size.cy, nYPos, czShow, _tcslen(czShow));

	// 光谱说明标题
	SetTextColor(memDC, DefaultTextColor);
	TextOut(memDC, nXPos, nYPos-size.cy, m_szYDepartment, _tcslen(m_szYDepartment));

	SelectObject(memDC, hOldPen);	// 释放资源
	DeleteObject(myBrush);
	DeleteObject(hPen);
}

// 设置Limit Line的属性
// LimitLineColor -- 当前Limit Line的颜色
// nLineWidth -- 当前LImit Line的线宽
// nID -- Limit Line 的 ID
// 返回值：true成功，false失败
bool CDevGDI::GDI_SetLimitLineStyle(const COLORREF &LimitLineColor, const int &nLineWidth, const int &nID)
{
	return GDI_SetLimitLineColor(LimitLineColor, nID, nLineWidth);
}

// 读取Limit Line的属性
// LimitLineColor -- 当前Limit Line的颜色
// nLineWidth -- 当前LImit Line的线宽
// nID -- Limit Line 的 ID
// 返回值：true成功，false失败
bool CDevGDI::GDI_GetLimitLineStyle(COLORREF &LimitLineColor, int &nLineWidth, const int &nID)
{
	assert((nID>-1)&&(nID<I_LIMITLINE_NUMBER));
	if ((nID<0)||(nID>=I_LIMITLINE_NUMBER))
	{
		return false;
	}

	LimitLineColor = m_LimitLineTag[nID].m_LimitLineColor;
	nLineWidth = m_LimitLineTag[nID].m_nLineWidth;

	return true;
}
