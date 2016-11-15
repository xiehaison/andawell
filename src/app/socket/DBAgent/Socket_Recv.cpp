// Socket_Recv.cpp : implementation file
//

#include "stdafx.h"
#include "DBAgent.h"
#include "Socket_Recv.h"
#include <sys/timeb.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void RunLog(const char* line,...)
{
    char buf[256];
	char buf1[1024]={0};
	struct _timeb tstruct1;
    CTime t1;
	CString dline1;
	
	//不带时间日志->buf
	memset(buf,0,256);
    va_list args;
    va_start(args, line);
    _vsnprintf(buf,sizeof(buf),line, args);
    va_end(args);
	
	//带时间日志->dline1
	_ftime( &tstruct1 );
	t1=CTime::GetCurrentTime();
	dline1.Format("%s(%3u)=>%s",t1.Format("%H:%M:%S"),tstruct1.millitm,buf);
	CString dline=dline1+"\n";
    OutputDebugString(dline);
}	
////////////////////////////////////////////////////////////////////////////
// CSocket_Recv

CSocket_Recv::CSocket_Recv()
{
	nPackLength = 0;
	status = 0;
	CurChan = -1;
}

CSocket_Recv::~CSocket_Recv()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSocket_Recv, CAsyncSocket)
//{{AFX_MSG_MAP(CSocket_Recv)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSocket_Recv member functions

void CSocket_Recv::OnClose(int nErrorCode) 
{
	Close();
	status = 0;
	
	CAsyncSocket::OnClose(nErrorCode);
}

void CSocket_Recv::OnConnect(int nErrorCode) 
{
	status = 2;
	if(nErrorCode)
	{
		Close();
		status = 0;
	}
	else
	{
		DBPacket pak;
		pak.HeadFlag=0xeffffffe;
		pak.PackType=PAK_PROXYINFO;
		pak.proxyinfo.socktype=0;
		pak.proxyinfo.proxyno=0;
		Send((char*)(&pak),sizeof(pak),0);
	}
	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CSocket_Recv::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	char szBuf[1024];
	int len = Receive(szBuf,1024);

    TakeApartPack(szBuf,len);
	
	CAsyncSocket::OnReceive(nErrorCode);
}
void CSocket_Recv::TakeApartPack(char *szReceive, int nLength)
{
	if(nPackLength> 2048) 
	{
		return ;
	}
	memcpy(&szPackBuf[nPackLength],szReceive,nLength);
	nPackLength+=nLength;

	if(true)//更新缓存区列表
	{
		char szHead[][21] = {"时间","接收字节","缓存区长度"};
		char szBuf[255];
		int index = p_ListBuf->InsertItem(p_ListBuf->GetItemCount(),m_db.GetCurTime(szBuf),0);
		char buf[20];
		p_ListBuf->SetItemText(index,1,itoa(nLength,buf,10));
		p_ListBuf->SetItemText(index,2,itoa(nPackLength,buf,10));
	}

	while(1)
	{
		if(nPackLength<sizeof(DBPacket)) break;
		
		char szPack[1024];
		memcpy(szPack,szPackBuf,sizeof(DBPacket));
		memcpy(szPackBuf,&szPackBuf[sizeof(DBPacket)]
			,nPackLength-sizeof(DBPacket));
		nPackLength-=sizeof(DBPacket);
		DBPacket *pak;
		pak=(DBPacket*)szPack;
		RunLog("DBAGENT=>RECVPAK[%d][%s]",pak->PackType,GetDBPakName(pak->PackType));
		DisplayPack(szPack);
		ParsePacket(szPack);		
	}
}
void CSocket_Recv::ParsePacket(char *szPack)
{
	char szBuf[255];
	DBPacket pak,retpak;
	memcpy(&pak,szPack,sizeof(DBPacket));
	retpak.HeadFlag = 0xEFFFFFFE;
    retpak.chan=pak.chan;
	retpak.PackType = PAK_COMPLETE;
	retpak.Result=1;
	retpak.SerialNo=pak.SerialNo;
	int chan = pak.chan;
	//此处为已经受到完整的包，必须应答；
	try{
		
		if (pak.HeadFlag!=0xEFFFFFFE) return;

		m_db.m_ch[chan].iCurCmd = pak.PackType;
		switch(pak.PackType)
		{
		case PAK_BILL:
			WriteBillDB(pak,chan);
			break;
		case PAK_PREPARESQL:
			{
				for(int j=2;j<7;j++)
					p_ListCommand->SetItemText(chan,j,"");
				//事务的开始；
				if(true)
				{
					//这样做可能霸道了些，但是可以保证立即恢复到准备状态；
					try{
						m_db.m_ch[chan]._cp.Detach()->Release();
						HRESULT hr = m_db.m_ch[chan]._cp.CreateInstance(__uuidof(Command));
						m_db.m_ch[chan]._rs.Detach()->Release();
						m_db.m_ch[chan]._rs.CreateInstance(__uuidof(Recordset));
						/*
						if(m_db.m_ch[chan]._cp->State != 0)
						{
							m_db.m_ch[chan]._cp.Detach()->Release();

							status=1;
							HRESULT hr = m_db.m_ch[chan]._cp.CreateInstance(__uuidof(Command));
							
							char szBuf[1024];
							if(!SUCCEEDED(hr))
							{
								sprintf(szBuf,"_cp CreateInstance fail chan=[%d],sql=[%s]",chan,pak.sqlstat); 
								WriteLog(szBuf);
							}

//							m_db.m_ch[chan]._cp->ActiveConnection = m_db._ctp;
							sprintf(szBuf,"chan=[%d],sql=[%s]",chan,pak.sqlstat); 
							WriteLog(szBuf);
						}*/
						
/*						if(m_db.m_ch[chan]._rs != NULL)
						{
							status=2;						
							m_db.m_ch[chan]._rs.Detach()->Release();

							status=3;
							m_db.m_ch[chan]._rs.CreateInstance(__uuidof(Recordset));
						}*/
					}
					catch(_com_error &e)
					{
					}
					catch(...)
					{
						char szBuf[255];
						sprintf(szBuf,"...%d",status);
						WriteLog(szBuf);
					}
					
				}


				m_db.m_ch[chan]._cp->ActiveConnection = m_db._ctp;
				m_db.m_ch[chan].SQL = pak.sqlstat;

				//此处判断指令类型 0-adProc 1-adText
                string sql = m_db.m_ch[chan].SQL;
                transform(sql.begin(), sql.end(), sql.begin(), ::tolower);
				if(sql.find("select ")+
                    sql.find("update ")+
                    sql.find("delete ") +
                    sql.find("create ")+
                    sql.find("drop ")+
                    sql.find("insert ") == -6 )
					m_db.m_ch[chan].iCmdType = 0;
				else 
                    m_db.m_ch[chan].iCmdType=1;

				m_db.m_ch[chan].inpara.clear();
				m_db.m_ch[chan].outpara.clear();
			
				retpak.PackType=PAK_PREPARESQL_READY;
				SendToServer(retpak);
			}
			break;
		case PAK_SETPARA:
			{
				int paraind = pak.req_SetPara.FieldInd;
				VARIANT v;
				switch(pak.req_SetPara.vType)
				{
				case CON_I://5
				case REF_I:
					v.vt = VT_I4;
					v.lVal = pak.req_SetPara.ICon;
					break;
				case CON_F://6
				case REF_F:
					v.vt = VT_R8;
					v.dblVal = pak.req_SetPara.FCon;
					break;
				case CON_S://7
					{
						v.vt = VT_BSTR;
						CString str(pak.req_SetPara.SCon);
						for(;;)
						{
							int index = str.Find("'");
							if(index==-1) break;
							str = str.Left(index)+str.Mid(index+1);
						}
						v.bstrVal = str.AllocSysString();
					}
					break;
				case REF_S:
					{
						v.vt = VT_BSTR;
						CString str("                                          ");
						v.bstrVal = str.AllocSysString();
					}
					break;
				case CON_T://8
				case REF_T:
					{
						v.vt = VT_BSTR;
						char szBuf[255];
						char * p=szBuf;
						memcpy(p,&pak.req_SetPara.TCon[0],4);//年
						p+=4;
						*p = '-';
						p+=1;
						memcpy(p,&pak.req_SetPara.TCon[4],2);//月
						p+=2;
						*p = '-';
						p+=1;
						memcpy(p,&pak.req_SetPara.TCon[6],2);//日
						p+=2;
						*p = ' ';
						p+=1;

						memcpy(p,&pak.req_SetPara.TCon[8],2);//日
						p+=2;
						*p = ':';
						p+=1;
						memcpy(p,&pak.req_SetPara.TCon[10],2);//日
						p+=2;
						*p = ':';
						p+=1;
						memcpy(p,&pak.req_SetPara.TCon[12],2);//日
						p+=2;
						*p = 0;
						p+=1;

						v.vt = VT_DATE;
						COleDateTime m_date;
						m_date.ParseDateTime(szBuf);
//						DATE d = DATE(m_date);
						v.date=DATE(m_date);

//						CString str(szBuf);
//						v.bstrVal = str.AllocSysString();
					}
					break;
				default:
					break;
				}

				pair<int,VARIANT> p(paraind,v);

				if (pak.req_SetPara.InOut==PARAM_IN)
//				if(m_db.m_ch[chan].iCmdType==1)
					m_db.m_ch[chan].inpara.insert(p);//[paraind]=v;
				else 
					m_db.m_ch[chan].outpara.insert(p);

				retpak.PackType=PAK_SETPARA_READY;
				SendToServer(retpak);
	//			PutSendPak(&retpak,chan);
				//                    ThAddLog("通道%d SetParam执行成功",pak.chan);
	//			SucProcCnt++;
			}
			break;
		case PAK_SQLOPEN:
		case PAK_SQLEXEC:
			{
				p_ListCommand->SetItemText(chan,6,"");
				p_ListCommand->SetItemText(chan,3,"正在执行...");
				p_ListCommand->SetItemText(chan,2,m_db.m_ch[chan].iCmdType == 0?CString("存储过程"):CString("SQL语句"));
				m_db.m_ch[chan].bIsWait = true;
				for(;;)
				{
					int iCount = m_db.m_ch[chan]._cp->Parameters->Count;
					if(iCount!=0)
						m_db.m_ch[chan]._cp->Parameters->Delete(0L);
					else break;
				}
				string s1;
				if(m_db.m_ch[chan].iCmdType == 1) //肯定为查询语句
				{
					CString T("");
					map <int,VARIANT>::const_iterator pos=m_db.m_ch[chan].inpara.begin();
					for (;pos!=m_db.m_ch[chan].inpara.end();++pos)
					{						
						CString str;
						str.Format("%s",(char *)(_bstr_t(pos->second)));
						str.TrimRight();
						if(T.GetLength()) T+=",";
						else T="内部参数:[";
						T+=str;

						if((pos->second.vt == VT_BSTR)||(pos->second.vt == VT_DATE))
							str.Format("'%s'",(char *)(_bstr_t(pos->second)));
						else
							str.Format("%s",(char *)(_bstr_t(pos->second)));
						s1 = str;
						string &s = m_db.m_ch[chan].SQL;
						//add by yutao begin 2003-12-22
						int ytind=0;
						ytind=s.find("?");
						if(ytind==-1)
							continue;
						//add by yutao end
						s.replace(s.find("?"),1,s1);
					}
					if(T.GetLength())	T+="]";
					p_ListCommand->SetItemText(chan,6,T);

					CString str(m_db.m_ch[chan].SQL.c_str());
					m_db.m_ch[chan]._cp->CommandText = _bstr_t(m_db.m_ch[chan].SQL.c_str());
					_variant_t v1(0L);
					m_db.m_ch[chan]._rs = m_db.m_ch[chan]._cp->Execute(&v1,NULL,adCmdText|adAsyncExecute);
				}
				else if(m_db.m_ch[chan].iCmdType == 0)//存储过程
				{

					//adProc
					string s = m_db.m_ch[chan].SQL;
				
					m_db.m_ch[chan].SQL= s.substr(0,s.find('?'));

					int index = m_db.m_ch[chan].SQL.find("exec");
					if(index!=-1)
						m_db.m_ch[chan].SQL.replace(index,4,"");
					s = m_db.m_ch[chan].SQL;

					_variant_t v(0L);
					char szBuf[1024]="";
					strcpy(szBuf,m_db.m_ch[chan].SQL.c_str());

					//处理内部参数
					{
						CString T("");
						CString str;
						map <int,VARIANT>::const_iterator pos=m_db.m_ch[chan].inpara.begin();
						for (;pos!=m_db.m_ch[chan].inpara.end();++pos)
						{
							str.Format("%s",(char *)(_bstr_t(pos->second)));
							str.TrimRight();
							if(T.GetLength()) T+=",";
							else T="内部参数:[";
							T+=str;
							VARIANT vvv = pos->second;
							switch(pos->second.vt)
							{
							case VT_I4:
								{
									m_db.m_ch[chan]._cp->Parameters->Append(m_db.m_ch[chan]._cp->CreateParameter(L"",adInteger,adParamInput,4,vvv));
								}
								break;
							case VT_R8:
								{
									m_db.m_ch[chan]._cp->Parameters->Append(m_db.m_ch[chan]._cp->CreateParameter(L"",adDouble,adParamInput,8,vvv));
								}
								break;
							case VT_BSTR:
								{
									m_db.m_ch[chan]._cp->Parameters->Append(m_db.m_ch[chan]._cp->CreateParameter(L"",adBSTR,adParamInput,255,vvv));
								}
								break;
							case VT_DATE:
								{
									m_db.m_ch[chan]._cp->Parameters->Append(m_db.m_ch[chan]._cp->CreateParameter(L"",adDate,adParamInput,8,vvv));
								}
								break;
							}
						}
						if(T.GetLength())	T+="]";
						p_ListCommand->SetItemText(chan,6,T);

					}
					

					//处理外部参数
					{
						CString T("");
						CString str;
						map <int,VARIANT>::const_iterator pos=m_db.m_ch[chan].outpara.begin();
						for (;pos!=m_db.m_ch[chan].outpara.end();++pos)
						{
							str.Format("%s",(char *)(_bstr_t(pos->second)));
							str.TrimRight();
							if(T.GetLength()) T+=",";
							else T="外部参数:[";
							T+=str;
							VARIANT vvv = pos->second;
							switch(pos->second.vt)
							{
							case VT_I4:
								{
									m_db.m_ch[chan]._cp->Parameters->Append(m_db.m_ch[chan]._cp->CreateParameter(L"",adInteger,adParamOutput,4,vvv));
								}
								break;
							case VT_R8:
								{
									m_db.m_ch[chan]._cp->Parameters->Append(m_db.m_ch[chan]._cp->CreateParameter(L"",adDouble,adParamOutput,8,vvv));
								}
								break;
							case VT_BSTR:
								{
									m_db.m_ch[chan]._cp->Parameters->Append(m_db.m_ch[chan]._cp->CreateParameter(L"",adBSTR,adParamOutput,255,vvv));
								}
								break;
							case VT_DATE:
								{
									m_db.m_ch[chan]._cp->Parameters->Append(m_db.m_ch[chan]._cp->CreateParameter(L"",adDate,adParamOutput,8,vvv));
								}
								break;
							default:
								{
									int kkk = pos->second.vt;
									break;
								}
								break;
							}							
						}
						if(T.GetLength())	T+="]";
						T = T+p_ListCommand->GetItemText(chan,6);
						p_ListCommand->SetItemText(chan,6,T);
					}
					m_db.m_ch[chan]._cp->CommandText = _bstr_t(m_db.m_ch[chan].SQL.c_str());
					_variant_t v1(0L);
					
					m_db.m_ch[chan]._rs = 
						m_db.m_ch[chan]._cp->Execute(&v1,NULL,adCmdStoredProc|adAsyncExecute);					

				}

                int s;
                s = m_db.m_ch[chan]._rs->State;

                int nSize;
                nSize = m_db.m_ch.size();
                if (!((CurChan >= nSize) || ((CurChan >= 0) && (CurChan != pak.chan))))
					p_ListRecv->SetItemText(p_ListRecv->GetItemCount()-1,4,"正在执行...");

//				retpak.Result=1;
//				SendToServer(retpak);

			}
			break;
		case PAK_GETFIELD_REQ:
			{
				//读取字段值
				if(m_db.m_ch[chan]._rs->State!=adStateOpen)
				{
					//未打开
					int nSize = m_db.m_ch.size();
					if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
						p_ListRecv->SetItemText(p_ListRecv->GetItemCount()-1,4,"记录集未打开");
					retpak.Result=0;
					retpak.PackType=PAK_GETFIELD_ERR;
					strcpy(retpak.errmsg,"记录集未打开");
					SendToServer(retpak);
					break;
				}


				if(pak.req_GetField.FieldInd<0||pak.req_GetField.FieldInd>=m_db.m_ch[chan]._rs->Fields->Count)
				{
					string ss("索引越界:字段个数 = ");
					ss+=itoa(m_db.m_ch[chan]._rs->Fields->Count,szBuf,10);
					//越界
					int nSize = m_db.m_ch.size();
					if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
						p_ListRecv->SetItemText(p_ListRecv->GetItemCount()-1,4,ss.c_str());
					retpak.Result=0;
					retpak.PackType=PAK_GETFIELD_ERR;
					strncpy(retpak.errmsg,ss.c_str(),255);
					SendToServer(retpak);
					break;  
				}


				VARIANT v = m_db.m_ch[chan]._rs->Fields->GetItem(short(pak.req_GetField.FieldInd))->Value;
				CString str = LPCTSTR(_bstr_t(v));
				switch(pak.req_GetField.vType)
				{
				case REF_I:
					{

						int iValue = v.lVal;
						if(v.vt==VT_I2)
							iValue=v.iVal;
						
						retpak.PackType=PAK_GETFIELD_VALUE;
						retpak.ret_GetField.vType=REF_I;
						retpak.ret_GetField.ICon=iValue;
					}
					break;
				case REF_F:
					{
						double fValue = v.dblVal;
						retpak.PackType=PAK_GETFIELD_VALUE;
						retpak.ret_GetField.vType=REF_F;
						retpak.ret_GetField.FCon=fValue;
					}
					break;
				case REF_S:
					{
						CString str = LPCTSTR(_bstr_t(v));
						str.TrimRight();
						retpak.PackType=PAK_GETFIELD_VALUE;
						retpak.ret_GetField.vType=REF_S;
						strcpy(retpak.ret_GetField.SCon,str);
					}
					break;
				case REF_T:
					{
						CString str = LPCTSTR(_bstr_t(v));
						retpak.PackType=PAK_GETFIELD_VALUE;
						retpak.ret_GetField.vType=REF_T;
						char szBuf[255],szB[255]="";
						strcpy(szBuf,str);
						//2003-1-2 1:12:09
						char *seps=":- ";
						char *token=NULL;	
						token = strtok(szBuf,seps);
						for(int i=0;;++i)
						{
							if(token == NULL)
								break;
							char szT[5];
								sprintf(szT,"%04s",token);
							if(i)
								sprintf(szT,"%02s",token);
							strcat(szB,szT);

							token = strtok(NULL,seps);
						}

//						COleDateTime m_date;
//						m_date.ParseDateTime(str);

						strcpy(retpak.ret_GetField.TCon,szB);
					}
					break;
				default:
	//				dbgerr("收到通道%d的GetField请求,数据类型错误",pak.chan);
					break;
				}
                CString ss = "字段值:";
				str = ss + str;
				int nSize = m_db.m_ch.size();
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
					p_ListRecv->SetItemText(p_ListRecv->GetItemCount()-1,4,str);
				//                    ThAddLog("通道%dGetField命令完成",pak.chan);
				/*
				retpak.PackType=PAK_GETFIELD_VALUE;
				retpak.ret_GetField.FieldInd=pak.req_GetField.FieldInd;
				PutSendPak(&retpak,chan);
				SucProcCnt++;
				*/
				retpak.PackType=PAK_GETFIELD_VALUE;
				SendToServer(retpak);
				break;
			}
		case PAK_EOF_REQ:
			{
				int state = m_db.m_ch[chan]._rs->State;
				long IsEof = m_db.m_ch[chan]._rs->GetadoEOF();

				retpak.ret_EOF.ICon=IsEof;
				retpak.PackType=PAK_EOF_RES;

				int nSize = m_db.m_ch.size();
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
				{
					if(IsEof)
						p_ListRecv->SetItemText(p_ListRecv->GetItemCount()-1,4,"Yes");
					else
						p_ListRecv->SetItemText(p_ListRecv->GetItemCount()-1,4,"No");
				}
				SendToServer(retpak);
//				m_send.Send(&retpak,sizeof(retpak),0);

	//			retpak.ret_EOF.ICon=IsEof;
	//			retpak.PackType=PAK_EOF_RES;
	//			PutSendPak(&retpak,chan);
			}
			break;
		case PAK_MOVENEXT:
			{
				m_db.m_ch[chan]._rs->MoveNext();
				int nSize = m_db.m_ch.size();
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
					p_ListRecv->SetItemText(p_ListRecv->GetItemCount()-1,4,"移动成功");
//				retpak.PackType=PAK_COMPLETE;
				retpak.PackType=PAK_MOVENEXT_RES;
				SendToServer(retpak);
//				m_send.Send(&retpak,sizeof(retpak),0);
	//			PutSendPak(&retpak,chan);
			}
			break;
		case PAK_GETPARAMOUT_REQ:
			{

				//读取字段值
				if(m_db.m_ch[chan].iCmdType != 0)
				{
					//不是存储过程
					int nSize = m_db.m_ch.size();
					if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
						p_ListRecv->SetItemText(p_ListRecv->GetItemCount()-1,4,"不是存储过程");
					retpak.Result=0;
					retpak.PackType=PAK_GETPARAMOUT_ERR;
					strcpy(retpak.errmsg,"不是存储过程");
					SendToServer(retpak);
					break;
				}

				int state = m_db.m_ch[chan]._cp->State;
				m_db.m_ch[chan]._rs = NULL;//获得输出参数；
				if(state !=0)
				{
					int nSize = m_db.m_ch.size();
					if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
						p_ListRecv->SetItemText(p_ListRecv->GetItemCount()-1,4,"执行中...");
					retpak.Result=0;
					retpak.PackType=PAK_GETPARAMOUT_ERR;
					strcpy(retpak.errmsg,"不是存储过程");
					SendToServer(retpak);
					break;
				}


				int nSize = m_db.m_ch[chan].outpara.size();
				if(pak.req_GetParamOut.FieldInd<0||pak.req_GetParamOut.FieldInd>=m_db.m_ch[chan].outpara.size())
				{
					//越界
					string ss("索引越界:参数个数 = ");
					ss+=itoa(nSize,szBuf,10);

					int nSize = m_db.m_ch.size();
					if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
						p_ListRecv->SetItemText(p_ListRecv->GetItemCount()-1,4,ss.c_str());
					retpak.PackType=PAK_GETPARAMOUT_ERR;
					strncpy(retpak.errmsg,ss.c_str(),255);
					break;
				}
				
				long iii = pak.req_GetParamOut.FieldInd+m_db.m_ch[chan].inpara.size();
				VARIANT vv = m_db.m_ch[chan]._cp->Parameters->Item[iii]->Value;
				CString str = LPCTSTR(_bstr_t(vv));

				switch(pak.req_GetParamOut.vType)
				{
				case REF_I:
					{
						retpak.ret_GetParamOut.vType=REF_I;
						retpak.ret_GetParamOut.ICon=vv.lVal;
					}
					break;
				case REF_F:
					{
						retpak.ret_GetParamOut.vType=REF_F;
						retpak.ret_GetParamOut.FCon=vv.dblVal;
					}
					break;
				case REF_S:
					{
						CString str	= LPCTSTR(_bstr_t(vv));
						str.TrimRight();
						retpak.ret_GetParamOut.vType=REF_S;
						strcpy(retpak.ret_GetParamOut.SCon,str);
					}
					break;
				case REF_T:
					{
						COleDateTime m_date = vv.date;
						retpak.ret_GetParamOut.vType=REF_T;
						strcpy(retpak.ret_GetParamOut.TCon,m_date.Format("%Y%m%d%H%M%S"));
						break;
					}
				default:
					break;
				}
                CString  s = "参数值:";
				str = s+str;
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
					p_ListRecv->SetItemText(p_ListRecv->GetItemCount()-1,4,str);
				retpak.PackType=PAK_GETPARAMOUT_VALUE;
				retpak.ret_GetParamOut.FieldInd=pak.req_GetParamOut.FieldInd;
				SendToServer(retpak);
				break;
			}
		default:
			break;
 		}
	}
	catch(_com_error &e)
	{
		m_db.m_ch[chan].iaCount[1]++;
		char szBuf[255];
		sprintf(szBuf,"成功[%d]失败[%d]",m_db.m_ch[chan].iaCount[0],m_db.m_ch[chan].iaCount[1]);
		p_ListCommand->SetItemText(chan,1,szBuf);

		CString str;
		str.Format("异常:%s",(LPTSTR)LPCTSTR(e.Description()));
		int nSize = m_db.m_ch.size();
		if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
			p_ListRecv->SetItemText(p_ListRecv->GetItemCount()-1,4,str);
		m_db.m_ch[chan].bIsWait = false;
		retpak.Result=0;
		if(pak.PackType==PAK_SQLOPEN||pak.PackType==PAK_SQLEXEC)
		{
			retpak.PackType=PAK_SQLEXEC_ERR;
			strncpy(retpak.errmsg,str,255);
		}
		//add by yutao begin 2003-12-22
		else if(pak.PackType==PAK_GETFIELD_REQ)
		{
			retpak.PackType=PAK_GETFIELD_ERR;
			strncpy(retpak.errmsg,str,255);
		}
		//add by yutao end
		SendToServer(retpak);
		WriteLog((LPTSTR)LPCTSTR(e.Description()));
	}
}

void CSocket_Recv::Initialize()
{
	//连接数据库
	m_db.Initialize();
	//
}

void CSocket_Recv::ConnectServer()
{
	Close();
	Create();
	//与服务器连接
	char szIP[255]="192.168.3.120";
	UINT nPort = GetPrivateProfileInt("tcp","port",0,"./DBAgent.ini");
	GetPrivateProfileString("tcp", "ip","", szIP, sizeof(szIP),"./DBAgent.ini");

	BOOL ok = Connect(szIP,nPort);
	int nError = WSAGetLastError();
	status = 1;
}
/*
备注：
	此函数显示 客户端命令请求
*/
void CSocket_Recv::DisplayPack(char *szPack)
{
//	char szBuf[255];
	try{
		DBPacket pak;
		memcpy(&pak,szPack,sizeof(DBPacket));
		if (pak.HeadFlag!=0xEFFFFFFE) return;
		int chan = pak.chan;

		char szBuf[255];
		int index;
		int nSize = m_db.m_ch.size();
		if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
		{
			index = p_ListRecv->InsertItem(p_ListRecv->GetItemCount(),itoa(chan,szBuf,10),0);
			p_ListRecv->SetItemData(index,chan);

			p_ListRecv->EnsureVisible(index,0);
			char szBuf[255];
			p_ListRecv->SetItemText(index,1,m_db.GetCurTime(szBuf));
		}

		int si=2;
		switch(pak.PackType)
		{
		case PAK_PREPARESQL:
			{
				string des("准备sql语句");
				des+="[";
				des+=pak.sqlstat;
				des+="]";				
				int nSize = m_db.m_ch.size();
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
				{			
					p_ListRecv->SetItemText(index,si++,"PAK_PREPARESQL");
					p_ListRecv->SetItemText(index,si++,des.c_str());
				}
			}
			break;
		case PAK_SETPARA:
			{
				string des("外部");
				if (pak.req_SetPara.InOut==PARAM_IN)
					des = "内部";
				
				int nSize = m_db.m_ch.size();
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
					p_ListRecv->SetItemText(index,si++,"PAK_SETPARA");
				des+="参数:[";
				des+="索引:";
				des+=itoa(pak.req_SetPara.FieldInd,szBuf,10);
				switch(pak.req_SetPara.vType)
				{
				case CON_I://5
					des+=" 类型:整数  ";
					des+=" 值:";
					des+=itoa(pak.req_SetPara.ICon,szBuf,10);
					break;
				case CON_F://6
					{
						des+=" 类型:浮点数";
						des+=" 值:";
						sprintf(szBuf,"%f",pak.req_SetPara.FCon);
					
						des+=szBuf;
					}
					break;
				case CON_S://7
					{
						des+=" 类型:字符串";
						des+=" 值:";
						des+=pak.req_SetPara.SCon;
					}
					break;
				case CON_T://8
					{
						des+=" 类型:时间  ";
						des+=" 值:";
						des+=pak.req_SetPara.TCon;
					}
					break;
				default:
					break;
				}
				des+="]";
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
					p_ListRecv->SetItemText(index,si++,des.c_str());

			}
			break;
		case PAK_SQLOPEN:
		case PAK_SQLEXEC:
			{
				string des("执行语句");
				
				int nSize = m_db.m_ch.size();
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
				{
					p_ListRecv->SetItemText(index,si++,"PAK_SQLOPEN");
					p_ListRecv->SetItemText(index,si++,des.c_str());
				}
			}
			break;
		case PAK_GETFIELD_REQ:
			{
				int nSize = m_db.m_ch.size();
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
					p_ListRecv->SetItemText(index,si++,"PAK_GETFIELD_REQ");
				string des("读取字段值");
				

				des+=" 索引:";
				des+=itoa(pak.req_GetField.FieldInd,szBuf,10);
				switch(pak.req_GetField.vType)
				{
				case REF_I:
					{
						des+=" 类型:整数";
					}
					break;
				case REF_F:
					{
						des+=" 类型:浮点数";
					}
					break;
				case REF_S:
					{
						des+=" 类型:字符串";
					}
					break;
				case REF_T:
					{
						des+=" 类型:时间";
					}
					break;
				default:
	//				dbgerr("收到通道%d的GetField请求,数据类型错误",pak.chan);
					break;
				}
				VARIANT v = m_db.m_ch[chan]._rs->Fields->GetItem(short(pak.req_GetField.FieldInd))->Value;
				CString str = LPTSTR(_bstr_t(v));

				str = CString("  值：") + str;
				str = str+des.c_str();
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
					p_ListRecv->SetItemText(index,si++,str);
			}
			break;
		case PAK_EOF_REQ:
			{
				string des("查询是否记录集EOF");
				
				int nSize = m_db.m_ch.size();
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
				{
					p_ListRecv->SetItemText(index,si++,"PAK_EOF_REQ");
					p_ListRecv->SetItemText(index,si++,des.c_str());
				}
			}
			break;
		case PAK_MOVENEXT:
			{
				string des("移动记录集指针");
				
				int nSize = m_db.m_ch.size();
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
				{
					p_ListRecv->SetItemText(index,si++,"PAK_MOVENEXT");
					p_ListRecv->SetItemText(index,si++,des.c_str());
				}
			}
			break;
		case PAK_GETPARAMOUT_REQ:
			{
				int nSize = m_db.m_ch.size();
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
					p_ListRecv->SetItemText(index,si++,"PAK_GETPARAMOUT_REQ");
		
				string des("获取输出参数值");
				des+=" 索引:";
				des+=itoa(pak.req_GetParamOut.FieldInd,szBuf,10);
				
				switch(pak.req_GetParamOut.vType)
				{
				case REF_I:
					{
						des+=" 类型:整数";
					}
					break;
				case REF_F:
					{
						des+=" 类型:浮点数";
					}
					break;
				case REF_S:
					{
						des+=" 类型:字符串";
					}
					break;
				case REF_T:
					{
						des+=" 类型:时间";
					}
					break;
				default:
					break;
				}
				if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
					p_ListRecv->SetItemText(index,si++,des.c_str());
			}
			break;
		default:
			break;
 		}
	}
	catch(_com_error &e)
	{
		WriteLog((LPTSTR)LPCTSTR(e.Description()));
	}
}
/*
备注：所有发送到服务器的TCP包,都要调用此函数
*/
void CSocket_Recv::SendToServer(DBPacket &pak)
{
	int nSize = m_db.m_ch.size();
	
	CListCtrl * pList =p_ListRecv;// p_ListSend;//
	char szBuf[255];
	int index;
	int si=1;
	if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
	{
		index = pList->InsertItem(pList->GetItemCount(),itoa(pak.chan,szBuf,10),5);
		pList->SetItemData(index,pak.chan);
		char szBuf[255];
		pList->SetItemText(index,si++,m_db.GetCurTime(szBuf));
	}

	if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
	switch(pak.PackType)
	{
	case PAK_COMPLETE:pList->SetItemText(index,si++,"执行完毕");break;
	case PAK_GETFIELD_VALUE:pList->SetItemText(index,si++,"获取字段值");break;
	case PAK_EOF_RES:pList->SetItemText(index,si++,"查询记录集结果");break;
	case PAK_GETPARAMOUT_VALUE:pList->SetItemText(index,si++,"获取输出参数");break;
	}

	//
	//int len = m_send.Send(&pak,sizeof(pak));
    int len = SendPacket(m_node, (char *)&pak, sizeof(pak));
	if(pak.Result == 1)
		sprintf(szBuf,"执行成功,发送 [%-10d]字节",len);
	else
		sprintf(szBuf,"执行失败,发送 [%-10d]字节",len);
	if(!((CurChan>=nSize)||((CurChan>=0)&&(CurChan!=pak.chan))))
		pList->SetItemText(index,si++,szBuf);
	RunLog("DBAgent=>SENDPAK[%d][%s]",pak.PackType,GetDBPakName(pak.PackType));
}

void CSocket_Recv::WriteLog(char *des)
{
	CString str(des);
	if(str.Find("在异步运行时")!=-1)
		Sleep(1);

	FILE * sp = fopen("./DBAgent.log","a");
	if(sp)
	{
		COleDateTime m_date = COleDateTime::GetCurrentTime();
		fprintf(sp,"%s\n",m_date.Format("%Y-%m-%d %H:%M:%S==>")+des);
		fclose(sp);
	}
}

void CSocket_Recv::CheckCommandState()
{
	int iii;
	DBPacket retpak;
	memset(&retpak,0,sizeof(retpak));
	retpak.HeadFlag = 0xEFFFFFFE;
	retpak.PackType = PAK_COMPLETE;
	retpak.Result=1;
	try{
		for(int i=0;i<m_db.m_ch.size();i++)
		{
			iii = i;
			if(m_db.m_ch[i].bIsWait)
			{
				if(m_db.m_ch[i].iCmdType == 1)
				{
					if(m_db.m_ch[i]._rs->State != 4)
					{
						m_db.m_ch[i].bIsWait = false;
						retpak.chan=i;
						retpak.SerialNo = 1;
						retpak.PackType=PAK_SQLEXEC_OK;
						SendToServer(retpak);
						

						p_ListCommand->SetItemText(i,3,"打开");
						m_db.m_ch[i].iaCount[0]++;
						char szBuf[255];
						sprintf(szBuf,"成功[%d]失败[%d]",m_db.m_ch[i].iaCount[0],m_db.m_ch[i].iaCount[1]);
						p_ListCommand->SetItemText(i,1,szBuf);
						

						int state = m_db.m_ch[i]._rs->State;
						if(state == 0)
						for(;;)
						{			
							m_db.m_ch[i]._rs =m_db.m_ch[i]._rs->NextRecordset(NULL);
							if(m_db.m_ch[i]._rs == NULL) break;
							state = m_db.m_ch[i]._rs->State;
							if(state == 1) {
								p_ListCommand->SetItemText(i,4,"是");
								break;
							}
						
						}
//						WriteLog("SQL语句执行成功");
					}
				}
				else
				{
					//当前为存储过程
					_RecordsetPtr _rr = m_db.m_ch[i]._rs;
					if(m_db.m_ch[i]._cp->State != 4)
					{
						m_db.m_ch[i].bIsWait = false;
						retpak.chan=i;
						retpak.PackType=PAK_SQLEXEC_OK;
						retpak.SerialNo = 1;
						SendToServer(retpak);
						p_ListCommand->SetItemText(i,3,"打开");
						m_db.m_ch[i].iaCount[0]++;
						char szBuf[255];
						sprintf(szBuf,"成功[%d]失败[%d]",m_db.m_ch[i].iaCount[0],m_db.m_ch[i].iaCount[1]);
						p_ListCommand->SetItemText(i,1,szBuf);

						//得到当前记录集指针
						int state = m_db.m_ch[i]._rs->State;
						if(state == 0)
						while(true)
						{			
							if(m_db.m_ch[i]._rs==NULL)break;
							m_db.m_ch[i]._rs =m_db.m_ch[i]._rs->NextRecordset(NULL);
							if(m_db.m_ch[i]._rs==NULL)break;
							state = m_db.m_ch[i]._rs->State;
							if(state == 1) {
								p_ListCommand->SetItemText(i,4,"是");
								break;
							}
						}

//						WriteLog("存储过程执行成功");
					}
				}
			}
			
		}
	}
	catch(_com_error &e)
	{
		int i=iii;
		m_db.m_ch[i].bIsWait = false;
		retpak.chan=i;
		retpak.Result=0;
		retpak.PackType=PAK_SQLEXEC_ERR;
		retpak.SerialNo = 1;
		char szBuf[1024];
		sprintf(szBuf,"CheckCommandState==[%s]",(LPTSTR)LPCTSTR(e.Description()));
		strncpy(retpak.errmsg,szBuf,255);
		SendToServer(retpak);
		WriteLog(szBuf);
		return;
/*
		CString str("CheckCommandState");
//		str.Format("%s",LPCTSTR(e.Description()));
//		str.TrimRight();

//		strcpy(szBuf,(LPTSTR)LPCTSTR(e.Description()));
//		strcpy(retpak.errmsg,(LPTSTR)LPCTSTR(e.Description()));
		retpak.SerialNo = 1;
		SendToServer(retpak);
		p_ListCommand->SetItemText(i,3,"关闭");
		m_db.m_ch[i].iaCount[1]++;
//		char szBuf[255];
		sprintf(szBuf,"成功[%d]失败[%d]",m_db.m_ch[i].iaCount[0],m_db.m_ch[i].iaCount[1]);
		p_ListCommand->SetItemText(i,1,szBuf);
		p_ListCommand->SetItemText(i,5,(LPTSTR)LPCTSTR(e.Description()));
		retpak.Result=0;
//		strcpy(szBuf,str);
		WriteLog("CheckCommandState");*/
	}
	catch(...)
	{
		WriteLog("...CheckCommandState");
	}
}

void CSocket_Recv::WriteBillDB(DBPacket pak, int chan)
{
#ifdef VER_10
	try
	{
		char szST[25],szET[25];
		struct tm * curtime;
		curtime = localtime( &(pak.bill.StartTime));
		wsprintf(szST,"%4d-%02d-%02d %02d:%02d:%02d"
			,curtime->tm_year+1900
			,curtime->tm_mon+1
			,curtime->tm_mday
			,curtime->tm_hour
			,curtime->tm_min
			,curtime->tm_sec);
		curtime = localtime( &(pak.bill.EndTime));
		wsprintf(szET,"%4d-%02d-%02d %02d:%02d:%02d"
			,curtime->tm_year+1900
			,curtime->tm_mon+1
			,curtime->tm_mday
			,curtime->tm_hour
			,curtime->tm_min
			,curtime->tm_sec);
		
		
		char szQuery[1024];
		sprintf(szQuery,"insert into mainbill(CallId,feenum,billtype,caller,callee,starttime,endtime,calltype,fee) \
			values('%s','%s',%d,'%s','%s','%s','%s',%d,%d);"
			,pak.bill.CallId
			,pak.bill.FeeNum
			,pak.bill.BillType
			,pak.bill.Caller
			,pak.bill.Called
			,szST//pak.bill.StartTime
			,szET//pak.bill.EndTime
			,pak.bill.CallType
			,pak.bill.Fee);

		for (int i=0;i<pak.bill.SecCnt;i++)
		{
			curtime = localtime( &(pak.bill.Secs[i].StartTime));
			wsprintf(szST,"%4d-%02d-%02d %02d:%02d:%02d"
				,curtime->tm_year+1900
				,curtime->tm_mon+1
				,curtime->tm_mday
				,curtime->tm_hour
				,curtime->tm_min
				,curtime->tm_sec);
			curtime = localtime( &(pak.bill.Secs[i].EndTime));
			wsprintf(szET,"%4d-%02d-%02d %02d:%02d:%02d"
				,curtime->tm_year+1900
				,curtime->tm_mon+1
				,curtime->tm_mday
				,curtime->tm_hour
				,curtime->tm_min
				,curtime->tm_sec);
			char szBuf[255];
			sprintf(szBuf,"insert into secbill(Callid,SecNo,CardFlag,SecType,billtype,starttime,endtime,ipara1,ipara2,spara1,fee) \
				values('%s',%d,%d,%d,%d,'%s','%s',%d,%d,'%s',%d);"
				,pak.bill.CallId
				,i
				,pak.bill.Secs[i].CardFlag
				,pak.bill.Secs[i].SecType
				,pak.bill.Secs[i].BillType
				,szST
				,szET
				,pak.bill.Secs[i].IPara1
				,pak.bill.Secs[i].IPara2
				,pak.bill.Secs[i].SPara1
				,pak.bill.Secs[i].Fee);
			strcat(szQuery,szBuf);

		}

		m_db.m_ch[chan]._rs.Detach();
		m_db.m_ch[chan]._rs.CreateInstance(__uuidof(Recordset));
		m_db.m_ch[chan]._rs->Open(_bstr_t(szQuery),m_db._ctp.GetInterfacePtr()
						,adOpenForwardOnly,adLockReadOnly
						,adCmdText);			
	}
	catch(_com_error &e)
	{
		WriteLog((LPTSTR)LPCTSTR(e.Description()));
	}
#endif
}
