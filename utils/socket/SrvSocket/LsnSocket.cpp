// LsnSocket.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LsnSocket.h"
#include "srvcomm.h"
#include "../include/packet.h"


//#include "lsnsocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLsnSocket
extern CLsnSocket gLsnSocket;
extern OnMsg gpCallBackMsg ; 
extern OnNotify gpCallBackNotify ; 

CLsnSocket::CLsnSocket()
{
    m_pSockRecv = NULL;
    m_pSockSend = NULL;
}


CLsnSocket::~CLsnSocket()
{
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
	CCommSocket *psock = new CCommSocket;
	Accept(*psock);
	
	psock->Receive(&regnode,sizeof(regnode));
	if (regnode.m_head==PACKET_HEAD)
	{
		if (regnode.m_dir != -1 && regnode.m_node != -1)
		{
			if (regnode.m_dir ==  SEND )
			{
                if (m_pSockRecv == NULL)
				{
                    m_pSockRecv = psock;
                    m_pSockRecv->m_dir = RECV;
                    m_pSockRecv->m_node = regnode.m_node;
                    OutputLog("Accept m_pSockRecv handle:%d!",psock->m_hSocket);
				}
				else if (m_pSockRecv->m_hSocket == -1 )
                {
                    m_pSockRecv = psock;
                    m_pSockRecv->m_dir = RECV;
                    m_pSockRecv->m_node = regnode.m_node;
                    OutputLog("Accept m_pSockRecv handle:%d!",psock->m_hSocket);
                }
				else{
					OutputLog("m_pSockRecv 已有连接!");
                    psock->Close();
                    delete psock;
                    return ;
				}
			}
			else if ( regnode.m_dir == RECV )
			{
				if (m_pSockSend == NULL)
				{
                    m_pSockSend = psock;
                    m_pSockSend->m_dir = SEND;
                    m_pSockSend->m_node = regnode.m_node;
                    OutputLog("Accept m_pSockSend handle:%d!",psock->m_hSocket);
				}
                else if (m_pSockSend->m_hSocket == INVALID_SOCKET )
                {
                    m_pSockSend = psock;
                    m_pSockSend->m_dir = SEND;
                    m_pSockSend->m_node = regnode.m_node;
                    OutputLog("Accept m_pSockSend handle:%d!",psock->m_hSocket);
                }
				else{
					OutputLog("m_pSockSend 已有连接!");
                    psock->Close();
                    delete psock;
                    return;
				}
			}
			S_RegNodeAck regack;
			regack.m_result = REGRESULT_OK;
			psock->Send(&regack,sizeof(regack));
			gpCallBackNotify(regnode.m_node,regnode.m_dir|COMM_CONNECTED);
		}
		else
		{
			OutputLog("节点:%04X,方向:%04X,头:%04X",regnode.m_node,regnode.m_dir,regnode.m_head);
			psock->Close();
		}
	}
	else{
		OutputLog("节点:%04X,方向:%04X,头:%04X",regnode.m_node,regnode.m_dir,regnode.m_head);
		psock->Close();
	}

	CSocket::OnAccept(nErrorCode);
}


void CLsnSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
    if ( m_pSockRecv )
    {
        if (m_pSockRecv->m_hSocket != -1)
        {   
            m_pSockRecv->ShutDown();
        }
    }

    if (m_pSockSend)
    {
        if (m_pSockSend->m_hSocket != -1)
        {   
            m_pSockSend->ShutDown();
        }
    }
    Close();	
	CSocket::OnClose(nErrorCode);
}


int CloseAll()
{ 

    if(gLsnSocket.m_hSocket == -1)
    {
        return 0;
    }
    if (gLsnSocket.m_pSockRecv && gLsnSocket.m_pSockRecv->m_hSocket != -1)
    {
        gLsnSocket.m_pSockRecv->ShutDown();
    }
    if (gLsnSocket.m_pSockSend && gLsnSocket.m_pSockSend->m_hSocket != -1)
    {
        gLsnSocket.m_pSockSend->ShutDown(0);
    }
    if (gLsnSocket.m_hSocket != -1)
    {
        gLsnSocket.ShutDown();
    }
	return 0;
}


int StartSrv(int port,int max_user)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	USES_CONVERSION;
	if (!AfxSocketInit())
	{
		AfxMessageBox("AfxSocketInit failed!");
		return FALSE;
	}	
	if(!gLsnSocket.Create(port)){
		OutputLog("Srv socket Create Error,%d",GetLastError());
		return -1;		
	}
	if(!gLsnSocket.Listen(max_user*2)){
		OutputLog("Srv socket Listen Error,%d",GetLastError());
		return -1;
	}
	return 0;
}


int SendPacket(int node,char *pack,int len)
{
    if (!gLsnSocket.m_pSockSend){
        OutputLog("send socket released!");
        return -1;
    }
	if( gLsnSocket.m_pSockSend->m_node == node && gLsnSocket.m_pSockSend->m_hSocket != -1){
		int sent = len;
		while( sent ){
			
            gLsnSocket.m_pSockSend->Send( &PACKET_HEAD,sizeof(PACKET_HEAD));
			gLsnSocket.m_pSockSend->Send( &len, 2);
            OutputLog("SendPacket handle:%d",gLsnSocket.m_pSockSend->m_hSocket);
            
			int sendlen = gLsnSocket.m_pSockSend->Send(&pack[len-sent],sent);
			if (sendlen < 0)
			{
				OutputLog("SendPacket Send error:%d",GetLastError());
				break;
			}
			else if(sendlen == 0){
				OutputLog("SendPacket Send error:%d",GetLastError());
				Sleep(100);
			}
			else{
				sent -= sendlen;
			}
		}
        if (sent == 0)
            return len;
	}
	return 0;
}



int SendPacket1(int node,char *pack,int len)
{
    if (!gLsnSocket.m_pSockRecv){
        OutputLog("send socket released!");
        return -1;
    }
    if( gLsnSocket.m_pSockRecv->m_node == node && gLsnSocket.m_pSockRecv->m_hSocket != -1){
        int sent = len;
        while( sent ){
            
            gLsnSocket.m_pSockRecv->Send( &PACKET_HEAD,sizeof(PACKET_HEAD));
            gLsnSocket.m_pSockRecv->Send( &len, 2);
            OutputLog("SendPacket handle:%d",gLsnSocket.m_pSockRecv->m_hSocket);
            
            int sendlen = gLsnSocket.m_pSockRecv->Send(&pack[len-sent],sent);
            if (sendlen < 0)
            {
                OutputLog("m_pSockRecv Send error:%d",GetLastError());
                break;
            }
            else if(sendlen == 0){
                OutputLog("m_pSockRecv Send error:%d",GetLastError());
                Sleep(100);
            }
            else{
                sent -= sendlen;
            }
        }
        if (sent == 0)
            return len;
    }
    return 0;
}

