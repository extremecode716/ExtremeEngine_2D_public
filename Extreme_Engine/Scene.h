#pragma once

#include "global.h"

class CLayer;
struct tLayerInfo;
class CGameObject;
class CScene
{
private:
	map<wstring, CLayer*>	m_mapLayer;
	vector<CLayer*>			m_vecLayer;
	set<UINT>				m_setLayerIdx;

public:
	void awake();
	void start();
	int update();
	int lateupdate();
	int finalupdate();
	void render();

	void render(CGameObject* _pCameObj);

	bool Save(const wstring& _strPath);
	bool Load(const wstring& _strPath);

public:
	int AddLayer(const wstring& _strLayerName);
	int AddLayer(CLayer* _pLayer);
	void DeleteLayer(const wstring& _strKey);

	CLayer* FindLayer(const wstring& _strLayerName);
	CGameObject* FindObject(Vec2& _vWindowPos, Vec2& _vResolution);

	int ChangeLayer(const wstring& _strLayerName, CGameObject* _pObj);

	void GetAllParentObjects(list<CGameObject*>& _listObj);
	UINT GetLayerCount() { return m_mapLayer.size(); }


	void GetLayers(vector<tLayerInfo>& _vecOutLayer);
	void EraseParentObjToLayer(const wstring& _strLayerName, CGameObject* _pParentObj);

private:
	UINT GetLayerIdx();
	vector<CLayer*>& GetVecLayer() { return m_vecLayer; }

public:
	Vec2 Get2DWorldPosFromWindowPos(Vec2& _vWindowPos, Vec2& _vResolution);

public:
	CScene();
	~CScene();

	friend class CCamera;
	friend class CCollisionMgr;
	friend class CDestroyMgr;
	friend class CSaveLoadMgr;
};

