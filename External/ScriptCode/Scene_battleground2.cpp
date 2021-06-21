#include "stdafx.h"
#include "Scene_battleground2.h"

#include "..\External\ScriptMgr\View\PoolingMgr.h"
#include "..\External\ScriptMgr\View\PortalTable.h"
#include "RespawnScript.h"

CScene_battleground2::CScene_battleground2()
	: m_pSound(NULL)
{
}


CScene_battleground2::~CScene_battleground2()
{
	if (NULL != m_pSound)
	{
		m_pChannel->stop();
	}
}

void CScene_battleground2::start()
{
	/////////////////
	// pooling 셋팅
	////////////////
	CPoolingMgr* pPoolingMgr = CPoolingMgr::GetInst(L"PoolingMgr");
	pPoolingMgr->InsertPooling(L"Wolf", 8);
	pPoolingMgr->InsertPooling(L"BaphometJR", 9);
	pPoolingMgr->InsertPooling(L"Creamy", 12);

	vector<CGameObject*>* pVecGameObj = NULL;
	////////////////
	// Reswpawn 셋팅
	////////////////

	pVecGameObj = pPoolingMgr->FindVecGameObj(L"Wolf");
	if (pVecGameObj != NULL)
	{
		UINT iVecSize = pVecGameObj->size();
		CRespawnScript* pRespawnScript = new CRespawnScript;
		pRespawnScript->Create(L"RespawnMgr_Wolf");
		for (UINT i = 0; i < iVecSize; ++i)
		{
			pRespawnScript->push_backRepawnObj(pVecGameObj->operator[](i));
		}
	}

	pVecGameObj = pPoolingMgr->FindVecGameObj(L"BaphometJR");
	if (pVecGameObj != NULL)
	{
		UINT iVecSize = pVecGameObj->size();
		CRespawnScript* pRespawnScript = new CRespawnScript;
		pRespawnScript->Create(L"RespawnMgr_BaphometJR");
		for (UINT i = 0; i < iVecSize; ++i)
		{
			pRespawnScript->push_backRepawnObj(pVecGameObj->operator[](i));
		}
	}

	pVecGameObj = pPoolingMgr->FindVecGameObj(L"Creamy");
	if (pVecGameObj != NULL)
	{
		UINT iVecSize = pVecGameObj->size();
		CRespawnScript* pRespawnScript = new CRespawnScript;
		pRespawnScript->SetRespawnDelayTime(1.5f);
		pRespawnScript->Create(L"RespawnMgr_Creamy");
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

	CPortalTable::GetThis()->CreatePortal(L"Portal_battleground1", vPos, vSpawnPos, L"배틀그라운드1", L"배틀그라운드1", L"Portal");

	vPos = Vec3(450.f, -150.f, 0.f);
	vSpawnPos = Vec3(600.f, 100.f, 90.f);

	CPortalTable::GetThis()->CreatePortal(L"Portal_battleground3", vPos, vSpawnPos, L"배틀그라운드3", L"배틀그라운드3", L"Portal");

	PlaySound();
}

void CScene_battleground2::CreatPortals()
{
}

void CScene_battleground2::PlaySound()
{
	m_pSound = CResMgr::GetInst()->FindSound(L"Desert");
	if (NULL != m_pSound)
	{
		m_pChannel = m_pSound->Play(-1, true);
		m_pChannel->setVolume(0.3f);
	}
}
