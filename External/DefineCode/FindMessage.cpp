#include "stdafx.h"
#include "FindMessage.h"
#include "GameObject.h"
#include "Transform.h"

CFindMessage::CFindMessage(const wstring & _strKey, const Vec2& _vPos, CGameObject* _pObj)
	: m_strFindKey(_strKey)
	, m_vFindPos(_vPos)
	, m_pFindObj(_pObj)
{
	SetType(MessageType::FIND_MT);
}


CFindMessage::~CFindMessage()
{
}

void CFindMessage::SetFind(const wstring & _strKey, const Vec2& _vPos, CGameObject* _pObj)
{
	m_strFindKey = _strKey;
	m_vFindPos = _vPos;
	m_pFindObj = _pObj;
	SetType(MessageType::FIND_MT);
}

Vec2 CFindMessage::GetFindObjPos()
{
	if (NULL == m_pFindObj)
		return m_vFindPos;

	return m_pFindObj->Transform()->GetLocal2DPos();
}
