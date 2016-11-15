// AdoDB.cpp: implementation of the CAdoDB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DBAgent.h"
#include "AdoDB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdoDB::CAdoDB()
{
	char szBuf[255];
	WriteLog(GetCurTime(szBuf));
	CoInitialize(NULL);
	HRESULT hr = _ctp.CreateInstance(__uuidof(Connection));
	m_ch.resize(GetPrivateProfileInt("chan","cnt",0,"./DBAgent.ini"));
}

CAdoDB::~CAdoDB()
{
	_ctp.Detach();
}

void CAdoDB::Initialize()
{
	OpenDB();
}

BOOL CAdoDB::OpenDB()
{
	char szServer[255];
	char szUser[255];
	char szPassword[255];
	char szDef[255];

	GetPrivateProfileString("DATABASE", "SERVER", 
                           "", szServer, sizeof(szServer), 
                           "./DBAgent.ini");
	GetPrivateProfileString("DATABASE", "USR", 
                           "", szUser, sizeof(szServer), 
                           "./DBAgent.ini");
	GetPrivateProfileString("DATABASE", "PWD", 
                           "", szPassword, sizeof(szServer), 
                           "./DBAgent.ini");
	GetPrivateProfileString("DATABASE", "DEF", 
                           "", szDef, sizeof(szServer), 
                           "./DBAgent.ini");

	char strConnect[512];
    sprintf(strConnect, "provider = sqloledb;server=%s;database=%s;"
        , szServer, szDef);
    //sprintf(strConnect, "provider = OraOLEDB.Oracle;server=%s;database=%s;"
    //    , szServer, szDef);

	try{
		HRESULT hr=_ctp->Open(_bstr_t(strConnect),_bstr_t(szUser),_bstr_t(szPassword),adOptionUnspecified);
		if(!SUCCEEDED(hr))	return false;
	}
	catch(_com_error & e) 
	{
		WriteLog((LPTSTR)LPCTSTR(e.Description()));
		return false;
	}
	return TRUE;
}

BOOL CAdoDB::CloseDB()
{
	try{
		_ctp->Close();

	}
	catch(_com_error & e) 
	{
		WriteLog((LPTSTR)LPCTSTR(e.Description()));
		return false;
	}
	return TRUE;
}

void CAdoDB::WriteLog(char *des)
{
	FILE * sp = fopen("./DBAgent.log","a");
	if(sp)
	{
		fprintf(sp,"%s\n",des);
		fclose(sp);
	}
}

char * CAdoDB::GetCurTime(char * buf)
{
	time_t lt;
	time(&lt);
	struct tm * curtime = localtime( &lt);
	sprintf(buf,"%4d-%02d-%02d %02d:%02d:%02d"
		,curtime->tm_year+1900
		,curtime->tm_mon+1
		,curtime->tm_mday
		,curtime->tm_hour
		,curtime->tm_min
		,curtime->tm_sec);

	return buf;
}
