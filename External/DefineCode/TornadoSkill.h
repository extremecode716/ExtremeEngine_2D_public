#pragma once
#include "Skill.h"


class CTornadoSkill :
	public CSkill
{
private:
	CPrefab* m_pEffect;

	int m_iMinDamage;
	int m_iMaxDamage;

public:
	virtual bool Action(CScript* _pScript) override;

	void ServeSetting(CScript* _pScript);
	virtual void SoundEffectPlay() override;

public:
	CTornadoSkill();
	virtual ~CTornadoSkill();
};

