//
// ButtonView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "ButtonView.h"


#include "MainFrm.h"
#include "SceneMgr.h"
#include "..\External\SaveLoadMgr.h"
#include "HierarchyView.h"
#include "ComponentView.h"
#include "HierarchyDlg.h"
#include "ComponentDlg.h"

#include "ResMgr.h"

#include "..\External\ScriptCode\CameraScript.h"
#include "Camera.h"
#include "GameObject.h"
#include "SceneMgr.h"
#include "Transform.h"

#include "Device.h"


// CButtonView

IMPLEMENT_DYNCREATE(CButtonView, CFormView)

CButtonView::CButtonView()
	: CFormView(IDD_BUTTONVIEW)
{
}

CButtonView::~CButtonView()
{
	SAFE_DELETE(m_pCameraObj);
}

void CButtonView::update()
{
	if (SCENE_STATE::PLAY == CSceneMgr::GetInst()->GetState())
		return;

	m_pCameraObj->update();
	m_pCameraObj->lateupdate();
	m_pCameraObj->finalupdate();
}

void CButtonView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAY_BUTTON, m_PlayButton);
	DDX_Control(pDX, IDC_PAUSE_BUTTON, m_PauseButton);
	DDX_Control(pDX, IDC_STOP_BUTTON, m_StopButton);
}

BEGIN_MESSAGE_MAP(CButtonView, CFormView)
	ON_BN_CLICKED(IDC_PLAY_BUTTON, &CButtonView::OnBnClickedPlayButton)
	ON_BN_CLICKED(IDC_PAUSE_BUTTON, &CButtonView::OnBnClickedPauseButton)
	ON_BN_CLICKED(IDC_STOP_BUTTON, &CButtonView::OnBnClickedStopButton)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CButtonView 진단입니다.

#ifdef _DEBUG
void CButtonView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CButtonView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CButtonView 메시지 처리기입니다.


void CButtonView::OnBnClickedPlayButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//if (SCENE_STATE::PLAY == CSceneMgr::GetInst()->GetState()) return;

	if (SCENE_STATE::PAUSE != CSceneMgr::GetInst()->GetState())
	{
		m_strPathName = L"playTemp.scene";
		CSaveLoadMgr::GetInst()->SaveStopScene(m_strPathName.GetBuffer());
	}

	CSceneMgr::GetInst()->ChagneState(SCENE_STATE::PLAY);
	::SetFocus(((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetGameViewHwnd());
	//::SetFocus(m_hWndOwner);

	m_PlayButton.EnableWindow(false);
	m_PauseButton.EnableWindow(true);
	m_StopButton.EnableWindow(true);
}


void CButtonView::OnBnClickedPauseButton()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (SCENE_STATE::PAUSE == CSceneMgr::GetInst()->GetState()
		|| SCENE_STATE::NONE == CSceneMgr::GetInst()->GetState()
		|| SCENE_STATE::STOP == CSceneMgr::GetInst()->GetState()) return;

	CSceneMgr::GetInst()->ChagneState(SCENE_STATE::PAUSE);
	::SetFocus(((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetGameViewHwnd());


	m_PlayButton.EnableWindow(true);
	m_PauseButton.EnableWindow(false);
	m_StopButton.EnableWindow(true);
}


void CButtonView::OnBnClickedStopButton()
{
	//if (SCENE_STATE::STOP == CSceneMgr::GetInst()->GetState() 
	//	|| SCENE_STATE::NONE == CSceneMgr::GetInst()->GetState()) return;

	if (L"" == m_strPathName) return;
	// View 초기화
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMainFrm->Init();
	
	CSaveLoadMgr::GetInst()->LoadPlayScene(m_strPathName.GetBuffer());
	m_strPathName = L"";

	// 일단 해제.
	//m_pCameraObj->Camera()->Reset();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CSceneMgr::GetInst()->ChagneState(SCENE_STATE::STOP);

	m_PlayButton.EnableWindow(true);
	m_PauseButton.EnableWindow(false);
	m_StopButton.EnableWindow(false);

	CResMgr::GetInst()->SetChange(true);
	::SetFocus(((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetGameViewHwnd());
}


void CButtonView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// 초기화 영역
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	static bool bInit = false;

	if (bInit)
		return;
	bInit = true;

	m_strPathName = L"";
	m_PlayButton.EnableWindow(true);
	m_PauseButton.EnableWindow(false);
	m_StopButton.EnableWindow(false);
}


int CButtonView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// Tool 전용 카메라 생성


	m_pCameraObj = new CGameObject;

	m_pCameraObj->SetTag(L"ToolCamera");
	m_pCameraObj->AddComponent<CTransform>(new CTransform);
	m_pCameraObj->AddComponent<CCamera>(new CCamera);
	m_pCameraObj->AddComponent<CScript>(new CCameraScript);
	m_pCameraObj->Camera()->SetAllLayerRenderCheck();
	m_pCameraObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, -1.f));

	CSceneMgr::GetInst()->SetToolCam(m_pCameraObj);



	return 0;
}
