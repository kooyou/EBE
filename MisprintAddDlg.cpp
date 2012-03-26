// MisprintAddDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EBE.h"
#include "MisprintAddDlg.h"
#include "EBEView.h"
#include "MainFrm.h"

// CMisprintAddDlg 对话框

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


// CMisprintAddDlg 消息处理程序

void CMisprintAddDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	CMainRichEditView* pview;
	pview=(CMainRichEditView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveFrame()->GetActiveView();
	this->UpdateData(TRUE);
	pview->m_misprintManageDlg.OnMisprintAddmisprint(this->m_misprintString);

	CDialog::OnOK();
}
