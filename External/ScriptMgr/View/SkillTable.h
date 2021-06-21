#pragma once
#include "..\SingletonScript.h"

class CSkill;
class CSkillTable :
	public CSingletonScript<CSkillTable>
{
private:
	map<wstring, CSkill*> m_mapSkillTable;

private:
	bool InsertSkill(const wstring& _strName, CSkill* _pSkill);

public:
	void InitSkillTable();
	CSkill* FindSkill(const wstring& _strName);

private:
	virtual int update() override;

public:
	virtual CSkillTable* Clone() override { return new CSkillTable(*this); }
public:
	CSkillTable();
	virtual ~CSkillTable();
};

