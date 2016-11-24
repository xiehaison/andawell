#pragma once

#ifndef  __PACKET_H__
#define __PACKET_H__

#pragma  pack(1)

#define MAX_MSG_LEN 1500
#define COMM_CONNECTED  1
#define COMM_BROKEN		0
#define MAX_FILENAME_LENGTH 256




const BYTE REF_I = 1;
const BYTE REF_F = 2;
const BYTE REF_T = 3;
const BYTE REF_S = 4;
const BYTE CON_I = 5;
const BYTE CON_F = 6;
const BYTE CON_S = 7;
const BYTE CON_T = 8;
const BYTE CON_SYS = 9;
const BYTE CON_EXP = 10;


#define PARAM_IN   0
#define PARAM_OUT  1



const short int RECV = 1<<8;
const short int SEND = 2<<8;
const short int PACKET_HEAD=0x7FFE;


#define  PackName(a)  #a

#define	PAK_BILL               68


//数据库通讯代理使用数据包
enum{
    PAK_NONE,
    PAK_PREPARESQL,
    PAK_PREPARESQL_READY,

    PAK_SETPARA,
    PAK_SETPARA_READY,

    PAK_SQLEXEC,
    PAK_SQLEXEC_OK,
    PAK_SQLEXEC_ERR,

    PAK_SQLOPEN,

    PAK_GETFIELD_REQ,
    PAK_GETFIELD_VALUE,
    PAK_GETFIELD_ERR,

    PAK_EOF_REQ,
    PAK_EOF_RES,

    PAK_MOVENEXT,
    PAK_MOVENEXT_RES,

    PAK_GETPARAMOUT_REQ,
    PAK_GETPARAMOUT_VALUE,
    PAK_GETPARAMOUT_ERR,

    PAK_COMPLETE,

    PAK_DBCFG,                //数据库代理连接上来后的配置信息
    PAK_PROXYINFO,

    PAK_UPDATEFIELD,
    PAK_UPDATEFIELD_RES,

    PAK_CLOSE
};


inline char* GetDBPakName(int dbpak)
{
    switch (dbpak)
    {
    case PAK_PREPARESQL_READY:return "PAK_PREPARESQL_READY";
    case PAK_SETPARA_READY:return "PAK_SETPARA_READY";
    case PAK_SQLEXEC_OK:return "PAK_SQLEXEC_OK";
    case PAK_SQLEXEC_ERR:return "PAK_SQLEXEC_ERR";
    case PAK_GETFIELD_VALUE:return "PAK_GETFIELD_VALUE";
    case PAK_EOF_RES:return "PAK_EOF_RES";
    case PAK_MOVENEXT_RES:return "PAK_MOVENEXT_RES";
    case PAK_GETPARAMOUT_VALUE:return "PAK_GETPARAMOUT_VALUE";
    case PAK_GETFIELD_ERR:return "PAK_GETFIELD_ERR";
    case PAK_COMPLETE:return "PAK_COMPLETE";
    default:return "NoName";
    }
}


typedef struct{
    int total;//数据库代理总数
    int no;//数据库代理编号
}Tcp_DbCfg;

#define SOCK_RECV 0
#define SOCK_SEND 1
typedef struct{
    int proxyno;
    int socktype;
}Tcp_ProxyInfo;
//MoveBy
typedef struct{
    DWORD MoveBy;
}Req_MoveBy;

//UpdateField
typedef struct{
    BYTE vType;
    BYTE FieldInd;
    union{       //参数值
        DWORD  ICon;
        double FCon;
        char   TCon[14];
        char   SCon[256];
    };
}Req_UpdateField;

//EOF数据
typedef struct{
    DWORD MoveBy;
}Req_EOF;

typedef struct{
    DWORD ICon;//EOF结果,1-到达末尾,0-没有
}Ret_EOF;

//GetParamOut数据包
typedef struct{
    BYTE vType;//字段类型
    BYTE FieldInd;//字段索引
}Req_GetParamOut;
typedef struct{
    BYTE vType;//字段类型
    BYTE FieldInd;//字段索引
    union{       //参数值
        DWORD  ICon;
        double FCon;
        char   TCon[14];
        char   SCon[256];
    };
}Ret_GetParamOut;

//SetPara数据包
typedef struct{
    BYTE vType;
    BYTE InOut;
    BYTE FieldInd;
    union{       //参数值
        DWORD  ICon;
        double FCon;
        char   TCon[14];
        char   SCon[256];
    };
}Req_SetPara;

typedef struct{
    char DBName[20];
}Req_SetDB;

typedef struct{
    int res;//操作结果,1-ok,0-fail;
}Ret_SetDB;

//GetField数据包
typedef struct{
    BYTE vType;//字段类型
    BYTE FieldInd;//字段索引
}Req_GetField;

typedef struct{
    BYTE vType;//字段类型
    BYTE FieldInd;//字段索引
    union{       //参数值
        DWORD  ICon;
        double FCon;
        char   TCon[14];
        char   SCon[256];
    };
}Ret_GetField;



typedef struct{
    DWORD HeadFlag;
    int chan;
    DWORD PackType;
    DWORD SerialNo;
    union{
        Req_SetPara             req_SetPara;

        Req_GetField            req_GetField;
        Ret_GetField            ret_GetField;

        Req_GetParamOut         req_GetParamOut;
        Ret_GetParamOut         ret_GetParamOut;

        Req_MoveBy              req_MoveBy;

        Req_EOF                 req_EOF;
        Ret_EOF                 ret_EOF;

        Req_SetDB               req_SetDB;
        Ret_SetDB               ret_SetDB;


        char                    sqlstat[256];
        char                    errmsg[256];

        Tcp_DbCfg               dbcfg;
        Tcp_ProxyInfo           proxyinfo;

        Req_UpdateField         req_updatefield;
    };
    int Result;
}DBPacket;



enum
{
    IA_Login,
    IA_LoginResult,
    IA_ReqServerInfo,
    IA_ReqServerInfoResult,
    IA_ReqTestMachineInfo,
    IA_ReqTestMachineInfoResult,
    IA_ReqMonitor,
    IA_ReqMonitorResult,
};


typedef struct {}S_IA_Login;
typedef struct {}S_IA_LoginResult;
typedef struct {}S_IA_ReqServerInfo;
typedef struct {}S_IA_ReqServerInfoResult;
typedef struct {}S_IA_ReqTestMachineInfo;
typedef struct {}S_IA_ReqTestMachineInfoResult;
typedef struct {}S_IA_ReqMonitor;
typedef struct {}S_IA_ReqMonitorResult;


typedef struct tag_IA_Packet{
    DWORD HeadTag;  //=0xeffffffe
    DWORD SrcCode;  //源地址
    DWORD DesCode;  //目的地址
    DWORD PackType; //包类型
    DWORD DesGrp;   //目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组

    DWORD SerialNo;   //序列号             
    union{
        S_IA_Login                      Login;
        S_IA_LoginResult                LoginResult;
        S_IA_ReqServerInfo              ReqServerInfo;
        S_IA_ReqServerInfoResult        ReqServerInfoResult;
        S_IA_ReqTestMachineInfo         ReqTestMachineInfo;
        S_IA_ReqTestMachineInfoResult   ReqTestMachineInfoResult;
        S_IA_ReqMonitor                 ReqMonitor;
        S_IA_ReqMonitorResult           ReqMonitorResult;
    };
    tag_IA_Packet(){
        memset(this, 0, sizeof(tag_IA_Packet));
    };
}tag_IA_Packet;





enum{
    IB_ReqCtrlInfo,
    IB_ReqCtrlInfoResult,
    IB_StartTest,
    IB_PauseTest,
    IB_SuspendTest,
    IB_StopTest,
    IB_ContinueTest,
    IB_ReqTestData,
    IB_ReqTestDataResult,

};

typedef struct   {} S_IB_ReqCtrlInfo;
typedef struct   {} S_IB_ReqCtrlInfoResult;
typedef struct   {} S_IB_StartTest;
typedef struct   {} S_IB_PauseTest;
typedef struct   {} S_IB_SuspendTest;
typedef struct   {} S_IB_StopTest;
typedef struct   {} S_IB_ContinueTest;
typedef struct   {} S_IB_ReqTestData;
typedef struct   {} S_IB_ReqTestDataResult;


enum{
    ID_RegTestMachine,
    ID_ResetTestMachine,
    ID_SynTestMachineInfo,
    ID_StartTestPlan,
    ID_PauseTestPlan,
    ID_SuspendTestPlan,
    ID_ContinueTestPlan,
    ID_StopTestPlan,
    ID_ReqMonitor,
    ID_ReqMonitorResult,
    ID_SendMonitorData,

};

typedef struct {}    S_ID_RegTestMachine;
typedef struct {}    S_ID_ResetTestMachine;
typedef struct {}    S_ID_SynTestMachineInfo;
typedef struct {}    S_ID_StartTestPlan;
typedef struct {}    S_ID_PauseTestPlan;
typedef struct {}    S_ID_SuspendTestPlan;
typedef struct {}    S_ID_ContinueTestPlan;
typedef struct {}    S_ID_StopTestPlan;
typedef struct {}    S_ID_ReqMonitor;
typedef struct {}    S_ID_ReqMonitorResult;
typedef struct {}    S_ID_SendMonitorData;


enum{
    IE_ReqCtrlInfo,
    IE_ReqCtrlInfoResult,
    IE_StartTest,
    IE_PauseTest,
    IE_SuspendTest,
    IE_StopTest,
    IE_ContinueTest,
    IE_ReqTestData,
    IE_ReqTestDataResult,
};



typedef struct tag_IB_Packet{
    DWORD HeadTag;  //=0xeffffffe
    DWORD SrcCode;  //源地址
    DWORD DesCode;  //目的地址
    DWORD PackType; //包类型
    DWORD DesGrp;   //目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组

    DWORD SerialNo;   //序列号             
    union{
        S_IB_ReqCtrlInfo		 ReqCtrlInfo;
        S_IB_ReqCtrlInfoResult   ReqCtrlInfoResult;
        S_IB_StartTest           StartTest;
        S_IB_PauseTest           PauseTest;
        S_IB_SuspendTest         SuspendTest;
        S_IB_StopTest            StopTest;
        S_IB_ContinueTest        ContinueTest;
        S_IB_ReqTestData         ReqTestData;
        S_IB_ReqTestDataResult   ReqTestDataResult;

    };
    tag_IB_Packet(){
        memset(this, 0, sizeof(tag_IB_Packet));
    };
}tag_IB_Packet;

typedef struct tag_IC_Packet{
    DWORD HeadTag;  //=0xeffffffe
    DWORD SrcCode;  //源地址
    DWORD DesCode;  //目的地址
    DWORD PackType; //包类型
    DWORD DesGrp;   //目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组

    DWORD SerialNo;   //序列号             
    union{
    };
    tag_IC_Packet(){
        memset(this, 0, sizeof(tag_IC_Packet));
    };
}tag_IC_Packet;

typedef struct tag_ID_Packet{
    DWORD HeadTag;  //=0xeffffffe
    DWORD SrcCode;  //源地址
    DWORD DesCode;  //目的地址
    DWORD PackType; //包类型
    DWORD DesGrp;   //目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组

    DWORD SerialNo;   //序列号             
    union{
        S_ID_RegTestMachine      RegTestMachine;
        S_ID_ResetTestMachine    ResetTestMachine;
        S_ID_SynTestMachineInfo  SynTestMachineInfo;
        S_ID_StartTestPlan       StartTestPlan;
        S_ID_PauseTestPlan       PauseTestPlan;
        S_ID_SuspendTestPlan     SuspendTestPlan;
        S_ID_ContinueTestPlan    ContinueTestPlan;
        S_ID_StopTestPlan        StopTestPlan;
        S_ID_ReqMonitor          ReqMonitor;
        S_ID_ReqMonitorResult    ReqMonitorResult;
        S_ID_SendMonitorData     SendMonitorData;

    };
    tag_ID_Packet(){
        memset(this, 0, sizeof(tag_ID_Packet));
    };
}tag_ID_Packet;

typedef struct {}  S_IE_ReqCtrlInfo;
typedef struct {}  S_IE_ReqCtrlInfoResult;
typedef struct {}  S_IE_StartTest;
typedef struct {}  S_IE_PauseTest;
typedef struct {}  S_IE_SuspendTest;
typedef struct {}  S_IE_StopTest;
typedef struct {}  S_IE_ContinueTest;
typedef struct {}  S_IE_ReqTestData;
typedef struct {}  S_IE_ReqTestDataResult;



typedef struct tag_IE_Packet{
    DWORD HeadTag;  //=0xeffffffe
    DWORD SrcCode;  //源地址
    DWORD DesCode;  //目的地址
    DWORD PackType; //包类型
    DWORD DesGrp;   //目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组

    DWORD SerialNo;   //序列号             
    union{

    };
    tag_IE_Packet(){
        memset(this, 0, sizeof(tag_IE_Packet));
    };
}tag_IE_Packet;



struct S_SocketPacket 
{
    short int m_head;
    short int m_len;
    unsigned char m_msg[MAX_MSG_LEN];
    S_SocketPacket ()
    {
        m_head = PACKET_HEAD;
        m_len = 0;
        memset(m_msg,0,sizeof(m_msg));
    }
};


struct S_RegNode{
	S_RegNode()
	{
		m_head = PACKET_HEAD;
		m_dir = -1;
		m_node = -1;
	}
	short int m_head;
	short int m_dir;
	short int m_node;
};


struct S_RegNodeAck{
#define REGRESULT_OK 0
	S_RegNodeAck()
	{
		m_head = PACKET_HEAD;
		m_result = -1;
	}
	short int m_head;
	short int m_result;
};


#pragma pack()

#endif//__PACKET_H__


