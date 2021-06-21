#include "stdafx.h"
#include "MonsterScript.h"

#include "Scene.h"
#include "Layer.h"
#include "SceneMgr.h"

#include "RandomScript.h"

//#include "RandomScript.h"


CMonsterScript::CMonsterScript()
	: m_bDie(false)
	, m_pStateMgr(NULL)
	, m_pMediator(NULL)
	, m_pCollq_Monster(NULL)
	, m_eAggressiveType(MONSTER_AGGRESSIVE_TYPE::NON_AGGRESSIVE_TYPE)
	, m_fSurvivalTime(0.f)
	, m_bMove(false)
	, m_eDir(DIRECTION_8::NONE)
	, m_ePreDir(DIRECTION_8::NONE)
	, m_vCurPos(Vec3(0.f, 0.f, 0.f))
	, m_vPrePos(Vec3(0.f, 0.f, 0.f))
	, m_fTempTime(0.f)
	, m_fMoveSpeed(100.f)
	, m_fRotSpeed(XM_PI)
	, m_pTileMgr(NULL)
	, m_fSearchTime(3.f)
	, m_fSearchTempTime(0.f)
	, m_iSearchMaxX(0.f)
	, m_iSearchMaxY(0.f)
	, m_fPivot(60.f)
	, m_iMinDamage(1)
	, m_iMaxDamage(1)
	, m_bHit(false)
	, m_fAttackRange(0.f)
	, m_pAttackerObj(NULL)
	, m_IsMove(false)
	, m_pEffect_Damage(NULL)
{
}

CMonsterScript::~CMonsterScript()
{
	if (m_pCollq_Monster != NULL)
	{
		m_pMediator->EraseCollq(m_pCollq_Monster->GetName());
		m_pCollq_Monster = NULL;
	}

	Safe_Delete_Stack(m_stackPath);
	SAFE_DELETE(m_pStateMgr);
}

float CMonsterScript::Lerp(const float _a, const float _b, float _t)
{
	return _a + (_b - _a) * _t;
}

void CMonsterScript::start()
{
	m_pEffect_Damage = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Effect_Damage(Prefab)");
}

int CMonsterScript::update()
{
	return RET_SUCCESS;
}

void CMonsterScript::GetMessageData(CMessage* _pData)
{
}

bool CMonsterScript::ChangeState(const wstring & _strKey)
{
	m_pStateMgr->ChangeState(_strKey);
	return true;
}

bool CMonsterScript::IsMove()
{
	if (m_vCurPos == m_vPrePos)
		return false;

	return true;
}

float CMonsterScript::GetMoveAngle()
{
	Vec3 vDir = (m_vCurPos - m_vPrePos);
	vDir.Normalize();
	float fAngle = atan2f(vDir.x, vDir.y) * 180.f / XM_PI;
	fAngle = (fAngle >= 0) ? fAngle : fAngle + 360.f;

	return fAngle;
}

DIRECTION_8 CMonsterScript::GetDirection()
{
	m_vPrePos = m_vCurPos;
	m_vCurPos = Transform()->GetLocalPos();
	float fAngle = GetMoveAngle();
	bool bMove = IsMove();
	
	if (!bMove)
	{
		m_eDir = DIRECTION_8::NONE;
		return m_eDir;
	}

	// 45도 8분할
	if (fAngle >= 337.5f || fAngle < 22.5f)        // ↑
	{
		m_eDir = DIRECTION_8::UP;
	}
	else if (fAngle >= 22.5f && fAngle < 67.5f)    // ↗
	{
		m_eDir = DIRECTION_8::UPPERRIGHT;
	}
	else if (fAngle >= 67.5f && fAngle < 112.5f)   // →
	{
		m_eDir = DIRECTION_8::RIGHT;
	}
	else if (fAngle >= 112.5f && fAngle < 157.5f)  // ↘
	{
		m_eDir = DIRECTION_8::LOWERRIGHT;
	}
	else if (fAngle >= 157.5f && fAngle < 202.5f)  // ↓
	{
		m_eDir = DIRECTION_8::DOWN;
	}
	else if (fAngle >= 202.5f && fAngle < 247.5f)  // ↙
	{
		m_eDir = DIRECTION_8::LOWERLEFT;
	}
	else if (fAngle >= 247.5f && fAngle < 292.5f)  // ←
	{
		m_eDir = DIRECTION_8::LEFT;
	}
	else if (fAngle >= 292.5f && fAngle < 337.5f)  // ↖
	{
		m_eDir = DIRECTION_8::UPPERLEFT;
	}
	else
	{
		m_eDir = DIRECTION_8::NONE;
	}

	return m_eDir;
}



void CMonsterScript::SetSearchMaxPos(float _iX, float _iY)
{
	m_iSearchMaxX = _iX;
	m_iSearchMaxY = _iY;
}

void CMonsterScript::Reset()
{
	CCollider* pCollider = Collider();
	if (pCollider != NULL)
	{
		pCollider->SetEnable(true);
	}
}

void CMonsterScript::DirUpdate()
{
	m_vPrePos = m_vCurPos;
	m_vCurPos = Transform()->GetLocalPos();
	float fAngle = GetMoveAngle();
	bool bMove = IsMove();

	if (!bMove)
	{
		m_eDir = DIRECTION_8::NONE;
		return;
	}

	// 45도 8분할
	if (fAngle >= 337.5f || fAngle < 22.5f)        // ↑
	{
		m_ePreDir = DIRECTION_8::UP;
		m_eDir = DIRECTION_8::UP;
	}
	else if (fAngle >= 22.5f && fAngle < 67.5f)    // ↗
	{
		m_ePreDir = DIRECTION_8::UPPERRIGHT;
		m_eDir = DIRECTION_8::UPPERRIGHT;
	}
	else if (fAngle >= 67.5f && fAngle < 112.5f)   // →
	{
		m_ePreDir = DIRECTION_8::RIGHT;
		m_eDir = DIRECTION_8::RIGHT;
	}
	else if (fAngle >= 112.5f && fAngle < 157.5f)  // ↘
	{
		m_ePreDir = DIRECTION_8::LOWERRIGHT;
		m_eDir = DIRECTION_8::LOWERRIGHT;
	}
	else if (fAngle >= 157.5f && fAngle < 202.5f)  // ↓
	{
		m_ePreDir = DIRECTION_8::DOWN;
		m_eDir = DIRECTION_8::DOWN;
	}
	else if (fAngle >= 202.5f && fAngle < 247.5f)  // ↙
	{
		m_ePreDir = DIRECTION_8::LOWERLEFT;
		m_eDir = DIRECTION_8::LOWERLEFT;
	}
	else if (fAngle >= 247.5f && fAngle < 292.5f)  // ←
	{
		m_ePreDir = DIRECTION_8::LEFT;
		m_eDir = DIRECTION_8::LEFT;
	}
	else if (fAngle >= 292.5f && fAngle < 337.5f)  // ↖
	{
		m_ePreDir = DIRECTION_8::UPPERLEFT;
		m_eDir = DIRECTION_8::UPPERLEFT;
	}
	else
	{
		m_eDir = DIRECTION_8::NONE;
	}
}

int CMonsterScript::SearchPathUpdate(int _iSearchX, int _iSearchY, CGameObject* _pSearchObj)
{
	if (m_IsMove == true) return RET_FAILED;

	if (NULL == _pSearchObj)
	{
		// 찾는 GameObj가 없을 경우
		m_fSearchTempTime += DT();

		if (m_fSearchTempTime > m_fSearchTime)
		{
			m_fSearchTempTime = 0.f;
			// 길찾기. 현재위치에서 랜덤 방향으로 3번!
			int iCount = 0;
			bool bMove = false;
			Vec2 vSeekerPos;
			Vec2 vFindPos;
			int iSeekIndexX;
			int iSeekIndexY;

			/*
			{
				// 정론 (연산 비용이 크다.) 현재 위치에서 갈수 있는 위치를 구하고 랜덤으로 뽑아온다.
				vSeekerPos = GetGameObject()->Transform()->GetLocal2DPos();
				vSeekerPos.y -= m_pTileMgr->GetSize().y / 2.f;
				int iMonTileIndexX = m_pTileMgr->GetIndexX(vSeekerPos);
				int iMonTileIndexY = m_pTileMgr->GetIndexY(vSeekerPos);

				int iSearchStartX = iMonTileIndexX - _iSearchX;
				int iSearchStartY = iMonTileIndexY - _iSearchY;
				int iSearchEndX = iMonTileIndexX + _iSearchX;
				int iSearchEndY = iMonTileIndexY + _iSearchY;
				vector<ULONG64> vecSearch;
				for (int y = iSearchStartY; y <= iSearchEndY; ++y)
				{
					for (int x = iSearchStartX; x <= iSearchEndX; ++x)
					{
						if (x == iMonTileIndexX && y == iMonTileIndexY)
							continue;
						ULONG64 llID = m_pTileMgr->FindsetBasic(x, y);
						if (llID == 2000)
							continue;

						vecSearch.push_back(llID);
					}
				}

				UINT iVecSize = vecSearch.size();
				if (iVecSize == 0)
					return RET_FAILED;

				int iRandomIndex = GameRandom::RandomInt(0, iVecSize - 1);
				ULONG64 llSearchID = vecSearch[iRandomIndex];
				vSeekerPos = GetGameObject()->Transform()->GetLocal2DPos();
				iSeekIndexX = HIDWORD(llSearchID);
				iSeekIndexY = LODWORD(llSearchID);
				vFindPos = m_pTileMgr->GetPosFromIndex(iSeekIndexX, iSeekIndexY);
				CMessage* pMsg = new CPathFindingMessage(m_pCollq_Monster->GetName(), vSeekerPos, L"Astar", vFindPos);
				m_pCollq_Monster->SendData(L"AstarMgr", pMsg);
			}
			*/
			while (iCount < 3)
			{
				// 반론. 정론의 연산이 많아서 랜덤으로 3번 탐색하게 사용 탐색 실패할 수 있음.
				++iCount;
				vSeekerPos = GetGameObject()->Transform()->GetLocal2DPos();
				vSeekerPos.y -= m_pTileMgr->GetSize().y / 2.f;
				int iMonTileIndexX = m_pTileMgr->GetIndexX(vSeekerPos);
				int iMonTileIndexY = m_pTileMgr->GetIndexY(vSeekerPos);

				int iRandomX = GameRandom::RandomInt(-_iSearchX, _iSearchX);
				int iRandomY = GameRandom::RandomInt(-_iSearchY, _iSearchY);
				iRandomX = (iRandomX == 0 && iRandomY == 0) ? 1 : iRandomX;

				iSeekIndexX = iMonTileIndexX + iRandomX;
				iSeekIndexY = iMonTileIndexY + iRandomY;
				if (iSeekIndexX < 0 || iSeekIndexY < 0)
					return RET_FAILED;

				bMove = m_pTileMgr->IsMoveToIndex(iSeekIndexX, iSeekIndexY);
				if (true == bMove)
					break;
			}

			if (false == bMove)
				return RET_FAILED;

			vSeekerPos = GetGameObject()->Transform()->GetLocal2DPos();
			vFindPos = m_pTileMgr->GetPosFromIndex(iSeekIndexX, iSeekIndexY);
			CMessage* pMsg = new CPathFindingMessage(m_strCollqName, vSeekerPos, L"Astar", vFindPos);
			m_pCollq_Monster->SendData(L"AstarMgr", pMsg);
		}
	}
	else
	{
		m_fSearchTempTime += DT() * 5;

		if (m_bHit == true || m_fSearchTempTime > m_fSearchTime)
		{
			m_fSearchTempTime = 0.f;
			// 찾는 GameObj가 있을 경우.
			CGameObject* pSearchObj = _pSearchObj;
			Vec2 vSeekerPos;
			Vec2 vFindPos;

			vSeekerPos = GetGameObject()->Transform()->GetLocal2DPos();
			vFindPos = pSearchObj->Transform()->GetLocal2DPos();

			int iSeekIndexX = m_pTileMgr->GetIndexX(vSeekerPos);
			int iSeekIndexY = m_pTileMgr->GetIndexY(vSeekerPos);
			int iFindIndexX = m_pTileMgr->GetIndexX(vFindPos);
			int iFindIndexY = m_pTileMgr->GetIndexY(vFindPos);

			if (iSeekIndexX == iFindIndexX && iSeekIndexY == iFindIndexY)
				return RET_FAILED;

			vSeekerPos = GetGameObject()->Transform()->GetLocal2DPos();

			CMessage* pMsg = new CPathFindingMessage(m_strCollqName, vSeekerPos, L"Astar", vFindPos);
			m_pCollq_Monster->SendData(L"AstarMgr", pMsg);

			m_bHit = false;
		}
	}

	return RET_SUCCESS;
}

bool CMonsterScript::MoveToPos(const Vec2 & _vecPos)
{
	Vec2 vMovePos = _vecPos;
	Vec3 vCurPos = Transform()->GetLocalPos();

	Vec2 vSubPos = (vMovePos - Vec2(vCurPos.x, vCurPos.y));
	float fDist = fabsf(vSubPos.Distance());
	float fMinMoveSpeed = m_fMoveSpeed * DT();
	if (fDist < fMinMoveSpeed) return false;

	Vec2 vDir = vSubPos.Normalize();

	vCurPos.x += vDir.x * fMinMoveSpeed;
	vCurPos.y += vDir.y * fMinMoveSpeed;

	Transform()->SetLocalPos(vCurPos);
	//m_vCurPos = vCurPos;

	return true;
}

float CMonsterScript::DistanceToPos(const Vec2& _vPos)
{
	Vec2 vPos = _vPos;
	Vec2 vCurPos = Transform()->GetLocal2DPos();
	float fDist = Vec2(vPos - vCurPos).Distance();

	return fDist;
}
