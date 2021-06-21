#pragma once
#include "Skill.h"

class CTeleportSkill :
	public CSkill
{
public:
	virtual bool Action(CScript* _pScript) override;

	void ServeSetting(CScript* _pScript);
	virtual void SoundEffectPlay() override;

public:
	CTeleportSkill();
	virtual ~CTeleportSkill();
};

