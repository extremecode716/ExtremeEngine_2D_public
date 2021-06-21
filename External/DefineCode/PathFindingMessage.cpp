#include "stdafx.h"
#include "PathFindingMessage.h"

CPathFindingMessage::CPathFindingMessage(const wstring & _strSeekerKey, const Vec2 & _vSeekerPos, const wstring & _strFindKey, const Vec2 & _vFindPos, CGameObject * _pSeekerObj, CGameObject * _pFindObj)
	: m_strSeekerKey(_strSeekerKey)
	, m_vSeekerPos(_vSeekerPos)
	, m_pSeekerObj(_pSeekerObj)
	, m_strFindKey(_strFindKey)
	, m_vFindPos(_vFindPos)
	, m_pFindObj(_pFindObj)
{
	SetType(MessageType::PATHFIND_MT);
}

CPathFindingMessage::~CPathFindingMessage()
{
}

/*
�Լ���  : SetPathFinding
�뵵    : Astar���� ���� path�� �ֻ��� ��θ� message�� ��η� move �����ش�. (����! move)
�Ű�����: (stack<tPathNode*>& _stackPath)
��ȯ    : bool
����    : �赿�� (2018.04.14)
*/
bool CPathFindingMessage::SetPathFinding(stack<tPathNode*>& _stackPath)
{
	if (_stackPath.empty()) return false;
	Safe_Delete_Stack(m_stackPathFinding);
	m_stackPathFinding = std::move(_stackPath);

	return true;
}


void CPathFindingMessage::SetSeeker(const wstring& _strSeekerKey, const Vec2& _vSeekerPos, CGameObject* _pSeekerObj)
{
	m_strSeekerKey = _strSeekerKey;
	m_vSeekerPos = _vSeekerPos;
	m_pSeekerObj = _pSeekerObj;
	SetType(MessageType::PATHFIND_MT);
}

void CPathFindingMessage::SetFind(const wstring& _strFindKey, const Vec2& _vFindPos, CGameObject* _pFindObj)
{
	m_strFindKey = _strFindKey;
	m_vFindPos = _vFindPos;
	m_pFindObj = _pFindObj;
	SetType(MessageType::PATHFIND_MT);
}
