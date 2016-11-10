#pragma once

// CCommSrvSock ÃüÁîÄ¿±ê

class CCommSrvSock : public CSocket
{
public:
	CCommSrvSock();
	virtual ~CCommSrvSock();
    virtual void OnReceive(int nErrorCode);
    virtual void OnClose(int nErrorCode);
    int m_socktype;
    void SendDBClose(int chan);
    void SendDBPrepare(int chan, LPCTSTR sql, DWORD& sno);
    void SendDBSqlExec(int chan, DWORD& sno);
    void SendDBSqlOpen(int chan, DWORD& sno);
    void SendDBMoveBy(int chan, int MoveBy, DWORD& sno);


};


