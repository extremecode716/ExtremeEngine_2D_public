#pragma once
#include "..\SingletonScript.h"


class CItemScript;
class CItemTable :
	public CSingletonScript<CItemTable>
{
private:
	map<wstring, CItemScript*> m_mapItemTable;
	list<CMaterial*> m_listMtrl;

public:
	void InitItemTable();

	CItemScript* FindItem(const wstring& _strName);
	CItemScript* CreateItem(const wstring& _strName);

private:
	virtual int update() override;

public:
	virtual CItemTable* Clone() override { return new CItemTable(*this); }

public:
	CItemTable();
	virtual ~CItemTable();
};

