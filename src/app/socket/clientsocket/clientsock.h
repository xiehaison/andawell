#ifndef __CLIENTSOCK_H__
#define __CLIENTSOCK_H__


#define E_SEND_OK       999
#define E_RECV_OK       998
#define E_ERROR_REG     -1
#define E_ERROR_SEND    -2
#define E_ERROR_CLOSE   -3


//typedef struct {
//    BYTE *msg;
//    DWORD len;
//    void T_Msg()
//    {
//        len = 0;
//    }
//}T_Msg;


typedef struct {
    DWORD node;
    DWORD dir;
    DWORD notify;
    BYTE msg[256];
    void T_MsgNotify()
    {
        dir = 0;
        node = 0;
        notify = 0;
        memset(msg,0,256);
    }
}T_MsgNotify;




typedef void (* OnMsg)(char *msg,int len);
typedef void (* OnNotify)(char *msg,int code);

DWORD StartClient(const char *rip,int rport,int note);
int SetHook(OnMsg msg,OnNotify notify);

int SendPacket(const char *pack,WORD len);


int CloseAll();

#endif//__CLIENTSOCK_H__

