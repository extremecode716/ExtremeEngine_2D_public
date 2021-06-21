#pragma once
#include "DefineCode\BulletScript.h"

class CParabolaBulletScript :
	public CBulletScript
{
private:
	float		m_fSpeed;
	Vec3		m_vMoveRot;
	Vec3		m_vMovePos;
	bool		m_isCollision;

	float		m_fTempTime;

private:
	float		m_fGravity;
	float Pow(float _valueX, int _valueY);

public:
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

public:
	virtual void start();
	virtual int update();

public:
	virtual CParabolaBulletScript* Clone() { return new CParabolaBulletScript(*this); }

public:
	CParabolaBulletScript();
	virtual ~CParabolaBulletScript();
};

