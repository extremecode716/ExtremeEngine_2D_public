#include "stdafx.h"
#include "MessageColleaque.h"
#include "DebugMgr.h"
#include "Script.h"
#include "..\ScriptMgr\View\MediatorMgr.h"

CMessageColleaque::CMessageColleaque(const wstring& _strName, CScript* _pScript)
{
	m_strName = _strName;
	m_pScript = _pScript;
}


CMessageColleaque::~CMessageColleaque()
{
}

void CMessageColleaque::Handle(const wstring& _strSrc, CMessage* _pData)
{
	SetEventFlag(true);

	//.....
#ifdef SAVELOAD_DEBUG
	if (NULL != _pData)
	{
		wstring strMessage = wstring(_strSrc + L" -> " + m_strName + L" : " + _pData->GetTypeName());
		CDebugMgr::GetInst()->Log(strMessage.c_str());
	}
#endif
	m_pScript->GetMessageData(_pData);

	SetEventFlag(false);
}

CColleaque * CMessageColleaque::Create(CMediatorMgr * _mediator, const wstring & _strName, CScript * _pScript)
{
	CColleaque* pCollq = _mediator->FindColleaque(_strName);
	if (pCollq != NULL)
	{
		pCollq->SetScript(_pScript);
		return pCollq;
	}

	pCollq = new CMessageColleaque(_strName, _pScript);
	pCollq->Join(_mediator);
	return pCollq;
}
