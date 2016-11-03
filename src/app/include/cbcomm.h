///////////////////////////////////////////////////////////////
//  comm通讯中间件接口(C++Builder)
//  编程:余涛
//  时间:2003年4月9日
///////////////////////////////////////////////////////////////
#include <windows.h>
#include "..\\include\\commpack.h"
#include "..\\include\\basedef.h"
#ifndef _COMM_H_
#define _COMM_H_


//Dll事件函数
typedef void (*OnRecvCmd)(const TcpPacket* packet);
typedef void (*OnConnStatus)(int socktype,int status);

//load通讯配置
typedef int (WINAPI *pLoadConfig)(const char*);
extern pLoadConfig LoadConfig;

//连结通讯中心
typedef int  (WINAPI *pConnectCenter)();
extern pConnectCenter ConnectCenter;

//发送数据包
typedef void (WINAPI *pSendPacket)(TcpPacket* packet);
extern pSendPacket SendPacket;


//hook连接状态函数
typedef void (WINAPI *pHookConnStatus)(OnConnStatus func);
extern pHookConnStatus HookConnStatus;


typedef void (WINAPI *pHookRecvCmd)(OnRecvCmd func);
extern pHookRecvCmd HookRecvCmd;


bool LoadDll(const char* dllname);
#endif

