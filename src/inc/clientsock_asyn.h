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
    DWORD node;          //ͨ�Žڵ��
    DWORD dir;           //���ͻ��߽���
    DWORD  notify;         //���С��0�����ӵĴ�����Ϣ,,����0�ǳɹ���,999�Ƿ������ӳɹ�,998�ǽ������ӳɹ�,
    BYTE msg[256];      //�����������socket���ӹ����в����Ĵ�����߳ɹ�����Ϣ,���ڹ۲��������

}T_MsgNotify;


/*
�����ͻ���
rip:ip��ַ ����192.168.10.11
rport:�˿ں�  ����:1232
note:�ڵ��� ��:10
*/
DWORD WINAPI  StartClient(const char *rip, DWORD rport, DWORD note);

/*
�������ݰ�
pack:���͵�����ָ��
len:Ҫ���͵��������Ĵ�С
*/
int SendPacket(const char *pack, DWORD len);
/*
��������
buf:���͵�������
len:���͵�����������
*/
void WINAPI  TcpSockSend(void *buf, DWORD  len);
//�̰߳�ȫ

/*
��ȡ�յ�����Ϣ
����յ�û����Ϣ,���ؿ�,NULL
����յ���Ϣ,������Ϣ�ṹ��
*/
  T_Msg * WINAPI  GetRecvMsg();


/*
��ȡ֪ͨ��Ϣ
���û����Ϣ,���ؿ�,NULL
����յ���Ϣ����ͬ־��Ϣ�Ľṹ��
*/
  T_MsgNotify * WINAPI  GetNotify();
/*
�ر���������
*/
  int WINAPI  CloseAll();

#endif//__CLIENTSOCK_H__

