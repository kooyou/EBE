// ReplaceSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EBE.h"
#include "ReplaceSetDlg.h"


// CReplaceSetDlg �Ի���

IMPLEMENT_DYNAMIC(CReplaceSetDlg, CDialog)

CReplaceSetDlg::CReplaceSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReplaceSetDlg::IDD, pParent)
	, m_fullword(FALSE)
	, m_capitzlization(FALSE)
	, m_IsAutoReplace(FALSE)
{

}

CReplaceSetDlg::~CReplaceSetDlg()
{
}

void CReplaceSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_WORDFULL, m_fullword);
	DDX_Check(pDX, IDC_CAPITLIZATION, m_capitzlization);
	DDX_Check(pDX, IDC_AUTORUN, m_IsAutoReplace);
}


BEGIN_MESSAGE_MAP(CReplaceSetDlg, CDialog)
END_MESSAGE_MAP()


// CReplaceSetDlg ��Ϣ�������
