#include "StdAfx.h"
#include "FileManage.h"

CFileManage::CFileManage(void)
{
}

CFileManage::~CFileManage(void)
{
}

CString CFileManage::GetNextRTFFile(CString curFile)
{
	if(m_vecFileName.empty()){
		AfxMessageBox(_T("当前没有文件，请先打开文件！"));
		return _T("");
	}
	curFile=m_vecFileName[m_vecFileName.size()-1];
	CString fileParentPath=curFile;
	int removePos=fileParentPath.ReverseFind('\\');
	fileParentPath.Delete(removePos+1,curFile.GetLength()-removePos);
	CFileFind findFile;
	BOOL bFind=findFile.FindFile(fileParentPath+"*.rtf"); 
	bool isCur=false;
	CString nextFile;
	while(bFind)  
	{  
		bFind=findFile.FindNextFile();
		if(findFile.IsDots()){
			continue;  
		}
		if(isCur){
			nextFile=fileParentPath+findFile.GetFileName();
			break;
		}
		if(findFile.GetFilePath()==curFile)
			isCur=true;
	}
	return nextFile;
}

void CFileManage::AddFile(CString openFile)
{
	m_vecFileName.push_back(openFile);
}