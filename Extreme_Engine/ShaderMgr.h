#pragma once

#include "global.h"

class CShader;
class CSampler;
class CBlendState;
class CDepthStencilState;

class CShaderMgr
{
	SINGLE(CShaderMgr);

private:
	map<wstring, CShader*>				m_mapShader;
	map<wstring, CSampler*>				m_mapSampler;
	map<wstring, CBlendState*>			m_mapBlendState;
	map<wstring, CDepthStencilState*>	m_mapDepthStencilState;

public:
	void init();

public:
	CShader* FindShader(const wstring& _strKey);
	CSampler* FindSampler(const wstring& _strKey);
	CBlendState* FindBlendState(const wstring& _strKey);
	CDepthStencilState* FindDepthStencilState(const wstring& _strKey);

private:
	void CreateSampler();
	void CreateShader();
	void CreateBlendState();
	void CreateDepthStencilState();
	int AddShader(const wstring& _strKey, CShader* _pShader);
	int AddSampler(const wstring& _strKey, CSampler* _pSampler);
	int AddBlendState(const wstring& _strKey, CBlendState* _pState);
	int AddDepthStencilState(const wstring& _strKey, CDepthStencilState* _pState);
};

