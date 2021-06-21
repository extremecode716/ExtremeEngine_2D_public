#include "stdafx.h"
#include "PortalTable.h"
#include "..\External\ScriptCode\PortalScript.h"

CPortalTable::CPortalTable()
{
}


CPortalTable::~CPortalTable()
{
}

/*
함수명  : InitPortalTable()
용도    : 포탈 테이블 초기화.
*/
void CPortalTable::InitPortalTable()
{
	////////////////
	// Dont Destory
	///////////////
	static bool bDont = false;
	if (bDont == true) return;
	CSceneMgr::GetInst()->DontDestroyOnLoad(GetGameObject());
	bDont = true;

	// prontera
	InsertPortal(L"Portal_prontera", L"prontera", L"Portal(Prefab)");

	// battleground1
	InsertPortal(L"Portal_battleground1", L"battleground1" , L"Portal(Prefab)");

	// battleground2
	InsertPortal(L"Portal_battleground2", L"battleground2" , L"Portal(Prefab)");

	// battleground3
	InsertPortal(L"Portal_battleground3", L"battleground3", L"Portal(Prefab)");
}


bool CPortalTable::InsertPortal(const wstring & _strKey, const wstring&  _strNextSceneKey, const wstring& _strPrefab)
{
	tuple<wstring, CPrefab*> tuplePortal = FindPortal(_strKey);
	if (std::get<1>(tuplePortal) != NULL) return false;

	CPrefab* pPortalPrefab = NULL;
	pPortalPrefab = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(_strPrefab);

	tuplePortal = make_tuple(_strNextSceneKey, pPortalPrefab);
	m_mapPortalTable.insert(make_pair(_strKey, tuplePortal));

	return true;
}

tuple<wstring, CPrefab*> CPortalTable::FindPortal(const wstring & _strKey)
{
	map<wstring, tuple<wstring, CPrefab*>>::const_iterator iter = m_mapPortalTable.find(_strKey);
	auto mapNull = m_mapPortalTable.end();
	if (mapNull == iter)
		return make_tuple(L"", (CPrefab*)NULL);

	return iter->second;
}

bool CPortalTable::CreatePortal(const wstring & _strKey, const Vec3 & _vPos, const Vec3 & _vSpawnPos, const wstring & _strTitleKey, const wstring & _strTitleText, const wstring & _strLayer)
{
	tuple<wstring, CPrefab*> tuplePortal = FindPortal(_strKey);
	if (std::get<1>(tuplePortal) == NULL) return false;

	wstring strSceneKey = get<0>(tuplePortal);
	CPrefab* pPortalPrefab = get<1>(tuplePortal);
	CGameObject* pPortal = Instantiate(pPortalPrefab, _vPos, _strLayer);
	CPortalScript* pPortalScript = new CPortalScript;
	pPortalScript->SetScenKey(strSceneKey);
	pPortalScript->SetSpawnPos(_vSpawnPos);
	pPortalScript->SetTitleText(_strTitleKey, _strTitleText);
	pPortal->AddComponent<CScript>(pPortalScript);
	//pPortalScript->awake();
	//pPortalScript->start();

	return true;
}
