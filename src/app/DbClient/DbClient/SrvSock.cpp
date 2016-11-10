// SrvSock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DbClient.h"
#include "SrvSock.h"


// CSrvSock

CSrvSock::CSrvSock()
{
}

CSrvSock::~CSrvSock()
{
}


// CSrvSock ��Ա����


void CSrvSock::OnAccept(int nErrorCode)
{
    // TODO:  �ڴ����ר�ô����/����û���

    CCommSrvSock  *pSocket = new CCommSrvSock;

    if (!Accept(*pSocket))
        delete pSocket;
    m_sock_list.AddTail(pSocket);
    CSocket::OnAccept(nErrorCode);
}


void CSrvSock::OnConnect(int nErrorCode)
{
    // TODO:  �ڴ����ר�ô����/����û���

    CSocket::OnConnect(nErrorCode);
}


void CSrvSock::OnReceive(int nErrorCode)
{
    // TODO:  �ڴ����ר�ô����/����û���

    CSocket::OnReceive(nErrorCode);
}


void CSrvSock::OnClose(int nErrorCode)
{
    // TODO:  �ڴ����ר�ô����/����û���
    while (!m_sock_list.IsEmpty())
    {
        CCommSrvSock  *pSocket = m_sock_list.GetHead();
        delete pSocket;
        m_sock_list.RemoveHead();
    }
    CSocket::OnClose(nErrorCode);
}
