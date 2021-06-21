#pragma once

#include "global.h"

class CSampler;
class CBlendState;
class CDepthStencilState;

struct SAMPLER_INFO
{
	CSampler*	pSampler;
	UINT		iTiming;
};

class CShader
{
private:
	ID3DBlob*				m_pVSBlob;
	ID3DBlob*				m_pVSInstBlob;
	ID3DBlob*				m_pPSBlob;

	ID3DBlob*				m_pVSErr;
	ID3DBlob*				m_pVSInstErr;
	ID3DBlob*				m_pPSErr;

	ID3D11VertexShader*		m_pVS;
	ID3D11VertexShader*		m_pVSInst;

	ID3D11PixelShader *		m_pPS;

	vector<SAMPLER_INFO>	m_vecSampler;
	vector<tShaderParam>    m_vecShaderParam;
	CBlendState*			m_pBlendState;
	CDepthStencilState*     m_pDepthStencilState;

	wstring					m_strKey;

public:
	wstring GetVSErr();
	wstring GetPSErr();
	ID3DBlob* GetVSBlob() { return m_pVSBlob; }
	ID3DBlob* GetVSInstBlob() { return m_pVSInstBlob; }
	ID3DBlob* GetPSBlob() { return m_pPSBlob; }
	void SetBlendState(CBlendState* _pState) { m_pBlendState = _pState; }
	void SetDepthStencilState(CDepthStencilState* _pState) { m_pDepthStencilState = _pState; }
	const wstring& GetKey() { return m_strKey; }
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }


public:
	int CreateVertexShader(wstring _strFilePath, char* _pFuncName, int _iHigh, int _iRow);
	int CreateVertexShader_Instancing(wstring _strFilePath, char* _pFuncName, int _iHigh, int _iRow);
	int CreatePixelShader(wstring _strFilePath, char* _pFuncName, int _iHigh, int _iRow);
	void UpdateData();
	void UpdateDataInstancing();

public:
	void AddSampler(CSampler* _pSampler, UINT _iTiming);
	void AddShaderParam(SHADER_PARAM _eParam, UINT _iTiming);
	vector<tShaderParam>& GetShaderParam() { return m_vecShaderParam; }

public:
	CShader();
	//CShader(const CShader& _pOther);
	~CShader();
};

