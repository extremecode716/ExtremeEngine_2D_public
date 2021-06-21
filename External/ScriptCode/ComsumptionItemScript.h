#pragma once
#include "DefineCode\ItemScript.h"

class CComsumptionItemScript :
	public CItemScript
{
private:
	tStatus m_tStatus;

	float  m_fMaxTime;
	float  m_fTime;

	bool m_bComsumption;
	bool m_bEnd;

public:
	void SetComsumptionInfo(UINT _index, const wstring& _strType, UINT _iType, const wstring& _strName, tStatus& _tStatus, float _fMaxTime, float _fTime);
	const wstring& GetName() const { return m_strName; }

	void Comsumption() { m_bComsumption = true; }

public:
	virtual void start() override;
	virtual int update() override;

private:
	virtual void OnCollisionEnter(CCollider* _pOther) override;
	virtual void OnCollisionExit(CCollider* _pOther) override;

public:
	virtual CComsumptionItemScript* Clone() override { return new CComsumptionItemScript(*this); }

public:
	CComsumptionItemScript();
	virtual ~CComsumptionItemScript();
};

