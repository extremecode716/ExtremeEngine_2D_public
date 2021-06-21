#pragma once
#include "State.h"

class CFsmState :
	public CState
{	

public:
	virtual void Enter(CScript* _pScript) override = 0;
	virtual void Execute(CScript* _pScript) override = 0;
	virtual void Exit(CScript* _pScript) override = 0;

public:
	CFsmState();
	virtual ~CFsmState();
};

