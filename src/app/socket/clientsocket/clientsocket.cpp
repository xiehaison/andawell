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

LPTSTR ConvertErrorCodeToString(DWORD ErrorCode)
{
    HLOCAL LocalAddress = NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, ErrorCode, 0, (LPTSTR)&LocalAddress, 0, NULL);
    return (LPTSTR)LocalAddress;
}


void F_Notify(char *msg,int node,int notify)
{
    T_MsgNotify m_msg;
    strcpy((char *)&m_msg.msg, msg);
    m_msg.node = node;
    m_msg.notify = notify;
    gNotify((char*)&m_msg, notify);
}


DWORD StartClient(const char *rip,int rport,int node)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
    USES_CONVERSION;

    DWORD err = 0;
    gComm.Init();
	if (!AfxSocketInit())
	{
		OutputLog("AfxSocketInit failed!");
		return FALSE;
	}	

	
    if (!gComm.m_Sock.Create()){
        err = GetLastError();
		OutputLog("socket create error:%d!",err);		
        gComm.Close();
        return -1;
	}

    if (!gComm.m_Sock.Connect(rip, rport)){
        err = GetLastError();
        OutputLog("socket connect error,ip:%s,port:%d,node:%d,error:%d,strerr=%s", rip, rport, node, err, ConvertErrorCodeToString(err));
        gComm.Close();
		return -2;
	}
	
    S_RegNode regnode;
    regnode.m_node = node;
    if (!gComm.m_Sock.send(&regnode, sizeof(regnode))){
        err = GetLastError();
		OutputLog("send register packet error,node:%d,error:%d!",node,err);
        gComm.Close();
		return -3;
	}
	S_RegNodeAck regack;

    int len = gComm.m_Sock.Recv(&regack, sizeof(regack));

    if (len < 0)
	{
        F_Notify("Registed failed,recv socket error !", node, E_ERROR_REG);
        OutputLog("Registed failed,socket closed!");
        gComm.Close();
		return -1;
	}

	if (len<sizeof(regack))
	{
        F_Notify("Registed failed,recv socket  包长度错误!", node, E_ERROR_REG);
        OutputLog("Registed failed! packet len error");
        gComm.Close();
		return -1;		
	}

	if (regack.m_result != REGRESULT_OK)
	{
		OutputLog("Registed failed,recv socket refused!");
        F_Notify("Registed failed,recv sock 服务器拒绝!", node,  E_ERROR_REG);
        gComm.Close();
		return -1;
	}

    gComm.m_Node = node;
	if (gNotify)
	{
		F_Notify("recv Registed ok!", node,  E_RECV_OK);
    }

	return 0;
}


int SetHook(OnMsg msg,OnNotify notify)
{
	gMsg = msg;
	gNotify = notify;
	return 0;
}

//参数中len的类型不可随意变,必须是2个字节
int SendPacket(const char *msg,WORD len)
{
    static DWORD count;
    //回调传回的错误消息,要使用静态变量才不会丢失
    static char errmsg[1000];
    int send = 0;
    if (gComm.m_Sock.m_hSocket == INVALID_SOCKET)
	{
		OutputLog("socket not connected!");
		return -1;
	}
    char sendbuf[MAX_MSG_LEN];
    memcpy(&sendbuf[0], &PACKET_HEAD, 2);
    memcpy(&sendbuf[2], &len, 2);
    memcpy(&sendbuf[4], msg,len);
    int retry = 0;

    while (send < len + 4){
        int size;
        size = gComm.m_Sock.send(&sendbuf[send], len + 4);
        if (size < 0)
        {
            DWORD error = GetLastError();
            OutputLog("socket error=%d:%s", error, ConvertErrorCodeToString(error));
            gComm.Close();
            return -1;
        }
        else if(retry++>10){
            OutputLog("发送消息次数超限!" );
            gComm.Close();
            return -1;
        }
        else {
            send += size;
        }
    }

    OutputLog("发送数据成功!count=%d,packsize=%d",count++,len);
	return len;
}


int CloseAll()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
        
        USES_CONVERSION;
    gComm.Close();

	return 0;
}

