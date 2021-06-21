#pragma once
#include "Colleaque.h"

class CScript;

class CMessageColleaque :
	public CColleaque
{
private:
	virtual void Handle(const wstring& _strSrc, CMessage* _pData);

public:
	static CColleaque* Create(CMediatorMgr * _mediator, const wstring& _strName, CScript* _pScript);

public:
	CMessageColleaque(const wstring& _strName, CScript* _pScript);
	virtual ~CMessageColleaque();
};

