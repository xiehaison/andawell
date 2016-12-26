// SockClt.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "SockClt.h"
#include "cltintf.h"
#include <process.h>
#include <sys/timeb.h>
#include <stdio.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

void DBGMsg(LPCTSTR DbgMessage,...)
{
    char buf[1024];
    memset(buf,0,1024);
	
    va_list args;
    va_start(args, DbgMessage);
    _vsnprintf (buf, sizeof(buf), DbgMessage, args);
    va_end(args);
	
    strcat(buf, "\n");
    char str[512];
    memset(str, 0, sizeof(str));
    strcat(str, buf);
	
    struct _timeb tstruct;
    _ftime( &tstruct );
	
	char line[1024]="";
    sprintf(line,"%d=>%s",GetTickCount(),str);
    OutputDebugString(line);
}

SOCKET gSendSock;
SOCKET gRecvSock;
char gCenIP[20]="";
int  gCenPort;
int  gMyCode;
int  gPakSize=0;
Func_CltRecvPak gFuncRecvPak=NULL;
Func_CltSysMsg  gFuncSysMsg=NULL;

bool gThread_CltRecv_Run;
bool gThread_CltSend_Run;
bool gThread_KeepAlive_Run;

YTQueue<RemInPak> gSendBuf;
int gKeepAlive=MAX_IDLE_TIME;

SOCKCLT_API void HookCltRecvPak(Func_CltRecvPak funcaddr)
{
	gFuncRecvPak=funcaddr;
}

SOCKCLT_API void HookCltSysMsg(Func_CltSysMsg funcaddr)
{
	gFuncSysMsg=funcaddr;
}

bool InitSockEnv(void)
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
	
    wVersionRequested = MAKEWORD( 2, 2 );
	
    WSACleanup();
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 )
        return false;
    if ( LOBYTE( wsaData.wVersion ) != 2 ||HIBYTE( wsaData.wVersion ) != 2 )
    {
        WSACleanup();
        return false;
    }
    return true;
}

bool InitClientSock()
{
    gRecvSock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (gRecvSock==INVALID_SOCKET)
    {
        return false;
    }
    struct sockaddr_in local;
    local.sin_port=0;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;
	
    if (bind(gRecvSock, (struct sockaddr *)&local, sizeof(local))!=0)
    {
        return false;
    }
	
    LINGER l;
    l.l_linger=0;
    l.l_onoff=1;
    setsockopt(gRecvSock,SOL_SOCKET,SO_LINGER,(const char*)&l,sizeof(l));
	
    gSendSock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (gSendSock==INVALID_SOCKET)
    {
        return false;
    }
    local.sin_port=0;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;
    if (bind(gSendSock, (struct sockaddr *)&local, sizeof(local))!=0)
    {
        return false;
    }
	
    l.l_linger=0;
    l.l_onoff=1;
    setsockopt(gSendSock,SOL_SOCKET,SO_LINGER,(const char*)&l,sizeof(l));
 
   return true;
	
}

SOCKCLT_API void SetPara(const char* cenip,int cenport,int mycode,int paksize)
{
	memset(gCenIP,0,20);
	if(strlen(cenip)>20)
		memcpy(gCenIP,cenip,20);
	else
		strcpy(gCenIP,cenip);
	gCenPort=cenport;
	gMyCode=mycode;
	gPakSize=paksize;
//	gSendBuf.SetPakSize(paksize);
}

bool Connect()
{
    struct sockaddr_in remote;
    remote.sin_family = AF_INET;
    remote.sin_port=htons(gCenPort);
    remote.sin_addr.s_addr = inet_addr(gCenIP);
    if (connect(gRecvSock,(sockaddr*)&remote,sizeof(sockaddr))!=0)
        return false;
    if (connect(gSendSock,(sockaddr*)&remote,sizeof(sockaddr))!=0)
        return false;
	
    _beginthread(Thread_CltRecv,100,NULL);
    _beginthread(Thread_CltSend,100,NULL);
	return true;
}

void Thread_CltRecv(LPVOID param)
{
	Identify iden;
	char buf[MAX_PAKSIZE];
	RemInPak rpak;
	int recved;
	int sended;

	gThread_CltRecv_Run=true;

	iden.CltCode=gMyCode;
	iden.SockType=SOCK_RECV;
	sended=send(gRecvSock,(char*)&iden,sizeof(iden),0);
	if (sended==SOCKET_ERROR)
		goto err;

	Sleep(500);

	DBGMsg("recv thread run");
	gFuncSysMsg(MSG_CLT_RECV_CONNECT);
	while(gThread_CltRecv_Run)
	{
		recved=recv(gRecvSock,(char*)(&rpak),sizeof(rpak),0);
		if(recved==SOCKET_ERROR)
			goto err;
		while(recved<sizeof(rpak))
		{
			int rt;
			rt=recv(gRecvSock,(char*)(buf+recved),sizeof(rpak)-recved,0);
			if (rt==SOCKET_ERROR)
				goto err;
			recved=recved+rt;
		}

		gKeepAlive=MAX_IDLE_TIME;

		if(gFuncRecvPak!=NULL)
			gFuncRecvPak(buf);
		
		Sleep(10);
	}
err:
	gThread_CltRecv_Run=false;
	if(gSendSock!=0)
		closesocket(gSendSock);

	if(gFuncSysMsg!=NULL)
		gFuncSysMsg(MSG_CLT_DISCONNECT);
	DBGMsg("recv thread quit");
}

void Thread_CltSend(LPVOID param)
{
	Identify iden;
//	char pak[MAX_PAKSIZE];
	RemInPak spak,nspak;

	int sended;
	char KeepAlive[MAX_PAKSIZE];
	int i;
	
	gThread_CltSend_Run=true;
	for(i=0;i<MAX_PAKSIZE;i++)
	{
		KeepAlive[i]=0;
	}

	iden.CltCode=gMyCode;
	iden.SockType=SOCK_SEND;
	sended=send(gSendSock,(char*)&iden,sizeof(iden),0);
	if(sended==SOCKET_ERROR)
		goto err;

	Sleep(500);
	DBGMsg("send thread run");
	gFuncSysMsg(MSG_CLT_SEND_CONNECT);
	while(gThread_CltSend_Run)
	{
		if(!gSendBuf.IsEmpty())
		{
			gSendBuf.RemoveHead(spak);
			nspak.brdno=htonl(spak.brdno);
			nspak.chno=htonl(spak.chno);
			nspak.cmdtype=htonl(spak.cmdtype);
			nspak.node=htonl(spak.node);

			sended=send(gSendSock,(char*)(&nspak),sizeof(spak),0);
			DBGMsg("sock clt send %d,%d,%d,%d byte",
				spak.brdno,spak.chno,spak.cmdtype,spak.node);
			if(sended==SOCKET_ERROR)
				goto err;
			while(sended<sizeof(spak))
			{
				int st;
				st=send(gSendSock,(char*)(&spak)+sended,sizeof(spak)-sended,0);
				if(st==SOCKET_ERROR)
					goto err;
				sended=sended+st;
			}
			gKeepAlive=MAX_IDLE_TIME;
		}
		Sleep(10);

	}
err:
	gThread_CltSend_Run=false;
	if(gRecvSock!=0)
		closesocket(gRecvSock);

	if(gFuncSysMsg!=NULL)
		gFuncSysMsg(MSG_CLT_DISCONNECT);
	DBGMsg("send thread quit");
}

void Thread_KeepAlive(LPVOID param)
{
	while(true)
	{
		if(gThread_CltSend_Run==false||gThread_CltRecv_Run==false)
		{
			DBGMsg("connect center %s[%d]",gCenIP,gCenPort);
			InitClientSock();
			Connect();
		}
		Sleep(1000);
	}
}

SOCKCLT_API void SendPacket(const char* buf)
{
	RemInPak pak;
	memcpy(&pak,buf,sizeof(pak));
	if(!gSendBuf.AddTail(pak))
	{
		gSendBuf.RemoveAll();
		gSendBuf.AddTail(pak);
	}
}

SOCKCLT_API bool StartUpClt()
{
	if (!InitSockEnv())
		return false;
	if(!InitClientSock())
		return false;
	_beginthread(Thread_KeepAlive,100,NULL);
	return true;
}

SOCKCLT_API void ConnectCenter()
{
	closesocket(gSendSock);
	closesocket(gRecvSock);
	InitClientSock();
	Connect();
}
