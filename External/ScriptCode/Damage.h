#pragma once
#include "Script.h"
class CDamage :
	public CScript
{
private:
	int         m_iDamage;
	int         m_iDamageCount;
	CTexture*	m_pTex;
	CMaterial*	m_pCloneMtrl;

	float		m_fXSize;
	float		m_fYSize;

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

private:
	void CalDamageCount();

public:
	void SetDamage(int _idamage);

public:
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetStartRot(const Vec3& _vRot) { m_vStartRot = _vRot; }
	void ReduceScale();
	void SetColor(Vec4 _vColor);

public:
	virtual void start() override;
	virtual int update() override;

public:
	virtual CDamage* Clone() override { return new CDamage(*this); }

public:
	CDamage();
	virtual ~CDamage();
};

