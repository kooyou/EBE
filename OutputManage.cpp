#include "StdAfx.h"
#include "OutputManage.h"
#include "OutputHtmlManage.h"

OutputManage::OutputManage(void)
{
}

OutputManage::~OutputManage(void)
{
}

void OutputManage::StartOutput(CRichEditCtrl *pRichEditCtrl,int OUTPUT_STYLE)
{
	OutputHtmlManage outputHtmlManage;
	switch(OUTPUT_STYLE){
		case OUTPUT_HTML:
			outputHtmlManage.OutputHtml(pRichEditCtrl);
			break;
		default:
			break;
	}
}
