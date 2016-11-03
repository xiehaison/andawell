//---------------------------------------------------------------------------
#pragma hdrstop
#include "cbcomm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//Dll���ܺ���
//loadͨѶ����
pLoadConfig LoadConfig;

//����ͨѶ����
pConnectCenter ConnectCenter;

//�������ݰ�
pSendPacket SendPacket;

//hook����״̬����
pHookConnStatus HookConnStatus;


pHookRecvCmd HookRecvCmd;

bool LoadDll(const char* dllname)
{
  HINSTANCE hind;
  hind=LoadLibrary(dllname);
  if (hind==NULL)
    return false;

  LoadConfig=(pLoadConfig)GetProcAddress(hind,"LoadConfig");
  if (LoadConfig==NULL)
   return false;

  ConnectCenter=(pConnectCenter)GetProcAddress(hind,"ConnectCenter");
  if (ConnectCenter==NULL)
    return false;
 

  SendPacket=(pSendPacket)GetProcAddress(hind,"SendPacket");
  if (SendPacket==NULL)
    return false;

  HookRecvCmd=(pHookRecvCmd)GetProcAddress(hind,"HookRecvCmd");
  if (HookRecvCmd==NULL)
     return false;
     
  HookConnStatus=(pHookConnStatus)GetProcAddress(hind,"HookConnStatus");
  if (HookConnStatus==NULL)
     return false;

  return true;
}

