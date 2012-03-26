// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// CntrItem.cpp : CEBECntrItem 类的实现
//

#include "stdafx.h"
#include "EBE.h"

#include "EBEDoc.h"
#include "EBEView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEBECntrItem 的实现

IMPLEMENT_SERIAL(CEBECntrItem, CRichEditCntrItem, 0)

CEBECntrItem::CEBECntrItem(REOBJECT* preo, CEBEDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: 在此添加一次性构造代码
}

CEBECntrItem::~CEBECntrItem()
{
	// TODO: 在此处添加清理代码
}


// CEBECntrItem 诊断

#ifdef _DEBUG
void CEBECntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CEBECntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

