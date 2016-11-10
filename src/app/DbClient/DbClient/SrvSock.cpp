// SrvSock.cpp : 实现文件
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


// CSrvSock 成员函数


void CSrvSock::OnAccept(int nErrorCode)
{
    // TODO:  在此添加专用代码和/或调用基类

    CCommSrvSock  *pSocket = new CCommSrvSock;

    if (!Accept(*pSocket))
        delete pSocket;
    m_sock_list.AddTail(pSocket);
    CSocket::OnAccept(nErrorCode);
}


void CSrvSock::OnConnect(int nErrorCode)
{
    // TODO:  在此添加专用代码和/或调用基类

    CSocket::OnConnect(nErrorCode);
}


void CSrvSock::OnReceive(int nErrorCode)
{
    // TODO:  在此添加专用代码和/或调用基类

    CSocket::OnReceive(nErrorCode);
}


void CSrvSock::OnClose(int nErrorCode)
{
    // TODO:  在此添加专用代码和/或调用基类
    while (!m_sock_list.IsEmpty())
    {
        CCommSrvSock  *pSocket = m_sock_list.GetHead();
        delete pSocket;
        m_sock_list.RemoveHead();
    }
    CSocket::OnClose(nErrorCode);
}
