#pragma once
#include "Component.h"

class CTransform :
	public CComponent
{
private:
	Vec3		m_vPos;
	Vec3		m_vScale;
	Vec3		m_vRot;

	Matrix		m_matWorld;

public:
	virtual int update();
	virtual int lateupdate();
	virtual int finalupdate();

private:
	void UpdateData();

public:
	Vec3 GetLocalPos() { return m_vPos; }
	Vec2 GetLocal2DPos() const { return Vec2(m_vPos.x, m_vPos.y); }
	void SetLocalPos(const Vec3& _vPos) { m_vPos = _vPos; }
	void SetLocal2DPos(const Vec2& _vPos) { m_vPos = Vec3(_vPos.x, _vPos.y, m_vPos.z); }
	Vec3 GetWorldPos();
	Vec2 GetWorld2DPos();

	Vec3 GetLocalScale() { return m_vScale; }
	Vec2 GetLocal2DScale() { return Vec2(m_vScale.x, m_vScale.y); }
	void SetLocalScale(const Vec3& _vScale) { m_vScale = _vScale; }
	void SetLocal2DScale(const Vec2& _vScale) { m_vScale = Vec3(_vScale.x, _vScale.y, m_vScale.z); }
	Vec3 GetWorldScale();

	Vec3 GetLocalRot() { return m_vRot; }
	void SetLocalRot(const Vec3& _vRot) { m_vRot = _vRot; }

	void SetTransform(const UINT _iID, float _fValue);


	const Matrix& GetWorldMat() { return m_matWorld; }

public:
	virtual CTransform* Clone() { return new CTransform(*this); }
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

public:
	CTransform();
	virtual ~CTransform();

	friend class CMeshRender;
};

