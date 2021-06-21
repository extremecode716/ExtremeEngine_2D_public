#pragma once

#include "global.h"

class CGameObject;

class CLayer
{
private:
	wstring				m_strLayerName;
	list<CGameObject*>	m_listObj;
	list<CGameObject*>  m_listParentObj;

	int					m_iIdx;
	// Z order sort
	bool				m_bZOrder;

public:
	void awake();
	void start();
	int update();
	int lateupdate();
	int finalupdate();

	void render();
	// ÀüÃ¼ zorder¿ë
	void render(list<CGameObject*>& _listObj);

private:
	bool IsEmpty();
	void SetLayerIdx(UINT _iLayerIdx) { m_iIdx = _iLayerIdx; }
	void SetLayerName(const wstring& _strLayerName) { m_strLayerName = _strLayerName; }
	void SetZOrder(bool _bZOrder) { m_bZOrder = _bZOrder; }
	void EraseParentThisObj(CGameObject* _pObj);
	void EraseObjFromLayer(CGameObject* _pObj);
	void EraseObjFromLayer_DontDestroy(CGameObject* _pObj);
	void RemoveObj(CGameObject* _pObj);
	void RemoveParentObj(CGameObject* _pObj);

	list<CGameObject*>& GetObjList() { return m_listObj; }
	list<CGameObject*>& GetParentObjList() { return m_listParentObj; }
public:
	UINT GetLayerIdx() { return m_iIdx; }
	const wstring& GetLayerName() { return m_strLayerName; }
	void AddGameObject(CGameObject* _pObj, bool _bAll = true, bool _bPrefab = false);
	CGameObject* FindObjectByTag(const wstring& _strTag);
	CGameObject* FindObject(const Vec2& _vWorldPos);
	void AddParentObject(CGameObject* _pParentObj);

public:
	CGameObject*	FindWithTag(const wstring& _strObjName);
	CGameObject*    FindGameObject(CGameObject* _gameObj);
	void SubGameObject(CGameObject* _gameObj);
	void SubGameObject(const wstring& _strObjName);

	void SubGameObjectByChild(CGameObject* _pObj);
	void Destory(const wstring& _strObjName);

public:
	CLayer();
	~CLayer();

	friend class CCamera;
	friend class CScene;
	friend class CSceneMgr;
	friend class CGameObject;
	friend class CCollisionMgr;
	friend class CSaveLoadMgr;
};

struct tLayerInfo
{
	wstring		strName;
	CLayer*		pLayer;
};
