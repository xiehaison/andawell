; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDBGateDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dbgate.h"
LastPage=0

ClassCount=5
Class1=CDBGateApp
Class2=CAboutDlg
Class3=CDBGateDlg
Class4=CSocket_Recv
Class5=CSocket_Send

ResourceCount=2
Resource1=IDD_ABOUTBOX
Resource2=IDD_DBGATE_DIALOG

[CLS:CDBGateApp]
Type=0
BaseClass=CWinApp
HeaderFile=DBGate.h
ImplementationFile=DBGate.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DBGateDlg.cpp
ImplementationFile=DBGateDlg.cpp
LastObject=CAboutDlg

[CLS:CDBGateDlg]
Type=0
BaseClass=CDialog
HeaderFile=DBGateDlg.h
ImplementationFile=DBGateDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST_COMMANDSERIAL

[CLS:CSocket_Recv]
Type=0
BaseClass=CAsyncSocket
HeaderFile=Socket_Recv.h
ImplementationFile=Socket_Recv.cpp
LastObject=CSocket_Recv

[CLS:CSocket_Send]
Type=0
BaseClass=CAsyncSocket
HeaderFile=Socket_Send.h
ImplementationFile=Socket_Send.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=9
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1350569991
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_DBGATE_DIALOG]
Type=1
Class=CDBGateDlg
ControlCount=20
Control1=IDC_LIST_COMMAND,SysListView32,1350631425
Control2=IDC_LIST_CHANNEL,SysListView32,1082195969
Control3=IDC_LIST_COMMANDSERIAL,SysListView32,1082195969
Control4=IDC_LIST_SENDSERIAL,SysListView32,1082195969
Control5=IDC_LIST_BUF,SysListView32,1082195969
Control6=IDOK,button,1073807361
Control7=IDCANCEL,button,1073807360
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_TAB1,SysTabControl32,1342177280
Control12=IDC_BUTTON_DB,button,1342242816
Control13=IDC_EDIT1,edit,1350633600
Control14=IDC_EDIT2,edit,1350633600
Control15=IDC_EDIT3,edit,1350633600
Control16=IDC_CHECK1,button,1342242819
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT4,edit,1350631552
Control19=IDC_BUTTON_CONFIG,button,1342242816
Control20=IDC_BUTTON_VIEW,button,1342242816

