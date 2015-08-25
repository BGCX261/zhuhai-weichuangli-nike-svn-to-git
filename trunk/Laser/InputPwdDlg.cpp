// InputPwdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "laser.h"
#include "InputPwdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputPwdDlg dialog


CInputPwdDlg::CInputPwdDlg(CString strPwdCmp, CWnd* pParent /*=NULL*/)
	: CDialog(CInputPwdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputPwdDlg)
	m_strPwdInput = _T("");
	//}}AFX_DATA_INIT
	m_strPwdCmp = strPwdCmp;
}


void CInputPwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputPwdDlg)
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwdInput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputPwdDlg, CDialog)
	//{{AFX_MSG_MAP(CInputPwdDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputPwdDlg message handlers

void CInputPwdDlg::OnOK() 
{
	UpdateData(TRUE);
	
	if (m_strPwdInput!=m_strPwdCmp)
	{
		AfxMessageBox(_T("密码不正确，请重新输入。"));
		m_strPwdInput = _T("");
		UpdateData(FALSE);
		return;
	}

	CDialog::OnOK();
}

void CInputPwdDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
