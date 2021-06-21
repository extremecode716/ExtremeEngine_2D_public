#include "stdafx.h"
#include "MonsterScript_Deviling.h"

#include "..\DefineCode\PoringAttackState.h"
#include "..\DefineCode\PoringDieState.h"
#include "..\DefineCode\PoringMoveState.h"
#include "..\DefineCode\PoringStandingState.h"

#include "..\DefineCode\FindMessage.h"
#include "..\DefineCode\AttackMessage.h"
#include "..\DefineCode\DieMessage.h"

CMonsterScript_Deviling::CMonsterScript_Deviling()
{
}


CMonsterScript_Deviling::~CMonsterScript_Deviling()
{
}

void CMonsterScript_Deviling::start()
{
	CMonsterScript::start();
	////////////////////
	// Monster Setting
	////////////////////
	m_fMoveSpeed = 250.f;
	m_pTransform = Transform();
	//m_pTransform->SetLocalPos(Vec3(1500.f, 500.f, 99.f));
	m_pTransform->SetLocalScale(Vec3(200.f, 200.f, 1.f));
	m_vPrePos = m_vCurPos;
	m_vCurPos = m_pTransform->GetLocalPos();
	SetAggressiveType(MONSTER_AGGRESSIVE_TYPE::NON_AGGRESSIVE_TYPE);

	m_pTileMgr = CTileMgrScript::GetThis();
	m_IsMove = false;
	m_ePreDir = DIRECTION_8::DOWN;
	SetSearchTime(3.f);

	// Stat
	m_fAttackRange = 50.f;
	tStatus* pStatus = CMonsterTable::GetThis()->FindMonsterStatus(L"Deviling");
	if (NULL != pStatus)
	{
		m_tStatus = *pStatus;
		m_iMinDamage = 100;
		m_iMaxDamage = 200;
	}
	else
	{
		assert(NULL);
	}


	// Mediator
	m_pMediator = CMediatorMgr::GetInst();
	m_pCollq_Monster = CMessageColleaque::Create(m_pMediator, m_strCollqName, this);

	/////////////////
	// State Setting
	/////////////////
	m_pStateMgr = new CStateMgr;
	CState* pState = NULL;
	set<wstring> setStandardKey = { L"STANDING", L"MOVE", L"DIE", L"ATTACK" };

	// STADING
	CPoringStandingState* pStandingState = new CPoringStandingState(this);
	pStandingState->SetAnimationName(L"UpStanding_Deviling", L"DownStanding_Deviling");
	pStandingState->SetSearchIndex(1, 1);
	pState = m_pStateMgr->AddState(L"STANDING", pStandingState);
	if (pState)
		pState->InsertNextKey(setStandardKey);
	// Move
	CPoringMoveState* pMoveState = new CPoringMoveState(this);
	pMoveState->SetAnimationName(L"UpWalk_Deviling", L"DownWalk_Deviling");
	pState = m_pStateMgr->AddState(L"MOVE", pMoveState);
	if (pState)
		pState->InsertNextKey(setStandardKey);
	// DIE
	CPoringDieState* pDieState = new CPoringDieState(this);
	pDieState->SetAnimationName(L"UpDying_Deviling", L"DownDying_Deviling");
	pState = m_pStateMgr->AddState(L"DIE", pDieState);
	if (pState)
		pState->InsertNextKey(setStandardKey);
	// Attack
	CPoringAttackState* pAttackState = new CPoringAttackState(this);
	pAttackState->SetAnimationName(L"UpWalk_Deviling", L"DownWalk_Deviling");
	pState = m_pStateMgr->AddState(L"ATTACK", pAttackState);
	if (pState)
		pState->InsertNextKey(setStandardKey);

	Animator()->PlayAnimation(L"DownStanding_Deviling");
	m_pStateMgr->ChangeState(L"STANDING");
}


int CMonsterScript_Deviling::update()
{
	float fDT = DT();
	m_fSurvivalTime += fDT;
	m_vPrePos = m_vCurPos;
	m_vCurPos = Transform()->GetLocalPos();

	KeyInput();

	if (m_tStatus.iHP < 0)
	{
		m_bDie = true;
		ChangeState(L"DIE");
	}

	// 상태 업데이트
	StateExecute();

	return RET_SUCCESS;
}

void CMonsterScript_Deviling::KeyInput()
{
}

void CMonsterScript_Deviling::StateExecute()
{
	CState* pCurState = m_pStateMgr->GetCurState();
	if (NULL == pCurState) return;
	m_pStateMgr->GetCurState()->Execute();
}

void CMonsterScript_Deviling::Reset()
{
	CMonsterScript::Reset();
	tStatus* pStatus = CMonsterTable::GetThis()->FindMonsterStatus(L"Deviling");
	if (NULL != pStatus)
	{
		m_tStatus = *pStatus;
	}
	else
	{
		assert(NULL);
	}
	m_bDie = false;
	m_pStateMgr->ChangeState(L"STANDING");
	m_pAttackerObj = NULL;
	Safe_Delete_Stack(m_stackPath);
}

void CMonsterScript_Deviling::SoundEffectPlay(const int _idx)
{
	STATE eState = (STATE)_idx;
	CSound*	pSound = NULL;
	switch (eState)
	{
	case STATE::DIYING:
		pSound = CResMgr::GetInst()->FindSound(L"poring_die");
		if (NULL != pSound)
		{
			pSound->Play(1);
		}
		break;
	case STATE::ATTACK:
		pSound = CResMgr::GetInst()->FindSound(L"poring_attack");
		if (NULL != pSound)
		{
			pSound->Play(1);
		}
		break;
	case STATE::WALKING:
		break;
	case STATE::DAMAGE:
		pSound = CResMgr::GetInst()->FindSound(L"poring_damage");
		if (NULL != pSound)
		{
			pSound->Play(1);
		}
		break;
	default:
		break;
	}
}

void CMonsterScript_Deviling::GetMessageData(CMessage * _pData)
{
	MessageType eType = _pData->GetType();

	switch (eType)
	{
	case MessageType::NONE_MT:
		break;
	case MessageType::ATTACK_MT:
	{
		CAttackMessage* pAttackMt = static_cast<CAttackMessage*>(_pData);
		m_bHit = true;
		m_pAttackerObj = pAttackMt->GetAttackerObj();
		m_tStatus.iHP -= pAttackMt->GetTotalDamage();
		SoundEffectPlay((int)STATE::DAMAGE);
		//CDebugMgr::GetInst()->Log(m_tStatus.iHP);

		SAFE_DELETE(pAttackMt);
	}
	break;
	case MessageType::FIND_MT:
	{
	}
	break;
	case MessageType::PATHFIND_MT:
	{
		CPathFindingMessage* pPathFindMt = static_cast<CPathFindingMessage*>(_pData);

		Safe_Delete_Stack(m_stackPath);
		m_pTileMgr = CTileMgrScript::GetThis();
		m_stackPath = std::move(pPathFindMt->GetPathFinding());
		SAFE_DELETE(pPathFindMt);
	}
	break;
	case MessageType::ERROR_MT:
		SAFE_DELETE(_pData);
		break;
	default:
		SAFE_DELETE(_pData);
		break;
	}
}

