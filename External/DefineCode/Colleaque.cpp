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
�Լ��� : SendData
�뵵   : ��� ��󿡰� SendData
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
�Լ��� : SendData
�뵵   : ���ڿ��� ���Ե� ������ ã�Ƽ� SendData
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
�Լ��� : SendData
�뵵   : �ڱ��ڽ��� �����ϰ� SendData
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
�Լ��� : SendData
�뵵   : �� ��󿡰Ը� SendData
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
