#include "stdafx.h"
#include "State.h"

CState::CState()
{
}

CState::~CState()
{
}

void CState::InsertNextKey(const set<wstring>& _setNextKey)
{
	m_setNextKey.insert(_setNextKey.begin(), _setNextKey.end());
}

bool CState::IsFindNextKey(const wstring & _strKey)
{
	set<wstring>::iterator iter = m_setNextKey.find(_strKey);
	if (iter == m_setNextKey.end())
		return false;

	return true;
}
