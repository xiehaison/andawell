#pragma once
#include "resource.h"
#include "ChartCtrl.h"
#include "packet.h"

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
    // ���ض˱��
    int m_rnode;
	bool m_bstart;
    afx_msg void OnBnClickedButton1();
    // �û�id
    int m_userid;
    // chartͼ��
    CChartCtrl m_ChartCtrl;
    virtual BOOL OnInitDialog();
    void OnAddseries(int Type, COLORREF Color, int width, int height, int penstyle, int count, double *XValues, double *YValues);
    void OnRecvData(S_Emulate_Data data,DWORD count,DWORD type);
	void StartMonitor();
	void StopMonitor();
	// �����ַ���
    CString m_teststring;
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedTestchart();
    COLORREF m_Color;
    int  m_width;
    int  m_height;
    int m_penstyle;
    int m_Type;
	bool pause_stat;
	bool start_stat;

    afx_msg void OnBnClickedClearchart();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedPause();
	// �����ص���������
	DWORD m_reqtype;
};
