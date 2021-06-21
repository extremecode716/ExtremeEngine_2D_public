#include "stdafx.h"
#include "PlayerDieState.h"


CPlayerDieState::CPlayerDieState(CScript* _pScript)
{
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(_pScript);
}


CPlayerDieState::~CPlayerDieState()
{
}

void CPlayerDieState::Enter(CScript* _pScript)
{
	if (NULL == _pScript) return;

}

void CPlayerDieState::Execute(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;
}

void CPlayerDieState::Exit(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;
}
