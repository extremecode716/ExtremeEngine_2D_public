#include "ResPtr.h"

#include "Mesh.h"
#include "Texture.h"
#include "Prefab.h"
#include "Material.h"
#include "Sound.h"

template class CResPtr<CMesh>;
template class CResPtr<CTexture>;
template class CResPtr<CPrefab>;
template class CResPtr<CMaterial>;
template class CResPtr<CSound>;
template class CResPtr<CRes>;

template<typename T>
CResPtr<T>::CResPtr()
	: m_pTarget(NULL)
{
}

template<typename T>
CResPtr<T>::CResPtr(const CResPtr & _Ptr)
	: m_pTarget(_Ptr.m_pTarget)
{
	if (NULL != m_pTarget)
	{
		m_pTarget->AddRef();
#ifdef _CONSOLE_REFCOUNT
		//cout <<g_refcount <<typeid(m_pTarget).name() << "\tRefCnt = " << m_pTarget->GetRefCnt() << "\tCResPtr<T>::CResPtr(const CResPtr & _Ptr)\t" << endl;
#endif
	}
}

template<typename T>
CResPtr<T>::CResPtr(T * _pTarget)
	: m_pTarget(_pTarget)
{
	if (NULL != m_pTarget)
	{
		m_pTarget->AddRef();
#ifdef _CONSOLE_REFCOUNT
		cout << ++g_refcount << typeid(m_pTarget).name() << "\tRefCnt = " << m_pTarget->GetRefCnt() << "\tCResPtr<T>::CResPtr(T * _pTarget)\t" << endl;
#endif
	}
}

template<typename T>
CResPtr<T>::~CResPtr()
{
	if (NULL != m_pTarget)
	{
		m_pTarget->SubRef();
#ifdef _CONSOLE_REFCOUNT
		//cout << --g_refcount <<"¼Ò¸ê"<< typeid(m_pTarget).name() << "\tRefCnt = " << m_pTarget->GetRefCnt() << "\tCResPtr<T>::~CResPtr()" << endl;
#endif
	}
}

template<typename T>
void CResPtr<T>::operator = (const CResPtr& _Ptr)
{
	if (m_pTarget == _Ptr.m_pTarget)
	{
		return;
	}

	if (NULL != m_pTarget)
		m_pTarget->SubRef();

	m_pTarget = _Ptr.m_pTarget;

	if (NULL != m_pTarget)
	{
		m_pTarget->AddRef();
#ifdef _CONSOLE_REFCOUNT
		cout << ++g_refcount << typeid(m_pTarget).name() << "\tRefCnt = " << m_pTarget->GetRefCnt() << "\tvoid CResPtr<T>::operator = (const CResPtr& _Ptr)\t" << endl;
#endif
	}
}

template<typename T>
void CResPtr<T>::operator = (T * _pTarget)
{
	if (m_pTarget == _pTarget)
	{
		return;
	}

	if (NULL != m_pTarget)
		m_pTarget->SubRef();

	m_pTarget = _pTarget;

	if (NULL != m_pTarget)
	{
		m_pTarget->AddRef();
#ifdef _CONSOLE_REFCOUNT
		cout << ++g_refcount << typeid(m_pTarget).name() << "\tRefCnt = " << m_pTarget->GetRefCnt() << "\tvoid CResPtr<T>::operator = (T * _pTarget)\t" << endl;
#endif
	}
}

template<typename T>
void CResPtr<T>::Delete()
{
	delete m_pTarget;
	m_pTarget = NULL;
}
