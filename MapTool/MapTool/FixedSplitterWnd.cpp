// FixedSplitterWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MapTool.h"
#include "FixedSplitterWnd.h"


// CFixedSplitterWnd

IMPLEMENT_DYNAMIC(CFixedSplitterWnd, CSplitterWnd)

CFixedSplitterWnd::CFixedSplitterWnd()
{

}

CFixedSplitterWnd::~CFixedSplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CFixedSplitterWnd, CSplitterWnd)
END_MESSAGE_MAP()


// CFixedSplitterWnd message handlers
int CFixedSplitterWnd::HitTest(CPoint point) const
{
	ASSERT_VALID(this);

	return HTNOWHERE;
}
