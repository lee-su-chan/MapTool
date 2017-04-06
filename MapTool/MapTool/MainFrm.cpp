
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MapTool.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//auto* pApp = AfxGetApp()->GetMainWnd();
	m_DXview.CreateDirectXWnd(lpCreateStruct, this->GetSafeHwnd(), m_wndSplitter.GetPane(0, 0)->GetSafeHwnd());

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cx = MAIN_WND_WIDTH;
	cs.cy = MAIN_WND_HEIGHT;
	cs.style &= ~(WS_MAXIMIZEBOX);	// Dialog size don't change.

	return TRUE;
}
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
	CRect rect;
	GetClientRect(&rect);

	//CSize size1(MulDiv(rect.Width(), 72, 100), GetSystemMetrics(SM_CYSCREEN)); // width(70%), 1280
	//CSize size2(MulDiv(rect.Width(), 28, 100), GetSystemMetrics(SM_CYSCREEN)); // width(30%),  320
	CSize size1(DIRECT_WND_WIDTH, DIRECT_WND_HEIGHT);
	CSize size2(MAIN_WND_WIDTH - DIRECT_WND_WIDTH, MAIN_WND_HEIGHT);

	// Create a splitter with 1 row, 2 colums
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to create static splitter \n");

		return FALSE;
	}

	// CFormView1 is left 
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CDirectXView), size1, pContext))
	{
		TRACE0("Failed to create CDirectXView pane \n");

		return FALSE;
	}
	// CFormView2 is right
	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CFormView2), size2, pContext))
	{
		TRACE0("Failed to create CFormView2 pane \n");

		return FALSE;
	}
	
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

