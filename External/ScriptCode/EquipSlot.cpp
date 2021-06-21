#include "stdafx.h"
#include "EquipSlot.h"
#include "Inventory.h"
#include "DefineCode\\ItemScript.h"
#include "EquipmentWindow.h"

CEquipSlot::CEquipSlot()
	: m_pEquipItemScript(NULL)
	, m_pInven(NULL)
	, m_pEquipment(NULL)
	, m_vPos{ 0.f, 0.f, 0.f }
	, m_vScale{ 1.f , 1.f, 1.f }
	, m_bColl(false)
	, m_iClickCount(0)
	, m_bDoubleClicked(false)
	, m_fDoubleClickedMinTime(0.5f)
	, m_fDoubleClickedTime(0.f)
{
}


CEquipSlot::~CEquipSlot()
{
}

void CEquipSlot::start()
{
	m_pInven = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->FindWithTag(L"Inventory")->Script<CInventory>();
	m_vScale = Transform()->GetLocalScale();
}

int CEquipSlot::update()
{
	if (NULL == m_pEquipItemScript || NULL == m_pInven) return RET_FAILED;
	if (false == m_pEquipment->m_bOpen) return RET_FAILED;

	if (m_pEquipment->HasDragItem() == false )
	{
		if (true == m_bColl)
		{
			if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_TAB))
			{
				++m_iClickCount;

				m_pEquipment->SetFocusSlot(this);
			}
			m_bColl = false;
		}
		else
		{
			m_iClickCount = 0;
			m_fDoubleClickedTime = 0.f;
		}


		// 클릭 시작 시 더블클릭 유효화 판정
		if (m_iClickCount > 0)
		{
			m_fDoubleClickedTime += DT();

			if (m_fDoubleClickedTime < m_fDoubleClickedMinTime)
			{
				if (m_iClickCount > 1)
				{
					m_bDoubleClicked = true;
					bool bInvenPush = m_pInven->PushItem(m_pEquipItemScript);
					if (true == bInvenPush)
					{
						m_pEquipItemScript = NULL;
						m_pEquipment->SetFocusSlot(NULL);
					}
					m_bDoubleClicked = false;
				}
			}
			else
			{
				m_fDoubleClickedTime = 0.f;
				m_iClickCount = 0;
			}
		}
	}

	return RET_SUCCESS;
}

CGameObject * CEquipSlot::Create()
{
	CPrefab* pEquipPrefab = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Equip_Slot(Prefab)");

	CGameObject* pClone = Instantiate(pEquipPrefab, m_vPos, L"Default");
	pClone->AddComponent<CScript>(this);

	return pClone;
}

void CEquipSlot::OnCollisionEnter(CCollider * _pOther)
{
	if (false == m_pEquipment->m_bOpen) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = true;
	}
}

void CEquipSlot::OnCollision(CCollider * _pOther)
{
	if (false == m_pEquipment->m_bOpen) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = true;
	}
}

void CEquipSlot::OnCollisionExit(CCollider * _pOther)
{
	if (false == m_pEquipment->m_bOpen) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = false;
	}
}


bool CEquipSlot::IsEmpty()
{
	bool bEmpty = (NULL == m_pEquipItemScript) ? true : false;

	return bEmpty;
}


/*
함수명  : EquipItem
용도    : slot에 장비 착용 (이미 착용된 상태면 해당 장비에서 인벤토리로 보내주는 로직)
*/
bool CEquipSlot::EquipItem(CItemScript * _pItemScript)
{
	if (NULL == m_pInven) return false;
	
	bool bEnable = GetGameObject()->GetEnable();

	bool bEmpty = IsEmpty();
	if (true == bEmpty)
	{
		m_pEquipItemScript = _pItemScript;
		CGameObject* pItemObj = m_pEquipItemScript->GetGameObject();
		m_pEquipItemScript->start();
		CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->AddGameObject(pItemObj);
		GetGameObject()->AddChildObj(pItemObj);
		pItemObj->SetEnable(bEnable);
	}
	else
	{
		bool bMoveInven = false;
		bMoveInven = m_pInven->PushItem(m_pEquipItemScript);
		if (false == bMoveInven) return false;

		m_pEquipItemScript = _pItemScript;
		CGameObject* pItemObj = m_pEquipItemScript->GetGameObject();
		m_pEquipItemScript->start();
		CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->AddGameObject(pItemObj);
		GetGameObject()->AddChildObj(pItemObj);
		pItemObj->SetEnable(bEnable);
	}

	return true;
}

void CEquipSlot::PopItemScript()
{
	m_pEquipItemScript = NULL;
}

