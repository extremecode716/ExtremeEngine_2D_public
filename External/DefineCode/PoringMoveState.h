#pragma once
#include "MonsterState.h"
class CPoringMoveState :
	public CMonsterState
{
private:
	wstring m_strUpWalk; 
	wstring m_strDownWalk;

public:
	void SetAnimationName(const wstring& _strUpWalk, const wstring& _strDownWalk);

public:
	virtual void Enter(CScript* _pScript) override;
	virtual void Execute(CScript* _pScript) override;
	virtual void Exit(CScript* _pScript) override;

public:
	CPoringMoveState(CScript* _pScript);
	virtual ~CPoringMoveState();
};

