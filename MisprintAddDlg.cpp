// MisprintAddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EBE.h"
#include "MisprintAddDlg.h"
#include "EBEView.h"
#include "MainFrm.h"

// CMisprintAddDlg �Ի���

IMPLEMENT_DYNAMIC(CMisprintAddDlg, CDialog)

CMisprintAddDlg::CMisprintAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMisprintAddDlg::IDD, pParent)
	, m_misprintString(_T(""))
	, m_replaceString(_T(""))
{

}

CMisprintAddDlg::~CMisprintAddDlg()
{
}

void CMisprintAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MISPRINT_EDIT, m_misprintString);
	DDX_Text(pDX, IDC_REPLACE_EDIT, m_replaceString);
}


BEGIN_MESSAGE_MAP(CMisprintAddDlg, CDialog)
END_MESSAGE_MAP()


// CMisprintAddDlg ��Ϣ�������

void CMisprintAddDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CMainRichEditView* pview;
	pview=(CMainRichEditView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveFrame()->GetActiveView();
	this->UpdateData(TRUE);
	pview->m_misprintManageDlg.OnMisprintAddmisprint(this->m_misprintString);

	CDialog::OnOK();
}
