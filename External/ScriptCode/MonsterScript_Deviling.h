#pragma once
#include "DefineCode\MonsterScript.h"

class CMonsterScript_Deviling :
	public CMonsterScript
{
private:
	void KeyInput();
	void StateExecute();

public:
	virtual void Reset() override;
	virtual void SoundEffectPlay(const int _idx) override;

public:
	virtual void start() override;
	virtual int update() override;

public:
	virtual void GetMessageData(CMessage* _pData) override;

public:
	virtual CMonsterScript_Deviling* Clone() override { return new CMonsterScript_Deviling(*this); }

public:
	CMonsterScript_Deviling();
	virtual ~CMonsterScript_Deviling();
};

