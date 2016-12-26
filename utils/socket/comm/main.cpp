#include "inc.h"

#include "Config.h"
#include "socket.h"
#include "global.h"
#include "../include/packet.h"

using namespace std;

S_Comm g_comm, *gp_comm = NULL;


void notify(int conn_stat)
{

    if (conn_stat)
    {
        OutputLog("socket connected!");
    }
    else{
        OutputLog("socket break!");
    }
}


void on_msg(char *msg,int len)
{
    S_MessagePacket *msgpack = (S_MessagePacket *)msg;
    OutputLog("msgtype:%s!", msgpack->OutputTypeString() );
}


int main(int argc, char* argv[])
{	
    char *conffilename="access.ini";
    char s0[256];
    char s1[256];
    char s2[256];


    GetPrivateProfileString("Total","NodeId","1",s0,sizeof(s0),conffilename);
    cout << "Total " << "NodeId " << s0 << endl;
    cout << conffilename << endl;
    GetPrivateProfileString("SYSTEM","ServerIP","127.0.0.1",s1,sizeof(s1),conffilename);
    cout << "SYSTEM " << "ServerIP " << s1 << endl;
    GetPrivateProfileString("SYSTEM","ServerPort","1271",s2,sizeof(s1),conffilename);
    cout << "SYSTEM " << "ServerPort " << s2 << endl;

    g_comm.SetData(s1,atoi(s2));
    gp_comm = &g_comm;

    sethook(notify,on_msg);
    start_conn_thread();
    S_MessagePacket msgpack;
    int count = 1;
    while( count++ ){
        msgpack.Init(T_AC_TEST_PACKET);
        char c = (count%10)+48;
        memset( msgpack.m_Msg.m_AC_TEST_PACKET.m_testdata, c, count%20 );
        int len = strlen(msgpack.m_Msg.m_AC_TEST_PACKET.m_testdata);
        len = SendPack((char *)&msgpack, len+4);
        OutputLog("sent %c packet,result:%d",c,len);
        sleep(1);
    }
 
    closeall();
    return 0;
}


