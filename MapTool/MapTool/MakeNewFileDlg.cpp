// MakeNewFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapTool.h"
#include "MakeNewFileDlg.h"
#include "afxdialogex.h"


// CMakeNewFileDlg dialog

IMPLEMENT_DYNAMIC(CMakeNewFileDlg, CDialog)

CMakeNewFileDlg::CMakeNewFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAKENEWFILEDLG, pParent)
	, m_CellSize(0)
	, m_TileSize(0)
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
void CMakeNewFileDlg::SetTextureComboBox()
{
	POSITION pos;
	int i;

	for (i = 0, pos = fileNameList.GetHeadPosition(); pos != NULL; fileNameList.GetNext(pos), ++i)
	{
		m_TextureComboBox.AddString(fileNameList.GetAt(pos));
	}
}

BOOL CMakeNewFileDlg::CastImageType(LPCTSTR InSourceImageFileName, 
	LPCTSTR InDestImageFileName, 
	const CRect& InTagetRect, 
	REFGUID InImageFormat)
{
	CImage TempSourceImage;
	CImage TempDestImage;
	
	CRect TempTargetRect = InTagetRect;

	// 1. 원본 이미지를 TempSourceImage에 로딩
	TempSourceImage.Load(InSourceImageFileName);
	CDC *pSourceDC = CDC::FromHandle(TempSourceImage.GetDC());

	// 2. 파일로 만들 이미지 객체 TempDestImage 생성
	int BitPerPixel = pSourceDC->GetDeviceCaps(BITSPIXEL);
	TempDestImage.Create(TempTargetRect.Width(), TempTargetRect.Height(), BitPerPixel);
	CDC *pDestDC = CDC::FromHandle(TempDestImage.GetDC());

	if (!pSourceDC || !pDestDC)
		return FALSE;

	// 3. 타겟 DC에 원본 이미지 DC의 내용을 쓴다.
	pDestDC->BitBlt(0, 0,
		TempTargetRect.Width(),
		TempTargetRect.Height(),
		pSourceDC,
		TempTargetRect.left,
		TempTargetRect.top,
		SRCCOPY);

	TempDestImage.ReleaseDC();
	TempSourceImage.ReleaseDC();

	TempDestImage.Save(InDestImageFileName, InImageFormat);
	
	return TRUE;
}

void CMakeNewFileDlg::OnCbnSelchangeCombo2()
{
	UpdateData(TRUE);

	CImage image;
	CDC *dc;
	CString pathAndNewm_IconName;
	CString strPath = _T("Data/Textures/");
	int x = 70;
	int y = 165;
	int width = 90;
	int height = 90;

	m_TextureComboBox.GetLBText(m_TextureComboBox.GetCurSel(), m_IconName);

	dc = this->GetDC();

	image.Load(strPath + m_IconName);
	//image.Draw(dc->m_hDC, x, y, image.GetWidth(), image.GetHeight());
	image.StretchBlt(dc->m_hDC, CRect(x, y, x + width, y + height), SRCCOPY);
}


BOOL CMakeNewFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//폴더나 파일의 목록을 가져올 디렉터리의 풀 패스
	CString path = _T("Data\\Textures\\*.*");
	CFileFind finder;

	//CFileFind는 파일, 디렉터리가 존재하면 TRUE 를 반환함 
	BOOL bWorking = finder.FindFile(path);

	CString fileName;
	CString DirName;

	while (bWorking)
	{
		//다음 파일/폴더가 존재하다면 TRUE 반환
		bWorking = finder.FindNextFile();

		//파일 일때
		if (finder.IsArchived())
		{
			//작업
			//파일의 이름
			fileName = finder.GetFileName();
			fileNameList.AddTail(fileName);
		}
	}

	SetTextureComboBox();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

int CMakeNewFileDlg::GetCellSize()
{
	switch (m_CellSize)
	{
	case 0: return 4;
	case 1: return 8;
	case 2: return 16;
	case 3: return 32;
	case 4: return 64;
	default: 
		AfxMessageBox(_T("GetCellSize() Error!"));
		return 0;
	}
}
int CMakeNewFileDlg::GetTileSize()
{
	switch (m_TileSize)
	{
	case 0: return 4;
	case 1: return 8;
	case 2: return 16;
	case 3: return 32;
	case 4: return 64;
	default:
		AfxMessageBox(_T("GetTileSize() Error!"));
		return 0;
	}
}
