#include "stdafx.h"
#include <process.h>
#include "communic.h"
//#include "global.h"
#include "../../include/ctidef.h"
#include "../../include/commpack.h"
//#include "inifile.h"
//#include "thread.h"
//#include "msgout.h"


bool gThread_TcpSend_RunFlag;

//数据库代理连接socket和端口
SOCKET gTCPSrvSock;
int gDBSrvPort;

list<SOCKET> gConnSock;
DBProxy gDBProxyList[MAX_DBPROXY];
int gDBProxyCnt=1;

int gOutCnt;
int gInCnt;
int gTotalCnt;
int gDBSendCnt;
int gDBRecvCnt;


/*
//根据数据库通讯代理的设置查找对应的socket
bool GetDBProxy(int chan,CString& ip,int& port)
{
        for (i=0;i<gDBOpProxyCnt;i++)
        {
            if (chan>=gDBOpProxy[i].StartNo&&chan<=gDBOpProxy[i].EndNo)
            {
                ip=CString(gDBOpProxy[i].IP);
                port=gDBOpProxy[i].Port;
                return true;
            }
        }
    return false;
}
*/
//发送数据库操作包
void SendDBPrepare(int chan,LPCTSTR sql,DWORD& sno)
{
//	RunLog(chan,MT_IVRLOG|MT_IVRERR,"通道%d关联数据库代理断开连接，数据发送失败",chan);
    SOCKET sock=GetDBProxySock(chan);
    if (sock==0)
    {
        RunLog("通道%d关联数据库代理断开连接，数据发送失败",chan);
        return;
    }
    DBPacket pak;
    memset(&pak,0,sizeof(pak)); 
	sno=GetTickCount();
    pak.chan=chan;
    pak.HeadFlag=0xeffffffe;
    pak.PackType=PAK_PREPARESQL;
	pak.SerialNo=sno;
    strncpy(pak.sqlstat,sql,sizeof(pak.sqlstat));
//    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
//    gChanList[pak.chan].DataFlag=DATATOSEND;
}


void SendDBSqlExec(int chan,DWORD& sno)
{
//	RunLog(chan,MT_IVRLOG|MT_IVRERR,"通道%d关联数据库代理断开连接，数据发送失败",chan);
    SOCKET sock=GetDBProxySock(chan);
    if (sock==0)
    {
        RunLog("通道%d关联数据库代理断开连接，数据发送失败",chan);
        return;
    }
    DBPacket pak;
    memset(&pak,0,sizeof(pak));
	sno=GetTickCount();
    pak.chan=chan;
    pak.HeadFlag=0xeffffffe;
	pak.SerialNo=sno;
    pak.PackType=PAK_SQLEXEC;
//    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
//    gChanList[pak.chan].DataFlag=DATATOSEND;
}


//0-成功,1-失败
void SendDBSqlOpen(int chan,DWORD& sno)
{
    SOCKET sock=GetDBProxySock(chan);
    if (sock==0)
    {
        RunLog("通道%d关联数据库代理断开连接，数据发送失败",chan);
        return;
    }
    DBPacket pak;
    memset(&pak,0,sizeof(pak));
    pak.chan=chan;
    pak.HeadFlag=0xeffffffe;
    pak.PackType=PAK_SQLOPEN;
	sno=GetTickCount();
	pak.SerialNo=sno;
//    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
//    gChanList[pak.chan].DataFlag=DATATOSEND;
}

void SendDBClose(int chan)
{
    SOCKET sock=GetDBProxySock(chan);
    if (sock==0)
    {
        RunLog("通道%d关联数据库代理断开连接，数据发送失败",chan);
        return;
    }
    DBPacket pak;
    memset(&pak,0,sizeof(pak));
    pak.chan=chan;
    pak.HeadFlag=0xeffffffe;
    pak.PackType=PAK_CLOSE;
//    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
//    gChanList[pak.chan].DataFlag=DATATOSEND;
}

void SendDBUdpateField(int chan,BYTE ind,int vType,int iValue,
					double fValue,const char* sValue,const char* tValue,DWORD& sno)
{
    SOCKET sock=GetDBProxySock(chan);
    if (sock==0)
    {
        RunLog("通道%d关联数据库代理断开连接，数据发送失败",chan);
        return;
    }
    DBPacket pak;
    memset(&pak,0,sizeof(pak));
    pak.chan=chan;
    pak.HeadFlag=0xeffffffe;
    pak.PackType=PAK_UPDATEFIELD;
    pak.req_updatefield.vType=vType;
    pak.req_updatefield.FieldInd=ind;
	
    switch(vType)
    {
    case CON_I:
        pak.req_updatefield.ICon=iValue;
        break;
    case CON_S:
		{
			char temp[254]="";
			memset(temp,0,254);
			if(strlen(sValue)>253)
			{
				RunLog("通道%d的SetParam字符参数长度最多不能超过253个字符长度",chan);
				memcpy(temp,sValue,253);
			}else
				strcpy(temp,sValue);
			
			strcat(pak.req_updatefield.SCon,"'");
			strcat(pak.req_updatefield.SCon,temp);
			strcat(pak.req_updatefield.SCon,"'");
			break;
		}
    case CON_T:
        strcpy(pak.req_updatefield.TCon,tValue);
        break;
    case CON_F:
        pak.req_updatefield.FCon=fValue;
        break;
    default:
        RunLog("通道%d错误的UpdateField包数据类型",chan);
        break;
    }

	sno=GetTickCount();
	pak.SerialNo=sno;
//    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
//    gChanList[pak.chan].DataFlag=DATATOSEND;
}

void SendDBSetParam(int chan,BYTE ind,BYTE InOut,int vType,int iValue,
					double fValue,const char* sValue,const char* tValue,DWORD& sno)
{
    SOCKET sock=GetDBProxySock(chan);
    if (sock==0)
    {
        RunLog("通道%d关联数据库代理断开连接，数据发送失败",chan);
        return;
    }
    DBPacket pak;
    memset(&pak,0,sizeof(pak));
    pak.chan=chan;
    pak.HeadFlag=0xeffffffe;
    pak.PackType=PAK_SETPARA;
    pak.req_SetPara.vType=vType;
    pak.req_SetPara.FieldInd=ind;
    pak.req_SetPara.InOut=InOut;

    if (InOut==PARAM_IN)
    {
        switch(vType)
        {
        case CON_I:
            pak.req_SetPara.ICon=iValue;
            break;
        case CON_S:
			{
				char temp[254]="";
				memset(temp,0,254);
				if(strlen(sValue)>253)
				{
					RunLog("通道%d的SetParam字符参数长度最多不能超过253个字符长度",chan);
					memcpy(temp,sValue,253);
				}else
					strcpy(temp,sValue);

				strcat(pak.req_SetPara.SCon,"'");
				strcat(pak.req_SetPara.SCon,temp);
				strcat(pak.req_SetPara.SCon,"'");
				break;
			}
        case CON_T:
            strcpy(pak.req_SetPara.TCon,tValue);
            break;
        case CON_F:
            pak.req_SetPara.FCon=fValue;
            break;
        default:
            RunLog("通道%d错误的SetParam包数据类型",chan);
            break;
        }
    }
	sno=GetTickCount();
	pak.SerialNo=sno;
//    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
//    gChanList[pak.chan].DataFlag=DATATOSEND;
}

void SendDBGetParamOut(int chan,int ind,int type,DWORD& sno)
{
    SOCKET sock=GetDBProxySock(chan);
    if (sock==0)
    {
        RunLog("通道%d关联数据库代理断开连接，数据发送失败",chan);
        return ;
    }
    DBPacket pak;
    memset(&pak,0,sizeof(pak));
    pak.chan=chan;
	sno=GetTickCount();
	pak.SerialNo=sno;
    pak.HeadFlag=0xeffffffe;
    pak.PackType=PAK_GETPARAMOUT_REQ;
    pak.req_GetField.vType=type;
    pak.req_GetField.FieldInd=ind;
//    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
//    gChanList[pak.chan].DataFlag=DATATOSEND;
}

//查询结果,ind-字段索引,type-获取字段类型
void SendDBGetField(int chan,int ind,int type,DWORD& sno)
{
    SOCKET sock=GetDBProxySock(chan);
    if (sock==0)
    {
        RunLog("通道%d关联数据库代理断开连接，数据发送失败",chan);
        return;
    }
    DBPacket pak;
    memset(&pak,0,sizeof(pak));
	sno=GetTickCount();
    pak.chan=chan;
	pak.SerialNo=sno;
    pak.HeadFlag=0xeffffffe;
    pak.PackType=PAK_GETFIELD_REQ;
    pak.req_GetField.vType=type;
    pak.req_GetField.FieldInd=ind;
//    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
//    gChanList[pak.chan].DataFlag=DATATOSEND;
}

//
void SendDBMoveBy(int chan,int MoveBy,DWORD& sno)
{
    SOCKET sock=GetDBProxySock(chan);
    if (sock==0)
    {
        RunLog("通道%d关联数据库代理断开连接，数据发送失败",chan);
        return;
    }
    DBPacket pak;
    memset(&pak,0,sizeof(pak));
	sno=GetTickCount();
	pak.SerialNo=sno;
    pak.chan=chan;
    pak.HeadFlag=0xeffffffe;
    pak.PackType=PAK_MOVENEXT;
    pak.req_MoveBy.MoveBy=MoveBy;
//    gChanList[chan].DataFlag=IDLE;
//    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
//    gChanList[pak.chan].DataFlag=DATATOSEND;
}

SOCKET GetDBProxySock(int chan)
{
    int cnt=gConnSock.size();
    int ind;

    if (gDBProxyCnt==0)
        return 0;
    ind=chan%gDBProxyCnt;
    return gDBProxyList[ind].sendsock;

    /*	list<SOCKET>::iterator begin,il;
    	begin=gConnSock.begin();
    	il=begin;
    	int i=0;
    	while(i<ind)
    		il++;
    	return (*il);*/
}
//发送没有参数的数据库操作指令
//eof,sqlopen,sqlexec
void SendDBOpCmd(int chan,int MsgType,DWORD& sno)
{
    SOCKET sock=GetDBProxySock(chan);
    if (sock==0)
    {
        RunLog("通道%d关联数据库代理断开连接，数据发送失败",chan);
        return;
    }
    DBPacket pak;
    memset(&pak,0,sizeof(pak));
	sno=GetTickCount();
    pak.chan=chan;
	pak.SerialNo=sno;
    pak.HeadFlag=0xeffffffe;
    pak.PackType=MsgType;
//    gChanList[chan].DataFlag=IDLE;
//    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
//    gChanList[pak.chan].DataFlag=DATATOSEND;
}

//计费包
void SendDBPak(int chan,DBPacket pak)
{
    SOCKET sock=GetDBProxySock(chan);
    if (sock==0)
    {
        RunLog("通道%d关联数据库代理断开连接，数据发送失败",chan);
        return;
    }
    pak.HeadFlag=0xeffffffe;
//    gChanList[chan].DataFlag=IDLE;

//    memcpy(&gChanList[pak.chan].dbpak,&pak,sizeof(pak));
//    gChanList[pak.chan].DataFlag=DATATOSEND;
}
/*
//
//发送UDP数据包
//0-成功,1-proxycode不存在,2-发送失败
int SendUDPData(int chan,int proxycode,LPCTSTR data)
{
    if (proxycode>=gProxyCnt||proxycode<0)
            return 1;
        UDPPacket pak;
        memset(&pak,0,sizeof(pak));
        strcpy(pak.SendIP,gLocalIP);
        pak.SendPort=gLocalPort;
        pak.chan=chan;
        pak.HeadFlag=0xEFFFFFFE;
        pak.PackType=MSG_CHANDATA;
        pak.PackTag=GetTickCount();
        if (strlen(data)>256)
            RunLog(chan,MT_IVRLOG|MT_IVRERR,"通道%d发送的数据长度超过256字节，超过部分被截掉",chan);
        strcpy(pak.Message,data);
        if (SendUDP(pak))
            return 0;
        else
            return 2;
    return 0;
}
*/
/*
//发送数据库UDP包
bool SendDBUDP(SOCKET sock,UDPPacket pak)
{
    int res;
    struct sockaddr_in to;
    to.sin_family = AF_INET;
    to.sin_addr.s_addr = inet_addr(pak.RecvIP);
    to.sin_port=htons(pak.RecvPort);
    res=sendto(sock,(char*)&pak,sizeof(UDPPacket),0,(sockaddr*)&to,sizeof(sockaddr));
    return (res==sizeof(UDPPacket));
}
*/


//初始化Socket,启动UDP接收线程
bool StartSock()
{
    struct sockaddr_in local;
    gTCPSrvSock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (gTCPSrvSock==INVALID_SOCKET)
        return false;

	CIniFile ini("./Client.ini");
	gDBSrvPort=ini.GetIntValue("dbproxy","port",0);
    local.sin_port=htons(gDBSrvPort);
    local.sin_family=AF_INET;
    local.sin_addr.s_addr=INADDR_ANY;
    if (bind(gTCPSrvSock,(struct sockaddr *)&local, sizeof(local))!=0)
    {
        RunLog("清检查TCP端口%d是否被占用",34534);
        return false;
    }


    if (listen(gTCPSrvSock,SOMAXCONN)==0)
    {
        _beginthread(Thread_TCPConnect,100,NULL);
		_beginthread(Thread_TcpSend,100,NULL);
    }

    return true;
}

void Thread_TCPConnect(LPVOID param)
{
    RunLog("Tcp连接监听线程启动");
    while(true)
    {
        SOCKET sock;
        struct sockaddr_in remote;
        int len=sizeof(remote);
        sock=accept(gTCPSrvSock,(struct sockaddr FAR *)&remote,&len);
        if (sock!=INVALID_SOCKET)
        {
            linger t;
            t.l_linger=0;
            t.l_onoff=1;
            setsockopt(sock,SOL_SOCKET,SO_LINGER,(const char FAR*) &t,sizeof(t)) ;


            Th_TcpSendRecv_Para* thpara=new Th_TcpSendRecv_Para;
            memset(thpara,0,sizeof(Th_TcpSendRecv_Para));
            strcpy(thpara->ip,inet_ntoa(remote.sin_addr));
            thpara->port=ntohs(remote.sin_port);
            thpara->sock=sock;
            _beginthread(Thread_TcpRecv,100,thpara);
        }else
            break;
        Sleep(10);
    }
    RunLog("Tcp连接监听线程退出");
}

void Thread_TcpSend(LPVOID param)
{
	int no;
	int i;
        RunLog("数据库代理数据发送线程启动");
        gThread_TcpSend_RunFlag=true;
        while(gThread_TcpSend_RunFlag)
        {
            for (i=0;i<gOutCnt;i++)
            {
                if (gDBProxyCnt==0)
                    break;
				no=i%gDBProxyCnt;
				//if(gChanList==0)
				//	return;
//                if (gChanList[i].DataFlag==DATATOSEND&&gDBProxyList[no].sendsock!=0)
//                {
//					int sended;
//					int sendcnt=0;
////					RunLog( "SEND DB PAK,CHAN %d,PakType%d,SNo=%d",i,gChanList[i].dbpak.PackType,gChanList[i].dbpak.SerialNo);
//                    sended=send(gDBProxyList[no].sendsock,(char*)(&gChanList[i].dbpak),sizeof(DBPacket),0);
//                    sendcnt+=sended;
//					if(sendcnt<sizeof(DBPacket))
//					{
//						char *psendbuf=(char*)(&gChanList[i].dbpak)+sended;
//						sended=send(gDBProxyList[no].sendsock,psendbuf,sizeof(DBPacket)-sendcnt,0);
//						sendcnt+=sended;
//						RunLog( "send twice");
//					}
//
//					
//					gDBSendCnt++;
//                    gChanList[i].DataFlag=IDLE;
//                }
            }
            Sleep(20);
        }
        RunLog("数据库代理数据发送线程退出");
}

void Thread_TcpRecv(LPVOID param)
{
    SOCKET sock;
    int res;
    int no=0;
    char ip[20]="";
    int port;
    fd_set rfds;
    DBPacket pak;
    int recved;
    TIMEVAL tv;
    int totallen=0;
	char pakbuf[sizeof(DBPacket)];
	int buflen=0;
	int nextrecvcnt=sizeof(DBPacket);

    sock=((Th_TcpSendRecv_Para*)param)->sock;
    strcpy(ip,((Th_TcpSendRecv_Para*)param)->ip);
    port=((Th_TcpSendRecv_Para*)param)->port;

    delete (Th_TcpSendRecv_Para*)param;

    tv.tv_sec=2;
    tv.tv_usec=0;

    FD_ZERO(&rfds);
    FD_SET(sock,&rfds);

    //判断端口类型
	RunLog("判断sock类型");
    res=select(1,&rfds,NULL,NULL,&tv);
    if (res==1)
    {
        recved=recv(sock,(char*)(&pak),sizeof(pak),0);
        if (recved==sizeof(pak))
        {
            if (pak.HeadFlag==0xeffffffe&&pak.PackType==PAK_PROXYINFO)
            {
                no=pak.proxyinfo.proxyno;

                if(no>=0&&no<MAX_DBPROXY)
                {
                    memset(gDBProxyList[no].ip,0,20);
                    strcpy(gDBProxyList[no].ip,ip);
                    if (pak.proxyinfo.socktype==SOCK_SEND)
                    {
	                    gDBProxyList[no].recvport=port;
                        gDBProxyList[no].recvsock=sock;
                    }else if (pak.proxyinfo.socktype==SOCK_RECV)
                    {
	                    gDBProxyList[no].sendport=port;
                        gDBProxyList[no].sendsock=sock;
						return;
                    }else
                    {
						closesocket(sock);
                        RunLog( "%s地址%d端口的数据库代理编号%未知的sock类型",ip,port,no);
                        goto quit;
                    }
                }else
				{
					closesocket(sock);
                    RunLog( "%s地址%d端口的数据库代理编号%越界",ip,port,no);
				}
            }else
            {
				closesocket(sock);
                RunLog( "%s地址%d端口的数据库代理编号%登记数据包错误",ip,port,no);
                goto quit;
            }
        }else
        {
			closesocket(sock);
            RunLog( "%s地址%d端口的数据库代理编号%超时没有登记",ip,port,no);
            goto quit;
        }
    }

        RunLog("数据库代理[%s][%d]数据接收线程%d启动",ip,no,sock);
        while(true)
        {
            recved=recv(sock,(char*)&pak,nextrecvcnt,0);
            if (recved==SOCKET_ERROR||recved==0)
                goto quit;
            totallen+=recved;
//            dbgerr(-1,"total=%d",totallen);

            if(recved<sizeof(pak))
            {
				memcpy(pakbuf+buflen,&pak,recved);
				buflen+=recved;
				nextrecvcnt=sizeof(DBPacket)-buflen;
				if (nextrecvcnt==0)
				{
					nextrecvcnt=sizeof(DBPacket);
					buflen=0;
					memcpy(&pak,pakbuf,sizeof(pak));
				}else
				{
//					dbgerr(-1,"接收到数据长度%d<%d,保存到缓冲区",recved,sizeof(pak));
					continue;
				}
            }
//			RunLog( "recv db pak ,chan %d,PAKTYPE%d,SNo=%d",pak.chan,pak.PackType,pak.SerialNo);

            if (pak.HeadFlag!=0xeffffffe)
            {
                RunLog("接收数据格式错误");
                continue;
            }
            gDBRecvCnt++;

            int chan=pak.chan;
            if (pak.chan<0||pak.chan>=gTotalCnt)
            {
                RunLog("数据包通道%d越界",chan);
                continue;
            }

//			RunLog(chan,MT_SYSLOG,"recv db data");

            switch(pak.PackType)
            {
			case PAK_PREPARESQL_READY:
			case PAK_SETPARA_READY:
			case PAK_SQLEXEC_OK:
			case PAK_SQLEXEC_ERR:
			case PAK_GETFIELD_VALUE:         
			case PAK_EOF_RES:                       
			case PAK_MOVENEXT_RES:
			case PAK_GETPARAMOUT_VALUE: 
			case PAK_GETFIELD_ERR:
//                memcpy(&gChanList[chan].dbpak,&pak,sizeof(pak));
//                gChanList[chan].DataFlag=HAVEDATA;
                break;
/*            case PAK_GETPARAMOUT_VALUE:
                memcpy(&gChanList[chan].dbpak,&pak,sizeof(pak));
                gChanList[chan].DataFlag=HAVEDATA;
                break;
            case PAK_COMPLETE:
                memcpy(&gChanList[chan].dbpak,&pak,sizeof(pak));
                gChanList[chan].DataFlag=HAVEDATA;
                break;
//            case PAK_VERIFYACCOUNT_RES:
//            case PAK_VERIFYPASSWORD_RES:
            case PAK_EOF_RES:
                memcpy(&gChanList[chan].dbpak,&pak,sizeof(pak));
                gChanList[chan].DataFlag=HAVEDATA;
                break;*/
            default:
                RunLog( "接收到错误类型数据包");
                break;
            }
        }

quit:
    if (gDBProxyList[no].sendsock!=0)
	{
        closesocket(gDBProxyList[no].sendsock);
		gDBProxyList[no].sendsock=0;
	}
    if (gDBProxyList[no].recvsock!=0)
	{
        closesocket(gDBProxyList[no].recvsock);
		gDBProxyList[no].recvsock=0;
	}

    RunLog("数据库代理数据接收线程%d退出",sock);
}

















