//////////////////////////////////////////////////////////////////////
// Buf.cpp: 实现对msg包缓冲的操作                                   //
// 编程：余涛                                                       //
// 日期：2003年4月6日                                               //
// 修改：                                                           //
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

//从start位置拷贝len长度的数据des中,包含start位置
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

//从缓冲区的m_start位置开始搜索提取一个数据包
//有-返回true,没有-返回false
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
        case 0://发现一个包的包头标记
            if ((*data)==0xeffffffe)
            {
                pakstart=pnt;
                state=1;
                findhead=true;
            }
            break;
        case 1:
            //判断剩余的有效数据区域是否能够包含一个完整的包
            if ((leftdatalen+4)<sizeof(TcpPacket))//不能够
                return false;
            else if ((leftdatalen+4)==sizeof(TcpPacket))//刚好一个包
            {
                //拷贝数据
                CopyData(pakstart,sizeof(TcpPacket),(char*)packet);
                m_start=0;
                m_end=0;
                m_datalen=0;
                return true;
            }else
            {
                //缓冲区中的内容大于一个包的长度,读取下一个包的包头位置，看看是否0xeffffffe;
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
                //移动m_start指针
                m_start=(pakstart+sizeof(TcpPacket))%MAX_BUF_SIZE;
                if (m_start<m_end)
                    m_datalen=m_end-m_start;
                else
                    m_datalen=(MAX_BUF_SIZE-m_start)+m_end;
                return true;
            }else//wrong
            {
                //从pakstart的下一个第4字节开始重新查找
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
        //要求所有包必须是4个字节的整数被数
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

//向缓冲区中添加数据
//缓冲区溢出,返回false,添加成功,返回true
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
