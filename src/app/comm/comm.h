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

//--------------------��������------------------------
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


#define CONN_OK              0//�ɹ�
#define CONN_PASSWORD_ERROR  1//�������
#define CONN_CODE_NOT_SET    2//�ڵ��Ų�����
#define CONN_CODE_LOGINED    3//�ڵ����Ѿ���ʹ��
#define CONN_DISCONNECT      4//����Ͽ�

#define ERR_SENDBUF_OVERFLOW     1//��������������
#define ERR_STREAM_BUF_OVERFLOW  2//�����������

//�����ļ���״̬
//SendFileInfo.Res
#define SF_OK            0//�ɹ�
#define SF_OPENFILE_FAIL 1//ָ���ļ��޷���
#define SF_NETWORK_FAIL  2//��������ʧ��
#define SF_SENDDING      3//������
#define SF_NOTONLINE     4//�Է�û����Ӧ
#define SF_FORCESTOP     5//ǿ���ж�
#define SF_CRC_ERROR     6//CRCУ�������
#define SF_PEER_BUSY     7//�Է����ڽ����������ͷ����͵��ļ�

typedef struct{
	int  DesCode;//�Է��Ľڵ���
	bool DesReady;//�Է��Ƿ���׼���õ���Ϣ
	int  FileLen;//�ļ�����
	int  FileSendBytes;//�Ѿ������ļ����ֽ���
	int  LastFileSendBytesAck;//��һ�ζԷ�ȷ�ϵķ����ֽ�����
	int  FileSendBytesAck;//�Է�ȷ�Ͻ��յ��ֽ���
	char FileName[512];//�����ļ�����
	HANDLE filehnd;//���ļ��ľ��
	int  Res;//�����ļ���״̬
	DWORD t_lastrecv;//��һ��ȷ�ϰ��Ľ���ʱ��
	DWORD t_recv;//��ǰ����ȷ�ϰ��Ľ���ʱ��
}SendFileInfo;


//-----------------------------������--------------------------------------
#define RECV_FILE      0   //׼�������ļ�
#define RECV_DIRLIST   1   //׼������Ŀ¼�б�


//RecvStreamInfo.tpye
#define RFT_FILE 0
#define	RFT_MEM  1

typedef struct{
//	int  type;//0-���յ��ļ���,1-���յ��ڴ���
	bool OnWork;//��ǰ�Ƿ��ڹ���
	int  SendCode;//Stream���ݷ��Ͷ˱��
	char recvfilename[512];//���յ��ļ�����
	HANDLE recvfilehnd;//���յ��ļ����
	int needrecvlen;//���յ��ļ������ĳ���
	char recvbuf[1024*1024];//���յĻ�������С
	int  recvlen;//�Ѿ����յĳ���
	DWORD Crc32;//���Ͷ˴��ͷ��͵��ļ�crcУ����
	DWORD t_start;//��ʼ���յ�ʱ��
	DWORD t_lastrecv;//������յ����ݵ�ʱ��
}RecvStreamInfo;

/*

typedef struct
{
	int code;
	//�Է��ڵ��drv��Ϣ
	File_DrvInfo Drv;
	//�Է��ڵ�ĵ�ǰĿ¼
	char curdir[512];
	//�ļ���Ŀ¼
	list<FD_DATA> FileList;
}DrvFileInfo;
*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMM_H__C20D2CDC_7B5D_46D2_97F9_9F8F7A439E97__INCLUDED_)
