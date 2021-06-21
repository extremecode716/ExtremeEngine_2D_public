#include "Script.h"

#include "Scene.h"
#include "Layer.h"
#include "SceneMgr.h"

CScript::CScript()
{
}


CScript::~CScript()
{
}

CGameObject* CScript::Instantiate(CPrefab * _pPrefab, const Vec3 & _vPos, const wstring & _strLayerName)
{
	if (NULL == _pPrefab) return NULL;
	CGameObject* pCloneObj = _pPrefab->Instantiate();
	
	pCloneObj->Transform()->SetLocalPos(_vPos);

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->FindLayer(_strLayerName);
	if (NULL == pLayer) return NULL;
	pLayer->AddGameObject(pCloneObj, true, true);

	return pCloneObj;
}

