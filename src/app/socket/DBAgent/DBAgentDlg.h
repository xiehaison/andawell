// DBGateDlg.h : header file
//

#if !defined(AFX_DBGATEDLG_H__F88C6B15_156A_48BA_AE6A_5184DFBC5A91__INCLUDED_)
#define AFX_DBGATEDLG_H__F88C6B15_156A_48BA_AE6A_5184DFBC5A91__INCLUDED_

#include "Socket_Recv.h"	// Added by ClassView
#include "AppAgent.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDBGateDlg dialog

void MyOnMsg(int node, char *msg, int len);
void MyOnNotify(int node, int notify,char *msg);

  
class CDBGateDlg : public CDialog
{
public:

// Construction
public:
	bool bIsStart;
	CSocket_Recv m_recv;
	void init_control();
	void adjust();
//	CImageList m_imagelist1;
	CDBGateDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDBGateDlg)
	enum { IDD = IDD_DBGATE_DIALOG };
	CListCtrl	m_buf;
	CListCtrl	m_commandserial;
	CListCtrl	m_sendserial;
	CListCtrl	m_channel;
	CListCtrl	m_listCommand;
    CAppAgent   m_appagent;
	CTabCtrl	m_tab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBGateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDBGateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonDb();
	afx_msg void OnKillfocusEdit4();
	afx_msg void OnDblclkListCommandserial(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListBuf(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonConfig();
	afx_msg void OnButtonView();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonDb3();
    afx_msg LRESULT OnSockRecv(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnSockRecvStatus(WPARAM wparam, LPARAM lparam);

    // //客户端数量
    int m_clientnum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBGATEDLG_H__F88C6B15_156A_48BA_AE6A_5184DFBC5A91__INCLUDED_)
