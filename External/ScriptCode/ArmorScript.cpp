#include "stdafx.h"
#include "ArmorScript.h"


CArmorScript::CArmorScript()
{
}


CArmorScript::~CArmorScript()
{
}

void CArmorScript::SetArmorInfo(UINT _index, const wstring & _strType, UINT _iType, const wstring & _strName, int _iDefense)
{
	m_iIdx = _index;
	m_strType = _strType;
	m_iType = _iType;
	m_strName = _strName;
	m_tArmor.SetInfo(_strName, _iDefense);
}

void CArmorScript::start()
{
	CItemScript::start();
}

int CArmorScript::update()
{
	return RET_SUCCESS;
}

void CArmorScript::OnCollisionEnter(CCollider * _pOther)
{
}

void CArmorScript::OnCollisionExit(CCollider * _pOther)
{
}
