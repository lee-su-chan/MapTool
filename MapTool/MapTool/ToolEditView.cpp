// ToolEditView.cpp : implementation file
//

#include "stdafx.h"
#include "MapTool.h"
#include "ToolEditView.h"
#include "Manager\EditInputManager.h"
#include "DirectX\D3D_Core.h"

// CToolEditView

IMPLEMENT_DYNCREATE(CToolEditView, CFormView)

CToolEditView::CToolEditView()
	: CFormView(IDD_TOOLEDITVIEW)
	, m_BrushRadiusText(_T("1"))
{
	EditInputManager::GetInstance()->m_TerrainEditType = TerrainEditType::UP;
	EditInputManager::GetInstance()->m_BrushType = BrushType::CIRCLE;
}

CToolEditView::~CToolEditView()
{
}

void CToolEditView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC1, m_BrushRadiusText);
	DDX_Control(pDX, IDC_SLIDER1, m_BrushRadiusSlider);
	DDX_Control(pDX, IDC_RADIO1, m_BrushTypeRadio);

	InitVariables();
}

BEGIN_MESSAGE_MAP(CToolEditView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON6, &CToolEditView::OnBnClickedUpButton)
	ON_BN_CLICKED(IDC_BUTTON8, &CToolEditView::OnBnClickedDownButton)
	ON_BN_CLICKED(IDC_BUTTON7, &CToolEditView::OnBnClickedOriginButton)
	ON_BN_CLICKED(IDC_BUTTON9, &CToolEditView::OnBnClickedFlatButton)
	ON_BN_CLICKED(IDC_RADIO1, &CToolEditView::OnBnClickedCircleRadio)
	ON_BN_CLICKED(IDC_RADIO2, &CToolEditView::OnBnClickedRectangleRadio)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CToolEditView::OnNMCustomdrawBrushRadiusSlider)
END_MESSAGE_MAP()


// CToolEditView diagnostics

#ifdef _DEBUG
void CToolEditView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CToolEditView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CToolEditView message handlers
void CToolEditView::InitVariables()
{
	m_BrushRadiusSlider.SetRange(1, 10);
	m_BrushTypeRadio.SetCheck(1);
}

#pragma region TerrainEdit
void CToolEditView::OnBnClickedUpButton()
{
	EditInputManager::GetInstance()->m_TerrainEditType = TerrainEditType::UP;
}
void CToolEditView::OnBnClickedDownButton()
{
	EditInputManager::GetInstance()->m_TerrainEditType = TerrainEditType::DOWN;
}
void CToolEditView::OnBnClickedOriginButton()
{
	EditInputManager::GetInstance()->m_TerrainEditType = TerrainEditType::ORIGIN;
}
void CToolEditView::OnBnClickedFlatButton()
{
	EditInputManager::GetInstance()->m_TerrainEditType = TerrainEditType::FLAT;
}
#pragma endregion

#pragma region Brush
void CToolEditView::OnBnClickedCircleRadio()
{
	EditInputManager::GetInstance()->m_BrushType = BrushType::CIRCLE;
}
void CToolEditView::OnBnClickedRectangleRadio()
{
	EditInputManager::GetInstance()->m_BrushType = BrushType::RECTANGLE;
}

void CToolEditView::OnNMCustomdrawBrushRadiusSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);

	int radius = m_BrushRadiusSlider.GetPos();

	m_BrushRadiusText.Format(_T("%d"), radius);
	EditInputManager::GetInstance()->m_BrushRadius = radius;

	UpdateData(FALSE);
}
#pragma endregion