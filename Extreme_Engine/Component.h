#pragma once

#include "global.h"

class CGameObject;
class CTransform;
class CMeshRender;
class CCollider;
class CAnimator;
class CCamera;

class CComponent
{
private:
	CGameObject*	m_pObj;

public:
	virtual void awake() {};
	virtual void start() {};
	virtual int update() = 0;
	virtual int lateupdate() { return RET_SUCCESS; };
	virtual int finalupdate() { return RET_SUCCESS; };
	virtual void render() {};

public:
	void SetGameObject(CGameObject* _pObj) { m_pObj = _pObj; }

public:
	CGameObject * GetGameObject() { return m_pObj; }

public:
	CGameObject* GetParentObject();
	CTransform* Transform();
	CMeshRender* MeshRender();
	CCollider* Collider();
	CAnimator* Animator();
	CCamera* Camera();


	virtual void Save(FILE* _pFile) = 0;
	virtual void Load(FILE* _pFile) = 0;
	virtual CComponent* Clone() = 0;

public:
	CComponent();
	virtual ~CComponent();

	friend class CGameObject;
	friend class CSaveLoadMgr;
};

