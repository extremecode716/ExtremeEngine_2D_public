#pragma once
#include "DefineCode\ItemScript.h"

class CRevolveItemScript :
	public CItemScript
{
private:
	float		m_fSpeed;
	Vec3		m_vMoveRot;
	Vec3		m_vMovePos;
	bool		m_bAlive;
	bool		m_bCollision;

	Vec3		m_vStartPos;
	Vec3		m_vStartRot;
	float		m_fTempTime;
	float		m_fDeleteTime;

private:
	CGameObject*	m_pTargetObj;
	bool			m_IsTarget;
	bool			m_bRevolve;
	Vec3			m_vTargetPos;
	float			m_fDistanceRevolve;
	float			m_fDistanceFromTarget;
	float			m_fCollisionDistanceFromTarget;
	float			m_fCollisionDistanceFromBullet;

private:
	float Lerp(const float _a, const float _b, float _t);
	//float Sqrt(float _x);
	float Pow(float _valueX, int _valueY);
	float GetRotFromTarget(const Vec3& _vPos, const Vec3& _vRot);
	float GetDistanceFromTarget(const Vec3& _vPos);
	float GetDistance(Vec3& _vPos, Vec3& _vTarget);

	void SetStartRot(const Vec3& _vecRot) { m_vStartRot = _vecRot; }
	void SetDeleteTime(float _fDeleteTime) { m_fDeleteTime = _fDeleteTime; }
public:
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetTargetPos(const Vec3& _vecPos) { m_IsTarget = true; m_vTargetPos = _vecPos; }
	void SetIsTarget(bool _isTarget) { m_IsTarget = _isTarget; }
	bool GetIsTarget() { return m_IsTarget; }
	bool IsRevolve() { return m_bRevolve; }
	void SetStartPos(const Vec3& _vecPos) { m_vStartPos = _vecPos; }

public:
	virtual void start() override;
	virtual int update() override;

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual CRevolveItemScript* Clone() override { return new CRevolveItemScript(*this); }

public:
	CRevolveItemScript();
	virtual ~CRevolveItemScript();
};

