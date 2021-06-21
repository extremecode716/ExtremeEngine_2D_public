#include "stdafx.h"
#include "PlayerStadingState.h"

CPlayerStadingState::CPlayerStadingState(CScript* _pScript)
{
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(_pScript);
}


CPlayerStadingState::~CPlayerStadingState()
{
}


void CPlayerStadingState::Enter(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;

	if (NULL != m_pPlayerScript->m_pWeaponObj)
	{
		m_pPlayerScript->m_pWeaponObj->SetEnable(false);
	}
	DIRECTION_8 ePreDir = m_pPlayerScript->GetPreDirection();

	switch (ePreDir)
	{
	case DIRECTION_8::NONE:
		break;
	case DIRECTION_8::UP:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpStading_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"UpStading_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpStanding_Y1Head");
		}
		break;
	case DIRECTION_8::UPPERRIGHT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftStading_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftStading_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftStanding_Y1Head");
		}
		break;
	case DIRECTION_8::RIGHT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LeftStading_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LeftStading_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LeftStanding_Y1Head");
		}
		break;
	case DIRECTION_8::LOWERRIGHT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftStading_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftStading_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftStanding_Y1Head");
		}
		break;
	case DIRECTION_8::DOWN:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"DownStading_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"DownStading_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"DownStanding_Y1Head");
		}
		break;
	case DIRECTION_8::LOWERLEFT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftStading_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftStading_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftStanding_Y1Head");
		}
		break;
	case DIRECTION_8::LEFT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LeftStading_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LeftStading_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LeftStanding_Y1Head");
		}
		break;
	case DIRECTION_8::UPPERLEFT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftStading_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftStading_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftStanding_Y1Head");
		}
		break;
	default:
		break;
	}
}

void CPlayerStadingState::Execute(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;

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
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D, KEY_STATE::STATE_HOLD))
	{
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A, KEY_STATE::STATE_HOLD))
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

		//CMouseScript::GetInst()->GetMousePos();
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

}

void CPlayerStadingState::Exit(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;
}
