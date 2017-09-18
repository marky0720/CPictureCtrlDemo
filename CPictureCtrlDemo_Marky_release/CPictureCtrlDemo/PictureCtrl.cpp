///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////
// PictureCtrl.cpp
// 
// Author: Tobias Eiseler
//
// E-Mail: tobias.eiseler@sisternicky.com
// 
// Function: A MFC Picture Control to display
//           an image on a Dialog, etc.
///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "PictureCtrl.h"
#include <GdiPlus.h>
using namespace Gdiplus;

//Macro to release COM Components



#ifdef SAFE_RELEASE
#undef SAFE_RELEASE
#endif
#define SAFE_RELEASE(x) do{\
							if((x) != NULL)\
							{\
								while((x)->Release() != 0);\
								(x) = NULL;\
							}\
						}while(0)

CPictureCtrl::CPictureCtrl(void)
	:CStatic()
	, m_pStream(NULL)
	, m_bIsPicLoaded(FALSE)
	, m_gdiplusToken(0)
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
}

CPictureCtrl::~CPictureCtrl(void)
{
	//Tidy up
	FreeData();
	GdiplusShutdown(m_gdiplusToken);
}

BOOL CPictureCtrl::LoadFromStream(IStream *piStream)
{
	//Set success error state
	SetLastError(ERROR_SUCCESS);

	FreeData();

	//Check for validity of argument
	if(piStream == NULL)
	{
		SetLastError(ERROR_INVALID_ADDRESS);
		return FALSE;
	}

	//Allocate stream
	DWORD dwResult = CreateStreamOnHGlobal(NULL, TRUE, &m_pStream);
	if(dwResult != S_OK)
	{
		SetLastError(dwResult);
		return FALSE;
	}

	//Rewind the argument stream
	LARGE_INTEGER lInt;
	lInt.QuadPart = 0;
	piStream->Seek(lInt, STREAM_SEEK_SET, NULL);

	//Read the lenght of the argument stream
	STATSTG statSTG;
	dwResult = piStream->Stat(&statSTG, STATFLAG_DEFAULT);
	if(dwResult != S_OK)
	{
		SetLastError(dwResult);
		SAFE_RELEASE(m_pStream);
		return FALSE;
	}

	//Copy the argument stream to the class stream
	piStream->CopyTo(m_pStream, statSTG.cbSize, NULL, NULL);

	//Mark as loaded
	m_bIsPicLoaded = TRUE;

	Invalidate();
	RedrawWindow();

	return TRUE;
}

BOOL CPictureCtrl::LoadFromStream(BYTE* pData, size_t nSize)
{
	//Set success error state
	SetLastError(ERROR_SUCCESS);
	FreeData();

	//Allocate stream
	DWORD dwResult = CreateStreamOnHGlobal(NULL, TRUE, &m_pStream);
	if(dwResult != S_OK)
	{
		SetLastError(dwResult);
		return FALSE;
	}

	//Copy argument data to the stream
	dwResult = m_pStream->Write(pData, (ULONG)nSize, NULL);
	if(dwResult != S_OK)
	{
		SetLastError(dwResult);
		SAFE_RELEASE(m_pStream);
		return FALSE;
	}

	//Mark as loaded
	m_bIsPicLoaded = TRUE;

	Invalidate();
	RedrawWindow();

	return TRUE;
}

BOOL CPictureCtrl::LoadFromFile(CString &szFilePath)
{
	//Set success error state
	SetLastError(ERROR_SUCCESS);
	FreeData();

	//Allocate stream
	DWORD dwResult = CreateStreamOnHGlobal(NULL, TRUE, &m_pStream);
	if(dwResult != S_OK)
	{
		SetLastError(dwResult);
		return FALSE;
	}

	//Open the specified file
	CFile cFile;
	CFileException cFileException;
	if(!cFile.Open(szFilePath, CStdioFile::modeRead | CStdioFile::typeBinary, &cFileException))
	{
		SetLastError(cFileException.m_lOsError);
		SAFE_RELEASE(m_pStream);
		return FALSE;
	}

	//Copy the specified file's content to the stream
	BYTE pBuffer[1024] = {0};
	while(UINT dwRead = cFile.Read(pBuffer, 1024))
	{
		dwResult = m_pStream->Write(pBuffer, dwRead, NULL);
		if(dwResult != S_OK)
		{
			SetLastError(dwResult);
			SAFE_RELEASE(m_pStream);
			cFile.Close();
			return FALSE;
		}
	}

	//Close the file
	cFile.Close();

	//Mark as Loaded
	m_bIsPicLoaded = TRUE;

	Invalidate();
	RedrawWindow();

	return TRUE;
}

// BOOL CPictureCtrl::LoadFromResource(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType)
// {
// 	//Set success error state
// 	SetLastError(ERROR_SUCCESS);
// 	FreeData();
// 
// 	//Locate the resource
// 	HRSRC hResource = FindResource(hModule, lpName, lpType);
// 	if(hResource == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	//Get the size of the resource
// 	DWORD dwResourceSize = SizeofResource(hModule, hResource);
// 	if(dwResourceSize == 0)
// 	{
// 		return FALSE;
// 	}
// 
// 	//Load the Resource
// 	HGLOBAL hGlobalResource = LoadResource(hModule, hResource);
// 	if(hGlobalResource == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	//Lock the resource and get the read pointer
// 	BYTE* pRecource = (BYTE*)LockResource(hGlobalResource);
// 	if(pRecource == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	//Allocate the Stream
// 	DWORD dwResult =  CreateStreamOnHGlobal(NULL, TRUE, &m_pStream);
// 	if(dwResult != S_OK)
// 	{
// 		FreeResource(hGlobalResource);
// 		SetLastError(dwResult);
// 		pRecource = NULL;
// 		return FALSE;
// 	}
// 
// 	//Copy the resource data to the stream
// 	dwResult = m_pStream->Write(pRecource, dwResourceSize, NULL);
// 	if(dwResult != S_OK)
// 	{
// 		FreeResource(hGlobalResource);
// 		SAFE_RELEASE(m_pStream);
// 		SetLastError(dwResult);
// 		return FALSE;		
// 	}
// 
// 	//Tidy up
// //	FreeResource(hGlobalResource);
// 	
// 	//Mark as loaded
// 	m_bIsPicLoaded = TRUE;
// 
// 	Invalidate();
// 	RedrawWindow();
// 
// 	return TRUE;
// }

//Overload - Single load function
BOOL CPictureCtrl::Load(CString &szFilePath, int IsLeftWindows)
{
	this->WindowsLocal = IsLeftWindows;
    return LoadFromFile(szFilePath);
}

BOOL CPictureCtrl::Load(IStream* piStream)
{
	return LoadFromStream(piStream);
}

BOOL CPictureCtrl::Load(BYTE* pData, size_t nSize)
{
	return LoadFromStream(pData, nSize);
}

// BOOL CPictureCtrl::Load(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType)
// {
// 	return LoadFromResource(hModule, lpName, lpType);
// }

void CPictureCtrl::FreeData()
{
	m_bIsPicLoaded = FALSE;
	SAFE_RELEASE(m_pStream);
}

void CPictureCtrl::PreSubclassWindow()
{
	CStatic::PreSubclassWindow();
	ModifyStyle(0, SS_OWNERDRAW);
}

void CPictureCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//Check if pic data is loaded
	if(m_bIsPicLoaded)
	{

		//Get control measures
		RECT rc;
        int left, top, width, height;
        int pic_width, pic_height;
		this->GetClientRect(&rc);

		Graphics graphics(lpDrawItemStruct->hDC);
		Image image(m_pStream);
        GetWindowLocal(&left, &top, &width,&height, rc);
        //add by marky
        pic_width = image.GetWidth();
        pic_height = image.GetHeight();
        if (pic_width > pic_height) {
             height = width * pic_height / pic_width;
        }
        else {
            width = height *  pic_width / pic_height;
        }
		graphics.DrawImage(&image,left, top, width, height);		
	}
}

BOOL CPictureCtrl::OnEraseBkgnd(CDC *pDC)
{
	if(m_bIsPicLoaded)
	{

		//Get control measures
		RECT rc;
        int left, top, width, height;
                int pic_width, pic_height;
		this->GetClientRect(&rc);

		Graphics graphics(pDC->GetSafeHdc());
		LARGE_INTEGER liSeekPos;
		liSeekPos.QuadPart = 0;
		m_pStream->Seek(liSeekPos, STREAM_SEEK_SET, NULL);
		Image image(m_pStream);
        GetWindowLocal(&left, &top, &width,&height,rc);
        //add by marky
        pic_width = image.GetWidth();
        pic_height = image.GetHeight();
        if (pic_width > pic_height) {
             height = width * pic_height / pic_width;
        }
        else {
            width = height *  pic_width / pic_height;
        }
		graphics.DrawImage(&image,left, top, width, height);
		return TRUE;
	}
	else
	{
		return CStatic::OnEraseBkgnd(pDC);
	}
}

//mod by marky
void CPictureCtrl::GetWindowLocal(int *pleft, int *ptop, int *pwidth,int *pheight, RECT rc) {
    
    if (Windows_L_T == this->WindowsLocal) {
            *pleft = rc.left; 
            *ptop = rc.top;

    }
    else if (Windows_R_T == this->WindowsLocal) {
            *pleft = (rc.right+rc.left)/2; 
             *ptop =  rc.top;
    }
    else if (Windows_L_B == this->WindowsLocal){
            *pleft = rc.left; 
             *ptop =  (rc.bottom+rc.top)/2;

    }
    else if (Windows_R_B == this->WindowsLocal) {
            *pleft = (rc.right+rc.left)/2; 
             *ptop =  (rc.bottom+rc.top)/2;

    }
    *pwidth = (rc.right-rc.left)/2;
    *pheight = (rc.bottom-rc.top)/2;
    

    /*
        if(this->IsLeftWindows) {
            left = rc.left; 
            top = rc.top;
            width = (rc.right-rc.left)/2;
            height = (rc.bottom-rc.top)/2;
        }
        else {
            left = (rc.right+rc.left)/2; 
            top =  (rc.bottom+rc.top)/2;
            width = (rc.right-rc.left)/2;
            height = (rc.bottom-rc.top)/2;
        }
     */
}