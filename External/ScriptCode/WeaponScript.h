#pragma once
#include "DefineCode\ItemScript.h"
class CWeaponScript :
	public CItemScript
{
private:
	tWeaponInfo m_tWeapon;

public:
	void SetWeaponInfo(UINT _index, const wstring& _strType, UINT _iType, const wstring& _strName, float _fRange, int _iDamage, float _fSpeed);

	const wstring& GetName() const { return m_tWeapon.strName; }
	float GetRange() const { return m_tWeapon.fRange; }
	int GetDamage() const { return m_tWeapon.iDamage; }
	float GetSpd() const { return m_tWeapon.fSpeed; }

public:
	virtual void start() override;
	virtual int update() override;

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual CWeaponScript* Clone() { return new CWeaponScript(*this); }

public:
	CWeaponScript();
	virtual ~CWeaponScript();
};

