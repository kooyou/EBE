#pragma once


// CMisprintSetDlg �Ի���

class CMisprintSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CMisprintSetDlg)

public:
	CMisprintSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMisprintSetDlg();

// �Ի�������
	enum { IDD = IDD_MISPRINTSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
