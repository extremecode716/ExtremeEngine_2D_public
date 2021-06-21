#pragma once
#include "Component.h"

#include "Prefab.h"
#include "GameObject.h"

#include "Transform.h"
#include "MeshRender.h"
#include "Camera.h"
#include "Collider.h"
#include "Collider_2D.h"
#include "Animator.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"

#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "DestroyMgr.h"
#include "ShaderMgr.h"
#include "FontEngine.h"

#include "Material.h"

// 스크립트 자체 메세지 받을 수 있게 수정.
#include "..\External\DefineCode\Message.h"

class CScript :
	public CComponent
{
public:
	virtual void awake() {}
	virtual void start() {}
	virtual int update() { return RET_SUCCESS; }
	virtual int lateupdate() { return RET_SUCCESS; }

public:
	float DT() { return CTimeMgr::GetInst()->DeltaTime(); }
	CGameObject* Instantiate(CPrefab* _pPrefab, const Vec3& _vPos, const wstring& _strLayerName = L"Default");


public:
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

public:
	virtual void GetMessageData(CMessage* _pData) {};  // 메세지 형식 수정

public:
	virtual void Save(FILE* _pFile) {}
	virtual void Load(FILE* _pFile) {}
	virtual CScript* Clone() = 0;

public:
	CScript();
	virtual ~CScript();
};

