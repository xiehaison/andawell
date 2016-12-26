
#ifndef __SRVCOMM_H__
#define __SRVCOMM_H__
#pragma once
#pragma pack(1)

typedef void (* OnMsg)(int node,char *msg,int len);
typedef void (* OnNotify)(int node,int notify);

int CloseAll();

int StartSrv(int port,int max_user);
int SetHook(OnMsg msg,OnNotify notify);
int SendPacket(int node,char *pack,int len);
int SendPacket1(int node,char *pack,int len);

#pragma pack()

#endif //__SRVCOMM_H__

