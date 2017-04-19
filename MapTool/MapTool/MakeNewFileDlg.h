#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMakeNewFileDlg dialog

class CMakeNewFileDlg : public CDialog
{
	DECLARE_DYNAMIC(CMakeNewFileDlg)

public:
	CMakeNewFileDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMakeNewFileDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAKENEWFILEDLG };
#endif
private:
	void SetTextureComboBox();
	BOOL CastImageType(LPCTSTR InSourceImageFileName, LPCTSTR InDestImageFileName, const CRect& InTagetRect, REFGUID InImageFormatToMake);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CStringList fileNameList;

public:
	afx_msg void OnEnChangeEditWidth();
	afx_msg void OnEnChangeEditHeight();
	int m_width;
	int m_height;
	afx_msg void OnBnClickedOk();
	CStatic m_TextureIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox m_TextureComboBox;
};
