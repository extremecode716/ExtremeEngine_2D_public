#include "stdafx.h"
#include "ItemScript.h"

CItemScript::CItemScript()
	: m_iIdx(0)
	, m_strType(L"")
	, m_strName(L"")
	, m_iType((UINT)ITEM_TYPE::ETC_TYPE)
	, m_pTransform(NULL)
	, m_iSlot(-1)
	, m_pItemMtrl(NULL)
	, m_pItemTex(NULL)
	, m_pSkill(NULL)
{
}


CItemScript::~CItemScript()
{
}

void CItemScript::SetItemMtrl(CMaterial * _pItemMtrl)
{
	m_pItemMtrl = _pItemMtrl;
}

void CItemScript::SetItemTex(CTexture * _pItemTex)
{
	if (NULL == m_pItemMtrl) return;
	m_pItemTex = _pItemTex;
	m_pItemMtrl->SetData(SHADER_PARAM::SP_TEX_0, &m_pItemTex);
}

bool CItemScript::Action(CScript * _pScript)
{
	if (NULL == m_pSkill) return false;
	
	m_pSkill->Action(_pScript);

	return true;
}

void CItemScript::SetObjPos(const Vec3 & _vPos)
{
	Transform()->SetLocalPos(_vPos);
}

void CItemScript::SetObjScale(const Vec3 & _vScale)
{
	Transform()->SetLocalScale(_vScale);
}

void CItemScript::start()
{
	Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	Transform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
}

int CItemScript::update()
{
	return RET_SUCCESS;
}
