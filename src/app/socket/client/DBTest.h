#pragma once


// CDBTest 对话框

class CDBTest : public CDialogEx
{
	DECLARE_DYNAMIC(CDBTest)

public:
	CDBTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDBTest();

// 对话框数据
	enum { IDD = IDD_DB_Test };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedSendprepare();  
    afx_msg void OnBnClickedSendGetField();
    afx_msg void OnBnClickedSendmoveby();
    afx_msg void OnBnClickedSendexec();
    afx_msg void OnBnClickedSendclose();
    // 通道
    CString m_chan;
    afx_msg void OnDestroy();
    virtual BOOL OnInitDialog();
    CString m_sql;
};
