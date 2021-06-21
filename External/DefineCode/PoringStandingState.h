#pragma once
#include "MonsterState.h"

class CPoringStandingState :
	public CMonsterState
{
	// 애니메이션 상태
private:
	wstring m_strUpStanding;
	wstring m_strDownStanding;

	int m_iSearchX;
	int m_iSearchY;

public:
	void SetAnimationName(const wstring& _strUpStanding, const wstring& _strDownStanding);
	void SetSearchIndex(int _iSearchX = 1, int _iSearchY = 1);

public:
	virtual void Enter(CScript* _pScript) override;
	virtual void Execute(CScript* _pScript) override;
	virtual void Exit(CScript* _pScript) override;

public:
	CPoringStandingState(CScript* _pScript);
	virtual ~CPoringStandingState();
};

