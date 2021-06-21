#pragma once

#include "Script.h"

class CSkill
{
private:
	wstring m_strKey;

protected:
	bool m_bAction;

public:
	virtual bool Action(CScript* _pScript) { return true; }
	virtual void SetAction(bool _bAction) { m_bAction = _bAction; }
	virtual bool GetAction() const { return m_bAction; }

	virtual void SoundEffectPlay() {};

public:
	CSkill();
	virtual ~CSkill();
};

