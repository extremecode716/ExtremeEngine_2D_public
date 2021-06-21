#pragma once
#include "FsmState.h"
#include "MonsterScript.h"

class CMonsterState :
	public CFsmState
{
protected:
	CMonsterScript*		m_pMonsterScript;

public:
	virtual void Enter(CScript* _pScript) override = 0;
	virtual void Execute(CScript* _pScript) override = 0;
	virtual void Exit(CScript* _pScript) override = 0;

public:
	CMonsterState();
	virtual ~CMonsterState();
};

