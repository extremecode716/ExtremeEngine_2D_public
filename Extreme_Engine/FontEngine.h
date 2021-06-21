#pragma once

#include "global.h"

// Font
#pragma comment(lib, "FW1FontWrapper")

// FontEngine은 힙영역에 등록한다. 데이터영역일 때 Portal 스크립트 처리 해제 순서 문제가 생기므로. 해제는 SceneMgr
class CFontEngine
{
private:
	static CFontEngine* g_pInstance;

public:
	static CFontEngine* GetInst();
	static void DeleteInst();

private:
	CFontEngine();
	~CFontEngine();

private:
	IFW1Factory*		m_pFW1Factory;
	IFW1FontWrapper*	m_pFontWrapper;

public:
	map<wstring, tDrawStringInfo> m_mapText;

private:
	bool IsFindText(const wstring& _strTextKey);

public:
	bool InsertText(const wstring& _strTextKey, const tDrawStringInfo& _tTexInfo);
	bool ChangeText(const wstring& _strTextKey, const tDrawStringInfo& _tTexInfo);
	bool eraseText(const wstring& _strTextKey);

public:
	void init();

public:
	void DrawFont();
	void DrawFont(wchar_t* _pStr, float _fPosX, float _fPosY, float _fSize, UINT _Color);
};
