#ifndef _rinpak_h_
#define _rinpak_h_

#define  REMIN_HEAD_TAG  0XEFEFEFEF
//Զ��
enum{
	REMIN_RING,      //����
	REMIN_STOPRING,  //ֹͣ����
	REMIN_OFFHOOK,   //ժ��
	REMIN_HOOK,      //�һ�
	REMIN_ALIVE,      //���� 
	REMIN_LOGIN      //�ͻ��˵�¼
};

typedef struct{
	int HeadTag;   //��ͷ���
	int cmdtype;   //����
	int node;      //�ڵ��
	int brdno;     //Ӳ�����
	int chno;      //��ͨ����
}RemInPak;

#endif