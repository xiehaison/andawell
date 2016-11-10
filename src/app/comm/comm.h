// comm.h : main header file for the COMM DLL
//
#include "..\\include\\commpack.h"
#include "..\\include\\ctidef.h"
#include "commsdk.h"
#include <sys/timeb.h>
#include "inifile.h"
#include "..\\utillib\\buf.h"
#include "..\\utillib\\crc32static.h"

#if !defined(AFX_COMM_H__C20D2CDC_7B5D_46D2_97F9_9F8F7A439E97__INCLUDED_)
#define AFX_COMM_H__C20D2CDC_7B5D_46D2_97F9_9F8F7A439E97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCommApp
// See comm.cpp for the implementation of this class
//

class CCommApp : public CWinApp
{
public:
	CCommApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCommApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//Comm

//--------------------函数声明------------------------
bool InitClientSock();
bool InitStreamSock();
bool ConnectRemote(LPCTSTR RemoteIP,int RemotePort);
void PutPacketIntoSendBuf(TcpPacket* packet);

void Thread_MsgNotify(LPVOID param);
void Thread_TCPSend(LPVOID param);
void Thread_TCPClient(LPVOID param);
void Thread_Connect(LPVOID param);
void Thread_SendAlive(LPVOID param);
//void Thread_SendFile(LPVOID param);
//void Thread_TCPStreamRecv(LPVOID param);
//void Thread_RecvDirInfoNotify(LPVOID param);


#define CONN_OK              0//成功
#define CONN_PASSWORD_ERROR  1//密码错误
#define CONN_CODE_NOT_SET    2//节点编号不存在
#define CONN_CODE_LOGINED    3//节点编号已经被使用
#define CONN_DISCONNECT      4//连结断开

#define ERR_SENDBUF_OVERFLOW     1//发送命令缓冲区溢出
#define ERR_STREAM_BUF_OVERFLOW  2//流缓冲区溢出

//发送文件的状态
//SendFileInfo.Res
#define SF_OK            0//成功
#define SF_OPENFILE_FAIL 1//指定文件无法打开
#define SF_NETWORK_FAIL  2//网络连接失败
#define SF_SENDDING      3//发送中
#define SF_NOTONLINE     4//对方没有响应
#define SF_FORCESTOP     5//强制中断
#define SF_CRC_ERROR     6//CRC校验码错误
#define SF_PEER_BUSY     7//对方正在接收其他发送方发送的文件

typedef struct{
	int  DesCode;//对方的节点编号
	bool DesReady;//对方是否发送准备好的消息
	int  FileLen;//文件长度
	int  FileSendBytes;//已经发送文件的字节数
	int  LastFileSendBytesAck;//上一次对方确认的发送字节数量
	int  FileSendBytesAck;//对方确认接收的字节数
	char FileName[512];//发送文件名称
	HANDLE filehnd;//打开文件的句柄
	int  Res;//发送文件的状态
	DWORD t_lastrecv;//上一次确认包的接收时间
	DWORD t_recv;//当前接收确认包的接收时间
}SendFileInfo;


//-----------------------------接收流--------------------------------------
#define RECV_FILE      0   //准备接收文件
#define RECV_DIRLIST   1   //准备接收目录列表


//RecvStreamInfo.tpye
#define RFT_FILE 0
#define	RFT_MEM  1

typedef struct{
//	int  type;//0-接收到文件中,1-接收到内存中
	bool OnWork;//当前是否在工作
	int  SendCode;//Stream数据发送端编号
	char recvfilename[512];//接收的文件名称
	HANDLE recvfilehnd;//接收的文件句柄
	int needrecvlen;//接收到文件或流的长度
	char recvbuf[1024*1024];//接收的缓冲区大小
	int  recvlen;//已经接收的长度
	DWORD Crc32;//发送端传送发送的文件crc校验码
	DWORD t_start;//开始接收的时间
	DWORD t_lastrecv;//最近接收到数据的时间
}RecvStreamInfo;

/*

typedef struct
{
	int code;
	//对方节点的drv信息
	File_DrvInfo Drv;
	//对方节点的当前目录
	char curdir[512];
	//文件和目录
	list<FD_DATA> FileList;
}DrvFileInfo;
*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMM_H__C20D2CDC_7B5D_46D2_97F9_9F8F7A439E97__INCLUDED_)
