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

// ������ ��ũ��Ʈ
#include "..\ScriptCode\RespawnScript.h"

CMgrScript::CMgrScript()
{
}

CMgrScript::~CMgrScript()
{
}

/*
0. SceneTable ����
1. ���콺 ����
2. ��ų���̺� ����
3. ���������̺� ����
4. �������̺� ����
5. ��Ż���̺� ����
6. ���� �ε�
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

	// ���� �߿�!!
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

	// �浹üũ
	CCollisionMgr::GetInst()->CheckCollisionLayer(L"Default", L"Mouse");
	CCollisionMgr::GetInst()->CheckCollisionLayer(L"Portal", L"Player");
	CCollisionMgr::GetInst()->CheckCollisionLayer(L"Effect", L"Default");
	//CCamera* pCamera = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Camera")->FindWithTag(L"MainCamera")->Camera();
	//pCamera->SetAllLayerRenderCheck();


	// ���߿� �Ŵ����� ���� ó���� ��.
	// �÷��̾� sound
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

	// ��ų sound
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"ef_teleportation", L"Sound\\ef_teleportation.wav");
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"se_field_wind_03", L"Sound\\se_field_wind_03.wav");
	
	// ��Ż sound
	(CSound*)CResMgr::GetInst()->Load<CSound>(L"ef_portal", L"Sound\\ef_portal.wav");

	// ���� sound
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
0. Astar ����
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
