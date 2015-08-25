#ifndef _StaticEx_H
#define _StaticEx_H
/////////////////////////////////////////////////////////////////////////////
// CStaticEx window

class AFX_EXT_CLASS CStaticEx : public CStatic
{
// Construction
public:
	CStaticEx();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetFontParam(long lfHeight);
	void SetTextColor(COLORREF TextColor);
	void SetBackColor(COLORREF BackColor);
	void SetText(CString strText, COLORREF TextColor=RGB(0, 0, 0), COLORREF BackColor=RGB(255, 255, 255));
	virtual ~CStaticEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticEx)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	long m_lfHeight;
	COLORREF m_BackColor;
	COLORREF m_TextColor;
};

/////////////////////////////////////////////////////////////////////////////
#endif