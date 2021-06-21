#pragma once
#include "DefineCode\ItemScript.h"
class CETCItemScript :
	public CItemScript
{
private:


public:
	void SetETCInfo(UINT _index, const wstring& _strType, UINT _iType, const wstring& _strName);
	const wstring& GetName() const { return m_strName; }

public:
	virtual void start() override;
	virtual int update() override;

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual CETCItemScript* Clone() override { return new CETCItemScript(*this); }

public:
	CETCItemScript();
	virtual ~CETCItemScript();
};

