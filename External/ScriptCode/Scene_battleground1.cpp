#include "stdafx.h"
#include "Scene_battleground1.h"

#include "..\External\ScriptMgr\View\PoolingMgr.h"
#include "..\External\ScriptMgr\View\PortalTable.h"
#include "RespawnScript.h"

#include "CollisionMgr.h"

CScene_battleground1::CScene_battleground1()
	: m_pSound(NULL)
{
}


CScene_battleground1::~CScene_battleground1()
{
	if (NULL != m_pSound)
	{
		m_pChannel->stop();
	}
}

/*
�Լ���  : start()
�뵵    : battleground1 ����.
*/
void CScene_battleground1::start()
{
	/////////////////
	// pooling ����
	////////////////
	CPoolingMgr* pPoolingMgr = CPoolingMgr::GetInst(L"PoolingMgr");
	pPoolingMgr->InsertPooling(L"Poring", 15);
	pPoolingMgr->InsertPooling(L"GoldPoring", 10);
	pPoolingMgr->InsertPooling(L"Deviling", 10);

	vector<CGameObject*>* pVecGameObj = NULL;
	////////////////
	// Reswpawn ����
	////////////////
	pVecGameObj = pPoolingMgr->FindVecGameObj(L"Poring");
	if (pVecGameObj != NULL)
	{
		UINT iVecSize = pVecGameObj->size();
		CRespawnScript* pRespawnScript = new CRespawnScript;
		pRespawnScript->SetRespawnDelayTime(1.5f);
		pRespawnScript->Create(L"RespawnMgr_Poring");
		for (UINT i = 0; i < iVecSize; ++i)
		{
			pRespawnScript->push_backRepawnObj(pVecGameObj->operator[](i));
		}
	}

	pVecGameObj = pPoolingMgr->FindVecGameObj(L"GoldPoring");
	if (pVecGameObj != NULL)
	{
		UINT iVecSize = pVecGameObj->size();
		CRespawnScript* pRespawnScript = new CRespawnScript;
		pRespawnScript->Create(L"RespawnMgr_GoldPoring");
		for (UINT i = 0; i < iVecSize; ++i)
		{
			pRespawnScript->push_backRepawnObj(pVecGameObj->operator[](i));
		}
	}

	pVecGameObj = pPoolingMgr->FindVecGameObj(L"Deviling");
	if (pVecGameObj != NULL)
	{
		UINT iVecSize = pVecGameObj->size();
		CRespawnScript* pRespawnScript = new CRespawnScript;
		pRespawnScript->Create(L"RespawnMgr_Deviling");
		for (UINT i = 0; i < iVecSize; ++i)
		{
			pRespawnScript->push_backRepawnObj(pVecGameObj->operator[](i));
		}
	}

	Vec3 vPos;
	Vec3 vSpawnPos;
	// ��Ż ����
	vPos = Vec3(150.f, 0.f, 0.f);
	vSpawnPos = Vec3(600.f, 100.f, 90.f);
	CPortalTable::GetThis()->CreatePortal(L"Portal_prontera", vPos, vSpawnPos, L"�����׶�", L"�����׶�", L"Portal");

	// ��Ż ����
	vPos = Vec3(450.f, -150.f, 0.f);
	vSpawnPos = Vec3(600.f, 100.f, 90.f);
	CPortalTable::GetThis()->CreatePortal(L"Portal_battleground2", vPos, vSpawnPos, L"��Ʋ�׶���2", L"��Ʋ�׶���2" ,L"Portal");

	SoundPlay();
}

void CScene_battleground1::CreatPortals()
{
}

void CScene_battleground1::SoundPlay()
{
	m_pSound = CResMgr::GetInst()->FindSound(L"Battle1");
	if (NULL != m_pSound)
	{
		m_pChannel = m_pSound->Play(-1, true);
		m_pChannel->setVolume(0.3f);
	}
}
