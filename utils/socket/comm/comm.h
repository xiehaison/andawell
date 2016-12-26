
#pragma once
#ifndef __COMM_H__
#define __COMM_H__

#include "socket.h"
#pragma  pack(1)


class S_Comm{
public:
    S_Comm()
    {
        memset(m_ipaddr,0,sizeof(m_ipaddr));
        m_port = 0;
    }
    ~S_Comm()
    {
        memset(m_ipaddr,0,sizeof(m_ipaddr));
        m_port = 0;
    }
    
    void SetData(char *ipaddr,int port)    
    {
        strcpy(m_ipaddr,ipaddr);
        m_port = port;
    }
    
    char *GetIP()
    {
        return m_ipaddr;
    }
    
    int GetPort()
    {
        return m_port;
    }
    
private:
public:
    char m_ipaddr[256];
    int m_port;
};



int startcomm();
int closecomm();


#pragma  pack()

#endif//__COMM_H__


