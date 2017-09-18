// CPictureCtrlDemoDlg.h : Headerdatei
//

#pragma once
#include "picturectrl.h"
#include "afxwin.h"

#define BMP_FILTER "BMP Files (*.bmp)||"
#define RAW_FILTER "RAW Files (*.raw)||"
#define BMP_TEMP "EDIT_BMP.bmp"
#define RAW_ORIG_TEMP "EDIT_RAW_ORIG.bmp"
#define RAW_EDIT_TEMP "EDIT_RAW_EDIT.bmp"
// CCPictureCtrlDemoDlg-Dialogfeld
class CCPictureCtrlDemoDlg : public CDialog
{
// Konstruktion
public:
	CCPictureCtrlDemoDlg(CWnd* pParent = NULL);	// Standardkonstruktor
    CString OpenFileDg(CString szFilter);
    void EditBmpImage(CString FileName);
    void ShowRAWImage(CString FileName, char* pChar);
    void EditRAWImage(CString FileName, char* pChar);
    //void EditRAWImage((CString FileName);

// Dialogfelddaten
	enum { IDD = IDD_CPICTURECTRLDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
// 	afx_msg void OnBnClickedButton4();
	CPictureCtrl m_picCtrl;
    afx_msg void OnBnClickedButton4();
    CEdit CTRL_RAW_W;
    CEdit CTRL_RAW_H;
    CEdit CTRL_RAW_BITS;
    CEdit CTRL_RAW_SHIFT_BITS;
};
