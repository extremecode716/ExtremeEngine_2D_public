#include "stdafx.h"
#include "Scene_battleground3.h"

#include "..\External\ScriptMgr\View\PoolingMgr.h"
#include "..\External\ScriptMgr\View\PortalTable.h"
#include "RespawnScript.h"

CScene_battleground3::CScene_battleground3()
	: m_pSound(NULL)
{
}


CScene_battleground3::~CScene_battleground3()
{
	if (NULL != m_pSound)
	{
		m_pChannel->stop();
	}
}

void CScene_battleground3::start()
{

	/////////////////
	// pooling 셋팅
	////////////////
	CPoolingMgr* pPoolingMgr = CPoolingMgr::GetInst(L"PoolingMgr");

	map<wstring, CResPtr<CPrefab>>& m_ma1 =  CResMgr::GetInst()->GetPrefabMap();
	pPoolingMgr->InsertPooling(L"Baphomet", 6);
	pPoolingMgr->InsertPooling(L"WraithDead", 13);

	vector<CGameObject*>* pVecGameObj = NULL;
	////////////////
	// Reswpawn 셋팅
	////////////////

	pVecGameObj = pPoolingMgr->FindVecGameObj(L"Baphomet");
	if (pVecGameObj != NULL)
	{
		UINT iVecSize = pVecGameObj->size();
		CRespawnScript* pRespawnScript = new CRespawnScript;
		pRespawnScript->SetRespawnDelayTime(2.f);
		pRespawnScript->Create(L"RespawnMgr_Baphomet");
		for (UINT i = 0; i < iVecSize; ++i)
		{
			pRespawnScript->push_backRepawnObj(pVecGameObj->operator[](i));
		}
	}

	pVecGameObj = pPoolingMgr->FindVecGameObj(L"WraithDead");
	if (pVecGameObj != NULL)
	{
		UINT iVecSize = pVecGameObj->size();
		CRespawnScript* pRespawnScript = new CRespawnScript;
		pRespawnScript->SetRespawnDelayTime(3.f);
		pRespawnScript->Create(L"RespawnMgr_WraithDead");
		for (UINT i = 0; i < iVecSize; ++i)
		{
			pRespawnScript->push_backRepawnObj(pVecGameObj->operator[](i));
		}
	}

	Vec3 vPos;
	Vec3 vSpawnPos;
	// 포탈 생성
	vPos = Vec3(150.f, 0.f, 0.f);
	vSpawnPos = Vec3(600.f, 100.f, 90.f);

	CPortalTable::GetThis()->CreatePortal(L"Portal_battleground2", vPos, vSpawnPos, L"배틀그라운드2", L"배틀그라운드2", L"Portal");
	
	PlaySound();
}

void CScene_battleground3::CreatPortals()
{
}

void CScene_battleground3::PlaySound()
{
	m_pSound = CResMgr::GetInst()->FindSound(L"BossRoom");
	if (NULL != m_pSound)
	{
		m_pChannel = m_pSound->Play(-1, true);
		m_pChannel->setVolume(0.3f);

	}
}
