#pragma once
#include "..\SingletonScript.h"
#include "..\External\DefineCode\DefineScript.h"

class CMediatorMgr;
class CColleaque;
class CTile;
class CTileMgrScript;

class CAstarMgr
	: public CSingletonScript<CAstarMgr>
{
private:
	CTileMgrScript* m_pTileMgrScript;

	stack<tPathNode*> m_stackPath;
	list<tPathNode*> m_listOpen;
	map<ULONG64, tPathNode*> m_mapClose;
	list<tPathNode*> m_listOverlapMapClose;

	CMediatorMgr*				m_pMediator;
	CColleaque*					m_pCollq_Astar;

private:
	float CalHeuristic(UINT _iCurIndexX, UINT _iCurIndexY, UINT _iDestIndexX, UINT _iDestIndexY);
	float CalCostG(float _fCostG , UINT _iCurIndexX, UINT _iCurIndexY, UINT _iNeighborIndexX, UINT _iNeighborIndexY);
	void FindNeighborCanGo(UINT _iIndexX, UINT _iIndexY, list<CTile*>& _listNeighbor);

public:
	void Init();
	bool AStarStart(UINT _iStartIndexX, UINT _iStartIndexY, UINT _iDestIndexX, UINT _iDestIndexY, UINT iMaxLoopCount = 100);
	
	virtual void awake() override;
	virtual int update() override;

public:
	virtual void GetMessageData(CMessage* _pData) override;

public:
	virtual CAstarMgr* Clone() override { return new CAstarMgr(*this); }

public:
	CAstarMgr();
	virtual ~CAstarMgr();
};

