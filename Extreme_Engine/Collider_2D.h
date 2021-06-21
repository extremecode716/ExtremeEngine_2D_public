#pragma once
#include "Collider.h"

class CCollider_2D :
	public CCollider
{
public:
	virtual void awake();
	virtual int update() { return 0; }
	virtual void render();

public:
	virtual bool Is2DCollider() { return true; }
	virtual bool Is3DCollider() { return false; }

	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

	CLONE(CCollider_2D);
public:
	CCollider_2D();
	virtual ~CCollider_2D();
};

