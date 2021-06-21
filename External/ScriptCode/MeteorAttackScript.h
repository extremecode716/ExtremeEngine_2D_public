#pragma once
#include "Script.h"

class CPlayerScript;
class CMonsterScript;
class CMeteorAttackScript :
	public CScript
{
private:
	CPlayerScript* m_pPlayerScript;
	bool bExplosion;
	Vec3 m_vPos;
	Vec3 m_vTargetPos;
	float m_fSpeed;

	bool m_bOnceRot;
	float m_fTagetRot;

	bool m_bOnceTime;
	float m_fExplosionTime;
	float m_fTempTime;

	bool m_bAttack;

	int m_iMinDamage;
	int m_iMaxDamage;

	set<CMonsterScript*> m_setCollision;
	float m_fCollisionTempTime;
	float m_fCollisionTime;

private:
	void SetPlayerScript(CPlayerScript* _pPlayer) { m_pPlayerScript = _pPlayer; }
	void SetTargetPos(const Vec3& _vPos);
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetDamage(int _min, int _max) { m_iMinDamage = _min; m_iMaxDamage = _max; }

private:
	float GetRotFromTarget();
	float GetDistance();
	void Attack(CMonsterScript* _pMonsterScript);
	void CreateDamageEffect(CMonsterScript* _pMonsterScript, int _iDamage);

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual void start() override;
	virtual int update() override;

public:
	virtual CMeteorAttackScript* Clone() override { return new CMeteorAttackScript(*this); }

public:
	CMeteorAttackScript();
	virtual ~CMeteorAttackScript();

	friend class CMeteorScript;
};

