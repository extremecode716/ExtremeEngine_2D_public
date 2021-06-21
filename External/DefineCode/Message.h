#pragma once
#include "defineScript.h"

class CMessage
{
protected:
	MessageType  m_eType;
	wstring      m_strType;

protected:
	void SetType(MessageType _eType);

public:
	MessageType GetType() { return m_eType; }
	const wstring& GetTypeName() { return m_strType; }


public:
	CMessage();
	virtual ~CMessage();
};