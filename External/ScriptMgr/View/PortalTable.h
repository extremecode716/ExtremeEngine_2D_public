#pragma once

#include "..\SingletonScript.h"

class CPortalTable
	:public CSingletonScript<CPortalTable>
{
private:
	map<wstring, tuple<wstring, CPrefab*>> m_mapPortalTable;

private:
	bool InsertPortal(const wstring& _strKey, const wstring& _strNextSceneKey, const wstring& _strPrefab = L"Portal(Prefab)");
	tuple<wstring, CPrefab*> FindPortal(const wstring& _strKey);

public:
	void InitPortalTable();
	bool CreatePortal(const wstring& _strKey, const Vec3& _vPos, const Vec3& _vSpawnPos, const wstring& _strTitleKey, const wstring& _strTitleText, const wstring& _strLayer = L"Default");

private:
	virtual int update() override { return RET_SUCCESS; }

public:
	virtual CPortalTable* Clone() override { return new CPortalTable(*this); }

public:
	CPortalTable();
	virtual ~CPortalTable();
};

