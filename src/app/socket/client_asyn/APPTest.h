#pragma once


// CAPPTest �Ի���

class CAPPTest : public CDialogEx
{
	DECLARE_DYNAMIC(CAPPTest)

public:
	CAPPTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAPPTest();

// �Ի�������
	enum { IDD = IDD_APP_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
    // Ŀ��ڵ�
    BYTE m_node;
    // ��Ϣ����
    int m_type;
};
