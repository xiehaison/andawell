#ifndef _buf_h_
#define _buf_h_
//////////////////////////////////////////////////////////////////////
// Buf.cpp: ʵ�ֶ�msg������Ĳ���
// ��̣�����
// ���ڣ�2003��4��6��
// �޸ģ�
//////////////////////////////////////////////////////////////////////
#define MAX_BUF_SIZE 2048
#include "..\\include\\commpack.h"
class CBuf
{
private:
    //�����10��λ�ÿ���������������ʼ��10���ֽ�
    //����GetPacket�Ĳ���
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
