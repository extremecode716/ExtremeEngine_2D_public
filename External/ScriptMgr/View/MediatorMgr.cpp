#include "stdafx.h"
#include "MediatorMgr.h"

CMediatorMgr::CMediatorMgr()
{
}

CMediatorMgr::~CMediatorMgr()
{
	Safe_Delete_Map(m_mapColleauque);
	m_mapColleauque.clear();
}


CColleaque * CMediatorMgr::FindColleaque(const wstring& _strKey)
{
	map<wstring, CColleaque*>::iterator iter = m_mapColleauque.find(_strKey);
	if (iter == m_mapColleauque.end())
		return NULL;

	return iter->second;
}

bool CMediatorMgr::EraseCollq(const wstring & _strKey)
{
	map<wstring, CColleaque*>::iterator iter = m_mapColleauque.find(_strKey);
	
	if (iter == m_mapColleauque.end())
		return false;
	
	CColleaque* pCollq = iter->second;
	m_mapColleauque.erase(iter);
	SAFE_DELETE(pCollq);

	return true;
}

bool CMediatorMgr::AddColleaque(CColleaque * _collq)
{
	if (_collq == NULL) return false;

	m_mapColleauque.insert(make_pair(_collq->GetName(), _collq));
	return true;
}



void CMediatorMgr::Mediate(const wstring& _strSrc, CMessage* _pData)
{
	map<wstring, CColleaque*>::iterator iter = m_mapColleauque.begin();

	for (; iter != m_mapColleauque.end(); ++iter)
	{
		iter->second->Handle(_strSrc, _pData);
	}
}

void CMediatorMgr::Mediate_Find(const wstring & _strSrc, const wstring& _strDest, CMessage* _pData)
{
	map<wstring, CColleaque*>::iterator iter = m_mapColleauque.begin();

	for (; iter != m_mapColleauque.end(); ++iter)
	{
		int iFindKey = iter->second->GetName().find(_strDest);
		if (iFindKey > -1)
			iter->second->Handle(_strSrc, _pData);
	}
}

void CMediatorMgr::Mediate_ExceptMe(const wstring& _strSrc, CMessage* _pData)
{
	map<wstring, CColleaque*>::iterator iter = m_mapColleauque.begin();

	for (; iter != m_mapColleauque.end(); ++iter)
	{
		if (_strSrc == iter->second->GetName()) continue;
		iter->second->Handle(_strSrc, _pData);
	}
}

void CMediatorMgr::Mediate(const wstring& _strSrc, const wstring& _strDest, CMessage* _pData)
{
	map<wstring, CColleaque*>::iterator iter = m_mapColleauque.find(_strDest);

	if (iter == m_mapColleauque.end())
	{
		SAFE_DELETE(_pData);
		return;
	}
	iter->second->Handle(_strSrc, _pData);
}
