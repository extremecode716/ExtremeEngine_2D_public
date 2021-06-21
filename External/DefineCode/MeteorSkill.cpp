#include "stdafx.h"
#include "MeteorSkill.h"

// 추가 작업
#include "..\ScriptCode\PlayerScript.h"
#include "..\ScriptCode\MeteorScript.h"

CMeteorSkill::CMeteorSkill()
	: m_pEffect(NULL)
	, m_iMinDamage(1)
	, m_iMaxDamage(1)
{
}


CMeteorSkill::~CMeteorSkill()
{
}

bool CMeteorSkill::Action(CScript * _pScript)
{
	CPlayerScript* pPlayerScript = dynamic_cast<CPlayerScript*>(_pScript);
	m_pEffect = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Effect_MeteorGround(Prefab)");
	if (pPlayerScript == NULL) return false;
	if (m_pEffect == NULL) return false;

	Vec3 vMeteorPos = pPlayerScript->Transform()->GetLocalPos();
	vMeteorPos.z -= 10.f;
	CGameObject* pMeteorGround = pPlayerScript->Instantiate(m_pEffect, vMeteorPos, L"Effect");

	if (NULL == pMeteorGround) return false;

	CMeteorScript* pMeteorScript = new CMeteorScript();
	pMeteorScript->SetPlayerScript(pPlayerScript);
	pMeteorScript->SetMeteorOffset(Vec3(300.f, 300.f, 0.f));
	pMeteorScript->SetDamage(50, 200);
	pMeteorScript->SetAttackTime(0.2f);
	pMeteorGround->AddComponent<CScript>(pMeteorScript);
	pMeteorGround->awake();
	pMeteorGround->start();

	return true;
}

void CMeteorSkill::ServeSetting(CScript * _pScript)
{
}

void CMeteorSkill::SoundEffectPlay()
{
}

