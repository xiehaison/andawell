///////////////////////////////////////////////////////////////
//  commͨѶ�м���ӿ�(C++Builder)
//  ���:����
//  ʱ��:2003��4��9��
///////////////////////////////////////////////////////////////
#include <windows.h>
#include "..\\include\\commpack.h"
#include "..\\include\\basedef.h"
#ifndef _COMM_H_
#define _COMM_H_


//Dll�¼�����
typedef void (*OnRecvCmd)(const TcpPacket* packet);
typedef void (*OnConnStatus)(int socktype,int status);

//loadͨѶ����
typedef int (WINAPI *pLoadConfig)(const char*);
extern pLoadConfig LoadConfig;

//����ͨѶ����
typedef int  (WINAPI *pConnectCenter)();
extern pConnectCenter ConnectCenter;

//�������ݰ�
typedef void (WINAPI *pSendPacket)(TcpPacket* packet);
extern pSendPacket SendPacket;


//hook����״̬����
typedef void (WINAPI *pHookConnStatus)(OnConnStatus func);
extern pHookConnStatus HookConnStatus;


typedef void (WINAPI *pHookRecvCmd)(OnRecvCmd func);
extern pHookRecvCmd HookRecvCmd;


bool LoadDll(const char* dllname);
#endif

