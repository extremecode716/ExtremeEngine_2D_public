//
// ButtonView.cpp : ���� �����Դϴ�.
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


// CButtonView �����Դϴ�.

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


// CButtonView �޽��� ó�����Դϴ�.


void CButtonView::OnBnClickedPlayButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// View �ʱ�ȭ
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMainFrm->Init();
	
	CSaveLoadMgr::GetInst()->LoadPlayScene(m_strPathName.GetBuffer());
	m_strPathName = L"";

	// �ϴ� ����.
	//m_pCameraObj->Camera()->Reset();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	// �ʱ�ȭ ����
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	// Tool ���� ī�޶� ����


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
