//////////////////////////////////////////////////////////////////////
// Buf.cpp: ʵ�ֶ�msg������Ĳ���                                   //
// ��̣�����                                                       //
// ���ڣ�2003��4��6��                                               //
// �޸ģ�                                                           //
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Buf.h"
CBuf::CBuf()
{
    m_start=0;
    m_end=0;
    m_datalen=0;
    memset(m_buf,0,MAX_BUF_SIZE+10);
}

CBuf::~CBuf()
{
}

void CBuf::debug()
{

 //   AddThreadLog("start=%d,end=%d,datalen=%d",m_start,m_end,m_datalen);
}

//��startλ�ÿ���len���ȵ�����des��,����startλ��
void CBuf::CopyData(int start,int len,char* des)
{
    if(len>MAX_BUF_SIZE-start)
    {
        memcpy(des,m_buf+start,(MAX_BUF_SIZE-start));
        memset(m_buf+start,0,(MAX_BUF_SIZE-start));
        memcpy(des+(MAX_BUF_SIZE-start),m_buf,len-(MAX_BUF_SIZE-start));
        memset(m_buf,0,len-(MAX_BUF_SIZE-start));
    }
    else
    {
        memcpy(des,m_buf+start,len);
        memset(m_buf+start,0,len);
    }
}

//�ӻ�������m_startλ�ÿ�ʼ������ȡһ�����ݰ�
//��-����true,û��-����false
bool CBuf::GetPacket(TcpPacket* packet)
{
    DWORD headtag=0xeffffffe;
    DWORD* data;
    int pakstart;
    bool findhead=false;
    int state=0;
    int pnt;
    DWORD leftdatalen;

    data=(DWORD*)(m_buf+m_start);
    pnt=m_start;
    leftdatalen=m_datalen;

    while(pnt!=m_end)
    {
        switch(state)
        {
        case 0://����һ�����İ�ͷ���
            if ((*data)==0xeffffffe)
            {
                pakstart=pnt;
                state=1;
                findhead=true;
            }
            break;
        case 1:
            //�ж�ʣ�����Ч���������Ƿ��ܹ�����һ�������İ�
            if ((leftdatalen+4)<sizeof(TcpPacket))//���ܹ�
                return false;
            else if ((leftdatalen+4)==sizeof(TcpPacket))//�պ�һ����
            {
                //��������
                CopyData(pakstart,sizeof(TcpPacket),(char*)packet);
                m_start=0;
                m_end=0;
                m_datalen=0;
                return true;
            }else
            {
                //�������е����ݴ���һ�����ĳ���,��ȡ��һ�����İ�ͷλ�ã������Ƿ�0xeffffffe;
                pnt=(pnt+sizeof(TcpPacket)-4)%MAX_BUF_SIZE;
                data=(DWORD*)(m_buf+pnt);
                state=2;
                continue;
            }
            break;
        case 2:
            if((*data)==0xeffffffe)//OK,
            {
                CopyData(pakstart,sizeof(TcpPacket),(char*)packet);
                //�ƶ�m_startָ��
                m_start=(pakstart+sizeof(TcpPacket))%MAX_BUF_SIZE;
                if (m_start<m_end)
                    m_datalen=m_end-m_start;
                else
                    m_datalen=(MAX_BUF_SIZE-m_start)+m_end;
                return true;
            }else//wrong
            {
                //��pakstart����һ����4�ֽڿ�ʼ���²���
                m_start=(m_start+4)%MAX_BUF_SIZE;
                m_datalen=m_datalen-4;
                leftdatalen=m_datalen;
                pnt=m_start;
                data=(DWORD*)(m_buf+pnt);
                state=0;
                continue;
            }
            break;
        }
        //Ҫ�����а�������4���ֽڵ���������
        pnt=(pnt+4)%MAX_BUF_SIZE;
        data=(DWORD*)(m_buf+pnt);
        leftdatalen-=4;
    }

    if (findhead==false)
    {
        //  dbgmsg("no head flag in buf,clear buf,in case of occupy space");
        m_start=0;
        m_end=0;
        m_datalen=0;
    }

    return false;
}

//�򻺳������������
//���������,����false,��ӳɹ�,����true
bool CBuf::PutData(char* data,int datalen)
{
    if ((MAX_BUF_SIZE-m_datalen)>datalen)
    {
        if ((MAX_BUF_SIZE-m_end)>=datalen)
        {
            memcpy(m_buf+m_end,data,datalen);
            m_end=m_end+datalen;
        }
        else
        {
            memcpy(m_buf+m_end,data,(MAX_BUF_SIZE-m_end));
            memcpy(m_buf,data+(MAX_BUF_SIZE-m_end),datalen-(MAX_BUF_SIZE-m_end));
            m_end=datalen-(MAX_BUF_SIZE-m_end);
        }
        m_datalen=m_datalen+datalen;
        memcpy(m_buf+MAX_BUF_SIZE,m_buf,10);
        return true;
    }
    else
        return false;
}
