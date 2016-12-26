// SockSrv.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "SockSrv.h"
#include "srvintf.h"
#include <process.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <stdio.h>

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
	
	char line[1024]="";
    sprintf(line,"%d=>%s",GetTickCount(),str);
    OutputDebugString(line);
}


//---全局变量
bool gThread_MsgNotify_Run;
bool gThread_SendData;

CltConn gConn[MAX_CONN];   //客户端连接端口数组

YTQueue<RemInPak> gSendBuf;//接收数据缓冲区
YTQueue<RemInPak> gRecvBuf;  //发送数据缓冲区

int gPakSize;    //单个数据包大小    

SOCKET gSrvSock=0;  //
int gSrvPort=0;     //服务器sock端口

Func_SysMsg  gSysMsg=NULL;
Func_SrvRecvPak gFuncRecvPak=NULL;


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

void Thread_KeepAlive(LPVOID param)
{
	//处理心跳保持定时器
	char Zero[MAX_PAKSIZE];
	int i;
	
	for(i=0;i<MAX_PAKSIZE;i++)
		Zero[i]=0;
	while(true)
	{
		for (i=0;i<MAX_CONN;i++)
		{
//			if(gConn[i].sendsock!=0&&gConn[i].recvsock!=0)
//			{
//				gConn[i].KeepAliveTimer-=MAX_IDLE_TIME/4;
//				DBGMsg("client %d time=%d",i,gConn[i].KeepAliveTimer);
//				if(gConn[i].KeepAliveTimer<(-MAX_IDLE_TIME))
//				{
//					DBGMsg("client %d keepalive timeout closed",i);
//					closesocket(gConn[i].sendsock);
//					closesocket(gConn[i].recvsock);
//					gConn[i].sendsock=0;
//					gConn[i].recvsock=0;
//					gConn[i].KeepAliveTimer=MAX_IDLE_TIME;
//				}
//				send(gConn[i].sendsock,Zero,gPakSize,0);
//			}
		}
		Sleep(MAX_IDLE_TIME/4);
	}
}

SOCKSRV_API bool StartUpSrv(int srvport,int paksize)
{
	if(!InitSockEnv())
		return false;

	if(gSrvSock!=0)
		closesocket(gSrvSock);

	if ((paksize+2)>MAX_BUFFSIZE)
		return false;
		
    struct sockaddr_in local;
	
    gSrvSock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (gSrvSock==INVALID_SOCKET)
        return false;
    local.sin_port=htons(srvport);
    local.sin_family=AF_INET;
    local.sin_addr.s_addr=INADDR_ANY;
    if (bind(gSrvSock,(struct sockaddr *)&local, sizeof(local))!=0)
    {
        return false;
    }
	
    if (listen(gSrvSock,SOMAXCONN)==0)
    {
//		gRecvBuf.SetPakSize(paksize+2);
//		gSendBuf.SetPakSize(paksize+2);
		gPakSize=paksize;
		_beginthread(Thread_Accept,0,NULL);
		_beginthread(Thread_MsgNotify,0,NULL);
		_beginthread(Thread_SendData,0,NULL);
		_beginthread(Thread_KeepAlive,0,NULL);
        return true;
    }
    else
        return false;
}

SOCKSRV_API void SendPak(WORD code,const char* buf,int size)
{
	RemInPak spak;
	memcpy(&spak,buf,sizeof(spak));
	spak.node=code;

	if (!gSendBuf.AddTail(spak))//buf,code)==-1)
	{
		gSendBuf.RemoveAll();
		gSendBuf.AddTail(spak);//buf,code);
		if(gSysMsg)
			gSysMsg(MSG_SEND_BUF_FULL,"send buf over flow");
	}
}

SOCKSRV_API void HookRecvPakFunc(Func_SrvRecvPak funcaddr)
{
	gFuncRecvPak=funcaddr;
}

SOCKSRV_API void HookSysMsgFunc(Func_SysMsg funcaddr)
{
	gSysMsg=funcaddr;
}

SOCKSRV_API void ClearUp()
{
}

void Thread_Accept(LPVOID param)
{
	DBGMsg("srv accept thread run");
    while(true)
    {
        SOCKET sock;
        struct sockaddr_in remote;
        int len=sizeof(remote);
        sock=accept(gSrvSock,(struct sockaddr FAR *)&remote,&len);
        if (sock!=INVALID_SOCKET)
        {
            linger t;
            t.l_linger=0;
            t.l_onoff=1;
            setsockopt(sock,SOL_SOCKET,SO_LINGER,(const char FAR*) &t,sizeof(t)) ;
			
			CltConn* conn=new CltConn;
			strcpy(conn->IP,inet_ntoa(remote.sin_addr));
			conn->recvsock=sock;
			DBGMsg("sock %s[%d] connected",conn->IP,conn->recvsock);
			_beginthread(Thread_CltRecv,100,conn);
        }else
            break;
        Sleep(10);
    }
	if(gSysMsg!=NULL)
	{
		int errcode=WSAGetLastError();
		char errmsg[128]="";
		sprintf(errmsg,"Tcp连接监听线程退出,错误原因%d",errcode);
		gSysMsg(MSG_ERROR,errmsg);
	}
	DBGMsg("srv accept thread quit");
}

void Thread_CltRecv(LPVOID param)
{
	CltConn conn;
	int recved;
	Identify iden;
	char errmsg[256]={0};
//	char  recvbuf[MAX_PAKSIZE];
	RemInPak nrpak,rpak;

	int code=-1;
	char ZeroBuf[MAX_PAKSIZE];
	int i;

	for (i=0;i<MAX_PAKSIZE;i++)
		ZeroBuf[i]=0;

	memcpy(&conn,(CltConn*)param,sizeof(conn));
	delete (CltConn*)param;

	DBGMsg("sock %s[%d] wait for login",conn.IP,conn.recvsock);

	
	//接收错误
	recved=recv(conn.recvsock,(char*)&iden,sizeof(iden),0);
	if(recved==SOCKET_ERROR)
		goto err1;

	while(recved<sizeof(iden))
	{
		int rt;
		rt=recv(conn.recvsock,(char*)&iden+recved,sizeof(iden)-recved,0);
		if(rt==SOCKET_ERROR)
		{
			memset(errmsg,0,256);
			sprintf(errmsg,"SockSrv IP[%s]连接错误",conn.IP);
//			sprintf(errmsg,"client socket recv error");
			closesocket(conn.recvsock);
			goto err1;
		}
		recved=recved+rt;
	}

	//包错误
	if(!(iden.head1==HEAD_TAG&&iden.head2==HEAD_TAG))
	{
		memset(errmsg,0,256);
		sprintf(errmsg,"SockSrv IP[%s]连接错误,包头错误",conn.IP);
//		sprintf(errmsg,"client socket identify packet head error");
		closesocket(conn.recvsock);
		goto err1;
	}
	
	//code越界
	if(iden.CltCode<1||iden.CltCode>=MAX_CONN)
	{
		memset(errmsg,0,256);
		sprintf(errmsg,"SockSrv IP[%s]连接错误,节点编码%d越界[0-%d]",conn.IP,iden.CltCode,MAX_CONN);
		closesocket(conn.recvsock);
		goto err1;
	}

	//code连接已经存在
	if(gConn[iden.CltCode].recvsock!=NULL&&gConn[iden.CltCode].sendsock!=NULL)
	{
		memset(errmsg,0,256);
		sprintf(errmsg,"SockSrv IP[%s]连接错误,节点%d已经存在",conn.IP,iden.CltCode);
		closesocket(conn.recvsock);
		goto err1;
	}

	//ok,启动数据接收
	if(iden.SockType==SOCK_SEND)//对方是发送，本端接收
		gConn[iden.CltCode].recvsock=conn.recvsock;
	else if(iden.SockType==SOCK_RECV)
	{
		DBGMsg("sock %s[%d] code[%d]send sock connected",conn.IP,conn.recvsock,code);
		gConn[iden.CltCode].sendsock=conn.recvsock;
		return;
	}
	else
	{
		//错误sock类型
		memset(errmsg,0,256);
		sprintf(errmsg,"SockSrv IP[%s]连接错误,错误的Sock类型",conn.IP);
//		sprintf(errmsg,"client socket err type %d",iden.SockType);
		closesocket(conn.recvsock);
		goto err1;
	}

	//启动数据接收循环
	Sleep(500);
	code=iden.CltCode;
	DBGMsg("sock %s[%d] code[%d]recv data loop start",conn.IP,conn.recvsock,code);
	gConn[i].KeepAliveTimer=MAX_IDLE_TIME;
	while(true)
	{
		recved=recv(conn.recvsock,(char*)(&nrpak),sizeof(rpak),0);
		DBGMsg("socksrv recved %d pak",gPakSize);
		rpak.brdno=ntohl(nrpak.brdno);
		rpak.chno=ntohl(nrpak.chno);
		rpak.cmdtype=ntohl(nrpak.cmdtype);
		rpak.node=ntohl(nrpak.node);

		DBGMsg("sock src recv  %d,%d,%d,%d byte",rpak.brdno,rpak.chno,rpak.cmdtype,rpak.node);
		
		if(recved==SOCKET_ERROR||recved==0)
		{
			memset(errmsg,0,256);
			sprintf(errmsg,"SockSrv IP[%s]节点[%d]接收错误",conn.IP,code);
			goto err;
		}
		//确保接收到一个完整的包
		while(recved<gPakSize)
		{
			int rt;
			rt=recv(conn.recvsock,(char*)(&rpak)+recved,sizeof(rpak)-recved,0);
			if(rt==SOCKET_ERROR)
			{
				memset(errmsg,0,256);
				sprintf(errmsg,"SockSrv IP[%s]节点[%d]接收端口断开连接",conn.IP,code);
				goto err;
			}
			recved=recved+rt;
			Sleep(10);
		}

		//全零的KeepAlive数据不加入队列
//		if(memcmp(recvbuf,ZeroBuf,gPakSize)==0)
//		{
//			DBGMsg("recv code[%d] alive pak",code);
//			gConn[i].KeepAliveTimer=MAX_IDLE_TIME;
//		}else
		if(!gRecvBuf.AddTail(rpak))//recvbuf,iden.CltCode)==-1)
		{
			if(gSysMsg!=NULL)
				gSysMsg(MSG_RECV_BUF_FULL,"SockSrv 接收数据缓冲溢出");
			gRecvBuf.RemoveAll();
			gRecvBuf.AddTail(rpak);//recvbuf,iden.CltCode);
		}
		gConn[code].KeepAliveTimer=MAX_IDLE_TIME;
		Sleep(10);
	}
	return;
err:
	if(code!=-1)
	{
		if(gConn[code].recvsock!=0)
		{
			closesocket(gConn[code].recvsock);
			gConn[code].recvsock=0;
		}
		if(gConn[code].sendsock!=0)
		{
			closesocket(gConn[code].sendsock);
			gConn[code].sendsock=0;
		}
	}
err1:
	if(gSysMsg!=NULL)
		gSysMsg(MSG_CLT_DISCONNECT,errmsg);
	DBGMsg("sock %s[%d] quit,errmsg %s",conn.IP,conn.recvsock,errmsg);
	return;
}

void Thread_SendData(LPVOID param)
{
	char pak[MAX_PAKSIZE];
	RemInPak spak;
	gThread_SendData=true;
	while(gThread_SendData)
	{
		//发送缓冲区中数据
		if(!gSendBuf.IsEmpty())//GetCount()>0)
		{
			gSendBuf.RemoveHead(spak);
			WORD code=spak.node;
//			memcpy(&code,pak,2);
			if(code>=0&&code<MAX_CONN)
			if(gConn[code].sendsock!=NULL)
			{
				int sended;
				sended=send(gConn[code].sendsock,(char*)(&spak),sizeof(spak),0);//pak+2,gPakSize,0);
				if(sended==SOCKET_ERROR)
				{
					closesocket(gConn[code].sendsock);
					gConn[code].sendsock=0;
					if(gConn[code].recvsock!=0)
					{
						closesocket(gConn[code].recvsock);
						gConn[code].recvsock=0;
					}
				}
				while(sended<gPakSize)
				{
					int st;
					st=send(gConn[code].sendsock,pak+2+sended,gPakSize-sended,0);
					if(st==SOCKET_ERROR)
					{
						closesocket(gConn[code].sendsock);
						gConn[code].sendsock=0;
						if(gConn[code].recvsock!=0)
						{
							closesocket(gConn[code].recvsock);
							gConn[code].recvsock=0;
						}
						break;
					}
					sended=sended+st;
				}
				DBGMsg("send pak to code[%d]",code);
				gConn[code].KeepAliveTimer=MAX_IDLE_TIME;
			}
		}
		Sleep(10);
	}
}

void Thread_MsgNotify(LPVOID param)
{
//	char pak[MAX_PAKSIZE];
	RemInPak rpak;
	gThread_MsgNotify_Run=true;
	while(gThread_MsgNotify_Run)
	{
		if(!gRecvBuf.IsEmpty())//GetCount()>0)
		{
			gRecvBuf.RemoveHead(rpak);
			WORD code=rpak.node;
//			memcpy(&code,pak,2);
			if(gFuncRecvPak)
				gFuncRecvPak(code,(char*)(&rpak));
		}
		Sleep(10);
	}
}

