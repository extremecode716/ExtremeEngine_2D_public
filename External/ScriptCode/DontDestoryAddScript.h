#pragma once
#include "Script.h"
class CDontDestoryAddScript :
	public CScript
{

	
private:
	virtual void start() override;
	virtual int update() override { return RET_SUCCESS; }

public:
	virtual CDontDestoryAddScript* Clone() override { return new CDontDestoryAddScript(*this); }
public:
	CDontDestoryAddScript();
	virtual ~CDontDestoryAddScript();
};

