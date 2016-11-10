#include "..\\include\\ctidef.h"
#include "..\\include\\commpack.h"

#ifndef _commsdk_h_
#define _commsdk_h_
//--------------------����Է��ڵ��Ŀ¼�ṹ����-----------------------------
#define DIROP_CMD_SENDED 0
#define DIROP_DIR_RECVED 1
typedef struct{
	FILETIME ftLastWriteTime;
	char FileName[128];
	DWORD FileSizeLow;
	DWORD FileSizeHigh;
	DWORD Attributes;
}FD_DATA;
//--------------------�¼�����------------------------
//�¼�֪ͨ����
//����״̬֪ͨ����
//socktype:0-����sock;1-��sock
//status:0-�ɹ�;1-�������;2-�ڵ��Ų�����;3-�ڵ����Ѿ���ʹ��;4-������ʧ;5-����ʧ��
typedef void(*OnConnStatus)(int socktype,int status);

//������ݵĴ��͹���֪ͨ�ʹ��ͽ��֪ͨ
typedef void (*OnNotify)(int msg,int para,char* hint);

//���նԷ�ͨѶ�ڵ��Ŀ¼��Ϣ��֪ͨ����
typedef void (*OnRecvDir)(int code,const FD_DATA* data,bool root,char* drvinfo);

//��ivr���Ľ���ͨ��״̬��Ϣ��֪ͨ����
typedef void (*OnRecvChanInfo)(int code,const YTChan* chinfo);

//��ivr���Ľ��ջ���״̬��Ϣ�ĺ���
typedef void(*OnRecvMeetInfo)(int code,const TcpPacket* packet);

//���յ�����ͨѶ�ڵ��ָ��
typedef void(*OnRecvCmd)(const TcpPacket* packet);

//���յ�ivr���ݺ���
typedef void(*OnRecvIvrData)(const TcpPacket* packet);

//loadͨѶ����
int WINAPI LoadConfig(LPCTSTR filename);

//����ͨѶ����
void WINAPI ConnectCenter();

//�õ�������
int WINAPI GetConnectResult();

//����һ���ļ�
//sfile-Դ�ļ�;dfile-Ŀ���ļ�
void WINAPI RecvFile(int descode,char* sfile,char* dfile);

//����һ���ļ�
//����������
//����ֵ:0-��ʼ����;1-����ʧ��
int WINAPI SendFile(int DesCode,LPCTSTR filename);

//��ѯ�����ļ�״̬
//void WINAPI GetFileTransferStatus(int& recved,int& res,float& speed,float& ratio);

//������Ϣ
void WINAPI SendPacket(TcpPacket* packet);

//����ivr���ݽ�����Ϣ��Ӧ����
void WINAPI HookRecvIvrData(OnRecvIvrData func);

//��������״̬��Ϣ��Ӧ����
void WINAPI HookConnStatus(OnConnStatus func);

//���ý���������Ϣ��Ӧ����
void WINAPI HookRecvCmd(OnRecvCmd func);

//���û�����Ϣ������Ӧ����
void WINAPI HookRecvMeetInfo(OnRecvMeetInfo func);

//����ͨ��״̬��Ϣ��Ӧ����
void WINAPI HookRecvChanInfo(OnRecvChanInfo func);

//������Ϣ���պ���
void WINAPI HookNotiyFunc(OnNotify func);

//���ý��նԷ�Ŀ¼��Ϣ�Ľ��պ���
void WINAPI HookRecvDirInfo(OnRecvDir func);


#endif