#include "stdafx.h"
#include "PoringAttackState.h"
#include "..\ScriptCode\MonsterScript_Poring.h"

#include "RandomScript.h"
#include "..\ScriptCode\Critical.h"
#include "..\ScriptCode\Damage.h"

#include "AttackMessage.h"
#include "..\ScriptMgr\View\TileMgrScript.h"


CPoringAttackState::CPoringAttackState(CScript* _pScript)
	: m_bAttack(false)
	, m_strAttackerName(L"")
	, m_pAttackerObj(NULL)
	, m_fAttackTempTime(0.f)
{
	m_pMonsterScript = dynamic_cast<CMonsterScript*>(_pScript);
}


CPoringAttackState::~CPoringAttackState()
{
}

void CPoringAttackState::SetAnimationName(const wstring & _strUpAttack, const wstring & _strDownAttack)
{
	m_strUpAttack = _strUpAttack;
	m_strDownAttack = _strDownAttack;
}

void CPoringAttackState::Enter(CScript * _pScript)
{
	if (NULL == m_pMonsterScript) return;

	wstring strCurAnimKey = m_pMonsterScript->Animator()->GetCurAnimKey();
	int iFindKey = strCurAnimKey.find(L"Up");

	if (iFindKey > -1)
	{
		m_pMonsterScript->Animator()->PlayAnimation(m_strUpAttack);
	}
	else
	{
		m_pMonsterScript->Animator()->PlayAnimation(L"DownWalk_Poring");
	}
}

void CPoringAttackState::Execute(CScript * _pScript)
{
	if (NULL == m_pMonsterScript) return;

	DIRECTION_8 ePreDir = m_pMonsterScript->GetPreDirection();

	switch (ePreDir)
	{
	case DIRECTION_8::NONE:
		break;
	case DIRECTION_8::UP:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strUpAttack))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strUpAttack);
		}
		break;
	case DIRECTION_8::UPPERRIGHT:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strUpAttack))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strUpAttack);
		}
		break;
	case DIRECTION_8::RIGHT:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strDownAttack))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strDownAttack);

		}
		break;
	case DIRECTION_8::LOWERRIGHT:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strDownAttack))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strDownAttack);
		}
		break;
	case DIRECTION_8::DOWN:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strDownAttack))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strDownAttack);
		}
		break;
	case DIRECTION_8::LOWERLEFT:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strDownAttack))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strDownAttack);
		}
		break;
	case DIRECTION_8::LEFT:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strDownAttack))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strDownAttack);
		}
		break;
	case DIRECTION_8::UPPERLEFT:
		if (!m_pMonsterScript->Animator()->IsPlayAnimation(m_strUpAttack))
		{
			m_pMonsterScript->Animator()->PlayAnimation(m_strUpAttack);
		}
		break;
	default:
		break;
	}

	Vec3 vScale = m_pMonsterScript->Transform()->GetLocalScale();
	m_pAttackerObj = m_pMonsterScript->GetAttackerObj();
	m_strAttackerName = m_pAttackerObj->GetTag();
	Vec2 vAttackerPos = m_pAttackerObj->Transform()->GetLocal2DPos();
	Vec2 vPos = m_pMonsterScript->Transform()->GetLocal2DPos();
	tStatus& tStat = m_pMonsterScript->GetStatus();
	
	float fDistance = m_pMonsterScript->DistanceToPos(vAttackerPos);

	if (fDistance < 150.f)
	{

	}
	else
	{
		m_pMonsterScript->ChangeState(L"STANDING");
	}


	UINT iAnimFrameIdx = m_pMonsterScript->Animator()->GetCurAnim()->GetFrameIdx();
	UINT iAnimMaxFrameIdx = m_pMonsterScript->Animator()->GetCurAnim()->GetMaxFrameIdx() - 1;

	if (iAnimFrameIdx == iAnimMaxFrameIdx)
	{
		if (false == m_bAttack)
		{
			int iRandomDamage = GameRandom::RandomInt(m_pMonsterScript->GetMinDamage(), m_pMonsterScript->GetMaxDamage());

			CMessage* pMsg = new CAttackMessage(m_pMonsterScript->GetCollqName(), iRandomDamage, m_pMonsterScript->GetGameObject());
			m_pMonsterScript->GetCollq()->SendData(m_strAttackerName, pMsg);

			m_pMonsterScript->SoundEffectPlay((int)STATE::ATTACK);

			Vec3 vEffPos = Vec3(vAttackerPos.x, vAttackerPos.y, 81.f);
			if (NULL != m_pMonsterScript->GetEffectDamage())
			{
				vEffPos.z = 79.f;
				CGameObject* pClone = m_pMonsterScript->Instantiate(m_pMonsterScript->GetEffectDamage(), vEffPos, L"Default");
				if (vScale.x > 0)
				{
					pClone->Script<CDamage>()->SetStartRot(Vec3(0.f, 0.f, 1.9f));
				}
				else
				{
					pClone->Script<CDamage>()->SetStartRot(Vec3(0.f, 0.f, 1.2f));
				}

				pClone->Script<CDamage>()->SetDamage(iRandomDamage);
				pClone->start();
			}

			m_bAttack = true;
		}
	}
	else
	{
		m_bAttack = false;
	}

}

void CPoringAttackState::Exit(CScript * _pScript)
{
	if (NULL == m_pMonsterScript) return;
}