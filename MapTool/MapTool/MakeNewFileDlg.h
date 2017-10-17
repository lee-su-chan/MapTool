#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include <vector>

#include "DirectX\TextureManagerClass.h"

using namespace DirectX;

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
	void InitTextureComboBox();
	std::string CStringToString(CString cStr);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	struct TargaHeader
	{
		BYTE data1[12];
		WORD width;
		WORD height;
		BYTE bpp;
		BYTE data2;
	};
	//struct TargaHeader
	//{
 //   BYTE  identsize;          // size of ID field that follows 18 BYTE header (0 usually)
 //   BYTE  colourmaptype;      // type of colour map 0=none, 1=has palette
 //   BYTE  imagetype;          // type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed

 //   WORD colourmapstart;     // first colour map entry in palette
 //   WORD colourmaplength;    // number of colours in palette
 //   BYTE  colourmapbits;      // number of bits per palette entry 15,16,24,32

 //   WORD xstart;             // image x origin
 //   WORD ystart;             // image y origin
 //   WORD width;              // image width in pixels
 //   WORD height;             // image height in pixels
 //   BYTE  bits;               // image bits per pixel 8,16,24,32
 //   BYTE  descriptor;
	//};
	
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo2();
	virtual void OnCancel();

public:
	bool InitTextures(ID3D11Device *, ID3D11DeviceContext *);

public:
	int GetCellSize() const;
	int GetTileSize() const;
	int GetTextureSize() const { return this->m_TextureSize; }
	int GetCurSel() const { return this->m_CurSel; }
	bool GetIsClickedCancel() const { return this->m_IsClickedCancel; }
	std::vector<std::string> *GetTextureNameVector() const { return this->textureNames; }

private:
	int m_CellSize;
	int m_TileSize;
	int m_TextureSize;
	int m_CurSel;
	bool m_IsClickedCancel;

	CStringList fileNameList;
	std::vector<std::string> *textureNames;

	CComboBox m_TextureComboBox;
	CImage *m_IconImage;

	TextureManagerClass *m_TextureManager;
};
