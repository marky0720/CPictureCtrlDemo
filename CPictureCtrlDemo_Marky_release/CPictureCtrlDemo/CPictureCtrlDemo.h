// CPictureCtrlDemo.h : Hauptheaderdatei f�r die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "\"stdafx.h\" vor dieser Datei f�r PCH einschlie�en"
#endif

#include "resource.h"		// Hauptsymbole


// CCPictureCtrlDemoApp:
// Siehe CPictureCtrlDemo.cpp f�r die Implementierung dieser Klasse
//

class CCPictureCtrlDemoApp : public CWinApp
{
public:
	CCPictureCtrlDemoApp();

// �berschreibungen
	public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CCPictureCtrlDemoApp theApp;