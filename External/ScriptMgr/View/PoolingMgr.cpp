#include "stdafx.h"
#include "PoolingMgr.h"
#include "MonsterTable.h"
#include "..\External\DefineCode\MonsterScript.h"

CPoolingMgr::CPoolingMgr()
{
}

CPoolingMgr::~CPoolingMgr()
{
	Safe_Delete_Map(m_mapPooling);
	m_mapPooling.clear();
}

/*
함수명  : InsertPooling(const wstring & _strKey, UINT _iCount)
용도    : 오브젝트 폴링에 사용할 GameObject를 넣어준다. key를 통해서 CMonsterTable에서 가져옴. 높은 의존관계.
*/
bool CPoolingMgr::InsertPooling(const wstring & _strKey, UINT _iCount)
{
	// 개수 제한 현재 임시 50
	if (_iCount == 0 || _iCount > 50) return false;

	CPrefab* pPrefab = NULL;

	// 몬스터 테이블에 등록된 것만 찾아온다.
	pPrefab = CMonsterTable::GetInst()->FindMonster(_strKey);
	if (pPrefab == NULL)
		return false;

	vector<CGameObject*>* pVecObj = new vector<CGameObject*>();
	pVecObj->resize(_iCount);
	for (UINT i = 0; i < _iCount; ++i)
	{
		CGameObject* pClone = Instantiate(pPrefab, Vec3(0.f, 0.f, 98.f));
		wstring strTag = pClone->GetTag() + to_wstring(i);
		pClone->SetTag(strTag);
		// 임시로 몬스터만... 설계를 부모 하나를 더 둬야했음...
		// 일단 귀찮으니 일단. 쓰자...
		pClone->Script<CMonsterScript>()->SetCollqName(strTag);
		pClone->awake();
		pClone->start();
		pClone->SetActive(false);

		pVecObj->operator[](i) = pClone;
	}

	m_mapPooling.insert(make_pair(_strKey, pVecObj));

	return true;
}

vector<CGameObject*>* CPoolingMgr::FindVecGameObj(const wstring & _strKey)
{
	map<wstring, vector<CGameObject*>*>::iterator iter = m_mapPooling.find(_strKey);
	auto mapNull = m_mapPooling.end();
	if (iter == mapNull)
		return NULL;

	return iter->second;
}

void CPoolingMgr::Clear()
{
	m_mapPooling.clear();
}
