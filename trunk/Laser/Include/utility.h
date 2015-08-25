#ifndef _utility_H
#define _utility_H


// �������ʼ��
AFX_EXT_API void UtilityInit(CWnd *pWnd);

// �ͷ���Դ�ļ�
AFX_EXT_API bool ReleaseResFile(HMODULE hModule, WORD wResID, const CString &strResType, const CString &strTrgFilePath);

// ���ݺ�����ַ���ģ���׵�ַ
AFX_EXT_API HMODULE WINAPI ModuleFromAddress(PVOID pv);

// �õ�Windows�ļ���·��
AFX_EXT_API CString GetWindowsDir(bool bWithBackslash=true);

// �ж��ļ��Ƿ����
AFX_EXT_API BOOL FileExist(const CString &strFilePath);

// �õ�����������Ŀ¼��������б��
AFX_EXT_API CString GetExeDir(void);

// �õ��������ļ���
AFX_EXT_API CString GetExeName(void);

// �õ���ǰ������
AFX_EXT_API void GetCrtDate(int &iYear, int &iMonth, int &iDay);

// �����ļ���
AFX_EXT_API BOOL CreateFolder(CString strDirPath);

// �ļ�ѡ��Ի���
AFX_EXT_API BOOL FileDlgEzd(CString &strFilePath);

// �ļ���ѡ��Ի��������߳��е���
AFX_EXT_API BOOL FolderDlg(CString &strFolder);

#endif