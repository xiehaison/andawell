// clientsocket.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f clientsocketps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "clientsocket.h"
#include "clientsock.h"
#include "cltsock.h"
#include "../include/packet.h"
#include <string.h>

#include "clientsocket_i.c"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

class CClientsocketApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientsocketApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CClientsocketApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CClientsocketApp, CWinApp)
	//{{AFX_MSG_MAP(CClientsocketApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CClientsocketApp theApp;

BOOL CClientsocketApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_CLIENTSOCKETLib);
    return CWinApp::InitInstance();
}

int CClientsocketApp::ExitInstance()
{
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}


CClientComm gComm;

OnMsg gMsg = NULL;
OnNotify gNotify = NULL;

int StartClient(const char *rip,int rport,int node)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
		USES_CONVERSION;
	if (!AfxSocketInit())
	{
		Output("AfxSocketInit failed!");
		return FALSE;
	}	

	S_RegNode regnode;
	
	CCltSock *psock = new CCltSock;
	if(!psock->Create()){
		Output("socket create error:%d!",GetLastError());		
		delete psock;
        return -1;
	}

	if(!psock->Connect(rip,rport)){
		Output("socket connect error,ip:%s,port:%d,node:%d,error:%d",rip,rport,node,GetLastError());
        delete psock;
		return -1;
	}
	
	regnode.m_dir = RECV;
	regnode.m_node = node;
	if ( !psock->Send(&regnode,sizeof(regnode)) ){
		Output("send register packet error,node:%d,dir:%d,error:%d!",node,GetLastError());
        delete psock;
		return -1;
	}
	S_RegNodeAck regack;

	gNotify("Recv register answer packet!",0);
	psock->SetTimeOut();
	int len=psock->Receive(&regack,sizeof(regack));
	psock->KillTimeOut();
	if (psock->m_hSocket == -1)
	{
		Output("Registed failed,socket closed!");
        delete psock;
		return -1;
	}

	if (len<sizeof(regack))
	{
		Output("Registed failed! packet len error");
        delete psock;
		return -1;		
	}

	if (regack.m_result != REGRESULT_OK)
	{
		Output("Registed failed,recv socket refused!");
		gNotify("Registed failed,recv socket refused!",0);
        delete psock;
		return -1;
	}

	if (gNotify)
	{
		gNotify("接收SOCKET已连接",0);
	}
    psock->m_dir = RECV;
	gComm.m_pRecvSock = psock;

	psock = new CCltSock;
	
    if ( !psock->Create() )
    {
        Output("send socket create failed!");
        delete psock;
        return -1;
    }
    if(!psock->Connect(rip,rport))
    {
        Output("send socket connect failed!");
        delete psock;
        return -1;
    }
	regnode.m_dir = SEND;
	regnode.m_node = node;
	psock->Send(&regnode,sizeof(regnode));
	psock->SetTimeOut();
	len=psock->Receive(&regack,sizeof(regack));
	psock->KillTimeOut();
	if (psock->m_hSocket == -1)
	{
		Output("Registed failed,socket closed!");
        delete psock;
		return -1;
	}
	
	if (len<sizeof(regack))
	{
		Output("Registed failed! packet len error");
        delete psock;
		return -1;		
	}
	
	if (regack.m_result!=REGRESULT_OK)
	{
		Output("Registed failed,send socket refused!");
        delete psock;
		return -1;
	}
	if (gNotify)
	{
		gNotify("发送SOCKET已连接",0);
	}
    psock->m_dir = SEND;
    gComm.m_Node = node;
	gComm.m_pSendSock = psock;
	return 0;
}


int SetHook(OnMsg msg,OnNotify notify)
{
	gMsg = msg;
	gNotify = notify;
	return 0;
}


int SendPacket(const char *msg,short int len)
{
    if (!gComm.m_pSendSock)
    {
        Output("SendPacket send socket not init!");
        return -1;
    }
 	if (gComm.m_pSendSock->m_hSocket == -1 || gComm.m_pSendSock == NULL)
	{
		Output("socket not connected!");
		return -1;
	}
	gComm.m_pSendSock->Send( &PACKET_HEAD,sizeof(PACKET_HEAD));
	gComm.m_pSendSock->Send( &len, 2);
	int send = len;
	while (send>0)
	{
		int l = gComm.m_pSendSock->Send( &msg[len-send], len);
		if ( l < 0 )
		{
			gNotify("SendPacket send socket error",0);
			return -1;
		}
		else if(l == 0){
			Sleep(100);
			continue;
		}
		else{
			send -= l;
		}
	}

	return 0;
}



int CloseAll()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
        
        USES_CONVERSION;

    if (gComm.m_pRecvSock )
    {
        if (gComm.m_pRecvSock->m_hSocket != -1)
            gComm.m_pRecvSock->ShutDown();
        gComm.m_pRecvSock = NULL;
    }
    if (gComm.m_pSendSock )
    {
        if (gComm.m_pSendSock->m_hSocket != -1)
            gComm.m_pSendSock->ShutDown();
        gComm.m_pSendSock = NULL;
    }
	gComm.m_Node = -1;
	return 0;
}

