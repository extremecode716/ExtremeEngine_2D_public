#pragma once
#include "DefineCode\ItemScript.h"


class CAccessoriesScript :
	public CItemScript
{
private:
	tAccInfo m_tAccInfo;

public:
	const wstring& GetName() const { return m_tAccInfo.strName; }
	int GetDamage() const { return m_tAccInfo.iDamage; }
	int GetDefense() const { return m_tAccInfo.iDefense; }

public:
	void SetAccInfo(UINT _index, const wstring& _strType, UINT _iType, const wstring& _strName, int _iDamage, int _iDefense);

public:
	virtual void start() override;
	virtual int update() override;

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual CAccessoriesScript* Clone() override { return new CAccessoriesScript(*this); }

public:
	CAccessoriesScript();
	virtual ~CAccessoriesScript();
};

