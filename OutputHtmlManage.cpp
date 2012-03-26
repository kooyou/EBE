#include "StdAfx.h"
#include "OutputHtmlManage.h"
#include "MainFrm.h"
#include "EBEView.h"
#include "SymbolReplaceSetDlg.h"

OutputHtmlManage::OutputHtmlManage(void)
{
}

OutputHtmlManage::~OutputHtmlManage(void)
{
}

void OutputHtmlManage::OutputHtml(CRichEditCtrl *pRichEditCtrl)
{
	this->m_pPropertyManage=((CMainRichEditView*)((CMainFrame*)(AfxGetApp()->GetMainWnd()))->GetActiveFrame()->GetActiveView())->m_pPropertyManage;
	CSymbolReplaceSetDlg* pSymbolReplaceSetDlg=((CMainFrame*)(AfxGetApp()->GetMainWnd()))->m_pSymbolReplaceSetDlg;
	m_winTxtTranslation.StartTranslate(pRichEditCtrl,m_pPropertyManage,pSymbolReplaceSetDlg);
	m_htmlFileGeneration.StartGenerate(m_pPropertyManage,m_winTxtTranslation.m_vecEachLine,m_winTxtTranslation.m_vecSectionStyle);
}
