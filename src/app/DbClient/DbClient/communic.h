#include <list>
#ifndef _communic_h_
#define _communic_h_
#include "../..\\include\\commpack.h"
using namespace std;

#define MAX_DBPROXY  20

typedef struct{
	char ip[20];
	int port;
	SOCKET sock;
	int no;
}Th_TcpSendRecv_Para;

typedef struct{
	char ip[20];
	int  sendport;
	int  recvport;
	SOCKET sendsock;
	SOCKET recvsock;
	bool threadrun;
	void clear()
	{
		memset(ip,0,20);
		sendport=0;
		recvport=0;
		sendsock=0;
		recvsock=0;
		threadrun=false;
	}
}DBProxy;

extern bool gThread_TcpSend_RunFlag;
extern DBProxy gDBProxyList[MAX_DBPROXY];
extern int gDBProxyCnt;
extern SOCKET gTCPSrvSock;
extern int gDBSrvPort;

SOCKET GetDBProxySock(int chan);
//bool GetDBProxy(int chan,CString& ip,int& port);
void SendDBPrepare(int chan,LPCTSTR sql,DWORD& sno);
void SendDBSqlExec(int chan,DWORD& sno);
void SendDBSqlOpen(int chan,DWORD& sno);
void SendDBSetParam(int chan,BYTE ind,BYTE InOut,int vType,int iValue,double fValue,
					const char* sValue,const char* tValue,DWORD& sno);
void SendDBUdpateField(int chan,BYTE ind,int vType,int iValue,double fValue,
					const char* sValue,const char* tValue,DWORD& sno);
void SendDBGetParamOut(int chan,int ind,int type,DWORD& sno);
void SendDBGetField(int chan,int ind,int type,DWORD& sno);
void SendDBMoveBy(int chan,int MoveBy,DWORD& sno);
void SendDBOpCmd(int chan,int MsgType,DWORD& sno);
void SendDBData(int chan,int proxycode,LPCTSTR data);
void SendDBPak(int chan,DBPacket pak);
void SendDBSetDB(int chan,LPCTSTR dbname);
void SendDBClose(int chan);

bool StartSock();
void Thread_TCPConnect(LPVOID param);
void Thread_TcpRecv(LPVOID param);
void Thread_TcpSend(LPVOID param);
void BrdDBProxyCfg();

#endif
