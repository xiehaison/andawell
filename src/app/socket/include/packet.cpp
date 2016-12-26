#include "stdafx.h"
#include "packet.h"

char *GetMsgTypeStr(DWORD type)
{
    switch (type)
    {
    case     ID_RegTestMachine:  return "ID_RegTestMachine";
    case     ID_RegTestMachineResult:  return "ID_RegTestMachineResult";
    case     ID_ResetTestMachine:  return "ID_ResetTestMachine";
    case     ID_ResetTestMachineResult:  return "ID_ResetTestMachineResult";
    case     ID_SynTestMachineInfo:  return "ID_SynTestMachineInfo";
    case     ID_SynTestMachineInfoResult:  return "ID_SynTestMachineInfoResult";
    case     ID_StartTestPlan:  return "ID_StartTestPlan";
    case     ID_StartTestPlanResult:  return "ID_StartTestPlanResult";
    case     ID_PauseTestPlan:  return "ID_PauseTestPlan";
    case     ID_PauseTestPlanResult:  return "ID_PauseTestPlanResult";
    case     ID_SuspendTestPlan:  return "ID_SuspendTestPlan";
    case     ID_SuspendTestPlanResult:  return "ID_SuspendTestPlanResult";
    case     ID_ContinueTestPlan:  return "ID_ContinueTestPlan";
    case     ID_ContinueTestPlanResult:  return "ID_ContinueTestPlanResult";
    case     ID_StopTestPlan:  return "ID_StopTestPlan";
    case     ID_StopTestPlanResult:  return "ID_StopTestPlanResult";
    case     ID_ProgressPlan:  return "ID_ProgressPlan";
    case     ID_ProgressPlanResult:  return "ID_ProgressPlanResult";
    case     ID_ReqMonitor:  return "ID_ReqMonitor";
    case     ID_ReqMonitorResult:  return "ID_ReqMonitorResult";
    case     ID_ReqMonitorData:  return "ID_ReqMonitorData";
    case     ID_ReqMonitorDataResult:  return "ID_ReqMonitorDataResult";
    case    IA_Login: return "IA_Login                     ";
    case    IA_LoginResult: return "IA_LoginResult               ";
    case    IA_ReqServerInfo: return "IA_ReqServerInfo             ";
    case    IA_ReqServerInfoResult: return "IA_ReqServerInfoResult       ";
    case    IA_ReqTestMachineInfo: return "IA_ReqTestMachineInfo        ";
    case    IA_ReqTestMachineInfoResult: return "IA_ReqTestMachineInfoResult  ";
    case    IA_ReqMonitor: return "IA_ReqMonitor                ";
    case    IA_ReqMonitorResult: return "IA_ReqMonitorResult          ";
    case    IA_TestString: return "IA_TestString";
    case    IB_ReqCtrlInfo: return "IB_ReqCtrlInfo = IB_START    ";
    case    IB_ReqCtrlInfoResult: return "IB_ReqCtrlInfoResult         ";
    case    IB_StartTest: return "IB_StartTest                 ";
    case    IB_PauseTest: return "IB_PauseTest                 ";
    case    IB_SuspendTest: return "IB_SuspendTest               ";
    case    IB_StopTest: return "IB_StopTest                  ";
    case    IB_ContinueTest: return "IB_ContinueTest              ";
    case    IB_ReqTestData: return "IB_ReqTestData               ";
    case    IB_ReqTestDataResult: return "IB_ReqTestDataResult         ";
    case    IC_NONE: return "IC_NONE                      ";
    case    IC_PREPARESQL: return "IC_PREPARESQL                ";
    case    IC_PREPARESQL_READY: return "IC_PREPARESQL_READY          ";
    case    IC_SETPARA: return "IC_SETPARA                   ";
    case    IC_SETPARA_READY: return "IC_SETPARA_READY             ";
    case    IC_SQLEXEC: return "IC_SQLEXEC                   ";
    case    IC_SQLEXEC_OK: return "IC_SQLEXEC_OK                ";
    case    IC_SQLEXEC_ERR: return "IC_SQLEXEC_ERR               ";
    case    IC_SQLOPEN: return "IC_SQLOPEN                   ";
    case    IC_GETFIELD_REQ: return "IC_GETFIELD_REQ              ";
    case    IC_GETFIELD_VALUE: return "IC_GETFIELD_VALUE            ";
    case    IC_GETFIELD_ERR: return "IC_GETFIELD_ERR              ";
    case    IC_EOF_REQ: return "IC_EOF_REQ                   ";
    case    IC_EOF_RES: return "IC_EOF_RES                   ";
    case    IC_MOVENEXT: return "IC_MOVENEXT                  ";
    case    IC_MOVENEXT_RES: return "IC_MOVENEXT_RES              ";
    case    IC_GETPARAMOUT_REQ: return "IC_GETPARAMOUT_REQ           ";
    case    IC_GETPARAMOUT_VALUE: return "IC_GETPARAMOUT_VALUE         ";
    case    IC_GETPARAMOUT_ERR: return "IC_GETPARAMOUT_ERR           ";
    case    IC_COMPLETE: return "IC_COMPLETE                  ";
    case    IC_DBCFG: return "IC_DBCFG                     ";
    case    IC_PROXYINFO: return "IC_PROXYINFO                 ";
    case    IC_UPDATEFIELD: return "IC_UPDATEFIELD               ";
    case    IC_UPDATEFIELD_RES: return "IC_UPDATEFIELD_RES           ";
    case    IC_CLOSE: return "IC_CLOSE                     ";
    case    IE_ReqCtrlInfo: return "IE_ReqCtrlInfo               ";
    case    IE_ReqCtrlInfoResult: return "IE_ReqCtrlInfoResult         ";
    case    IE_StartTest: return "IE_StartTest                 ";
    case    IE_PauseTest: return "IE_PauseTest                 ";
    case    IE_SuspendTest: return "IE_SuspendTest               ";
    case    IE_StopTest: return "IE_StopTest                  ";
    case    IE_ContinueTest: return "IE_ContinueTest              ";
    case    IE_ReqTestData: return "IE_ReqTestData               ";
    case    IE_ReqTestDataResult: return "IE_ReqTestDataResult         ";

    default:;
    }
    return NULL;
}

