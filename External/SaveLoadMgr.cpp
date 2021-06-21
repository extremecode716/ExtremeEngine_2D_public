#include "stdafx.h"
#include "SaveLoadMgr.h"


#include "ScriptMgr.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "Component.h"
#include "Script.h"
#include "Prefab.h"

#include "Transform.h"
#include "MeshRender.h"
#include "Collider_2D.h"
#include "Animator.h"
#include "Camera.h"

#include "DebugMgr.h" 

CSaveLoadMgr::CSaveLoadMgr()
{
}

CSaveLoadMgr::~CSaveLoadMgr()
{
}

/////////////////
// Scene Save
/////////////////
void CSaveLoadMgr::SaveScene(const wstring & _strFilePath)
{
#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"=====Scene Save Start=====");
#endif
	FILE *pFile = NULL;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");

	if (NULL == pFile)
		assert(NULL);

	// Resource 저장
	CResMgr::GetInst()->SaveResource(pFile);

	// Prefab 저장
#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"===Prefab Save Start===");
#endif
	map<wstring, CResPtr<CPrefab>>& mapPrefab = CResMgr::GetInst()->GetPrefabMap();
	UINT iCount = mapPrefab.size();
	fwrite(&iCount, sizeof(UINT), 1, pFile);

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"-Prefab Count-");
	CDebugMgr::GetInst()->Log(iCount);
#endif

	for (auto& pair : mapPrefab)
	{
		SaveResourceKey((CRes*)pair.second, pFile);
		SaveGameObject(pair.second->GameObject(), pFile);
	}
#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"===Prefab Save End===");
#endif

	CScene* pScene = CSceneMgr::GetInst()->GetCurScene();

	// Layer Save
	iCount = pScene->GetLayerCount();
	fwrite(&iCount, sizeof(UINT), 1, pFile);

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"-Layer Count-");
	CDebugMgr::GetInst()->Log(iCount);
#endif

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"===Layer Save Start===");
#endif
	vector<CLayer*>& vecLayer = pScene->GetVecLayer();
	UINT vecSize = vecLayer.size();
	for (UINT i = 0; i < vecSize; ++i)
	{
		if (NULL != vecLayer[i])
			SaveLayer(vecLayer[i], pFile);
	}

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"===Layer Save End===");
#endif

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"======Scene Save End======");
#endif

	fclose(pFile);
}

void CSaveLoadMgr::SaveStopScene(const wstring & _strFilePath)
{
#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"=====Scene Save Start=====");
#endif
	FILE *pFile = NULL;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");

	if (NULL == pFile)
		assert(NULL);
	UINT iCount = 0;
	CScene* pScene = CSceneMgr::GetInst()->GetCurScene();

	// Layer Save
	iCount = pScene->GetLayerCount();
	fwrite(&iCount, sizeof(UINT), 1, pFile);

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"-Layer Count-");
	CDebugMgr::GetInst()->Log(iCount);
#endif

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"===Layer Save Start===");
#endif
	vector<CLayer*>& vecLayer = pScene->GetVecLayer();
	UINT vecSize = vecLayer.size();
	for (UINT i = 0; i < vecSize; ++i)
	{
		if (NULL != vecLayer[i])
			SaveLayer(vecLayer[i], pFile);
	}

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"===Layer Save End===");
#endif

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"======Scene Save End======");
#endif

	fclose(pFile);
}

/////////////////
// Layer Save
/////////////////
void CSaveLoadMgr::SaveLayer(CLayer * _pLayer, FILE * _pFile)
{
	// Layer Idx
	UINT iLayerIdx = _pLayer->GetLayerIdx();
	fwrite(&iLayerIdx, sizeof(UINT), 1, _pFile);
#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"--Layer Idx--");
	CDebugMgr::GetInst()->Log(iLayerIdx);
#endif
	// Layer Name
	SaveWString(_pLayer->GetLayerName(), _pFile);

	// Parent Object Count
	list<CGameObject*>& listParent = _pLayer->GetParentObjList();
	UINT iParentObjCount = listParent.size();
	fwrite(&iParentObjCount, sizeof(UINT), 1, _pFile);
#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"-ParentObj Count-");
	CDebugMgr::GetInst()->Log(iParentObjCount);
#endif
	// Save Parent Obj
	list<CGameObject*>::iterator iter = listParent.begin();
	for (; iter != listParent.end(); ++iter)
	{
		SaveGameObject((*iter), _pFile);
	}
}

/////////////////
// GameObject Save
/////////////////
void CSaveLoadMgr::SaveGameObject(CGameObject * _pObj, FILE * _pFile)
{
#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"==GameObj Save Start==");
#endif
	// Tag
	SaveWString(_pObj->GetTag(), _pFile);

	// Component
#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"=Component Start=");
#endif
	UINT i = (UINT)COMPONENT_TYPE::TRANSFORM;
	for (i; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		CComponent* pCom = _pObj->GetComponent((COMPONENT_TYPE)i);
		if (NULL == pCom)
			continue;

		pCom->Save(_pFile);
	}
	// COMPONENT_TYPE::END; 게임오브젝트 컴포넌트 마감
	fwrite(&i, sizeof(UINT), 1, _pFile);

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"=Component End=");
#endif
	//*
	// Script Count
	list<CScript*>& listScript = _pObj->GetScriptList();
	UINT iScriptCount = listScript.size();
	fwrite(&iScriptCount, sizeof(UINT), 1, _pFile);

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"-Script Count-");
	CDebugMgr::GetInst()->Log(iScriptCount);
#endif
	// Script
	list<CScript*>::iterator iter = listScript.begin();
	for (iter; iter != listScript.end(); ++iter)
	{
		SaveWString(CScriptMgr::GetScriptName(*iter), _pFile);
		(*iter)->Save(_pFile);  // 구현요망
	}
	//*/

	// Child GameObject Count
	list<CGameObject*>& listChild = _pObj->GetChildList();
	UINT iChildObjCount = listChild.size();
	fwrite(&iChildObjCount, sizeof(UINT), 1, _pFile);

#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"-ChildObj Count-");
	CDebugMgr::GetInst()->Log(iChildObjCount);
#endif

	// Child GameObject
	list<CGameObject*>::iterator childIter = listChild.begin();
	for (; childIter != listChild.end(); ++childIter)
	{
		SaveGameObject(*childIter, _pFile);
	}
#ifdef SAVELOAD_DEBUG
	CDebugMgr::GetInst()->Log(L"==GameObj Save End==");
#endif
}

/////////////////
// Scene Load
/////////////////
void CSaveLoadMgr::LoadScene(const wstring & _strFilePath, bool bScript)
{
	FILE* pFile = NULL;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");

	if (NULL == pFile)
		assert(NULL);

	// Resource Load
	CResMgr::GetInst()->LoadResource(pFile);

	// Prefab Load	
	UINT iCount = 0;
	fread(&iCount, sizeof(UINT), 1, pFile);

	for (UINT i = 0; i < iCount; ++i)
	{
		wstring strKey = LoadResourceKey(pFile);
		CGameObject* pObj = LoadGameObject(pFile);
		CResMgr::GetInst()->AddPrefab(strKey, pObj);
	}

	CScene* pScene = new CScene;

	// Layer Count
	iCount = 0;
	fread(&iCount, sizeof(UINT), 1, pFile);

	for (UINT i = 0; i < iCount; ++i)
	{
		CLayer* pLayer = LoadLayer(pFile);
		pScene->AddLayer(pLayer);
	}
	// Layer 추가시 수정 할 것
	//pScene->AddLayer(L"Player");
	//pScene->AddLayer(L"Portal");
	//pScene->AddLayer(L"Tile");
	//pScene->AddLayer(L"Effect");

	CSceneMgr::GetInst()->ChangeScene(pScene, bScript);
	fclose(pFile);
}


void CSaveLoadMgr::LoadPlayScene(const wstring & _strFilePath)
{
	FILE* pFile = NULL;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");

	if (NULL == pFile)
		assert(NULL);

	UINT iCount = 0;
	CScene* pScene = new CScene;

	// Layer Count
	iCount = 0;
	fread(&iCount, sizeof(UINT), 1, pFile);

	for (UINT i = 0; i < iCount; ++i)
	{
		CLayer* pLayer = LoadLayer(pFile);
		pScene->AddLayer(pLayer);
	}

	CSceneMgr::GetInst()->ChangeScene(pScene);
	fclose(pFile);
}

CLayer * CSaveLoadMgr::LoadLayer(FILE * _pFile)
{
	CLayer* pLayer = new CLayer;

	// Read Layer Index
	UINT	iLayerIdx = 0;
	fread(&iLayerIdx, sizeof(UINT), 1, _pFile);
	pLayer->SetLayerIdx(iLayerIdx);

	// Read Layer Name
	pLayer->SetLayerName(LoadWString(_pFile));

	// Parent Object Count
	UINT iParentObjCount = 0;
	fread(&iParentObjCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iParentObjCount; ++i)
	{
		CGameObject* pObj = LoadGameObject(_pFile);
		pLayer->AddGameObject(pObj);
	}

	return pLayer;
}

CGameObject * CSaveLoadMgr::LoadGameObject(FILE * _pFile)
{
	CGameObject* pObj = new CGameObject;

	// Tag
	pObj->SetTag(LoadWString(_pFile));

	// Component
	UINT iType = 0;
	CComponent* pComponent = NULL;

	while (iType != (UINT)COMPONENT_TYPE::END)
	{
		fread(&iType, sizeof(UINT), 1, _pFile);

		switch (iType)
		{
		case (UINT)COMPONENT_TYPE::TRANSFORM:
			pComponent = new CTransform;
			pComponent->Load(_pFile);
			pObj->AddComponent<CTransform>(pComponent);
			break;
		case (UINT)COMPONENT_TYPE::MESHRENDER:
			pComponent = new CMeshRender;
			pComponent->Load(_pFile);
			pObj->AddComponent<CMeshRender>(pComponent);
			break;
		case (UINT)COMPONENT_TYPE::COLLIDER_2D:
			pComponent = new CCollider_2D;
			pComponent->Load(_pFile);
			pObj->AddComponent<CCollider>(pComponent);
			break;
		case (UINT)COMPONENT_TYPE::COLLIDER_3D:
			break;

		case (UINT)COMPONENT_TYPE::ANIMATOR:
			pComponent = new CAnimator;
			pComponent->Load(_pFile);
			pObj->AddComponent<CAnimator>(pComponent);
			break;
		case (UINT)COMPONENT_TYPE::CAMERA:
			pComponent = new CCamera;
			pComponent->Load(_pFile);
			pObj->AddComponent<CCamera>(pComponent);
			break;
		}
	}

	UINT iCount = 0;
	//*
	// Script Count
	wstring strScriptName;
	fread(&iCount, sizeof(UINT), 1, _pFile);

	// Script
	for (UINT i = 0; i < iCount; ++i)
	{
		strScriptName = LoadWString(_pFile);
		CScript* pScript = CScriptMgr::GetScript(strScriptName);
		pObj->AddComponent<CScript>(pScript);

		pScript->Load(_pFile);
	}
	//*/
	// Child Object Count
	fread(&iCount, sizeof(UINT), 1, _pFile);

	// Child Object
	for (UINT i = 0; i < iCount; ++i)
	{
		CGameObject* pChildObj = LoadGameObject(_pFile);
		pObj->AddChildObj(pChildObj);
	}

	return pObj;
}