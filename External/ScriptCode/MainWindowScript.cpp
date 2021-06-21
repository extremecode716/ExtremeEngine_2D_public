#include "stdafx.h"
#include "MainWindowScript.h"

#include "..\External\ScriptMgr\View\SceneTable.h"

CMainWindowScript::CMainWindowScript()
	: m_pSound(NULL)
{

}


CMainWindowScript::~CMainWindowScript()
{
	if (NULL != m_pSound)
	{
		m_pChannel->stop();
	}
}

void CMainWindowScript::SoundPlay()
{
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"Title", L"Sound\\BGM\\Title.mp3");

	m_pSound = CResMgr::GetInst()->FindSound(L"Title");
	if (NULL != m_pSound)
	{
		m_pChannel = m_pSound->Play();
		m_pChannel->setVolume(0.3f);
	}
}

void CMainWindowScript::awake()
{
	CSceneTable* pSceneTable = CSceneTable::GetInst(L"SceneTable", L"Default");
	pSceneTable->InitSceneTable();

	strNextScene = L"Ragnarok_00_39";

	SoundPlay();
}

int CMainWindowScript::update()
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_ENTER, KEY_STATE::STATE_TAB))
	{
		CSceneTable::GetInst()->ChangeScene(strNextScene);
	}

	return RET_SUCCESS;
}
