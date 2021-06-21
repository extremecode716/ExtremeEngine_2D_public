#include "stdafx.h"
#include "PlayerPickUpState.h"


CPlayerPickUpState::CPlayerPickUpState(CScript* _pScript)
{
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(_pScript);
}


CPlayerPickUpState::~CPlayerPickUpState()
{
}

void CPlayerPickUpState::Enter(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;

}

void CPlayerPickUpState::Execute(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;
}

void CPlayerPickUpState::Exit(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;
}
