// AdoDB.h: interface for the CAdoDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADODB_H__99B3A0F6_847A_4922_B47F_88FAE544424B__INCLUDED_)
#define AFX_ADODB_H__99B3A0F6_847A_4922_B47F_88FAE544424B__INCLUDED_
#import "c:/Program Files/Common Files/System/ado/msado15.DLL" no_namespace rename("EOF","adoEOF")
#include <atldbcli.h>
#include <vector>
#include <list>
#include <map>
#include <string.h>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAdoDB  
{
public:
	_ConnectionPtr _ctp;//连接
//	_RecordsetPtr _rs;

	typedef struct{
		BYTE vType;
		BYTE InOut;	//#define PARAM_IN   0#define PARAM_OUT  1

		union{
			DWORD  IValue;
			double FValue;
			char   TValue[14];
			char   SValue[256];
		};
	}SQLPara;
	typedef struct tagcommand{
		int iaCount[2];
		bool bIsWait;
		int iCurCmd;		//当前指令；

		int iCmdType;		//0,adProc 1,adText
		string SQL;

		map <int,VARIANT> inpara;
		map <int,VARIANT> outpara;

		_CommandPtr _cp;
		_RecordsetPtr _rs;

		tagcommand(){
			iaCount[0]=0;iaCount[1]=0;
			bIsWait = false;
			iCmdType	= -1;
			iCurCmd		= -1;
			HRESULT hr	= _cp.CreateInstance(__uuidof(Command));
			_rs.CreateInstance(__uuidof(Recordset));
		}
		~tagcommand(){
			_cp.Detach();
			_rs.Detach();
		}

	}command;
	std::vector <command> m_ch;
//	command m_ch[150];

public:
	char * GetCurTime(char *buf);
	void WriteLog(char * des);
	BOOL CloseDB();
	BOOL OpenDB();
	void Initialize();
	CAdoDB();
	virtual ~CAdoDB();
};

#endif // !defined(AFX_ADODB_H__99B3A0F6_847A_4922_B47F_88FAE544424B__INCLUDED_)
