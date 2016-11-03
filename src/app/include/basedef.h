#include <list>
#ifndef _basedef_h_
#define _basedef_h_
//DTMF缓冲区最大值
#define MAX_DTMFBUF_LEN 64
#define MAX_COMMAND     9999999

using namespace std;

//座席的来电队列元素数据
typedef struct{
    char phone[20];
    time_t  t;
}
Phone;

//外线
typedef struct{
    char CallNum[20];//呼叫主叫号码
	char MidNum[20]; //原被叫号码
    char LineNum[20];//线路号码
}
OutLine;

//座席角色
#define ROLE_EXT  0
#define ROLE_SEAT  1
#define ROLE_EXTSEAT 2

typedef struct {
    char SeatNo[8];//登录座席号
	char Name[10];//工号姓名
    char LineNo[8];//线路固定分机号
	char Password[10]; //座席密码 
    BYTE Role;//内线角色.普通座席，管理座席

    DWORD Group;//组号
	DWORD Tech; //技能 
	
	//座席登记状态
#define LS_LOGOUT   0//座席登出
#define LS_LOGIN    1//座席登入
#define LS_PAUSE    2//座席暂停
#define LS_CANCELED 3//座席取消

    BYTE LogStatus;//座席登记状态;
    time_t LogInTime;//座席登记时间
    int TalkTime;//座席登录进来后的累计通话时间(秒)
	
	int No;
	int SeatCode;//座席台通讯节点Code
    WORD movechan;//座席的呼叫转移通道
	int  MoveType;//座席呼叫转移类型0-内线;1-外线
    char MoveNum[20];//座席的呼叫转移号码

    char LeaveMsgFile[64];//内线通道留言语音文件

	int AutoRecFlag;//自动通话录音标记 0-不录音 1-录音
}
InLine;

//线路状态
enum{
 CHAN_IDLE,	               //空闲
 CHAN_TALK2,		       //双方通话
 CHAN_MEET,                //会议中
 CHAN_AUTOIVR,	           //自动ivr
 CHAN_HOLD,                //通话保持
 CHAN_NOTUSE,              //未开通
 CHAN_WAIT,                //队列中
 CHAN_CALLOUT_MEET,        //呼出加入会议
 CHAN_CALLOUT_IVR,         //呼出自动IVR
 CHAN_CALLOUT_TALKWITHIN,  //呼出和内线通话
 CHAN_CALLOUT_MONITORMEET, //呼出监听会议状态
 CHAN_CALLOUT_TALKWITHOUT, //呼出和外线通话
	//--内线专用
 CHAN_LEVMSG,		  //不在座位
 CHAN_MOVECALL,	      //呼叫转移
 CHAN_RING,		      //振铃中
 CHAN_OFFHOOK,        //主动摘机
 CHAN_WAITHOOK,       //内线等待挂机状态16
 CHAN_SILENT,         //静音状态
 CHAN_IAMBUSY,        //示忙

 CHAN_CALLOUT_OFFHOOK, //外线被呼叫接通通话

 CHAN_AUTOCALLOUT_READYFOR,    //内线摘机等待接通被叫
 CHAN_AUTOCALLOUT_TALK,     //内线和自动呼出外线通话状态
 CHAN_AUTOCALLOUT_WAIT_OFFHOOK, //内线等待外线呼出成功

 CHAN_CALLOUTING  //外线正在呼出状态
};
#define  LineStatus(a)  #a

//IVR通道状态数据
typedef struct{
	int   ChanType;
    WORD  Status;//线路状态;
	WORD  AllocRes;

	char CallID[25];
	time_t OffHookTime;//摘机时间

#define DIR_NONE         0
#define DIR_IN           1
#define DIR_OUT          2
#define DIR_AFTERRELEASE 3
#define DIR_MONEYALERT   4
#define DIR_TOBESTOP     5

    BYTE Direct;//通道的通话方向

    int IvrFileHnd;//执行的ivr文件索引
	int IvrVer;//执行的 版本;0或1

//在会议中被人邀请标记
	bool InviteFlag;     //是否有人邀请我
	char InviteNum[20];  //邀请我的人号码
	int  InviteVoc;      //邀请我的语音
	int  Agree;          //0-等待对方答复，1-同意 2-不容易  
	int  InviteChan;     //邀请我的通道

//外线呼叫外线参数
	int CallOutChan;  //外线呼叫外线呼叫成功后的通道

//---语音播放按键中断设置
	char StopDtmf[13];   //中断键
	WORD SaveVarNo;  //中断键保存变量
	
//--通话状态参数
	char ConnectNum[20];//连接通话号码
    WORD ConnChan;//连结通道
	
//--呼叫座席等待参数--------
	int   WaitGroup;//等待座席分组号码
	int   WaitTechs;//等待技能类型 >0开始等待
	DWORD WaitTime;//等待时间长度
//--通话保持参数----
	//对于外线
#define HOLD_SILENT    0
#define HOLD_HOLD      1
	BYTE    HoldType;   //Hold类型 0-Silent ,1-Hold
	WORD    WhoHoldMe;  //哪个通道保持了我
	time_t  StartHoldTime; //开始保持我的时间
	//对于内线
	WORD SilentChan;  //被静音的外线通道

    WORD HoldChanNo;//通话保持通道
	int  RoomNo;//通道参加会议的会议房间号
	int  CreateRoomNo;//通道创建的会议号码

    //通道类型相关参数
    OutLine  Out;
    InLine   In;

    char DtmfBuf[MAX_DTMFBUF_LEN];//通道dtmf缓冲
	
	void Reset()
    {
		InviteFlag=false;
		Agree=false;
		if (Status!=CHAN_MOVECALL&&Status!=CHAN_LEVMSG)
			Status=CHAN_IDLE;
		WaitGroup=-1;
		WaitTime=0;
	    Direct=DIR_NONE;
        memset(DtmfBuf,0,MAX_DTMFBUF_LEN);
        HoldChanNo=-1;
		SilentChan=-1;
		ConnChan=-1;
		CallOutChan=0;
        memset(Out.CallNum,0,20);
		memset(Out.LineNum,0,20);
		memset(Out.MidNum,0,20);
		memset(ConnectNum,0,20);
		memset(In.SeatNo,0,8);
		In.Tech=0;
		In.Group=0;
		OffHookTime=0;
		RoomNo=-1;
		CreateRoomNo=-1;
		memset(StopDtmf,0,13);//=0;
		SaveVarNo=-1;
    }
	void SetCallNum(const char* num)
	{
		memset(Out.CallNum,0,20);
		strncpy(Out.CallNum,num,19);
	}
	void SetLineNum(const char* num)
	{
		memset(Out.LineNum,0,20);
		strncpy(Out.LineNum,num,19);
	}
}
YTChan;

//----------------------会议结构
//会议通道参数
#define MEMBER_TYPE_MEMBER  0//正式会议成员，可以发言
#define MEMBER_TYPE_AUDIT   1//旁听会议成员
#define MEMBER_TYPE_PRESIDE 2//主持人
typedef struct tagMeetMember{
    WORD    VocChan;//参会者的通道编号
	char    Num[16];//参会通道号码
	WORD    Type;//会议通道类型
    time_t  EnterTime;//加入会议的时间
    WORD    InGain;//输入增益(0--0x800) (0x1000表示0dB,推荐使用0x800(-6dB)
	bool    ZhanKeng;//会议占坑标记
	tagMeetMember()
	{
		memset(Num,0,16);
		ZhanKeng=false;
	}
}
MeetMember;

typedef struct tagMeetRoom{
    list <MeetMember> MemberList;//与会人通道列表
	int  RoomSize;//房间大小
    int  RoomNo;//物理会议号码
	int  RecFlag;//录音标记 1-在录音,0-停止录音
	char RoomName[128];//房间名称
	int  RoomType;//房间类型
	char RoomTypeName[128];//类型名称
	time_t RoomCreateTime;//会议创建时间
	int  RoomAttr;//房间属性.录放音|索引放音|旁听
	time_t SetStartRecTime;
	time_t SetEndRecTime;
	tagMeetRoom()
	{
		RoomSize=0;
		RoomNo=-1;
		RoomType=0;
		memset(RoomName,0,128);
		memset(RoomTypeName,0,128);
		SetStartRecTime=0;
		SetEndRecTime=0;
		RecFlag=false;
	}
}
MeetRoom;
#endif
