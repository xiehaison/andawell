#pragma once
#ifndef _SOCKET_H_
#define _SOCKET_H_

#pragma pack(1)


#ifndef MAX
#define MAX(a,b) (((a)>(b)) ? (a):(b))
#endif

#define ERR_SOCKETREAD	-1000
#define ERR_SOCKETWRITE	-1001
#define CONN_TIMEOUT 10
#define HEART_TIMEOUT  1

#ifndef WIN32
#define SD_RECEIVE      0x00
#define SD_SEND         0x01
#define SD_BOTH         0x02
#endif

#define MAX_MSG_LEN  1500


#define  MAX_RECV_BUF_LEN 1500

int CloseSocket(int fd);
int initsock();
int SockRead(int fd, void *buf, int n, int msec);
int SockReadAll(int fFD, int sFD,void *buf,int n, int sec);
void closeall();

int WriteData(int fd, const void *buf, int n);

int Connect(const char *rip, int rport);

//recv&send data
int SendData(const char* rip, int rport, const void* buf, int buflen,bool bDisconnect =1);
int SendAllData(const char* rip, int rport, const void* buf, int buflen, const void * attach=NULL,int attachlen=0,bool bDisConnect=1);
int start_conn_thread();

void *comm_connect_thread(void *param);

typedef void (*on_notify)(int status) ;
typedef void (*on_recv)(char *msg,int len) ;

int SendPack(char *buf,int n);

void sethook(on_notify notify,on_recv recv);
#pragma pack()

#endif

