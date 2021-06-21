#pragma once
#include "Component.h"

#include "ResPtr.h"

class CMesh;
class CMaterial;

class CCollider :
	public CComponent
{
	static UINT g_iColID;

protected:
	UINT				m_iColID;
	bool				m_bEnable;
	CResPtr<CMesh>		m_pMesh;
	CResPtr<CMaterial>	m_pMtrl;

	int					m_iCollision;

	Vec3				m_vObjPos;			// 충돌체의 게임오브젝트의 위치
	Vec3				m_vOffsetPos;		// 게임오브젝트로 부터의 상대적인 위치
	Vec3				m_vOffsetScale;		// 게임오브젝트로 부터의 상대적인 크기

	Matrix				m_matColliderWorld;

	bool				m_bScale;			// 게임오브젝트의 크기에 영향을 받을지 않받을지

public:
	void SetOffsetPos(const Vec3& _vPos) { m_vOffsetPos = _vPos; }
	void SetOffsetScale(const Vec3& _vScale) { m_vOffsetScale = _vScale; }
	void SetOffset(const UINT _iID, float _fValue);

	void SetEnable(bool _bEnable) { m_bEnable = _bEnable; }
	bool GetEnable() const { return m_bEnable; }

	const Vec3& GetOffsetPos() { return m_vOffsetPos; }
	const Vec3& GetOffsetScale() { return m_vOffsetScale; }
	Vec3 GetWorldPos(){ return m_vObjPos + m_vOffsetPos; }
	const Matrix& GetWorldMat() { return m_matColliderWorld; }


public:
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	virtual bool Is2DCollider() = 0;
	virtual bool Is3DCollider() = 0;
public:
	virtual int finalupdate();

	void UpdateData();

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

	UINT GetColID() { return m_iColID; }

public:
	
public:
	CCollider();
	CCollider(const CCollider& _other);
	virtual ~CCollider();
};

