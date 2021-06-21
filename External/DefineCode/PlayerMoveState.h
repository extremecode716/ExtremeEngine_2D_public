#pragma once
#include "PlayerState.h"
class CPlayerMoveState :
	public CPlayerState
{
private:
	bool m_bAstar;

public:
	virtual void Enter(CScript* _pScript) override;
	virtual void Execute(CScript* _pScript) override;
	virtual void Exit(CScript* _pScript) override;

public:
	CPlayerMoveState(CScript* _pScript);
	virtual ~CPlayerMoveState();
};

