#pragma once

class CHtmlProperty: public CMFCPropertyGridProperty
{
public:
	CHtmlProperty();
	virtual ~CHtmlProperty();

	void AddModelOpatoin(CString modelName);
	CString GetBookName();
	CString GetCurPage();
	int GetPageLeftRight();//��ҳ����1����ҳ����2
	int GetExpStyle();//���������ַ���1��ԲȦ����2
//	void GetPicProperty(CPicProperty* picPro);
	CString SetPage(CString pageNum);
	int SetPageLeftRight(int pageLeftRight);//��ҳ����1����ҳ����2
	CString GetModel();
	CString GetExpModel();
	CString GetTextCss();
	void SetTextCss(CString textCss);
	void SetBookName(CString bookName);
	void SetModel(CString model);
	void SetExpModel(CString expModel);
	void SetExpStyle(int expStyle);
	void RemoveModelAllOpation();
public:
	CString strGroupName;
};
