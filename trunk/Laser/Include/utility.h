#ifndef _utility_H
#define _utility_H


// 工具箱初始化
AFX_EXT_API void UtilityInit(CWnd *pWnd);

// 释放资源文件
AFX_EXT_API bool ReleaseResFile(HMODULE hModule, WORD wResID, const CString &strResType, const CString &strTrgFilePath);

// 根据函数地址获得模块首地址
AFX_EXT_API HMODULE WINAPI ModuleFromAddress(PVOID pv);

// 得到Windows文件夹路径
AFX_EXT_API CString GetWindowsDir(bool bWithBackslash=true);

// 判断文件是否存在
AFX_EXT_API BOOL FileExist(const CString &strFilePath);

// 得到主程序所在目录，最后带反斜杠
AFX_EXT_API CString GetExeDir(void);

// 得到主程序文件名
AFX_EXT_API CString GetExeName(void);

// 得到当前年月日
AFX_EXT_API void GetCrtDate(int &iYear, int &iMonth, int &iDay);

// 创建文件夹
AFX_EXT_API BOOL CreateFolder(CString strDirPath);

// 文件选择对话框
AFX_EXT_API BOOL FileDlgEzd(CString &strFilePath);

// 文件夹选择对话框，在主线程中调用
AFX_EXT_API BOOL FolderDlg(CString &strFolder);

#endif