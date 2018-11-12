
//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "myDialog.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("asdf")

Polyline_dialog* dialog;

class myEditorReactor : public AcEditorReactor{
public:
	
	virtual void abortDxfIn(AcDbDatabase* db){
		AfxMessageBox(L"abortDxfIn");
	}
	virtual void abortDxfOut(AcDbDatabase* db){
		AfxMessageBox(L"abortDxfOut");
	}
	virtual void abortInsert(AcDbDatabase* pTo){
		AfxMessageBox(L"abortInsert");
	}
	virtual void beginRightClick(const AcGePoint3d& clickPoint){
		AfxMessageBox(L"beginRightClick");
	}
};

AcEditor *paE;

myEditorReactor* pmER;

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CArxProject1App : public AcRxArxApp {

public:
	CArxProject1App () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		pmER = new myEditorReactor();
		acedEditor->addReactor(pmER);
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kNoDependencyMsg(void* pkt){
		AcRx::AppRetCode retCode = AcRxArxApp::On_kNoDependencyMsg(pkt) ;
		AfxMessageBox(L"On_kNoDependencyMsg");
		return (retCode);
	}
	
	

	virtual void RegisterServerComponents () {
	}
	
	
	static void asdfMyGroupMyCommand () {
		CAcModuleResourceOverride res;
		dialog = new Polyline_dialog();
		dialog->Create(IDD_DIALOG1);
		dialog->ShowWindow(SW_SHOW);
		//dialog->DoModal();
		//delete dialog;
	}

	// Modal Command with pickfirst selection
	// ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, asdfMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET)
	static void asdfMyGroupMyPickFirst () {
		ads_name result ;
		int iRet =acedSSGet (ACRX_T("_I"), NULL, NULL, NULL, result) ;
		if ( iRet == RTNORM ){
			// There are selected entities
			// Put your command using pickfirst set code here
		}
		else{
			// There are no selected entities
			// Put your command code here
		}
	}

	// Application Session Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, asdfMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION)
	static void asdfMyGroupMySessionCmd () {
		// Put your command code here
	}

	// The ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO macros can be applied to any static member 
	// function of the CArxProject1App class.
	// The function may or may not take arguments and have to return RTNORM, RTERROR, RTCAN, RTFAIL, RTREJ to AutoCAD, but use
	// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal to return
	// a value to the Lisp interpreter.
	//
	// NOTE: ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid.
	
	//- ACED_ADSFUNCTION_ENTRY_AUTO(classname, name, regFunc) - this example
	//- ACED_ADSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file
	//- ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) - a Lisp command (prefix C:)
	//- ACED_ADSCOMMAND_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file

	// Lisp Function is similar to ARX Command but it creates a lisp 
	// callable function. Many return types are supported not just string
	// or integer.
	// ACED_ADSFUNCTION_ENTRY_AUTO(CArxProject1App, MyLispFunction, false)
	static int ads_MyLispFunction () {
		//struct resbuf *args =acedGetArgs () ;
		
		// Put your command code here

		//acutRelRb (args) ;
		
		// Return a value to the AutoCAD Lisp Interpreter
		// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal

		return (RTNORM) ;
	}
	
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CArxProject1App)

ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, asdfMyGroup, MyCommand,    MyCommandLocal,    ACRX_CMD_MODAL,                       NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, asdfMyGroup, MyPickFirst,  MyPickFirstLocal,  ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, asdfMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION,    NULL)
ACED_ADSSYMBOL_ENTRY_AUTO (CArxProject1App, MyLispFunction, false)

