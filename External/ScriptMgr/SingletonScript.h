#pragma once
#include "Script.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Script.h"

template<typename T>
class CSingletonScript
	: public CScript
{
protected:
	static bool g_bLoad;
	static T* g_pThis;

public:
	static T* GetInst(const wstring& _strMgrObj = L"MgrObject", const wstring& _strLayer = L"Default");
	static T* GetThis();

public:
	CSingletonScript() { }
	virtual ~CSingletonScript() 
	{
		if (false == g_bLoad)
			g_pThis = NULL;

		g_bLoad = false;
	};
};

template<typename T>
bool CSingletonScript<T>::g_bLoad = false;
template<typename T>
T* CSingletonScript<T>::g_pThis = NULL;

template<typename T>
T* CSingletonScript<T>::GetInst(const wstring& _strMgrObj, const wstring& _strLayer)
{
	if (NULL == g_pThis)
	{
		g_pThis = new T;
	}
	else
		return g_pThis;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->FindLayer(_strLayer);
	CGameObject* pObj = pLayer->FindObjectByTag(_strMgrObj);

	if (NULL == pObj)
	{
		pObj = new CGameObject;
		pObj->AddComponent<CTransform>(new CTransform);
		pObj->SetTag(_strMgrObj);
		pLayer->AddGameObject(pObj);
	}
	
	pObj->AddComponent<CScript>(g_pThis);

	return g_pThis;
}

template<typename T>
inline T * CSingletonScript<T>::GetThis()
{
	return g_pThis;
}
