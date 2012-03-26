// HtmlViewCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "EBE.h"
#include "HtmlViewCtrl.h"


// CHtmlViewCtrl

IMPLEMENT_DYNCREATE(CHtmlViewCtrl, CHtmlView)

CHtmlViewCtrl::CHtmlViewCtrl()
{
}

CHtmlViewCtrl::~CHtmlViewCtrl()
{
}

void CHtmlViewCtrl::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHtmlViewCtrl, CHtmlView)
END_MESSAGE_MAP()


// CHtmlViewCtrl 诊断

#ifdef _DEBUG
void CHtmlViewCtrl::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CHtmlViewCtrl::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG


// CHtmlViewCtrl 消息处理程序
