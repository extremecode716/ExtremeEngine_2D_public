#pragma once
#include "Script.h"

class CCameraScript
	: public CScript
{
private:
	float		m_fScale;

	CGameObject*   m_pTargetObj;

public:
	virtual void start() override;
	virtual int update() override;

public:
	virtual CCameraScript* Clone() override { return new CCameraScript(*this); }

public:
	CCameraScript();
	virtual ~CCameraScript();
};

