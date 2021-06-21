#include "stdafx.h"
#include "TeleportSkill.h"
#include "..\\External\ScriptMgr\View\TileMgrScript.h"
#include "RandomScript.h"

// 서브 셋팅을 위해서
#include "..\ScriptCode\PlayerScript.h"
#include "..\External\ScriptCode\UIMgr.h"

CTeleportSkill::CTeleportSkill()
{
}


CTeleportSkill::~CTeleportSkill()
{
}

/*
함수명  : Action(CScript* _pScript)
용도    : 텔레포트 스킬 사용한다.
*/
bool CTeleportSkill::Action(CScript* _pScript)
{
	CTileMgrScript* pTileMgr = CTileMgrScript::GetThis();
	if (NULL == pTileMgr) return false;

	set<ULONG64>& setBasic = pTileMgr->GetsetBasic();
	int isetBasicSize = setBasic.size();
	if (isetBasicSize > 0)
	{
		set<ULONG64>::iterator iter = setBasic.begin();
		int iRandNum = GameRandom::RandomInt(0, isetBasicSize - 1);
		std::advance(iter, iRandNum);
		UINT iIndexX = HIDWORD(*iter);
		UINT iIndexY = LODWORD(*iter);
		Vec2 vTelPos = pTileMgr->GetPosFromIndex(iIndexX, iIndexY);
		_pScript->GetGameObject()->Transform()->SetLocal2DPos(vTelPos);

		// 서브셋팅
		ServeSetting(_pScript);
		SoundEffectPlay();
		
		return true;
	}

	return false;
}

// 이동 일체 중지.
void CTeleportSkill::ServeSetting(CScript * _pScript)
{
	CPlayerScript* pPlayerScript = dynamic_cast<CPlayerScript*>(_pScript);
	if (NULL == pPlayerScript) return;

	pPlayerScript->Reset();
	CUIMgr* pUIMgr = pPlayerScript->GetUIMgr();
	if (pUIMgr != NULL)
	{
		pUIMgr->Transform()->SetLocal2DPos(pPlayerScript->Transform()->GetLocal2DPos());
	}

	CPrefab* pEffectPrefab = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Effect_Teleport(Prefab)");

	if (NULL != pEffectPrefab)
	{
		CGameObject* pCloneObj = pEffectPrefab->Instantiate();

		CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
		CLayer* pLayer = pCurScene->FindLayer(L"Default");
		if (NULL == pLayer)
		{
			SAFE_DELETE(pCloneObj);
		}
		else
		{
			pLayer->AddGameObject(pCloneObj, true, true);
			pPlayerScript->GetGameObject()->AddChildObj(pCloneObj);
			pCloneObj->start();
		}
	}

}

void CTeleportSkill::SoundEffectPlay()
{
	CSound* pSound = CResMgr::GetInst()->FindSound(L"ef_teleportation");
	if (NULL != pSound)
	{
		pSound->Play(1);
	}

}
