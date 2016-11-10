#pragma once

#ifndef  __PACKET_H__
#define __PACKET_H__

#pragma  pack(1)

#define MAX_MSG_LEN 1500
#define COMM_CONNECTED  1
#define COMM_BROKEN		0
#define MAX_FILENAME_LENGTH 256

const short int RECV = 1<<8;
const short int SEND = 2<<8;
const short int PACKET_HEAD=0x7FFE;

enum PACKET_TYPE
{
	T_ACRoute	 = 1       ,
		T_ACSilent	        ,
		T_ACInitSys	        ,
		T_ACHalt	            ,
		T_ACPlay	            ,
		T_ACRec	            ,
		T_ACStopRp	        ,
		T_ACDial	            ,
		T_ACDialChannel	    ,
		T_ACDialResult	    ,
		T_ACRelease	        ,
		T_ACGetCaller	    ,
		T_ACGetCalled	    ,
		T_ACGetDtmf	        ,
		T_ACPop	            ,
		T_ACPush	            ,
		T_ACAllocRes	        ,
		T_ACDeAllocRes	    ,
		T_ACChannelStatus	,
		T_ACChannelInfo	    ,
		T_ACGetRes	        ,
		T_ACWaitCall	        ,
		T_ACAcceptCall	    ,
		T_ACAnswerCall	    ,
		T_ACWaitDialChan	    ,
		T_ACWaitDialResult	,
		T_ACRecvDtmf	        ,
		T_ACRpStatus	        ,
		T_ACRes	            ,
		T_ACFaxStatus	    ,
		T_ACMeetStatus	    ,
		T_AC_TEST_PACKET ,
		
};


enum E_CALL_RESULT{	
    E_OK = 0,        
        E_CALL_BUSY,    //对方忙
        E_CALL_VACANT,  //空号
        E_CALL_FAULT,   //呼叫故障
        E_CALL_RING,    //对方振铃
        E_CALL_EMPTYMSG,//没有消息
        E_CALL_NO_ACK,  //久叫不应
        E_CALL_ACK,     //
        E_CALL_TALK,    
        E_CALL_LRING,
        E_CALL_PROCEDING,
        E_CALL_IDLE,
        E_CALL_NOIDLELINE,
        E_DEV_NOT_REG,
        E_DEV_NOT_EXE,
        E_DEV_FAULT,
};


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


struct S_AC_TEST_PACKET 
{
#define TEST_PACK_LEN 100
	char m_testdata[TEST_PACK_LEN];
};


struct S_ACRoute	           // 交换                      
{
	int ch1;
	int ch2;
	int mode;
};

struct S_ACSilent	           // 断开连接                  
{
	int lch;
};

struct S_ACInitSys	           // 初始化                   
{};
struct S_ACHalt	               // 停机                      
{};

struct S_ACPlay	               // 放音                      
{
	int lch;
	char filename[MAX_FILENAME_LENGTH];
	int mode;
};

struct S_ACRec	               // 录音                      
{
	int lch;
	char recfile[MAX_FILENAME_LENGTH];
};

struct S_ACStopRp	           // 停止录放                  
{
	int lch;
};

struct S_ACDial	               // 呼出                     
{
	int lch;
	char called[32];
	char caller[32];
	int cid;
};


struct S_ACDialChannel	       // 呼出分配通道             
{
	int cid;
	int lch;
};


struct S_ACDialResult	       // 呼叫结果                 
{
	int cid;
    int lch;
	int result;
    int charge;
};

struct S_ACRelease	           // 释放呼叫                 
{
	int lch;
    int result;
};

struct S_ACGetCaller	       // 取主叫                   
{
	int lch;
};

struct S_ACGetCalled	       // 取被叫                   
{
	int lch;
};

struct S_ACGetDtmf	           // 接收DTMF                  
{
	int lch;
};

struct S_ACPop	               // 弹出                      
{};
struct S_ACPush	               // 压入                      
{};

struct S_ACAllocRes	           // 分配资源                  
{
	int lch;
	unsigned long type;
};

struct S_ACDeAllocRes	       // 释放资源                  
{
	int lch;
	unsigned long type;
};

struct S_ACChannelStatus	   // 通道状态                  
{
	int lch;
	int status;
};

struct S_ACChannelInfo	       // 通道信息                  
{
	int lch;
	//	struct info
};

struct S_ACGetRes	           // 获取资源服务信息          
{
	int type;
};

struct S_ACWaitCall	           // 呼入                      
{
	int lch;//通道
	char caller[32];
	char called[32];
	char origcalled[32];
	int type;
	
};
struct S_ACAcceptCall	       // 回振铃                    
{
	int lch;
};          

struct S_ACAnswerCall	       // 回摘机                    
{
	int lch;
	int type;
};  

struct S_ACWaitDialChan	       // 呼出分配到通道            
{
	int cid;
	int lch;
};                  

struct S_ACWaitDialResult	   // 呼叫结果                  
{
	int cid;
	int result;
};             

struct S_ACRecvDtmf	           // 收到DTMF                  
{
	int lch;
	char dtmf;
};            

struct S_ACRpStatus	           // 录放音状态                
{
	int lch;
	int status;
};             

struct S_ACRes	                // 资源状态                 
{
	int type;
	int total;
	int residue;
};

struct S_ACFaxStatus	            // 传真状态             
{
	int lch;
};

struct S_ACMeetStatus	        // 会议状态                 
{
	int roomid;
	int status;
};


struct S_MessagePacket{
#define MSG_HEADLEN sizeof(m_msgtype)+sizeof(m_msglen)
	S_MessagePacket()
	{	
		m_msgtype = -1;
		m_msglen  = -1;
		memset((void *)&m_Msg,0,sizeof(S_MESSAGE));
	}		
	short int m_msgtype;
	short int m_msglen;
	union S_MESSAGE{
		S_ACRoute	                m_ACRoute	                ;                 
		S_ACSilent	                m_ACSilent	                ;                 
		S_ACInitSys	                m_ACInitSys	                ;                          
		S_ACHalt	                m_ACHalt	                ;                          
		S_ACPlay	                m_ACPlay	                ;                          
		S_ACRec	                    m_ACRec	                    ;
		S_ACStopRp	                m_ACStopRp	                ;
		S_ACDial	                m_ACDial	                ;
		S_ACDialChannel	            m_ACDialChannel	            ;
		S_ACDialResult	            m_ACDialResult	            ;
		S_ACRelease	                m_ACRelease	                ;
		S_ACGetCaller	            m_ACGetCaller	            ;
		S_ACGetCalled	            m_ACGetCalled	            ;
		S_ACGetDtmf	                m_ACGetDtmf	                ;
		S_ACPop	                    m_ACPop	                    ;
		S_ACPush	                m_ACPush	                ;
		S_ACAllocRes	            m_ACAllocRes	            ;
		S_ACDeAllocRes	            m_ACDeAllocRes	            ;
		S_ACChannelStatus	        m_ACChannelStatus	        ;
		S_ACChannelInfo	            m_ACChannelInfo	            ;
		S_ACGetRes	                m_ACGetRes	                ;
		S_ACWaitCall	            m_ACWaitCall	            ;
		S_ACAcceptCall	            m_ACAcceptCall	            ;
		S_ACAnswerCall	            m_ACAnswerCall	            ;
		S_ACWaitDialChan	        m_ACWaitDialChan	        ;
		S_ACWaitDialResult	        m_ACWaitDialResult	        ;
		S_ACRecvDtmf	            m_ACRecvDtmf	            ;
		S_ACRpStatus	            m_ACRpStatus	            ;
		S_ACRes	                    m_ACRes	                    ;
		S_ACFaxStatus	            m_ACFaxStatus	            ;
		S_ACMeetStatus	            m_ACMeetStatus	            ;		
		S_AC_TEST_PACKET			m_AC_TEST_PACKET			;
	}m_Msg;
	
	int Init(int msgtype)
	{
		memset((void *)&m_Msg,0,sizeof(m_Msg));
        m_msgtype = msgtype;
		switch (msgtype)
		{
        case T_ACRoute	        :m_msglen=sizeof(S_ACRoute	           );return m_msglen+MSG_HEADLEN;
        case T_ACSilent	        :m_msglen=sizeof(S_ACSilent	       );    return m_msglen+MSG_HEADLEN;
        case T_ACInitSys	    :m_msglen=sizeof(S_ACInitSys	       );return m_msglen+MSG_HEADLEN;
        case T_ACHalt	        :m_msglen=sizeof(S_ACHalt	           );return m_msglen+MSG_HEADLEN;
        case T_ACPlay	        :m_msglen=sizeof(S_ACPlay	           );return m_msglen+MSG_HEADLEN;
        case T_ACRec	        :m_msglen=sizeof(S_ACRec	           );return m_msglen+MSG_HEADLEN;
        case T_ACStopRp	        :m_msglen=sizeof(S_ACStopRp	       );    return m_msglen+MSG_HEADLEN;
        case T_ACDial	        :m_msglen=sizeof(S_ACDial	           );return m_msglen+MSG_HEADLEN;
        case T_ACDialChannel	:m_msglen=sizeof(S_ACDialChannel	   );return m_msglen+MSG_HEADLEN;
        case T_ACDialResult	    :m_msglen=sizeof(S_ACDialResult	   );    return m_msglen+MSG_HEADLEN;
        case T_ACRelease	    :m_msglen=sizeof(S_ACRelease	       );return m_msglen+MSG_HEADLEN;
        case T_ACGetCaller	    :m_msglen=sizeof(S_ACGetCaller	       );return m_msglen+MSG_HEADLEN;
        case T_ACGetCalled	    :m_msglen=sizeof(S_ACGetCalled	       );return m_msglen+MSG_HEADLEN;
        case T_ACGetDtmf	    :m_msglen=sizeof(S_ACGetDtmf	       );return m_msglen+MSG_HEADLEN;
        case T_ACPop	        :m_msglen=sizeof(S_ACPop	           );return m_msglen+MSG_HEADLEN;
        case T_ACPush	        :m_msglen=sizeof(S_ACPush	           );return m_msglen+MSG_HEADLEN;
        case T_ACAllocRes	    :m_msglen=sizeof(S_ACAllocRes	       );return m_msglen+MSG_HEADLEN;
        case T_ACDeAllocRes	    :m_msglen=sizeof(S_ACDeAllocRes	   );    return m_msglen+MSG_HEADLEN;
        case T_ACChannelStatus	:m_msglen=sizeof(S_ACChannelStatus	   );return m_msglen+MSG_HEADLEN;
        case T_ACChannelInfo	:m_msglen=sizeof(S_ACChannelInfo	   );return m_msglen+MSG_HEADLEN;
        case T_ACGetRes	        :m_msglen=sizeof(S_ACGetRes	       );    return m_msglen+MSG_HEADLEN;
        case T_ACWaitCall	    :m_msglen=sizeof(S_ACWaitCall	       );return m_msglen+MSG_HEADLEN;
        case T_ACAcceptCall	    :m_msglen=sizeof(S_ACAcceptCall	   );    return m_msglen+MSG_HEADLEN;
        case T_ACAnswerCall	    :m_msglen=sizeof(S_ACAnswerCall	   );    return m_msglen+MSG_HEADLEN;
        case T_ACWaitDialChan	:m_msglen=sizeof(S_ACWaitDialChan	   );return m_msglen+MSG_HEADLEN;
        case T_ACWaitDialResult	:m_msglen=sizeof(S_ACWaitDialResult   ); return m_msglen+MSG_HEADLEN;
        case T_ACRecvDtmf	    :m_msglen=sizeof(S_ACRecvDtmf	       );return m_msglen+MSG_HEADLEN;
        case T_ACRpStatus	    :m_msglen=sizeof(S_ACRpStatus	       );return m_msglen+MSG_HEADLEN;
        case T_ACRes	        :m_msglen=sizeof(S_ACRes	           );return m_msglen+MSG_HEADLEN;
        case T_ACFaxStatus	    :m_msglen=sizeof(S_ACFaxStatus	       );return m_msglen+MSG_HEADLEN;
        case T_ACMeetStatus	    :m_msglen=sizeof(S_ACMeetStatus	   );    return m_msglen+MSG_HEADLEN;
        case T_AC_TEST_PACKET   :m_msglen=sizeof(S_AC_TEST_PACKET  );    return m_msglen+MSG_HEADLEN;
        default:return MSG_HEADLEN;
        }
        return MSG_HEADLEN;
	}

    char *OutputTypeString()
    {
        switch (m_msgtype)
        {
        case T_ACRoute	        :return(" T_ACRoute	           ");
        case T_ACSilent	        :return(" T_ACSilent	       ");
        case T_ACInitSys	    :return(" T_ACInitSys	       ");
        case T_ACHalt	        :return(" T_ACHalt	           ");
        case T_ACPlay	        :return(" T_ACPlay	           ");
        case T_ACRec	        :return(" T_ACRec	           ");
        case T_ACStopRp	        :return(" T_ACStopRp	       ");
        case T_ACDial	        :return(" T_ACDial	           ");
        case T_ACDialChannel	:return(" T_ACDialChannel	   ");
        case T_ACDialResult	    :return(" T_ACDialResult	   ");
        case T_ACRelease	    :return(" T_ACRelease	       ");
        case T_ACGetCaller	    :return(" T_ACGetCaller	       ");
        case T_ACGetCalled	    :return(" T_ACGetCalled	       ");
        case T_ACGetDtmf	    :return(" T_ACGetDtmf	       ");
        case T_ACPop	        :return(" T_ACPop	           ");
        case T_ACPush	        :return(" T_ACPush	           ");
        case T_ACAllocRes	    :return(" T_ACAllocRes	       ");
        case T_ACDeAllocRes	    :return(" T_ACDeAllocRes	   ");
        case T_ACChannelStatus	:return(" T_ACChannelStatus	   ");
        case T_ACChannelInfo	:return(" T_ACChannelInfo	   ");
        case T_ACGetRes	        :return(" T_ACGetRes	       ");
        case T_ACWaitCall	    :return(" T_ACWaitCall	       ");
        case T_ACAcceptCall	    :return(" T_ACAcceptCall	   ");
        case T_ACAnswerCall	    :return(" T_ACAnswerCall	   ");
        case T_ACWaitDialChan	:return(" T_ACWaitDialChan	   ");
        case T_ACWaitDialResult	:return(" T_ACWaitDialResult   ");
        case T_ACRecvDtmf	    :return(" T_ACRecvDtmf	       ");
        case T_ACRpStatus	    :return(" T_ACRpStatus	       ");
        case T_ACRes	        :return(" T_ACRes	           ");
        case T_ACFaxStatus	    :return(" T_ACFaxStatus	       ");
        case T_ACMeetStatus	    :return(" T_ACMeetStatus	   ");
        case T_AC_TEST_PACKET   :return(" T_AC_TEST_PACKET     ");
        }
        return NULL;
    }
};

#ifdef xxxxx

char *OutputTypeString(S_MessagePacket *msgpack)
{
	switch (msgpack->m_msgtype)
	{
	case T_ACRoute	        :return(" T_ACRoute	           ");
	case T_ACSilent	        :return(" T_ACSilent	       ");
	case T_ACInitSys	    :return(" T_ACInitSys	       ");
	case T_ACHalt	        :return(" T_ACHalt	           ");
	case T_ACPlay	        :return(" T_ACPlay	           ");
	case T_ACRec	        :return(" T_ACRec	           ");
	case T_ACStopRp	        :return(" T_ACStopRp	       ");
	case T_ACDial	        :return(" T_ACDial	           ");
	case T_ACDialChannel	:return(" T_ACDialChannel	   ");
	case T_ACDialResult	    :return(" T_ACDialResult	   ");
	case T_ACRelease	    :return(" T_ACRelease	       ");
	case T_ACGetCaller	    :return(" T_ACGetCaller	       ");
	case T_ACGetCalled	    :return(" T_ACGetCalled	       ");
	case T_ACGetDtmf	    :return(" T_ACGetDtmf	       ");
	case T_ACPop	        :return(" T_ACPop	           ");
	case T_ACPush	        :return(" T_ACPush	           ");
	case T_ACAllocRes	    :return(" T_ACAllocRes	       ");
	case T_ACDeAllocRes	    :return(" T_ACDeAllocRes	   ");
	case T_ACChannelStatus	:return(" T_ACChannelStatus	   ");
	case T_ACChannelInfo	:return(" T_ACChannelInfo	   ");
	case T_ACGetRes	        :return(" T_ACGetRes	       ");
	case T_ACWaitCall	    :return(" T_ACWaitCall	       ");
	case T_ACAcceptCall	    :return(" T_ACAcceptCall	   ");
	case T_ACAnswerCall	    :return(" T_ACAnswerCall	   ");
	case T_ACWaitDialChan	:return(" T_ACWaitDialChan	   ");
	case T_ACWaitDialResult	:return(" T_ACWaitDialResult   ");
	case T_ACRecvDtmf	    :return(" T_ACRecvDtmf	       ");
	case T_ACRpStatus	    :return(" T_ACRpStatus	       ");
	case T_ACRes	        :return(" T_ACRes	           ");
	case T_ACFaxStatus	    :return(" T_ACFaxStatus	       ");
	case T_ACMeetStatus	    :return(" T_ACMeetStatus	   ");
	case T_AC_TEST_PACKET   :return(" T_AC_TEST_PACKET     ");
	}
	return NULL;
}
#endif

#pragma pack()

#endif//__PACKET_H__


