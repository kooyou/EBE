#include "StdAfx.h"
#include "WinTxtTranslation.h"

enum{NOTENUMTYPE_ARAB=1,NOTENUMTYPE_AIRCLE};

WinTxtTranslation::WinTxtTranslation(void)
{
}

WinTxtTranslation::~WinTxtTranslation(void)
{
}

void WinTxtTranslation::StartTranslate(CRichEditCtrl *pRichEditCtrl,CPropertyManage* propertyManage,CSymbolReplaceSetDlg* pSymbolReplaceSetDlg)
{
	this->m_pRichEditCtrl=pRichEditCtrl;
	this->m_pPropertyManage=propertyManage;
	this->m_pSymbolReplaceSetDlg=pSymbolReplaceSetDlg;

	//��ʼ
	ReadWinTxt();
	//��ʶע�ͱ��
	MarkNoteNum();
	//�������ʽ��ʶ
	HandleSectionStyle();
	//��Ӣ���ַ��滻
	KeyWordReplace();
	//��ʶ������
	MarkHandle();
}

void WinTxtTranslation::ReadWinTxt()
{
	wchar_t wch[500];
	CString lineText;//ÿһ�е��ı�
	int lineCount=m_pRichEditCtrl->GetLineCount();

	for(int i=0;i<lineCount;i++){
		memset(wch,0,500);
		m_pRichEditCtrl->GetLine(i,wch,500);
		lineText=wch;
		lineText.TrimRight(_T("\n"));
		lineText.TrimRight(_T("\r"));
		lineText.TrimRight(_T(" "));
		if(lineText.GetLength()<1)//���в���
			continue;
		//ɾ������ո�
		DelExcessSpace(lineText);

		//����ʽ��ʶ
		MarkLineStyle(lineText);

		//��ÿһ��д������
		m_vecEachLine.push_back(lineText);
	}
}

int WinTxtTranslation::DelExcessSpace(CString& lineText)
{//ɾ������ո�
	int delCunt=0;
	int delpos=-1;
	delpos=lineText.FindOneOf(_T(" "));
	while(delpos>=0){
		if(delpos<=0){
			delpos=lineText.Find(_T(" "),delpos+1);
			continue;
		}
		delCunt++;
		if(!((lineText[delpos-1]<='z'&&lineText[delpos-1]>='a')||
			(lineText[delpos-1]<='Z'&&lineText[delpos-1]>='A')||
			lineText[delpos-1]==' '))
		{
			lineText.Delete(delpos,1);
			delpos--;//���¼�����ʼλ��
		}
		else
			delCunt--;
		delpos=lineText.Find(_T(" "),delpos+1);
	}
	return delCunt;
}

void WinTxtTranslation::KeyWordReplace()
{
	CString lineText;
	for(int i=0;i<(int)m_vecEachLine.size();i++){
		lineText=m_vecEachLine[i];
		if(m_pSymbolReplaceSetDlg->m_nSelect==1)
			//����ȫ���滻�Ļ���ע���ı����滻
			if(lineText.Find(_T("**ע��**"))!=-1)
				break;

		//�ѽ������滻�Ĳ����ŵ���ǰ̨������Ͳ���Ҫ��
//		ReplaceFromReplaceSetDlg(lineText);

		m_vecEachLine[i]=lineText;
	}
}

//�ж��Ƿ�Ϊת���ַ�
void WinTxtTranslation::findIsESC(CString& lineText)
{
	int startPos=0;
	int symbolPos=0;
	while(startPos>=0){
		startPos=lineText.Find(_T("&"),startPos);
		if(startPos<0)
			break;
		symbolPos=lineText.Find(_T("��"),startPos);
		if(symbolPos<0)
			break;
		if(symbolPos-startPos<10){//�ж�ת���ַ���������10
			lineText.SetAt(symbolPos,';');
		}
	}
}

void WinTxtTranslation::ReplaceFromReplaceSetDlg(CString& lineTextToReplace)
{
	//�������滻
	m_pSymbolReplaceSetDlg->UpdateData(true);//ˢ������

	if(m_pSymbolReplaceSetDlg->m_Symbol1)//����
	{
		if(m_pSymbolReplaceSetDlg->m_editString1.IsEmpty())
			lineTextToReplace.Replace(_T(","),_T("��"));
		else{
			lineTextToReplace.Replace(_T(","),
				m_pSymbolReplaceSetDlg->m_editString1);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol2)//���
	{
		if(m_pSymbolReplaceSetDlg->m_editString2.IsEmpty())
			lineTextToReplace.Replace(_T("."),_T("��"));
		else{
			lineTextToReplace.Replace(_T("."),
				m_pSymbolReplaceSetDlg->m_editString2);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol3)//�ֺ�
	{
		if(m_pSymbolReplaceSetDlg->m_editString3.IsEmpty())
		{
			lineTextToReplace.Replace(_T(";"),_T("��"));
			findIsESC(lineTextToReplace);//�ж��Ƿ�Ϊת���ַ�
		}
		else{
			lineTextToReplace.Replace(_T(";"),
				m_pSymbolReplaceSetDlg->m_editString3);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol4)//ð��
	{
		if(m_pSymbolReplaceSetDlg->m_editString4.IsEmpty())
			lineTextToReplace.Replace(_T(":"),_T("��"));
		else{
			lineTextToReplace.Replace(_T(":"),
				m_pSymbolReplaceSetDlg->m_editString4);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol5)//���˺�
	{	
		if(m_pSymbolReplaceSetDlg->m_editString5.IsEmpty())
			lineTextToReplace.Replace(_T("~"),_T("��"));
		else{
			lineTextToReplace.Replace(_T("~"),
				m_pSymbolReplaceSetDlg->m_editString5);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol6)//���ۺ�
	{
		if(m_pSymbolReplaceSetDlg->m_editString6.IsEmpty())
			lineTextToReplace.Replace(_T("--"),_T("��"));
		else{
			lineTextToReplace.Replace(_T("--"),
				m_pSymbolReplaceSetDlg->m_editString6);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol7)//����
	{
		lineTextToReplace.Replace(_T("("),_T("��"));
		lineTextToReplace.Replace(_T(")"),_T("��"));
	}

	if(m_pSymbolReplaceSetDlg->m_Symbol8)//�����ۺ�
	{
		if(m_pSymbolReplaceSetDlg->m_editString8.IsEmpty())
			lineTextToReplace.Replace(_T("-"),_T("��"));
		else{
			lineTextToReplace.Replace(_T("-"),
				m_pSymbolReplaceSetDlg->m_editString8);
		}
	}

	if(m_pSymbolReplaceSetDlg->m_IsDoubleDash)//˫���ۺ��滻
	{
		CString replaceStr;
		m_pSymbolReplaceSetDlg->m_doubleDashEdit.GetWindowTextW(replaceStr);
		lineTextToReplace.Replace(_T("����"),replaceStr);
	}
}
//������ʱû�õ�
void WinTxtTranslation::EngChnRep(CString& lineText)
{
	int pos=0;
	while(pos!=-1){
		pos=lineText.Find(_T("��"),pos);
		if(pos>0){
		if((lineText[pos-1]>='a'&&lineText[pos-1]<='z')||
			(lineText[pos-1]>='A'&&lineText[pos-1]<='Z')||
			(lineText[pos-1]>='0'&&lineText[pos-1]<='9'))
			if(lineText.GetLength()!=pos+1){
				if((lineText[pos+1]>='a'&&lineText[pos+1]<='z')||
			(lineText[pos+1]>='A'&&lineText[pos+1]<='Z')||
			(lineText[pos+1]>='0'&&lineText[pos+1]<='9')){
					lineText.SetAt(pos,',');
				}
			}
			else
			{
				lineText.SetAt(pos,',');
			}
			
		if(lineText.GetLength()==pos)
			break;
		pos++;
		}
	}

	pos=0;
	while(pos!=-1){
		pos=lineText.Find(_T("��"),pos);
		if(pos>0){
		if((lineText[pos-1]>='a'&&lineText[pos-1]<='z')||
			(lineText[pos-1]>='A'&&lineText[pos-1]<='Z')||
			(lineText[pos-1]>='0'&&lineText[pos-1]<='9'))
			if(lineText.GetLength()!=pos+1){
				if((lineText[pos+1]>='a'&&lineText[pos+1]<='z')||
			(lineText[pos+1]>='A'&&lineText[pos+1]<='Z')||
			(lineText[pos+1]>='0'&&lineText[pos+1]<='9')){
					lineText.SetAt(pos,'.');
				}
			}
			else
			{
				lineText.SetAt(pos,'.');
			}
			
		if(lineText.GetLength()==pos)
			break;
		pos++;
		}
	}

	pos=0;
	while(pos!=-1){
		pos=lineText.Find(_T("��"),pos);
		if(pos>0){
		if((lineText[pos-1]>='a'&&lineText[pos-1]<='z')||
			(lineText[pos-1]>='A'&&lineText[pos-1]<='Z')||
			(lineText[pos-1]>='0'&&lineText[pos-1]<='9'))
			if(lineText.GetLength()!=pos+1){
				if((lineText[pos+1]>='a'&&lineText[pos+1]<='z')||
			(lineText[pos+1]>='A'&&lineText[pos+1]<='Z')||
			(lineText[pos+1]>='0'&&lineText[pos+1]<='9')){
					lineText.SetAt(pos,';');
				}
			}
			else
			{
				lineText.SetAt(pos,';');
			}
			
		if(lineText.GetLength()==pos)
			break;
		pos++;
		}
	}
}

void WinTxtTranslation::MarkLineStyle(CString& lineText)
{
	int findIndex=-1;
	//���nobr
	if(lineText.Find(_T("<nobr>"))!=-1){
		lineText.Replace(_T("<nobr>"),_T("##nobr##"));
	}

	//���letter-spaing
	findIndex=lineText.Find(_T("<LS="));
	if(findIndex!=-1){
		lineText.Replace(_T("<LS="),_T("##LS="));
		findIndex=lineText.Find(_T(">"),findIndex+1);
		if(findIndex!=-1){
			lineText.Delete(findIndex,1);
			lineText.Insert(findIndex,_T("##"));
		}
	}

	//���<em>
	//<em>����Ҫ���
}

void WinTxtTranslation::MarkNoteNum()
{
	bool IsFirst=true;
	int cstrIndex=0;
	CString expStart=_T("^^^");//��סע�ͱ�ŵı�ʶ��
	CString expEnd=_T("^^^");
	CString strExpNum=_T("");

	CString lineText;//ÿ�е�����

	//ȷ��ע����ʽ
	int noteNumType=m_pPropertyManage->m_pHtmlProperty->GetExpStyle();

	for(int index=0;index<(int)m_vecEachLine.size();index++){
		lineText=m_vecEachLine[index];
		CString lenstr(lineText);//תΪCSringW��ʽ����ȡ�ַ���
		int len=lineText.GetLength();//�õ���һ�е��ַ������������ֽ���
		int i=0;

		//�ж��Ƿ�ע���ı�
		if(lineText.Find(_T("**ע��**"))!=-1){
			lineText=_T("##**ע��**");//����"#"����ʶע�Ϳ�ʼ
			m_vecEachLine[index]=lineText;
			return;
		}

		switch(noteNumType)//ע����ʽ
		{
		case NOTENUMTYPE_ARAB://������������ʽ
			if(-1==lineText.Find(_T("<**")))
				break;
			lineText.Replace(_T("<**"),expStart);
			lineText.Replace(_T("**>"),expEnd);
			break;
		case NOTENUMTYPE_AIRCLE://ԲȦ��ʽ
			for(i=0;i<len;i++){
				if(lenstr[i]>=9312&&lenstr[i]<=9322){//����ԲȦ��ע���ַ�
			/*		//ǰ�����ܿ��ܽ�����ע���ı���ע���ı�����Ҫ���<span>
					if(i<=2)
						break;*/
					CString strExpNum(lenstr[i]);
					lineText.Replace(strExpNum,expStart+strExpNum+expEnd);
				}
			}
			break;
		default:
			break;
		}

		//�����޸ĺ���ı�
		m_vecEachLine[index]=lineText;
	}
}
void WinTxtTranslation::HandleSectionStyle()
{
	//��ʼ��CssStyle����
	for(std::vector<CString>::iterator iter=m_vecEachLine.begin();iter!=m_vecEachLine.end();iter++){
		std::vector<CString> vecStr;
		vecStr.push_back(_T(""));
		vecStr.push_back(_T(""));
		vecStr.push_back(_T(""));
		m_vecSectionStyle.push_back(vecStr);
	}

	int originTextLine=0;
	CString lineText;
	//����vector����
	for(std::vector<CString>::iterator iter=m_vecEachLine.begin();iter!=m_vecEachLine.end();){
		lineText=*iter;
		lineText.TrimRight(_T("\n"));
		lineText.TrimRight(_T("\r"));
		lineText.TrimRight(_T(" "));

		//��ʽ�ı��е���
		originTextLine++;

		//����Ƿ���cssStyle��ʽ��ʶ��
		if(lineText.Find(_T("$class="))!=-1){
			RecordSectionStyle(lineText,originTextLine-1);
			originTextLine--;
			iter=m_vecEachLine.erase(iter);//��Ϊerase֮���iterator����Ч
		}
		else{
			++iter;//��Ϊerase��ʹiterator��Ч
		}
		/////////////////////////////////////
	}

}

void WinTxtTranslation::RecordSectionStyle(CString lineText, int lineIndex)
{
	if(m_vecSectionStyle.empty())
		return;
	CString cssStr;
	CString styleStr;
	//ɾ������ı�ʶ����
	lineText.Replace(_T("$"),_T(""));

	int pos;
	//��ȡclass
	pos=lineText.Find(_T("style"));
	cssStr=lineText.Left(pos);
	cssStr.TrimRight(_T(" "));
	cssStr.TrimRight(_T("\""));
	cssStr.TrimLeft(_T(" "));
	cssStr.Replace(_T("<class=\""),_T(""));

	//��ȡstyle
	styleStr=lineText.Right(lineText.GetLength()-pos);
	styleStr.TrimRight(_T(" "));
	styleStr.TrimRight(_T(">"));


	//���ÿ�е�cssStyle
	m_vecSectionStyle[lineIndex][0]=_T("##paraStart##");
	m_vecSectionStyle[lineIndex][1]=cssStr;
	m_vecSectionStyle[lineIndex][2]=styleStr;
}

void WinTxtTranslation::MarkHandle()
{
	CString lineText;
	for(std::vector<CString>::iterator iter=m_vecEachLine.begin();iter!=m_vecEachLine.end();iter++){
		lineText=*iter;
		//�ж��Ƿ���ͼƬ��ʶ��
		if(lineText.Compare(_T("**Pic_Start**"))==0){
			//д��ͼƬ��ʼ��ʶ��
			lineText=_T("pic#start");
		}

		if(lineText.Compare(_T("**Pic_End**"))==0){
			//д��ͼƬ������ʶ��
			lineText=_T("pic#start");
		}
		//�ж��Ƿ��Ǳ���ʶ��
		if(lineText.Find(_T("**Table_Start**"))!=-1){
			//���ʼ
			lineText=_T("table#start");
		}
		if(lineText.Find(_T("**Table_End**"))!=-1){
			//������
			lineText=_T("table#end");
		}
		
		//�����޸ĵ��ı�
		*iter=lineText;
	}
}