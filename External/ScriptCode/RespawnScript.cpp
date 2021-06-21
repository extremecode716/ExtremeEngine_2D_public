#include "stdafx.h"
#include "RespawnScript.h"

#include "RandomScript.h"
#include "..\External\ScriptMgr\View\TileMgrScript.h"
#include "..\DefineCode\MonsterScript.h"
#include "..\DefineCode\DieMessage.h"

CRespawnScript::CRespawnScript()
	: m_pMediator(NULL)
	, m_pCollq_Respawn(NULL)
	, m_eState(RESPAWN_STATE::STATE_NONE)
	, m_isActive(true)
	, m_fTempTime(0.f)
	, m_fRespawnDelayTime(5.f)
	, m_iCount(0)
	, m_iMaxCount(0)
	, m_pTransform(NULL)
	, m_pRecentlyObj(NULL)
{
}

CRespawnScript::~CRespawnScript()
{
}

/*
함수명  : push_backRepawnObj(CGameObject * _pObj)
용도    : 리스폰될 오브젝트들을 넣어준다. 해당 오브젝트의 Respawn Collq를 등록해준다.
*/
void CRespawnScript::push_backRepawnObj(CGameObject * _pObj)
{
	if (NULL == _pObj) return;

	m_listRepawnObj.push_back(_pObj);

	CMonsterScript* pMonsterScript = _pObj->Script<CMonsterScript>();
	if (NULL != pMonsterScript)
	{
		pMonsterScript->SetRespawnCollqName(m_strRespawnCollq);
	}
}

CGameObject * CRespawnScript::Create(const wstring& _strTag)
{
	SetCollqName(_strTag);
	m_pMediator = CMediatorMgr::GetInst();
	m_pCollq_Respawn = CMessageColleaque::Create(m_pMediator, m_strRespawnCollq, this);

	CGameObject* pRepawnObj = new CGameObject;
	pRepawnObj->SetTag(_strTag);
	pRepawnObj->AddComponent<CTransform>(new CTransform);
	pRepawnObj->AddComponent<CScript>(this);

	CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->AddGameObject(pRepawnObj);
	pRepawnObj->start();

	return pRepawnObj;
}

void CRespawnScript::GetMessageData(CMessage * _pData)
{
	if (NULL == _pData) return;
	MessageType eType = _pData->GetType();

	switch (eType)
	{
	case MessageType::NONE_MT:
		break;
	case MessageType::ATTACK_MT:
	{
	}
	break;
	case MessageType::FIND_MT:
	{
	}
	break;
	case MessageType::PATHFIND_MT:
	{
	}
	break;
	case MessageType::DIE_MT:
	{
		CDieMessage* pDieMt = static_cast<CDieMessage*>(_pData);

		m_listRepawnObj.push_back(pDieMt->GetDieObj());
		--m_iCount;

		SAFE_DELETE(pDieMt);
	}
	break;
	case MessageType::ERROR_MT:
		SAFE_DELETE(_pData);
		break;
	default:
		SAFE_DELETE(_pData);
		break;
	}
}

void CRespawnScript::start()
{
	///////////////////
	// Respawn Setting
	///////////////////
	m_eState = RESPAWN_STATE::STATE_START;
	m_pTransform = Transform();
	m_fRespawnDelayTime = 3.f;

	m_fTempTime = 0.f;
	m_isActive = false;
	m_iMaxCount = 10;
}

int CRespawnScript::update()
{
	if (true == m_listRepawnObj.empty()) return RET_SUCCESS;

	if (m_iCount < m_iMaxCount)
	{
		float fDT = DT();
		m_eState = RESPAWN_STATE::STATE_IDLE;
		if (RESPAWN_STATE::STATE_IDLE == m_eState && !m_isActive)
		{
			m_fTempTime += fDT;
		}

		if (m_isActive)
		{
			m_eState = RESPAWN_STATE::STATE_RESPAWN;
			m_pTileMgr = CTileMgrScript::GetThis();
			if (NULL == m_pTileMgr) return false;

			set<ULONG64>& setBasic = m_pTileMgr->GetsetBasic();
			int isetBasicSize = setBasic.size();
			if (isetBasicSize <= 0) return false;
			
			set<ULONG64>::iterator iter = setBasic.begin();
			int iRandNum = GameRandom::RandomInt(0, isetBasicSize - 1);
			std::advance(iter, iRandNum);
			UINT iIndexX = HIDWORD(*iter);
			UINT iIndexY = LODWORD(*iter);
			Vec2 vTelPos = m_pTileMgr->GetPosFromIndex(iIndexX, iIndexY);

			CGameObject* pClone = m_listRepawnObj.front();
			m_listRepawnObj.pop_front();
			pClone->SetActive(true);
			pClone->Transform()->SetLocal2DPos(vTelPos);
			m_pRecentlyObj = pClone;
			m_isActive = false;

			++m_iCount;
		}

		if (m_fTempTime >= m_fRespawnDelayTime)
		{
			m_isActive = true;
			m_fTempTime = 0.f;
		}

	}
	return RET_SUCCESS;
}
