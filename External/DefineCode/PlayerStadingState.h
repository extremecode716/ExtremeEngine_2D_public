#pragma once
#include "PlayerState.h"

class CPlayerStadingState :
	public CPlayerState
{
public:
	virtual void Enter(CScript* _pScript) override;
	virtual void Execute(CScript* _pScript) override;
	virtual void Exit(CScript* _pScript) override;

public:
	CPlayerStadingState(CScript* _pScript);
	virtual ~CPlayerStadingState();
};

