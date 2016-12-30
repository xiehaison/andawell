#pragma once
#include "resource.h"
#include "afxcmn.h"

// CMonTest �Ի���
class CMonTest : public CDialogEx
{
	DECLARE_DYNAMIC(CMonTest)

public:
	CMonTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMonTest();

// �Ի�������
	enum { IDD = IDD_MON_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();

    // ���ܼ��
    BOOL m_accept_monitor;
    // �ٶ�
    // �����ַ���
    CString m_teststring;
    afx_msg void OnBnClickedButton1();
    // �ڵ��
    int m_testspeed;
    // //�ɼ�������������
    CString m_gained;
    // �������е�������
    CString m_databuf;
    // �Ѿ����͵�������
    CString m_SentCount;
    // ��ʧ����������
    CString m_lostcount;
    afx_msg void OnBnClickedCheck1();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedSendsampling();
    // ��ص����ض�
    DWORD m_rnode;
    // ��Ŀ״̬:�ѱ����,�ȴ���ʼ(idle),����������,��ͣ,����,ֹͣ
    int m_projstatus;
    // ��Ŀ���
    int m_project_no;
    // �ܲɼ���
    DWORD m_totalcount;
    // �ɼ��ٶ�
    CProgressCtrl m_speedctrl;
};
