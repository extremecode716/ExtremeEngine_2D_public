#pragma once

#include "Animator.h"
#include "Animation.h"
#include "Transform.h"
#include "Script.h"
#include "KeyMgr.h"


class CState
{
protected:
	wstring			 m_strKey;
	
	set<wstring>    m_setNextKey;

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	wstring& GetKey() { return m_strKey; }
	
	void InsertNextKey(const wstring& _strKey) { m_setNextKey.insert(_strKey); }
	void InsertNextKey(const set<wstring>& _setNextKey);
	set<wstring>& GetNextKey() { return m_setNextKey; }
	bool IsFindNextKey(const wstring& _strKey);

public:
	virtual void Enter(CScript* _pScript = NULL) = 0;
	virtual void Execute(CScript* _pScript = NULL) = 0;
	virtual void Exit(CScript* _pScript = NULL) = 0;

public:
	CState();
	virtual ~CState();
};

