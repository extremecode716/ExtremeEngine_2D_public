#include "DepthStencilState.h"

#include "Device.h"


CDepthStencilState::CDepthStencilState()
	: m_pState(NULL)
{
}


CDepthStencilState::~CDepthStencilState()
{
	SAFE_RELEASE(m_pState);
}

CDepthStencilState * CDepthStencilState::Create(bool _bDepthEnable
	, D3D11_DEPTH_WRITE_MASK _eMask
	, D3D11_COMPARISON_FUNC _eFunc
	, bool _bStencilEnable
	, D3D11_DEPTH_STENCILOP_DESC _front
	, D3D11_DEPTH_STENCILOP_DESC _back
	, UINT _iStencilReadMask
	, UINT _iStencilWriteMask)
{
	D3D11_DEPTH_STENCIL_DESC tDesc = {};

	tDesc.DepthEnable = _bDepthEnable;
	tDesc.DepthWriteMask = _eMask;
	tDesc.DepthFunc = _eFunc;
	tDesc.StencilEnable = _bStencilEnable;
	tDesc.StencilReadMask = _iStencilReadMask;
	tDesc.StencilWriteMask = _iStencilWriteMask;
	tDesc.FrontFace = _front;
	tDesc.BackFace = _back;

	ID3D11DepthStencilState* pState = NULL;
	if (FAILED(DEVICE->CreateDepthStencilState(&tDesc, &pState)))
	{
		assert(NULL);
	}

	CDepthStencilState* pDepthState = new CDepthStencilState;

	pDepthState->m_tDesc = tDesc;
	pDepthState->m_pState = pState;

	return pDepthState;
}

void CDepthStencilState::UpdateData()
{
	CONTEXT->OMSetDepthStencilState(m_pState, 0);
}

