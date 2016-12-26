// SockSrvDemoDlg.h : header file
//

#if !defined(AFX_SOCKSRVDEMODLG_H__AED49D0C_6453_4449_B850_E81A7E5D9724__INCLUDED_)
#define AFX_SOCKSRVDEMODLG_H__AED49D0C_6453_4449_B850_E81A7E5D9724__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSockSrvDemoDlg dialog

class CSockSrvDemoDlg : public CDialog
{
// Construction
public:
	void AddLog(const char* line,...);
	CSockSrvDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSockSrvDemoDlg)
	enum { IDD = IDD_SOCKSRVDEMO_DIALOG };
	CEdit	m_ctrlLog;
	int		m_code;
	CString	m_content;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockSrvDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSockSrvDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT , LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKSRVDEMODLG_H__AED49D0C_6453_4449_B850_E81A7E5D9724__INCLUDED_)
