; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSockSrvDemoDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SockSrvDemo.h"

ClassCount=3
Class1=CSockSrvDemoApp
Class2=CSockSrvDemoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SOCKSRVDEMO_DIALOG

[CLS:CSockSrvDemoApp]
Type=0
HeaderFile=SockSrvDemo.h
ImplementationFile=SockSrvDemo.cpp
Filter=N

[CLS:CSockSrvDemoDlg]
Type=0
HeaderFile=SockSrvDemoDlg.h
ImplementationFile=SockSrvDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDCONTENT

[CLS:CAboutDlg]
Type=0
HeaderFile=SockSrvDemoDlg.h
ImplementationFile=SockSrvDemoDlg.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SOCKSRVDEMO_DIALOG]
Type=1
Class=CSockSrvDemoDlg
ControlCount=4
Control1=IDC_EDRECVPAK,edit,1352728708
Control2=IDC_EDCONTENT,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_EDCODE,edit,1350631552

