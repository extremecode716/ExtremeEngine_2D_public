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
�Լ���  : GetIndex
�뵵    : Pos �� �ش��ϴ� Tile index�� �����Ѵ�.
�Ű�����: const Vec2& _vPos
��ȯ    : vec2 / int / int
����    : �赿�� (2018.04.14)
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
�Լ���  : GetPosFromIndex
�뵵    : Tile �ε��� ������ Pos�� ��ȯ�Ѵ�. �Ǻ����� ��������
�Ű�����: (int _iIndexX, int _iIndexY)
��ȯ    : Vec2
������ : �赿��
*/
Vec2 CTileMgrScript::GetPosFromIndex(int _iIndexX, int _iIndexY, float _fPivot)
{
	float fXPos = (_iIndexX + _iIndexY) / 2.f * m_vSize.x + m_vStartPos.x + m_vSize.x / 2.f;
	float fYPos = (_iIndexX - _iIndexY) / 2.f * m_vSize.y + m_vStartPos.y + m_vSize.y / 2.f;
	
	fYPos -= _fPivot;

	return Vec2(fXPos, fYPos);
}


/*
�Լ���  : CreateTile
�뵵    : 2���� Tile ���� ���� �Ѵ�.
�Ű�����: void
��ȯ    : bool
����    : �赿�� (2018.04.14)
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
�Լ���  : SetTileInfo
�뵵    : 2���� Tile ���� ������ �����Ѵ�.(_vPos�� ��� ��ġ)
�Ű�����: UINT _iIndexX, UINT _iIndexY, const Vec2 & _vPos, TILE_TYPE _eType
��ȯ    : void
����    : �赿�� (2018.04.14)
*/
void CTileMgrScript::SetTileInfo(UINT _iIndexX, UINT _iIndexY, const Vec2 & _vPos, TILE_TYPE _eType)
{
	m_pTile[_iIndexY][_iIndexX].SetIndex(_iIndexY, _iIndexX);
	m_pTile[_iIndexY][_iIndexX].SetPos(_vPos);
	m_pTile[_iIndexY][_iIndexX].SetSize(m_vSize);
	m_pTile[_iIndexY][_iIndexX].SetType(_eType);
}

/*
�Լ���  : GetTile
�뵵    : Index ��ȣ�� ���� Ÿ�� ������ ��ȯ�Ѵ�.
�Ű�����: UINT _iIndexX, UINT _iIndexY
��ȯ    : CTile *
����    : �赿�� (2018.04.14)
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
�Լ���  : FindsetBasic(UINT _iIndexX, UINT _iIndexY)
�뵵    : setBasic���� ã�´�. (�������� 2000)
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
