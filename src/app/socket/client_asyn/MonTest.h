#pragma once
#include "resource.h"
#include "ChartCtrl.h"
//#include "ColourPicker.h"
#include "ChartLineSerie.h"



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
    afx_msg void OnBnClickedStart();
    virtual BOOL OnInitDialog();

//    CChartAxis* GetSelectedAxis();
    CChartCtrl m_ChartCtrl;

    // �����豸
    afx_msg void OnBnClickedTestchart();
    // //����صļ��ڵ�
    CString m_dstnode;
    afx_msg void OnBnClickedTestchart2();
};
