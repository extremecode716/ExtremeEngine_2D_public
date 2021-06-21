#include "stdafx.h"
#include "SkillTable.h"

#include "..\External\DefineCode\Skill.h"

// 스킬 추가↓
#include "..\External\DefineCode\TeleportSkill.h"
#include "..\External\DefineCode\TornadoSkill.h"
#include "..\External\DefineCode\MeteorSkill.h"
#include "..\External\DefineCode\RecoverySkill.h"

CSkillTable::CSkillTable()
{
}


CSkillTable::~CSkillTable()
{
	Safe_Delete_Map(m_mapSkillTable);
}

void CSkillTable::InitSkillTable()
{
	////////////////
	// Dont Destory
	///////////////
	static bool bDont = false;
	if (bDont == true) return;
	CSceneMgr::GetInst()->DontDestroyOnLoad(GetGameObject());
	bDont = true;

	CSkill* pSkill = NULL;

	// 텔레포트
	pSkill = new CTeleportSkill;
	InsertSkill(L"Skill_Teleport", pSkill);

	// 토네이도
	pSkill = new CTornadoSkill;
	InsertSkill(L"Skill_Tornado", pSkill);

	// 메테오
	pSkill = new CMeteorSkill;
	InsertSkill(L"Skill_Meteor", pSkill);

	// HP 회복 스킬
	pSkill = new CRecoverySkill;
	((CRecoverySkill*)pSkill)->SetSkillInfo(L"HP", 1000);
	InsertSkill(L"Skill_HPRecovery", pSkill);

	// SP 회복 스킬
	pSkill = new CRecoverySkill;
	((CRecoverySkill*)pSkill)->SetSkillInfo(L"SP", 1000);
	InsertSkill(L"Skill_SPRecovery", pSkill);
}

CSkill * CSkillTable::FindSkill(const wstring & _strName)
{
	map<wstring, CSkill*>::const_iterator iter = m_mapSkillTable.find(_strName);
	if (iter == m_mapSkillTable.end())
		return NULL;

	return iter->second;
}

bool CSkillTable::InsertSkill(const wstring & _strName, CSkill * _pSkill)
{
	if (NULL == _pSkill) return false;

	CSkill* pFindSkill = FindSkill(_strName);
	if (NULL != pFindSkill)
	{
		SAFE_DELETE(_pSkill);
		return false;
	}

	m_mapSkillTable.insert(make_pair(_strName, _pSkill));
	return true;
}

int CSkillTable::update()
{
	return RET_SUCCESS;
}
