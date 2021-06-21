// HierarchyDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "HierarchyDlg.h"
#include "afxdialogex.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"

#include "MainFrm.h"
#include "ComponentView.h"

#include "ResMgr.h"
#include "DestroyMgr.h"


// CHierarchyDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHierarchyDlg, CDialogEx)

CHierarchyDlg::CHierarchyDlg(CWnd* pParent /*=NULL*/)
	: CTreeCtrlDlg(IDD_HIERARCHYDLG, pParent)
	, m_bDragMouseResDlg(false)
	, m_pDragGameObj(NULL)
	, m_hDragItem(NULL)
	, m_hTargetItem(NULL)
	, m_hLBtnClickedItem(NULL)
	, m_hRBtnClickedItem(NULL)
{

}

CHierarchyDlg::~CHierarchyDlg()
{
}

void CHierarchyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_ctrlTree);
}


BEGIN_MESSAGE_MAP(CHierarchyDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
//	ON_NOTIFY(TVN_BEGINRDRAG, IDC_TREE1, &CHierarchyDlg::OnTvnBeginrdragTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CHierarchyDlg::OnTvnSelchangedTree1)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_TREE1, &CHierarchyDlg::OnTvnBegindragTree1)
//	ON_WM_RBUTTONDOWN()
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CHierarchyDlg::OnNMRClickTree1)
	ON_COMMAND(ID_MENU_ADDPREFAB, &CHierarchyDlg::OnMenuAddprefab)
	ON_COMMAND(ID_MENU_Delete, &CHierarchyDlg::OnMenuDelete)
	ON_NOTIFY(TVN_KEYDOWN, IDC_TREE1, &CHierarchyDlg::OnTvnKeydownTree1)
//	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CHierarchyDlg::OnNMClickTree1)
ON_NOTIFY(NM_CLICK, IDC_TREE1, &CHierarchyDlg::OnNMClickTree1)
END_MESSAGE_MAP()


// CHierarchyDlg 메시지 처리기입니다.

void CHierarchyDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;
	CTreeCtrlDlg::PostNcDestroy();
}


BOOL CHierarchyDlg::OnInitDialog()
{
	CTreeCtrlDlg::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetTimer(0, 500, NULL); 
	m_CMenu1.LoadMenuW(IDR_MENU1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CHierarchyDlg::UpdateTreeControl()
{
	m_ctrlTree.DeleteAllItems();

	// 모든 게임 오브젝트 가져온다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	list<CGameObject*> listObj;
	pCurScene->GetAllParentObjects(listObj);

	list<CGameObject*>::iterator iter = listObj.begin();
	for (; iter != listObj.end(); ++iter)
	{
		AddGameObject((*iter), NULL);
	}

	Invalidate();
}

// wrapping func
void CHierarchyDlg::AddGameObject(CGameObject * _pObj, HTREEITEM _hParent)
{
	// 해당 아이템을 트리 컨트롤에 넣는다.
	HTREEITEM hParentItem = AddItem(_pObj->GetTag(), _hParent, (DWORD_PTR)_pObj);

	list<CGameObject*>& listChildObj  = _pObj->GetChildList();
	list<CGameObject*>::iterator iter = listChildObj.begin();
	for (; iter != listChildObj.end(); ++iter)
	{
		AddGameObject((*iter), hParentItem);
	}
}

void CHierarchyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (CSceneMgr::GetInst()->GetUpdateCheck())
	{
		CSceneMgr::GetInst()->SetUpdateCheck(false);

		// Tree Control 을 GameObject 정보로 갱신한다.
		UpdateTreeControl();
	}
	CTreeCtrlDlg::OnTimer(nIDEvent);
}


void CHierarchyDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (NULL == m_hDragItem)
		return;
	// 드래그 중일 경우
	::ClientToScreen(m_hWnd, &point);
	m_ctrlTree.ScreenToClient(&point);

	m_hTargetItem = m_ctrlTree.HitTest(point);

	if (NULL != m_hTargetItem)
	{
		m_ctrlTree.SelectDropTarget(m_hTargetItem);
	}

	RECT rt = {};
	GetClientRect(&rt);
	if (point.y > rt.bottom)
	{
		m_bDragMouseResDlg = true;
	}
	else
	{
		m_bDragMouseResDlg = false;
	}

	CTreeCtrlDlg::OnMouseMove(nFlags, point);
}


void CHierarchyDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (NULL == m_hDragItem)
		return;

	// 마우스 캡쳐 해제
	ReleaseCapture();

	// 하이라이트 제거
	m_ctrlTree.SelectDropTarget(NULL);

	if (true == m_bDragMouseResDlg)
	{
		if (NULL != m_pDragGameObj)
		{
			wstring strPrefabTag = m_pDragGameObj->GetTag();
			strPrefabTag += L"(Prefab)";
			CResMgr::GetInst()->AddPrefab(strPrefabTag, m_pDragGameObj->Clone());

			m_hDragItem = NULL;
			m_hTargetItem = NULL;
			m_pDragGameObj = NULL;
			return;
		}
	}
	else
	{
		// 목적지가 자기자신이거나, 목적지가 자신의 부모일 경우
		if (m_hDragItem == m_hTargetItem
			|| m_hTargetItem == m_ctrlTree.GetNextItem(m_hDragItem, TVGN_PARENT))
			return;

		CGameObject* pDragObj = (CGameObject*)m_ctrlTree.GetItemData(m_hDragItem);

		if (NULL == m_hTargetItem)
		{
			pDragObj->ClearParent();
			CLayer* pLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(pDragObj->GetLayerName());
			pLayer->AddParentObject(pDragObj);
			MoveTreeItem(m_hDragItem, m_hTargetItem);
		}
		else
		{
			CGameObject* pTargetObj = (CGameObject*)m_ctrlTree.GetItemData(m_hTargetItem);
			if (!FAILED(pTargetObj->AddChildObj(pDragObj)))
			{
				MoveTreeItem(m_hDragItem, m_hTargetItem);
			}
		}
	}

	// 초기화
	m_hDragItem   = NULL;
	m_hTargetItem = NULL;
	m_pDragGameObj = NULL;

	CTreeCtrlDlg::OnLButtonUp(nFlags, point);
}


void CHierarchyDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (NULL != m_hDragItem)
		return;

	CGameObject* pObj = (CGameObject*)m_ctrlTree.GetItemData(pNMTreeView->itemNew.hItem);

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CComponentView* pComView = (CComponentView*)pMainFrm->GetComponentView();
	pComView->UpdateComponent(pObj);

	*pResult = 0;
}


void CHierarchyDlg::OnTvnBegindragTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_hDragItem = pNMTreeView->itemNew.hItem;
	m_pDragGameObj = (CGameObject*)m_ctrlTree.GetItemData(m_hDragItem);
	// 마우스 이벤트 독점

	SetCapture();


	*pResult = 0;
}

void CHierarchyDlg::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CPoint	point;
	GetCursorPos(&point);
	m_ctrlTree.ScreenToClient(&point);
	m_hRBtnClickedItem = m_ctrlTree.HitTest(point);

	if (NULL == m_hRBtnClickedItem)	return;
	GetCursorPos(&point);

	CMenu *p_Menu = m_CMenu1.GetSubMenu(0);
	if (NULL == p_Menu) return;
	p_Menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	*pResult = 0;
}


void CHierarchyDlg::OnMenuAddprefab()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (NULL == m_hRBtnClickedItem) return;

	CGameObject* pRBtnClickedObj = (CGameObject*)m_ctrlTree.GetItemData(m_hRBtnClickedItem);
	if (NULL == pRBtnClickedObj) return;

	CResMgr::GetInst()->AddPrefab(pRBtnClickedObj->GetTag(), pRBtnClickedObj->Clone());

	m_hRBtnClickedItem = NULL;
	pRBtnClickedObj = NULL;
}


void CHierarchyDlg::OnMenuDelete()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (NULL == m_hRBtnClickedItem) return;

	CGameObject* pRBtnClickedObj = (CGameObject*)m_ctrlTree.GetItemData(m_hRBtnClickedItem);
	if (NULL == pRBtnClickedObj) return;

	CDestroyMgr::GetInst()->AddGameObject(pRBtnClickedObj);

	m_hRBtnClickedItem = NULL;
	pRBtnClickedObj = NULL;

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMainFrm->Init();
}

void CHierarchyDlg::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CPoint	point;
	GetCursorPos(&point);
	m_ctrlTree.ScreenToClient(&point);
	m_hLBtnClickedItem = m_ctrlTree.HitTest(point);

	if (NULL == m_hLBtnClickedItem)	return;

	*pResult = 0;
}

void CHierarchyDlg::OnTvnKeydownTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVKEYDOWN pTVKeyDown = reinterpret_cast<LPNMTVKEYDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (NULL == m_hLBtnClickedItem) return;

	if (pTVKeyDown->wVKey == VK_DELETE)
	{
		CGameObject* pLBtnClickedObj = (CGameObject*)m_ctrlTree.GetItemData(m_hLBtnClickedItem);
		if (NULL == pLBtnClickedObj) return;

		CDestroyMgr::GetInst()->AddGameObject(pLBtnClickedObj);

		pLBtnClickedObj = NULL;
		m_hLBtnClickedItem = NULL;

		CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMainFrm->Init();
	}

	*pResult = 0;
}



void CHierarchyDlg::OnOK()
{

	//CTreeCtrlDlg::OnOK();
}


void CHierarchyDlg::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CTreeCtrlDlg::OnCancel();
}
