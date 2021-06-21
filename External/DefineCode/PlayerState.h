#pragma once
#include "FsmState.h"
#include "..\External\ScriptCode\PlayerScript.h"

#include "MonsterScript.h"

class CPlayerState :
	public CFsmState
{
protected:
	CPlayerScript*		m_pPlayerScript;

public:
	virtual void Enter(CScript* _pScript) = 0;
	virtual void Execute(CScript* _pScript) = 0;
	virtual void Exit(CScript* _pScript) = 0;

public:
	CPlayerState();
	virtual ~CPlayerState();
};

