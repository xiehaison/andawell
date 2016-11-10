#include "..\\include\\ctidef.h"
#include "..\\include\\commpack.h"

#ifndef _commsdk_h_
#define _commsdk_h_
//--------------------浏览对方节点的目录结构数据-----------------------------
#define DIROP_CMD_SENDED 0
#define DIROP_DIR_RECVED 1
typedef struct{
	FILETIME ftLastWriteTime;
	char FileName[128];
	DWORD FileSizeLow;
	DWORD FileSizeHigh;
	DWORD Attributes;
}FD_DATA;
//--------------------事件函数------------------------
//事件通知函数
//连结状态通知汉数
//socktype:0-命令sock;1-流sock
//status:0-成功;1-密码错误;2-节点编号不存在;3-节点编号已经被使用;4-心跳丢失;5-连接失败
typedef void(*OnConnStatus)(int socktype,int status);

//大块数据的传送过程通知和传送结果通知
typedef void (*OnNotify)(int msg,int para,char* hint);

//接收对方通讯节点的目录信息的通知函数
typedef void (*OnRecvDir)(int code,const FD_DATA* data,bool root,char* drvinfo);

//从ivr核心接收通道状态信息的通知函数
typedef void (*OnRecvChanInfo)(int code,const YTChan* chinfo);

//从ivr核心接收会议状态信息的函数
typedef void(*OnRecvMeetInfo)(int code,const TcpPacket* packet);

//接收到其他通讯节点的指令
typedef void(*OnRecvCmd)(const TcpPacket* packet);

//接收到ivr数据函数
typedef void(*OnRecvIvrData)(const TcpPacket* packet);

//load通讯配置
int WINAPI LoadConfig(LPCTSTR filename);

//连结通讯中心
void WINAPI ConnectCenter();

//得到连结结果
int WINAPI GetConnectResult();

//接收一个文件
//sfile-源文件;dfile-目的文件
void WINAPI RecvFile(int descode,char* sfile,char* dfile);

//发送一个文件
//发送任务编号
//返回值:0-开始发送;1-连结失败
int WINAPI SendFile(int DesCode,LPCTSTR filename);

//查询发送文件状态
//void WINAPI GetFileTransferStatus(int& recved,int& res,float& speed,float& ratio);

//发送消息
void WINAPI SendPacket(TcpPacket* packet);

//设置ivr数据接收消息响应函数
void WINAPI HookRecvIvrData(OnRecvIvrData func);

//设置连结状态消息响应函数
void WINAPI HookConnStatus(OnConnStatus func);

//设置接收命令消息响应函数
void WINAPI HookRecvCmd(OnRecvCmd func);

//设置会议消息接收响应函数
void WINAPI HookRecvMeetInfo(OnRecvMeetInfo func);

//设置通道状态消息响应函数
void WINAPI HookRecvChanInfo(OnRecvChanInfo func);

//设置消息接收函数
void WINAPI HookNotiyFunc(OnNotify func);

//设置接收对方目录消息的接收函数
void WINAPI HookRecvDirInfo(OnRecvDir func);


#endif