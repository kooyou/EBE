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
	if(!PageLeftRight.Compare(_T("左"))){
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
	if(!PageLR.Compare(_T("左"))){
		LeftRight= 1;
	}
	else
		LeftRight= 2;

	if(pageLeftRight==1)
		oleVar.bstrVal=SysAllocString(_T("左"));
	else
		oleVar.bstrVal=SysAllocString(_T("右"));
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
	if(ExpStyle.Compare(_T("阿拉伯数字"))==0){
		return 1;
	}
	else if(ExpStyle.Compare(_T("圆圈"))==0)
		return 2;
	else return 0;
}

void CHtmlProperty::SetExpStyle(int expStyle)
{//获取属性面板上的正文样式
	CMFCPropertyGridProperty* this1=this->GetSubItem(3);
	CString style=_T("");
	switch(expStyle){
		case 1:
			style=_T("阿拉伯数字");
			break;
		case 2:
			style=_T("圆圈");
			break;
		default:
			break;
	}
	COleVariant oleVar=this1->GetValue();
	oleVar.bstrVal=style.AllocSysString();
	this1->SetValue(oleVar);
}

CString CHtmlProperty::GetExpModel()
{//获取注释模板
	CString ExpModel;
	//CMFCPropertyGridProperty* this=this->GetProperty(0);
	CMFCPropertyGridProperty* this1=this->GetSubItem(4);
	COleVariant oleVar=this1->GetValue();
	ExpModel=oleVar.bstrVal;
	return ExpModel;
}

void CHtmlProperty::SetExpModel(CString expModel)
{//获取属性面板上的正文样式
	CMFCPropertyGridProperty* this1=this->GetSubItem(4);
	COleVariant oleVar=this1->GetValue();
	oleVar.bstrVal=expModel.AllocSysString();
	this1->SetValue(oleVar);
}

CString CHtmlProperty::GetModel()
{//获取属性面板上选定的模板
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
{//获取属性面板上的正文样式
	CMFCPropertyGridProperty* this1=this->GetSubItem(5);
	COleVariant oleVar=this1->GetValue();
	oleVar.bstrVal=model.AllocSysString();
	this1->SetValue(oleVar);
}

CString CHtmlProperty::GetTextCss()
{//获取属性面板上的正文样式
	CString textCss;
	//CMFCPropertyGridProperty* this=this->GetProperty(0);
	CMFCPropertyGridProperty* this1=this->GetSubItem(6);
	COleVariant oleVar=this1->GetValue();
	textCss=oleVar.bstrVal;
	return textCss;
}

void CHtmlProperty::SetTextCss(CString textCss)
{//获取属性面板上的正文样式
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