#pragma once
#include "DefineCode\MonsterScript.h"

class CMonsterScript_Poring :
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
	virtual CMonsterScript_Poring* Clone() override { return new CMonsterScript_Poring(*this); }

public:
	CMonsterScript_Poring();
	virtual ~CMonsterScript_Poring();

	//friend class CPoringStandingState;
	//friend class CPoringMoveState;
	//friend class CPoringDieState;
	//friend class CPoringAttackState;
};

