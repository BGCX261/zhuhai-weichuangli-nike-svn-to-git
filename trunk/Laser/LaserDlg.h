// LaserDlg.h : header file
//

#if !defined(AFX_LASERDLG_H__6B0917F5_52B2_47DD_9D14_8FAFFC83BBD9__INCLUDED_)
#define AFX_LASERDLG_H__6B0917F5_52B2_47DD_9D14_8FAFFC83BBD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLaserDlg dialog

class CLaserDlg : public CDialogEx
{
private:
	bool IsManager(void);
	BOOL m_bAppHadQuit;
	HANDLE m_hMarkEvent;
	HANDLE m_hDelAllTmpEvent;
	
	CStringArray m_strTxtArray;
	CIniFile m_IniFile;
	CWinThread *m_pThread;
	CStaticEx *m_pCtrTxtShow[4];
	CString m_strObjName[4];
	CString m_strFixedObjName[4];
	CStdioFile m_LogStdioFile;

	CString m_strPwd;
// Construction
public:
	void UpdateTxtShow();
	void DelTmpFileByArray();
	BOOL IsScanRepeat();
	void ClearTxtShow();
	void MarkTxtArray(void);
	CLaserDlg(CWnd* pParent = NULL);	// standard constructor
	~CLaserDlg();
// Dialog Data
	//{{AFX_DATA(CLaserDlg)
	enum { IDD = IDD_LASER_DIALOG };
	CStaticEx	m_ctrTxt4;
	CStaticEx	m_ctrTxt3;
	CStaticEx	m_ctrTxt2;
	CStaticEx	m_ctrTxt1;
	CQMarkEzdWnd m_MarkEzd;
	CString	m_strTxtFileDir;
	CString	m_strBakFileDir;
	CString	m_strEzdPath;
	CString	m_strLogPath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLaserDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLaserDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonTxtDirChoose();
	afx_msg void OnButtonBakDirChoose();
	afx_msg void OnButtonEzdPathChoose();
	afx_msg void OnButtonMark();
	afx_msg void OnButtonLogPathChoose();
	afx_msg void OnButtonDeleteAllTmp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	friend UINT MarkThread(LPVOID lp);
};

UINT MarkThread(LPVOID lp);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LASERDLG_H__6B0917F5_52B2_47DD_9D14_8FAFFC83BBD9__INCLUDED_)
