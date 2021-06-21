// MeshRenderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "MeshRenderDlg.h"
#include "afxdialogex.h"


// CMeshRenderDlg 대화 상자입니다.
#include "GameObject.h"
#include "MeshRender.h"
#include "Mesh.h"
#include "Material.h"

#include "ListDlg.h"

IMPLEMENT_DYNAMIC(CMeshRenderDlg, CDialogEx)

CMeshRenderDlg::CMeshRenderDlg(CWnd* pParent /*=NULL*/)
	: CComponentDlg(IDD_MESHRENDERDLG, pParent)
	, m_bFocus_mesh(false)
	, m_bFocus_mtrl(false)
	, m_bFocus_rs(false)
	, m_bMtrlShaderBn(false)
{

}

CMeshRenderDlg::~CMeshRenderDlg()
{
}

void CMeshRenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MESH, m_editMesh);
	DDX_Control(pDX, IDC_MTRL, m_editMtrl);
	DDX_Control(pDX, IDC_RS, m_cbRS);
	DDX_Control(pDX, IDC_BUTTON4, m_bnMtrlSP);
}

void CMeshRenderDlg::UpdateComponent(CGameObject * _pObj)
{
	m_pTargetObj = _pObj;
	if (NULL == m_pTargetObj)
		return;

	CString str;

	if (NULL != m_pTargetObj->MeshRender()->GetMesh())
	{
		str = m_pTargetObj->MeshRender()->GetMesh()->GetKey().c_str();
		m_editMesh.SetWindowTextW(str);
	}
	else
	{
		m_editMesh.SetWindowTextW(L"");
	}

	if (NULL != m_pTargetObj->MeshRender()->GetSharedMaterial())
	{
		str = m_pTargetObj->MeshRender()->GetSharedMaterial()->GetKey().c_str();
		m_editMtrl.SetWindowTextW(str);
	}
	else
	{
		m_editMtrl.SetWindowTextW(L"");
	}

	if (!m_bFocus_rs)
	{
		int iSel = (UINT)m_pTargetObj->MeshRender()->GetRSType();
		m_cbRS.SetCurSel(iSel);
	}
}

BEGIN_MESSAGE_MAP(CMeshRenderDlg, CDialogEx)
	ON_CONTROL_RANGE(EN_SETFOCUS, IDC_MESH, IDC_MTRL, &CMeshRenderDlg::OnEnSetfocus)
	ON_CONTROL_RANGE(EN_KILLFOCUS, IDC_MESH, IDC_MTRL, &CMeshRenderDlg::OnEnKillfocus)
	
	ON_CBN_SETFOCUS(IDC_RS, &CMeshRenderDlg::OnCbnSetfocusRs)
	ON_CBN_KILLFOCUS(IDC_RS, &CMeshRenderDlg::OnCbnKillfocusRs)
	ON_CBN_EDITCHANGE(IDC_RS, &CMeshRenderDlg::OnCbnEditchangeRs)
	ON_CBN_SELCHANGE(IDC_RS, &CMeshRenderDlg::OnCbnSelchangeRs)
	ON_BN_CLICKED(IDC_BUTTON1, &CMeshRenderDlg::OnMeshBnClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CMeshRenderDlg::OnMatrlBnClicked)
	ON_BN_CLICKED(IDC_BUTTON3, &CMeshRenderDlg::OnSubComponentBnClicked)
	ON_BN_CLICKED(IDC_BUTTON4, &CMeshRenderDlg::OnMtrlShaderBnClicked)
END_MESSAGE_MAP()


// CMeshRenderDlg 메시지 처리기입니다.

// CMeshRenderDlg message handlers
void CMeshRenderDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CComponentDlg::PostNcDestroy();
}


BOOL CMeshRenderDlg::OnInitDialog()
{
	CComponentDlg::OnInitDialog();

	m_cbRS.InsertString(0, L"RT_WIREFRAME");
	m_cbRS.InsertString(1, L"RT_FRONT");
	m_cbRS.InsertString(2, L"RT_BACK");
	m_cbRS.InsertString(3, L"RT_NONE");

	RECT rt = {};
	GetWindowRect(&rt);
	m_lHeightDlg = rt.bottom - rt.top;
	return TRUE;
}

void CMeshRenderDlg::OnEnSetfocus(UINT _id)
{
	if (_id == IDC_MESH)
		m_bFocus_mesh = true;
	else if (_id == IDC_MTRL)
		m_bFocus_mtrl = true;
}

void CMeshRenderDlg::OnEnKillfocus(UINT _id)
{
	if (_id == IDC_MESH)
		m_bFocus_mesh = false;
	else if (_id == IDC_MTRL)
		m_bFocus_mtrl = false;
}



void CMeshRenderDlg::OnCbnSetfocusRs()
{
	m_bFocus_rs = true;
}


void CMeshRenderDlg::OnCbnKillfocusRs()
{
	m_bFocus_rs = false;
}


void CMeshRenderDlg::OnCbnEditchangeRs()
{
	if (NULL == m_pTargetObj)
		return;
	int iSel = (UINT)m_pTargetObj->MeshRender()->GetRSType();
	m_cbRS.SetCurSel(iSel);
}


void CMeshRenderDlg::OnCbnSelchangeRs()
{
	if (NULL == m_pTargetObj)
		return;
	int iSel = m_cbRS.GetCurSel();
	m_pTargetObj->MeshRender()->SetRSMode((RASTERIZE_TYPE)iSel);
	::SetFocus(m_hWndOwner);
}

void CMeshRenderDlg::OnMeshBnClicked()
{
	if (NULL == m_pTargetObj)
		return;
	CListDlg dlg;

	dlg.InitList(RESOURCE_TYPE::MESH);

	CMesh* pMesh = (CMesh*)dlg.DoModal();

	if (NULL == pMesh)
		return;

	m_pTargetObj->MeshRender()->SetMesh(pMesh);
	::SetFocus(m_hWndOwner);
}

void CMeshRenderDlg::OnMatrlBnClicked()
{
	if (NULL == m_pTargetObj)
		return;
	CListDlg dlg;

	dlg.InitList(RESOURCE_TYPE::MATERIAL);

	CMaterial* pMtrl = (CMaterial*)dlg.DoModal();

	if (NULL == pMtrl)
		return;

	m_pTargetObj->MeshRender()->SetMaterial(pMtrl);

	::SetFocus(m_hWndOwner);
}


void CMeshRenderDlg::OnSubComponentBnClicked()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (NULL == m_pTargetObj)
		return;
	m_pTargetObj->SubComponent<CMeshRender>();
}


void CMeshRenderDlg::OnMtrlShaderBnClicked()
{
	if (NULL == m_pTargetObj)
		return;
	if (m_bMtrlShaderBn)
		m_bMtrlShaderBn = false;
	else
		m_bMtrlShaderBn = true;

	Safe_Delete_Vec(m_vecMtrlDlg);
	m_vecMtrlDlg.clear();

	RECT rt = {};
	GetWindowRect(&rt);
	if (m_bMtrlShaderBn)
	{
		const vector<tShaderParam_EX>& vParam = m_pTargetObj->MeshRender()->GetSharedMaterial()->GetVecParam();

		rt.bottom = rt.top + m_lHeightDlg;
		RECT childRt = {};
		for (UINT i = 0; i < vParam.size(); ++i)
		{
			m_vecMtrlDlg.push_back(new CMaterialDlg);
			m_vecMtrlDlg[i]->Create(IDD_MATERIALDLG, this);
			m_vecMtrlDlg[i]->ShowWindow(true);
			m_vecMtrlDlg[i]->UpdateWindow();
			m_vecMtrlDlg[i]->InitSP(m_pTargetObj->MeshRender()->GetSharedMaterial(), vParam[i]);
			m_vecMtrlDlg[i]->GetWindowRect(&childRt);
			LONG lHeightChild = childRt.bottom - childRt.top;
			m_vecMtrlDlg[i]->SetWindowPos(&wndTop, 0, rt.bottom - rt.top, childRt.right - childRt.left, childRt.bottom - childRt.top, 0);

			rt.bottom += lHeightChild;
			MoveWindow(&rt);
		
		}
		m_bnMtrlSP.SetWindowTextW(L"↑");
	}
	else
	{
		rt.bottom = rt.top + m_lHeightDlg;
		MoveWindow(&rt);
		m_bnMtrlSP.SetWindowTextW(L"↓");
	}

}
