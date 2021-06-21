#include "Texture.h"

#include "PathMgr.h"
#include "Device.h"

CTexture::CTexture()
	: m_tDesc{}
{
}

CTexture::~CTexture()
{
	SAFE_DELETE(m_pImage);
	SAFE_RELEASE(m_pTex2D);
	SAFE_RELEASE(m_pView);
}

CTexture * CTexture::Create(const wstring & _strFileName)
{
	wstring strExt = CPathMgr::GetExt(_strFileName.c_str());

	ScratchImage* pImage = new ScratchImage;

	bool bFail = false;
	if (strExt == L".dds" || strExt == L".DDS")
	{
		if (FAILED(LoadFromDDSFile(_strFileName.c_str(), DDS_FLAGS_NONE, NULL, *pImage)))
		{
			bFail = true;
		}
	}
	else if (strExt == L".tga" || strExt == L".TGA")
	{
		if (FAILED(LoadFromTGAFile(_strFileName.c_str(), NULL, *pImage)))
		{
			bFail = true;
		}
	}
	else
	{
		if (FAILED(LoadFromWICFile(_strFileName.c_str(), WIC_FLAGS_NONE, NULL, *pImage)))
		{
			bFail = true;
		}
	}

	if (bFail)
	{
		SAFE_DELETE(pImage);
		return NULL;
	}

	ID3D11ShaderResourceView* pView = NULL;

	if (FAILED(CreateShaderResourceView(DEVICE
		, pImage->GetImages(), pImage->GetImageCount(),
		pImage->GetMetadata(), &pView)))
	{
		SAFE_DELETE(pImage);
		return NULL;
	}

	CTexture* pTexture = new CTexture;
	pTexture->m_pImage = pImage;
	pTexture->m_pView = pView;
	pView->GetResource((ID3D11Resource**)&pTexture->m_pTex2D); // RefCount Áõ°¡
	pTexture->m_pTex2D->GetDesc(&pTexture->m_tDesc);

	return pTexture;
}

void CTexture::SaveTexture(const wstring & _strPath)
{
	wstring strPath = CPathMgr::GetResPath();
	strPath += _strPath;

	SaveToWICFile(*(m_pImage->GetImages()),
		WIC_FLAGS_NONE,
		GetWICCodec(static_cast<WICCodecs>(WIC_CODEC_PNG)),
		strPath.c_str());

}

void CTexture::ResetImage()
{
	//ID3D11Texture2D*	pTex2D = NULL;

	//m_pView->GetResource((ID3D11Resource**)(&pTex2D));
	//D3D11_MAPPED_SUBRESOURCE tData = {};

	//CONTEXT->Map(pTex2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &tData);
	//memcpy(tData.pData, m_pImage->GetPixels(), m_pImage->GetPixelsSize());
	//CONTEXT->Unmap(pTex2D, 0);

	//SAFE_RELEASE(pTex2D);

	ID3D11ShaderResourceView* pView = NULL;

	CreateShaderResourceView(DEVICE, m_pImage->GetImages(), m_pImage->GetImageCount(),
		m_pImage->GetMetadata(), &pView);

	ID3D11Texture2D* pTex2D = NULL;
	pView->GetResource((ID3D11Resource**)&pTex2D);

	SAFE_RELEASE(m_pTex2D);
	SAFE_RELEASE(m_pView);

	m_pTex2D = pTex2D;
	m_pView = pView;

}

bool CTexture::IsDynamic()
{
	if (m_tDesc.Usage == D3D11_USAGE_DYNAMIC)
		return true;
	return false;
}

void CTexture::ChangeDynamic()
{
	m_tDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ID3D11Texture2D* pTex2D = NULL;
	D3D11_SUBRESOURCE_DATA tSub = {};

	tSub.pSysMem = m_pImage->GetPixels();
	tSub.SysMemPitch = m_pImage->GetImages()->rowPitch;
	tSub.SysMemSlicePitch = m_pImage->GetImages()->slicePitch;

	DEVICE->CreateTexture2D(&m_tDesc, &tSub, &pTex2D);

	D3D11_SHADER_RESOURCE_VIEW_DESC tResDesc = {};
	tResDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	tResDesc.Texture2D.MipLevels = m_tDesc.MipLevels;

	ID3D11ShaderResourceView * pView = NULL;
	DEVICE->CreateShaderResourceView(pTex2D, &tResDesc, &pView);

	SAFE_RELEASE(m_pTex2D);
	SAFE_RELEASE(m_pView);

	m_pTex2D = pTex2D;
	m_pView = pView;
}

void CTexture::UpdateData(UINT _iRegister, UINT _iTiming)
{
	if (_iTiming & (UINT)SHADER_TYPE::ST_VERTEX)
		CONTEXT->VSSetShaderResources(_iRegister, 1, &m_pView);
	if (_iTiming & (UINT)SHADER_TYPE::ST_HULL)
		CONTEXT->HSSetShaderResources(_iRegister, 1, &m_pView);
	if (_iTiming & (UINT)SHADER_TYPE::ST_DOMAIN)
		CONTEXT->DSSetShaderResources(_iRegister, 1, &m_pView);
	if (_iTiming & (UINT)SHADER_TYPE::ST_GEOMETRY)
		CONTEXT->GSSetShaderResources(_iRegister, 1, &m_pView);
	if (_iTiming & (UINT)SHADER_TYPE::ST_COMPUTE)
		CONTEXT->CSSetShaderResources(_iRegister, 1, &m_pView);
	if (_iTiming & (UINT)SHADER_TYPE::ST_PIXEL)
		CONTEXT->PSSetShaderResources(_iRegister, 1, &m_pView);
}