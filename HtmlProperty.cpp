#include "StdAfx.h"
#include "HtmlProperty.h"

CHtmlProperty::CHtmlProperty():CMFCPropertyGridProperty(strGroupName)
{
}

CHtmlProperty::~CHtmlProperty()
{
}

CString CHtmlProperty::GetBookName()
{
	CString bookName;
	//CMFCPropertyGridProperty* this=this->GetProperty(0);
	CMFCPropertyGridProperty* this1=this->GetSubItem(0);
	COleVariant oleVar=this1->GetValue();
	bookName=oleVar.bstrVal;
	return bookName;
}

void CHtmlProperty::SetBookName(CString bookName)
{
	CMFCPropertyGridProperty* this1=this->GetSubItem(0);
	COleVariant oleVar=this1->GetValue();
	oleVar.bstrVal=bookName.AllocSysString();
	this1->SetValue(oleVar);
}

CString CHtmlProperty::GetCurPage()
{
	CString curPage;
	//CMFCPropertyGridProperty* this=this->GetProperty(0);
	CMFCPropertyGridProperty* this1=this->GetSubItem(1);
	COleVariant oleVar=this1->GetValue();
	curPage=oleVar.bstrVal;
	return curPage;
}

CString CHtmlProperty::SetPage(CString pageNum)
{
	CString lastPage;
	//CMFCPropertyGridProperty* this=this->GetProperty(0);
	CMFCPropertyGridProperty* this1=this->GetSubItem(1);
	COleVariant oleVar=this1->GetValue();
	lastPage=oleVar.bstrVal;
	oleVar.bstrVal=pageNum.AllocSysString();
	this1->SetValue(oleVar);
	return lastPage;
}

int CHtmlProperty::GetPageLeftRight()
{
	//this->GetFocus();
	CString PageLeftRight;
	//CMFCPropertyGridProperty* this=this->GetProperty(0);
	CMFCPropertyGridProperty* this1=this->GetSubItem(2);
	this1->Redraw();
	COleVariant oleVar=this1->GetValue();
	PageLeftRight=oleVar.bstrVal;
	if(!PageLeftRight.Compare(_T("��"))){
		return 1;
	}
	else
		return 2;
}

int CHtmlProperty::SetPageLeftRight(int pageLeftRight)
{
	int LeftRight;
	CString PageLR;
	CMFCPropertyGridProperty* this1=this->GetSubItem(2);
	this1->Redraw();
	COleVariant oleVar=this1->GetValue();
	PageLR=oleVar.bstrVal;
	if(!PageLR.Compare(_T("��"))){
		LeftRight= 1;
	}
	else
		LeftRight= 2;

	if(pageLeftRight==1)
		oleVar.bstrVal=SysAllocString(_T("��"));
	else
		oleVar.bstrVal=SysAllocString(_T("��"));
	this1->SetValue(oleVar);
	return LeftRight;
}

int CHtmlProperty::GetExpStyle()
{
	CString ExpStyle;
	//CMFCPropertyGridProperty* this=this->GetProperty(0);
	CMFCPropertyGridProperty* this1=this->GetSubItem(3);
	COleVariant oleVar=this1->GetValue();
	ExpStyle=oleVar.bstrVal;
	if(ExpStyle.Compare(_T("����������"))==0){
		return 1;
	}
	else if(ExpStyle.Compare(_T("ԲȦ"))==0)
		return 2;
	else return 0;
}

void CHtmlProperty::SetExpStyle(int expStyle)
{//��ȡ��������ϵ�������ʽ
	CMFCPropertyGridProperty* this1=this->GetSubItem(3);
	CString style=_T("");
	switch(expStyle){
		case 1:
			style=_T("����������");
			break;
		case 2:
			style=_T("ԲȦ");
			break;
		default:
			break;
	}
	COleVariant oleVar=this1->GetValue();
	oleVar.bstrVal=style.AllocSysString();
	this1->SetValue(oleVar);
}

CString CHtmlProperty::GetExpModel()
{//��ȡע��ģ��
	CString ExpModel;
	//CMFCPropertyGridProperty* this=this->GetProperty(0);
	CMFCPropertyGridProperty* this1=this->GetSubItem(4);
	COleVariant oleVar=this1->GetValue();
	ExpModel=oleVar.bstrVal;
	return ExpModel;
}

void CHtmlProperty::SetExpModel(CString expModel)
{//��ȡ��������ϵ�������ʽ
	CMFCPropertyGridProperty* this1=this->GetSubItem(4);
	COleVariant oleVar=this1->GetValue();
	oleVar.bstrVal=expModel.AllocSysString();
	this1->SetValue(oleVar);
}

CString CHtmlProperty::GetModel()
{//��ȡ���������ѡ����ģ��
	CString model;
	//CMFCPropertyGridProperty* this=this->GetProperty(0);
	CMFCPropertyGridProperty* this1=this->GetSubItem(5);
	COleVariant oleVar=this1->GetValue();
	model=oleVar.bstrVal;
	return model;
}

void CHtmlProperty::RemoveModelAllOpation()
{
	CMFCPropertyGridProperty* this1=this->GetSubItem(5);
	this1->RemoveAllOptions();
}
void CHtmlProperty::SetModel(CString model)
{//��ȡ��������ϵ�������ʽ
	CMFCPropertyGridProperty* this1=this->GetSubItem(5);
	COleVariant oleVar=this1->GetValue();
	oleVar.bstrVal=model.AllocSysString();
	this1->SetValue(oleVar);
}

CString CHtmlProperty::GetTextCss()
{//��ȡ��������ϵ�������ʽ
	CString textCss;
	//CMFCPropertyGridProperty* this=this->GetProperty(0);
	CMFCPropertyGridProperty* this1=this->GetSubItem(6);
	COleVariant oleVar=this1->GetValue();
	textCss=oleVar.bstrVal;
	return textCss;
}

void CHtmlProperty::SetTextCss(CString textCss)
{//��ȡ��������ϵ�������ʽ
	CMFCPropertyGridProperty* this1=this->GetSubItem(6);
	COleVariant oleVar=this1->GetValue();
	oleVar.bstrVal=textCss.AllocSysString();
	this1->SetValue(oleVar);
}

void CHtmlProperty::AddModelOpatoin(CString modelName)
{
	CMFCPropertyGridProperty* pModelPropertyGrid=
		this->GetSubItem(5);
	pModelPropertyGrid->AddOption(modelName);
}