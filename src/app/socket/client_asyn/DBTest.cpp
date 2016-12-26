// DBTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "DBTest.h"
#include "afxdialogex.h"


// CDBTest �Ի���

IMPLEMENT_DYNAMIC(CDBTest, CDialogEx)

CDBTest::CDBTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDBTest::IDD, pParent)
//    , m_chan(_T(""))
    , m_sql(_T(""))
{

}

CDBTest::~CDBTest()
{
}

void CDBTest::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    //DDX_Text(pDX, IDC_Channel, m_chan);
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


// CDBTest ��Ϣ�������

void SendDBClose();
void SendDBPrepare(LPCTSTR sql, DWORD& sno);
void SendDBSqlExec(DWORD& sno);
void SendDBSqlOpen(DWORD& sno);
void SendDBMoveBy(int MoveBy, DWORD& sno);
void SendDBSetParam(BYTE ind, BYTE InOut, int vType, int iValue,double fValue, const char* sValue, const char* tValue, DWORD& sno);
void SendDBUdpateField(BYTE ind, int vType, int iValue, double fValue, const char* sValue, const char* tValue, DWORD& sno);
void SendDBGetParamOut(int ind, int type, DWORD& sno);
void SendDBGetField(int ind, int type, DWORD& sno);
void SendDBOpCmd(int MsgType, DWORD& sno);

extern 

void SendDBUdpateField(BYTE ind, int vType, int iValue,double fValue, const char* sValue, const char* tValue, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    pak.chan = atoi(g_Dlg->m_node);
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
            //RunLog(chan, MT_IVRLOG | MT_IVRERR, "ͨ��%d��SetParam�ַ�����������಻�ܳ���253���ַ�����", chan);
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
        //RunLog(chan, MT_IVRLOG | MT_IVRERR, "ͨ��%d�����UpdateField����������", chan);
        break;
    }

    sno = GetTickCount();
    pak.SerialNo = sno;
    TcpSockSend((char*)&pak, sizeof(DBPacket));
}


//eof,sqlopen,sqlexec
void SendDBOpCmd(int MsgType, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.chan = atoi(g_Dlg->m_node);
    pak.SerialNo = sno;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = MsgType;
    TcpSockSend((char*)&pak, sizeof(DBPacket));
}


void SendDBSetParam(BYTE ind, BYTE InOut, int vType, int iValue,double fValue, const char* sValue, const char* tValue, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    pak.chan = atoi(g_Dlg->m_node);
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
//                RunLog(chan, MT_IVRLOG | MT_IVRERR, "ͨ��%d��SetParam�ַ�����������಻�ܳ���253���ַ�����", chan);
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
//            RunLog(chan, MT_IVRLOG | MT_IVRERR, "ͨ��%d�����SetParam����������", chan);
            break;
        }
    }
    sno = GetTickCount();
    pak.SerialNo = sno;
    TcpSockSend((char*)&pak, sizeof(DBPacket));
}

void SendDBGetParamOut(int ind, int type, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    pak.chan = atoi(g_Dlg->m_node);
    sno = GetTickCount();
    pak.SerialNo = sno;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_GETPARAMOUT_REQ;
    pak.req_GetField.vType = type;
    pak.req_GetField.FieldInd = ind;
    TcpSockSend((void *)&pak, sizeof(DBPacket));
}

void SendDBClose()
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    pak.chan = atoi(g_Dlg->m_node);
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_CLOSE;
    TcpSockSend((void *)&pak, sizeof(DBPacket));
}

//�������ݿ������
void SendDBPrepare( LPCTSTR sql, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.chan = atoi(g_Dlg->m_node);
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_PREPARESQL;
    pak.SerialNo = sno;
    strncpy(pak.sqlstat, sql, sizeof(pak.sqlstat));
    TcpSockSend((void *)&pak, sizeof(DBPacket));
}


void SendDBSqlExec(DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.chan = atoi(g_Dlg->m_node);
    pak.HeadFlag = 0xeffffffe;
    pak.SerialNo = sno;
    pak.PackType = IC_SQLEXEC;
    TcpSockSend((void *)&pak, sizeof(DBPacket));
}


//0-�ɹ�,1-ʧ��
void SendDBSqlOpen(DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    pak.chan = atoi(g_Dlg->m_node);
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_SQLOPEN;
    sno = GetTickCount();
    pak.SerialNo = sno;
    TcpSockSend((char*)&pak, sizeof(DBPacket));
}


void SendDBGetField(int ind, int type, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.chan = atoi(g_Dlg->m_node);
    pak.SerialNo = sno;
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_GETFIELD_REQ;
    pak.req_GetField.vType = type;
    pak.req_GetField.FieldInd = ind;
    TcpSockSend((void *)&pak, sizeof(DBPacket));
}


//
void SendDBMoveBy(int MoveBy, DWORD& sno)
{
    DBPacket pak;
    memset(&pak, 0, sizeof(pak));
    sno = GetTickCount();
    pak.SerialNo = sno;
    pak.chan = atoi(g_Dlg->m_node);
    pak.HeadFlag = 0xeffffffe;
    pak.PackType = IC_MOVENEXT;
    pak.req_MoveBy.MoveBy = MoveBy;
    TcpSockSend((void *)&pak, sizeof(DBPacket));
}


void CDBTest::OnBnClickedSendprepare()
{
    DWORD sno = 0;
    UpdateData();
    SendDBPrepare(m_sql, sno);
}


void CDBTest::OnBnClickedSendGetField()
{
    DWORD sno = 0;
    SendDBGetField(1, 3, sno);
}


void CDBTest::OnBnClickedSendmoveby()
{
    DWORD sno = 0;
    SendDBMoveBy(1, sno);
}


void CDBTest::OnBnClickedSendexec()
{
    DWORD sno = 0;
    SendDBSqlExec(sno);
}


void CDBTest::OnBnClickedSendclose()
{
    SendDBClose();
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
        //ar << m_chan;

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
        //ar >> m_chan;

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



