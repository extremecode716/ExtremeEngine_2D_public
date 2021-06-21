#include "Layer.h"

#include "GameObject.h"
#include "Transform.h"

#include "Scene.h"
#include "SceneMgr.h"

CLayer::CLayer()
	: m_bZOrder(false)
{
}

CLayer::~CLayer()
{
	Safe_Delete_List(m_listObj);
	//Safe_Delete_List(m_listParentObj);
}

void CLayer::awake()
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end(); ++iter)
	{
		(*iter)->awake();
	}
}

void CLayer::start()
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end(); ++iter)
	{
		(*iter)->start();
	}
}

int CLayer::update()
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end(); ++iter)
	{
		(*iter)->update();
	}
	return RET_SUCCESS;
}

int CLayer::lateupdate()
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end(); ++iter)
	{
		(*iter)->lateupdate();
	}
	return RET_SUCCESS;
}

int CLayer::finalupdate()
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end(); ++iter)
	{
		(*iter)->finalupdate();
	}
	return RET_SUCCESS;
}

void CLayer::render()
{
	// Z Order 정렬
	if (m_bZOrder)
	{
		static list<CGameObject*> listObj;
		listObj = m_listObj;
		listObj.sort([](CGameObject* _pLeft, CGameObject* _pRight)
		{
			return _pLeft->Transform()->GetWorldPos().z > _pRight->Transform()->GetWorldPos().z;
		}
		);

		list<CGameObject*>::iterator iter = listObj.begin();
		for (; iter != listObj.end(); ++iter)
		{
			(*iter)->render();
		}
	}
	else
	{
		list<CGameObject*>::iterator iter = m_listObj.begin();
		for (; iter != m_listObj.end(); ++iter)
		{
			(*iter)->render();
		}
	}
}

void CLayer::render(list<CGameObject*>& _listObj)
{
	_listObj.insert(_listObj.end(), m_listObj.begin(), m_listObj.end());
}

bool CLayer::IsEmpty()
{
	return m_listObj.empty();
}

void CLayer::EraseParentThisObj(CGameObject * _pObj)
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end();)
	{
		if (*iter == _pObj)
		{
			iter = m_listParentObj.erase(iter);
			return;
		}
		else
		{
			++iter;
		}
	}
}

void CLayer::EraseObjFromLayer(CGameObject * _pObj)
{
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end();)
	{
		if ((*iter) == _pObj)
		{
			CGameObject* pParentObj = _pObj->GetParentObj();
			if (NULL != pParentObj)
			{
				// 부모오브젝트를 찾아 자식 오브젝트를 제거한다. (그냥 없앨 경우 쓰레기값이 들어가기 선행처리)
				list<CGameObject*>::iterator iterChild = pParentObj->GetChildList().begin();
				for (; iterChild != pParentObj->GetChildList().end();)
				{
					if ((*iterChild) == _pObj)
					{
						iterChild = pParentObj->GetChildList().erase(iterChild);
						break;
					}
					else
					{
						++iterChild;
					}
				}
			}
			iter = m_listObj.erase(iter);
			break;
		}
		else
		{
			++iter;
		}
	}

	iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end();)
	{
		if ((*iter) == _pObj)
		{
			iter = m_listParentObj.erase(iter);
			break;
		}
		else
		{
			++iter;
		}
	}

}

void CLayer::EraseObjFromLayer_DontDestroy(CGameObject * _pObj)
{
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end();)
	{
		if ((*iter) == _pObj)
		{
			iter = m_listObj.erase(iter);
			break;
		}
		else
		{
			++iter;
		}
	}

	iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end();)
	{
		if ((*iter) == _pObj)
		{
			iter = m_listParentObj.erase(iter);
			break;
		}
		else
		{
			++iter;
		}
	}
}

void CLayer::RemoveObj(CGameObject * _pObj)
{
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end();)
	{
		if ((*iter) == _pObj)
		{
			SAFE_DELETE(*iter);
			iter = m_listObj.erase(iter);
			break;
		}
		else
		{
			++iter;
		}
	}

	iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end();)
	{
		if ((*iter) == _pObj)
		{
			SAFE_DELETE(*iter);
			iter = m_listParentObj.erase(iter);
			return;
		}
		else
		{
			++iter;
		}
	}
}

void CLayer::RemoveParentObj(CGameObject * _pObj)
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end();)
	{
		if (*iter == _pObj)
		{
			SAFE_DELETE(*iter);
			iter = m_listParentObj.erase(iter);
			return;
		}
		else
		{
			++iter;
		}
	}
}

void CLayer::AddGameObject(CGameObject * _pObj, bool _bAll, bool _bPrefab)
{
	if (NULL == _pObj) return;
#ifdef _EXTREME_TOOL
	CSceneMgr::GetInst()->SetUpdateCheck(true);
#endif

	// _pObj 가 최상위 부모인 경우
	if (!_pObj->HasParent() && _pObj->GetLayerName() != m_strLayerName || _bPrefab)
	{
		m_listParentObj.push_back(_pObj);
	}

	list<CGameObject*> listSource;
	if (_bAll)
	{
		list<CGameObject*> queue;
		queue.push_back(_pObj);

		list<CGameObject*>::iterator iter = queue.begin();
		for (; iter != queue.end();)
		{
			queue.insert(queue.end(), (*iter)->GetChildList().begin(), (*iter)->GetChildList().end());

			if ((*iter)->GetLayerName() != m_strLayerName || _bPrefab)
				listSource.push_back(*iter);

			iter = queue.erase(iter);
		}
	}
	else
	{
		if (_pObj->GetLayerName() != m_strLayerName || _bPrefab)
			listSource.push_back(_pObj);
	}

	m_listObj.insert(m_listObj.end(), listSource.begin(), listSource.end());

	// Object 가 이미 이전에 다른 레이어에 들어있었다면,
	// 해당 레이어에서 오브젝트를 삭제해야한다.
	if (!_bPrefab)
	{
		list<CGameObject*>::iterator iter = listSource.begin();
		CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
		for (; iter != listSource.end(); ++iter)
		{
			CLayer* pLayer = pCurScene->FindLayer((*iter)->GetLayerName());
			if (NULL != pLayer)
				pLayer->EraseObjFromLayer((*iter));

			(*iter)->SetLayerName(m_strLayerName);
		}
	}
	else
	{
		_pObj->SetLayerName(m_strLayerName);
	}
}

CGameObject * CLayer::FindObjectByTag(const wstring & _strTag)
{
	list<CGameObject*>::iterator iter = m_listObj.begin();

	for (; iter != m_listObj.end(); ++iter)
	{
		if ((*iter)->GetTag() == _strTag)
			return *iter;
	}

	return NULL;
}

CGameObject * CLayer::FindObject(const Vec2& _vWorldPos)
{
	list<CGameObject*>::iterator iter = m_listObj.begin();

	for (; iter != m_listObj.end(); ++iter)
	{
		if ((*iter)->IsMouseOn(_vWorldPos))
		{
			return *iter;
		}
	}

	return NULL;
}


void CLayer::AddParentObject(CGameObject* _pParentObj)
{
	if (!_pParentObj->HasParent())
		m_listParentObj.push_back(_pParentObj);
}


CGameObject * CLayer::FindWithTag(const wstring& _strObjName)
{
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end(); ++iter)
	{
		if ((*iter)->GetTag() == _strObjName)
			return (*iter);
	}
	return NULL;
}

CGameObject * CLayer::FindGameObject(CGameObject* _gameObj)
{
	CGameObject* GameObj = _gameObj;
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end(); ++iter)
	{
		if ((*iter) == GameObj)
			return (*iter);
	}
	return NULL;
}

void CLayer::SubGameObject(CGameObject* _gameObj)
{
	CGameObject* pFindGameObj = _gameObj;
	if (NULL == pFindGameObj) return;
	EraseObjFromLayer(pFindGameObj);
}



/*
함수명  : SubGameObjectByChild(CGameObject * _pObj)
용도    : 매개변수로 들어온 오브젝트로 부터 하위 오브젝트들을 listobj 와 listParentObj 에서 지워준다.(DontDestory에서 씬 전환시 사용)
*/
void CLayer::SubGameObjectByChild(CGameObject * _pObj)
{
	CGameObject* pFindGameObj = _pObj;
	if (NULL == pFindGameObj) return;

	list<CGameObject*> listObj;

	// 자식 객체까지 BFS 반복
	list<CGameObject*> queue;
	queue.push_back(pFindGameObj);

	list<CGameObject*>::iterator iter = queue.begin();
	for (; iter != queue.end();)
	{
		queue.insert(queue.end(), (*iter)->GetChildList().begin(), (*iter)->GetChildList().end());

		listObj.push_back(*iter);

		iter = queue.erase(iter);
	}

	// erase
	iter = listObj.begin();
	for (; iter != listObj.end(); ++iter)
	{
		EraseObjFromLayer_DontDestroy(*iter);
	}
}


void CLayer::SubGameObject(const wstring & _strObjName)
{
	CGameObject* GameObj = FindWithTag(_strObjName);
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end();)
	{
		if (GameObj == (*iter))
		{
			CGameObject* pParentObj = GameObj->GetParentObj();
			if (NULL != pParentObj)
			{
				list<CGameObject*>::iterator iterChild = pParentObj->GetChildList().begin();
				for (; iterChild != pParentObj->GetChildList().end();)
				{
					if ((*iterChild) == GameObj)
					{
						iterChild = pParentObj->GetChildList().erase(iterChild);
						break;
					}
					else
					{
						++iterChild;
					}
				}
			}
			iter = m_listObj.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	list<CGameObject*>::iterator iterParent = m_listParentObj.begin();
	for (; iterParent != m_listParentObj.end();)
	{
		if (GameObj == (*iterParent))
		{
			iterParent = m_listParentObj.erase(iterParent);
		}
		else
		{
			++iterParent;
		}
	}
}


void CLayer::Destory(const wstring& _strObjName)
{
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end(); ++iter)
	{
		if ((*iter)->GetTag() == _strObjName)
		{
			SAFE_DELETE((*iter));
		}
	}
}
