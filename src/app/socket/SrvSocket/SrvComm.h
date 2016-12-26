
#ifndef __SRVCOMM_H__
#define __SRVCOMM_H__
#pragma once
#pragma pack(1)


#define MAX_NODE 10000

struct T_MsgServer{
    DWORD     node;
    WORD     len;
    char    msg[256];
};


struct T_MsgNotifyServer{
    int node;
    int notify;
    char msg[256];
};


typedef DWORD (*OnMsg)(int node, char *msg, int len);
typedef DWORD (*OnNotify)(int node, int notify,char *msg);

int CloseAll();

int StartSrv(int port, int max_user);
int SetHook(OnMsg msg, OnNotify notify);
int SendPacket(int node, char *pack, WORD len);

#pragma pack()

#endif //__SRVCOMM_H__

