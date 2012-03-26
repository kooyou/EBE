// NoteModelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EBE.h"
#include "NoteModelDlg.h"


// CNoteModelDlg 对话框

IMPLEMENT_DYNAMIC(CNoteModelDlg, CDialog)

CNoteModelDlg::CNoteModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNoteModelDlg::IDD, pParent)
	, m_noteModelSelect(2)
{

}

CNoteModelDlg::~CNoteModelDlg()
{
}

void CNoteModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX,IDC_NOTE_STYLE1,m_noteModelSelect);
}


BEGIN_MESSAGE_MAP(CNoteModelDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CNoteModelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNoteModelDlg 消息处理程序

CString CNoteModelDlg::GetNoteFirstLineModel(int noteModelType)
{
	UpdateData();
	CString noteFirstLine;
	if(noteModelType==-1||noteModelType>2)
		noteModelType=this->m_noteModelSelect;

	switch(noteModelType){
		case 0:
			noteFirstLine=GetFirstModel(1);
			break;
		case 1:
			noteFirstLine=GetSecondModel(1);
			break;
		case 2:
			noteFirstLine=GetThirdModel(1);
			break;
		default:
			break;
	}
	return noteFirstLine;
}

CString CNoteModelDlg::GetNoteSecondLineModel(int noteModelType)
{
	UpdateData();
	CString noteSecondLine;
	if(noteModelType==-1||noteModelType>2)
		noteModelType=this->m_noteModelSelect;
	switch(noteModelType){
		case 0:
			noteSecondLine=GetFirstModel(2);
			break;
		case 1:
			noteSecondLine=GetSecondModel(2);
			break;
		case 2:
			noteSecondLine=GetThirdModel(2);
			break;
		default:
			break;
	}
	return noteSecondLine;
}

CString CNoteModelDlg::GetNoteThirdLineModel(int noteModelType)
{
	UpdateData();
	CString noteThirdLine;
	if(noteModelType==-1||noteModelType>2)
		noteModelType=this->m_noteModelSelect;
	switch(noteModelType){
		case 0:
			noteThirdLine=GetFirstModel(3);
			break;
		case 1:
			noteThirdLine=GetSecondModel(3);
			break;
		case 2:
			noteThirdLine=GetThirdModel(3);
			break;
		default:
			break;
	}
	return noteThirdLine;
}

CString CNoteModelDlg::GetFirstModel(int nLine)
{
	CString lineStr;
	CString getStr;

	switch(nLine){
		case 1:
			this->GetDlgItemTextW(IDC_NOTE1_LINE1_1,getStr);
			lineStr=lineStr+getStr;
			lineStr=lineStr+_T("#number#");
			this->GetDlgItemTextW(IDC_NOTE1_LINE1_2,getStr);
			lineStr=lineStr+getStr;
			lineStr=lineStr+_T("#noteText#");
			this->GetDlgItemTextW(IDC_NOTE1_LINE1_3,getStr);
			lineStr=lineStr+getStr;
			break;
		case 2:
			this->GetDlgItemTextW(IDC_NOTE1_LINE2_1,getStr);
			lineStr=lineStr+getStr;
			this->GetDlgItemTextW(IDC_NOTE1_LINE2_2,getStr);
			lineStr=lineStr+getStr;
			lineStr=lineStr+_T("#noteText#");
			this->GetDlgItemTextW(IDC_NOTE1_LINE2_3,getStr);
			lineStr=lineStr+getStr;
			break;
		case 3:
			this->GetDlgItemTextW(IDC_NOTE1_LINE3_1,getStr);
			lineStr=lineStr+getStr;
			this->GetDlgItemTextW(IDC_NOTE1_LINE3_2,getStr);
			lineStr=lineStr+getStr;
			lineStr=lineStr+_T("#noteText#");
			this->GetDlgItemTextW(IDC_NOTE1_LINE3_3,getStr);
			lineStr=lineStr+getStr;
			this->GetDlgItemTextW(IDC_NOTE1_LINE3_4,getStr);
			lineStr=lineStr+getStr;
			break;
		default:
			break;
	}
	lineStr.Replace(_T("&&"),_T("&"));//控件显示的原因，需要替换为一个转义字符
	return lineStr;
}

CString CNoteModelDlg::GetSecondModel(int nLine)
{
	CString lineStr;
	CString getStr;

	switch(nLine){
		case 1:
			this->GetDlgItemTextW(IDC_NOTE2_LINE1_1,getStr);
			lineStr=lineStr+getStr;
			lineStr=lineStr+_T("#number#");
			this->GetDlgItemTextW(IDC_NOTE2_LINE1_2,getStr);
			lineStr=lineStr+getStr;
			lineStr=lineStr+_T("#noteText#");
			this->GetDlgItemTextW(IDC_NOTE2_LINE1_3,getStr);
			lineStr=lineStr+getStr;
			break;
		case 2:
			this->GetDlgItemTextW(IDC_NOTE2_LINE2_1,getStr);
			lineStr=lineStr+getStr;
			this->GetDlgItemTextW(IDC_NOTE2_LINE2_2,getStr);
			lineStr=lineStr+getStr;
			lineStr=lineStr+_T("#noteText#");
			this->GetDlgItemTextW(IDC_NOTE2_LINE2_3,getStr);
			lineStr=lineStr+getStr;
			break;
		case 3:
			this->GetDlgItemTextW(IDC_NOTE2_LINE3_1,getStr);
			lineStr=lineStr+getStr;
			this->GetDlgItemTextW(IDC_NOTE2_LINE3_2,getStr);
			lineStr=lineStr+getStr;
			lineStr=lineStr+_T("#noteText#");
			this->GetDlgItemTextW(IDC_NOTE2_LINE3_3,getStr);
			lineStr=lineStr+getStr;
			this->GetDlgItemTextW(IDC_NOTE2_LINE3_4,getStr);
			lineStr=lineStr+getStr;
			break;
		default:
			break;
	}
	lineStr.Replace(_T("&&"),_T("&"));//控件显示的原因，需要替换为一个转义字符
	return lineStr;
}

CString CNoteModelDlg::GetThirdModel(int nLine)
{
	CString lineStr;
	CString getStr;

	switch(nLine){
		case 1:
			this->GetDlgItemTextW(IDC_NOTEMINE_LINE1_1,getStr);
			lineStr=lineStr+getStr;
			lineStr=lineStr+_T("#number#");
			this->GetDlgItemTextW(IDC_NOTEMINE_LINE1_2,getStr);
			lineStr=lineStr+getStr;
			lineStr=lineStr+_T("#noteText#");
			this->GetDlgItemTextW(IDC_NOTEMINE_LINE1_3,getStr);
			lineStr=lineStr+getStr;
			this->GetDlgItemTextW(IDC_NOTEMINE_LINE1_4,getStr);
			lineStr=lineStr+getStr;
			break;
		case 2:
			this->GetDlgItemTextW(IDC_NOTEMINE_LINE2_1,getStr);
			lineStr=lineStr+getStr;
			this->GetDlgItemTextW(IDC_NOTEMINE_LINE2_2,getStr);
			lineStr=lineStr+getStr;
			lineStr=lineStr+_T("#noteText#");
			this->GetDlgItemTextW(IDC_NOTEMINE_LINE2_3,getStr);
			lineStr=lineStr+getStr;
			this->GetDlgItemTextW(IDC_NOTEMINE_LINE2_4,getStr);
			lineStr=lineStr+getStr;
			break;
		case 3:
			this->GetDlgItemTextW(IDC_NOTEMINE_LINE3_1,getStr);
			lineStr=lineStr+getStr;
			this->GetDlgItemTextW(IDC_NOTEMINE_LINE3_2,getStr);
			lineStr=lineStr+getStr;
			lineStr=lineStr+_T("#noteText#");
			this->GetDlgItemTextW(IDC_NOTEMINE_LINE3_3,getStr);
			lineStr=lineStr+getStr;
			this->GetDlgItemTextW(IDC_NOTEMINE_LINE3_4,getStr);
			lineStr=lineStr+getStr;
			break;
		default:
			break;
	}
	lineStr.Replace(_T("&&"),_T("&"));//控件显示的原因，需要替换为一个转义字符
	return lineStr;
}

void CNoteModelDlg::InitMineModelFromFile()
{
	CString sIniFilePath;
	CString sModFileName; 
	GetModuleFileName(NULL,sModFileName.GetBuffer(MAX_PATH),MAX_PATH);
	sModFileName.ReleaseBuffer(); 
	sModFileName.MakeReverse(); 
	sIniFilePath=sModFileName.Right(sModFileName.GetLength()-sModFileName.Find( '\\')); 
	sIniFilePath.MakeReverse();
	this->m_filePath=sIniFilePath+_T("noteModel.txt");

	CStdioFile file;
	if(!file.Open(m_filePath,CFile::modeRead)){
		AfxMessageBox(_T("打开注释模板文件失败"));
		return;
	}
	CString rString;
	file.ReadString(rString);
	this->SetDlgItemTextW(IDC_NOTEMINE_LINE1_1,rString);
	file.ReadString(rString);
	this->SetDlgItemTextW(IDC_NOTEMINE_LINE1_2,rString);
	file.ReadString(rString);
	this->SetDlgItemTextW(IDC_NOTEMINE_LINE1_3,rString);
	file.ReadString(rString);
	this->SetDlgItemTextW(IDC_NOTEMINE_LINE1_4,rString);
	file.ReadString(rString);
	this->SetDlgItemTextW(IDC_NOTEMINE_LINE2_1,rString);
	file.ReadString(rString);
	this->SetDlgItemTextW(IDC_NOTEMINE_LINE2_2,rString);
	file.ReadString(rString);
	this->SetDlgItemTextW(IDC_NOTEMINE_LINE2_3,rString);
	file.ReadString(rString);
	this->SetDlgItemTextW(IDC_NOTEMINE_LINE2_4,rString);
	file.ReadString(rString);
	this->SetDlgItemTextW(IDC_NOTEMINE_LINE3_1,rString);
	file.ReadString(rString);
	this->SetDlgItemTextW(IDC_NOTEMINE_LINE3_2,rString);
	file.ReadString(rString);
	this->SetDlgItemTextW(IDC_NOTEMINE_LINE3_3,rString);
	file.ReadString(rString);
	this->SetDlgItemTextW(IDC_NOTEMINE_LINE3_4,rString);

}

void CNoteModelDlg::StoreMineModelToFile()
{
	CStdioFile file;
	if(!file.Open(m_filePath,CFile::modeWrite)){
		AfxMessageBox(_T("打开注释模板文件失败"));
		return;
	}
	CString rString;
	this->GetDlgItemTextW(IDC_NOTEMINE_LINE1_1,rString);
	rString=rString+_T("\n");
	file.WriteString(rString);
	this->GetDlgItemTextW(IDC_NOTEMINE_LINE1_2,rString);
	rString=rString+_T("\n");
	file.WriteString(rString);
	this->GetDlgItemTextW(IDC_NOTEMINE_LINE1_3,rString);
	rString=rString+_T("\n");
	file.WriteString(rString);
	this->GetDlgItemTextW(IDC_NOTEMINE_LINE1_4,rString);
	rString=rString+_T("\n");
	file.WriteString(rString);
	this->GetDlgItemTextW(IDC_NOTEMINE_LINE2_1,rString);
	rString=rString+_T("\n");
	file.WriteString(rString);
	this->GetDlgItemTextW(IDC_NOTEMINE_LINE2_2,rString);
	rString=rString+_T("\n");
	file.WriteString(rString);
	this->GetDlgItemTextW(IDC_NOTEMINE_LINE2_3,rString);
	rString=rString+_T("\n");
	file.WriteString(rString);
	this->GetDlgItemTextW(IDC_NOTEMINE_LINE2_4,rString);
	rString=rString+_T("\n");
	file.WriteString(rString);
	this->GetDlgItemTextW(IDC_NOTEMINE_LINE3_1,rString);
	rString=rString+_T("\n");
	file.WriteString(rString);
	this->GetDlgItemTextW(IDC_NOTEMINE_LINE3_2,rString);
	rString=rString+_T("\n");
	file.WriteString(rString);
	this->GetDlgItemTextW(IDC_NOTEMINE_LINE3_3,rString);
	rString=rString+_T("\n");
	file.WriteString(rString);
	this->GetDlgItemTextW(IDC_NOTEMINE_LINE3_4,rString);
	rString=rString+_T("\n");
	file.WriteString(rString);
}
BOOL CNoteModelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitMineModelFromFile();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CNoteModelDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	StoreMineModelToFile();
	OnOK();
}
