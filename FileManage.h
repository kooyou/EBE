#pragma once
#include <vector>

class CFileManage
{
public:
	CFileManage(void);
	~CFileManage(void);

	void AddFile(CString openFile);
	CString GetNextRTFFile(CString curFile);

	std::vector<CString> m_vecFileName;
};
