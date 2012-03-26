#include "StdAfx.h"
#include "SectionStyleManage.h"

SectionStyleManage::SectionStyleManage(void)
{
}

SectionStyleManage::~SectionStyleManage(void)
{
}

void SectionStyleManage::addStyle(CString styleStr,CRichEditView* pRichEditView)
{
	CRichEditCtrl &RECtrl=pRichEditView->GetRichEditCtrl();

	wchar_t ch[500];
	CString lineText;
	int i=0;
	//������ǰ��������
	long startPos=-1,endPos=-1;
	RECtrl.GetSel(startPos,endPos);
	long lineIndex=RECtrl.LineFromChar(startPos);
	for(i=lineIndex;i>=0;i--){
		memset(ch,0,500);
		RECtrl.GetLine(i,ch,500);
		lineText=ch;
		if(lineText[0]==' '&&lineText[1]==' '){
			long paraPos=-1;
			paraPos=RECtrl.LineIndex(i);
			if(paraPos<0)
				return;
			//�����ʶ�ı�
			RECtrl.SetSel(paraPos,paraPos);
			CString cssStyle=_T("<$class=\"")+
				styleStr+_T("\" style=\"\">\n");
			RECtrl.ReplaceSel(cssStyle);
			RECtrl.SetSel(paraPos,paraPos+cssStyle.GetLength());
			CHARFORMAT cf;
			RECtrl.GetSelectionCharFormat(cf);
			cf.yHeight=230;//��ʶ��С(��ʶ���ı�ʶ���ָ߶�Ϊ210)
			wcscpy_s(cf.szFaceName,_T("����"));//����Ϊ����
			cf.crTextColor=RGB(0,0,255);//��ɫΪ��ɫ
			RECtrl.SetSelectionCharFormat(cf);

			break;
		}
	}
}
