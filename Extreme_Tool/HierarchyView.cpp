// HierarchyView.cpp : ���� �����Դϴ�.
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


// CHierarchyView �����Դϴ�.

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


// CHierarchyView �޽��� ó�����Դϴ�.


void CHierarchyView::Init()
{
	m_pHierarchyDlg->Init();
	m_pResDlg->Init();
}

int CHierarchyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CHierarchyView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	RECT rt = {};

	m_pHierarchyDlg->GetClientRect(&rt);

	m_pResDlg->SetWindowPos(NULL, 0, rt.bottom - rt.top, rt.right - rt.left, 600, 0);
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
