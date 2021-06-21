#include "stdafx.h"
#include "MonsterTable.h"

CMonsterTable::CMonsterTable()
{
}


CMonsterTable::~CMonsterTable()
{
	Safe_Delete_Map(m_mapMonsterStatuse);
}

/*
�Լ���  : InitMonsterTable()
�뵵    : ���� ���̺� �ʱ�ȭ.
*/
void CMonsterTable::InitMonsterTable()
{
	////////////////
	// Dont Destory
	///////////////
	static bool bDont = false;
	if (bDont == true) return;
	CSceneMgr::GetInst()->DontDestroyOnLoad(GetGameObject());
	bDont = true;

	CPrefab* pMonster = NULL;
	tStatus* pStatuse = NULL;

	// �Ϲ����� Poring
	pMonster = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Monster_Poring(Prefab)");
	InsertMonster(L"Poring", pMonster);
	pStatuse = new tStatus(1, 1500, 1500, 1500, 1500, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 250, 0);
	InsertMonsterStatus(L"Poring", pStatuse);

	// ��� ����
	pMonster = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Monster_GoldPoring(Prefab)");
	InsertMonster(L"GoldPoring", pMonster);
	pStatuse = new tStatus(1, 2500, 2500, 2500, 2500, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 250, 0);
	InsertMonsterStatus(L"GoldPoring", pStatuse);

	// ���� ����
	pMonster = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Monster_Deviling(Prefab)");
	InsertMonster(L"Deviling", pMonster);
	pStatuse = new tStatus(1, 3000, 3000, 3000,3000, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 250, 0);
	InsertMonsterStatus(L"Deviling", pStatuse);

	// ����
	pMonster = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Monster_Wolf(Prefab)");
	InsertMonster(L"Wolf", pMonster);
	pStatuse = new tStatus(1, 7000, 7000, 7000, 7000, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 250, 0);
	InsertMonsterStatus(L"Wolf", pStatuse);


	// ������Ʈ �ִϾ�
	pMonster = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Monster_BaphometJR(Prefab)");
	InsertMonster(L"BaphometJR", pMonster);
	pStatuse = new tStatus(1, 10000, 10000, 10000, 10000, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 250, 0);
	InsertMonsterStatus(L"BaphometJR", pStatuse);

	// ũ����
	pMonster = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Monster_Creamy(Prefab)");
	InsertMonster(L"Creamy", pMonster);
	pStatuse = new tStatus(1, 5000, 5000, 5000, 5000, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 250, 0);
	InsertMonsterStatus(L"Creamy", pStatuse);

	// ������Ʈ
	pMonster = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Monster_Baphomet(Prefab)");
	InsertMonster(L"Baphomet", pMonster);
	pStatuse = new tStatus(1, 40000, 40000, 40000, 40000, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 250, 0);
	InsertMonsterStatus(L"Baphomet", pStatuse);

	// ���̾� ����
	pMonster = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Monster_WraithDead(Prefab)");
	InsertMonster(L"WraithDead", pMonster);
	pStatuse = new tStatus(1, 50000, 50000, 50000, 50000, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 250, 0);
	InsertMonsterStatus(L"WraithDead", pStatuse);

}


CPrefab * CMonsterTable::FindMonster(const wstring & _strKey)
{
	map<wstring, CPrefab*>::const_iterator iter = m_mapMonsterTable.find(_strKey);
	auto mapNull = m_mapMonsterTable.end();

	if (iter == mapNull)
		return NULL;

	return iter->second;
}

tStatus* CMonsterTable::FindMonsterStatus(const wstring & _strKey)
{
	map<wstring, tStatus*>::const_iterator iter = m_mapMonsterStatuse.find(_strKey);
	auto mapNull = m_mapMonsterStatuse.end();

	if (iter == mapNull)
		return NULL;

	return iter->second;
}

bool CMonsterTable::InsertMonster(const wstring & _strKey, CPrefab * _pMonsterPrefab)
{
	if (NULL == _pMonsterPrefab) return false;

	CPrefab* pFindMonster = FindMonster(_strKey);
	if (NULL != pFindMonster)
	{
		return false;
	}

	m_mapMonsterTable.insert(make_pair(_strKey, _pMonsterPrefab));
	return true;
}
bool CMonsterTable::InsertMonsterStatus(const wstring & _strKey, tStatus* _pStatuse)
{
	tStatus* pFindMonster = FindMonsterStatus(_strKey);
	if (NULL != pFindMonster)
	{
		SAFE_DELETE(_pStatuse);
		return false;
	}

	m_mapMonsterStatuse.insert(make_pair(_strKey, _pStatuse));
	return true;
}
