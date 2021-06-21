#include "stdafx.h"
#include "PoringStandingState.h"
#include "..\DefineCode\MonsterScript.h"


CPoringStandingState::CPoringStandingState(CScript* _pScript)
{
	m_pMonsterScript = dynamic_cast<CMonsterScript*>(_pScript);
}

CPoringStandingState::~CPoringStandingState()
{
}

void CPoringStandingState::SetAnimationName(const wstring & _strUpStanding, const wstring & _strDownStanding)
{
	m_strUpStanding = _strUpStanding;
	m_strDownStanding = _strDownStanding;
}

/*
함수명  : SetSearchIndex(int _iSearchX, int _iSearchY)
용도    : search 할 x y 값을 setting (default x = 1 , y = 1)
*/
void CPoringStandingState::SetSearchIndex(int _iSearchX, int _iSearchY)
{
	m_iSearchX = _iSearchX;
	m_iSearchY = _iSearchY;
}

void CPoringStandingState::Enter(CScript * _pScript)
{
	if (NULL == m_pMonsterScript) return;
	wstring strCurAnimKey = m_pMonsterScript->Animator()->GetCurAnimKey();
	int iFindKey = strCurAnimKey.find(L"Up");

	if (iFindKey > -1)
	{
		m_pMonsterScript->Animator()->PlayAnimation(m_strUpStanding);
	}
	else
	{
		m_pMonsterScript->Animator()->PlayAnimation(m_strDownStanding);
	}

}

void CPoringStandingState::Execute(CScript * _pScript)
{
	if (NULL == m_pMonsterScript) return;

	CGameObject* pAttackerObj = m_pMonsterScript->GetAttackerObj();

	if (pAttackerObj != NULL)
	{
		Vec2 vAttackerPos = pAttackerObj->Transform()->GetLocal2DPos();
		float fDistance = m_pMonsterScript->DistanceToPos(vAttackerPos);

		if (fDistance < 150.f)
		{
			m_pMonsterScript->ChangeState(L"ATTACK");
		}
		else if (fDistance > 1200.f) 
		{
			// 거리 제한!
			m_pMonsterScript->ResetAttackerObj();
			return;
		}
	}
	m_pMonsterScript->SearchPathUpdate(m_iSearchX, m_iSearchY, pAttackerObj);

	if (!m_pMonsterScript->GetStackPath().empty())
	{
		m_pMonsterScript->ChangeState(L"MOVE");
	}
	
}

void CPoringStandingState::Exit(CScript * _pScript)
{
	if (NULL == m_pMonsterScript) return;
}
