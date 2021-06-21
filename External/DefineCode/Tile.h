#pragma once
#include "DefineScript.h"

class CTile
{
private:
	UINT      m_iIndexX;
	UINT      m_iIndexY;
	
	Vec2      m_vPos;
	Vec2      m_vSize;
	TILE_TYPE m_eType;

public:
	void SetIndex(UINT _x, UINT _y);
	void SetPos(const Vec2& _vPos);
	void SetSize(const Vec2& _vSize);
	void SetType(TILE_TYPE _eType);

	UINT GetIndexX() const { return m_iIndexX; }
	UINT GetIndexY() const { return m_iIndexY; }
	float GetPosX() const { return m_vPos.x; }
	float GetPosY() const { return m_vPos.y; }
	TILE_TYPE GetType() const { return m_eType; }

public:
	CTile();
	virtual ~CTile();
};

