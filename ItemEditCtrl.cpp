// ItemEditCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "EBE.h"
#include "ItemEditCtrl.h"
#include "UsefulStringList.h"


// CItemEditCtrl

IMPLEMENT_DYNAMIC(CItemEditCtrl, CEdit)

CItemEditCtrl::CItemEditCtrl()
{

}

CItemEditCtrl::~CItemEditCtrl()
{
}


BEGIN_MESSAGE_MAP(CItemEditCtrl, CEdit)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CItemEditCtrl 消息处理程序



void CItemEditCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	// TODO: 在此处添加消息处理程序代码
	// 得到父窗口，并通知父窗口结束编辑过程
	((CUsefulStringList*)this->GetParent())->ItemEditEnd();
	this->ShowWindow(SW_HIDE);
}
