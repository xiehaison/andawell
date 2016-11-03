#ifndef _atomcmd_h_
#define _atomcmd_h_
#include <list>
#include <time.h>
#include "commpack.h"

using namespace std;
//字符缓冲区最大值
#define MAX_SCONBUF  4096*4
//单个字符常量最大值
#define MAX_SCONLEN  512

//TTS类型
#define TTS_TEXT     1
#define TTS_INTEGER  5
#define TTS_FLOAT    6
#define TTS_YUAN     10
#define TTS_YJF      11
#define TTS_YEAR     20
#define TTS_MONTH    21
#define TTS_DAY      22
#define TTS_DATE     23
#define TTS_HOUR     24
#define TTS_MINUTE   25
#define TTS_SECOND   26
#define TTS_TIME     27
#define TTS_DATETIME 28
#define TTS_NUM      29
//数据库操作GetField等待时间(毫秒)
#define TIME_DBOP  2000
#define SCON 255
//脚本命令结构
#define LT  0
#define GT  1
#define LE  2
#define GE  3
#define EQ  4

#define WAIT_TRIGGER        0   //等待通道振铃状态
#define DMANALOG_WAITHOOK   1   //DMPCI模拟卡的准备拆线状态,DMPCI摘机和挂机之间需要至少1.5秒钟的时间间隔
//-----------------内线主动摘机的状态
#define INLINE_SIGNAL       2   //内线摘机播放信号音
#define INLINE_BUSY         3   //信号音播放结束没有任何有效按键,开始播放忙音
#define INLINE_RECVDTMF     4   //接收用户按键状态

#define CMD_START          6
#define CMD_CALLSEAT       40
#define CMD_PLAYVOC        41
#define CMD_TALK2          42
#define CMD_INPUT          43
#define CMD_DIGIT          44
#define CMD_CREATEMEET     45
#define CMD_ENTERMEET      46
#define CMD_MEETTALK       47
#define CMD_SCRIPT	       48
#define CMD_CALLEXT        49
#define CMD_CALLOUT        50
#define CMD_RECORD         51
#define CMD_YPLAYTTS       52
#define CMD_YCYCPLAY       53
#define CMD_YGOTO          54
#define CMD_TALKWITHOUT    55   //和外线通话
#define CMD_CALLOUT2       56
#define CMD_PLAYVOC2       57   //两个通道同时放音
#define CMD_INVITE         58   //邀请一个在会议中的人通话
#define CMD_TALKWITHINVITE 59   //和被邀请的人通话

const BYTE REF_I=1;
const BYTE REF_F=2;
const BYTE REF_T=3;
const BYTE REF_S=4;
const BYTE CON_I=5;
const BYTE CON_F=6;
const BYTE CON_S=7;
const BYTE CON_T=8;
const BYTE CON_SYS=9;
const BYTE CON_EXP=10;
const WORD CMD_CALLFUNC=0;
const WORD CMD_PUSHALL=1;
const WORD CMD_POPALL=2;
const WORD CMD_PUSH=3;
const WORD CMD_SET=4;
const WORD CMD_ADD=5;
const WORD CMD_SUB=6;
const WORD CMD_MUL=7;
const WORD CMD_DIV=8;
const WORD CMD_CMPD=9;
const WORD CMD_CMPT=10;
const WORD CMD_CONDGOTO=11;
const WORD CMD_I2S=12;
const WORD CMD_F2S=13;
const WORD CMD_T2S=14;
const WORD CMD_S2I=15;
const WORD CMD_S2F=16;
const WORD CMD_S2T=17;
const WORD CMD_STRLEN=18;
const WORD CMD_STRTRIMLEFT=19;
const WORD CMD_STRTRIMRIGHT=20;
const WORD CMD_STRTRIM=21;
const WORD CMD_STRREPLACE=22;
const WORD CMD_STRMID=23;
const WORD CMD_STRDEL=24;
const WORD CMD_STRCAT=25;
const WORD CMD_STRUPPER=26;
const WORD CMD_STRLOWER=27;
const WORD CMD_STRPARSE=28;
const WORD CMD_NOW=29;
const WORD CMD_DATEADDDAY=30;
const WORD CMD_DATEADDHOUR=31;
const WORD CMD_DATEADDMIN=32;
const WORD CMD_DATEPARTMIN=33;
const WORD CMD_DATEPARTSEC=34;
const WORD CMD_DATEPARTDAY=35;
const WORD CMD_DATEPARTMONTH=36;
const WORD CMD_DATEPARTWEEK=37;
const WORD CMD_DATEPARTYEAR=38;
const WORD CMD_DATEDIFFDAY=39;
const WORD CMD_DATEDIFFHOUR=40;
const WORD CMD_DATEDIFFMIN=41;
const WORD CMD_DATEDIFFSEC=42;
const WORD CMD_SENDPACKET=43;
const WORD CMD_RECVPACKET=44;
const WORD CMD_SQLOPEN=45;
const WORD CMD_GETFIELDI=46;
const WORD CMD_GETFIELDS=47;
const WORD CMD_GETFIELDT=48;
const WORD CMD_GETFIELDF=49;
const WORD CMD_MOVENEXT=50;
const WORD CMD_EOF=51;
const WORD CMD_SQLEXEC=52;
const WORD CMD_SPEXEC=53;
const WORD CMD_SETSQLPARAMI=54;
const WORD CMD_SETSQLPARAMS=55;
const WORD CMD_SETSQLPARAMT=56;
const WORD CMD_SETSQLPARAMF=57;
const WORD CMD_GETSPOUTI=58;
const WORD CMD_GETSPOUTS=59;
const WORD CMD_GETSPOUTT=60;
const WORD CMD_GETSPOUTF=61;
const WORD CMD_POP=62;
const WORD CMD_DATEPARTHOUR=63;
const WORD CMD_NONE=64;
const WORD CMD_IF=65;
const WORD CMD_GOTO=66;
const WORD CMD_PREPARESQL=67;
const WORD CMD_SETPARAMIN=68;
const WORD CMD_SETPARAMOUT=69;
const WORD CMD_GETPARAMOUT=70;
const WORD CMD_GETFIELD=71;
const WORD CMD_STOP=72;
const WORD CMD_PRINT=73;
const WORD CMD_GOTOOUT=74;
const WORD CMD_STARTBILL=75;
const WORD CMD_SETBILLTYPE=76;
const WORD CMD_SECBILLBEGIN=77;
const WORD CMD_SECBILLEND=78;
const WORD CMD_ENDBILL=79;
const WORD CMD_RECFILE=80;
const WORD CMD_GOTODEF=81;
const WORD CMD_PLAYTTS=83;
const WORD CMD_SLEEP=84;
const WORD CMD_VERIFYACCOUNT=85;
const WORD CMD_VERIFYPASSWORD=86;
const WORD CMD_CYCPLAY=87;
const WORD CMD_SETSECPARA=88;
const WORD CMD_RECFILE2=89;
const WORD CMD_ADDMUSIC=90;
const WORD CMD_SS7ACK=91;
const WORD CMD_PLAYDTMF=92;
const WORD CMD_SETCARDPARA=93;
const WORD CMD_CONNCHAN=94;
const WORD CMD_CHECKSTATUS=95;
const WORD CMD_GETMEETMEMBERCNT=96;
const WORD CMD_KALAOK=97;
const WORD CMD_REMOVEMUSIC=98;
const WORD CMD_AUDITMEET=99;
const WORD CMD_ADDMUSIC2=100;
const WORD CMD_PLAYINDVOCINMEET=101;
const WORD CMD_PLAYFILEVOCINMEET=102;
const WORD CMD_STOPMEETPLAYVOC=103;
const WORD CMD_STARTSEC=105;
const WORD CMD_SETSEC=106;
const WORD CMD_ENDSEC=107;
const WORD CMD_FINDNUMINMEET=108;
const WORD CMD_HAVEPRESIDE=109;
const WORD CMD_SETDTMFSTOP=110;
const WORD CMD_CANCELDTMFSTOP=111;
const WORD CMD_PLAYFILE=112;
const WORD CMD_PLAYINDEX=113;
const WORD CMD_GETMEET=114;
const WORD CMD_FINDIDLEMEETROOM=115;
const WORD CMD_CHECKTIMEFORMAT=116;
const WORD CMD_ALLOCRES=117;
const WORD CMD_FREERES=118;
const WORD CMD_LISTENMEET=119;
const WORD CMD_GETMEETPARA=120;
const WORD CMD_EXECIVR=121;
const WORD CMD_DELETEMEET=122;
const WORD CMD_LEAVEMEET=123;
const WORD CMD_UPDATEFIELD=124;
const WORD CMD_FINDNUMINSYSTEM=125;
const WORD CMD_INTALKWITHOUT=126;
const WORD CMD_PLAYTTSINMEET=127;
const WORD CMD_SS7ACM=128;
const WORD CMD_GETCALLED=129;
const WORD CMD_GETSEATPARA=130;
const WORD CMD_PLAYINDEX2=131;
const WORD CMD_SAVEDTMF=132;
const WORD CMD_CANCELBILL=133;
//字符常量指针结构
typedef struct{
    WORD StartPos;
    WORD Len;
}SString;

typedef struct{
	WORD No1;
}Srp_SaveDtmf;


typedef struct{
	//语音文件索引号
	BYTE RefType1;
	WORD No1;
	int  ICon1;
}Srp_PlayIndex2;

typedef struct{
	WORD ICon1; 
	WORD No2;
	WORD No3; 
}Srp_GetSeatPara;

typedef struct{
	WORD No1;
}Srp_GetCalled;

typedef struct{
	//房间号
	BYTE RefType1;
	WORD No1;
	int  ICon1;

	//播放内容
	BYTE RefType2;
	WORD No2;
	SString SCon2;

	//播放类型
	BYTE RefType3;
	WORD No3;
	int ICon3;
}Srp_PlayTTSInMeet;

typedef struct{
	WORD No1;//通话连接外线通道
}Srp_InTalkWithOut;

typedef struct{
	BYTE RefType1;
	WORD No1;
	SString SCon1;

	WORD No2;
}Srp_FindNumInSystem;

//更新字段
typedef struct{
	BYTE RefType1;
	WORD No1;
	int  ICon1;

	BYTE RefType2;
	WORD No2;
	int ICon2;
	float FCon2;
	SString SCon2;
	char TCon2[14];
}Srp_UpdateField;

//离开会议
typedef struct{
	BYTE RefType1;
	WORD No1;
}Srp_LeaveMeet;

//删除会议
typedef struct{
	WORD No1;
}Srp_DeleteMeet;

//执行IVR流程
typedef struct{
	BYTE RefType1;
	WORD No1;
	int  ICon1;
}Srp_ExecIvr;
//取得会议参数
typedef struct{
	char GetType[10];
	
	//房间
	BYTE RefType1;
	WORD No1;

	//参数值
	BYTE RefType2;
	WORD No2;
}Srp_GetMeetPara;

//旁听会议
typedef struct{
	//会议房间号码
	BYTE RefType1;
	WORD No1;

	//加入结果
	WORD No2;
}Srp_ListenMeet;

//分配资源
typedef struct{
	//分配资源类型
	BYTE RefType1;
	WORD No1;
	int  ICon1;

	//分配结果
	WORD No2;
}Srp_AllocRes;


//检查日期时间格式
typedef struct{
	//日期时间字符串
	WORD No1;
	//检查类型
	WORD Type;
	//检查结果 0-错误,1-正确
	WORD No2;
}Srp_CheckTimeFormat;

//在系统中寻找有空闲位置的房间
typedef struct{
	BYTE RefType1;
	WORD No1;
	int  ICon1;

	BYTE RefType2;
	WORD No2;
	int  ICon2;

	BYTE RefType3;
	WORD No3;
	int  ICon3;

	BYTE RefType4;
	WORD No4;
	int  ICon4;

	WORD No5;
}Srp_FindIdleMeetRoom;

//得到指定编号的会议房间值
typedef struct{
	//房间编号
	BYTE RefType1;
	WORD No1;
	int  ICon1;
	//取得的房间号码
	WORD No2;
}Srp_GetMeet;
//播放文件语音
typedef struct{
	//语音文件名称
	BYTE RefType1;
	WORD No1;
	SString SCon1;
	//播放结果0-ok,1-fail,2-dtmfstop
	WORD No2;
}Srp_PlayFile;

//播放索引语音
typedef struct{
	//语音文件索引号
	BYTE RefType1;
	WORD No1;
	int  ICon1;
	//播放结果0-ok,1-fail,2-dtmfstop
	WORD No2;
}Srp_PlayIndex;
//设置按键打断
typedef struct{
	//中断按键
	BYTE RefType1;
	WORD No1;
	SString SCon1;
}Srp_SetDtmfStop;

//判断会议中是否有主持人
typedef struct  {
	//会议房间号码
	BYTE RefType1;
	WORD No1;
	int  ICon1;
	//判断结果0-没有,1-有
	WORD No2;
}Srp_HavePreside;

//查找号码是否在会议房间中
typedef struct{
	//查询电话号码
	BYTE RefType1;
	WORD No1;
	SString  SCon1;

	BYTE RefType2;
	WORD No2;
	int  ICon2;
	//返回的所在房间号码
	WORD No3;

	//返回的通道号码
	WORD No4;
}Srp_FindNumInMeet;

//设置分段参数
typedef struct{
	//参数索引
	BYTE RefType1;
	WORD No1;
	int  ICon1;

	//字符参数值
	BYTE RefType2;
	WORD No2;
	SString SCon2;
}Srp_SetSec;

//会议中播放索引语音
typedef struct{
	//会议房间号码
	BYTE RefType1;
	WORD No1;

	//索引语音
	BYTE RefType2;
	WORD No2;
	int ICon2;

	//循环播放标记
	BYTE RefType3;
	WORD No3;
	int ICon3;
}Srp_PlayIndVocInMeet;

//会议中播放文件语音
typedef struct{
	//会议房间号码
	BYTE RefType1;
	WORD No1;

	//文件语音
	BYTE RefType2;
	WORD No2;
	SString SCon2;

	//音量
	BYTE RefType3;
	WORD No3;
	int ICon3;

	//循环播放标记
	BYTE RefType4;
	WORD No4;
	int ICon4;
}Srp_PlayFileVocInMeet;

//停止会议中播放语音
typedef struct{
	//会议房间号码
	BYTE RefType1;
	WORD No1;

	//停止播放语音类型
	BYTE RefType2;
	WORD No2;
	int ICon2;
}Srp_StopMeetPlayVoc;

//添加会议背景文件音乐
typedef struct{
	//房间号
	BYTE RefType1;
	WORD No1;
	int ICon1;

	//背景音乐
	BYTE RefType2;
	WORD No2;
	SString SCon2;

	//音量
	BYTE RefType3;
	WORD No3;
	int ICon3;
}Srp_AddMusic2;

//旁听会议
typedef struct{
	BYTE RefType1;
	WORD No1;
	int ICon1;
}Srp_AuditMeet;

//去除背景音乐
typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon1;
}Srp_RemoveMusic;

typedef struct{
    //录音文件名称
    BYTE RefType1;
    WORD No1;
    SString SCon1;

    //背景音乐名称
    BYTE RefType2;
    WORD No2;
    SString SCon2;

    //背景音乐音量
    BYTE RefType3;
    WORD No3;
    int ICon3;

    //录音中断按键
    BYTE RefType4;
    WORD No4;
    SString SCon4;

    //录音时间长度
    BYTE RefType5;
    WORD No5;
    int ICon5;

    //录音结果
    WORD No6;
}Srp_KaLaOk;

typedef struct{
	//会议房间号
	BYTE RefType1;
	WORD No1;
	//会议房间人数//-1,房间号码不存在,
	WORD No2;
}Srp_GetMeetMemberCnt;

//连接通道
typedef struct{
    WORD No1;//连接通道1
    WORD No2;//连接通道2;
    WORD No3;//保留
}Srp_ConnChan;

//检查线路状态
typedef struct{
    WORD No1;//线路通道
    WORD No2;//线路状态结果
}Srp_CheckStatus;

typedef struct{
    WORD No1;//账号
    WORD No2;//费率
    WORD No3;//余额
}Srp_SetCardPara;

typedef struct{
	WORD No1;
}Srp_PlayDTMF;

typedef struct{
	BYTE RefType1;
	WORD No1;
	int ICon1;

	BYTE RefType2;
	WORD No2;
	int ICon2;

	BYTE RefType3;
	WORD No3;
	int ICon3;

	WORD No4;
}Srp_AddMusic;

typedef struct{
	BYTE RefType1;
	WORD No1;
	SString SCon1;

	BYTE RefType2;
	WORD No2;
	int ICon2;

	BYTE RefType3;
	WORD No3;
	int ICon3;

	BYTE RefType4;
	SString SCon4;
	WORD No4;

	BYTE RefType5;
	WORD No5;
	int ICon5;

	WORD No6;
}Srp_RecFile2;

typedef struct{
	WORD No1;
	WORD No2;
	WORD No3;
}Srp_SetSecPara;

typedef struct{
	WORD No1;
	WORD No2;
}Srp_VerifyAccount;

typedef struct{
	WORD No1;//账号
	WORD No2;//密码

	BYTE RefType3;//费率
	WORD No3;
	int ICon3;

	WORD No4;//余额
	WORD No5;//验证结果
	WORD No6;//登录数量
}Srp_VerifyPassword;

typedef struct{
	BYTE RefType1;
	WORD No1;
	int ICon1;
}Srp_Sleep;

typedef struct{
	//播放内容
	BYTE RefType1;
	WORD No1;
	int ICon1;
	char TCon1[14];
	SString SCon1;
	double FCon1;

	//播放类型
	BYTE RefType2;
	WORD No2;
	int ICon2;

	//结果  0-正常；1-错误；2-按键打断
	WORD No3;
}Srp_PlayTTS;

typedef struct{
    BYTE RefType1;
    WORD No1;
    SString SCon1;

    BYTE RefType2;
    WORD No2;
    SString SCon2;

	BYTE RefType3;
	WORD No3;
	int ICon3;

    WORD No4;
}Srp_RecFile;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon1;
    BYTE RefType2;
    WORD No2;
    int ICon2;
}Srp_StartBill;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon1;

    WORD No2;
}Srp_SetBillType;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon1;

	BYTE RefType2;
	WORD No2;
	int ICon2;

	BYTE RefType3;
	WORD No3;
	int ICon3;
}Srp_SecBillBegin;

typedef struct{
    int CmdOut;
    SString SCon;
}Srp_GotoOut;

typedef struct{
    BYTE RefType1;
    WORD No1;
}Srp_Print;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon1;

    BYTE RefType2;
    WORD No2;
    int ICon2;
    double FCon2;
    char TCon2[14];
    SString SCon2;
}Srp_SetParamIn;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon1;
    BYTE vType;//变量类型
}Srp_SetParamOut;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon1;
    BYTE RefType2;
    WORD No2;
}Srp_GetParamOut;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon1;
    BYTE RefType2;
    WORD No2;
}Srp_GetField;

typedef struct{
    BYTE RefType1;
    WORD No1;
    SString SCon1;
}Srp_PrepareSQL;

typedef struct{
    SString ID;
    int LGoTo;
}Srp_GoTo;

typedef struct{
    BYTE RefType1;
    WORD No1;
    BYTE Op;
    BYTE RefType2;
    WORD No2;
    int ICon;
    double FCon;
    char   TCon[14];
    SString SCon;
    SString ID;
    int LGoTo;
}Srp_IF;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon;
    WORD No2;
}Srp_SendPacket;

typedef struct{
    WORD No1;
    BYTE RefType2;
    WORD No2;
    int ICon2;
	WORD No3;
}Srp_RecvPacket;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon1;
	WORD No2;
}Srp_SqlOpen;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    WORD No2;
}Srp_GetFieldI;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    WORD No2;
}Srp_GetFieldS;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    WORD No2;
}Srp_GetFieldF;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    WORD No2;
}Srp_GetFieldT;


typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
}Srp_MoveNext;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
}Srp_Eof;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon1;
	WORD No2;
}Srp_SqlExec;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon1;
}Srp_SpExec;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    BYTE RefType2;
    WORD No2;
    int DCon2;
    BYTE InOut;
}Srp_SetSqlParamI;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    BYTE RefType2;
    WORD No2;
    SString SCon2;
    BYTE InOut;
}Srp_SetSqlParamS;

#define PARAM_IN  0
#define PARMA_OUT 1   
typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    BYTE RefType2;
    WORD No2;
    double FCon2;
    BYTE InOut;
}Srp_SetSqlParamF;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    BYTE RefType2;
    WORD No2;
    char TCon2[14];
    BYTE InOut;
}Srp_SetSqlParamT;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    WORD No2;
}Srp_GetSpOutI;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    WORD No2;
}Srp_GetSpOutS;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    WORD No2;
}Srp_GetSpOutF;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    WORD No2;
}Srp_GetSpOutT;

typedef struct{
    WORD No1;
}Srp_Now;

typedef struct{
    WORD No1;
    BYTE RefType2;
    WORD No2;
    int DCon2;
}Srp_DateAddDay;

typedef struct{
    WORD No1;
    BYTE RefType2;
    WORD No2;
    int DCon2;
}Srp_DateAddHour;

typedef struct{
    WORD No1;
    BYTE RefType2;
    WORD No2;
    int DCon2;
}Srp_DateAddMin;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_DatePartHour;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_DatePartMin;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_DatePartSec;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_DatePartDay;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_DatePartMonth;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_DatePartWeek;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_DatePartYear;

typedef struct{
    WORD No1;
    WORD No2;
    WORD No3;
}Srp_DateDiffDay;

typedef struct{
    WORD No1;
    WORD No2;
    WORD No3;
}Srp_DateDiffHour;

typedef struct{
    WORD No1;
    WORD No2;
    WORD No3;
}Srp_DateDiffMin;

typedef struct{
    WORD No1;
    WORD No2;
    WORD No3;
}Srp_DateDiffSec;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_StrLen;

typedef struct{
    WORD No1;
}Srp_StrTrimLeft;

typedef struct{
    WORD No1;
}Srp_StrTrimRight;

typedef struct{
    WORD No1;
}Srp_StrTrim;

typedef struct{
    BYTE RefType1;
    WORD No1;
    SString SCon1;
    BYTE RefType2;
    WORD No2;
    SString Scon2;
    WORD No3;
}Srp_StrReplace;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    BYTE RefType2;
    WORD No2;
    int DCon2;
    WORD No3;
    WORD No4;
}Srp_StrMid;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    BYTE RefType2;
    WORD No2;
    int DCon2;
    WORD No3;
}Srp_StrDel;

typedef struct{
    WORD No1;
    BYTE RefType2;
    WORD No2;
    SString SCon2;
}Srp_StrCat;

typedef struct{
    WORD No1;
}Srp_StrUpper;

typedef struct{
    WORD No1;
}Srp_StrLower;

typedef struct{
    BYTE RefType1;
    WORD No1;
    int DCon1;
    BYTE RefType2;
    WORD No2;
    SString SCon2;
    WORD No3;
    WORD No4;
}Srp_StrParse;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_I2S;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_F2S;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_T2S;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_S2I;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_S2F;

typedef struct{
    WORD No1;
    WORD No2;
}Srp_S2T;

typedef struct{
    BYTE RefType1;
    WORD No1;
    BYTE RefType2;
    WORD No2;
    double DCon;
    WORD No3;
}Srp_CmpD;

typedef struct{
    WORD No1;
    BYTE RefType2;
    WORD No2;
    char TCon[14];
    WORD No3;
}Srp_CmpT;

typedef struct{
    BYTE RefType1;
    WORD No1;

    BYTE RefType2;
    WORD No2;
	union{
		SString SCon;
		double DCon;
		char TCon[14];
	};
}Srp_Set;

typedef struct{
    BYTE RefType1;
    WORD No1;
    BYTE RefType2;
    WORD No2;
    double DCon;
}Srp_Add;

typedef struct{
    BYTE RefType1;
    WORD No1;
    BYTE RefType2;
    WORD No2;
    double DCon;
}Srp_Sub;

typedef struct{
    BYTE RefType1;
    WORD No1;
    BYTE RefType2;
    WORD No2;
    double DCon;
}Srp_Mul;

typedef struct{
    BYTE RefType1;
    WORD No1;
    BYTE RefType2;
    WORD No2;
    double DCon;
}Srp_Div;

typedef struct{
    BYTE RefType;
    WORD No;
}Srp_Push;

typedef struct{
    BYTE RefType;
    WORD No;
}Srp_Pop;

typedef struct{
    WORD iNo1;
    WORD iNo2;
    int ICon2;
    SString ID;
    int LGoTo;
}Srp_CondGoTo;

typedef struct{
    BYTE RefType1;
    WORD No1;//0-31 S变量,255-常量
    SString SCon1;
    BYTE RefType2;
    WORD No2;
    int ICon2;
	WORD No3;
}Srp_CallFunc;

typedef struct{
	BYTE RefType1;
	WORD No1;
	int ICon1;

	BYTE RefType2;
	WORD No2;
	int ICon2;

	WORD No3;
}Srp_CycPlay;

typedef struct{
    int LineNo;
    WORD CmdType;
    union{
        Srp_CallFunc callfunc;
        Srp_CondGoTo condgoto;
        Srp_Push push;
        Srp_Pop pop;
        Srp_Set _set;
        Srp_Add add;
        Srp_Sub sub;
        Srp_Mul mul;
        Srp_Div _div;
        Srp_CmpD cmpd;
        Srp_CmpT cmpt;
        Srp_I2S i2s;
        Srp_F2S f2s;
        Srp_T2S t2s;
        Srp_S2I s2i;
        Srp_S2F s2f;
        Srp_S2T s2t;
        Srp_StrLen strlen;
        Srp_StrTrimLeft strtrimleft;
        Srp_StrTrimRight strtrimright;
        Srp_StrTrim strtrim;
        Srp_StrReplace strreplace;
        Srp_StrMid strmid;
        Srp_StrDel strdel;
        Srp_StrCat strcat;
        Srp_StrUpper strupper;
        Srp_StrLower strlower;
        Srp_StrParse strparser;
        Srp_Now now;
        Srp_DateAddDay dateaddday;
        Srp_DateAddHour dateaddhour;
        Srp_DateAddMin dateaddmin;
        Srp_DatePartHour dateparthour;
        Srp_DatePartMin datepartmin;
        Srp_DatePartSec datepartsec;
        Srp_DatePartDay datepartday;
        Srp_DatePartMonth datepartmonth;
        Srp_DatePartWeek datepartweek;
        Srp_DatePartYear datepartyear;
        Srp_DateDiffDay datediffday;
        Srp_DateDiffHour datediffhour;
        Srp_DateDiffMin datediffmin;
        Srp_DateDiffSec datediffsec;
        Srp_SendPacket sendpacket;
        Srp_RecvPacket recvpacket;
        Srp_SqlOpen sqlopen;
        Srp_GetFieldI getfieldi;
        Srp_GetFieldS getfields;
        Srp_GetFieldT getfieldt;
        Srp_GetFieldF getfieldf;
        Srp_MoveNext movenext;
        Srp_Eof eof;
        Srp_SqlExec sqlexec;
        Srp_SpExec spexec;
        Srp_SetSqlParamI setsqlparami;
        Srp_SetSqlParamS setsqlparams;
        Srp_SetSqlParamT setsqlparamt;
        Srp_SetSqlParamF setsqlparamf;
        Srp_GetSpOutI getspouti;
        Srp_GetSpOutS getspouts;
        Srp_GetSpOutT getspoutt;
        Srp_GetSpOutF getspoutf;
        Srp_IF _if;
        Srp_GoTo _goto;
        Srp_PrepareSQL preparesql;
        Srp_SetParamIn setparamin;
        Srp_SetParamOut setparamout;
        Srp_GetParamOut getparamout;
        Srp_GetField    getfield;
        Srp_Print       print;
		Srp_GotoOut  gotoout;
		Srp_StartBill startbill;
		Srp_SetBillType setbilltype;
		Srp_SecBillBegin secbillbegin;
		Srp_RecFile recfile;
		Srp_Sleep  sleep;
		Srp_PlayTTS playtts;
		Srp_VerifyAccount verifyaccount;
		Srp_VerifyPassword verifypassword;
		Srp_CycPlay cycplay;
		Srp_SetSecPara setsecpara;
		Srp_RecFile2 recfile2;
		Srp_AddMusic addmusic;
		Srp_PlayDTMF playdtmf;
		Srp_SetCardPara setcardpara;
		Srp_ConnChan connchan;
		Srp_CheckStatus checkstatus;
		Srp_GetMeetMemberCnt getmeetmembercnt;
		Srp_KaLaOk kalaok;
		Srp_RemoveMusic removemusic;
		Srp_AuditMeet auditmeet;
        Srp_AddMusic2 addmusic2;
		Srp_PlayIndVocInMeet playindvocinmeet;
		Srp_PlayFileVocInMeet playfilevocinmeet;
		Srp_StopMeetPlayVoc   stopmeetplayvoc;
		Srp_SetSec   setsec;

		Srp_FindNumInMeet findnuminmeet;
		Srp_HavePreside  havepreside;

		Srp_SetDtmfStop setdtmfstop;

		Srp_PlayFile playfile;
		Srp_PlayIndex playindex;

		Srp_GetMeet getmeet;
		Srp_FindIdleMeetRoom findidlemeetroom;
		Srp_CheckTimeFormat checktimeformat;

		Srp_AllocRes  allocres;

		Srp_ListenMeet listenmeet;
		Srp_GetMeetPara getmeetpara;

		Srp_ExecIvr  execivr;

		Srp_DeleteMeet deletemeet;

		Srp_LeaveMeet leavemeet;

		Srp_UpdateField updatefield;
		
		Srp_FindNumInSystem  findnuminsystem;

		Srp_InTalkWithOut intalkwithout;

		Srp_PlayTTSInMeet playttsinmeet;

		Srp_GetCalled getcalled;

		Srp_GetSeatPara getseatpara;

		Srp_PlayIndex2  playindex2;

		Srp_SaveDtmf savedtmf;
    };
}Srp_Cmd1;

typedef struct{
	WORD CmdType;
    //录音文件名
    BYTE RefType1;
    BYTE No1;
    char SCon1[256];

    //中断方式
    BYTE RefType2;
    BYTE No2;
    char SCon2[12];

    //录音时间长度
    BYTE RefType3;
    BYTE No3;
    int ICon3;
    //0-成功;1-失败
    int Out[2];
}Cmd_Record;

typedef struct{
    WORD CmdType;

    //放音类型
    BYTE RefType1;
    BYTE No1;
    int ICon1;

    //放音内容
    BYTE RefType2;
    BYTE No2;
    char SCon2[256];
    //0-成功;1-失败
    int Out[2];
}Cmd_PlayTTS;

typedef struct{
    WORD CmdType;

    //语音索引号
    BYTE RefType1;
    BYTE No1;
    int ICon1;

    //超时时间
    BYTE RefType2;
    BYTE No2;
    int ICon2;
    //0-成功;1-失败
    int Out[2];
}Cmd_CycPlay;

//开始命令
typedef struct{
    WORD CmdType;
    int Out[1];
}Cmd_Start;

//号号通呼出命令
typedef struct{
    WORD CmdType;
	
	//主叫
    BYTE RefType1;
    BYTE No1;//主叫
    char SCon1[20];//主叫常量
	
	//被叫
    BYTE RefType2;
    BYTE No2;//被叫
    char SCon2[20];//被叫常量
    
	//呼出占用通道
    BYTE No3;//呼叫成功占用的通道号
	
	//呼出局向
	BYTE RefType4;
	BYTE No4;
	int ICon4;
	
    //等待铃声
    BYTE RefType5;
    BYTE No5;
    int  ICon5;
	char SCon5[128];
	
	//停止呼叫按键
	char SCon6[13];
	
	//停止呼叫按键存放变量
	BYTE No7;

	//呼出等待时间长短
	BYTE RefType8;
	BYTE No8;
	int  ICon8;
	
    //0-被叫应答,成功;1-无人接;2-被叫忙;
	//3-呼出失败;4-线路忙;5-空号;6-呼叫过程中被打断;7-呼出超时
    int Out[8];
}Cmd_CallOut2;

//数字中继呼出外线命令
typedef struct{
    WORD CmdType;

	//主叫
    BYTE RefType1;
    BYTE No1;//主叫
    char SCon1[20];//主叫常量

	//被叫
    BYTE RefType2;
    BYTE No2;//被叫
    char SCon2[20];//被叫常量
    
	//呼出占用通道
    BYTE No3;//呼叫成功占用的通道号

	//呼出局向
	BYTE RefType4;
	BYTE No4;
	int ICon4;

    //等待铃声
    BYTE RefType5;
    BYTE No5;
    int  ICon5;
	char SCon5[256];

	//停止呼叫按键
	char SCon6;

	//停止呼叫按键存放变量
	BYTE No7;

    //0-被叫应答，成功;1-无人接;2-被叫忙;
	//3-呼出失败;4-线路忙;5-空号;6-呼叫过程中被打断
    int Out[7];
}Cmd_CallOut;

//脚本命令
typedef struct{
    WORD CmdType;
    int CmdCnt;
    Srp_Cmd1* pCmdList;
    int Out[1];
}Cmd_Script;


//邀请人通话
typedef struct{
	WORD CmdType;
	//被邀请人通道存放变量
	int  No1;

	//邀请人号码
	int  No2;

	//邀请提示语音
	BYTE RefType3;
	int  No3;
	int  ICon3;

	//等待被邀请方按键等待时间
	BYTE RefType4;
	int No4;
	int ICon4;

	//等待音乐
	BYTE RefType5;
	int  No5;
	int  ICon5;
	char SCon5[256];
	//0-被邀请人同意 1-被邀请人不同意 2-对方超过时间没有按键
	int  Out[3];
}Cmd_Invite;

//和被邀请人通话
typedef struct{
	//被邀请人通道存放变量
	int  No1;
	//0-被邀请人挂机,被邀请人按#键结束通话,回到原来的会议房间
	int  Out[2];
}Cmd_TalkWithInvite;

//跳转命令
typedef struct{
	WORD CmdType;
	int GotoCmdNo;       
	char  GotoLab[128];//跳转标号
}Cmd_Goto;

//呼叫指定分机
typedef struct{
    WORD CmdType;
    //输入的内线号码存放的变量
    BYTE sNo1;

    ////等待应答的提示语音系统变量
    BYTE  RefType2;
    BYTE  No2;
    char  SCon2[256];
	int ICon2;
	BYTE  VocType;

    BYTE sNo3;//留言语音变量
    BYTE sNo4;//呼叫转移的分机号
    BYTE iNo1;//接通后被叫分机的通道号

    //被叫占线排队等待时间长度,ICon5=0表示不排队
    BYTE RefType5;
    BYTE iNo5;
    int ICon5;
    
    //振铃模式
    BYTE RefType6;
    BYTE No6;
    int ICon6;

    //lbout[0]-被叫应答,成功,lbout[1]-被叫忙,lbout[2]-被叫无人接听
    //lbout[3]--没有该分机号码,lbout[4]-分机处于留言状态,lbout[5]-分机被设置为转接状态
    int Out[6];
}Cmd_CallExt;

//呼叫座席
typedef struct{
     WORD CmdType;
     //等待提示音
     BYTE RefType1;
     BYTE No1;
     char SCon1[256];
	 int ICon1;
	 BYTE VocType;

     //呼叫模式
     BYTE RefType2;
     BYTE No2;
     int ICon2;

     //呼叫分机组号
     BYTE RefType3;
     BYTE No3;
     int ICon3;

     //等待接通时间
     BYTE RefType4;
     BYTE No4;
     int ICon4;

     //服务座席通道
     BYTE No5;

     //振铃模式
     BYTE RefType6;
     BYTE No6;
     int ICon6;

	 //呼叫分机技能
	 BYTE RefType7;
	 BYTE No7;
	 int ICon7;
	 
     //0-座席摘机;1-超时没有空闲座席;2-有空闲座席,但是座席超时没有摘机
	 int Out[3]; 
}Cmd_CallSeat;

//播放语音
#define VOC_FILE  0  //文件语音类型
#define VOC_INDEX 1  //索引语音类型
typedef struct {
     WORD CmdType;
     //拨放语音文件名
     BYTE RefType1;
     BYTE No1;
     char SCon1[256];	
	 int ICon1;

     //拨放语音文件类型；0-文件放音；1-索引放音
     BYTE RefType2;
     BYTE No2;
     int ICon2;

     //按键打断方式。N-不打断,?-任意键打端
     BYTE RefType3;
     BYTE No3;
     char SCon3[252];

     //播放的通道
     BYTE RefType4;
     BYTE No4;

	 //out0-正常播放结束，out1-播错误,out2-播放被按键打断
     int Out[3];
}Cmd_PlayVoc;

//和外线通话
typedef struct {
	WORD CmdType;

	//通话方外线通道号码
	BYTE RefType1;
	BYTE No1;
	int  ICon1;

	//通话类型
	BYTE RefType2;
	BYTE No2;
	int  ICon2;

	//会议房间号
	BYTE No3;

	//对方挂机
	int  Out[1];
}Cmd_TalkWithOut;

//座席通话
typedef struct {
     WORD CmdType;
     BYTE No1;//和外线通话内线通道
     
     //如果通话的过程中等待,等待语音编号
     BYTE RefType2;
     BYTE No2;
     int ICon2;

	 //如果通话的过程中创建了会议，会议房间号码存放的变量
	 BYTE No3;
     //0-主通道挂机;1-连接通道挂机;2-成功创建会议;3-创建会议失败
	 int Out[1];
}Cmd_Talk2;

//按键选择
typedef struct {
    WORD   CmdType;

	BYTE RefType1;
	BYTE No1;
	char SCon1[256];
	int ICon1;

     //拨放语音文件类型；0-文件放音;1-索引放音
     BYTE RefType2;
     BYTE No2;
     int ICon2;

     //重复输入次数
     BYTE RefType3;
     BYTE No3;
     int ICon3;

     //选择分支提示音播玩后等待延时的毫秒数
     BYTE RefType4;
     BYTE No4;
     int ICon4;

     //用户输入按键
     BYTE No5;
    int Out[13];
}Cmd_Digit;

//按键输入
typedef struct {
    WORD  CmdType;
	//拨放语音文件名
	BYTE RefType1;
	BYTE No1;
	char SCon1[256];
	int ICon1;

    //拨放语音文件类型；1-文件放音；2-索引放音
    BYTE RefType2;
    BYTE No2;
    int ICon2;

    //按键输入长度,=0根据结束按键来接收电话按键
    BYTE RefType3;
    BYTE No3;
    int ICon3;

    //结束按键
    BYTE RefType4;
    BYTE No4;
    char SCon4;

    //用户输入按键存放变量
    BYTE No5;

    //重复输入次数
    BYTE RefType6;
    BYTE No6;
    int ICon6;

    //选择分支提示音播玩后等待延时的毫秒数
    BYTE RefType7;
    BYTE No7;
    int ICon7;

	//中断输入按键
	BYTE RefType8;
	BYTE No8;
	char SCon8;

    int Out[3];//out[0]-正常输入按键,out[1]-规定时间没有输入,out[2]-用户中断输入
}Cmd_Input;

//创建会议
typedef struct {
    WORD CmdType;
    BYTE iNo;//申请到的会议房间号
	//会议房间人数
	BYTE RefType2;
	BYTE No2;
	int ICon2;
	//会议房间属性
	BYTE RefType3;
	BYTE No3;
	int  ICon3;
    //0-申请会议房间成功;1-申请会议房间失败
    int Out[2];
}Cmd_CreateMeet;

//加入会议
typedef struct {
	WORD CmdType;

	//加入会议房间号
	BYTE RefType1;
	BYTE No1;

	//音量
	BYTE RefType2;
	BYTE No2;
	int ICon2;

	//是否主持人通道
	BYTE IsPreside; //1-是 0-不是 

    //0-加入成功;1-加入失败
    int Out[2];
}Cmd_EnterMeet;

//会议进行
typedef struct {
    WORD CmdType;
    BYTE iNo;//会议房间号
	BYTE No2;//退出通道存放变量
    //0-退出会议 1-赶出会议
    int Out[2];
}Cmd_MeetTalk;

//静态命令参数
typedef struct {
    WORD CmdType;//命令类型
    //命令参数
    union{
		Cmd_CallSeat    cmd_CallSeat;
		Cmd_PlayVoc     cmd_PlayVoc;
		Cmd_Talk2       cmd_Talk2;
		Cmd_Start       cmd_Start;
		Cmd_Digit       cmd_Digit;
		Cmd_Input       cmd_Input;
		Cmd_CreateMeet  cmd_CreateMeet;
		Cmd_EnterMeet   cmd_EnterMeet;
		Cmd_MeetTalk    cmd_MeetTalk;
		Cmd_CallExt     cmd_CallExt;
		Cmd_Script      cmd_Script;
		Cmd_CallOut     cmd_CallOut;
		Cmd_Record      cmd_Record;
		Cmd_PlayTTS     cmd_PlayTTS;
		Cmd_CycPlay     cmd_CycPlay;
		Cmd_Goto        cmd_goto;
		Cmd_TalkWithOut cmd_TalkWithOut;
		Cmd_CallOut2    cmd_CallOut2;
		Cmd_Invite      cmd_Invite;
		Cmd_TalkWithInvite cmd_TalkWithInvite;
    };
    int stopflag;
}CmdPara;

//运行命令参数
typedef struct {
	//外线呼入时的运行状态机参数
	int  CmdNo;//当前通道执行的命令编号

	int   Step;//外线呼入内线当前通道命令执行的状态
	int   Step1;//外线呼入内线当前通道执行的状态1

	int  SrpStep;//对于某些不能够一个循环完成的脚本命令(callfunc,sqlopen...)等的执行状态
	int  SrpCmdPnt;//运行脚本命令时的命令指针


	//内线主动摘机的运行状态机参数
	int   InState;//大状态
	int   InStep;//小状态

	//状态机参数
	int  T1;  //定时器1
	int  T1_Start;//定时器1计时开始
	int  T2;  //定时器2
	int  T2_Start;//定时器2计时开始

	int  HookT_Start;
	int  RPara1;//需要保存运行时参数1
	int  RPara2;//需要保存运行时参数2
	int  RPara3;
	int  RPara4;
	int  RPara5;
	bool Stop;//运行暂停标记
	char SPara1[512];//运行时字符串s参数2
	char SPara2[64];

	//呼叫过程参数
	union{
		CallStat_WaitInQueue cs_waitinqueue;
		CallStat_TalkWithSeat cs_talkwithseat;
		CallStat_InCallOut cs_incallout; 
	};

	//通道当前接收的CALLOUT指令
	TcpPacket recvpak;

	//当前执行的脚本命令
	Srp_Cmd1 srp;

	//记账卡告警标记 0-不告警,1-需要告警
	int MoneyAlert;

	void ClearSPara()
	{
		memset(SPara1,0,512);
	}

	void AddSPara(char* str)
	{
		strcat(SPara1,str);
	}

	void SetSPara(char* str)
	{
		ClearSPara();
		AddSPara(str);
	}
}CmdRunTime;

#endif
