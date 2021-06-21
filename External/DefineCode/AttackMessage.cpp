#include "stdafx.h"
#include "AttackMessage.h"
#include "GameObject.h"
#include "Transform.h"

CAttackMessage::CAttackMessage(const wstring& _strAttacker, int _totalDamage, CGameObject* _pAttackerObj)
	: m_strAttackerKey(_strAttacker)
	, m_iTotalDamage(_totalDamage)
	, m_pAttackerObj(_pAttackerObj)
{
	SetType(MessageType::ATTACK_MT);
}

Vec2 CAttackMessage::GetAttackerObjPos()
{
	return m_pAttackerObj->Transform()->GetLocal2DPos();
}

CAttackMessage::~CAttackMessage()
{
}

void CAttackMessage::SetAttack(const wstring& _strAttacker, int _totalDamage, CGameObject* _pAttackerObj)
{
	m_strAttackerKey = _strAttacker;
	m_iTotalDamage = _totalDamage;
	m_pAttackerObj = _pAttackerObj;
	SetType(MessageType::ATTACK_MT);
}
