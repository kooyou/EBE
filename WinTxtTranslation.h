#pragma once
#include <vector>
#include "PropertyManage.h"
#include "SymbolReplaceSetDlg.h"

class WinTxtTranslation
{
public:
	WinTxtTranslation(void);
	~WinTxtTranslation(void);

public:
	//方法
	void StartTranslate(CRichEditCtrl* pRichEditCtrl,CPropertyManage* propertyManage,CSymbolReplaceSetDlg* pSymbolReplaceSetDlg);

public:
	//属性
	std::vector<CString> m_vecEachLine;
	std::vector<std::vector<CString>> m_vecSectionStyle;

private:
	void ReadWinTxt();
	int DelExcessSpace(CString& lineText);
	void EngChnRep(CString& lineText);
	void MarkLineStyle(CString& lineText);
	void MarkNoteNum();
	void HandleSectionStyle();
	void MarkHandle();
	void RecordSectionStyle(CString lineText,int lineIndex);
	void KeyWordReplace();
	void ReplaceFromReplaceSetDlg(CString& lineTextToReplace);

	void findIsESC(CString& lineText);
	

private:
	//属性
	CRichEditCtrl* m_pRichEditCtrl;
	CPropertyManage* m_pPropertyManage;
	CSymbolReplaceSetDlg* m_pSymbolReplaceSetDlg;
};
