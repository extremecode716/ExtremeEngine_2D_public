#include "stdafx.h"
#include "Inventory.h"
#include "Slot.h"

#include "DefineCode\ItemScript.h"
#include "..\ScriptMgr\View\ItemTable.h" // 임시 테스트
#include "MoveToMouseScript.h"
#include "..\ScriptMgr\View\MouseScript.h"

CInventory::CInventory()
	: m_strName(L"")
	, m_vPos{0.f, 0.f}
	, m_vSize{400.f, 250.f}
	, m_vSlotStartPos{0.f, 0.f , 0.f}
	, m_vSlotScale{50.f, 50.f, 1.f}
	, m_iSlotCount(0)
	, m_pBackMtrl(NULL)
	, m_pTapMtrl(NULL)
	, m_pTitleMtrl(NULL)
	, m_pExitMtrl(NULL)
	, m_bOpen(false)
	, m_pFocusSlot(NULL)
	, m_pMouseMgr(NULL)
	, m_bColl(false)
{
}

CInventory::~CInventory()
{
	SAFE_DELETE(m_pTapMtrl);
	SAFE_DELETE(m_pBackMtrl);
	SAFE_DELETE(m_pTitleMtrl);
	SAFE_DELETE(m_pExitMtrl);
}

void CInventory::awake()
{
	list<CGameObject*>::iterator iter = GetGameObject()->GetChildList().begin();
	for (; iter != GetGameObject()->GetChildList().end(); ++iter)
	{
		if ((*iter)->GetTag() == L"Inven_title")
		{
			(*iter)->Script<CMoveToMouseScript>()->SetParentName(L"Inventory");
			break;
		}
	}
}

void CInventory::start()
{
	Init(L"PlayerInventory", 28);
	GetGameObject()->SetEnableIncludingChild(false);
	m_pMouseMgr = CMouseScript::GetThis();

	// Text
	m_tTitleText.SetDrawInfo(L"Inven_tile", false, L"인벤토리", 50.f, 0, 0, 0xff000000);
	CFontEngine::GetInst()->InsertText(m_tTitleText.GetKey(), m_tTitleText);
	m_vTitleTextOffset = Vec2(-120.f, 200.f);
}


void CInventory::Init(const wstring& _strName, UINT _iSlotCount)
{
	m_strName = _strName;
	m_iSlotCount = _iSlotCount;
	m_vPos = Transform()->GetLocal2DPos();

	m_vecSlot.resize(_iSlotCount);

	CreateSlots();

	ChangeInventoryMtrl();

	// 임시 테스트 인벤토리에 아이템 삽입
	CItemTable* pItemTable = CItemTable::GetThis();

	CItemScript* pItemScript = pItemTable->CreateItem(L"흑요석단검");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"머리빗");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"가시달린아가미");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"각성포션");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"노랑포션");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"강화클립");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"고농축오리데오콘");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"고밀도카르늄");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"꽃반지");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"디아볼루스부츠");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"디아볼루스아머");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"망토");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"머플러");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"이속증가포션");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"하회탈");
	PushItem(pItemScript);

	pItemScript = pItemTable->CreateItem(L"후드");
	PushItem(pItemScript);
}

/*
함수명  : CreateSlots
용도    : 슬릇들을 생성한다.
*/
void CInventory::CreateSlots()
{
	m_vSlotStartPos = Vec3(0 - m_vSize.x / 2.f + m_vSlotScale.x, 0 + m_vSize.y / 2.f - m_vSlotScale.y, 17.f);

	Vec3 vSlotPos;
	for (UINT i = 0; i < m_iSlotCount; ++i)
	{
		m_vecSlot[i] = new CSlot;
		m_vecSlot[i]->SetSlotIndex(i);
		m_vecSlot[i]->SetInventory(this);
		vSlotPos = InitSlotPos(i);

		CGameObject* pSlotObj = m_vecSlot[i]->Create(vSlotPos, m_vSlotScale);
		pSlotObj->awake();
		pSlotObj->start();

		GetGameObject()->AddChildObj(pSlotObj);
	}
}

/*
함수명  : CreateSlots
용도    : 인덱스에 따라 슬릇 위치를 반환한다.
*/
Vec3 CInventory::InitSlotPos(UINT _index)
{
	int iColumn = _index / 7;
	int iRow = _index % 7;

	Vec3 vSlotPos = m_vSlotStartPos;
	vSlotPos.y -= m_vSlotScale.y * iColumn;
	vSlotPos.x += m_vSlotScale.x * iRow;

	return vSlotPos;
}

bool CInventory::HasFocusSlotItem()
{
	if (NULL == m_pFocusSlot) return false;
	bool bFocusItem = (m_pFocusSlot->GetItemScript() != NULL) ? true : false;

	return bFocusItem;
}

bool CInventory::HasDragItem()
{
	if (NULL == m_pMouseMgr->GetDragObj())
		return false;

	return true;
}


bool CInventory::IsIndex(UINT _index)
{
	if (_index < 0 || _index >= m_vecSlot.capacity())
		return false;

	return true;
}

bool CInventory::IsEmpty(UINT _index)
{
	//bool bIndex = IsIndex(_index);
	//if (!bIndex) return false;

	CSlot* pSlot = m_vecSlot[_index];
	if (NULL == pSlot)
		return false;

	return pSlot->IsEmpty();
}

void CInventory::SetSlotPos(UINT _index, const Vec2 & _vPos)
{
	m_vecSlot[_index]->SetPos(_vPos);
}

void CInventory::SetSlotSize(UINT _index, const Vec2 & _vSize)
{
	m_vecSlot[_index]->SetSize(_vSize);
}

void CInventory::ChangeInventoryMtrl()
{
	CGameObject* pObj = GetGameObject()->FindChildObjByTag(L"Inven_tap");
	if (NULL != pObj)
	{
		m_pTapMtrl = pObj->MeshRender()->GetMaterial();
		CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"tab_itm_01Tex");
		m_pTapMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);
	}
	pObj = GetGameObject()->FindChildObjByTag(L"Inven_background");
	if (NULL != pObj)
	{
		m_pBackMtrl = pObj->MeshRender()->GetMaterial();
		CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"itemwin_leftTex");
		m_pBackMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);
	}

	pObj = GetGameObject()->FindChildObjByTag(L"Inven_titlebar");
	if (NULL != pObj)
	{
		m_pTitleMtrl = pObj->MeshRender()->GetMaterial();
		CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"titlebar_fixTex");
		m_pTitleMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);
	}

}

UINT CInventory::GetSlotIndex(const Vec2 & _vPos)
{
	return 0;
}

bool CInventory::PushItem(CItemScript * _pItemScript)
{
	if (NULL == _pItemScript) return false;

	bool bPushSuccess = false;
	UINT index = 0;
	for (; index < m_iSlotCount; ++index)
	{
		if (bPushSuccess = IsEmpty(index))
		{
			break;
		}
	}
	if (!bPushSuccess) return false;

	m_vecSlot[index]->PushItemScript(_pItemScript);
	_pItemScript->SetSlot(index);

	return true;
}

/*
함수명  : PopItem
용도    : Inventory 에서 아이템을 제거한다.
*/
bool CInventory::PopItem(CItemScript * _pItemScript)
{
	if (NULL == _pItemScript) return false;

	int iSlotIndex = _pItemScript->GetSlot();
	m_vecSlot[iSlotIndex]->PopItemScript();

	return true;
}

float CInventory::Distance(const Vec2 & _vSrcPos, const Vec2 & _vDestPos)
{
	Vec2 vScrPos = _vSrcPos;
	Vec2 vDestPos = _vDestPos;
	float fDist = Vec2(vScrPos - vDestPos).Distance();

	return fDist;
}

void CInventory::SetFocusSlot(CSlot * _pSlot)
{
	m_pFocusSlot = _pSlot;
}

void CInventory::OnCollisionEnter(CCollider * _pOther)
{
	if (false == m_bOpen) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = true;
	}
}

void CInventory::OnCollision(CCollider * _pOther)
{
	if (false == m_bOpen) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = true;
	}
}

void CInventory::OnCollisionExit(CCollider * _pOther)
{
	if (false == m_bOpen) return;
	int iFindKey = _pOther->GetGameObject()->GetTag().find(L"Mouse");
	if (iFindKey > -1)
	{
		m_bColl = false;
	}
}

int CInventory::update()
{
	m_vPos = Transform()->GetLocal2DPos();
	m_vSize = Transform()->GetLocal2DScale();

	// Text 수정
	m_tTitleText.SetPos(m_vPos + m_vTitleTextOffset);
	CFontEngine::GetInst()->ChangeText(m_tTitleText.GetKey(), m_tTitleText);

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_I, KEY_STATE::STATE_TAB))
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

int CInventory::lateupdate()
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
					bool bPush = PushItem(pItemScript);
					if (true == bPush)
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
