// TxtFile.cpp: implementation of the CTxtFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Laser.h"
#include "TxtFile.h"

#include <locale.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTxtFile::CTxtFile()
{
}

CTxtFile::~CTxtFile()
{

}

BOOL CTxtFile::BakFile(CString strPath, CString strBakDir)
{
	int nYear, nMonth, nDay;
	GetCrtDate(nYear, nMonth, nDay);

	CString strYearMonth;
	strYearMonth.Format(_T("%d\\%d"), nYear, nMonth);

	CreateFolder(strBakDir+_T("\\")+strYearMonth);

	CString strSN;
	GetSN(strSN, strPath);

	return MoveFile(strPath, strBakDir+_T("\\")+strYearMonth+_T("\\")+strSN+_T(".tmp"));
}

BOOL CTxtFile::Exist(CString strPath, CString strBakDir, CString &strHistoryTmp)
{
	CString strYearMonth;
	CString strSN;
	GetSN(strSN, strPath);

	int nYear, nMonth, nDay;
	int nYearPre, nMonthPre;
	GetCrtDate(nYear, nMonth, nDay);

	const int nPreviousMonth=12;
	for (int i=0; i<=nPreviousMonth; i++)
	{
		nYearPre  = (nYear*12+nMonth-i)/12;
		nMonthPre = (nYear*12+nMonth-i)%12;

		strYearMonth.Format(_T("%d\\%d"), nYearPre, nMonthPre);

		if (FileExist(strBakDir+_T("\\")+strYearMonth+_T("\\")+strSN+_T(".tmp")) )
		{
			strHistoryTmp = strBakDir+_T("\\")+strYearMonth+_T("\\")+strSN+_T(".tmp");
			return TRUE;
		}
	}
	
	return FALSE;
}

BOOL CTxtFile::GetSN(CString &strSN, CString strPath)
{
	BOOL bRet = FALSE;

	CStdioFile StdioFile;
	
	if (!StdioFile.Open(strPath, CStdioFile::modeRead|CStdioFile::shareExclusive))
	{
		return FALSE;
	}

	setlocale( LC_CTYPE, "chs" );

	if (!StdioFile.ReadString(strSN))
	{
		goto LClearup;
	}

	if (!StdioFile.ReadString(strSN))
	{
		goto LClearup;
	}

	strSN = strSN.Right(strSN.GetLength()-1);
	strSN = strSN.Left(strSN.GetLength()-1);

	bRet = TRUE;
LClearup:
	StdioFile.Close();
	return bRet;
}