// clientDlg.h : header file
//

#include "afxwin.h"
#if !defined(AFX_CLIENTDLG_H__CC6A4E9D_D70C_4A35_AEF4_AA01BE3A127D__INCLUDED_)
#define AFX_CLIENTDLG_H__CC6A4E9D_D70C_4A35_AEF4_AA01BE3A127D__INCLUDED_

#include "MonTest.h"
#include "ManageEmu.h"
#include "ProgTestEmu.h"

#include "afxcmn.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

class CClientDlg : public CDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
	CEdit	m_ctrlLog;
	CString	m_strLog;
	CString	m_rip;
	CString	m_rport;
	CString	m_node;
    int bconn;
    CMonTest        m_montest;
    CManageEmu      m_manager;
    CProgTestEmu    m_ProgTest;
    //}}AFX_DATA

	void Output(LPCTSTR line, ...)
	{
		char buf[1024];
		memset(buf,0,1024);
		
		va_list args;
		va_start(args, line);
		_vsnprintf (buf, sizeof(buf), line, args);
		va_end(args);
		
		strcat(buf, "\r\n");
		
		CString dline;
		dline.Format("%s",buf);
		UpdateData(TRUE);
		m_strLog += dline;
		int linecnt=m_ctrlLog.GetLineCount();
		if (linecnt>500)
		{
			int pos=m_strLog.Find("\r\n");
			m_strLog.Delete(0,pos+2);
		}
		UpdateData(FALSE);
		m_ctrlLog.SetSel(m_strLog.GetLength(),m_strLog.GetLength());
        OutputDebugString(buf);
	}	
    int OnSockStatus_Asyn(T_MsgNotify msg);
    int OnSockRecv_Asyn(T_Msg *msg);
    void ShowConnectStatus(int status =1);


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedSendsql();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    //afx_msg LRESULT OnSockRecv(WPARAM wparam, LPARAM lparam);
    //afx_msg LRESULT OnSockStatus(WPARAM wparam, LPARAM lparam);

    afx_msg void OnDestroy();
    CTabCtrl m_tab;
    afx_msg void OnSize(UINT nType, int cx, int cy);
    void Adjust();

    afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedClear();

};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__CC6A4E9D_D70C_4A35_AEF4_AA01BE3A127D__INCLUDED_)
