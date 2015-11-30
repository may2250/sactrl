// deskland �Զ���ɸ�����, �汾1.4.8
// ���ߣ�deskland@msn.com
// �����޸����ڣ�2008-02-28
// history: 2008-02-28 1.4		����TimeToStrFull����

#pragma once
#pragma warning (disable:4267)
#pragma warning (disable:4996)

class Cdeskland
{
public:
	// ����������ַ�������ȡ����������double������ (ASCII)
	// pszSource�������������ַ���
	// pdzArray��������������������
	// pszInsulate�����ִ��ָ���
	// return value�������鳤��
	int DevGetArrayConfig(const char* pszSource, double* pdzArray, const char* pszInsulate);
	// ����������ַ�������ȡ����������double������  (UNICODE)
	// pszSource�������������ַ���
	// pdzArray��������������������
	// pszInsulate�����ִ��ָ���
	// return value�������鳤��
	int DevGetArrayConfig(const wchar_t* pszSource, double* pdzArray, const wchar_t* pszInsulate);
	// ���ַ���ת����������
	// tTime -- ��ת������������
	// pszTimeStr -- ʱ���ַ���
	// iTimeType -- ת�����ͣ�0 δ��, 1 2002-2-22 0:0:0
	// ����ֵ��true�ɹ���false ʧ��
	bool DevStrToTimeFull(SYSTEMTIME &tTime, const TCHAR *pszTimeStr, const int &iTimeType);
	// ���ַ���ת����������
	// tTime -- ��ת������������
	// pszTimeStr -- ʱ���ַ���
	// iTimeType -- ת�����ͣ�0 00:00:00, 1 δ��
	bool DevStrToTime(SYSTEMTIME &tTime, const TCHAR *pszTimeStr,
		const int &iTimeType);
	// �Ƚ�ʱ��˳��,
	// ����ֵ: 0ʱ����ͬ��<0ԭʱ������Ŀ��ʱ�䣬>0ԭʱ��ǰ��Ŀ��ʱ��
	// bEnableYYMMDD: true:�Ƚ�������, false:���Ƚ�������
	int DevCompareTwoTime(const SYSTEMTIME &SourceTime, const SYSTEMTIME &TarTime,
		const bool &bEnableYYMMDD = false);
	// ���㵱ǰ�·ݵ�����
	BYTE DevCalculateMonth(const SYSTEMTIME &LocalTime);
	// ����ƫ��ʱ��
	// StartTime -- ��ʼʱ��
	// EndTime -- ����ʱ��
	// return value: ƫ��ʱ�䣬��λ��
	int DevEscapeTimeCalculate(const SYSTEMTIME &StartTime,
		const SYSTEMTIME &EndTime);
	// ����ƫ��ʱ��
	// EscapeTime -- ƫ��ʱ��
	// StartTime -- ��ʼʱ��
	// EndTime -- ����ʱ��
	// return value: true ��ʱ�䣬 false ��ʱ��
	bool DevEscapeTimeCalculate(SYSTEMTIME &EscapeTime,
		const SYSTEMTIME &StartTime, const SYSTEMTIME &EndTime);
	int DevGetDaysInMonth(SYSTEMTIME &tTime);	// �õ���ǰ�·ݵ�����
	// ����ԭʱ���ƫ��ʱ��õ��µ�ʱ��
	// tSource -- ԭʱ��
	// tNewTime -- ����õ�����ʱ��
	// nEscape -- ƫ��ʱ��
	// ucType -- �������ͣ�0--���룬1--�룬2--���ӣ�3--Сʱ��4--�գ�5--�£�6--��
	void DevEscapeTime(const SYSTEMTIME &tSource, SYSTEMTIME &tNewTime, const int nEscape,
		const unsigned char &ucType);
	// ʱ��ƫ�Ƽ��㣬
	// tTime -- ʱ��ṹ, ����ԭʱ�䣬�õ�ƫ��ʱ��
	// iEscapeSecond -- ʱ��ƫ�Ƶ���������λ��
	// bAbs -- ʱ��ѡ�true����ʱ�䣬false����ʱ��
	void DevEscapeTimeCalculate(SYSTEMTIME &tTime, const int &iEscapeSecond,
		const bool &bAbs);
	// Convert date time to string, the user can see mode
	// pszTime ��ת������ַ���
	// tTime �����ʱ��ṹ
	// iType ת�����ͣ�0 -- 00:00:00, 1 -- 2004-3-31 22:00:32,
	//		2 -- SQL date 02/20/2004, 3 -- 2004-03-09
	//		4 -- SQL DateTime 02/20/2004 22:00:32
	//		5 -- ����ʱ���ʽ 2006��5��19��
	void TimeToStrVisible(wchar_t *pszTime, const SYSTEMTIME &tTime,
		const int &iType);
	// Convert date time to string, the user can see mode
	// pszTime ��ת������ַ���
	// tTime �����ʱ��ṹ
	// iType ת�����ͣ�0 -- 00:00:00, 1 -- 2004-3-31 22:00:32,
	//		2 -- SQL date 02/20/2004, 3 -- 2004-03-09
	//		4 -- SQL DateTime 02/20/2004 22:00:32
	//		5 -- ����ʱ���ʽ 2006��5��19��
	void TimeToStrVisible(char *pszTime, const SYSTEMTIME &tTime,
		const int &iType);
	// ������ת�����ַ���ת		(ASCII)
	// szStr -- ��ת���ɵ��ַ���
	// dVal -- ����ĸ���������
	// nRangeVal -- ���ֵΪ������
	// nPrecsion -- С���㾫������
	bool GuangFloatToStr(char *szStr, const double &dVal, const int &nRangeVal, const int &nPrecsion);
	// ������ת�����ַ���ת		(UNICODE)
	// szStr -- ��ת���ɵ��ַ���
	// dVal -- ����ĸ���������
	// nRangeVal -- ���ֵΪ������
	// nPrecsion -- С���㾫������
	bool GuangFloatToStr(wchar_t *szStr, const double &dVal, const int &nRangeVal, const int &nPrecsion);
	// ������ת�����ַ���ת		(UNICODE)
	// szStr -- ��ת���ɵ��ַ���
	// dVal -- ����ĸ���������
	bool GuangFloatToStr(wchar_t *szStr, const double &dVal);
	// ������ת�����ַ���ת		(ASCII)
	// szStr -- ��ת���ɵ��ַ���
	// dVal -- ����ĸ���������
	bool GuangFloatToStr(char *szStr, const double &dVal);
	// ���ַ����ж�ȡ�ض����õ�����,��׼�����ļ�����
	// szConfig -- ��������������
	// szSource -- �����ҵ�ԭ�ַ���
	// szTarget -- ���ҵ�Ŀ���ַ���
	// iStartLocation -- ��ʼ�����ַ�����λ��
	// szEndFlag -- �н����жϱ�־�ַ���
	// return value: true--���ҳɹ�, false--����ʧ��
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
	// x86��ʽ���ַ���ת���Σ���16����
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
	// ��ǰ�ַ����в���һ���ַ��� ASCII ģʽ
	// pszDes -- �������Ŀ���ַ���
	// iLocation -- �������λ��
	// pszSource -- ������ַ���
	bool InsertStr(char *pszDes, const int &iLocation, const char *pszSource);
	// ��ǰ�ַ����в���һ���ַ��� Unicode ģʽ
	// pszDes -- �������Ŀ���ַ���
	// iLocation -- �������λ��
	// pszSource -- ������ַ���
	bool InsertStr(wchar_t *pszDes, const int &iLocation,
		const wchar_t *pszSource);

	Cdeskland(void);
	virtual ~Cdeskland(void);
};
