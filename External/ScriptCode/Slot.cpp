#include "stdafx.h"
#include "Slot.h"
#include "DefineCode\\ItemScript.h"
#include "EquipmentWindow.h"
#include "Inventory.h"

#include "DebugMgr.h"



CSlot::CSlot()
	: m_iIndex(0)
	, m_iQuantity(0)
	, m_vPos{0.f, 0.f}
	, m_vSize{0.f, 0.f}
	, m_pItemScript(NULL)
	, m_bColl(false)
	, m_iClickCount(0)
	, m_bDoubleClicked(false)
	, m_fDoubleClickedMinTime(0.5f)
	, m_fDoubleClickedTime(0.f)
	, m_pInven(NULL)
	, m_pEquipment(NULL)
{
}

CSlot::~CSlot()
{
}

bool CSlot::IsEmpty()
{
	bool bEmpty = (NULL == m_pItemScript) ? true : false;
	
	return bEmpty;
}

void CSlot::PushItemScript(CItemScript * _pItemScript)
{
	bool bEnable = GetGameObject()->GetEnable();

	if (NULL == m_pItemScript)
	{
		m_pItemScript = _pItemScript;
		CGameObject* pItemObj = m_pItemScript->GetGameObject();
		m_pItemScript->start();
		CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->AddGameObject(pItemObj);
		GetGameObject()->AddChildObj(pItemObj);
		pItemObj->SetEnable(bEnable);
	}
	else if (m_pItemScript->GetIDx() == _pItemScript->GetIDx())
	{
		++m_iQuantity;
	}
	else
	{
		// Error
	}
}

void CSlot::PopItemScript(UINT _iCount)
{
	if (m_iQuantity >= _iCount)
	{
		m_iQuantity -= _iCount;
	}

	if (m_iQuantity == 0)
	{
		m_pItemScript = NULL;
	}
}

void CSlot::SetPos(const Vec2 & _vPos)
{
	m_vPos = _vPos;
	
}

void CSlot::SetSize(const Vec2 & _vSize)
{
	m_vSize = _vSize;
}

CGameObject* CSlot::Create(const Vec3 & _vPos, const Vec3 & _vScale)
{
	CPrefab* pSlotPrefab =  (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Inven_Slot(Prefab)");

	CGameObject* pClone = Instantiate(pSlotPrefab, _vPos, L"Default");
	m_vPos = Vec2(_vPos.x, _vPos.y);
	m_vSize = Vec2(_vScale.x, _vScale.y);
	pClone->AddComponent<CScript>(this);
	return pClone;
}

void CSlot::OnCollisionEnter(CCollider * _pOther)
{
	if (false == m_pInven->m_bOpen) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = true;
	}
}

void CSlot::OnCollision(CCollider * _pOther)
{
	if (false == m_pInven->m_bOpen) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = true;
	}
}

void CSlot::OnCollisionExit(CCollider * _pOther)
{
	if (false == m_pInven->m_bOpen) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = false;
	}
}

void CSlot::start()
{
	m_pEquipment = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->FindWithTag(L"Equipwindow")->Script<CEquipmentWindow>();

}

int CSlot::update()
{
	if (NULL == m_pItemScript || NULL == m_pEquipment) return RET_FAILED;
	if (false == m_pInven->m_bOpen) return RET_FAILED;

	if (m_pInven->HasDragItem() == false)
	{
		if (true == m_bColl)
		{
			if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_TAB))
			{
				++m_iClickCount;

				m_pInven->SetFocusSlot(this);
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
					bool bEquip = m_pEquipment->EquipItem(m_pItemScript);
					if (true == bEquip)
					{
						m_pItemScript = NULL;
						m_pInven->SetFocusSlot(NULL);
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
