#pragma once
#include "PlayerState.h"
class CPlayerIdleState :
	public CPlayerState
{
public:
	virtual void Enter(CScript* _pScript) override;
	virtual void Execute(CScript* _pScript) override;
	virtual void Exit(CScript* _pScript) override;

public:
	CPlayerIdleState(CScript* _pScript);
	virtual ~CPlayerIdleState();
};

