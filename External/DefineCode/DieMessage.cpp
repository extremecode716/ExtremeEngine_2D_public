#include "stdafx.h"
#include "DieMessage.h"
#include "GameObject.h"

CDieMessage::CDieMessage(const wstring & _strDieKey, CGameObject * _pDieObj)
	: m_strDieKey(_strDieKey)
	, m_pDieObj(_pDieObj)
{
	SetType(MessageType::DIE_MT);
}

CDieMessage::~CDieMessage()
{
}
