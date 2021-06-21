#include "Mesh.h"

#include "Device.h"

#include "Shader.h"
#include "ResMgr.h"
#include "InstancingBuffer.h"

CMesh::CMesh()
	: m_pVB(NULL)
	, m_iVtxCount(0)
	, m_iVtxSize(0)
	, m_eVtxUsage(D3D11_USAGE_DEFAULT)
	, m_pVtxSysMem(NULL)
	, m_pIB(NULL)
	, m_iIdxCount(0)
	, m_iIdxSize(0)
	, m_eIdxUsage(D3D11_USAGE_DEFAULT)
	, m_eIdxFormat(DXGI_FORMAT_UNKNOWN)
	, m_pIdxSysMem(NULL)
	, m_pLayout(NULL)
	, m_iLayoutOffset(0)
	, m_iInstancingOffset(0)
	, m_pRecentBlob(NULL)
{}

CMesh::~CMesh()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
	SAFE_RELEASE(m_pLayout);

	SAFE_DELETE(m_pVtxSysMem);
	SAFE_DELETE(m_pIdxSysMem);
}

CMesh * CMesh::Create(UINT _iVtxCount, UINT _iVtxSize, D3D11_USAGE _eVtxUsage
	, void * _pVtxSysMem, UINT _iIdxCount, UINT _iIdxSize, D3D11_USAGE _eIdxUsage
	, DXGI_FORMAT _eIdxFormat, void * _pIdxSysMem, D3D11_PRIMITIVE_TOPOLOGY _eTopology)
{
	D3D11_BUFFER_DESC tBufferDesc = {};

	tBufferDesc.ByteWidth = _iVtxSize * _iVtxCount;
	tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	tBufferDesc.Usage = _eVtxUsage;
	if (D3D11_USAGE_DYNAMIC == tBufferDesc.Usage)
		tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = _pVtxSysMem;

	ID3D11Buffer* pVB = NULL;
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, &pVB)))
	{
		return NULL;
	}

	tBufferDesc.ByteWidth = _iIdxSize * _iIdxCount;

	tBufferDesc.Usage = _eIdxUsage;
	if (D3D11_USAGE_DYNAMIC == tBufferDesc.Usage)
		tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	tSub.pSysMem = _pIdxSysMem;

	ID3D11Buffer* pIB = NULL;
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, &pIB)))
	{
		return NULL;
	}

	CMesh* pMesh = new CMesh;
	pMesh->m_pVB = pVB;
	pMesh->m_iVtxCount = _iVtxCount;
	pMesh->m_iVtxSize = _iVtxSize;
	pMesh->m_eVtxUsage = _eVtxUsage;

	pMesh->m_pIB = pIB;
	pMesh->m_iIdxCount = _iIdxCount;
	pMesh->m_iIdxSize = _iIdxSize;
	pMesh->m_eIdxUsage = _eIdxUsage;
	pMesh->m_eIdxFormat = _eIdxFormat;

	pMesh->m_eTopology = _eTopology;

	pMesh->SetVtxSysMem(_pVtxSysMem, _iVtxSize, _iVtxCount);
	pMesh->SetIdxSysMem(_pIdxSysMem, _iIdxSize, _iIdxCount);

	return pMesh;
}

void CMesh::SetVtxSysMem(void * _pVtxSysMem, UINT _iVtxSize, UINT _iVtxCount)
{
	SAFE_DELETE(m_pVtxSysMem);

	m_iVtxCount = _iVtxCount;
	m_iVtxSize = _iVtxSize;

	m_pVtxSysMem = malloc(_iVtxSize * _iVtxCount);
	memcpy(m_pVtxSysMem, _pVtxSysMem, _iVtxSize * _iVtxCount);
}

void CMesh::SetIdxSysMem(void * _pIdxSysMem, UINT _iIdxSize, UINT _iIdxCount)
{
	SAFE_DELETE(m_pIdxSysMem);

	m_iIdxCount = _iIdxCount;
	m_iIdxSize = _iIdxSize;

	m_pIdxSysMem = malloc(_iIdxSize * _iIdxCount);
	memcpy(m_pVtxSysMem, m_pIdxSysMem, _iIdxSize * _iIdxCount);
}

void CMesh::AddLayoutDesc(char * _pSemanticName, int _iSemanticIdx, DXGI_FORMAT _eFormat, 
	int _iInputSlot, int _iInstancing, D3D11_INPUT_CLASSIFICATION _eClass)
{
	D3D11_INPUT_ELEMENT_DESC tDesc = {};

	tDesc.SemanticName = _pSemanticName;
	tDesc.SemanticIndex = _iSemanticIdx; // 같은 종류의 시멘틱에 대해서 증가하는 인덱스
	tDesc.Format = _eFormat;
	tDesc.InputSlot = _iInputSlot; // 0 ~ 15 사이의 값
	tDesc.InputSlotClass = _eClass;
	tDesc.InstanceDataStepRate = _iInstancing; // 인스턴싱

	if (0 == _iInputSlot)
	{
		tDesc.AlignedByteOffset = m_iLayoutOffset;
		m_iLayoutOffset += GetSizeofFormat(_eFormat);
	}
	else
	{
		tDesc.AlignedByteOffset = m_iInstancingOffset;
		m_iInstancingOffset += GetSizeofFormat(_eFormat);
	}

	m_vecLayoutDesc.push_back(tDesc);
}

int CMesh::SetLayout(ID3DBlob* _pVSBlob)
{
	if (_pVSBlob == m_pRecentBlob)
		return RET_SUCCESS;

	m_pRecentBlob = _pVSBlob;

	SAFE_RELEASE(m_pLayout);

	if (FAILED(DEVICE->CreateInputLayout(&m_vecLayoutDesc[0], m_vecLayoutDesc.size()
		, m_pRecentBlob->GetBufferPointer()
		, m_pRecentBlob->GetBufferSize()
		, &m_pLayout)))
	{
		return RET_FAILED;
	}
	return RET_SUCCESS;
}

void CMesh::UpdateData()
{
	UINT iOffset = 0;          // 시작위치 (간격)
	UINT iStride = m_iVtxSize; // 간격
	// 순서대로 간격을 뛰는게 아님. 인덱스의 순서에 따라서 셋팅됨.

	CONTEXT->IASetVertexBuffers(0, 1, &m_pVB, &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(m_pIB, m_eIdxFormat, 0);
	CONTEXT->IASetPrimitiveTopology(m_eTopology);

	CONTEXT->IASetInputLayout(m_pLayout);
}

void CMesh::UpdateDataInstancing()
{
	ID3D11Buffer* arrBuffer[2] = { m_pVB	, CInstancingBuffer::GetInst()->GetBuffer() };
	UINT		  iStride[2] = { m_iVtxSize	, sizeof(tInstancingData) };
	UINT		  iOffset[2] = { 0, 0 };

	CONTEXT->IASetVertexBuffers(0, 2, arrBuffer, iStride, iOffset);
	CONTEXT->IASetIndexBuffer(m_pIB, m_eIdxFormat, 0);
	CONTEXT->IASetPrimitiveTopology(m_eTopology);

	CONTEXT->IASetInputLayout(m_pLayout);
}

void CMesh::render()
{
	CONTEXT->DrawIndexed(m_iIdxCount, 0, 0);
}

void CMesh::renderInstancing()
{
	CONTEXT->DrawIndexedInstanced(m_iIdxCount
		, CInstancingBuffer::GetInst()->GetInstanceCount()
		, 0, 0, 0);
}

//CRes * CMesh::Load(FILE * _pFile)
//{
//	wstring strKey = LoadWString(_pFile);
//	wstring strPath = LoadWString(_pFile);
//
//	return (CMesh*)CResMgr::GetInst()->Load<CMesh>(strKey, strPath);
//}
