#ifndef _srvintf_h_
#define _srvintf_h_

#ifdef SOCKSRV_EXPORTS
#define SOCKSRV_API __declspec(dllexport)
#else
#define SOCKSRV_API __declspec(dllimport)
#endif

enum{
	    MSG_ERROR,            //ϵͳ��������,����������
		MSG_CLT_CONNECT,      //�ͻ���SOCK����������Ϣ
		MSG_CLT_DISCONNECT,   //�ͻ���SOCK�Ͽ�������Ϣ
		MSG_RECV_BUF_FULL,    //�ͻ���SOCK���ջ����������Ϣ
		MSG_SEND_BUF_FULL     //�����SOCK���ͻ����������Ϣ
};

typedef void (*Func_SrvRecvPak)(int code,const char* buf);
typedef void (*Func_SysMsg)(int status,const char* msg);


SOCKSRV_API bool StartUpSrv(int srvport,int paksize);

SOCKSRV_API void SendPak(WORD code,const char* buf,int size);

SOCKSRV_API void HookRecvPakFunc(Func_SrvRecvPak funcaddr);

SOCKSRV_API void HookSysMsgFunc(Func_SysMsg funcaddr);

SOCKSRV_API void ClearUp();

#endif