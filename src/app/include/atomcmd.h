#ifndef _atomcmd_h_
#define _atomcmd_h_
#include <list>
#include <time.h>
#include "commpack.h"

using namespace std;
//�ַ����������ֵ
#define MAX_SCONBUF  4096*4
//�����ַ��������ֵ
#define MAX_SCONLEN  512

//TTS����
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
//���ݿ����GetField�ȴ�ʱ��(����)
#define TIME_DBOP  2000
#define SCON 255
//�ű�����ṹ
#define LT  0
#define GT  1
#define LE  2
#define GE  3
#define EQ  4

#define WAIT_TRIGGER        0   //�ȴ�ͨ������״̬
#define DMANALOG_WAITHOOK   1   //DMPCIģ�⿨��׼������״̬,DMPCIժ���͹һ�֮����Ҫ����1.5���ӵ�ʱ����
//-----------------��������ժ����״̬
#define INLINE_SIGNAL       2   //����ժ�������ź���
#define INLINE_BUSY         3   //�ź������Ž���û���κ���Ч����,��ʼ����æ��
#define INLINE_RECVDTMF     4   //�����û�����״̬

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
#define CMD_TALKWITHOUT    55   //������ͨ��
#define CMD_CALLOUT2       56
#define CMD_PLAYVOC2       57   //����ͨ��ͬʱ����
#define CMD_INVITE         58   //����һ���ڻ����е���ͨ��
#define CMD_TALKWITHINVITE 59   //�ͱ��������ͨ��

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
//�ַ�����ָ��ṹ
typedef struct{
    WORD StartPos;
    WORD Len;
}SString;

typedef struct{
	WORD No1;
}Srp_SaveDtmf;


typedef struct{
	//�����ļ�������
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
	//�����
	BYTE RefType1;
	WORD No1;
	int  ICon1;

	//��������
	BYTE RefType2;
	WORD No2;
	SString SCon2;

	//��������
	BYTE RefType3;
	WORD No3;
	int ICon3;
}Srp_PlayTTSInMeet;

typedef struct{
	WORD No1;//ͨ����������ͨ��
}Srp_InTalkWithOut;

typedef struct{
	BYTE RefType1;
	WORD No1;
	SString SCon1;

	WORD No2;
}Srp_FindNumInSystem;

//�����ֶ�
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

//�뿪����
typedef struct{
	BYTE RefType1;
	WORD No1;
}Srp_LeaveMeet;

//ɾ������
typedef struct{
	WORD No1;
}Srp_DeleteMeet;

//ִ��IVR����
typedef struct{
	BYTE RefType1;
	WORD No1;
	int  ICon1;
}Srp_ExecIvr;
//ȡ�û������
typedef struct{
	char GetType[10];
	
	//����
	BYTE RefType1;
	WORD No1;

	//����ֵ
	BYTE RefType2;
	WORD No2;
}Srp_GetMeetPara;

//��������
typedef struct{
	//���鷿�����
	BYTE RefType1;
	WORD No1;

	//������
	WORD No2;
}Srp_ListenMeet;

//������Դ
typedef struct{
	//������Դ����
	BYTE RefType1;
	WORD No1;
	int  ICon1;

	//������
	WORD No2;
}Srp_AllocRes;


//�������ʱ���ʽ
typedef struct{
	//����ʱ���ַ���
	WORD No1;
	//�������
	WORD Type;
	//����� 0-����,1-��ȷ
	WORD No2;
}Srp_CheckTimeFormat;

//��ϵͳ��Ѱ���п���λ�õķ���
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

//�õ�ָ����ŵĻ��鷿��ֵ
typedef struct{
	//������
	BYTE RefType1;
	WORD No1;
	int  ICon1;
	//ȡ�õķ������
	WORD No2;
}Srp_GetMeet;
//�����ļ�����
typedef struct{
	//�����ļ�����
	BYTE RefType1;
	WORD No1;
	SString SCon1;
	//���Ž��0-ok,1-fail,2-dtmfstop
	WORD No2;
}Srp_PlayFile;

//������������
typedef struct{
	//�����ļ�������
	BYTE RefType1;
	WORD No1;
	int  ICon1;
	//���Ž��0-ok,1-fail,2-dtmfstop
	WORD No2;
}Srp_PlayIndex;
//���ð������
typedef struct{
	//�жϰ���
	BYTE RefType1;
	WORD No1;
	SString SCon1;
}Srp_SetDtmfStop;

//�жϻ������Ƿ���������
typedef struct  {
	//���鷿�����
	BYTE RefType1;
	WORD No1;
	int  ICon1;
	//�жϽ��0-û��,1-��
	WORD No2;
}Srp_HavePreside;

//���Һ����Ƿ��ڻ��鷿����
typedef struct{
	//��ѯ�绰����
	BYTE RefType1;
	WORD No1;
	SString  SCon1;

	BYTE RefType2;
	WORD No2;
	int  ICon2;
	//���ص����ڷ������
	WORD No3;

	//���ص�ͨ������
	WORD No4;
}Srp_FindNumInMeet;

//���÷ֶβ���
typedef struct{
	//��������
	BYTE RefType1;
	WORD No1;
	int  ICon1;

	//�ַ�����ֵ
	BYTE RefType2;
	WORD No2;
	SString SCon2;
}Srp_SetSec;

//�����в�����������
typedef struct{
	//���鷿�����
	BYTE RefType1;
	WORD No1;

	//��������
	BYTE RefType2;
	WORD No2;
	int ICon2;

	//ѭ�����ű��
	BYTE RefType3;
	WORD No3;
	int ICon3;
}Srp_PlayIndVocInMeet;

//�����в����ļ�����
typedef struct{
	//���鷿�����
	BYTE RefType1;
	WORD No1;

	//�ļ�����
	BYTE RefType2;
	WORD No2;
	SString SCon2;

	//����
	BYTE RefType3;
	WORD No3;
	int ICon3;

	//ѭ�����ű��
	BYTE RefType4;
	WORD No4;
	int ICon4;
}Srp_PlayFileVocInMeet;

//ֹͣ�����в�������
typedef struct{
	//���鷿�����
	BYTE RefType1;
	WORD No1;

	//ֹͣ������������
	BYTE RefType2;
	WORD No2;
	int ICon2;
}Srp_StopMeetPlayVoc;

//��ӻ��鱳���ļ�����
typedef struct{
	//�����
	BYTE RefType1;
	WORD No1;
	int ICon1;

	//��������
	BYTE RefType2;
	WORD No2;
	SString SCon2;

	//����
	BYTE RefType3;
	WORD No3;
	int ICon3;
}Srp_AddMusic2;

//��������
typedef struct{
	BYTE RefType1;
	WORD No1;
	int ICon1;
}Srp_AuditMeet;

//ȥ����������
typedef struct{
    BYTE RefType1;
    WORD No1;
    int ICon1;
}Srp_RemoveMusic;

typedef struct{
    //¼���ļ�����
    BYTE RefType1;
    WORD No1;
    SString SCon1;

    //������������
    BYTE RefType2;
    WORD No2;
    SString SCon2;

    //������������
    BYTE RefType3;
    WORD No3;
    int ICon3;

    //¼���жϰ���
    BYTE RefType4;
    WORD No4;
    SString SCon4;

    //¼��ʱ�䳤��
    BYTE RefType5;
    WORD No5;
    int ICon5;

    //¼�����
    WORD No6;
}Srp_KaLaOk;

typedef struct{
	//���鷿���
	BYTE RefType1;
	WORD No1;
	//���鷿������//-1,������벻����,
	WORD No2;
}Srp_GetMeetMemberCnt;

//����ͨ��
typedef struct{
    WORD No1;//����ͨ��1
    WORD No2;//����ͨ��2;
    WORD No3;//����
}Srp_ConnChan;

//�����·״̬
typedef struct{
    WORD No1;//��·ͨ��
    WORD No2;//��·״̬���
}Srp_CheckStatus;

typedef struct{
    WORD No1;//�˺�
    WORD No2;//����
    WORD No3;//���
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
	WORD No1;//�˺�
	WORD No2;//����

	BYTE RefType3;//����
	WORD No3;
	int ICon3;

	WORD No4;//���
	WORD No5;//��֤���
	WORD No6;//��¼����
}Srp_VerifyPassword;

typedef struct{
	BYTE RefType1;
	WORD No1;
	int ICon1;
}Srp_Sleep;

typedef struct{
	//��������
	BYTE RefType1;
	WORD No1;
	int ICon1;
	char TCon1[14];
	SString SCon1;
	double FCon1;

	//��������
	BYTE RefType2;
	WORD No2;
	int ICon2;

	//���  0-������1-����2-�������
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
    BYTE vType;//��������
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
    WORD No1;//0-31 S����,255-����
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
    //¼���ļ���
    BYTE RefType1;
    BYTE No1;
    char SCon1[256];

    //�жϷ�ʽ
    BYTE RefType2;
    BYTE No2;
    char SCon2[12];

    //¼��ʱ�䳤��
    BYTE RefType3;
    BYTE No3;
    int ICon3;
    //0-�ɹ�;1-ʧ��
    int Out[2];
}Cmd_Record;

typedef struct{
    WORD CmdType;

    //��������
    BYTE RefType1;
    BYTE No1;
    int ICon1;

    //��������
    BYTE RefType2;
    BYTE No2;
    char SCon2[256];
    //0-�ɹ�;1-ʧ��
    int Out[2];
}Cmd_PlayTTS;

typedef struct{
    WORD CmdType;

    //����������
    BYTE RefType1;
    BYTE No1;
    int ICon1;

    //��ʱʱ��
    BYTE RefType2;
    BYTE No2;
    int ICon2;
    //0-�ɹ�;1-ʧ��
    int Out[2];
}Cmd_CycPlay;

//��ʼ����
typedef struct{
    WORD CmdType;
    int Out[1];
}Cmd_Start;

//�ź�ͨ��������
typedef struct{
    WORD CmdType;
	
	//����
    BYTE RefType1;
    BYTE No1;//����
    char SCon1[20];//���г���
	
	//����
    BYTE RefType2;
    BYTE No2;//����
    char SCon2[20];//���г���
    
	//����ռ��ͨ��
    BYTE No3;//���гɹ�ռ�õ�ͨ����
	
	//��������
	BYTE RefType4;
	BYTE No4;
	int ICon4;
	
    //�ȴ�����
    BYTE RefType5;
    BYTE No5;
    int  ICon5;
	char SCon5[128];
	
	//ֹͣ���а���
	char SCon6[13];
	
	//ֹͣ���а�����ű���
	BYTE No7;

	//�����ȴ�ʱ�䳤��
	BYTE RefType8;
	BYTE No8;
	int  ICon8;
	
    //0-����Ӧ��,�ɹ�;1-���˽�;2-����æ;
	//3-����ʧ��;4-��·æ;5-�պ�;6-���й����б����;7-������ʱ
    int Out[8];
}Cmd_CallOut2;

//�����м̺�����������
typedef struct{
    WORD CmdType;

	//����
    BYTE RefType1;
    BYTE No1;//����
    char SCon1[20];//���г���

	//����
    BYTE RefType2;
    BYTE No2;//����
    char SCon2[20];//���г���
    
	//����ռ��ͨ��
    BYTE No3;//���гɹ�ռ�õ�ͨ����

	//��������
	BYTE RefType4;
	BYTE No4;
	int ICon4;

    //�ȴ�����
    BYTE RefType5;
    BYTE No5;
    int  ICon5;
	char SCon5[256];

	//ֹͣ���а���
	char SCon6;

	//ֹͣ���а�����ű���
	BYTE No7;

    //0-����Ӧ�𣬳ɹ�;1-���˽�;2-����æ;
	//3-����ʧ��;4-��·æ;5-�պ�;6-���й����б����
    int Out[7];
}Cmd_CallOut;

//�ű�����
typedef struct{
    WORD CmdType;
    int CmdCnt;
    Srp_Cmd1* pCmdList;
    int Out[1];
}Cmd_Script;


//������ͨ��
typedef struct{
	WORD CmdType;
	//��������ͨ����ű���
	int  No1;

	//�����˺���
	int  No2;

	//������ʾ����
	BYTE RefType3;
	int  No3;
	int  ICon3;

	//�ȴ������뷽�����ȴ�ʱ��
	BYTE RefType4;
	int No4;
	int ICon4;

	//�ȴ�����
	BYTE RefType5;
	int  No5;
	int  ICon5;
	char SCon5[256];
	//0-��������ͬ�� 1-�������˲�ͬ�� 2-�Է�����ʱ��û�а���
	int  Out[3];
}Cmd_Invite;

//�ͱ�������ͨ��
typedef struct{
	//��������ͨ����ű���
	int  No1;
	//0-�������˹һ�,�������˰�#������ͨ��,�ص�ԭ���Ļ��鷿��
	int  Out[2];
}Cmd_TalkWithInvite;

//��ת����
typedef struct{
	WORD CmdType;
	int GotoCmdNo;       
	char  GotoLab[128];//��ת���
}Cmd_Goto;

//����ָ���ֻ�
typedef struct{
    WORD CmdType;
    //��������ߺ����ŵı���
    BYTE sNo1;

    ////�ȴ�Ӧ�����ʾ����ϵͳ����
    BYTE  RefType2;
    BYTE  No2;
    char  SCon2[256];
	int ICon2;
	BYTE  VocType;

    BYTE sNo3;//������������
    BYTE sNo4;//����ת�Ƶķֻ���
    BYTE iNo1;//��ͨ�󱻽зֻ���ͨ����

    //����ռ���Ŷӵȴ�ʱ�䳤��,ICon5=0��ʾ���Ŷ�
    BYTE RefType5;
    BYTE iNo5;
    int ICon5;
    
    //����ģʽ
    BYTE RefType6;
    BYTE No6;
    int ICon6;

    //lbout[0]-����Ӧ��,�ɹ�,lbout[1]-����æ,lbout[2]-�������˽���
    //lbout[3]--û�и÷ֻ�����,lbout[4]-�ֻ���������״̬,lbout[5]-�ֻ�������Ϊת��״̬
    int Out[6];
}Cmd_CallExt;

//������ϯ
typedef struct{
     WORD CmdType;
     //�ȴ���ʾ��
     BYTE RefType1;
     BYTE No1;
     char SCon1[256];
	 int ICon1;
	 BYTE VocType;

     //����ģʽ
     BYTE RefType2;
     BYTE No2;
     int ICon2;

     //���зֻ����
     BYTE RefType3;
     BYTE No3;
     int ICon3;

     //�ȴ���ͨʱ��
     BYTE RefType4;
     BYTE No4;
     int ICon4;

     //������ϯͨ��
     BYTE No5;

     //����ģʽ
     BYTE RefType6;
     BYTE No6;
     int ICon6;

	 //���зֻ�����
	 BYTE RefType7;
	 BYTE No7;
	 int ICon7;
	 
     //0-��ϯժ��;1-��ʱû�п�����ϯ;2-�п�����ϯ,������ϯ��ʱû��ժ��
	 int Out[3]; 
}Cmd_CallSeat;

//��������
#define VOC_FILE  0  //�ļ���������
#define VOC_INDEX 1  //������������
typedef struct {
     WORD CmdType;
     //���������ļ���
     BYTE RefType1;
     BYTE No1;
     char SCon1[256];	
	 int ICon1;

     //���������ļ����ͣ�0-�ļ�������1-��������
     BYTE RefType2;
     BYTE No2;
     int ICon2;

     //������Ϸ�ʽ��N-�����,?-��������
     BYTE RefType3;
     BYTE No3;
     char SCon3[252];

     //���ŵ�ͨ��
     BYTE RefType4;
     BYTE No4;

	 //out0-�������Ž�����out1-������,out2-���ű��������
     int Out[3];
}Cmd_PlayVoc;

//������ͨ��
typedef struct {
	WORD CmdType;

	//ͨ��������ͨ������
	BYTE RefType1;
	BYTE No1;
	int  ICon1;

	//ͨ������
	BYTE RefType2;
	BYTE No2;
	int  ICon2;

	//���鷿���
	BYTE No3;

	//�Է��һ�
	int  Out[1];
}Cmd_TalkWithOut;

//��ϯͨ��
typedef struct {
     WORD CmdType;
     BYTE No1;//������ͨ������ͨ��
     
     //���ͨ���Ĺ����еȴ�,�ȴ��������
     BYTE RefType2;
     BYTE No2;
     int ICon2;

	 //���ͨ���Ĺ����д����˻��飬���鷿������ŵı���
	 BYTE No3;
     //0-��ͨ���һ�;1-����ͨ���һ�;2-�ɹ���������;3-��������ʧ��
	 int Out[1];
}Cmd_Talk2;

//����ѡ��
typedef struct {
    WORD   CmdType;

	BYTE RefType1;
	BYTE No1;
	char SCon1[256];
	int ICon1;

     //���������ļ����ͣ�0-�ļ�����;1-��������
     BYTE RefType2;
     BYTE No2;
     int ICon2;

     //�ظ��������
     BYTE RefType3;
     BYTE No3;
     int ICon3;

     //ѡ���֧��ʾ�������ȴ���ʱ�ĺ�����
     BYTE RefType4;
     BYTE No4;
     int ICon4;

     //�û����밴��
     BYTE No5;
    int Out[13];
}Cmd_Digit;

//��������
typedef struct {
    WORD  CmdType;
	//���������ļ���
	BYTE RefType1;
	BYTE No1;
	char SCon1[256];
	int ICon1;

    //���������ļ����ͣ�1-�ļ�������2-��������
    BYTE RefType2;
    BYTE No2;
    int ICon2;

    //�������볤��,=0���ݽ������������յ绰����
    BYTE RefType3;
    BYTE No3;
    int ICon3;

    //��������
    BYTE RefType4;
    BYTE No4;
    char SCon4;

    //�û����밴����ű���
    BYTE No5;

    //�ظ��������
    BYTE RefType6;
    BYTE No6;
    int ICon6;

    //ѡ���֧��ʾ�������ȴ���ʱ�ĺ�����
    BYTE RefType7;
    BYTE No7;
    int ICon7;

	//�ж����밴��
	BYTE RefType8;
	BYTE No8;
	char SCon8;

    int Out[3];//out[0]-�������밴��,out[1]-�涨ʱ��û������,out[2]-�û��ж�����
}Cmd_Input;

//��������
typedef struct {
    WORD CmdType;
    BYTE iNo;//���뵽�Ļ��鷿���
	//���鷿������
	BYTE RefType2;
	BYTE No2;
	int ICon2;
	//���鷿������
	BYTE RefType3;
	BYTE No3;
	int  ICon3;
    //0-������鷿��ɹ�;1-������鷿��ʧ��
    int Out[2];
}Cmd_CreateMeet;

//�������
typedef struct {
	WORD CmdType;

	//������鷿���
	BYTE RefType1;
	BYTE No1;

	//����
	BYTE RefType2;
	BYTE No2;
	int ICon2;

	//�Ƿ�������ͨ��
	BYTE IsPreside; //1-�� 0-���� 

    //0-����ɹ�;1-����ʧ��
    int Out[2];
}Cmd_EnterMeet;

//�������
typedef struct {
    WORD CmdType;
    BYTE iNo;//���鷿���
	BYTE No2;//�˳�ͨ����ű���
    //0-�˳����� 1-�ϳ�����
    int Out[2];
}Cmd_MeetTalk;

//��̬�������
typedef struct {
    WORD CmdType;//��������
    //�������
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

//�����������
typedef struct {
	//���ߺ���ʱ������״̬������
	int  CmdNo;//��ǰͨ��ִ�е�������

	int   Step;//���ߺ������ߵ�ǰͨ������ִ�е�״̬
	int   Step1;//���ߺ������ߵ�ǰͨ��ִ�е�״̬1

	int  SrpStep;//����ĳЩ���ܹ�һ��ѭ����ɵĽű�����(callfunc,sqlopen...)�ȵ�ִ��״̬
	int  SrpCmdPnt;//���нű�����ʱ������ָ��


	//��������ժ��������״̬������
	int   InState;//��״̬
	int   InStep;//С״̬

	//״̬������
	int  T1;  //��ʱ��1
	int  T1_Start;//��ʱ��1��ʱ��ʼ
	int  T2;  //��ʱ��2
	int  T2_Start;//��ʱ��2��ʱ��ʼ

	int  HookT_Start;
	int  RPara1;//��Ҫ��������ʱ����1
	int  RPara2;//��Ҫ��������ʱ����2
	int  RPara3;
	int  RPara4;
	int  RPara5;
	bool Stop;//������ͣ���
	char SPara1[512];//����ʱ�ַ���s����2
	char SPara2[64];

	//���й��̲���
	union{
		CallStat_WaitInQueue cs_waitinqueue;
		CallStat_TalkWithSeat cs_talkwithseat;
		CallStat_InCallOut cs_incallout; 
	};

	//ͨ����ǰ���յ�CALLOUTָ��
	TcpPacket recvpak;

	//��ǰִ�еĽű�����
	Srp_Cmd1 srp;

	//���˿��澯��� 0-���澯,1-��Ҫ�澯
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
