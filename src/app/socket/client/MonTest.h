#pragma once
#include "resource.h"

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
};
