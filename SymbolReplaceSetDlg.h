#pragma once
#include "Resource.h"
#include "afxwin.h"

// CSymbolReplaceSetDlg �Ի���

class CSymbolReplaceSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSymbolReplaceSetDlg)

public:
	CSymbolReplaceSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSymbolReplaceSetDlg();

// �Ի�������
	enum { IDD = IDD_SYMBOL_REPLACE_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	// ����
	BOOL m_Symbol1;
	// ���
	BOOL m_Symbol2;
	// �ֺ�
	BOOL m_Symbol3;
	// ð��
	BOOL m_Symbol4;
	// ���˺�
	BOOL m_Symbol5;
	// ���ۺ�
	BOOL m_Symbol6;
	// ����
	BOOL m_Symbol7;
	// �����ۺ�
	BOOL m_Symbol8;

private:
	CBrush m_brush;
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	// ȫ���滻���ǲ����滻
	int m_nSelect;
	// ˫���ۺ��滻
	BOOL m_IsDoubleDash;
	afx_msg void OnBnClickedDoubleDash();
	// ˫���ۺ��滻�ַ���
	CEdit m_doubleDashEdit;
	// �ֺ�
	CString m_editString3;
	// ����
	CString m_editString1;
	// ���
	CString m_editString2;
	// ð��
	CString m_editString4;
	// ���˺�
	CString m_editString5;
	// ���ۺ�
	CString m_editString6;
	// �����ۺ�
	CString m_editString8;
	// ����
	CString m_editString7;
};
