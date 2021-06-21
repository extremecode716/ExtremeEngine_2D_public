#include "ShaderMgr.h"

#include "PathMgr.h"
#include "Shader.h"
#include "Sampler.h"
#include "BlendState.h"
#include "DepthStencilState.h"

CShaderMgr::CShaderMgr()
{
}

CShaderMgr::~CShaderMgr()
{
	Safe_Delete_Map(m_mapDepthStencilState);
	Safe_Delete_Map(m_mapBlendState);
	Safe_Delete_Map(m_mapSampler);
	Safe_Delete_Map(m_mapShader);
}

void CShaderMgr::init()
{
	CreateSampler();
	CreateBlendState();
	CreateDepthStencilState();
	CreateShader();
}

void CShaderMgr::CreateSampler()
{
	//================
	// Default Sampler
	//================
	CSampler* pSampler = CSampler::Create(D3D11_FILTER_ANISOTROPIC
		, D3D11_TEXTURE_ADDRESS_WRAP
		, D3D11_TEXTURE_ADDRESS_WRAP
		, 0);

	AddSampler(L"DefaultSampler", pSampler);
}

void CShaderMgr::CreateShader()
{
	//===============
	// Color Shader
	//===============	
	CShader* pShader = new CShader;

	wstring strPath = CPathMgr::GetResPath();
	strPath += L"Shader\\Standard.fx";

	pShader->CreateVertexShader(strPath, "VS_Color", 5, 0);
	pShader->CreatePixelShader(strPath, "PS_Color", 5, 0);
	pShader->SetBlendState(FindBlendState(L"AlphaBlend"));
	pShader->SetDepthStencilState(FindDepthStencilState(L"LESS_EQUAL"));
	CShaderMgr::GetInst()->AddShader(L"ColorShader", pShader);

	//===============
	// Texture Shader
	//===============	
	pShader = new CShader;

	strPath = CPathMgr::GetResPath();
	strPath += L"Shader\\Standard.fx";

	pShader->CreateVertexShader(strPath, "VS_Tex", 5, 0);
	pShader->CreatePixelShader(strPath, "PS_Tex", 5, 0);
	pShader->AddSampler(FindSampler(L"DefaultSampler"), (UINT)SHADER_TYPE::ST_PIXEL);

	pShader->AddShaderParam(SHADER_PARAM::SP_FLOAT_0, (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->AddShaderParam(SHADER_PARAM::SP_TEX_0, (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->SetBlendState(FindBlendState(L"AlphaBlend"));
	pShader->SetDepthStencilState(FindDepthStencilState(L"LESS_EQUAL"));


	CShaderMgr::GetInst()->AddShader(L"TexShader", pShader);

	//===============
	// Collider Shader
	//===============	
	pShader = new CShader;

	strPath = CPathMgr::GetResPath();
	strPath += L"Shader\\Standard.fx";

	pShader->CreateVertexShader(strPath, "VS_Collider", 5, 0);
	pShader->CreatePixelShader(strPath, "PS_Collider", 5, 0);
	pShader->SetBlendState(FindBlendState(L"AlphaBlend"));
	pShader->SetDepthStencilState(FindDepthStencilState(L"LESS_EQUAL"));
	pShader->AddShaderParam(SHADER_PARAM::SP_INT_0, (UINT)SHADER_TYPE::ST_PIXEL);


	CShaderMgr::GetInst()->AddShader(L"ColliderShader", pShader);

	//===============
	// Split 2D Shader
	//===============	
	pShader = new CShader;

	strPath = CPathMgr::GetResPath();
	strPath += L"Shader\\Standard.fx";

	pShader->CreateVertexShader(strPath, "VS_SPLIT_2D", 5, 0);
	pShader->CreatePixelShader(strPath, "PS_SPLIT_2D", 5, 0);

	pShader->AddSampler(FindSampler(L"DefaultSampler"), (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->SetBlendState(FindBlendState(L"AlphaBlend"));
	pShader->SetDepthStencilState(FindDepthStencilState(L"LESS_EQUAL"));

	pShader->AddShaderParam(SHADER_PARAM::SP_TEX_0, (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->AddShaderParam(SHADER_PARAM::SP_VEC4_0, (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->AddShaderParam(SHADER_PARAM::SP_INT_0, (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->AddShaderParam(SHADER_PARAM::SP_VEC4_1, (UINT)SHADER_TYPE::ST_PIXEL);

	CShaderMgr::GetInst()->AddShader(L"Split2DShader", pShader);


	//===============
	// Damage 2D Shader
	//===============	
	pShader = new CShader;

	strPath = CPathMgr::GetResPath();
	strPath += L"Shader\\Standard.fx";

	pShader->CreateVertexShader(strPath, "VS_DAMAGE_2D", 5, 0);
	pShader->CreatePixelShader(strPath, "PS_DAMAGE_2D", 5, 0);

	pShader->AddSampler(FindSampler(L"DefaultSampler"), (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->SetBlendState(FindBlendState(L"AlphaBlend"));
	pShader->SetDepthStencilState(FindDepthStencilState(L"LESS_EQUAL"));

	pShader->AddShaderParam(SHADER_PARAM::SP_TEX_0, (UINT)SHADER_TYPE::ST_PIXEL);  // TEX
	pShader->AddShaderParam(SHADER_PARAM::SP_VEC4_0, (UINT)SHADER_TYPE::ST_PIXEL); // UV
	pShader->AddShaderParam(SHADER_PARAM::SP_VEC4_1, (UINT)SHADER_TYPE::ST_PIXEL); // Color
	pShader->AddShaderParam(SHADER_PARAM::SP_FLOAT_0, (UINT)SHADER_TYPE::ST_PIXEL);// Alpha   
	pShader->AddShaderParam(SHADER_PARAM::SP_INT_0, (UINT)SHADER_TYPE::ST_PIXEL);  // Damage
	pShader->AddShaderParam(SHADER_PARAM::SP_INT_1, (UINT)SHADER_TYPE::ST_PIXEL);  // Damage Count

	CShaderMgr::GetInst()->AddShader(L"Damage2DShader", pShader);

	//=====================
	// Effect Std2D Shader (black background - EffectAlphaBlend)
	//=====================
	pShader = new CShader;

	strPath = CPathMgr::GetResPath();
	strPath += L"Shader\\Standard.fx";

	pShader->CreateVertexShader(strPath, "VS_Std_2D", 5, 0);
	pShader->CreatePixelShader(strPath, "PS_Std_2D", 5, 0);

	pShader->AddSampler(FindSampler(L"DefaultSampler"), (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->SetBlendState(FindBlendState(L"EffectAlphaBlend"));
	pShader->SetDepthStencilState(FindDepthStencilState(L"LESS_EQUAL"));

	pShader->AddShaderParam(SHADER_PARAM::SP_TEX_0, (UINT)SHADER_TYPE::ST_PIXEL);

	CShaderMgr::GetInst()->AddShader(L"EffectStd2DShader", pShader);


	//===============
	// Std 2D Shader
	//===============	
	pShader = new CShader;

	strPath = CPathMgr::GetResPath();
	strPath += L"Shader\\Standard.fx";

	pShader->CreateVertexShader(strPath, "VS_Std_2D", 5, 0);
	pShader->CreatePixelShader(strPath, "PS_Std_2D", 5, 0);

	pShader->AddSampler(FindSampler(L"DefaultSampler"), (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->SetBlendState(FindBlendState(L"AlphaBlend"));
	pShader->SetDepthStencilState(FindDepthStencilState(L"LESS_EQUAL"));

	pShader->AddShaderParam(SHADER_PARAM::SP_TEX_0, (UINT)SHADER_TYPE::ST_PIXEL);

	CShaderMgr::GetInst()->AddShader(L"Std2DShader", pShader);


	//=====================
	// Flow Std2D Shader
	//=====================
	pShader = new CShader;

	strPath = CPathMgr::GetResPath();
	strPath += L"Shader\\Standard.fx";

	pShader->CreateVertexShader(strPath, "VS_Std_2D", 5, 0);
	pShader->CreatePixelShader(strPath, "PS_Flow_Std_2D", 5, 0);

	pShader->AddSampler(FindSampler(L"DefaultSampler"), (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->SetBlendState(FindBlendState(L"AlphaBlend"));
	pShader->SetDepthStencilState(FindDepthStencilState(L"LESS_EQUAL"));

	pShader->AddShaderParam(SHADER_PARAM::SP_TEX_0, (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->AddShaderParam(SHADER_PARAM::SP_INT_0, (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->AddShaderParam(SHADER_PARAM::SP_FLOAT_0, (UINT)SHADER_TYPE::ST_PIXEL);

	CShaderMgr::GetInst()->AddShader(L"FlowStd2DShader", pShader);
}

void CShaderMgr::CreateBlendState()
{

	CBlendState* pState = new CBlendState;

	pState->SetMRT(false);

	D3D11_RENDER_TARGET_BLEND_DESC tTargetDesc = {};

	tTargetDesc.BlendEnable = true;
	tTargetDesc.BlendOp = D3D11_BLEND_OP_ADD;
	tTargetDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	tTargetDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	tTargetDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	tTargetDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
	tTargetDesc.DestBlendAlpha = D3D11_BLEND_ZERO;
	tTargetDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	pState->AddTargetBlendDesc(0, tTargetDesc);
	pState->CreateBlendState();

	AddBlendState(L"AlphaBlend", pState);

	///////////////////////////////////////////////////////////////////////
	pState = new CBlendState;

	pState->SetMRT(false);

	tTargetDesc = {};

	tTargetDesc.BlendEnable = true;
	tTargetDesc.BlendOp = D3D11_BLEND_OP_ADD;
	tTargetDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	tTargetDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	tTargetDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	tTargetDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
	tTargetDesc.DestBlendAlpha = D3D11_BLEND_ONE;
	tTargetDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	pState->AddTargetBlendDesc(0, tTargetDesc);
	pState->CreateBlendState();

	AddBlendState(L"EffectAlphaBlend", pState);


}

void CShaderMgr::CreateDepthStencilState()
{
	CDepthStencilState* pState = NULL;

	pState = CDepthStencilState::Create(true, D3D11_DEPTH_WRITE_MASK_ALL, D3D11_COMPARISON_LESS_EQUAL);

	AddDepthStencilState(L"LESS_EQUAL", pState);
}

int CShaderMgr::AddShader(const wstring& _strKey, CShader * _pShader)
{
	CShader* pShader = FindShader(_strKey);

	if (NULL != pShader)
		return RET_FAILED;

	_pShader->SetKey(_strKey);
	m_mapShader.insert(make_pair(_strKey, _pShader));

	return RET_SUCCESS;
}

int CShaderMgr::AddSampler(const wstring & _strKey, CSampler * _pSampler)
{
	CSampler* pShader = FindSampler(_strKey);

	if (NULL != pShader)
		return RET_FAILED;

	m_mapSampler.insert(make_pair(_strKey, _pSampler));
	return RET_SUCCESS;
}

int CShaderMgr::AddBlendState(const wstring & _strKey, CBlendState * _pState)
{
	CBlendState* pState = FindBlendState(_strKey);

	if (NULL != pState)
		return RET_FAILED;

	m_mapBlendState.insert(make_pair(_strKey, _pState));
	return RET_SUCCESS;
}

int CShaderMgr::AddDepthStencilState(const wstring & _strKey, CDepthStencilState * _pState)
{
	CDepthStencilState* pState = FindDepthStencilState(_strKey);

	if (NULL != pState)
		return RET_FAILED;

	m_mapDepthStencilState.insert(make_pair(_strKey, _pState));
	return RET_SUCCESS;
}

CShader * CShaderMgr::FindShader(const wstring& _strKey)
{
	map<wstring, CShader*>::iterator iter = m_mapShader.find(_strKey);

	if (iter == m_mapShader.end())
		return NULL;

	return iter->second;
}

CSampler * CShaderMgr::FindSampler(const wstring & _strKey)
{
	map<wstring, CSampler*>::iterator iter = m_mapSampler.find(_strKey);

	if (iter == m_mapSampler.end())
		return NULL;

	return iter->second;
}

CBlendState * CShaderMgr::FindBlendState(const wstring & _strKey)
{
	map<wstring, CBlendState*>::iterator iter = m_mapBlendState.find(_strKey);

	if (iter == m_mapBlendState.end())
		return NULL;

	return iter->second;
}

CDepthStencilState * CShaderMgr::FindDepthStencilState(const wstring & _strKey)
{
	map<wstring, CDepthStencilState*>::iterator iter = m_mapDepthStencilState.find(_strKey);

	if (iter == m_mapDepthStencilState.end())
		return NULL;

	return iter->second;
}
