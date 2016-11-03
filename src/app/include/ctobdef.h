/*
���ķ������������ṹ����
1)�����м�ͨ��
2)��ϯͨ��
3)����ͻ����Ա

����:����
����:2003��11��1��
�޶�:
*/
#ifndef _ctobdef_h_
#define _ctobdef_h_

#include <list>
#include <time.h>
using namespace std;

//����
typedef struct{
    char Caller[20];//���к���
    char Called[20];//��·����
}LZ_OutLine;

//��ϯ�Ǽ�״̬
#define LZ_LS_LOGOUT   0//��ϯ�ǳ�
#define LZ_LS_LOGIN    1//��ϯ����
#define LZ_LS_PAUSE    2//��ϯ��ͣ
#define LZ_LS_CANCELED 3//��ϯȡ��

//��ϯ��ɫ
#define LZ_ROLE_SEAT     1//��ͨ��ϯ
#define LZ_ROLE_SEATMAN  2//������ϯ

typedef struct {
    char SeatNo[8];//��¼��ϯ��
	char Name[10];//��������
    char LineNo[8];//��·�̶��ֻ���
	char Password[10]; //��ϯ���� 
    BYTE Role;//���߽�ɫ.��ͨ��ϯ��������ϯ

    DWORD Group;//���
	DWORD Tech; //���� 
    BYTE   LogStatus;//��ϯ�Ǽ�״̬;
    time_t LogInTime;//��ϯ�Ǽ�ʱ��
    int TalkTime;//��ϯ��¼��������ۼ�ͨ��ʱ��(��)
	
	int SeatCode;//��ϯ̨ͨѶ�ڵ�Code
}LZ_InLine;

//***********************��·״̬����***********************
//����״̬
#define LZ_OUT_IDLE          0   //����
#define LZ_OUT_OFFHOOK       1   //����ժ��
#define LZ_OUT_RING          2   //��������
#define LZ_OUT_TALKWITHOUT   3   //������ͨ��
#define LZ_OUT_TALKWITHIN    4   //����ϯͨ��
#define LZ_OUT_HOLD          5   //����ϯͨ��������
#define LZ_OUT_MEET          6   //������
#define LZ_OUT_AUTOIVR       7   //�Զ�IVR
#define LZ_OUT_WAIT          8   //���еȴ�

//����״̬��ز���
typedef struct  {
	int OutChan;      //ͨ������ͨ��
	char OutNum[20];  //ͨ�����ߺ���
}OutTalkWithOutPara;

typedef struct{
	int InChan;
	char InNum[20];
}OutTalkWithInPara;

typedef struct{
	int HoldInChan;//���ֵ�����ͨ��
}OutHoldPara;

typedef struct{
	int WaitGroup;//�ȴ���ϯ�������
	int WaitTechs;//�ȴ��������� >0��ʼ�ȴ�
	DWORD WaitTime;//�ȴ�ʱ�䳤��
}OutWaitPara;

typedef struct{
	int RoomNo;
}OutMeetPara;

//����״̬
#define LZ_IN_IDLE           0  //���߿���
#define LZ_IN_OFFHOOK        1  //����ժ��
#define LZ_IN_RING           2  //��������
#define LZ_IN_TALKWITHOUT    3  //���ߺ�����ͨ��
#define LZ_IN_TALKWITHIN     4  //������ͨ��
#define LZ_IN_MEET           5  //������
#define LZ_IN_MOVE           6  //����ת��״̬
#define LZ_IN_LEVMSG         7  //����״̬

//����״̬��ز���
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
    int  MoveChan;//��ϯ�ĺ���ת��ͨ��
	int  MoveType;//��ϯ����ת������0-����;1-����
    char MoveNum[20];//��ϯ�ĺ���ת�ƺ���
}InMovePara;

//ͨ���ṹ����
typedef struct  {
	long ChanType;         //ͨ������,����/����
	long CallDirect;       //ͨ������,����/����
	time_t OffHookTime;    //ժ��ʱ��
	long OffHookDur;       //ժ��ʱ��,��λ��
	
	long Status;           //��·״̬
	long ChdStatus;        //��·��״̬

	//״̬��������
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

	//����/���߹̶�����
	union{
		OutLine Out;
		InLine  In;
	};
}LZ_Chan;

//***************************����ṹ************************************
//����ͨ������
#define LZ_MEET_TYPE_MEMBER  0//��ʽ�����Ա�����Է���
#define LZ_MEET_TYPE_AUDIT   1//���������Ա
#define LZ_MEET_TYPE_PRESIDE 2//������ͨ��
typedef struct {
    WORD    VocChan;//�λ��ߵ�ͨ�����
	char    Num[16];//�λ�ͨ������
	WORD    Type;//����ͨ������
    time_t  EnterTime;//��������ʱ��
    WORD    InGain;//��������(0--0x8000) (0x1000��ʾ0dB,�Ƽ�ʹ��0x800(-6dB))
}LZ_MeetMember;

#define LZ_ROOM_ATTR_RECORD  0X01  //¼������
#define LZ_ROOM_ATTR_MUSIC   0x02  //��������
#define LZ_ROOM_ATTR_AUDIT   0X04  //��������

typedef struct {
    list <LZ_MeetMember> MemberList;//�����ͨ���б�
	int  RoomSize;//�����С
    int  RoomNo;//����������
	int  RecFlag;//¼����� 1-��¼��,0-ֹͣ¼��
	char RoomName[128];//��������
	int  RoomType;//��������
	char RoomTypeName[128];//��������
	time_t RoomCreateTime;//���鴴��ʱ��
	int  RoomAttr;//��������.¼��|����|����
}LZ_MeetRoom;

#endif
