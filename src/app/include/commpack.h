#ifndef _commpack_h_
#define _commpack_h_

#include <list>
#include <windows.h>
#include <time.h>
#include "basedef.h"

using namespace std;
//AAA计费节点机器编号
#define CODE_AAA    103
#define CODE_AUTOCALLOUT 104
#define	CODE_SYSMON 105

#define BROADALL  9999

//自动外呼结果
enum{
	AC_NO_IDLELINE,    //没有空闲外线
	AC_NO_IDLE_SEAT,   //没有空闲的呼出座席
	AC_SEAT_INTERUPT,  //呼叫过程中中断
	AC_TALK_INTERUPT   //谈话过程中按键中断
};


//消息类型
enum{
	MT_INOUT     = 1,   //呼入呼出消息
	MT_IVRLOG    = 1<<1,   //ivr流程消息
	MT_IVROK     = 1<<2,   //ivr流程正常运行消息
	MT_IVRERR    = 1<<3,   //ivr流程运行错误消息
	MT_SYSLOG    = 1<<4,  //系统需要输出到核心服务器界面的消息,受界面本地监控控制
	MT_NOTIME    = 1<<5,   //不显示时间,不受本地监控控制
	MT_SPEC      = 1<<6,
	MT_DBPAK     = 1<<7    //数据库交互包
};
//会议音量大小
#define   VOL_HIGH    0X1200
#define   VOL_NORMAL  0X800
#define   VOL_LOW     0X400
#define   VOL_SILENT  0

//计费包的最大分段数量
#define MAX_SECS  8

#define MAX_DATA_SIZE 2048

#define STREAM_BLOCK 1024

#define TIME_ALIVE 4000

#define DATA_SOCK_RECV   0  //数据SOCKET
#define DATA_SOCK_SEND   1
#define STREAM_SOCK      2  //流SOCKET

//通讯节点类型
#define CT_IVREXEC     0  //系统IVR解释器
#define CT_SEATIN      1  //内线座席
#define CT_SUPERSEAT   2  //管理座席

//通讯中心是使用的数据包数据包类型
enum{
 MSG_COMM_LOGIN        ,  //通讯节点登录    
 MSG_COMM_ALIVE        ,  //通讯节点心跳信息
 MSG_COMM_LOGINRES     ,  //通讯节点登录结果
 MSG_COMM_NOTIFY       ,  //通讯节点连接

 MSG_IVRKERN_DISCONN   ,   //IVR核心服务器断开连接
 MSG_SEAT_DISCONN      ,   //座席台断开连接

 MSG_IVRDATA           ,  //IVR流程数据
 MSG_OP_RES            ,  //操作结果
//--会议包--
 MSG_MEET_GETROOM      ,   //获取房间信息
 MSG_MEET_ROOMINFO     ,   //10房间信息
 MSG_MEET_MEMBERINFO   ,   //成员信息
 MSG_MEET_MUSICINFO    ,   //会议音乐信息
 MSG_MEET_ONESAY       ,   //会议中只允许一个人发言
 MSG_MEET_ALLSAY       ,   //会议中大家都允许发言
 MSG_MEET_SILENT       ,   //禁止所有人发言(主持除外)
 MSG_MEET_REC          ,   //会议录音
 MSG_MEET_PLAYMUSIC    ,   //播放音乐
 MSG_MEET_STOPMUSIC    ,   //停止播放音乐  -ljq
 MSG_MEET_STOPREC      ,   //停止录音 -ljq
 MSG_MEET_SETPARA      ,   //20设置会议参数
 MSG_MEET_KICKOUT      ,   //踢出会议
 MSG_MEET_ADDMEMBER    ,   //添加会议成员
 MSG_MEET_DEL_ROOM     ,   //房间删除
 MSG_MEET_DEL_MEMBER   ,   //成员退出
 MSG_MEET_MONITOR      ,   //-会议监控
 MSG_MEET_OPRES        ,   //会议操作监控应答
 MSG_MEET_SETRECTIME   ,   //设置录音时间

//--座席包
 MSG_SEAT_LOGIN         ,   //坐席登录
 MSG_SEAT_SETSRVSTATUS  ,   //设置服务状态,暂停服务/正常服务
 MSG_SEAT_LOGOUT        ,   //30座席登出
 MSG_SEAT_MOVECALL      ,   //转移来电
 MSG_SEAT_MOVETOMEET    ,   //来电转移到会议

 MSG_SEAT_SILENTCALL    ,   //silent来电,座席在resumecall之前不能接听其他外线呼入
 MSG_SEAT_HOLDCALL      ,   //保持来电,座席在resumecall之前可以接听其他外线呼入
 MSG_SEAT_GETHOLDLIST   ,   //得到保持通道列表
 MSG_SEAT_HOLDLEAVE     ,   //保持线路变化消息
 MSG_SEAT_HOLDINFO      ,   //保持线路信息
 MSG_SEAT_RESUMECALL    ,   //恢复来电
 MSG_SEAT_GETHOLD       ,   //取保持

 MSG_SEAT_CREATMEET     ,    //40创建会议
 MSG_SEAT_MOVETOIVR     ,    //座席呼叫转移到IVR
 MSG_SEAT_RECORD        ,    //录音当前通话
 MSG_SEAT_RECFILEOP     ,    //座席录音操作 收听/删除/查询 
 MSG_SEAT_RECVCALL      ,    //接听其他分机来电
 MSG_SEAT_CALLOUT       ,    //座席呼出
 MSG_SEAT_SETSTATUS     ,    //设置分机状态,呼叫转移/留言/正常状态
 MSG_SEAT_CALLCOME      ,    //来电
 MSG_SEAT_GETSEATINFO   ,    //取得全部通道信息
 MSG_SEAT_SEATINFO      ,    //坐席状态变化通知
 MSG_SEAT_OPRES         ,    //50座席命令操作结果
 MSG_SEAT_LOGIN_RES     ,    //坐席等录结果
 MSG_SEAT_STATUSCHANGE  ,    //座席状态变化消息通知
 MSG_SEAT_ENTERMEET     ,    //加入会议
 MSG_SEAT_AUDITMEET     ,    //旁听会议
 MSG_SEAT_SENDSMS       ,    //坐席发短消息 
 MSG_SEAT_GETCALLQUEUE  ,    //取得未接,已接,已拨的电话列表
 MSG_SEAT_CALLQUEUE     ,    //呼叫电话记录队列信息
 MSG_SEAT_MOVEIVRINFO   ,    //MOVEIVR信息

 MSG_SEATMAN_INSERTCALL ,
 MSG_SEATMAN_MONITOR    ,
 MSG_SEATMAN_RECORD     ,    //60

//--呼叫统计数据包---
 MSG_CS_TALKWTIHSEAT   ,    //外线和座席通话纪录
 MSG_CS_INCALLOUT      ,    //内线呼叫外线纪录
 MSG_CS_INMEET         ,    //在会议室中记录
 MSG_CS_WAITINQUEUE    ,    //等待队列纪录
 MSG_CS_MEETINOUTREC   ,    //会议人员变化纪录
 MSG_CS_MAINBILL       ,    //主话单
 MSG_CS_SECBILL        ,    //IVR流程生成的分段话单

//--运行监控包
//中心平台发送
 MSG_MON_IVRRUNLOG     ,    //IVR运行记录
 MSG_MON_CHANINFO      ,    //通道状态信息
 MSG_MON_SETMONTYPE,        //70
 MSG_MON_STOPMON,
 MSG_MON_STARTMON,
 MSG_MON_DISCONN,
 MSG_MON_LOGIN,

//自动呼出任务服务器
 MSG_CALLOUT_TASK,         //自动呼出任务
 MSG_CALLOUT_RES,          //自动呼出任务结果

//核心远程配置
 MSG_CONSOLE_CMD,          //远程命令
 MSG_CONSOLE_RES,          //结果
 MSG_CONSOLE_PUTDATA,      //Put数据
 MSG_CONSOLE_GETDATA,      //Get数据

//记账卡计费数据包
 MSG_CARD_MONEYALERT,      //电话卡余额不足告警
 MSG_CARD_NOMONEY,         //电话卡月额使用完毕

//2004年1月31日补充包
 MSG_CALLSEAT_COME,        //来电进入队列
 MSG_CALLSEAT_LEAVE,       //来电离开队列
 MSG_GET_CALLSEAT,         //得到目前系统的等待队列

//2004年2月5日补充自动呼出包
 MSG_AUTOCALLOUT_QUERY_READYCNT, 
 MSG_AUTOCALLOUT_READYCNT,
 MSG_AUTOCALLOUT_TASK,
 MSG_AUTOCALLOUT_RES,

//2004年2月20日补充
 MSG_NONE                  //接受到的数据包已经处理完毕
};

//2004年2月24日补充

#define  PackName(a)  #a
 
inline char* GetPackName(int type)
{
	switch(type)
	{
	case MSG_COMM_LOGIN: return "MSG_COMM_LOGIN";  //通讯节点登录    
 case MSG_COMM_ALIVE       : return "MSG_COMM_ALIVE";  //通讯节点心跳信息
 case MSG_COMM_LOGINRES     : return "MSG_COMM_LOGINRES";  //通讯节点登录结果
 case MSG_COMM_NOTIFY       : return "MSG_COMM_NOTIFY";  //通讯节点连接

 case MSG_IVRKERN_DISCONN   : return "MSG_IVRKERN_DISCONN";   //IVR核心服务器断开连接
 case MSG_SEAT_DISCONN      : return "MSG_SEAT_DISCONN";   //座席台断开连接

 case MSG_IVRDATA           : return "MSG_IVRDATA";  //IVR流程数据
 case MSG_OP_RES            : return "MSG_OP_RES";  //操作结果
//--会议包--
 case MSG_MEET_GETROOM      : return "MSG_MEET_GETROOM";   //获取房间信息
 case MSG_MEET_ROOMINFO     : return "MSG_MEET_ROOMINFO";   //10房间信息
 case MSG_MEET_MEMBERINFO   : return "MSG_MEET_MEMBERINFO";   //成员信息
 case MSG_MEET_MUSICINFO    : return "MSG_MEET_MUSICINFO";   //会议音乐信息
 case MSG_MEET_ONESAY       : return "MSG_MEET_ONESAY";   //会议中只允许一个人发言
 case MSG_MEET_ALLSAY       : return "MSG_MEET_ALLSAY";   //会议中大家都允许发言
 case MSG_MEET_SILENT       : return "MSG_MEET_SILENT";   //禁止所有人发言(主持除外)
 case MSG_MEET_REC          : return "MSG_MEET_REC";   //会议录音
 case MSG_MEET_PLAYMUSIC    : return "MSG_MEET_PLAYMUSIC";   //播放音乐
 case MSG_MEET_STOPMUSIC    : return "MSG_MEET_STOPMUSIC";   //停止播放音乐  -ljq
 case MSG_MEET_STOPREC      : return "MSG_MEET_STOPREC";   //停止录音 -ljq
 case MSG_MEET_SETPARA      : return "MSG_MEET_SETPARA";   //20设置会议参数
 case MSG_MEET_KICKOUT      : return "MSG_MEET_KICKOUT";   //踢出会议
 case MSG_MEET_ADDMEMBER    : return "MSG_MEET_ADDMEMBER";   //添加会议成员
 case MSG_MEET_DEL_ROOM     : return "MSG_MEET_DEL_ROOM";   //房间删除
 case MSG_MEET_DEL_MEMBER   : return "MSG_MEET_DEL_MEMBER";   //成员退出
 case MSG_MEET_MONITOR      : return "MSG_MEET_MONITOR";   //-会议监控
 case MSG_MEET_OPRES        : return "MSG_MEET_OPRES";   //会议操作监控应答
 case MSG_MEET_SETRECTIME   : return "MSG_MEET_SETRECTIME";   //设置录音时间
//--座席包
 case MSG_SEAT_LOGIN         : return "MSG_SEAT_LOGIN";   //坐席登录
 case MSG_SEAT_SETSRVSTATUS  : return "MSG_SEAT_SETSRVSTATUS";   //设置服务状态,暂停服务/正常服务
 case MSG_SEAT_LOGOUT        : return "MSG_SEAT_LOGOUT";   //30座席登出
 case MSG_SEAT_MOVECALL      : return "MSG_SEAT_MOVECALL";   //转移来电
 case MSG_SEAT_MOVETOMEET    : return "MSG_SEAT_MOVETOMEET";   //来电转移到会议
 case MSG_SEAT_SILENTCALL    : return "MSG_SEAT_SILENTCALL";   //silent来电,座席在resumecall之前不能接听其他外线呼入
 case MSG_SEAT_HOLDCALL      : return "MSG_SEAT_HOLDCALL";   //保持来电,座席在resumecall之前可以接听其他外线呼入
 case MSG_SEAT_GETHOLDLIST   : return "MSG_SEAT_GETHOLDLIST";   //得到保持通道列表
 case MSG_SEAT_HOLDLEAVE     : return "MSG_SEAT_HOLDLEAVE";   //保持线路变化消息
 case MSG_SEAT_HOLDINFO      : return "MSG_SEAT_HOLDINFO";   //保持线路信息
 case MSG_SEAT_RESUMECALL    : return "MSG_SEAT_RESUMECALL";   //恢复来电
 case MSG_SEAT_GETHOLD       : return "MSG_SEAT_GETHOLD";   //取保持

 case MSG_SEAT_CREATMEET     : return "MSG_SEAT_CREATMEET";    //40创建会议
 case MSG_SEAT_MOVETOIVR     : return "MSG_SEAT_MOVETOIVR";    //座席呼叫转移到IVR
 case MSG_SEAT_RECORD        : return "MSG_SEAT_RECORD";    //录音当前通话
 case MSG_SEAT_RECFILEOP     : return "MSG_SEAT_RECFILEOP";    //座席录音操作 收听/删除/查询 
 case MSG_SEAT_RECVCALL      : return "MSG_SEAT_RECVCALL";    //接听其他分机来电
 case MSG_SEAT_CALLOUT       : return "MSG_SEAT_CALLOUT";    //座席呼出
 case MSG_SEAT_SETSTATUS     : return "MSG_SEAT_SETSTATUS";    //设置分机状态,呼叫转移/留言/正常状态
 case MSG_SEAT_CALLCOME      : return "MSG_SEAT_CALLCOME";    //来电
 case MSG_SEAT_GETSEATINFO   : return "MSG_SEAT_GETSEATINFO";    //取得全部通道信息
 case MSG_SEAT_SEATINFO      : return "MSG_SEAT_SEATINFO";    //坐席状态变化通知
 case MSG_SEAT_OPRES         : return "MSG_SEAT_OPRES";    //50座席命令操作结果
 case MSG_SEAT_LOGIN_RES     : return "MSG_SEAT_LOGIN_RES";    //坐席等录结果
 case MSG_SEAT_STATUSCHANGE  : return "MSG_SEAT_STATUSCHANGE";    //座席状态变化消息通知
 case MSG_SEAT_ENTERMEET     : return "MSG_SEAT_ENTERMEET";    //加入会议
 case MSG_SEAT_AUDITMEET     : return "MSG_SEAT_AUDITMEET";    //旁听会议
 case MSG_SEAT_SENDSMS       : return "MSG_SEAT_SENDSMS";    //坐席发短消息 
 case MSG_SEAT_GETCALLQUEUE  : return "MSG_SEAT_GETCALLQUEUE";    //取得未接,已接,已拨的电话列表
 case MSG_SEAT_CALLQUEUE     : return "MSG_SEAT_CALLQUEUE";    //呼叫电话记录队列信息
 case MSG_SEAT_MOVEIVRINFO:return "MSG_SEAT_MOVEIVRINFO";

 case MSG_SEATMAN_INSERTCALL : return "MSG_SEATMAN_INSERTCALL";
 case MSG_SEATMAN_MONITOR    : return "MSG_SEATMAN_MONITOR";
 case MSG_SEATMAN_RECORD     : return "MSG_SEATMAN_RECORD";    //60
//--呼叫统计数据包---
 case MSG_CS_TALKWTIHSEAT   : return "MSG_CS_TALKWTIHSEAT";    //外线和座席通话纪录
 case MSG_CS_INCALLOUT      : return "MSG_CS_INCALLOUT";    //内线呼叫外线纪录
 case MSG_CS_INMEET         : return "MSG_CS_INMEET";    //在会议室中记录
 case MSG_CS_WAITINQUEUE    : return "MSG_CS_WAITINQUEUE";    //等待队列纪录
 case MSG_CS_MEETINOUTREC   : return "MSG_CS_MEETINOUTREC";    //会议人员变化纪录
 case MSG_CS_MAINBILL       : return "MSG_CS_MAINBILL";    //主话单
 case MSG_CS_SECBILL        : return "MSG_CS_SECBILL";    //IVR流程生成的分段话单
//--运行监控包
//中心平台发送
 case MSG_MON_IVRRUNLOG     : return "MSG_MON_IVRRUNLOG";    //IVR运行记录
 case MSG_MON_CHANINFO      : return "MSG_MON_CHANINFO";    //通道状态信息
 case MSG_MON_SETMONTYPE: return "MSG_MON_SETMONTYPE";        //70
 case MSG_MON_STOPMON: return "MSG_MON_STOPMON";
 case MSG_MON_STARTMON: return "MSG_MON_STARTMON";
 case MSG_MON_DISCONN: return "MSG_MON_DISCONN";
 case MSG_MON_LOGIN: return "MSG_MON_LOGIN";

//自动呼出任务服务器
 case MSG_CALLOUT_TASK: return "MSG_CALLOUT_TASK";         //自动呼出任务
 case MSG_CALLOUT_RES: return "MSG_CALLOUT_RES";         //自动呼出任务结果

//核心远程配置
 case MSG_CONSOLE_CMD: return "MSG_CONSOLE_CMD";          //远程命令
 case MSG_CONSOLE_RES: return "MSG_CONSOLE_RES";          //结果
 case MSG_CONSOLE_PUTDATA: return "MSG_CONSOLE_PUTDATA";      //Put数据
 case MSG_CONSOLE_GETDATA: return "MSG_CONSOLE_GETDATA";      //Get数据
//记账卡计费数据包
 case MSG_CARD_MONEYALERT: return "MSG_CARD_MONEYALERT";      //电话卡余额不足告警
 case MSG_CARD_NOMONEY: return "MSG_CARD_NOMONEY";          //电话卡月额使用完毕
 case MSG_CALLSEAT_COME: return "MSG_CALLSEAT_COME";        //来电进入队列
 case MSG_CALLSEAT_LEAVE: return "MSG_CALLSEAT_LEAVE";       //来电离开队列
 case MSG_GET_CALLSEAT: return "MSG_GET_CALLSEAT";//得到目前系统的等待队列	

 case MSG_AUTOCALLOUT_QUERY_READYCNT: return "MSG_AUTOCALLOUT_QUERY_READYCNT"; 
 case MSG_AUTOCALLOUT_READYCNT: return "MSG_AUTOCALLOUT_READYCNT"; 
 case MSG_AUTOCALLOUT_TASK: return "MSG_AUTOCALLOUT_TASK"; 
 case MSG_AUTOCALLOUT_RES: return "MSG_AUTOCALLOUT_RES"; 
}
	return "MSG_NONAME";
}

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
	switch(dbpak)
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

#define	PAK_BILL               68
#define MSG_CHANDATA 65

//自动呼出UDP连接使用的通讯包
//#define UDP_CALLOUTTASK        66
//#define UDP_CALLOUTRES         67

#define PARAM_IN   0
#define PARAM_OUT  1

//电话卡返回消息
typedef struct{
	int Chan;
	int MeetFlag;
	int MeetNo;
}Card_MoneyAlert;

typedef struct{
	int Chan;
	int MeetFlag;
	int MeetNo;
}Card_NoMoney;

//远程调试
typedef struct{
	char cmdline[256];
}Console_Cmd;

typedef struct{
	char resline[256];
}Console_Res;

typedef struct{
	int datalen;
	char Data[256];
}Console_PutData;

typedef struct{
	int datalen;
	char Data[256];
}Console_GetData;

//-------------呼叫过程记录------------------------
//主话单
typedef struct {
	char CallID[25];   //呼叫ID号码
	char Caller[20];   //主叫号码
	char Called[20];   //被叫号码
	char InLineNo[5]; //内线号码,内线使用外线呼出的内线号码
	int  DevChan;      //占用设备通道
	time_t StartTime;  //开始时间
	time_t EndTime;    //结束时间
	BYTE  CallDirect;  //通话方向  0-呼入　1-呼出
}CallStat_MainBill;

//ivr流程设定分段话单
typedef struct{
	char    CallID[25]; //呼叫ID号码
	char    SPara0[64]; //字符参数
	char    SPara1[64]; //字符参数
	char    SPara2[64]; //字符参数
	char    SPara3[64]; //字符参数
	time_t  StartTime;  //开始时间
	time_t  EndTime;    //结束时间
}CallStat_SecBill;

//
enum{
	WAIT_NOIDLESEAT, //超过没有空闲服务座席
	WAIT_OK,         //座席摘机
	WAIT_NOTOFFHOOK, //座席操时没有摘机
	WAIT_USERHOOK    //客户没有等到座席摘机就挂机
};

//外线呼入队列等待
typedef struct{
	char   CallID[25];      //呼叫ID号码
	char   Caller[20];      //呼入等待外线号码
	char   Called[20];      //呼入被叫号码
	DWORD  WaitGroup;       //等待的分组号码
	DWORD  WaitTechs;       //等待的技能号码
	time_t WaitStartTime;   //开始等待时间
	time_t WaitEndTime;     //结束等待时间
	char   SeatNo[5];       //等待服务座席号码
	BYTE   WaitRes;         //等待结果;
}CallStat_WaitInQueue;

//外线和座席通话
typedef struct  {
	char   CallID[25];      //呼叫ID号码
	char   Caller[20];       //呼入外线号码
	char   Called[20];       //呼入被叫号码
	char   SeatNo[5];        //通话座席号码
	int    SeatDevChan;      //通话座席通道
	char   InLineNo[8];      //通话内线号码
	time_t TalkStartTime;  //通话开始时间
	time_t TalkEndTime;    //通话结束时间
}CallStat_TalkWithSeat;

//内线呼叫外线
typedef struct  {
	char   CallID[25];      //呼叫ID号码
	char   SeatNo[5];        //呼叫外线的座席号码
	char   Caller[20];       //系统呼出使用的主叫
	char   Called[20];       //内线呼出被叫
	time_t TalkStartTime;  //通话开始时间
	time_t TalkEndTime;    //通话结束时间
	char   RecFileName[100]; //通话录音文件
}CallStat_InCallOut;

//内线或外线在会议中
typedef struct{
	char   CallID[25];      //呼叫ID号码
	char   Num[20];         //号码

	DWORD  RoomNo;          //会议房间号码
	time_t EnterMeetTime;  //加入会议房间
	time_t LeaveMeetTime;  //离开会议时间
}CallStat_InMeet;

//会议人数变化记录
typedef struct{
	char   CallID[25];      //呼叫ID号码
	int    RoomNo;            //会议房间号码
	int    MemberCnt;         //会议人数
	char   Num[20];         //号码
	BYTE   Action;           //1-加入会议;0-离开会议
	time_t ActTime;        //动作时间
}CallStat_MeetInOutRec;

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

//呼出任务包
typedef struct{
	int  RecNo;
	char Caller[20];
	char Called[20];
	int  Dpc;                  //呼出局向
	char CallTime[15];
	char NextCallTime[15];
	int  TryCnt;
	int  TryInterval;
	int  TryedCnt;
	char S0[65];
	char S1[65];
	char S2[65];
	char S3[65];
	char S4[65];
	int  IvrHandle;
}CallOut_Task;

//呼出结果包
typedef struct{
   int  RecNo;
   char Caller[20];
   char Called[20];
   int  TryCnt;
   int  TryedCnt;
   int  CallResult;
   char NextCallTime[15];
   int  TryInterval;
}CallOut_Res;

typedef struct{
	int  MsgType;        //IVR Run Log类别 
	char Msg[256];       //Log消息
}Mon_IvrRunLog;

typedef struct{
	WORD Total;
	WORD Chan;
	BYTE ChanType;
	BYTE Direct;
	char Caller[20];
	char Called[20];
	time_t CallBeginTime;
	int RoomNo;
	time_t MeetBeginTime;
	char SeatNo[8];
}Mon_ChanInfo;

typedef struct{
	int  MonType;
	char Caller[20];
}Mon_SetMonType;

//座席台断开连接消息
typedef struct{
	int code;
}Seat_DisConn;

//Data
typedef struct{
	DWORD   Code;//节点编号
	char    PassWord[20];//接入密码
	DWORD   Type;//0-数据socket,1-流socket
	DWORD   CodeType;//节点类型  
}Comm_LogIn;

enum{
	COMM_LOGINOK,     //成功
	COMM_CODE_ERROR,  //CODE越界
	COMM_PASS_ERROR,  //密码错误
	COMM_CODE_LOGINED //CODE已经占用
};
typedef struct{
	int Res;//登录结果;0-;1-密码错误;2-节点编号不存在;3-节点编号已经被使用
}Comm_LogInRes;

typedef struct{
	char Msg[256];
}Comm_Msg;

typedef struct{
	int  Code;//节点编号
	char Des[128];//节点描述
}Comm_CodeInfo;

typedef struct{
	BYTE Status;//0-在线;1-不在线
}Comm_CodeStatus;

//*******会议数据包*******
typedef struct{
	int RoomNo;
	time_t StartTime;
	time_t EndTime;
}Meet_SetRecTime;

typedef struct{
	int EngageCnt;//预定会议人数
    int RoomNo;//物理会议号码
	int Engaged;//该房间是否预订 0-没有;1-预订
	int RecFlag;//是否录音标记
}Meet_Mdy_Room;

typedef struct{
	int RoomNo;//会议房间号码
}Meet_Del_Room;

typedef struct{
	int    RoomNo;
	int    VocChan;//参会者的通道编号
	char   Num[20];
}Meet_Del_Member;


typedef struct{
	int  MemberCnt;//房间当前人数
	int  RoomSize;//房间大小
    int  RoomNo;//物理会议号码
	int  RecFlag;//录音标记 1-在录音;0-停止录音
	char RoomName[128];//房间名称
	int  RoomType;//房间类型
	char RoomTypeName[128];//类型名称
	time_t RoomCreateTime;//会议创建时间
	int  RoomAttr;//房间属性.索引放音|(录音/放音)|旁听
	time_t SetStartRecTime;
	time_t SetEndRecTime;
}Meet_RoomInfo;

typedef struct{
	int     RoomNo;//物理会议号码 
    int     VocChan;//参会者的通道编号
	char    Num[16];//参会通道号码
	int     Type;//会议通道类型  0-正式 1-旁听 2-主持人
    time_t  EnterTime;//加入会议的时间
    int     InGain;//输入增益(0--0x8000) (0x1000表示0dB,推荐使用0x800(-6dB))
}Meet_MemberInfo;

typedef struct{
	int RoomNo;
	int VocCh;
}Meet_OneSay;

#define MEET_REC_START 1
#define MEET_REC_STOP  0
typedef struct{
	int RoomNo;
	int Flag;//0-rec;1-stop rec
	time_t StartRecTime;
	time_t EndRecTime;
}Meet_Rec;

typedef struct{
	int MusicInd;//音乐索引
	char MusicName[128];//音乐名称
}Meet_MusicInfo;

typedef struct{
	int RoomNo;   //物理会议房间号码
	int MusicInd; //播放音乐索引
	int Volume;   //音量 
}Meet_PlayMusic;

typedef struct{
    int RoomNo;
}Meet_StopMusic;

typedef struct{
	int RoomNo;
    int VocCh;
	int Type;     //会议通道类型  0-正式 1-旁听 2-主持人
	int Volume;   //音量 
}Meet_SetPara;

typedef struct{
	int RoomNo;
	int KickOutChan;
}Meet_KickOut;

typedef struct{
	int RoomNo;
	int NumType;  //号码类型 0-外线;1-座席
	int MeetType; //会议类型 0-正式会员;1-旁听会议
	char Caller[16];
	char Num[16];//
}Meet_AddMember;

typedef struct{
    int RoomNo;
}Meet_AllSay;

typedef struct{
	int RoomNo;
}Meet_Silent;

typedef struct{
	char Caller[20];
	char num[20];//监听使用的号码，可以是分机或外线
	int  RoomNo;//监听会议房间号码
}Meet_Monitor;

enum{
 OPRES_SETMEETPARA_FAIL   ,   //改变会议参数失败
 OPRES_SETMEETPARA_OK     ,   //改变会议参数成功
 OPRES_CALLOUTMEMBER_OK   ,   //呼叫加入会议成功 
 OPRES_CALLOUTMEMBER_FAIL ,   //呼叫加入会议失败
 OPRES_KICKOUT_OK         ,   //踢人成功
 OPRES_KICKOUT_FAIL       ,   //踢人失败
 OPRES_PLAYMUSIC_OK       ,   //播放音乐成功
 OPRES_PLAYMUSIC_FAIL        //播放音乐失败
};

typedef struct{
	int  OpRes;    //操作结果值
	char Msg[256]; //操作结果描述
}Meet_OpRes;

//----------------座席消息---------------------
#define SEAT_OPRES_CREATEMEET_OK    1  //创建会议成功
#define SEAT_OPRES_CREATEMEET_FAIL  2  //创建会议失败
#define SEAT_OPRES_ENTERMEET_FAIL   3  //添加会议成员失败
#define SEAT_OPRES_SEAT_NOT_OFFHOOK 4  //座席没有摘机
#define SEAT_OPRES_LOGOUT_OK        5  //LOGOUT OK

//座席操作结果
typedef struct{
	int  res;
	char msg[128];
}Seat_OpRes;

typedef struct{
	char SeatNo[8];
	char SeatPass[8];
	char InLine[8];
}Seat_LogIn;

//登录返回消息
#define	ST_LOGIN_OK               0              //登录成功
#define ST_LOGIN_EXT_ERR          1              //分机号码错误
#define ST_LOGIN_EXT_NOT_PERMIT   2              //工号不在分机允许等录列表中
#define ST_LOGIN_PASS_ERR         3              //工号密码错误
#define ST_LOGIN_ALREADY_LOGIN    4              //该工号已经登录
typedef struct{
	int  LogInRes;
	int  Role;          //0-班长,1-普通
	char err[128];   
}Seat_LogIn_Res;

typedef struct{
	char InLineNo[8];
    int  SrvStatus;     //服务状态 1-示忙,0-示闲
}Seat_SetSrvStatus;

typedef struct{
	char SeatNo[8];
	char SeatPass[8];
	char InLineNo[8];
}Seat_LogOut;

typedef struct{
	char InLineNo[8];
	int  MoveType;//0-内线，1外线
	char MoveNum[20];
}Seat_MoveCall;

typedef struct{
	WORD HoldChan;    //被保持通道编号
	char Num[20];     //被保持通道呼入号码
	time_t StartHoldTime;  //被保持开始时间
	WORD HoldMeInChan;     //保持我的通道
	char HoldMeNum[20];    //保持我的通道号码
	char HoldMeSeatName[20];  //保持通道的座席姓名
}Seat_HoldInfo;

typedef struct{
	WORD HoldChan;
}Seat_HoldLeave;

typedef struct{
	char InLineNo[8];
}Seat_GetHoldList;

typedef struct{
	char InLineNo[8];
}Seat_SilentCall;

typedef struct{
    char InLineNo[8];
}Seat_HoldCall;

typedef struct{
    char InLineNo[8]; //发起通话恢复的分机号码
	char RestoreLineNo[8];//恢复的分机号码
}Seat_ResumeCall;

typedef struct  {
	char InLineNo[8];
	WORD HoldChan;
}Seat_GetHold;


typedef struct{
	char InLineNo[8];
	int  MoveIvrNo;  //转移IVR编号
	char S0[64];     //执行前参数
	char S1[64];     //执行前参数
	char S2[64];     //执行前参数
	char S3[64];     //执行前参数
}Seat_MoveToIvr;

typedef struct{
	int MoveIvrInd;
	char MoveIvrName[256];
}Seat_MoveIvrInfo;

typedef struct{
	char InLineNo[8]; //内线号码
	int  RoomNo;      //房间号码
	int  Chan;        //转移通道号码
}Seat_MoveToMeet;


typedef struct{
	int InCnt;             //内线总数
	int LogicChan;         //内线逻辑通道号
	
	int  Group;            //分组号
	char GroupName[20];    //分组名称
	char InLineNo[8];      //内线号码
	char LogInSeatName[8]; //登录工号姓名
	char LogInSeatNo[8];   //工号
	int  LineStatus;       //线路状态
	int  LogStatus;        //签入状态
	char TalkWithNum[20];  //通话方号码
}Seat_SeatInfo;

typedef struct{
	int LogicChan; 
	char InLineNo[8];
	char LogInSeatName[8];
	char LogInSeatNo[8];
	int  LineStatus;
	char TalkWithNum[20];
}Seat_StatusChange;


typedef struct{
	char InLineNo[8];
	char RecvNum[8];
}Seat_RecvCall;

typedef struct{
	char InLineNo[8];
    int Status;//分机状态:0-正常;1-留言;2-呼叫转移
	int Numtype;//0-内线，1-外线
	char Num[20];
}Seat_SetStatus;

typedef struct{
    char InLineNo[8];
}Seat_Hook;

typedef struct{
	char InLineNo[8];
	int roomno;
}Seat_AuditMeet;

typedef struct{
	int  Chan;  //来点通道号码
	char InLineNo[8];//内线号码
	char CallerNum[20];//来电号码
	char CalledNum[20];//被叫号码
	char MidNum[20];//原被叫
}Seat_CallCome;


typedef struct{
	char InLineNo[8];
	char CallOutNum[20];
	char Caller[20];
}Seat_CallOut;

typedef struct{
	char InLineNo[8];
	char DesLineNo[8];
	char SmsContent[256];
}Seat_SendSms;

typedef struct{
	char InLineNo[8];
	char InsertNum[8];
}SeatMan_InsertCall;

typedef struct{
	char InLineNo[8];
	char MonitorNum[8];
}SeatMan_Monitor;

typedef struct{
	char InLineNo[8];
	char RecNum[8];
}SeatMan_Record;


//通知消息
#define NT_BUSY           0//通讯节点对端正在进行一个文件传输，现在不能进行文件传输操作
#define NT_READY          1//我已经准备好,可以开始发送文件
#define NT_CRC_ERROR      2//流发送的CRC错误
#define NT_STREAM_RECV_OK 3//接收流正确，并且CRC校验也正确
#define NT_NOTONLINE      4//对方通讯节点目前不再线

typedef struct{
	DWORD Event;//通知事件
	DWORD Para;//参数
	char  Msg[256];//通知内容
}Comm_Notify;

typedef struct{
	int chan;
	char Data[256];
}Msg_IvrData;



typedef struct{
	int Chan;                  //通道
	char Caller[20];           //主叫
	time_t  CallSeatTime;      //进入队列时间
	int Group;                 //等待分组
	int Tech;                  //等待技能
}Msg_CallSeat_Come;

//离开结果定义
enum{
	CALLSEAT_TALK,             //和座席通话
	CALLSEAT_NOTACK,           //找到空闲座席，但是座席没有摘机
	CALLSEAT_TIMEOUT,          //超过时间没有空闲座席
	CALLSEAT_RING			   //振铃当前座席
};

typedef struct{
	int Chan;                  //通道
	int LeaveRes;              //离开结果
	time_t RingTime;              //振铃时间
}Msg_CallSeat_Leave;

//查询制定分组的空闲呼出坐席人数
typedef struct{
	int Group;                //查询的分组
}AutoCallOut_Query_ReadyCnt;

//返回空闲呼出坐席人数
typedef struct{
	int Group;
	int Cnt;
}AutoCallOut_ReadyCnt;

//呼出任务
typedef struct{
	int  RecID;
	char Caller[20];
	char Called[20];
	int  DpcNo;
	int	 IvrHnd;
	int  Group;
}AutoCallOut_Task;

//呼出任务的结果
typedef struct{
	int  RecID;
	int  CallRes;
	int  SeatChan;
	char InLine[8];
	char SeatNo[8];
	char SeatKey;  
}AutoCallOut_Res;

//基于提高短数据处理效率的考虑,短数据一律采用定长度的
//数据包.数据长度4字节的整数被数
typedef struct tagTcpPacket{
	DWORD HeadTag;//=0xeffffffe
	DWORD SrcCode;//源代码
	DWORD DesCode;//目的代码
	DWORD PackType;//包类型
	DWORD DesGrp;//目的分组号码,0-发送指定DesCode,0xffffffff-发送到所有节点,其它-指定分组
	             //座席分组必须=1
	union{
		Comm_LogIn login;
		Comm_LogInRes  loginres;
		Comm_Notify  notify;

		Meet_RoomInfo   mt_roominfo;
		Meet_MemberInfo mt_memberinfo;
		Meet_OneSay     mt_onesay;
		Meet_AllSay     mt_allsay;
		Meet_Rec        mt_rec;
		Meet_SetPara    mt_setpara;
		Meet_KickOut    mt_kickout;
		Meet_AddMember  mt_addmember;
		Meet_Del_Room   mt_del_room;
		Meet_Mdy_Room   mt_mdy_room;
        Meet_MusicInfo  mt_musicinfo;
        Meet_PlayMusic  mt_playmusic;
        Meet_StopMusic  mt_stopmusic;
//		Meet_Del_Member mt_del_member;
		Meet_Silent     mt_silent;   
		Meet_Monitor    mt_monitor;
		Meet_OpRes      mt_opres;
		Meet_SetRecTime mt_setrectime;
		
		Msg_IvrData ivrdata;

		Seat_DisConn       st_disconn;
		Seat_LogIn         st_login;
 		Seat_LogIn_Res     st_loginres;
		Seat_SeatInfo      st_seatinfo;
		Seat_StatusChange  st_statuschange;
		Seat_MoveCall      st_movecall;
		Seat_RecvCall      st_recvcall;
		Seat_SetStatus     st_setstatus;
		Seat_SetSrvStatus  st_setsrvstatus;
		
		Seat_SilentCall    st_silentcall;
		Seat_HoldCall      st_holdcall;
		Seat_ResumeCall    st_resumecall;
		Seat_HoldInfo      st_holdinfo;
		Seat_HoldLeave     st_holdleave;
		Seat_GetHold       st_gethold;
		Seat_GetHoldList   st_getholdlist;

		Seat_Hook          st_hook;
		Seat_CallCome      st_callcome;
		Seat_CallOut       st_callout;
		Seat_SendSms       st_sendsms; 
		SeatMan_InsertCall stm_insertcall;
		SeatMan_Monitor    stm_monitor;
		SeatMan_Record     stm_record;
		Seat_OpRes         st_opres;
		Seat_MoveToIvr     st_moveivr;
		Seat_LogOut        st_logout;
		Seat_MoveToMeet    st_movetomeet;
		Seat_MoveIvrInfo   st_moveivrinfo;

		CallStat_WaitInQueue  cs_waitinqueue;
		CallStat_TalkWithSeat cs_talkwithseat;
		CallStat_InCallOut    cs_incallout;
		CallStat_InMeet       cs_inmeet;
		CallStat_MeetInOutRec cs_inoutrec;
		CallStat_MainBill     cs_mainbill;
		CallStat_SecBill      cs_secbill;

		Mon_IvrRunLog    mon_ivrrunlog;
		Mon_ChanInfo     mon_chaninfo;
		Mon_SetMonType   mon_setmontype;

		CallOut_Task    co_task;
		CallOut_Res     co_res;

		Console_Cmd     con_cmd;
		Console_Res     con_res;
		Console_PutData con_putdata;
		Console_GetData con_getdata;

		Card_MoneyAlert cd_moneyalert;
		Card_NoMoney    cd_nomoney;
		Msg_CallSeat_Come callseat_come;
		Msg_CallSeat_Leave callseat_leave;

		AutoCallOut_Query_ReadyCnt ac_query_readycnt;
		AutoCallOut_ReadyCnt ac_readycnt;
		AutoCallOut_Task ac_task;
		AutoCallOut_Res ac_res;
	};
	tagTcpPacket(){
		memset(this,0,sizeof(tagTcpPacket));
	};
}TcpPacket;

#ifdef VER_10 
typedef struct{
	BYTE    BillType;//计费类型
	BYTE    CardFlag;//卡计费:0-没有使用卡,1-输入卡
	time_t StartTime;//分段计费开始
	time_t EndTime;//分段计费结束
	BYTE    SecType;//分段类型
	int    IPara1;//整形参数1
	int    IPara2;//整形参数2
	char   SPara1[20];//字符参数
	float  Fee;
}SecBill;
typedef struct{
	char  CallId[25];// 呼叫ID
	BYTE  BillType;//计费类型
	char  FeeNum[21];//计费号码
	
	char  Caller[20];
	char  Called[20];
	time_t StartTime;// 开始计费时间
	time_t EndTime;// 结束计费时间
	
	BYTE CallType;//呼叫类型
	BYTE SecCnt;
	float Fee;
	SecBill Secs[MAX_SECS];
}UDP_Bill;
#endif

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

#endif
