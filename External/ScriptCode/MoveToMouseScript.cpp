#include "stdafx.h"
#include "MoveToMouseScript.h"


CMoveToMouseScript::CMoveToMouseScript()
	: m_pParentObj(NULL)
	, m_strParentName(L"")
	, m_pMouseObj(NULL)
	, m_bCollMouse(false)
	, m_bClicked(false)
	, m_vOffsetPos{ 0.f, 0.f, 0.f}
{
}


CMoveToMouseScript::~CMoveToMouseScript()
{
}




void CMoveToMouseScript::OnCollisionEnter(CCollider * _pOther)
{
	if (false == GetGameObject()->GetEnable()) return;

}

void CMoveToMouseScript::OnCollision(CCollider * _pOther)
{
	if (false == GetGameObject()->GetEnable()) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bCollMouse = true;
	}
}

void CMoveToMouseScript::OnCollisionExit(CCollider * _pOther)
{
	if (false == GetGameObject()->GetEnable()) return;
	if (_pOther->GetGameObject()->GetTag() == L"MouseObj")
	{
		//m_bCollMouse = false;
	}
}

void CMoveToMouseScript::SetOffsetPos(const Vec3 & _vPos)
{
	m_vOffsetPos = _vPos;
}

void CMoveToMouseScript::SetParentName(const wstring & _strName)
{
	m_strParentName = _strName;
}

void CMoveToMouseScript::start()
{
	// 인벤토리 최상위 부모
	m_pParentObj = GetGameObject();
	while (m_pParentObj->HasParent())
	{
		if (m_pParentObj->GetTag() == m_strParentName)
			break;
		m_pParentObj = m_pParentObj->GetParentObj();
	}

	CScene*	pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->FindLayer(L"Mouse");
	m_pMouseObj = pLayer->FindWithTag(L"MouseObj");

}

int CMoveToMouseScript::update()
{
	if (false == GetGameObject()->GetEnable()) return RET_FAILED;

	if (true == m_bCollMouse)
	{
		if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_TAB))
		{
			m_bClicked = true;
			Vec3 vParentPos = m_pParentObj->Transform()->GetLocalPos();
			Vec3 vPos = m_pMouseObj->Transform()->GetLocalPos();
			m_vOffsetPos = vPos - vParentPos;
		}
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_AWAY))
	{
		m_bClicked = false;
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_HOLD))
	{
		if (true == m_bClicked)
		{
			Vec3 vMousePos = m_pMouseObj->Transform()->GetLocalPos();
			Vec3 vPos = vMousePos;
			vPos.x -= m_vOffsetPos.x;
			vPos.y -= m_vOffsetPos.y;
			vPos.z = 1.f;
			m_pParentObj->Transform()->SetLocalPos(vPos);
		}
	}

	m_bCollMouse = false;

	return 0;
}
