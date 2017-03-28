#pragma once



// CFormView1 form view

// MainFormView
class CFormView1 : public CFormView
{
	DECLARE_DYNCREATE(CFormView1)

protected:
	CFormView1();           // protected constructor used by dynamic creation
	virtual ~CFormView1();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW1 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
};


