#pragma once
#include "DefineCode\BulletScript.h"

class CBasicBulletScript :
	public CBulletScript
{
private:
	float		m_fSpeed;
	Vec3		m_vMoveRot;
	Vec3		m_vMovePos;
	bool		m_bAlive;
	bool		m_bCollision;

	float		m_fTempTime;

private:
	CResPtr<CMaterial> m_pMtrl;

public:
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetGrayColor();

public:
	virtual void start();
	virtual int update();

private:
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

public:
	virtual CBasicBulletScript* Clone() { return new CBasicBulletScript(*this); }

public:
	CBasicBulletScript();
	virtual ~CBasicBulletScript();
};

