// ItemEditCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EBE.h"
#include "ItemEditCtrl.h"
#include "UsefulStringList.h"


// CItemEditCtrl

IMPLEMENT_DYNAMIC(CItemEditCtrl, CEdit)

CItemEditCtrl::CItemEditCtrl()
{

}

CItemEditCtrl::~CItemEditCtrl()
{
}


BEGIN_MESSAGE_MAP(CItemEditCtrl, CEdit)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CItemEditCtrl ��Ϣ�������



void CItemEditCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	// TODO: �ڴ˴������Ϣ����������
	// �õ������ڣ���֪ͨ�����ڽ����༭����
	((CUsefulStringList*)this->GetParent())->ItemEditEnd();
	this->ShowWindow(SW_HIDE);
}
