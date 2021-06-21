#include "Component.h"

#include "GameObject.h"


CComponent::CComponent()
{
}


CComponent::~CComponent()
{
}

CGameObject * CComponent::GetParentObject()
{
	return m_pObj->GetParentObj();
}

CTransform * CComponent::Transform()
{
	return m_pObj->Transform();
}

CMeshRender * CComponent::MeshRender()
{
	return m_pObj->MeshRender();
}

CCollider * CComponent::Collider()
{
	return m_pObj->Collider();
}

CAnimator * CComponent::Animator()
{
	return m_pObj->Animator();
}

CCamera * CComponent::Camera()
{
	return m_pObj->Camera();
}
