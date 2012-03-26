#pragma once
#include "SymbolReplaceSetDlg.h"

class CFormat
{
public:
	CFormat(void);
	virtual ~CFormat(void);
	void DelSpaceLines(CRichEditView* pRichEditView);//删除多余的行
	void UnionFontSize(CRichEditView* pRichEditView,CFont* pfont);//统一字体
	void DelUselessSpaces(CRichEditView* pRichEditView);//删除多余的空格
	void ChangeLineAuto(CRichEditView* pRichEditView);//自动换行
	void DelFrontSpaces(CRichEditView* pRichEditView);//删除选定内容的行前空格
	void ReplaceKeySymbol(CSymbolReplaceSetDlg* pSymbolReplaceSetDlg, CRichEditView* pRichEditView);//替换相应的标点符号

};
