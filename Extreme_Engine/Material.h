#pragma once
#include "Res.h"

struct tShaderParam_EX : public tShaderParam
{
	void* pData;
};

class CShader;

class CMaterial :
	public CRes
{
private:
	CShader*				m_pShader;
	vector<tShaderParam_EX> m_vecParam;

public:
	void SetShader(CShader* _pShader);
	CShader* GetShader() { return m_pShader; }
	const vector<tShaderParam_EX>& GetVecParam() const { return m_vecParam; }

private:
	void ClearShaderParam();
	void AdjustShaderParam();
	void UpdateParam();

public:
	void SetData(SHADER_PARAM _eParam, void* _pData);
	void UpdateData();
	void UpdateDataInstancing();

public:
	virtual void Save(FILE* _pFile);
	static CRes* Load(FILE* _pFile);
	void LoadShaderParam(FILE* _pFile);
	virtual CMaterial* Clone() { return new CMaterial(*this); }

public:
	CMaterial();
	CMaterial(const CMaterial& _other);
	virtual ~CMaterial();
};

