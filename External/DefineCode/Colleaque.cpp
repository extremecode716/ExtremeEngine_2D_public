#include "stdafx.h"
#include "Colleaque.h"
#include "..\ScriptMgr\View\MediatorMgr.h"

CColleaque::CColleaque()
	: m_pMediator(NULL)
	, m_strName(L"")
	, m_bEventFlag(false)
{
}


CColleaque::~CColleaque()
{
}

void CColleaque::SetName(const wstring& _strName)
{
	m_strName = _strName;
}

void CColleaque::SetEventFlag(bool _bEvent)
{
	m_bEventFlag = _bEvent;
}

bool CColleaque::Join(CMediatorMgr * _mediator)
{
	if (NULL == _mediator) return false;
	m_pMediator = _mediator;
	bool bAdd = _mediator->AddColleaque(this);

	return bAdd;
}

/*
함수명 : SendData
용도   : 모든 대상에게 SendData
*/
void CColleaque::SendData_All(CMessage* _pData)
{
	if (NULL == m_pMediator)
	{
		SAFE_DELETE(_pData);
		return;
	}

	m_pMediator->Mediate(m_strName, _pData);
}

/*
함수명 : SendData
용도   : 문자열이 포함된 대상들을 찾아서 SendData
*/
void CColleaque::SendData_Find(const wstring & _strDest, CMessage* _pData)
{
	if (NULL == m_pMediator || L"" == _strDest)
	{
		SAFE_DELETE(_pData);
		return;
	}

	m_pMediator->Mediate_Find(m_strName, _strDest,  _pData);
}

/*
함수명 : SendData
용도   : 자기자신을 제외하고 SendData
*/
void CColleaque::SendData_ExceptMe(CMessage* _pData)
{
	if (NULL == m_pMediator)
	{
		SAFE_DELETE(_pData);
		return;
	}

	m_pMediator->Mediate_ExceptMe(m_strName, _pData);
}

/*
함수명 : SendData
용도   : 한 대상에게만 SendData
*/
void CColleaque::SendData(const wstring& _strDest, CMessage* _pData)
{
	if (NULL == m_pMediator || L"" == _strDest)
	{
		SAFE_DELETE(_pData);
		return;
	}

	m_pMediator->Mediate(m_strName, _strDest,  _pData);
}
