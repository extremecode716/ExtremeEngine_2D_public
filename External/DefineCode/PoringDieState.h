#pragma once
#include "MonsterState.h"
class CPoringDieState :
	public CMonsterState
{
private:
	wstring m_strUpDie;
	wstring m_strDownDie;

private:
	float m_fDelay;
	float m_fMaxDelay;

public:
	void SetAnimationName(const wstring& _strUpDie, const wstring& _strDownDie);

public:
	virtual void Enter(CScript* _pScript) override;
	virtual void Execute(CScript* _pScript) override;
	virtual void Exit(CScript* _pScript) override;

public:
	CPoringDieState(CScript* _pScript);
	virtual ~CPoringDieState();
};

