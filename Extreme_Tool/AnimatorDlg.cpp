// AnimatorDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "AnimatorDlg.h"
#include "afxdialogex.h"


// CAnimatorDlg 대화 상자입니다.
#include "GameObject.h"
#include "Animation.h"
#include "Animation_2D.h"
#include "AddAnimDlg.h"

IMPLEMENT_DYNAMIC(CAnimatorDlg, CDialogEx)

CAnimatorDlg::CAnimatorDlg(CWnd* pParent /*=NULL*/)
	: CComponentDlg(IDD_ANIMATORDLG, pParent)
	, m_bRepeat(FALSE)
	, m_bFocus_cb(false)
	, m_iCurAnimIdx(-1)
	, m_bFocus_Term(false)
{

}

CAnimatorDlg::~CAnimatorDlg()
{
}

void CAnimatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_ANIM_REPEAT_CHECK, m_bRepeat);
	DDX_Control(pDX, IDC_COMBO1, m_cbAnim);
	DDX_Control(pDX, IDC_ANIM_TERM, m_EditTerm);
}

void CAnimatorDlg::UpdateComponent(CGameObject * _pObj)
{
	m_pTargetObj = _pObj;

	if (NULL == m_pTargetObj)
		return;

	if (!m_bFocus_cb)
	{
		m_vecAnim.clear();
		m_cbAnim.ResetContent();
		m_pTargetObj->Animator()->PushAnimations(m_vecAnim);

		for (UINT i = 0; i < m_vecAnim.size(); ++i)
		{
			m_cbAnim.InsertString(i, m_vecAnim[i].strKey.c_str());
		}

		CAnimation* pCurAnim = m_pTargetObj->Animator()->GetCurAnim();

		if (NULL == pCurAnim)
			m_cbAnim.SetCurSel(-1);
		else
		{
			int iIdx = m_cbAnim.FindString(-1, pCurAnim->GetKey().c_str());  // -1 부터 찾아야함.
			m_cbAnim.SetCurSel(iIdx);
		}
	}
	m_bRepeat = m_pTargetObj->Animator()->IsRepeat();

	if (!m_bFocus_Term)
	{
		CAnimation* pCurAnim = m_pTargetObj->Animator()->GetCurAnim();
		if (NULL != pCurAnim)
		{
			float fTerm = pCurAnim->GetAnimTerm();
			CString strTerm;
			strTerm.Format(L"%.3f", fTerm);
			m_EditTerm.SetWindowTextW(strTerm);
		}
	}

	UpdateData(false);
}

BEGIN_MESSAGE_MAP(CAnimatorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ANIM_BUTTON1, &CAnimatorDlg::OnAddBnClicked)
	ON_BN_CLICKED(IDC_ANIM_REPEAT_CHECK, &CAnimatorDlg::OnBnClickedAnimRepeatCheck)
	ON_CBN_KILLFOCUS(IDC_COMBO1, &CAnimatorDlg::OnCbnKillfocus)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAnimatorDlg::OnCbnSelchange)
	ON_CBN_SETFOCUS(IDC_COMBO1, &CAnimatorDlg::OnCbnSetfocus)
	ON_BN_CLICKED(IDC_BUTTON1, &CAnimatorDlg::OnSubComponentBnClicked)
//	ON_CBN_DROPDOWN(IDC_COMBO1, &CAnimatorDlg::OnCbnDropdownCombo1)
ON_BN_CLICKED(IDC_BUTTON2, &CAnimatorDlg::OnBnClickedButton2)
ON_EN_SETFOCUS(IDC_ANIM_TERM, &CAnimatorDlg::OnEnSetfocusAnimTerm)
ON_EN_KILLFOCUS(IDC_ANIM_TERM, &CAnimatorDlg::OnEnKillfocusAnimTerm)
ON_EN_CHANGE(IDC_ANIM_TERM, &CAnimatorDlg::OnEnChangeAnimTerm)
END_MESSAGE_MAP()


// CAnimatorDlg 메시지 처리기입니다.
void CAnimatorDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CComponentDlg::PostNcDestroy();
}



void CAnimatorDlg::OnAddBnClicked()
{
	CAddAnimDlg dlg;

	if (NULL == m_pTargetObj)
		return;

	dlg.SetTarget(m_pTargetObj);

	dlg.DoModal();
}


void CAnimatorDlg::OnBnClickedAnimRepeatCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (NULL == m_pTargetObj)
		return;

	if (m_bRepeat)
		m_bRepeat = FALSE;
	else
		m_bRepeat = TRUE;

	bool bReapeat = (m_bRepeat == TRUE) ? true : false;
	m_pTargetObj->Animator()->SetRepeat(bReapeat);
	UpdateData(false);
}

void CAnimatorDlg::OnCbnSetfocus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bFocus_cb = true;
}


void CAnimatorDlg::OnCbnKillfocus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bFocus_cb = false;
}


void CAnimatorDlg::OnCbnSelchange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (NULL == m_pTargetObj)
		return;

	int iIDx = m_cbAnim.GetCurSel();

	if (-1 == iIDx || m_iCurAnimIdx == iIDx) return;
	m_iCurAnimIdx = iIDx;
	CString str;
	m_cbAnim.GetLBText(iIDx, str);
	bool bReapeat = (m_bRepeat == TRUE) ? true : false;
	m_pTargetObj->Animator()->PlayAnimation(str.GetBuffer(), bReapeat);
	::SetFocus(m_hWndOwner);
}


void CAnimatorDlg::OnSubComponentBnClicked()
{
	if (NULL == m_pTargetObj)
		return;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pTargetObj->SubComponent<CAnimator>();
}


BOOL CAnimatorDlg::OnInitDialog()
{
	CComponentDlg::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_CMenu.LoadMenuW(IDR_MENU1);
	m_EditTerm.SendMessage(EM_SETREADONLY, 1, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAnimatorDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iIDx = m_cbAnim.GetCurSel();

	if (-1 == iIDx) return;
	m_iCurAnimIdx = iIDx;
	CString str;
	m_cbAnim.GetLBText(iIDx, str);
	m_pTargetObj->Animator()->RemoveAnimation(str.GetBuffer());
	m_iCurAnimIdx = -1;
	::SetFocus(m_hWndOwner);
}


void CAnimatorDlg::OnEnSetfocusAnimTerm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bFocus_Term = true;
	m_EditTerm.SendMessage(EM_SETREADONLY, 0, 0);
}


void CAnimatorDlg::OnEnKillfocusAnimTerm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bFocus_Term = false;
	m_EditTerm.SendMessage(EM_SETREADONLY, 1, 0);
}


void CAnimatorDlg::OnEnChangeAnimTerm()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (NULL == m_pTargetObj) return;
	if (m_bFocus_Term)
	{
		CString str;
		m_EditTerm.GetWindowTextW(str);
		float fTerm = (float)_wtof(str);
		CAnimation* pCurAnim = m_pTargetObj->Animator()->GetCurAnim();
		if (NULL == pCurAnim) return;
		pCurAnim->SetAnimTerm(fTerm);
		//m_pTargetObj->SetTag(str.GetBuffer());
	}

}
