#ifndef __CLIENTSOCK_H__
#define __CLIENTSOCK_H__

typedef void (* OnMsg)(char *msg,int len);
typedef void (* OnNotify)(char *msg,int code);

int StartClient(const char *rip,int rport,int note);

int SetHook(OnMsg msg,OnNotify notify);

int SendPacket(const char *pack,short int len);
int SendPacket1(const char *pack,short int len);
int CloseAll();

#endif//__CLIENTSOCK_H__