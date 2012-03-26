#pragma once

enum{OUTPUT_HTML=1,OUTPUT_XML};

class OutputManage
{
public:
	OutputManage(void);
	virtual ~OutputManage(void);
public:
	void StartOutput(CRichEditCtrl* pRichEditCtrl,int OUTPUT_STYLE);
};
