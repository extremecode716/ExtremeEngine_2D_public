// ColliderDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "ColliderDlg.h"
#include "afxdialogex.h"


// CColliderDlg ��ȭ �����Դϴ�.
#include "GameObject.h"
#include "Collider.h"

#include "KeyMgr.h"

IMPLEMENT_DYNAMIC(CColliderDlg, CDialogEx)

CColliderDlg::CColliderDlg(CWnd* pParent /*=NULL*/)
	: CComponentDlg(IDD_COLLIDERDLG, pParent)
{

}

CColliderDlg::~CColliderDlg()
{
}

void CColliderDlg::UpdateComponent(CGameObject * _pObj)
{
	m_pTargetObj = _pObj;
	if (NULL == m_pTargetObj)
		return;

	CCollider* pColTrans = m_pTargetObj->Collider();
	Vec3 vTransform[2] = { pColTrans->GetOffsetPos() , pColTrans->GetOffsetScale() };
	CString str;

	for (int i = 0; i < 2; ++i)
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

void CColliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	int iStartID = IDC_OFFSET_X;

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			DDX_Control(pDX, iStartID++, m_arrEdit[i][j]);
		}
	}
}



BEGIN_MESSAGE_MAP(CColliderDlg, CDialogEx)
	ON_CONTROL_RANGE(EN_SETFOCUS, IDC_OFFSET_X, IDC_SIZE_Z, &CColliderDlg::OnEnSetfocus)
	ON_CONTROL_RANGE(EN_KILLFOCUS, IDC_OFFSET_X, IDC_SIZE_Z, &CColliderDlg::OnEnKillfocus)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_OFFSET_X, IDC_SIZE_Z, &CColliderDlg::OnEnChange)
	ON_BN_CLICKED(IDC_BUTTON3, &CColliderDlg::OnSubComponentBnClicked)
END_MESSAGE_MAP()


// CColliderDlg �޽��� ó�����Դϴ�.

void CColliderDlg::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	delete this;

	CComponentDlg::PostNcDestroy();
}

void CColliderDlg::OnEnSetfocus(UINT _id)
{
	int iID = _id - 1001;
	m_bFocus[iID / 3][iID % 3] = true;
}

void CColliderDlg::OnEnKillfocus(UINT _id)
{
	int iID = _id - 1001;
	m_bFocus[iID / 3][iID % 3] = false;
}


void CColliderDlg::OnEnChange(UINT _id)
{
	if (NULL == m_pTargetObj)
		return;
	const int iID = _id - 1001;
	const UINT iFocusX = iID % 3;
	const UINT iFocusY = iID / 3;
	if (true == m_bFocus[iFocusY][iFocusX])
	{
		CString str;
		m_arrEdit[iFocusY][iFocusX].GetWindowTextW(str);

		float fOutput = (float)_wtof(str.GetBuffer());
		CCollider* pColTrans = m_pTargetObj->Collider();

		const UINT iColliderID = iFocusX + iFocusY * 3;
		pColTrans->SetOffset(iColliderID, fOutput);
	}
}




void CColliderDlg::OnSubComponentBnClicked()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (NULL == m_pTargetObj)
		return;
	m_pTargetObj->SubComponent<CCollider>();
}
