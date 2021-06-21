#include "stdafx.h"
#include "ETCItemScript.h"

CETCItemScript::CETCItemScript()
{
}


CETCItemScript::~CETCItemScript()
{
}

void CETCItemScript::SetETCInfo(UINT _index, const wstring & _strType, UINT _iType, const wstring & _strName)
{
	m_iIdx = _index;
	m_strType = _strType;
	m_iType = _iType;
	m_strName = _strName;
}

void CETCItemScript::start()
{
	CItemScript::start();
}

int CETCItemScript::update()
{
	return RET_SUCCESS;
}

void CETCItemScript::OnCollisionEnter(CCollider * _pOther)
{
}

void CETCItemScript::OnCollisionExit(CCollider * _pOther)
{
}
