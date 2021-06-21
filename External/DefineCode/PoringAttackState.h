#pragma once
#include "MonsterState.h"

class CPoringAttackState :
	public CMonsterState
{
private:
	bool  m_bAttack;
	wstring m_strAttackerName;
	CGameObject* m_pAttackerObj;

	float m_fAttackTempTime;

	wstring m_strUpAttack;
	wstring m_strDownAttack;

public:
	void SetAnimationName(const wstring& _strUpAttack, const wstring& _strDownAttack);

public:
	virtual void Enter(CScript* _pScript) override;
	virtual void Execute(CScript* _pScript) override;
	virtual void Exit(CScript* _pScript) override;

public:
	CPoringAttackState(CScript* _pScript);
	virtual ~CPoringAttackState();
};

