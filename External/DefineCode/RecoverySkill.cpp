#include "stdafx.h"
#include "RecoverySkill.h"

#include "..\ScriptCode\PlayerScript.h"

CRecoverySkill::CRecoverySkill()
	: m_iRecovery(0)
{
}


CRecoverySkill::~CRecoverySkill()
{
}

void CRecoverySkill::SetSkillInfo(const wstring & _strType, int _iRecovery)
{
	m_strType = _strType;
	m_iRecovery = _iRecovery;
}

bool CRecoverySkill::Action(CScript * _pScript)
{
	CPlayerScript* pPlayerScript = dynamic_cast<CPlayerScript*>(_pScript);
	if (NULL == pPlayerScript) return false;

	pPlayerScript->Recovery(m_strType, m_iRecovery);
	ServeSetting(pPlayerScript);
	SoundEffectPlay();

	return true;
}

void CRecoverySkill::ServeSetting(CScript * _pScript)
{
}

void CRecoverySkill::SoundEffectPlay()
{
	CSound* pSound = CResMgr::GetInst()->FindSound(L"se_drink_potion");
	if (NULL != pSound)
	{
		pSound->Play(1);
	}
}

