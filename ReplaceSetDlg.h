#pragma once


// CReplaceSetDlg �Ի���

class CReplaceSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CReplaceSetDlg)

public:
	CReplaceSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReplaceSetDlg();

// �Ի�������
	enum { IDD = IDD_REPLACESETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ȫ��ƥ��
	BOOL m_fullword;
	// ��Сдƥ��
	BOOL m_capitzlization;
	BOOL m_IsAutoReplace;
};
