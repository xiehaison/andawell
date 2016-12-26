; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ResourceCount=0
ClassCount=4
Class1=CSrvSocketApp
LastClass=CCommSend
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "resource.h"
ODLFile=SrvSocket.idl
LastPage=0
Class2=CLsnSocket
Class3=CCommSocket
Class4=CCommSend


[CLS:CSrvSocketApp]
Type=0
HeaderFile=SrvSocket.h
ImplementationFile=SrvSocket.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CSrvSocketApp

[CLS:CLsnSocket]
Type=0
HeaderFile=LsnSocket.h
ImplementationFile=LsnSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CLsnSocket
VirtualFilter=uq

[CLS:CCommSocket]
Type=0
HeaderFile=CommSocket.h
ImplementationFile=CommSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CCommSocket
VirtualFilter=uq

[CLS:CCommSend]
Type=0
HeaderFile=CommSend.h
ImplementationFile=CommSend.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CCommSend

