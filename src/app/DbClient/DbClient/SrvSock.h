#pragma once
using namespace std;
#include "afxtempl.h"
#include "CommSrvSock.h"


// CSrvSock ÃüÁîÄ¿±ê
class CSrvSock : public CSocket
{
public:
	CSrvSock();
	virtual ~CSrvSock();
    virtual void OnAccept(int nErrorCode);
    virtual void OnConnect(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
    virtual void OnClose(int nErrorCode);
    CList < CCommSrvSock*, CCommSrvSock * > m_sock_list;

};


