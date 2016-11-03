#pragma once
class CIniFile  
{
private:
	CString m_inifile;
public:
	CIniFile(LPCTSTR inifile);
	virtual ~CIniFile();
	void Clear();

	bool SetStringValue(LPCTSTR sec,LPCTSTR key,LPCTSTR value);
	CString GetStringValue(LPCTSTR sec,LPCTSTR key,LPCTSTR def);

	bool SetIntValue(LPCTSTR sec,LPCTSTR key,int value);
	int GetIntValue(LPCTSTR sec,LPCTSTR key,int defvalue);
};

