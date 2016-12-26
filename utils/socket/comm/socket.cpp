using namespace  std;

#include "inc.h"

#include "socket.h"
#include "../include/packet.h"

extern S_Comm g_comm, *gp_comm ;

int gConnectContinue = 0;
int gTxConnectContinue = 0;


int gTxContinue = 0;
int gRxContinue = 0;

int g_sockrecv = -1;
int g_socksend = -1;
int g_node = 4;
on_notify g_hook_connect = NULL;
on_recv g_hook_recv = NULL;

int start_rx_thread();

struct s_param 
{
    S_Comm *mp_comm;    //传递的参数
    int *m_pcontinue;   //通讯状态
    int *m_pstatus;     //收发线程的状态
    int m_mark;         //描述socket的收发方向
    int *m_psock;       //socket的句柄
};


void sethook(on_notify notify,on_recv recv)
{
    g_hook_connect = notify;
    g_hook_recv = recv;
}


void closeall()
{
    gConnectContinue = 0;
    gTxConnectContinue = 0;
    gTxContinue = 0;
    gRxContinue = 0;
    CloseSocket(g_sockrecv);
    CloseSocket(g_socksend);
}

int	CloseSocket(int fd)
{ 
	int ret;

    if(fd == -1)	 
        return 0;

    shutdown(fd, SD_BOTH);
    ret = close(fd);

	return(ret);
}


int SockRead(const int fd, void *buf, int n, int msec)
{
	int nleft,nbytes;
	char*	ptr;
	int selected;
	fd_set	rdset;
	timeval wait_time;

    if(fd <= 0) {
        OutputLog("SockRead fd=%d,errno=%s",fd,strerror(errno));
        return -1000;
    }

	ptr = (char *)buf;
	nleft = n;
	wait_time.tv_sec = msec/1000;
	wait_time.tv_usec = msec%1000;

	FD_ZERO(&rdset); 
	FD_SET(fd,&rdset);
 
	selected = select(fd+1,&rdset,NULL,NULL,&wait_time); 
    if (selected == 0 || ! FD_ISSET(fd,&rdset)) 
    {
        if(selected == 0)	{
//            OutputLog("recv data timeout!");
            FD_CLR(fd,&rdset);
            FD_ZERO(&rdset); 
            return 0;
        }
        else if (selected == -1)
        {
            OutputLog("recv data select error=%s!",strerror(errno));
            shutdown(fd,SD_BOTH);
            gRxContinue = 0;
        }
        return ERR_SOCKETREAD; 
    }
			 
	while (nleft > 0)  
	{ 
		nbytes = recv(fd,ptr,nleft,0);
		if (nbytes < 0)
		{
            OutputLog("recv data recv error=%s!",strerror(errno));
            shutdown(fd,SD_BOTH);
            gRxContinue = 0;
		} 
		else if (nbytes == 0) 
			break; 
		nleft -= nbytes; 
		ptr += nbytes; 
	} 
	return(n-nleft);
} 


int WriteData(const int fd, const void *buf, int n)
{
	int nleft,nbytes;
	char *ptr;
	
	int errorCode=1, optlen=sizeof(socklen_t); 
	int ret = getsockopt(fd,SOL_SOCKET,SO_ERROR,&errorCode,(socklen_t*)&optlen); 

    if(ret == -1){
        OutputLog("send data  getsockopt error=%s!",strerror(errno));
        shutdown(fd,SD_BOTH);
        gTxContinue = 0;        
        return -1;
    }
    if( errorCode != 0 ){
        OutputLog("send data  getsockopt optval=%s!",errorCode );
		return -1;
    }


	ptr = (char *)buf;
	nleft=n;
	while (nleft > 0)
	{
		nbytes = send(fd,ptr,nleft,0);

		if(nbytes < 0)
		{
            OutputLog("send data failed,fd=%d, error=%s!",fd,strerror(errno));
            gTxContinue = 0;
            return(-1);
		}
		else if (nbytes == 0)
			break;
		nleft -= nbytes;
		ptr += nbytes;
	}

	return(n-nleft);
}


int SendPack(char *buf,int n)
{
    if ( g_socksend && gTxContinue )
    {
        int len = WriteData(g_socksend,&PACKET_HEAD,2);
//        OutputLog("WriteData Head!len=%d",len);
        if (len != 2)
            return -1;
        len = WriteData(g_socksend,&n,2);
//        OutputLog("WriteData length!len=%d",len);
        if (len != 2)
            return -1;
        len = WriteData(g_socksend,buf,n);
//        OutputLog("WriteData Message!len=%d",len);
        if (len != n)
            return -1;
        return len;
    }
    return -1;
}


void *comm_rx_thread(void *param)
{    
    OutputLog("execute comm_rx_thread thread ,g_sockrecv=%d!", g_sockrecv);
//    int hd = *(int *)param;
    int hd = g_sockrecv;

    while(gRxContinue)
    {
        OutputLog("g_sockrecv=%d!", hd);
        short int head = 0;
        short int msglen = 0;
        int len = 0;
        char buf[MAX_RECV_BUF_LEN];
        memset(&buf,0,sizeof(buf));
        len = SockRead(hd, &head, 2, 1000);
        if(len==0){
            OutputLog("no msg!");
            sleep(1);
            continue;
        }
        else if ( len == 1 )
        {
            OutputLog("not occur!socket errno:%s!",strerror(errno));
            gRxContinue = 0;
            break;            
        }
        else if (len == 2)
        {
            if( head == PACKET_HEAD )
            {
                OutputLog("message head received");
                len = SockRead(hd,&msglen,2,1000);
                int readlen = 0;
                if (len == 2)
                {
                    OutputLog("message length received");
                    int recvtime = 0;
                    while (readlen < msglen)
                    {
                        int n = SockRead(hd,&buf[readlen],msglen-readlen,1000);
                        if ( n < 0 )
                        {
                            OutputLog("socket read errno:%s!",strerror(errno));
                            gRxContinue = 0;
                            break;
                        }
                        readlen += n;
                        if( recvtime++ > 10 ){
                            OutputLog("socket read packet timeout!");
                            gRxContinue = 0;
                            break;
                        }
                    }
                    OutputLog("message received!");
                    if (g_hook_recv)
                    {
                        g_hook_recv(buf,msglen);
                    }
                    if (gRxContinue == 0)
                    {
                        break;
                    }
                }
                else if (len == 1)
                {
                    OutputLog("should not occur!socket errno:%s!",strerror(errno));
                    gRxContinue = 0;
                    break            ;
                }
                else if (len == 0)
                {
                    OutputLog("socket read msglen timeout!");
                    gRxContinue = 0;
                    break;
                }
                else if ( len < 0)
                {
                    OutputLog("socket read msglen errno=%s!",strerror(errno));
                    gRxContinue = 0;
                    break;
                }
            }
            else{
                OutputLog("packet head error,socket reset!");
                gRxContinue = 0;
                break;     
            }
        }
        else 
        {
            OutputLog("socket error:%s,len=%d!",strerror(errno),len);
            gRxContinue = 0;
            break;
        }

    }    
    OutputLog("quit comm_rx_thread thread !");
}


int initsock()
{
    int		sockethd;
    
    if ( (sockethd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        OutputLog("Create socket error! error code fd=%d,errno=%d", sockethd,strerror(errno));
        return -1;
    }    
    
    OutputLog("initsock socket ok,fd=%d!",sockethd);
    return sockethd;
}


void *comm_connect_thread(void *param)
{    
    char rip[256];
    int rport;

	sockaddr_in server_addr;
	timeval tm;
    fd_set set;  

    s_param *p_param = (s_param *)param;
    S_Comm *pComm = (class S_Comm *)param;

    strcpy(rip,p_param->mp_comm->GetIP());
    rport = p_param->mp_comm->GetPort();
      
    *p_param->m_psock = initsock();

    OutputLog("inintsock=%d",*p_param->m_psock);

    if (*p_param->m_psock == -1 )
    {
        OutputLog("initsock failed,sock=%d,errno = %s",*p_param->m_psock,strerror(errno));
        exit(-1);
    }

    OutputLog("initsock sock=%d",*p_param->m_psock);

    while (*p_param->m_pcontinue)
    {
        if (*p_param->m_pstatus)
        {
            shutdown(*p_param->m_psock,SD_BOTH);
            *p_param->m_pstatus = 0;    
        }        

        OutputLog("Connect socket remote ip:%s,port:%d",rip,rport);

        memset(&(server_addr.sin_zero), 0, 8);
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(rip);
        server_addr.sin_port = htons(rport);
        
        unsigned long ul = 1; 
        ioctl(*p_param->m_psock, FIONBIO, &ul); //设置为非阻塞模式 

//        OutputLog("connect remote");
        if( connect(*p_param->m_psock, (sockaddr *)&server_addr, sizeof(sockaddr)) == -1 ) 
        { 
           
            tm.tv_sec = CONN_TIMEOUT; 
            tm.tv_usec = 0; 
            
            FD_ZERO(&set); 
            FD_SET(*p_param->m_psock, &set); 
            int ret;
            if( (ret = select(*p_param->m_psock+1, NULL, &set, NULL, &tm)) > 0) 
            { 

                int error;
                int len;
                int r = getsockopt(*p_param->m_psock, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&len); 
               
                if (r == -1)
                {
                    OutputLog("getsockeopt ret=%d,optval=%d,errno=%s",r,error,strerror(errno));
                    FD_CLR(*p_param->m_psock,&set);
                    sleep(1);
                    continue;
                }
                else 
                {
                    if(error == 0) {
                        OutputLog("sock %d connect server ok!,handle:%d", p_param->m_mark,*p_param->m_psock);
                        *p_param->m_pstatus = 1;
                    }
                    else {
                        OutputLog("connect server getsockopt optval failed,error=%s!",strerror(errno));
                        FD_CLR(*p_param->m_psock,&set);
                        sleep(1);
                        continue;
                    }
                }
            }
            else if (ret == 0)
            {
                OutputLog("connect server timeout!");
                FD_CLR(*p_param->m_psock,&set);
                continue;
            }
            else{ 
                OutputLog("connect server select failed,errno=%s!",strerror(errno));
                FD_CLR(*p_param->m_psock,&set);
                sleep(1);
                continue;
            }
        }

        ul = 0; 
        ioctl(*p_param->m_psock, FIONBIO, &ul); //设置为阻塞模式 
        
        S_RegNode regnode;
        regnode.m_node = g_node;
        if (p_param->m_mark == RECV){
            regnode.m_dir = RECV;
            OutputLog("recv handle:%d",*p_param->m_psock);
        }
        else{
            regnode.m_dir = SEND;
            OutputLog("send handle:%d",*p_param->m_psock);
        }
        WriteData(*p_param->m_psock, &regnode, sizeof(regnode));
        S_RegNodeAck regack;
        int readlen = SockRead(*p_param->m_psock,&regack,sizeof(regack),1000);
        if ( readlen == sizeof(regack) )
        {
            if (regack.m_result == REGRESULT_OK)
            {
                if (g_hook_connect)
                {
                    g_hook_connect( *p_param->m_pstatus | p_param->m_mark );
                }
            }
            else{
                OutputLog("Registed failed,server refused!");
                close(*p_param->m_psock);
            }
        }
        else{
            OutputLog("read recv regpacket error!");
            close(*p_param->m_psock);
            return 0;
        }
        
        if (*p_param->m_pstatus)
        {
            if (p_param->m_mark == RECV)
            {
                OutputLog("start rx thread!");
                start_rx_thread();
            }
        }

        while (*p_param->m_pstatus)
        {
            fd_set readset;  
            fd_set writeset;  
            fd_set expset;  
            tm.tv_sec = HEART_TIMEOUT; 
            tm.tv_usec = 0; 
            
            FD_ZERO(&readset); 
            FD_ZERO(&writeset); 
            FD_ZERO(&expset); 
            FD_SET(*p_param->m_psock, &writeset); 
            int r;

            if( (r=select(*p_param->m_psock+1, NULL, &set, NULL, &tm)) > 0) 
            { 
                int error;
                int len;
                int ret = getsockopt(*p_param->m_psock, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&len); 
                if (ret != 0)
                {
                    OutputLog("getsockopt socket optval=%d,errno=%s!",error,strerror(errno));
                    p_param->m_pstatus = 0;                
                }
                else if(error == 0) {
                    OutputLog("normal heartbeat %d ok!",p_param->m_mark);
                    sleep(HEART_TIMEOUT);
                    continue;
                }
                else {
//                    OutputLog("socket test getsockopt optval=%d, error=%s!",error,strerror(errno));
                    sleep(HEART_TIMEOUT);
                }
            } 
            else if ( r == 0 )
            {
                OutputLog("select test timeout!");
                FD_CLR(*p_param->m_psock,&set);
                *p_param->m_pstatus = 0;                
            }
            else{ 
                OutputLog("select test failed,errno=%s!",strerror(errno));
                FD_CLR(*p_param->m_psock,&set);
                *p_param->m_pstatus = 0;                
            }            
        }

        if (g_hook_connect)
        {
            g_hook_connect( *p_param->m_pstatus |(p_param->m_mark<<8));
        }

        OutputLog("heartbeat dead!");
    }
    OutputLog("close Connect thread!");
    return 0;
}


s_param param,    paramtx;
S_Comm param_test;

int start_conn_thread()
{

    pthread_attr_t pthread_attr_recv; 
	pthread_t threadId_recv; 

	pthread_attr_init(&pthread_attr_recv);
	pthread_attr_setdetachstate(&pthread_attr_recv,PTHREAD_CREATE_DETACHED); 
    
    gConnectContinue = 1;


    param.m_mark = RECV;
    param.mp_comm = gp_comm;
    param.m_pcontinue = &gConnectContinue;
    param.m_pstatus = &gRxContinue;
    param.m_psock = &g_sockrecv;

    if (pthread_create(&threadId_recv,&pthread_attr_recv,&comm_connect_thread,&param) != 0) 
	{
		OutputLog("Create comm_connect thread error!!!");
        return -1;
	}


    gTxConnectContinue = 1;
    pthread_attr_t pthread_attr; 
    pthread_t threadId; 
    
    pthread_attr_init(&pthread_attr);
    pthread_attr_setdetachstate(&pthread_attr,PTHREAD_CREATE_DETACHED); 



//    param_test.SetData("192.168.1.224",9901);

    paramtx.m_mark = SEND;
//    paramtx.mp_comm = &param_test;
    paramtx.mp_comm = gp_comm;
  
    paramtx.m_pcontinue = &gTxConnectContinue;
    paramtx.m_pstatus = &gTxContinue;
    paramtx.m_psock = &g_socksend;
    if (pthread_create(&threadId,&pthread_attr,&comm_connect_thread,&paramtx) != 0) 
    {
        OutputLog("Create comm_connect thread error!!!");
        return -1;
    }
    OutputLog("Create comm_connect thread ok!");
    return 0;
}


int start_rx_thread()
{
    pthread_attr_t pthread_attr; 
    pthread_t threadId; 
    
    pthread_attr_init(&pthread_attr);
    pthread_attr_setdetachstate(&pthread_attr,PTHREAD_CREATE_DETACHED); 
    
    if (pthread_create(&threadId,&pthread_attr,&comm_rx_thread,&g_sockrecv) != 0) 
    {
        OutputLog("Create comm_rx_thread thread error!!!");
        return -1;
    }
    OutputLog("Create comm_rx_thread thread ok!");
    return 0;
}



