#include "StdAfx.h"
#include "Format.h"

CFormat::CFormat(void)
{
}

CFormat::~CFormat(void)
{
}

//统一字体大小
///由于函数的改变，暂时不使用CFont参数
void CFormat::UnionFontSize(CRichEditView *pRichEditView, CFont* pfont)
{
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();
	/*pRichEditCtrl->SetSel(0,pRichEditCtrl->GetTextLength());
	CHARFORMAT cf;
	pRichEditCtrl->GetSelectionCharFormat(cf);
	cf.cbSize=fontSize;
	pRichEditCtrl->SetSelectionCharFormat(cf);*/
	//font.CreateStockObject(DEFAULT_GUI_FONT);

//	pRichEditCtrl->SetFont(pfont);

	long textStart=0;
	long textEnd=-1;
	if(pRichEditCtrl->GetSelText().GetLength()>0){
		pRichEditCtrl->GetSel(textStart,textEnd);
		textEnd++;
	}
	else{
		textStart=0;
		textEnd=pRichEditCtrl->GetTextLength();
	}
	for(;textStart<textEnd-1;textStart++){
		pRichEditCtrl->SetSel(textStart,textStart+1);
		CHARFORMAT cf;
		pRichEditCtrl->GetSelectionCharFormat(cf);
		cf.dwMask=CFM_BOLD|CFM_FACE|CFM_SIZE|CFM_CHARSET|CFM_PROTECTED; 
		cf.yHeight=210;
		pRichEditCtrl->SetSel(textStart,textStart+1);
		pRichEditCtrl->SetSelectionCharFormat(cf);
	}
}

void CFormat::DelSpaceLines(CRichEditView *pRichEditView)
{
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();
	int lineCun=pRichEditCtrl->GetLineCount();
	int pos=-1;
	for(int i=0;i<lineCun;i++){

		//删除空行
		wchar_t ch[500];
		memset(ch,0,500);
		pRichEditCtrl->GetLine(i,ch,500);
		CString lineText=ch;
		lineText.TrimRight(_T("\n"));
		lineText.TrimRight(_T("\r"));
		lineText.TrimLeft(_T(" "));
		lineText.TrimLeft(_T("	"));
		lineText.TrimRight(_T(" "));
		if(lineText==_T("")){
			//删除当前行
			long startPos,endPos;
			startPos=pRichEditCtrl->LineIndex(i);
			endPos=pRichEditCtrl->LineIndex(i+1);
			pRichEditCtrl->SetSel(startPos,endPos);
			pRichEditCtrl->ReplaceSel(_T(""));
			i--;//当前行退一行
			lineCun--;//总行数减1
		}
	}
}

void CFormat::DelUselessSpaces(CRichEditView *pRichEditView)
{
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();
	int lineCun=pRichEditCtrl->GetLineCount();
	int pos=-1;
	//第一：删除段前多余空格
	for(int i=0;i<lineCun;i++){
		//删除多余空格
		pos=pRichEditCtrl->LineIndex(i);
		pRichEditCtrl->SetSel(pos,pos+1);
		CString strSel=pRichEditCtrl->GetSelText();
		if(!strSel.IsEmpty()){
			CHARFORMAT2 cf;
			pRichEditCtrl->GetSelectionCharFormat(cf);
			CString cstr;
			PARAFORMAT pf;
			pRichEditCtrl->GetParaFormat(pf);
			if(pf.dxStartIndent>4)
				pf.dxStartIndent=4;
			pRichEditCtrl->SetParaFormat(pf);
		}
	}
	//第二：删除行中多余空格
	long startPos=0,endPos=-1;
	long ChnStart=0x4E00,ChnEnd=0x9FBF;
	pRichEditCtrl->SetSel(startPos,endPos);
	pRichEditCtrl->GetSel(startPos,endPos);
	CString refString;
	CString frontStr,backStr;

	for(int i=1;i<endPos-2;i++){
		pRichEditCtrl->GetTextRange(i,i+1,refString);
		if(refString.Compare(_T(" "))==0){
			pRichEditCtrl->GetTextRange(i-1,i,frontStr);
			pRichEditCtrl->GetTextRange(i+1,i+2,backStr);
			if( frontStr.Compare(_T("，"))==0||
				frontStr.Compare(_T("。"))==0||
				frontStr.Compare(_T("“"))==0||
				frontStr.Compare(_T("”"))==0||
				frontStr.Compare(_T("；"))==0||
				frontStr.Compare(_T("："))==0||
				frontStr.Compare(_T("？"))==0||
				frontStr.Compare(_T("）"))==0||
				frontStr.Compare(_T("（"))==0||
				frontStr.Compare(_T("‘"))==0||
				frontStr.Compare(_T("’"))==0){
					//中文标点符号
					pRichEditCtrl->SetSel(i,i+1);
					pRichEditCtrl->ReplaceSel(_T(""));

					//处理索引
					i=i-2;
					endPos--;
			}
			else if(((ChnStart<=frontStr[0]&&frontStr[0]<=ChnEnd)||
				(ChnStart<=backStr[0]&&backStr[0]<=ChnEnd))){
					//中文文字
					pRichEditCtrl->SetSel(i,i+1);
					pRichEditCtrl->ReplaceSel(_T(""));

					//处理索引
					i=i-2;
					endPos--;
			}
		}
	}
}

void CFormat::ChangeLineAuto(CRichEditView *pRichEditView)
{
}

void CFormat::DelFrontSpaces(CRichEditView *pRichEditView)//删除行前空格
{
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();
	long start=-1,end=-1;
	pRichEditCtrl->GetSel(start,end);
	long lineIndex=pRichEditCtrl->LineIndex(start);
	long eachLineIndex=lineIndex;
	CString refStr;
	while(eachLineIndex<end){//外循环，迭代没一行
		pRichEditCtrl->GetTextRange(start,start+1,refStr);
		while(refStr==" "){//内循环，查找当前行前面的空格并删除
			pRichEditCtrl->SetSel(start,start+1);
			pRichEditCtrl->ReplaceSel(_T(""));
			end--;
			if(start+1>=end)
				break;
			pRichEditCtrl->GetTextRange(start,start+1,refStr);
		}
		if(lineIndex>=end)
			break;
		eachLineIndex=pRichEditCtrl->LineIndex(lineIndex++);
		start=eachLineIndex;
	}
}

void CFormat::ReplaceKeySymbol(CSymbolReplaceSetDlg* pSymbolReplaceSetDlg, CRichEditView *pRichEditView)
{
	long startPos=0,endPos=0;
	CRichEditCtrl* pRichEditCtrl=&pRichEditView->GetRichEditCtrl();

	//判断是否为全文替换，确定终止位置
	if(pSymbolReplaceSetDlg->m_nSelect==1){
		long lineCount=pRichEditCtrl->GetLineCount();
		CString strLine;
		for(long i=0;i<lineCount;i++){
			pRichEditCtrl->GetLine(i,strLine.GetBuffer());
			if(strLine.Find(_T("**注释**"))!=-1){
				endPos=pRichEditCtrl->LineIndex(i);
			}
		}
	}
	else{
		endPos=pRichEditCtrl->GetTextLength();
	}

	//开始替换
	CString strCh;
	while(startPos<endPos-1){
		pRichEditCtrl->GetTextRange(startPos,startPos+1,strCh);

		//////////单个字符比较//////////////
		//逗号
		if(pSymbolReplaceSetDlg->m_Symbol1){
			if(strCh.Compare(_T(","))==0){
				pRichEditCtrl->SetSel(startPos,startPos+1);
				if(!pSymbolReplaceSetDlg->m_editString1.IsEmpty()){
					pRichEditCtrl->ReplaceSel(
						pSymbolReplaceSetDlg->m_editString1);
				}
				else{
					pRichEditCtrl->ReplaceSel(_T("，"));
				}
			}
		}
		//句号
		if(pSymbolReplaceSetDlg->m_Symbol2){
			if(strCh.Compare(_T("."))==0){
				pRichEditCtrl->SetSel(startPos,startPos+1);
				if(!pSymbolReplaceSetDlg->m_editString2.IsEmpty()){
					pRichEditCtrl->ReplaceSel(
						pSymbolReplaceSetDlg->m_editString2);
				}
				else{
					pRichEditCtrl->ReplaceSel(_T("。"));
				}
			}
		}
		//分号
		if(pSymbolReplaceSetDlg->m_Symbol3){
			if(strCh.Compare(_T(";"))==0){
				pRichEditCtrl->SetSel(startPos,startPos+1);
				if(!pSymbolReplaceSetDlg->m_editString3.IsEmpty()){
					pRichEditCtrl->ReplaceSel(
						pSymbolReplaceSetDlg->m_editString3);
				}
				else{
					pRichEditCtrl->ReplaceSel(_T("；"));
				}
			}
		}
		//冒号
		if(pSymbolReplaceSetDlg->m_Symbol4){
			if(strCh.Compare(_T(":"))==0){
				pRichEditCtrl->SetSel(startPos,startPos+1);
				if(!pSymbolReplaceSetDlg->m_editString4.IsEmpty()){
					pRichEditCtrl->ReplaceSel(
						pSymbolReplaceSetDlg->m_editString4);
				}
				else{
					pRichEditCtrl->ReplaceSel(_T("："));
				}
			}
		}
		//波浪号
		if(pSymbolReplaceSetDlg->m_Symbol5){
			if(strCh.Compare(_T("~"))==0){
				pRichEditCtrl->SetSel(startPos,startPos+1);
				if(!pSymbolReplaceSetDlg->m_editString5.IsEmpty()){
					pRichEditCtrl->ReplaceSel(
						pSymbolReplaceSetDlg->m_editString5);
				}
				else{
					pRichEditCtrl->ReplaceSel(_T("～"));
				}
			}
		}
		//括号
		if(pSymbolReplaceSetDlg->m_Symbol7){
			if(strCh.Compare(_T("("))==0){
				pRichEditCtrl->SetSel(startPos,startPos+1);
				pRichEditCtrl->ReplaceSel(_T("（"));
			}
			else if(strCh.Compare(_T(")"))==0){
				pRichEditCtrl->SetSel(startPos,startPos+1);
				pRichEditCtrl->ReplaceSel(_T("）"));
			}
		}
		//单破折号
		if(pSymbolReplaceSetDlg->m_Symbol8){
			if(strCh.Compare(_T("-"))==0){
				pRichEditCtrl->SetSel(startPos,startPos+1);
				if(!pSymbolReplaceSetDlg->m_editString8.IsEmpty()){
					pRichEditCtrl->ReplaceSel(
						pSymbolReplaceSetDlg->m_editString8);
				}
				else{
					pRichEditCtrl->ReplaceSel(_T("—"));
				}
			}
		}

		/////////////双字符比较///////////////
		pRichEditCtrl->GetTextRange(startPos,startPos+2,strCh);
		//破折号
		if(pSymbolReplaceSetDlg->m_Symbol6){
			if(strCh.Compare(_T("--"))==0){
				pRichEditCtrl->SetSel(startPos,startPos+1);
				if(!pSymbolReplaceSetDlg->m_editString6.IsEmpty()){
					pRichEditCtrl->ReplaceSel(
						pSymbolReplaceSetDlg->m_editString6);
				}
				else{
					pRichEditCtrl->ReplaceSel(_T("—"));
				}
			}
		}
		//双破折号替换
		if(pSymbolReplaceSetDlg->m_IsDoubleDash)
		{
			if(strCh.Compare(_T("——"))==0){
				CString replaceStr;
				pSymbolReplaceSetDlg->
					m_doubleDashEdit.GetWindowTextW(replaceStr);
				pRichEditCtrl->SetSel(startPos,startPos+2);
				pRichEditCtrl->ReplaceSel(replaceStr);
			}
		}

		startPos++;
	}
}