
// ServerDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CServerDemoDlg �Ի���
class CServerDemoDlg : public CDialogEx
{
// ����
public:
	CServerDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��
    void SetCounter(DWORD count);
// �Ի�������
	enum { IDD = IDD_SERVERDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
    void AddLog(const char *line, ...);

    CEdit m_ctrlLog;
    int m_code;
    CString m_content;
    CString m_ip;
    int m_port;
};
