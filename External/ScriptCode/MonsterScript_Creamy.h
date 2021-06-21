#pragma once
#include "DefineCode\MonsterScript.h"

class CMonsterScript_Creamy :
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
	virtual CMonsterScript_Creamy* Clone() override { return new CMonsterScript_Creamy(*this); }

public:
	CMonsterScript_Creamy();
	virtual ~CMonsterScript_Creamy();
};

