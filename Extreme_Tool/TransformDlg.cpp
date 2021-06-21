// TransformDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "TransformDlg.h"
#include "afxdialogex.h"

#include "SceneMgr.h"
#include "GameObject.h"
#include "Transform.h"

#include "Scene.h"
#include "Layer.h"
// CTransformDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTransformDlg, CDialogEx)

CTransformDlg::CTransformDlg(CWnd* pParent /*=NULL*/)
	: CComponentDlg(IDD_TRANSFORMDLG, pParent)
{

}

CTransformDlg::~CTransformDlg()
{
}

void CTransformDlg::UpdateComponent(CGameObject * _pObj)
{
	m_pTargetObj = _pObj;
	if (NULL == m_pTargetObj)
		return;

	if (!m_bFocusTag)
	{
		wstring strTag = m_pTargetObj->GetTag();
		m_editTag.SetWindowTextW(strTag.c_str());
	}
	if (!m_bFocusLayer)
	{
		m_vecLayer.clear();
		m_cbLayer.ResetContent();

		CScene*	pCurScene = CSceneMgr::GetInst()->GetCurScene();
		pCurScene->GetLayers(m_vecLayer);

		UINT iVecSize = m_vecLayer.size();
		for (UINT i = 0; i < iVecSize; ++i)
		{
			m_cbLayer.InsertString(i, m_vecLayer[i].strName.c_str());
		}

		wstring strLayer = m_pTargetObj->GetLayerName();
		m_cbLayer.SetWindowTextW(strLayer.c_str());
	}
	CTransform* pTrans = m_pTargetObj->Transform();
	Vec3 vTransform[3] = { pTrans->GetLocalPos(),  pTrans->GetLocalRot(), pTrans->GetLocalScale() };

	CString str;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (!m_bFocus[i][j])
			{
				str.Format(L"%.2f", vTransform[i][j]);
				m_arrEdit[i][j].SetWindowTextW(str);
			}
		}
	}


}

void CTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	int iStartID = IDC_POS_X;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			DDX_Control(pDX, iStartID++, m_arrEdit[i][j]);
		}
	}
	DDX_Control(pDX, IDC_EDIT1, m_editTag);
	DDX_Control(pDX, IDC_COMBO1, m_cbLayer);
}


BEGIN_MESSAGE_MAP(CTransformDlg, CDialogEx)
	ON_CONTROL_RANGE(EN_SETFOCUS, IDC_POS_X, IDC_SCA_Z, &CTransformDlg::OnEnSetfocus)
	ON_CONTROL_RANGE(EN_KILLFOCUS, IDC_POS_X, IDC_SCA_Z, &CTransformDlg::OnEnKillfocus)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_POS_X, IDC_SCA_Z, &CTransformDlg::OnEnChange)
	ON_EN_SETFOCUS(IDC_EDIT1, &CTransformDlg::OnEnSetfocusEditTag)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CTransformDlg::OnEnKillfocusEditTag)
	ON_EN_CHANGE(IDC_EDIT1, &CTransformDlg::OnEnChangeEditTag)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTransformDlg::OnCbnSelchangeLayer)
	ON_CBN_KILLFOCUS(IDC_COMBO1, &CTransformDlg::OnCbnKillfocusLayer)
	ON_CBN_SETFOCUS(IDC_COMBO1, &CTransformDlg::OnCbnSetfocusLayer)
END_MESSAGE_MAP()


// CTransformDlg 메시지 처리기입니다.





void CTransformDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;

	CComponentDlg::PostNcDestroy();
}


void CTransformDlg::OnEnSetfocus(UINT _id)
{
	int iID = _id - 1001;
	m_bFocus[iID / 3][iID % 3] = true;

}

void CTransformDlg::OnEnKillfocus(UINT _id)
{
	int iID = _id - 1001;
	m_bFocus[iID / 3][iID % 3] = false;

}


void CTransformDlg::OnEnChange(UINT _id)
{
	if (NULL == m_pTargetObj) return;

	const int iID = _id - 1001;
	const UINT iFocusX = iID % 3;
	const UINT iFocusY = iID / 3;
	if (true == m_bFocus[iFocusY][iFocusX])
	{
		CString str;
		m_arrEdit[iFocusY][iFocusX].GetWindowTextW(str);

		float fOutput = (float)_wtof(str.GetBuffer());
		CTransform* pTrans = m_pTargetObj->Transform();

		const UINT iTranformID = iFocusX + iFocusY * 3;
		pTrans->SetTransform(iTranformID, fOutput);
	}
}

void CTransformDlg::OnEnSetfocusEditTag()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bFocusTag = true;
	m_editTag.SendMessage(EM_SETREADONLY, 0, 0);
}


void CTransformDlg::OnEnKillfocusEditTag()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bFocusTag = false;
	m_editTag.SendMessage(EM_SETREADONLY, 1, 0);
	CSceneMgr::GetInst()->SetUpdateCheck(true);
}


void CTransformDlg::OnEnChangeEditTag()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CComponentDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	if (NULL == m_pTargetObj) return;
	if (m_bFocusTag)
	{
		CString str;
		m_editTag.GetWindowTextW(str);

		m_pTargetObj->SetTag(str.GetBuffer());
		UpdateData(false);
	}
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTransformDlg::OnCbnSelchangeLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iIdx = m_cbLayer.GetCurSel();

	if (-1 == iIdx) return;
	CString str;
	m_cbLayer.GetLBText(iIdx, str);
	// layer 이름 변경.
	CScene*	pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->ChangeLayer(str.GetBuffer(), m_pTargetObj);

	UpdateData(false);
	::SetFocus(m_hWndOwner);
}


void CTransformDlg::OnCbnKillfocusLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bFocusLayer = false;
}


void CTransformDlg::OnCbnSetfocusLayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bFocusLayer = true;
}
