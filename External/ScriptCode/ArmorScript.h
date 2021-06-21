#pragma once
#include "DefineCode\ItemScript.h"

class CArmorScript :
	public CItemScript
{
private:
	tArmorInfo    m_tArmor;

public:
	void SetArmorInfo(UINT _index, const wstring& _strType, UINT _iType, const wstring& _strName, int _iDefense);

	const wstring& GetName() const { return m_tArmor.strName; }
	int GetDefense() const { return m_tArmor.iDefense; }

public:
	virtual void start() override;
	virtual int update() override;

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual CArmorScript* Clone() override { return new CArmorScript(*this); }

public:
	CArmorScript();
	virtual ~CArmorScript();
};

