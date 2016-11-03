#ifndef _rinpak_h_
#define _rinpak_h_

#define  REMIN_HEAD_TAG  0XEFEFEFEF
//远程
enum{
	REMIN_RING,      //振铃
	REMIN_STOPRING,  //停止振铃
	REMIN_OFFHOOK,   //摘机
	REMIN_HOOK,      //挂机
	REMIN_ALIVE,      //心跳 
	REMIN_LOGIN      //客户端登录
};

typedef struct{
	int HeadTag;   //包头标记
	int cmdtype;   //命令
	int node;      //节点号
	int brdno;     //硬件板号
	int chno;      //板通道号
}RemInPak;

#endif