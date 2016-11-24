#ifndef __CLIENTSOCK_H__
#define __CLIENTSOCK_H__


#define E_SEND_OK       999
#define E_RECV_OK       998
#define E_ERROR_REG     -1
#define E_ERROR_SEND    -2
#define E_ERROR_CLOSE   -3


typedef struct {
    char *msg;
    int len;
}T_Msg;


typedef struct {
    char msg[255];
    int node;
    int dir;
    int notify;
}T_MsgNotify;


//
//typedef void (* OnMsg)(char *msg,int len);
//typedef void (* OnNotify)(char *msg,int code);

DWORD StartClient(const char *rip,int rport,int note);
//int SetHook(OnMsg msg,OnNotify notify);

int SendPacket(const char *pack,short int len);
//int SendPacket1(const char *pack, short int len); 
void TcpSockSend(void *buf, int len);

bool GetRecvMsg(BYTE *buf, WORD len);
bool GetRecv(BYTE *buf, WORD len);
int CloseAll();

#endif//__CLIENTSOCK_H__

