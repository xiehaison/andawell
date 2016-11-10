// IniFile1.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniFile::CIniFile()
{

}

CIniFile::~CIniFile()
{

}

CString CIniFile::GetStringValue(LPCTSTR sec, LPCTSTR key, LPCTSTR def)
{
	char temp[1024];
	DWORD res=0;
	memset(temp,0,1024);
	res=::GetPrivateProfileString(sec,key,def,temp,1024,m_inifile);
	if (res>0)
	{
		return CString(temp);
	}else
		return "";
}

bool CIniFile::SetStringValue(LPCTSTR sec, LPCTSTR key, LPCTSTR value)
{
	BOOL res=WritePrivateProfileString(sec,key,value,m_inifile);
	if (res==TRUE)
		return true;
	else
		return false;
}

void CIniFile::Create(LPCTSTR inifile)
{
	m_inifile.Format("%s",inifile);
}

void CIniFile::Clear()
{
	DeleteFile(m_inifile);
}
