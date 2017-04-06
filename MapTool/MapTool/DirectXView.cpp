// DirectXView.cpp : implementation file
//

#include "stdafx.h"
#include "MapTool.h"
#include "DirectXView.h"


// CDirectXView

IMPLEMENT_DYNCREATE(CDirectXView, CView)

CDirectXView::CDirectXView()
{
	m_application = NULL;
}

CDirectXView::~CDirectXView()
{
	if (m_application)
	{
		m_application->Shutdown();
		delete m_application;
		m_application = NULL;
	}
}

BEGIN_MESSAGE_MAP(CDirectXView, CView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CDirectXView drawing

void CDirectXView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

}


// CDirectXView diagnostics

#ifdef _DEBUG
void CDirectXView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CDirectXView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDirectXView message handlers


bool CDirectXView::CreateDirectXWnd(LPCREATESTRUCT lpCreateStruct, HWND mainFrmHwnd, HWND directXViewHwnd)
{
	bool result;
	HWND hwndArray[2];

	hwndArray[0] = directXViewHwnd;
	hwndArray[1] = mainFrmHwnd;

	m_application = new ApplicationClass;
	result = m_application->Initialize(lpCreateStruct->hInstance,
		hwndArray,
		DIRECT_WND_WIDTH,
		DIRECT_WND_HEIGHT);

	if (!result)
	{
		MessageBoxA(lpCreateStruct->hwndParent, "Could not initialize the application object.", "Error", MB_OK);

		return false;
	}

	return true;
}
void CDirectXView::Frame()
{
	m_application->Frame();
}