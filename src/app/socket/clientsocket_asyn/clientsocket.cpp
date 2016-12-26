// clientsocket.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f clientsocketps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "clientsocket.h"
#include "clientsock_asyn.h"
#include "cltsock.h"
#include "../include/packet.h"
#include <string.h>

#include "clientsocket_i.c"

CRITICAL_SECTION gCS;
CRITICAL_SECTION gCSRecv;
CRITICAL_SECTION gCSNotify;

T_MsgNotify   gSockNotify;

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

LPTSTR ConvertErrorCodeToString(DWORD ErrorCode)
{
    HLOCAL LocalAddress = NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, ErrorCode, 0, (LPTSTR)&LocalAddress, 0, NULL);
    return (LPTSTR)LocalAddress;
}


void F_Notify(char *msg,int node,int dir,int notify)
{
    EnterCriticalSection(&gCSNotify);
    T_MsgNotify m_Notify;
    strcpy((char *)&m_Notify.msg, msg);
    m_Notify.node = node;
    m_Notify.dir = dir;
    m_Notify.notify = notify;
    gComm.m_listnotify.push_back(m_Notify); 
    EnterCriticalSection(&gCSNotify);
}

T_MsgNotify gRetMsgNotify;
T_MsgNotify * WINAPI GetNotify()
{
    if (gComm.m_listnotify.empty())
        return NULL;
    EnterCriticalSection(&gCSNotify);
    strcpy((char *)gRetMsgNotify.msg, (char *)gComm.m_listnotify.begin()->msg);
    gRetMsgNotify.dir = gComm.m_listnotify.begin()->dir;
    gRetMsgNotify.node = gComm.m_listnotify.begin()->node;
    gRetMsgNotify.notify = gComm.m_listnotify.begin()->notify;
    gComm.m_listnotify.pop_front();
    LeaveCriticalSection(&gCSNotify);
    return &gRetMsgNotify;
}


DWORD WINAPI  StartClient(const char *rip, DWORD rport, DWORD  node)
{

    AFX_MANAGE_STATE(AfxGetStaticModuleState())

        USES_CONVERSION;

    InitializeCriticalSection(&gCS);
    InitializeCriticalSection(&gCSRecv);
    InitializeCriticalSection(&gCSNotify);

    DWORD err = 0;
    gComm.Init();
    if (!AfxSocketInit())
    {
        OutputLog("AfxSocketInit failed!");
        return FALSE;
    }

    S_RegNode regnode;

    if (!gComm.m_Sock.Create()){
        err = GetLastError();
        OutputLog("socket create error:%d!", err);
        gComm.m_Sock.ShutDown(2);
        gComm.Close();
        return -1;
    }

    if (!gComm.m_Sock.Connect(rip, rport)){
        err = GetLastError();
        OutputLog("socket connect error,ip:%s,port:%d,node:%d,error:%d,strerr=%s", rip, rport, node, err, ConvertErrorCodeToString(err));
        gComm.m_Sock.ShutDown(2);
        gComm.Close();
        return err;
    }

    regnode.m_node = node;
    if (!gComm.m_Sock.Send(&regnode, sizeof(regnode))){
        err = GetLastError();
        OutputLog("send register packet error,node:%d,dir:%d,error:%d!", node, err);
        gComm.m_Sock.ShutDown(2);
        gComm.Close();
        return err;
    }
    S_RegNodeAck regack;

    //gNotify("Recv register answer packet!",0);
    int len = gComm.m_Sock.Recv(&regack, sizeof(regack));
    if (len < 0){
        gComm.Close();
        return -1;
    }

    if (gComm.m_Sock.m_hSocket == INVALID_SOCKET)
	{
        F_Notify("Registed failed,recv socket error !", node, RECV, E_ERROR_Socket);
        OutputLog("Registed failed,socket closed!");
        gComm.m_Sock.ShutDown(2);
        gComm.Close();
        return -1;
	}

	if (len<sizeof(regack)) 
	{
        F_Notify("Registed failed,recv socket  包长度错误!", node, RECV, E_ERROR_PACKLEN);
        OutputLog("Registed failed! packet len error");
        gComm.m_Sock.ShutDown(2);
        gComm.Close();
        return -1;
	}

	if (regack.m_result != REGRESULT_OK)
	{
		OutputLog("Registed failed,recv socket refused!");
        F_Notify("Registed failed,recv sock 服务器拒绝!", node, RECV, E_ERROR_ACK);
        gComm.m_Sock.ShutDown(2);
        gComm.Close();

		return -1;
	}

    F_Notify("Registed ok!", node, RECV, E_RECV_OK);

    return 0;

}



void WINAPI  TcpSockSend(void *buf, DWORD  len)
{
    EnterCriticalSection(&gCS);
    int retlen = SendPacket((char *)buf, len);
    if (retlen < 0)
    {
        OutputLog("发送数据失败!socket连接中断");
        CloseAll();
    }
    LeaveCriticalSection(&gCS);
}

//参数中len的类型不可随意变,必须是2个字节
int SendPacket(const char *msg, DWORD len)
{
    static DWORD count;
    WORD msulen = len;
    //回调传回的错误消息,要使用静态变量才不会丢失
    int send = 0;
    if (gComm.m_Sock.m_hSocket == INVALID_SOCKET)
    {
        OutputLog("socket not connected!");
        return -1;
    }
    char sendbuf[MAX_MSG_LEN];
    memcpy(&sendbuf[0], &PACKET_HEAD, 2);
    memcpy(&sendbuf[2], &msulen, 2);
    memcpy(&sendbuf[4], msg, len);
    int retry = 0;

    while (send < len + 4){
        int size;
        size = gComm.m_Sock.send(&sendbuf[send], len + 4);
        if (size < 0)
        {
            DWORD error = GetLastError();
            OutputLog("sendpacket socket error=%d:%s", error, ConvertErrorCodeToString(error));
            gComm.Close();
            return -1;
        }
        else if (retry++>10){
            OutputLog("发送消息次数超限!");
            gComm.Close();
            return -1;
        }
        else {
            send += size;
        }
    }

    OutputLog("发送数据成功!count=%d,packsize=%d", count++, len);
    return len;
}



///线程安全
T_Msg gRetMsg;
T_Msg * WINAPI  GetRecvMsg()
{
    //T_Msg msu;
    memset(&gRetMsg, 0, sizeof(gRetMsg));
    if (gComm.m_RecvQueue.empty())
        return NULL;
    EnterCriticalSection(&gCSRecv);
    gRetMsg.len = gComm.m_RecvQueue.begin()->len;
    memcpy(gRetMsg.msg, gComm.m_RecvQueue.begin()->msg, gRetMsg.len);
    gComm.m_RecvQueue.pop_front();
    LeaveCriticalSection(&gCSRecv);
    return &gRetMsg;
}


int WINAPI  CloseAll()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    USES_CONVERSION;

    gComm.Close();
    return 0;
}

