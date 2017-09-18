// CPictureCtrlDemoDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CPictureCtrlDemo.h"
#include "PictureCtrl.h"
#include "CPictureCtrlDemoDlg.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "bitmap_image.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg-Dialogfeld fur Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstutzung

// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCPictureCtrlDemoDlg-Dialogfeld




CCPictureCtrlDemoDlg::CCPictureCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCPictureCtrlDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCPictureCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_PICTURE, m_picCtrl);
    DDX_Control(pDX, IDC_EDIT_RAW_W, CTRL_RAW_W);
    DDX_Control(pDX, IDC_EDIT_RAW_H, CTRL_RAW_H);
    DDX_Control(pDX, IDC_EDIT_RAW_BITS, CTRL_RAW_BITS);
    DDX_Control(pDX, IDC_EDIT_RAW_SHIFT_BITS, CTRL_RAW_SHIFT_BITS);
}

BEGIN_MESSAGE_MAP(CCPictureCtrlDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CCPictureCtrlDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCPictureCtrlDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCPictureCtrlDemoDlg::OnBnClickedButton3)
/*	ON_BN_CLICKED(IDC_BUTTON4, &CCPictureCtrlDemoDlg::OnBnClickedButton4)*/
ON_BN_CLICKED(IDC_BUTTON4, &CCPictureCtrlDemoDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CCPictureCtrlDemoDlg-Meldungshandler

BOOL CCPictureCtrlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Hinzufugen des Menubefehls "Info..." zum Systemmen?

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol fur dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Groses Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusatzliche Initialisierung einfugen
    CTRL_RAW_W.SetWindowText(_T("0"));
    CTRL_RAW_H.SetWindowText(_T("0"));;
    CTRL_RAW_BITS.SetWindowText(_T("8"));;
    CTRL_RAW_SHIFT_BITS.SetWindowText(_T("0"));;
	return TRUE;  // Geben Sie TRUE zuruck, auser ein Steuerelement soll den Fokus erhalten
}

void CCPictureCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Wenn Sie dem Dialogfeld eine Schaltflache "Minimieren" hinzufugen, benotigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Fur MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgefuhrt.

void CCPictureCtrlDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Geratekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, wahrend der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CCPictureCtrlDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCPictureCtrlDemoDlg::OnBnClickedButton1()
{
    CString filename; 
    filename = OpenFileDg(CString(BMP_FILTER));
	m_picCtrl.Load(filename, Windows_L_T);
}

void CCPictureCtrlDemoDlg::OnBnClickedButton2()
{
	//Load an Image from a Stream
    CString filename; 
    filename = OpenFileDg(CString(BMP_FILTER));
	
    
    //marky : edit bmp image
    EditBmpImage(filename);


    //Create the Stream
    m_picCtrl.Load(CString(BMP_TEMP),Windows_R_T);
    return;
}

void CCPictureCtrlDemoDlg::OnBnClickedButton3()
{
	//Load from a Byte Stream
    CString filename; 
    filename = OpenFileDg(CString(RAW_FILTER));
    //Load an Image from File
    //CTRL_RAW_W.SetWindowText( filename);

    //unsigned char *ImageData;
    //ImageData = (unsigned char *)malloc( 100*100 * sizeof(unsigned char)*2 );
    ShowRAWImage(filename, RAW_ORIG_TEMP);
    //if (ImageData != NULL) {
    //    free(ImageData);
    //}
	//Load the file ... Internet source ... etc.
    m_picCtrl.Load(CString(RAW_ORIG_TEMP),Windows_L_B);
    
    return;

}


void CCPictureCtrlDemoDlg::OnBnClickedButton4()
{
    // TODO: Add your control notification handler code here
	//Load from a Byte Stream
    CString filename; 
    filename = OpenFileDg(CString(RAW_FILTER));
    //Load an Image from File
    //CTRL_RAW_W.SetWindowText( filename);

    //unsigned char *ImageData;
    //ImageData = (unsigned char *)malloc( 100*100 * sizeof(unsigned char)*2 );
    
    //marky : edit raw image
    EditRAWImage(filename, RAW_EDIT_TEMP);
    //if (ImageData != NULL) {
    //    free(ImageData);
    //}
	//Load the file ... Internet source ... etc.
    m_picCtrl.Load(CString(RAW_EDIT_TEMP),Windows_R_B);
    return;

    
}

CString CCPictureCtrlDemoDlg::OpenFileDg(CString szFilter) {
    {
        CString filename("");       
        //CString szFilter;
        //szFilter = ;
        CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);
 

        if(dlg.DoModal() == IDOK)
        {
            filename = dlg.GetPathName(); // return full path and filename
        }
        return filename;
        
    }
}


void CCPictureCtrlDemoDlg::EditBmpImage(CString FileName) {
    //Load bmp image
    
    std::string stdFileName;
    stdFileName = CT2A(FileName.GetString());
    bitmap_image bmp_image(stdFileName);//(stdFileName);
    
    int W = bmp_image.width();
    int H= bmp_image.height();
    unsigned char PxielGreen, PxielRed, PxielBlue;
    

    for (int x = 0; x < W; ++x)
    {
        for (int y = 0; y < H; ++y)
        {
            bmp_image.get_pixel(x,y, PxielRed, PxielGreen, PxielBlue);
             
            //marky : edit BMP RGB here
            PxielRed /= 2;
            PxielGreen /= 2;
            PxielBlue /= 2;

            //update
            bmp_image.set_pixel(x,y,PxielRed,PxielGreen,PxielBlue);
        }
   }
   

    bmp_image.save_image(BMP_TEMP);

}


void CCPictureCtrlDemoDlg::ShowRAWImage(CString FileName, char* pChar) {
    //Load bmp image
    unsigned char PxielGreen, PxielRed, PxielBlue;
    std::string stdFileName;
    stdFileName = CT2A(FileName.GetString());
    CString sWindowTextW, sWindowTextH, sWindowTextBITS, sWindowTextBIT_SHIFT;
    int W = 0;//_ttoi(sWindowText);
    int H= 0;//atoi(CTRL_RAW_H.getWindowText());
    int RAW_BITS = 0;
    int RAW_BITS_SHIFT = 0;
    int raw_value=0;
    unsigned short *pBIT_16;
    unsigned char *pBIT_8, *ImageData=NULL;
    long ImageSize = 0;
    
    CTRL_RAW_W.GetWindowTextW(sWindowTextW);
    CTRL_RAW_H.GetWindowTextW(sWindowTextH);
    CTRL_RAW_BITS.GetWindowTextW(sWindowTextBITS);
    CTRL_RAW_SHIFT_BITS.GetWindowTextW(sWindowTextBIT_SHIFT);


    W = _wtoi(sWindowTextW);
    H = _wtoi(sWindowTextH);
    RAW_BITS = _wtoi(sWindowTextBITS);
    RAW_BITS_SHIFT = _wtoi(sWindowTextBIT_SHIFT);
    bitmap_image bmp_image(W,H);//bmp_image(stdFileName);//(stdFileName);
    
    ImageSize = W*H * sizeof(unsigned char);
    if (RAW_BITS >8)
        ImageSize = W*H * sizeof(unsigned char)*2;

    ImageData = (unsigned char *)malloc(ImageSize);
    //memset(ImageData,0xFF, W*H * sizeof(unsigned char)*2);  //for test

    //memcopy from file
    {
        FILE *fp;
        //char *sFileName =  FileName.GetBuffer();
        //fp=fopen(sFileName,"rb");
        fp=fopen(stdFileName.c_str(),"rb");
        if (ImageData != NULL && fp != NULL) {
             long FileSize = 0;
             fseek(fp,0L,SEEK_END);
             FileSize=ftell(fp);

             fseek(fp,0L,SEEK_SET);

             if (FileSize >= ImageSize) {
                 fread(ImageData, ImageSize, 1,fp);
             }
             else {
                 memset(ImageData,0xFF, ImageSize);  //for test
             }

             fclose(fp);
        }
    }

    


    //copy image from file
    pBIT_16 = ( unsigned short *)&ImageData[0];
    pBIT_8 = ( unsigned char *)&ImageData[0];


    

    for (int x = 0; x < W; ++x)
    {
        for (int y = 0; y < H; ++y)
        {
            //bmp_image.get_pixel(x,y, PxielRed, PxielGreen, PxielBlue);
             
            //edit R, G, B
            
            if (RAW_BITS >8) {
                raw_value = pBIT_16[y*W+x]>>RAW_BITS_SHIFT;
            }
            else {
                raw_value = pBIT_8[y*W+x]>>RAW_BITS_SHIFT;
            }
            
            PxielRed = raw_value;
            PxielGreen = raw_value;
            PxielBlue = raw_value;

            //update
            bmp_image.set_pixel(x,y,PxielRed,PxielGreen,PxielBlue);
        }
   }
   
    if (ImageData != NULL) {
        free(ImageData);
    }

    bmp_image.save_image(pChar);

}


void CCPictureCtrlDemoDlg::EditRAWImage(CString FileName, char* pChar) {
    //Load bmp image
    unsigned char PxielGreen, PxielRed, PxielBlue;
    std::string stdFileName;
    stdFileName = CT2A(FileName.GetString());
    CString sWindowTextW, sWindowTextH, sWindowTextBITS, sWindowTextBIT_SHIFT;
    int W = 0;//_ttoi(sWindowText);
    int H= 0;//atoi(CTRL_RAW_H.getWindowText());
    int RAW_BITS = 0;
    int RAW_BITS_SHIFT = 0;
    int raw_value=0;
    unsigned short *pBIT_16;
    unsigned char *pBIT_8, *ImageData=NULL;
    long ImageSize = 0;
    
    CTRL_RAW_W.GetWindowTextW(sWindowTextW);
    CTRL_RAW_H.GetWindowTextW(sWindowTextH);
    CTRL_RAW_BITS.GetWindowTextW(sWindowTextBITS);
    CTRL_RAW_SHIFT_BITS.GetWindowTextW(sWindowTextBIT_SHIFT);


    W = _wtoi(sWindowTextW);
    H = _wtoi(sWindowTextH);
    RAW_BITS = _wtoi(sWindowTextBITS);
    RAW_BITS_SHIFT = _wtoi(sWindowTextBIT_SHIFT);
    bitmap_image bmp_image(W,H);//bmp_image(stdFileName);//(stdFileName);
    
    ImageSize = W*H * sizeof(unsigned char);
    if (RAW_BITS >8)
        ImageSize = W*H * sizeof(unsigned char)*2;

    ImageData = (unsigned char *)malloc(ImageSize);
    //memset(ImageData,0xFF, W*H * sizeof(unsigned char)*2);  //for test

    //memcopy from file
    {
        FILE *fp;
        //char *sFileName =  FileName.GetBuffer();
        //fp=fopen(sFileName,"rb");
        fp=fopen(stdFileName.c_str(),"rb");
        if (ImageData != NULL && fp != NULL) {
             long FileSize = 0;
             fseek(fp,0L,SEEK_END);
             FileSize=ftell(fp);

             fseek(fp,0L,SEEK_SET);

             if (FileSize >= ImageSize) {
                 fread(ImageData, ImageSize, 1,fp);
             }
             else {
                 memset(ImageData,0xFF, ImageSize);  //for test
             }

             fclose(fp);
        }
    }

    


    //copy image from file
    pBIT_16 = ( unsigned short *)&ImageData[0];
    pBIT_8 = ( unsigned char *)&ImageData[0];


    

    for (int x = 0; x < W; ++x)
    {
        for (int y = 0; y < H; ++y)
        {
            //bmp_image.get_pixel(x,y, PxielRed, PxielGreen, PxielBlue);
             
            //edit R, G, B
            
            if (RAW_BITS >8) {
                //marky : edit raw here
                pBIT_16[y*W+x] += 50;
                raw_value = pBIT_16[y*W+x]>>RAW_BITS_SHIFT;
            }
            else {
                //marky : edit raw here
                pBIT_8[y*W+x] += 50;
                raw_value = pBIT_8[y*W+x]>>RAW_BITS_SHIFT;
            }
            
            //marky : edit raw here
            PxielRed = raw_value;
            PxielGreen = raw_value*1;
            PxielBlue = raw_value*2;

            //update
            bmp_image.set_pixel(x,y,PxielRed,PxielGreen,PxielBlue);
        }
   }
   
    if (ImageData != NULL) {
        free(ImageData);
    }

    bmp_image.save_image(pChar);

}