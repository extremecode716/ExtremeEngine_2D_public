#include "stdafx.h"
#include "PoringMoveState.h"
#include "..\DefineCode\MonsterScript.h"

CPoringMoveState::CPoringMoveState(CScript* _pScript)
{
	m_pMonsterScript = dynamic_cast<CMonsterScript*>(_pScript);
}

CPoringMoveState::~CPoringMoveState()
{
}

void CPoringMoveState::SetAnimationName(const wstring & _strUpWalk, const wstring & _strDownWalk)
{
	m_strUpWalk = _strUpWalk;
	m_strDownWalk = _strDownWalk;
}

void CPoringMoveState::Enter(CScript * _pScript)
{
	if (NULL == m_pMonsterScript) return;

	wstring strCurAnimKey = m_pMonsterScript->Animator()->GetCurAnimKey();
	int iFindKey = strCurAnimKey.find(L"Up");

	if (iFindKey > -1)
	{
		m_pMonsterScript->Animator()->PlayAnimation(m_strUpWalk);
	}
	else
	{
		m_pMonsterScript->Animator()->PlayAnimation(m_strDownWalk);
	}
}

void CPoringMoveState::Execute(CScript * _pScript)
{
	if (NULL == m_pMonsterScript) return;

	Vec3 vCurPos = m_pMonsterScript->Transform()->GetLocalPos();
	float fMoveSpeed = m_pMonsterScript->GetMoveSpeed();
	float fDT = m_pMonsterScript->DT();

	bool bMove = false;
	while (!bMove)
	{
		bMove = true;
		if (!m_pMonsterScript->GetStackPath().empty())
		{
			tPathNode* pPathNode = m_pMonsterScript->GetStackPath().top();
			UINT PosXIndex = pPathNode->iIndexX;
			UINT PosYIndex = pPathNode->iIndexY;
			Vec2 vPos = m_pMonsterScript->GetTileMgr()->GetPosFromIndex(PosXIndex, PosYIndex, m_pMonsterScript->GetPivot());
			bMove = m_pMonsterScript->MoveToPos(vPos);
			if (!bMove)
			{
				m_pMonsterScript->GetStackPath().pop();
				SAFE_DELETE(pPathNode);
				continue;
			}
		}
	}

	Vec3 vScale = m_pMonsterScript->Transform()->GetLocalScale();
	m_pMonsterScript->DirUpdate();
	DIRECTION_8 eDir = m_pMonsterScript->GetDir();
	switch (eDir)
	{
	case DIRECTION_8::NONE:
		Exit(NULL);
		break;
	case DIRECTION_8::UP:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strUpWalk))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strUpWalk);
		}
		break;
	case DIRECTION_8::UPPERRIGHT:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strUpWalk))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strUpWalk);
		}
		if (vScale.x > 0)
		{
			vScale.x *= -1;
			m_pMonsterScript->Transform()->SetLocalScale(vScale);
		}
		break;
	case DIRECTION_8::RIGHT:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strDownWalk))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strDownWalk);
		}
		if (vScale.x > 0)
		{
			vScale.x *= -1;
			m_pMonsterScript->Transform()->SetLocalScale(vScale);
		}
		break;
	case DIRECTION_8::LOWERRIGHT:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strDownWalk))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strDownWalk);
		}
		if (vScale.x > 0)
		{
			vScale.x *= -1;
			m_pMonsterScript->Transform()->SetLocalScale(vScale);
		}
		break;
	case DIRECTION_8::DOWN:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strDownWalk))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strDownWalk);
		}
		break;
	case DIRECTION_8::LOWERLEFT:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strDownWalk))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strDownWalk);
		}
		if (vScale.x < 0)
		{
			vScale.x *= -1;
			m_pMonsterScript->Transform()->SetLocalScale(vScale);
		}
		break;
	case DIRECTION_8::LEFT:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strDownWalk))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strDownWalk);
		}
		if (vScale.x < 0)
		{
			vScale.x *= -1;
			m_pMonsterScript->Transform()->SetLocalScale(vScale);
		}
		break;
	case DIRECTION_8::UPPERLEFT:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strUpWalk))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strUpWalk);
		}
		if (vScale.x < 0)
		{
			vScale.x *= -1;
			m_pMonsterScript->Transform()->SetLocalScale(vScale);
		}
		break;
	default:
		break;
	}
}

void CPoringMoveState::Exit(CScript * _pScript)
{
	if (NULL == m_pMonsterScript) return;

	if (NULL == m_pMonsterScript->GetAttackerObj())
	{
		// 없을 경우
		m_pMonsterScript->ChangeState(L"STANDING");
	}
	else
	{
		// 공격대상자가 있을 경우
		m_pMonsterScript->ChangeState(L"ATTACK");
	}

}
