// HierarchyView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "HierarchyView.h"

#include "HierarchyDlg.h"
#include "ResDlg.h"
// CHierarchyView

IMPLEMENT_DYNCREATE(CHierarchyView, CFormView)

CHierarchyView::CHierarchyView()
	: CFormView(IDD_HIERARCHYVIEW)
	, m_pHierarchyDlg(NULL)
	, m_pResDlg(NULL)
{

}

CHierarchyView::~CHierarchyView()
{
}

void CHierarchyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHierarchyView, CFormView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CHierarchyView 진단입니다.

#ifdef _DEBUG
void CHierarchyView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CHierarchyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHierarchyView 메시지 처리기입니다.


void CHierarchyView::Init()
{
	m_pHierarchyDlg->Init();
	m_pResDlg->Init();
}

int CHierarchyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_pHierarchyDlg = new CHierarchyDlg();
	m_pHierarchyDlg->Create(IDD_HIERARCHYDLG, this);
	m_pHierarchyDlg->ShowWindow(true);
	m_pHierarchyDlg->UpdateWindow();

	m_pResDlg = new CResDlg();
	m_pResDlg->Create(IDD_RESDLG, this);
	m_pResDlg->ShowWindow(true);
	m_pResDlg->UpdateWindow();

	return 0;
}


void CHierarchyView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CHierarchyView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	RECT rt = {};

	m_pHierarchyDlg->GetClientRect(&rt);

	m_pResDlg->SetWindowPos(NULL, 0, rt.bottom - rt.top, rt.right - rt.left, 600, 0);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
