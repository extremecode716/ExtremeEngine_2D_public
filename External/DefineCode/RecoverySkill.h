#pragma once
#include "DefineCode\Skill.h"
class CRecoverySkill :
	public CSkill
{
private:
	wstring m_strType;
	int m_iRecovery;

public:
	void SetSkillInfo(const wstring& _strType, int _iRecovery);

public:
	virtual bool Action(CScript* _pScript) override;

	void ServeSetting(CScript* _pScript);
	virtual void SoundEffectPlay() override;

public:
	CRecoverySkill();
	virtual ~CRecoverySkill();
};

