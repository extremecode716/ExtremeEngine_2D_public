#pragma once
#include "Res.h"

class CGameObject;

class CPrefab :
	public CRes
{
private:
	CGameObject*			m_pObj;
	
public:
	CGameObject*	Instantiate();
	CGameObject*	GameObject() { return m_pObj; }

	void RemovePrefab(CGameObject *_pGameObj);

public:
	CPrefab(CGameObject* _pObj);
	virtual ~CPrefab();
};

