#include "Shader.h"

#include "Device.h"
#include "Sampler.h"
#include "BlendState.h"
#include "DepthStencilState.h"

CShader::CShader()
	: m_pVSBlob(NULL)
	, m_pPSBlob(NULL)
	, m_pVSErr(NULL)
	, m_pPSErr(NULL)
	, m_pVS(NULL)
	, m_pPS(NULL)
	, m_pBlendState(NULL)
	, m_pDepthStencilState(NULL)
{
}

CShader::~CShader()
{
	SAFE_RELEASE(m_pVSBlob);
	SAFE_RELEASE(m_pVSInstBlob);
	SAFE_RELEASE(m_pPSBlob);

	SAFE_RELEASE(m_pVSErr);
	SAFE_RELEASE(m_pVSInstErr);
	SAFE_RELEASE(m_pPSErr);

	SAFE_RELEASE(m_pVS);
	SAFE_RELEASE(m_pVSInst);
	SAFE_RELEASE(m_pPS);
}

int CShader::CreateVertexShader(wstring _strFilePath, char * _pFuncName, int _iHigh, int _iRow)
{
	UINT iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D10_SHADER_DEBUG;
#endif

	char strVersion[255] = "";
	sprintf_s(strVersion, "vs_%d_%d", _iHigh, _iRow);

	if (FAILED(D3DCompileFromFile(_strFilePath.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _pFuncName, strVersion, iFlag, 0, &m_pVSBlob, &m_pVSErr)))
	{
		return RET_FAILED;
	}

	if (FAILED(DEVICE->CreateVertexShader(m_pVSBlob->GetBufferPointer(), m_pVSBlob->GetBufferSize()
		, NULL, &m_pVS)))
	{
		return RET_FAILED;
	}
	return RET_SUCCESS;
}

int CShader::CreateVertexShader_Instancing(wstring _strFilePath, char * _pFuncName, int _iHigh, int _iRow)
{
	UINT iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D10_SHADER_DEBUG;
#endif

	char strVersion[255] = "";
	sprintf_s(strVersion, "vs_%d_%d", _iHigh, _iRow);

	if (FAILED(D3DCompileFromFile(_strFilePath.c_str(), NULL
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _pFuncName, strVersion, iFlag, 0, &m_pVSInstBlob, &m_pVSInstErr)))
	{
		return RET_FAILED;
	}

	if (FAILED(DEVICE->CreateVertexShader(m_pVSInstBlob->GetBufferPointer()
		, m_pVSInstBlob->GetBufferSize()
		, NULL, &m_pVSInst)))
	{
		return RET_FAILED;
	}
	return RET_SUCCESS;
}

int CShader::CreatePixelShader(wstring _strFilePath, char * _pFuncName, int _iHigh, int _iRow)
{
	UINT iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D10_SHADER_DEBUG;
#endif

	char strVersion[255] = "";
	sprintf_s(strVersion, "ps_%d_%d", _iHigh, _iRow);

	if (FAILED(D3DCompileFromFile(_strFilePath.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _pFuncName, strVersion, iFlag, 0, &m_pPSBlob, &m_pPSErr)))
	{
		return RET_FAILED;
	}

	if (FAILED(DEVICE->CreatePixelShader(m_pPSBlob->GetBufferPointer(), m_pPSBlob->GetBufferSize()
		, NULL, &m_pPS)))
	{
		return RET_FAILED;
	}

	return RET_SUCCESS;
}

wstring CShader::GetVSErr()
{
	if (NULL != m_pVSErr)
	{
		string strErr = (char*)m_pVSErr->GetBufferPointer();
		return wstring(strErr.begin(), strErr.end());
	}
	return wstring();
}

wstring CShader::GetPSErr()
{
	if (NULL != m_pPSErr)
	{
		string strErr = (char*)m_pPSErr->GetBufferPointer();
		return wstring(strErr.begin(), strErr.end());
	}
	return wstring();
}

void CShader::UpdateData()
{
	CONTEXT->VSSetShader(m_pVS, NULL, NULL);
	CONTEXT->HSSetShader(NULL, NULL, NULL);
	CONTEXT->DSSetShader(NULL, NULL, NULL);
	CONTEXT->GSSetShader(NULL, NULL, NULL);
	CONTEXT->CSSetShader(NULL, NULL, NULL);
	CONTEXT->PSSetShader(m_pPS, NULL, NULL);

	for (UINT i = 0; i < m_vecSampler.size(); ++i)
	{
		m_vecSampler[i].pSampler->UpdateData(m_vecSampler[i].iTiming);
	}

	if (NULL != m_pBlendState)
		m_pBlendState->UpdateData();
	else
		CONTEXT->OMSetBlendState(NULL, NULL, 0xffffffff);

	if (NULL != m_pDepthStencilState)
		m_pDepthStencilState->UpdateData();
	else
		CONTEXT->OMSetDepthStencilState(NULL, NULL);
}

void CShader::UpdateDataInstancing()
{
	CONTEXT->VSSetShader(m_pVSInst, NULL, NULL);
	CONTEXT->HSSetShader(NULL, NULL, NULL);
	CONTEXT->DSSetShader(NULL, NULL, NULL);
	CONTEXT->GSSetShader(NULL, NULL, NULL);
	CONTEXT->CSSetShader(NULL, NULL, NULL);
	CONTEXT->PSSetShader(m_pPS, NULL, NULL);

	for (UINT i = 0; i < m_vecSampler.size(); ++i)
	{
		m_vecSampler[i].pSampler->UpdateData(m_vecSampler[i].iTiming);
	}

	if (NULL != m_pBlendState)
		m_pBlendState->UpdateData();
	else
		CONTEXT->OMSetBlendState(NULL, NULL, 0xffffffff);

	if (NULL != m_pDepthStencilState)
		m_pDepthStencilState->UpdateData();
	else
		CONTEXT->OMSetDepthStencilState(NULL, NULL);
}

void CShader::AddSampler(CSampler * _pSampler, UINT _iTiming)
{
	m_vecSampler.push_back(SAMPLER_INFO{ _pSampler, _iTiming });
}

void CShader::AddShaderParam(SHADER_PARAM _eParam, UINT _iTiming)
{
	tShaderParam param = {};
	param.eShaderParam = _eParam;
	param.iRegister = g_SPRegister[(UINT)_eParam];
	param.iTiming = _iTiming;

	m_vecShaderParam.push_back(param);
}
