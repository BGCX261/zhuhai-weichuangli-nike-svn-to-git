; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLaserDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "laser.h"
LastPage=0

ClassCount=3
Class1=CLaserApp
Class2=CLaserDlg

ResourceCount=2
Resource1=IDD_LASER_DIALOG
Class3=CInputPwdDlg
Resource2=IDD_DIALOG_INPUT_PWD

[CLS:CLaserApp]
Type=0
BaseClass=CWinApp
HeaderFile=Laser.h
ImplementationFile=Laser.cpp
LastObject=CLaserApp

[CLS:CLaserDlg]
Type=0
BaseClass=CDialogEx
HeaderFile=LaserDlg.h
ImplementationFile=LaserDlg.cpp
LastObject=IDC_BUTTON_MARK
Filter=D
VirtualFilter=dWC

[DLG:IDD_LASER_DIALOG]
Type=1
Class=CLaserDlg
ControlCount=23
Control1=IDOK,button,1208025089
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC_MARKDLL,static,1350565895
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_TXT_DIR,edit,1484849280
Control7=IDC_EDIT_BAK_DIR,edit,1484849280
Control8=IDC_BUTTON_TXT_DIR_CHOOSE,button,1342242817
Control9=IDC_BUTTON_BAK_DIR_CHOOSE,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_EZD_PATH,edit,1484849280
Control12=IDC_BUTTON_EZD_PATH_CHOOSE,button,1342242816
Control13=IDC_BUTTON_MARK,button,1342242816
Control14=IDC_STATIC_TXT1,static,1342308352
Control15=IDC_STATIC_TXT2,static,1342308352
Control16=IDC_STATIC_TXT3,static,1342308352
Control17=IDC_STATIC_TXT4,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT_LOG_PATH,edit,1484849280
Control20=IDC_BUTTON_LOG_PATH_CHOOSE,button,1342242816
Control21=IDC_BUTTON_DELETE_ALL_TMP,button,1342242816
Control22=IDC_STATIC_TIME_USE,static,1342312449
Control23=IDC_EDIT1,edit,1350631552

[DLG:IDD_DIALOG_INPUT_PWD]
Type=1
Class=CInputPwdDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_PWD,edit,1350631585

[CLS:CInputPwdDlg]
Type=0
HeaderFile=InputPwdDlg.h
ImplementationFile=InputPwdDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_PWD
VirtualFilter=dWC

