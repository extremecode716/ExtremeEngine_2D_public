
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "Extreme_Tool.h"

#include "MainFrm.h"
#include "GameView.h"
#include "HierarchyView.h"
#include "ComponentView.h"
#include "ButtonView.h"
#include "DebugView.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "Transform.h"

#include "PathMgr.h"
#include "SaveLoadMgr.h"
#include "ResMgr.h"

#include "MapTool_2D.h"
#include "SceneInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// (1900, 1070) ->  // (1650, 900) 
#define WORK_SPACE_X 1700  
#define WORK_SPACE_Y 1000

// (1200, 675)  ->  // (1000, 600) 
#define GAME_VIEW_X 1000
#define GAME_VIEW_Y 600

#define BUTTON_VIEW_X GAME_VIEW_X
#define BUTTON_VIEW_Y 40

#define DEBUG_VIEW_X GAME_VIEW_X
#define DEBUG_VIEW_Y WORK_SPACE_Y - GAME_VIEW_Y - BUTTON_VIEW_Y

// (300) -> // (250)
#define HIERARCHY_VIEW_X 200
#define HIERARCHY_VIEW_Y WORK_SPACE_Y

#define COMPONENT_VIEW_X WORK_SPACE_X - GAME_VIEW_X - HIERARCHY_VIEW_X
#define COMPONENT_VIEW_Y WORK_SPACE_Y

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_GAMEOBJECT_ADDGAMEOBJECT, &CMainFrame::OnAddGameObject)
	ON_COMMAND(ID_SCENE_SAVE, &CMainFrame::OnSceneSave)
	ON_COMMAND(ID_SCENE_LOAD, &CMainFrame::OnSceneLoad)
	ON_COMMAND(ID_TOOL_TILETOOL, &CMainFrame::OnTileTool)
	ON_COMMAND(ID_TOOL_TEXTURELOAD, &CMainFrame::OnToolTextureload)
	ON_COMMAND(ID_SCENE_SCENEINFO, &CMainFrame::OnSceneSceneinfo)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
	: m_pMapTool2D(NULL)
	, m_pSceneInfo(NULL)
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::Init()
{
	((CHierarchyView*)GetHierarchyView())->Init();
	((CComponentView*)GetComponentView())->InitTarget();
	((CComponentView*)GetComponentView())->update();
	CSceneMgr::GetInst()->SetUpdateCheck(true);
	CResMgr::GetInst()->SetChange(true);
}

void CMainFrame::update()
{
	CComponentView* pComView = (CComponentView*)GetComponentView();
	pComView->update();
	CButtonView* pBtnView = (CButtonView*)GetBtnView();
	pBtnView->update();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 프레임의 클라이언트 영역을 차지하는 뷰를 만듭니다.
	m_MainSplitter.SetBorderSize(CPoint(0, 0), CPoint(1, 1));
	m_SubSplitter.SetBorderSize(CPoint(0, 0), CPoint(1, 1));

	// FrameWnd 3열 분할
	m_MainSplitter.CreateStatic(this, 1, 3);
	m_MainSplitter.SetColumnInfo(0, GAME_VIEW_X - 4, GAME_VIEW_X - 4);

	// Frame Wnd 0, 0 요소를 3행으로 분할
	m_SubSplitter.CreateStatic(&m_MainSplitter, 3, 1, WS_CHILD | WS_VISIBLE, m_MainSplitter.IdFromRowCol(0, 0));

	// 조각난 영역에 View 를 생성한다.
	m_MainSplitter.CreateView(0, 1, RUNTIME_CLASS(CHierarchyView), CSize(HIERARCHY_VIEW_X, HIERARCHY_VIEW_Y), NULL);
	m_MainSplitter.CreateView(0, 2, RUNTIME_CLASS(CComponentView), CSize(COMPONENT_VIEW_X, COMPONENT_VIEW_Y), NULL);

	m_SubSplitter.CreateView(0, 0, RUNTIME_CLASS(CButtonView), CSize(BUTTON_VIEW_X, BUTTON_VIEW_Y), NULL);
	m_SubSplitter.CreateView(1, 0, RUNTIME_CLASS(CGameView), CSize(GAME_VIEW_X, GAME_VIEW_Y), NULL);
	m_SubSplitter.CreateView(2, 0, RUNTIME_CLASS(CDebugView), CSize(DEBUG_VIEW_X, DEBUG_VIEW_Y), NULL);

	m_pMapTool2D = new CMapTool_2D;
	m_pMapTool2D->Create(IDD_MAPTOOL_2D, this);
	m_pMapTool2D->ShowWindow(false);

	m_pSceneInfo = new CSceneInfo;
	m_pSceneInfo->Create(IDD_SCENEINFO, this);
	m_pSceneInfo->ShowWindow(false);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);


	RECT rt = { 0, 0, WORK_SPACE_X, WORK_SPACE_Y };

	AdjustWindowRect(&rt, cs.style, true);

	cs.cx = rt.right - rt.left + 2;
	cs.cy = rt.bottom - rt.top + 2;
	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 뷰 창으로 포커스를 이동합니다.

}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 뷰에서 첫째 크랙이 해당 명령에 나타나도록 합니다.


	// 그렇지 않으면 기본 처리합니다.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnAddGameObject()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->FindLayer(L"Default");

	CGameObject* pObj = new CGameObject;
	pObj->SetTag(L"Untagged Obj");
	pObj->AddComponent<CTransform>(new CTransform);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 100.f));
	pObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));

	pLayer->AddGameObject(pObj);

	CComponentView* pView = (CComponentView*)GetComponentView();
	pView->SetTarget(pObj);
	::SetFocus(m_hWndOwner);
}


void CMainFrame::OnSceneSave()
{
	wchar_t szFilter[] = L"Scene (*.scene) | *.scene; |";

	CFileDialog dlg(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, szFilter);
	CString strInitPath = CPathMgr::GetResPath();
	strInitPath += L"Scene";
	dlg.m_ofn.lpstrInitialDir = strInitPath;

	CString strPathName;
	if (IDOK == dlg.DoModal()) {

		strPathName = dlg.GetPathName();
		wchar_t* pExt = CPathMgr::GetExt(strPathName.GetBuffer());

		if (0 == wcslen(pExt))
			strPathName += L".scene";

		CSaveLoadMgr::GetInst()->SaveScene(strPathName.GetBuffer());
	}
}

void CMainFrame::OnSceneLoad()
{
	wchar_t szFilter[] = L"Scene (*.scene) | *.scene; |";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_READONLY, szFilter);
	CString strInitPath = CPathMgr::GetResPath();
	strInitPath += L"Scene";
	dlg.m_ofn.lpstrInitialDir = strInitPath;

	CString strPathName;
	if (IDOK == dlg.DoModal()) {

		// ComponentView 초기화
		Init();

		strPathName = dlg.GetPathName();
		CSaveLoadMgr::GetInst()->LoadScene(strPathName.GetBuffer());
	}
}


void CMainFrame::OnTileTool()
{
	m_pMapTool2D->ShowWindow(true);
}


void CMainFrame::OnToolTextureload()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_READONLY);
	CString strFolderInitPath = CPathMgr::GetResPath();
	strFolderInitPath += L"Texture";
	dlg.m_ofn.lpstrInitialDir = strFolderInitPath;

	CString strFullPath;
	if (IDOK == dlg.DoModal()) {

		strFullPath = dlg.GetPathName();
		wstring strFolderPath = CPathMgr::GetFolderPath(strFullPath.GetBuffer());
		int iFind = strFolderPath.find(L"Texture");
		strFolderPath = strFolderPath.substr(iFind);
		wstring strFileName = CPathMgr::GetFileName(strFullPath.GetBuffer());
		wstring strEXT = CPathMgr::GetExt(strFullPath.GetBuffer());
		if (strEXT != L".png" && strEXT != L".jpg" && strEXT != L".jpeg" && strEXT != L".bmp" && strEXT != L".gif")
			return;
		wstring strFilePath = strFolderPath + strFileName + strEXT;

		CResMgr::GetInst()->Load<CTexture>(strFileName, strFilePath);

		// ComponentView 초기화
		Init();

	}
}

void CMainFrame::OnSceneSceneinfo()
{
	m_pSceneInfo->ShowWindow(true);
}
