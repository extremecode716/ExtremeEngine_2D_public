#include "stdafx.h"
#include "Scene_prontera.h"

#include "..\External\ScriptMgr\View\PoolingMgr.h"
#include "..\External\ScriptMgr\View\PortalTable.h"
#include "RespawnScript.h"


CScene_prontera::CScene_prontera()
	: m_pSound(NULL)
{
}


CScene_prontera::~CScene_prontera()
{
	if (NULL != m_pSound)
	{
		m_pChannel->stop();
	}
}

/*
�Լ���  : start()
�뵵    : prontera ����.
*/
void CScene_prontera::start()
{
	
	Vec3 vPos;
	Vec3 vSpawnPos;
	// ��Ż ����
	vPos = Vec3(150.f, 0.f, 0.f);
	vSpawnPos = Vec3(600.f, 100.f, 90.f);

	CPortalTable::GetThis()->CreatePortal(L"Portal_battleground1", vPos, vSpawnPos, L"��Ʋ�׶���1", L"��Ʋ�׶���1", L"Portal");

	SoundPlay();

}

void CScene_prontera::CreatPortals()
{
	
}

void CScene_prontera::SoundPlay()
{
	m_pSound = CResMgr::GetInst()->FindSound(L"Prontera");
	if (NULL != m_pSound)
	{
		m_pChannel = m_pSound->Play(-1, true);
		m_pChannel->setVolume(0.3f);
	}
}

