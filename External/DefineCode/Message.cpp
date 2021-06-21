#include "stdafx.h"
#include "Message.h"


CMessage::CMessage()
	: m_eType(MessageType::NONE_MT)
	, m_strType(L"NONE_MT")
{
}


CMessage::~CMessage()
{
}


void CMessage::SetType(MessageType _eType)
{
	m_eType = _eType;

	switch (m_eType)
	{
	case MessageType::NONE_MT:
		m_strType = L"NONE_MT";
		break;
	case MessageType::ATTACK_MT:
		m_strType = L"ATTACK_MT";
		break;
	case MessageType::FIND_MT:
		m_strType = L"FIND_MT";
		break;
	case MessageType::PATHFIND_MT:
		m_strType = L"PATHFIND_MT";
		break;
	case MessageType::DIE_MT:
		m_strType = L"DIE_MT";
		break;
	case MessageType::ERROR_MT:
		m_strType = L"ERROR_MT";
		break;
	default:
		m_strType = L"ERROR_MT";
		break;
	}
}