#include "stdafx.h"
#include "MgrScript.h"
#include "..\ScriptMgr\View\MouseScript.h"
#include "CollisionMgr.h"

#include "..\ScriptMgr\View\SceneTable.h"
#include "..\ScriptMgr\View\AstarMgr.h"
#include "..\ScriptMgr\View\ItemTable.h"
#include "..\ScriptMgr\View\SkillTable.h"
#include "..\ScriptMgr\View\MonsterTable.h"
#include "..\ScriptMgr\View\PortalTable.h"

// 리스폰 스크립트
#include "..\ScriptCode\RespawnScript.h"

CMgrScript::CMgrScript()
{
}

CMgrScript::~CMgrScript()
{
}

/*
0. SceneTable 생성
1. 마우스 생성
2. 스킬테이블 생성
3. 아이템테이블 생성
4. 몬스터테이블 생성
5. 포탈테이블 생성
6. 사운드 로드
*/
void CMgrScript::awake()
{
	////////////////
	// Dont Destory
	///////////////
	static bool bDont = false;
	if (bDont == true) return;
	CSceneMgr::GetInst()->DontDestroyOnLoad(GetGameObject());
	bDont = true;

	// 순서 중요!!
	//CSceneTable* pSceneTable = CSceneTable::GetInst(L"SceneTable", L"Default");
	//pSceneTable->InitSceneTable();
	CMouseScript* pMouseScript = CMouseScript::GetInst(L"MouseObj", L"Mouse");
	CSkillTable* pSkillTable = CSkillTable::GetInst(L"SkillTable", L"Default");
	pSkillTable->InitSkillTable();
	CItemTable* pItemTable = CItemTable::GetInst(L"ItemTable", L"Default");
	pItemTable->InitItemTable();
	CMonsterTable* pMonsterTable = CMonsterTable::GetInst(L"MonsterTable", L"Default");
	pMonsterTable->InitMonsterTable();
	CPortalTable* pPortalTable = CPortalTable::GetInst(L"PortalTable", L"Default");
	pPortalTable->InitPortalTable();

	// 충돌체크
	CCollisionMgr::GetInst()->CheckCollisionLayer(L"Default", L"Mouse");
	CCollisionMgr::GetInst()->CheckCollisionLayer(L"Portal", L"Player");
	CCollisionMgr::GetInst()->CheckCollisionLayer(L"Effect", L"Default");
	//CCamera* pCamera = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Camera")->FindWithTag(L"MainCamera")->Camera();
	//pCamera->SetAllLayerRenderCheck();


	// 나중에 매니저로 만들어서 처리할 것.
	// 플레이어 sound
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"Hit_Dagger", L"Sound\\_hit_dagger.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"Hit_axe", L"Sound\\_hit_axe.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"Hit_mace", L"Sound\\_hit_mace.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"Thief_Invenom", L"Sound\\thief_invenom.wav");

	//etc sound
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"se_drink_potion", L"Sound\\se_drink_potion.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"explosion", L"Sound\\explosion.mp3");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"ef_fireball", L"Sound\\ef_fireball.wav");

	//BGM
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"Prontera", L"Sound\\BGM\\Prontera.mp3");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"Battle1", L"Sound\\BGM\\Battle1.mp3");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"Desert", L"Sound\\BGM\\Desert.mp3");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"BossRoom", L"Sound\\BGM\\BossRoom.mp3");

	// 스킬 sound
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"ef_teleportation", L"Sound\\ef_teleportation.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"se_field_wind_03", L"Sound\\se_field_wind_03.wav");
	
	// 포탈 sound
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"ef_portal", L"Sound\\ef_portal.wav");

	// 몬스터 sound
	// poring
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"poring_attack", L"Sound\\poring_attack.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"poring_damage", L"Sound\\poring_damage.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"poring_die", L"Sound\\poring_die.wav");

	// wolf
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"wolf_attack", L"Sound\\wolf_attack.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"wolf_damage", L"Sound\\wolf_damage.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"wolf_die", L"Sound\\wolf_die.wav");

	// creamy
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"creamy_attack", L"Sound\\creamy_attack.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"creamy_damage", L"Sound\\creamy_damage.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"creamy_die", L"Sound\\creamy_die.wav");
	
	// baphomet
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"baphomet__attack", L"Sound\\baphomet__attack.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"baphomet__damage", L"Sound\\baphomet__damage.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"baphomet__die", L"Sound\\baphomet__die.wav");

	// wraith dead
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"wraith_attack", L"Sound\\wraith_attack.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"wraith_die", L"Sound\\wraith_die.wav");
}

/*
0. Astar 셋팅
*/
void CMgrScript::start()
{
	m_pAstarMgr = CAstarMgr::GetInst();
	m_pAstarMgr->awake();
}

int CMgrScript::update()
{
	return RET_SUCCESS;
}
