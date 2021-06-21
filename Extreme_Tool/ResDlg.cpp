// ResDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "ResDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ResMgr.h"
#include "ComponentView.h"

#include "Mesh.h"
#include "Material.h"
#include "Prefab.h"
#include "Texture.h"
#include "GameObject.h"
#include "ResPtr.h"
#include "Sound.h"


// CResDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CResDlg, CDialogEx)

CResDlg::CResDlg(CWnd* pParent /*=NULL*/)
	: CTreeCtrlDlg(IDD_RESDLG, pParent)
	, m_arrResRoot{}
{

}

CResDlg::~CResDlg()
{
}

void CResDlg::UpdateTreeControl()
{
	// ��Ʈ�� �ƴ� Tree Item ����
	HTREEITEM hRoot = m_ctrlTree.GetRootItem();

	while (true)
	{
		if (NULL == hRoot)
			break;
		DeleteChildren(hRoot);
		hRoot = m_ctrlTree.GetNextItem(hRoot, TVGN_NEXT);
	}

	map<wstring, CResPtr<CMesh>>& mapMesh     = CResMgr::GetInst()->GetMeshMap();
	map<wstring, CResPtr<CTexture>>& mapTex   = CResMgr::GetInst()->GetTextureMap();
	map<wstring, CResPtr<CPrefab>>& mapPrefab = CResMgr::GetInst()->GetPrefabMap();
	map<wstring, CResPtr<CMaterial>>& mapMtrl = CResMgr::GetInst()->GetMtrlMap();
	map<wstring, CResPtr<CSound>>& mapSound = CResMgr::GetInst()->GetSoundMap();
	vector<CResPtr<CRes>>& vecClone           = CResMgr::GetInst()->GetCloneMap();


	for (auto& pair : mapMesh)
		AddItem(pair.second->GetKey().c_str(), m_arrResRoot[(UINT)RES_TYPE::MESH], (DWORD_PTR)((CRes*)pair.second));

	for (auto& pair : mapTex)
		AddItem(pair.second->GetKey().c_str(), m_arrResRoot[(UINT)RES_TYPE::TEXTURE], (DWORD_PTR)((CRes*)pair.second));

	for (auto& pair : mapPrefab)
		AddItem(pair.second->GetKey().c_str(), m_arrResRoot[(UINT)RES_TYPE::PREFAB], (DWORD_PTR)((CRes*)pair.second));

	for (auto& pair : mapMtrl)
		AddItem(pair.second->GetKey().c_str(), m_arrResRoot[(UINT)RES_TYPE::MATERIAL], (DWORD_PTR)((CRes*)pair.second));

	for (auto& pair : mapSound)
		AddItem(pair.second->GetKey().c_str(), m_arrResRoot[(UINT)RES_TYPE::SOUND], (DWORD_PTR)((CRes*)pair.second));

	for (auto& pRes : vecClone)
		AddItem(pRes->GetKey().c_str(), m_arrResRoot[(UINT)RES_TYPE::CLONE], (DWORD_PTR)((CRes*)pRes));

	Invalidate();
}

void CResDlg::Init()
{
	HTREEITEM hRoot = m_ctrlTree.GetRootItem();

	while (true)
	{
		if (NULL == hRoot)
			break;
		DeleteChildren(hRoot);
		hRoot = m_ctrlTree.GetNextItem(hRoot, TVGN_NEXT);

	}
	Invalidate();
}

void CResDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TREE2, m_ctrlTree);
}


BEGIN_MESSAGE_MAP(CResDlg, CDialogEx)
	ON_WM_TIMER()
	ON_NOTIFY(NM_CLICK, IDC_TREE2, &CResDlg::OnNMClickTree2)
	ON_NOTIFY(TVN_KEYDOWN, IDC_TREE2, &CResDlg::OnTvnKeydownTree2)
	ON_NOTIFY(NM_RCLICK, IDC_TREE2, &CResDlg::OnNMRClickTree2)
	ON_COMMAND(ID_RESMENU_DELETE, &CResDlg::OnResmenuDelete)
END_MESSAGE_MAP()


// CResDlg �޽��� ó�����Դϴ�.


void CResDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (CResMgr::GetInst()->IsChange())
	{
		CResMgr::GetInst()->SetChange(false);
		UpdateTreeControl();
	}

	CTreeCtrlDlg::OnTimer(nIDEvent);
}


BOOL CResDlg::OnInitDialog()
{
	CTreeCtrlDlg::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetTimer(0, 1000, NULL);

	m_arrResRoot[(UINT)RES_TYPE::MESH]     = AddItem(L"Mesh", NULL, NULL);
	m_arrResRoot[(UINT)RES_TYPE::TEXTURE]  = AddItem(L"Texture", NULL, NULL);
	m_arrResRoot[(UINT)RES_TYPE::MATERIAL] = AddItem(L"Material", NULL, NULL);
	m_arrResRoot[(UINT)RES_TYPE::PREFAB]   = AddItem(L"Prefab", NULL, NULL);
	m_arrResRoot[(UINT)RES_TYPE::SOUND]	   = AddItem(L"Sound", NULL, NULL);
	m_arrResRoot[(UINT)RES_TYPE::CLONE]    = AddItem(L"Clone", NULL, NULL);

	m_CMenu1.LoadMenuW(IDR_MENU1);

	UpdateTreeControl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CResDlg::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	delete this;
	CTreeCtrlDlg::PostNcDestroy();
}


void CResDlg::OnNMClickTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CPoint point;
	GetCursorPos(&point);
	m_ctrlTree.ScreenToClient(&point);
	m_hLBtnClickedItem = m_ctrlTree.HitTest(point);

	if (NULL == m_hLBtnClickedItem) return;

	if (m_arrResRoot[(UINT)RES_TYPE::PREFAB] != m_ctrlTree.GetNextItem(m_hLBtnClickedItem, TVGN_PARENT))
		return;

	CPrefab* pPrefab = (CPrefab*)m_ctrlTree.GetItemData(m_hLBtnClickedItem);

	if (NULL == pPrefab)
		return;

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CComponentView* pComView = (CComponentView*)pMainFrm->GetComponentView();
	pComView->UpdateComponent(pPrefab->GameObject());

	*pResult = 0;
}

void CResDlg::OnNMRClickTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CPoint	point;
	GetCursorPos(&point);
	m_ctrlTree.ScreenToClient(&point);
	m_hRBtnClickedItem = m_ctrlTree.HitTest(point);

	if (NULL == m_hRBtnClickedItem)	return;
	HTREEITEM hRoot = m_ctrlTree.GetNextItem(m_hRBtnClickedItem, TVGN_PARENT);
	CString strName = m_ctrlTree.GetItemText(hRoot);
	if (L"Prefab" != strName) return;

	GetCursorPos(&point);

	CMenu *p_Menu = m_CMenu1.GetSubMenu(1);
	if (NULL == p_Menu) return;
	p_Menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	*pResult = 0;
}


void CResDlg::OnResmenuDelete()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (NULL == m_hRBtnClickedItem) return;

	CGameObject* pRBtnClickedObj = (CGameObject*)m_ctrlTree.GetItemData(m_hRBtnClickedItem);
	if (NULL == pRBtnClickedObj) return;

	HTREEITEM hRoot = m_ctrlTree.GetNextItem(m_hRBtnClickedItem, TVGN_PARENT);
	CString strName = m_ctrlTree.GetItemText(hRoot);
	if (L"Prefab" == strName)
	{
		CPrefab* pRBtnClickedObj = (CPrefab*)m_ctrlTree.GetItemData(m_hRBtnClickedItem);
		if (NULL == pRBtnClickedObj) return;

		pRBtnClickedObj = CResMgr::GetInst()->SubPrefab(pRBtnClickedObj->GetKey());
		SAFE_DELETE(pRBtnClickedObj);
		m_hRBtnClickedItem = NULL;

		CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMainFrm->Init();
	}
}



void CResDlg::OnTvnKeydownTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVKEYDOWN pTVKeyDown = reinterpret_cast<LPNMTVKEYDOWN>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (NULL == m_hLBtnClickedItem) return;

	if (pTVKeyDown->wVKey == VK_DELETE)
	{
		HTREEITEM hRoot = m_ctrlTree.GetNextItem(m_hLBtnClickedItem, TVGN_PARENT);
		CString strName = m_ctrlTree.GetItemText(hRoot);
		if (L"Prefab" == strName)
		{
			CPrefab* pLBtnClickedObj = (CPrefab*)m_ctrlTree.GetItemData(m_hLBtnClickedItem);
			if (NULL == pLBtnClickedObj) return;

			pLBtnClickedObj = CResMgr::GetInst()->SubPrefab(pLBtnClickedObj->GetKey());
			SAFE_DELETE(pLBtnClickedObj);
			m_hLBtnClickedItem = NULL;

			CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			pMainFrm->Init();
		}
	}
	*pResult = 0;
}



void CResDlg::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	//CTreeCtrlDlg::OnOK();
}


void CResDlg::OnCancel()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

//	CTreeCtrlDlg::OnCancel();
}
