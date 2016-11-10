
// DbClientDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDbClientDlg 对话框
class CDbClientDlg : public CDialogEx
{
// 构造
public:
	CDbClientDlg(CWnd* pParent = NULL);	// 标准构造函数
    CSrvSock lsnSocket;
    CSocket *findsock();

// 对话框数据
	enum { IDD = IDD_DBCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedConfig();
    afx_msg void OnBnClickedStart();
    // 服务启动标志
    int m_start_flag;
    afx_msg void OnBnClickedSqlsend();
    // sql语句
    CString m_sql;
    // 输出日志
    CString m_out;
    // 输出日志
    CEdit m_ctrl_out;
    CListCtrl m_sql_result;
};
