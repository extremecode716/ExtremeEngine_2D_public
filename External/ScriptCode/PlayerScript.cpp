#include "stdafx.h"
#include "PlayerScript.h"

#include "DefineCode\BulletScript.h"
#include "BasicBulletScript.h"
#include "MissileBulletScript.h"
#include "ParabolaBulletScript.h"
#include "RevolveBulletScript.h"

#include "Scene.h"
#include "Layer.h"
#include "SceneMgr.h"

#include "RandomScript.h"

#include "..\DefineCode\\PlayerIdleState.h"
#include "..\DefineCode\PlayerMoveState.h"
#include "..\DefineCode\PlayerAttackState.h"
#include "..\DefineCode\PlayerDieState.h"
#include "..\DefineCode\PlayerPickUpState.h"
#include "..\DefineCode\PlayerStadingState.h"
#include "..\ScriptMgr\View\MouseScript.h"

#include "UIMgr.h"
#include "GaugeScript.h"

//임시
#include "..\ScriptMgr\View\SceneTable.h"

CPlayerScript::CPlayerScript()
	: m_eState(PLAYER_STATE::STATE_NONE)
	, m_fSurvivalTime(0.f)
	, m_fTempTime(0.f)
	, m_fMoveSpeed(100.f)
	, m_fRotSpeed(XM_PI)
	, m_pStateMgr(NULL)
	, m_pMediator(NULL)
	, m_pCollq_Player(NULL)
	, m_pWeaponObj(NULL)
	, m_pUIMgr(NULL)
	, m_bMove(false)
	, m_eDir(DIRECTION_8::NONE)
	, m_ePreDir(DIRECTION_8::NONE)
	, m_vCurPos{ 0.f, 0.f, 0.f }
	, m_vPrePos{ 0.f, 0.f, 0.f }
	, m_vMousePos{ 0.f, 0.f }
	, m_pFindMsg(NULL)
	, m_pMonster(NULL)
	, m_pEffect_Critical(NULL)
	, m_pEffect_Damage(NULL)
	, m_iMinDamage(100)
	, m_iMaxDamage(1000)
	, m_pHPScript(NULL)
	, m_pSPScript(NULL)
{
}

CPlayerScript::~CPlayerScript()
{
	Safe_Delete_Stack(m_stackPath);
	SAFE_DELETE(m_pStateMgr);
	SAFE_DELETE(m_pFindMsg);
}

void CPlayerScript::start()
{
	////////////////
	// Dont Destory
	///////////////
	static bool bDont = false;
	if (bDont == true) return;
	CSceneMgr::GetInst()->DontDestroyOnLoad(GetGameObject());
	bDont = true;

	////////////////////
	// Player Setting
	////////////////////
	m_eState = PLAYER_STATE::STATE_START;
	m_fMoveSpeed = 250.f;
	m_pTransform = Transform();
	m_pTransform->SetLocalPos(Vec3(1000.f, 0.f, 90.f));
	m_pTransform->SetLocalScale(Vec3(200.f, 200.f, 1.f));

	// Stat
	m_tStatus.SetStatus(10, 50000, 50000, 50000, 50000, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 250, 0);

	m_pEffect_Critical = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Effect_Critical(Prefab)");
	m_pEffect_Damage = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Effect_Damage(Prefab)");

	// Mediator
	m_pMediator = CMediatorMgr::GetInst();
	m_strCollqName = L"Player";
	m_pCollq_Player = CMessageColleaque::Create(m_pMediator, m_strCollqName, this);

	/////////////////
	// State Setting
	/////////////////
	m_pStateMgr = new CStateMgr;
	CState* pState = NULL;
	set<wstring> setStandardKey = { L"IDLE", L"STANDING", L"MOVE_POS" ,L"MOVE", L"DIE" , L"ATTACK" };
	// IDLE
	pState = m_pStateMgr->AddState(L"IDLE", new CPlayerIdleState(this));
	if (pState)
		pState->InsertNextKey(setStandardKey);
	// STADING
	pState = m_pStateMgr->AddState(L"STANDING", new CPlayerStadingState(this));
	if (pState)
		pState->InsertNextKey(setStandardKey);
	// MOVE
	pState = m_pStateMgr->AddState(L"MOVE_POS", new CPlayerMoveState(this));
	if (pState)
		pState->InsertNextKey(setStandardKey);
	pState = m_pStateMgr->AddState(L"MOVE", new CPlayerMoveState(this));
	if (pState)
		pState->InsertNextKey(setStandardKey);
	// DIE
	pState = m_pStateMgr->AddState(L"DIE", new CPlayerDieState(this));
	if (pState)
		pState->InsertNextKey(setStandardKey);
	// ATTACK
	pState = m_pStateMgr->AddState(L"ATTACK", new CPlayerAttackState(this));
	if (pState)
		pState->InsertNextKey(setStandardKey);

	// 기본 셋팅
	m_ePreDir = DIRECTION_8::DOWN;
	Animator()->PlayAnimation(L"DownStading_Thief");
	m_pStateMgr->ChangeState(L"STANDING");

	// 장비 //찾는 방식 맘에 안듦 나중에 수정요망
	CScene*	pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->FindLayer(GetGameObject()->GetLayerName());
	m_pWeaponObj = pLayer->FindWithTag(L"Weapon");
	m_pWeaponObj->SetEnable(false);

	m_pHeadObj = pLayer->FindWithTag(L"Head");
	m_pHeadObj->Animator()->PlayAnimation(L"DownStanding_Y1Head");

	m_pHeadObj->Animator()->GetCurAnim()->SetAnimTerm(Animator()->GetCurAnim()->GetAnimTerm());
	m_pWeaponObj->Animator()->GetCurAnim()->SetAnimTerm(Animator()->GetCurAnim()->GetAnimTerm());


	// UIMgr 셋팅
	CGameObject* pUIMgrObj = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->FindWithTag(L"UIMgrObject");
	if (pUIMgrObj != NULL)
	{
		m_pUIMgr= pUIMgrObj->Script<CUIMgr>();
	}

	m_pHPScript = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->FindWithTag(L"UI_HP")->Script<CGaugeScript>();
	m_pHPScript->SetGauge(m_tStatus.iMaxHP, m_tStatus.iHP);
	m_pHPScript->SetGaugeText(L"HP", Vec2(0.f, 0.f));

	m_pSPScript = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->FindWithTag(L"UI_SP")->Script<CGaugeScript>();
	m_pSPScript->SetGauge(m_tStatus.iMaxMP, m_tStatus.iMP);
	m_pSPScript->SetGaugeText(L"SP", Vec2(0.f, 0.f));

}

void CPlayerScript::InputKey()
{
	// 프론테라로 워프
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_ENTER, KEY_STATE::STATE_TAB))
	{
		Safe_Delete_Stack(m_stackPath);
		// prontera
		CSceneTable::GetInst()->ChangeScene(L"prontera");
	}
}

void CPlayerScript::Recovery(const wstring & _strType, int _iRecovery)
{
	if (_strType == L"HP")
	{
		m_tStatus.iHP += _iRecovery;
		m_tStatus.iHP = (m_tStatus.iHP >= m_tStatus.iMaxHP) ? m_tStatus.iMaxHP : m_tStatus.iHP;
		m_pHPScript->SetGauge(m_tStatus.iMaxHP, m_tStatus.iHP);
	}
	else if (_strType == L"SP")
	{
		m_tStatus.iMP += _iRecovery;
		m_tStatus.iMP = (m_tStatus.iMP >= m_tStatus.iMaxMP) ? m_tStatus.iMaxMP : m_tStatus.iHP;
		m_pSPScript->SetGauge(m_tStatus.iMaxMP, m_tStatus.iMP);
	}
}

int CPlayerScript::update()
{
	float fDT = DT();
	m_fSurvivalTime += fDT;
	
	Vec3 vPos = m_pTransform->GetLocalPos();
	Vec3 vRot = m_pTransform->GetLocalRot();
	Vec3 vScale = m_pTransform->GetLocalScale();
	m_vPrePos = m_vCurPos;
	m_vCurPos = vPos;

	///////////////////
	// Player Control
	///////////////////
	m_pHeadObj->Animator()->GetCurAnim()->SetAnimTerm(Animator()->GetCurAnim()->GetAnimTerm());
	m_pWeaponObj->Animator()->GetCurAnim()->SetAnimTerm(Animator()->GetCurAnim()->GetAnimTerm());

	InputKey();

	//m_pTransform->SetLocalPos(vPos);
	//m_pTransform->SetLocalRot(vRot);

	// 상태 업데이트
	StateExecute();
	DirUpdate();

	return RET_SUCCESS;
}


void CPlayerScript::GetMessageData(CMessage* _pData)
{
	if (NULL == _pData) return;
	MessageType eType = _pData->GetType();

	switch (eType)
	{
	case MessageType::NONE_MT:
		break;
	case MessageType::ATTACK_MT:
	{
		CAttackMessage* pAttackMt = static_cast<CAttackMessage*>(_pData);
		m_tStatus.iHP -= pAttackMt->GetTotalDamage();
		m_tStatus.iHP = (m_tStatus.iHP < 0) ? 0 : m_tStatus.iHP;

		m_pHPScript->SetGauge(m_tStatus.iMaxHP, m_tStatus.iHP);
		//CDebugMgr::GetInst()->Log(m_tStatus.iHP);

		SAFE_DELETE(pAttackMt);
	}
	break;
	case MessageType::FIND_MT:
	{
		SAFE_DELETE(m_pFindMsg);
		CFindMessage* pFindMt = static_cast<CFindMessage*>(_pData);
		m_pFindMsg = pFindMt;

		// 인벤토리가 열려있으면 찾는 메세지 다 지워버려!
		if (m_pUIMgr->IsInvenOpen() == true)
		{
			SAFE_DELETE(m_pFindMsg);
		}
		//CDebugMgr::GetInst()->Log(pFindMt->GetFindKey());
	}
	break;
	case MessageType::PATHFIND_MT:
	{
		CPathFindingMessage* pPathFindMt = static_cast<CPathFindingMessage*>(_pData);

		Safe_Delete_Stack(m_stackPath);
		m_pTileMgrScript = CTileMgrScript::GetThis();
		m_stackPath = std::move(pPathFindMt->GetPathFinding());
		SAFE_DELETE(pPathFindMt);
	}
	break;
	case MessageType::DIE_MT:
	{
		CDieMessage* pDieMt = static_cast<CDieMessage*>(_pData);

		CGameObject* pDieObj = pDieMt->GetDieObj();
		if (m_pMonster == pDieObj)
		{
			m_pMonster = NULL;
		}

		SAFE_DELETE(pDieMt);
	}
	break;
	case MessageType::ERROR_MT:
		SAFE_DELETE(_pData);
		break;
	default:
		break;
	}
}

void CPlayerScript::Reset()
{
	Safe_Delete_Stack(m_stackPath);
	m_pMonster = NULL;
}

bool CPlayerScript::IsMove()
{
	if (m_vCurPos == m_vPrePos)
		return false;
	return true;
}

float CPlayerScript::DistanceToPos(const Vec2 & _vPos)
{
	Vec2 vPos = _vPos;
	Vec2 vCurPos = Transform()->GetLocal2DPos();
	float fDist = Vec2(vPos - vCurPos).Distance();
	return fDist;
}


float CPlayerScript::GetAngleToPos(const Vec2& _vPos)
{
	Vec2 vPos = _vPos;
	Vec2 vDir = (vPos - Vec2(m_vCurPos.x, m_vCurPos.y));
	vDir.Normalize();
	float fAngle = atan2f(vDir.x, vDir.y) * 180.f / XM_PI;
	fAngle = (fAngle >= 0) ? fAngle : fAngle + 360.f;

	return fAngle;
}

float CPlayerScript::GetMoveAngle()
{
	Vec3 vDir = (m_vCurPos - m_vPrePos);
	vDir.Normalize();
	float fAngle = atan2f(vDir.x, vDir.y) * 180.f / XM_PI;
	fAngle = (fAngle >= 0) ? fAngle : fAngle + 360.f;

	return fAngle;
}

DIRECTION_8 CPlayerScript::GetDirectionToPos(const Vec2 & _vPos)
{
	static float fTempTime = 0.5f;
	float fMaxDelayTime = 0.5f;

	if (m_eDir == DIRECTION_8::NONE)
	{
		fTempTime = fMaxDelayTime;
	}
	else if (DistanceToPos(_vPos) <= 30.0f)
	{
		fTempTime = fMaxDelayTime;
		SAFE_DELETE(m_pFindMsg);
		return DIRECTION_8::NONE;
	}

	fTempTime += DT();
	if (fTempTime < fMaxDelayTime)
	{
		return m_ePreDir;
	}
	else
	{
		fTempTime = 0;
	}
	
	DIRECTION_8 vDir = DIRECTION_8::NONE;
	float fAngle = GetAngleToPos(_vPos);

	// 45도 8분할
	if (fAngle >= 337.5f || fAngle < 22.5f)        // ↑
	{
		vDir = DIRECTION_8::UP;
	}
	else if (fAngle >= 22.5f && fAngle < 67.5f)    // ↗
	{
		vDir = DIRECTION_8::UPPERRIGHT;
	}
	else if (fAngle >= 67.5f && fAngle < 112.5f)   // →
	{
		vDir = DIRECTION_8::RIGHT;
	}
	else if (fAngle >= 112.5f && fAngle < 157.5f)  // ↘
	{
		vDir = DIRECTION_8::LOWERRIGHT;
	}
	else if (fAngle >= 157.5f && fAngle < 202.5f)  // ↓
	{
		vDir = DIRECTION_8::DOWN;
	}
	else if (fAngle >= 202.5f && fAngle < 247.5f)  // ↙
	{
		vDir = DIRECTION_8::LOWERLEFT;
	}
	else if (fAngle >= 247.5f && fAngle < 292.5f)  // ←
	{
		vDir = DIRECTION_8::LEFT;
	}
	else if (fAngle >= 292.5f && fAngle < 337.5f)  // ↖
	{
		vDir = DIRECTION_8::UPPERLEFT;
	}
	else
	{
		vDir = DIRECTION_8::NONE;
	}

	return vDir;
}

void CPlayerScript::DirUpdate()
{
	m_vPrePos = m_vCurPos;
	m_vCurPos = Transform()->GetLocalPos();
	float fAngle = GetMoveAngle();
	bool bMove = IsMove();

	if (!bMove)
	{
		m_eDir = DIRECTION_8::NONE;
		return;
	}

	// 45도 8분할
	if (fAngle >= 337.5f || fAngle < 22.5f)        // ↑
	{
		m_ePreDir = DIRECTION_8::UP;
		m_eDir = DIRECTION_8::UP;
	}
	else if (fAngle >= 22.5f && fAngle < 67.5f)    // ↗
	{
		m_ePreDir = DIRECTION_8::UPPERRIGHT;
		m_eDir = DIRECTION_8::UPPERRIGHT;
	}
	else if (fAngle >= 67.5f && fAngle < 112.5f)   // →
	{
		m_ePreDir = DIRECTION_8::RIGHT;
		m_eDir = DIRECTION_8::RIGHT;
	}
	else if (fAngle >= 112.5f && fAngle < 157.5f)  // ↘
	{
		m_ePreDir = DIRECTION_8::LOWERRIGHT;
		m_eDir = DIRECTION_8::LOWERRIGHT;
	}
	else if (fAngle >= 157.5f && fAngle < 202.5f)  // ↓
	{
		m_ePreDir = DIRECTION_8::DOWN;
		m_eDir = DIRECTION_8::DOWN;
	}
	else if (fAngle >= 202.5f && fAngle < 247.5f)  // ↙
	{
		m_ePreDir = DIRECTION_8::LOWERLEFT;
		m_eDir = DIRECTION_8::LOWERLEFT;
	}
	else if (fAngle >= 247.5f && fAngle < 292.5f)  // ←
	{
		m_ePreDir = DIRECTION_8::LEFT;
		m_eDir = DIRECTION_8::LEFT;
	}
	else if (fAngle >= 292.5f && fAngle < 337.5f)  // ↖
	{
		m_ePreDir = DIRECTION_8::UPPERLEFT;
		m_eDir = DIRECTION_8::UPPERLEFT;
	}
	else
	{
		m_eDir = DIRECTION_8::NONE;
	}
}

bool CPlayerScript::MoveToPos(const Vec2 & _vecPos)
{
	Vec2 vMousePos = _vecPos;
	Vec3 vCurPos = Transform()->GetLocalPos();

	Vec2 vSubPos = (vMousePos - Vec2(vCurPos.x, vCurPos.y));
	float fDist = fabsf(vSubPos.Distance());
	float fMinMoveSpeed = m_fMoveSpeed * DT();
	if (fDist < fMinMoveSpeed) return false;

	Vec2 vDir = vSubPos.Normalize();

	vCurPos.x += vDir.x * fMinMoveSpeed;
	vCurPos.y += vDir.y * fMinMoveSpeed;

	Transform()->SetLocalPos(vCurPos);
	//m_vCurPos = vCurPos;

	return true;
}

void CPlayerScript::SoundEffectPlay(const int _idx)
{
	switch (_idx)
	{
	case 0:
	{		
		CSound*  pHit_Dagger = CResMgr::GetInst()->FindSound(L"Hit_Dagger");
		pHit_Dagger->Play(1);
	}
		break;
	case 1:
	{
		CSound* pThief_Invenom = CResMgr::GetInst()->FindSound(L"Thief_Invenom");
		pThief_Invenom->Play(1);
	}
		break;
	case 2:
	{
		CSound* pHit_Axe = CResMgr::GetInst()->FindSound(L"Hit_axe");
		pHit_Axe->Play(1);
	}
		break;
	case 3:
	{
		CSound* pHit_Mace = CResMgr::GetInst()->FindSound(L"Hit_mace");
		pHit_Mace->Play(1);
	}
		break;

	default:
		break;
	}
}

// 상태 연결망
bool CPlayerScript::ChangeState(const wstring & _strKey)
{
	m_pStateMgr->ChangeState(_strKey);

	return true;
}

void CPlayerScript::StateExecute()
{
	CState* pCurState = m_pStateMgr->GetCurState();
	if (NULL == pCurState) return;
	m_pStateMgr->GetCurState()->Execute();
}
