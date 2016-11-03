#ifndef _commpack_h_
#define _commpack_h_

#include <list>
#include <windows.h>
#include <time.h>
#include "basedef.h"

using namespace std;
//AAA�Ʒѽڵ�������
#define CODE_AAA    103
#define CODE_AUTOCALLOUT 104
#define	CODE_SYSMON 105

#define BROADALL  9999

//�Զ�������
enum{
	AC_NO_IDLELINE,    //û�п�������
	AC_NO_IDLE_SEAT,   //û�п��еĺ�����ϯ
	AC_SEAT_INTERUPT,  //���й������ж�
	AC_TALK_INTERUPT   //̸�������а����ж�
};


//��Ϣ����
enum{
	MT_INOUT     = 1,   //���������Ϣ
	MT_IVRLOG    = 1<<1,   //ivr������Ϣ
	MT_IVROK     = 1<<2,   //ivr��������������Ϣ
	MT_IVRERR    = 1<<3,   //ivr�������д�����Ϣ
	MT_SYSLOG    = 1<<4,  //ϵͳ��Ҫ��������ķ������������Ϣ,�ܽ��汾�ؼ�ؿ���
	MT_NOTIME    = 1<<5,   //����ʾʱ��,���ܱ��ؼ�ؿ���
	MT_SPEC      = 1<<6,
	MT_DBPAK     = 1<<7    //���ݿ⽻����
};
//����������С
#define   VOL_HIGH    0X1200
#define   VOL_NORMAL  0X800
#define   VOL_LOW     0X400
#define   VOL_SILENT  0

//�ƷѰ������ֶ�����
#define MAX_SECS  8

#define MAX_DATA_SIZE 2048

#define STREAM_BLOCK 1024

#define TIME_ALIVE 4000

#define DATA_SOCK_RECV   0  //����SOCKET
#define DATA_SOCK_SEND   1
#define STREAM_SOCK      2  //��SOCKET

//ͨѶ�ڵ�����
#define CT_IVREXEC     0  //ϵͳIVR������
#define CT_SEATIN      1  //������ϯ
#define CT_SUPERSEAT   2  //������ϯ

//ͨѶ������ʹ�õ����ݰ����ݰ�����
enum{
 MSG_COMM_LOGIN        ,  //ͨѶ�ڵ��¼    
 MSG_COMM_ALIVE        ,  //ͨѶ�ڵ�������Ϣ
 MSG_COMM_LOGINRES     ,  //ͨѶ�ڵ��¼���
 MSG_COMM_NOTIFY       ,  //ͨѶ�ڵ�����

 MSG_IVRKERN_DISCONN   ,   //IVR���ķ������Ͽ�����
 MSG_SEAT_DISCONN      ,   //��ϯ̨�Ͽ�����

 MSG_IVRDATA           ,  //IVR��������
 MSG_OP_RES            ,  //�������
//--�����--
 MSG_MEET_GETROOM      ,   //��ȡ������Ϣ
 MSG_MEET_ROOMINFO     ,   //10������Ϣ
 MSG_MEET_MEMBERINFO   ,   //��Ա��Ϣ
 MSG_MEET_MUSICINFO    ,   //����������Ϣ
 MSG_MEET_ONESAY       ,   //������ֻ����һ���˷���
 MSG_MEET_ALLSAY       ,   //�����д�Ҷ�������
 MSG_MEET_SILENT       ,   //��ֹ�����˷���(���ֳ���)
 MSG_MEET_REC          ,   //����¼��
 MSG_MEET_PLAYMUSIC    ,   //��������
 MSG_MEET_STOPMUSIC    ,   //ֹͣ��������  -ljq
 MSG_MEET_STOPREC      ,   //ֹͣ¼�� -ljq
 MSG_MEET_SETPARA      ,   //20���û������
 MSG_MEET_KICKOUT      ,   //�߳�����
 MSG_MEET_ADDMEMBER    ,   //��ӻ����Ա
 MSG_MEET_DEL_ROOM     ,   //����ɾ��
 MSG_MEET_DEL_MEMBER   ,   //��Ա�˳�
 MSG_MEET_MONITOR      ,   //-������
 MSG_MEET_OPRES        ,   //����������Ӧ��
 MSG_MEET_SETRECTIME   ,   //����¼��ʱ��

//--��ϯ��
 MSG_SEAT_LOGIN         ,   //��ϯ��¼
 MSG_SEAT_SETSRVSTATUS  ,   //���÷���״̬,��ͣ����/��������
 MSG_SEAT_LOGOUT        ,   //30��ϯ�ǳ�
 MSG_SEAT_MOVECALL      ,   //ת������
 MSG_SEAT_MOVETOMEET    ,   //����ת�Ƶ�����

 MSG_SEAT_SILENTCALL    ,   //silent����,��ϯ��resumecall֮ǰ���ܽ����������ߺ���
 MSG_SEAT_HOLDCALL      ,   //��������,��ϯ��resumecall֮ǰ���Խ����������ߺ���
 MSG_SEAT_GETHOLDLIST   ,   //�õ�����ͨ���б�
 MSG_SEAT_HOLDLEAVE     ,   //������·�仯��Ϣ
 MSG_SEAT_HOLDINFO      ,   //������·��Ϣ
 MSG_SEAT_RESUMECALL    ,   //�ָ�����
 MSG_SEAT_GETHOLD       ,   //ȡ����

 MSG_SEAT_CREATMEET     ,    //40��������
 MSG_SEAT_MOVETOIVR     ,    //��ϯ����ת�Ƶ�IVR
 MSG_SEAT_RECORD        ,    //¼����ǰͨ��
 MSG_SEAT_RECFILEOP     ,    //��ϯ¼������ ����/ɾ��/��ѯ 
 MSG_SEAT_RECVCALL      ,    //���������ֻ�����
 MSG_SEAT_CALLOUT       ,    //��ϯ����
 MSG_SEAT_SETSTATUS     ,    //���÷ֻ�״̬,����ת��/����/����״̬
 MSG_SEAT_CALLCOME      ,    //����
 MSG_SEAT_GETSEATINFO   ,    //ȡ��ȫ��ͨ����Ϣ
 MSG_SEAT_SEATINFO      ,    //��ϯ״̬�仯֪ͨ
 MSG_SEAT_OPRES         ,    //50��ϯ����������
 MSG_SEAT_LOGIN_RES     ,    //��ϯ��¼���
 MSG_SEAT_STATUSCHANGE  ,    //��ϯ״̬�仯��Ϣ֪ͨ
 MSG_SEAT_ENTERMEET     ,    //�������
 MSG_SEAT_AUDITMEET     ,    //��������
 MSG_SEAT_SENDSMS       ,    //��ϯ������Ϣ 
 MSG_SEAT_GETCALLQUEUE  ,    //ȡ��δ��,�ѽ�,�Ѳ��ĵ绰�б�
 MSG_SEAT_CALLQUEUE     ,    //���е绰��¼������Ϣ
 MSG_SEAT_MOVEIVRINFO   ,    //MOVEIVR��Ϣ

 MSG_SEATMAN_INSERTCALL ,
 MSG_SEATMAN_MONITOR    ,
 MSG_SEATMAN_RECORD     ,    //60

//--����ͳ�����ݰ�---
 MSG_CS_TALKWTIHSEAT   ,    //���ߺ���ϯͨ����¼
 MSG_CS_INCALLOUT      ,    //���ߺ������߼�¼
 MSG_CS_INMEET         ,    //�ڻ������м�¼
 MSG_CS_WAITINQUEUE    ,    //�ȴ����м�¼
 MSG_CS_MEETINOUTREC   ,    //������Ա�仯��¼
 MSG_CS_MAINBILL       ,    //������
 MSG_CS_SECBILL        ,    //IVR�������ɵķֶλ���

//--���м�ذ�
//����ƽ̨����
 MSG_MON_IVRRUNLOG     ,    //IVR���м�¼
 MSG_MON_CHANINFO      ,    //ͨ��״̬��Ϣ
 MSG_MON_SETMONTYPE,        //70
 MSG_MON_STOPMON,
 MSG_MON_STARTMON,
 MSG_MON_DISCONN,
 MSG_MON_LOGIN,

//�Զ��������������
 MSG_CALLOUT_TASK,         //�Զ���������
 MSG_CALLOUT_RES,          //�Զ�����������

//����Զ������
 MSG_CONSOLE_CMD,          //Զ������
 MSG_CONSOLE_RES,          //���
 MSG_CONSOLE_PUTDATA,      //Put����
 MSG_CONSOLE_GETDATA,      //Get����

//���˿��Ʒ����ݰ�
 MSG_CARD_MONEYALERT,      //�绰������澯
 MSG_CARD_NOMONEY,         //�绰���¶�ʹ�����

//2004��1��31�ղ����
 MSG_CALLSEAT_COME,        //����������
 MSG_CALLSEAT_LEAVE,       //�����뿪����
 MSG_GET_CALLSEAT,         //�õ�Ŀǰϵͳ�ĵȴ�����

//2004��2��5�ղ����Զ�������
 MSG_AUTOCALLOUT_QUERY_READYCNT, 
 MSG_AUTOCALLOUT_READYCNT,
 MSG_AUTOCALLOUT_TASK,
 MSG_AUTOCALLOUT_RES,

//2004��2��20�ղ���
 MSG_NONE                  //���ܵ������ݰ��Ѿ��������
};

//2004��2��24�ղ���

#define  PackName(a)  #a
 
inline char* GetPackName(int type)
{
	switch(type)
	{
	case MSG_COMM_LOGIN: return "MSG_COMM_LOGIN";  //ͨѶ�ڵ��¼    
 case MSG_COMM_ALIVE       : return "MSG_COMM_ALIVE";  //ͨѶ�ڵ�������Ϣ
 case MSG_COMM_LOGINRES     : return "MSG_COMM_LOGINRES";  //ͨѶ�ڵ��¼���
 case MSG_COMM_NOTIFY       : return "MSG_COMM_NOTIFY";  //ͨѶ�ڵ�����

 case MSG_IVRKERN_DISCONN   : return "MSG_IVRKERN_DISCONN";   //IVR���ķ������Ͽ�����
 case MSG_SEAT_DISCONN      : return "MSG_SEAT_DISCONN";   //��ϯ̨�Ͽ�����

 case MSG_IVRDATA           : return "MSG_IVRDATA";  //IVR��������
 case MSG_OP_RES            : return "MSG_OP_RES";  //�������
//--�����--
 case MSG_MEET_GETROOM      : return "MSG_MEET_GETROOM";   //��ȡ������Ϣ
 case MSG_MEET_ROOMINFO     : return "MSG_MEET_ROOMINFO";   //10������Ϣ
 case MSG_MEET_MEMBERINFO   : return "MSG_MEET_MEMBERINFO";   //��Ա��Ϣ
 case MSG_MEET_MUSICINFO    : return "MSG_MEET_MUSICINFO";   //����������Ϣ
 case MSG_MEET_ONESAY       : return "MSG_MEET_ONESAY";   //������ֻ����һ���˷���
 case MSG_MEET_ALLSAY       : return "MSG_MEET_ALLSAY";   //�����д�Ҷ�������
 case MSG_MEET_SILENT       : return "MSG_MEET_SILENT";   //��ֹ�����˷���(���ֳ���)
 case MSG_MEET_REC          : return "MSG_MEET_REC";   //����¼��
 case MSG_MEET_PLAYMUSIC    : return "MSG_MEET_PLAYMUSIC";   //��������
 case MSG_MEET_STOPMUSIC    : return "MSG_MEET_STOPMUSIC";   //ֹͣ��������  -ljq
 case MSG_MEET_STOPREC      : return "MSG_MEET_STOPREC";   //ֹͣ¼�� -ljq
 case MSG_MEET_SETPARA      : return "MSG_MEET_SETPARA";   //20���û������
 case MSG_MEET_KICKOUT      : return "MSG_MEET_KICKOUT";   //�߳�����
 case MSG_MEET_ADDMEMBER    : return "MSG_MEET_ADDMEMBER";   //��ӻ����Ա
 case MSG_MEET_DEL_ROOM     : return "MSG_MEET_DEL_ROOM";   //����ɾ��
 case MSG_MEET_DEL_MEMBER   : return "MSG_MEET_DEL_MEMBER";   //��Ա�˳�
 case MSG_MEET_MONITOR      : return "MSG_MEET_MONITOR";   //-������
 case MSG_MEET_OPRES        : return "MSG_MEET_OPRES";   //����������Ӧ��
 case MSG_MEET_SETRECTIME   : return "MSG_MEET_SETRECTIME";   //����¼��ʱ��
//--��ϯ��
 case MSG_SEAT_LOGIN         : return "MSG_SEAT_LOGIN";   //��ϯ��¼
 case MSG_SEAT_SETSRVSTATUS  : return "MSG_SEAT_SETSRVSTATUS";   //���÷���״̬,��ͣ����/��������
 case MSG_SEAT_LOGOUT        : return "MSG_SEAT_LOGOUT";   //30��ϯ�ǳ�
 case MSG_SEAT_MOVECALL      : return "MSG_SEAT_MOVECALL";   //ת������
 case MSG_SEAT_MOVETOMEET    : return "MSG_SEAT_MOVETOMEET";   //����ת�Ƶ�����
 case MSG_SEAT_SILENTCALL    : return "MSG_SEAT_SILENTCALL";   //silent����,��ϯ��resumecall֮ǰ���ܽ����������ߺ���
 case MSG_SEAT_HOLDCALL      : return "MSG_SEAT_HOLDCALL";   //��������,��ϯ��resumecall֮ǰ���Խ����������ߺ���
 case MSG_SEAT_GETHOLDLIST   : return "MSG_SEAT_GETHOLDLIST";   //�õ�����ͨ���б�
 case MSG_SEAT_HOLDLEAVE     : return "MSG_SEAT_HOLDLEAVE";   //������·�仯��Ϣ
 case MSG_SEAT_HOLDINFO      : return "MSG_SEAT_HOLDINFO";   //������·��Ϣ
 case MSG_SEAT_RESUMECALL    : return "MSG_SEAT_RESUMECALL";   //�ָ�����
 case MSG_SEAT_GETHOLD       : return "MSG_SEAT_GETHOLD";   //ȡ����

 case MSG_SEAT_CREATMEET     : return "MSG_SEAT_CREATMEET";    //40��������
 case MSG_SEAT_MOVETOIVR     : return "MSG_SEAT_MOVETOIVR";    //��ϯ����ת�Ƶ�IVR
 case MSG_SEAT_RECORD        : return "MSG_SEAT_RECORD";    //¼����ǰͨ��
 case MSG_SEAT_RECFILEOP     : return "MSG_SEAT_RECFILEOP";    //��ϯ¼������ ����/ɾ��/��ѯ 
 case MSG_SEAT_RECVCALL      : return "MSG_SEAT_RECVCALL";    //���������ֻ�����
 case MSG_SEAT_CALLOUT       : return "MSG_SEAT_CALLOUT";    //��ϯ����
 case MSG_SEAT_SETSTATUS     : return "MSG_SEAT_SETSTATUS";    //���÷ֻ�״̬,����ת��/����/����״̬
 case MSG_SEAT_CALLCOME      : return "MSG_SEAT_CALLCOME";    //����
 case MSG_SEAT_GETSEATINFO   : return "MSG_SEAT_GETSEATINFO";    //ȡ��ȫ��ͨ����Ϣ
 case MSG_SEAT_SEATINFO      : return "MSG_SEAT_SEATINFO";    //��ϯ״̬�仯֪ͨ
 case MSG_SEAT_OPRES         : return "MSG_SEAT_OPRES";    //50��ϯ����������
 case MSG_SEAT_LOGIN_RES     : return "MSG_SEAT_LOGIN_RES";    //��ϯ��¼���
 case MSG_SEAT_STATUSCHANGE  : return "MSG_SEAT_STATUSCHANGE";    //��ϯ״̬�仯��Ϣ֪ͨ
 case MSG_SEAT_ENTERMEET     : return "MSG_SEAT_ENTERMEET";    //�������
 case MSG_SEAT_AUDITMEET     : return "MSG_SEAT_AUDITMEET";    //��������
 case MSG_SEAT_SENDSMS       : return "MSG_SEAT_SENDSMS";    //��ϯ������Ϣ 
 case MSG_SEAT_GETCALLQUEUE  : return "MSG_SEAT_GETCALLQUEUE";    //ȡ��δ��,�ѽ�,�Ѳ��ĵ绰�б�
 case MSG_SEAT_CALLQUEUE     : return "MSG_SEAT_CALLQUEUE";    //���е绰��¼������Ϣ
 case MSG_SEAT_MOVEIVRINFO:return "MSG_SEAT_MOVEIVRINFO";

 case MSG_SEATMAN_INSERTCALL : return "MSG_SEATMAN_INSERTCALL";
 case MSG_SEATMAN_MONITOR    : return "MSG_SEATMAN_MONITOR";
 case MSG_SEATMAN_RECORD     : return "MSG_SEATMAN_RECORD";    //60
//--����ͳ�����ݰ�---
 case MSG_CS_TALKWTIHSEAT   : return "MSG_CS_TALKWTIHSEAT";    //���ߺ���ϯͨ����¼
 case MSG_CS_INCALLOUT      : return "MSG_CS_INCALLOUT";    //���ߺ������߼�¼
 case MSG_CS_INMEET         : return "MSG_CS_INMEET";    //�ڻ������м�¼
 case MSG_CS_WAITINQUEUE    : return "MSG_CS_WAITINQUEUE";    //�ȴ����м�¼
 case MSG_CS_MEETINOUTREC   : return "MSG_CS_MEETINOUTREC";    //������Ա�仯��¼
 case MSG_CS_MAINBILL       : return "MSG_CS_MAINBILL";    //������
 case MSG_CS_SECBILL        : return "MSG_CS_SECBILL";    //IVR�������ɵķֶλ���
//--���м�ذ�
//����ƽ̨����
 case MSG_MON_IVRRUNLOG     : return "MSG_MON_IVRRUNLOG";    //IVR���м�¼
 case MSG_MON_CHANINFO      : return "MSG_MON_CHANINFO";    //ͨ��״̬��Ϣ
 case MSG_MON_SETMONTYPE: return "MSG_MON_SETMONTYPE";        //70
 case MSG_MON_STOPMON: return "MSG_MON_STOPMON";
 case MSG_MON_STARTMON: return "MSG_MON_STARTMON";
 case MSG_MON_DISCONN: return "MSG_MON_DISCONN";
 case MSG_MON_LOGIN: return "MSG_MON_LOGIN";

//�Զ��������������
 case MSG_CALLOUT_TASK: return "MSG_CALLOUT_TASK";         //�Զ���������
 case MSG_CALLOUT_RES: return "MSG_CALLOUT_RES";         //�Զ�����������

//����Զ������
 case MSG_CONSOLE_CMD: return "MSG_CONSOLE_CMD";          //Զ������
 case MSG_CONSOLE_RES: return "MSG_CONSOLE_RES";          //���
 case MSG_CONSOLE_PUTDATA: return "MSG_CONSOLE_PUTDATA";      //Put����
 case MSG_CONSOLE_GETDATA: return "MSG_CONSOLE_GETDATA";      //Get����
//���˿��Ʒ����ݰ�
 case MSG_CARD_MONEYALERT: return "MSG_CARD_MONEYALERT";      //�绰������澯
 case MSG_CARD_NOMONEY: return "MSG_CARD_NOMONEY";          //�绰���¶�ʹ�����
 case MSG_CALLSEAT_COME: return "MSG_CALLSEAT_COME";        //����������
 case MSG_CALLSEAT_LEAVE: return "MSG_CALLSEAT_LEAVE";       //�����뿪����
 case MSG_GET_CALLSEAT: return "MSG_GET_CALLSEAT";//�õ�Ŀǰϵͳ�ĵȴ�����	

 case MSG_AUTOCALLOUT_QUERY_READYCNT: return "MSG_AUTOCALLOUT_QUERY_READYCNT"; 
 case MSG_AUTOCALLOUT_READYCNT: return "MSG_AUTOCALLOUT_READYCNT"; 
 case MSG_AUTOCALLOUT_TASK: return "MSG_AUTOCALLOUT_TASK"; 
 case MSG_AUTOCALLOUT_RES: return "MSG_AUTOCALLOUT_RES"; 
}
	return "MSG_NONAME";
}

//���ݿ�ͨѶ����ʹ�����ݰ�
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
 
 PAK_DBCFG,                //���ݿ���������������������Ϣ
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

//�Զ�����UDP����ʹ�õ�ͨѶ��
//#define UDP_CALLOUTTASK        66
//#define UDP_CALLOUTRES         67

#define PARAM_IN   0
#define PARAM_OUT  1

//�绰��������Ϣ
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

//Զ�̵���
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

//-------------���й��̼�¼------------------------
//������
typedef struct {
	char CallID[25];   //����ID����
	char Caller[20];   //���к���
	char Called[20];   //���к���
	char InLineNo[5]; //���ߺ���,����ʹ�����ߺ��������ߺ���
	int  DevChan;      //ռ���豸ͨ��
	time_t StartTime;  //��ʼʱ��
	time_t EndTime;    //����ʱ��
	BYTE  CallDirect;  //ͨ������  0-���롡1-����
}CallStat_MainBill;

//ivr�����趨�ֶλ���
typedef struct{
	char    CallID[25]; //����ID����
	char    SPara0[64]; //�ַ�����
	char    SPara1[64]; //�ַ�����
	char    SPara2[64]; //�ַ�����
	char    SPara3[64]; //�ַ�����
	time_t  StartTime;  //��ʼʱ��
	time_t  EndTime;    //����ʱ��
}CallStat_SecBill;

//
enum{
	WAIT_NOIDLESEAT, //����û�п��з�����ϯ
	WAIT_OK,         //��ϯժ��
	WAIT_NOTOFFHOOK, //��ϯ��ʱû��ժ��
	WAIT_USERHOOK    //�ͻ�û�еȵ���ϯժ���͹һ�
};

//���ߺ�����еȴ�
typedef struct{
	char   CallID[25];      //����ID����
	char   Caller[20];      //����ȴ����ߺ���
	char   Called[20];      //���뱻�к���
	DWORD  WaitGroup;       //�ȴ��ķ������
	DWORD  WaitTechs;       //�ȴ��ļ��ܺ���
	time_t WaitStartTime;   //��ʼ�ȴ�ʱ��
	time_t WaitEndTime;     //�����ȴ�ʱ��
	char   SeatNo[5];       //�ȴ�������ϯ����
	BYTE   WaitRes;         //�ȴ����;
}CallStat_WaitInQueue;

//���ߺ���ϯͨ��
typedef struct  {
	char   CallID[25];      //����ID����
	char   Caller[20];       //�������ߺ���
	char   Called[20];       //���뱻�к���
	char   SeatNo[5];        //ͨ����ϯ����
	int    SeatDevChan;      //ͨ����ϯͨ��
	char   InLineNo[8];      //ͨ�����ߺ���
	time_t TalkStartTime;  //ͨ����ʼʱ��
	time_t TalkEndTime;    //ͨ������ʱ��
}CallStat_TalkWithSeat;

//���ߺ�������
typedef struct  {
	char   CallID[25];      //����ID����
	char   SeatNo[5];        //�������ߵ���ϯ����
	char   Caller[20];       //ϵͳ����ʹ�õ�����
	char   Called[20];       //���ߺ�������
	time_t TalkStartTime;  //ͨ����ʼʱ��
	time_t TalkEndTime;    //ͨ������ʱ��
	char   RecFileName[100]; //ͨ��¼���ļ�
}CallStat_InCallOut;

//���߻������ڻ�����
typedef struct{
	char   CallID[25];      //����ID����
	char   Num[20];         //����

	DWORD  RoomNo;          //���鷿�����
	time_t EnterMeetTime;  //������鷿��
	time_t LeaveMeetTime;  //�뿪����ʱ��
}CallStat_InMeet;

//���������仯��¼
typedef struct{
	char   CallID[25];      //����ID����
	int    RoomNo;            //���鷿�����
	int    MemberCnt;         //��������
	char   Num[20];         //����
	BYTE   Action;           //1-�������;0-�뿪����
	time_t ActTime;        //����ʱ��
}CallStat_MeetInOutRec;

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

//���������
typedef struct{
	int  RecNo;
	char Caller[20];
	char Called[20];
	int  Dpc;                  //��������
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

//���������
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
	int  MsgType;        //IVR Run Log��� 
	char Msg[256];       //Log��Ϣ
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

//��ϯ̨�Ͽ�������Ϣ
typedef struct{
	int code;
}Seat_DisConn;

//Data
typedef struct{
	DWORD   Code;//�ڵ���
	char    PassWord[20];//��������
	DWORD   Type;//0-����socket,1-��socket
	DWORD   CodeType;//�ڵ�����  
}Comm_LogIn;

enum{
	COMM_LOGINOK,     //�ɹ�
	COMM_CODE_ERROR,  //CODEԽ��
	COMM_PASS_ERROR,  //�������
	COMM_CODE_LOGINED //CODE�Ѿ�ռ��
};
typedef struct{
	int Res;//��¼���;0-;1-�������;2-�ڵ��Ų�����;3-�ڵ����Ѿ���ʹ��
}Comm_LogInRes;

typedef struct{
	char Msg[256];
}Comm_Msg;

typedef struct{
	int  Code;//�ڵ���
	char Des[128];//�ڵ�����
}Comm_CodeInfo;

typedef struct{
	BYTE Status;//0-����;1-������
}Comm_CodeStatus;

//*******�������ݰ�*******
typedef struct{
	int RoomNo;
	time_t StartTime;
	time_t EndTime;
}Meet_SetRecTime;

typedef struct{
	int EngageCnt;//Ԥ����������
    int RoomNo;//����������
	int Engaged;//�÷����Ƿ�Ԥ�� 0-û��;1-Ԥ��
	int RecFlag;//�Ƿ�¼�����
}Meet_Mdy_Room;

typedef struct{
	int RoomNo;//���鷿�����
}Meet_Del_Room;

typedef struct{
	int    RoomNo;
	int    VocChan;//�λ��ߵ�ͨ�����
	char   Num[20];
}Meet_Del_Member;


typedef struct{
	int  MemberCnt;//���䵱ǰ����
	int  RoomSize;//�����С
    int  RoomNo;//����������
	int  RecFlag;//¼����� 1-��¼��;0-ֹͣ¼��
	char RoomName[128];//��������
	int  RoomType;//��������
	char RoomTypeName[128];//��������
	time_t RoomCreateTime;//���鴴��ʱ��
	int  RoomAttr;//��������.��������|(¼��/����)|����
	time_t SetStartRecTime;
	time_t SetEndRecTime;
}Meet_RoomInfo;

typedef struct{
	int     RoomNo;//���������� 
    int     VocChan;//�λ��ߵ�ͨ�����
	char    Num[16];//�λ�ͨ������
	int     Type;//����ͨ������  0-��ʽ 1-���� 2-������
    time_t  EnterTime;//��������ʱ��
    int     InGain;//��������(0--0x8000) (0x1000��ʾ0dB,�Ƽ�ʹ��0x800(-6dB))
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
	int MusicInd;//��������
	char MusicName[128];//��������
}Meet_MusicInfo;

typedef struct{
	int RoomNo;   //������鷿�����
	int MusicInd; //������������
	int Volume;   //���� 
}Meet_PlayMusic;

typedef struct{
    int RoomNo;
}Meet_StopMusic;

typedef struct{
	int RoomNo;
    int VocCh;
	int Type;     //����ͨ������  0-��ʽ 1-���� 2-������
	int Volume;   //���� 
}Meet_SetPara;

typedef struct{
	int RoomNo;
	int KickOutChan;
}Meet_KickOut;

typedef struct{
	int RoomNo;
	int NumType;  //�������� 0-����;1-��ϯ
	int MeetType; //�������� 0-��ʽ��Ա;1-��������
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
	char num[20];//����ʹ�õĺ��룬�����Ƿֻ�������
	int  RoomNo;//�������鷿�����
}Meet_Monitor;

enum{
 OPRES_SETMEETPARA_FAIL   ,   //�ı�������ʧ��
 OPRES_SETMEETPARA_OK     ,   //�ı��������ɹ�
 OPRES_CALLOUTMEMBER_OK   ,   //���м������ɹ� 
 OPRES_CALLOUTMEMBER_FAIL ,   //���м������ʧ��
 OPRES_KICKOUT_OK         ,   //���˳ɹ�
 OPRES_KICKOUT_FAIL       ,   //����ʧ��
 OPRES_PLAYMUSIC_OK       ,   //�������ֳɹ�
 OPRES_PLAYMUSIC_FAIL        //��������ʧ��
};

typedef struct{
	int  OpRes;    //�������ֵ
	char Msg[256]; //�����������
}Meet_OpRes;

//----------------��ϯ��Ϣ---------------------
#define SEAT_OPRES_CREATEMEET_OK    1  //��������ɹ�
#define SEAT_OPRES_CREATEMEET_FAIL  2  //��������ʧ��
#define SEAT_OPRES_ENTERMEET_FAIL   3  //��ӻ����Աʧ��
#define SEAT_OPRES_SEAT_NOT_OFFHOOK 4  //��ϯû��ժ��
#define SEAT_OPRES_LOGOUT_OK        5  //LOGOUT OK

//��ϯ�������
typedef struct{
	int  res;
	char msg[128];
}Seat_OpRes;

typedef struct{
	char SeatNo[8];
	char SeatPass[8];
	char InLine[8];
}Seat_LogIn;

//��¼������Ϣ
#define	ST_LOGIN_OK               0              //��¼�ɹ�
#define ST_LOGIN_EXT_ERR          1              //�ֻ��������
#define ST_LOGIN_EXT_NOT_PERMIT   2              //���Ų��ڷֻ������¼�б���
#define ST_LOGIN_PASS_ERR         3              //�����������
#define ST_LOGIN_ALREADY_LOGIN    4              //�ù����Ѿ���¼
typedef struct{
	int  LogInRes;
	int  Role;          //0-�೤,1-��ͨ
	char err[128];   
}Seat_LogIn_Res;

typedef struct{
	char InLineNo[8];
    int  SrvStatus;     //����״̬ 1-ʾæ,0-ʾ��
}Seat_SetSrvStatus;

typedef struct{
	char SeatNo[8];
	char SeatPass[8];
	char InLineNo[8];
}Seat_LogOut;

typedef struct{
	char InLineNo[8];
	int  MoveType;//0-���ߣ�1����
	char MoveNum[20];
}Seat_MoveCall;

typedef struct{
	WORD HoldChan;    //������ͨ�����
	char Num[20];     //������ͨ���������
	time_t StartHoldTime;  //�����ֿ�ʼʱ��
	WORD HoldMeInChan;     //�����ҵ�ͨ��
	char HoldMeNum[20];    //�����ҵ�ͨ������
	char HoldMeSeatName[20];  //����ͨ������ϯ����
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
    char InLineNo[8]; //����ͨ���ָ��ķֻ�����
	char RestoreLineNo[8];//�ָ��ķֻ�����
}Seat_ResumeCall;

typedef struct  {
	char InLineNo[8];
	WORD HoldChan;
}Seat_GetHold;


typedef struct{
	char InLineNo[8];
	int  MoveIvrNo;  //ת��IVR���
	char S0[64];     //ִ��ǰ����
	char S1[64];     //ִ��ǰ����
	char S2[64];     //ִ��ǰ����
	char S3[64];     //ִ��ǰ����
}Seat_MoveToIvr;

typedef struct{
	int MoveIvrInd;
	char MoveIvrName[256];
}Seat_MoveIvrInfo;

typedef struct{
	char InLineNo[8]; //���ߺ���
	int  RoomNo;      //�������
	int  Chan;        //ת��ͨ������
}Seat_MoveToMeet;


typedef struct{
	int InCnt;             //��������
	int LogicChan;         //�����߼�ͨ����
	
	int  Group;            //�����
	char GroupName[20];    //��������
	char InLineNo[8];      //���ߺ���
	char LogInSeatName[8]; //��¼��������
	char LogInSeatNo[8];   //����
	int  LineStatus;       //��·״̬
	int  LogStatus;        //ǩ��״̬
	char TalkWithNum[20];  //ͨ��������
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
    int Status;//�ֻ�״̬:0-����;1-����;2-����ת��
	int Numtype;//0-���ߣ�1-����
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
	int  Chan;  //����ͨ������
	char InLineNo[8];//���ߺ���
	char CallerNum[20];//�������
	char CalledNum[20];//���к���
	char MidNum[20];//ԭ����
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


//֪ͨ��Ϣ
#define NT_BUSY           0//ͨѶ�ڵ�Զ����ڽ���һ���ļ����䣬���ڲ��ܽ����ļ��������
#define NT_READY          1//���Ѿ�׼����,���Կ�ʼ�����ļ�
#define NT_CRC_ERROR      2//�����͵�CRC����
#define NT_STREAM_RECV_OK 3//��������ȷ������CRCУ��Ҳ��ȷ
#define NT_NOTONLINE      4//�Է�ͨѶ�ڵ�Ŀǰ������

typedef struct{
	DWORD Event;//֪ͨ�¼�
	DWORD Para;//����
	char  Msg[256];//֪ͨ����
}Comm_Notify;

typedef struct{
	int chan;
	char Data[256];
}Msg_IvrData;



typedef struct{
	int Chan;                  //ͨ��
	char Caller[20];           //����
	time_t  CallSeatTime;      //�������ʱ��
	int Group;                 //�ȴ�����
	int Tech;                  //�ȴ�����
}Msg_CallSeat_Come;

//�뿪�������
enum{
	CALLSEAT_TALK,             //����ϯͨ��
	CALLSEAT_NOTACK,           //�ҵ�������ϯ��������ϯû��ժ��
	CALLSEAT_TIMEOUT,          //����ʱ��û�п�����ϯ
	CALLSEAT_RING			   //���嵱ǰ��ϯ
};

typedef struct{
	int Chan;                  //ͨ��
	int LeaveRes;              //�뿪���
	time_t RingTime;              //����ʱ��
}Msg_CallSeat_Leave;

//��ѯ�ƶ�����Ŀ��к�����ϯ����
typedef struct{
	int Group;                //��ѯ�ķ���
}AutoCallOut_Query_ReadyCnt;

//���ؿ��к�����ϯ����
typedef struct{
	int Group;
	int Cnt;
}AutoCallOut_ReadyCnt;

//��������
typedef struct{
	int  RecID;
	char Caller[20];
	char Called[20];
	int  DpcNo;
	int	 IvrHnd;
	int  Group;
}AutoCallOut_Task;

//��������Ľ��
typedef struct{
	int  RecID;
	int  CallRes;
	int  SeatChan;
	char InLine[8];
	char SeatNo[8];
	char SeatKey;  
}AutoCallOut_Res;

//������߶����ݴ���Ч�ʵĿ���,������һ�ɲ��ö����ȵ�
//���ݰ�.���ݳ���4�ֽڵ���������
typedef struct tagTcpPacket{
	DWORD HeadTag;//=0xeffffffe
	DWORD SrcCode;//Դ����
	DWORD DesCode;//Ŀ�Ĵ���
	DWORD PackType;//������
	DWORD DesGrp;//Ŀ�ķ������,0-����ָ��DesCode,0xffffffff-���͵����нڵ�,����-ָ������
	             //��ϯ�������=1
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
	BYTE    BillType;//�Ʒ�����
	BYTE    CardFlag;//���Ʒ�:0-û��ʹ�ÿ�,1-���뿨
	time_t StartTime;//�ֶμƷѿ�ʼ
	time_t EndTime;//�ֶμƷѽ���
	BYTE    SecType;//�ֶ�����
	int    IPara1;//���β���1
	int    IPara2;//���β���2
	char   SPara1[20];//�ַ�����
	float  Fee;
}SecBill;
typedef struct{
	char  CallId[25];// ����ID
	BYTE  BillType;//�Ʒ�����
	char  FeeNum[21];//�ƷѺ���
	
	char  Caller[20];
	char  Called[20];
	time_t StartTime;// ��ʼ�Ʒ�ʱ��
	time_t EndTime;// �����Ʒ�ʱ��
	
	BYTE CallType;//��������
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
