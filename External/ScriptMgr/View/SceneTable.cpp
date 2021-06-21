#include "stdafx.h"
#include "SceneTable.h"

#include "SaveLoadMgr.h"

CSceneTable::CSceneTable()
{
}


CSceneTable::~CSceneTable()
{
}

void CSceneTable::InitSceneTable()
{
	////////////////
	// Dont Destory
	///////////////
	static bool bDont = false;
	if (bDont == true) return;
	CSceneMgr::GetInst()->DontDestroyOnLoad(GetGameObject());
	bDont = true;

	wstring strInitPath = CPathMgr::GetResPath();
	wstring strKey;
	wstring strPath;
	strInitPath += L"Scene\\";

	// Main-> 최신 업데이트시 수정할 것.
	strKey = L"Ragnarok_00_39";
	strPath = strInitPath + strKey + L".scene";
	m_mapSceneTable.insert(make_pair(strKey, strPath));

	// 프론테라
	strKey = L"prontera";
	strPath = strInitPath + strKey + L".scene";
	m_mapSceneTable.insert(make_pair(strKey, strPath));

	// battleground1
	strKey = L"battleground1";
	strPath = strInitPath + strKey + L".scene";
	m_mapSceneTable.insert(make_pair(strKey, strPath));

	// battleground2
	strKey = L"battleground2";
	strPath = strInitPath + strKey + L".scene";
	m_mapSceneTable.insert(make_pair(strKey, strPath));

	// battleground3
	strKey = L"battleground3";
	strPath = strInitPath + strKey + L".scene";
	m_mapSceneTable.insert(make_pair(strKey, strPath));
}

const wchar_t* CSceneTable::FindPath(const wstring & _strKey)
{
	map<wstring, wstring>::const_iterator iter = m_mapSceneTable.find(_strKey);

	if (iter == m_mapSceneTable.end())
	{
		return NULL;
	}
	
	return iter->second.c_str();
}

/*
함수명 : ChangeScene(const wstring& _strKey)
용도   : 스크립트에서 씬을 전환할때 사용.
*/

bool CSceneTable::ChangeScene(const wstring& _strKey)
{
	const wchar_t* strPath = FindPath(_strKey);

	if (NULL == strPath) return false;

	CSaveLoadMgr::GetInst()->LoadScene(strPath, true);

	return true;
}
