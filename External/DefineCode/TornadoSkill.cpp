#include "stdafx.h"
#include "TornadoSkill.h"

// 서브 셋팅을 위해서
#include "..\ScriptCode\TornadoScript.h"
#include "..\ScriptCode\DeleteEndAnim.h"
#include "..\ScriptCode\PlayerScript.h"

CTornadoSkill::CTornadoSkill()
	: m_pEffect(NULL)
	, m_iMinDamage(1)
	, m_iMaxDamage(1)
{
}


CTornadoSkill::~CTornadoSkill()
{
}


bool CTornadoSkill::Action(CScript * _pScript)
{
	CPlayerScript* pPlayerScript = dynamic_cast<CPlayerScript*>(_pScript);
	m_pEffect = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Effect_Tornado(Prefab)");
	if (pPlayerScript == NULL) return false;
	if (m_pEffect == NULL) return false;

	Vec3 vTornadoPos = pPlayerScript->Transform()->GetLocalPos();
	vTornadoPos.z -= 10.f;
	CGameObject* pTornadoObj = pPlayerScript->Instantiate(m_pEffect, vTornadoPos, L"Effect");

	if (pTornadoObj == NULL) return false;

	CDeleteEndAnim* pDeleteEndScript = new CDeleteEndAnim;
	pDeleteEndScript->SetCount(0, 2);
	CTornadoScript* pTornadoScript = new CTornadoScript;
	pTornadoScript->SetInfo(pPlayerScript, 200.f, 1, 5, 0.25f);
	pTornadoObj->AddComponent<CScript>(pDeleteEndScript);
	pTornadoObj->AddComponent<CScript>(pTornadoScript);
	pTornadoObj->awake();
	pTornadoObj->start();

	return true;
}

void CTornadoSkill::ServeSetting(CScript * _pScript)
{
}

void CTornadoSkill::SoundEffectPlay()
{
}

