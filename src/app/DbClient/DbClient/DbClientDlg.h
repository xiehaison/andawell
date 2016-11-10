
// DbClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDbClientDlg �Ի���
class CDbClientDlg : public CDialogEx
{
// ����
public:
	CDbClientDlg(CWnd* pParent = NULL);	// ��׼���캯��
    CSrvSock lsnSocket;
    CSocket *findsock();

// �Ի�������
	enum { IDD = IDD_DBCLIENT_DIALOG };

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
    afx_msg void OnBnClickedConfig();
    afx_msg void OnBnClickedStart();
    // ����������־
    int m_start_flag;
    afx_msg void OnBnClickedSqlsend();
    // sql���
    CString m_sql;
    // �����־
    CString m_out;
    // �����־
    CEdit m_ctrl_out;
    CListCtrl m_sql_result;
};
