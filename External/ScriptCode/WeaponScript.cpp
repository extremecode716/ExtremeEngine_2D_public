#include "stdafx.h"
#include "WeaponScript.h"

CWeaponScript::CWeaponScript()
{
}


CWeaponScript::~CWeaponScript()
{
}

void CWeaponScript::SetWeaponInfo(UINT _index, const wstring & _strType, UINT _iType, const wstring& _strName, float _fRange, int _iDamage, float _fSpeed)
{
	m_iIdx = _index;
	m_strType = _strType;
	m_iType = _iType;
	m_strName = _strName;
	m_tWeapon.SetInfo(_strName, _fRange, _iDamage, _fSpeed);
}

void CWeaponScript::start()
{
	CItemScript::start();
}

int CWeaponScript::update()
{
	return RET_SUCCESS;
}

void CWeaponScript::OnCollisionEnter(CCollider * _pOther)
{
}

void CWeaponScript::OnCollisionExit(CCollider * _pOther)
{
}
