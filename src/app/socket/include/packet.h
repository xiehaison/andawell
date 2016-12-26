#pragma once

#ifndef  __PACKET_H__
#define __PACKET_H__

#pragma  pack(1)

#define MAX_MSG_LEN 1500
#define COMM_CONNECTED  1
#define COMM_BROKEN		0
#define MAX_FILENAME_LENGTH 256

#define IA_START 000
#define IB_START 1000
#define IC_START 2000
#define ID_START 3000
#define IE_START 4000

const BYTE REF_I    = 1;
const BYTE REF_F    = 2;
const BYTE REF_T    = 3;
const BYTE REF_S    = 4;
const BYTE CON_I    = 5;
const BYTE CON_F    = 6;
const BYTE CON_S    = 7;
const BYTE CON_T    = 8;
const BYTE CON_SYS  = 9;
const BYTE CON_EXP  = 10;


#define PARAM_IN   0
#define PARAM_OUT  1

const short int RECV = 1<<8;
const short int SEND = 2<<8;
const short int PACKET_HEAD=0x7FFE;


#define  PackName(a)  #a

#define	IC_BILL               68

typedef struct {
    WORD header;
    WORD msulen;
    void S_Packet_Header()
    {
        header = PACKET_HEAD;
        msulen = 0;
    }
}S_Packet_Header;


//数据库通讯代理使用数据包
enum{
    IC_NONE = IC_START,
    IC_PREPARESQL,
    IC_PREPARESQL_READY,
    IC_SETPARA,
    IC_SETPARA_READY,
    IC_SQLEXEC,
    IC_SQLEXEC_OK,
    IC_SQLEXEC_ERR,
    IC_SQLOPEN,
    IC_GETFIELD_REQ,
    IC_GETFIELD_VALUE,
    IC_GETFIELD_ERR,
    IC_EOF_REQ,
    IC_EOF_RES,
    IC_MOVENEXT,
    IC_MOVENEXT_RES,
    IC_GETPARAMOUT_REQ,
    IC_GETPARAMOUT_VALUE,
    IC_GETPARAMOUT_ERR,
    IC_COMPLETE,
    IC_DBCFG,                //数据库代理连接上来后的配置信息
    IC_PROXYINFO,
    IC_UPDATEFIELD,
    IC_UPDATEFIELD_RES,
    IC_CLOSE,
    IC_END,
};


inline char* GetDBPakName(int dbpak)
{
    switch (dbpak)
    {
    case IC_PREPARESQL_READY:		return "IC_PREPARESQL_READY";
    case IC_SETPARA_READY:			return "IC_SETPARA_READY";
    case IC_SQLEXEC_OK:				return "IC_SQLEXEC_OK";
    case IC_SQLEXEC_ERR:			return "IC_SQLEXEC_ERR";
    case IC_GETFIELD_VALUE:			return "IC_GETFIELD_VALUE";
    case IC_EOF_RES:				return "IC_EOF_RES";
    case IC_MOVENEXT_RES:			return "IC_MOVENEXT_RES";
    case IC_GETPARAMOUT_VALUE:		return "IC_GETPARAMOUT_VALUE";
    case IC_GETFIELD_ERR:			return "IC_GETFIELD_ERR";
    case IC_COMPLETE:				return "IC_COMPLETE";
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
    DWORD HeadTag;  //=0xeffffffe
    DWORD PackType; //包类型
    DWORD SerialNo;   //序列号             

    DWORD SrcCode;  //源地址
    DWORD DesCode;  //目的地址
    DWORD DesGrp;   //目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组

}S_Msg_Header;

typedef struct{
    DWORD HeadFlag;
    DWORD PackType;
    DWORD SerialNo;

    DWORD SrcCode;  //源地址
    DWORD DesCode;  //目的地址
    DWORD DesGrp;   //目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组
    //union{
    //    S_Msg_Header Header;
    //    DWORD HeadFlag;
    //    DWORD PackType;
    //    DWORD SerialNo;

    //    DWORD SrcCode;  //源地址
    //    DWORD DesCode;  //目的地址
    //    DWORD DesGrp;   //目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组

    //};

    int chan;
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
    IA_Login = IA_START,
    IA_LoginResult,
    IA_ReqServerInfo,
    IA_ReqServerInfoResult,
    IA_ReqTestMachineInfo,
    IA_ReqTestMachineInfoResult,
    IA_ReqMonitor,
    IA_ReqMonitorResult,
    IA_TestString,
    IA_END
};


typedef struct {
    char username[50];
    char password[50];
    BYTE usertype;
}S_IA_Login;

typedef struct {
    enum{
        E_LOGIN_OK,
        E_LOGIN_PASSWORD_ERROR,
        E_LOGIN_NOUSER,
    };
    BYTE loginresult;
}S_IA_LoginResult;


typedef struct {

}S_IA_ReqServerInfo;
typedef struct {}S_IA_ReqServerInfoResult;
typedef struct {}S_IA_ReqTestMachineInfo;
typedef struct {}S_IA_ReqTestMachineInfoResult;

enum{
	E_STOP_MONITOR,
	E_START_MONITOR,
};

typedef struct {
    int rnode;
    int userid;
    int node;
	int type;
	int datatype;
	DWORD time;
}S_IA_ReqMonitor;

typedef struct {
    enum{
        E_MONITOR_YES,
        E_MONITOR_NO,
    };
    DWORD result;
}S_IA_ReqMonitorResult;

typedef struct {
    BYTE str[101];
}S_IA_TestString;


typedef struct tag_IA_Packet{
    DWORD HeadTag;  //=0xeffffffe
    DWORD PackType; //包类型
    DWORD SerialNo;   //序列号             

    DWORD SrcCode;  //源地址
    DWORD DesCode;  //目的地址
    DWORD DesGrp;   //目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组

    union{
        S_IA_Login                      Login;
        S_IA_LoginResult                LoginResult;
        S_IA_ReqServerInfo              ReqServerInfo;
        S_IA_ReqServerInfoResult        ReqServerInfoResult;
        S_IA_ReqTestMachineInfo         ReqTestMachineInfo;
        S_IA_ReqTestMachineInfoResult   ReqTestMachineInfoResult;
        S_IA_ReqMonitor                 ReqMonitor;
        S_IA_ReqMonitorResult           ReqMonitorResult;
        S_IA_TestString                 TestString;
    };
    tag_IA_Packet(){
        memset(this, 0, sizeof(tag_IA_Packet));
        HeadTag = 0xeffffffe;

    };
}tag_IA_Packet;


enum{
    IB_ReqCtrlInfo = IB_START,
    IB_ReqCtrlInfoResult,
    IB_StartTest,
    IB_PauseTest,
    IB_SuspendTest,
    IB_StopTest,
    IB_ContinueTest,
    IB_ReqTestData,
    IB_ReqTestDataResult,
    IB_END,
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
    IE_ReqCtrlInfo = IE_START,
    IE_ReqCtrlInfoResult,
    IE_StartTest,
    IE_PauseTest,
    IE_SuspendTest,
    IE_StopTest,
    IE_ContinueTest,
    IE_ReqTestData,
    IE_ReqTestDataResult,
    IE_END
};



typedef struct tag_IB_Packet{
    DWORD HeadTag;  //=0xeffffffe
    DWORD PackType; //包类型
    DWORD SerialNo;   //序列号             

    DWORD SrcCode;  //源地址
    DWORD DesCode;  //目的地址
    DWORD DesGrp;   //目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组

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
    DWORD PackType; //包类型
    DWORD SerialNo;   //序列号             

    DWORD SrcCode;  //源地址
    DWORD DesCode;  //目的地址
    DWORD DesGrp;   //目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组

    union{
    };
    tag_IC_Packet(){
        memset(this, 0, sizeof(tag_IC_Packet));
        HeadTag = 0xeffffffe;

    };
}tag_IC_Packet;


enum{
    ID_RegTestMachine = ID_START,
    ID_RegTestMachineResult,
    ID_ResetTestMachine,
    ID_ResetTestMachineResult,
    ID_SynTestMachineInfo,
    ID_SynTestMachineInfoResult,
    ID_StartTestPlan,
    ID_StartTestPlanResult,
    ID_PauseTestPlan,
    ID_PauseTestPlanResult,
    ID_SuspendTestPlan,
    ID_SuspendTestPlanResult,
    ID_ContinueTestPlan,
    ID_ContinueTestPlanResult,
    ID_StopTestPlan,
    ID_StopTestPlanResult,
    ID_ProgressPlan,
    ID_ProgressPlanResult,
    ID_ReqMonitor,
    ID_ReqMonitorResult,
    ID_ReqMonitorData,
    ID_ReqMonitorDataResult,
    ID_END,
};

typedef struct {
    DWORD node;
}    S_ID_RegTestMachine;


typedef struct {
    DWORD node;
    DWORD result;
}    S_ID_RegTestMachineResult;

typedef struct {}    S_ID_ResetTestMachine;
typedef struct {}    S_ID_SynTestMachineInfo;
typedef struct {
    char  projname[50]; //项目名
    char  planname[50]; //计划名
    int   sn;           //编号
    DWORD start_time;   //启动时间--1970开始后的秒数
    DWORD start_user;   //操作者
    DWORD node;         //启动节点

}    S_ID_StartTestPlan;

typedef struct {
    char  projname[50]; //项目名
    char  planname[50]; //计划名
    int   sn;           //编号
    DWORD time;   //时间--1970开始后的秒数
    DWORD user;   //操作者
    DWORD node;         //操作节点
}    S_ID_PauseTestPlan;

typedef struct {
    char  projname[50]; //项目名
    char  planname[50]; //计划名
    int   sn;           //编号
    DWORD time;   //时间--1970开始后的秒数
    DWORD user;   //操作者
    DWORD node;         //操作节点

}    S_ID_SuspendTestPlan;

typedef struct {
    char  projname[50]; //项目名
    char  planname[50]; //计划名
    int   sn;           //编号
    DWORD time;   //时间--1970开始后的秒数
    DWORD user;   //操作者
    DWORD node;         //操作节点

}    S_ID_ContinueTestPlan;


typedef struct {
    char  projname[50]; //项目名
    char  planname[50]; //计划名
    int   sn;           //编号
    DWORD time;   //时间--1970开始后的秒数
    DWORD user;   //操作者
    DWORD node;         //操作节点

}S_ID_StopTestPlan;


typedef struct {}    S_ID_ResetTestMachineResult;
typedef struct {}    S_ID_SynTestMachineInfoResult;
typedef struct {}    S_ID_StartTestPlanResult;
typedef struct {}    S_ID_PauseTestPlanResult;
typedef struct {}    S_ID_SuspendTestPlanResult;
typedef struct {}    S_ID_ContinueTestPlanResult;
typedef struct {}    S_ID_StopTestPlanResult;
typedef struct {
    int progress;
    int   sn;           //编号
    DWORD time;   //时间--1970开始后的秒数

}    S_ID_ProgressPlan;

typedef struct {}    S_ID_ProgressPlanResult;


typedef struct {
}    S_ID_ReqMonitor;

//0:不允许监控
//1:允许监控

typedef struct {
    enum{
        E_Monitor_No = 0,
        E_Monitor_Yes,
    };
    BYTE  result;		//是否允许监控
	DWORD   projno;		//项目编号
	DWORD   data_type;  //数据类型
	//DWORD　　　
}   S_ID_ReqMonitorResult;


enum{
    E_Emulate_Data_Type1,
    E_Emulate_Data_Type2,
    E_Emulate_Data_Type3,
    E_Emulate_Data_Type4,
    E_Emulate_Data_Type5,
};

typedef struct {
    DWORD type;
}    S_ID_ReqMonitorData;


struct S_Emulate_Data_Type1
{
    DWORD   time[10];     //测试时间  --从1970年开始的秒数
    DWORD   msec[10];     //测试时间毫秒数 
    double  value[10];    //采样数值
};

struct S_Emulate_Data_Type2
{
    DWORD   time[10];     //测试时间  --从1970年开始的秒数
    DWORD   msec[10];     //测试时间毫秒数 
    double  value[2][10];    //采样数值
};

struct S_Emulate_Data_Type3
{
    DWORD   time[10];     //测试时间  --从1970年开始的秒数
    DWORD   msec[10];     //测试时间毫秒数 
    double  value[3][10];    //采样数值
};

struct S_Emulate_Data_Type4
{
    DWORD   time[10];     //测试时间  --从1970年开始的秒数
    DWORD   msec[10];     //测试时间毫秒数 
    double  value_x[10];    //采样数值
    DWORD   value_y[10];    //采样数值
};

struct S_Emulate_Data_Type5
{
    DWORD   time[10];     //测试时间  --从1970年开始的秒数
    DWORD   msec[10];     //测试时间毫秒数 
    double  value_x[10];    //采样数值
    BYTE    value_y[10];    //采样数值
};


union S_Emulate_Data
{
    S_Emulate_Data_Type1 emu_data_type1;
    S_Emulate_Data_Type2 emu_data_type2;
    S_Emulate_Data_Type3 emu_data_type3;
    S_Emulate_Data_Type4 emu_data_type4;
    S_Emulate_Data_Type5 emu_data_type5;
};

typedef struct {
    //ID_ReqMonitorDataResult
    DWORD type;
    DWORD count;           //数据个数  
    union S_Emulate_Data Emulate_Data;
}    S_ID_ReqMonitorDataResult;


typedef struct tag_ID_Packet{

    DWORD HeadTag;  //=0xeffffffe
    DWORD PackType; //包类型
    DWORD SerialNo;   //序列号             

    DWORD SrcCode;  //源地址
    DWORD DesCode;  //目的地址
    DWORD DesGrp;   //目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组

    union{
        S_ID_RegTestMachine         RegTestMachine;
        S_ID_ResetTestMachine       ResetTestMachine;
        S_ID_SynTestMachineInfo     SynTestMachineInfo;
        S_ID_StartTestPlan          StartTestPlan;
        S_ID_PauseTestPlan          PauseTestPlan;
        S_ID_SuspendTestPlan        SuspendTestPlan;
        S_ID_ContinueTestPlan       ContinueTestPlan;
        S_ID_StopTestPlan           StopTestPlan;
        S_ID_ProgressPlan           ProgressPlan;

        S_ID_RegTestMachineResult         RegTestMachineResult;
        S_ID_ResetTestMachineResult       ResetTestMachineResult;
        S_ID_SynTestMachineInfoResult     SynTestMachineInfoResult;
        S_ID_StartTestPlanResult          StartTestPlanResult;
        S_ID_PauseTestPlanResult          PauseTestPlanResult;
        S_ID_SuspendTestPlanResult        SuspendTestPlanResult;
        S_ID_ContinueTestPlanResult       ContinueTestPlanResult;
        S_ID_StopTestPlanResult           StopTestPlanResult;
        S_ID_ProgressPlanResult           ProgressPlanResult;

        S_ID_ReqMonitor             ReqMonitor;
        S_ID_ReqMonitorResult       ReqMonitorResult;
        S_ID_ReqMonitorData         ReqMonitorData;
        S_ID_ReqMonitorDataResult   ReqMonitorDataResult;

    };
    tag_ID_Packet(){
        memset(this, 0, sizeof(tag_ID_Packet));
        HeadTag = 0xeffffffe;
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
        HeadTag = 0xeffffffe;

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
		m_node = -1;
	}
	short int m_head;
	short int m_node;
};

struct S_HeartBeat{
    S_HeartBeat()
    {
        m_head = PACKET_HEAD;
        m_node = -1;
        m_heartbeat = 0;
    }
    short int m_head;
    short int m_node;
    DWORD m_heartbeat;
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

#define GetMsgSrc(msg)  (((S_Msg_Header *)msg)->SrcCode)
#define GetMsgType(msg) (((S_Msg_Header *)msg)->PackType)
#define GetMsgDst(msg)  (((S_Msg_Header *)msg)->DesCode)
#define GetMsgSN(msg)   (((S_Msg_Header *)msg)->SerialNo)

char *GetMsgTypeStr(DWORD type);

#pragma pack()

#endif//__PACKET_H__


