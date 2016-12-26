#ifndef _srvintf_h_
#define _srvintf_h_

#ifdef SOCKSRV_EXPORTS
#define SOCKSRV_API __declspec(dllexport)
#else
#define SOCKSRV_API __declspec(dllimport)
#endif

enum{
	    MSG_ERROR,            //系统发生故障,需重新启动
		MSG_CLT_CONNECT,      //客户端SOCK连接上来消息
		MSG_CLT_DISCONNECT,   //客户端SOCK断开连接消息
		MSG_RECV_BUF_FULL,    //客户端SOCK接收缓冲区溢出消息
		MSG_SEND_BUF_FULL     //服务端SOCK发送缓冲区溢出消息
};

typedef void (*Func_SrvRecvPak)(int code,const char* buf);
typedef void (*Func_SysMsg)(int status,const char* msg);


SOCKSRV_API bool StartUpSrv(int srvport,int paksize);

SOCKSRV_API void SendPak(WORD code,const char* buf,int size);

SOCKSRV_API void HookRecvPakFunc(Func_SrvRecvPak funcaddr);

SOCKSRV_API void HookSysMsgFunc(Func_SysMsg funcaddr);

SOCKSRV_API void ClearUp();

#endif