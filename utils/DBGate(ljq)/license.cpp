#include "stdafx.h"
#include "license.h"
#define ROUNDS 32
#define DELTA 0x9e3779b9 /* sqr(5)-1 * 2^31 */

typedef DWORD word32;
/**********************************************************
   Input values: 	k[4]	128-bit key
			v[2]    64-bit plaintext block
   Output values:	v[2]    64-bit ciphertext block 
 **********************************************************/

void tean(word32 *k, word32 *v, long N) {
  word32 y=v[0], z=v[1];
  word32 limit,sum=0;
  if(N>0) { /* ENCRYPT */
    limit=DELTA*N;
    while(sum!=limit) {
      y+=((z<<4)^(z>>5)) + (z^sum) + k[sum&3];
      sum+=DELTA;
      z+=((y<<4)^(y>>5)) + (y^sum) + k[(sum>>11)&3];
    }
  } else { /* DECRYPT */
    sum=DELTA*(-N);
    while(sum) {
      z-=((y<<4)^(y>>5)) + (y^sum) + k[(sum>>11)&3];
      sum-=DELTA;
      y-=((z<<4)^(z>>5)) + (z^sum) + k[sum&3];
    }
  }
  v[0]=y; v[1]=z;
}

void cl_enc_block(word32 *k, word32 *v) {
 tean(k,v,ROUNDS);
}

void cl_dec_block(word32 *k, word32 *v) {
 tean(k,v,-ROUNDS);
}


//辅助函数
//将二进制流转化为可见十六进制代码,以0结尾
//len=binlen,len必须是偶数
void WINAPI bintohex(char* bin,char* hout,int len)
{
	int i;
	for (i=0;i<len;i++)
	{
		sprintf(hout+i*2,"%02x",*(unsigned char*)(bin+i));
	}
}

//将可见的十六进制代码流转化为二进制流
//len=hinlen,len必须是偶数
void WINAPI hextobin(char hin[],char bout[],int len)
{
	int i;
	char highbyte,lowbyte;
	for (i=0;i<len/2;i++)
	{
		if (hin[i*2]>='0'&&hin[i*2]<='9')
			highbyte=hin[i*2]-'0';
		if (hin[i*2]>='A'&&hin[i*2]<='F')
			highbyte=hin[i*2]-'A'+10;
		if (hin[i*2]>='a'&&hin[i*2]<='f')
			highbyte=hin[i*2]-'a'+10;

		if (hin[i*2+1]>='0'&&hin[i*2+1]<='9')
			lowbyte=hin[i*2+1]-'0';
		if (hin[i*2+1]>='A'&&hin[i*2+1]<='F')
			lowbyte=hin[i*2+1]-'A'+10;
		if (hin[i*2+1]>='a'&&hin[i*2+1]<='f')
			lowbyte=hin[i*2+1]-'a'+10;

		bout[i]=(highbyte<<4)|(lowbyte);
	}
}

//mingwen-16位明文;miwen-32位密文;key-最长16位密钥
void WINAPI JieMi(const char* miwen,char* mingwen,const char* key)
{
	if(strlen(miwen)!=32)
		return;
	if(strlen(key)>16)
		return;

	char t1[32];
	memcpy(t1,miwen,32);
	char t2[17]="";
	hextobin(t1,t2,32);

	char tkey[16];
	memset(tkey,0,16);
	strcpy(tkey,key);

	cl_dec_block((word32*)tkey,(word32*)t2);
	cl_dec_block((word32*)tkey,(word32*)(t2+8));

	memcpy(mingwen,t2,16);
}

//mingwen-16位明文;miwen-32位密文;key-最长16位密钥
void WINAPI JiaMi(const char* mingwen,char* miwen,const char* key)
{
	char t1[17];
	memset(t1,0,17);
	memcpy(t1,mingwen,16);

	char tkey[16];
	memset(tkey,0,16);
	strcpy(tkey,key);
	tkey[15]=0;

	cl_enc_block((word32*)tkey,(word32*)t1);
	cl_enc_block((word32*)tkey,(word32*)(t1+8));

	char t2[33]="";
	bintohex(t1,t2,16);

	memcpy(miwen,t2,32);
}

//计算校验码
void calyzm(const char* machinenum,char* yzm)
{
	char temp1[33]="";
	char temp2[33]="";
	char temp6[17]="";
	memcpy(temp6,machinenum,16);
	JiaMi(temp6,temp1,"windows");
	
	memset(temp6,0,17);
	memcpy(temp6,machinenum+16,16);
	JiaMi(temp6,temp2,"windows");
	char temp3[33];
	int i;
	for (i=0;i<33;i++)
		temp3[i]=temp1[i]^temp2[i];

	char temp4[17]="";
	for (i=0;i<16;i++)
		temp4[i]=temp3[i]^temp3[16+i];

	char temp5[9]="";
	for (i=0;i<8;i++)
		temp5[i]=temp4[i]^temp4[8+i];
	sprintf(yzm,"%02x%02x%02x%02x%02x%02x%02x%02x",
		temp5[0],temp5[1],temp5[2],temp5[3],temp5[4],temp5[5],temp5[6],temp5[7]);
}
