#include "stdafx.h"
#include "StateMgr.h"


CStateMgr::CStateMgr()
	: m_pPreState(NULL)
	, m_pCurState(NULL)
{
}


CStateMgr::~CStateMgr()
{
	Safe_Delete_Map(m_mapSate);
}


void CStateMgr::SetCurState(CState * _pState)
{
	m_pCurState = _pState;
}


wstring CStateMgr::GetCurStateKey()
{
	if (m_pCurState == NULL) return L"";
	return m_pCurState->GetKey();
}

wstring CStateMgr::GetPreStateKey()
{
	if (m_pPreState == NULL) return L"";
	return m_pPreState->GetKey();
}

CState * CStateMgr::GetCurState()
{
	if (NULL == m_pCurState) return NULL;
	return m_pCurState;
}

CState* CStateMgr::AddState(const wstring & _strKey, CState* _state)
{
	bool bState = IsFindState(_strKey);
	if (bState) return NULL;

	_state->SetKey(_strKey);
	m_mapSate.insert(make_pair(_strKey, _state));

	return _state;
}

bool CStateMgr::ChangeState(const wstring & _strKey)
{
	CState* pState = FindState(_strKey);
	if (NULL == pState) return false;
	if (m_pCurState == pState) return false;
	if (NULL != m_pCurState)
	{
		if (!m_pCurState->IsFindNextKey(_strKey)) return false;
	}

	m_pPreState = m_pCurState;
	m_pCurState = pState;
	//if (NULL != m_pPreState)
	//{
	//	m_pPreState->Exit();
	//}
	m_pCurState->Enter();
	return true;
}

//bool CStateMgr::ChangeState(const wstring & _strKey)
//{
//	CState* pState = FindState(_strKey);
//	if (NULL == pState) return false;
//	if (m_pCurState == pState) return false;
//
//	m_pPreState = m_pCurState;
//	m_pCurState = pState;
//	if (NULL != m_pPreState)
//	{
//		m_pPreState->Exit();
//	}
//	m_pCurState->Enter();
//	return true;
//}

bool CStateMgr::ChangePreState(const wstring & _strKey)
{
	CState* pState = FindState(_strKey);
	if (NULL == pState) return false;
	if (m_pPreState == pState) return false;
	m_pPreState = pState;

	return true;
}

bool CStateMgr::IsFindState(const wstring & _strKey)
{
	map<wstring, CState*>::iterator iter = m_mapSate.find(_strKey);

	if (iter == m_mapSate.end())
		return false;
	return true;
}

CState * CStateMgr::FindState(const wstring & _strKey)
{
	map<wstring, CState*>::iterator iter = m_mapSate.find(_strKey);

	if (iter == m_mapSate.end())
		return NULL;
	return iter->second;
}
