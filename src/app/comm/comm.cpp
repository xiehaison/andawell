// comm.cpp : Defines the initialization routines for the DLL.
//
#include "stdafx.h"
#include "comm.h"
#include "commsdk.h"
#include "..\\include\\queue.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

//����Ŀ¼���
bool gRecvDirEnd=true;

BEGIN_MESSAGE_MAP(CCommApp, CWinApp)
	//{{AFX_MSG_MAP(CCommApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommApp construction

CCommApp::CCommApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCommApp object

CCommApp theApp;

//ϵͳ����Ϣ���� 
//list<TcpPacket> gMsgList;
CMyFifo<TcpPacket> gMsgList;
HANDLE ghMsgLock;

CRITICAL_SECTION gMsgLock;//��Ϣ�ٽ���

//-----------------------ȫ�ֱ���---------------------------
OnNotify Notify=NULL;//�¼�֪ͨ
OnRecvDir RecvDir=NULL;//���յ�Ŀ¼��Ϣ֪ͨ
OnRecvChanInfo RecvChanInfo=NULL;//���յ�ͨ����Ϣ
OnRecvMeetInfo RecvMeetInfo=NULL;//���յ�������Ϣ
OnRecvCmd  RecvCmd=NULL;//���յ�����
OnConnStatus ConnStatus=NULL;//����״̬����
OnRecvIvrData RecvIvrData=NULL;

SOCKET	gCltSockRecv=NULL;//���ݽ���socket                   
SOCKET  gCltSockSend=NULL;//���ݷ��Ͷ˿�
SOCKET  gStreamSock=NULL;//��socket

//�߳����п��ƿ���
bool gThread_RecvDirInfoNotify=true;
bool gThread_MsgNotify=true;
bool gThread_TCPSend=true;
bool gThread_TCPStreamRecv=true;
bool gThread_TCPClient=true;
bool gThread_SendAlive=true;
//bool gThread_SendFile=false;
bool gThread_Connect=false;

//ͨѶ���ò���
CString gCommCentIP;
int gCommCentPort;
int	gLocalCode;
int gLocalType;

CString	gLocalPass;

int gTimer=TIME_ALIVE;//�����ı�������Ķ�ʱ��

int gConnStatus=CONN_DISCONNECT;//�����������״̬,

int gSysErr;                      //ϵͳ�Ĵ���

CMyFifo<TcpPacket> gSendBuf;

CRITICAL_SECTION SBLock;//�������ݻ����ٽ���

SendFileInfo gSendFile;//�����ļ�״̬��Ϣ

int gReadyToRecv;//��ǰ���ڵ�׼������ʲô

RecvStreamInfo gRecvStream;//�����ļ���״̬��Ϣ

//DrvFileInfo gDrvFile;//����Է��ڵ��Ŀ¼�ṹ����



/////////////////////////////////////////////////////////////////////////////
// CCommApp initialization
//�оٻ������߼�����Ŀ¼
/*
void GetLogicDrvInfo(File_DrvInfo& drvinfo)
{
	drvinfo.DrvCnt=GetLogicalDrives();
	memset(drvinfo.DrvName,0,200);
	GetLogicalDriveStrings(200,drvinfo.DrvName);
}
*/
void dbgmsg(LPCTSTR DbgMessage,...)
{
#ifdef _DEBUG
	char buf[1024];
	memset(buf,0,1024);

	va_list args;
	va_start(args, DbgMessage);
	_vsnprintf (buf, sizeof(buf), DbgMessage, args);
    va_end(args);

	strcat(buf, "\n");
	char str[512];
	memset(str, 0, sizeof(str));
	strcat(str, buf);
	
	struct _timeb tstruct;
	_ftime( &tstruct );

	CTime t=CTime::GetCurrentTime();
	CString line;
	line.Format("%s(%3u)=>%s",t.Format("%H:%M:%S"),tstruct.millitm,str);
	OutputDebugString(line);
#endif
}

//����now��then��ʱ���(����),���ǵ�����������
DWORD TimeSpan(DWORD now, DWORD then)
{
	if (then>=now)
		return (then-now);
	else
	{
		return ((0xFFFFFFFF-now)+then);
	}
}

BOOL CCommApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	InitializeCriticalSection(&SBLock);

	ghMsgLock=CreateMutex(NULL,FALSE,NULL);
	if(ghMsgLock==NULL)
	{
		AfxMessageBox("Comm.dll Init ghMsgLock Fail");
		exit(0);
	}
	InitializeCriticalSection(&gMsgLock);

//	_beginthread(Thread_MsgNotify,100,NULL);
//	_beginthread(Thread_SendAlive,100,NULL);

	return TRUE;
}

bool InitStreamSock()
{
    struct sockaddr_in local;
    gStreamSock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (gStreamSock==INVALID_SOCKET)
    {
       return false;
    }
    local.sin_port=0;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(gStreamSock, (struct sockaddr *)&local, sizeof(local))!=0)
    {
       return false;
    }
	LINGER l;
	l.l_linger=0;
	l.l_onoff=1;
	setsockopt(gStreamSock,SOL_SOCKET,SO_LINGER,(const char*)&l,sizeof(l));
    return true;
}

bool InitClientSock()
{
    gCltSockRecv=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (gCltSockRecv==INVALID_SOCKET)
    {
       return false;
    }
    struct sockaddr_in local;
    local.sin_port=0;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(gCltSockRecv, (struct sockaddr *)&local, sizeof(local))!=0)
    {
       return false;
    }

	LINGER l;
	l.l_linger=0;
	l.l_onoff=1;
	setsockopt(gCltSockRecv,SOL_SOCKET,SO_LINGER,(const char*)&l,sizeof(l));

	gCltSockSend=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (gCltSockSend==INVALID_SOCKET)
		return false;

	local.sin_port=0;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(gCltSockSend, (struct sockaddr *)&local, sizeof(local))!=0)
		return false;

	l.l_linger=0;
	l.l_onoff=1;
	setsockopt(gCltSockSend,SOL_SOCKET,SO_LINGER,(const char*)&l,sizeof(l));
	
    return true;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//                         �ӿں���
//������������������������������������������������������������������������������
/*
void WINAPI RecvFile(int descode,char* sfile,char* dfile)
{
	memset(gRecvStream.recvfilename,0,512);
	strcpy(gRecvStream.recvfilename,dfile);

	TcpPacket packet;
	packet.DesCode=descode;
	packet.PackType=MSG_FILE_GETFILE;
	memset(packet.getfile.SrcFileName,0,512);
	strcpy(packet.getfile.SrcFileName,sfile);
	SendPacket(&packet);
}
*/
//������Ϣ
void WINAPI SendPacket(TcpPacket* packet)
{
	packet->HeadTag=0xeffffffe;
	packet->SrcCode=gLocalCode;
	PutPacketIntoSendBuf(packet);
}

void WINAPI HookRecvIvrData(OnRecvIvrData func)
{
	RecvIvrData=func;
}

//������״̬������Ϣ��Ӧ����
void WINAPI HookConnStatus(OnConnStatus func)
{
	ConnStatus=func;
}
//���ý���������Ϣ��Ӧ����
void WINAPI HookRecvCmd(OnRecvCmd func)
{
	RecvCmd=func;
}

//���û�����Ϣ������Ӧ����
void WINAPI HookRecvMeetInfo(OnRecvMeetInfo func)
{
	RecvMeetInfo=func;
}

//����ͨ��״̬��Ϣ��Ӧ����
void WINAPI HookRecvChanInfo(OnRecvChanInfo func)
{
	RecvChanInfo=func;
}

//������Ϣ���պ���
void WINAPI HookNotiyFunc(OnNotify func)
{
	Notify=func;
}

//���ý��նԷ�Ŀ¼��Ϣ�Ľ��պ���
void WINAPI HookRecvDirInfo(OnRecvDir func)
{
	RecvDir=func;
}

//װ�����ú���
//����:���ڵ���
int WINAPI LoadConfig(LPCTSTR filename)
{
	CIniFile ini;
	ini.Create(filename);
	gLocalCode=atoi(ini.GetStringValue("station","code","0"));
	gLocalPass=ini.GetStringValue("station","pass","");
	gLocalType=atoi(ini.GetStringValue("station","type","-1"));

	gCommCentIP=ini.GetStringValue("commcent","ip","");
	gCommCentPort=atoi(ini.GetStringValue("commcent","port","0"));
	return gLocalCode;
}

//����ͨѶ����
void WINAPI ConnectCenter()
{
	if(gThread_Connect) return;
    gConnStatus=CONN_DISCONNECT;
	closesocket(gCltSockRecv);
	closesocket(gCltSockSend);
	closesocket(gStreamSock);
	InitClientSock();
    InitStreamSock();
	_beginthread(Thread_Connect,100,NULL);
}

//�õ�������
int WINAPI GetConnectResult()
{
	return gConnStatus;
}
/*
//�оٶԷ��������߼������̷���
void WINAPI SendListDrvCmd(int DesCode)
{
	TcpPacket packet;
	memset(&packet,0,sizeof(packet));
	packet.HeadTag=0xeffffffe;
	packet.PackType=MSG_FILE_VIEWDRV;
	packet.SrcCode=gLocalCode;
	packet.DesCode=DesCode;
	gDrvFile.Drv.DrvCnt=0;
	memset(gDrvFile.curdir,0,512);

	send(gCltSockRecv,(char*)&packet,sizeof(packet),0);
}
*/
/*
//�оٶԷ���ָ��Ŀ¼������
void WINAPI SendListDirCmd(int DesCode,const char* dir)
{
	if (gRecvDirEnd) 
	{
		TcpPacket packet;
		memset(&packet,0,sizeof(packet));
		packet.HeadTag=0xeffffffe;
		packet.PackType=MSG_FILE_VIEWDIR;
		packet.SrcCode=gLocalCode;
		packet.DesCode=DesCode;
		memset(packet.viewdir.Dir,0,200);
		strcpy(packet.viewdir.Dir,dir);

	//	gReadyToRecv=RECV_DIRLIST;

		gDrvFile.FileList.empty();
		gDrvFile.code=DesCode;
		memset(gDrvFile.curdir,0,512);
		strcpy(gDrvFile.curdir,dir);

		PutPacketIntoSendBuf(&packet);
//		send(gCltSockRecv,(char*)&packet,sizeof(packet),0);
	}
}
*/
//����һ���ڴ�����gRecvStream.recvbuf
//����ֵ:0-��ʼ����;1-����ʧ��;2-��ǰ�з�����������ִ��
int WINAPI SendMem(int DesCode,char* mem,int len)
{
	return 0;
}
/*
//����һ���ļ�
//����������
//����ֵ:0-��ʼ����;1-����ʧ��;2-��ǰ�з�����������ִ��
int WINAPI SendFile(int DesCode,LPCTSTR filename)
{
	if (gConnStatus!=CONN_OK)
		return 1;
	else if (gThread_SendFile)
	{
		return 2;
	}else
	{
//		if (gSendFile.Res==SF_SENDDING)
//			return 2;
		gSendFile.DesCode=DesCode;
		memset(gSendFile.FileName,0,512);
		strcpy(gSendFile.FileName,filename);
		gSendFile.Res=SF_SENDDING;
		gSendFile.DesReady=false;

		_beginthread(Thread_SendFile,100,NULL);
		return 0;
	}
}
*/
/*
//��ѯ�Է��ڵ��߼�������
void WINAPI GetPeerNodeDrvInfo(int& cnt,char* drv)
{
	cnt=0;
	drv=NULL;
	if(gDrvFile.Drv.DrvCnt>=0)
	{
		cnt=gDrvFile.Drv.DrvCnt;
		strcpy(drv,gDrvFile.Drv.DrvName);
	}
}
*/
/*
//��ѯ�����ļ�״̬
void WINAPI GetFileTransferStatus(int& recved,int& res,float& speed,float& ratio)
{
	recved=gSendFile.FileSendBytesAck;
	res=gSendFile.Res;
	
	int elapse;
	elapse=gSendFile.t_recv-gSendFile.t_lastrecv;
	if (elapse>0)
	{
		speed=float((gSendFile.FileSendBytesAck-gSendFile.LastFileSendBytesAck)*1000/elapse);
	}else
		speed=0;
	if (gSendFile.FileLen>0)
		ratio=float(gSendFile.FileSendBytesAck)/float(gSendFile.FileLen);
	else
		ratio=0;
}

//ֹͣ�ļ����Ͳ���
void WINAPI StopSendFile()
{
	if (gSendFile.filehnd!=NULL)
	{
		CloseHandle(gSendFile.filehnd);
		gSendFile.filehnd=NULL;
	}
	gSendFile.Res=SF_FORCESTOP;
	if (gThread_SendFile)
		gThread_SendFile=false;
}
*/

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//                         �����߳�
//������������������������������������������������������������������������������
/*

//�о�Ŀ¼���ݲ��ҷ���Ŀ¼��Ϣ�߳�
typedef struct{
	char dir[512];
	int descode;
}SendDirPara;
void Thread_ListDir(LPVOID param)
{
	int descode;
	char dir[512];
	TcpPacket packet;

	memset(dir,0,512);
	SendDirPara* para;
	para=(SendDirPara*)param;
	memcpy(dir,(char*)param,strlen((char*)para->dir));
	descode=para->descode;
	delete para;

	if(strlen(dir)>0)
	{
		if(dir[strlen(dir)-1]=='\\')
			strcat(dir,"*");
		else
			strcat(dir,"\\*");
	}else
	{
		dbgmsg("%s is null",dir);
		goto err;
	}

	dbgmsg("thread listdir run,dir=%s",dir);
	WIN32_FIND_DATA finddata;
	HANDLE hFind;
	hFind=FindFirstFile(dir, &finddata);
	if(hFind==INVALID_HANDLE_VALUE) 
	{
		dbgmsg("hFind is null");
		goto err;
	}

	memset(&packet,0,sizeof(packet));
	packet.SrcCode=gLocalCode;
	packet.DesCode=descode;
	packet.HeadTag=0xeffffffe;
	packet.PackType=MSG_FILE_DIRINFO;
	gDrvFile.FileList.empty();
	do{
		strcpy(packet.dirinfo.FileName,finddata.cFileName);
		packet.dirinfo.FileSizeLow=finddata.nFileSizeLow;
		packet.dirinfo.FileSizeHigh=finddata.nFileSizeHigh;
		packet.dirinfo.Attributes=finddata.dwFileAttributes;
		SendPacket(&packet);
		Sleep(10);
	}while(FindNextFile(hFind, &finddata));

	packet.PackType=MSG_FILE_ENDOFDIR;
	SendPacket(&packet);

	dbgmsg("thread listdit exit normally");
	return;
err:
	dbgmsg("thread listdit exit error");
}

//�����ļ��߳�
void Thread_SendFile(LPVOID param)
{
	DWORD t_start,t_now;
	int sended;
	int i=1;

	dbgmsg("send file thread run");
	gSendFile.FileSendBytesAck=0;
	gThread_SendFile=true;
	TcpPacket packet;

	//�����ļ���crcУ����
	DWORD errcode;
	errcode=CCrc32Static::FileCrc32Assembly(gSendFile.FileName,packet.putfile.Crc32);
	if (errcode!=NO_ERROR)
	{
		gSendFile.Res=SF_OPENFILE_FAIL;
		goto end;
	}


	gSendFile.filehnd=CreateFile(gSendFile.FileName,GENERIC_READ,
		                         FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (gSendFile.filehnd==INVALID_HANDLE_VALUE)
	{
		gSendFile.Res=SF_OPENFILE_FAIL;
		goto end;
	}
	else
	{
		gSendFile.FileLen=GetFileSize(gSendFile.filehnd,0);
		gSendFile.FileSendBytes=0;
		gSendFile.FileSendBytesAck=0;
		gSendFile.LastFileSendBytesAck=0;
		gSendFile.t_lastrecv=0;
		gSendFile.t_recv=0;

		packet.HeadTag=0xeffffffe;
		packet.SrcCode=gLocalCode;
		packet.DesCode=gSendFile.DesCode;
		packet.PackType=MSG_FILE_PUTFILE;

		strcpy(packet.putfile.FileName,"c:\\recv.txt");
		packet.putfile.FileLen=gSendFile.FileLen;
		
		sended=send(gCltSockRecv,(char*)&packet,sizeof(packet),0);
		if (sended!=sizeof(packet))
		{
			dbgmsg("not have any ack");
			gSendFile.Res=SF_NETWORK_FAIL;
			goto end;
		}

		t_start=GetTickCount();
		t_now=GetTickCount();
		while(!gSendFile.DesReady)
		{
			t_now=GetTickCount();
			if (TimeSpan(t_start,t_now)>2000)
			{
				dbgmsg("peer have not any ack");
				gSendFile.Res=SF_NOTONLINE;
				goto end;
			}
			Sleep(10);
		}

		gSendFile.FileSendBytesAck=0;
		while (gSendFile.FileSendBytesAck<gSendFile.FileLen)
		{
			if (!gThread_SendFile)
				return;
			DWORD readed;
			char buf[STREAM_BLOCK];
			if (ReadFile(gSendFile.filehnd,buf,STREAM_BLOCK,&readed,0))
			{
				int sendcnt=0;
				sended=send(gStreamSock,buf,readed,0);
resend:
				if (sended==SOCKET_ERROR)
				{
					gSendFile.Res=SF_NETWORK_FAIL;
					goto end;
				}else if (sended<(readed-sendcnt))
				{
					dbgmsg("network busy,wait 100 ms then send");
					sendcnt+=sended;
					sended=send(gStreamSock,buf+sended,readed-sendcnt,0);
					Sleep(100);
					goto resend;
				}

				gSendFile.FileSendBytes+=readed;
				dbgmsg("send %d bytes",gSendFile.FileSendBytes);
				if(gSendFile.FileSendBytes==gSendFile.FileLen)
				{
					dbgmsg("send file fininshed");
					gSendFile.Res=SF_OK;
					goto end;
				}
				//�Ѿ�������һЩ�ֽڣ��ȴ��Է���ȷ�ϼ�������
//				if (gSendFile.FileSendBytes>=i*STREAM_BLOCK*2)
//				{
/*					t_start=GetTickCount();
					while((gSendFile.FileSendBytesAck+STREAM_BLOCK*4)<gSendFile.FileSendBytes)
					{
						t_now=GetTickCount();
						if (TimeSpan(t_start,t_now)>2000)
						{
							gSendFile.Res=SF_NETWORK_FAIL;
							dbgmsg("no ack");
							goto end;
						}
						Sleep(20);
					}
//					i++;
					dbgmsg("recved %d bytes,going on",gSendFile.FileSendBytes);
//				}
			}else
			{
				gSendFile.Res=SF_OPENFILE_FAIL;
				goto end;
			}
		}
	}
end:
	CloseHandle(gSendFile.filehnd);
	gThread_SendFile=false;
	dbgmsg("exit send file thread");
}
*/
//tcp socket�ͻ��������߳�
//ͬʱ�����socket�Ƿ���Ҫ��Ϊ��Ϊ�����ж϶���Ҫ��״̬����
//�жϵ������Ǽ��recvlen,needrecvlen,t_start����
void Thread_SendAlive(LPVOID param)
{
   dbgmsg("comm.dllsend alive thread run");
   gThread_SendAlive=true;
   dbgmsg("comm.dll=>�����߳�����");
   while(gThread_SendAlive)
   {
      TcpPacket packet;
      packet.HeadTag=0xeffffffe;
      packet.SrcCode=gLocalCode;
      packet.DesCode=0;
      packet.PackType=MSG_COMM_ALIVE;
      
      gTimer-=TIME_ALIVE/4;
      if (gTimer<(-TIME_ALIVE))
      {
//		  dbgmsg("comm.dll=>��ͨѶ�������ӶϿ���");
		  gConnStatus=CONN_DISCONNECT;
//		  dbgmsg("comm.dll=>��������ͨѶ���ģ�");
		  ConnectCenter();
		  if(ConnStatus!=NULL)
			  ConnStatus(0,gConnStatus);
      }else if(gTimer<TIME_ALIVE/2)
		  send(gCltSockRecv,(char*)&packet,sizeof(packet),0);

      Sleep(TIME_ALIVE/4);
   }
   dbgmsg("comm.dll=>�����߳��˳�");
}
/*
void Thread_TCPStreamRecv(LPVOID param)
{
	int recved;
	int i=0;

	TcpPacket packet;
	memset(&packet,0,sizeof(packet));
	packet.HeadTag=0xeffffffe;
    packet.SrcCode=gLocalCode;
    packet.DesCode=0;
    packet.PackType=MSG_COMM_LOGIN;
	packet.login.Type=STREAM_SOCK;

    strcpy(packet.login.PassWord,gLocalPass);
	packet.login.Code=gLocalCode;
	packet.login.Type=STREAM_SOCK;
	packet.login.CodeType=gLocalType;
    send(gStreamSock,(char*)&packet,sizeof(packet),0);

	dbgmsg("comm.dll=>�����ݽ����߳�����");
	//�ȴ�5���ӵ�¼��֤
	TIMEVAL tv;
	int nRet;
	tv.tv_sec=5;
	tv.tv_usec=0;
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(gStreamSock,&rfds);
	nRet=select(1,&rfds,NULL,NULL,&tv);
	if (nRet==1)
	{
		recved=recv(gStreamSock,(char*)&packet,sizeof(packet),0);
		if (recved==sizeof(packet))
		{
			gConnStatus=packet.loginres.Res;
			if (ConnStatus!=NULL)
				ConnStatus(1,gConnStatus);
		}
	}else
		goto end;

	while(gThread_TCPStreamRecv)
	{
		//�����ļ�
		if(gReadyToRecv==RECV_FILE)
		{
			char buf[STREAM_BLOCK];
			recved=recv(gStreamSock,buf,STREAM_BLOCK,0);
			dbgmsg("stream file sock recv %d byte",recved);
			if (recved==SOCKET_ERROR)
				break;
			gRecvStream.t_lastrecv=GetTickCount();
			DWORD written;
			if(!WriteFile(gRecvStream.recvfilehnd,buf,recved,&written,0))
				dbgmsg("write file %s error",gRecvStream.recvfilename);
			gRecvStream.recvlen=gRecvStream.recvlen+recved;
			if (gRecvStream.recvlen==gRecvStream.needrecvlen)
			{
				dbgmsg("recv ok,close file");
				CloseHandle(gRecvStream.recvfilehnd);
				gRecvStream.recvfilehnd=NULL;

				//�����ļ�ȫ���ֽ�ȷ��
				packet.HeadTag=0xeffffffe;
				packet.SrcCode=gLocalCode;
				packet.DesCode=gRecvStream.SendCode;
				packet.PackType=MSG_FILE_REPORT;
				packet.report.RecvedDataLen=gRecvStream.recvlen;
				PutPacketIntoSendBuf(&packet);
				//����յ��ļ���crcУ����
				DWORD crc32,errcode;
				packet.PackType=MSG_COMM_NOTIFY;
				errcode=CCrc32Static::FileCrc32Assembly(gRecvStream.recvfilename,crc32);
				if(crc32==gRecvStream.Crc32)
					packet.notify.Event=NT_STREAM_RECV_OK;
				else
					packet.notify.Event=NT_CRC_ERROR;

				PutPacketIntoSendBuf(&packet);

				i=0;
				continue;
			}
			//�յ�4��STREAM_BLOCK�󣬷���һ������ȷ��
			dbgmsg("recved %d bytes",gRecvStream.recvlen);
//			dbgmsg("current len limit is %d",gExpectCount*(STREAM_BLOCK*2)-200);
			i++;
			if(i>=4)
//			if (gRecvStream.recvlen>(gExpectCount*(STREAM_BLOCK*2)-200))
			{
				dbgmsg("send recv ack package");
				packet.SrcCode=gLocalCode;
				packet.DesCode=gRecvStream.SendCode;
				packet.PackType=MSG_FILE_REPORT;
				packet.report.RecvedDataLen=gRecvStream.recvlen;
				PutPacketIntoSendBuf(&packet);
//				dbgmsg("send recv report smg,recved %d",gRecvStream.recvlen);
//				gExpectCount++;
				i=0;
			}
		}else if(gReadyToRecv==RECV_DIRLIST)
		{
			FD_DATA fdata;
			recved=recv(gStreamSock,(char*)&fdata,sizeof(fdata),0);
			if (recved==SOCKET_ERROR)
				break;

			dbgmsg("stream dirlist sock recved %d data",recved);
			if(recved==sizeof(fdata))
			{
				gDrvFile.FileList.push_back(fdata);
			}
		}else
			Sleep(10);
	}
end:
	closesocket(gStreamSock);
	gConnStatus=CONN_DISCONNECT;
	if(ConnStatus!=NULL)
		ConnStatus(0,gConnStatus);
	dbgmsg("stream recv thread exit");
}
*/
//��SendBuf���������
void PutPacketIntoSendBuf(TcpPacket* packet)
{
	if(gSendBuf.AddTail((*packet))==-1)
	{
		gSendBuf.RemoveAll();
		dbgmsg("comm.dll senbuf full");
	}
}

//��gMsgList�������Ϣ
void PutPacketIntoList(TcpPacket* packet)
{
	if(gMsgList.AddTail((*packet))==-1)
	{
		gMsgList.RemoveAll();
		dbgmsg("comm.dll recv packet list full");
		gMsgList.AddTail((*packet));
	}
}

/*
//���յ��Է��ڵ���ļ�Ŀ¼��Ϣ֪ͨ�߳�
void Thread_RecvDirInfoNotify(LPVOID param)
{
	list<FD_DATA>::iterator begin;
	dbgmsg("thread recv dir info run");
	gThread_RecvDirInfoNotify=true;
	while (gThread_RecvDirInfoNotify)
	{
		if (gDrvFile.FileList.size()==0)
		{
			Sleep(40);
			continue;
		}
		begin=gDrvFile.FileList.begin();
		if (RecvDir!=NULL&&begin!=NULL)
		{
			RecvDir(gDrvFile.code,&(*begin),false,"");
			gDrvFile.FileList.pop_front();
		}
		Sleep(20);
	}
	dbgmsg("thread recv dir info exit");
}
*/
//��Ϣ֪ͨ�߳� 
void Thread_MsgNotify(LPVOID param)
{
	gThread_MsgNotify=true;
	dbgmsg("comm thread_msgnotify running");
	while(gThread_MsgNotify)
	{
		//list<TcpPacket>::iterator begin;
		if(gMsgList.GetCount()==0)// if (gMsgList.empty()) 
		{
//			ReleaseMutex(ghMsgLock);
			Sleep(10);
			continue;
		}
		TcpPacket pak;
		gMsgList.RemoveHead(pak);
		switch(pak.PackType)
		{
		case MSG_COMM_NOTIFY:
			if (Notify!=NULL)
				Notify(pak.notify.Event,pak.notify.Para,pak.notify.Msg);
			break;
		default:
			if (RecvCmd!=NULL)
			{
				RecvCmd(&(pak));
			}
			break;
		}
		Sleep(10);
	}
	dbgmsg("comm thread_msgnotify exit");
}

//Socket Data�ͻ��˷����߳�
void Thread_TCPSend(LPVOID param)
{
	gThread_TCPSend=true;
	dbgmsg("thread tcpsend run");
	while(gThread_TCPSend)
	{
		TcpPacket packet;
		TcpPacket head;
		Sleep(10);

		if(gSendBuf.GetCount()==0)
			continue;

		gSendBuf.RemoveHead(head);
	
		int sended=0;
		sended=send(gCltSockSend,(char*)&head,sizeof(TcpPacket),0);
		while(sended<sizeof(TcpPacket))
		{
			int st;
			st=send(gCltSockSend,(char*)&head+sended,sizeof(TcpPacket)-sended,0);
			if(st==SOCKET_ERROR)
				continue;
			sended=sended+st;
		}
		
		dbgmsg("comm.dll=>send packet from thread,descode=%d,packtype=%d,packname=%s",head.DesCode,head.PackType,GetPackName(head.PackType));
	}
	gThread_TCPSend=false;
	dbgmsg("thread tcpsend exit");
}

//���Ͷ˿���֤����
void Thread_TCPSendAuth(LPVOID param)
{
    int recved;
    
	//��¼
	dbgmsg("start send sock auth");
    TcpPacket packet;
	memset(&packet,0,sizeof(packet));
    packet.HeadTag=0xeffffffe;
    packet.SrcCode=gLocalCode;
    packet.DesCode=0;
    packet.PackType=MSG_COMM_LOGIN;

    strcpy(packet.login.PassWord,gLocalPass);
	packet.login.Code=gLocalCode;
	packet.login.Type=DATA_SOCK_SEND;
	packet.login.CodeType=gLocalType;
    send(gCltSockSend,(char*)&packet,sizeof(packet),0);
   
	//�ȴ�5���ӵ�¼��֤
	TIMEVAL tv;
	int nRet;
	tv.tv_sec=5;
	tv.tv_usec=0;
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(gCltSockSend,&rfds);
	nRet=select(1,&rfds,NULL,NULL,&tv);	

	if (nRet==1)
	{
		recved=recv(gCltSockSend,(char*)&packet,sizeof(packet),0);
		if (recved==sizeof(packet))
		{
			gConnStatus=packet.loginres.Res;
			if(ConnStatus!=NULL)
				ConnStatus(0,gConnStatus);
		}
	}else
		goto end;

	if (gConnStatus!=CONN_OK)
	{
		dbgmsg("login failed,err=%d",gConnStatus);
		goto end;
	}
	_beginthread(Thread_TCPSend,100,NULL);
	return;
end:
//    gThread_SendAlive=false;
	gConnStatus=CONN_DISCONNECT;
	if(ConnStatus!=NULL)
		ConnStatus(2,gConnStatus);
    closesocket(gCltSockRecv);
	closesocket(gCltSockSend);
//	closesocket(gStreamSock);
}

//Socket Data�ͻ������ݽ����߳�
void Thread_TCPClient(LPVOID param)
{
    int recved;
    
	//��¼
	gTimer=TIME_ALIVE;
    TcpPacket packet,retpak;
	memset(&packet,0,sizeof(packet));
    packet.HeadTag=0xeffffffe;
    packet.SrcCode=gLocalCode;
    packet.DesCode=0;
    packet.PackType=MSG_COMM_LOGIN;

    strcpy(packet.login.PassWord,gLocalPass);
	packet.login.Code=gLocalCode;
	packet.login.Type=DATA_SOCK_RECV;
	packet.login.CodeType=gLocalType;
    send(gCltSockRecv,(char*)&packet,sizeof(packet),0);
   
	//�ȴ�5���ӵ�¼��֤
	TIMEVAL tv;
	int nRet;
	tv.tv_sec=5;
	tv.tv_usec=0;
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(gCltSockRecv,&rfds);
	nRet=select(1,&rfds,NULL,NULL,&tv);	

	if (nRet==1)
	{
		recved=recv(gCltSockRecv,(char*)&packet,sizeof(packet),0);
		if (recved==sizeof(packet))
		{
			gConnStatus=packet.loginres.Res;
			if(ConnStatus!=NULL)
				ConnStatus(0,gConnStatus);
		}
	}else
		goto end;

	if (gConnStatus!=CONN_OK)
	{
		dbgmsg("login failed,err=%d",gConnStatus);
		goto end;
	}

    while(gThread_TCPClient)
    {
	  recved=recv(gCltSockRecv,(char*)&packet,sizeof(packet),0);
//	  dbgmsg("Thread_TCPClient recved %d bytes",recved);
	  if (recved==SOCKET_ERROR||recved==0)
		  break;

	  while(recved<sizeof(packet))
	  {
		  int rt;
		  rt=recv(gCltSockRecv,(char*)&packet+recved,sizeof(packet)-recved,0);
		  if(rt==SOCKET_ERROR)
			  goto end;
		  recved=recved+rt;
	  }

      if (recved==sizeof(packet))//have data
      {
			switch(packet.PackType)
			{
			 case MSG_COMM_ALIVE:
				 gTimer=TIME_ALIVE;
				 break;
/*			 case MSG_FILE_REPORT:
				 dbgmsg("recved MSG_FILE_REPORT,recved %d bytes",packet.report.RecvedDataLen);
				 gSendFile.t_lastrecv=gSendFile.t_recv;
				 gSendFile.LastFileSendBytesAck=gSendFile.FileSendBytesAck;
				 gSendFile.t_recv=GetTickCount();
				 gSendFile.FileSendBytesAck=packet.report.RecvedDataLen;
				 gReadyToRecv=RECV_FILE;
				 break;
			 case MSG_FILE_VIEWDIR:
				 SendDirPara *dir;
				 dir=new SendDirPara;
				 memset(dir,0,sizeof(SendDirPara));
				 memcpy(dir->dir,packet.viewdir.Dir,200);
				 dir->descode=packet.SrcCode;
				 _beginthread(Thread_ListDir,100,dir);
				 break;
			 case MSG_FILE_VIEWDRV:
				 retpak.HeadTag=0xeffffffe;
				 retpak.DesGrp=0;
				 retpak.SrcCode=packet.DesCode;
				 retpak.DesCode=packet.SrcCode;
				 retpak.PackType=MSG_FILE_DRVINFO;
				 GetLogicDrvInfo(retpak.drvinfo);

				 if(gSendBuf.AddTail(retpak)==-1)
				 {
					 gSendBuf.RemoveAll();
					 dbgmsg("comm.dll send buf full");
				 }

				 break;
			 case MSG_COMM_NOTIFY:
				 dbgmsg("recved MSG_COMM_NOTIFY ");
				 if (gSendFile.DesCode==packet.SrcCode)
				 {
					 if(packet.notify.Event==NT_READY)
						gSendFile.DesReady=true;
					 else if (packet.notify.Event==NT_BUSY)
						 gSendFile.Res=SF_PEER_BUSY;
					 else if (packet.notify.Event==NT_STREAM_RECV_OK)
						 gSendFile.Res=SF_OK;
					 else if (packet.notify.Event==NT_CRC_ERROR)
						 gSendFile.Res=SF_CRC_ERROR;
					 PutPacketIntoList(&packet);
				 }
				 break;
			 case MSG_FILE_GETFILE:
				 {
					 SendFile(packet.SrcCode,packet.getfile.SrcFileName);
				 }
				 break;
			 case MSG_FILE_PUTFILE:
				 retpak.HeadTag=0xeffffffe;
				 retpak.SrcCode=packet.DesCode;
				 retpak.DesCode=packet.SrcCode;
				 retpak.PackType=MSG_COMM_NOTIFY;

				 if (!gRecvStream.OnWork)//Ŀǰ����
				 {
//					 memset(&gRecvStream.recvfilename,0,512);
					 gReadyToRecv=RECV_FILE;
//					 strcpy(gRecvStream.recvfilename,packet.putfile.FileName);
					 gRecvStream.recvfilehnd=CreateFile(gRecvStream.recvfilename,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,0,CREATE_ALWAYS,0,0);
					 gRecvStream.needrecvlen=packet.putfile.FileLen;
					 gRecvStream.recvlen=0;
					 gRecvStream.SendCode=packet.SrcCode;
					 gRecvStream.Crc32=packet.putfile.Crc32;
					 gRecvStream.t_start=GetTickCount();

					 retpak.notify.Event=NT_READY;
					 dbgmsg("send nt_ready msg");
				 }else//Ŀǰ��æ
				 {
					 retpak.notify.Event=NT_BUSY;
					 dbgmsg("send busy msg");
				 }
				 send(gCltSockRecv,(char*)&retpak,sizeof(retpak),0);
				 break;
			 case MSG_FILE_ENDOFDIR:
				 gRecvDirEnd=true;*/
			 default:
				gTimer=TIME_ALIVE; 
				dbgmsg("recv packet from code %d,packtype=%d,packname=%s",packet.SrcCode,packet.PackType,GetPackName(packet.PackType));
				PutPacketIntoList(&packet);
				break;
			}
//		}
	  }
	  Sleep(10);
    }
end:
//    gThread_SendAlive=false;
	gConnStatus=CONN_DISCONNECT;
	if(ConnStatus!=NULL)
		ConnStatus(0,gConnStatus);
	dbgmsg("exit recv pack thread,close client socket");
    closesocket(gCltSockRecv);
	closesocket(gCltSockSend);
	closesocket(gStreamSock);
}

void Thread_Connect(LPVOID param)
{
	gThread_Connect=true;
    struct sockaddr_in remote;
    remote.sin_family = AF_INET;
    remote.sin_port=htons(gCommCentPort);
    remote.sin_addr.s_addr = inet_addr(gCommCentIP);

	if (connect(gCltSockRecv,(sockaddr*)&remote,sizeof(sockaddr))==0)
		_beginthread(Thread_TCPClient,100,NULL);
	else
	{
		if (ConnStatus!=NULL)
 		  ConnStatus(0,5);
	}

	if (connect(gCltSockSend,(sockaddr*)&remote,sizeof(sockaddr))==0)
		_beginthread(Thread_TCPSendAuth,100,NULL);
	else
	{
		if (ConnStatus!=NULL)
			ConnStatus(2,5);
	}

/*	if (connect(gStreamSock,(sockaddr*)&remote,sizeof(sockaddr))==0)
		_beginthread(Thread_TCPStreamRecv,100,NULL);
	else
	{
		if(ConnStatus!=NULL)
 			ConnStatus(1,5);
	}*/
	gThread_Connect=false;
	dbgmsg("comm.dll:connect center thread quit");
}

int CCommApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	gThread_MsgNotify=false;
	gThread_RecvDirInfoNotify=false;
	gThread_SendAlive=false;
	gThread_TCPClient=false;
	gThread_TCPSend=false;
	gThread_TCPStreamRecv=false;
	
	return CWinApp::ExitInstance();
}
