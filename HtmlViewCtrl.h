#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CHtmlView��"
#endif 

// CHtmlViewCtrl Html ��ͼ

class CHtmlViewCtrl : public CHtmlView
{
	DECLARE_DYNCREATE(CHtmlViewCtrl)

public:
	CHtmlViewCtrl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CHtmlViewCtrl();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


