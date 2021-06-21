// MapTool_2D.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "MapTool_2D.h"
#include "afxdialogex.h"

#include "..\External\ScriptMgr\View\TileMgrScript.h"
// CMapTool_2D ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTool_2D, CDialogEx)

CMapTool_2D::CMapTool_2D(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAPTOOL_2D, pParent)
	, m_pTileMgrScript(NULL)
{

}

CMapTool_2D::~CMapTool_2D()
{
}

void CMapTool_2D::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditStartPosX);
	DDX_Control(pDX, IDC_EDIT2, m_EditStartPosY);
	DDX_Control(pDX, IDC_EDIT3, m_EditTileSizeX);
	DDX_Control(pDX, IDC_EDIT4, m_EditTileSizeY);
	DDX_Control(pDX, IDC_EDIT5, m_EditTileCountX);
	DDX_Control(pDX, IDC_EDIT7, m_EditTileCountY);
}


BEGIN_MESSAGE_MAP(CMapTool_2D, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool_2D::OnMapInfoChangeClickedButton)
//	ON_WM_ACTIVATE()
ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CMapTool_2D �޽��� ó�����Դϴ�.


void CMapTool_2D::OnMapInfoChangeClickedButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// Ÿ�� �� ���� ����
	CString str;
	float fMapInfo = 0.f;
	int iMapInfo = 0;
	bool bError = false;
	float arrfMapInfo[4] = { 0.f, };
	int   arriMapInfo[2] = { 0, };

	// Start Pos Setting
	m_EditStartPosX.GetWindowTextW(str);
	fMapInfo = (float)_wtof(str);
	arrfMapInfo[0] = fMapInfo;
	m_EditStartPosY.GetWindowTextW(str);
	fMapInfo = (float)_wtof(str);
	arrfMapInfo[1] = fMapInfo;

	// Tile Size Setting
	m_EditTileSizeX.GetWindowTextW(str);
	fMapInfo = (float)_wtof(str);
	bError = (bError == false) ? ((fMapInfo > 0) ? false : true) : true;
	arrfMapInfo[2] = fMapInfo;
	m_EditTileSizeY.GetWindowTextW(str);
	fMapInfo = (float)_wtof(str);
	bError = (bError == false) ? ((fMapInfo > 0) ? false : true) : true;
	arrfMapInfo[3] = fMapInfo;

	// Tile Count Setting
	m_EditTileCountX.GetWindowTextW(str);
	iMapInfo = _wtoi(str);
	bError = (bError == false) ? ((iMapInfo > 0) ? false : true) : true;
	arriMapInfo[0] = iMapInfo;
	m_EditTileCountY.GetWindowTextW(str);
	iMapInfo = _wtoi(str);
	bError = (bError == false) ? ((iMapInfo > 0) ? false : true) : true;
	arriMapInfo[1] = iMapInfo;

	if (bError == false)
	{
		m_pTileMgrScript = CTileMgrScript::GetInst(L"TileMgr", L"Default");
		m_pTileMgrScript->GetGameObject()->Transform()->SetLocalPos(Vec3(0.f, 0.f, 100.f));
		// Ÿ�� ������Ʈ ����. // ������ Ÿ�� ������Ʈ�� ���� �� ��.
		
		list<CGameObject*>::iterator iter = m_pTileMgrScript->GetGameObject()->GetChildList().begin();
		for (; iter != m_pTileMgrScript->GetGameObject()->GetChildList().end(); ++iter)
		{
			CDestroyMgr::GetInst()->AddGameObject(*iter);
		}
		CDestroyMgr::GetInst()->Destory();
		m_pTileMgrScript->GetGameObject()->GetChildList().clear();
		m_pTileMgrScript->Destory();

		// TileMgr Setting
		m_pTileMgrScript->m_vStartPos.x = arrfMapInfo[0];
		m_pTileMgrScript->m_vStartPos.y = arrfMapInfo[1];

		m_pTileMgrScript->m_vSize.x = arrfMapInfo[2];
		m_pTileMgrScript->m_vSize.y = arrfMapInfo[3];

		m_pTileMgrScript->m_iXCount = arriMapInfo[0];
		m_pTileMgrScript->m_iYCount = arriMapInfo[1];

		m_pTileMgrScript->CreateTile();

		// ���� ��ġ
		// ������
		// ����
		float fXSize = m_pTileMgrScript->m_vSize.x;
		float fYSize = m_pTileMgrScript->m_vSize.y;
		Vec3 vStartPos = Vec3(m_pTileMgrScript->m_vStartPos.x + fXSize / 2.f, m_pTileMgrScript->m_vStartPos.y, 1.f);
		UINT iXCount = m_pTileMgrScript->m_iXCount;
		UINT iYCount = m_pTileMgrScript->m_iYCount;

		Vec3 vNextPos;
		Vec3 vPos;
		for (UINT y = 0; y < iYCount; ++y)
		{
			vNextPos = vStartPos + Vec3(y * fXSize / 2.f, y * -fYSize / 2.f , 0.f);
			for (UINT x = 0; x < iXCount; ++x)
			{
				vPos = vNextPos + Vec3(x * fXSize / 2.f, x * fYSize / 2.f, 0.f);
				
				m_pTileMgrScript->SetTileInfo(x, y, Vec2(vPos.x, vPos.y), TILE_TYPE::BASIC);

				// Ÿ�� ������Ʈ ���� �� �ڽ����� �߰�.
				CGameObject* pTileObjs = new CGameObject;
				wstring strName = wstring(L"Tile[" + to_wstring(y) + L"][" + to_wstring(x) + L"]");
				pTileObjs->SetTag(strName);
				pTileObjs->AddComponent<CTransform>(new CTransform);
				pTileObjs->Transform()->SetLocalPos(vPos);
				pTileObjs->Transform()->SetLocalScale(Vec3(fXSize, fYSize, 1.f));
				pTileObjs->AddComponent<CMeshRender>(new CMeshRender);
				pTileObjs->MeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
				pTileObjs->MeshRender()->SetMaterial(CResMgr::GetInst()->FindMaterial(L"MapMtrl"));
				CSceneMgr::GetInst()->GetCurScene()->FindLayer(m_pTileMgrScript->GetGameObject()->GetLayerName())->AddGameObject(pTileObjs);
				
				m_pTileMgrScript->GetGameObject()->AddChildObj(pTileObjs);			
			}
		}

		CDialogEx::OnOK();
	}
}


BOOL CMapTool_2D::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_bFocuse = false;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMapTool_2D::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	delete this;
	CDialogEx::PostNcDestroy();
}



void CMapTool_2D::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		m_pTileMgrScript = CTileMgrScript::GetThis();
		if (NULL != m_pTileMgrScript)
		{
			CString str;
			// Start Pos
			str.Format(L"%.1f", m_pTileMgrScript->m_vStartPos.x);
			m_EditStartPosX.SetWindowTextW(str);
			str.Format(L"%.1f", m_pTileMgrScript->m_vStartPos.y);
			m_EditStartPosY.SetWindowTextW(str);

			// Tile Size
			str.Format(L"%.1f", m_pTileMgrScript->m_vSize.x);
			m_EditTileSizeX.SetWindowTextW(str);
			str.Format(L"%.1f", m_pTileMgrScript->m_vSize.y);
			m_EditTileSizeY.SetWindowTextW(str);

			// Tile Count
			str.Format(L"%d", m_pTileMgrScript->m_iXCount);
			m_EditTileCountX.SetWindowTextW(str);
			str.Format(L"%d", m_pTileMgrScript->m_iYCount);
			m_EditTileCountY.SetWindowTextW(str);
		}
		// NULL�϶� ���� ���ְ� ������ else ó���ؼ� 0���� ó���� ��... �� ���ʿ���� ������ ó�����ؾ���.
	}
}
