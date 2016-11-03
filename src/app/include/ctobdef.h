/*
核心服务器管理对象结构定义
1)数字中继通道
2)座席通道
3)会议和会议成员

作者:余涛
日期:2003年11月1日
修订:
*/
#ifndef _ctobdef_h_
#define _ctobdef_h_

#include <list>
#include <time.h>
using namespace std;

//外线
typedef struct{
    char Caller[20];//呼叫号码
    char Called[20];//线路号码
}LZ_OutLine;

//座席登记状态
#define LZ_LS_LOGOUT   0//座席登出
#define LZ_LS_LOGIN    1//座席登入
#define LZ_LS_PAUSE    2//座席暂停
#define LZ_LS_CANCELED 3//座席取消

//座席角色
#define LZ_ROLE_SEAT     1//普通座席
#define LZ_ROLE_SEATMAN  2//管理座席

typedef struct {
    char SeatNo[8];//登录座席号
	char Name[10];//工号姓名
    char LineNo[8];//线路固定分机号
	char Password[10]; //座席密码 
    BYTE Role;//内线角色.普通座席，管理座席

    DWORD Group;//组号
	DWORD Tech; //技能 
    BYTE   LogStatus;//座席登记状态;
    time_t LogInTime;//座席登记时间
    int TalkTime;//座席登录进来后的累计通话时间(秒)
	
	int SeatCode;//座席台通讯节点Code
}LZ_InLine;

//***********************线路状态定义***********************
//外线状态
#define LZ_OUT_IDLE          0   //空闲
#define LZ_OUT_OFFHOOK       1   //呼出摘机
#define LZ_OUT_RING          2   //呼入振铃
#define LZ_OUT_TALKWITHOUT   3   //和外线通话
#define LZ_OUT_TALKWITHIN    4   //和座席通话
#define LZ_OUT_HOLD          5   //和座席通话被保持
#define LZ_OUT_MEET          6   //会议中
#define LZ_OUT_AUTOIVR       7   //自动IVR
#define LZ_OUT_WAIT          8   //队列等待

//外线状态相关参数
typedef struct  {
	int OutChan;      //通话外线通道
	char OutNum[20];  //通话外线号码
}OutTalkWithOutPara;

typedef struct{
	int InChan;
	char InNum[20];
}OutTalkWithInPara;

typedef struct{
	int HoldInChan;//保持的内线通道
}OutHoldPara;

typedef struct{
	int WaitGroup;//等待座席分组号码
	int WaitTechs;//等待技能类型 >0开始等待
	DWORD WaitTime;//等待时间长度
}OutWaitPara;

typedef struct{
	int RoomNo;
}OutMeetPara;

//内线状态
#define LZ_IN_IDLE           0  //内线空闲
#define LZ_IN_OFFHOOK        1  //内线摘机
#define LZ_IN_RING           2  //内线振铃
#define LZ_IN_TALKWITHOUT    3  //内线和外线通话
#define LZ_IN_TALKWITHIN     4  //和内线通话
#define LZ_IN_MEET           5  //会议中
#define LZ_IN_MOVE           6  //呼叫转移状态
#define LZ_IN_LEVMSG         7  //留言状态

//内线状态相关参数
typedef struct{
	int OutChan;
	char OutNum[20];
}InTalkWithOutPara;

typedef struct{
	int InChan;
	char InNum[20];
}InTalkWithInPara;

typedef struct{
	int RoomNo;
}InMeetPara;

typedef struct{
    int  MoveChan;//座席的呼叫转移通道
	int  MoveType;//座席呼叫转移类型0-内线;1-外线
    char MoveNum[20];//座席的呼叫转移号码
}InMovePara;

//通道结构定义
typedef struct  {
	long ChanType;         //通道类型,内线/外线
	long CallDirect;       //通话方向,呼出/呼出
	time_t OffHookTime;    //摘机时刻
	long OffHookDur;       //摘机时间,单位秒
	
	long Status;           //线路状态
	long ChdStatus;        //线路子状态

	//状态关联参数
	union{
		OutTalkWithOutPara o_p_TalkWithOut;
		OutTalkWithInPara  o_p_TalkWithIn;
		OutHoldPara        o_p_Hold;
		OutWaitPara        o_p_Wait;
		OutMeetPara        o_p_Meet;

		InTalkWithOutPara  i_p_TalkWithOut;
		InTalkWithInPara   i_p_TalkWithIn;
		InMeetPara         i_p_Meet;
		InMovePara         i_p_Move;
	};

	//内线/外线固定参数
	union{
		OutLine Out;
		InLine  In;
	};
}LZ_Chan;

//***************************会议结构************************************
//会议通道参数
#define LZ_MEET_TYPE_MEMBER  0//正式会议成员，可以发言
#define LZ_MEET_TYPE_AUDIT   1//旁听会议成员
#define LZ_MEET_TYPE_PRESIDE 2//主持人通道
typedef struct {
    WORD    VocChan;//参会者的通道编号
	char    Num[16];//参会通道号码
	WORD    Type;//会议通道类型
    time_t  EnterTime;//加入会议的时间
    WORD    InGain;//输入增益(0--0x8000) (0x1000表示0dB,推荐使用0x800(-6dB))
}LZ_MeetMember;

#define LZ_ROOM_ATTR_RECORD  0X01  //录音属性
#define LZ_ROOM_ATTR_MUSIC   0x02  //放音属性
#define LZ_ROOM_ATTR_AUDIT   0X04  //旁听属性

typedef struct {
    list <LZ_MeetMember> MemberList;//与会人通道列表
	int  RoomSize;//房间大小
    int  RoomNo;//物理会议号码
	int  RecFlag;//录音标记 1-在录音,0-停止录音
	char RoomName[128];//房间名称
	int  RoomType;//房间类型
	char RoomTypeName[128];//类型名称
	time_t RoomCreateTime;//会议创建时间
	int  RoomAttr;//房间属性.录音|放音|旁听
}LZ_MeetRoom;

#endif
