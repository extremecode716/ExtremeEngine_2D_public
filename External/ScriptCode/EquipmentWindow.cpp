#include "stdafx.h"
#include "EquipmentWindow.h"
#include "DefineCode\ItemScript.h"
#include "Inventory.h"
#include "EquipSlot.h"
#include "MoveToMouseScript.h"
#include "..\ScriptMgr\View\MouseScript.h"

CEquipmentWindow::CEquipmentWindow()
	: m_strName(L"")
	, m_vSlotScale{50.f, 50.f, 1.f}
	, m_pInven(NULL)
	, m_pHead1(NULL)
	, m_pHead2(NULL)
	, m_pHead3(NULL)
	, m_pBody(NULL)
	, m_pR_Hand(NULL)
	, m_pL_Hand(NULL)
	, m_pRobe(NULL)
	, m_pShoes(NULL)
	, m_pAcc1(NULL)
	, m_pAcc2(NULL)
	, m_pFocusSlot(NULL)
	, m_bOpen(false)
	, m_bColl(false)
	, m_pMouseMgr(NULL)
	, m_pBackMtrl(NULL)
{
}


CEquipmentWindow::~CEquipmentWindow()
{
	SAFE_DELETE(m_pBackMtrl);
}


void CEquipmentWindow::start()
{
	m_strName = L"PlayerEquip";
	InitEquip();
	GetGameObject()->SetEnableIncludingChild(false);
	m_pMouseMgr = CMouseScript::GetThis();

	// Text
	m_tTitleText.SetDrawInfo(L"Equip_tile", false, L"장비창", 50.f, 0, 0, 0xff000000);
	CFontEngine::GetInst()->InsertText(m_tTitleText.GetKey(), m_tTitleText);
	m_vTitleTextOffset = Vec2(-75.f, 270.f);
}

int CEquipmentWindow::update()
{
	m_vPos = Transform()->GetLocal2DPos();
	m_vScale = Transform()->GetLocal2DScale();

	// Text 수정
	m_tTitleText.SetPos(m_vPos + m_vTitleTextOffset);
	CFontEngine::GetInst()->ChangeText(m_tTitleText.GetKey(), m_tTitleText);

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_E, KEY_STATE::STATE_TAB))
	{
		if (false == m_bOpen)
		{
			m_bOpen = true;
			GetGameObject()->SetEnableIncludingChild(true);

			// Text 수정
			m_tTitleText.SetShow(true);
			CFontEngine::GetInst()->ChangeText(m_tTitleText.GetKey(), m_tTitleText);
		}
		else
		{
			m_bOpen = false;
			GetGameObject()->SetEnableIncludingChild(false);
			m_pFocusSlot = NULL;

			// Text 수정
			m_tTitleText.SetShow(false);
			CFontEngine::GetInst()->ChangeText(m_tTitleText.GetKey(), m_tTitleText);
		}
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_ESC, KEY_STATE::STATE_TAB))
	{
		if (true == m_bOpen)
		{
			m_bOpen = false;
			GetGameObject()->SetEnableIncludingChild(false);
			m_pFocusSlot = NULL;

			// Text 수정
			m_tTitleText.SetShow(false);
			CFontEngine::GetInst()->ChangeText(m_tTitleText.GetKey(), m_tTitleText);
		}
	}

	if (false == m_bOpen) return RET_FAILED;

	// 슬롯에서 분리시켜 마우스로 이동시킨다.
	bool bMouseDragItem = HasDragItem();
	if (bMouseDragItem == false)
	{
		bool bFocus = HasFocusSlotItem();
		if (true == bFocus)
		{
			CGameObject* pMouseObj = CMouseScript::GetThis()->GetGameObject();
			Vec2 vMousePos = pMouseObj->Transform()->GetLocal2DPos();
			CGameObject* pFocusItemObj = m_pFocusSlot->GetItemScript()->GetGameObject();
			Vec2 vFocusItemPos = pFocusItemObj->Transform()->GetWorld2DPos();

			vFocusItemPos.y -= m_vSlotScale.y / 2.f;

			float fDist = Distance(vMousePos, vFocusItemPos);

			if (fDist > 45.f)
			{
				CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->AddGameObject(pFocusItemObj);
				pMouseObj->AddChildObj(pFocusItemObj);
				CMouseScript::GetThis()->SetDragObj(pFocusItemObj);
				m_pFocusSlot->PopItemScript();
				m_pFocusSlot = NULL;
			}
		}
	}
	return RET_SUCCESS;
}

int CEquipmentWindow::lateupdate()
{
	if (false == m_bOpen) return RET_FAILED;

	bool bMouseDragItem = HasDragItem();
	if (bMouseDragItem == true)
	{
		if (m_bColl == true)
		{
			if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LBTN, KEY_STATE::STATE_TAB))
			{
				CItemScript* pItemScript = m_pMouseMgr->GetDragObj()->Script<CItemScript>();
				if (NULL != pItemScript)
				{
					bool bEqup = EquipItem(pItemScript);
					if (true == bEqup)
					{
						CMouseScript::GetThis()->SetDragObj(NULL);
					}
				}
			}
			m_bColl = false;
		}
	}

	return RET_SUCCESS;
}

/*
함수명  : InitEquip
용도    : 장비 인벤토리 초기화 (Equip Slot 생성 및 offset 셋팅)
*/
void CEquipmentWindow::InitEquip()
{
	m_pHead1  = new CEquipSlot;
	m_pHead2  = new CEquipSlot;
	m_pHead3  = new CEquipSlot;
	m_pBody   = new CEquipSlot;
	m_pR_Hand = new CEquipSlot;
	m_pL_Hand = new CEquipSlot;
	m_pRobe   = new CEquipSlot;
	m_pShoes  = new CEquipSlot;
	m_pAcc1   = new CEquipSlot;
	m_pAcc2   = new CEquipSlot;

	m_pHead1->SetSlotType((UINT)ITEM_TYPE::EQUIP_HEAD1_TYPE);
	m_pHead2->SetSlotType((UINT)ITEM_TYPE::EQUIP_HEAD2_TYPE);
	m_pHead3->SetSlotType((UINT)ITEM_TYPE::EQUIP_HEAD3_TYPE);
	m_pBody->SetSlotType((UINT)ITEM_TYPE::EQUIP_BODY_TYPE);
	m_pR_Hand->SetSlotType((UINT)ITEM_TYPE::EQUIP_RHAND_TYPE);
	m_pL_Hand->SetSlotType((UINT)ITEM_TYPE::EQUIP_LHAND_TYPE);
	m_pRobe->SetSlotType((UINT)ITEM_TYPE::EQUIP_ROBE_TYPE);
	m_pShoes->SetSlotType((UINT)ITEM_TYPE::EQUIP_SHOES_TYPE);
	m_pAcc1->SetSlotType((UINT)ITEM_TYPE::EQUIP_ACC1_TYPE);
	m_pAcc2->SetSlotType((UINT)ITEM_TYPE::EQUIP_ACC2_TYPE);

	Vec3 vOffset = Vec3(-220.f, 160.f, 0.f);
	m_pHead1->SetPos(vOffset);
	vOffset = Vec3(220.f, 160.f, 0.f);
	m_pHead2->SetPos(vOffset);
	vOffset = Vec3(-220.f, 96.f, 0.f);
	m_pHead3->SetPos(vOffset);
	vOffset = Vec3(220.f, 96.f, 0.f);
	m_pBody->SetPos(vOffset);
	vOffset = Vec3(-220.0f, 30.f, 0.f);
	m_pR_Hand->SetPos(vOffset);
	vOffset = Vec3(220.f, 30.f, 0.f);
	m_pL_Hand->SetPos(vOffset);
	vOffset = Vec3(-220.0f, -35.f, 0.f);
	m_pRobe->SetPos(vOffset);
	vOffset = Vec3(220.f, -35.f, 0.f);
	m_pShoes->SetPos(vOffset);
	vOffset = Vec3(-220.0f, -100.f, 0.f);
	m_pAcc1->SetPos(vOffset);
	vOffset = Vec3(220.f, -100.f, 0.f);
	m_pAcc2->SetPos(vOffset);

	m_pHead1->SetEquipment(this);
	m_pHead2->SetEquipment(this);
	m_pHead3->SetEquipment(this);
	m_pBody->SetEquipment(this);
	m_pR_Hand->SetEquipment(this);
	m_pL_Hand->SetEquipment(this);
	m_pRobe->SetEquipment(this);
	m_pShoes->SetEquipment(this);
	m_pAcc1->SetEquipment(this);
	m_pAcc2->SetEquipment(this);

	CreateEquipSlots();

	ChangeEquipMtrl();
}

void CEquipmentWindow::CreateEquipSlots()
{
	CGameObject* pEquipSlotObj;
	pEquipSlotObj = m_pHead1->Create();
	GetGameObject()->AddChildObj(pEquipSlotObj);
	pEquipSlotObj->awake();
	pEquipSlotObj->start();

	pEquipSlotObj = m_pHead2->Create();
	GetGameObject()->AddChildObj(pEquipSlotObj);
	pEquipSlotObj->awake();
	pEquipSlotObj->start();

	pEquipSlotObj = m_pHead3->Create();
	GetGameObject()->AddChildObj(pEquipSlotObj);
	pEquipSlotObj->awake();
	pEquipSlotObj->start();

	pEquipSlotObj = m_pBody->Create();
	GetGameObject()->AddChildObj(pEquipSlotObj);
	pEquipSlotObj->awake();
	pEquipSlotObj->start();

	pEquipSlotObj = m_pR_Hand->Create();
	GetGameObject()->AddChildObj(pEquipSlotObj);
	pEquipSlotObj->awake();
	pEquipSlotObj->start();

	pEquipSlotObj = m_pL_Hand->Create();
	GetGameObject()->AddChildObj(pEquipSlotObj);
	pEquipSlotObj->awake();
	pEquipSlotObj->start();

	pEquipSlotObj = m_pRobe->Create();
	GetGameObject()->AddChildObj(pEquipSlotObj);
	pEquipSlotObj->awake();
	pEquipSlotObj->start();

	pEquipSlotObj = m_pShoes->Create();
	GetGameObject()->AddChildObj(pEquipSlotObj);
	pEquipSlotObj->awake();
	pEquipSlotObj->start();

	pEquipSlotObj = m_pAcc1->Create();
	GetGameObject()->AddChildObj(pEquipSlotObj);
	pEquipSlotObj->awake();
	pEquipSlotObj->start();

	pEquipSlotObj = m_pAcc2->Create();
	GetGameObject()->AddChildObj(pEquipSlotObj);
	pEquipSlotObj->awake();
	pEquipSlotObj->start();
}

bool CEquipmentWindow::IsEquip(CItemScript * _pItemScript)
{
	UINT iType = _pItemScript->GetType();

	if ((iType & (UINT)ITEM_TYPE::EQUIP_TYPE) == (UINT)ITEM_TYPE::EQUIP_TYPE)
	{
		return true;
	}

	return false;
}

void CEquipmentWindow::ChangeEquipMtrl()
{
	CGameObject* pObj = GetGameObject()->FindChildObjByTag(L"Equip_background");
	if (NULL != pObj)
	{
		m_pBackMtrl = pObj->MeshRender()->GetMaterial();
		CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"EquipWinTex");
		m_pBackMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);
	}

}

bool CEquipmentWindow::HasFocusSlotItem()
{
	if (NULL == m_pFocusSlot) return false;
	bool bFocusItem = (m_pFocusSlot->GetItemScript() != NULL) ? true : false;

	return bFocusItem;
}

bool CEquipmentWindow::HasDragItem()
{
	if (NULL == m_pMouseMgr->GetDragObj())
		return false;

	return true;
}

float CEquipmentWindow::Distance(const Vec2 & _vSrcPos, const Vec2 & _vDestPos)
{
	Vec2 vScrPos = _vSrcPos;
	Vec2 vDestPos = _vDestPos;
	float fDist = Vec2(vScrPos - vDestPos).Distance();

	return fDist;
}

/*
함수명  : EquipItem
용도    : 아이템 착용 (착용가능 하면 인벤토리에서 해당 아이템을 가져와서 셋팅해준다.) 
*/
bool CEquipmentWindow::EquipItem(CItemScript * _pItemScript)
{
	if (NULL == _pItemScript) return false;
	bool bEquipType = IsEquip(_pItemScript);
	if (false == bEquipType) return false;
	m_pInven = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"Default")->FindWithTag(L"Inventory")->Script<CInventory>();
	if (NULL == m_pInven) return false;
	UINT iType = _pItemScript->GetType();

	bool bEquip = false;
	if ((iType & (UINT)ITEM_TYPE::EQUIP_HEAD1_TYPE) == (UINT)ITEM_TYPE::EQUIP_HEAD1_TYPE)
	{
		bEquip = m_pHead1->EquipItem(_pItemScript);
	}
	else if ((iType & (UINT)ITEM_TYPE::EQUIP_HEAD2_TYPE) == (UINT)ITEM_TYPE::EQUIP_HEAD2_TYPE)
	{
		bEquip = m_pHead2->EquipItem(_pItemScript);
	}
	else if ((iType & (UINT)ITEM_TYPE::EQUIP_HEAD3_TYPE) == (UINT)ITEM_TYPE::EQUIP_HEAD3_TYPE)
	{
		bEquip = m_pHead3->EquipItem(_pItemScript);
	}
	else if ((iType & (UINT)ITEM_TYPE::EQUIP_BODY_TYPE) == (UINT)ITEM_TYPE::EQUIP_BODY_TYPE)
	{
		bEquip = m_pBody->EquipItem(_pItemScript);
	}
	else if ((iType & (UINT)ITEM_TYPE::EQUIP_RHAND_TYPE) == (UINT)ITEM_TYPE::EQUIP_RHAND_TYPE)
	{
		bEquip = m_pR_Hand->EquipItem(_pItemScript);
	}
	else if ((iType & (UINT)ITEM_TYPE::EQUIP_LHAND_TYPE) == (UINT)ITEM_TYPE::EQUIP_LHAND_TYPE)
	{
		bEquip = m_pL_Hand->EquipItem(_pItemScript);
	}
	else if ((iType & (UINT)ITEM_TYPE::EQUIP_ROBE_TYPE) == (UINT)ITEM_TYPE::EQUIP_ROBE_TYPE)
	{
		bEquip = m_pRobe->EquipItem(_pItemScript);
	}
	else if ((iType & (UINT)ITEM_TYPE::EQUIP_SHOES_TYPE) == (UINT)ITEM_TYPE::EQUIP_SHOES_TYPE)
	{
		bEquip = m_pShoes->EquipItem(_pItemScript);
	}
	else if ((iType & (UINT)ITEM_TYPE::EQUIP_ACC1_TYPE) == (UINT)ITEM_TYPE::EQUIP_ACC1_TYPE)
	{
		bEquip = m_pAcc1->EquipItem(_pItemScript);
	}
	else if ((iType & (UINT)ITEM_TYPE::EQUIP_ACC2_TYPE) == (UINT)ITEM_TYPE::EQUIP_ACC2_TYPE)
	{
		bEquip = m_pAcc2->EquipItem(_pItemScript);
	}

	return bEquip;
}

void CEquipmentWindow::SetFocusSlot(CEquipSlot * _pSlot)
{
	m_pFocusSlot = _pSlot;
}

void CEquipmentWindow::awake()
{
	list<CGameObject*>::iterator iter = GetGameObject()->GetChildList().begin();
	for (; iter != GetGameObject()->GetChildList().end(); ++iter)
	{
		// 문제발생.
		if ((*iter)->GetTag() == L"Equip_title")
		{
			(*iter)->Script<CMoveToMouseScript>()->SetParentName(L"Equipwindow");
			break;
		}
	}
}

void CEquipmentWindow::OnCollisionEnter(CCollider * _pOther)
{
	if (false == m_bOpen) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = true;
	}
}

void CEquipmentWindow::OnCollision(CCollider * _pOther)
{
	if (false == m_bOpen) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = true;
	}
}

void CEquipmentWindow::OnCollisionExit(CCollider * _pOther)
{
	if (false == m_bOpen) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = false;
	}
}
