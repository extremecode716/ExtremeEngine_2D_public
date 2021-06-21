#include "stdafx.h"
#include "PoringDieState.h"
#include "..\DefineCode\MonsterScript.h"

#include "DieMessage.h"

CPoringDieState::CPoringDieState(CScript* _pScript)
	: m_fDelay(0.f)
	, m_fMaxDelay(3.f)
{
	m_pMonsterScript = dynamic_cast<CMonsterScript*>(_pScript);
}

CPoringDieState::~CPoringDieState()
{
}

void CPoringDieState::SetAnimationName(const wstring & _strUpDie, const wstring & _strDownDie)
{
	m_strUpDie = _strUpDie;
	m_strDownDie = _strDownDie;
}

void CPoringDieState::Enter(CScript * _pScript)
{
	if (NULL == m_pMonsterScript) return;

	wstring strCurAnimKey = m_pMonsterScript->Animator()->GetCurAnimKey();
	int iFindKey = strCurAnimKey.find(L"Up");

	if (iFindKey > -1)
	{
		m_pMonsterScript->Animator()->PlayAnimation(m_strUpDie, false);
	}
	else
	{
		m_pMonsterScript->Animator()->PlayAnimation(m_strDownDie, false);
	}

	CCollider* pCollider = m_pMonsterScript->Collider();
	if (pCollider != NULL)
	{
		pCollider->SetEnable(false);
	}
	m_pMonsterScript->SoundEffectPlay((int)STATE::DIYING);

	// Player Notify
	CDieMessage* pMsg = new CDieMessage(m_pMonsterScript->GetCollqName(), m_pMonsterScript->GetGameObject());
	m_pMonsterScript->GetCollq()->SendData(m_pMonsterScript->GetAttackerObj()->GetTag(), pMsg);
}

void CPoringDieState::Execute(CScript * _pScript)
{
	if (NULL == m_pMonsterScript) return;

	m_fDelay += m_pMonsterScript->DT();

	if (m_fDelay >= m_fMaxDelay)
	{
		m_fDelay = 0.f;
		// 실행 종료
		m_pMonsterScript->GetGameObject()->SetActive(false);
		m_pMonsterScript->Reset();
		
		// RespawnMgr Notify
		CDieMessage* pMsg = new CDieMessage(m_pMonsterScript->GetCollqName(), m_pMonsterScript->GetGameObject());
		m_pMonsterScript->GetCollq()->SendData(m_pMonsterScript->GetRespawnCollqName(), pMsg);

	}

}

void CPoringDieState::Exit(CScript * _pScript)
{
	if (NULL == m_pMonsterScript) return;
}