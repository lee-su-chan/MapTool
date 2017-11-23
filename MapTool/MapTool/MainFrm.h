
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "ToolEditView.h"
#include "FixedSplitterWnd.h"
#include "MakeNewFileDlg.h"

#include "MFC_Core.h"
#include "DirectX\ApplicationClass.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	ApplicationClass *m_application;

private:


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

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileNew();
};


