#include <list>
#ifndef _basedef_h_
#define _basedef_h_
//DTMF���������ֵ
#define MAX_DTMFBUF_LEN 64
#define MAX_COMMAND     9999999

using namespace std;

//��ϯ���������Ԫ������
typedef struct{
    char phone[20];
    time_t  t;
}
Phone;

//����
typedef struct{
    char CallNum[20];//�������к���
	char MidNum[20]; //ԭ���к���
    char LineNum[20];//��·����
}
OutLine;

//��ϯ��ɫ
#define ROLE_EXT  0
#define ROLE_SEAT  1
#define ROLE_EXTSEAT 2

typedef struct {
    char SeatNo[8];//��¼��ϯ��
	char Name[10];//��������
    char LineNo[8];//��·�̶��ֻ���
	char Password[10]; //��ϯ���� 
    BYTE Role;//���߽�ɫ.��ͨ��ϯ��������ϯ

    DWORD Group;//���
	DWORD Tech; //���� 
	
	//��ϯ�Ǽ�״̬
#define LS_LOGOUT   0//��ϯ�ǳ�
#define LS_LOGIN    1//��ϯ����
#define LS_PAUSE    2//��ϯ��ͣ
#define LS_CANCELED 3//��ϯȡ��

    BYTE LogStatus;//��ϯ�Ǽ�״̬;
    time_t LogInTime;//��ϯ�Ǽ�ʱ��
    int TalkTime;//��ϯ��¼��������ۼ�ͨ��ʱ��(��)
	
	int No;
	int SeatCode;//��ϯ̨ͨѶ�ڵ�Code
    WORD movechan;//��ϯ�ĺ���ת��ͨ��
	int  MoveType;//��ϯ����ת������0-����;1-����
    char MoveNum[20];//��ϯ�ĺ���ת�ƺ���

    char LeaveMsgFile[64];//����ͨ�����������ļ�

	int AutoRecFlag;//�Զ�ͨ��¼����� 0-��¼�� 1-¼��
}
InLine;

//��·״̬
enum{
 CHAN_IDLE,	               //����
 CHAN_TALK2,		       //˫��ͨ��
 CHAN_MEET,                //������
 CHAN_AUTOIVR,	           //�Զ�ivr
 CHAN_HOLD,                //ͨ������
 CHAN_NOTUSE,              //δ��ͨ
 CHAN_WAIT,                //������
 CHAN_CALLOUT_MEET,        //�����������
 CHAN_CALLOUT_IVR,         //�����Զ�IVR
 CHAN_CALLOUT_TALKWITHIN,  //����������ͨ��
 CHAN_CALLOUT_MONITORMEET, //������������״̬
 CHAN_CALLOUT_TALKWITHOUT, //����������ͨ��
	//--����ר��
 CHAN_LEVMSG,		  //������λ
 CHAN_MOVECALL,	      //����ת��
 CHAN_RING,		      //������
 CHAN_OFFHOOK,        //����ժ��
 CHAN_WAITHOOK,       //���ߵȴ��һ�״̬16
 CHAN_SILENT,         //����״̬
 CHAN_IAMBUSY,        //ʾæ

 CHAN_CALLOUT_OFFHOOK, //���߱����н�ͨͨ��

 CHAN_AUTOCALLOUT_READYFOR,    //����ժ���ȴ���ͨ����
 CHAN_AUTOCALLOUT_TALK,     //���ߺ��Զ���������ͨ��״̬
 CHAN_AUTOCALLOUT_WAIT_OFFHOOK, //���ߵȴ����ߺ����ɹ�

 CHAN_CALLOUTING  //�������ں���״̬
};
#define  LineStatus(a)  #a

//IVRͨ��״̬����
typedef struct{
	int   ChanType;
    WORD  Status;//��·״̬;
	WORD  AllocRes;

	char CallID[25];
	time_t OffHookTime;//ժ��ʱ��

#define DIR_NONE         0
#define DIR_IN           1
#define DIR_OUT          2
#define DIR_AFTERRELEASE 3
#define DIR_MONEYALERT   4
#define DIR_TOBESTOP     5

    BYTE Direct;//ͨ����ͨ������

    int IvrFileHnd;//ִ�е�ivr�ļ�����
	int IvrVer;//ִ�е� �汾;0��1

//�ڻ����б���������
	bool InviteFlag;     //�Ƿ�����������
	char InviteNum[20];  //�����ҵ��˺���
	int  InviteVoc;      //�����ҵ�����
	int  Agree;          //0-�ȴ��Է��𸴣�1-ͬ�� 2-������  
	int  InviteChan;     //�����ҵ�ͨ��

//���ߺ������߲���
	int CallOutChan;  //���ߺ������ߺ��гɹ����ͨ��

//---�������Ű����ж�����
	char StopDtmf[13];   //�жϼ�
	WORD SaveVarNo;  //�жϼ��������
	
//--ͨ��״̬����
	char ConnectNum[20];//����ͨ������
    WORD ConnChan;//����ͨ��
	
//--������ϯ�ȴ�����--------
	int   WaitGroup;//�ȴ���ϯ�������
	int   WaitTechs;//�ȴ��������� >0��ʼ�ȴ�
	DWORD WaitTime;//�ȴ�ʱ�䳤��
//--ͨ�����ֲ���----
	//��������
#define HOLD_SILENT    0
#define HOLD_HOLD      1
	BYTE    HoldType;   //Hold���� 0-Silent ,1-Hold
	WORD    WhoHoldMe;  //�ĸ�ͨ����������
	time_t  StartHoldTime; //��ʼ�����ҵ�ʱ��
	//��������
	WORD SilentChan;  //������������ͨ��

    WORD HoldChanNo;//ͨ������ͨ��
	int  RoomNo;//ͨ���μӻ���Ļ��鷿���
	int  CreateRoomNo;//ͨ�������Ļ������

    //ͨ��������ز���
    OutLine  Out;
    InLine   In;

    char DtmfBuf[MAX_DTMFBUF_LEN];//ͨ��dtmf����
	
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

//----------------------����ṹ
//����ͨ������
#define MEMBER_TYPE_MEMBER  0//��ʽ�����Ա�����Է���
#define MEMBER_TYPE_AUDIT   1//���������Ա
#define MEMBER_TYPE_PRESIDE 2//������
typedef struct tagMeetMember{
    WORD    VocChan;//�λ��ߵ�ͨ�����
	char    Num[16];//�λ�ͨ������
	WORD    Type;//����ͨ������
    time_t  EnterTime;//��������ʱ��
    WORD    InGain;//��������(0--0x800) (0x1000��ʾ0dB,�Ƽ�ʹ��0x800(-6dB)
	bool    ZhanKeng;//����ռ�ӱ��
	tagMeetMember()
	{
		memset(Num,0,16);
		ZhanKeng=false;
	}
}
MeetMember;

typedef struct tagMeetRoom{
    list <MeetMember> MemberList;//�����ͨ���б�
	int  RoomSize;//�����С
    int  RoomNo;//����������
	int  RecFlag;//¼����� 1-��¼��,0-ֹͣ¼��
	char RoomName[128];//��������
	int  RoomType;//��������
	char RoomTypeName[128];//��������
	time_t RoomCreateTime;//���鴴��ʱ��
	int  RoomAttr;//��������.¼����|��������|����
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
