#ifndef _ctidef_h_
#define _ctidef_h_
#include <list>
#include <time.h>
#include "commpack.h"
#include "atomcmd.h"
#include "basedef.h"

using namespace std;

//---------------ͨ���ṹ
//ͨ������
#define TYPE_SS7DOUT 0//��������
#define TYPE_AIN  1//������ϯ
#define TYPE_MON  3//��������¼��
#define TYPE_AOUT 4//ģ������
#define TYPE_DIN  5//������ϯ
#define TYPE_SS1OUT 6//1����������
#define TYPE_ISDNOUT 7//ISDN��������
#define TYPE_NOUSE  8 //������·

//��ϯ�Ǽ�״̬
#define LOG_LOGOUT   0//�˳�����
#define LOG_LOGIN    1//�Ǽǽ������
#define LOG_PAUSE    2//��ͣ����
#define LOG_CANCELED 3//���߱�ȡ��

typedef struct{
	Phone List[20];
	int size;//��������
	int first;//����ָ��
	void clear()
	{
		size=0;
		first=0;
	}
	void push_back(Phone phone)
	{
		size=size+1;
		if (size>20) 
		{
			size=20;
			memcpy(&List[first],&phone,sizeof(Phone));
			first=(first+1)%20;
		}else
		{
			memcpy(&List[(first+size-1)%20],&phone,sizeof(Phone));
		}
	}
	void push_back_phone(char *phone)
	{
		Phone ph;
		memset(&ph,0,sizeof(ph));
		strcpy(ph.phone,phone);
		time(&(ph.t));
		push_back(ph);
	}
}PhoneList;

//��ϯ
typedef struct{
	char SeatNo[8];
	char Name[10];
	char PassWord[10];
	int  Group;
	int  Tech;
	int  No;
}Seat;

typedef struct{
	Seat List[10];
	int size;
	int first;
	int pos;
	void clear()
	{
		size=0;
		first=0;
	}
	void push_back(Seat seat)
	{
		size=size+1;
		if (size>10) 
		{
			size=10;
			memcpy(&List[first],&seat,sizeof(Seat));
			first=(first+1)%10;
		}else
		{
			memcpy(&List[(first+size-1)%10],&seat,sizeof(Seat));
		}
	}
	void gethead(Seat& seat)
	{

	}
}SeatList;

//IVRͨ���б�����
typedef struct{
	//����ͨ�������¼��seat�б�
	list<Seat> AllowLoginList;
//	SeatList AllowLoginList;
	PhoneList LDList;//����
	PhoneList QDList;//ȥ��
	PhoneList WJList;//δ��

#define DATATOSEND 2
#define HAVEDATA   1
#define IDLE       0

    BYTE  DataFlag;//UDP�����շ���־
	DBPacket dbpak;

    //���зֶβ���
	char   SPara[4][64];
	time_t SecStartTime;
}
YTChanList;

//��������
typedef struct{
	int TotalCnt;
	int InCnt;
	int OutCnt;
	int CallOutCnt;
	int CallInCnt;
    int WorkSeat;
	int CallingCnt;
}SysRunPara;

//----------------------�궨��
#define BOARD(wd)  BYTE(WORD(wd)>>8)
#define LOGIC(wd)  BYTE(WORD(wd)&0x00FF)

#endif
