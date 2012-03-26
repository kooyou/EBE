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

	//�ļ�
	CStdioFile m_fPicLeftStr;
	CStdioFile m_fPicRightStr;
	CStdioFile m_fPicLeftEnd;
	CStdioFile m_fPicRightEnd;
	CStdioFile m_fPicCenter;
	CStdioFile m_fHtmlWithModel;

	CString m_htmlFileName;//��¼��ǰд���html�ļ�������
	CString m_sIniFilePath;//��ǰִ���ļ�·��

	std::vector<CString> m_vecHtml;//���ɵ�html�ı�

	TableManage m_tableManage;

	int m_lineNum;
	CString m_pageNum;
	bool m_IsNote;
	bool m_IsDiv;
	bool m_IsFirstWriteExp;
	bool m_IsBr;
};
