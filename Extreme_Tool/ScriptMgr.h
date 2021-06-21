#pragma once


// �� ������ ���� ��� ������.
struct tScriptInfo
{
	wstring strScriptName;
	DWORD	dwTypeId;
};

class CScript;

class CScriptMgr
{
public:
	static void GetScriptInfo(vector<tScriptInfo>& _vec);
	static CScript* GetScript(DWORD _dwTypdId);
	static const wchar_t* GetScriptName(CScript* _pScript);


private:
	CScriptMgr() {};
	~CScriptMgr() {};
};

