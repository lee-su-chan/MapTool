#pragma once

#include "MyResource.h"
#include "DirectX\ApplicationClass.h"

// CDirectXView view

class CDirectXView : public CView
{
	DECLARE_DYNCREATE(CDirectXView)

public:
	CDirectXView();           // protected constructor used by dynamic creation
	virtual ~CDirectXView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

// Objects
private:
	ApplicationClass *m_application;

protected:
	DECLARE_MESSAGE_MAP()

public:
	bool CreateDirectXWnd(LPCREATESTRUCT, HWND, HWND);
	void Frame();
};


