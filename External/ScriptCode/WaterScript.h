#pragma once
#include "Script.h"

class CWaterScript :
	public CScript
{
private:
	float m_fAccTime;

public:
	virtual int update() override;

public:
	virtual CWaterScript* Clone() override { return new CWaterScript(*this); }

public:
	CWaterScript();
	virtual ~CWaterScript();
};

