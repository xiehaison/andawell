#pragma once


// CManageEmu �Ի���

class CManageEmu : public CDialogEx
{
	DECLARE_DYNAMIC(CManageEmu)

public:
	CManageEmu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CManageEmu();

// �Ի�������
	enum { IDD = IDD_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedConfig();
    afx_msg void OnBnClickedRegister();
};
