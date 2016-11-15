// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__1C846587_5230_446D_9708_DB08EDE0F4A2__INCLUDED_)
#define AFX_STDAFX_H__1C846587_5230_446D_9708_DB08EDE0F4A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0602
#endif
#define _ATL_APARTMENT_THREADED

#include <afxwin.h>
#include <afxdisp.h>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <afxsock.h>

using namespace std;
#include <iostream>
#include <fstream>

#include "../..\\include\\commpack.h"
#include "../..\\include\\basedef.h"
#include "../..\\include\\ctidef.h"

void F_Notify(char *msg, int node, int dir, int notify);




void Output(LPCTSTR DbgMessage,...);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1C846587_5230_446D_9708_DB08EDE0F4A2__INCLUDED)
