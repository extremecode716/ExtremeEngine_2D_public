#include "stdafx.h"
#include "MeteorScript.h"

#include "PlayerScript.h"
#include "..\DefineCode\MonsterScript.h"
#include "MeteorAttackScript.h"


CMeteorScript::CMeteorScript()
	: m_pPlayerScript(NULL)
	, m_vOffset{}
	, m_bAttack(false)
	, m_iMinDamage(1)
	, m_iMaxDamage(1)
	, m_fTempTime(0.f)
	, m_fAttackTime(0.2f)
	, m_pSound(NULL)
{
}

CMeteorScript::~CMeteorScript()
{
}

void CMeteorScript::start()
{
}

int CMeteorScript::update()
{
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
					CreateMeteor((*iter));
				}
				m_setCollision.clear();	

				Collider()->SetEnable(false);	
			}
			CDestroyMgr::GetInst()->AddGameObject(GetGameObject());
			m_bAttack = false;
		}
	}
	return RET_SUCCESS;
}
void CMeteorScript::CreateMeteor(CMonsterScript* _pMonScript)
{
	CResPtr<CPrefab> pEffect = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Effect_Meteor(Prefab)");
	m_listMeteorObj.push_back(_pMonScript);

	Vec3 vMonPos = _pMonScript->Transform()->GetLocalPos();
	Vec3 vMeteorPos = m_vOffset + vMonPos; // 대각선 위 ↙
	vMeteorPos.z -= 20.f;
	CGameObject* pMeteor = Instantiate(pEffect, vMeteorPos, L"Effect");
	CMeteorAttackScript* pAttackScript = pMeteor->Script<CMeteorAttackScript>();
	if (NULL == pAttackScript) return;
	pAttackScript->SetPlayerScript(m_pPlayerScript);
	pAttackScript->SetTargetPos(vMonPos);
	pAttackScript->SetSpeed(400.f);
	pAttackScript->SetDamage(m_iMinDamage, m_iMaxDamage);
	pMeteor->awake();
	pMeteor->start();
}

void CMeteorScript::OnCollisionEnter(CCollider * _pOther)
{
	wstring strTag = _pOther->GetGameObject()->GetTag();
	int iFindKey = strTag.find(L"Monster");

	if (iFindKey > -1)
	{
		CGameObject* pMonObj = _pOther->GetGameObject();
		CMonsterScript* pMonScript = pMonObj->Script<CMonsterScript>();
		if (NULL == pMonScript) return;
		bool bDie = pMonScript->IsDie();
		if (bDie == false)
		{
			m_setCollision.insert(pMonScript);
		}
	}

}

void CMeteorScript::OnCollision(CCollider * _pOther)
{
}

void CMeteorScript::OnCollisionExit(CCollider * _pOther)
{
}
