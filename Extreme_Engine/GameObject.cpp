#include "GameObject.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"

//#include "Meshrender.h"
#include "Script.h"

CGameObject::CGameObject()
	: m_bActive(true)
	, m_bEnable(true)
	, m_strTag(L"")
	, m_strLayerName(L"")
	, m_arrCom{}
	, m_listScript{}
	, m_pParentObj(NULL)
	, m_bScriptEvent(false)
	
{
}

CGameObject::CGameObject(const CGameObject& _pOther)
	: m_bActive(_pOther.m_bActive)
	, m_bEnable(_pOther.m_bEnable)
	, m_strTag(_pOther.m_strTag)
	, m_strLayerName(_pOther.m_strLayerName)
	, m_arrCom{}
	, m_listScript{}
	, m_pParentObj(_pOther.m_pParentObj)
	, m_bScriptEvent(_pOther.m_bScriptEvent)
{

	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != _pOther.m_arrCom[i])
		{
			m_arrCom[i] = _pOther.m_arrCom[i]->Clone();
			m_arrCom[i]->SetGameObject(this);
		}
	}

	list<CScript*>::const_iterator iter = _pOther.m_listScript.begin();
	for (; iter != _pOther.m_listScript.end(); ++iter)
	{
		CScript* pCloneScript = (*iter)->Clone();
		pCloneScript->SetGameObject(this);
		m_listScript.push_back(pCloneScript);
	}

	list<CGameObject*>::const_iterator iterObj = _pOther.m_listChildObj.begin();
	for (; iterObj != _pOther.m_listChildObj.end(); ++iterObj)
	{
		AddChildObj((*iterObj)->Clone());
	}

}

CGameObject::~CGameObject()
{
	for (int i = 0; i != (UINT)COMPONENT_TYPE::END; ++i)
	{
		SAFE_DELETE(m_arrCom[i]);
	}

	Safe_Delete_List(m_listScript);

	//list<CGameObject*>::iterator iterChildObj = m_listChildObj.begin();
	//for (; iterChildObj != m_listChildObj.end(); ++iterChildObj)
	//{
	//	CDestroyMgr::
	//}
}

void CGameObject::awake()
{
	if (false == m_bActive) return;

	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrCom[i])
			m_arrCom[i]->awake();
	}

	list<CScript*>::iterator iter = m_listScript.begin();
	for (; iter != m_listScript.end(); ++iter)
	{
		(*iter)->awake();
	}

	list<CGameObject*>::iterator iterChild = m_listChildObj.begin();
	for (; iterChild != m_listChildObj.end(); ++iterChild)
	{
		(*iterChild)->awake();
	}
}

void CGameObject::start()
{
	if (false == m_bActive) return;

	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrCom[i])
			m_arrCom[i]->start();
	}

	list<CScript*>::iterator iter = m_listScript.begin();
	for (; iter != m_listScript.end(); ++iter)
	{
		(*iter)->start();
	}

	list<CGameObject*>::iterator iterChild = m_listChildObj.begin();
	for (; iterChild != m_listChildObj.end(); ++iterChild)
	{
		(*iterChild)->start();
	}
}

int CGameObject::update()
{
	if (false == m_bActive) return RET_SUCCESS;

	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrCom[i])
			m_arrCom[i]->update();
	}

	list<CScript*>::iterator iter = m_listScript.begin();
	for (; iter != m_listScript.end(); ++iter)
	{
		(*iter)->update();
	}

	list<CGameObject*>::iterator iterChild = m_listChildObj.begin();
	for (; iterChild != m_listChildObj.end(); ++iterChild)
	{
		(*iterChild)->update();
	}

	return RET_SUCCESS;
}

int CGameObject::lateupdate()
{
	if (false == m_bActive) return RET_SUCCESS;

	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrCom[i])
			m_arrCom[i]->lateupdate();
	}

	list<CScript*>::iterator iter = m_listScript.begin();
	for (; iter != m_listScript.end(); ++iter)
	{
		(*iter)->lateupdate();
	}

	list<CGameObject*>::iterator iterChild = m_listChildObj.begin();
	for (; iterChild != m_listChildObj.end(); ++iterChild)
	{
		(*iterChild)->lateupdate();
	}
	return RET_SUCCESS;
}

int CGameObject::finalupdate()
{
	if (false == m_bActive) return RET_SUCCESS;

	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrCom[i])
			m_arrCom[i]->finalupdate();
	}
	list<CGameObject*>::iterator iterChild = m_listChildObj.begin();
	for (; iterChild != m_listChildObj.end(); ++iterChild)
	{
		if (NULL != *iterChild)
		(*iterChild)->finalupdate();
	}

	return RET_SUCCESS;
}

void CGameObject::render()
{
	if (false == m_bActive) return;
	if (NULL != MeshRender())
	{
		MeshRender()->render();
	}
}

void CGameObject::Destroy()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		SAFE_DELETE(m_arrCom[i]);
	}

	Safe_Delete_List(m_listScript);
}

bool CGameObject::IsMouseOn(const Vec2& _vWorldPos)
{
	Vec3 vWorldPos = Transform()->GetWorldPos();
	Vec3 vWorldScale = Transform()->GetWorldScale();

	if (vWorldPos.x - vWorldScale.x / 2.f <= _vWorldPos.x &&  _vWorldPos.x <= vWorldPos.x + vWorldScale.x / 2.f
		&& vWorldPos.y - vWorldScale.y / 2.f <= _vWorldPos.y &&  _vWorldPos.y <= vWorldPos.y + vWorldScale.y / 2.f)
	{
		return true;
	}

	return false;
}

int CGameObject::AddChildObj(CGameObject * _pChildObj)
{
	// 순환체크
	if (IsAncestor(_pChildObj))
		return RET_FAILED;

	_pChildObj->ClearParent();
	_pChildObj->m_pParentObj = this;
	m_listChildObj.push_back(_pChildObj);
	return RET_SUCCESS;
}

CGameObject* CGameObject::FindChildObjByTag(const wstring& _strTag)
{
	list<CGameObject*>::iterator iter = m_listChildObj.begin();

	for (; iter != m_listChildObj.end(); ++iter)
	{
		if ((*iter)->GetTag() == _strTag)
		{
			return (*iter);
		}
	}
	return NULL;
}

bool CGameObject::IsAncestor(CGameObject * _pObj)
{
	/*
	// 재귀적 호출
	CGameObject* pParentObj = this;
	if (NULL == pParentObj)
	return false;

	if (pParentObj == _pObj)
	return true;

	pParentObj = pParentObj->GetParentObj();
	return pParentObj->IsAncestor(_pObj);
	*/

	// 반복문
	CGameObject* pParentObj = this;
	list<CGameObject*> listParents;

	while (pParentObj)
	{
		listParents.push_back(pParentObj);
		pParentObj = pParentObj->GetParentObj();
	}

	list<CGameObject*>::iterator iter = listParents.begin();
	for (; iter != listParents.end(); ++iter)
	{
		if ((*iter) == _pObj)
			return true;
	}

	return false;
}
void CGameObject::ClearParent()
{
	if (NULL == m_pParentObj)
	{
		// 부모 게임오브젝트가 자식으로 들어가는 상황이 생길 때(레이어에 부모게임오브젝트라고 알고 있다), 그 해당 부모 게임오브젝트를 레이어 선언된 곳에서 뺴줘야한다.
		CLayer* pCurLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(m_strLayerName);
		if (NULL != pCurLayer)
		{
			pCurLayer->EraseParentThisObj(this);
		}
		return;
	}

	list<CGameObject*>& listChildObj = m_pParentObj->m_listChildObj;

	list<CGameObject*>::iterator iter = listChildObj.begin();
	for (; iter != listChildObj.end(); ++iter)
	{
		if ((*iter) == this)
		{
			listChildObj.erase(iter);
			break;
		}
	}
	m_pParentObj = NULL;
}

void CGameObject::AddComponent(CComponent* _pCom, ID<CScript>)
{
#ifdef _EXTREME_TOOL
	SetScriptCheck(true);
#endif

	m_listScript.push_back((CScript*)_pCom);
	_pCom->SetGameObject(this);
}

void CGameObject::SubComponent(ID<CScript>)
{
	Safe_Delete_List(m_listScript);
#ifdef _EXTREME_TOOL
	SetScriptCheck(true);
#endif
}

void CGameObject::SubComponent(ID<CScript>,const int _iIDx)
{
	list<CScript*>::iterator iter = m_listScript.begin();

	for (int i = 0; iter != m_listScript.end(); ++i,++iter)
	{
		if (_iIDx == i)
		{
			SAFE_DELETE(*iter);
			iter = m_listScript.erase(iter);
#ifdef _EXTREME_TOOL
			SetScriptCheck(true);
#endif
			break;
		}
	}
}


void CGameObject::AddComponent(COMPONENT_TYPE _eType)
{
	switch (_eType)
	{
	case COMPONENT_TYPE::TRANSFORM:
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM])
		{
			m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM] = new CTransform;
			m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]->SetGameObject(this);
		}
		break;
	case COMPONENT_TYPE::MESHRENDER:
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER])
		{
			m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER] = new CMeshRender;
			m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]->SetGameObject(this);
		}
		break;
	case COMPONENT_TYPE::COLLIDER_2D:
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER])
		{
			m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER] = new CCollider_2D;
			m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER]->SetGameObject(this);
		}
		break;
	case COMPONENT_TYPE::COLLIDER_3D:
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER])
		{
			//m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER] = new CCollider_3D;
			//m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER]->SetGameObject(this);
		}
		break;
	case COMPONENT_TYPE::ANIMATOR:
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR])
		{
			m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR] = new CAnimator;
			m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR]->SetGameObject(this);
		}
		break;
	case COMPONENT_TYPE::CAMERA:
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::CAMERA])
		{
			m_arrCom[(UINT)COMPONENT_TYPE::CAMERA] = new CCamera;
			m_arrCom[(UINT)COMPONENT_TYPE::CAMERA]->SetGameObject(this);
		}
		break;
	case COMPONENT_TYPE::END:
		break;
	default:
		break;
	}

}

void CGameObject::SetActiveIncludingChild(bool _bActive)
{
	list<CGameObject*> queue;
	queue.push_back(this);

	list<CGameObject*>::iterator iter = queue.begin();
	for (; iter != queue.end();)
	{
		queue.insert(queue.end(), (*iter)->GetChildList().begin(), (*iter)->GetChildList().end());
		(*iter)->SetActive(_bActive);
		iter = queue.erase(iter);
	}
}

void CGameObject::SetEnable(bool _bShow)
{
	m_bEnable = _bShow;
	CMeshRender* pMeshRender = MeshRender();
	if (NULL == pMeshRender) return;

	pMeshRender->SetEnable(_bShow);
}

void CGameObject::SetEnableIncludingChild(bool _bShow)
{
	list<CGameObject*> queue;
	queue.push_back(this);

	list<CGameObject*>::iterator iter = queue.begin();
	for (; iter != queue.end();)
	{
		queue.insert(queue.end(), (*iter)->GetChildList().begin(), (*iter)->GetChildList().end());
		(*iter)->SetEnable(_bShow);
		iter = queue.erase(iter);
	}
}

bool CGameObject::GetEnable()
{
	return m_bEnable;
	//CMeshRender* pMeshRender = MeshRender();
	//if (NULL == pMeshRender) return false;

	//return pMeshRender->GetEnable();
}

ULONG64 CGameObject::GetInstID()
{
	if (!MeshRender())
		return 0;

	return MeshRender()->GetInstID();
}
