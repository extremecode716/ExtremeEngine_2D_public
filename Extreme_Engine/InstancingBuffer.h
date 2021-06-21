#pragma once

#include "global.h"

struct tInstancingData
{
	Matrix matWorld;
	Matrix matWV;
	Matrix matWVP;
};

class CInstancingBuffer
{
	SINGLE(CInstancingBuffer);

private:
	ID3D11Buffer*			m_pInstancingBuffer;
	UINT					m_iMaxCount;
	vector<tInstancingData>	m_vecData;

public:
	void init();
	void Clear() { m_vecData.clear(); }
	void AddInstancingData(tInstancingData& _tData) { m_vecData.push_back(_tData); }
	void SetData();
	UINT GetInstanceCount() { return m_vecData.size(); }
	ID3D11Buffer* GetBuffer() { return m_pInstancingBuffer; }

private:
	void Resize(UINT _iCount);
};

