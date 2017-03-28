#pragma once


// CFixedSplitterWnd

class CFixedSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CFixedSplitterWnd)

public:
	CFixedSplitterWnd();
	virtual ~CFixedSplitterWnd();

protected:
	DECLARE_MESSAGE_MAP()

	// Don't Move Border
	virtual int HitTest(CPoint point) const;
};


