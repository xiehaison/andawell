// CommSrvSock.cpp : ʵ���ļ�
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


// CCommSrvSock ��Ա����


void CCommSrvSock::OnReceive(int nErrorCode)
{
    // TODO:  �ڴ����ר�ô����/����û���
    char szBuf[1536];
    int len = Receive(szBuf, 2048);
    if (len > sizeof(DBPacket))
    {
        RunLog("�����Ȳ���!");
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
    // TODO:  �ڴ����ר�ô����/����û���

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

//�������ݿ������
void CCommSrvSock::SendDBPrepare(int chan, LPCTSTR sql, DWORD& sno)
{
    //	RunLog(chan,MT_IVRLOG|MT_IVRERR,"ͨ��%d�������ݿ����Ͽ����ӣ����ݷ���ʧ��",chan);
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
    //	RunLog(chan,MT_IVRLOG|MT_IVRERR,"ͨ��%d�������ݿ����Ͽ����ӣ����ݷ���ʧ��",chan);
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


//0-�ɹ�,1-ʧ��
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