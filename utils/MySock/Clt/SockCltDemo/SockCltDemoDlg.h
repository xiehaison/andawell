// SockCltDemoDlg.h : header file
//

#if !defined(AFX_SOCKCLTDEMODLG_H__02A4D9AA_DD4A_4FC8_AC56_8DB244AE97CD__INCLUDED_)
#define AFX_SOCKCLTDEMODLG_H__02A4D9AA_DD4A_4FC8_AC56_8DB244AE97CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSockCltDemoDlg dialog

class CSockCltDemoDlg : public CDialog
{
// Construction
public:
	void AddRecvLine(const char* line,...);
	CSockCltDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSockCltDemoDlg)
	enum { IDD = IDD_SOCKCLTDEMO_DIALOG };
	CEdit	m_ctrlLog;
	CButton	m_startup;
	CStatic	m_recvcnt;
	CString	m_sendtext;
	int		m_sendcnt;
	int		m_interval;
	CString	m_cenip;
	int		m_cenport;
	int		m_paksize;
	int		m_code;
	CString	m_log;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockCltDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSockCltDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	afx_msg void OnStartup();
	afx_msg void OnConsend();
	afx_msg void OnZero();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKCLTDEMODLG_H__02A4D9AA_DD4A_4FC8_AC56_8DB244AE97CD__INCLUDED_)
