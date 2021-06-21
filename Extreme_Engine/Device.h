#pragma once

#include "global.h"

class CDevice
{
	SINGLE(CDevice);
private:
	HWND					m_hWnd;			// 장치 출력 윈도우
	bool					m_bWindow;		// 창 모드

	ID3D11Device*			m_pDevice;		// 디바이스 - memory
	ID3D11DeviceContext*	m_pContext;		// 컨텍스트 - rendering

	IDXGISwapChain*			m_pSwapChain;	// 스왚 체인
	ID3D11RenderTargetView*	m_pTargetView;			// 랜더 타겟 뷰
	ID3D11DepthStencilView* m_pDepthStencilView;    // 뎁스 스텐실 뷰
	ID3D11Texture2D*		m_pDepthStencilTex;     // 뎁스 스텐실 텍스트

	UINT					m_iMSLev;				// 멀티 샘플링 레벨
	float					m_fCol[4];				// 초기화 컬러

	// 상수버퍼
	map<wstring, CBUFFER>	m_mapConstBuffer;
	ID3D11RasterizerState*  m_arrRasterizer[(UINT)RASTERIZE_TYPE::RT_END];

public:
	int init(HWND _hWnd, bool _bWindow);
	void SetClearColor(float _fCol[4]) { memcpy(m_fCol, _fCol, sizeof(float) * 4); }
	void ClearTarget()
	{
		m_pContext->ClearRenderTargetView(m_pTargetView, m_fCol);
		m_pContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	}
	void Present() { m_pSwapChain->Present(0, 0); }

	ID3D11Device* GetDevice() { return m_pDevice; }
	ID3D11DeviceContext* GetContext() { return m_pContext; }

private:
	int CreateSwapChain();
	int CreateView();
	int CreateRasterizerState();

public:
	const CBUFFER* FindConstBuffer(const wstring& _strKey);
	int CreateConstBuffer(const wstring& _strKey, UINT _iSize, D3D11_USAGE _eUsage, UINT _iRegister);
	void SetRasterizer(RASTERIZE_TYPE _eType) { m_pContext->RSSetState(m_arrRasterizer[(UINT)_eType]); }

};

