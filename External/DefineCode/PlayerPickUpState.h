#pragma once
#include "PlayerState.h"

class CPlayerPickUpState :
	public CPlayerState
{
public:
	virtual void Enter(CScript* _pScript) override;
	virtual void Execute(CScript* _pScript) override;
	virtual void Exit(CScript* _pScript) override;

public:
	CPlayerPickUpState(CScript* _pScript);
	virtual ~CPlayerPickUpState();
};

