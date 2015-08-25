#if !defined(AFX_DIALOGEX_H__9B7E40F8_08E5_4ABA_BAB0_DBCC3F91B39C__INCLUDED_)
#define AFX_DIALOGEX_H__9B7E40F8_08E5_4ABA_BAB0_DBCC3F91B39C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogEx dialog
class CResizeCtrl;

class AFX_EXT_CLASS CDialogEx : public CDialog
{
public:
	enum AlignType
	{
		LeftTopAlignType = 0,
		LeftBottomAlignType,
		RightTopAlignType,
		RightBottomAlignType
	};

public:
	virtual  ~CDialogEx();
	CDialogEx( UINT uID, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogEx)
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL AddToolTips(CWnd *pItemWnd, CString strTip);
	VOID ResizeItem(UINT uID, AlignType iAlign, BOOL IsRightLength, BOOL IsBottomLength);

	// Generated message map functions
	//{{AFX_MSG(CDialogEx)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	

private:
	CToolTipCtrl m_ToolTipCtrl;
	CResizeCtrl *m_pResizeCtrl;
	CRect m_rtWndMinSize;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGEX_H__9B7E40F8_08E5_4ABA_BAB0_DBCC3F91B39C__INCLUDED_)
