#pragma once

#include "global.h"

union COL_ID
{
	struct
	{
		UINT	iLeftID;
		UINT	iRightID;
	};
	unsigned long long llID;
};

class CLayer;
class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

	//임시
public:
	UINT					m_arrColMat[MAX_LAYER]; // 레이어 충돌 체크용
	map<long long, bool>	m_mapColID;             // Collider가 등록된 오브젝트의 ID와 충돌 여부
	
public:
	int update();

private:
	void CollisionLayer(CLayer* _pLeft, CLayer* _pRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
	void GetProjAxis(const Matrix& _matWorld, Vec3* _vProj, Vec3* _vSource);

	const UINT* GetArrColMat() const { return m_arrColMat; }

public:
	int CheckCollisionLayer(const wstring& _strLeft, const wstring& _strRight);

	
	friend class CSceneInfo;
};

