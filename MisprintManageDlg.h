#pragma once
#include "afxcmn.h"
#include "Resource.h"
#include "MisprintManage.h"


// CMisprintManageDlg �Ի���

class CMisprintManageDlg : public CDialog
{
	DECLARE_DYNAMIC(CMisprintManageDlg)

public:
	CMisprintManageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMisprintManageDlg();

// �Ի�������
	enum { IDD = IDD_MisprintManageDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �����б�
	CListCtrl m_misprintListCtrl;
	afx_msg void OnBnClickedDelMisprint();
	virtual BOOL OnInitDialog();

	void OnMisprintCheck(CRichEditView* pRichEditView);
	void OnMisprintAddmisprint(CString AddMisprint);

	void SetMisprintSet();

private:
	void RemoveMisprint(CString misprintString);

private:
	MisprintManage m_misprintManage;
};
