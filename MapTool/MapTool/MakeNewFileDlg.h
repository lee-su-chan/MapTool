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

private:
	CStringList fileNameList;
	int m_CellSize;
	int m_TileSize;

public:
	CComboBox m_TextureComboBox;
	CString m_IconName;
	
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo2();

	int GetCellSize();
	int GetTileSize();
};
