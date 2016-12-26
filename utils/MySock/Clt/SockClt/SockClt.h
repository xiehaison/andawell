// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SOCKCLT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SOCKCLT_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#include <winsock2.h>
#include <malloc.h>
#ifndef _sockclt_h_
#define _sockclt_h_

#ifdef SOCKCLT_EXPORTS
#define SOCKCLT_API __declspec(dllexport)
#else
#define SOCKCLT_API __declspec(dllimport)
#endif

enum{
	SOCK_RECV,
	SOCK_SEND
};

#define MAX_CONN       1024
#define MAX_BUFFSIZE   1024*1024
#define HEAD_TAG       0XEFFFFFFE
#define MAX_PAKSIZE    1024
#define MAX_IDLE_TIME  4000

class CMyQueue{
private:
	char *m_buf;//[MAX_BUFFSIZE];
	int m_pHead,m_pTail;
	int m_paksize;
	int m_maxqueue;
public:
	CMyQueue()
	{
		m_pHead=0;
		m_pTail=0;
		m_buf=(char*)malloc(MAX_BUFFSIZE);
	}
	~CMyQueue()
	{
		if(m_buf!=NULL)
			free(m_buf);
	}
	
	void inline SetPakSize(int size)
	{
		m_paksize=size;
		m_maxqueue=MAX_BUFFSIZE/size;
	}
	
	int inline AddTail(const char* buf)
	{
		if(GetCount() == m_maxqueue - 1){
			return -1;
		}
		memcpy(m_buf+m_pTail*m_paksize,buf,m_paksize);
		m_pTail++;
		if(m_pTail >= m_maxqueue)
			m_pTail = 0;
		
		return m_pTail;
	}
	
	void inline GetHead(char* buf)
	{
		memcpy(buf,m_buf+m_pHead*m_paksize,m_paksize);
	}
	
	void inline RemoveHead(char* buf)
	{
		memcpy(buf,m_buf+m_pHead*m_paksize,m_paksize);
		m_pHead++;
		if(m_pHead >= m_maxqueue)
			m_pHead = 0;
	}
	
	void inline RemoveAll()
	{
		m_pHead = 0;
		m_pTail = 0;
	}
	
	int  inline GetCount()
	{
		if(m_pHead <= m_pTail)
			return m_pTail-m_pHead;
		else
			return m_maxqueue - m_pHead + m_pTail;
	}
	
	int inline IsEmpty()
	{
		if(m_pTail == m_pHead)
			return 1;
		else 
			return 0;
	}
};

typedef struct tagIdentify{
	DWORD head1;  
	DWORD head2;
	WORD  CltCode;
	int   SockType;//0-recv 1-send;
	tagIdentify()
	{
		head1=HEAD_TAG;
		head2=HEAD_TAG;
	};
}Identify;

extern SOCKET gSendSock;
extern SOCKET gRecvSock;

bool InitSockEnv(void);
bool Connect();
bool InitClientSock();
void Thread_CltRecv(LPVOID param);
void Thread_CltSend(LPVOID param);
void Thread_KeepAlive(LPVOID param);
#endif
