
// MFCApplication2View.cpp : implementation of the CMFCApplication2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2View

IMPLEMENT_DYNCREATE(CMFCApplication2View, CHtmlView)

BEGIN_MESSAGE_MAP(CMFCApplication2View, CHtmlView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CHtmlView::OnFilePrint)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplication2View construction/destruction

CMFCApplication2View::CMFCApplication2View()
{
	// TODO: add construction code here

}

CMFCApplication2View::~CMFCApplication2View()
{
}

BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

void CMFCApplication2View::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	Navigate2(_T("https://api.ciscospark.com/v1/authorize?client_id=Ce07a320a3e5fd132ac55854ef107e48988fb573b0478c4126df9f01d941a3ec3&response_type=code&redirect_uri=http%3A%2F%2F127.0.0.1.com&scope=spark%3Amessages_write%20spark%3Arooms_read%20spark%3Amemberships_read%20spark%3Amessages_read%20spark%3Arooms_write%20spark%3Apeople_read%20spark%3Amemberships_write&state=set_state_here"),NULL,NULL);
}

void CMFCApplication2View::OnDocumentComplete(LPCTSTR lpszURL)
{
	CHtmlView::OnDocumentComplete(lpszURL);
	if (lpszURL != nullptr) {
		CString strURL(lpszURL);
		static int i = 0;
		if (strURL.Find(_T("127.0.0.1.com/?code=")) > 0 && i == 0)
		{
			CString strCode = strURL.Mid(strURL.Find(_T("127.0.0.1.com/?code="))+20);
			CString strNewURL(_T("https://api.ciscospark.com/v1/access_token"));
			CString strPostData(_T("grant_type=authorization_code&client_id=Ce07a320a3e5fd132ac55854ef107e48988fb573b0478c4126df9f01d941a3ec3&client_secret=ec699f8e1f970a7b4e76b06ca226e1d5e3a5c40ee509cacbda2f6d1da7662b67&redirect_uri=http%3A%2F%2F127.0.0.1.com&code="));
			strPostData.Append(strCode);
			Navigate2(strNewURL, NULL, NULL, NULL, (LPVOID)(LPCTSTR)strPostData, (DWORD)strPostData.GetLength());
			i++;
		}

		
		if (i == 1) {
			LPDISPATCH   lpDispatch;
			lpDispatch = GetHtmlDocument();
			ASSERT(lpDispatch);
			CComQIPtr <IHTMLDocument2, &IID_IHTMLDocument2>   pDoc2;
			HRESULT   hr;
			hr = lpDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&pDoc2);
			if (SUCCEEDED(hr))
			{
				IHTMLElement   *pBodyElement;
				pDoc2->get_body(&pBodyElement);
				BSTR   body;
				pBodyElement->get_innerHTML(&body);
				char * strBody = ::_com_util::ConvertBSTRToString(body);
				pDoc2.Release();
			}
			lpDispatch->Release();
		}
	}
}
// CMFCApplication2View printing


void CMFCApplication2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}


void CMFCApplication2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication2View diagnostics

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication2View message handlers
