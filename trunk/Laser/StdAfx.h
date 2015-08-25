// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__9A2A5A13_C33C_44D6_AEB9_1572FE8D5DF6__INCLUDED_)
#define AFX_STDAFX_H__9A2A5A13_C33C_44D6_AEB9_1572FE8D5DF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions


#include "Include/QMarkEzdWnd.h"
#include "Include/utilityApi.h"



#ifndef _DEBUG
#pragma comment(lib, "Lib/QMarkEzd.lib")
#pragma comment(lib, "Lib/utility.lib")
#else
#pragma comment(lib, "Lib/QMarkEzdD.lib")
#pragma comment(lib, "Lib/utilityD.lib")
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9A2A5A13_C33C_44D6_AEB9_1572FE8D5DF6__INCLUDED_)
