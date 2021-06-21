#pragma once
#include "Component.h"

union uInstID
{
	struct
	{
		UINT iMesh;
		UINT iMtrl;
	};
	ULONG64 IllD;
};

class CLayer;

class CCamera :
	public CComponent
{
private:
	Matrix		m_matView;
	Matrix		m_matProj;

	bool		m_bPerspective;

	// 원근 
	float		m_fFOV;

	// 직교
	float		m_fWidth;
	float		m_fHeight;
	float		m_fScale;

	// 공통
	float		m_fNear;
	float		m_fFar;

	UINT		m_iLayerCheck;

	// Instancing Group
	map<ULONG64, vector<CGameObject*>*> m_mapInstGroup;
	vector<CGameObject*>				m_vecSingleObj;

public:
	virtual int update();
	virtual int finalupdate();

	void render(CLayer* _pLayer);
	void render();
	
	// 전체 z order
	void render(CLayer* _pLayer, list<CGameObject*>& _listObj);

public:
	void LayerRenderCheck(const wstring& _strLayerName);
	UINT GetLayerRenderCheck() const { return m_iLayerCheck; }
	void SetAllLayerRenderCheck() { m_iLayerCheck = 0xffffffff; }
	void SetPos(Vec3& _vec3);
	void SetScale(float _fScale) { m_fScale = _fScale; }
	float GetScale() { return m_fScale; };
	const Matrix& GetProjMat() { return m_matProj; }
	const Matrix& GetViewMat() { return m_matView; }
	void Reset();

private:
	void UpdateInstancing();

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);
	virtual CCamera* Clone() { return new CCamera(*this); }

public:
	CCamera();
	virtual ~CCamera();
};

