// ScriptDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "ScriptDlg.h"
#include "afxdialogex.h"

#include "GameObject.h"
#include "SceneMgr.h"
#include "Script.h"
#include "ScriptMgr.h"

// CScriptDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CScriptDlg, CDialogEx)

CScriptDlg::CScriptDlg(CWnd* pParent /*=NULL*/)
	: CComponentDlg(IDD_SCRIPTDLG, pParent)
{

}

CScriptDlg::~CScriptDlg()
{
}

void CScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbScript);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CScriptDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CScriptDlg::OnAddScript)
	//ON_BN_CLICKED(IDC_BUTTON1, &CScriptDlg::OnSubComponentBnClicked)
	ON_LBN_SELCHANGE(IDC_LIST1, &CScriptDlg::OnLbnSelchangeList1)
	ON_COMMAND(ID_SCRIPTMENU_DELETE, &CScriptDlg::OnScriptmenuDelete)
	ON_LBN_KILLFOCUS(IDC_LIST1, &CScriptDlg::OnLbnKillfocusList1)
	ON_LBN_SETFOCUS(IDC_LIST1, &CScriptDlg::OnLbnSetfocusList1)
END_MESSAGE_MAP()


// CScriptDlg 메시지 처리기입니다.

BOOL CScriptDlg::OnInitDialog()
{
	CComponentDlg::OnInitDialog();

	vector<tScriptInfo> vec;
	CScriptMgr::GetScriptInfo(vec);

	for (UINT i = 0; i < vec.size(); ++i)
	{
		m_cbScript.InsertString(i, vec[i].strScriptName.c_str());
		m_cbScript.SetItemData(i, vec[i].dwTypeId);
	}

	m_iScriptIdx = -1;
	m_bFocusList = false;
	m_CMenu1.LoadMenuW(IDR_MENU1);
	return TRUE;
}

void CScriptDlg::UpdateList()
{
	if (NULL == m_pTargetObj) return;
	m_List.ResetContent();

	list<CScript*>& listScript = m_pTargetObj->GetScriptList();
	list<CScript*>::iterator iter = listScript.begin();
	for (int i = 0; iter != listScript.end(); ++iter, ++i)
	{
		CString strScriptName = CScriptMgr::GetScriptName(*iter);

		m_List.InsertString(i, strScriptName);
	}
}


void CScriptDlg::OnAddScript()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (NULL == m_pTargetObj)
		return;

	if (SCENE_STATE::PLAY == CSceneMgr::GetInst()->GetState()
		|| SCENE_STATE::PAUSE == CSceneMgr::GetInst()->GetState())
	{
		m_cbScript.SetCurSel(-1);
		return;
	}

	int iIdx = m_cbScript.GetCurSel();

	if (-1 == iIdx)
		return;

	DWORD dwTypeID = m_cbScript.GetItemData(iIdx);

	CScript* pScript = CScriptMgr::GetScript(dwTypeID);
	pScript->SetGameObject(m_pTargetObj);
	m_pTargetObj->AddComponent<CScript>(pScript);

	m_cbScript.SetCurSel(-1);
	::SetFocus(m_hWndOwner);
}


//void CScriptDlg::OnSubComponentBnClicked()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	m_pTargetObj->SubComponent<CScript>();
//}

void CScriptDlg::UpdateComponent(CGameObject * _pObj)
{
	m_pTargetObj = _pObj;
	if (NULL == m_pTargetObj) return;
	if (m_bFocusList) return;
	UpdateList();

}

void CScriptDlg::PostNcDestroy()
{
	delete this;
	CComponentDlg::PostNcDestroy();
}


void CScriptDlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (NULL == m_pTargetObj) return;

	const int iIdx = m_List.GetCurSel();

	if (-1 == iIdx)
		return;
	CMenu *p_Menu = m_CMenu1.GetSubMenu(2);
	if (NULL == p_Menu) return;
	CPoint	point;
	GetCursorPos(&point);
	p_Menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	m_iScriptIdx = iIdx;
}


void CScriptDlg::OnScriptmenuDelete()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (NULL == m_pTargetObj) return;
	if (-1 == m_iScriptIdx) return;

	m_pTargetObj->SubComponent<CScript>(m_iScriptIdx);

	m_iScriptIdx = -1;
	::SetFocus(m_hWndOwner);
}


void CScriptDlg::OnLbnKillfocusList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bFocusList = false;
}


void CScriptDlg::OnLbnSetfocusList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bFocusList = true;
}
