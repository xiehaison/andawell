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

#define	IC_BILL               68


//���ݿ�ͨѶ����ʹ�����ݰ�
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

    IC_DBCFG,                //���ݿ���������������������Ϣ
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
    case IC_PREPARESQL_READY:return "IC_PREPARESQL_READY";
    case IC_SETPARA_READY:return "IC_SETPARA_READY";
    case IC_SQLEXEC_OK:return "IC_SQLEXEC_OK";
    case IC_SQLEXEC_ERR:return "IC_SQLEXEC_ERR";
    case IC_GETFIELD_VALUE:return "IC_GETFIELD_VALUE";
    case IC_EOF_RES:return "IC_EOF_RES";
    case IC_MOVENEXT_RES:return "IC_MOVENEXT_RES";
    case IC_GETPARAMOUT_VALUE:return "IC_GETPARAMOUT_VALUE";
    case IC_GETFIELD_ERR:return "IC_GETFIELD_ERR";
    case IC_COMPLETE:return "IC_COMPLETE";
    default:return "NoName";
    }
}


typedef struct{
    int total;//���ݿ��������
    int no;//���ݿ������
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
    union{       //����ֵ
        DWORD  ICon;
        double FCon;
        char   TCon[14];
        char   SCon[256];
    };
}Req_UpdateField;

//EOF����
typedef struct{
    DWORD MoveBy;
}Req_EOF;

typedef struct{
    DWORD ICon;//EOF���,1-����ĩβ,0-û��
}Ret_EOF;

//GetParamOut���ݰ�
typedef struct{
    BYTE vType;//�ֶ�����
    BYTE FieldInd;//�ֶ�����
}Req_GetParamOut;
typedef struct{
    BYTE vType;//�ֶ�����
    BYTE FieldInd;//�ֶ�����
    union{       //����ֵ
        DWORD  ICon;
        double FCon;
        char   TCon[14];
        char   SCon[256];
    };
}Ret_GetParamOut;

//SetPara���ݰ�
typedef struct{
    BYTE vType;
    BYTE InOut;
    BYTE FieldInd;
    union{       //����ֵ
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
    int res;//�������,1-ok,0-fail;
}Ret_SetDB;

//GetField���ݰ�
typedef struct{
    BYTE vType;//�ֶ�����
    BYTE FieldInd;//�ֶ�����
}Req_GetField;

typedef struct{
    BYTE vType;//�ֶ�����
    BYTE FieldInd;//�ֶ�����
    union{       //����ֵ
        DWORD  ICon;
        double FCon;
        char   TCon[14];
        char   SCon[256];
    };
}Ret_GetField;


typedef struct{
    DWORD HeadTag;  //=0xeffffffe
    DWORD PackType; //������
    DWORD SerialNo;   //���к�             
}S_Msg_Header;

typedef struct{
    DWORD HeadFlag;
    DWORD PackType;
    DWORD SerialNo;

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
typedef struct {}S_IA_ReqMonitor;
typedef struct {}S_IA_ReqMonitorResult;


typedef struct tag_IA_Packet{
    DWORD HeadTag;  //=0xeffffffe
    DWORD PackType; //������
    DWORD SerialNo;   //���к�             

    DWORD SrcCode;  //Դ��ַ
    DWORD DesCode;  //Ŀ�ĵ�ַ
    DWORD DesGrp;   //Ŀ�ķ������,0-����ָ��DesCode,0xffffffff-���͵����нڵ�,����-ָ������

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
    DWORD PackType; //������
    DWORD SerialNo;   //���к�             

    DWORD SrcCode;  //Դ��ַ
    DWORD DesCode;  //Ŀ�ĵ�ַ
    DWORD DesGrp;   //Ŀ�ķ������,0-����ָ��DesCode,0xffffffff-���͵����нڵ�,����-ָ������

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
    DWORD PackType; //������
    DWORD SerialNo;   //���к�             

    DWORD SrcCode;  //Դ��ַ
    DWORD DesCode;  //Ŀ�ĵ�ַ
    DWORD DesGrp;   //Ŀ�ķ������,0-����ָ��DesCode,0xffffffff-���͵����нڵ�,����-ָ������

    union{
    };
    tag_IC_Packet(){
        memset(this, 0, sizeof(tag_IC_Packet));
    };
}tag_IC_Packet;


enum{

    ID_RegTestMachine = ID_START,
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
    ID_END,

};

typedef struct {}    S_ID_RegTestMachine;
typedef struct {}    S_ID_ResetTestMachine;
typedef struct {}    S_ID_SynTestMachineInfo;
typedef struct {}    S_ID_StartTestPlan;
typedef struct {}    S_ID_PauseTestPlan;
typedef struct {}    S_ID_SuspendTestPlan;
typedef struct {}    S_ID_ContinueTestPlan;
typedef struct {}    S_ID_StopTestPlan;
typedef struct {
    int type;
    int data;
}    S_ID_ReqMonitor;
typedef struct {}    S_ID_ReqMonitorResult;
typedef struct {}    S_ID_SendMonitorData;


typedef struct tag_ID_Packet{
    //union{
    //    S_Msg_Header header;
    //    DWORD HeadTag;  //=0xeffffffe
    //    DWORD PackType; //������
    //    DWORD SerialNo;   //���к�             
    //};

    DWORD HeadTag;  //=0xeffffffe
    DWORD PackType; //������
    DWORD SerialNo;   //���к�             

    DWORD SrcCode;  //Դ��ַ
    DWORD DesCode;  //Ŀ�ĵ�ַ
    DWORD DesGrp;   //Ŀ�ķ������,0-����ָ��DesCode,0xffffffff-���͵����нڵ�,����-ָ������

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
    DWORD SrcCode;  //Դ��ַ
    DWORD DesCode;  //Ŀ�ĵ�ַ
    DWORD PackType; //������
    DWORD DesGrp;   //Ŀ�ķ������,0-����ָ��DesCode,0xffffffff-���͵����нڵ�,����-ָ������

    DWORD SerialNo;   //���к�             
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


