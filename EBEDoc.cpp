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

// EBEDoc.cpp : CEBEDoc 类的实现
//

#include "stdafx.h"
#include "EBE.h"

#include "EBEDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEBEDoc

IMPLEMENT_DYNCREATE(CEBEDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CEBEDoc, CRichEditDoc)
	// 启用默认的 OLE 容器实现
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()


// CEBEDoc 构造/析构

CEBEDoc::CEBEDoc()
{
	// TODO: 在此添加一次性构造代码

}

CEBEDoc::~CEBEDoc()
{
}

BOOL CEBEDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}

CRichEditCntrItem* CEBEDoc::CreateClientItem(REOBJECT* preo) const
{
	return new CEBECntrItem(preo, const_cast<CEBEDoc*>(this));
}




// CEBEDoc 序列化

void CEBEDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}

	// 调用基类 CRichEditDoc 将启用
	//  容器文档的 COleClientItem 对象的序列化。
	// TODO: 如果作为文本进行序列化，则设置 CRichEditDoc::m_bRTF = FALSE
	CString fileStyle=ar.GetFile()->GetFileName().Right(3);
	if(fileStyle.Compare(_T("txt"))==0){
		this->m_bRTF=FALSE;//打开TXT
	}
	else{
		this->m_bRTF=TRUE;//打开RTF
	}

	CRichEditDoc::Serialize(ar);
}


// CEBEDoc 诊断

#ifdef _DEBUG
void CEBEDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CEBEDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG


// CEBEDoc 命令
