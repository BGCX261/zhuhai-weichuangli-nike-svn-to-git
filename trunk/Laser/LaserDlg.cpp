// LaserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Laser.h"
#include "LaserDlg.h"
#include "TxtFile.h"
#include "InputPwdDlg.h"
#include <MMSYSTEM.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLaserDlg dialog

#define INI_KEY_TXT_DIR  _T("文本文件路径")
#define INI_KEY_BAK_DIR  _T("备份文件路径")
#define INI_KEY_EZD_PATH _T("模板文件路径")
#define INI_KEY_LOG_DIR  _T("日志文件路径")
#define INI_KEY_PWD      _T("软件密码")

#define OBJ_NAME1 _T("s1")
#define OBJ_NAME2 _T("s2")
#define OBJ_NAME3 _T("s3")
#define OBJ_NAME4 _T("s4")


CLaserDlg::CLaserDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CLaserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLaserDlg)
	m_strTxtFileDir = _T("");
	m_strBakFileDir = _T("");
	m_strEzdPath = _T("");
	m_strLogPath = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_bAppHadQuit = FALSE;
	m_strTxtArray.RemoveAll();
	m_hMarkEvent = CreateEvent(NULL, FALSE, FALSE, _T("MarkEvent"));
	m_hDelAllTmpEvent = CreateEvent(NULL, FALSE, FALSE, _T("DelAllTmpEvent"));
	
	m_strTxtFileDir=_T("c:\\Nike");
	m_strBakFileDir=_T("d:\\");
	m_strLogPath = _T("d:\\");
	m_strPwd = _T("888888");
	
	m_IniFile.ReadKey(INI_KEY_TXT_DIR, m_strTxtFileDir, FALSE);
	m_IniFile.ReadKey(INI_KEY_BAK_DIR, m_strBakFileDir, FALSE);
	m_IniFile.ReadKey(INI_KEY_EZD_PATH, m_strEzdPath, FALSE);
	m_IniFile.ReadKey(INI_KEY_LOG_DIR, m_strLogPath, FALSE);
	m_IniFile.ReadKey(INI_KEY_PWD, m_strPwd, TRUE);
	
	m_pCtrTxtShow[0] = &m_ctrTxt1;
	m_pCtrTxtShow[1] = &m_ctrTxt2;
	m_pCtrTxtShow[2] = &m_ctrTxt3;
	m_pCtrTxtShow[3] = &m_ctrTxt4;
	
	m_strFixedObjName[0] = _T("d1");
	m_strFixedObjName[1] = _T("d2");
	m_strFixedObjName[2] = _T("d3");
	m_strFixedObjName[3] = _T("d4");
	
	m_strObjName[0] = OBJ_NAME1;
	m_strObjName[1] = OBJ_NAME2;
	m_strObjName[2] = OBJ_NAME3;
	m_strObjName[3] = OBJ_NAME4;
	
	CString strYearMonthDay = CTime::GetCurrentTime().Format(_T("%Y-%m-%d Mark.txt"));
	CString strCrtLog = (m_strLogPath.Right(1))==_T("\\") ? m_strLogPath+strYearMonthDay : m_strLogPath+_T("\\")+strYearMonthDay;
	m_LogStdioFile.Open(strCrtLog, CStdioFile::modeWrite|CStdioFile::modeNoTruncate|CStdioFile::modeCreate);
	m_LogStdioFile.SeekToEnd();
}
CLaserDlg::~CLaserDlg()
{
	m_LogStdioFile.Close();
}

UINT MarkThread(LPVOID lp)
{
	CLaserDlg *pLaserDlg = (CLaserDlg *)lp;
	
	CStringArray &strTxtArray = pLaserDlg->m_strTxtArray;
	CString strFileFound;
	CString strTxtDir = pLaserDlg->m_strTxtFileDir;
	CFileFind FileFind;
	BOOL bFound = FALSE;
	BOOL bRepeated = FALSE;
	
	CString strSN;
	
	while (!pLaserDlg->m_bAppHadQuit)
	{
		bFound = FileFind.FindFile(strTxtDir+_T("\\*.tmp"));
		while (bFound)
		{
			Sleep(1);
			bFound = FileFind.FindNextFile();
			
			// 如果是文件夹则继续
			if (FileFind.IsDots() || FileFind.IsDirectory())
			{
				continue;
			}
			
			strFileFound = FileFind.GetFilePath();
			
			// 判断该文件是否已添加
			bRepeated = FALSE;
			for (int i=0; i<strTxtArray.GetSize(); i++)
			{
				if (strTxtArray[i]==strFileFound)
				{
					bRepeated = TRUE;
					break;
				}
			}
			
			if (bRepeated)
			{
				continue;
			}
			
			strTxtArray.Add(strFileFound);
		}
		
		FileFind.Close();
		// 查找tmp文件结束
		
		// 判断当前文件个数是否大于0
		if (strTxtArray.GetSize()<=0)
		{
			continue;
		}
		
		// 文件个数超过最大数目时，结束线程
		if (strTxtArray.GetSize()>4)
		{
			MessageBox(pLaserDlg->m_hWnd, _T("文本文件超过 4 个，不能打标。\n\n请关闭打标软件，并清理TMP文件。"), _T("严重警告"), MB_OK);
			pLaserDlg->SetWindowText(_T("请关闭打标软件，并清理TMP文件"));
			break;
		}
		
		Sleep(300);
		
		pLaserDlg->ClearTxtShow();
		
		// 有重复的文件，需要再次搜索
		if (pLaserDlg->IsScanRepeat())
		{
			strTxtArray.RemoveAll();
			continue;
		}		
		
		pLaserDlg->UpdateTxtShow();
		
		if (WAIT_OBJECT_0 == WaitForSingleObject(pLaserDlg->m_hDelAllTmpEvent, 10) )
		{
			pLaserDlg->DelTmpFileByArray();
			continue;
		}
		
		if (WAIT_TIMEOUT == WaitForSingleObject(pLaserDlg->m_hMarkEvent, 10) )
		{
			continue;
		}
		
		pLaserDlg->MarkTxtArray();
		
		strTxtArray.RemoveAll();
		
		pLaserDlg->ClearTxtShow();
	}
	
	return S_OK;
}

void CLaserDlg::MarkTxtArray(void)
{
	CString strSN;
	CString strTime = CTime::GetCurrentTime().Format(_T("%H:%M:%S SN= "));
	
	m_MarkEzd.Lmc1_LoadEzdFile(m_strEzdPath);
	
	int i=0;
	DWORD dwTimeReduceMM = 0;
	
	for (i=0; i<m_strTxtArray.GetSize(); i++)
	{
		CTxtFile::GetSN(strSN, m_strTxtArray[i]);
		
		strSN.MakeUpper();
		m_MarkEzd.Lmc1_ChangeTextByName(m_strObjName[i], strSN);
		
		m_LogStdioFile.WriteString(strTime + strSN + _T("\n"));
		
		dwTimeReduceMM += 250;
	}
	
	for (; i<4; i++)
	{
		m_MarkEzd.Lmc1_DeleteEnt(m_strObjName[i]);
		m_MarkEzd.Lmc1_DeleteEnt(m_strFixedObjName[i]);
	}
	
	CString strTimeUse;
	DWORD dwStart = GetTickCount();
	m_MarkEzd.Lmc1_Mark();
	DWORD dwGap = GetTickCount() - dwStart;
	
	if (dwGap > dwTimeReduceMM)
	{
		dwGap -= dwTimeReduceMM;
	}
	
	strTimeUse.Format(_T("本次用时: %d.%d 秒"), dwGap/1000, dwGap%1000);
	SetDlgItemText(IDC_STATIC_TIME_USE, strTimeUse);
	
	for (i=0; i<m_strTxtArray.GetSize(); i++)
	{
		// Move file
		CTxtFile::BakFile(m_strTxtArray[i], m_strBakFileDir);
	}
	
	ResetEvent(m_hMarkEvent);
}

void CLaserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLaserDlg)
	DDX_Control(pDX, IDC_STATIC_TXT4, m_ctrTxt4);
	DDX_Control(pDX, IDC_STATIC_TXT3, m_ctrTxt3);
	DDX_Control(pDX, IDC_STATIC_TXT2, m_ctrTxt2);
	DDX_Control(pDX, IDC_STATIC_TXT1, m_ctrTxt1);
	DDX_Control(pDX, IDC_STATIC_MARKDLL, m_MarkEzd);
	DDX_Text(pDX, IDC_EDIT_TXT_DIR, m_strTxtFileDir);
	DDX_Text(pDX, IDC_EDIT_BAK_DIR, m_strBakFileDir);
	DDX_Text(pDX, IDC_EDIT_EZD_PATH, m_strEzdPath);
	DDX_Text(pDX, IDC_EDIT_LOG_PATH, m_strLogPath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLaserDlg, CDialogEx)
//{{AFX_MSG_MAP(CLaserDlg)
ON_BN_CLICKED(IDC_BUTTON_TXT_DIR_CHOOSE, OnButtonTxtDirChoose)
ON_BN_CLICKED(IDC_BUTTON_BAK_DIR_CHOOSE, OnButtonBakDirChoose)
ON_BN_CLICKED(IDC_BUTTON_EZD_PATH_CHOOSE, OnButtonEzdPathChoose)
ON_BN_CLICKED(IDC_BUTTON_MARK, OnButtonMark)
ON_BN_CLICKED(IDC_BUTTON_LOG_PATH_CHOOSE, OnButtonLogPathChoose)
ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL_TMP, OnButtonDeleteAllTmp)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLaserDlg message handlers

BOOL CLaserDlg::OnInitDialog()
{
	//	UtilityInit(this);
	
	CDialogEx::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	if (!m_MarkEzd.Lmc1_Initial(m_hWnd) )
	{
		AfxMessageBox(_T("打标卡初始化失败。"));
	}
	
	if (!m_MarkEzd.Lmc1_LoadEzdFile(m_strEzdPath) )
	{
		AfxMessageBox(_T("加载模板文件失败。\n\n")+m_strEzdPath);
	}
	
	ResizeItem(IDC_STATIC_MARKDLL, LeftTopAlignType, TRUE, TRUE);
	ResizeItem(IDC_EDIT_BAK_DIR, LeftTopAlignType, TRUE, FALSE);
	ResizeItem(IDC_EDIT_TXT_DIR, LeftTopAlignType, TRUE, FALSE);
	ResizeItem(IDC_EDIT_EZD_PATH, LeftTopAlignType, TRUE, FALSE);
	ResizeItem(IDC_EDIT_LOG_PATH, LeftTopAlignType, TRUE, FALSE);
	ResizeItem(IDC_BUTTON_LOG_PATH_CHOOSE, RightTopAlignType, FALSE, FALSE);
	ResizeItem(IDC_BUTTON_BAK_DIR_CHOOSE, RightTopAlignType, FALSE, FALSE);
	ResizeItem(IDC_BUTTON_TXT_DIR_CHOOSE, RightTopAlignType, FALSE, FALSE);
	ResizeItem(IDC_BUTTON_EZD_PATH_CHOOSE, RightTopAlignType, FALSE, FALSE);
	ResizeItem(IDC_BUTTON_MARK, RightBottomAlignType, FALSE, FALSE);
	ResizeItem(IDC_BUTTON_DELETE_ALL_TMP, RightBottomAlignType, FALSE, FALSE);
	ResizeItem(IDC_STATIC_TXT1, LeftBottomAlignType, TRUE, FALSE);
	ResizeItem(IDC_STATIC_TXT2, LeftBottomAlignType, TRUE, FALSE);
	ResizeItem(IDC_STATIC_TXT3, LeftBottomAlignType, TRUE, FALSE);
	ResizeItem(IDC_STATIC_TXT4, LeftBottomAlignType, TRUE, FALSE);
	
	
	m_ctrTxt1.SetFontParam(30);
	m_ctrTxt2.SetFontParam(30);
	m_ctrTxt3.SetFontParam(30);
	m_ctrTxt4.SetFontParam(30);
	
	m_pThread = AfxBeginThread(MarkThread, this);
	GetDlgItem(IDC_EDIT1)->SetFocus();
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CLaserDlg::OnOK() 
{
	CDialogEx::OnOK();
}

void CLaserDlg::OnCancel() 
{
	CDialogEx::OnCancel();
}

BOOL CLaserDlg::DestroyWindow() 
{
	m_bAppHadQuit = TRUE;
	Sleep(1000);
	return CDialogEx::DestroyWindow();
}

void CLaserDlg::OnButtonTxtDirChoose() 
{
	if (!IsManager())
	{
		return;
	}
	if (FolderDlg(m_strTxtFileDir) )
	{
		m_IniFile.WriteKey(INI_KEY_TXT_DIR, m_strTxtFileDir);
		UpdateData(FALSE);
		AfxMessageBox(_T("文本文件路径已保存，重启软件生效。"));
	}	
}

void CLaserDlg::OnButtonBakDirChoose() 
{
	if (!IsManager())
	{
		return;
	}
	if (FolderDlg(m_strBakFileDir) )
	{
		m_IniFile.WriteKey(INI_KEY_BAK_DIR, m_strBakFileDir);
		UpdateData(FALSE);
		AfxMessageBox(_T("备份文件路径已保存，重启软件生效。"));
	}
}

void CLaserDlg::OnButtonEzdPathChoose() 
{
	if (!IsManager())
	{
		return;
	}
	if (FileDlgEzd(m_strEzdPath) )
	{
		m_IniFile.WriteKey(INI_KEY_EZD_PATH, m_strEzdPath);
		m_MarkEzd.Lmc1_LoadEzdFile(m_strEzdPath);
		UpdateData(FALSE);
		AfxMessageBox(_T("模板文件路径已保存，重启软件生效。"));
	}
}

void CLaserDlg::OnButtonLogPathChoose() 
{
	if (!IsManager())
	{
		return;
	}
	if (FolderDlg(m_strLogPath) )
	{
		m_IniFile.WriteKey(INI_KEY_LOG_DIR, m_strLogPath);
		UpdateData(FALSE);
		AfxMessageBox(_T("日志文件路径已保存，重启软件生效。"));
	}
	
}

void CLaserDlg::OnButtonMark() 
{
	if (m_strTxtArray.GetSize()<=0)
	{
		AfxMessageBox(_T("没有文本文件，不能打标。"));
	}
	else
	{
		SetEvent(m_hMarkEvent);
	}
	GetDlgItem(IDC_EDIT1)->SetFocus();
}

void CLaserDlg::ClearTxtShow()
{
	for (int i=0; i<(sizeof(m_pCtrTxtShow))/(sizeof(m_pCtrTxtShow[0])); i++)
	{
		m_pCtrTxtShow[i]->SetText(_T(""));
	}
}

BOOL CLaserDlg::IsScanRepeat()
{
	int iLoop1, iLoop2;
	CString strSN1, strSN2;
	CString strHistoryFile;
	BOOL bRet = FALSE;
	CInputPwdDlg InputPwdDlg(m_strPwd);
	int nCfmRet;
	
	for (iLoop1=0; iLoop1<m_strTxtArray.GetSize(); iLoop1++)
	{
		CTxtFile::GetSN(strSN1, m_strTxtArray[iLoop1]);
		
		for (iLoop2=iLoop1+1; iLoop2<m_strTxtArray.GetSize(); iLoop2++)
		{
			CTxtFile::GetSN(strSN2, m_strTxtArray[iLoop2]);
			
			if (strSN1==strSN2)
			{
				DeleteFile(m_strTxtArray[iLoop2]);
				AfxMessageBox(_T("已检测到重复扫描。将删掉: ")+m_strTxtArray[iLoop2], MB_OK);
				bRet = TRUE;
			}
		}
		
		if (CTxtFile::Exist(m_strTxtArray[iLoop1], m_strBakFileDir, strHistoryFile) )
		{
			nCfmRet = IDNO;
			CString strTip = _T("确认需要返工吗，如下条码已标刻过: \n\n") + strSN1;
			while (IDYES== (nCfmRet=AfxMessageBox(strTip, MB_YESNO|MB_ICONQUESTION)) )
			{
				if (IDOK==InputPwdDlg.DoModal() )
				{
					break;
				}
			}
			if (IDNO==nCfmRet)
			{
				DeleteFile(m_strTxtArray[iLoop1]);
				AfxMessageBox(_T("重复的SN号，将删除: ")+m_strTxtArray[iLoop1], MB_OK);
				bRet = TRUE;
			}
			if (IDYES==nCfmRet)
			{
				DeleteFile(strHistoryFile);
			}
		}
	}
	return bRet;
}

void CLaserDlg::OnButtonDeleteAllTmp() 
{
	if (!IsManager())
	{
		return;
	}
	if (IDYES==AfxMessageBox(_T("确认要删除当前所有TMP文件吗"), MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2))
	{
		SetEvent(m_hDelAllTmpEvent);	
	}
}

void CLaserDlg::DelTmpFileByArray()
{
	for (int i=0; i<m_strTxtArray.GetSize(); i++)
	{
		DeleteFile(m_strTxtArray[i]);
	}
	m_strTxtArray.RemoveAll();
	ClearTxtShow();
}

void CLaserDlg::UpdateTxtShow()
{
	CString strSN;
	for (int i=0; i<m_strTxtArray.GetSize(); i++)
	{
		if (!CTxtFile::GetSN(strSN, m_strTxtArray[i]) )
		{
			AfxMessageBox(_T("文本文件格式错误，无法获取 SN。"));
			m_strTxtArray.RemoveAll();
		}
		else
		{
			m_pCtrTxtShow[i]->SetText(strSN, RGB(255, 0, 0));
		}
	}
}

bool CLaserDlg::IsManager()
{
	CInputPwdDlg InputPwdDlg(m_strPwd);
	return (IDOK!=InputPwdDlg.DoModal()) ? false : true;
}

BOOL CLaserDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message==WM_KEYDOWN || pMsg->message == WM_KEYUP)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
