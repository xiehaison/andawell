#pragma once
#include "afxcmn.h"


// CAppAgent �Ի���

class CAppAgent : public CDialogEx
{
	DECLARE_DYNAMIC(CAppAgent)

public:
	CAppAgent(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAppAgent();
    void Adjust();

// �Ի�������
	enum { IDD = IDD_APPAGENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    // �ڵ��б�
    CListCtrl m_nodelist;
    // ��Ϣ�б�
    CListCtrl m_msglist;
    CTabCtrl m_tab;
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
