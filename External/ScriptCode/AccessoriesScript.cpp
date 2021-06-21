#include "stdafx.h"
#include "AccessoriesScript.h"

void CAccessoriesScript::SetAccInfo(UINT _index, const wstring & _strType, UINT _iType, const wstring & _strName, int _iDamage, int _iDefense)
{
	m_iIdx = _index;
	m_strType = _strType;
	m_iType = _iType;
	m_strName = _strName;
	m_tAccInfo.SetInfo(_strName, _iDamage, _iDefense);
}

void CAccessoriesScript::start()
{
	CItemScript::start();
}

int CAccessoriesScript::update()
{
	return RET_SUCCESS;
}

void CAccessoriesScript::OnCollisionEnter(CCollider * _pOther)
{
}

void CAccessoriesScript::OnCollisionExit(CCollider * _pOther)
{
}

CAccessoriesScript::CAccessoriesScript()
{
}

CAccessoriesScript::~CAccessoriesScript()
{
}
