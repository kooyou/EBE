#include "StdAfx.h"
#include "ModelManage.h"
#include <locale>

ModelManage::ModelManage(void)
{
	InitModelMapFromTxt();//初始化map容器内容
}

ModelManage::~ModelManage(void)
{
	WriteModelMapToTxt();//将数据写到文件
}

CString ModelManage::getModelFilePath(CString modelFile)
{
	CString modelFilePath;
	modelFilePath=this->m_mapModel[modelFile];
	return modelFilePath;
}

void ModelManage::InitModelMapFromTxt()
{
	//区域设定
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定

	//获得当前可执行文件的路径  
	CString sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	CString sIniFilePath;
	sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	sIniFilePath.MakeReverse();

	//从文件读取信息
	CStdioFile modelFile;
	m_fPath.Format(_T("%s//modelList.txt"),sIniFilePath);
	if(!modelFile.Open(m_fPath,CFile::modeRead))
		return;
	CString optionStr;//模板名称
	CString filename;//模板对应的文件地址
	while(modelFile.ReadString(optionStr)){
		if(modelFile.ReadString(filename)){
			m_mapModel[optionStr]=filename;//将模板对应的文件地址写入map
		}
	}
	modelFile.Close();
	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定
}

void ModelManage::AddModel(CString modelFile, CString modelFilePath)
{
	m_mapModel[modelFile]=modelFilePath;//将模板对应的文件地址写入map
}

void ModelManage::DelModel(CString modelFile)
{
	m_mapModel.erase(m_mapModel.find(modelFile));//删除模板
}

void ModelManage::WriteModelMapToTxt()
{
	//区域设定
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//设定

	//保存模板信息
	CStdioFile modelFile;
	if(!modelFile.Open(m_fPath,CFile::modeCreate|CFile::modeWrite))
		return;
	for(std::map<CString,CString>::iterator i=m_mapModel.begin();i!=m_mapModel.end();i++){
		modelFile.WriteString(i->first);
		modelFile.WriteString(_T("\n"));
		modelFile.WriteString(i->second);
		modelFile.WriteString(_T("\n"));
	}
	modelFile.Close();

	//恢复区域设定
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//还原区域设定
}

void ModelManage::OpenModelFile(CString modelFile)
{
	CString modelFilePath=this->m_mapModel[modelFile];
	if(!PathFileExists(modelFilePath)){
		CString errMess;
		errMess.Format(_T("没有找到文件：%s"),modelFilePath);
		AfxMessageBox(errMess);
		return;
	}

	//用记事本打开模板文件
	::ShellExecute(NULL,_T("open"),modelFilePath,NULL,NULL,SW_SHOW);
}