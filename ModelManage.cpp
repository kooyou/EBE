#include "StdAfx.h"
#include "ModelManage.h"
#include <locale>

ModelManage::ModelManage(void)
{
	InitModelMapFromTxt();//��ʼ��map��������
}

ModelManage::~ModelManage(void)
{
	WriteModelMapToTxt();//������д���ļ�
}

CString ModelManage::getModelFilePath(CString modelFile)
{
	CString modelFilePath;
	modelFilePath=this->m_mapModel[modelFile];
	return modelFilePath;
}

void ModelManage::InitModelMapFromTxt()
{
	//�����趨
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨

	//��õ�ǰ��ִ���ļ���·��  
	CString sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	CString sIniFilePath;
	sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	sIniFilePath.MakeReverse();

	//���ļ���ȡ��Ϣ
	CStdioFile modelFile;
	m_fPath.Format(_T("%s//modelList.txt"),sIniFilePath);
	if(!modelFile.Open(m_fPath,CFile::modeRead))
		return;
	CString optionStr;//ģ������
	CString filename;//ģ���Ӧ���ļ���ַ
	while(modelFile.ReadString(optionStr)){
		if(modelFile.ReadString(filename)){
			m_mapModel[optionStr]=filename;//��ģ���Ӧ���ļ���ַд��map
		}
	}
	modelFile.Close();
	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨
}

void ModelManage::AddModel(CString modelFile, CString modelFilePath)
{
	m_mapModel[modelFile]=modelFilePath;//��ģ���Ӧ���ļ���ַд��map
}

void ModelManage::DelModel(CString modelFile)
{
	m_mapModel.erase(m_mapModel.find(modelFile));//ɾ��ģ��
}

void ModelManage::WriteModelMapToTxt()
{
	//�����趨
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );//�趨

	//����ģ����Ϣ
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

	//�ָ������趨
	setlocale( LC_CTYPE, old_locale );
	free( old_locale );//��ԭ�����趨
}

void ModelManage::OpenModelFile(CString modelFile)
{
	CString modelFilePath=this->m_mapModel[modelFile];
	if(!PathFileExists(modelFilePath)){
		CString errMess;
		errMess.Format(_T("û���ҵ��ļ���%s"),modelFilePath);
		AfxMessageBox(errMess);
		return;
	}

	//�ü��±���ģ���ļ�
	::ShellExecute(NULL,_T("open"),modelFilePath,NULL,NULL,SW_SHOW);
}