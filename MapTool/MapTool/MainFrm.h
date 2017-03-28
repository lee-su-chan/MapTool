
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "Directx\GraphicsClass.h"
#include "MainFormView.h"
#include "FormView2.h"
#include "FixedSplitterWnd.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	GraphicsClass	*m_graphics;

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar			m_wndToolBar;
	CStatusBar			m_wndStatusBar;
	CFixedSplitterWnd	m_wndSplitter;
	CView				*m_pFormView1;
	CView				*m_pFormView2;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};


