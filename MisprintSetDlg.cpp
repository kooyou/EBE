// MisprintSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EBE.h"
#include "MisprintSetDlg.h"


// CMisprintSetDlg 对话框

IMPLEMENT_DYNAMIC(CMisprintSetDlg, CDialog)

CMisprintSetDlg::CMisprintSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMisprintSetDlg::IDD, pParent)
{

}

CMisprintSetDlg::~CMisprintSetDlg()
{
}

void CMisprintSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMisprintSetDlg, CDialog)
END_MESSAGE_MAP()


// CMisprintSetDlg 消息处理程序
