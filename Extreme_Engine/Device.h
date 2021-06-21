#pragma once

#include "global.h"

class CDevice
{
	SINGLE(CDevice);
private:
	HWND					m_hWnd;			// ��ġ ��� ������
	bool					m_bWindow;		// â ���

	ID3D11Device*			m_pDevice;		// ����̽� - memory
	ID3D11DeviceContext*	m_pContext;		// ���ؽ�Ʈ - rendering

	IDXGISwapChain*			m_pSwapChain;	// ���� ü��
	ID3D11RenderTargetView*	m_pTargetView;			// ���� Ÿ�� ��
	ID3D11DepthStencilView* m_pDepthStencilView;    // ���� ���ٽ� ��
	ID3D11Texture2D*		m_pDepthStencilTex;     // ���� ���ٽ� �ؽ�Ʈ

	UINT					m_iMSLev;				// ��Ƽ ���ø� ����
	float					m_fCol[4];				// �ʱ�ȭ �÷�

	// �������
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

