
// ClientSockDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CClientSockDemoDlg �Ի���
class CClientSockDemoDlg : public CDialogEx
{
// ����
public:
	CClientSockDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��
    void AddLog(const char *line, ...);
    void SetCount();

// �Ի�������
	enum { IDD = IDD_CLIENTSOCKDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
