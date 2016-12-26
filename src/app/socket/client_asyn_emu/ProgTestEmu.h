#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CProgTestEmu �Ի���

class CProgTestEmu : public CDialogEx
{
	DECLARE_DYNAMIC(CProgTestEmu)

public:
	CProgTestEmu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProgTestEmu();

// �Ի�������
	enum { IDD = IDD_PROJ_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    // ���Խ���
    CProgressCtrl m_progress;
    CString m_plan_name;
    // ��Ŀ��
    CString m_project_name;
    // ������ֵ
    int m_progress_num;
    afx_msg void OnBnClickedStart();
    afx_msg void OnBnClickedPause();
    afx_msg void OnBnClickedSuspend();
    afx_msg void OnBnClickedContinue();
    afx_msg void OnBnClickedClose();
    afx_msg void OnBnClickedSendprogress();
};
