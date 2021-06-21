#include "stdafx.h"
#include "ComsumptionItemScript.h"

CComsumptionItemScript::CComsumptionItemScript()
	: m_fMaxTime(0.f)
	, m_fTime(0.f)
	, m_bComsumption(false)
	, m_bEnd(false)
{
}


CComsumptionItemScript::~CComsumptionItemScript()
{
}


void CComsumptionItemScript::SetComsumptionInfo(UINT _index, const wstring & _strType, UINT _iType, const wstring & _strName, tStatus& _tStatus, float _fMaxTime, float _fTime)
{
	m_iIdx = _index;
	m_strType = _strType;
	m_iType = _iType;
	m_strName = _strName;
	m_tStatus = _tStatus;
	m_fMaxTime = _fMaxTime;
	m_fTime = _fTime;
}

void CComsumptionItemScript::start()
{
	CItemScript::start();
}

int CComsumptionItemScript::update()
{
	if (m_bComsumption == false || m_bEnd == false) return RET_SUCCESS;

	if (m_fTime <= m_fMaxTime)
	{
		m_fTime += DT();
	}
	else
	{
		m_bEnd = true;
		// 삭제 하기.
		//....
	}


	return RET_SUCCESS;
}

void CComsumptionItemScript::OnCollisionEnter(CCollider * _pOther)
{
}

void CComsumptionItemScript::OnCollisionExit(CCollider * _pOther)
{
}
