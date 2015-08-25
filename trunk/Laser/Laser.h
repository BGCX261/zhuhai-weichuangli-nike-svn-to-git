// Laser.h : main header file for the LASER application
//

#if !defined(AFX_LASER_H__5DC9D9FF_2DE7_4F67_9C65_854291DEFFB1__INCLUDED_)
#define AFX_LASER_H__5DC9D9FF_2DE7_4F67_9C65_854291DEFFB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLaserApp:
// See Laser.cpp for the implementation of this class
//

class CLaserApp : public CWinApp
{
public:
	CLaserApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLaserApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLaserApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LASER_H__5DC9D9FF_2DE7_4F67_9C65_854291DEFFB1__INCLUDED_)
