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

	// Main-> �ֽ� ������Ʈ�� ������ ��.
	strKey = L"Ragnarok_00_39";
	strPath = strInitPath + strKey + L".scene";
	m_mapSceneTable.insert(make_pair(strKey, strPath));

	// �����׶�
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
�Լ��� : ChangeScene(const wstring& _strKey)
�뵵   : ��ũ��Ʈ���� ���� ��ȯ�Ҷ� ���.
*/

bool CSceneTable::ChangeScene(const wstring& _strKey)
{
	const wchar_t* strPath = FindPath(_strKey);

	if (NULL == strPath) return false;

	CSaveLoadMgr::GetInst()->LoadScene(strPath, true);

	return true;
}
