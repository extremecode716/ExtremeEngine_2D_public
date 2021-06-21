#include "DestroyMgr.h"

#include "ResMgr.h"

#include "Gameobject.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Layer.h"

CDestroyMgr::CDestroyMgr()
{

}

CDestroyMgr::~CDestroyMgr()
{

}
void CDestroyMgr::AddGameObject(CGameObject* _obj)
{
	 if (NULL == _obj) return;

	 list<CGameObject*>::iterator iter = _obj->GetChildList().begin();
	 for (; iter != _obj->GetChildList().end(); ++iter)
	 {
		 AddGameObject(*iter);
	 }

	 m_listObj.push_back(_obj); 
}

void CDestroyMgr::Destory()
{
	if (m_listObj.empty()) return;

	vector<CLayer*>& vecLayer = CSceneMgr::GetInst()->GetCurScene()->GetVecLayer();

	vector<CLayer*>::iterator iterLayer = vecLayer.begin();

	//CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->SubGameObject((*iter));
	//CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Transparent")->SubGameObject((*iter));
	//CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Camera")->SubGameObject((*iter));
	for (; iterLayer != vecLayer.end(); ++iterLayer)
	{
		if (NULL == (*iterLayer)) continue;
		list<CGameObject*>::iterator iterObj = m_listObj.begin();
		for (; iterObj != m_listObj.end(); ++iterObj)
		{
			(*iterLayer)->SubGameObject((*iterObj));
		}
	}
	Safe_Delete_List(m_listObj);
	m_listObj.clear();

#ifdef _EXTREME_TOOL
	CSceneMgr::GetInst()->SetUpdateCheck(true);
#endif
}

void CDestroyMgr::Clear()
{
	m_listObj.clear();
}

void CDestroyMgr::DestroyCloneMtrl()
{
}
