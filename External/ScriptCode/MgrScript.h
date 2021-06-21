#pragma once
#include "Script.h"

class CAstarMgr;
class CMgrScript :
	public CScript
{
private:
	CAstarMgr*      m_pAstarMgr;

public:
	virtual void awake() override;
	virtual void start() override;
	virtual int update() override;

public:
	virtual CMgrScript* Clone() override { return new CMgrScript(*this); }

public:
	CMgrScript();
	virtual ~CMgrScript();
};

