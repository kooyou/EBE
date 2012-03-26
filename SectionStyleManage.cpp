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
	//搜索当前段落的序号
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
			//输出标识文本
			RECtrl.SetSel(paraPos,paraPos);
			CString cssStyle=_T("<$class=\"")+
				styleStr+_T("\" style=\"\">\n");
			RECtrl.ReplaceSel(cssStyle);
			RECtrl.SetSel(paraPos,paraPos+cssStyle.GetLength());
			CHARFORMAT cf;
			RECtrl.GetSelectionCharFormat(cf);
			cf.yHeight=230;//标识大小(标识表格的标识文字高度为210)
			wcscpy_s(cf.szFaceName,_T("宋体"));//设置为宋体
			cf.crTextColor=RGB(0,0,255);//颜色为蓝色
			RECtrl.SetSelectionCharFormat(cf);

			break;
		}
	}
}
