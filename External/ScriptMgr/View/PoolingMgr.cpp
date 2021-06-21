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
�Լ���  : InsertPooling(const wstring & _strKey, UINT _iCount)
�뵵    : ������Ʈ ������ ����� GameObject�� �־��ش�. key�� ���ؼ� CMonsterTable���� ������. ���� ��������.
*/
bool CPoolingMgr::InsertPooling(const wstring & _strKey, UINT _iCount)
{
	// ���� ���� ���� �ӽ� 50
	if (_iCount == 0 || _iCount > 50) return false;

	CPrefab* pPrefab = NULL;

	// ���� ���̺� ��ϵ� �͸� ã�ƿ´�.
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
		// �ӽ÷� ���͸�... ���踦 �θ� �ϳ��� �� �־�����...
		// �ϴ� �������� �ϴ�. ����...
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
