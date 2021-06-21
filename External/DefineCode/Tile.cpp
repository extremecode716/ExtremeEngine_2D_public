#include "stdafx.h"
#include "Tile.h"

#include "..\External\ScriptMgr\View\TileMgrScript.h"

CTile::CTile()
	: m_iIndexX(0)
	, m_iIndexY(0)
	, m_vPos{0.f, 0.f}
	, m_vSize{ 0.f, 0.f }
	, m_eType(TILE_TYPE::BASIC)
{
}


CTile::~CTile()
{
}


void CTile::SetIndex(UINT _x, UINT _y)
{
	m_iIndexX = _x;
	m_iIndexY = _y;
}

void CTile::SetPos(const Vec2 & _vPos)
{
	m_vPos = _vPos;
}

void CTile::SetSize(const Vec2 & _vSize)
{
	m_vSize = _vSize;
}

void CTile::SetType(TILE_TYPE _eType)
{
	m_eType = _eType;

	// 갈수있는 타입들을 Tile Mgr에 셋팅한다.
	PATH_NODE_ID id;
	id.iIndexXID = m_iIndexX;
	id.iIndexYID = m_iIndexY;
	set<ULONG64>& setBasic = CTileMgrScript::GetThis()->GetsetBasic();
	set<ULONG64>::iterator iter = setBasic.find(id.llID);

	if (iter == setBasic.end())
	{
		if (TILE_TYPE::BASIC == _eType)
		{
			setBasic.insert(id.llID);
		}
	}
	else
	{
		if (TILE_TYPE::BASIC != _eType)
		{
			setBasic.erase(iter);
		}
	}
}