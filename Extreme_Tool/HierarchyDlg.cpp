// HierarchyDlg.cpp : ���� �����Դϴ�.
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


// CHierarchyDlg ��ȭ �����Դϴ�.

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


// CHierarchyDlg �޽��� ó�����Դϴ�.

void CHierarchyDlg::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	delete this;
	CTreeCtrlDlg::PostNcDestroy();
}


BOOL CHierarchyDlg::OnInitDialog()
{
	CTreeCtrlDlg::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetTimer(0, 500, NULL); 
	m_CMenu1.LoadMenuW(IDR_MENU1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CHierarchyDlg::UpdateTreeControl()
{
	m_ctrlTree.DeleteAllItems();

	// ��� ���� ������Ʈ �����´�.
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
	// �ش� �������� Ʈ�� ��Ʈ�ѿ� �ִ´�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (CSceneMgr::GetInst()->GetUpdateCheck())
	{
		CSceneMgr::GetInst()->SetUpdateCheck(false);

		// Tree Control �� GameObject ������ �����Ѵ�.
		UpdateTreeControl();
	}
	CTreeCtrlDlg::OnTimer(nIDEvent);
}


void CHierarchyDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (NULL == m_hDragItem)
		return;
	// �巡�� ���� ���
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (NULL == m_hDragItem)
		return;

	// ���콺 ĸ�� ����
	ReleaseCapture();

	// ���̶���Ʈ ����
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
		// �������� �ڱ��ڽ��̰ų�, �������� �ڽ��� �θ��� ���
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

	// �ʱ�ȭ
	m_hDragItem   = NULL;
	m_hTargetItem = NULL;
	m_pDragGameObj = NULL;

	CTreeCtrlDlg::OnLButtonUp(nFlags, point);
}


void CHierarchyDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_hDragItem = pNMTreeView->itemNew.hItem;
	m_pDragGameObj = (CGameObject*)m_ctrlTree.GetItemData(m_hDragItem);
	// ���콺 �̺�Ʈ ����

	SetCapture();


	*pResult = 0;
}

void CHierarchyDlg::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (NULL == m_hRBtnClickedItem) return;

	CGameObject* pRBtnClickedObj = (CGameObject*)m_ctrlTree.GetItemData(m_hRBtnClickedItem);
	if (NULL == pRBtnClickedObj) return;

	CResMgr::GetInst()->AddPrefab(pRBtnClickedObj->GetTag(), pRBtnClickedObj->Clone());

	m_hRBtnClickedItem = NULL;
	pRBtnClickedObj = NULL;
}


void CHierarchyDlg::OnMenuDelete()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	//CTreeCtrlDlg::OnCancel();
}
