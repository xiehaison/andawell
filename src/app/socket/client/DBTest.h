#pragma once


// CDBTest �Ի���

class CDBTest : public CDialogEx
{
	DECLARE_DYNAMIC(CDBTest)

public:
	CDBTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDBTest();

// �Ի�������
	enum { IDD = IDD_DB_Test };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedSendprepare();  
    afx_msg void OnBnClickedSendGetField();
    afx_msg void OnBnClickedSendmoveby();
    afx_msg void OnBnClickedSendexec();
    afx_msg void OnBnClickedSendclose();
    // ͨ��
    CString m_chan;
    afx_msg void OnDestroy();
    virtual BOOL OnInitDialog();
    CString m_sql;
};
