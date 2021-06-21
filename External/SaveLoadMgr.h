#pragma once

#include "define.h"

class CScene;
class CLayer;
class CGameObject;

class CSaveLoadMgr
{
	SINGLE(CSaveLoadMgr);

public:
	void SaveScene(const wstring& _strFilePath);
	void LoadScene(const wstring& _strFilePath, bool bScript = false);

	// 플레이 버튼시 Stop Scene 저장
	void SaveStopScene(const wstring& _strFilePath);
	// 스탑 버튼시 Play Scene 저장
	void LoadPlayScene(const wstring& _strFilePath);

private:
	void SaveLayer(CLayer* _pLayer, FILE* _pFile);
	CLayer* LoadLayer(FILE* _pFile);

	void SaveGameObject(CGameObject* _pObj, FILE* _pFile);
	CGameObject* LoadGameObject(FILE* _pFile);
};

