#pragma once


// CCtrlTest �Ի���

class CCtrlTest : public CDialogEx
{
	DECLARE_DYNAMIC(CCtrlTest)

public:
	CCtrlTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCtrlTest();

// �Ի�������
	enum { IDD = IDD_CTRL_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedLogin();
};
