#pragma once

#include <vector>

class MisprintManage
{
public:
	MisprintManage(void);
	virtual ~MisprintManage(void);

public:
	void replaceListAll(CRichEditView* pRichEditView);
	void MisprintTip(CRichEditView* pRichEditView);

	void AddMisprint(CString addString);

//	void SetMisprintLib();
private:
	bool CreateMisprintTipLib();
	void GetMisprintLibFromFile();

public:
	CString m_libFileName;
	
private:
	CStdioFile m_misprintLibFile;
	std::vector<CString> m_vecMisprintLib;
};
