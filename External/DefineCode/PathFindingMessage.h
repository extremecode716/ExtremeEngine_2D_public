#pragma once
#include "Message.h"

class CGameObject;
class CPathFindingMessage :
	public CMessage
{
private:
	// ã�� ��
	wstring		            m_strSeekerKey;
	Vec2		            m_vSeekerPos;
	CGameObject*	        m_pSeekerObj;

	// ã�� ��
	wstring			        m_strFindKey;
	Vec2			        m_vFindPos;
	CGameObject*	        m_pFindObj;


	// ã�� ����ġ�� ������ �����ش�. (swap������ ��)
	stack<tPathNode*>		m_stackPathFinding;

public:
	void SetSeeker(const wstring& _strSeekerKey, const Vec2& _vSeekerPos, CGameObject* _pSeekerObj = NULL);
	void SetFind(const wstring& _strFindKey, const Vec2& _vFindPos, CGameObject* _pFindObj = NULL);

	const wstring& GetSeekerKey() const { return m_strSeekerKey; }
	const Vec2& GetSeekerPos() const { return m_vSeekerPos; }

	const wstring& GetFindKey() const { return m_strFindKey; }
	const Vec2& GetFindPos() const { return m_vFindPos; }

	bool SetPathFinding(stack<tPathNode*>& _stackPath);
	const stack<tPathNode*>& GetPathFinding() const { return m_stackPathFinding; }

public:
	CPathFindingMessage(const wstring& _strSeekerKey, const Vec2& _vSeekerPos, 
		const wstring& _strFindKey, const Vec2& _vFindPos, 
		CGameObject* _pSeekerObj = NULL ,CGameObject* _pFindObj = NULL);
	virtual ~CPathFindingMessage();
};

