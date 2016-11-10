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

CIniFile::CIniFile(LPCTSTR inifile)
{
	m_inifile.Format("%s",inifile);
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
	if (WritePrivateProfileString(sec,key,value,m_inifile))
		return true;
	else
		return false;
}

void CIniFile::Clear()
{
	DeleteFile(m_inifile);
}

bool CIniFile::SetIntValue(LPCTSTR sec,LPCTSTR key,int value)
{
	CString sval;
	sval.Format("%d",value);
	return SetStringValue(sec,key,sval);
}

int CIniFile::GetIntValue(LPCTSTR sec,LPCTSTR key,int defvalue)
{
	CString sdefvalue,svar;
	sdefvalue.Format("%d",defvalue);
	svar=GetStringValue(sec,key,sdefvalue);
	return atoi(svar);
}