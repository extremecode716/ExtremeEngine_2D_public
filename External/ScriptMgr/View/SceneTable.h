#pragma once
#include "..\SingletonScript.h"

class CSceneTable
	: public CSingletonScript<CSceneTable>
{
private:
	map<wstring, wstring> m_mapSceneTable;

private:
	const wchar_t* FindPath(const wstring& _strKey);

public:
	void InitSceneTable();
	bool ChangeScene(const wstring& _strPathName);

private:
	virtual int update() override { return RET_SUCCESS; }

public:
	virtual CSceneTable* Clone() override { return new CSceneTable(*this); }

public:
	CSceneTable();
	~CSceneTable();
};

