#include "stdafx.h"
#include "MeteorAttackScript.h"

#include "..\DefineCode\Colleaque.h"
#include "..\DefineCode\AttackMessage.h"
#include "PlayerScript.h"
#include "..\DefineCode\MonsterScript.h"
#include "Damage.h"
#include "RandomScript.h"
#include "DeleteEndAnim.h"


CMeteorAttackScript::CMeteorAttackScript()
	: m_pPlayerScript(NULL)
	, bExplosion(false)
	, m_vPos{}
	, m_vTargetPos{}
	, m_fSpeed(200.f)
	, m_bOnceRot(false)
	, m_fTagetRot{}
	, m_bOnceTime(false)
	, m_fExplosionTime(0.f)
	, m_fTempTime(0.f)
	, m_bAttack(false)
	, m_iMinDamage(1)
	, m_iMaxDamage(1)
	, m_fCollisionTempTime(0.f)
	, m_fCollisionTime(0.2f)
{
}


CMeteorAttackScript::~CMeteorAttackScript()
{
}

void CMeteorAttackScript::start()
{
	Animator()->PlayAnimation(L"Meteor", false);
	Collider()->SetEnable(false);

	CSound* pSound = CResMgr::GetInst()->FindSound(L"ef_fireball");
	if (NULL != pSound)
	{
		pSound->Play(1);
	}
}

int CMeteorAttackScript::update()
{
	if (bExplosion == false)
	{
		m_vPos = Transform()->GetLocalPos();

		if (false == m_bOnceTime)
		{
			m_fExplosionTime = Vec2(m_vPos.x - m_vTargetPos.x, m_vPos.y - m_vTargetPos.y).Distance() / m_fSpeed;
			m_bOnceTime = true;
		}

		m_fTempTime += DT();
		if (m_fTempTime >= m_fExplosionTime)
		{
			Collider()->SetEnable(true);
			Animator()->PlayAnimation(L"Explosion", false);
			CSound* pSound = CResMgr::GetInst()->FindSound(L"explosion");
			if (NULL != pSound)
			{
				pSound->Play(1);
			}

			CDeleteEndAnim* pDeleteEndAnim = new CDeleteEndAnim;
			GetGameObject()->AddComponent<CScript>(pDeleteEndAnim);
			pDeleteEndAnim->SetCount(0, 1);
			pDeleteEndAnim->start();
			bExplosion = true;

			return RET_SUCCESS;
		}

		if (false == m_bOnceRot)
		{
			m_fTagetRot = GetRotFromTarget();
			m_fTagetRot = XM_PI / 4.f + m_fTagetRot;
			m_bOnceRot = true;
		}

		Vec2 vMovePos;
		vMovePos.x = m_vPos.x + cos(m_fTagetRot) * m_fSpeed * DT();
		vMovePos.y = m_vPos.y + sin(m_fTagetRot) * m_fSpeed * DT();

		Transform()->SetLocal2DPos(vMovePos);
	}
	else
	{
		m_fCollisionTempTime += DT();
		if (m_fCollisionTempTime >= m_fCollisionTime)
		{
			Collider()->SetEnable(false);

			set<CMonsterScript*>::iterator iter = m_setCollision.begin();
			auto setNull = m_setCollision.end();
			for (; iter != setNull; ++iter)
			{
				Attack(*iter);
			}
			m_setCollision.clear();
		}
	}

	return RET_SUCCESS;
}


void CMeteorAttackScript::Attack(CMonsterScript* _pMonsterScript)
{
	int iRandomDamage = GameRandom::RandomInt(m_iMinDamage, m_iMaxDamage);

	CColleaque* pPlayerCollq = m_pPlayerScript->GetCollq();
	CColleaque* pMonCollq = _pMonsterScript->GetCollq();
	CMessage* pMsg = new CAttackMessage(pPlayerCollq->GetName(), iRandomDamage, m_pPlayerScript->GetGameObject());
	pPlayerCollq->SendData(pMonCollq->GetName(), pMsg);

	CreateDamageEffect(_pMonsterScript, iRandomDamage);
}

void CMeteorAttackScript::CreateDamageEffect(CMonsterScript * _pMonsterScript, int _iDamage)
{
	Vec2 vMonPos = _pMonsterScript->Transform()->GetLocal2DPos();
	Vec2 vMonScale = _pMonsterScript->Transform()->GetLocal2DScale();
	Vec3 vEffPos = Vec3(vMonPos.x, vMonPos.y, 81.f);
	if (NULL != _pMonsterScript->GetEffectDamage())
	{
		vEffPos.z = 79.f;
		CGameObject* pEffectDamageClone = _pMonsterScript->Instantiate(_pMonsterScript->GetEffectDamage(), vEffPos, L"Default");

		if (pEffectDamageClone == NULL) return;
		if (vMonScale.x > 0)
		{
			pEffectDamageClone->Script<CDamage>()->SetStartRot(Vec3(0.f, 0.f, 1.9f));
		}
		else
		{
			pEffectDamageClone->Script<CDamage>()->SetStartRot(Vec3(0.f, 0.f, 1.2f));
		}

		pEffectDamageClone->Script<CDamage>()->SetDamage(_iDamage);
		pEffectDamageClone->start();
	}
}

void CMeteorAttackScript::OnCollisionEnter(CCollider * _pOther)
{
}

void CMeteorAttackScript::OnCollision(CCollider * _pOther)
{
	wstring strTag = _pOther->GetGameObject()->GetTag();
	int iFindKey = strTag.find(L"Monster");

	if (iFindKey > -1)
	{
		CGameObject* pMonObj = _pOther->GetGameObject();
		CMonsterScript* pMonScript = pMonObj->Script<CMonsterScript>();

		bool bDie = pMonScript->IsDie();
		if (bDie == false)
		{
			if (pMonScript != NULL)
			{
				m_setCollision.insert(pMonScript);
			}
		}
	}
}

void CMeteorAttackScript::OnCollisionExit(CCollider * _pOther)
{
}
void CMeteorAttackScript::SetTargetPos(const Vec3 & _vPos)
{
	m_vTargetPos = _vPos;
}

float CMeteorAttackScript::GetRotFromTarget()
{
	float angle;

	angle = atan2(m_vTargetPos.x - m_vPos.x, m_vTargetPos.y - m_vPos.y) * (180.f / XM_PI);

	angle = -angle;

	return angle;
}

float CMeteorAttackScript::GetDistance()
{
	Vec3 vPos = m_vPos;
	Vec3 vTarget = m_vTargetPos;

	float fDistance = sqrt(pow(vPos.x - vTarget.x, 2) + pow(vPos.y - vTarget.y, 2));

	return fDistance;
}
