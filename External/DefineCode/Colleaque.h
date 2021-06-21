#pragma once
#include "Message.h"

class CMediatorMgr;
class CScript;
class CColleaque
{
private:
	CMediatorMgr*	m_pMediator;

protected:
	wstring     m_strName;
	CScript*	m_pScript;
	bool		m_bEventFlag;

protected:
	void SetEventFlag(bool _bEvent);

public:
	void SetName(const wstring& _strName);
	void SetScript(CScript* _pScript) { m_pScript = _pScript; }
	const wstring& GetName() const { return m_strName; }
	bool GetEvnetFlag() const { return m_bEventFlag; }

public:
	bool Join(CMediatorMgr* _mediator);
	void SendData_All(CMessage* _pData);
	void SendData_Find(const wstring& _strDest, CMessage* _pData);
	void SendData_ExceptMe(CMessage* _pData);
	void SendData(const wstring& _strDest, CMessage* _pData);
	virtual void Handle(const wstring& _strSrc, CMessage* _pData) = 0;

public:
   	CColleaque();
	virtual ~CColleaque();
};

