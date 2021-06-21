#include "stdafx.h"
#include "PlayerIdleState.h"

CPlayerIdleState::CPlayerIdleState(CScript* _pScript)
{
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(_pScript);
}


CPlayerIdleState::~CPlayerIdleState()
{
}


void CPlayerIdleState::Enter(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;
	if (L"IDLE" == m_strKey)
	{
		m_pPlayerScript->Animator()->PlayAnimation(L"DownStading_Thief");
	}
}

void CPlayerIdleState::Execute(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;
}

void CPlayerIdleState::Exit(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;
}