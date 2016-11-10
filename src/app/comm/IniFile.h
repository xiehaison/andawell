#pragma once
class CIniFile  
{
public:
	void Clear();
	void Create(LPCTSTR inifile);
	CString m_inifile;
	bool SetStringValue(LPCTSTR sec,LPCTSTR key,LPCTSTR value);
	CString GetStringValue(LPCTSTR sec,LPCTSTR key,LPCTSTR def);
	CIniFile();
	virtual ~CIniFile();
};

