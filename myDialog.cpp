#include "stdafx.h"
#include "myDialog.h"



void createPolyline(std::vector<double> polylineDot){

	AcGePoint3dArray ptArr;
	size_t polylineDotLogicalSize = polylineDot.size() / 3;
	ptArr.setLogicalLength(polylineDotLogicalSize);
	size_t iter = 0;
	for(int i = 0; i < polylineDotLogicalSize; i++){
		ptArr[i].set(polylineDot.at(iter), polylineDot.at(iter + 1), polylineDot.at(iter + 2));
		iter = iter + 3;
	}

	AcDb3dPolyline *pNewPolyLine = new AcDb3dPolyline(AcDb::k3dSimplePoly, ptArr, Adesk::kFalse);
	
	pNewPolyLine->setColorIndex(3);
	AcDbBlockTable *pBlockTable;
	acdbHostApplicationServices() -> workingDatabase() -> getSymbolTable(pBlockTable, AcDb::kForRead);
	AcDbBlockTableRecord *pBlockTableRecord;

	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);
	pBlockTable->close();

	AcDbObjectId polylineObjectId;
	pBlockTableRecord->appendNcDbEntity(polylineObjectId, pNewPolyLine);
	pBlockTableRecord->close();

	pNewPolyLine->setLayer(L"0");
	pNewPolyLine->close();
}

/*************************************
     CLASS Polyline_dialog BEGIN
*************************************/

//>>>>>>Polyline_dialog_MESSAGE_MAP<<<<<<
BEGIN_MESSAGE_MAP(Polyline_dialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD,      &Polyline_dialog::OnButtonClicked_CButton_add)
	ON_BN_CLICKED(IDC_BUTTON_DEL,      &Polyline_dialog::OnButtonClicked_CButton_del)
	ON_BN_CLICKED(IDC_BUTTON_POLYLINE, &Polyline_dialog::OnButtonClicked_CButton_polyline)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, &Polyline_dialog::onAcadKeepFocus)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
//<<<<<<Polyline_dialog_MESSAGE_MAP>>>>>>

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*Polyline_dialog_BEGIN_MESSAGE_MAP_FUNCTIONS*/

void Polyline_dialog::OnButtonClicked_CButton_add(){

	if(myCEdit_value >= 42)
		return;

	myCEditArray[++myCEdit_value].Create(WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER,
		                          CRect(006, 10 + marginY, 156, 34 + marginY), this, myCEdit_ID++);

	myCEditArray[++myCEdit_value].Create(WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER,
		                          CRect(166, 10 + marginY, 316, 34 + marginY), this, myCEdit_ID++);

	myCEditArray[++myCEdit_value].Create(WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER,
		                          CRect(326, 10 + marginY, 476, 34 + marginY), this, myCEdit_ID++);

	marginY = marginY + 30;

}

void Polyline_dialog::OnButtonClicked_CButton_del(){

	
	if(myCEdit_value < 3)
		return;
	
	myCEditArray[myCEdit_value].DestroyWindow();
	myCEditArray[myCEdit_value - 1].DestroyWindow();
	myCEditArray[myCEdit_value - 2].DestroyWindow();

	myCEdit_value = myCEdit_value - 3;
	myCEdit_ID -= 3;
	marginY = marginY - 30;

}

void Polyline_dialog::OnButtonClicked_CButton_polyline(){

	wchar_t textFromCEdit[60];
	vector<double> numberArray;
	for(int i = 0; i <= myCEdit_value; i++){
		myCEditArray[i].GetWindowTextW(textFromCEdit, 60);
		numberArray.push_back(wcstod(textFromCEdit, NULL));
	}
	createPolyline(numberArray);
	
}

LRESULT Polyline_dialog::onAcadKeepFocus(WPARAM, LPARAM){
    return FALSE;
}


/*@Polyline_dialog_END_MESSAGE_MAP_FUNCTIONS@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

Polyline_dialog :: Polyline_dialog(CWnd* pParent/* = NULL*/) : CDialog(IDD_DIALOG1, pParent){
	
}

BOOL Polyline_dialog :: OnInitDialog(){
	CDialog::OnInitDialog();

	//>>>>>>CEdit<<<<<<
	myCEditArray = new myCEdit[300];
	marginY = 30;
	myCEdit_ID = 5000;
	myCEdit_value = 0;
	
	myCEditArray[myCEdit_value].Create  (WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER,
		                                   CRect(6, 10, 156, 34),   this,   myCEdit_ID);
	
	myCEditArray[++myCEdit_value].Create(WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER,
		                                   CRect(166, 10, 316, 34), this, ++myCEdit_ID);

	myCEditArray[++myCEdit_value].Create(WS_CHILD | WS_VISIBLE | ES_CENTER | WS_BORDER,
		                                   CRect(326, 10, 476, 34), this, ++myCEdit_ID);
	//<<<<<<CEdit>>>>>>

	//>>>>>>CButton<<<<<<
	CButton_add = new CButton();
	CButton_add->Create     (L"ADD",      WS_CHILD | WS_VISIBLE | ES_CENTER, 
		                       CRect(486, 10, 526, 34),   this, IDC_BUTTON_ADD);

	CButton_del = new CButton();
	CButton_del->Create     (L"DEL",      WS_CHILD | WS_VISIBLE | ES_CENTER, 
		                       CRect(536, 10, 576, 34),   this, IDC_BUTTON_DEL);

	CButton_polyline = new CButton();
	CButton_polyline->Create(L"POLYLINE", WS_CHILD | WS_VISIBLE | ES_CENTER, 
		                       CRect(486, 400, 576, 450), this, IDC_BUTTON_POLYLINE);
	//<<<<<<CButton>>>>>>
	return TRUE;
}

void Polyline_dialog :: OnClose(){
		
		for(int i = 0; i < myCEdit_value; i++){
			myCEditArray[i].DestroyWindow();
		}
		delete[] myCEditArray;

		
		
		CButton_add->DestroyWindow();
		CButton_del->DestroyWindow();
	  CButton_polyline->DestroyWindow();

		delete CButton_add;
		delete CButton_del;
	  delete CButton_polyline;
		CDialog::OnClose();
	}

/*************************************
      CLASS Polyline_dialog END
*************************************/

/*******************************
      CLASS MYCEDIT BEGIN
*******************************/

//>>>>>>MESSAGE_MAP<<<<<<
BEGIN_MESSAGE_MAP(myCEdit, CEdit)
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_WM_CREATE()
END_MESSAGE_MAP()
//<<<<<<MESSAGE_MAP>>>>>>


BOOL myCEdit::PreTranslateMessage(MSG* pMsg){
	
	if((pMsg->message == WM_KEYDOWN) && (GetKeyState(VK_CONTROL) < 0)){
		switch(pMsg->wParam){
		case 'A':
			SetSel(0, -1);
			return TRUE;
			break;
		case 'C':
			Copy();
			return TRUE;
			break;
		case 'V':
			Paste();
			return TRUE;
			break;
		case 'X':
			Cut();
			return TRUE;
			break;
		}
	}else{
		return CEdit::PreTranslateMessage(pMsg);
	}
	return CEdit::PreTranslateMessage(pMsg);
}

void myCEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

int myCEdit::OnCreate(LPCREATESTRUCT lpCreateStruct){
	CWnd::OnCreate(lpCreateStruct);
	this->SetWindowTextW(L"0.0000");
	return 1;
}

void myCEdit::OnKillFocus(CWnd *pNewWnd){
	using std::wstring;

	wchar_t text[40] = L"";
	this->GetWindowTextW(text, 40);
	wstring inputText = text;
	inputText = validator(inputText);
	this->SetWindowTextW(inputText.c_str());

	CEdit::OnKillFocus(pNewWnd);
	return;
	
}

void myCEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags){

	CString a;
	this->GetWindowTextW(a);
	//Проверка на ввод второго знака минус
	if(nChar == '-'){
		if(a.Find('-') != -1)
			return;
		if(a.IsEmpty())
			CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	
	if(nChar == ',' || nChar == '.'){
		if(a.Find('.') != -1)
			return;
		if(a.Find(',') != -1)
			return;
	}

	
	if((nChar >= '0' && nChar <= '9') || nChar == ',' || nChar == '.')
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	if(nChar == VK_BACK)
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	return;
}

/*******************************
      CLASS MYCEDIT END
*******************************/

#include <algorithm>


std::wstring validator(std::wstring const _inputString){
	
	using std::wstring;
  using std::string;
	using std::vector;
	using boost::split;

	enum{precise = 4};
	wstring inputString = _inputString;


	if(inputString == L""){
		wstring outputString = L"0.";
		for(int i = 0; i < precise; i++){
			outputString += L'0';
		}
		return outputString;
	}else{
		;
	}

	
	size_t inputStringLenght = inputString.length();
	wchar_t inputStringCurrentValue = L'0';
	for(size_t iter = 0; iter < inputString.length(); iter++){
		inputStringCurrentValue = inputString[iter];
		if(!((inputStringCurrentValue >= '0' && inputStringCurrentValue <= '9') || inputStringCurrentValue == ',' || inputStringCurrentValue == '.')){
			return L"0.0000";
		}
	}

	
	if(inputString.size() >= 2){
		int begin = 0;
		size_t end = inputString.size() - 1;
		for(auto iter = begin; iter <= end; iter++){
			if(inputString.at(0) == L'0' && (inputString.at(1) != L'.' || (inputString.at(1) >= L'1' && inputString.at(1) <= L'9'))){
				inputString.erase(0, 1);
				end = inputString.size() - 1;
				iter = 0;
				continue;
			}
		}
	}

	
	if(inputString.find(L'.') == string::npos && inputString.find(L',') == string::npos){
		wstring outputString;
		outputString += inputString;
		outputString += L'.';
		for(int i = 0; i < precise; i++){
			outputString += L'0';
		}
		return outputString;
	}
	
	vector<wstring> v2;
	split(v2, inputString, [](wchar_t t){ if(t == L'.' || t == L',')return true;else return false;});
	wstring &beforeDot = v2[0];
	wstring &afterDot  = v2[1];

	
	size_t sizeAfterDot = afterDot.size();
	if(sizeAfterDot != precise){
		
		if(sizeAfterDot < precise){
			while(sizeAfterDot != precise){
				afterDot.push_back(L'0');
				sizeAfterDot++;
			}
		}else{
			afterDot.resize(4);
		}
	}
	
	if(beforeDot == L"")
		beforeDot.push_back(L'0');

	wstring outputString;
	outputString += beforeDot;
	outputString += L'.';
	outputString += afterDot;

	return outputString;
}
