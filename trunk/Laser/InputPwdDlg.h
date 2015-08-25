#if !defined(AFX_INPUTPWDDLG_H__874C7DC1_9650_4434_B1E4_9183710C57C4__INCLUDED_)
#define AFX_INPUTPWDDLG_H__874C7DC1_9650_4434_B1E4_9183710C57C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputPwdDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputPwdDlg dialog

class CInputPwdDlg : public CDialog
{
// Construction
public:
	CInputPwdDlg(CString strPwdCmp, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputPwdDlg)
	enum { IDD = IDD_DIALOG_INPUT_PWD };
	CString	m_strPwdInput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputPwdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputPwdDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strPwdCmp;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTPWDDLG_H__874C7DC1_9650_4434_B1E4_9183710C57C4__INCLUDED_)
