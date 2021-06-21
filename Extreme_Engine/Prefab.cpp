#include "Prefab.h"

#include "GameObject.h"

CPrefab::CPrefab(CGameObject * _pObj)
	: m_pObj(_pObj)
{
}

CPrefab::~CPrefab()
{
	RemovePrefab(m_pObj);
}

CGameObject * CPrefab::Instantiate()
{
	return m_pObj->Clone();
}

void CPrefab::RemovePrefab(CGameObject * _pGameObj)
{
	if (NULL == _pGameObj) return;
	list<CGameObject*>& listChild = _pGameObj->GetChildList();

	Safe_Delete_List(listChild);
	/*for (auto& obj : listChild)
	{
		RemovePrefab(obj);
	}*/
	SAFE_DELETE(_pGameObj);
}
