#pragma once
#include "afxcmn.h"
#include "resource.h"


// CManager �Ի���

class CManager : public CDialogEx
{
	DECLARE_DYNAMIC(CManager)

public:
	CManager(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CManager();

// �Ի�������
	enum { IDD = IDD_Manager };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_nodelist;
    CListCtrl m_userlist;
    CTabCtrl m_tab;
    virtual BOOL OnInitDialog();
};
