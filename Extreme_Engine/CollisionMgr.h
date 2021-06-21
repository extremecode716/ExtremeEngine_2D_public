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

	//�ӽ�
public:
	UINT					m_arrColMat[MAX_LAYER]; // ���̾� �浹 üũ��
	map<long long, bool>	m_mapColID;             // Collider�� ��ϵ� ������Ʈ�� ID�� �浹 ����
	
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

