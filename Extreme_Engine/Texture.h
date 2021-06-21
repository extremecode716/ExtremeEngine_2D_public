#pragma once
#include "Res.h"


// https://github.com/Microsoft/DirectXTex

class CTexture :
	public CRes
{
private:
	ScratchImage*				m_pImage;
	ID3D11Texture2D*			m_pTex2D;
	ID3D11ShaderResourceView*	m_pView;

	D3D11_TEXTURE2D_DESC	    m_tDesc;

public:
	static CTexture* Create(const wstring& _strFileName);
	const ID3D11ShaderResourceView* GetView() { return m_pView; }

	float GetWidth() { return (float)m_pImage->GetMetadata().width; }
	float GetHeight() { return (float)m_pImage->GetMetadata().height; }
	void* GetPixel() { return m_pImage->GetPixels(); }
	void SaveTexture(const wstring& _strPath);
	void ResetImage();

	// 이미지가 동적인지 확인
	bool IsDynamic();
	// 동적 이미지로 변경
	void ChangeDynamic();
public:
	void UpdateData(UINT _iRegister, UINT _iTiming);

public:
	CTexture();
	virtual ~CTexture();
};


