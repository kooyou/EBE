#include "StdAfx.h"
#include "TableManage.h"

TableManage::TableManage(void)
{
}

TableManage::~TableManage(void)
{
}

void TableManage::SplitTableText(CString& lineText)
{
	std::vector<CString> vecStr;
	lineText.Replace(_T("	"),_T(" "));
	CString str;
	lineText.TrimLeft(_T(" "));
	lineText.TrimRight(_T(" "));
	int pos=0;
	while (true)    
	{        
		CString subStr = lineText.SpanExcluding(_T(" ")); 
		if(!subStr.IsEmpty())
			vecStr.push_back(subStr); 
		lineText.TrimLeft(_T(" "));
		lineText = lineText.Right(lineText.GetLength()-subStr.GetLength());
		if (lineText.IsEmpty())   
		{            
			break;        
		}    
	}
	m_vecTableStr.push_back(vecStr);
}

