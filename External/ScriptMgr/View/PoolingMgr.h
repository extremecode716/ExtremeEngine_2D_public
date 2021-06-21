#pragma once

#include "..\SingletonScript.h"
// #include <tuple>

// SceneTable이 로드 할때마다 교체 할 것이다.
// SceneTable이 관리
// 일단 몬스터 전용
class CPoolingMgr
	: public CSingletonScript<CPoolingMgr>
{
private:
	map<wstring, vector<CGameObject*>*> m_mapPooling;

public:
	vector<CGameObject*>* FindVecGameObj(const wstring& _strKey);
	bool InsertPooling(const wstring& _strKey, UINT _iCount);
	void Clear();

private:
	virtual int update() override { return RET_SUCCESS; }

public:
	virtual CPoolingMgr* Clone() override { return new CPoolingMgr(*this); }

public:
	CPoolingMgr();
	~CPoolingMgr();
};

