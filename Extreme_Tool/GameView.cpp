// GameView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "GameView.h"

#include "Scene.h"
#include "SceneMgr.h"
#include "GameObject.h"

#include "MainFrm.h"
#include "ComponentView.h"

#include "DebugMgr.h"
#include "DebugView.h"

// CGameView

IMPLEMENT_DYNCREATE(CGameView, CFormView)

CGameView::CGameView()
	: CFormView(IDD_GAMEVIEW)
{

}

CGameView::~CGameView()
{
}

LRESULT CGameView::ReceiveLog(WPARAM _lparam, LPARAM)
{
	wchar_t* pLog = (wchar_t*)_lparam;
	
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CDebugView* pDebugView = (CDebugView*)pMainFrm->GetDebugView();

	pDebugView->AddLog(_lparam);

	return LRESULT();
}

void CGameView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameView, CFormView)
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(MM_LOG, ReceiveLog)
END_MESSAGE_MAP()


// CGameView �����Դϴ�.

#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGameView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGameView �޽��� ó�����Դϴ�.


BOOL CGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CFormView::PreCreateWindow(cs);
}


void CGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	/*
	RECT rt = {};
	GetWindowRect(&rt);

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CGameObject* pObj = pCurScene->FindObject(Vec2((float)point.x, (float)point.y)
		, Vec2((float)(rt.right - rt.left), (float)(rt.bottom - rt.top)));

	if (NULL != pObj)
	{
		CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		CComponentView* pComView = (CComponentView*)pMainFrm->GetComponentView();

		pComView->UpdateComponent(pObj);
	}


	CFormView::OnLButtonDown(nFlags, point);
	*/
}


void CGameView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}
