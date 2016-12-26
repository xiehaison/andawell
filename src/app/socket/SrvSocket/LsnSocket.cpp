// LsnSocket.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LsnSocket.h"
#include "../srvsocket/srvcomm.h"
#include "../include/packet.h"
#include "CommSocket.h"


//#include "lsnsocket.h"
extern SOCKET gSocket;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLsnSocket
extern CLsnSocket gLsnSocket;
extern OnMsg gpCallBackMsg;
extern OnNotify gpCallBackNotify;

CLsnSocket::CLsnSocket()
{
    for (int i = 0; i < MAX_NODE; i++)
    {
        m_Sock[i].m_hSocket = INVALID_SOCKET;
    }
}


CLsnSocket::~CLsnSocket()
{
    for (int i = 0; i < MAX_NODE; i++)
    {
        if (m_Sock[i].m_hSocket != INVALID_SOCKET)
        {
            m_Sock[i].ShutDown(2);
            m_Sock[i].Close();
        }
    }
    ShutDown(2);
    Close();
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CLsnSocket, CSocket)
    //{{AFX_MSG_MAP(CLsnSocket)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CLsnSocket member functions

void CLsnSocket::OnAccept(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class

    S_RegNode regnode;
    sock.m_hSocket = INVALID_SOCKET;
    Accept(sock);

    int len = sock.Recv(&regnode, sizeof(regnode));
    if (len <= 0){
        sock.ShutDown(2);
        sock.Close();
        return;
    }
    else
    {
        if (regnode.m_head == PACKET_HEAD)
        {
            if (regnode.m_node > 0 && regnode.m_node < MAX_NODE)
            {
                //该节点没有使用
                if (m_Sock[regnode.m_node].m_hSocket == INVALID_SOCKET)
                {
                    S_RegNodeAck regack;
                    regack.m_result = REGRESULT_OK;
                    int len = sock.send(&regack, sizeof(regack));
                    if (len < 0 || len != sizeof(regack)){
                        OutputLog("收到的通信注册应答包错误!");
                        sock.ShutDown(2);
                        sock.Close();
                        return;
                    }
                    else{
                        GetPeerName(sock.m_rip, sock.m_uPort);
                        OutputLog("IP[%s:%d],[node:%d] socket 已连接!", sock.m_rip, sock.m_uPort, regnode.m_node);
                        gSocket = sock.m_hSocket;
                        gpCallBackNotify(regnode.m_node, COMM_CONNECTED, (char *)&gSocket);
                        //accept的socket是自己的socket
                        m_Sock[regnode.m_node].Create();
                        m_Sock[regnode.m_node].Attach(sock.m_hSocket);
                        m_Sock[regnode.m_node].m_node = regnode.m_node;
                        return;
                    }

                }
                else{
                    OutputLog("该节点已被使用!");
                    sock.ShutDown(2);
                    sock.Close();
                    return;
                }
            }
            else{
                OutputLog("该节点超出范围!");
                sock.ShutDown(2);
                sock.Close();
                return;
            }
        }
        else{
            OutputLog("收到的socket的包头不对,关闭socket连接,节点:%04X,头:%04X", regnode.m_node, regnode.m_head);
            sock.ShutDown(2);
            sock.Close();
            return;
        }
    }
    CSocket::OnAccept(nErrorCode);
}


void CLsnSocket::OnClose(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class
	Close();
	CSocket::OnClose(nErrorCode);
}


int CloseAll()
{
    if (gLsnSocket.m_hSocket == INVALID_SOCKET)
        return 0;
	
	for (int i = 0; i < MAX_NODE; i++){
		gLsnSocket.release(i);
	}

	gLsnSocket.ShutDown(2);
	gLsnSocket.Close();
    return 0;
}


int StartSrv(int port, int max_user)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

        USES_CONVERSION;
    if (!AfxSocketInit())
    {
        AfxMessageBox("AfxSocketInit failed!");
        return FALSE;
    }

    if (!gLsnSocket.Create(port)){
        OutputLog("Srv socket Create Error,%d", GetLastError());
        return -1;
    }

    if (!gLsnSocket.Listen(max_user )){
        OutputLog("Srv socket Listen Error,%d", GetLastError());
        return -1;
    }
    return 0;
}


int   SendPacket(int node, char *pack, WORD len)
{
    static DWORD count;
    int sent = len + 4;
    if (gLsnSocket.m_Sock[node].m_hSocket == INVALID_SOCKET){
        OutputLog("send socket released!,该节点的没有连接");
        return -1;
    }
    else{

        char sendbuf[MAX_MSG_LEN];
        memcpy(&sendbuf[0], &PACKET_HEAD, 2);
        memcpy(&sendbuf[2], &len, 2);
        memcpy(&sendbuf[4], pack, len);


        int cc = 0;
        while (sent){
            int sendlen = gLsnSocket.m_Sock[node].send(&sendbuf[len + 4 - sent], sent);
            if (sendlen < 0)
            {
                OutputLog("SendPacket Send error:%d", GetLastError());
                gLsnSocket.m_Sock[node].ShutDown(2);
                return -1;
            }
            else{
                if (++cc > 10){
                    OutputLog("发送数据[node:%d],packsize=%d,count:%d,重试超限", node, len, count++);
                    break;
                }
                sent -= sendlen;
            }
        }
    }
    OutputLog("发送数据[node:%d],packsize=%d,count:%d",node,len-sent,count++);
    return len;
}

