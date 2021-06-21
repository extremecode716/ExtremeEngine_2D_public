#include "stdafx.h"
#include "TornadoScript.h"

#include "..\DefineCode\Colleaque.h"
#include "..\DefineCode\AttackMessage.h"
#include "..\DefineCode\MonsterScript.h"
#include "Damage.h"
#include "RandomScript.h"

CTornadoScript::CTornadoScript()
	: m_pPlayerScript(NULL)
	, m_fForce(200.f)
	, m_iMinDamage(1)
	, m_iMaxDamage(1)
	, m_fTempTime(0.f)
	, m_fAttackTime(0.3f)
	, m_bAttack(false)
	, m_pSound(NULL)
{
}


CTornadoScript::~CTornadoScript()
{
	if (NULL != m_pSound)
	{
		m_pChannel->stop();
	}
}

void CTornadoScript::start()
{
	m_vPos = Transform()->GetLocal2DPos();

	m_pSound = CResMgr::GetInst()->FindSound(L"se_field_wind_03");
	if (NULL != m_pSound)
	{
		m_pChannel = m_pSound->Play();
	}

}

int CTornadoScript::update()
{
	m_vPos = Transform()->GetLocal2DPos();

	if (false == m_bAttack)
	{
		m_fTempTime += DT();

		if (m_fTempTime >= m_fAttackTime)
		{
			m_bAttack = true;
			m_fTempTime = 0.f;

			if (!m_setCollision.empty())
			{
				set<CMonsterScript*>::iterator iter = m_setCollision.begin();
				auto setNull = m_setCollision.end();
				for (; iter != setNull; ++iter)
				{
					AttackMonster(*iter);
				}
				m_setCollision.clear();
			}
			m_bAttack = false;
		}
	}

	return RET_SUCCESS;
}

void CTornadoScript::AttackMonster(CMonsterScript * _pMonster)
{
	if (m_pPlayerScript == NULL) return;
	CColleaque* pPlayerCollq = m_pPlayerScript->GetCollq();
	CColleaque* pMonCollq = _pMonster->GetCollq();
	if (pPlayerCollq != NULL && pMonCollq != NULL)
	{
		int iRandomDamage = GameRandom::RandomInt(m_iMinDamage, m_iMaxDamage);
		CMessage* pMsg = new CAttackMessage(pPlayerCollq->GetName(), iRandomDamage, m_pPlayerScript->GetGameObject());
		pPlayerCollq->SendData(pMonCollq->GetName(), pMsg);

		CreateDamageEffect(_pMonster, iRandomDamage);
	}
}



void CTornadoScript::OnCollisionEnter(CCollider * _pOther)
{
}

void CTornadoScript::OnCollision(CCollider * _pOther)
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
			Vec2 vMonPos = pMonObj->Transform()->GetLocal2DPos();
			Vec3 vMonRot = pMonObj->Transform()->GetLocalRot();

			float fRot = GetRotFromTarget(vMonPos, vMonRot);
			fRot = XM_PI / 2.f + fRot;
			Vec2 vMovePos;
			vMovePos.x = vMonPos.x + cos(fRot) * m_fForce * DT();
			vMovePos.y = vMonPos.y + sin(fRot) * m_fForce * DT();

			pMonObj->Transform()->SetLocal2DPos(vMovePos);
		}
	}
}


void CTornadoScript::CreateDamageEffect(CMonsterScript * _pMonster, int _iDamage)
{
	Vec2 vMonPos = _pMonster->Transform()->GetLocal2DPos();
	Vec2 vMonScale = _pMonster->Transform()->GetLocal2DScale();
	Vec3 vEffPos = Vec3(vMonPos.x, vMonPos.y, 81.f);
	if (NULL != _pMonster->GetEffectDamage())
	{
		vEffPos.z = 79.f;
		CGameObject* pEffectDamageClone = _pMonster->Instantiate(_pMonster->GetEffectDamage(), vEffPos, L"Default");
		
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


void CTornadoScript::OnCollisionExit(CCollider * _pOther)
{
}


float CTornadoScript::GetRotFromTarget(const Vec2& _vPos, const Vec3& _vRot)
{
	float angle;

	Vec2 vPos = _vPos;
	Vec3 vRot = _vRot;

	angle = atan2(vPos.x - m_vPos.x, vPos.y - m_vPos.y) * (180.f / XM_PI);

	vRot.z = -angle;

	return vRot.z;
}


void CTornadoScript::SetInfo(CPlayerScript * _pPlayer, float _fForce, int _iMinDamage, int _iMaxDamage, float _fAttackTime)
{
	m_pPlayerScript = _pPlayer;
	m_fForce = _fForce;
	m_iMinDamage = _iMinDamage;
	m_iMaxDamage = _iMaxDamage;
	m_fAttackTime = _fAttackTime;
}
