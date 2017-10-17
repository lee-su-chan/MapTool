#pragma once

// CToolEditView form view

class CToolEditView : public CFormView
{
	DECLARE_DYNCREATE(CToolEditView)

protected:
	CToolEditView();           // protected constructor used by dynamic creation
	virtual ~CToolEditView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLEDITVIEW };
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

private:
	void InitVariables();

public:
#pragma region TerrainEdit
	afx_msg void OnBnClickedUpButton();
	afx_msg void OnBnClickedDownButton();
	afx_msg void OnBnClickedOriginButton();
	afx_msg void OnBnClickedFlatButton();
#pragma endregion

#pragma region Brush
	afx_msg void OnBnClickedCircleRadio();
	afx_msg void OnBnClickedRectangleRadio();
	afx_msg void OnNMCustomdrawBrushRadiusSlider(NMHDR *pNMHDR, LRESULT *pResult);

	CButton m_BrushTypeRadio;
	CString m_BrushRadiusText;
	CSliderCtrl m_BrushRadiusSlider;
#pragma endregion
};