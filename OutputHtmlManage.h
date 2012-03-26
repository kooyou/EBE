#pragma once

#include "WinTxtTranslation.h"
#include "HtmlFileGeneration.h"
#include "PropertyManage.h"

class OutputHtmlManage
{
public:
	OutputHtmlManage(void);
	~OutputHtmlManage(void);

public:
	void OutputHtml(CRichEditCtrl* pRichEditCtrl);

public:
	WinTxtTranslation m_winTxtTranslation;
	HtmlFileGeneration m_htmlFileGeneration;
	CPropertyManage* m_pPropertyManage;
};
