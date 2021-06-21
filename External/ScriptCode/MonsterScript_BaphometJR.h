#pragma once
#include "DefineCode\MonsterScript.h"

//wraith dead
class CMonsterScript_BaphometJR :
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
	virtual CMonsterScript_BaphometJR* Clone() override { return new CMonsterScript_BaphometJR(*this); }

public:
	CMonsterScript_BaphometJR();
	virtual ~CMonsterScript_BaphometJR();
};

