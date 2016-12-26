#ifndef __CLIENTSOCK_H__
#define __CLIENTSOCK_H__


#define E_SEND_OK               999
#define E_RECV_OK               998
#define E_ERROR_REG             -1
#define E_ERROR_SEND            -2
#define E_ERROR_CLOSE           -3
#define E_ERROR_Timeout         -4
#define E_ERROR_Socket          -5
#define E_ERROR_ACK             -6
#define E_ERROR_PACKLEN         -7
#define E_ERROR_Server_Reject   -8
#define E_ERROR_Connect         -9
#define E_ERROR_Create          -10



typedef struct {
    BYTE msg[2048];
    DWORD len;
}T_Msg; 


typedef struct {
    DWORD node;          //通信节点号
    DWORD dir;           //发送或者接收
    DWORD  notify;         //如果小于0是连接的错误消息,,大于0是成功的,999是发送连接成功,998是接收连接成功,
    BYTE msg[256];      //这个部分是在socket连接过程中产生的错误或者成功的消息,便于观察错误类型

}T_MsgNotify;


/*
启动客户端
rip:ip地址 例如192.168.10.11
rport:端口号  例如:1232
note:节点编号 如:10
*/
DWORD WINAPI  StartClient(const char *rip, DWORD rport, DWORD note);

/*
发送数据包
pack:发送的数据指针
len:要发送的数据区的大小
*/
int SendPacket(const char *pack, DWORD len);
/*
发送数据
buf:发送的数据区
len:发送的数据区长度
*/
void WINAPI  TcpSockSend(void *buf, DWORD  len);
//线程安全

/*
获取收到的消息
如果收到没有消息,返回空,NULL
如果收到消息,返回消息结构体
*/
  T_Msg * WINAPI  GetRecvMsg();


/*
获取通知消息
如果没有消息,返回空,NULL
如果收到消息返回同志消息的结构体
*/
  T_MsgNotify * WINAPI  GetNotify();
/*
关闭所有连接
*/
  int WINAPI  CloseAll();

#endif//__CLIENTSOCK_H__

