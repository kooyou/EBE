#pragma once

#include <map>
#include <vector>

class ModelManage
{
public:
	ModelManage(void);
	~ModelManage(void);

	CString getModelFilePath(CString modelFile);
	void InitModelMapFromTxt();
	void AddModel(CString modelFile,CString modelFilePath);
	void DelModel(CString modelFile);
	void OpenModelFile(CString modelFile);
private:
	void WriteModelMapToTxt();

	CString m_fPath;

public:
	std::map<CString,CString> m_mapModel;
	std::vector<CString> m_vecModelOpation;
	std::vector<CString> m_vecAutoModelOpation;
};
