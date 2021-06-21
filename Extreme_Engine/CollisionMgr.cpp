#include "CollisionMgr.h"

#include "Scene.h"
#include "SceneMgr.h"
#include "Layer.h"

#include "GameObject.h"
#include "Collider.h"


CCollisionMgr::CCollisionMgr()
	: m_arrColMat{}
{
}


CCollisionMgr::~CCollisionMgr()
{
}

int CCollisionMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CLayer*>& vecLayer = pCurScene->GetVecLayer();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		for (UINT j = i; j < MAX_LAYER; ++j)
		{
			if ((m_arrColMat[i] >> j) & 1)    // 레이어 충돌 여부
			{
				CollisionLayer(vecLayer[i], vecLayer[j]);  // 레이어 충돌
			}
		}
	}

	return 0;
}

int CCollisionMgr::CheckCollisionLayer(const wstring & _strLeft, const wstring & _strRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	CLayer* pLeft = pCurScene->FindLayer(_strLeft);
	CLayer* pRight = pCurScene->FindLayer(_strRight);

	if (NULL == pLeft || NULL == pRight)
		return RET_FAILED;

	UINT iLeftIdx = pLeft->GetLayerIdx();
	UINT iRightIdx = pRight->GetLayerIdx();

	if (iRightIdx < iLeftIdx)
	{
		UINT iTemp = iLeftIdx;
		iLeftIdx = iRightIdx;
		iRightIdx = iTemp;
	}

	if (m_arrColMat[iLeftIdx] & (1 << iRightIdx))
		m_arrColMat[iLeftIdx] &= ~(1 << iRightIdx);
	else
		m_arrColMat[iLeftIdx] |= (1 << iRightIdx);

	return RET_SUCCESS;
}

void CCollisionMgr::CollisionLayer(CLayer * _pLeft, CLayer * _pRight)
{
	list<CGameObject*>& listLeft = _pLeft->GetObjList();
	list<CGameObject*>& listRight = _pRight->GetObjList();

	CCollider* pLeft = NULL;
	CCollider* pRight = NULL;

	list<CGameObject*>::iterator iterLeft = listLeft.begin();
	for (; iterLeft != listLeft.end(); ++iterLeft)
	{
		if ((*iterLeft)->GetActive() == false || (*iterLeft)->GetEnable() == false)
			continue;
		pLeft = (*iterLeft)->Collider();
		if (NULL == pLeft || pLeft->GetEnable() == false)
			continue;

		list<CGameObject*>::iterator iterRight = listRight.begin();
		for (; iterRight != listRight.end(); ++iterRight)
		{
			if ((*iterRight)->GetActive() == false || (*iterRight)->GetEnable() == false)
				continue;
			pRight = (*iterRight)->Collider();
			if (NULL == pRight || pRight->GetEnable() == false ||(pLeft->Is2DCollider() != pRight->Is2DCollider()))
				continue;

			COL_ID id;
			id.iLeftID = pLeft->GetColID();
			id.iRightID = pRight->GetColID();

			map<long long, bool>::iterator iterID = m_mapColID.find(id.llID);
			bool bPrev = false;  // 이전 프레임 충돌 여부
			if (iterID != m_mapColID.end())
				bPrev = iterID->second;

			// 충돌 여부 판단
			if (IsCollision(pLeft, pRight))
			{
				// 충돌 하고 있었다.
				if (bPrev)
				{
					pLeft->OnCollision(pRight);
					pRight->OnCollision(pLeft);
				}
				else
				{
					// 최초 충돌 시점
					pLeft->OnCollisionEnter(pRight);
					pRight->OnCollisionEnter(pLeft);

					if (iterID == m_mapColID.end())  // m_mapColID에 없다면
					{
						m_mapColID.insert(make_pair(id.llID, true));
					}
					else
					{
						iterID->second = true;
					}
				}
			}
			else
			{
				// 이전 프레임에 충돌 했을시
				if (bPrev)
				{
					pLeft->OnCollisionExit(pRight);
					pRight->OnCollisionExit(pLeft);
					iterID->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider * _pLeftCol, CCollider * _pRightCol)
{
	Vec3 vProj[4] = {};    // 투영 축
	Vec3 vSouce[4] = {};   // 원본 위치
	Vec3 vCenter = _pRightCol->GetWorldPos() - _pLeftCol->GetWorldPos();

	GetProjAxis(_pLeftCol->GetWorldMat(), vProj, vSouce);
	GetProjAxis(_pRightCol->GetWorldMat(), vProj + 2, vSouce + 2);

	for (int i = 0; i < 4; ++i)
	{
		float fDist = 0.f;
		for (int j = 0; j < 4; ++j)
		{
			fDist += fabsf(vSouce[j].Dot(vProj[i]));
		}
		fDist /= 2.f;

		float fCenter = fabsf(vCenter.Dot(vProj[i]));

		if (fCenter > fDist)
			return false;
	}
	return true;
}

void CCollisionMgr::GetProjAxis(const Matrix & _matWorld, Vec3 * _vProj, Vec3 * _vSource)
{
	// 1 ----- 2
	// |       |
	// |       |
	// 0 ----- 3
	Vec3 vLocal[4] = { Vec3(-0.5f, -0.5f, 0.f), Vec3(-0.5f, 0.5f, 0.f)
		, Vec3(0.5f, 0.5f, 0.f), Vec3(0.5f, -0.5f, 0.f) };

	Vec3 vOut1 = XMVector3TransformCoord(vLocal[2].Convert(), _matWorld);
	Vec3 vOut2 = XMVector3TransformCoord(vLocal[1].Convert(), _matWorld);

	_vSource[0] = vOut1 - vOut2;
	_vSource[0].z = 0.f;
	_vProj[0] = _vSource[0];
	_vProj[0].Normalize();

	vOut1 = XMVector3TransformCoord(vLocal[0].Convert(), _matWorld);
	vOut2 = XMVector3TransformCoord(vLocal[1].Convert(), _matWorld);

	_vSource[1] = vOut1 - vOut2;
	_vSource[1].z = 0.f;
	_vProj[1] = _vSource[1];
	_vProj[1].Normalize();

}

