#pragma once

#include <vector>

class TableManage
{
public:
	TableManage(void);
	~TableManage(void);

public:
	// Ù–‘
	std::vector<std::vector<CString>> m_vecTableStr;
	int m_rowNum;
	int m_colNum;

public:
	//∑Ω∑®
	void SplitTableText(CString& lineText);
};
