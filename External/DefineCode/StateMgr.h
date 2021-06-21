#pragma once
#include "global.h"
#include "FsmState.h"
class CStateMgr
{
private:
	map<wstring, CState*> m_mapSate;

	CState*				 m_pPreState;
	CState*				 m_pCurState;

public:
	void SetCurState(CState* _pState);
	wstring GetCurStateKey();
	wstring GetPreStateKey();

	CState* GetCurState();

public:
	CState* AddState(const wstring& _strKey, CState* _state);
	bool ChangeState(const wstring& _strKey);
	bool ChangePreState(const wstring& _strKey);
	bool IsFindState(const wstring& _strKey);
	CState* FindState(const wstring& _strKey);

public:
	CStateMgr();
	~CStateMgr();
};

