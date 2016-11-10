#ifndef _buf_h_
#define _buf_h_
//////////////////////////////////////////////////////////////////////
// Buf.cpp: 实现对msg包缓冲的操作
// 编程：余涛
// 日期：2003年4月6日
// 修改：
//////////////////////////////////////////////////////////////////////
#define MAX_BUF_SIZE 2048
#include "..\\include\\commpack.h"
class CBuf
{
private:
    //多余的10个位置拷贝拷贝缓冲区开始的10个字节
    //便于GetPacket的操作
    char m_buf[MAX_BUF_SIZE+10];
    int m_start,m_end;
    int m_datalen;

    void CopyData(int start,int len,char* des);
public:
    CBuf();
    virtual ~CBuf();
    bool GetPacket(TcpPacket* packet);
    bool PutData(char* data,int datalen);
    void debug();
};
#endif
