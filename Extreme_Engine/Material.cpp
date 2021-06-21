#include "Material.h"

#include "Shader.h"
#include "Texture.h"
#include "Device.h"
#include "ShaderMgr.h"
#include "ResMgr.h"

UINT g_SPRegister[(UINT)SHADER_PARAM::SP_END]
{
	1,//SP_INT_0,
	1,//SP_INT_1,
	1,//SP_INT_2,
	1,//SP_INT_3,
	1,//SP_INT_END,
	2,//SP_FLOAT_0,
	2,//SP_FLOAT_1,
	2,//SP_FLOAT_2,
	2,//SP_FLOAT_3,
	2,//SP_FLOAT_END,
	3,//SP_VEC4_0,
	3,//SP_VEC4_1,
	3,//SP_VEC4_2,
	3,//SP_VEC4_3,
	3,//SP_VEC4_END,
	0,//SP_TEX_0,
	1,//SP_TEX_1,
	2,//SP_TEX_2,
	3,//SP_TEX_3,
	0,//SP_TEX_END,	
};

wchar_t* g_SPName[(UINT)SHADER_PARAM::SP_END]
{
	L"SP_INT_0"		,
	L"SP_INT_1"		,
	L"SP_INT_2"		,
	L"SP_INT_3"		,
	L"SP_INT_END"	,
	L"SP_FLOAT_0"	,
	L"SP_FLOAT_1"	,
	L"SP_FLOAT_2"	,
	L"SP_FLOAT_3"	,
	L"SP_FLOAT_END"	,
	L"SP_VEC4_0"	,
	L"SP_VEC4_1"	,
	L"SP_VEC4_2"	,
	L"SP_VEC4_3"	,
	L"SP_VEC4_END"	,
	L"SP_TEX_0"		,
	L"SP_TEX_1"		,
	L"SP_TEX_2"		,
	L"SP_TEX_3"		,
	L"SP_TEX_END"	,
};


CMaterial::CMaterial()
	: m_pShader(NULL)
{
}

CMaterial::CMaterial(const CMaterial & _other)
	:  m_pShader(_other.m_pShader)
	, m_vecParam(_other.m_vecParam)
{
	m_strKey = _other.m_strKey;
	m_strPath = _other.m_strPath;

	for (UINT i = 0; i < m_vecParam.size(); ++i)
	{
		switch (m_vecParam[i].eShaderParam)
		{
		case SHADER_PARAM::SP_INT_0:
		case SHADER_PARAM::SP_INT_1:
		case SHADER_PARAM::SP_INT_2:
		case SHADER_PARAM::SP_INT_3:
		{
			m_vecParam[i].pData = new int;
			memcpy(m_vecParam[i].pData, _other.m_vecParam[i].pData, sizeof(int));
		}
		break;
		case SHADER_PARAM::SP_FLOAT_0:
		case SHADER_PARAM::SP_FLOAT_1:
		case SHADER_PARAM::SP_FLOAT_2:
		case SHADER_PARAM::SP_FLOAT_3:
		{
			m_vecParam[i].pData = new float;
			memcpy(m_vecParam[i].pData, _other.m_vecParam[i].pData, sizeof(float));
		}
		break;
		case SHADER_PARAM::SP_VEC4_0:
		case SHADER_PARAM::SP_VEC4_1:
		case SHADER_PARAM::SP_VEC4_2:
		case SHADER_PARAM::SP_VEC4_3:
		{
			m_vecParam[i].pData = new Vec4;
			memcpy(m_vecParam[i].pData, _other.m_vecParam[i].pData, sizeof(Vec4));
		}
		break;
		case SHADER_PARAM::SP_TEX_0:
		case SHADER_PARAM::SP_TEX_1:
		case SHADER_PARAM::SP_TEX_2:
		case SHADER_PARAM::SP_TEX_3:
		{
			m_vecParam[i].pData = new void*;
			memcpy(m_vecParam[i].pData, _other.m_vecParam[i].pData, sizeof(void*));
		}
		break;
		}
	}
}

CMaterial::~CMaterial()
{
	ClearShaderParam();
}

void CMaterial::SetShader(CShader * _pShader)
{
	if (m_pShader == _pShader)
		return;

	m_pShader = _pShader;

	if (NULL != m_pShader)
	{
		ClearShaderParam();
		AdjustShaderParam();
	}
}

void CMaterial::ClearShaderParam()
{
	for (UINT i = 0; i < m_vecParam.size(); ++i)
	{
		SAFE_DELETE(m_vecParam[i].pData);
	}

	m_vecParam.clear();
}

void CMaterial::AdjustShaderParam()
{
	vector<tShaderParam>& vecParam = m_pShader->GetShaderParam();

	for (UINT i = 0; i < vecParam.size(); ++i)
	{
		tShaderParam_EX param;
		param.eShaderParam = vecParam[i].eShaderParam;
		param.iRegister = vecParam[i].iRegister;
		param.iTiming = vecParam[i].iTiming;


		switch (vecParam[i].eShaderParam)
		{
		case SHADER_PARAM::SP_INT_0:
		case SHADER_PARAM::SP_INT_1:
		case SHADER_PARAM::SP_INT_2:
		case SHADER_PARAM::SP_INT_3:
		{
			param.pData = new int;
			*((int*)param.pData) = 0;
		}
		break;
		case SHADER_PARAM::SP_FLOAT_0:
		case SHADER_PARAM::SP_FLOAT_1:
		case SHADER_PARAM::SP_FLOAT_2:
		case SHADER_PARAM::SP_FLOAT_3:
		{
			param.pData = new float;
			*((float*)param.pData) = 0.f;
		}
		break;
		case SHADER_PARAM::SP_VEC4_0:
		case SHADER_PARAM::SP_VEC4_1:
		case SHADER_PARAM::SP_VEC4_2:
		case SHADER_PARAM::SP_VEC4_3:
		{
			param.pData = new Vec4;
			*((Vec4*)param.pData) = Vec4(0.f, 0.f, 0.f, 0.f);
		}
		break;
		case SHADER_PARAM::SP_TEX_0:
		case SHADER_PARAM::SP_TEX_1:
		case SHADER_PARAM::SP_TEX_2:
		case SHADER_PARAM::SP_TEX_3:
		{
			/*param.pData = new void*;
			*((int*)param.pData) = NULL;*/
			param.pData = new CResPtr<CTexture>;
		}
		break;
		default:
			continue;
		}

		m_vecParam.push_back(param);
	}
}

void CMaterial::SetData(SHADER_PARAM _eParam, void * _pData)
{
	UINT idx = 0;
	bool bFind = false;
	for (; idx < m_vecParam.size(); ++idx)
	{
		if (m_vecParam[idx].eShaderParam == _eParam)
		{
			bFind = true;
			break;
		}
	}

	if (!bFind)
		return;


	switch (m_vecParam[idx].eShaderParam)
	{
	case SHADER_PARAM::SP_INT_0:
	case SHADER_PARAM::SP_INT_1:
	case SHADER_PARAM::SP_INT_2:
	case SHADER_PARAM::SP_INT_3:
	{
		*((int*)m_vecParam[idx].pData) = *((int*)_pData);
	}
	break;
	case SHADER_PARAM::SP_FLOAT_0:
	case SHADER_PARAM::SP_FLOAT_1:
	case SHADER_PARAM::SP_FLOAT_2:
	case SHADER_PARAM::SP_FLOAT_3:
	{
		*((float*)m_vecParam[idx].pData) = *((float*)_pData);
	}
	break;
	case SHADER_PARAM::SP_VEC4_0:
	case SHADER_PARAM::SP_VEC4_1:
	case SHADER_PARAM::SP_VEC4_2:
	case SHADER_PARAM::SP_VEC4_3:
	{
		*((Vec4*)m_vecParam[idx].pData) = *((Vec4*)_pData);
	}
	break;
	case SHADER_PARAM::SP_TEX_0:
	case SHADER_PARAM::SP_TEX_1:
	case SHADER_PARAM::SP_TEX_2:
	case SHADER_PARAM::SP_TEX_3:
	{
		*((CResPtr<CTexture>*)m_vecParam[idx].pData) = *((CTexture**)_pData);
	}
	break;
	default:
		break;
	}
}

void CMaterial::UpdateParam()
{
	int iArr[(UINT)SHADER_PARAM::SP_INT_END - (UINT)SHADER_PARAM::SP_INT_0] = {};
	float fArr[(UINT)SHADER_PARAM::SP_FLOAT_END - (UINT)SHADER_PARAM::SP_FLOAT_0] = {};
	Vec4 vecArr[(UINT)SHADER_PARAM::SP_VEC4_END - (UINT)SHADER_PARAM::SP_VEC4_0] = {};

	void* Arr[3] = { iArr , fArr , vecArr };

	for (UINT i = 0; i < m_vecParam.size(); ++i)
	{
		switch (m_vecParam[i].eShaderParam)
		{
		case SHADER_PARAM::SP_INT_0:
		case SHADER_PARAM::SP_INT_1:
		case SHADER_PARAM::SP_INT_2:
		case SHADER_PARAM::SP_INT_3:
			iArr[(UINT)m_vecParam[i].eShaderParam - (UINT)SHADER_PARAM::SP_INT_0] = *((int*)m_vecParam[i].pData);
			break;
		case SHADER_PARAM::SP_FLOAT_0:
		case SHADER_PARAM::SP_FLOAT_1:
		case SHADER_PARAM::SP_FLOAT_2:
		case SHADER_PARAM::SP_FLOAT_3:
			fArr[(UINT)m_vecParam[i].eShaderParam - (UINT)SHADER_PARAM::SP_FLOAT_0] = *((float*)m_vecParam[i].pData);
			break;
		case SHADER_PARAM::SP_VEC4_0:
		case SHADER_PARAM::SP_VEC4_1:
		case SHADER_PARAM::SP_VEC4_2:
		case SHADER_PARAM::SP_VEC4_3:
			vecArr[(UINT)m_vecParam[i].eShaderParam - (UINT)SHADER_PARAM::SP_VEC4_0] = *((Vec4*)m_vecParam[i].pData);
			break;
		case SHADER_PARAM::SP_TEX_0:
		case SHADER_PARAM::SP_TEX_1:
		case SHADER_PARAM::SP_TEX_2:
		case SHADER_PARAM::SP_TEX_3:
			if (NULL != (*(CTexture**)m_vecParam[i].pData))
			{
				(*((CTexture**)m_vecParam[i].pData))->UpdateData(m_vecParam[i].iRegister, m_vecParam[i].iTiming);
			}
			break;
		}
	}

	static const CBUFFER* arrConstBuffer[3] =
	{
		CDevice::GetInst()->FindConstBuffer(g_SPName[(UINT)SHADER_PARAM::SP_INT_END]),
		CDevice::GetInst()->FindConstBuffer(g_SPName[(UINT)SHADER_PARAM::SP_FLOAT_END]),
		CDevice::GetInst()->FindConstBuffer(g_SPName[(UINT)SHADER_PARAM::SP_VEC4_END])
	};

	for (int i = 0; i < 3; ++i)
	{
		D3D11_MAPPED_SUBRESOURCE tSub = {};

		CONTEXT->Map(arrConstBuffer[i]->pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
		memcpy(tSub.pData, Arr[i], arrConstBuffer[i]->iSize);
		CONTEXT->Unmap(arrConstBuffer[i]->pBuffer, 0);

		CONTEXT->VSSetConstantBuffers(arrConstBuffer[i]->iRegister, 1, &arrConstBuffer[i]->pBuffer);
		CONTEXT->HSSetConstantBuffers(arrConstBuffer[i]->iRegister, 1, &arrConstBuffer[i]->pBuffer);
		CONTEXT->DSSetConstantBuffers(arrConstBuffer[i]->iRegister, 1, &arrConstBuffer[i]->pBuffer);
		CONTEXT->GSSetConstantBuffers(arrConstBuffer[i]->iRegister, 1, &arrConstBuffer[i]->pBuffer);
		CONTEXT->CSSetConstantBuffers(arrConstBuffer[i]->iRegister, 1, &arrConstBuffer[i]->pBuffer);
		CONTEXT->PSSetConstantBuffers(arrConstBuffer[i]->iRegister, 1, &arrConstBuffer[i]->pBuffer);
	}
}

void CMaterial::UpdateData()
{
	if (NULL == m_pShader)
		assert(NULL);

	m_pShader->UpdateData();

	UpdateParam();
}

void CMaterial::UpdateDataInstancing()
{
	if (NULL == m_pShader)
		assert(NULL);

	m_pShader->UpdateDataInstancing();

	UpdateParam();
}

void CMaterial::Save(FILE * _pFile)
{
	CRes::Save(_pFile);

	// 참조 쉐이더 유무
	BYTE bShader = 0;
	if (NULL != m_pShader)
		bShader = 1;
	fwrite(&bShader, 1, 1, _pFile);

	if (NULL != m_pShader)
	{
		// Shader key값 저장
		SaveWString(m_pShader->GetKey(), _pFile);

		for (UINT i = 0; i < m_vecParam.size(); ++i)
		{
			switch (m_vecParam[i].eShaderParam)
			{
			case SHADER_PARAM::SP_INT_0:
			case SHADER_PARAM::SP_INT_1:
			case SHADER_PARAM::SP_INT_2:
			case SHADER_PARAM::SP_INT_3:
			{
				fwrite(m_vecParam[i].pData, sizeof(int), 1, _pFile);
			}
			break;
			case SHADER_PARAM::SP_FLOAT_0:
			case SHADER_PARAM::SP_FLOAT_1:
			case SHADER_PARAM::SP_FLOAT_2:
			case SHADER_PARAM::SP_FLOAT_3:
			{
				fwrite(m_vecParam[i].pData, sizeof(float), 1, _pFile);
			}
			break;
			case SHADER_PARAM::SP_VEC4_0:
			case SHADER_PARAM::SP_VEC4_1:
			case SHADER_PARAM::SP_VEC4_2:
			case SHADER_PARAM::SP_VEC4_3:
			{
				fwrite(m_vecParam[i].pData, sizeof(Vec4), 1, _pFile);
			}
			break;
			case SHADER_PARAM::SP_TEX_0:
			case SHADER_PARAM::SP_TEX_1:
			case SHADER_PARAM::SP_TEX_2:
			case SHADER_PARAM::SP_TEX_3:
			{
				CTexture* pTex = *((CTexture**)m_vecParam[i].pData);

				BYTE bTex = 0;
				if (pTex != NULL)
					bTex = 1;

				fwrite(&bTex, 1, 1, _pFile);

				if (pTex)
					pTex->Save(_pFile);
			}
			break;
			}
		}
	}
}

CRes * CMaterial::Load(FILE * _pFile)
{
	wstring strKey = LoadWString(_pFile);
	wstring strPath = LoadWString(_pFile);

	return CResMgr::GetInst()->FindMaterial(strKey);
}

void CMaterial::LoadShaderParam(FILE * _pFile)
{
	// 참조 쉐이더 유무
	BYTE bShader = 0;
	if (NULL != m_pShader)
		bShader = 1;
	fread(&bShader, 1, 1, _pFile);

	if (0 == bShader)
		return;

	// Shader key값 저장
	wstring strShaderKey = LoadWString(_pFile);
	CShader* pShader = CShaderMgr::GetInst()->FindShader(strShaderKey);
	SetShader(pShader);

	for (UINT i = 0; i < m_vecParam.size(); ++i)
	{
		switch (m_vecParam[i].eShaderParam)
		{
		case SHADER_PARAM::SP_INT_0:
		case SHADER_PARAM::SP_INT_1:
		case SHADER_PARAM::SP_INT_2:
		case SHADER_PARAM::SP_INT_3:
		{
			fread(m_vecParam[i].pData, sizeof(int), 1, _pFile);
		}
		break;
		case SHADER_PARAM::SP_FLOAT_0:
		case SHADER_PARAM::SP_FLOAT_1:
		case SHADER_PARAM::SP_FLOAT_2:
		case SHADER_PARAM::SP_FLOAT_3:
		{
			fread(m_vecParam[i].pData, sizeof(float), 1, _pFile);
		}
		break;
		case SHADER_PARAM::SP_VEC4_0:
		case SHADER_PARAM::SP_VEC4_1:
		case SHADER_PARAM::SP_VEC4_2:
		case SHADER_PARAM::SP_VEC4_3:
		{
			fread(m_vecParam[i].pData, sizeof(Vec4), 1, _pFile);
		}
		break;
		case SHADER_PARAM::SP_TEX_0:
		case SHADER_PARAM::SP_TEX_1:
		case SHADER_PARAM::SP_TEX_2:
		case SHADER_PARAM::SP_TEX_3:
		{
			BYTE bTex = 0;
			fread(&bTex, 1, 1, _pFile);

			if (bTex)
			{
				wstring strKey = LoadWString(_pFile);
				wstring strPath = LoadWString(_pFile);
				CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(strKey);
				(*(CResPtr<CTexture>*)m_vecParam[i].pData) = pTex;
			}
		}
		break;
		}
	}
}
