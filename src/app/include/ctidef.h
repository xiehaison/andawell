#ifndef _ctidef_h_
#define _ctidef_h_
#include <list>
#include <time.h>
#include "commpack.h"
#include "atomcmd.h"
#include "basedef.h"

using namespace std;

//---------------通道结构
//通道类型
#define TYPE_SS7DOUT 0//数字外线
#define TYPE_AIN  1//内线座席
#define TYPE_MON  3//监听高阻录音
#define TYPE_AOUT 4//模拟外线
#define TYPE_DIN  5//外线座席
#define TYPE_SS1OUT 6//1号信令外线
#define TYPE_ISDNOUT 7//ISDN信令外线
#define TYPE_NOUSE  8 //无用线路

//座席登记状态
#define LOG_LOGOUT   0//退出服务
#define LOG_LOGIN    1//登记进入服务
#define LOG_PAUSE    2//暂停服务
#define LOG_CANCELED 3//内线被取消

typedef struct{
	Phone List[20];
	int size;//队列数量
	int first;//队首指针
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

//座席
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

//IVR通道列表数据
typedef struct{
	//内线通道允许登录的seat列表
	list<Seat> AllowLoginList;
//	SeatList AllowLoginList;
	PhoneList LDList;//来电
	PhoneList QDList;//去电
	PhoneList WJList;//未接

#define DATATOSEND 2
#define HAVEDATA   1
#define IDLE       0

    BYTE  DataFlag;//UDP数据收发标志
	DBPacket dbpak;

    //呼叫分段参数
	char   SPara[4][64];
	time_t SecStartTime;
}
YTChanList;

//运行数据
typedef struct{
	int TotalCnt;
	int InCnt;
	int OutCnt;
	int CallOutCnt;
	int CallInCnt;
    int WorkSeat;
	int CallingCnt;
}SysRunPara;

//----------------------宏定义
#define BOARD(wd)  BYTE(WORD(wd)>>8)
#define LOGIC(wd)  BYTE(WORD(wd)&0x00FF)

#endif
