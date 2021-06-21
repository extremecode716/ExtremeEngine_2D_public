#include "stdafx.h"
#include "PlayerMoveState.h"
#include "..\External\ScriptCode\\PlayerScript.h"

CPlayerMoveState::CPlayerMoveState(CScript* _pScript)
	: m_bAstar(false)
{
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(_pScript);
}


CPlayerMoveState::~CPlayerMoveState()
{
}

void CPlayerMoveState::Enter(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;

	if (L"MOVE" == m_strKey)
	{
		SAFE_DELETE(m_pPlayerScript->m_pFindMsg);
	}
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
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpWalk_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"UpWalk_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpWalk_Y1Head");
		}
		break;
	case DIRECTION_8::UPPERRIGHT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftWalk_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftWalk_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftWalk_Y1Head");
		}
		break;
	case DIRECTION_8::RIGHT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LeftWalk_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LeftWalk_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LeftWalk_Y1Head");
		}
		break;
	case DIRECTION_8::LOWERRIGHT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftWalk_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftWalk_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftWalk_Y1Head");
		}
		break;
	case DIRECTION_8::DOWN:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"DownWalk_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"DownWalk_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"DownWalk_Y1Head");
		}
		break;
	case DIRECTION_8::LOWERLEFT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftWalk_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftWalk_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftWalk_Y1Head");
		}
		break;
	case DIRECTION_8::LEFT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LeftWalk_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"LeftWalk_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LeftWalk_Y1Head");
		}
		break;
	case DIRECTION_8::UPPERLEFT:
		if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftWalk_Thief"))
		{
			m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftWalk_Thief");
			m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftWalk_Y1Head");
		}
		break;
	default:
		break;
	}



}

void CPlayerMoveState::Execute(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;

	Vec3 vScale = m_pPlayerScript->Transform()->GetLocalScale();
	Vec3 vCurPos = m_pPlayerScript->Transform()->GetLocalPos();
	float fMoveSpeed = m_pPlayerScript->GetMoveSpeed();
	float fDT = m_pPlayerScript->DT();


	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D, KEY_STATE::STATE_HOLD) &&
		CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W, KEY_STATE::STATE_HOLD))
	{
		vCurPos.x += fMoveSpeed * 0.75f * fDT;
		vCurPos.y += fMoveSpeed * 0.75f * fDT;
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D, KEY_STATE::STATE_HOLD) &&
		CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_S, KEY_STATE::STATE_HOLD))
	{
		vCurPos.x += fMoveSpeed * 0.75f * fDT;
		vCurPos.y -= fMoveSpeed * 0.75f * fDT;
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A, KEY_STATE::STATE_HOLD) &&
		CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W, KEY_STATE::STATE_HOLD))
	{
		vCurPos.x -= fMoveSpeed * 0.75f * fDT;
		vCurPos.y += fMoveSpeed * 0.75f * fDT;
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A, KEY_STATE::STATE_HOLD) &&
		CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_S, KEY_STATE::STATE_HOLD))
	{
		vCurPos.x -= fMoveSpeed * 0.75f * fDT;
		vCurPos.y -= fMoveSpeed * 0.75f * fDT;
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A, KEY_STATE::STATE_HOLD))
	{
		vCurPos.x -= fMoveSpeed * fDT;
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D, KEY_STATE::STATE_HOLD))
	{
		vCurPos.x += fMoveSpeed * fDT;
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W, KEY_STATE::STATE_HOLD))
	{
		vCurPos.y += fMoveSpeed * fDT;
		m_pPlayerScript->ChangeState(L"MOVE");
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_S, KEY_STATE::STATE_HOLD))
	{
		vCurPos.y -= fMoveSpeed * fDT;
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
			SAFE_DELETE(m_pPlayerScript->m_pFindMsg);
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
							SAFE_DELETE(m_pPlayerScript->m_pFindMsg);
						}
					}
				}
			}
		}
	}

	m_pPlayerScript->Transform()->SetLocalPos(vCurPos);

	DIRECTION_8 eDir;
	if (L"MOVE_POS" == m_strKey)
	{
		if (NULL == m_pPlayerScript->m_pMonster)
		{
			eDir = m_pPlayerScript->GetDirectionToPos(m_pPlayerScript->m_vMousePos);
		}
		else
		{
			eDir = m_pPlayerScript->GetDirectionToPos(m_pPlayerScript->m_pMonster->Transform()->GetLocal2DPos());
		}

		switch (eDir)
		{
		case DIRECTION_8::NONE:
			if (NULL == m_pPlayerScript->m_pMonster)
			{
				m_pPlayerScript->ChangeState(L"STANDING");
			}
			else
			{
				m_pPlayerScript->ChangeState(L"ATTACK");
			}
			break;
		case DIRECTION_8::UP:
			vCurPos.y += fMoveSpeed * fDT;
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"UpWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpWalk_Y1Head");
			}
			break;
		case DIRECTION_8::UPPERRIGHT:
			vCurPos.y += fMoveSpeed * 0.75f * fDT;
			vCurPos.x += fMoveSpeed * 0.75f * fDT;
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftWalk_Y1Head");
			}
			if (vScale.x > 0)
			{
				vScale.x *= -1;
				m_pPlayerScript->Transform()->SetLocalScale(vScale);
			}
			break;
		case DIRECTION_8::RIGHT:
			vCurPos.x += fMoveSpeed * fDT;
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LeftWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"LeftWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LeftWalk_Y1Head");
			}
			if (vScale.x > 0)
			{
				vScale.x *= -1;
				m_pPlayerScript->Transform()->SetLocalScale(vScale);
			}
			break;
		case DIRECTION_8::LOWERRIGHT:
			vCurPos.y -= fMoveSpeed * 0.75f * fDT;
			vCurPos.x += fMoveSpeed * 0.75f * fDT;
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftWalk_Y1Head");
			}
			if (vScale.x > 0)
			{
				vScale.x *= -1;
				m_pPlayerScript->Transform()->SetLocalScale(vScale);
			}
			break;
		case DIRECTION_8::DOWN:
			vCurPos.y -= fMoveSpeed * fDT;
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"DownWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"DownWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"DownWalk_Y1Head");
			}
			break;
		case DIRECTION_8::LOWERLEFT:
			vCurPos.y -= fMoveSpeed * 0.75f * fDT;
			vCurPos.x -= fMoveSpeed * 0.75f * fDT;
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftWalk_Y1Head");
			}
			if (vScale.x < 0)
			{
				vScale.x *= -1;
				m_pPlayerScript->Transform()->SetLocalScale(vScale);
			}
			break;
		case DIRECTION_8::LEFT:
			vCurPos.x -= fMoveSpeed * fDT;
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LeftWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"LeftWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LeftWalk_Y1Head");
			}
			if (vScale.x < 0)
			{
				vScale.x *= -1;
				m_pPlayerScript->Transform()->SetLocalScale(vScale);
			}
			break;
		case DIRECTION_8::UPPERLEFT:
			vCurPos.y += fMoveSpeed * 0.75f * fDT;
			vCurPos.x -= fMoveSpeed * 0.75f * fDT;
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftWalk_Y1Head");
			}
			if (vScale.x < 0)
			{
				vScale.x *= -1;
				m_pPlayerScript->Transform()->SetLocalScale(vScale);
			}
			break;
		default:
			break;
		}
		m_pPlayerScript->Transform()->SetLocalPos(vCurPos);
	}
	else
	{
		bool bMove = false;
		while (!bMove)
		{
			bMove = true;
			if (!m_pPlayerScript->m_stackPath.empty())
			{
				tPathNode* pPathNode = m_pPlayerScript->m_stackPath.top();
				UINT PosXIndex = pPathNode->iIndexX;
				UINT PosYIndex = pPathNode->iIndexY;
				Vec2 vPos = m_pPlayerScript->m_pTileMgrScript->GetPosFromIndex(PosXIndex, PosYIndex);
				bMove = m_pPlayerScript->MoveToPos(vPos);
				if (!bMove)
				{
					m_pPlayerScript->m_stackPath.pop();
					SAFE_DELETE(pPathNode);
					continue;
				}
			}
		}

		m_pPlayerScript->DirUpdate();
		eDir = m_pPlayerScript->GetDir();

		switch (eDir)
		{
		case DIRECTION_8::NONE:
			if (m_pPlayerScript->m_pMonster == NULL)
			{
				m_pPlayerScript->ChangeState(L"STANDING");
			}
			else
			{
				m_pPlayerScript->ChangeState(L"MOVE_POS");
			}
			break;
		case DIRECTION_8::UP:
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"UpWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpWalk_Y1Head");
			}
			break;
		case DIRECTION_8::UPPERRIGHT:
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpperLeftWalk_Y1Head");
			}
			if (vScale.x > 0)
			{
				vScale.x *= -1;
				m_pPlayerScript->Transform()->SetLocalScale(vScale);
			}
			break;
		case DIRECTION_8::RIGHT:
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LeftWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"LeftWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LeftWalk_Y1Head");
			}
			if (vScale.x > 0)
			{
				vScale.x *= -1;
				m_pPlayerScript->Transform()->SetLocalScale(vScale);
			}
			break;
		case DIRECTION_8::LOWERRIGHT:
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftWalk_Y1Head");
			}
			if (vScale.x > 0)
			{
				vScale.x *= -1;
				m_pPlayerScript->Transform()->SetLocalScale(vScale);
			}
			break;
		case DIRECTION_8::DOWN:
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"DownWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"DownWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"DownWalk_Y1Head");
			}
			break;
		case DIRECTION_8::LOWERLEFT:
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LowerLeftWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"LowerLeftWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LowerLeftWalk_Y1Head");
			}
			if (vScale.x < 0)
			{
				vScale.x *= -1;
				m_pPlayerScript->Transform()->SetLocalScale(vScale);
			}
			break;
		case DIRECTION_8::LEFT:
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"LeftWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"LeftWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"LeftWalk_Y1Head");
			}
			if (vScale.x < 0)
			{
				vScale.x *= -1;
				m_pPlayerScript->Transform()->SetLocalScale(vScale);
			}
			break;
		case DIRECTION_8::UPPERLEFT:
			if (!m_pPlayerScript->Animator()->IsPlayAnimation(L"UpperLeftWalk_Thief"))
			{
				m_pPlayerScript->Animator()->PlayAnimation(L"UpperLeftWalk_Thief");
				m_pPlayerScript->m_pHeadObj->Animator()->PlayAnimation(L"UpWalk_Y1Head");
			}
			if (vScale.x < 0)
			{
				vScale.x *= -1;
				m_pPlayerScript->Transform()->SetLocalScale(vScale);
			}
			break;
		default:
			break;
		}
	}
}

void CPlayerMoveState::Exit(CScript* _pScript)
{
	if (NULL == m_pPlayerScript) return;
}
