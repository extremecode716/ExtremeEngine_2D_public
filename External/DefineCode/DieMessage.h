#pragma once
#include "Message.h"

class CGameObject;
class CDieMessage :
	public CMessage
{
private:
	wstring m_strDieKey;
	CGameObject* m_pDieObj;

public:
	const wstring& GetDieKey() const { return m_strDieKey; }
	CGameObject* GetDieObj() const { return m_pDieObj; }

public:
	CDieMessage(const wstring& _strDieKey, CGameObject* _pDieObj);
	virtual ~CDieMessage();
};

