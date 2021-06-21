#include "Device.h"



CDevice::CDevice()
	: m_hWnd(NULL), m_bWindow(false)
	, m_pDevice(NULL), m_pContext(NULL)
	, m_pSwapChain(NULL), m_pTargetView(NULL)
	, m_pDepthStencilView(NULL), m_pDepthStencilTex(NULL)
	, m_iMSLev(4), m_fCol{}
{
}

CDevice::~CDevice()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pContext);

	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pTargetView);

	SAFE_RELEASE(m_pDepthStencilTex);
	SAFE_RELEASE(m_pDepthStencilView);

	map<wstring, CBUFFER>::iterator iter = m_mapConstBuffer.begin();
	for (; iter != m_mapConstBuffer.end(); ++iter)
	{
		SAFE_RELEASE(iter->second.pBuffer);
	}

	for (int i = 0; i < (UINT)RASTERIZE_TYPE::RT_END; ++i)
	{
		SAFE_RELEASE(m_arrRasterizer[i]);
	}
}

int CDevice::init(HWND _hWnd, bool _bWindow)
{
	m_hWnd = _hWnd;
	m_bWindow = _bWindow;

	int iFlag = 0;
#ifdef _DEBUG
	iFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL eFeatureLv = (D3D_FEATURE_LEVEL)0;

	if (FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE
		, NULL, iFlag, 0, 0, D3D11_SDK_VERSION, &m_pDevice, &eFeatureLv, &m_pContext)))
	{
		return RET_FAILED;
	}

	// ��Ƽ���� üũ
	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_iMSLev);
	if (0 > m_iMSLev)
	{
		return RET_FAILED;
	}

	// ���� ü�� ����
	if (FAILED(CreateSwapChain()))
	{
		return RET_FAILED;
	}

	// RenderTargetView, DepthStencilView
	if (FAILED(CreateView()))
	{
		return RET_FAILED;
	}

	// View Port ����
	D3D11_VIEWPORT tViewPortDesc = {};

	tViewPortDesc.Width = WINSIZE_X;
	tViewPortDesc.Height = WINSIZE_Y;

	tViewPortDesc.MinDepth = 0;
	tViewPortDesc.MaxDepth = 1;

	// �»��
	tViewPortDesc.TopLeftX = 0;
	tViewPortDesc.TopLeftY = 0;

	m_pContext->RSSetViewports(1, &tViewPortDesc);

	// Rasterizer state
	CreateRasterizerState();

	return RET_SUCCESS;
}

int CDevice::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC tDesc = {};

	tDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tDesc.BufferDesc.Width = WINSIZE_X;
	tDesc.BufferDesc.Height = WINSIZE_Y;

	tDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// ȭ�� ���ŷ�
	tDesc.BufferDesc.RefreshRate.Numerator = 60;
	tDesc.BufferDesc.RefreshRate.Denominator = 1;

	// ���� �뵵 ����
	tDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// â��� ����
	tDesc.OutputWindow = m_hWnd;
	tDesc.Windowed = m_bWindow;

	// ��Ƽ ����
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;

	// ��� ���Ŀ� ���۳��� ������ �ʿ� ����
	tDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// �߰� ���� ����
	tDesc.BufferCount = 1;

	IDXGIDevice* pDXGIDevice = NULL;
	IDXGIAdapter* pAdapter = NULL;
	IDXGIFactory* pFactory = NULL;

	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pAdapter);
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);


	if (FAILED(pFactory->CreateSwapChain(m_pDevice, &tDesc, &m_pSwapChain)))
	{
		return RET_FAILED;
	}

	SAFE_RELEASE(pDXGIDevice);
	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);

	return RET_SUCCESS;
}

int CDevice::CreateView()
{
	ID3D11Texture2D*	pBackBuffer = NULL;

	// �����Ǿ��ִ� ���� ���
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	SAFE_RELEASE(pBackBuffer);

	m_pDevice->CreateRenderTargetView(pBackBuffer, 0, &m_pTargetView);

	// Depth Stencil Texture
	D3D11_TEXTURE2D_DESC tDesc = {};

	tDesc.Width = WINSIZE_X;
	tDesc.Height = WINSIZE_Y;

	tDesc.MipLevels = 1;
	tDesc.ArraySize = 1;
	tDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;

	tDesc.Usage = D3D11_USAGE_DEFAULT;
	tDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	if (FAILED(m_pDevice->CreateTexture2D(&tDesc, 0, &m_pDepthStencilTex)))
	{
		return RET_FAILED;
	}

	if (FAILED(m_pDevice->CreateDepthStencilView(m_pDepthStencilTex, 0, &m_pDepthStencilView)))
	{
		return RET_FAILED;
	}

	m_pContext->OMSetRenderTargets(1, &m_pTargetView, m_pDepthStencilView);

	return RET_SUCCESS;
}

int CDevice::CreateRasterizerState()
{
	m_arrRasterizer[(UINT)RASTERIZE_TYPE::RT_BACK] = NULL;

	D3D11_RASTERIZER_DESC tDesc = {};

	tDesc.FillMode = D3D11_FILL_WIREFRAME;
	tDesc.CullMode = D3D11_CULL_NONE;
	tDesc.DepthClipEnable = true;

	m_pDevice->CreateRasterizerState(&tDesc, &m_arrRasterizer[(UINT)RASTERIZE_TYPE::RT_WIREFRAME]);

	tDesc.FillMode = D3D11_FILL_SOLID;
	tDesc.CullMode = D3D11_CULL_FRONT;
	tDesc.DepthClipEnable = true; // ���� ���۸� ����ϰڴ�.

	m_pDevice->CreateRasterizerState(&tDesc, &m_arrRasterizer[(UINT)RASTERIZE_TYPE::RT_FRONT]);

	tDesc.FillMode = D3D11_FILL_SOLID;
	tDesc.CullMode = D3D11_CULL_NONE;
	tDesc.DepthClipEnable = true;

	m_pDevice->CreateRasterizerState(&tDesc, &m_arrRasterizer[(UINT)RASTERIZE_TYPE::RT_NONE]);
	return 0;
}

const CBUFFER * CDevice::FindConstBuffer(const wstring & _strKey)
{
	map<wstring, CBUFFER>::iterator iter = m_mapConstBuffer.find(_strKey);

	if (iter == m_mapConstBuffer.end())
		return NULL;

	return &iter->second;
}

int CDevice::CreateConstBuffer(const wstring & _strKey, UINT _iSize, D3D11_USAGE _eUsage, UINT _iRegister)
{
	CBUFFER buffer = {};

	D3D11_BUFFER_DESC tBufferDesc = {};

	tBufferDesc.ByteWidth = _iSize;
	tBufferDesc.Usage = _eUsage;
	tBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (tBufferDesc.Usage == D3D11_USAGE_DYNAMIC)
		tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, NULL, &buffer.pBuffer)))
	{
		return RET_FAILED;
	}

	buffer.iRegister = _iRegister;
	buffer.iSize = _iSize;

	m_mapConstBuffer.insert(make_pair(_strKey, buffer));

	return 0;
}
