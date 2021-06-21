#pragma once

#include "..\External\DefineCode\DefineScript.h"
#include "..\SingletonScript.h"

class CPrefab;
class CMonsterTable
	: public CSingletonScript<CMonsterTable>
{
private:
	// 개별적으로 처리
	// 프립팹 저장해놓는다.
	map<wstring, CPrefab*> m_mapMonsterTable;
	// 스텟을 저장해놓는다.
	map<wstring, tStatus*> m_mapMonsterStatuse;
	// 아이템을 저장해놓는다.

private:
	bool InsertMonster(const wstring& _strKey, CPrefab* _pMonsterPrefab);
	bool InsertMonsterStatus(const wstring& _strKey, tStatus* _pStatuse);

public:
	void InitMonsterTable();
	CPrefab* FindMonster(const wstring& _strKey);
	tStatus* FindMonsterStatus(const wstring& _strKey);

	
private:
	virtual int update() override { return RET_SUCCESS; }

public:
	virtual CMonsterTable* Clone() override { return new CMonsterTable(*this); }

public:
	CMonsterTable();
	~CMonsterTable();
};

