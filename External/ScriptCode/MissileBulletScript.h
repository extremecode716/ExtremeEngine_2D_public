#pragma once
#include "DefineCode\BulletScript.h"

class CMissileBulletScript :
	public CBulletScript
{
private:
	float		m_fSpeed;
	Vec3		m_vMoveRot;
	Vec3		m_vMovePos;
	bool		m_isCollision;

	float		m_fTempTime;

private:
	CGameObject*	m_pTargetObj;
	bool			m_IsTarget;
	Vec3			m_vTargetPos;

private:
	float Lerp(const float _a, const float _b, float _t);
	float GetRotFromTarget(const Vec3& _vPos, const Vec3& _vRot);

public:
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetTargetPos(const Vec3& _vecPos) { m_IsTarget = true; m_vTargetPos = _vecPos; }
	void SetIsTarget(bool _isTarget) { m_IsTarget = _isTarget; }
	bool GetIsTarget() { return m_IsTarget; }

public:
	virtual void start();
	virtual int update();
	
public:
	virtual CMissileBulletScript* Clone() { return new CMissileBulletScript(*this); }

public:
	CMissileBulletScript();
	virtual ~CMissileBulletScript();
};

