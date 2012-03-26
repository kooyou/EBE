// PictureProperty.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EBE.h"
#include "PictureProperty.h"


// CPictureProperty

CPictureProperty::CPictureProperty():CMFCPropertyGridProperty(strGroupName)
{
}

CPictureProperty::~CPictureProperty()
{
}


// CPictureProperty ��Ա����

int CPictureProperty::GetPictureAlign()
{
	CMFCPropertyGridProperty* this1;
	COleVariant oleVar;
	this1=this->GetSubItem(3);
	oleVar=this1->GetValue();
	CString picAlgin=oleVar.bstrVal;

	int align=-1;
	if(!picAlgin.Compare(_T("����")))
		align=PICTURE_ALIGN_CENTER;
	else if(!picAlgin.Compare(_T("��")))
		align=PICTURE_ALIGN_LEFT;
	else if(!picAlgin.Compare(_T("��")))
		align=PICTURE_ALIGN_RIGHT;
	else
		align=0;
	return align;
}

void CPictureProperty::SetPictureAlign(int align)
{
	CMFCPropertyGridProperty* this1=this->GetSubItem(3);
	COleVariant oleVar=this1->GetValue();
	CString alignStr=_T("");
	switch(align){
		case PICTURE_ALIGN_CENTER:
			alignStr=_T("����");
			break;
		case PICTURE_ALIGN_LEFT:
			alignStr=_T("��");
			break;
		case PICTURE_ALIGN_RIGHT:
			alignStr=_T("��");
			break;
		default:
			break;
	}
	oleVar.bstrVal=alignStr.AllocSysString();
	this1->SetValue(oleVar);
}

CString CPictureProperty::GetPictureName()
{
	CString picName;
	CMFCPropertyGridProperty* this1;
	COleVariant oleVar;
	this1=this->GetSubItem(0);
	oleVar=this1->GetValue();
	picName=oleVar.bstrVal;//����
	return picName;
}

void CPictureProperty::SetPictureName(CString pictureName)
{
	CMFCPropertyGridProperty* this1=this->GetSubItem(0);
	COleVariant oleVar=this1->GetValue();
	oleVar.bstrVal=pictureName.AllocSysString();
	this1->SetValue(oleVar);
}

CString CPictureProperty::GetPictureHight()
{
	CString picHight;
	CMFCPropertyGridProperty* this1;
	COleVariant oleVar;
	this1=this->GetSubItem(1);
	oleVar=this1->GetValue();
	picHight=oleVar.bstrVal;//�߶�
	return picHight;
}

void CPictureProperty::SetPictureHight(CString pictureHight)
{
	CMFCPropertyGridProperty* this1=this->GetSubItem(1);
	COleVariant oleVar=this1->GetValue();
	oleVar.bstrVal=pictureHight.AllocSysString();
	this1->SetValue(oleVar);
}

CString CPictureProperty::GetPictureWidth()
{
	CString picWidth;
	CMFCPropertyGridProperty* this1;
	COleVariant oleVar;
	this1=this->GetSubItem(2);
	oleVar=this1->GetValue();
	picWidth=oleVar.bstrVal;//���
	return picWidth;
}

void CPictureProperty::SetPictureWidth(CString pictureWidth)
{
	CMFCPropertyGridProperty* this1=this->GetSubItem(1);
	COleVariant oleVar=this1->GetValue();
	oleVar.bstrVal=pictureWidth.AllocSysString();
	this1->SetValue(oleVar);
}