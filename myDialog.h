
#include "resource.h"


class myCEdit : public CEdit{
public:
	myCEdit() : CEdit(){}

	afx_msg void OnKillFocus(CWnd *pNewWnd);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){}
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
 DECLARE_MESSAGE_MAP()
};


std::wstring validator(std::wstring const _inputString);


class Polyline_dialog : public CDialog{
public:
	Polyline_dialog(CWnd* pParent = NULL);
	virtual BOOL OnInitDialog();
	CListBox* cListBox;
	//>>>>>>myCEdit<<<<<<
	
	myCEdit* myCEditArray;
	
	int myCEdit_ID;
	
	int myCEdit_value;
	
	int marginY; // = 30;
	//<<<<<<myCEdit>>>>>>

	//>>>>>>CButton<<<<<<
	
	enum{IDC_BUTTON_ADD = 2001, IDC_BUTTON_DEL = 2002, IDC_BUTTON_POLYLINE = 2003};
	CButton *CButton_add;
	CButton *CButton_del;
	CButton *CButton_polyline;

	
	void OnButtonClicked_CButton_add();
	void OnButtonClicked_CButton_del();
	void OnButtonClicked_CButton_polyline();
	//>>>>>>CButton<<<<<<

	afx_msg void OnClose();
	afx_msg LRESULT Polyline_dialog::onAcadKeepFocus(WPARAM, LPARAM);



	DECLARE_MESSAGE_MAP()
};
