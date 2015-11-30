#include "stdafx.h"
#include ".\deskland.h"
#include <string>
#include <comdef.h>
#include <assert.h>
#include <math.h>

Cdeskland::Cdeskland(void)
{
}

Cdeskland::~Cdeskland(void)
{
}

// find a spical string in a source string (UINICODE)
// iStartLocation: the start location of the source string
// pszSource: the source string you want to find
// pszFindStr: the string you are interested to find
// return value: -1 can't find the string. otherwise is the string location
int Cdeskland::GuangStrFind(int iStartLocation, const wchar_t *pszSource,
	const wchar_t *pszFindStr)
{
	int iLocation = iStartLocation;
	int iFindStrLen = (int)wcslen(pszFindStr) + 1;
	int iLocalMax = (int)wcslen(pszSource) - iFindStrLen;
	bool bFindOut = false;
	wchar_t *pszTarStr = new wchar_t[iFindStrLen];

	assert(pszTarStr!=NULL);
	assert(pszSource!=NULL);
	assert(pszFindStr!=NULL);
	assert(iStartLocation>=0);
	assert(iStartLocation<=iLocalMax);

	while (iLocation<=iLocalMax)
	{
		memcpy(pszTarStr, pszSource+iLocation, iFindStrLen*sizeof(wchar_t));
		pszTarStr[iFindStrLen-1] = '\0';
		if (wcscmp(pszTarStr, pszFindStr) == 0)
		{
			bFindOut = true;
			break;
		}
		iLocation++;
	}

	if (pszTarStr!=NULL)
	{
		delete[] pszTarStr;
		pszTarStr = NULL;
	}

	if (bFindOut)
		return iLocation;
	else
		return -1;
}

// find a spical string in a source string
// iStartLocation: the start location of the source string
// pszSource: the source string you want to find
// pszFindStr: the string you are interested to find
// return value: -1 can't find the string. otherwise is the string location
int Cdeskland::GuangStrFind(int iStartLocation, const char *pszSource,
	const char *pszFindStr)
{
	int iLocation = iStartLocation;
	int iFindStrLen = (int)strlen(pszFindStr) + 1;
	int iLocalMax = (int)strlen(pszSource) - iFindStrLen;
	bool bFindOut = false;
	char *pszTarStr = new char[iFindStrLen];

	assert(pszTarStr!=NULL);
	assert(pszSource!=NULL);
	assert(pszFindStr!=NULL);
	assert(iStartLocation>=0);
	assert(iStartLocation<=iLocalMax);

	while (iLocation<=iLocalMax)
	{
		memcpy(pszTarStr, pszSource+iLocation, iFindStrLen);
		pszTarStr[iFindStrLen-1] = '\0';
		if (strcmp(pszTarStr, pszFindStr) == 0)
		{
			bFindOut = true;
			break;
		}
		iLocation++;
	}

	if (pszTarStr!=NULL)
	{
		delete[] pszTarStr;
		pszTarStr = NULL;
	}

	if (bFindOut)
		return iLocation;
	else
		return -1;
}

// Get a part of string from source string
// pszStrGet: get out the string stored there
// pszStrSource: the source string 
// iStart: the start location from source string
// iEnd: the end location from source string
// ruturn value: the get out string.
char *Cdeskland::GuangStrMid(char *pszStrGet, const char *pszStrSource,
	int iStart, int iEnd)
{
	assert((pszStrSource!=NULL)&&(iEnd-iStart>=0));

	memcpy(pszStrGet, pszStrSource+iStart, iEnd-iStart);
	pszStrGet[iEnd-iStart] = '\0';

	return pszStrGet;
}

// Get a part of string from source string (UNICODE)
// pszStrGet: get out the string stored there
// pszStrSource: the source string
// iStart: the start location from source string
// iEnd: the end location from source string
// ruturn value: the get out string.
wchar_t *Cdeskland::GuangStrMid(wchar_t *pszStrGet, const wchar_t *pszStrSource, int iStart,
	int iEnd)
{
	assert((pszStrSource!=NULL)&&(iEnd-iStart>=0));

	memcpy(pszStrGet, pszStrSource+iStart, (iEnd-iStart)*sizeof(wchar_t));
	pszStrGet[iEnd-iStart] = L'\0';

	return pszStrGet;
}

// Get a set from configurtion string
// pszStrGet: the config value you want to get
// pszTargetSet: the config mark in config file
// pszStrSource: the string get from the configuration file
// return value: true:get the value, false:can't get value
bool Cdeskland::GuangGetConfig(char *pszStrGet, const char *pszTargetSet,
	const char *pszStrSource)
{
	assert(pszStrSource != NULL);

	int iLocation = GuangStrFind(0, pszStrSource, pszTargetSet);
	if (iLocation == -1)
		return false;
	int iLoEnd = GuangStrFind(iLocation, pszStrSource, "\r\n");
	iLocation += (int)strlen(pszTargetSet);
	GuangStrMid(pszStrGet, pszStrSource, iLocation, iLoEnd);

	while ((pszStrGet[0]==' ')||(pszStrGet[0]=='\t'))
	{
		strcpy(pszStrGet, pszStrGet+1);
	}
	strcpy(pszStrGet, pszStrGet+1);
	while ((pszStrGet[0]==' ')||(pszStrGet[0]=='\t'))
	{
		strcpy(pszStrGet, pszStrGet+1);
	}

	return true;
}

// x86格式的字符串转整形，按16进制
unsigned int Cdeskland::AtoI16ForX86(const char *szSource)
{
	int i = 0;
	int iLen = (int)strlen(szSource)+1;
	char *pszTarget = new char[iLen];

	pszTarget[iLen-1] = '\0';
	for (i=0; i<iLen-1; i+=2)
	{
		pszTarget[iLen-i-3] = szSource[i];
		pszTarget[iLen-i-2] = szSource[i+1];
	}
	i = GuangAtoI16(pszTarget);

	delete[] pszTarget;

	return i;
}

// convert a character to int according hex (Unicode Mode)
int Cdeskland::GuangAtoI16(const wchar_t *szSource)
{
	assert(szSource!=NULL);

	int iRet = 0;
	int i = 0;

	while(*szSource == L'0')
	{
		szSource++;
	}

	while (*szSource != L'\0')
	{
		switch (*szSource)
		{
		case L'0':
			iRet *= 0x10;
			break;
		case L'1':
			iRet = iRet*0x10+0x01;
			break;
		case L'2':
			iRet = iRet*0x10+0x02;
			break;
		case L'3':
			iRet = iRet*0x10+0x03;
			break;
		case L'4':
			iRet = iRet*0x10+0x04;
			break;
		case L'5':
			iRet = iRet*0x10+0x05;
			break;
		case L'6':
			iRet = iRet*0x10+0x06;
			break;
		case L'7':
			iRet = iRet*0x10+0x07;
			break;
		case L'8':
			iRet = iRet*0x10+0x08;
			break;
		case '9':
			iRet = iRet*0x10+0x09;
			break;
		case L'a':
		case L'A':
			iRet = iRet*0x10+0x0a;
			break;
		case L'b':
		case L'B':
			iRet = iRet*0x10+0x0b;
			break;
		case L'c':
		case L'C':
			iRet = iRet*0x10+0x0c;
			break;
		case L'd':
		case L'D':
			iRet = iRet*0x10+0x0d;
			break;
		case L'e':
		case L'E':
			iRet = iRet*0x10+0x0e;
			break;
		case L'f':
		case L'F':
			iRet = iRet*0x10+0x0f;
			break;
		default:
			return iRet;
			break;
		}
		i++;
		szSource++;
		if (i>7)
			break;
	}

	return iRet;
}

// convert a character to int according hex
int Cdeskland::GuangAtoI16(const char *szSource)
{
	assert(szSource!=NULL);

	int iRet = 0;
	int i = 0;

	while(*szSource == '0')
	{
		szSource++;
	}

	while (*szSource != '\0')
	{
		switch (*szSource)
		{
		case '0':
			iRet *= 0x10;
			break;
		case '1':
			iRet = iRet*0x10+0x01;
			break;
		case '2':
			iRet = iRet*0x10+0x02;
			break;
		case '3':
			iRet = iRet*0x10+0x03;
			break;
		case '4':
			iRet = iRet*0x10+0x04;
			break;
		case '5':
			iRet = iRet*0x10+0x05;
			break;
		case '6':
			iRet = iRet*0x10+0x06;
			break;
		case '7':
			iRet = iRet*0x10+0x07;
			break;
		case '8':
			iRet = iRet*0x10+0x08;
			break;
		case '9':
			iRet = iRet*0x10+0x09;
			break;
		case 'a':
		case 'A':
			iRet = iRet*0x10+0x0a;
			break;
		case 'b':
		case 'B':
			iRet = iRet*0x10+0x0b;
			break;
		case 'c':
		case 'C':
			iRet = iRet*0x10+0x0c;
			break;
		case 'd':
		case 'D':
			iRet = iRet*0x10+0x0d;
			break;
		case 'e':
		case 'E':
			iRet = iRet*0x10+0x0e;
			break;
		case 'f':
		case 'F':
			iRet = iRet*0x10+0x0f;
			break;
		default:
			return iRet;
			break;
		}
		i++;
		szSource++;
		if (i>7)
			break;
	}

	return iRet;
}

// change the integer to character with special length ASCII mode
void Cdeskland::GuangItoANBit(const int &iSourceInt, char *pszStr,
	const int &iChangeType, const int &iCharLen)
{
	char czTemp[10];
	int i = 0;

	itoa(iSourceInt, czTemp, iChangeType);
	int iLen = (int)strlen(czTemp);

	for (i=0; i<iCharLen-iLen; i++)
		pszStr[i] = '0';
	strcpy(pszStr+iCharLen-iLen, czTemp);
}

// change the integer to character with special length UNICODE mode
void Cdeskland::GuangItoANBit(const int &iSourceInt, wchar_t *pszStr,
	const int &iChangeType, const int &iCharLen)
{
	wchar_t czTemp[10];
	int i = 0;

	_itow(iSourceInt, czTemp, iChangeType);
	int iLen = (int)wcslen(czTemp);

	for (i=0; i<iCharLen-iLen; i++)
		pszStr[i] = '0';
	wcscpy(pszStr+iCharLen-iLen, czTemp);
}

// make the string to upper case
// szTarget: the upper case string
// szSource: the source string
// return value: the upper case string
char *Cdeskland::GuangMakeUpper(char *szTarget, const char *szSource)
{
	assert(szSource != NULL);

	while (*szSource != '\0')
	{
		*szTarget = toupper(*szSource);
		szTarget ++;
		szSource ++;
	}
	*szTarget = '\0';

	return szTarget;
}

// 向当前字符串中插入一个字符串 ASCII 模式
// pszDes -- 被插入的目标字符串
// iLocation -- 被插入的位置
// pszSource -- 插入的字符串
bool Cdeskland::InsertStr(char *pszDes,
    const int &iLocation, const char *pszSource)
{
	assert(iLocation<=(int)strlen(pszDes));

	int i = 0;
	int iNewLen = (int)strlen(pszDes) + (int)strlen(pszSource);
	char *pNewChar = (char *)VirtualAlloc(NULL,
		iNewLen*sizeof(char), MEM_COMMIT, PAGE_READWRITE);

	if (pNewChar==NULL)
	{
		return false;
	}

	// copy string before the part of insert
	for (i=0; i<iLocation; i++)
	{
		pNewChar[i] = pszDes[i];
	}
	pNewChar[i] = '\0';
	strcat(pNewChar, pszSource);// insert string
	// copy string after the part of insert
	strcat(pNewChar, pszDes+iLocation);

	strcpy(pszDes, pNewChar);// return the transacted string
	VirtualFree(pNewChar, iNewLen*sizeof(char), MEM_DECOMMIT);
	pNewChar = NULL;

	return true;
}

// 向当前字符串中插入一个字符串 Unicode 模式
// pszDes -- 被插入的目标字符串
// iLocation -- 被插入的位置
// pszSource -- 插入的字符串
bool Cdeskland::InsertStr(wchar_t *pszDes,
	const int &iLocation, const wchar_t *pszSource)
{
	assert(iLocation<=(int)wcslen(pszDes));

	int i = 0;
	int iNewLen = (int)wcslen(pszDes) + (int)wcslen(pszSource);
	wchar_t *pNewChar = NULL;

	pNewChar=static_cast<wchar_t*>(VirtualAlloc(pNewChar, iNewLen*sizeof(wchar_t)+2, MEM_COMMIT, PAGE_READWRITE));
	if (pNewChar==NULL)
	{
		return false;
	}

	// copy string before the part of insert
	for (i=0; i<iLocation; i++)
	{
		pNewChar[i] = pszDes[i];
	}
	pNewChar[i] = _T('\0');
	wcscat(pNewChar, pszSource);// insert string
	// copy string after the part of insert
	wcscat(pNewChar, pszDes+iLocation);

	wcscpy(pszDes, pNewChar);// return the transacted string
	if (!VirtualFree(pNewChar, iNewLen*sizeof(wchar_t)+2, MEM_DECOMMIT))
	{
		return false;
	}
	pNewChar = NULL;

	return true;
}

// 从字符串中读取特定配置的内容,标准配置文件类型
// szConfig -- 读出来的配置项
// szSource -- 被查找的原字符串
// szTarget -- 查找的目标字符串
// iStartLocation -- 开始查找字符串的位置
// szEndFlag -- 行结束判断标志字符串
// return value: true--查找成功, false--查找失败
bool Cdeskland::GuangGetConfig(CString &szConfig, const CString &szSource,
	const CString &szTarget, const int &iStartLocation,
	const TCHAR *szEndFlag/* = _T("\r\n")*/)
{
	int iLoStart = 0;
	int iLoEnd = 0;

	assert(iStartLocation < szSource.GetLength());

	iLoStart = szSource.Find(szTarget, iStartLocation);
	if (iLoStart == -1)
	{
		return false;
	}
	iLoStart = szSource.Find(_T("="), iLoStart) + 1;
	if (iLoStart == -1)
	{
		return false;
	}
	iLoEnd = szSource.Find(szEndFlag, iLoStart);
	if ((iLoEnd == -1)||(iLoEnd == iLoStart))
	{
		return false;
	}
	szConfig = szSource.Mid(iLoStart, iLoEnd-iLoStart);
	szConfig.TrimLeft();
	szConfig.TrimRight();

	return true;
}

// 浮点型转换成字符串转		(ASCII)
// szStr -- 被转换成的字符串
// dVal -- 输入的浮点型数据
// nRangeVal -- 最大值为数限制
// nPrecsion -- 小数点精度限制
bool Cdeskland::GuangFloatToStr(char *szStr, const double &dVal, const int &nRangeVal, const int &nPrecsion)
{
	int nInsertLocation = 0;
	int i = 0;
	char szTemp[11];
	char szPrintType[20] = "%.";

	itoa(nPrecsion, szTemp, 10);
	strcat(szPrintType, szTemp);
	strcat(szPrintType, "f");
	sprintf(szStr, szPrintType, dVal);

	int nLocation = GuangStrFind(0, szStr, ".");
	if (dVal<0.0)
	{
		nInsertLocation = nRangeVal-nLocation+1;
		for (i=1; i<nInsertLocation+1; i++)
		{
			InsertStr(szStr, 1, "0");
		}
	}
	else
	{
		nInsertLocation = nRangeVal-nLocation;
		for (i=0; i<nInsertLocation; i++)
		{
			InsertStr(szStr, 0, "0");
		}
		InsertStr(szStr, 0, " ");
	}

	return true;
}

// 浮点型转换成字符串转		(UNICODE)
// szStr -- 被转换成的字符串
// dVal -- 输入的浮点型数据
// nRangeVal -- 最大值为数限制
// nPrecsion -- 小数点精度限制
bool Cdeskland::GuangFloatToStr(wchar_t *szStr, const double &dVal, const int &nRangeVal, const int &nPrecsion)
{
	int nInsertLocation = 0;
	int i = 0;
	wchar_t szTemp[11];
	wchar_t szPrintType[20] = L"%.";

	_itow(nPrecsion, szTemp, 10);
	wcscat(szPrintType, szTemp);
	wcscat(szPrintType, L"f");
	swprintf(szStr, szPrintType, dVal);

	int nLocation = GuangStrFind(0, szStr, L".");
	if (dVal<0.0)
	{
		nInsertLocation = nRangeVal-nLocation+1;
		for (i=1; i<nInsertLocation+1; i++)
		{
			InsertStr(szStr, 1, L"0");
		}
	}
	else
	{
		nInsertLocation = nRangeVal-nLocation;
		for (i=0; i<nInsertLocation; i++)
		{
			InsertStr(szStr, 0, L"0");
		}
		InsertStr(szStr, 0, L" ");
	}

	return true;
}

// 浮点型转换成字符串转		(UNICODE)
// szStr -- 被转换成的字符串
// dVal -- 输入的浮点型数据
bool Cdeskland::GuangFloatToStr(wchar_t *szStr, const double &dVal)
{
	wcscpy(szStr, (wchar_t *)(_bstr_t)dVal);
	if ((fabs(dVal)<1.0)&&(fabs(dVal)>0.0))
	{
		if (dVal>0.0)
		{
			InsertStr(szStr, 0, L"0");
		}
		else
		{
			InsertStr(szStr, 1, L"0");
		}
	}

	return true;
}

// 浮点型转换成字符串转		(ASCII)
// szStr -- 被转换成的字符串
// dVal -- 输入的浮点型数据
bool Cdeskland::GuangFloatToStr(char *szStr, const double &dVal)
{
	strcpy(szStr, (char *)(_bstr_t)dVal);
	if ((fabs(dVal)<1.0)&&(fabs(dVal)>0.0))
	{
		if (dVal>0.0)
		{
			InsertStr(szStr, 0, "0");
		}
		else
		{
			InsertStr(szStr, 1, "0");
		}
	}

	return true;
}

// Convert date time to string, the user can see mode
// pszTime 被转换后的字符串
// tTime 输入的时间结构
// iType 转换类型，0 -- 00:00:00, 1 -- 2004-3-31 22:00:32,
//		2 -- SQL date 02/20/2004, 3 -- 2004-03-09
//		4 -- SQL DateTime 02/20/2004 22:00:32
//		5 -- 中文时间格式 2006年5月19日
void Cdeskland::TimeToStrVisible(wchar_t *pszTime, const SYSTEMTIME &tTime,
	const int &iType)
{
	wchar_t szTemp[5];

	switch (iType)
	{
	case 0:
		GuangItoANBit(tTime.wHour, szTemp, 10, 2);
		wcscpy(pszTime, szTemp);
		wcscat(pszTime, L":");
		GuangItoANBit(tTime.wMinute, szTemp, 10, 2);
		wcscat(pszTime, szTemp);
		wcscat(pszTime, L":");
		GuangItoANBit(tTime.wSecond, szTemp, 10, 2);
		wcscat(pszTime, szTemp);
		break;
	case 1:
		GuangItoANBit(tTime.wYear, szTemp, 10, 4);
		wcscpy(pszTime, szTemp);
		GuangItoANBit(tTime.wMonth, szTemp, 10, 2);
		wcscat(pszTime, L"-");
		wcscat(pszTime, szTemp);
		GuangItoANBit(tTime.wDay, szTemp, 10, 2);
		wcscat(pszTime, L"-");
		wcscat(pszTime, szTemp);
		wcscat(pszTime, L" ");

		GuangItoANBit(tTime.wHour, szTemp, 10, 2);
		wcscat(pszTime, szTemp);
		wcscat(pszTime, L":");
		GuangItoANBit(tTime.wMinute, szTemp, 10, 2);
		wcscat(pszTime, szTemp);
		wcscat(pszTime, L":");
		GuangItoANBit(tTime.wSecond, szTemp, 10, 2);
		wcscat(pszTime, szTemp);
		break;
	case 2:
		_itow(tTime.wMonth, szTemp, 10);
		wcscpy(pszTime, szTemp);
		wcscat(pszTime, L"/");
		_itow(tTime.wDay, szTemp, 10);
		wcscat(pszTime, szTemp);
		wcscat(pszTime, L"/");
		GuangItoANBit(tTime.wYear, szTemp, 10, 4);
		wcscat(pszTime, szTemp);
		break;
	case 3:
		GuangItoANBit(tTime.wYear, szTemp, 10, 4);
		wcscpy(pszTime, szTemp);
		wcscat(pszTime, L"-");
		GuangItoANBit(tTime.wMonth, szTemp, 10, 2);
		wcscat(pszTime, szTemp);
		wcscat(pszTime, L"-");
		GuangItoANBit(tTime.wDay, szTemp, 10, 2);
		wcscat(pszTime, szTemp);
		break;
	case 4:
		_itow(tTime.wMonth, szTemp, 10);
		wcscpy(pszTime, szTemp);
		wcscat(pszTime, L"/");
		_itow(tTime.wDay, szTemp, 10);
		wcscat(pszTime, szTemp);
		wcscat(pszTime, L"/");
		GuangItoANBit(tTime.wYear, szTemp, 10, 4);
		wcscat(pszTime, szTemp);
		wcscat(pszTime, L" ");

		GuangItoANBit(tTime.wHour, szTemp, 10, 2);
		wcscat(pszTime, szTemp);
		wcscat(pszTime, L":");
		GuangItoANBit(tTime.wMinute, szTemp, 10, 2);
		wcscat(pszTime, szTemp);
		wcscat(pszTime, L":");
		GuangItoANBit(tTime.wSecond, szTemp, 10, 2);
		wcscat(pszTime, szTemp);
		break;
	case 5:
		_itow(tTime.wYear, szTemp, 10);
		wcscpy(pszTime, szTemp);
		wcscat(pszTime, L"年");
		_itow(tTime.wMonth, szTemp, 10);
		wcscat(pszTime, szTemp);
		wcscat(pszTime, L"月");
		_itow(tTime.wDay, szTemp, 10);
		wcscat(pszTime, szTemp);
		wcscat(pszTime, L"日");
		break;
	default:
		break;
	}
}

// Convert date time to string, the user can see mode
// pszTime 被转换后的字符串
// tTime 输入的时间结构
// iType 转换类型，0 -- 00:00:00, 1 -- 2004-3-31 22:00:32,
//		2 -- SQL date 02/20/2004, 3 -- 2004-03-09
//		4 -- SQL DateTime 02/20/2004 22:00:32
//		5 -- 中文时间格式 2006年5月19日
void Cdeskland::TimeToStrVisible(char *pszTime, const SYSTEMTIME &tTime,
	const int &iType)
{
	char szTemp[5];

	switch (iType)
	{
	case 0:
		GuangItoANBit(tTime.wHour, szTemp, 10, 2);
		strcpy(pszTime, szTemp);
		strcat(pszTime, ":");
		GuangItoANBit(tTime.wMinute, szTemp, 10, 2);
		strcat(pszTime, szTemp);
		strcat(pszTime, ":");
		GuangItoANBit(tTime.wSecond, szTemp, 10, 2);
		strcat(pszTime, szTemp);
		break;
	case 1:
		GuangItoANBit(tTime.wYear, szTemp, 10, 4);
		strcpy(pszTime, szTemp);
		itoa(tTime.wMonth, szTemp, 10);
		strcat(pszTime, "-");
		strcat(pszTime, szTemp);
		itoa(tTime.wDay, szTemp, 10);
		strcat(pszTime, "-");
		strcat(pszTime, szTemp);
		strcat(pszTime, " ");

		GuangItoANBit(tTime.wHour, szTemp, 10, 2);
		strcat(pszTime, szTemp);
		strcat(pszTime, ":");
		GuangItoANBit(tTime.wMinute, szTemp, 10, 2);
		strcat(pszTime, szTemp);
		strcat(pszTime, ":");
		GuangItoANBit(tTime.wSecond, szTemp, 10, 2);
		strcat(pszTime, szTemp);
		break;
	case 2:
		itoa(tTime.wMonth, szTemp, 10);
		strcpy(pszTime, szTemp);
		strcat(pszTime, "/");
		itoa(tTime.wDay, szTemp, 10);
		strcat(pszTime, szTemp);
		strcat(pszTime, "/");
		GuangItoANBit(tTime.wYear, szTemp, 10, 4);
		strcat(pszTime, szTemp);
		break;
	case 3:
		GuangItoANBit(tTime.wYear, szTemp, 10, 4);
		strcpy(pszTime, szTemp);
		strcat(pszTime, "-");
		GuangItoANBit(tTime.wMonth, szTemp, 10, 2);
		strcat(pszTime, szTemp);
		strcat(pszTime, "-");
		GuangItoANBit(tTime.wDay, szTemp, 10, 2);
		strcat(pszTime, szTemp);
		break;
	case 4:
		itoa(tTime.wMonth, szTemp, 10);
		strcpy(pszTime, szTemp);
		strcat(pszTime, "/");
		itoa(tTime.wDay, szTemp, 10);
		strcat(pszTime, szTemp);
		strcat(pszTime, "/");
		GuangItoANBit(tTime.wYear, szTemp, 10, 4);
		strcat(pszTime, szTemp);
		strcat(pszTime, " ");

		GuangItoANBit(tTime.wHour, szTemp, 10, 2);
		strcat(pszTime, szTemp);
		strcat(pszTime, ":");
		GuangItoANBit(tTime.wMinute, szTemp, 10, 2);
		strcat(pszTime, szTemp);
		strcat(pszTime, ":");
		GuangItoANBit(tTime.wSecond, szTemp, 10, 2);
		strcat(pszTime, szTemp);
		break;
	case 5:
		itoa(tTime.wYear, szTemp, 10);
		strcpy(pszTime, szTemp);
		strcat(pszTime, "年");
		itoa(tTime.wMonth, szTemp, 10);
		strcat(pszTime, szTemp);
		strcat(pszTime, "月");
		itoa(tTime.wDay, szTemp, 10);
		strcat(pszTime, szTemp);
		strcat(pszTime, "日");
		break;
	default:
		break;
	}
}

// 时间偏移计算，
// tTime -- 时间结构, 给出原时间，得到偏移时间
// iEscapeSecond -- 时间偏移的数量，单位秒
// bAbs -- 时间选项，true增加时间，false减少时间
void Cdeskland::DevEscapeTimeCalculate(SYSTEMTIME &tTime,
	const int &iEscapeSecond, const bool &bAbs)
{
	int iEsapeMinute = iEscapeSecond/60;
	int iEsapeSecond = iEscapeSecond%60;
	int iNewMinute;
	int iNewSecond;

	if (bAbs)
	{
		iNewMinute = tTime.wMinute + iEsapeMinute;
		iNewSecond = tTime.wSecond + iEsapeSecond;
	}
	else
	{
		iNewMinute = tTime.wMinute - iEsapeMinute;
		iNewSecond = tTime.wSecond - iEsapeSecond;
	}

	if (iNewSecond<0)
	{
		iNewMinute --;
		tTime.wSecond = iNewSecond+60;
	}
	else if (iNewSecond>60)
	{
		iNewMinute ++;
		tTime.wSecond = iNewSecond-60;
	}
	else
	{
		tTime.wSecond = iNewSecond;
	}

	if (iNewMinute<0)
	{
		tTime.wMinute = iNewMinute+60;
		if (tTime.wHour == 0)
		{
			tTime.wHour = 23;
		}
		else
		{
			tTime.wHour --;
		}
	}
	else if (iNewMinute>60)
	{
		tTime.wMinute = iNewMinute-60;
		if (tTime.wHour == 23)
		{
			tTime.wHour = 0;
		}
		else
		{
			tTime.wHour ++;
		}
	}
	else
	{
		tTime.wMinute = iNewMinute;
	}
}

// 计算偏移时间
// EscapeTime -- 偏移时间
// StartTime -- 开始时间
// EndTime -- 结束时间
// return value: true 正时间， false 负时间
bool Cdeskland::DevEscapeTimeCalculate(SYSTEMTIME &EscapeTime,
	const SYSTEMTIME &StartTime, const SYSTEMTIME &EndTime)
{
	int iDayInMonth = 31;
	bool bRet = true;

	// 计算时间大小
	if (EndTime.wYear*3600*24*iDayInMonth*12+EndTime.wMonth*3600*24
		*iDayInMonth+EndTime.wDay*3600*24+EndTime.wHour*3600+EndTime.wMinute
		*60+EndTime.wSecond<StartTime.wYear*3600*24*iDayInMonth*12
		+StartTime.wMonth*3600*24*iDayInMonth+StartTime.wDay*3600*24
		+StartTime.wHour*3600+StartTime.wMinute*60+StartTime.wSecond)
	{
		bRet = false;
	}

	if (bRet)
	{
		iDayInMonth = DevCalculateMonth(StartTime);
	}
	else
	{
		iDayInMonth = DevCalculateMonth(EndTime);
	}

	int iEscSecond = EndTime.wSecond-StartTime.wSecond+(EndTime.wMinute
		-StartTime.wMinute)*60+(EndTime.wHour-StartTime.wHour)*3600
		+(EndTime.wDay-StartTime.wDay)*3600*24+(EndTime.wMonth
		-StartTime.wMonth)*3600*24*iDayInMonth+(EndTime.wYear-StartTime.wYear)
		*3600*24*iDayInMonth*12;

	EscapeTime.wYear = iEscSecond/(3600*24*iDayInMonth*12);// 得到年
	iEscSecond %= 3600*24*iDayInMonth*12;
	EscapeTime.wMonth = iEscSecond/(3600*24*iDayInMonth);// 得到月
	iEscSecond %= 3600*24*iDayInMonth;
	EscapeTime.wDay = iEscSecond/(3600*24);// 得到日
	iEscSecond %= 3600*24;
	EscapeTime.wHour = iEscSecond/3600;// 得到小时
	iEscSecond %= 3600;
	EscapeTime.wMinute = iEscSecond/60;// 得到分钟
	iEscSecond %= 60;
	EscapeTime.wSecond = iEscSecond;// 得到秒
	EscapeTime.wMilliseconds = 0;// 得到毫秒

	return bRet;
}

// 计算当前月份的天数
BYTE Cdeskland::DevCalculateMonth(const SYSTEMTIME &LocalTime)
{
	BYTE ucRet = 0;

	assert((LocalTime.wMonth>=0)&&(LocalTime.wMonth<32));

	switch (LocalTime.wMonth)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		ucRet = 31;
		break;
	case 2:
		if (((LocalTime.wYear % 100 == 0)&&(LocalTime.wYear % 400 == 0))
			||((LocalTime.wYear % 100 > 0)&&(LocalTime.wYear % 4 == 0)))
		{
			ucRet = 29;
		}
		else
		{
			ucRet = 28;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		ucRet = 30;
		break;
	default:
		break;
	}

	return ucRet;
}

// 计算偏移时间
// StartTime -- 开始时间
// EndTime -- 结束时间
// return value: 偏移时间，单位秒
int Cdeskland::DevEscapeTimeCalculate(const SYSTEMTIME &StartTime,
	const SYSTEMTIME &EndTime)
{
	int iEscSecond = (EndTime.wYear-StartTime.wYear)*365*24*3600;
	iEscSecond += (EndTime.wMonth-StartTime.wMonth)*30*24*3600;
	iEscSecond += (EndTime.wDay-StartTime.wDay)*24*3600;
	iEscSecond += (EndTime.wHour-StartTime.wHour)*3600;
	iEscSecond += (EndTime.wMinute-StartTime.wMinute)*60;
	iEscSecond += EndTime.wSecond-StartTime.wSecond;

	return iEscSecond;
}

// 得到当前月份的天数
int Cdeskland::DevGetDaysInMonth(SYSTEMTIME &tTime)
{
	int nDays = -1;

	switch (tTime.wMonth)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		nDays = 31;
		break;
	case 2:
		if ((tTime.wYear % 4)==0)
		{
			nDays = 29;
		}
		else
		{
			nDays = 28;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		nDays = 30;
		break;
	default:
		break;
	}

	return nDays;
}

// 根据原时间和偏移时间得到新的时间
// tSource -- 原时间
// tNewTime -- 计算得到的新时间
// nEscape -- 偏移时间
// ucType -- 计算类型，0--毫秒，1--秒，2--分钟，3--小时，4--日，5--月，6--年
void Cdeskland::DevEscapeTime(const SYSTEMTIME &tSource, SYSTEMTIME &tNewTime, const int nEscape,
		const unsigned char &ucType)
{
	tNewTime = tSource;
	int nDaysInMonth = DevGetDaysInMonth(tNewTime);

	switch (ucType)
	{
	case 0:					// 毫秒
		break;
	case 1:					// 秒
		break;
	case 2:					// 分钟
		break;
	case 3:					// 小时
		break;
	case 4:					// 日
		if (tNewTime.wDay+nEscape>nDaysInMonth)
		{
			tNewTime.wDay = tSource.wDay+nEscape-nDaysInMonth;
			if (tNewTime.wMonth==12)
			{
				tNewTime.wYear ++;
				tNewTime.wMonth = 1;
			}
			else
			{
				tNewTime.wMonth ++;
			}
		}
		else if (tNewTime.wDay+nEscape<1)
		{
			if (tNewTime.wMonth==1)
			{
				tNewTime.wYear --;
				tNewTime.wMonth = 12;
			}
			else
			{
				tNewTime.wMonth --;
			}
			nDaysInMonth = DevGetDaysInMonth(tNewTime);
			tNewTime.wDay = tSource.wDay+nEscape+nDaysInMonth;
		}
		else
		{
			tNewTime.wDay = tSource.wDay+nEscape;
		}
		break;
	case 5:					// 月
		break;
	case 6:					// 年
		break;
	default:
		break;
	}
}

// 比较时间顺序,
// 返回值: 0时间相同，<0原时间晚于目标时间，>0原时间前于目标时间
int Cdeskland::DevCompareTwoTime(const SYSTEMTIME &SourceTime, const SYSTEMTIME &TarTime,
	const bool &bEnableYYMMDD/* = false*/)
{
	if (bEnableYYMMDD)
	{
		// 比较年
		if (SourceTime.wYear>TarTime.wYear)
		{
			return -1;
		}
		else if (SourceTime.wYear<TarTime.wYear)
		{
			return 1;
		}

		// 比较月
		if (SourceTime.wMonth>TarTime.wMonth)
		{
			return -1;
		}
		else if (SourceTime.wMonth<TarTime.wMonth)
		{
			return 1;
		}

		// 比较日
		if (SourceTime.wDay>TarTime.wDay)
		{
			return -1;
		}
		else if (SourceTime.wDay<TarTime.wDay)
		{
			return 1;
		}
	}

	// 比较小时
	if (SourceTime.wHour>TarTime.wHour)
	{
		return -1;
	}
	else if (SourceTime.wHour<TarTime.wHour)
	{
		return 1;
	}

	// 比较分钟
	if (SourceTime.wMinute>TarTime.wMinute)
	{
		return -1;
	}
	else if (SourceTime.wMinute<TarTime.wMinute)
	{
		return 1;
	}

	// 比较秒
	if (SourceTime.wSecond>TarTime.wSecond)
	{
		return -1;
	}
	else if (SourceTime.wSecond<TarTime.wSecond)
	{
		return 1;
	}

	return 0;
}

// 将字符串转换成日期型
// tTime -- 被转换的日期类型
// pszTimeStr -- 时间字符串
// iTimeType -- 转换类型，0 00:00:00, 1 未定
bool Cdeskland::DevStrToTime(SYSTEMTIME &tTime, const TCHAR *pszTimeStr,
		const int &iTimeType)
{
	TCHAR czTemp[5];

	tTime.wYear = 0;
	tTime.wMonth = 0;
	tTime.wDay = 0;
	tTime.wHour = 0;
	tTime.wDayOfWeek = 7;
	tTime.wMinute = 0;
	tTime.wSecond = 0;
	tTime.wMilliseconds = 0;

	switch (iTimeType)
	{
	case 0:
		memcpy(czTemp, pszTimeStr, 2*sizeof(TCHAR));// add hour
		czTemp[2] = _T('\0');
		tTime.wHour = _ttoi(czTemp);
		memcpy(czTemp, pszTimeStr+3, 2*sizeof(TCHAR));//add minute
		czTemp[2] = _T('\0');
		tTime.wMinute = _ttoi(czTemp);
		memcpy(czTemp, pszTimeStr+6, 2*sizeof(TCHAR));// add second
		czTemp[2] = _T('\0');
		tTime.wSecond = _ttoi(czTemp);
		break;
	default:
		break;
	}

	return true;
}

// 将设置组从字符串中提取出来保存在double数组中 (UNICODE)
// pszSource——被分析的字符串
// pdzArray——被解析出来的数组
// pszInsulate——字串分隔符
// return value——数组长度
int Cdeskland::DevGetArrayConfig(const wchar_t* pszSource, double* pdzArray, const wchar_t* pszInsulate)
{
	assert(pszSource!=NULL);
	assert(pszInsulate!=NULL);

	int i = 0;
	int j = 0;
	int iLoStart = 0;
	int iLoEnd = 0;
	int iLenSource = wcslen(pszSource);
	int iLenInsulate = wcslen(pszInsulate);
	wchar_t* pSelStr = new wchar_t[iLenInsulate+1];
	wchar_t* pStoreStr = new wchar_t[iLenSource+1];

	if ((iLenSource==0)||(iLenInsulate==0))
	{
		return 0;
	}

	while (i<iLenSource-iLenInsulate)
	{
		memcpy(pSelStr, pszSource+i, sizeof(wchar_t)*iLenInsulate);
		pSelStr[iLenInsulate] = L'\0';
		if (wcscmp(pSelStr, pszInsulate)==0)
		{
			iLoEnd = i;
			memcpy(pStoreStr, pszSource+iLoStart, sizeof(wchar_t)*(iLoEnd-iLoStart));
			pStoreStr[iLoEnd-iLoStart] = L'\0';
			pdzArray[j] = wcstod(pStoreStr, NULL);	//_wtof(pStoreStr);
			iLoStart = iLoEnd+1;
			j++;
		}
		i++;
	}

	memcpy(pStoreStr, pszSource+iLoStart, sizeof(wchar_t)*(iLenSource-iLoStart));
	pStoreStr[iLenSource-iLoStart] = L'\0';
	pdzArray[j] = _wtof(pStoreStr);

	delete[] pSelStr;
	delete[] pStoreStr;

	return ++j;
}

// 将设置组从字符串中提取出来保存在double数组中 (ASCII)
// pszSource——被分析的字符串
// pdzArray——被解析出来的数组
// pszInsulate——字串分隔符
// return value——数组长度
int Cdeskland::DevGetArrayConfig(const char* pszSource, double* pdzArray, const char* pszInsulate)
{
	assert(pszSource!=NULL);
	assert(pszInsulate!=NULL);

	int i = 0;
	int j = 0;
	int iLoStart = 0;
	int iLoEnd = 0;
	int iLenSource = strlen(pszSource);
	int iLenInsulate = strlen(pszInsulate);
	char* pSelStr = new char[iLenInsulate+1];
	char* pStoreStr = new char[iLenSource+1];

	if ((iLenSource==0)||(iLenInsulate==0))
	{
		return 0;
	}

	while (i<iLenSource-iLenInsulate)
	{
		memcpy(pSelStr, pszSource+i, sizeof(char)*iLenInsulate);
		pSelStr[iLenInsulate] = L'\0';
		if (strcmp(pSelStr, pszInsulate)==0)
		{
			iLoEnd = i;
			memcpy(pStoreStr, pszSource+iLoStart, sizeof(char)*(iLoEnd-iLoStart));
			pStoreStr[iLoEnd-iLoStart] = L'\0';
			pdzArray[j] = atof(pStoreStr);
			iLoStart = iLoEnd+1;
			j++;
		}
		i++;
	}

	memcpy(pStoreStr, pszSource+iLoStart, sizeof(char)*(iLenSource-iLoStart));
	pStoreStr[iLenSource-iLoStart] = L'\0';
	pdzArray[j] = atof(pStoreStr);

	delete[] pSelStr;
	delete[] pStoreStr;

	return ++j;
}

// 将字符串转换成日期型
// tTime -- 被转换的日期类型
// pszTimeStr -- 时间字符串
// iTimeType -- 转换类型，0 未定, 1 2002-2-22 0:0:0
// 返回值：true成功，false 失败
bool Cdeskland::DevStrToTimeFull(SYSTEMTIME &tTime, const TCHAR *pszTimeStr, const int &iTimeType)
{
	CString szStr(pszTimeStr);
	CString szTemp;
	int nLoStart = 0;
	int nLoEnd = 0;

	switch (iTimeType)
	{
	case 1:
		nLoEnd = szStr.Find(_T('-'), nLoStart);
		if (nLoEnd==-1)
		{
			return false;
		}
		szTemp = szStr.Left(nLoEnd);
		tTime.wYear = _ttoi(szTemp);	// get year
		nLoStart = nLoEnd+1;
		nLoEnd = szStr.Find(_T('-'), nLoStart);
		if (nLoEnd==-1)
		{
			return false;
		}
		szTemp = szStr.Mid(nLoStart, nLoEnd-nLoStart);
		//
		break;
	default:
		break;
	}

	return true;
}
