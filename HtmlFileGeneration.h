#pragma once
#include "PropertyManage.h"
#include <vector>
#include "TableManage.h"


class HtmlFileGeneration
{
public:
	HtmlFileGeneration(void);
	~HtmlFileGeneration(void);

public:
	void StartGenerate(CPropertyManage* pPropertyManage,std::vector<CString>& vecEachLine,std::vector<std::vector<CString>>& vecSectionStyle);

private:
	bool InitFiles();
	void CloseFiles();
	void AddHtmlVector(CString lineText);
	void TraverseVector(std::vector<CString>& vecEachLine,std::vector<std::vector<CString>>& vecSectionStyle);
	void OutputHtmlFile();
	std::vector<CString>::iterator HandleTableMark(std::vector<CString>::iterator iter);
	BOOL HandlePictureMark(std::vector<CString>::iterator iter);
	void WritePicEnd();
	void WritePicStart();
	void WriteTableText();
	void WriteTableStart();
	void WriteTableEnd();
	void WriteEachLine(CString& lineText);
	void WriteNote(CString& noteText);
	void WriteSectionStyle(CString& lineText,int lineIndex,std::vector<std::vector<CString>>& vecSectionStyle);
	void HandleNoteNum(CString& lineText);
	CString HandleLineStyleMark(CString& lineText);
	void WriteDiv();

private:
	CPropertyManage* m_pPropertyManage;
	std::vector<CString>::iterator m_iterVecEachLine;
	std::vector<CString>::iterator m_iterVecEachLineEnd;
	std::vector<std::vector<CString>>::iterator m_iterVecSectionStyle;

	//文件
	CStdioFile m_fPicLeftStr;
	CStdioFile m_fPicRightStr;
	CStdioFile m_fPicLeftEnd;
	CStdioFile m_fPicRightEnd;
	CStdioFile m_fPicCenter;
	CStdioFile m_fHtmlWithModel;

	CString m_htmlFileName;//记录当前写入的html文件的名字
	CString m_sIniFilePath;//当前执行文件路径

	std::vector<CString> m_vecHtml;//生成的html文本

	TableManage m_tableManage;

	int m_lineNum;
	CString m_pageNum;
	bool m_IsNote;
	bool m_IsDiv;
	bool m_IsFirstWriteExp;
	bool m_IsBr;
};
