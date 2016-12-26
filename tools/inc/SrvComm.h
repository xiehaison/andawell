
#ifndef __SRVCOMM_H__
#define __SRVCOMM_H__
#pragma once
#pragma pack(1)


#define MAX_NODE 10000

struct T_MsgServer{
    int node;
    char *msg;
    int len;
};


struct T_MsgNotifyServer{
    int node;
    int notify;
};


typedef void (* OnMsg)(int node,char *msg,int len);
typedef void (* OnNotify)(int node,int notify);

int CloseAll();

int StartSrv(int port,int max_user);
int SetHook(OnMsg msg,OnNotify notify);
int SendPacket(int node,char *pack,int len);
int SendPacket1(int node,char *pack,int len);

#pragma pack()

#endif //__SRVCOMM_H__

