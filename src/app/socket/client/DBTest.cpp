// DBTest.cpp : 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "DBTest.h"
#include "afxdialogex.h"

#include "../include/packet.h"

// CDBTest 对话框

IMPLEMENT_DYNAMIC(CDBTest, CDialogEx)

CDBTest::CDBTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDBTest::IDD, pParent)
    , m_chan(_T(""))
    , m_sql(_T(""))
{

}

CDBTest::~CDBTest()
{
}

void CDBTest::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_Channel, m_chan);
    DDX_Text(pDX, IDC_SQL_STR, m_sql);
}


BEGIN_MESSAGE_MAP(CDBTest, CDialogEx)
    ON_BN_CLICKED(IDC_SendPrepare, &CDBTest::OnBnClickedSendprepare)
    ON_BN_CLICKED(IDC_SendGetField, &CDBTest::OnBnClickedSendGetField)
    ON_BN_CLICKED(IDC_SendMoveBy, &CDBTest::OnBnClickedSendmoveby)
    ON_BN_CLICKED(IDC_SendExec, &CDBTest::OnBnClickedSendexec)
    ON_BN_CLICKED(IDC_SendClose, &CDBTest::OnBnClickedSendclose)
    ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDBTest 消息处理程序

void SendDBClose(int chan);
void SendDBPrepare(int chan, LPCTSTR sql, DWORD& sno);
void SendDBSqlExec(int chan, DWORD& sno);
void SendDBSqlOpen(int chan, DWORD& sno);
void SendDBMoveBy(int chan, int MoveBy, DWORD& sno);
void SendDBSetParam(int chan, BYTE ind, BYTE InOut, int vType, int iValue,double fValue, const char* sValue, const char* tValue, DWORD& sno);
void SendDBUdpateField(int chan, BYTE ind, int vType, int iValue, double fValue, const char* sValue, const char* tValue, DWORD& sno);
void SendDBGetParamOut(int chan, int ind, int type, DWORD& sno);
void SendDBGetField(int chan, int ind, int type, DWORD& sno);
void SendDBOpCmd(int chan, int MsgType, DWORD& sno);



void SendDBUdpateField(int chan, BYTE ind, int vType, int iValue,double fValue, const char* sValue, const char* tValue, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    pak.chan = chan;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_UPDATEFIELD;
    pak.req_updatefield.vType = vType;
    pak.req_updatefield.FieldInd = ind;

    switch (vType)
    {
    case CON_I:
        pak.req_updatefield.ICon = iValue;
        break;
    case CON_S:
    {
        char temp[254] = "";
        memset(temp, 0, 254);
        if (strlen(sValue)>253)
        {
            //RunLog(chan, MT_IVRLOG | MT_IVRERR, "通道%d的SetParam字符参数长度最多不能超过253个字符长度", chan);
            memcpy(temp, sValue, 253);
        }
        else
            strcpy(temp, sValue);

        strcat(pak.req_updatefield.SCon, "'");
        strcat(pak.req_updatefield.SCon, temp);
        strcat(pak.req_updatefield.SCon, "'");
        break;
    }
    case CON_T:
        strcpy(pak.req_updatefield.TCon, tValue);
        break;
    case CON_F:
        pak.req_updatefield.FCon = fValue;
        break;
    default:
        //RunLog(chan, MT_IVRLOG | MT_IVRERR, "通道%d错误的UpdateField包数据类型", chan);
        break;
    }

    sno = GetTickCount();
    pak.SerialNo = sno;
    SendPacket((char*)&pak, sizeof(DBPacket));
}


//eof,sqlopen,sqlexec
void SendDBOpCmd(int chan, int MsgType, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.chan = chan;
    pak.SerialNo = sno;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = MsgType;
    SendPacket((char*)&pak, sizeof(DBPacket));
}


void SendDBSetParam(int chan, BYTE ind, BYTE InOut, int vType, int iValue,double fValue, const char* sValue, const char* tValue, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    pak.chan = chan;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_SETPARA;
    pak.req_SetPara.vType = vType;
    pak.req_SetPara.FieldInd = ind;
    pak.req_SetPara.InOut = InOut;

    if (InOut == PARAM_IN)
    {
        switch (vType)
        {
        case CON_I:
            pak.req_SetPara.ICon = iValue;
            break;
        case CON_S:
        {
            char temp[254] = "";
            memset(temp, 0, 254);
            if (strlen(sValue)>253)
            {
//                RunLog(chan, MT_IVRLOG | MT_IVRERR, "通道%d的SetParam字符参数长度最多不能超过253个字符长度", chan);
                memcpy(temp, sValue, 253);
            }
            else
                strcpy(temp, sValue);

            strcat(pak.req_SetPara.SCon, "'");
            strcat(pak.req_SetPara.SCon, temp);
            strcat(pak.req_SetPara.SCon, "'");
            break;
        }
        case CON_T:
            strcpy(pak.req_SetPara.TCon, tValue);
            break;
        case CON_F:
            pak.req_SetPara.FCon = fValue;
            break;
        default:
//            RunLog(chan, MT_IVRLOG | MT_IVRERR, "通道%d错误的SetParam包数据类型", chan);
            break;
        }
    }
    sno = GetTickCount();
    pak.SerialNo = sno;
    SendPacket((char*)&pak, sizeof(DBPacket));
}

void SendDBGetParamOut(int chan, int ind, int type, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    pak.chan = chan;
    sno = GetTickCount();
    pak.SerialNo = sno;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_GETPARAMOUT_REQ;
    pak.req_GetField.vType = type;
    pak.req_GetField.FieldInd = ind;
    SendPacket((char*)&pak, sizeof(DBPacket));
}

void SendDBClose(int chan)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    pak.chan = chan;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_CLOSE;
    SendPacket((char*)&pak, sizeof(DBPacket));
}

//发送数据库操作包
void SendDBPrepare(int chan, LPCTSTR sql, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.chan = chan;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_PREPARESQL;
    pak.SerialNo = sno;
    strncpy(pak.sqlstat, sql, sizeof(pak.sqlstat));
    SendPacket((char*)&pak, sizeof(DBPacket));
}


void SendDBSqlExec(int chan, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.chan = chan;
    pak.HeadFlag = 0xeffffffe;
    pak.SerialNo = sno;
    pak.PackType = IC_SQLEXEC;
    SendPacket((char*)&pak, sizeof(DBPacket));
}


//0-成功,1-失败
void SendDBSqlOpen(int chan, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    pak.chan = chan;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_SQLOPEN;
    sno = GetTickCount();
    pak.SerialNo = sno;
    SendPacket((char*)&pak, sizeof(DBPacket));
}


void SendDBGetField(int chan, int ind, int type, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.chan = chan;
    pak.SerialNo = sno;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_GETFIELD_REQ;
    pak.req_GetField.vType = type;
    pak.req_GetField.FieldInd = ind;
    SendPacket((char*)&pak, sizeof(DBPacket));
}


//
void SendDBMoveBy(int chan, int MoveBy, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.SerialNo = sno;
    pak.chan = chan;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_MOVENEXT;
    pak.req_MoveBy.MoveBy = MoveBy;
    SendPacket((char*)&pak, sizeof(DBPacket));
    DWORD type = GetMsgType((S_Msg_Header*)&pak);
}


void CDBTest::OnBnClickedSendprepare()
{
    DWORD sno = 0;
    UpdateData();
    SendDBPrepare(atoi(m_chan), m_sql, sno);
}


void CDBTest::OnBnClickedSendGetField()
{
    DWORD sno = 0;
    SendDBGetField(atoi(m_chan), 1, 3, sno);
}


void CDBTest::OnBnClickedSendmoveby()
{
    DWORD sno = 0;
    SendDBMoveBy(atoi(m_chan), 1, sno);
}


void CDBTest::OnBnClickedSendexec()
{
    DWORD sno = 0;
    SendDBSqlExec(atoi(m_chan), sno);
}


void CDBTest::OnBnClickedSendclose()
{
    SendDBClose(atoi(m_chan));
}


void CDBTest::OnDestroy()
{
    CDialogEx::OnDestroy();
    UpdateData();
    CFile file("settings_client_dbtest.tmp", CFile::modeReadWrite | CFile::modeCreate);
    CArchive ar(&file, CArchive::store);
    try
    {
        ar << m_sql;
        ar << m_chan;

        ar.Close();
    }
    catch (CMemoryException* e)
    {
        e->ReportError();
        ar.Close();
    }
    catch (CFileException* e)
    {
        e->ReportError();
        ar.Close();
    }
    catch (CException* e)
    {
        e->ReportError();
        ar.Close();
    }
    CDialog::OnDestroy();

}


BOOL CDBTest::OnInitDialog()
{
    CFile file("settings_client_dbtest.tmp", CFile::modeReadWrite);

    CArchive ar(&file, CArchive::load);
    try
    {
        ar >> m_sql;
        ar >> m_chan;

        ar.Close();
    }
    catch (CMemoryException* e)
    {
        e->ReportError();
        ar.Close();
    }
    catch (CFileException* e)
    {
        e->ReportError();
        ar.Close();
    }
    catch (CException* e)
    {
        e->ReportError();
        ar.Close();
    }

    CDialogEx::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
}



