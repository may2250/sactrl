// deskland 自定义可复用类, 版本1.4.8
// 作者：deskland@msn.com
// 最终修改日期：2008-02-28
// history: 2008-02-28 1.4		增加TimeToStrFull功能

#pragma once
#pragma warning (disable:4267)
#pragma warning (disable:4996)

class Cdeskland
{
public:
	// 将设置组从字符串中提取出来保存在double数组中 (ASCII)
	// pszSource——被分析的字符串
	// pdzArray——被解析出来的数组
	// pszInsulate——字串分隔符
	// return value——数组长度
	int DevGetArrayConfig(const char* pszSource, double* pdzArray, const char* pszInsulate);
	// 将设置组从字符串中提取出来保存在double数组中  (UNICODE)
	// pszSource——被分析的字符串
	// pdzArray——被解析出来的数组
	// pszInsulate——字串分隔符
	// return value——数组长度
	int DevGetArrayConfig(const wchar_t* pszSource, double* pdzArray, const wchar_t* pszInsulate);
	// 将字符串转换成日期型
	// tTime -- 被转换的日期类型
	// pszTimeStr -- 时间字符串
	// iTimeType -- 转换类型，0 未定, 1 2002-2-22 0:0:0
	// 返回值：true成功，false 失败
	bool DevStrToTimeFull(SYSTEMTIME &tTime, const TCHAR *pszTimeStr, const int &iTimeType);
	// 将字符串转换成日期型
	// tTime -- 被转换的日期类型
	// pszTimeStr -- 时间字符串
	// iTimeType -- 转换类型，0 00:00:00, 1 未定
	bool DevStrToTime(SYSTEMTIME &tTime, const TCHAR *pszTimeStr,
		const int &iTimeType);
	// 比较时间顺序,
	// 返回值: 0时间相同，<0原时间晚于目标时间，>0原时间前于目标时间
	// bEnableYYMMDD: true:比较年月日, false:不比较年月日
	int DevCompareTwoTime(const SYSTEMTIME &SourceTime, const SYSTEMTIME &TarTime,
		const bool &bEnableYYMMDD = false);
	// 计算当前月份的天数
	BYTE DevCalculateMonth(const SYSTEMTIME &LocalTime);
	// 计算偏移时间
	// StartTime -- 开始时间
	// EndTime -- 结束时间
	// return value: 偏移时间，单位秒
	int DevEscapeTimeCalculate(const SYSTEMTIME &StartTime,
		const SYSTEMTIME &EndTime);
	// 计算偏移时间
	// EscapeTime -- 偏移时间
	// StartTime -- 开始时间
	// EndTime -- 结束时间
	// return value: true 正时间， false 负时间
	bool DevEscapeTimeCalculate(SYSTEMTIME &EscapeTime,
		const SYSTEMTIME &StartTime, const SYSTEMTIME &EndTime);
	int DevGetDaysInMonth(SYSTEMTIME &tTime);	// 得到当前月份的天数
	// 根据原时间和偏移时间得到新的时间
	// tSource -- 原时间
	// tNewTime -- 计算得到的新时间
	// nEscape -- 偏移时间
	// ucType -- 计算类型，0--毫秒，1--秒，2--分钟，3--小时，4--日，5--月，6--年
	void DevEscapeTime(const SYSTEMTIME &tSource, SYSTEMTIME &tNewTime, const int nEscape,
		const unsigned char &ucType);
	// 时间偏移计算，
	// tTime -- 时间结构, 给出原时间，得到偏移时间
	// iEscapeSecond -- 时间偏移的数量，单位秒
	// bAbs -- 时间选项，true增加时间，false减少时间
	void DevEscapeTimeCalculate(SYSTEMTIME &tTime, const int &iEscapeSecond,
		const bool &bAbs);
	// Convert date time to string, the user can see mode
	// pszTime 被转换后的字符串
	// tTime 输入的时间结构
	// iType 转换类型，0 -- 00:00:00, 1 -- 2004-3-31 22:00:32,
	//		2 -- SQL date 02/20/2004, 3 -- 2004-03-09
	//		4 -- SQL DateTime 02/20/2004 22:00:32
	//		5 -- 中文时间格式 2006年5月19日
	void TimeToStrVisible(wchar_t *pszTime, const SYSTEMTIME &tTime,
		const int &iType);
	// Convert date time to string, the user can see mode
	// pszTime 被转换后的字符串
	// tTime 输入的时间结构
	// iType 转换类型，0 -- 00:00:00, 1 -- 2004-3-31 22:00:32,
	//		2 -- SQL date 02/20/2004, 3 -- 2004-03-09
	//		4 -- SQL DateTime 02/20/2004 22:00:32
	//		5 -- 中文时间格式 2006年5月19日
	void TimeToStrVisible(char *pszTime, const SYSTEMTIME &tTime,
		const int &iType);
	// 浮点型转换成字符串转		(ASCII)
	// szStr -- 被转换成的字符串
	// dVal -- 输入的浮点型数据
	// nRangeVal -- 最大值为数限制
	// nPrecsion -- 小数点精度限制
	bool GuangFloatToStr(char *szStr, const double &dVal, const int &nRangeVal, const int &nPrecsion);
	// 浮点型转换成字符串转		(UNICODE)
	// szStr -- 被转换成的字符串
	// dVal -- 输入的浮点型数据
	// nRangeVal -- 最大值为数限制
	// nPrecsion -- 小数点精度限制
	bool GuangFloatToStr(wchar_t *szStr, const double &dVal, const int &nRangeVal, const int &nPrecsion);
	// 浮点型转换成字符串转		(UNICODE)
	// szStr -- 被转换成的字符串
	// dVal -- 输入的浮点型数据
	bool GuangFloatToStr(wchar_t *szStr, const double &dVal);
	// 浮点型转换成字符串转		(ASCII)
	// szStr -- 被转换成的字符串
	// dVal -- 输入的浮点型数据
	bool GuangFloatToStr(char *szStr, const double &dVal);
	// 从字符串中读取特定配置的内容,标准配置文件类型
	// szConfig -- 读出来的配置项
	// szSource -- 被查找的原字符串
	// szTarget -- 查找的目标字符串
	// iStartLocation -- 开始查找字符串的位置
	// szEndFlag -- 行结束判断标志字符串
	// return value: true--查找成功, false--查找失败
	bool GuangGetConfig(CString &szConfig, const CString &szSource,
		const CString &szTarget, const int &iStartLocation,
		const TCHAR *szEndFlag = _T("\r\n"));
	// find a spical string in a source string (UINICODE)
	// iStartLocation: the start location of the source string
	// pszSource: the source string you want to find
	// pszFindStr: the string you are interested to find
	// return value: -1 can't find the string. otherwise is the string location
	int GuangStrFind(int iStartLocation, const wchar_t *pszSource,
		const wchar_t *pszFindStr);
	// find a spical string in a source string (ASCII)
	// iStartLocation: the start location of the source string
	// pszSource: the source string you want to find
	// pszFindStr: the string you are interested to find
	// return value: -1 can't find the string. otherwise is the string location
	int GuangStrFind(int iStartLocation, const char *pszSource,
		const char *pszFindStr);
	// Get a part of string from source string (ASCII)
	// pszStrGet: get out the string stored there
	// pszStrSource: the source string
	// iStart: the start location from source string
	// iEnd: the end location from source string
	// ruturn value: the get out string.
	char *GuangStrMid(char *pszStrGet, const char *pszStrSource, int iStart,
		int iEnd);
	// Get a part of string from source string (UNICODE)
	// pszStrGet: get out the string stored there
	// pszStrSource: the source string
	// iStart: the start location from source string
	// iEnd: the end location from source string
	// ruturn value: the get out string.
	wchar_t *GuangStrMid(wchar_t *pszStrGet, const wchar_t *pszStrSource, int iStart,
		int iEnd);
	// Get a set from configurtion string
	// pszStrGet: the config value you want to get
	// pszTargetSet: the config mark in config file
	// pszStrSource: the string get from the configuration file
	// return value: true:get the value, false:can't get value
	bool GuangGetConfig(char *pszStrGet, const char *pszTargetSet,
		const char *pszStrSource);
	// x86格式的字符串转整形，按16进制
	unsigned int AtoI16ForX86(const char *szSource);
	// convert a character to int according hex (Unicode Mode)
	int GuangAtoI16(const wchar_t *szSource);
	// convert a character to int according hex (ASCII Mode)
	int GuangAtoI16(const char *szSource);
	// change the integer to character with special length ASCII mode
	void GuangItoANBit(const int &iSourceInt, char *pszStr,
		const int &iChangeType, const int &iCharLen);
	// change the integer to character with special length UNICODE mode
	void GuangItoANBit(const int &iSourceInt, wchar_t *pszStr,
		const int &iChangeType, const int &iCharLen);
	// make the string to upper case
	// szTarget: the upper case string
	// szSource: the source string
	// return value: the upper case string
	char *GuangMakeUpper(char *szTarget, const char *szSource);
	// 向当前字符串中插入一个字符串 ASCII 模式
	// pszDes -- 被插入的目标字符串
	// iLocation -- 被插入的位置
	// pszSource -- 插入的字符串
	bool InsertStr(char *pszDes, const int &iLocation, const char *pszSource);
	// 向当前字符串中插入一个字符串 Unicode 模式
	// pszDes -- 被插入的目标字符串
	// iLocation -- 被插入的位置
	// pszSource -- 插入的字符串
	bool InsertStr(wchar_t *pszDes, const int &iLocation,
		const wchar_t *pszSource);

	Cdeskland(void);
	virtual ~Cdeskland(void);
};
