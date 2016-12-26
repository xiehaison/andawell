#ifndef _cltintf_h_
#define _cltintf_h_

#ifdef SOCKCLT_EXPORTS
#define SOCKCLT_API __declspec(dllexport)
#else
#define SOCKCLT_API __declspec(dllimport)
#endif
enum{
	MSG_CLT_DISCONNECT,
	MSG_CLT_SEND_CONNECT,
	MSG_CLT_RECV_CONNECT,
	MSG_CLT_BUF_OVERFLOW
};

typedef void (*Func_CltRecvPak)(const char* buf);
typedef void (*Func_CltSysMsg)(int status);


SOCKCLT_API void SetPara(const char* cenip,int cenport,int mycode,int paksize);
SOCKCLT_API bool StartUpClt();
SOCKCLT_API void ConnectCenter();
SOCKCLT_API void HookCltRecvPak(Func_CltRecvPak funcaddr);
SOCKCLT_API void HookCltSysMsg(Func_CltSysMsg funcaddr);
SOCKCLT_API void SendPacket(const char* buf);

#endif