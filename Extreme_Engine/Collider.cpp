#include "Collider.h"

#include "Transform.h"

#include "Device.h"

#include "GameObject.h"
#include "Script.h"

UINT CCollider::g_iColID = 0;

CCollider::CCollider()
	: m_iColID(g_iColID++)
	, m_bEnable(true)
	, m_iCollision(0)
	, m_vOffsetPos({0.f,0.f,0.f})
	, m_vOffsetScale({1.f,1.f,1.f})
	, m_bScale(true)
	, m_pMesh(NULL)
	, m_pMtrl(NULL)
{
}

CCollider::CCollider(const CCollider & _other)
	: m_iColID(g_iColID++)
	, m_bEnable(_other.m_bEnable)
	, m_pMesh(_other.m_pMesh)
	, m_pMtrl(_other.m_pMtrl)
	, m_iCollision(_other.m_iCollision)
	, m_vObjPos(_other.m_vObjPos)
	, m_vOffsetPos(_other.m_vOffsetPos)
	, m_vOffsetScale(_other.m_vOffsetScale)
	, m_matColliderWorld(_other.m_matColliderWorld)
	, m_bScale(_other.m_bScale)
{}

CCollider::~CCollider()
{
}

void CCollider::SetOffset(const UINT _iID, float _fValue)
{
	switch (_iID)
	{
		//OffsetPos
	case 0:
		m_vOffsetPos = { _fValue ,m_vOffsetPos.y, m_vOffsetPos.z };
		break;
	case 1:
		m_vOffsetPos = { m_vOffsetPos.x ,_fValue, m_vOffsetPos.z };
		break;
	case 2:
		m_vOffsetPos = { m_vOffsetPos.x ,m_vOffsetPos.y, _fValue };
		break;

		// OffsetSize
	case 3:
		m_vOffsetScale = { _fValue ,m_vOffsetScale.y, m_vOffsetScale.z };
		break;
	case 4:
		m_vOffsetScale = { m_vOffsetScale.x ,_fValue, m_vOffsetScale.z };
		break;
	case 5:
		m_vOffsetScale = { m_vOffsetScale.x ,m_vOffsetScale.y, _fValue };
		break;
	default:
		break;
	}
}

void CCollider::OnCollisionEnter(CCollider * _pOther)
{
	list<CScript*>& listScript = GetGameObject()->GetScriptList();
	list<CScript*>::iterator iter = listScript.begin();
	for (; iter != listScript.end(); ++iter)
	{
		(*iter)->OnCollisionEnter(_pOther);
	}
}

void CCollider::OnCollision(CCollider * _pOther)
{
	m_iCollision = 1;

	list<CScript*>& listScript = GetGameObject()->GetScriptList();
	list<CScript*>::iterator iter = listScript.begin();
	for (; iter != listScript.end(); ++iter)
	{
		(*iter)->OnCollision(_pOther);
	}
}

void CCollider::OnCollisionExit(CCollider * _pOther)
{
	m_iCollision = 0;
	list<CScript*>& listScript = GetGameObject()->GetScriptList();
	list<CScript*>::iterator iter = listScript.begin();
	for (; iter != listScript.end(); ++iter)
	{
		(*iter)->OnCollisionExit(_pOther);
	}
}

int CCollider::finalupdate()
{
	m_vObjPos = Transform()->GetWorldPos();
	// Collider 크 * 자(x) * 이동 * (행렬)
	if (!m_bScale)
	{
		Vec3 ObjScale = Transform()->GetWorldScale();
		ObjScale = m_vOffsetScale / ObjScale;
		m_matColliderWorld = XMMatrixScaling(ObjScale.x, ObjScale.y, ObjScale.z);
	}
	else
	{
		m_matColliderWorld = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
	}

	m_matColliderWorld *= XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);
	m_matColliderWorld *= Transform()->GetWorldMat();

	return RET_SUCCESS;
}

void CCollider::UpdateData()
{
	g_Transform.matWorld = m_matColliderWorld;
	g_Transform.matWorld = XMMatrixTranspose(g_Transform.matWorld);

	const CBUFFER* pBuffer = CDevice::GetInst()->FindConstBuffer(L"Transform");

	// 상수버퍼로 데이터 옮김
	D3D11_MAPPED_SUBRESOURCE tSub = {};

	CONTEXT->Map(pBuffer->pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &g_Transform, pBuffer->iSize);
	CONTEXT->Unmap(pBuffer->pBuffer, 0);


	CONTEXT->VSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
}

void CCollider::Save(FILE * _pFile)
{
	SaveResourceKey(m_pMesh.GetTarget(), _pFile);
	SaveResourceKey(m_pMtrl.GetTarget(), _pFile);

	fwrite(&m_vObjPos, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vOffsetPos, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vOffsetScale, sizeof(Vec3), 1, _pFile);
	fwrite(&m_bScale, 1, 1, _pFile);
}

void CCollider::Load(FILE * _pFile)
{
	wstring strKey;
	strKey = LoadResourceKey(_pFile);
	if (!strKey.empty())
		m_pMesh = (CMesh*)CResMgr::GetInst()->Load<CMesh>(strKey);

	strKey = LoadResourceKey(_pFile);
	if (!strKey.empty())
		m_pMtrl = CResMgr::GetInst()->FindMaterial(strKey);

	fread(&m_vObjPos, sizeof(Vec3), 1, _pFile);
	fread(&m_vOffsetPos, sizeof(Vec3), 1, _pFile);
	fread(&m_vOffsetScale, sizeof(Vec3), 1, _pFile);
	fread(&m_bScale, 1, 1, _pFile);
}
