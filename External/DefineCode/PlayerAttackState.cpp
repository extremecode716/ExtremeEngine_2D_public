#include "stdafx.h"
#include "PlayerAttackState.h"

#include "RandomScript.h"
#include "..\ScriptCode\Critical.h"
#include "..\ScriptCode\Damage.h"
#include "MonsterScript.h"

CPlayerAttackState::CPlayerAttackState(CScript* _pScript)
	: m_bAttack(false)
	, m_strMonsterName(L"")
	, m_pMonsterObj(NULL)
{
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(_pScript);
}


CPlayerAttackState::~CPlayerAttackState()
{
}

void CPlayerAttackState::Enter(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;

	m_pPlayerScript->m_pWeaponObj->SetEnable(true);

	DIRECTION_8 ePreDir = m_pPlayerScript->GetPreDirection();

	switch (ePreDir)
	{
	case DIRECTION_8::NONE:
		break;
	case DIRECTION_8::UP:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"UpperDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::UPPERRIGHT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"UpperDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::RIGHT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"LowerDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::LOWERRIGHT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"LowerDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::DOWN:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"LowerDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::LOWERLEFT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"LowerDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::LEFT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"LowerDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::UPPERLEFT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"UpperDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftDagger_Y1Head");
		}
		break;
	default:
		break;
	}
}

void CPlayerAttackState::Execute(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;
	DIRECTION_8 ePreDir = m_pPlayerScript->GetPreDirection();

	switch (ePreDir)
	{
	case DIRECTION_8::NONE:
		break;
	case DIRECTION_8::UP:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"UpperDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::UPPERRIGHT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"UpperDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::RIGHT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"LowerDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::LOWERRIGHT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"LowerDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::DOWN:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"LowerDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::LOWERLEFT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"LowerDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::LEFT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"LowerDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftDagger_Y1Head");
		}
		break;
	case DIRECTION_8::UPPERLEFT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftMeleeAttack2_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftMeleeAttack2_Thief");
			m_pPlayerScript->m_pWeaponObj->Animator()->PlayAnimation(L"UpperDagger");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftDagger_Y1Head");
		}
		break;
	default:
		break;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D, KEY_STATE::STATE_HOLD) &&
		CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W, KEY_STATE::STATE_HOLD))
	{
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D, KEY_STATE::STATE_HOLD) &&
		CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_S, KEY_STATE::STATE_HOLD))
	{
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A, KEY_STATE::STATE_HOLD) &&
		CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W, KEY_STATE::STATE_HOLD))
	{
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A, KEY_STATE::STATE_HOLD) &&
		CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_S, KEY_STATE::STATE_HOLD))
	{
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A, KEY_STATE::STATE_HOLD))
	{
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D, KEY_STATE::STATE_HOLD))
	{
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W, KEY_STATE::STATE_HOLD))
	{
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_S, KEY_STATE::STATE_HOLD))
	{
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (!m_pPlayerScript->m_stackPath.empty())
	{
		m_pPlayerScript->ChangeState(L"MOVE");
	}

	// 메세지 처리
	if (NULL != m_pPlayerScript->m_pFindMsg)
	{
		m_pPlayerScript->m_vMousePos = m_pPlayerScript->m_pFindMsg->GetFindObjPos();

		if (L"Ground" == m_pPlayerScript->m_pFindMsg->GetFindKey())
		{
			m_pPlayerScript->m_pMonster = NULL;
			m_pPlayerScript->ChangeState(L"MOVE_POS");
		}
		else if (L"Astar" == m_pPlayerScript->m_pFindMsg->GetFindKey())
		{
			m_pPlayerScript->m_pMonster = NULL;
			Vec2 vCurPos = m_pPlayerScript->Transform()->GetLocal2DPos();
			CMessage* pMsg = new CPathFindingMessage(m_pPlayerScript->GetCollqName(), vCurPos, L"Astar", m_pPlayerScript->m_vMousePos);
			m_pPlayerScript->m_pCollq_Player->SendData(L"AstarMgr", pMsg);
			m_pPlayerScript->ChangeState(L"MOVE");
		}
		else
		{
			int iMonster = m_pPlayerScript->m_pFindMsg->GetFindKey().find(L"Monster");
			if (iMonster > -1)
			{
				CGameObject* pMonster = m_pPlayerScript->m_pFindMsg->GetFindObj();
				if (NULL != pMonster)
				{
					CMonsterScript* pMonsterScript = pMonster->Script<CMonsterScript>();
					if (NULL != pMonsterScript)
					{
						bool bDie = pMonsterScript->IsDie();
						if (false == bDie)
						{
							m_pPlayerScript->m_pMonster = m_pPlayerScript->m_pFindMsg->GetFindObj();
							Vec2 vCurPos = m_pPlayerScript->Transform()->GetLocal2DPos();
							CMessage* pMsg = new CPathFindingMessage(m_pPlayerScript->GetCollqName(), vCurPos, L"Astar", m_pPlayerScript->m_vMousePos);
							m_pPlayerScript->m_pCollq_Player->SendData(L"AstarMgr", pMsg);
							m_pPlayerScript->ChangeState(L"MOVE");
						}
					}
				}
			}
		}
	}

	Vec2 vPos = m_pPlayerScript->Transform()->GetLocal2DPos();
	Vec3 vScale = m_pPlayerScript->Transform()->GetLocalScale();
	UINT iAnimFrameIdx = m_pPlayerScript->Animator()->GetCurAnim()->GetFrameIdx();
	UINT iAnimMaxFrameIdx = m_pPlayerScript->Animator()->GetCurAnim()->GetMaxFrameIdx() - 1;

	if (NULL != m_pPlayerScript->m_pMonster)
	{
		m_strMonsterName = m_pPlayerScript->m_pMonster->GetTag(); // 태그로 찾음 문제
		m_pMonsterObj = m_pPlayerScript->m_pMonster;

		Vec2 vMonsterPos = m_pMonsterObj->Transform()->GetLocal2DPos();

		float fDistance = m_pPlayerScript->DistanceToPos(vMonsterPos);

		// 거리에 따라 공격/이동 판단
		if (fDistance < 150.f)
		{

		}
		else
		{
			CMessage* pMsg = new CFindMessage(m_strMonsterName, vMonsterPos, m_pMonsterObj);
			m_pPlayerScript->m_pCollq_Player->SendData(L"Player", pMsg);
			m_pPlayerScript->ChangeState(L"STANDING");
		}

		if (iAnimFrameIdx == iAnimMaxFrameIdx)
		{
			if (false == m_bAttack)
			{
				// sound random
				int idx = GameRandom::RandomInt(0, 3);
				m_pPlayerScript->SoundEffectPlay(idx);

				int iMinDamage = m_pPlayerScript->m_iMinDamage;
				int iMaxDamage = m_pPlayerScript->m_iMaxDamage;
				int iRandomDamage = GameRandom::RandomInt(iMinDamage, iMaxDamage);

				CMessage* pMsg = new CAttackMessage(m_pPlayerScript->GetCollqName(), iRandomDamage, m_pPlayerScript->GetGameObject());
				m_pPlayerScript->m_pCollq_Player->SendData(m_strMonsterName, pMsg);

				Vec3 vEffPos = Vec3(m_pMonsterObj->Transform()->GetLocalPos().x, m_pMonsterObj->Transform()->GetLocalPos().y, 80.f);
				if (NULL != m_pPlayerScript->m_pEffect_Damage)
				{
					vEffPos.z = 79.f;
					CGameObject* pClone = m_pPlayerScript->Instantiate(m_pPlayerScript->m_pEffect_Damage,
						vEffPos, L"Default");
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

				if (NULL != m_pPlayerScript->m_pEffect_Critical)
				{
					vEffPos.z = 80.f;
					CGameObject* pClone = m_pPlayerScript->Instantiate(m_pPlayerScript->m_pEffect_Critical,
						vEffPos, L"Default");
					if (vScale.x > 0)
					{
						pClone->Script<CCritical>()->SetStartRot(Vec3(0.f, 0.f, 1.9f));
					}
					else
					{
						pClone->Script<CCritical>()->SetStartRot(Vec3(0.f, 0.f, 1.2f));
					}
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
	else
	{
		m_pPlayerScript->ChangeState(L"STANDING");
	}
}

void CPlayerAttackState::Exit(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;

}