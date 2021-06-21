#include "stdafx.h"
#include "AstarMgr.h"

#include "TileMgrScript.h"
#include "..\External\DefineCode\Tile.h"

#include "MediatorMgr.h"
#include "..\External\DefineCode\MessageColleaque.h"
#include "..\External\DefineCode\FindMessage.h"
#include "..\External\DefineCode\PathFindingMessage.h"


CAstarMgr::CAstarMgr()
{
}


CAstarMgr::~CAstarMgr()
{
	Safe_Delete_Stack(m_stackPath);
	Safe_Delete_List(m_listOpen);
	Safe_Delete_Map(m_mapClose);
	Safe_Delete_List(m_listOverlapMapClose);
	m_listOverlapMapClose.clear();
	m_listOpen.clear();
	m_mapClose.clear();
}


void CAstarMgr::awake()
{
	// Ÿ�� ����
	m_pTileMgrScript = CTileMgrScript::GetThis();

	// Mediator
	m_pMediator = CMediatorMgr::GetInst();
	m_pCollq_Astar = CMessageColleaque::Create(m_pMediator, L"AstarMgr", this);
}


/*
�Լ���  : Init
�뵵    : Astar���۽��۽� ȣ��Ǵ� �ʱ�ȭ �Լ�
�Ű�����: void
��ȯ    : void
����    : �赿�� (2018.04.14)
*/
void CAstarMgr::Init()
{
	if (NULL == m_pTileMgrScript) return;

	// �ӽ� ��
	//CTile* pTile = m_pTileMgrScript->GetTile(0, 5);
	//pTile->SetType(TILE_TYPE::BLOCK);
	// pTile = m_pTileMgrScript->GetTile(1, 5);
	// pTile->SetType(TILE_TYPE::BLOCK);
	// pTile = m_pTileMgrScript->GetTile(2, 5);
	// pTile->SetType(TILE_TYPE::BLOCK);
	// pTile = m_pTileMgrScript->GetTile(3, 5);
	// pTile->SetType(TILE_TYPE::BLOCK);
	// pTile = m_pTileMgrScript->GetTile(4, 5);
	// pTile->SetType(TILE_TYPE::BLOCK);
	// pTile = m_pTileMgrScript->GetTile(5, 5);
	// pTile->SetType(TILE_TYPE::BLOCK);
	// pTile = m_pTileMgrScript->GetTile(5, 4);
	// pTile->SetType(TILE_TYPE::BLOCK);
	 //pTile = m_pTileMgrScript->GetTile(5, 3);
	 //pTile->SetType(TILE_TYPE::BLOCK);
	 //pTile = m_pTileMgrScript->GetTile(5, 2);
	 //pTile->SetType(TILE_TYPE::BLOCK);
	 //pTile = m_pTileMgrScript->GetTile(5, 1);
	 //pTile->SetType(TILE_TYPE::BLOCK);
	 //pTile = m_pTileMgrScript->GetTile(5, 0);
	 //pTile->SetType(TILE_TYPE::BLOCK);

	//Safe_Delete_Stack(m_stackPath);
}


/*
�Լ���  : AStarStart
�뵵    : AStar ���� �Լ� (LoopCount ����)
�Ű�����: UINT _iStartIndexX, UINT _iStartIndexY, UINT _iDestIndexX, UINT _iDestIndexY, UINT iMaxLoopCount = 100
��ȯ    : bool
����    : �赿�� (2018.04.14)
*/
bool CAstarMgr::AStarStart(UINT _iStartIndexX, UINT _iStartIndexY, UINT _iDestIndexX, UINT _iDestIndexY, UINT iMaxLoopCount)
{
	if (NULL == m_pTileMgrScript) return false;
	CTile* pStartTile = m_pTileMgrScript->GetTile(_iStartIndexX, _iStartIndexY);
	CTile* pDestTile = m_pTileMgrScript->GetTile(_iDestIndexX, _iDestIndexY);
	if (NULL == pStartTile || NULL == pDestTile) return false;

	UINT iLoopCount = 0;
	bool bSuccess = false;
	list<CTile*> listNeighbor;
	tPathNode* pNode = new tPathNode();
	pNode->iIndexX = _iStartIndexX;
	pNode->iIndexY = _iStartIndexY;
	m_listOpen.push_back(pNode);

	while (m_listOpen.size() > 0)
	{
		++iLoopCount;
		if (iLoopCount > iMaxLoopCount)
		{
			break;
		}
		pNode = m_listOpen.front();
		m_listOpen.pop_front();

		PATH_NODE_ID ID;
		ID.iIndexXID = pNode->iIndexX;
		ID.iIndexYID = pNode->iIndexY;
		
		map<ULONG64, tPathNode*>::iterator mapIter = m_mapClose.find(ID.llID);
		if (mapIter == m_mapClose.end())
		{
			m_mapClose.insert(make_pair(ID.llID, pNode));
		}
		else
		{
			m_listOverlapMapClose.push_back(pNode);
		}

		FindNeighborCanGo(ID.iIndexXID, ID.iIndexYID, listNeighbor);

		while (listNeighbor.size() > 0)
		{
			CTile* pNeighborTile = listNeighbor.front();
			listNeighbor.pop_front();

			tPathNode* pNeighborNode = new tPathNode();
			UINT iNeighborIndexX = pNeighborTile->GetIndexX();
			UINT iNeighborIndexY = pNeighborTile->GetIndexY();

			pNeighborNode->pParrentNode = pNode;
			pNeighborNode->iIndexX = iNeighborIndexX;
			pNeighborNode->iIndexY = iNeighborIndexY;
			pNeighborNode->fCostG = CalCostG(pNode->fCostG, pNode->iIndexX, pNode->iIndexY, iNeighborIndexX, iNeighborIndexY);
			pNeighborNode->fCostH = CalHeuristic(iNeighborIndexX, iNeighborIndexY, _iDestIndexX, _iDestIndexY);
			pNeighborNode->fCostF = pNeighborNode->fCostG + pNeighborNode->fCostH;

			m_listOpen.push_back(pNeighborNode);

			// ��� Ž�� �Ϸ�.
			if (pNeighborNode->iIndexX == _iDestIndexX && pNeighborNode->iIndexY == _iDestIndexY)
			{
				while (NULL != pNeighborNode->pParrentNode)
				{
					tPathNode* pPathFindNode = new tPathNode();
					pPathFindNode->iIndexX = pNeighborNode->iIndexX;
					pPathFindNode->iIndexY = pNeighborNode->iIndexY;
					pPathFindNode->fCostG = pNeighborNode->fCostG;
					pPathFindNode->fCostH = pNeighborNode->fCostH;
					pPathFindNode->fCostF = pNeighborNode->fCostF;
					pPathFindNode->pParrentNode = pNeighborNode->pParrentNode;
#ifdef _EXTREME_TOOL
					CDebugMgr::GetInst()->Log(to_wstring(pPathFindNode->iIndexX) + L"   " + to_wstring(pPathFindNode->iIndexY));
#endif
					m_stackPath.push(pPathFindNode);

					pNeighborNode = pPathFindNode->pParrentNode;
				}	
				bSuccess = true;
				break;
			}
		}

		if (bSuccess)
		{
			Safe_Delete_List(m_listOverlapMapClose);
			Safe_Delete_List(m_listOpen);
			Safe_Delete_Map(m_mapClose);
			m_listOverlapMapClose.clear();
			m_listOpen.clear();
			m_mapClose.clear();
			return true;
		}
		m_listOpen.sort([](tPathNode* _pLeft, tPathNode* _pRight)
		{
			return _pLeft->fCostF < _pRight->fCostF;
		});
	}

	Safe_Delete_List(m_listOverlapMapClose);
	Safe_Delete_Stack(m_stackPath);
	Safe_Delete_List(m_listOpen);
	Safe_Delete_Map(m_mapClose);
	m_listOverlapMapClose.clear();
	m_listOpen.clear();
	m_mapClose.clear();

	return bSuccess;
}


int CAstarMgr::update()
{
	return 0;
}

void CAstarMgr::GetMessageData(CMessage * _pData)
{
	if (NULL == _pData) return;
	MessageType eType = _pData->GetType();

	switch (eType)
	{
	case MessageType::NONE_MT:
		break;
	case MessageType::ATTACK_MT:
		break;
	case MessageType::FIND_MT:
	{
	}
	break;
	case MessageType::PATHFIND_MT:
	{
		// PATHFIND �޼����� ������ ��ã�� �˰����� ������ ã�� ����� �ٽ� �����ش�. 
		m_pTileMgrScript = CTileMgrScript::GetThis();
		if (NULL == m_pTileMgrScript)
		{
			SAFE_DELETE(_pData);
			break;
		}
		bool bSuccess = false;
		CPathFindingMessage* pPathFindMt = static_cast<CPathFindingMessage*>(_pData);
		
		Vec2 vSeekerPos = pPathFindMt->GetSeekerPos();
		//vSeekerPos.y -= m_pTileMgrScript->GetSize().y / 2.f;
		Vec2 vFindPos = pPathFindMt->GetFindPos();

		int iSeekerIndexX = m_pTileMgrScript->GetIndexX(vSeekerPos);
		int iSeekerIndexY = m_pTileMgrScript->GetIndexY(vSeekerPos);

		int iFindIndexX = m_pTileMgrScript->GetIndexX(vFindPos);
		int iFindIndexY = m_pTileMgrScript->GetIndexY(vFindPos);

		if (iSeekerIndexX == iFindIndexX && iSeekerIndexY == iFindIndexY)
		{
			SAFE_DELETE(pPathFindMt);
			break;
		}

		Init();
		bSuccess = AStarStart(iSeekerIndexX, iSeekerIndexY, iFindIndexX, iFindIndexY);
		if (!bSuccess)
		{
			SAFE_DELETE(pPathFindMt);
			break;
		}

		pPathFindMt->SetPathFinding(m_stackPath);
		m_pCollq_Astar->SendData(pPathFindMt->GetSeekerKey(), pPathFindMt);
		Safe_Delete_Stack(m_stackPath);
	}
	break;
	case MessageType::ERROR_MT:
		SAFE_DELETE(_pData);
		break;
	default:
		SAFE_DELETE(_pData);
		break;
	}
}

/*
�Լ���  : CalHeuristic
�뵵    : �������� ������ġ���� �޸���ƽ ����� ���.
�Ű�����: UINT _iCurIndexX, UINT _iCurIndexY, UINT _iDestIndexX, UINT _iDestIndexY
��ȯ    : float
����    : �赿�� (2018.04.14)
*/
float CAstarMgr::CalHeuristic(UINT _iCurIndexX, UINT _iCurIndexY, UINT _iDestIndexX, UINT _iDestIndexY)
{
	CTile* pCurTile = m_pTileMgrScript->GetTile(_iCurIndexX, _iCurIndexY);
	CTile* pDestTile = m_pTileMgrScript->GetTile(_iDestIndexX, _iDestIndexY);
	
	float fDistX = fabsf(pDestTile->GetPosX() - pCurTile->GetPosX());
	float fDIstY = fabsf(pDestTile->GetPosY() - pCurTile->GetPosY());

	return fDistX + fDIstY;
	//int iCurX = _iCurIndexX;
	//int iCurY = _iCurIndexY;

	//int iDestX = _iDestIndexX;
	//int iDestY = _iDestIndexY;

	//float fResult= abs(iDestX - iCurX) + abs(iDestY - iCurX);


	//return fResult;
}

/*
�Լ���  : CalCostG
�뵵    : �̿� ������� G ����� ���. 
�Ű�����: UINT _iCurIndexX, UINT _iCurIndexY, UINT _iNeighborIndexX, UINT _iNeighborIndexY
��ȯ    : float
����    : �赿�� (2018.04.14) 
*/
float CAstarMgr::CalCostG(float _fCostG, UINT _iCurIndexX, UINT _iCurIndexY, UINT _iNeighborIndexX, UINT _iNeighborIndexY)
{

	float fCostG = 0.f;

	int iSubIdex = (_iCurIndexX + _iCurIndexY) - (_iNeighborIndexX + _iNeighborIndexY);
	iSubIdex = abs(iSubIdex);

	if (iSubIdex == 2)
	{
		fCostG = 240.0f;
	}
	else if (iSubIdex == 0)
	{
		fCostG = 240.0f;
	}
	else
	{
		fCostG = 100.0f;
	}

	fCostG += _fCostG;

	return fCostG;
}


/*
�Լ���  : FindNeighborCanGo
�뵵    : push�� �̿�����Ʈ�� �����ִ� �̿�Ÿ�ϵ��� �־��ش�.
�Ű�����: UINT _iIndexX, UINT _iIndexY, list<CTile*>& _listNeighbor
��ȯ    : void
����    : �赿�� (2018.04.14)
*/
void CAstarMgr::FindNeighborCanGo(UINT _iIndexX, UINT _iIndexY, list<CTile*>& _listNeighbor)
{
	_listNeighbor.clear();
	map<ULONG64, tPathNode*>::iterator mapIter;
	CTile* pNeighborTile;

	PATH_NODE_ID ID;
	ID.iIndexXID = _iIndexX + 1;
	ID.iIndexYID = _iIndexY + 1;
	mapIter = m_mapClose.find(ID.llID);

	if (mapIter == m_mapClose.end())
	{
		// �� �̿�
		pNeighborTile = m_pTileMgrScript->GetTile(_iIndexX + 1, _iIndexY + 1);
		if (NULL != pNeighborTile)
		{
			if (TILE_TYPE::BASIC == pNeighborTile->GetType())
				_listNeighbor.push_back(pNeighborTile);
		}
	}

	ID.iIndexXID = _iIndexX - 1;
	ID.iIndexYID = _iIndexY - 1;
	mapIter = m_mapClose.find(ID.llID);

	if (mapIter == m_mapClose.end())
	{
		// �� �̿�
		pNeighborTile = m_pTileMgrScript->GetTile(_iIndexX - 1, _iIndexY - 1);
		if (NULL != pNeighborTile)
		{
			if (TILE_TYPE::BASIC == pNeighborTile->GetType())
				_listNeighbor.push_back(pNeighborTile);
		}
	}

	ID.iIndexXID = _iIndexX + 1;
	ID.iIndexYID = _iIndexY - 1;
	mapIter = m_mapClose.find(ID.llID);

	if (mapIter == m_mapClose.end())
	{
		// �� �̿�
		pNeighborTile = m_pTileMgrScript->GetTile(_iIndexX + 1, _iIndexY - 1);
		if (NULL != pNeighborTile)
		{
			if (TILE_TYPE::BASIC == pNeighborTile->GetType())
				_listNeighbor.push_back(pNeighborTile);
		}
	}

	ID.iIndexXID = _iIndexX - 1;
	ID.iIndexYID = _iIndexY + 1;
	mapIter = m_mapClose.find(ID.llID);

	if (mapIter == m_mapClose.end())
	{
		// �� �̿�
		pNeighborTile = m_pTileMgrScript->GetTile(_iIndexX - 1, _iIndexY + 1);
		if (NULL != pNeighborTile)
		{
			if (TILE_TYPE::BASIC == pNeighborTile->GetType())
				_listNeighbor.push_back(pNeighborTile);
		}
	}

	ID.iIndexXID = _iIndexX + 1;
	ID.iIndexYID = _iIndexY;
	mapIter = m_mapClose.find(ID.llID);

	if (mapIter == m_mapClose.end())
	{
		// �� �̿�
		pNeighborTile = m_pTileMgrScript->GetTile(_iIndexX + 1, _iIndexY);
		if (NULL != pNeighborTile)
		{
			if (TILE_TYPE::BASIC == pNeighborTile->GetType())
				_listNeighbor.push_back(pNeighborTile);
		}
	}

	ID.iIndexXID = _iIndexX;
	ID.iIndexYID = _iIndexY - 1;
	mapIter = m_mapClose.find(ID.llID);

	if (mapIter == m_mapClose.end())
	{
		// �� �̿�
		pNeighborTile = m_pTileMgrScript->GetTile(_iIndexX, _iIndexY - 1);
		if (NULL != pNeighborTile)
		{
			if (TILE_TYPE::BASIC == pNeighborTile->GetType())
				_listNeighbor.push_back(pNeighborTile);
		}
	}

	ID.iIndexXID = _iIndexX;
	ID.iIndexYID = _iIndexY + 1;
	mapIter = m_mapClose.find(ID.llID);

	if (mapIter == m_mapClose.end())
	{
		// �� �̿�
		pNeighborTile = m_pTileMgrScript->GetTile(_iIndexX, _iIndexY + 1);
		if (NULL != pNeighborTile)
		{
			if (TILE_TYPE::BASIC == pNeighborTile->GetType())
				_listNeighbor.push_back(pNeighborTile);
		}
	}

	ID.iIndexXID = _iIndexX - 1;
	ID.iIndexYID = _iIndexY;
	mapIter = m_mapClose.find(ID.llID);

	if (mapIter == m_mapClose.end())
	{
		// �� �̿�
		pNeighborTile = m_pTileMgrScript->GetTile(_iIndexX - 1, _iIndexY);
		if (NULL != pNeighborTile)
		{
			if (TILE_TYPE::BASIC == pNeighborTile->GetType())
				_listNeighbor.push_back(pNeighborTile);
		}
	}
	
}

