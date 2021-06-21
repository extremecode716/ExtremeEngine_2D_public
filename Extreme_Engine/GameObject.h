#pragma once

#include "global.h"

#include "Component.h"

template<typename T>
struct ID { typedef T type; };

class CTransform;
class CMeshRender;
class CCamera;
class CScript;
class CCollider;
class CAnimator;


class CGameObject
{
private:
	bool                    m_bActive;
	bool					m_bEnable;
	wstring					m_strTag;
	wstring					m_strLayerName;
	CComponent*				m_arrCom[(UINT)COMPONENT_TYPE::END];
	list<CScript*>			m_listScript;

	CGameObject*			m_pParentObj;
	list<CGameObject*>		m_listChildObj;

	bool					m_bScriptEvent;

public:
	void awake();
	void start();

	int update();
	int lateupdate();
	int finalupdate(); // transform 
	void render();

	void Destroy();

public:
	void SetActive(bool _bActive) { m_bActive = _bActive; }
	void SetActiveIncludingChild(bool _bActive);
	void SetEnable(bool _bShow);
	void SetEnableIncludingChild(bool _bShow);
	bool GetActive() const { return m_bActive; }
	bool GetEnable();
	void SetTag(const wstring& _strTag) { m_strTag = _strTag; }
	const wstring& GetTag() { return m_strTag; }
	const wstring& GetLayerName() { return m_strLayerName; }
	void SetScriptCheck(bool _bCheck) { m_bScriptEvent = _bCheck; }
	bool GetScriptCheck() { return m_bScriptEvent; }
	ULONG64 GetInstID();

private:
	void SetLayerName(const wstring& _strLayerName) { m_strLayerName = _strLayerName; }

public:
	CTransform* Transform() { return (CTransform*)m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]; }
	CMeshRender* MeshRender() { return (CMeshRender*)m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]; }
	CAnimator* Animator() { return (CAnimator*)m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR]; }
	CCollider* Collider() { return (CCollider*)m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER]; }
	CCamera* Camera() { return (CCamera*)m_arrCom[(UINT)COMPONENT_TYPE::CAMERA]; }

	template<typename T>
	T* Script() { return (T*)GetComponent<T>(); }

	CGameObject* GetParentObj() { return m_pParentObj; }
	list<CGameObject*>& GetChildList() { return m_listChildObj; }
	list<CScript*>& GetScriptList() { return m_listScript; }

	CGameObject* FindChildObjByTag(const wstring& _strTag);


	bool IsMouseOn(const Vec2& _vWorldPos);

public:
	CComponent* GetComponent(COMPONENT_TYPE _eTYPE) { return m_arrCom[(UINT)_eTYPE]; }

	template<typename T>
	CComponent* GetComponent();

	template<typename T>
	void AddComponent(CComponent* _pCom)
	{
		AddComponent(_pCom, ID<T>());
	}
	void AddComponent(COMPONENT_TYPE _eType);

	template<typename T>
	void SubComponent()
	{
		SubComponent(ID<T>());
	}

	template<typename T>
	void SubComponent(const int _iIdx)
	{
		SubComponent(ID<T>(), _iIdx);
	}

public:
	int AddChildObj(CGameObject* _pChildObj);
	bool HasParent() { return (m_pParentObj == NULL) ? false : true; }
	void SetParentObj(CGameObject* _pParentObj) { m_pParentObj = _pParentObj; }
	void ClearParent();
	bool IsAncestor(CGameObject* _pObj);

private:
	template<typename T>
	void AddComponent(CComponent* _pCom, ID<T> _id);
	void AddComponent(CComponent* _pCom, ID<CScript>);

	template<typename T>
	void SubComponent(ID<T> _id);
	void SubComponent(ID<CScript>);
	// бщ Remove Script (SAFE_DELETE)
	void SubComponent(ID<CScript>,const int _iIDx);


public:
	CGameObject*	Clone() { return new CGameObject(*this); }

public:
	CGameObject();
	CGameObject(const CGameObject& _pOther);
	~CGameObject();

	friend class CLayer;
};

template<typename T>
CComponent* CGameObject::GetComponent()
{
	const type_info& info = typeid(T);

	if (info.hash_code() == typeid(CTransform).hash_code())
	{
		return m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM];
	}
	else if (info.hash_code() == typeid(CMeshRender).hash_code())
	{
		return m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER];
	}
	else if (info.hash_code() == typeid(CAnimator).hash_code())
	{
		return m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR];
	}
	else if (info.hash_code() == typeid(CCollider).hash_code())
	{
		return m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER];
	}
	else if (info.hash_code() == typeid(CCamera).hash_code())
	{
		return m_arrCom[(UINT)COMPONENT_TYPE::CAMERA];
	}
	else
	{
		list<CScript*>::iterator iter = m_listScript.begin();
		for (; iter != m_listScript.end(); ++iter)
		{
			if (dynamic_cast<T*>(*iter))
			{
				return *iter;
			}
		}
	}
	return NULL;
}

template<typename T>
inline void CGameObject::AddComponent(CComponent * _pCom, ID<T>)
{
	const type_info& info = typeid(T);

	if (info.hash_code() == typeid(CTransform).hash_code())
	{
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM])
		{
			m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM] = _pCom;
		}
		else
		{
			SAFE_DELETE(m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]);
			m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM] = _pCom;
		}
	}
	else if (info.hash_code() == typeid(CMeshRender).hash_code())
	{
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER])
		{
			m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER] = _pCom;
		}
		else
		{
			SAFE_DELETE(m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]);
			m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER] = _pCom;
		}
	}
	else if (info.hash_code() == typeid(CAnimator).hash_code())
	{
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR])
		{
			m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR] = _pCom;
		}
		else
		{
			SAFE_DELETE(m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR]);
			m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR] = _pCom;
		}
	}
	else if (info.hash_code() == typeid(CCollider).hash_code())
	{
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER])
		{
			m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER] = _pCom;
		}
		else
		{
			SAFE_DELETE(m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER]);
			m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER] = _pCom;
		}
	}
	else if (info.hash_code() == typeid(CCamera).hash_code())
	{
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::CAMERA])
		{
			m_arrCom[(UINT)COMPONENT_TYPE::CAMERA] = _pCom;
		}
		else
		{
			SAFE_DELETE(m_arrCom[(UINT)COMPONENT_TYPE::CAMERA]);
			m_arrCom[(UINT)COMPONENT_TYPE::CAMERA] = _pCom;
		}
	}

	_pCom->SetGameObject(this);
}

template<typename T>
inline void CGameObject::SubComponent(ID<T>)
{
	const type_info& info = typeid(T);

	if (info.hash_code() == typeid(CTransform).hash_code())
	{
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM])
		{
		}
		else
		{
			SAFE_DELETE(m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]);
		}
	}
	else if (info.hash_code() == typeid(CMeshRender).hash_code())
	{
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER])
		{
		}
		else
		{
			SAFE_DELETE(m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]);
		}
	}
	else if (info.hash_code() == typeid(CAnimator).hash_code())
	{
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR])
		{
		}
		else
		{
			SAFE_DELETE(m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR]);
		}
	}
	else if (info.hash_code() == typeid(CCollider).hash_code())
	{
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER])
		{
		}
		else
		{
			SAFE_DELETE(m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER]);
		}
	}
	else if (info.hash_code() == typeid(CCamera).hash_code())
	{
		if (NULL == m_arrCom[(UINT)COMPONENT_TYPE::CAMERA])
		{
		}
		else
		{
			SAFE_DELETE(m_arrCom[(UINT)COMPONENT_TYPE::CAMERA]);
		}
	}
}
