// MakeNewFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapTool.h"
#include "MakeNewFileDlg.h"
#include "afxdialogex.h"

#include "MFC_Core.h"

#pragma warning(disable:4996)

// CMakeNewFileDlg dialog

IMPLEMENT_DYNAMIC(CMakeNewFileDlg, CDialog)

CMakeNewFileDlg::CMakeNewFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAKENEWFILEDLG, pParent)
	, m_CellSize(0)
	, m_TileSize(0)
	, m_TextureSize(0)
	, m_IsClickedCancel(false)
{

}

CMakeNewFileDlg::~CMakeNewFileDlg()
{
}

void CMakeNewFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_TextureComboBox);
	DDX_Radio(pDX, IDC_RADIO3, m_CellSize);
	DDX_Radio(pDX, IDC_RADIO8, m_TileSize);
}


BEGIN_MESSAGE_MAP(CMakeNewFileDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CMakeNewFileDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMakeNewFileDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CMakeNewFileDlg message handlers

void CMakeNewFileDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (m_TextureComboBox.GetCurSel() == -1)
	{
		AfxMessageBox(TEXT("텍스쳐를 선택해주십시오."));

		return;
	}

	CDialog::OnOK();
}

void CMakeNewFileDlg::InitTextureComboBox()
{
	POSITION pos;
	
	for (pos = fileNameList.GetHeadPosition(); pos != NULL; fileNameList.GetNext(pos))
	{
		m_TextureComboBox.AddString(fileNameList.GetAt(pos));
		++m_TextureSize;
	}
}

std::string CMakeNewFileDlg::CStringToString(CString cStr)
{
	CT2CA pszConvertedAnsiString(cStr);
	std::string str(pszConvertedAnsiString);

	return str;
}


void CMakeNewFileDlg::OnCbnSelchangeCombo2()
{
	UpdateData(TRUE);
	if(!m_IconImage->IsNull())
		m_IconImage->Detach();

	//CDC *dc = this->GetDC();
	//std::string fullPath = "Data/Textures/";
	//CString iconName;
	//const int x = 90;
	//const int y = 180;
	//const int width = 110;
	//const int height = 110;
	//int error;
	//int count;
	//FILE *filePtr;
	//TargaHeader targaFileHeader;
	
	//m_TextureComboBox.GetLBText(m_TextureComboBox.GetCurSel(), iconName);
	//CT2CA pszConvertedAnsiString(iconName);
	//fullPath += pszConvertedAnsiString;

	//error = fopen_s(&filePtr, fullPath.c_str(), "rb");
	//if (error != 0)
	//	return;

	//count = (unsigned int)fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
	//if (count != 1)
	//	return;

	//---------------------------------------------------------------------------
	CDC *dc = this->GetDC();
	CString fullPath = _T("Data/Textures/");
	CString iconName = _T("");
	const int x = 90;
	const int y = 180;
	const int width = 110;
	const int height = 110;
	
	m_TextureComboBox.GetLBText(m_TextureComboBox.GetCurSel(), iconName);
	fullPath += iconName;
	m_IconImage->Load(fullPath);
	dc->SetStretchBltMode(COLORONCOLOR);
	m_IconImage->StretchBlt(dc->m_hDC, CRect(x, y, x + width, y + height), SRCCOPY);
	//---------------------------------------------------------------------------

	m_CurSel = m_TextureComboBox.GetCurSel();
}


BOOL CMakeNewFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	int i;
	int nTexture = 0;
	CString path = _T("Data\\Textures\\*.*");
	CString fileName;
	CFileFind finder;
	
	textureNames = new std::vector<std::string>();
	m_IconImage = new CImage;

	//CFileFind는 파일, 디렉터리가 존재하면 TRUE 를 반환함 
	BOOL isWorking = finder.FindFile(path);
	while (isWorking)
	{
		//다음 파일/폴더가 존재하다면 TRUE 반환
		isWorking = finder.FindNextFile();

		//파일 일때
		if (finder.IsArchived())
		{
			fileName = finder.GetFileName();
			fileNameList.AddTail(fileName);
			textureNames->push_back(CStringToString(fileName));
		}
	}
	
	InitTextureComboBox();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

bool CMakeNewFileDlg::InitTextures(ID3D11Device *device, ID3D11DeviceContext *deviceContext)
{
	bool result;
	int i;

	m_TextureManager = new TextureManagerClass;
	if (!m_TextureManager)
		return false;

	result = m_TextureManager->Initialize(textureNames->size());
	if (!result)
	{
		AfxMessageBox(_T("Could not initialize TextureManagerClass object."));
		return false;
	}

	for (i = 0; i < textureNames->size(); ++i)
	{
		result = m_TextureManager->LoadTexture(device,
			deviceContext,
			"Data/Textures/",
			(char *)textureNames->at(i).data(),
			i);
		if (!result)
			return false;
	}
}

int CMakeNewFileDlg::GetCellSize() const
{
	switch (m_CellSize)
	{
		case 0: return 4;
		case 1: return 8;
		case 2: return 16;
		case 3: return 32;
		case 4: return 64;
		default: AfxMessageBox(_T("GetCellSize() Error!")); return 0;
	}
}
int CMakeNewFileDlg::GetTileSize() const
{
	switch (m_TileSize)
	{
		case 0: return 4;
		case 1: return 8;
		case 2: return 16;
		case 3: return 32;
		case 4: return 64;
		default: AfxMessageBox(_T("GetTileSize() Error!")); return 0;
	}
}

void CMakeNewFileDlg::OnCancel()
{
	m_IsClickedCancel = true;

	CDialog::OnCancel();
}