// TxtFile.h: interface for the CTxtFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TXTFILE_H__BD482EF4_D13B_4204_903A_2777E85F866D__INCLUDED_)
#define AFX_TXTFILE_H__BD482EF4_D13B_4204_903A_2777E85F866D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTxtFile  
{
public:
	CTxtFile();
	virtual ~CTxtFile();


	/*
	strPath:文本文件路径
	strBakDir:备份总文件夹路径
	*/
	static BOOL BakFile(CString strPath, CString strBakDir);
	static BOOL GetSN(CString &strSN, CString strPath);
	static BOOL Exist(CString strPath, CString strBakDir, CString &strHistoryTmp);
	

};

#endif // !defined(AFX_TXTFILE_H__BD482EF4_D13B_4204_903A_2777E85F866D__INCLUDED_)
