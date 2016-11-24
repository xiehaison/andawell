#if !defined(AFX_SOCKET_RECV_H__96F2AB29_5B91_4FB8_828F_3B139FC095F7__INCLUDED_)
#define AFX_SOCKET_RECV_H__96F2AB29_5B91_4FB8_828F_3B139FC095F7__INCLUDED_

#include "AdoDB.h"	// Added by ClassView
#include "Socket_Send.h"	// Added by ClassView
#include "srvcomm.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Socket_Recv.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSocket_Recv command target

class CSocket_Recv : public CAsyncSocket
{
public:
    DWORD nPackLength;
	char szPackBuf[1024*4];
//	void TakeApartPack(char *szReceive,int nLength);
    //void ParsePacket(char *szPack);
    void ParsePacket(T_MsgServer &msg);
    void DisplayPack(T_MsgServer &msg);
    void SendToNote(T_MsgServer &msg);

// Attributes
public:
	int status;//0,关闭 1，正在连接 2，已经连接
	CAdoDB m_db;
    int m_node;
    int CurChan;
	CListCtrl * p_ListRecv;
	CListCtrl * p_ListSend;
	CListCtrl * p_ListBuf;
	CListCtrl * p_ListCommand;

// Operations
public:
	CSocket_Recv();
	virtual ~CSocket_Recv();

// Overrides
public:
	void WriteBillDB(DBPacket pak,int chan);
	void CheckCommandState();
	void WriteLog(char *des);
    void SendToServer(DBPacket &pak);
    void SendToServer(DBPacket &pak,int note);
    void DisplayPack(char * szPack);
	CSocket_Send m_send;
	void ConnectServer();
	void Initialize();
    void TakeApartPack(T_MsgServer *pmsg);
    void SendToServer(T_MsgServer &msg);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocket_Recv)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSocket_Recv)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
};
void RunLog(const char* line,...);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKET_RECV_H__96F2AB29_5B91_4FB8_828F_3B139FC095F7__INCLUDED_)
