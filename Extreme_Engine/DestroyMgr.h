#pragma once

#include "global.h"

class CGameObject;

class CDestroyMgr
{
	SINGLE(CDestroyMgr);

private:
	list<CGameObject*>	m_listObj;

public:
	void AddGameObject(CGameObject* _obj);
	list<CGameObject*>& GetObjList() { return m_listObj; }
	void Destory();
	void Clear();
	void DestroyCloneMtrl();
};

