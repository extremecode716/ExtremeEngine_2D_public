#pragma once
#include "PlayerState.h"
class CPlayerDieState :
	public CPlayerState
{
public:
	virtual void Enter(CScript* _pScript) override;
	virtual void Execute(CScript* _pScript) override;
	virtual void Exit(CScript* _pScript) override;

public:
	CPlayerDieState(CScript* _pScript);
	virtual ~CPlayerDieState();
};

