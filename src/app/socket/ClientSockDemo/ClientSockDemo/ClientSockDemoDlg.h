
// ClientSockDemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CClientSockDemoDlg 对话框
class CClientSockDemoDlg : public CDialogEx
{
// 构造
public:
	CClientSockDemoDlg(CWnd* pParent = NULL);	// 标准构造函数
    void AddLog(const char *line, ...);
    void SetCount();

// 对话框数据
	enum { IDD = IDD_CLIENTSOCKDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedStartup();
    CEdit m_ctrlLog;
    CString m_ip;
    DWORD m_port;
    int m_node;
    int m_span;
    int m_count;
    int m_size;
    CString m_content;
    afx_msg void OnBnClickedZero();
    afx_msg void OnBnClickedSend();
    afx_msg void OnBnClickedConsend();
};
