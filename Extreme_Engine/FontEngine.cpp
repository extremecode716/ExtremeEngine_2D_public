#include "FontEngine.h"

#include "Device.h"

CFontEngine* CFontEngine::g_pInstance = NULL;

CFontEngine * CFontEngine::GetInst()
{
	if (NULL == g_pInstance)
	{
		g_pInstance = new CFontEngine;
	}
	return g_pInstance;
}

void CFontEngine::DeleteInst()
{
	if (NULL != g_pInstance)
	{
		delete g_pInstance;
		g_pInstance = NULL;
	}
}

CFontEngine::CFontEngine()
	: m_pFW1Factory(NULL)
	, m_pFontWrapper(NULL)
{
}


CFontEngine::~CFontEngine()
{
	SAFE_RELEASE(m_pFW1Factory);
	SAFE_RELEASE(m_pFontWrapper);
}

bool CFontEngine::IsFindText(const wstring & _strTextKey)
{
	map<wstring, tDrawStringInfo>::iterator iter = m_mapText.find(_strTextKey);

	if (iter == m_mapText.end())
		return false;

	return true;
}

bool CFontEngine::InsertText(const wstring& _strTextKey, const tDrawStringInfo & _tTexInfo)
{
	bool bFind = IsFindText(_strTextKey);
	if (bFind == true) return false;

	m_mapText.insert(make_pair(_strTextKey, _tTexInfo));

	return true;
}

bool CFontEngine::ChangeText(const wstring & _strTextKey, const tDrawStringInfo & _tTexInfo)
{
	map<wstring, tDrawStringInfo>::iterator iter = m_mapText.find(_strTextKey);

	if (iter == m_mapText.end())
		return false;

	iter->second.bShow = _tTexInfo.bShow;
	iter->second.strText = _tTexInfo.strText;
	iter->second.fFontSize = _tTexInfo.fFontSize;
	iter->second.fPositionX = _tTexInfo.fPositionX;
	iter->second.fPositionY = _tTexInfo.fPositionY;
	iter->second.iColor = _tTexInfo.iColor;

	return true;
}

bool CFontEngine::eraseText(const wstring & _strTextKey)
{
	map<wstring, tDrawStringInfo>::iterator iter = m_mapText.find(_strTextKey);

	if (iter == m_mapText.end())
		return false;

	m_mapText.erase(iter);

	return true;
}

void CFontEngine::init()
{
	if (FAILED(FW1CreateFactory(FW1_VERSION, &m_pFW1Factory)))
	{
		assert(NULL);
	}

	if (FAILED(m_pFW1Factory->CreateFontWrapper(DEVICE, L"Arial", &m_pFontWrapper)))
	{
		assert(NULL);
	}
}

void CFontEngine::DrawFont()
{
	map<wstring, tDrawStringInfo>::iterator iter = m_mapText.begin();
	
	for (; iter != m_mapText.end(); ++iter)
	{
		if (iter->second.bShow == true)
		{
			m_pFontWrapper->DrawString(
				CONTEXT,
				(iter->second.strText.c_str()), // String
				(iter->second.fFontSize), //Font Size
				(iter->second.fPositionX), // X position
				(iter->second.fPositionY),  // Y position
				(iter->second.iColor), // Text color // 0xAaBbGgRr
				0 //  Flags (for example FW1_RESTORESTATE to keep context states unchanged)
			);
		}
	}


}

void CFontEngine::DrawFont(wchar_t * _pStr, float _fPosX, float _fPosY, float _fSize, UINT _Color)
{
	m_pFontWrapper->DrawString(
		CONTEXT,
		_pStr,// String
		_fSize,// Font size
		_fPosX,// X position
		_fPosY,// Y position
		_Color,// Text color, 0xAaBbGgRr
		0// Flags (for example FW1_RESTORESTATE to keep context states unchanged)
	);
}
