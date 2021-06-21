#pragma once
#include "Script.h"

class CPlayerScript;
class CMonsterScript;
class CMeteorScript :
	public CScript
{
private:
	CPlayerScript* m_pPlayerScript;
	Vec3	 m_vOffset;

	set<CMonsterScript*> m_setCollision;
	list<CMonsterScript*> m_listMeteorObj;
	bool	 m_bAttack;
	int		 m_iMinDamage;
	int		 m_iMaxDamage;
	float	 m_fTempTime;
	float	 m_fAttackTime;

	CSound*	 m_pSound;

private:
	void CreateMeteor(CMonsterScript* _pMonScript);

public:
	void SetPlayerScript(CPlayerScript* _pPlayer) { m_pPlayerScript = _pPlayer; }
	void SetMeteorOffset(const Vec3& _vOffset) { m_vOffset = _vOffset; }
	void SetDamage(int _min, int _max) { m_iMinDamage = _min; m_iMaxDamage = _max; }
	void SetAttackTime(float _fAttackTime) { m_fAttackTime = _fAttackTime; }

public:
	virtual void start() override;
	virtual int update() override;

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual CMeteorScript* Clone() override { return new CMeteorScript(*this); }

public:
	CMeteorScript();
	virtual ~CMeteorScript();

	friend class CMeteorAttackScript;
};

