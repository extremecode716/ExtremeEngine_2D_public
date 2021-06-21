#include "Transform.h"

#include "Device.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

#include "GameObject.h"

tTransform	g_Transform;

CTransform::CTransform()
	: m_vPos(Vec3(0.f, 0.f, 0.f))
	, m_vScale(Vec3(1.f, 1.f, 1.f))
	, m_vRot(Vec3(0.f, 0.f, 0.f))
{
}

CTransform::~CTransform()
{
}

int CTransform::update()
{


	return RET_SUCCESS;
}

int CTransform::lateupdate()
{
	return RET_SUCCESS;
}

int CTransform::finalupdate()
{
	// 크 * 자 * 이 * 공부
	XMMATRIX matScale = XMMatrixScaling(m_vScale.x, m_vScale.y, m_vScale.z);

	XMMATRIX matTransform = XMMatrixTranslation(m_vPos.x, m_vPos.y, m_vPos.z);

	XMMATRIX matRot = XMMatrixRotationX(m_vRot.x);
	matRot *= XMMatrixRotationY(m_vRot.y);
	matRot *= XMMatrixRotationZ(m_vRot.z);

	m_matWorld = matScale * matRot * matTransform;

	CGameObject* pParentObj = GetParentObject();
	if (NULL != pParentObj)
	{
		m_matWorld *= pParentObj->Transform()->GetWorldMat();
	}


	return RET_SUCCESS;
}


void CTransform::UpdateData()
{
	g_Transform.matWorld = m_matWorld;
	g_Transform.matWorld = XMMatrixTranspose(g_Transform.matWorld);

	const CBUFFER* pBuffer = CDevice::GetInst()->FindConstBuffer(L"Transform");

	// 상수버퍼로 데이터 옮김
	D3D11_MAPPED_SUBRESOURCE tSub = {};

	CONTEXT->Map(pBuffer->pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &g_Transform, pBuffer->iSize);
	CONTEXT->Unmap(pBuffer->pBuffer, 0);


	CONTEXT->VSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
}

Vec3 CTransform::GetWorldPos()
{
	CGameObject* pParentObj = GetParentObject();
	Vec3 vWorldPos = m_vPos;

	if (NULL != pParentObj)
	{
		vWorldPos = XMVector3TransformCoord(m_vPos.Convert(), pParentObj->Transform()->GetWorldMat());
	}

	return vWorldPos;
}

Vec2 CTransform::GetWorld2DPos()
{
	CGameObject* pParentObj = GetParentObject();
	Vec3 vWorldPos = m_vPos;

	if (NULL != pParentObj)
	{
		vWorldPos = XMVector3TransformCoord(m_vPos.Convert(), pParentObj->Transform()->GetWorldMat());
	}

	return Vec2(vWorldPos.x, vWorldPos.y);

}

Vec3 CTransform::GetWorldScale()
{
	CGameObject* pParent = GetParentObject();
	Vec3 vWorldScale = m_vScale;
	while (pParent)
	{
		vWorldScale *= pParent->Transform()->GetLocalScale();
		pParent = pParent->GetParentObj();
	}

	return vWorldScale;
}

void CTransform::SetTransform(const UINT _iID, float _fValue)
{
	switch (_iID)
	{
		//Pos
	case 0:
		m_vPos = { _fValue ,m_vPos.y, m_vPos.z };
		break;
	case 1:
		m_vPos = { m_vPos.x ,_fValue, m_vPos.z };
		break;
	case 2:
		m_vPos = { m_vPos.x ,m_vPos.y, _fValue };
		break;

		// Rot
	case 3:
		m_vRot = { _fValue ,m_vRot.y, m_vRot.z };
		break;
	case 4:
		m_vRot = { m_vRot.x ,_fValue, m_vRot.z };
		break;
	case 5:
		m_vRot = { m_vRot.x ,m_vRot.y, _fValue };
		break;

		//Scale
	case 6:
		m_vScale = { _fValue ,m_vScale.y, m_vScale.z };
		break;
	case 7:
		m_vScale = { m_vScale.x ,_fValue, m_vScale.z };
		break;
	case 8:
		m_vScale = { m_vScale.x ,m_vScale.y, _fValue };
		break;
	default:
		break;
	}
}


void CTransform::Save(FILE * _pFile)
{
	UINT iType = (UINT)COMPONENT_TYPE::TRANSFORM;

	fwrite(&iType, sizeof(UINT), 1, _pFile);

	fwrite(&m_vPos, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vScale, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vRot, sizeof(Vec3), 1, _pFile);
}

void CTransform::Load(FILE * _pFile)
{
	fread(&m_vPos, sizeof(Vec3), 1, _pFile);
	fread(&m_vScale, sizeof(Vec3), 1, _pFile);
	fread(&m_vRot, sizeof(Vec3), 1, _pFile);
}
