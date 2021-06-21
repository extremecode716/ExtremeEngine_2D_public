// MapTool_2D.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "MapTool_2D.h"
#include "afxdialogex.h"

#include "..\External\ScriptMgr\View\TileMgrScript.h"
// CMapTool_2D 대화 상자입니다.

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


// CMapTool_2D 메시지 처리기입니다.


void CMapTool_2D::OnMapInfoChangeClickedButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 타일 맵 정보 갱신
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
		// 타일 오브젝트 생성. // 기존에 타일 오브젝트들 삭제 할 것.
		
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

		// 시작 위치
		// 사이즈
		// 개수
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

				// 타일 오브젝트 생성 및 자식으로 추가.
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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_bFocuse = false;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMapTool_2D::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
		// NULL일때 정보 없애고 싶으면 else 처리해서 0으로 처리할 것... 뭐 별필요없어 보여서 처리안해야지.
	}
}
