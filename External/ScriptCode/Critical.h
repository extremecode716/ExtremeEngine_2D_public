#pragma once
#include "Script.h"

class CCritical :
	public CScript
{
private:
	float		m_fSpeed;
	Vec3        m_vStartPos;
	Vec3		m_vStartRot;
	Vec3		m_vMovePos;

	float		m_fTempTime;
	float		m_fDeleteTime;

	float		m_fReduceScale;
	Vec3		m_vReduceMinScale;

private:
	float		m_fGravity;

	CMaterial*   m_pMtrl;
public:
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetStartRot(const Vec3& _vRot) { m_vStartRot = _vRot; }
	void ReduceScale();

public:
	virtual void start() override;
	virtual int update() override;

public:
	virtual CCritical* Clone() override { return new CCritical(*this); }
public:
	CCritical();
	virtual ~CCritical();
};

