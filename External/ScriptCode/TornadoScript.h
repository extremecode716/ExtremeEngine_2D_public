#pragma once
#include "Script.h"
#include "PlayerScript.h"


class CMonsterScript;
class CTornadoScript :
	public CScript
{
private:
	CPlayerScript* m_pPlayerScript;
	Vec2	 m_vPos;
	Vec2	 m_vOffset;


	set<CMonsterScript*> m_setCollision;
	float	 m_fForce;
	bool	 m_bAttack;
	int		 m_iMinDamage;
	int		 m_iMaxDamage;
	float	 m_fTempTime;
	float	 m_fAttackTime;

	FMOD::Channel* m_pChannel;
	CSound*	 m_pSound;

private:
	float GetRotFromTarget(const Vec2& _vPos, const Vec3& _vRot);
	void AttackMonster(CMonsterScript* _pMonster);
	void CreateDamageEffect(CMonsterScript* _pMonster, int _iDamage);

public:
	void SetInfo(CPlayerScript* _pPlayer, float _fForce, int _iMinDamage, int _iMaxDamage , float _fAttackTime);

public:
	virtual void start() override;
	virtual int update() override;

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual CTornadoScript* Clone() override { return new CTornadoScript(*this); }

public:
	CTornadoScript();
	virtual ~CTornadoScript();
};

