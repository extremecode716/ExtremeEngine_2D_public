#pragma once
#include "Message.h"

class CGameObject;
class CAttackMessage :
	public CMessage
{
private:
	wstring	m_strAttackerKey;
	int m_iTotalDamage;
	CGameObject* m_pAttackerObj;
	// + 속성 추가;

public:
	void SetAttack(const wstring& _strAttacker ,int _totalDamage, CGameObject* _pAttackerObj);
	int GetTotalDamage() const { return m_iTotalDamage; }
	const wstring& GetAttackerKey() const { return m_strAttackerKey; }
	CGameObject* GetAttackerObj() const { return m_pAttackerObj; }
	Vec2 GetAttackerObjPos();


public:
	CAttackMessage(const wstring& _strAttacker, int _totalDamage, CGameObject* _pAttackerObj);
	virtual ~CAttackMessage();
};

