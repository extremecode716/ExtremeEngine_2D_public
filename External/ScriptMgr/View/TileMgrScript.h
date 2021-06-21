#pragma once
#include "..\SingletonScript.h"

#include "..\\External\DefineCode\DefineScript.h"

class CTile;

class CTileMgrScript :
	public CSingletonScript<CTileMgrScript>
{
private:
	Vec2	        m_vStartPos;
	Vec2	        m_vSize;
	UINT	        m_iXCount;
	UINT	        m_iYCount;

	CTile**			m_pTile;

	// 갈 수 있는 지형위치 저장
	set<ULONG64>	m_setBasic;

public:
	const Vec2& GetStartPos() const { return m_vStartPos; }
	const Vec2& GetSize() const { return m_vSize; }
	UINT GetXCount() const { return m_iXCount; }
	UINT GetYCount() const { return m_iYCount; }
	int GetIndexX(const Vec2& _vPos);
	int GetIndexY(const Vec2& _vPos);

	Vec2 GetPosFromIndex(int _iIndexX, int _iIndexY, float _fPivot = 20);

	void SetTilesInfo();
	bool CreateTile();
	void SetTileInfo(UINT _iIndexX, UINT _iIndexY, const Vec2& _vPos, TILE_TYPE _eType);
	CTile** GetTile() const { return m_pTile; }
	CTile* GetTile(UINT _iIndexX, UINT _iIndexY);
	bool HasTile(const Vec2& _vPos);
	TILE_TYPE GetTileType(UINT _indexX, UINT _indexY);
	bool IsMoveToPos(const Vec2& _vPos);
	bool IsMoveToPos(const Vec2& _vPos, Vec2& _vTilePos);
	bool IsMoveToIndex(int _indexX, int _indexY);
	set<ULONG64>& GetsetBasic() { return m_setBasic; }
	ULONG64 FindsetBasic(UINT _iIndexX, UINT _iIndexY);

	void Destory();

public:
	virtual int update() override;
	virtual void Save(FILE* _pFile) override;
	virtual void Load(FILE* _pFile) override;

public:
	virtual CTileMgrScript* Clone() override { return new CTileMgrScript(*this); }

public:
	CTileMgrScript();
	virtual ~CTileMgrScript();

	friend class CMapTool_2D;
};

