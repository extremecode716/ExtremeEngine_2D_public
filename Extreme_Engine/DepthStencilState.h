#pragma once

#include "global.h"

class CDepthStencilState
{
private:
	ID3D11DepthStencilState*	m_pState;
	D3D11_DEPTH_STENCIL_DESC	m_tDesc;

public:
	static CDepthStencilState* Create(bool _bDepthEnable, D3D11_DEPTH_WRITE_MASK _eMask
		, D3D11_COMPARISON_FUNC _eFunc, bool _bStencilEnable = false
		, D3D11_DEPTH_STENCILOP_DESC _front = {}, D3D11_DEPTH_STENCILOP_DESC _back = {}
	, UINT _iStencilReadMask = 0, UINT _iStencilWriteMask = 0);

public:
	void UpdateData();

public:
	CDepthStencilState();
	~CDepthStencilState();
};

