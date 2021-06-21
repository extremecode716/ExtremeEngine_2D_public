#include "InstancingBuffer.h"

#include "Device.h"

CInstancingBuffer::CInstancingBuffer()
	: m_iMaxCount(10)
{
}

CInstancingBuffer::~CInstancingBuffer()
{
	SAFE_RELEASE(m_pInstancingBuffer);
}

void CInstancingBuffer::init()
{
	D3D11_BUFFER_DESC tDesc = {};

	tDesc.ByteWidth = sizeof(tInstancingData) * m_iMaxCount;
	tDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tDesc.Usage = D3D11_USAGE_DYNAMIC;
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (FAILED(DEVICE->CreateBuffer(&tDesc, NULL, &m_pInstancingBuffer)))
		assert(NULL);
}

void CInstancingBuffer::SetData()
{
	if (m_vecData.size() > m_iMaxCount)
	{
		Resize(m_vecData.size());
	}

	D3D11_MAPPED_SUBRESOURCE tMap = {};

	CONTEXT->Map(m_pInstancingBuffer, NULL, D3D11_MAP_WRITE_DISCARD, 0, &tMap);
	memcpy(tMap.pData, &m_vecData[0], sizeof(tInstancingData) * m_vecData.size());
	CONTEXT->Unmap(m_pInstancingBuffer, 0);
}

void CInstancingBuffer::Resize(UINT _iCount)
{
	SAFE_RELEASE(m_pInstancingBuffer);

	m_iMaxCount = _iCount;

	D3D11_BUFFER_DESC tDesc = {};

	tDesc.ByteWidth = sizeof(tInstancingData) * m_iMaxCount;
	tDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tDesc.Usage = D3D11_USAGE_DYNAMIC;
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (FAILED(DEVICE->CreateBuffer(&tDesc, NULL, &m_pInstancingBuffer)))
		assert(NULL);
}
