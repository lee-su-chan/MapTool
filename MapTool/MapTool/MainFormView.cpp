// FormView1.cpp : implementation file
//

#include "stdafx.h"
#include "MapTool.h"
#include "MainFormView.h"


// CFormView1

IMPLEMENT_DYNCREATE(CFormView1, CFormView)

CFormView1::CFormView1()
	: CFormView(IDD_FORMVIEW1)
{

}

CFormView1::~CFormView1()
{
}

void CFormView1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormView1, CFormView)
//	ON_WM_CREATE()
ON_WM_SIZING()
END_MESSAGE_MAP()


// CFormView1 diagnostics

#ifdef _DEBUG
void CFormView1::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormView1::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormView1 message handlers