#pragma once

#include "global.h"

// 씬 유지를 위해 잠시 사용안함.
struct tScriptInfo
{
	wstring strScriptName;
	DWORD	dwTypeId;
};

class CScript;

class CScriptMgr
{
public:
	static void				GetScriptInfo(vector<tScriptInfo>& _vec);
	static CScript*			GetScript(DWORD _dwTypdId);
	static CScript*			GetScript(const wstring& _strScriptName);
	static const wchar_t*	GetScriptName(CScript* _pScript);


private:
	CScriptMgr() {};
	~CScriptMgr() {};
};

