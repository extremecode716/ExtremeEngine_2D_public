// ComponentView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "ComponentView.h"

#include "TransformDlg.h"
#include "MeshRenderDlg.h"
#include "ColliderDlg.h"
#include "AnimatorDlg.h"
#include "ScriptDlg.h"

#include "GameObject.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

// CComponentView

IMPLEMENT_DYNCREATE(CComponentView, CFormView)

CComponentView::CComponentView()
	: CFormView(IDD_COMPONENTVIEW)
	, m_arrDlg{}
	, m_pTargetObj(NULL)
{

}

CComponentView::~CComponentView()
{
}

void CComponentView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_bnAC);
}

BEGIN_MESSAGE_MAP(CComponentView, CFormView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CComponentView::OnAddComBnClicked)
//	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CComponentView 진단입니다.

#ifdef _DEBUG
void CComponentView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CComponentView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CComponentView 메시지 처리기입니다.


int CComponentView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	m_arrDlg[(UINT)COMPONENT_TYPE::TRANSFORM] = new CTransformDlg;
	m_arrDlg[(UINT)COMPONENT_TYPE::TRANSFORM]->Create(IDD_TRANSFORMDLG, this);
	m_arrDlg[(UINT)COMPONENT_TYPE::TRANSFORM]->ShowWindow(false);
	m_arrDlg[(UINT)COMPONENT_TYPE::TRANSFORM]->UpdateWindow();



	m_arrDlg[(UINT)COMPONENT_TYPE::MESHRENDER] = new CMeshRenderDlg;
	m_arrDlg[(UINT)COMPONENT_TYPE::MESHRENDER]->Create(IDD_MESHRENDERDLG, this);
	m_arrDlg[(UINT)COMPONENT_TYPE::MESHRENDER]->ShowWindow(false);
	m_arrDlg[(UINT)COMPONENT_TYPE::MESHRENDER]->UpdateWindow();


	m_arrDlg[(UINT)COMPONENT_TYPE::COLLIDER] = new CColliderDlg;
	m_arrDlg[(UINT)COMPONENT_TYPE::COLLIDER]->Create(IDD_COLLIDERDLG, this);
	m_arrDlg[(UINT)COMPONENT_TYPE::COLLIDER]->ShowWindow(false);
	m_arrDlg[(UINT)COMPONENT_TYPE::COLLIDER]->UpdateWindow();


	m_arrDlg[(UINT)COMPONENT_TYPE::ANIMATOR] = new CAnimatorDlg;
	m_arrDlg[(UINT)COMPONENT_TYPE::ANIMATOR]->Create(IDD_ANIMATORDLG, this);
	m_arrDlg[(UINT)COMPONENT_TYPE::ANIMATOR]->ShowWindow(false);
	m_arrDlg[(UINT)COMPONENT_TYPE::ANIMATOR]->UpdateWindow();

	m_arrDlg[(UINT)COMPONENT_TYPE::SCRIPT] = new CScriptDlg;
	m_arrDlg[(UINT)COMPONENT_TYPE::SCRIPT]->Create(IDD_SCRIPTDLG, this);
	m_arrDlg[(UINT)COMPONENT_TYPE::SCRIPT]->ShowWindow(false);
	m_arrDlg[(UINT)COMPONENT_TYPE::SCRIPT]->UpdateWindow();

	return 0;
}


void CComponentView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrDlg[i])
			m_arrDlg[i]->DestroyWindow();
	}
}

void CComponentView::InitTarget()
{
	m_pTargetObj = NULL;
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrDlg[i])
			m_arrDlg[i]->InitTarget();
	}
}

void CComponentView::UpdateComponent(CGameObject * _pObj)
{
	m_pTargetObj = _pObj;
	if (NULL == m_pTargetObj)
	{
		for (UINT i = 0; i <= (UINT)COMPONENT_TYPE::SCRIPT; ++i)
		{
			if (NULL == m_arrDlg[i])
			{
				continue;
			}
			m_arrDlg[i]->ShowWindow(false);
		}
		return;
	}

	INT iStartY = 0;

	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::SCRIPT; ++i)
	{
		if (NULL == m_arrDlg[i])
		{
			continue;
		}
		else if (NULL == m_pTargetObj->GetComponent((COMPONENT_TYPE)i))
		{
			m_arrDlg[i]->ShowWindow(false);
		}
		else
		{
			RECT rt = {};
			m_arrDlg[i]->GetWindowRect(&rt);
			m_arrDlg[i]->ShowWindow(true);
			m_arrDlg[i]->SetWindowPos(NULL, 0, iStartY, rt.right - rt.left, rt.bottom - rt.top, 0);

			m_arrDlg[i]->UpdateComponent(_pObj);

			iStartY += rt.bottom - rt.top - 1;
		}
	}

	RECT rt = {};
	// Script Dlg
	//if (0 == m_pTargetObj->GetScriptList().size())
	//{
	//	m_arrDlg[(UINT)COMPONENT_TYPE::SCRIPT]->ShowWindow(false);
	//}
	//else
	//{
	m_arrDlg[(UINT)COMPONENT_TYPE::SCRIPT]->GetWindowRect(&rt);
	m_arrDlg[(UINT)COMPONENT_TYPE::SCRIPT]->ShowWindow(true);
	m_arrDlg[(UINT)COMPONENT_TYPE::SCRIPT]->SetWindowPos(NULL, 0, iStartY, rt.right - rt.left, rt.bottom - rt.top, 0);
	m_arrDlg[(UINT)COMPONENT_TYPE::SCRIPT]->UpdateComponent(_pObj);

	iStartY += rt.bottom - rt.top;
	//}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_ENTER, KEY_STATE::STATE_TAB))
	{
		::SetFocus(m_hWndOwner);
	}
	// Add Component Button
	m_bnAC.GetWindowRect(&rt);
	ScreenToClient(&rt);

	m_bnAC.SetWindowPos(NULL, rt.left, iStartY + 35, rt.right - rt.left, rt.bottom - rt.top, 0);

	// UpdateData(false);
}

void CComponentView::update()
{
	// 임시
	if (SCENE_STATE::PLAY != CSceneMgr::GetInst()->GetState())
	{
		UpdateComponent(m_pTargetObj);
	}
}


#include "ComListDlg.h"

void CComponentView::OnAddComBnClicked()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (SCENE_STATE::PLAY == CSceneMgr::GetInst()->GetState()
		|| SCENE_STATE::PAUSE == CSceneMgr::GetInst()->GetState())
	{
		return;
	}

	CComListDlg dlg;
	COMPONENT_TYPE type = (COMPONENT_TYPE)dlg.DoModal();
	if (NULL == m_pTargetObj) return;

	m_pTargetObj->AddComponent(type);

}


//HBRUSH CComponentView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
//	// TODO:  여기서 DC의 특성을 변경합니다.
//
//	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
//	return hbr;
//}


//void CComponentView::OnInitialUpdate()
//{
//	CFormView::OnInitialUpdate();
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//}
