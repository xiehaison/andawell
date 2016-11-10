// CommSrvSock.cpp : 实现文件
//

#include "stdafx.h"
#include "DbClient.h"
#include "CommSrvSock.h"


// CCommSrvSock

CCommSrvSock::CCommSrvSock()
{
}

CCommSrvSock::~CCommSrvSock()
{
}


// CCommSrvSock 成员函数


void CCommSrvSock::OnReceive(int nErrorCode)
{
    // TODO:  在此添加专用代码和/或调用基类
    char szBuf[1536];
    int len = Receive(szBuf, 2048);
    if (len > sizeof(DBPacket))
    {
        RunLog("包长度不对!");
        return;
    }

    DBPacket *pak = (DBPacket *)szBuf;
    if (pak->HeadFlag == 0xeffffffe && pak->PackType == PAK_PROXYINFO){
        m_socktype = pak->proxyinfo.socktype;
    }


    CSocket::OnReceive(nErrorCode);
}


void CCommSrvSock::OnClose(int nErrorCode)
{
    // TODO:  在此添加专用代码和/或调用基类

    CSocket::OnClose(nErrorCode);
}



void CCommSrvSock::SendDBClose(int chan)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    pak.chan = chan;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = PAK_CLOSE;
    
}

//发送数据库操作包
void CCommSrvSock::SendDBPrepare(int chan, LPCTSTR sql, DWORD& sno)
{
    //	RunLog(chan,MT_IVRLOG|MT_IVRERR,"通道%d关联数据库代理断开连接，数据发送失败",chan);
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.chan = chan;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = PAK_PREPARESQL;
    pak.SerialNo = sno;
    strncpy(pak.sqlstat, sql, sizeof(pak.sqlstat));
    //    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
    //    gChanList[pak.chan].DataFlag=DATATOSEND;
}



void CCommSrvSock::SendDBSqlExec(int chan, DWORD& sno)
{
    //	RunLog(chan,MT_IVRLOG|MT_IVRERR,"通道%d关联数据库代理断开连接，数据发送失败",chan);
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.chan = chan;
    pak.HeadFlag = 0xeffffffe;
    pak.SerialNo = sno;
    pak.PackType = PAK_SQLEXEC;
    //    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
    //    gChanList[pak.chan].DataFlag=DATATOSEND;
}


//0-成功,1-失败
void CCommSrvSock::SendDBSqlOpen(int chan, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    pak.chan = chan;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = PAK_SQLOPEN;
    sno = GetTickCount();
    pak.SerialNo = sno;
    //    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
    //    gChanList[pak.chan].DataFlag=DATATOSEND;
}


//
void CCommSrvSock::SendDBMoveBy(int chan, int MoveBy, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.SerialNo = sno;
    pak.chan = chan;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = PAK_MOVENEXT;
    pak.req_MoveBy.MoveBy = MoveBy;
    //    gChanList[chan].DataFlag=IDLE;
    //    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
    //    gChanList[pak.chan].DataFlag=DATATOSEND;
}