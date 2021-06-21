#pragma once
#include "Message.h"

class CGameObject;
class CFindMessage :
	public CMessage
{
private:
	wstring			m_strFindKey;
	Vec2			m_vFindPos;
	CGameObject*	m_pFindObj;

public:
	void SetFind(const wstring& _strKey, const Vec2& _vPos, CGameObject* _pObj = NULL);
	void SetPos(const Vec2& _vPos) { m_vFindPos = _vPos; }

	const wstring& GetFindKey() const { return m_strFindKey; }
	const Vec2& GetFindPos() const { return m_vFindPos; }
	CGameObject* GetFindObj() const { return m_pFindObj; }
	Vec2 GetFindObjPos();

public:
	CFindMessage(const wstring& _strKey, const Vec2& _vPos, CGameObject* _pObj = NULL);
	virtual ~CFindMessage();
};

