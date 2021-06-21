#pragma once
#include "PlayerState.h"

class CPlayerAttackState :
	public CPlayerState
{
private:
	bool	m_bAttack;
	wstring m_strMonsterName;
	CGameObject* m_pMonsterObj;

public:
	virtual void Enter(CScript* _pScript) override;
	virtual void Execute(CScript* _pScript) override;
	virtual void Exit(CScript* _pScript) override;

public:
	CPlayerAttackState(CScript* _pScript);
	virtual ~CPlayerAttackState();
};

