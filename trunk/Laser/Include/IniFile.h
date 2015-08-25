// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__8B5D7960_8A8E_4941_910D_1556BE367029__INCLUDED_)
#define AFX_INIFILE_H__8B5D7960_8A8E_4941_910D_1556BE367029__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CIniFile  
{
public:
	/************************************************************************
	* 配置文件默认与主程序在同一目录HGLaser.INI，当前Section名为Default
	************************************************************************/
	CIniFile();
	virtual ~CIniFile();

public:
	void SetIniFilePath(CString strIniFilePath);
	void SetCrtSectionName(CString strCrtSectionName);

	BOOL ReadKey(CString strKeyName, CString &strKeyValue, BOOL bWriteBack=TRUE, CString strSectionName=m_strCrtSectionName);
	BOOL ReadKey(CString strKeyName, double &dfKeyValue, BOOL bWriteBack=TRUE, CString strSectionName=m_strCrtSectionName);
	BOOL ReadKey(CString strKeyName, int &nKeyValue, BOOL bWriteBack=TRUE, CString strSectionName=m_strCrtSectionName);
	
	BOOL WriteKey(CString strKeyName, CString strKeyValue, CString strSectionName=m_strCrtSectionName);
	BOOL WriteKey(CString strKeyName, double dfKeyValue, CString strSectionName=m_strCrtSectionName);
	BOOL WriteKey(CString strKeyName, int nKeyValue, CString strSectionName=m_strCrtSectionName);

private:
	CString m_strIniFilePath;
	static CString m_strCrtSectionName;
};

#endif // !defined(AFX_INIFILE_H__8B5D7960_8A8E_4941_910D_1556BE367029__INCLUDED_)
