#include "stdafx.h"
#include "TileMgrScript.h"
#include "..\External\DefineCode\Tile.h"

CTileMgrScript::CTileMgrScript()
	: m_vStartPos{0.f, 0.f}
	, m_vSize{0.f, 0.f}
	, m_iXCount(0)
	, m_iYCount(0)
	, m_pTile(NULL)
{
}

CTileMgrScript::~CTileMgrScript()
{
	if (NULL != m_pTile)
	{
		for (UINT i = 0; i < m_iYCount; ++i)
		{
			delete[] m_pTile[i];
		}
		delete[] m_pTile;
		m_pTile = NULL;
	}
}

/*
함수명  : GetIndex
용도    : Pos 에 해당하는 Tile index를 리턴한다.
매개변수: const Vec2& _vPos
반환    : vec2 / int / int
수정    : 김동일 (2018.04.14)
*/
int CTileMgrScript::GetIndexX(const Vec2 & _vPos)
{
	int iIndexX = (int)floorf((_vPos.x - m_vStartPos.x) / m_vSize.x + (_vPos.y - m_vStartPos.y) / m_vSize.y);
	return iIndexX;
}

int CTileMgrScript::GetIndexY(const Vec2 & _vPos)
{
	int iIndexY = (int)floorf((_vPos.x - m_vStartPos.x) / m_vSize.x - (_vPos.y - m_vStartPos.y) / m_vSize.y);
	return iIndexY;
}
/*
함수명  : GetPosFromIndex
용도    : Tile 인덱스 정보를 Pos로 변환한다. 피봇값을 기준으로
매개변수: (int _iIndexX, int _iIndexY)
반환    : Vec2
만든이 : 김동일
*/
Vec2 CTileMgrScript::GetPosFromIndex(int _iIndexX, int _iIndexY, float _fPivot)
{
	float fXPos = (_iIndexX + _iIndexY) / 2.f * m_vSize.x + m_vStartPos.x + m_vSize.x / 2.f;
	float fYPos = (_iIndexX - _iIndexY) / 2.f * m_vSize.y + m_vStartPos.y + m_vSize.y / 2.f;
	
	fYPos -= _fPivot;

	return Vec2(fXPos, fYPos);
}


/*
함수명  : CreateTile
용도    : 2차원 Tile 들을 생성 한다.
매개변수: void
반환    : bool
수정    : 김동일 (2018.04.14)
*/
void CTileMgrScript::SetTilesInfo()
{
	bool bSuccess = CreateTile();
	if (!bSuccess) return;

	Vec3 vStartPos = Vec3(m_vStartPos.x + m_vSize.x / 2.f, m_vStartPos.y, 1.f);
	Vec3 vNextPos;
	Vec3 vPos;
	for (UINT y = 0; y < m_iYCount; ++y)
	{
		vNextPos = vStartPos + Vec3(y * m_vSize.x / 2.f, y * -m_vSize.y / 2.f, 0.f);
		for (UINT x = 0; x < m_iXCount; ++x)
		{
			vPos = vNextPos + Vec3(x * m_vSize.x / 2.f, x * m_vSize.y / 2.f, 0.f);
			SetTileInfo(x, y, Vec2(vPos.x, vPos.y), TILE_TYPE::BASIC);
		}
	}

}


bool CTileMgrScript::CreateTile()
{
	if (m_iXCount < 1 || m_iYCount < 1) return false;
	if (NULL != m_pTile) return false;
	m_pTile = new CTile*[m_iYCount];
	for (UINT y = 0; y < m_iYCount; ++y)
	{
		m_pTile[y] = new CTile[m_iXCount];
	}
	return true;
}

/*
함수명  : SetTileInfo
용도    : 2차원 Tile 들의 정보를 셋팅한다.(_vPos는 가운데 위치)
매개변수: UINT _iIndexX, UINT _iIndexY, const Vec2 & _vPos, TILE_TYPE _eType
반환    : void
수정    : 김동일 (2018.04.14)
*/
void CTileMgrScript::SetTileInfo(UINT _iIndexX, UINT _iIndexY, const Vec2 & _vPos, TILE_TYPE _eType)
{
	m_pTile[_iIndexY][_iIndexX].SetIndex(_iIndexY, _iIndexX);
	m_pTile[_iIndexY][_iIndexX].SetPos(_vPos);
	m_pTile[_iIndexY][_iIndexX].SetSize(m_vSize);
	m_pTile[_iIndexY][_iIndexX].SetType(_eType);
}

/*
함수명  : GetTile
용도    : Index 번호를 통해 타일 정보를 반환한다.
매개변수: UINT _iIndexX, UINT _iIndexY
반환    : CTile *
수정    : 김동일 (2018.04.14)
*/
CTile* CTileMgrScript::GetTile(UINT _iIndexX, UINT _iIndexY)
{
	if (NULL == m_pTile) return NULL;
	if (_iIndexX < 0 || _iIndexX >= m_iXCount ||
		_iIndexY < 0 || _iIndexY >= m_iYCount)
		return NULL;

	return &m_pTile[_iIndexX][_iIndexY];
}

bool CTileMgrScript::HasTile(const Vec2 & _vPos)
{
	if (NULL == m_pTile) return false;

	int iFindIndexX = GetIndexX(_vPos);
	int iFindIndexY = GetIndexY(_vPos);

	if (iFindIndexX < 0 || iFindIndexX >= (int)m_iXCount ||
		iFindIndexY < 0 || iFindIndexY >= (int)m_iYCount)
		return false;

	return true;
}

TILE_TYPE CTileMgrScript::GetTileType(UINT _indexX, UINT _indexY)
{
	TILE_TYPE eType = m_pTile[_indexX][_indexY].GetType();

	return eType;
}

bool CTileMgrScript::IsMoveToPos(const Vec2 & _vPos)
{
	if (NULL == m_pTile) return false;

	int iFindIndexX = GetIndexX(_vPos);
	int iFindIndexY = GetIndexY(_vPos);

	if (iFindIndexX < 0 || iFindIndexX >= (int)m_iXCount ||
		iFindIndexY < 0 || iFindIndexY >= (int)m_iYCount)
		return false;

	TILE_TYPE eType = GetTileType(iFindIndexX, iFindIndexY);
	if (TILE_TYPE::BLOCK == eType)
		return false;

	return true;
}

bool CTileMgrScript::IsMoveToPos(const Vec2 & _vPos, Vec2& _vTilePos)
{
	if (NULL == m_pTile) return false;

	int iFindIndexX = GetIndexX(_vPos);
	int iFindIndexY = GetIndexY(_vPos);

	if (iFindIndexX < 0 || iFindIndexX >= (int)m_iXCount ||
		iFindIndexY < 0 || iFindIndexY >= (int)m_iYCount)
		return false;

	TILE_TYPE eType = GetTileType(iFindIndexX, iFindIndexY);
	if (TILE_TYPE::BLOCK == eType)
		return false;

	_vTilePos = GetPosFromIndex(iFindIndexX, iFindIndexY, m_vSize.y / 2.f);
	return true;
}

bool CTileMgrScript::IsMoveToIndex(int _indexX, int _indexY)
{
	if (NULL == m_pTile) return false;

	int iFindIndexX = _indexX;
	int iFindIndexY = _indexY;

	if (iFindIndexX < 0 || iFindIndexX >= (int)m_iXCount ||
		iFindIndexY < 0 || iFindIndexY >= (int)m_iYCount)
		return false;

	TILE_TYPE eType = GetTileType(iFindIndexX, iFindIndexY);
	if (TILE_TYPE::BLOCK == eType)
		return false;

	return true;
}

/*
함수명  : FindsetBasic(UINT _iIndexX, UINT _iIndexY)
용도    : setBasic에서 찾는다. (에러값은 2000)
*/
ULONG64 CTileMgrScript::FindsetBasic(UINT _iIndexX, UINT _iIndexY)
{
	PATH_NODE_ID id;
	id.iIndexXID = _iIndexX;
	id.iIndexYID = _iIndexY;

	ULONG64 iIndexXY = id.llID;

	set<ULONG64>::iterator iter = m_setBasic.find(iIndexXY);
	auto setNull = m_setBasic.end();
	
	if (iter == setNull)
		return 2000;

	return *iter;
}


void CTileMgrScript::Destory()
{
	if (NULL != m_pTile)
	{
		for (UINT i = 0; i < m_iYCount; ++i)
		{
			delete[] m_pTile[i];
		}
		delete[] m_pTile;
		m_pTile = NULL;
	}
}

int CTileMgrScript::update()
{
	return 0;
}

void CTileMgrScript::Save(FILE * _pFile)
{
	fwrite(&m_vStartPos, sizeof(Vec2), 1, _pFile);
	fwrite(&m_vSize, sizeof(Vec2), 1, _pFile);
	fwrite(&m_iXCount, sizeof(UINT), 1, _pFile);
	fwrite(&m_iYCount, sizeof(UINT), 1, _pFile);
}

void CTileMgrScript::Load(FILE * _pFile)
{
	fread(&m_vStartPos, sizeof(Vec2), 1, _pFile);
	fread(&m_vSize, sizeof(Vec2), 1, _pFile);
	fread(&m_iXCount, sizeof(UINT), 1, _pFile);
	fread(&m_iYCount, sizeof(UINT), 1, _pFile);
	g_bLoad = true;
	g_pThis = this;
	SetTilesInfo();
}
