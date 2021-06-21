#pragma once
#include "Component.h"

#include "ResPtr.h"

class CMesh;
class CMaterial;

class CMeshRender :
	public CComponent
{
private:
	CResPtr<CMesh>		m_pMesh;
	CResPtr<CMaterial>	m_pMtrl;
	RASTERIZE_TYPE		m_eRT;

	bool				m_bEnable;

public:
	virtual int update() { return RET_SUCCESS; };
	virtual void render();

public:
	void SetMesh(CMesh* _pMesh) { m_pMesh = _pMesh; }
	void SetMaterial(CMaterial* _pMaterial) { m_pMtrl = _pMaterial; }
	void SetRSMode(RASTERIZE_TYPE _eMode) { m_eRT = _eMode; }

	void SetEnable(bool _bShow) { m_bEnable = _bShow; }
	bool GetEnable() const { return m_bEnable; }

public:
	CMesh* GetMesh() { return m_pMesh; };
	CMaterial* GetSharedMaterial() { return m_pMtrl; }
	CMaterial* GetMaterial();
	RASTERIZE_TYPE GetRSType() { return m_eRT; }
	ULONG64 GetInstID();

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);
	virtual CMeshRender* Clone() { return new CMeshRender(*this); }

public:
	CMeshRender();
	virtual ~CMeshRender();
};

