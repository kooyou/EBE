#pragma once


// CMisprintAddDlg �Ի���

class CMisprintAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CMisprintAddDlg)

public:
	CMisprintAddDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMisprintAddDlg();

// �Ի�������
	enum { IDD = IDD_ADDMISPRINT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����
	CString m_misprintString;
	// �滻�ַ���
	CString m_replaceString;
protected:
	virtual void OnOK();
};
